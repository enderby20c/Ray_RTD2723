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
// ID Code      : RTDFactoryMode.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
#define __FACTORY_MODE__

#include "RTD2020UserInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _OSD_FACTORY_PAGE_1_TABLE_END 13


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
bit g_bBgOnOff = _OFF;
BYTE g_ucBgColorR = 128;
BYTE g_ucBgColorG = 128;
BYTE g_ucBgColorB = 128;
BYTE g_ucSSCspeed = _LVDS_SPREAD_SPEED;
BYTE g_ucLVDSclk = _LVDS_DRIV_CONTROL;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void RTDFactoryMenuOperation(void);
void RTDFactoryMainMenu(void);
void RTDFactoryAutoColorEnter(void);
void RTDFactoryExitEnter(void);
void RTDFactoryPanelUsedTimer(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryMenuOperation(void)
{
    if(GET_KEYMESSAGE() < _KEY_AMOUNT)
    {
        if(GET_OSD_STATE() == _MENU_FACTORY_MAIN)
        {
            switch(GET_KEYMESSAGE())
            {
                case _MENU_KEY_MESSAGE:
                    switch(OsdFactoryGetItem(GET_OSD_ITEM_INDEX()))
                    {
                        case _OSD_FACTORY_AUTOCOLOR:
                            RTDFactoryAutoColorEnter();
                            break;

                        case _OSD_FACTORY_EXIT:
                            RTDFactoryExitEnter();
                            break;

                        case _OSD_FACTORY_RESET_PANEL_TIME:
                            break;

                        default:
                            OsdFactoryHilightWindow(_OSD_WIN_HIGHLIGHT_2, GET_OSD_ITEM_INDEX(), _CP_YELLOW);
                            SET_OSD_STATE(_MENU_FACTORY_MAIN_ADJ);
                            OsdFactoryItemValueUpdate(OsdFactoryGetItem(GET_OSD_ITEM_INDEX()));
                            break;
                    }

                    break;
                case _LEFT_KEY_MESSAGE:
                    // select the previous one item
                    SET_OSD_ITEM_INDEX((GET_OSD_ITEM_INDEX() + OsdFactoryGetItemMax() - 1) % OsdFactoryGetItemMax());
                    OsdFactoryHilightWindow(_OSD_WIN_HIGHLIGHT_2, GET_OSD_ITEM_INDEX(), _CP_BLACK);
                    OsdFactoryChangColorTemp();
                    break;
                case _RIGHT_KEY_MESSAGE:
                    // select the next one item
                    SET_OSD_ITEM_INDEX((GET_OSD_ITEM_INDEX() + 1) % OsdFactoryGetItemMax());
                    OsdFactoryHilightWindow(_OSD_WIN_HIGHLIGHT_2, GET_OSD_ITEM_INDEX(), _CP_BLACK);
                    OsdFactoryChangColorTemp();
                    break;
                case _EXIT_KEY_MESSAGE:
                    RTDFactoryExitEnter();
                    break;
                default:
                    break;
            }
        }
        else if(GET_OSD_STATE() == _MENU_FACTORY_MAIN_ADJ)
        {
            switch(GET_KEYMESSAGE())
            {
                case _MENU_KEY_MESSAGE:
                    OsdFactoryHilightWindow(_OSD_WIN_HIGHLIGHT_2, GET_OSD_ITEM_INDEX(), _CP_BLACK);
                    SET_OSD_STATE(_MENU_FACTORY_MAIN);
                    break;
                case _LEFT_KEY_MESSAGE:
                case _RIGHT_KEY_MESSAGE:
                    OsdFactoryFuncItemProcess(OsdFactoryGetItem(GET_OSD_ITEM_INDEX()));
                    break;
                case _EXIT_KEY_MESSAGE:
                    OsdFactoryHilightWindow(_OSD_WIN_HIGHLIGHT_2, GET_OSD_ITEM_INDEX(), _CP_BLACK);
                    SET_OSD_STATE(_MENU_FACTORY_MAIN);
                    break;
                default:
                    break;
            }
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryMainMenu(void)
{
    g_usFontPointer0 = _FACTORY_PAGE_0_WORD_START;
    g_usFontPointer1 = _FACTORY_PAGE_1_WORD_START;
    g_usFontPointer2 = _FACTORY_PAGE_2_WORD_START;
    g_usFontPointer3 = _FACTORY_PAGE_3_WORD_START;

    UserCommonOsdDisableOsd();
    OsdFuncCloseWindow(_OSD_WINDOW_ALL);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
    SET_OSD_STATE(_MENU_FACTORY_MAIN);
    SET_OSD_IN_FACTORY_MENU_STATUS(_TRUE);

    // OSD Map
    OsdFactoryFuncApplyMap(WIDTH(_FACTORY_OSD_COL), HEIGHT(_FACTORY_OSD_ROW), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    OsdFuncMapRotation(_OSD_ROTATE_DEGREE_0, _OSD_MAP_A_REMAPPING_ENABLE, HEIGHT(_FACTORY_OSD_ROW), _OSD_MAP_B_REMAPPING_DISABLE, 0, _OSD_FONT_LIB_ROTATION_ENABLE);
#endif

    // load space font
    OsdFontVLCLoadFontByGen(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);

    // Draw String & Value
    SET_OSD_ITEM_INDEX(0);
    OsdFactoryMenuSubItem();

    // draw window
    OsdFactoryHilightWindow(_OSD_WIN_HIGHLIGHT_2, GET_OSD_ITEM_INDEX(), _CP_BLACK);
    OsdFactoryFuncWindowBorder(_OSD_WINDOW_0, 0, 0, _FACTORY_OSD_WINDOW_SIZE_X, _FACTORY_OSD_WINDOW_SIZE_Y, _CP_BLACK);

    // Set OSD Position
    OsdFactoryFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, _FACTORY_OSD_V_POS_MIN);
    UserCommonOsdEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryAutoColorEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
       (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
    {
        BYTE ucTemp = 0;

        if(GET_OSD_FACTORY_AUTO_COLOR_TYPE() == _AUTO_COLOR_TYPE_INTERNAL)
        {
            ucTemp = _AUTO_CALIBRATE_RGB;
        }
        else
        {
            ucTemp = _AUTO_TUNE_RGB;
        }

        if(UserCommonVgaAutoDoWhiteBalance(ucTemp) == _AUTO_SUCCESS)
        {
            UserCommonVgaAutoGetAutoColorResult(&g_stVgaAdcData);
            OsdFactoryMenuString(ROW(OsdFactoryGetItemRow(_OSD_FACTORY_AUTOCOLOR)), COL(_FACTORY_ON_OFF_COL), (_PFONT_FACTORY_PAGE_ITEM_1 + _OSD_FACTORY_AUTOCOLOR), _OSD_TEXT_PASS_FACT, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
        }
        else
        {
            UserCommonNVRamRestoreADCSetting();
            OsdFactoryMenuString(ROW(OsdFactoryGetItemRow(_OSD_FACTORY_AUTOCOLOR)), COL(_FACTORY_ON_OFF_COL), (_PFONT_FACTORY_PAGE_ITEM_1 + _OSD_FACTORY_AUTOCOLOR), _OSD_TEXT_FAIL_FACT, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
        }

        for(ucTemp = _OSD_FACTORY_GAIN_RED; ucTemp <= _OSD_FACTORY_OFFSET_BLUE; ucTemp++)
        {
            OsdFactoryItemValueUpdate(OsdFactoryGetItem(ucTemp));
            OsdFactoryMenuItemValue(ROW(OsdFactoryGetItemRow(ucTemp)), _FACTORY_ON_OFF_COL, _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + ucTemp));
        }
    }
#endif // End of #if(_VGA_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryExitEnter(void)
{
    UserCommonOsdDisableOsd();
    OsdFuncCloseWindow(_OSD_WINDOW_ALL);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
    SET_OSD_STATE(_MENU_NONE);
    SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);

    // Reset osd sram point
    g_usFontPointer0 = _OSD_PAGE_0_START;
    g_usFontPointer1 = _OSD_PAGE_1_START;
    g_usFontPointer2 = _OSD_PAGE_2_START;
    g_usFontPointer3 = _OSD_PAGE_3_START;
}

//--------------------------------------------------
// Description : Pannel used time Timer
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryPanelUsedTimer(void)
{
    SET_PANEL_TIME_MIN(GET_PANEL_TIME_MIN() + 1);

    if((GET_PANEL_TIME_HOUR() >= 65535) && (GET_PANEL_TIME_MIN() >= 59))
    {
        SET_PANEL_TIME_HOUR(65535);
        SET_PANEL_TIME_MIN(59);
    }

    if(GET_PANEL_TIME_MIN() >= 60)
    {
        SET_PANEL_TIME_HOUR(GET_PANEL_TIME_HOUR() + 1);
        SET_PANEL_TIME_MIN(0);
    }

    if(GET_OSD_IN_FACTORY_MENU_STATUS() == _FALSE)
    {
        if((GET_PANEL_TIME_MIN() % 20) == 0)
        {
            RTDNVRamSaveOsdUserData();
        }
    }
    else
    {
        OsdFactoryShowNumber(ROW(OsdFactoryGetItemRow(_OSD_FACTORY_RESET_PANEL_TIME)), COL(_FACTORY_PANEL_TIME_HOUR_NUMBER_COL), GET_PANEL_TIME_HOUR(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), (_PFONT_FACTORY_PAGE_1), COLOR(_CP_WHITE, _CP_BG));
        OsdFactoryShowNumber(ROW(OsdFactoryGetItemRow(_OSD_FACTORY_RESET_PANEL_TIME)), COL(_FACTORY_PANEL_TIME_MIN_NUMBER_COL), GET_PANEL_TIME_MIN(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), (_PFONT_FACTORY_PAGE_1), COLOR(_CP_WHITE, _CP_BG));
        RTDNVRamSaveOsdUserData();
    }

    UserCommonTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_PANEL_USED_TIMER);
}



