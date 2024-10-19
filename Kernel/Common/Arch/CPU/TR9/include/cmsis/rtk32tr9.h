/********************************************************************************/
/*   Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.        */
/*                                                                              */
/*   SPDX-License-Identifier: LicenseRef-Realtek-Proprietary                    */
/*                                                                              */
/*   This software component is confidential and proprietary to Realtek         */
/*   Semiconductor Corp. Disclosure, reproduction, redistribution, in whole     */
/*   or in part, of this work and its derivatives without express permission    */
/*   is prohibited.                                                             */
/********************************************************************************/

/**************************************************************************//**
 * @file     rtk32tr9.h
 * @brief    CMSIS RISCV# Core Peripheral Access Layer Header File for
 *           Device rtk32rx3081
 * @version  V3.10
 * @date     23. November 2012
 *
 * @note
 *
 ******************************************************************************/


#ifndef Device_RTK32_TR9_H      /* ToDo: replace '<Device>' with your device name */
#define Device_RTK32_TR9_H

#if defined(DEBUG)
#define _JTAG_DEBUG                         _ON
#else
#define _JTAG_DEBUG                         _OFF
#endif

#define TR9

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
#define __MPU_PRESENT                       1       /*!< MPU(PMP) present or not                               */

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */
#define _CPU_IRQ_DISABLE_VALUE          (7)

#define INT_PRIORITY_CTRL_BASE_ADDR     (0xA3000080)
#define INT_PENDING_STATUS_ADDR         (0xA3000040)
#define TR9_MTIME_CLK_EN_ADDR           (0xA3000000)

/* ----------------------------------------------------------------------------
   --MTIME register offset
   ---------------------------------------------------------------------------- */
/* internal RISCV Arch Timer */
/* assert MTINT when {timeh, time} >= {timecmph, timecmp} */
#define TIMER_BASE_ADDR                 (0xE0000000)                // 1KB range from TIMER_BASE will be reserved in core (0xE0000000 ~ (0xE00003FF))
#define MTIME_L_REG                     (TIMER_BASE_ADDR + 0x00)    // Low 32 bits of 48-bits timer (Reset = 0)
#define MTIME_H_REG                     (TIMER_BASE_ADDR + 0x04)    // High 16 bits of 48-bits timer (Reset = 0)
#define MTIMECMP_L_REG                  (TIMER_BASE_ADDR + 0x08)    // Low 32 bits of 48-bits timer compare (Reset = 0xffffffff)
#define MTIMECMP_H_REG                  (TIMER_BASE_ADDR + 0x0C)    // High 16 bits of 48-bits timer compare (Reset = 0x0000ffff)
#define MSI_TRIGGER_REG                 (TIMER_BASE_ADDR + 0x10)    // 1 bit Machine software interrupt (Reset = 0, write 1 to assert MSINT, write 0 to deassert)

extern EnumCpuIrqPriority const tINTERRUPT_PRIORITY_TR9[];

#define GET_INT_PRIORITY(enumIRQnTypeIdx)       (tINTERRUPT_PRIORITY_TR9[enumIRQnTypeIdx])

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

#define SET_SYSCALL()                       {\
                                                Scaler32SetDWord(MSI_TRIGGER_REG, 1);\
                                                while(Scaler32GetDWord(MSI_TRIGGER_REG));\
                                            }
#define CLEAR_SYSCALL()                     {Scaler32SetDWord(MSI_TRIGGER_REG, 0);}

#define SET_SW_INT0()                       {SET_SCPU_SW_INT0();}
#define CLEAR_SW_INT0()                     {\
                                                Scaler32SetDWord(TR9_SW_INT0_CTRL_ADDR, 0);\
                                                Scaler32GetDWord(TR9_SW_INT0_CTRL_ADDR);\
                                            }

#define SET_SW_INT1()                       {SET_SCPU_SW_INT1();}
#define CLEAR_SW_INT1()                     {\
                                                Scaler32SetDWord(TR9_SW_INT1_CTRL_ADDR, 0);\
                                                Scaler32GetDWord(TR9_SW_INT1_CTRL_ADDR);\
                                            }


#define SET_PENDSV_EVENT()                  (SET_SW_INT0())
#define CLEAR_PENDSV_EVENT()                (CLEAR_SW_INT0())


// Instruction sync. Barrier,will confirm all instruction execute done and flush pipeline
#define ASM_ISB()                           (__ISB())

// Data memory Barrier,will confirm memory op execute done (but not promise clear write buffer and sync to last memory,still need clean op for cache sync), then commit the memory op inst. after it.
#define ASM_DMB()                           (__DMB())

