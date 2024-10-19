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
 * BootResetVector.S
 *     Boot Reset Vector file for MNT RX3081
 *
 */

#include <rlxasm.h>
#include "Project_Asm.h"

                                                            // PA40010_70_CPU1_IMEM_ADDR_BASE
#define DEFAULT_CPU1_IMEM_ADDR_BASE_VALUE   (0x06000000)    // 0x8600_0000
#define ACTIVE_CPU1_IMEM_ADDR_BASE_VALUE    (0x05000000)    // 0x8500_0000

                                                            // PA40010_74_CPU1_IMEM_ADDR_TOP
#define DEFAULT_CPU1_IMEM_ADDR_TOP_VALUE    (0x06000fff)    // 0x8600_0FFF
#define ACTIVE_CPU1_IMEM_ADDR_TOP_VALUE     (0x05000fff)    // 0x8500_0FFF


#################################################################
# LUI V1 instruction:                                           #
# 31-27   26-24 23-21 20-16     15-11    10-5      4-0          #
# 01101     011   001 XXXXX     11110    XXXXXX    XXXXX        #
# OP_LI     V1    001 IMM[4:0]  EXTEND   IMM[10:5] IMM[15:11]   #
#################################################################
#define LUI_V1_CONSTANT                     (0x6b20f000)

#################################################################
# ADDUI V1 instruction:                                         #
# 31-27   26-24 23-21 20-16     15-11    10-5      4-0          #
# 01001     011   000 XXXXX     11110    XXXXXX    XXXXX        #
# OP_ADDIU8  V1   000 IMM[4:0]  EXTEND   IMM[10:5] IMM[15:11]   #
#################################################################
#define ADDUI_V1_CONSTANT                   (0x4b00f000)

                                                            // PBFC001_88_CPU_EXCEPTION_INST_BUF_2
#define DEFAULT_CPU_EXCEPT_INST_BUF2_VALUE  (0x6b20f610)    // lui    v1, 0x8600
#define ACTIVE_CPU_EXCEPT_INST_BUF2_VALUE   (0x6b20f510)    // lui    v1, 0x8500

                                                            // PBFC001_8C_CPU_EXCEPTION_INST_BUF_3
#define DEFAULT_CPU_EXCEPT_INST_BUF3_VALUE  (0x4b01f184)    // addiu  v1, 0x2181,   targetAddr = 0x8600_2180
#define ACTIVE_CPU_EXCEPT_INST_BUF3_VALUE   (0x4b01f000)    // addiu  v1, 0x1   ,   targetAddr = 0x8500_0000


    .extern     Reset_Handler

##################################################################
# Boot Reset Handler                                             #
##################################################################
    .section    ".BootResetVector", "ax"
    .align      2
    .globl      BootResetVector
    .ent        BootResetVector
BootResetVector:
    ##################################################################
    # Initialize Status<BEV> for normal exception vectors
    ##################################################################
    li      v1,     (ST0_BEV)   # make sure coprocessors enabled && BEV=1 && IEc=0
    mtc0    v1,     REG_C0_STS

    # Modify Exception Vector ReDirect to Flash Default Address(0x86002180)
    li      v0,     PBFC001_88_CPU_EXCEPTION_INST_BUF_2
    li      v1,     DEFAULT_CPU_EXCEPT_INST_BUF2_VALUE
    sw      v1,     0(v0)
    li      v1,     DEFAULT_CPU_EXCEPT_INST_BUF3_VALUE
    sw      v1,     4(v0)

    ##################################################################
    # Initialize Stack Pointer
    ##################################################################
    li      v0,     _estack
    move    sp,     v0

    ##################################################################
    # Clear IP[x]
    ##################################################################
    li      v1,     0x0
    mtc0    v1,     REG_C0_CAUSE

    ##################################################################
    # Initialize IMEM && Enable DMEM
    ##################################################################
    # clear all bits of CCTL
    mtc0    v1,     REG_C0_CCTL

    ##################################################################
    # trigger IMEM FILL(always from Default BASE && TOP address) && Enable DMEM
    ##################################################################
    li      v0,     (REG_C0_CCTL_DMEMON + REG_C0_CCTL_IMEMOFF + REG_C0_CCTL_IMEMFILL + REG_C0_CCTL_IMEM_LDST_ON + REG_C0_CCTL_IINVAL)
    mtc0    v0,     REG_C0_CCTL

    # insert additional 3 nops when I-Cache status changed(invalidate)
    nop
    nop
    nop

    ##################################################################
    # set IMEM_BASE && IMEM_TOP to Active Region
    ##################################################################
    # Scaler32SetDWord(PA40010_70_CPU1_IMEM_ADDR_BASE, ACTIVE_CPU1_IMEM_ADDR_BASE_VALUE)
    li      v0,     PA40010_70_CPU1_IMEM_ADDR_BASE
    li      v1,     ACTIVE_CPU1_IMEM_ADDR_BASE_VALUE
    sw      v1,     0(v0)
    # Scaler32SetDWord((PA40010_70_CPU1_IMEM_ADDR_BASE + 4), ACTIVE_CPU1_IMEM_ADDR_TOP_VALUE)
    li      v1,     ACTIVE_CPU1_IMEM_ADDR_TOP_VALUE
    sw      v1,     4(v0)

    ##################################################################
    # Enable IMEM
    ##################################################################
    li      v1,     (REG_C0_CCTL_IMEMON)
    mtc0    v1,     REG_C0_CCTL

    ##################################################################
    # Modify Exception Vector ReDirect to ITCM Target Address(0x85000000)
    ##################################################################
    li      v0,     PBFC001_88_CPU_EXCEPTION_INST_BUF_2
    li      v1,     ACTIVE_CPU_EXCEPT_INST_BUF2_VALUE
    sw      v1,     0(v0)
    li      v1,     ACTIVE_CPU_EXCEPT_INST_BUF3_VALUE
    sw      v1,     4(v0)

    ##################################################################
    # Jump to Reset_Handler
    ##################################################################
    li      v1,     Reset_Handler    # Jump to Reset_Handler (C Code in arch_exception_handlers.c)
    jr      v1
    nop
    .end BootResetVector
