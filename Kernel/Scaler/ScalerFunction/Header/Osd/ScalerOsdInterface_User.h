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
// ID Code      : ScalerOsdInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//***************************************************************
// Command
//***************************************************************
//--------------------------------------------------
// Macros of Font Reorder control
//--------------------------------------------------
#define SCALEROSD_FONT_ROTATE_SETTING_GET()                     (MCU_FF03_TRIPLE_BYTES_OPERATION)
#define SCALEROSD_FONT_ROTATE_SETTING_SET(x)                    {\
                                                                    MCU_FF03_TRIPLE_BYTES_OPERATION = (x);\
                                                                }

#define SCALEROSD_FONT_ROTATE_1_2_BITS_SHIFT_SET(x)             {\
                                                                    MCU_FF04_SHIFT_BITS_NUMBER = (x);\
                                                                }

#define SCALEROSD_FONT_ROTATE_3_L_BITS_SHIFT_SET(x)             {\
                                                                    MCU_FF05_SHIFT_BYTE_ADDRESS = (x);\
                                                                }

#define SCALEROSD_FONT_ROTATE_INPUT_SET(x)                      {\
                                                                    MCU_FF06_INPUT_TRIPLE_BYTES = (x);\
                                                                }

#define SCALEROSD_FONT_ROTATE_ONPUT_GET()                       (MCU_FF07_RESULT_TRIPLE_BYTES)


//***************************************************************
// Windows
//***************************************************************
//--------------------------------------------------
// MACRO for Osd Window Number
//--------------------------------------------------
#define X_START(x)                                              (x)
#define Y_START(x)                                              (x)
#define X_END(x)                                                (x)
#define Y_END(x)                                                (x)

#define GET_OSD_WINDOW_NUMBER()                                 (g_stOsdWindows.b5WindowNumber)
#define SET_OSD_WINDOW_NUMBER(x)                                (g_stOsdWindows.b5WindowNumber = (x))

//--------------------------------------------------
// MACRO for Osd Window Enable
//--------------------------------------------------
#define GET_OSD_WINDOW_ENABLE()                                 (g_stOsdWindows.b1WindowEnable)
#define SET_OSD_WINDOW_ENABLE(x)                                (g_stOsdWindows.b1WindowEnable = (x))

//--------------------------------------------------
// MACRO for Osd Window Color
//--------------------------------------------------
#define GET_OSD_WINDOW_COLOR()                                  (g_stOsdWindows.ucWindowColor & _HW_OSD_PALETTE_BIT)
#define SET_OSD_WINDOW_COLOR(x)                                 (g_stOsdWindows.ucWindowColor = ((x) & _HW_OSD_PALETTE_BIT))

//--------------------------------------------------
// MACRO for Osd Window Blend Enable
//--------------------------------------------------
#define GET_OSD_WINDOW_BLEND_ENABLE()                           (g_stOsdWindows.b1WindowBlend)
#define SET_OSD_WINDOW_BLEND_ENABLE(x)                          (g_stOsdWindows.b1WindowBlend = (x))

//--------------------------------------------------
// MACRO for Osd Window Reference Delay
//--------------------------------------------------
#define GET_OSD_WINDOW_REFERENCE_DELAY()                        (g_stOsdWindows.ucWindowReferenceDelay & ((_HW_FOSD_MAP_C_D_SUPPORT == _ON) ? (_BIT1 | _BIT0) : (_BIT0)))
#define SET_OSD_WINDOW_REFERENCE_DELAY(x)                       (g_stOsdWindows.ucWindowReferenceDelay = ((x) & ((_HW_FOSD_MAP_C_D_SUPPORT == _ON) ? (_BIT1 | _BIT0) : (_BIT0))))

//--------------------------------------------------
// MACRO for Osd Window Rotation Function Enable
//--------------------------------------------------
#define GET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE()               (g_stOsdWindows.b1WindowRotationFunctionEnable)
#define SET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE(x)              (g_stOsdWindows.b1WindowRotationFunctionEnable = (x))

//--------------------------------------------------
// MACRO for Osd Window Wait Den Stop
//--------------------------------------------------
#define GET_OSD_WINDOW_WAIT_DEN_STOP()                          (g_stOsdWindows.b1WindowWaitEvenStop)
#define SET_OSD_WINDOW_WAIT_DEN_STOP(x)                         (g_stOsdWindows.b1WindowWaitEvenStop = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Level Step
//--------------------------------------------------
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_1                       0
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_2                       1
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_3                       2
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_4                       3

