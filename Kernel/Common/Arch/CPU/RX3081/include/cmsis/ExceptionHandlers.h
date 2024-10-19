#ifndef RX3081_EXCEPTION_HANDLERS_H_
#define RX3081_EXCEPTION_HANDLERS_H_

#include "Global.h"

#include <stdint.h>

// ----------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif

extern void Reset_Handler (void);
extern void HardFault_Handler (void);
extern void UsageFault_Handler (void);
extern void PendSV_Handler (void);
extern void SysTick_Handler (void);

#if defined(__cplusplus)
}
#endif

// ----------------------------------------------------------------------------

#endif // RX3081_EXCEPTION_HANDLERS_H_
