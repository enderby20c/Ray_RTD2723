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
// ID Code      : UserCommonColorInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _COLOR_FUNCTION_SHARPNESS = _BIT0,
    _COLOR_FUNCTION_ULTRA_VIVID = _BIT1,
    _COLOR_FUNCTION_LOCAL_CONTRAST = _BIT2,
    _COLOR_FUNCTION_DCR = _BIT3,
    _COLOR_FUNCTION_DCC = _BIT4,
    _COLOR_FUNCTION_ICM = _BIT5,
    _COLOR_FUNCTION_COLOR_ENHANCE = _COLOR_FUNCTION_ICM,
    _COLOR_FUNCTION_IAPS = _BIT6,
    _COLOR_FUNCTION_CTS_BRI = _BIT7,
    _COLOR_FUNCTION_3DGAMMA = _BIT8,
    _COLOR_FUNCTION_SRGB = _BIT9,
    _COLOR_FUNCTION_UNIFORMITY = _BIT10,
    _COLOR_FUNCTION_GAMMA = _BIT11,
    _COLOR_FUNCTION_PCM = (_BIT12 | _COLOR_FUNCTION_SRGB | _COLOR_FUNCTION_GAMMA),
    _COLOR_FUNCTION_LOCAL_DIMMING = (_BIT13 | _COLOR_FUNCTION_DCR),
    _COLOR_FUNCTION_LIGHT_ENHANCE = (_COLOR_FUNCTION_DCC | _COLOR_FUNCTION_IAPS),
    _COLOR_FUNCTION_GLOBAL_DIMMING = (_COLOR_FUNCTION_DCR | _COLOR_FUNCTION_PCM),
    _COLOR_FUNCTION_SDRTOHDR = (_COLOR_FUNCTION_PCM | _COLOR_FUNCTION_DCC | _COLOR_FUNCTION_ICM),
    _COLOR_FUNCTION_GLOBAL_HUE_SAT = _COLOR_FUNCTION_SRGB,
    _COLOR_FUNCTION_D_COLOR_CONV,
    _COLOR_FUNCTION_NIGHT_SNIPER = (_COLOR_FUNCTION_LOCAL_CONTRAST | _COLOR_FUNCTION_ICM | _COLOR_FUNCTION_D_COLOR_CONV),
} EnumColorFunction;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_RGB_QUANTIZATION_RANGE_FUNCTION == _ON)
extern void UserCommonColorRGBQuantizationRangeAdjust(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_YCC_QUANTIZATION_RANGE_FUNCTION == _ON)
extern void UserCommonColorYCCQuantizationRangeAdjust(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_COLOR_IP_COLOR_CONVERT == _ON)
extern EnumFunctionOnOFF UserCommonColorSpaceConvertDDomainCheckEnableStatus(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonColorSpaceConvertDDomainEnable(EnumDisplayRegion enumDisplayRegion, bit bOn);
extern BYTE UserCommonColorSpaceGetColorDepth(EnumInputPort enumInputPort);
extern EnumColorimetry UserCommonColorSpaceGetColorimetry(EnumInputPort enumInputPort);
extern EnumColorimetryExt UserCommonColorSpaceGetExtColorimetry(EnumInputPort enumInputPort);
extern EnumColorimetryAddExt UserCommonColorSpaceGetAddExtColorimetry(EnumInputPort enumInputPort);
extern EnumColorRGBQuantization UserCommonColorSpaceGetRGBQuantizationRange(EnumInputPort enumInputPort);
extern EnumColorYCCQuantization UserCommonColorSpaceGetYCCQuantizationRange(EnumInputPort enumInputPort);
#endif

#if(_COLOR_FORMAT_CONVERT_FUNCTION == _ON)
extern void UserCommonColorColorFormatConvertAdjust(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace, EnumDBApply enumDBApply);
#endif

#if(_ULTRA_VIVID_FUNCTION == _ON)
extern void UserCommonColorUltraVividAdjust(EnumSelRegion enumSelRegion);
extern void UserCommonColorUltraVividEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_COLOR_IP_DCR == _ON)
#if(_HW_DCR_BIT == _DCR_8BIT)
extern DWORD UserCommonColorDCRReadResult_8BIT(EnumDCRAdjOption enumDCRReadOption);
extern WORD UserCommonColorDCRGetAverage_8BIT(EnumDCRAverageOption enumDCRAverageOption, DWORD ulDivider);
#endif
#if(_HW_DCR_BIT == _DCR_10BIT)
extern DWORD UserCommonColorDCRReadResult_10BIT(EnumDCRAdjOption enumDCRReadOption);
extern WORD UserCommonColorDCRGetAverage_10BIT(EnumDCRAverageOption enumDCRAverageOption, DWORD ulDivider);
extern WORD UserCommonColorDCRGetMaxRGB_10BIT(void);
#endif
extern DWORD UserCommonColorDCRGetMeasureRegionSize(EnumSelRegion enumDCRMeasureRegion);
#if(_HW_DCR_SET_BACKGROUND_OPTION_SUPPORT == _ON)
extern void UserCommonColorDCRSetBackgroundColor(WORD usRValue, WORD usGValue, WORD usBValue);
extern void UserCommonColorDCRSetBackgroundEnable(EnumFunctionOnOFF enumOn);
#endif
extern void UserCommonColorDCRSetMeasureRegion(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
extern void UserCommonColorNightSniperAdjust(EnumSelRegion enumSelRegion);
extern bit UserCommonColorNightSniperCheckStatus(EnumSelRegion enumSelRegion);
#endif

#if(_ICM_FUNCTION == _ON)
extern void UserCommonColorICMAdjust(EnumSelRegion enumSelRegion);
extern void UserCommonColorICMEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
extern void UserCommonColorICMSCMSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply);
extern EnumHLWSetSel UserCommonColorICMSCMGetEffectiveRegion(void);
#endif
#endif

