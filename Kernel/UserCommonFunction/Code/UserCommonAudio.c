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
// ID Code      : UserCommonAudio.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_AUDIO__

#include "UserCommonInclude.h"
#include "Audio/UserCommonAudio.h"


#if(_AUDIO_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : User Common Ready to play audio
// Input Value  : None
// Output Value : _TRUE => Free to Play
//--------------------------------------------------
EnumAudioStatus UserCommonAudioGetPathReadyToPlayStatus(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            if(UserInterfaceAudioGetReadyToPlayStatus() == _AUDIO_READY_TRUE)
            {
                return _AUDIO_READY_TRUE;
            }
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            if(UserInterfaceAudioGetArcReadyToPlayStatus() == _AUDIO_READY_TRUE)
            {
                return _AUDIO_READY_TRUE;
            }
            break;
#endif
        default:
            break;
    }
    return _AUDIO_READY_FALSE;
}

//--------------------------------------------------
// Description  : UserCommonAudioGetAdjustVolumeThroughDVC
// Input Value  :
// Output Value : _TRUE(Through DVC Control) ; _FALSE(By-Pass DVC Control)
//--------------------------------------------------
bit UserCommonAudioGetAdjustVolumeThroughDVC(void)
{
#if(_EMBEDDED_DAC_SUPPORT == _ON)

    EnumAudioDACOutput enumAudioDACOutput = UserInterfaceAudioDACGetOutput();

    if(enumAudioDACOutput != _AUDIO_DAC_OUTPUT_NONE)
    {
        // Through DVC Control
        return _TRUE;
    }
#endif

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
    // Through DVC Control
    return _TRUE;
#endif

    // By-Pass DVC Control
    return _FALSE;
}

//--------------------------------------------------
// Description  : User Common Audio Mute Process
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void UserCommonAudioMuteCurrentDigitalPortProc(EnumInputPort enumInputPort)
{
    EnumInputPort enumAudioInputPort = SysRegionGetInputPort(UserInterfaceAudioGetDisplayModeRegion());

#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource(_AUDIO_DAC_OUT) == _DIGITAL_AUDIO)
#endif
    {
        if(enumAudioInputPort == enumInputPort)
        {
            // Reset Audio Output
            UserCommonAudioResetProc();
        }
    }
}

//--------------------------------------------------
// Description  : User Common Audio Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAudioResetProc(void)
{
    BYTE ucPathIndex = _PATH_0;

#if((_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    // Disable Port Reset when in Audio Pattern Gen Fix Port Mode
    if(ScalerAudioGetInternalAudioGenEnable(_NO_INPUT_PORT) == _ENABLE)
    {
        return;
    }
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
    if(UserInterfaceAudioGetStandAloneStatus() == _AUDIO_STAND_ALONE_TRUE)
    {
        ucPathIndex = SysAudioGetAudioPath(_AUDIO_DAC_OUT);

        // if Currently playing digital audio
        if((GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACK) && (UserInterfaceAudioGetSource() == _DIGITAL_AUDIO))
        {
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
            if(SysSourceGetAudioPlaybackPort() != SysRegionGetInputPort(UserInterfaceAudioGetDisplayModeRegion()))
#endif
            {
                DebugMessageAudio("UserCommon Audio Reset Process", 0x00);

#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
                SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);
#else
                SysAudioMuteProc(_ON);
#endif

                ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
                ScalerTimerDelayXms(3);
                ScalerAudioInputDigitalMute(_ON, GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));

                SysAudioChangeAllPathAudioState(_AUDIO_STATUS_RESET_TO_PREPARING);
            }
        }
    }
    else
#endif
    {
        for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
        {
            if(GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACK)
            {
                DebugMessageAudio("UserCommon Audio Reset Process", 0x00);

                if(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex) == _AUDIO_DAC_OUT)
                {
#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
                    SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);
#else
                    SysAudioMuteProc(_ON);
#endif
                }
                else
                {
                    SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    SysAudioParallelModeOutput(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);
#endif
                }

                ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
                ScalerTimerDelayXms(3);
                ScalerAudioInputDigitalMute(_ON, GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));

                SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_RESET_TO_PREPARING);
            }
        }
    }
}

