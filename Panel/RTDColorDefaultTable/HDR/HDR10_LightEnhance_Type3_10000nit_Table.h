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

//----------------------------------------------------------------------------------------------------
// ID Code      : Gain_16_10000nit_Table.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// HDR10 BRIGHTNESS ADJUST GAIN 1.6 10000 NIT
//****************************************************************************

#if(_HW_DCC_TABLE_TYPE == _DCC_GEN_1)

_DCC_CONTROL,
0x30,
_DCC_TABLE,
//control
0x00, 0x00, 0x00,
0x01, 0x00, 0x00,
0x00, 0x00, 0x00,
// control LSB 0x0017 ~ 0x001B
0x00, 0x00, 0x00, 0x00, 0x00,
// usercurve 0x0100 ~ 0x010F
0x19, 0x31, 0x49, 0x60, 0x75, 0x88, 0x99, 0xA9, 0xB6, 0xC0, 0xC7, 0xCE, 0xD5, 0xE2, 0xF0, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// usercurve  0x011B ~ 0x0150
0x0C, 0x40, 0x00, 0x25, 0x80, 0xC0,
0x3E, 0x00, 0xC0, 0x55, 0x00, 0x40,
0x6B, 0x00, 0x40, 0x7F, 0x00, 0x80,
0x91, 0x80, 0xC0, 0xA1, 0xC0, 0x00,
0xAF, 0xC0, 0x00, 0xBB, 0x80, 0x80,
0xC4, 0x40, 0xC0, 0xCA, 0xC0, 0x40,
0xD2, 0x00, 0xC0, 0xDB, 0x80, 0x00,
0xE9, 0x40, 0xC0, 0xF8, 0x80, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

#endif
