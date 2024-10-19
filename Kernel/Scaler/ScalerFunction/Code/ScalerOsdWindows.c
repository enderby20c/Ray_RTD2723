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
// ID Code      : ScalerOsdWindows.c
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
StructOsdGridWindow g_stOsdWindowsGridWindow;
StructOsdWindow g_stOsdWindows;
StructOsdWindowGradient g_stOsdWindowsGradient;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Draw grid line
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerOsdDrawGridLine(WORD usPitchHorizontal, WORD usPitchVertical)
{
    BYTE ucFactor = 1;
    BYTE ucDelaySel = (_BIT7 | _BIT6);

#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
    ucDelaySel = (_BIT7 | _BIT6 | _BIT5 | _BIT4);
#endif

    if((GET_OSD_GRID_WINDOW_NUMBER() == _OSD_WINDOW_2) || (GET_OSD_GRID_WINDOW_NUMBER() == _OSD_WINDOW_3) || (GET_OSD_GRID_WINDOW_NUMBER() == _OSD_WINDOW_4))
    {
        WORD usOffset = (((WORD)GET_OSD_GRID_WINDOW_NUMBER() << 8) - _P3A_F6_PT_0200_WIN_F_WIN2_ADR_00);

        // Check Scaling up
        ScalerOsdSetAddrWindow(((WORD)GET_OSD_GRID_WINDOW_NUMBER() << 8) + _P3A_F6_PT_0000_WIN_F_WIN0_ADR_00);

        switch(ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT) & ucDelaySel)
        {
            case 0x00: // _OSD_POSITION_GLOBAL_1
                if(ScalerGetBit(P3A_C0_FRAME_CTRL_F_OSD_SU_CRTL, _BIT0) == _BIT0)
                {
                    return;
                }
                break;
            case _BIT6: // _OSD_POSITION_GLOBAL_2
                if(ScalerGetBit(P3A_C0_FRAME_CTRL_F_OSD_SU_CRTL, _BIT1) == _BIT1)
                {
                    return;
                }
                break;
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
            case _BIT7: // _OSD_POSITION_GLOBAL_3
                if(ScalerGetBit(P3A_C0_FRAME_CTRL_F_OSD_SU_CRTL, _BIT2) == _BIT2)
                {
                    return;
                }
                break;
            case (_BIT7 | _BIT6): // _OSD_POSITION_GLOBAL_4
                if(ScalerGetBit(P3A_C0_FRAME_CTRL_F_OSD_SU_CRTL, _BIT3) == _BIT3)
                {
                    return;
                }
                break;
#endif
            default:
                break;
        }

        // Set Grid Enable
        ScalerOsdSetAddrWindow(usOffset + _P3A_F6_PT_0220_WIN_F_WIN2_GRID_EN);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ((BYTE)GET_OSD_GRID_LINE_HORIZONTAL_ENABLE() << 2) | ((BYTE)GET_OSD_GRID_LINE_VERTICAL_ENABLE() << 1) | GET_OSD_GRID_LINE_FUNCTION_ENABLE());

        // Set Line Color
        ScalerOsdSetAddrWindow(usOffset + _P3A_F6_PT_0221_WIN_F_WIN2_GRID_COLOR);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, GET_OSD_GRID_LINE_COLOR() & _HW_OSD_PALETTE_BIT);

        // Set Line Width
        ScalerOsdSetAddrWindow(usOffset + _P3A_F6_PT_0222_WIN_F_WIN2_GRID_WDI);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, GET_OSD_GRID_LINE_WIDTH());

        // Set H Offset
        ScalerOsdSetAddrWindow(usOffset + _P3A_F6_PT_0225_WIN_F_WIN2_GRID_H_OFFSET);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, GET_OSD_GRID_LINE_H_OFFSET());

        // Set V Offset
        ScalerOsdSetAddrWindow(usOffset + _P3A_F6_PT_0226_WIN_F_WIN2_GRID_V_OFFSET);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, GET_OSD_GRID_LINE_V_OFFSET());

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
        {
            if(GET_OSD_GRID_LINE_PITCH() >= 0x3FFF)
            {
                ucFactor = 4;
            }
            else if(GET_OSD_GRID_LINE_PITCH() >= 0x1FFF)
            {
                ucFactor = 2;
            }
        }
#endif

        // Set Line Pitch
        ScalerOsdSetAddrWindow(usOffset + _P3A_F6_PT_0223_WIN_F_WIN2_GRID_PITCH_MSB);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ((GET_OSD_GRID_LINE_PITCH() / ucFactor) >> 8) & 0x7F);
        ScalerOsdSetAddrWindow(usOffset + _P3A_F6_PT_0224_WIN_F_WIN2_GRID_PITCH_LSB);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, (GET_OSD_GRID_LINE_PITCH() / ucFactor) & 0xFF);

        // Set Panel Pitch
        ScalerOsdDrawGridLinePanelPitch(usPitchHorizontal / ucFactor, usPitchVertical / ucFactor);
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    code StructOsdGridWindow g_stOsdWindowGridTest  = { _OSD_WINDOW_2,        bGridLineWindowNumber
                                                        1,                    bGridLineWidth
                                                        1,                    bGridLineColor
                                                        _DISABLE,             bGridLineHorizontalEnable
                                                        _ENABLE,              bGridLineVerticalEnable
                                                        0x03,                 bGridLineOffset
                                                        0x2710,               bGridLinePitch
                                                        _ENABLE               bGridFunctionEnable
                                                      };
    g_stOsdGridWindow = g_stOsdWindowGridTest;
    ScalerOsdDrawGridLine(993, 993);

*/

//--------------------------------------------------
// Description  : Set grid line pitch pixel
// Input Value  : ucPitchHorizontal -> Horizontal pitch
// Input Value  : ucPitchVertical   -> Vertical pitch
// Output Value :
//--------------------------------------------------
void ScalerOsdDrawGridLinePanelPitch(WORD usPitchHorizontal, WORD usPitchVertical)
{
    // uint : 0.125um
    ScalerOsdSetAddrWindow(_P3A_F6_PT_32D0_WIN_F_WIN_GRID_PITCH_PANEL_MSB);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ((usPitchHorizontal & 0xF00) >> 4) | ((usPitchVertical & 0xF00) >> 8));

    ScalerOsdSetAddrWindow(_P3A_F6_PT_32D1_WIN_F_WIN_GRID_PITCH_PANEL_H_LSB);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, usPitchHorizontal & 0xFF);

    ScalerOsdSetAddrWindow(_P3A_F6_PT_32D2_WIN_F_WIN_GRID_PITCH_PANEL_V_LSB);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, usPitchVertical & 0xFF);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdDrawGridLinePanelPitch(993, 993);
*/

//--------------------------------------------------
// Description  : window number mapping to register address
// Input Value  : enumOsdWindowsTyp
// Output Value :
//--------------------------------------------------
WORD ScalerOsdWindowRegisterMapping(EnumOsdWindowsType enumOsdWindowsType)
{
    WORD usWin = 0;

    usWin = enumOsdWindowsType / 10 * 16;
    usWin += (enumOsdWindowsType % 10);
    return (usWin << 8);
}

