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
// ID Code      : ScalerAudioInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))
//--------------------------------------------------
// Definitions of Audio Frequency Paramater
//--------------------------------------------------
#define _DP_INITIAL_I_CODE                          0x00000010UL
#define _DP_STABLE_I_CODE                           0x00000010UL

#define _HDMI_INITIAL_I_CODE                        0x00000038UL
#define _HDMI_STABLE_I_CODE                         0x00000038UL

#define _AUDIO_DYNAMIC_I_CODE_TIMER_MS              100 // Unit: ms

#define _AUTO_FREQ_DETECT_XTAL_DIV                  (BYTE)(((((WORD) _SYS_CLK_KHZ << 1) / 160) + 1) >> 1)

#define _DVC_DB_STEP_NUMBER                         64

#define _AUDIO_PLL_VCO                              393216 // 1KHz
#define _AUDIO_PLL_N                                0x0C
#define _AUDIO_PLL_F                                0x9045

//--------------------------------------------------
// Macro of Audio Control Paramater
//--------------------------------------------------
#if(_LINE_IN_SUPPORT == _ON)
#define GET_LINE_IN_AUDIO_CHANNEL_ALLOCATION()      (0x00)
#define GET_LINE_IN_AUDIO_CHANNEL_COUNT()           (_AUDIO_CHANNEL_COUNT_2)
#define GET_LINE_IN_AUDIO_CODING_TYPE()             (0x01)
#endif

//--------------------------------------------------
// Macro of Audio Internal Gen
//--------------------------------------------------
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
#define GET_AUDIO_GEN_FREQ_MAPPING()                (g_stAudioGenFreq.enumAudioFreq)
#define SET_AUDIO_GEN_FREQ_MAPPING(x)               (g_stAudioGenFreq.enumAudioFreq = (x))

#define GET_AUDIO_GEN_FREQ_S_CODE()                 (g_stAudioGenFreq.ucSCode)
#define SET_AUDIO_GEN_FREQ_S_CODE(x)                (g_stAudioGenFreq.ucSCode = (x))

#define GET_AUDIO_GEN_FREQ_N_CODE()                 (g_stAudioGenFreq.ucNCode)
#define SET_AUDIO_GEN_FREQ_N_CODE(x)                (g_stAudioGenFreq.ucNCode = (x))

#define GET_AUDIO_GEN_FREQ_F_CODE()                 (g_stAudioGenFreq.usFCode)
#define SET_AUDIO_GEN_FREQ_F_CODE(x)                (g_stAudioGenFreq.usFCode = (x))
#endif

#endif // End of #if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of Audio DVC Paramater
//--------------------------------------------------
#define _DVC_VOLUME_ADJUST_TIMER                    20 // ms

#define _DVC_ZCD_TIMEOUT_DEFAULT                    (0x0030 & 0x0FFF) // 48KHz, Fcut = 500Hz

//--------------------------------------------------
// Definitions of Audio Control Paramater
//--------------------------------------------------
#define _AUDIO_INPUT_FROM_TMDS                      0
#define _AUDIO_INPUT_FROM_FRL                       1

#define _ADC_AUDIO_PLL_N                            0x19
#define _ADC_AUDIO_PLL_F                            0x768AA

#define _ZCD_TIMEOUT_DEFAULT                        0x1F

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
#define _AUDIO_FW_TRCK_FIRST_STABLE_CNT             0x20
#define _AUDIO_WL_GOES_UP                           2
#define _AUDIO_WL_GOES_DOWN                         1
#define _AUDIO_WL_GOES_UNKNOWN                      0
#define _AUDIO_FW_TRCK_PREPARING_CHECK              30
#define _AUDIO_FW_TRCK_PLAYBACK_CHECK               20
#endif

#if((_HDMI_SUPPORT == _ON) && (_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON))
#define _AUDIO_HDMI_STABLE_FCODE_RANGE              0x1E
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
#define GET_AUDIO_DAC_STATE()                       (g_stAudioDACInfo.b3AudioDACState)
#define SET_AUDIO_DAC_STATE(x)                      (g_stAudioDACInfo.b3AudioDACState = (x))

