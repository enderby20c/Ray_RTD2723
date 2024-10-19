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
// ID Code      : RL6952_Series_DpMacStreamRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DP_MAC_STREAM_RX1__

#include "ScalerFunctionInclude.h"
#include "DpMacStreamRx1/ScalerDpMacStreamRx1.h"

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX1_SUPPORT == _ON))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable DP BS Miss Detect Start
// Input Value  : _ENABLE/ DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetBsMissDetectStart(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Clear BS Detect Flag
        ScalerSetBit(_REG_DP_MAC_STREAM_RX1_BS_MISS_CTRL, ~_BIT6, _BIT6);

        // BS Detect Enable Setting
        ScalerSetBit(_REG_DP_MAC_STREAM_RX1_BS_MISS_CTRL, ~(_BIT6 | _BIT4), _BIT4);
    }
    else
    {
        // BS Detect Disable Setting
        ScalerSetBit(_REG_DP_MAC_STREAM_RX1_BS_MISS_CTRL, ~(_BIT6 | _BIT4), 0x00);

        // Clear BS Detect Flag
        ScalerSetBit(_REG_DP_MAC_STREAM_RX1_BS_MISS_CTRL, ~_BIT6, _BIT6);
    }
}

//--------------------------------------------------
// Description  : Set Bs Miss Detect Period
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpMacStreamRx1SetBsMissDetectPeriod(StructDpInfo *pstDpInfo)
{
    WORD usBsMissDetectPeriodCount = 0;

    usBsMissDetectPeriodCount = ScalerDpMacStreamRxBsMissDetectPeriodCalculate(pstDpInfo);

    // Set Tracking HTT
    ScalerSetByte(PB8_B9_BS_MISS_DETECT_PERIOD_MSB, HIBYTE(usBsMissDetectPeriodCount));
    ScalerSetByte(PB8_BA_BS_MISS_DETECT_PERIOD_LSB, LOBYTE(usBsMissDetectPeriodCount));
}
#endif
#endif
