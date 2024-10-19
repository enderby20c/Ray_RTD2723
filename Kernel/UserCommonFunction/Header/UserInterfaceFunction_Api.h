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
// ID Code      : UserInterfaceFunction_Api.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_INTERFACE_FUNCTION_API__
#define __USER_INTERFACE_FUNCTION_API__

#if(_VGA_SUPPORT == _ON)
#include _USER_VGA_MODE_TABLE_INCLUDE
#endif

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
#include _USER_DATA_EXCHANGE_INCLUDE
#endif

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//-------------------------------------------------------
// Extern functions from UserAdjust.c
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
extern BYTE UserAdjustAudioGetOsdVolume(void);
extern void UserAdjustAudioVolume(BYTE ucVolume);
extern WORD UserAdjustAudioVolumeMapping(BYTE ucVolume);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//-------------------------------------------------------
// Extern functions from UserInterfaceAudio.c
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
extern EnumAudioStatus UserInterfaceAudioGetReadyToPlayStatus(void);
extern EnumAudioInputSource UserInterfaceAudioGetSource(void);
extern EnumAudioMuteStatus UserInterfaceAudioGetOutputMuteStatus(void);
extern WORD UserInterfaceAudioGetVolume(void);

#if(_DP_SUPPORT == _ON)
#if(_DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT == _ON)
extern EnumAudioDpDpcdSupport UserInterfaceAudioDpGetCapabilityInitialState(EnumInputPort enumInputPort);
#endif // End of #if(_DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern EnumAudioDACOutput UserInterfaceAudioDACGetOutput(void);
extern EnumAudioDacDepopState UserInterfaceAudioDACGetKeepDepopState(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
extern EnumAudioStandAloneStatus UserInterfaceAudioGetStandAloneStatus(void);
#endif

extern void UserInterfaceAudioPowerProc(EnumPowerStatus enumPowStatus);
extern void UserInterfaceAudioAmpMuteProc(bit bMute);

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
extern void UserInterfaceAudioAmpFastMuteProc(bit bMute);
#endif

extern EnumDisplayRegion UserInterfaceAudioGetDisplayModeRegion(void);
extern EnumRegionIndex UserInterfaceAudioGetRegionIndex(void);
extern EnumAudioSamplingFreqType UserInterfaceAudioGetUserSamplingFreq(void);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
extern EnumAudioSamplingFreqType UserInterfaceAudioGetSamplingFreqLimit(void);
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
extern void UserInterfaceAudioExternalCodecProc(bit bEnable);
#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
extern void UserInterfaceAudioExternalCodecFastProc(bit bEnable);
#endif
extern EnumAudioMuteStatus UserInterfaceAudioGetMuteStatus(void);
#endif

#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
extern EnumAudioSpdifParallelMode UserInterfaceAudioSpdifParallelMode(void);
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
extern EnumAudioI2sParallelMode UserInterfaceAudioI2sParallelMode(void);
extern EnumAudioI2sParallelType UserInterfaceAudioI2sParallelType(void);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern EnumAudioInternalGenFreq UserInterfaceAudioGetUserDefineAudioGenFreq(void);
#if(_INTERNAL_AUDIO_CHANNEL_CONFIG_BY_USER_SUPPORT == _ON)
extern EnumAudioLeftRightChannelSelect UserInterfaceAudioGetUserLeftRightChanelSelect(void);
#endif
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
extern EnumAudioTtsOsdSupport UserInterfaceAudioGetTtsSupport(void);
extern BYTE UserInterfaceAudioGetTtsPlayAudioVolume(void);
extern BYTE UserInterfaceAudioGetTtsPlayTextVolume(void);
extern EnumAudioTtsPlayReady UserInterfaceAudioGetTtsAudioReady(void);
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

#if(_AUDIO_ARC_SUPPORT == _ON)
extern EnumAudioInputSource UserInterfaceAudioGetArcSource(void);
extern EnumInputPort UserInterfaceAudioGetArcInputport(void);
extern EnumAudioArcMode UserInterfaceAudioGetArcMode(void);
extern EnumAudioMuteStatus UserInterfaceAudioGetArcMuteStatus(void);
extern EnumArcAudioChanelStatus UserInterfaceAudioGetArcChannel(void);
extern EnumArcAudioOutputType UserInterfaceAudioGetArcAudioOutput(void);
extern EnumAudioMuteStatus UserInterfaceAudioGetArcOutputMuteStatus(void);
extern EnumAudioStatus UserInterfaceAudioGetArcReadyToPlayStatus(void);
extern void UserInterfaceArcTxHandler(void);
extern EnumEdidAudioCapCheckResult UserInterfaceArcTxEdidChangeCheck(void);
extern void UserInterfaceArcTxEdidAudioCapabilitySwitch(void);
extern EnumEdidAudioCapModifyResult UserInterfaceArcTxEdidModify(BYTE *pucEdidAddr, WORD *pusCtaDataBlockAddr);
extern EnumEdidAudioCapModifyEnable UserInterfaceArcTxEdidGetModifyEnable(void);
extern EnumEdidAudioType UserInterfaceArcTxEdidGetType(void);
extern void UserInterfaceArcTxOsdChangeProc(EnumAudioArcMode enumArcMode);

#if(_AUDIO_EARC_SUPPORT == _ON)
extern EnumEdidAudioBlockExistStatus UserInterfaceArcTxCheckInputPortEdidHasAudioCapability(EnumInputPort enumInputPort);
extern EnumArcCompatibleType UserInterfaceArcTxEarcGetDowngradeToArcPermission(void);
extern void UserInterfaceArcTxEarcCdsParseDoneNotify(void);

#if(_AUDIO_ARC_TX_HIGH_LEVEL_FW_TYPE == _ARC_TX_HIGH_LEVEL_FW_TYPE_SD_TEST)
extern void UserInterfaceArcTxEarcGetCdsAudioCapability(BYTE *pucCurrentArcTxEarcCdsAdb, BYTE *pucCurrentArcTxEarcCdsSpkAdb);
#endif
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
extern void UserInterfaceArcTxMuteProc(bit bMute);
extern void UserInterfaceArcTxArcModeInitial(void);
extern void UserInterfaceArcTxArcModeOutputReset(void);
extern void UserInterfaceArcTxAudioOutputFormatSetting(EnumArcAudioChanelStatus enumArcOsdChannelNum, StructAudioInterfaceInfoForArc stArcAudioSourceInfo);
extern EnumArcOutputStreamStatus UserInterfaceArcTxStreamHandler(void);
extern EnumArcOutputStableDetectResult UserInterfaceArcTxStableDetect(void);
extern void UserInterfaceArcTxInitial(EnumAudioArcMode enumArcMode);
extern void UserInterfaceArcTxDisable(void);

#if(_AUDIO_EARC_SUPPORT == _ON)
extern void UserInterfaceArcTxEarcModeOutputReset(void);
extern EnumEarcDiscoveryResult UserInterfaceArcTxEarcCheckDiscoveryPass(void);
extern EnumEarcDiscoveryTimeoutStatus UserInterfaceArcTxEarcCheckDiscoveryTimeout(void);
extern EnumArcOutputStreamStatus UserInterfaceArcTxEarcStreamHandler(void);
extern EnumEarcAudioLatencyUpdateStatus UserInterfaceArcTxEarcCheckAudioLatencyUpdate(BYTE *pucAudioLatency);
extern EnumEarcRequestAudioLatencyResult UserInterfaceArcTxEarcSetRequestAudioLatency(BYTE ucAudioLatency);
extern EnumEarcCdsUpdateStatus UserInterfaceArcTxEarcCheckCdsUpdate(void);
extern EnumEarcCdsReloadResult UserInterfaceArcTxEarcCdsReload(BYTE *pucEarcRxCdsTable);
extern void UserInterfaceArcTxEarcSetChStatusMuteFlag(EnumAudioMuteStatus enumArcMute);
extern EnumAudioMuteStatus UserInterfaceArcTxEarcGetChStatusMuteFlag(void);
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//-------------------------------------------------------
// Extern functions from UserInterfaceCec.c
//-------------------------------------------------------
#if(_HDMI_CEC_SUPPORT == _ON)
extern void UserInterfaceCecReceivedNotify(StructCecRxReceivedInfo *pstCecRxInfo);
extern EnumCecTxTransmitTask UserInterfaceCecTransmitInfoPrepare(StructCecTxTransmitInfo *pstCecTxInfo);
extern void UserInterfaceCecHighLevelFlow(void);
extern EnumCecFunctionEnable UserInterfaceCecGetCecActive(void);
extern void UserInterfaceCecRequestSendCecMessage(EnumCECOpCode enumOpCode);

#if(_AUDIO_ARC_SUPPORT == _ON)
extern EnumCecOsdEnable UserInterfaceCecGetOsdCecEnable(void);
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_HDMI_CEC_SUPPORT == _ON)

