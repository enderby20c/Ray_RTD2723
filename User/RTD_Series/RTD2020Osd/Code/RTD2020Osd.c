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
// ID Code      : RTD2020Osd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSD__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructOsdInfo g_stOsdInfo;

WORD g_usAdjustValue;
WORD g_usBackupValue;
WORD g_us4thItemNum;

volatile BYTE g_ucLogoTimerCounter;
bit g_bOsdLogoTransparencyDec;

#if(_PIXEL_SHIFT_SUPPORT == _ON)
StructTimer g_stTimer;
StructPixelOrbitingStatus g_stPixelOrbitingStatus;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void RTDOsdSystemFlowProc(void);
void RTDOsdEventMsgProc(void);

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : OSD system flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDOsdSystemFlowProc(void)
{
    switch(SysModeGetModeState())
    {
        case _MODE_STATUS_POWER_OFF:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
            }

            break;

        case _MODE_STATUS_INITIAL:

            if(SysModeGetModeStateChange() == _TRUE)
            {
#if(_FREESYNC_OD_MEASURE == _ON)
                UserAdjustFreeSyncODMeasure();
#endif

                OsdDispShowLogo();
                UserCommonPowerPanelAction(_BACKLIGHT_ON);

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                UserCommonTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_AUDIO_TTS_SHOW_LOGO);
#else
                UserCommonTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
            }

            break;

        case _MODE_STATUS_DISPLAY_INITIAL:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    RTDKeyPadLedControl(_LED_POWER_SEARCH);
                }
            }

            break;

        case _MODE_STATUS_DISPLAY_SETTING:
        case _MODE_STATUS_DISPLAY_CHECK:

            // Polling display state change
            if(SysRegionCheckUserDisplayStateChange() == _TRUE)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    // Update LED status
                    if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) == 0X00)
                    {
                        RTDKeyPadLedControl(_LED_POWER_SEARCH);
#if(_FREEZE_SUPPORT == _ON)
                        if(GET_OSD_FREEZE_STATUS() == _ON)
                        {
                            SET_OSD_FREEZE_STATUS(_OFF);
                        }
#endif
                    }
                    else
                    {
                        RTDKeyPadLedControl(_LED_POWER_ACTIVE);

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                        UserAdjustAudioTtsPlayEvent(_AUDIO_TTS_EVENT_POWER_ON);
#endif
#endif
                    }
                }

                // Perform display state change actions
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
                {
                    switch(SysRegionGetDisplayState(_DISPLAY_RGN_1P))
                    {
                        case _DISPLAY_STATE_NO_SIGNAL:

                            // Check NSG to PS condition in single display
                            if(SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)) == _TRUE)
                            {
                                UserCommonTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                            }
                            else
                            {
                                UserCommonTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
                            }
                            break;

                        case _DISPLAY_STATE_OOR:

                            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOSUPPORT_MSG);
                            break;

                        default:
                            break;
                    }
                }
#if(_MULTI_DISPLAY_MAX != 0X01)
                else
                {
                    EnumDisplayRegion enumIndexRegion = _DISPLAY_RGN_NONE;
                    BYTE ucIndex = 0x00;
                    BYTE ucMaxIndex = SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX);

                    // Check separate display state
                    for(ucIndex = 0x00; ucIndex < ucMaxIndex; ++ucIndex)
                    {
                        enumIndexRegion = SysRegionGetDisplayRegion(ucIndex);

                        if(SysRegionCheckDisplayEvent(enumIndexRegion, _DISPLAY_EVENT_STATE_CHANGE_USR) == _TRUE)
                        {
                            switch(SysRegionGetDisplayState(enumIndexRegion))
                            {
                                case _DISPLAY_STATE_NO_SIGNAL:
                                case _DISPLAY_STATE_OOR:
                                case _DISPLAY_STATE_NONE:
                                    if((GET_OSD_STATE() == _MENU_NONE) ||
                                       (GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION))
                                    {
                                        OsdDispMpUpdateDisplayStateNotice(_OFF, enumIndexRegion);
                                        UserCommonTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
                                    }
                                    break;

                                default:
                                    break;
                            }
                        }
                    }

                    // Check NSG to PS condition in multi-display
                    if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                    {
                        if((GET_OSD_STATE() != _MENU_NONE) &&
                           (GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION))
                        {
                            OsdDispDisableOsd();
                        }

                        UserCommonTimerActiveTimerEvent(SEC(6), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                    }
                }
#endif // End of #if(_MULTI_DISPLAY_MAX != 0X01)
            }
#if(_PIXEL_SHIFT_SUPPORT == _ON)
            if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) &&
               (SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) != 0))
            {
                OsdDisplayPixelOrbitingAction();
            }
#endif
            break;

        case _MODE_STATUS_POWER_SAVING:

            if(SysSourceGetCableStatusChange(SysSourceGetInputPort()) == _TRUE)// when cable ststua change, continue source handler.
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
            }

            if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
            {
                if(GET_OSD_WAKE_UP_SHOW_QUICKLINK_MENU() == _TRUE)
                {
                    SET_OSD_WAKE_UP_SHOW_QUICKLINK_MENU(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_WAKE_UP_SHOW_QUICKLINK_MENU_MSG);
                }
                else if(GET_OSD_POWER_SAVING_SHOW_SOURCE() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_SOURCE(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG);
                }
            }

            break;

        case _MODE_STATUS_FACTORY:

            break;

        default:

            break;
    }

    switch(SysModeGetModeState())
    {
        case _MODE_STATUS_POWER_OFF:
        case _MODE_STATUS_INITIAL:
        case _MODE_STATUS_DISPLAY_INITIAL:

            // Skip key process check in off, initial, and display initial states
            return;

        default:

            if(GET_KEYMESSAGE() < _KEY_AMOUNT)
            {
                // Set repeat-key enable
                if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) ||
                   (SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
                {
                    if((GET_OSD_STATE() != _MENU_NONE) &&
                       ((GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE) || (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)))
                    {
                        SET_KEYREPEATENABLE();
                    }
                }

                if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
                {
                    RTDFactoryMenuOperation();
                    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                }
                else
                {
#if(_FREEZE_SUPPORT == _ON)
                    if(OsdFuncCheckFreezeDisableMsg() == _TRUE)
                    {
                        break;
                    }
#endif

#if(_FREEZE_SUPPORT == _ON)
                    if(OsdFuncCheckFreezeDisable() == _TRUE) // Confirm whether disable the freeze status
                    {
                        break;
                    }
#endif
                    if((GET_OSD_STATE() > _MENU_NONE) &&
                       (GET_OSD_STATE() < _MENU_HOTKEY_SOURCE))
                    {
                        OsdDispMainMenuKeyInfo(GET_KEYMESSAGE(), _OSD_HIGHLIGHT);
                    }

                    // Perform OSD action
                    (*tOperationTable[GET_OSD_STATE()])();

                    // Reactive OSD disable event in check state
                    if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) && (GET_OSD_IN_FACTORY_MENU_STATUS() != _TRUE))
                    {
                        if(GET_OSD_TIME_OUT() <= _OSD_TIMEOUT_MIN)
                        {
                            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                        }
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
                        else if((GET_OSD_STATE() > _MENU_ADVANCE_FW_UPDATE) && (GET_OSD_STATE() <= _MENU_FW_UPDATE_PROCESS_BAR))
                        {
                            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                        }
#endif
                        else if(GET_OSD_STATE() != _MENU_NONE)
                        {
                            UserCommonTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
                        }
                    }
                    else
                    {
                        OsdFuncShowSourceMenuCheck();
                    }
                }
            }
            break;
    }
}

//--------------------------------------------------
// Description  : OSD event message processing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDOsdEventMsgProc(void)
{
    switch(GET_OSD_EVENT_MESSAGE())
    {
        case _OSDEVENT_SHOW_NOSIGNAL_MSG:
            OsdDispOsdMessage(_OSD_DISP_NOSIGNAL_MSG);
            UserCommonPowerPanelAction(_BACKLIGHT_ON);
            UserCommonTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOCABLE_MSG:
            OsdDispOsdMessage(_OSD_DISP_NOCABLE_MSG);
            UserCommonPowerPanelAction(_BACKLIGHT_ON);
            UserCommonTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOSUPPORT_MSG:
            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

            OsdDispOsdMessage(_OSD_DISP_NOSUPPORT_MSG);
            UserCommonPowerPanelAction(_BACKLIGHT_ON);
            UserCommonTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG:
            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            OsdDispHotKeySourceMenu();

            UserCommonTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            UserCommonPowerPanelAction(_BACKLIGHT_ON);
            break;

        case _OSDEVENT_WAKE_UP_SHOW_QUICKLINK_MENU_MSG: // wake up show QuickLink Menu
            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            OsdDispHotKeyOptionMenu();
            UserCommonTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            UserCommonPowerPanelAction(_BACKLIGHT_ON);

            break;

        case _OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG:

            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                // OsdDispDisableOsd();
                OsdDispOsdMessage(_OSD_DISP_POWER_SAVING_MSG);
                UserCommonPowerPanelAction(_BACKLIGHT_ON);

                UserCommonTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                UserAdjustAudioTtsPlayEvent(_AUDIO_TTS_EVENT_POWER_SAVING);
#endif
#endif
            }
            else
            {
                // For multi-display, show PS message only when all NSG
                if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _FALSE)
                {
                    break;
                }
                else
                {
                    // OsdDispDisableOsd();
                    OsdDispOsdMessage(_OSD_DISP_POWER_SAVING_MSG);
                    UserCommonPowerPanelAction(_BACKLIGHT_ON);

                    UserCommonTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                    UserAdjustAudioTtsPlayEvent(_AUDIO_TTS_EVENT_POWER_SAVING);
#endif
#endif
                }
            }

            break;

        case _OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG:

            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                OsdDispDisableOsd();

                SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
            }
            else
            {
                // For multi-display, go to PS only when all NSG
                if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _FALSE)
                {
                    break;
                }
                else
                {
                    OsdDispDisableOsd();

                    SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
                }
            }

            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_DO_AUTO_CONFIG_MSG:
#if(_FREEZE_SUPPORT == _ON)
            UserCommonTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
#endif
            OsdDispAutoConfigProc();
            break;
#endif

        case _OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG:
            if((GET_OSD_STATE() == _MENU_NONE) || (GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION))
            {
                OsdDispMpUpdateDisplayStateNotice(_OFF, _DISPLAY_RGN_NONE);
                UserCommonTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            break;

        case _OSDEVENT_ACTIVE_DO_ONE_TIME_MSG:

#if(_FREEZE_SUPPORT == _ON)
            UserCommonTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
#endif

#if(_VGA_SUPPORT == _ON)
            if(SysRegionGetInputPort(SysModeGetDisplayTarget()) == _A0_INPUT_PORT)
            {
                if(UserInterfaceVgaGetFirstAutoConfigStatus() == _DO_AUTO_CONFIG_TRUE)
                {
                    OsdDispAutoConfigProc();
                }
            }
#endif

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
            if(GET_OSD_FW_UPDATE_NOW() == _ON)
            {
                OsdDispOsdMessage(_OSD_DISP_FW_UPDATE_BAR_MSG);
                UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                break;
            }
#endif

            if((GET_OSD_STATE() == _MENU_NONE) || (GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION))
            {
                OsdDispMpUpdateDisplayStateNotice(_OFF, _DISPLAY_RGN_NONE);

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                UserCommonTimerActiveTimerEvent(SEC(11), _USER_TIMER_EVENT_OSD_DISABLE);
#else
                UserCommonTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
            }
            break;

        case _OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG:
            UserCommonNVRamSaveSystemData();
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG:
            UserCommonNVRamSaveModeUserData();
            break;
#endif
        case _OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG:
            RTDNVRamSaveOsdUserData();
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_SAVE_NVRAM_ADCDATA_MSG:
            if(UserCommonColorGetColorSpaceRGB(GET_OSD_COLOR_FORMAT(SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION()))) == _TRUE)
            {
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
            }
            else
            {
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
            }
            break;
#endif

        case _OSDEVENT_SAVE_NVRAM_COLORPROC_MSG:
            RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
            break;

        case _OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG:
            RTDNVRamSaveOsdInputPortData(UserAdjustGetSelectRegionPort());
            break;

        case _OSDEVENT_SAVE_NVRAM_INPUTSOURCEDATA_MSG:
            RTDNVRamSaveOsdInputSourceData(SysRegionGetSourceType(GET_OSD_SYSTEM_DISPLAY_REGION()));
            break;

        case _OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG:
            RTDNVRamSaveOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());
            break;


        case _OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG:
            RTDNVRamSaveOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
            break;

        case _OSDEVENT_SHOW_MP_NOSIGNAL_NOCABLE_MSG:
            if(((GET_OSD_STATE() == _MENU_NONE) ||
                (GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION)) &&
               (SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK))
            {
                OsdDispMpUpdateDisplayStateNotice(_OFF, _DISPLAY_RGN_NONE);
                UserCommonTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            break;

#if(_PIXEL_SHIFT_SUPPORT == _ON)
        case _OSDEVENT_PIXEL_ORBITING_ACTION_MSG:
            UserAdjustPixelOrbitingActive();
            SET_PIXEL_ORBITING_TIME(_PIXEL_SHIFT_TIME);
            break;
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _OSDEVENT_SAVE_AUDIO_ARC_EARC_DATA_MSG:
            RTDNVRamSaveAudioArcData();
            break;
#endif

        default:
            break;
    }
    SET_OSD_EVENT_MESSAGE(_OSDEVENT_NONE_MSG);
}

void MenuNone(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) &&
               (SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _FALSE))
            {
                OsdDispMainMenu();

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                UserAdjustAudioTtsPlayEvent(_AUDIO_TTS_EVENT_KEY_MENU);
#endif
#endif
            }
            else
            {
                SET_OSD_WAKE_UP_SHOW_QUICKLINK_MENU(_TRUE);

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            // input source
            CLR_KEYREPEATENABLE();

            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
                SET_OSD_POWER_SAVING_SHOW_SOURCE(_TRUE);

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            else if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdFuncShowSourceMenuCheck();
                OsdDispHotKeySourceMenu();
            }

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
            UserAdjustAudioTtsPlayEvent(_AUDIO_TTS_EVENT_KEY_RIGHT);
#endif
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            if(((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) && (SysRegionGetDisplayState(_DISPLAY_RGN_1P) != _DISPLAY_STATE_ACTIVE)) ||
               ((GET_OSD_DISPLAY_MODE() != _OSD_DM_1P) && (SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)))
            {
                break;
            }
            else
            {
                // active show input information
                OsdDispMpUpdateDisplayStateNotice(_ON, _DISPLAY_RGN_NONE);
                UserCommonTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                UserAdjustAudioTtsPlayEvent(_AUDIO_TTS_EVENT_KEY_LEFT);
#endif
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:

            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
                SET_OSD_POWER_SAVING_SHOW_SOURCE(_TRUE);

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            else
            {
                // auto adjust
#if(_VGA_SUPPORT == _ON)
                if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) &&
                   (SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
                   (GET_FAIL_SAFE_MODE(UserCommonRegionGetIndex(SysVgaGetRegion())) == _FALSE) &&
                   (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
                {
#if(_FREEZE_SUPPORT == _ON)
                    if(GET_OSD_FREEZE_STATUS() == _ON)
                    {
                        SET_OSD_FREEZE_STATUS(_OFF);
                        UserCommonDisplayFreeze(GET_OSD_FREEZE_STATUS());
                        OsdDispOsdMessage(_OSD_DISP_DISABLE_FREEZE_MSG);
                        UserCommonTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
                    }
#endif

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
                }
                else
#endif

                {
                    OsdDispDirectMenu(GET_OSD_HOTKEY_EXIT());
                }
            }
            break;

        default:
            break;
    }
}

void MeunMain(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp1stMenuEnterCheck();
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp1stMenuSelectbyKey();
            OsdDisp1stMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            OsdDispPopMenuCheck();
            break;

        default:
            break;
    }
}

void MenuPictureItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_PICTURE_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndPictureSelectbyKey() == _FALSE)
            {
                break;
            }
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_PICTURE));
            OsdDisp1stMenuRedraw();
            SET_OSD_STATE(_MENU_MAIN);
            break;

        default:
            break;
    }
}

void MenuDisplayItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_DISPLAY_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndDisplaySelectbyKey() == _FALSE)
            {
                break;
            }
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_DISPLAY));
            OsdDisp1stMenuRedraw();
            SET_OSD_STATE(_MENU_MAIN);
            break;

        default:
            break;
    }
}

void MenuColorItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_COLOR_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndColorSelectbyKey() == _FALSE)
            {
                break;
            }

            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_COLOR));
            OsdDisp1stMenuRedraw();
            SET_OSD_STATE(_MENU_MAIN);
            break;

        default:
            break;
    }
}

void MenuAdvanceItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_ADVANCE_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndAdvanceSelectbyKey() == _FALSE)
            {
                break;
            }
            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_ADVANCE));
            OsdDisp1stMenuRedraw();
            SET_OSD_STATE(_MENU_MAIN);

            break;

        default:
            break;
    }
}

void MenuAudioItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_AUDIO_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndAudioSelectbyKey() == _FALSE)
            {
                break;
            }

            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_AUDIO));
            OsdDisp1stMenuRedraw();
            SET_OSD_STATE(_MENU_MAIN);

            break;

        default:
            break;
    }
}

void MenuOtherItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_OTHER_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndOtherSelectbyKey() == _FALSE)
            {
                break;
            }

            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_OTHER));
            OsdDisp1stMenuRedraw();
            SET_OSD_STATE(_MENU_MAIN);

            break;

        default:
            break;
    }
}

void MenuHdrItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_HDR_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndHdrSelectbyKey() == _FALSE)
            {
                break;
            }

            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_HDR));
            OsdDisp1stMenuRedraw();
            SET_OSD_STATE(_MENU_MAIN);
            break;

        default:
            break;
    }
}

void MenuMutiPItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_MUTIP_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndMutiPSelectbyKey() == _FALSE)
            {
                break;
            }

            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_MUTIP));
            OsdDisp1stMenuRedraw();
            SET_OSD_STATE(_MENU_MAIN);
            break;

        default:
            break;
    }
}

void MenuQuickLinkItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_QUICKLINK_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndQuicklinkSelectbyKey() == _FALSE)
            {
                break;
            }

            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() != _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispDisableOsd();
            }
            else
            {
                SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_QUICKLINK));
                OsdDisp1stMenuRedraw();
                SET_OSD_STATE(_MENU_MAIN);
            }
            break;

        default:
            break;
    }
}

#if(_DM_FUNCTION == _ON)
void MenuDVisionItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_DVISION_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndDVisionSelectbyKey() == _FALSE)
            {
                break;
            }

            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() != _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispDisableOsd();
            }
            else
            {
                SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_DVISION));
                OsdDisp1stMenuRedraw();
                SET_OSD_STATE(_MENU_MAIN);
            }
            break;

        default:
            break;
    }
}
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
void MenuAudioArcItem(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_AUDIO_ARC_EARC_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndeArcSelectbyKey() == _FALSE)
            {
                break;
            }

            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() != _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispDisableOsd();
            }
            else
            {
                SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_AUDIO_ARC_EARC));
                OsdDisp1stMenuRedraw();
                SET_OSD_STATE(_MENU_MAIN);
            }
            break;

        default:
            break;
    }
}
#endif

void MenuDisplayMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            if(g_usBackupValue != g_usAdjustValue)
            {
#if(_COLOR_DEMO_FUNCTION == _ON)
                // Disable HLW
                SET_OSD_HLWIN_TYPE(_HL_WIN_OFF);
                UserAdjustHLWinType();
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
                if(GET_OSD_PXP_MST() != _DP_MST_PXP_OFF)
                {
                    SET_OSD_PXP_MST(_DP_MST_PXP_OFF);
                    UserAdjustDpMstRxPxpMode(GET_OSD_PXP_MST());
                }
#endif

                SET_OSD_DISPLAY_MODE(g_usAdjustValue);
                UserAdjustDisplayMode();

#if(_DP_MST_SUPPORT == _ON)
                UserCommonDpMstRxCapablePortSwitch(UserCommonDpGetMSTCapablePort());
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_MODE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_DISPLAYMODE, g_usAdjustValue);

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_MODE), _LOW);

            break;

        default:
            break;
    }
}

void MenuSelectRegion(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                SET_OSD_SELECT_REGION(g_usAdjustValue);
                UserAdjustOsdSelectRegionColorProc();
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_SELECTREGION), _LOW);
            break;

        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_SELECTREGIOM, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_SELECTREGION), _LOW);
            break;

        default:
            break;
    }
}

void MenuDisplayFunDispRotateAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_DISP_ROTATE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_DISP_ROTATE_ADJUST, g_usAdjustValue);
                SET_OSD_DISP_ROTATE(g_usAdjustValue);

                UserCommonPowerPanelAction(_BACKLIGHT_OFF);
                SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }
            break;


        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_DISP_ROTATE(g_usBackupValue);

                    UserCommonPowerPanelAction(_BACKLIGHT_OFF);
                    SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
                }
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_DISP_ROTATE), _LOW);
            }
            break;

        default:
            break;
    }
}

void MenuDisplayFunDispLatencyAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_LATENCY), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_LATENCY_ADJUST, g_usAdjustValue);
                SET_OSD_LATENCY(g_usAdjustValue);

                UserCommonPowerPanelAction(_BACKLIGHT_OFF);
                SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }

            break;

        case _EXIT_KEY_MESSAGE:

            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_LATENCY(g_usBackupValue);

                    UserCommonPowerPanelAction(_BACKLIGHT_OFF);
                    SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
                }
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_LATENCY), _LOW);
            }

            break;

        default:
            break;
    }
}

void MenuDisplayFunFreezeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_FREEZE_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_FREEZE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_FREEZE_ADJUST, g_usAdjustValue);
#if(_FREEZE_SUPPORT == _ON)
            UserCommonDisplayFreeze(g_usAdjustValue);
#endif

            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_FREEZE_STATUS(g_usBackupValue);
#if(_FREEZE_SUPPORT == _ON)
                UserCommonDisplayFreeze(GET_OSD_FREEZE_STATUS());
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_FREEZE), _LOW);
            break;

        default:
            break;
    }
}

void MenuDisplayFunLRratioAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                UserAdjustDisplayMode();

#if(_DP_MST_SUPPORT == _ON)
                UserCommonDpMstRxCapablePortSwitch(UserCommonDpGetMSTCapablePort());
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_LR_RATIO), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_LR_RATIO_ADJUST, g_usAdjustValue);
            // Set Ratio Status
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
            {
                SET_OSD_PBP_LR_RATIO(g_usAdjustValue);
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_FLAG)
            {
                SET_OSD_3P_FLAG_RATIO(g_usAdjustValue);
            }
            else
            {
                SET_OSD_3P_SKEW_LR_RATIO(g_usAdjustValue);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
                {
                    SET_OSD_PBP_LR_RATIO(g_usBackupValue);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_3P_FLAG)
                {
                    SET_OSD_3P_FLAG_RATIO(g_usBackupValue);
                }
                else
                {
                    SET_OSD_3P_SKEW_LR_RATIO(g_usBackupValue);
                }
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_LR_RATIO), _LOW);
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipPositionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_PIP_POSITION), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_ADJUST, g_usAdjustValue);
                SET_OSD_PIP_POSITION_TYPE(g_usAdjustValue);
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                {
#if(_COLOR_DEMO_FUNCTION == _ON)
                    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_MOVE)
                    {
                        UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
                        UserCommonDisplayPipSubTimingFormatAdjust();
                        UserCommonTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
                    }
                    else
#endif
                    {
                        UserCommonDisplayPipSubTimingFormatAdjust();
                    }
                }
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:

            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_PIP_POSITION_TYPE(g_usBackupValue);

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                    {
                        UserCommonDisplayPipSubTimingFormatAdjust();
                    }
#endif
                }
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_PIP_POSITION), _LOW);
            }
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipPositionUser(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_DISPLAYFUN_PIP_POSITION_USER);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_USER, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_PIP_POSITION_USER), _LOW);
            break;

        default:
            break;
    }
}


void MenuDisplayFunPipPositionHAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_DISPLAYFUN_PIP_POSITION_USER);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_H_ADJUST, g_usAdjustValue);
                SET_OSD_PIP_USER_POSITION_H(g_usAdjustValue);

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                {
                    UserCommonDisplayPipSubTimingFormatAdjust();
                }
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_PIP_USER_POSITION_H(g_usBackupValue);

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                    {
                        UserCommonDisplayPipSubTimingFormatAdjust();
                    }
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_DISPLAYFUN_PIP_POSITION_USER);
            }
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipPositionVAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_DISPLAYFUN_PIP_POSITION_USER);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_V_ADJUST, g_usAdjustValue);
                SET_OSD_PIP_USER_POSITION_V(g_usAdjustValue);

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                {
                    UserCommonDisplayPipSubTimingFormatAdjust();
                }
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_PIP_USER_POSITION_V(g_usBackupValue);

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                    {
                        UserCommonDisplayPipSubTimingFormatAdjust();
                    }
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_DISPLAYFUN_PIP_POSITION_USER);
            }
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipTransparencyAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PIP_TRANSPARENCY())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_PIP_TRANSPARENCY), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_TRANSPARENCY_ADJUST, g_usAdjustValue);
            SET_OSD_PIP_TRANSPARENCY(g_usAdjustValue);
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
#if(_PIP_TRANSPARENCY_SUPPORT == _ON)
            UserAdjustPipTransparency(g_usAdjustValue);
#endif
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_PIP_TRANSPARENCY(g_usBackupValue);
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
#if(_PIP_TRANSPARENCY_SUPPORT == _ON)
                UserAdjustPipTransparency(g_usBackupValue);
#endif
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_PIP_TRANSPARENCY), _LOW);
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipSizeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PIP_SIZE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_PIP_SIZE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_SIZE_ADJUST, g_usAdjustValue);
                SET_OSD_PIP_SIZE(g_usAdjustValue);

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                {
                    UserCommonDisplayPipSubTimingFormatAdjust();
                }
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_PIP_SIZE())
                {
                    SET_OSD_PIP_SIZE(g_usBackupValue);

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                    {
                        UserCommonDisplayPipSubTimingFormatAdjust();
                    }
#endif
                }
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_PIP_SIZE), _LOW);
            }
            break;

        default:
            break;
    }
}

void MenuPictureBacklightAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_BACKLIGHT())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                SET_OSD_BACKLIGHT(g_usAdjustValue);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_PICTURE_BACKLIGHT), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT_ADJUST, g_usAdjustValue);
            UserAdjustBacklight(g_usAdjustValue);
            SET_OSD_BACKLIGHT(g_usAdjustValue);
#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
            UserCommonColorHDRBackLightAdaptiveTMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            if(UserCommonRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()) != _NON_REGION)
            {
                UserCommonColorHDRBackLightAdaptiveTMAdjust(UserCommonRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()));
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_BACKLIGHT())
            {
                SET_OSD_BACKLIGHT(g_usBackupValue);
                UserAdjustBacklight(GET_OSD_BACKLIGHT());
#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
                UserCommonColorHDRBackLightAdaptiveTMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
                if(UserCommonRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()) != _NON_REGION)
                {
                    UserCommonColorHDRBackLightAdaptiveTMAdjust(UserCommonRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()));
                }
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_PICTURE_BACKLIGHT), _LOW);
            break;

        default:
            break;
    }
}

void MenuPictureBrightnessAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
                SET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_PICTURE_BRIGHTNESS), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS_ADJUST, g_usAdjustValue);

#if(_BRIGHTNESS_FUNCTION == _ON)
            SET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            UserCommonColorBrightnessAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION(), g_usBackupValue);

#if(_BRIGHTNESS_FUNCTION == _ON)
                UserCommonColorBrightnessAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_PICTURE_BRIGHTNESS), _LOW);
            break;

        default:
            break;
    }
}

void MenuPictureContrastAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
                SET_OSD_CONTRAST(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_PICTURE_CONTRAST), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST_ADJUST, g_usAdjustValue);

#if(_CONTRAST_FUNCTION == _ON)
            SET_OSD_CONTRAST(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_CONTRAST(GET_OSD_SELECT_REGION(), g_usBackupValue);

#if(_CONTRAST_FUNCTION == _ON)
                UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_PICTURE_CONTRAST), _LOW);
            break;

        default:
            break;
    }
}

void MenuPictureSharpnessAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_PICTURE_SHARNESS), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS_ADJUST, g_usAdjustValue);
            SET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort(), g_usAdjustValue);
#if(_SHARPNESS_FUNCTION == _ON)
            UserCommonColorSharpnessAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()))
            {
                SET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort(), g_usBackupValue);
#if(_SHARPNESS_FUNCTION == _ON)
                UserCommonColorSharpnessAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_PICTURE_SHARNESS), _LOW);

            break;

        default:
            break;
    }
}
void MenuDisplayHPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                SET_VGA_MODE_ADJUST_H_POSITION(g_usAdjustValue);
            }
#endif

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_HPOS), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            OsdDispSliderAndNumber(_MENU_ANALOG_HPOS_ADJUST, g_usAdjustValue);
            UserCommonDisplayHPositionAdjust(g_usAdjustValue, SysVgaGetRegion());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_VGA_MODE_ADJUST_H_POSITION(g_usBackupValue);
                UserCommonDisplayHPositionAdjust(GET_VGA_MODE_ADJUST_H_POSITION(), SysVgaGetRegion());
            }
#endif
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_HPOS), _LOW);

            break;

        default:
            break;
    }
}

void MenuDisplayVPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                SET_VGA_MODE_ADJUST_V_POSITION(g_usAdjustValue);
            }
#endif

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_VPOS), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            OsdDispSliderAndNumber(_MENU_ANALOG_VPOS_ADJUST, g_usAdjustValue);
            UserCommonDisplayVPositionAdjust(g_usAdjustValue, SysVgaGetRegion());
#endif
            break;

        case _EXIT_KEY_MESSAGE:

#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_VGA_MODE_ADJUST_V_POSITION(g_usBackupValue);
                UserCommonDisplayVPositionAdjust(GET_VGA_MODE_ADJUST_V_POSITION(), SysVgaGetRegion());
            }
#endif
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_VPOS), _LOW);

            break;

        default:
            break;
    }
}

void MenuDisplayClockAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
            }
#endif
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_CLOCK), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            OsdDispSliderAndNumber(_MENU_ANALOG_CLOCK_ADJUST, g_usAdjustValue);
            UserCommonVgaClockAdjust(g_usAdjustValue);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_VGA_MODE_ADJUST_CLOCK(g_usBackupValue);
                UserCommonVgaClockAdjust(GET_VGA_MODE_ADJUST_CLOCK());
            }
#endif
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_CLOCK), _LOW);

            break;

        default:
            break;
    }
}

void MenuDisplayPhaseAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                SET_VGA_MODE_ADJUST_PHASE(g_usAdjustValue);
            }
#endif
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_PHASE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            OsdDispSliderAndNumber(_MENU_ANALOG_PHASE_ADJUST, g_usAdjustValue);
            UserCommonVgaPhaseAdjust(g_usAdjustValue);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_VGA_MODE_ADJUST_PHASE(g_usBackupValue);
                UserCommonVgaPhaseAdjust(GET_VGA_MODE_ADJUST_PHASE());
            }
#endif
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DISPLAY_PHASE), _LOW);
            break;

        default:
            break;
    }
}

void MenuColorPanelUniformityAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_PANEL_UNIFORMITY), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_PANEL_UNIFORMITY_ADJUST, g_usAdjustValue);
            SET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION(), g_usAdjustValue);

#if(_UNIFORMITY_FUNCTION == _ON)
            UserAdjustPanelUniformityMode(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_UNIFORMITY_FUNCTION == _ON)
                UserAdjustPanelUniformityMode(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING);
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_PANEL_UNIFORMITY), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorGammaAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_GAMMA(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_GAMMA), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_GAMMA_ADJUST, g_usAdjustValue);
            SET_OSD_GAMMA(GET_OSD_SELECT_REGION(), g_usAdjustValue);

#if(_GAMMA_FUNCTION == _ON)
#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
            OsdFuncColorPcmAdjust();
#else
            UserAdjustGamma(GET_OSD_SYSTEM_SELECT_REGION());
#endif
#endif
            break;


        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_GAMMA(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_GAMMA(GET_OSD_SELECT_REGION(), g_usBackupValue);

#if(_GAMMA_FUNCTION == _ON)
#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
                OsdFuncColorPcmAdjust();
#else
                UserAdjustGamma(GET_OSD_SYSTEM_SELECT_REGION());
#endif
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_GAMMA), _LOW);
            break;

        default:
            break;
    }
}

void MenuColorColortempAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_TEMPERATURE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMPERATURE_ADJUST, g_usAdjustValue);
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), g_usAdjustValue);

            RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
#if((_OCC_PCM_GAMMA_SUPPORT == _ON) || (_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON))
            OsdFuncColorPcmAdjust();
#else
#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
#endif

            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()))
            {
                SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), g_usBackupValue);
                // Adjust Color
                RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
#if(_OCC_PCM_GAMMA_SUPPORT == _ON)
                OsdFuncColorPcmAdjust();
#else
#if(_CONTRAST_FUNCTION == _ON)
                UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_TEMPERATURE), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffectAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFFECT_ADJUST, g_usAdjustValue);
            SET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            UserAdjustColorEffectMode(GET_OSD_SYSTEM_SELECT_REGION());
            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION(), g_usBackupValue);
                UserAdjustColorEffectMode(GET_OSD_SYSTEM_SELECT_REGION());
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorDemoAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HLWIN_TYPE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_DEMO), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);

            OsdDispSliderAndNumber(_MENU_COLOR_DEMO_ADJUST, g_usAdjustValue);
            SET_OSD_HLWIN_TYPE(g_usAdjustValue);
            UserAdjustOsdSelectRegionColorProc();
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HLWIN_TYPE())
            {
                SET_OSD_HLWIN_TYPE(g_usBackupValue);
                UserAdjustOsdSelectRegionColorProc();
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_DEMO), _LOW);
            break;

        default:
            break;
    }
}
void MenuColorColorDemoSideAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HLWIN_SIDE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_DEMO_SIDE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_DEMO_SIDE_ADJUST, g_usAdjustValue);
            SET_OSD_HLWIN_SIDE(g_usAdjustValue);
            RTDNVRamSaveOsdUserData();

            // Add function here !!!!!!!!!
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HLWIN_SIDE())
            {
                SET_OSD_HLWIN_SIDE(g_usBackupValue);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_DEMO_SIDE), _LOW);
            break;

        default:
            break;
    }
}

void MenuColorColorFormatAdjust(void)
{
    EnumInputPort enumInputPort = SysRegionGetInputPort((GET_OSD_SYSTEM_DISPLAY_REGION()));

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_COLOR_FORMAT(enumInputPort))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_FORMAT), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_COLOR_FORMAT_ADJUST, g_usAdjustValue);
                if(g_usAdjustValue != GET_OSD_COLOR_FORMAT(enumInputPort))
                {
                    SET_OSD_COLOR_FORMAT(enumInputPort, g_usAdjustValue);
#if(_COLOR_FORMAT_CONVERT_FUNCTION == _ON)
                    OsdFuncColorFormatAdjust(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
                }
            }
            break;


        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_COLOR_FORMAT(enumInputPort))
                {
                    SET_OSD_COLOR_FORMAT(enumInputPort, g_usBackupValue);
#if(_COLOR_FORMAT_CONVERT_FUNCTION == _ON)
                    OsdFuncColorFormatAdjust(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
                }
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_FORMAT), _LOW);
            }
            break;

        default:
            break;
    }
}

void MenuColorColorPCMAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_PCM), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, g_usAdjustValue);
            SET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            OsdFuncColorPcmAdjust();

            break;



        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION(), g_usBackupValue);
                OsdFuncColorPcmAdjust();
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_PCM), _LOW);
            break;

        default:
            break;
    }
}

void MenuColorColorHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HUE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_HUE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_HUE_ADJUST, g_usAdjustValue);
            SET_OSD_HUE(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)
            UserAdjustGlobalHueSat(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HUE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_HUE(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)
                UserAdjustGlobalHueSat(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_HUE), _LOW);


            break;

        default:
            break;
    }
}

void MenuColorColorSaturationAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SATURATION(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_SATURATION), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_SATURATION_ADJUST, g_usAdjustValue);
            SET_OSD_SATURATION(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)
            UserAdjustGlobalHueSat(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SATURATION(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_SATURATION(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_GLOBAL_HUE_SATURATION_FUNCTION == _ON)
                UserAdjustGlobalHueSat(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_SATURATION), _LOW);

            break;

        default:
            break;
    }
}
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
void MenuColorEyeProtectAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_COLOR_EYE_PROTECT_ADJUST);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EYE_PROTECT_ADJUST, g_usAdjustValue);
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EYE_PROTECT), _LOW);

            break;

        default:
            break;
    }
}
#endif
void MenuAdvanceAspectAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_ASPECT), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_ASPECT_ADJUST, g_usAdjustValue);
                if(g_usAdjustValue != GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()))
                {
                    SET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort(), g_usAdjustValue);
#if(_ASPECT_RATIO_SUPPORT == _ON)
                    UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
                }
            }
            break;


        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()))
                {
                    SET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort(), g_usBackupValue);
                    // Adjust HLW
#if(_ASPECT_RATIO_SUPPORT == _ON)
                    UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
                }

                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_ASPECT), _LOW);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceOverScanAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_OVERSCAN), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_OVER_SCAN_ADJUST, g_usAdjustValue);
                SET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort(), g_usAdjustValue);

#if(_OVERSCAN_SUPPORT == _ON)
                UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()))
                {
                    SET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort(), g_usBackupValue);
#if(_OVERSCAN_SUPPORT == _ON)
                    UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
                }
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_OVERSCAN), _LOW);
            }
            break;

        default:
            break;
    }
}



void MenuAdvanceDdcciAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DDCCI_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DDCCI), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            OsdDispSliderAndNumber(_MENU_ADVANCE_DDCCI_ADJUST, g_usAdjustValue);
            SET_OSD_DDCCI_STATUS(g_usAdjustValue);
            UserCommonDdcciSwitchPort(UserAdjustDdcciGetStatus());
            UserCommonDdcciMapping();
            break;
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DDCCI_STATUS())
            {
                SET_OSD_DDCCI_STATUS(g_usBackupValue);
                UserCommonDdcciSwitchPort(UserAdjustDdcciGetStatus());
                UserCommonDdcciMapping();
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DDCCI), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceUltraVividAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_ULTRAVIVID), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(((GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()) == _ULTRA_VIVID_H) &&
                (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) ||
               ((GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()) == _ULTRA_VIVID_OFF) &&
                (GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)))
            {
            }
            else
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_ULTRA_VIVID_ADJUST, g_usAdjustValue);
                SET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION(), g_usAdjustValue);

