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
// ID Code      : ScalerOsdSRAM.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Osd/ScalerOsd.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usOsdSRAMColAMax;
WORD g_usOsdSRAMColBMax;
bit g_bOsdSetMapAAndMapB;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_OSD_8_BIT_FONT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set OSD 8 bit font offset
// Input Value  : ucOffset
// Output Value :
//--------------------------------------------------
void ScalerOsd8BitFontOffset(WORD usOffset)
{
    // char_sel_8bit_offset[11:8]
    ScalerSetBit(P3A_6E_FRAME_CTRL_F_FONT_8BIT_OFFSET_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usOffset) & 0x0F);
    ScalerSetByte(P3A_6F_FRAME_CTRL_F_FONT_8BIT_OFFSET_L, LOBYTE(usOffset));
}
#endif

//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol. ucLength. usHeight. -> Just that !!
//                usPixelLength                     -> BLANK_FONT : 2~511
//                ucBackgroundColor                 -> Color number
//                enumOsdBlinkingType               -> _OSD_BLANK_FONT or _OSD_BLANK_ALIGN
// Output Value :
//--------------------------------------------------
void ScalerOsdBlankFont(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, WORD usPixelLength, BYTE ucBackgroundColor, EnumOsdBlankType enumOsdBlankingType)
{
    WORD usTemp = 0;

    enumOsdBlankingType = _OSD_BLANK_FONT;

    // Blank font length at least 2 pixel
    if(usPixelLength < 2)
    {
        usPixelLength = 2;
    }

    for(usTemp = 0; usTemp < usHeight; usTemp++)
    {
        ScalerOsdSramDataValue(usRow + usTemp, usCol, usLength, (((BYTE)enumOsdBlankingType & 0x03) << 6) | (HIBYTE(usPixelLength & _HW_OSD_BLANK_FONT_LEN_BIT)), _OSD_BYTE0);
        ScalerOsdSramDataValue(usRow + usTemp, usCol, usLength, (usPixelLength & 0xFF), _OSD_BYTE1);
        ScalerOsdSramDataValue(usRow + usTemp, usCol, usLength, (ucBackgroundColor & _HW_OSD_PALETTE_BIT), _OSD_BYTE2);
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdBlankFont(ROW(0), COL(1), LENGTH(1), HEIGHT(1), VALUES(4), BGCOLOR(0), _OSD_BLINKING_EFFECT_DISABLE);
*/

//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol. usLength. usHeight.     -> Just that !!
//                ucForegroundColor. ucBackgroundColor  -> Color number
// Output Value :
//--------------------------------------------------
void ScalerOsdChange1BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucForegroundColor, BYTE ucBackgroundColor)
{
    WORD usTemp = 0;

    for(usTemp = 0; usTemp < usHeight; usTemp++)
    {
        ScalerOsdSramDataValue(usRow + usTemp, usCol, usLength, (((ucForegroundColor & 0x0F) << 4) | (ucBackgroundColor & 0x0F)), _OSD_BYTE2);
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
        if(GET_OSD_COMMAND_4_BYTE_ENABLE() == _ENABLE)
        {
            ScalerOsdSramDataValue(usRow + usTemp, usCol, usLength, ((ucForegroundColor & 0xF0) | ((ucBackgroundColor & 0xF0) >> 4)), _OSD_BYTE3);
        }
#endif
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdChange1BitColor(ROW(0), COL(0), LENGTH(1), HEIGHT(1), FGCOLOR(3), BGCOLOR(4));
*/


//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol. usLength. usHeight.       -> Just that !!
//                ucColor0. ucColor1. ucColor2. ucColor3  -> Color number
// Output Value :
//--------------------------------------------------
void ScalerOsdChange2BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3)
{
    WORD usTemp = 0;
    BYTE ucByte0 = _BIT7;
    BYTE ucByte2 = 0;

    if((ucColor0 > 7) && (ucColor3 > 7))
    {
        ucByte0 |= _BIT5;
        ucColor0 -= 8;
        ucColor3 -= 8;
    }

    if((ucColor1 > 7) && (ucColor2 > 7))
    {
        ucByte0 |= _BIT4;
        ucColor1 -= 8;
        ucColor2 -= 8;
    }

    ucByte0 = ucByte0 | ((ucColor3 & 0x07) << 1) | ((ucColor0 & _BIT2) >> 2);
    ucByte2 = ((ucColor0 & 0x03) << 6) | ((ucColor2 & 0x07) << 3) | (ucColor1 & 0x07);

    for(usTemp = 0; usTemp < usHeight; usTemp++)
    {
        ScalerOsdSramDataValue2Byte(usRow + usTemp, usCol, usLength, ucByte0, ucByte2, _OSD_BYTE0_BYTE2);
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdChange2BitColor(ROW(0), COL(0), LENGTH(1), HEIGHT(1), COLOR00(0), COLOR01(1), COLOR10(2), COLOR11(3));
*/

//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol. usLength. usHeight.       -> Just that !!
//                ucColor0. ucColor1. ucColor2. ucColor3  -> Color number
// Output Value :
//--------------------------------------------------
void ScalerOsdChange2BitColor16_31(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3)
{
    BYTE ucRowCmdByte0 = _BIT7;
    bit bOSDOn = _OFF;
    WORD usTemp = 0;

    // Get OSD Status
    bOSDOn = ScalerGetBit(P3A_00_FRAME_CTRL_F_OSD_EN, _BIT0);

    // Set OSD Circuit Enable for Write-Protection Function effective in OSD enable.
    ScalerSetBit(P3A_00_FRAME_CTRL_F_OSD_EN, ~(_BIT0), _ON);

    // Check Global Double Buffer
    if(bOSDOn == _OFF)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }

    if(((ucColor0 >= 16) && (ucColor1 >= 16) && (ucColor2 >= 16) && (ucColor3 >= 16)))
    {
        ucRowCmdByte0 |= _BIT5;
        ucColor0 -= 16;
        ucColor1 -= 16;
        ucColor2 -= 16;
        ucColor3 -= 16;
    }

    if((GET_OSD_SET_MAPA_AND_MAP_B() == _ENABLE) ||
       (ScalerGetBit(P3A_01_FRAME_CTRL_F_MAP_EN, _BIT1) == _BIT1) ||
       (GET_OSD_MAPB_ROW_BASE_ADDR() != 0) ||
       (GET_OSD_MAPB_CHAR_SEL_ADDR() != 0))
    {
        if(usRow >= _OSD_MAP_B_ROW_OFFSET)
        {
            ScalerOsdSramAddressSetCommand((GET_OSD_MAPB_ROW_BASE_ADDR() + (usRow - _OSD_MAP_B_ROW_OFFSET)), _OSD_BYTE0);
        }
        else
        {
            ScalerOsdSramAddressSetCommand((0 + usRow), _OSD_BYTE0);
        }
    }
    else
    {
        ScalerOsdSramAddressSetCommand((0 + usRow), _OSD_BYTE0);
    }

    for(usTemp = 0; usTemp < usHeight; usTemp++)
    {
        ScalerOsdSetDataPortSram(ucRowCmdByte0);
    }

    ScalerOsdChange2BitColor(usRow, usCol, usLength, usHeight, ucColor0, ucColor1, ucColor2, ucColor3);

    // Recovery OSD Status
    if(bOSDOn == _OFF)
    {
        ScalerSetBit(P3A_00_FRAME_CTRL_F_OSD_EN, ~(_BIT0), bOSDOn);
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdChange2BitColor(ROW(0), COL(0), LENGTH(1), HEIGHT(1), COLOR00(0), COLOR01(1), COLOR10(2), COLOR11(3));
*/

//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol. usLength. usHeight.  -> Just that !!
//                ucBackgroundColor                  -> Color number
//                ucColorPaletteType                 -> _OSD_4BIT_PALETTE_00_01_02_03 | _OSD_4BIT_PALETTE_04_05_06_07 | _OSD_4BIT_PALETTE_08_09_10_11 | _OSD_4BIT_PALETTE_12_13_14_15
//                                                     (_OSD_4BIT_PALETTE_16_17_18_19   _OSD_4BIT_PALETTE_20_21_22_23   _OSD_4BIT_PALETTE_24_25_26_27   _OSD_4BIT_PALETTE_28_29_30_31)
//                                                     (_OSD_4BIT_PALETTE_32_33_34_35   _OSD_4BIT_PALETTE_36_37_38_39   _OSD_4BIT_PALETTE_40_41_42_43   _OSD_4BIT_PALETTE_44_45_46_47)
//                                                     (_OSD_4BIT_PALETTE_48_49_50_51   _OSD_4BIT_PALETTE_52_53_54_55   _OSD_4BIT_PALETTE_56_57_58_59   _OSD_4BIT_PALETTE_50_61_62_63)
// Output Value :
//--------------------------------------------------
void ScalerOsdChange4BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucBackgroundColor, BYTE ucColorPaletteType)
{
    WORD usTemp = 0;

    for(usTemp = 0; usTemp < usHeight; usTemp++)
    {
        ScalerOsdSramDataValue2Byte(usRow + usTemp, usCol, usLength, (0xC0 | ucBackgroundColor), ucColorPaletteType, _OSD_BYTE0_BYTE2);
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdChange4BitColor(ROW(0), COL(0), LENGTH(1), HEIGHT(1), BGCOLOR(0), (_OSD_4BIT_PALETTE_00_01_02_03 | _OSD_4BIT_PALETTE_04_05_06_07 | _OSD_4BIT_PALETTE_08_09_10_11 | _OSD_4BIT_PALETTE_12_13_14_15));
*/

//--------------------------------------------------
// Description  : Set OSD Char Command All Byte Series
// Input Value  : usCharAddr -> SRAM address
//                ucByte0      -> Byte0 data
//                ucByte1      -> Byte1 data
//                ucByte2      -> Byte2 data
//                usLength     -> Length
// Output Value :
//--------------------------------------------------
void ScalerOsdCharCommandAllByteSeries(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2, WORD usLength)
{
    ScalerOsdSramAddressSetCommand(usCharAddr, _OSD_BYTEALL);

    do
    {
        ScalerSetByte(P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT, ucByte0);
        ScalerSetByte(P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT, ucByte1);
        ScalerSetByte(P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT, ucByte2);
    }
    while(--usLength);
}

//--------------------------------------------------
// Description  : Set OSD Char Command Byte Series
// Input Value  : usCharAddr       -> SRAM address
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2 or _OSD_BYTEALL
//                ucData           -> ucByteSelect' data
//                usLength         -> Length
// Output Value :
//--------------------------------------------------
void ScalerOsdCharCommandByteSeries(WORD usCharAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData, WORD usLength)
{
    ScalerOsdSramAddressSetCommand(usCharAddr, enumOsdWriteType);

    do
    {
        ScalerSetByte(P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT, ucData);
    }
    while(--usLength);
}

//--------------------------------------------------
// Description  : Set OSD Command All Byte
// Input Value  : usCharAddr   -> SRAM address
//                ucByte0      -> Byte0 data
//                ucByte1      -> Byte1 data
//                ucByte2      -> Byte2 data
// Output Value :
//--------------------------------------------------
void ScalerOsdCommandAllByte(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2)
{
    ScalerOsdWriteAllByte(_OSD_SRAM_COMMAND, usCharAddr, ucByte0, ucByte1, ucByte2);
}

//--------------------------------------------------
// Description  : Set OSD Command Byte
// Input Value  : usAddr           -> SRAM address
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2 or _OSD_BYTEALL
//                ucData           -> ucByteSelect's data
// Output Value :
//--------------------------------------------------
void ScalerOsdCommandByte(WORD usAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData)
{
    ScalerOsdWriteByte(((BYTE)enumOsdWriteType << 4) | _OSD_SRAM_COMMAND, _OSD_WITHOUT_DB, usAddr, ucData);
}

//--------------------------------------------------
// Description  : Set decode compression data or not, Compression enable/disable
// Input Value  : enumDecodeCompression -> _OSD_DECODE_COMPRESSED or _OSD_DECODE_NON_COMPRESSED
// Input Value  : ucConpressionEn -> _OSD_COMPRESSION_DISABLE or _OSD_COMPRESSION_ENABLE
// Output Value :
//--------------------------------------------------
void ScalerOsdCompressionCtrl(EnumOsdDecodeCompressionType enumDecodeCompression, bit bCompressionEnable)
{
    enumDecodeCompression = enumDecodeCompression;
    ScalerSetBit(P3A_4F_FRAME_CTRL_F_COMPRESSION_EN, ~(_BIT1 | _BIT0), bCompressionEnable);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdCompressionCtrl(_OSD_DECODE_NON_COMPRESSED, _OSD_COMPRESSION_ENABLE);
*/

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerOsdSetDoubleBufferReady(void)
{
    // Check Double Buffer Mode
    if(ScalerGetBit(P3A_00_FRAME_CTRL_F_OSD_EN, (_BIT7 | _BIT6)) != _BIT7)
    {
        return;
    }

    ScalerSetBit(P3A_00_FRAME_CTRL_F_OSD_EN, ~_BIT5, _BIT5);
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerOsdWaitDoubleBufferReady(void)
{
    BYTE ucIdx = 0;

    // Check Double Buffer Mode
    if(ScalerGetBit(P3A_00_FRAME_CTRL_F_OSD_EN, (_BIT7 | _BIT6)) != _BIT7)
    {
        return;
    }

    for(ucIdx = 100; ucIdx > 0; ucIdx--)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

        if(ScalerGetBit(P3A_00_FRAME_CTRL_F_OSD_EN, _BIT5) == 0x00)
        {
            break;
        }
    }
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerOsdFontLibraryRotation(void)
{
    BYTE ucIdx = 0;

    for(ucIdx = 100; ucIdx > 0; ucIdx--)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);

        if(ScalerGetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, _BIT6) == 0x00)
        {
            break;
        }
    }
}

//--------------------------------------------------
// Description  : MASK Specific Region of Font Enable/Disable
// Input Value  : bOnOff
// Output Value :
//--------------------------------------------------
void ScalerOsdFontMaskRegionOnOff(EnumOsdMapType enumOsdMapType, bit bOnOff)
{
    switch(enumOsdMapType)
    {
        case _OSD_A:
            ScalerSetBit(P3A_50_FRAME_CTRL_F_MASK_MAP_ENABLE, ~_BIT0, (bOnOff == _ENABLE) ? (_BIT0) : (0x00));
            break;
        case _OSD_B:
            ScalerSetBit(P3A_50_FRAME_CTRL_F_MASK_MAP_ENABLE, ~_BIT1, (bOnOff == _ENABLE) ? (_BIT1) : (0x00));
            break;
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
        case _OSD_C:
            ScalerSetBit(P3A_50_FRAME_CTRL_F_MASK_MAP_ENABLE, ~_BIT2, (bOnOff == _ENABLE) ? (_BIT2) : (0x00));
            break;
        case _OSD_D:
            ScalerSetBit(P3A_50_FRAME_CTRL_F_MASK_MAP_ENABLE, ~_BIT3, (bOnOff == _ENABLE) ? (_BIT3) : (0x00));
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : MASK Specific Region of Font
// Input Value  : usRowStart
// Input Value  : usRowEnd
// Input Value  : usColumnStart
// Input Value  : usColumnEnd
// Output Value :
//--------------------------------------------------
void ScalerOsdFontMaskRegionSet(EnumOsdMapType enumOsdMapType, WORD usRowStart, WORD usRowEnd, WORD usColumnStart, WORD usColumnEnd)
{
    switch(enumOsdMapType)
    {
        case _OSD_A:
            // MASK Row Start/End of Font A
            ScalerSetBit(P3A_51_FRAME_CTRL_F_MASK_MAP_A_ROW_H, ~(HIBYTE(_HW_OSD_MASK_MAP_ROW_BIT)), HIBYTE(usRowStart & _HW_OSD_MASK_MAP_ROW_BIT));
            ScalerSetByte(P3A_52_FRAME_CTRL_F_MASK_MAP_A_ROW_M, LOBYTE(usRowStart));
            ScalerSetBit(P3A_51_FRAME_CTRL_F_MASK_MAP_A_ROW_H, ~(HIBYTE(_HW_OSD_MASK_MAP_ROW_BIT) << 4), HIBYTE(usRowEnd & _HW_OSD_MASK_MAP_ROW_BIT) << 4);
            ScalerSetByte(P3A_53_FRAME_CTRL_F_MASK_MAP_A_ROW_L, LOBYTE(usRowEnd));
            // MASK Column Start/End of Font A
            ScalerSetBit(P3A_54_FRAME_CTRL_F_MASK_MAP_A_COL_H, ~(HIBYTE(_HW_OSD_MASK_MAP_COLUMN_BIT)), HIBYTE(usColumnStart & _HW_OSD_MASK_MAP_COLUMN_BIT));
            ScalerSetByte(P3A_55_FRAME_CTRL_F_MASK_MAP_A_COL_M, LOBYTE(usColumnStart));
            ScalerSetBit(P3A_54_FRAME_CTRL_F_MASK_MAP_A_COL_H, ~(HIBYTE(_HW_OSD_MASK_MAP_COLUMN_BIT) << 4), HIBYTE(usColumnEnd & _HW_OSD_MASK_MAP_COLUMN_BIT) << 4);
            ScalerSetByte(P3A_56_FRAME_CTRL_F_MASK_MAP_A_COL_L, LOBYTE(usColumnEnd));
            break;
        case _OSD_B:
            // MASK Row Start/End of Font B
            ScalerSetBit(P3A_57_FRAME_CTRL_F_MASK_MAP_B_ROW_H, ~(HIBYTE(_HW_OSD_MASK_MAP_ROW_BIT)), HIBYTE(usRowStart & _HW_OSD_MASK_MAP_ROW_BIT));
            ScalerSetByte(P3A_58_FRAME_CTRL_F_MASK_MAP_B_ROW_M, LOBYTE(usRowStart));
            ScalerSetBit(P3A_57_FRAME_CTRL_F_MASK_MAP_B_ROW_H, ~(HIBYTE(_HW_OSD_MASK_MAP_ROW_BIT) << 4), HIBYTE(usRowEnd & _HW_OSD_MASK_MAP_ROW_BIT) << 4);
            ScalerSetByte(P3A_59_FRAME_CTRL_F_MASK_MAP_B_ROW_L, LOBYTE(usRowEnd));

            // MASK Column Start/End of Font B
            ScalerSetBit(P3A_5A_FRAME_CTRL_F_MASK_MAP_B_COL_H, ~(HIBYTE(_HW_OSD_MASK_MAP_COLUMN_BIT)), HIBYTE(usColumnStart & _HW_OSD_MASK_MAP_COLUMN_BIT));
            ScalerSetByte(P3A_5B_FRAME_CTRL_F_MASK_MAP_B_COL_M, LOBYTE(usColumnStart));
            ScalerSetBit(P3A_5A_FRAME_CTRL_F_MASK_MAP_B_COL_H, ~(HIBYTE(_HW_OSD_MASK_MAP_COLUMN_BIT) << 4), HIBYTE(usColumnEnd & _HW_OSD_MASK_MAP_COLUMN_BIT) << 4);
            ScalerSetByte(P3A_5C_FRAME_CTRL_F_MASK_MAP_B_COL_L, LOBYTE(usColumnEnd));
            break;
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
        case _OSD_C:
            // MASK Row Start/End of Font C
            ScalerSetBit(P3A_5D_FRAME_CTRL_F_MASK_MAP_C_ROW_H, ~(HIBYTE(_HW_OSD_MASK_MAP_ROW_BIT)), HIBYTE(usRowStart & _HW_OSD_MASK_MAP_ROW_BIT));
            ScalerSetByte(P3A_5E_FRAME_CTRL_F_MASK_MAP_C_ROW_M, LOBYTE(usRowStart));
            ScalerSetBit(P3A_5D_FRAME_CTRL_F_MASK_MAP_C_ROW_H, ~(HIBYTE(_HW_OSD_MASK_MAP_ROW_BIT) << 4), HIBYTE(usRowEnd & _HW_OSD_MASK_MAP_ROW_BIT) << 4);
            ScalerSetByte(P3A_5F_FRAME_CTRL_F_MASK_MAP_C_ROW_L, LOBYTE(usRowEnd));
            // MASK Column Start/End of Font C
            ScalerSetBit(P3A_60_FRAME_CTRL_F_MASK_MAP_C_COL_H, ~(HIBYTE(_HW_OSD_MASK_MAP_COLUMN_BIT)), HIBYTE(usColumnStart & _HW_OSD_MASK_MAP_COLUMN_BIT));
            ScalerSetByte(P3A_61_FRAME_CTRL_F_MASK_MAP_C_COL_M, LOBYTE(usColumnStart));
            ScalerSetBit(P3A_60_FRAME_CTRL_F_MASK_MAP_C_COL_H, ~(HIBYTE(_HW_OSD_MASK_MAP_COLUMN_BIT) << 4), HIBYTE(usColumnEnd & _HW_OSD_MASK_MAP_COLUMN_BIT) << 4);
            ScalerSetByte(P3A_62_FRAME_CTRL_F_MASK_MAP_C_COL_L, LOBYTE(usColumnEnd));
            break;
        case _OSD_D:
            // MASK Row Start/End of Font D
            ScalerSetBit(P3A_63_FRAME_CTRL_F_MASK_MAP_D_ROW_H, ~(HIBYTE(_HW_OSD_MASK_MAP_ROW_BIT)), HIBYTE(usRowStart & _HW_OSD_MASK_MAP_ROW_BIT));
            ScalerSetByte(P3A_64_FRAME_CTRL_F_MASK_MAP_D_ROW_M, LOBYTE(usRowStart));
            ScalerSetBit(P3A_63_FRAME_CTRL_F_MASK_MAP_D_ROW_H, ~(HIBYTE(_HW_OSD_MASK_MAP_ROW_BIT) << 4), HIBYTE(usRowEnd & _HW_OSD_MASK_MAP_ROW_BIT) << 4);
            ScalerSetByte(P3A_65_FRAME_CTRL_F_MASK_MAP_D_ROW_L, LOBYTE(usRowEnd));
            // MASK Column Start/End of Font D
            ScalerSetBit(P3A_66_FRAME_CTRL_F_MASK_MAP_D_COL_H, ~(HIBYTE(_HW_OSD_MASK_MAP_COLUMN_BIT)), HIBYTE(usColumnStart & _HW_OSD_MASK_MAP_COLUMN_BIT));
            ScalerSetByte(P3A_67_FRAME_CTRL_F_MASK_MAP_D_COL_M, LOBYTE(usColumnStart));
            ScalerSetBit(P3A_66_FRAME_CTRL_F_MASK_MAP_D_COL_H, ~(HIBYTE(_HW_OSD_MASK_MAP_COLUMN_BIT) << 4), HIBYTE(usColumnEnd & _HW_OSD_MASK_MAP_COLUMN_BIT) << 4);
            ScalerSetByte(P3A_68_FRAME_CTRL_F_MASK_MAP_D_COL_L, LOBYTE(usColumnEnd));
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set Osd Font Rotation
// Input Value  : enumRotType
// Input Value  : ucFontDownloadRotEn
// Output Value :
//--------------------------------------------------
void ScalerOsdFontRotateCtrlAuto(EnumOsdRotateType enumRotType, BYTE ucFontDownloadRotEn)
{
    switch(enumRotType)
    {
        default:
        case _OSD_ROTATE_DEGREE_0:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT1 | _BIT0), 0x00);
            break;

        case _OSD_ROTATE_DEGREE_90:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT1 | _BIT0), _BIT0);
            break;

        case _OSD_ROTATE_DEGREE_270:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _OSD_ROTATE_DEGREE_180:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT1 | _BIT0), _BIT1);
            break;
    }

    if(((bit)ucFontDownloadRotEn) == _ENABLE)
    {
        ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~_BIT7, 0x00);
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdFontRotateCtrl(_OSD_ROTATE_DEGREE_90, _ENABLE);
*/

//--------------------------------------------------
// Description  : Osd Load Hardware VLC : Font data
// Input Value  : *pArray          -> VLC table
//                usVLCTableSize   -> Use VLC_TABLE_SIZE(VLC table)
//                ucBankNum        -> Bank number (GET_CURRENT_BANK_NUMBER())
//                usOffset         -> Font address
//                usFontTableStart -> Font base address
//                ucOsdRotateType  -> _OSD_ROTATE_DEGREE_0 or _OSD_ROTATE_DEGREE_90 or _OSD_ROTATE_DEGREE_270 or _OSD_ROTATE_DEGREE_180
//                bTableLocation   ->
// Output Value :
//--------------------------------------------------
void ScalerOsdHardwareCompressionFont(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, EnumOsdRotateType enumOsdRotateType, bit bTableLocation)
{
    BYTE ucVlcType = 0x00;
    BYTE ucFFF1Backup = MCU_FFF1_SCA_WR_INTRVL;

    if(enumOsdRotateType == _OSD_ROTATE_DEGREE_90)
    {
        ucVlcType = _OSD_ROTATE_CW | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE;
    }
    else if(enumOsdRotateType == _OSD_ROTATE_DEGREE_270)
    {
        ucVlcType = _OSD_ROTATE_CCW | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE;
    }
    else if(enumOsdRotateType == _OSD_ROTATE_DEGREE_180)
    {
        ucVlcType = _OSD_ROTATE_CW180 | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE;
    }
    else
    {
        ucVlcType = _OSD_ROTATE_NO_SWAP | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE;
    }

    // rotation
    ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT7 | _BIT1 | _BIT0), ucVlcType);

    ScalerOsdSetAddrSramFont(usOffset);

    MCU_FFF1_SCA_WR_INTRVL = ((ucFFF1Backup & (~(0x8F))) | (_BIT7 | _BIT1));

    ScalerOsdBurstWriteDataPortSram(pucArray, usVLCTableSize, ucBankNum, _BURSTWRITE_DATA_OSD, bTableLocation);

    MCU_FFF1_SCA_WR_INTRVL = ucFFF1Backup;

    // Font download roatation disable
    ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~_BIT7, _OSD_ROTATE_HARDWARE_ROTATION_DISABLE);
}

//--------------------------------------------------
// Description  : Osd Load Hardware VLC : Font
// Input Value  : *pArray          -> VLC table
//                usVLCTableSize   -> Use VLC_TABLE_SIZE(VLC table)
//                ucBankNum        -> Bank number (GET_CURRENT_BANK_NUMBER())
//                usOffset         -> Font address
//                usFontTableStart -> Font base address
//                ucOsdRotateType  -> _OSD_ROTATE_DEGREE_0 or _OSD_ROTATE_DEGREE_90 or _OSD_ROTATE_DEGREE_270 or _OSD_ROTATE_DEGREE_180
//                enumSramType --> _OSD_SRAM_FONT or _OSD_SRAM_COMMAND
// Output Value :
//--------------------------------------------------
void ScalerOsdHardwareVLCFont(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, EnumOsdRotateType enumOsdRotateType, bit bTableLocation)
{
    BYTE ucVlcType = 0;

    if(enumOsdRotateType == _OSD_ROTATE_DEGREE_90)
    {
        ucVlcType = _OSD_ROTATE_CW | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE;
    }
    else if(enumOsdRotateType == _OSD_ROTATE_DEGREE_270)
    {
        ucVlcType = _OSD_ROTATE_CCW | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE;
    }
    else if(enumOsdRotateType == _OSD_ROTATE_DEGREE_180)
    {
        ucVlcType = _OSD_ROTATE_CW180 | _OSD_ROTATE_HARDWARE_ROTATION_ENABLE;
    }
    else
    {
        ucVlcType = _OSD_ROTATE_NO_SWAP;
    }

    // rotation
    ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT7 | _BIT1 | _BIT0), ucVlcType);

    ScalerBurstWrite(pucArray, 8, ucBankNum, P3A_47_FRAME_CTRL_F_VLC_0_1, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);

    // osd compression enable
    ScalerSetBit(P3A_4F_FRAME_CTRL_F_COMPRESSION_EN, ~(_BIT1 | _BIT0), _OSD_COMPRESSION_ENABLE);

    pucArray += 10;

    ScalerOsdSetAddrSramFont(usOffset);
    ScalerOsdBurstWriteDataPortSram(pucArray, usVLCTableSize, ucBankNum, _BURSTWRITE_DATA_OSD, bTableLocation);

    // OSD HW needs time to process it and then write decompressed data into SRAM.
    DELAY_XUS(500);

    // osd compression disable
    ScalerSetBit(P3A_4F_FRAME_CTRL_F_COMPRESSION_EN, ~(_BIT1 | _BIT0), _OSD_COMPRESSION_DISABLE);

    // Font download rotation disable
    ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT7), _OSD_ROTATE_HARDWARE_ROTATION_DISABLE);
}