//--------------------------------------------------
// MACRO for Osd Window Gradient Level Per
//--------------------------------------------------
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_1                        1
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_2                        2
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_3                        3
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_4                        4
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_5                        5
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_6                        6
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_7                        7
#define _OSD_WINDOW_GRADIENT_LEVEL_PER_8                        8

//--------------------------------------------------
// MACRO for Osd Window Shadow/Border/3D
//--------------------------------------------------
#define _OSD_WINDOW_BUTTON_TYPE_DISABLE                         0
#define _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_1                     1
#define _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_2                     2
#define _OSD_WINDOW_BUTTON_TYPE_ROUNDED                         5
#define _OSD_WINDOW_BUTTON_TYPE_CHESSBOARD                      6
#define _OSD_WINDOW_BUTTON_TYPE_BORDER                          7

#define GET_OSD_WINDOW_BUTTON_TYPE()                            (g_stOsdWindows.b3WindowType)
#define SET_OSD_WINDOW_BUTTON_TYPE(x)                           (g_stOsdWindows.b3WindowType = (x))

//--------------------------------------------------
// MACRO for Osd Window Rounded Size
//--------------------------------------------------
// _OSD_ROUNDED_WIN_SIZE_8X8, _OSD_ROUNDED_WIN_SIZE_16X16
#define GET_OSD_WINDOW_ROUNDED_SIZE()                           (g_stOsdWindows.b1WindowRoundedSize)
#define SET_OSD_WINDOW_ROUNDED_SIZE(x)                          (g_stOsdWindows.b1WindowRoundedSize = (x))

//--------------------------------------------------
// MACRO for Osd Window Color Mask : And Operation
//--------------------------------------------------
#define GET_OSD_WINDOW_COLOR_MASK_AND()                         (g_stOsdWindows.b1WindowColorMaskAndOp)
#define SET_OSD_WINDOW_COLOR_MASK_AND(x)                        (g_stOsdWindows.b1WindowColorMaskAndOp = (x))

//--------------------------------------------------
// MACRO for Osd Window Eff Color 1
//--------------------------------------------------
#define GET_OSD_WINDOW_EFF_COLOR_1()                            (g_stOsdWindows.ucWindowEffColor1 & _HW_OSD_PALETTE_BIT)
#define SET_OSD_WINDOW_EFF_COLOR_1(x)                           (g_stOsdWindows.ucWindowEffColor1 = ((x) & _HW_OSD_PALETTE_BIT))
#define GET_OSD_WINDOW_COLOR_BORDER()                           (g_stOsdWindows.ucWindowEffColor1 & _HW_OSD_PALETTE_BIT)
#define SET_OSD_WINDOW_COLOR_BORDER(x)                          (g_stOsdWindows.ucWindowEffColor1 = ((x) & _HW_OSD_PALETTE_BIT))

//--------------------------------------------------
// MACRO for Osd Window Eff Color 2
//--------------------------------------------------
#define GET_OSD_WINDOW_EFF_COLOR_2()                            (g_stOsdWindows.ucWindowEffColor2 & _HW_OSD_PALETTE_BIT)
#define SET_OSD_WINDOW_EFF_COLOR_2(x)                           (g_stOsdWindows.ucWindowEffColor2 = ((x) & _HW_OSD_PALETTE_BIT))

//--------------------------------------------------
// MACRO for Osd Window Border Pixel Width
//--------------------------------------------------
// 000 ~ 111 : 1 ~ 8 Pixel
#define GET_OSD_WINDOW_BORDER_PIXEL_WIDTH()                     (g_stOsdWindows.b5WindowBorderPixelWidth)
#define SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(x)                    (g_stOsdWindows.b5WindowBorderPixelWidth = (x))

//--------------------------------------------------
// MACRO for Osd Window Border Pixel Height
//--------------------------------------------------
#define GET_OSD_WINDOW_BORDER_PIXEL_HEIGHT()                    (g_stOsdWindows.b5WindowBorderPixelHeight)
#define SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(x)                   (g_stOsdWindows.b5WindowBorderPixelHeight = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Color
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_COLOR()                         (g_stOsdWindowsGradient.ucWindowGradientColor & _HW_OSD_PALETTE_BIT)
#define SET_OSD_WINDOW_GRADIENT_COLOR(x)                        (g_stOsdWindowsGradient.ucWindowGradientColor = ((x) & _HW_OSD_PALETTE_BIT))

