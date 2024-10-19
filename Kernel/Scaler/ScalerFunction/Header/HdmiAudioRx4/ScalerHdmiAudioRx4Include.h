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
// ID Code      : ScalerHdmiAudioRx4Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_HDMI_AUDIO_RX4_ICODE_RELOADED()          (bit)(g_stHdmiAudioRx4DigtalInfo.b1AudioICodeReloaded)
#define SET_HDMI_AUDIO_RX4_ICODE_RELOADED()          (g_stHdmiAudioRx4DigtalInfo.b1AudioICodeReloaded = _TRUE)
#define CLR_HDMI_AUDIO_RX4_ICODE_RELOADED()          (g_stHdmiAudioRx4DigtalInfo.b1AudioICodeReloaded = _FALSE)

#define GET_HDMI_AUDIO_RX4_SAMPLING_FREQ()           (g_stHdmiAudioRx4DigtalInfo.b4AudioSamplingFreq)
#define SET_HDMI_AUDIO_RX4_SAMPLING_FREQ(x)          (g_stHdmiAudioRx4DigtalInfo.b4AudioSamplingFreq = (x))

#define GET_HDMI_AUDIO_RX4_SAMPLING_FREQ_CHANGE()    (bit)(g_stHdmiAudioRx4DigtalInfo.b1AudioSampleFreqChange)
#define SET_HDMI_AUDIO_RX4_SAMPLING_FREQ_CHANGE()    (g_stHdmiAudioRx4DigtalInfo.b1AudioSampleFreqChange = _TRUE)
#define CLR_HDMI_AUDIO_RX4_SAMPLING_FREQ_CHANGE()    (g_stHdmiAudioRx4DigtalInfo.b1AudioSampleFreqChange = _FALSE)

#define GET_HDMI_AUDIO_RX4_PACKET_DETECT()           (bit)(g_stHdmiAudioRx4DigtalInfo.b1AudioDetected)
#define SET_HDMI_AUDIO_RX4_PACKET_DETECT()           (g_stHdmiAudioRx4DigtalInfo.b1AudioDetected = _TRUE)
#define CLR_HDMI_AUDIO_RX4_PACKET_DETECT()           (g_stHdmiAudioRx4DigtalInfo.b1AudioDetected = _FALSE)

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
#define GET_HDMI_AUDIO_RX4_VERSION()                 (bit)(g_stHdmiAudioRx4DigtalInfo.b1AudioFromHdmiVer)
#define SET_HDMI_AUDIO_RX4_VERSION(x)                (g_stHdmiAudioRx4DigtalInfo.b1AudioFromHdmiVer = (x))
#endif

#define GET_HDMI_AUDIO_RX4_DIGITAL_SOURCE()          (g_stHdmiAudioRx4DigtalInfo.b2AudioDigitalSource)
#define SET_HDMI_AUDIO_RX4_DIGITAL_SOURCE(x)         (g_stHdmiAudioRx4DigtalInfo.b2AudioDigitalSource = (x))

#define GET_HDMI_AUDIO_RX4_CHANNEL_COUNT()           ((ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6) ? (ScalerGetDataPortSingleByte(P78_CD_HDMI_PSAP, 0x15) & (_BIT2 | _BIT1 | _BIT0)) : (ScalerGetDataPortSingleByte(P73_CD_HDMI_PSAP, 0x15) & (_BIT2 | _BIT1 | _BIT0)))
#define GET_HDMI_AUDIO_RX4_CODING_TYPE()             ((ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6) ? ((ScalerGetDataPortSingleByte(P78_CD_HDMI_PSAP, 0x15) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4) : ((ScalerGetDataPortSingleByte(P73_CD_HDMI_PSAP, 0x15) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4))
#define GET_HDMI_AUDIO_RX4_CHANNEL_ALLOCATION()      ((ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == _BIT6) ? (ScalerGetDataPortSingleByte(P78_CD_HDMI_PSAP, 0x18)) : (ScalerGetDataPortSingleByte(P73_CD_HDMI_PSAP, 0x18)))

