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
// ID Code      : UserCommonColorInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_LOCAL_DIMMING_FUNCTION == _ON)
typedef struct
{
    DWORD ulColorCurrentBlackNum;
    DWORD ulColorCurrentWhiteNum;
    DWORD ulColorLastBlackNum;
    DWORD ulColorLastWhiteNum;
#if((_LOCAL_DIMMING_FULL_PATTERN_ONESTEP_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE != _LD_COMPENSATE_NONE) || (_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON))
    BYTE ucMaxR;
    BYTE ucMaxG;
    BYTE ucMaxB;
    BYTE ucMinR;
    BYTE ucMinG;
    BYTE ucMinB;
#endif

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    DWORD ulColorMaxRNum;
    DWORD ulColorMaxGNum;
    DWORD ulColorMaxBNum;
    DWORD ulColorLastMaxRNum;
    DWORD ulColorLastMaxGNum;
    DWORD ulColorLastMaxBNum;
#endif

#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
    BYTE ucColorDCRMaxY;
    BYTE ucColorLastDCRMaxY;
#endif
}StructLocalDimmingDCRData;
#endif

#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
typedef struct
{
    EnumDynamicLowBlueType enumDynamicLowBlueType;
    WORD usHazardRmax;
    WORD usHazardGmax;
    WORD usHazardBmax;
    WORD usHazardTarget;
    WORD usGainR;
    WORD usGainG;
    WORD usGainB;
    WORD usGainStepB;
    WORD usGainOffset;
    WORD usRegionPixelThd;
    BYTE pucBlurMatrix[169];
} StructColorDynamicLowBlueSetting;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_LOCAL_DIMMING_FUNCTION == _ON)
extern StructLocalDimmingDCRData g_stColorLocalDimmingDCRData;
#endif
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
extern StructColorDynamicLowBlueSetting g_stColorDynamicLowBlueSetting;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
extern EnumRGBQuantLimitRangeStatus UserCommonColorGetRGBQuantizationLimitRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorRGBQuantization enumColorRGBQuantization);
#endif

#if(_YCC_QUANTIZATION_RANGE_FUNCTION == _ON)
extern EnumYccQuantFullRangeStatus UserCommonColorGetYCCQuantizationFullRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorYCCQuantization enumColorYCCQuantization);
#endif

#if(_COLOR_IP_COLOR_CONVERT == _ON)
extern void UserCommonColorFormatConvert(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace, EnumDBApply enumDBApply);
extern void UserCommonColorSetColorFormatConvert(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace, EnumDBApply enumDBApply);
extern void UserCommonColorLoadYuv2RgbTable(EnumDisplayRegion enumDisplayRegion, EnumDBApply enumDBApply);
extern EnumColorSpace UserCommonColorGetColorFormat(EnumDisplayRegion enumDisplayRegion);
#if(_COLOR_IP_DM == _ON)
extern void UserCommonColorSetColorFormatConvertDM(EnumDisplayRegion enumDisplayRegion, EnumDBApply enumDBApply);
#endif
#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
extern void UserCommonColorSpaceConvertNightSniperEnable(EnumSelRegion enumSelRegion, bit bOn);
extern EnumSelRegion UserCommonColorSpaceConvertNightSniperGetSelRegion(EnumDisplayRegion enumDisplayRegion);
#endif
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
extern bit UserCommonColorNightSniperCheckRegionSupport(EnumSelRegion enumSelRegion);
extern EnumNightSniperType UserCommonColorGetNightSniperEnableStatus(EnumSelRegion enumSelRegion);
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
extern void UserCommonColorGetDColorConvertData(EnumSelRegion enumSelRegion, StructColorDColorConvertSetting *pstDColorConvertData);
#endif

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
extern void UserCommonColorGetUltraVividData(EnumSelRegion enumSelRegion, StructColorUltraVividSetting *pstUltraVividData);
extern void UserCommonColorUltraVividRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_COLOR_IP_DCR == _ON)
extern void UserCommonColorGetDCRData(StructColorDCRSetting *pstDCRData);
extern void UserCommonColorDCRRegionAdjust(void);
#if(_HW_DCR_CLL_FALL_OPTION_SUPPORT == _ON)
extern void UserCommonColorDCRResetCLLResult(void);
#endif
#endif