//--------------------------------------------------
// MACRO for Osd Window Gradient Level Color R
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_R()                 (g_stOsdWindowsGradient.ucWindowGradientLevelColorR)
#define SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_R(x)                (g_stOsdWindowsGradient.ucWindowGradientLevelColorR = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Level Color G
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_G()                 (g_stOsdWindowsGradient.ucWindowGradientLevelColorG)
#define SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_G(x)                (g_stOsdWindowsGradient.ucWindowGradientLevelColorG = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Level Color B
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_B()                 (g_stOsdWindowsGradient.ucWindowGradientLevelColorB)
#define SET_OSD_WINDOW_GRADIENT_LEVEL_COLOR_B(x)                (g_stOsdWindowsGradient.ucWindowGradientLevelColorB = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Level Step : 0 ~ 255
//--------------------------------------------------
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_1                       0
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_2                       1
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_3                       2
#define _OSD_WINDOW_GRADIENT_LEVEL_STEP_4                       3

#define GET_OSD_WINDOW_GRADIENT_LEVEL_SETP()                    (g_stOsdWindowsGradient.ucWindowGradientLevelStep)
#define SET_OSD_WINDOW_GRADIENT_LEVEL_SETP(x)                   (g_stOsdWindowsGradient.ucWindowGradientLevelStep = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Level Step Decimal
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_LEVEL_SETP_DEC()                (g_stOsdWindowsGradient.b3WindowGradientLevelStepDec)
#define SET_OSD_WINDOW_GRADIENT_LEVEL_SETP_DEC(x)               (g_stOsdWindowsGradient.b3WindowGradientLevelStepDec = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Effective
//--------------------------------------------------
#define GET_OSD_WINDOW_GRANIENT_WIN()                           (g_stOsdWindowsGradient.b6WindowGradientEffective)
#define SET_OSD_WINDOW_GRANIENT_WIN(x)                          (g_stOsdWindowsGradient.b6WindowGradientEffective = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Index
//--------------------------------------------------
#define GET_OSD_WINDOW_GRANIENT_INDEX()                         (g_stOsdWindowsGradient.ucWindowGradientIndex)
#define SET_OSD_WINDOW_GRANIENT_INDEX(x)                        (g_stOsdWindowsGradient.ucWindowGradientIndex = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient R
//--------------------------------------------------
#define _OSD_WINDOW_GRADIENT_POLARITY_DECREASE                  0
#define _OSD_WINDOW_GRADIENT_POLARITY_INCREASE                  1

#define GET_OSD_WINDOW_GRADIENT_POLARITY_R()                    (g_stOsdWindowsGradient.b1WindowGradientPolarityR)
#define SET_OSD_WINDOW_GRADIENT_POLARITY_R(x)                   (g_stOsdWindowsGradient.b1WindowGradientPolarityR = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient G
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_POLARITY_G()                    (g_stOsdWindowsGradient.b1WindowGradientPolarityG)
#define SET_OSD_WINDOW_GRADIENT_POLARITY_G(x)                   (g_stOsdWindowsGradient.b1WindowGradientPolarityG = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient B
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_POLARITY_B()                    (g_stOsdWindowsGradient.b1WindowGradientPolarityB)
#define SET_OSD_WINDOW_GRADIENT_POLARITY_B(x)                   (g_stOsdWindowsGradient.b1WindowGradientPolarityB = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Enable R
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_ENABLE_R()                      (g_stOsdWindowsGradient.b1WindowGradientEnableR)
#define SET_OSD_WINDOW_GRADIENT_ENABLE_R(x)                     (g_stOsdWindowsGradient.b1WindowGradientEnableR = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Enable G
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_ENABLE_G()                      (g_stOsdWindowsGradient.b1WindowGradientEnableG)
#define SET_OSD_WINDOW_GRADIENT_ENABLE_G(x)                     (g_stOsdWindowsGradient.b1WindowGradientEnableG = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Enable B
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_ENABLE_B()                      (g_stOsdWindowsGradient.b1WindowGradientEnableB)
#define SET_OSD_WINDOW_GRADIENT_ENABLE_B(x)                     (g_stOsdWindowsGradient.b1WindowGradientEnableB = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Saturated Color Mode
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_MODE()          (g_stOsdWindowsGradient.b1WindowGradientSaturatedColorMode)
#define SET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_MODE(x)         (g_stOsdWindowsGradient.b1WindowGradientSaturatedColorMode = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Saturated Color R
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_R()             (g_stOsdWindowsGradient.ucWindowGradienttSaturatedColorR)
#define SET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_R(x)            (g_stOsdWindowsGradient.ucWindowGradienttSaturatedColorR = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Saturated Color G
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_G()             (g_stOsdWindowsGradient.ucWindowGradienttSaturatedColorG)
#define SET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_G(x)            (g_stOsdWindowsGradient.ucWindowGradienttSaturatedColorG = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Saturated Color B
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_B()             (g_stOsdWindowsGradient.ucWindowGradienttSaturatedColorB)
#define SET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_B(x)            (g_stOsdWindowsGradient.ucWindowGradienttSaturatedColorB = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Reversed Color Mode
//--------------------------------------------------
#define GET_OSD_WINDOW_GRADIENT_REVERSED_COLOR_MODE()           (g_stOsdWindowsGradient.b1WindowGradientReversedColorMode)
#define SET_OSD_WINDOW_GRADIENT_REVERSED_COLOR_MODE(x)          (g_stOsdWindowsGradient.b1WindowGradientReversedColorMode = (x))