//--------------------------------------------------
// Description  : User Common Audio Reset Region Process
// Input Value  : enumDisplayRegion --> audio reset target
// Output Value : None
//--------------------------------------------------
void UserCommonAudioResetRegionProc(EnumDisplayRegion enumDisplayRegion)
{
    EnumDisplayRegion enumUserDisplayRegion = UserInterfaceAudioGetDisplayModeRegion();
    BYTE ucPathIndex = _PATH_0;

#if((_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    // Disable Port Reset when in Audio Pattern Gen Fix Port Mode
    if(ScalerAudioGetInternalAudioGenEnable(_NO_INPUT_PORT) == _ENABLE)
    {
        return;
    }
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
    if(UserInterfaceAudioGetStandAloneStatus() == _AUDIO_STAND_ALONE_TRUE)
    {
        ucPathIndex = SysAudioGetAudioPath(_AUDIO_DAC_OUT);

        // if Currently playing digital audio
        if((enumDisplayRegion == enumUserDisplayRegion) &&
           (GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACK) &&
           (UserInterfaceAudioGetSource() == _DIGITAL_AUDIO))
        {
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
            if(SysSourceGetAudioPlaybackPort() != SysRegionGetInputPort(enumUserDisplayRegion))
#endif
            {
                DebugMessageAudio("UserCommon Audio Reset Region Process", 0x00);

#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
                SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);
#else
                SysAudioMuteProc(_ON);
#endif

                ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
                ScalerTimerDelayXms(3);
                ScalerAudioInputDigitalMute(_ON, GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));

                SysAudioChangeAllPathAudioState(_AUDIO_STATUS_RESET_TO_PREPARING);
            }
        }
    }
    else
#endif
    {
        for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
        {
            if((enumDisplayRegion == enumUserDisplayRegion) && (GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACK))
            {
                DebugMessageAudio("UserCommon Audio Path Reset Process", enumDisplayRegion);

                if(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex) == _AUDIO_DAC_OUT)
                {
#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
                    SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);
#else
                    SysAudioMuteProc(_ON);
#endif
                }
                else
                {
                    SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    SysAudioParallelModeOutput(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);
#endif
                }

                ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
                ScalerTimerDelayXms(3);
                ScalerAudioInputDigitalMute(_ON, GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));

                SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_RESET_TO_PREPARING);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit UserCommonAudioGetAudioDetected(EnumInputPort enumInputPort)
{
    return ScalerAudioGetAudioDetected(enumInputPort);
}

//--------------------------------------------------
// Description  : Adjust Digital volume
// Input Value  : ucVolume
// Output Value : None
//--------------------------------------------------
void UserCommonAudioDigitalAdjustVolume(WORD usVolume)
{
    ScalerAudioDigitalAdjustVolume(usVolume);
}

//--------------------------------------------------
// Description  : Get Current Audio Port
// Input Value  : None
// Output Value : Input Port
//--------------------------------------------------
EnumInputPort UserCommonAudioGetDigitalAudioPortMapping(void)
{
    return ScalerAudioGetDigitalAudioPortMapping(_AUDIO_DAC_OUT);
}

//--------------------------------------------------
// Description  : Get Detect Audio Sampling Freq
// Input Value  : enumInputPort
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqPacket UserCommonAudioSamplingFreqDetect(EnumInputPort enumInputPort)
{
    return ScalerAudioSamplingFreqDetect(enumInputPort);
}

//--------------------------------------------------
// Description  : Update User Define Audio Sampling Freq
// Input Value  : None
// Output Value : EnumAudioSamplingFreqType
//--------------------------------------------------
EnumAudioSamplingFreqType UserCommonAudioUpdateUserSamplingFreq(void)
{
    EnumAudioSamplingFreqType enumAudioFreq = UserInterfaceAudioGetUserSamplingFreq();

    if(enumAudioFreq == _AUDIO_FREQ_NO_AUDIO)
    {
        enumAudioFreq = _AUDIO_FREQ_48K;
    }

    return enumAudioFreq;
}

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Update User Define Audio Sampling Freq Limitation
// Input Value  : None
// Output Value : EnumAudioSamplingFreqType
//--------------------------------------------------
EnumAudioSamplingFreqType UserCommonAudioGetSamplingFreqLimit(void)
{
    EnumAudioSamplingFreqType enumAudioFreq = UserInterfaceAudioGetSamplingFreqLimit();

    if(enumAudioFreq == _AUDIO_FREQ_NO_AUDIO)
    {
        enumAudioFreq = _AUDIO_FREQ_48K;
    }

    return enumAudioFreq;
}
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get Current Digital Audio LPCM status
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
EnumAudioCodingType UserCommonAudioGetNonLPCMStatus(void)
{
    if(ScalerAudioLPCMCheckData(_AUDIO_DAC_OUT) == _TRUE)
    {
#if(_HDMI_SUPPORT == _ON)
        if(ScalerAudioDigitalAudioSourceType(_AUDIO_DAC_OUT) == _SOURCE_HDMI)
        {
            if(ScalerAudioLPCMCheckInfo(_AUDIO_DAC_OUT) == _TRUE)
            {
                return _AUDIO_LPCM;
            }
            else
            {
                return _AUDIO_NON_LPCM;
            }
        }
#endif
        return _AUDIO_LPCM;
    }
    return _AUDIO_NON_LPCM;
}

