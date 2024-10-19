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
 *     Exception Vector in ITCM for MNT RX3081
 *
 */

#include <machine/asm.h>
#include <rlxasm.h>
#include "Project_Asm.h"

    .extern     HardFault_Handler
    .extern     UsageFault_Handler

#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
    .extern     g_pulDebugCpuContext
#endif

.equ    TCB_CTX_SR,         (0 << 2)    #REG_C0_STS
.equ    TCB_CTX_EPC,        (1 << 2)    #REG_C0_EPC
.equ    TCB_CTX_LO,         (2 << 2)    #LO
.equ    TCB_CTX_HI,         (3 << 2)    #HI
.equ    TCB_CTX_GPR2,       (4 << 2)    #v0 (CK0)
.equ    TCB_CTX_GPR3,       (5 << 2)    #v1 (CK1)
.equ    TCB_CTX_GPR4,       (6 << 2)    #a0
.equ    TCB_CTX_GPR5,       (7 << 2)    #a1
.equ    TCB_CTX_GPR6,       (8 << 2)    #a2
.equ    TCB_CTX_GPR7,       (9 << 2)    #a3
.equ    TCB_CTX_GPR16,      (10 << 2)   #s0
.equ    TCB_CTX_GPR17,      (11 << 2)   #s1
.equ    TCB_CTX_GPR24,      (12 << 2)   #t8
.equ    TCB_CTX_GPR31,      (13 << 2)   #ra
#.equ    TCB_CTX_GPR29,      (14 << 2)   #sp
#.equ    STK_CTX_SIZE,       (16 << 2)
.equ    STK_CTX_SIZE,       (14 << 2)


.macro SAVE_CONTEXT
    .set push
    # Save (a0,a1,a2,a3,s0,s1,t8,ra,LO,HI,REG_C0_CK0(v0),REG_C0_CK1(v1),REG_C0_EPC,REG_C0_STS)
    # Save GPR
    sw      a0,     TCB_CTX_GPR4(sp)
    sw      a1,     TCB_CTX_GPR5(sp)
    sw      a2,     TCB_CTX_GPR6(sp)
    sw      a3,     TCB_CTX_GPR7(sp)
    sw      s0,     TCB_CTX_GPR16(sp)
    sw      s1,     TCB_CTX_GPR17(sp)
    move    a0,     t8
    sw      a0,     TCB_CTX_GPR24(sp)
    move    a0,     ra
    sw      a0,     TCB_CTX_GPR31(sp)
    # Save HILO
    mflo    a0
    mfhi    a1
    sw      a0,     TCB_CTX_LO(sp)
    sw      a1,     TCB_CTX_HI(sp)
    # Save $2 in REG_C0_CK0 to TCB_CTX_GPR2
    mfc0    a0,     REG_C0_CK0
    sw      a0,     TCB_CTX_GPR2(sp)
    # Save $3 in REG_C0_CK1 to TCB_CTX_GPR3
    mfc0    a0,     REG_C0_CK1
    sw      a0,     TCB_CTX_GPR3(sp)
    # Save EPC
    mfc0    a0,     REG_C0_EPC
    sw      a0,     TCB_CTX_EPC(sp)
    # Save Status register
    mfc0    a0,     REG_C0_STS
    sw      a0,     TCB_CTX_SR(sp)
    .set pop
.endm

