#ifndef TR9_EXCEPTION_HANDLERS_H_
#define TR9_EXCEPTION_HANDLERS_H_

#include "Global.h"

#include <stdint.h>

// ----------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif

extern void Reset_Handler(void);
extern void NMI_Handler(void);
extern void MTI_Handler(void);
extern void HardFault_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);


#if defined(__cplusplus)
}
#endif

// ----------------------------------------------------------------------------

#endif // TR9_EXCEPTION_HANDLERS_H_
