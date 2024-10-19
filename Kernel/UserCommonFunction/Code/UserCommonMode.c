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
// ID Code      : UserCommonMode.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_MODE__

#include "UserCommonInclude.h"
#include "Mode/UserCommonMode.h"

#if(_PANEL_EXIST_MULTIPANEL == _OFF)
#if(GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH)
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
#warning "NOTE: Because of HW limitation, Main & Sub Region is force to do 1/2 HSD when Pixel Clock of Input Timing > 1400M or Input Timing Hwidth > 5120. It will lead to low picture quality in PBP TB Mode!"
#warning "NOTE: Because of HW limitation, Part of Timing would be abnormal in PBP TB Mode!"
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
#warning "NOTE: Because of HW limitation, Main Region is force to do 1/2 HSD when Pixel Clock of Input Timing > 1400M or Input Timing Hwidth > 5120. It will lead to low picture quality in 3P SkewT/B Mode!"
#endif
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructRegionUserInfoType g_pstModetRegionUserInfo[_MULTI_DISPLAY_MAX];

#if(_VGA_SUPPORT == _ON)
BYTE g_ucModeVgaCheckCounter;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get backlight staus when performing display setting
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
EnumBacklightAction UserCommonModeDisplaySettingGetBacklightAction(void)
{
#if(_2P_FRAME_SYNC_SUPPORT == _ON)
    if(ScalerFRC2PFrameSyncBypassFrameSyncRegion() == _TRUE)
    {
        return _BACKLIGHT_ENABLE;
    }
    else
#endif
    {
        if(GET_FORCE_DISPLAY_1P_MODE() == _FALSE)
        {
            return _BACKLIGHT_ENABLE;
        }
    }

#if((_PANEL_STYLE == _PANEL_VBO) && (_VBO_BACKLIGHT_BY_USER == _DISABLE))
    return _BACKLIGHT_DISABLE;
#else
    return UserInterfaceModeDisplaySettingGetBacklightAction();
#endif
}

//--------------------------------------------------
// Description  : Color setting process in display initial
// Input Value  : display mode
// Output Value : None
//--------------------------------------------------
void UserCommonModeDisplayInitialColorProc(EnumDisplayMode enumDisplayMode)
{
#if(_COLOR_IP_I_DITHER == _ON)
    UserCommonColorIDitherDisplayInitialProc();
#endif

#if(_COLOR_IP_D_DITHER == _ON)
#if(_D_DITHER_FREERUN_EN_SUPPORT == _DISABLE)
    ScalerColorDDitherEnable(_FUNCTION_ON);
#endif
#endif

#if(_COLOR_IP_DCC == _ON)
    ScalerColorDCCEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorDCCSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_ICM == _ON)
    ScalerColorICMEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorICMSCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_DCR == _ON)
    ScalerColorDCREnable(_FUNCTION_ON);
    // Only one set, no need to reset set_sel setting.
#endif

#if(_COLOR_IP_CONTRAST == _ON)
    ScalerColorContrastEnable(_FUNCTION_ON);
#endif

#if(_COLOR_IP_BRIGHTNESS == _ON)
    ScalerColorBrightnessEnable(_FUNCTION_ON);
#endif

#if((_COLOR_IP_CONTRAST == _ON) || (_COLOR_IP_BRIGHTNESS == _ON))
    ScalerColorBrightnessContrastHLWSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NONE);
#endif

#if(_COLOR_IP_IAPS == _ON)
    ScalerColorIAPSGainEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorIAPSGainSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
    ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
    // Only one set, no need to reset set_sel setting.
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
    ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorPostGammaSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
    ScalerColorOutputGammaEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorGammaSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_SRGB == _ON)
    ScalerColorSRGBEnable(_FUNCTION_ON);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorSRGBSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NONE);
#endif
#endif

#if(_COLOR_IP_UNIFORMITY == _ON)
    ScalerColorPanelUniformityEnable(_FUNCTION_ON);
    // Only one set, no need to reset set_sel setting.
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    ScalerColorLocalContrastFBInital();
#endif
    ScalerColorLocalContrastEnable(_FULL_REGION, _LOCAL_CONTRAST_ALL_FUNCTION_ON);
    // Only one set, no need to reset set_sel setting.
#endif

#if(_COLOR_IP_HL_WIN == _ON)
    ScalerColorHLWDDomainEnable(_FUNCTION_ON);
#endif

#if(_COLOR_IP_BORDER_WIN == _ON)
    // Draw border
    {
        StructColorBorderWindowSetting stBorderWindow = {0};

        UserCommonColorGetBorderWindowData(&stBorderWindow);
        ScalerColorIPBorderWindowAdjust(&stBorderWindow, _DB_APPLY_NONE);
    }
#endif

#if(_COLOR_IP_MRCM == _ON)
    UserCommonColorMRCMDefaultSetting();
    UserCommonColorMRCMAdjust();
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
    if(UserCommonNVRamGetSystemData(_COLORIMETRY_SEAMLESS_CHANGE) == _TRUE)
    {
        EnumDisplayMode enumDisplayModeTrans = enumDisplayMode;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        enumDisplayModeTrans = ScalerRegionEagleSightTransDisplayMode(enumDisplayModeTrans);
#endif

        if(enumDisplayModeTrans == _DISPLAY_MODE_1P)
        {
            CLR_DIGITAL_COLOR_INFO_CHANGE_RESET();
        }
        else
        {
            SET_DIGITAL_COLOR_INFO_CHANGE_RESET();
        }
    }
    else
    {
        SET_DIGITAL_COLOR_INFO_CHANGE_RESET();
    }
#endif
#endif

    UserInterfaceModeDisplayInitialColorProc(enumDisplayMode);
}

