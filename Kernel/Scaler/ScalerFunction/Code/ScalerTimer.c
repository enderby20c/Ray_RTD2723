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
// ID Code      : ScalerTimer.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Timer/ScalerTimer.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_INSTANT_TIMER_EVENT_0 == _ON)
// Timer0 Setting (T0 target ms)
WORD g_usTimer0MS;
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
// Timer1 Setting (T1 target ms)
WORD g_usTimer1MS;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Configures Timer Timeout Count (count up to target value then trigger int)
// Input Value  : timerID --> Timer ID
//                u32TargetValue --> target timeout value of timer/counter
// Output Value : None
//--------------------------------------------------
void ScalerTimerSetTargetValue(EnumCpuTimerID enumTimerID, DWORD ulTargetValue)
{
    DWORD ulTmp = Scaler32GetDWord(PA40012_40_TC0CR + (enumTimerID << 2));
    Scaler32SetDWord(PA40012_40_TC0CR + (enumTimerID << 2), (ulTmp & ~(_BIT31)));
    Scaler32SetDWord(PA40012_00_TC0TVR + (enumTimerID << 2), ulTargetValue);
    ScalerTimerAckINTFlag(enumTimerID);
    Scaler32SetDWord(PA40012_40_TC0CR + (enumTimerID << 2), ulTmp);
}

//--------------------------------------------------
// Description  : get current Timer Timeout configuration
// Input Value  : timerID --> Timer ID
// Output Value : target timeout value of timer/counter
//--------------------------------------------------
DWORD ScalerTimerGetTargetValue(EnumCpuTimerID enumTimerID)
{
    return Scaler32GetDWord(PA40012_00_TC0TVR + (enumTimerID << 2));
}

//--------------------------------------------------
// Description  : get current count value of timer/counter
// Input Value  : timerID --> Timer ID
// Output Value : current count value of timer/counter
//--------------------------------------------------
DWORD ScalerTimerGetCurrentValue(EnumCpuTimerID enumTimerID)
{
    return Scaler32GetDWord(PA40012_20_TC0CVR + (enumTimerID << 2));
}

//--------------------------------------------------
// Description  : Clear current count value of timer/counter to 0
// Input Value  : timerID --> Timer ID
// Output Value : None
//--------------------------------------------------
void ScalerTimerClearCurrentValue(EnumCpuTimerID enumTimerID)
{
    DWORD ulTmp = Scaler32GetDWord(PA40012_40_TC0CR + (enumTimerID << 2));
    Scaler32SetDWord(PA40012_40_TC0CR + (enumTimerID << 2), (ulTmp & ~(_BIT31)));
    ScalerTimerAckINTFlag(enumTimerID);
    Scaler32SetDWord(PA40012_40_TC0CR + (enumTimerID << 2), ulTmp);
}

//--------------------------------------------------
// Description  : Enable/Disable Timer/Counter
// Input Value  : timerID --> Timer ID
//                timerEnFlag --> 0:will disable and clear timer counter ; 1:enable and start timer/counter
// Output Value : None
//--------------------------------------------------
void ScalerTimerSetEnable(EnumCpuTimerID enumTimerID, bit bTimerEnFlag)
{
    Scaler32SetBit(PA40012_40_TC0CR + (enumTimerID << 2), ~(_BIT31), ((DWORD)(bTimerEnFlag) << 31));
}

//--------------------------------------------------
// Description  : set timer use as a Timer or a Counter
// Input Value  : timerID --> Timer ID
//                timerWorkMode --> 0:as counter ; 1:as timer
// Output Value : None
//--------------------------------------------------
void ScalerTimerSetWorkMode(EnumCpuTimerID enumTimerID, EnumCpuTIMERxMode enumTimerWorkMode)
{
    Scaler32SetBit(PA40012_40_TC0CR + (enumTimerID << 2), ~_TIMER_X_TIMER_MODE, enumTimerWorkMode);
}

//--------------------------------------------------
// Description  : pause or continue timer/counter count
// Input Value  : timerID --> Timer ID
//                timerPauseFlag --> 0:continue ; 1:pause
// Output Value : None
//--------------------------------------------------
void ScalerTimerSetPause(EnumCpuTimerID enumTimerID, EnumCpuTIMERxPause enumTimerPauseFlag)
{
    Scaler32SetBit(PA40012_40_TC0CR + (enumTimerID << 2), ~_TIMER_X_PAUSE, enumTimerPauseFlag);
}

