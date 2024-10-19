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
// ID Code      : ScalerAudioInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_AUDIO_EARC_SUPPORT == _ON)
#define _CDS_AUDIO_DESCRIPTOR_LENGTH                31
#define _CDS_SPEAKER_ADB_LENGTH                     4
#define _CDS_SPEAKER_LDB_LENGTH                     172
#define _CDS_RCDB_LENGTH                            12
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Audio Channel Count
//--------------------------------------------------
typedef enum
{
    _AUDIO_CHANNEL_COUNT_MONO = 0x00,
    _AUDIO_CHANNEL_COUNT_2,
    _AUDIO_CHANNEL_COUNT_3,
    _AUDIO_CHANNEL_COUNT_4,
    _AUDIO_CHANNEL_COUNT_5,
    _AUDIO_CHANNEL_COUNT_6,
    _AUDIO_CHANNEL_COUNT_7,
    _AUDIO_CHANNEL_COUNT_8,
} EnumAudioChannelCount;

#if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))
//--------------------------------------------------
// Enumerations of Audio Ready To Play Status
//--------------------------------------------------
typedef enum
{
    _AUDIO_READY_FALSE = _FALSE,
    _AUDIO_READY_TRUE = _TRUE,
} EnumAudioStatus;

//--------------------------------------------------
// Enumerations of Audio input Source
//--------------------------------------------------
typedef enum
{
    _LINE_IN_AUDIO,
    _DIGITAL_AUDIO,
    _NO_AUDIO_SOURCE = 0xFF,
} EnumAudioInputSource;

//--------------------------------------------------
// Enumerations of Non-LPCM Audio Status
//--------------------------------------------------
typedef enum
{
    _AUDIO_LPCM,
    _AUDIO_NON_LPCM,
} EnumAudioCodingType;

//--------------------------------------------------
// Enumerations of Non-LPCM Audio Status
//--------------------------------------------------
typedef enum
{
    _AUDIO_MUTE_OFF = _OFF,
    _AUDIO_MUTE_ON = _ON,
} EnumAudioMuteStatus;

//--------------------------------------------------
// Enumerations of Audio DAC Output
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OUTPUT_NONE,
    _AUDIO_DAC_OUTPUT_SPEAKER,
    _AUDIO_DAC_OUTPUT_HEADPHONE,
    _AUDIO_DAC_OUTPUT_BOTH,
} EnumAudioDACOutput;

//--------------------------------------------------
// Enumerations of Audio DAC Keep Depop State
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_KEEP_DEPOP_FALSE = _FALSE,
    _AUDIO_DAC_KEEP_DEPOP_TRUE = _TRUE,
} EnumAudioDacDepopState;

//--------------------------------------------------
// Enumerations of Audio Stand Alone Status
//--------------------------------------------------
typedef enum
{
    _AUDIO_STAND_ALONE_FALSE = _FALSE,
    _AUDIO_STAND_ALONE_TRUE = _TRUE,
} EnumAudioStandAloneStatus;

//--------------------------------------------------
// Enumerations of Audio DAC State
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OFF,
    _AUDIO_DAC_INITIAL,
    _AUDIO_DAC_CHARGE,
    _AUDIO_DAC_DEPOP,
    _AUDIO_DAC_READY,
} EnumAudioDACState;

//--------------------------------------------------
// Enumerations of Digital Audio Source
//--------------------------------------------------
typedef enum
{
    _DIGITAL_AUDIO_SOURCE_NONE,
    _DIGITAL_AUDIO_SOURCE_HDMI,
    _DIGITAL_AUDIO_SOURCE_DP,
} EnumAudioDigitalSource;

