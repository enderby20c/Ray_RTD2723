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
// ID Code      : RTDFactoryFunction.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
#define __FACTORY_FUNCTION__

#include "RTD2020UserInclude.h"
#include "RTD2020OsdTextTableBodyFactory.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _FACTORY_WIN0_BORDER_PIXEL          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _FACTORY_WIN0_BORDER_COLOR          ((_CP_WHITE << 4) | _CP_WHITE)
#define _FACTORY_WIN0_FUNC_CONTROL          (_BLEND_ENABLE | _GRADIENT_DISABLE | _GRADIENT_DIRECTION_H | _BORDER_ENABLE | _3D_BUTTON_1)
#define _FACTORY_WIN0_GRADIENT_CONTROL0     (_R_GRADIENT_DISABLE | _G_GRADIENT_DISABLE | _B_GRADIENT_ENABLE | _GRADIENT_LEVEL_3 | _R_GRADIENT_INC | _G_GRADIENT_INC | _B_GRADIENT_INC)
#define _FACTORY_WIN0_GRADIENT_CONTROL1     _3_LEVEL_RER_GRADIENT

#define GET_OSD_INFO_MAP_FONT_BASE_ADDRESS()\
                                            g_usFontTableStart

#define GET_OSD_INFO_FONT_POINTER_0()       g_usFontPointer0
#define GET_OSD_INFO_FONT_POINTER_1()       g_usFontPointer1
#define GET_OSD_INFO_FONT_POINTER_2()       g_usFontPointer2
#define GET_OSD_INFO_FONT_POINTER_3()       g_usFontPointer3

#define SET_OSD_INFO_FONT_POINTER_0(x)      {g_usFontPointer0 = (x);}
#define SET_OSD_INFO_FONT_POINTER_1(x)      {g_usFontPointer1 = (x);}
#define SET_OSD_INFO_FONT_POINTER_2(x)      {g_usFontPointer2 = (x);}
#define SET_OSD_INFO_FONT_POINTER_3(x)      {g_usFontPointer3 = (x);}

#define _OSD_FACTORY_PAGE1_ITEM_AMOUNT      (sizeof(tOSD_FACTORY_PAGE1_ITEM_PRI))

#define _HIGHT_18_LINE                      0x11
#define _CLEAR_DATA_FACT                    _OSD_1_BIT_BYTE0, 0x00, COLOR(_CP_WHITE, _CP_BG)


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tFONT_FACTORY_GLOBAL[] =
{
    0x0f, 0x12, 0x34, 0x56, 0x78, 0x9a,
    0xbc, 0xde, 0x00, 0x08, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xc0, 0xff,
};

BYTE code tOSD_FACTORY_PAGE1_ITEM_PRI[] =
{
#if(_DP_SUPPORT == _ON)
    _OSD_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH,
    _OSD_FACTORY_DP_AUX_SETTING,
    _OSD_FACTORY_DP_IRQ_TIME,
    _OSD_FACTORY_DP_AUX_MODE,
#endif
#if((_HDMI_SUPPORT == _ON) && ((_HDMI_FREESYNC_SUPPORT == _OFF) && (_TMDS_HDCP_2_2_SUPPORT == _OFF)))
    _OSD_FACTORY_HOT_PLUG_HDMI_SUPPORT,
    _OSD_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME,
#endif
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
    _OSD_FACTORY_COLORIMETRY_SEAMLESS,
#endif
    _OSD_FACTORY_OSD_DOUBLE_SIZE,

#if(_VGA_SUPPORT == _ON)
    _OSD_FACTORY_AUTOCOLOR,
    _OSD_FACTORY_AUTOCOLOR_TYPE,
    _OSD_FACTORY_GAIN_RED, _OSD_FACTORY_GAIN_GREEN, _OSD_FACTORY_GAIN_BLUE,
    _OSD_FACTORY_OFFSET_RED, _OSD_FACTORY_OFFSET_GREEN, _OSD_FACTORY_OFFSET_BLUE,
#endif
    _OSD_FACTORY_BURNIN,
    _OSD_FACTORY_RESET_PANEL_TIME,
    _OSD_FACTORY_CT1_RED, _OSD_FACTORY_CT1_GREEN, _OSD_FACTORY_CT1_BLUE,
    _OSD_FACTORY_CT2_RED, _OSD_FACTORY_CT2_GREEN, _OSD_FACTORY_CT2_BLUE,
    _OSD_FACTORY_CT3_RED, _OSD_FACTORY_CT3_GREEN, _OSD_FACTORY_CT3_BLUE,
    _OSD_FACTORY_CT4_RED, _OSD_FACTORY_CT4_GREEN, _OSD_FACTORY_CT4_BLUE,
    _OSD_FACTORY_CT5_RED, _OSD_FACTORY_CT5_GREEN, _OSD_FACTORY_CT5_BLUE,
    _OSD_FACTORY_CT6_RED, _OSD_FACTORY_CT6_GREEN, _OSD_FACTORY_CT6_BLUE,
    _OSD_FACTORY_BG,
    _OSD_FACTORY_BG_RED,
    _OSD_FACTORY_BG_GREEN,
    _OSD_FACTORY_BG_BLUE,
    _OSD_FACTORY_SSC,
    _OSD_FACTORY_SSC_SPEED,
#if(_PANEL_STYLE == _PANEL_LVDS)
    _OSD_FACTORY_LVDS_DRIVING,
#endif

    _OSD_FACTORY_EXIT,
};

BYTE code tClearTableDataFact[] =
{
    _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT,
    _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT,
    _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT,
    _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT,
    _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT,
    _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT, _CLEAR_DATA_FACT,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructOsdItemDataType g_stFactoryOsdItemData;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdFactoryFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
void OsdFactoryFuncClearOsdFont(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);
WORD OsdFactoryFuncSetOsdFontPointer(BYTE ucPointerSelect, WORD usPointer);
void OsdFactoryFuncWindowBorder(BYTE ucWin, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
void OsdFactoryFuncEnableOsd(void);
WORD OsdFactoryDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
void OsdFactoryFuncItemProcess(EnumOsdFactoryItem enumOsdFactoryItem);
void OsdFactoryFuncSetPosition(BYTE ucType, WORD usX, WORD usY);
void OsdFactoryChangColorTemp(void);
void OsdFactoryItemValueUpdate(EnumOsdFactoryItem enumOsdFactoryItem);
void OsdFactoryHilightWindow(BYTE ucWin, WORD usIndex, BYTE ucColor);
void OsdFactoryShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucCPColor);
void OsdFactoryMenuString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, WORD usString, BYTE ucColor, BYTE ucLanguage);
void OsdFactoryPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE *pucArray, BYTE ucColor, BYTE ucLanguage);
void OsdFactoryMenuItemValue(BYTE ucRow, BYTE ucCol, BYTE ucColor, BYTE ucPFONTFACTORY);
void OsdFactoryMenuItemValueAdj(BYTE ucRow, BYTE ucCol, BYTE ucColor, BYTE ucPFONTFACTORY);
EnumOsdFactoryItem OsdFactoryGetItem(WORD usIdx);
WORD OsdFactoryGetItemMax(void);
WORD OsdFactoryGetItemRow(EnumOsdFactoryItem enumOsdFactoryItem);
WORD OsdFactoryGetItemCol(EnumOsdFactoryItem enumOsdFactoryItem);
void OsdFactoryMenuSubItem(void);
void OsdFactoryDpDebugMessage(void);
void OsdFactoryFRCMessage(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFactoryFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    BYTE ucI = 0;

    for(ucI = 0; ucI < ucHeight; ucI++)
    {
        UserCommonOsdCommandAllByte(ucI, 0x80, _HIGHT_18_LINE, ucWidth);
    }

    // Row Command end
    UserCommonOsdCommandByte(ucHeight, _OSD_BYTE0, 0x00);

    // Frame Control (set font start address)
    g_usFontSelectStart = ucHeight + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(ucWidth * ucHeight);

    // Font base address must be multiple of 4
    g_usFontTableStart += (((g_usFontTableStart % 4) == 0) ? (0) : (4 - g_usFontTableStart % 4));

    UserCommonOsdSramBaseAddressSet(_OSD_A, 0, g_usFontSelectStart, g_usFontTableStart);

    // 1bit, width 12pixels
    UserCommonOsdCharCommandByteSeries(g_usFontSelectStart, _OSD_BYTE0, _OSD_MODE_BYTE0, (WORD)ucWidth * ucHeight);

    // char initial
    UserCommonOsdCharCommandByteSeries(g_usFontSelectStart, _OSD_BYTE1, 0, (WORD)ucWidth * ucHeight);

    // color initial
    UserCommonOsdCharCommandByteSeries(g_usFontSelectStart, _OSD_BYTE2, ucColor, (WORD)ucWidth * ucHeight);

    g_ucOsdWidth = ucWidth;
    g_ucOsdHeight = ucHeight;
    SET_OSD_MAPA_COL_MAX(WIDTH(g_ucOsdWidth));
}

