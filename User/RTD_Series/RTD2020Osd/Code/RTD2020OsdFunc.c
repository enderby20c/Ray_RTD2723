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
// ID Code      : RTD2020OsdFunc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDFUNC__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _CLEAR_DATA                                     _OSD_1_BIT_BYTE0, 0x00, 0x00

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usFontSelectStart;
WORD g_usFontTableStart;
BYTE g_ucOsdWidth;
BYTE g_ucOsdHeight;
BYTE g_ucOsdWidthB;
BYTE g_ucOsdHeightB;
WORD g_usFontPointer0 = _OSD_PAGE_0_START;
WORD g_usFontPointer1 = _OSD_PAGE_1_START;
WORD g_usFontPointer2 = _OSD_PAGE_2_START;
WORD g_usFontPointer3 = _OSD_PAGE_3_START;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
void OsdFuncApplyMapOsdAB(BYTE ucWidthA, BYTE ucHeightA, BYTE ucColorA, BYTE ucWidthB, BYTE ucHeightB, BYTE ucColorB);
#endif

void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
void OsdFuncTransparency(BYTE ucTrans);
void OsdFuncBlending(BYTE ucType);
void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex);
void OsdFuncDisableOsd(void);
void OsdFuncEnableOsd(void);
void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom);
void OsdFuncSet2BitIconOffset(WORD usOffset);
void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);
#if(_SIX_COLOR_SUPPORT == _ON)
void OsdFuncSixColorAdjust(void);
#endif

#if(_COLOR_FORMAT_CONVERT_FUNCTION == _ON)
void OsdFuncColorFormatAdjust(EnumDisplayRegion enumRegion);
#endif

void OsdFuncColorPcmAdjust(void);
BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum, BYTE ucRegion);
#if(_FREEZE_SUPPORT == _ON)
bit OsdFuncCheckFreezeDisableMsg(void);
bit OsdFuncCheckFreezeDisable(void);
void OsdFuncShowOSDAfterClosedFreezeMsg(void);
#endif

void OsdFuncShowSourceMenuCheck(void);
#if(_HDR10_SUPPORT == _ON)
bit OsdFuncHdrRegionCheck(void);
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
BYTE OsdFuncGetHdmiPortVersion(EnumInputPort enumInputPort);
void OsdFuncSetHdmiPortVersion(EnumInputPort enumInputPort, BYTE ucValue);
#endif

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
void OsdFuncMapRotation(EnumOsdRotateType enumOsdRotateType, EnumOsdRotateMapA enumOsdRotateMapA, BYTE ucMapARowSize, EnumOsdRotateMapB enumOsdRotateMapB, BYTE ucMapBRowSize, EnumOsdRotateFontLib enumOsdRotateFontLib);
#endif

void OsdFuncHardwareCompression(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType, bit bTableLocation);
void OsdFuncSetAutoSearchPort(EnumRegionIndex enumRegionIdx);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    BYTE ucI = 0;
    BYTE ucTmp = 17; // Row Height = 18

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucI = ucWidth;
        ucWidth = ucHeight;
        ucHeight = ucI;
        ucTmp = 11;  // Row Height = 12
    }
#endif

    // Row Command
    for(ucI = 0; ucI < ucHeight; ucI++)
    {
        UserCommonOsdCommandAllByte(ucI, 0x80, ucTmp, ucWidth);
    }

    // Row Command end
    UserCommonOsdCommandByte(ucHeight, _OSD_BYTE0, 0x00);

    // Frame Control (set font start address)
    g_usFontSelectStart = ucHeight + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(ucWidth * ucHeight);

    // Font base address must be multiple of 4
    g_usFontTableStart += (((g_usFontTableStart % 4) == 0) ? (0) : (4 - g_usFontTableStart % 4));

    UserCommonOsdSramBaseAddressSet(_OSD_A, 0, g_usFontSelectStart, g_usFontTableStart);

    // Character Command initial
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucTmp = _OSD_1_BIT_BYTE0_ROTATE;  // 18 Pixel
    }
    else