#define GET_HDMI_AUDIO_RX4_AUTO_LOAD_FREQ()          (g_stHdmiAudioRx4FreqParameter.b1AutoLoad)
#define SET_HDMI_AUDIO_RX4_AUTO_LOAD_FREQ()          (g_stHdmiAudioRx4FreqParameter.b1AutoLoad = _TRUE)
#define CLR_HDMI_AUDIO_RX4_AUTO_LOAD_FREQ()          (g_stHdmiAudioRx4FreqParameter.b1AutoLoad = _FALSE)

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
#define GET_HDMI_AUDIO_RX4_AUTO_LOAD_FREQ_FOR_FRL()  (g_stHdmiAudioRx4FreqParameter.b1AutoLoadForFrl)
#define SET_HDMI_AUDIO_RX4_AUTO_LOAD_FREQ_FOR_FRL()  (g_stHdmiAudioRx4FreqParameter.b1AutoLoadForFrl = _TRUE)
#define CLR_HDMI_AUDIO_RX4_AUTO_LOAD_FREQ_FOR_FRL()  (g_stHdmiAudioRx4FreqParameter.b1AutoLoadForFrl = _FALSE)
#endif

#define GET_HDMI_RX4_TARGET_SAMPLING_FREQ()          (g_stHdmiAudioRx4FreqParameter.enumFsTarget)
#define SET_HDMI_RX4_TARGET_SAMPLING_FREQ(x)         (g_stHdmiAudioRx4FreqParameter.enumFsTarget = (x))

#define GET_HDMI_RX4_SAMPLING_FREQ_USER_DEFINE()     (g_stHdmiAudioRx4FreqParameter.enumFsManual)
#define SET_HDMI_RX4_SAMPLING_FREQ_USER_DEFINE(x)    (g_stHdmiAudioRx4FreqParameter.enumFsManual = (x))

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
#define GET_HDMI_RX4_SAMPLING_FREQ_LIMIT()           (g_stHdmiAudioRx4FreqParameter.enumFsLimit)
#define SET_HDMI_RX4_SAMPLING_FREQ_LIMIT(x)          (g_stHdmiAudioRx4FreqParameter.enumFsLimit = (x))
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
#define GET_HDMI_AUDIO_RX4_FW_TRACKING_STATE()       (g_stHdmiAudioRx4FwTrackingInfo.b2AudioFwTrackState)
#define SET_HDMI_AUDIO_RX4_FW_TRACKING_STATE(x)      (g_stHdmiAudioRx4FwTrackingInfo.b2AudioFwTrackState = (x))

#define GET_HDMI_AUDIO_RX4_FW_TRACKING_EVENT()       (bit)(g_stHdmiAudioRx4FwTrackingInfo.b1AudioFwTrackEventStatus)
#define SET_HDMI_AUDIO_RX4_FW_TRACKING_EVENT()       (g_stHdmiAudioRx4FwTrackingInfo.b1AudioFwTrackEventStatus = _TRUE)
#define CLR_HDMI_AUDIO_RX4_FW_TRACKING_EVENT()       (g_stHdmiAudioRx4FwTrackingInfo.b1AudioFwTrackEventStatus = _FALSE)

#define GET_HDMI_AUDIO_RX4_FW_TRACKING_TIMEOUT()     (bit)(g_stHdmiAudioRx4FwTrackingInfo.b1AudioFwTrackTimeoutEvent)
#define SET_HDMI_AUDIO_RX4_FW_TRACKING_TIMEOUT()     (g_stHdmiAudioRx4FwTrackingInfo.b1AudioFwTrackTimeoutEvent = _TRUE)
#define CLR_HDMI_AUDIO_RX4_FW_TRACKING_TIMEOUT()     (g_stHdmiAudioRx4FwTrackingInfo.b1AudioFwTrackTimeoutEvent = _FALSE)