//--------------------------------------------------
// Description  : Clear OSD SRAM data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFactoryFuncClearOsdFont(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight)
{
    BYTE ucHeightCount = 0;

    for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
    {
        UserCommonOsdSramAddressCount(ucRow + ucHeightCount, ucCol, _OSD_BYTEALL);
        UserCommonOsdBurstWriteDataPortSram(tClearTableDataFact, (ucWidth * 3), GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_FLASH);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD OsdFactoryFuncSetOsdFontPointer(BYTE ucPointerSelect, WORD usPointer)
{
    usPointer++;

    if(ucPointerSelect == _PFONT_FACTORY_PAGE_0)
    {
        if(usPointer > _FACTORY_PAGE_0_WORD_END)
        {
            usPointer = _FACTORY_PAGE_0_WORD_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_1)
    {
        if(usPointer > _FACTORY_PAGE_1_WORD_END)
        {
            usPointer = _FACTORY_PAGE_1_WORD_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_2)
    {
        if(usPointer > _FACTORY_PAGE_2_WORD_END)
        {
            usPointer = _FACTORY_PAGE_2_WORD_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_3)
    {
        if(usPointer > _FACTORY_PAGE_3_WORD_END)
        {
            usPointer = _FACTORY_PAGE_3_WORD_START;
        }
    }
    else // freserve for Sub Itme adjust value
    {
        if(usPointer > (_FACTORY_ITEM_WORD_1_END + ((ucPointerSelect - _PFONT_FACTORY_PAGE_ITEM_1) * _FACTORY_ITEM_WORD_GAP)))
        {
            usPointer = _FACTORY_ITEM_WORD_1_START + ((ucPointerSelect - _PFONT_FACTORY_PAGE_ITEM_1) * _FACTORY_ITEM_WORD_GAP);
        }
    }
    return usPointer;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFactoryFuncWindowBorder(BYTE ucWin, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor)
{
    SET_OSD_WINDOW_NUMBER(ucWin);
    SET_OSD_WINDOW_COLOR_BORDER(_CP_WHITE);
    SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_BORDER);

    SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(2);
    SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(2);

    SET_OSD_WINDOW_COLOR(ucColor);
    SET_OSD_WINDOW_ENABLE(_ENABLE);

    UserCommonOsdDrawWindow(usXStart, usYStart, usXEnd, usYEnd);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdFactoryFuncEnableOsd(void)
{
    UserCommonOsdEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD OsdFactoryDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            if(usValue >= usMax)
            {
                if(bCycle == _ON)
                {
                    return usMin;
                }
                else
                {
                    return usMax;
                }
            }
            else
            {
                usValue++;
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(usValue <= usMin)
            {
                if(bCycle == _ON)
                {
                    return usMax;
                }
                else
                {
                    return usMin;
                }
            }
            else
            {
                usValue--;
            }
            break;

        default:
            break;
    }

    return usValue;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFactoryFuncItemProcess(EnumOsdFactoryItem enumOsdFactoryItem)
{
    switch(enumOsdFactoryItem)
    {
        case _OSD_FACTORY_AUTOCOLOR_TYPE:
        case _OSD_FACTORY_BURNIN:

            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            RTDNVRamSaveOsdUserData();
            break;

        case _OSD_FACTORY_CT1_RED:
        case _OSD_FACTORY_CT2_RED:
        case _OSD_FACTORY_CT3_RED:
        case _OSD_FACTORY_CT4_RED:
        case _OSD_FACTORY_CT5_RED:
        case _OSD_FACTORY_CT6_RED:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_stColorProcData.usColorTempR = g_stFactoryOsdItemData.usAdjValue << 4;

#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SYSTEM_SELECT_REGION()));

            break;

        case _OSD_FACTORY_CT1_GREEN:
        case _OSD_FACTORY_CT2_GREEN:
        case _OSD_FACTORY_CT3_GREEN:
        case _OSD_FACTORY_CT4_GREEN:
        case _OSD_FACTORY_CT5_GREEN:
        case _OSD_FACTORY_CT6_GREEN:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_stColorProcData.usColorTempG = g_stFactoryOsdItemData.usAdjValue << 4;

#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SYSTEM_SELECT_REGION()));
            break;

        case _OSD_FACTORY_CT1_BLUE:
        case _OSD_FACTORY_CT2_BLUE:
        case _OSD_FACTORY_CT3_BLUE:
        case _OSD_FACTORY_CT4_BLUE:
        case _OSD_FACTORY_CT5_BLUE:
        case _OSD_FACTORY_CT6_BLUE:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_stColorProcData.usColorTempB = g_stFactoryOsdItemData.usAdjValue << 4;

#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SYSTEM_SELECT_REGION()));
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSD_FACTORY_GAIN_RED:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_stVgaAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL] = g_stFactoryOsdItemData.usAdjValue;
            UserCommonVgaAdcDataAdjust();
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_ADCDATA_MSG);
            break;

        case _OSD_FACTORY_GAIN_GREEN:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_stVgaAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL] = g_stFactoryOsdItemData.usAdjValue;
            UserCommonVgaAdcDataAdjust();
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_ADCDATA_MSG);
            break;

        case _OSD_FACTORY_GAIN_BLUE:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_stVgaAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL] = g_stFactoryOsdItemData.usAdjValue;
            UserCommonVgaAdcDataAdjust();
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_ADCDATA_MSG);
            break;

        case _OSD_FACTORY_OFFSET_RED:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_stVgaAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL] = g_stFactoryOsdItemData.usAdjValue;
            UserCommonVgaAdcDataAdjust();
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_ADCDATA_MSG);
            break;

        case _OSD_FACTORY_OFFSET_GREEN:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_stVgaAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL] = g_stFactoryOsdItemData.usAdjValue;
            UserCommonVgaAdcDataAdjust();
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_ADCDATA_MSG);
            break;

        case _OSD_FACTORY_OFFSET_BLUE:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_stVgaAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL] = g_stFactoryOsdItemData.usAdjValue;
            UserCommonVgaAdcDataAdjust();
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_ADCDATA_MSG);
            break;
#endif // End of #if(_VGA_SUPPORT == _ON)

        case _OSD_FACTORY_BG:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            UserCommonDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, g_stFactoryOsdItemData.usAdjValue);
            break;

        case _OSD_FACTORY_BG_RED:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_ucBgColorR = g_stFactoryOsdItemData.usAdjValue;
            UserCommonDDomainBackgroundSetColor(_DDOMAIN_RGN_ALL, g_ucBgColorR, g_ucBgColorG, g_ucBgColorB, _DB_APPLY_POLLING);
            break;

        case _OSD_FACTORY_BG_GREEN:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_ucBgColorG = g_stFactoryOsdItemData.usAdjValue;
            UserCommonDDomainBackgroundSetColor(_DDOMAIN_RGN_ALL, g_ucBgColorR, g_ucBgColorG, g_ucBgColorB, _DB_APPLY_POLLING);
            break;

        case _OSD_FACTORY_BG_BLUE:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_ucBgColorB = g_stFactoryOsdItemData.usAdjValue;
            UserCommonDDomainBackgroundSetColor(_DDOMAIN_RGN_ALL, g_ucBgColorR, g_ucBgColorG, g_ucBgColorB, _DB_APPLY_POLLING);
            break;

        case _OSD_FACTORY_SSC:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            UserCommonNVRamSetSystemData(_SSC, g_stFactoryOsdItemData.usAdjValue);
            UserCommonDisplayPLLSetDPLLSSC(g_ucSSCspeed, g_stFactoryOsdItemData.usAdjValue);
            UserCommonNVRamSaveSystemData();
            break;

        case _OSD_FACTORY_SSC_SPEED:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_ucSSCspeed = g_stFactoryOsdItemData.usAdjValue;
            UserCommonDisplayPLLSetDPLLSSC(g_stFactoryOsdItemData.usAdjValue, UserCommonNVRamGetSystemData(_SSC));
            break;

        case _OSD_FACTORY_LVDS_DRIVING:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            g_ucLVDSclk = g_stFactoryOsdItemData.usAdjValue;
            // UserCommonDisplayPLLSetDPLLSSC(g_stFactoryOsdItemData.usAdjValue);
            break;

#if(_DP_SUPPORT == _ON)
        case _OSD_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            UserCommonNVRamSetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH, g_stFactoryOsdItemData.usAdjValue);
            UserCommonNVRamSaveSystemData();
            break;

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
        case _OSD_FACTORY_DP_AUX_MODE:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            UserCommonNVRamSetSystemData(_DP_AUX_DIFF_MODE, g_stFactoryOsdItemData.usAdjValue);
            UserCommonDpAuxSet();
            UserCommonNVRamSaveSystemData();
            break;
#endif

        case _OSD_FACTORY_DP_AUX_SETTING:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            UserCommonNVRamSetSystemData(_DP_AUX_ADJR_SETTING, g_stFactoryOsdItemData.usAdjValue);
            UserCommonDpAuxSet();
            UserCommonNVRamSaveSystemData();
            break;
