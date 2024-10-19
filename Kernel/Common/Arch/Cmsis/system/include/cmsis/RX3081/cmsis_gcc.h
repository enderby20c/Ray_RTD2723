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
 * @file     cmsis_gcc.h
 * @brief    CMSIS compiler GCC header file
 * @version  V5.0.2
 * @date     13. February 2017
 ******************************************************************************/
/*
 * Copyright (c) 2009-2017 ARM Limited. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*   SPDX-License-Identifier: LicenseRef-Realtek-Proprietary AND Apache-2.0     */

#ifndef __CMSIS_GCC_H
#define __CMSIS_GCC_H
#include <stdint.h>
#include <assert.h>
#include "rlxasm.h"

/* ignore some GCC warnings */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"


/* CMSIS compiler specific defines */
#ifndef   __ASM
  #define __ASM                                  __asm
#endif
#ifndef   __INLINE
  #define __INLINE                               inline
#endif
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static inline
#endif
#ifndef   __NO_RETURN
  #define __NO_RETURN                            __attribute__((noreturn))
#endif
#ifndef   __USED
  #define __USED                                 __attribute__((used))
#endif
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                        struct __attribute__((packed, aligned(1)))
#endif
#ifndef   __UNALIGNED_UINT32        /* deprecated */
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed)) T_UINT32 { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32(x)                  (((struct T_UINT32 *)(x))->v)
#endif
#ifndef   __UNALIGNED_UINT16_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT16_WRITE { uint16_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT16_WRITE(addr, val)    (void)((((struct T_UINT16_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT16_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT16_READ { uint16_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT16_READ(addr)          (((const struct T_UINT16_READ *)(const void *)(addr))->v)
#endif
#ifndef   __UNALIGNED_UINT32_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT32_WRITE { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_WRITE(addr, val)    (void)((((struct T_UINT32_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT32_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT32_READ { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_READ(addr)          (((const struct T_UINT32_READ *)(const void *)(addr))->v)
#endif
#ifndef   __ALIGNED
  #define __ALIGNED(x)                           __attribute__((aligned(x)))
#endif

#define RLX_IRQ_OFFSET      2      /* reserve 0, 1 for system use */
#define NUM_RLX_IRQ         14     /* number of hardware irq */

typedef unsigned char U8;
typedef unsigned char BIT;


extern uint32_t ISR_TABLE[];
extern uint32_t DSR_TABLE[];

extern const uint32_t PRIORITY_TABLE[];

/* ###########################  Core Function Access  ########################### */
/** \ingroup  CMSIS_Core_FunctionInterface
    \defgroup CMSIS_Core_RegAccFunctions CMSIS Core Register Access Functions
  @{
 */

#define __maybe_unused   __attribute__((unused))

/** \brief  Enable IRQ Interrupts

  This function enables interrupts by setting the IEc-bit in the
  status register
 */
__attribute__((always_inline)) __STATIC_INLINE void __enable_irq(void)
{
  uint32_t flags __maybe_unused;

#ifdef SOC_CPU_HAS_EIDI
  __ASM volatile (
    ".set push                  \n\t"
    ".set noreorder             \n\t"
    "ei                         \n\t"
    ".set pop                   \n\t"
    : /* no output */
    : /* no input */
    : /* no clobber */ );
#else
  __ASM volatile (
    ".set push                  \n\t"
    ".set noreorder             \n\t"
    "mfc0 %0, $12               \n\t"
    COP_HAZARD
    "ori  %0, %0, 0x1           \n\t"
    "mtc0 %0, $12               \n\t"
    COP_HAZARD
    ".set pop                   \n\t"
    : "=r" (flags)
    : /* no input */
    : /* no clobber */ );
#endif
}

/** \brief  Disable IRQ Interrupts

  This function disables IRQ interrupts by setting the IEc-bit in status register
  It returns previous interrupt mask bit for RTX implementation
 */
__attribute__((always_inline)) __STATIC_INLINE unsigned long __disable_irq(void)
{
  uint32_t flags;
  uint32_t tmp;
  uint32_t ie __maybe_unused = ~(0x1);

#ifdef SOC_CPU_HAS_EIDI
  __asm volatile (
    ".set push                  \n\t"
    ".set noreorder             \n\t"
    "mfc0 %0, $12               \n\t"
    "li   %1, 0x1               \n\t"
    "di                         \n\t"
    "xor  %0, %1                \n\t"
    "and  %0, %1                \n\t"
    ".set pop                   \n\t"
    : "=d" (flags), "=d" (tmp)
    : /* no input */
    : /* no clobber */ );
#else
  __asm volatile (
    ".set push                  \n\t"
    ".set noreorder             \n\t"
    "mfc0 %0, $12               \n\t"
    COP_HAZARD
    "and  %1, %0, %2            \n\t"
    "mtc0 %1, $12               \n\t"
    "xori %0, 0x1               \n\t"
    "andi %0, 0x1               \n\t"
    ".set pop                   \n\t"
    : "=&r" (flags), "=r" (tmp)
    : "r" (ie)
    : /* no clobber */ );
#endif

  return flags;
}

/** \brief  Enable IRQ Interrupts by Saved Status

  This function enables interrupt by restoring the saved interrupt
  status register.

  __enable_irq_restore and __disable_irq_save normally appear in pairs
 */
__STATIC_INLINE void __enable_irq_restore(uint32_t sr)
{
  uint32_t flags;
  uint32_t ie __maybe_unused = ~(0x1);

#ifdef SOC_CPU_HAS_EIDI
  __ASM volatile (
    ".set push                  \n\t"
    ".set noreorder             \n\t"
    "li   %0, 0x1               \n\t"
    "and  %1, %0                \n\t"
    "beqz %1, 1f                \n\t"
    "ei                         \n\t"
    "1:                         \n\t"
    ".set pop                   \n\t"
    : "=&d" (flags), "+&d" (sr)
    : /* no input */
    : /* no clobber */ );
#else
  __ASM volatile (
    ".set push                  \n\t"
    ".set noreorder             \n\t"
    "mfc0 %0, $12               \n\t"
    "andi %1, 0x1               \n\t"
    "and  %0, %2                \n\t"
    "or   %0, %1                \n\t"
    "mtc0 %0, $12               \n\t"
    COP_HAZARD
    ".set pop                   \n\t"
    : "=&r" (flags), "+&r" (sr)
    : "r" (ie)
    : /* no clobber */ );
#endif
}

/** \brief  Disable IRQ Interrupts and Save Status

  This function disables interrupts by setting the IE-bit in the
  status register, and returns the previous value of that register.
  __disable_irq_save and __enable_irq_restore normally appear in pairs
 */
__STATIC_INLINE unsigned long __disable_irq_save(void)
{
  uint32_t flags;
  uint32_t tmp;
  uint32_t ie __maybe_unused = ~(0x1);

#ifdef SOC_CPU_HAS_EIDI
  __ASM volatile (
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0 %0, $12                   \n\t"
    COP_HAZARD
    "di                             \n\t"
    "li   %1, 0x1                   \n\t"
    "and  %0, %1                    \n\t"
    ".set pop                       \n\t"
    : "=&d" (flags), "=&d" (tmp)
    :
    : /* no clobber */ );
#else
  __ASM volatile (
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0 %0, $12                   \n\t"
    COP_HAZARD
    "and  %1, %0, %2                \n\t"
    "mtc0 %1, $12                   \n\t"
    "andi %0, 0x1                   \n\t"
    ".set pop                       \n\t"
    : "=&r" (flags), "=r" (tmp)
    : "r" (ie)
    : /* no clobber */ );
#endif

  return flags;
}

__STATIC_INLINE void __enable_cpu_intr(unsigned int intr)
{
  uint32_t flags;
  uint32_t tmp = (0x100 << intr);

  __ASM volatile(
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0 %0, $12                   \n\t"
    COP_HAZARD
    "or   %0, %1                    \n\t"
    "mtc0 %0, $12                   \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : "=&d" (flags)
    : "d" (tmp)
    : /* no clobber */ );
}

__STATIC_INLINE void __enable_vec_intr(unsigned int intr)
{
#ifdef SOC_CPU_HAS_VEC
  uint32_t flags;
  uint32_t tmp = (0x100 << intr);

  __ASM volatile(
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mflxc0   %0, $0                \n\t"
    COP_HAZARD
    "or       %0, %1                \n\t"
    "mtlxc0   %0, $0                \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : "=&r" (flags)
    : "r" (tmp)
    : /* no clobber */ );
#endif
}

__STATIC_INLINE void __disable_cpu_intr(unsigned int intr)
{
  uint32_t flags;
  uint32_t tmp = ~(0x100 << intr);

  __ASM volatile(
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0     %0, $12               \n\t"
    COP_HAZARD
    "and      %0, %1                \n\t"
    "mtc0     %0, $12               \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : "=&d" (flags)
    : "d" (tmp)
    : /* no clobber */ );
}

__STATIC_INLINE void __disable_vec_intr(unsigned int intr)
{
#ifdef SOC_CPU_HAS_VEC
  uint32_t flags;
  uint32_t tmp = ~(0x100 << intr);

  __ASM volatile(
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mflxc0   %0, $0                \n\t"
    COP_HAZARD
    "and      %0, %1                \n\t"
    "mtlxc0   %0, $0                \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : "=&r" (flags)
    : "r" (tmp)
    : /* no clobber */ );
#endif
}

__STATIC_INLINE uint32_t __get_cpu_pending_intr(unsigned int intr)
{
  uint32_t status;
  uint32_t cause;

  __ASM volatile (
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0 %0, $12                   \n\t"
    "mfc0 %1, $13                   \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : "=d" (status), "=d" (cause)
    : /* no input */
    : /* no clobber */ );
    return ((status & cause & (0x100 << intr)) ? 1 : 0);
}

__STATIC_INLINE uint32_t __get_vec_pending_intr(unsigned int intr)
{
  uint32_t status = 0;
  uint32_t ecause = 0;

#ifdef SOC_CPU_HAS_VEC
  __ASM volatile(
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mflxc0 %0, $0                  \n\t"
    "mflxc0 %1, $1                  \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : "=r" (status), "=r" (ecause)
    : /* no input */
    : /* no clobber */ );
#endif
    return ((status & ecause & (0x100 << intr)) ? 1 : 0);
}

/*
 * RTX specific functions
 */
__STATIC_INLINE void __set_cpu_softirq(uint32_t intr)
{
  uint32_t flags;
  uint32_t mask = (0x100 << intr);

  __ASM volatile (
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0  %0, $13                  \n\t"
    COP_HAZARD
    "or    %0, %1                   \n\t"
    "mtc0  %0, $13                  \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : "=&d" (flags)
    : "d" (mask)
    : /* no clobber */ );
}

__STATIC_INLINE void __clear_cpu_softirq(uint32_t intr)
{
  uint32_t flags;
  uint32_t mask = ~(0x100 << intr);

  __ASM volatile (
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0  %0, $13                  \n\t"
    COP_HAZARD
    "and   %0, %1                   \n\t"
    "mtc0  %0, $13                  \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : "=&d" (flags)
    : "d" (mask)
    : /* no clobber */ );
}

__STATIC_INLINE void __set_cpu_intr_pending(U8 fl, BIT p)
{
  uint32_t flags;
  uint32_t pend = p << 9;

  __ASM volatile (
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0  %0, $13                  \n\t"
    COP_HAZARD
    "or    %0, %1                   \n\t"
    "mtc0  %0, $13                  \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : "=&d" (flags)
    : "d" (pend)
    : /* no clobber */ );
}

__STATIC_INLINE void __clear_cpu_intr_pending(unsigned char *fl)
{
  uint32_t flags;
  uint32_t pend = ~0x200;

  __ASM volatile (
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0  %0, $13                  \n\t"
    COP_HAZARD
    "and   %1, %0                   \n\t"
    "mtc0  %1, $13                  \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : "=&d" (flags), "=&d" (pend)
    : "d" (pend)
    : /* no clobber */ );

    *fl = (unsigned char)((flags >> 9) & 0x1);
}


/** \brief  setup ISR vector

  This function registers ISR handler for specific IRQn

 */
__STATIC_INLINE void __isr_set_vector(EnumIRQnType enumIRQn, uint32_t vector)
{
  assert (enumIRQn < NUM_INTR);
  ISR_TABLE[enumIRQn] = vector;
}


/** \brief  get DSR vector

  This function return DSR handler of specific IRQn

 */
__STATIC_INLINE uint32_t __isr_get_vector(EnumIRQnType enumIRQn)
{
  assert (enumIRQn < NUM_INTR);
  return ISR_TABLE[enumIRQn];
}


/** \brief  setup DSR vector

  This function registers DSR handler for specific IRQn

 */
__STATIC_INLINE void __dsr_set_vector(EnumIRQnType enumIRQn, uint32_t vector)
{
  assert (enumIRQn < NUM_INTR);
  DSR_TABLE[enumIRQn] = vector;
}


/** \brief  get logical index of irq

  This function return the irq index based on RLX_IRQ_OFFSET

 */
__STATIC_INLINE uint32_t __irq_get_index(uint32_t irq)
{
  return irq + RLX_IRQ_OFFSET;
}


/**
  \brief   Get Control Register
  \details Returns the content of the Control Register.
  \return               Control Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_CONTROL(void)
{
  /* Only privilege mode is supported in RLX CPUs */
  return(0);
}


