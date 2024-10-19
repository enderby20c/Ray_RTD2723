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
// ID Code      : DccModeHDRLike2084.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DCC MODE HDR Like 2084
//****************************************************************************
#if(_HW_DCC_TABLE_TYPE == _DCC_GEN_1)

_DCC_CONTROL,
0x10,
_DCC_TABLE,
//control
0x04, 0x00, 0x00,
0xB0, 0xFF, 0x00,
0x10, 0x00, 0xFF,
// control LSB 0x0017 ~ 0x001B
0x00, 0x00, 0x00, 0x00, 0x00,
//usercurve
0x18, 0x2A, 0x3F, 0x52,
0x62, 0x72, 0x82, 0x92,
0xA3, 0xB4, 0xC5, 0xD5,
0xE2, 0xF0, 0xFA, 0x00,
0x00, 0x00, 0x02,
0x50, 0x14, 0x34, 0x22,
// usercurve Add 0x011B ~ 0x0150
0x0A, 0x80, 0x00, 0x1F, 0x80, 0x00,
0x34, 0x80, 0x00, 0x48, 0x80, 0x00,
0x5A, 0x00, 0x00, 0x6A, 0x00, 0x00,
0x7A, 0x00, 0x00, 0x8A, 0x00, 0x00,
0x9A, 0x80, 0x00, 0xAB, 0x80, 0x00,
0xBC, 0x80, 0x00, 0xCD, 0x00, 0x00,
0xDB, 0x80, 0x00, 0xE9, 0x00, 0x00,
0xF5, 0x00, 0x00, 0xFD, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
_DCC_END,

#endif