#if(_ULTRA_VIVID_FUNCTION == _ON)
                UserCommonColorUltraVividAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif // End of #if(_ULTRA_VIVID_SUPPORT == _ON)
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_ULTRA_VIVID_FUNCTION == _ON)
                UserCommonColorUltraVividAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif // End of #if(_ULTRA_VIVID_SUPPORT == _ON)
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_ULTRAVIVID), _LOW);
            break;

        default:
            break;
    }
}


void MenuAdvanceDCRAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DCR_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DCR), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_DCR_ADJUST, g_usAdjustValue);
            SET_OSD_DCR_STATUS(g_usAdjustValue);

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DCR_STATUS())
            {
                SET_OSD_DCR_STATUS(g_usBackupValue);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DCR), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceDpOptionD0(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            OsdDisp4thMenuEnter(_MENU_ADVANCE_DP_OPTION_D0);
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_DP_OPTION_D0, 0);
            if(g_usAdjustValue == 0)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            }
            else if(g_usAdjustValue == 1)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            }
            else if(g_usAdjustValue == 2)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            }
            else if(g_usAdjustValue == 3)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            }
            break;



        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DPOPTION), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceDpOptionD1(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            OsdDisp4thMenuEnter(_MENU_ADVANCE_DP_OPTION_D1);
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_DP_OPTION_D1, 1);
            if(g_usAdjustValue == 0)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            }
            else if(g_usAdjustValue == 1)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            }
            else if(g_usAdjustValue == 2)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            }
            else if(g_usAdjustValue == 3)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            }
            break;



        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DPOPTION), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceDpOptionD2(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            OsdDisp4thMenuEnter(_MENU_ADVANCE_DP_OPTION_D2);
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_DP_OPTION_D2, 1);
            if(g_usAdjustValue == 0)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            }
            else if(g_usAdjustValue == 1)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            }
            else if(g_usAdjustValue == 2)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            }
            else if(g_usAdjustValue == 3)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            }
            break;



        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DPOPTION), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceDpOptionD6(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            OsdDisp4thMenuEnter(_MENU_ADVANCE_DP_OPTION_D6);
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_DP_OPTION_D6, 2);
            if(g_usAdjustValue == 0)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            }
            else if(g_usAdjustValue == 1)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            }
            else if(g_usAdjustValue == 2)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D2);
            }
            else if(g_usAdjustValue == 3)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            }
            break;



        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DPOPTION), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceDPMstAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                SET_OSD_DP_MST(g_usAdjustValue);
#if(_DP_MST_SUPPORT == _ON)
                UserCommonDpMstRxCapablePortSwitch(UserCommonDpGetMSTCapablePort());

                if(SysSourceGetPortTypeFromInputPort(SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION())) == _PORT_DP)
                {
                    UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
                }
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DPMST), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_DP_MST_ADJUST, g_usAdjustValue);

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_DP_MST(g_usBackupValue);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DPMST), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceCloneAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
#if(_MULTI_DISPLAY_MAX != 0x01)
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                SET_OSD_CLONE_MODE_MTP(g_usAdjustValue);

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
                if(GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_FIX_OFF)
                {
                    UserCommonDpMacTxCloneModeSwitch(_DP_CLONE_OUTPUT_FALSE);
                }
                else
                {
                    UserCommonDpMacTxCloneModeSwitch(_DP_CLONE_OUTPUT_TRUE);
                }
#endif
            }
            else
#endif
            {
                SET_OSD_CLONE_MODE_1P(g_usAdjustValue);

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
                if(GET_OSD_CLONE_MODE_1P() == _OSD_CLONE_FIX_OFF)
                {
                    UserCommonDpMacTxCloneModeSwitch(_DP_CLONE_OUTPUT_FALSE);
                }
                else
                {
                    UserCommonDpMacTxCloneModeSwitch(_DP_CLONE_OUTPUT_TRUE);
                }
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_CLONE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_CLONE_ADJUST, g_usAdjustValue);
            break;


        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
#if(_MULTI_DISPLAY_MAX != 0x01)
                if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
                {
                    SET_OSD_CLONE_MODE_MTP(g_usBackupValue);
                }
                else
#endif
                {
                    SET_OSD_CLONE_MODE_1P(g_usBackupValue);
                }
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_CLONE), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceFreeSyncAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_FREE_SYNC_STATUS(g_usAdjustValue);
#if(_FREESYNC_SUPPORT == _ON)
                UserCommonFreeSyncSupportSwitch();
#endif

#if((_HDMI_MULTI_EDID_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
#if(_TMDS_FS_ON_ONLY_TARGETPORT_HPD_SUPPORT == _ON)
                // Switch Edid for All HDMI Port, Only toggle Target Port HPD
                UserCommonEdidSwitchHdmiAllPortEdidToggleTargetPortHpd();
#else
                // Switch Edid for All HDMI Port
                UserCommonEdidSwitchHdmiAllPortEdid();
#endif
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                // Switch All DP Port Edid
                UserCommonEdidSwitchDpAllPortEdid();
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
                UserCommonColorHDRAdjust(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_FREESYNC), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_FREESYNC_ADJUST, g_usAdjustValue);

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_FREE_SYNC_STATUS(g_usBackupValue);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_FREESYNC), _LOW);

            break;

        default:
            break;
    }
}

void MenuAdvanceDualDPEdidAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                UserCommonNVRamSetSystemData(_DUAL_DP_EDID_SELECT, g_usAdjustValue);
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DUAL_DP_SUPPORT == _ON))
                UserCommonEdidSwitchDpEdid(_DUAL_DP_INPUT_PORT);
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DUAL_DP_EDID), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_DUAL_DP_EDID_ADJUST, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                UserCommonNVRamSetSystemData(_DUAL_DP_EDID_SELECT, g_usBackupValue);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DUAL_DP_EDID), _LOW);
            break;

        default:
            break;
    }
}
void MenuAdvanceEdidAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_EDID_DX_ADJUST);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_EDID_ADJUST, g_usAdjustValue);

            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DP_RESOLUTION), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceEdidDXAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if((g_us4thItemNum == 0) &&
               (g_usAdjustValue != g_usBackupValue))
            {
                UserCommonNVRamSetSystemData(_EDID_D0_SELECT, g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                UserCommonEdidSwitchDpEdid(_D0_INPUT_PORT);
#endif
            }
            else if((g_us4thItemNum == 1) &&
                    (g_usAdjustValue != g_usBackupValue))
            {
                UserCommonNVRamSetSystemData(_EDID_D1_SELECT, g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                UserCommonEdidSwitchDpEdid(_D1_INPUT_PORT);
#endif
            }
            else if((g_us4thItemNum == 2) &&
                    (g_usAdjustValue != g_usBackupValue))
            {
                UserCommonNVRamSetSystemData(_EDID_D2_SELECT, g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                UserCommonEdidSwitchDpEdid(_D2_INPUT_PORT);
#endif
            }
            else if((g_us4thItemNum == 3) &&
                    (g_usAdjustValue != g_usBackupValue))
            {
                UserCommonNVRamSetSystemData(_EDID_D6_SELECT, g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                UserCommonEdidSwitchDpEdid(_D6_INPUT_PORT);
#endif
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EDID_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            OsdDisp4thItemAdj(_ON);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EDID_ADJUST);
            break;

        default:
            break;
    }
}
void MenuAdvanceHDMIVersionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_HDMI_VERSION_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDMI_VERSION_ADJUST, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_HDMI_VERSIONS), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceDxHDMIVersionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(g_usAdjustValue != g_usBackupValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                OsdFuncSetHdmiPortVersion(_D0_INPUT_PORT + (g_us4thItemNum), g_usAdjustValue);

                // Add EDID DDCRAM Switch & HPD event
                UserCommonEdidSwitchHdmiEdid(_D0_INPUT_PORT + g_us4thItemNum, UserInterfaceEdidGetMultiHdmiEdidIndex(_D0_INPUT_PORT + g_us4thItemNum));
            }
#endif

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_HDMI_VERSION_ADJUST);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp4thItemAdj(_ON);

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_HDMI_VERSION_ADJUST);
            break;

        default:
            break;
    }
}
void MenuAdvanceDscAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usAdjustValue != g_usBackupValue)
            {
                EnumDisplayMode enumDisplayMode = SysModeGetDisplayMode();
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                enumDisplayMode = SysRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif
                if(enumDisplayMode == _DISPLAY_MODE_1P)
                {
                    SET_OSD_1P_DSC_PORT(g_usAdjustValue);
                }
                else
                {
                    SET_OSD_DSC_PORT(g_usAdjustValue);
                }

#if(_DSC_DECODER_SUPPORT == _ON)
                // Switch Port Capability of DSC
                UserCommonDscSwitchPortCapability(g_usBackupValue, g_usAdjustValue);
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DSC), _LOW);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_DSC_ADJUST, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                EnumDisplayMode enumDisplayMode = SysModeGetDisplayMode();
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                enumDisplayMode = SysRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif
                if(enumDisplayMode == _DISPLAY_MODE_1P)
                {
                    SET_OSD_1P_DSC_PORT(g_usBackupValue);
                }
                else
                {
                    SET_OSD_DSC_PORT(g_usBackupValue);
                }
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DSC), _LOW);
            break;

        default:
            break;
    }
}
void MenuAdvanceTypeCModeD0(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_TYPEC_MODE_D0);
            break;

        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_TYPEC_MODE_D0, 0);
            if(g_usAdjustValue == 0)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D0);
            }
            else if(g_usAdjustValue == 1)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D1);
            }
            else if(g_usAdjustValue == 2)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D2);
            }
            else if(g_usAdjustValue == 3)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D6);
            }
            break;



        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_TYPEC_MODE), _LOW);

            break;

        default:
            break;
    }
}

void MenuAdvanceTypeCModeD1(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_TYPEC_MODE_D1);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_TYPEC_MODE_D1, 1);
            if(g_usAdjustValue == 0)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D0);
            }
            else if(g_usAdjustValue == 1)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D1);
            }
            else if(g_usAdjustValue == 2)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D2);
            }
            else if(g_usAdjustValue == 3)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D6);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_TYPEC_MODE), _LOW);

            break;

        default:
            break;
    }
}

void MenuAdvanceTypeCModeD2(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_TYPEC_MODE_D2);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_TYPEC_MODE_D2, 2);
            if(g_usAdjustValue == 0)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D0);
            }
            else if(g_usAdjustValue == 1)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D1);
            }
            else if(g_usAdjustValue == 2)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D2);
            }
            else if(g_usAdjustValue == 3)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D6);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_TYPEC_MODE), _LOW);

            break;

        default:
            break;
    }
}

void MenuAdvanceTypeCModeD6(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_TYPEC_MODE_D6);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_TYPEC_MODE_D6, 3);
            if(g_usAdjustValue == 0)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D0);
            }
            else if(g_usAdjustValue == 1)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D1);
            }
            else if(g_usAdjustValue == 2)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D2);
            }
            else if(g_usAdjustValue == 3)
            {
                SET_OSD_STATE(_MENU_ADVANCE_TYPEC_MODE_D6);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_TYPEC_MODE), _LOW);

            break;

        default:
            break;
    }
}


void MenuAdvancePixelShifAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_PIXELSHIFT_STATUS(g_usAdjustValue);
#if(_PIXEL_SHIFT_SUPPORT == _ON)
                UserAdjustPixelOrbiting();
#endif
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_PIXELSHIFT), _LOW);
            }
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_PIXEL_SHIFT_ADJUST, g_usAdjustValue);
            SET_OSD_PIXELSHIFT_STATUS(g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_PIXELSHIFT), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceSdrToHdrAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_SDR_TO_HDR), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_SDR_TO_HDR_ADJUST, g_usAdjustValue);
            SET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_SDR_TO_HDR_FUNCTION == _ON)
            UserAdjustSDRToHDR(GET_OSD_SYSTEM_SELECT_REGION(), _ON);
#endif
            break;


        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_SDR_TO_HDR_FUNCTION == _ON)
                UserAdjustSDRToHDR(GET_OSD_SYSTEM_SELECT_REGION(), _ON);
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_SDR_TO_HDR), _LOW);

            break;

        default:
            break;
    }
}
void MenuAdvanceGlobalDimmingAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_GLOBAL_DIMMING(GET_OSD_GLOBAL_DIMMING());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_GLOBAL_DIMMING), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_GLOBAL_DIMMING_ADJUST, g_usAdjustValue);
            SET_OSD_GLOBAL_DIMMING(g_usAdjustValue);
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
            UserCommonColorGlobalDimmingAdjust();
#endif
            break;


        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_GLOBAL_DIMMING(g_usBackupValue);
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
                UserCommonColorGlobalDimmingAdjust();
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_GLOBAL_DIMMING), _LOW);

            break;

        default:
            break;
    }
}

void MenuAdvanceLocalContrastAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LOCAL_CONTRAST(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_LOCAL_CONTRAST), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_LOCAL_CONTRAST_FUNCTION == _ON)
            // Only _1P_NORMAL_REGION/_FULL_REGION/_DEMO_INSIDE /_2P_PIP_MAIN allow user to adjust OSD
            if(UserCommonColorLocalContrastCheckStatus(GET_OSD_SYSTEM_SELECT_REGION()) == _TRUE)
            {
                OsdDispSliderAndNumber(_OSD_ADVANCE_LOCAL_CONTRAST, g_usAdjustValue);
                SET_OSD_LOCAL_CONTRAST(GET_OSD_SELECT_REGION(), g_usAdjustValue);

                UserAdjustLocalContrast(GET_OSD_SYSTEM_SELECT_REGION());
            }
#endif
            break;


        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LOCAL_CONTRAST(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_LOCAL_CONTRAST(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_LOCAL_CONTRAST_FUNCTION == _ON)
                UserAdjustLocalContrast(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_LOCAL_CONTRAST), _LOW);

            break;

        default:
            break;
    }
}
void MenuAdvanceLocalContrastUser(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_LOCAL_CONTRAST_USER);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_LOCAL_CONTRAST_USER, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_LOCAL_CONTRAST_USER), _LOW);
            break;

        default:
            break;
    }
}
void MenuAdvanceLocalContrastBlending(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_LOCAL_CONTRAST_BLENDING);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_LOCAL_CONTRAST_BLENDING, g_usAdjustValue);
                SET_OSD_LOCAL_CONTRAST_BLENDING(GET_OSD_SELECT_REGION(), g_usAdjustValue);

#if(_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON)
                UserCommonColorLocalContrastToneMappingAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_LOCAL_CONTRAST_BLENDING(GET_OSD_SELECT_REGION(), g_usBackupValue);

#if(_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON)
                    UserCommonColorLocalContrastToneMappingAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_LOCAL_CONTRAST_BLENDING);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceLocalContrastDiffGain(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_LOCAL_CONTRAST_DIFFGAIN);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_LOCAL_CONTRAST_DIFFGAIN, g_usAdjustValue);
                SET_OSD_LOCAL_CONTRAST_DIFFGAIN(GET_OSD_SELECT_REGION(), g_usAdjustValue);

#if(_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON)
                UserCommonColorLocalContrastSharpnessAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_LOCAL_CONTRAST_DIFFGAIN(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON)
                    UserCommonColorLocalContrastSharpnessAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_LOCAL_CONTRAST_DIFFGAIN);
            }
            break;

        default:
            break;
    }
}



void MenuAdvanceHubSwitchAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_USER_USB_HUB_SWITCH_MODE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_HUB_SWITCH), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HUB_SWITCH_ADJUST, g_usAdjustValue);

            break;


        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_USER_USB_HUB_SWITCH_MODE())
            {
                SET_USER_USB_HUB_SWITCH_MODE(g_usBackupValue);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_HUB_SWITCH), _LOW);

            break;

        default:
            break;
    }
}

void MenuAdvanceEagleSightAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST, g_usAdjustValue);
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_EAGLE_SIGHT), _LOW);

            break;

        default:
            break;
    }
}
void MenuAdvanceMbrAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_MBR_ADJUST);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_MBR_ADJUST, g_usAdjustValue);
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_MBR), _LOW);

            break;

        default:
            break;
    }
}
void MenuAdvanceDpAuxlessAlpmAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_DP_AUXLESS_ALPM())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DP_AUXLESS_ALPM), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            OsdDispSliderAndNumber(_MENU_ADVANCE_DP_AUXLESS_ALPM_ADJUST, g_usAdjustValue);
            SET_OSD_DP_AUXLESS_ALPM(g_usAdjustValue);

#if((_DP_SUPPORT == _ON) && (_DP_AUXLESS_ALPM_SUPPORT == _ON))
            UserCommonDpAuxlessAlpmSupportSwitch();
