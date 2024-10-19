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

/*
 * ItcmExceptionVector.S
 *     Exception Vector in ITCM for MNT KR4
 *
 */

#include "Project_Asm.h"

    .extern     HardFault_Handler
    .extern     ISR_TABLE

#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
    .extern     g_pulDebugCpuContext
#endif


#include "kr4_asm_common.h"

#################################
# Vector Interrupt Table        #
#################################
    .section    ".ISR_MTVEC.itcm_section", "ax"
    .align      2
    .globl MTVEC_Table
MTVEC_Table:
    j     VectTRAP      # 00:Trap Handler / User Mode Software INT(Reserved)
    .word 0             # 01:Supervisor Mode Software INT(Reserved)
    .word 0             # 02:Reserved
    j     VectIntMSI    # 03:Machine Mode Software INT
    .word 0             # 04:User Mode CPU Timer INT(Reserved)
    .word 0             # 05:Supervisor Mode CPU Timer INT(Reserved)
    .word 0             # 06:Reserved
    j     VectIntMTI    # 07:Machine Mode CPU Timer INT
    .word 0             # 08:User Mode External INT(Reserved)
    .word 0             # 09:Supervisor Mode External INT(Reserved)
    .word 0             # 10:Reserved
    j     VectIntMEI    # 11:Machine Mode External INT
    .word 0             # 12:Reserved
    .word 0             # 13:Reserved
    .word 0             # 14:Reserved
    .word 0             # 15:Reserved
    j     VectIntHwINT5 # 16:CLI[0] (FW:HW_INT5)
    j     VectIntHwINT4 # 17:CLI[1] (FW:HW_INT4)
    j     VectIntHwINT3 # 18:CLI[2] (FW:HW_INT3)
    j     VectIntHwINT2 # 19:CLI[3] (FW:HW_INT2)
    j     VectIntHwINT1 # 20:CLI[4] (FW:HW_INT1)
    j     VectIntHwINT0 # 21:CLI[5] (FW:HW_INT0)
    j     VectIntSwINT1 # 22:CLI[6] (FW:SW_INT1)
    j     VectIntSwINT0 # 23:CLI[7] (FW:SW_INT0)


#################################
# HW Vector Interrupt Handler   #
#################################
    .section    ".ISR_COMMON.itcm_section", "ax"
    .align      2
    .globl      VectIntSwINT0
VectIntSwINT0:
    csrrw   x0,     mscratch,   0   #set mscratch = 0 (APP_SW_INT0)
    j       VectIntCommon

    .align      2
    .globl      VectIntSwINT1
VectIntSwINT1:
    csrrw   x0,     mscratch,   1   #set mscratch = 1 (APP_SW_INT1)
    j       VectIntCommon

    .align      2
    .globl      VectIntHwINT0
VectIntHwINT0:
    csrrw   x0,     mscratch,   2   #set mscratch = 2 (CPU HW INT0)
    j       VectIntCommon

    .align      2
    .globl      VectIntHwINT1
VectIntHwINT1:
    csrrw   x0,     mscratch,   3   #set mscratch = 3 (CPU HW INT1)
    j       VectIntCommon

    .align      2
    .globl      VectIntHwINT2
VectIntHwINT2:
    csrrw   x0,     mscratch,   4   #set mscratch = 4 (CPU HW INT2)
    j       VectIntCommon

    .align      2
    .globl      VectIntHwINT3
VectIntHwINT3:
    csrrw   x0,     mscratch,   5   #set mscratch = 5 (CPU HW INT3)
    j       VectIntCommon

    .align      2
    .globl      VectIntHwINT4
VectIntHwINT4:
    csrrw   x0,     mscratch,   6   #set mscratch = 6 (CPU HW INT4)
    j       VectIntCommon

    .align      2
    .globl      VectIntHwINT5
VectIntHwINT5:
    csrrw   x0,     mscratch,   7   #set mscratch = 7 (CPU HW INT5)
    j       VectIntCommon

    .align      2
    .globl      VectIntMTI
VectIntMTI:
    csrrw   x0,     mscratch,   8   #set mscratch = 8 (CPU Core Timer)
    j       VectIntCommon

    .align      2
    .globl      VectIntMSI
