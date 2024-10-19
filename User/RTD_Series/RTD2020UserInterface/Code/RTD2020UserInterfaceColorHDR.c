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
// ID Code      : RTD2020UserInterfaceColorHDR.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_HDR__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceColorHDR.h"

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
#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust HDR to SDR flow
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorHDRAdjustSDRProc(EnumDisplayRegion enumDisplayRegion)
{
    EnumSelRegion enumSelRegion = (EnumSelRegion)enumDisplayRegion;
    BYTE ucOSDSelectRegion = UserAdjustGetOsdDisplaySelectRegion(enumDisplayRegion);

    WORD usColorFunction = (_COLOR_FUNCTION_ULTRA_VIVID |
                            _COLOR_FUNCTION_LIGHT_ENHANCE |
                            _COLOR_FUNCTION_DCC |
                            _COLOR_FUNCTION_COLOR_ENHANCE |
                            _COLOR_FUNCTION_ICM |
                            _COLOR_FUNCTION_LOCAL_CONTRAST |
                            _COLOR_FUNCTION_CTS_BRI);

    if(UserInterfaceColorHDRGetHDRDemoModeEnable() == _HDR_DEMO_ON)
    {
        enumSelRegion = _DEMO_INSIDE;
    }

    UserCommonColorMultiFunctionRegionEnableStart(enumSelRegion, usColorFunction);

#if(_ULTRA_VIVID_FUNCTION == _ON)
    UserCommonColorUltraVividAdjust(enumSelRegion);
#endif

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
    UserCommonColorHDRAdjustHDR10LightEnhance(enumSelRegion, _DB_APPLY_NONE);
#elif(_DCC_FUNCTION == _ON)
    UserCommonColorDCCAdjust(enumSelRegion);
#endif

#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
    UserCommonColorHDRAdjustHDR10ColorEnhance(enumSelRegion, _DB_APPLY_NONE);
#elif(_ICM_FUNCTION == _ON)
    UserCommonColorICMAdjust(enumSelRegion);
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
    // Load Inital Table
    UserCommonColorLocalContrastInitalDataAdjust(enumSelRegion);
    UserCommonColorLocalContrastAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_CONTRAST_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS(ucOSDSelectRegion) == _PCM_OSD_NATIVE)
    {
        RTDNVRamLoadColorSetting(UserAdjustGetOSDSelectRegion(enumSelRegion));
    }
    UserCommonColorContrastAdjust(enumSelRegion);
#endif

#if(_BRIGHTNESS_FUNCTION == _ON)
    UserCommonColorBrightnessAdjust(enumSelRegion);
#endif

    UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegion, usColorFunction);

    if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
    {
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
    else // MtP
    {
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
        if((UserCommonColorDMGetDMStatus(GET_OSD_SYSTEM_DISPLAY_REGION()) == _TRUE) ||
           (UserCommonColorDMGetDMStatus(UserAdjustConvertDisplayRegion(GET_OSD_INVERSE_REGION())) == _TRUE)) // DM is on (backlight max)
        {
            return;
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
            return;
        }
#endif
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
}

//--------------------------------------------------
// Description  : Get Demo Mode Status
// Input Value  : None
// Output Value : HDR Demo On/Off
//--------------------------------------------------
EnumHDRDemoStatus UserInterfaceColorHDRGetHDRDemoModeEnable(void)
{
#if(_COLOR_DEMO_FUNCTION == _ON)
    if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
    {
        if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
        {
            return _HDR_DEMO_ON;
        }
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        else if(SysModeGetDisplayMode() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            return _HDR_DEMO_ON;
        }
#endif
    }
#endif

    return _HDR_DEMO_OFF;
}

//--------------------------------------------------
// Description  : Get HDR Demo Mode Outside Status
// Input Value  : None
// Output Value : HDR Demo Outside On/Off
//--------------------------------------------------
EnumHDRDemoStatus UserInterfaceColorHDRGetHDRDemoModeOutsideStatus(void)
{
    return _HDR_DEMO_OFF;
}

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Remap OSD to HDR10 mode by user
// Input Value  : Input Port
// Output Value : EnumHDR10ModeDef
//--------------------------------------------------
EnumHDR10ModeDef UserInterfaceColorHDRGetHDR10ModeStatus(EnumInputPort enumInputPort)
{
    // Disable HDR for 3P/4P modes
    if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX) > 2)
    {
        return _HDR10_MODE_OFF;
    }

    switch(GET_OSD_HDR_MODE(enumInputPort))
    {
        case _HDR10_MODE_AUTO:
            // HDR Check Data
            return _HDR10_MODE_AUTO;

        case _HDR10_MODE_FORCE_2084:
            // HDR always ON
            return _HDR10_MODE_FORCE_2084;

#if(_HLG_SUPPORT == _ON)
        case _HDR10_HLG_MODE_AUTO:
            return _HDR10_HLG_MODE_AUTO;

        case _HDR10_HLG_MODE_FORCE_HLG:
            return _HDR10_HLG_MODE_FORCE_HLG;
#endif

        default:
        case _HDR10_MODE_OFF:
            // HDR always OFF
            return _HDR10_MODE_OFF;
    }
}

