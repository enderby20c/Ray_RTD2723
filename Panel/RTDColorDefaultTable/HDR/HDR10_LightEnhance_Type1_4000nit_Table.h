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
// ID Code      : Gain_12_4000nit_Table.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// HDR10 BRIGHTNESS ADJUST GAIN 1.2 4000 NIT
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
0x15, 0x2A, 0x3F, 0x54, 0x69, 0x7E, 0x92, 0xA5, 0xB4, 0xC0, 0xCC, 0xD7, 0xE7, 0xF8, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// usercurve  0x011B ~ 0x0150
0x0A, 0x40, 0x00, 0x1F, 0x80, 0x40,
0x34, 0xC0, 0x80, 0x4A, 0x00, 0x80,
0x5F, 0x40, 0xC0, 0x74, 0x00, 0x40,
0x88, 0x80, 0x40, 0x9B, 0xC0, 0x00,
0xAD, 0x80, 0xC0, 0xBB, 0x00, 0xC0,
0xC6, 0x80, 0x00, 0xD1, 0x40, 0xC0,
0xDF, 0x40, 0x40, 0xEF, 0xC0, 0x40,
0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

#endif