/**
  \brief   Set Control Register
  \details Writes the given value to the Control Register.
  \param [in]    control  Control Register value to set
 */
__attribute__((always_inline)) __STATIC_INLINE void __set_CONTROL(uint32_t control)
{
  /* Not supported */
  (void) control;
}


/**
  \brief   Get IPSR Register
  \details Returns the content of the IPSR Register.
  \return               IPSR Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_IPSR(void)
{
  extern uint32_t os_cur_irq;
  uint32_t irq;

  if (os_cur_irq < 2) {
    /* no exception or syscall */
    return os_cur_irq;
  } else {
    irq = (os_cur_irq - (uint32_t)ISR_TABLE) >> 2;
    if (irq < NUM_INTR)
      return __irq_get_index(irq);
  }

  return 0;
}


/**
  \brief   Get APSR Register
  \details Returns the content of the APSR Register.
  \return               APSR Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_APSR(void)
{
  /* Not supported */
  return(0);
}


/**
  \brief   Get xPSR Register
  \details Returns the content of the xPSR Register.
  \return               xPSR Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_xPSR(void)
{
  /* Not supported */
  return(0);
}


/**
  \brief   Get Process Stack Pointer
  \details Returns the current value of the Process Stack Pointer (PSP).
  \return               PSP Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_PSP(void)
{
  //register uint32_t result;
  //__ASM volatile ("move %0, $29\n"  : "=r" (result));
  //return(result);
  return 0;
}


/**
  \brief   Set Process Stack Pointer
  \details Assigns the given value to the Process Stack Pointer (PSP).
  \param [in]    topOfProcStack  Process Stack Pointer value to set
 */
