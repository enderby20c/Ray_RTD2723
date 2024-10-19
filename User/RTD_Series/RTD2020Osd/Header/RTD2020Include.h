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
// ID Code      : RTD2020Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include <RTD2020Project.h>
#include <RTD2020OsdTextTableDefine.h>
#include <RTD2020ResourceInclude.h>


#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _A0_INPUT_TYPE                              (_OPTION_ICON_END + (_A0_INPUT_PORT_TYPE & 0x0F))
#define _D0_INPUT_TYPE                              (_OPTION_ICON_END + (_D0_INPUT_PORT_TYPE & 0x0F))
#define _D1_INPUT_TYPE                              (_OPTION_ICON_END + (_D1_INPUT_PORT_TYPE & 0x0F))
#define _D2_INPUT_TYPE                              (_OPTION_ICON_END + (_D2_INPUT_PORT_TYPE & 0x0F))
#define _D3_INPUT_TYPE                              (_OPTION_ICON_END + (_D3_INPUT_PORT_TYPE & 0x0F))
#define _D4_INPUT_TYPE                              (_OPTION_ICON_END + (_D4_INPUT_PORT_TYPE & 0x0F))
#define _D5_INPUT_TYPE                              (_OPTION_ICON_END + (_D5_INPUT_PORT_TYPE & 0x0F))
#define _D6_INPUT_TYPE                              (_OPTION_ICON_END + (_D6_INPUT_PORT_TYPE & 0x0F))
#define _D7_INPUT_TYPE                              (_OPTION_ICON_END + (_D7_INPUT_PORT_TYPE & 0x0F))
#define _D8_INPUT_TYPE                              (_OPTION_ICON_END + (_D8_INPUT_PORT_TYPE & 0x0F))
#define _D9_INPUT_TYPE                              (_OPTION_ICON_END + (_D9_INPUT_PORT_TYPE & 0x0F))

//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#define _CONTRAST_MAX                               2848
#define _CONTRAST_MIN                               1248
#define _CONTRAST_CENTER                            (((_CONTRAST_MAX - _CONTRAST_MIN) / 2) + _CONTRAST_MIN)

//--------------------------------------------------
// Definitions of Backlight Range
//--------------------------------------------------
#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
#define _BACKLIGHT_MAX                              255
#else
#define _BACKLIGHT_MAX                              4095
#endif
#define _BACKLIGHT_MIN                              30
#define _BACKLIGHT_CENTER                           (((_BACKLIGHT_MAX - _BACKLIGHT_MIN) / 2) + _BACKLIGHT_MIN)

//--------------------------------------------------
// Definitions of Brightness Range
//--------------------------------------------------
#define _BRIGHTNESS_MAX                             712
#define _BRIGHTNESS_MIN                             312
#define _BRIGHTNESS_CENTER                          (((_BRIGHTNESS_MAX - _BRIGHTNESS_MIN) / 2) + _BRIGHTNESS_MIN)

//--------------------------------------------------
// Definitions of Sharpness Range
//--------------------------------------------------
#define _SHARPNESS_MAX                              4
#define _SHARPNESS_MIN                              0
#define _SHARPNESS_CENTER                           (((_SHARPNESS_MAX - _SHARPNESS_MIN) / 2) + _SHARPNESS_MIN)
//--------------------------------------------------
// Definitions of Phase Range
//--------------------------------------------------
#define _OSD_PHASE_MAX                              100
#define _OSD_PHASE_MIN                              0

//--------------------------------------------------
// Definitions of Colortemp User RGB
//--------------------------------------------------
#define _USER_RGB_MAX                               255
#define _USER_RGB_MIN                               0
#define _USER_RGB_CENTER                            (((_USER_RGB_MAX - _USER_RGB_MIN) / 2) + _USER_RGB_MIN)

//--------------------------------------------------
// Definitions of OD Gain Range
//--------------------------------------------------
#define _OD_GAIN_MAX                                127
#define _OD_GAIN_MIN                                0
#define _OD_GAIN_CENTER                             (((_OD_GAIN_MAX - _OD_GAIN_MIN) / 2) + _OD_GAIN_MIN)

//--------------------------------------------------
// Definitions of 3D EFFECT
//--------------------------------------------------
#define _3D_EFFECT_MAX                              0x10
#define _3D_EFFECT_MIN                              0x00

//--------------------------------------------------
// Definitions of 2DTO3D EFFECT
//--------------------------------------------------
#define _2DTO3D_H_EFFECT_MAX                        0x30
#define _2DTO3D_H_EFFECT_MIN                        0x00

#define _2DTO3D_H_V_EFFECT_MAX                      0xFF
#define _2DTO3D_H_V_EFFECT_MIN                      0x00

//--------------------------------------------------
// Definitions of Menu Time Range
//--------------------------------------------------
#define _OSD_TIMEOUT_MAX                            60
#define _OSD_TIMEOUT_MIN                            10
#define _OSD_TIMEOUT_CENTER                         (((_OSD_TIMEOUT_MAX - _OSD_TIMEOUT_MIN) / 2) + _OSD_TIMEOUT_MIN)
//--------------------------------------------------
// Definitions of Transparency Range
//--------------------------------------------------
#define _OSD_TRANSPARENCY_MAX                       255
#define _OSD_TRANSPARENCY_MIN                       0
#define _OSD_TRANSPARENCY_CENTER                    (((_OSD_TRANSPARENCY_MAX - _OSD_TRANSPARENCY_MIN) / 2) + _OSD_TRANSPARENCY_MIN)
//--------------------------------------------------
// Definitions of OSD H Position Range
//--------------------------------------------------
#define _OSD_H_POS_MAX                              100
#define _OSD_H_POS_MIN                              0
#define _OSD_H_POS_CENTER                           (((_OSD_H_POS_MAX - _OSD_H_POS_MIN) / 2) + _OSD_H_POS_MIN)

//--------------------------------------------------
// Definitions of OSD V Position Range
//--------------------------------------------------
#define _OSD_V_POS_MAX                              100
#define _OSD_V_POS_MIN                              0
#define _OSD_V_POS_CENTER                           (((_OSD_V_POS_MAX - _OSD_V_POS_MIN) / 2) + _OSD_V_POS_MIN)

//--------------------------------------------------
// Definitions of OSD V Position Range
//--------------------------------------------------
#define _OSD_ASPECT_ORIGINAL_RATIO_MAX              100
#define _OSD_ASPECT_ORIGINAL_RATIO_MIN              0
#define _OSD_ASPECT_ORIGINAL_RATIO_CENTER           ((_OSD_ASPECT_ORIGINAL_RATIO_MAX - _OSD_ASPECT_ORIGINAL_RATIO_MIN) / 2)

//--------------------------------------------------
// Definitions of Hue Saturation Range
// Allowed Hue = 0 ~ 360, Sat = 0 ~ 330
//--------------------------------------------------
#define _DEFAULT_HUE                                _HUE_CENTER
#define _DEFAULT_SATURATION                         _SATURATION_CENTER

//--------------------------------------------------
// Definitions of OSD Volume Range
//--------------------------------------------------
#define _OSD_VOLUME_MAX                             100
#define _OSD_VOLUME_MIN                             0
#define _OSD_VOLUME_CENTER                          (((_OSD_VOLUME_MAX - _OSD_VOLUME_MIN) / 2) + _OSD_VOLUME_MIN)

//--------------------------------------------------
// Definitions of MBR Backlight Range
//--------------------------------------------------
#define _MBR_DUTY_MAX                               100
#define _MBR_DUTY_MIN                               0
#define _MBR_DUTY_CENTER                            (((_MBR_DUTY_MAX - _MBR_DUTY_MIN) / 2) + _MBR_DUTY_MIN)
#define _MBR_POS_MAX                                100
#define _MBR_POS_MIN                                0
#define _MBR_POS_CENTER                             (((_MBR_POS_MAX - _MBR_POS_MIN) / 2) + _MBR_POS_MIN)

//--------------------------------------------------
// Definitions of OSD audio source
//--------------------------------------------------
typedef enum
{
    _OSD_AUDIO_SOURCE_LINEIN,
    _OSD_AUDIO_SOURCE_DIGITAL_REGION_1,
    _OSD_AUDIO_SOURCE_DIGITAL_REGION_2,
    _OSD_AUDIO_SOURCE_DIGITAL_REGION_3,
    _OSD_AUDIO_SOURCE_DIGITAL_REGION_4,
    _OSD_AUDIO_SOURCE_AMOUNT,
}EnumOsdAudioSourceType;

//--------------------------------------------------
// Definitions of Hue Saturation Range
//--------------------------------------------------
#define _SIX_COLOR_SATURATION_MAX                   200
#define _SIX_COLOR_SATURATION_MIN                   0
#define _SIX_COLOR_SATURATION_CENTER                100

#define _SIX_COLOR_HUE_MAX                          100
#define _SIX_COLOR_HUE_MIN                          0
#define _SIX_COLOR_HUE_CENTER                       50

//--------------------------------------------------
// Definitions of Chameleon Hue Saturation Range
//--------------------------------------------------
#define _CHAMELEON_SAT_MAX                          100
#define _CHAMELEON_SAT_MIN                          0
#define _CHAMELEON_SAT_CENTER                       50

#define _CHAMELEON_HUE_MAX                          300
#define _CHAMELEON_HUE_MIN                          0
#define _CHAMELEON_HUE_CENTER                       150

#define _CHAMELEON_LIGHT_MAX                        100
#define _CHAMELEON_LIGHT_MIN                        0
#define _CHAMELEON_LIGHT_CENTER                     50

//--------------------------------------------------
// Definitions of Chameleon Darkness Offset Range
// Allowed offset = 0 ~ 40
// offset = 0 case, lightness adjust may be useless
// in some color widthout G code, ex. R color
//--------------------------------------------------
#define _ICM_CHAMELEON_DARKNESS_OFFSET              20

//--------------------------------------------------
// Definitions of ICM Night Sniper Range
//--------------------------------------------------
#define _ICM_NIGHT_SNIPER_DARKNESS_OFFSET           20

//--------------------------------------------------
// Definitions of OSD Select Region Width
//--------------------------------------------------
#define _OSD_SR_WIDTH_MAX                           10
#define _OSD_SR_WIDTH_MIN                           0
#define _OSD_SR_WIDTH_CENTER                        (((_OSD_SR_WIDTH_MAX - _OSD_SR_WIDTH_MIN) / 2) + _OSD_SR_WIDTH_MIN)

//--------------------------------------------------
// Definitions of Eagle Sight Border Width
//--------------------------------------------------
#define _EAGLE_SIGHT_BORDER_WIDTH_MAX               2
#define _EAGLE_SIGHT_BORDER_WIDTH_MIN               0
#define _EAGLE_SIGHT_BORDER_WIDTH_CENTER            (((_EAGLE_SIGHT_BORDER_WIDTH_MAX - _EAGLE_SIGHT_BORDER_WIDTH_MIN) / 2) + _EAGLE_SIGHT_BORDER_WIDTH_MIN)

//--------------------------------------------------
// Definitions of OSD Select Region Border Color
//--------------------------------------------------
typedef enum
{
    _SELECT_REGION_COLOR_R,
    _SELECT_REGION_COLOR_G,
    _SELECT_REGION_COLOR_B,
    _SELECT_REGION_COLOR_W,
    _SELECT_REGION_COLOR_AMOUNT,
}EnumSelectRegionColorType;

//--------------------------------------------------
// Definitions of OSD Select Region Border Color
//--------------------------------------------------
#define _OSD_SELECT_REGION_BORDER_RED               (0x80)
#define _OSD_SELECT_REGION_BORDER_GREEN             (0x80)
#define _OSD_SELECT_REGION_BORDER_BLUE              (0x80)
#define _OSD_SELECT_REGION_BORDER_WHITE             (0xFF)

//--------------------------------------------------
// Definitions of OSD PBP LR RATIO
//--------------------------------------------------
#define _OSD_PBP_LR_RATIO_MAX                       4
#define _OSD_PBP_LR_RATIO_MIN                       0
#define _OSD_PBP_LR_RATIO_CENTER                    (((_OSD_PBP_LR_RATIO_MAX - _OSD_PBP_LR_RATIO_MIN) / 2) + _OSD_PBP_LR_RATIO_MIN)

//--------------------------------------------------
// Definitions of OSD 3P Flag RATIO
//--------------------------------------------------
#define _OSD_3P_FLAG_RATIO_MAX                      4
#define _OSD_3P_FLAG_RATIO_MIN                      0
#define _OSD_3P_FLAG_RATIO_CENTER                   (((_OSD_3P_FLAG_RATIO_MAX - _OSD_3P_FLAG_RATIO_MIN) / 2) + _OSD_3P_FLAG_RATIO_MIN)

//--------------------------------------------------
// Definitions of OSD 3P SkewLR RATIO
//--------------------------------------------------
#define _OSD_3P_SKEW_LR_RATIO_MAX                   4
#define _OSD_3P_SKEW_LR_RATIO_MIN                   0
#define _OSD_3P_SKEW_LR_RATIO_CENTER                (((_OSD_3P_SKEW_LR_RATIO_MAX - _OSD_3P_SKEW_LR_RATIO_MIN) / 2) + _OSD_3P_SKEW_LR_RATIO_MIN)

//--------------------------------------------------
// Definitions of OSD PIP SUB position
//--------------------------------------------------
typedef enum
{
    _PIP_POSITON_LT,
    _PIP_POSITON_RT,
    _PIP_POSITON_LB,
    _PIP_POSITON_RB,
    _PIP_POSITON_MIDDLE,
    _PIP_POSITON_USER,
    _PIP_POSITON_AMOUNT,
}EnumPipPositionType;

#define _OSD_PIP_USER_POSITION_H_MAX                100
#define _OSD_PIP_USER_POSITION_H_MIN                0
#define _OSD_PIP_USER_POSITION_H_CENTER             (((_OSD_PIP_USER_POSITION_H_MAX - _OSD_PIP_USER_POSITION_H_MIN) / 2) + _OSD_PIP_USER_POSITION_H_MIN)

#define _OSD_PIP_USER_POSITION_V_MAX                100
#define _OSD_PIP_USER_POSITION_V_MIN                0
#define _OSD_PIP_USER_POSITION_V_CENTER             (((_OSD_PIP_USER_POSITION_V_MAX - _OSD_PIP_USER_POSITION_V_MIN) / 2) + _OSD_PIP_USER_POSITION_V_MIN)

//--------------------------------------------------
// Definitions of OSD PIP Transparency
//--------------------------------------------------
#define _OSD_PIP_TRANSPARENCY_MAX                   10
#define _OSD_PIP_TRANSPARENCY_MIN                   0
#define _OSD_PIP_TRANSPARENCY_CENTER                (((_OSD_PIP_TRANSPARENCY_MAX - _OSD_PIP_TRANSPARENCY_MIN) / 2) + _OSD_PIP_TRANSPARENCY_MIN)

//--------------------------------------------------
// Definitions of OSD PIP Size
//--------------------------------------------------
#define _OSD_PIP_SIZE_MAX                           10
#define _OSD_PIP_SIZE_MIN                           0
#define _OSD_PIP_SIZE_CENTER                        (((_OSD_PIP_TRANSPARENCY_MAX - _OSD_PIP_TRANSPARENCY_MIN) / 2) + _OSD_PIP_TRANSPARENCY_MIN)

#define _OSD_PIP_SIZE_MIN_H_SIZE                    (640)
#define _OSD_PIP_SIZE_MIN_V_SIZE                    (480)

//--------------------------------------------------
// Definitions of Local Contrast advance setting
//--------------------------------------------------
#define _OSD_LC_BLENDING_MAX                        100
#define _OSD_LC_BLENDING_MIN                        0
#define _OSD_LC_DIFFGAIN_MAX                        100
#define _OSD_LC_DIFFGAIN_MIN                        0

//--------------------------------------------------
// Definitions of Eagle Sight Transparency
//--------------------------------------------------
#define _OSD_EAGLE_SIGHT_TRANSPARENCY_MAX           8
#define _OSD_EAGLE_SIGHT_TRANSPARENCY_MIN           0
#define _OSD_EAGLE_SIGHT_TRANSPARENCY_CENTER        (((_OSD_EAGLE_SIGHT_TRANSPARENCY_MAX - _OSD_EAGLE_SIGHT_TRANSPARENCY_MIN) / 2) + _OSD_EAGLE_SIGHT_TRANSPARENCY_MIN)

//--------------------------------------------------
// Enumerations of LED indication
//--------------------------------------------------
typedef enum
{
    _LED_POWER_ON = 0x00,
    _LED_POWER_SEARCH,
    _LED_POWER_ACTIVE,
    _LED_POWER_SAVING,
    _LED_POWER_NOSUPPORT,
    _LED_POWER_NOSUPPORT_SAVING,
    _LED_POWER_OFF,
    _LED_TYPE_1,
    _LED_TYPE_2,
    _LED_TYPE_3,
    _LED_TYPE_4,
    _LED_TYPE_5,
    _LED_TYPE_FLASH,
    _LED_SYSTEM_END,
} EnumLedIndication;

typedef enum
{
    _HDMI_1P4 = 0,
    _HDMI_2P0,
    _HDMI_2P1,
}EnumHDMIVerSelection;

typedef enum
{
    _H_V_SU_128TAPS_NORMAL,
    _H_V_SU_96TAPS_NORMAL,
    _H_SU_128TAPS_1_TO_1,
    _H_SU_96TAPS_1_TO_1,
} EnumSUCoefType;

typedef enum
{
    _H_SD_128TAPS_NORMAL_0,
    _H_SD_128TAPS_NORMAL_1,
    _H_SD_128TAPS_NORMAL_2,
    _H_SD_128TAPS_NORMAL_3,
    _H_SD_128TAPS_NORMAL_4,
    _H_SD_128TAPS_BYPASS_0,
    _H_SD_128TAPS_BYPASS_1,
    _H_SD_128TAPS_BYPASS_2,
    _H_SD_128TAPS_BYPASS_3,
    _H_SD_128TAPS_BYPASS_4,
    _V_SD_64TAPS_NORMAL_0,
    _V_SD_64TAPS_NORMAL_1,
    _V_SD_64TAPS_NORMAL_2,
    _V_SD_64TAPS_NORMAL_3,
    _V_SD_64TAPS_NORMAL_4,
    _V_SD_64TAPS_BYPASS_0,
    _V_SD_64TAPS_BYPASS_1,
    _V_SD_64TAPS_BYPASS_2,
    _V_SD_64TAPS_BYPASS_3,
    _V_SD_64TAPS_BYPASS_4,
} EnumSDCoefType;

//==========================================================================================================
// Timer
//==========================================================================================================
//--------------------------------------------------
// MACRO for Check Timer event
// Max 60 minutes
// 2000 comes from 60 secs div _TIMER_COUNT_20_MS
//--------------------------------------------------
#if(_PIXEL_SHIFT_SUPPORT == _ON)
#define GET_OSD_TIME_FOR_INTCOUNT()                 (g_stTimer.ucTimeForINTCount)
#define SET_OSD_TIME_FOR_INTCOUNT(x)                (g_stTimer.ucTimeForINTCount = (x))

#define GET_OSD_TIME_FOR_MINUTE()                   (g_stTimer.ucTimeForMinute)
#define SET_OSD_TIME_FOR_MINUTE(x)                  (g_stTimer.ucTimeForMinute = (x))

#define GET_PIXEL_ORBITING_TIME()                   (g_stTimer.b4OrbitingTimer)
#define SET_PIXEL_ORBITING_TIME(x)                  (g_stTimer.b4OrbitingTimer = (x))

#define GET_PIXEL_ORBITING_CAPABILITY()             (g_stPixelOrbitingStatus.b1Capability)
#define SET_PIXEL_ORBITING_CAPABILITY(x)            (g_stPixelOrbitingStatus.b1Capability = (x))
#endif

//--------------------------------------------------
// Macro of Key Scan Start Flag
//--------------------------------------------------
#define GET_KEYSCANSTART()                          ((bit)(g_stOsdInfo.ucOsdKeyControl & _BIT1))
#define SET_KEYSCANSTART()                          (g_stOsdInfo.ucOsdKeyControl |= _BIT1)
#define CLR_KEYSCANSTART()                          (g_stOsdInfo.ucOsdKeyControl &= ~_BIT1)

//--------------------------------------------------
// Macro of Key Scan Ready Flag
//--------------------------------------------------
#define GET_KEYSCANREADY()                          ((bit)(g_stOsdInfo.ucOsdKeyControl & _BIT0))
#define SET_KEYSCANREADY()                          (g_stOsdInfo.ucOsdKeyControl |= _BIT0)
#define CLR_KEYSCANREADY()                          (g_stOsdInfo.ucOsdKeyControl &= ~_BIT0)

//--------------------------------------------------
// Macro of Key Repeat Start
//--------------------------------------------------
#define GET_KEYREPEATSTART()                        (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT2)
#define SET_KEYREPEATSTART()                        (g_stOsdInfo.ucOsdKeyControl |= _BIT2)
#define CLR_KEYREPEATSTART()                        (g_stOsdInfo.ucOsdKeyControl &= ~_BIT2)

//--------------------------------------------------
// Macro of Key Repeat Function Enable
// If you want to use repeat function, please set this flag. If not, please clear it.
//--------------------------------------------------
#define GET_KEYREPEATENABLE()                       (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT3)
#define SET_KEYREPEATENABLE()                       (g_stOsdInfo.ucOsdKeyControl |= _BIT3)
#define CLR_KEYREPEATENABLE()                       (g_stOsdInfo.ucOsdKeyControl &= ~_BIT3)

//--------------------------------------------------
// Macro of Key Hold Start
//--------------------------------------------------
#define GET_KEY_HOLD()                              (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT4)
#define SET_KEY_HOLD()                              (g_stOsdInfo.ucOsdKeyControl |= _BIT4)
#define CLR_KEY_HOLD()                              (g_stOsdInfo.ucOsdKeyControl &= ~_BIT4)

#if(_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_OSD_ADDRESS()                  (g_stOsdInfo.ucOsdFreeSyncInforOsdAddress)
#define SET_FREESYNC_OSD_ADDRESS(x)                 (g_stOsdInfo.ucOsdFreeSyncInforOsdAddress = (x))
#endif

//--------------------------------------------------
// Macro of Key Message
//--------------------------------------------------
#define GET_KEYMESSAGE()                            (g_stOsdInfo.ucOsdKeyMessage)
#define SET_KEYMESSAGE(x)                           (g_stOsdInfo.ucOsdKeyMessage = (x))

//--------------------------------------------------
// Definitions of Key Message
//--------------------------------------------------
#define _MENU_KEY_MESSAGE                           0
#define _RIGHT_KEY_MESSAGE                          1
#define _LEFT_KEY_MESSAGE                           2
#define _EXIT_KEY_MESSAGE                           3
#define _5_KEY_MESSAGE                              4
#define _6_KEY_MESSAGE                              5
#define _7_KEY_MESSAGE                              6
#define _HOLD_KEY_MESSAGE                           7
#define _NONE_KEY_MESSAGE                           8

#define _KEY_AMOUNT                                 4

//--------------------------------------------------
// Definitions of LED indicction
//--------------------------------------------------
typedef enum
{
    _LED_ALL_OFF = _LED_SYSTEM_END,
} EnumUserLedIndication;

//--------------------------------------------------
// Macro of OSD
//--------------------------------------------------
#define FONTBYTE0(x)                                HIBYTE(0x1000 | (x)), LOBYTE(0x1000 | (x))
#define FONTBYTE1(x)                                HIBYTE(0x5000 | (x)), LOBYTE(0x5000 | (x))
#define FONTBYTE2(x)                                HIBYTE(0x9000 | (x)), LOBYTE(0x9000 | (x))
#define FONTALLBYTE(x)                              HIBYTE(0xD000 | (x)), LOBYTE(0xD000 | (x))
#define WINDOWBYTE0(x)                              HIBYTE(0x0000 | (x)), LOBYTE(0x0000 | (x))
#define WINDOWBYTE1(x)                              HIBYTE(0x4000 | (x)), LOBYTE(0x4000 | (x))
#define WINDOWBYTE2(x)                              HIBYTE(0x8000 | (x)), LOBYTE(0x8000 | (x))
#define WINDOWALLBYTE(x)                            HIBYTE(0xC000 | (x)), LOBYTE(0xC000 | (x))
#define FRAMEBYTE0(x)                               WINDOWBYTE0(x)
#define FRAMEBYTE1(x)                               WINDOWBYTE1(x)
#define FRAMEBYTE2(x)                               WINDOWBYTE2(x)
#define FRAMEALLBYTE(x)                             WINDOWALLBYTE(x)
#define WINNO(x)                                    (x)
#define ROW(x)                                      (x)
#define COL(x)                                      (x)
#define WIDTH(x)                                    (x)
#define HEIGHT(x)                                   (x)
#define LENGTH(x)                                   (x)
#define FGCOLOR(x)                                  (x)
#define BGCOLOR(x)                                  (x)
#define COLOR00(x)                                  (x)
#define COLOR01(x)                                  (x)
#define COLOR10(x)                                  (x)
#define COLOR11(x)                                  (x)
#define XSTART(x)                                   (x)
#define YSTART(x)                                   (x)
#define XEND(x)                                     (x)
#define YEND(x)                                     (x)
#define PIXELROW(x)                                 ((x) * 18)
#define PIXELCOL(x)                                 ((x) * 12)

//--------------------------------------------------
// Definitions of Checking Max or Min Value Used by OsdDisplayDetOverRange()
//--------------------------------------------------
#define _DET_OVERRANGE_MAX                          (0)
#define _DET_OVERRANGE_MIN                          (1)

//--------------------------------------------------
// Definitions of OSD Function
//--------------------------------------------------
#define _SPACE_                                     0xfc
#define _EXT_                                       0xfc
#define _REPEAT_                                    0xfd
#define _NEXT_                                      0xfe
#define _END_                                       0xff


//--------------------------------------------------
// Definitions of Write Byte
//--------------------------------------------------
#define _WRITE_BYTE0                                0
#define _WRITE_BYTE1                                1
#define _WRITE_BYTE2                                2
#define _WRITE_BYTEALL                              3