#if((_DCC_HISTOGRM_INFO_FUNCTION == _ON) || (_DCC_FUNCTION == _ON))
extern void UserCommonColorDCCHistogramAdjust(void);
#endif

#if(_DCC_FUNCTION == _ON)
extern void UserCommonColorDCCAdjust(EnumSelRegion enumSelRegion);
extern void UserCommonColorDCCEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
extern void UserCommonColorDCCSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply);
extern EnumHLWSetSel UserCommonColorDCCGetEffectiveRegion(void);
#endif
#endif

#if(_COLOR_IP_IAPS == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
extern void UserCommonColorIAPSGainSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply);
extern EnumHLWSetSel UserCommonColorIAPSGainGetEffectiveRegion(void);
#endif
#endif

#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
extern void UserCommonColorDCCGetHistoInfo(BYTE *pucReadArray);
extern BYTE UserCommonColorDCCReadS0toS6(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption);
#if(_HW_DCC_Y_BIT_MODE == _DCC_Y_8BIT)
extern BYTE UserCommonColorDCCReadY_8BIT(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption);
#endif
#if(_HW_DCC_Y_BIT_MODE == _DCC_Y_10BIT)
extern WORD UserCommonColorDCCReadY_10BIT(BYTE *pucReadArray, EnumDCCReadOption enumDCCReadOption);
#endif
#endif

#if(_CONTRAST_FUNCTION == _ON)
extern void UserCommonColorContrastAdjust(EnumSelRegion enumSelRegion);
#endif

#if(_COLOR_IP_CONTRAST == _ON)
extern void UserCommonColorContrastGetSetting(EnumCtsCoefType enumCtsCoefType, WORD *pusData);
#endif

#if(_BRIGHTNESS_FUNCTION == _ON)
extern void UserCommonColorBrightnessAdjust(EnumSelRegion enumSelRegion);
#endif

#if(_COLOR_IP_BRIGHTNESS == _ON)
extern void UserCommonColorBrightnessGetSetting(EnumBriCoefType enumBriCoefType, WORD *pusData);
#endif

#if((_CONTRAST_FUNCTION == _ON) || (_BRIGHTNESS_FUNCTION == _ON))
extern void UserCommonColorBRICTSEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_PCM_FUNCTION == _ON)
extern void UserCommonColorPCMAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void UserCommonColorPCMEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);

extern void UserCommonColorInGammaAdjust(EnumSelRegion enumSelRegion);
#if(_OCC_FUNCTION == _ON)
extern BYTE *UserCommonColorGetOCCGamma1Addr(EnumOCCGamma1Type enumOCCGamma1Type);
#endif
#endif

#if(_GAMMA_FUNCTION == _ON)
extern void UserCommonColorGammaAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void UserCommonColorGammaEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#if(_OGC_FUNCTION == _ON)
extern void UserCommonColorGetOGCColorTempGain(BYTE ucColorTemp, BYTE ucGammaMode, BYTE *pucData, EnumOGCModeSelect enumOGCModeSelect);
#endif
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
extern void UserCommonColorPCMSetPCMOff(EnumSelRegion enumSelRegion);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
extern EnumHLWSetSel UserCommonColorPCMGetEffectiveRegion(void);
#if((_ADVANCED_HDR10_SUPPORT == _OFF) && (_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _OFF))
extern void UserCommonColorPCMSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply);
#endif
#endif
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
extern EnumHLWSetSel UserCommonColorGammaGetEffectiveRegion(void);
extern void UserCommonColorGammaSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply);
#endif
#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
extern BYTE UserCommonColorGetOGCBank(EnumOGCTypeSelect enumOGCTypeSelect, EnumOGCModeSelect enumOGCModeSelect);
extern BYTE *UserCommonColorGetOGCAddr(EnumOGCTypeSelect enumOGCTypeSelect, EnumOGCModeSelect enumOGCModeSelect);
#endif
#if(_OGC_DICOM_FUNCTION == _ON)
extern BYTE UserCommonColorGetDICOMBank(EnumDICOMTypeSelect enumDICOMTypeSelect);
extern BYTE *UserCommonColorGetDICOMAddr(EnumDICOMTypeSelect enumDICOMTypeSelect);
#endif
#endif

