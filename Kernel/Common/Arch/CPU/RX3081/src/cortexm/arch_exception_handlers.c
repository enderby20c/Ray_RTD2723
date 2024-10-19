// ----------------------------------------------------------------------------
#include "ScalerFunctionInclude.h"
#include "ExceptionHandlers.h"
#include <string.h>



// ----------------------------------------------------------------------------
__attribute__((noreturn, weak))
extern void _start(void);

#ifndef CPU32_BOOTLOADER
extern void SysIntPendSVCallback(void);
extern void SysIntSystickCallback(void);
#endif

// ----------------------------------------------------------------------------
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
// ----------------------------------------------------------------------------
__attribute__((section(".after_vectors"), weak, noreturn))
void Reset_Handler(void)
{
    // early init already done in BootResetVector.S(imem/stack...etc)
    // current IEc is 0(Global Interrupt is disabled)

#if(_SCPU_SUPPORT == _ON)
    // Kernel Start to Execute
    // 0xA3000004[2]:Kernel FW executed
    Scaler32SetBit(PA30000_04_GLOBAL_CTRL_DUMMY0, ~(DWORD)(_BIT2 | _BIT1 | _BIT0) , (_BIT2 | _BIT1 | _BIT0));
#endif

    // Switch CPU Freq to PLL source
    ScalerMcu1usDelayCalc(_EXT_XTAL_CLK);
    ScalerGlobalCtrlSetSys32ClkSrc(_EXT_XTAL_CLK);

    _start();

    // will never be executed
    __builtin_unreachable();

}


// ----------------------------------------------------------------------------

/**
  * @brief  ARM InCore Pending System Service INT callback.
  * @param  None
  * @retval None
  */
__attribute__((section(".itcm_section"), weak))
void PendSV_Handler(void)
{
#ifndef CPU32_BOOTLOADER
    SysIntPendSVCallback();
#endif
}

/**
  * @brief  ARM InCore SysTick Constant(1ms) Timer INT callback.
  * @param  None
  * @retval None
  */
__attribute__((section(".itcm_section"), weak))
void SysTick_Handler(void)
{
    if(ScalerTimerGetINTFlag(_CPU_TIMER_3) != 0)
    {
        // Ack Timer0 INT flag
        ScalerTimerAckINTFlag(_CPU_TIMER_3);

#if defined(USE_HAL_DRIVER)
        ScalerSysTickIncTick();
#ifndef CPU32_BOOTLOADER
        SysIntSystickCallback();
#endif
#endif
    }
}

// ----------------------------------------------------------------------------
