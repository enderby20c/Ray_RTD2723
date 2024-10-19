/********************************************************************************/
/*   Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.        */
/*                                                                              */
/*   Commercial License Usage                                                   */
/*   This software component is confidential and proprietary to Realtek         */
/*   Semiconductor Corp. Disclosure, reproduction, redistribution, in whole     */
/*   or in part, of this work and its derivatives without express permission    */
/*   is prohibited.                                                             */
/********************************************************************************/

/**************************************************************************//**
 * @file     rtk32rx3081.h
 * @brief    CMSIS MIPS# Core Peripheral Access Layer Header File for
 *           Device rtk32rx3081
 * @version  V3.10
 * @date     23. November 2012
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

/*  SPDX-License-Identifier: LicenseRef-Realtek-Proprietary AND ARM Proprietary */

#ifndef Device_RTK32_RX3081_H      /* ToDo: replace '<Device>' with your device name */
#define Device_RTK32_RX3081_H

#if defined(DEBUG)
#define _JTAG_DEBUG                         _ON
#else
#define _JTAG_DEBUG                         _OFF
#endif

#define RX3081

#define OS_INCLUDE_STARTUP_INIT_MULTIPLE_RAM_SECTIONS

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup <Device>_CMSIS Device CMSIS Definitions
  Configuration of the Cortex-M# Processor and Core Peripherals
  @{
*/
#define __MPU_PRESENT                       0       /*!< MPU(PMP) present or not                               */

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */
#define _CPU_IRQ_DISABLE_VALUE          (7)

#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//RX3081 as KCPU(Boot CPU)
#define INT_PRIORITY_CTRL_BASE_ADDR     (0xA4001080)
#define INT_PENDING_STATUS_ADDR         (0xA4001040)
#else
//RX3081 as SCPU
#define INT_PRIORITY_CTRL_BASE_ADDR     (0xA3000080)
#define INT_PENDING_STATUS_ADDR         (0xA3000040)
#endif

extern EnumCpuIrqPriority const tINTERRUPT_PRIORITY_RX3081[];

#define GET_INT_PRIORITY(enumIRQnTypeIdx)       (tINTERRUPT_PRIORITY_RX3081[enumIRQnTypeIdx])

// Native Priority: Low(HW_LOWEST - HW_LOWEST) ~ High(HW_HIGHEST - HW_LOWEST) , Disable(7)
#define GET_REMAP_PRIORITY_NATIVE(ulPriority)   (((ulPriority) < _CPU_IRQ_HW_LOWEST_LEVEL) ? (_CPU_IRQ_DISABLE_VALUE) : ((ulPriority) - _CPU_IRQ_HW_LOWEST_LEVEL))
// Remap Priority: Low(HW_LOWEST) ~ High(HW_HIGHEST) , Disable(0)
#define GET_REMAP_PRIORITY(ulRegPriorityNative) (((ulRegPriorityNative) == _CPU_IRQ_DISABLE_VALUE) ? ((DWORD)_CPU_IRQ_DISABLE) : ((DWORD)_CPU_IRQ_HW_LOWEST_LEVEL + (ulRegPriorityNative)))


#ifdef  USE_FULL_ASSERT
/**
  * @brief  The ASSERT_PARAM macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
void assert_failed(BYTE* file, DWORD line);
#define ASSERT_PARAM(expr)                  ((expr) ? (void)0 : assert_failed((BYTE *)__FILE__, __LINE__))
#else
#define ASSERT_PARAM(expr)                  ((void)0)
#endif
/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

// #define SET_SYSCALL()                       (__set_cpu_softirq(0))
#define SET_SW_INT0()                       (__set_cpu_softirq(0))
#define CLEAR_SW_INT0()                     (__clear_cpu_softirq(0))

#define SET_SW_INT1()                       (__set_cpu_softirq(1))
#define CLEAR_SW_INT1()                     (__clear_cpu_softirq(1))

#define SET_PENDSV_EVENT()                  (SET_SW_INT0())
#define CLEAR_PENDSV_EVENT()                (CLEAR_SW_INT0())


// Instruction sync. Barrier,will confirm all instruction execute done and flush pipeline
#define ASM_ISB()                           (__ISB())

// Data memory Barrier,will confirm memory op execute done (but not promise clear write buffer and sync to last memory,still need clean op for cache sync), then commit the memory op inst. after it.
#define ASM_DMB()                           (__DMB())

// Data synchronization Barrier,will confirm memory op execute && sync done (will clear write buffer(to cache) ,but not promise sync to last memory,still need clean op for cache sync), then execute the inst. after it.
#define ASM_DSB()                           (__DSB())

#define ASM_JUMP_TO_PC(pc)                  ({\
                                                __asm__ __volatile__(\
                                                    "move  $3,%0                    \n\t"\
                                                    "jr    $3                       \n\t"\
                                                    : /* no output operands */\
                                                    : "d" (pc)  /* input operands */\
                                                    : "v1"/* no clobber */ );\
                                            })