//--------------------------------------------------
// Description  : Adjust SDR to HDR flow
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorHDRAdjustHDR10Proc(EnumDisplayRegion enumDisplayRegion)
{
    EnumSelRegion enumSelRegion = (EnumSelRegion)enumDisplayRegion;

    WORD usColorFunction = (_COLOR_FUNCTION_ULTRA_VIVID |
                            _COLOR_FUNCTION_LIGHT_ENHANCE |
                            _COLOR_FUNCTION_DCC |
                            _COLOR_FUNCTION_COLOR_ENHANCE |
                            _COLOR_FUNCTION_ICM |
                            _COLOR_FUNCTION_LOCAL_CONTRAST |
                            _COLOR_FUNCTION_CTS_BRI);

    if(UserInterfaceColorHDRGetHDRDemoModeEnable() == _HDR_DEMO_ON)
    {
        enumSelRegion = _DEMO_INSIDE;
    }

    UserCommonColorMultiFunctionRegionEnableStart(enumSelRegion, usColorFunction);

#if(_ULTRA_VIVID_FUNCTION == _ON)
    UserCommonColorUltraVividAdjust(enumSelRegion);
#endif

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
    UserCommonColorHDRAdjustHDR10LightEnhance(enumSelRegion, _DB_APPLY_NONE);
#elif(_DCC_FUNCTION == _ON)
    UserCommonColorDCCAdjust(enumSelRegion);
#endif

#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
    UserCommonColorHDRAdjustHDR10ColorEnhance(enumSelRegion, _DB_APPLY_NONE);
#elif(_ICM_FUNCTION == _ON)
    UserCommonColorICMAdjust(enumSelRegion);
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
    // Load Inital Table
    UserCommonColorLocalContrastInitalDataAdjust(enumSelRegion);
    UserCommonColorLocalContrastAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_CONTRAST_FUNCTION == _ON)
    UserCommonColorContrastAdjust(enumSelRegion);
#endif

#if(_BRIGHTNESS_FUNCTION == _ON)
    UserCommonColorBrightnessAdjust(enumSelRegion);
#endif

    UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegion, usColorFunction);

    if(UserCommonColorHDR10GetHDRChangeStatus(enumDisplayRegion) != _HDR10_INFO_MAX_LV_CHANGE)
    {
#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
        if(UserCommonColorHDRGetBackLightAdaptiveTMBackLightStatus() == _HDR10_BACKLIGHT_ADAPTIVE_TM_BACKLIGHT_OSD)
        {
            UserAdjustBacklight(GET_OSD_BACKLIGHT());
        }
        else
#endif
        {
            UserAdjustBacklight(_BACKLIGHT_MAX);
        }
    }
}

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get HDR10 Light Enhance Gain Value, user should return value corresponded to Light Enhance table used.
// Input Value  : EnumSelRegion
// Output Value : HDR10 Light Enhance Gain Value / 100, e.g. return 160 when actual gain value is 1.60, and Gain Value range should be 100 ~ 160!!
//--------------------------------------------------
BYTE UserInterfaceColorHDRGetHDR10LightEnhanceGain(EnumDisplayRegion enumDisplayRegion)
{
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON)
    {
        switch(GET_OSD_HDR_LIGHT_ENHANCE(UserAdjustGetOsdDisplaySelectRegion(enumDisplayRegion)))
        {
            default:
            case _HDR10_LIGHTENHANCE_OFF:
                return 100;

            case _HDR10_LIGHTENHANCE_TYPE_120:
                return 120;

            case _HDR10_LIGHTENHANCE_TYPE_140:
                return 140;

            case _HDR10_LIGHTENHANCE_TYPE_160:
                return 160;
        }
    }

    return 100;
}
#endif
#endif

//--------------------------------------------------
// Description  : Get HDR10 User Data
// Input Value  : EnumDisplayRegion, StructHDR10UserData
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorHDRGetHDR10UserData(EnumDisplayRegion enumDisplayRegion, StructHDR10UserData *pstHDR10UserData)
{
    enumDisplayRegion = enumDisplayRegion;
    pstHDR10UserData->enumHDR10UserDefineMaxPanelLvType = _HDR10_PANEL_MAX_PEAK_LV;
    pstHDR10UserData->enumHDR10Force2084MasteringLvType = _HDR10_MAX_MASTERING_LV_TYPE_1200;
    pstHDR10UserData->enumHDR10UserForceMasteringLvStatus = _USER_FORCE_MASTERING_LV_OFF;
    pstHDR10UserData->enumHDR10UserForceMaxMasteringLvType = _HDR10_MAX_MASTERING_LV_TYPE_540; // Only if user choose enumHDR10UserForceMasteringLvStatus to be _USER_FORCE_MASTERING_LV_ON, enumHDR10UserForceMaxMasteringLvType should be assigned.

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
    if(pstHDR10UserData->enumHDR10Force2084MasteringLvType == _HDR10_MAX_MASTERING_LV_TYPE_STEPLESS_TM)
    {
        pstHDR10UserData->usHDR10StepLessForce2084MasteringLv = 1200; // Only if user choose enumHDR10Force2084MasteringLvType to be _HDR10_MAX_MASTERING_LV_TYPE_STEPLESS_TM, usHDR10StepLessForce2084MasteringLv should be assigned.
    }

    pstHDR10UserData->enumHDR10MasteringLvStepLessTMStatus = _MASTERING_LV_STEPLESS_TM_OFF;

    if(pstHDR10UserData->enumHDR10MasteringLvStepLessTMStatus == _MASTERING_LV_STEPLESS_TM_ON) // Only if user choose enumHDR10MasteringLvStepLessTMStatus to be _MASTERING_LV_STEPLESS_TM_ON, usHDR10StepLessMaxMasteringLv0 should be assigned.
    {
        pstHDR10UserData->usHDR10StepLessMaxMasteringLv0 = 540;
    }
    else
#endif
    {
        pstHDR10UserData->enumHDR10MaxMasteringLv0Type = _HDR10_MAX_MASTERING_LV_TYPE_540;
    }
}