#define GET_AUDIO_DAC_STATE_CHANGE()                (bit)(g_stAudioDACInfo.b1AudioDACStateChange)
#define SET_AUDIO_DAC_STATE_CHANGE()                (g_stAudioDACInfo.b1AudioDACStateChange = _TRUE)
#define CLR_AUDIO_DAC_STATE_CHANGE()                (g_stAudioDACInfo.b1AudioDACStateChange = _FALSE)

#define GET_DAC_AOUT_GAIN_DB()                      (g_stAudioDACInfo.enumDACAIOGainDb)
#define SET_DAC_AOUT_GAIN_DB(x)                     (g_stAudioDACInfo.enumDACAIOGainDb = (x))
#define GET_DAC_HPOUT_GAIN_DB()                     (g_stAudioDACInfo.enumDACHPOGainDb)
#define SET_DAC_HPOUT_GAIN_DB(x)                    (g_stAudioDACInfo.enumDACHPOGainDb = (x))
#endif

#if(_DUAL_DP_SUPPORT == _ON)
#define GET_AUDIO_DUAL_DP_STATUS()                  (g_bAudioDpDualStatus)
#define SET_AUDIO_DUAL_DP_STATUS()                  (g_bAudioDpDualStatus = _TRUE)
#define CLR_AUDIO_DUAL_DP_STATUS()                  (g_bAudioDpDualStatus = _FALSE)
#endif

#define GET_AUDIO_DVC_MUTE_CTRL_STATUS()            (g_bAudioDVCMuteCtrlStatus)
#define SET_AUDIO_DVC_MUTE_CTRL_STATUS(x)           (g_bAudioDVCMuteCtrlStatus = (x))

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
#define SET_IIS_PARALLEL_MODE_NORMAL()              ScalerSetByte(P6F_FA_IIS_GEN_CTRL_0, 0xC0) // set bit7 = 1
#define SET_IIS_PARALLEL_MODE_RESET()               ScalerSetBit(P6F_FA_IIS_GEN_CTRL_0, ~_BIT7, 0x00)

#if(_SCPU_SUPPORT == _ON)
#define GET_AUDIO_SCPU_AUDIO_STATE()                Scaler32GetByte(PA30000_08_GLOBAL_CTRL_DUMMY1, 0x01)
#define SET_AUDIO_SCPU_AUDIO_STATE(x)               Scaler32SetByte(PA30000_08_GLOBAL_CTRL_DUMMY1, 0x01, (x))
#endif

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
#define GET_HDMI_RX3_HBR_AUDIO_IS_SETTING()         (bit)(g_stAudioHbrSetting.b1HdmiRx3HbrAudioSetting)
#define SET_HDMI_RX3_HBR_AUDIO_IS_SETTING()         (g_stAudioHbrSetting.b1HdmiRx3HbrAudioSetting = _TRUE)
#define CLR_HDMI_RX3_HBR_AUDIO_IS_SETTING()         (g_stAudioHbrSetting.b1HdmiRx3HbrAudioSetting = _FALSE)

#define GET_HDMI_RX3_HBR_AUDIO_FIFO_ERROR()         (bit)(g_stAudioHbrSetting.b1HdmiRx3HbrFifoError)
#define SET_HDMI_RX3_HBR_AUDIO_FIFO_ERROR()         (g_stAudioHbrSetting.b1HdmiRx3HbrFifoError = _TRUE)
#define CLR_HDMI_RX3_HBR_AUDIO_FIFO_ERROR()         (g_stAudioHbrSetting.b1HdmiRx3HbrFifoError = _FALSE)
#endif

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
#define GET_HDMI_RX4_HBR_AUDIO_IS_SETTING()         (bit)(g_stAudioHbrSetting.b1HdmiRx4HbrAudioSetting)
#define SET_HDMI_RX4_HBR_AUDIO_IS_SETTING()         (g_stAudioHbrSetting.b1HdmiRx4HbrAudioSetting = _TRUE)
#define CLR_HDMI_RX4_HBR_AUDIO_IS_SETTING()         (g_stAudioHbrSetting.b1HdmiRx4HbrAudioSetting = _FALSE)