#define GET_HDMI_AUDIO_RX4_FW_TRACKING_RESET()       (bit)(g_stHdmiAudioRx4FwTrackingInfo.b1AudioFwTrackReset)
#define SET_HDMI_AUDIO_RX4_FW_TRACKING_RESET()       (g_stHdmiAudioRx4FwTrackingInfo.b1AudioFwTrackReset = _TRUE)
#define CLR_HDMI_AUDIO_RX4_FW_TRACKING_RESET()       (g_stHdmiAudioRx4FwTrackingInfo.b1AudioFwTrackReset = _FALSE)

#define GET_HDMI_AUDIO_RX4_WL_TARGET_DIRECTION()     (g_stHdmiAudioRx4FwTrackingInfo.b2AudioWaterLevelTargetDirection)
#define SET_HDMI_AUDIO_RX4_WL_TARGET_DIRECTION(x)    (g_stHdmiAudioRx4FwTrackingInfo.b2AudioWaterLevelTargetDirection = (x))
#define CLR_HDMI_AUDIO_RX4_WL_TARGET_DIRECTION()     (g_stHdmiAudioRx4FwTrackingInfo.b2AudioWaterLevelTargetDirection = _AUDIO_WL_GOES_UNKNOWN)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructAudioDigitalInfo g_stHdmiAudioRx4DigtalInfo;
extern StructAudioFreqParameter g_stHdmiAudioRx4FreqParameter;

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern StructAudioFwTrackingInfo g_stHdmiAudioRx4FwTrackingInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerHdmiAudioRx4DigitalDetectProc(void);
extern bit ScalerHdmiAudioRx4GetAudioDetected(void);
extern void ScalerHdmiAudioRx4Initial(void);
extern void ScalerHdmiAudioRx4LoadStableICodeEvent(void);
extern EnumAudioSamplingFreqType ScalerHdmiAudioRx4SamplingFreqDetect(void);
extern void ScalerHdmiAudioRx4SetAudioPLLOnProc(void);
extern void ScalerHdmiAudioRx4WatchDogProc(bit bOn);
extern bit ScalerHdmiAudioRx4SamplingFreqChange(void);

#if(_HW_HDMI_AUDIO_8CH_LAYOUT_NORMAL_OUTPUT == _OFF)
extern void ScalerHdmiAudioRx4I2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput);
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
extern bit ScalerHdmiAudioRx4CheckVersionChange(void);
extern bit ScalerHdmiAudioRx4SetVersion(void);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerHdmiAudioRx4GetInternalAudioGenEnable(void);
extern void ScalerHdmiAudioRx4InternalAudioGenSwitch(bit bOn, EnumAudioLeftRightChannelSelect enumAudioLeftRightChannelSelect);
#endif

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
extern bit ScalerHdmiAudioRx4CheckNfCodeStable(void);
#endif

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
extern void ScalerHdmiAudioRx4FwTrackingHandler(void);
extern void ScalerHdmiAudioRx4FwTrackingInitial(void);
extern void ScalerHdmiAudioRx4FwTrackingReset(void);
extern void ScalerHdmiAudioRx4FwPreparingTracking(void);
extern void ScalerHdmiAudioRx4FwBoundaryTracking(void);
extern void ScalerHdmiAudioRx4FwTrackingEventSet(void);
extern void ScalerHdmiAudioRx4TimeoutEventSet(void);
extern BYTE ScalerHdmiAudioRx4FwTrackingTimerEventPeriod(void);
#endif

extern StructAudioChannelInfo ScalerHdmiAudioRx4GetChannelStatus(void);

#if(_AUDIO_ARC_SUPPORT == _ON)
extern BYTE ScalerHdmiAudioRx4GetAudioInfo(EnumAudioInfoContent enumAudioInfoContent);
#endif

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
extern bit ScalerHdmiAudioRx4HbrAudioSettingForFrl(void);
extern void ScalerHdmiAudioRx4HbrAudioResetForFrl(void);
#endif
extern void ScalerHdmiAudioRx4ClkStableCheckTime(void);
extern bit ScalerHdmiAudioRx4HbrAudioSettingForTmds(void);
extern void ScalerHdmiAudioRx4HbrAudioResetForTmds(void);
#endif
#endif // End of #if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