//-------------------------------------------------------
// Extern functions from UserInterfaceColor.c
//-------------------------------------------------------
#if(_COLOR_IP_COLOR_CONVERT == _ON)
extern EnumRGBFormatStatus UserInterfaceColorGetColorRGBFormat(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_COLOR_FORMAT_CONVERT_FUNCTION == _ON)
extern void UserInterfaceColorSetColorFormat(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort);
#endif

#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
extern EnumRGBQuantLimitRangeStatus UserInterfaceColorGetRGBQuantizationLimitRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorRGBQuantization enumColorRGBQuantization);
#endif

#if((_YCC_QUANTIZATION_RANGE_FUNCTION == _ON) && (_YCC_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
extern EnumYccQuantFullRangeStatus UserInterfaceColorGetYCCQuantizationFullRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorYCCQuantization enumColorYCCQuantization);
#endif

#if(_COLOR_DEMO_FUNCTION == _ON)
extern EnumDemoModeType UserInterfaceColorGetDemoModeType(void);
#endif

#if(_DCR_FUNCTION == _ON)
extern void UserInterfaceColorDCRHandler(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_DCC_HISTOGRM_INFO_FUNCTION == _ON)
extern void UserInterfaceColorDCCHistogramHandler(EnumDisplayRegion enumDisplayRegion);
#endif

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
extern void UserInterfaceColorGetUltraVividData(EnumSelRegion enumSelRegion, StructUltraVividSetting *pstUltraVividData);
#endif

#if(_COLOR_IP_DCR == _ON)
extern void UserInterfaceColorGetDCRData(StructDCRSetting *pstDCRData);
#endif

#if((_COLOR_IP_DCC_HISTOGRAM == _ON) || (_COLOR_IP_DCC == _ON))
extern void UserInterfaceColorGetDCCHistogramData(StructDCCHistogramSetting *pstDCCHistogramData);
#endif

#if(_COLOR_IP_DCC == _ON)
extern void UserInterfaceColorGetDCCData(EnumSelRegion enumSelRegion, StructDCCSetting *pstDCCData);
#endif

#if(_COLOR_IP_CONTRAST == _ON)
extern void UserInterfaceColorGetContrastData(EnumSelRegion enumSelRegion, StructCtsSetting *pstCtsData);
#endif

#if(_COLOR_IP_BRIGHTNESS == _ON)
extern void UserInterfaceColorGetBrightnessData(EnumSelRegion enumSelRegion, StructBriSetting *pstBriData);
#endif

#if(_COLOR_IP_ICM == _ON)
extern void UserInterfaceColorGetICMData(EnumSelRegion enumSelRegion, StructICMSetting *pstICMData);
#endif

#if(_COLOR_IP_IAPS == _ON)
extern void UserInterfaceColorGetIAPSData(EnumSelRegion enumSelRegion, StructIAPSSetting *pstIAPSData);
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
extern void UserInterfaceColorGetInGammaData(EnumSelRegion enumSelRegion, StructInGammaSetting *pstIgData);
#endif

#if(_COLOR_IP_YMAPPING == _ON)
extern void UserInterfaceColorGetYmappingData(EnumSelRegion enumSelRegion, StructYmappingSetting *pstIYmData);
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
extern void UserInterfaceColorGetPostGammaData(EnumSelRegion enumSelRegion, StructPostGammaSetting *pstPgData);
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
extern void UserInterfaceColorGetOutGammaData(EnumSelRegion enumSelRegion, StructOutGammaSetting *pstOgData);
#endif

#if(_COLOR_IP_SRGB == _ON)
extern void UserInterfaceColorGetsRGBData(EnumSelRegion enumSelRegion, StructSRGBSetting *pstsRGBData);
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
extern void UserInterfaceColorGetDColorConvertData(EnumSelRegion enumSelRegion, StructDColorConvertSetting *pstDColorConvertData);
#endif

#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
extern void UserInterfaceColorGet3DGammaData(EnumSelRegion enumSelRegion, Struct3DGammaSetting *pst3DGammaData);
#if(_RGB_3D_GAMMA_CUBE_MAPPING_SUPPORT == _ON)
extern EnumFunctionOnOFF UserInterfaceColor3DGammaCubeGetEnableStatus(EnumSelRegion enumSelRegion);
#endif
#endif

#if(_COLOR_IP_UNIFORMITY == _ON)
extern void UserInterfaceColorGetUniformityData(EnumSelRegion enumSelRegion, StructUniformitySetting *pstUniData);
#if(_UNIFORMITY_CUSTOM_ENABLE_CONDITION_SUPPORT == _ON)
extern EnumFunctionOnOFF UserInterfaceColorGetUniformityCustomEnableStatus(void);
#endif
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
extern void UserInterfaceColorLowBlueGetData(StructColorEyeProtectSetting *pstColorProtectSetting);
extern EnumDynamicLowBlueType UserInterfaceColorLowBlueGetEnableStatus(void);
#endif
#if(_UNIFORMITY_PLUS_FUNCTION == _ON)
extern EnumFunctionOnOFF UserInterfaceColorUniformityPlusFunctionStatus(EnumSelRegion enumSelRegion);
#endif
#endif

#if(_COLOR_IP_HL_WIN == _ON)
extern void UserInterfaceColorGetHLWData(StructHLWSetting *pstHLWData);
#endif

#if(_COLOR_IP_SHARPNESS == _ON)
extern void UserInterfaceColorGetSharpnessData(EnumSelRegion enumSelRegion, StructSharpnessSetting *pstSharpnessData);
#endif

#if(_SD_TABLE_SEL_FUNCTION == _ON)
extern void UserInterfaceColorGetScalingDownCoef(EnumSelRegion enumSelRegion, StructScalingDownCoefSetting *pstScalingDownData, EnumByPassEnable enumBypassFSEnable);
#endif

