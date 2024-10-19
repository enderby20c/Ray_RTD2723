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
// ID Code      : ScalerAudioInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))
//--------------------------------------------------
// Definitions of DP Audio Frequency Paramater
//--------------------------------------------------
#define _DP_SAMPLING_FREQ_32K_GROUP_NF_CODE                             0x000C9045 // [21:16]: N code, [15:0]: F code
#define _DP_SAMPLING_FREQ_44K_GROUP_NF_CODE                             0x000B6158 // [21:16]: N code, [15:0]: F code
#define _DP_SAMPLING_FREQ_48K_GROUP_NF_CODE                             0x000C9045 // [21:16]: N code, [15:0]: F code

#define _DP_SAMPLING_FREQ_32K_GROUP_S_CODE                              (0x30 & 0x7F)
#define _DP_SAMPLING_FREQ_44K_GROUP_S_CODE                              (0x20 & 0x7F)
#define _DP_SAMPLING_FREQ_48K_GROUP_S_CODE                              (0x20 & 0x7F)

#endif // End of #if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of HDMI Audio Frequency Paramater
//--------------------------------------------------
#define _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE                            0xB0
#define _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE                            0xA0
#define _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE                            0xA0

#define _HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE                            0x0C
#define _HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE                            0x0B
#define _HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE                            0x0C

#define _HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE                            0x9045
#define _HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE                            0x6159
#define _HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE                            0x9045

//--------------------------------------------------
//  Audio SPDIF/IIS PATH Options
//--------------------------------------------------
#define _AUDIO_BYPASS_PATH                                              0
#define _AUDIO_DVC_PATH                                                 1

//--------------------------------------------------
// Definitions of Audio DP Capability info
//--------------------------------------------------
#if(_DP_SUPPORT == _ON)
#define GET_AUDIO_DP_D0_CAPABILITY_SWITCH()                             (g_stAudioDpCapabilityInfo.b1DpD0CapabilitySwitch)
#define SET_AUDIO_DP_D0_CAPABILITY_SWITCH()                             (g_stAudioDpCapabilityInfo.b1DpD0CapabilitySwitch = _TRUE)
#define CLR_AUDIO_DP_D0_CAPABILITY_SWITCH()                             (g_stAudioDpCapabilityInfo.b1DpD0CapabilitySwitch = _FALSE)

#define GET_AUDIO_DP_D1_CAPABILITY_SWITCH()                             (g_stAudioDpCapabilityInfo.b1DpD1CapabilitySwitch)
#define SET_AUDIO_DP_D1_CAPABILITY_SWITCH()                             (g_stAudioDpCapabilityInfo.b1DpD1CapabilitySwitch = _TRUE)
#define CLR_AUDIO_DP_D1_CAPABILITY_SWITCH()                             (g_stAudioDpCapabilityInfo.b1DpD1CapabilitySwitch = _FALSE)

#define GET_AUDIO_DP_D2_CAPABILITY_SWITCH()                             (g_stAudioDpCapabilityInfo.b1DpD2CapabilitySwitch)
#define SET_AUDIO_DP_D2_CAPABILITY_SWITCH()                             (g_stAudioDpCapabilityInfo.b1DpD2CapabilitySwitch = _TRUE)
#define CLR_AUDIO_DP_D2_CAPABILITY_SWITCH()                             (g_stAudioDpCapabilityInfo.b1DpD2CapabilitySwitch = _FALSE)

#define GET_AUDIO_DP_D0_SUPPORT()                                       (g_stAudioDpCapabilityInfo.b1DpD0Support)
#define SET_AUDIO_DP_D0_SUPPORT(x)                                      (g_stAudioDpCapabilityInfo.b1DpD0Support = (x))

#define GET_AUDIO_DP_D1_SUPPORT()                                       (g_stAudioDpCapabilityInfo.b1DpD1Support)
#define SET_AUDIO_DP_D1_SUPPORT(x)                                      (g_stAudioDpCapabilityInfo.b1DpD1Support = (x))

#define GET_AUDIO_DP_D2_SUPPORT()                                       (g_stAudioDpCapabilityInfo.b1DpD2Support)
#define SET_AUDIO_DP_D2_SUPPORT(x)                                      (g_stAudioDpCapabilityInfo.b1DpD2Support = (x))
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_AUDIO_ARC_SUPPORT == _ON)
#define GET_AUDIO_ARC_TX_LINK_MODE()                                    (g_enumAudioArcTxLinkMode)
#define SET_AUDIO_ARC_TX_LINK_MODE(x)                                   (g_enumAudioArcTxLinkMode = (x))