//--------------------------------------------------
// MACRO for Osd Window Gradient Direction
//--------------------------------------------------
#define _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL               0
#define _OSD_WINDOW_GRADIENT_DIRECTION_VERTICAL                 1

#define GET_OSD_WINDOW_GRADIENT_DIRECTION()                     (g_stOsdWindowsGradient.b1WindowGradientDirection)
#define SET_OSD_WINDOW_GRADIENT_DIRECTION(x)                    (g_stOsdWindowsGradient.b1WindowGradientDirection = (x))

//--------------------------------------------------
// MACRO for Osd Grid Window Number
//--------------------------------------------------
#define GET_OSD_GRID_WINDOW_NUMBER()                            (g_stOsdWindowsGridWindow.b3GridLineWindowNumber)
#define SET_OSD_GRID_WINDOW_NUMBER(x)                           (g_stOsdWindowsGridWindow.b3GridLineWindowNumber = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Width
//--------------------------------------------------
#define GET_OSD_GRID_LINE_WIDTH()                               (g_stOsdWindowsGridWindow.ucGridLineWidth)
#define SET_OSD_GRID_LINE_WIDTH(x)                              (g_stOsdWindowsGridWindow.ucGridLineWidth = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Color
//--------------------------------------------------
#define GET_OSD_GRID_LINE_COLOR()                               (g_stOsdWindowsGridWindow.ucGridLineColor & _HW_OSD_PALETTE_BIT)
#define SET_OSD_GRID_LINE_COLOR(x)                              (g_stOsdWindowsGridWindow.ucGridLineColor = ((x) & _HW_OSD_PALETTE_BIT))

//--------------------------------------------------
// MACRO for Osd Grid Line Horizontal Enable
//--------------------------------------------------
#define GET_OSD_GRID_LINE_HORIZONTAL_ENABLE()                   (g_stOsdWindowsGridWindow.b1GridLineHorizontalEnable)
#define SET_OSD_GRID_LINE_HORIZONTAL_ENABLE(x)                  (g_stOsdWindowsGridWindow.b1GridLineHorizontalEnable = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Vertical Enable
//--------------------------------------------------
#define GET_OSD_GRID_LINE_VERTICAL_ENABLE()                     (g_stOsdWindowsGridWindow.b1GridLineVerticalEnable)
#define SET_OSD_GRID_LINE_VERTICAL_ENABLE(x)                    (g_stOsdWindowsGridWindow.b1GridLineVerticalEnable = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Offset
//--------------------------------------------------
#define GET_OSD_GRID_LINE_H_OFFSET()                            (g_stOsdWindowsGridWindow.ucGridLineHOffset)
#define SET_OSD_GRID_LINE_H_OFFSET(x)                           (g_stOsdWindowsGridWindow.ucGridLineHOffset = (x))
#define GET_OSD_GRID_LINE_V_OFFSET()                            (g_stOsdWindowsGridWindow.ucGridLineVOffset)
#define SET_OSD_GRID_LINE_V_OFFSET(x)                           (g_stOsdWindowsGridWindow.ucGridLineVOffset = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Pitch
//--------------------------------------------------
#define GET_OSD_GRID_LINE_PITCH()                               (g_stOsdWindowsGridWindow.b15GridLinePitch)
#define SET_OSD_GRID_LINE_PITCH(x)                              (g_stOsdWindowsGridWindow.b15GridLinePitch = (x))

