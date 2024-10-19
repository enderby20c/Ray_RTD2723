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
// ID Code      : RTD2020UserInterfaceMode.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_MODE__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceMode.h"

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
// Description  : Get whether to by pass normal active process
// Input Value  : None
// Output Value : _TRUE => By pass normal active process
//--------------------------------------------------
EnumBypassColorProcStatus UserInterfaceModeGetActiveByPassStatus(EnumDisplayRegion enumDisplayRegion)
{
    if(SysRegionCheckDisplayEvent(enumDisplayRegion, _DISPLAY_EVENT_FIRST_ACTIVE) == _TRUE)
    {
        // Adjust color format & overscan case
        if((SysRegionGetInputPort(GET_OSD_SYSTEM_DISPLAY_REGION()) == SysRegionGetInputPort(enumDisplayRegion)) &&
           ((GET_OSD_STATE() == _MENU_COLOR_FORMAT_ADJUST) || (GET_OSD_STATE() == _MENU_COLOR_ITEM)))
        {
            return _BYPASS_COLOR_PROC_FALSE;
        }

        return _BYPASS_COLOR_PROC_TRUE;
    }

    return _BYPASS_COLOR_PROC_FALSE;
}

//--------------------------------------------------
// Description  : Color process in display initial
// Input Value  : System display mode
// Output Value : None
//--------------------------------------------------
void UserInterfaceModeDisplayInitialColorProc(EnumDisplayMode enumDisplayMode)
{
    enumDisplayMode = enumDisplayMode;

#if(_COLOR_DEMO_FUNCTION == _ON)
    // Reset to case:_HL_WIN_MOVE default position
    g_usColorHLWinHWidth = _PANEL_DH_WIDTH / 6;
    g_usColorHLWinVHeight = _PANEL_DV_HEIGHT - _HL_WIN_BORDER_SIZE;
    g_usColorHLWinHPos = (_PANEL_DH_WIDTH - _PANEL_DH_WIDTH / 6) / 2;
    g_usColorHLWinVPos = 0;
    g_bColorHLWinRLMove = _RIGHT;
#endif
}

#if((_PANEL_STYLE != _PANEL_VBO) || ((_PANEL_STYLE == _PANEL_VBO) && (_VBO_BACKLIGHT_BY_USER == _ENABLE)))
//--------------------------------------------------
// Description  : Get backlight staus when performing display setting
// Input Value  : None
// Output Value : _BACKLIGHT_ENABLE or _BACKLIGHT_DISABLE
//--------------------------------------------------
EnumBacklightAction UserInterfaceModeDisplaySettingGetBacklightAction(void)
{
#if((_PANEL_STYLE == _PANEL_DPTX) ||\
    (_PANEL_STYLE == _PANEL_VBO))

    return _BACKLIGHT_DISABLE;

#else

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(GET_ROT_TYPE() != UserInterfaceDisplayGetRotationDegree())
    {
        return _BACKLIGHT_DISABLE;
    }

    if((GET_ROT_TYPE() != _ROT_DISABLE) &&
       (UserInterfaceDisplayGetRotationDegree() != _ROT_DISABLE) &&
       (GET_ROT_DISP_SIZE() != UserInterfaceDisplayGetRotationDisplayType()))
    {
        return _BACKLIGHT_DISABLE;
    }
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(GET_ROT_TYPE() != _ROT_DISABLE)
#endif
    {
        if(GET_DISP_LATENCY_RATIO() != UserInterfaceDisplayGetLatencyRatio())
        {
            return _BACKLIGHT_DISABLE;
        }
    }
#endif

    return _BACKLIGHT_ENABLE;

#endif
}
#endif

