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
// ID Code      : RTD2020OsdFontProp.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDFONTPROP__

#include "RTD2020UserInclude.h"
#include "RTD2020OsdTextTableBody.h"


#if(_OSD_TYPE == _REALTEK_2020_OSD)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_OSD_INFO_MAP_FONT_BASE_ADDRESS()        (g_usFontTableStart)

#define GET_OSD_INFO_FONT_POINTER_0()               (g_usFontPointer0)
#define SET_OSD_INFO_FONT_POINTER_0(x)              (g_usFontPointer0 = (x))

#define GET_OSD_INFO_FONT_POINTER_1()               (g_usFontPointer1)
#define SET_OSD_INFO_FONT_POINTER_1(x)              (g_usFontPointer1 = (x))

#define GET_OSD_INFO_FONT_POINTER_2()               (g_usFontPointer2)
#define SET_OSD_INFO_FONT_POINTER_2(x)              (g_usFontPointer2 = (x))

#define GET_OSD_INFO_FONT_POINTER_3()               (g_usFontPointer3)
#define SET_OSD_INFO_FONT_POINTER_3(x)              (g_usFontPointer3 = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
WORD code tSTRING_RESOLUTION_TABLE[][6] =
{
    {   _,   _,   _,   _,   _,   _},
    { 240,   _, _4_, _8_, _0_, _i_},
    { 480,   _, _4_, _8_, _0_, _p_},
    { 288,   _, _5_, _7_, _6_, _i_},
    { 576,   _, _5_, _7_, _6_, _p_},
    { 720,   _, _7_, _2_, _0_, _p_},
    { 540, _1_, _0_, _8_, _0_, _i_},
    {1080, _1_, _0_, _8_, _0_, _p_},
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE *g_pucShowNumberAddress;
BYTE g_pucModeInfoData[40];


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
EnumIconInputSource OsdPropGetSourceTypeIcon(EnumStringPort enumStringinput);
BYTE *OsdPropGetSourceTypeIconAddress(EnumStringPort enumStringinput);
void OsdPropGetShowInputPortStringAddress(EnumStringPort enumStringinput);
void OsdPropGetShowHFreqPClkStringAddress(BYTE ucRegionIndex);

void OsdPropGetShowResolutionStringAddress(BYTE ucRegionIndex);
#if(_FREESYNC_SUPPORT == _ON)
void OsdPropShowFreeSyncVFreqRange(WORD usRow, WORD usCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucColor);
#endif

WORD OsdPropGetFontPointer(BYTE ucPointerSelect);
BYTE OsdPropVideoResolution(BYTE ucRegionIndex);
WORD OsdPropSetFontPointer(BYTE ucPointerSelect, WORD usPointer);
void OsdPropFontDataToSram(BYTE ucFptsSelect, BYTE *pucArray, BYTE ucRotateType);

void OsdPropPutString(WORD usRow, WORD usCol, BYTE ucFptsSelect, WORD usString, BYTE ucColor, BYTE ucLanguage);
void OsdPropPutStringCenter(WORD usRow, WORD usCol, BYTE ucWidth, BYTE ucFptsSelect, WORD usString, BYTE ucColor, BYTE ucLanguage);
void OsdPropShowNumber(WORD usRow, WORD usCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
BYTE *OsdPropGetStringTableAddress(WORD usString);
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
void OsdPropShowPercentage(WORD usRow, WORD usCol, BYTE ucPercentage);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : get source icon table type
// Input Value  : enumInputPort: input port
// Output Value : icon type
//--------------------------------------------------
EnumIconInputSource OsdPropGetSourceTypeIcon(EnumStringPort enumStringinput)
{
    // get source icon
    switch(enumStringinput)
    {
        case _STRING_A0_PORT:
            return _A0_INPUT_TYPE;

        case _STRING_D0_PORT:
            return _D0_INPUT_TYPE;

        case _STRING_D1_PORT:
            return _D1_INPUT_TYPE;

        case _STRING_D2_PORT:
            return _D2_INPUT_TYPE;

        case _STRING_D3_PORT:
            return _D3_INPUT_TYPE;

        case _STRING_D4_PORT:
            return _D4_INPUT_TYPE;

        case _STRING_D5_PORT:
            return _D5_INPUT_TYPE;

        case _STRING_D6_PORT:
            return _D6_INPUT_TYPE;

        case _STRING_D7_PORT:
            return _D7_INPUT_TYPE;

        case _STRING_D8_PORT:
            return _D8_INPUT_TYPE;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _STRING_D9_PORT:
        case _STRING_D9_D0_PORT:
        case _STRING_D9_D1_PORT:
        case _STRING_D9_D2_PORT:
            return _D9_INPUT_TYPE;
#endif

        default:
            return _ICON_INPUT_NO_PORT;
    }
}

//--------------------------------------------------
// Description  : get source icon table address
// Input Value  : enumInputPort: input port
// Output Value : icon address
//--------------------------------------------------
BYTE *OsdPropGetSourceTypeIconAddress(EnumStringPort enumStringinput)
{
    switch(OsdPropGetSourceTypeIcon(enumStringinput))
    {
        case _ICON_INPUT_VGA:
            // print "VGA"
            return tsOsdStrVga;

        case _ICON_INPUT_HDMI:
            // print "HDMI"
            return tsOsdStrHdmi;

        case _ICON_INPUT_DP:
            // print "DP"
            return tsOsdStrDp;

        case _ICON_INPUT_NO_PORT:
        default:
            // print "None"
            return tsOsdStrNone;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : enumInputPort: input port
// Output Value : formatted string pointer
//--------------------------------------------------
void OsdPropGetShowInputPortStringAddress(EnumStringPort enumStringinput)
{
    BYTE ucIndex = 0;
    BYTE *pucIconInfo = OsdPropGetSourceTypeIconAddress(enumStringinput);

    // pritn port info (ex: "Dx: ")
    switch(enumStringinput)
    {
        case _STRING_A0_PORT:
            // vga ports
            g_pucModeInfoData[0] = _A_;
            g_pucModeInfoData[1] = _0_;
            break;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _STRING_D9_D0_PORT:
        case _STRING_D9_D1_PORT:
        case _STRING_D9_D2_PORT:
            // PXP_MST Stream port
            if(enumStringinput == _STRING_D9_D0_PORT)
            {
                g_pucModeInfoData[0] = _D_;
                g_pucModeInfoData[1] = _0_;
            }
            else if(enumStringinput == _STRING_D9_D1_PORT)
            {
                g_pucModeInfoData[0] = _D_;
                g_pucModeInfoData[1] = _1_;
            }
            else // if(enumStringinput == _STRING_D9_D2_PORT)
            {
                g_pucModeInfoData[0] = _D_;
                g_pucModeInfoData[1] = _2_;
            }
            g_pucModeInfoData[2] = _LEFT_BRACE_;
            g_pucModeInfoData[3] = _S_;
            g_pucModeInfoData[4] = _t_;
            g_pucModeInfoData[5] = _r_;
            g_pucModeInfoData[6] = _e_;
            g_pucModeInfoData[7] = _a_;
            g_pucModeInfoData[8] = _m_;
            g_pucModeInfoData[9] = _2_;
            g_pucModeInfoData[10] = _RIGHT_BRACE_;
            g_pucModeInfoData[11] = _END_;
            return;
#endif

        default:
            // digital ports
            g_pucModeInfoData[0] = _D_;
            g_pucModeInfoData[1] = _0_ + (enumStringinput - _STRING_D0_PORT);
            break;
    }

    // print ": "
    g_pucModeInfoData[2] = _COLON_;
    g_pucModeInfoData[3] = _;

    // Copy icon info string + string end
    while(pucIconInfo[ucIndex] != _END_)
    {
        g_pucModeInfoData[4 + ucIndex] = pucIconInfo[ucIndex];
        ucIndex++;
    }
    g_pucModeInfoData[4 + ucIndex] = _END_;

    // return g_pucModeInfoData;
}
#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : get source icon table address
// Input Value  : enumInputPort: input port
// Output Value : icon address
//--------------------------------------------------
BYTE *OsdPropGetArcPortAddress(BYTE ucPort)
{
    if(ucPort == _ARC_PORT_LINE_IN)
    {
        return tsOsdStrAnalog;
    }
    switch(OsdPropGetSourceTypeIcon(_STRING_A0_PORT + ucPort))
    {
        case _ICON_INPUT_HDMI20:
        case _ICON_INPUT_HDMI:
            // print "HDMI"
            return tsOsdStrHdmi;

        case _ICON_INPUT_DP:
            // print "DP"
            return tsOsdStrDp;

        case _ICON_INPUT_NO_PORT:
        default:
            // print "None"
            return tsOsdStrNone;
    }
    return tsOsdStrNone;
}

//--------------------------------------------------
// Description  :
// Input Value  : enumInputPort: input port
// Output Value : formatted string pointer
//--------------------------------------------------
void OsdPropGetArcInputPortStringAddress(BYTE ucPort)
{
    BYTE ucIndex = 0;
    BYTE *pucIconInfo = OsdPropGetArcPortAddress(ucPort);
    // skip _ARC_PORT_LINE_IN
    if(ucPort > _ARC_PORT_LINE_IN)
    {
        // digital ports
        g_pucModeInfoData[0] = _D_;
        g_pucModeInfoData[1] = _0_ + (ucPort - 1);
        // print ": "
        g_pucModeInfoData[2] = _COLON_;
        g_pucModeInfoData[3] = _;

        // Copy icon info string + string end
        while(pucIconInfo[ucIndex] != _END_)
        {
            g_pucModeInfoData[4 + ucIndex] = pucIconInfo[ucIndex];
            ucIndex++;
        }
        g_pucModeInfoData[4 + ucIndex] = _END_;
    }
}
#endif
//--------------------------------------------------
// Description  : print H frequency and pixel clock string
// Input Value  : None
// Output Value : formatted string pointer
//--------------------------------------------------
void OsdPropGetShowHFreqPClkStringAddress(BYTE ucRegionIndex)
{
    EnumDisplayRegion enumDisplayRegion = SysRegionGetDisplayRegion(ucRegionIndex);
    WORD usPixelClk = UserCommonSourceGetInputPixelClk(SysRegionGetInputPort(enumDisplayRegion));
    WORD usHfreq = 0;
    BYTE ucDest = 0;
    BYTE ucSrc = 0;
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(enumDisplayRegion, &stTimingInfo);
    usHfreq = stTimingInfo.usHFreq;

    // print "H: "
    ucSrc = 0;
    while(tsOsdStrHfDclk1[ucSrc] != _END_)
    {
        g_pucModeInfoData[ucDest++] = tsOsdStrHfDclk1[ucSrc++];
    }
    g_pucModeInfoData[ucDest++] = _;

    // print H freq in "xxx.x" format
    g_pucModeInfoData[ucDest++] = (usHfreq < 1000) ? _ :
                                  (_0_ + ((usHfreq / 1000) % 10));
    g_pucModeInfoData[ucDest++] = (_0_ + ((usHfreq / 100) % 10));
    g_pucModeInfoData[ucDest++] = (_0_ + ((usHfreq / 10) % 10));
    g_pucModeInfoData[ucDest++] = _DOT_;
    g_pucModeInfoData[ucDest++] = (_0_ + ((usHfreq / 1) % 10));

    // print "KHz, PCLK: "
    ucSrc = 0;
    while(tsOsdStrHfDclk2[ucSrc] != _END_)
    {
        g_pucModeInfoData[ucDest++] = tsOsdStrHfDclk2[ucSrc++];
    }
    g_pucModeInfoData[ucDest++] = _;

    // print pixel clock in in "xxxx.x" format
    g_pucModeInfoData[ucDest++] = (usPixelClk < 10000) ? _ :
                                  (_0_ + ((usPixelClk / 10000) % 10));
    g_pucModeInfoData[ucDest++] = (usPixelClk < 1000) ? _ :
                                  (_0_ + ((usPixelClk / 1000) % 10));
    g_pucModeInfoData[ucDest++] = (_0_ + ((usPixelClk / 100) % 10));
    g_pucModeInfoData[ucDest++] = (_0_ + ((usPixelClk / 10) % 10));
    g_pucModeInfoData[ucDest++] = _DOT_;
    g_pucModeInfoData[ucDest++] = (_0_ + ((usPixelClk / 1) % 10));

    // print "MHz" + string end
    ucSrc = 0;
    while(tsOsdStrHfDclk2[ucSrc] != _END_)
    {
        g_pucModeInfoData[ucDest++] = tsOsdStrHfDclk3[ucSrc++];
    }
    g_pucModeInfoData[ucDest++] = _END_;

    // return g_pucModeInfoData;
}

//--------------------------------------------------
// Description  : return resulution string (ex: 1080p@60.0Hz)
// Input Value  : None
// Output Value : formatted string pointer
//--------------------------------------------------
void OsdPropGetShowResolutionStringAddress(BYTE ucRegionIndex)
{
    BYTE ucResolutionIndex = OsdPropVideoResolution(ucRegionIndex);
    BYTE ucDest = 0;
    BYTE ucSrc = 0;
    EnumDisplayRegion enumRegion = SysRegionGetDisplayRegion(ucRegionIndex);
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(enumRegion, &stTimingInfo);

    if(ucResolutionIndex != 0)
    {
        // print video timing string (Ex: "1080p")
        g_pucModeInfoData[ucDest++] = tSTRING_RESOLUTION_TABLE[ucResolutionIndex][1];
        g_pucModeInfoData[ucDest++] = tSTRING_RESOLUTION_TABLE[ucResolutionIndex][2];
        g_pucModeInfoData[ucDest++] = tSTRING_RESOLUTION_TABLE[ucResolutionIndex][3];
        g_pucModeInfoData[ucDest++] = tSTRING_RESOLUTION_TABLE[ucResolutionIndex][4];
        g_pucModeInfoData[ucDest++] = tSTRING_RESOLUTION_TABLE[ucResolutionIndex][5];
    }
    else
    {
        // print H width (ex: "1920")
        if(stTimingInfo.usHWidth >= 1000)
        {
            g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usHWidth / 1000) % 10);
        }
        g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usHWidth / 100) % 10);
        g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usHWidth / 10) % 10);
        g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usHWidth / 1) % 10);

        // print "x"
        g_pucModeInfoData[ucDest++] = _x_;

        // print V height (ex: "1080")
        if(stTimingInfo.usVHeight >= 1000)
        {
            g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usVHeight / 1000) % 10);
        }
        g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usVHeight / 100) % 10);
        g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usVHeight / 10) % 10);
        g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usVHeight / 1) % 10);
    }

    // print "@"
    g_pucModeInfoData[ucDest++] = _AT_0_;
    g_pucModeInfoData[ucDest++] = _AT_1_;

    // print xxx.x format for V freqeuncy
    if(stTimingInfo.usVFreq >= 1000)
    {
        g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usVFreq / 1000) % 10);
    }
    g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usVFreq / 100) % 10);
    g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usVFreq / 10) % 10);
    g_pucModeInfoData[ucDest++] = _DOT_;
    g_pucModeInfoData[ucDest++] = _0_ + ((stTimingInfo.usVFreq / 1) % 10);

    // print "Hz"
    ucSrc = 0;
    while(tsOsdStrHz[ucSrc] != _END_)
    {
        g_pucModeInfoData[ucDest++] = tsOsdStrHz[ucSrc++];
    }
    g_pucModeInfoData[ucDest++] = _END_;

    // return g_pucModeInfoData;
}