//--------------------------------------------------
// Macro of Osd Put String Mode
//--------------------------------------------------
typedef enum
{
    _PUT_STRING_LEFT = 0,
    _PUT_STRING_CENTER,
    _PUT_STRING_RIGHT,

} EnumOsdPutStringMode;

//--------------------------------------------------
// MACRO for OSD Logo Status
//--------------------------------------------------
#define GET_OSD_LOGO_ON()                           (g_stOsdInfo.b1OsdLogo)
#define SET_OSD_LOGO_ON(x)                          (g_stOsdInfo.b1OsdLogo = (x))

//--------------------------------------------------
// MACRO for Power Saving Show Source
//--------------------------------------------------
#define GET_OSD_WAKE_UP_SHOW_QUICKLINK_MENU()       (g_stOsdInfo.b1OsdWakeUpSwitchDdcciPort)
#define SET_OSD_WAKE_UP_SHOW_QUICKLINK_MENU(x)      (g_stOsdInfo.b1OsdWakeUpSwitchDdcciPort = (x))

//--------------------------------------------------
// MACRO for Power Saving Show Source
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_SOURCE()          (g_stOsdInfo.b1OsdWakeUpShowSource)
#define SET_OSD_POWER_SAVING_SHOW_SOURCE(x)         (g_stOsdInfo.b1OsdWakeUpShowSource = (x))


//--------------------------------------------------
// MACRO for Power Saving Show Display Mode
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE()    (g_stOsdInfo.b1OsdWakeUpShowDisplayMode)
#define SET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE(x)   (g_stOsdInfo.b1OsdWakeUpShowDisplayMode = (x))

//--------------------------------------------------
// MACRO for Power Saving Show DP Option
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DP_OPTION()       (g_stOsdInfo.b1OsdWakeUpShowDpOption)
#define SET_OSD_POWER_SAVING_SHOW_DP_OPTION(x)      (g_stOsdInfo.b1OsdWakeUpShowDpOption = (x))

//--------------------------------------------------
// MACRO for Source Menu Status
//--------------------------------------------------
#define GET_OSD_IN_FACTORY_MENU_STATUS()            (g_stOsdInfo.b1OsdFactoryModeStatus)
#define SET_OSD_IN_FACTORY_MENU_STATUS(x)           (g_stOsdInfo.b1OsdFactoryModeStatus = (x))

//--------------------------------------------------
// MACRO for Source Menu Status
//--------------------------------------------------
// bit0 -> port0    bit1 -> port1
#define GET_OSD_DO_ASPECT_RATIO(port)               (g_stOsdInfo.ucOsdDoAspectRatio & (_BIT0 << (port)))
#define SET_OSD_DO_ASPECT_RATIO(port, x)            (g_stOsdInfo.ucOsdDoAspectRatio = ((g_stOsdInfo.ucOsdDoAspectRatio & (~(_BIT0 << (port)))) | ((_BIT0 & (x)) << (port))))

//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_COLOR_FORMAT(port)                  (g_stOsdInfo.pucOsdColorFormat[(port) % _OSD_INPUT_AMOUNT])
#define SET_OSD_COLOR_FORMAT(port, x)               (g_stOsdInfo.pucOsdColorFormat[(port) % _OSD_INPUT_AMOUNT] = (x))

//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_STATE_PREVIOUS()                    (g_stOsdInfo.usOsdStatePrevious)
#define SET_OSD_STATE_PREVIOUS(x)                   (g_stOsdInfo.usOsdStatePrevious = (x))


//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_STATE()                             (g_stOsdInfo.usOsdState)
#define SET_OSD_STATE(x)                            (g_stOsdInfo.usOsdState = (x))

//--------------------------------------------------
// MACRO for Osd Evevt Message
//--------------------------------------------------
#define GET_OSD_EVENT_MESSAGE()                     (g_stOsdInfo.ucOsdEventMsg)
#define SET_OSD_EVENT_MESSAGE(x)                    (g_stOsdInfo.ucOsdEventMsg = (x))

//--------------------------------------------------
// MACRO for Six Color
//--------------------------------------------------
#define GET_OSD_SIX_COLOR()                         (g_stOsdInfo.b3OsdsixColor)
#define SET_OSD_SIX_COLOR(x)                        (g_stOsdInfo.b3OsdsixColor = (x))

//--------------------------------------------------
// MACRO for Six Color Hue
//--------------------------------------------------
#define GET_OSD_SIX_COLOR_HUE()                     (g_stOsdInfo.ucOsdsixColorHue)
#define SET_OSD_SIX_COLOR_HUE(x)                    (g_stOsdInfo.ucOsdsixColorHue = (x))

//--------------------------------------------------
// MACRO for Six Color Saturation
//--------------------------------------------------
#define GET_OSD_SIX_COLOR_SATURATION()              (g_stOsdInfo.ucOsdsixColorSaturation)
#define SET_OSD_SIX_COLOR_SATURATION(x)             (g_stOsdInfo.ucOsdsixColorSaturation = (x))

//--------------------------------------------------
// MACRO for OSD double size
//--------------------------------------------------
#define GET_OSD_DOUBLE_SIZE()                       (g_stOsdInfo.b1OsdDoubleSizeStatus)
#define SET_OSD_DOUBLE_SIZE(x)                      (g_stOsdInfo.b1OsdDoubleSizeStatus = (x))

//--------------------------------------------------
// MACRO for Freeze Status
//--------------------------------------------------
#define GET_OSD_FREEZE_STATUS()                     (g_stOsdInfo.b1FreezeStatus)
#define SET_OSD_FREEZE_STATUS(x)                    (g_stOsdInfo.b1FreezeStatus = (x))

#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FREEZE_SUPPORT == _ON))
#define GET_FREEZE_DISABLE_MSG_STATE()              (g_stOsdInfo.b1FreezeDisableOsdStatus)
#define SET_FREEZE_DISABLE_MSG_STATE(x)             (g_stOsdInfo.b1FreezeDisableOsdStatus = (x))
#endif

//--------------------------------------------------
//--------------------------------------------------
#define GET_OSD_ITEM_INDEX()                        (g_stOsdInfo.ucOsdItemIndex)
#define SET_OSD_ITEM_INDEX(x)                       (g_stOsdInfo.ucOsdItemIndex = (x))


#define GET_OSD_INFO_STRING_MODE()                  (g_stOsdInfo.b2StringMode)
#define SET_OSD_INFO_STRING_MODE(x)                 (g_stOsdInfo.b2StringMode = (x))
#define CLR_OSD_INFO_STRING_MODE()                  (g_stOsdInfo.b2StringMode = _PUT_STRING_LEFT)

//--------------------------------------------------
// Macro of Osd Put String Center Length
//--------------------------------------------------
#define GET_OSD_INFO_STRING_MODE_LENGTH()           (g_stOsdInfo.ucStringModeLength)
#define SET_OSD_INFO_STRING_MODE_LENGTH(x)          (g_stOsdInfo.ucStringModeLength = (x))
#define CLR_OSD_INFO_STRING_MODE_LENGTH()           (g_stOsdInfo.ucStringModeLength = 0)

//--------------------------------------------------
// Macro of Osd Put String Blank Pixel
//--------------------------------------------------
#define GET_OSD_INFO_STRING_BLANK_PIXEL()           (g_stOsdInfo.ucStringBlankPixel)
#define SET_OSD_INFO_STRING_BLANK_PIXEL(x)          (g_stOsdInfo.ucStringBlankPixel = (x))
#define CLR_OSD_INFO_STRING_BLANK_PIXEL()           (g_stOsdInfo.ucStringBlankPixel = 0)

//--------------------------------------------------
// MACRO for PixelShift
//--------------------------------------------------
#define GET_OSD_PIXELSHIFT_STATUS()                 (g_stOsdInfo.b1OsdPixelShift)
#define SET_OSD_PIXELSHIFT_STATUS(x)                (g_stOsdInfo.b1OsdPixelShift = (x))

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for FW update
//--------------------------------------------------
#define GET_OSD_FW_UPDATE_COUNT()                   (g_stOsdInfo.ucOsdFwUpdateWaitTime)
#define SET_OSD_FW_UPDATE_COUNT(x)                  (g_stOsdInfo.ucOsdFwUpdateWaitTime = (x))
#define GET_OSD_FW_UPDATE_NOW()                     (g_stOsdInfo.b1OsdFwUpdateNow)
#define SET_OSD_FW_UPDATE_NOW(x)                    (g_stOsdInfo.b1OsdFwUpdateNow = (x))
#endif

//==========================================================================================================
// Macro of NVRam User Data
//==========================================================================================================

//--------------------------------------------------
// MACRO for OSD Display Mode
//--------------------------------------------------
#define GET_OSD_DISPLAY_MODE()                      (g_stOsdUserData.stDisplayData.ucDisplayMode)
#define SET_OSD_DISPLAY_MODE(x)                     (g_stOsdUserData.stDisplayData.ucDisplayMode = (x))

//--------------------------------------------------
// MACRO for OSD Select Region Width
//--------------------------------------------------
#define GET_OSD_SELECT_REGION_WIDTH()               (g_stOsdUserData.stColorData.ucSelectRegionWidth)
#define SET_OSD_SELECT_REGION_WIDTH(x)              (g_stOsdUserData.stColorData.ucSelectRegionWidth = (x))

//--------------------------------------------------
// MACRO for OSD Select Region Color
//--------------------------------------------------
#define GET_OSD_SELECT_REGION_COLOR()               (g_stOsdUserData.stColorData.ucSelectRegionColor)
#define SET_OSD_SELECT_REGION_COLOR(x)              (g_stOsdUserData.stColorData.ucSelectRegionColor = (x))

//--------------------------------------------------
// MACRO for PBP LR Ratio
//--------------------------------------------------
#define GET_OSD_PBP_LR_RATIO()                      (g_stOsdUserData.stDisplayData.ucPbpLrRatio)
#define SET_OSD_PBP_LR_RATIO(x)                     (g_stOsdUserData.stDisplayData.ucPbpLrRatio = (x))

//--------------------------------------------------
// MACRO for 3P Flag Ratio
//--------------------------------------------------
#define GET_OSD_3P_FLAG_RATIO()                     (g_stOsdUserData.stDisplayData.uc3PFlagRatio)
#define SET_OSD_3P_FLAG_RATIO(x)                    (g_stOsdUserData.stDisplayData.uc3PFlagRatio = (x))

//--------------------------------------------------
// MACRO for 3P Flag Ratio
//--------------------------------------------------
#define GET_OSD_3P_SKEW_LR_RATIO()                  (g_stOsdUserData.stDisplayData.uc3PSkewLRRatio)
#define SET_OSD_3P_SKEW_LR_RATIO(x)                 (g_stOsdUserData.stDisplayData.uc3PSkewLRRatio = (x))

//--------------------------------------------------
// MACRO for PIP Position
//--------------------------------------------------
#define GET_OSD_PIP_POSITION_TYPE()                 (g_stOsdUserData.stDisplayData.ucPipSubPosType)
#define SET_OSD_PIP_POSITION_TYPE(x)                (g_stOsdUserData.stDisplayData.ucPipSubPosType = (x))

#define GET_OSD_PIP_USER_POSITION_H()               (g_stOsdUserData.stDisplayData.usPipSubHPos)
#define SET_OSD_PIP_USER_POSITION_H(x)              (g_stOsdUserData.stDisplayData.usPipSubHPos = (x))

#define GET_OSD_PIP_USER_POSITION_V()               (g_stOsdUserData.stDisplayData.usPipSubVPos)
#define SET_OSD_PIP_USER_POSITION_V(x)              (g_stOsdUserData.stDisplayData.usPipSubVPos = (x))

//--------------------------------------------------
// MACRO for PIP Transparency
//--------------------------------------------------
#define GET_OSD_PIP_TRANSPARENCY()                  (g_stOsdUserData.stDisplayData.ucPipSubBlending)
#define SET_OSD_PIP_TRANSPARENCY(x)                 (g_stOsdUserData.stDisplayData.ucPipSubBlending = (x))

//--------------------------------------------------
// MACRO for PIP Size
//--------------------------------------------------
#define GET_OSD_PIP_SIZE()                          (g_stOsdUserData.stDisplayData.ucPipSubScaling)
#define SET_OSD_PIP_SIZE(x)                         (g_stOsdUserData.stDisplayData.ucPipSubScaling = (x))

//--------------------------------------------------
// MACRO for Panel Time Min
//--------------------------------------------------
#define GET_PANEL_TIME_MIN()                        (g_stOsdUserData.ucMin)
#define SET_PANEL_TIME_MIN(x)                       (g_stOsdUserData.ucMin = (x))

//--------------------------------------------------
// MACRO for Panel Time Hour
//--------------------------------------------------
#define GET_PANEL_TIME_HOUR()                       (g_stOsdUserData.usHour)
#define SET_PANEL_TIME_HOUR(x)                      (g_stOsdUserData.usHour = (x))

//--------------------------------------------------
// MACRO for Rotation Status
//--------------------------------------------------
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#define GET_OSD_DISP_ROTATION_SIZE_TYPE()           (g_stOsdUserData.stDisplayData.b2DispRotationSizeType)
#define SET_OSD_DISP_ROTATION_SIZE_TYPE(x)          (g_stOsdUserData.stDisplayData.b2DispRotationSizeType = (x))
#endif

//--------------------------------------------------
// MACRO for DP Port Version
//--------------------------------------------------
#define GET_OSD_DP_D0_VERSION()                     (g_stOsdUserData.stDpData.b2OsdDpD0PortVersion)
#define SET_OSD_DP_D0_VERSION(x)                    (g_stOsdUserData.stDpData.b2OsdDpD0PortVersion = (x))

#define GET_OSD_DP_D1_VERSION()                     (g_stOsdUserData.stDpData.b2OsdDpD1PortVersion)
#define SET_OSD_DP_D1_VERSION(x)                    (g_stOsdUserData.stDpData.b2OsdDpD1PortVersion = (x))

#define GET_OSD_DP_D2_VERSION()                     (g_stOsdUserData.stDpData.b2OsdDpD2PortVersion)
#define SET_OSD_DP_D2_VERSION(x)                    (g_stOsdUserData.stDpData.b2OsdDpD2PortVersion = (x))

#define GET_OSD_DP_D6_VERSION()                     (g_stOsdUserData.stDpData.b2OsdDpD6PortVersion)
#define SET_OSD_DP_D6_VERSION(x)                    (g_stOsdUserData.stDpData.b2OsdDpD6PortVersion = (x))

#define GET_OSD_DP_MST()                            (g_stOsdUserData.stDpData.b3OsdDpMST)
#define SET_OSD_DP_MST(x)                           (g_stOsdUserData.stDpData.b3OsdDpMST = (x))

//--------------------------------------------------
// MACRO for DP ALPM
//--------------------------------------------------
#define GET_OSD_DP_AUXLESS_ALPM()                   (g_stOsdUserData.stDpData.b1OsdDpAuxlessAlpm)
#define SET_OSD_DP_AUXLESS_ALPM(x)                  (g_stOsdUserData.stDpData.b1OsdDpAuxlessAlpm = (x))

//--------------------------------------------------
// MACRO for DP AdativeSync
//--------------------------------------------------
#define GET_OSD_DP_ADAPTIVE_SYNC()                  (g_stOsdUserData.stDpData.b1OsdDpAdaptiveSync)
#define SET_OSD_DP_ADAPTIVE_SYNC(x)                 (g_stOsdUserData.stDpData.b1OsdDpAdaptiveSync = (x))

//--------------------------------------------------
// MACRO for Panel replay
//--------------------------------------------------
#define GET_OSD_PANEL_REPLAY()                      (g_stOsdUserData.stDpData.b1OsdPanelReplay)
#define SET_OSD_PANEL_REPLAY(x)                     (g_stOsdUserData.stDpData.b1OsdPanelReplay = (x))

//--------------------------------------------------
// PXP MST marco
//--------------------------------------------------
typedef enum
{
    _OFF_PXP_MST,
    _ON_FIXED_MODE,
    _ON_SELECT_MODE,
} EnumPxMstMode;

#define GET_OSD_PXP_MST()                           (g_stOsdUserData.stDpData.b2PxPMst)
#define SET_OSD_PXP_MST(x)                          (g_stOsdUserData.stDpData.b2PxPMst = (x))

//--------------------------------------------------
// MACRO for DP Lane Count switch
//--------------------------------------------------
#if(_USB_HUB_SUPPORT == _ON)
#define GET_OSD_D0_TYPE_C_U3_MODE()                 (g_stOsdUserData.stTypeCData.b1D0TypeCU3Mode)
#define SET_OSD_D0_TYPE_C_U3_MODE(x)                (g_stOsdUserData.stTypeCData.b1D0TypeCU3Mode = (x))

#define GET_OSD_D1_TYPE_C_U3_MODE()                 (g_stOsdUserData.stTypeCData.b1D1TypeCU3Mode)
#define SET_OSD_D1_TYPE_C_U3_MODE(x)                (g_stOsdUserData.stTypeCData.b1D1TypeCU3Mode = (x))

#define GET_OSD_D2_TYPE_C_U3_MODE()                 (g_stOsdUserData.stTypeCData.b1D2TypeCU3Mode)
#define SET_OSD_D2_TYPE_C_U3_MODE(x)                (g_stOsdUserData.stTypeCData.b1D2TypeCU3Mode = (x))

#define GET_OSD_D6_TYPE_C_U3_MODE()                 (g_stOsdUserData.stTypeCData.b1D6TypeCU3Mode)
#define SET_OSD_D6_TYPE_C_U3_MODE(x)                (g_stOsdUserData.stTypeCData.b1D6TypeCU3Mode = (x))
#endif

//--------------------------------------------------
// MACRO for Type-C Pin Assignment E Support Switch
//--------------------------------------------------
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
#define GET_OSD_D0_TYPE_C_PIN_ASSIGNMENT_E_SELECT() (g_stOsdUserData.stTypeCData.b1D0TypeCPinAssignmentESupportSelect)
#define SET_OSD_D0_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x)(g_stOsdUserData.stTypeCData.b1D0TypeCPinAssignmentESupportSelect = (x))

#define GET_OSD_D1_TYPE_C_PIN_ASSIGNMENT_E_SELECT() (g_stOsdUserData.stTypeCData.b1D1TypeCPinAssignmentESupportSelect)
#define SET_OSD_D1_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x)(g_stOsdUserData.stTypeCData.b1D1TypeCPinAssignmentESupportSelect = (x))

#define GET_OSD_D2_TYPE_C_PIN_ASSIGNMENT_E_SELECT() (g_stOsdUserData.stTypeCData.b1D2TypeCPinAssignmentESupportSelect)
#define SET_OSD_D2_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x)(g_stOsdUserData.stTypeCData.b1D2TypeCPinAssignmentESupportSelect = (x))

#define GET_OSD_D6_TYPE_C_PIN_ASSIGNMENT_E_SELECT() (g_stOsdUserData.stTypeCData.b1D6TypeCPinAssignmentESupportSelect)
#define SET_OSD_D6_TYPE_C_PIN_ASSIGNMENT_E_SELECT(x)(g_stOsdUserData.stTypeCData.b1D6TypeCPinAssignmentESupportSelect = (x))
#endif
#endif

//--------------------------------------------------
// MACRO for Display Rotate
//--------------------------------------------------
#define GET_OSD_DISP_ROTATE()                       (g_stOsdUserData.stDisplayData.b3OsdDispRotate)
#define SET_OSD_DISP_ROTATE(x)                      (g_stOsdUserData.stDisplayData.b3OsdDispRotate = (x))

//--------------------------------------------------
// MACRO for Latency
//--------------------------------------------------
#define GET_OSD_LATENCY()                           (g_stOsdUserData.stDisplayData.b2LatencyStatus)
#define SET_OSD_LATENCY(x)                          (g_stOsdUserData.stDisplayData.b2LatencyStatus = (x))

//--------------------------------------------------
// MACRO for PCM Soft Proft
//--------------------------------------------------
#define GET_OSD_PCM_SOFT_PROFT_MODE()               (g_stOsdUserData.stColorData.b1PCMSoftProftMode)
#define SET_OSD_PCM_SOFT_PROFT_MODE(x)              (g_stOsdUserData.stColorData.b1PCMSoftProftMode = (x))

//--------------------------------------------------
// MACRO for OSD Rotate
//--------------------------------------------------

#define GET_OSD_ROTATE_STATUS()                     (g_stOsdUserData.b2OsdRotate)
#define SET_OSD_ROTATE_STATUS(x)                    (g_stOsdUserData.b2OsdRotate = (x))

//--------------------------------------------------
// Macro of BackLight
//--------------------------------------------------
#define GET_OSD_BACKLIGHT()                         (g_stOsdUserData.usBackLight)
#define SET_OSD_BACKLIGHT(x)                        (g_stOsdUserData.usBackLight = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_VGA_COLOR_FORMAT_STATUS()               (g_stOsdUserData.stColorData.b3VGARGBYUV)
#define SET_VGA_COLOR_FORMAT_STATUS(x)              (g_stOsdUserData.stColorData.b3VGARGBYUV = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_DVI_COLOR_FORMAT_STATUS()               (g_stOsdUserData.stColorData.b3DVIRGBYUV)
#define SET_DVI_COLOR_FORMAT_STATUS(x)              (g_stOsdUserData.stColorData.b3DVIRGBYUV = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_DDCCI_STATUS()                      (g_stOsdUserData.b1DDCCIStatus)
#define SET_OSD_DDCCI_STATUS(x)                     (g_stOsdUserData.b1DDCCIStatus = (x))

//--------------------------------------------------
// MACRO for Transparency
//--------------------------------------------------
#define GET_OSD_TRANSPARENCY_STATUS()               (g_stOsdUserData.ucTransparency)
#define SET_OSD_TRANSPARENCY_STATUS(x)              (g_stOsdUserData.ucTransparency = (x))

//--------------------------------------------------
// MACRO for Language
//--------------------------------------------------
#define GET_OSD_LANGUAGE()                          (g_stOsdUserData.b4Language)
#define SET_OSD_LANGUAGE(x)                         (g_stOsdUserData.b4Language = (x))

//--------------------------------------------------
// MACRO for OsdTimeout
//--------------------------------------------------
#define GET_OSD_TIME_OUT()                          (g_stOsdUserData.ucOsdTimeout)
#define SET_OSD_TIME_OUT(x)                         (g_stOsdUserData.ucOsdTimeout = (x))

//--------------------------------------------------
// MACRO for OsdHPos
//--------------------------------------------------
#define GET_OSD_HPOS()                              (g_stOsdUserData.ucOsdHPos)
#define SET_OSD_HPOS(x)                             (g_stOsdUserData.ucOsdHPos = (x))

//--------------------------------------------------
// MACRO for OsdVPos
//--------------------------------------------------
#define GET_OSD_VPOS()                              (g_stOsdUserData.ucOsdVPos)
#define SET_OSD_VPOS(x)                             (g_stOsdUserData.ucOsdVPos = (x))

//--------------------------------------------------
// MACRO for OD Status
//--------------------------------------------------
#define GET_OSD_OD_STATUS()                         (g_stOsdUserData.stColorData.b1ODStatus)
#define SET_OSD_OD_STATUS(x)                        (g_stOsdUserData.stColorData.b1ODStatus = (x))

//--------------------------------------------------
// MACRO for OD Gain
//--------------------------------------------------
#define GET_OSD_OD_GAIN()                           (g_stOsdUserData.stColorData.ucODGain)
#define SET_OSD_OD_GAIN(x)                          (g_stOsdUserData.stColorData.ucODGain = (x))

//--------------------------------------------------
// MACRO for DCR Status
//--------------------------------------------------
#define GET_OSD_DCR_STATUS()                        (g_stOsdUserData.stColorData.b1OsdDcrStatus)
#define SET_OSD_DCR_STATUS(x)                       (g_stOsdUserData.stColorData.b1OsdDcrStatus = (x))

//--------------------------------------------------
// MACRO for FreeSync Status
//--------------------------------------------------
#define GET_OSD_FREE_SYNC_STATUS()                  (g_stOsdUserData.stDisplayData.b1FreeSyncStatus)
#define SET_OSD_FREE_SYNC_STATUS(x)                 (g_stOsdUserData.stDisplayData.b1FreeSyncStatus = (x))

//--------------------------------------------------
// MACRO for Clone Mode
//--------------------------------------------------
#define GET_OSD_CLONE_MODE_1P()                     (g_stOsdUserData.stDpData.enumCloneMode1P)
#define SET_OSD_CLONE_MODE_1P(x)                    (g_stOsdUserData.stDpData.enumCloneMode1P = (x))

//--------------------------------------------------
// MACRO for Clone Mode Source
//--------------------------------------------------
#define GET_OSD_CLONE_MODE_MTP()                    (g_stOsdUserData.stDpData.enumCloneModeMtP)
#define SET_OSD_CLONE_MODE_MTP(x)                   (g_stOsdUserData.stDpData.enumCloneModeMtP = (x))

//--------------------------------------------------
// MACRO for DSC port support
//--------------------------------------------------
#define GET_OSD_DSC_PORT()                          (g_stOsdUserData.stDisplayData.b3DscStatus)
#define SET_OSD_DSC_PORT(x)                         (g_stOsdUserData.stDisplayData.b3DscStatus = (x))

//--------------------------------------------------
// MACRO for DSC port support
//--------------------------------------------------
#define GET_OSD_1P_DSC_PORT()                       (g_stOsdUserData.stDisplayData.b3Dsc1PStatus)
#define SET_OSD_1P_DSC_PORT(x)                      (g_stOsdUserData.stDisplayData.b3Dsc1PStatus = (x))

//--------------------------------------------------
// MACRO for Volume Mute
//--------------------------------------------------
#define GET_OSD_VOLUME_MUTE()                       (g_stOsdUserData.stAudioData.b1VolumeMute)
#define SET_OSD_VOLUME_MUTE(x)                      (g_stOsdUserData.stAudioData.b1VolumeMute = (x))

//--------------------------------------------------
// MACRO for Volume
//--------------------------------------------------
#define GET_OSD_VOLUME()                            (g_stOsdUserData.stAudioData.ucVolume)
#define SET_OSD_VOLUME(x)                           (g_stOsdUserData.stAudioData.ucVolume = (x))