//--------------------------------------------------
// MACRO for Osd Grid Line Function Enable
//--------------------------------------------------
#define GET_OSD_GRID_LINE_FUNCTION_ENABLE()                     (g_stOsdWindowsGridWindow.b1GridFunctionEnable)
#define SET_OSD_GRID_LINE_FUNCTION_ENABLE(x)                    (g_stOsdWindowsGridWindow.b1GridFunctionEnable = (x))



//***************************************************************
// SRAM
//***************************************************************
//--------------------------------------------------
// ScalerOsdSramAddressCount.c
//--------------------------------------------------
#define _OSD_MAP_B_ROW_OFFSET                                   200

#define ROW_MAPA(x)                                             (x)
#define ROW_MAPB(x)                                             ((x) + _OSD_MAP_B_ROW_OFFSET)

#define GET_OSD_MAPA_COL_MAX()                                  (g_usOsdSRAMColAMax)
#define SET_OSD_MAPA_COL_MAX(x)                                 (g_usOsdSRAMColAMax = (x))

#define GET_OSD_MAPB_COL_MAX()                                  (g_usOsdSRAMColBMax)
#define SET_OSD_MAPB_COL_MAX(x)                                 (g_usOsdSRAMColBMax = (x))

#define GET_OSD_SET_MAPA_AND_MAP_B()                            (g_bOsdSetMapAAndMapB)
#define SET_OSD_SET_MAPA_AND_MAP_B(x)                           (g_bOsdSetMapAAndMapB = (x))

//--------------------------------------------------
// ScalerOsdHardwareVLC.c
//--------------------------------------------------
#define _OSD_ROTATE_HARDWARE_ROTATION_DISABLE                   (0x00)
#define _OSD_ROTATE_HARDWARE_ROTATION_ENABLE                    (_BIT7)

#define _OSD_COMPRESSION_DISABLE                                (0x00)
#define _OSD_COMPRESSION_ENABLE                                 (_BIT0)


#define VLC_TABLE_SIZE(x)                                       (((WORD)(x)[8] << 8) + (x)[9])

//--------------------------------------------------
// ScalerOsdChange4BitColor.c
//--------------------------------------------------
#define _OSD_4BIT_PALETTE_00_01_02_03                           0
#define _OSD_4BIT_PALETTE_16_17_18_19                           _BIT0
#define _OSD_4BIT_PALETTE_32_33_34_35                           _BIT1
#define _OSD_4BIT_PALETTE_48_49_50_51                           (_BIT1 | _BIT0)

#define _OSD_4BIT_PALETTE_04_05_06_07                           0
#define _OSD_4BIT_PALETTE_20_21_22_23                           _BIT2
#define _OSD_4BIT_PALETTE_36_37_38_39                           _BIT3
#define _OSD_4BIT_PALETTE_52_53_54_55                           (_BIT3 | _BIT2)

#define _OSD_4BIT_PALETTE_08_09_10_11                           0
#define _OSD_4BIT_PALETTE_24_25_26_27                           _BIT4
#define _OSD_4BIT_PALETTE_40_41_42_43                           _BIT5
#define _OSD_4BIT_PALETTE_56_57_58_59                           (_BIT5 | _BIT4)

#define _OSD_4BIT_PALETTE_12_13_14_15                           0
#define _OSD_4BIT_PALETTE_28_29_30_31                           _BIT6
#define _OSD_4BIT_PALETTE_44_45_46_47                           _BIT7
#define _OSD_4BIT_PALETTE_50_61_62_63                           (_BIT7 | _BIT6)

//--------------------------------------------------
// ScalerOsdChange1BitColor.c
//--------------------------------------------------
#define FG_COLOR(x)                                             (x)
#define BG_COLOR(x)                                             (x)

//--------------------------------------------------
// ScalerOsdChange2BitColor.c
//--------------------------------------------------
#define COLOR_00(x)                                             (x)
#define COLOR_01(x)                                             (x)
#define COLOR_10(x)                                             (x)
#define COLOR_11(x)                                             (x)


