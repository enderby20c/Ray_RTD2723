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
// ID Code      : ScalerAudioTtsInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_TTS_PLAYBACK_ERROR()                    (bit)(g_stAudioTtsInfo.b1TtsPlaybackError)
#define SET_TTS_PLAYBACK_ERROR()                    (g_stAudioTtsInfo.b1TtsPlaybackError = _TRUE)
#define CLR_TTS_PLAYBACK_ERROR()                    (g_stAudioTtsInfo.b1TtsPlaybackError = _FALSE)

#define GET_TTS_PLAYBACK_EVENT_ACTIVE()             (bit)(g_stAudioTtsInfo.b1TtsPlayEventActive)
#define SET_TTS_PLAYBACK_EVENT_ACTIVE()             (g_stAudioTtsInfo.b1TtsPlayEventActive = _TRUE)
#define CLR_TTS_PLAYBACK_EVENT_ACTIVE()             (g_stAudioTtsInfo.b1TtsPlayEventActive = _FALSE)

#define GET_TTS_PLAY_DONE_FLAG()                    (bit)(g_stAudioTtsInfo.b1TtsPlayDoneFlag)
#define SET_TTS_PLAY_DONE_FLAG()                    (g_stAudioTtsInfo.b1TtsPlayDoneFlag = _TRUE)
#define CLR_TTS_PLAY_DONE_FLAG()                    (g_stAudioTtsInfo.b1TtsPlayDoneFlag = _FALSE)

#define GET_TTS_DATA_SEGMENT_TARGET()               (BYTE)(g_stAudioTtsInfo.ucTtsSegmentTarget)
#define SET_TTS_DATA_SEGMENT_TARGET(x)              (g_stAudioTtsInfo.ucTtsSegmentTarget = (x))

#define GET_TTS_DATA_SEGMENT_CURRENT()              (BYTE)(g_stAudioTtsInfo.ucTtsSegmentCurrent)
#define INC_TTS_DATA_SEGMENT_CURRENT()              (g_stAudioTtsInfo.ucTtsSegmentCurrent++)
#define CLR_TTS_DATA_SEGMENT_CURRENT()              (g_stAudioTtsInfo.ucTtsSegmentCurrent = 0)

#define GET_TTS_DATA_SEGMENT_ADDRESS(x)             (DWORD)(g_stAudioTtsInfo.pulTtsSegmentAddress[(x)])
#define SET_TTS_DATA_SEGMENT_ADDRESS(x, y)          (g_stAudioTtsInfo.pulTtsSegmentAddress[(x)] = (y))

#define GET_TTS_DATA_SEGMENT_LENGTH(x)              (WORD)(g_stAudioTtsInfo.pusTtsSegmentLength[(x)])
#define SET_TTS_DATA_SEGMENT_LENGTH(x, y)           (g_stAudioTtsInfo.pusTtsSegmentLength[(x)] = (y))

#define GET_TTS_SAMPLING_FREQ_USER_DEFINE()         (BYTE)(g_stAudioTtsInfo.enumTtsUserDefineFreq)
#define SET_TTS_SAMPLING_FREQ_USER_DEFINE(x)        (g_stAudioTtsInfo.enumTtsUserDefineFreq = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Structure of TTS Variable
//--------------------------------------------------
typedef struct
{
    BYTE b1TtsPlaybackError : 1;
    BYTE b1TtsPlayEventActive : 1;
    BYTE b1TtsPlayDoneFlag : 1;
    BYTE ucTtsSegmentTarget;
    BYTE ucTtsSegmentCurrent;
    EnumAudioSamplingFreqType enumTtsUserDefineFreq;
    DWORD pulTtsSegmentAddress[_AUDIO_TTS_DATA_SEGMENT_SIZE];
    WORD pusTtsSegmentLength[_AUDIO_TTS_DATA_SEGMENT_SIZE];
} StructAudioTtsInfo;

//--------------------------------------------------
// enum of TTS Blcok
//--------------------------------------------------
typedef enum
{
    _AUDIO_TTS_BLOCK_0,
    _AUDIO_TTS_BLOCK_1,
} EnumAudioTtsBlock;

//--------------------------------------------------
// enum of TTS data width
//--------------------------------------------------
typedef enum
{
    _AUDIO_TTS_DATA_8BIT,
    _AUDIO_TTS_DATA_16BIT,
} EnumAudioTtsDataWidth;

//--------------------------------------------------
// enum of TTS SPIC status
//--------------------------------------------------
typedef enum
{
    _AUDIO_TTS_SPIC_IDLE,
    _AUDIO_TTS_SPIC_BUSY,
} EnumAudioSpicStatus;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructAudioTtsInfo g_stAudioTtsInfo;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerAudioTtsInitial(void);
extern void ScalerAudioTtsDataPlay_WDINT(void);
extern void ScalerAudioTtsSetVolume(WORD usRegTtsVolume, WORD usRegAudioVolume);

#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

