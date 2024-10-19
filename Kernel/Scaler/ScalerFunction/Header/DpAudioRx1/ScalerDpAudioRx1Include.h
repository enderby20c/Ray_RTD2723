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
// ID Code      : ScalerDpAudioRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_AUDIO_RX1_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_AUDIO_RX1_ICODE_RELOADED()            (bit)(g_stDpAudioRx1DigtalInfo.b1AudioICodeReloaded)
#define SET_DP_AUDIO_RX1_ICODE_RELOADED()            (g_stDpAudioRx1DigtalInfo.b1AudioICodeReloaded = _TRUE)
#define CLR_DP_AUDIO_RX1_ICODE_RELOADED()            (g_stDpAudioRx1DigtalInfo.b1AudioICodeReloaded = _FALSE)

#define GET_DP_AUDIO_RX1_SAMPLING_FREQ()             (g_stDpAudioRx1DigtalInfo.b4AudioSamplingFreq)
#define SET_DP_AUDIO_RX1_SAMPLING_FREQ(x)            (g_stDpAudioRx1DigtalInfo.b4AudioSamplingFreq = (x))

#define GET_DP_AUDIO_RX1_PACKET_DETECT()             (bit)(g_stDpAudioRx1DigtalInfo.b1AudioDetected)
#define SET_DP_AUDIO_RX1_PACKET_DETECT()             (g_stDpAudioRx1DigtalInfo.b1AudioDetected = _TRUE)
#define CLR_DP_AUDIO_RX1_PACKET_DETECT()             (g_stDpAudioRx1DigtalInfo.b1AudioDetected = _FALSE)

#define GET_DP_AUDIO_RX1_DIGITAL_SOURCE()            (g_stDpAudioRx1DigtalInfo.b2AudioDigitalSource)
#define SET_DP_AUDIO_RX1_DIGITAL_SOURCE(x)           (g_stDpAudioRx1DigtalInfo.b2AudioDigitalSource = (x))

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_AUDIO_RX1_CHANNEL_COUNT()             ((ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B) ? ScalerGetBit(P75_5F_SDP_AUD_STR_HB3, (_BIT2 | _BIT1 | _BIT0)) : ScalerGetBit(PB9_CF_SDP_AUD_STR_HB3, (_BIT2 | _BIT1 | _BIT0)))
#define GET_DP_AUDIO_RX1_CODING_TYPE()               ((ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_1)) == _CODING_TYPE_128B132B) ? ScalerGetBit(P75_5F_SDP_AUD_STR_HB3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) : ScalerGetBit(PB9_CF_SDP_AUD_STR_HB3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#else
#define GET_DP_AUDIO_RX1_CHANNEL_COUNT()             (ScalerGetBit(PB9_CF_SDP_AUD_STR_HB3, (_BIT2 | _BIT1 | _BIT0)))
#define GET_DP_AUDIO_RX1_CODING_TYPE()               (ScalerGetBit(PB9_CF_SDP_AUD_STR_HB3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#endif

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
#define GET_DP_AUDIO_RX1_HBR_RECEIVE_IN_8_CH()       (bit)(g_stDpAudioRx1HbrReceiveType.b1HbrAudio8Ch)
#define SET_DP_AUDIO_RX1_HBR_RECEIVE_IN_8_CH()       (g_stDpAudioRx1HbrReceiveType.b1HbrAudio8Ch = _TRUE)
#define CLR_DP_AUDIO_RX1_HBR_RECEIVE_IN_8_CH()       (g_stDpAudioRx1HbrReceiveType.b1HbrAudio8Ch = _FALSE)

#define GET_DP_AUDIO_RX1_HBR_OPERATION_DONE()        (bit)(g_stDpAudioRx1HbrReceiveType.b1HbrAudioSysDetect)
#define SET_DP_AUDIO_RX1_HBR_OPERATION_DONE()        (g_stDpAudioRx1HbrReceiveType.b1HbrAudioSysDetect = _TRUE)
#define CLR_DP_AUDIO_RX1_HBR_OPERATION_DONE()        (g_stDpAudioRx1HbrReceiveType.b1HbrAudioSysDetect = _FALSE)

#define GET_DP_AUDIO_RX1_HBR_CHANNEL_STATUS_TOTAL()  (g_stDpAudioRx1HbrChannelInfo)

#define GET_DP_AUDIO_RX1_HBR_CHANNEL_STATUS_0()      (g_stDpAudioRx1HbrChannelInfo.ucChannelStaus0)
#define SET_DP_AUDIO_RX1_HBR_CHANNEL_STATUS_0(x)     (g_stDpAudioRx1HbrChannelInfo.ucChannelStaus0 = (x))

#define GET_DP_AUDIO_RX1_HBR_CHANNEL_STATUS_1()      (g_stDpAudioRx1HbrChannelInfo.ucChannelStaus1)
#define SET_DP_AUDIO_RX1_HBR_CHANNEL_STATUS_1(x)     (g_stDpAudioRx1HbrChannelInfo.ucChannelStaus1 = (x))

