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
 * @version  V5.0.4
 * @date     09. April 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
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


#define __RISCV_ARCH__ 1
/* ignore some GCC warnings */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"

/* Fallback for __has_builtin */
#ifndef __has_builtin
  #define __has_builtin(x) (0)
#endif

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
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif
#ifndef   __NO_RETURN
  #define __NO_RETURN                            __attribute__((__noreturn__))
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
#ifndef   __PACKED_UNION
  #define __PACKED_UNION                         union __attribute__((packed, aligned(1)))
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
#ifndef   __RESTRICT
  #define __RESTRICT                             __restrict
#endif

/** define the RISC-V Privileg Level support
    1: M(achine)-mode
    2: M-mode + U(ser)-mode
    3: M-mode + S(upervisor)-mode + U-mode
*/
#define PRIVILEG_LEVEL      1
#define N_EXTENSION         0   // Is "N" Standard Extension for User-Level Interrupts support?

extern const uint32_t PRIORITY_TABLE[];

/* ###########################  Core Function Access  ########################### */
/** \ingroup  CMSIS_Core_FunctionInterface
    \defgroup CMSIS_Core_RegAccFunctions CMSIS Core Register Access Functions
  @{
 */

#define __maybe_unused   __attribute__((unused))

/**
  \brief  Defines the address of RTK RISCV CSR (Control and Status Register).
*/
/* =============================================================== */
/* =============================================================== */
/* riscv_machine_mode_csr_e                                        */
/* =============================================================== */
/* =============================================================== */
/* Name          |Address     |Description */
/* Machine Information Registers */
#define mvendorid       0xF11    // RO Vendor ID.
#define marchid     	0xF12    // RO Architecture ID.
#define mimpid      	0xF13    // RO Implementation ID.
#define mhartid     	0xF14    // RO Hardware thread ID.

/* Machine Trap Setup */
#define mstatus     	0x300    // RW Machine status register.
#define misa        	0x301    // RW ISA and extensions
#define medeleg     	0x302    // RW Machine exception delegation register.
#define mideleg     	0x303    // RW Machine interrupt delegation register.
#define mie         	0x304    // RW Machine interrupt-enable register.
#define mtvec       	0x305    // RW Machine trap-handler base address.
#define mcounteren  	0x306    // RW Machine counter enable.

/* Machine Trap Handling */
#define mscratch    	0x340    // RW Scratch register for machine trap handlers.
#define mepc        	0x341    // RW Machine exception program counter.
#define mcause      	0x342    // RW Machine trap cause.
#define mtval       	0x343    // RW Machine bad address or instruction.
#define mip         	0x344    // RW Machine interrupt pending.

/* Machine Memory Protection */
#define pmpcfg0     	0x3A0    // RW Physical memory protection configuration.
#define pmpcfg1     	0x3A1    // RW Physical memory protection configuration RV32 only.
#define pmpcfg2     	0x3A2    // RW Physical memory protection configuration.
#define pmpcfg3     	0x3A3    // RW Physical memory protection configuration RV32 only.
#define pmpaddr0    	0x3B0    // RW Physical memory protection address register.
#define pmpaddr1    	0x3B1    // RW Physical memory protection address register.
#define pmpaddr2    	0x3B3    // RW Physical memory protection address register.
#define pmpaddr3    	0x3B4    // RW Physical memory protection address register.
#define pmpaddr4    	0x3B5    // RW Physical memory protection address register.
#define pmpaddr5    	0x3B6    // RW Physical memory protection address register.
#define pmpaddr6    	0x3B7    // RW Physical memory protection address register.
#define pmpaddr7    	0x3B8    // RW Physical memory protection address register.
#define pmpaddr8    	0x3B9    // RW Physical memory protection address register.
#define pmpaddr9    	0x3BA    // RW Physical memory protection address register.
#define pmpaddr10   	0x3BB    // RW Physical memory protection address register.
#define pmpaddr11   	0x3BC    // RW Physical memory protection address register.
#define pmpaddr12   	0x3BD    // RW Physical memory protection address register.
#define pmpaddr13   	0x3BE    // RW Physical memory protection address register.
#define pmpaddr14   	0x3BF    // RW Physical memory protection address register.

/* Machine Counter/Timers */
#define mcycle 			0xB00 	// RW Machine cycle counter.
#define minstret 		0xB02 	// RW Machine instructions-retired counter.
#define mhpmcounter3	0xB03 	// RW Machine performance-monitoring counter.
#define mhpmcounter4 	0xB04 	// RW Machine performance-monitoring counter.
#define mhpmcounter5 	0xB05 	// RW Machine performance-monitoring counter.
#define mhpmcounter6 	0xB06 	// RW Machine performance-monitoring counter.
#define mhpmcounter7 	0xB07 	// RW Machine performance-monitoring counter.
#define mhpmcounter8 	0xB08 	// RW Machine performance-monitoring counter.
#define mhpmcounter9 	0xB09 	// RW Machine performance-monitoring counter.
#define mhpmcounter10   0xB0A 	// RW Machine performance-monitoring counter.
#define mhpmcounter11 	0xB0B 	// RW Machine performance-monitoring counter.
#define mhpmcounter12 	0xB0C 	// RW Machine performance-monitoring counter.
#define mhpmcounter13 	0xB0D 	// RW Machine performance-monitoring counter.
#define mhpmcounter14 	0xB0E 	// RW Machine performance-monitoring counter.
#define mhpmcounter15 	0xB0F 	// RW Machine performance-monitoring counter.
#define mhpmcounter16 	0xB10 	// RW Machine performance-monitoring counter.
#define mhpmcounter17 	0xB11 	// RW Machine performance-monitoring counter.
#define mhpmcounter18 	0xB12 	// RW Machine performance-monitoring counter.
#define mhpmcounter19 	0xB13 	// RW Machine performance-monitoring counter.
#define mhpmcounter20 	0xB14 	// RW Machine performance-monitoring counter.
#define mhpmcounter21 	0xB15 	// RW Machine performance-monitoring counter.
#define mhpmcounter22 	0xB16 	// RW Machine performance-monitoring counter.
#define mhpmcounter23 	0xB17 	// RW Machine performance-monitoring counter.
#define mhpmcounter24 	0xB18 	// RW Machine performance-monitoring counter.
#define mhpmcounter25 	0xB19 	// RW Machine performance-monitoring counter.
#define mhpmcounter26 	0xB1A 	// RW Machine performance-monitoring counter.
#define mhpmcounter27 	0xB1B 	// RW Machine performance-monitoring counter.
#define mhpmcounter28 	0xB1C 	// RW Machine performance-monitoring counter.
#define mhpmcounter29 	0xB1D 	// RW Machine performance-monitoring counter.
#define mhpmcounter30 	0xB1E 	// RW Machine performance-monitoring counter.
#define mhpmcounter31 	0xB1F 	// RW Machine performance-monitoring counter.

