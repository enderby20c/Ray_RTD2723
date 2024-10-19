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

//****************************************************************************
// DEFINITIONS / MACROS of FactoryMode.c
//****************************************************************************
#define _FACTORY_OSD_ROW                            40 // 23
#define _FACTORY_OSD_COL                            33
#define _FACTORY_OSD_WIDTH                          (_FACTORY_OSD_COL * _FONT_WIDTH)

#define _FACTORY_OSD_WINDOW_SIZE_X                  (_FACTORY_OSD_COL * _FONT_WIDTH)
#define _FACTORY_OSD_WINDOW_SIZE_Y                  (_FACTORY_OSD_ROW * _FONT_HEIGHT)

#define _FACTORY_OSD                                0
//--------------------------------------------------
// Definitions of OSD H Position Range
//--------------------------------------------------
#define _FACTORY_OSD_H_POS_MAX                      100
#define _FACTORY_OSD_H_POS_MIN                      0
#define _FACTORY_OSD_H_POS_CENTER                   (((_FACTORY_OSD_H_POS_MAX - _FACTORY_OSD_H_POS_MIN) / 2) + _FACTORY_OSD_H_POS_MIN)
//--------------------------------------------------
// Definitions of OSD V Position Range
//--------------------------------------------------
#define _FACTORY_OSD_V_POS_MAX                      100
#define _FACTORY_OSD_V_POS_MIN                      0
#define _FACTORY_OSD_V_POS_CENTER                   (((_FACTORY_OSD_V_POS_MAX - _FACTORY_OSD_V_POS_CENTER) / 2) + _FACTORY_OSD_V_POS_MIN)

//--------------------------------------------------
// Definitions of OSD Font Pointer
//--------------------------------------------------
typedef enum
{
    _PFONT_FACTORY_PAGE_0,
    _PFONT_FACTORY_PAGE_1,
    _PFONT_FACTORY_PAGE_2,
    _PFONT_FACTORY_PAGE_3,

    _PFONT_FACTORY_PAGE_ITEM_1,
    _PFONT_FACTORY_PAGE_ITEM_2,
    _PFONT_FACTORY_PAGE_ITEM_3,
    _PFONT_FACTORY_PAGE_ITEM_4,
    _PFONT_FACTORY_PAGE_ITEM_5,
    _PFONT_FACTORY_PAGE_ITEM_6,
    _PFONT_FACTORY_PAGE_ITEM_7,
    _PFONT_FACTORY_PAGE_ITEM_8,
    _PFONT_FACTORY_PAGE_ITEM_9,
    _PFONT_FACTORY_PAGE_ITEM_10,
    _PFONT_FACTORY_PAGE_ITEM_11,
    _PFONT_FACTORY_PAGE_ITEM_12,
    _PFONT_FACTORY_PAGE_ITEM_13,
    _PFONT_FACTORY_PAGE_ITEM_14,
    _PFONT_FACTORY_PAGE_ITEM_15,
    _PFONT_FACTORY_PAGE_ITEM_16,
    _PFONT_FACTORY_PAGE_ITEM_17,
    _PFONT_FACTORY_PAGE_ITEM_18,
    _PFONT_FACTORY_PAGE_ITEM_19,
    _PFONT_FACTORY_PAGE_ITEM_20,
    _PFONT_FACTORY_PAGE_ITEM_21,
    _PFONT_FACTORY_PAGE_ITEM_22,
    _PFONT_FACTORY_PAGE_ITEM_23,
    _PFONT_FACTORY_PAGE_ITEM_24,
    _PFONT_FACTORY_PAGE_ITEM_25,
    _PFONT_FACTORY_PAGE_ITEM_26,
    _PFONT_FACTORY_PAGE_ITEM_27,
    _PFONT_FACTORY_PAGE_ITEM_28,
    _PFONT_FACTORY_PAGE_ITEM_29,
    _PFONT_FACTORY_PAGE_ITEM_30,
    _PFONT_FACTORY_PAGE_ITEM_31,
    _PFONT_FACTORY_PAGE_ITEM_32,
    _PFONT_FACTORY_PAGE_ITEM_33,
    _PFONT_FACTORY_PAGE_ITEM_34,
    _PFONT_FACTORY_PAGE_ITEM_35,
    _PFONT_FACTORY_PAGE_ITEM_36,
    _PFONT_FACTORY_PAGE_ITEM_37,
    _PFONT_FACTORY_PAGE_ITEM_38,
    _PFONT_FACTORY_PAGE_ITEM_39,
    _PFONT_FACTORY_PAGE_ITEM_40,
    _PFONT_FACTORY_PAGE_ITEM_41,
    _PFONT_FACTORY_PAGE_ITEM_42,
    _PFONT_FACTORY_PAGE_ITEM_43,
    _PFONT_FACTORY_PAGE_ITEM_44,
    _PFONT_FACTORY_PAGE_ITEM_45,
    _PFONT_FACTORY_PAGE_ITEM_46,
    _PFONT_FACTORY_PAGE_ITEM_47,
    _PFONT_FACTORY_PAGE_ITEM_48,
    _PFONT_FACTORY_PAGE_ITEM_49,
    _PFONT_FACTORY_PAGE_ITEM_END,

}EnumOsdFactoryPFONTr;

