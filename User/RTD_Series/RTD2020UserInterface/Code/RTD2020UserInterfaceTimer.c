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
// ID Code      : RTD2020UserInterfaceTimer.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_TIMER__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceTimer.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : User timer event process
// Input Value  : Event ID
// Output Value : None
//--------------------------------------------------
void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _USER_TIMER_EVENT_KEY_REPEAT_ENABLE:
            SET_KEYREPEATSTART();
            break;

        case _USER_TIMER_EVENT_KEY_SCAN_READY:
            SET_KEYSCANREADY();
            break;

        case _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO:
            OsdDispDisableOsd();
#if(_GOSD_SUPPORT == _ON)
            // set SubBlending mix Fosd only
            UserCommonOsdSubBlendingSetFosdMixerEnable(_ENABLE);
            UserCommonOsdSubBlendingSetGosdMixerEnable(_DISABLE);
#else // #if(_GOSD_SUPPORT == _ON)
#if(_INSTANT_TIMER_EVENT_0 == _ON)
            UserCommonTimer0SetTimerCount(_TIMER_OFF);
#endif // #if(_INSTANT_TIMER_EVENT_0 == _ON)
#endif // #if(_GOSD_SUPPORT == _ON)
            SET_OSD_LOGO_ON(_OFF);

#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
            UserCommonPowerPanelAction(_BACKLIGHT_OFF);
#else
            UserCommonPowerPanelAction(_PANEL_OFF);
#endif
            UserCommonDDomainBackgroundEnable(_DDOMAIN_RGN_ALL, _ENABLE);
            UserCommonDDomainPatternGenEnable(_DISABLE);
            break;

        case _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOCABLE_MSG);
            break;

        case _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOSIGNAL_MSG);
            break;

        case _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG);
            break;

        case _USER_TIMER_EVENT_GO_TO_POWER_SAVING:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG);
            break;

        case _USER_TIMER_EVENT_OSD_DISABLE:
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
        case _USER_TIMER_EVENT_UPDATE_OSD_DISABLE:
#endif
            OsdDispDisableOsd();
            OsdDispPopMenuCheck();
            break;

#if(_VGA_SUPPORT == _ON)
        case _USER_TIMER_EVENT_DO_AUTO_COLOR:
            CLR_KEY_HOLD();
            OsdDisplayAutoBalanceProc();
            break;
#endif

        case _USER_TIMER_EVENT_PANEL_USED_TIMER:
            RTDFactoryPanelUsedTimer();
            break;

#if(_COLOR_DEMO_FUNCTION == _ON)
        case _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE:
            if((SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) != 0X00) ||
               (SysModeGetModeState() == _MODE_STATUS_DISPLAY_SETTING))
            {
                UserAdjustHLWinType5Move();
            }
            break;
#endif

        case _USER_TIMER_EVENT_OSD_KEYINFO_UNHIGHLIGHT:
            OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNHIGHLIGHT);
            break;

#if(_FREESYNC_SUPPORT == _ON)
        case _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ:
            if((GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION) &&
               (UserCommonDrrGetType() == _DRR_FREESYNC_TYPE))
            {
                // g_usFontPointer1 = GET_FREESYNC_OSD_ADDRESS();
                OsdPropPutStringCenter(ROW(3), COL(12), WIDTH(_OSD_MESSAGE_STRING_LENGHT), _PFONT_PAGE_2, _STRING_NOW_RESOLUTION_0, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                UserCommonTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ);
            }
            break;
#endif
#if(_FREEZE_SUPPORT == _ON)
        case _USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG:
            OsdFuncDisableOsd();
            if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) && (GET_OSD_STATE() != _MENU_NONE))
            {
                OsdFuncShowOSDAfterClosedFreezeMsg();
#if(_URGENT_EVENT_CHECK_MODE == _OFF)
                SET_FREEZE_DISABLE_MSG_STATE(_OFF);
#endif
            }
            break;
#endif
#if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)
        case _USER_TIMER_EVENT_HDR_BOOST:
            g_bColorLocalDimmingHdrBoost = _FALSE;
            break;

        case _USER_TIMER_EVENT_HDR_COOL:
            g_bColorLocalDimmingHdrBoost = _TRUE;
            break;
