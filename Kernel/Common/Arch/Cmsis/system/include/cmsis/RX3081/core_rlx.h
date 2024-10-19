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
 * @file     core_rlx.h
 * @brief    Core Processors Instruction Access Header File
 * @version  V0.0.1
 * @date     8. December 2020
 ******************************************************************************/
/*
 * Copyright (c) 2009-2020 Arm Limited. All rights reserved.
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

#ifndef __CORE_RLX_H_GENERIC
#define __CORE_RLX_H_GENERIC

#ifdef __cplusplus
 extern "C" {
#endif

/*******************************************************************************
 *                 CMSIS definitions
 ******************************************************************************/
/** \ingroup RLX
  @{
 */

/*  CMSIS RLX definitions */
#define __RLX_CMSIS_VERSION_MAIN  (0x03)                                   /*!< [31:16] CMSIS HAL main version   */
#define __RLX_CMSIS_VERSION_SUB   (0x20)                                   /*!< [15:0]  CMSIS HAL sub version    */
#define __RLX_CMSIS_VERSION       ((__RLX_CMSIS_VERSION_MAIN << 16) | \
                                    __RLX_CMSIS_VERSION_SUB          )     /*!< CMSIS HAL version number         */

/** __FPU_USED indicates whether an FPU is used or not.
    This core does not support an FPU at all
*/
#define __FPU_USED       0U
#if defined ( __GNUC__ )
  #if defined (__VFP_FP__) && !defined(__SOFTFP__)
    #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif
#endif

#include "cmsis_compiler.h"               /* CMSIS compiler specific defines */

#ifdef __cplusplus
}
#endif

#endif /* __CORE_RLX_H_GENERIC */

#ifndef __CMSIS_GENERIC

#ifndef __CORE_RLX_H_DEPENDANT
#define __CORE_RLX_H_DEPENDANT

#ifdef __cplusplus
 extern "C" {
#endif

/* check device defines and use defaults */
#if defined __CHECK_DEVICE_DEFINES
  #ifndef __RLX_REV
    #define __RLX_REV               0x0200
    #warning "__RLX_REV not defined in device header file; using default!"
  #endif

  #ifndef __MPU_PRESENT
    #define __MPU_PRESENT             0
    #warning "__MPU_PRESENT not defined in device header file; using default!"
  #endif

#endif

/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CMSIS_glob_defs CMSIS Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */

/*@} end of group RLX */


/* ##########################   NVIC functions  #################################### */
/** \ingroup  CMSIS_Core_FunctionInterface
    \defgroup CMSIS_Core_NVICFunctions NVIC Functions
    \brief      Functions that manage interrupts and exceptions via the NVIC.
    @{
 */

#ifdef CMSIS_NVIC_VIRTUAL
  #ifndef CMSIS_NVIC_VIRTUAL_HEADER_FILE
    #define CMSIS_NVIC_VIRTUAL_HEADER_FILE "cmsis_nvic_virtual.h"
  #endif
  #include CMSIS_NVIC_VIRTUAL_HEADER_FILE
#else
  #define NVIC_SetPriorityGrouping    __NVIC_SetPriorityGrouping
  #define NVIC_GetPriorityGrouping    __NVIC_GetPriorityGrouping
  #define NVIC_EnableIRQ              __NVIC_EnableIRQ
  #define NVIC_GetEnableIRQ           __NVIC_GetEnableIRQ
  #define NVIC_DisableIRQ             __NVIC_DisableIRQ
  #define NVIC_GetPendingIRQ          __NVIC_GetPendingIRQ
  #define NVIC_SetPendingIRQ          __NVIC_SetPendingIRQ
  #define NVIC_ClearPendingIRQ        __NVIC_ClearPendingIRQ
  #define NVIC_GetActive              __NVIC_GetActive
  #define NVIC_SetPriority            __NVIC_SetPriority
  #define NVIC_GetPriority            __NVIC_GetPriority
  #define NVIC_EncodePriority         __NVIC_EncodePriority
  #define NVIC_DecodePriority         __NVIC_DecodePriority
  #define NVIC_SystemReset            __NVIC_SystemReset
#endif /* CMSIS_NVIC_VIRTUAL */

#ifdef CMSIS_VECTAB_VIRTUAL
  #ifndef CMSIS_VECTAB_VIRTUAL_HEADER_FILE
   #define CMSIS_VECTAB_VIRTUAL_HEADER_FILE "cmsis_vectab_virtual.h"
  #endif
  #include CMSIS_VECTAB_VIRTUAL_HEADER_FILE
#else
  #define NVIC_SetVector              __NVIC_SetVector
  #define NVIC_GetVector              __NVIC_GetVector
#endif  /* (CMSIS_VECTAB_VIRTUAL) */

#define UNUSED(x) (void)(x)

/**
  \brief   Set Interrupt Vector
  \details Sets an interrupt vector in SRAM based interrupt vector table.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
           VTOR must been relocated to SRAM before.
  \param [in]   enumIRQn  Interrupt number
  \param [in]   vector    Address of interrupt handler function
 */
__STATIC_INLINE void __NVIC_SetVector(EnumIRQnType enumIRQn, uint32_t vector)
{
  // __isr_set_vector(enumIRQn, vector);
  /* Not supported */
  UNUSED(enumIRQn);
  UNUSED(vector);
}


/**
  \brief   Get Interrupt Vector
  \details Reads an interrupt vector from interrupt vector table.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]   enumIRQn  Interrupt number.
  \return                 Address of interrupt handler function
 */
__STATIC_INLINE uint32_t __NVIC_GetVector(EnumIRQnType enumIRQn)
{
  // return __isr_get_vector(enumIRQn);
  /* Not supported */
  UNUSED(enumIRQn);
  return 0;
}

__STATIC_INLINE void DSR_SetVector(EnumIRQnType enumIRQn, uint32_t vector)
{
  // __dsr_set_vector(enumIRQn, vector);
  /* Not supported */
  UNUSED(enumIRQn);
  UNUSED(vector);
}

/** \brief  Set Priority Grouping

  The function sets the priority grouping field using the required unlock sequence.
  The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
  Only values from 0..7 are used.
  In case of a conflict between priority grouping and available
  priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.

    \param [in]      PriorityGroup  Priority grouping field.
 */
__STATIC_INLINE void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  /* Not supported */
  UNUSED(PriorityGroup);
}