//--------------------------------------------------
// Description  : Get Current Mute status
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
EnumAudioMuteStatus UserCommonAudioGetPathOutputMuteStatus(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            return UserInterfaceAudioGetOutputMuteStatus();
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            return UserInterfaceAudioGetArcOutputMuteStatus();
            break;
#endif
        default:
            break;
    }
    return _AUDIO_MUTE_ON;
}

//--------------------------------------------------
// Description  : Get Current Mute status
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
EnumAudioCodingType UserCommonAudioGetPathNonLPCMStatus(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            return UserCommonAudioGetNonLPCMStatus();
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            return UserCommonAudioGetArcNonLPCMStatus();
            break;
#endif
        default:
            break;
    }
    return _AUDIO_NON_LPCM;
}

//--------------------------------------------------
// Description  : Get Current Digital Audio Source
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
BYTE UserCommonAudioGetDigitalAudioSource(EnumInputPort enumInputPort)
{
    return ScalerAudioGetDigitalAudioSource(enumInputPort);
}

#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get SPDIF Parallel Mode
// Input Value  : Node
// Output Value : Parallel Mode SPDIF Mode
//--------------------------------------------------
EnumAudioSpdifParallelMode UserCommonAudioSpdifParallelMode(void)
{
    return UserInterfaceAudioSpdifParallelMode();
}
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get I2S Parallel Mode
// Input Value  : Node
// Output Value : Parallel Mode I2S Mode
//--------------------------------------------------
EnumAudioI2sParallelMode UserCommonAudioI2sParallelMode(void)
{
    return UserInterfaceAudioI2sParallelMode();
}

//--------------------------------------------------
// Description  : Get I2S Parallel Type
// Input Value  : Node
// Output Value : Parallel Mode I2S Type
//--------------------------------------------------
EnumAudioI2sParallelType UserCommonAudioI2sParallelType(void)
{
    return UserInterfaceAudioI2sParallelType();
}
#endif

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Dp Audio Capability Initial State
// Input Value  : Input Port
// Output Value : EnumAudioDpDpcdSupport
//--------------------------------------------------
EnumAudioDpDpcdSupport UserCommonAudioDpGetCapabilityInitialState(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

#if(_DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT == _ON)
    return UserInterfaceAudioDpGetCapabilityInitialState(enumInputPort);
#else
    return _AUDIO_DP_DPCD_SUPPORT;
#endif // End of #if(_DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT == _ON)
}

#if(_DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Dp Audio Capability State
// Input Value  : Input Port
// Input Value  : EnumAudioDpDpcdSupport
// Output Value : None
//--------------------------------------------------
void UserCommonAudioDpSetCapabilityState(EnumInputPort enumInputPort, EnumAudioDpDpcdSupport enumDpcdSupport)
{
    ScalerAudioDpSetCapabilityState(enumInputPort, enumDpcdSupport);
}
#endif // End of #if(_DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_LINE_IN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current DAC Input Source
// Input Value  : None
// Output Value : _LINE_IN_AUDIO/ _DIGITAL_AUDIO
//--------------------------------------------------
EnumAudioInputSource UserCommonAudioGetInputSource(void)
{
    return ScalerAudioGetInputSource(_AUDIO_DAC_OUT);
}
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Curretn DAC State
// Input Value  : None
// Output Value : Current DAC State
//--------------------------------------------------
EnumAudioDACState UserCommonAudioDACGetState(void)
{
    return ScalerAudioDACGetState();
}
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get User Define Audio Gen Freq
// Input Value  : None
// Output Value : EnumAudioSamplingFreqType
//--------------------------------------------------
EnumAudioSamplingFreqType UserCommonAudioUpdateUserDefineAudioGenFreq(void)
{
    // Return Frequency
    switch(UserInterfaceAudioGetUserDefineAudioGenFreq())
    {
        case _AUDIO_GEN_FREQ_500HZ:

            return _AUDIO_FREQ_32K;

            break;

        case _AUDIO_GEN_FREQ_750HZ:

            return _AUDIO_FREQ_48K;

            break;

        case _AUDIO_GEN_FREQ_1000HZ:

            return _AUDIO_FREQ_64K;

            break;

        case _AUDIO_GEN_FREQ_1500HZ:

            return _AUDIO_FREQ_96K;

            break;

        case _AUDIO_GEN_FREQ_2000HZ:

            return _AUDIO_FREQ_128K;

            break;

        case _AUDIO_GEN_FREQ_3000HZ:

            return _AUDIO_FREQ_192K;

            break;

        default:
            break;
    }

    // Default to 1000Hz
    return _AUDIO_FREQ_64K;
}