#if(_COLOR_IP_BORDER_WIN == _ON)
extern void UserInterfaceColorGetBorderWindowData(StructBorderWindowSetting *pstBorderWindowData);
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
extern void UserInterfaceColorGetLocalContrastData(EnumSelRegion enumSelRegion, StructLocalContrastSetting *pstLocalContrastData);
extern void UserInterfaceColorGetLocalContrastTemporalData(StructLocalContrastTemporalSetting *pstLocalContrastData);
#endif

#if(_COLOR_IP_ANTI_ALIASING == _ON)
extern void UserInterfaceColorGetAntiAliasingData(StructAntiAliasingSetting *pstAntiAliasingData);
extern void UserInterfaceColorGetAntiAliasingCoefTableData(StructAntiAliasingSetting *pstAntiAliasingData);
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
extern EnumFunctionOnOFF UserInterfaceColorGetLocalContrastEnableStatus(EnumSelRegion enumSelRegion);
#endif

#if(_SDR_PLUS_FUNCTION == _ON)
extern EnumFunctionOnOFF UserInterfaceColorGetSDRPlusEnableStatus(EnumSelRegion enumSelRegion);
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
extern EnumNightSniperType UserInterfaceColorGetNightSniperEnableStatus(EnumSelRegion enumSelRegion);
#endif

#if(_OD_FUNCTION == _ON)
extern EnumFunctionOnOFF UserInterfaceColorGetODEnableStatus(void);
extern void UserInterfaceColorGetODData(StructODSetting *pstODData);
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
extern void UserInterfaceColorDataExchangeSendODGain(BYTE ucODGain);
extern void UserInterfaceColorDataExchangeSendODUserData(StructODSetting *pstODData);
extern void UserInterfaceColorDataExchangeSendODEnable(BYTE ucEnable);
#endif
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
extern EnumSDRCalibrationType UserInterfaceColorSDROCCOGCMode(void);
#endif

extern EnumSelRegion UserInterfaceColorGetOSDSystemSelRegion(void);
//-------------------------------------------------------
// Extern functions from UserInterfaceColorMRCM.c
//-------------------------------------------------------
#if(_MRCM_SUPPORT == _ON)
extern void UserInterfaceColorMRCMGetData(StructMRCMLoopData *pstMRCMLoopUserData);
extern void UserInterfaceColorMRCMReadResult(void);
extern void UserInterfaceColorMRCMApplication(void);
#endif // End of #if(_MRCM_SUPPORT == _ON)


//-------------------------------------------------------
// Extern functions from UserInterfaceDebug.c
//-------------------------------------------------------
#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
extern EnumDebugMode UserInterfaceDebugIIC(BYTE ucType, BYTE *pucDdcciArray, BYTE *pucReturnValue);
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceDdcci.c
//-------------------------------------------------------
#if(_DDCCI_CODE_REDUCTION == _OFF)

extern void UserInterfaceDdcciHandler(void);
extern EnumDdcciStatus UserInterfaceDdcciGetStatus(void);
extern void UserInterfaceDdcciGetInputMsg(void);


#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _ON)
extern void UserInterfaceDdcciGetCpStringData(BYTE *pucDest, EnumPortType enumPortType, WORD usStartIndex, WORD usLength);
extern WORD UserInterfaceDdcciGetCpStringSize(EnumPortType enumPortType);
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern EnumDdcciStatus UserInterfaceDdcciGetFactoryCommand(void);

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern EnumDdcciStatus UserInterfaceDdcciCheckHDMIFreesyncOpcode(BYTE ucOpcode);
#endif

#endif

#endif

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
extern void UserInterfaceDdcciCustomerDebugHandler(BYTE *pucRecvData, BYTE *pucReplyLen, BYTE *pucReplyData);
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceDisplay.c
//-------------------------------------------------------

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
extern EnumPIPSubAdjustMute UserInterfaceDisplayPIPSubAdjustMute(void);
#endif

extern EnumOsdLogoStatus UserInterfaceDisplayGetLogoStatus(void);
extern EnumNoSupportStatus UserInterfaceDisplayGetNoSupportStatus(void);
extern EnumNoSupportStatus UserInterfaceDisplayGetRegionNoSupportStatus(EnumDisplayRegion enumDisplayRegion);
extern EnumDclkNoSupportStatus UserInterfaceDisplayGetDclkNoSupportStatus(void);

