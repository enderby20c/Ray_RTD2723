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
// ID Code      : ScalerDpAudioRx4Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_AUDIO_RX4_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_AUDIO_RX4_ICODE_RELOADED()            (bit)(g_stDpAudioRx4DigtalInfo.b1AudioICodeReloaded)
#define SET_DP_AUDIO_RX4_ICODE_RELOADED()            (g_stDpAudioRx4DigtalInfo.b1AudioICodeReloaded = _TRUE)
#define CLR_DP_AUDIO_RX4_ICODE_RELOADED()            (g_stDpAudioRx4DigtalInfo.b1AudioICodeReloaded = _FALSE)

#define GET_DP_AUDIO_RX4_SAMPLING_FREQ()             (g_stDpAudioRx4DigtalInfo.b4AudioSamplingFreq)
#define SET_DP_AUDIO_RX4_SAMPLING_FREQ(x)            (g_stDpAudioRx4DigtalInfo.b4AudioSamplingFreq = (x))

#define GET_DP_AUDIO_RX4_PACKET_DETECT()             (bit)(g_stDpAudioRx4DigtalInfo.b1AudioDetected)
#define SET_DP_AUDIO_RX4_PACKET_DETECT()             (g_stDpAudioRx4DigtalInfo.b1AudioDetected = _TRUE)
#define CLR_DP_AUDIO_RX4_PACKET_DETECT()             (g_stDpAudioRx4DigtalInfo.b1AudioDetected = _FALSE)

#define GET_DP_AUDIO_RX4_DIGITAL_SOURCE()            (g_stDpAudioRx4DigtalInfo.b2AudioDigitalSource)
#define SET_DP_AUDIO_RX4_DIGITAL_SOURCE(x)           (g_stDpAudioRx4DigtalInfo.b2AudioDigitalSource = (x))

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_AUDIO_RX4_CHANNEL_COUNT()             ((ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_4)) == _CODING_TYPE_128B132B) ? ScalerGetBit(PE1_5F_SDP_AUD_STR_HB3, (_BIT2 | _BIT1 | _BIT0)) : ScalerGetBit(P35_CF_SDP_AUD_STR_HB3, (_BIT2 | _BIT1 | _BIT0)))
#define GET_DP_AUDIO_RX4_CODING_TYPE()               ((ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_4)) == _CODING_TYPE_128B132B) ? ScalerGetBit(PE1_5F_SDP_AUD_STR_HB3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) : ScalerGetBit(P35_CF_SDP_AUD_STR_HB3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#else
#define GET_DP_AUDIO_RX4_CHANNEL_COUNT()             (ScalerGetBit(P35_CF_SDP_AUD_STR_HB3, (_BIT2 | _BIT1 | _BIT0)))
#define GET_DP_AUDIO_RX4_CODING_TYPE()               (ScalerGetBit(P35_CF_SDP_AUD_STR_HB3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#endif

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
#define GET_DP_AUDIO_RX4_HBR_RECEIVE_IN_8_CH()       (bit)(g_stDpAudioRx4HbrReceiveType.b1HbrAudio8Ch)
#define SET_DP_AUDIO_RX4_HBR_RECEIVE_IN_8_CH()       (g_stDpAudioRx4HbrReceiveType.b1HbrAudio8Ch = _TRUE)
#define CLR_DP_AUDIO_RX4_HBR_RECEIVE_IN_8_CH()       (g_stDpAudioRx4HbrReceiveType.b1HbrAudio8Ch = _FALSE)

#define GET_DP_AUDIO_RX4_HBR_OPERATION_DONE()        (bit)(g_stDpAudioRx4HbrReceiveType.b1HbrAudioSysDetect)
#define SET_DP_AUDIO_RX4_HBR_OPERATION_DONE()        (g_stDpAudioRx4HbrReceiveType.b1HbrAudioSysDetect = _TRUE)
#define CLR_DP_AUDIO_RX4_HBR_OPERATION_DONE()        (g_stDpAudioRx4HbrReceiveType.b1HbrAudioSysDetect = _FALSE)

#define GET_DP_AUDIO_RX4_HBR_CHANNEL_STATUS_TOTAL()  (g_stDpAudioRx4HbrChannelInfo)

#define GET_DP_AUDIO_RX4_HBR_CHANNEL_STATUS_0()      (g_stDpAudioRx4HbrChannelInfo.ucChannelStaus0)
#define SET_DP_AUDIO_RX4_HBR_CHANNEL_STATUS_0(x)     (g_stDpAudioRx4HbrChannelInfo.ucChannelStaus0 = (x))

#define GET_DP_AUDIO_RX4_HBR_CHANNEL_STATUS_1()      (g_stDpAudioRx4HbrChannelInfo.ucChannelStaus1)
#define SET_DP_AUDIO_RX4_HBR_CHANNEL_STATUS_1(x)     (g_stDpAudioRx4HbrChannelInfo.ucChannelStaus1 = (x))