#if((_COLOR_IP_DCC_HISTOGRAM == _ON) || (_COLOR_IP_DCC == _ON))
extern void UserCommonColorGetDCCHistogramData(StructColorDCCHistogramSetting *pstDCCHistogramData);
#endif

#if(_COLOR_IP_DCC == _ON)
extern void UserCommonColorGetDCCData(EnumSelRegion enumSelRegion, StructColorDCCSetting *pstDCCData);
extern void UserCommonColorDCCRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_COLOR_IP_CONTRAST == _ON)
extern void UserCommonColorContrast10bitPanelCompensate(EnumSelRegion enumSelRegion, WORD *pusData);
#if(_CONTRAST_6BIT_PANEL_COMPENSATE == _ON)
extern void UserCommonColorContrast6bitPanelCompensate(WORD *pusData);
#endif
extern void UserCommonColorGetContrastData(EnumSelRegion enumSelRegion, StructColorCtsSetting *pstCtsData);
#endif

#if(_COLOR_IP_BRIGHTNESS == _ON)
extern void UserCommonColorGetBrightnessData(EnumSelRegion enumSelRegion, StructColorBriSetting *pstBriData);
#endif

#if((_COLOR_IP_CONTRAST == _ON) || (_COLOR_IP_BRIGHTNESS == _ON))
extern void UserCommonColorBRICTSRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_COLOR_IP_ICM == _ON)
extern void UserCommonColorGetICMData(EnumSelRegion enumSelRegion, StructColorICMSetting *pstICMData);
extern void UserCommonColorICMRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_COLOR_IP_IAPS == _ON)
extern void UserCommonColorGetIAPSData(EnumSelRegion enumSelRegion, StructColorIAPSSetting *pstIAPSData);
extern void UserCommonColorIAPSRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
extern void UserCommonColorGetInGammaData(EnumSelRegion enumSelRegion, StructColorInGammaSetting *pstIgData);
extern void UserCommonColorPCMRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_COLOR_IP_YMAPPING == _ON)
extern void UserCommonColorGetYmappingData(EnumSelRegion enumSelRegion, StructColorYmappingSetting *pstYmData);
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
extern void UserCommonColorGetPostGammaData(EnumSelRegion enumSelRegion, StructColorPostGammaSetting *pstPgData);
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
extern void UserCommonColorGetOutGammaData(EnumSelRegion enumSelRegion, StructColorOutGammaSetting *pstOgData);
extern void UserCommonColorGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_COLOR_IP_SRGB == _ON)
extern void UserCommonColorGetsRGBData(EnumSelRegion enumSelRegion, StructColorSRGBSetting *pstsRGBData);
extern void UserCommonColorSRGBRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
extern void UserCommonColorGet3DGammaData(EnumSelRegion enumSelRegion, StructColor3DGammaSetting *pst3DGammaData);
extern void UserCommonColor3DGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_UNIFORMITY_FUNCTION == _ON)
extern BYTE UserCommonColorGetUniformityType(BYTE ucIndex);
extern BYTE UserCommonColorGetPanelUniformityGainBank(EnumUniformityTypeSelect enumUniformityType);
extern WORD UserCommonColorGetPanelUniformityGainAddr(EnumUniformityTypeSelect enumUniformityType);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
extern BYTE UserCommonColorGetPanelUniformityOffsetBank(EnumUniformityTypeSelect enumUniformityType);
extern WORD UserCommonColorGetPanelUniformityOffsetAddr(EnumUniformityTypeSelect enumUniformityType);
extern WORD UserCommonColorGetPanelUniformityDecayAddr(EnumUniformityTypeSelect enumUniformityType);
#endif
#endif