//--------------------------------------------------
// Description  : Draw window
// Input Value  : usXStart -> Horizontal start address
//                usYStart -> Vertical start address
//                usXEnd   -> Horizontal end address
//                usYEnd   -> Vertical end address
// Output Value :
//--------------------------------------------------
void ScalerOsdDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
{
    BYTE pucpTemp[15] = {0};
    WORD usWinTemp = 0;
    BYTE ucWinIdx = 0;

    usWinTemp = ScalerOsdWindowRegisterMapping(GET_OSD_WINDOW_NUMBER());
    ucWinIdx = GET_OSD_WINDOW_NUMBER() % 8;

    if(GET_OSD_WINDOW_BUTTON_TYPE() == _OSD_WINDOW_BUTTON_TYPE_BORDER)
    {
        // Border Width cannot be 0
        if(GET_OSD_WINDOW_BORDER_PIXEL_WIDTH() == 0)
        {
            SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(1);
        }

        // Border Height cannot be 0
        if(GET_OSD_WINDOW_BORDER_PIXEL_HEIGHT() == 0)
        {
            SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(1);
        }
    }

    // Check Grid Function
    if((GET_OSD_WINDOW_NUMBER() == _OSD_WINDOW_2) ||
       (GET_OSD_WINDOW_NUMBER() == _OSD_WINDOW_3) ||
       (GET_OSD_WINDOW_NUMBER() == _OSD_WINDOW_4))
    {
        ScalerOsdSetAddrWindow((((WORD)GET_OSD_WINDOW_NUMBER() - _OSD_WINDOW_2) << 8) + _P3A_F6_PT_0220_WIN_F_WIN2_GRID_EN);
        if((ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT) & _BIT0) != 0x00)
        {
            SET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE(_DISABLE);
        }
    }

    // Disable window button type for window 29
    if((GET_OSD_WINDOW_NUMBER() == _OSD_WINDOW_29) &&
       (GET_OSD_WINDOW_ENABLE() == _OFF) &&
       ((GET_OSD_WINDOW_BUTTON_TYPE() == _OSD_WINDOW_BUTTON_TYPE_BORDER) ||
        (GET_OSD_WINDOW_BUTTON_TYPE() == _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_1) ||
        (GET_OSD_WINDOW_BUTTON_TYPE() == _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_2)))
    {
        SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_DISABLE);
    }

    pucpTemp[0] = (((BYTE)GET_OSD_WINDOW_REFERENCE_DELAY() << 6) |
                   ((BYTE)GET_OSD_WINDOW_BLEND_ENABLE() << 3) |
                   ((BYTE)GET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE() << 2) |
                   ((BYTE)GET_OSD_WINDOW_COLOR_MASK_AND() << 1));

    ScalerOsdSetAddrWindow(usWinTemp + _P3A_F6_PT_0001_WIN_F_WIN0_ADR_01);
    pucpTemp[1] = (ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT) & 0xF0); // Get rounded enable status
    pucpTemp[1] |= ((BYTE)GET_OSD_WINDOW_ROUNDED_SIZE() << 3) | ((BYTE)GET_OSD_WINDOW_BUTTON_TYPE());

    pucpTemp[2] = (GET_OSD_WINDOW_COLOR() & _HW_OSD_PALETTE_BIT);
    pucpTemp[3] = ((usXStart >> 8) & 0x3F);
    pucpTemp[4] = (usXStart & 0xFF);
    pucpTemp[5] = ((usYStart >> 8) & 0x3F);
    pucpTemp[6] = (usYStart & 0xFF);
    pucpTemp[7] = ((usXEnd >> 8) & 0x3F);
    pucpTemp[8] = (usXEnd & 0xFF);
    pucpTemp[9] = ((usYEnd >> 8) & 0x3F);
    pucpTemp[10] = (usYEnd & 0xFF);
    pucpTemp[11] = (GET_OSD_WINDOW_EFF_COLOR_2() & _HW_OSD_PALETTE_BIT);
    pucpTemp[12] = (GET_OSD_WINDOW_EFF_COLOR_1() & _HW_OSD_PALETTE_BIT);
    pucpTemp[13] = (GET_OSD_WINDOW_BORDER_PIXEL_WIDTH() & 0x1F);
    pucpTemp[14] = (GET_OSD_WINDOW_BORDER_PIXEL_HEIGHT() & 0x1F);

    if(GET_OSD_WINDOW_WAIT_DEN_STOP() == _ENABLE)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    }

    ScalerOsdSetAddrWindow(usWinTemp + 1);
    ScalerOsdBurstWriteDataPortWindow(&pucpTemp[1], 14, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);

    if((GET_OSD_WINDOW_ENABLE() == _ENABLE) && (((bit)ScalerGetBit(P3A_31_FRAME_CTRL_F_WIN_ENABLE_7_0 + GET_OSD_WINDOW_NUMBER() / 8, (_BIT0 << ucWinIdx))) == 0x00))
    {
        // if win disable to enable, wait dden_stop
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    }

    ScalerOsdSetAddrWindow(usWinTemp);
    ScalerOsdBurstWriteDataPortWindow(&pucpTemp[0], 1, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);

    // Set window enable/disable
    ScalerSetBit(P3A_31_FRAME_CTRL_F_WIN_ENABLE_7_0 + GET_OSD_WINDOW_NUMBER() / 8,
                 ~(_BIT0 << ucWinIdx),
                 (GET_OSD_WINDOW_ENABLE() == _OFF) ? (0x00) : (_BIT0 << ucWinIdx));

    memset(&g_stOsdWindows, 0x00, sizeof(g_stOsdWindows));
}

/*
//--------------------------------------------------
// example 1
//--------------------------------------------------
    code StructOsdWindow g_stOsdWindowTest = { _OSD_WINDOW_6,                               // b5WindowNumber
                                               _ENABLE,                                     // b1WindowEnable
                                               9,                                           // b6WindowColor
                                               6,                                           // b6WindowColorShadow
                                               0,                                           // b6WindowColorBorder
                                               1,                                           // b3WindowShadowBorderPixelWidth
                                               1,                                           // b3WindowShadowBorderPixelHeight
                                               _OSD_WINDOW_GRADIENT_LEVEL_STEP_3,           // b2WindowGradientLevelStep
                                               _OSD_WINDOW_GRADIENT_LEVEL_PER_5,            // b3WindowGradientLevelPer
                                               _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,      // b1WindowGradientPolarityR
                                               _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,      // b1WindowGradientPolarityG
                                               _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,      // b1WindowGradientPolarityB
                                               _ENABLE,                                     // b1WindowGradientEnableR
                                               _DISABLE,                                    // b1WindowGradientEnableG
                                               _ENABLE,                                     // b1WindowGradientEnableB
                                               0,                                           // b1WindowGradientSaturatedColorMode
                                               0,                                           // b1WindowGradientReversedColorMode
                                               0,                                           // b1WindowReferenceDelay
                                               _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8,      // b1WindowGradientLevelExtension
                                               1,                                           // b1WindowBlend
                                               1,                                           // b1WindowGradient
                                               _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,   // b1WindowGradientDirection
                                               1,                                           // b1WindowButtonEnable
                                               _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_1,         // b3WindowType
                                               _ENABLE                                      // b1WindowRotationFunctionEnable
                                             };

    g_stOsdWindow = g_stOsdWindowTest;
    ScalerOsdDrawWindow(XSTART(100), YSTART(200), XEND(300), YEND(400));


//--------------------------------------------------
// example 2
//--------------------------------------------------
    SET_OSD_WINDOW_NUMBER(6);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    SET_OSD_WINDOW_COLOR(4);
    SET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE(_ENABLE);
    ScalerOsdDrawWindow(XSTART(100), YSTART(200), XEND(300), YEND(400));

*/