.macro LOAD_CONTEXT
    .set push
    # Restore (a0,a1,a2,a3,s0,s1,t8,ra,LO,HI,REG_C0_CK0(v0),REG_C0_CK1(v1),REG_C0_EPC,REG_C0_STS)
    # Restore HILO
    lw      a0,     TCB_CTX_LO(sp)
    lw      a1,     TCB_CTX_HI(sp)
    mtlo    a0
    mthi    a1
    # Restore GPR
    lw      a0,     TCB_CTX_GPR31(sp)
    move    ra,     a0
    # Restore Task's stack
    lw      a0,     TCB_CTX_GPR24(sp)
    move    t8,     a0
    lw      v0,     TCB_CTX_GPR2(sp)
    lw      v1,     TCB_CTX_GPR3(sp)
    # Restore $2 in TCB_CTX_GPR2 to REG_C0_CK0 #
    mtc0    v0,     REG_C0_CK0
    # Restore $3 in TCB_CTX_GPR3 to REG_C0_CK1 #
    mtc0    v1,     REG_C0_CK1
    lw      s1,     TCB_CTX_GPR17(sp)
    lw      s0,     TCB_CTX_GPR16(sp)
    lw      a3,     TCB_CTX_GPR7(sp)
    lw      a2,     TCB_CTX_GPR6(sp)
    lw      a1,     TCB_CTX_GPR5(sp)
    lw      a0,     TCB_CTX_GPR4(sp)

    lw      v0,     TCB_CTX_EPC(sp)
    lw      v1,     TCB_CTX_SR(sp)
    # Restore REG_C0 EPC
    mtc0    v0,     REG_C0_EPC
    # Restore REG_C0 Status register
    mtc0    v1,     REG_C0_STS
    nop
    .set pop
.endm

###########################################################
# ISR priority table - mapping ISR priority to ISR offset
#
# calculate ISR offset into ISR_TABLE based on predefined
# priority, IP7 has the highest priority.
# i.e. IP7 > IP6 > ... > IP0
###########################################################
    .section    ".itcm_section"
    .align      2
    .globl isr_offset
isr_offset:
    .byte   0   # Reserved
    .byte   0   # (IP&IM) is 00000001'b , Addr_Offset of ISR[0] is 0=(0*4)

    .rept   2   # (IP&IM) is 00000010'b ~ 00000011'b
    .byte   4   # Addr_Offset of ISR[1] is 4=(1*4)
    .endr

    .rept   4   # (IP&IM) is 00000100'b ~ 00000111'b
    .byte   8   # Addr_Offset of ISR[2] is 8=(2*4)
    .endr

    .rept   8   # (IP&IM) is 00001000'b ~ 00001111'b
    .byte   12  # Addr_Offset of ISR[3] is 12=(3*4)
    .endr

    .rept   16  # (IP&IM) is 00010000'b ~ 00011111'b
    .byte   16  # Addr_Offset of ISR[4] is 16=(4*4)
    .endr

    .rept   32  # (IP&IM) is 00100000'b ~ 00111111'b
    .byte   20  # Addr_Offset of ISR[5] is 20=(5*4)
    .endr

    .rept   64  # (IP&IM) is 01000000'b ~ 01111111'b
    .byte   24  # Addr_Offset of ISR[6] is 24=(6*4)
    .endr

    .rept   128 # (IP&IM) is 10000000'b ~ 11111111'b
    .byte   28  # Addr_Offset of ISR[7] is 28=(7*4)
    .endr

.globl im_mask
im_mask:
    .word   0xFFFFFEFF  # ISR[0] IM MASK  Priority_LOW
    .word   0xFFFFFCFF  # ISR[1] IM MASK
    .word   0xFFFFF8FF  # ISR[2] IM MASK
    .word   0xFFFFF0FF  # ISR[3] IM MASK
    .word   0xFFFFE0FF  # ISR[4] IM MASK
    .word   0xFFFFC0FF  # ISR[5] IM MASK
    .word   0xFFFF80FF  # ISR[6] IM MASK
    .word   0xFFFF00FF  # ISR[7] IM MASK  Priority_High

/*----------------------------------------------------------------------------
 *      Functions
 *---------------------------------------------------------------------------*/

##################################################################
##################################################################
# Itcm Exception Handler                                         #
##################################################################
##################################################################
    .section    ".ExceptionVector.itcm_section", "ax"
    .align      2
    .set        noreorder
    .globl      ItcmExceptionVector
    .ent        ItcmExceptionVector
