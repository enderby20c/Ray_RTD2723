#include "ScalerFunctionInclude.h"

__attribute__((section(".fast_data.g_ulTargetSystickCpuTicks")))
DWORD g_ulTargetSystickCpuTicks;


// ----------------------------------------------------------------------------
// This is the application hardware initialisation routine,
// redefined to add more inits.
//
// Called early from _start(), right after data & bss init, before
// constructors.
//
// After Reset the Cortex-M processor is in Thread mode,
// priority is Privileged, and the Stack is set to Main.
//
// Warning: The HAL requires the system timer, running at 1000 Hz
// and calling HAL_IncTick().

void __initialize_hardware(void) {
#ifndef CPU32_BOOTLOADER
    ScalerMcuInitialKR4();
#endif
}