#if(_FIRST_CHECK_CONTROL_BACKLIGHT_BY_USER == _ON)
//--------------------------------------------------
// Description  : Get backlight staus when performing FirstDisplayCheck
// Input Value  : None
// Output Value : _BACKLIGHT_ENABLE or _BACKLIGHT_DISABLE
//--------------------------------------------------
EnumBacklightAction UserInterfaceModeFirstDisplayCheckGetBacklightAction(EnumDisplayMode enumDisplayMode)
{
#if(_2P_FRAME_SYNC_SUPPORT == _ON)
    if(UserCommonDisplayGet2PFrameSyncEnable() == _ENABLE)
    {
        // 2P Frame Sync Support on, Enable Backlight on when Region_0 or Region_1 in active
        if((SysRegionGetDisplayState((EnumDisplayRegion)(enumDisplayMode | _REGION_INDEX_0)) == _DISPLAY_STATE_ACTIVE) ||
           (SysRegionGetDisplayState((EnumDisplayRegion)(enumDisplayMode | _REGION_INDEX_1)) == _DISPLAY_STATE_ACTIVE))
        {
            return _BACKLIGHT_ENABLE;
        }
    }
    else
#endif
    {
        // Turn on back light when:
        // 1. under 2P/4P mode
        // 2. 1P mode in active state
        // Main & Sub Will Loop 1 Times
        if(((enumDisplayMode == _DISPLAY_MODE_1P) && (SysRegionGetDisplayState((EnumDisplayRegion)(enumDisplayMode | _REGION_INDEX_0)) == _DISPLAY_STATE_ACTIVE)) ||
           (enumDisplayMode != _DISPLAY_MODE_1P))
        {
            return _BACKLIGHT_ENABLE;
        }
    }

    return _BACKLIGHT_DISABLE;
}
#endif

//--------------------------------------------------
// Description  : Modify display Timing Based on User Requirement
// Input Value  : Display Region
// Output Value : None
//--------------------------------------------------
void UserInterfaceModeDisplaySettingInitialization(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
}

//--------------------------------------------------
// Description  : Set User Required Color Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceModeDisplaySettingColorProc(EnumDisplayRegion enumDisplayRegion)
{
    EnumSourceType enumSourceType = SysRegionGetSourceType(enumDisplayRegion);

#if(_COLOR_PROCESS_CONTROL_BY_USER == _ON)
    // For User

#else
#if(_ULTRA_HDR_SUPPORT == _ON)
    bit bAdjustBacklight = _TRUE;

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if((UserCommonColorDMGetDMStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _TRUE) ||
       (UserCommonColorDMGetDMStatus(UserAdjustConvertDisplayRegion(GET_OSD_INVERSE_REGION())) == _TRUE)) // DM is on (backlight max)
    {
        bAdjustBacklight &= _FALSE;
    }
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
    if(UserCommonColorHDRGetBackLightAdaptiveTMBackLightStatus() != _HDR10_BACKLIGHT_ADAPTIVE_TM_BACKLIGHT_OSD)
#else
    if((UserCommonColorHDRGetHDR10Status(GET_OSD_SYSTEM_DISPLAY_REGION()) != _HDR10_OFF) ||
       (UserCommonColorHDRGetHDR10Status(UserAdjustConvertDisplayRegion(GET_OSD_INVERSE_REGION())) != _HDR10_OFF)) // HDR is on (backlight max)
#endif
    {
        bAdjustBacklight &= _FALSE;
    }
#endif

    if(bAdjustBacklight == _TRUE)
#endif
    {
        // Adjust Backlight
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }

    // Adjust Brightness & Contrast
    RTDNVRamLoadOsdInputSourceData(enumSourceType);

    // Adjust Transparency
    UserCommonOsdSetTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // User Adjust Background Color
    UserCommonDDomainBackgroundSetColorByRegion(enumDisplayRegion, 0, 0, 0, _DB_APPLY_NO_POLLING);

#if(_COLOR_DEMO_FUNCTION == _ON)
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_MOVE)
    {
        UserCommonTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
    }
#endif
#endif  // End of #if(_COLOR_PROCESS_CONTROL_BY_USER == _ON)
}

//--------------------------------------------------
// Description  : Set Color in pass normal active process
// Input Value  : None
// Output Value : void
//--------------------------------------------------
void UserInterfaceModeDisplaySettingByPassColorProc(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
}