//--------------------------------------------------
// Enumerations of Audio Sampling Freq Packet Number
//--------------------------------------------------
typedef enum
{
    _AUDIO_FREQ_PACKET_NO_AUDIO = 0,
    _AUDIO_FREQ_PACKET_32K = 32,
    _AUDIO_FREQ_PACKET_44_1K = 44,
    _AUDIO_FREQ_PACKET_48K = 48,
    _AUDIO_FREQ_PACKET_64K = 64,
    _AUDIO_FREQ_PACKET_88_2K = 88,
    _AUDIO_FREQ_PACKET_96K = 96,
    _AUDIO_FREQ_PACKET_128K = 128,
    _AUDIO_FREQ_PACKET_176_4K = 176,
    _AUDIO_FREQ_PACKET_192K = 192,
    _AUDIO_FREQ_PACKET_256K = 256,
    _AUDIO_FREQ_PACKET_352_8K = 352,
    _AUDIO_FREQ_PACKET_384K = 384,
    _AUDIO_FREQ_PACKET_512K = 512,
    _AUDIO_FREQ_PACKET_705_6K = 705,
    _AUDIO_FREQ_PACKET_768K = 768,
} EnumAudioSamplingFreqPacket;

//--------------------------------------------------
// Enumerations of Audio Sampling Freq Type
//--------------------------------------------------
typedef enum
{
    _AUDIO_FREQ_NO_AUDIO = 0x00,
    _AUDIO_FREQ_32K,
    _AUDIO_FREQ_44_1K,
    _AUDIO_FREQ_48K,
    _AUDIO_FREQ_64K,
    _AUDIO_FREQ_88_2K,
    _AUDIO_FREQ_96K,
    _AUDIO_FREQ_128K,
    _AUDIO_FREQ_176_4K,
    _AUDIO_FREQ_192K,
    _AUDIO_FREQ_256K,
    _AUDIO_FREQ_352_8K,
    _AUDIO_FREQ_384K,
    _AUDIO_FREQ_512K,
    _AUDIO_FREQ_705_6K,
    _AUDIO_FREQ_768K,
} EnumAudioSamplingFreqType;

//--------------------------------------------------
// Enumerations of Audio Output Port
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OUT = 0x00,
    _AUDIO_I2S_OUT,
    _AUDIO_SPDIF_OUT,
    _AUDIO_DPTX_OUT,
#if(_AUDIO_ARC_SUPPORT == _ON)
    _AUDIO_ARC_OUT,
#endif
} EnumAudioOutputType;

//--------------------------------------------------
// Enumerations of Audio Sampling Freq Type
//--------------------------------------------------
typedef enum
{
    _AUDIO_GEN_FREQ_NO_AUDIO = 0x00,
    _AUDIO_GEN_FREQ_500HZ,
    _AUDIO_GEN_FREQ_750HZ,
    _AUDIO_GEN_FREQ_1000HZ,
    _AUDIO_GEN_FREQ_1500HZ,
    _AUDIO_GEN_FREQ_2000HZ,
    _AUDIO_GEN_FREQ_3000HZ,
} EnumAudioInternalGenFreq;

//--------------------------------------------------
// Enumerations of Audio Sampling Freq Type
//--------------------------------------------------
typedef enum
{
    _AUDIO_LEFT_CHANNEL = 0x00,
    _AUDIO_RIGHT_CHANNEL,
    _AUDIO_LEFT_RIGHT_CHANNEL,
} EnumAudioLeftRightChannelSelect;

#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of Audio SPDIF Parallel Mode
//--------------------------------------------------
typedef enum
{
    _SPDIF_1_TO_2 = 0x00,
    _SPDIF_1_TO_4,
    _NO_SPDIF_PARALLEL_MODE,
} EnumAudioSpdifParallelMode;
#endif // End of #if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of Audio I2S Parallel Mode
//--------------------------------------------------
typedef enum
{
    _I2S_1_TO_4 = 0x00,
    _I2S_1_TO_2,
    _NO_I2S_PARALLEL_MODE,
} EnumAudioI2sParallelMode;

//--------------------------------------------------
// Enumerations of Audio I2S Parallel Type
//--------------------------------------------------
typedef enum
{
    _I2S_PHILIP32_24BIT = 0x00,
    _I2S_PHILIP32_16BIT,
    _I2S_PHILIP16_16BIT,
    _I2S_LEFT32_24BIT,
    _I2S_LEFT32_16BIT,
    _I2S_RIGHT32_24BIT,
    _I2S_RIGHT32_16BIT,
} EnumAudioI2sParallelType;
#endif // End of #if(_I2S_PARALLEL_MODE_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of Audio DP DPCD Support
//--------------------------------------------------
typedef enum
{
    _AUDIO_DP_DPCD_NOT_SUPPORT = 0x00,
    _AUDIO_DP_DPCD_SUPPORT,
} EnumAudioDpDpcdSupport;
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of Audio ARC MODE
//--------------------------------------------------
typedef enum
{
    _EARC_ARC_OFF = 0x00,
    _EARC_MODE,
    _ARC_MODE,
} EnumAudioArcMode;