#define GET_DP_AUDIO_RX4_HBR_CHANNEL_STATUS_2()      (g_stDpAudioRx4HbrChannelInfo.ucChannelStaus2)
#define SET_DP_AUDIO_RX4_HBR_CHANNEL_STATUS_2(x)     (g_stDpAudioRx4HbrChannelInfo.ucChannelStaus2 = (x))

#define GET_DP_AUDIO_RX4_HBR_CHANNEL_STATUS_3()      (g_stDpAudioRx4HbrChannelInfo.ucChannelStaus3)
#define SET_DP_AUDIO_RX4_HBR_CHANNEL_STATUS_3(x)     (g_stDpAudioRx4HbrChannelInfo.ucChannelStaus3 = (x))

#define GET_DP_AUDIO_RX4_HBR_CHANNEL_STATUS_4()      (g_stDpAudioRx4HbrChannelInfo.ucChannelStaus4)
#define SET_DP_AUDIO_RX4_HBR_CHANNEL_STATUS_4(x)     (g_stDpAudioRx4HbrChannelInfo.ucChannelStaus4 = (x))

#define GET_DP_AUDIO_RX4_HBR_CHANNEL_NUMBER_12()     (g_stDpAudioRx4HbrChannelInfo.ucChannelNumber12)
#define SET_DP_AUDIO_RX4_HBR_CHANNEL_NUMBER_12(x)    (g_stDpAudioRx4HbrChannelInfo.ucChannelNumber12 = (x))

#define GET_DP_AUDIO_RX4_HBR_CHANNEL_NUMBER_34()     (g_stDpAudioRx4HbrChannelInfo.ucChannelNumber34)
#define SET_DP_AUDIO_RX4_HBR_CHANNEL_NUMBER_34(x)    (g_stDpAudioRx4HbrChannelInfo.ucChannelNumber34 = (x))

#define GET_DP_AUDIO_RX4_HBR_CHANNEL_NUMBER_56()     (g_stDpAudioRx4HbrChannelInfo.ucChannelNumber56)
#define SET_DP_AUDIO_RX4_HBR_CHANNEL_NUMBER_56(x)    (g_stDpAudioRx4HbrChannelInfo.ucChannelNumber56 = (x))

#define GET_DP_AUDIO_RX4_HBR_CHANNEL_NUMBER_78()     (g_stDpAudioRx4HbrChannelInfo.ucChannelNumber78)
#define SET_DP_AUDIO_RX4_HBR_CHANNEL_NUMBER_78(x)    (g_stDpAudioRx4HbrChannelInfo.ucChannelNumber78 = (x))
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructAudioDigitalInfo g_stDpAudioRx4DigtalInfo;

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
extern volatile StructAudioDpHbrReceiveType g_stDpAudioRx4HbrReceiveType;
extern volatile StructAudioChannelInfo g_stDpAudioRx4HbrChannelInfo;
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpAudioRx4AudioInitial(void);
extern void ScalerDpAudioRx4DigitalDetectProc(void);
extern void ScalerDpAudioRx4SetAudioOutputMute(bit bMute);
extern bit ScalerDpAudioRx4GetAudioDetected(void);
extern bit ScalerDpAudioRx4LPCMCheckData(void);
extern bit ScalerDpAudioRx4LPCMCheckChange(void);
extern void ScalerDpAudioRx4LPCMResetProc(void);
extern void ScalerDpAudioRx4LPCMFormatChangeProc_EXINT0(void);
extern void ScalerDpAudioRx4LoadStableICodeEvent(void);
extern EnumAudioSamplingFreqType ScalerDpAudioRx4SamplingFreqDetect(void);
extern bit ScalerDpAudioRx4SamplingFreqChange(void);
extern void ScalerDpAudioRx4AudioPLLPowerDown(void);
extern void ScalerDpAudioRx4WatchDogProc(bit bOn);
extern void ScalerDpAudioRx4AudioEnableControl(bit bEnable);
extern void ScalerDpAudioRx4AudioEnableControl_EXINT0(bit bEnable);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
extern void ScalerDpAudioRx4ResetSamplingFreqLimitProc(void);
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

extern void ScalerDpAudioRx4FifoTrackingProc_EXINT0(void);
extern void ScalerDpAudioRx4DisableSetting_EXINT0(void);
extern void ScalerDpAudioRx4HbrModeControl(bit bEnable);
extern BYTE ScalerDpAudioRx4GetAudioInfoFrame(EnumAudioInfoContent enumAudioInfoContent);

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
extern void ScalerDpAudioRx4UpdateHbrAudioChannelStatus(void);
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

extern StructAudioChannelInfo ScalerDpAudioRx4GetChannelStatus(void);

#if(_DP_TX_AUDIO_SUPPORT == _ON)
extern void ScalerDpAudioRx4RsDecoderControl(bit bEnable);
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerDpAudioRx4GetInternalAudioGenEnable(void);
extern void ScalerDpAudioRx4InternalAudioGenSwitch(bit bOn, EnumAudioLeftRightChannelSelect enumAudioLeftRightChannelSelect);
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#endif // End of #if(_DP_AUDIO_RX4_SUPPORT == _ON)