// Data synchronization Barrier,will confirm memory op execute && sync done (will clear write buffer(to cache) ,but not promise sync to last memory,still need clean op for cache sync), then execute the inst. after it.
#define ASM_DSB()                           (__DSB())

#define CSR_WRITE_WITH_DSB(csr, value)      {\
                                                __csr_write(csr, value);\
                                                ASM_DSB();\
                                            }

#define CSR_SET_WITH_DSB(csr, bits)         {\
                                                __csr_set(csr, bits);\
                                                ASM_DSB();\
                                            }

#define CSR_CLEAR_WITH_DSB(csr, bits)       {\
                                                __csr_clear(csr, bits);\
                                                ASM_DSB();\
                                            }


// IRQ_PRIORITY: _CPU_IRQ_SW_LEVEL_0 ~ _CPU_IRQ_HW_LEVEL_5
// Input = Priority: Low(SW_INT0) ~ High(HW_HIGHEST) , Disable(0)
#define SET_BASE_PRIORITY(IRQ_PRIORITY)     (__set_BASEPRI(IRQ_PRIORITY))
// Output = Remap Priority: Low(SW_INT0) ~ High(HW_HIGHEST) , Disable(0)
#define GET_BASE_PRIORITY()                 (__get_BASEPRI())

#define CPU32_ENABLE_GLOBAL_IRQ()           (__enable_irq())

#define CPU32_DISABLE_GLOBAL_IRQ()          (__disable_irq())

#define CPU32_GET_GLOBAL_IRQ_STATUS()       ((__get_MSTATUS() & MSTATUS_MIE) ? _ENABLE : _DISABLE)

#define CPU32_IS_INSIDE_INTERRUPT()         ((__csr_read(0x304) == 0x00FF0888) ? _FALSE : _TRUE)

#define SET_VTOR(ulValue)                   (__set_MTVEC((uint32_t)(ulValue), 1))


#define SET_IMEM_RANGE(ulIWBase0,ulIWTop0)  {\
                                                __csr_write(0x7D0, (ulIWBase0));\
                                                __csr_write(0x7D1, (ulIWTop0));\
                                                ASM_DSB();\
                                            }

#define IMEM_FILL_AND_ENABLE()              (CSR_SET_WITH_DSB(0x7C0, MCCTL0_IMEM0FILL))
#define ENABLE_ITCM()                       (CSR_SET_WITH_DSB(0x7C1, MCCTL1_IMEM0_EN))
#define RESET_I_CACHE()                     (CSR_SET_WITH_DSB(0x7C0, MCCTL0_IINV))
#define RESET_D_CACHE()                     (CSR_SET_WITH_DSB(0x7C0, MCCTL0_DWBINV))


#define CLEAN_D_CACHE()                     {\
                                                if(CPU32_GET_GLOBAL_IRQ_STATUS() == _ENABLE)\
                                                {\
                                                    CPU32_DISABLE_GLOBAL_IRQ();\
                                                    CSR_SET_WITH_DSB(0x7C0, MCCTL0_DWB);\
                                                    CPU32_ENABLE_GLOBAL_IRQ();\
                                                }\
                                                else\
                                                {\
                                                    CSR_SET_WITH_DSB(0x7C0, MCCTL0_DWB);\
                                                }\
                                            }
#define ENABLE_I_D_CACHE()                  (CSR_SET_WITH_DSB(0x7C1, (MCCTL1_DCACHE_EN | MCCTL1_ICACHE_EN)))
#define ENABLE_I_CACHE()                    (CSR_SET_WITH_DSB(0x7C1, (MCCTL1_ICACHE_EN)))
#define ENABLE_D_CACHE()                    (CSR_SET_WITH_DSB(0x7C1, (MCCTL1_DCACHE_EN)))
#define DISABLE_I_CACHE()                   (CSR_CLEAR_WITH_DSB(0x7C1, (MCCTL1_ICACHE_EN)))
#define DISABLE_D_CACHE()                   (CSR_CLEAR_WITH_DSB(0x7C1, (MCCTL1_DCACHE_EN)))


#define TR9_DDR_CACHEABLE()                 (__csr_write(0x7C3, (__csr_read(0x7C3) & (0xFFFF0FFF))))
#define TR9_DDR_UNCACHEABLE()               (__csr_write(0x7C3, ((__csr_read(0x7C3) & (0xFFFF0FFF))|0x00008000)))
#define TR9_FLASH_CACHEABLE()               (__csr_write(0x7C3, (__csr_read(0x7C3) & (0xFFFFFFF0))))
#define TR9_FLASH_UNCACHEABLE()             (__csr_write(0x7C3, ((__csr_read(0x7C3) & (0xFFFFFFF0))|0x00000008)))