//***************************************************************
// Function
//***************************************************************
//--------------------------------------------------
// ScalerOsdPosition.c
//--------------------------------------------------
#define X_POS(x)                                                (x)
#define Y_POS(x)                                                (x)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Osd Options
//--------------------------------------------------
typedef enum
{
    _OSD_A,
    _OSD_B,
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
    _OSD_C,
    _OSD_D,
#endif
} EnumOsdMapType;

typedef enum
{
    _OSD_ROTATE_DEGREE_0,
    _OSD_ROTATE_DEGREE_90,
    _OSD_ROTATE_DEGREE_270,
    _OSD_ROTATE_DEGREE_180,
} EnumOsdRotateType;

typedef enum
{
    _OSD_BLANK_FONT = 0x00,
} EnumOsdBlankType;

typedef enum
{
    _OSD_TRANSPARENCY_DISABLE = 0x00,
    _OSD_TRANSPARENCY_ONLY_WINDOW,
    _OSD_TRANSPARENCY_ALL,
    _OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND,
} EnumOsdTransparencyType;

typedef enum
{
    _OSD_POSITION_GLOBAL_A,
    _OSD_POSITION_GLOBAL_B,
    _OSD_POSITION_GLOBAL_1 = _OSD_POSITION_GLOBAL_A,
    _OSD_POSITION_GLOBAL_2 = _OSD_POSITION_GLOBAL_B,
    _OSD_POSITION_FONT_A,
    _OSD_POSITION_FONT_B,

#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
    _OSD_POSITION_GLOBAL_3,
    _OSD_POSITION_GLOBAL_4,
    _OSD_POSITION_FONT_C,
    _OSD_POSITION_FONT_D,
#endif
} EnumOsdPositionType;

typedef enum
{
    _OSD_FIRST_DELAY,
    _OSD_SECOND_DELAY,
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
    _OSD_THIRD_DELAY,
    _OSD_FOURTH_DELAY,
#endif
} EnumOsdReferenceType;

typedef enum
{
    _OSD_2BIT_CHAR_BIT7_BY_CHANGE_PALETTE,
    _OSD_2BIT_CHAR_BIT7_BY_SELECT_FONT,
} EnumOsd2BitCharBit7Type;

typedef enum
{
    _OSD_4BIT_BACKGROUND_TO_BYTE2,
    _OSD_4BIT_BACKGROUND_TO_BYTE0,
} EnumOsd4BitBackgroundType;

typedef enum
{
    _OSD_FONT_LIB_ROTATION_DISABLE,
    _OSD_FONT_LIB_ROTATION_ENABLE,
} EnumOsdRotateFontLib;

typedef enum
{
    _OSD_WINDOW_0,
    _OSD_WINDOW_1,
    _OSD_WINDOW_2,
    _OSD_WINDOW_3,
    _OSD_WINDOW_4,
    _OSD_WINDOW_5,
    _OSD_WINDOW_6,
    _OSD_WINDOW_7,
    _OSD_WINDOW_8,
    _OSD_WINDOW_9,

    _OSD_WINDOW_10,
    _OSD_WINDOW_11,
    _OSD_WINDOW_12,
    _OSD_WINDOW_13,
    _OSD_WINDOW_14,
    _OSD_WINDOW_15,
    _OSD_WINDOW_16,
    _OSD_WINDOW_17,
    _OSD_WINDOW_18,
    _OSD_WINDOW_19,
    _OSD_WINDOW_20,
    _OSD_WINDOW_21,
    _OSD_WINDOW_22,
    _OSD_WINDOW_23,
    _OSD_WINDOW_24,
    _OSD_WINDOW_25,
    _OSD_WINDOW_26,
    _OSD_WINDOW_27,
    _OSD_WINDOW_28,
    _OSD_WINDOW_29,
    _OSD_WINDOW_30,
    _OSD_WINDOW_31,

    _OSD_WINDOW_ALL,
} EnumOsdWindowsType;

typedef enum
{
    _OSD_MAP_A_REMAPPING_DISABLE,
    _OSD_MAP_A_REMAPPING_ENABLE,
} EnumOsdRotateMapA;

typedef enum
{
    _OSD_MAP_B_REMAPPING_DISABLE,
    _OSD_MAP_B_REMAPPING_ENABLE,
} EnumOsdRotateMapB;