//--------------------------------------------------
// Description  : Modify display Timing Based on User Requirement
// Input Value  : Display Region
// Output Value : None
//--------------------------------------------------
void UserCommonModeDisplaySettingInitialization(EnumDisplayRegion enumDisplayRegion)
{
    UserInterfaceModeDisplaySettingInitialization(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Set color in bypass normal active process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonModeDisplaySettingByPassColorProc(EnumDisplayRegion enumDisplayRegion)
{
#if(_I_DITHER_FUNCTION == _ON)
    // Adjust I Dithering
#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_0)
    ScalerColorScalingDownSetMaskLSB(ScalerRegionGetInputDataPath(enumDisplayRegion));
#endif

    if(ScalerColorIDitherGetTableSetNum() == 1)
    {
        UserCommonColorIDitherReloadTable((EnumSelRegion)enumDisplayRegion, ScalerMDomainGetColorDepth());
    }

    ScalerColorIDitherTableSelect((EnumSelRegion)enumDisplayRegion, ScalerMDomainGetColorDepth());
#endif

#if(_OD_FUNCTION == _ON)
    UserCommonColorODEnable(UserInterfaceColorGetODEnableStatus());
#endif

#if(_SHARPNESS_FUNCTION == _ON)
    UserCommonColorSharpnessAdjust((EnumSelRegion)enumDisplayRegion, _DB_APPLY_NO_POLLING);
#endif

#if(_SD_TABLE_SEL_FUNCTION == _ON)
    UserCommonColorScalingDownCoefAdjust((EnumSelRegion)enumDisplayRegion);
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
    if(ScalerColorLocalContrastCheckRegionSupport((EnumSelRegion)enumDisplayRegion) == _TRUE)
    {
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
        ScalerColorLocalContrastBacklightDecision((EnumSelRegion)enumDisplayRegion, UserCommonColorLocalContrastReadYavgStatus());
#else
        ScalerColorLocalContrastBacklightDecision((EnumSelRegion)enumDisplayRegion, _LOCALCONTRAST_READYAVG_DISABLE);
#endif
    }
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
    UserCommonColorLocalDimmingAdjust();
#endif

#if((_DM_FUNCTION == _ON) && (_IS_MAIN_PROCESS_CPU == _TRUE))
    if(UserCommonColorDMGetDMStatus(enumDisplayRegion) == _TRUE)
    {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(enumDisplayRegion != _DISPLAY_RGN_EAGLE_SIGHT_SUB)
#endif
        {
            ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_DM, ScalerRegionGetInputDataPath(enumDisplayRegion), _ENABLE);
        }
    }
#endif

#if(_COLOR_IP_HL_WIN == _ON)
    UserCommonColorHLWinTypeAdjust(_DB_APPLY_NO_POLLING);
#endif

    UserInterfaceModeDisplaySettingByPassColorProc(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Set User Required Single Setting Color Process
// Input Value  : enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonModeDisplaySettingSingleColorProc(EnumDisplayRegion enumDisplayRegion)
{
    EnumInputPort enumInputPort = SysRegionGetInputPort(enumDisplayRegion);

#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
    UserCommonColorRGBQuantizationRangeAdjust(enumDisplayRegion);
#endif

#if(_YCC_QUANTIZATION_RANGE_FUNCTION == _ON)
    UserCommonColorYCCQuantizationRangeAdjust(enumDisplayRegion);
#endif

#if(_COLOR_IP_COLOR_CONVERT == _ON)
#if(_COLOR_FORMAT_CONVERT_FUNCTION == _ON)
    // Set Color Format when specific region not first active
    UserInterfaceColorSetColorFormat(enumDisplayRegion, enumInputPort);
#endif

    EnumColorSpace enumColorSpace = ((UserInterfaceColorGetColorRGBFormat(enumDisplayRegion) == _RGB_FORMAT_TRUE) ? _COLOR_SPACE_RGB : _COLOR_SPACE_YPBPR);

#if(_COLOR_IP_3DDI == _ON)
    // Set 3DDI RGB2YUV
    Scaler3DDISetRGB2YUV(enumDisplayRegion, enumInputPort, enumColorSpace);
#endif

    UserCommonColorLoadYuv2RgbTable(enumDisplayRegion, _DB_APPLY_NONE);

    // Adjust Color Space
    UserCommonColorFormatConvert(enumDisplayRegion, enumInputPort, enumColorSpace, _DB_APPLY_NO_POLLING);
#endif

    // Adjust VGA Color Functions
#if(_VGA_SUPPORT == _ON)
    UserCommonColorVgaProc();
#endif  // End of #if(_VGA_SUPPORT == _ON)

    // Color Sampling
#if(_COLOR_IP_DM == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(UserCommonColorDMGetDMStatus(enumDisplayRegion) == _TRUE)
    {
        ScalerColor422To444DM(enumInputPort, enumDisplayRegion, _OFF);
    }
    else
#endif
#endif
    {
        ScalerColor422To444(enumInputPort, enumDisplayRegion);
    }

#if(_I_DITHER_FUNCTION == _ON)
    // Adjust I Dithering
#if(_HW_SCALING_DOWN_TYPE == _SD_GEN_0)
    ScalerColorScalingDownSetMaskLSB(ScalerRegionGetInputDataPath(enumDisplayRegion));
#endif

    if(ScalerColorIDitherGetTableSetNum() == 1)
    {
        UserCommonColorIDitherReloadTable((EnumSelRegion)enumDisplayRegion, ScalerMDomainGetColorDepth());
    }

    ScalerColorIDitherTableSelect((EnumSelRegion)enumDisplayRegion, ScalerMDomainGetColorDepth());
#endif

#if(_OD_FUNCTION == _ON)
    UserCommonColorODAdjust();
#endif

#if(_COLOR_IP_HL_WIN == _ON)
    {
        StructColorHLWSetting stHLW = {0};

        UserCommonColorGetHLWData(&stHLW);
        ScalerColorIPHLWAdjust(&stHLW, _DB_APPLY_NONE);
    }
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
    UserCommonColorDColorConvertAdjust((EnumSelRegion)enumDisplayRegion, _DB_APPLY_NO_POLLING);
#endif

#if(_COLOR_IP_ANTI_ALIASING == _ON)
    UserCommonColorAntiAliasingAdjust((EnumSelRegion)enumDisplayRegion);
#endif
}

//--------------------------------------------------
// Description  : Set User Required Color Process
// Input Value  : enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonModeDisplaySettingColorProc(EnumDisplayRegion enumDisplayRegion)
{
    CLR_ALL_COLOR_FUNCTION_REGION_ENABLE();

#if(_COLOR_PROCESS_CONTROL_BY_USER == _ON)
    UserInterfaceModeDisplaySettingColorProc(enumDisplayRegion);
#else

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
    UserCommonColorDMFormatChgWoResetInitial(enumDisplayRegion);
#endif

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
#if(_DIGITAL_PORT_SUPPORT == _ON)
    {
        EnumDisplayMode enumDisplayMode = SysModeGetDisplayMode();
        bit bFreeSyncEn = _OFF;
        EnumDMSupport enumDMEn = _OFF;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

#if(_FREESYNC_SUPPORT == _ON)
        bFreeSyncEn = ScalerDrrFreeSyncGetInfo(SysSourceGetInputPort(), _SPD_INFO_FREESYNC_SUPPORT);
#endif

#if(_DM_FUNCTION == _ON)
        enumDMEn = UserCommonColorDMGetEnableStatus(enumDisplayRegion);
#endif
        if(UserCommonModeColorimetrySeamlessChangeCheckBypass(SysSourceGetInputPort()) == _FALSE)
        {
            if((enumDisplayMode == _DISPLAY_MODE_1P) && (bFreeSyncEn == _OFF) && (enumDMEn == _DM_SUPPORT_OFF))
            {
                SET_DIGITAL_COLOR_INFO_CHANGE_RESET();
            }
        }
    }
#endif

    UserCommonColorSeamlessChgInitial(enumDisplayRegion);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
    {
        // If color setting is related to eagle sight sub timing, it should be set here.
#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
        ScalerColorLocalContrastBacklightDecision(_2P_PIP_EAGLE_SIGHT_SUB, UserCommonColorLocalContrastReadYavgStatus());
#else
        ScalerColorLocalContrastBacklightDecision(_2P_PIP_EAGLE_SIGHT_SUB, _LOCALCONTRAST_READYAVG_DISABLE);
#endif
#endif

#if(_COLOR_IP_SHARPNESS == _ON)
        UserCommonColorSharpnessAdjust(_2P_PIP_EAGLE_SIGHT_SUB, _DB_APPLY_NONE);
#endif
        UserCommonDisplayEagleSightAdjust(_EAGLE_SIGHT_TRANSPARENCY);
    }
#endif

    if(UserInterfaceModeGetActiveByPassStatus(enumDisplayRegion) == _BYPASS_COLOR_PROC_TRUE)
    {
        UserCommonModeDisplaySettingByPassColorProc(enumDisplayRegion);
        return;
    }

#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(SysModeGetDisplayMode() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN)
        {
            UserCommonColorHDRInitialSetting(enumDisplayRegion);
        }
    }
    else
#endif
    {
        UserCommonColorHDRInitialSetting(enumDisplayRegion);
    }
#if(_ADVANCED_HDR10_SUPPORT == _ON)
    UserCommonColorAdvancedHDR10InitialSetting();
#endif
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    UserCommonColorDMInitialSetting(enumDisplayRegion);
#endif
#endif

    if(ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP) == _FALSE)
    {
        return;
    }

#if(_COLOR_DEMO_FUNCTION == _ON)
    if(UserCommonColorGetDemoModeType() != _DEMO_OFF)
    {
        UserCommonModeDisplaySettingDemoModeColorProc(enumDisplayRegion);   // Demo mode flow
    }
    else
#endif
    {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(SysModeGetDisplayMode() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
            {
#if(_OD_FUNCTION == _ON)
                UserCommonColorODAdjust();
#endif

#if(_EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT == _ON)
                UserCommonModeSetESOriginalModeSUFI(enumDisplayRegion);
#endif
#if(_SD_TABLE_SEL_FUNCTION == _ON)
                StructColorScalingDownCoefSetting stScalingDownData = {0};
                UserCommonColorGetScalingDownCoef((EnumSelRegion)enumDisplayRegion, &stScalingDownData);
                ScalerColorIPScalingDownCoefAdjust((EnumSelRegion)enumDisplayRegion, &stScalingDownData);
#endif
            }
            else
            {
                UserCommonModeDisplaySettingNormalModeColorProc(enumDisplayRegion); // Normal mode flow
#if(_ULTRA_HDR_SUPPORT == _ON)
                UserCommonColorHDRInitialSetting(_DISPLAY_RGN_EAGLE_SIGHT_SUB);
#endif
                UserCommonModeDisplaySettingNormalModeColorProc(_DISPLAY_RGN_EAGLE_SIGHT_SUB); // Normal mode flow
            }
        }
        else
#endif
        {
            UserCommonModeDisplaySettingNormalModeColorProc(enumDisplayRegion); // Normal mode flow
        }
    }

    UserInterfaceModeDisplaySettingColorProc(enumDisplayRegion);


#if(_LOCAL_DIMMING_FUNCTION == _ON)
    UserCommonColorLocalDimmingAdjust();
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN)
        {
            UserCommonColorGlobalDimmingAdjust();
        }
        else
        {
            UserCommonColorGlobalDimmingSetForceMainEffect();
        }
    }
    else