// ===========================================================================================================================================================
// TYPE                    B_ADDR      E_ADDR        size    MCCA                       PMP Config(Kernel)      PMP Config(Boot)
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Flash                   0x00000000  0x1FFFFFFF  512MB     CCA0,(0x0) Cacheable       pmp0cfg (R/X)           Default (R/W/X)
// ITCM                    0x20000000  0x20001FFF  8KB       CCA1,(0x0) Cacheable       pmp0cfg (R/X)           Default (R/W/X)
// DTCM                    0x30000000  0x30000FFF  4KB       CCA1,(0x0) Cacheable       Default (R/W/X)         Default (R/W/X)
// Reserved                0x40000000  0x5FFFFFFF  512MB     CCA2,(0x8) Non-Cacheable   Default (R/W/X)         Default (R/W/X)
// DDR RAM TEXT            0x60000000  0x601FFFFF  2MB       CCA3,(0x1) Cacheable+WA    pmp1cfg (R/X)           Default (R/W/X)
// DDR RAM DATA            0x60200000  0x603FFFFF  2MB       CCA3,(0x1) Cacheable+WA    pmp2cfg (R/W/X)         Default (R/W/X)
// DDR_Protected           0x60400000  0x6FFFFFFF  252MB     CCA3,(0x1) Cacheable+WA    pmp3cfg (R)             Default (R/W/X)
// Reserved                0x70000000  0x7FFFFFFF  256MB     CCA3,(0x1) Cacheable+WA    Default (R/W/X)         Default (R/W/X)
// Reserved                0x80000000  0x9FFFFFFF  512MB     CCA4,(0x8) Non-Cacheable   Default (R/W/X)         Default (R/W/X)
// XDATA ScalerReg         0xA0000000  0xA1FFFFFF            CCA5,(0x8) Non-Cacheable   Default (R/W/X)         Default (R/W/X)
// Peripheral ScalerReg    0xA2000000  0xA2FFFFFF            CCA5,(0x8) Non-Cacheable   Default (R/W/X)         Default (R/W/X)
// CPU Specific ScalerReg  0xA3000000  0xAFFFFFFF            CCA5,(0x8) Non-Cacheable   Default (R/W/X)         Default (R/W/X)
// 32bits ScalerReg        0xB0000000  0xBEFFFFFF            CCA5,(0x8) Non-Cacheable   Default (R/W/X)         Default (R/W/X)
// ROM                     0xBFC00000  0xBFFFFFFF  4MB       CCA5,(0x8) Non-Cacheable   Default (R/W/X)         Default (R/W/X)
// Reserved                0xC0000000  0xDFFFFFFF  512MB     CCA6,(0x8) Non-Cacheable   Default (R/W/X)         Default (R/W/X)
// TR9 Internal Timer      0xE0000000  0xE0000013  20        CCA7,(0x8) Non-Cacheable   Default (R/W/X)         Default (R/W/X)
// Reserved                0xE0000014  0xFFFFFFFF  512MB-20  CCA7,(0x8) Non-Cacheable   Default (R/W/X)         Default (R/W/X)
// ===========================================================================================================================================================
// PMP_R                   (_BIT0)             // PMP entry permits Read
// PMP_W                   (_BIT1)             // PMP entry permits Write
// PMP_X                   (_BIT2)             // PMP entry permits Execute
// PMP_A_DISABLE           (0)                 // Disable PMP Entry
// PMP_A_TOR               (_BIT3)             // pmpaddr[i-1] <= PMP[i]'s Address < pmpaddr[i]
// PMP_A_NA4               (_BIT4)             // Address Natural Aligned 4 Bytes Region
// PMP_A_NAPOT             (_BIT4 | _BIT3)     // Address Natural Aligned Power Of Two Region
// PMP_L                   (_BIT7)             // LOCK PMP Setting
//
// PMP Priority:
// PMP[0] > PMP[1] > PMP[2] > PMP[3] > PMP[4] > PMP[5] > PMP[6] > PMP[7]
#define PMP0CFG_VALUE_RX                    (PMP_A_TOR | PMP_X | PMP_R)                             // FLASH+ITCM
#define PMP0CFG_VALUE_RWX                   (PMP_A_TOR | PMP_X | PMP_W | PMP_R)                     // FLASH+ITCM
#define PMP0ADDR_VALUE_ITCM_RX              ((_ITCM_E_ADDRESS + 1) / 4)                             // 0x0000_0000 ~ 0x2000_1FFF
#define PMP0ADDR_VALUE_ITCM_RWX             ((_ITCM_B_ADDRESS) / 4)                                 // 0x0000_0000 ~ 0x2000_0000