#define GET_HDMI_RX4_HBR_AUDIO_FIFO_ERROR()         (bit)(g_stAudioHbrSetting.b1HdmiRx4HbrFifoError)
#define SET_HDMI_RX4_HBR_AUDIO_FIFO_ERROR()         (g_stAudioHbrSetting.b1HdmiRx4HbrFifoError = _TRUE)
#define CLR_HDMI_RX4_HBR_AUDIO_FIFO_ERROR()         (g_stAudioHbrSetting.b1HdmiRx4HbrFifoError = _FALSE)
#endif
#endif

//--------------------------------------------------
// Macros of Switch Audio DAC Use Power Control
//--------------------------------------------------
#define _EXTERNAL_PCB_V33S                          0
#define _TEST_MODE_INTERNAL_LDO_V33S                1
#define _AUDIO_DAC_USE_POWER_TYPE                   _EXTERNAL_PCB_V33S
#endif // End of #if(_AUDIO_SUPPORT == _ON)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))
//--------------------------------------------------
// Enum for Audio Tracking Mode
//--------------------------------------------------
typedef enum
{
    _AUDIO_TRACKING_AUTO_LOAD_MODE = 0,
    _AUDIO_TRACKING_MANNUAL_MODE = 1,

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    _AUDIO_TRACKING_MANNUAL_MODE_FIX_TARGET_FREQ = 2,
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
} EnumAudioFreqTrackingMode;

//--------------------------------------------------
// Structure for Audio
//--------------------------------------------------
typedef struct
{
    EnumAudioSamplingFreqType b4AudioSamplingFreq : 4;
    BYTE b1AudioDetected : 1;
    BYTE b1AudioSampleFreqChange : 1;
    BYTE b1AudioICodeReloaded : 1;
    BYTE b1AudioFromHdmiVer : 1;
    EnumAudioDigitalSource b2AudioDigitalSource : 2;
} StructAudioDigitalInfo;

#if(_DP_SUPPORT == _ON)
typedef struct
{
    EnumAudioCodingType enumAudioCodingType;
    BYTE b1AudioCodingTypeChange : 1;
} StructAudioDpCodingType;

typedef struct
{
    BYTE b1HbrAudioModeChange : 1;
} StructAudioDpHbrReceiveMode;

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
typedef struct
{
    BYTE b1FsmBackup : 1;
    BYTE b1FifoTrackingBackup : 1;
} StructAudioDpInternalGen;
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
typedef struct
{
    BYTE b1HbrAudio8Ch : 1;
    BYTE b1HbrAudioSysDetect : 1;
} StructAudioDpHbrReceiveType;
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)

typedef struct
{
    EnumAudioSamplingFreqType enumFsManual;
    EnumAudioSamplingFreqType enumFsTarget;
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    EnumAudioSamplingFreqType enumFsLimit;
    EnumAudioSamplingFreqType enumFsSource;
    BYTE b1FreqLimitControl : 1;
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    BYTE b1AutoLoad : 1;
    BYTE b1AutoLoadForFrl : 1;
    BYTE b1SamplingFreqChange : 1;
} StructAudioFreqParameter;

#endif // End of #if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))

#if(_AUDIO_SUPPORT == _ON)

