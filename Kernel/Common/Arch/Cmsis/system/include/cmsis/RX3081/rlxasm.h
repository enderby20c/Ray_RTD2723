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

#ifndef __RLX_ASM_H
#define __RLX_ASM_H

#ifdef __ASSEMBLER__

#include <machine/regdef.h>

/*
 * Coprocessor 0 register names
 */
//#define REG_C0_INDEX                      $0
//#define REG_C0_RANDOM                     $1
//#define REG_C0_ENTRYLO                    $2
//#define REG_C0_CONTEXT                    $4
//#define REG_C0_WIRED                      $6
#define REG_C0_BADVADDR                   $8
//#define REG_C0_ENTRYHI                    $10
#define REG_C0_STATUS                     $12
#define REG_C0_STS                        $12
#define REG_C0_CAUSE                      $13
#define REG_C0_EPC                        $14
#define REG_C0_PRID                       $15
#define REG_C0_DREG                       $16
#define REG_C0_DEPC                       $17
#define REG_C0_CCTL                       $20
#define REG_C0_CK0                        $26 /* rx3081 */
#define REG_C0_CK1                        $27 /* rx3081 */
#define REG_C0_DESAVE                     $31

#define STATUSB_IP0                       8
#define ST0_BEV                           0x00400000

/*
 * CCTL control bits
 */
#define REG_C0_CCTL_DMEMON                0x00000400      /* Enable the DMEM                                */
#define REG_C0_CCTL_DMEMOFF               0x00000800      /* Disable the DMEM                               */
#define REG_C0_CCTL_IMEMFILL              0x00000010      /* IMEM fill                                      */
#define REG_C0_CCTL_IMEMOFF               0x00000020      /* Disable the IMEM                               */
#define REG_C0_CCTL_DINVAL                0x00000001      /* The value of DInval                            */
#define REG_C0_CCTL_IINVAL                0x00000002      /* The value of IInval(invalidate i-cache)        */
#define REG_C0_CCTL_IMEM_LDST_ON          0x00000004      /* 0->1, enable IMEM access by Load/Store Inst.   */
#define REG_C0_CCTL_IMEM_LDST_OFF         0x00000008      /* 0->1, disable IMEM access by Load/Store Inst.  */
#define REG_C0_CCTL_IMEMFILL              0x00000010      /* 0->1, trigger IMEM fill operation by HW        */
#define REG_C0_CCTL_IMEMOFF               0x00000020      /* 0->1, disable IMEM                             */
#define REG_C0_CCTL_IMEMON                0x00000040      /* 0->1, enable IMEM(must fill IMEM before enable)*/
#define REG_C0_CCTL_DMEMON                0x00000400      /* 0->1, enable DMEM                              */
#define REG_C0_CCTL_DMEMOFF               0x00000800      /* 0->1, disable DMEM                             */
#define REG_C0_CCTL_DMEMFILL              0x00001000      /* 0->1, trigger DMEM fill operation by HW        */

/*
 * RX3081 CACHE instruction
 */
#define CACHE_OP_INVALID_ICACHE           (0b10000)       /* IInval The line in ICACHE is invalidated. */
#define CACHE_OP_IMEM_READ                (0b00110)       /* IMLoad Load IMEM instruction into special registers. */
#define CACHE_OP_IMEM_WRITE               (0b01010)       /* IMStore Store instruction into IMEM. */

#endif /* INCLUDED_BY_ASSEMBLY */

//#ifdef __m3081

#define __write_32bit_c0_register(register, sel, value)                                                  \
    do {\
        __asm__ __volatile__(\
        "li $2, " #value"\n\t"\
        "mtc0 $2, " #register "\n\t"\
        : /* output operands */\
        : /* input operands */\
        : "v0"/* clobber(modified cpu reg in the code) */ );\
    } while (0)

#define __read_32bit_c0_register(source, sel)                            \
    ({                                                                   \
        int __res;                                                       \
        __asm__ __volatile__("mfc0\t%0, " #source "\n\t" : "=r"(__res)); \
        __res;                                                           \
    })

#define read_c0_status() __read_32bit_c0_register($12, 0)
#define write_c0_status(val) __write_32bit_c0_register($12, 0, val)

#define read_c0_cause() __read_32bit_c0_register($13, 0)
#define write_c0_cause(val) __write_32bit_c0_register($13, 0, val)

#define SOC_CPU_HAS_EIDI
#define SZ_REG_ARRAY                      16
#define NUM_INTR                          8

#define COP_HAZARD                        "nop;nop;nop\n\t"
#define LOAD_HAZARD                       "nop\n\t"
#define __COP_HAZARD                      nop; nop; nop
#define __LOAD_HAZARD                     nop
//#endif

#endif /* __RLX_ASM_H */