#define _FACTORY_ITEM_WORD_GAP                      7
#define _FACTORY_PAGE_0_WORD_START                  0x0001
#define _FACTORY_PAGE_0_WORD_END                    0x01F0

#define _FACTORY_PAGE_1_WORD_START                  0x01F1
#define _FACTORY_PAGE_1_WORD_END                    0x01FF

#define _FACTORY_PAGE_2_WORD_START                  0x0200
#define _FACTORY_PAGE_2_WORD_END                    0x02FF

#define _FACTORY_PAGE_3_WORD_START                  0x0300
#define _FACTORY_PAGE_3_WORD_END                    0x03FF

#define _FACTORY_ITEM_WORD_1_START                  (0x200)
#define _FACTORY_ITEM_WORD_1_END                    (_FACTORY_ITEM_WORD_1_START + _FACTORY_ITEM_WORD_GAP)


#define _FACTORY_MODEL_NAME_ROW                     1
#define _FACTORY_MENU_ROW1                          3

#define _FACTORY_FUNCTION_COL                       1
#define _FACTORY_ON_OFF_COL                         24 // 13
#define _FACTORY_R_COL                              11
#define _FACTORY_G_COL                              18
#define _FACTORY_B_COL                              25
#define _FACTORY_R_NUM_COL                          15
#define _FACTORY_G_NUM_COL                          22
#define _FACTORY_B_NUM_COL                          29

#define _FACTORY_TIME_HOUR_COL                      10
#define _FACTORY_TIME_MIN_COL                       19
#define _FACTORY_PANEL_TIME_HOUR_NUMBER_COL         14
#define _FACTORY_PANEL_TIME_MIN_NUMBER_COL          23
#define _FACTORY_MENU_DEBUG_ROW                     (_FACTORY_MENU_ROW1 + 25)

#define _MAIN_MENU_STATE_END                        _MENU_END

//--------------------------------------------------
// Definitions of Factory OSD Flow
//--------------------------------------------------
typedef enum
{
//-------------------------------------------------------------------------------------------------------------------------------------------------
//  Factory State
//-------------------------------------------------------------------------------------------------------------------------------------------------

    _MENU_FACTORY_MAIN = _MAIN_MENU_STATE_END,
    _MENU_FACTORY_MAIN_ADJ,
    _MENU_FACTORY_OSD_END,
}EnumOsdFactoryMenuPtr;

typedef enum
{
//-------------------------------------------------------------------------------------------------------------------------------------------------
//  Factory State
//-------------------------------------------------------------------------------------------------------------------------------------------------

    _OSD_FACTORY_AUTOCOLOR,
    _OSD_FACTORY_AUTOCOLOR_TYPE,
    _OSD_FACTORY_BURNIN,
    _OSD_FACTORY_RESET_PANEL_TIME,

    _OSD_FACTORY_CT1_RED, _OSD_FACTORY_CT1_GREEN, _OSD_FACTORY_CT1_BLUE,
    _OSD_FACTORY_CT2_RED, _OSD_FACTORY_CT2_GREEN, _OSD_FACTORY_CT2_BLUE,
    _OSD_FACTORY_CT3_RED, _OSD_FACTORY_CT3_GREEN, _OSD_FACTORY_CT3_BLUE,
    _OSD_FACTORY_CT4_RED, _OSD_FACTORY_CT4_GREEN, _OSD_FACTORY_CT4_BLUE,
    _OSD_FACTORY_CT5_RED, _OSD_FACTORY_CT5_GREEN, _OSD_FACTORY_CT5_BLUE,
    _OSD_FACTORY_CT6_RED, _OSD_FACTORY_CT6_GREEN, _OSD_FACTORY_CT6_BLUE,

    _OSD_FACTORY_GAIN_RED, _OSD_FACTORY_GAIN_GREEN, _OSD_FACTORY_GAIN_BLUE,
    _OSD_FACTORY_OFFSET_RED, _OSD_FACTORY_OFFSET_GREEN, _OSD_FACTORY_OFFSET_BLUE,

    _OSD_FACTORY_BG,
    _OSD_FACTORY_BG_RED,
    _OSD_FACTORY_BG_GREEN,
    _OSD_FACTORY_BG_BLUE,
    _OSD_FACTORY_SSC,
    _OSD_FACTORY_SSC_SPEED,
    _OSD_FACTORY_LVDS_DRIVING,
    _OSD_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH,
    _OSD_FACTORY_HOT_PLUG_HDMI_SUPPORT,
    _OSD_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME,
    _OSD_FACTORY_DP_AUX_MODE,
    _OSD_FACTORY_OSD_DOUBLE_SIZE,
    _OSD_FACTORY_COLORIMETRY_SEAMLESS,
    _OSD_FACTORY_DP_AUX_SETTING,
    _OSD_FACTORY_DP_IRQ_TIME,
    _OSD_FACTORY_EXIT,
    _OSD_FACTORY_OSD_END,
}EnumOsdFactoryItem;