#endif
            break;
        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_DP_AUXLESS_ALPM())
            {
                SET_OSD_DP_AUXLESS_ALPM(g_usBackupValue);

#if((_DP_SUPPORT == _ON) && (_DP_AUXLESS_ALPM_SUPPORT == _ON))
                UserCommonDpAuxlessAlpmSupportSwitch();
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DP_AUXLESS_ALPM), _LOW);

            break;

        default:
            break;
    }
}
void MenuAdvanceDpAdaptiveSyncAdjust(void)
{
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
    EnumInputPort enumInputPort = SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_ADAPTIVE_SYNC())
            {
                SET_OSD_FREE_SYNC_STATUS(g_usAdjustValue);

                SET_OSD_DP_ADAPTIVE_SYNC(g_usAdjustValue);

#if(_FREESYNC_SUPPORT == _ON)
                UserCommonFreeSyncSupportSwitch();
#endif

#if((_DP_SUPPORT == _ON) && (_DP_ADAPTIVESYNC_SUPPORT == _ON))
                UserCommonDpAdaptiveSyncSupportSwitch();
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_ADAPTIVESYNC_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                // Switch Dp Version to 1.4, if AdaptiveSync On & Dp Version < 1.4
                UserAdjustDpVersionForceUpdate(enumInputPort, (bit)UserCommonDpAdaptiveSyncGetSupport(enumInputPort), _DP_VER_1_DOT_4);

                // Switch All DP Port Edid
                UserCommonEdidSwitchDpAllPortEdid();
#endif

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DP_ADAPTIVESYNC), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_DP_ADAPTIVESYNC, g_usAdjustValue);

            SET_OSD_DP_ADAPTIVE_SYNC(g_usAdjustValue);

            break;
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_DP_ADAPTIVE_SYNC(g_usBackupValue);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_DP_ADAPTIVESYNC), _LOW);

            break;

        default:
            break;
    }
}
void MenuAdvancePanelReplayAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PANEL_REPLAY())
            {
                SET_OSD_PANEL_REPLAY(g_usAdjustValue);

#if(_DP_SUPPORT == _ON)
#if(_DP_PR_MODE_SUPPORT == _ON)
                UserCommonDpPRModeSupportSwitch();
#endif
#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_PANEL_REPLAY), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            OsdDispSliderAndNumber(_MENU_ADVANCE_PANEL_REPLAYM_ADJUST, g_usAdjustValue);

            SET_OSD_PANEL_REPLAY(g_usAdjustValue);

            break;
        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PANEL_REPLAY())
            {
                SET_OSD_PANEL_REPLAY(g_usBackupValue);

#if(_DP_SUPPORT == _ON)
#if(_DP_PR_MODE_SUPPORT == _ON)
                UserCommonDpPRModeSupportSwitch();
#endif
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_PANEL_REPLAY), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceSDRPlusAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usAdjustValue != g_usBackupValue)
            {
                SET_OSD_SDR_PLUS(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_SDR_PLUS), _LOW);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_SDR_PLUS_FUNCTION == _ON)
            // Only _1P_NORMAL_REGION/_FULL_REGION/_DEMO_INSIDE /_2P_PIP_MAIN allow user to adjust OSD
            if(UserCommonColorLocalContrastCheckStatus(GET_OSD_SYSTEM_SELECT_REGION()) == _TRUE)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_SDR_PLUS, g_usAdjustValue);
                SET_OSD_SDR_PLUS(GET_OSD_SELECT_REGION(), g_usAdjustValue);
                UserAdjustLocalContrast(GET_OSD_SYSTEM_SELECT_REGION());
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usAdjustValue != g_usBackupValue)
            {
                SET_OSD_SDR_PLUS(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_SDR_PLUS_FUNCTION == _ON)
                UserAdjustLocalContrast(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_SDR_PLUS), _LOW);
            break;

        default:
            break;
    }
}
void MenuAdvanceSDRPlusSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_SDR_PLUS_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_SDR_PLUS_SELECT, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_SDR_PLUS_ADJ), _LOW);
            break;

        default:
            break;
    }
}
void MenuAdvanceSDRPlusSharpAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_SDR_PLUS_SHARP);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_SDR_PLUS_SHARP, g_usAdjustValue);
                SET_OSD_SDR_PLUS_SHARP(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_SDR_PLUS_FUNCTION == _ON)
                UserCommonColorLocalContrastSharpnessAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_SDR_PLUS_SHARP(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_SDR_PLUS_FUNCTION == _ON)
                    UserCommonColorLocalContrastSharpnessAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_SDR_PLUS_SHARP);
            }
            break;

        default:
            break;
    }
}
void MenuAdvanceSDRPlusDarkAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_SDR_PLUS_DARK);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_SDR_PLUS_DARK, g_usAdjustValue);
                SET_OSD_SDR_PLUS_DARK(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_SDR_PLUS_FUNCTION == _ON)
                UserCommonColorLocalContrastToneMappingAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_SDR_PLUS_DARK(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_SDR_PLUS_FUNCTION == _ON)
                    UserCommonColorLocalContrastToneMappingAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_SDR_PLUS_DARK);
            }
            break;

        default:
            break;
    }
}

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
void MenuAdvanceNightSniper(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_NIGHT_SNIPER);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_NIGHT_SNIPER, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_NIGHT_SNIPER), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceNightSniperSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_NIGHT_SNIPER_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                // NightSniper only support 1P/ PIP/PBPLR, Full region
                if(UserCommonColorNightSniperCheckStatus(GET_OSD_SYSTEM_SELECT_REGION()) == _TRUE)
                {
                    OsdDispSliderAndNumber(_MENU_ADVANCE_NIGHT_SNIPER_ADJUST, g_usAdjustValue);
                    SET_OSD_NIGHT_SNIPER(GET_OSD_SELECT_REGION(), g_usAdjustValue);

                    UserAdjustNightSniper(GET_OSD_SYSTEM_SELECT_REGION());
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_NIGHT_SNIPER(GET_OSD_SELECT_REGION(), g_usBackupValue);
                    UserAdjustNightSniper(GET_OSD_SYSTEM_SELECT_REGION());
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_NIGHT_SNIPER_ADJUST);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceNightSniperSaturatuin(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_NIGHT_SNIPER_SATURATION);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_NIGHT_SNIPER_SATURATION, g_usAdjustValue);
                SET_OSD_NIGHT_SNIPER_SAT(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_ICM_FUNCTION == _ON)
                UserCommonColorICMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_NIGHT_SNIPER_SAT(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_ICM_FUNCTION == _ON)
                    UserCommonColorICMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_NIGHT_SNIPER_SATURATION);
            }
            break;

        default:
            break;
    }
}
void MenuAdvanceNightSniperLightness(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_NIGHT_SNIPER_LIGHTNESS);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_NIGHT_SNIPER_LIGHTNESS, g_usAdjustValue);
                SET_OSD_NIGHT_SNIPER_LIGHT(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_ICM_FUNCTION == _ON)
                UserCommonColorICMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_NIGHT_SNIPER_LIGHT(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_ICM_FUNCTION == _ON)
                    UserCommonColorICMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_NIGHT_SNIPER_LIGHTNESS);
            }
            break;

        default:
            break;
    }
}
#endif

void MenuAdvanceAntiAliasingAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_ADVANCE_ANTI_ALIASING);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_ANTI_ALIASING, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_ANTI_ALIASING), _LOW);
            break;

        default:
            break;
    }
}

void MenuAdvanceEnergySaverAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ENERGY_SAVER())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_ENERGY_SAVE), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_ENERGY_SAVER, g_usAdjustValue);
            SET_OSD_ENERGY_SAVER(g_usAdjustValue);
            // add function
#if((_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON) && (_LOCAL_DIMMING_FUNCTION == _ON))
            UserCommonColorLocalDimmingAdjust();
#endif
            break;


        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ENERGY_SAVER())
            {
                SET_OSD_ENERGY_SAVER(g_usBackupValue);
                // add function
#if((_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON) && (_LOCAL_DIMMING_FUNCTION == _ON))
                UserCommonColorLocalDimmingAdjust();
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_ENERGY_SAVE), _LOW);

            break;

        default:
            break;
    }
}

void MenuAudioVolumeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_VOLUME), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME_ADJUST, g_usAdjustValue);
            SET_OSD_VOLUME(g_usAdjustValue);

            if(GET_OSD_VOLUME_MUTE() == _ENABLE)
            {
                SET_OSD_VOLUME_MUTE(_DISABLE);
#if(_AUDIO_SUPPORT == _ON)
                UserAdjustAudioMuteSwitch();
#endif
            }
            else
            {
#if(_AUDIO_SUPPORT == _ON)
                UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME())
            {
                SET_OSD_VOLUME(g_usBackupValue);
#if(_AUDIO_SUPPORT == _ON)
                UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_VOLUME), _LOW);

            break;

        default:
            break;
    }
}

void MenuAudioMuteOnOff(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME_MUTE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_MUTE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_MUTE_ON_OFF, g_usAdjustValue);
            SET_OSD_VOLUME_MUTE(g_usAdjustValue);
#if(_AUDIO_SUPPORT == _ON)
            UserAdjustAudioMuteSwitch();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME_MUTE())
            {
                SET_OSD_VOLUME_MUTE(g_usBackupValue);
#if(_AUDIO_SUPPORT == _ON)
                UserAdjustAudioMuteSwitch();
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_MUTE), _LOW);
            break;

        default:
            break;
    }
}

void MenuAudioStandAlongSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_STAND_ALONE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_STAND_ALONG), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_STAND_ALONG_SELECT, g_usAdjustValue);
            SET_OSD_AUDIO_STAND_ALONE(g_usAdjustValue);
            break;


        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_STAND_ALONE())
            {
                SET_OSD_AUDIO_STAND_ALONE(g_usBackupValue);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_STAND_ALONG), _LOW);
            break;

        default:
            break;
    }
}

void MenuAudioAudioSourceSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_SOURCE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_AUDIO_SOURCE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_AUDIO_SOURCE_SELECT, g_usAdjustValue);
            SET_OSD_AUDIO_SOURCE(g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_SOURCE())
            {
                SET_OSD_AUDIO_SOURCE(g_usBackupValue);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_AUDIO_SOURCE), _LOW);
            break;

        default:
            break;
    }
}

void MenuAudioSoundModeSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_SOUND_MODE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_SOUND_MODE), _LOW);
            break;

        default:
            break;
    }
}
void MenuAudioAudioSelfTestSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
        case _EXIT_KEY_MESSAGE:
#if(_AUDIO_SUPPORT == _ON)
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
            if(UserCommonAudioGetInternalAudioGenEnable(SysRegionGetInputPort(UserInterfaceAudioGetDisplayModeRegion())) == _ENABLE)
            {
                SysAudioInternalGenTestProc(_OFF);
            }
#endif
#endif
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_AUDIO_SELF_TEST), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_AUDIO_SELF_TEST_SELECT, g_usAdjustValue);
#if(_AUDIO_SUPPORT == _ON)
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
            SysAudioInternalGenTestProc(g_usAdjustValue);

#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
            SysAudioDacOutputProc(_ENABLE);
#else
            SysAudioMuteProc(_OFF);
#endif
#endif
#endif
            break;

        default:
            break;
    }
}

void MenuOtherMenuTimeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_TIME_OUT(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_MENU_TIME), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME_ADJUST, g_usAdjustValue);
            UserCommonTimerReactiveTimerEvent(SEC(g_usAdjustValue), _USER_TIMER_EVENT_OSD_DISABLE);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_TIME_OUT(g_usBackupValue);
                UserCommonTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_MENU_TIME), _LOW);
            break;

        default:
            break;
    }
}

void MenuOtherOsdHPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_HPOS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#if(_MRCM_SUPPORT == _ON)
                if(GET_OSD_CROSSHAIR() == _CROSSHAIR_POSITION)
                {
                    UserAdjustMRCM();
                }
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_OSD_HPOS), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS_ADJUST, g_usAdjustValue);
            OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, g_usAdjustValue, GET_OSD_VPOS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_HPOS(g_usBackupValue);
                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_OSD_HPOS), _LOW);

            break;

        default:
            break;
    }
}

void MenuOtherOsdVPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_VPOS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#if(_MRCM_SUPPORT == _ON)
                if(GET_OSD_CROSSHAIR() == _CROSSHAIR_POSITION)
                {
                    UserAdjustMRCM();
                }
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_OSD_VPOS), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS_ADJUST, g_usAdjustValue);
            OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_VPOS(g_usBackupValue);
                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_OSD_VPOS), _LOW);

            break;

        default:
            break;
    }
}

void MenuOtherLanguageAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_LANGUAGE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_LANGUAGE), _HIGH);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_LANGUAGE_ADJUST, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_LANGUAGE), _LOW);
            break;

        default:
            break;
    }
}

void MenuOtherTransparencyAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_TRANSPARENCY_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_TRNASPARENCY), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY_ADJUST, g_usAdjustValue);
            OsdFuncTransparency(g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_TRANSPARENCY_STATUS(g_usBackupValue);
                OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_TRNASPARENCY), _LOW);

            break;

        default:
            break;
    }
}

void MenuOtherRotateAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ROTATE_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            // reDraw
            OsdDispMainMenu();
            SET_OSD_STATE_PREVIOUS(_MENU_OTHER_ITEM);
            SET_OSD_STATE(OsdDispGetUpLayer(_OSD_OTHER_ROTATE));
            SET_OSD_ITEM_INDEX(OsdDispGetOsdItemIdx(_OSD_OTHER_ROTATE));
            OsdDisp2ndMenuReDraw(GET_OSD_STATE(), _HIGH);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_ROTATE_ADJUST, g_usAdjustValue);

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_ROTATE), _LOW);
            break;

        default:
            break;
    }
}

void MenuOtherSelectRegionWidthAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SELECT_REGION_WIDTH())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_BORDER_WIDTH), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp3rdItemAdj(_OSD_OTHER_BORDER_WIDTH, _ON);
            SET_OSD_SELECT_REGION_WIDTH(g_usAdjustValue);

#if(_BORDER_WINDOW_FUNCTION == _ON)
            UserCommonColorBorderWindowAdjust(_DB_APPLY_NO_POLLING);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SELECT_REGION_WIDTH())
            {
                SET_OSD_SELECT_REGION_WIDTH(g_usBackupValue);

#if(_BORDER_WINDOW_FUNCTION == _ON)
                UserCommonColorBorderWindowAdjust(_DB_APPLY_NO_POLLING);
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_BORDER_WIDTH), _LOW);
            break;

        default:
            break;
    }
}

void MenuOtherSelectRegionColorAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SELECT_REGION_COLOR())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_BORDER_COLOR), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp3rdItemAdj(_OSD_OTHER_BORDER_COLOR, _ON);
            if(g_usAdjustValue != GET_OSD_SELECT_REGION_COLOR())
            {
                SET_OSD_SELECT_REGION_COLOR(g_usAdjustValue);

#if(_BORDER_WINDOW_FUNCTION == _ON)
                UserCommonColorBorderWindowAdjust(_DB_APPLY_NO_POLLING);
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SELECT_REGION_COLOR())
            {
                SET_OSD_SELECT_REGION_COLOR(g_usBackupValue);

#if(_BORDER_WINDOW_FUNCTION == _ON)
                UserCommonColorBorderWindowAdjust(_DB_APPLY_NO_POLLING);
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_BORDER_COLOR), _LOW);
            break;

        default:
            break;
    }
}

void MenuOtherCrosshairAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_CROSSHAIR(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#if(_MRCM_SUPPORT == _ON)
                UserAdjustMRCM();
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_CROSSHAIR), _HIGH);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_CROSSHAIR_ADJUST, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_OTHER_CROSSHAIR), _LOW);
            break;

        default:
            break;
    }
}

void MenuColorColortempUserR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_COLOR_TEMP_USER_R);
            break;

        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_R, g_usAdjustValue);
            if(g_usAdjustValue == 0)
            {
                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
            }
            else if(g_usAdjustValue == 1)
            {
                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            }
            else if(g_usAdjustValue == 2)
            {
                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
            }
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_TEMP_USER), _LOW);
            break;

        default:
            break;
    }
}

void MenuColorColortempUserG(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_COLOR_TEMP_USER_G);
            break;
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_G, g_usAdjustValue);
            if(g_usAdjustValue == 0)
            {
                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
            }
            else if(g_usAdjustValue == 1)
            {
                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            }
            else if(g_usAdjustValue == 2)
            {
                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_TEMP_USER), _LOW);
            break;

        default:
            break;
    }
}


void MenuColorColortempUserB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_COLOR_TEMP_USER_B);
            break;
        case _LEFT_KEY_MESSAGE:
        case _RIGHT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_B, g_usAdjustValue);
            if(g_usAdjustValue == 0)
            {
                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
            }
            else if(g_usAdjustValue == 1)
            {
                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            }
            else if(g_usAdjustValue == 2)
            {
                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_TEMP_USER), _LOW);
            break;

        default:
            break;
    }
}


void MenuColorColortempUserAdjustR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_R())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_TEMP_USER_R);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_R, g_usAdjustValue);
            SET_COLOR_TEMP_TYPE_USER_R(g_usAdjustValue);

#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_R())
            {
                SET_COLOR_TEMP_TYPE_USER_R(g_usBackupValue);

#if(_CONTRAST_FUNCTION == _ON)
                UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_TEMP_USER_R);

            break;

        default:
            break;
    }
}

void MenuColorColortempUserAdjustG(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_G())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_TEMP_USER_G);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_G, g_usAdjustValue);
            SET_COLOR_TEMP_TYPE_USER_G(g_usAdjustValue);

#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_G())
            {
                SET_COLOR_TEMP_TYPE_USER_G(g_usBackupValue);

#if(_CONTRAST_FUNCTION == _ON)
                UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_TEMP_USER_G);

            break;

        default:
            break;
    }
}

void MenuColorColortempUserAdjustB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_B())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_TEMP_USER_B);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_B, g_usAdjustValue);
            SET_COLOR_TEMP_TYPE_USER_B(g_usAdjustValue);

#if(_CONTRAST_FUNCTION == _ON)
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_B())
            {
                SET_COLOR_TEMP_TYPE_USER_B(g_usBackupValue);

#if(_CONTRAST_FUNCTION == _ON)
                UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_TEMP_USER_B);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserRHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_R_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserRSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_R_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_Y_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_Y_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserGHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_G_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserGSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_G_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserCHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_C_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserCSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_C_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_B_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_B_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_M_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_EFF_USER_M_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_EFF_USER_R_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_EFFECT_USER), _LOW);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserRHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_R_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_HUE(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_R_HUE);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserRSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_R_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_SAT_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_SATURATION(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_R_SAT);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_Y_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_HUE_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_HUE(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_Y_HUE);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_Y_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_SAT_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_SATURATION(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_Y_SAT);

            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserGHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_G_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_HUE_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_HUE(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_G_HUE);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserGSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_G_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_SAT_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_SATURATION(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_G_SAT);

            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserCHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_C_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_HUE_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_HUE(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_C_HUE);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserCSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_C_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_SAT_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_SATURATION(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_C_SAT);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_B_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_HUE_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_HUE(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_B_HUE);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_B_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_SAT_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_SATURATION(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_B_SAT);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_M_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_HUE_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_HUE(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_M_HUE);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_M_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_SAT_ADJUST, g_usAdjustValue);
            SET_OSD_SIX_COLOR_SATURATION(g_usAdjustValue);
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EFF_USER_M_SAT);

            break;

        default:
            break;
    }
}


#if(_ICM_CHAMELEON_FUNCTION == _ON)
void MenuColorChameleonHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_CHAMELEON_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_CHAMELEON_HUE, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_CHAMELEON_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_CHAMELEON_USER), _LOW);
            break;

        default:
            break;
    }
}

void MenuColorChameleonSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_CHAMELEON_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_CHAMELEON_SAT, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_CHAMELEON_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_CHAMELEON_USER), _LOW);
            break;

        default:
            break;
    }
}

void MenuColorChameleonLightness(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            OsdDisp4thMenuEnter(_MENU_COLOR_CHAMELEON_LIGHTNESS);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_CHAMELEON_LIGHTNESS, g_usAdjustValue);
            SET_OSD_STATE((_MENU_COLOR_CHAMELEON_HUE + g_usAdjustValue));
            break;


        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_CHAMELEON_USER), _LOW);
            break;

        default:
            break;
    }
}

void MenuColorChameleonHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CHAMELEON_HUE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_CHAMELEON_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_CHAMELEON_HUE_ADJUST, g_usAdjustValue);
            SET_OSD_CHAMELEON_HUE(GET_OSD_SELECT_REGION(), g_usAdjustValue);

            // HERE add function
            UserCommonColorICMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CHAMELEON_HUE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_CHAMELEON_HUE(GET_OSD_SELECT_REGION(), g_usBackupValue);
                // HERE add function
                UserCommonColorICMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_CHAMELEON_HUE);

            break;

        default:
            break;
    }
}
void MenuColorChameleonSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CHAMELEON_SAT(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_CHAMELEON_SAT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_CHAMELEON_SAT_ADJUST, g_usAdjustValue);
            SET_OSD_CHAMELEON_SAT(GET_OSD_SELECT_REGION(), g_usAdjustValue);

            // HERE add function
            UserCommonColorICMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CHAMELEON_SAT(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_CHAMELEON_SAT(GET_OSD_SELECT_REGION(), g_usBackupValue);

                // HERE add function
                UserCommonColorICMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_CHAMELEON_SAT);

            break;

        default:
            break;
    }
}
void MenuColorChameleonLightnessAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CHAMELEON_LIGHTNESS(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_CHAMELEON_LIGHTNESS);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_CHAMELEON_LIGHTNESS_ADJUST, g_usAdjustValue);
            SET_OSD_CHAMELEON_LIGHTNESS(GET_OSD_SELECT_REGION(), g_usAdjustValue);

            // HERE add function
            UserCommonColorICMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CHAMELEON_LIGHTNESS(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_CHAMELEON_LIGHTNESS(GET_OSD_SELECT_REGION(), g_usBackupValue);

                // HERE add function
                UserCommonColorICMAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_CHAMELEON_LIGHTNESS);

            break;

        default:
            break;
    }
}
#endif