/** \brief  Get Priority Grouping

  The function reads the priority grouping field from the NVIC Interrupt Controller.

    \return                Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field).
 */
__STATIC_INLINE uint32_t __NVIC_GetPriorityGrouping(void)
{
  /* Not supported */
  return 0;   /* read priority grouping field */
}

/** \brief  Enable External Interrupt

    The function enables a device-specific interrupt in the NVIC interrupt controller.

    \param [in]      enumIRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void __NVIC_EnableIRQ(EnumIRQnType enumIRQn)
{
    if ((SDWORD)(enumIRQn) >= 0)
    {
        // PA30000_80_CPU1_INT_PRIORITY_CTRL0
        DWORD ulPriorityRegAddress =  INT_PRIORITY_CTRL_BASE_ADDR + ((((DWORD)enumIRQn) / 8) << 2);
        DWORD ulBitOffset =  (((DWORD)enumIRQn) % 8) << 2;
        DWORD ulBitMask = ((1UL << 3) << ulBitOffset);

        bit bGlobalIntStatus = CPU32_GET_GLOBAL_IRQ_STATUS();
        if(bGlobalIntStatus == _ENABLE)
        {
            CPU32_DISABLE_GLOBAL_IRQ();
        }

        (*((volatile DWORD *)(ulPriorityRegAddress))) |= ulBitMask;

        if(bGlobalIntStatus == _ENABLE)
        {
            CPU32_ENABLE_GLOBAL_IRQ();
        }
    }
}

/** \brief  Disable External Interrupt

    The function disables a device-specific interrupt in the NVIC interrupt controller.

    \param [in]      enumIRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void __NVIC_DisableIRQ(EnumIRQnType enumIRQn)
{
    if ((SDWORD)(enumIRQn) >= 0)
    {
        // PA30000_80_CPU1_INT_PRIORITY_CTRL0
        DWORD ulPriorityRegAddress =  INT_PRIORITY_CTRL_BASE_ADDR + ((((DWORD)enumIRQn) / 8) << 2);
        DWORD ulBitOffset =  (((DWORD)enumIRQn) % 8) << 2;
        DWORD ulBitMask = ~((1UL << 3) << ulBitOffset);

        bit bGlobalIntStatus = CPU32_GET_GLOBAL_IRQ_STATUS();
        if(bGlobalIntStatus == _ENABLE)
        {
            CPU32_DISABLE_GLOBAL_IRQ();
        }

        (*((volatile DWORD *)(ulPriorityRegAddress))) &= ulBitMask;

        if(bGlobalIntStatus == _ENABLE)
        {
            CPU32_ENABLE_GLOBAL_IRQ();
        }
    }
}

/**
  \brief   Get Interrupt Enable status
  \details Returns a device specific interrupt enable status from the NVIC interrupt controller.
  \param [in]      enumIRQn  Device specific interrupt number.
  \return             0  Interrupt is not enabled.
  \return             1  Interrupt is enabled.
  \note    enumIRQn must not be negative.
 */
