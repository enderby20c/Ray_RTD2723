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
// ID Code      : ScalerHdcp14.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDCP14__

#include "ScalerFunctionInclude.h"
#include "Hdcp14/ScalerHdcp14.h"


#if(_HW_HDCP_1_4_SEPARATE_CIPHER_SUPPORT == _ON)
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
// Description  : Enable/Disable DownLoad HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp14RxCipherDownLoadKey(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable HDCP Block and Key download port
        ScalerSetBit(P63_A0_DP_HDCP_CONTROL, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Enable HDCP Sram clk
        ScalerSetBit(P63_97_HDCP_DUMMY_1, ~_BIT2, _BIT2);
        ScalerMcuDelayXus(1);
    }
    else
    {
        // Disable HDCP Sram clk
        ScalerSetBit(P63_97_HDCP_DUMMY_1, ~_BIT2, 0x00);
        ScalerMcuDelayXus(1);

        // Disable Key download port
        ScalerSetBit(P63_A0_DP_HDCP_CONTROL, ~_BIT0, 0x00);

        // Enable HDCP Sram clk
        ScalerSetBit(P63_97_HDCP_DUMMY_1, ~_BIT2, _BIT2);
        ScalerMcuDelayXus(1);
    }
}

//--------------------------------------------------
// Description  : DownLoad HDCP Key to SRAM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp14RxCipherDownLoadKeyToSram(WORD usLength, BYTE *pucReadArray)
{
    WORD usIndex = 0;

    for(usIndex = 0; usIndex < usLength; usIndex++)
    {
        ScalerSetByte(P63_A1_DP_HDCP_DOWNLOAD_PORT, pucReadArray[usIndex]);

        // Polling 1ms for Key Sram Write Done
        ScalerTimerPollingFlagProc(1, P63_A0_DP_HDCP_CONTROL, _BIT6, _TRUE);
    }
}

//--------------------------------------------------
// Description  : HDCP1.4 Cipher Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD ScalerHdcp14RxCipherProc(BYTE *pucAksv, BYTE *pucAn, bit bRepeater)
{
    BYTE ucTemp = 0x00;
    WORD usHdcp14R0 = 0;

    // Enable hdcp Block
    ScalerSetBit(P63_A0_DP_HDCP_CONTROL, ~_BIT7, _BIT7);

    for(ucTemp = 0; ucTemp < 5; ucTemp++)
    {
        // AKSV DPCD [0x68007 ~ 0x6800B]
        ScalerSetByte(P63_CD_HDCP_AKSV_4 + ucTemp, pucAksv[ucTemp]);
    }

    for(ucTemp = 0; ucTemp < 8; ucTemp++)
    {
        // An DPCD [0x6800C ~ 0x68013]
        ScalerSetByte(P63_D2_HDCP_AN_7 + ucTemp, pucAn[ucTemp]);
    }

    // Repeater bit
    ScalerSetBit(P63_DA_HDCP_REPEATER, ~_BIT0, bRepeater);

    // Calculate R0' by manual toggle HDCP 1.4 Module
    ScalerSetBit(P63_CC_HDCP_OTHER, ~_BIT7, _BIT7);

    // Delay Time us [200,x] Waiting for R0 Calculate Finish
    DELAY_XUS_EXINT(200);

    usHdcp14R0 = ((((WORD)ScalerGetByte(P63_DC_HDCP_R0_0)) << 8) | ScalerGetByte(P63_DB_HDCP_R0_1));

    return usHdcp14R0;
}

//--------------------------------------------------
// Description  : Load KSV FIFO to SHA-1 Input
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp14RxWriteShaInput(BYTE *pucInputArray, bit bIsFirst)
{
    // Reset SHA Block counter
    ScalerSetBit(P63_B3_SHA_CONTRL, ~(_BIT5 | _BIT3 | _BIT0), _BIT3);

    // Start to Write SHA-1 Transform Input
    ScalerSetBit(P63_B3_SHA_CONTRL, ~(_BIT5 | _BIT3 | _BIT0), 0x00);

    // Write SHA-1 Input Data, Total 512 bits
    for(BYTE ucLoopIndex = 0; ucLoopIndex < 16; ucLoopIndex++)
    {
        ScalerSetByte(P63_B4_SHA_DATA1, pucInputArray[ucLoopIndex * 4]);
        ScalerSetByte(P63_B5_SHA_DATA2, pucInputArray[1 + ucLoopIndex * 4]);
        ScalerSetByte(P63_B6_SHA_DATA3, pucInputArray[2 + ucLoopIndex * 4]);
        ScalerSetByte(P63_B7_SHA_DATA4, pucInputArray[3 + ucLoopIndex * 4]);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(P63_B3_SHA_CONTRL, ~(_BIT5 | _BIT0), _BIT0);

        // Polling 1ms for HDCP Sha Data Write Done
        if(ScalerTimerPollingFlagProc(1, P63_B3_SHA_CONTRL, _BIT5, _TRUE) == _TRUE)
        {
            ScalerSetBit(P63_B3_SHA_CONTRL, ~(_BIT5 | _BIT0), _BIT5);
        }
    }

    // Set First Run For SHA-1 Circuit
    ScalerSetBit(P63_B3_SHA_CONTRL, ~(_BIT5 | _BIT1 | _BIT0), ((bIsFirst == _TRUE) ? _BIT1 : 0x00));

    // Run SHA-1 Circuit
    ScalerSetBit(P63_B3_SHA_CONTRL, ~(_BIT5 | _BIT2 | _BIT0), _BIT2);

    ScalerTimerPollingFlagProc(5, P63_B3_SHA_CONTRL, _BIT4, _TRUE);

    // Disable First Run and Disable SHA-1 Circuit
    ScalerSetBit(P63_B3_SHA_CONTRL, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);
}
#endif