//--------------------------------------------------
// Enumerations of Audio Mute Status
//--------------------------------------------------
typedef enum
{
    _ARC_AUDIO_2CH = 0,
    _ARC_AUDIO_8CH,
}EnumArcAudioChanelStatus;

//--------------------------------------------------
// Enumerations of Audio Output Port
//--------------------------------------------------
typedef enum
{
    _ARC_AUDIO_DAC_OUT = 0x00,
    _ARC_AUDIO_ARC_OUT,
} EnumArcAudioOutputType;

//--------------------------------------------------
// Enumerations of HDMI ARC Tx Audio Layout Type
//--------------------------------------------------
typedef enum
{
    _AUDIO_LAYOUT_UNKNOWN = 0x00,
    _AUDIO_LAYOUT_2CH,
    _AUDIO_LAYOUT_8CH,
    _AUDIO_LAYOUT_6CH_ONE_BIT_AUDIO,
} EnumArcAudioLayoutType;

//--------------------------------------------------
// Enumerations of Audio Interface Info
//--------------------------------------------------
typedef struct
{
    BYTE ucAudioChStatusByte0;
    BYTE ucAudioChStatusByte1;
    BYTE ucAudioChStatusByte2;
    BYTE ucAudioChStatusByte3;
    BYTE ucAudioChStatusByte4;
    BYTE ucAudioInfoPb4;
    BYTE ucAudioInfoPb5;
    BYTE ucAudioInfoPb6;
    BYTE ucAudioInfoPb7;
    BYTE ucAudioInfoPb8;
    BYTE ucAudioInfoPb9;
    BYTE ucAudioInfoPb10;
    EnumAudioCodingType enumAudioCodingType;
    EnumAudioChannelCount enumAudioChannelCount;
    EnumAudioSamplingFreqPacket enumAudioFs;
} StructAudioInterfaceInfoForArc;

//--------------------------------------------------
// Enumerations of ARC Tx OSD Info
//--------------------------------------------------
typedef struct
{
    EnumAudioInputSource enumArcInputSource;
    EnumInputPort enumArcInputPort;
    EnumAudioArcMode enumArcMode;
    EnumAudioMuteStatus enumArcMuteStatus;
    EnumArcAudioChanelStatus enumArcAudioChanelStatus;
} StructArcTxOsdInfo;

#if(_AUDIO_EARC_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of ARC Tx CDS Info
//--------------------------------------------------
typedef struct
{
    BYTE ucEarcCdsAdbOffset;
    BYTE ucEarcCdsSpkAdbOffset;
    BYTE ucEarcCdsSpkLdbOffset;
    BYTE ucEarcCdsRcdbOffset;
    BYTE pucEarcCdsAdb[_CDS_AUDIO_DESCRIPTOR_LENGTH];
    BYTE pucEarcCdsSpkAdb[_CDS_SPEAKER_ADB_LENGTH];
    // BYTE g_pucEarcCdsSpkLdb[_CDS_SPEAKER_LDB_LENGTH];
    // BYTE g_pucEarcCdsRcdb[_CDS_RCDB_LENGTH];
} StructArcTxEarcCdsInfo;
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)

//--------------------------------------------------
// Enumerations Dp Audio Channel Info
//--------------------------------------------------
typedef struct
{
    BYTE ucChannelStaus0;
    BYTE ucChannelStaus1;
    BYTE ucChannelStaus2;
    BYTE ucChannelStaus3;
    BYTE ucChannelStaus4;
    BYTE ucChannelNumber12;
    BYTE ucChannelNumber34;
    BYTE ucChannelNumber56;
    BYTE ucChannelNumber78;
} StructAudioChannelInfo;
#endif // End of #if((_AUDIO_SUPPORT == _ON) || (_DP_RX_MST2SST_AUDIO_SUPPORT == _ON) || (_HDMI_ARC_TX_MAC_SUPPORT == _ON))

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