__attribute__((always_inline)) __STATIC_INLINE void __set_PSP(uint32_t topOfProcStack)
{
  //__ASM volatile ("move $29, %0\n" : : "r" (topOfProcStack) : "$29");
  /* not supported */
}


/**
  \brief   Get Main Stack Pointer
  \details Returns the current value of the Main Stack Pointer (MSP).
  \return               MSP Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_MSP(void)
{
    uint32_t stackpointer;

  __ASM volatile (
    "move  %0, sp                   \n\t"
    : "=r" (stackpointer)  /* output operands */
    : /* no input operands */
    : /* no clobber */ );

    return(stackpointer);
}


/**
  \brief   Set Main Stack Pointer
  \details Assigns the given value to the Main Stack Pointer (MSP).
  \param [in]    topOfMainStack  Main Stack Pointer value to set
 */
__attribute__((always_inline)) __STATIC_INLINE void __set_MSP(uint32_t topOfMainStack)
{
  __ASM volatile (
    "move  sp, %0                   \n\t"
    : /* no output operands */
    : "d" (topOfMainStack)  /* input operands */
    : /* no clobber */ );
}

/**
  \brief   Get Priority Mask
  \details Returns the current state of the priority mask bit from the Priority Mask Register.
  \return               Priority Mask value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_PRIMASK(void)
{
  uint32_t flags;
  uint32_t ie __maybe_unused = 0x1;

  __ASM volatile (
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0 %0, $12                   \n\t"
    COP_HAZARD
    "and  %0, %1                    \n\t"
    "xor  %0, %1                    \n\t"
    ".set pop                       \n\t"
    : "=&r" (flags)
    : "r" (ie)
    : /* no clobber */ );

  return flags;
}