//--------------------------------------------------
// MACRO for Audio Stand a long
//--------------------------------------------------
#define GET_OSD_AUDIO_STAND_ALONE()                 (g_stOsdUserData.stAudioData.b1AudioStandAloneStatus)
#define SET_OSD_AUDIO_STAND_ALONE(x)                (g_stOsdUserData.stAudioData.b1AudioStandAloneStatus = (x))

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
//--------------------------------------------------
// MACRO for Audio TTS Support
//--------------------------------------------------
#define GET_OSD_AUDIO_TTS_SUPPORT()                 (g_stOsdUserData.stAudioData.b1TtsSupport)
#define SET_OSD_AUDIO_TTS_SUPPORT(x)                (g_stOsdUserData.stAudioData.b1TtsSupport = (x))

//--------------------------------------------------
// MACRO for Audio TTS Text Volume
//--------------------------------------------------
#define GET_OSD_AUDIO_TTS_TEXT_VOLUME()             (g_stOsdUserData.stAudioData.ucTtsTextVolume)
#define SET_OSD_AUDIO_TTS_TEXT_VOLUME(x)            (g_stOsdUserData.stAudioData.ucTtsTextVolume = (x))

//--------------------------------------------------
// MACRO for Audio TTS Audio Volume
//--------------------------------------------------
#define GET_OSD_AUDIO_TTS_AUDIO_VOLUME()            (g_stOsdUserData.stAudioData.ucTtsAudioVolume)
#define SET_OSD_AUDIO_TTS_AUDIO_VOLUME(x)           (g_stOsdUserData.stAudioData.ucTtsAudioVolume = (x))

#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_HLWIN_TYPE()                        (g_stOsdUserData.stColorData.ucHLWinType)
#define SET_OSD_HLWIN_TYPE(x)                       (g_stOsdUserData.stColorData.ucHLWinType = (x))

#define GET_OSD_HLWIN_SIDE()                        (g_stOsdUserData.stColorData.b2DemoSideIdx)
#define SET_OSD_HLWIN_SIDE(x)                       (g_stOsdUserData.stColorData.b2DemoSideIdx = (x))

//--------------------------------------------------
// MACRO for Auto-Color Type
//--------------------------------------------------
typedef enum
{
    _AUTO_COLOR_TYPE_INTERNAL,
    _AUTO_COLOR_TYPE_EXTERNAL,
} EnumFactoryAutoColorType;

#define GET_OSD_FACTORY_AUTO_COLOR_TYPE()           (g_stOsdUserData.stVgaData.b1FactoryAutoColorType)
#define SET_OSD_FACTORY_AUTO_COLOR_TYPE(x)          (g_stOsdUserData.stVgaData.b1FactoryAutoColorType = (x))

//--------------------------------------------------
// MACRO for Local Dimming
//--------------------------------------------------
#define GET_OSD_LOCAL_DIMMING()                     (g_stOsdUserData.stColorData.b1HdrLocalDimming)
#define SET_OSD_LOCAL_DIMMING(x)                    (g_stOsdUserData.stColorData.b1HdrLocalDimming = (x))

//--------------------------------------------------
// MACRO for Local Dimming Smooth Backlight adjust
//--------------------------------------------------
#define GET_OSD_LD_ADJ()                            (g_stOsdUserData.stColorData.ucHdrLocalDimmingAdj)
#define SET_OSD_LD_ADJ(x)                           (g_stOsdUserData.stColorData.ucHdrLocalDimmingAdj = (x))

//--------------------------------------------------
// MACRO for GlobalDimming
//--------------------------------------------------
#define GET_OSD_GLOBAL_DIMMING()                    (g_stOsdUserData.stColorData.b1GlobalDimming)
#define SET_OSD_GLOBAL_DIMMING(x)                   (g_stOsdUserData.stColorData.b1GlobalDimming = (x))

#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
//--------------------------------------------------
// MACRO for Eye Protect
//--------------------------------------------------
#define GET_OSD_EYEPROTECT_LOWBLUE()                (g_stOsdUserData.stEyeProtectData.b3LowBlueMode)
#define SET_OSD_EYEPROTECT_LOWBLUE(x)               (g_stOsdUserData.stEyeProtectData.b3LowBlueMode = (x))

#define GET_OSD_EYEPROTECT_LOWBLUE_LEVEL()          (g_stOsdUserData.stEyeProtectData.b3ProtectLevel)
#define SET_OSD_EYEPROTECT_LOWBLUE_LEVEL(x)         (g_stOsdUserData.stEyeProtectData.b3ProtectLevel = (x))

#define GET_OSD_EYEPROTECT_NIGHTMODE_TIME()         (g_stOsdUserData.stEyeProtectData.enumNightModeTime)
#define SET_OSD_EYEPROTECT_NIGHTMODE_TIME(x)        (g_stOsdUserData.stEyeProtectData.enumNightModeTime = (x))

#define GET_OSD_EYEPROTECT_AMBIENTSENSE_MODE()      (g_stOsdUserData.stEyeProtectData.bAmbientSenseMode)
#define SET_OSD_EYEPROTECT_AMBIENTSENSE_MODE(x)     (g_stOsdUserData.stEyeProtectData.bAmbientSenseMode = (x))

#define GET_OSD_EYEPROTECT_TIME_MIN_COUNT()         (g_stOsdInfo.ucNightModeTime)
#define SET_OSD_EYEPROTECT_TIME_MIN_COUNT(x)        (g_stOsdInfo.ucNightModeTime = (x))
#endif
//--------------------------------------------------
// MACRO for HDMI version
//--------------------------------------------------
#define GET_OSD_D0_HDMI_VER()                       (g_stOsdUserData.stTmdsData.b2OsdHdmiD0PortVersion)
#define SET_OSD_D0_HDMI_VER(x)                      (g_stOsdUserData.stTmdsData.b2OsdHdmiD0PortVersion = (x))

#define GET_OSD_D1_HDMI_VER()                       (g_stOsdUserData.stTmdsData.b2OsdHdmiD1PortVersion)
#define SET_OSD_D1_HDMI_VER(x)                      (g_stOsdUserData.stTmdsData.b2OsdHdmiD1PortVersion = (x))

#define GET_OSD_D2_HDMI_VER()                       (g_stOsdUserData.stTmdsData.b2OsdHdmiD2PortVersion)
#define SET_OSD_D2_HDMI_VER(x)                      (g_stOsdUserData.stTmdsData.b2OsdHdmiD2PortVersion = (x))

#define GET_OSD_D3_HDMI_VER()                       (g_stOsdUserData.stTmdsData.b2OsdHdmiD3PortVersion)
#define SET_OSD_D3_HDMI_VER(x)                      (g_stOsdUserData.stTmdsData.b2OsdHdmiD3PortVersion = (x))

#define GET_OSD_D4_HDMI_VER()                       (g_stOsdUserData.stTmdsData.b2OsdHdmiD4PortVersion)
#define SET_OSD_D4_HDMI_VER(x)                      (g_stOsdUserData.stTmdsData.b2OsdHdmiD4PortVersion = (x))

#define GET_OSD_D5_HDMI_VER()                       (g_stOsdUserData.stTmdsData.b2OsdHdmiD5PortVersion)
#define SET_OSD_D5_HDMI_VER(x)                      (g_stOsdUserData.stTmdsData.b2OsdHdmiD5PortVersion = (x))


//--------------------------------------------------
// MACRO for HDMI version
//--------------------------------------------------
#define GET_OSD_HOTKEY_EXIT()                       (g_stOsdUserData.ucExitHotKeyItem)
#define SET_OSD_HOTKEY_EXIT(x)                      (g_stOsdUserData.ucExitHotKeyItem = (x))

#if(_USB3_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Hub PSPD marco
//--------------------------------------------------
#define GET_OSD_D0_USB3_RETIMER_PD_WAKEUP()         (g_stOsdUserData.stUsbHubData.b1OsdD0Usb3RetimerPDWakeUp)
#define SET_OSD_D0_USB3_RETIMER_PD_WAKEUP(x)        (g_stOsdUserData.stUsbHubData.b1OsdD0Usb3RetimerPDWakeUp = (x))
#define GET_OSD_D0_USB3_RETIMER_PS_WAKEUP()         (g_stOsdUserData.stUsbHubData.b1OsdD0Usb3RetimerPSWakeUp)
#define SET_OSD_D0_USB3_RETIMER_PS_WAKEUP(x)        (g_stOsdUserData.stUsbHubData.b1OsdD0Usb3RetimerPSWakeUp = (x))
#define GET_OSD_D1_USB3_RETIMER_PD_WAKEUP()         (g_stOsdUserData.stUsbHubData.b1OsdD1Usb3RetimerPDWakeUp)
#define SET_OSD_D1_USB3_RETIMER_PD_WAKEUP(x)        (g_stOsdUserData.stUsbHubData.b1OsdD1Usb3RetimerPDWakeUp = (x))
#define GET_OSD_D1_USB3_RETIMER_PS_WAKEUP()         (g_stOsdUserData.stUsbHubData.b1OsdD1Usb3RetimerPSWakeUp)
#define SET_OSD_D1_USB3_RETIMER_PS_WAKEUP(x)        (g_stOsdUserData.stUsbHubData.b1OsdD1Usb3RetimerPSWakeUp = (x))
#define GET_OSD_D2_USB3_RETIMER_PD_WAKEUP()         (g_stOsdUserData.stUsbHubData.b1OsdD2Usb3RetimerPDWakeUp)
#define SET_OSD_D2_USB3_RETIMER_PD_WAKEUP(x)        (g_stOsdUserData.stUsbHubData.b1OsdD2Usb3RetimerPDWakeUp = (x))
#define GET_OSD_D2_USB3_RETIMER_PS_WAKEUP()         (g_stOsdUserData.stUsbHubData.b1OsdD2Usb3RetimerPSWakeUp)
#define SET_OSD_D2_USB3_RETIMER_PS_WAKEUP(x)        (g_stOsdUserData.stUsbHubData.b1OsdD2Usb3RetimerPSWakeUp = (x))
#endif
//--------------------------------------------------
// Hub UFP Switch marco
//--------------------------------------------------
#define GET_USER_USB_HUB_SWITCH_MODE()              (g_stOsdUserData.stUsbHubData.ucUSBHubUfpSwitchMode)
#define SET_USER_USB_HUB_SWITCH_MODE(x)             (g_stOsdUserData.stUsbHubData.ucUSBHubUfpSwitchMode = (x))

//--------------------------------------------------
// EagleSight marco
//--------------------------------------------------
#define GET_EAGLE_SIGHT_STATUS()                    (g_stOsdUserData.stEagleSightData.b1EagleSightEn)
#define SET_EAGLE_SIGHT_STATUS(x)                   (g_stOsdUserData.stEagleSightData.b1EagleSightEn = (x))
#define GET_EAGLE_SIGHT_TRANSPARENCY()              (g_stOsdUserData.stEagleSightData.ucEagleSightTransparency)
#define SET_EAGLE_SIGHT_TRANSPARENCY(x)             (g_stOsdUserData.stEagleSightData.ucEagleSightTransparency = (x))
#define GET_EAGLE_SIGHT_ZOOM()                      (g_stOsdUserData.stEagleSightData.ucEagleSightZoom)
#define SET_EAGLE_SIGHT_ZOOM(x)                     (g_stOsdUserData.stEagleSightData.ucEagleSightZoom = (x))
#define GET_EAGLE_SIGHT_CAP_POSITION()              (g_stOsdUserData.stEagleSightData.ucEagleSightCapPosition)
#define SET_EAGLE_SIGHT_CAP_POSITION(x)             (g_stOsdUserData.stEagleSightData.ucEagleSightCapPosition = (x))
#define GET_EAGLE_SIGHT_DISP_POSITION()             (g_stOsdUserData.stEagleSightData.ucEagleSightDispPosition)
#define SET_EAGLE_SIGHT_DISP_POSITION(x)            (g_stOsdUserData.stEagleSightData.ucEagleSightDispPosition = (x))
#define GET_EAGLE_SIGHT_BORDER()                    (g_stOsdUserData.stEagleSightData.b3EagleSightBorder)
#define SET_EAGLE_SIGHT_BORDER(x)                   (g_stOsdUserData.stEagleSightData.b3EagleSightBorder = (x))

#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
#define GET_EAGLE_SIGHT_CIRCLE_WIN_STATUS()         (g_stOsdUserData.stEagleSightData.b1EagleSightCircleWin)
#define SET_EAGLE_SIGHT_CIRCLE_WIN_STATUS(x)        (g_stOsdUserData.stEagleSightData.b1EagleSightCircleWin = (x))
#endif

//--------------------------------------------------
// MBR marco
//--------------------------------------------------
#define GET_OSD_MBR_MODE()                          (g_stOsdUserData.stMbrData.b2MbrMode)
#define SET_OSD_MBR_MODE(x)                         (g_stOsdUserData.stMbrData.b2MbrMode = (x))
#define GET_OSD_MBR_DUTY()                          (g_stOsdUserData.stMbrData.b7MbrDuty)
#define SET_OSD_MBR_DUTY(x)                         (g_stOsdUserData.stMbrData.b7MbrDuty = (x))
#define GET_OSD_MBR_POSITION()                      (g_stOsdUserData.stMbrData.b7MbrPosition)
#define SET_OSD_MBR_POSITION(x)                     (g_stOsdUserData.stMbrData.b7MbrPosition = (x))

//--------------------------------------------------
// Crosshair marco
//--------------------------------------------------
#define GET_OSD_CROSSHAIR()                         (g_stOsdUserData.ucCrosshair)
#define SET_OSD_CROSSHAIR(x)                        (g_stOsdUserData.ucCrosshair = (x))

//--------------------------------------------------
// Anti-Aliasing marco
//--------------------------------------------------
#define GET_ANTI_ALIASING_MODE()                    (g_stOsdUserData.stAntiAliasingData.ucAntiAliasingMode)
#define SET_ANTI_ALIASING_MODE(x)                   (g_stOsdUserData.stAntiAliasingData.ucAntiAliasingMode = (x))
#define GET_ANTI_ALIASING_LEVEL()                   (g_stOsdUserData.stAntiAliasingData.ucAntiAliasingLevel)
#define SET_ANTI_ALIASING_LEVEL(x)                  (g_stOsdUserData.stAntiAliasingData.ucAntiAliasingLevel = (x))

//--------------------------------------------------
// Energy Save marco
//--------------------------------------------------
#define GET_OSD_ENERGY_SAVER()                      (g_stOsdUserData.b1EnergySave)
#define SET_OSD_ENERGY_SAVER(x)                     (g_stOsdUserData.b1EnergySave = (x))

//==========================================================================================================
// Macro of NVRam Color Temp Data
//==========================================================================================================

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_R()                (g_stColorProcData.usColorTempR >> 4)
#define SET_COLOR_TEMP_TYPE_USER_R(x)               (g_stColorProcData.usColorTempR = ((x) << 4))

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_G()                (g_stColorProcData.usColorTempG >> 4)
#define SET_COLOR_TEMP_TYPE_USER_G(x)               (g_stColorProcData.usColorTempG = ((x) << 4))
//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_B()                (g_stColorProcData.usColorTempB >> 4)
#define SET_COLOR_TEMP_TYPE_USER_B(x)               (g_stColorProcData.usColorTempB = ((x) << 4))



//==========================================================================================================
// Macro of NVRam Input Source Data
//==========================================================================================================


//==========================================================================================================
// Macro of NVRam Input Port Data
//==========================================================================================================

//--------------------------------------------------
// MACRO for HDR Mode
//--------------------------------------------------
#define GET_OSD_HDR_MODE(port)                      (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].ucHdrMode)
#define SET_OSD_HDR_MODE(port, x)                   (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].ucHdrMode = (x))

//--------------------------------------------------
// Macro of Aspect Origin Ratio
//--------------------------------------------------
#define GET_OSD_ASPECT_ORIGIN_RATIO(port)           (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].ucAspectOriginRatio)
#define SET_OSD_ASPECT_ORIGIN_RATIO(port, x)        (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].ucAspectOriginRatio = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_ASPECT_RATIO_TYPE(port)             (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].b3AspectRatio)
#define SET_OSD_ASPECT_RATIO_TYPE(port, x)          (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].b3AspectRatio = (x))

//--------------------------------------------------
// MACRO for Sharpness
//--------------------------------------------------
#define GET_OSD_SHARPNESS(port)                     (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].b4Sharpness)
#define SET_OSD_SHARPNESS(port, x)                  (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].b4Sharpness = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_OVERSCAN_STATUS(port)               (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].b1OverScan)
#define SET_OSD_OVERSCAN_STATUS(port, x)            (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].b1OverScan = (x))


//==========================================================================================================
// Macro of NVRam Region Data
//==========================================================================================================
#define _INSIDE                                     0
#define _OUTSIDE                                    1

//--------------------------------------------------
// Macro of Color Temperature
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE(region)                 (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b4ColorTempType)
#define SET_COLOR_TEMP_TYPE(region, x)              (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b4ColorTempType = (x))

//--------------------------------------------------
// MACRO for Ultra Vivid Status
//--------------------------------------------------
#define GET_OSD_ULTRA_VIVID_STATUS(region)          (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b2UltraVividStatus)
#define SET_OSD_ULTRA_VIVID_STATUS(region, x)       (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b2UltraVividStatus = (x))

//--------------------------------------------------
// MACRO for OsdVPos
//--------------------------------------------------
#define GET_OSD_GAMMA(region)                       (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3Gamma)
#define SET_OSD_GAMMA(region, x)                    (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3Gamma = (x))

//--------------------------------------------------
// MACRO for Local Contrast
//--------------------------------------------------
#define GET_OSD_LOCAL_CONTRAST(region)              (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3LocalContrast)
#define SET_OSD_LOCAL_CONTRAST(region, x)           (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3LocalContrast = (x))

#define GET_OSD_LOCAL_CONTRAST_BLENDING(region)     (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucLocalContrastBlending)
#define SET_OSD_LOCAL_CONTRAST_BLENDING(region, x)  (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucLocalContrastBlending = (x))

#define GET_OSD_LOCAL_CONTRAST_DIFFGAIN(region)     (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucLocalContrastDiffGain)
#define SET_OSD_LOCAL_CONTRAST_DIFFGAIN(region, x)  (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucLocalContrastDiffGain = (x))

//--------------------------------------------------
// MACRO for SDR+
//--------------------------------------------------
#define GET_OSD_SDR_PLUS(region)                    (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1SdrPlus)
#define SET_OSD_SDR_PLUS(region, x)                 (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1SdrPlus = (x))

#define GET_OSD_SDR_PLUS_SHARP(region)              (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b7SdrPlusSharp)
#define SET_OSD_SDR_PLUS_SHARP(region, x)           (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b7SdrPlusSharp = (x))

#define GET_OSD_SDR_PLUS_DARK(region)               (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucSdrPlusDark)
#define SET_OSD_SDR_PLUS_DARK(region, x)            (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucSdrPlusDark = (x))

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
//--------------------------------------------------
// MACRO for Night Sniper
//--------------------------------------------------
#define GET_OSD_NIGHT_SNIPER(region)                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1NightSniper)
#define SET_OSD_NIGHT_SNIPER(region, x)             (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1NightSniper = (x))

#define GET_OSD_NIGHT_SNIPER_SAT(region)            (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b7NightSniperSat)
#define SET_OSD_NIGHT_SNIPER_SAT(region, x)         (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b7NightSniperSat = (x))

#define GET_OSD_NIGHT_SNIPER_LIGHT(region)          (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucNightSniperLight)
#define SET_OSD_NIGHT_SNIPER_LIGHT(region, x)       (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucNightSniperLight = (x))
#endif

//--------------------------------------------------
// MACRO for Color Effect
//--------------------------------------------------
#define GET_OSD_COLOR_EFFECT(region)                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b4ColorEffect)
#define SET_OSD_COLOR_EFFECT(region, x)             (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b4ColorEffect = (x))

//--------------------------------------------------
// MACRO for Hue
//--------------------------------------------------
#define GET_OSD_HUE(region)                         (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHue)
#define SET_OSD_HUE(region, x)                      (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHue = (x))

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_SATURATION(region)                  (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucSaturation)
#define SET_OSD_SATURATION(region, x)               (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucSaturation = (x))

//--------------------------------------------------
// MACRO for PCM Status
//--------------------------------------------------
#define GET_OSD_PCM_STATUS(region)                  (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3PCMStatus)
#define SET_OSD_PCM_STATUS(region, x)               (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3PCMStatus = (x))

//--------------------------------------------------
// MACRO for BRIGHTNESS
//--------------------------------------------------
#define GET_OSD_BRIGHTNESS(region)                  (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].usBrightness)
#define SET_OSD_BRIGHTNESS(region, x)               (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].usBrightness = (x))

//--------------------------------------------------
// MACRO for Contrast
//--------------------------------------------------
#define GET_OSD_CONTRAST(region)                    (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].usContrast)
#define SET_OSD_CONTRAST(region, x)                 (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].usContrast = (x))

//--------------------------------------------------
// MACRO for Panel Uniformity
//--------------------------------------------------
#define GET_OSD_PANEL_UNIFORMITY(region)            (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1PanelUniformity)
#define SET_OSD_PANEL_UNIFORMITY(region, x)         (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1PanelUniformity = (x))

//--------------------------------------------------
// MACRO for Dark Enhance Status
//--------------------------------------------------
#define GET_OSD_REGION_DARK_ENHANCE(region)         (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1HdrDarkEnhance)
#define SET_OSD_REGION_DARK_ENHANCE(region, x)      (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1HdrDarkEnhance = (x))

//--------------------------------------------------
// MACRO for Dark Enhance Status
//--------------------------------------------------
#define GET_OSD_REGION_HDR_SHARPNESS(region)        (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1HdrSharpnesse)
#define SET_OSD_REGION_HDR_SHARPNESS(region, x)     (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1HdrSharpnesse = (x))

//--------------------------------------------------
// MACRO for HDR Contrast Adjust
//--------------------------------------------------
#define GET_OSD_REGION_HDR_CONTRAST(region)         (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHdrContrast)
#define SET_OSD_REGION_HDR_CONTRAST(region, x)      (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHdrContrast = (x))

//--------------------------------------------------
// MACRO for HDR ColorEnhance
//--------------------------------------------------
#define GET_OSD_HDR_COLOR_ENHANCE(region)           (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHdrColorEnhance)
#define SET_OSD_HDR_COLOR_ENHANCE(region, x)        (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHdrColorEnhance = (x))
//--------------------------------------------------
// MACRO for HDR ColorEnhance
//--------------------------------------------------
#define GET_OSD_HDR_LIGHT_ENHANCE(region)           (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHdrLightEnhance)
#define SET_OSD_HDR_LIGHT_ENHANCE(region, x)        (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHdrLightEnhance = (x))

//--------------------------------------------------
// MACRO for HDR HLG OOTF
//--------------------------------------------------
#define GET_OSD_HDR_HLG_OOTF(region)                (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHdrHlgOotf)
#define SET_OSD_HDR_HLG_OOTF(region, x)             (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucHdrHlgOotf = (x))

//--------------------------------------------------
// MACRO for SDR to HDR
//--------------------------------------------------
#define GET_OSD_SDR_TO_HDR(region)                  (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1Sdr2HdrStatus)
#define SET_OSD_SDR_TO_HDR(region, x)               (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b1Sdr2HdrStatus = (x))


#if(_ICM_CHAMELEON_FUNCTION == _ON)
//--------------------------------------------------
// MACRO for CHAMELEON
//--------------------------------------------------
#define GET_OSD_CHAMELEON_HUE(region)               (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].usChameleonHue)
#define SET_OSD_CHAMELEON_HUE(region, x)            (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].usChameleonHue = (x))
#define GET_OSD_CHAMELEON_SAT(region)               (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucChameleonSat)
#define SET_OSD_CHAMELEON_SAT(region, x)            (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucChameleonSat = (x))
#define GET_OSD_CHAMELEON_LIGHTNESS(region)         (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucChameleonLightness)
#define SET_OSD_CHAMELEON_LIGHTNESS(region, x)      (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].ucChameleonLightness = (x))
#endif
//==========================================================================================================
// Macro of NVRam Display Mode Data
//==========================================================================================================
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for 1P Input Source
//--------------------------------------------------
#define GET_OSD_INPUT_SOURCE(x)                     (g_stOsdDisplayModeData.pucOsdInputPort[x])
#define SET_OSD_INPUT_SOURCE(x, port)               {\
                                                        if(GET_OSD_PXP_MST() == _DP_MST_PXP_OFF)\
                                                        {\
                                                            g_stOsdDisplayModeData.pucOsdInputPort[x] = (port);\
                                                            g_stOsdDisplayModeData.pucOsdInputPortBackup[x] = (port);\
                                                        }\
                                                        else\
                                                        {\
                                                            g_stOsdDisplayModeData.pucOsdInputPort[x] = (port);\
                                                        }\
                                                    }

//--------------------------------------------------
// MACRO for 1P Input Source
//--------------------------------------------------
#define GET_OSD_INPUT_SOURCE_BACK_UP(x)             (g_stOsdDisplayModeData.pucOsdInputPortBackup[x])
#define SET_OSD_INPUT_SOURCE_BACK_UP(x, port)       (g_stOsdDisplayModeData.pucOsdInputPortBackup[x] = (port))

//--------------------------------------------------
// MACRO for 1P Input Source
//--------------------------------------------------
#define GET_OSD_1P_INPUT_SOURCE_BACK_UP()           (GET_OSD_INPUT_SOURCE_BACK_UP(0))
#define SET_OSD_1P_INPUT_SOURCE_BACK_UP(x)          (SET_OSD_INPUT_SOURCE_BACK_UP(0, (x)))

//--------------------------------------------------
// MACRO for 2P Input Source
//--------------------------------------------------
#define GET_OSD_2P_INPUT_SOURCE_BACK_UP()           (GET_OSD_INPUT_SOURCE_BACK_UP(1))
#define SET_OSD_2P_INPUT_SOURCE_BACK_UP(x)          (SET_OSD_INPUT_SOURCE_BACK_UP(1, (x)))