//--------------------------------------------------
// Description  : Osd Load Hardware VLC : Command
// Input Value  : *pArray          -> VLC table
//                usVLCTableSize   -> Use VLC_TABLE_SIZE(VLC table)
//                ucBankNum        -> Bank number (GET_CURRENT_BANK_NUMBER())
//                usOffset         -> Font address
//                usFontTableStart -> Font base address
//                enumSramType --> _OSD_SRAM_FONT or _OSD_SRAM_COMMAND
// Output Value :
//--------------------------------------------------
void ScalerOsdHardwareVLCCommand(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, bit bTableLocation)
{
    ScalerBurstWrite(pucArray, 8, ucBankNum, P3A_47_FRAME_CTRL_F_VLC_0_1, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);

    // osd compression enable
    ScalerSetBit(P3A_4F_FRAME_CTRL_F_COMPRESSION_EN, ~(_BIT1 | _BIT0), _OSD_COMPRESSION_ENABLE);

    pucArray += 10;

    ScalerOsdSramAddressSetCommand(usOffset, _OSD_BYTEALL);
    ScalerOsdBurstWriteDataPortSram(pucArray, usVLCTableSize, ucBankNum, _BURSTWRITE_DATA_OSD, bTableLocation);

    // OSD HW needs time to process it and then write decompressed data into SRAM.
    DELAY_XUS(500);

    // osd compression disable
    ScalerSetBit(P3A_4F_FRAME_CTRL_F_COMPRESSION_EN, ~(_BIT1 | _BIT0), _OSD_COMPRESSION_DISABLE);
}