#endif // End of #if(_DP_SUPPORT == _ON)

        case _OSD_FACTORY_HOT_PLUG_HDMI_SUPPORT:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            UserCommonNVRamSetSystemData(_HDMI_HOT_PLUG_SUPPORT, g_stFactoryOsdItemData.usAdjValue);
            UserCommonNVRamSaveSystemData();
            break;

        case _OSD_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            UserCommonNVRamSetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME, g_stFactoryOsdItemData.usAdjValue);
            UserCommonNVRamSaveSystemData();
            break;
        case _OSD_FACTORY_OSD_DOUBLE_SIZE:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            SET_OSD_DOUBLE_SIZE(g_stFactoryOsdItemData.usAdjValue);
            UserCommonNVRamSaveSystemData();
            break;

        case _OSD_FACTORY_COLORIMETRY_SEAMLESS:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            UserCommonNVRamSetSystemData(_COLORIMETRY_SEAMLESS_CHANGE, g_stFactoryOsdItemData.usAdjValue);
            UserCommonNVRamSaveSystemData();
            break;

        case _OSD_FACTORY_DP_IRQ_TIME:
            OsdFactoryMenuItemValueAdj(ROW(OsdFactoryGetItemRow(enumOsdFactoryItem)), (OsdFactoryGetItemCol(enumOsdFactoryItem)), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + GET_OSD_ITEM_INDEX()));
            UserCommonNVRamSetSystemData(_DP_IRQ_TIME, g_stFactoryOsdItemData.usAdjValue);
            UserCommonNVRamSaveSystemData();
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFactoryFuncSetPosition(BYTE ucType, WORD usX, WORD usY)
{
    if(ucType == _FACTORY_OSD)
    {
        usX = ((DWORD)(_PANEL_DH_WIDTH - _FACTORY_OSD_WINDOW_SIZE_X) * usX) / _OSD_H_POS_MAX;
        usY = ((DWORD)(_PANEL_DV_HEIGHT - _FACTORY_OSD_WINDOW_SIZE_Y) * usY) / _OSD_V_POS_MAX;
    }

    UserCommonOsdPosition(_OSD_POSITION_GLOBAL_A, usX, usY);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFactoryChangColorTemp(void)
{
    if((OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) >= _OSD_FACTORY_CT1_RED) &&
       (OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) <= _OSD_FACTORY_CT1_BLUE))
    {
        if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_9300)
        {
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_9300);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
        }
    }
    else if((OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) >= _OSD_FACTORY_CT2_RED) &&
            (OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) <= _OSD_FACTORY_CT2_BLUE))
    {
        if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_7500)
        {
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_7500);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
        }
    }
    else if((OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) >= _OSD_FACTORY_CT3_RED) &&
            (OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) <= _OSD_FACTORY_CT3_BLUE))
    {
        if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_6500)
        {
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_6500);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
        }
    }
    else if((OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) >= _OSD_FACTORY_CT4_RED) &&
            (OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) <= _OSD_FACTORY_CT4_BLUE))
    {
        if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_5800)
        {
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_5800);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
        }
    }
    else if((OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) >= _OSD_FACTORY_CT5_RED) &&
            (OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) <= _OSD_FACTORY_CT5_BLUE))
    {
        if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_SRGB)
        {
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_SRGB);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
        }
    }
    else if((OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) >= _OSD_FACTORY_CT6_RED) &&
            (OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) <= _OSD_FACTORY_CT6_BLUE))
    {
        if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_USER)
        {
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
        }
    }
    else // if((OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) >= _OSD_FACTORY_CT6_RED) && (OsdFactoryGetItem(GET_OSD_ITEM_INDEX()) >= _OSD_FACTORY_CT6_BLUE))
    {
        if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_USER)
        {
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFactoryItemValueUpdate(EnumOsdFactoryItem enumOsdFactoryItem)
{
    memset(&g_stFactoryOsdItemData, 0, sizeof(StructOsdItemDataType));

    switch(enumOsdFactoryItem)
    {
        case _OSD_FACTORY_AUTOCOLOR:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_AUTO_COLOR_FACT;
            g_stFactoryOsdItemData.usAdjValue = _OFF;
            g_stFactoryOsdItemData.usAdjValueMin = _OFF;
            g_stFactoryOsdItemData.usAdjValueMax = _ON;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_OFF_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_DIRECT;
            break;

        case _OSD_FACTORY_AUTOCOLOR_TYPE:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_AUTO_COLOR_TYPE_FACT;
            g_stFactoryOsdItemData.usAdjValue = GET_OSD_FACTORY_AUTO_COLOR_TYPE();
            g_stFactoryOsdItemData.usAdjValueMin = _AUTO_COLOR_TYPE_INTERNAL;
            g_stFactoryOsdItemData.usAdjValueMax = _AUTO_COLOR_TYPE_EXTERNAL;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_INTERNEL_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_FACTORY_BURNIN:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_BURN_IN_FACT;
            g_stFactoryOsdItemData.usAdjValue = _OFF;
            g_stFactoryOsdItemData.usAdjValueMin = _OFF;
            g_stFactoryOsdItemData.usAdjValueMax = _ON;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_OFF_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_FACTORY_RESET_PANEL_TIME:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_PANEL_TIME_FACT;
            g_stFactoryOsdItemData.usAdjValue = _OFF;
            g_stFactoryOsdItemData.usAdjValueMin = _OFF;
            g_stFactoryOsdItemData.usAdjValueMax = _ON;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_OFF_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_DIRECT;
            break;

        case _OSD_FACTORY_CT1_RED:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_9300);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT9300_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempR >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_RED_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT1_GREEN:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_9300);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT9300_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempG >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_GREEN_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT1_BLUE:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_9300);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT9300_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempB >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_BLUE_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT2_RED:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_7500);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT7500_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempR >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_RED_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT2_GREEN:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_7500);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT7500_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempG >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_GREEN_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT2_BLUE:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_7500);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT7500_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempB >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_BLUE_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT3_RED:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_6500);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT6500_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempR >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_RED_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT3_GREEN:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_6500);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT6500_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempG >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_GREEN_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT3_BLUE:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_6500);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT6500_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempB >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_BLUE_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT4_RED:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_5800);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT5800_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempR >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_RED_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT4_GREEN:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_5800);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT5800_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempG >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_GREEN_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT4_BLUE:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_5800);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_CT5800_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempB >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_BLUE_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT5_RED:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_SRGB);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_SRGB_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempR >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_RED_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT5_GREEN:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_SRGB);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_SRGB_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempG >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_GREEN_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT5_BLUE:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_SRGB);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_SRGB_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempB >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_BLUE_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT6_RED:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_USER_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempR >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_RED_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT6_GREEN:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_USER_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempG >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_GREEN_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_CT6_BLUE:
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);
            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_USER_FACT;
            g_stFactoryOsdItemData.usAdjValue = (g_stColorProcData.usColorTempB >> 4);
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_BLUE_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSD_FACTORY_GAIN_RED:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_ADC_GAIN_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_stVgaAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL];
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_RED_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_GAIN_GREEN:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_ADC_GAIN_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_stVgaAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL];
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_GREEN_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_GAIN_BLUE:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_ADC_GAIN_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_stVgaAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL];
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_BLUE_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_OFFSET_RED:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_ADCOFFSET_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_stVgaAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL];
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_RED_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_OFFSET_GREEN:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_ADCOFFSET_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_stVgaAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL];
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_GREEN_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_OFFSET_BLUE:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_ADCOFFSET_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_stVgaAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL];
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 255;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_BLUE_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;
#endif

        case _OSD_FACTORY_EXIT:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_EXIT_FACT;
            g_stFactoryOsdItemData.usAdjValue = 0;
            g_stFactoryOsdItemData.usAdjValueMin = 0;
            g_stFactoryOsdItemData.usAdjValueMax = 0;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_NULL_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_DIRECT;
            break;

        case _OSD_FACTORY_BG:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_B_G_COLOR_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_bBgOnOff;
            g_stFactoryOsdItemData.usAdjValueMin = _OFF;
            g_stFactoryOsdItemData.usAdjValueMax = _ON;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_OFF_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_FACTORY_BG_RED:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_B_G_COLOR_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_ucBgColorR;
            g_stFactoryOsdItemData.usAdjValueMin = _FACTORY_RBG_MIN;
            g_stFactoryOsdItemData.usAdjValueMax = _FACTORY_RBG_MAX;
            g_stFactoryOsdItemData.usAdjValueCenter = _FACTORY_RBG_CENTER;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_RED_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_BG_GREEN:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_B_G_COLOR_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_ucBgColorG;
            g_stFactoryOsdItemData.usAdjValueMin = _FACTORY_RBG_MIN;
            g_stFactoryOsdItemData.usAdjValueMax = _FACTORY_RBG_MAX;
            g_stFactoryOsdItemData.usAdjValueCenter = _FACTORY_RBG_CENTER;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_GREEN_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_BG_BLUE:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_B_G_COLOR_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_ucBgColorB;
            g_stFactoryOsdItemData.usAdjValueMin = _FACTORY_RBG_MIN;
            g_stFactoryOsdItemData.usAdjValueMax = _FACTORY_RBG_MAX;
            g_stFactoryOsdItemData.usAdjValueCenter = _FACTORY_RBG_CENTER;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_BLUE_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_SSC:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_SSC_FACT;
            g_stFactoryOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_SSC);
            g_stFactoryOsdItemData.usAdjValueMin = _FACTORY_SSC_MIN;
            g_stFactoryOsdItemData.usAdjValueMax = _FACTORY_SSC_MAX;
            g_stFactoryOsdItemData.usAdjValueCenter = (_FACTORY_SSC_MAX - _FACTORY_SSC_MIN) / 2;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_NULL_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_SSC_SPEED:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_SSC_SPEED_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_ucSSCspeed;
            g_stFactoryOsdItemData.usAdjValueMin = _SPEED_33K;
            g_stFactoryOsdItemData.usAdjValueMax = _SPEED_30K;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_SPEED33_K_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_FACTORY_LVDS_DRIVING:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_LVDS_DRIVING_FACT;
            g_stFactoryOsdItemData.usAdjValue = g_ucLVDSclk;
            g_stFactoryOsdItemData.usAdjValueMin = _LVDS_DRIV_CONTROL_2_0;
            g_stFactoryOsdItemData.usAdjValueMax = _LVDS_DRIV_CONTROL_1_5;
            g_stFactoryOsdItemData.usAdjValueCenter = (g_stFactoryOsdItemData.usAdjValueMax - g_stFactoryOsdItemData.usAdjValueMin) / 2;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_C20MA_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_DP_HPD_DC_OFF_SUPPORT_FACT;
            g_stFactoryOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH);
            g_stFactoryOsdItemData.usAdjValueMin = _OFF;
            g_stFactoryOsdItemData.usAdjValueMax = _ON;
            // g_stFactoryOsdItemData.usAdjValueCenter = (_FACTORY_SSC_MAX-_FACTORY_SSC_MIN)/2;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_OFF_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_FACTORY_HOT_PLUG_HDMI_SUPPORT:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_HDMI_HPD_SUPPOT_FACT;
            g_stFactoryOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT);
            g_stFactoryOsdItemData.usAdjValueMin = _OFF;
            g_stFactoryOsdItemData.usAdjValueMax = _ON;
            // g_stFactoryOsdItemData.usAdjValueCenter = (_FACTORY_SSC_MAX-_FACTORY_SSC_MIN)/2;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_OFF_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_HDMI_HDP_TIME_FACT;
            g_stFactoryOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME);
            g_stFactoryOsdItemData.usAdjValueMin = _FACTORY_HOT_PLUG_HDMI_TIME_MIN;
            g_stFactoryOsdItemData.usAdjValueMax = _FACTORY_HOT_PLUG_HDMI_TIME_MAX;
            g_stFactoryOsdItemData.usAdjValueCenter = (_FACTORY_HOT_PLUG_HDMI_TIME_MAX - _FACTORY_HOT_PLUG_HDMI_TIME_MIN) / 2;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_NULL_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_DP_AUX_MODE:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_DP_AUX_DIFF_MODE_FACT;
            g_stFactoryOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_DP_AUX_DIFF_MODE);
            g_stFactoryOsdItemData.usAdjValueMin = _OFF;
            g_stFactoryOsdItemData.usAdjValueMax = _ON;
            // g_stFactoryOsdItemData.usAdjValueCenter = (_FACTORY_HOT_PLUG_HDMI_TIME_MAX-_FACTORY_HOT_PLUG_HDMI_TIME_MIN)/2;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_SINGLE_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_FACTORY_OSD_DOUBLE_SIZE:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_OSD_DOUBLE_SIZE_FACT;
            g_stFactoryOsdItemData.usAdjValue = GET_OSD_DOUBLE_SIZE();
            g_stFactoryOsdItemData.usAdjValueMin = _OFF;
            g_stFactoryOsdItemData.usAdjValueMax = _ON;
            // g_stFactoryOsdItemData.usAdjValueCenter = (_FACTORY_HOT_PLUG_HDMI_TIME_MAX-_FACTORY_HOT_PLUG_HDMI_TIME_MIN)/2;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_OFF_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_FACTORY_COLORIMETRY_SEAMLESS:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_COLORIMETRY_SAEMLESS_FACT;
            g_stFactoryOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_COLORIMETRY_SEAMLESS_CHANGE);
            g_stFactoryOsdItemData.usAdjValueMin = _OFF;
            g_stFactoryOsdItemData.usAdjValueMax = _ON;
            // g_stFactoryOsdItemData.usAdjValueCenter = (_FACTORY_HOT_PLUG_HDMI_TIME_MAX-_FACTORY_HOT_PLUG_HDMI_TIME_MIN)/2;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_OFF_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_LIST;
            break;

        case _OSD_FACTORY_DP_AUX_SETTING:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_DP_AUX_ADJ_SETTING_FACT;
            g_stFactoryOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING);
            g_stFactoryOsdItemData.usAdjValueMin = _FACTORY_DP_ADJ_SETTING_MIN;
            g_stFactoryOsdItemData.usAdjValueMax = _FACTORY_DP_ADJ_SETTING_MAX;
            g_stFactoryOsdItemData.usAdjValueCenter = (_FACTORY_DP_ADJ_SETTING_MAX - _FACTORY_DP_ADJ_SETTING_MIN) / 2;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_NULL_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_REAL;
            break;

        case _OSD_FACTORY_DP_IRQ_TIME:
            g_stFactoryOsdItemData.usStringIdx = _OSD_TEXT_DP_IRQ_TIME_FACT;
            g_stFactoryOsdItemData.usAdjValue = UserCommonNVRamGetSystemData(_DP_IRQ_TIME);
            g_stFactoryOsdItemData.usAdjValueMin = _FACTORY_DP_IRQ_TIME_MIN;
            g_stFactoryOsdItemData.usAdjValueMax = _FACTORY_DP_IRQ_TIME_MAX;
            g_stFactoryOsdItemData.usAdjValueCenter = (_FACTORY_DP_IRQ_TIME_MAX - _FACTORY_DP_IRQ_TIME_MIN) / 2;
            g_stFactoryOsdItemData.usSubStringIdx = _OSD_TEXT_NULL_FACT;
            g_stFactoryOsdItemData.b3ShowType = _ADJ_BAR_10_TIMES;
            break;

        case _OSD_FACTORY_OSD_END:
        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFactoryHilightWindow(BYTE ucWin, WORD usIndex, BYTE ucColor)
{
    BYTE ucROW = OsdFactoryGetItemRow(OsdFactoryGetItem(usIndex));

    switch(OsdFactoryGetItem(usIndex))
    {
        case _OSD_FACTORY_CT1_RED:
        case _OSD_FACTORY_CT2_RED:
        case _OSD_FACTORY_CT3_RED:
        case _OSD_FACTORY_CT4_RED:
        case _OSD_FACTORY_CT5_RED:
        case _OSD_FACTORY_CT6_RED:
        case _OSD_FACTORY_GAIN_RED:
        case _OSD_FACTORY_OFFSET_RED:
        case _OSD_FACTORY_BG_RED:
            SET_OSD_WINDOW_NUMBER(ucWin);
            SET_OSD_WINDOW_COLOR(ucColor);

            SET_OSD_WINDOW_ENABLE(_ENABLE);
            UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
            UserCommonOsdDrawWindow((_FACTORY_R_COL * _FONT_WIDTH), ((ucROW) * _FONT_HEIGHT), ((_FACTORY_R_COL + 7) * _FONT_WIDTH), ((ucROW + 1) * _FONT_HEIGHT));
            UserCommonOsdWindowHighlightFunction(_ENABLE, ucWin, _CP_RED, _CP_BLACK, ucColor);
            break;

        case _OSD_FACTORY_CT1_BLUE:
        case _OSD_FACTORY_CT2_BLUE:
        case _OSD_FACTORY_CT3_BLUE:
        case _OSD_FACTORY_CT4_BLUE:
        case _OSD_FACTORY_CT5_BLUE:
        case _OSD_FACTORY_CT6_BLUE:
        case _OSD_FACTORY_GAIN_BLUE:
        case _OSD_FACTORY_OFFSET_BLUE:
        case _OSD_FACTORY_BG_BLUE:
            SET_OSD_WINDOW_NUMBER(ucWin);
            SET_OSD_WINDOW_COLOR(ucColor);

            SET_OSD_WINDOW_ENABLE(_ENABLE);
            UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
            UserCommonOsdDrawWindow((_FACTORY_B_COL * _FONT_WIDTH), ((ucROW) * _FONT_HEIGHT), ((_FACTORY_B_COL + 7) * _FONT_WIDTH), ((ucROW + 1) * _FONT_HEIGHT));
            UserCommonOsdWindowHighlightFunction(_ENABLE, ucWin, _CP_RED, _CP_BLACK, ucColor);
            break;

        case _OSD_FACTORY_CT1_GREEN:
        case _OSD_FACTORY_CT2_GREEN:
        case _OSD_FACTORY_CT3_GREEN:
        case _OSD_FACTORY_CT4_GREEN:
        case _OSD_FACTORY_CT5_GREEN:
        case _OSD_FACTORY_CT6_GREEN:
        case _OSD_FACTORY_GAIN_GREEN:
        case _OSD_FACTORY_OFFSET_GREEN:
        case _OSD_FACTORY_BG_GREEN:
            SET_OSD_WINDOW_NUMBER(ucWin);
            SET_OSD_WINDOW_COLOR(ucColor);

            SET_OSD_WINDOW_ENABLE(_ENABLE);
            UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
            UserCommonOsdDrawWindow((_FACTORY_G_COL * _FONT_WIDTH), ((ucROW) * _FONT_HEIGHT), ((_FACTORY_G_COL + 7) * _FONT_WIDTH), ((ucROW + 1) * _FONT_HEIGHT));
            UserCommonOsdWindowHighlightFunction(_ENABLE, ucWin, _CP_RED, _CP_BLACK, ucColor);
            break;

        default:
            SET_OSD_WINDOW_NUMBER(ucWin);
            SET_OSD_WINDOW_COLOR(ucColor);

            SET_OSD_WINDOW_ENABLE(_ENABLE);
            UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
            UserCommonOsdDrawWindow(3, ((ucROW) * _FONT_HEIGHT), (_FACTORY_OSD_WINDOW_SIZE_X - 2), ((ucROW + 1) * _FONT_HEIGHT));
            UserCommonOsdWindowHighlightFunction(_ENABLE, ucWin, _CP_RED, _CP_BLACK, ucColor);
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD OsdFactoryGetFontPointer(BYTE ucPointerSelect)
{
    WORD usPointer = 0;

    if(ucPointerSelect == _PFONT_FACTORY_PAGE_0)
    {
        usPointer = GET_OSD_INFO_FONT_POINTER_0();
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_1)
    {
        usPointer = GET_OSD_INFO_FONT_POINTER_1();
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_2)
    {
        usPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_3)
    {
        usPointer = GET_OSD_INFO_FONT_POINTER_3();
    }
    else
    {
        usPointer = _FACTORY_ITEM_WORD_1_START + ((ucPointerSelect - _PFONT_FACTORY_PAGE_ITEM_1) * _FACTORY_ITEM_WORD_GAP);
        SET_OSD_INFO_FONT_POINTER_3(usPointer);
    }
    return usPointer;
}


//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPutStringPropFontTableFact(BYTE ucLanguage, WORD usFontPoint)
{
    if(ucLanguage != _ENGLISH)
    {
        return 0;
    }

    return *(tOSD_TABLE_LANGUAGE_FONT_BODY_FACTORY[_ENGLISH] + usFontPoint);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropFontDataToSramFact(BYTE ucFptsSelect, BYTE *pucArray, BYTE ucRotateType)
{
    if(ucFptsSelect == _PFONT_FACTORY_PAGE_0)
    {
        if(ucRotateType != _OSD_ROTATE_DEGREE_0)
        {
            OsdFuncHardwareCompression(pucArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_0()), GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);
        }
        else// reduce delay can be improve draw speed
        {
            UserCommonOsdAddrSet(_OSD_SRAM_FONT, _OSD_BYTEALL, GET_OSD_INFO_FONT_POINTER_0(), _DISABLE);
            UserCommonOsdBurstWriteDataPortSram(pucArray, 27, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);
        }

        if(GET_OSD_INFO_FONT_POINTER_0() >= _FACTORY_PAGE_0_WORD_END)
        {
            SET_OSD_INFO_FONT_POINTER_0(_FACTORY_PAGE_0_WORD_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_0(GET_OSD_INFO_FONT_POINTER_0() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_FACTORY_PAGE_1)
    {
        if(ucRotateType != _OSD_ROTATE_DEGREE_0)
        {
            OsdFuncHardwareCompression(pucArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_1()), GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);
        }
        else// reduce delay can be improve draw speed
        {
            UserCommonOsdAddrSet(_OSD_SRAM_FONT, _OSD_BYTEALL, GET_OSD_INFO_FONT_POINTER_1(), _DISABLE);
            UserCommonOsdBurstWriteDataPortSram(pucArray, 27, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);
        }

        if(GET_OSD_INFO_FONT_POINTER_1() >= _FACTORY_PAGE_1_WORD_END)
        {
            SET_OSD_INFO_FONT_POINTER_1(_FACTORY_PAGE_1_WORD_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_1(GET_OSD_INFO_FONT_POINTER_1() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_FACTORY_PAGE_2)
    {
        if(ucRotateType != _OSD_ROTATE_DEGREE_0)
        {
            OsdFuncHardwareCompression(pucArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2()), GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);
        }
        else// reduce delay can be improve draw speed
        {
            UserCommonOsdAddrSet(_OSD_SRAM_FONT, _OSD_BYTEALL, GET_OSD_INFO_FONT_POINTER_2(), _DISABLE);
            UserCommonOsdBurstWriteDataPortSram(pucArray, 27, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);
        }

        if(GET_OSD_INFO_FONT_POINTER_2() >= _FACTORY_PAGE_2_WORD_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_FACTORY_PAGE_2_WORD_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if((ucFptsSelect >= _PFONT_FACTORY_PAGE_ITEM_1) &&
            (ucFptsSelect <= _PFONT_FACTORY_PAGE_ITEM_END))
    {
        if(ucRotateType != _OSD_ROTATE_DEGREE_0)
        {
            OsdFuncHardwareCompression(pucArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_3()), GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);
        }
        else// reduce delay can be improve draw speed
        {
            UserCommonOsdAddrSet(_OSD_SRAM_FONT, _OSD_BYTEALL, GET_OSD_INFO_FONT_POINTER_3(), _DISABLE);
            UserCommonOsdBurstWriteDataPortSram(pucArray, 27, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);
        }

        SET_OSD_INFO_FONT_POINTER_3(GET_OSD_INFO_FONT_POINTER_3() + 1);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFactoryShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucCPColor)
{
    BYTE ucIndex = 0;
    BYTE ucTemp = 0;
    BYTE pucDataSN[7] = {0};

    pucDataSN[0] = (U0030_FACTORY + (ulValue / 100000));
    pucDataSN[1] = (U0030_FACTORY + (ulValue % 100000 / 10000));
    pucDataSN[2] = (U0030_FACTORY + (ulValue % 10000) / 1000);
    pucDataSN[3] = (U0030_FACTORY + (ulValue % 1000) / 100);
    pucDataSN[4] = (U0030_FACTORY + (ulValue % 100) / 10);
    pucDataSN[5] = (U0030_FACTORY + (ulValue % 10));

    for(ucIndex = 0; ucIndex < 6; ucIndex++)
    {
        if(pucDataSN[ucIndex] != U0030_FACTORY)
        {
            ucIndex = 6 - ucIndex;
            break;
        }
    }

    if((ulValue == 0) && (((bit)(ucPar & _BIT1)) == _FALSE))
    {
        ucIndex = 1;// show "0"
    }

    // Get show number of numeric
    if((bit)(ucPar & _BIT1) == _TRUE)// Show all
    {
        ucTemp = (ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4;
        ucIndex = (ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4;
    }
    else
    {
        ucTemp = (ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4;

        if(ucTemp < ucIndex)
        {
            ucTemp = ucIndex;
        }
    }

    for(ulValue = 0; ulValue < ucTemp; ulValue++)
    {
        if(ucIndex > ulValue)
        {
            pucDataSN[ulValue] = pucDataSN[(6 - ucIndex) + ulValue];
        }
        else
        {
            pucDataSN[ulValue] = U0020_FACTORY; // Space
        }
    }
    if(ucIndex <= 1)
    {
        pucDataSN[ulValue] = U0020_FACTORY;
        ulValue++;
    }
    pucDataSN[ulValue] = _END_;

    // Align Right
    if((bit)(ucPar & _BIT0) == _ALIGN_RIGHT)
    {
        OsdFactoryFuncClearOsdFont(ucRow, (ucCol - 2), ucTemp, 1);
        OsdFactoryPutString(ucRow, COL(ucCol - 2), ucFontPoint, &pucDataSN[0], ucCPColor, _ENGLISH);
    }
    else
    {
        OsdFactoryFuncClearOsdFont(ucRow, (ucCol), ucTemp, 1);
        OsdFactoryPutString(ucRow, ucCol, ucFontPoint, &pucDataSN[0], ucCPColor, _ENGLISH);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFactoryMenuString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, WORD usString, BYTE ucColor, BYTE ucLanguage)
{
    OsdFactoryFuncClearOsdFont(ucRow, (ucCol), 7, 1);

    OsdFactoryPutString(ucRow, ucCol, ucFptsSelect, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[usString], ucColor, ucLanguage);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFactoryPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE *pucArray, BYTE ucColor, BYTE ucLanguage)
{
    bit bCenterFlag = _FALSE;
    bit bNextLineFlag = _FALSE;
    BYTE pucFontData[27] = {0};
    BYTE ucColBackup = ucCol;

    // update array pointer to selected language position
    if(ucLanguage != 0)
    {
        BYTE ucLanguageIndex = ucLanguage;

        while(ucLanguageIndex != 0)
        {
            if(pucArray[0] == _END_)
            {
                ucLanguageIndex--;
            }
            pucArray++;
        }
    }

    do
    {
        BYTE ucElementCount = 0;
        BYTE ucColumnLength = 0;
        WORD usFontPointer = OsdFactoryGetFontPointer(ucFptsSelect);

        bNextLineFlag = _FALSE;

        memset(pData, 0x00, sizeof(pData));

        if(GET_OSD_INFO_STRING_MODE_LENGTH() != 0)
        {
            WORD usOffset = 0;
            WORD usWidth = 0;

            bCenterFlag = _TRUE;

            // calculate totol string width
            while((pucArray[ucElementCount] != _END_) &&
                  (pucArray[ucElementCount] != _NEXT_LINE))
            {
                pData[3] = pucArray[ucElementCount];

                switch(pData[3])
                {
                    default:
                        usOffset = 0;
                        break;

                    case _FONT_SELECT_EXT1:
                        usOffset = _FONT_SELECT_OFFSET1;
                        break;

                    case _FONT_SELECT_EXT2:
                        usOffset = _FONT_SELECT_OFFSET2;
                        break;
                }

                if(usOffset != 0)
                {
                    ucElementCount++;
                    pData[3] = pucArray[ucElementCount];
                }

                if((usOffset + pData[3]) < (_GLOBAL_FONT_END_OFFSET_FACTORY + _GLOBAL_FONT_END_FACTORY))
                {
                    usWidth += tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[0][pData[3] + usOffset];
                }
                else
                {
                    if(((ucLanguage + 1) < (WORD)(sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY) / sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[0]))) &&
                       (tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[ucLanguage + 1] != NULL))
                    {
                        usWidth += tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[ucLanguage + 1][pData[3] + usOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY];
                    }
                }

                ucElementCount++;
            }

            // String col size
            // total pixels / 12 (round up)
            ucElementCount = (usWidth / 12) + (((usWidth % 12) > 0) ? 1 : 0);

            if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_CENTER)
            {
                // center-aligned
                // add one font if centered width and actual sting width is not both even or both odd
                if((((GET_OSD_INFO_STRING_MODE_LENGTH() % 2) == 0) && ((ucElementCount % 2) == 1)) ||
                   (((GET_OSD_INFO_STRING_MODE_LENGTH() % 2) == 1) && ((ucElementCount % 2) == 0)))
                {
                    ucElementCount++;
                }

                // total center-aligned pixels - total string pixels / 2
                pData[1] = ((ucElementCount * 12) - usWidth) / 2;
            }
            else if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_RIGHT)
            {
                // right aligned
                // count right-aligned pixels
                pData[1] = (ucElementCount * 12) - usWidth;
            }

            // left-aligned
            if(pData[1] == 0)
            {
                bCenterFlag = _FALSE;
            }
        }
        pData[4] = 0;
        ucElementCount = 0;

        // reorder
        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT6);
        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~(_BIT7 | _BIT5)));

        while((pucArray[ucElementCount] != _END_) &&
              (pucArray[ucElementCount] != _NEXT_LINE))
        {
            WORD usOffset = 0;

            switch(pucArray[ucElementCount])
            {
                case _END_:
                    break;

                default:
                    // pixel count = 0 ????
                    if(pData[2] == 0)
                    {
                        pData[3] = pucArray[ucElementCount];

                        if(pData[3] == _FONT_BLANK_PIXEL)
                        {
                            pData[2] = pucArray[ucElementCount + 1];

                            pData[3] = _;
                        }

                        if(bCenterFlag == _TRUE)
                        {
                            pData[3] = _;
                        }
                    }
                    else
                    {
                        pData[3] = _;
                    }

                    switch(pData[3])
                    {
                        default:
                            usOffset = 0;
                            break;

                        case _FONT_SELECT_EXT1:
                            usOffset = _FONT_SELECT_OFFSET1;
                            break;

                        case _FONT_SELECT_EXT2:
                            usOffset = _FONT_SELECT_OFFSET2;
                            break;
                    }

                    if(usOffset != 0)
                    {
                        ucElementCount++;
                        pData[3] = pucArray[ucElementCount];
                    }

                    if((usOffset + pData[3]) < (_GLOBAL_FONT_END_OFFSET_FACTORY + _GLOBAL_FONT_END_FACTORY))
                    {
                        if(pData[2] == 0)
                        {
                            pData[4] = tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[0][pData[3] + usOffset];

                            if(bCenterFlag == _TRUE)
                            {
                                pData[4] = pData[1];
                            }
                        }
                        else
                        {
                            pData[4] = (pData[2] > 12) ? 12 : pData[2];
                            pData[2] -= pData[4];
                        }
                    }
                    else
                    {
                        if(pData[2] == 0)
                        {
                            if(((ucLanguage + 1) < (WORD)(sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY) / sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[0]))) &&
                               (tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[ucLanguage + 1] != NULL))
                            {
                                pData[4] = tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[ucLanguage + 1][pData[3] + usOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY];
                            }
                            else
                            {
                                pData[4] = 0;
                            }

                            if(bCenterFlag == _TRUE)
                            {
                                pData[4] = pData[1];
                            }
                        }
                        else
                        {
                            pData[4] = (pData[2] > 12) ? 12 : pData[2];
                            pData[2] -= pData[4];
                        }
                    }

                    if(pData[2] == 0)
                    {
                        if(pucArray[ucElementCount] != _FONT_BLANK_PIXEL)
                        {
                            ucElementCount++;

                            if(bCenterFlag == _TRUE)
                            {
                                ucElementCount = 0;
                            }
                        }
                        else
                        {
                            ucElementCount += 2;
                        }
                    }
                    break;
            }

            if(pData[5] == 0)
            {
                pData[5] = pData[4];
            }

            // first bits shift direction: left shift
            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT3);

            // left bits shift direction: right shift
            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~_BIT2));

            // first bits shift and second bits shift
            SCALEROSD_FONT_ROTATE_1_2_BITS_SHIFT_SET(((pData[4] - pData[5]) << 4) | pData[5]);

            pData[6] = ucElementCount;
            pData[7] = pData[5];

            for(pData[0] = 0; pData[0] < 9; pData[0]++)
            {
                // restart from last three bytes
                SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT0);

                if(usOffset == _GLOBAL_FONT_END_OFFSET_FACTORY)
                {
                    if(pData[3] >= _GLOBAL_FONT_END_FACTORY)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[3] + usOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[3] + usOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[3] + usOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3) + 2)));
                    }
                    else
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[3] + usOffset) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[3] + usOffset) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[3] + usOffset) * 27) + (pData[0] * 3) + 2)));
                    }
                }
                else if(usOffset > _GLOBAL_FONT_END_OFFSET_FACTORY)
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[3] + usOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3))));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[3] + usOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3) + 1)));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[3] + usOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3) + 2)));
                }
                else// if(usOffset < _GLOBAL_FONT_END_OFFSET_FACTORY)
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[3] + usOffset) * 27) + (pData[0] * 3))));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[3] + usOffset) * 27) + (pData[0] * 3) + 1)));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[3] + usOffset) * 27) + (pData[0] * 3) + 2)));
                }

                ucElementCount = pData[6];
                pData[5] = pData[7];

                if((pData[5] == 12) ||
                   (pucArray[ucElementCount] == _END_) ||
                   (pucArray[ucElementCount] == _NEXT_LINE))
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                }

                while((pData[5] < 12) &&
                      (pucArray[ucElementCount] != _END_) &&
                      (pucArray[ucElementCount] != _NEXT_LINE))
                {
                    WORD usFontOffset = 0;

                    // third bits shift and left bits shift
                    SCALEROSD_FONT_ROTATE_3_L_BITS_SHIFT_SET((pData[5] << 4) | pData[5]);

                    if(pData[2] == 0)
                    {
                        pData[8] = pucArray[ucElementCount];

                        if(pData[8] == _FONT_BLANK_PIXEL)
                        {
                            pData[2] = pucArray[ucElementCount + 1];

                            pData[8] = _;
                        }
                    }
                    else
                    {
                        pData[8] = _;
                    }

                    if((pData[8] == _FONT_SELECT_EXT1) ||
                       (pData[8] == _FONT_SELECT_EXT2))
                    {
                        usFontOffset = (pData[8] == _FONT_SELECT_EXT1) ? _FONT_SELECT_OFFSET1 : _FONT_SELECT_OFFSET2;
                        ucElementCount++;
                        pData[8] = pucArray[ucElementCount];
                    }
                    else
                    {
                        usFontOffset = 0;
                    }

                    if((usFontOffset + pData[8]) < (_GLOBAL_FONT_END_OFFSET_FACTORY + _GLOBAL_FONT_END_FACTORY))
                    {
                        if(pData[2] == 0)
                        {
                            pData[4] = tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[0][pData[8] + usFontOffset];
                        }
                        else
                        {
                            pData[4] = (pData[2] > 12) ? 12 : pData[2];
                        }
                    }
                    else
                    {
                        if(pData[2] == 0)
                        {
                            if(((ucLanguage + 1) < (WORD)(sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY) / sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[0]))) &&
                               (tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[ucLanguage + 1] != NULL))
                            {
                                pData[4] = tOSD_TABLE_LANGUAGE_FONT_WIDTH_FACTORY[ucLanguage + 1][pData[8] + usFontOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY];
                            }
                            else
                            {
                                pData[4] = 0;
                            }
                        }
                        else
                        {
                            pData[4] = (pData[2] > 12) ? 12 : pData[2];
                        }
                    }

                    ucElementCount++;
                    pData[5] += pData[4];

                    if(usFontOffset == _GLOBAL_FONT_END_OFFSET_FACTORY)
                    {
                        if(pData[8] >= _GLOBAL_FONT_END_FACTORY)
                        {
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[8] + usFontOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3))));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[8] + usFontOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3) + 1)));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[8] + usFontOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3) + 2)));
                        }
                        else
                        {
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[8] + usFontOffset) * 27) + (pData[0] * 3))));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[8] + usFontOffset) * 27) + (pData[0] * 3) + 1)));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[8] + usFontOffset) * 27) + (pData[0] * 3) + 2)));
                        }
                    }
                    else if(usFontOffset > _GLOBAL_FONT_END_OFFSET_FACTORY)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[8] + usFontOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[8] + usFontOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact((ucLanguage + 1), (((pData[8] + usFontOffset - _GLOBAL_FONT_END_FACTORY - _GLOBAL_FONT_END_OFFSET_FACTORY) * 27) + (pData[0] * 3) + 2)));
                    }
                    else// if(usFontOffset < _GLOBAL_FONT_END_OFFSET_FACTORY)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[8] + usFontOffset) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[8] + usFontOffset) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTableFact(0, (((pData[8] + usFontOffset) * 27) + (pData[0] * 3) + 2)));
                    }
                }

                pucFontData[pData[0] * 3 + 2] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
                pucFontData[pData[0] * 3 + 1] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
                pucFontData[pData[0] * 3] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            }

            if(pData[5] <= 12)
            {
                pData[5] = 0;
            }
            else
            {
                pData[5] = pData[5] - 12;

                if(ucElementCount >= 1)
                {
                    ucElementCount--;
                }
                else
                {
                    ucElementCount = 1;
                }

                pData[8] = pucArray[ucElementCount - 1];

                if((pData[8] == _FONT_SELECT_EXT1) ||
                   (pData[8] == _FONT_SELECT_EXT2))
                {
                    ucElementCount--;
                }
            }

            // Write the pro font data to sram
            OsdPropFontDataToSramFact(ucFptsSelect, pucFontData, _OSD_ROTATE_DEGREE_0);

            // Record the length (coloumn) of prop string
            ucColumnLength++;

            // Only shift for the first word
            bCenterFlag = _FALSE;
        }// End of while(*(pArray + stringcnt) != _END_)

        if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_CENTER)
        {
            ucCol = ucColBackup + ((((GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength) / 2) < 0) ? 0 : ((GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength) / 2));
        }
        else if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_RIGHT)
        {
            ucCol = ucColBackup + (((GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength) < 0) ? 0 : (GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength));
        }

        // Increase the sram address pointer
        UserCommonOsdSramAddressCount(ucRow, ucCol, _OSD_BYTEALL);

        while(ucColumnLength != 0)
        {
            ucColumnLength -= 1;

            // Gen3 OSd support 0-1023 1 bit font
            UserCommonOsdSetDataPortSram(HIBYTE(usFontPointer) | _OSD_MODE_BYTE0);
            UserCommonOsdSetDataPortSram(LOBYTE(usFontPointer));
            UserCommonOsdSetDataPortSram(ucColor);

            usFontPointer = OsdFactoryFuncSetOsdFontPointer(ucFptsSelect, usFontPointer);
        }

        if(pucArray[ucElementCount] == _NEXT_LINE)
        {
            // Start the next line from pArray
            pucArray += ucElementCount + 1;
            ucRow++;

            bNextLineFlag = _TRUE;
        }
    }
    while(bNextLineFlag == _TRUE);

    CLR_OSD_INFO_STRING_MODE();
    CLR_OSD_INFO_STRING_MODE_LENGTH();
}