//--------------------------------------------------
// MACRO for 1P Input Source
//--------------------------------------------------
#define GET_OSD_1P_INPUT_SOURCE()                   (GET_OSD_INPUT_SOURCE(0))
#define SET_OSD_1P_INPUT_SOURCE(x)                  {SET_OSD_INPUT_SOURCE(0, (x))}

//--------------------------------------------------
// MACRO for 2P Input Source
//--------------------------------------------------
#define GET_OSD_2P_INPUT_SOURCE()                   (GET_OSD_INPUT_SOURCE(1))
#define SET_OSD_2P_INPUT_SOURCE(x)                  {SET_OSD_INPUT_SOURCE(1, (x))}

//--------------------------------------------------
// MACRO for 3P Input Source
//--------------------------------------------------
#define GET_OSD_3P_INPUT_SOURCE()                   (GET_OSD_INPUT_SOURCE(2))
#define SET_OSD_3P_INPUT_SOURCE(x)                  {SET_OSD_INPUT_SOURCE(2, (x))}

//--------------------------------------------------
// MACRO for 4P Input Source
//--------------------------------------------------
#define GET_OSD_4P_INPUT_SOURCE()                   (GET_OSD_INPUT_SOURCE(3))
#define SET_OSD_4P_INPUT_SOURCE(x)                  {SET_OSD_INPUT_SOURCE(3, (x))}
#else
//--------------------------------------------------
// MACRO for 1P Input Source
//--------------------------------------------------
#define GET_OSD_INPUT_SOURCE(x)                     (g_stOsdDisplayModeData.pucOsdInputPort[x])
#define SET_OSD_INPUT_SOURCE(x, port)               (g_stOsdDisplayModeData.pucOsdInputPort[x] = (port))

//--------------------------------------------------
// MACRO for 1P Input Source
//--------------------------------------------------
#define GET_OSD_1P_INPUT_SOURCE()                   (GET_OSD_INPUT_SOURCE(0))
#define SET_OSD_1P_INPUT_SOURCE(x)                  (SET_OSD_INPUT_SOURCE(0, (x)))

//--------------------------------------------------
// MACRO for 2P Input Source
//--------------------------------------------------
#define GET_OSD_2P_INPUT_SOURCE()                   (GET_OSD_INPUT_SOURCE(1))
#define SET_OSD_2P_INPUT_SOURCE(x)                  (SET_OSD_INPUT_SOURCE(1, (x)))

//--------------------------------------------------
// MACRO for 3P Input Source
//--------------------------------------------------
#define GET_OSD_3P_INPUT_SOURCE()                   (GET_OSD_INPUT_SOURCE(2))
#define SET_OSD_3P_INPUT_SOURCE(x)                  (SET_OSD_INPUT_SOURCE(2, (x)))

//--------------------------------------------------
// MACRO for 4P Input Source
//--------------------------------------------------
#define GET_OSD_4P_INPUT_SOURCE()                   (GET_OSD_INPUT_SOURCE(3))
#define SET_OSD_4P_INPUT_SOURCE(x)                  (SET_OSD_INPUT_SOURCE(3, (x)))
#endif

//--------------------------------------------------
// MACRO for OSD Select Region
//--------------------------------------------------
#define GET_OSD_SYSTEM_SELECT_REGION()              (UserCommonRegionCheckSystemSelectRegion(UserAdjustConvertSystemSelectRegion(GET_OSD_SELECT_REGION())))
#define GET_OSD_SYSTEM_DISPLAY_REGION()             (UserAdjustConvertDisplayRegion(GET_OSD_SELECT_REGION()))
#if(_COLOR_DEMO_FUNCTION == _ON)
#define GET_OSD_SELECT_REGION()                     (UserAdjustCheckOsdSelectRegion())
#define SET_OSD_SELECT_REGION(x)                    (g_stOsdDisplayModeData.ucSelectRegion = (x))
#define GET_OSD_INVERSE_REGION()                    (UserAdjustCheckOsdInverseSelectRegion())
#else
#define GET_OSD_SELECT_REGION()                     (g_stOsdDisplayModeData.ucSelectRegion)
#define SET_OSD_SELECT_REGION(x)                    (g_stOsdDisplayModeData.ucSelectRegion = (x))
#define GET_OSD_INVERSE_REGION()                    ((g_stOsdDisplayModeData.ucSelectRegion & 0xFE) | (~g_stOsdDisplayModeData.ucSelectRegion & 0x01))
#endif



//--------------------------------------------------
// MACRO for Audio Input Region
//--------------------------------------------------
#define GET_OSD_AUDIO_SOURCE()                      (g_stOsdDisplayModeData.ucAuidioInputRegion)
#define SET_OSD_AUDIO_SOURCE(x)                     (g_stOsdDisplayModeData.ucAuidioInputRegion = (x))

//--------------------------------------------------
// MACRO for OSD DVision
//--------------------------------------------------
#define _OSD_DVISION_PICTURE_DARK                   0
#define _OSD_DVISION_PICTURE_BRIGHT                 1
#define _OSD_DVISION_PICTURE_GAME                   2
#define _OSD_DVISION_PICTURE_USER                   3
#define _OSD_DVISION_PICTURE_AMOUNT                 4
#if(_DM_FUNCTION == _ON)
#define GET_OSD_DVISION(port)                       (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].b7DVision)
#define SET_OSD_DVISION(port, x)                    (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].b7DVision = (x))
#define GET_OSD_DVISION_NOTICE(port)                (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].b1DVisionNotification)
#define SET_OSD_DVISION_NOTICE(port, x)             (g_pstOsdInputPortData[(port) % _OSD_INPUT_AMOUNT].b1DVisionNotification = (x))

#define GET_DVISION_PICTURE(region)                 (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3DVisionPicture)
#define SET_DVISION_PICTURE(region, x)              (g_pstOsdRegionData[RTDNVRamTransferOsdRegionType(GET_OSD_DISPLAY_MODE(), (region))].b3DVisionPicture = (x))

#define GET_DVISION_PICTURE_MODIFY(region)          (RTDNVRamGetDVisionModeData(_OSD_DVISION_PICTURE, (region)))
#define SET_DVISION_PICTURE_MODIFY(region, x)       (RTDNVRamSetDVisionModeData(_OSD_DVISION_PICTURE, (x), (region)))
#define GET_DVISION_BACKLIGHT(region)               (RTDNVRamGetDVisionModeData(_OSD_DVISION_BACKLIGHT, (region)))
#define SET_DVISION_BACKLIGHT(region, x)            (RTDNVRamSetDVisionModeData(_OSD_DVISION_BACKLIGHT, (x), (region)))
#define GET_DVISION_BRIGHTNESS(region)              (RTDNVRamGetDVisionModeData(_OSD_DVISION_BRIGHTNESS, (region)))
#define SET_DVISION_BRIGHTNESS(region, x)           (RTDNVRamSetDVisionModeData(_OSD_DVISION_BRIGHTNESS, (x), (region)))
#define GET_DVISION_CONTRAST(region)                (RTDNVRamGetDVisionModeData(_OSD_DVISION_CONTRAST, (region)))
#define SET_DVISION_CONTRAST(region, x)             (RTDNVRamSetDVisionModeData(_OSD_DVISION_CONTRAST, (x), (region)))
#define GET_DVISION_SATURATION(region)              (RTDNVRamGetDVisionModeData(_OSD_DVISION_SATURATION, (region)))
#define SET_DVISION_SATURATION(region, x)           (RTDNVRamSetDVisionModeData(_OSD_DVISION_SATURATION, (x), (region)))
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for OSD DVision
//--------------------------------------------------
#define GET_OSD_ARC_OUT()                           (g_stAudioArcData.b2ArcAudioOut)
#define SET_OSD_ARC_OUT(x)                          (g_stAudioArcData.b2ArcAudioOut = (x))
#define GET_OSD_ARC_PORT()                          (g_stAudioArcData.ucInputport)
#define SET_OSD_ARC_PORT(x)                         (g_stAudioArcData.ucInputport = (x))
#define GET_OSD_ARC_MODE()                          (g_stAudioArcData.ucArcType)
#define SET_OSD_ARC_MODE(x)                         (g_stAudioArcData.ucArcType = (x))
#define GET_OSD_ARC_MUTE_STATUS()                   (g_stAudioArcData.b2ArcMute)
#define SET_OSD_ARC_MUTE_STATUS(x)                  (g_stAudioArcData.b2ArcMute = (x))
#define GET_OSD_ARC_CHANEL()                        (g_stAudioArcData.b3ArcChanel)
#define SET_OSD_ARC_CHANEL(x)                       (g_stAudioArcData.b3ArcChanel = (x))
#endif
//--------------------------------------------------
// MACRO for Factory Power Saving Case
//--------------------------------------------------
#define GET_FORCE_POW_SAV_STATUS()                  (g_bPowerForcePowSavStatus)
#define SET_FORCE_POW_SAV_STATUS(x)                 (g_bPowerForcePowSavStatus = (x))

//--------------------------------------------------
// Definitions of OSD Number ROW COL
//--------------------------------------------------
#define _MENU_1ST_ITEM_MAX                          8
#define _MENU_2ND_ITEM_ROW_ST                       4
#define _MENU_2ND_ITEM_COL_ST                       14
#define _MENU_2ND_ITEM_WIDTH                        12
#define _MENU_2ND_ITEM_MAX                          8
#define _MENU_2ND_ITEM_VAL_COL_ST                   (_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH + 2)
#define _MENU_3RD_ITEM_ADJBAR_ST                    (_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH + 9)
#define _MENU_3RD_ITEM_WIDTH                        15

#define _MENU_3RD_ITEM_ROW_ST                       6
#define _MENU_3RD_ITEM_LIST_ST                      (_MENU_2ND_ITEM_COL_ST + _MENU_2ND_ITEM_WIDTH + 3)
#define _MENU_3RD_ITEM_LIST_WIDTH                   (_MENU_3RD_ITEM_WIDTH - 2)
#define _MENU_3RD_ITEM_MAX                          6

#define _MENU_4TH_ITEM_ROW_ST                       _MENU_3RD_ITEM_ROW_ST
#define _MENU_4TH_ITEM_LIST_ST                      _MENU_3RD_ITEM_LIST_ST
#define _MENU_4TH_ITEM_LIST_WIDTH                   _MENU_3RD_ITEM_LIST_WIDTH
#define _MENU_4TH_ITEM_MAX                          4

#define _OSD_NUMBER_1_ROW                           (_MENU_2ND_ITEM_ROW_ST + 5)
#define _OSD_NUMBER_1_COL                           (_MENU_2ND_ITEM_VAL_COL_ST + 2)

#define _OSD_NUMBER_UNSTLECT_COLOR                  COLOR(_CP_ORANGE, _CP_BG)

//--------------------------------------------------
// Definitions of OSD
//--------------------------------------------------
#define _PFONT_PAGE_0                               0
#define _PFONT_PAGE_1                               1
#define _PFONT_PAGE_2                               2
#define _PFONT_PAGE_3                               3 // Only for Slide Bar Number used
#define _OSD_GLOBAL_START                           0x001
#define _OSD_GLOBAL_END                             0x00F

#define _OSD_PAGE_0_START                           0x100
#define _OSD_PAGE_0_END                             0x190

#define _OSD_PAGE_1_START                           0x200
#define _OSD_PAGE_1_END                             0x280

#define _OSD_PAGE_2_START                           0x1A0
#define _OSD_PAGE_2_END                             0x1F0
#define _OSD_PAGE_3_START                           0x281
#define _OSD_PAGE_3_END                             0x2CF

//--------------------------------------------------
// Definitions of OSD Window
//--------------------------------------------------
//=========== OSD Window Setting ======================//
//Blending type1:Only windows blending.
//Blending type2:All blending.
//Blending type3:Windows & Character background blending.
#define _WIN0                                       0
#define _WIN1                                       1
#define _WIN2                                       2
#define _WIN3                                       3
#define _WIN4                                       4
#define _WIN5                                       5
#define _WIN6                                       6
#define _WIN7                                       7
#define _WIN8                                       8
#define _WIN9                                       9
#define _WIN_ALL                                    0xFF

#define _WIN0_TRANS                                 (_BIT7 | 0)
#define _WIN1_TRANS                                 (_BIT7 | 1)
#define _WIN2_TRANS                                 (_BIT7 | 2)
#define _WIN3_TRANS                                 (_BIT7 | 3)
#define _WIN4_TRANS                                 (_BIT7 | 4)
#define _WIN5_TRANS                                 (_BIT7 | 5)
#define _WIN6_TRANS                                 (_BIT7 | 6)
#define _WIN7_TRANS                                 (_BIT7 | 7)

#define COLOR(fg, bg)                               ((fg) << 4 | (bg))
#define COLOR0(x)                                   (x)
#define COLOR1(x)                                   (x)
#define COLOR2(x)                                   (x)
#define COLOR3(x)                                   (x)

#define X_START(x)                                  (x)
#define Y_START(x)                                  (x)
#define X_END(x)                                    (x)
#define Y_END(x)                                    (x)

#define _BORDER0_1_PIXEL                            0
#define _BORDER0_2_PIXEL                            1
#define _BORDER0_3_PIXEL                            2
#define _BORDER0_4_PIXEL                            3
#define _BORDER0_5_PIXEL                            4
#define _BORDER0_6_PIXEL                            5
#define _BORDER0_7_PIXEL                            6
#define _BORDER0_8_PIXEL                            7

#define _BORDER1_1_PIXEL                            0x00
#define _BORDER1_2_PIXEL                            0x08
#define _BORDER1_3_PIXEL                            0x10
#define _BORDER1_4_PIXEL                            0x18
#define _BORDER1_5_PIXEL                            0x20
#define _BORDER1_6_PIXEL                            0x28
#define _BORDER1_7_PIXEL                            0x30
#define _BORDER1_8_PIXEL                            0x38

#define _BLEND_DISABLE                              0
#define _BLEND_ENABLE                               0x80
#define _GRADIENT_DISABLE                           0
#define _GRADIENT_ENABLE                            0x40
#define _GRADIENT_DIRECTION_H                       0
#define _GRADIENT_DIRECTION_V                       0x20
#define _BORDER_DISABLE                             0
#define _BORDER_ENABLE                              0x10

#define _1_LEVEL_RER_GRADIENT                       0x20
#define _2_LEVEL_RER_GRADIENT                       0x40
#define _3_LEVEL_RER_GRADIENT                       0x60
#define _4_LEVEL_RER_GRADIENT                       0x80
#define _5_LEVEL_RER_GRADIENT                       0xA0
#define _6_LEVEL_RER_GRADIENT                       0xC0
#define _7_LEVEL_RER_GRADIENT                       0xE0
#define _8_LEVEL_RER_GRADIENT                       0x00

#define _R_GRADIENT_DEC                             0x00
#define _R_GRADIENT_INC                             0x80
#define _G_GRADIENT_DEC                             0x00
#define _G_GRADIENT_INC                             0x40
#define _B_GRADIENT_DEC                             0x00
#define _B_GRADIENT_INC                             0x20

#define _GRADIENT_LEVEL_1                           0
#define _GRADIENT_LEVEL_2                           0x08
#define _GRADIENT_LEVEL_3                           0x10
#define _GRADIENT_LEVEL_4                           0x18

#define _R_GRADIENT_ENABLE                          0x04
#define _R_GRADIENT_DISABLE                         0x00
#define _G_GRADIENT_ENABLE                          0x02
#define _G_GRADIENT_DISABLE                         0x00
#define _B_GRADIENT_ENABLE                          0x01
#define _B_GRADIENT_DISABLE                         0x00

#define _SHADOW_1                                   0x00
#define _SHADOW_2                                   0x02
#define _SHADOW_3                                   0x04
#define _SHADOW_4                                   0x06
#define _3D_BUTTON_1                                0x08
#define _3D_BUTTON_2                                0x0A

#define _OSD_UNSELECT                               0
#define _OSD_SELECT                                 1
#define _OSD_REJECT                                 2
#define _OSD_ADJUST                                 3
#define _OSD_UNHIGHLIGHT                            4
#define _OSD_HIGHLIGHT                              5
#define _OSD_PRE_SELECT                             6
#define _OSD_SELECT_ADJUST                          7


#define _KEY_INFO_ENTER                             0
#define _KEY_INFO_RIGHT                             1
#define _KEY_INFO_LEFT                              2
#define _KEY_INFO_EXIT                              3
#define _KEY_INFO_BACK                              4
#define _KEY_INFO_ALL                               5   // exit, left, right, enter

//=========== OSD Font Icon Address ======================//
#define _1GLOBAL_START                              0x00                        // Global 49
#define _1DYNAMIC_START                             (_1GLOBAL_START + 50)       // Dynamic 0
#define _1DYNAMIC_ICON_START                        (_1DYNAMIC_START + 0)       // main menu icon (6 x 4 x 8) = 196
#define _2DYNAMIC_START                             0x00
#define _2BIT_ICON_OFFSET                           0xFF
#define _4BIT_ICON_OFFSET                           0x00
#if(_DM_FUNCTION == _ON)
#define _DM_ICON_START                              0xD0
#endif
#define _LOGO_START_ADDRESS                         0x00

#define _1BIT_NOTICE_ICON_START                     0x01 // 0x18    // No signal , No support , No cable need 24 x 3 x 3 = 216
#define _1BIT_NOTICE_NO_SUPPORT_ICON                (_1BIT_NOTICE_ICON_START)
#define _1BIT_NOTICE_NO_SUPPORT_TEXT_0              (_1BIT_NOTICE_NO_SUPPORT_ICON + 24)
#define _1BIT_NOTICE_NO_SUPPORT_TEXT_1              (_1BIT_NOTICE_NO_SUPPORT_TEXT_0 + 24)
#define _1BIT_NOTICE_NO_CABLE_ICON                  (_1BIT_NOTICE_NO_SUPPORT_TEXT_1 + 24)
#define _1BIT_NOTICE_NO_CABLE_TEXT_0                (_1BIT_NOTICE_NO_CABLE_ICON + 24)
#define _1BIT_NOTICE_NO_CABLE_TEXT_1                (_1BIT_NOTICE_NO_CABLE_TEXT_0 + 24)
#define _1BIT_NOTICE_NO_SIGNAL_ICON                 (_1BIT_NOTICE_NO_CABLE_TEXT_1 + 24)
#define _1BIT_NOTICE_NO_SIGNAL_TEXT_0               (_1BIT_NOTICE_NO_SIGNAL_ICON + 24)
#define _1BIT_NOTICE_NO_SIGNAL_TEXT_1               (_1BIT_NOTICE_NO_SIGNAL_TEXT_0 + 24)
#define _1BIT_NOTICE_INFORMATION                    (_1BIT_NOTICE_NO_SIGNAL_TEXT_1 + 24)

//=============== 1Bit Icon ========================

typedef enum
{
    ___ = 0,
    _iREALTEK_00,
    _iREALTEK_01,
    _iREALTEK_02,
    _iREALTEK_03,
    _iREALTEK_04,
    _iREALTEK_05,
    _iREALTEK_06,
    _iREALTEK_07,
    _iREALTEK_08,
    _iREALTEK_09,
    _iREALTEK_0A,
    _iREALTEK_0B,
    _iREALTEK_10,
    _iREALTEK_11,
    _iREALTEK_12,
    _iREALTEK_13,
    _iREALTEK_14,
    _iREALTEK_15,
    _iREALTEK_16,
    _iREALTEK_17,
    _iREALTEK_18,
    _iREALTEK_19,
    _iREALTEK_1A,
    _iREALTEK_1B,
    _iLEFT_00,
    _iLEFT_01,
    _iRIGHT_00,
    _iRIGHT_01,
    _iKEY_BACK_00,
    _iKEY_BACK_01,
    _iKEY_BACK_10,
    _iKEY_BACK_11,
    _iKEY_LEFT_00,
    _iKEY_LEFT_01,
    _iKEY_LEFT_10,
    _iKEY_LEFT_11,
    _iKEY_RIGHT_00,
    _iKEY_RIGHT_01,
    _iKEY_RIGHT_10,
    _iKEY_RIGHT_11,
    _iKEY_ENTER_00,
    _iKEY_ENTER_01,
    _iKEY_ENTER_10,
    _iKEY_ENTER_11,
    _iKEY_EXIT_00,
    _iKEY_EXIT_01,
    _iKEY_EXIT_10,
    _iKEY_EXIT_11,
    _iINDICATE,
}EnumOneBitGLOBAL;

#define _4BIT_REALTEK_LOGO_ST                       0xF0

//RTD LOGO
#define _OSD_LOGOA_WIDTH                            840
#define _OSD_LOGOA_HEIGHT                           180
#define _LOGO_WINDOW_SIZE_X                         _OSD_LOGOA_WIDTH
#define _LOGO_WINDOW_SIZE_Y                         _OSD_LOGOA_HEIGHT


//---------------------------------------------------------------------
// Definitions of OSD Show Number Function Used by OsdDisplayShowNumber()
//---------------------------------------------------------------------
#define _ALIGN_LEFT                                 (0)
#define _ALIGN_RIGHT                                (1)

#define _FORCE_SHOW_NUMBER_OFF                      (0 << 1)
#define _FORCE_SHOW_NUMBER_ON                       (1 << 1)

#define _SHOW_1                                     (0 << 4)
#define _SHOW_2                                     (1 << 4)
#define _SHOW_3                                     (2 << 4)
#define _SHOW_4                                     (3 << 4)
#define _SHOW_5                                     (4 << 4)
#define _SHOW_6                                     (5 << 4)

//------------------------------------------------------
// Definitions of OSD Slider Function Used by OsdDisplaySlider()
//------------------------------------------------------
#define _SLIDER_RESOLUTION                          (10)

#define _PALETTE_INDEX0                             0   // 0 ~ 15
#define _PALETTE_INDEX1                             1   // 16 ~ 31
#define _PALETTE_INDEX2                             2   // 32 ~ 47
#define _PALETTE_INDEX3                             3   // 48 ~ 63

// OSD Position
#define _POS_DIRECT                                 0
#define _POS_PERCENT                                1

//--------------------------------------------------
// Definitions of OSD MAIN MENU
//--------------------------------------------------
#define _OSD_MAIN_MENU_WIDTH                        44
#define _OSD_MAIN_MENU_HEIGHT                       22

//--------------------------------------------------
// Definitions of corsshair
//--------------------------------------------------
#define _OSD_CROSSHAIR_WIDTH                        3
#define _OSD_CROSSHAIR_HEIGHT                       3

//--------------------------------------------------
// Definitions of OSD MSG MENU
//--------------------------------------------------
#define _OSD_MSG_MENU_WIDTH                         36
#define _OSD_MSG_MENU_HEIGHT                        8

#define _OSD_HOTKEY_MENU_WIDTH                      36
#define _OSD_HOTKEY_MENU_HEIGHT                     8

#define _OSD_HOTKEY_SOURCE_MENU_WIDTH               64
#define _OSD_HOTKEY_SOURCE_MENU_HEIGHT              8

#define _OSD_2PLR_INFO_MENU_WIDTH                   48
#define _OSD_2PLR_INFO_MENU_HEIGHT                  8

#define _OSD_2PTB_INFO_MENU_WIDTH                   24
#define _OSD_2PTB_INFO_MENU_HEIGHT                  16

#define _OSD_2PPIP_INFO_MENU_WIDTH                  48
#define _OSD_2PPIP_INFO_MENU_HEIGHT                 16

#define _OSD_4P_INFO_MENU_WIDTH                     48
#define _OSD_4P_INFO_MENU_HEIGHT                    16

//--------------------------------------------------
// Definitions of OSD Type
//--------------------------------------------------

#define _OSD_MESSAGE_ROW_START                      2
#define _OSD_MESSAGE_COL_START                      12
#define _OSD_MESSAGE_STRING_LENGHT                  23

//--------------------------------------------------
// Definitions of HL window Border Size
//--------------------------------------------------
#define _HL_WIN_BORDER_SIZE                         2

//--------------------------------------------------
// Definitions of Slider
//--------------------------------------------------
#define _SLIDER_LENGHT                              120 // 250
#define _SLIDER_HIGH                                18 // 20
#define _SLIDER_BORDER_PIXEL                        1 // 2
#define _SLIDER_OFFSET                              6

#define _SLIDER_SELECT_BORDER_COLOR                 _CP_GRAY
#define _SLIDER_SELECT_BG_COLOR                     _CP_WHITE

#define _SLIDER_UNSELECT_BORDER_COLOR               _CP_WHITE
#define _SLIDER_UNSELECT_BG_COLOR                   _CP_GRAY

#define _SLIDER_SELECT_COLOR                        _CP_ORANGE
#define _SLIDER_UNSELECT_COLOR                      _CP_BLUE

#define _SLIDER_0                                   0
#define _SLIDER_1                                   1
#define _SLIDER_2                                   2

#define _SELECT                                     1
#define _UNSELECT                                   0

#define _SLIDER_0_ROW                               (_MENU_2ND_ITEM_ROW_ST + 2)// 16
#define _SLIDER_0_COL                               (_MENU_3RD_ITEM_ADJBAR_ST)// 11

#define _ITEM_0                                     0
#define _ITEM_1                                     1
#define _ITEM_2                                     2
#define _ITEM_3                                     3
#define _ITEM_4                                     4
#define _ITEM_5                                     5
#define _ITEM_6                                     6
#define _ITEM_7                                     7

#define _NONE_ITEM                                  8

#define _FONTFROM_0_255                             0x00
#define _FONTFROM_256_512                           _BIT5

//--------------------------------------------------
// Definitions of No signal & No cable & No support BLANK_SIZE
//--------------------------------------------------
#define _FONT_WIDTH                                 12
#define _FONT_HEIGHT                                18
#define _MESSAGE_WIDTH_FONT_NUM                     36
#define _MESSAGE_HEIGHT_FONT_NUM                    8
#define _MESSAGE_HEIGHT_MID_FONT_NUM                (_MESSAGE_HEIGHT_FONT_NUM / 2) // (8/2)
#define _MESSAGE_WIDTH_MID_FONT_NUM                 (_MESSAGE_WIDTH_FONT_NUM / 2)  // (36/2)

//--------------------------------------------------
// Definitions of Color effect user mode Hue & Saturation
//--------------------------------------------------
#define _COLOR_HUE                                  0
#define _COLOR_SATURATION                           1