#endif
    {
        UserCommonColorGlobalDimmingAdjust();
    }
#endif
#endif
}

//--------------------------------------------------
// Description  : Set User Required Multi Setting Color Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonModeDisplaySettingMultiColorProc(EnumSelRegion enumSelRegion)
{
    UserCommonColorBypassHLWSelRegionColorFunction(enumSelRegion);

#if(_COLOR_IP_SHARPNESS == _ON)
    {
        StructColorSharpnessSetting stSharpness = {0};

        UserCommonColorGetSharpnessData(enumSelRegion, &stSharpness);
        ScalerColorIPSharpnessAdjust(enumSelRegion, &stSharpness, _DB_APPLY_NO_POLLING);
    }
#endif

#if(_SD_TABLE_SEL_FUNCTION == _ON)
    {
        StructColorScalingDownCoefSetting stScalingDownData = {0};
        UserCommonColorGetScalingDownCoef(enumSelRegion, &stScalingDownData);
        ScalerColorIPScalingDownCoefAdjust(enumSelRegion, &stScalingDownData);
    }
#endif

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
    {
        StructColorUltraVividSetting stUltraVividData = {0};

        UserCommonColorGetUltraVividData(enumSelRegion, &stUltraVividData);
        ScalerColorIPUltraVividAdjust(enumSelRegion, &stUltraVividData);

        if(stUltraVividData.stUltraVividSetting.enumUltraVividMode != _ULTRAVIVID_OFF)
        {
            UserCommonColorUltraVividRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
    }
#endif

#if(_COLOR_IP_DCR == _ON)
    {
        StructColorDCRSetting stDCR = {0};

        UserCommonColorGetDCRData(&stDCR);
        ScalerColorIPDCRAdjust(&stDCR);
    }
#endif


#if(_COLOR_IP_MRCM == _ON)
    UserCommonColorMRCMDefaultSetting();
    UserCommonColorMRCMAdjust();
#endif

#if(_COLOR_IP_ICM == _ON)
    {
        StructColorICMSetting stICM = {0};

        UserCommonColorGetICMData(enumSelRegion, &stICM);
        ScalerColorIPICMAdjust(enumSelRegion, &stICM);

#if(_HW_ICM_DB_TYPE == _ICM_DB_GEN_0)
        if(stICM.stICMSetting.enumICMMode != _ICM_OFF)
        {
            UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
#else
        // Always keep region _ON when ICM _OFF(need to load lc bypass table), so not need to polling region apply
        UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
#endif
    }
#endif

#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
    {
        StructColorDCCHistogramSetting stDCCHistogram = {0};

        UserCommonColorGetDCCHistogramData(&stDCCHistogram);
        ScalerColorIPDCCHistogramAdjust(&stDCCHistogram);
    }
#endif

#if(_COLOR_IP_DCC == _ON)
    {
        StructColorDCCSetting stDCC = {0};

        UserCommonColorGetDCCData(enumSelRegion, &stDCC);
        ScalerColorIPDCCAdjust(enumSelRegion, &stDCC);

        if(stDCC.stDCCSetting.enumDCCMode != _DCC_OFF)
        {
            UserCommonColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
    }
#endif

#if(_COLOR_IP_IAPS == _ON)
    {
        StructColorIAPSSetting stIAPS = {0};

        UserCommonColorGetIAPSData(enumSelRegion, &stIAPS);
        ScalerColorIPIAPSAdjust(enumSelRegion, &stIAPS);

        if(stIAPS.stIAPSSetting.enumIAPSMode != _IAPS_OFF)
        {
            UserCommonColorIAPSRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
    }
#endif

#if(_COLOR_IP_CONTRAST == _ON)
    {
        StructColorCtsSetting stCts = {0};
        UserCommonColorGetContrastData(enumSelRegion, &stCts);
        ScalerColorIPContrastAdjust(enumSelRegion, &stCts);
        UserCommonColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        ScalerColorContrastEnable(_FUNCTION_ON);
    }
#endif

#if(_COLOR_IP_BRIGHTNESS == _ON)
    {
        StructColorBriSetting stBri = {0};
        UserCommonColorGetBrightnessData(enumSelRegion, &stBri);
        ScalerColorIPBrightnessAdjust(enumSelRegion, &stBri);
        UserCommonColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        ScalerColorBrightnessEnable(_FUNCTION_ON);
    }
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
    {
        StructColor3DGammaSetting st3DGamma = {0};

        UserCommonColorGet3DGammaData(enumSelRegion, &st3DGamma);

        ScalerColorIP3DGammaAdjust(&st3DGamma);

        if(st3DGamma.st3DGammaSetting.enum3DGammaMode != _3DGAMMA_OFF)
        {
            UserCommonColor3DGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
    }
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
    {
        StructColorInGammaSetting stInGamma = {0};

        UserCommonColorGetInGammaData(enumSelRegion, &stInGamma);
        ScalerColorIPInGammaAdjust(enumSelRegion, &stInGamma, _IG_DB_DISABLE);

        if(stInGamma.stInGammaSetting.enumInGammaMode != _INGAMMA_OFF)
        {
            UserCommonColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
    }
#endif

#if(_COLOR_IP_YMAPPING == _ON)
    {
        StructColorYmappingSetting stYmappingData = {0};

        UserCommonColorGetYmappingData(enumSelRegion, &stYmappingData);
        ScalerColorIPYmappingAdjust(enumSelRegion, &stYmappingData);
    }
#endif

#if(_COLOR_IP_SRGB == _ON)
    {
        StructColorSRGBSetting stSRGB = {0};

        UserCommonColorGetsRGBData(enumSelRegion, &stSRGB);
        ScalerColorIPSRGBAdjust(enumSelRegion, &stSRGB);

        if(stSRGB.stSRGBSetting.enumSRGBMode != _SRGB_OFF)
        {
            UserCommonColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
    }
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
    {
        StructColorPostGammaSetting stPostGamma = {0};
        ScalerColorPostGammaEnable(enumSelRegion, _FUNCTION_OFF);

        UserCommonColorGetPostGammaData(enumSelRegion, &stPostGamma);
        ScalerColorIPPostGammaAdjust(enumSelRegion, &stPostGamma);
    }
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
    {
        StructColorOutGammaSetting stOutGamma = {0};

        UserCommonColorGetOutGammaData(enumSelRegion, &stOutGamma);
        ScalerColorIPOutGammaAdjust(enumSelRegion, &stOutGamma);

        if(stOutGamma.stOutGammaSetting.enumOutGammaMode != _OUTGAMMA_OFF)
        {
            UserCommonColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }

#if(_COLOR_IP_LOCAL_DIMMING == _ON)
        if(stOutGamma.stOutGammaSetting.enumOutGammaMode != _OUTGAMMA_HDR10)
        {
            UserCommonColorLocalDimmingHistoLUTAdjust(_LOCAL_DIMMING_SDR);
        }
        else
        {
            UserCommonColorLocalDimmingHistoLUTAdjust(_LOCAL_DIMMING_HDR);
        }
#endif
    }
#endif

#if(_COLOR_IP_UNIFORMITY == _ON)
    {
        StructColorUniformitySetting stUniData = {0};

        UserCommonColorGetUniformityData(enumSelRegion, &stUniData);
        ScalerColorIPUniformityAdjust(&stUniData);
        if(stUniData.stUniformitySetting.enumUniformityMode != _UNIFORMITY_OFF)
        {
            UserCommonColorPanelUniformityRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
        else
        {
            // get data update lowblue setting struct
            UserCommonColorLowBlueGetData(&g_stColorDynamicLowBlueSetting);
            UserCommonColorLowBlueInitial();
            // check low blue setting struct status is enable
            if(UserCommonColorGetLowBlueStatus() != _LOWBLUE_MODE_OFF)
            {
                UserCommonColorLowBlueAdjust(enumSelRegion);
            }
        }
#endif
    }
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
    {
        if(ScalerColorLocalContrastCheckRegionSupport(enumSelRegion) == _TRUE)
        {
            StructColorLocalContrastSetting stLocalContrast = {0};

            // LocalContrast Temporal data
            StructColorLocalContrastTemporalSetting stLocalContrastTemporal = {0};

            UserCommonColorGetLocalContrastData(enumSelRegion, &stLocalContrast);
            UserCommonColorGetLocalContrastTemporalData(enumSelRegion, &stLocalContrastTemporal);

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
            ScalerColorLocalContrastBacklightDecision(enumSelRegion, UserCommonColorLocalContrastReadYavgStatus());
#else
            ScalerColorLocalContrastBacklightDecision(enumSelRegion, _LOCALCONTRAST_READYAVG_DISABLE);
#endif

            // Load Inital Table
            UserCommonColorLocalContrastInitalDataAdjust(enumSelRegion);

            // Load Tone-mapping/Sharpness/CDM Table
            ScalerColorIPLocalContrastAdjust(enumSelRegion, &stLocalContrast);

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
            // Load Temporal Table
            ScalerColorIPLocalContrastTemporalAdjust(enumSelRegion, &stLocalContrastTemporal, UserCommonColorLocalContrastReadYavgStatus());
#else
            // Load Temporal Table
            ScalerColorIPLocalContrastTemporalAdjust(enumSelRegion, &stLocalContrastTemporal, _LOCALCONTRAST_READYAVG_DISABLE);
#endif

#if(_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON)
            // Calculate new TM Blending Factor & new Ydiff Gain in User mode
            if((stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_HDR10_USER) && (stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.enumLocalContrastBlendingStatus == _LOCALCONTRAST_BLENDING_ENABLE))
            {
                ScalerColorLocalContrastToneMappingGainAdjust(enumSelRegion, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.ucTMFactor);

                // Recalculate ydiff devisor in User mode
                stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucYdiffdevisor = ScalerColorLocalContrastYdiffDevisorAdjust(enumSelRegion, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucBank);
                ScalerColorLocalContrastYdiffGainAdjust(enumSelRegion, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.pucTable, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastHDR10UserData.ucYdiffgainFactor, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastHDR10Data.ucYdiffdevisor);
            }
            else if((stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_USER) && (stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.enumLocalContrastBlendingStatus == _LOCALCONTRAST_BLENDING_ENABLE))
            {
                ScalerColorLocalContrastToneMappingGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucTMFactor);

                // Recalculate ydiff devisor in User mode
                stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor = ScalerColorLocalContrastYdiffDevisorAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucBank);
                ScalerColorLocalContrastYdiffGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastUserData.ucYdiffgainFactor, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor);
            }
#endif

#if(_SDR_PLUS_FUNCTION == _ON)
            // Calculate new TM Blending Factor & new Ydiff Gain in SDR+ Adjust mode
            if((stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_SDR_PLUS) && (stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.enumLocalContrastBlendingStatus == _LOCALCONTRAST_BLENDING_ENABLE))
            {
                ScalerColorLocalContrastToneMappingGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucTMFactor);

                // Recalculate ydiff devisor in User mode
                stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor = ScalerColorLocalContrastYdiffDevisorAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucBank);
                ScalerColorLocalContrastYdiffGainAdjust(enumSelRegion, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.pucTable, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucBank, stLocalContrast.stLocalContrastSetting.unLocalContrastData.stLocalContrastSDRPlusData.ucYdiffgainFactor, stLocalContrast.unKernelLocalContrastData.stKernelLocalContrastUserData.ucYdiffdevisor);
            }
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
            UserCommonColorLocalContrastSetSceneChangeTHD(enumSelRegion);
#endif
#endif
            if(stLocalContrast.stLocalContrastSetting.enumLocalContrastMode == _LOCALCONTRAST_OFF)
            {
                // bypass lc bypass table
                ScalerColorLocalContrastBypass(enumSelRegion);

                // lc bypass table not include Tone-mapping curve, use "_LOCAL_CONTRAST_EXCLUDE_TONEMAPPING_CURVE_APPLY"
                ScalerColorLocalContrastTableDBApply(enumSelRegion, _LOCAL_CONTRAST_EXCLUDE_TONEMAPPING_CURVE_APPLY, _DB_APPLY_NO_POLLING);
            }
            else
            {
                // lc normal table include both Tone-mapping curve and regs, use "_LOCAL_CONTRAST_ALL_APPLY"
                ScalerColorLocalContrastTableDBApply(enumSelRegion, _LOCAL_CONTRAST_ALL_APPLY, _DB_APPLY_NO_POLLING);
            }

            UserCommonColorLocalContrastRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
    }


#endif
}

//--------------------------------------------------
// Description  : OSD Fix Active Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonModeDisplayActiveProc(EnumDisplayRegion enumDisplayRegion)
{
#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
    EnumDisplayMode enumDisplayModeTrans = (EnumDisplayMode)GET_RGN_DISPLAY_MODE(enumDisplayRegion);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayModeTrans = ScalerRegionEagleSightTransDisplayMode(enumDisplayModeTrans);
#endif
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        UserCommonDisplayHPositionAdjust(GET_VGA_MODE_ADJUST_H_POSITION(), enumDisplayRegion);
        UserCommonDisplayVPositionAdjust(GET_VGA_MODE_ADJUST_V_POSITION(), enumDisplayRegion);
        UserCommonVgaClockAdjust(GET_VGA_MODE_ADJUST_CLOCK());
        UserCommonVgaPhaseAdjust(GET_VGA_MODE_ADJUST_PHASE());
    }
#endif

#if(_FRC_SUPPORT == _ON)
    ScalerFRCWaitWriteFrameBufFinish();
#endif

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
    if(enumDisplayModeTrans == _DISPLAY_MODE_1P)
    {
        SET_FREE_RUN_DDOMAIN_SETTING(UserInterfaceDisplayFreeRunDclkSettingSelect());
    }
    else
    {
        SET_FREE_RUN_DDOMAIN_SETTING(_DEFAULT_FREERUN_DDOMAIN_SETTING);
    }
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    UserCommonColorDMActiveProc(enumDisplayRegion, _DM_CHK_FIRST_ACTIVE);
#endif
#endif

    UserInterfaceModeDisplayActiveProc(enumDisplayRegion);

#if(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
    // black frame insertion setting only on main region
    if(ScalerRegionGetIndex(enumDisplayRegion) == _REGION_INDEX_0)
    {
        UserCommonDisplayMbrBlackFrameInsertAdjust();
    }
#endif

    ScalerGlobalWaitDDomainDBApplyFinish();
}

//--------------------------------------------------
// Description  : Reset process for display region
// Input Value  : display region
// Output Value : None
//--------------------------------------------------
void UserCommonModeResetRegionProc(EnumDisplayRegion enumDisplayRegion)
{
    bit bPanelOff = _FALSE;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN)
    {
        bPanelOff = _TRUE;
    }
    else
#endif
    {
        if(enumDisplayRegion == _DISPLAY_RGN_1P)
        {
            bPanelOff = _TRUE;
        }
    }

    if(bPanelOff == _TRUE)
    {
#if(_LOCAL_DIMMING_FUNCTION == _ON)
        UserCommonColorLocalDimmingEnable(_OFF);
#elif(_GLOBAL_DIMMING_FUNCTION == _ON)
        UserInterfaceColorGlobalDimmingRestoreBacklight();
#endif
        // Turn off backlight
        if(UserInterfaceDisplayGetLogoStatus() == _OSD_LOGO_OFF)
        {
#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
            UserCommonPowerPanelAction(_BACKLIGHT_OFF);
#else
            UserCommonPowerPanelAction(_PANEL_OFF);
#endif
        }

        UserInterfaceModeResetProc();
    }

#if(_AUDIO_SUPPORT == _ON)
    UserCommonAudioResetRegionProc(enumDisplayRegion);
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetInputPort(enumDisplayRegion) == _A0_INPUT_PORT)
    {
        // Reset VGA check counter
        g_ucModeVgaCheckCounter = 30;

#if(_DIGITAL_FILTER_SUPPORT == _ON)
#if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
        // Reset digital filter
        ScalerColorDigitalFilterEnable(_FUNCTION_OFF);
#endif
#endif

#if(_RINGING_FILTER_FUNCTION == _ON)
#if(_HW_RINGING_FILTER_TYPE != _GEN_NONE)
        // Reset ringing filter
        ScalerColorRingingFilterOff();
#endif
#endif
    }
#endif

    UserInterfaceModeResetRegionProc(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Resume from NSG process for display region
// Input Value  : display region
// Output Value : None
//--------------------------------------------------
void UserCommonModeResumeRegionProc(EnumDisplayRegion enumDisplayRegion)
{
    bit bCheckDisplayRegion = _FALSE;

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
    if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
    {
        if((GET_2P_FRAME_SYNC_MAIN() == _TRUE) && (SysRegionGetDisplayRegionIndex(enumDisplayRegion) == _REGION_INDEX_0))
        {
            bCheckDisplayRegion = _TRUE;
        }
        else if((GET_2P_FRAME_SYNC_MAIN() == _FALSE) && (SysRegionGetDisplayRegionIndex(enumDisplayRegion) == _REGION_INDEX_1))
        {
            bCheckDisplayRegion = _TRUE;
        }
    }
    else
#endif
    {
        if(enumDisplayRegion == _DISPLAY_RGN_1P)
        {
            bCheckDisplayRegion = _TRUE;
        }
    }

    if((bCheckDisplayRegion == _TRUE) && (SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK))
    {
        // Turn off backlight
#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
        UserCommonPowerPanelAction(_BACKLIGHT_OFF);
#else
        UserCommonPowerPanelAction(_PANEL_OFF);
#endif

        UserInterfaceModeResetProc();
    }

    UserInterfaceModeResumeRegionProc(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : OSD Fix Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonModeResetProc(void)
{
    // Turn off backlight
    if(UserInterfaceDisplayGetLogoStatus() == _OSD_LOGO_OFF)
    {
#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
        UserCommonPowerPanelAction(_BACKLIGHT_OFF);
#else
        UserCommonPowerPanelAction(_PANEL_OFF);
#endif
    }

#if(_HDR10_SUPPORT == _ON)
    memset(&g_pstColorHDR10Setting, 0, sizeof(g_pstColorHDR10Setting));
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    memset(&g_pstColorFreeSyncIISetting, 0, sizeof(g_pstColorFreeSyncIISetting));
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    UserCommonColorAdvancedHDR10Reset();
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    UserCommonColorDMResetProc();
#endif
#endif

#if(_AUDIO_SUPPORT == _ON)
    UserCommonAudioResetProc();
#endif

    UserInterfaceModeResetProc();

#if(_VGA_SUPPORT == _ON)
    g_ucModeVgaCheckCounter = 30;
#endif

#if(_VGA_SUPPORT == _ON)
#if(_DIGITAL_FILTER_SUPPORT == _ON)
#if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
    ScalerColorDigitalFilterEnable(_FUNCTION_OFF);
#endif
#endif

#if(_RINGING_FILTER_FUNCTION == _ON)
#if(_HW_RINGING_FILTER_TYPE != _GEN_NONE)
    ScalerColorRingingFilterOff();
#endif
#endif

#endif

#if((_EAGLE_SIGHT_SUPPORT == _ON) && (_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON))
    ScalerColorPIPBlendingSetCircleWindowEnable(_FALSE, 0);
#endif

#if(_COLOR_IP_HL_WIN == _ON)
    ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_NO_POLLING);
#endif

#if(_COLOR_IP_BORDER_WIN == _ON)
    UserCommonColorBorderWindowDisable(_DB_APPLY_NO_POLLING);
#endif

#if(_COLOR_IP_BRIGHTNESS == _ON)
    ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_CONTRAST == _ON)
    ScalerColorContrastEnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_I_DITHER == _ON)
    ScalerColorIDitherEnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_D_DITHER == _ON)
#if(_D_DITHER_FREERUN_EN_SUPPORT == _DISABLE)
    ScalerColorDDitherEnable(_FUNCTION_OFF);
#endif
#endif

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
    UserCommonColorUltraVividRegionEnable(_FULL_REGION, _DB_APPLY_NO_POLLING, _OFF);
#endif

#if(_COLOR_IP_DCC == _ON)
    ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_ICM == _ON)
    ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_DCR == _ON)
    ScalerColorDCREnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_IAPS == _ON)
    ScalerColorIAPSGainEnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
    ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
    ScalerColorPostGammaEnable(_FULL_REGION, _FUNCTION_OFF);
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_SRGB == _ON)
    ScalerColorSRGBEnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_UNIFORMITY == _ON)
    ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#endif