#if(_OVERSCAN_SUPPORT == _ON)
extern EnumOverScanStatus UserInterfaceDisplayGetOverScanStatus(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
extern EnumAspectRatioType UserInterfaceDisplayGetAspectRatioType(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceDisplayGetAspectRatio(EnumDisplayRegion enumDisplayRegion, WORD *pusHRatio, WORD *pusVRatio);
extern void UserInterfaceDisplayAdjustAspectRatio(EnumDisplayRegion enumDisplayRegion);

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
extern WORD UserInterfaceDisplayGetAspectRatioMinDVHeight(void);
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern WORD UserInterfaceDisplayGetAspectRatioOriginalRatio(EnumDisplayRegion enumDisplayRegion);
#endif
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
extern EnumRotationType UserInterfaceDisplayGetRotationDegree(void);
extern EnumRotationDisplayType UserInterfaceDisplayGetRotationDisplayType(void);
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
extern BYTE UserInterfaceDisplayGetLatencyRatio(void);
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
extern BYTE UserInterfaceDisplayGetHDMIALLMOffLatencyRatio(void);
#endif

#if(_FRC_SUPPORT == _ON)
extern void UserInterfaceDisplayGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq);
#endif

extern void UserInterfaceDisplaySelectMDomainSettingForMain(StructCustomizedMdomain *pstCustomizedMdomain);

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
extern EnumFreeRunDdomainSetting UserInterfaceDisplayFreeRunDclkSettingSelect(void);
#endif

#if(_MULTI_DISPLAY_MAX > 0x01)
extern void UserInterfaceDisplaySelectMDomainSettingForSub(StructCustomizedMdomain *pstCustomizedMdomain);
#endif

extern void UserInterfaceDisplayAdjustInputTiming(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceDisplayAdjustDisplayTiming(EnumDisplayRegion enumDisplayRegion);

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
extern void UserInterfaceDisplayGetPipSubTimingFormat(StructTimingFormat *pstTimingFormat);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern void UserInterfaceDisplayGetEagleSightSubTimingFormat(StructTimingFormat *pstTimingFormat);
extern void UserInterfaceDisplaySetEagleSightSettingDefault(StructEagleSightSetting *pstEagleSightSetting);
extern void UserInterfaceDisplayGetEagleSightSetting(StructEagleSightSetting *pstEagleSightSetting);
extern void UserInterfaceDisplayAdjustEagleSightInputCapturePosition(StructEagleSightPosition *pstEagleSightPosition);
extern void UserInterfaceDisplayAdjustEagleSightDisplayCapturePosition(StructEagleSightPosition *pstEagleSightPosition);
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
extern void UserInterfaceColorGetCircleWindowData(StructCircleWindowSetting *pstCircleWindowData);
#endif
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
extern void UserInterfaceDisplayGetPbpTimingFormat(EnumDisplayRegion enumDisplayRegion, StructTimingFormat *pstTimingFormat);
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
extern void UserInterfaceDisplayGet3PFlagTimingFormat(EnumDisplayRegion enumDisplayRegion, StructTimingFormat *pstTimingFormat);
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
extern void UserInterfaceDisplayGet3PSkewLRTimingFormat(EnumDisplayRegion enumDisplayRegion, StructTimingFormat *pstTimingFormat);
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
extern void UserInterfaceDisplaySetPixelOrbitingOff(void);
#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
extern WORD UserInterfaceDisplayRotationSetPixelShiftNumInfo(void);
#endif
#endif

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
extern void UserInterfaceDisplayMbrBacklightAdjust(EnumMbrBacklightMode enumBacklightMode, bit bLightCtrl, WORD usDVTotal);
extern void UserInterfaceDisplayMbrAdimAdjust(EnumMbrBacklightMode enumBacklightMode, bit bLightCtrl);
extern EnumMbrPDimCtrl UserInterfaceDisplayMbrGetPdimControl(EnumMbrBacklightMode enumBacklightMode, bit bLightCtrl);
extern void UserInterfaceDisplayMbrPdimAdjust(EnumMbrBacklightMode enumBacklightMode, bit bLightCtrl);
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
extern BYTE UserInterfaceDisplayMbrGetBacklightDuty(void);
extern BYTE UserInterfaceDisplayMbrGetBacklightPosition(void);
#endif
extern EnumMbrBacklightMode UserInterfaceDisplayMbrGetBacklightMode(void);
extern EnumMbrBacklightSeq UserInterfaceDisplayMbrGetBacklightSequence(bit bLightCtrl);
extern WORD UserInterfaceDisplayMbrGetBacklightSequenceDelay(bit bLightCtrl);
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern EnumRtkAdvMbrUserStatus UserInterfaceDisplayGetRtkAdvMbrSetting(void);
#endif

#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
extern EnumMbrBFIMode UserInterfaceDisplayMbrGetBlackFrameInsertMode(void);
extern void UserInterfaceDisplayMbrBlackFrameInsertCtrl(EnumMbrBFIMode enumMbrBFIMode);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern EnumDrrFreeSyncDpGetIVF UserInterfaceDisplayDpFreeSyncGetIVFmaxFromLut(WORD *pusVfreqMax);
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern EnumDrrFreeSyncHdmiGetIVF UserInterfaceDisplayHdmiFreeSyncGetIVFmaxFromLut(WORD *pusVfreqMax);
#endif

#if(_HDMI21_VRR_SUPPORT == _ON)
extern EnumDrrVrrHdmiGetIVF UserInterfaceDisplayHdmiVrrGetIVFmaxFromLut(WORD *pusVfreqMax);
#endif

#if(_DRR_SUPPORT == _ON)
#if(_SEARCH_DRR_IVF_PRIORITY_BY_USER == _ON)
extern EnumDrrGetIVFPriority UserInterfaceDisplayGetDrrIVFByUser(EnumInputPort enumInputPort, WORD *pusIVfreq);
#endif
#endif

extern WORD UserInterfaceDisplayGetExtendedActiveWaitTime(void);

//-------------------------------------------------------
// Extern functions from UserInterfaceDisplayCalibration.c
//-------------------------------------------------------
#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_UNIFORMITY_FUNCTION == _ON))
extern void UserInterfaceColorCalibrationBeforeProc(EnumCaliType enumMode);
extern void UserInterfaceColorCalibrationAfterProc(EnumCaliType enumMode);
extern void UserInterfaceColorCalibrationAdjustBacklight(BYTE ucBacklight);

#if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)
extern void UserInterfaceColorCalibrationLDBoostAdjust(bit bBoost);
#endif

#if((_MULTI_BRI_CALIBRATION_TYPE != _MULTI_BRI_CALIBRATION_NONE) || (_OCC_RGB_3D_GAMMA_SUPPORT == _ON))
extern void UserInterfaceColorCalibrationAdjustMultiBacklight(EnumColorBacklightType enumColorBacklightType);
#endif
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
extern void UserInterfaceColorCalibrationBeforeDimmingProc(void);
extern void UserInterfaceColorCalibrationAfterDimmingProc(void);
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceDisplayCalibration.c
//-------------------------------------------------------

//-------------------------------------------------------
// Extern functions from UserInterfaceDp.c
//-------------------------------------------------------
#if(_DP_SUPPORT == _ON)
extern EnumDpVersionType UserInterfaceDpGetVersion(EnumInputPort enumInputPort);
extern EnumDpLinkRate UserInterfaceDpGetMaxLinkRate(EnumInputPort enumInputPort);
extern EnumDpLaneCount UserInterfaceDpGetLaneCount(EnumInputPort enumInputPort);
#if(_DP_PR_MODE_SUPPORT)
extern EnumDpPRModeSupport UserInterfaceDpPRModeGetEnable(EnumInputPort enumInputPort);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT)
extern EnumDpAuxlessAlpmSupport UserInterfaceDpAuxlessAlpmGetEnable(EnumInputPort enumInputPort);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern EnumDPMSTPort UserInterfaceDpGetMSTCapablePort(void);
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
extern EnumDpMstPxpMode UserInterfaceDpGetPxpMode(void);
extern EnumInputPort UserInterfaceDpGetPxpInputTarget(void);
extern EnumDpPxpPortNumSwapStatus UserInterfaceDpGetPxpPortNumSwapStatus(void);
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
extern EnumDPCloneOutputStatus UserInterfaceDpGetCloneOutputStatus(void);
extern EnumInputPort UserInterfaceDpGetCloneOutputUserInputPort(void);
#endif

#if(_DUAL_DP_SUPPORT == _ON)
extern EnumDPDualPortDefaultStatus UserInterfaceDpGetDualDefaultPort(void);
#endif

#if(_DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT == _ON)
extern EnumDpHpdToggleMode UserInterfaceDpGetDcOnHpdMode(void);
#endif

#if(_DP_USER_INT_FOR_SOURCE_WRITE_OUI_SUPPORT == _ON)
extern void UserInterfaceDpSourceWriteOuiHandler_EXINT0(EnumInputPort enumInputPort);
#endif
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
extern EnumGetHdmi5VStatus UserInterfaceDpGetHdmi5VStatus(BYTE ucInputPort);
#endif
//-------------------------------------------------------
// Extern functions from UserInterfaceEdid.c
//-------------------------------------------------------
#if(_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON)
extern void UserInterfaceEdidGetEmbeddedEdidData(EnumInputPortEdid enumInputPort);

#if((_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON) && ((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) || (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)))
extern void UserInterfaceEdidReloadHdmiExternalSwitchEmbeddedEdid(EnumInputPort enumInputPort);
#endif
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern EnumEdidReloadCheck UserInterfaceEdidCheckHdmiDscEdidIndexChange(EnumInputPort enumInputPort);
#endif
extern EnumHdmiEdidHpdBehavior UserInterfaceEdidGetHpdToggleResetToSearch(void);
extern EnumHdmiEdidLocation UserInterfaceEdidGetMultiHdmiEdidLocation(BYTE ucPortIndex, EnumEdidSelection enumEdidIndex);
extern EnumEdidSelection UserInterfaceEdidGetMultiHdmiEdidIndex(EnumInputPort enumInputPort);
#endif

#if((_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE) && ((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON)))
extern void UserInterfaceEdidGetExternalEdid(EnumInputPort enumInputPort, BYTE *pucEdidContent);
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceDpAdaptiveSync.c
//-------------------------------------------------------
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern EnumDpAdaptiveSyncSupport UserInterfaceDpAdaptiveSyncGetEnable(EnumInputPort enumInputPort);
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceFreeSync.c
//-------------------------------------------------------
#if((_FREESYNC_SUPPORT == _ON) || (_FREESYNC_II_SUPPORT == _ON))
extern EnumFreeSyncSupport UserInterfaceFreeSyncGetEnable(EnumInputPort enumInputPort);
extern BYTE UserInterfaceFreeSyncGetPanelIndex(void);
#if(_DP_FREESYNC_SUPPORT == _ON)
extern void UserInterfaceFreeSyncGetDpAupiPanelInfo(StructDrrAmdAupiInfo *pstDrrDpAmdAupiInfo);
#endif
#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern void UserInterfaceFreeSyncGetHdmiAupiPanelInfo(StructDrrAmdAupiInfo *pstDrrHdmiAmdAupiInfo);
extern BYTE UserInterfaceFreeSyncGetHdmiMccsAddress(void);
#endif
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceDscDecoder.c
//-------------------------------------------------------
#if(_DSC_DECODER_SUPPORT == _ON)
extern EnumDscDecoderSupport UserInterfaceDscDecoderGetEnable(EnumInputPort enumInputPort);
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
extern EnumDscDecoderSupport UserInterfaceDscDecoderMst2sstGetEnable(void);
#endif

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern void UserInterfaceDscDecoderGetEdidModifyParameter(StructDscHdmiEdidModifyParameter *pstructDscHdmiEdidModifyParameter);
#endif
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceGlobalDimming.c
//-------------------------------------------------------
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
extern void UserInterfaceColorGlobalDimmingAdjustPWM(WORD usPWMValue);
#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
extern WORD UserInterfaceColorGlobalDimmingGetMaxPWM(void);
extern WORD UserInterfaceColorGlobalDimmingGetMinPWM(void);
#endif
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceHdcp.c
//-------------------------------------------------------
#if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
extern void UserInterfaceHdcpGetKeyBksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserInterfaceHdcpGetKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_DP_TX_SUPPORT == _ON)
extern void UserInterfaceHdcpGetTxKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserInterfaceHdcpGetTxKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && ((_RX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER) || (_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER)))
extern void UserInterfaceHdcp2GetCertrxByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceHdcp2GetRSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceHdcp2GetRSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceHdcp2GetRSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceHdcp2GetRSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceHdcp2GetLCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern void UserInterfaceHdcp2GetDpTxRRMODNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceHdcp2GetDpTxDcpLlcNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceHdcp2GetDpTxEKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceHdcp2GetDpTxNPinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