#define _FACTORY_RBG_MAX                            255
#define _FACTORY_RBG_MIN                            0
#define _FACTORY_RBG_CENTER                         128

#define _FACTORY_SSC_MAX                            15
#define _FACTORY_SSC_MIN                            0

#define _FACTORY_LVDS_CLOCK_CURRENT_MAX             3
#define _FACTORY_LVDS_CLOCK_CURRENT_MIN             0

#define _FACTORY_LVDS_DATA_CURRENT_MAX              3
#define _FACTORY_LVDS_DATA_CURRENT_MIN              0

#define _FACTORY_PATTERN_MAX                        25
#define _FACTORY_PATTERN_MIN                        0

#define _FACTORY_HOT_PLUG_HDMI_TIME_MAX             7
#define _FACTORY_HOT_PLUG_HDMI_TIME_MIN             1

#define _FACTORY_DP_ADJ_SETTING_MAX                 31
#define _FACTORY_DP_ADJ_SETTING_MIN                 0

#define _FACTORY_DP_IRQ_TIME_MAX                    95
#define _FACTORY_DP_IRQ_TIME_MIN                    55

#define _FACTORY_OSD_PAGE_MAX                       2
#define _FACTORY_OSD_PAGE_MIN                       0

#define _FACTORY_MENU_ITEM_MAX                      18

#include <RTD2020OsdTextTableDefineFactory.h>

typedef enum
{
    _FIRST_REDRAW,
    _REDRAW,
    _MOVE_ITEM,

} EnumFactoryMenuDraw;

//****************************************************************************
// EXTEND VARIABLE DECLARATIONS of FactoryMode.c
//****************************************************************************
extern StructOsdItemDataType g_stFactoryOsdItemData;
extern BYTE code tFONT_FACTORY_GLOBAL[];

//****************************************************************************
// FUNCTION EXTERN of FactoryMode.c
//****************************************************************************
extern bit g_bBgOnOff;
extern BYTE g_ucBgColorR;
extern BYTE g_ucBgColorG;
extern BYTE g_ucBgColorB;
extern BYTE g_ucSSCspeed;
extern BYTE g_ucLVDSclk;

//----------------------------------------------------------------------------------------
// Extern functions from FactoryMode.c
//----------------------------------------------------------------------------------------
// __FACTORY_MODE__
extern void RTDFactoryMenuOperation(void);
extern void RTDFactoryMainMenu(void);
extern void RTDFactoryAutoColorEnter(void);
extern void RTDFactoryPanelUsedTimer(void);
//----------------------------------------------------------------------------------------
// Extern functions from FactoryFunction.c
//----------------------------------------------------------------------------------------
// __FACTORY_FUNCTION__
extern void OsdFactoryFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
extern void OsdFactoryFuncWindowBorder(BYTE ucWin, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
extern void OsdFactoryFuncEnableOsd(void);
extern void OsdFactoryFuncItemProcess(EnumOsdFactoryItem enumOsdFactoryItem);
extern void OsdFactoryFuncSetPosition(BYTE ucType, WORD usX, WORD usY);
extern void OsdFactoryChangColorTemp(void);
extern void OsdFactoryItemValueUpdate(EnumOsdFactoryItem enumOsdFactoryItem);
extern void OsdFactoryHilightWindow(BYTE ucWin, WORD usIndex, BYTE ucColor);
extern void OsdFactoryMenuString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, WORD usString, BYTE ucColor, BYTE ucLanguage);
extern void OsdFactoryPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE *pucArray, BYTE ucColor, BYTE ucLanguage);
extern void OsdFactoryMenuItemValue(BYTE ucRow, BYTE ucCol, BYTE ucColor, BYTE ucPFONTFACTORY);
extern void OsdFactoryMenuItemValueAdj(BYTE ucRow, BYTE ucCol, BYTE ucColor, BYTE ucPFONTFACTORY);
extern EnumOsdFactoryItem OsdFactoryGetItem(WORD usIdx);
extern WORD OsdFactoryGetItemMax(void);
extern WORD OsdFactoryGetItemRow(EnumOsdFactoryItem enumOsdFactoryItem);
extern void OsdFactoryMenuSubItem(void);
extern void OsdFactoryDpDebugMessage(void);
extern void OsdFactoryShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucCPColor);
extern BYTE OsdPropAsciitoFont(BYTE ucASCII);
extern void OsdPropShowFileName(WORD usRow, WORD usCol);
