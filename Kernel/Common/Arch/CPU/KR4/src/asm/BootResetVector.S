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
 *     Boot Reset Vector file for MNT KR4
 *
 */
#include "kr4_asm_common.h"
#include "Project_Asm.h"

    .extern     Reset_Handler

##################################################################
# Boot Reset Handler                                             #
##################################################################
    .section    ".BootResetVector", "ax"
    .align      2
    .globl      BootResetVector
BootResetVector:
    ##################################################################
    # Initialize Stack Pointer
    ##################################################################
    li      sp,     _DTCM_E_ADDRESS + 1

    # Disable IMEM && DMEM && Disable I-Cache/D-Cache && Enable Wait previous writes are all responded
    # __csr_write(0x7C1, MCCTL1_DMEM0_EN | MCCTL1_UCRD_WAIT_WRT_EN);
    li      a0,     0x04000200
    csrw    0x7c1,  a0
    # __DSB()
    fence.i

    j       Reset_Handler