#define PMP1CFG_VALUE                       (PMP_L | PMP_A_NAPOT | PMP_X | PMP_R)                   // DDR_RAM_TEXT
#define PMP1ADDR_VALUE                      ((_SCPU_DDR_TEXT_BASE_ADDR / 4) | (0x001FFFFF >> 3))    // 0x6000_0000 ~ 0x601F_FFFF

#define PMP2CFG_VALUE                       (PMP_L | PMP_A_NAPOT | PMP_W | PMP_R)                   // DDR_RAM_DATA
#define PMP2ADDR_VALUE                      ((_SCPU_DDR_DATA_BASE_ADDR / 4) | (0x001FFFFF >> 3))    // 0x6020_0000 ~ 0x603F_FFFF

#define PMP3CFG_VALUE                       (PMP_L | PMP_A_TOR | PMP_W | PMP_R)                     // DDR_RAM_PROTECT
#define PMP3ADDR_VALUE                      (_SCPU_DDR_MAX_ADDR / 4)                                // 0x6040_0000 ~ 0x6FFF_FFFF

#define PMP4CFG_VALUE                       (PMP_L | PMP_A_DISABLE | PMP_W | PMP_R)                 // 32B REG (RBUS/RBUSD)
#define PMP4ADDR_VALUE                      (_DEVICE_16BSCALERIP_BASE_ADDR / 4)                     // 0xA000_0000

#define PMP5CFG_VALUE                       (PMP_L | PMP_A_TOR | PMP_W | PMP_R)                     // 32B REG (RBUS/RBUSD)
#define PMP5ADDR_VALUE                      ((0xBEFFFFFF) / 4)                                      //  ~ 0xBEFF_FFFF

#define PMP6CFG_VALUE                       (PMP_L | PMP_A_NAPOT | PMP_R)                           // ROM
#define PMP6ADDR_VALUE                      ((_ROM_CODE_BASE_ADDR / 4) | (0x0000FFFF >> 3))         // 0xBFC0_0000 ~ 0xBFC0_FFFF

#define PMP7CFG_VALUE                       (PMP_L | PMP_A_NAPOT | PMP_W | PMP_R)                   // TR9 Internal Timer
#define PMP7ADDR_VALUE                      ((TIMER_BASE_ADDR / 4) | (0x000003FF >> 3))             // 0xE000_0000 ~ 0xE000_03FF

#ifdef CPU32_BOOTLOADER
#define CACHE_CONTROL_INIT()                ({\
                                                /* Disable IMEM0 && Enable IMEM RWbyFW && Enable DMEM0 && Disable I-Cache/D-Cache && Setup Cache Policy && Enable WriteBuffer && Enable Wait previous writes are all responded */\
                                                __csr_write(0x7C1, (MCCTL1_UCRD_WAIT_WRT_EN | MCCTL1_LUBUF_EN | MCCTL1_NONBLOCK_LD_EN | MCCTL1_MERGE_UC_NO | MCCTL1_FAST_WB_EN | MCCTL1_WRT_BUF_EN | MCCTL1_WB_MERGE_YES | MCCTL1_GWALLOC_WA | MCCTL1_DMEM0_EN | MCCTL1_LD_ST_IMEM0));\
                                                /* MCCA Cache Attribute Init */\
                                                __csr_write(0x7C3,(0x88881800));\
                                                /* PMP Entry Init (Disable All PMP Entry, Default R/W/X ) */\
                                                __csr_write(0x3A0,(0));\
                                                __csr_write(0x3A1,(0));\
                                            })

#else
#define CACHE_CONTROL_INIT()
#endif

#if (__MPU_PRESENT == 1U)