#endif
    {
        ucTmp = _OSD_1_BIT_BYTE0;  // 12 Pixel
    }

    UserCommonOsdCharCommandAllByteSeries(g_usFontSelectStart, ucTmp, 0, ucColor, (WORD)ucWidth * ucHeight);

    // for calculation (unit: word count)
    g_ucOsdWidth = ucWidth;
    g_ucOsdHeight = ucHeight;
    SET_OSD_MAPA_COL_MAX(WIDTH(g_ucOsdWidth));

    UserCommonOsdScalingUpDoubleEn(_OSD_POSITION_GLOBAL_A, GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());
    UserCommonOsdScalingUpDoubleEn(_OSD_POSITION_GLOBAL_B, GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());
}

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncApplyMapOsdAB(BYTE ucWidthA, BYTE ucHeightA, BYTE ucColorA, BYTE ucWidthB, BYTE ucHeightB, BYTE ucColorB)
{
    BYTE ucI = 0;
    BYTE ucTmp = 17; // Row Height = 18
    BYTE ucMapBRowCommandBaseAddr = (ucHeightA + 1);

////////// OSD A Row command
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucI = ucWidthA;
        ucWidthA = ucHeightA;
        ucHeightA = ucI;
        ucTmp = 11;  // Row Height = 12
    }
#endif
    // Row Command
    for(ucI = 0; ucI < ucHeightA; ucI++)
    {
        UserCommonOsdCommandAllByte(ucI, 0x80, ucTmp, ucWidthA);
    }
    // Row Command end
    UserCommonOsdCommandByte(ucHeightA, _OSD_BYTE0, 0x00);


////////// OSD B Row command
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucI = ucWidthB;
        ucWidthB = ucHeightB;
        ucHeightB = ucI;
        ucTmp = 11;  // Row Height = 12
    }
#endif

    // Row Command
    // MapB Row Command address must be multiple of 4
    ucMapBRowCommandBaseAddr += (((ucMapBRowCommandBaseAddr % 4) == 0) ? (0) : (4 - (ucMapBRowCommandBaseAddr % 4)));

    for(ucI = ucMapBRowCommandBaseAddr; ucI < (ucMapBRowCommandBaseAddr + ucHeightB); ucI++)
    {
        UserCommonOsdCommandAllByte(ucI, 0x80, ucTmp, ucWidthB);
    }
    // Row Command end
    UserCommonOsdCommandByte((ucMapBRowCommandBaseAddr + ucHeightB), _OSD_BYTE0, 0x00);

    // Frame Control (set font start address)
    g_usFontSelectStart = (ucMapBRowCommandBaseAddr + ucHeightB) + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(ucWidthA * ucHeightA) + (WORD)(ucWidthB * ucHeightB);
    g_usFontTableStart += (((g_usFontTableStart % 4) == 0) ? (0) : (4 - g_usFontTableStart % 4)); // 6493, Font base address must be multiple of 4

    UserCommonOsdSramBaseAddressSet(_OSD_A, 0, g_usFontSelectStart, g_usFontTableStart);
    UserCommonOsdSramBaseAddressSet(_OSD_B, ucMapBRowCommandBaseAddr, (g_usFontSelectStart + (WORD)(ucWidthA * ucHeightA)), g_usFontTableStart);

    // Character Command initial
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucTmp = _OSD_1_BIT_BYTE0_ROTATE;  // 18 Pixel
    }
    else