#define GET_DP_AUDIO_RX1_HBR_CHANNEL_STATUS_2()      (g_stDpAudioRx1HbrChannelInfo.ucChannelStaus2)
#define SET_DP_AUDIO_RX1_HBR_CHANNEL_STATUS_2(x)     (g_stDpAudioRx1HbrChannelInfo.ucChannelStaus2 = (x))

#define GET_DP_AUDIO_RX1_HBR_CHANNEL_STATUS_3()      (g_stDpAudioRx1HbrChannelInfo.ucChannelStaus3)
#define SET_DP_AUDIO_RX1_HBR_CHANNEL_STATUS_3(x)     (g_stDpAudioRx1HbrChannelInfo.ucChannelStaus3 = (x))

#define GET_DP_AUDIO_RX1_HBR_CHANNEL_STATUS_4()      (g_stDpAudioRx1HbrChannelInfo.ucChannelStaus4)
#define SET_DP_AUDIO_RX1_HBR_CHANNEL_STATUS_4(x)     (g_stDpAudioRx1HbrChannelInfo.ucChannelStaus4 = (x))

#define GET_DP_AUDIO_RX1_HBR_CHANNEL_NUMBER_12()     (g_stDpAudioRx1HbrChannelInfo.ucChannelNumber12)
#define SET_DP_AUDIO_RX1_HBR_CHANNEL_NUMBER_12(x)    (g_stDpAudioRx1HbrChannelInfo.ucChannelNumber12 = (x))

#define GET_DP_AUDIO_RX1_HBR_CHANNEL_NUMBER_34()     (g_stDpAudioRx1HbrChannelInfo.ucChannelNumber34)
#define SET_DP_AUDIO_RX1_HBR_CHANNEL_NUMBER_34(x)    (g_stDpAudioRx1HbrChannelInfo.ucChannelNumber34 = (x))

#define GET_DP_AUDIO_RX1_HBR_CHANNEL_NUMBER_56()     (g_stDpAudioRx1HbrChannelInfo.ucChannelNumber56)
#define SET_DP_AUDIO_RX1_HBR_CHANNEL_NUMBER_56(x)    (g_stDpAudioRx1HbrChannelInfo.ucChannelNumber56 = (x))

#define GET_DP_AUDIO_RX1_HBR_CHANNEL_NUMBER_78()     (g_stDpAudioRx1HbrChannelInfo.ucChannelNumber78)
#define SET_DP_AUDIO_RX1_HBR_CHANNEL_NUMBER_78(x)    (g_stDpAudioRx1HbrChannelInfo.ucChannelNumber78 = (x))
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructAudioDigitalInfo g_stDpAudioRx1DigtalInfo;

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
extern volatile StructAudioDpHbrReceiveType g_stDpAudioRx1HbrReceiveType;
extern volatile StructAudioChannelInfo g_stDpAudioRx1HbrChannelInfo;
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpAudioRx1AudioInitial(void);
extern void ScalerDpAudioRx1DigitalDetectProc(void);
extern void ScalerDpAudioRx1SetAudioOutputMute(bit bMute);
extern bit ScalerDpAudioRx1GetAudioDetected(void);
extern bit ScalerDpAudioRx1LPCMCheckData(void);
extern bit ScalerDpAudioRx1LPCMCheckChange(void);
extern void ScalerDpAudioRx1LPCMResetProc(void);
extern void ScalerDpAudioRx1LPCMFormatChangeProc_EXINT0(void);
extern void ScalerDpAudioRx1LoadStableICodeEvent(void);
extern EnumAudioSamplingFreqType ScalerDpAudioRx1SamplingFreqDetect(void);
extern bit ScalerDpAudioRx1SamplingFreqChange(void);
extern void ScalerDpAudioRx1AudioPLLPowerDown(void);
extern void ScalerDpAudioRx1WatchDogProc(bit bOn);
extern void ScalerDpAudioRx1AudioEnableControl(bit bEnable);
extern void ScalerDpAudioRx1AudioEnableControl_EXINT0(bit bEnable);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
extern void ScalerDpAudioRx1ResetSamplingFreqLimitProc(void);
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

extern void ScalerDpAudioRx1FifoTrackingProc_EXINT0(void);
extern void ScalerDpAudioRx1DisableSetting_EXINT0(void);
extern void ScalerDpAudioRx1HbrModeControl(bit bEnable);
extern BYTE ScalerDpAudioRx1GetAudioInfoFrame(EnumAudioInfoContent enumAudioInfoContent);

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
extern void ScalerDpAudioRx1UpdateHbrAudioChannelStatus(void);
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

extern StructAudioChannelInfo ScalerDpAudioRx1GetChannelStatus(void);

#if(_DP_TX_AUDIO_SUPPORT == _ON)
extern void ScalerDpAudioRx1RsDecoderControl(bit bEnable);
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerDpAudioRx1GetInternalAudioGenEnable(void);
extern void ScalerDpAudioRx1InternalAudioGenSwitch(bit bOn, EnumAudioLeftRightChannelSelect enumAudioLeftRightChannelSelect);
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)