ItcmExceptionVector:
    #########################################################################
    # Done By CPU HW:                                                       #
    # 1. EPC = restart location(PC backup)                                  #
    # 2. Enter Kernel Mode && Disable GlobalINT(IEp = IEc, then IEc = 0)    #
    # 3. CAUSE = exception cause                                            #
    # 4. BADADDR = VirtualAddress (which cause AdEL/AdES)                   #
    # 5. PC = Exception Vector (then code jump to here)                     #
    #########################################################################

    ##############################################################
    # Examine ExcCode = CAUSE[6:2]
    # Branch to exeception code specific handlers
    # Go to the common handler to deal with all hardware interrupts
    ##############################################################

    # already Done in 0x1BCF0180 Exception Buffer
    #mtc0    v1,     REG_C0_CK1         # Reserve the v0, v1 value to CK0 and CK1
    #mtc0    v0,     REG_C0_CK0
    #nop
    #nop

    mfc0    v1,     REG_C0_CAUSE        # General Reg  v1 gets CAUSE from COP0 REG 13
    li      v0,     0x007c
    and     v0,     v1                  # select ExcCode = CAUSE[6:2]
    # Check if ExcCode == 0  (Normal Interrupt)
    beqz    v0,     Vector_INT          # common handler to deal with all hardware interrupts
    li      v1,     0x0028              # RI exception pretends to be syscall instruction
    # Check if ExcCode == 10 (ReservedInstruction trap)
    bne     v0,     v1, Vector_TRAP     # if ExcCode != 10, this is a Trap(AdEL-I/Bp/AdEL-D/AdES)
    # ExcCode is 10, continue to check if a SYSCALL implementation (use Special ReservedInstruction:0xFEBA)
    mfc0    v0,     REG_C0_EPC          # Verify magic code to differentiate from other RI exception
    li      v1,     -2                  # Align epc to 2 bytes (-2 = 0xFFFFFFFE)
    and     v0,     v1
    lh      v1,     0(v0)               # load content(ReservedInst. value) of EPC address
    li      v0,     0xFEBA              # 0xFEBA is special Reserved Inst. means user want to do SYSCALL
    and     v1,     v0
    # Check if ReservedInstruction == 0xFEBA)
    beq     v0,     v1, Vector_SVC
    # Other Undefined Instruction


    li      v0,     UsageFault_Handler  # Jump to UsageFault_Handler(UNDEFINED instruction)

#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
CpuFaultCommonProcess:
    # backup sp to v1
    # backup v0(Handler Address) to sp
    move    v1,     sp
    move    sp,     v0

    # g_pulDebugCpuContext[0] = sp (original, from v1)
    li      v0,     g_pulDebugCpuContext + 4
    sw      v1,     -4(v0)

    # backup v0(Handler Address) from sp to v1
    # sp = &g_pulDebugCpuContext[1]
    move    v1,     sp
    move    sp,     v0

    # backup CONTEXT (a0,a1,a2,a3,s0,s1,t8,ra,LO,HI,REG_C0_CK0(v0),REG_C0_CK1(v1),REG_C0_EPC,REG_C0_STS)
    # NOTE:can't use v1 in SAVE_CONTEXT macro
    SAVE_CONTEXT

    # sp = g_pulDebugCpuContext[0]
    li      v0,     g_pulDebugCpuContext
    lw      v0,     0(v0)
    move    sp,     v0

    # recover v0(Handler Address) from v1
    move    v0,     v1
#endif

    jr      v0                          #

#########################################
# TRAP Handler                          #
#########################################
Vector_TRAP:
    li      v1,     0x0024              # BREAK instruction
    # Check if ExcCode == 9 (BREAK trap)
    beq     v0,     v1, SYSCALL_Exit    # check if BREAK instruction

    li      v0,     HardFault_Handler   # Jump to HardFault_Handler
#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
    li      v1,     CpuFaultCommonProcess
    jr      v1
#else
    jr      v0
#endif

#########################################
# Normal Interrupt Handler (6HW + 2SW)  #
#########################################
Vector_INT: # Parameter: v1 --- REG_C0_CAUSE value
    li      v0,     0xff00
    and     v1,     v0                  # v1[15:8] is IM[7:0] (1:INT_en , 0:INT_dis)
    mfc0    v0,     REG_C0_STS          # v0=SR, v0[15:8] is IP[7:0] (1:INT_Pending , 0:INT_NotPending)
    and     v0,     v1                  # v0=(IP&IM), get unmasked interrupt pending
    beqz    v0,     Restore_V0_V1_ERET
    srl     v0,     v0, STATUSB_IP0     # To use priority table, shift IP to right byte(>>8)
    li      v1,     isr_offset          # Get ISR offset value:
    addu    v0,     v1, v0              #    IP7 > IP6 > ... > IP0, gotten from priority table
    lb      v0,     0(v0)               # v0 is address offset value of final ISR_Handler in ISR_TABLE
    li      v1,     ISR_TABLE           # v1 = ISR_TABLE address
    addu    v0,     v1                  # v0=calculated ISR_TABLE address

    # Jump to OS interrupt service routine(v0= calculated ISR_TABLE address)
