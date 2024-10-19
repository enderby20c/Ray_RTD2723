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
 * @file     core_tr9.h
 * @brief    CMSIS TR9 Core Peripheral Access Layer Header File
 * @version  V0.0.1
 * @date     04. October 2017
 ******************************************************************************/
/*
 * Copyright (c) 2017 GreenWaves Technologies SAS. All rights reserved.
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

#if defined ( __ICCARM__ )
  #pragma system_include         /* treat file as system include file for MISRA check */
#elif defined (__clang__)
  #pragma clang system_header   /* treat file as system include file */
#endif

#ifndef __CORE_TR9_H_GENERIC
#define __CORE_TR9_H_GENERIC

#ifdef __cplusplus
 extern "C" {
#endif

extern DWORD g_ulTargetSystickCpuTicks;

/*******************************************************************************
 *                 CMSIS definitions
 ******************************************************************************/
/**
  \ingroup RISCV
  @{
 */

/*  CMSIS RISCV definitions */
#define __RISCV_CMSIS_VERSION_MAIN (0U) /*!< [31:16] CMSIS HAL main version */
#define __RISCV_CMSIS_VERSION_SUB (1U)  /*!< [15:0]  CMSIS HAL sub version */
#define __RISCV_CMSIS_VERSION \
    ((__RISCV_CMSIS_VERSION_MAIN << 16U) | __RISCV_CMSIS_VERSION_SUB) /*!< CMSIS HAL version number */

#define __RISCV_V (1U) /*!< RISCV Core Version */

/** __FPU_USED indicates whether an FPU is used or not.
    This core does not support an FPU at all
*/
#define __FPU_USED       0U

#include "cmsis_compiler.h" /* CMSIS compiler specific defines */

#ifdef __cplusplus
}
#endif

#endif /* __CORE_TR9_H_GENERIC */

#ifndef __CMSIS_GENERIC

#ifndef __CORE_RISCV_H_DEPENDANT
#define __CORE_RISCV_H_DEPENDANT