#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : print "FreeSync AAA-BBBHz"
// Input Value  : None
// Output Value : formatted string pointer
//--------------------------------------------------
void OsdPropShowFreeSyncVFreqRange(WORD usRow, WORD usCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucColor)
{
    WORD usMinVFreq = UserCommonFreeSyncGetInfo(SysSourceGetInputPort(), _SPD_INFO_FREESYNC_MIN_VFREQ);
    WORD usMaxVFreq = UserCommonFreeSyncGetInfo(SysSourceGetInputPort(), _SPD_INFO_FREESYNC_MAX_VFREQ);
    BYTE ucDest = 0;
    BYTE ucSrc = 0;

    // Check if V freq is zero; Replace with #define value when zero
    if(usMinVFreq == 0)
    {
        if(SysSourceGetSourceType() == _SOURCE_DP)
        {
            usMinVFreq = _PANEL_DP_FREESYNC_MIN_FRAME_RATE / 10;
        }
        else if(SysSourceGetSourceType() == _SOURCE_HDMI)
        {
            usMinVFreq = _PANEL_HDMI_FREESYNC_MIN_FRAME_RATE / 10;
        }
    }
    if(usMaxVFreq == 0)
    {
        if(SysSourceGetSourceType() == _SOURCE_DP)
        {
            usMaxVFreq = _PANEL_DP_FREESYNC_MAX_FRAME_RATE / 10;
        }
        else if(SysSourceGetSourceType() == _SOURCE_HDMI)
        {
            usMaxVFreq = _PANEL_HDMI_FREESYNC_MAX_FRAME_RATE / 10;
        }
    }

    // print "FreeSync Range "
    ucSrc = 0;
    while(tsOsdStrFreesyncRange[ucSrc] != _END_)
    {
        g_pucModeInfoData[ucDest++] = tsOsdStrFreesyncRange[ucSrc++];
    }
    g_pucModeInfoData[ucDest++] = _;

    // print xxx for V freq. min
    if(usMinVFreq >= 100)
    {
        g_pucModeInfoData[ucDest++] = _0_ + ((usMinVFreq / 100) % 10);
    }
    g_pucModeInfoData[ucDest++] = _0_ + ((usMinVFreq / 10) % 10);
    g_pucModeInfoData[ucDest++] = _0_ + ((usMinVFreq / 1) % 10);

    // print "-"
    g_pucModeInfoData[ucDest++] = _SLINE_;

    // print xxx for V freq. max
    if(usMaxVFreq >= 100)
    {
        g_pucModeInfoData[ucDest++] = _0_ + ((usMaxVFreq / 100) % 10);
    }
    g_pucModeInfoData[ucDest++] = _0_ + ((usMaxVFreq / 10) % 10);
    g_pucModeInfoData[ucDest++] = _0_ + ((usMaxVFreq / 1) % 10);

    // print "Hz" + string end
    ucSrc = 0;
    while(tsOsdStrHz[ucSrc] != _END_)
    {
        g_pucModeInfoData[ucDest++] = tsOsdStrHz[ucSrc++];
    }
    g_pucModeInfoData[ucDest++] = _END_;

    OsdPropPutStringCenter(usRow, usCol, ucWidth, ucFptsSelect, _STRING_FREESYNC_SUPPORT_V_RANGE, ucColor, _ENGLISH);
}
#endif