//--------------------------------------------------
// Definitions of Percentage
//--------------------------------------------------
#define _0_PERCENT                                  0
#define _50_PERCENT                                 50
#define _100_PERCENT                                100
#define _BAR_BORDER                                 2

//--------------------------------------------------
// Definitions of Highlight Window
//--------------------------------------------------
#define _SLIDER_0_BAR_WINDOW                        _OSD_WINDOW_17
#define _SLIDER_0_BG_WINDOW                         _OSD_WINDOW_16
#define _SLIDER_0_BORDER_WINDOW                     _OSD_WINDOW_15

#define _SLIDER_1_BAR_WINDOW                        _OSD_WINDOW_17
#define _SLIDER_1_BG_WINDOW                         _OSD_WINDOW_16
#define _SLIDER_1_BORDER_WINDOW                     _OSD_WINDOW_15

#define _OSD_WIN_HIGHLIGHT_1                        _OSD_WINDOW_24
#define _OSD_WIN_HIGHLIGHT_2                        _OSD_WINDOW_25
#define _OSD_WIN_HIGHLIGHT_3                        _OSD_WINDOW_13
#define _OSD_WIN_HIGHLIGHT_3_BORDER                 _OSD_WINDOW_12

#define _OSD_WIN_HIGHLIGHT_4                        _OSD_WINDOW_30
#define _OSD_WIN_HIGHLIGHT_5                        _OSD_WINDOW_31

#define _OSD_WIN_GRID_1                             _OSD_WINDOW_2
#define _OSD_WIN_GRID_2                             _OSD_WINDOW_3
#define _OSD_WIN_GRID_3                             _OSD_WINDOW_4
#define _OSD_WIN_GRID_4                             _OSD_WINDOW_5
#define _OSD_WIN_GRID_5                             _OSD_WINDOW_6
#define _OSD_WIN_GRID_6                             _OSD_WINDOW_7
#define _OSD_WIN_GRID_7                             _OSD_WINDOW_8

//--------------------------------------------------
// Definitions of 4 Bit Font - Byte0
//--------------------------------------------------
#define _OSD_4_BIT_BYTE0                            0xC0

//--------------------------------------------------
// Definitions of 1 Bit Font - Byte0
//--------------------------------------------------
#define _OSD_1_BIT_BYTE0                            0x40
#define _OSD_1_BIT_BYTE0_ROTATE                     0x40
#define _OSD_MODE_BYTE0                             _OSD_1_BIT_BYTE0
#define _OSD_MODE_BYTE0_256_511                     (_OSD_1_BIT_BYTE0 | _BIT0)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _ADJ_BAR_REAL,
    _ADJ_BAR_PERCENT,
    _ADJ_BAR_10_TIMES,
    _ADJ_LIST,
    _ADJ_DIRECT,
}EnumAdjType;

//--------------------------------------------------
// Define enter panel uniformity msg adjust from pcm or gamma
//--------------------------------------------------
typedef enum
{
    _FROM_STATE_PCM,
    _FROM_STATE_GAMMA,
    _FROM_STATE_HDR,
    _FROM_STATE_LD,
    _FROM_STATE_SDRTOHDR,
}EnumFromWhichState;


//--------------------------------------------------
// Define PCM Soft Proft
//--------------------------------------------------
typedef enum
{
    _PCM_SOFT_MODE_1,
    _PCM_SOFT_MODE_2,
    _PCM_SOFT_MODE_AMOUNT = _PCM_SOFT_MODE_2,
}EnumPCMSoftProftMode;

//--------------------------------------------------
// Define Gamma
//--------------------------------------------------
typedef enum
{
    _GAMMA_OFF,
    _GAMMA_18,
    _GAMMA_20,
    _GAMMA_22,
    _GAMMA_24,
    _GAMMA_AMOUNT = _GAMMA_24,
}EnumGammaType;

//--------------------------------------------------
// Definitions of Display Mode
//--------------------------------------------------
typedef enum
{
    _OSD_DM_1P,
    _OSD_DM_2P_LR,
    _OSD_DM_2P_TB,
    _OSD_DM_2P_PIP,
    _OSD_DM_3P_FLAG,
    _OSD_DM_3P_SKEW_L,
    _OSD_DM_3P_SKEW_R,
    _OSD_DM_3P_SKEW_T,
    _OSD_DM_3P_SKEW_B,
    _OSD_DM_4P,
    _OSD_DM_AMOUNT,
}EnumOSDDisplayModeDef;

//--------------------------------------------------
// Definitions of Display State Notice Message
//--------------------------------------------------
typedef enum
{
    _OSD_NOTICE_NONE,
    _OSD_NOTICE_KEEP,
    _OSD_NOTICE_NO_SUPPORT,
    _OSD_NOTICE_NO_CABLE,
    _OSD_NOTICE_NO_SIGNAL,
    _OSD_NOTICE_INFO,
    _OSD_NOTICE_AMOUNT,
}EnumOSDDisplayDisplayStateNoticeDef;

//--------------------------------------------------
// Definitions of Select Region
//--------------------------------------------------
typedef enum
{
    _OSD_SR_1P_FULL,
}EnumOSDSelectRegion1PDef;

typedef enum
{
    _OSD_SR_EAGLESIGHT_MAIN,
    _OSD_SR_EAGLESIGHT_SUB,
    _OSD_SR_EAGLESIGHT_FULL,
}EnumOSDEaglesightSelectRegionDef;

typedef enum
{
    _OSD_SR_2P_LR_L,
    _OSD_SR_2P_LR_R,
    _OSD_SR_2P_LR_FULL,
}EnumOSDSelectRegion2PLRDef;

typedef enum
{
    _OSD_SR_2P_TB_T,
    _OSD_SR_2P_TB_B,
    _OSD_SR_2P_TB_FULL,
}EnumOSDSelectRegion2PTBDef;

typedef enum
{
    _OSD_SR_2P_PIP_MAIN,
    _OSD_SR_2P_PIP_SUB,
    _OSD_SR_2P_PIP_FULL,
}EnumOSDSelectRegion2PPIPDef;

typedef enum
{
    _OSD_SR_2P_PIP_EAGLE_SIGHT_MAIN,
    _OSD_SR_2P_PIP_EAGLE_SIGHT_SUB,
    _OSD_SR_2P_PIP_EAGLE_SIGHT_FULL,
}EnumOSDSelectRegion2PPIPEagleSightDef;

typedef enum
{
    _OSD_SR_3P_FLAG_MAIN,
    _OSD_SR_3P_FLAG_MAIN_OUT,
    _OSD_SR_3P_FLAG_L,
    _OSD_SR_3P_FLAG_L_OUT,
    _OSD_SR_3P_FLAG_R,
    _OSD_SR_3P_FLAG_R_OUT,
    _OSD_SR_3P_FLAG_FULL,
}EnumOSDSelectRegion3PFlagDef;
typedef enum
{
    _OSD_SR_3P_SKEW_R_MAIN,
    _OSD_SR_3P_SKEW_R_MAIN_OUT,
    _OSD_SR_3P_SKEW_R_UP,
    _OSD_SR_3P_SKEW_R_UP_OUT,
    _OSD_SR_3P_SKEW_R_DOWN,
    _OSD_SR_3P_SKEW_R_DOWN_OUT,
    _OSD_SR_3P_SKEW_R_FULL,
}EnumOSDSelectRegion3PSkewRDef;
typedef enum
{
    _OSD_SR_3P_SKEW_L_MAIN,
    _OSD_SR_3P_SKEW_L_MAIN_OUT,
    _OSD_SR_3P_SKEW_L_UP,
    _OSD_SR_3P_SKEW_L_UP_OUT,
    _OSD_SR_3P_SKEW_L_DOWN,
    _OSD_SR_3P_SKEW_L_DOWN_OUT,
    _OSD_SR_3P_SKEW_L_FULL,
}EnumOSDSelectRegion3PSkewLDef;
typedef enum
{
    _OSD_SR_3P_SKEW_T_MAIN,
    _OSD_SR_3P_SKEW_T_MAIN_OUT,
    _OSD_SR_3P_SKEW_T_LEFT,
    _OSD_SR_3P_SKEW_T_LEFT_OUT,
    _OSD_SR_3P_SKEW_T_RIGHT,
    _OSD_SR_3P_SKEW_T_RIGHT_OUT,
    _OSD_SR_3P_SKEW_T_FULL,
}EnumOSDSelectRegion3PSkewTDef;
typedef enum
{
    _OSD_SR_3P_SKEW_B_MAIN,
    _OSD_SR_3P_SKEW_B_MAIN_OUT,
    _OSD_SR_3P_SKEW_B_LEFT,
    _OSD_SR_3P_SKEW_B_LEFT_OUT,
    _OSD_SR_3P_SKEW_B_RIGHT,
    _OSD_SR_3P_SKEW_B_RIGHT_OUT,
    _OSD_SR_3P_SKEW_B_FULL,
}EnumOSDSelectRegion3PSkewBDef;
typedef enum
{
    _OSD_SR_4P_LT_INSIDE,
    _OSD_SR_4P_LT_OUTSIDE,
    _OSD_SR_4P_LB_INSIDE,
    _OSD_SR_4P_LB_OUTSIDE,
    _OSD_SR_4P_RT_INSIDE,
    _OSD_SR_4P_RT_OUTSIDE,
    _OSD_SR_4P_RB_INSIDE,
    _OSD_SR_4P_RB_OUTSIDE,
    _OSD_SR_4P_FULL,
}EnumOSDSelectRegion4PDef;

//--------------------------------------------------
// Definitions of 2P/4P Input Source
//--------------------------------------------------
typedef enum
{
    _OSD_HOTKEY_INPUT_1P,
    _OSD_HOTKEY_INPUT_2P,
    _OSD_HOTKEY_INPUT_3P,
    _OSD_HOTKEY_INPUT_4P,
}EnumOSDS_HOTKEY_INPUTDef;

//--------------------------------------------------
// Define Color Effect
//--------------------------------------------------
typedef enum
{
    _COLOREFFECT_STANDARD,
    _COLOREFFECT_GAME,
    _COLOREFFECT_MOVIE,
    _COLOREFFECT_PHOTO,
    _COLOREFFECT_VIVID,
    _COLOREFFECT_USER,
#if(_ICM_CHAMELEON_FUNCTION == _OFF)
    _COLOREFFECT_AMOUNT = _COLOREFFECT_USER,
#else
    _COLOREFFECT_CHAMELEON,
    _COLOREFFECT_AMOUNT = _COLOREFFECT_CHAMELEON,
#endif
}EnumColorEffectType;

//--------------------------------------------------
// Define Ultra Vivid
//--------------------------------------------------
typedef enum
{
    _ULTRA_VIVID_OFF,
    _ULTRA_VIVID_L,
    _ULTRA_VIVID_M,
    _ULTRA_VIVID_H,
    _ULTRA_VIVID_AMOUNT = _ULTRA_VIVID_H,
}EnumUltraVividType;

//--------------------------------------------------
// Define Anti-Aliasing
//--------------------------------------------------
typedef enum
{
    _ANTI_ALIASING_EDGE_ENHANCE,
    _ANTI_ALIASING_NOISE_REDUCTION,
    _ANTI_ALIASING_MODE_AMOUNT = _ANTI_ALIASING_NOISE_REDUCTION,
}EnumAntiAliasingModeType;

//--------------------------------------------------
// Define Local Contrast
//--------------------------------------------------
typedef enum
{
    _LOCAL_CONTRAST_OFF,
    _LOCAL_CONTRAST_L,
    _LOCAL_CONTRAST_M,
    _LOCAL_CONTRAST_H,
#if(_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON)
    _LOCAL_CONTRAST_USER,
    _LOCAL_CONTRAST_AMOUNT = _LOCAL_CONTRAST_USER,
#else
    _LOCAL_CONTRAST_AMOUNT = _LOCAL_CONTRAST_H,
#endif
}EnumLocalContrastType;

typedef enum
{
    _LOCALCONTRAST_TEMPORAL_TYPE_24,
    _LOCALCONTRAST_TEMPORAL_TYPE_60,
    _LOCALCONTRAST_TEMPORAL_TYPE_120,
    _LOCALCONTRAST_TEMPORAL_TYPE_144,
    _LOCALCONTRAST_TEMPORAL_TYPE_165,
    _LOCALCONTRAST_TEMPORAL_TYPE_240,
}EnumLocalContrastTemporalType;
//--------------------------------------------------
// Define Supported Aspect Ratios
//--------------------------------------------------
typedef enum
{
    _OSD_ASPECT_RATIO_FULL,
    _OSD_ASPECT_RATIO_16_BY_9,
    _OSD_ASPECT_RATIO_4_BY_3,
    _OSD_ASPECT_RATIO_5_BY_4,
    _OSD_ASPECT_RATIO_ORIGIN,
    _OSD_ASPECT_RATIO_REDUCE,
    _OSD_ASPECT_RATIO_ENLARGE,
    _OSD_ASPECT_RATIO_USER,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_ENLARGE,
}EnumAspectRatioTypeIndex;

//--------------------------------------------------
// Define DP Port Version
//--------------------------------------------------
typedef enum
{
    _DP_VER_1_DOT_1 = 0,
    _DP_VER_1_DOT_2,
    _DP_VER_1_DOT_4,
    _DP_VER_2_DOT_0,
#if((_DP_ADAPTIVESYNC_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON) || (_DP_PR_MODE_SUPPORT == _ON) || (_DP_AUXLESS_ALPM_SUPPORT == _ON))
    _DP_VER_AMOUNT = _DP_VER_2_DOT_0,
#else
    _DP_VER_AMOUNT = _DP_VER_1_DOT_4,
#endif
}EnumOSDDpPortVersionDef;

typedef enum
{
    _MST_OFF = 0,
    _MST_AUTO,
    _MST_D0,
    _MST_D1,
    _MST_D2,
    _MST_D6,
    _MST_AMOUNT = _MST_D2,
}EnumOSDDpMstTypeDef;

//--------------------------------------------------
// Define DSC Port enable
//--------------------------------------------------
typedef enum
{
    _DSC_OFF = 0,
    _DSC_AUTO,
}EnumOSDDscTypeDef;

//--------------------------------------------------
// Define Display Image Rotate
//--------------------------------------------------
typedef enum
{
    _DISP_ROTATE_0 = 0,
#if(_HW_DISPLAY_ROTATION_180_SUPPORT == _ON)
    _DISP_ROTATE_180,
#endif
#if(_HW_DISPLAY_ROTATION_90_SUPPORT == _ON)
    _DISP_ROTATE_90,
#endif
#if(_HW_DISPLAY_ROTATION_270_SUPPORT == _ON)
    _DISP_ROTATE_270,
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
    _DISP_ROTATE_HOR_MIRROR,
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
    _DISP_ROTATE_VER_MIRROR,
#endif

    _DISP_ROTATE_AMOUNT,
}EnumOSDDispRotateDegree;

//--------------------------------------------------
// Define Display Latency
//--------------------------------------------------
typedef enum
{
    _LATENCY_L = 0,
    _LATENCY_M,
    _LATENCY_H,
    _LATENCY_AMOUNT = _LATENCY_H,
}EnumOSDDLatency;

//--------------------------------------------------
// Define HotKey Option
//--------------------------------------------------
typedef enum
{
    _HOTKEY_DDCCI = 0,
    _HOTKEY_AMOUNT = _HOTKEY_DDCCI,
}EnumOSDHotKeyDef;

//--------------------------------------------------
// Definitions of Input Port
//--------------------------------------------------
typedef enum
{
    _OSD_INPUT_A0 = 0,
    _OSD_INPUT_D0,
    _OSD_INPUT_D1,
    _OSD_INPUT_D2,
    _OSD_INPUT_D3,
    _OSD_INPUT_D4,
    _OSD_INPUT_D5,
    _OSD_INPUT_D6,
    _OSD_INPUT_D7,
    _OSD_INPUT_D8,
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    _OSD_INPUT_D9,
    _OSD_INPUT_D9_D0,
    _OSD_INPUT_D9_D1,
    _OSD_INPUT_D9_D2,
#endif
    _OSD_INPUT_AUTO,
    _OSD_INPUT_AMOUNT = _OSD_INPUT_AUTO,
}EnumOSDInputPort;

//--------------------------------------------------
// Definitions of Color Temperature
//--------------------------------------------------
typedef enum
{
    _CT_9300,
    _CT_7500,
    _CT_6500,
    _CT_5800,
    _CT_SRGB,
    _CT_USER,
    _CT_COLORTEMP_AMOUNT = _CT_USER,
} EnumOSDColorTempDef;

#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
//--------------------------------------------------
// Definitions of CCT Transfer Matrix
//--------------------------------------------------
typedef enum
{
    _COLORIMETRY_TRANSFER_DEFUALT_CCT,
    _COLORIMETRY_TRANSFER_USER_DEFINE_0,
    _COLORIMETRY_TRANSFER_USER_DEFINE_1,
    _COLORIMETRY_TRANSFER_USER_DEFINE_2,
    _COLORIMETRY_TRANSFER_USER_DEFINE_3,
    _COLORIMETRY_TRANSFER_USER_DEFINE_4,
    _COLORIMETRY_TRANSFER_USER_DEFINE_5,
    _COLORIMETRY_TRANSFER_USER_DEFINE_6,
    _COLORIMETRY_TRANSFER_USER_DEFINE_7,
    _COLORIMETRY_TRANSFER_USER_DEFINE_8,
    _COLORIMETRY_TRANSFER_USER_DEFINE_9,
    _COLORIMETRY_TRANSFER_USER_DEFINE_10,
    _COLORIMETRY_TRANSFER_USER_DEFINE_11,
    _COLORIMETRY_TRANSFER_USER_DEFINE_12,
    _COLORIMETRY_TRANSFER_USER_DEFINE_13,
}EnumColorimetryTransfer;
#endif

//--------------------------------------------------
// Define HL Window Type
//--------------------------------------------------
typedef enum
{
    _HL_WIN_OFF,
    _HL_WIN_FULL,
    _HL_WIN_LEFTSIDE,
    _HL_WIN_TOPSIDE,
    _HL_WIN_CENTER,
    _HL_WIN_MOVE,
    _HL_WIN_AMOUNT = _HL_WIN_MOVE,
}EnumHLWinType;

//--------------------------------------------------
// Definitions of 3D Effect
//--------------------------------------------------
typedef enum
{
    _3D_EFFECT_OFF = _OFF,
    _3D_EFFECT_WEAK,
    _3D_EFFECT_MEDIUM,
    _3D_EFFECT_STRONG,
    _3D_EFFECT_AMOUNT = _3D_EFFECT_STRONG,
} EnumOSDSelect3DEffectDef;

//--------------------------------------------------
// Definitions of PCMType
//--------------------------------------------------
typedef enum
{
    _PCM_OSD_NATIVE,
#if(_OCC_FUNCTION == _ON)
    _PCM_OSD_SRGB,
    _PCM_OSD_ADOBE_RGB,
#endif
#if((_OCC_FUNCTION == _ON) && (_RGB_3D_GAMMA_FUNCTION == _ON))
    _PCM_OSD_SOFT_PROFT_M1,
    _PCM_OSD_SOFT_PROFT_M2,
#endif
    _PCM_OSD_USER,
    _PCM_OSD_AMOUNT = _PCM_OSD_USER,
}EnumPCMTypeIndex;

//--------------------------------------------------
// Definitions of PCMType
//--------------------------------------------------
typedef enum
{
    _UNIFORMITY_OSD_TYPE1 = 0,  // gamma 1.8
    _UNIFORMITY_OSD_TYPE2,      // gamma 2.0
    _UNIFORMITY_OSD_TYPE3,      // gamma 2.2
    _UNIFORMITY_OSD_TYPE4,      // gamma 2.4
    _UNIFORMITY_OSD_TYPE5,      // srgb
    _UNIFORMITY_OSD_TYPE6,      // adobe rgb
    _UNIFORMITY_OSD_OFF,        // OFF
}EnumUniformityTypeSelectIndex;

//--------------------------------------------------
// Definitions of HDR Light Enhance
//--------------------------------------------------
typedef enum
{
    _HDR10_LIGHTENHANCE_OFF,
    _HDR10_LIGHTENHANCE_TYPE_120,
    _HDR10_LIGHTENHANCE_TYPE_140,
    _HDR10_LIGHTENHANCE_TYPE_160,
} EnumHDR10LightEnhanceType;

//--------------------------------------------------
// Definitions of HDR10 Color Enhance
//--------------------------------------------------
typedef enum
{
    _HDR10_COLORENHANCE_OFF,
    _HDR10_COLORENHANCE_TYPE_1,
    _HDR10_COLORENHANCE_TYPE_2,
    _HDR10_COLORENHANCE_TYPE_3,
}EnumHDR10ColorEnhanceType;

//--------------------------------------------------
// Definitions of HDR10 Sharpness Enhance
//--------------------------------------------------
typedef enum
{
    _HDR10_SHARPNESSENHANCE_OFF,
    _HDR10_SHARPNESSENHANCE_ON,
}EnumHDR10SharpnessEnhanceType;

//--------------------------------------------------
// Definitions of HDR10 User ToneMapping Type
//--------------------------------------------------
typedef enum
{
    _HDR10_USER_MAX_MASTERING_LV_TYPE_540, // 540 nits
    _HDR10_USER_MAX_MASTERING_LV_TYPE_1200, // 1200 nits
    _HDR10_USER_MAX_MASTERING_LV_TYPE_4000, // 4000 nits
    _HDR10_USER_MAX_MASTERING_LV_TYPE_10000, // 10000 nits
    _HDR10_USER_MAX_MASTERING_LV_TYPE_NOTM, // Tone Mapping by source based on peak lv
} EnumHDR10UserMasteringLvType;

//--------------------------------------------------
// Definitions of Clone Mode
//--------------------------------------------------
typedef enum
{
    _OSD_CLONE_FIX_OFF = _OFF,
    _OSD_CLONE_FIX_A0,
    _OSD_CLONE_FIX_D0,
    _OSD_CLONE_FIX_D1,
    _OSD_CLONE_FIX_D2,
    _OSD_CLONE_FIX_D3,
    _OSD_CLONE_FIX_D4,
    _OSD_CLONE_FIX_D5,
    _OSD_CLONE_FIX_D6,
}EnumOSDCloneModeFixDef;
//--------------------------------------------------
// Define of Level Type
//--------------------------------------------------
typedef enum
{
    _LEVEL_OFF = 0,
    _LEVEL_L,
    _LEVEL_M,
    _LEVEL_H,
    _LEVEL_AMOUNT = _LEVEL_H,
}EnumLevelType;
//--------------------------------------------------
// Define of EaghtSight Zoom
//--------------------------------------------------
typedef enum
{
    _ES_1p5x = 0,
    _ES_2x,
    _ES_3x,
    _ES_4x,
    _ES_ZOOM_AMOUNT = _ES_4x,
}EnumESZoomType;
typedef enum
{
    _POSITON_LT = 0,
    _POSITON_RT,
    _POSITON_LB,
    _POSITON_RB,
    _POSITON_CENTER,
    _POSITON_USER,
    _POSITON_AMOUNT = _POSITON_CENTER,
}EnumESPositionType;

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
typedef enum
{
    _FW_UPDATE_NONE = 0,
    _FW_UPDATE_ON_GOING,
    _FW_UPDATE_SUCCESS,
    _FW_UPDATE_FAIL_NO_FILE,
    _FW_UPDATE_FAIL_VERSION_FAIL,
}EnumFwUpdateStatusType;
#endif

//--------------------------------------------------
// User Data
//--------------------------------------------------
typedef struct
{
    BYTE b1OsdLogo : 1;
    BYTE b1OsdWakeUpSwitchDdcciPort : 1;
    BYTE b1OsdWakeUpShowSource : 1;
    BYTE b1OsdWakeUpShowDisplayMode : 1;
    BYTE b1OsdWakeUpShowDpOption : 1;
    BYTE b1OsdFactoryModeStatus : 1;
    BYTE b1OsdDoubleSizeStatus : 1;
    BYTE b1FreezeStatus : 1;
    EnumSixColorType b3OsdsixColor : 3;
#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FREEZE_SUPPORT == _ON))
    BYTE b1FreezeDisableOsdStatus : 1;
#endif
    WORD usOsdStatePrevious;
    WORD usOsdState;
    BYTE ucOsdEventMsg;
    BYTE ucOsdKeyMessage;
    BYTE ucOsdKeyControl;
    BYTE ucOsdDoAspectRatio;
    BYTE pucOsdColorFormat[_OSD_INPUT_AMOUNT];

    BYTE ucOsdsixColorHue;
    BYTE ucOsdsixColorSaturation;
    BYTE ucOsdColorTempOsdItem;

#if(_FREESYNC_SUPPORT == _ON)
    BYTE ucOsdFreeSyncInforOsdAddress;
#endif
    BYTE ucOsdItemIndex;

    BYTE b1OsdPixelShift : 1;
    EnumOsdPutStringMode b2StringMode : 2;
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
    BYTE b1OsdFwUpdateNow : 1;
    BYTE ucOsdFwUpdateWaitTime;
#endif
    BYTE ucStringModeLength;
    BYTE ucStringBlankPixel;
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
    BYTE ucNightModeTime;
#endif
}StructOsdInfo;

#if(_PIXEL_SHIFT_SUPPORT == _ON)
typedef struct
{
    BYTE ucTimeForINTCount;
    BYTE ucTimeForMinute;
    BYTE b4OrbitingTimer : 4;
}StructTimer;

typedef struct
{
    BYTE b1Capability : 1;
}StructPixelOrbitingStatus;
#endif