#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
void MenuColorEyeProtectLowBlueModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_EYEPROTECT_LOWBLUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EYE_PROTECT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EYE_PROTECT_MODE_ADJUST, g_usAdjustValue);
            SET_OSD_EYEPROTECT_LOWBLUE(g_usAdjustValue);
            UserCommonColorLowBlueAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_EYEPROTECT_LOWBLUE())
            {
                SET_OSD_EYEPROTECT_LOWBLUE(g_usBackupValue);
                // HERE add function
                //
            }
            UserCommonColorLowBlueAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EYE_PROTECT_ADJUST);

            break;

        default:
            break;
    }
}
void MenuColorEyeProtectLevelAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_EYEPROTECT_LOWBLUE_LEVEL())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EYE_PROTECT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EYE_PROTECT_LEVEL_ADJUST, g_usAdjustValue);
            SET_OSD_EYEPROTECT_LOWBLUE_LEVEL(g_usAdjustValue);

            UserCommonColorLowBlueAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            // HERE add function
            //
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_EYEPROTECT_LOWBLUE_LEVEL())
            {
                SET_OSD_EYEPROTECT_LOWBLUE_LEVEL(g_usBackupValue);
                // HERE add function
                //
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EYE_PROTECT_ADJUST);

            UserCommonColorLowBlueAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            break;

        default:
            break;
    }
}
void MenuColorEyeProtectNightModeTimeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(_EYEPROTECT_TIME_OFF != GET_OSD_EYEPROTECT_NIGHTMODE_TIME())
            {
                if(GET_OSD_EYEPROTECT_NIGHTMODE_TIME() == _EYEPROTECT_TIME_1MIN)
                {
                    SET_OSD_EYEPROTECT_TIME_MIN_COUNT(0);
                    UserCommonTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_EYE_PROTECT_TIMEOUT);
                }
                else if(GET_OSD_EYEPROTECT_NIGHTMODE_TIME() == _EYEPROTECT_TIME_5MIN)
                {
                    SET_OSD_EYEPROTECT_TIME_MIN_COUNT(0);
                    UserCommonTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_EYE_PROTECT_TIMEOUT);
                }
                else
                {
                    SET_OSD_EYEPROTECT_TIME_MIN_COUNT(0);
                    UserCommonTimerReactiveTimerEvent(SEC(10), _USER_TIMER_EVENT_EYE_PROTECT_TIMEOUT);
                }
                UserCommonColorLowBlueAdjust(GET_OSD_SYSTEM_SELECT_REGION());
            }
            else
            {
                SET_OSD_EYEPROTECT_TIME_MIN_COUNT(0);
                UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_EYE_PROTECT_TIMEOUT);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EYE_PROTECT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EYE_PROTECT_TIME_ADJUST, g_usAdjustValue);
            SET_OSD_EYEPROTECT_NIGHTMODE_TIME(g_usAdjustValue);

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EYE_PROTECT_ADJUST);

            break;

        default:
            break;
    }
}
void MenuColorEyeProtectAmbientSenseAdjustMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_EYEPROTECT_AMBIENTSENSE_MODE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_COLOR_EYE_PROTECT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EYE_PROTECT_TIME_ADJUST, g_usAdjustValue);
            SET_OSD_EYEPROTECT_AMBIENTSENSE_MODE(g_usAdjustValue);
            // HERE add function
            //
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_EYEPROTECT_AMBIENTSENSE_MODE())
            {
                SET_OSD_EYEPROTECT_AMBIENTSENSE_MODE(g_usBackupValue);
                // HERE add function
                //
            }
            OsdDisp3rdMenuReDraw(_MENU_COLOR_EYE_PROTECT_ADJUST);

            break;

        default:
            break;
    }
}
#endif

void MenuAdvanceODGainAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_OD_GAIN(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_OVERDRIVE), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_OD_GAIN_ADJUST, g_usAdjustValue);
            SET_OSD_OD_GAIN(g_usAdjustValue);
#if(_OD_FUNCTION == _ON)
            UserCommonColorODGainAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_OD_GAIN(g_usBackupValue);
#if(_OD_FUNCTION == _ON)
                UserCommonColorODGainAdjust();
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_OVERDRIVE), _LOW);

            break;

        default:
            break;
    }
}

void MenuAdvanceDpD0VersionAdjust(void)
{
#if(((_DP_PR_MODE_SUPPORT == _ON) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)) || (_DP_ADAPTIVESYNC_SUPPORT == _ON))
    EnumInputPort enumInputPort = SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usAdjustValue != GET_OSD_DP_D0_VERSION())
            {
                SET_OSD_DP_D0_VERSION(g_usAdjustValue);
                if((GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D0))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
                // Disable HDR Function, if DP Version Switch to 1.1/1.2
                if((GET_OSD_DP_D0_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_HDR_MODE(_D0_INPUT_PORT) != _HDR10_MODE_OFF))
                {
                    SET_OSD_HDR_MODE(_D0_INPUT_PORT, _HDR10_MODE_OFF);

                    // Switch DP D0 Port Edid
                    UserCommonEdidSwitchDpEdid(_D0_INPUT_PORT);
                }
#endif
#endif
#if(_DSC_DECODER_SUPPORT == _ON)
#if(_DSC_MULTI_DISPLAY_AUTO_SELECT_SUPPORT == _OFF)
                // Disable DSC Mode by Port
                if((GET_OSD_DP_D0_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_DSC_PORT() == _DSC_FROM_D0_PORT))
                {
                    SET_OSD_DSC_PORT(_DSC_FROM_NO_PORT);
                }
#endif
                // Disable DSC Auto when all of DP port switch DP version <= 1.2
                if(((GET_OSD_DP_D0_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_DP_D1_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_DP_D2_VERSION() <= _DP_VER_1_DOT_2)) &&
                   ((GET_OSD_D3_HDMI_VER() < _HDMI_2P1) && (GET_OSD_D4_HDMI_VER() < _HDMI_2P1) && (GET_OSD_D5_HDMI_VER() < _HDMI_2P1)))
                {
                    SET_OSD_1P_DSC_PORT(_DSC_OFF);
                    SET_OSD_DSC_PORT(_DSC_FROM_NO_PORT);
                }
#endif
#if((_DP_SUPPORT == _ON) && (_DP_ADAPTIVESYNC_SUPPORT == _ON))
                // Disable AdaptiveSync by Port
                if((GET_OSD_DP_D0_VERSION() < _DP_VER_1_DOT_4) && (enumInputPort == _D0_INPUT_PORT))
                {
                    SET_OSD_DP_ADAPTIVE_SYNC(_OFF);
                    UserCommonDpAdaptiveSyncSupportSwitch();
                }
#endif
#if((_DP_PR_MODE_SUPPORT == _ON) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
                // Disable PR Mode by Port
                if((GET_OSD_DP_D0_VERSION() < _DP_VER_1_DOT_4) && (enumInputPort == _D0_INPUT_PORT))
                {
                    SET_OSD_PANEL_REPLAY(_OFF);
                    UserCommonDpPRModeSupportSwitch();
                }
#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_SUPPORT == _ON)
                UserCommonDpRxVersionSwitch(_D0_INPUT_PORT, UserInterfaceDpGetVersion(_D0_INPUT_PORT), UserCommonDpGetMSTCapablePort());
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_DP_OPTION_D0);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp4thItemAdj(_ON);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_DP_OPTION_D0);

            break;


        default:
            break;
    }
}

void MenuAdvanceDpD1VersionAdjust(void)
{
#if(((_DP_PR_MODE_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)) || (_DP_ADAPTIVESYNC_SUPPORT == _ON))
    EnumInputPort enumInputPort = SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usAdjustValue != GET_OSD_DP_D1_VERSION())
            {
                SET_OSD_DP_D1_VERSION(g_usAdjustValue);
                if((GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D1))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
                // Disable HDR Function, if DP Version Switch to 1.1/1.2
                if((GET_OSD_DP_D1_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_HDR_MODE(_D1_INPUT_PORT) != _HDR10_MODE_OFF))
                {
                    SET_OSD_HDR_MODE(_D1_INPUT_PORT, _HDR10_MODE_OFF);

                    // Switch DP D1 Port Edid
                    UserCommonEdidSwitchDpEdid(_D1_INPUT_PORT);
                }
#endif
#endif
#if(_DSC_DECODER_SUPPORT == _ON)
#if(_DSC_MULTI_DISPLAY_AUTO_SELECT_SUPPORT == _OFF)
                // Disable DSC Mode by Port
                if((GET_OSD_DP_D1_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_DSC_PORT() == _DSC_FROM_D1_PORT))
                {
                    SET_OSD_DSC_PORT(_DSC_FROM_NO_PORT);
                }
#endif
                // Disable DSC Auto when all of DP port switch DP version <= 1.2
                if(((GET_OSD_DP_D0_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_DP_D1_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_DP_D2_VERSION() <= _DP_VER_1_DOT_2)) &&
                   ((GET_OSD_D1_HDMI_VER() < _HDMI_2P1) && (GET_OSD_D2_HDMI_VER() < _HDMI_2P1) && (GET_OSD_D3_HDMI_VER() < _HDMI_2P1) && (GET_OSD_D4_HDMI_VER() < _HDMI_2P1) && (GET_OSD_D5_HDMI_VER() < _HDMI_2P1)))
                {
                    SET_OSD_1P_DSC_PORT(_DSC_OFF);
                    SET_OSD_DSC_PORT(_DSC_FROM_NO_PORT);
                }
#endif
#if((_DP_SUPPORT == _ON) && (_DP_ADAPTIVESYNC_SUPPORT == _ON))
                // Disable AdaptiveSync by Port
                if((GET_OSD_DP_D1_VERSION() < _DP_VER_1_DOT_4) && (enumInputPort == _D1_INPUT_PORT))
                {
                    SET_OSD_DP_ADAPTIVE_SYNC(_OFF);
                    UserCommonDpAdaptiveSyncSupportSwitch();
                }
#endif
#if((_DP_PR_MODE_SUPPORT == _ON) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
                // Disable PR Mode by Port
                if((GET_OSD_DP_D1_VERSION() < _DP_VER_1_DOT_4) && (enumInputPort == _D1_INPUT_PORT))
                {
                    SET_OSD_PANEL_REPLAY(_OFF);
                    UserCommonDpPRModeSupportSwitch();
                }
#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_SUPPORT == _ON)
                UserCommonDpRxVersionSwitch(_D1_INPUT_PORT, UserInterfaceDpGetVersion(_D1_INPUT_PORT), UserCommonDpGetMSTCapablePort());
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_DP_OPTION_D1);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp4thItemAdj(_ON);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_DP_OPTION_D1);

            break;


        default:
            break;
    }
}

void MenuAdvanceDpD2VersionAdjust(void)
{
#if(((_DP_PR_MODE_SUPPORT == _ON) && (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)) || (_DP_ADAPTIVESYNC_SUPPORT == _ON))
    EnumInputPort enumInputPort = SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usAdjustValue != GET_OSD_DP_D2_VERSION())
            {
                SET_OSD_DP_D2_VERSION(g_usAdjustValue);
                if((GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D2))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
                // Disable HDR Function, if DP Version Switch to 1.1/1.2
                if((GET_OSD_DP_D2_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_HDR_MODE(_D2_INPUT_PORT) != _HDR10_MODE_OFF))
                {
                    SET_OSD_HDR_MODE(_D2_INPUT_PORT, _HDR10_MODE_OFF);

                    // Switch DP D2 Port Edid
                    UserCommonEdidSwitchDpEdid(_D2_INPUT_PORT);
                }
#endif
#endif
#if(_DSC_DECODER_SUPPORT == _ON)
#if(_DSC_MULTI_DISPLAY_AUTO_SELECT_SUPPORT == _OFF)
                // Disable DSC Mode by Port
                if((GET_OSD_DP_D2_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_DSC_PORT() == _DSC_FROM_D2_PORT))
                {
                    SET_OSD_DSC_PORT(_DSC_FROM_NO_PORT);
                }
#endif
                // Disable DSC Auto when all of DP port switch DP version <= 1.2
                if(((GET_OSD_DP_D0_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_DP_D1_VERSION() <= _DP_VER_1_DOT_2) && (GET_OSD_DP_D2_VERSION() <= _DP_VER_1_DOT_2)) &&
                   ((GET_OSD_D1_HDMI_VER() < _HDMI_2P1) && (GET_OSD_D2_HDMI_VER() < _HDMI_2P1) && (GET_OSD_D3_HDMI_VER() < _HDMI_2P1) && (GET_OSD_D4_HDMI_VER() < _HDMI_2P1) && (GET_OSD_D5_HDMI_VER() < _HDMI_2P1)))
                {
                    SET_OSD_1P_DSC_PORT(_DSC_OFF);
                    SET_OSD_DSC_PORT(_DSC_FROM_NO_PORT);
                }
#endif
#if((_DP_SUPPORT == _ON) && (_DP_ADAPTIVESYNC_SUPPORT == _ON))
                // Disable AdaptiveSync by Port
                if((GET_OSD_DP_D2_VERSION() < _DP_VER_1_DOT_4) && (enumInputPort == _D2_INPUT_PORT))
                {
                    SET_OSD_DP_ADAPTIVE_SYNC(_OFF);
                    UserCommonDpAdaptiveSyncSupportSwitch();
                }
#endif
#if((_DP_PR_MODE_SUPPORT == _ON) && (_D2_INPUT_PORT_TYPE == _D2_DP_PORT))
                // Disable PR Mode by Port
                if((GET_OSD_DP_D2_VERSION() < _DP_VER_1_DOT_4) && (enumInputPort == _D2_INPUT_PORT))
                {
                    SET_OSD_PANEL_REPLAY(_OFF);
                    UserCommonDpPRModeSupportSwitch();
                }
#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_SUPPORT == _ON)
                UserCommonDpRxVersionSwitch(_D2_INPUT_PORT, UserInterfaceDpGetVersion(_D2_INPUT_PORT), UserCommonDpGetMSTCapablePort());
#endif
            }
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_DP_OPTION_D2);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp4thItemAdj(_ON);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_DP_OPTION_D2);

            break;


        default:
            break;
    }
}

void MenuAdvanceDpD6VersionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usAdjustValue != GET_OSD_DP_D6_VERSION())
            {
                SET_OSD_DP_D6_VERSION(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_DP_OPTION_D6);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp4thItemAdj(_ON);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_DP_OPTION_D6);

            break;

        default:
            break;
    }
}


void MenuAdvanceD0TypeCModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D0_USB_HUB_SUPPORT == _ON)
            if(g_usAdjustValue != GET_OSD_D0_TYPE_C_U3_MODE())
            {
                SET_OSD_D0_TYPE_C_U3_MODE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                SysUsbTypeCRxSetCapabilityChangeFlag(_D0_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_CAP_CHG);
            }
#endif
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_TYPEC_MODE_D0);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp4thItemAdj(_ON);
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_TYPEC_MODE_D0);
            break;

        default:
            break;
    }
}

void MenuAdvanceD1TypeCModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D1_USB_HUB_SUPPORT == _ON)
            if(g_usAdjustValue != GET_OSD_D1_TYPE_C_U3_MODE())
            {
                SET_OSD_D1_TYPE_C_U3_MODE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                SysUsbTypeCRxSetCapabilityChangeFlag(_D1_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_CAP_CHG);
            }
#endif
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_TYPEC_MODE_D1);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp4thItemAdj(_ON);
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_TYPEC_MODE_D1);
            break;

        default:
            break;
    }
}

void MenuAdvanceD2TypeCModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D2_USB_HUB_SUPPORT == _ON)
            if(g_usAdjustValue != GET_OSD_D2_TYPE_C_U3_MODE())
            {
                SET_OSD_D2_TYPE_C_U3_MODE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                SysUsbTypeCRxSetCapabilityChangeFlag(_D2_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_CAP_CHG);
            }
#endif
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_TYPEC_MODE_D2);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp4thItemAdj(_ON);
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_TYPEC_MODE_D2);
            break;

        default:
            break;
    }
}

void MenuAdvanceD6TypeCModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(0)
            if(g_usAdjustValue != GET_OSD_D6_TYPE_C_U3_MODE())
            {
                SET_OSD_D6_TYPE_C_U3_MODE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
#endif
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_TYPEC_MODE_D6);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDisp4thItemAdj(_ON);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_TYPEC_MODE_D6);
            break;

        default:
            break;
    }
}



void MenuAdvanceLDOnOffAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_LOCAL_DIMMING(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_LOCALDIMMING), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_LD_ONOFF_ADJUST, g_usAdjustValue);
            SET_OSD_LOCAL_DIMMING(g_usAdjustValue);
#if(_LOCAL_DIMMING_FUNCTION == _ON)
            UserCommonColorLocalDimmingAdjust();
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_LOCAL_DIMMING(g_usBackupValue);
#if(_LOCAL_DIMMING_FUNCTION == _ON)
                UserCommonColorLocalDimmingAdjust();
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_LOCALDIMMING), _LOW);
            break;

        default:
            break;
    }
}


void MenuAdvanceLDSmoothAdjAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LD_ADJ())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_LOCALDIMMING_USER), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_LD_SMOOTH_ADJ_ADJUST, g_usAdjustValue);
            SET_OSD_LD_ADJ(g_usAdjustValue);
#if(_LOCAL_DIMMING_FUNCTION == _ON)
            UserCommonColorLocalDimmingAdjust();
#endif
            break;


        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LD_ADJ())
            {
                SET_OSD_LD_ADJ(g_usBackupValue);
#if(_LOCAL_DIMMING_FUNCTION == _ON)
                UserCommonColorLocalDimmingAdjust();
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_LOCALDIMMING_USER), _LOW);

            break;

        default:
            break;
    }
}

bit MenuHdrEdidSwitchCheck(EnumHDR10ModeDef enumHDR10ModeDefBefore, EnumHDR10ModeDef enumHDR10ModeDefAfter)
{
    if(enumHDR10ModeDefBefore != enumHDR10ModeDefAfter)
    {
        if((enumHDR10ModeDefBefore == _HDR10_MODE_OFF) || (enumHDR10ModeDefAfter == _HDR10_MODE_OFF))
        {
            return _TRUE;
        }
#if(_HLG_SUPPORT == _ON)
        if(((enumHDR10ModeDefBefore == _HDR10_MODE_AUTO) || (enumHDR10ModeDefBefore == _HDR10_MODE_FORCE_2084)) && ((enumHDR10ModeDefAfter == _HDR10_HLG_MODE_AUTO) || (enumHDR10ModeDefAfter == _HDR10_HLG_MODE_FORCE_HLG)))
        {
            return _TRUE;
        }
        if(((enumHDR10ModeDefBefore == _HDR10_HLG_MODE_AUTO) || (enumHDR10ModeDefBefore == _HDR10_HLG_MODE_FORCE_HLG)) && ((enumHDR10ModeDefAfter == _HDR10_MODE_AUTO) || (enumHDR10ModeDefAfter == _HDR10_MODE_FORCE_2084)))
        {
            return _TRUE;
        }
#endif
    }
    return _FALSE;
}