typedef enum
{
    _OSD_MAP_C_REMAPPING_DISABLE,
    _OSD_MAP_C_REMAPPING_ENABLE,
} EnumOsdRotateMapC;

typedef enum
{
    _OSD_MAP_D_REMAPPING_DISABLE,
    _OSD_MAP_D_REMAPPING_ENABLE,
} EnumOsdRotateMapD;

typedef enum
{
    _OSD_DB_DISABLE = 0x00,
    _OSD_DB_NORMAL,
    _OSD_DB_WAIT_READY_AND_DVS,
} EnumOsdDoubleBufferType;

typedef enum
{
    _OSD_WINDOW_28_FUNCTION_DISABLE,
    _OSD_WINDOW_28_FUNCTION_NO_BLENDING_BOTH,
    _OSD_WINDOW_28_FUNCTION_NO_BLENDING_FOREGROUND,
    _OSD_WINDOW_28_FUNCTION_NO_BLENDING_BACKGROUND,
    _OSD_WINDOW_28_FUNCTION_BLENDING_BOTH,
} EnumOsdWindow28FunctionType;

typedef enum
{
    _OSD_WINDOW_29_FUNCTION_DISABLE,
    _OSD_WINDOW_29_FUNCTION_NO_BLENDING_BOTH,
    _OSD_WINDOW_29_FUNCTION_NO_BLENDING_FOREGROUND,
    _OSD_WINDOW_29_FUNCTION_NO_BLENDING_BACKGROUND,
    _OSD_WINDOW_29_FUNCTION_BLENDING_BOTH,
    _OSD_WINDOW_29_FUNCTION_MASK_REGION_APPEAR,
    _OSD_WINDOW_29_FUNCTION_MASK_REGION_TRANSPARENT_ALL,
    _OSD_WINDOW_29_FUNCTION_MASK_REGION_TRANSPARENT_FONT,
} EnumOsdWindow29FunctionType;

typedef enum
{
    _OSD_FONT_ABOVE_WIN_31,
    _OSD_FONT_ABOVE_WIN_30,
    _OSD_FONT_ABOVE_WIN_29,
    _OSD_FONT_ABOVE_WIN_28,
    _OSD_FONT_ABOVE_WIN_27,
    _OSD_FONT_ABOVE_WIN_26,
    _OSD_FONT_ABOVE_WIN_25,
    _OSD_FONT_ABOVE_WIN_24,
} EnumOsdFontPriorityType;

typedef enum
{
    _OSD_WIN_GRADIENT_0,
    _OSD_WIN_GRADIENT_1,
    _OSD_WIN_GRADIENT_2,
    _OSD_WIN_GRADIENT_3,
    _OSD_WIN_GRADIENT_4,
    _OSD_WIN_GRADIENT_5,
    _OSD_WIN_GRADIENT_END,
} EnumOsdWinGradientType;

typedef enum
{
    _OSD_FONT_SCALING_BOUNDARY_NEIGHTBOOR,
    _OSD_FONT_SCALING_RESERVED,
    _OSD_FONT_SCALING_BOUNDARY_FAT,
} EnumOsdFontScalingBoundaryType;

typedef enum
{
    _OSD_ROUNDED_WIN_SIZE_8X8 = 0x00,
    _OSD_ROUNDED_WIN_SIZE_16X16,
} EnumOsdRoundedWindowType;

typedef enum
{
    _OSD_DECODE_COMPRESSED = 0x00,
    _OSD_DECODE_NON_COMPRESSED = _BIT1,
} EnumOsdDecodeCompressionType;

typedef enum
{
    _OSD_FRONT,
    _OSD_BACK,
} EnumOsdFBSel;

//--------------------------------------------------
// ScalerOsdDrawWindow.c
//--------------------------------------------------
typedef struct
{
    BYTE ucWindowColor;
    BYTE b1WindowEnable                      : 1;
    BYTE b1WindowBlend                       : 1;
    BYTE ucWindowEffColor1;
    BYTE b1WindowRotationFunctionEnable      : 1;
    BYTE ucWindowReferenceDelay;

    BYTE b5WindowNumber                      : 5;
    BYTE b3WindowType                        : 3;

    BYTE ucWindowEffColor2;
    BYTE b1WindowColorMaskAndOp              : 1;
    BYTE b1WindowRoundedSize                 : 1;
    BYTE b1WindowWaitEvenStop                : 1;
    BYTE b5WindowBorderPixelWidth            : 5;
    BYTE b5WindowBorderPixelHeight           : 5;
} StructOsdWindow;