#define mcycleh 		0xB80 	// RW Upper 32 bits of mcycle RV32I only.
#define minstreth 		0xB82 	// RW Upper 32 bits of minstret RV32I only.
#define mhpmcounter3h 	0xB83 	// RW Upper 32 bits of mhpmcounter3 RV32I only.
#define mhpmcounter4h 	0xB84 	// RW Upper 32 bits of mhpmcounter4 RV32I only.
#define mhpmcounter5h 	0xB85 	// RW Upper 32 bits of mhpmcounter5 RV32I only.
#define mhpmcounter6h 	0xB86 	// RW Upper 32 bits of mhpmcounter6 RV32I only.
#define mhpmcounter7h 	0xB87 	// RW Upper 32 bits of mhpmcounter7 RV32I only.
#define mhpmcounter8h 	0xB88 	// RW Upper 32 bits of mhpmcounter8 RV32I only.
#define mhpmcounter9h 	0xB89 	// RW Upper 32 bits of mhpmcounter9 RV32I only.
#define mhpmcounter10h  0xB8A 	// RW Upper 32 bits of mhpmcounter10 RV32I only.
#define mhpmcounter11h	0xB8B 	// RW Upper 32 bits of mhpmcounter11 RV32I only.
#define mhpmcounter12h	0xB8C 	// RW Upper 32 bits of mhpmcounter12 RV32I only.
#define mhpmcounter13h	0xB8D 	// RW Upper 32 bits of mhpmcounter13 RV32I only.
#define mhpmcounter14h	0xB8E 	// RW Upper 32 bits of mhpmcounter14 RV32I only.
#define mhpmcounter15h	0xB8F 	// RW Upper 32 bits of mhpmcounter15 RV32I only.
#define mhpmcounter16h	0xB90 	// RW Upper 32 bits of mhpmcounter16 RV32I only.
#define mhpmcounter17h	0xB91 	// RW Upper 32 bits of mhpmcounter17 RV32I only.
#define mhpmcounter18h	0xB92 	// RW Upper 32 bits of mhpmcounter18 RV32I only.
#define mhpmcounter19h	0xB93 	// RW Upper 32 bits of mhpmcounter19 RV32I only.
#define mhpmcounter20h	0xB94 	// RW Upper 32 bits of mhpmcounter20 RV32I only.
#define mhpmcounter21h	0xB95 	// RW Upper 32 bits of mhpmcounter21 RV32I only.
#define mhpmcounter22h	0xB96 	// RW Upper 32 bits of mhpmcounter22 RV32I only.
#define mhpmcounter23h	0xB97 	// RW Upper 32 bits of mhpmcounter23 RV32I only.
#define mhpmcounter24h	0xB98 	// RW Upper 32 bits of mhpmcounter24 RV32I only.
#define mhpmcounter25h	0xB99 	// RW Upper 32 bits of mhpmcounter25 RV32I only.
#define mhpmcounter26h	0xB9A 	// RW Upper 32 bits of mhpmcounter26 RV32I only.
#define mhpmcounter27h	0xB9B 	// RW Upper 32 bits of mhpmcounter27 RV32I only.
#define mhpmcounter28h	0xB9C 	// RW Upper 32 bits of mhpmcounter28 RV32I only.
#define mhpmcounter29h	0xB9D 	// RW Upper 32 bits of mhpmcounter29 RV32I only.
#define mhpmcounter30h	0xB9E 	// RW Upper 32 bits of mhpmcounter30 RV32I only.
#define mhpmcounter31h	0xB9F 	// RW Upper 32 bits of mhpmcounter31 RV32I only.

/* Machine Counter Setup */
#define mcountinhibit 	0x320 	// RW Machine counter-inhibit register.
#define mhpmevent3 	  	0x323 	// RW Machine performance-monitoring event selector.
#define mhpmevent4 		0x324 	// RW Machine performance-monitoring event selector.
#define mhpmevent5 		0x325 	// RW Machine performance-monitoring event selector.
#define mhpmevent6 		0x326 	// RW Machine performance-monitoring event selector.
#define mhpmevent7 		0x327 	// RW Machine performance-monitoring event selector.
#define mhpmevent8 		0x328 	// RW Machine performance-monitoring event selector.
#define mhpmevent9 		0x329 	// RW Machine performance-monitoring event selector.
#define mhpmevent10     0x32A 	// RW Machine performance-monitoring event selector.
#define mhpmevent11 	0x32B 	// RW Machine performance-monitoring event selector.
#define mhpmevent12 	0x32C 	// RW Machine performance-monitoring event selector.
#define mhpmevent13 	0x32D 	// RW Machine performance-monitoring event selector.
#define mhpmevent14 	0x32E 	// RW Machine performance-monitoring event selector.
#define mhpmevent15 	0x32F 	// RW Machine performance-monitoring event selector.
#define mhpmevent16 	0x330 	// RW Machine performance-monitoring event selector.
#define mhpmevent17 	0x331 	// RW Machine performance-monitoring event selector.
#define mhpmevent18 	0x332 	// RW Machine performance-monitoring event selector.
#define mhpmevent19 	0x333 	// RW Machine performance-monitoring event selector.
#define mhpmevent20 	0x334 	// RW Machine performance-monitoring event selector.
#define mhpmevent21 	0x335 	// RW Machine performance-monitoring event selector.
#define mhpmevent22 	0x336 	// RW Machine performance-monitoring event selector.
#define mhpmevent23 	0x337 	// RW Machine performance-monitoring event selector.
#define mhpmevent24 	0x338 	// RW Machine performance-monitoring event selector.
#define mhpmevent25 	0x339 	// RW Machine performance-monitoring event selector.
#define mhpmevent26 	0x33A 	// RW Machine performance-monitoring event selector.
#define mhpmevent27 	0x33B 	// RW Machine performance-monitoring event selector.
#define mhpmevent28 	0x33C 	// RW Machine performance-monitoring event selector.
#define mhpmevent29 	0x33D 	// RW Machine performance-monitoring event selector.
#define mhpmevent30 	0x33E 	// RW Machine performance-monitoring event selector.
#define mhpmevent31 	0x33F 	// RW Machine performance-monitoring event selector.

/* Debug/Trace Registers (shared with Debug Mode) */
#define tselect 		0x7A0 	// RW Debug/Trace trigger register select.
#define tdata1 			0x7A1 	// RW First Debug/Trace trigger data register.
#define tdata2 			0x7A2 	// RW Second Debug/Trace trigger data register.
#define tdata3 			0x7A3 	// RW Third Debug/Trace trigger data register.

/* Debug Mode Registers */
#define dcsr 			0x7B0 	// RW Debug control and status register.
#define dpc 			0x7B1 	// RW Debug PC.
#define dscratch0 		0x7B2 	// RW Debug scratch register 0.
#define dscratch1 		0x7B3  	// RW Debug scratch register 1.

/* Non-standard read/write */
#define mcctl0	        0x7C0	// RW instruction and data memory control 0
#define mcctl1	        0x7C1	// RW instruction and data memory control 1
#define mcctl2	        0x7C2	// RW instruction and data memory control 2
#define mcca	        0x7C3	// RW Memory management and cache attribute
#define msmmupfn	    0x7C4	// RW Simple virtual to physical memory mapping address
#define mccr	        0x7C5	// RW valid if no Supervisior mode
#define mbpctl	        0x7C6	// RW Core control register
#define mbpsta	        0x7C7	// RW Internal use for branch prediction control
#define mgctl	        0x7C8	// RW bp status
#define mdmaslot	    0x7C9	// RW DMA Arbitor Time Slot
#define mIWBase0	    0x7D0	// RW Base address of IMEM0
#define mIWTop0	        0x7D1	// RW Top address of IMEM0
#define mIWBase1	    0x7D2	// RW Base address of IMEM1
#define mIWTop1	        0x7D3	// RW Top address of IMEM1
#define mDWBase0	    0x7D4	// RW Base address of DMEM0
#define mDWTop0	        0x7D5	// RW Top address of DMEM0
#define mDWBase1	    0x7D6	// RW Base address of DMEM1
#define mDWTop1	        0x7D7	// RW Top address of DMEM1
#define mL2MemBase	    0x7D8	// RW Base address of L2MEM
#define mL2MemTop	    0x7D9	// RW Top address of L2MEM
#define mMergeUCBase0	0x7DA	// RW Base address of uncacheable write merge range
#define mMergeUCTop0	0x7DB	// RW Top address of?uncacheable write merge range
#define mMergeUCBase1	0x7DC	// RW Base address of?uncacheable write merge range
#define mMergeUCTop1	0x7DD	// RW Top address of?uncacheable write merge range
#define mWThroughBase	0x7DE	// RW Base address of write-through range
#define mWThroughTop	0x7DF	// RW Top address of write-through range
#define mMatchAddr	    0x7E0	// RW from taroko CP3_gen[22]
#define mMatchMask	    0x7E1	// RW from taroko CP3_gen[23]
#define mMatchPCBase	0x7E2	// RW from taroko CP3_gen[26]
#define mMatchPCTop	    0x7E3	// RW from taroko CP3_gen[27]
#define mBDBGInfo	    0x7E4	// RW BDBG Info
#define mBDBGCont	    0x7E5	// RW BDBG control
#define mVLSBase	    0x7E6	// RW Base address of VLS
#define mVLSTop	        0x7E7	// RW Top address of VLS
#define mZWFRange	    0x7E8	// ZERO_WORD_FIRST_RANGE
/* Non-standard read only */
#define mcctl3	        0xFC0	// RO instruction and data memory cotrol-sel3
#define mCheckSum	    0xFC1	// RO
#define mCheckSumH	    0xFC2	// RO
#define mMMCRBase	    0xFC3	// RO MMCR base address
#define mMMCRCoreSt	    0xFC4	// RO MMCR core status
#define mrevnum	        0xFD0	// RO Revision number
#define mcpunum	        0xFD1   // RO CPU number & CPU Project ID
/* =============================================================== */
/* =============================================================== */

