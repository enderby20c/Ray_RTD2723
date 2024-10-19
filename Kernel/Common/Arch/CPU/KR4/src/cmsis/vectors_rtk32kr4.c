/********************************************************************************/
/*   Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.        */
/*                                                                              */
/*   Commercial License Usage                                                   */
/*   This software component is confidential and proprietary to Realtek         */
/*   Semiconductor Corp. Disclosure, reproduction, redistribution, in whole     */
/*   or in part, of this work and its derivatives without express permission    */
/*   is prohibited.                                                             */
/********************************************************************************/

/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/* SPDX-License-Identifier: LicenseRef-Realtek-Proprietary AND Liviu Ionescu Proprietary */

// ----------------------------------------------------------------------------
#include "ScalerFunctionInclude.h"
#include "ExceptionHandlers.h"

// ----------------------------------------------------------------------------
__attribute__((weak))
void SysIntDefaultHandler(void);

// Forward declaration of the specific IRQ handlers. These are aliased
// to the SysIntDefaultHandler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
// TODO: Rename this and add the actual routines here.
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntMainCpuSw0IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntMainCpuSw1IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntMainCpuHw0IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntMainCpuHw1IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntMainCpuHw2IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntMainCpuHw3IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntMainCpuHw4IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntMainCpuHw5IRQHandler(void);
#else
__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntSecondCpuSw0IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntSecondCpuSw1IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntSecondCpuHw0IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntSecondCpuHw1IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntSecondCpuHw2IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntSecondCpuHw3IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntSecondCpuHw4IRQHandler(void);

__attribute__((weak, alias("SysIntDefaultHandler")))
void SysIntSecondCpuHw5IRQHandler(void);
#endif


extern void Vector_SVC(void);


// The vector table.
// This relies on the linker script to place at correct location in memory.
__attribute__((section(".ISR_TABLE.itcm_section"), used))
uint32_t ISR_TABLE[] =
{
                                                /// Priority Low
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    (uint32_t)SysIntMainCpuSw0IRQHandler,       // 23:ISR[0]
    (uint32_t)SysIntMainCpuSw1IRQHandler,       // 22:ISR[1]
    (uint32_t)SysIntMainCpuHw0IRQHandler,       // 21:ISR[2]
    (uint32_t)SysIntMainCpuHw1IRQHandler,       // 20:ISR[3]
    (uint32_t)SysIntMainCpuHw2IRQHandler,       // 19:ISR[4]
    (uint32_t)SysIntMainCpuHw3IRQHandler,       // 18:ISR[5]
    (uint32_t)SysIntMainCpuHw4IRQHandler,       // 17:ISR[6]
    (uint32_t)SysIntMainCpuHw5IRQHandler,       // 16:ISR[7]
#else
    (uint32_t)SysIntSecondCpuSw0IRQHandler,     // 23:ISR[0]
    (uint32_t)SysIntSecondCpuSw1IRQHandler,     // 22:ISR[1]
    (uint32_t)SysIntSecondCpuHw0IRQHandler,     // 21:ISR[2]
    (uint32_t)SysIntSecondCpuHw1IRQHandler,     // 20:ISR[3]
    (uint32_t)SysIntSecondCpuHw2IRQHandler,     // 19:ISR[4]
    (uint32_t)SysIntSecondCpuHw3IRQHandler,     // 18:ISR[5]
    (uint32_t)SysIntSecondCpuHw4IRQHandler,     // 17:ISR[6]
    (uint32_t)SysIntSecondCpuHw5IRQHandler,     // 16:ISR[7]
#endif

    (uint32_t)MTI_Handler,                      // 07:MTI
    (uint32_t)Vector_SVC,                       // 03:MSI
    (uint32_t)NMI_Handler,                      // 11:MEI

                                                /// Priority High
};

// ----------------------------------------------------------------------------
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
__attribute__((section(".after_vectors.SysIntDefaultHandler")))
void SysIntDefaultHandler(void)
{
    while (1)
    {
    }
}