#endif
#if(_DM_FUNCTION == _ON)
        case _USER_TIMER_EVENT_OSD_DVISION_SHOW_LOGO_MAIN:
            OsdDispOsdDMMessage(_OSD_DISP_DM_MAIN_MSG);
            UserCommonTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            DebugMessageDM("DM_ShowDMLogo_Main", 0);
            break;
        case _USER_TIMER_EVENT_OSD_DVISION_SHOW_LOGO_SUB:
            OsdDispOsdDMMessage(_OSD_DISP_DM_SUB_MSG);
            UserCommonTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            DebugMessageDM("DM_ShowDMLogo_Sub", 1);
            break;
#endif

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

        case _USER_TIMER_EVENT_AUDIO_TTS_SHOW_LOGO:

            if(UserInterfaceAudioGetTtsAudioReady() != _AUDIO_TTS_PLAY_READY)
            {
                UserCommonTimerReactiveTimerEvent(SEC(1), _USER_TIMER_EVENT_AUDIO_TTS_SHOW_LOGO);
            }
            else
            {
                UserAdjustAudioTtsPlayEvent(_AUDIO_TTS_EVENT_OSD_LOGO_SHOW);

                UserCommonTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
            }
            break;

        case _USER_TIMER_EVENT_AUDIO_TTS_POWER_OFF:
            SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
            break;
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
        case _USER_TIMER_EVENT_UPDATE_PROCESSING:
            // Update FW Update Progress rate
            g_usAdjustValue = SysUsbU2HostFwUpdateProgressRate();
            if(g_usAdjustValue < _100_PERCENT)
            {
                g_usAdjustValue = g_usAdjustValue + 1;
                OsdWindowDrawing(_SLIDER_1_BAR_WINDOW, ((14 * 12) + _BAR_BORDER), ((27) + _BAR_BORDER), (((14 * 12) + _BAR_BORDER) + (g_usAdjustValue * (240 - _BAR_BORDER - _BAR_BORDER) / _100_PERCENT)), ((27 + 36) - _BAR_BORDER), _CP_WHITE);
                OsdPropShowPercentage(ROW(2), COL(23), g_usAdjustValue);

                // Error Handling when FW Update
                if(SysUsbU2HostGetEventStatus(_U2HOST_FW_UPDATE_EVENT) == _U2HOST_EVENT_FAIL)
                {
                    OsdPropPutString(ROW(4), COL(14), _PFONT_PAGE_2, _STRING_RESULT_MSG4, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    SET_OSD_FW_UPDATE_NOW(_OFF);
                    UserCommonTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_UPDATE_OSD_DISABLE);
                    SysUsbU2HostClearEventStatus(_U2HOST_FW_UPDATE_EVENT);
                }
                else
                {
                    UserCommonTimerActiveTimerEvent(100, _USER_TIMER_EVENT_UPDATE_PROCESSING);
                }
            }
            else
            {
                OsdWindowDrawing(_SLIDER_1_BAR_WINDOW, ((14 * 12) + _BAR_BORDER), ((27) + _BAR_BORDER), (((14 * 12) + _BAR_BORDER) + (g_usAdjustValue * (240 - _BAR_BORDER - _BAR_BORDER) / _100_PERCENT)), ((27 + 36) - _BAR_BORDER), _CP_WHITE);
                OsdPropShowPercentage(ROW(2), COL(23), _100_PERCENT);

                UserCommonOsdEnableOsd();
                g_usBackupValue = _OFF;
                SET_OSD_FW_UPDATE_NOW(_OFF);
                OsdPropPutString(ROW(4), COL(14), _PFONT_PAGE_2, _STRING_RESULT_MSG3, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                OsdPropPutString(ROW(5), COL(13), _PFONT_PAGE_2, _STRING_RESULT_MSG5, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                OsdPropPutStringCenter(ROW(6), COL(14), WIDTH(8), _PFONT_PAGE_2, _STRING_YES, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                OsdPropPutStringCenter(ROW(6), COL(22), WIDTH(8), _PFONT_PAGE_2, _STRING_NO, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(6), COL(22), WIDTH(8), HEIGHT(1), _CP_BLUE, _CP_WHITE, _CP_BLUE);
            }
            break;

        case _USER_TIMER_EVENT_WAIT_RESPONSE:

            // File Name Search Fail
            if(SysUsbU2HostGetEventStatus(_U2HOST_FILE_NAME_SEARCH_EVENT) == _U2HOST_EVENT_FAIL)
            {
                OsdPropPutString(ROW(7), COL(14), _PFONT_PAGE_1, _STRING_RESULT_MSG2, COLOR(_CP_RED, _CP_BG), _ENGLISH);
                SET_OSD_FW_UPDATE_COUNT(0);
                UserCommonTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_UPDATE_OSD_DISABLE);
                SysUsbU2HostClearEventStatus(_U2HOST_FILE_NAME_SEARCH_EVENT);
            }
#if((_USB2_HOST_EHCI_FW_PROGRAM_FW_VERSION_CHECK == _ON) && (_CUSTOMER_FW_VERSION_SUPPORT == _ON))
            // File Name Search Pass and FW Version check Fail
            else if((SysUsbU2HostGetEventStatus(_U2HOST_FILE_NAME_SEARCH_EVENT) == _U2HOST_EVENT_PASS) && (SysUsbU2HostGetEventStatus(_U2HOST_FW_VERSION_CHECK_EVENT) == _U2HOST_EVENT_FAIL))
            {
                OsdFuncClearOsd(ROW(5), COL(14), LENGTH(22), HEIGHT(2));
                OsdPropPutString(ROW(5), COL(14), _PFONT_PAGE_1, _STRING_RESULT_MSG1, COLOR(_CP_RED, _CP_BG), _ENGLISH);
                SET_OSD_FW_UPDATE_COUNT(0);
                UserCommonTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_UPDATE_OSD_DISABLE);
                SysUsbU2HostClearEventStatus(_U2HOST_FILE_NAME_SEARCH_EVENT);
                SysUsbU2HostClearEventStatus(_U2HOST_FW_VERSION_CHECK_EVENT);
            }
            // File Name Search Pass and FW Version check Pass
            else if((SysUsbU2HostGetEventStatus(_U2HOST_FILE_NAME_SEARCH_EVENT) == _U2HOST_EVENT_PASS) && (SysUsbU2HostGetEventStatus(_U2HOST_FW_VERSION_CHECK_EVENT) == _U2HOST_EVENT_PASS))
            {
                // update Now or not
                OsdFuncClearOsd(ROW(5), COL(14), LENGTH(22), HEIGHT(3));
                OsdPropPutString(ROW(6), COL(14), _PFONT_PAGE_1, _STRING_FW_UPDATE_MSG2, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                OsdPropPutStringCenter(ROW(7), COL(14), WIDTH(8), _PFONT_PAGE_0, _STRING_YES, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                OsdPropPutStringCenter(ROW(7), COL(22), WIDTH(8), _PFONT_PAGE_0, _STRING_NO, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(7), COL(22), WIDTH(8), HEIGHT(1), _CP_BLUE, _CP_WHITE, _CP_BLUE);
                SET_OSD_STATE(_MENU_FW_UPDATE_CHECK_MSG);
                SET_OSD_FW_UPDATE_COUNT(0);
                SysUsbU2HostClearEventStatus(_U2HOST_FILE_NAME_SEARCH_EVENT);
                SysUsbU2HostClearEventStatus(_U2HOST_FW_VERSION_CHECK_EVENT);
            }
#else
            else if(SysUsbU2HostGetEventStatus(_U2HOST_FILE_NAME_SEARCH_EVENT) == _U2HOST_EVENT_PASS)
            {
                // update Now or not
                OsdFuncClearOsd(ROW(5), COL(14), LENGTH(22), HEIGHT(3));
                OsdPropPutString(ROW(6), COL(14), _PFONT_PAGE_1, _STRING_FW_UPDATE_MSG2, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                OsdPropPutStringCenter(ROW(7), COL(14), WIDTH(8), _PFONT_PAGE_0, _STRING_YES, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                OsdPropPutStringCenter(ROW(7), COL(22), WIDTH(8), _PFONT_PAGE_0, _STRING_NO, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(7), COL(22), WIDTH(8), HEIGHT(1), _CP_BLUE, _CP_WHITE, _CP_BLUE);
                SET_OSD_STATE(_MENU_FW_UPDATE_CHECK_MSG);
                SET_OSD_FW_UPDATE_COUNT(0);
                SysUsbU2HostClearEventStatus(_U2HOST_FILE_NAME_SEARCH_EVENT);
                SysUsbU2HostClearEventStatus(_U2HOST_FW_VERSION_CHECK_EVENT);
            }
#endif
            else
            {
                if(GET_OSD_FW_UPDATE_COUNT() > 12)
                {
                    // timeout skip update process
                    OsdPropPutString(ROW(7), COL(14), _PFONT_PAGE_1, _STRING_RESULT_MSG2, COLOR(_CP_RED, _CP_BG), _ENGLISH);
                    SET_OSD_FW_UPDATE_COUNT(0);
                    UserCommonTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_UPDATE_OSD_DISABLE);
                    SysUsbU2HostSetEventChange(_U2HOST_OSD_FW_UPDATE_ENABLE, _DISABLE);

                    break;
                }
                UserCommonTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_WAIT_RESPONSE);
                UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                SET_OSD_FW_UPDATE_COUNT(GET_OSD_FW_UPDATE_COUNT() + 1);

                // Countdown 10 sec OSD View
                // OsdPropShowNumber(ROW(5), COL(30),GET_OSD_FW_UPDATE_COUNT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_3, _OSD_NUMBER_UNSTLECT_COLOR);
            }
            break;
#endif
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        case _USER_TIMER_EVENT_EYE_PROTECT_TIMEOUT:
            if(GET_OSD_EYEPROTECT_LOWBLUE() != _LOWBLUE_OFF)
            {
                SET_OSD_EYEPROTECT_TIME_MIN_COUNT(GET_OSD_EYEPROTECT_TIME_MIN_COUNT() + 1);
                UserCommonColorLowBlueAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            }
            break;
#endif

        default:
            break;
    }
}

#if(_INSTANT_TIMER_EVENT_0 == _ON)
//--------------------------------------------------
// Description  : Action in Timer0 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------

void UserInterfaceTimer0InstantAccess_T0INT(void)
{
    if(GET_OSD_LOGO_ON() == _ON)
    {
        if(g_ucLogoTimerCounter == _OSD_TRANSPARENCY_MAX)
        {
            g_bOsdLogoTransparencyDec = _TRUE;
        }
        else if(g_ucLogoTimerCounter == 0x30)
        {
            g_bOsdLogoTransparencyDec = _FALSE;
        }
        UserCommonOsdSetTransparency_T0INT((g_bOsdLogoTransparencyDec == _TRUE) ? (g_ucLogoTimerCounter--) : (g_ucLogoTimerCounter++));
    }
}

#endif // End of #if(_INSTANT_TIMER_EVENT_0 == _ON)

#if(_INSTANT_TIMER_EVENT_1 == _ON)
//--------------------------------------------------
// Description  : Action in Timer1 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------

void UserInterfaceTimer1InstantAccess_T1INT(void)
{
#if(_PIXEL_SHIFT_SUPPORT == _ON)
    g_bflagMinuteON = _FALSE;

    GET_OSD_TIME_FOR_INTCOUNT()++;

    // one second count
    if(GET_OSD_TIME_FOR_INTCOUNT() >= 2)
    {
        SET_OSD_TIME_FOR_INTCOUNT(0);
        GET_OSD_TIME_FOR_MINUTE()++;
        g_bflagMinuteON = _TRUE;
    }

    // one hour count
    if(GET_OSD_TIME_FOR_MINUTE() >= 60)
    {
        SET_OSD_TIME_FOR_MINUTE(0);
    }
#endif
}

#endif // End of #if(_INSTANT_TIMER_EVENT_1 == _ON)

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
//--------------------------------------------------
// Description  : Action in Timer2 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------

void UserInterfaceTimer2InstantAccess_T2INT(void)
{
}

#endif // End of #if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
