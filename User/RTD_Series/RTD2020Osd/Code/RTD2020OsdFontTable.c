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
// ID Code      : RTD2020OsdFontTable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDFONTTABLE__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tOSD_iREALTEK[] =
{
    _iREALTEK_00, _iREALTEK_01, _iREALTEK_02, _iREALTEK_03, _iREALTEK_04, _iREALTEK_05, _iREALTEK_06, _iREALTEK_07, _iREALTEK_08, _iREALTEK_09, _iREALTEK_0A, _iREALTEK_0B, _NEXT_,
    _iREALTEK_10, _iREALTEK_11, _iREALTEK_12, _iREALTEK_13, _iREALTEK_14, _iREALTEK_15, _iREALTEK_16, _iREALTEK_17, _iREALTEK_18, _iREALTEK_19, _iREALTEK_1A, _iREALTEK_1B, _END_,
};

BYTE code tOSD_iKEY_BACK[] =
{
    _iKEY_BACK_00, _iKEY_BACK_01, _NEXT_,
    _iKEY_BACK_10, _iKEY_BACK_11, _END_,
};

BYTE code tOSD_iKEY_LEFT[] =
{
    _iKEY_LEFT_00, _iKEY_LEFT_01, _NEXT_,
    _iKEY_LEFT_10, _iKEY_LEFT_11, _END_,
};

BYTE code tOSD_iKEY_RIGHT[] =
{
    _iKEY_RIGHT_00, _iKEY_RIGHT_01, _NEXT_,
    _iKEY_RIGHT_10, _iKEY_RIGHT_11, _END_,
};

BYTE code tOSD_iKEY_ENTER[] =
{
    _iKEY_ENTER_00, _iKEY_ENTER_01, _NEXT_,
    _iKEY_ENTER_10, _iKEY_ENTER_11, _END_,
};

BYTE code tOSD_iKEY_EXIT[] =
{
    _iKEY_EXIT_00, _iKEY_EXIT_01, _NEXT_,
    _iKEY_EXIT_10, _iKEY_EXIT_11, _END_,
};

BYTE code tOSD_Crosshair[] =
{
    0x00, 0x01, 0x00, 0x03, 0x00, 0x04, 0x00, 0x02, 0x00, _END_,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
bit g_bOsdCrosshairShow = _FALSE;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdFontPut1Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor);
void OsdFontPut1BitTable(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor);
void OsdFontPut1BitMainMenuIcon(WORD usRow, WORD usCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
#if(_DM_FUNCTION == _ON)
void OsdFontPut1BitMapAB(WORD usRow, WORD usCol, BYTE ucByte0, BYTE ucIcon, BYTE ucColor);
void OsdFontPut1BitTableMapAB(WORD usRow, WORD usCol, BYTE ucByte0, BYTE *pucArray, BYTE ucColor);
#endif

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
void OsdFontPut1BitMainMenuIconOsdB(WORD usRow, WORD usCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
#endif
void OsdFontPut4Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucCPIdx);

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFontPut1Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor)
{
    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;
    BYTE ucByte0 = _OSD_1_BIT_BYTE0;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        usOsdAddr = (WORD)((g_ucOsdWidth - ucRow - 1) + g_ucOsdWidth * ucCol);
        ucByte0 = _OSD_1_BIT_BYTE0_ROTATE;
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol) * g_ucOsdWidth + ucRow;
        ucByte0 = _OSD_1_BIT_BYTE0_ROTATE;
    }
#endif

    UserCommonOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFontPut1BitTable(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor)
{
    BYTE ucOsdWidth = 0;
    BYTE ucCount = 0;
    BYTE ucHTemp = ucCol;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucOsdWidth = g_ucOsdHeight;
    }
    else