#if((_GLOBAL_HUE_SATURATION_FUNCTION == _ON) || (_HDR10_SUPPORT == _ON))
extern void UserCommonColorSRGBAdjust(EnumSelRegion enumSelRegion);
extern void UserCommonColorSRGBEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
extern void UserCommonColorDColorConvertAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void UserCommonColorColorConvertDBApply(EnumDisplayRegion enumDisplayRegion, EnumDBApply enumDBApply);
#endif

#if(_SDR_TO_HDR_FUNCTION == _ON)
extern void UserCommonColorSDRToHDRAdjust(EnumSelRegion enumSelRegion);
#endif

#if((_RGB_3D_GAMMA_FUNCTION == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON) || (_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON))
extern void UserCommonColor3DGammaAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void UserCommonColor3DGammaEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
extern void UserCommonColorRGBGamma3DGammaSwapEnable(EnumFunctionOnOFF enumOn);
#endif

#if(_OCC_RGB_3D_GAMMA_SUPPORT == _ON)
extern BYTE UserCommonColorGetOCC3DGammaTableBank(Enum3DGammaTypeSelect enum3DGammaType);
extern BYTE *UserCommonColorGetOCC3DGammaTableAddress(Enum3DGammaTypeSelect enum3DGammaType);
extern BYTE UserCommonColorGet3DGammaOGCTableBank(void);
extern BYTE *UserCommonColorGet3DGammaOGCTableAddress(Enum3DGammaTypeSelect enum3DGammaType);
#if (_OCC_RGB_3D_GAMMA_HDR10_REMAP_SUPPORT == _ON)
extern BYTE UserCommonColorGetOCC3DGammaStartType(void);
#endif
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
extern EnumFunctionOnOFF UserCommonColor3DGammaCubeGetEnableStatus(EnumSelRegion enumSelRegion);
#endif
#endif

#if(_UNIFORMITY_FUNCTION == _ON)
extern void UserCommonColorPanelUniformityAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void UserCommonColorPanelUniformityEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
extern void UserCommonColorPanelUniformityOffsetEnable(EnumFunctionOnOFF enumOn);
#endif
#if(_COLOR_IP_UNIFORMITY == _ON)
extern bit UserCommonColorPanelUniformityCheckStatus(EnumSelRegion enumSelRegion);
#endif

extern EnumColorSpace UserCommonColorGetColorSpace(EnumInputPort enumInputPort);
extern bit UserCommonColorGetColorSpaceRGB(EnumColorSpace enumColorSpace);
extern bit UserCommonColorScalingByPassTableSel(EnumSelRegion enumSelRegion);

#if((_2P_PIP_DISPLAY_SUPPORT == _ON) || (_EAGLE_SIGHT_SUPPORT == _ON))
extern void UserCommonColorPIPBlendingLevelAdjust(WORD usLevel, EnumDBApply enumDBApply);
#endif

#if(_SHARPNESS_FUNCTION == _ON)
extern void UserCommonColorSharpnessAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#if(_DM_FUNCTION == _ON)
extern BYTE *UserCommonColorGetSharpnessDMCoefH(void);
extern BYTE *UserCommonColorGetSharpnessDMCoefV(void);
#endif
#endif

#if(_SD_TABLE_SEL_FUNCTION == _ON)
extern void UserCommonColorScalingDownCoefAdjust(EnumSelRegion enumSelRegion);
#endif

#if(_COLOR_IP_HL_WIN == _ON)
extern void UserCommonColorHLWinTypeAdjust(EnumDBApply enumDBApply);
extern void UserCommonColorHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply);
extern void UserCommonColorHLWDDomainAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
extern void UserCommonColorHLWBorderAdjust(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply);
extern void UserCommonColorHLWBorderEnable(bit bTopBorderEn, bit bBottomBorderEn, bit bLeftBorderEn, bit bRightBorderEn, EnumDBApply enumDBApply);
extern bit UserCommonColorDemoModeSupportCheck(void);
#endif

