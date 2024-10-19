// ----------------------------------------------------------------------------
#include "ScalerFunctionInclude.h"
#include "ExceptionHandlers.h"
#include <string.h>

// ----------------------------------------------------------------------------
__attribute__((section(".after_vectors")))
extern void SysIntDefaultHandler(void);

__attribute__((section(".after_vectors"), noreturn))
extern void _start(void);

#ifndef CPU32_BOOTLOADER
extern void SysIntMEI_IRQHandler(void);
extern void SysIntPendSVCallback(void);
extern void SysIntSystickCallback(void);
#endif

// ----------------------------------------------------------------------------
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
// ----------------------------------------------------------------------------

extern unsigned int _estack;

#ifdef CPU32_BOOTLOADER
// The DEBUG version is not naked, but has a proper stack frame, (Note: has "push" instruction in begin)
// to allow setting breakpoints at Reset_Handler.
// FOR TR9 BOOTLOADER FW
__attribute__((section(".reset_vectors"), noreturn))
void Reset_Handler(void)
{
    // Forece Reset Machine Trap-Vector Base-Address Register to Default Value(0: All exceptions set pc to BASE)
    __set_MTVEC((uint32_t)SysIntDefaultHandler, 0);
    ASM_DSB();

    // Disable All INT
    __disable_irq();

    // Set INT Priority : MEI > MSI > MTI > CLI[0] > CLI[1] > ...
    __csr_write(0x7C5, 0);

    // Disable TR9 Internal Timer Clk
    Scaler32SetBit(PA30000_00_CPU1_CLK_DIV, ~_BIT18, 0);

    // Clear MSIP/SW_INT0/SW_INT1 Pending Flag
    CLEAR_SYSCALL();
    CLEAR_SW_INT0();
    CLEAR_SW_INT1();

    // Switch CPU Freq to PLL source
    ScalerMcu1usDelayCalc(_M2PLL_CLK);
    // Switch CPU Freq to PLL source(Already done in Reset_Handler)
    ScalerGlobalCtrlSetSys32ClkSrc(_M2PLL_CLK);

    //Init MPU0 for I/DCache and MPU1 for DDR Protect region
#ifdef CPU32_BOOTLOADER
#if (__MPU_PRESENT == 1)
    ScalerCpuHalSetupMPUs();
#endif
#endif
    _start();

    //will never be executed
    __builtin_unreachable();
}

#else

// The DEBUG version is not naked, but has a proper stack frame, (Note: has "push" instruction in begin)
// to allow setting breakpoints at Reset_Handler.
// FOR TR9 KERNEL FW
__attribute__((section(".reset_vectors"), noreturn))
void Reset_Handler(void)
{
   // Disable All INT
    __disable_irq();

    MPU_SETUP_CPU32_USE_REGION();

    // Mark Kernel FW Execute now~
    Scaler32SetBit(PA30000_04_GLOBAL_CTRL_DUMMY0, ~(_BIT2), (_BIT2));

    // Switch CPU Freq to PLL source
    ScalerMcu1usDelayCalc(_M2PLL_CLK);
    // Switch CPU Freq to PLL source(Already done in Reset_Handler)
    ScalerGlobalCtrlSetSys32ClkSrc(_M2PLL_CLK);

    _start();

    //will never be executed
    __builtin_unreachable();
}
#endif

//--------------------------------------------------
// Description  : MEI_Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
__attribute__((section(".after_vectors"), weak))
void NMI_Handler(void)
{
#if defined(DEBUG)
    __DEBUG_BKPT();
#endif

#ifndef CPU32_BOOTLOADER
    SysIntMEI_IRQHandler();
#endif
    while (1)
    {
    }
}

//--------------------------------------------------
// Description  : MTI_Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
__attribute__ ((section(".after_vectors"),weak))
void MTI_Handler(void)
{
    MTimer_RefreshCMP();

    ScalerWdtClearWDT();
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