/**
  \brief  Bit offset definition for M-mode Status register.
*/
enum mstatus_bits_e {
    mstatus_bit_uie     = 0,    // U-mode interrupt enable
    mstatus_bit_sie     = 1,    // S-mode interrupt enable
    mstatus_bit_mie     = 3,    // M-mode interrupt enable
    mstatus_bit_upie    = 4,
    mstatus_bit_spie    = 5,
    mstatus_bit_mpie    = 7,    // MPIE = MIE when entering ISR; MIE = MPIE when exiting ISR by "mret" instruction
    mstatus_bit_mpp     = 11,   // 2 bits, MPP = current previlieg mode when entering ISR
};
#define MSTATUS_UIE             ((1UL) << mstatus_bit_uie)
#define MSTATUS_SIE             ((1UL) << mstatus_bit_sie)
#define MSTATUS_MIE             ((1UL) << mstatus_bit_mie)
#define MSTATUS_UPIE            ((1UL) << mstatus_bit_upie)
#define MSTATUS_SPIE            ((1UL) << mstatus_bit_spie)
#define MSTATUS_MPIE            ((1UL) << mstatus_bit_mpie)
#define MSTATUS_MPP             ((1UL) << mstatus_bit_mpp)

/**
  \brief  Bit offset definition for M-mode Interrupt Pending register.
*/
enum mip_bits_e {
    mip_bit_usip        = 0,    // U-mode software interrupt pending
    mip_bit_ssip        = 1,    // S-mode software interrupt pending
    mip_bit_msip        = 3,    // M-mode software interrupt pending
    mip_bit_utip        = 4,    // U-mode timer interrupt pending
    mip_bit_stip        = 5,    // S-mode timer interrupt pending
    mip_bit_mtip        = 7,    // M-mode timer interrupt pending
    mip_bit_ueip        = 8,    // U-mode external interrupt pending
    mip_bit_seip        = 9,    // S-mode external interrupt pending
    mip_bit_meip        = 11,   // M-mode external interrupt pending
    mip_bit_cip0        = 16,   // Core interrupt[0] pending
    mip_bit_cip1        = 17,   // Core interrupt[1] pending
    mip_bit_cip2        = 18,   // Core interrupt[2] pending
    mip_bit_cip3        = 19,   // Core interrupt[3] pending
    mip_bit_cip4        = 20,   // Core interrupt[4] pending
    mip_bit_cip5        = 21,   // Core interrupt[5] pending
    mip_bit_cip6        = 22,   // Core interrupt[6] pending
    mip_bit_cip7        = 23    // Core interrupt[7] pending
};
#define MIP_USIP                ((1UL) << mip_bit_usip)
#define MIP_SSIP                ((1UL) << mip_bit_ssip)
#define MIP_MSIP                ((1UL) << mip_bit_msip)
#define MIP_UTIP                ((1UL) << mip_bit_utip)
#define MIP_STIP                ((1UL) << mip_bit_stip)
#define MIP_MTIP                ((1UL) << mip_bit_mtip)
#define MIP_UEIP                ((1UL) << mip_bit_ueip)
#define MIP_SEIP                ((1UL) << mip_bit_seip)
#define MIP_MEIP                ((1UL) << mip_bit_meip)
#define MIP_CIP0                ((1UL) << mip_bit_cip0)
#define MIP_CIP1                ((1UL) << mip_bit_cip1)
#define MIP_CIP2                ((1UL) << mip_bit_cip2)
#define MIP_CIP3                ((1UL) << mip_bit_cip3)
#define MIP_CIP4                ((1UL) << mip_bit_cip4)
#define MIP_CIP5                ((1UL) << mip_bit_cip5)
#define MIP_CIP6                ((1UL) << mip_bit_cip6)
#define MIP_CIP7                ((1UL) << mip_bit_cip7)
/**
  \brief  Bit offset definition for M-mode Interrupt Enable register.
*/
enum mie_bits_e {
    mie_bit_usie        = 0,    // U-mode software interrupt enable
    mie_bit_ssie        = 1,    // S-mode software interrupt enable
    mie_bit_msie        = 3,    // M-mode software interrupt enable
    mie_bit_utie        = 4,    // U-mode timer interrupt enable
    mie_bit_stie        = 5,    // S-mode timer interrupt enable
    mie_bit_mtie        = 7,    // M-mode timer interrupt enable
    mie_bit_ueie        = 8,    // U-mode external interrupt enable
    mie_bit_seie        = 9,    // S-mode external interrupt enable
    mie_bit_meie        = 11,   // M-mode external interrupt enable
    mie_bit_cie0        = 16,   // Core interrupt[0] enable
    mie_bit_cie1        = 17,   // Core interrupt[1] enable
    mie_bit_cie2        = 18,   // Core interrupt[2] enable
    mie_bit_cie3        = 19,   // Core interrupt[3] enable
    mie_bit_cie4        = 20,   // Core interrupt[4] enable
    mie_bit_cie5        = 21,   // Core interrupt[5] enable
    mie_bit_cie6        = 22,   // Core interrupt[6] enable
    mie_bit_cie7        = 23,   // Core interrupt[7] enable
};
#define MIE_USIE                ((1UL) << mie_bit_usie)
#define MIE_SSIE                ((1UL) << mie_bit_ssie)
#define MIE_MSIE                ((1UL) << mie_bit_msie)
#define MIE_UTIE                ((1UL) << mie_bit_utie)
#define MIE_STIE                ((1UL) << mie_bit_stie)
#define MIE_MTIE                ((1UL) << mie_bit_mtie)
#define MIE_UEIE                ((1UL) << mie_bit_ueie)
#define MIE_SEIE                ((1UL) << mie_bit_seie)
#define MIE_MEIE                ((1UL) << mie_bit_meie)
#define MIE_CIE0                ((1UL) << mie_bit_cie0)
#define MIE_CIE1                ((1UL) << mie_bit_cie1)
#define MIE_CIE2                ((1UL) << mie_bit_cie2)
#define MIE_CIE3                ((1UL) << mie_bit_cie3)
#define MIE_CIE4                ((1UL) << mie_bit_cie4)
#define MIE_CIE5                ((1UL) << mie_bit_cie5)
#define MIE_CIE6                ((1UL) << mie_bit_cie6)
#define MIE_CIE7                ((1UL) << mie_bit_cie7)