void MenuHdrModeAdjust(void)
{
    EnumInputPort enumInputPort = SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION());

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_MODE(enumInputPort))
            {
                if(MenuHdrEdidSwitchCheck(g_usBackupValue, GET_OSD_HDR_MODE(enumInputPort)) == _TRUE)
                {
#if(_EDID_HDR10_AUTO_SWITCH == _ON)
#if((_HDMI_MULTI_EDID_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
                    // Switch All HDMI Port Edid
                    UserCommonEdidSwitchHdmiAllPortEdid();
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
                    // Switch Dp Version to 1.4, if HDR On
                    UserAdjustHdrCheckDpVersion(enumInputPort, GET_OSD_HDR_MODE(enumInputPort));

                    // Switch All DP Port Edid
                    UserCommonEdidSwitchDpAllPortEdid();

#if(_DP_HDR_VENDOR_SUPPORT != _DP_HDR_VENDOR_SUPPORT_NONE)
                    // Switch All DP Port Capability of HDR
                    UserCommonDpHdrSupportSwitch();
#endif
#endif
#endif
                }
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
                // Turn off Dolby when HDR is set to off
                if(GET_OSD_HDR_MODE(enumInputPort) == _HDR10_MODE_OFF)
                {
                    SET_OSD_DVISION(enumInputPort, _OFF);
                    UserCommonColorDMOSDSupportSwitch(enumInputPort);
                }
#endif
#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                RTDNVRamSaveOsdInputPortData(UserAdjustGetSelectRegionPort());
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_MODE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_MODE_ADJUST, g_usAdjustValue);
            SET_OSD_HDR_MODE(enumInputPort, g_usAdjustValue);

#if(_ULTRA_HDR_SUPPORT == _ON)
            UserCommonColorHDRAdjust(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_MODE(enumInputPort))
            {
                SET_OSD_HDR_MODE(enumInputPort, g_usBackupValue);

#if(_ULTRA_HDR_SUPPORT == _ON)
                UserCommonColorHDRAdjust(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_MODE), _LOW);

            break;

        default:
            break;
    }
}



void MenuHdrDarkEnhanceOnOffAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_REGION_DARK_ENHANCE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_DARK_ENHANCE), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF_ADJUST, g_usAdjustValue);
            SET_OSD_REGION_DARK_ENHANCE(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_ULTRA_HDR_SUPPORT == _ON)
            UserCommonColorHDRAdjust(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_REGION_DARK_ENHANCE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_REGION_DARK_ENHANCE(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_ULTRA_HDR_SUPPORT == _ON)
                UserCommonColorHDRAdjust(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_DARK_ENHANCE), _LOW);

            break;

        default:
            break;
    }
}
void MenuHdrSharpnessOnOffAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_REGION_HDR_SHARPNESS(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_SHARP_ENHANCE), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_SHARPNESS_ONOFF_ADJUST, g_usAdjustValue);
            SET_OSD_REGION_HDR_SHARPNESS(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_ULTRA_VIVID_FUNCTION == _ON)
            UserCommonColorUltraVividAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif // End of #if(_ULTRA_VIVID_SUPPORT == _ON)

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_REGION_HDR_SHARPNESS(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_REGION_HDR_SHARPNESS(GET_OSD_SELECT_REGION(), g_usBackupValue);

#if(_ULTRA_VIVID_FUNCTION == _ON)
                UserCommonColorUltraVividAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif // End of #if(_ULTRA_VIVID_SUPPORT == _ON)
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_SHARP_ENHANCE), _LOW);

            break;

        default:
            break;
    }
}

void MenuHdrContrastAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_REGION_HDR_CONTRAST(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_CONTRAST), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_CONTRAST_ADJUST, g_usAdjustValue);
            SET_OSD_REGION_HDR_CONTRAST(GET_OSD_SELECT_REGION(), g_usAdjustValue);

#if((_CONTRAST_FUNCTION == _ON) && (_HDR10_SUPPORT == _ON))
            UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_REGION_HDR_CONTRAST(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_REGION_HDR_CONTRAST(GET_OSD_SELECT_REGION(), g_usBackupValue);

#if((_CONTRAST_FUNCTION == _ON) && (_HDR10_SUPPORT == _ON))
                UserCommonColorContrastAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_CONTRAST), _LOW);

            break;

        default:
            break;
    }
}
void MenuHdrColorEnhanceAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_COLOR_ENHANCE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_COLOR_ENHANCE), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_COLOR_ENHANCE_ADJUST, g_usAdjustValue);
            SET_OSD_HDR_COLOR_ENHANCE(GET_OSD_SELECT_REGION(), g_usAdjustValue);

#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
            UserCommonColorHDRAdjustHDR10ColorEnhance(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_COLOR_ENHANCE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_HDR_COLOR_ENHANCE(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
                UserCommonColorHDRAdjustHDR10ColorEnhance(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_COLOR_ENHANCE), _LOW);
            break;

        default:
            break;
    }
}

void MenuHdrLightEnhanceAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_LIGHT_ENHANCE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_LIGHT_ENHANCE), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_LIGHT_ENHANCE_ADJUST, g_usAdjustValue);
            SET_OSD_HDR_LIGHT_ENHANCE(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
            UserCommonColorHDRAdjustHDR10LightEnhance(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_LIGHT_ENHANCE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_HDR_LIGHT_ENHANCE(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
                UserCommonColorHDRAdjustHDR10LightEnhance(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING);
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_LIGHT_ENHANCE), _LOW);
            break;

        default:
            break;
    }
}

void MenuHdrHlgOotfAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_HLG_OOTF(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_HLG_OOTF), _LOW);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_HLG_OOTF_ADJUST, g_usAdjustValue);
            SET_OSD_HDR_HLG_OOTF(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_HLG_SUPPORT == _ON)
            // ;reserve
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HDR_HLG_OOTF(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_HDR_HLG_OOTF(GET_OSD_SELECT_REGION(), g_usBackupValue);
#if(_HLG_SUPPORT == _ON)
                // ;reserve
#endif
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_HLG_OOTF), _LOW);
            break;

        default:
            break;
    }
}

void MenuSource_Item(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDisp2ndMenuEnter(GET_OSD_ITEM_INDEX(), _MENU_INPUT_ITEM);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(OsdDisp2ndInputSelectbyKey() == _FALSE)
            {
                break;
            }

            OsdDisp2ndMenuCursor(GET_OSD_ITEM_INDEX());
            break;

        case _EXIT_KEY_MESSAGE:

            if((SysModeGetModeState() != _MODE_STATUS_DISPLAY_CHECK) ||
               (SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE))
            {
                OsdDispDisableOsd();
            }
            else
            {
                SET_OSD_ITEM_INDEX(OsdDisp1stMenuGetIdx(_OSD_MENU_INPUT));
                OsdDisp1stMenuRedraw();
                SET_OSD_STATE(_MENU_MAIN);
            }
            break;

        default:
            break;
    }
    // OsdFuncShowSourceMenuCheck();
}

void MenuAdvanceEagleSightFunctionAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_EAGLE_SIGHT_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_EAGLE_SIGHT_FUNCTION_ADJUST, g_usAdjustValue);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                SET_EAGLE_SIGHT_STATUS(g_usAdjustValue);
                UserCommonDisplayEagleSightAdjust(_EAGLE_SIGHT_ENABLE);
#if(_PIXEL_SHIFT_SUPPORT == _ON)
                UserAdjustPixelOrbitingActiveResume();
                OsdDisplaySetPixelOrbitingCapability();
#endif

#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceEagleSightRegionAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_SELECT_REGION(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_EAGLE_SIGHT_REGION_ADJUST, g_usAdjustValue);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceEagleSightTransparencyAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_EAGLE_SIGHT_TRANSPARENCY(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_EAGLE_SIGHT_TRANSPARENT_ADJUST, g_usAdjustValue);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                SET_EAGLE_SIGHT_TRANSPARENCY(g_usAdjustValue);
                UserCommonDisplayEagleSightAdjust(_EAGLE_SIGHT_TRANSPARENCY);
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceEagleSightZoomAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_EAGLE_SIGHT_ZOOM(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_EAGLE_SIGHT_ZOOM_ADJUST, g_usAdjustValue);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                SET_EAGLE_SIGHT_ZOOM(g_usAdjustValue);
                UserCommonDisplayEagleSightAdjust(_EAGLE_SIGHT_RATIO);
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceEagleSightCapPositionAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_EAGLE_SIGHT_CAP_POSITION(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_EAGLE_SIGHT_CAP_POSITION_ADJUST, g_usAdjustValue);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                SET_EAGLE_SIGHT_CAP_POSITION(g_usAdjustValue);
                UserCommonDisplayEagleSightAdjust(_EAGLE_SIGHT_CAP_POSITION);
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceEagleSightDispPositionAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_EAGLE_SIGHT_DISP_POSITION(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_EAGLE_SIGHT_DISP_POSITION_ADJUST, g_usAdjustValue);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                SET_EAGLE_SIGHT_DISP_POSITION(g_usAdjustValue);
                UserCommonDisplayEagleSightAdjust(_EAGLE_SIGHT_DISP_POSITION);
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceEagleSightBorderAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_EAGLE_SIGHT_BORDER(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_EAGLE_SIGHT_BORDER_ADJUST, g_usAdjustValue);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                SET_EAGLE_SIGHT_BORDER(g_usAdjustValue);
                UserCommonDisplayEagleSightAdjust(_EAGLE_SIGHT_BORDER);
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    SET_EAGLE_SIGHT_BORDER(g_usBackupValue);
                    UserCommonDisplayEagleSightAdjust(_EAGLE_SIGHT_BORDER);
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            }
            break;

        default:
            break;
    }
}
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
void MenuAdvanceEagleSightCircleWinAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_EAGLE_SIGHT_CIRCLE_WIN_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_EAGLE_SIGHT_CIRCLEWIN_ADJUST, g_usAdjustValue);
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                SET_EAGLE_SIGHT_CIRCLE_WIN_STATUS(g_usAdjustValue);
                UserCommonDisplayEagleSightAdjust(_EAGLE_SIGHT_CIRCLE_WIN);
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    SET_EAGLE_SIGHT_CIRCLE_WIN_STATUS(g_usAdjustValue);
                    UserCommonDisplayEagleSightAdjust(_EAGLE_SIGHT_CIRCLE_WIN);
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_EAGLE_SIGHT_ADJUST);
            }
            break;

        default:
            break;
    }
}
#endif

void MenuAdvanceMbrModeAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_MBR_MODE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_MBR_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_MBR_MODE_ADJUST, g_usAdjustValue);
                SET_OSD_MBR_MODE(g_usAdjustValue);

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
                switch(SysModeGetDisplayMode())
                {
                    case _DISPLAY_MODE_1P:
                        // Reset to display setting or adjust backlight directly
                        // Caustion!! RTK_Adv_MBR requires "reset to display setting" to be effective
#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _ON)
                        UserCommonDisplayMbrStrobeBacklightCtrl(_LIGHT_CONTROL_ON);
#else
                        UserCommonPowerPanelAction(_BACKLIGHT_OFF);
                        SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
                        break;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                        // Reset to display setting or adjust backlight directly
                        // Caustion!! RTK_Adv_MBR requires "reset to display initial" to be effective
#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _ON)
                        UserCommonDisplayMbrStrobeBacklightCtrl(_LIGHT_CONTROL_ON);
#else
                        UserCommonPowerPanelAction(_BACKLIGHT_OFF);
                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
#endif
                        break;
#endif
                    default:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP:
#endif
                        break;
                }

#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
                UserCommonDisplayMbrBlackFrameInsertAdjust();
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_MBR_MODE(g_usBackupValue);

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
                    switch(SysModeGetDisplayMode())
                    {
                        case _DISPLAY_MODE_1P:
                            // Reset to display setting or adjust backlight directly
                            // Caustion!! RTK_Adv_MBR requires "reset to display setting" to be effective
#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _ON)
                            UserCommonDisplayMbrStrobeBacklightCtrl(_LIGHT_CONTROL_ON);
#else
                            UserCommonPowerPanelAction(_BACKLIGHT_OFF);
                            SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
                            break;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                            // Reset to display setting or adjust backlight directly
                            // Caustion!! RTK_Adv_MBR requires "reset to display initial" to be effective
#if(_MOTION_BLUR_REDUCTION_MODE_SWITCH_NO_MUTE_SUPPORT == _ON)
                            UserCommonDisplayMbrStrobeBacklightCtrl(_LIGHT_CONTROL_ON);
#else
                            UserCommonPowerPanelAction(_BACKLIGHT_OFF);
                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
#endif
                            break;
#endif
                        default:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                        case _DISPLAY_MODE_2P_PIP:
#endif
                            break;
                    }

#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
                    UserCommonDisplayMbrBlackFrameInsertAdjust();
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_MBR_ADJUST);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceMbrDutyAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_MBR_DUTY(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_MBR_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_MBR_DUTY_ADJUST, g_usAdjustValue);
                SET_OSD_MBR_DUTY(g_usAdjustValue);
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
                if(GET_OSD_MBR_MODE() == _OSD_MBR_USERMODE)
                {
                    UserInterfaceDisplayMbrBacklightAdjust(_BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR, _LIGHT_CONTROL_ON, GET_MBR_DVTOTAL());
                }
                else if(GET_OSD_MBR_MODE() == _OSD_MBR_RTK_ADV)
                {
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
                    UserCommonDisplayMbrAdvAdjust(GET_OSD_MBR_DUTY(), GET_OSD_MBR_POSITION(), _LIGHT_CONTROL_ON);
#endif
                }
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_MBR_DUTY(g_usAdjustValue);
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
                    if(GET_OSD_MBR_MODE() == _OSD_MBR_USERMODE)
                    {
                        UserInterfaceDisplayMbrBacklightAdjust(_BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR, _LIGHT_CONTROL_ON, GET_MBR_DVTOTAL());
                    }
                    else if(GET_OSD_MBR_MODE() == _OSD_MBR_RTK_ADV)
                    {
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
                        UserCommonDisplayMbrAdvAdjust(GET_OSD_MBR_DUTY(), GET_OSD_MBR_POSITION(), _LIGHT_CONTROL_ON);
#endif
                    }
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_MBR_ADJUST);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceMbrPositionAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_MBR_POSITION(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_MBR_ADJUST);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_MBR_POSITION_ADJUST, g_usAdjustValue);
                SET_OSD_MBR_POSITION(g_usAdjustValue);
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
                if(GET_OSD_MBR_MODE() == _OSD_MBR_USERMODE)
                {
                    UserInterfaceDisplayMbrBacklightAdjust(_BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR, _LIGHT_CONTROL_ON, GET_MBR_DVTOTAL());
                }
                else if(GET_OSD_MBR_MODE() == _OSD_MBR_RTK_ADV)
                {
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
                    UserCommonDisplayMbrAdvAdjust(GET_OSD_MBR_DUTY(), GET_OSD_MBR_POSITION(), _LIGHT_CONTROL_ON);
#endif
                }
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_OSD_MBR_POSITION(g_usAdjustValue);
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
                    if(GET_OSD_MBR_MODE() == _OSD_MBR_USERMODE)
                    {
                        UserInterfaceDisplayMbrBacklightAdjust(_BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR, _LIGHT_CONTROL_ON, GET_MBR_DVTOTAL());
                    }
                    else if(GET_OSD_MBR_MODE() == _OSD_MBR_RTK_ADV)
                    {
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
                        UserCommonDisplayMbrAdvAdjust(GET_OSD_MBR_DUTY(), GET_OSD_MBR_POSITION(), _LIGHT_CONTROL_ON);
#endif
                    }
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_MBR_ADJUST);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceAntiAliasingModeAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_ANTI_ALIASING_MODE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_ANTI_ALIASING);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_ANTI_ALIASING_MODE_ADJ, g_usAdjustValue);
                SET_ANTI_ALIASING_MODE(g_usAdjustValue);
#if(_COLOR_IP_ANTI_ALIASING == _ON)
                UserCommonColorAntiAliasingAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_ANTI_ALIASING_MODE(g_usBackupValue);
#if(_COLOR_IP_ANTI_ALIASING == _ON)
                    UserCommonColorAntiAliasingAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_ANTI_ALIASING);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceAntiAliasingLevelAdj(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_ANTI_ALIASING_LEVEL(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp3rdMenuReDraw(_MENU_ADVANCE_ANTI_ALIASING);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_ANTI_ALIASING_LEVEL_ADJ, g_usAdjustValue);
                SET_ANTI_ALIASING_LEVEL(g_usAdjustValue);
#if(_COLOR_IP_ANTI_ALIASING == _ON)
                UserCommonColorAntiAliasingAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != g_usAdjustValue)
                {
                    SET_ANTI_ALIASING_LEVEL(g_usBackupValue);
#if(_COLOR_IP_ANTI_ALIASING == _ON)
                    UserCommonColorAntiAliasingAdjust(GET_OSD_SYSTEM_SELECT_REGION());
#endif
                }
                OsdDisp3rdMenuReDraw(_MENU_ADVANCE_ANTI_ALIASING);
            }
            break;

        default:
            break;
    }
}

void MenuSource_1P_ADJ(void)
{
    WORD usAdjustValue = _OSD_INPUT_A0;
    usAdjustValue = usAdjustValue;

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                switch(g_usAdjustValue)
                {
                    case _OSD_INPUT_A0:
                    case _OSD_INPUT_D0:
                    case _OSD_INPUT_D1:
                    case _OSD_INPUT_D2:
                    case _OSD_INPUT_D3:
                    case _OSD_INPUT_D4:
                    case _OSD_INPUT_D5:
                    case _OSD_INPUT_D6:
                    case _OSD_INPUT_D7:
                    case _OSD_INPUT_D8:
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
                    case _OSD_INPUT_D9:
                    case _OSD_INPUT_D9_D0:
                    case _OSD_INPUT_D9_D1:
                    case _OSD_INPUT_D9_D2:
#endif

                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_1P_INPUT_SOURCE(g_usAdjustValue);

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
                        usAdjustValue = UserAdjustGetInputPortValue(_REGION_INDEX_0);
#else
                        usAdjustValue = g_usAdjustValue;
#endif

                        switch(GET_OSD_DISPLAY_MODE())
                        {
                            case _OSD_DM_1P:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_1P, g_usAdjustValue);
                                break;
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_LR:
                                if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
                                {
                                    UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_L_LARGE_LEFT, usAdjustValue);
                                }
                                else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
                                {
                                    UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_R_LARGE_LEFT, usAdjustValue);
                                }
                                else
                                {
                                    UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_LEFT, usAdjustValue);
                                }

                                break;
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_TB:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_TOP, usAdjustValue);
                                break;
#endif
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_PIP:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_PIP_MAIN, usAdjustValue);
                                break;
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_3P_FLAG:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_FLAG_MAIN, g_usAdjustValue);
                                break;
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_3P_SKEW_L:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_L_MAIN, g_usAdjustValue);
                                break;
                            case _OSD_DM_3P_SKEW_R:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_R_MAIN, g_usAdjustValue);
                                break;
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_3P_SKEW_T:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_T_MAIN, g_usAdjustValue);
                                break;
                            case _OSD_DM_3P_SKEW_B:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_B_MAIN, g_usAdjustValue);
                                break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_4P:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_LT, g_usAdjustValue);
                                break;
