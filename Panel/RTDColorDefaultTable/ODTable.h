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
// ID Code      : ODTable.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// OD TABLE
//****************************************************************************
#if(_HW_OD_TABLE_TYPE == _OD_GEN_0)
BYTE code tOD_TABLE_COMMON[] =
{
    0x00,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,
    0x04,0x00,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,
    0x09,0x05,0x00,0xFF,0x00,0xFE,0xFA,0xFD,0xFA,0xFA,0xFA,0xFD,0xFA,0xFA,0xFA,0xFA,0xFA,
    0x11,0x07,0x04,0x00,0xFF,0xFC,0xFC,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF0,
    0x17,0x0F,0x09,0x04,0x00,0xFD,0xFA,0xFB,0xF4,0xF4,0xF4,0xF4,0xF4,0xF1,0xED,0xE7,0xE4,
    0x1B,0x14,0x0D,0x08,0x03,0x00,0xFD,0xFA,0xF3,0xF3,0xF3,0xF0,0xEE,0xE9,0xE4,0xDD,0xDA,
    0x21,0x18,0x12,0x0D,0x08,0x04,0x00,0xFD,0xF8,0xF3,0xF1,0xEE,0xE9,0xE5,0xE2,0xD6,0xD4,
    0x27,0x1C,0x1B,0x14,0x0F,0x0A,0x05,0x00,0xFC,0xF8,0xF3,0xEF,0xE9,0xE3,0xE1,0xD6,0xCE,
    0x2B,0x21,0x20,0x1E,0x16,0x12,0x0D,0x07,0x00,0xFC,0xF7,0xF1,0xEB,0xE3,0xDF,0xD5,0xCC,
    0x2F,0x25,0x25,0x21,0x1B,0x1B,0x14,0x0E,0x08,0x00,0xFA,0xF3,0xEC,0xE2,0xDE,0xD6,0xCB,
    0x32,0x27,0x25,0x21,0x1E,0x1E,0x1B,0x15,0x0F,0x08,0x00,0xFA,0xF0,0xE5,0xDE,0xD6,0xCC,
    0x2E,0x26,0x25,0x23,0x21,0x1F,0x1B,0x18,0x12,0x0F,0x08,0x00,0xF7,0xE9,0xDF,0xD7,0xD0,
    0x29,0x24,0x24,0x23,0x20,0x20,0x1E,0x19,0x15,0x10,0x0D,0x08,0x00,0xF3,0xE1,0xDC,0xD4,
    0x24,0x21,0x20,0x1F,0x1D,0x1D,0x1B,0x19,0x17,0x14,0x12,0x0D,0x09,0x00,0xF3,0xE4,0xDD,
    0x1B,0x17,0x19,0x17,0x17,0x17,0x17,0x17,0x14,0x12,0x10,0x0D,0x0A,0x09,0x00,0xF0,0xE6,
    0x11,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0A,0x0B,0x0B,0x0B,0x0A,0x09,0x08,0x00,0xF1,
    0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,
};