//--------------------------------------------------
// Description  :Picture sub Item switcht
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdFactoryMenuItemValue(BYTE ucRow, BYTE ucCol, BYTE ucColor, BYTE ucPFONTFACTORY)
{
    WORD usTemp = 0;

    if(g_stFactoryOsdItemData.b3ShowType == _ADJ_LIST)
    {
        usTemp = g_stFactoryOsdItemData.usSubStringIdx + g_stFactoryOsdItemData.usAdjValue;
        OsdFactoryMenuString(ROW(ucRow), COL(ucCol), ucPFONTFACTORY, usTemp, COLOR(ucColor, _CP_BG), _ENGLISH);
    }
    else if(g_stFactoryOsdItemData.b3ShowType == _ADJ_BAR_PERCENT)
    {
        usTemp = UserCommonDisplayRealValueToPercentAdjust(
            g_stFactoryOsdItemData.usAdjValue,
            g_stFactoryOsdItemData.usAdjValueMax,
            g_stFactoryOsdItemData.usAdjValueMin,
            (g_stFactoryOsdItemData.usAdjValueMin + (g_stFactoryOsdItemData.usAdjValueMax - g_stFactoryOsdItemData.usAdjValueMin) / 2));

        OsdFactoryShowNumber(ROW(ucRow), COL(ucCol), usTemp, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucPFONTFACTORY, COLOR(ucColor, _CP_BG));
    }
    else if(g_stFactoryOsdItemData.b3ShowType == _ADJ_BAR_REAL)
    {
        usTemp = g_stFactoryOsdItemData.usAdjValue;
        OsdFactoryShowNumber(ROW(ucRow), COL(ucCol), usTemp, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucPFONTFACTORY, COLOR(ucColor, _CP_BG));
    }
    else if(g_stFactoryOsdItemData.b3ShowType == _ADJ_BAR_10_TIMES)
    {
        usTemp = g_stFactoryOsdItemData.usAdjValue * 10;
        OsdFactoryShowNumber(ROW(ucRow), COL(ucCol), (usTemp), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), ucPFONTFACTORY, COLOR(ucColor, _CP_BG));
    }
    else// if(g_stFactoryOsdItemData.b3ShowType == _ADJ_DIRECT)
    {
    }
}
//--------------------------------------------------
// Description  :Picture sub Item switcht
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdFactoryMenuItemValueAdj(BYTE ucRow, BYTE ucCol, BYTE ucColor, BYTE ucPFONTFACTORY)
{
    WORD usTemp = 0;

    if(g_stFactoryOsdItemData.b3ShowType == _ADJ_LIST)
    {
        g_stFactoryOsdItemData.usAdjValue = (BYTE)OsdFactoryDetOverRange((g_stFactoryOsdItemData.usAdjValue), (g_stFactoryOsdItemData.usAdjValueMax), (g_stFactoryOsdItemData.usAdjValueMin), _ON);

        usTemp = g_stFactoryOsdItemData.usSubStringIdx + g_stFactoryOsdItemData.usAdjValue;
        OsdFactoryMenuString(ROW(ucRow), COL(ucCol), ucPFONTFACTORY, usTemp, COLOR(ucColor, _CP_BG), _ENGLISH);
    }
    else if(g_stFactoryOsdItemData.b3ShowType == _ADJ_BAR_PERCENT)
    {
        g_stFactoryOsdItemData.usAdjValue = (BYTE)OsdFactoryDetOverRange((g_stFactoryOsdItemData.usAdjValue), (g_stFactoryOsdItemData.usAdjValueMax), (g_stFactoryOsdItemData.usAdjValueMin), _OFF);
        usTemp = UserCommonDisplayRealValueToPercentAdjust(g_stFactoryOsdItemData.usAdjValue, g_stFactoryOsdItemData.usAdjValueMax, g_stFactoryOsdItemData.usAdjValueMin, g_stFactoryOsdItemData.usAdjValueCenter);
        OsdFactoryShowNumber(ROW(ucRow), COL(ucCol), usTemp, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), ucPFONTFACTORY, COLOR(ucColor, _CP_BG));
    }
    else if(g_stFactoryOsdItemData.b3ShowType == _ADJ_BAR_REAL)
    {
        g_stFactoryOsdItemData.usAdjValue = (BYTE)OsdFactoryDetOverRange((g_stFactoryOsdItemData.usAdjValue), (g_stFactoryOsdItemData.usAdjValueMax), (g_stFactoryOsdItemData.usAdjValueMin), _OFF);
        usTemp = g_stFactoryOsdItemData.usAdjValue;
        OsdFactoryShowNumber(ROW(ucRow), COL(ucCol), usTemp, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), ucPFONTFACTORY, COLOR(ucColor, _CP_BG));
    }
    else if(g_stFactoryOsdItemData.b3ShowType == _ADJ_BAR_10_TIMES)
    {
        g_stFactoryOsdItemData.usAdjValue = (BYTE)OsdFactoryDetOverRange((g_stFactoryOsdItemData.usAdjValue), (g_stFactoryOsdItemData.usAdjValueMax), (g_stFactoryOsdItemData.usAdjValueMin), _OFF);
        usTemp = g_stFactoryOsdItemData.usAdjValue * 10;
        OsdFactoryShowNumber(ROW(ucRow), COL(ucCol), (usTemp), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), ucPFONTFACTORY, COLOR(ucColor, _CP_BG));
    }
    else// if(g_stFactoryOsdItemData.b3ShowType == _ADJ_DIRECT)
    {
    }

    DebugMessageOsd("g_stFactoryOsdItemData.usAdjValue", g_stFactoryOsdItemData.usAdjValue);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumOsdFactoryItem OsdFactoryGetItem(WORD usIdx)
{
    return tOSD_FACTORY_PAGE1_ITEM_PRI[usIdx];
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD OsdFactoryGetItemMax(void)
{
    return _OSD_FACTORY_PAGE1_ITEM_AMOUNT;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD OsdFactoryGetItemRow(EnumOsdFactoryItem enumOsdFactoryItem)
{
    WORD usForLoop = 0;
    WORD usForRow = _FACTORY_MENU_ROW1;

    for(usForLoop = 0; usForLoop < _OSD_FACTORY_PAGE1_ITEM_AMOUNT; usForLoop++)
    {
        if(tOSD_FACTORY_PAGE1_ITEM_PRI[usForLoop] == enumOsdFactoryItem)
        {
            return ROW(usForRow);
        }

        switch(tOSD_FACTORY_PAGE1_ITEM_PRI[usForLoop])
        {
            case _OSD_FACTORY_CT1_RED:
            case _OSD_FACTORY_CT1_GREEN:
            case _OSD_FACTORY_CT2_RED:
            case _OSD_FACTORY_CT2_GREEN:
            case _OSD_FACTORY_CT3_RED:
            case _OSD_FACTORY_CT3_GREEN:
            case _OSD_FACTORY_CT4_RED:
            case _OSD_FACTORY_CT4_GREEN:
            case _OSD_FACTORY_CT5_RED:
            case _OSD_FACTORY_CT5_GREEN:
            case _OSD_FACTORY_CT6_RED:
            case _OSD_FACTORY_CT6_GREEN:
            case _OSD_FACTORY_GAIN_GREEN:
            case _OSD_FACTORY_GAIN_RED:
            case _OSD_FACTORY_OFFSET_GREEN:
            case _OSD_FACTORY_OFFSET_RED:
            case _OSD_FACTORY_BG_RED:
            case _OSD_FACTORY_BG_GREEN:
                break;

            default:
                usForRow++;
                break;
        }
    }

    return ROW(usForRow);
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD OsdFactoryGetItemCol(EnumOsdFactoryItem enumOsdFactoryItem)
{
    switch(enumOsdFactoryItem)
    {
        case _OSD_FACTORY_CT1_RED:
        case _OSD_FACTORY_CT2_RED:
        case _OSD_FACTORY_CT3_RED:
        case _OSD_FACTORY_CT4_RED:
        case _OSD_FACTORY_CT5_RED:
        case _OSD_FACTORY_CT6_RED:
        case _OSD_FACTORY_GAIN_RED:
        case _OSD_FACTORY_OFFSET_RED:
        case _OSD_FACTORY_BG_RED:
            return _FACTORY_R_COL;

        case _OSD_FACTORY_CT1_BLUE:
        case _OSD_FACTORY_CT2_BLUE:
        case _OSD_FACTORY_CT3_BLUE:
        case _OSD_FACTORY_CT4_BLUE:
        case _OSD_FACTORY_CT5_BLUE:
        case _OSD_FACTORY_CT6_BLUE:
        case _OSD_FACTORY_GAIN_BLUE:
        case _OSD_FACTORY_OFFSET_BLUE:
        case _OSD_FACTORY_BG_BLUE:
            return _FACTORY_B_COL;

        case _OSD_FACTORY_CT1_GREEN:
        case _OSD_FACTORY_CT2_GREEN:
        case _OSD_FACTORY_CT3_GREEN:
        case _OSD_FACTORY_CT4_GREEN:
        case _OSD_FACTORY_CT5_GREEN:
        case _OSD_FACTORY_CT6_GREEN:
        case _OSD_FACTORY_GAIN_GREEN:
        case _OSD_FACTORY_OFFSET_GREEN:
        case _OSD_FACTORY_BG_GREEN:
            return _FACTORY_G_COL;

        default:
            return _FACTORY_ON_OFF_COL;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdFactoryMenuSubItem(void)
{
    BYTE ucLoop = 0;
    BYTE ucBackupCT = 0;
    WORD usRow = 0;

    OsdFactoryPutString(_FACTORY_MODEL_NAME_ROW, _FACTORY_FUNCTION_COL, _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_MODEL_NAME_FACT], COLOR(_CP_ORANGE, _CP_BG), _ENGLISH);

#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
    // OSD Shows Current FW Version
    OsdFactoryShowNumber(ROW(_FACTORY_MODEL_NAME_ROW), COL(_FACTORY_G_NUM_COL), _CUSTOMER_FW_VERSION, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_ON | _SHOW_3), (_PFONT_FACTORY_PAGE_0), COLOR(_CP_WHITE, _CP_BG));
    OsdFactoryShowNumber(ROW(_FACTORY_MODEL_NAME_ROW), COL(_FACTORY_B_COL), _CUSTOMER_FW_SUB_VERSION, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_ON | _SHOW_3), (_PFONT_FACTORY_PAGE_0), COLOR(_CP_WHITE, _CP_BG));
#endif

    ucBackupCT = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());

    for(ucLoop = 0; ucLoop < _OSD_FACTORY_PAGE1_ITEM_AMOUNT; ucLoop++)
    {
        OsdFactoryItemValueUpdate(OsdFactoryGetItem(ucLoop));
        usRow = (OsdFactoryGetItemRow(OsdFactoryGetItem(ucLoop)));

        if((g_stFactoryOsdItemData.usSubStringIdx != _OSD_TEXT_NULL_FACT) &&
           (g_stFactoryOsdItemData.b3ShowType == _ADJ_BAR_REAL))
        {
            // with Sub item
            if(g_stFactoryOsdItemData.usSubStringIdx == _OSD_TEXT_RED_FACT)
            {
                OsdFactoryMenuString(ROW(usRow), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, g_stFactoryOsdItemData.usStringIdx, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            }
            OsdFactoryMenuString(ROW(usRow), COL(OsdFactoryGetItemCol(OsdFactoryGetItem(ucLoop))), _PFONT_FACTORY_PAGE_0, g_stFactoryOsdItemData.usSubStringIdx, COLOR(_CP_ORANGE, _CP_BG), _ENGLISH);
            OsdFactoryMenuItemValue(ROW(usRow), COL(OsdFactoryGetItemCol(OsdFactoryGetItem(ucLoop)) + 4), _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + ucLoop));
        }
        else
        {
            // without sub item
            OsdFactoryMenuString(ROW(usRow), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, g_stFactoryOsdItemData.usStringIdx, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            OsdFactoryMenuItemValue(ROW(usRow), _FACTORY_ON_OFF_COL, _CP_WHITE, (_PFONT_FACTORY_PAGE_ITEM_1 + ucLoop));
        }
    }

    SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), ucBackupCT);
    RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

    // Panel time
    OsdFactoryMenuString(ROW(OsdFactoryGetItemRow(_OSD_FACTORY_RESET_PANEL_TIME)), COL(_FACTORY_TIME_HOUR_COL), _PFONT_FACTORY_PAGE_0, _OSD_TEXT_HOUR_FACT, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    OsdFactoryMenuString(ROW(OsdFactoryGetItemRow(_OSD_FACTORY_RESET_PANEL_TIME)), COL(_FACTORY_TIME_MIN_COL), _PFONT_FACTORY_PAGE_0, _OSD_TEXT_MIN_FACT, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
    OsdFactoryShowNumber(ROW(OsdFactoryGetItemRow(_OSD_FACTORY_RESET_PANEL_TIME)), COL(_FACTORY_PANEL_TIME_HOUR_NUMBER_COL), GET_PANEL_TIME_HOUR(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), (_PFONT_FACTORY_PAGE_1), COLOR(_CP_WHITE, _CP_BG));
    OsdFactoryShowNumber(ROW(OsdFactoryGetItemRow(_OSD_FACTORY_RESET_PANEL_TIME)), COL(_FACTORY_PANEL_TIME_MIN_NUMBER_COL), GET_PANEL_TIME_MIN(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4), (_PFONT_FACTORY_PAGE_1), COLOR(_CP_WHITE, _CP_BG));

#if(_DP_SUPPORT == _ON)
    OsdFactoryDpDebugMessage();
#endif

#if(_FRC_SUPPORT)
    OsdFactoryFRCMessage();
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdFactoryDpDebugMessage(void)
{
    BYTE ucI = 0;
    EnumDisplayRegion enumDisplayTargetRegion = SysModeGetDisplayTarget();
    EnumInputPort enumTargetPort = SysRegionGetInputPort(enumDisplayTargetRegion);

    ucI = ucI;
    enumTargetPort = enumTargetPort;

    OsdFactoryPutString(ROW(_FACTORY_MENU_DEBUG_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_DP_DEBUG_MSG_FACT], COLOR(_CP_ORANGE, _CP_BG), _ENGLISH);

#if(_DP_SUPPORT == _ON)
    switch(UserCommonDpAuxRxGetLaneCount(enumTargetPort))
    {
        case _DP_LINK_1_LANE:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(1), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_ONE_LANE_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _DP_LINK_2_LANE:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(1), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_TWO_LANE_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _DP_LINK_4_LANE:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(1), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_FOUR_LANE_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        default:
            break;
    }

    switch(UserCommonDpAuxRxGetDpcdLinkRate(enumTargetPort))
    {
        case _DP_LINK_RBR:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(7), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_RBR_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _DP_LINK_HBR:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(7), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_HBR_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _DP_LINK_HBR2:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(7), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_HBR2_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _DP_LINK_HBR3:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(7), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_HBR2_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        default:
            break;
    }
#endif

#if(_COLOR_IP_COLOR_CONVERT == _ON)
    switch(UserCommonColorGetColorSpace(enumTargetPort))
    {
        case _COLOR_SPACE_RGB:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(11), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_RGB_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _COLOR_SPACE_YCBCR422:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(11), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_YCBCR444_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _COLOR_SPACE_YCBCR444:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(11), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_YCBCR422_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _COLOR_SPACE_YCBCR420:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(11), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_YCBCR420_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        default:
            break;
    }

    OsdFactoryShowNumber(ROW(_FACTORY_MENU_DEBUG_ROW + 1), COL(20), (UserCommonColorSpaceGetColorDepth(enumTargetPort)), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_PAGE_0, COLOR(_CP_WHITE, _CP_BG));

    switch(UserCommonColorSpaceGetRGBQuantizationRange(enumTargetPort))
    {
        case _RGB_QUANTIZATION_FULL_RANGE:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(23), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_FULL_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _RGB_QUANTIZATION_LIMIT_RANGE:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(23), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_LIMIT_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _RGB_QUANTIZATION_DEFAULT_RANGE:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 1), COL(23), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_DEFAULT_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;
        case _RGB_QUANTIZATION_RESERVED:
        default:
            break;
    }
#endif

#if(_DP_SUPPORT == _ON)
    for(ucI = _DP_LANE_0; ucI <= _DP_LANE_3; ucI++)
    {
        OsdFactoryPutString(ROW((_FACTORY_MENU_DEBUG_ROW + 2) + ucI), COL(1), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_LANE0_FACT + ucI], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);

        switch(UserCommonDpAuxRxGetLaneVoltageSwingLv(enumTargetPort, ucI))
        {
            case _DP_LINK_VOLTAGE_SWING_LEVEL_0:
                OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 2 + ucI), COL(5), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_SWING_LV0_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _DP_LINK_VOLTAGE_SWING_LEVEL_1:
                OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 2 + ucI), COL(5), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_SWING_LV1_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _DP_LINK_VOLTAGE_SWING_LEVEL_2:
                OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 2 + ucI), COL(5), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_SWING_LV2_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _DP_LINK_VOLTAGE_SWING_LEVEL_3:
                OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 2 + ucI), COL(5), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_SWING_LV3_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            default:
                break;
        }

        switch(UserCommonDpAuxRxGetLanePreEmpLv(enumTargetPort, ucI))
        {
            case _DP_LINK_PREEMPHASIS_LEVEL_0:
                OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 2 + ucI), COL(14), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_P_E_LV0_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _DP_LINK_PREEMPHASIS_LEVEL_1:
                OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 2 + ucI), COL(14), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_P_E_LV1_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _DP_LINK_PREEMPHASIS_LEVEL_2:
                OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 2 + ucI), COL(14), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_P_E_LV2_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            case _DP_LINK_PREEMPHASIS_LEVEL_3:
                OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 2 + ucI), COL(14), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_P_E_LV3_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
                break;
            default:
                break;
        }
    }