//--------------------------------------------------
// Description  : Draw window
// Input Value  : usXStart -> Horizontal start address
//                usYStart -> Vertical start address
//                usXEnd   -> Horizontal end address
//                usYEnd   -> Vertical end address
// Output Value :
//--------------------------------------------------
void ScalerOsdDrawWindowGradient(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
{
    BYTE pucpTemp[11] = {0};

    if(GET_OSD_WINDOW_GRANIENT_WIN() != 0x3F)
    {
        // Check Chessboard function
        pucpTemp[0] = GET_OSD_WINDOW_GRANIENT_WIN() / 10 * 16;
        pucpTemp[0] += (GET_OSD_WINDOW_GRANIENT_WIN() % 10);
        ScalerOsdSetAddrWindow(((WORD)pucpTemp[0] << 8) + _P3A_F6_PT_0001_WIN_F_WIN0_ADR_01);
        if((ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT) & 0x07) == _OSD_WINDOW_BUTTON_TYPE_CHESSBOARD)
        {
            // Disable eff-function
            ScalerOsdSetAddrWindow(((WORD)pucpTemp[0] << 8) + _P3A_F6_PT_0001_WIN_F_WIN0_ADR_01);
            ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, _OSD_WINDOW_BUTTON_TYPE_DISABLE);

            // Set eff-width = 0, eff-height = 0
            ScalerOsdSetAddrWindow(((WORD)pucpTemp[0] << 8) + _P3A_F6_PT_000D_WIN_F_WIN0_EFF_WID);
            ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
            ScalerOsdSetAddrWindow(((WORD)pucpTemp[0] << 8) + _P3A_F6_PT_000E_WIN_F_WIN0_EFF_HEI);
            ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
        }

        // Set Gradient Size
        ScalerOsdDrawWindowGradientSize(usXStart, usYStart, usXEnd, usYEnd);

        pucpTemp[0] = (((BYTE)GET_OSD_WINDOW_GRADIENT_POLARITY_R() << 7) | ((BYTE)GET_OSD_WINDOW_GRADIENT_POLARITY_G() << 6) | ((BYTE)GET_OSD_WINDOW_GRADIENT_POLARITY_B() << 5) | ((BYTE)GET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_MODE() << 4));
        pucpTemp[0] |= (((BYTE)GET_OSD_WINDOW_GRADIENT_REVERSED_COLOR_MODE() << 3) | ((BYTE)GET_OSD_WINDOW_GRADIENT_ENABLE_R() << 2) | ((BYTE)GET_OSD_WINDOW_GRADIENT_ENABLE_G() << 1) | ((BYTE)GET_OSD_WINDOW_GRADIENT_ENABLE_B()));
        pucpTemp[1] = (((BYTE)GET_OSD_WINDOW_GRADIENT_DIRECTION() << 7) | ((BYTE)GET_OSD_WINDOW_GRANIENT_WIN() & 0x3F));
        pucpTemp[2] = (GET_OSD_WINDOW_GRADIENT_COLOR() & _HW_OSD_PALETTE_BIT);
        pucpTemp[3] = GET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_R();
        pucpTemp[4] = GET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_G();
        pucpTemp[5] = GET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_B();
        pucpTemp[6] = GET_OSD_WINDOW_GRADIENT_LEVEL_SETP();
        pucpTemp[7] = GET_OSD_WINDOW_GRADIENT_LEVEL_SETP_DEC();
        pucpTemp[8] = GET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_R();
        pucpTemp[9] = GET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_G();
        pucpTemp[10] = GET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_B();

        ScalerOsdSetAddrWindow(GET_OSD_WINDOW_GRANIENT_INDEX() * 0x20 + 0x3200);
        ScalerOsdBurstWriteDataPortWindow(pucpTemp, 11, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);

        memset(&g_stOsdWindowsGradient, 0x00, sizeof(g_stOsdWindowsGradient));
    }
}


//--------------------------------------------------
// Description  : Set window Priority
// Input Value  : EnumOsdFontPriorityType        ->    _OSD_FONT_ABOVE_WIN_31, _OSD_FONT_ABOVE_WIN_30,  _OSD_FONT_ABOVE_WIN_29,
//                                                     _OSD_FONT_ABOVE_WIN_28, _OSD_FONT_ABOVE_WIN_27, _OSD_FONT_ABOVE_WIN_26,
//                                                     _OSD_FONT_ABOVE_WIN_25,  _OSD_FONT_ABOVE_WIN_24,
// Output Value :
//--------------------------------------------------
void ScalerOsdFontPriority(EnumOsdFontPriorityType enumOsdFontPriorityType)
{
    ScalerSetBit(P3A_30_FRAME_CTRL_F_FONT_PRIORITY, ~(_BIT2 | _BIT1 | _BIT0), enumOsdFontPriorityType);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdFontPriority(_OSD_FONT_ABOVE_WIN_31);
*/

//--------------------------------------------------
// Description  : Set Window Rounded Window Size
// Input Value  : enumOsdWindowsType -> _OSD_WINDOW_0 or _OSD_WINDOW_5 or _OSD_WINDOW_4_1 ~ _OSD_WINDOW_4_8 or _OSD_WINDOW_5_1 ~ _OSD_WINDOW_5_8
//                enumRoundedWinSize -> _OSD_ROUNDED_WIN_SIZE_8x8 or _OSD_ROUNDED_WIN_SIZE_16x16 or _OSD_ROUNDED_WIN_SIZE_32x32
// Output Value :
//--------------------------------------------------
void ScalerOsdRoundedWindowSize(EnumOsdWindowsType enumOsdWindowsType, EnumOsdRoundedWindowType enumRoundedWinSize)
{
    WORD usWin = 0;
    BYTE ucValue = 0;

    // Set Address
    usWin = ScalerOsdWindowRegisterMapping(enumOsdWindowsType);
    ScalerOsdSetAddrWindow(usWin + _P3A_F6_PT_0001_WIN_F_WIN0_ADR_01);

    // Set Value
    ucValue = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
    ucValue = ((ucValue & (~_BIT3)) | ((BYTE)enumRoundedWinSize << 3));
    ScalerOsdSetAddrWindow(usWin + _P3A_F6_PT_0001_WIN_F_WIN0_ADR_01);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucValue);
}

