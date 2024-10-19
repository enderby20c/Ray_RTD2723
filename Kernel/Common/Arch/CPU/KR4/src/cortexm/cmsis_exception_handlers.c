// ----------------------------------------------------------------------------

#include "SysInclude.h"
#include "ExceptionHandlers.h"
#include <string.h>


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
void __attribute__ ((section(".after_vectors"),weak))
HardFault_Handler (void)
{
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_KCPU_HARD_FAULT);
#else
    ScalerCpuCtrlBusErrorProcess(_DBG_SYSBUS_ERR_SCPU_HARD_FAULT);
#endif

#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
    while (1)
    {
    }
#endif
}


// ----------------------------------------------------------------------------