#endif
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdFactoryFRCMessage(void)
{
    switch(GET_MEMORY_CONFIG_SELECT())
    {
        case _FRAME_SYNC_MEMORY:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 6), COL(1), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_FRAME_SYNC_MEMORY_FACT], COLOR(_CP_RED, _CP_BG), _ENGLISH);
            break;
        case _FRAME_SYNC_LINE_BUFFER:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 6), COL(1), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_FRAME_SYNC_LINE_BUFFER_FACT], COLOR(_CP_RED, _CP_BG), _ENGLISH);
            break;
        case _FREE_RUN_MEMORY:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 6), COL(1), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_FREE_RUN_MEMORY_FACT], COLOR(_CP_RED, _CP_BG), _ENGLISH);
            break;
        case _MN_FRAME_SYNC_MEMORY:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 6), COL(1), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_MN_FRAME_SYNC_MEMORY_FACT], COLOR(_CP_RED, _CP_BG), _ENGLISH);
            break;
        case _FREE_RUN_NO_INPUT:
        default:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 6), COL(1), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_FREE_RUN_NO_INPUT_FACT], COLOR(_CP_RED, _CP_BG), _ENGLISH);
            break;
    }

    if((g_stMDomainInfo.b1HSD == _TRUE) || (g_stMDomainInfo.b1VSD == _TRUE))
    {
        OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 6), COL(13), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_H_V_SCALER_DOWN_FACT], COLOR(_CP_RED, _CP_BG), _ENGLISH);
    }