#if(_COLOR_IP_UNIFORMITY == _ON)
extern void UserCommonColorGetUniformityData(EnumSelRegion enumSelRegion, StructColorUniformitySetting *pstUniData);
extern void UserCommonColorPanelUniformityRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_COLOR_IP_SHARPNESS == _ON)
extern void UserCommonColorGetSharpnessData(EnumSelRegion enumSelRegion, StructColorSharpnessSetting *pstSharpnessData);
#endif

#if(_SD_TABLE_SEL_FUNCTION == _ON)
extern void UserCommonColorGetScalingDownCoef(EnumSelRegion enumSelRegion, StructColorScalingDownCoefSetting *pstScalingDownData);
#endif

#if(_COLOR_IP_HL_WIN == _ON)
extern void UserCommonColorGetHLWData(StructColorHLWSetting *pstHLWData);
#endif

#if(_COLOR_IP_BORDER_WIN == _ON)
extern void UserCommonColorGetBorderWindowData(StructColorBorderWindowSetting *pstBorderWindowData);
#endif

#if(_COLOR_IP_OD == _ON)
extern void UserCommonColorGetODData(StructODSetting *pstODData);
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
extern void UserCommonColorGetLocalContrastData(EnumSelRegion enumSelRegion, StructColorLocalContrastSetting *pstLocalContrastData);
extern void UserCommonColorGetLocalContrastTemporalData(EnumSelRegion enumSelRegion, StructColorLocalContrastTemporalSetting *pstLocalContrastData);
extern void UserCommonColorLocalContrastRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
extern void UserCommonColorColorLocalContrastTableDBApply(EnumSelRegion enumSelRegion, EnumLocalContrastDBApplyType enumDBApplyType, EnumDBApply enumDBApply);
#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
extern void UserCommonColorLocalContrastSetSceneChangeTHD(EnumSelRegion enumSelRegion);
#endif
#endif
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
extern EnumLocalContrastReadYavgData UserCommonColorLocalContrastReadYavgStatus(void);
extern bit UserCommonColorLocalContrastCheckReadYavgSupport(void);
extern void UserCommonColorLocalContrastRestoreSetting(void);
#endif
#endif

#if(_I_DITHER_FUNCTION == _ON)
extern void UserCommonColorIDitherDisplayInitialProc(void);
extern void UserCommonColorIDitherReloadTable(EnumSelRegion enumSelRegion, BYTE ucColorDepth);
#endif

#if(_I_DITHER_FUNCTION == _ON)
extern void UserCommonColorIDitherAdjust(void);
#endif

#if(_D_DITHER_FUNCTION == _ON)
extern void UserCommonColorDDitherAdjust(void);
#endif

#if(_VGA_SUPPORT == _ON)
extern void UserCommonColorVgaProc(void);
#endif

#if(_COLOR_IP_LOCAL_DIMMING == _ON)
extern void UserCommonColorGetLocalDimmingData(StructColorLocalDimmingSetting *pstLocalDimmingData);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
extern void UserCommonColorGetCircleWindowData(StructColorCircleWindowSetting *pstCircleWindowData);
extern void UserCommonColorSetCircleWindowBorderEnable(bit bEnable, EnumDBApply enumDBApply);
#endif
#endif
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
extern void UserCommonColorLowBlueInitial(void);
extern void UserCommonColorMRCMLowBlueReset(void);
extern void UserCommonColorLowBlueGetData(StructColorDynamicLowBlueSetting *pstDynamicLowBlueSetting);
extern void UserCommonColorLowBlueLocalAdjust(WORD *pusCurrentGainB);
extern void UserCommonColorLowBlueStaticGlobalAdjust(void);
extern EnumDynamicLowBlueType UserCommonColorGetLowBlueStatus(void);
extern void UserCommonColorLowBlueRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);

#endif