/**
  \brief   Set Priority Mask
  \details Assigns the given value to the Priority Mask Register.
  \param [in]    priMask  Priority Mask
 */
__attribute__((always_inline)) __STATIC_INLINE void __set_PRIMASK(uint32_t priMask)
{
  /* not supported */
}

extern const DWORD im_mask;    // STATUS.IM mask table
/**
  \brief   Get Base Priority
  \details Returns the current value of the Base Priority register.
  \return  Native Priority: Low(0) ~ High(5) , Disable(7)
 */
__attribute__((always_inline)) __STATIC_INLINE EnumCpuIrqPriority __get_BASEPRI(void)
{
    const DWORD * im_mask_table = ((const DWORD *)(&im_mask));
    uint32_t status;
    uint32_t ulIdx = 0;

  __ASM volatile (
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0 %0, $12                   \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : "=d" (status) /* output operands */
    : /* no input */
    : /* no clobber */ );

    status |= 0xFFFF00FF;

    while(ulIdx < 8)
    {
        if(im_mask_table[ulIdx] == status)
        {
            break;
        }
        ulIdx++;
    }
    if(ulIdx == 8)
    {
        return _CPU_IRQ_DISABLE;
    }
    else
    {
        return (EnumCpuIrqPriority)(_CPU_IRQ_SW_LEVEL_0 + ulIdx);
    }
}