#if(_GLOBAL_DIMMING_FUNCTION == _ON)
    UserCommonColorGlobalDimmingInitialSetting(_DISABLE);
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
    ScalerColorLocalContrastEnable(_FULL_REGION, _LOCAL_CONTRAST_ALL_FUNCTION_OFF);
#endif

#if(_COLOR_IP_COLOR_CONVERT == _ON)
    ScalerColorSpaceConvertIDomainEnable(_DISPLAY_RGN_1P, _OFF);
    ScalerColorSpaceConvertDDomainEnable(_DISPLAY_RGN_1P, _OFF);
#endif

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    // Clear MBR mode
    ScalerMbrAdvanceClearRtkAdvMbrMode();
#endif

#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
    // Disable MBR BFI Function
    UserInterfaceDisplayMbrBlackFrameInsertCtrl(_BFI_MODE_OFF);
    ScalerMDomainBlackFrameInsertEnable(_FUNCTION_OFF, GET_MBR_BFI_AVAILABLE_MODE());
    CLR_MBR_BFI_AVAILABLE_MODE();
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
    UserInterfaceDisplaySetPixelOrbitingOff();
#endif

#if(_COLOR_IP_MRCM == _ON)
    UserCommonColorMRCMEnable(_FUNCTION_OFF);
#endif