//--------------------------------------------------
// Description  :
// Input Value  : usRow -> ROW_MAPA(x), ROW_MAPB(x)
//                ucHeight -> 1 ~ 64
//                usLength -> number of row to be changed
// Output Value :
//--------------------------------------------------
void ScalerOsdRowHeight(WORD usRow, BYTE ucHeight, WORD usLength)
{
    WORD usIdx = 0;

    if(ucHeight > 64)
    {
        ucHeight = 64;
    }

    ucHeight--;

    if((GET_OSD_SET_MAPA_AND_MAP_B() == _ENABLE) ||
       (ScalerGetBit(P3A_01_FRAME_CTRL_F_MAP_EN, _BIT1) == _BIT1) ||
       (GET_OSD_MAPB_ROW_BASE_ADDR() != 0) ||
       (GET_OSD_MAPB_CHAR_SEL_ADDR() != 0))
    {
        if(usRow >= _OSD_MAP_B_ROW_OFFSET)
        {
            ScalerOsdSramAddressSetCommand((GET_OSD_MAPB_ROW_BASE_ADDR() + (usRow - _OSD_MAP_B_ROW_OFFSET)), _OSD_BYTE1);
        }
        else
        {
            ScalerOsdSramAddressSetCommand((0 + usRow), _OSD_BYTE1);
        }
    }
    else
    {
        ScalerOsdSramAddressSetCommand((0 + usRow), _OSD_BYTE1);
    }

    for(usIdx = 0; usIdx < usLength; usIdx++)
    {
        ScalerOsdSetDataPortSram(ucHeight);
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdRowHeight(ROW_MAPA(0), HEIGHT(31), LENGTH(3));
*/

//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol.     -> Just that !!
//                enumOsdWriteType  -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
// Output Value :
//--------------------------------------------------
void ScalerOsdSramAddressCount(WORD usRow, WORD usCol, EnumOsdWriteType enumOsdWriteType)
{
    WORD usCharCommandStartAddress = 0;
    WORD usColSize = 0;

    if((GET_OSD_SET_MAPA_AND_MAP_B() == _ENABLE) ||
       (ScalerGetBit(P3A_01_FRAME_CTRL_F_MAP_EN, _BIT1) == _BIT1) ||
       (GET_OSD_MAPB_ROW_BASE_ADDR() != 0) ||
       (GET_OSD_MAPB_CHAR_SEL_ADDR() != 0))
    {
        if(usRow >= _OSD_MAP_B_ROW_OFFSET)
        {
            usRow -= _OSD_MAP_B_ROW_OFFSET;
            usColSize = GET_OSD_MAPB_COL_MAX();
            // Font Select Base B
            usCharCommandStartAddress = GET_OSD_MAPB_CHAR_SEL_ADDR();
        }
        else
        {
            usColSize = GET_OSD_MAPA_COL_MAX();
            // Font Select Base A
            usCharCommandStartAddress = GET_OSD_MAPA_CHAR_SEL_ADDR();
        }
    }
    else
    {
        usColSize = GET_OSD_MAPA_COL_MAX();
        // Font Select Base A
        usCharCommandStartAddress = GET_OSD_MAPA_CHAR_SEL_ADDR();
    }

    usCharCommandStartAddress = usCharCommandStartAddress + (usRow * usColSize) + usCol;
    ScalerOsdAddrSet(_OSD_SRAM_COMMAND, enumOsdWriteType, usCharCommandStartAddress, _OSD_WITHOUT_DB);
}


//--------------------------------------------------
// Description  : SRAM address value and which byte : Row/Character Command
// Input Value  : usSramAddress -> SRAM address
//                enumOsdWriteType    -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2 or _OSD_BYTEALL
// Output Value :
//--------------------------------------------------
void ScalerOsdSramAddressSetCommand(WORD usSramAddress, EnumOsdWriteType enumOsdWriteType)
{
    // Select Which Byte to Write: 001: Byte0, 010: Byte1, 100: Byte2, 011: Byte0 & Byte1, 101: Byte0 & Byte2, 110: Byte1 & Byte2,000: All
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
    ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4),
                 (enumOsdWriteType == _OSD_BYTEALL) ? (0x00) : (enumOsdWriteType << 4));
#else
    ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5), (enumOsdWriteType == _OSD_BYTEALL) ? (0) : (enumOsdWriteType << 5));