#if(_BORDER_WINDOW_FUNCTION == _ON)
extern void UserCommonColorBorderWindowAdjust(EnumDBApply enumDBApply);
extern void UserCommonColorBorderWindowDisable(EnumDBApply enumDBApply);
#endif

#if(_OD_FUNCTION == _ON)
extern void UserCommonColorODGainAdjust(void);
extern void UserCommonColorODAdjust(void);
extern void UserCommonColorODEnable(EnumFunctionOnOFF enumOn);
extern bit UserCommonColorODGetStatus(EnumODStatusType enumStatusType);
extern BYTE UserCommonColorODGetDeltaGain(void);
extern EnumODParamIndex UserCommonColorODGetUseParam(void);
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
extern void UserCommonColorLocalContrastAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void UserCommonColorLocalContrastTemporalAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void UserCommonColorLocalContrastEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
extern bit UserCommonColorGetLocalContrastEnableStatus(EnumSelRegion enumSelRegion);
#if(_SDR_PLUS_FUNCTION == _ON)
extern bit UserCommonColorGetSDRPlusEnableStatus(EnumSelRegion enumSelRegion);
#endif
#if((_ADVANCED_LOCAL_CONTRAST_SUPPORT == _ON) || (_SDR_PLUS_FUNCTION == _ON))
extern void UserCommonColorLocalContrastSharpnessAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void UserCommonColorLocalContrastToneMappingAdjust(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
extern void UserCommonColorLocalContrastInitalDataAdjust(EnumSelRegion enumSelRegion);
extern WORD UserCommonColorLocalContrastGetInputVFreq(EnumSelRegion enumSelRegion);
extern EnumDisplayRegion UserCommonColorLocalContrastGetDisplayRegion(EnumSelRegion enumSelRegion);
extern bit UserCommonColorLocalContrastCheckStatus(EnumSelRegion enumSelRegion);
#endif

#if(_VGA_SUPPORT == _ON)
#if(_RINGING_FILTER_FUNCTION == _ON)
#if(_HW_RINGING_FILTER_TYPE != _GEN_NONE)
extern void UserCommonColorRingingFilterOff(void);
#endif
#endif
#if(_DIGITAL_FILTER_SUPPORT == _ON)
#if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
extern void UserCommonColorDigitalFilterEnable(EnumFunctionOnOFF enumOn);
#endif
#endif
#endif

#if(_SPI_SUPPORT == _ON)
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
extern bit UserCommonColorSpiSetCommandRegion(EnumDeviceLedDriver enumDeviceLedDriver, WORD usStartAddr, WORD usNumofData, BYTE *pucDataBuffer, bit bApplyUpdSync);
#endif
#endif

extern EnumHLWType UserCommonColorGetSelectRegionHLWArea(EnumSelRegion enumSelRegion);
extern void UserCommonColorMultiFunctionRegionEnableStart(EnumSelRegion enumSelRegion, WORD usColorFunction);
extern void UserCommonColorMultiFunctionRegionEnableEnd(EnumSelRegion enumSelRegion, WORD usColorFunction);
extern void UserCommonColorBypassHLWSelRegionColorFunction(EnumSelRegion enumSelRegion);

#if(_COLOR_DEMO_FUNCTION == _ON)
extern EnumDemoModeType UserCommonColorGetDemoModeType(void);
#endif

#if(_3DDI_FUNCTION == _ON)
extern bit UserCommonColor3DDIEnableDecision(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort);
#endif

#if(_DYNAMIC_COLOR_AUTO_MEASURE == _ON)
extern void UserCommonColorSetDynamicColorInitialBoundary(WORD usDHStart, WORD usDHEnd, WORD usDVStart, WORD usDVEnd);
extern void UserCommonColorSetAutoMeasure(WORD usDHStart, WORD usDHEnd, EnumAutoChannelType enumAutoChannelType);
extern bit UserCommonColorGetDynamicColorMeasureResult(BYTE *pucMeasureResult, WORD usDHStart, WORD usDHEnd, bit bWait);
#endif

#if(_I_DITHER_FUNCTION == _ON)
extern void UserCommonColorIDitherRegionEnable(EnumDisplayRegion enumDisplayRegion, EnumFunctionOnOFF enumOn);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
extern void UserCommonColorCircleWindowAdjust(EnumDBApply enumDBApply);
#endif
#endif

#if(_COLOR_IP_ANTI_ALIASING == _ON)
extern void UserCommonColorAntiAliasingAdjust(EnumSelRegion enumSelRegion);
extern bit UserCommonColorGetAntiAliasingSupport(EnumSelRegion enumSelRegion);
#endif

#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
extern void UserCommonColorLowBlueAdjust(EnumSelRegion enumSelRegion);
#endif