VectIntMSI:
    csrrw   x0,     mscratch,   9   #set mscratch = 9 (Software Interrupt)
    j       VectIntCommon

    .align      2
    .globl      VectIntMEI
VectIntMEI:
    csrrw   x0,     mscratch,   10  #set mscratch = 10 (External Interrupt)
    j       VectIntCommon

#################################
# Interrupt Priority Mask Table #
#################################
    # Two kinds Natural INT Priority :
    #           High <----------------------------------------------->Low
    #   (1)     CLI[0] > CLI[1] > CLI[2] > ... > CLI[7] > MEI > MSI > MTI
    #   (2)     MEI > MSI > MTI > CLI[0] > CLI[1] > CLI[2] > ... > CLI[7]
    # We use (2) setting: MCCR[0]=0
    # CLI[15:8] CLI[7:0]     MEIE MTIE MSIE
    # 00000000  11111111  00001000  10001000 = 0x00FF0888
    .align      2
    .globl VectorINT_MIE_MaskTable
VectorINT_MIE_MaskTable:
    .word   0x007F0888  # 00:CLI[7] CPU SW INT0 MIE Masked Value            Priority_Low
    .word   0x003F0888  # 01:CLI[6] CPU SW INT1 MIE Masked Value
    .word   0x001F0888  # 02:CLI[5] CPU HW INT0 MIE Masked Value
    .word   0x000F0888  # 03:CLI[4] CPU HW INT1 MIE Masked Value
    .word   0x00070888  # 04:CLI[3] CPU HW INT2 MIE Masked Value
    .word   0x00030888  # 05:CLI[2] CPU HW INT3 MIE Masked Value
    .word   0x00010888  # 06:CLI[1] CPU HW INT4 MIE Masked Value
    .word   0x00000888  # 07:CLI[0] CPU HW INT5 MIE Masked Value
    .word   0x00000808  # 08:MTI    Machine CPU CoreTimer MIE Masked Value
    .word   0x00000800  # 09:MSI    Machine Software INT MIE Masked Value
    .word   0x00000000  # 10:MEI    Machine External INT MIE Masked Value   Priority_High


##################################################################
##################################################################
# Vector Interrupt Common Process                                #
##################################################################
##################################################################
    .globl      VectIntCommon
VectIntCommon:
    ##################################################
    # mscratch stores index of VectorINT  Priority   #
    # mscratch = 0 (CPU SW INT0)                Low  #
    # mscratch = 1 (CPU SW INT1)                     #
    # mscratch = 2 (CPU HW INT0)                     #
    # mscratch = 3 (CPU HW INT1)                     #
    # mscratch = 4 (CPU HW INT2)                     #
    # mscratch = 5 (CPU HW INT3)                     #
    # mscratch = 6 (CPU HW INT4)                     #
    # mscratch = 7 (CPU HW INT5)                     #
    # mscratch = 8 (Machine CPU Core Timer)          #
    # mscratch = 9 (Machine Software Interrupt)      #
    # mscratch = 10(Machine External Interrupt) High #
    ##################################################

    # reserve space for context switch
    addi    sp,     sp,         -STK_CTX_SIZE   # set sp = sp - STK_CTX_SIZE

    # backup CONTEXT (a0,a1,a2,a3,a4,a5,a6,a7,t0,t1,t2,t3,t4,t5,t6,ra,mstatus,mepc,mie)
    SAVE_INT_CONTEXT
    # t2 is mie now

    csrr    a0,     mscratch        # a0 = mscratch (Vector INT Index)
    la      a1,     VectorINT_MIE_MaskTable
    slli    a0,     a0,         2   # a0 = VecIntIdx * 4
    #---- Masked all low priority IRQs
    add     a2,     a1,         a0  # a2 = address of VectorINT_MIE_MaskTable[VecIntIdx]
    lw      a1,     0(a2)           # a1 = MEM[a2], VecINT MIE Mask Value
    csrw    0x304,  a1              # MIE = MEM[ VectorINT_MIE_MaskTable[VecIntIdx] ]

    # Execute Interrupt Handler ISR_TABLE[int]
    la      a1,     ISR_TABLE
    add     a2,     a1,         a0  # a2 = address of ISR_TABLE[VecIntIdx]
    lw      a1,     0(a2)           # a1 = MEM[a2],address of Vector INT Handler

    # Enable Global IRQ(mstatus[3] = MIE = 1)
    li      a2,     8
    csrw    mstatus,a2

    jalr    a1                      # Call Vector INT Handler

    # ISR_RETURN:
    # Disable Global IRQ(mstatus[3] = MIE = 0)
    csrw    mstatus,x0

    # restore CONTEXT (a0,a1,a2,a3,a4,a5,a6,a7,t0,t1,t2,t3,t4,t5,t6,ra,mstatus,mepc,mie)
    LOAD_CONTEXT

    # restore stack space for context switch
    addi    sp,     sp,         STK_CTX_SIZE    # set sp = sp + STK_CTX_SIZE

    # Causes the IE stack to be popped, then use content
    # of EPC as returning address from the exception handler
    # MIE = MPIE
    # MPIE = 1
    # PC = MEPC
    mret



