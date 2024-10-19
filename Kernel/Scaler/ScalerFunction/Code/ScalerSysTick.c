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
// ID Code      : ScalerSysTick.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "SysTick/ScalerSysTick.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile DWORD g_ulSysTickTimerCounter; // constant timer interrupt counter(maybe 1ms or 250us per tick)
volatile DWORD g_ulSysTickTargetUS;
volatile BYTE g_ucSysTickTimerFlag;

#if(_SCPU_SUPPORT == _ON)
volatile BYTE g_ucSysTickScpuTimerFlag;
#endif
#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
volatile DWORD g_ulSysTickScpuTargetUS;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : This function configures the source of the time base.
//                 The time source is configured  to have 1ms time base with a dedicated
//                 Tick interrupt priority.
//          NOTE: This function is called  automatically at the beginning of program after
//                reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig().
//          NOTE: In the default implementation, SysTick timer is the source of time base.
//                It is used to generate interrupts at regular time intervals.
//                Care must be taken if HAL_Delay() is called from a peripheral ISR process,
//                The the SysTick interrupt must have higher priority (numerically lower)
//                than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
// Input Value  : TickPriority: Tick interrupt priority.
// Output Value : HAL status
//--------------------------------------------------
void ScalerSysTickInit(DWORD ulTickPriority)
{
    // Configure the SysTick to have interrupt in 1ms time basis
    ScalerCpuHalSystickConfig(_SYSTICK_TIMER_US);

    // Configure the SysTick IRQ priority
    ScalerCpuHalSetPriority(_IRQN_SYSTICK, ulTickPriority);

    ScalerSysTickAckFlag();
}

//--------------------------------------------------
// Description  : Increase Constant Timer Interrupt Counter (maybe 1ms or 250us per rick)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSysTickIncTick(void)
{
    g_ulSysTickTimerCounter++;
    g_ucSysTickTimerFlag = 1;
#if(_SCPU_SUPPORT == _ON)
    g_ucSysTickScpuTimerFlag = 1;
#endif
}

//--------------------------------------------------
// Description  : Get Constant Timer Interrupt Counter Value
// Input Value  : None
// Output Value : tick value
//--------------------------------------------------
DWORD ScalerSysTickGetTick(void)
{
    return g_ulSysTickTimerCounter;
}

//--------------------------------------------------
// Description  : Ack g_ulSysTickTimerCounter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSysTickAckFlag(void)
{
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    g_ucSysTickTimerFlag = 0;
#else
#if(_SCPU_SUPPORT == _ON)
    g_ucSysTickScpuTimerFlag = 0;
#endif
#endif
}

//--------------------------------------------------
// Description  : Suspend Tick increment.
//          NOTE: In the default implementation , SysTick timer is the source of time base. It is
//                used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
//                is called, the SysTick interrupt will be disabled and so Tick increment
//                is suspended.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSysTickSuspendTick(void)
{
    // Disable SysTick Interrupt
    SYSTICK_DISABLE_INTERRUPT();
}

//--------------------------------------------------
// Description  : Resume Tick increment.
//          NOTE: In the default implementation , SysTick timer is the source of time base. It is
//                used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
//                is called, the SysTick interrupt will be enabled and so Tick increment
//                is resumed.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSysTickResumeTick(void)
{
    // Enable SysTick Interrupt
    SYSTICK_ENABLE_INTERRUPT();
}

//--------------------------------------------------
// Description  : Get SysTick timer current Value
// Input Value  : None
// Output Value : SysTick timer current Value
//--------------------------------------------------
DWORD ScalerSysTickGetCurrentValue(void)
{
    // SysTick timer current Value
    return SYSTICK_GET_CURRENT_VALUE();
}

//--------------------------------------------------
// Description  : Get SysTick timer reload Value
// Input Value  : None
// Output Value : SysTick timer reload Value
//--------------------------------------------------
DWORD ScalerSysTickGetReloadValue(void)
{
    // SysTick timer reload Value
    return SYSTICK_GET_RELOAD_VALUE();
}