// IRQ_PRIORITY: _CPU_IRQ_SW_LEVEL_0 ~ _CPU_IRQ_HW_LEVEL_5
// Input enumCpuIrqPriority: Low(SW_INT0) ~ High(HW_HIGHEST) , Disable(0)
#define SET_BASE_PRIORITY(enumCpuIrqPriority)   (__set_BASEPRI((enumCpuIrqPriority)))

// return enumCpuIrqPriority: Low(SW_INT0) ~ High(HW_HIGHEST) , Disable(0)
#define GET_BASE_PRIORITY()                 (__get_BASEPRI())

#define CPU32_ENABLE_GLOBAL_IRQ()           (__enable_irq())

#define CPU32_DISABLE_GLOBAL_IRQ()          (__disable_irq())

#define CPU32_GET_GLOBAL_IRQ_STATUS()       ((read_c0_status() & _BIT0) ? _ENABLE : _DISABLE)

#define CPU32_IS_INSIDE_INTERRUPT()         (((read_c0_status() & _BIT(15,8)) == _BIT(15,8)) ? _FALSE : _TRUE)

#define SET_VTOR(ulValue)

#define SET_IMEM_RANGE(ulIWBase0,ulIWTop0)
#define IMEM_FILL_AND_ENABLE()
#define ENABLE_ITCM()
#define RESET_I_CACHE()                     ({\
                                                __asm__ __volatile__(\
                                                    "mfc0   $2,$20          \n\t"\
                                                    "li     $3,(0xFFFFFFFD) \n\t"\
                                                    "and    $2,$3           \n\t"\
                                                    "mtc0   $2,$20          \n\t"\
                                                    "li     $3,2            \n\t"\
                                                    "or     $2,$3           \n\t"\
                                                    "mtc0   $2,$20          \n\t"\
                                                    "nop                    \n\t"\
                                                    "nop                    \n\t"\
                                                    "nop                    \n\t"\
                                                    : /* no output operands */\
                                                    : /* input operands */\
                                                    : "v0","v1"/* no clobber */ );\
                                            })

#define RESET_D_CACHE()
#define CLEAN_D_CACHE()
#define ENABLE_I_D_CACHE()
#define ENABLE_I_CACHE()
#define ENABLE_D_CACHE()
#define DISABLE_I_CACHE()
#define DISABLE_D_CACHE()

#define CACHE_CONTROL_INIT()

#define MPU_SETUP_CPU32_USE_REGION()
#define MPU_SETUP_ITCM_REGION(enumCpu32MpuAccessPermission) (UNUSED(enumCpu32MpuAccessPermission))

#define SYSTICK_CONFIG(ulTicksNumb)         (ScalerTimerInitTimer(_CPU_TIMER_3, _TIMER_X_TIMER_MODE, (ulTicksNumb), _ENABLE, _TIMER_X_INT_ENABLE))
#define SYSTICK_DISABLE_INTERRUPT()         (ScalerTimerSetINTEn(_CPU_TIMER_3, _TIMER_X_INT_DISABLE))
#define SYSTICK_ENABLE_INTERRUPT()          (ScalerTimerSetINTEn(_CPU_TIMER_3, _TIMER_X_INT_ENABLE))
#define SYSTICK_GET_CURRENT_VALUE()         (ScalerTimerGetCurrentValue(_CPU_TIMER_3))
#define SYSTICK_GET_RELOAD_VALUE()          (ScalerTimerGetTargetValue(_CPU_TIMER_3))