##################################################################
##################################################################
# SVCall Process                                         #
##################################################################
##################################################################
    .globl      Vector_SVC
Vector_SVC:
    # clear MSIP flag
    lui     a2,     0xe0000
    sw      x0,     16(a2)

    lw      a2,     TCB_CTX_GPR10(sp)
    jr      a2


##################################################################
##################################################################
# Trap Exception Process                                         #
##################################################################
##################################################################
    .section    ".itcm_section", "ax"
    .globl      VectTRAP
VectTRAP:
    # reserve space for context switch
    addi    sp,     sp,         -STK_CTX_SIZE   # set sp = sp - STK_CTX_SIZE

#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
    sw      s0,     0(sp)
    sw      s1,     4(sp)

    #Back SP to g_pulDebugCpuContext[0]
    la      s0,     g_pulDebugCpuContext
    addi    s1,     sp,         STK_CTX_SIZE
    sw      s1,     0(s0)

    # Set SP point to g_pulDebugCpuContext[1]
    addi    sp,     s0,         4

    # backup CONTEXT (a0,a1,a2,a3,a4,a5,a6,a7,t0,t1,t2,t3,t4,t5,t6,ra,mstatus,mepc,mie,s0~s11)
    SAVE_INT_CONTEXT

    # restore s0,s1
    addi    t0,     s1,         -STK_CTX_SIZE
    lw      s0,     0(t0)
    lw      s1,     4(t0)

    # backup s0~s11 cpu context
    sw      s0,     (19<<2)(sp)
    sw      s1,     (20<<2)(sp)
    sw      s2,     (21<<2)(sp)
    sw      s3,     (22<<2)(sp)
    sw      s4,     (23<<2)(sp)
    sw      s5,     (24<<2)(sp)
    sw      s6,     (25<<2)(sp)
    sw      s7,     (26<<2)(sp)
    sw      s8,     (27<<2)(sp)
    sw      s9,     (28<<2)(sp)
    sw      s10,    (29<<2)(sp)
    sw      s11,    (30<<2)(sp)

    # Restore SP
    la      t0,     g_pulDebugCpuContext
    lw      t1,     0(t0)
    addi    sp,     t1,         -STK_CTX_SIZE
#endif

    # backup CONTEXT (a0,a1,a2,a3,a4,a5,a6,a7,t0,t1,t2,t3,t4,t5,t6,ra,mstatus,mepc,mie)
    SAVE_INT_CONTEXT

    la      a1,     HardFault_Handler
    jalr    a1                      # Call Vector INT Handler

    # restore CONTEXT (a0,a1,a2,a3,a4,a5,a6,a7,t0,t1,t2,t3,t4,t5,t6,ra,mstatus,mepc,mie)
    LOAD_CONTEXT

    # restore stack space for context switch
    addi    sp,     sp,         STK_CTX_SIZE    # set sp = sp + STK_CTX_SIZE

    # Causes the IE stack to be popped, then use content
    # of EPC as returning address from the exception handler
    # MIE = MPIE
    # MPIE = 1
    # PC = MEPC
    mret

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