/**
  \brief   Set Base Priority
  \details Assigns the given value to the Base Priority register.
  \param [in]    basePri  Base Priority value to set (0~7)
 */
__attribute__((always_inline)) __STATIC_INLINE void __set_BASEPRI(EnumCpuIrqPriority enumCpuIrqPriority)
{
    uint32_t ulTmp = 0;
    uint32_t mask = 0xFFFF00FF;
    const DWORD * im_mask_table = ((const DWORD *)(&im_mask));
    uint32_t im_flags = (enumCpuIrqPriority == _CPU_IRQ_DISABLE) ? (0x0000FF00) : (im_mask_table[(enumCpuIrqPriority - _CPU_IRQ_SW_LEVEL_0)] & 0x0000FF00);

  __ASM volatile (
    ".set push                      \n\t"
    ".set noreorder                 \n\t"
    "mfc0  %0, $12                  \n\t"
    COP_HAZARD
    "and   %0, %1                   \n\t"
    "or    %0, %2                   \n\t"
    "mtc0  %0, $12                  \n\t"
    COP_HAZARD
    ".set pop                       \n\t"
    : /* no output operands */
    : "d" (ulTmp) , "d" (mask) , "d" (im_flags)  /* input operands */
    : /* no clobber */ );
}

/*@} end of CMSIS_Core_RegAccFunctions */


/* ##########################  Core Instruction Access  ######################### */
/** \defgroup CMSIS_Core_InstructionInterface CMSIS Core Instruction Interface
  Access to dedicated instructions
  @{
*/

