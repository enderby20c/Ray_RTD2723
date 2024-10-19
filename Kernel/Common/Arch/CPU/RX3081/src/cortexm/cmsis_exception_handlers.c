// ----------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "ExceptionHandlers.h"
#include <string.h>


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
__INLINE void __ALWAYS_INLINE Trap_Debug_Dump(EnumDebugSysBusErrorType enumDebugSysBusErrorType)
{
    // Log Bus Error Information
    if(Scaler32GetDWord(PA40010_4C_CPU1_TEST_MODE_DUMMY3) == 0x00000000)
    {
        Scaler32SetDWord(PA40010_4C_CPU1_TEST_MODE_DUMMY3, (DWORD)g_pulDebugSysBusErrorInfo);
        DISABLE_CPU32_WDT();
        g_pulDebugSysBusErrorInfo[0] = enumDebugSysBusErrorType;
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
        // g_pulDebugSysBusErrorInfo[1~7] = {CP0_STATUS, CP0_CAUSE, CP0_EPC, CP0_BADVADDR, CP0_CCTL, CP0_CK0, CP0_CK1}
        TRAP_DUMP((&g_pulDebugSysBusErrorInfo[1]));
#endif
    }
}
#endif

// ----------------------------------------------------------------------------
void __attribute__ ((section(".after_vectors"),weak))
HardFault_Handler (void)
{
#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
    Trap_Debug_Dump(_DBG_SYSBUS_ERR_KCPU_HARD_FAULT);
#endif
    while (1)
    {
    }
}

void __attribute__ ((section(".after_vectors"),weak))
UsageFault_Handler (void)
{
#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
    Trap_Debug_Dump(_DBG_SYSBUS_ERR_KCPU_USAGE_FAULT);
#endif
    while (1)
    {
    }
}


// ----------------------------------------------------------------------------