#endif

    ScalerOsdSetAddrSramCommand(usSramAddress);
}

//--------------------------------------------------
// Description  : Row command & Charactor command & Font base address
// Input Value  : enumOsdMapType          -> _OSD_A or _OSD_B
//                ucRowCommandStart       -> Row command start address
//                ucCharactorCommandStart -> Charactor command start address
//                ulFontStart             -> Font start address
// Output Value :
//--------------------------------------------------
void ScalerOsdSramBaseAddressSet(EnumOsdMapType enumOsdMapType, WORD usRowCommandStart, WORD usCharactorCommandStart, DWORD ulFontStart)
{
    // Font Base Address
    if((ulFontStart % 4) != 0x00)
    {
        // Font base address must be multiple of 4
        ulFontStart += (4 - (ulFontStart % 4));
    }

#if((_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4) && (_HW_FOSD_SRAM_SIZE == 24576))
    if(GET_OSD_COMMAND_4_BYTE_ENABLE() == _ENABLE)
    {
        if(ulFontStart > 16384)
        {
            DebugMessageOsd("[Warning] 4 byte : Font base address over range.", ulFontStart);
        }
    }
    else
    {
        if(ulFontStart > 24576)
        {
            DebugMessageOsd("[Warning] 3 byte : Font base address over range.", ulFontStart);
        }
    }
#endif

#if(_HW_OSD_FONT_BASE_ADDR_BIT == _19_BIT)
    ScalerSetBit(P3A_44_FRAME_CTRL_F_FONT_BASE_H, ~(_BIT2 | _BIT1 | _BIT0), (ulFontStart & _19_BIT) >> 16);
    ScalerSetByte(P3A_45_FRAME_CTRL_F_FONT_BASE_M, HIBYTE(ulFontStart));
#else
    ScalerSetByte(P3A_45_FRAME_CTRL_F_FONT_BASE_H, HIBYTE(ulFontStart));
#endif
    ScalerSetByte(P3A_46_FRAME_CTRL_F_FONT_BASE_L, LOBYTE(ulFontStart));

#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
    if(GET_OSD_COMMAND_4_BYTE_ENABLE() == _ENABLE)
    {
        DWORD ulFontBase2 = 0;

        // font_base2 = 4 * (font_base/12 + ((font_base % 12 > 0) ? (1) : (0)))
        ulFontBase2 = 4 * (ulFontStart / 12 + ((ulFontStart % 12 > 0) ? (1) : (0)));
        ScalerSetBit(P3A_B2_FRAME_CTRL_F_FONT_BASE_H_2, ~(_BIT2 | _BIT1 | _BIT0), DWORD_TO_BYTE((ulFontBase2 & _19_BIT), 2));
        ScalerSetByte(P3A_B3_FRAME_CTRL_F_FONT_BASE_M_2, DWORD_TO_BYTE(ulFontBase2, 1));
        ScalerSetByte(P3A_B4_FRAME_CTRL_F_FONT_BASE_L_2, DWORD_TO_BYTE(ulFontBase2, 0));
    }
#endif

    if((usRowCommandStart % 4) != 0x00)
    {
        // Row Command Base address must be multiple of 4
        usRowCommandStart += (4 - (usRowCommandStart % 4));
    }
    switch(enumOsdMapType)
    {
        case _OSD_A:
            // Font Select Base Address
            SET_OSD_MAPA_CHAR_SEL_ADDR(usCharactorCommandStart);
            break;
        case _OSD_B:
            // Row Command Base B
            SET_OSD_MAPB_ROW_BASE_ADDR(usRowCommandStart);
            // Font Select Base B
            SET_OSD_MAPB_CHAR_SEL_ADDR(usCharactorCommandStart);
            break;
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
        case _OSD_C:
            // Row Command Base C
            SET_OSD_MAPC_ROW_BASE_ADDR(usRowCommandStart);
            // Font Select Base C
            SET_OSD_MAPC_CHAR_SEL_ADDR(usCharactorCommandStart);
            break;
        case _OSD_D:
            // Row Command Base D
            SET_OSD_MAPD_ROW_BASE_ADDR(usRowCommandStart);
            // Font Select Base D
            SET_OSD_MAPD_CHAR_SEL_ADDR(usCharactorCommandStart);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol.    -> Just that !!
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
// Output Value :
//--------------------------------------------------
void ScalerOsdSramDataValue(WORD usRow, WORD usCol, WORD usLength, BYTE ucValue, EnumOsdWriteType enumOsdWriteType)
{
    WORD usTemp = 0;

    ScalerOsdSramAddressCount(usRow, usCol, enumOsdWriteType);

    for(usTemp = 0; usTemp < usLength; usTemp++)
    {
        ScalerOsdSetDataPortSram(ucValue);
    }
}

//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol.    -> Just that !!
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
// Output Value :
//--------------------------------------------------
void ScalerOsdSramDataValue2Byte(WORD usRow, WORD usCol, WORD usLength, BYTE ucValue1, BYTE ucValue2, EnumOsdWriteType enumOsdWriteType)
{
    WORD usTemp = 0;

    ScalerOsdSramAddressCount(usRow, usCol, enumOsdWriteType);

    for(usTemp = 0; usTemp < usLength; usTemp++)
    {
        ScalerOsdSetDataPortSram(ucValue1);
        ScalerOsdSetDataPortSram(ucValue2);
    }
}

//--------------------------------------------------
// Description  : Get SRAM address value : Font
// Input Value  : usFontIdx
//                ucFontLen
// Output Value : pucData -> Data
//--------------------------------------------------
void ScalerOsdSramGetDataFont(WORD usFontIdx, BYTE ucFontLen, BYTE *pucData)
{
    BYTE ucLenIdx = 0;
    BYTE ucRdIdx = 0;

    for(ucLenIdx = 0; ucLenIdx < ucFontLen; ucLenIdx++)
    {
        ScalerOsdSetAddrSramFont(usFontIdx + ucLenIdx);

        for(ucRdIdx = 0; ucRdIdx < 27; ucRdIdx++)
        {
            pucData[ucLenIdx * 27 + ucRdIdx] = ScalerGetByte(P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT);
        }
    }
}

//--------------------------------------------------
// Description  : Get SRAM address value : Command
// Input Value  : enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
//                enumSramType -> Row, Char command Or Font Data
//                usSramAddress -> address
//                usLength -> Length
// Output Value : pucData -> Data
//--------------------------------------------------
void ScalerOsdSramGetDataCommand(EnumOsdWriteType enumOsdWriteType, WORD usSramAddress, WORD usLength, BYTE *pucData)
{
    WORD usLenIdx = 0;
    BYTE ucRdIdx = 0;
    BYTE ucByteSel = 0;

    switch(enumOsdWriteType)
    {
        case _OSD_BYTEALL:
            ucByteSel = 3;
            break;
        case _OSD_BYTE0_BYTE1:
        case _OSD_BYTE0_BYTE2:
        case _OSD_BYTE1_BYTE2:
            ucByteSel = 2;
            break;

        default:
            ucByteSel = 1;
            break;
    }

    for(usLenIdx = 0; usLenIdx < usLength; usLenIdx++)
    {
        ScalerOsdSramAddressSetCommand(usSramAddress + usLenIdx, enumOsdWriteType);

        for(ucRdIdx = 0; ucRdIdx < ucByteSel; ucRdIdx++)
        {
            pucData[(usLenIdx * ucByteSel) + ucRdIdx] = ScalerGetByte(P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT);
        }
    }
}

//--------------------------------------------------
// Description  : Get Font Base Addr
// Input Value  :
// Output Value :
//--------------------------------------------------
DWORD ScalerOsdGetFontBaseAddr(void)
{
    DWORD ulAddr = 0;

#if(_HW_OSD_FONT_BASE_ADDR_BIT == _19_BIT)
    ulAddr = TO_DWORD(0x00,
                      ScalerGetBit(P3A_44_FRAME_CTRL_F_FONT_BASE_H, (_BIT2 | _BIT1 | _BIT0)),
                      ScalerGetByte(P3A_45_FRAME_CTRL_F_FONT_BASE_M),
                      ScalerGetByte(P3A_46_FRAME_CTRL_F_FONT_BASE_L));
#else
    ulAddr = TO_WORD(ScalerGetByte(P3A_45_FRAME_CTRL_F_FONT_BASE_H),
                     ScalerGetByte(P3A_46_FRAME_CTRL_F_FONT_BASE_L));
#endif

    return ulAddr;
}

#if(_HW_OSD_DISP_FONT_BASE_ADDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Display Font Base Address
// Input Value  : ulDispFontAddr             -> Display Font start address
// Output Value :
//--------------------------------------------------
void ScalerOsdSramBaseAddressSetDispFontAddr(DWORD ulDispFontAddr)
{
    // Display Font Base Address
    if((ulDispFontAddr % 4) != 0x00)
    {
        // Display Font base address must be multiple of 4
        ulDispFontAddr += (4 - (ulDispFontAddr % 4));
    }

#if((_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4) && (_HW_FOSD_SRAM_SIZE == 24576))
    if(GET_OSD_COMMAND_4_BYTE_ENABLE() == _ENABLE)
    {
        if(ulDispFontAddr > 16384)
        {
            DebugMessageOsd("[Warning] 4 byte : Font base address over range.", ulDispFontAddr);
        }
    }
    else
    {
        if(ulDispFontAddr > 24576)
        {
            DebugMessageOsd("[Warning] 3 byte : Font base address over range.", ulDispFontAddr);
        }
    }
#endif

    ScalerSetBit(P3A_41_FRAME_CTRL_F_DISP_FONT_BASE_H, ~(_BIT2 | _BIT1 | _BIT0), (ulDispFontAddr & _19_BIT) >> 16);
    ScalerSetByte(P3A_42_FRAME_CTRL_F_DISP_FONT_BASE_M, HIBYTE(ulDispFontAddr));
    ScalerSetByte(P3A_43_FRAME_CTRL_F_DISP_FONT_BASE_L, LOBYTE(ulDispFontAddr));
}

//--------------------------------------------------
// Description  : Get Display Font Base Address
// Input Value  :
// Output Value :
//--------------------------------------------------
DWORD ScalerOsdSramBaseAddressGetDispFontAddr(void)
{
    DWORD ulAddr = 0;

    // Page3A41[2:0] : disp_font_base[18:16]
    // Page3A42 : disp_font_base[15:8]
    // Page3A43 : disp_font_base[7:0]
    ulAddr = TO_DWORD(0x00,
                      ScalerGetBit(P3A_41_FRAME_CTRL_F_DISP_FONT_BASE_H, (_BIT2 | _BIT1 | _BIT0)),
                      ScalerGetByte(P3A_42_FRAME_CTRL_F_DISP_FONT_BASE_M),
                      ScalerGetByte(P3A_43_FRAME_CTRL_F_DISP_FONT_BASE_L));
    return ulAddr;
}

//--------------------------------------------------
// Description  : Display Font base address enable
// Input Value  : bDispFontAddrEnable   -> _DISABLE : display address = font_base address
//                                      -> _ENABLE : display address =  disp_font_base address
// Output Value :
//--------------------------------------------------
void ScalerOsdSramBaseAddressSetDispFontAddrEnable(bit bDispFontAddrEnable)
{
    ScalerSetBit(P3A_41_FRAME_CTRL_F_DISP_FONT_BASE_H, ~(_BIT7), (bDispFontAddrEnable == _ENABLE) ? (_BIT7) : (_BIT0));
}
#endif // end of #if(_HW_OSD_DISP_FONT_BASE_ADDR_SUPPORT == _ON)

#if(_HW_FOSD_HW_PUT_STRING_GEN_TYPE == _OSD_HW_PUT_STRING_GEN_1)
//--------------------------------------------------
// Description  : Set HW put string address
// Input Value  : usAddr
// Output Value :
//--------------------------------------------------
void ScalerOsdSramSetHWPutStringAddress(WORD usAddr)
{
    ScalerSetByte(P3A_86_FRAME_CTRL_F_PUT_STRING_ADR_PORT_H, HIBYTE(usAddr));
    ScalerSetByte(P3A_87_FRAME_CTRL_F_PUT_STRING_ADR_PORT_L, LOBYTE(usAddr));
}

//--------------------------------------------------
// Description  : Set HW put string font data
// Input Value  : ucData
// Output Value :
//--------------------------------------------------
void ScalerOsdSramSetHWPutStringFontData(BYTE ucData)
{
    ScalerSetByte(P3A_82_FRAME_CTRL_F_PUT_STRING_FONT_DATA_1, ucData);
}

//--------------------------------------------------
// Description  : Set HW put string font select
// Input Value  : enumFontSel
// Output Value :
//--------------------------------------------------
void ScalerOsdSramSetHWPutStringFontSelect(EnumOsdHWPutStringFontSelType enumFontSel)
{
    ScalerSetBit(P3A_81_FRAME_CTRL_F_PUT_STRING_CTRL2, ~(_BIT1 | _BIT0), enumFontSel);
}

//--------------------------------------------------
// Description  : Set HW put string font width
// Input Value  : ucFontWidth
// Output Value :
//--------------------------------------------------
void ScalerOsdSramSetHWPutStringFontWidth(BYTE ucFontWidth)
{
    // Check font width range : 1 ~ 12
    ucFontWidth = (ucFontWidth > 12) ? (12) : (ucFontWidth);
    ScalerSetBit(P3A_80_FRAME_CTRL_F_PUT_STRING_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ucFontWidth << 4));
}
//--------------------------------------------------
// Description  : Set HW put string last font
// Input Value  : bLastFont -> last font or not
//                ucWidth -> font width
// Output Value :
//--------------------------------------------------
void ScalerOsdSramSetHWPutStringLastFont(bit bLastFont, BYTE ucWidth)
{
    BYTE ucValue = 0;
    ucValue = ((ucWidth & 0x0F) << 4) | ((bLastFont == _TRUE) ? (_BIT2) : (0x00));
    ScalerSetBit(P3A_80_FRAME_CTRL_F_PUT_STRING_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), ucValue);
}