//--------------------------------------------------
// Description  : Set Window Rounded On/Off
// Input Value  : enumOsdWindowsType -> _OSD_WINDOW_0 or _OSD_WINDOW_5 or _OSD_WINDOW_4_1 ~ _OSD_WINDOW_4_8 or _OSD_WINDOW_5_1 ~ _OSD_WINDOW_5_8
//                bOnOff             -> _ENABLE or _DISABLE
//                bUpperLeftEnable  - > _ENABLE or _DISABLE
//                bLowerLeftEnable   -> _ENABLE or _DISABLE
//                bUpperRightEnable  -> _ENABLE or _DISABLE
//                bLowerRightEnable  -> _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerOsdRoundedWindowOnOff(EnumOsdWindowsType enumOsdWindowsType, bit bOnOff, bit bUpperLeftEnable, bit bLowerLeftEnable, bit bUpperRightEnable, bit bLowerRightEnable)
{
    BYTE ucVaule = 0x00;
    WORD usWin = 0x00;

    usWin = ScalerOsdWindowRegisterMapping(enumOsdWindowsType);
    ScalerOsdSetAddrWindow(usWin + _P3A_F6_PT_0001_WIN_F_WIN0_ADR_01);
    ucVaule = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
    ucVaule = (ucVaule & ~(0xF0)) | (((BYTE)bUpperLeftEnable << 7) | ((BYTE)bLowerLeftEnable << 6) | ((BYTE)bUpperRightEnable << 5) | ((BYTE)bLowerRightEnable << 4));
    if(bOnOff == _ON)
    {
        ucVaule = ((ucVaule & (~(_BIT2 | _BIT1 | _BIT0))) | _OSD_WINDOW_BUTTON_TYPE_ROUNDED);
    }
    else
    {
        ucVaule = ((ucVaule & (~(_BIT2 | _BIT1 | _BIT0))) | _OSD_WINDOW_BUTTON_TYPE_DISABLE);
    }
    ScalerOsdSetAddrWindow(usWin + _P3A_F6_PT_0001_WIN_F_WIN0_ADR_01);
    ScalerOsdSetDataPortWindow(ucVaule);
}

//--------------------------------------------------
// Description  : Set Window Rounded Pattern 16x16
// Input Value  : ucIdx -> Pattern Index 0~15
// Input Value  : ucType -> Pattern Type
// Output Value :
//--------------------------------------------------
void ScalerOsdRoundedWindowPattern16x16(BYTE ucIdx, BYTE ucType)
{
    WORD usReg = _P3A_F6_PT_32C5_WIN_F_WIN_ROUND_16_PAT_0;
    BYTE ucValue = 0;

    usReg += (ucIdx / 2);
    ScalerOsdSetAddrWindow(usReg);
    ucValue = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
    if((ucIdx % 2) == 0)
    {
        ucValue = ((ucValue & (~(_BIT3 | _BIT2 | _BIT1 | _BIT0))) | (ucType & 0x0F));
    }
    else
    {
        ucValue = ((ucValue & (~(_BIT7 | _BIT6 | _BIT5 | _BIT4))) | ((ucType & 0x0F) << 4));
    }
    ScalerOsdSetAddrWindow(usReg);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucValue);
}

//--------------------------------------------------
// Description  : Set Window Rounded Pattern 8x8
// Input Value  : ucIdx -> Pattern Index 0~7
// Input Value  : ucType -> Pattern Type
// Output Value :
//--------------------------------------------------
void ScalerOsdRoundedWindowPattern8x8(BYTE ucIdx, BYTE ucType)
{
    WORD usReg = _P3A_F6_PT_32C1_WIN_F_WIN_ROUND_8_PAT_0;
    BYTE ucValue = 0;

    usReg += (ucIdx / 2);
    ScalerOsdSetAddrWindow(usReg);
    ucValue = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
    if((ucIdx % 2) == 0)
    {
        ucValue = ((ucValue & (~(_BIT2 | _BIT1 | _BIT0))) | (ucType & 0x07));
    }
    else
    {
        ucValue = ((ucValue & (~(_BIT6 | _BIT5 | _BIT4))) | ((ucType & 0x07) << 4));
    }
    ScalerOsdSetAddrWindow(usReg);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucValue);
}

#if(_HW_OSD_ROUND_WIN_0_PIXEL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Window Rounded Pattern 16x16 0_Pixel Enable/Disable
// Input Value  : ucIdx -> Pattern Index 0~15
// Input Value  : bEnable -> _ENABLE, _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerOsdRoundedWindowPattern16x16_0Pixel(BYTE ucIdx, bit bEnable)
{
    BYTE ucValue = 0;

    if(ucIdx <= 7)
    {
        // win_round_pat_16_7_0pixel_en ~ win_round_pat_16_0_0pixel_en
        ScalerOsdSetAddrWindow(_P3A_F6_PT_32CD_WIN_F_WIN_ROUND_16_PAT_CTRL1);
        ucValue = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
        ucValue = (ucValue & (~(((BYTE)_BIT0) << ucIdx))) | (((BYTE)bEnable) << ucIdx);
        ScalerOsdSetAddrWindow(_P3A_F6_PT_32CD_WIN_F_WIN_ROUND_16_PAT_CTRL1);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucValue);
    }
    else
    {
        // win_round_pat_16_15_0pixel_en ~ win_round_pat_16_8_0pixel_en
        ScalerOsdSetAddrWindow(_P3A_F6_PT_32CE_WIN_F_WIN_ROUND_16_PAT_CTRL2);
        ucValue = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
        ucValue = (ucValue & (~(((BYTE)_BIT0) << (ucIdx - 8)))) | (((BYTE)bEnable) << (ucIdx - 8));
        ScalerOsdSetAddrWindow(_P3A_F6_PT_32CE_WIN_F_WIN_ROUND_16_PAT_CTRL2);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucValue);
    }
}

//--------------------------------------------------
// Description  : Set Window Rounded Pattern 8x8 0_Pixel Enable/Disable
// Input Value  : ucIdx -> Pattern Index 0~7
// Input Value  : bEnable -> _ENABLE, _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerOsdRoundedWindowPattern8x8_0Pixel(BYTE ucIdx, bit bEnable)
{
    WORD usReg = _P3A_F6_PT_32C1_WIN_F_WIN_ROUND_8_PAT_0;
    BYTE ucValue = 0;

    usReg += (ucIdx / 2);
    ScalerOsdSetAddrWindow(usReg);
    ucValue = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
    if((ucIdx % 2) == 0)
    {
        ucValue = ((ucValue & (~(_BIT3))) | ((bEnable == _ENABLE) ? (_BIT3) : (0x00)));
    }
    else
    {
        ucValue = ((ucValue & (~(_BIT7))) | ((bEnable == _ENABLE) ? (_BIT7) : (0x00)));
    }
    ScalerOsdSetAddrWindow(usReg);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucValue);
}
#endif