#endif
    {
        ucOsdWidth = g_ucOsdWidth;
    }

    while(*pucArray != _END_)
    {
        if(*pucArray == _NEXT_)
        {
            ucRow++;
            ucHTemp = ucCol;
            pucArray++;
        }
        else if(*pucArray == _SPACE_)
        {
            ucHTemp++;
            pucArray++;
        }
        else if(*pucArray == _REPEAT_)
        {
            ucCount = *(pucArray + 1) - 1;

            while(ucCount > 0)
            {
                if(*(pucArray - 1) != _SPACE_)
                {
                    OsdFontPut1Bit(ucRow, ucHTemp, *(pucArray - 1), ucColor);
                }

                ucHTemp++;

                if((ucHTemp == ucOsdWidth) && (*(pucArray + 1) != _NEXT_))
                {
                    ucRow++;
                    ucHTemp = ucCol;
                }
                ucCount--;
            }
            pucArray += 2;
        }
        else
        {
            OsdFontPut1Bit(ucRow, ucHTemp, *pucArray, ucColor);
            ucHTemp++;

            if((ucHTemp == ucOsdWidth) && (*(pucArray + 1) != _NEXT_))
            {
                ucRow++;
                ucHTemp = ucCol;
            }
            pucArray++;
        }
    }
}
#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFontPut1BitMapAB(WORD usRow, WORD usCol, BYTE ucByte0, BYTE ucIcon, BYTE ucColor)
{
    UserCommonOsdSramDataValue(usRow, usCol, 1, ucByte0, _OSD_BYTE0);
    UserCommonOsdSramDataValue(usRow, usCol, 1, ucIcon, _OSD_BYTE1);
    UserCommonOsdSramDataValue(usRow, usCol, 1, ucColor, _OSD_BYTE2);
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFontPut1BitTableMapAB(WORD usRow, WORD usCol, BYTE ucByte0, BYTE *pucArray, BYTE ucColor)
{
    BYTE ucOsdWidth = 0;
    BYTE ucCount = 0;
    WORD usHTemp = usCol;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucOsdWidth = g_ucOsdHeight;
    }
    else
#endif
    {
        ucOsdWidth = g_ucOsdWidth;
    }

    while(*pucArray != _END_)
    {
        if(*pucArray == _NEXT_)
        {
            usRow++;
            usHTemp = usCol;
            pucArray++;
        }
        else if(*pucArray == _SPACE_)
        {
            usHTemp++;
            pucArray++;
        }
        else if(*pucArray == _REPEAT_)
        {
            ucCount = *(pucArray + 1) - 1;

            while(ucCount > 0)
            {
                if(*(pucArray - 1) != _SPACE_)
                {
                    OsdFontPut1BitMapAB(usRow, usHTemp, ucByte0, *(pucArray - 1), ucColor);
                }

                usHTemp++;

                if((usHTemp == (WORD)ucOsdWidth) && (*(pucArray + 1) != _NEXT_))
                {
                    usRow++;
                    usHTemp = usCol;
                }
                ucCount--;
            }
            pucArray += 2;
        }
        else
        {
            OsdFontPut1BitMapAB(usRow, usHTemp, ucByte0, *pucArray, ucColor);
            usHTemp++;

            if((usHTemp == (WORD)ucOsdWidth) && (*(pucArray + 1) != _NEXT_))
            {
                usRow++;
                usHTemp = usCol;
            }
            pucArray++;
        }
    }
}

#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFontPut1BitMainMenuIcon(WORD usRow, WORD usCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground)
{
    WORD usOsdAddr = (WORD)usRow * g_ucOsdWidth + usCol;
    BYTE ucByte0 = _OSD_1_BIT_BYTE0;
    BYTE ucByte2 = 0;
    BYTE ucLength = 6;
    BYTE ucHeight = 4;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        usOsdAddr = (WORD)((g_ucOsdWidth - usRow - 1) + g_ucOsdWidth * usCol);
        ucByte0 = _OSD_1_BIT_BYTE0_ROTATE;
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        usOsdAddr = (WORD)(g_ucOsdHeight - 1 - usCol) * g_ucOsdWidth + usRow;
        ucByte0 = _OSD_1_BIT_BYTE0_ROTATE;
    }
#endif

    ucForeground &= 0x0F;

    ucByte2 = ((ucForeground << 4) | ucBackground);

//20170207 Abel Modify
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        for(ucHeight = 0; ucHeight < 4; ucHeight++)
        {
            for(ucLength = 0; ucLength < 6; ucLength++)
            {
                usOsdAddr = (WORD)(g_ucOsdWidth - usRow - ucHeight - 1) + g_ucOsdWidth * (usCol + ucLength);
                UserCommonOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);
                ucIcon++;
            }
        }
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        for(ucHeight = 0; ucHeight < 4; ucHeight++)
        {
            for(ucLength = 0; ucLength < 6; ucLength++)
            {
                usOsdAddr = (WORD)(g_ucOsdHeight - 1 - (usCol + ucLength)) * g_ucOsdWidth + (usRow + ucHeight);
                UserCommonOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, ucByte0, ucIcon, ucByte2);
                ucIcon++;
            }
        }
    }
    else
#endif
    {
        for(ucHeight = 0; ucHeight < 4; ucHeight++)
        {
            for(ucLength = 0; ucLength < 6; ucLength++)
            {
                UserCommonOsdCommandAllByte(usOsdAddr + g_usFontSelectStart + ucLength, ucByte0, ucIcon, ucByte2);
                ucIcon++;
            }
            usOsdAddr += g_ucOsdWidth;
        }
    }
}

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFontPut1BitMainMenuIconOsdB(WORD usRow, WORD usCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground)
{
    WORD usOsdAddr = (WORD)usRow * g_ucOsdWidthB + usCol;
    BYTE ucByte0 = _OSD_1_BIT_BYTE0;
    BYTE ucByte2 = 0;
    BYTE ucLength = 6;
    BYTE ucHeight = 4;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        usOsdAddr = (WORD)((g_ucOsdWidthB - usRow - 1) + g_ucOsdWidthB * usCol);
        ucByte0 = _OSD_1_BIT_BYTE0_ROTATE;
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        usOsdAddr = (WORD)(g_ucOsdHeight - 1 - usCol) * g_ucOsdWidthB + usRow;
        ucByte0 = _OSD_1_BIT_BYTE0_ROTATE;
    }
