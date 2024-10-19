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

.equ    TCB_CTX_GPR10,      (0 << 2)    # a0
.equ    TCB_CTX_GPR11,      (1 << 2)    # a1
.equ    TCB_CTX_GPR12,      (2 << 2)    # a2
.equ    TCB_CTX_GPR13,      (3 << 2)    # a3
.equ    TCB_CTX_GPR14,      (4 << 2)    # a4
.equ    TCB_CTX_GPR15,      (5 << 2)    # a5
.equ    TCB_CTX_GPR16,      (6 << 2)    # a6
.equ    TCB_CTX_GPR17,      (7 << 2)    # a7
.equ    TCB_CTX_GPR05,      (8 << 2)    # t0
.equ    TCB_CTX_GPR06,      (9 << 2)    # t1
.equ    TCB_CTX_GPR07,      (10 << 2)   # t2
.equ    TCB_CTX_GPR28,      (11 << 2)   # t3
.equ    TCB_CTX_GPR29,      (12 << 2)   # t4
.equ    TCB_CTX_GPR30,      (13 << 2)   # t5
.equ    TCB_CTX_GPR31,      (14 << 2)   # t6
.equ    TCB_CTX_GPR01,      (15 << 2)   # ra
.equ    TCB_CTX_SR,         (16 << 2)   # mstatus
.equ    TCB_CTX_EPC,        (17 << 2)   # mepc
.equ    TCB_CTX_MIE,        (18 << 2)   # mie
.equ    STK_CTX_SIZE,       (19 << 2)

#################################
# SAVE_TRAP_CONTEXT             #
#################################
.macro SAVE_TRAP_CONTEXT
    # Save (a0,a1,a2,a3,a4,a5,a6,a7,t0,t1,t2,t3,t4,t5,t6,ra,mstatus,mepc,mie)
    # Save GPR
    # push a0~a7 to stack
    sw      a0,     TCB_CTX_GPR10(sp)
    sw      a1,     TCB_CTX_GPR11(sp)
    sw      a2,     TCB_CTX_GPR12(sp)
    sw      a3,     TCB_CTX_GPR13(sp)
    sw      a4,     TCB_CTX_GPR14(sp)
    sw      a5,     TCB_CTX_GPR15(sp)
    sw      a6,     TCB_CTX_GPR16(sp)
    sw      a7,     TCB_CTX_GPR17(sp)
    # push t0~t6 to stack
    sw      t0,     TCB_CTX_GPR05(sp)
    sw      t1,     TCB_CTX_GPR06(sp)
    sw      t2,     TCB_CTX_GPR07(sp)
    sw      t3,     TCB_CTX_GPR28(sp)
    sw      t4,     TCB_CTX_GPR29(sp)
    sw      t5,     TCB_CTX_GPR30(sp)
    sw      t6,     TCB_CTX_GPR31(sp)
    sw      ra,     TCB_CTX_GPR01(sp)
    
    csrr    t0,     mstatus # mstatus
    csrr    t1,     mepc    # mepc
    csrr    t2,     mie     # mie  
    addi    t1,     t1,         4   # Trap return address = mepc + 4       
    sw      t0,     TCB_CTX_SR(sp)
    sw      t1,     TCB_CTX_EPC(sp)
    sw      t2,     TCB_CTX_MIE(sp)
.endm

#################################
# SAVE_INT_CONTEXT              #
#################################
.macro SAVE_INT_CONTEXT
    # Save (a0,a1,a2,a3,a4,a5,a6,a7,t0,t1,t2,t3,t4,t5,t6,ra,mstatus,mepc,mie)
    # Save GPR
    # push a0~a7 to stack
    sw      a0,     TCB_CTX_GPR10(sp)
    sw      a1,     TCB_CTX_GPR11(sp)
    sw      a2,     TCB_CTX_GPR12(sp)
    sw      a3,     TCB_CTX_GPR13(sp)
    sw      a4,     TCB_CTX_GPR14(sp)
    sw      a5,     TCB_CTX_GPR15(sp)
    sw      a6,     TCB_CTX_GPR16(sp)
    sw      a7,     TCB_CTX_GPR17(sp)
    # push t0~t6 to stack
    sw      t0,     TCB_CTX_GPR05(sp)
    sw      t1,     TCB_CTX_GPR06(sp)
    sw      t2,     TCB_CTX_GPR07(sp)
    sw      t3,     TCB_CTX_GPR28(sp)
    sw      t4,     TCB_CTX_GPR29(sp)
    sw      t5,     TCB_CTX_GPR30(sp)
    sw      t6,     TCB_CTX_GPR31(sp)
    sw      ra,     TCB_CTX_GPR01(sp)
    
    csrr    t0,     mstatus # mstatus
    csrr    t1,     mepc    # mepc
    csrr    t2,     mie     # mie 
    sw      t0,     TCB_CTX_SR(sp)
    # INT return address = mepc
    sw      t1,     TCB_CTX_EPC(sp)
    sw      t2,     TCB_CTX_MIE(sp)
.endm

#################################
# LOAD_CONTEXT                  #
#################################
.macro LOAD_CONTEXT
    # Restore (a0,a1,a2,a3,a4,a5,a6,a7,t0,t1,t2,t3,t4,t5,t6,ra,mstatus,mepc,mie)
    lw      t0,     TCB_CTX_SR(sp)
    lw      t1,     TCB_CTX_EPC(sp)
    lw      t2,     TCB_CTX_MIE(sp)
    csrw    mstatus,t0      # mstatus
    csrw    mepc,   t1      # mepc
    csrw    mie,    t2      # mie
    
    # Save GPR
    # pull a0~a7 from stack
    lw      a0,     TCB_CTX_GPR10(sp)
    lw      a1,     TCB_CTX_GPR11(sp)
    lw      a2,     TCB_CTX_GPR12(sp)
    lw      a3,     TCB_CTX_GPR13(sp)
    lw      a4,     TCB_CTX_GPR14(sp)
    lw      a5,     TCB_CTX_GPR15(sp)
    lw      a6,     TCB_CTX_GPR16(sp)
    lw      a7,     TCB_CTX_GPR17(sp)
    # pull t0~t6 from stack
    lw      t0,     TCB_CTX_GPR05(sp)
    lw      t1,     TCB_CTX_GPR06(sp)
    lw      t2,     TCB_CTX_GPR07(sp)
    lw      t3,     TCB_CTX_GPR28(sp)
    lw      t4,     TCB_CTX_GPR29(sp)
    lw      t5,     TCB_CTX_GPR30(sp)
    lw      t6,     TCB_CTX_GPR31(sp)
    lw      ra,     TCB_CTX_GPR01(sp)
.endm