#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Eagle Sight HDR10 Adjust Full Region
// Input Value  : None
// Output Value : EnumHDR10AdjustEagleSightFullStatus
//--------------------------------------------------
EnumHDR10AdjustEagleSightFullStatus UserInterfaceColorHDRGetEagleSightAdjustFullRegion(void)
{
    if((GET_OSD_SELECT_REGION() == _OSD_SR_2P_PIP_EAGLE_SIGHT_FULL) || (GET_OSD_SYSTEM_SELECT_REGION() == _FULL_REGION))
    {
        return _HDR10_ADJUST_EAGLE_SIGHT_FULL_REGION_ON;
    }
    return _HDR10_ADJUST_EAGLE_SIGHT_FULL_REGION_OFF;
}
#endif
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust SDR to FreeSync II flow
// Input Value  : EnumDisplayRegion enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorHDRAdjustFreeSyncIIProc(EnumDisplayRegion enumDisplayRegion)
{
    EnumSelRegion enumSelRegion = (EnumSelRegion)enumDisplayRegion;
    WORD usColorFunction = (_COLOR_FUNCTION_ULTRA_VIVID |
                            _COLOR_FUNCTION_LIGHT_ENHANCE |
                            _COLOR_FUNCTION_DCC |
                            _COLOR_FUNCTION_COLOR_ENHANCE |
                            _COLOR_FUNCTION_ICM |
                            _COLOR_FUNCTION_LOCAL_CONTRAST |
                            _COLOR_FUNCTION_CTS_BRI);

    if(UserInterfaceColorHDRGetHDRDemoModeEnable() == _HDR_DEMO_ON)
    {
        enumSelRegion = _DEMO_INSIDE;
    }

    UserCommonColorMultiFunctionRegionEnableStart(enumSelRegion, usColorFunction);

#if(_ULTRA_VIVID_FUNCTION == _ON)
    UserCommonColorUltraVividAdjust(enumSelRegion);
#endif

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
    UserCommonColorHDRAdjustHDR10LightEnhance(enumSelRegion, _DB_APPLY_NONE);
#elif(_DCC_FUNCTION == _ON)
    UserCommonColorDCCAdjust(enumSelRegion);
#endif

#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
    UserCommonColorHDRAdjustHDR10ColorEnhance(enumSelRegion, _DB_APPLY_NONE);
#elif(_ICM_FUNCTION == _ON)
    UserCommonColorICMAdjust(enumSelRegion);
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
    // Load Inital Table
    UserCommonColorLocalContrastInitalDataAdjust(enumSelRegion);
    UserCommonColorLocalContrastAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_CONTRAST_FUNCTION == _ON)
    UserCommonColorContrastAdjust(enumSelRegion);
#endif

#if(_BRIGHTNESS_FUNCTION == _ON)
    UserCommonColorBrightnessAdjust(enumSelRegion);
#endif

    UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegion, usColorFunction);
}
#endif // End of #if(_FREESYNC_II_SUPPORT == _ON)

#if(_ADVANCED_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Decide whether to Enable Advanced HDR10 Function
// Input Value  : EnumDisplayRegion
// Output Value : _ON or _OFF
//--------------------------------------------------
EnumAdvancedHDR10Support UserInterfaceColorHDRGetAdvancedHDR10Enable(EnumDisplayRegion enumDisplayRegion)
{
    EnumHDR10ModeDef enumHDR10ModeDef = UserInterfaceColorHDRGetHDR10ModeStatus(SysRegionGetInputPort(enumDisplayRegion));

#if(_HLG_SUPPORT == _ON)
    if((enumHDR10ModeDef == _HDR10_MODE_AUTO) || (enumHDR10ModeDef == _HDR10_HLG_MODE_AUTO))
#else
    if(enumHDR10ModeDef == _HDR10_MODE_AUTO)
#endif
    {
        return _ADVANCED_HDR10_SUPPORT_ON;
    }
    else
    {
        return _ADVANCED_HDR10_SUPPORT_OFF;
    }
}
#endif
#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