typedef enum
{
    _ = U0020,
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
    _PERCENT0_ = U0025_0,           // %
    _PERCENT1_ = U0025_1,           // %
#endif
    _UPDOT_ = U0027,                // '
    _LEFT_BRACE_ = U0028,           // (
    _RIGHT_BRACE_ = U0029,          // )
    _COMMA_ = U002C,                // ,
    _SLINE_ = U002D,                // -
    _DOT_ = U002E,                  // .
    _AND_ = U002F,                  // /


    _0_ = U0030, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_,

    _COLON_ = U003A,                // :
    _SEPERATE_ = U003B,             // ;
    _QUERY_ = U003F,                // ?
    _AT_0_ = U0040_0,               // @
    _AT_1_ = U0040_1,               // @

    _A_ = U0041, _B_, _C_, _D_, _E_, _F_, _G_, _H_, _I_, _J_, _K_, _L_,
    _M_, _N_, _O_, _P_, _Q_, _R_, _S_, _T_, _U_, _V_,
    _W_0, _W_1,
    _X_, _Y_, _Z_,

    _a_ = U0061, _b_, _c_, _d_, _e_, _f_, _g_, _h_, _i_, _j_, _k_, _l_,
    _m_, _n_, _o_, _p_, _q_, _r_, _s_, _t_, _u_, _v_,
    _w_0, _w_1,
    _x_, _y_, _z_,
}EnumOSDFontDef;

typedef enum
{
    _CP_EMPTY = 0,
    _CP_BG = 0,
    _CP_BLACK = 0,
    _CP_WHITE,
    _CP_BLUE_120,
    _CP_GREEN_119,
    _CP_BLUE,
    _CP_YELLOW,
    _CP_GRAY,
    _CP_ORANGE,
    _CP_LIGHTBLUE,
    _CP_SELECTBOTTOM,
    _CP_PINK,
    _CP_RED,
    _CP_GREEN_1,
    _CP_ORANGE_DARK,
    _CP_ORANGE_H,
    _CP_BLUE_200,

}EnumOSDColorPaletteDef;

typedef enum
{
    _LOGO_CP_BG = 0,
    _LOGO_CP_BLACK = 0,
    _LOGO_CP_WHITE,
    _LOGO_CP_RED,
    _LOGO_CP_GREEN,
    _LOGO_CP_BLUE,
    _LOGO_CP_YELLOW,
    _LOGO_CP_GRAY,
    _LOGO_CP_DARKBLUE,
    _LOGO_CP_LIGHTBLUE,
    _LOGO_CP_SELECTBOTTOM,
    _LOGO_CP_PINK,
    _LOGO_CP_RED_1,
    _LOGO_CP_GREEN_1,
    _LOGO_CP_ORANGE_L,
    _LOGO_CP_ORANGE_H,
    _LOGO_CP_GRAY_1,
}EnumOSDColorPaletteLogo;

typedef enum
{
    _OSD_MENU_NONE = 0,
//=====>> 1st Osd Item only Start
    _OSD_MENU_PICTURE,
    _OSD_MENU_DISPLAY,
    _OSD_MENU_COLOR,
    _OSD_MENU_ADVANCE,
    _OSD_MENU_AUDIO,
    _OSD_MENU_OTHER,
    _OSD_MENU_MUTIP,
    _OSD_MENU_HDR,
    _OSD_MENU_QUICKLINK,
    _OSD_MENU_INPUT,
    _OSD_MENU_FACTORY,
#if(_DM_FUNCTION == _ON)
    _OSD_MENU_DVISION,
#endif
//=====>> 1st Osd Item only End

    _OSD_PICTURE_BACKLIGHT,
    _OSD_PICTURE_BRIGHTNESS,
    _OSD_PICTURE_CONTRAST,
    _OSD_PICTURE_SHARNESS,

    _OSD_DISPLAY_AUTO,
    _OSD_AUTO_COLOR,
    _OSD_DISPLAY_HPOS,
    _OSD_DISPLAY_VPOS,
    _OSD_DISPLAY_CLOCK,
    _OSD_DISPLAY_PHASE,
    _OSD_DISPLAY_DISP_ROTATE,
    _OSD_DISPLAY_LATENCY,
    _OSD_DISPLAY_FREEZE,

    _OSD_MUTIP_MODE,
    _OSD_MUTIP_SELECTREGION,
    _OSD_MUTIP_LR_RATIO,
    _OSD_MUTIP_PIP_POSITION,
    _OSD_MUTIP_PIP_POSITION_USER,
    _OSD_MUTIP_PIP_TRANSPARENCY,
    _OSD_MUTIP_PIP_SIZE,
    _OSD_MUTIP_INPUT_SWAP,
    _OSD_MUTIP_PXP_MST,

    _OSD_COLOR_PANEL_UNIFORMITY,
    _OSD_COLOR_GAMMA,
    _OSD_COLOR_TEMPERATURE,
    _OSD_COLOR_TEMP_USER,
    _OSD_COLOR_EFFECT,
    _OSD_COLOR_EFFECT_USER,
    _OSD_COLOR_CHAMELEON_USER,
    _OSD_COLOR_DEMO,
    _OSD_COLOR_DEMO_SIDE,
    _OSD_COLOR_FORMAT,
    _OSD_COLOR_PCM,
    _OSD_COLOR_HUE,
    _OSD_COLOR_SATURATION,
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
    _OSD_COLOR_EYE_PROTECT,
#endif
    _OSD_ADVANCE_ASPECT,
    _OSD_ADVANCE_OVERSCAN,
    _OSD_ADVANCE_OVERDRIVE,
    _OSD_ADVANCE_DDCCI,
    _OSD_ADVANCE_ULTRAVIVID,
    _OSD_ADVANCE_DCR,
    _OSD_ADVANCE_DPOPTION,
    _OSD_ADVANCE_DPMST,
    _OSD_ADVANCE_DP_RESOLUTION,
    _OSD_ADVANCE_CLONE,
    _OSD_ADVANCE_HDMI_VERSIONS,
    _OSD_ADVANCE_FREESYNC,
    _OSD_ADVANCE_TYPEC_MODE,
    _OSD_ADVANCE_LOCALDIMMING,
    _OSD_ADVANCE_LOCALDIMMING_USER,
    _OSD_ADVANCE_PIXELSHIFT,
    _OSD_ADVANCE_SDR_TO_HDR,
    _OSD_ADVANCE_DUAL_DP_EDID,
    _OSD_ADVANCE_GLOBAL_DIMMING,
    _OSD_ADVANCE_LOCAL_CONTRAST,
    _OSD_ADVANCE_LOCAL_CONTRAST_USER,
    _OSD_ADVANCE_DSC,
    _OSD_ADVANCE_HUB_SWITCH,
    _OSD_ADVANCE_EAGLE_SIGHT,
    _OSD_ADVANCE_MBR,
    _OSD_ADVANCE_DP_AUXLESS_ALPM,
    _OSD_ADVANCE_DP_ADAPTIVESYNC,
    _OSD_ADVANCE_PANEL_REPLAY,
    _OSD_ADVANCE_SDR_PLUS,
    _OSD_ADVANCE_SDR_PLUS_ADJ,
    _OSD_ADVANCE_SDR_PLUS_SHARP,
    _OSD_ADVANCE_SDR_PLUS_DARK,
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
    _OSD_ADVANCE_NIGHT_SNIPER,
    _OSD_ADVANCE_NIGHT_SNIPER_ADJUST,
    _OSD_ADVANCE_NIGHT_SNIPER_SATURATION,
    _OSD_ADVANCE_NIGHT_SNIPER_LIGHTNESS,
#endif
    _OSD_ADVANCE_ANTI_ALIASING,
    _OSD_ADVANCE_ENERGY_SAVE,

    _OSD_AUDIO_VOLUME,
    _OSD_AUDIO_MUTE,
    _OSD_AUDIO_STAND_ALONG,
    _OSD_AUDIO_AUDIO_SOURCE,
    _OSD_AUDIO_SOUND_MODE,
    _OSD_AUDIO_AUDIO_SELF_TEST,

    _OSD_OTHER_RESET,
    _OSD_OTHER_MENU_TIME,
    _OSD_OTHER_OSD_HPOS,
    _OSD_OTHER_OSD_VPOS,
    _OSD_OTHER_LANGUAGE,
    _OSD_OTHER_TRNASPARENCY,
    _OSD_OTHER_ROTATE,
    _OSD_OTHER_BORDER_WIDTH,
    _OSD_OTHER_BORDER_COLOR,

    _OSD_HDR_MODE,
    _OSD_HDR_DARK_ENHANCE,
    _OSD_HDR_SHARP_ENHANCE,
    _OSD_HDR_CONTRAST,
    _OSD_HDR_COLOR_ENHANCE,
    _OSD_HDR_LIGHT_ENHANCE,
    _OSD_HDR_HLG_OOTF,

    _OSD_SOURCE_1P,
    _OSD_SOURCE_2P,
    _OSD_SOURCE_3P,
    _OSD_SOURCE_4P,

#if(_DM_FUNCTION == _ON)
    _OSD_DVISION,
    _OSD_DVISION_PICTURE,
    _OSD_DVISION_BACKLIGHT,
    _OSD_DVISION_BRIGHTNESS,
    _OSD_DVISION_CONTRAST,
    _OSD_DVISION_SATURATION,
    _OSD_DVISION_RESET,
    _OSD_DVISION_NOTIFICATION,
#endif

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
    _OSD_TTS_FUNCTION,
    _OSD_TTS_TEXT_VOLUME,
    _OSD_TTS_AUDIO_VOLUME,
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
    _OSD_ADVANCE_FW_UPDATE,
#endif

    _OSD_OTHER_CROSSHAIR,

#if(_AUDIO_ARC_SUPPORT == _ON)
    _OSD_MENU_AUDIO_ARC_EARC,
    _OSD_AUDIO_ARC_OUTPUT,
    _OSD_AUDIO_ARC_INPUTPORT,
    _OSD_AUDIO_ARC_MODE,
    _OSD_AUDIO_ARC_MUTE,
    _OSD_AUDIO_ARC_CHANEL,
#endif
//==>STEP 1//add New Item Here!!!!!
    _OSD_EXIT_HOTKEY,

}EnumOsdItem;
typedef enum
{
    _MENU_NONE,
    _MENU_MAIN,

    _MENU_PICTURE_ITEM,
    _MENU_DISPLAY_ITEM,
    _MENU_COLOR_ITEM,
    _MENU_ADVANCE_ITEM,
    _MENU_AUDIO_ITEM,
    _MENU_OTHER_ITEM,
    _MENU_MUTIP_ITEM,
    _MENU_HDR_ITEM,
#if(_DM_FUNCTION == _ON)
    _MENU_DVISION_ITEM,
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
    _MENU_AUDIO_ARC_EARC_ITEM,
#endif
    _MENU_QUICKLINK_ITEM,
    _MENU_INPUT_ITEM,

    _MENU_DISPLAYMODE,
    _MENU_SELECTREGIOM,
    _MENU_DISPLAYFUN_DISP_ROTATE_ADJUST,
    _MENU_DISPLAYFUN_LATENCY_ADJUST,
    _MENU_DISPLAYFUN_FREEZE_ADJUST,

    _MENU_DISPLAYFUN_LR_RATIO_ADJUST,
    _MENU_DISPLAYFUN_PIP_POSITION_ADJUST,
    _MENU_DISPLAYFUN_PIP_POSITION_USER,
    _MENU_DISPLAYFUN_PIP_POSITION_H_ADJUST,
    _MENU_DISPLAYFUN_PIP_POSITION_V_ADJUST,
    _MENU_DISPLAYFUN_PIP_TRANSPARENCY_ADJUST,
    _MENU_DISPLAYFUN_PIP_SIZE_ADJUST,

    _MENU_PICTURE_BACKLIGHT_ADJUST,
    _MENU_PICTURE_BRIGHTNESS_ADJUST,
    _MENU_PICTURE_CONTRAST_ADJUST,
    _MENU_PICTURE_SHARPNESS_ADJUST,

    _MENU_ANALOG_HPOS_ADJUST,
    _MENU_ANALOG_VPOS_ADJUST,
    _MENU_ANALOG_CLOCK_ADJUST,
    _MENU_ANALOG_PHASE_ADJUST,

    _MENU_COLOR_PANEL_UNIFORMITY_ADJUST,
    _MENU_COLOR_GAMMA_ADJUST,
    _MENU_COLOR_TEMPERATURE_ADJUST,
    _MENU_COLOR_EFFECT_ADJUST,
    _MENU_COLOR_DEMO_ADJUST,
    _MENU_COLOR_DEMO_SIDE_ADJUST,
    _MENU_COLOR_FORMAT_ADJUST,
    _MENU_COLOR_PCM_ADJUST,
    _MENU_COLOR_HUE_ADJUST,
    _MENU_COLOR_SATURATION_ADJUST,
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
    _MENU_COLOR_EYE_PROTECT_ADJUST,
#endif

    _MENU_ADVANCE_ASPECT_ADJUST,
    _MENU_ADVANCE_OVER_SCAN_ADJUST,
    _MENU_ADVANCE_DDCCI_ADJUST,
    _MENU_ADVANCE_ULTRA_VIVID_ADJUST,
    _MENU_ADVANCE_DCR_ADJUST,
    _MENU_ADVANCE_DP_OPTION_D0,
    _MENU_ADVANCE_DP_OPTION_D1,
    _MENU_ADVANCE_DP_OPTION_D2,
    _MENU_ADVANCE_DP_OPTION_D6,
    _MENU_ADVANCE_DP_MST_ADJUST,
    _MENU_ADVANCE_CLONE_ADJUST,
    _MENU_ADVANCE_FREESYNC_ADJUST,
    _MENU_ADVANCE_DUAL_DP_EDID_ADJUST,
    _MENU_ADVANCE_EDID_ADJUST,
    _MENU_ADVANCE_EDID_DX_ADJUST,
    _MENU_ADVANCE_HDMI_VERSION_ADJUST,
    _MENU_ADVANCE_DX_HDMI_VERSION_ADJUST,
    _MENU_ADVANCE_DSC_ADJUST,
    _MENU_ADVANCE_TYPEC_MODE_D0,
    _MENU_ADVANCE_TYPEC_MODE_D1,
    _MENU_ADVANCE_TYPEC_MODE_D2,
    _MENU_ADVANCE_TYPEC_MODE_D6,
    _MENU_ADVANCE_PIXEL_SHIFT_ADJUST,
    _MENU_ADVANCE_SDR_TO_HDR_ADJUST,
    _MENU_ADVANCE_GLOBAL_DIMMING_ADJUST,
    _MENU_ADVANCE_LOCAL_CONTRAST_ADJUST,
    _MENU_ADVANCE_LOCAL_CONTRAST_USER,
    _MENU_ADVANCE_LOCAL_CONTRAST_BLENDING,
    _MENU_ADVANCE_LOCAL_CONTRAST_DIFFGAIN,
    _MENU_ADVANCE_HUB_SWITCH_ADJUST,
    _MENU_ADVANCE_EAGLE_SIGHT_ADJUST,
    _MENU_ADVANCE_MBR_ADJUST,
    _MENU_ADVANCE_DP_AUXLESS_ALPM_ADJUST,
    _MENU_ADVANCE_DP_ADAPTIVESYNC,
    _MENU_ADVANCE_PANEL_REPLAYM_ADJUST,
    _MENU_ADVANCE_SDR_PLUS,
    _MENU_ADVANCE_SDR_PLUS_SELECT,
    _MENU_ADVANCE_SDR_PLUS_SHARP,
    _MENU_ADVANCE_SDR_PLUS_DARK,
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
    _MENU_ADVANCE_NIGHT_SNIPER,
    _MENU_ADVANCE_NIGHT_SNIPER_ADJUST,
    _MENU_ADVANCE_NIGHT_SNIPER_SATURATION,
    _MENU_ADVANCE_NIGHT_SNIPER_LIGHTNESS,
#endif
    _MENU_ADVANCE_ANTI_ALIASING,
    _MENU_ADVANCE_ENERGY_SAVER,
    _MENU_AUDIO_VOLUME_ADJUST,
    _MENU_AUDIO_MUTE_ON_OFF,
    _MENU_AUDIO_STAND_ALONG_SELECT,
    _MENU_AUDIO_AUDIO_SOURCE_SELECT,
    _MENU_AUDIO_SOUND_MODE_SELECT,
    _MENU_AUDIO_AUDIO_SELF_TEST_SELECT,

    _MENU_OTHER_MENU_TIME_ADJUST,
    _MENU_OTHER_OSD_HPOS_ADJUST,
    _MENU_OTHER_OSD_VPOS_ADJUST,
    _MENU_OTHER_LANGUAGE_ADJUST,
    _MENU_OTHER_TRNASPARENCY_ADJUST,
    _MENU_OTHER_ROTATE_ADJUST,
    _MENU_OTHER_BORDER_WIDTH_ADJUST,
    _MENU_OTHER_BORDER_COLOR_ADJUST,
    _MENU_OTHER_CROSSHAIR_ADJUST,

    _MENU_COLOR_TEMP_USER_R,
    _MENU_COLOR_TEMP_USER_G,
    _MENU_COLOR_TEMP_USER_B,

    _MENU_COLOR_TEMP_USER_ADJUST_R,
    _MENU_COLOR_TEMP_USER_ADJUST_G,
    _MENU_COLOR_TEMP_USER_ADJUST_B,

    _MENU_COLOR_EFF_USER_R_HUE,
    _MENU_COLOR_EFF_USER_R_SAT,
    _MENU_COLOR_EFF_USER_Y_HUE,
    _MENU_COLOR_EFF_USER_Y_SAT,
    _MENU_COLOR_EFF_USER_G_HUE,
    _MENU_COLOR_EFF_USER_G_SAT,
    _MENU_COLOR_EFF_USER_C_HUE,
    _MENU_COLOR_EFF_USER_C_SAT,
    _MENU_COLOR_EFF_USER_B_HUE,
    _MENU_COLOR_EFF_USER_B_SAT,
    _MENU_COLOR_EFF_USER_M_HUE,
    _MENU_COLOR_EFF_USER_M_SAT,

    _MENU_COLOR_EFF_USER_R_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_R_SAT_ADJUST,
    _MENU_COLOR_EFF_USER_Y_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_Y_SAT_ADJUST,
    _MENU_COLOR_EFF_USER_G_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_G_SAT_ADJUST,
    _MENU_COLOR_EFF_USER_C_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_C_SAT_ADJUST,
    _MENU_COLOR_EFF_USER_B_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_B_SAT_ADJUST,
    _MENU_COLOR_EFF_USER_M_HUE_ADJUST,
    _MENU_COLOR_EFF_USER_M_SAT_ADJUST,

#if(_ICM_CHAMELEON_FUNCTION == _ON)
    _MENU_COLOR_CHAMELEON_HUE,
    _MENU_COLOR_CHAMELEON_SAT,
    _MENU_COLOR_CHAMELEON_LIGHTNESS,
    _MENU_COLOR_CHAMELEON_HUE_ADJUST,
    _MENU_COLOR_CHAMELEON_SAT_ADJUST,
    _MENU_COLOR_CHAMELEON_LIGHTNESS_ADJUST,
#endif
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
    _MENU_COLOR_EYE_PROTECT_MODE_ADJUST,
    _MENU_COLOR_EYE_PROTECT_LEVEL_ADJUST,
    _MENU_COLOR_EYE_PROTECT_TIME_ADJUST,
    _MENU_COLOR_EYE_PROTECT_AMBIENTSENSE_ADJUST,
#endif
    _MENU_ADVANCE_OD_GAIN_ADJUST,

    _MENU_ADVANCE_DP_D0_VERSION_ADJUST,
    _MENU_ADVANCE_DP_D1_VERSION_ADJUST,
    _MENU_ADVANCE_DP_D2_VERSION_ADJUST,
    _MENU_ADVANCE_DP_D6_VERSION_ADJUST,

    _MENU_ADVANCE_D0_TYPEC_MODE_ADJUST,
    _MENU_ADVANCE_D1_TYPEC_MODE_ADJUST,
    _MENU_ADVANCE_D2_TYPEC_MODE_ADJUST,
    _MENU_ADVANCE_D6_TYPEC_MODE_ADJUST,
    _MENU_ADVANCE_HDR_LD_ONOFF_ADJUST,
    _MENU_ADVANCE_HDR_LD_SMOOTH_ADJ_ADJUST,

    _MENU_ADVANCE_HDR_MODE_ADJUST,
    _MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF_ADJUST,
    _MENU_ADVANCE_HDR_SHARPNESS_ONOFF_ADJUST,
    _MENU_ADVANCE_HDR_CONTRAST_ADJUST,
    _MENU_ADVANCE_HDR_COLOR_ENHANCE_ADJUST,
    _MENU_ADVANCE_HDR_LIGHT_ENHANCE_ADJUST,
    _MENU_ADVANCE_HDR_HLG_OOTF_ADJUST,

    _MENU_ADVANCE_EAGLE_SIGHT_FUNCTION_ADJUST,
    _MENU_ADVANCE_EAGLE_SIGHT_REGION_ADJUST,
    _MENU_ADVANCE_EAGLE_SIGHT_TRANSPARENT_ADJUST,
    _MENU_ADVANCE_EAGLE_SIGHT_ZOOM_ADJUST,
    _MENU_ADVANCE_EAGLE_SIGHT_CAP_POSITION_ADJUST,
    _MENU_ADVANCE_EAGLE_SIGHT_DISP_POSITION_ADJUST,
    _MENU_ADVANCE_EAGLE_SIGHT_BORDER_ADJUST,
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
    _MENU_ADVANCE_EAGLE_SIGHT_CIRCLEWIN_ADJUST,
#endif
    _MENU_ADVANCE_MBR_MODE_ADJUST,
    _MENU_ADVANCE_MBR_DUTY_ADJUST,
    _MENU_ADVANCE_MBR_POSITION_ADJUST,
    _MENU_ADVANCE_ANTI_ALIASING_MODE_ADJ,
    _MENU_ADVANCE_ANTI_ALIASING_LEVEL_ADJ,
    _MENU_INPUT_SOURCE_1P_ADJ,
    _MENU_INPUT_SOURCE_2P_ADJ,
    _MENU_INPUT_SOURCE_3P_ADJ,
    _MENU_INPUT_SOURCE_4P_ADJ,
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    _MENU_PXP_MST_ADJUST,
#endif
#if(_DM_FUNCTION == _ON)
    _MENU_OSD_DVISION,
    _MENU_OSD_DVISION_PICTURE,
    _MENU_OSD_DVISION_BACKLIGHT,
    _MENU_OSD_DVISION_BRIGHTNESS,
    _MENU_OSD_DVISION_CONTRAST,
    _MENU_OSD_DVISION_SATURATION,
    _MENU_OSD_DVISION_NOTIFICATION,
#endif

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
    _MENU_TTS_FUNCTION,
    _MENU_TTS_TEXT_VOLUME,
    _MENU_TTS_AUDIO_VOLUME,
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
    _MENU_ADVANCE_FW_UPDATE,
    _MENU_FW_UPDATE_WAITING,
    _MENU_FW_UPDATE_CHECK_MSG,
    _MENU_FW_UPDATE_PROCESS_BAR,
    // _MENU_FW_UPDATE_REBOOT,
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
    _MENU_AUDIO_ARC_OUTPUT,
    _MENU_AUDIO_ARC_INPUTPORT,
    _MENU_AUDIO_ARC_MODE,
    _MENU_AUDIO_ARC_MUTE,
    _MENU_AUDIO_ARC_CHANEL,
#endif

// ==>STEP 4 //add New Item Here!!!!!

    _MENU_EXIT_HOTKEY_ADJ,

    _MENU_HOTKEY_SOURCE,
    _MENU_HOTKEY_INFORMATION,
    _MENU_PANEL_UNIFORMITY_MSG_ADJUST,
    _MENU_MESSAGE_DISPLAY,
    _MENU_HOTKEY_NONE,
    _MENU_END,
}EnumOsdMenuStatus;