#if(_FREESYNC_SUPPORT == _ON)
BYTE code tOD_TABLE_FREESYNC[] =
{
    0x00,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,
    0x04,0x00,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,
    0x09,0x05,0x00,0xFF,0x00,0xFE,0xFA,0xFD,0xFA,0xFA,0xFA,0xFD,0xFA,0xFA,0xFA,0xFA,0xFA,
    0x11,0x07,0x04,0x00,0xFF,0xFC,0xFC,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF0,
    0x17,0x0F,0x09,0x04,0x00,0xFD,0xFA,0xFB,0xF4,0xF4,0xF4,0xF4,0xF4,0xF1,0xED,0xE7,0xE4,
    0x1B,0x14,0x0D,0x08,0x03,0x00,0xFD,0xFA,0xF3,0xF3,0xF3,0xF0,0xEE,0xE9,0xE4,0xDD,0xDA,
    0x21,0x18,0x12,0x0D,0x08,0x04,0x00,0xFD,0xF8,0xF3,0xF1,0xEE,0xE9,0xE5,0xE2,0xD6,0xD4,
    0x27,0x1C,0x1B,0x14,0x0F,0x0A,0x05,0x00,0xFC,0xF8,0xF3,0xEF,0xE9,0xE3,0xE1,0xD6,0xCE,
    0x2B,0x21,0x20,0x1E,0x16,0x12,0x0D,0x07,0x00,0xFC,0xF7,0xF1,0xEB,0xE3,0xDF,0xD5,0xCC,
    0x2F,0x25,0x25,0x21,0x1B,0x1B,0x14,0x0E,0x08,0x00,0xFA,0xF3,0xEC,0xE2,0xDE,0xD6,0xCB,
    0x32,0x27,0x25,0x21,0x1E,0x1E,0x1B,0x15,0x0F,0x08,0x00,0xFA,0xF0,0xE5,0xDE,0xD6,0xCC,
    0x2E,0x26,0x25,0x23,0x21,0x1F,0x1B,0x18,0x12,0x0F,0x08,0x00,0xF7,0xE9,0xDF,0xD7,0xD0,
    0x29,0x24,0x24,0x23,0x20,0x20,0x1E,0x19,0x15,0x10,0x0D,0x08,0x00,0xF3,0xE1,0xDC,0xD4,
    0x24,0x21,0x20,0x1F,0x1D,0x1D,0x1B,0x19,0x17,0x14,0x12,0x0D,0x09,0x00,0xF3,0xE4,0xDD,
    0x1B,0x17,0x19,0x17,0x17,0x17,0x17,0x17,0x14,0x12,0x10,0x0D,0x0A,0x09,0x00,0xF0,0xE6,
    0x11,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0A,0x0B,0x0B,0x0B,0x0A,0x09,0x08,0x00,0xF1,
    0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,
};
#endif

#elif(_HW_OD_TABLE_TYPE == _OD_GEN_1)

#if(_HW_OD_LUT_MODE == _OD_8BIT_LUT)
BYTE code tOD_TABLE_COMMON[] =
{
    0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
    0x04,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
    0x09,0x05,0x00,0x01,0x00,0x02,0x06,0x03,0x06,0x06,0x06,0x03,0x06,0x06,0x06,0x06,0x06,
    0x0B,0x07,0x04,0x00,0x01,0x04,0x04,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x10,
    0x11,0x0F,0x09,0x04,0x00,0x03,0x06,0x05,0x0C,0x0C,0x0C,0x0C,0x0C,0x0F,0x13,0x19,0x1C,
    0x1B,0x14,0x0D,0x08,0x03,0x00,0x03,0x06,0x0D,0x0D,0x0D,0x10,0x12,0x17,0x1C,0x23,0x26,
    0x15,0x18,0x12,0x0D,0x08,0x04,0x00,0x03,0x08,0x0D,0x0F,0x12,0x17,0x1B,0x1E,0x2A,0x2C,
    0x17,0x1C,0x1B,0x14,0x0F,0x0A,0x05,0x00,0x04,0x08,0x0D,0x11,0x17,0x1D,0x1F,0x2A,0x32,
    0x1B,0x21,0x20,0x1E,0x16,0x12,0x0D,0x07,0x00,0x04,0x09,0x0F,0x15,0x1D,0x21,0x2B,0x34,
    0x1F,0x20,0x20,0x21,0x1B,0x1B,0x14,0x0E,0x08,0x00,0x06,0x0D,0x14,0x1E,0x22,0x2A,0x35,
    0x24,0x1F,0x1F,0x21,0x1E,0x1E,0x1B,0x15,0x0F,0x08,0x00,0x06,0x10,0x1B,0x22,0x2A,0x34,
    0x22,0x1A,0x1B,0x20,0x21,0x1F,0x1B,0x18,0x12,0x0F,0x08,0x00,0x09,0x17,0x21,0x29,0x30,
    0x1A,0x18,0x19,0x1E,0x20,0x20,0x1E,0x19,0x15,0x10,0x0D,0x08,0x00,0x0D,0x1F,0x24,0x2C,
    0x16,0x16,0x15,0x16,0x16,0x16,0x17,0x16,0x16,0x14,0x12,0x0D,0x09,0x00,0x0D,0x1C,0x23,
    0x13,0x10,0x12,0x11,0x12,0x12,0x12,0x12,0x11,0x11,0x10,0x0D,0x0A,0x09,0x00,0x10,0x1A,
    0x11,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0A,0x0B,0x0B,0x0B,0x0A,0x09,0x08,0x00,0x0F,
    0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,
};