#if(_OD_FUNCTION == _ON)
    OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 6), COL(21), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_OD_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);

    switch(UserCommonColorODGetUseParam())
    {
        default:
        case _OD_PARAM_OFF:
            OsdFactoryPutString((_FACTORY_MENU_DEBUG_ROW + 6), COL(23), _PFONT_FACTORY_PAGE_0, tOSD_TABLE_LANGUAGE_TEXT_FACTORY[_OSD_TEXT_OFF_FACT], COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;

        case _OD_PARAM_4_5_BPP:
            OsdFactoryShowNumber(ROW(_FACTORY_MENU_DEBUG_ROW + 6), COL(23), 45, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_PAGE_0, COLOR(_CP_WHITE, _CP_BG));
            break;

        case _OD_PARAM_6_0_BPP:
            OsdFactoryShowNumber(ROW(_FACTORY_MENU_DEBUG_ROW + 6), COL(23), 60, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_PAGE_0, COLOR(_CP_WHITE, _CP_BG));
            break;

        case _OD_PARAM_7_5_BPP:
            OsdFactoryShowNumber(ROW(_FACTORY_MENU_DEBUG_ROW + 6), COL(23), 75, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_PAGE_0, COLOR(_CP_WHITE, _CP_BG));
            break;
    }
#endif
}