#endif
    {
        ucTmp = _OSD_1_BIT_BYTE0;  // 12 Pixel
    }

    UserCommonOsdCharCommandAllByteSeries(g_usFontSelectStart, ucTmp, 0, ucColorA, (WORD)ucWidthA * ucHeightA);
    UserCommonOsdCharCommandAllByteSeries((g_usFontSelectStart + (WORD)(ucWidthA * ucHeightA)), ucTmp, 0, ucColorB, (WORD)ucWidthB * ucHeightB);

    g_ucOsdWidth = ucWidthA;
    g_ucOsdHeight = ucHeightA;
    g_ucOsdWidthB = ucWidthB;
    g_ucOsdHeightB = ucHeightB;
    SET_OSD_MAPA_COL_MAX(WIDTH(g_ucOsdWidth));
    SET_OSD_MAPB_COL_MAX(WIDTH(g_ucOsdWidthB));

    UserCommonOsdScalingUpDoubleEn(_OSD_POSITION_GLOBAL_1, GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());
    UserCommonOsdScalingUpDoubleEn(_OSD_POSITION_GLOBAL_2, GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY)
{
    UserCommonOsdPosition(enumOsdPositionType, usX, usY);
    UserCommonTimerWaitForDDomainEvent(_EVENT_DVS);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncTransparency(BYTE ucTrans)
{
    UserCommonOsdSetTransparency(ucTrans);
}

//--------------------------------------------------
// Description  :
// Input Value  : Blending type1:Only windows blending.
//                Blending type2:All blending.
//                Blending type3:Windows & Character background blending.
// Output Value : None
//--------------------------------------------------
void OsdFuncBlending(BYTE ucType)
{
    UserCommonOsdWindow29SpecialFunction(_OSD_WINDOW_29_FUNCTION_MASK_REGION_TRANSPARENT_ALL);
    UserCommonOsdSetTransparencyType(ucType);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex)
{
    UserCommonOsdWindowDisable(enumWinIndex);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncDisableOsd(void)
{
    EnumOsdWinGradientType enumGradientIdx = 0;

    UserCommonOsdDisableOsd();

    UserCommonOsdMapABFunctionEnable(_OSD_B, _DISABLE);

    for(enumGradientIdx = 0; enumGradientIdx < _OSD_WIN_GRADIENT_END; enumGradientIdx++)
    {
        UserCommonOsdDrawWindowGradientDisableIndex(enumGradientIdx);
    }

    OsdFuncCloseWindow(_OSD_WINDOW_ALL);

#if(_AUDIO_SUPPORT == _ON)
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(UserCommonAudioGetInternalAudioGenEnable(SysRegionGetInputPort(UserInterfaceAudioGetDisplayModeRegion())) == _ENABLE)
    {
        SysAudioInternalGenTestProc(_OFF);
    }
#endif
#endif
    CLR_OSD_CROSSHAIR_SHOW();
    // SET_OSD_GRID_LINE_FUNCTION_ENABLE(_OFF);
    // SET_OSD_GRID_WINDOW_NUMBER(_OSD_WINDOW_2);
    // ScalerOsdDrawGridLine();
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncEnableOsd(void)
{
    UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    UserCommonOsdEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom)
{
    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + g_usFontSelectStart;
    BYTE ucHeightCount = 0;

    ucFontSelectFrom = ucFontSelectFrom;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        BYTE ucWidthCount = 0;

        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdWidth - ucRow - ucHeight) + g_ucOsdWidth * (ucCol + ucWidthCount) + g_usFontSelectStart;
            UserCommonOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucHeight);
        }
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        BYTE ucWidthCount = 0;

        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol - ucWidthCount) * g_ucOsdWidth + ucRow + g_usFontSelectStart;
            UserCommonOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucHeight);
        }
    }
    else