#endif

    ucForeground &= 0x0F;

    ucByte2 = ((ucForeground << 4) | ucBackground);

//20170207 Abel Modify
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        for(ucHeight = 0; ucHeight < 4; ucHeight++)
        {
            for(ucLength = 0; ucLength < 6; ucLength++)
            {
                usOsdAddr = (WORD)(g_ucOsdWidthB - usRow - ucHeight - 1) + g_ucOsdWidthB * (usCol + ucLength);
                UserCommonOsdCommandAllByte(usOsdAddr + ((g_usFontSelectStart + (WORD)(g_ucOsdWidth) * g_ucOsdHeight)), ucByte0, ucIcon, ucByte2);
                ucIcon++;
            }
        }
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        for(ucHeight = 0; ucHeight < 4; ucHeight++)
        {
            for(ucLength = 0; ucLength < 6; ucLength++)
            {
                usOsdAddr = (WORD)(g_ucOsdHeightB - 1 - (usCol + ucLength)) * g_ucOsdWidthB + (usRow + ucHeight);
                UserCommonOsdCommandAllByte(usOsdAddr + ((g_usFontSelectStart + (WORD)(g_ucOsdWidth) * g_ucOsdHeight)), ucByte0, ucIcon, ucByte2);
                ucIcon++;
            }
        }
    }
    else
#endif
    {
        for(ucHeight = 0; ucHeight < 4; ucHeight++)
        {
            for(ucLength = 0; ucLength < 6; ucLength++)
            {
                UserCommonOsdCommandAllByte(usOsdAddr + ((g_usFontSelectStart + (WORD)(g_ucOsdWidth) * g_ucOsdHeight)) + ucLength, ucByte0, ucIcon, ucByte2);
                ucIcon++;
            }
            usOsdAddr += g_ucOsdWidthB;
        }
    }
}
#endif // End of #if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))


//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFontPut4Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucCPIdx)
{
    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol;

    UserCommonOsdCommandAllByte(usOsdAddr + g_usFontSelectStart, _OSD_4_BIT_BYTE0, ucIcon, ucCPIdx);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdFontCrosshair(void)
{
    UserCommonOsdDisableOsd();
    UserCommonOsdWindowDisable(_OSD_WINDOW_ALL);
    OsdFuncApplyMap(WIDTH(_OSD_CROSSHAIR_WIDTH), HEIGHT(_OSD_CROSSHAIR_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    OsdFuncMapRotation(GET_OSD_ROTATE_STATUS(), _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_OSD_CROSSHAIR_HEIGHT), _OSD_MAP_B_REMAPPING_DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(0xFF);

    // Adjust Color Palette
    UserCommonOsdSetColorPalette(0, 0xFF, 0x00, 0x00); // up
    UserCommonOsdSetColorPalette(1, 0xFF, 0xFF, 0x00); // left
    UserCommonOsdSetColorPalette(2, 0xFF, 0x00, 0xFF); // right
    UserCommonOsdSetColorPalette(3, 0x00, 0xFF, 0xFF); // down

    OsdFontVLCLoadFont(_FONT1_CROSSHAIR);

    // Realtek Mark
    OsdFontPut1Bit(ROW(0), COL(0), 0x01, COLOR(0, _CP_BG));
    OsdFontPut1Bit(ROW(0), COL(1), 0x02, COLOR(0, _CP_BG));
    OsdFontPut1Bit(ROW(0), COL(2), 0x03, COLOR(0, _CP_BG));
    OsdFontPut1Bit(ROW(1), COL(0), 0x04, COLOR(1, _CP_BG));
    OsdFontPut1Bit(ROW(1), COL(1), 0x05, COLOR(1, _CP_BG));
    OsdFontPut1Bit(ROW(1), COL(2), 0x06, COLOR(2, _CP_BG));
    OsdFontPut1Bit(ROW(2), COL(0), 0x07, COLOR(3, _CP_BG));
    OsdFontPut1Bit(ROW(2), COL(1), 0x08, COLOR(3, _CP_BG));
    OsdFontPut1Bit(ROW(2), COL(2), 0x09, COLOR(3, _CP_BG));

    if(GET_OSD_CROSSHAIR() == _CROSSHAIR_ON)
    {
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
    }
    else
    {
        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
    }

    // Osd Enable
    OsdFuncEnableOsd();
    SET_OSD_CROSSHAIR_SHOW();
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
/*
void OsdFontPut2Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3)

*/
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
/*
void OsdFontPut2BitTable(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3)

*/
//void OsdFontPut4Bit()
//{
//}

//void OsdFontPut4BitTable()
//{
//}

#endif// #if(_OSD_TYPE == _REALTEK_2020_OSD)