/**
  \brief  Bit offset definition for M-mode Cache Control Register0.
*/
enum mcctl0_bits_e {
    mcctl0_bit_IInv     = 0,    // ICache Invalidate
    mcctl0_bit_DInv     = 1,    // DCache Invalidate
    mcctl0_bit_DWB      = 2,    // DCache WriteBack
    mcctl0_bit_DWBInv   = 3,    // DCache WriteBack and Invalidate
    mcctl0_bit_IMem0Fill= 4,    // Fill IMEM0 then turn on IMEM0
    mcctl0_bit_IMem1Fill= 5,    // Fill IMEM1 then turn on IMEM1
    mcctl0_bit_DWBInvEC = 8,    // DCache write back Invalidate then enter coherence(MP only)
    mcctl0_bit_DWBInvLC = 9     // DCache write back Invalidate then leave coherence(MP only)
};
#define MCCTL0_IINV             ((1UL) << mcctl0_bit_IInv)
#define MCCTL0_DINV             ((1UL) << mcctl0_bit_DInv)
#define MCCTL0_DWB              ((1UL) << mcctl0_bit_DWB)
#define MCCTL0_DWBINV           ((1UL) << mcctl0_bit_DWBInv)
#define MCCTL0_IMEM0FILL        ((1UL) << mcctl0_bit_IMem0Fill)
#define MCCTL0_IMEM1FILL        ((1UL) << mcctl0_bit_IMem1Fill)
#define MCCTL0_DWBINVEC         ((1UL) << mcctl0_bit_DWBInvEC)
#define MCCTL0_DWBINVLC         ((1UL) << mcctl0_bit_DWBInvLC)

/**
  \brief  Bit offset definition for M-mode Cache Control Register1.
*/
#define MCCTL1_ICACHE_EN        (_BIT0)             // ICache on/off
#define MCCTL1_IMEM0_EN         (_BIT1)             // IMem0 on/off
#define MCCTL1_IMEM1_EN         (_BIT2)             // IMem1 on/off
#define MCCTL1_LD_ST_IMEM0      (_BIT4)             // Load&store inst hit IMem0 on/off
#define MCCTL1_LD_ST_IMEM1      (_BIT5)             // Load&store inst hit IMem1 on/off
#define MCCTL1_DCACHE_EN        (_BIT8)             // DCache on/off
#define MCCTL1_DMEM0_EN         (_BIT9)             // DMem0 on/off
#define MCCTL1_DMEM1_EN         (_BIT10)            // DMem1 on/off
#define MCCTL1_GWALLOC_CCA      (_BIT12)            // Determine write policy by CSR.CCA
#define MCCTL1_GWALLOC_WT       (_BIT13)            // All store miss will perform write-through.
#define MCCTL1_GWALLOC_WA       (_BIT13 | _BIT12)   // All store miss will perform write-allocate, except the range from CSR.mWThroughBase to CSR.mWThroughTop
#define MCCTL1_WB_MERGE_CCA     (_BIT14)            // Determine merge policy of cacheable write by CSR.CCA
#define MCCTL1_WB_MERGE_NO      (_BIT15)            // Do not merge cacheable write.
#define MCCTL1_WB_MERGE_YES     (_BIT15 | _BIT14)   // Always merge cacheable write.
#define MCCTL1_L2CACHE_EN       (_BIT16)            // L2Cache on/off
#define MCCTL1_L2MEM_EN         (_BIT17)            // L2Mem on/off
#define MCCTL1_IC_IN_L2C_EN     (_BIT18)            // L2Cache keeps cache line evicted from ICache
#define MCCTL1_DC_IN_L2C_EN     (_BIT19)            // L2Cache keeps cache line evicted from DCache
#define MCCTL1_WRT_BUF_EN       (_BIT20)            // Write buffer on/off
#define MCCTL1_FAST_WB_EN       (_BIT21)            // Controls the fast write back mode between DCACHE and L2CACHE when using CACHE instruction to do data cache line write-back or write-back-invalidate.
#define MCCTL1_MERGE_UC_CCA     (_BIT22)            // Determine merge policy of uncacheable write by CSR.CCA
#define MCCTL1_MERGE_UC_NO      (_BIT23)            // Do not merge uncacheable write.
#define MCCTL1_MERGE_UC_YES     (_BIT23 | _BIT22)   // Merge uncacheable write where its address is located between CSR.mMergeUCBase and CSR.mMergeUCTop.
#define MCCTL1_NONBLOCK_LD_EN   (_BIT24)            // Non-blocking load on/off
#define MCCTL1_LUBUF_EN         (_BIT25)            // Load-use data buffer on/off
#define MCCTL1_UCRD_WAIT_WRT_EN (_BIT26)            // An uncacheable read will be not be sent to system bus until previous writes are all responded.

/**
  \brief  Bit offset definition for M-mode Cache Control Register2.
*/
#define MCCTL2_ICMASK_EN_WAY0   (0)                 // Runtime ICache reduction (00:enable way 0)
#define MCCTL2_ICMASK_EN_WAY01  (_BIT0)             // Runtime ICache reduction (01:enable way 0&&Way 1)
#define MCCTL2_ICMASK_RESERVED  (_BIT1)             // Runtime ICache reduction (10:Reserved)
#define MCCTL2_ICMASK_EN_4WAY   (_BIT1 | _BIT0)     // Runtime ICache reduction (11:enable 4 ways) , Default
#define MCCTL2_IFPMASK_NO_PF    (0)                 // I-side pre-fetch capability. (00:No Pre-Fetch)
#define MCCTL2_IFPMASK_1LINE_PF (_BIT2)             // I-side pre-fetch capability. (01:1 pre-fetch line) , Default
#define MCCTL2_IFPMASK_2LINE_PF (_BIT3)             // I-side pre-fetch capability. (10:2 pre-fetch lines)
#define MCCTL2_IFPMASK_RESERVED (_BIT3 | _BIT2)     // I-side pre-fetch capability. (11:Reserved)
#define MCCTL2_DCMASK_EN_WAY0   (0)                 // Runtime DCache reduction (00:enable way 0)
#define MCCTL2_DCMASK_EN_WAY01  (_BIT8)             // Runtime DCache reduction (01:enable way 0&&Way 1)
#define MCCTL2_DCMASK_RESERVED  (_BIT9)             // Runtime DCache reduction (10:Reserved)
#define MCCTL2_DCMASK_EN_4WAY   (_BIT9 | _BIT8)     // Runtime DCache reduction (11:enable 4 ways) , Default
#define MCCTL2_OSBMASK_8ENTRY   (0)                 // Outstanding buffer mask (00:8 entries) , default
#define MCCTL2_OSBMASK_4ENTRY   (_BIT10)            // Outstanding buffer mask (01:4 entries)
#define MCCTL2_OSBMASK_2ENTRY   (_BIT11)            // Outstanding buffer mask (10:2 entries)
#define MCCTL2_OSBMASK_1ENTRY   (_BIT11 | _BIT10)   // Outstanding buffer mask (11:1 entry)
#define MCCTL2_WBQMASK_8ENTRY   (0)                 // Write Buffer Queue mask (00:8 entries) , default
#define MCCTL2_WBQMASK_4ENTRY   (_BIT12)            // Write Buffer Queue mask (01:4 entries)
#define MCCTL2_WBQMASK_2ENTRY   (_BIT13)            // Write Buffer Queue mask (10:2 entries)
#define MCCTL2_WBQMASK_1ENTRY   (_BIT13 | _BIT12)   // Write Buffer Queue mask (11:1 entry)
#define MCCTL2_LDQMASK_8ENTRY   (0)                 // Load Data Queue mask (00:8 entries) , default
#define MCCTL2_LDQMASK_4ENTRY   (_BIT14)            // Load Data Queue mask (01:4 entries)
#define MCCTL2_LDQMASK_2ENTRY   (_BIT15)            // Load Data Queue mask (10:2 entries)
#define MCCTL2_LDQMASK_1ENTRY   (_BIT15 | _BIT14)   // Load Data Queue mask (11:1 entry)
#define MCCTL2_DMEM0_NR         (_BIT16)            // Read write access to exported DMEM0 is non-re-ordered            (No-Config in MNT KR4)
#define MCCTL2_DMEM1_NR         (_BIT17)            // Read write access to exported DMEM1 is non-re-ordered            (No-Config in MNT KR4)
#define MCCTL2_L2CMASK_EN_WAY01 (0)                 // Runtime L2Cache reduction (00: enable way 0 ~ way 1)             (No-Config in MNT KR4)
#define MCCTL2_L2CMASK_EN_WAY03 (_BIT24)            // Runtime L2Cache reduction (01: enable way 0 ~ way3)              (No-Config in MNT KR4)
#define MCCTL2_L2CMASK_RESERVED (_BIT25)            // Runtime L2Cache reduction (10: Reserved)                         (No-Config in MNT KR4)
#define MCCTL2_L2CMASK_EN_WAY07 (_BIT25 | _BIT24)   // Runtime L2Cache reduction (11: enable way 0 ~ way 7) , default   (No-Config in MNT KR4)