#if(_FREESYNC_SUPPORT == _ON)
BYTE code tOD_TABLE_FREESYNC[] =
{
    0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
    0x04,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
    0x09,0x05,0x00,0x01,0x00,0x02,0x06,0x03,0x06,0x06,0x06,0x03,0x06,0x06,0x06,0x06,0x06,
    0x0B,0x07,0x04,0x00,0x01,0x04,0x04,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x10,
    0x11,0x0F,0x09,0x04,0x00,0x03,0x06,0x05,0x0C,0x0C,0x0C,0x0C,0x0C,0x0F,0x13,0x19,0x1C,
    0x1B,0x14,0x0D,0x08,0x03,0x00,0x03,0x06,0x0D,0x0D,0x0D,0x10,0x12,0x17,0x1C,0x23,0x26,
    0x15,0x18,0x12,0x0D,0x08,0x04,0x00,0x03,0x08,0x0D,0x0F,0x12,0x17,0x1B,0x1E,0x2A,0x2C,
    0x17,0x1C,0x1B,0x14,0x0F,0x0A,0x05,0x00,0x04,0x08,0x0D,0x11,0x17,0x1D,0x1F,0x2A,0x32,
    0x1B,0x21,0x20,0x1E,0x16,0x12,0x0D,0x07,0x00,0x04,0x09,0x0F,0x15,0x1D,0x21,0x2B,0x34,
    0x1F,0x20,0x20,0x21,0x1B,0x1B,0x14,0x0E,0x08,0x00,0x06,0x0D,0x14,0x1E,0x22,0x2A,0x35,
    0x24,0x1F,0x1F,0x21,0x1E,0x1E,0x1B,0x15,0x0F,0x08,0x00,0x06,0x10,0x1B,0x22,0x2A,0x34,
    0x22,0x1A,0x1B,0x20,0x21,0x1F,0x1B,0x18,0x12,0x0F,0x08,0x00,0x09,0x17,0x21,0x29,0x30,
    0x1A,0x18,0x19,0x1E,0x20,0x20,0x1E,0x19,0x15,0x10,0x0D,0x08,0x00,0x0D,0x1F,0x24,0x2C,
    0x16,0x16,0x15,0x16,0x16,0x16,0x17,0x16,0x16,0x14,0x12,0x0D,0x09,0x00,0x0D,0x1C,0x23,
    0x13,0x10,0x12,0x11,0x12,0x12,0x12,0x12,0x11,0x11,0x10,0x0D,0x0A,0x09,0x00,0x10,0x1A,
    0x11,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0B,0x0A,0x0B,0x0B,0x0B,0x0A,0x09,0x08,0x00,0x0F,
    0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,
};
#endif

#elif(_HW_OD_LUT_MODE == _OD_10BIT_LUT)