#if(_COLOR_DEMO_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Loading select region's display setting data for Demo mode color proc
// Input Value  : Select Region
// Output Value : None
//--------------------------------------------------
void UserInterfaceModeDisplaySettingDemoModeColorProc(EnumSelRegion enumSelRegion)
{
    if(enumSelRegion == _DEMO_INSIDE)  // For DEMO inside.
    {
        // Osd select region do not have _DEMO_INSIDE/_DEMO_OUTSIDE.
        // Into "LoadColorSetting", GET_COLOR_TEMP_TYPE -> RTDNVRamTransferOsdRegionType => Output: _INSIDE/_OUTSIDE.
        // When HLW not OFF, ucType = ucRegion % 2. Using EnumOSDHLWRegion (0/1) will gets correct behavior.
        RTDNVRamLoadColorSetting(_OSD_HLW_INSIDE);
    }
    else if(enumSelRegion == _DEMO_OUTSIDE)  // For DEMO outside.
    {
        RTDNVRamLoadColorSetting(_OSD_HLW_OUTSIDE);
    }
}
#endif

//--------------------------------------------------
// Description  : Loading select region's display setting data for Normal mode color proc
// Input Value  : Select Region
// Output Value : None
//--------------------------------------------------
void UserInterfaceModeDisplaySettingNormalModeColorProc(EnumSelRegion enumSelRegion)
{
    EnumSelRegion enumOsdSelRegion = GET_OSD_SYSTEM_SELECT_REGION();

    if(enumOsdSelRegion == enumSelRegion)   // OSD Select Region == Display target.
    {
        RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
    }
    else
    {
        RTDNVRamLoadColorSetting(GET_OSD_INVERSE_REGION());  // OSD Select Region != Display target.
    }
}

//--------------------------------------------------
// Description  : OSD Active Process
// Input Value  : Display Region
// Output Value : None
//--------------------------------------------------
void UserInterfaceModeDisplayActiveProc(EnumDisplayRegion enumDisplayRegion)
{
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
    // Save auto search input port
    if((UserCommonSourceGetAutoSearchTarget() == enumDisplayRegion) && (SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT))
    {
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
        // D4 and D14/D15 have the same g_ucSourceSearchIndex => SysRegionGetInputPort()=D4 is always true for D4/D14/D15.
        if(UserCommonNVRamGetSystemRegionPortData(enumDisplayRegion) != SysRegionGetInputPort(enumDisplayRegion))
        {
            if((SysRegionGetInputPort(enumDisplayRegion) == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)) // ACTIVE PORT = D14
            {
                UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, _D14_INPUT_PORT);
            }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
            else if((SysRegionGetInputPort(enumDisplayRegion) == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)) // ACTIVE PORT = D15
            {
                UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, _D15_INPUT_PORT);
            }
#endif
            else
            {
                UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, SysRegionGetInputPort(enumDisplayRegion));
            }

            UserCommonNVRamSaveSystemData();
        }
        else
        {
            // NVRAM Port is D4 but Active Port is D14.
            if((SysRegionGetInputPort(enumDisplayRegion) == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14))
            {
                UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, _D14_INPUT_PORT);
                UserCommonNVRamSaveSystemData();
            }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
            // NVRAM Port is D4 but Active Port is D15.
            else if((SysRegionGetInputPort(enumDisplayRegion) == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15))
            {
                UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, _D15_INPUT_PORT);
                UserCommonNVRamSaveSystemData();
            }
#endif
        }

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

        // D3 and D12/D13 have the same g_ucSourceSearchIndex => SysRegionGetInputPort()=D3 is always true for D3/D12/D13.
        if(UserCommonNVRamGetSystemRegionPortData(enumDisplayRegion) != SysRegionGetInputPort(enumDisplayRegion))
        {
            if((SysRegionGetInputPort(enumDisplayRegion) == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)) // ACTIVE PORT = D12
            {
                UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, _D12_INPUT_PORT);
            }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
            else if((SysRegionGetInputPort(enumDisplayRegion) == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)) // ACTIVE PORT = D13
            {
                UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, _D13_INPUT_PORT);
            }
#endif
            else
            {
                UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, SysRegionGetInputPort(enumDisplayRegion));
            }

            UserCommonNVRamSaveSystemData();
        }
        else
        {
            // NVRAM Port is D3 but Active Port is D12.
            if((SysRegionGetInputPort(enumDisplayRegion) == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12))
            {
                UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, _D12_INPUT_PORT);
                UserCommonNVRamSaveSystemData();
            }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
            // NVRAM Port is D3 but Active Port is D13.
            else if((SysRegionGetInputPort(enumDisplayRegion) == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13))
            {
                UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, _D13_INPUT_PORT);
                UserCommonNVRamSaveSystemData();
            }