typedef enum
{
    _ICON_NONE = 0,
    // main
    _ICON_PICTURE,
    _ICON_DISPLAYFUNCTION,
    _ICON_COLOR,
    _ICON_ADVANCE,
    _ICON_AUDIO,
    _ICON_OTHER,
    _ICON_MUTIP,
    _ICON_HDR,
    _ICON_QUICKLINK,
    _ICON_INPUT,
    _ICON_FACTORY,
#if(_DM_FUNCTION == _ON)
    _ICON_DVISION,
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
    _ICON_EARC,
#endif
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
    _ICON_FW_UPDATE,
#endif
    // picture
    _ICON_BACKLIGHT,
    _ICON_BRIGHTNESS,
    _ICON_CONTRAST,
    _ICON_SHARPNESS,

    // analog
    _ICON_AUTO_ADJUST,
    _ICON_ANALOG,
    _ICON_HPOS,
    _ICON_VPOS,
    _ICON_CLOCK,
    _ICON_PHASE,
    _ICON_DISP_ROTATE,
    _ICON_LANTENCY,
    _ICON_FREEZE,

    _ICON_DISPLAYMODE,
    _ICON_SELECTREGION,
    _ICON_DISP_LR_RATIO,
    _ICON_PIP_POSITION,
    // _ICON_PIP_POSITION_USER,
    _ICON_PIP_TRANSPARENCY,
    _ICON_PIP_SIZE,
    _ICON_INPUT_SWAP,

    // color
    _ICON_PANEL_UNIFORMITY,
    _ICON_GAMMA,
    _ICON_COLOR_TEMPERATURE,
    _ICON_COLOR_TEMPERATURE_USER,
    _ICON_COLOR_EFFECT,
    _ICON_COLOR_EFFECT_USER,
    _ICON_COLOR_DEMO,
    _ICON_COLOR_FORMAT,
    _ICON_PCM,
    _ICON_HUE,
    _ICON_SATURATION,

    // advance
    _ICON_ASPECT,
    _ICON_OVER_SCAN,
    _ICON_OVER_DRIVE,
    _ICON_DDCCI,
    _ICON_ULTRAVIVID,
    _ICON_DCR,
    _ICON_DP_OPTION,
    _ICON_DP_MST,
    _ICON_RESOLUTION,
    _ICON_CLONE,
    _ICON_DUAL_DP_EDID,
    _ICON_FREESYNC,
    _ICON_TYPEC_MODE,
    _ICON_LOCAL_DIMMING,
    _ICON_PIXEL_SHIFT,
    _ICON_SDR_TO_HDR,
    _ICON_SINGLE_DP_EDID,
    _ICON_HDMI_VERSIONS,

    // audio
    _ICON_VOLUME,
    _ICON_MUTE,
    _ICON_STAND_ALONG,
    _ICON_AUDIO_SOURCE,
    _ICON_SOUND_MODE,
    _ICON_AUDIO_SELF_TEST,

    // other
    _ICON_RESET,
    _ICON_MENU_TIME,
    _ICON_OSD_HPOS,
    _ICON_OSD_VPOS,
    _ICON_LANGUAGE,
    _ICON_TRNASPARENCY,
    _ICON_ROTATE,
    _ICON_BORDER_WIDTH,
    _ICON_BORDER_COLOR,

    _ICON_HDR_MODE,
    _ICON_DARK_ENHANCE,
    _ICON_HDR_SHARPNESS,
    _ICON_COLOR_ENHANCE,
    _ICON_LIGHT_ENHANCE,
    // input
    _ICON_INPUT_AUTO,

    // display mode
    _ICON_1P,
    _ICON_2P_LR,
    _ICON_2P_TB,
    _ICON_2P_PIP,
    _ICON_4P,
    _ICON_INFORMATION,

    // display function
    _ICON_PIP_USER_POSITION_H,
    _ICON_PIP_USER_POSITION_V,

    // select region
    _ICON_2P_LR_L,
    _ICON_2P_LR_R,
    _ICON_2P_LR_FULL,
    _ICON_2P_TB_T,
    _ICON_2P_TB_B,
    _ICON_2P_TB_FULL,
    _ICON_2P_PIP_MAIN,
    _ICON_2P_PIP_SUB,
    _ICON_2P_PIP_FULL,
    _ICON_4P_LT_INSIDE,
    _ICON_4P_LT_OUTSIDE,
    _ICON_4P_LB_INSIDE,
    _ICON_4P_LB_OUTSIDE,
    _ICON_4P_RT_INSIDE,
    _ICON_4P_RT_OUTSIDE,
    _ICON_4P_RB_INSIDE,
    _ICON_4P_RB_OUTSIDE,
    _ICON_4P_FULL,

    // option icon
    _ICON_ON,
    _ICON_OFF,
    _ICON_AUDIO_ANALOG,
    _ICON_AUDIO_DIGITAL_REGION_1,
    _ICON_AUDIO_DIGITAL_REGION_2,
    _ICON_AUDIO_DIGITAL_REGION_3,
    _ICON_AUDIO_DIGITAL_REGION_4,
    _ICON_AS_RATIO_FULL,
    _ICON_AS_RATIO_16_9,
    _ICON_AS_RATIO_4_3,
    _ICON_AS_RATIO_5_4,
    _ICON_AS_RATIO_ORIGINAL,

    _ICON_ULTRA_VIVID_H,
    _ICON_ULTRA_VIVID_M,
    _ICON_ULTRA_VIVID_L,

    _ICON_TEMP_9300,
    _ICON_TEMP_7500,
    _ICON_TEMP_6500,
    _ICON_TEMP_5800,
    _ICON_TEMP_SRGB,
    _ICON_TEMP_USER,

    _ICON_COLOR_EFF_STD,
    _ICON_COLOR_EFF_GAME,
    _ICON_COLOR_EFF_MOVIE,
    _ICON_COLOR_EFF_PHOTO,
    _ICON_COLOR_EFF_VIVID,
    _ICON_COLOR_EFF_USER,
    _ICON_COLOR_DEMO_TYPE1,
    _ICON_COLOR_DEMO_TYPE2,
    _ICON_COLOR_DEMO_TYPE3,
    _ICON_COLOR_DEMO_TYPE4,
    _ICON_COLOR_DEMO_TYPE5,

    _ICON_COLOR_FORMAT_RGB,
    _ICON_COLOR_FORMAT_YUV,

    _ICON_TEMP_USER_R,
    _ICON_TEMP_USER_G,
    _ICON_TEMP_USER_B,

    _ICON_COLOR_PCM_SRGB,
    _ICON_COLOR_PCM_ADOBE_RGB,
    _ICON_COLOR_PCM_USER,
    _ICON_COLOR_PCM_NACTIVE,
    _ICON_COLOR_PCM_SOFT_PROFT,

    _ICON_COLOR_EFF_USER_Y,
    _ICON_COLOR_EFF_USER_C,
    _ICON_COLOR_EFF_USER_M,
    _ICON_COLOR_EFF_USER_HUE,
    _ICON_COLOR_EFF_USER_SAT,

    _ICON_NO_SUPPORT,
    _ICON_NO_SUPPORT_TEXT_0,
    _ICON_NO_SUPPORT_TEXT_1,

    _ICON_NO_CABLE,
    _ICON_NO_CABLE_TEXT_0,
    _ICON_NO_CABLE_TEXT_1,

    _ICON_NO_SIGNAL,
    _ICON_NO_SIGNAL_TEXT_0,
    _ICON_NO_SIGNAL_TEXT_1,

    _ICON_POWER_SAVING,
    _ICON_POWER_SAVING_TEXT_0,
    _ICON_POWER_SAVING_TEXT_1,
    _ICON_POWER_SAVING_TEXT_2,

    _ICON_AUTO_ADJUST_TEXT_0,
    _ICON_AUTO_ADJUST_TEXT_1,
    _ICON_AUTO_ADJUST_TEXT_2,

    _ICON_AUTO_COLOR_TEXT_0,
    _ICON_AUTO_COLOR_TEXT_1,
    _ICON_AUTO_COLOR_TEXT_2,

    _ICON_MODE1,
    _ICON_MODE2,

    _ICON_0_DEGREE,
    _ICON_90_DEGREE,
    _ICON_180_DEGREE,
    _ICON_270_DEGREE,
    _ICON_HOR_MIRROR,
    _ICON_VER_MIRROR,


    _ICON_DP_1080P,
    _ICON_DP_2560_1440,
    _ICON_DP_4K2K_30HZ,
    _ICON_DP_4K2K_60HZ,

    _ICON_TRUN_OFF_PANEL_UNI_TEXT0,
    _ICON_TRUN_OFF_PANEL_UNI_TEXT1,

    _ICON_YES,
    _ICON_NO,

    _ICON_ONOFF,
    _ICON_OD_GAIN,

    _ICON_D0,
    _ICON_D1,
    _ICON_D6,

    _ICON_1_DOT_1,
    _ICON_1_DOT_2,
    _ICON_1_DOT_3,
    _ICON_1_DOT_4,

    _ICON_1_DOT_8,
    _ICON_2_DOT_0,
    _ICON_2_DOT_1,
    _ICON_2_DOT_2,
    _ICON_2_DOT_4,


    _ICON_COLOR_R,
    _ICON_COLOR_G,
    _ICON_COLOR_B,
    _ICON_COLOR_W,

    _ICON_PIP_POSITION_LT,
    _ICON_PIP_POSITION_RT,
    _ICON_PIP_POSITION_LB,
    _ICON_PIP_POSITION_RB,
    _ICON_PIP_POSITION_MIDDLE,
    _ICON_PIP_POSITION_USER,

    _ICON_FREEZE_DISABLE_TEXT_0,
    _ICON_FREEZE_DISABLE_TEXT_1,
    _ICON_FREEZE_DISABLE_TEXT_2,
    _ICON_DP_5K3K_60HZ,
    _ICON_DP_4K2K_144HZ,

    _ICON_U3_ON,
    _ICON_U3_OFF,

    _ICON_HDR10_MODE_FORCE_2084,

    _ICON_LD_SMOOTHADJ,


    _ICON_MST_WARNING_MSG_0,
    _ICON_MST_WARNING_MSG_1,
    _ICON_MST_WARNING_MSG_2,

    _ICON_ENGLISH,
    _ICON_CHINESE_T,

    _ICON_INFORMATION_HINT,

    _OPTION_ICON_END,
}EnumIconIndex;


typedef enum
{
    // aligh Port order
    _ICON_INPUT_NO_PORT = _OPTION_ICON_END,
    _ICON_INPUT_VGA,
    _ICON_INPUT_DVI,
    _ICON_INPUT_HDMI,
    _ICON_INPUT_DP,
    _ICON_INPUT_MHL,
    _ICON_INPUT_HDMI20,
    _ICON_INPUT_DUAL_DVI,
    _ICON_INPUT_END,

}EnumIconInputSource;
//#define _PORT_NONE                              0x00
//#define _PORT_VGA                               0x01
//#define _PORT_DVI                               0x02
//#define _PORT_HDMI                              0x03
//#define _PORT_DP                                0x04
//#define _PORT_MHL                               0x05
//#define _PORT_HDMI20                            0x06
//#define _PORT_DUAL_DVI                          0x07

typedef enum
{
    _ICON_A0_PORT = _ICON_INPUT_END,
    _ICON_D0_PORT,
    _ICON_D1_PORT,
    _ICON_D2_PORT,
    _ICON_D3_PORT,
    _ICON_D4_PORT,
    _ICON_D5_PORT,
    _ICON_D6_PORT,
    _ICON_D7_PORT,
    _ICON_D8_PORT,

    _ICON_PORT_END,
}EnumIconPort;


typedef enum
{
    _FONT1_GLOBAL,
    _REALTEK_LOGO_FONT_CMD,
    _REALTEK_4BIT_LOGO,
#if(_DM_FUNCTION == _ON)
    _FONT_DVISION,
    _FONT_DVISION_2P,
#endif
    _FONT1_CROSSHAIR,
}EnumFontSel;


typedef enum
{
    _PALETTE_RTD_LOGO,
    _PALETTE_MAIN_MENU,
}EnumPaletteindex;

typedef enum
{
    _ENGLISH = 0,
    _CHINESE_T,
    _FRENCH,
    _GERMAN,
    _SPANISH,
    _CHINESE_S,
    _JAPAN,

    _LANGUAGE_AMOUNT
}EnumOSDLanguageDef;

typedef enum
{
    _OSDEVENT_NONE_MSG = 0,
    _OSDEVENT_SHOW_NOSIGNAL_MSG,
    _OSDEVENT_SHOW_NOCABLE_MSG,
    _OSDEVENT_SHOW_NOSUPPORT_MSG,
    _OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG,
    _OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG,
    _OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG,
    _OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG,
    _OSDEVENT_WAKE_UP_SHOW_QUICKLINK_MENU_MSG,
    _OSDEVENT_DO_AUTO_CONFIG_MSG,
    _OSDEVENT_ACTIVE_DO_ONE_TIME_MSG,
    _OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_ADCDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_COLORPROC_MSG,
    _OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_INPUTSOURCEDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG,
    _OSDEVENT_SHOW_MP_NOSIGNAL_NOCABLE_MSG,
#if(_PIXEL_SHIFT_SUPPORT == _ON)
    _OSDEVENT_PIXEL_ORBITING_ACTION_MSG,
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
    _OSDEVENT_SAVE_AUDIO_ARC_EARC_DATA_MSG,
#endif
}EnumOSDEvenMassage;

typedef enum
{
    _OSD_DISP_NOSIGNAL_MSG,
    _OSD_DISP_NOCABLE_MSG,
    _OSD_DISP_NOSUPPORT_MSG,
    _OSD_DISP_FAIL_SAFE_MODE_MSG,
    _OSD_DISP_AUTO_CONFIG_MSG,
    _OSD_DISP_INPUT_SIGNAL_MSG,
    _OSD_DISP_AUTO_COLOR_MSG,
    _OSD_DISP_SWITCH_DDCCI_PORT_MSG,
    _OSD_DISP_POWER_SAVING_MSG,
    _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG,
#if(_FREEZE_SUPPORT == _ON)
    _OSD_DISP_DISABLE_FREEZE_MSG,
#endif
#if(_DP_MST_SUPPORT == _ON)
    _OSD_DISP_MST_WARNING_MSG,
#endif
#if(_DM_FUNCTION == _ON)
    _OSD_DISP_DM_MAIN_MSG,
    _OSD_DISP_DM_SUB_MSG,
#endif
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
    _OSD_DISP_FW_UPDATE_MSG,
    _OSD_DISP_FW_UPDATE_BAR_MSG,
#endif
} EnumOSDDispMsg;

typedef enum
{
    _ICON_POS_UP_0,
    _ICON_POS_UP_1,
    _ICON_POS_UP_2,
    _ICON_POS_UP_3,
    _ICON_POS_DOWN_0,
    _ICON_POS_DOWN_1,
    _ICON_POS_DOWN_2,
    _ICON_POS_DOWN_3,
} EnumOSDMainMenuIcon;

typedef enum
{
    _POS_NOTICE_NO_SUPPORT_ICON,
    _POS_NOTICE_NO_SUPPORT_TEXT_0,
    _POS_NOTICE_NO_SUPPORT_TEXT_1,

    _POS_NOTICE_NO_CABLE_ICON,
    _POS_NOTICE_NO_CABLE_TEXT_0,
    _POS_NOTICE_NO_CABLE_TEXT_1,

    _POS_NOTICE_NO_SIGNAL_ICON,
    _POS_NOTICE_NO_SIGNAL_TEXT_0,
    _POS_NOTICE_NO_SIGNAL_TEXT_1,
}EnumOSDNoticeIcon;

typedef enum
{
    _STRING_PICTURE,
    _STRING_DISPLAYFUNCTION,
    _STRING_COLOR,
    _STRING_ADVANCE,
    _STRING_AUDIO,
    _STRING_OTHER,
    _STRING_MUTIP,
    _STRING_ULTRAHDR,
    _STRING_QUICKLINK,
    _STRING_INPUT,
    _STRING_FACTORY,
#if(_DM_FUNCTION == _ON)
    _STRING_DVISION_VISION,
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
    _STRING_ARC_EARC,
#endif
    // picture
    _STRING_BACKLIGHT,
    _STRING_BRIGHTNESS,
    _STRING_CONTRAST,
    _STRING_SHARPNESS,

    // Display
    _STRING_AUTO_ADJUST,
    _STRING_AUTO_COLOR,
    _STRING_HPOS,
    _STRING_VPOS,
    _STRING_CLOCK,
    _STRING_PHASE,
    _STRING_DISP_ROTATE,
    _STRING_DISP_LATENCY,
    _STRING_FREEZE,

    // Muti function
    _STRING_DISPLAYMODE,
    _STRING_SELECTREGION,
    _STRING_DISP_LR_RATIO,
    _STRING_PIP_POSITION,
    _STRING_PIP_POSITION_USER,
    _STRING_PIP_TRANSPARENCY,
    _STRING_PIP_SIZE,
    _STRING_INPUT_SWAP,

    // color
    _STRING_PANEL_UNIFORMITY,
    _STRING_GAMMA,
    _STRING_COLOR_TEMP,
    _STRING_COLOR_TEMP_USER,
    _STRING_COLOR_EFFECT,
    _STRING_COLOR_EFFECT_USER,
    _STRING_DEMO,
    _STRING_DEMO_SIDE,
    _STRING_COLOR_FORMAT,
    _STRING_PCM,
    _STRING_HUE,
    _STRING_SATURATION,
    _STRING_LIGHTNESS,

    // advance
    _STRING_ASPECT_RATIO,
    _STRING_OVER_SCAN,
    _STRING_OVER_DRIVE,
    _STRING_DDCCI,
    _STRING_ULTRA_VIVID,
    _STRING_DCR,
    _STRING_DP_OPTION,
    _STRING_DP_MST,
    _STRING_DP_RESOLUTION,
    _STRING_CLONE,
    _STRING_MST_TX,
    _STRING_HDMI_VERSION,
    _STRING_FREESYNC,
    _STRING_TYPEC_MODE,
    _STRING_LOCAL_DIMMING,
    _STRING_LD_SMOOTHADJ,
    _STRING_PIXEL_SHIFT,
    _STRING_SDR_TO_HDR,
    _STRING_DUAL_DP_EDID,
    _STRING_GLOBAL_DIMMING,
    _STRING_OWL_SIGHT,
    _STRING_DSC,
    _STRING_HUB_SWITCH,
    _STRING_EAGLE_SIGHT,
    _STRING_MBR,
    _STRING_DP_ALPM,
    _STRING_DP_ADAPTIVESYNC,
    _STRING_PANEL_REPLAY,

    // audio
    _STRING_VOLUME,
    _STRING_MUTE,
    _STRING_STAND_ALONG,
    _STRING_AUDIO_SOURCE,
    _STRING_SOUND_MODE,
    _STRING_AUDIO_SELF_TEST,
    _STRING_TTS_SUPPORT,
    _STRING_TTS_TEXT_VOLUME,
    _STRING_TTS_AUDIO_VOLUME,

    // other
    _STRING_RESET,
    _STRING_MENU_TIME,
    _STRING_OSD_HPOS,
    _STRING_OSD_VPOS,
    _STRING_LANGUAGE,
    _STRING_TRANSPARENCY,
    _STRING_ROTATE,
    _STRING_BORDER_WIDTH,
    _STRING_BORDER_COLOR,
    // HDR
    _STRING_HDR_MODE,
    _STRING_DARK_ENHANCE,
    _STRING_SHARPNESS_ENHANCE,
    _STRING_HDR_CONTRAST,
    _STRING_COLOR_ENHANCE,
    _STRING_LIGHT_ENHANCE,
    _STRING_HLG_OOTF,

    // Input Source
    _STRING_SOURCE_1P,
    _STRING_SOURCE_2P,
    _STRING_SOURCE_3P,
    _STRING_SOURCE_4P,
    _STRING_AUTO_SELECT,

    // display mode
    _STRING_1P,
    _STRING_2P_LR,
    _STRING_2P_TB,
    _STRING_2P_PIP,
    _STRING_3P_FLAG,
    _STRING_3P_SKEW_L,
    _STRING_3P_SKEW_R,
    _STRING_3P_SKEW_T,
    _STRING_3P_SKEW_B,
    _STRING_4P,

    _STRING_PIP_USER_POSITION_H,
    _STRING_PIP_USER_POSITION_V,
    // select region
    _STRING_2P_LR_L,
    _STRING_2P_LR_R,
    _STRING_2P_LR_FULL,
    _STRING_2P_TB_T,
    _STRING_2P_TB_B,
    _STRING_2P_TB_FULL,
    _STRING_2P_PIP_MAIN,
    _STRING_2P_PIP_SUB,
    _STRING_2P_PIP_FULL,
    _STRING_4P_LT_IN,
    _STRING_4P_LT_OUT,
    _STRING_4P_RT_IN,
    _STRING_4P_RT_OUT,
    _STRING_4P_LB_IN,
    _STRING_4P_LB_OUT,
    _STRING_4P_RB_IN,
    _STRING_4P_RB_OUT,
    _STRING_4P_FULL,
    _STRING_3P_FLAG_MAIN,
    _STRING_3P_FLAG_MAIN_OUT,
    _STRING_3P_FLAG_LEFT,
    _STRING_3P_FLAG_LEFT_OUT,
    _STRING_3P_FLAG_RIGHT,
    _STRING_3P_FLAG_RIGHT_OUT,
    _STRING_3P_FLAG_FULL,
    _STRING_3P_SKEW_MAIN,
    _STRING_3P_SKEW_MAIN_OUT,
    _STRING_3P_SKEW_UP,
    _STRING_3P_SKEW_UP_OUT,
    _STRING_3P_SKEW_DOWN,
    _STRING_3P_SKEW_DOWN_OUT,
    _STRING_3P_SKEW_FULL,

    _STRING_OFF,
    _STRING_ON,
    _STRING_ON_BY_POSITION,

    _STRING_D0,
    _STRING_D1,
    _STRING_D2,
    _STRING_D9,
    _STRING_D6,

    _STRING_1_DOT_1,
    _STRING_1_DOT_2,
    _STRING_DP_1_DOT_4,
    _STRING_DP_2_DOT_0,

    _STRING_AUDIO_LINE_IN,
    _STRING_AUDIO_DIGITAL_REGION1,
    _STRING_AUDIO_DIGITAL_REGION2,
    _STRING_AUDIO_DIGITAL_REGION3,
    _STRING_AUDIO_DIGITAL_REGION4,

    _STRING_AS_RATIO_FULL,
    _STRING_AS_RATIO_16_9,
    _STRING_AS_RATIO_4_3,
    _STRING_AS_RATIO_5_4,
    _STRING_AS_RATIO_ORIGINAL,
    _STRING_AS_RATIO_REDUCE,
    _STRING_AS_RATIO_ENLARGE,
    _STRING_AS_RATIO_USER,

    _STRING_ULTRA_VIVID_OFF,
    _STRING_ULTRA_VIVID_L,
    _STRING_ULTRA_VIVID_M,
    _STRING_ULTRA_VIVID_H,

    _STRING_TEMP_9300,
    _STRING_TEMP_7500,
    _STRING_TEMP_6500,
    _STRING_TEMP_5800,
    _STRING_TEMP_SRGB,
    _STRING_TEMP_USER,

    _STRING_COLOR_EFF_STD,
    _STRING_COLOR_EFF_GAME,
    _STRING_COLOR_EFF_MOVIE,
    _STRING_COLOR_EFF_PHOTO,
    _STRING_COLOR_EFF_VIVID,
    _STRING_SIX_COLOR,
    _STRING_CHAMELEON,
    _STRING_COLOR_EFF_USER,

    _STRING_COLOR_DEMO_OFF,
    _STRING_COLOR_DEMO_TYPE1,
    _STRING_COLOR_DEMO_TYPE2,
    _STRING_COLOR_DEMO_TYPE3,
    _STRING_COLOR_DEMO_TYPE4,
    _STRING_COLOR_DEMO_TYPE5,

    _STRING_COLOR_FORMAT_RGB,
    _STRING_COLOR_SPACE_YCBCR422,
    _STRING_COLOR_SPACE_YCBCR444,
    _STRING_COLOR_SPACE_YCBCR420,
    _STRING_COLOR_FORMAT_YUV,
    _STRING_COLOR_SPACE_Y_ONLY,
    _STRING_COLOR_SPACE_RAW,

    _STRING_TEMP_USER_R,
    _STRING_TEMP_USER_G,
    _STRING_TEMP_USER_B,

    _STRING_COLOR_PCM_NACTIVE,
    _STRING_COLOR_PCM_SRGB,
    _STRING_COLOR_PCM_ADOBE_RGB,
    _STRING_COLOR_PCM_SOFT_PROFT_1,
    _STRING_COLOR_PCM_SOFT_PROFT_2,
    _STRING_COLOR_PCM_USER,

    _STRING_COLOR_EFF_USER_R_HUE,
    _STRING_COLOR_EFF_USER_R_SAT,
    _STRING_COLOR_EFF_USER_Y_HUE,
    _STRING_COLOR_EFF_USER_Y_SAT,
    _STRING_COLOR_EFF_USER_G_HUE,
    _STRING_COLOR_EFF_USER_G_SAT,
    _STRING_COLOR_EFF_USER_C_HUE,
    _STRING_COLOR_EFF_USER_C_SAT,
    _STRING_COLOR_EFF_USER_B_HUE,
    _STRING_COLOR_EFF_USER_B_SAT,
    _STRING_COLOR_EFF_USER_M_HUE,
    _STRING_COLOR_EFF_USER_M_SAT,
    _STRING_COLOR_EFF_USER_HUE,
    _STRING_COLOR_EFF_USER_SAT,

    _STRING_MODE1,
    _STRING_MODE2,

    _STRING_0_DEGREE,
#if(_HW_DISPLAY_ROTATION_180_SUPPORT == _ON)
    _STRING_180_DEGREE,
#endif
#if(_HW_DISPLAY_ROTATION_90_SUPPORT == _ON)
    _STRING_90_DEGREE,
#endif
#if(_HW_DISPLAY_ROTATION_270_SUPPORT == _ON)
    _STRING_270_DEGREE,
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
    _STRING_LR_MIRROR,
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
    _STRING_UD_MIRROR,
#endif
    _STRING_DP_1080P,
    _STRING_DP_QHD,
    _STRING_DP_4K_60HZ,
    _STRING_DP_4K2K_240HZ,
    _STRING_DP_5K_144HZ,
    _STRING_DP_5K_8K_60HZ,

    _STRING_DUAL_DP_5K3K_60HZ,
    _STRING_DUAL_DP_4K2K_144HZ,
    _STRING_DUAL_DP_8K4K_60HZ,

    _STRING_NO,
    _STRING_YES,

    _STRING_MST_OFF,
    _STRING_MST_AUTO,
    _STRING_MST_D0,
    _STRING_MST_D1,
    _STRING_MST_D2,
    _STRING_MST_D6,

    _STRING_HDMI_D0,
    _STRING_HDMI_D1,
    _STRING_HDMI_D2,
    _STRING_HDMI_D3,
    _STRING_HDMI_D4,
    _STRING_HDMI_D5,

    _STRING_GAMMA_OFF,
    _STRING_GAMMA_1_DOT_8,
    _STRING_GAMMA_2_DOT_0,
    _STRING_GAMMA_2_DOT_2,
    _STRING_GAMMA_2_DOT_4,

    _STRING_1_DOT_4,
    _STRING_2_DOT_0,
    _STRING_2_DOT_1,

    _STRING_U3_ON,
    _STRING_U3_OFF,

    _STRING_HDR10_MODE_OFF,
    _STRING_HDR10_MODE_AUTO,
    _STRING_HDR10_MODE_FORCE_2084,
    _STRING_HDR10_MODE_AUTO_HLG,
    _STRING_HDR10_MODE_FORCE_HLG,

    _STRING_ENGLISH,
    _STRING_CHINESE_T,

    _STRING_DISABLE,
    _STRING_ENABLE,
    _STRING_INPUT_SELECT,

    _STRING_POSITION_LT,
    _STRING_POSITION_RT,
    _STRING_POSITION_LD,
    _STRING_POSITION_RD,
    _STRING_POSITION_CENTER,
    _STRING_POSITION_USER,


    _STRING_OSD_0_DEGREE,
    _STRING_OSD_90_DEGREE,
    _STRING_OSD_270_DEGREE,
    _STRING_OSD_180_DEGREE,

    _STRING_DSC_NONE,
    _STRING_DSC_D0,
    _STRING_DSC_D1,
    _STRING_DSC_D2,
    _STRING_DSC_D3,
    _STRING_DSC_D4,
    _STRING_DSC_D5,

    _STRING_CLONE_FIX_OFF,
    _STRING_CLONE_FIX_A0,
    _STRING_CLONE_FIX_D0,
    _STRING_CLONE_FIX_D1,
    _STRING_CLONE_FIX_D2,
    _STRING_CLONE_FIX_D3,
    _STRING_CLONE_FIX_D4,
    _STRING_CLONE_FIX_D5,
    _STRING_CLONE_FIX_D6,

    _STRING_DSC_OFF,
    _STRING_DSC_AUTO,

    _STRING_EAGLE_SIGHT_ONOFF,
    _STRING_EAGLE_SIGHT_SELECTREGION,
    _STRING_EAGLE_SIGHT_TRANSPARENT,
    _STRING_EAGLE_SIGHT_ZOOM,
    _STRING_EAGLE_SIGHT_CAP_POSITION,
    _STRING_EAGLE_SIGHT_DISP_POSITION,
    _STRING_EAGLE_SIGHT_BORDER,
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
    _STRING_EAGLE_SIGHT_CIRCLEWIN,
#endif
    _STRING_1_5_X,
    _STRING_2_0_X,
    _STRING_3_0_X,
    _STRING_4_0_X,

    _STRING_MBR_MODE,
    _STRING_MBR_DUTY,
    _STRING_MBR_POSITION,
    _STRING_MBR_OFF,
    _STRING_MBR_USERMODE,
    _STRING_MBR_RTK_ADV,

// Show OSD Number
    _STRING_SHOW_NUMBER,

    // information
    _STRING_HFREQPCLK_0,
    _STRING_HFREQPCLK_1,
    _STRING_HFREQPCLK_2,
    _STRING_HFREQPCLK_3,

    _STRING_VGA_USER_MODE,
    _STRING_VGA_PRESET_MODE,

    // HDCP
    _STRING_HDCP_NONE,
    _STRING_HDCP_14,
    _STRING_HDCP_22,
    _STRING_HDCP_14_REPEATER,
    _STRING_HDCP_22_REPEATER,

    _STRING_FREESYNC_SUPPORT_V_RANGE,
    _STRING_DRR_STATUS,

    // Adjust message
    _STRING_PLEASE_WAIT,
    _STRING_NO_SIGNAL,
    _STRING_NO_CABLE,
    _STRING_NO_SUPPORT,
    _STRING_GO_TO_POWER_SAVING_MODE,
    _STRING_NOW_RESOLUTION_0,
    _STRING_NOW_RESOLUTION_1,
    _STRING_NOW_RESOLUTION_2,
    _STRING_NOW_RESOLUTION_3,

    _STRING_PASS,
    _STRING_FAIL,

    _STRING_2P,
    _STRING_3P,

    _STRING_USB_AUTO,
    _STRING_USB_TYPEB,
    _STRING_USB_D0,
    _STRING_USB_D1,

    _STRING_HLG_STANDARD,
    _STRING_HLG_USER1,
    _STRING_HLG_USER2,
    _STRING_HLG_USER3,

    _STRING_SBTM,
    _STRING_HLG,
    _STRING_HDR_NOTM,
    _STRING_SDR,

    _STRING_ANALOG,
    _STRING_INFORMATION,
    _STRING_ENTER,
    _STRING_EXIT_HOTKEY,
    _STRING_INSIDE,
    _STRING_OUTSIDE,
    _STRING_SINGLE_DP_EDID,

    _STRING_OWLSIGHT_OFF,
    _STRING_OWLSIGHT_L,
    _STRING_OWLSIGHT_M,
    _STRING_OWLSIGHT_H,
    _STRING_OWLSIGHT_USER,
    _STRING_OWLSIGHT_BLENDING,
    _STRING_OWLSIGHT_DIFFGAIN,
#if(_DM_FUNCTION == _ON)
    _STRING_DVISION,
    _STRING_DVISION_PICTURE,
    _STRING_DVISION_BACKLIGHT,
    _STRING_DVISION_BRIGHTNESS,
    _STRING_DVISION_CONTRAST,
    _STRING_DVISION_SATURATION,
    _STRING_DVISION_RESET,
    _STRING_DVISION_NOTIFICATION,
    _STRING_DVISION_DARK,
    _STRING_DVISION_BRIGHT,
    _STRING_DVISION_GAME,
    _STRING_DVISION_USER,
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
    _STRING_AUDIO_ARC_OUT,
    _STRING_AUDIO_ARC_PORT,
    _STRING_AUDIO_ARC_MODE,
    _STRING_ARC_EARC_OFF,
    _STRING_ARC_MODE,
    _STRING_EARC_MODE,
    _STRING_AUDIO_ARC_MUTE,
    _STRING_AUDIO_ARC_CHANEL,
    _STRING_AUDIO_ARC_2_CH,
    _STRING_AUDIO_ARC_8_CH,
    _STRING_AUDIO_ARC_PORT_LINE_IN,
    _STRING_AUDIO_ARC_PORT_D0,
    _STRING_AUDIO_ARC_PORT_D1,
    _STRING_AUDIO_ARC_PORT_D2,
    _STRING_AUDIO_ARC_PORT_D3,
    _STRING_AUDIO_ARC_PORT_D4,
    _STRING_AUDIO_DAC,
    _STRING_AUDIO_ARC,
#endif

    _STRING_PXP_MST,
    _STRING_OFF_PXP_MST,
    _STRING_ON_FIXED,
    _STRING_ON_SELECT,

    _STRING_OD,
    _STRING_SDR_PLUS,
    _STRING_SDR_PLUS_ADJ,
    _STRING_SDR_PLUS_SHARP,
    _STRING_SDR_PLUS_DARK,
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
    _STRING_NIGHT_SNIPER,
    _STRING_NIGHT_SNIPER_SELECT,
    _STRING_NIGHT_SNIPER_SATURATION,
    _STRING_NIGHT_SNIPER_LIGHTNESS,
#endif
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
    _STRING_FW_UPDATE,
    _STRING_FW_UPDATE_MSG1,
    _STRING_FW_UPDATE_MSG2,
    _STRING_FW_UPDATE_MSG3,
    _STRING_RESULT_MSG1,
    _STRING_RESULT_MSG2,
    _STRING_RESULT_MSG3,
    _STRING_RESULT_MSG4,
    _STRING_RESULT_MSG5,
#endif
    _STRING_CROSSHAIR,

    _STRING_ANTI_ALIASING,
    _STRING_MODE,
    _STRING_LEVEL,
    _STRING_EDGE_ENHANCE,
    _STRING_NOISE_REDUCTION,
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
    _STRING_EYE_PROTECT,
    _STRING_LOWBLUE,
    _STRING_PROTECT_LEVEL,
    _STRING_NIGHT_MODE,
    _STRING_AMBIENT_SENCE,
    _STRING_LOWBLUE_OFF,
    _STRING_ADAPTIVE_MODE,
    _STRING_GLOBAL_MODE,
    _STRING_STATIC_GLOBAL_MODE,
    _STRING_LEVEL0,
    _STRING_LEVEL1,
    _STRING_LEVEL2,
    _STRING_LEVEL3,
    _STRING_NIGHT_OFF,
    _STRING_NIGHT_1MIN,
    _STRING_NIGHT_5MIN,
    _STRING_NIGHT_10MIN,
#endif
    _STRING_ENERGYSAVE,
    _STRIN_END,
}EnumStringIndex;