BYTE code tOD_TABLE_COMMON[] =
{
    0x00,0x00,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,
    0x04,0x80,0x00,0x00,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,
    0x09,0x80,0x05,0x80,0x00,0x00,0x01,0x80,0x00,0x80,0x02,0x80,0x06,0x80,0x03,0x80,0x06,0x80,0x06,0x80,0x06,0x80,0x03,0x80,0x06,0x80,0x06,0x80,0x06,0x80,0x06,0x80,0x06,0x80,
    0x0B,0x80,0x07,0x80,0x04,0x80,0x00,0x00,0x01,0x80,0x04,0x80,0x04,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x10,0x80,
    0x11,0x80,0x0F,0x80,0x09,0x80,0x04,0x80,0x00,0x00,0x03,0x80,0x06,0x80,0x05,0x80,0x0C,0x80,0x0C,0x80,0x0C,0x80,0x0C,0x80,0x0C,0x80,0x0F,0x80,0x13,0x80,0x19,0x80,0x1C,0x80,
    0x1B,0x80,0x14,0x80,0x0D,0x80,0x08,0x80,0x03,0x80,0x00,0x00,0x03,0x80,0x06,0x80,0x0D,0x80,0x0D,0x80,0x0D,0x80,0x10,0x80,0x12,0x80,0x17,0x80,0x1C,0x80,0x23,0x80,0x26,0x80,
    0x15,0x80,0x18,0x80,0x12,0x80,0x0D,0x80,0x08,0x80,0x04,0x80,0x00,0x00,0x03,0x80,0x08,0x80,0x0D,0x80,0x0F,0x80,0x12,0x80,0x17,0x80,0x1B,0x80,0x1E,0x80,0x2A,0x80,0x2C,0x80,
    0x17,0x80,0x1C,0x80,0x1B,0x80,0x14,0x80,0x0F,0x80,0x0A,0x80,0x05,0x80,0x00,0x00,0x04,0x80,0x08,0x80,0x0D,0x80,0x11,0x80,0x17,0x80,0x1D,0x80,0x1F,0x80,0x2A,0x80,0x32,0x80,
    0x1B,0x80,0x21,0x80,0x20,0x80,0x1E,0x80,0x16,0x80,0x12,0x80,0x0D,0x80,0x07,0x80,0x00,0x00,0x04,0x80,0x09,0x80,0x0F,0x80,0x15,0x80,0x1D,0x80,0x21,0x80,0x2B,0x80,0x34,0x80,
    0x1F,0x80,0x20,0x80,0x20,0x80,0x21,0x80,0x1B,0x80,0x1B,0x80,0x14,0x80,0x0E,0x80,0x08,0x80,0x00,0x00,0x06,0x80,0x0D,0x80,0x14,0x80,0x1E,0x80,0x22,0x80,0x2A,0x80,0x35,0x80,
    0x24,0x80,0x1F,0x80,0x1F,0x80,0x21,0x80,0x1E,0x80,0x1E,0x80,0x1B,0x80,0x15,0x80,0x0F,0x80,0x08,0x80,0x00,0x00,0x06,0x80,0x10,0x80,0x1B,0x80,0x22,0x80,0x2A,0x80,0x34,0x80,
    0x22,0x80,0x1A,0x80,0x1B,0x80,0x20,0x80,0x21,0x80,0x1F,0x80,0x1B,0x80,0x18,0x80,0x12,0x80,0x0F,0x80,0x08,0x80,0x00,0x00,0x09,0x80,0x17,0x80,0x21,0x80,0x29,0x80,0x30,0x80,
    0x1A,0x80,0x18,0x80,0x19,0x80,0x1E,0x80,0x20,0x80,0x20,0x80,0x1E,0x80,0x19,0x80,0x15,0x80,0x10,0x80,0x0D,0x80,0x08,0x80,0x00,0x00,0x0D,0x80,0x1F,0x80,0x24,0x80,0x2C,0x80,
    0x16,0x80,0x16,0x80,0x15,0x80,0x16,0x80,0x16,0x80,0x16,0x80,0x17,0x80,0x16,0x80,0x16,0x80,0x14,0x80,0x12,0x80,0x0D,0x80,0x09,0x80,0x00,0x00,0x0D,0x80,0x1C,0x80,0x23,0x80,
    0x13,0x80,0x10,0x80,0x12,0x80,0x11,0x80,0x12,0x80,0x12,0x80,0x12,0x80,0x12,0x80,0x11,0x80,0x11,0x80,0x10,0x80,0x0D,0x80,0x0A,0x80,0x09,0x80,0x00,0x00,0x10,0x80,0x1A,0x80,
    0x11,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0A,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0A,0x80,0x09,0x80,0x08,0x80,0x00,0x00,0x0F,0x80,
    0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x00,0x00,
};