//--------------------------------------------------
// Description  : Set window 28 Special function
// Input Value  : enumOsdWindow28FunctionType   -> _OSD_WINDOW_28_FUNCTION_DISABLE                    or _OSD_WINDOW_28_FUNCTION_NO_BLENDING_BOTH                  or
//                                                 _OSD_WINDOW_28_FUNCTION_NO_BLENDING_FOREGROUND     or _OSD_WINDOW_28_FUNCTION_NO_BLENDING_BACKGROUND            or
//                                                 _OSD_WINDOW_28_FUNCTION_BLENDING_BOTH
// Output Value :
//--------------------------------------------------
void ScalerOsdWindow28SpecialFunction(EnumOsdWindow28FunctionType enumOsdWindow28FunctionType)
{
    if(enumOsdWindow28FunctionType != _OSD_WINDOW_28_FUNCTION_DISABLE)
    {
        ScalerSetBit(P3A_2F_FRAME_CTRL_F_WIN_SPECIAL_FUN, ~(_BIT4 | _BIT1 | _BIT0), ((enumOsdWindow28FunctionType - _OSD_WINDOW_28_FUNCTION_NO_BLENDING_BOTH) | _BIT4));
    }
    else
    {
        ScalerSetBit(P3A_2F_FRAME_CTRL_F_WIN_SPECIAL_FUN, ~_BIT4, 0x00);
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdWindow28SpecialFunction(_OSD_WINDOW_28_FUNCTION_NO_BLENDING_FOREGROUND);
*/

//--------------------------------------------------
// Description  : Set window 29 Special function
// Input Value  : EnumOsdWindow29FunctionType   -> _OSD_WINDOW_29_FUNCTION_DISABLE                        or _OSD_WINDOW_29_FUNCTION_NO_BLENDING_BOTH                  or
//                                                 _OSD_WINDOW_29_FUNCTION_NO_BLENDING_FOREGROUND         or _OSD_WINDOW_29_FUNCTION_NO_BLENDING_BACKGROUND            or
//                                                 _OSD_WINDOW_29_FUNCTION_BLENDING_BOTH                  or _OSD_WINDOW_29_FUNCTION_MASK_REGION_APPEAR                or
//                                                 _OSD_WINDOW_29_FUNCTION_MASK_REGION_TRANSPARENT_ALL    or _OSD_WINDOW_29_FUNCTION_MASK_REGION_TRANSPARENT_FONT
// Output Value :
//--------------------------------------------------
void ScalerOsdWindow29SpecialFunction(EnumOsdWindow29FunctionType enumOsdWindow29FunctionType)
{
    if((enumOsdWindow29FunctionType == _OSD_WINDOW_29_FUNCTION_NO_BLENDING_BOTH) ||
       (enumOsdWindow29FunctionType == _OSD_WINDOW_29_FUNCTION_NO_BLENDING_FOREGROUND) ||
       (enumOsdWindow29FunctionType == _OSD_WINDOW_29_FUNCTION_NO_BLENDING_BACKGROUND) ||
       (enumOsdWindow29FunctionType == _OSD_WINDOW_29_FUNCTION_BLENDING_BOTH))
    {
        ScalerSetBit(P3A_2F_FRAME_CTRL_F_WIN_SPECIAL_FUN, ~(_BIT6 | _BIT5), _BIT5);  // 01: Font Blending
        ScalerSetBit(P3A_2F_FRAME_CTRL_F_WIN_SPECIAL_FUN, ~(_BIT3 | _BIT2), ((enumOsdWindow29FunctionType - _OSD_WINDOW_29_FUNCTION_NO_BLENDING_BOTH) << 2));
    }
    else if(enumOsdWindow29FunctionType == _OSD_WINDOW_29_FUNCTION_MASK_REGION_APPEAR)
    {
        ScalerSetBit(P3A_2F_FRAME_CTRL_F_WIN_SPECIAL_FUN, ~(_BIT6 | _BIT5), _BIT6);  // 10: Window 7 mask region appear
    }
    else if((enumOsdWindow29FunctionType == _OSD_WINDOW_29_FUNCTION_MASK_REGION_TRANSPARENT_ALL) || (enumOsdWindow29FunctionType == _OSD_WINDOW_29_FUNCTION_MASK_REGION_TRANSPARENT_FONT))
    {
        ScalerSetBit(P3A_2F_FRAME_CTRL_F_WIN_SPECIAL_FUN, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));  // 11: Window 7 mask region transparent
        ScalerSetBit(P3A_2F_FRAME_CTRL_F_WIN_SPECIAL_FUN, ~_BIT7, ((enumOsdWindow29FunctionType - _OSD_WINDOW_29_FUNCTION_MASK_REGION_TRANSPARENT_ALL) << 7));
    }
    else
    {
        ScalerSetBit(P3A_2F_FRAME_CTRL_F_WIN_SPECIAL_FUN, ~(_BIT6 | _BIT5), 0x00);
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdWindow29SpecialFunction(_OSD_WINDOW_29_FUNCTION_DISABLE);
*/

//--------------------------------------------------
// Description  : Set window 6 Special function
// Input Value  : bEnable            -> _ENABLE or _DISABLE
//                enumOsdWindowsType -> _OSD_WINDOW_8   or _OSD_WINDOW_9   or _OSD_WINDOW_4_1 or _OSD_WINDOW_4_2 or _OSD_WINDOW_4_3 or
//                                      _OSD_WINDOW_4_4 or _OSD_WINDOW_4_5 or _OSD_WINDOW_4_6 or _OSD_WINDOW_4_7 or _OSD_WINDOW_4_8
//                ChessBoardColor1   -> Color (0 ~ 63)
//                ChessBoardColor2   -> Color (0 ~ 63)
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowChessboard(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucChessBoardColor1, BYTE ucChessBoardColor2)
{
    WORD usTemp = 0;

    WORD usTempWindowNumber = 0;

    // Check Gradient Function
    for(usTemp = _OSD_WIN_GRADIENT_0; usTemp <= _OSD_WIN_GRADIENT_5; usTemp++)
    {
        ScalerOsdSetAddrWindow(usTemp * 0x20 + _P3A_F6_PT_3201_WIN_F_WIN_GRADIENT0_1);
        usTempWindowNumber = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
        if(enumOsdWindowsType == (usTempWindowNumber & 0x3F))
        {
            // Disable Gradient Function
            ScalerOsdSetAddrWindow(usTemp * 0x20 + _P3A_F6_PT_3201_WIN_F_WIN_GRADIENT0_1);
            ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, (usTempWindowNumber | 0x3F));
        }
    }

    // Calculate Window Address
    usTempWindowNumber = ScalerOsdWindowRegisterMapping(enumOsdWindowsType);

    // Set Address
    ScalerOsdSetAddrWindow((usTempWindowNumber + _P3A_F6_PT_0001_WIN_F_WIN0_ADR_01));

    // Get Data
    usTemp = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
    if(bEnable == _ENABLE)
    {
        usTemp = ((usTemp & (~(_BIT2 | _BIT1 | _BIT0))) | (_BIT2 | _BIT1));
    }
    else
    {
        usTemp = (usTemp & (~(_BIT2 | _BIT1 | _BIT0)));
    }

    // Set Data
    ScalerOsdSetAddrWindow((usTempWindowNumber + _P3A_F6_PT_0001_WIN_F_WIN0_ADR_01));
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, usTemp);

    // Set Chessboard Color1, Color2
    ScalerOsdSetAddrWindow((usTempWindowNumber + _P3A_F6_PT_000B_WIN_F_WIN0_EFF_COLOR_2));
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucChessBoardColor2);
    ScalerOsdSetAddrWindow((usTempWindowNumber + _P3A_F6_PT_000C_WIN_F_WIN0_EFF_COLOR_1));
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucChessBoardColor1);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdWindowChessboard(_ENABLE, _OSD_WINDOW_4_1, 0, 8);
*/