//--------------------------------------------------
// Description  : Enable/Disable Timer/Counter
// Input Value  : timerID --> Timer ID
// Output Value : timerEnFlag     --> 0:will disable and clear timer counter ; 1:enable and start timer/counter
//--------------------------------------------------
bit ScalerTimerGetEnable(EnumCpuTimerID enumTimerID)
{
    if((Scaler32GetDWord(PA40012_40_TC0CR + (enumTimerID << 2)) & _BIT31) != 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : get timer use as a Timer or a Counter
// Input Value  : timerID --> Timer ID
// Output Value : timerWorkMode --> 0:as counter ; 1:as timer
//--------------------------------------------------
DWORD ScalerTimerGetWorkMode(EnumCpuTimerID enumTimerID)
{
    return (Scaler32GetDWord(PA40012_40_TC0CR + (enumTimerID << 2)) & _TIMER_X_TIMER_MODE);
}

//--------------------------------------------------
// Description  : get pause or continue timer/counter count
// Input Value  : timerID --> Timer ID
// Output Value : timerPauseFlag --> 0:continue ; other:pause
//--------------------------------------------------
DWORD ScalerTimerGetPause(EnumCpuTimerID enumTimerID)
{
    return (Scaler32GetDWord(PA40012_40_TC0CR + (enumTimerID << 2)) & _TIMER_X_PAUSE);
}

//--------------------------------------------------
// Description  : enable/disable timer/counter Interrupt
// Input Value  : timerID --> Timer ID
//                timerIntEnFlag --> 0:disable INT ; 1:enable INT
// Output Value : None
//--------------------------------------------------
void ScalerTimerSetINTEn(EnumCpuTimerID enumTimerID, EnumCpuTIMERxIntEN enumTimerIntEnFlag)
{
    Scaler32SetDWord(PA40012_60_TC0ICR + (enumTimerID << 2), enumTimerIntEnFlag);
}

//--------------------------------------------------
// Description  : get timer/counter NMI flag
// Input Value  : timerID --> Timer ID
// Output Value : NMI flag of timer/counter(0:not happened ; 1:happened)
//--------------------------------------------------
bit ScalerTimerGet_NMI_Flag(EnumCpuTimerID enumTimerID)
{
    return ((Scaler32GetDWord(PA40012_E8_UMSK_ISR) & (1UL << enumTimerID)) != 0);
}

//--------------------------------------------------
// Description  : Ack timer/counter NMI flag
// Input Value  : timerID --> Timer ID
// Output Value : None
//--------------------------------------------------
void ScalerTimerAck_NMI_Flag(EnumCpuTimerID enumTimerID)
{
    Scaler32SetBit(PA40012_E8_UMSK_ISR, ~(1UL << enumTimerID), (1UL << enumTimerID));

    // avoiding RBUS delay cause repeat entering INT
    ASM_DSB();
}

//--------------------------------------------------
// Description  : get timer/counter INT flag
// Input Value  : timerID --> Timer ID
// Output Value : INT flag of timer/counter(0:not happened ; 1:happened)
//--------------------------------------------------
bit ScalerTimerGetINTFlag(EnumCpuTimerID enumTimerID)
{
    return ((Scaler32GetDWord(PA40012_EC_ISR) & (1UL << enumTimerID)) != 0);
}

//--------------------------------------------------
// Description  : Ack timer/counter INT flag
// Input Value  : timerID --> Timer ID
// Output Value : None
//--------------------------------------------------
void ScalerTimerAckINTFlag(EnumCpuTimerID enumTimerID)
{
    Scaler32SetDWord(PA40012_EC_ISR, (1UL << enumTimerID));

    // avoiding RBUS delay cause repeat entering INT
    ASM_DSB();
}

//--------------------------------------------------
// Description  : Init TmierX to use
// Input Value  : timerID --> Timer ID
// Output Value : None
//--------------------------------------------------
DWORD ScalerTimerInitTimer(EnumCpuTimerID enumTimerID, EnumCpuTIMERxMode enumTimerWorkMode, DWORD ulTargetCountValue, bit bTimerEnFlag, EnumCpuTIMERxIntEN enumTimerIntEnFlag)
{
    ScalerTimerSetWorkMode(enumTimerID, enumTimerWorkMode);
    ScalerTimerSetTargetValue(enumTimerID, ulTargetCountValue);
    ScalerTimerSetEnable(enumTimerID, bTimerEnFlag);
    ScalerTimerSetINTEn(enumTimerID, enumTimerIntEnFlag);
    return 0;
}

//--------------------------------------------------
// Description  : Set Time Count for Timer0/1/2
// Input Value  : OperationMode --> Initial/Normal/Saving
// Output Value : None
//--------------------------------------------------
void ScalerTimerSetTimerCount(EnumScalerTimerOperationMode enumOperationMode)
{
    DWORD ulSystick32US = _SYSTICK_TIMER_US;

    if(enumOperationMode == _TIMER_OPERATION_POWER_IDLE_MODE)
    {
        ulSystick32US = ((DWORD)_IDLE_TIME_MAX * 1000);
    }

    // Start 1ms/250us constant Timer
    // Configure the SysTick to have interrupt in ulSystickMS ms time basis
    ScalerCpuHalSystickConfig(ulSystick32US);
    SET_INTERRUPT_ENABLE_STATUS(_INT_TIMER_2, _ENABLE);

    // Clear timer2 notify bit
    SET_TIMER2_ALL_INT_STATUS(_FALSE);

#if((_INSTANT_TIMER_EVENT_0 == _ON) || (_INSTANT_TIMER_EVENT_1 == _ON))
    if(enumOperationMode != _TIMER_OPERATION_POWER_IDLE_MODE)
    {
#if(_INSTANT_TIMER_EVENT_0 == _ON)
        if(ScalerTimerGetEnable(_CPU_TIMER_0) == _ON)
        {
            // Update timing setting
            ScalerTimer0SetTimerCount(g_usTimer0MS);
        }
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
        if(ScalerTimerGetEnable(_CPU_TIMER_1) == _ON)
        {
            // Update timing setting
            ScalerTimer1SetTimerCount(g_usTimer1MS);
        }
#endif
    }
#endif
}

#if(_INSTANT_TIMER_EVENT_0 == _ON)
//--------------------------------------------------
// Description  : Timer0 Set Timer Counter
// Input Value  : ucTimerMs --> Counter in ms (1~65535ms)
//                Stops Timer0 if ucTimerMs = 0 or _TIMER_OFF
// Output Value : None
//--------------------------------------------------
void ScalerTimer0SetTimerCount(WORD usTimerMs)
{
    g_usTimer0MS = usTimerMs;
    if(usTimerMs == _TIMER_OFF)
    {
        // Stop Timer 0
        ScalerTimerSetEnable(_CPU_TIMER_0, _OFF);
    }
    else
    {
        DWORD ulT0TargetCnt = (GET_TIMER32_1MS_TICK_COUNT() * ((DWORD)usTimerMs));
        ScalerTimerInitTimer(_CPU_TIMER_0, _TIMER_X_TIMER_MODE, ulT0TargetCnt, _ENABLE, _TIMER_X_INT_ENABLE);
        SET_INTERRUPT_ENABLE_STATUS(_INT_TIMER_0, _ENABLE);
    }
}
#endif // End of #if(_INSTANT_TIMER_EVENT_0 == _ON)

#if(_INSTANT_TIMER_EVENT_1 == _ON)
//--------------------------------------------------
// Description  : Timer1 Set Timer Counter
// Input Value  : ucTimerMs --> Counter in ms (1~65535ms)
//                Stops Timer0 if ucTimerMs = 0 or _TIMER_OFF
// Output Value : None
//--------------------------------------------------
void ScalerTimer1SetTimerCount(WORD usTimerMs)
{
    g_usTimer1MS = usTimerMs;
    if(usTimerMs == _TIMER_OFF)
    {
        // Stop Timer 0
        ScalerTimerSetEnable(_CPU_TIMER_1, _OFF);
    }
    else
    {
        DWORD ulT0TargetCnt = (GET_TIMER32_1MS_TICK_COUNT() * ((DWORD)usTimerMs));
        ScalerTimerInitTimer(_CPU_TIMER_1, _TIMER_X_TIMER_MODE, ulT0TargetCnt, _ENABLE, _TIMER_X_INT_ENABLE);
        SET_INTERRUPT_ENABLE_STATUS(_INT_TIMER_1, _ENABLE);
    }
}
#endif // End of #if(_INSTANT_TIMER_EVENT_1 == _ON)

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerTimerInitial(void)
{
    DWORD ulTickCnt1MS = GET_TIMER32_1MS_TICK_COUNT();
    ScalerTimerInitTimer(_CPU_TIMER_0, _TIMER_X_TIMER_MODE, ulTickCnt1MS, _TIMER_X_DISABLE, _TIMER_X_INT_DISABLE);
    ScalerTimerInitTimer(_CPU_TIMER_1, _TIMER_X_TIMER_MODE, ulTickCnt1MS, _TIMER_X_DISABLE, _TIMER_X_INT_DISABLE);

    // Load Timer2 Count Value
    ScalerTimerSetTimerCount(_TIMER_OPERATION_INITIAL_MODE);
}

//--------------------------------------------------
// Description  : Watch Dog Timer Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDInitial(void)
{
    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_2, _ENABLE);
    ScalerTimerInitTimer(_CPU_TIMER_2, _TIMER_X_COUNTER_MODE, ((DWORD)_TIMER32_MAX_COUNT), _DISABLE, _TIMER_X_INT_ENABLE);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerTimerSetRunStatus(EnumTimerId enumTimerId, bit bStatus)
{
    switch(enumTimerId)
    {
        case _TIMER_0:
            ScalerTimerSetEnable(_CPU_TIMER_0, bStatus);
            break;

        case _TIMER_1:
            ScalerTimerSetEnable(_CPU_TIMER_1, bStatus);
            break;

        case _TIMER_2:
            // Constant 1ms timer
#if(_CPU32_IP == _CPU32_IP_RX3081)
            ScalerTimerSetEnable(_CPU_TIMER_3, bStatus);
#endif
            break;

        default:
            break;
    }
}