#if(_EMBEDDED_DAC_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of Audio DAC Output Gain
//--------------------------------------------------
typedef enum
{
#if(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_0)
    _AUDIO_DAC_OUTPUT_GAIN_0_DB = 0x00,
    _AUDIO_DAC_OUTPUT_GAIN_0_2_5_DB = 0x01,
    _AUDIO_DAC_OUTPUT_GAIN_0_5_DB = 0x02,
    _AUDIO_DAC_OUTPUT_GAIN_0_7_5_DB = 0x03,
    _AUDIO_DAC_OUTPUT_GAIN_1_0_DB = 0x04,
    _AUDIO_DAC_OUTPUT_GAIN_1_5_DB = 0x05,
    _AUDIO_DAC_OUTPUT_GAIN_2_DB = 0x06,
    _AUDIO_DAC_OUTPUT_GAIN_2_5_DB = 0x07,
#elif(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_1)
#if(_AUDIO_DAC_USE_POWER_TYPE == _EXTERNAL_PCB_V33S)
    _AUDIO_DAC_OUTPUT_GAIN_0_DB = 0xFF,
    _AUDIO_DAC_OUTPUT_GAIN_0_5_DB = 0x00,
    _AUDIO_DAC_OUTPUT_GAIN_1_0_DB = 0x01,
    _AUDIO_DAC_OUTPUT_GAIN_1_4_DB = 0x02,
    _AUDIO_DAC_OUTPUT_GAIN_1_9_DB = 0x03,
    _AUDIO_DAC_OUTPUT_GAIN_2_5_DB = 0x04,
    _AUDIO_DAC_OUTPUT_GAIN_3_0_DB = 0x05,
#elif(_AUDIO_DAC_USE_POWER_TYPE == _TEST_MODE_INTERNAL_LDO_V33S)
    _AUDIO_DAC_OUTPUT_GAIN_0_DB = 0x02,
    _AUDIO_DAC_OUTPUT_GAIN_0_5_DB = 0x03,
    _AUDIO_DAC_OUTPUT_GAIN_1_0_DB = 0x04,
    _AUDIO_DAC_OUTPUT_GAIN_1_4_DB = 0x05,
#endif
#elif(_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_2)
    _AUDIO_DAC_OUTPUT_GAIN_0_DB = 0x03, // 0dB
    _AUDIO_DAC_OUTPUT_GAIN_0_4_DB = 0x04, // 0.4dB
    _AUDIO_DAC_OUTPUT_GAIN_0_8_DB = 0x05, // 0.8dB
    _AUDIO_DAC_OUTPUT_GAIN_1_2_DB = 0x06, // 1.2dB
    _AUDIO_DAC_OUTPUT_GAIN_1_6_DB = 0x07, // 1.6dB
#endif
} EnumAudioDacOutputGain;

typedef struct
{
    EnumAudioDACState b3AudioDACState : 3;
    BYTE b1AudioDACStateChange : 1;
    EnumAudioDacOutputGain enumDACAIOGainDb;
    EnumAudioDacOutputGain enumDACHPOGainDb;
}StructAudioDACInfo;
#endif

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
typedef struct
{
    BYTE b2AudioFwTrackState : 2;
    BYTE b1AudioFwTrackEventStatus : 1;
    BYTE b1AudioFwTrackReset : 1;
    BYTE b1AudioFwTrackTimeoutEvent : 1;
    BYTE b2AudioWaterLevelTargetDirection : 2;
    BYTE b1AudioFwTrackStable : 1;
    BYTE ucAfifoBackup;
    BYTE ucAfifoTrackStableCnt;
    BYTE ucAudioFreqRecord;
} StructAudioFwTrackingInfo;

typedef enum
{
    _AUDIO_FW_TRACKING_INITIAL,
    _AUDIO_FW_TRACKING_PROCESS_PREPARING,
    _AUDIO_FW_TRACKING_PROCESS_PLAYBACK,
} EnumAudioFwTrackingState;
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
typedef struct
{
    EnumAudioSamplingFreqType enumAudioFreq;
    BYTE ucSCode;
    BYTE ucNCode;
    WORD usFCode;
} StructAudioGenFreqParameter;
#endif