#endif
    {
        for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
        {
            UserCommonOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucWidth);
            usOsdAddr += g_ucOsdWidth;
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSet2BitIconOffset(WORD usOffset)
{
    UserCommonOsd2BitFontOffset(usOffset);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight)
{
    BYTE ucHeightCount = 0;
    BYTE code tucClearTableData[] =
    {
        _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
        _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
        _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
        _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
        _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
        _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA, _CLEAR_DATA,
    };

    for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
    {
        UserCommonOsdSramAddressCount(ucRow + ucHeightCount, ucCol, _OSD_BYTEALL);
        UserCommonOsdBurstWriteDataPortSram(tucClearTableData, (ucWidth * 3), GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_FLASH);
    }
}

#if(_SIX_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSixColorAdjust(void)
{
    UserCommonColorICMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
}
#endif

#if(_COLOR_FORMAT_CONVERT_FUNCTION == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncColorFormatAdjust(EnumDisplayRegion enumRegion)
{
    EnumSourceType enumSourceType = SysRegionGetSourceType(enumRegion);
    EnumInputPort enumInputPort = SysRegionGetInputPort((GET_OSD_SYSTEM_DISPLAY_REGION()));

    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return;
    }

    if(enumSourceType == _SOURCE_VGA)
    {
        if(GET_OSD_COLOR_FORMAT(enumInputPort) == _COLOR_SPACE_RGB)
        {
            SET_VGA_COLOR_FORMAT_STATUS(_COLOR_SPACE_RGB);
        }
        else
        {
            SET_VGA_COLOR_FORMAT_STATUS(_COLOR_SPACE_YPBPR);
        }
    }
    else if(enumSourceType == _SOURCE_DVI)
    {
        if(GET_OSD_COLOR_FORMAT(enumInputPort) == _COLOR_SPACE_RGB)
        {
            SET_DVI_COLOR_FORMAT_STATUS(_COLOR_SPACE_RGB);
        }
        else
        {
            SET_DVI_COLOR_FORMAT_STATUS(_COLOR_SPACE_YPBPR);
        }
    }

#if(_OVERSCAN_SUPPORT == _ON)
    if(GET_OSD_OVERSCAN_STATUS(enumInputPort) == _ON)
    {
        UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
    }
    else
#endif
    {
        EnumDisplayRegion enumStartRegion = _DISPLAY_RGN_1P;
        EnumDisplayRegion enumStopRegion = _DISPLAY_RGN_1P;
        EnumDisplayRegion enumIndexRegion = 0;

        switch(GET_OSD_DISPLAY_MODE())
        {
            case _OSD_DM_1P:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                enumStartRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
                enumStopRegion = _DISPLAY_RGN_EAGLE_SIGHT_SUB;
#endif
                break;

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_2P_TB:
                enumStartRegion = _DISPLAY_RGN_TOP;
                enumStopRegion = _DISPLAY_RGN_BOTTOM;
                break;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_2P_LR:
                if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
                {
                    enumStartRegion = _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT;
                    enumStopRegion = _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT;
                }
                else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
                {
                    enumStartRegion = _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT;
                    enumStopRegion = _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT;
                }
                else
                {
                    enumStartRegion = _DISPLAY_RGN_PBP_LR_EQUAL_LEFT;
                    enumStopRegion = _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT;
                }
                break;
#endif


#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_2P_PIP:
                enumStartRegion = _DISPLAY_RGN_PIP_MAIN;
                enumStopRegion = _DISPLAY_RGN_PIP_SUB;
                break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_3P_FLAG:
                enumStartRegion = _DISPLAY_RGN_FLAG_MAIN;
                enumStopRegion = _DISPLAY_RGN_FLAG_RIGHT;
                break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_3P_SKEW_L:
                enumStartRegion = _DISPLAY_RGN_SKEW_L_MAIN;
                enumStopRegion = _DISPLAY_RGN_SKEW_L_BOTTOM;
                break;

            case _OSD_DM_3P_SKEW_R:
                enumStartRegion = _DISPLAY_RGN_SKEW_R_MAIN;
                enumStopRegion = _DISPLAY_RGN_SKEW_R_BOTTOM;
                break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_3P_SKEW_T:
                enumStartRegion = _DISPLAY_RGN_SKEW_T_MAIN;
                enumStopRegion = _DISPLAY_RGN_SKEW_T_RIGHT;
                break;

            case _OSD_DM_3P_SKEW_B:
                enumStartRegion = _DISPLAY_RGN_SKEW_B_MAIN;
                enumStopRegion = _DISPLAY_RGN_SKEW_B_RIGHT;
                break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_4P:
                enumStartRegion = _DISPLAY_RGN_LT;
                enumStopRegion = _DISPLAY_RGN_RB;
                break;
#endif

            default:
                break;
        }

        for(enumIndexRegion = enumStartRegion; enumIndexRegion <= enumStopRegion; ++enumIndexRegion)
        {
            if(SysRegionGetInputPort(enumIndexRegion) == enumInputPort)
            {
                UserCommonColorColorFormatConvertAdjust(enumIndexRegion, enumInputPort, (UserInterfaceColorGetColorRGBFormat(GET_OSD_SYSTEM_DISPLAY_REGION()) == _RGB_FORMAT_TRUE) ? _COLOR_SPACE_RGB : _COLOR_SPACE_YPBPR, _DB_APPLY_POLLING);
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncColorPcmAdjust(void)
{
#if(_PCM_FUNCTION == _ON)
    EnumSelRegion enumSelRegion = GET_OSD_SYSTEM_SELECT_REGION();
    UserAdjustPCM(enumSelRegion);
#endif  // End of #if(_PCM_FUNCTION == _ON)
}


//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum, BYTE ucRegion)
{
    BYTE ucCheckloop = 0;

    do
    {
        switch(GET_KEYMESSAGE())
        {
            case _RIGHT_KEY_MESSAGE:
                if(ucOsdInputNum >= _OSD_INPUT_AUTO)
                {
                    ucOsdInputNum = _OSD_INPUT_A0;
                }
                else
                {
                    ucOsdInputNum++;
                }
                break;

            case _LEFT_KEY_MESSAGE:
                if(ucOsdInputNum == _OSD_INPUT_A0)
                {
                    ucOsdInputNum = _OSD_INPUT_AUTO;
                }
                else
                {
                    ucOsdInputNum--;
                }
                break;

            default:
                break;
        }

        switch(ucOsdInputNum)
        {
            case _OSD_INPUT_A0:
                ucCheckloop = (_A0_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D0:
                ucCheckloop = (_D0_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D1:
                ucCheckloop = (_D1_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D2:
                ucCheckloop = (_D2_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D3:
                ucCheckloop = (_D3_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D4:
                ucCheckloop = (_D4_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D5:
                ucCheckloop = (_D5_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D6:
                ucCheckloop = (_D6_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D7:

                if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
                {
                    ucCheckloop = 0x00;
                }
                else
                {
                    ucCheckloop = (_D7_INPUT_TYPE - _OPTION_ICON_END);
                }

                break;
            case _OSD_INPUT_D8:

                if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
                {
                    ucCheckloop = 0x00;
                }
                else
                {
                    ucCheckloop = (_D8_INPUT_TYPE - _OPTION_ICON_END);
                }

                break;

            case _OSD_INPUT_AUTO:

                if((ucRegion == _REGION_INDEX_0) &&
                   ((GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                    (GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                    (GET_OSD_4P_INPUT_SOURCE() == _OSD_INPUT_AUTO)))
                {
                    ucCheckloop = 0x00;
                }
                else if((ucRegion == _REGION_INDEX_1) &&
                        ((GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_4P_INPUT_SOURCE() == _OSD_INPUT_AUTO)))
                {
                    ucCheckloop = 0x00;
                }
                else if((ucRegion == _REGION_INDEX_2) &&
                        ((GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_4P_INPUT_SOURCE() == _OSD_INPUT_AUTO)))
                {
                    ucCheckloop = 0x00;
                }
                else if((ucRegion == _REGION_INDEX_3) &&
                        ((GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO)))
                {
                    ucCheckloop = 0x00;
                }
                else
                {
                    return ucOsdInputNum;
                }
                break;
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
            case _OSD_INPUT_D9:
            case _OSD_INPUT_D9_D0:
            case _OSD_INPUT_D9_D1:
            case _OSD_INPUT_D9_D2:
                ucCheckloop = 0x00;
                break;
#endif
            default:
                break;
        }
    }while(ucCheckloop == 0x00); // 0x00=>NO PORT

    return ucOsdInputNum;
}

#if(_FREEZE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit OsdFuncCheckFreezeDisableMsg(void)
{
#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(UserCommonTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG) == _TRUE)
    {
        return _TRUE;
    }
#else
    if(GET_FREEZE_DISABLE_MSG_STATE() == _ON)
    {
        return _TRUE;
    }
#endif
    return _FALSE;
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit OsdFuncCheckFreezeDisable(void)
{
    if(GET_OSD_FREEZE_STATUS() == _OFF)
    {
        return _FALSE;
    }
//Here  need to confirm

    return _FALSE;
}
//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
void OsdFuncShowOSDAfterClosedFreezeMsg(void)
{
    OsdDispMainMenu();
//here need to confirm
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncShowSourceMenuCheck(void)
{
#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if (UserCommonTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING) == _TRUE)
    {
        UserCommonTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
    }
    else if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) ||
            (UserCommonTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING) == _TRUE))
    {
        UserCommonTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
    }
#else
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
        if(GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION)
        {
        }
        else
        {
            UserCommonTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
        }
    }
#endif
}

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : TRUE: support HDR ; FALSE: non-Support HDR
//--------------------------------------------------
bit OsdFuncHdrRegionCheck(void)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        case _OSD_DM_1P:
            return _TRUE;

        case _OSD_DM_2P_LR:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_LR_FULL)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }

        case _OSD_DM_2P_TB:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_TB_FULL)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }

        case _OSD_DM_2P_PIP:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_PIP_FULL)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }
        case _OSD_DM_3P_FLAG:
        case _OSD_DM_3P_SKEW_L:
        case _OSD_DM_3P_SKEW_R:
        case _OSD_DM_3P_SKEW_T:
        case _OSD_DM_3P_SKEW_B:
        case _OSD_DM_4P:
        default:
            return _FALSE;
    }
}
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncGetHdmiPortVersion(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D0_INPUT_PORT:
            return (GET_OSD_D0_HDMI_VER());
#endif

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return (GET_OSD_D1_HDMI_VER());
#endif

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return (GET_OSD_D2_HDMI_VER());
#endif

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return (GET_OSD_D3_HDMI_VER());
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return (GET_OSD_D4_HDMI_VER());
#endif

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return (GET_OSD_D5_HDMI_VER());
#endif

        default:
            return 0;
    }

    return 0;
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSetHdmiPortVersion(EnumInputPort enumInputPort, BYTE ucValue)
{
    ucValue = ucValue;

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            SET_OSD_D0_HDMI_VER(ucValue);
            break;

        case _D1_INPUT_PORT:
            SET_OSD_D1_HDMI_VER(ucValue);
            break;

        case _D2_INPUT_PORT:
            SET_OSD_D2_HDMI_VER(ucValue);
            break;

        case _D3_INPUT_PORT:
            SET_OSD_D3_HDMI_VER(ucValue);
            break;

        case _D4_INPUT_PORT:
            SET_OSD_D4_HDMI_VER(ucValue);
            break;

        case _D5_INPUT_PORT:
            SET_OSD_D5_HDMI_VER(ucValue);
            break;
        default:
            break;
    }
}
#endif

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : None
//--------------------------------------------------
void OsdFuncMapRotation(EnumOsdRotateType enumOsdRotateType, EnumOsdRotateMapA enumOsdRotateMapA, BYTE ucMapARowSize, EnumOsdRotateMapB enumOsdRotateMapB, BYTE ucMapBRowSize, EnumOsdRotateFontLib enumOsdRotateFontLib)
{
    ucMapARowSize = ucMapARowSize;
    ucMapBRowSize = ucMapBRowSize;

#if(_HW_FOSD_HW_FONT_LIB_ROTATE_START_ADDR_SUPPORT == _OFF)
    UserCommonOsdMapRotationAndRotionSize(enumOsdRotateType, enumOsdRotateMapA, enumOsdRotateMapB, enumOsdRotateFontLib, _PANEL_DH_WIDTH, _PANEL_DV_HEIGHT);
#else
    UserCommonOsdMapRotationAndRotionSizeAndStart(enumOsdRotateType,
                                                  enumOsdRotateMapA, enumOsdRotateMapB,
                                                  _OSD_MAP_C_REMAPPING_DISABLE, _OSD_MAP_D_REMAPPING_DISABLE,
                                                  enumOsdRotateFontLib, _PANEL_DH_WIDTH, _PANEL_DV_HEIGHT, UserCommonOsdGetFontBaseAddr() / 4);
#endif
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : None
//--------------------------------------------------
void OsdFuncHardwareCompression(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType, bit bTableLocation)
{
    usFontTableStart = usFontTableStart;
    UserCommonOsdHardwareCompressionFont(pucArray, usVLCTableSize, ucBankNum, usOffset, enumOsdRotateType, bTableLocation);
}
//--------------------------------------------------
// Description  : only support one port can auto search
// Input Value  : region of auto serach port
// Output Value : None
//--------------------------------------------------
void OsdFuncSetAutoSearchPort(EnumRegionIndex enumRegionIdx)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _MULTI_DISPLAY_MAX; ++ucIndex)
    {
        if(ucIndex == enumRegionIdx)
        {
            SET_OSD_INPUT_SOURCE(ucIndex, _OSD_INPUT_AUTO);
        }
        else if(GET_OSD_INPUT_SOURCE(ucIndex) == _OSD_INPUT_AUTO)
        {
            EnumDisplayRegion enumDisplayRegion = SysRegionGetDisplayRegion(ucIndex);
            SET_OSD_INPUT_SOURCE(ucIndex, _OSD_INPUT_A0 + UserCommonNVRamGetSystemRegionPortData(enumDisplayRegion));
        }
    }

    DebugMessageOsd("GET_OSD_1P_INPUT_SOURCE", GET_OSD_1P_INPUT_SOURCE());
    DebugMessageOsd("GET_OSD_2P_INPUT_SOURCE", GET_OSD_2P_INPUT_SOURCE());
    DebugMessageOsd("GET_OSD_3P_INPUT_SOURCE", GET_OSD_3P_INPUT_SOURCE());
    DebugMessageOsd("GET_OSD_4P_INPUT_SOURCE", GET_OSD_4P_INPUT_SOURCE());
}
#endif// #if(_OSD_TYPE == _REALTEK_2020_OSD)