#ifdef __cplusplus
 extern "C" {
#endif

/* check device defines and use defaults */
#if defined __CHECK_DEVICE_DEFINES
  #ifndef __RISCV_REV
    #define __RISCV_REV               0x0000U
    #warning "__RISCV_REV not defined in device header file; using default!"
  #endif

  #ifndef __FPU_PRESENT
    #define __FPU_PRESENT             0U
    #warning "__FPU_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __MPU_PRESENT
    #define __MPU_PRESENT             0U
    #warning "__MPU_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __NVIC_PRIO_BITS
    #define __NVIC_PRIO_BITS          0U
    #warning "__NVIC_PRIO_BITS not defined in device header file; using default!"
  #endif

  #ifndef __Vendor_SysTickConfig
    #define __Vendor_SysTickConfig    0U
    #warning "__Vendor_SysTickConfig not defined in device header file; using default!"
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
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/*@} end of group RISCV */

/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - Core Register
  - Core NVIC Register
  - Core SCB Register
  - Core SysTick Register
  - Core Debug Register
  - Core MPU Register
  - Core FPU Register
******************************************************************************/
/**
   \defgroup CMSIS_core_register Defines and Type Definitions
   \brief Type definitions and defines for RISCV processor based devices.
*/

/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_CORE  Status and Control Registers
  \brief      Core Register type definitions.
  @{
 */
#define MSTATUS_ADDR    0x300             /*!< Mahcine Status Register */
#define MISA_ADDR       0x301             /*!< ISA and Extensions Register */
#define MIE_ADDR        0x304             /*!< Machine Interrupt Enable Register */
#define MTVEC_ADDR      0x305             /*!< Machine Trap-handler Base Address Register */
#define MEPC_ADDR       0x341             /*!< Machine Exception Program Counter Register */
#define MCAUSE_ADDR     0x342             /*!< Machine Trap Cause Register */
#define MTVAL_ADDR      0x343             /*!< Machine Trap Value Register */
#define MIP_ADDR        0x344             /*!< Machine Interrupt Pending Register */

#define MVENDORID_ADDR  0xF11             /*!< Vendor ID Register */
#define MARCHID_ADDR    0xF12             /*!< Architecture ID Register */
#define MIMPID_ADDR     0xF13             /*!< Implementation ID Register */
#define MHARTID_ADDR    0xF14             /*!< Hardware Thread ID Register */

#define PCER_ADDR       0x7A0             /*!< Performance Counter Mode Register */
#define PCMR_ADDR       0x7A1             /*!< Performance Counter Event Register */

#ifndef ASIC

#define PCCR0_ADDR      0x780             /*!< Performance Counter Counter CYCLE Register */
#define PCCR1_ADDR      0x781             /*!< Performance Counter Counter INSTR Register */
#define PCCR2_ADDR      0x782             /*!< Performance Counter Counter LD_STALL Register */
#define PCCR3_ADDR      0x783             /*!< Performance Counter Counter JR_STALL Register */
#define PCCR4_ADDR      0x784             /*!< Performance Counter Counter IMISS Register */
#define PCCR5_ADDR      0x785             /*!< Performance Counter Counter LD Register */
#define PCCR6_ADDR      0x786             /*!< Performance Counter Counter ST Register */
#define PCCR7_ADDR      0x787             /*!< Performance Counter Counter JUMP Register */
#define PCCR8_ADDR      0x788             /*!< Performance Counter Counter BRANCH Register */
#define PCCR9_ADDR      0x789             /*!< Performance Counter Counter BTAKEN Register */
#define PCCR10_ADDR     0x78A             /*!< Performance Counter Counter RVC Register */
#define PCCR11_ADDR     0x78B             /*!< Performance Counter Counter LD_EXT Register */
#define PCCR12_ADDR     0x78C             /*!< Performance Counter Counter ST_EXT Register */
#define PCCR13_ADDR     0x78D             /*!< Performance Counter Counter LD_EXT_CYC Register */
#define PCCR14_ADDR     0x78E             /*!< Performance Counter Counter ST_EXT_CYC Register */
#define PCCR15_ADDR     0x78F             /*!< Performance Counter Counter TCDM_CONT Register */

#endif

#define PCCR31_ADDR     0x79F             /*!< Performance Counter Counter ALL Register */

#define HWLP_S0_ADDR    0x7B0             /*!< Hardware Loop Start0 Register */
#define HWLP_E0_ADDR    0x7B1             /*!< Hardware Loop End0 Register */
#define HWLP_C0_ADDR    0x7B2             /*!< Hardware Loop Count0 Register */
#define HWLP_S1_ADDR    0x7B3             /*!< Hardware Loop Start1 Register */
#define HWLP_E1_ADDR    0x7B4             /*!< Hardware Loop End1 Register */
#define HWLP_C1_ADDR    0x7B5             /*!< Hardware Loop Count1 Register */

#define DMHARTID_ADDR   0x014             /*!< User Unique Hardware Thread ID Register */
#define UEPC_ADDR       0x041             /*!< User Exception Program Counter Register */

#define CPRIV_ADDR      0xC10             /*!< Current Privilege Level Register */
/* Only for FC */
#define USTATUS_FC_ADDR 0x000             /*!< FC User Status Register */
#define UTVEC_FC_ADDR   0x005             /*!< FC User Trap-handler Base Address Register */
#define UCAUSE_FC_ADDR  0x042             /*!< FC User Trap Cause Register */

/**
  \brief  Union type to access the Vendor ID Register (MVENDORID).
 */
typedef union {
  struct {
      uint32_t OFFSET:7; /*!< bit:  0..6   */
      uint32_t BANK:25;  /*!< bit:  7..31  */
  } b;                   /*!< Structure used for bit  access */
  uint32_t w;            /*!< Type      used for word access */
} MVENDORID_Type;

/* MVENDORID Register Definitions */
#define MVENDORID_BANK_Pos 7U                                      /*!< MVENDORID: BANK Position */
#define MVENDORID_BANK_Msk (0x1FFFFFFUL /*<< MVENDORID_BANK_Pos*/) /*!< MVENDORID: BANK Mask */

#define MVENDORID_OFFSET_Pos 0U                                   /*!< MVENDORID: OFFSET Position */
#define MVENDORID_OFFSET_Msk (0x7FUL /*<< MVENDORID_OFFSET_Pos*/) /*!< MVENDORID: OFFSET Mask */


/**
  \brief  Union type to access the Hart ID Register (MHARTID).
 */
typedef union {
    struct {
        uint32_t OFFSET : 5; /*!< bit:  0..4  Hardware thread id */
        uint32_t BANK : 27;  /*!< bit:  5..31 Reserved */
    } b;                     /*!< Structure used for bit  access */
    uint32_t w;              /*!< Type      used for word access */
} MHARTID_Type;
/* MHARTID Register Definitions */
#define MHARTID_BANK_Pos 0U                               /*!< MHARTID: BANK Position */
#define MHARTID_BANK_Msk (0x1FUL /*<< MHARTID_BANK_Pos*/) /*!< MHARTID: BANK Mask */


/**
  \brief  Union type to access the ISA and Extensions Register (MISA).
 */
typedef union {
    struct {
        uint32_t EXTENSION : 26; /*!< bit:  0.. 25  ISA Extension */
        uint32_t WIRI : 4;       /*!< bit:  26..29  Reserved */
        uint32_t MXL : 2;        /*!< bit:  30..31  Machine XLEN */
    } b;                         /*!< Structure used for bit  access */
    uint32_t w;                  /*!< Type      used for word access */
} MISA_Type;

/* MISA Register Definitions */
#define MISA_MXL_Pos 30U                     /*!< MISA: MXL Position */
#define MISA_MXL_Msk (0x3UL << MISA_MXL_Pos) /*!< MISA: MXL Mask */

#define MISA_EXTENSION_Pos 0U                                      /*!< MISA: EXTENSION Position */
#define MISA_EXTENSION_Msk (0x3FFFFFFUL /*<< MISA_EXTENSION_Pos*/) /*!< MISA: EXTENSION Mask */


/**
   \brief  Union type to access the Machine Mode Status Register (MSTATUS).
*/
typedef union {
    struct {
        uint32_t UIE : 1;   /*!< bit:  0       User Interrupt-enable bit */
        uint32_t SIE : 1;   /*!< bit:  1       Supervisor Interrupt-enable bit */
        uint32_t WPRI0 : 1; /*!< bit:  2       Reserved */
        uint32_t MIE : 1;   /*!< bit:  3       Machine Interrupt-enable bit */
        uint32_t UPIE : 1;  /*!< bit:  4       Prior User Interrupt-enable bit on trap */
        uint32_t SPIE : 1;  /*!< bit:  5       Prior Supervisor Interrupt-enable bit on trap */
        uint32_t WPRI1 : 1; /*!< bit:  6       Reserved */
        uint32_t MPIE : 1;  /*!< bit:  7       Prior Machine Interrupt-enable bit on trap */
        uint32_t SPP : 1;   /*!< bit:  8       Supervisor previous privilege value, up to supervisor mode*/
        uint32_t WPRI2 : 2; /*!< bit:  9, 10   Reserved */
        uint32_t MPP : 2;   /*!< bit:  11, 12  Supervise previous privilege value, up to machine mode */
        uint32_t FS : 2;    /*!< bit:  13, 14  Reserved */
        uint32_t XS : 2;    /*!< bit:  15, 16  Reserved */
        uint32_t MPRV : 1;  /*!< bit:  17      Reserved */
        uint32_t SUM : 1;   /*!< bit:  18      Reserved */
        uint32_t MXR : 1;   /*!< bit:  19      Reserved */
        uint32_t TVM : 1;   /*!< bit:  20      Reserved */
        uint32_t TW : 1;    /*!< bit:  21      Reserved */
        uint32_t TSR : 1;   /*!< bit:  22      Reserved */
        uint32_t WPRI3 : 8; /*!< bit:  23..30  Reserved */
        uint32_t SD : 1;    /*!< bit:  31      Reserved */
    } b;                    /*!< Structure used for bit  access */
    uint32_t w;             /*!< Type      used for word access */
} MSTATUS_Type;


/* MSTATUS Register Definitions */
#define MSTATUS_SD_Pos 31U                     /*!< MSTATUS: SD Position */
#define MSTATUS_SD_Msk (1UL << MSTATUS_SD_Pos) /*!< MSTATUS: SD Mask */

#define MSTATUS_TSR_Pos 22U                      /*!< MSTATUS: TSR Position */
#define MSTATUS_TSR_Msk (1UL << MSTATUS_TSR_Pos) /*!< MSTATUS: TSR Mask */

#define MSTATUS_TW_Pos 21U                     /*!< MSTATUS: TW Position */
#define MSTATUS_TW_Msk (1UL << MSTATUS_TW_Pos) /*!< MSTATUS: TW Mask */

#define MSTATUS_TVM_Pos 20U                      /*!< MSTATUS: TVM Position */
#define MSTATUS_TVM_Msk (1UL << MSTATUS_TVM_Pos) /*!< MSTATUS: TVM Mask */

#define MSTATUS_MXR_Pos 19U                      /*!< MSTATUS: MXR Position */
#define MSTATUS_MXR_Msk (1UL << MSTATUS_MXR_Pos) /*!< MSTATUS: MXR Mask */

#define MSTATUS_SUM_Pos 18U                      /*!< MSTATUS: SUM Position */
#define MSTATUS_SUM_Msk (1UL << MSTATUS_SUM_Pos) /*!< MSTATUS: SUM Mask */

#define MSTATUS_MPRV_Pos 17U                       /*!< MSTATUS: MPRV Position */
#define MSTATUS_MPRV_Msk (1UL << MSTATUS_MPRV_Pos) /*!< MSTATUS: MPRV Mask */

#define MSTATUS_XS_Pos 15U                     /*!< MSTATUS: XS Position */
#define MSTATUS_XS_Msk (3UL << MSTATUS_XS_Pos) /*!< MSTATUS: XS Mask */

#define MSTATUS_FS_Pos 13U                     /*!< MSTATUS: FS Position */
#define MSTATUS_FS_Msk (3UL << MSTATUS_FS_Pos) /*!< MSTATUS: FS Mask */

#define MSTATUS_MPP_Pos 11U                      /*!< MSTATUS: MPP Position */
#define MSTATUS_MPP_Msk (3UL << MSTATUS_MPP_Pos) /*!< MSTATUS: MPP Mask */

#define MSTATUS_SPP_Pos 8U                       /*!< MSTATUS: SPP Position */
#define MSTATUS_SPP_Msk (1UL << MSTATUS_SPP_Pos) /*!< MSTATUS: SPP Mask */

#define MSTATUS_MPIE_Pos 7U                        /*!< MSTATUS: MPIE Position */
#define MSTATUS_MPIE_Msk (1UL << MSTATUS_MPIE_Pos) /*!< MSTATUS: MPIE Mask */

#define MSTATUS_SPIE_Pos 5U                        /*!< MSTATUS: SPIE Position */
#define MSTATUS_SPIE_Msk (1UL << MSTATUS_SPIE_Pos) /*!< MSTATUS: SPIE Mask */

#define MSTATUS_UPIE_Pos 4U                        /*!< MSTATUS: UPIE Position */
#define MSTATUS_UPIE_Msk (1UL << MSTATUS_UPIE_Pos) /*!< MSTATUS: UPIE Mask */

#define MSTATUS_MIE_Pos 3U                       /*!< MSTATUS: MIE Position */
#define MSTATUS_MIE_Msk (1UL << MSTATUS_MIE_Pos) /*!< MSTATUS: MIE Mask */

#define MSTATUS_SIE_Pos 1U                       /*!< MSTATUS: SIE Position */
#define MSTATUS_SIE_Msk (1UL << MSTATUS_SIE_Pos) /*!< MSTATUS: SIE Mask */

#define MSTATUS_UIE_Pos 0U                             /*!< MSTATUS: UIE Position */
#define MSTATUS_UIE_Msk (1UL /* << MSTATUS_UIE_Pos */) /*!< MSTATUS: UIE Mask */

/**
  \brief  Union type to access the Machine Trap-Vector Baser-Address Register (MTVEC).
 */
typedef union {
    struct {
        uint32_t MODE : 2;  /*!< bit:  0..1  vector mode */
        uint32_t BASE : 30; /*!< bit:  2..31 vector base address */
    } b;                    /*!< Structure used for bit  access */
    uint32_t w;             /*!< Type      used for word access */
} MTVEC_Type;

/* MTVEC Register Definitions */
#define MTVEC_BASE_Pos 2U                               /*!< MTVEC: BASE Position */
#define MTVEC_BASE_Msk (0x3FFFFFFFUL << MTVEC_BASE_Pos) /*!< MTVEC: BASE Mask */

#define MTVEC_MODE_Pos 0U                            /*!< MTVEC: MODE Position */
#define MTVEC_MODE_Msk (0x3UL /*<< MTVEC_MODE_Pos*/) /*!< MTVEC: MODE Mask */


/**
  \brief  Union type to access the Machine Trap Cause Register (MCAUSE).
 */
typedef union {
    struct {
        uint32_t EC : 31; /*!< bit: 0..30  Exception code */
        uint32_t IRQ : 1; /*!< bit:  31 Interrupt flag */
    } b;                  /*!< Structure used for bit  access */
    uint32_t w;           /*!< Type      used for word access */
} MCAUSE_Type;

/* MCAUSE Register Definitions */
#define MCAUSE_IRQ_Pos 31U                       /*!< MCAUSE: IRQ Position */
#define MCAUSE_IRQ_Msk (0x1UL << MCAUSE_IRQ_Pos) /*!< MCAUSE: IRQ Mask */

#define MCAUSE_EC_Pos 0U                                  /*!< MCAUSE: EC Position */
#define MCAUSE_EC_Msk (0x1FFFFFFFUL /*<< MCAUSE_EC_Pos*/) /*!< MCAUSE: EC Mask */



/*@} */


/*******************************************************************************
 *                Hardware Abstraction Layer
  Core Function Interface contains:
  - Core NVIC Functions
  - Core SysTick Functions
  - Core Debug Functions
  - Core Register Access Functions
 ******************************************************************************/
/**
  \defgroup CMSIS_Core_FunctionInterface Functions and Instructions Reference
*/

/* ##########################   NVIC functions  #################################### */
/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_Core_NVICFunctions NVIC Functions
  \brief    Functions that manage interrupts and exceptions via the NVIC.
  @{
 */

#define MXLEN                         32    // RISC-V-32

#define PLATFORM_INT_CTRLER_EN        0
#if defined(PLATFORM_INT_CTRLER_EN) && PLATFORM_INT_CTRLER_EN
#include "plic.h"
#else
/* if PLIC is not supported, PLIC interrupt number should be 0 */
#define PLIC_INT_NUMBER               0
#endif

#define MAX_SYSTEM_EXECPTION_NUM      16
#define MAX_CORE_EXCEPTION_NUM        16
#define MAX_USER_EXCEPTION_NUM        (MAX_CORE_EXCEPTION_NUM + PLIC_INT_NUMBER)
#define MAX_VECTOR_TABLE_NUM          (MAX_SYSTEM_EXECPTION_NUM + MAX_USER_EXCEPTION_NUM + PLIC_INT_NUMBER)

#define NVIC_USER_IRQ_OFFSET          MAX_SYSTEM_EXECPTION_NUM
#define NVIC_PLIC_IRQ_OFFSET          (MAX_SYSTEM_EXECPTION_NUM + MAX_CORE_EXCEPTION_NUM)
#define NVIC_M_IRQ_OFFSET             32

#define RISCV_ARCH_SYS_TIMER 1 // use RISC-V ARchi timer as SysTick Timer
#define EXT_DW_TIMER 2         // use external DW timer as SysTick Timer

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

/* Interrupt Priorities are WORD accessible only under ARMv6M                   */
/* The following MACROS handle generation of the register offset and byte masks */
#define _BIT_SHIFT(IRQn)         (  ((((uint32_t)(int32_t)(IRQn))         )      &  0x03UL) * 8UL)
#define _SHP_IDX(IRQn)           ( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >>    2UL)      )
#define _IP_IDX(IRQn)            (   (((uint32_t)(int32_t)(IRQn))                >>    2UL)      )

/**
  \brief   Set Interrupt Vector
  \details Sets an interrupt vector in SRAM based interrupt vector table.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
           VTOR must been relocated to SRAM before.
  \param [in]   enumIRQn      Interrupt number
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
  \param [in]   enumIRQn      Interrupt number.
  \return                 Address of interrupt handler function
 */
__STATIC_INLINE uint32_t __NVIC_GetVector(EnumIRQnType enumIRQn)
{
  // return __isr_get_vector(enumIRQn);
  /* Not supported */
  UNUSED(enumIRQn);
  return 0;
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
    else
    {
        switch(enumIRQn)
        {
            case _IRQN_MTI:
                // set MTIE = 1
                __csr_set(mie, (1 << (uint32_t)(mie_bit_mtie)));
                break;
            case _IRQN_MSI:
                // set MSIE = 1
                __csr_set(mie, (1 << (uint32_t)(mie_bit_msie)));
                break;
            case _IRQN_MEI:
                // set MEIE = 1
                __csr_set(mie, (1 << (uint32_t)(mie_bit_meie)));
                break;
            default:
                break;
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
    else
    {
        switch(enumIRQn)
        {
            case _IRQN_MTI:
                // set MTIE = 0
                __csr_clear(mie, (1 << (uint32_t)(mie_bit_mtie)));
                break;
            case _IRQN_MSI:
                // set MSIE = 0
                __csr_clear(mie, (1 << (uint32_t)(mie_bit_msie)));
                break;
            case _IRQN_MEI:
                // set MEIE = 0
                __csr_clear(mie, (1 << (uint32_t)(mie_bit_meie)));
                break;
            default:
                break;
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
        EnumCpuIrqPriority enumHwIrqPriority = GET_INT_PRIORITY(enumIRQn);
        if(enumHwIrqPriority != _CPU_IRQ_DISABLE)
        {
            retval = __get_irq_enable(mie_bit_cie7 - (enumHwIrqPriority - _CPU_IRQ_SW_LEVEL_0));
        }


        DWORD ulPriorityRegAddress =  INT_PRIORITY_CTRL_BASE_ADDR + ((((DWORD)enumIRQn) / 8) << 2);
        DWORD ulBitOffset =  (((DWORD)enumIRQn) % 8) << 2;
        retval = (*((volatile DWORD *)(ulPriorityRegAddress))) & ((1UL << 3) << ulBitOffset);
    }
    else
    {
        switch(enumIRQn)
        {
            case _IRQN_MTI:
                // get (MTIE)
                retval = __get_irq_enable(mie_bit_mtie);
                break;
            case _IRQN_MSI:
                // get (MSIE)
                retval = __get_irq_enable(mie_bit_msie);
                break;
            case _IRQN_MEI:
                // get (MEIE)
                retval = __get_irq_enable(mie_bit_meie);
                break;
            default:
                break;
        }
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
            retval = __get_irq_pending(mip_bit_cip7 - (enumHwIrqPriority - _CPU_IRQ_SW_LEVEL_0));
        }
    }
    else
    {
        switch(enumIRQn)
        {
            case _IRQN_MTI:
                // get (MTIP)
                retval = __get_irq_pending(mip_bit_mtip);
                break;
            case _IRQN_MSI:
                // get (MSIP)
                retval = __get_irq_pending(mip_bit_msip);
                break;
            case _IRQN_MEI:
                // get (MEIP)
                retval = __get_irq_pending(mip_bit_meip);
                break;
            default:
                break;
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
        switch(enumHwIrqPriority)
        {
            case _CPU_IRQ_SW_LEVEL_0:
                SET_SW_INT0();
                break;
            case _CPU_IRQ_SW_LEVEL_1:
                SET_SW_INT1();
                break;
            default:
                break;
        }
    }
    else
    {
        switch(enumIRQn)
        {
            case _IRQN_MSI:
                // set MSIP = 1
                SET_SYSCALL();
                break;
            default:
                break;
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
        switch(enumHwIrqPriority)
        {
            case _CPU_IRQ_SW_LEVEL_0:
                CLEAR_SW_INT0();
                break;
            case _CPU_IRQ_SW_LEVEL_1:
                CLEAR_SW_INT1();
                break;
            default:
                break;
        }
    }
    else
    {
        switch(enumIRQn)
        {
            case _IRQN_MSI:
                // set MSIP = 1
                CLEAR_SYSCALL();
                break;
            default:
                break;
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
            // get (CIE[i] & CIP[i])
            retval = __get_irq_active(mie_bit_cie7 - (enumHwIrqPriority - _CPU_IRQ_SW_LEVEL_0));
        }
    }
    else
    {
        switch(enumIRQn)
        {
            case _IRQN_MTI:
                // get (MTIE & MTIP)
                retval = __get_irq_active(mie_bit_mtie);
                break;
            case _IRQN_MSI:
                // get (MSIE & MSIP)
                retval = __get_irq_active(mie_bit_msie);
                break;
            case _IRQN_MEI:
                // get (MEIE & MEIP)
                retval = __get_irq_active(mie_bit_meie);
                break;
            default:
                break;
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
  while(1);                                                    /* wait until reset */
}

/**
  \brief   Refresh 48bits TR9 Internal Timer MTIMECMP
  \details Refresh 48bits TR9 Internal Timer MTIMECMP
  \param [in]  None
  \return  None
  \note    Need Execute MachineTimer_Init first
 */
__STATIC_INLINE void MTimer_RefreshCMP()
{
    // internal RISCV Arch Timer
    // assert MTINT when {timeh, time} >= {timecmph, timecmp}
    // MTIME_L_REG      : Low 32 bits of 48-bits timer (Reset = 0)
    // MTIME_H_REG      : High 16 bits of 48-bits timer (Reset = 0)
    // MTIMECMP_L_REG   : Low 32 bits of 48-bits timer compare (Reset = 0xffffffff)
    // MTIMECMP_H_REG   : High 16 bits of 48-bits timer compare (Reset = 0x0000ffff)
    // MSI_TRIGGER_REG  : 1 bit Machine software interrupt (Reset = 0, write 1 to assert MSINT, write 0 to deassert)
    Scaler32SetDWord(MTIME_H_REG, 0);
    Scaler32SetDWord(MTIME_L_REG, 0);

    Scaler32SetDWord(MTIMECMP_H_REG, 0);
    Scaler32SetDWord(MTIMECMP_L_REG, g_ulTargetSystickCpuTicks);
}


/**
  \brief   Get Current 48bits TR9 Internal Timer Count Value
  \details Get Current 48bits TR9 Internal Timer Count Value(MTIME)
  \param [in]  None
  \return  48bits MTIME value
  \note    None
 */
__STATIC_INLINE QWORD MTimer_GetCurrent()
{
    DWORD ulCurrentTimeHigh, ulCurrentTimeLow;
    do
    {
        ulCurrentTimeHigh = Scaler32GetDWord(MTIME_H_REG);
        ulCurrentTimeLow = Scaler32GetDWord(MTIME_L_REG);
    }
    while (ulCurrentTimeHigh != Scaler32GetDWord(MTIME_H_REG));

    return (((QWORD)(ulCurrentTimeHigh & 0x0000FFFF)) << 32) | ((QWORD)ulCurrentTimeLow);
}


/**
  \brief   System Tick Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  cpu_ticks  Number of ticks between two interrupts.
  \return  None
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
__STATIC_INLINE void MTimer_Init(uint32_t cpu_ticks)
{
    g_ulTargetSystickCpuTicks = cpu_ticks;

    MTimer_RefreshCMP();

    // Enable TR9 Internal Timer Clk
    Scaler32SetBit(TR9_MTIME_CLK_EN_ADDR, ~_BIT18, _BIT18);
}



/*@} end of CMSIS_Core_NVICFunctions */

/* ##########################   CORE ID functions  #################################### */
/**
  \ingroup  CMSIS_Core_IDFunctionInterface
  \defgroup CMSIS_Core_IDFunctions ID Functions
  \brief    Functions that manage Cluster and Core ID.
  @{
 */

__attribute__((always_inline)) __STATIC_INLINE uint32_t __core_ID()
{
    int hart_id;

    __ASM volatile ("csrr %0, 0x014" : "=r" (hart_id) : );
    return hart_id & 0x1f;
}

__attribute__((always_inline)) __STATIC_INLINE uint32_t __cluster_ID()
{
    int hart_id;

    __ASM volatile ("csrr %0, 0x014" : "=r" (hart_id) : );
    return (hart_id >> 5) & 0x3f;
}

/*@} end of CMSIS_Core_IDFunctions */


#ifdef __cplusplus
}
#endif

#endif /* __CORE_RISCV_H_DEPENDANT */

#endif /* __CMSIS_GENERIC */
