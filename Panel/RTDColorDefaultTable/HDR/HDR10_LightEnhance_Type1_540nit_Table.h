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
// ID Code      : Gain_12_540nit_Table.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// HDR10 BRIGHTNESS ADJUST GAIN 1.2 540 NIT
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
0x1B, 0x37, 0x53, 0x6E, 0x88, 0x9E, 0xB1, 0xC3, 0xD4, 0xE9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// usercurve  0x011B ~ 0x0150
0x0D, 0x80, 0x80, 0x29, 0x40, 0x40,
0x45, 0x40, 0x00, 0x60, 0xC0, 0x80,
0x7B, 0xC0, 0xC0, 0x94, 0x40, 0xC0,
0xA8, 0x00, 0xC0, 0xBB, 0x00, 0xC0,
0xCB, 0x40, 0x40, 0xDE, 0x80, 0x40,
0xF4, 0x40, 0x80, 0xFF, 0xF0, 0xF0,
0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0,
0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

#endif