OSIrqHandler:
    # os_cur_irq = calculated ISR_TABLE address
    li      v1,     os_cur_irq
    sw      v0,     0(v1)

    # reserve space for context switch
    addiu   sp,     -STK_CTX_SIZE       # set sp = sp - STK_CTX_SIZE

    # backup CONTEXT (a0,a1,a2,a3,s0,s1,t8,ra,LO,HI,REG_C0_CK0(v0),REG_C0_CK1(v1),REG_C0_EPC,REG_C0_STS)
    SAVE_CONTEXT

    #---- Masked all low priority IRQs
    # current v0 is calculated ISR_TABLE address
    # current a0 is REG_C0_STS
    li      v1,     ISR_TABLE           # v1 = ISR_TABLE Address
    subu    v1,     v0, v1              # v1 = Address Offset of ISR_TABLE
    li      a1,     im_mask             # Get IM_MASK table base address
    addu    a1,     a1, v1              # a1 = address of IM_MASK[int]
    lw      a1,     0(a1)               # a1 is the value of IM_MASK[int]
    and     a0,     a1                  # a0 = REG_C0_STS & IM_MASK[int]
    mtc0    a0,     REG_C0_STS          # REG_C0_STS = a0

    # Execute Interrupt Handler ISR_TABLE[int]
    lw      v0,     0(v0)               # Load Interrupt Handler ISR_TABLE[int] to v0
    ei                                  # Enable IE (IEc = 1)

    jalr    v0                          # Jump to handler of IPx. From 0 ~ 7
    nop

    # ISR_RETURN:
    # disable IE (IEc = 0)
    di

    # set os_cur_irq = 0
    li      a0,     os_cur_irq
    li      a1,     0x0

    # restore CONTEXT (a0,a1,a2,a3,s0,s1,t8,ra,LO,HI,REG_C0_CK0(v0),REG_C0_CK1(v1),REG_C0_EPC,REG_C0_STS)
    LOAD_CONTEXT

    # reserve space for context switch
    addiu   sp,     STK_CTX_SIZE       # set sp = sp + STK_CTX_SIZE

Restore_V0_V1_ERET:
    # restore v0,v1 value from CK0,CK1
    mfc0    v0,     REG_C0_CK0
    mfc0    v1,     REG_C0_CK1

    # Causes the IE stack to be popped, then use content
    # of EPC as returning address from the exception handler
    # IEc = IEp
    # PC = EPC
    eret


Vector_SVC:
    # set os_cur_irq = 1
    li      v0,     os_cur_irq
    li      v1,     0x1
    sw      v1,     0(v0)

    # Execute SysCall
OSSysCall:
    # Restore the v0, v1 value from CK0 and CK1(Reserved at ItcmExceptionVector start)
    mfc0    v0,     REG_C0_CK0
    mfc0    v1,     REG_C0_CK1
    jalr    s0                          # Call SysCall Function

    # Save SysCall Function return value to CK0,CK1
    mtc0    v0,     REG_C0_CK0
    mtc0    v1,     REG_C0_CK1
    nop
    nop
    # set os_cur_irq = 0, means Syscall End~
    li      v0,     os_cur_irq
    li      v1,     0x0
    sw      v1,     0(v0)

SYSCALL_Exit:
    # Fix Return Address(in EPC)
    mfc0    v1,     REG_C0_EPC
    addiu   v1,     v1, 2
    mtc0    v1,     REG_C0_EPC
    nop
    nop
    # restore SysCall Function return value from CK0,CK1
    mfc0    v0,     REG_C0_CK0
    mfc0    v1,     REG_C0_CK1
    # Causes the IE stack to be popped, then use content
    # of EPC as returning address from the exception handler
    # IEc = IEp
    # PC = EPC
    eret

    .end ItcmExceptionVector

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