#define GET_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT()               (g_stAudioArcTxTimerCtrl.b1DrivingChangeKeepoutTimeout)
#define SET_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT()               (g_stAudioArcTxTimerCtrl.b1DrivingChangeKeepoutTimeout = _TRUE)
#define CLR_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT()               (g_stAudioArcTxTimerCtrl.b1DrivingChangeKeepoutTimeout = _FALSE)

#define GET_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMER_ACTIVE()          (g_stAudioArcTxTimerCtrl.b1DrivingChangeKeepoutTimerActive)
#define SET_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMER_ACTIVE()          (g_stAudioArcTxTimerCtrl.b1DrivingChangeKeepoutTimerActive = _TRUE)
#define CLR_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMER_ACTIVE()          (g_stAudioArcTxTimerCtrl.b1DrivingChangeKeepoutTimerActive = _FALSE)

#if(_AUDIO_EARC_SUPPORT == _ON)
#define GET_AUDIO_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT()   (g_stAudioArcTxTimerCtrl.b1ForceEarcDiscInitByHpdToggleTimeout)
#define SET_AUDIO_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT()   (g_stAudioArcTxTimerCtrl.b1ForceEarcDiscInitByHpdToggleTimeout = _TRUE)
#define CLR_AUDIO_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT()   (g_stAudioArcTxTimerCtrl.b1ForceEarcDiscInitByHpdToggleTimeout = _FALSE)
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)

//-------------------------------------------------
// Audio Parallel Debug Mode Support On
//-------------------------------------------------
#ifndef _AUDIO_FORCE_PARALLEL_MODE
#define _AUDIO_FORCE_PARALLEL_MODE                                      _OFF
#endif

#endif // End of #if(_AUDIO_SUPPORT == _ON)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))
//--------------------------------------------------
// Enumerations of Audio Input Port
//--------------------------------------------------
typedef enum
{
    _AUDIO_FROM_RX0_PORT = 0x00,
    _AUDIO_FROM_RX1_PORT,
    _AUDIO_FROM_RX2_PORT,
    _AUDIO_FROM_RX3_PORT,
    _AUDIO_FROM_RX4_PORT,
    _AUDIO_FROM_RX5_PORT,
    _AUDIO_FROM_ADC_PORT,
    _AUDIO_FROM_PXP_PORT,
    _AUDIO_FROM_MST2SST_PORT,
} EnumAudioInputPort;

#endif // End of #if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of Audio Port Map Type
//--------------------------------------------------
typedef enum
{
    _AUDIO_PORT_MAP_TO_CURRENT = 0x00,
    _AUDIO_PORT_MAP_TO_TARGET,
} EnumAudioPortMapType;

//--------------------------------------------------
// Enumerations of Audio Spdif/Iis Output Select
//--------------------------------------------------
typedef enum
{
    _AUDIO_SELECT_BY_CA_MODE,
    _AUDIO_DEFAULT_MODE,
} EnumAudioIisSpdifOutput;

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Struct for DP Audio Support
//--------------------------------------------------
typedef struct
{
    BYTE b1DpD0CapabilitySwitch : 1;
    BYTE b1DpD1CapabilitySwitch : 1;
    BYTE b1DpD2CapabilitySwitch : 1;

    EnumAudioDpDpcdSupport b1DpD0Support : 1;
    EnumAudioDpDpcdSupport b1DpD1Support : 1;
    EnumAudioDpDpcdSupport b1DpD2Support : 1;
} StructAudioDpCapabilityInfo;
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Struct for Audio ARC/eARC Timer Control
//--------------------------------------------------
typedef struct
{
    BYTE b1DrivingChangeKeepoutTimeout : 1;
    BYTE b1DrivingChangeKeepoutTimerActive : 1;
#if(_AUDIO_EARC_SUPPORT == _ON)
    BYTE b1ForceEarcDiscInitByHpdToggleTimeout : 1;
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
} StructAudioArcTxTimerCtrl;
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_AUDIO_SUPPORT == _ON)
#if(_DP_SUPPORT == _ON)
extern StructAudioDpCapabilityInfo g_stAudioDpCapabilityInfo;
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_AUDIO_ARC_SUPPORT == _ON)
extern EnumAudioArcMode g_enumAudioArcTxLinkMode;
extern StructAudioArcTxTimerCtrl g_stAudioArcTxTimerCtrl;
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))
extern EnumAudioSamplingFreqPacket ScalerAudioGetSamplingFreqPacket(EnumAudioSamplingFreqType enumSamplingFreqType);
extern EnumAudioInputPort ScalerAudioGetDigitalAudioPort(EnumAudioOutputType enumAudioOutput);
extern EnumAudioSamplingFreqType ScalerAudioDpRecoverHbrAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq);

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
extern bit ScalerAudioDpGetHbr8ChannelSupport(EnumAudioOutputType enumAudioOutput);
extern bit ScalerAudioDpGetHbrOperationState(EnumAudioOutputType enumAudioOutput);
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