//--------------------------------------------------
// Description  : Return video timing resolution index
// Input Value  : None
// Output Value : video resloution table index (0: not video timing)
//--------------------------------------------------
BYTE OsdPropVideoResolution(BYTE ucRegionIndex)
{
    EnumDisplayRegion enumRegion = SysRegionGetDisplayRegion(ucRegionIndex);
    EnumInputPort enumInputPort = SysRegionGetInputPort(enumRegion);
    bit bVideoTiming = _FALSE;
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(enumRegion, &stTimingInfo);

    // not video timing if V freq. > 62.0 Hz
    if(stTimingInfo.usVFreq > 620)
    {
        return 0;
    }

    // Detect video timing
    if(stTimingInfo.b1Interlace == _TRUE)
    {
        bVideoTiming = _TRUE;
    }
    else
    {
        switch(SysRegionGetSourceType(enumRegion))
        {
#if(_VGA_SUPPORT == _ON)
            case _SOURCE_VGA:
                if(GET_VGA_COLOR_FORMAT_STATUS() == _COLOR_SPACE_YPBPR)
                {
                    bVideoTiming = _TRUE;
                }
                break;
#endif

#if(_HDMI_SUPPORT == _ON)
            case _SOURCE_DVI:
                if(UserCommonSourceHdcpCheckEnabled(enumInputPort) == _HDCP_NONE)
                {
                    bVideoTiming = _FALSE;
                }
                else
                {
                    bVideoTiming = _TRUE;
                }
                break;
#endif

#if(_HDMI_SUPPORT == _ON)
            case _SOURCE_HDMI:
                if(UserCommonColorGetColorSpaceRGB(UserCommonColorGetColorSpace(enumInputPort)) == _FALSE)
                {
                    bVideoTiming = _TRUE;
                }
                break;
#endif

#if(_DP_SUPPORT == _ON)
            case _SOURCE_DP:
                if(UserCommonColorGetColorSpaceRGB(UserCommonColorGetColorSpace(enumInputPort)) == _FALSE)
                {
                    bVideoTiming = _TRUE;
                }
                break;
#endif

            default:
                break;
        }
    }

    if(bVideoTiming == _TRUE)
    {
        BYTE ucIndex = 1;
        WORD usVHeight = stTimingInfo.usVHeight;

#if(_3DDI_FUNCTION == _ON)
        if(UserCommonColor3DDIEnableDecision(enumRegion, enumInputPort) == _TRUE)
        {
            usVHeight = usVHeight / 2;
        }
#endif

        for(; ucIndex < sizeof(tSTRING_RESOLUTION_TABLE) / sizeof(tSTRING_RESOLUTION_TABLE[0]); ++ucIndex)
        {
            // Search for V height
            if(tSTRING_RESOLUTION_TABLE[ucIndex][0] == usVHeight)
            {
                // Check special case for 848x480
                if((stTimingInfo.usHWidth == 848) &&
                   (usVHeight == 480))
                {
                    return 0;
                }

                // Check special cases for non-interlaced timing
                switch(usVHeight)
                {
                    case 240:
                    case 288:
                    case 540:
                        if(stTimingInfo.b1Interlace == _FALSE)
                        {
                            return 0;
                        }
                        break;
                    default:
                        break;
                }

                // Video timing index found
                return ucIndex;
            }
        }
    }

    return 0;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD OsdPropGetFontPointer(BYTE ucPointerSelect)
{
    switch(ucPointerSelect)
    {
        case _PFONT_PAGE_0:
            return GET_OSD_INFO_FONT_POINTER_0();

        case _PFONT_PAGE_1:
            return GET_OSD_INFO_FONT_POINTER_1();

        case _PFONT_PAGE_2:
            return GET_OSD_INFO_FONT_POINTER_2();

        case _PFONT_PAGE_3:
            return GET_OSD_INFO_FONT_POINTER_3();

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD OsdPropSetFontPointer(BYTE ucPointerSelect, WORD usPointer)
{
    usPointer++;

    switch(ucPointerSelect)
    {
        case _PFONT_PAGE_0:
            if(usPointer > _OSD_PAGE_0_END)
            {
                usPointer = _OSD_PAGE_0_START;
            }
            break;
        case _PFONT_PAGE_1:
            if(usPointer > _OSD_PAGE_1_END)
            {
                usPointer = _OSD_PAGE_1_START;
            }
            break;
        case _PFONT_PAGE_2:
            if(usPointer > _OSD_PAGE_2_END)
            {
                usPointer = _OSD_PAGE_2_START;
            }
            break;
        case _PFONT_PAGE_3:
            if(usPointer > _OSD_PAGE_3_END)
            {
                usPointer = _OSD_PAGE_3_START;
            }
            break;
        default:
            break;
    }

    return usPointer;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropFontDataToSram(BYTE ucFptsSelect, BYTE *pucArray, BYTE ucRotateType)
{
    if(ucFptsSelect == _PFONT_PAGE_0)
    {
        OsdFuncHardwareCompression(pucArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_0()), GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_0() >= _OSD_PAGE_0_END)
        {
            SET_OSD_INFO_FONT_POINTER_0(_OSD_PAGE_0_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_0(GET_OSD_INFO_FONT_POINTER_0() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_1)
    {
        OsdFuncHardwareCompression(pucArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_1()), GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_1() >= _OSD_PAGE_1_END)
        {
            SET_OSD_INFO_FONT_POINTER_1(_OSD_PAGE_1_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_1(GET_OSD_INFO_FONT_POINTER_1() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_2)
    {
        OsdFuncHardwareCompression(pucArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2()), GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _OSD_PAGE_2_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_OSD_PAGE_2_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_3)
    {
        OsdFuncHardwareCompression(pucArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_3()), GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_3() >= _OSD_PAGE_3_END)
        {
            SET_OSD_INFO_FONT_POINTER_3(_OSD_PAGE_3_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_3(GET_OSD_INFO_FONT_POINTER_3() + 1);
        }
    }
}

#if(_HW_FOSD_HW_PUT_STRING_GEN_TYPE == _OSD_HW_PUT_STRING_GEN_1)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropFontDataToSramForHWPutString(BYTE ucFptsSelect, BYTE ucTotalFontCount, WORD *pusFptStart)
{
    switch(ucFptsSelect)
    {
        case _PFONT_PAGE_0:
            if((GET_OSD_INFO_FONT_POINTER_0() + ucTotalFontCount) >= _OSD_PAGE_0_END)
            {
                SET_OSD_INFO_FONT_POINTER_0(_OSD_PAGE_0_START);
                *pusFptStart = _OSD_PAGE_0_START;
            }

            UserCommonOsdAddrSet(_OSD_SRAM_FONT, 0x00, _OSD_BYTEALL, _DISABLE);
            UserCommonOsdSramSetHWPutStringAddress(g_usFontTableStart + GET_OSD_INFO_FONT_POINTER_0() * 9);
            SET_OSD_INFO_FONT_POINTER_0(GET_OSD_INFO_FONT_POINTER_0() + ucTotalFontCount);
            break;
        case _PFONT_PAGE_1:
            if((GET_OSD_INFO_FONT_POINTER_1() + ucTotalFontCount) >= _OSD_PAGE_1_END)
            {
                SET_OSD_INFO_FONT_POINTER_1(_OSD_PAGE_1_START);
                *pusFptStart = _OSD_PAGE_1_START;
            }

            UserCommonOsdAddrSet(_OSD_SRAM_FONT, 0x00, _OSD_BYTEALL, _DISABLE);
            UserCommonOsdSramSetHWPutStringAddress(g_usFontTableStart + GET_OSD_INFO_FONT_POINTER_1() * 9);
            SET_OSD_INFO_FONT_POINTER_1(GET_OSD_INFO_FONT_POINTER_1() + ucTotalFontCount);
            break;
        case _PFONT_PAGE_2:
            if((GET_OSD_INFO_FONT_POINTER_2() + ucTotalFontCount) >= _OSD_PAGE_2_END)
            {
                SET_OSD_INFO_FONT_POINTER_2(_OSD_PAGE_2_START);
                *pusFptStart = _OSD_PAGE_2_START;
            }

            UserCommonOsdAddrSet(_OSD_SRAM_FONT, 0x00, _OSD_BYTEALL, _DISABLE);
            UserCommonOsdSramSetHWPutStringAddress(g_usFontTableStart + GET_OSD_INFO_FONT_POINTER_2() * 9);
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + ucTotalFontCount);
            break;
        case _PFONT_PAGE_3:
            if((GET_OSD_INFO_FONT_POINTER_3() + ucTotalFontCount) >= _OSD_PAGE_3_END)
            {
                SET_OSD_INFO_FONT_POINTER_3(_OSD_PAGE_3_START);
                *pusFptStart = _OSD_PAGE_3_START;
            }

            UserCommonOsdAddrSet(_OSD_SRAM_FONT, 0x00, _OSD_BYTEALL, _DISABLE);
            UserCommonOsdSramSetHWPutStringAddress(g_usFontTableStart + GET_OSD_INFO_FONT_POINTER_3() * 9);
            SET_OSD_INFO_FONT_POINTER_3(GET_OSD_INFO_FONT_POINTER_3() + ucTotalFontCount);
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
void OsdPropHWPutString(WORD usRow, WORD usCol, BYTE ucFptsSelect, WORD usString, BYTE ucColor, BYTE ucLanguage)
{
    BYTE *pucArray = OsdPropGetStringTableAddress(usString);
    bit bCenterFlag = _FALSE;
    bit bNextLineFlag = _FALSE;
    WORD usColBackup = usCol;

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
        WORD usFontPointer = OsdPropGetFontPointer(ucFptsSelect);
        WORD usOffset = 0;
        BYTE ucWidth = 0;
        BYTE ucAlignPixel = 0;
        BYTE ucCurrentFont = 0;
        BYTE ucTemp = 0;
        BYTE ucIdx = 0;
        WORD usTotalPixel = 0;

        bNextLineFlag = _FALSE;
        memset(pData, 0x00, sizeof(pData));

        // calculate totol string width
        while((pucArray[ucElementCount] != _END_) && (pucArray[ucElementCount] != _NEXT_LINE))
        {
            pData[2] = pucArray[ucElementCount];
            switch(pData[2])
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
                ///  if _FONT_SELECT_EXT"N" is defined in XXXOsdTextTableDefine.h, new case should be added, for example
                /// case _FONT_SELECT_EXT3:
                ///    usOffset = _FONT_SELECT_OFFSET3;
                ///    break;
            }

            if(usOffset != 0)
            {
                ucElementCount++;
                pData[2] = pucArray[ucElementCount];
            }

            if((usOffset + pData[2]) < (_GLOBAL_FONT_END_OFFSET + _GLOBAL_FONT_END))
            {
                ucWidth += tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[2] + usOffset];
            }
            else
            {
                if(((ucLanguage + 1) < (WORD)(sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH) / sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH[0]))) &&
                   (tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1] != NULL))
                {
                    ucWidth += tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[2] + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET];
                }
            }
            ucElementCount++;
        }

        // String col size
        // - total pixels / 12 (round up)
        ucTemp = (ucWidth / 12) + (((ucWidth % 12) > 0) ? 1 : 0);

        if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_CENTER)
        {
            // center-aligned
            // add one font if centered width and actual sting width is not both even or both odd
            if((((GET_OSD_INFO_STRING_MODE_LENGTH() % 2) == 0) && ((ucTemp % 2) == 1)) ||
               (((GET_OSD_INFO_STRING_MODE_LENGTH() % 2) == 1) && ((ucTemp % 2) == 0)))
            {
                ucTemp++;
            }
            // total center-aligned pixels - total string pixels / 2
            ucAlignPixel = ((ucTemp * 12) - ucWidth) / 2;
        }
        else if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_RIGHT)
        {
            // right aligned
            // count right-aligned pixels
            ucAlignPixel = (ucTemp * 12) - ucWidth;
        }

        // Record the length (coloumn) of prop string
        usTotalPixel = ucAlignPixel + ucWidth;
        ucColumnLength = (usTotalPixel / 12) + (((usTotalPixel % 12) > 0) ? 1 : 0);

        // left-aligned
        if(ucAlignPixel != 0)
        {
            bCenterFlag = _TRUE;
        }

        // Step 0. Check rotation
        UserCommonOsdFontRotateCtrlAuto(GET_OSD_ROTATE_STATUS(), _ENABLE); // TODO : need to check
        // Step 1. Set hw_put_string_addr;
        OsdPropFontDataToSramForHWPutString(ucFptsSelect, ucColumnLength, &usFontPointer);
        // Step 2. Set hw_put_string_last_font = 0, Set hw_put_string_font_width = 0;
        UserCommonOsdSramSetHWPutStringLastFont(_FALSE, 0);
        // Step 3. Set hw_put_string_enable = 1; // enable put sting function
        UserCommonOsdSramSetHWPutStringEnable(_ENABLE);
        // Step 4. Set hw_put_string_font_sel = 0; // select 1 bit font
        UserCommonOsdSramSetHWPutStringFontSelect(_OSD_1_BIT_FONT);
        // Step 5. Set hw_put_string_apply = 1; // notify HW start to put string
        UserCommonOsdSramSetHWPutStringApply();

        ucElementCount = 0;
        ucTemp = 0;
        while((pucArray[ucElementCount] != _END_) && (pucArray[ucElementCount] != _NEXT_LINE))
        {
            switch(pucArray[ucElementCount])
            {
                case _END_:
                    break;
                default:
                    if(ucTemp == 0)
                    {
                        ucCurrentFont = pucArray[ucElementCount];
                        if(ucCurrentFont == _FONT_BLANK_PIXEL)
                        {
                            ucTemp = pucArray[ucElementCount + 1];
                            ucCurrentFont = _;
                        }
                        if(bCenterFlag == _TRUE)
                        {
                            ucCurrentFont = _;
                        }
                    }
                    else
                    {
                        ucCurrentFont = _;
                    }

                    switch(ucCurrentFont)
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

                        /// if _FONT_SELECT_EXT"N" is defined in XXXOsdTextTableDefine.h, new case should be added, for example
                        /// case _FONT_SELECT_EXT3:
                        ///    usOffset = _FONT_SELECT_OFFSET3;
                        ///    break;
                    }

                    if(usOffset != 0)
                    {
                        ucElementCount++;
                        ucCurrentFont = pucArray[ucElementCount];
                    }

                    if((usOffset + ucCurrentFont) < (_GLOBAL_FONT_END_OFFSET + _GLOBAL_FONT_END))
                    {
                        if(ucTemp == 0)
                        {
                            ucWidth = tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][ucCurrentFont + usOffset];
                            if(bCenterFlag == _TRUE)
                            {
                                ucWidth = ucAlignPixel;
                            }
                        }
                        else
                        {
                            ucWidth = (ucTemp > 12) ? 12 : ucTemp;
                            ucTemp -= ucWidth;
                        }
                    }
                    else
                    {
                        if(ucTemp == 0)
                        {
                            if(((ucLanguage + 1) < (WORD)(sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH) / sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH[0]))) &&
                               (tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1] != NULL))
                            {
                                ucWidth = tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][ucCurrentFont + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET];
                            }
                            else
                            {
                                ucWidth = 0;
                            }

                            if(bCenterFlag == _TRUE)
                            {
                                ucWidth = ucAlignPixel;
                            }
                        }
                        else
                        {
                            ucWidth = (ucTemp > 12) ? 12 : ucTemp;
                            ucTemp -= ucWidth;
                        }
                    }

                    if(ucTemp == 0)
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
            } // end of switch(pucArray[ucElementCount])

            if(((pucArray[ucElementCount] == _END_) || (pucArray[ucElementCount] == _NEXT_LINE)) && ((usTotalPixel % 12) == 0))
            {
                // last font
                // Step n-4. Set hw_put_string_last_font = 1;
                UserCommonOsdSramSetHWPutStringLastFont(_TRUE, ucWidth);
            }
            else
            {
                // Stpe 6. Set hw_put_string_font_width;
                UserCommonOsdSramSetHWPutStringFontWidth(ucWidth);
            }

            for(ucIdx = 0; ucIdx < 9; ucIdx++)
            {
                if(usOffset == _GLOBAL_FONT_END_OFFSET)
                {
                    if(ucCurrentFont >= _GLOBAL_FONT_END)
                    {
                        UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable((ucLanguage + 1), (((ucCurrentFont + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (ucIdx * 3))));
                        UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable((ucLanguage + 1), (((ucCurrentFont + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (ucIdx * 3) + 1)));
                        UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable((ucLanguage + 1), (((ucCurrentFont + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (ucIdx * 3) + 2)));
                    }
                    else
                    {
                        UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable(0, (((ucCurrentFont + usOffset) * 27) + (ucIdx * 3))));
                        UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable(0, (((ucCurrentFont + usOffset) * 27) + (ucIdx * 3) + 1)));
                        UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable(0, (((ucCurrentFont + usOffset) * 27) + (ucIdx * 3) + 2)));
                    }
                }
                else if(usOffset > _GLOBAL_FONT_END_OFFSET)
                {
                    UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable((ucLanguage + 1), (((ucCurrentFont + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (ucIdx * 3))));
                    UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable((ucLanguage + 1), (((ucCurrentFont + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (ucIdx * 3) + 1)));
                    UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable((ucLanguage + 1), (((ucCurrentFont + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (ucIdx * 3) + 2)));
                }
                else// if(usOffset < _GLOBAL_FONT_END_OFFSET)
                {
                    UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable(0, (((ucCurrentFont + usOffset) * 27) + (ucIdx * 3))));
                    UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable(0, (((ucCurrentFont + usOffset) * 27) + (ucIdx * 3) + 1)));
                    UserCommonOsdSramSetHWPutStringFontData(OsdPutStringPropFontTable(0, (((ucCurrentFont + usOffset) * 27) + (ucIdx * 3) + 2)));
                }
            }

            // Only shift for the first word
            bCenterFlag = _FALSE;

            if(((pucArray[ucElementCount] == _END_) || (pucArray[ucElementCount] == _NEXT_LINE)) && ((usTotalPixel % 12) == 0))
            {
                // last font
                // Step n-1. Wait hw_put_string_apply = 0; // when put string finish, HW auto clear to 0
                UserCommonOsdSramSetHWPutStringApplyPollingFinish();
                // Step n. Set hw_put_string_enable = 0; // disable put string function
                UserCommonOsdSramSetHWPutStringEnable(_DISABLE);

                // Step 0. Check rotation
                UserCommonOsdFontRotateCtrlAuto(GET_OSD_ROTATE_STATUS(), _DISABLE);
            }
        } // End of while((pucArray[ucElementCount] != _END_) && (pucArray[ucElementCount] != _NEXT_LINE))

        // Last font
        if((usTotalPixel % 12) != 0)
        {
            ucWidth = 12 - (usTotalPixel % 12);

            // Step n-4. Set hw_put_string_last_font = 1;
            // Stpe 6. Set hw_put_string_font_width;
            UserCommonOsdSramSetHWPutStringLastFont(_TRUE, ucWidth);
            for(ucIdx = 0; ucIdx < 9; ucIdx++)
            {
                UserCommonOsdSramSetHWPutStringFontData(0x00);
                UserCommonOsdSramSetHWPutStringFontData(0x00);
                UserCommonOsdSramSetHWPutStringFontData(0x00);
            }

            // Step n-1. Wait hw_put_string_apply = 0; // when put string finish, HW auto clear to 0
            UserCommonOsdSramSetHWPutStringApplyPollingFinish();
            // Step n. Set hw_put_string_enable = 0; // disable put string function
            UserCommonOsdSramSetHWPutStringEnable(_DISABLE);
            // Step 0. Check rotation
            UserCommonOsdFontRotateCtrlAuto(GET_OSD_ROTATE_STATUS(), _DISABLE);
        }

        if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_CENTER)
        {
            usCol = usColBackup + ((((GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength) / 2) < 0) ? 0 : ((GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength) / 2));
        }
        else if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_RIGHT)
        {
            usCol = usColBackup + (((GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength) < 0) ? 0 : (GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength));
        }

        UserCommonOsdSramAddressCount(usRow, usCol, _OSD_BYTEALL);

        while(ucColumnLength != 0)
        {
            ucColumnLength -= 1;

            // Gen3 OSd support 0-1023 1 bit font
            UserCommonOsdSetDataPortSram(HIBYTE(usFontPointer) | _OSD_MODE_BYTE0);
            UserCommonOsdSetDataPortSram(LOBYTE(usFontPointer));
            UserCommonOsdSetDataPortSram(ucColor);
            usFontPointer += 1;
        }

        if(pucArray[ucElementCount] == _NEXT_LINE)
        {
            // Start the next line from pArray
            pucArray += ucElementCount + 1;
            usRow++;
            bNextLineFlag = _TRUE;
        }
    }
    while(bNextLineFlag == _TRUE);

    CLR_OSD_INFO_STRING_MODE();
    CLR_OSD_INFO_STRING_MODE_LENGTH();
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropPutString(WORD usRow, WORD usCol, BYTE ucFptsSelect, WORD usString, BYTE ucColor, BYTE ucLanguage)
{
    BYTE *pucArray = OsdPropGetStringTableAddress(usString);
    bit bCenterFlag = _FALSE;
    bit bNextLineFlag = _FALSE;
    BYTE pucFontData[27] = {0};
    WORD usColBackup = usCol;

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
        WORD usFontPointer = OsdPropGetFontPointer(ucFptsSelect);

        bNextLineFlag = _FALSE;

        memset(pData, 0x00, sizeof(pData));

        if(GET_OSD_INFO_STRING_MODE() != _PUT_STRING_LEFT)
        {
            WORD usOffset = 0;
            WORD usWidth = 0;

            // calculate totol string width
            while((pucArray[ucElementCount] != _END_) &&
                  (pucArray[ucElementCount] != _NEXT_LINE))
            {
                pData[2] = pucArray[ucElementCount];

                switch(pData[2])
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

                    ///  if _FONT_SELECT_EXT"N" is defined in XXXOsdTextTableDefine.h, new case should be added, for example
                    /// case _FONT_SELECT_EXT3:
                    ///    usOffset = _FONT_SELECT_OFFSET3;
                    ///    break;
                }

                if(usOffset != 0)
                {
                    ucElementCount++;
                    pData[2] = pucArray[ucElementCount];
                }

                if((usOffset + pData[2]) < (_GLOBAL_FONT_END_OFFSET + _GLOBAL_FONT_END))
                {
                    usWidth += tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[2] + usOffset];
                }
                else
                {
                    if(((ucLanguage + 1) < (WORD)(sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH) / sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH[0]))) &&
                       (tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1] != NULL))
                    {
                        usWidth += tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[2] + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET];
                    }
                }

                ucElementCount++;
            }

            // String col size
            // - total pixels / 12 (round up)
            pData[0] = (usWidth / 12) + (((usWidth % 12) > 0) ? 1 : 0);

            if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_CENTER)
            {
                // center-aligned
                // add one font if centered width and actual sting width is not both even or both odd
                if((((GET_OSD_INFO_STRING_MODE_LENGTH() % 2) == 0) && ((pData[0] % 2) == 1)) ||
                   (((GET_OSD_INFO_STRING_MODE_LENGTH() % 2) == 1) && ((pData[0] % 2) == 0)))
                {
                    pData[0]++;
                }

                // total center-aligned pixels - total string pixels / 2
                pData[9] = ((pData[0] * 12) - usWidth) / 2;
            }
            else if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_RIGHT)
            {
                // right aligned
                // count right-aligned pixels
                pData[9] = (pData[0] * 12) - usWidth;
            }

            // left-aligned
            if(pData[9] != 0)
            {
                bCenterFlag = _TRUE;
            }
        }
        pData[0] = 0;
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
                    if(pData[5] == 0)
                    {
                        pData[2] = pucArray[ucElementCount];

                        if(pData[2] == _FONT_BLANK_PIXEL)
                        {
                            pData[5] = pucArray[ucElementCount + 1];

                            pData[2] = _;
                        }

                        if(bCenterFlag == _TRUE)
                        {
                            pData[2] = _;
                        }
                    }
                    else
                    {
                        pData[2] = _;
                    }

                    switch(pData[2])
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

                        /// if _FONT_SELECT_EXT"N" is defined in XXXOsdTextTableDefine.h, new case should be added, for example
                        /// case _FONT_SELECT_EXT3:
                        ///    usOffset = _FONT_SELECT_OFFSET3;
                        ///    break;
                    }

                    if(usOffset != 0)
                    {
                        ucElementCount++;
                        pData[2] = pucArray[ucElementCount];
                    }

                    if((usOffset + pData[2]) < (_GLOBAL_FONT_END_OFFSET + _GLOBAL_FONT_END))
                    {
                        if(pData[5] == 0)
                        {
                            pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[2] + usOffset];

                            if(bCenterFlag == _TRUE)
                            {
                                pData[3] = pData[9];
                            }
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                            pData[5] -= pData[3];
                        }
                    }
                    else
                    {
                        if(pData[5] == 0)
                        {
                            if(((ucLanguage + 1) < (WORD)(sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH) / sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH[0]))) &&
                               (tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1] != NULL))
                            {
                                pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[2] + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET];
                            }
                            else
                            {
                                pData[3] = 0;
                            }

                            if(bCenterFlag == _TRUE)
                            {
                                pData[3] = pData[9];
                            }
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                            pData[5] -= pData[3];
                        }
                    }

                    if(pData[5] == 0)
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

            if(pData[6] == 0)
            {
                pData[6] = pData[3];
            }

            // first bits shift direction: left shift
            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT3);

            // left bits shift direction: right shift
            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~_BIT2));

            // first bits shift and second bits shift
            SCALEROSD_FONT_ROTATE_1_2_BITS_SHIFT_SET(((pData[3] - pData[6]) << 4) | pData[6]);

            pData[8] = ucElementCount;
            pData[7] = pData[6];

            for(pData[0] = 0; pData[0] < 9; pData[0]++)
            {
                // restart from last three bytes
                SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT0);

                if(usOffset == _GLOBAL_FONT_END_OFFSET)
                {
                    if(pData[2] >= _GLOBAL_FONT_END)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                    }
                    else
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + usOffset) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + usOffset) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + usOffset) * 27) + (pData[0] * 3) + 2)));
                    }
                }
                else if(usOffset > _GLOBAL_FONT_END_OFFSET)
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + usOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                }
                else// if(usOffset < _GLOBAL_FONT_END_OFFSET)
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + usOffset) * 27) + (pData[0] * 3))));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + usOffset) * 27) + (pData[0] * 3) + 1)));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + usOffset) * 27) + (pData[0] * 3) + 2)));
                }

                ucElementCount = pData[8];
                pData[6] = pData[7];

                if((pData[6] == 12) ||
                   (pucArray[ucElementCount] == _END_) ||
                   (pucArray[ucElementCount] == _NEXT_LINE))
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                }

                while((pData[6] < 12) &&
                      (pucArray[ucElementCount] != _END_) &&
                      (pucArray[ucElementCount] != _NEXT_LINE))
                {
                    WORD usFontOffset = 0;

                    // third bits shift and left bits shift
                    SCALEROSD_FONT_ROTATE_3_L_BITS_SHIFT_SET((pData[6] << 4) | pData[6]);

                    if(pData[5] == 0)
                    {
                        pData[1] = pucArray[ucElementCount];

                        if(pData[1] == _FONT_BLANK_PIXEL)
                        {
                            pData[5] = pucArray[ucElementCount + 1];

                            pData[1] = _;
                        }
                    }
                    else
                    {
                        pData[1] = _;
                    }

                    if((pData[1] == _FONT_SELECT_EXT1) ||
                       (pData[1] == _FONT_SELECT_EXT2))
                    {
                        usFontOffset = (pData[1] == _FONT_SELECT_EXT1) ? _FONT_SELECT_OFFSET1 : _FONT_SELECT_OFFSET2;
                        ucElementCount++;
                        pData[1] = pucArray[ucElementCount];
                    }
                    else
                    {
                        usFontOffset = 0;
                    }

                    if((usFontOffset + pData[1]) < (_GLOBAL_FONT_END_OFFSET + _GLOBAL_FONT_END))
                    {
                        if(pData[5] == 0)
                        {
                            pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[1] + usFontOffset];
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                        }
                    }
                    else
                    {
                        if(pData[5] == 0)
                        {
                            if(((ucLanguage + 1) < (WORD)(sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH) / sizeof(tOSD_TABLE_LANGUAGE_FONT_WIDTH[0]))) &&
                               (tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1] != NULL))
                            {
                                pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[1] + usFontOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET];
                            }
                            else
                            {
                                pData[3] = 0;
                            }
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                        }
                    }

                    ucElementCount++;
                    pData[6] += pData[3];

                    if(usFontOffset == _GLOBAL_FONT_END_OFFSET)
                    {
                        if(pData[1] >= _GLOBAL_FONT_END)
                        {
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + usFontOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + usFontOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + usFontOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                        }
                        else
                        {
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + usFontOffset) * 27) + (pData[0] * 3))));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + usFontOffset) * 27) + (pData[0] * 3) + 1)));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + usFontOffset) * 27) + (pData[0] * 3) + 2)));
                        }
                    }
                    else if(usFontOffset > _GLOBAL_FONT_END_OFFSET)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + usFontOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + usFontOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + usFontOffset - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                    }
                    else// if(usFontOffset < _GLOBAL_FONT_END_OFFSET)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + usFontOffset) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + usFontOffset) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + usFontOffset) * 27) + (pData[0] * 3) + 2)));
                    }
                }

                pucFontData[pData[0] * 3 + 2] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
                pucFontData[pData[0] * 3 + 1] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
                pucFontData[pData[0] * 3] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            }

            if(pData[6] <= 12)
            {
                pData[6] = 0;
            }
            else
            {
                pData[6] = pData[6] - 12;

                if(ucElementCount >= 1)
                {
                    ucElementCount--;
                }
                if(ucElementCount != 0)
                {
                    pData[1] = pucArray[ucElementCount - 1];

                    if((pData[1] == _FONT_SELECT_EXT1) ||
                       (pData[1] == _FONT_SELECT_EXT2))
                    {
                        ucElementCount--;
                    }
                }
            }

            // Write the pro font data to sram
            OsdPropFontDataToSram(ucFptsSelect, pucFontData, GET_OSD_ROTATE_STATUS());

            // Record the length (coloumn) of prop string
            ucColumnLength++;

            // Only shift for the first word
            bCenterFlag = _FALSE;
        }// End of while(*(pArray + stringcnt) != _END_)

        if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_CENTER)
        {
            usCol = usColBackup + ((((GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength) / 2) < 0) ? 0 : ((GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength) / 2));
        }
        else if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_RIGHT)
        {
            usCol = usColBackup + (((GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength) < 0) ? 0 : (GET_OSD_INFO_STRING_MODE_LENGTH() - ucColumnLength));
        }

        UserCommonOsdSramAddressCount(usRow, usCol, _OSD_BYTEALL);

        while(ucColumnLength != 0)
        {
            ucColumnLength -= 1;

            // Gen3 OSd support 0-1023 1 bit font
            UserCommonOsdSetDataPortSram(HIBYTE(usFontPointer) | _OSD_MODE_BYTE0);
            UserCommonOsdSetDataPortSram(LOBYTE(usFontPointer));
            UserCommonOsdSetDataPortSram(ucColor);

            usFontPointer = OsdPropSetFontPointer(ucFptsSelect, usFontPointer);
        }

        if(pucArray[ucElementCount] == _NEXT_LINE)
        {
            // Start the next line from pArray
            pucArray += ucElementCount + 1;
            usRow++;

            bNextLineFlag = _TRUE;
        }
    }
    while(bNextLineFlag == _TRUE);

    CLR_OSD_INFO_STRING_MODE();
    CLR_OSD_INFO_STRING_MODE_LENGTH();
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropPutStringCenter(WORD usRow, WORD usCol, BYTE ucWidth, BYTE ucFptsSelect, WORD usString, BYTE ucColor, BYTE ucLanguage)
{
    SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
    SET_OSD_INFO_STRING_MODE_LENGTH(ucWidth);

#if(_HW_FOSD_HW_PUT_STRING_GEN_TYPE == _OSD_HW_PUT_STRING_GEN_1)
    // test HW put string
    OsdPropHWPutString(usRow, usCol, ucFptsSelect, usString, ucColor, ucLanguage);
    // OsdPropPutString(usRow, usCol, ucFptsSelect, usString, ucColor, ucLanguage); // Force using old method avoid deadlock
#else
    OsdPropPutString(usRow, usCol, ucFptsSelect, usString, ucColor, ucLanguage);
#endif
}