//--------------------------------------------------
// Description  : Disable window
// Input Value  : enumOsdWindowsType -> _OSD_WINDOW_0,   _OSD_WINDOW_1,   _OSD_WINDOW_2,   _OSD_WINDOW_3,   _OSD_WINDOW_4,   _OSD_WINDOW_5,
//                                      _OSD_WINDOW_6,   _OSD_WINDOW_7,   _OSD_WINDOW_8,   _OSD_WINDOW_9,   _OSD_WINDOW_4_1, _OSD_WINDOW_4_2,
//                                      _OSD_WINDOW_4_3, _OSD_WINDOW_4_4, _OSD_WINDOW_4_5, _OSD_WINDOW_4_6, _OSD_WINDOW_4_7, _OSD_WINDOW_4_8
//                                      _OSD_WINDOW_5_1, _OSD_WINDOW_5_2, _OSD_WINDOW_5_3, _OSD_WINDOW_5_4, _OSD_WINDOW_5_5, _OSD_WINDOW_5_6,
//                                      _OSD_WINDOW_5_7, _OSD_WINDOW_5_8
//                                      _OSD_WINDOW_ALL,
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowDisable(EnumOsdWindowsType enumOsdWindowsType)
{
    if(enumOsdWindowsType == _OSD_WINDOW_ALL)
    {
        ScalerSetByte(P3A_31_FRAME_CTRL_F_WIN_ENABLE_7_0, 0x00);
        ScalerSetByte(P3A_32_FRAME_CTRL_F_WIN_ENABLE_15_8, 0x00);
        ScalerSetByte(P3A_33_FRAME_CTRL_F_WIN_ENABLE_23_16, 0x00);
        ScalerSetByte(P3A_34_FRAME_CTRL_F_WIN_ENABLE_31_24, 0x00);
    }
    else
    {
        ScalerSetBit(P3A_31_FRAME_CTRL_F_WIN_ENABLE_7_0 + enumOsdWindowsType / 8, ~(_BIT0 << (enumOsdWindowsType % 8)), 0x00);
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdWindowDisable(_OSD_WINDOW_0);
*/

//--------------------------------------------------
// Description  : Disable Gradient Window
// Input Value  : emunWindowGradientIndex
// Output Value :
//--------------------------------------------------
void ScalerOsdDrawWindowGradientDisableIndex(EnumOsdWinGradientType enumWindowGradientIndex)
{
    ScalerOsdSetAddrWindow((BYTE)enumWindowGradientIndex * 0x20 + _P3A_F6_PT_3201_WIN_F_WIN_GRADIENT0_1);
    ScalerOsdSetDataPortWindow(0x3F);
}

//--------------------------------------------------
// Description  : Set window extension gradient level for R/G/B channel
// Input Value  : enumOsdWinGradientIdx
//                ucLevelR           -> window RED extension gradient level (0 ~ 255)
//                ucLevelG           -> window GRN extension gradient level (0 ~ 255)
//                ucLevelB           -> window BLU extension gradient level (0 ~ 255)
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowGradientLevelIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucLevelR, BYTE ucLevelG, BYTE ucLevelB)
{
    WORD usTempWindowNumber = 0;

    usTempWindowNumber = ((BYTE)enumOsdWinGradientIdx * 0x20);
    ScalerOsdSetAddrWindow(usTempWindowNumber + _P3A_F6_PT_3203_WIN_F_WIN_GRADIENT0_LEVEL_R);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucLevelR);
    ScalerOsdSetAddrWindow(usTempWindowNumber + _P3A_F6_PT_3204_WIN_F_WIN_GRADIENT0_LEVEL_G);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucLevelG);
    ScalerOsdSetAddrWindow(usTempWindowNumber + _P3A_F6_PT_3205_WIN_F_WIN_GRADIENT0_LEVEL_B);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucLevelB);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    SET_OSD_WINDOW_GRADIENT_ENABLE_R(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_ENABLE(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_LEVEL_EXTENSION(_OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_256);
    SET_OSD_WINDOW_NUMBER(5);
    SET_OSD_WINDOW_COLOR(4);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    ScalerOsdDrawWindow(XSTART(100), YSTART(200), XEND(300), YEND(400));
    ScalerOsdWindowGradientLevel(_OSD_WINDOW_0, 100, 100, 100);
*/

//--------------------------------------------------
// Description  : Draw window Gradient Size
// Input Value  : usXStart -> Horizontal start address
//                usYStart -> Vertical start address
//                usXEnd   -> Horizontal end address
//                usYEnd   -> Vertical end address
// Output Value :
//--------------------------------------------------
void ScalerOsdDrawWindowGradientSize(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
{
    // Set H Start
    ScalerOsdSetAddrWindow((BYTE)GET_OSD_WINDOW_GRANIENT_INDEX() * 0x20 + _P3A_F6_PT_3210_WIN_F_FB_WIN_GRADIENT0_H_STA_MSB);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, (usXStart >> 8) & 0x3F);
    ScalerOsdSetAddrWindow((BYTE)GET_OSD_WINDOW_GRANIENT_INDEX() * 0x20 + _P3A_F6_PT_3211_WIN_F_FB_WIN_GRADIENT0_H_STA_LSB);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, usXStart & 0xFF);

    // Set V Start
    ScalerOsdSetAddrWindow((BYTE)GET_OSD_WINDOW_GRANIENT_INDEX() * 0x20 + _P3A_F6_PT_3212_WIN_F_FB_WIN_GRADIENT0_V_STA_MSB);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, (usYStart >> 8) & 0x3F);
    ScalerOsdSetAddrWindow((BYTE)GET_OSD_WINDOW_GRANIENT_INDEX() * 0x20 + _P3A_F6_PT_3213_WIN_F_FB_WIN_GRADIENT0_V_STA_LSB);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, usYStart & 0xFF);

    // Set H End
    ScalerOsdSetAddrWindow((BYTE)GET_OSD_WINDOW_GRANIENT_INDEX() * 0x20 + _P3A_F6_PT_3214_WIN_F_FB_WIN_GRADIENT0_H_END_MSB);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, (usXEnd >> 8) & 0x3F);
    ScalerOsdSetAddrWindow((BYTE)GET_OSD_WINDOW_GRANIENT_INDEX() * 0x20 + _P3A_F6_PT_3215_WIN_F_FB_WIN_GRADIENT0_H_END_LSB);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, usXEnd & 0xFF);

    // Set V End
    ScalerOsdSetAddrWindow((BYTE)GET_OSD_WINDOW_GRANIENT_INDEX() * 0x20 + _P3A_F6_PT_3216_WIN_F_FB_WIN_GRADIENT0_V_END_MSB);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, (usYEnd >> 8) & 0x3F);
    ScalerOsdSetAddrWindow((BYTE)GET_OSD_WINDOW_GRANIENT_INDEX() * 0x20 + _P3A_F6_PT_3217_WIN_F_FB_WIN_GRADIENT0_V_END_LSB);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, usYEnd & 0xFF);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdWindow29SpecialFunction(_OSD_WINDOW_29_FUNCTION_DISABLE);
*/

