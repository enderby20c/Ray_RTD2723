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
// ID Code      : ScalerIR.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_IR__

#include "ScalerFunctionInclude.h"
#include "IR/ScalerIR.h"


#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile bit g_bIRReceived = 0;
volatile BYTE g_pucIRCode[8];
EnumNECIRStatus g_enumIRNECStatus = _NEC_IR_NONE;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : IRDA Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIRHWModeInitial(void)
{
    // Sample clock divider
    ScalerSetByte(P23_AA_IR_SF2, HIBYTE(_IR_HW_XTAL_SAMPLE_CLK_DIV));
    ScalerSetByte(P23_AB_IR_SF3, LOBYTE(_IR_HW_XTAL_SAMPLE_CLK_DIV));


    // Clear interrupt flag
    ScalerSetBit(P23_BB_IR_SR3, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable HW interrupt
    ScalerSetBit(P23_B2_IR_CR2, ~_BIT2, _BIT2);

    // _BIT0: Enable IR
    ScalerSetBit(P23_B2_IR_CR2, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Set HW IR Table
// Input Value  : User Table
// Output Value : None
//--------------------------------------------------
void ScalerIRHWModeDecoder(BYTE *pucIRTableArray, BYTE ucBankNum)
{
    // P23_A0_IR_PSR0 ~ P23_A9_IR_SF1
    ScalerBurstWrite(pucIRTableArray + _IR_TABLE_1_START, _IR_TABLE_1_LENGTH, ucBankNum, P23_A0_IR_PSR0, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);

    // P23_AC_IR_DPIR0 ~ P23_B3_IR_CR3
    ScalerBurstWrite(pucIRTableArray + _IR_TABLE_2_START, _IR_TABLE_2_LENGTH, ucBankNum, P23_AE_IR_DPIR2, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);

    // P23_D0_IR_PSR_UP0 ~ P23_D7_IR_PER_UP3
    ScalerBurstWrite(pucIRTableArray + _IR_TABLE_3_START, _IR_TABLE_3_LENGTH, ucBankNum, P23_D0_IR_PSR_UP0, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);

    // P23_DA_IR_CTRL_RC62 ~ P23_DB_IR_CTRL_RC63
    ScalerBurstWrite(pucIRTableArray + _IR_TABLE_4_START, _IR_TABLE_3_LENGTH, ucBankNum, P23_DA_IR_CTRL_RC62, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);
}

//--------------------------------------------------
// Description  : Read the IR raw data in fifo
// Input Value  : None
// Output Value : Data ready or not
//--------------------------------------------------
bit ScalerIRHWModeGetData(BYTE *pucBuffer)
{
    // Wait IR Reset
    ScalerTimerPollingFlagProc(100, P23_B0_IR_CR0, _BIT7, _FALSE);

    if(GET_IR_HW_RECEIVED() == _TRUE)
    {
        pucBuffer[0] = g_pucIRCode[0];
        pucBuffer[1] = g_pucIRCode[1];
        pucBuffer[2] = g_pucIRCode[2];
        pucBuffer[3] = g_pucIRCode[3];
        pucBuffer[4] = g_pucIRCode[4];
        pucBuffer[5] = g_pucIRCode[5];
        pucBuffer[6] = g_pucIRCode[6];
        pucBuffer[7] = g_pucIRCode[7];

        CLR_IR_HW_RECEIVED();

#if(_DEBUG_MESSAGE_IR == _ON)
        DebugMessageIR("IR0", g_pucIRCode[0]);
        DebugMessageIR("IR1", g_pucIRCode[1]);
        DebugMessageIR("IR2", g_pucIRCode[2]);
        DebugMessageIR("IR3", g_pucIRCode[3]);
#endif // End of #if(_DEBUG_MESSAGE_IR == _ON)

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : IRDA clock divider switch
// Input Value  : Clock --> _M2PLL_CLK/_EXT_XTAL_CLK(_IOSC_CLK)
// Output Value : None
//--------------------------------------------------
void ScalerIRHWModeClockSel(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // HW Sample clock divider
        ScalerSetByte(P23_AA_IR_SF2, HIBYTE(_IR_HW_XTAL_SAMPLE_CLK_DIV));
        ScalerSetByte(P23_AB_IR_SF3, LOBYTE(_IR_HW_XTAL_SAMPLE_CLK_DIV));
    }
    else if(enumClock == _IOSC_CLK)
    {
        // HW Sample clock divider
        ScalerSetByte(P23_AA_IR_SF2, HIBYTE(_IR_HW_IOSC_SAMPLE_CLK_DIV));
        ScalerSetByte(P23_AB_IR_SF3, LOBYTE(_IR_HW_IOSC_SAMPLE_CLK_DIV));
    }
}

//--------------------------------------------------
// Description  : Get NEC IR Status
// Input Value  : None
// Output Value : _NEC_IR_REPEAT or _NEC_IR_DATA
//--------------------------------------------------
EnumNECIRStatus ScalerIRHWModeGetNECIRStatus(void)
{
    return GET_IR_NEC_STATUS();
}

//--------------------------------------------------
// Description  : Set NEC IR Initial Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIRHWModeClrNECStatus(void)
{
    CLR_IR_NEC_STATUS();
}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)