//--------------------------------------------------
// Enumerations of SPD Info
//--------------------------------------------------
typedef enum
{
    _ADUIO_INFO_PB1 = 0,
    _ADUIO_INFO_PB2,
    _ADUIO_INFO_PB3,
    _ADUIO_INFO_PB4,
    _ADUIO_INFO_PB5,
    _ADUIO_INFO_PB6,
    _ADUIO_INFO_PB7,
    _ADUIO_INFO_PB8,
    _ADUIO_INFO_PB9,
    _ADUIO_INFO_PB10,
} EnumAudioInfoContent;
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
typedef struct
{
#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
    BYTE b1HdmiRx3HbrAudioSetting : 1;
    BYTE b1HdmiRx3HbrFifoError : 1;
#endif

#if(_HDMI_AUDIO_RX4_SUPPORT == _ON)
    BYTE b1HdmiRx4HbrAudioSetting : 1;
    BYTE b1HdmiRx4HbrFifoError : 1;
#endif
} StructAudioHbrSetting;
#endif

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE) && (_SCPU_SUPPORT == _ON))
typedef enum
{
    _PARALLELMODE_HBR_IDLE_STATE = 0x00,
    _PARALLELMODE_HBR_FIRST_STATE_FOR_RX3_FRL = 0x01,
    _PARALLELMODE_HBR_FIRST_STATE_FOR_RX3_TMDS = 0x11,
    _PARALLELMODE_HBR_FIRST_STATE_FOR_RX4_FRL = 0x21,
    _PARALLELMODE_HBR_FIRST_STATE_FOR_RX4_TMDS = 0x31,
    _PARALLELMODE_HBR_SECOND_STATE = 0x02,
    _PARALLELMODE_HBR_THIRD_STATE = 0x03,
    _PARALLELMODE_HBR_FOURTH_STATE = 0x04,
} EnumAudioParallelModeHbrState;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_AUDIO_SUPPORT == _ON)
#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern StructAudioDACInfo g_stAudioDACInfo;
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern StructAudioGenFreqParameter g_stAudioGenFreq;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
extern bit g_bAudioDpDualStatus;
#endif

#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
extern StructAudioHbrSetting g_stAudioHbrSetting;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_AUDIO_SUPPORT == _ON)
extern void ScalerAudioClockGatting(bit bEnable);
#endif

#if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))
extern void ScalerAudioLoadStableICodeEvent(EnumScalerTimerEventID enumEventID);
extern DWORD ScalerAudioGetUserSamplingFreqNFCode(EnumPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
extern BYTE ScalerAudioGetUserSamplingFreqSCode(EnumPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
extern DWORD ScalerAudioGetUserSamplingFreqNFCode_EXINT0(EnumPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
extern BYTE ScalerAudioGetUserSamplingFreqSCode_EXINT0(EnumPortType enumPortType, EnumAudioSamplingFreqType enumAudioFreq);
extern BYTE ScalerAudioGetRxCodingType(EnumAudioOutputType enumAudioOutput);
extern StructAudioChannelInfo ScalerAudioGetRxChannelStatus(EnumAudioOutputType enumAudioOutput);

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#if(_HW_DP_AUDIO_CHANNEL_STATUS_1S1D2S_RECEIVE_SUPPORT == _OFF)
extern void ScalerAudioSetChannelStatusFrequency(EnumAudioSamplingFreqType enumAudioFreq, StructAudioChannelInfo *pstAudioStatus);
extern void ScalerAudioSetChannelStatusNumber(EnumAudioChannelCount enumChannelCount, StructAudioChannelInfo *pstAudioStatus);
#endif // End of #if(_HW_DP_AUDIO_CHANNEL_STATUS_1S1D2S_RECEIVE_SUPPORT == _OFF)
#endif // End of #if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif // End of #if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))

#if(_AUDIO_SUPPORT == _ON)
extern BYTE ScalerAudioChannelOutputSel(BYTE ucCa);

extern void ScalerAudioDVCResetProc(void);
extern void ScalerAudioDVCResetProcCheck(EnumAudioInputPort enumAudioInput);

#if(_DP_SUPPORT == _ON)
extern void ScalerAudioDpAudioEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerAudioRxDisableSetting_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerAudioDpGetCapabilityChange(EnumInputPort enumInputPort);
#endif


#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern void ScalerAudioDACNormalToDepopCheck(EnumAudioInputPort enumAudioInput);
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

