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
 * ExceptionVectorRedirect.S
 *     Exception Vector Redirect file for MNT RX3081
 *
 */

#include <rlxasm.h>
#include "Project_Asm.h"

    .extern     BootExceptionVector

##################################################################
# Exception Vector ReDirect                                      #
##################################################################
    .section    ".ExceptionVectorRedirect", "ax"
    .align      2
    .globl      ExceptionVectorRedirect
    .ent        ExceptionVectorRedirect
ExceptionVectorRedirect:
    mtc0    v1, REG_C0_CK1             # Reserve the v0, v1 value to CK0 and CK1
    mtc0    v0, REG_C0_CK0
    nop
    nop
#if defined(DEBUG)
	li      v1, ItcmExceptionVector    # Jump to ExceptionVector in ITCM (0xA5000000)
#else
	li      v1, BootExceptionVector    # Jump to BootExceptionVector (0x86002180)
#endif
    jr      v1
    nop
    nop
    nop
    .end ExceptionVectorRedirect
