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
// ID Code      : ScalerIOSC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_IOSC__

#include "ScalerFunctionInclude.h"
#include "IOSC/ScalerIOSC.h"





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
// Description  : Internal Oscillator Triming.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOSCTrimming(void)
{
    SBYTE chTempInx = 0;
    BYTE pucData[4];

    // Disable auto trimming.
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT7, 0x00);

    // Trim Resolution select, Fosc=counter * Fxtal / 1000
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT5, 0x00);

    // Wait time for Internal OSC Stable->15*2^10 Tref
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT4, _BIT4);

    // Wait time for trimming->4*2^10 Tref
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

#if(_EXT_XTAL == _XTAL14318K)
#if(_HW_INTERNAL_OSC_XTAL == _IOSC27000K)
    // Trimming comparason target 0x75D --> 27M
    ScalerSetByte(P6_A1_OSC_TRIM_CTRL1, 0x5D);
    ScalerSetBit(P6_A5_EMB_BGRES, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);

#elif(_HW_INTERNAL_OSC_XTAL == _IOSC28000K)
    // Trimming comparason target 0x7A4 --> 28M
    ScalerSetByte(P6_A1_OSC_TRIM_CTRL1, 0xA4);
    ScalerSetBit(P6_A5_EMB_BGRES, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
#endif

#elif(_EXT_XTAL == _XTAL27000K)

#if(_HW_INTERNAL_OSC_XTAL == _IOSC27000K)
    // Trimming comparason target 1000(0x3E8) --> 27M
    ScalerSetByte(P6_A1_OSC_TRIM_CTRL1, 0xE8);
    ScalerSetBit(P6_A5_EMB_BGRES, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x03);

#elif(_HW_INTERNAL_OSC_XTAL == _IOSC28000K)
    // Trimming comparason target 1037(0x40D) --> 28M
    ScalerSetByte(P6_A1_OSC_TRIM_CTRL1, 0x0D);
    ScalerSetBit(P6_A5_EMB_BGRES, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);
#endif
#endif

    // Switch to hardware trimming result.
    ScalerSetBit(P6_A2_OSC_TRIM_CTRL2, ~_BIT7, 0x00);

#if(_HW_IOSC_GEN == _IOSC_GEN_0)
    // Thermal compensation factor, 11 for the best
    ScalerSetBit(P6_A6_EMB_BGRES1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
#endif

    // Enable trimming
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT7, _BIT7);

    //-------Use manual mode go back recheck best step start --------
    // Wait for auto trimming stop, time-consuming ~= 3.36ms
    if(ScalerTimerPollingFlagProc(10, P6_A0_OSC_TRIM_CTRL0, _BIT6, _TRUE) == _FALSE)
    {
        return;
    }

#if(_HW_IOSC_GEN == _IOSC_GEN_0)
    // Back up final result of auto trimming
    pucData[0] = (ScalerGetBit(P6_A2_OSC_TRIM_CTRL2, (_BIT5 | _BIT4 | _BIT3)) >> 3) | (ScalerGetBit(P6_A2_OSC_TRIM_CTRL2, (_BIT2 | _BIT1 | _BIT0)) << 3);
    pucData[3] = ((pucData[0] & 0x38) >> 3) | ((pucData[0] & 0x07) << 3);
#elif(_HW_IOSC_GEN == _IOSC_GEN_1)
    // Back up final result of auto trimming
    pucData[0] = (ScalerGetBit(P6_A7_OSC_TRIM_CTRL3, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
    pucData[3] = pucData[0];
#endif

    // Get target iosc cycle counter
    PDATA_WORD(5) = (ScalerGetBit(P6_A5_EMB_BGRES, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | ScalerGetByte(P6_A1_OSC_TRIM_CTRL1);

    // Initial variable
    PDATA_WORD(7) = 0xFFF;

    // Change to manual trimming mode
    ScalerSetBit(P6_A3_EMBEDDED_OSC_CTRL, ~_BIT6, 0x00);
    ScalerSetBit(P6_A2_OSC_TRIM_CTRL2, ~_BIT7, _BIT7);

    for(chTempInx = -1; chTempInx < 2; chTempInx++)
    {
#if(_HW_IOSC_GEN == _IOSC_GEN_0)
        if(((pucData[0] == 0x00) && (chTempInx == -1)) || ((pucData[0] == 0x3F) && (chTempInx == 1)))
#elif(_HW_IOSC_GEN == _IOSC_GEN_1)
        if(((pucData[0] == 0x00) && (chTempInx == -1)) || ((pucData[0] == 0x7F) && (chTempInx == 1)))
#endif
        {
            continue;
        }
        pucData[1] = pucData[0] + chTempInx;

#if(_HW_IOSC_GEN == _IOSC_GEN_0)
        pucData[2] = ((pucData[1] & 0x38) >> 3) | ((pucData[1] & 0x07) << 3);

        // Apply trimming step
        ScalerSetBit(P6_A3_EMBEDDED_OSC_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pucData[2] & 0x3F);
#elif(_HW_IOSC_GEN == _IOSC_GEN_1)
        pucData[2] = pucData[1];

        // Apply trimming step
        ScalerSetBit(P6_A6_EMB_BGRES1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pucData[2] & 0x7F);
#endif

        // Restart trimming
        ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT7, 0x00);
        ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT7, _BIT7);

        // Polling trimming finished, time-cunsuming ~= 440us
        ScalerTimerPollingFlagProc(10, P6_A0_OSC_TRIM_CTRL0, _BIT6, _TRUE);

        // Get iosc cycle counter in current step
        PDATA_WORD(6) = (ScalerGetBit(P6_A5_EMB_BGRES, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | ScalerGetByte(P6_A4_OSC_TRIM_CNT);

        // Record minimum step
        if(ABSDWORD(PDATA_WORD(6), PDATA_WORD(5)) < PDATA_WORD(7))
        {
            PDATA_WORD(7) = ABSDWORD(PDATA_WORD(6), PDATA_WORD(5));
            pucData[3] = pucData[2];
        }
    }
#if(_HW_IOSC_GEN == _IOSC_GEN_0)
    // Apply the best trimming step
    ScalerSetBit(P6_A3_EMBEDDED_OSC_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pucData[3] & 0x3F);
    //-------Use manual mode go back recheck best step end , total time-consuming ~= 5.36ms ----------
#elif(_HW_IOSC_GEN == _IOSC_GEN_1)
    // Apply the best trimming step
    ScalerSetBit(P6_A6_EMB_BGRES1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pucData[3] & 0x7F);
    //-------Use manual mode go back recheck best step end , total time-consuming ~= 5.36ms ----------
#endif
}
