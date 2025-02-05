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
// ID Code      : Gain_12_1200nit_Table.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// HDR10 BRIGHTNESS ADJUST GAIN 1.2 1200 NIT
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
0x24, 0x46, 0x66, 0x82, 0x99, 0xAA, 0xB8, 0xC6, 0xD5, 0xE9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// usercurve  0x011B ~ 0x0150
0x12, 0x00, 0x00, 0x35, 0xC0, 0xC0,
0x57, 0x00, 0x80, 0x75, 0x00, 0x40,
0x8E, 0x80, 0x80, 0xA2, 0x80, 0x40,
0xB1, 0x00, 0x00, 0xBF, 0x00, 0x00,
0xCC, 0x40, 0x00, 0xDF, 0x00, 0x80,
0xF4, 0x80, 0xC0, 0xFF, 0xF0, 0xF0,
0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0,
0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

#endif
