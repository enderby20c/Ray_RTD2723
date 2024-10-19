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
// ID Code      : Gain_14_4000nit_Table.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// HDR10 BRIGHTNESS ADJUST GAIN 1.4 4000 NIT
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
0x18, 0x31, 0x49, 0x61, 0x77, 0x8C, 0x9F, 0xAF, 0xBC, 0xC5, 0xCE, 0xD8, 0xE7, 0xF8, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// usercurve  0x011B ~ 0x0150
0x0C, 0x00, 0x80, 0x24, 0xC0, 0x00,
0x3D, 0x40, 0x40, 0x55, 0x40, 0x00,
0x6C, 0x80, 0x80, 0x82, 0x40, 0x80,
0x96, 0x40, 0x80, 0xA8, 0x00, 0xC0,
0xB6, 0xC0, 0x40, 0xC1, 0x00, 0x00,
0xC9, 0x80, 0x00, 0xD2, 0x40, 0x80,
0xDF, 0xC0, 0x80, 0xEF, 0xC0, 0x40,
0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

#endif