#endif
        }
#endif
    }
#else
    // Save auto search input port
    if((UserCommonSourceGetAutoSearchTarget() == enumDisplayRegion) &&
       (SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) &&
       (UserCommonNVRamGetSystemRegionPortData(enumDisplayRegion) != SysRegionGetInputPort(enumDisplayRegion)))
    {
        UserCommonNVRamSetSystemRegionPortData(enumDisplayRegion, SysRegionGetInputPort(enumDisplayRegion));
        UserCommonNVRamSaveSystemData();
    }
#endif

    // DDCCI switch to active port
    UserCommonDdcciSwitchPort(UserAdjustDdcciGetStatus());

    UserCommonDdcciMapping();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
    {
    }
    else
#endif
    {
        if(GET_FAIL_SAFE_MODE(UserCommonRegionGetIndex(enumDisplayRegion)) == _TRUE)
        {
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG);
        }
        else
        {
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_ACTIVE_DO_ONE_TIME_MSG);
        }
    }

#if(_FREEZE_SUPPORT == _ON)
    if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
    {
        UserCommonDisplayFreeze(GET_OSD_FREEZE_STATUS());
    }
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _ON)
    if(UserCommonColorDMGetMuteStatus(enumDisplayRegion) == _FALSE) // unmute if DM is ready
#endif
#endif
    {
        UserCommonDDomainBackgroundEnableByRegion(enumDisplayRegion, _DISABLE);
    }

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
#if(_PIP_TRANSPARENCY_SUPPORT == _ON)
    // Adjust PIPBlending level
    UserAdjustPipTransparency(GET_OSD_PIP_TRANSPARENCY());
#endif
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
    OsdDisplaySetPixelOrbitingCapability();

    if((GET_OSD_PIXELSHIFT_STATUS() == _ON) &&
       (GET_PIXEL_ORBITING_CAPABILITY() == _ON))
    {
        SET_PIXEL_ORBITING_TIME(_PIXEL_SHIFT_TIME);
    }
#endif
}

//--------------------------------------------------
// Description  : OSD Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceModeResetProc(void)
{
    // Disable OSD
    if(GET_OSD_LOGO_ON() == _OFF)
    {
        OsdDispDisableOsd();
    }

    SET_OSD_LOGO_ON(_OFF);

    // Cancel Timer Events
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_DO_AUTO_COLOR);
#if(_COLOR_DEMO_FUNCTION == _ON)
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
#endif
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_UPDATE_PROCESSING);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_WAIT_RESPONSE);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_UPDATE_OSD_DISABLE);
#endif
}

//--------------------------------------------------
// Description  : OSD Reset Region Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceModeResetRegionProc(EnumDisplayRegion enumDisplayRegion)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        default:
            break;

        case _OSD_DM_1P:
        case _OSD_DM_2P_LR:
        case _OSD_DM_2P_TB:
        case _OSD_DM_2P_PIP:
        case _OSD_DM_3P_FLAG:
        case _OSD_DM_3P_SKEW_L:
        case _OSD_DM_3P_SKEW_R:
        case _OSD_DM_3P_SKEW_T:
        case _OSD_DM_3P_SKEW_B:
        case _OSD_DM_4P:

            switch(SysRegionGetDisplayState(enumDisplayRegion))
            {
                case _DISPLAY_STATE_NO_SIGNAL:
                case _DISPLAY_STATE_OOR:

                    // if display power saving, close Hint message
                    if(GET_OSD_STATE() == _MENU_MESSAGE_DISPLAY)
                    {
                        OsdDispDisableOsd();
                    }

                    // Cancel PS Timer Events
                    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
                    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);

                    break;

                default:
                    break;
            }
            break;
    }

    // Update LED status
    if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) == 0X00)
    {
        RTDKeyPadLedControl(_LED_POWER_SEARCH);
    }
}

//--------------------------------------------------
// Description  : OSD Resume from NSG Region Process
// Input Value  : display region
// Output Value : None
//--------------------------------------------------
void UserInterfaceModeResumeRegionProc(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

    // if display power saving, close Hint message
    if(GET_OSD_STATE() == _MENU_MESSAGE_DISPLAY)
    {
        OsdDispDisableOsd();
    }

    // Cancel PS Timer Events
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
    UserCommonTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
}
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