// real ic
#ifdef CPU32_BOOTLOADER
// Bootloader PMP setting
#define MPU_SETUP_CPU32_USE_REGION()
#define MPU_SETUP_ITCM_REGION(enumCpu32MpuAccessPermission)
#else
// Kernel PMP setting
#define MPU_SETUP_CPU32_USE_REGION()        ({\
                                                __csr_write(0x3B0, PMP0ADDR_VALUE_ITCM_RX);\
                                                __csr_write(0x3B1, PMP1ADDR_VALUE);\
                                                __csr_write(0x3B2, PMP2ADDR_VALUE);\
                                                __csr_write(0x3B3, PMP3ADDR_VALUE);\
                                                __csr_write(0x3B4, PMP4ADDR_VALUE);\
                                                __csr_write(0x3B5, PMP5ADDR_VALUE);\
                                                __csr_write(0x3B6, PMP6ADDR_VALUE);\
                                                __csr_write(0x3B7, PMP7ADDR_VALUE);\
                                                __csr_write(0x3A0, ((PMP3CFG_VALUE << 24) | (PMP2CFG_VALUE << 16) | (PMP1CFG_VALUE << 8) | (PMP0CFG_VALUE_RX << 0)));\
                                                __csr_write(0x3A1, ((PMP7CFG_VALUE << 24) | (PMP6CFG_VALUE << 16) | (PMP5CFG_VALUE << 8) | (PMP4CFG_VALUE << 0)));\
                                                ASM_ISB();\
                                            })

#define MPU_SETUP_ITCM_REGION(enumCpu32MpuAccessPermission)\
                                            ({\
                                                if((enumCpu32MpuAccessPermission == _MPU_REGION_R_ONLY_PRIVILEGED_ONLY) ||\
                                                   (enumCpu32MpuAccessPermission == _MPU_REGION_R_ONLY_ALL))\
                                                {\
                                                    /* Read Only */\
                                                    __csr_write(0x3B0, PMP0ADDR_VALUE_ITCM_RX);\
                                                }\
                                                else\
                                                {\
                                                    /* R/W ok */\
                                                    __csr_write(0x3B0, PMP0ADDR_VALUE_ITCM_RWX);\
                                                }\
                                                ASM_DSB();\
                                            })
#endif

#else
#define MPU_SETUP_CPU32_USE_REGION()
#define MPU_SETUP_ITCM_REGION(enumCpu32MpuAccessPermission)
#endif

#define SYSTICK_CONFIG(ulTicksNumb)         (ScalerTimerInitTimer(_CPU_TIMER_3, _TIMER_X_TIMER_MODE, (ulTicksNumb), _ENABLE, _TIMER_X_INT_ENABLE))
#define SYSTICK_DISABLE_INTERRUPT()         (ScalerTimerSetINTEn(_CPU_TIMER_3, _TIMER_X_INT_DISABLE))
#define SYSTICK_ENABLE_INTERRUPT()          (ScalerTimerSetINTEn(_CPU_TIMER_3, _TIMER_X_INT_ENABLE))
#define SYSTICK_GET_CURRENT_VALUE()         (ScalerTimerGetCurrentValue(_CPU_TIMER_3))
#define SYSTICK_GET_RELOAD_VALUE()          (ScalerTimerGetTargetValue(_CPU_TIMER_3))



#define IMEM_WRITE(ulAddr, ulData)          {Scaler32SetDWord((ulAddr), (ulData));}

#define IMEM_READ(ulAddr)                   (Scaler32GetDWord((ulAddr)))

// TR9 Default exception handlers.
// pulBuf[7] = {MSTATUS, MCAUSE, MEPC, MTVAL, MIE, MIP, MTVEC}
#define TRAP_DUMP(pulBuf)                   ({\
                                                (pulBuf)[0] = __csr_read(0x300); /* MSTATUS_ADDR */\
                                                (pulBuf)[1] = __csr_read(0x342); /* MCAUSE_ADDR  */\
                                                (pulBuf)[2] = __csr_read(0x341); /* MEPC_ADDR    */\
                                                (pulBuf)[3] = __csr_read(0x343); /* MTVAL_ADDR   */\
                                                (pulBuf)[4] = __csr_read(0x304); /* MIE_ADDR     */\
                                                (pulBuf)[5] = __csr_read(0x344); /* MIP_ADDR     */\
                                                (pulBuf)[6] = __csr_read(0x305); /* MTVEC_ADDR   */\
                                            })

#if defined(DEBUG)
#define __DEBUG_BKPT()                      asm volatile ("ebreak")
#endif

#ifndef   __ALWAYS_INLINE
#define __ALWAYS_INLINE                     __attribute__((always_inline))
#endif

// SVC_M_N
//     M:parameter number
//       N: 0:no return;1:have return value
__ALWAYS_INLINE static inline void SVC_Call(void * funcPtr)
{
    DWORD funcPtr_val = (DWORD)(funcPtr);
    asm volatile ("mv     a0, %0" : : "rK"(funcPtr_val) : "a0");
    SET_SYSCALL();
}


/**
  * @}
  */
#include "tr9_math.h"

#ifdef __cplusplus
}
#endif

#endif  /* Device_RTK32_TR9_H */
