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
// ID Code      : Gain_16_4000nit_Table.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// HDR10 BRIGHTNESS ADJUST GAIN 1.6 4000 NIT
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
0x1B, 0x37, 0x50, 0x69, 0x7F, 0x93, 0xA4, 0xB2, 0xBD, 0xC5, 0xCD, 0xD8, 0xE7, 0xF8, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// usercurve  0x011B ~ 0x0150
0x0D,0xC0,0xC0,0x29,0x80,0x00,
0x44,0x00,0xC0,0x5D,0x40,0x00,
0x74,0x80,0x40,0x89,0x80,0x00,
0x9C,0x00,0x40,0xAB,0xC0,0x80,
0xB8,0x80,0x80,0xC1,0x80,0x40,
0xC9,0x80,0xC0,0xD2,0x00,0x40,
0xDF,0x80,0x80,0xEF,0xC0,0x40,
0xFF,0xF0,0xF0,0xFF,0xF0,0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

#endif