#if(_COLOR_IP_ANTI_ALIASING == _ON)
    ScalerColorAntiAliasingClear();
#endif

#if(_OD_FUNCTION == _ON)
    // Disable OD function
    ScalerODEnable(_FUNCTION_OFF);
#endif

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
    SET_FREE_RUN_DDOMAIN_SETTING(_DEFAULT_FREERUN_DDOMAIN_SETTING);
#endif
}

//--------------------------------------------------
// Description  : User Judge Ready to Active
// Input Value  : None
// Output Value : True --> Ready to Active
//                False --> Not Ready to Active
//--------------------------------------------------
bit UserCommonModeGetReadyForActiveStatus(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
    if((GET_PANELPOWERSTATUS() != _READY_FOR_BACKLIGHT) && (GET_PANELPOWERSTATUS() != _BACKLIGHT_ON_ALREADY))
    {
        return _FALSE;
    }
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        if(UserInterfaceVgaGetFirstAutoConfigStatus() == _DO_AUTO_CONFIG_TRUE)
        {
            if((g_ucModeVgaCheckCounter > 0) && (UserCommonVgaAutoMeasureMultiTimes() == _FALSE))
            {
                g_ucModeVgaCheckCounter--;

                return _FALSE;
            }
        }
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Whther to support this timing
// Input Value  : dispaly region
// Output Value : TRUE => Go to No Support State
//--------------------------------------------------
bit UserCommonModeCheckNoSupport(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);
    EnumInputPort enumInputPort = SysRegionGetInputPort(enumDisplayRegion);
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

    SET_FAIL_SAFE_MODE(ucRegionIndex, _FALSE);

    // check non-initialized value
    if((GET_INPUT_TIMING_HWIDTH() == 0x00) ||
       (GET_INPUT_TIMING_VHEIGHT() == 0x00))
    {
        return _TRUE;
    }

    // check OOR boundary
    if((GET_INPUT_TIMING_HFREQ() < _OOR_H_FREQ_LOWER_BOUND) ||
       (GET_INPUT_TIMING_VFREQ() < _OOR_V_FREQ_LOWER_BOUND) ||
       (GET_INPUT_TIMING_VFREQ() > _OOR_V_FREQ_UPPER_BOUND) ||
       (GET_INPUT_TIMING_HWIDTH() > _OOR_H_WIDTH_UPPER_BOUND) ||
       (GET_INPUT_TIMING_VHEIGHT() < _OOR_V_HEIGHT_LOWER_BOUND))
    {
        return _TRUE;
    }

    // need check H_FREQ upper bound
    if(ScalerMeasureIgnoreHFreqCheck(enumInputPort) != _TRUE)
    {
        if(GET_INPUT_TIMING_HFREQ() > _OOR_H_FREQ_UPPER_BOUND)
        {
            return _TRUE;
        }
    }

    // check fail-safe boundary
    if((GET_INPUT_TIMING_HFREQ() < _FAIL_SAVE_H_FREQ_LOWER_BOUND) ||
       (GET_INPUT_TIMING_HFREQ() > _FAIL_SAVE_H_FREQ_UPPER_BOUND) ||
       (GET_INPUT_TIMING_VFREQ() < _FAIL_SAVE_V_FREQ_LOWER_BOUND) ||
       (GET_INPUT_TIMING_VFREQ() > _FAIL_SAVE_V_FREQ_UPPER_BOUND))
    {
        SET_FAIL_SAFE_MODE(ucRegionIndex, _TRUE);
    }

    switch(SysRegionGetSourceType(enumDisplayRegion))
    {
#if(_VGA_SUPPORT == _ON)

        case _SOURCE_VGA:

            if(ScalerSyncGetNativeInputPixelClk(SysRegionGetInputPort(enumDisplayRegion)) >= _INPUTCLOCK_RANG_VGA)
            {
                return _TRUE;
            }

            break;

#endif

#if(_HDMI_SUPPORT == _ON)

        case _SOURCE_DVI:

            if(ScalerSyncGetNativeInputPixelClk(SysRegionGetInputPort(enumDisplayRegion)) >= _INPUTCLOCK_RANG_DVI)
            {
                return _TRUE;
            }

            break;
#endif

#if(_HDMI_SUPPORT == _ON)

        case _SOURCE_HDMI:

            if(ScalerSyncGetNativeInputPixelClk(SysRegionGetInputPort(enumDisplayRegion)) >= ((ScalerTmdsMacRxGetHdmiVer(SysRegionGetInputPort(enumDisplayRegion)) == _FROM_HDMI_TMDS_MAC) ? _INPUTCLOCK_RANG_HDMI : _INPUTCLOCK_RANG_HDMI21))
            {
                return _TRUE;
            }

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

#if(_DP_DYNAMIC_ADJUST_LINK_RATE_SUPPORT == _ON)
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            if(SysRegionGetInputPort(enumDisplayRegion) == _D0_INPUT_PORT)
            {
                if(ScalerSyncGetNativeInputPixelClk(SysRegionGetInputPort(enumDisplayRegion)) >= _INPUTCLOCK_RANG_USBC)
                {
                    return _TRUE;
                }

                break;
            }
#endif

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            if(SysRegionGetInputPort(enumDisplayRegion) == _D1_INPUT_PORT)
            {
                if(ScalerSyncGetNativeInputPixelClk(SysRegionGetInputPort(enumDisplayRegion)) >= _INPUTCLOCK_RANG_USBC)
                {
                    return _TRUE;
                }

                break;
            }
#endif

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            if(SysRegionGetInputPort(enumDisplayRegion) == _D2_INPUT_PORT)
            {
                if(ScalerSyncGetNativeInputPixelClk(SysRegionGetInputPort(enumDisplayRegion)) >= _INPUTCLOCK_RANG_USBC)
                {
                    return _TRUE;
                }

                break;
            }
#endif
#endif

#if(_DUAL_DP_SUPPORT == _ON)
            if(SysRegionGetInputPort(enumDisplayRegion) == _DUAL_DP_INPUT_PORT)
            {
                if(ScalerSyncGetNativeInputPixelClk(SysRegionGetInputPort(enumDisplayRegion)) >= (_INPUTCLOCK_RANG_DP * 2))
                {
                    return _TRUE;
                }
            }
            else
#endif
            {
                if(ScalerSyncGetNativeInputPixelClk(SysRegionGetInputPort(enumDisplayRegion)) >= _INPUTCLOCK_RANG_DP)
                {
                    return _TRUE;
                }
            }

            break;
#endif

        default:
            break;
    }

    if(UserInterfaceDisplayGetRegionNoSupportStatus(enumDisplayRegion) == _NO_SUPPORT_TRUE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Transform SelRegion Processing Type in Display Setting
// Input Value  : enumSelRegion
// Output Value : enumProcRegionType
//--------------------------------------------------
EnumProcRegionType UserCommonModeDisplaySettingTransSelRegionProcType(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_REGION:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _2P_PIP_MAIN:
        case _2P_PIP_SUB:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _2P_PIP_EAGLE_SIGHT_MAIN:
        case _2P_PIP_EAGLE_SIGHT_SUB:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_LR_EQUAL_L:
        case _2P_PBP_LR_EQUAL_R:
        case _2P_PBP_LR_L_LARGE_L:
        case _2P_PBP_LR_L_LARGE_R:
        case _2P_PBP_LR_R_LARGE_L:
        case _2P_PBP_LR_R_LARGE_R:
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _2P_PBP_TB_T:
        case _2P_PBP_TB_B:
#endif
        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:
            return _PROC_REGION_TYPE_NONE;

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_M:
        case _3P_FLAG_L:
        case _3P_FLAG_R:
            return _PROC_REGION_TYPE_INSIDE;

        case _3P_FLAG_M_OUTSIDE:
        case _3P_FLAG_L_OUTSIDE:
        case _3P_FLAG_R_OUTSIDE:
            return _PROC_REGION_TYPE_OUTSIDE;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M:
        case _3P_SKEW_L_T:
        case _3P_SKEW_L_B:
        case _3P_SKEW_R_M:
        case _3P_SKEW_R_T:
        case _3P_SKEW_R_B:
            return _PROC_REGION_TYPE_INSIDE;

        case _3P_SKEW_L_M_OUTSIDE:
        case _3P_SKEW_L_T_OUTSIDE:
        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_R_M_OUTSIDE:
        case _3P_SKEW_R_T_OUTSIDE:
        case _3P_SKEW_R_B_OUTSIDE:
            return _PROC_REGION_TYPE_OUTSIDE;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M:
        case _3P_SKEW_T_L:
        case _3P_SKEW_T_R:
        case _3P_SKEW_B_M:
        case _3P_SKEW_B_L:
        case _3P_SKEW_B_R:
            return _PROC_REGION_TYPE_INSIDE;

        case _3P_SKEW_T_M_OUTSIDE:
        case _3P_SKEW_T_L_OUTSIDE:
        case _3P_SKEW_T_R_OUTSIDE:
        case _3P_SKEW_B_M_OUTSIDE:
        case _3P_SKEW_B_L_OUTSIDE:
        case _3P_SKEW_B_R_OUTSIDE:
            return _PROC_REGION_TYPE_OUTSIDE;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT:
        case _4P_LB:
        case _4P_RT:
        case _4P_RB:
            return _PROC_REGION_TYPE_INSIDE;

        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
            return _PROC_REGION_TYPE_OUTSIDE;
#endif

        case _FULL_REGION:
        default:
            return _PROC_REGION_TYPE_FULL;
    }

    return _PROC_REGION_TYPE_FULL;
}

//--------------------------------------------------
// Description  : Get User SelRegion
// Input Value  : enumDisplayRegion
// Output Value : enumSelRegion
//--------------------------------------------------
EnumSelRegion UserCommonModeDisplaySettingGetSelRegion(EnumDisplayRegion enumDisplayRegion)
{
    EnumSelRegion enumOSDSelRegion = UserInterfaceColorGetOSDSystemSelRegion();
    EnumSelRegion enumSelRegion = (EnumSelRegion)enumDisplayRegion;
    EnumSelRegion enumSelRegionInverse = ScalerRegionGetInverse(enumOSDSelRegion);
    EnumProcRegionType enumProcRegionType = UserCommonModeDisplaySettingTransSelRegionProcType(enumOSDSelRegion);

    switch(enumProcRegionType)
    {
        case _PROC_REGION_TYPE_NONE:
            break;

        case _PROC_REGION_TYPE_INSIDE:
            if(enumOSDSelRegion != enumSelRegion)
            {
                enumSelRegion = enumSelRegionInverse;
            }
            break;

        case _PROC_REGION_TYPE_OUTSIDE:
            if(enumSelRegionInverse != enumSelRegion)
            {
                enumSelRegion = enumOSDSelRegion;
            }
            break;

        default:
        case _PROC_REGION_TYPE_FULL:
            enumSelRegion = _FULL_REGION;
            break;
    }

    return enumSelRegion;
}

#if(_COLOR_DEMO_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set User Required Color Process in Demo mode flow
// Input Value  : enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonModeDisplaySettingDemoModeColorProc(EnumDisplayRegion enumDisplayRegion)
{
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT) && (enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB))
    {
        return;
    }