#if(_FREESYNC_SUPPORT == _ON)
BYTE code tOD_TABLE_FREESYNC[] =
{
    0x00,0x00,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,0x02,0x80,
    0x04,0x80,0x00,0x00,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,
    0x09,0x80,0x05,0x80,0x00,0x00,0x01,0x80,0x00,0x80,0x02,0x80,0x06,0x80,0x03,0x80,0x06,0x80,0x06,0x80,0x06,0x80,0x03,0x80,0x06,0x80,0x06,0x80,0x06,0x80,0x06,0x80,0x06,0x80,
    0x0B,0x80,0x07,0x80,0x04,0x80,0x00,0x00,0x01,0x80,0x04,0x80,0x04,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x09,0x80,0x10,0x80,
    0x11,0x80,0x0F,0x80,0x09,0x80,0x04,0x80,0x00,0x00,0x03,0x80,0x06,0x80,0x05,0x80,0x0C,0x80,0x0C,0x80,0x0C,0x80,0x0C,0x80,0x0C,0x80,0x0F,0x80,0x13,0x80,0x19,0x80,0x1C,0x80,
    0x1B,0x80,0x14,0x80,0x0D,0x80,0x08,0x80,0x03,0x80,0x00,0x00,0x03,0x80,0x06,0x80,0x0D,0x80,0x0D,0x80,0x0D,0x80,0x10,0x80,0x12,0x80,0x17,0x80,0x1C,0x80,0x23,0x80,0x26,0x80,
    0x15,0x80,0x18,0x80,0x12,0x80,0x0D,0x80,0x08,0x80,0x04,0x80,0x00,0x00,0x03,0x80,0x08,0x80,0x0D,0x80,0x0F,0x80,0x12,0x80,0x17,0x80,0x1B,0x80,0x1E,0x80,0x2A,0x80,0x2C,0x80,
    0x17,0x80,0x1C,0x80,0x1B,0x80,0x14,0x80,0x0F,0x80,0x0A,0x80,0x05,0x80,0x00,0x00,0x04,0x80,0x08,0x80,0x0D,0x80,0x11,0x80,0x17,0x80,0x1D,0x80,0x1F,0x80,0x2A,0x80,0x32,0x80,
    0x1B,0x80,0x21,0x80,0x20,0x80,0x1E,0x80,0x16,0x80,0x12,0x80,0x0D,0x80,0x07,0x80,0x00,0x00,0x04,0x80,0x09,0x80,0x0F,0x80,0x15,0x80,0x1D,0x80,0x21,0x80,0x2B,0x80,0x34,0x80,
    0x1F,0x80,0x20,0x80,0x20,0x80,0x21,0x80,0x1B,0x80,0x1B,0x80,0x14,0x80,0x0E,0x80,0x08,0x80,0x00,0x00,0x06,0x80,0x0D,0x80,0x14,0x80,0x1E,0x80,0x22,0x80,0x2A,0x80,0x35,0x80,
    0x24,0x80,0x1F,0x80,0x1F,0x80,0x21,0x80,0x1E,0x80,0x1E,0x80,0x1B,0x80,0x15,0x80,0x0F,0x80,0x08,0x80,0x00,0x00,0x06,0x80,0x10,0x80,0x1B,0x80,0x22,0x80,0x2A,0x80,0x34,0x80,
    0x22,0x80,0x1A,0x80,0x1B,0x80,0x20,0x80,0x21,0x80,0x1F,0x80,0x1B,0x80,0x18,0x80,0x12,0x80,0x0F,0x80,0x08,0x80,0x00,0x00,0x09,0x80,0x17,0x80,0x21,0x80,0x29,0x80,0x30,0x80,
    0x1A,0x80,0x18,0x80,0x19,0x80,0x1E,0x80,0x20,0x80,0x20,0x80,0x1E,0x80,0x19,0x80,0x15,0x80,0x10,0x80,0x0D,0x80,0x08,0x80,0x00,0x00,0x0D,0x80,0x1F,0x80,0x24,0x80,0x2C,0x80,
    0x16,0x80,0x16,0x80,0x15,0x80,0x16,0x80,0x16,0x80,0x16,0x80,0x17,0x80,0x16,0x80,0x16,0x80,0x14,0x80,0x12,0x80,0x0D,0x80,0x09,0x80,0x00,0x00,0x0D,0x80,0x1C,0x80,0x23,0x80,
    0x13,0x80,0x10,0x80,0x12,0x80,0x11,0x80,0x12,0x80,0x12,0x80,0x12,0x80,0x12,0x80,0x11,0x80,0x11,0x80,0x10,0x80,0x0D,0x80,0x0A,0x80,0x09,0x80,0x00,0x00,0x10,0x80,0x1A,0x80,
    0x11,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0A,0x80,0x0B,0x80,0x0B,0x80,0x0B,0x80,0x0A,0x80,0x09,0x80,0x08,0x80,0x00,0x00,0x0F,0x80,
    0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x07,0x80,0x00,0x00,
};
#endif
#endif // End of #if(_OD_LUT_MODE == _OD_8BIT_LUT)

#endif // End of #if(_OD_TABLE_TYPE == _OD_GEN_0)