extern EnumAudioChannelCount ScalerAudioGetRxChannelCount(EnumAudioOutputType enumAudioOutput);
#endif // End of #if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON))

#if(_AUDIO_SUPPORT == _ON)
extern void ScalerAudioInitial(void);
extern void ScalerAudioDacDisable(void);
extern bit ScalerAudioSourceChangeCheck(EnumInputPort enumPowerCutOnPort, EnumPortType enumPowerCutOnPortType);
extern void ScalerAudioSourceInputSwitch(EnumAudioInputSource enumAudioSourceType, EnumInputPort enumInputPort);
extern bit ScalerAudioGetAudioInputPortChanged(EnumAudioInputSource enumAudioSourceType, EnumInputPort enumInputPort);
extern void ScalerAudioSyncUserDefineFrequencyPllSetting(void);
extern EnumAudioInputPort ScalerAudioDxToRxMapping(EnumInputPort enumInputPort, EnumAudioPortMapType enumAudioPortMapType);
extern EnumAudioSamplingFreqPacket ScalerAudioSamplingFreqDetect(EnumInputPort enumInputPort);
extern bit ScalerAudioSamplingFreqChange(EnumAudioOutputType enumAudioOutput);
extern EnumInputPort ScalerAudioGetDigitalAudioPortMapping(EnumAudioOutputType enumAudioOutput);
extern void ScalerAudioWatchDogProc(bit bOn, EnumInputPort enumInputPort, EnumAudioOutputType enumAudioOutput);
extern bit ScalerAudioCheckModeSwitch(EnumInputPort enumInputPort);
extern void ScalerAudioModeSwitchProcess(EnumInputPort enumInputPort);
extern void ScalerAudioDigitalDetect(void);
extern BYTE ScalerAudioGetDigitalAudioSource(EnumInputPort enumInputPort);
extern void ScalerAudioInputDigitalMute(bit bMute, EnumAudioOutputType enumAudioOutput);
extern void ScalerAudioMuteProc(bit bMute, WORD usVolume);
extern void ScalerAudioDigitalVolumeMute(bit bMute, WORD usVolume);
extern bit ScalerAudioGetAudioDetected(EnumInputPort enumInputPort);
extern bit ScalerAudioLPCMCheckData(EnumAudioOutputType enumAudioOutput);
extern bit ScalerAudioLPCMCheckChange(EnumAudioOutputType enumAudioOutput);
extern void ScalerAudioLPCMResetProc(EnumInputPort enumInputPort, EnumAudioOutputType enumAudioOutput);
extern void ScalerAudioDigitalAdjustVolume(WORD usVolume);
extern void ScalerAudioDVCSetVolumeMuteStatus(bit bMute);
extern EnumAudioCodingType ScalerAudioGetNonLPCMStatus(void);
extern EnumAudioCodingType ScalerAudioGetPathNonLPCMStatus(EnumAudioOutputType enumAudioOutput);

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
extern void ScalerAudioDVCVolumeFastMute(bit bMute, WORD usVolume);
#endif

extern void ScalerAudioDVCAdjustVolume(WORD usVolume);
extern bit ScalerAudioDVCGetVolumeMuteStatus(void);
extern void ScalerAudioInputDigitalReset(EnumInputPort enumInputPort, EnumAudioOutputType enumAudioOutput);
extern BYTE ScalerAudioGetInputChannelAllocation(EnumInputPort enumInputPort);
extern EnumAudioChannelCount ScalerAudioGetInputChannelCount(EnumInputPort enumInputPort);
extern StructAudioChannelInfo ScalerAudioGetInputChannelStatus(EnumInputPort enumInputPort);

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
extern void ScalerAudioSwitchI2sSpdifPath(bit bAudiopath, EnumInputPort enumInputPort);
#endif