//-------------------------------------------------------
// Extern functions from UserInterfaceHDR.c
//-------------------------------------------------------
#if(_ULTRA_HDR_SUPPORT == _ON)

extern void UserInterfaceColorHDRAdjustSDRProc(EnumDisplayRegion enumDisplayRegion);
extern EnumHDRDemoStatus UserInterfaceColorHDRGetHDRDemoModeEnable(void);
extern EnumHDRDemoStatus UserInterfaceColorHDRGetHDRDemoModeOutsideStatus(void);

#if(_HDR10_SUPPORT == _ON)
extern EnumHDR10ModeDef UserInterfaceColorHDRGetHDR10ModeStatus(EnumInputPort enumInputPort);
extern void UserInterfaceColorHDRAdjustHDR10Proc(EnumDisplayRegion enumDisplayRegion);

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
extern BYTE UserInterfaceColorHDRGetHDR10LightEnhanceGain(EnumDisplayRegion enumDisplayRegion);
#endif
#endif

extern void UserInterfaceColorHDRGetHDR10UserData(EnumDisplayRegion enumDisplayRegion, StructHDR10UserData *pstHDR10UserData);
#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern EnumHDR10AdjustEagleSightFullStatus UserInterfaceColorHDRGetEagleSightAdjustFullRegion(void);
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
extern void UserInterfaceColorHDRAdjustFreeSyncIIProc(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
extern EnumAdvancedHDR10Support UserInterfaceColorHDRGetAdvancedHDR10Enable(EnumDisplayRegion enumDisplayRegion);
#endif

#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)

//-------------------------------------------------------
// Extern functions from UserInterfaceColorDM.c
//-------------------------------------------------------
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern void UserInterfaceColorDMSetOsdEvent(EnumDisplayRegion enumDisplayRegion, EnumDMOsdEvent enumDMOsdEvent);
extern EnumDMSupport UserInterfaceColorDMGetEnableStatus(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceColorDMUpdatePictureMode(EnumDisplayRegion enumDisplayRegion, BYTE ucDMPictureMode);
extern void UserInterfaceColorDMAdjust(EnumDisplayRegion enumDisplayRegion, EnumHDRTargetStatus enumHDRTargetStatus, EnumDMAdjustType enumAdjustType);
extern void UserInterfaceColorDMGetData(EnumSelRegion enumSelRegion, Struct3rdPartyDMOsdSetting *pstDMOsdData);
#endif
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceKey.c
//-------------------------------------------------------
extern void UserInterfaceKeyHandler(void);

//-------------------------------------------------------
// Extern functions from UserInterfaceLocalDimming.c
//-------------------------------------------------------
#if(_LOCAL_DIMMING_FUNCTION == _ON)
extern EnumLocalDimmingStatus UserInterfaceColorLocalDimmingGetEnableStatus(void);
extern void UserInterfaceColorLocalDimmingGetData(StructLocalDimmingSetting * pstLocalDimmingData);
extern void UserInterfaceColorLocalDimmingRestoreBacklight(void);
extern EnumLocalDimmingType UserInterfaceColorLocalDimmingMultiPPolicy(void);
#if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)
extern BYTE UserInterfaceColorLocalDimmingBoostCoolingAdjust(BYTE ucBoostGain, BYTE ucPWMTotalRatio);
#endif // End of #if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)
#if(_LOCAL_DIMMING_COMPENSATE_MODE != _LD_COMPENSATE_NONE)
extern BYTE UserInterfaceColorLocalDimmingBoostGetCompADdim(void);
#endif
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceColorGlobalDimming.c
//-------------------------------------------------------
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
extern EnumGlobalDimmingStatus UserInterfaceColorGlobalDimmingGetEnableStatus(void);
extern void UserInterfaceColorGlobalDimmingRestoreBacklight(void);
extern EnumGlobalDimmingSubStatus UserInterfaceColorGlobalDimmingGetForceMainEffect(void);
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceMode.c
//-------------------------------------------------------
extern EnumBypassColorProcStatus UserInterfaceModeGetActiveByPassStatus(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceModeDisplayInitialColorProc(EnumDisplayMode enumDisplayMode);

#if((_PANEL_STYLE != _PANEL_VBO) || ((_PANEL_STYLE == _PANEL_VBO) && (_VBO_BACKLIGHT_BY_USER == _ENABLE)))
extern EnumBacklightAction UserInterfaceModeDisplaySettingGetBacklightAction(void);
#endif

#if(_FIRST_CHECK_CONTROL_BACKLIGHT_BY_USER == _ON)
extern EnumBacklightAction UserInterfaceModeFirstDisplayCheckGetBacklightAction(EnumDisplayMode enumDisplayMode);
#endif

extern void UserInterfaceModeDisplaySettingInitialization(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceModeDisplaySettingColorProc(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceModeDisplaySettingByPassColorProc(EnumDisplayRegion enumDisplayRegion);
#if(_COLOR_DEMO_FUNCTION == _ON)
extern void UserInterfaceModeDisplaySettingDemoModeColorProc(EnumSelRegion enumSelRegion);
#endif
extern void UserInterfaceModeDisplaySettingNormalModeColorProc(EnumSelRegion enumSelRegion);
extern void UserInterfaceModeDisplayActiveProc(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceModeResetProc(void);
extern void UserInterfaceModeResetRegionProc(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceModeResumeRegionProc(EnumDisplayRegion enumDisplayRegion);

//----------------------------------------------------------------------------------------
// Extern functions from UserInterfaceNVRam.c
//----------------------------------------------------------------------------------------
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
extern EnumFlashMoveDataResult UserInterfaceFlashMoveData(BYTE ucPageID, BYTE *pucData);
#endif

extern EnumNvramCheckResult UserInterfaceNVRamGetDataStatus(EnumNvramCheckType enumNvramCheckType);

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)
extern EnumNvramCheckResult UserInterfaceNVRamSystemEepromReadCustomProc(DWORD ulSubAddr, WORD usLength, BYTE *pucReadArray);
extern EnumNvramCheckResult UserInterfaceNVRamSystemEepromWriteCustomProc(DWORD ulSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceOsd.c
//-------------------------------------------------------
extern void UserInterfaceOsdHandler(void);
#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern void UserInterfaceOsdForEagleSightModify(EnumDBApply enumDBApply);
#endif

//-------------------------------------------------------
// Extern functions from UserInterfacePower.c
//-------------------------------------------------------
#if(_PANEL_POWER_SEQUENCE_CONTROL_BY_USER == _ON)
extern void UserInterfacePowerPanelAction(EnumPanelPowerSeq enumEvent);
#endif

extern void UserInterfacePowerPanelTimerEventHandler(BYTE ucAction);
extern void UserInterfacePowerPanelWaitT1(void);
extern void UserInterfacePowerPanelWaitT2(void);
extern void UserInterfacePowerPanelWaitT3(void);
extern void UserInterfacePowerPanelWaitT4(void);
extern void UserInterfacePowerPanelWaitT5(void);

extern void UserInterfacePowerSwitch(EnumPowerAction enumSwitch);
extern void UserInterfacePowerAcOnInitial(void);
extern void UserInterfacePowerOnInitial(void);

extern EnumForcePSStatus UserInterfacePowerGetForcePSStatus(void);
extern EnumPSPermissionStatus UserInterfacePowerGetIntoPSStatus(void);
extern EnumForceFakePS UserInterfacePowerGetFakePSStatus(void);
extern EnumForceFakePowerOff UserInterfacePowerGetFakeOffStatus(void);

//-------------------------------------------------------
// Extern functions from UserInterfaceSource.c
//-------------------------------------------------------
extern EnumDisplayRegion UserInterfaceSourceGetAutoSearchTarget(void);
extern EnumInputPort UserInterfaceSourceGetInputPort0(void);

#if(_MULTI_DISPLAY_MAX >= 0x02)
extern EnumInputPort UserInterfaceSourceGetInputPort1(void);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
extern EnumInputPort UserInterfaceSourceGetInputPort2(void);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
extern EnumInputPort UserInterfaceSourceGetInputPort3(void);
#endif

extern EnumCableResetStatus UserInterfaceSourceGetCableResetStatus(EnumDisplayRegion enumDisplayRegion);

#if(_MULTI_DISPLAY_MAX != 0x01)
extern EnumAutoSearchStatus UserInterfaceSourceGetRegionAutoSearchStatus(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort);
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
extern EnumAutoSearchStatus UserInterfaceSourceAdjustOsdCheckTotalSearchFinish(void);
extern void UserInterfaceSourceAdjustSourceSearchTime(void);
extern WORD UserInterfaceSourceGetEizoSearchFinishTime(void);
#endif

extern EnumSourceDetectionInfo UserInterfaceSourceBypassDetection(void);

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
extern EnumInputPort UserInterfaceSourceHdmiExternalSwitchDefaultPort(void);
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
extern BYTE UserInterfaceSourceGetHpSwitchOsdEventTime(BYTE ucSourceScanType);
extern EnumSourceHpPxpSubScanType UserInterfaceSourceGetHpPxpSubAutoScan(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserInterfaceTimer.c
//----------------------------------------------------------------------------------------
extern void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID);

#if(_INSTANT_TIMER_EVENT_0 == _ON)
extern void UserInterfaceTimer0InstantAccess_T0INT(void);
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
extern void UserInterfaceTimer1InstantAccess_T1INT(void);
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
extern void UserInterfaceTimer2InstantAccess_T2INT(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserInterfaceTmds.c
//----------------------------------------------------------------------------------------
#if(_HDMI_SUPPORT == _ON)
extern EnumUserForcePSTmdsHpdToggle UserInterfaceTmdsForcePSWakeupHpdToggle(void);

#if(((_HDMI20_SUPPORT == _ON) || (_AUDIO_ARC_SUPPORT == _ON)) && (_HDMI_5V_DETECT_BY_USER == _ON))
extern EnumUserHdmi5vStatus UserInterfaceTmds5vPinDetect(EnumInputPort enumInputPort);
#endif

#if(_DELL_HDMI_HPD_DDC_STYLE_SUPPORT == _ON)
extern EnumUserDdcStatus UserInterfaceTmdsSetHdcpScdcStatusWhenAcOn(void);
#endif
#endif

//-------------------------------------------------------
// Extern functions from UserInterfaceUart.c
//-------------------------------------------------------
#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
extern void UserInterfaceUartExt0IntHandler(void);
extern DWORD UserInterfaceUartExt0GetPowerNormalBaudRate(void);
extern DWORD UserInterfaceUartExt0GetPowerSavingBaudRate(void);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
extern void UserInterfaceUartExt1IntHandler(void);
extern DWORD UserInterfaceUartExt1GetPowerNormalBaudRate(void);
extern DWORD UserInterfaceUartExt1GetPowerSavingBaudRate(void);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
extern void UserInterfaceUartExt2IntHandler(void);
extern DWORD UserInterfaceUartExt2GetPowerNormalBaudRate(void);
extern DWORD UserInterfaceUartExt2GetPowerSavingBaudRate(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserInterfaceUsb.c
//----------------------------------------------------------------------------------------
#if(_USB_SUPPORT == _ON)
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
extern EnumUsbHubMode UserInterfaceUsbGetOsdU3Mode(EnumInputPort enumInputPort);
#endif  // End of #if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
extern EnumUsbHubMode UserInterfaceUsbGetOsdTxU3Mode(EnumOutputPort enumOutputPort);
#endif  // End of #if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
#endif  // End of #if(_USB_SUPPORT == _ON)

//----------------------------------------------------------------------------------------
// Extern functions from UserInterfaceUsbTypeC.c
//----------------------------------------------------------------------------------------
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
extern EnumTypeCPinAssignmentESupportStatus UserInterfaceUsbTypeCGetOsdPinAssignmentESupportSelection(EnumInputPort enumInputPort);
#endif  // End of #if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
extern EnumTypeCPinCfgCapType UserInterfaceUsbTypeCGetPinAssignmentConfig(EnumInputPort enumInputPort, EnumTypeCU3ModeType enumU3ModeSel, EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportSel);
extern EnumTypeCMultiFuncStatus UserInterfaceUsbTypeCGetMultiFuncConfig(EnumInputPort enumInputPort, EnumTypeCU3ModeType enumU3ModeSel);
#endif  // End of #if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)

#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
extern EnumTypeCPinAssignmentESupportStatus UserInterfaceUsbTypeCGetOsdTxPinAssignmentESupportSelection(EnumOutputPort enumOutputPort);
#endif  // End of #if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
extern EnumTypeCPinCfgCapType UserInterfaceUsbTypeCGetTxPinAssignmentConfig(EnumOutputPort enumOutputPort, EnumTypeCU3ModeType enumU3ModeSel, EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportSel);
extern EnumTypeCMultiFuncStatus UserInterfaceUsbTypeCGetTxMultiFuncConfig(EnumOutputPort enumOutputPort, EnumTypeCU3ModeType enumU3ModeSel);
#endif  // End of #if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)

extern EnumTypeCPinMismatchAction UserInterfaceUsbTypeCGetPinAssignmentMismatchAction(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserInterfaceUsbTypeCUpdateDisplayConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment);
extern EnumTypeCAltModeWaitStatus UserInterfaceUsbTypeCGetDpAltModeWaitStatus(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCFunctionSupport UserInterfaceUsbTypeCGetFunctionSupport(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCOperationMode UserInterfaceUsbTypeCGetOperationMode(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserInterfaceUsbTypeCGetStatusEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCStatusEvent *pstStatusEvent);
extern void UserInterfaceUsbTypeCGetAlertEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAlertEvent *pstAlertEvent);
#if(_TYPE_C_EIZO_CUSTOMIZED_DP_LANE_CNT_SUPPORT == _ON)
extern EnumDpLaneCount UserInterfaceUsbTypeCGetAltModeLaneCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment);
#endif
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern EnumTypeCLenovoCheckDeviceTypeResult UserInterfaceUsbTypeCCheckLenovoDeviceTypeValid(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCLenovoDeviceType enumLenovoDeviceType);
extern void UserInterfaceUsbTypeCLenovoAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoSysEvent stLenovoSysEvent);
extern void UserInterfaceUsbTypeCGetLenovoDockingEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoDockEvent *pstLenovoDockEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern void UserInterfaceUsbTypeCAcerAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAcerSysEvent stAcerSysEvent);
extern void UserInterfaceUsbTypeCGetAcerUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAcerUserEvent *pstAcerUserEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern void UserInterfaceUsbTypeCHpAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCHpSysEvent stHpSysEvent);
extern void UserInterfaceUsbTypeCGetHpUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCHpUserEvent *pstHpUserEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern EnumTypeCDellInitCompleteStatus UserInterfaceUsbTypeCGetDellAltModeInitComplete(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserInterfaceUsbTypeCDellAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCDellSysEvent stDellSysEvent);
extern void UserInterfaceUsbTypeCGetDellUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCDellUserEvent *pstDellUserEvent);
#endif
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

#if(_PORT_CTRL_RTS_SUPPORT == _ON)
#if(_TYPE_C_PORT_CTRL_RTS_SMBUS_MODE == _PORT_CTRL_RTS_INT_MODE)
extern void UserInterfaceUsbTypeCRtsGetNotifyEn(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCRtsNotifyEn *pstTypeCNotifyEn);
#endif
extern BYTE UserInterfaceUsbTypeCTurnOnRtsStatusUpdate(EnumTypeCPcbPort enumTypeCPcbPort);
#endif // End of #if(_PORT_CTRL_RTS_SUPPORT == _ON)

#if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON) || (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))
extern void UserInterfaceUsbTypeCPowerControl(EnumPowerAction enumSwitch);
extern EnumTypeCPortCtrlReconnectStatus UserInterfaceUsbTypeCGetPowerOnReconnectStatus(EnumTypeCPcbPort enumTypeCPcbPort, EnumPowerAction enumSwitch);
#endif // End of #if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON) || (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))

#if(_PORT_CTRL_USER_SERIES_SUPPORT == _ON)
#if(_PORT_CTRL_USER_DET_CC_ATTACH_BY_SMBUS == _ON)
extern EnumTypeCAttachStatus UserInterfaceUsbTypeCUserGetCcAttachByI2C(EnumInputPort enumInputPort);
#endif
#if(_PORT_CTRL_USER_DET_ALT_MODE_READY_BY_SMBUS == _ON)
extern EnumTypeCAltModeStatus UserInterfaceUsbTypeCUserGetAltModeReadyByI2C(EnumInputPort enumInputPort);
#endif
extern EnumTypeCUserPortCtrlRespStatus UserInterfaceUsbTypeCUserReconnect(EnumInputPort enumInputPort);
#if(_PORT_CTRL_EXT_DET_ORIENTATION_SUPPORT == _ON)
extern EnumTypeCOrientation UserInterfaceUsbTypeCUserGetOrientation(EnumInputPort enumInputPort);
#endif
extern EnumTypeCPinCfgType UserInterfaceUsbTypeCUesrGetPinAssignment(EnumInputPort enumInputPort);
extern EnumTypeCPowerRole UserInterfaceUsbTypeCUserGetPowerRole(EnumInputPort enumInputPort);
extern EnumTypeCDataRole UserInterfaceUsbTypeCUserGetDataRole(EnumInputPort enumInputPort);
extern void UserInterfaceUsbTypeCUserSetPdoCnt(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt);
extern void UserInterfaceUsbTypeCUserSetPdo(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo);
extern void UserInterfaceUsbTypeCUserSetRdo(EnumInputPort enumInputPort, StructTypeCUserRDO stTypeCUserRdo);
extern void UserInterfaceUsbTypeCUserCcFunctionControl(EnumInputPort enumInputPort, EnumTypeCCcFunction enumCcFunction);
extern EnumTypeCPdoNumber UserInterfaceUsbTypeCUserGetPdoCnt(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole);
extern void UserInterfaceUsbTypeCUserGetPdo(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO *pstPDO);
extern EnumTypeCPdoNumber UserInterfaceUsbTypeCUserGetPartnerPdoCnt(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole);
extern void UserInterfaceUsbTypeCUserGetPartnerPdo(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO *pstPartnerPDO);
extern void UserInterfaceUsbTypeCUserGetPdoStatus(EnumInputPort enumInputPort, WORD *pusVoltage, WORD *pusCurrent);
extern void UserInterfaceUsbTypeCUserGetRequestedSrcPdo(EnumInputPort enumInputPort, StructTypeCUserPDO *pstSrcPDO);
extern EnumTypeCUserPortCtrlRespStatus UserInterfaceUsbTypeCUserGetFwVersion(EnumInputPort enumInputPort, StructTypeCPortCtrlFwVersion *pstTypeCFwVersion);
extern void UserInterfaceUsbTypeCUserGetCableInfoForDpcd(EnumInputPort enumInputPort, StructTypeCCableInfoForDpcd *pstTypeCCableInfoForDpcd);
extern EnumTypeCUserPortCtrlRespStatus UserInterfaceUsbTypeCUserConfigPinAssignment(EnumInputPort enumInputPort, EnumTypeCPinCfgCapType enumPinAssignment);
extern EnumTypeCUserPortCtrlRespStatus UserInterfaceUsbTypeCUserConfigMultiFunction(EnumInputPort enumInputPort, EnumTypeCMultiFuncStatus enumMultiFunction);
#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
extern EnumTypeCLenovoAltModeStatus UserInterfaceUsbTypeCUserGetLenovoAltModeReady(EnumInputPort enumInputPort);
extern EnumTypeCLenovoDeviceType UserInterfaceUsbTypeCUserGetLenovoDeviceType(EnumInputPort enumInputPort);
extern void UserInterfaceUsbTypeCUserGetLenovoSystemEvent(EnumInputPort enumInputPort, StructTypeCLenovoSysEvent *pstLenovoSysEvent);
extern void UserInterfaceUsbTypeCUserSetLenovoDockingEvent(EnumInputPort enumInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
extern EnumTypeCLenovoCheckBusyResult UserInterfaceUsbTypeCUserCheckLenovoDockingEventBusy(EnumInputPort enumInputPort);
#endif
#endif // End of #if(_PORT_CTRL_USER_SERIES_SUPPORT == _ON)

extern EnumTypeCPdoReference UserInterfaceUsbTypeCPdoReference(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern EnumTypeCRdoReference UserInterfaceUsbTypeCRdoReference(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD UserInterfaceUsbTypeCGetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD UserInterfaceUsbTypeCGetAvailablePower(EnumTypeCPcbPort enumTypeCPcbPort, WORD usMaxPower);
extern void UserInterfaceUsbTypeCGetSnkInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCSnkInfo *pstTypeCSnkInfo);
extern EnumTypeCPdoNumber UserInterfaceUsbTypeCGetPdoCount(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
#if(_PORT_CTRL_PD3_1_EPR_SUPPORT == _ON)
extern EnumTypeCPdoNumber UserInterfaceUsbTypeCGetEPRPdoCount(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
#endif
extern void UserInterfaceUsbTypeCGetSrcPdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserSrcPdo);
extern void UserInterfaceUsbTypeCGetSnkPdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserSnkPdo);
extern void UserInterfaceUsbTypeCGetInitRdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserInitRDO *pstTypeCUserInitRdo);
extern void UserInterfaceUsbTypeCGetRdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO *pstTypeCUserRdo);
extern EnumTypeCUnconstrainPowerExist UserInterfaceUsbTypeCGetUnconstrainedPow(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCSpmOperation UserInterfaceUsbTypeCSpmOperation(void);
extern void UserInterfaceUsbTypeCSystemPowerManagement(void);
extern WORD UserInterfaceUsbTypeCGetAdaptorPower(void);
extern WORD UserInterfaceUsbTypeCGetHubPower(void);
extern EnumBillboardCtrl UserInterfaceUsbTypeCGetBillboardSupport(EnumHubDsp enumHubDsp);

#if((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON))
extern EnumTypeCEmbVbusProtectReference UserInterfaceUsbTypeCEmbeddedGetVbusProtectReference(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserInterfaceUsbTypeCEmbeddedGetVbusProtectInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCVbusProtectInfo *pstTypeCVbusProtectInfo);
extern BYTE UserInterfaceUsbTypeCEmbeddedGetVbusDischargeCount(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)
extern EnumTypeCLocalPowerExist UserInterfaceUsbTypeCGetLocalPow(void);
#endif
#endif // End of #if((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON))
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
extern EnumBillboardProgramCtrl UserInterfaceUsbTypeCBBProgramEnable(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserInterfaceUsbTypeCBBCustomCommand(StructUsbBillboardCustomCommandInfo *pststUsbBillboardCustomCommandInfo);
#endif // End of #if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
#endif // End of #if(_BILLBOARD_SCALER_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

//----------------------------------------------------------------------------------------
// Extern functions from UserInterfaceUsbHub.c
//----------------------------------------------------------------------------------------
#if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
extern void UserInterfaceUsbHubDspChangeProc(EnumInputPort enumInputPort);
extern EnumUsbHubCtrMode UserInterfaceUsbHubGetCtrlMode(EnumInputPort enumInputPort);
extern EnumUsbHubSetU3ModeFailureType UserInterfaceUsbHubSetSSMode(EnumInputPort enumInputPort, bit bEn);
extern EnumHubDspDetectStatus UserInterfaceUsbHubGetDFPStatus(EnumInputPort enumInputPort);
extern WORD UserInterfaceUsbHubSetPollingStep(EnumInputPort enumInputPort);
#endif // End of #if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)

#if(_BILLBOARD_HUB_SUPPORT == _ON)
extern void UserInterfaceUsbHubBillboardControl(EnumInputPort enumInputPort, EnumBillboardCtrl enumAtion);
extern void UserInterfaceUsbHubBillboardHandler(EnumInputPort enumInputPort);
#endif

#if(_USB_HUB_SUPPORT == _ON)
extern EnumUsbHubOSDResult UserInterfaceUsbHubGetOSDSelectResult(void);
extern BYTE UserInterfaceUsbHubPathEnableCond(EnumInputPort enumInputPort);
extern void UserInterfaceUsbHubTypeBProcess(void);
extern void UserInterfaceUsbHubPowerControl(EnumInputPort enumInputPort, bit bEnable);
extern WORD UserInterfaceUsbHubDisableDurationTime(void);
#if(_USB3_REPEATER_SUPPORT == _ON)
extern EnumUSBPDSupportStatus UserInterfaceUsbHubGetUSBPDSupportStatus(EnumInputPort enumInputPort);
extern EnumUSBPSSupportStatus UserInterfaceUsbHubGetUSBPSSupportStatus(EnumInputPort enumInputPort);
#endif // End of #if(_USB3_REPEATER_SUPPORT == _ON)
#endif // End of #if(_DP_USB_HUB_SUPPORT == _ON)

//----------------------------------------------------------------------------------------
// Extern functions from UserInterfaceVga.c
//----------------------------------------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
extern WORD UserInterfaceVgaGetModeFlashIdBase(void);
#endif

extern BYTE UserInterfaceVgaGetConfuseMode(BYTE ucModeIndex);
extern EnumModeTableStatus UserInterfaceVgaGetLoadModeTableDefaultStatus(void);
extern EnumAutoConfigAction UserInterfaceVgaGetFirstAutoConfigStatus(void);
extern void UserInterfaceVgaGetAutoConfigPercentage(BYTE ucAutoPercentage);
extern EnumAutoConfigSkip UserInterfaceVgaSkipAutoVpos(void);
extern EnumAutoConfigSkip UserInterfaceVgaSkipAutoHpos(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserInterfaceDualbank.c
//----------------------------------------------------------------------------------------
#if(_DUAL_BANK_SUPPORT == _ON)
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
#if(_DUAL_BANK_USER_FLAG_CUSTOMER_TYPE == _DUAL_BANK_USER_TYPE)
extern EnumFwUpdateWriteFlagResult UserInterfaceDualBankFwUpdateWriteDoneFlag(WORD usFlagBank, WORD usFlagAddr);
#endif
#endif
#endif

#endif // End of #ifndef __USER_INTERFACE_FUNCTION_API__

