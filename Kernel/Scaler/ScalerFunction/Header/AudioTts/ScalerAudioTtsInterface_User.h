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
// ID Code      : ScalerAudioTtsInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of Audio TTS Play Status
//--------------------------------------------------
typedef enum
{
    _TTS_NO_PROCESSING = 0x00,
    _TTS_PROCESSING,
    _TTS_PLAY_ERROR,
} EnumAudioTtsPlayStatus;

//--------------------------------------------------
// Enumerations of Audio TTS OSD Support
//--------------------------------------------------
typedef enum
{
    _AUDIO_TTS_OSD_SUPPORT_OFF = 0x00,
    _AUDIO_TTS_OSD_SUPPORT_ON,
} EnumAudioTtsOsdSupport;

//--------------------------------------------------
// Enumerations of Audio TTS Play Ready
//--------------------------------------------------
typedef enum
{
    _AUDIO_TTS_PLAY_NOT_READY = 0x00,
    _AUDIO_TTS_PLAY_READY,
} EnumAudioTtsPlayReady;

//--------------------------------------------------
// Structure of Audio TTS Segment
//--------------------------------------------------
typedef struct
{
    DWORD ulDataAddress;
    WORD usDataLength;
} StructAudioTtsSegment;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

