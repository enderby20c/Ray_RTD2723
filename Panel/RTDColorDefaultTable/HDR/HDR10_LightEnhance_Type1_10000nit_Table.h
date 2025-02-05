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
// ID Code      : Gain_12_10000nit_Table.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// HDR10 BRIGHTNESS ADJUST GAIN 1.2 10000 NIT
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
0x13, 0x26, 0x39, 0x4C, 0x5F, 0x72, 0x85, 0x97, 0xA7, 0xB7, 0xC2, 0xCC, 0xD5, 0xE1, 0xF0, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// usercurve  0x011B ~ 0x0150
0x09, 0x40, 0x00, 0x1C, 0x80, 0x00,
0x2F, 0xC0, 0x40, 0x43, 0x00, 0x80,
0x56, 0x00, 0x80, 0x69, 0x00, 0x80,
0x7B, 0xC0, 0x00, 0x8E, 0x40, 0x00,
0x9F, 0x80, 0xC0, 0xAF, 0xC0, 0x00,
0xBD, 0x00, 0x40, 0xC7, 0x00, 0x00,
0xD0, 0xC0, 0x40, 0xDB, 0x00, 0xC0,
0xE9, 0x00, 0x80, 0xF8, 0x40, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

#endif