__STATIC_INLINE uint32_t __NVIC_GetEnableIRQ(EnumIRQnType enumIRQn)
{
    uint32_t retval = 0;

    if ((SDWORD)(enumIRQn) >= 0)
    {
        // PA30000_80_CPU1_INT_PRIORITY_CTRL0
        DWORD ulPriorityRegAddress =  INT_PRIORITY_CTRL_BASE_ADDR + ((((DWORD)enumIRQn) / 8) << 2);
        DWORD ulBitOffset =  (((DWORD)enumIRQn) % 8) << 2;
        retval = (*((volatile DWORD *)(ulPriorityRegAddress))) & ((1UL << 3) << ulBitOffset);
    }
    if(retval != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/** \brief  Get Pending Interrupt

    The function reads the pending register in the NVIC and returns the pending bit
    for the specified interrupt.

    \param [in]      enumIRQn  Interrupt number.

    \return             0  Interrupt status is not pending.
    \return             1  Interrupt status is pending.
 */
__STATIC_INLINE uint32_t __NVIC_GetPendingIRQ(EnumIRQnType enumIRQn)
{
    uint32_t retval = 0;

    if ((SDWORD)(enumIRQn) >= 0)
    {
        EnumCpuIrqPriority enumHwIrqPriority = GET_INT_PRIORITY(enumIRQn);
        if(enumHwIrqPriority != _CPU_IRQ_DISABLE)
        {
            retval = __get_cpu_pending_intr(enumHwIrqPriority - 1);
        }
    }
    return retval;
}


/** \brief  Set Pending Interrupt

    The function sets the pending bit of an external interrupt.

    \param [in]      enumIRQn  Interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void __NVIC_SetPendingIRQ(EnumIRQnType enumIRQn)
{
    if ((SDWORD)(enumIRQn) >= 0)
    {
        EnumCpuIrqPriority enumHwIrqPriority = GET_INT_PRIORITY(enumIRQn);
        if(enumHwIrqPriority != _CPU_IRQ_DISABLE)
        {
            __set_cpu_softirq(enumHwIrqPriority - 1);
        }
    }
}


/** \brief  Clear Pending Interrupt

    The function clears the pending bit of an external interrupt.

    \param [in]      enumIRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void __NVIC_ClearPendingIRQ(EnumIRQnType enumIRQn)
{
    if ((SDWORD)(enumIRQn) >= 0)
    {
        EnumCpuIrqPriority enumHwIrqPriority = GET_INT_PRIORITY(enumIRQn);
        if(enumHwIrqPriority != _CPU_IRQ_DISABLE)
        {
            __clear_cpu_softirq(enumHwIrqPriority - 1);
        }
    }
}


/** \brief  Get Active Interrupt

    The function reads the active register in NVIC and returns the active bit.

    \param [in]      enumIRQn  Interrupt number.

    \return             0  Interrupt status is not active.
    \return             1  Interrupt status is active.
 */
__STATIC_INLINE uint32_t __NVIC_GetActive(EnumIRQnType enumIRQn)
{
    uint32_t retval = 0;

    if ((SDWORD)(enumIRQn) >= 0)
    {
        EnumCpuIrqPriority enumHwIrqPriority = GET_INT_PRIORITY(enumIRQn);
        if(enumHwIrqPriority != _CPU_IRQ_DISABLE)
        {
            retval = __get_cpu_pending_intr((enumHwIrqPriority - 1));
        }
    }
    return retval;
}


/** \brief  Set Interrupt Priority

    The function sets the priority of an interrupt.

    \note The priority cannot be set for every core interrupt.

    \param [in]      enumIRQn  Interrupt number.
    \param [in]  priority  Priority to set.
 */
__STATIC_INLINE void __NVIC_SetPriority(EnumIRQnType enumIRQn, uint32_t priority)
{
    if ((SDWORD)(enumIRQn) >= 0)
    {
        // PA30000_80_CPU1_INT_PRIORITY_CTRL0
        DWORD ulPriorityRegAddress =  INT_PRIORITY_CTRL_BASE_ADDR + ((((DWORD)enumIRQn) / 8) << 2);
        DWORD ulBitOffset =  (((DWORD)enumIRQn) % 8) << 2;

        bit bGlobalIntStatus = CPU32_GET_GLOBAL_IRQ_STATUS();
        if(bGlobalIntStatus == _ENABLE)
        {
            CPU32_DISABLE_GLOBAL_IRQ();
        }

        if(priority >= _CPU_IRQ_HW_LOWEST_LEVEL)
        {
            priority = priority - _CPU_IRQ_HW_LOWEST_LEVEL;
            (*((volatile DWORD *)(ulPriorityRegAddress))) = ((*((volatile DWORD *)(ulPriorityRegAddress))) & (~((7UL) << ulBitOffset))) | ((priority & (7UL)) << ulBitOffset);
        }
        else
        {
            // Others('b111):INT Disabled
            (*((volatile DWORD *)(ulPriorityRegAddress))) = ((*((volatile DWORD *)(ulPriorityRegAddress))) & (~((7UL) << ulBitOffset))) | ((7UL) << ulBitOffset);
        }

        if(bGlobalIntStatus == _ENABLE)
        {
            CPU32_ENABLE_GLOBAL_IRQ();
        }
    }
}


/** \brief  Get Interrupt Priority

    The function reads the priority of an interrupt. The interrupt
    number can be positive to specify an external (device specific)
    interrupt, or negative to specify an internal (core) interrupt.


    \param [in]   enumIRQn  Interrupt number.
    \return             Interrupt Priority. Value is aligned automatically to the implemented
                        priority bits of the microcontroller.
 */
__STATIC_INLINE uint32_t __NVIC_GetPriority(EnumIRQnType enumIRQn)
{
    DWORD ulPriority = _CPU_IRQ_DISABLE;
    if ((SDWORD)(enumIRQn) >= 0)
    {
        // PA30000_80_CPU1_INT_PRIORITY_CTRL0
        DWORD ulPriorityRegAddress = INT_PRIORITY_CTRL_BASE_ADDR + ((((DWORD)enumIRQn) / 8) << 2);
        DWORD ulBitOffset =  (((uint32_t)enumIRQn) % 8) << 2;
        ulPriority = (((*((volatile DWORD *)(ulPriorityRegAddress))) & ((7UL) << ulBitOffset)) >> ulBitOffset);
        // Input = Native Priority: Low(HW_HIGHEST-SW_INT0 = 7) ~ High(HW_HIGHEST-HW_HIGHEST = 0) , Disable(15)
        // Output= Remap Priority: Low(SW_INT0) ~ High(HW_HIGHEST) , Disable(0)
        ulPriority = GET_REMAP_PRIORITY(ulPriority);
    }
    return ulPriority;
}


/** \brief  Encode Priority

    The function encodes the priority for an interrupt with the given priority group,
    preemptive priority value, and subpriority value.
    In case of a conflict between priority grouping and available
    priority bits (__NVIC_PRIO_BITS), the samllest possible priority group is set.

    \param [in]     PriorityGroup  Used priority group.
    \param [in]   PreemptPriority  Preemptive priority value (starting from 0).
    \param [in]       SubPriority  Subpriority value (starting from 0).
    \return                        Encoded priority. Value can be used in the function \ref NVIC_SetPriority().
 */
__STATIC_INLINE uint32_t __NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  UNUSED(PriorityGroup);
  UNUSED(SubPriority);

  return PreemptPriority;
}


/** \brief  Decode Priority

    The function decodes an interrupt priority value with a given priority group to
    preemptive priority value and subpriority value.
    In case of a conflict between priority grouping and available
    priority bits (__NVIC_PRIO_BITS) the samllest possible priority group is set.

    \param [in]         Priority   Priority value, which can be retrieved with the function \ref NVIC_GetPriority().
    \param [in]     PriorityGroup  Used priority group.
    \param [out] pPreemptPriority  Preemptive priority value (starting from 0).
    \param [out]     pSubPriority  Subpriority value (starting from 0).
 */
__STATIC_INLINE void __NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  UNUSED(PriorityGroup);
  *pPreemptPriority = Priority;
  *pSubPriority = 0;
}


/** \brief  System Reset

    The function initiates a system reset request to reset the MCU.
 */
__STATIC_INLINE void __NVIC_SystemReset(void)
{
  __DSB();                                                     /* Ensure all outstanding memory accesses included
                                                                  buffered write are completed before reset */
  /*
   * do reset stuff
   * not supported now
   */

  __DSB();                                                     /* Ensure completion of memory access */
  while(1){};                                                    /* wait until reset */
}

/*@} end of CMSIS_Core_NVICFunctions */

#ifdef __cplusplus
}
#endif

#endif /* __CORE_RLX_H_DEPENDANT */
#endif /* __CMSIS_GENERIC */
