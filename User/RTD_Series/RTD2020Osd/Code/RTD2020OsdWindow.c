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
// ID Code      : RTD2020OsdWindow.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDWINDOW__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _BORDER_PIXEL_WIDTH                 1

#define _SLIDER_LENGHT_V                    _SLIDER_HIGH_V
#define _SLIDER_WIDTH_V                     20
#define _SLIDER_HIGH_V                      (7 * 18)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdWindowDrawing(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
void OsdWindowDrawingByFont(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
void OsdWindowDrawingByFontHighlight(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor);
void OsdWindowSlider(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState);
void OsdWindowSliderDisable(void);
void OsdWindowSliderV(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState);
void OsdWindowGridLine(BYTE ucLineIdx);

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowDrawing(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor)
{
    /*
    if((GET_OSD_GRID_WINDOW_NUMBER() == ucWindow) &&  (GET_OSD_GRID_LINE_FUNCTION_ENABLE() == _ON))
    {
        WORD xdata usTemp = 0;
        WORD xdata usTemp1 = 0;
        WORD xdata usTemp2 = 0;

        if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
        {
            usTemp  = usYEnd - usYStart;    // calculate X
            usTemp1 = usXEnd - usXStart;    // calculate Y
            usTemp2 = usYStart;

            usXEnd = (g_ucOsdHeight * 18 - usYStart);
            usXStart = usXEnd - usTemp1;
            usYStart = usTemp2;
            usYEnd = usYStart + usTemp;
        }
        else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
        {
            usTemp  = usYEnd - usYStart;    // calculate X
            usTemp1 = usXEnd - usXStart;    // calculate Y
            usTemp2 = usYStart;

            usXStart = usYStart;
            usYStart = (g_ucOsdWidth * 12) - usXEnd;
            usXEnd = usXStart + usTemp1;
            usYEnd = usYStart + usTemp;
        }
        else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
        {
            usTemp  = usXEnd - usXStart;    // calculate X
            usTemp1 = usYEnd - usYStart;    // calculate Y
            usTemp2 = usXStart;

            usXStart = (g_ucOsdWidth * 12) - usTemp - usXStart;
            usXEnd = usXStart + usTemp;
            usYStart = (g_ucOsdHeight * 18) - usTemp1 - usYStart - 2;
            usYEnd = usYStart + usTemp1 + 2;
        }
        else
        {
        }
    }
    else
    */
    {
        if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
        {
            SET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE(_DISABLE);
        }
        else
        {
            SET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE(_ENABLE);
        }
    }

    SET_OSD_WINDOW_NUMBER(ucWindow);
    SET_OSD_WINDOW_COLOR(ucColor);

    SET_OSD_WINDOW_BLEND_ENABLE(_ENABLE);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    UserCommonOsdDrawWindow(usXStart, usYStart, usXEnd, usYEnd);
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowDrawingByFont(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    WORD usHstart = 0;
    WORD usHend = 0;
    WORD usVstart = 0;
    WORD usVend = 0;

    usHstart = ((WORD)ucCol * 12);
    usHend = usHstart + ((WORD)ucWidth * 12);

    if(ucRow > 0)
    {
        usVstart = (ucRow * 18);
    }
    usVend = usVstart + (18 * ucHeight);

    OsdWindowDrawing(ucWindow, usHstart, usVstart, usHend, usVend, ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowDrawingByFontHighlight(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor)
{
    WORD usHstart = 0;
    WORD usHend = 0;
    WORD usVstart = 0;
    WORD usVend = 0;

    usHstart = ((WORD)ucCol * 12);
    usHend = usHstart + ((WORD)ucWidth * 12);

    if(ucRow > 0)
    {
        usVstart = (ucRow * 18);
    }
    usVend = usVstart + (18 * ucHeight);

    OsdWindowDrawing(ucWindow, usHstart, usVstart, usHend, usVend, ucColor);

    UserCommonOsdWindowHighlightFunction(_ENABLE, ucWindow, ucForegroundColor, ucBackgroundColor, _CP_BG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowSlider(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState)
{
    OsdWindowSliderV(ucRow, ucCol, ucPercentValue, ucSliderNumber, bSelectState);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowSliderDisable(void)
{
    UserCommonOsdWindowDisable(_SLIDER_0_BAR_WINDOW);
    UserCommonOsdWindowDisable(_SLIDER_0_BORDER_WINDOW);
    UserCommonOsdWindowDisable(_SLIDER_0_BG_WINDOW);
    UserCommonOsdWindowDisable(_SLIDER_1_BAR_WINDOW);
    UserCommonOsdWindowDisable(_SLIDER_1_BORDER_WINDOW);
    UserCommonOsdWindowDisable(_SLIDER_1_BG_WINDOW);
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowSliderV(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState)
{
    WORD usHstart = 0;
    WORD usHend = 0;
    WORD usVstart = 0;
    WORD usVend = 0;
    WORD usSliderPixel = 0;
    BYTE ucSliderBarWindow = 0;
    // BYTE ucSliderBoderWindow = 0;
    BYTE ucSliderBackgroundWindow = 0;
    BYTE ucSliderColor = 0;
    BYTE ucSliderBackgroundColor = 0;
    // BYTE ucSliderBoderColor = 0;

    usSliderPixel = (WORD)_SLIDER_LENGHT_V * ucPercentValue / 100;

    usHstart = ((WORD)ucCol * 12) + _SLIDER_OFFSET;
    usHend = usHstart + _SLIDER_WIDTH_V;

    usVstart = (ucRow * 18);
    usVend = usVstart + _SLIDER_HIGH_V;

    if(ucSliderNumber == _SLIDER_0)
    {
        ucSliderBarWindow = _SLIDER_0_BAR_WINDOW;
        // ucSliderBoderWindow = _SLIDER_0_BORDER_WINDOW;
        ucSliderBackgroundWindow = _SLIDER_0_BG_WINDOW;
    }
    else
    {
        ucSliderBarWindow = _SLIDER_1_BAR_WINDOW;
        // ucSliderBoderWindow = _SLIDER_1_BORDER_WINDOW;
        ucSliderBackgroundWindow = _SLIDER_1_BG_WINDOW;
    }

    if(bSelectState == _SELECT)
    {
        ucSliderColor = _SLIDER_SELECT_COLOR;
        ucSliderBackgroundColor = _SLIDER_SELECT_BG_COLOR;
        // ucSliderBoderColor = _SLIDER_UNSELECT_BORDER_COLOR;// _SLIDER_SELECT_BORDER_COLOR;
    }
    else
    {
        ucSliderColor = _SLIDER_UNSELECT_COLOR;
        ucSliderBackgroundColor = _SLIDER_UNSELECT_BG_COLOR;
        // ucSliderBoderColor = _SLIDER_UNSELECT_BORDER_COLOR;
    }

    // SET_OSD_WINDOW_BUTTON_ENABLE(_ENABLE);
    // Slider Boder Window
    // Slider BG Color
    // OsdWindowDrawing(ucSliderBoderWindow, usHstart - _SLIDER_BORDER_PIXEL, usVstart - _SLIDER_BORDER_PIXEL, usHend + _SLIDER_BORDER_PIXEL, usVend + _SLIDER_BORDER_PIXEL, ucSliderBoderColor);

    // Slider BG Window
    SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(1);
    SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(1);

    SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_BORDER);
    SET_OSD_WINDOW_COLOR_BORDER(ucSliderColor);
    OsdWindowDrawing(ucSliderBackgroundWindow, usHstart, usVstart, usHend, usVend, ucSliderBackgroundColor);

    if(usSliderPixel == 0)// Slider Window
    {
        UserCommonOsdWindowDisable(ucSliderBarWindow);
    }
    else
    {
        OsdWindowDrawing(ucSliderBarWindow, usHstart, usVend - usSliderPixel, usHend, usVend, ucSliderColor);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowGridLine(BYTE ucLineIdx)
{
    if(ucLineIdx == _OFF)
    {
        UserCommonOsdWindowDisable(_OSD_WIN_GRID_1);
        UserCommonOsdWindowDisable(_OSD_WIN_GRID_2);
        UserCommonOsdWindowDisable(_OSD_WIN_GRID_3);
        UserCommonOsdWindowDisable(_OSD_WIN_GRID_4);
        UserCommonOsdWindowDisable(_OSD_WIN_GRID_5);
        UserCommonOsdWindowDisable(_OSD_WIN_GRID_6);
        UserCommonOsdWindowDisable(_OSD_WIN_GRID_7);
    }
    else if(ucLineIdx == 1)
    {
        OsdWindowDrawing(_OSD_WIN_GRID_1, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 1 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH + _MENU_3RD_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 1 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_2, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 2 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH + _MENU_3RD_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 2 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_3, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 3 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH + _MENU_3RD_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 3 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_4, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 4 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH + _MENU_3RD_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 4 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_5, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 5 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH + _MENU_3RD_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 5 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_6, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 6 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH + _MENU_3RD_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 6 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_7, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 7 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH + _MENU_3RD_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 7 * 2) * 18 - 8), _CP_GRAY);
    }
    else
    {
        OsdWindowDrawing(_OSD_WIN_GRID_1, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 1 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 1 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_2, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 2 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 2 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_3, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 3 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 3 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_4, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 4 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 4 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_5, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 5 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 5 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_6, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 6 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 6 * 2) * 18 - 8), _CP_GRAY);
        OsdWindowDrawing(_OSD_WIN_GRID_7, (_MENU_2ND_ITEM_COL_ST * 12 - 6), ((_MENU_2ND_ITEM_ROW_ST + 7 * 2) * 18 - 9), ((_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH) * 12), ((_MENU_2ND_ITEM_ROW_ST + 7 * 2) * 18 - 8), _CP_GRAY);
    }
}
#endif// #if(_OSD_TYPE == _REALTEK_2020_OSD)

