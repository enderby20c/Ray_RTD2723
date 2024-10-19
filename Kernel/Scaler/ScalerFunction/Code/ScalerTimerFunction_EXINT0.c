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
// ID Code      : ScalerTimerFunction_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TIMERFUNCTION_EXINT0__

#include "ScalerFunctionInclude.h"
#include "TimerFunction/ScalerTimerFunction.h"




//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_RECORD_TIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Recorded Time
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerTimerGetRecordTimer_EXINT0(void)
{
    WORD usRecordTime = 0;
    LOAD_TIMER_COUNTER(&usRecordTime);

    if(g_usTimerRecordStartTime == usRecordTime)
    {
        usRecordTime = 0x00;
    }
    else if(g_usTimerRecordStartTime < usRecordTime)
    {
        usRecordTime = usRecordTime - g_usTimerRecordStartTime;
    }
    else
    {
        usRecordTime = (0xFFFF - g_usTimerRecordStartTime) + 1 + usRecordTime;
    }

    return (BYTE)usRecordTime;
}
#endif