/**
  \brief  Bit offset definition for M-mode Cache Attribute Register.
*/
enum mcca_bits_e {
    mcca_bit_cca0       = 0,    // CCA0 start bit
    mcca_bit_cca1       = 4,    // CCA1 start bit
    mcca_bit_cca2       = 8,    // CCA2 start bit
    mcca_bit_cca3       = 12,    // CCA3 start bit
    mcca_bit_cca4       = 16,    // CCA4 start bit
    mcca_bit_cca5       = 20,    // CCA5 start bit
    mcca_bit_cca6       = 24,    // CCA6 start bit
    mcca_bit_cca7       = 28,    // CCA7 start bit
};

#define MCCA_CACHEABLE_WA       (_BIT0)             // cacheable + write-allocate
#define MCCA_CACHEABLE_WT       (_BIT1)             // write-through, write-through attribute always overwrites write-allocate
#define MCCA_COHERENT           (_BIT2)             // coherent
#define MCCA_UNCACHEABLE        (_BIT3)             // uncacheable

/**
  \brief  Bit offset definition for Physical Memory Protection Register.
*/
#define PMP_R                   (_BIT0)             // PMP entry permits Read
#define PMP_W                   (_BIT1)             // PMP entry permits Write
#define PMP_X                   (_BIT2)             // PMP entry permits Execute
/*
    https://wiki.realtek.com/display/PSPRSDK/RISC-V+(KR4)+Memory+Protection+Functions+Porting+on+FreeRTOS
*/
#define PMP_A_DISABLE           (0)                 // Disable PMP Entry
#define PMP_A_TOR               (_BIT3)             // pmpaddr[i-1] <= PMP[i]'s Address < pmpaddr[i]
#define PMP_A_NA4               (_BIT4)             // Address Natural Aligned 4 Bytes Region
#define PMP_A_NAPOT             (_BIT4 | _BIT3)     // Address Natural Aligned Power Of Two Region
#define PMP_L                   (_BIT7)             // LOCK PMP Setting



/**
  \brief   Get PRIVLVL Register
  \details Returns the content of the PRIVLVL Register.
  \return               PRIVLVL Register value
 */
__STATIC_FORCEINLINE uint32_t __get_CPRIV(void)
{
#if defined(PRIVILEG_LEVEL) && (PRIVILEG_LEVEL > 1)
    // TODO: HW implementation to store current privleg mode is needed
    uint32_t ret = 1;

    //__ASM volatile ("csrr %0, priv_reg??" : "=r" (ret) );
    return(ret);
#else
    // M-mode only, always return true
    return 1;
#endif
}

/**
 *  @brief      Set one or more bits of a CSR register.
 *  @details    Set a given CSR register value with a given bits value.
 *  @param[in]  csr The given CSR address.
 *  @param[in]  bits The bits value to set the given CSR.
 *
 */