#define __CMSIS_GCC_OUT_REG(r) "=r" (r)
#define __CMSIS_GCC_USE_REG(r) "r" (r)

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
//__attribute__((always_inline)) __STATIC_INLINE void __NOP(void)
//{
//  __ASM volatile ("nop");
//}
#define __NOP()                             __ASM volatile ("nop")       /* This implementation generates debug information */

/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one of a number of events occurs.
 */
//__attribute__((always_inline)) __STATIC_INLINE void __WFI(void)
//{
//  __ASM volatile ("wfi");
//}
#define __WFI()                             __ASM volatile ("sleep")       /* This implementation generates debug information */


/**
  \brief   Wait For Event
  \details Wait For Event is a hint instruction that permits the processor to enter
           a low-power state until one of a number of events occurs.
 */
//__attribute__((always_inline)) __STATIC_INLINE void __WFE(void)
//{
//  __ASM volatile ("wfe");
//}
#define __WFE()                             __ASM volatile ("sleep")       /* This implementation generates debug information */


/**
  \brief   Send Event
  \details Send Event is a hint instruction. It causes an event to be signaled to the CPU.
 */
//__attribute__((always_inline)) __STATIC_INLINE void __SEV(void)
//{
//  __ASM volatile ("sev");
//}
/* Not supported */
#define __SEV()                             __ASM volatile ("nop")       /* This implementation generates debug information */


/**
  \brief   Instruction Synchronization Barrier
  \details Instruction Synchronization Barrier flushes the pipeline in the processor,
           so that all instructions following the ISB are fetched from cache or memory,
           after the instruction has been completed.
 */
__attribute__((always_inline)) __STATIC_INLINE void __ISB(void)
{
#ifdef __m5281
  __ASM volatile ("sync":::"memory");
#else
  __ASM volatile ("":::"memory");
#endif
}


/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
__attribute__((always_inline)) __STATIC_INLINE void __DSB(void)
{
#ifdef __m5281
  __ASM volatile ("sync":::"memory");
#else
  __ASM volatile ("":::"memory");
#endif
}


/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
__attribute__((always_inline)) __STATIC_INLINE void __DMB(void)
{
#ifdef __m5281
  __ASM volatile ("sync":::"memory");
#else
  __ASM volatile ("":::"memory");
#endif
}


/**
  \brief   Reverse byte order (32 bit)
  \details Reverses the byte order in integer value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __REV(uint32_t value)
{
#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
  return __builtin_bswap32(value);
#else
  return (((value & 0xff000000) >> 24) | \
          ((value & 0x00ff0000) >>  8) | \
          ((value & 0x0000ff00) <<  8) | \
          ((value & 0x000000ff) << 24));
#endif
}


/**
  \brief   Reverse byte order (16 bit)
  \details Reverses the byte order in two unsigned short values.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __REV16(uint32_t value)
{
  return (((value & 0xff00) >>  8) | \
          ((value & 0x00ff) <<  8));
}


/**
  \brief   Reverse byte order in signed short value
  \details Reverses the byte order in a signed short value with sign extension to integer.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__attribute__((always_inline)) __STATIC_INLINE int32_t __REVSH(int32_t value)
{
  return (short)__builtin_bswap16(value);
}


/**
  \brief   Rotate Right in unsigned value (32 bit)
  \details Rotate Right (immediate) provides the value of the contents of a register rotated by a variable number of bits.
  \param [in]    op1  Value to rotate
  \param [in]    op2  Number of Bits to rotate
  \return               Rotated value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  return (op1 >> op2) | (op1 << (32U - op2));
}


/**
  \brief   Breakpoint
  \details Causes the processor to enter Debug state.
           Debug tools can use this to investigate system state when the instruction at a particular address is reached.
  \param [in]    value  is ignored by the processor.
                 If required, a debugger can use it to store additional information about the breakpoint.
 */
#define __BKPT(value)                       __ASM volatile ("break "#value)