//--------------------------------------------------
// Description  : Set window gradient step extension
// Input Value  : enumOsdWinGradientIdx
//                ucStep
//                ucDecimal
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowGradientStepIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucStep, BYTE ucDecimal)
{
    WORD usTempWindowNumber = 0;

    usTempWindowNumber = (enumOsdWinGradientIdx * 0x20);
    ScalerOsdSetAddrWindow(usTempWindowNumber + _P3A_F6_PT_3206_WIN_F_WIN_GRADIENT0_STEP);
    ScalerOsdSetDataPortWindow(ucStep);
    ScalerOsdSetAddrWindow(usTempWindowNumber + _P3A_F6_PT_3207_WIN_F_WIN_GRADIENT0_STEP_DEC);
    ScalerOsdSetDataPortWindow(ucDecimal & 0x07);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    SET_OSD_WINDOW_GRADIENT_ENABLE_R(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_ENABLE(_ENABLE);
    SET_OSD_WINDOW_NUMBER(5);
    SET_OSD_WINDOW_COLOR(4);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    ScalerOsdDrawWindow(XSTART(100), YSTART(200), XEND(300), YEND(400));
    ScalerOsdWindowGradientStep(_ENABLE, _OSD_WINDOW_5, 200);
*/

//--------------------------------------------------
// Description  : Set window highlight function
// Input Value  : bEnable              -> _ENABLE or _DISABLE
//                enumOsdWindowsType   -> _OSD_WINDOW_24 ~ _OSD_WINDOW_31
//                ucForegroundColor    -> 0 ~ 63
//                BackgroundColor      -> 0 ~ 63
//                CharactorBorderColor -> 0 ~ 63
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowHighlightFunction(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucForegroundColor, BYTE ucBackgroundColor, BYTE ucCharactorBorderColor)
{
    BYTE ucData = 0x00;
    WORD usAddrFG = 0x00;
    WORD usAddrBG = 0x00;

    ucCharactorBorderColor = ucCharactorBorderColor;

    switch(enumOsdWindowsType)
    {
        case _OSD_WINDOW_24:
            usAddrFG = _P3A_F6_PT_2430_WIN_F_WIN24_HL_EN;
            usAddrBG = _P3A_F6_PT_2431_WIN_F_WIN24_HL_BG_COLOR;
            break;

        case _OSD_WINDOW_25:
            usAddrFG = _P3A_F6_PT_2530_WIN_F_WIN25_HL_EN;
            usAddrBG = _P3A_F6_PT_2531_WIN_F_WIN25_HL_BG_COLOR;
            break;

        case _OSD_WINDOW_26:
            usAddrFG = _P3A_F6_PT_2630_WIN_F_WIN26_HL_EN;
            usAddrBG = _P3A_F6_PT_2631_WIN_F_WIN26_HL_BG_COLOR;
            break;

        case _OSD_WINDOW_27:
            usAddrFG = _P3A_F6_PT_2730_WIN_F_WIN27_HL_EN;
            usAddrBG = _P3A_F6_PT_2731_WIN_F_WIN27_HL_BG_COLOR;
            break;

        case _OSD_WINDOW_28:
            usAddrFG = _P3A_F6_PT_2830_WIN_F_WIN28_HL_EN;
            usAddrBG = _P3A_F6_PT_2831_WIN_F_WIN28_HL_BG_COLOR;
            break;

        case _OSD_WINDOW_29:
            usAddrFG = _P3A_F6_PT_2930_WIN_F_WIN29_HL_EN;
            usAddrBG = _P3A_F6_PT_2931_WIN_F_WIN29_HL_BG_COLOR;
            break;

        case _OSD_WINDOW_30:
            usAddrFG = _P3A_F6_PT_3030_WIN_F_WIN30_HL_EN;
            usAddrBG = _P3A_F6_PT_3031_WIN_F_WIN30_HL_BG_COLOR;
            break;

        case _OSD_WINDOW_31:
            usAddrFG = _P3A_F6_PT_3130_WIN_F_WIN31_HL_EN;
            usAddrBG = _P3A_F6_PT_3131_WIN_F_WIN31_HL_BG_COLOR;
            break;

        default:
            return;
    }

    ScalerOsdSetAddrWindow(usAddrFG);
    ucData = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
    ScalerOsdSetAddrWindow(usAddrFG);
    ucData = (ucData & ~0xBF) | (((BYTE)bEnable << 7) | (ucForegroundColor & 0x3F));
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucData);
    ScalerOsdSetAddrWindow(usAddrBG);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucBackgroundColor & _HW_OSD_PALETTE_BIT);

#if(_HW_OSD_PALETTE_BIT == _8_BIT)
    switch(enumOsdWindowsType)
    {
        case _OSD_WINDOW_24:
            usAddrFG = _P3A_F6_PT_240F_WIN_F_WIN24_ADR_0F;
            break;
        case _OSD_WINDOW_25:
            usAddrFG = _P3A_F6_PT_250F_WIN_F_WIN25_ADR_0F;
            break;
        case _OSD_WINDOW_26:
            usAddrFG = _P3A_F6_PT_260F_WIN_F_WIN26_ADR_0F;
            break;
        case _OSD_WINDOW_27:
            usAddrFG = _P3A_F6_PT_270F_WIN_F_WIN27_ADR_0F;
            break;
        case _OSD_WINDOW_28:
            usAddrFG = _P3A_F6_PT_280F_WIN_F_WIN28_ADR_0F;
            break;
        case _OSD_WINDOW_29:
            usAddrFG = _P3A_F6_PT_290F_WIN_F_WIN29_ADR_0F;
            break;
        case _OSD_WINDOW_30:
            usAddrFG = _P3A_F6_PT_300F_WIN_F_WIN30_ADR_0F;
            break;
        case _OSD_WINDOW_31:
            usAddrFG = _P3A_F6_PT_310F_WIN_F_WIN31_ADR_0F;
            break;
        default:
            return;
    }
    ScalerOsdSetAddrWindow(usAddrFG);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, (ucForegroundColor >> 6) & (_BIT1 | _BIT0)); // fg_color_hl[7:6]
#endif
}