// csrrs rd, csr, rs1   ==> t = CSRs[csr]; CSRs[csr] = t | x[rs1]; x[rd] = t
#define __csr_set(csr, bits)                                                       \
    ({                                                                             \
        uint32_t reg_val = (uint32_t) bits;                                        \
        __ASM volatile ("csrrs %0, " #csr ", %1" : "=r"(reg_val) : "rK"(reg_val)); \
        reg_val;                                                                   \
    })

/**
 *  @brief      Clear one or more bits of a CSR register.
 *  @param[in]  csr The given CSR address.
 *  @param[in]  bits The mask of bits value to be cleared.
 *
 */
// csrrc rd, csr, rs1 ==> t = CSRs[csr]; CSRs[csr] = t &~x[rs1]; x[rd] = t
#define __csr_clear(csr, bits)                                                    \
    ({                                                                            \
        uint32_t reg_val = (uint32_t) bits;                                       \
        __ASM volatile("csrrc %0, " #csr ", %1" : "=r"(reg_val) : "rK"(reg_val)); \
        reg_val;                                                                  \
    })

/**
 *  @brief      Read a CSR register.
 *  @param[in]  csr The given CSR address.
 *
 *  @returns    The CSR register value.
 */
// csrr rd, csr   ==> x[rd] = CSRs[csr]
#define __csr_read(csr)                                                \
    ({                                                                 \
        uint32_t reg_val;                                              \
        __ASM volatile("csrr %0, " #csr : "=r"(reg_val) : : "memory"); \
        reg_val;                                                       \
    })

/**
 *  @brief      Write a CSR register with a given value.
 *  @param[in]  csr The address of the CSR to be written.
 *  @param[in]  value The value for the CSR writting.
 *
 */
// csrw csr, rs1    ==> CSRs[csr] = x[rs1]
#define __csr_write(csr, value)                                           \
    ({                                                                    \
        uint32_t reg_val = (uint32_t)(value);                             \
        __ASM volatile("csrw " #csr ", %0" : : "rK"(reg_val) : "memory"); \
    })



/**
  \brief   Restore the MIE bit
  \details Restore the MIE bit of MSTATUS
 */
__STATIC_FORCEINLINE void __restore_irq(int ullMIE)
{
    if (ullMIE) {
        __csr_set(mstatus, (1 << mstatus_bit_mie));
    } else {
        __csr_clear(mstatus, (1 << mstatus_bit_mie));
    }
}

/**
  \brief   Enable IRQ Interrupts
  \details Enables IRQ interrupts by setting the MPIE-bit in the MSTATUS.
           Can only be executed in Privileged modes.
 */
__STATIC_FORCEINLINE void __enable_irq(void)
{
    __csr_set(mstatus, (1 << mstatus_bit_mie));
}

/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by clearing the MPIE-bit in the CPSR.
           Can only be executed in Privileged modes.
 */
__STATIC_FORCEINLINE void __disable_irq(void)
{
    __csr_clear(mstatus, (1 << mstatus_bit_mie));
}

__STATIC_INLINE uint32_t __get_irq_active(unsigned int intr)
{
    uint32_t ulmie = __csr_read(mie);
    uint32_t ulmip = __csr_read(mip);

    return ((ulmie & ulmip & (1UL << intr)) ? 1 : 0);
}

__STATIC_INLINE uint32_t __get_irq_pending(unsigned int intr)
{
    uint32_t ulmip = __csr_read(mip);
    return ((ulmip & (1UL << intr)) ? 1 : 0);
}

__STATIC_INLINE uint32_t __get_irq_enable(unsigned int intr)
{
    uint32_t ulmie = __csr_read(mie);
    return ((ulmie & (1UL << intr)) ? 1 : 0);
}

/**
  \brief   Set mstatus Register
  \details Writes the given value to the mstatus Register.
  \param [in]    control  mstatus Register value to set
 */
__STATIC_FORCEINLINE void __set_MSTATUS(uint32_t control)
{

    __ASM volatile ("csrw mstatus, %0" ::"r"(control) );
}

/**
  \brief   Get MCAUSE Register
  \details Returns the content of the MCAUSE Register.
  \return               MCAUSE Register value
 */
__STATIC_FORCEINLINE uint32_t __get_MCAUSE(void)
{
    uint32_t result;

    __ASM volatile ("csrr %0, mcause" : "=r"(result) );
    return(result);
}

/**
  \brief   Get MSTATUS Register
  \details Returns the content of the MSTATUS Register.
  \return               MSTATUS Register value
 */
__STATIC_FORCEINLINE uint32_t __get_MSTATUS(void)
{
    uint32_t result;

    __ASM volatile ("csrr %0, mstatus" : "=r"(result) );
    return(result);
}

#if defined(N_EXTENSION) && (N_EXTENSION == 1)

/**
  \brief   Set ustatus Register
  \details Writes the given value to the ustatus Register.
  \param [in]    control  ustatus Register value to set
 */
__STATIC_FORCEINLINE void __set_USTATUS(uint32_t control)
{

    __ASM volatile ("csrw 0x0, %0" :: "r"(control) );
}

/**
  \brief   Get UCAUSE Register
  \details Returns the content of the UCAUSE Register.
  \return               UCAUSE Register value
 */
__STATIC_FORCEINLINE uint32_t __get_UCAUSE(void)
{
    uint32_t result;

    __ASM volatile ("csrr %0, 0x042" : "=r"(result) );
    return(result);
}

/**
  \brief   Get USTATUS Register
  \details Returns the content of the USTATUS Register.
  \return               USTATUS Register value
 */
__STATIC_FORCEINLINE uint32_t __get_USTATUS(void)
{
    uint32_t result;

    __ASM volatile ("csrr %0, 0x0" : "=r"(result) );
    return(result);
}
#endif  // end of "#if defined(N_EXTENSION) && (N_EXTENSION == 1)"

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
  \details Returns the content of the mip CSR.
  \return               mip CSR value
 */
__STATIC_FORCEINLINE uint32_t __get_IPSR(void)
{
    if (__get_MCAUSE() & (1 << 31)) {
        return __csr_read(mip);
    } else {
        return 0;
    }
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
__STATIC_FORCEINLINE uint32_t __get_PSP(void)
{
    //register uint32_t result;
    //__ASM volatile("lw %0, (userStack)" : "=r"(result));
    //return (result);
  /* not supported */
  return 0;
}

/**
  \brief   Set Process Stack Pointer
  \details Assigns the given value to the Process Stack Pointer (PSP).
  \param [in]    topOfProcStack  Process Stack Pointer value to set
 */
__STATIC_FORCEINLINE void __set_PSP(uint32_t topOfProcStack)
{
    //__ASM volatile("sw %0, (userStack)(x0)" ::"r"(topOfProcStack));
    /* not supported */
}

/**
  \brief   Get Main Stack Pointer
  \details Returns the current value of the Main Stack Pointer (MSP).
  \return               MSP Register value
 */
__STATIC_FORCEINLINE uint32_t __get_MSP(void)
{
    register uint32_t result;
    //__ASM volatile("lw %0, (kernelStack)" : "=r"(result));
    __ASM volatile("mv %0, sp" : "=r"(result));
    return (result);
}

/**
  \brief   Set Main Stack Pointer
  \details Assigns the given value to the Main Stack Pointer (MSP).
  \param [in]    topOfMainStack  Main Stack Pointer value to set
 */
__STATIC_FORCEINLINE void __set_MSP(uint32_t topOfMainStack)
{
    //__ASM volatile("sw %0, (kernelStack)(x0)" ::"r"(topOfMainStack));
    __ASM volatile("mv sp, %0" :: "r"(topOfMainStack));
}


#if defined(PRIVILEG_LEVEL) && (PRIVILEG_LEVEL > 1)

/**
  \brief   Get the running mode is User Mode
  \details Read 0xC10 privilege register
  \return               Is User mode
 */
__STATIC_FORCEINLINE uint32_t __is_U_Mode()
{
    // TODO: no HW implementation currently
    return 0;
}

/**
  \brief   Get the running mode is Machine Mode
  \details Read 0xC10 privilege register
  \return               Is Machine mode
 */
__STATIC_FORCEINLINE uint32_t __is_M_Mode()
{
    // TODO: no HW implementation currently
    return 1;
}

#endif  // end of "#if defined(PRIVILEG_LEVEL) && (PRIVILEG_LEVEL > 1)"

/**
  \brief   Get current IRQ mode
  \details Returns the IRQ mode of current exception.
  \return               The IRQ mode.
  \                     0: System fault exception or ECall exception.
  \                     1: Standard interrupt.
 */
__STATIC_FORCEINLINE uint32_t __is_IRQ_Mode(void)
{
    return ((__get_MCAUSE() >> 31) & 0x01);
}


/**
  \brief   Get Priority Mask
  \details Returns the current state of the priority mask bit from the Priority Mask Register.
  \return               Priority Mask value
 */
__STATIC_FORCEINLINE uint32_t __get_PRIMASK(void)
{
    // RISC-V has no such "Priority Mask Register" design as ARM's, use MIE to indicates this status
    if (__get_MSTATUS() & (1 << 3)) {
        // M-mode Interrupt is enabled: Priority Mask bit = 0
        return 0;
    } else {
        // M-mode Interrupt is disabled: Priority Mask bit = 1
        return 1;
    }
}

extern const DWORD VectorINT_MIE_MaskTable;    // MIE Mask Table
/**
  \brief   Get Base Priority
  \details Returns the current value of the Base Priority register.
  \return               EnumCpuIrqPriority
 */
__attribute__((always_inline)) __STATIC_INLINE EnumCpuIrqPriority __get_BASEPRI(void)
{
    uint32_t ulIdx = 0;
    uint32_t status= __csr_read(mie);
    const DWORD * mie_mask_table = ((const DWORD *)(&VectorINT_MIE_MaskTable));

    if(status == 0x00FF0888)
    {
        return _CPU_IRQ_DISABLE;
    }

    while(ulIdx < 8)
    {
        if(mie_mask_table[ulIdx] == status)
        {
            return (EnumCpuIrqPriority)(_CPU_IRQ_SW_LEVEL_0 + ulIdx);
        }
        ulIdx++;
    }
    // maybe MTI/MSI/MEI
    return _CPU_IRQ_HW_LEVEL_5;
}

/**
  \brief   Set Base Priority
  \details Assigns the given value to the Base Priority register.
  \param [in]    basePri  Base Priority value to set (0~7)
 */
__attribute__((always_inline)) __STATIC_INLINE void __set_BASEPRI(EnumCpuIrqPriority enumCpuIrqPriority)
{
    const DWORD * mie_mask_table = ((const DWORD *)(&VectorINT_MIE_MaskTable));
    if(enumCpuIrqPriority == _CPU_IRQ_DISABLE)
    {
        __csr_write(mie, 0x00FF0888);
    }
    else
    {
        __csr_write(mie, mie_mask_table[(enumCpuIrqPriority - _CPU_IRQ_SW_LEVEL_0)]);
    }
}


/**
  \brief   Set Machine Trap-Vector Base-Address Register
  \details Writes the base address and mode to the Machine Trap-Vector Base-Address Register.
  \param [in]    vect_base  The vector table base address.
  \param [in]    mode  The vector table mode.
  \                    0: All exceptions set pc to BASE
  \                    1: Asynchronous interrupts set pc to BASE+4��cause
 */
__STATIC_FORCEINLINE  void __set_MTVEC(uint32_t vect_base, uint32_t mode)
{
    uint32_t reg_val;

    // base address must be 4-bytes aligned
    reg_val =  (vect_base & 0xFFFFFFFC) | (mode & 0x03);
    __ASM volatile ("csrw 0x305, %0" :: "r"(reg_val) );
}

__STATIC_FORCEINLINE  uint32_t __get_MTVEC(void)
{
    return __csr_read (mtvec);
}
/*@} end of CMSIS_Core_RegAccFunctions */


/* ##########################  Core Instruction Access  ######################### */
/** \defgroup CMSIS_Core_InstructionInterface CMSIS Core Instruction Interface
  Access to dedicated instructions
  @{
*/

/* Define macros for porting to both thumb1 and thumb2.
 * For thumb1, use low register (r0-r7), specified by constraint "l"
 * Otherwise, use general registers, specified by constraint "r"
 */
#if defined (__thumb__) && !defined (__thumb2__)
#define __CMSIS_GCC_OUT_REG(r) "=l" (r)
#define __CMSIS_GCC_RW_REG(r) "+l" (r)
#define __CMSIS_GCC_USE_REG(r) "l" (r)
#else
#define __CMSIS_GCC_OUT_REG(r) "=r" (r)
#define __CMSIS_GCC_RW_REG(r) "+r" (r)
#define __CMSIS_GCC_USE_REG(r) "r" (r)
#endif

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
#define __NOP() __ASM volatile ("nop")

/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one of a number of events occurs.
 */
#define __WFI() __ASM volatile ("wfi")


/**
  \brief   Wait For Event
  \details Wait For Event is a hint instruction that permits the processor to enter
           a low-power state until one of a number of events occurs.
 */
// RISC-V has no "wfe" instruction
#define __WFE() __ASM volatile ("nop")


/**
  \brief   Send Event
  \details Send Event is a hint instruction. It causes an event to be signaled to the CPU.
 */
// RISC-V has no "sev" instruction
#define __SEV() __ASM volatile ("nop")


/**
  \brief   Instruction Synchronization Barrier
  \details Instruction Synchronization Barrier flushes the pipeline in the processor,
           so that all instructions following the ISB are fetched from cache or memory,
           after the instruction has been completed.
 */
__STATIC_FORCEINLINE void __ISB(void)
{
    __ASM volatile ("fence.i":::"memory");
}


/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
__STATIC_FORCEINLINE void __DSB(void)
{
    __ASM volatile ("fence":::"memory");
}


/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
__STATIC_FORCEINLINE void __DMB(void)
{
    __ASM volatile ("fence.i":::"memory");
}


__STATIC_FORCEINLINE void ASM_JUMP_TO_PC(uint32_t pc)
{
    uint32_t pc_val = (uint32_t)(pc);
    __ASM volatile ("mv     a5, %0" : : "rK"(pc_val) : "a5");
    __ASM volatile ("jr     a5"     : :         : "a5");
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
#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
  return (short)__builtin_bswap16(value);
#endif
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


/**
  \brief   Count leading zeros
  \details Counts the number of leading zeros of a data value.
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
#define __CLZ __builtin_clz


/**
  \ingroup PULP_BUILTIN_MARCO
  @{
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __ExtInsMaskFast(uint32_t size, uint32_t offset)
{
    return ((((size - 1)) << 5) | (offset));
}
__attribute__((always_inline)) __STATIC_INLINE uint32_t __ExtInsMaskSafe(uint32_t size, uint32_t offset)
{
    return ((((size - 1) & 0x1F) << 5) | (offset & 0x1F));
}

/*! @brief Packing of scalars into vectors */
#define __VEC_PACK2(x, y)                     __builtin_pulp_pack2((int16_t)  x, (int16_t)  y)
#define __VEC_PACKU2(x, y)                    __builtin_pulp_pack2((uint16_t) x, (uint16_t) y)
#define __VEC_PACK4(x, y, z, t)               __builtin_pulp_pack4((int8_t)   x, (int8_t)   y, (int8_t)  z, (int8_t)  t)
#define __VEC_PACKU4(x, y, z, t)              __builtin_pulp_pack4((uint8_t)  x, (uint8_t)  y, (uint8_t) z, (uint8_t) t)

/*! @brief Max */
#define __MAX(x, y)              __builtin_pulp_maxsi((x), (y))
#define __MAX2(x, y)             __builtin_pulp_max2(x, y)
#define __MAX4(x, y)             __builtin_pulp_max4(x, y)

#define __MAXU2(x, y)            __builtin_pulp_maxu2(x, y)
#define __MAXU4(x, y)            __builtin_pulp_maxu4(x, y)

/*! @brief Min */
#define __MIN2(x, y)             __builtin_pulp_min2(x, y)
#define __MIN4(x, y)             __builtin_pulp_min4(x, y)

#define __MINU2(x, y)            __builtin_pulp_minu2(x, y)
#define __MINU4(x, y)            __builtin_pulp_minu4(x, y)

/*! @brief Clip */
#define __CLIP(x, precision)     __builtin_pulp_clip(x, -(1<<(precision)), (1<<precision)-1)
#define __CLIPU(x, precision)    __builtin_pulp_clipu(x, 0, (1<<precision)-1)

/*! @brief Abs */
#define __ABS2(x)                __builtin_pulp_abs2(x)
#define __ABS4(x)                __builtin_pulp_abs4(x)

/* Unary minus */
#define __NEG2(x)                __builtin_pulp_neg2(x)
#define __NEG4(x)                __builtin_pulp_neg4(x)

/* Addition */
#define __ADD2(x, y)             __builtin_pulp_add2(x, y)
#define __ADD4(x, y)             __builtin_pulp_add4(x, y)

/* Substraction */
#define __SUB2(x, y)             __builtin_pulp_sub2(x, y)
#define __SUB4(x, y)             __builtin_pulp_sub4(x, y)

/* Average */
#define __AVG2(x, y)             __builtin_pulp_avg2(x, y)
#define __AVG4(x, y)             __builtin_pulp_avg4(x, y)

/* Average unsigned */
#define __AVGU2(x, y)            __builtin_pulp_avgu2(x, y)
#define __AVGU4(x, y)            __builtin_pulp_avgu4(x, y)

/* Bitwise and */
#define __AND2(x, y)             __builtin_pulp_and2(x, y)
#define __AND4(x, y)             __builtin_pulp_and4(x, y)

/* Bitwise or */
#define __OR2(x, y)              __builtin_pulp_or2(x, y)
#define __OR4(x, y)              __builtin_pulp_or4(x, y)

/* Bitwise exor */
#define __EXOR2(x, y)            __builtin_pulp_exor2(x, y)
#define __EXOR4(x, y)            __builtin_pulp_exor4(x, y)

/* Logical shift right */
#define __SRL2(x, y)             __builtin_pulp_srl2(x, y)
#define __SRL4(x, y)             __builtin_pulp_srl4(x, y)

/* Arithmetic shift right */
#define __SRA2(x, y)             __builtin_pulp_sra2(x, y)
#define __SRA4(x, y)             __builtin_pulp_sra4(x, y)

/* Logical shift left */
#define __SLL2(x, y)             __builtin_pulp_sll2(x, y)
#define __SLL4(x, y)             __builtin_pulp_sll4(x, y)

/*! @brief Mac */
#define __MAC(acc, x, y)         __builtin_pulp_mac(x, y, acc)
#define __MSU(acc, x, y)         __builtin_pulp_msu(x, y, acc)
#define __MACS(acc, x, y)        __builtin_pulp_macs(x, y, acc)
#define __MACHHS(acc, x, y)      __builtin_pulp_machhs(x, y, acc)
#define __MACU(acc, x, y)        __builtin_pulp_macu(x, y, acc)
#define __MACHHU(acc, x, y)      __builtin_pulp_machhu(x, y, acc)

#define __MACSN(acc, x, y, n)      __builtin_pulp_macsN(x, y, acc, n)
#define __MACUN(acc, x, y, n)      __builtin_pulp_macuN(x, y, acc, n)
#define __MACSRN(acc, x, y, n)     __builtin_pulp_macsRN(x, y, acc, n, (1<<(n-1)))
#define __MACURN(acc, x, y, n)     __builtin_pulp_macuRN(x, y, acc, n, (1<<(n-1)))

#define __MACHHSN(acc, x, y, n)    __builtin_pulp_machhsN(x, y, acc, n)
#define __MACHHUN(acc, x, y, n)    __builtin_pulp_machhuN(x, y, acc, n)
#define __MACHHSRN(acc, x, y, n)   __builtin_pulp_machhsN(x, y, acc, n, (1<<(n-1)))
#define __MACHHURN(acc, x, y, n)   __builtin_pulp_machhuN(x, y, acc, n, (1<<(n-1)))

/*! @brief Multiplications */
#define __MULS(x, y)            __builtin_pulp_muls(x, y)
#define __MULU(x, y)            __builtin_pulp_mulu(x, y)
#define __MULHHS(x, y)          __builtin_pulp_mulhhs(x, y)
#define __MULHHU(x, y)          __builtin_pulp_mulhhu(x, y)

#define __MULSN(x, y, n)        __builtin_pulp_mulsN(x, y, n)
#define __MULSRN(x, y, n)       __builtin_pulp_mulsRN(x, y, n, (1<<(n-1)))
#define __MULUN(x, y, n)        __builtin_pulp_muluN(x, y, n)
#define __MULURN(x, y, n)       __builtin_pulp_muluRN(x, y, n, (1<<(n-1)))

#define __MULHHSN(x, y, n)      __builtin_pulp_mulhhsN(x, y, n)
#define __MULHHSRN(x, y, n)     __builtin_pulp_mulhhsRN(x, y, n, (1<<(n-1)))
#define __MULHHUN(x, y, n)      __builtin_pulp_mulhhuN(x, y, n)
#define __MULHHURN(x, y, n)     __builtin_pulp_mulhhuRN(x, y, n, (1<<(n-1)))

/*! @brief Vectorial product and sum of products */
#define __DOTP2(x, y)           __builtin_pulp_dotsp2(x, y)
#define __DOTPU2(x, y)          __builtin_pulp_dotup2(x, y)
#define __DOTPUS2(x, y)         __builtin_pulp_dotusp2(x, y)

#define __SUM_DOTP2(x, y, z)    __builtin_pulp_sdotsp2(x, y, z)
#define __SUM_DOTPU2(x, y, z)   __builtin_pulp_sdotup2(x, y, z)
#define __SUM_DOTPUS2(x, y, z)  __builtin_pulp_sdotusp2(x, y, z)

#define __DOTP4(x, y)           __builtin_pulp_dotsp4(x, y)
#define __DOTPU4(x, y)          __builtin_pulp_dotup4(x, y)
#define __DOTPUS4(x, y)         __builtin_pulp_dotusp4(x, y)

#define __SUM_DOTP4(x, y, z)    __builtin_pulp_sdotsp4(x, y, z)
#define __SUM_DOTPU4(x, y, z)   __builtin_pulp_sdotup4(x, y, z)
#define __SUM_DOTPUS4(x, y, z)  __builtin_pulp_sdotusp4(x, y, z)


/*! @brief Complex Multiplication, Q15x15 into Q15, with optional post scaling by 1 or 2 */
#define __CPLX_MULS(x, y)        __builtin_pulp_cplxmuls(x, y)
#define __CPLX_MULS_DIV2(x, y)   __builtin_pulp_cplxmulsdiv2(x, y)
#define __CPLX_MULS_DIV4(x, y)   __builtin_pulp_cplxmulsdiv4(x, y)

/*! @brief Complex conjugate */
#define __CPLX_CONJ(x)           __builtin_pulp_cplx_conj(x)

/*! @brief Complex rotation by -pi/2 */
#define __CPLX_MJ(x)             __builtin_pulp_cplxmjrot2(x)

/*! @brief Complex substration, result rotated by -pi/2 */
#define __SUB2_ROTMJ(x, y)       __builtin_pulp_sub2rotmj(x, y)

/*! @brief Complex addition with post scaling by 1 or 2 */
#define __ADD2_DIV2(x, y)        __builtin_pulp_add2div2(x, y)
#define __ADD2_DIV4(x, y)        __builtin_pulp_add2div4(x, y)

/*! @brief Complex subtraction with post scaling by 1 or 2 */
#define __SUB2_DIV2(x, y)        __builtin_pulp_sub2div2(x, y)
#define __SUB2_DIV4(x, y)        __builtin_pulp_sub2div4(x, y)

/*! @brief Viterbi Max and Viterbi Select, pair of Q15 */
#define __VIT_MAX(x, y)          __builtin_pulp_vitmax2(x, y)
#define __VIT_SEL(x, y)          __builtin_pulp_vitsel2(x, y)

/*! @brief Position of the most significant bit of x */
#define __FL1(x)                 __builtin_pulp_fl1(x)

/*! @brief Number of sign bits */
#define __CLB(x)                 __builtin_pulp_clb(x)

/*! @brief Bit Extraction */
#define __BIT_EXTRACT(src, size, off)           __builtin_pulp_bextract(src, size, off)
#define __BIT_EXTRACTU(src, size, off)          __builtin_pulp_bextractu(src, size, off)

#define __BIT_EXTRACT_R(src, size, off)         __builtin_pulp_bextract_r(src,  __ExtInsMaskFast(size, off))
#define __BIT_EXTRACTU_R(src, size, off)        __builtin_pulp_bextractu_r(src, __ExtInsMaskFast(size, off))

#define __BIT_EXTRACT_R_SAFE(src, size, off)    __builtin_pulp_bextract_r(src,  __ExtInsMaskSafe(size, off))
#define __BIT_EXTRACTU_R_SAFE(src, size, off)   __builtin_pulp_bextractu_r(src, __ExtInsMaskSafe(size, off))

/*! @brief Bit insertion */
#define __BIT_INSERT(dst, src, size, off)        __builtin_pulp_binsert(dst, ~(((1<<size)-1)<<off), src, (((1<<size)-1)<<off), off)
#define __BIT_INSERT_R(dst, src, size, off)      __builtin_pulp_binsert_r(dst, src, __ExtInsMaskFast(size, off))
#define __BIT_INSERT_R_SAFE(dst, src, size, off) __builtin_pulp_binsert_r(dst, src, __ExtInsMaskSafe(size, off))

/*! @brief 1 bit rotation to the right, 32 bits input */
#define __ROTR(x)                                __builtin_pulp_rotr(x)

/*! @brief Add with normalization and rounding */
#define __ADD_ROUND_NORM(x, y, scale)            __builtin_pulp_addRN(x, y, scale, (1<<(scale-1)))
#define __ADD_ROUND_NORM_REG(x, y, scale)        __builtin_pulp_addRN_r(x, y, scale)
#define __ADD_ROUND_NORMU(x, y, scale)           __builtin_pulp_adduRN(x, y, scale, (1<<(scale-1)))
#define __ADD_ROUND_NORMU_REG(x, y, scale)       __builtin_pulp_adduRN_r(x, y, scale)

/*! @brief Normalization and rounding */
#define __ROUND_NORM(x, scale)                   __builtin_pulp_addRN(x, 0, scale, (1<<(scale-1)))
#define __ROUND_NORM_REG(x, scale)               __builtin_pulp_addRN_r(x, 0, scale)
#define __ROUND_NORMU(x, scale)                  __builtin_pulp_adduRN(x, 0, scale, (1<<(scale-1)))
#define __ROUND_NORMU_REG(x, scale)              __builtin_pulp_adduRN_r(x, 0, scale)
/*@} end of group PULP_BUILTIN_MARCO */

/**
  \ingroup PULP_VECTOR_TYPE
  @{
 */
typedef   signed short v2s   __attribute__((vector_size (4)));
typedef unsigned short v2u   __attribute__((vector_size (4)));

typedef   signed char  v4s   __attribute__((vector_size (4)));
typedef unsigned char  v4u   __attribute__((vector_size (4)));

typedef signed char    v4qi   __attribute__((vector_size (4)));
typedef unsigned char  v4qu   __attribute__((vector_size (4)));

typedef signed short   v2hi   __attribute__((vector_size (4)));
typedef unsigned short v2hu   __attribute__((vector_size (4)));
/*@} end of group PULP_VECTOR_TYPE */

#pragma GCC diagnostic pop

#endif /* __CMSIS_GCC_H */
