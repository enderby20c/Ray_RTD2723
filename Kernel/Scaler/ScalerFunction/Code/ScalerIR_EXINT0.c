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
// ID Code      : ScalerIR_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_IR_EXINT0__

#include "ScalerFunctionInclude.h"
#include "IR/ScalerIR.h"

#ifdef __C51__
#pragma REGISTERBANK(1)
#endif


#if(_IR_SUPPORT == _IR_HW_SUPPORT)
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
// Description  : IR interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIRHWModeIntHandler_EXINT0(void)
{
    BYTE ucTemp = 0;

    if((ScalerGetBit_EXINT(P23_B2_IR_CR2, _BIT2) == _BIT2) && (ScalerGetBit_EXINT(P23_BB_IR_SR3, _BIT0) != 0x00))
    {
        ScalerSetBit_EXINT(P23_BB_IR_SR3, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        // when detect repeat signal, repeat bit and data bit will all be setted
        if(ScalerGetBit_EXINT(P23_BB_IR_SR3, _BIT1) == _BIT1)
        {
            SET_IR_NEC_STATUS(_NEC_IR_REPEAT);
        }
        else // when detect only data(address + cmd), only data bit will be setted
        {
            SET_IR_NEC_STATUS(_NEC_IR_DATA);
        }

        ScalerSetBit_EXINT(P23_BB_IR_SR3, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(ScalerGetBit_EXINT(P23_BB_IR_SR3, (_BIT6 | _BIT4)) != 0x00)
        {
            // Read out unused code to avoid buffer pointer in disorder
            ucTemp = ScalerGetByte_EXINT(P23_B4_IR_RP0);
            ucTemp += ScalerGetByte_EXINT(P23_B5_IR_RP1);
            ucTemp += ScalerGetByte_EXINT(P23_B6_IR_RP2);
            ucTemp += ScalerGetByte_EXINT(P23_B7_IR_RP3);
            ucTemp += ScalerGetByte_EXINT(P23_DC_IR_RP2_0);
            ucTemp += ScalerGetByte_EXINT(P23_DD_IR_RP2_1);
            ucTemp += ScalerGetByte_EXINT(P23_DE_IR_RP2_2);
            ucTemp += ScalerGetByte_EXINT(P23_DF_IR_RP2_3);

            // Reset IR
            ScalerSetBit_EXINT(P23_B0_IR_CR0, ~(_BIT7), _BIT7);

            CLR_IR_HW_RECEIVED();
        }
        else
        {
            // Get code
            g_pucIRCode[0] = ScalerGetByte_EXINT(P23_B4_IR_RP0);
            g_pucIRCode[1] = ScalerGetByte_EXINT(P23_B5_IR_RP1);
            g_pucIRCode[2] = ScalerGetByte_EXINT(P23_B6_IR_RP2);
            g_pucIRCode[3] = ScalerGetByte_EXINT(P23_B7_IR_RP3);
            g_pucIRCode[4] = ScalerGetByte_EXINT(P23_DC_IR_RP2_0);
            g_pucIRCode[5] = ScalerGetByte_EXINT(P23_DD_IR_RP2_1);
            g_pucIRCode[6] = ScalerGetByte_EXINT(P23_DE_IR_RP2_2);
            g_pucIRCode[7] = ScalerGetByte_EXINT(P23_DF_IR_RP2_3);

            // Clear flag
            ScalerSetByte_EXINT(P23_BB_IR_SR3, 0x7F);

            SET_IR_HW_RECEIVED();
        }
    }
}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

