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
 * BootExceptionVector.S
 *     Exception Vector Redirect file for MNT RX3081
 *
 */

#include <rlxasm.h>
#include "Project_Asm.h"

    .extern     SysIntDefaultHandler

##################################################################
# Default Exception Handler                                      #
##################################################################
    .section    ".BootExceptionVector", "ax"
    .align      2
    .globl      BootExceptionVector
    .ent        BootExceptionVector
BootExceptionVector:
##################################################################
# Default Exception Handler before ITCM_Exception Handler Active
##################################################################
    li      v1, SysIntDefaultHandler    # Jump to SysIntDefaultHandler
    jr      v1
    .end BootExceptionVector