typedef struct
{
    BYTE b6WindowGradientEffective           : 6;
    BYTE b1WindowGradientPolarityR           : 1;
    BYTE b1WindowGradientEnableR             : 1;

    BYTE ucWindowGradientColor;
    BYTE b1WindowGradientPolarityG           : 1;
    BYTE b1WindowGradientEnableG             : 1;

    BYTE b3WindowGradientLevelStepDec        : 3;
    BYTE b1WindowGradientPolarityB           : 1;
    BYTE b1WindowGradientEnableB             : 1;

    BYTE b1WindowGradientDirection           : 1;
    BYTE b1WindowGradientSaturatedColorMode  : 1;
    BYTE b1WindowGradientReversedColorMode   : 1;

    BYTE ucWindowGradienttSaturatedColorR;
    BYTE ucWindowGradienttSaturatedColorG;
    BYTE ucWindowGradienttSaturatedColorB;

    BYTE ucWindowGradientLevelStep;

    BYTE ucWindowGradientLevelColorR;
    BYTE ucWindowGradientLevelColorG;
    BYTE ucWindowGradientLevelColorB;

    BYTE ucWindowGradientIndex;
} StructOsdWindowGradient;

//--------------------------------------------------
// ScalerOsdDrawGridLine.c
//--------------------------------------------------
typedef struct
{
    BYTE ucGridLineColor;
    BYTE b1GridLineHorizontalEnable         : 1;
    BYTE b1GridLineVerticalEnable           : 1;

    BYTE ucGridLineWidth;

    BYTE b1GridFunctionEnable               : 1;
    BYTE b3GridLineWindowNumber             : 3;
    WORD b15GridLinePitch                   : 15;

    BYTE ucGridLineHOffset;
    BYTE ucGridLineVOffset;
} StructOsdGridWindow;

typedef enum
{
    _OSD_WIN_CONTROL = 0,
    _OSD_SRAM_FONT = _BIT1,
    _OSD_SRAM_COMMAND = _BIT2,
    _OSD_SRAM = (_OSD_SRAM_FONT | _OSD_SRAM_COMMAND),
} EnumOsdAddrIndicateType;

typedef enum
{
    _OSD_WITHOUT_DB = 0,
    _OSD_WITH_DB = _BIT7,
} EnumOsdDBufType;

typedef enum
{
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
    _OSD_BYTE3 = 1,
    _OSD_BYTE0,
    _OSD_BYTE0_BYTE3,
    _OSD_BYTE1,
    _OSD_BYTE1_BYTE3,
    _OSD_BYTE0_BYTE1,
    _OSD_BYTE0_BYTE1_BYTE3,
    _OSD_BYTE2,
    _OSD_BYTE2_BYTE3,
    _OSD_BYTE0_BYTE2,
    _OSD_BYTE0_BYTE2_BYTE3,
    _OSD_BYTE1_BYTE2,
    _OSD_BYTE1_BYTE2_BYTE3,
#else
    _OSD_BYTE0 = 1,
    _OSD_BYTE1,
    _OSD_BYTE0_BYTE1,
    _OSD_BYTE2,
    _OSD_BYTE0_BYTE2,
    _OSD_BYTE1_BYTE2,
#endif

    _OSD_BYTEALL,
} EnumOsdWriteType;

#if(_HW_FOSD_HW_PUT_STRING_GEN_TYPE == _OSD_HW_PUT_STRING_GEN_1)
typedef enum
{
    _OSD_1_BIT_FONT = 0,
    _OSD_2_BIT_FONT,
    _OSD_4_BIT_FONT,
} EnumOsdHWPutStringFontSelType;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//--------------------------------------------------
// ScalerOsdSramAddressCount.c
//--------------------------------------------------
extern WORD g_usOsdSRAMColAMax;
extern WORD g_usOsdSRAMColBMax;

//--------------------------------------------------
// ScalerOsdDrawWindow.c
//--------------------------------------------------
extern StructOsdWindow g_stOsdWindows;
extern StructOsdWindowGradient g_stOsdWindowsGradient;

//--------------------------------------------------
// ScalerOsdDrawGridLine.c
//--------------------------------------------------
extern StructOsdGridWindow g_stOsdWindowsGridWindow;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