#endif

    switch(UserCommonColorGetDemoModeType())
    {
        case _DEMO_MODE_BOTH:
            UserInterfaceModeDisplaySettingDemoModeColorProc(_DEMO_INSIDE);
            UserCommonModeDisplaySettingSingleColorProc(enumDisplayRegion);    // SingleProc After DemoMode UserInterface for Get Data
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if((UserCommonDisplayGetEagleSightMainSubSync() == _EAGLE_SIGHT_MAIN_SUB_SYNC) &&
               (enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN))
            {
                UserCommonModeDisplaySettingSingleColorProc(_DISPLAY_RGN_EAGLE_SIGHT_SUB);
            }
#endif
            UserCommonModeDisplaySettingMultiColorProc(_DEMO_INSIDE);
            UserInterfaceModeDisplaySettingDemoModeColorProc(_DEMO_OUTSIDE);
            UserCommonModeDisplaySettingMultiColorProc(_DEMO_OUTSIDE);
            break;

        case _DEMO_MODE_OUTSIDE:
            UserCommonColorBypassHLWSelRegionColorFunction(_DEMO_INSIDE);
            UserInterfaceModeDisplaySettingDemoModeColorProc(_DEMO_OUTSIDE);
            UserCommonModeDisplaySettingSingleColorProc(enumDisplayRegion);
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if((UserCommonDisplayGetEagleSightMainSubSync() == _EAGLE_SIGHT_MAIN_SUB_SYNC) &&
               (enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN))
            {
                UserCommonModeDisplaySettingSingleColorProc(_DISPLAY_RGN_EAGLE_SIGHT_SUB);
            }
#endif
            UserCommonModeDisplaySettingMultiColorProc(_DEMO_OUTSIDE);
            break;

        case _DEMO_MODE_INSIDE:
            UserCommonColorBypassHLWSelRegionColorFunction(_DEMO_OUTSIDE);
            UserInterfaceModeDisplaySettingDemoModeColorProc(_DEMO_INSIDE);
            UserCommonModeDisplaySettingSingleColorProc(enumDisplayRegion);
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if((UserCommonDisplayGetEagleSightMainSubSync() == _EAGLE_SIGHT_MAIN_SUB_SYNC) &&
               (enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN))
            {
                UserCommonModeDisplaySettingSingleColorProc(_DISPLAY_RGN_EAGLE_SIGHT_SUB);
            }
#endif
            UserCommonModeDisplaySettingMultiColorProc(_DEMO_INSIDE);
            break;

        case _DEMO_OFF:
        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Set User Required Color Process in normal mode flow
// Input Value  : enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonModeDisplaySettingNormalModeColorProc(EnumDisplayRegion enumDisplayRegion)
{
    EnumSelRegion enumSelRegion = UserCommonModeDisplaySettingGetSelRegion(enumDisplayRegion);

    UserInterfaceModeDisplaySettingNormalModeColorProc(enumSelRegion);

    UserCommonModeDisplaySettingSingleColorProc(enumDisplayRegion);

    UserCommonModeDisplaySettingMultiColorProc(enumSelRegion);
}

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set ES Original Mode H/VSUFI
// Input Value  : EnumDisplayRegion enumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonModeSetESOriginalModeSUFI(EnumDisplayRegion enumDisplayRegion)
{
    bit bStatus = _FALSE;

    if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
    {
        bStatus = ScalerScalingGetESOriginalModeStatus(GET_MDOMAIN_INPUT_HWIDTH(), GET_MDOMAIN_INPUT_VHEIGHT());
        if(bStatus == _TRUE)
        {
            ScalerScalingModifyESOriginalModeSUFI();
        }
    }
}
#endif
#endif

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Decide Input Port Digitial Color Info Change Check
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonModeColorimetrySeamlessChangeCheckBypass(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_DP_SUPPORT == _ON)
#if(_DP_COLORIMTRY_SEAMLESS_COLOR_INFO_CHECK_BYPASS == _ON)
    if(SysSourceGetPortTypeFromInputPort(enumInputPort) == _PORT_DP)
    {
        return _TRUE;
    }
#endif
#endif

    return _FALSE;
}
#endif

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get IMC staus when active
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit UserCommonModeGetImgCmpStatus(EnumDisplayRegion enumDisplayRegion)
{
    return ScalerFRCGetImgCmpStatus(enumDisplayRegion);
}
#endif