//--------------------------------------------------
// Description  : Set HW put string apply
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerOsdSramSetHWPutStringApply(void)
{
    ScalerSetBit(P3A_80_FRAME_CTRL_F_PUT_STRING_CTRL, ~(_BIT1), _BIT1);
}

//--------------------------------------------------
// Description  : Set HW put string apply polling finish
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerOsdSramSetHWPutStringApplyPollingFinish(void)
{
    ScalerTimerPollingFlagProc(100, P3A_80_FRAME_CTRL_F_PUT_STRING_CTRL, (_BIT1), 0x00);
}

//--------------------------------------------------
// Description  : Set HW put string enable
// Input Value  : bEnable
// Output Value :
//--------------------------------------------------
void ScalerOsdSramSetHWPutStringEnable(bit bEnable)
{
    ScalerSetBit(P3A_80_FRAME_CTRL_F_PUT_STRING_CTRL, ~(_BIT0), bEnable);
}
#endif

#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
//--------------------------------------------------
// Description  : Get 4 byte command enable/disable
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerOsdSramGet4ByteCmdEnable(void)
{
    return GET_OSD_COMMAND_4_BYTE_ENABLE();
}

//--------------------------------------------------
// Description  : Set 4 byte command enable
// Input Value  : bEnable
// Output Value :
//--------------------------------------------------
void ScalerOsdSramSet4ByteCmdEnable(bit bEnable)
{
    SET_OSD_COMMAND_4_BYTE_ENABLE(bEnable);
}
#endif