#endif
                            default:
                                break;
                        }

                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    case _OSD_INPUT_AUTO: // Auto
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        OsdFuncSetAutoSearchPort(_REGION_INDEX_0); // replace "SET_OSD_1P_INPUT_SOURCE(g_usAdjustValue);"
                        SysSourceSetMultiAutoSearchTarget(UserCommonSourceGetAutoSearchTarget());
                        OsdDisp2ndMenuReDraw(_MENU_INPUT_ITEM, _LOW);
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        return;
                        break;

                    default:
                        break;
                }

#if(_DP_MST_SUPPORT == _ON)
                UserCommonDpMstRxCapablePortSwitch(UserCommonDpGetMSTCapablePort());
                RTDNVRamSaveOsdUserData();

#endif
            }

            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                OsdDisp2ndMenuReDraw(_MENU_INPUT_ITEM, _LOW);
            }
            else
            {
                OsdDispDisableOsd();
            }

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            OsdDispSliderAndNumber(_MENU_INPUT_SOURCE_1P_ADJ, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(_MENU_INPUT_ITEM, _LOW);

            break;

        default:
            break;
    }
}

void MenuSource_2P_ADJ(void)
{
    WORD usAdjustValue = _OSD_INPUT_A0;
    usAdjustValue = usAdjustValue;

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_MULTI_DISPLAY_MAX >= 0x02)
            if(g_usBackupValue != g_usAdjustValue)
            {
                switch(g_usAdjustValue)
                {
                    case _OSD_INPUT_A0:
                    case _OSD_INPUT_D0:
                    case _OSD_INPUT_D1:
                    case _OSD_INPUT_D2:
                    case _OSD_INPUT_D3:
                    case _OSD_INPUT_D4:
                    case _OSD_INPUT_D5:
                    case _OSD_INPUT_D6:
                    case _OSD_INPUT_D7:
                    case _OSD_INPUT_D8:
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
                    case _OSD_INPUT_D9:
                    case _OSD_INPUT_D9_D0:
                    case _OSD_INPUT_D9_D1:
                    case _OSD_INPUT_D9_D2:
#endif

                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_2P_INPUT_SOURCE(g_usAdjustValue);

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
                        usAdjustValue = UserAdjustGetInputPortValue(_REGION_INDEX_1);
#else
                        usAdjustValue = g_usAdjustValue;
#endif

                        switch(GET_OSD_DISPLAY_MODE())
                        {
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_LR:
                                if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
                                {
                                    UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT, usAdjustValue);
                                }
                                else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
                                {
                                    UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT, usAdjustValue);
                                }
                                else
                                {
                                    UserAdjustRegionInputPort(_DISPLAY_RGN_PBP_LR_EQUAL_RIGHT, usAdjustValue);
                                }
                                break;
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_TB:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_BOTTOM, usAdjustValue);
                                break;
#endif
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_PIP:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_PIP_SUB, usAdjustValue);
                                break;
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_3P_FLAG:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_FLAG_LEFT, g_usAdjustValue);
                                break;
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_3P_SKEW_L:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_L_TOP, g_usAdjustValue);
                                break;
                            case _OSD_DM_3P_SKEW_R:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_R_TOP, g_usAdjustValue);
                                break;
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_3P_SKEW_T:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_T_LEFT, g_usAdjustValue);
                                break;
                            case _OSD_DM_3P_SKEW_B:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_B_LEFT, g_usAdjustValue);
                                break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_4P:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_LB, g_usAdjustValue);
                                break;
#endif
                            default:
                                break;
                        }

                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    case _OSD_INPUT_AUTO: // Auto
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        OsdFuncSetAutoSearchPort(_REGION_INDEX_1); // replace "SET_OSD_2P_INPUT_SOURCE(g_usAdjustValue);"
                        SysSourceSetMultiAutoSearchTarget(UserCommonSourceGetAutoSearchTarget());
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    default:
                        break;
                }
            }
#endif // End of #if(_MULTI_DISPLAY_MAX >= 0x02)

            OsdDisp2ndMenuReDraw(_MENU_INPUT_ITEM, _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_INPUT_SOURCE_2P_ADJ, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(_MENU_INPUT_ITEM, _LOW);

            break;

        default:
            break;
    }
}

void MenuSource_3P_ADJ(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if((_3P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
            if(g_usBackupValue != g_usAdjustValue)
            {
                switch(g_usAdjustValue)
                {
                    case _OSD_INPUT_A0:
                    case _OSD_INPUT_D0:
                    case _OSD_INPUT_D1:
                    case _OSD_INPUT_D2:
                    case _OSD_INPUT_D3:
                    case _OSD_INPUT_D4:
                    case _OSD_INPUT_D5:
                    case _OSD_INPUT_D6:
                    case _OSD_INPUT_D7:
                    case _OSD_INPUT_D8:
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_3P_INPUT_SOURCE(g_usAdjustValue);
                        switch(GET_OSD_DISPLAY_MODE())
                        {
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_3P_FLAG:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_FLAG_RIGHT, g_usAdjustValue);
                                break;
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_3P_SKEW_L:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_L_BOTTOM, g_usAdjustValue);
                                break;
                            case _OSD_DM_3P_SKEW_R:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_R_BOTTOM, g_usAdjustValue);
                                break;
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_3P_SKEW_T:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_T_RIGHT, g_usAdjustValue);
                                break;
                            case _OSD_DM_3P_SKEW_B:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SKEW_B_RIGHT, g_usAdjustValue);
                                break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_4P:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_RT, g_usAdjustValue);
                                break;
#endif
                            default:
                                break;
                        }
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    case _OSD_INPUT_AUTO: // Auto
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        OsdFuncSetAutoSearchPort(_REGION_INDEX_2); // replace "SET_OSD_3P_INPUT_SOURCE(g_usAdjustValue);"
                        SysSourceSetMultiAutoSearchTarget(UserCommonSourceGetAutoSearchTarget());
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    default:
                        break;
                }
            }
#endif // End of #if(_4P_DISPLAY_SUPPORT == _ON)

            OsdDisp2ndMenuReDraw(_MENU_INPUT_ITEM, _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_INPUT_SOURCE_3P_ADJ, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(_MENU_INPUT_ITEM, _LOW);
            break;

        default:
            break;
    }
}

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
void MenuDVisionAdjust(void)
{
    EnumInputPort enumInputPort = SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION());

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                // DM OSD On/Off Process
                UserCommonColorDMOSDSupportSwitch(enumInputPort);

                // Demo mode off when Dolby OSD on
                if(GET_OSD_DVISION(SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION())) == _ON)
                {
#if(_COLOR_DEMO_FUNCTION == _ON)
                    // Disable HLW
                    SET_OSD_HLWIN_TYPE(_HL_WIN_OFF);
                    UserAdjustOsdSelectRegionColorProc();
                    RTDNVRamSaveOsdUserData();
                    RTDNVRamSaveOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
#endif
                }

                RTDNVRamSaveOsdInputPortData(UserAdjustGetSelectRegionPort());
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OSD_DVISION, g_usAdjustValue);
            SET_OSD_DVISION(enumInputPort, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_DVISION(enumInputPort, g_usBackupValue);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION), _LOW);
            break;

        default:
            break;
    }
}
void MenuDVisionPictureAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_PICTURE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OSD_DVISION_PICTURE, g_usAdjustValue);
            SET_DVISION_PICTURE(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            UserCommonColorDMOSDAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DM_ADJUST_DM_AND_COLOR);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_DVISION_PICTURE(GET_OSD_SELECT_REGION(), g_usBackupValue);
                UserCommonColorDMOSDAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DM_ADJUST_DM_AND_COLOR);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_PICTURE), _LOW);
            break;

        default:
            break;
    }
}
void MenuDVisionBacklightAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);

                if((GET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].b7DVisionBacklight) &&
                   (GET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionBrightness) &&
                   (GET_DVISION_CONTRAST(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionContrast) &&
                   (GET_DVISION_SATURATION(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionSaturation))
                {
                    SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), _OFF);
                }
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_BACKLIGHT), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), _ON);
            OsdDispSliderAndNumber(_MENU_OSD_DVISION_BACKLIGHT, g_usAdjustValue);
            SET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            UserCommonColorDMOSDAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DM_ADJUST_DM_AND_COLOR);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION(), g_usBackupValue);
                UserCommonColorDMOSDAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DM_ADJUST_DM_AND_COLOR);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_BACKLIGHT), _LOW);
            break;

        default:
            break;
    }
}
void MenuDVisionBrightnessAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);

                if((GET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].b7DVisionBacklight) &&
                   (GET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionBrightness) &&
                   (GET_DVISION_CONTRAST(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionContrast) &&
                   (GET_DVISION_SATURATION(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionSaturation))
                {
                    SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), _OFF);
                }
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_BRIGHTNESS), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), _ON);
            OsdDispSliderAndNumber(_MENU_OSD_DVISION_BRIGHTNESS, g_usAdjustValue);
            SET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            UserCommonColorDMOSDAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DM_ADJUST_DM_AND_COLOR);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION(), g_usBackupValue);
                UserCommonColorDMOSDAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DM_ADJUST_DM_AND_COLOR);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_BRIGHTNESS), _LOW);
            break;

        default:
            break;
    }
}
void MenuDVisionContrastAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);

                if((GET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].b7DVisionBacklight) &&
                   (GET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionBrightness) &&
                   (GET_DVISION_CONTRAST(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionContrast) &&
                   (GET_DVISION_SATURATION(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionSaturation))
                {
                    SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), _OFF);
                }
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_CONTRAST), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), _ON);
            OsdDispSliderAndNumber(_MENU_OSD_DVISION_CONTRAST, g_usAdjustValue);
            SET_DVISION_CONTRAST(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            UserCommonColorDMOSDAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DM_ADJUST_DM_AND_COLOR);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_DVISION_CONTRAST(GET_OSD_SELECT_REGION(), g_usBackupValue);
                UserCommonColorDMOSDAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DM_ADJUST_DM_AND_COLOR);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_CONTRAST), _LOW);
            break;

        default:
            break;
    }
}
void MenuDVisionSaturationAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);

                if((GET_DVISION_BACKLIGHT(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].b7DVisionBacklight) &&
                   (GET_DVISION_BRIGHTNESS(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionBrightness) &&
                   (GET_DVISION_CONTRAST(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionContrast) &&
                   (GET_DVISION_SATURATION(GET_OSD_SELECT_REGION()) == tDVisionPictureModeDefault[GET_DVISION_PICTURE(GET_OSD_SELECT_REGION())].ucDVisionSaturation))
                {
                    SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), _OFF);
                }
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_SATURATION), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            SET_DVISION_PICTURE_MODIFY(GET_OSD_SELECT_REGION(), _ON);
            OsdDispSliderAndNumber(_MENU_OSD_DVISION_SATURATION, g_usAdjustValue);
            SET_DVISION_SATURATION(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            UserCommonColorDMOSDAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DM_ADJUST_DM_AND_COLOR);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_DVISION_SATURATION(GET_OSD_SELECT_REGION(), g_usBackupValue);
                UserCommonColorDMOSDAdjust(GET_OSD_SYSTEM_SELECT_REGION(), _DM_ADJUST_DM_AND_COLOR);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_SATURATION), _LOW);
            break;

        default:
            break;
    }
}
void MenuDVisionNotificationAdjust(void)
{
    EnumInputPort enumInputPort = SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION());

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_NOTIFICATION), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OSD_DVISION_NOTIFICATION, g_usAdjustValue);
            SET_OSD_DVISION_NOTICE(enumInputPort, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_DVISION_NOTICE(enumInputPort, g_usBackupValue);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_DVISION_NOTIFICATION), _LOW);
            break;

        default:
            break;
    }
}
#endif
#endif

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
void MenuTtsFunctionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_TTS_SUPPORT())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_TTS_FUNCTION), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_TTS_FUNCTION, g_usAdjustValue);
            SET_OSD_AUDIO_TTS_SUPPORT(g_usAdjustValue);
            // Here add function
            break;


        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_TTS_SUPPORT())
            {
                SET_OSD_AUDIO_TTS_SUPPORT(g_usBackupValue);
                // Here add function
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_TTS_FUNCTION), _LOW);
            break;

        default:
            break;
    }
}

void MenuTtsTextVolumeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_TTS_TEXT_VOLUME())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_TTS_TEXT_VOLUME), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_TTS_TEXT_VOLUME, g_usAdjustValue);
            SET_OSD_AUDIO_TTS_TEXT_VOLUME(g_usAdjustValue);

            // Here add function

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_TTS_TEXT_VOLUME())
            {
                SET_OSD_AUDIO_TTS_TEXT_VOLUME(g_usBackupValue);
                // Here add function
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_TTS_TEXT_VOLUME), _LOW);

            break;

        default:
            break;
    }
}

void MenuTtsAudioVolumeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_TTS_AUDIO_VOLUME())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_TTS_AUDIO_VOLUME), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_TTS_AUDIO_VOLUME, g_usAdjustValue);
            SET_OSD_AUDIO_TTS_AUDIO_VOLUME(g_usAdjustValue);

            // Here add function

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_TTS_AUDIO_VOLUME())
            {
                SET_OSD_AUDIO_TTS_AUDIO_VOLUME(g_usBackupValue);
                // Here add function
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_TTS_AUDIO_VOLUME), _LOW);

            break;

        default:
            break;
    }
}
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
void MenuFwUpdateAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_stOsdItemData.usAdjValue == _ON)
            {
                OsdDispOsdMessage(_OSD_DISP_FW_UPDATE_MSG);
                SET_OSD_STATE(_MENU_FW_UPDATE_WAITING);
                SysUsbU2HostSetEventChange(_U2HOST_OSD_FW_UPDATE_ENABLE, _ENABLE);
                UserCommonTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_WAIT_RESPONSE);
                g_usAdjustValue = _OFF;
            }
            else
            {
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_FW_UPDATE), _LOW);
            }
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_OSD_ADVANCE_FW_UPDATE, g_usAdjustValue);
            g_stOsdItemData.usAdjValue = g_usAdjustValue;
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_FW_UPDATE), _LOW);
            break;

        default:
            break;
    }
}
void MenuFwUpdateWait(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            break;

        default:
            break;
    }
}

void MenuFwUpdateMsg(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _EXIT_KEY_MESSAGE:
            break;
        case _MENU_KEY_MESSAGE:
            if(g_usAdjustValue == _OFF)
            {
                OsdDispDisableOsd();
                SysUsbU2HostSetEventChange(_U2HOST_OSD_FW_UPDATE_START, _DISABLE);
            }
            else // update Yess
            {
                OsdFuncCloseWindow(_OSD_WIN_HIGHLIGHT_1);
                OsdFuncClearOsd(ROW(0), COL(12), LENGTH(24), HEIGHT(8));
                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 0);
                SET_OSD_STATE(_MENU_FW_UPDATE_PROCESS_BAR);
                SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_BORDER);
                SET_OSD_WINDOW_BORDER_PIXEL_WIDTH(_BAR_BORDER);
                SET_OSD_WINDOW_BORDER_PIXEL_HEIGHT(_BAR_BORDER);
                SET_OSD_WINDOW_EFF_COLOR_1(_CP_BLUE);
                OsdWindowDrawing(_SLIDER_1_BORDER_WINDOW, ((14 * 12)), (27), ((14 + 20) * 12), (27 + 36), _CP_LIGHTBLUE);
                g_usAdjustValue = SysUsbU2HostFwUpdateProgressRate();
                OsdWindowDrawing(_SLIDER_1_BAR_WINDOW, ((14 * 12) + _BAR_BORDER), ((27) + _BAR_BORDER), (((14 * 12) + _BAR_BORDER) + g_usAdjustValue), ((27 + 36) - _BAR_BORDER), _CP_WHITE);
                OsdPropShowPercentage(ROW(2), COL(23), g_usAdjustValue);
                UserCommonTimerActiveTimerEvent(100, _USER_TIMER_EVENT_UPDATE_PROCESSING);
                SET_OSD_FW_UPDATE_NOW(_ON);
                SysUsbU2HostSetEventChange(_U2HOST_OSD_FW_UPDATE_START, _ENABLE);

                // UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
            }
            break;
        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(g_usAdjustValue == _OFF)
            {
                g_usAdjustValue = _ON;
                OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(7), COL(14), WIDTH(8), HEIGHT(1), _CP_BLUE, _CP_WHITE, _CP_BLUE);
            }
            else
            {
                g_usAdjustValue = _OFF;
                OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(7), COL(22), WIDTH(8), HEIGHT(1), _CP_BLUE, _CP_WHITE, _CP_BLUE);
            }
            break;

        default:
            break;
    }
}

void MenuFwUpdateProcess(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _EXIT_KEY_MESSAGE:
            if(g_usAdjustValue < 100)
            {
                UserCommonOsdDisableOsd();
            }
            // UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
            break;
        case _MENU_KEY_MESSAGE:
            if(g_usAdjustValue >= 100)
            {
                if(g_usBackupValue == _OFF)
                {
                    OsdDispDisableOsd();
                    SysUsbU2HostSetEventChange(_U2HOST_OSD_FW_REBOOT_ENABLE, _DISABLE);
                }
                else
                {
                    OsdDispDisableOsd();
                    // Set Kernel Stauts SysUsbU2HostSetEventChange
                    SysUsbU2HostSetEventChange(_U2HOST_OSD_FW_REBOOT_ENABLE, _ENABLE);
                }
            }
            else
            {
                UserCommonOsdEnableOsd();
            }
            // UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
            break;
        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(g_usAdjustValue >= 100)
            {
                if(g_usBackupValue == _OFF)
                {
                    g_usBackupValue = _ON;
                    OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(6), COL(14), WIDTH(8), HEIGHT(1), _CP_BLUE, _CP_WHITE, _CP_BLUE);
                }
                else
                {
                    g_usBackupValue = _OFF;
                    OsdWindowDrawingByFontHighlight(_OSD_WIN_HIGHLIGHT_1, ROW(6), COL(22), WIDTH(8), HEIGHT(1), _CP_BLUE, _CP_WHITE, _CP_BLUE);
                }
            }
            else
            {
                UserCommonOsdEnableOsd();
            }
            // UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
            break;

        default:
            break;
    }
}
#endif // End of #if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)

#if(_AUDIO_ARC_SUPPORT == _ON)
void MenuAudioArcOutput(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ARC_OUT(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_AUDIO_ARC_EARC_DATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_ARC_OUTPUT), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_ARC_OUTPUT, g_usAdjustValue);
            // SET_OSD_ARC_PORT(g_usAdjustValue);
            // add function
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ARC_OUT(g_usBackupValue);
                // add function
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_ARC_OUTPUT), _LOW);
            break;

        default:
            break;
    }
}

void MenuAudioArcInputport(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ARC_PORT(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_AUDIO_ARC_EARC_DATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_ARC_INPUTPORT), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_ARC_INPUTPORT, g_usAdjustValue);
            // SET_OSD_ARC_PORT(g_usAdjustValue);
            // add function
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ARC_PORT(g_usBackupValue);
                // add function
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_ARC_INPUTPORT), _LOW);
            break;

        default:
            break;
    }
}

void MenuAudioArcMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ARC_MODE(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_AUDIO_ARC_EARC_DATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_ARC_MODE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_ARC_MODE, g_usAdjustValue);
            SET_OSD_ARC_MODE(g_usAdjustValue);
            // add function
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ARC_MODE(g_usBackupValue);
                // add function
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_ARC_MODE), _LOW);
            break;

        default:
            break;
    }
}