typedef enum
{
    // input
    _STRING_A0_PORT = _STRIN_END,
    _STRING_D0_PORT,
    _STRING_D1_PORT,
    _STRING_D2_PORT,
    _STRING_D3_PORT,
    _STRING_D4_PORT,
    _STRING_D5_PORT,
    _STRING_D6_PORT,
    _STRING_D7_PORT,
    _STRING_D8_PORT,
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    _STRING_D9_PORT,
    _STRING_D9_D0_PORT,
    _STRING_D9_D1_PORT,
    _STRING_D9_D2_PORT,
#endif
    _STRING_AUTOSELECT_PORT,
}EnumStringPort;

typedef enum
{
    _OSD_ROTATE_DISPLAY_FULL = 0,
    _OSD_ROTATE_DISPLAY_PIXEL_BY_PIXEL,
    _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO,
}EnumOsdRotationDisplaySizeDef;

typedef enum
{
    _AUTO_CONFIG_DO = 0,
    _AUTO_CONFIG_RESULT,
}EnumAutoConfig;

typedef enum
{
    _OSD_HLW_INSIDE = 0,
    _OSD_HLW_OUTSIDE,
}EnumOSDHLWRegion;

typedef enum
{
    _OSD_HUB_AUTO = 0,
    _OSD_HUB_TYPEB,
    _OSD_HUB_D0,
    _OSD_HUB_D1,
}EnumOsdUSBHubUfpSwitch;

typedef enum
{
    _EAGLE_SIGHT_FUNCTION = 0,
    _EAGLE_SIGHT_COLOR_REGION,
    _EAGLE_SIGHT_TRANSPARENT,
    _EAGLE_SIGHT_ZOOM,
    _EAGLE_SIGHT_CAPTURE_POSITION,
    _EAGLE_SIGHT_DISPLAY_POSITION,
    _EAGLE_SIGHT_BORDER_WIDTH,
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
    _EAGLE_SIGHT_CIRCLE_WINDOW,
#endif
}EnumOsdEagleSightItem;

typedef enum
{
    _OSD_MBR_OFF = 0,
    _OSD_MBR_USERMODE,
    _OSD_MBR_RTK_ADV,
}EnumOsdMBR;

typedef enum
{
    _MBR_MODE = 0,
    _MBR_DUTY,
    _MBR_POSITION,
}EnumOsdMBRMode;

typedef enum
{
    _CROSSHAIR_OFF = 0,
    _CROSSHAIR_ON,
    _CROSSHAIR_POSITION,
}EnumOsdCrosshairMode;

typedef enum
{
    _LOWBLUE_MODE = 0,
    _PROTECT_LEVEL,
    _NIGHT_MODE,
    _AMBIENT_SENSE_MODE,
}EnumOsdEyeProtectItem;

typedef enum
{
    _LOWBLUE_OFF = 0,
    _LOWBLUE_ADAPTIVE,
    _LOWBLUE_GLOBAL,
    _LOWBLUE_STATIC_GLOBAL,
}EnumLowBlueType;
typedef enum
{
    _EYEPROTECT_TIME_OFF = 0,
    _EYEPROTECT_TIME_1MIN,
    _EYEPROTECT_TIME_5MIN,
    _EYEPROTECT_TIME_10MIN,
}EnumNightModeTimeType;
typedef enum
{
    _EYEPROTECT_LEVEL_0 = 0,
    _EYEPROTECT_LEVEL_1,
    _EYEPROTECT_LEVEL_2,
    _EYEPROTECT_LEVEL_3,
}EnumEyeProtectLevelType;

#if(_AUDIO_ARC_SUPPORT == _ON)
typedef enum
{
    _ARC_DAC = 0,
    _ARC_ARC,
}EnumAudioArcOutType;
typedef enum
{
    _ARC_2_CH = 0,
    _ARC_8_CH,
}EnumAudioArcChanel;

typedef enum
{
    _AUDIO_ARC_EARC_OFF = 0,
    _AUDIO_ARC_ON,
    _AUDIO_EARC_ON,
}EnumAudioArcType;

typedef enum
{
    _ARC_PORT_LINE_IN = 0,
    _ARC_PORT_D0,
    _ARC_PORT_D1,
    _ARC_PORT_D2,
    _ARC_PORT_D3,
    _ARC_PORT_D4,
}EnumAudioArcPortType;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
// __RTD_POWER__
extern bit g_bPowerForcePowSavStatus;

// __RTD_OSD__
extern StructOsdInfo g_stOsdInfo;
extern WORD g_usAdjustValue;
extern WORD g_usBackupValue;
extern WORD g_us4thItemNum;
extern volatile BYTE g_ucLogoTimerCounter;
extern bit g_bOsdLogoTransparencyDec;

// __RTD_OSDFUNC__
extern WORD g_usFontSelectStart;
extern WORD g_usFontTableStart;
extern BYTE g_ucOsdWidth;
extern BYTE g_ucOsdHeight;
extern BYTE g_ucOsdWidthB;
extern BYTE g_ucOsdHeightB;
extern WORD g_usFontPointer0;
extern WORD g_usFontPointer1;
extern WORD g_usFontPointer2;
extern WORD g_usFontPointer3;

#if(_COLOR_DEMO_FUNCTION == _ON)
extern bit g_bColorHLWinRLMove;
extern WORD g_usColorHLWinHPos;
extern WORD g_usColorHLWinHWidth;
extern WORD g_usColorHLWinVPos;
extern WORD g_usColorHLWinVHeight;
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
extern bit g_bflagMinuteON;
extern StructTimer g_stTimer;
extern StructPixelOrbitingStatus g_stPixelOrbitingStatus;
#endif

//----------------------------------------------------------------------------------------
// Extern Tables from OsdFont.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTVLC__
extern BYTE code tICON_REALTEK_1BIT_LOGO0[];
extern BYTE code tICON_REALTEK_1BIT_LOGO1[];

//----------------------------------------------------------------------------------------
// Extern Tables from OsdTable.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTTABLE__
extern BYTE code tOSD_iREALTEK[];
extern BYTE code tOSD_iKEY_BACK[];
extern BYTE code tOSD_iKEY_LEFT[];
extern BYTE code tOSD_iKEY_RIGHT[];
extern BYTE code tOSD_iKEY_ENTER[];
extern BYTE code tOSD_iKEY_EXIT[];



//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from RTDKey.c
//----------------------------------------------------------------------------------------
// __RTD_KEY__
extern void RTDKeyHandler(void);
extern void RTDKeyInitial(void);
extern void RTDKeyPadLedControl(BYTE ucKeyPadLed);

//----------------------------------------------------------------------------------------
// Extern functions from Osd.c
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// Extern functions from OsdFunc.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFUNC__
extern void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
extern void OsdFuncApplyMapOsdAB(BYTE ucWidthA, BYTE ucHeightA, BYTE ucColorA, BYTE ucWidthB, BYTE ucHeightB, BYTE ucColorB);
#endif

extern void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
extern void OsdFuncTransparency(BYTE ucTrans);
extern void OsdFuncBlending(BYTE ucType);
//extern BYTE OsdFuncGetOsdFontPointer(BYTE ucPointerSelect);
//extern BYTE OsdFuncSetOsdFontPointer(BYTE ucPointerSelect, BYTE ucPointer);
extern void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex);
extern void OsdFuncDisableOsd(void);
extern void OsdFuncEnableOsd(void);
extern void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom);
extern void OsdFuncSet2BitIconOffset(WORD usOffset);
extern void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);

#if(_SIX_COLOR_SUPPORT == _ON)
extern void OsdFuncSixColorAdjust(void);
#endif

#if(_COLOR_FORMAT_CONVERT_FUNCTION == _ON)
extern void OsdFuncColorFormatAdjust(EnumDisplayRegion enumRegion);
#endif

extern void OsdFuncColorPcmAdjust(void);
extern BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum, BYTE ucRegion);
#if(_FREEZE_SUPPORT == _ON)
extern bit OsdFuncCheckFreezeDisableMsg(void);
extern bit OsdFuncCheckFreezeDisable(void);
extern void OsdFuncShowOSDAfterClosedFreezeMsg(void);
#endif

extern void OsdFuncShowSourceMenuCheck(void);
#if(_HDR10_SUPPORT == _ON)
extern bit OsdFuncHdrRegionCheck(void);
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern BYTE OsdFuncGetHdmiPortVersion(EnumInputPort enumInputPort);
extern void OsdFuncSetHdmiPortVersion(EnumInputPort enumInputPort, BYTE ucValue);
#endif

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
extern void OsdFuncMapRotation(EnumOsdRotateType enumOsdRotateType, EnumOsdRotateMapA enumOsdRotateMapA, BYTE ucMapARowSize, EnumOsdRotateMapB enumOsdRotateMapB, BYTE ucMapBRowSize, EnumOsdRotateFontLib enumOsdRotateFontLib);
#endif

extern void OsdFuncHardwareCompression(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType, bit bTableLocation);
extern void OsdFuncSetAutoSearchPort(EnumRegionIndex enumRegionIdx);

//----------------------------------------------------------------------------------------
// Extern functions from OsdDisplay.c
//----------------------------------------------------------------------------------------
// __RTD_OSDDISPLAY__
extern void OsdDispPopMenuCheck(void);
extern void OsdDispDisableOsd(void);
extern void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);
extern void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState);
extern void OsdDispMainMenu(void);
extern void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue);
extern WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
extern void OsdDispOsdReset(void);
extern void OsdDispHotKeyOptionMenu(void);
extern void OsdDispHotKeySourceMenuIcon(BYTE ucPort);
extern void OsdDispHotKeySourceMenu(void);

extern void OsdDispHotKeySourceMenuSwitch(BYTE ucPort);

extern void OsdDispPanelUniformityMsgSwitch(void);
extern void OsdDispOsdMessage(EnumOSDDispMsg enumMessage);
#if(_DM_FUNCTION == _ON)
extern void OsdDispOsdDMMessage(EnumOSDDispMsg enumMessage);
#endif
#if(_VGA_SUPPORT == _ON)
extern void OsdDispAutoConfigProc(void);
extern void OsdDisplayAutoBalanceProc(void);
#endif

extern void OsdDispShowLogo(void);
#if(_GOSD_SUPPORT == _ON)
extern void OsdDispGosdShowLogo(void);
#endif

extern void OsdDisplaySixColorGetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor);
extern void OsdDisplaySixColorSetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor);
#if(_SIX_COLOR_SUPPORT == _ON)
extern void OsdDisplaySixColorGetOneColorData(EnumSelRegion enumSelRegion, BYTE ucColor, StructICMSetting *pstICMData);
#endif

extern void OsdDispMpUpdateDisplayStateNotice(bit bOn, EnumDisplayRegion enumDisplayRegion);

#if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
extern BYTE OsdDispMpDisplayStateGetNoticeType(EnumDisplayRegion enumDisplayRegion, bit bOn);
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
extern void OsdDispMpDisplayStateNotice_2P_LR(BYTE ucNoticeL, BYTE ucNoticeR);
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
extern void OsdDispMpDisplayStateNotice_2P_TB(BYTE ucNoticeT, BYTE ucNoticeB);
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
extern void OsdDispMpDisplayStateNotice_2P_PIP(BYTE ucNoticeMain, BYTE ucNoticeSub);
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
extern void OsdDispMpDisplayStateNotice_3P_FLAG(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P);
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
extern void OsdDispMpDisplayStateNotice_3P_SKEWL(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P);
extern void OsdDispMpDisplayStateNotice_3P_SKEWR(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P);
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
extern void OsdDispMpDisplayStateNotice_3P_SKEWT(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P);
extern void OsdDispMpDisplayStateNotice_3P_SKEWB(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P);
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
extern void OsdDispMpDisplayStateNotice_4P(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P, BYTE ucNotice4P);
#endif

extern void OsdDisp1stMenuIconString(BYTE ucIconPos, WORD usIcon, BYTE ucColor);
extern void OsdDisp2ndMenuReDraw(WORD usOsdState, bit bRedrawLevel);
extern bit OsdDisp2ndMenuCheck(WORD usOsdState);
extern void OsdDisp2ndMenuEnter(BYTE ucIndex, WORD usOsdState);

extern bit OsdDisp2ndMutiPSelectbyKey(void);
extern bit OsdDisp2ndPictureSelectbyKey(void);
extern bit OsdDisp2ndDisplaySelectbyKey(void);
extern bit OsdDisp2ndColorSelectbyKey(void);
extern bit OsdDisp2ndAdvanceSelectbyKey(void);
extern bit OsdDisp2ndAudioSelectbyKey(void);
extern bit OsdDisp2ndOtherSelectbyKey(void);
extern bit OsdDisp2ndHdrSelectbyKey(void);
extern bit OsdDisp2ndQuicklinkSelectbyKey(void);
extern bit OsdDisp2ndInputSelectbyKey(void);
#if(_DM_FUNCTION == _ON)
extern bit OsdDisp2ndDVisionSelectbyKey(void);
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
extern bit OsdDisp2ndeArcSelectbyKey(void);
#endif
extern void OsdDisp1stMenuCursor(BYTE ucIdx);
extern void OsdDisp1stMenuRedraw(void);
extern BYTE OsdDisp1stMenuGetIdx(EnumOsdItem enumOsdItem);
extern void OsdDisp2ndMenuCursor(BYTE ucIdex);
extern void OsdDisp1stMenuSelectbyKey(void);
extern void OsdDisp1stMenuEnterCheck(void);
extern void OsdDispItemValueUpdate(EnumOsdItem enumOsdItem);
extern void OsdDisp4thMenuEnter(WORD usOsdState);
extern void OsdDisp3rdMenuReDraw(WORD usOsdState);
extern void OsdDisp3rdItemAdj(EnumOsdItem enumOsdItem, bit bitbAdjShow);
extern void OsdDisp4thItemAdj(bit bitbAdjShow);

extern EnumOsdMenuStatus OsdDispGetUpLayer(EnumOsdItem enumOsdItem);
extern BYTE OsdDispGetOsdItemIdx(EnumOsdItem enumOsdItem);
extern void OsdDispDirectMenu(EnumOsdItem enumOsdItem);

#if(_PIXEL_SHIFT_SUPPORT == _ON)
extern void OsdDisplayPixelOrbitingAction(void);
extern void OsdDisplaySetPixelOrbitingCapability(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from OsdFont.c
//----------------------------------------------------------------------------------------
// __RTD_OSDFONTVLC__
extern void OsdFontVLCLoadFont(BYTE ucState);
extern void OsdFontVLCLoadFontByGen(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, WORD usFontTableStart, EnumOsdRotateType enumOsdRotateType);

// __RTD_OSDFONTDYNAMICICON_1__
extern void OsdFontVLCDynamicLoadIcon(BYTE ucIconPos, WORD usIcon);

// __RTD_OSDFONTDYNAMICICON_2__
extern void OsdFontVLCLoadMainIcon_2(BYTE ucIconPos, WORD usIcon);
#if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
extern void OsdFontLoadNoticeIcon(BYTE ucIconPos, WORD usIcon);
#endif

// __RTD_OSDFONTTABLE__
extern void OsdFontPut1Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor);
extern void OsdFontPut1BitTable(BYTE ucRow, BYTE ucCol, BYTE *pucArray, BYTE ucColor);
extern void OsdFontPut1BitMainMenuIcon(WORD usRow, WORD usCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
#if(_DM_FUNCTION == _ON)
extern void OsdFontPut1BitMapAB(WORD usRow, WORD usCol, BYTE ucByte0, BYTE ucIcon, BYTE ucColor);
extern void OsdFontPut1BitTableMapAB(WORD usRow, WORD usCol, BYTE ucByte0, BYTE *pucArray, BYTE ucColor);
#endif

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON) || (_3P_DISPLAY_SUPPORT == _ON))
extern void OsdFontPut1BitMainMenuIconOsdB(WORD usRow, WORD usCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
#endif
extern void OsdFontPut4Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucCPIdx);
extern void OsdFontCrosshair(void);
//extern void OsdFontPut2Bit(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
//extern void OsdFontPut2BitTable(BYTE ucRow, BYTE ucCol, BYTE *pArray, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);

// __RTD_OSDFONTPROP__
#if(_HW_FOSD_HW_PUT_STRING_GEN_TYPE == _OSD_HW_PUT_STRING_GEN_1)
extern void OsdPropHWPutString(WORD usRow, WORD usCol, BYTE ucFptsSelect, WORD usString, BYTE ucColor, BYTE ucLaHWnguage);
#endif
extern void OsdPropPutString(WORD usRow, WORD usCol, BYTE ucFptsSelect, WORD usString, BYTE ucColor, BYTE ucLanguage);
extern void OsdPropPutStringCenter(WORD usRow, WORD usCol, BYTE ucWidth, BYTE ucFptsSelect, WORD usString, BYTE ucColor, BYTE ucLanguage);
extern void OsdPropShowNumber(WORD usRow, WORD usCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
extern BYTE OsdPutStringPropFontTable(BYTE ucLanguage, WORD usFontPoint);
extern void OsdPropShowFreeSyncVFreqRange(WORD usRow, WORD usCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucColor);
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
extern void OsdPropShowPercentage(WORD usRow, WORD usCol, BYTE ucPercentage);
extern void OsdPropShowFileName(WORD usRow, WORD usCol);
#endif
#if(_DRR_SUPPORT == _ON)
extern void OsdPropShowDrrStatus(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucColor);
#endif
// __RTD_OSDPALETTE__
extern void OsdPaletteSelectPalette(BYTE ucValue);

// __RTD_OSDWINDOW__
extern void OsdWindowDrawing(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
extern void OsdWindowDrawingByFont(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
extern void OsdWindowDrawingByFontHighlight(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor);
extern void OsdWindowSlider(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState);
extern void OsdWindowSliderDisable(void);
extern void OsdWindowGridLine(BYTE ucLineIdx);

//----------------------------------------------------------------------------------------
// Extern functions from OsdTableFunc.c
//----------------------------------------------------------------------------------------
// __RTD_OSDTABLEFUNC__
extern void OsdTableFuncShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint);
extern BYTE OsdTableFuncVideoResolution(void);
extern void OsdTableFuncPutStringProp(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucStringIndex, BYTE ucLanguage);
extern void OsdTableFuncPutStringCenter(BYTE ucRow, BYTE ucColStart, BYTE ucColEnd, BYTE ucFptsSelect, BYTE ucString, BYTE ucStringIndex, SBYTE chCenterOffset, BYTE ucLanguage);
extern void OsdTableFuncDrawWindow(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
extern void OsdTableFuncPutIcon1BitTable(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucForeground, BYTE ucBackground);
extern void OsdTableFuncPutIcon2BitTable(BYTE ucRow, BYTE ucCol, BYTE ucIcon, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);

#if(_GOSD_SUPPORT == _ON)
//----------------------------------------------------------------------------------------
// Extern functions from OsdGosd.c
//----------------------------------------------------------------------------------------
// __RTD_OSDGOSD__
extern void GosdFuncDisplaySharpnessSetting(EnumGosdDisplayOSD enumOsd, BYTE ucEnhanceLevel, EnumDBApply enumDBApply);
#endif // End of #if(_GOSD_SUPPORT == _ON)

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)


#include <RTD2020NVRamOsd.h>