//--------------------------------------------------
// Description  : Select window highlight function
// Input Value  : bSwitchEnable        -> switch window _ENABLE or _DISABLE
//                enumOsdWindowsType   -> _OSD_WINDOW_24 ~ _OSD_WINDOW_31
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowHighlightWinSwitch(bit bSwitchEnable, EnumOsdWindowsType enumOsdWindowsType)
{
    BYTE ucData = 0x00;
    WORD usAddr = 0x00;

    switch(enumOsdWindowsType)
    {
        case _OSD_WINDOW_24: // win24 <--> win5
            usAddr = _P3A_F6_PT_2430_WIN_F_WIN24_HL_EN;
            break;

        case _OSD_WINDOW_25: // win25 <--> win6
            usAddr = _P3A_F6_PT_2530_WIN_F_WIN25_HL_EN;
            break;

        case _OSD_WINDOW_26: // win26 <--> win7
            usAddr = _P3A_F6_PT_2630_WIN_F_WIN26_HL_EN;
            break;

        case _OSD_WINDOW_27: // win27 <--> win8
            usAddr = _P3A_F6_PT_2730_WIN_F_WIN27_HL_EN;
            break;

        case _OSD_WINDOW_28: // win28 <--> win11
            usAddr = _P3A_F6_PT_2830_WIN_F_WIN28_HL_EN;
            break;

        case _OSD_WINDOW_29: // win29 <--> win12
            usAddr = _P3A_F6_PT_2930_WIN_F_WIN29_HL_EN;
            break;

        case _OSD_WINDOW_30: // win30 <--> win13
            usAddr = _P3A_F6_PT_3030_WIN_F_WIN30_HL_EN;
            break;

        case _OSD_WINDOW_31: // win31 <--> win14
            usAddr = _P3A_F6_PT_3130_WIN_F_WIN31_HL_EN;
            break;

        default:
            return;
    }

    ScalerOsdSetAddrWindow(usAddr);
    ucData = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
    ScalerOsdSetAddrWindow(usAddr);
    ucData = (ucData & ~_BIT6) | ((BYTE)bSwitchEnable << 6);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucData);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdWindowHighlightFunction(_ENABLE, _OSD_WINDOW_4_1, 1, 3, 5);
*/

//--------------------------------------------------
// Description  : Enable/Disable window
// Input Value  : enumOsdWindowsType
// Input Value  : bWinOnOff
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowOnOFF(EnumOsdWindowsType enumOsdWindowsType, bit bWinOnOff)
{
    if(enumOsdWindowsType <= _OSD_WINDOW_7)
    {
        // _OSD_WINDOW_0 ~ _OSD_WINDOW_7
        ScalerSetBit(P3A_31_FRAME_CTRL_F_WIN_ENABLE_7_0, ~((BYTE)_BIT0 << enumOsdWindowsType), ((BYTE)bWinOnOff << enumOsdWindowsType));
    }
    else if(enumOsdWindowsType <= _OSD_WINDOW_15)
    {
        // _OSD_WINDOW_8 ~ _OSD_WINDOW_15
        ScalerSetBit(P3A_32_FRAME_CTRL_F_WIN_ENABLE_15_8, ~((BYTE)_BIT0 << (enumOsdWindowsType - _OSD_WINDOW_8)), ((BYTE)bWinOnOff << (enumOsdWindowsType - _OSD_WINDOW_8)));
    }
    else if(enumOsdWindowsType <= _OSD_WINDOW_23)
    {
        // _OSD_WINDOW_16 ~ _OSD_WINDOW_23
        ScalerSetBit(P3A_33_FRAME_CTRL_F_WIN_ENABLE_23_16, ~((BYTE)_BIT0 << (enumOsdWindowsType - _OSD_WINDOW_16)), ((BYTE)bWinOnOff << (enumOsdWindowsType - _OSD_WINDOW_16)));
    }
    else if(enumOsdWindowsType <= _OSD_WINDOW_31)
    {
        if((enumOsdWindowsType == _OSD_WINDOW_29) && (bWinOnOff == _OFF))
        {
            BYTE ucEffOpt = 0x00;

            ScalerOsdSetAddrWindow(_P3A_F6_PT_2901_WIN_F_WIN29_ADR_01);
            ucEffOpt = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);

            if(((ucEffOpt & 0x07) == _OSD_WINDOW_BUTTON_TYPE_BORDER) ||
               ((ucEffOpt & 0x07) == _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_1) ||
               ((ucEffOpt & 0x07) == _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_2))
            {
                ScalerOsdSetAddrWindow(_P3A_F6_PT_2901_WIN_F_WIN29_ADR_01);
                ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucEffOpt & (~(0x07))); // Set _OSD_WINDOW_BUTTON_TYPE_DISABLE
            }
        }

        // _OSD_WINDOW_24 ~ _OSD_WINDOW_31
        ScalerSetBit(P3A_34_FRAME_CTRL_F_WIN_ENABLE_31_24, ~((BYTE)_BIT0 << (enumOsdWindowsType - _OSD_WINDOW_24)), ((BYTE)bWinOnOff << (enumOsdWindowsType - _OSD_WINDOW_24)));
    }
}

//--------------------------------------------------
// Description  : Set window gradient saturated color
// Input Value  : enumOsdWindowsType ->
//                bversedGradient    -> _ENABLE or _DISABLE
//                ucColorR           -> window RED saturated color (0 ~ 255)
//                ucColorG           -> window GRN saturated color (0 ~ 255)
//                ucColorB           -> window BLU saturated color (0 ~ 255)
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowSaturatedColorSelectIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucColorR, BYTE ucColorG, BYTE ucColorB)
{
    WORD usTempWindowNumber = 0;

    usTempWindowNumber = (enumOsdWinGradientIdx * 0x20);
    ScalerOsdSetAddrWindow(usTempWindowNumber + _P3A_F6_PT_3208_WIN_F_WIN_GRADIENT0_SAT_R);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucColorR);
    ScalerOsdSetAddrWindow(usTempWindowNumber + _P3A_F6_PT_3209_WIN_F_WIN_GRADIENT0_SAT_G);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucColorG);
    ScalerOsdSetAddrWindow(usTempWindowNumber + _P3A_F6_PT_320A_WIN_F_WIN_GRADIENT0_SAT_B);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucColorB);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    SET_OSD_WINDOW_GRADIENT_ENABLE_R(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_MODE(_ENABLE);
    SET_OSD_WINDOW_GRADIENT_REVERSED_COLOR_MODE(_DISABLE);
    SET_OSD_WINDOW_GRADIENT_ENABLE(_ENABLE);
    SET_OSD_WINDOW_NUMBER(5);
    SET_OSD_WINDOW_COLOR(4);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    ScalerOsdDrawWindow(XSTART(100), YSTART(200), XEND(300), YEND(400));
    ScalerOsdWindowSaturatedColorSelect(_OSD_WINDOW_5, 242, 242, 242);
*/

//--------------------------------------------------
// Description  : Set window special color mask : _OSD_SPECIAL_COLOR_MASK_AND_OPERATION
// Input Value  : bEnable            -> _ENABLE or _DISABLE
//                enumOsdWindowsType
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowSpecialColorMaskANDOperation(bit bEnable, EnumOsdWindowsType enumOsdWindowsType)
{
    WORD usWin = 0;
    BYTE ucValue = 0;

    // Set Address
    usWin = ScalerOsdWindowRegisterMapping(enumOsdWindowsType);
    ScalerOsdSetAddrWindow(usWin + _P3A_F6_PT_0000_WIN_F_WIN0_ADR_00);

    // Set Data
    ucValue = ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
    ucValue = ((ucValue & (~_BIT1)) | ((BYTE)bEnable << 1));
    ScalerOsdSetAddrWindow(usWin + _P3A_F6_PT_0000_WIN_F_WIN0_ADR_00);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucValue);
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    SET_OSD_WINDOW_NUMBER(0);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    SET_OSD_WINDOW_COLOR(4);
    ScalerOsdDrawWindow(XSTART(100), YSTART(200), XEND(300), YEND(400));
    ScalerOsdWindowSpecialColorMask(_ENABLE, _OSD_WINDOW_0, _OSD_SPECIAL_COLOR_MASK_AND_OPERATION);
*/