//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit UserCommonAudioGetInternalAudioGenEnable(EnumInputPort enumInputPort)
{
    return ScalerAudioGetInternalAudioGenEnable(enumInputPort);
}

//--------------------------------------------------
// Description  : Get User Define Audio Gen Freq
// Input Value  : None
// Output Value : EnumAudioSamplingFreqType
//--------------------------------------------------
EnumAudioLeftRightChannelSelect UserCommonAudioGetUserLeftRightChanelSelect(void)
{
#if(_INTERNAL_AUDIO_CHANNEL_CONFIG_BY_USER_SUPPORT == _ON)
    return UserInterfaceAudioGetUserLeftRightChanelSelect();
#else
    return _AUDIO_LEFT_RIGHT_CHANNEL;
#endif
}
#endif

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
//--------------------------------------------------
// Description  : Set TTS Play Event
// Input Value  : *pstAudioTtsSegment
//                ucSegmentSize
//                ucTtsVolume --> 0 ~ 100
//                ucAudioVolume --> 0 ~ 100
// Output Value : None
//--------------------------------------------------
void UserCommonAudioTtsSetPlaybackActiveEvent(StructAudioTtsSegment *pstAudioTtsSegment, BYTE ucSegmentSize, BYTE ucTtsVolume, BYTE ucAudioVolume)
{
    EnumAudioState enumAudioState = _AUDIO_STATUS_PREPARING;

    // =================
    // Support Check
    // =================

    // Check TTS Support or not
    if(UserInterfaceAudioGetTtsSupport() == _AUDIO_TTS_OSD_SUPPORT_OFF)
    {
        DebugMessageAudio("[TTS] OSD set to Not Support!", 0x00);

        return;
    }

    DebugMessageAudio("[TTS] Playback Event pre-setting", 0x00);


    // =================
    // Reset Flow
    // =================

    // Disable Play_Done_INT
    ScalerAudioTtsPlayDoneDetect(_DISABLE);

    // Clear TTS Related Flag
    ScalerAudioTtsClearFlag();

    // Reset SPIC
    ScalerAudioTtsSpicReset();

    // Turn-off Upsampling
    ScalerAudioTtsUpsamplingControl(_DISABLE);

    // Cancel Previous WD Event
    ScalerAudioTtsSetTimerEvent(_DISABLE);


    // =================
    // Prepare Flow
    // =================

    // Check Previous Audio State for volume setting
    enumAudioState = SysAudioGetPathAudioState(_AUDIO_DAC_OUT);

    if(enumAudioState == _AUDIO_STATUS_PREPARING)
    {
        DebugMessageAudio("     -> Audio State From Preparing", 0x00);

        // Set TTS Volume to 100%
        ScalerAudioTtsDvcGainControl(UserAdjustAudioVolumeMapping(100), UserAdjustAudioVolumeMapping(0));

        // Set Main Volume to OSD Config
        UserAdjustAudioVolume(UserAdjustAudioGetOsdVolume());
    }
    else if(enumAudioState == _AUDIO_STATUS_PLAYBACK)
    {
        DebugMessageAudio("     -> Audio State From Playback", 0x00);

        // Set TTS Volume to User Config
        ScalerAudioTtsDvcGainControl(UserAdjustAudioVolumeMapping(ucTtsVolume), UserAdjustAudioVolumeMapping(ucAudioVolume));
    }
    else if(enumAudioState == _AUDIO_STATUS_TTS_PLAYBACK)
    {
        DebugMessageAudio("     -> Audio State From TTS_Playback", 0x00);

        // Reset Audio State for New TTS Playback Event
        SysAudioChangeAudioState(_AUDIO_DAC_OUT, _AUDIO_STATUS_PREPARING);
    }

    // Record TTS Segment data
    ScalerAudioTtsGetCommandData(pstAudioTtsSegment, ucSegmentSize);


    // =================
    // Active Event
    // =================

    // Set TTS Event Active for SysAudioHandler trigger
    ScalerAudioTtsSetPlaybackEvent(_ENABLE);
}

