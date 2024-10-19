/*
 * Copyright 2012-2016  Realtek Semiconductor Corp.
 *
 * ResetVectorRedirect.S
 *     Reset Vector Redirect file for MNT RX3081
 *
 */

#include <rlxasm.h>

    .extern     BootResetVector

##################################################################
# Reser Vector ReDirect                                          #
##################################################################
    .section    ".ResetVectorRedirect", "ax"
    .align      2
    .globl      ResetVectorRedirect
	.ent        ResetVectorRedirect
ResetVectorRedirect:
	li      v1, BootResetVector    # Jump to BootResetVector (0x86002000)
    jr      v1
    nop
    nop
    nop
	.end ResetVectorRedirect