//--------------------------------------------------
// Description  :
//=====_BIT0:======
//#define _ALIGN_LEFT                                 (0)
//#define _ALIGN_RIGHT                                (1)
//=====_BIT1======
// _FORCE_SHOW_NUMBER_OFF                      (0 << 1)
// _FORCE_SHOW_NUMBER_ON                       (1 << 1)
//=====(_BIT6|_BIT5|_BIT4)=======
//#define _SHOW_1                                     (0 << 4)
//#define _SHOW_2                                     (1 << 4)
//#define _SHOW_3                                     (2 << 4)
//#define _SHOW_4                                     (3 << 4)
//#define _SHOW_5                                     (4 << 4)
//#define _SHOW_6                                     (5 << 4)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropShowNumber(WORD usRow, WORD usCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor)
{
    BYTE ucIndex = 0;
    BYTE ucTemp = 0;
    BYTE pucDataSN[7] = {0};

    pucDataSN[0] = (_0_ + (ulValue / 100000));
    pucDataSN[1] = (_0_ + (ulValue % 100000 / 10000));
    pucDataSN[2] = (_0_ + (ulValue % 10000) / 1000);
    pucDataSN[3] = (_0_ + (ulValue % 1000) / 100);
    pucDataSN[4] = (_0_ + (ulValue % 100) / 10);
    pucDataSN[5] = (_0_ + (ulValue % 10));

    for(ucIndex = 0; ucIndex < 6; ucIndex++)
    {
        if(pucDataSN[ucIndex] != _0_)
        {
            ucIndex = 6 - ucIndex;
            break;
        }
    }

    if((ulValue == 0) && ((bit)(ucPar & _BIT1) == _FALSE))
    {
        ucIndex = 1;// just show "0"
    }

    if((bit)(ucPar & _BIT1) == _TRUE)
    {
        ucIndex = (ucPar & (_BIT4 | _BIT5 | _BIT6)) >> 4;
        ucTemp = ucIndex;
    }
    else
    {
        ucTemp = (ucPar & (_BIT4 | _BIT5 | _BIT6)) >> 4;

        if(ucTemp < ucIndex)
        {
            ucTemp = ucIndex;// replace the number to real
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
            pucDataSN[ulValue] = _; // Space
        }
    }

    pucDataSN[ulValue] = _END_;
    g_pucShowNumberAddress = &pucDataSN[0];
    UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);

    if((ucPar & _BIT0) == _ALIGN_RIGHT)// Align Right
    {
        // ScalerOsdChange1BitColor(ROW(usRow), COL(usCol - ucTemp), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), HEIGHT(1), FG_COLOR(ucColor&0x0F), BG_COLOR(ucColor&0x0F));
        UserCommonOsdSramDataValue(ROW(usRow), COL(usCol - ucTemp), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), _OSD_1_BIT_BYTE0, _OSD_BYTE0);
        UserCommonOsdSramDataValue(ROW(usRow), COL(usCol - ucTemp), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), 0x00, _OSD_BYTE1);
        UserCommonOsdSramDataValue(ROW(usRow), COL(usCol - ucTemp), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), ((FG_COLOR(ucColor & 0x0F) << 4) | BG_COLOR(ucColor & 0x0F)), _OSD_BYTE2);
        OsdPropPutString(usRow, (usCol - ulValue), ucFontPoint, _STRING_SHOW_NUMBER, ucColor, _ENGLISH);
    }
    else
    {
        // ScalerOsdChange1BitColor(ROW(usRow), COL(usCol), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), HEIGHT(1), FG_COLOR(ucColor&0x0F), BG_COLOR(ucColor&0x0F));
        UserCommonOsdSramDataValue(ROW(usRow), COL(usCol), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), _OSD_1_BIT_BYTE0, _OSD_BYTE0);
        UserCommonOsdSramDataValue(ROW(usRow), COL(usCol), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), 0x00, _OSD_BYTE1);
        UserCommonOsdSramDataValue(ROW(usRow), COL(usCol), LENGTH(((ucPar & (_BIT6 | _BIT5 | _BIT4)) >> 4) + 1), ((FG_COLOR(ucColor & 0x0F) << 4) | BG_COLOR(ucColor & 0x0F)), _OSD_BYTE2);
        OsdPropPutString(usRow, usCol, ucFontPoint, _STRING_SHOW_NUMBER, ucColor, _ENGLISH);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *OsdPropGetStringTableAddress(WORD usString)
{
    BYTE *pucArray = tsOsdNull;

    switch(usString)
    {
        case _STRING_MUTIP:
            pucArray = tsOsdMutiP;
            break;
        case _STRING_PICTURE:
            pucArray = tsOsdPicture;
            break;
        case _STRING_DISPLAYFUNCTION:
            pucArray = tsOsdDisplayFunction;
            break;
        case _STRING_COLOR:
            pucArray = tsOsdColor;
            break;
        case _STRING_ADVANCE:
            pucArray = tsOsdAdvance;
            break;
        case _STRING_INPUT:
            pucArray = tsOsdInput;
            break;
        case _STRING_AUDIO:
            pucArray = tsOsdAudio;
            break;
        case _STRING_OTHER:
            pucArray = tsOsdOther;
            break;
        case _STRING_FACTORY:
            pucArray = tsOsdFactory;
            break;
        case _STRING_QUICKLINK:
            pucArray = tsOsdQuickLink;
            break;

        case _STRING_INFORMATION:
            pucArray = tsOsdInformation;
            break;
        case _STRING_DISPLAYMODE:
            pucArray = tsOsdDisplayMode;
            break;
        case _STRING_SELECTREGION:
        case _STRING_EAGLE_SIGHT_SELECTREGION:
            pucArray = tsOsdSelectRegion;
            break;
        case _STRING_ANALOG:
            pucArray = tsOsdAnalog;
            break;

        // display mode
        case _STRING_1P:
            pucArray = tsOsdStr1p;
            break;
        case _STRING_2P_LR:
            pucArray = tsOsdStr2pLr;
            break;
        case _STRING_2P_TB:
            pucArray = tsOsdStr2pTb;
            break;
        case _STRING_2P_PIP:
            pucArray = tsOsdStr2pPip;
            break;
        case _STRING_3P_FLAG:
            pucArray = tsOsdStr3pFlag;
            break;
        case _STRING_3P_SKEW_L:
            pucArray = tsOsdStr3pSkewL;
            break;
        case _STRING_3P_SKEW_R:
            pucArray = tsOsdStr3pSkewR;
            break;
        case _STRING_3P_SKEW_T:
            pucArray = tsOsdStr3pSkewTop;
            break;
        case _STRING_3P_SKEW_B:
            pucArray = tsOsdStr3pSkewBotton;
            break;
        case _STRING_4P:
            pucArray = tsOsdStr4p;
            break;

        // display function
        case _STRING_DISP_ROTATE:
            pucArray = tsOsdDispRotate;
            break;
        case _STRING_DISP_LATENCY:
            pucArray = tsOsdLatency;
            break;
        case _STRING_DISP_LR_RATIO:
            pucArray = tsOsdDispLrRatio;
            break;
        case _STRING_PIP_POSITION:
            pucArray = tsOsdPipPosition;
            break;
        case _STRING_PIP_POSITION_USER:
            pucArray = tsOsdPipPositionUser;
            break;

        case _STRING_PIP_USER_POSITION_H:
            pucArray = tsOsdPipHPosition;
            break;
        case _STRING_PIP_USER_POSITION_V:
            pucArray = tsOsdPipVPosition;
            break;
        case _STRING_PIP_TRANSPARENCY:
            pucArray = tsOsdPipTransparency;
            break;
        case _STRING_PIP_SIZE:
            pucArray = tsOsdPipSize;
            break;
        case _STRING_INPUT_SWAP:
            pucArray = tsOsdInputSwap;
            break;

        case _STRING_2P_LR_L:
            pucArray = tsOsdLeftSide;
            break;
        case _STRING_2P_LR_R:
            pucArray = tsOsdRightSide;
            break;
        case _STRING_2P_LR_FULL:
        case _STRING_2P_TB_FULL:
        case _STRING_2P_PIP_FULL:
        case _STRING_3P_FLAG_FULL:
        case _STRING_3P_SKEW_FULL:
            pucArray = tsOsdFull;
            break;
        case _STRING_2P_TB_T:
            pucArray = tsOsdTopSide;
            break;
        case _STRING_2P_TB_B:
            pucArray = tsOsdBottomSide;
            break;
        case _STRING_2P_PIP_MAIN:
            pucArray = tsOsdMain;
            break;
        case _STRING_2P_PIP_SUB:
            pucArray = tsOsdSub;
            break;

        case _STRING_4P_LT_IN:
        case _STRING_3P_FLAG_MAIN:
        case _STRING_3P_SKEW_MAIN:
            pucArray = tsOsdStr1pIn;
            break;
        case _STRING_4P_LT_OUT:
        case _STRING_3P_FLAG_MAIN_OUT:
        case _STRING_3P_SKEW_MAIN_OUT:
            pucArray = tsOsdStr1pOut;
            break;
        case _STRING_4P_RT_IN:
        case _STRING_3P_FLAG_LEFT:
        case _STRING_3P_SKEW_UP:
            pucArray = tsOsdStr2pIn;
            break;
        case _STRING_4P_RT_OUT:
        case _STRING_3P_FLAG_LEFT_OUT:
        case _STRING_3P_SKEW_UP_OUT:
            pucArray = tsOsdStr2pOut;
            break;

        case _STRING_4P_LB_IN:
        case _STRING_3P_FLAG_RIGHT:
        case _STRING_3P_SKEW_DOWN:
            pucArray = tsOsdStr3pIn;
            break;
        case _STRING_4P_LB_OUT:
        case _STRING_3P_FLAG_RIGHT_OUT:
        case _STRING_3P_SKEW_DOWN_OUT:
            pucArray = tsOsdStr3pOut;
            break;

        case _STRING_4P_RB_IN:
            pucArray = tsOsdStr4pIn;
            break;
        case _STRING_4P_RB_OUT:
            pucArray = tsOsdStr4pOut;
            break;
        case _STRING_4P_FULL:
            pucArray = tsOsdStr4pFull;
            break;

        // picture
        case _STRING_BACKLIGHT:
            pucArray = tsOsdBacklight;
            break;
        case _STRING_BRIGHTNESS:
            pucArray = tsOsdBrightness;
            break;
        case _STRING_CONTRAST:
            pucArray = tsOsdContrast;
            break;
        case _STRING_SHARPNESS:
            pucArray = tsOsdSharpness;
            break;

        // display
        case _STRING_AUTO_ADJUST:
            pucArray = tsOsdAutoAdjust;
            break;
        case _STRING_HPOS:
            pucArray = tsOsdHPosition;
            break;
        case _STRING_VPOS:
            pucArray = tsOsdVPosition;
            break;
        case _STRING_CLOCK:
            pucArray = tsOsdClock;
            break;
        case _STRING_PHASE:
            pucArray = tsOsdPhase;
            break;

        // color
        case _STRING_PANEL_UNIFORMITY:
            pucArray = tsOsdPanelUniformity;
            break;

        case _STRING_GAMMA:
            pucArray = tsOsdGamma;
            break;
        case _STRING_COLOR_TEMP:
            pucArray = tsOsdTemperature;
            break;
        case _STRING_COLOR_TEMP_USER:
            pucArray = tsOsdStrColorTempUser;
            break;
        case _STRING_COLOR_EFFECT:
            pucArray = tsOsdColorEffect;
            break;
        case _STRING_SIX_COLOR:
            pucArray = tsOsdStrSixColor;
            break;
        case _STRING_CHAMELEON:
            pucArray = tsOsdStrChameleon;
            break;
        case _STRING_DEMO:
            pucArray = tsOsdDemo;
            break;
        case _STRING_DEMO_SIDE:
            pucArray = tsOsdDemoColorAdjust;
            break;
        case _STRING_COLOR_FORMAT:
            pucArray = tsOsdColorFormat;
            break;
        case _STRING_PCM:
            pucArray = tsOsdPcm;
            break;
        case _STRING_HUE:
            pucArray = tsOsdHue;
            break;
        case _STRING_SATURATION:
            pucArray = tsOsdSaturation;
            break;
        case _STRING_LIGHTNESS:
            pucArray = tsOsdStrLightness;
            break;

        // advance
        case _STRING_ASPECT_RATIO:
            pucArray = tsOsdAspectRatio;
            break;
        case _STRING_OVER_SCAN:
            pucArray = tsOsdOverScan;
            break;
        case _STRING_OVER_DRIVE:
            pucArray = tsOsdOverDrive;
            break;
        case _STRING_DDCCI:
            pucArray = tsOsdDdcci;
            break;
        case _STRING_ULTRA_VIVID:
            pucArray = tsOsdUltraVivid;
            break;
        case _STRING_DCR:
            pucArray = tsOsdDcr;
            break;
        case _STRING_DP_OPTION:
            pucArray = tsOsdDpOption;
            break;
        case _STRING_DP_MST:
            pucArray = tsOsdDpMst;
            break;
        case _STRING_DP_RESOLUTION:
            pucArray = tsOsdDpResolution;
            break;
        case _STRING_CLONE:
            pucArray = tsOsdClone;
            break;
        case _STRING_MST_TX:
            pucArray = tsOsdMstTx;
            break;
        case _STRING_FREESYNC:
#if(_FREESYNC_II_SUPPORT == _ON)
            pucArray = tsOsdFreeSync2;
#else
            pucArray = tsOsdFreeSync;
#endif // #if(_FREESYNC_II_SUPPORT == _ON)
            break;
        case _STRING_FREEZE:
            pucArray = tsOsdFreeze;
            break;

#if(_USB_HUB_SUPPORT == _ON)
        case _STRING_TYPEC_MODE:
            pucArray = tsOsdTypeCConfig;
            break;
#endif
        case _STRING_DSC:
            pucArray = tsOsdDsc;
            break;

#if(_HDR10_SUPPORT == _ON)
        case _STRING_HDR_MODE:
            pucArray = tsOsdHdr;
            break;
        case _STRING_ULTRAHDR:
            pucArray = tsOsdUltraHdr;
            break;
        case _STRING_DARK_ENHANCE:
            pucArray = tsOsdDarkEnhance;
            break;
        case _STRING_SHARPNESS_ENHANCE:
            pucArray = tsOsdSharpnessEnhance;
            break;
        case _STRING_COLOR_ENHANCE:
            pucArray = tsOsdColorEnhance;
            break;
        case _STRING_LIGHT_ENHANCE:
            pucArray = tsOsdLightEnhance;
            break;
        case _STRING_HDR_CONTRAST:
            pucArray = tsOsdHdrContrast;
            break;
#endif
        case _STRING_HLG_OOTF:
            pucArray = tsOsdStrHlgOotf;
            break;

        case _STRING_LOCAL_DIMMING:
            pucArray = tsOsdLocalDimming;
            break;
        case _STRING_LD_SMOOTHADJ:
            pucArray = tsOsdStrLdSmoothAdj;
            break;
        case _STRING_GLOBAL_DIMMING:
            pucArray = tsOsdGlobalDimming;
            break;
        case _STRING_OWL_SIGHT:
            pucArray = tsOsdStrOwlSight;
            break;
        case _STRING_EAGLE_SIGHT:
            pucArray = tsOsdStrEagleSight;
            break;
        case _STRING_MBR:
            pucArray = tsOsdStrMbr;
            break;
#if(_PIXEL_SHIFT_SUPPORT == _ON)
        case _STRING_PIXEL_SHIFT:
            pucArray = tsOsdPixelShifting;
            break;
#endif

        case _STRING_SINGLE_DP_EDID:
            pucArray = tsOsdSingleDpEdid;
            break;
        case _STRING_DUAL_DP_EDID:
            pucArray = tsOsdDualDpEdid;
            break;

        case _STRING_HDMI_VERSION:
            pucArray = tsOsdHdmiVersion;
            break;

#if(_SDR_TO_HDR_FUNCTION == _ON)
        case _STRING_SDR_TO_HDR:
            pucArray = tsOsdSdrToHdr;
            break;
#endif
        case _STRING_DP_ALPM:
            pucArray = tsOsdStrDpAlpm;
            break;
        case _STRING_DP_ADAPTIVESYNC:
            pucArray = tsOsdStrDpAdaptiveSync;
            break;
        case _STRING_PANEL_REPLAY:
            pucArray = tsOsdStrPanelReplay;
            break;

        // audio
        case _STRING_VOLUME:
            pucArray = tsOsdVolume;
            break;
        case _STRING_MUTE:
            pucArray = tsOsdMute;
            break;
        case _STRING_STAND_ALONG:
            pucArray = tsOsdStandAlone;
            break;
        case _STRING_AUDIO_SOURCE:
            pucArray = tsOsdAudioSource;
            break;
        case _STRING_SOUND_MODE:
            pucArray = tsOsdSoundMode;
            break;
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
        case _STRING_AUDIO_SELF_TEST:
            pucArray = tsOsdAudioSelfTest;
            break;
#endif

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
        case _STRING_TTS_SUPPORT:
            pucArray = tsOsdStrTtsSupport;
            break;
        case _STRING_TTS_TEXT_VOLUME:
            pucArray = tsOsdStrTtsTextVolume;
            break;
        case _STRING_TTS_AUDIO_VOLUME:
            pucArray = tsOsdStrTtsAudioVolume;
            break;
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

        // other
        case _STRING_RESET:
            pucArray = tsOsdReset;
            break;
        case _STRING_MENU_TIME:
            pucArray = tsOsdMenuTime;
            break;
        case _STRING_OSD_HPOS:
            pucArray = tsOsdOsdHPosition;
            break;
        case _STRING_OSD_VPOS:
            pucArray = tsOsdOsdVPosition;
            break;
        case _STRING_LANGUAGE:
            pucArray = tsOsdLanguage;
            break;
        case _STRING_TRANSPARENCY:
            pucArray = tsOsdTransparency;
            break;
        case _STRING_ROTATE:
            pucArray = tsOsdRotate;
            break;
        case _STRING_ON:
            pucArray = tsOsdStrOn;
            break;
        case _STRING_OFF:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_AUDIO_LINE_IN:
            pucArray = tsOsdStrAnalog;
            break;
        case _STRING_AUDIO_DIGITAL_REGION1:
            pucArray = tsOsdStrDigitalRegion0;
            break;
        case _STRING_AUDIO_DIGITAL_REGION2:
            pucArray = tsOsdStrDigitalRegion1;
            break;
        case _STRING_AUDIO_DIGITAL_REGION3:
            pucArray = tsOsdStrDigitalRegion2;
            break;
        case _STRING_AUDIO_DIGITAL_REGION4:
            pucArray = tsOsdStrDigitalRegion3;
            break;
        case _STRING_AS_RATIO_FULL:
            pucArray = tsOsdStrAspectRatioFull;
            break;
        case _STRING_AS_RATIO_16_9:
            pucArray = tsOsdStrAspectRatio16by9;
            break;
        case _STRING_AS_RATIO_4_3:
            pucArray = tsOsdStrAspectRatio4by3;
            break;
        case _STRING_AS_RATIO_5_4:
            pucArray = tsOsdStrAspectRatio5by4;
            break;
        case _STRING_AS_RATIO_ORIGINAL:
            pucArray = tsOsdStrAspectRatioOriginal;
            break;
        case _STRING_AS_RATIO_REDUCE:
            pucArray = tsOsdStrAspectRatioReduce;
            break;
        case _STRING_AS_RATIO_ENLARGE:
            pucArray = tsOsdStrAspectRatioEnlarge;
            break;
        case _STRING_AS_RATIO_USER:
            pucArray = tsOsdStrUser;
            break;
        case _STRING_ULTRA_VIVID_OFF:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_ULTRA_VIVID_H:
            pucArray = tsOsdStrLevelH;
            break;
        case _STRING_ULTRA_VIVID_M:
            pucArray = tsOsdStrLevelM;
            break;
        case _STRING_ULTRA_VIVID_L:
            pucArray = tsOsdStrLevelL;
            break;
        case _STRING_TEMP_9300:
            pucArray = tsOsdStr9300;
            break;
        case _STRING_TEMP_7500:
            pucArray = tsOsdStr7500;
            break;
        case _STRING_TEMP_6500:
            pucArray = tsOsdStr6500;
            break;
        case _STRING_TEMP_5800:
            pucArray = tsOsdStr5800;
            break;
        case _STRING_TEMP_SRGB:
            pucArray = tsOsdStrSrgb;
            break;
        case _STRING_TEMP_USER:
            pucArray = tsOsdStrUser;
            break;
        case _STRING_COLOR_EFF_STD:
            pucArray = tsOsdStrStandard;
            break;
        case _STRING_COLOR_EFF_GAME:
            pucArray = tsOsdStrGame;
            break;
        case _STRING_COLOR_EFF_MOVIE:
            pucArray = tsOsdStrMovie;
            break;
        case _STRING_COLOR_EFF_PHOTO:
            pucArray = tsOsdStrPhoto;
            break;
        case _STRING_COLOR_EFF_VIVID:
            pucArray = tsOsdStrVivid;
            break;
        case _STRING_COLOR_EFF_USER:
            pucArray = tsOsdStrUser;
            break;
        case _STRING_COLOR_DEMO_OFF:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_COLOR_DEMO_TYPE1:
            pucArray = tsOsdStrType1;
            break;
        case _STRING_COLOR_DEMO_TYPE2:
            pucArray = tsOsdStrType2;
            break;
        case _STRING_COLOR_DEMO_TYPE3:
            pucArray = tsOsdStrType3;
            break;
        case _STRING_COLOR_DEMO_TYPE4:
            pucArray = tsOsdStrType4;
            break;
        case _STRING_COLOR_DEMO_TYPE5:
            pucArray = tsOsdStrType5;
            break;
        case _STRING_COLOR_FORMAT_RGB:
            pucArray = tsOsdStrRgb;
            break;
        case _STRING_COLOR_FORMAT_YUV:
            pucArray = tsOsdStrYuv;
            break;
        case _STRING_COLOR_SPACE_YCBCR422:
            pucArray = tsOsdNull;
            break;// need to confirm
        case _STRING_COLOR_SPACE_YCBCR444:
            pucArray = tsOsdNull;
            break;// need to confirm
        case _STRING_COLOR_SPACE_YCBCR420:
            pucArray = tsOsdNull;
            break;// need to confirm
        case _STRING_COLOR_SPACE_Y_ONLY:
            pucArray = tsOsdNull;
            break;// need to confirm
        case _STRING_COLOR_SPACE_RAW:
            pucArray = tsOsdNull;
            break;// need to confirm
        case _STRING_TEMP_USER_R:
            pucArray = tsOsdStrUserR;
            break;
        case _STRING_TEMP_USER_G:
            pucArray = tsOsdStrUserG;
            break;
        case _STRING_TEMP_USER_B:
            pucArray = tsOsdStrUserB;
            break;
        case _STRING_COLOR_PCM_SRGB:
            pucArray = tsOsdStrPcmSrgb;
            break;
        case _STRING_COLOR_PCM_ADOBE_RGB:
            pucArray = tsOsdStrPcmAdobeRgb;
            break;
        case _STRING_COLOR_PCM_USER:
            pucArray = tsOsdStrUser;
            break;
        case _STRING_COLOR_PCM_NACTIVE:
            pucArray = tsOsdStrPcmNative;
            break;
        case _STRING_COLOR_PCM_SOFT_PROFT_1:
            pucArray = tsOsdStrMode1;
            break;
        case _STRING_COLOR_PCM_SOFT_PROFT_2:
            pucArray = tsOsdStrMode2;
            break;
        case _STRING_COLOR_EFF_USER_Y_HUE:
            pucArray = tsOsdStrUserYHue;
            break;
        case _STRING_COLOR_EFF_USER_C_HUE:
            pucArray = tsOsdStrUserCHue;
            break;
        case _STRING_COLOR_EFF_USER_M_HUE:
            pucArray = tsOsdStrUserMHue;
            break;
        case _STRING_COLOR_EFF_USER_R_HUE:
            pucArray = tsOsdStrUserRHue;
            break;
        case _STRING_COLOR_EFF_USER_G_HUE:
            pucArray = tsOsdStrUserGHue;
            break;
        case _STRING_COLOR_EFF_USER_B_HUE:
            pucArray = tsOsdStrUserBHue;
            break;
        case _STRING_COLOR_EFF_USER_Y_SAT:
            pucArray = tsOsdStrUserYSat;
            break;
        case _STRING_COLOR_EFF_USER_C_SAT:
            pucArray = tsOsdStrUserCSat;
            break;
        case _STRING_COLOR_EFF_USER_M_SAT:
            pucArray = tsOsdStrUserMSat;
            break;
        case _STRING_COLOR_EFF_USER_R_SAT:
            pucArray = tsOsdStrUserRSat;
            break;
        case _STRING_COLOR_EFF_USER_G_SAT:
            pucArray = tsOsdStrUserGSat;
            break;
        case _STRING_COLOR_EFF_USER_B_SAT:
            pucArray = tsOsdStrUserBSat;
            break;
        case _STRING_COLOR_EFF_USER_HUE:
            pucArray = tsOsdStrHue;
            break;
        case _STRING_COLOR_EFF_USER_SAT:
            pucArray = tsOsdStrSaturation;
            break;
        case _STRING_MODE1:
            pucArray = tsOsdStrMode1;
            break;
        case _STRING_MODE2:
            pucArray = tsOsdStrMode2;
            break;
        case _STRING_0_DEGREE:
            pucArray = tsOsdStrDegree0;
            break;
#if(_HW_DISPLAY_ROTATION_180_SUPPORT == _ON)
        case _STRING_180_DEGREE:
            pucArray = tsOsdStrDegree180;
            break;
#endif
#if(_HW_DISPLAY_ROTATION_90_SUPPORT == _ON)
        case _STRING_90_DEGREE:
            pucArray = tsOsdStrDegree90;
            break;
#endif
#if(_HW_DISPLAY_ROTATION_270_SUPPORT == _ON)
        case _STRING_270_DEGREE:
            pucArray = tsOsdStrDegree270;
            break;
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _STRING_LR_MIRROR:
            pucArray = tsOsdStrLrMirror;
            break;
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _STRING_UD_MIRROR:
            pucArray = tsOsdStrUdMirror;
            break;
#endif
        case _STRING_DP_1080P:
            pucArray = tsOsdStr1080p;
            break;
        case _STRING_DP_QHD:
            pucArray = tsOsdStrQhd;
            break;
        case _STRING_DP_4K_60HZ:
            pucArray = tsOsdStr4kat60;
            break;
        case _STRING_DP_5K_8K_60HZ:
            pucArray = tsOsdStr8Kat60;
            break;
        case _STRING_DUAL_DP_4K2K_144HZ:
            pucArray = tsOsdStr4kat144;
            break;
        case _STRING_DP_4K2K_240HZ:
            pucArray = tsOsdStr4kat240;
            break;
        case _STRING_DP_5K_144HZ:
            pucArray = tsOsdStr5kat144;
            break;
        case _STRING_DUAL_DP_5K3K_60HZ:
            pucArray = tsOsdStr5Kat60;
            break;
        case _STRING_DUAL_DP_8K4K_60HZ:
            pucArray = tsOsdStr8Kat60;
            break;
        case _STRING_YES:
            pucArray = tsOsdStrYes;
            break;
        case _STRING_NO:
            pucArray = tsOsdStrNo;
            break;
        case _STRING_MST_OFF:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_MST_AUTO:
            pucArray = tsOsdStrAuto;
            break;
        case _STRING_MST_D0:
            pucArray = tsOsdStrD0;
            break;
        case _STRING_MST_D1:
            pucArray = tsOsdStrD1;
            break;
        case _STRING_MST_D2:
            pucArray = tsOsdStrD2;
            break;
        case _STRING_MST_D6:
        case _STRING_CLONE_FIX_D6:
            pucArray = tsOsdStrD6;
            break;
        case _STRING_D0:
            pucArray = tsOsdStrD0;
            break;
        case _STRING_D1:
            pucArray = tsOsdStrD1;
            break;
        case _STRING_D2:
            pucArray = tsOsdStrD2;
            break;
        case _STRING_D9:
            pucArray = tsOsdStrD9;
            break;
        case _STRING_D6:
            pucArray = tsOsdStrD6;
            break;
        case _STRING_HDMI_D0:
            pucArray = tsOsdStrD0;
            break;
        case _STRING_HDMI_D1:
            pucArray = tsOsdStrD1;
            break;
        case _STRING_HDMI_D2:
            pucArray = tsOsdStrD2;
            break;
        case _STRING_HDMI_D3:
            pucArray = tsOsdStrD3;
            break;
        case _STRING_HDMI_D4:
            pucArray = tsOsdStrD4;
            break;
        case _STRING_HDMI_D5:
            pucArray = tsOsdStrD5;
            break;
        case _STRING_1_DOT_1:
            pucArray = tsOsdStr1Dot1;
            break;
        case _STRING_1_DOT_2:
            pucArray = tsOsdStr1Dot2;
            break;
        case _STRING_DP_2_DOT_0:
            pucArray = tsOsdStr2Dot0;
            break;
        case _STRING_DP_1_DOT_4:
            pucArray = tsOsdStr1Dot4;
            break;
        case _STRING_1_DOT_4:
            pucArray = tsOsdStr1Dot4;
            break;
        case _STRING_2_DOT_0:
            pucArray = tsOsdStr2Dot0;
            break;
        case _STRING_2_DOT_1:
            pucArray = tsOsdStr2Dot1;
            break;
        case _STRING_GAMMA_OFF:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_GAMMA_1_DOT_8:
            pucArray = tsOsdStr1Dot8;
            break;
        case _STRING_GAMMA_2_DOT_0:
            pucArray = tsOsdStr2Dot0;
            break;
        case _STRING_GAMMA_2_DOT_2:
            pucArray = tsOsdStr2Dot2;
            break;
        case _STRING_GAMMA_2_DOT_4:
            pucArray = tsOsdStr2Dot4;
            break;
        case _STRING_U3_ON:
            pucArray = tsOsdStrU3On;
            break;
        case _STRING_U3_OFF:
            pucArray = tsOsdStrU3Off;
            break;
        case _STRING_HDR10_MODE_OFF:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_HDR10_MODE_AUTO:
            pucArray = tsOsdStrAuto;
            break;
        case _STRING_HDR10_MODE_FORCE_2084:
            pucArray = tsOsdStrForce2084;
            break;
        case _STRING_HDR10_MODE_AUTO_HLG:
            pucArray = tsOsdStrAutoHdrHlg;
            break;
        case _STRING_HDR10_MODE_FORCE_HLG:
            pucArray = tsOsdStrForceHlg;
            break;
        case _STRING_ENGLISH:
            pucArray = tsOsdStrEnglish;
            break;
        case _STRING_CHINESE_T:
            pucArray = tsOsdStrChineseT;
            break;
        case _STRING_ENABLE:
            pucArray = tsOsdStrEnable;
            break;
        case _STRING_DISABLE:
            pucArray = tsOsdStrDisable;
            break;
        case _STRING_INPUT_SELECT:
            pucArray = tsOsdStrInputSelect;
            break;
        case _STRING_POSITION_LT:
            pucArray = tsOsdStrTopLeft;
            break;
        case _STRING_POSITION_RT:
            pucArray = tsOsdStrTopRight;
            break;
        case _STRING_POSITION_LD:
            pucArray = tsOsdStrBottomLeft;
            break;
        case _STRING_POSITION_RD:
            pucArray = tsOsdStrBottomRight;
            break;
        case _STRING_POSITION_CENTER:
            pucArray = tsOsdStrCenter;
            break;
        case _STRING_POSITION_USER:
            pucArray = tsOsdStrUser;
            break;
        case _STRING_BORDER_WIDTH:
            pucArray = tsOsdBorderWidth;
            break;
        case _STRING_BORDER_COLOR:
            pucArray = tsOsdBorderColor;
            break;
        case _STRING_OSD_0_DEGREE:
            pucArray = tsOsdStrDegree0;
            break;
        case _STRING_OSD_90_DEGREE:
            pucArray = tsOsdStrDegree90;
            break;
        case _STRING_OSD_180_DEGREE:
            pucArray = tsOsdStrDegree180;
            break;
        case _STRING_OSD_270_DEGREE:
            pucArray = tsOsdStrDegree270;
            break;
        case _STRING_DSC_NONE:
        case _STRING_CLONE_FIX_OFF:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_DSC_D0:
        case _STRING_CLONE_FIX_D0:
            pucArray = tsOsdStrD0;
            break;
        case _STRING_DSC_D1:
        case _STRING_CLONE_FIX_D1:
            pucArray = tsOsdStrD1;
            break;
        case _STRING_DSC_D2:
        case _STRING_CLONE_FIX_D2:
            pucArray = tsOsdStrD2;
            break;
        case _STRING_DSC_D3:
        case _STRING_CLONE_FIX_D3:
            pucArray = tsOsdStrD3;
            break;
        case _STRING_DSC_D4:
        case _STRING_CLONE_FIX_D4:
            pucArray = tsOsdStrD4;
            break;
        case _STRING_DSC_D5:
        case _STRING_CLONE_FIX_D5:
            pucArray = tsOsdStrD5;
            break;
        case _STRING_CLONE_FIX_A0:
            pucArray = tsOsdStrVga;
            break;
        case _STRING_DSC_AUTO:
            pucArray = tsOsdStrAuto;
            break;
        case _STRING_DSC_OFF:
            pucArray = tsOsdStrOff;
            break;

        case _STRING_EAGLE_SIGHT_ONOFF:
            pucArray = tsOsdStrEagleSight;
            break;

        case _STRING_EAGLE_SIGHT_TRANSPARENT:
            pucArray = tsOsdStrEsTransparency;
            break;
        case _STRING_EAGLE_SIGHT_ZOOM:
            pucArray = tsOsdStrEsZoom;
            break;
        case _STRING_EAGLE_SIGHT_CAP_POSITION:
            pucArray = tsOsdCapturePosition;
            break;
        case _STRING_EAGLE_SIGHT_DISP_POSITION:
            pucArray = tsOsdDisplayPosition;
            break;
        case _STRING_EAGLE_SIGHT_BORDER:
            pucArray = tsOsdBorderWidth;
            break;
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
        case _STRING_EAGLE_SIGHT_CIRCLEWIN:
            pucArray = tsOsdCircleWindow;
            break;
#endif
        case _STRING_1_5_X:
            pucArray = tsOsdStrx1p5;
            break;
        case _STRING_2_0_X:
            pucArray = tsOsdStrx2;
            break;
        case _STRING_3_0_X:
            pucArray = tsOsdStrx3;
            break;
        case _STRING_4_0_X:
            pucArray = tsOsdStrx4;
            break;
        case _STRING_HLG_STANDARD:
            pucArray = tsOsdStrStandard;
            break;
        case _STRING_HLG_USER1:
            pucArray = tsOsdStrUserMode1;
            break;
        case _STRING_HLG_USER2:
            pucArray = tsOsdStrUserMode2;
            break;
        case _STRING_HLG_USER3:
            pucArray = tsOsdStrUserMode3;
            break;
        case _STRING_MBR_MODE:
            pucArray = tsOsdStrMbrMode;
            break;
        case _STRING_MBR_OFF:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_MBR_DUTY:
            pucArray = tsOsdStrMbrDuty;
            break;
        case _STRING_MBR_POSITION:
            pucArray = tsOsdStrMbrPosition;
            break;
        case _STRING_MBR_USERMODE:
            pucArray = tsOsdStrMbrUser;
            break;
        case _STRING_MBR_RTK_ADV:
            pucArray = tsOsdStrMbrRtkAdv;
            break;


        // information
        case _STRING_SHOW_NUMBER:
            pucArray = g_pucShowNumberAddress;
            break;
        case _STRING_HFREQPCLK_0:
        case _STRING_HFREQPCLK_1:
        case _STRING_HFREQPCLK_2:
        case _STRING_HFREQPCLK_3:
            OsdPropGetShowHFreqPClkStringAddress(usString - _STRING_HFREQPCLK_0);
            pucArray = g_pucModeInfoData;
            break;

        case _STRING_VGA_USER_MODE:
            pucArray = tsOsdVgaUserMode;
            break;
        case _STRING_VGA_PRESET_MODE:
            pucArray = tsOsdVgaPresetMode;
            break;

        case _STRING_HDCP_NONE:
            pucArray = tsOsdStrHdcpDisable;
            break;
        case _STRING_HDCP_14:
            pucArray = tsOsdStrHdcp14Sink;
            break;
        case _STRING_HDCP_22:
            pucArray = tsOsdStrHdcp22Sink;
            break;
        case _STRING_HDCP_14_REPEATER:
            pucArray = tsOsdStrHdcp14Repeater;
            break;
        case _STRING_HDCP_22_REPEATER:
            pucArray = tsOsdStrHdcp22Repeater;
            break;
        case _STRING_SDR:
            pucArray = tsOsdStrSdr;
            break;
        case _STRING_HLG:
            pucArray = tsOsdStrHlg;
            break;
        case _STRING_HDR_NOTM:
            pucArray = tsOsdStrHdrNotm;
            break;
        case _STRING_SBTM:
            pucArray = tsOsdStrSbtm;
            break;
        // Input Source
        case _STRING_SOURCE_1P:
            pucArray = tsOsdStr1p;
            break;
        case _STRING_SOURCE_2P:
            pucArray = tsOsdStr2p;
            break;
        case _STRING_SOURCE_3P:
            pucArray = tsOsdStr3p;
            break;
        case _STRING_SOURCE_4P:
            pucArray = tsOsdStr4p;
            break;

        // Adjust message
        case _STRING_PLEASE_WAIT:
            pucArray = tsOsdPleaseWait;
            break;

        case _STRING_NO_SIGNAL:
            pucArray = tsOsdNoSignal;
            break;

        case _STRING_NO_CABLE:
            pucArray = tsOsdNoCable;
            break;

        case _STRING_NO_SUPPORT:
            pucArray = tsOsdNoSupport;
            break;

        case _STRING_GO_TO_POWER_SAVING_MODE:
            pucArray = tsOsdGoToPowerSaving;
            break;

        case _STRING_NOW_RESOLUTION_0:
        case _STRING_NOW_RESOLUTION_1:
        case _STRING_NOW_RESOLUTION_2:
        case _STRING_NOW_RESOLUTION_3:
            OsdPropGetShowResolutionStringAddress(usString - _STRING_NOW_RESOLUTION_0);
            pucArray = g_pucModeInfoData;
            break;

        case _STRING_AUTO_COLOR:
            pucArray = tsOsdAutoColor;
            break;

        case _STRING_AUTO_SELECT:
            pucArray = tsOsdAutoSelect;
            break;

        case _STRING_PASS:
            pucArray = tsOsdPass;
            break;

        case _STRING_FAIL:
            pucArray = tsOsdFail;
            break;

        case _STRING_2P:
            pucArray = tsOsdStr2p;
            break;

        case _STRING_3P:
            pucArray = tsOsdStr3p;
            break;

        case _STRING_A0_PORT:
        case _STRING_D0_PORT:
        case _STRING_D1_PORT:
        case _STRING_D2_PORT:
        case _STRING_D3_PORT:
        case _STRING_D4_PORT:
        case _STRING_D5_PORT:
        case _STRING_D6_PORT:
        case _STRING_D7_PORT:
        case _STRING_D8_PORT:
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _STRING_D9_PORT:
        case _STRING_D9_D0_PORT:
        case _STRING_D9_D1_PORT:
        case _STRING_D9_D2_PORT:
#endif
            OsdPropGetShowInputPortStringAddress(usString);
            pucArray = g_pucModeInfoData;
            break;

        case _STRING_AUTOSELECT_PORT:
            pucArray = tsOsdAutoSelect;
            break;
#if(_FREESYNC_SUPPORT == _ON)
        case _STRING_FREESYNC_SUPPORT_V_RANGE:
            pucArray = g_pucModeInfoData;// OsdPropGetShowFreeSyncVFreqRangeStringAddress();
            break;
#endif
        case _STRING_DRR_STATUS:
            pucArray = g_pucModeInfoData;
            break;

        case _STRING_ENTER:
            pucArray = tsOsdStrEnter;
            break;
        case _STRING_EXIT_HOTKEY:
            pucArray = tsOsdHotkeyItem;
            break;
        case _STRING_INSIDE:
            pucArray = tsOsdStrInside;
            break;
        case _STRING_OUTSIDE:
            pucArray = tsOsdStrOutside;
            break;
        case _STRING_HUB_SWITCH:
            pucArray = tsOsdStrHubSwitch;
            break;
        case _STRING_USB_AUTO:
            pucArray = tsOsdStrAuto;
            break;
        case _STRING_USB_D0:
            pucArray = tsOsdStrD0;
            break;
        case _STRING_USB_D1:
            pucArray = tsOsdStrD1;
            break;
        case _STRING_USB_TYPEB:
            pucArray = tsOsdStrTypeB;
            break;

        case _STRING_OWLSIGHT_OFF:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_OWLSIGHT_L:
            pucArray = tsOsdStrLevelL;
            break;
        case _STRING_OWLSIGHT_M:
            pucArray = tsOsdStrLevelM;
            break;
        case _STRING_OWLSIGHT_H:
            pucArray = tsOsdStrLevelH;
            break;
        case _STRING_OWLSIGHT_USER:
            pucArray = tsOsdStrOwlSightUser;
            break;
        case _STRING_OWLSIGHT_BLENDING:
            pucArray = tsOsdDarkEnhance;
            break;
        case _STRING_OWLSIGHT_DIFFGAIN:
            pucArray = tsOsdSharpnessEnhance;
            break;
#if(_DM_FUNCTION == _ON)
        case _STRING_DVISION_VISION:
            pucArray = tsOsdStrDVisionVision;
            break;
        case _STRING_DVISION:
            pucArray = tsOsdStrDVision;
            break;
        case _STRING_DVISION_PICTURE:
            pucArray = tsOsdStrPictureMode;
            break;
        case _STRING_DVISION_BACKLIGHT:
            pucArray = tsOsdBacklight;
            break;
        case _STRING_DVISION_BRIGHTNESS:
            pucArray = tsOsdBrightness;
            break;
        case _STRING_DVISION_CONTRAST:
            pucArray = tsOsdContrast;
            break;
        case _STRING_DVISION_SATURATION:
            pucArray = tsOsdSaturation;
            break;
        case _STRING_DVISION_RESET:
            pucArray = tsOsdStrColorReset;
            break;
        case _STRING_DVISION_DARK:
            pucArray = tsOsdStrDarkMode;
            break;
        case _STRING_DVISION_BRIGHT:
            pucArray = tsOsdStrBrightMode;
            break;
        case _STRING_DVISION_GAME:
            pucArray = tsOsdStrGameMode;
            break;
        case _STRING_DVISION_NOTIFICATION:
            pucArray = tsOsdStrDmNotice;
            break;
        case _STRING_DVISION_USER:
            pucArray = tsOsdStrUser;
            break;
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
        case _STRING_AUDIO_ARC_PORT_LINE_IN:
            pucArray = tsOsdStrAnalog;
            break;
        case _STRING_AUDIO_ARC_PORT_D0:
        case _STRING_AUDIO_ARC_PORT_D1:
        case _STRING_AUDIO_ARC_PORT_D2:
        case _STRING_AUDIO_ARC_PORT_D3:
        case _STRING_AUDIO_ARC_PORT_D4:
            OsdPropGetArcInputPortStringAddress(usString - _STRING_AUDIO_ARC_PORT_LINE_IN);
            pucArray = g_pucModeInfoData;
            break;
        case _STRING_ARC_EARC:
            pucArray = tsOsdStreArc;
            break;
        case _STRING_AUDIO_ARC_OUT:
            pucArray = tsOsdAudioOut;
            break;
        case _STRING_AUDIO_ARC_PORT:
            pucArray = tsOsdInput;
            break;
        case _STRING_AUDIO_ARC_MODE:
            pucArray = tsOsdStrMode;
            break;
        case _STRING_AUDIO_ARC_MUTE:
            pucArray = tsOsdMute;
            break;
        case _STRING_AUDIO_ARC_CHANEL:
            pucArray = tsOsdStrEarcChannel;
            break;
        case _STRING_AUDIO_ARC_2_CH:
            pucArray = tsOsdStrChannel2;
            break;
        case _STRING_AUDIO_ARC_8_CH:
            pucArray = tsOsdStrChannel8;
            break;
        case _STRING_ARC_EARC_OFF:
            pucArray = tsOsdStrDisable;
            break;
        case _STRING_ARC_MODE:
            pucArray = tsOsdStrArc;
            break;
        case _STRING_EARC_MODE:
            pucArray = tsOsdStreArc;
            break;
        case _STRING_AUDIO_ARC:
            pucArray = tsOsdStrArc;
            break;
        case _STRING_AUDIO_DAC:
            pucArray = tsOsdStrDac;
            break;
#endif
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
        case _STRING_PXP_MST:
            pucArray = tsOsdStrPxpMst;
            break;
        case _STRING_OFF_PXP_MST:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_ON_FIXED:
            pucArray = tsOsdStrFixed;
            break;
        case _STRING_ON_SELECT:
            pucArray = tsOsdStrSelect;
            break;
#endif

        case _STRING_OD:
            pucArray = tsOsdOd;
            break;

        case _STRING_SDR_PLUS:
            pucArray = tsOsdStrSdrPlus;
            break;
        case _STRING_SDR_PLUS_ADJ:
            pucArray = tsOsdStrSdrPlusAdj;
            break;
        case _STRING_SDR_PLUS_DARK:
            pucArray = tsOsdDarkEnhance;
            break;
        case _STRING_SDR_PLUS_SHARP:
            pucArray = tsOsdSharpnessEnhance;
            break;
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
        case _STRING_NIGHT_SNIPER:
            pucArray = tsOsdStrNightSniper;
            break;
        case _STRING_NIGHT_SNIPER_SELECT:
            pucArray = tsOsdStrNightSniper;
            break;
        case _STRING_NIGHT_SNIPER_SATURATION:
            pucArray = tsOsdStrSaturation;
            break;
        case _STRING_NIGHT_SNIPER_LIGHTNESS:
            pucArray = tsOsdStrLightness;
            break;
#endif

        case _STRING_CROSSHAIR:
            pucArray = tsOsdStrCrosshair;
            break;
        case _STRING_ON_BY_POSITION:
            pucArray = tsOsdStrPosition;
            break;
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
        case _STRING_FW_UPDATE:
            pucArray = tsOsdStrFWUpdate;
            break;
        case _STRING_FW_UPDATE_MSG1:
            pucArray = tsOsdStrFWUpdateMsg;
            break;
        case _STRING_FW_UPDATE_MSG2:
            pucArray = tsOsdStrStartUpdate;
            break;
        case _STRING_FW_UPDATE_MSG3:
            pucArray = tsOsdStrFileSearch;
            break;
        case _STRING_RESULT_MSG1:
            pucArray = tsOsdStrFileResultMsg1;
            break;
        case _STRING_RESULT_MSG2:
            pucArray = tsOsdStrFileResultMsg2;
            break;
        case _STRING_RESULT_MSG3:
            pucArray = tsOsdStrFileResultMsg3;
            break;
        case _STRING_RESULT_MSG4:
            pucArray = tsOsdStrFileResultMsg4;
            break;
        case _STRING_RESULT_MSG5:
            pucArray = tsOsdStrFileResultMsg5;
            break;
#endif
#if(_ANTI_ALIASING_FUNCTION == _ON)
        case _STRING_ANTI_ALIASING:
            pucArray = tsOsdStrAntiAliasing;
            break;
        case _STRING_MODE:
            pucArray = tsOsdStrMode;
            break;
        case _STRING_LEVEL:
            pucArray = tsOsdStrLevel;
            break;
        case _STRING_EDGE_ENHANCE:
            pucArray = tsOsdEdgeEnhance;
            break;
        case _STRING_NOISE_REDUCTION:
            pucArray = tsOsdNoiseReduction;
            break;
#endif
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        case _STRING_EYE_PROTECT:
            pucArray = tsOsdStrEyeProtect;
            break;
        case _STRING_LOWBLUE:
            pucArray = tsOsdStrLowBlue;
            break;
        case _STRING_LOWBLUE_OFF:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_ADAPTIVE_MODE:
            pucArray = tsOsdStrAdaptiveMode;
            break;
        case _STRING_GLOBAL_MODE:
            pucArray = tsOsdStrGlobalMode;
            break;
        case _STRING_STATIC_GLOBAL_MODE:
            pucArray = tsOsdStrStaticGlobalMode;
            break;
        case _STRING_NIGHT_MODE:
            pucArray = tsOsdStrNightMode;
            break;
        case _STRING_AMBIENT_SENCE:
            pucArray = tsOsdAmbientSenseMode;
            break;
        case _STRING_PROTECT_LEVEL:
            pucArray = tsOsdStrProtectLevel;
            break;
        case _STRING_LEVEL0:
            pucArray = tsOsdStrLevel0;
            break;
        case _STRING_LEVEL1:
            pucArray = tsOsdStrLevel1;
            break;
        case _STRING_LEVEL2:
            pucArray = tsOsdStrLevel2;
            break;
        case _STRING_LEVEL3:
            pucArray = tsOsdStrLevel3;
            break;
        case _STRING_NIGHT_OFF:
            pucArray = tsOsdStrOff;
            break;
        case _STRING_NIGHT_1MIN:
            pucArray = tsOsdStr1Min;
            break;
        case _STRING_NIGHT_5MIN:
            pucArray = tsOsdStr5Min;
            break;
        case _STRING_NIGHT_10MIN:
            pucArray = tsOsdStr10Min;
            break;
#endif
        case _STRING_ENERGYSAVE:
            pucArray = tsOsdEnergySaver;
            break;
        default:
            pucArray = tsOsdNoSupport;
            break;
    }

    return pucArray;
}

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : print "xxx%"
// Input Value  : None
// Output Value : formatted string pointer
//--------------------------------------------------
void OsdPropShowPercentage(WORD usRow, WORD usCol, BYTE ucPercentage)
{
    BYTE pucDatap[7] = {0};

    if(ucPercentage >= 100)
    {
        pucDatap[0] = (_1_); // + (ucPercentage / 100));
    }
    else
    {
        pucDatap[0] = (_); // + (ucPercentage / 100));
    }
    pucDatap[1] = (_0_ + (ucPercentage % 100 / 10));
    pucDatap[2] = (_0_ + (ucPercentage % 10));
    pucDatap[3] = (_PERCENT0_);
    pucDatap[4] = (_PERCENT1_);
    pucDatap[5] = (_);
    pucDatap[6] = _END_;
    g_pucShowNumberAddress = &pucDatap[0];
    OsdPropPutString(usRow, (usCol), _PFONT_PAGE_3, _STRING_SHOW_NUMBER, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
}

//--------------------------------------------------
// Description  : covert ASCII to Font
// Input Value  : ASCII
// Output Value : FONT
//--------------------------------------------------
BYTE OsdPropAsciitoFont(BYTE ucASCII)
{
    if((ucASCII >= 'A') && (ucASCII <= 'Z'))
    {
        return (ucASCII - 'A' + _A_);
    }
    else if((ucASCII >= 'a') && (ucASCII <= 'z'))
    {
        return (ucASCII - 'a' + _a_);
    }
    else if((ucASCII >= '0') && (ucASCII <= '9'))
    {
        return (ucASCII - '0' + _0_);
    }
    else if(ucASCII == '.')
    {
        return (_DOT_);
    }
    else if(ucASCII == '_')
    {
        return (_SLINE_);
    }

    return _QUERY_;
}

//--------------------------------------------------
// Description  : print file name
// Input Value  : None
// Output Value : formatted string pointer
//--------------------------------------------------
void OsdPropShowFileName(WORD usRow, WORD usCol)
{
    BYTE pucDatap[64] = {0};
    BYTE ucLoop = 0;
    BYTE ucLength = UserCommonUsb2HostGetFileName(0);

    if(ucLength > 126)
    {
        ucLength = 126;
    }
    pucDatap[0] = _;
    for(ucLoop = 1; ucLoop <= ucLength; ucLoop++)
    {
        pucDatap[ucLoop] = OsdPropAsciitoFont(UserCommonUsb2HostGetFileName(ucLoop + 1));
        DebugMessageOsd("=>pucDatap", pucDatap[ucLoop]);
    }
    pucDatap[ucLoop] = _END_;
    g_pucShowNumberAddress = &pucDatap[0];
    OsdPropPutString(usRow, (usCol), _PFONT_PAGE_3, _STRING_SHOW_NUMBER, COLOR(_CP_RED, _CP_BG), _ENGLISH);
}
#endif // End of #if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
#if(_DRR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : print DRR status
// Input Value  : None
// Output Value : formatted string pointer
//--------------------------------------------------
void OsdPropShowDrrStatus(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucColor)
{
    BYTE ucloop = 0;

    switch(UserCommonDrrGetType())
    {
        case _DRR_NONE_TYPE:
            g_pucModeInfoData[ucloop++] = _D_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _COLON_;
            g_pucModeInfoData[ucloop++] = _O_;
            g_pucModeInfoData[ucloop++] = _F_;
            g_pucModeInfoData[ucloop++] = _F_;
            g_pucModeInfoData[ucloop++] = _END_;
            break;
        case _DRR_FREESYNC_TYPE:
            g_pucModeInfoData[ucloop++] = _D_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _COLON_;
            g_pucModeInfoData[ucloop++] = _O_;
            g_pucModeInfoData[ucloop++] = _N_;
            g_pucModeInfoData[ucloop++] = _LEFT_BRACE_;
            g_pucModeInfoData[ucloop++] = _F_;
            g_pucModeInfoData[ucloop++] = _S_;
            g_pucModeInfoData[ucloop++] = _RIGHT_BRACE_;
            g_pucModeInfoData[ucloop++] = _END_;
            break;
        case _DRR_HDMI21_VRR_TYPE:
            g_pucModeInfoData[ucloop++] = _D_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _COLON_;
            g_pucModeInfoData[ucloop++] = _O_;
            g_pucModeInfoData[ucloop++] = _N_;
            g_pucModeInfoData[ucloop++] = _LEFT_BRACE_;
            g_pucModeInfoData[ucloop++] = _V_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _RIGHT_BRACE_;
            g_pucModeInfoData[ucloop++] = _END_;
            break;
        case _DRR_DP_AS_TYPE:
            g_pucModeInfoData[ucloop++] = _D_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _COLON_;
            g_pucModeInfoData[ucloop++] = _O_;
            g_pucModeInfoData[ucloop++] = _N_;
            g_pucModeInfoData[ucloop++] = _LEFT_BRACE_;
            g_pucModeInfoData[ucloop++] = _A_;
            g_pucModeInfoData[ucloop++] = _S_;
            g_pucModeInfoData[ucloop++] = _RIGHT_BRACE_;
            g_pucModeInfoData[ucloop++] = _END_;
            break;
        case _DRR_DP_BOTHFSAS_TYPE:
            g_pucModeInfoData[ucloop++] = _D_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _COLON_;
            g_pucModeInfoData[ucloop++] = _O_;
            g_pucModeInfoData[ucloop++] = _N_;
            g_pucModeInfoData[ucloop++] = _LEFT_BRACE_;
            g_pucModeInfoData[ucloop++] = _F_;
            g_pucModeInfoData[ucloop++] = _S_;
            g_pucModeInfoData[ucloop++] = _AND_;
            g_pucModeInfoData[ucloop++] = _A_;
            g_pucModeInfoData[ucloop++] = _S_;
            g_pucModeInfoData[ucloop++] = _RIGHT_BRACE_;
            g_pucModeInfoData[ucloop++] = _END_;
            break;
        case _DRR_TYPE:
        default:
            g_pucModeInfoData[ucloop++] = _D_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _R_;
            g_pucModeInfoData[ucloop++] = _COLON_;
            g_pucModeInfoData[ucloop++] = _O_;
            g_pucModeInfoData[ucloop++] = _N_;
            g_pucModeInfoData[ucloop++] = _END_;
            break;
    }

    OsdPropPutString(ucRow, ucCol, ucFptsSelect, _STRING_DRR_STATUS, ucColor, _ENGLISH);
}
#endif

#endif// #if(_OSD_TYPE == _REALTEK_2020_OSD)