//--------------------------------------------------
// Description  : Get TTS Play Status
// Input Value  : None
// Output Value : _NO_PROCESSING / _PROCESSING / _PLAY_ERROR
//--------------------------------------------------
EnumAudioTtsPlayStatus UserCommonAudioTtsGetPlaybackStatus(void)
{
    return _TTS_NO_PROCESSING;
}

//--------------------------------------------------
// Description  : Get TTS Error Segment Play Fail
// Input Value  : None
// Output Value : ucErrorSegment
//--------------------------------------------------
BYTE UserCommonAudioTtsGetErrorSegment(void)
{
    BYTE ucErrorSegment = 0x00;

    return ucErrorSegment;
}
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Common Get Current Digital Audio LPCM status
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
EnumAudioCodingType UserCommonAudioGetArcNonLPCMStatus(void)
{
    return ScalerAudioGetArcNonLPCMStatus();
}

//--------------------------------------------------
// Description  : User Common Get ARC Tx Audio Source
// Input Value  : None
// Output Value : _DIGITAL_AUDIO or _LINE_IN_AUDIO
//--------------------------------------------------
EnumAudioInputSource UserCommonAudioGetArcSource(void)
{
    return UserInterfaceAudioGetArcSource();
}

//--------------------------------------------------
// Description  : User Common Get Arc Audio Inputport
// Input Value  : None
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort UserCommonAudioGetArcInputport(void)
{
    return UserInterfaceAudioGetArcInputport();
}

//--------------------------------------------------
// Description  : User Common Get Arc Mode
// Input Value  : None
// Output Value : EnumAudioArcMode
//--------------------------------------------------
EnumAudioArcMode UserCommonAudioGetArcMode(void)
{
    return UserInterfaceAudioGetArcMode();
}

//--------------------------------------------------
// Description  : User Common Get Arc Mute Status
// Input Value  : None
// Output Value : EnumAudioMuteStatus
//--------------------------------------------------
EnumAudioMuteStatus UserCommonAudioGetArcMuteStatus(void)
{
    return UserInterfaceAudioGetArcMuteStatus();
}

//--------------------------------------------------
// Description  : User Common Get Arc Channel
// Input Value  : None
// Output Value : EnumArcAudioChanelStatus
//--------------------------------------------------
EnumArcAudioChanelStatus UserCommonAudioGetArcChannel(void)
{
    return UserInterfaceAudioGetArcChannel();
}
#endif // #if(_AUDIO_ARC_SUPPORT == _ON
#endif // #if(_AUDIO_SUPPORT == _ON)

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Audio Channel Allocation
// Input Value  : EnumInputPort
// Output Value : ucAudioInfoSdpDataCA
//--------------------------------------------------
BYTE UserCommonAudioGetInputChannelAllocation(EnumInputPort enumInputPort)
{
    return ScalerAudioGetInputChannelAllocation(enumInputPort);
}

//--------------------------------------------------
// Description  : Get Audio Channel Count
// Input Value  : EnumInputPort
// Output Value : EnumAudioChannelCount
//--------------------------------------------------
EnumAudioChannelCount UserCommonAudioGetInputChannelCount(EnumInputPort enumInputPort)
{
    return ScalerAudioGetInputChannelCount(enumInputPort);
}

//--------------------------------------------------
// Description  : Get Audio Channel Status
// Input Value  : enumInputPort
// Output Value : StructAudioChannelInfo
//--------------------------------------------------
StructAudioChannelInfo UserCommonAudioGetInputChannelStatus(EnumInputPort enumInputPort)
{
    return ScalerAudioGetInputChannelStatus(enumInputPort);
}
#endif