/**
  \brief   Reverse bit order of value
  \details Reverses the bit order of the given value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __RBIT(uint32_t value)
{
  uint32_t result;

  int32_t s = (4 /*sizeof(v)*/ * 8) - 1; /* extra shift needed at end */

  result = value;                      /* r will be reversed bits of v; first get LSB of v */
  for (value >>= 1U; value; value >>= 1U)
  {
    result <<= 1U;
    result |= value & 1U;
    s--;
  }
  result <<= s;                        /* shift when v's highest bits are zero */

  return(result);
}


/**
  \brief   Count leading zeros
  \details Counts the number of leading zeros of a data value.
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
#define __CLZ             __builtin_clz


/**
  \brief   LDR Exclusive (8 bit)
  \details Executes a exclusive LDR instruction for 8 bit value.
  \param [in]    ptr  Pointer to data
  \return             value of type uint8_t at (*ptr)
 */
__attribute__((always_inline)) __STATIC_INLINE uint8_t __LDREXB(volatile uint8_t *addr)
{
    uint32_t result;

    __ASM volatile ("lb %0, 0(%1)" : "=r" (result) : "Q" (*addr) );
    return(result);
}


/**
  \brief   LDR Exclusive (16 bit)
  \details Executes a exclusive LDR instruction for 16 bit values.
  \param [in]    ptr  Pointer to data
  \return        value of type uint16_t at (*ptr)
 */
__attribute__((always_inline)) __STATIC_INLINE uint16_t __LDREXH(volatile uint16_t *addr)
{
    uint32_t result;

    __ASM volatile ("lh %0, 0(%1)" : "=r" (result) : "Q" (*addr) );
    return(result);
}


/**
  \brief   LDR Exclusive (32 bit)
  \details Executes a exclusive LDR instruction for 32 bit values.
  \param [in]    ptr  Pointer to data
  \return        value of type uint32_t at (*ptr)
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __LDREXW(volatile uint32_t *addr)
{
    uint32_t result;

    __ASM volatile ("lw %0, 0(%1)" : "=r" (result) : "Q" (*addr) );
    return(result);
}


/**
  \brief   STR Exclusive (8 bit)
  \details Executes a exclusive STR instruction for 8 bit values.
  \param [in]  value  Value to store
  \param [in]    ptr  Pointer to location
  \return          0  Function succeeded
  \return          1  Function failed
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __STREXB(uint8_t value, volatile uint8_t *addr)
{
   /* Not supported */
   __ASM volatile ("sb %1, 0(%0)" : "=r" (*addr) : "r" (value) );
   return(0);
}


/**
  \brief   STR Exclusive (16 bit)
  \details Executes a exclusive STR instruction for 16 bit values.
  \param [in]  value  Value to store
  \param [in]    ptr  Pointer to location
  \return          0  Function succeeded
  \return          1  Function failed
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __STREXH(uint16_t value, volatile uint16_t *addr)
{
    /* FIXME: Not supported */
    __ASM volatile ("sh %1, 0(%0)" : "=r" (*addr) : "r" (value) );
    return(0);
}


/**
  \brief   STR Exclusive (32 bit)
  \details Executes a exclusive STR instruction for 32 bit values.
  \param [in]  value  Value to store
  \param [in]    ptr  Pointer to location
  \return          0  Function succeeded
  \return          1  Function failed
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __STREXW(uint32_t value, volatile uint32_t *addr)
{
    /* FIXME: Not supported */
    __ASM volatile ("sw %1, 0(%0)" : "=r" (*addr) : "r" (value) );
    return(0);
}


/**
  \brief   Remove the exclusive lock
  \details Removes the exclusive lock which is created by LDREX.
 */
__attribute__((always_inline)) __STATIC_INLINE void __CLREX(void)
{
    /* FIXME: Not supported */
    __ASM volatile ("" ::: "memory");
}


#pragma GCC diagnostic pop

#endif /* __CMSIS_GCC_H */