#if(_DP_SUPPORT == _ON)
extern void ScalerAudioDpAudioEnable(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerAudioDpSetCapabilityState(EnumInputPort enumInputPort, EnumAudioDpDpcdSupport enumDpcdSupport);
extern EnumAudioDpDpcdSupport ScalerAudioDpGetCapabilityState(EnumInputPort enumInputPort);

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
extern bit ScalerAudioGetDpStandaloneAudioStatus(EnumInputPort enumInputPort);
#endif
#endif

#if(_HDMI_SUPPORT == _ON)
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
extern bit ScalerAudioHdmiHbrSettingProc(EnumAudioOutputType enumAudioOutput);
#endif

extern bit ScalerAudioLPCMCheckInfo(EnumAudioOutputType enumAudioOutput);

#if(_HW_HDMI_AUDIO_8CH_LAYOUT_NORMAL_OUTPUT == _OFF)
extern void ScalerAudioHdmiI2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput, EnumInputPort enumInputPort);
#endif
#endif

extern EnumSourceType ScalerAudioDigitalAudioSourceType(EnumAudioOutputType enumAudioOutput);

#if(_LINE_IN_SUPPORT == _ON)
extern void ScalerAudioADCInitial(void);
extern EnumAudioInputSource ScalerAudioGetInputSource(EnumAudioOutputType enumAudioOutput);
extern EnumAudioInputSource ScalerAudioGetInputSource_EXINT0(EnumAudioOutputType enumAudioOutput);
#endif

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
extern void ScalerAudioSpdifParallelModeSet(EnumAudioSpdifParallelMode enumAudioSpdifParallelMode);
extern void ScalerAudioSpdifParallelModeReset(void);
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
extern void ScalerAudioI2sParallelModeSet(EnumAudioI2sParallelMode enumAudioI2sParallelMode, EnumAudioI2sParallelType enumAudioI2sParallelType);
extern void ScalerAudioI2sParallelModeReset(void);
#endif

extern bit ScalerAudioParallelModePlaybackStableCheck(void);
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern void ScalerAudioDACInitial(void);
extern void ScalerAudioDACOutputSwitch(EnumAudioDACOutput enumDACOutput);
extern void ScalerAudioDACSetState(EnumAudioDACState enumTargetState);
extern bit ScalerAudioDACGetStateChange(void);
extern void ScalerAudioDACClrStateChange(void);
extern void ScalerAudioDACSetVcmReady(bit bReady);
extern void ScalerAudioDACNormalToDepop(void);
extern void ScalerAudioDACDepopToNormal(void);
extern void ScalerAudioDACOutputEnable(void);
extern EnumAudioDACOutput ScalerAudioDACGetOutput(void);
extern EnumAudioDACState ScalerAudioDACGetState(void);
#endif

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
extern void ScalerAudioSpdifChannelStatusProc(EnumAudioInputSource enumAudioSourceType, EnumInputPort enumInputPort);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern void ScalerAudioSetUserDefineAudioGenFrequency(EnumAudioSamplingFreqType enumAudioFreq);
extern void ScalerAudioInternalAudioGenSwitch(bit bOn, EnumInputPort enumInputPort, EnumAudioLeftRightChannelSelect enumAudioLeftRightChannelSelect);
extern bit ScalerAudioGetInternalAudioGenEnable(EnumInputPort enumInputPort);
extern void ScalerAudioInternalAudioGenPowerControl(bit bOn, EnumInputPort enumInputPort);

#if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)
extern void ScalerAudioSetInternalGenTestUserState(bit bOn);
#endif // End of #if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerAudioFwTrackingHandler(void);
#endif

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
extern void ScalerAudioSpreadPcodeEnable(EnumAudioInputPort enumAudioInputPort);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
extern void ScalerAudioSwitchArcSpdifPath(EnumAudioInputSource enumAudioSourceType, EnumInputPort enumInputPort);
extern void ScalerAudioInterfaceWatchDogProc(bit bOn, EnumAudioInputPort enumAudioInputPort, EnumAudioInputSource enumAudioSourceType);
extern void ScalerAudioInterfaceAudioReadyToPlay(bit bEnable, EnumInputPort enumInputPort);
extern EnumInputPort ScalerAudioGetArcDxPort(void);
extern void ScalerAudioTriggerArcPortHpdToggle(void);
extern EnumAudioCodingType ScalerAudioGetArcNonLPCMStatus(void);
extern void ScalerAudioGetArcInterfaceInfo(StructAudioInterfaceInfoForArc *pstInterfaceAudioInfo);
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