void MenuAudioArcMute(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ARC_MUTE_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_AUDIO_ARC_EARC_DATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_ARC_MUTE), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_ARC_MUTE, g_usAdjustValue);
            SET_OSD_ARC_MUTE_STATUS(g_usAdjustValue);
            // add function
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ARC_MUTE_STATUS(g_usBackupValue);
                // add function
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_ARC_MUTE), _LOW);
            break;

        default:
            break;
    }
}

void MenuAudioArcChanel(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ARC_CHANEL(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_AUDIO_ARC_EARC_DATA_MSG);
            }

            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_ARC_CHANEL), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_ARC_CHANEL, g_usAdjustValue);
            SET_OSD_ARC_CHANEL(g_usAdjustValue);
            // add function
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ARC_CHANEL(g_usBackupValue);
                // add function
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_AUDIO_ARC_CHANEL), _LOW);
            break;

        default:
            break;
    }
}
#endif

void MenuSource_4P_ADJ(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_4P_DISPLAY_SUPPORT == _ON)
            if(g_usBackupValue != g_usAdjustValue)
            {
                switch(g_usAdjustValue)
                {
                    case _OSD_INPUT_A0:
                    case _OSD_INPUT_D0:
                    case _OSD_INPUT_D1:
                    case _OSD_INPUT_D2:
                    case _OSD_INPUT_D3:
                    case _OSD_INPUT_D4:
                    case _OSD_INPUT_D5:
                    case _OSD_INPUT_D6:
                    case _OSD_INPUT_D7:
                    case _OSD_INPUT_D8:
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_4P_INPUT_SOURCE(g_usAdjustValue);
                        UserAdjustRegionInputPort(_DISPLAY_RGN_RB, g_usAdjustValue);
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    case _OSD_INPUT_AUTO: // Auto
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        OsdFuncSetAutoSearchPort(_REGION_INDEX_3); // replace "SET_OSD_4P_INPUT_SOURCE(g_usAdjustValue);"
                        SysSourceSetMultiAutoSearchTarget(UserCommonSourceGetAutoSearchTarget());
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    default:
                        break;
                }
            }
#endif // End of #if(_4P_DISPLAY_SUPPORT == _ON)

            OsdDisp2ndMenuReDraw(_MENU_INPUT_ITEM, _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            OsdDispSliderAndNumber(_MENU_INPUT_SOURCE_4P_ADJ, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDisp2ndMenuReDraw(_MENU_INPUT_ITEM, _LOW);
            break;

        default:
            break;
    }
}

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
void MenuPxpMstAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PXP_MST())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                UserAdjustDpMstRxPxpMode(GET_OSD_PXP_MST());
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_PXP_MST), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PXP_MST_ADJUST, g_usAdjustValue);
            SET_OSD_PXP_MST(g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_PXP_MST(g_usBackupValue);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_MUTIP_PXP_MST), _LOW);
            break;

        default:
            break;
    }
}
#endif

void MenuHotKeyExitAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_HOTKEY_EXIT(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_EXIT_HOTKEY), _LOW);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_EXIT_HOTKEY_ADJ, g_usAdjustValue);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_HOTKEY_EXIT(g_usBackupValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_EXIT_HOTKEY), _LOW);
            break;

        default:
            break;
    }
}

void MenuHotKeySource(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_1P_INPUT_SOURCE())
            {
                switch(g_usBackupValue)
                {
                    case _OSD_INPUT_A0:
                    case _OSD_INPUT_D0:
                    case _OSD_INPUT_D1:
                    case _OSD_INPUT_D2:
                    case _OSD_INPUT_D3:
                    case _OSD_INPUT_D4:
                    case _OSD_INPUT_D5:
                    case _OSD_INPUT_D6:
                    case _OSD_INPUT_D7:
                    case _OSD_INPUT_D8:
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_1P_INPUT_SOURCE(g_usBackupValue);
                        UserAdjustRegionInputPort(_DISPLAY_RGN_1P, g_usBackupValue);
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    case _OSD_INPUT_AUTO: // Auto
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_1P_INPUT_SOURCE(g_usBackupValue);
                        SysSourceSetMultiAutoSearchTarget(_DISPLAY_RGN_1P);
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    default:
                        break;
                }

#if(_DP_MST_SUPPORT == _ON)
                UserCommonDpMstRxCapablePortSwitch(UserCommonDpGetMSTCapablePort());
                RTDNVRamSaveOsdUserData();

#endif
            }

            OsdDispDisableOsd();
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            g_usBackupValue = OsdFuncCheckInputPortType(g_usBackupValue, _REGION_INDEX_0);
            DebugMessageOsd("hot key", g_usBackupValue);
            OsdDispHotKeySourceMenuSwitch(g_usBackupValue);
            OsdDispHotKeySourceMenuIcon(g_usBackupValue);

            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuHotKeyInformation(void)
{
    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        switch(GET_KEYMESSAGE())
        {
            case _MENU_KEY_MESSAGE:
            case _RIGHT_KEY_MESSAGE:
            case _LEFT_KEY_MESSAGE:
            case _EXIT_KEY_MESSAGE:
            default:
                OsdDispDisableOsd();
                break;
        }
    }
    else
    {
        switch(GET_KEYMESSAGE())
        {
            case _RIGHT_KEY_MESSAGE:
                OsdDispHotKeySourceMenu();
                break;
            case _MENU_KEY_MESSAGE:
            case _LEFT_KEY_MESSAGE:
            case _EXIT_KEY_MESSAGE:
            default:
                OsdDispDisableOsd();
                break;
        }
    }
}

void MenuPanelUniformityMsgAdjust(void)
{
    BYTE ucbackupIdx = GET_OSD_ITEM_INDEX();
    switch(GET_KEYMESSAGE())
    {
        case _EXIT_KEY_MESSAGE:
        case _MENU_KEY_MESSAGE:

            if((g_usAdjustValue != GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION())) &&
               (GET_KEYMESSAGE() == _EXIT_KEY_MESSAGE))
            {
                SET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION(), g_usAdjustValue);

#if(_UNIFORMITY_FUNCTION == _ON)
                UserAdjustPanelUniformityMode(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING);
                UserAdjustPanelUniformityMode(UserCommonRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()), _DB_APPLY_POLLING);
#endif
            }

            RTDNVRamSaveOsdUserData();
            UserCommonTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
            OsdFuncDisableOsd();
            OsdDispMainMenu();
            SET_OSD_ITEM_INDEX(ucbackupIdx);

            if(g_usBackupValue == _FROM_STATE_GAMMA)
            {
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_GAMMA), _HIGH);
            }
            else if(g_usBackupValue == _FROM_STATE_PCM)
            {
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_COLOR_PCM), _HIGH);
            }

            else if(g_usBackupValue == _FROM_STATE_HDR)
            {
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_HDR_MODE), _HIGH);
            }
            else if(g_usBackupValue == _FROM_STATE_LD)
            {
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_LOCALDIMMING), _HIGH);
            }
            else if(g_usBackupValue == _FROM_STATE_SDRTOHDR)
            {
                OsdDisp2ndMenuReDraw(OsdDispGetUpLayer(_OSD_ADVANCE_SDR_TO_HDR), _HIGH);
            }
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispPanelUniformityMsgSwitch();

#if(_UNIFORMITY_FUNCTION == _ON)
            UserAdjustPanelUniformityMode(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING);
            UserAdjustPanelUniformityMode(UserCommonRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()), _DB_APPLY_POLLING);
#endif
            break;

        default:
            break;
    }
}


void MenuMeseageDisplay(void)
{
}


void MenuHotKeyNone(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            switch(g_stOsdItemData.usStringIdx)
            {
                case _STRING_INPUT_SWAP:
                    if((GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR) ||
                       (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB) ||
                       (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP))
                    {
                        g_usBackupValue = GET_OSD_1P_INPUT_SOURCE();
                        SET_OSD_1P_INPUT_SOURCE(GET_OSD_2P_INPUT_SOURCE());
                        SET_OSD_2P_INPUT_SOURCE(g_usBackupValue);
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);

#if(_2P_DISPLAY_SUPPORT == _ON)
                        UserAdjustSwapInputPort();
#endif
                    }

                    break;


                case _STRING_RESET:
                    // show wait
                    OsdDispOsdReset();
                    break;

                case _STRING_AUTO_ADJUST:
#if(_VGA_SUPPORT == _ON)
                    if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
                       (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
                    {
                        UserCommonVgaAutoConfig();
                    }
#endif
                    break;

                case _STRING_AUTO_COLOR:
#if(_VGA_SUPPORT == _ON)
                    if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
                       (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
                    {
                        if(GET_OSD_FACTORY_AUTO_COLOR_TYPE() == _AUTO_COLOR_TYPE_INTERNAL)
                        {
                            g_usAdjustValue = _AUTO_CALIBRATE_RGB;
                        }
                        else
                        {
                            g_usAdjustValue = _AUTO_TUNE_RGB;
                        }

                        if(UserCommonVgaAutoDoWhiteBalance(g_usAdjustValue) == _AUTO_SUCCESS)
                        {
                            UserCommonVgaAutoGetAutoColorResult(&g_stVgaAdcData);
                            UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
                        }
                        else
                        {
                            UserCommonNVRamRestoreADCSetting();
                        }
                    }
#endif
                    break;
                default:
                    break;
            }
            break;
        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}


void (*code tOperationTable[])(void) =
{
    MenuNone,
    MeunMain,
    // 1st Item
    MenuPictureItem,
    MenuDisplayItem,
    MenuColorItem,
    MenuAdvanceItem,
    MenuAudioItem,
    MenuOtherItem,
    MenuMutiPItem,
    MenuHdrItem,
#if(_DM_FUNCTION == _ON)
    MenuDVisionItem,
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
    MenuAudioArcItem,
#endif
    MenuQuickLinkItem,
    MenuSource_Item,

    // MutiP
    MenuDisplayMode,
    MenuSelectRegion,
    MenuDisplayFunDispRotateAdjust,
    MenuDisplayFunDispLatencyAdjust,
    MenuDisplayFunFreezeAdjust,
    MenuDisplayFunLRratioAdjust,
    MenuDisplayFunPipPositionAdjust,
    MenuDisplayFunPipPositionUser,
    MenuDisplayFunPipPositionHAdjust,
    MenuDisplayFunPipPositionVAdjust,
    MenuDisplayFunPipTransparencyAdjust,
    MenuDisplayFunPipSizeAdjust,

    // picture
    MenuPictureBacklightAdjust,
    MenuPictureBrightnessAdjust,
    MenuPictureContrastAdjust,
    MenuPictureSharpnessAdjust,

    // display
    MenuDisplayHPosAdjust,
    MenuDisplayVPosAdjust,
    MenuDisplayClockAdjust,
    MenuDisplayPhaseAdjust,

    // color adjust
    MenuColorPanelUniformityAdjust,
    MenuColorGammaAdjust,
    MenuColorColortempAdjust,
    MenuColorColorEffectAdjust,
    MenuColorColorDemoAdjust,
    MenuColorColorDemoSideAdjust,
    MenuColorColorFormatAdjust,
    MenuColorColorPCMAdjust,
    MenuColorColorHueAdjust,
    MenuColorColorSaturationAdjust,
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
    MenuColorEyeProtectAdjust,
#endif

    // advance adjust
    MenuAdvanceAspectAdjust,
    MenuAdvanceOverScanAdjust,
    MenuAdvanceDdcciAdjust,
    MenuAdvanceUltraVividAdjust,
    MenuAdvanceDCRAdjust,
    MenuAdvanceDpOptionD0,
    MenuAdvanceDpOptionD1,
    MenuAdvanceDpOptionD2,
    MenuAdvanceDpOptionD6,
    MenuAdvanceDPMstAdjust,
    MenuAdvanceCloneAdjust,
    MenuAdvanceFreeSyncAdjust,
    MenuAdvanceDualDPEdidAdjust,
    MenuAdvanceEdidAdjust,
    MenuAdvanceEdidDXAdjust,
    MenuAdvanceHDMIVersionAdjust,
    MenuAdvanceDxHDMIVersionAdjust,
    MenuAdvanceDscAdjust,
    MenuAdvanceTypeCModeD0,
    MenuAdvanceTypeCModeD1,
    MenuAdvanceTypeCModeD2,
    MenuAdvanceTypeCModeD6,
    MenuAdvancePixelShifAdjust,
    MenuAdvanceSdrToHdrAdjust,
    MenuAdvanceGlobalDimmingAdjust,
    MenuAdvanceLocalContrastAdjust,
    MenuAdvanceLocalContrastUser,
    MenuAdvanceLocalContrastBlending,
    MenuAdvanceLocalContrastDiffGain,
    MenuAdvanceHubSwitchAdjust,
    MenuAdvanceEagleSightAdjust,
    MenuAdvanceMbrAdjust,
    MenuAdvanceDpAuxlessAlpmAdjust,
    MenuAdvanceDpAdaptiveSyncAdjust,
    MenuAdvancePanelReplayAdjust,
    MenuAdvanceSDRPlusAdjust,
    MenuAdvanceSDRPlusSelect,
    MenuAdvanceSDRPlusSharpAdjust,
    MenuAdvanceSDRPlusDarkAdjust,
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
    MenuAdvanceNightSniper,
    MenuAdvanceNightSniperSelect,
    MenuAdvanceNightSniperSaturatuin,
    MenuAdvanceNightSniperLightness,
#endif
    MenuAdvanceAntiAliasingAdjust,
    MenuAdvanceEnergySaverAdjust,

    // Audio adjust
    MenuAudioVolumeAdjust,
    MenuAudioMuteOnOff,
    MenuAudioStandAlongSelect,
    MenuAudioAudioSourceSelect,
    MenuAudioSoundModeSelect,
    MenuAudioAudioSelfTestSelect,

    // other adjust
    MenuOtherMenuTimeAdjust,
    MenuOtherOsdHPosAdjust,
    MenuOtherOsdVPosAdjust,
    MenuOtherLanguageAdjust,
    MenuOtherTransparencyAdjust,
    MenuOtherRotateAdjust,
    MenuOtherSelectRegionWidthAdjust,
    MenuOtherSelectRegionColorAdjust,
    MenuOtherCrosshairAdjust,

    // color temp user RGB
    MenuColorColortempUserR,
    MenuColorColortempUserG,
    MenuColorColortempUserB,

    // color temp user adjust RGB
    MenuColorColortempUserAdjustR,
    MenuColorColortempUserAdjustG,
    MenuColorColortempUserAdjustB,

    // color effect user adjust
    MenuColorColorEffcUserRHue,
    MenuColorColorEffcUserRSat,
    MenuColorColorEffcUserYHue,
    MenuColorColorEffcUserYSat,
    MenuColorColorEffcUserGHue,
    MenuColorColorEffcUserGSat,
    MenuColorColorEffcUserCHue,
    MenuColorColorEffcUserCSat,
    MenuColorColorEffcUserBHue,
    MenuColorColorEffcUserBSat,
    MenuColorColorEffcUserMHue,
    MenuColorColorEffcUserMSat,

    // color effect user adjust Hue & Sat
    MenuColorColorEffcUserRHueAdjust,
    MenuColorColorEffcUserRSatAdjust,
    MenuColorColorEffcUserYHueAdjust,
    MenuColorColorEffcUserYSatAdjust,
    MenuColorColorEffcUserGHueAdjust,
    MenuColorColorEffcUserGSatAdjust,
    MenuColorColorEffcUserCHueAdjust,
    MenuColorColorEffcUserCSatAdjust,
    MenuColorColorEffcUserBHueAdjust,
    MenuColorColorEffcUserBSatAdjust,
    MenuColorColorEffcUserMHueAdjust,
    MenuColorColorEffcUserMSatAdjust,

#if(_ICM_CHAMELEON_FUNCTION == _ON)
    MenuColorChameleonHue,
    MenuColorChameleonSat,
    MenuColorChameleonLightness,
    MenuColorChameleonHueAdjust,
    MenuColorChameleonSatAdjust,
    MenuColorChameleonLightnessAdjust,
#endif
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
    MenuColorEyeProtectLowBlueModeAdjust,
    MenuColorEyeProtectLevelAdjust,
    MenuColorEyeProtectNightModeTimeAdjust,
    MenuColorEyeProtectAmbientSenseAdjustMode,
#endif

    MenuAdvanceODGainAdjust,

    MenuAdvanceDpD0VersionAdjust,
    MenuAdvanceDpD1VersionAdjust,
    MenuAdvanceDpD2VersionAdjust,
    MenuAdvanceDpD6VersionAdjust,

    MenuAdvanceD0TypeCModeAdjust,
    MenuAdvanceD1TypeCModeAdjust,
    MenuAdvanceD2TypeCModeAdjust,
    MenuAdvanceD6TypeCModeAdjust,
    MenuAdvanceLDOnOffAdjust,
    MenuAdvanceLDSmoothAdjAdjust,

    MenuHdrModeAdjust,
    MenuHdrDarkEnhanceOnOffAdjust,
    MenuHdrSharpnessOnOffAdjust,
    MenuHdrContrastAdjust,
    MenuHdrColorEnhanceAdjust,
    MenuHdrLightEnhanceAdjust,
    MenuHdrHlgOotfAdjust,

    MenuAdvanceEagleSightFunctionAdj,
    MenuAdvanceEagleSightRegionAdj,
    MenuAdvanceEagleSightTransparencyAdj,
    MenuAdvanceEagleSightZoomAdj,
    MenuAdvanceEagleSightCapPositionAdj,
    MenuAdvanceEagleSightDispPositionAdj,
    MenuAdvanceEagleSightBorderAdj,
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
    MenuAdvanceEagleSightCircleWinAdj,
#endif
    MenuAdvanceMbrModeAdj,
    MenuAdvanceMbrDutyAdj,
    MenuAdvanceMbrPositionAdj,
    MenuAdvanceAntiAliasingModeAdj,
    MenuAdvanceAntiAliasingLevelAdj,
    // input
    MenuSource_1P_ADJ,
    MenuSource_2P_ADJ,
    MenuSource_3P_ADJ,
    MenuSource_4P_ADJ,

#if(_DM_FUNCTION == _ON)
    MenuDVisionAdjust,
    MenuDVisionPictureAdjust,
    MenuDVisionBacklightAdjust,
    MenuDVisionBrightnessAdjust,
    MenuDVisionContrastAdjust,
    MenuDVisionSaturationAdjust,
    MenuDVisionNotificationAdjust,
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    MenuPxpMstAdjust,
#endif
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
    MenuTtsFunctionAdjust,
    MenuTtsTextVolumeAdjust,
    MenuTtsAudioVolumeAdjust,
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
    MenuFwUpdateAdjust,
    MenuFwUpdateWait,
    MenuFwUpdateMsg,
    MenuFwUpdateProcess,
#endif
#if(_AUDIO_ARC_SUPPORT == _ON)
    MenuAudioArcOutput,
    MenuAudioArcInputport,
    MenuAudioArcMode,
    MenuAudioArcMute,
    MenuAudioArcChanel,
#endif

//STEP 4 Add New Item Here!!!!!

    MenuHotKeyExitAdjust,
    // hotkey source
    MenuHotKeySource,
    // hotkey information
    MenuHotKeyInformation,
    // ask turn off/on panel uniformity msg
    MenuPanelUniformityMsgAdjust,
    // display PS logo
    MenuMeseageDisplay,
    MenuHotKeyNone,
};
#endif// #if(_OSD_TYPE == _REALTEK_2020_OSD)