// SVC_M_N
//     M:parameter number
//       N: 0:no return;1:have return value
#define SVC_Call(f)                         ({\
                                                __asm__ __volatile__(\
                                                    "move $16, %0    \n\t"\
                                                    ".hword 0xFEBA \n\t"\
                                                    : /* output operands */\
                                                    : "d" (f)/* input operands */\
                                                    : "s0", "ra"/* clobber(modified cpu reg in the code) */ );\
                                            })

#define IMEM_WRITE(ulAddr, ulData)          ({\
                                                __asm__ __volatile__(\
                                                    "move $3, %1 \n\t"\
                                                    "move $2, %0 \n\t"\
                                                    "mtlo $3 \n\t"\
                                                    "CACHE 0b01010, 0($2)\n\t"\
                                                    : /* output operands */\
                                                    : "d" (ulAddr), "d" (ulData)/* input operands */\
                                                    : "v0", "v1"/* clobber(modified cpu reg in the code) */ );\
                                            })

#define IMEM_READ(ulAddr)                   ({\
                                                int __res;\
                                                __asm__ __volatile__(\
                                                    "move $2, %0 \n\t"\
                                                    "CACHE 0b00110, 0($2)\n\t"\
                                                    "mflo\t%0 \n\t"\
                                                    : "=r"(__res)/* output operands */\
                                                    : "d" (ulAddr)/* input operands */\
                                                    : "v0"/* clobber(modified cpu reg in the code) */ );\
                                                __res;\
                                            })

#define CPU_SWITCH_DISABLE_ALL_INT()        ({\
                                                __asm__ __volatile__(\
                                                    "lui $2, 0x0040 \n\t"\
                                                    "mtc0 $2, $12 \n\t"\
                                                    "nop \n\t"\
                                                    : /* output operands */\
                                                    : /* input operands */\
                                                    : "v0" /* clobber(modified cpu reg in the code) */ );\
                                            })

// RX3081 Default exception handlers.
// pulBuf[7] = {CP0_STATUS, CP0_CAUSE, CP0_EPC, CP0_BADVADDR, CP0_CCTL, CP0_CK0, CP0_CK1}
#define TRAP_DUMP(pulBuf)                   ({\
                                                __asm__ __volatile__(\
                                                    ".set push          \n\t"\
                                                    ".set noreorder     \n\t"\
                                                    "mfc0 %0, $12       \n\t"\
                                                    "mfc0 %1, $13       \n\t"\
                                                    COP_HAZARD\
                                                    "mfc0 %2, $14       \n\t"\
                                                    "mfc0 %3, $8        \n\t"\
                                                    COP_HAZARD\
                                                    "mfc0 %4, $20       \n\t"\
                                                    "mfc0 %5, $26       \n\t"\
                                                    COP_HAZARD\
                                                    "mfc0 %6, $27       \n\t"\
                                                    COP_HAZARD\
                                                    ".set pop           \n\t"\
                                                    : "=d" (pulBuf[0]), "=d" (pulBuf[1]), "=d" (pulBuf[2]), "=d" (pulBuf[3]), "=d" (pulBuf[4]), "=d" (pulBuf[5]), "=d" (pulBuf[6])\
                                                    : /* no input */\
                                                    : /* no clobber */ );\
                                            })

#if defined(DEBUG)
#define __DEBUG_BKPT()                      asm volatile ("sdbbp 0")
#endif

#ifndef   __ALWAYS_INLINE
#define __ALWAYS_INLINE                     __attribute__((always_inline))
#endif
/**
  * @}
  */
#include "rlx_math.h"


#ifdef __cplusplus
}
#endif

#endif  /* Device_RTK32_RX3081_H */
