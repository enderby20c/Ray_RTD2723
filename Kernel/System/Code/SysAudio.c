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
// ID Code      : SysAudio.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_AUDIO__

#include "SysInclude.h"
#include "Audio/SysAudio.h"

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructAudioInfoType g_stAudioInfo;

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
StructAudioParalleInfo g_stAudioParallelInfo;
#endif

StructAudioInfo g_pstAudioPathInfo[_AUDIO_PATH_VALID];

#if(_AUDIO_ARC_SUPPORT == _ON)
StructArcTxOsdInfo g_stAudioArcTxOsdInfo;
StructArcTxModeInfoType g_stAudioArcTxModeInfo;
StructAudioInterfaceInfoForArc g_stAudioArcTxAudioSourceInfo;

#if(_AUDIO_EARC_SUPPORT == _ON)
StructArcTxEarcCdsInfo g_stAudioEarcRxCdsInfo;
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Audio handler. Main audio control flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioHandler(void)
{
    SysAudioJudgeHandler();
    SysAudioModeHandler();
}

//--------------------------------------------------
// Description  : Audio Judge Handler. check & Input/Output Handler & State Change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioJudgeHandler(void)
{
    EnumAudioStatus enumAudioReadyStatus = _AUDIO_READY_FALSE;
    BYTE ucPathIndex = _PATH_0;

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
    EnumDisplayRegion enumDisplayRegion = UserInterfaceAudioGetDisplayModeRegion();
#endif

    // ======================================
    // change check & Input/Output Handler
    // ======================================
    for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
    {
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
        if(ScalerAudioGetInternalAudioGenEnable(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _ENABLE)
        {
            SysAudioOutputHandler(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
            continue;
        }
#endif
        SysAudioPathSettingCheck(ucPathIndex);

#if(_AUDIO_PATH_VALID > 0x01)
        if(SysAudioCheckSameInputAtPreviousPath(ucPathIndex) == _FALSE)
#endif
        {
            SysAudioInputHandler(SysAudioGetInputSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)), GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));
        }

        SysAudioOutputHandler(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
    }

    // ======================================
    // Audio State Change
    // ======================================
    for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
    {
        enumAudioReadyStatus = SysAudioStableCheck(ucPathIndex);

        switch(GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex))
        {
            case _AUDIO_STATUS_MODE_SWITCH:
                DebugMessageAudio("Switch to Audio Mode Switch", ucPathIndex);
                SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PREPARING);
                break;

            case _AUDIO_STATUS_RESET_TO_PREPARING:
                DebugMessageAudio("Switch to Preparing", ucPathIndex);
                SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PREPARING);
                break;

            case _AUDIO_STATUS_PREPARING:
                if(ScalerAudioCheckModeSwitch(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _TRUE)
                {
                    DebugMessageAudio("Switch to Audio Mode Switch", ucPathIndex);
                    SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_MODE_SWITCH);
                }
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                else if(SysAudioTtsGetPlaybackEvent(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _TRUE)
                {
                    DebugMessageAudio("Switch to Audio TTS Playback", ucPathIndex);
                    SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_TTS_PLAYBACK);
                }
#endif
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
                else if(ScalerAudioSamplingFreqDetect(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) <= ScalerAudioGetSamplingFreqPacket(UserCommonAudioGetSamplingFreqLimit()))
#else
                else if(SysAudioSourceAudioReceived(ucPathIndex) == _TRUE)
#endif
                {
                    DebugMessageAudio("Switch to Audio Setting Mode", ucPathIndex);
                    SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_SETTING);
                }
                break;

            case _AUDIO_STATUS_SETTING:
                if((SysAudioSourceAudioReceived(ucPathIndex) == _FALSE) || (GET_AUDIO_PATH_AUDIO_INPUT_READY(ucPathIndex) == _AUDIO_READY_FALSE))
                {
                    DebugMessageAudio("Switch to Audio Preparing", ucPathIndex);
                    SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PREPARING);
                }
                else if(enumAudioReadyStatus == _AUDIO_READY_TRUE)
                {
                    DebugMessageAudio("Switch to Audio Playback", ucPathIndex);
                    SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PLAYBACK);
                }

                break;

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
            case _AUDIO_STATUS_PLAYBACKCHECK:
                if(enumAudioReadyStatus == _AUDIO_READY_TRUE)
                {
                    if(SysAudioFormatChangeCheck(ucPathIndex) == _TRUE)
                    {
                        DebugMessageAudio("Switch to Audio Preparing", ucPathIndex);
                        SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PREPARING);
                    }
                    else
                    {
                        DebugMessageAudio("Switch to Audio Playback", ucPathIndex);
                        SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PLAYBACK);
                    }
                }
                else
                {
                    if(SysRegionGetDisplayState(enumDisplayRegion) != _DISPLAY_STATE_ACTIVE)
                    {
                        DebugMessageAudio("Switch to Audio Preparing", ucPathIndex);
                        SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PREPARING);
                    }
                }
                break;
#endif

            case _AUDIO_STATUS_PLAYBACK:
                if(enumAudioReadyStatus == _AUDIO_READY_FALSE)
                {
#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
#if(_AUDIO_ARC_SUPPORT == _ON)
                    if((SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_ACTIVE) && (GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex) != _AUDIO_ARC_OUT))
#else
                    if(SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_ACTIVE)
#endif
                    {
                        DebugMessageAudio("Switch to Audio Prebackcheck", ucPathIndex);
                        SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PLAYBACKCHECK);
                    }
                    else
#endif
                    {
                        DebugMessageAudio("Switch to Audio Preparing", ucPathIndex);
                        SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PREPARING);
                    }
                }
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                else if(SysAudioTtsGetPlaybackEvent(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _TRUE)
                {
                    DebugMessageAudio("Switch to Audio TTS Playback", ucPathIndex);
                    SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_TTS_PLAYBACK);
                }
#endif
                break;

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
            case _AUDIO_STATUS_TTS_PLAYBACK:
                if(ScalerAudioTtsPlaybackStableCheck() == _TRUE)
                {
                    SET_TTS_PLAYBACK_CHANGE();
                    DebugMessageAudio("TTS Fail and Back to Audio Preparing", ucPathIndex);
                    SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PREPARING);
                }

                // Check if TTS play done
                if(ScalerAudioTtsGetPlayDoneStatus() == _TRUE)
                {
                    SET_TTS_PLAYBACK_CHANGE();

                    // Check Previous Audio State
                    if(enumAudioReadyStatus == _AUDIO_READY_TRUE)
                    {
                        DebugMessageAudio("TTS End and Back to Audio Playback", ucPathIndex);
                        SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PLAYBACK);
                    }
                    else
                    {
                        DebugMessageAudio("TTS End and Back to Audio Preparing", ucPathIndex);
                        SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_PREPARING);
                    }
                }
                break;
#endif
            case _AUDIO_STATUS_POWER_OFF:
            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Audio Mode Handler. Audio state setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioModeHandler(void)
{
    BYTE ucPathIndex = _PATH_0;

    for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
    {
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
        if(ScalerAudioGetInternalAudioGenEnable(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _ENABLE)
        {
            continue;
        }
#endif

        switch(GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex))
        {
            case _AUDIO_STATUS_MODE_SWITCH:
                if(GET_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex) == _TRUE)
                {
                    CLR_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex);
                    ScalerAudioModeSwitchProcess(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));
                }
                break;

            case _AUDIO_STATUS_PREPARING:
                if(GET_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex) == _TRUE)
                {
                    CLR_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex);

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                    if(GET_TTS_PLAYBACK_CHANGE() == _TRUE)
                    {
                        CLR_TTS_PLAYBACK_CHANGE();

                        // Recover TTS
                        ScalerAudioTtsRecoverProc();

                        // Reset TTS
                        ScalerAudioTtsResetProc();
                    }
#endif
                    SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    if(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex) == _AUDIO_ARC_OUT)
                    {
                        // Disable Audio Parallel Mode
                        SysAudioParallelModeOutput(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);
                    }
#endif

#if(_AUDIO_PATH_VALID > 0x01)
                    if((SysAudioCheckOtherPathHasSameInput(ucPathIndex) == _FALSE) ||
                       ((GET_AUDIO_PATH_AUDIO_INPUT_READY(ucPathIndex) == _AUDIO_READY_FALSE) && (SysAudioCheckSameInputAtNextPathNeedToReset(ucPathIndex) == _FALSE)))
#endif
                    {
                        DebugMessageAudio("Reset Interface Audio", ucPathIndex);

                        ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
                        ScalerTimerDelayXms(3);
                        ScalerAudioInputDigitalMute(_ON, GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));

#if((_HDMI_SUPPORT == _ON) && (_HW_HDMI_AUDIO_8CH_LAYOUT_NORMAL_OUTPUT == _OFF))
                        if(ScalerAudioDigitalAudioSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _SOURCE_HDMI)
                        {
                            // Reset SPDIF Output Channel
                            ScalerAudioHdmiI2sSpdifChannelOutputSelect(_AUDIO_DEFAULT_MODE, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));
                        }
#endif

#if((_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON) && (_AUDIO_COMPRESS_SUPPORT == _ON))
                        // Reset SPDIF Path
                        ScalerAudioSwitchI2sSpdifPath(_AUDIO_DVC_PATH, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));
#endif
                    }
                    // Set Coding Type LPCM
                    SET_AUDIO_PATH_AUDIO_FORMAT(ucPathIndex, _AUDIO_LPCM);
                }
                break;

            case _AUDIO_STATUS_SETTING:
                if(GET_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex) == _TRUE)
                {
                    CLR_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex);

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                    if(GET_TTS_PLAYBACK_CHANGE() == _TRUE)
                    {
                        CLR_TTS_PLAYBACK_CHANGE();

                        // Recover TTS
                        ScalerAudioTtsRecoverProc();

                        // Reset TTS
                        ScalerAudioTtsResetProc();
                    }
#endif
                    SET_AUDIO_PATH_AUDIO_FORMAT(ucPathIndex, UserCommonAudioGetPathNonLPCMStatus(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)));

                    // Setting SPDIF/IIS Path by LPCM/Non-LPCM
#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
#if(_AUDIO_COMPRESS_SUPPORT == _ON)
                    if((GET_AUDIO_PATH_AUDIO_FORMAT(ucPathIndex) == _AUDIO_NON_LPCM) || (ScalerAudioGetInputChannelCount(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) > _AUDIO_CHANNEL_COUNT_2))
#else
                    if(ScalerAudioGetInputChannelCount(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) > _AUDIO_CHANNEL_COUNT_2)
#endif
                    {
                        ScalerAudioSwitchI2sSpdifPath(_AUDIO_BYPASS_PATH, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));
                    }
                    else
                    {
                        ScalerAudioSwitchI2sSpdifPath(_AUDIO_DVC_PATH, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));
                    }
#endif

                    // Setting HDMI Mac SPDIF Channel Output
#if((_HDMI_SUPPORT == _ON) && (_HW_HDMI_AUDIO_8CH_LAYOUT_NORMAL_OUTPUT == _OFF))
                    if(ScalerAudioDigitalAudioSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _SOURCE_HDMI)
                    {
                        ScalerAudioHdmiI2sSpdifChannelOutputSelect(_AUDIO_SELECT_BY_CA_MODE, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));
                    }
#endif
                    // Update User Define Frequency
                    SysAudioSetUserDefineAudioFrequency();

                    // Set User Define Frequency When No Audio except input port
                    ScalerAudioSyncUserDefineFrequencyPllSetting();

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                    if(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex) == _AUDIO_ARC_OUT)
                    {
#if(_AUDIO_FORCE_PARALLEL_MODE == _OFF)
                        if((ScalerAudioSamplingFreqDetect(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) > _AUDIO_FREQ_PACKET_192K) && (GET_AUDIO_PATH_AUDIO_FORMAT(ucPathIndex) == _AUDIO_NON_LPCM))
#endif
                        {
#if((_DP_SUPPORT == _ON) && (_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON))
                            // Check HBR Audio Receive Type
                            if((ScalerAudioDigitalAudioSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _SOURCE_DP) &&
                               (ScalerAudioDpGetHbr8ChannelSupport(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _TRUE))
                            {
                                // Disable Audio Parallel Mode
                                SysAudioParallelModeOutput(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);
                                DebugMessageAudio("[Audio] DP Port with HBR Audio", ucPathIndex);
                            }
                            else
#endif // End of f((_DP_SUPPORT == _ON) && (_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON))
                            {
                                // Enable Parallel Mode
                                SysAudioParallelModeOutput(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _ENABLE);
                                DebugMessageAudio("[Audio] Non-DP Port with HBR Audio", ucPathIndex);
                            }
                        }
                    }
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
                    SysAudioPlayingAloneProc(ucPathIndex, _AUDIO_STATUS_SETTING);
#endif
                }
                break;

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
            case _AUDIO_STATUS_PLAYBACKCHECK:
                if(GET_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex) == _TRUE)
                {
                    CLR_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex);
                    SysAudioFastOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);

#if(_AUDIO_PATH_VALID > 0x01)
                    if((SysAudioCheckOtherPathHasSameInput(ucPathIndex) == _FALSE) ||
                       ((GET_AUDIO_PATH_AUDIO_INPUT_READY(ucPathIndex) == _AUDIO_READY_FALSE) && (SysAudioCheckSameInputAtNextPathNeedToReset(ucPathIndex) == _FALSE)))
#endif
                    {
                        // Mac Reset
                        ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
                        ScalerTimerDelayXms(3);
                        ScalerAudioInputDigitalMute(_ON, GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
                    }
                }
                break;
#endif

            case _AUDIO_STATUS_PLAYBACK:
                if(GET_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex) == _TRUE)
                {
                    CLR_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex);

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
                    if(GET_TTS_PLAYBACK_CHANGE() == _TRUE)
                    {
                        CLR_TTS_PLAYBACK_CHANGE();

                        // Recover TTS
                        ScalerAudioTtsRecoverProc();

                        // Reset TTS
                        ScalerAudioTtsResetProc();
                    }
#endif
                    SET_AUDIO_PATH_AUDIO_FS(ucPathIndex, ScalerAudioSamplingFreqDetect(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)));
                    SET_AUDIO_PATH_AUDIO_CHANNEL_COUNT(ucPathIndex, ScalerAudioGetRxChannelCount(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)));

#if(_AUDIO_PATH_VALID > 0x01)
                    if((ucPathIndex > _PATH_0) && (SysAudioCheckSameInputAtPreviousPathReady(ucPathIndex) == _TRUE))
                    {
                        DebugMessageAudio("Not Set Interface Audio Twice When Two Path Same Input Port", ucPathIndex);

                        if(UserCommonAudioGetPathOutputMuteStatus(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _AUDIO_MUTE_OFF)
                        {
#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
                            if(GET_AUDIO_PATH_AUDIO_PRE_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACKCHECK)
                            {
                                SysAudioFastOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _ENABLE);
                            }
                            else
#endif
                            {
                                SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _ENABLE);
                            }
                        }
                    }
                    else
#endif
                    {
                        // Eanble Mac Audio Watchdog
                        ScalerAudioWatchDogProc(_ON, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));

                        if(UserCommonAudioGetPathOutputMuteStatus(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _AUDIO_MUTE_OFF)
                        {
#if((_HDMI_SUPPORT == _ON) && (_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                            if(SysAudioHbrAudioSettingForParallelMode(ucPathIndex) == _FALSE)
                            {
                                SET_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex);
                                break;
                            }
#endif
                            // UnMute Mac,Dac,ARC
                            ScalerAudioInputDigitalMute(_OFF, GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
                            ScalerTimerDelayXms(3);

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
                            if(GET_AUDIO_PATH_AUDIO_PRE_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACKCHECK)
                            {
                                SysAudioFastOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _ENABLE);
                            }
                            else
#endif
                            {
                                SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _ENABLE);
                            }
                        }
                    }

#if(_SLEEP_AUDIO_SUPPORT == _ON)
                    SysAudioPlayingAloneProc(ucPathIndex, _AUDIO_STATUS_PLAYBACK);
#endif
                }
                break;

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
            case _AUDIO_STATUS_TTS_PLAYBACK:
                if(GET_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex) == _TRUE)
                {
                    CLR_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex);
                    // TTS Config
                    ScalerAudioTtsPlayConfig();

                    // Clear Flag
                    ScalerAudioTtsSetPlaybackEvent(_DISABLE);
                }
                break;
#endif

            case _AUDIO_STATUS_RESET_TO_PREPARING:
            case _AUDIO_STATUS_POWER_OFF:
            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Audio Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioInitialSetting(void)
{
    BYTE ucPathIndex = _PATH_0;

    SET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex, _AUDIO_DAC_OUT);
    SET_AUDIO_PATH_INPUT_PORT(ucPathIndex, SysRegionGetInputPort(UserInterfaceAudioGetDisplayModeRegion()));
    SET_AUDIO_PATH_AUDIO_FORMAT(ucPathIndex, _AUDIO_LPCM);
    ucPathIndex++;

#if(_AUDIO_ARC_SUPPORT == _ON)
    SET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex, _AUDIO_ARC_OUT);
    SET_AUDIO_PATH_INPUT_PORT(ucPathIndex, UserCommonAudioGetArcInputport());
    SET_AUDIO_PATH_AUDIO_FORMAT(ucPathIndex, _AUDIO_LPCM);
    ucPathIndex++;
#endif
}

//--------------------------------------------------
// Description  : Audio Path Setting And Check
// Input Value  : ucPathIndex
// Output Value : None
//--------------------------------------------------
void SysAudioPathSettingCheck(BYTE ucPathIndex)
{
    switch(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex))
    {
        case _AUDIO_DAC_OUT:
            SET_AUDIO_PATH_INPUT_PORT(ucPathIndex, SysRegionGetInputPort(UserInterfaceAudioGetDisplayModeRegion()));
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            SET_AUDIO_PATH_INPUT_PORT(ucPathIndex, UserCommonAudioGetArcInputport());
            break;
#endif
        default:
            break;
    }

    SysAudioInputSourceChangeCheck(ucPathIndex);
    SysAudioOutputPortChangeCheck(ucPathIndex);
}

//--------------------------------------------------
// Description  : Audio Input Port Change Check
// Input Value  : InputChangeCheck
// Output Value : _FALSE/ _TRUE
//--------------------------------------------------
void SysAudioInputSourceChangeCheck(BYTE ucPathIndex)
{
    EnumAudioInputSource enumAudioSourceType = SysAudioGetInputSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
    EnumRegionIndex enumRegionIndex = UserInterfaceAudioGetRegionIndex();

#if((_SLEEP_AUDIO_SUPPORT == _ON) && (((_LINE_IN_SUPPORT == _ON) && (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN) && (_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON)) || ((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))))
    EnumAudioStandAloneStatus enumStandaloneStatus = UserInterfaceAudioGetStandAloneStatus();
#endif

    switch(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex))
    {
        case _AUDIO_DAC_OUT:
            if(enumRegionIndex >= _MULTI_DISPLAY_MAX)
            {
#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
                if((GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACKCHECK) ||
                   (GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACK))
#else
                if(GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACK)
#endif
                {
                    SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_RESET_TO_PREPARING);

                    DebugMessageAudio("Switch to Audio Mode Switch", ucPathIndex);
                    DebugMessageAudio("enumRegionIndex >= _MULTI_DISPLAY_MAX", ucPathIndex);
                }
                return;
            }

            // change audio Input port
            if(ScalerAudioGetAudioInputPortChanged(enumAudioSourceType, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _TRUE)
            {
                if(GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACK)
                {
                    SysAudioOutputProc(_AUDIO_DAC_OUT, _DISABLE);

#if(_AUDIO_PATH_VALID > 0x01)
                    if(SysAudioCheckOtherPathHasSameInput(ucPathIndex) == _FALSE)
#endif
                    {
                        ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));

                        ScalerTimerDelayXms(3);
                        ScalerAudioInputDigitalMute(_ON, _AUDIO_DAC_OUT);
                    }
                }

#if(_LINE_IN_SUPPORT == _ON)
                if(enumAudioSourceType == _LINE_IN_AUDIO)
                {
                    EnumDisplayRegion enumDisplayRegion = UserInterfaceAudioGetDisplayModeRegion();
#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN) && (_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON))
                    if(((enumDisplayRegion == _DISPLAY_RGN_NONE) && (SysAudioCheckSourceJudge() == _TRUE)) ||
                       (GET_RGN_SOURCE_JUDGE(enumRegionIndex) == _TRUE) ||
                       ((enumStandaloneStatus == _AUDIO_STAND_ALONE_TRUE) &&
                        (GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)))
#else
                    if(((enumDisplayRegion == _DISPLAY_RGN_NONE) && (SysAudioCheckSourceJudge() == _TRUE)) ||
                       (GET_RGN_SOURCE_JUDGE(enumRegionIndex) == _TRUE))
#endif
                    {
#if(_EMBEDDED_DAC_SUPPORT == _ON)
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                        ScalerAudioDACNormalToDepop();
#endif
                        DebugMessageAudio("Audio Switch Input To Line In", GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));

                        ScalerAudioSourceInputSwitch(_LINE_IN_AUDIO, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));

                        CLR_AUDIO_POWER_CUT_TO_LINE_IN_STATUS();
                    }
                }
                else
#endif
                {
#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
                    if((GET_RGN_SOURCE_JUDGE(enumRegionIndex) == _TRUE) ||
                       ((enumStandaloneStatus == _AUDIO_STAND_ALONE_TRUE) &&
                        (enumAudioSourceType == _DIGITAL_AUDIO) &&
                        (ScalerAudioGetDpStandaloneAudioStatus(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _TRUE)))
#else
                    if(GET_RGN_SOURCE_JUDGE(enumRegionIndex) == _TRUE)
#endif
                    {
#if(_EMBEDDED_DAC_SUPPORT == _ON)
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                        ScalerAudioDACNormalToDepop();
#endif
                        DebugMessageAudio("Audio Switch Input To Digital", GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));

                        ScalerAudioSourceInputSwitch(_DIGITAL_AUDIO, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));
                    }
                }
                SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_RESET_TO_PREPARING);
            }
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            if(ScalerAudioGetDigitalAudioPort(_AUDIO_ARC_OUT) != ScalerAudioDxToRxMapping(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), _AUDIO_PORT_MAP_TO_CURRENT))
            {
                SysAudioOutputProc(_AUDIO_ARC_OUT, _DISABLE);

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                SysAudioParallelModeOutput(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);
#endif

#if(_AUDIO_PATH_VALID > 0x01)
                if(SysAudioCheckOtherPathHasSameInput(ucPathIndex) == _FALSE)
#endif
                {
                    ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
                    ScalerTimerDelayXms(3);
                    ScalerAudioInputDigitalMute(_ON, _AUDIO_ARC_OUT);
                }
                ScalerAudioSwitchArcSpdifPath(UserCommonAudioGetArcSource(), GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));

                SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_RESET_TO_PREPARING);
            }
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio Output Change Check
// Input Value  : ucPathIndex
// Output Value : _TRUE/ _FALSE
//--------------------------------------------------
void SysAudioOutputPortChangeCheck(BYTE ucPathIndex)
{
#if(_EMBEDDED_DAC_SUPPORT == _ON)
    EnumAudioDACOutput enumAudioDacOutput = UserInterfaceAudioDACGetOutput();
#endif

    switch(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex))
    {
        case _AUDIO_DAC_OUT:
#if(_EMBEDDED_DAC_SUPPORT == _ON)
            if((ScalerAudioDACGetState() != _AUDIO_DAC_OFF) && (ScalerAudioDACGetState() != _AUDIO_DAC_INITIAL) && (ScalerAudioDACGetState() != _AUDIO_DAC_CHARGE))
            {
                // User want to change DAC Output
                if(ScalerAudioDACGetOutput() != enumAudioDacOutput)
                {
                    if(GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACK)
                    {
                        SysAudioOutputProc(_AUDIO_DAC_OUT, _DISABLE);

#if(_AUDIO_PATH_VALID > 0x01)
                        if(SysAudioCheckOtherPathHasSameInput(ucPathIndex) == _FALSE)
#endif
                        {
                            ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
                            ScalerTimerDelayXms(3);
                            ScalerAudioInputDigitalMute(_ON, _AUDIO_DAC_OUT);
                        }
                    }

                    DebugMessageAudio("Audio Dac Switch Output", ScalerAudioDACGetOutput());

                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                    ScalerAudioDACNormalToDepop();

                    ScalerAudioDACSetVcmReady(_OFF);

                    ScalerAudioDACSetState(_AUDIO_DAC_CHARGE);

                    SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_RESET_TO_PREPARING);
                }
            }
#endif
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:

            if(GET_AUDIO_ARC_TX_MODE_STATE() != _ARC_MODE_STATUS_POWER_OFF)
            {
                // User want to change ARC Mode or Output Channel
                if(SysAudioArcTxOutputChange() == _TRUE)
                {
                    if(GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACK)
                    {
                        SysAudioOutputProc(_AUDIO_DAC_OUT, _DISABLE);

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                        SysAudioParallelModeOutput(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);
#endif

#if(_AUDIO_PATH_VALID > 0x01)
                        if(SysAudioCheckOtherPathHasSameInput(ucPathIndex) == _FALSE)
#endif
                        {
                            ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
                            ScalerTimerDelayXms(3);
                            ScalerAudioInputDigitalMute(_ON, _AUDIO_DAC_OUT);
                        }
                    }

                    DebugMessageAudio("Audio ARC Switch Output", 0x00);

                    SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_RESET_TO_PREPARING);
                }
            }

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio Input Check
// Input Value  : ucPathIndex
// Output Value : EnumAudioStatus
//--------------------------------------------------
EnumAudioStatus SysAudioInputGetReadyToPlay(BYTE ucPathIndex)
{
    EnumAudioStatus enumAudioReadyStatus = _AUDIO_READY_TRUE;

#if(_AUDIO_PATH_VALID > 0x01)
    if((GET_AUDIO_PATH_AUDIO_INPUT_READY(ucPathIndex) == _AUDIO_READY_TRUE) && (SysAudioCheckOtherPathHasSameInput(ucPathIndex) == _TRUE))
    {
        for(BYTE ucCheckPath = _PATH_0; ucCheckPath < _AUDIO_PATH_VALID; ucCheckPath++)
        {
            // Check Other path with same inputport input not ready
            if((ucCheckPath != ucPathIndex) &&
               (GET_AUDIO_PATH_INPUT_PORT(ucPathIndex) == GET_AUDIO_PATH_INPUT_PORT(ucCheckPath)) &&
               (GET_AUDIO_PATH_AUDIO_INPUT_READY(ucCheckPath) == _AUDIO_READY_FALSE))
            {
                return _AUDIO_READY_FALSE;
            }
        }
    }
#endif

#if(_LINE_IN_SUPPORT == _ON)
    if(SysAudioGetInputSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _LINE_IN_AUDIO)
    {
        return _AUDIO_READY_TRUE;
    }
    else
#endif
    {
        if(ScalerAudioGetAudioDetected(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _AUDIO_READY_TRUE)
        {
            enumAudioReadyStatus = _AUDIO_READY_TRUE;

            if(SysAudioGetInputSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _DIGITAL_AUDIO)
            {
                // Sampling Frequency Change Check
                if(SysAudioSamplingFreqChange(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _TRUE)
                {
                    DebugMessageAudio("Audio Ready False: Sampling Frequency Change", 0);

                    enumAudioReadyStatus = _AUDIO_READY_FALSE;
                }

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
                // Sampling Frequency Limitation Check
                if(ScalerAudioSamplingFreqDetect(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) > ScalerAudioGetSamplingFreqPacket(UserInterfaceAudioGetSamplingFreqLimit()))
                {
                    DebugMessageAudio("Audio Ready False: Sampling Frequency Over Limitation", 0);

                    enumAudioReadyStatus = _AUDIO_READY_FALSE;
                }
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)
                // DP Audio Capability Status Check
                if((SysSourceGetPortTypeFromInputPort(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _PORT_DP) && (ScalerAudioDpGetCapabilityState(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _AUDIO_DP_DPCD_NOT_SUPPORT))
                {
                    DebugMessageAudio("Audio Ready False : DP Audio Capability Not Support", 0);

                    enumAudioReadyStatus = _AUDIO_READY_FALSE;
                }

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
                if(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex) == _AUDIO_ARC_OUT)
                {
#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
                    if(ScalerAudioDpGetHbr8ChannelSupport(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _FALSE)
                    {
                        if(ScalerAudioDpGetHbrOperationState(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _TRUE)
                        {
                            DebugMessageAudio("Audio Ready False : DP Audio in HBR but Not Start Operation", 0);

                            enumAudioReadyStatus = _AUDIO_READY_FALSE;
                        }
                    }
                    else
                    {
                        if(ScalerAudioDpGetHbrOperationState(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _FALSE)
                        {
                            DebugMessageAudio("Audio Ready False : DP Audio in Non-HBR but Not End Operation", 0);

                            enumAudioReadyStatus = _AUDIO_READY_FALSE;
                        }
                    }
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
                }
#endif // End of #if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#endif // End of #if(_DP_SUPPORT == _ON)

                // Playback Status Check
                if(GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex) == _AUDIO_STATUS_PLAYBACK)
                {
                    // Coding Type Check
                    if(SysAudioLpcmStatusChange(ucPathIndex) == _TRUE)
                    {
                        DebugMessageAudio("Audio Ready False : LPCM Status Change", 0);

                        enumAudioReadyStatus = _AUDIO_READY_FALSE;
                    }

                    if((GET_AUDIO_PATH_AUDIO_FORMAT(ucPathIndex) == _AUDIO_LPCM) && (GET_AUDIO_PATH_AUDIO_CHANNEL_COUNT(ucPathIndex) != ScalerAudioGetRxChannelCount(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex))))
                    {
                        DebugMessageAudio("Audio Ready False : Channel count Change", 0);

                        enumAudioReadyStatus = _AUDIO_READY_FALSE;
                    }
                }
            }
            else
            {
                enumAudioReadyStatus = _AUDIO_READY_FALSE;
            }
        }
        else
        {
            enumAudioReadyStatus = _AUDIO_READY_FALSE;
        }
        return enumAudioReadyStatus;
    }
    return _AUDIO_READY_FALSE;
}

//--------------------------------------------------
// Description  : Audio Output Check
// Input Value  : enumAudioOutput
// Output Value : EnumAudioStatus
//--------------------------------------------------
EnumAudioStatus SysAudioOutputGetReadyToPlay(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
#if(_EMBEDDED_DAC_SUPPORT == _ON)
            if(ScalerAudioDACGetState() == _AUDIO_DAC_READY)
#endif
            {
                return _AUDIO_READY_TRUE;
            }
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:

            if(GET_AUDIO_ARC_TX_AUDIO_OUTPUT_READY() == _TRUE)
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
// Description  : Audio Change Audio State
// Input Value  : ucPathIndex, enumAudioState
// Output Value : None
//--------------------------------------------------
void SysAudioChangeAudioState(BYTE ucPathIndex, EnumAudioState enumAudioState)
{
    SET_AUDIO_PATH_AUDIO_PRE_STATE(ucPathIndex, GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex));
    SET_AUDIO_PATH_AUDIO_STATE(ucPathIndex, enumAudioState);
    SET_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex);
}

//--------------------------------------------------
// Description  : Audio All Path Swich Audio State
// Input Value  : enumAudioState
// Output Value : None
//--------------------------------------------------
void SysAudioChangeAllPathAudioState(EnumAudioState enumAudioState)
{
    BYTE ucPathIndex = _PATH_0;

    for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
    {
        SET_AUDIO_PATH_AUDIO_PRE_STATE(ucPathIndex, GET_AUDIO_PATH_AUDIO_STATE(ucPathIndex));
        SET_AUDIO_PATH_AUDIO_STATE(ucPathIndex, enumAudioState);
        SET_AUDIO_PATH_AUDIO_STATE_CHANGE(ucPathIndex);
    }
}

//--------------------------------------------------
// Description  : Audio stable check
// Input Value  : ucPathIndex
// Output Value : EnumAudioStatus
//--------------------------------------------------
EnumAudioStatus SysAudioStableCheck(BYTE ucPathIndex)
{
    if(SysAudioInputGetReadyToPlay(ucPathIndex) == _AUDIO_READY_FALSE)
    {
        SET_AUDIO_PATH_AUDIO_INPUT_READY(ucPathIndex, _AUDIO_READY_FALSE);
        return _AUDIO_READY_FALSE;
    }
    else
    {
        SET_AUDIO_PATH_AUDIO_INPUT_READY(ucPathIndex, _AUDIO_READY_TRUE);
    }

    if(SysAudioOutputGetReadyToPlay(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _AUDIO_READY_FALSE)
    {
        return _AUDIO_READY_FALSE;
    }

    if(UserCommonAudioGetPathReadyToPlayStatus(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _AUDIO_READY_FALSE)
    {
        return _AUDIO_READY_FALSE;
    }

    return _AUDIO_READY_TRUE;
}

//--------------------------------------------------
// Description  : Audio Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysAudioFormatChangeCheck(BYTE ucPathIndex)
{
    if((GET_AUDIO_PATH_AUDIO_FS(ucPathIndex) == ScalerAudioSamplingFreqDetect(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex))) &&
       (GET_AUDIO_PATH_AUDIO_FORMAT(ucPathIndex) == UserCommonAudioGetPathNonLPCMStatus(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex))))
    {
        return _FALSE;
    }
    return _TRUE;
}

//--------------------------------------------------
// Description  : Audio Output Prco (Normal-Control DVC & Ext.Amp & Ext. DSP)
// Input Value  : enumAudioOutput, bEnable
// Output Value : None
//--------------------------------------------------
void SysAudioOutputProc(EnumAudioOutputType enumAudioOutput, bit bEnable)
{
    bEnable = bEnable;

    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            SysAudioDacOutputProc(bEnable);
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            SysAudioArcTxOutputProc(bEnable);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Transfer depop mode to Normal mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioDisable(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            ScalerAudioDacDisable();
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            SysAudioArcTxDisable();
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio Output Reset Prco
// Input Value  : enumAudioOutput, bEnable
// Output Value : None
//--------------------------------------------------
void SysAudioOutputResetProc(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
#if(_EMBEDDED_DAC_SUPPORT == _ON)
            ScalerAudioDACNormalToDepop();
#endif
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio Tts Get Playback Event
// Input Value  : enumAudioOutput
// Output Value : _TRUE/ _FALSE
//--------------------------------------------------
bit SysAudioTtsGetPlaybackEvent(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
            return ScalerAudioTtsGetPlaybackEvent();
#endif
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            break;
#endif
        default:
            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio Source Audio Received
// Input Value  : ucPathIndex
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioSourceAudioReceived(BYTE ucPathIndex)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(SysAudioGetInputSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _LINE_IN_AUDIO)
    {
        return _TRUE;
    }
#endif

    if(ScalerAudioSamplingFreqDetect(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) != _AUDIO_FREQ_PACKET_NO_AUDIO)
    {
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if any Later Path has Same InputPort
// Input Value  : ucPathIndex
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioCheckSameInputAtNextPathNeedToReset(BYTE ucPathIndex)
{
    ucPathIndex = ucPathIndex;

#if(_AUDIO_PATH_VALID > 0x01)
    BYTE ucCheckPath = ucPathIndex;

    ucCheckPath++;

    while(ucCheckPath < _AUDIO_PATH_VALID)
    {
#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
        if((GET_AUDIO_PATH_INPUT_PORT(ucPathIndex) == GET_AUDIO_PATH_INPUT_PORT(ucCheckPath)) && ((GET_AUDIO_PATH_AUDIO_STATE(ucCheckPath) == _AUDIO_STATUS_PREPARING) || (GET_AUDIO_PATH_AUDIO_STATE(ucCheckPath) == _AUDIO_STATUS_PLAYBACKCHECK)))
#else
        if((GET_AUDIO_PATH_INPUT_PORT(ucPathIndex) == GET_AUDIO_PATH_INPUT_PORT(ucCheckPath)) && (GET_AUDIO_PATH_AUDIO_STATE(ucCheckPath) == _AUDIO_STATUS_PREPARING))
#endif
        {
            return _TRUE;
        }
        ucCheckPath++;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if any Previous Path has Same InputPort
// Input Value  : ucPathIndex
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioCheckSameInputAtPreviousPath(BYTE ucPathIndex)
{
    ucPathIndex = ucPathIndex;

#if(_AUDIO_PATH_VALID > 0x01)
    BYTE ucCheckPath = ucPathIndex;

    while(ucCheckPath > _PATH_0)
    {
        ucCheckPath--;
        if(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex) == GET_AUDIO_PATH_INPUT_PORT(ucCheckPath))
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Same Input Of Previous Path Ready
// Input Value  : ucPathIndex
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioCheckSameInputAtPreviousPathReady(BYTE ucPathIndex)
{
    ucPathIndex = ucPathIndex;

#if(_AUDIO_PATH_VALID > 0x01)
    BYTE ucCheckPath = ucPathIndex;

    while(ucCheckPath > _PATH_0)
    {
        ucCheckPath--;
        if(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex) == GET_AUDIO_PATH_INPUT_PORT(ucCheckPath))
        {
            if(GET_AUDIO_PATH_AUDIO_STATE(ucCheckPath) == _AUDIO_STATUS_PLAYBACK)
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Other Path Has Same Input
// Input Value  : ucPathIndex
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioCheckOtherPathHasSameInput(BYTE ucPathIndex)
{
    ucPathIndex = ucPathIndex;

#if(_AUDIO_PATH_VALID > 0x01)
    for(BYTE ucCheckPath = _PATH_0; ucCheckPath < _AUDIO_PATH_VALID; ucCheckPath++)
    {
        if((ucCheckPath != ucPathIndex) && (GET_AUDIO_PATH_INPUT_PORT(ucPathIndex) == GET_AUDIO_PATH_INPUT_PORT(ucCheckPath)))
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio Get Audio Path
// Input Value  : ucPathIndex
// Output Value : _PATH
//--------------------------------------------------
BYTE SysAudioGetAudioPath(EnumAudioOutputType enumAudioOutput)
{
    BYTE ucPathIndex = _PATH_0;

    for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
    {
        if(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex) == enumAudioOutput)
        {
            return ucPathIndex;
        }
    }

    return _PATH_0;
}

#if(_SLEEP_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Receive Audio Status
// Input Value  : ucPathIndex
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioPlayingAloneStatus(void)
{
    BYTE ucPathCnt = _PATH_0;

    for(ucPathCnt = _PATH_0; ucPathCnt < _AUDIO_PATH_VALID; ucPathCnt++)
    {
        if(GET_AUDIO_PATH_AUDIO_PLAY_ALONE(ucPathCnt) == _TRUE)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio Playing Alone Proc
// Input Value  : ucPathIndex
// Output Value : None
//--------------------------------------------------
void SysAudioPlayingAloneProc(BYTE ucPathIndex, EnumAudioState enumAudioState)
{
    EnumAudioStandAloneStatus enumStandaloneStatus = UserInterfaceAudioGetStandAloneStatus();

    switch(enumAudioState)
    {
        case _AUDIO_STATUS_SETTING:
            if(enumStandaloneStatus == _AUDIO_STAND_ALONE_TRUE)
            {
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
                if((SysAudioGetInputSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _DIGITAL_AUDIO) &&
                   (ScalerAudioGetDigitalAudioSource(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _DIGITAL_AUDIO_SOURCE_DP))
                {
                    SET_AUDIO_PLAYBACK_SEARCH_INDEX(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));

                    // Enable DP audio FSM
                    ScalerAudioDpAudioEnable(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), _ENABLE);

                    DebugMessageAudio("Sleep Audio Playback Index", GET_AUDIO_PLAYBACK_SEARCH_INDEX());
                }
#endif

#if((_LINE_IN_SUPPORT == _ON) && (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN) && (_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON))
                SET_AUDIO_PATH_AUDIO_PLAY_ALONE(ucPathIndex);
#endif
            }
            else
            {
                CLR_AUDIO_PATH_AUDIO_PLAY_ALONE(ucPathIndex);
            }
            break;

        case _AUDIO_STATUS_PLAYBACK:
            if(enumStandaloneStatus == _AUDIO_STAND_ALONE_TRUE)
            {
#if((_LINE_IN_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
                if(SysAudioGetInputSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _LINE_IN_AUDIO)
                {
                    SET_AUDIO_PATH_AUDIO_PLAY_ALONE(ucPathIndex);
                }
                else
                {
                    CLR_AUDIO_PATH_AUDIO_PLAY_ALONE(ucPathIndex);
                }
#endif

#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
                if((SysAudioGetInputSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _DIGITAL_AUDIO) &&
                   (ScalerAudioGetDigitalAudioSource(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _DIGITAL_AUDIO_SOURCE_DP))
                {
                    SET_AUDIO_PATH_AUDIO_PLAY_ALONE(ucPathIndex);
                }
                else
                {
                    CLR_AUDIO_PATH_AUDIO_PLAY_ALONE(ucPathIndex);
                }
#endif
            }
            else
            {
                CLR_AUDIO_PATH_AUDIO_PLAY_ALONE(ucPathIndex);
            }
            break;
        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get Audio Source
// Input Value  : enumAudioOutput
// Output Value : EnumAudioInputSource
//--------------------------------------------------
EnumAudioInputSource SysAudioGetInputSourceType(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            return UserInterfaceAudioGetSource();
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            return UserInterfaceAudioGetArcSource();
            break;
#endif
        default:
            break;
    }
    return _NO_AUDIO_SOURCE;
}

//--------------------------------------------------
// Description  : Get Dac Audio State
// Input Value  : None
// Output Value : EnumAudioState
//--------------------------------------------------
EnumAudioState SysAudioGetAudioState(void)
{
    return GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_DAC_OUT));
}

//--------------------------------------------------
// Description  : Get Path Audio State
// Input Value  : None
// Output Value : EnumAudioState
//--------------------------------------------------
EnumAudioState SysAudioGetPathAudioState(EnumAudioOutputType enumAudioOutput)
{
    return GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(enumAudioOutput));
}

//--------------------------------------------------
// Description  : Audio Power Process
// Input Value  : None
// Output Value : Node
//--------------------------------------------------
void SysAudioPowerProc(EnumPowerAction enumSwitch)
{
    BYTE ucPathIndex = _PATH_0;

    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // Update User Define Frequency
            SysAudioSetUserDefineAudioFrequency();

            SysAudioInitial();

            // Add User interface function
            UserInterfaceAudioPowerProc(_POWER_STATUS_NORMAL);

            // Switch all path to preparing state
            SysAudioChangeAllPathAudioState(_AUDIO_STATUS_RESET_TO_PREPARING);
            break;

        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

            for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
            {
                // Mute Audio
                SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);

                // Reset Digital Audio
                ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
            }

            // Add User interface function
            UserInterfaceAudioPowerProc(_POWER_STATUS_OFF);

            for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
            {
                // Disable Audio
                SysAudioDisable(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
            }

            // Switch all path to power off stat
            SysAudioChangeAllPathAudioState(_AUDIO_STATUS_POWER_OFF);
            break;

        case _POWER_ACTION_NORMAL_TO_PS:

            for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
            {
                // Mute Audio
                SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);

                // Reset Digital Audio
                ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
            }

            // Add User interface function
            UserInterfaceAudioPowerProc(_POWER_STATUS_SAVING);

            for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
            {
                // Disable Audio
                SysAudioDisable(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
            }

            // Switch all path to power off stat
            SysAudioChangeAllPathAudioState(_AUDIO_STATUS_POWER_OFF);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio Mute Process
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void SysAudioMuteProc(bit bMute)
{
    WORD usVolume = UserInterfaceAudioGetVolume();

    if(bMute == _ON)
    {
        if(ScalerAudioDVCGetVolumeMuteStatus() == _OFF)
        {
            // Ext. Audio Amplifier Mute Control
            UserInterfaceAudioAmpMuteProc(_ON);

            // Audio DVC Hold by Mute Support Option
            if(UserCommonAudioGetAdjustVolumeThroughDVC() == _TRUE)
            {
                // Digital Audio Output DVC Mute Control
                ScalerAudioMuteProc(_ON, usVolume);
            }
            else
            {
                // Audio DVC Hold by Mute Control
                ScalerAudioDVCAdjustVolume(0);
            }

            // Audio DVC Mute Flag Setting
            ScalerAudioDVCSetVolumeMuteStatus(_ON);
        }
    }
    else
    {
        bit bResult = 0;

#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
        bResult |= ((ScalerAudioDVCGetVolumeMuteStatus() == _ON) && (UserInterfaceAudioGetMuteStatus() == _OFF));
#else
        bResult |= (ScalerAudioDVCGetVolumeMuteStatus() == _ON);
#endif // End of #if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
        bResult |= (ScalerAudioGetInternalAudioGenEnable(SysRegionGetInputPort(UserInterfaceAudioGetDisplayModeRegion())) == _ENABLE);
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

        if(bResult == _TRUE)
        {
            // Audio DVC Hold by Mute Support Option
            if(UserCommonAudioGetAdjustVolumeThroughDVC() == _TRUE)
            {
                // Digital Audio Output DVC Mute Control
                ScalerAudioMuteProc(_OFF, usVolume);
            }

            // Ext. Audio Amplifier Mute Control
            UserInterfaceAudioAmpMuteProc(_OFF);

            // Audio DVC Mute Flag Setting
            ScalerAudioDVCSetVolumeMuteStatus(_OFF);
        }
    }
}

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Fast Mute Process (Fast-Control DVC & Ext.Amp & Ext. DSP)
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void SysAudioFastOutputProc(EnumAudioOutputType enumAudioOutput, bit bEnable)
{
    if(bEnable == _DISABLE)
    {
        // Audio DVC Use Fast-Mode Control
        SysAudioFastMuteProc(enumAudioOutput, _ON);

#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
        UserInterfaceAudioExternalCodecFastProc(_DISABLE);
#endif
    }
    else
    {
#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
        UserInterfaceAudioExternalCodecFastProc(_ENABLE);
#endif
        // Audio DVC Use Fast-Mode Control
        SysAudioFastMuteProc(enumAudioOutput, _OFF);
    }
}

//--------------------------------------------------
// Description  : Audio Fast Mute Proc
// Input Value  : enumAudioOutput, bEnable
// Output Value : None
//--------------------------------------------------
void SysAudioFastMuteProc(EnumAudioOutputType enumAudioOutput, bit bEnable)
{
    bEnable = bEnable;

    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            SysAudioDacFastMuteProc(bEnable);
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            SysAudioArcFastMuteProc(bEnable);
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio Mute Process
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void SysAudioDacFastMuteProc(bit bMute)
{
    WORD usVolume = UserInterfaceAudioGetVolume();

    if(ScalerAudioDVCGetVolumeMuteStatus() == _ON)
    {
        return;
    }

    if(bMute == _ON)
    {
        UserInterfaceAudioAmpFastMuteProc(_ON);
        ScalerAudioDVCVolumeFastMute(_ON, usVolume);
    }
    else
    {
        ScalerAudioDVCVolumeFastMute(_OFF, usVolume);
        UserInterfaceAudioAmpFastMuteProc(_OFF);
    }
}

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Mute Process
// Input Value  : _DISABLE => Mute On
// Output Value : None
//--------------------------------------------------
void SysAudioArcFastMuteProc(bit bMute)
{
    if(bMute == _ON)
    {
    }
    else
    {
    }
}
#endif
#endif

//--------------------------------------------------
// Description  : Audio Mute Process
// Input Value  : _DISABLE => Mute On
// Output Value : None
//--------------------------------------------------
void SysAudioDacOutputProc(bit bEnable)
{
    if(bEnable == _DISABLE)
    {
        SysAudioMuteProc(_ON);

#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
        UserInterfaceAudioExternalCodecProc(_DISABLE);
#endif
    }
    else
    {
#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
        UserInterfaceAudioExternalCodecProc(_ENABLE);
#endif

        SysAudioMuteProc(_OFF);
    }
}

//--------------------------------------------------
// Description  : Check Whether Audio Coding Type Change or Not
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioLpcmStatusChange(BYTE ucPathIndex)
{
    EnumAudioCodingType enumAudioCodingType = GET_AUDIO_PATH_AUDIO_FORMAT(ucPathIndex);
    EnumAudioOutputType enumAudioOutput = GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex);

    if(ScalerAudioDigitalAudioSourceType(enumAudioOutput) == _SOURCE_HDMI)
    {
        if(enumAudioCodingType != UserCommonAudioGetPathNonLPCMStatus(enumAudioOutput))
        {
            return _TRUE;
        }
    }
    else if(ScalerAudioDigitalAudioSourceType(enumAudioOutput) == _SOURCE_DP)
    {
        if(ScalerAudioLPCMCheckChange(enumAudioOutput) == _TRUE)
        {
            return _TRUE;
        }
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Whether Audio Sampling Frequency Change or Not
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioSamplingFreqChange(EnumAudioOutputType enumAudioOutput)
{
    if(ScalerAudioSamplingFreqChange(enumAudioOutput) == _TRUE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Parallel Mode Setting
// Input Value  : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void SysAudioParallelModeOutput(EnumAudioOutputType enumAudioOutput, bit bEnable)
{
    bEnable = bEnable;

    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
            SysAudioParallelModeSetting(bEnable);
#endif
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio Parallel Mode Setting
// Input Value  : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void SysAudioParallelModeSetting(bit bEnable)
{
#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
    EnumAudioSpdifParallelMode enumAudioSpdifParallelMode = UserCommonAudioSpdifParallelMode();
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
    EnumAudioI2sParallelMode enumAudioI2sParallelMode = UserCommonAudioI2sParallelMode();
    EnumAudioI2sParallelType enumAudioI2sParallelType = UserCommonAudioI2sParallelType();
#endif

    if(bEnable == _ENABLE)
    {
#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
        if(enumAudioSpdifParallelMode != _NO_SPDIF_PARALLEL_MODE)
        {
            ScalerAudioSpdifParallelModeSet(enumAudioSpdifParallelMode);

            SET_AUDIO_SPDIF_PARALLEL_MODE(enumAudioSpdifParallelMode);
        }
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
        if(enumAudioI2sParallelMode != _NO_I2S_PARALLEL_MODE)
        {
            ScalerAudioI2sParallelModeSet(enumAudioI2sParallelMode, enumAudioI2sParallelType);

            SET_AUDIO_I2S_PARALLEL_MODE(enumAudioI2sParallelMode);
            SET_AUDIO_I2S_PARALLEL_TYPE(enumAudioI2sParallelType);
        }
#endif
    }
    else
    {
#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
        ScalerAudioSpdifParallelModeReset();
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
        ScalerAudioI2sParallelModeReset();
#endif
    }
}

//--------------------------------------------------
// Description  : Check Audio Parallel Mode Type Change
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioParallelModeTypeChange(void)
{
#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
    if(GET_AUDIO_SPDIF_PARALLEL_MODE() != UserCommonAudioSpdifParallelMode())
    {
        DebugMessageAudio("False : Audio Parallel Mode SPDIF Type Change", 0);

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
    if((GET_AUDIO_I2S_PARALLEL_MODE() != UserCommonAudioI2sParallelMode()) || (GET_AUDIO_I2S_PARALLEL_TYPE() != UserCommonAudioI2sParallelType()))
    {
        DebugMessageAudio("False : Audio Parallel Mode I2S Type Change", 0);

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
#endif
}
#endif

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Fw Tracking Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioFwTrackingHandler(void)
{
    ScalerAudioFwTrackingHandler();
}
#endif

//--------------------------------------------------
// Description  : Audio Analog Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioDacHandler(void)
{
#if(_EMBEDDED_DAC_SUPPORT == _ON)
    EnumAudioDACOutput enumAudioDacOutput = UserInterfaceAudioDACGetOutput();

    switch(ScalerAudioDACGetState())
    {
        case _AUDIO_DAC_OFF:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                DebugMessageAudio("0.[Top Audio]Audio DAC OFF", 0x00);

                ScalerAudioDACClrStateChange();
            }

            break;

        case _AUDIO_DAC_INITIAL:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                ScalerAudioDACClrStateChange();

                DebugMessageAudio("0.[Top Audio]Audio DAC Initial", 0x00);

                ScalerTimerActiveTimerEvent(_DAC_VCM_INITIAL_TIME, _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_INITIAL);
            }

            break;

        case _AUDIO_DAC_CHARGE:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                ScalerAudioDACClrStateChange();

                DebugMessageAudio("0.[Top Audio]Audio DAC Charge", 0x00);

                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_CHARGE);

                ScalerAudioDACOutputSwitch(enumAudioDacOutput);
                ScalerAudioDACSetVcmReady(_ON);

                ScalerTimerActiveTimerEvent(_DAC_VCM_CHARGE_TIME, _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_CHARGE);
            }

            break;

        case _AUDIO_DAC_DEPOP:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                DebugMessageAudio("0.[Top Audio]Audio DAC Depop", 0x00);

                if(UserInterfaceAudioDACGetKeepDepopState() == _AUDIO_DAC_KEEP_DEPOP_FALSE)
                {
                    ScalerAudioDACClrStateChange();

                    ScalerAudioDACOutputEnable();

                    ScalerTimerActiveTimerEvent(_DAC_DEPOP_TO_NORMAL_WAIT_TIME, _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
                }
            }
            break;

        case _AUDIO_DAC_READY:

            if(ScalerAudioDACGetStateChange() == _TRUE)
            {
                ScalerAudioDACClrStateChange();

                DebugMessageAudio("0.[Top Audio]Audio DAC Ready", 0x00);
            }
            break;

        default:
            break;
    }
#endif // End of #if(_EMBEDDED_DAC_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Audio Input Handler
// Input Value  : enumAudioSourceType/ enumInputPort
// Output Value : None
//--------------------------------------------------
void SysAudioInputHandler(EnumAudioInputSource enumAudioSourceType, EnumInputPort enumInputPort)
{
    enumAudioSourceType = enumAudioSourceType;
    enumInputPort = enumInputPort;

    ScalerAudioDigitalDetect();

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
    ScalerAudioSpdifChannelStatusProc(enumAudioSourceType, enumInputPort);
#endif

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
    SysAudioFwTrackingHandler();
#endif
}

//--------------------------------------------------
// Description  : Audio Output Handler
// Input Value  : enumAudioOutput
// Output Value : None
//--------------------------------------------------
void SysAudioOutputHandler(EnumAudioOutputType enumAudioOutput)
{
    switch(enumAudioOutput)
    {
        case _AUDIO_DAC_OUT:
            SysAudioDacHandler();
            break;

#if(_AUDIO_ARC_SUPPORT == _ON)
        case _AUDIO_ARC_OUT:
            SysAudioArcTxHandler();
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioInitial(void)
{
    ScalerAudioInitial();

#if(_AUDIO_PARALLEL_MODE_SUPPORT == _ON)
    SysAudioParallelModeOutput(_AUDIO_DAC_OUT, _DISABLE);
#endif

    ScalerAudioSourceInputSwitch(UserInterfaceAudioGetSource(), SysSourceGetInputPort());

#if(_EMBEDDED_DAC_SUPPORT == _ON)
#if((_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_0) || (_HW_AUDIO_DAC_GEN == _AUDIO_DAC_GEN_1))
    ScalerAudioDACSetVcmReady(_ON);
#endif
    ScalerAudioDACSetState(_AUDIO_DAC_INITIAL);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
    SysAudioArcTxInitial();
#endif

#if(_LINE_IN_SUPPORT == _ON)
    CLR_AUDIO_POWER_CUT_TO_LINE_IN_STATUS();
#endif
}

//--------------------------------------------------
// Description  : Audio Frequency Set By User Define
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioSetUserDefineAudioFrequency(void)
{
    // Update User Define Frequency When No Audio
    EnumAudioSamplingFreqType enumAudioFreqNoAudio = UserCommonAudioUpdateUserSamplingFreq();

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    // Update User Define Frequency Limit
    EnumAudioSamplingFreqType enumAudioFreqLimit = UserCommonAudioGetSamplingFreqLimit();
#endif

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
    ScalerAudioTtsSetUserDefineAudioFrequency(enumAudioFreqNoAudio);
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

#if(_DP_AUDIO_RX0_SUPPORT == _ON)
    ScalerDpAudioRx0SetUserDefineAudioFrequency(enumAudioFreqNoAudio);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    ScalerDpAudioRx0SetUserDefineSamplingFreqLimit(enumAudioFreqLimit);
#endif
#endif // End of #if(_DP_AUDIO_RX0_SUPPORT == _ON)

#if(_DP_AUDIO_RX1_SUPPORT == _ON)
    ScalerDpAudioRx1SetUserDefineAudioFrequency(enumAudioFreqNoAudio);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    ScalerDpAudioRx1SetUserDefineSamplingFreqLimit(enumAudioFreqLimit);
#endif
#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)

#if(_DP_AUDIO_RX2_SUPPORT == _ON)
    ScalerDpAudioRx2SetUserDefineAudioFrequency(enumAudioFreqNoAudio);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    ScalerDpAudioRx2SetUserDefineSamplingFreqLimit(enumAudioFreqLimit);
#endif
#endif // End of #if(_DP_AUDIO_RX2_SUPPORT == _ON)

#if(_DP_AUDIO_RX3_SUPPORT == _ON)
    ScalerDpAudioRx3SetUserDefineAudioFrequency(enumAudioFreqNoAudio);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    ScalerDpAudioRx3SetUserDefineSamplingFreqLimit(enumAudioFreqLimit);
#endif
#endif // End of #if(_DP_AUDIO_RX3_SUPPORT == _ON)

#if(_DP_AUDIO_RX4_SUPPORT == _ON)
    ScalerDpAudioRx4SetUserDefineAudioFrequency(enumAudioFreqNoAudio);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    ScalerDpAudioRx4SetUserDefineSamplingFreqLimit(enumAudioFreqLimit);
#endif
#endif // End of #if(_DP_AUDIO_RX4_SUPPORT == _ON)

#if(_HDMI_MAC_RX3_SUPPORT == _ON)
    ScalerHdmiAudioRx3SetUserDefineAudioFrequency(enumAudioFreqNoAudio);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    ScalerHdmiAudioRx3SetUserDefineSamplingFreqLimit(enumAudioFreqLimit);
#endif
#endif // End of #if(_HDMI_MAC_RX3_SUPPORT == _ON)

#if(_HDMI_MAC_RX4_SUPPORT == _ON)
    ScalerHdmiAudioRx4SetUserDefineAudioFrequency(enumAudioFreqNoAudio);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    ScalerHdmiAudioRx4SetUserDefineSamplingFreqLimit(enumAudioFreqLimit);
#endif
#endif // End of #if(_HDMI_MAC_RX4_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Audio Power Cut Process
// Input Value  : enumPowerCutOnPort, enumPowerCutOffPort
// Output Value : None
//--------------------------------------------------
void SysAudioPowerCutProc(EnumInputPort enumPowerCutOnPort, EnumPortType enumPowerCutOnPortType, EnumInputPort enumPowerCutOffPort, EnumPortType enumPowerCutOffPortType)
{
#if(_DP_SUPPORT == _ON)
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
    EnumDpMacSel enumDpMacSel = ScalerDpRxGetMacSwitch(enumPowerCutOnPort);
#endif
#endif
    BYTE ucPathIndex = _PATH_0;

    enumPowerCutOnPortType = enumPowerCutOnPortType;
    enumPowerCutOffPortType = enumPowerCutOffPortType;

#if((_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    // Disable PowerCut when in Audio Pattern Gen
    if(ScalerAudioGetInternalAudioGenEnable(_NO_INPUT_PORT) == _ENABLE)
    {
        return;
    }
#endif

#if(_LINE_IN_SUPPORT == _ON)
    if((ScalerAudioGetInputSource(_AUDIO_DAC_OUT) == _LINE_IN_AUDIO) && (GET_AUDIO_POWER_CUT_TO_LINE_IN_STATUS() == _FALSE))
    {
        DebugMessageAudio("APC: Line In Mode", enumPowerCutOnPort);

        return;
    }
#endif

#if(_DP_SUPPORT == _ON)
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_COMBO)
    if((enumPowerCutOnPortType == _PORT_DP) && (enumDpMacSel == _DP_MAC_NONE))
    {
        DebugMessageAudio("APC: DP MAC None", enumPowerCutOnPort);

        return;
    }
#endif
#endif

    if(ScalerAudioSourceChangeCheck(enumPowerCutOnPort, enumPowerCutOnPortType) == _TRUE)
    {
        DebugMessageAudio("APC: Audio Power Cut Proc", 0);

        if(SysAudioGetPathAudioState(_AUDIO_DAC_OUT) == _AUDIO_STATUS_PLAYBACK)
        {
            SysAudioOutputProc(_AUDIO_DAC_OUT, _DISABLE);

            ScalerAudioInputDigitalReset(enumPowerCutOnPort, _AUDIO_DAC_OUT);
            ScalerTimerDelayXms(3);
            ScalerAudioInputDigitalMute(_ON, _AUDIO_DAC_OUT);
        }

#if(_EMBEDDED_DAC_SUPPORT == _ON)
        if(ScalerAudioDACGetState() == _AUDIO_DAC_READY)
        {
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
            ScalerAudioDACNormalToDepop();
        }
#endif

#if(_LINE_IN_SUPPORT == _ON)
        if(enumPowerCutOffPortType == _PORT_VGA)
        {
            DebugMessageAudio("APC: Line In", enumPowerCutOffPort);

            ScalerAudioSourceInputSwitch(_LINE_IN_AUDIO, enumPowerCutOffPort);

            SET_AUDIO_POWER_CUT_TO_LINE_IN_STATUS();
        }
        else
#endif
        {
            DebugMessageAudio("APC: Digital", enumPowerCutOffPort);

            ScalerAudioSourceInputSwitch(_DIGITAL_AUDIO, enumPowerCutOffPort);

#if(_LINE_IN_SUPPORT == _ON)
            CLR_AUDIO_POWER_CUT_TO_LINE_IN_STATUS();
#endif
        }
        ucPathIndex = SysAudioGetAudioPath(_AUDIO_DAC_OUT);
        SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_RESET_TO_PREPARING);
    }

#if(_AUDIO_ARC_SUPPORT == _ON)
    if(enumPowerCutOnPort == UserCommonAudioGetArcInputport())
    {
        DebugMessageAudio("APC: Audio Power Cut Proc", 0);

        if(SysAudioGetPathAudioState(_AUDIO_ARC_OUT) == _AUDIO_STATUS_PLAYBACK)
        {
            SysAudioOutputProc(_AUDIO_ARC_OUT, _DISABLE);

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
            SysAudioParallelModeOutput(_AUDIO_ARC_OUT, _DISABLE);
#endif
            ScalerAudioInputDigitalReset(enumPowerCutOnPort, _AUDIO_ARC_OUT);
            ScalerTimerDelayXms(3);
            ScalerAudioInputDigitalMute(_ON, _AUDIO_ARC_OUT);
        }

        ucPathIndex = SysAudioGetAudioPath(_AUDIO_ARC_OUT);
        SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_RESET_TO_PREPARING);
    }
#endif
}


//--------------------------------------------------
// Description  : Audio Reset Process
// Input Value  : enumPowerCutOnPort, enumPowerCutOffPort
// Output Value : None
//--------------------------------------------------
void SysAudioResetProc(EnumInputPort enumInputPort)
{
    BYTE ucPathIndex = _PATH_0;

    for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
    {
        if(enumInputPort == GET_AUDIO_PATH_INPUT_PORT(ucPathIndex))
        {
            SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
            if(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex) == _AUDIO_ARC_OUT)
            {
                SysAudioParallelModeOutput(_AUDIO_ARC_OUT, _DISABLE);
            }
#endif
            ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
            ScalerTimerDelayXms(3);
            ScalerAudioInputDigitalMute(_ON, GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));

            SysAudioOutputResetProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));
            SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_RESET_TO_PREPARING);
        }
    }
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Audio Secondary Data Reset Process
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void SysAudioDpAudioSecDataResetProc(EnumInputPort enumInputPort)
{
#if((_INTERNAL_AUDIO_TEST_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON))
    // Disable Data Reset when in Audio Pattern Gen
    if(ScalerAudioGetInternalAudioGenEnable(_NO_INPUT_PORT) == _ENABLE)
    {
        return;
    }
#endif
    SysAudioResetProc(enumInputPort);

    ScalerDpMacStreamRxSecDataReset(enumInputPort);
}

//--------------------------------------------------
// Description  : Check Dp Port Exist
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioCheckDpPortExist(void)
{
    BYTE ucPathIndex = _PATH_0;

    for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
    {
        if(ScalerAudioDigitalAudioSourceType(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _SOURCE_DP)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
#endif

#if(_LINE_IN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Source Judge Sraus
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysAudioCheckSourceJudge(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    // Check display state
    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE)
        {
            return _TRUE;
        }
    }
    return _FALSE;
}
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Internal Audio Gen Test Process
// Input Value  : _ON/ _OFF
// Output Value : None
//--------------------------------------------------
void SysAudioInternalGenTestProc(bit bOn)
{
    BYTE ucPathIndex = _PATH_0;

    for(ucPathIndex = _PATH_0; ucPathIndex < _AUDIO_PATH_VALID; ucPathIndex++)
    {
        SysAudioOutputProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex), _DISABLE);

        if(bOn == _ON)
        {
            SET_AUDIO_INTERNAL_GEN_INPUT_PORT(ucPathIndex, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));

            ScalerAudioSetUserDefineAudioGenFrequency(UserCommonAudioUpdateUserDefineAudioGenFreq());

            ScalerAudioInputDigitalReset(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex));

            ScalerAudioInternalAudioGenPowerControl(_ON, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));

            ScalerAudioInternalAudioGenSwitch(_ON, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex), UserCommonAudioGetUserLeftRightChanelSelect());

            ScalerAudioSourceInputSwitch(_DIGITAL_AUDIO, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));

            ScalerAudioDigitalVolumeMute(_OFF, UserInterfaceAudioGetVolume());

#if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)
            ScalerAudioSetInternalGenTestUserState(_ON);
#endif
        }
        else
        {
            EnumInputPort enumGenPort = GET_AUDIO_INTERNAL_GEN_INPUT_PORT(ucPathIndex);

#if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)
            ScalerAudioSetInternalGenTestUserState(_OFF);
#endif
            ScalerAudioInternalAudioGenSwitch(_OFF, enumGenPort, _AUDIO_LEFT_RIGHT_CHANNEL);

            ScalerAudioSourceInputSwitch(_DIGITAL_AUDIO, GET_AUDIO_PATH_INPUT_PORT(ucPathIndex));

            ScalerAudioInternalAudioGenPowerControl(_OFF, enumGenPort);

            SysAudioChangeAudioState(ucPathIndex, _AUDIO_STATUS_RESET_TO_PREPARING);
        }
    }
}
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio ARC Tx Output Process
// Input Value  : _DISABLE => Mute On
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxOutputProc(bit bEnable)
{
    if(bEnable == _DISABLE)
    {
        SysAudioArcTxMuteProc(_ON);
    }
    else
    {
        SysAudioArcTxMuteProc(_OFF);
    }
}

//--------------------------------------------------
// Description  : Audio ARC Tx Mute Process
// Input Value  : _ON => Mute On
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxMuteProc(bit bMute)
{
    bMute = bMute;

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    UserCommonArcTxMuteProc(bMute);
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
    ScalerHdmiArcTxMuteProc(bMute);
#endif
#endif
}

//--------------------------------------------------
// Description  : Audio ARC Tx Get OSD Info
// Input Value  : StructArcTxOsdInfo
// Output Value : StructArcTxOsdInfo
//--------------------------------------------------
void SysAudioArcTxGetOsdInfo(StructArcTxOsdInfo *pstArcOsdInfo)
{
    pstArcOsdInfo->enumArcInputSource = UserCommonAudioGetArcSource();
    pstArcOsdInfo->enumArcInputPort = UserCommonAudioGetArcInputport();
    pstArcOsdInfo->enumArcMode = UserCommonAudioGetArcMode();
    pstArcOsdInfo->enumArcMuteStatus = UserCommonAudioGetArcMuteStatus();
    pstArcOsdInfo->enumArcAudioChanelStatus = UserCommonAudioGetArcChannel();
}

//--------------------------------------------------
// Description  : Audio ARC Tx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxHandler(void)
{
    SysAudioArcTxHpdPinDetectProc();
    SysAudioArcTxJudgeHandler();
    SysAudioArcTxModeHandler();

#if(_AUDIO_EARC_SUPPORT == _ON)
    if(GET_AUDIO_ARC_TX_LINK_MODE() == _EARC_MODE)
    {
        SysAudioArcTxEarcHeartbeatStatusCheckProc();
    }
#endif
}

//--------------------------------------------------
// Description  : Audio ARC Tx Judge Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxJudgeHandler(void)
{
    CLR_AUDIO_ARC_TX_MODE_STATE_CHANGE();

    switch(GET_AUDIO_ARC_TX_MODE_STATE())
    {
        case _ARC_MODE_STATUS_POWER_OFF:

            if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) != _AUDIO_STATUS_POWER_OFF)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: Power Off --> IDLE", 0x00);
            }

            break;

        case _ARC_MODE_STATUS_IDLE:

            if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_POWER_OFF);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: IDLE --> Power Off", 0x00);
            }
            else if(GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_OSD_CHANGE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: IDLE --> OSD Change", 0x00);
            }
            else if(GET_AUDIO_ARC_TX_HPD_PIN_STATUS() == _HDMI_5V_STATUS_HIGH)
            {
                if(GET_AUDIO_ARC_TX_OSD_ARC_MODE() == _ARC_MODE)
                {
#if(_HDMI_CEC_SUPPORT == _ON)
                    if(UserCommonCecGetOsdCecEnable() == _ENABLE)
                    {
                        SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_CONNECT);

                        DebugMessageArcTx("[ARC Tx] Mode Status Change: IDLE --> ARC Connect", 0x00);
                    }
#endif
                }
#if(_AUDIO_EARC_SUPPORT == _ON)
                else if(GET_AUDIO_ARC_TX_OSD_ARC_MODE() == _EARC_MODE)
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_EARC_DISCOVERY);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: IDLE --> eARC Discovery", 0x00);
                }
#endif
            }

            break;

        case _ARC_MODE_STATUS_OSD_CHANGE:

            if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_POWER_OFF);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: OSD Change --> Power Off", 0x00);
            }
            else
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: OSD Change --> IDLE", 0x00);
            }

            break;

#if(_HDMI_CEC_SUPPORT == _ON)
        case _ARC_MODE_STATUS_ARC_DISCONNECT:

            if((GET_AUDIO_ARC_TX_HPD_PIN_STATUS() == _HDMI_5V_STATUS_LOW) || (SysAudioArcTxGetHpdToggleResetArcTxEvent() == _TRUE) ||
               (GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_START() == _FALSE))
            {
                if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF)
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_POWER_OFF);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Disconnect --> Power Off", 0x00);
                }
                else if(GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE)
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_OSD_CHANGE);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Disconnect --> OSD Change", 0x00);
                }
                else // Trigger ARC Port HPD Toggle
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Disconnect --> IDLE", 0x00);
                }
            }

            break;

        case _ARC_MODE_STATUS_ARC_CONNECT:

            if((GET_AUDIO_ARC_TX_HPD_PIN_STATUS() == _HDMI_5V_STATUS_LOW) || (SysAudioArcTxGetHpdToggleResetArcTxEvent() == _TRUE))
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Connect --> IDLE", 0x00);
            }
            else if((GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF) ||
                    (GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE) || (GET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE() == _TRUE))
            {
                if(UserCommonCecGetOsdCecEnable() == _ENABLE)
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_DISCONNECT);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Connect --> ARC Disconnect", 0x00);
                }
                else
                {
                    if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF)
                    {
                        SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_POWER_OFF);

                        DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Connect --> Power Off", 0x00);
                    }
                    else if(GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE)
                    {
                        SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_OSD_CHANGE);

                        DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Connect --> OSD Change", 0x00);
                    }
                    else // Trigger ARC Port HPD Toggle
                    {
                        SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                        DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Connect --> IDLE", 0x00);
                    }
                }
            }
            else if(GET_AUDIO_ARC_TX_LINK_MODE() == _ARC_MODE)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_WAIT_INPUT_READY);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Connect --> ARC Wait Input", 0x00);
            }

            break;

        case _ARC_MODE_STATUS_ARC_WAIT_INPUT_READY:

            if((GET_AUDIO_ARC_TX_HPD_PIN_STATUS() == _HDMI_5V_STATUS_LOW) || (SysAudioArcTxGetHpdToggleResetArcTxEvent() == _TRUE))
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Wait Input --> IDLE", 0x00);
            }
            else if((GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF) ||
                    (GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE) || (GET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE() == _TRUE))
            {
                if(UserCommonCecGetOsdCecEnable() == _ENABLE)
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_DISCONNECT);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Wait Input --> ARC Disconnect", 0x00);
                }
                else
                {
                    if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF)
                    {
                        SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_POWER_OFF);

                        DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Wait Input --> Power Off", 0x00);
                    }
                    else if(GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE)
                    {
                        SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_OSD_CHANGE);

                        DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Wait Input --> OSD Change", 0x00);
                    }
                    else // Trigger ARC Port HPD Toggle
                    {
                        SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                        DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Wait Input --> IDLE", 0x00);
                    }
                }
            }
            else if(GET_CEC_ARC_TERMINATE_RECEIVE_HAPPENED() == _TRUE)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_CONNECT);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Wait Input --> ARC Connect", 0x00);
            }
            else if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_SETTING)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_AUDIO_OUTPUT);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Wait Input --> ARC Audio Output", 0x00);
            }

            break;

        case _ARC_MODE_STATUS_ARC_AUDIO_OUTPUT:

            if((GET_AUDIO_ARC_TX_HPD_PIN_STATUS() == _HDMI_5V_STATUS_LOW) || (SysAudioArcTxGetHpdToggleResetArcTxEvent() == _TRUE))
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Audio Output --> IDLE", 0x00);
            }
            else if((GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF) ||
                    (GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE) || (GET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE() == _TRUE))
            {
                if(UserCommonCecGetOsdCecEnable() == _ENABLE)
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_DISCONNECT);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Audio Output --> ARC Disconnect", 0x00);
                }
                else
                {
                    if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF)
                    {
                        SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_POWER_OFF);

                        DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Audio Output --> Power Off", 0x00);
                    }
                    else if(GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE)
                    {
                        SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_OSD_CHANGE);

                        DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Audio Output --> OSD Change", 0x00);
                    }
                    else // Trigger ARC Port HPD Toggle
                    {
                        SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                        DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Audio Output --> IDLE", 0x00);
                    }
                }
            }
            else if(GET_CEC_ARC_TERMINATE_RECEIVE_HAPPENED() == _TRUE)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_CONNECT);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Audio Output --> ARC Connect", 0x00);
            }
            else if((GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_PREPARING) ||
                    (SysAudioArcTxCheckInputAudioInfoChange() == _TRUE))
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_WAIT_INPUT_READY);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Audio Output --> ARC Wait Input", 0x00);
            }
            else if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_PLAYBACK)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_STABLE_DETECT);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Audio Output --> ARC Stable Detect", 0x00);
            }

            break;

        case _ARC_MODE_STATUS_ARC_STABLE_DETECT:

            if((GET_AUDIO_ARC_TX_HPD_PIN_STATUS() == _HDMI_5V_STATUS_LOW) || (SysAudioArcTxGetHpdToggleResetArcTxEvent() == _TRUE))
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Stable Detect --> IDLE", 0x00);
            }
            else if(GET_CEC_ARC_TERMINATE_RECEIVE_HAPPENED() == _TRUE)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_CONNECT);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Stable Detect --> ARC Connect", 0x00);
            }
            else if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) != _AUDIO_STATUS_PLAYBACK)
            {
                if((GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF) ||
                   (GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE) || (GET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE() == _TRUE))
                {
                    if(UserCommonCecGetOsdCecEnable() == _ENABLE)
                    {
                        SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_DISCONNECT);

                        DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Stable Detect --> ARC Disconnect", 0x00);
                    }
                    else
                    {
                        if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF)
                        {
                            SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_POWER_OFF);

                            DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Stable Detect --> Power Off", 0x00);
                        }
                        else if(GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE)
                        {
                            SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_OSD_CHANGE);

                            DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Stable Detect --> OSD Change", 0x00);
                        }
                        else // Trigger ARC Port HPD Toggle
                        {
                            SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                            DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Stable Detect --> Idle", 0x00);
                        }
                    }
                }
                else
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_WAIT_INPUT_READY);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: ARC Stable Detect --> ARC Wait Input", 0x00);
                }
            }

            break;
#endif

#if(_AUDIO_EARC_SUPPORT == _ON)
        case _ARC_MODE_STATUS_EARC_DISCOVERY:

            if((GET_AUDIO_ARC_TX_HPD_PIN_STATUS() == _HDMI_5V_STATUS_LOW) || (SysAudioArcTxGetHpdToggleResetArcTxEvent() == _TRUE) ||
               (GET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE() == _TRUE))
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Discovery --> IDLE", 0x00);
            }
            else if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_POWER_OFF);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Discovery --> Power Off", 0x00);
            }
            else if(GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_OSD_CHANGE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Discovery --> OSD Change", 0x00);
            }
            else if(GET_AUDIO_ARC_TX_EARC_DISCOVERY_FINISH() == _TRUE)
            {
                if(GET_AUDIO_ARC_TX_LINK_MODE() == _EARC_MODE)
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_EARC_WAIT_INPUT_READY);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Discovery --> eARC Wait Input", 0x00);
                }
#if(_HDMI_CEC_SUPPORT == _ON)
                else if(UserCommonArcTxEarcGetDowngradeToArcPermission() == _TRUE)
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_ARC_CONNECT);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Discovery --> ARC Connect", 0x00);
                }
#endif
            }

            break;

        case _ARC_MODE_STATUS_EARC_WAIT_INPUT_READY:

            if((GET_AUDIO_ARC_TX_HPD_PIN_STATUS() == _HDMI_5V_STATUS_LOW) || (SysAudioArcTxGetHpdToggleResetArcTxEvent() == _TRUE) ||
               (GET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE() == _TRUE))
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Wait Input --> IDLE", 0x00);
            }
            else if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_POWER_OFF);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Wait Input --> Power Off", 0x00);
            }
            else if(GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_OSD_CHANGE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Wait Input --> OSD Change", 0x00);
            }
            else if(SysAudioArcTxEarcCheckDiscoveryTimeout() == _TRUE)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_EARC_DISCOVERY);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Wait Input --> eARC Discovery", 0x00);
            }
            else if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_SETTING)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_EARC_AUDIO_OUTPUT);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Wait Input --> eARC Audio Output", 0x00);
            }

            break;

        case _ARC_MODE_STATUS_EARC_AUDIO_OUTPUT:

            if((GET_AUDIO_ARC_TX_HPD_PIN_STATUS() == _HDMI_5V_STATUS_LOW) || (SysAudioArcTxGetHpdToggleResetArcTxEvent() == _TRUE) ||
               (GET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE() == _TRUE))
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Audio Output --> IDLE", 0x00);
            }
            else if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_POWER_OFF);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Audio Output --> Power Off", 0x00);
            }
            else if(GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_OSD_CHANGE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Audio Output --> OSD Change", 0x00);
            }
            else if(SysAudioArcTxEarcCheckDiscoveryTimeout() == _TRUE)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_EARC_DISCOVERY);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Audio Output --> eARC Discovery", 0x00);
            }
            else if((GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_PREPARING) ||
                    (SysAudioArcTxCheckInputAudioInfoChange() == _TRUE))
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_EARC_WAIT_INPUT_READY);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Audio Output --> eARC Wait Input", 0x00);
            }
            else if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_PLAYBACK)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_EARC_STABLE_DETECT);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Audio Output --> eARC Stable Detect", 0x00);
            }

            break;

        case _ARC_MODE_STATUS_EARC_STABLE_DETECT:

            if((GET_AUDIO_ARC_TX_HPD_PIN_STATUS() == _HDMI_5V_STATUS_LOW) || (SysAudioArcTxGetHpdToggleResetArcTxEvent() == _TRUE))
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Stable Detect --> IDLE", 0x00);
            }
            else if(SysAudioArcTxEarcCheckDiscoveryTimeout() == _TRUE)
            {
                SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_EARC_DISCOVERY);

                DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Stable Detect --> eARC Discovery", 0x00);
            }
            else if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) != _AUDIO_STATUS_PLAYBACK)
            {
                if(GET_AUDIO_PATH_AUDIO_STATE(SysAudioGetAudioPath(_AUDIO_ARC_OUT)) == _AUDIO_STATUS_POWER_OFF)
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_POWER_OFF);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Stable Detect --> Power Off", 0x00);
                }
                else if(GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE)
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_OSD_CHANGE);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Stable Detect --> OSD Change", 0x00);
                }
                else if(GET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE() == _TRUE)
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_IDLE);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Stable Detect --> IDLE(Reset by User)", 0x00);
                }
                else
                {
                    SysAudioArcTxStateChangeEvent(_ARC_MODE_STATUS_EARC_WAIT_INPUT_READY);

                    DebugMessageArcTx("[ARC Tx] Mode Status Change: eARC Stable Detect --> eARC Wait Input", 0x00);
                }
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio ARC Tx Mode Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxModeHandler(void)
{
    /*****************************************/
    /******  ARC Tx Mode State Machine  ******/
    /*****************************************/

    switch(GET_AUDIO_ARC_TX_MODE_STATE())
    {
        case _ARC_MODE_STATUS_POWER_OFF:

            if(GET_AUDIO_ARC_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                CLR_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();
                CLR_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE();
                CLR_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE();

#if(_HDMI_CEC_SUPPORT == _ON)
                CLR_CEC_ARC_INITIATE_RECEIVE_HAPPENED();
                CLR_CEC_ARC_TERMINATE_RECEIVE_HAPPENED();

                // Cancel Polling Request_ARC_INITIATE & Request_ARC_TERMINATE
                CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_START();
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_INITIATE);

                // Cancel Polling Request_ARC_TERMINATE
                CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_START();
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_TERMINATE);
#endif

#if(_AUDIO_EARC_SUPPORT == _ON)
#if(_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY == _ON)
                CLR_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_HAPPENED();
                CLR_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT();
#endif
#endif

                SET_AUDIO_ARC_TX_LINK_MODE(_EARC_ARC_OFF);
            }

            break;

        case _ARC_MODE_STATUS_IDLE:

            if(GET_AUDIO_ARC_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                SysAudioArcTxClrHpdToggleResetArcTxEvent();
                CLR_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();

                if((GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _TRUE) || (GET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE() == _TRUE))
                {
                    CLR_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE();
                    CLR_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE();

                    if(GET_AUDIO_ARC_TX_OSD_ARC_MODE() != _EARC_ARC_OFF)
                    {
                        ScalerAudioTriggerArcPortHpdToggle();

                        DebugMessageArcTx("[ARC Tx] IDLE: Trigger ARC/eARC Port HPD Toggle", 0x00);
                    }
                }

#if(_HDMI_CEC_SUPPORT == _ON)
                CLR_CEC_ARC_INITIATE_RECEIVE_HAPPENED();
                CLR_CEC_ARC_TERMINATE_RECEIVE_HAPPENED();

                // Cancel Polling Request_ARC_INITIATE & Request_ARC_TERMINATE
                CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_START();
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_INITIATE);

                // Cancel Polling Request_ARC_TERMINATE
                CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_START();
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_TERMINATE);
#endif

                if(GET_AUDIO_ARC_TX_LINK_MODE() == _ARC_MODE)
                {
                    SysAudioArcTxArcModeOutputReset();
                }
#if(_AUDIO_EARC_SUPPORT == _ON)
                else if(GET_AUDIO_ARC_TX_LINK_MODE() == _EARC_MODE)
                {
                    SysAudioArcTxEarcModeOutputReset();
                }

                CLR_AUDIO_ARC_TX_EARC_DISCOVERY_FINISH();
                CLR_AUDIO_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT();
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT);
#endif

                SET_AUDIO_ARC_TX_LINK_MODE(_EARC_ARC_OFF);
            }

            break;

        case _ARC_MODE_STATUS_OSD_CHANGE:

            if(GET_AUDIO_ARC_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                CLR_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();

#if(_AUDIO_EARC_SUPPORT == _ON)
                if(GET_AUDIO_ARC_TX_LINK_MODE() == _EARC_MODE)
                {
                    SysAudioArcTxEarcModeOutputReset();
                }
                else
#endif
                {
                    SysAudioArcTxArcModeOutputReset();
                }

                SysAudioArcTxOsdChangeProc(GET_AUDIO_ARC_TX_OSD_ARC_MODE());
            }

            break;

#if(_HDMI_CEC_SUPPORT == _ON)
        case _ARC_MODE_STATUS_ARC_DISCONNECT:

            if(GET_AUDIO_ARC_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                CLR_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();

                SysAudioArcTxArcModeOutputReset();

                CLR_CEC_ARC_INITIATE_RECEIVE_HAPPENED();
                CLR_CEC_ARC_TERMINATE_RECEIVE_HAPPENED();

                // Cancel Polling Request_ARC_INITIATE
                CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_START();
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_INITIATE);

                // Start Polling Request_ARC_TERMINATE
                UserCommonCecRequestSendCecMessage(_CEC_OPCODE_REQUEST_ARC_TERMINATION);

                SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_START();
                CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_TIMEOUT();
                CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_COUNT();

                DebugMessageArcTx("[ARC Tx] Trigger CEC Request_ARC_Terminate", 0x00);
            }

            if(SysAudioArcTxCecRequestArcTerminateProc() == _TRUE)
            {
                CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_START();
            }

            break;

        case _ARC_MODE_STATUS_ARC_CONNECT:

            if(GET_AUDIO_ARC_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                SysAudioArcTxClrHpdToggleResetArcTxEvent();
                CLR_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();

#if(_AUDIO_EARC_SUPPORT == _ON)
#if(_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY == _ON)
                CLR_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_HAPPENED();
                CLR_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT();
#endif
#endif

                CLR_CEC_ARC_INITIATE_RECEIVE_HAPPENED();
                CLR_CEC_ARC_TERMINATE_RECEIVE_HAPPENED();

                SysAudioArcTxArcModeOutputReset();

                // Other state back to ARC_CONNECT state would not set CEC command
                if(GET_AUDIO_ARC_TX_LINK_MODE() == _ARC_MODE)
                {
                    SET_AUDIO_ARC_TX_LINK_MODE(_EARC_ARC_OFF);
                }
                // Only IDLE to ARC_CONNECT state will send CEC command
                else
                {
                    // Start Polling Request_ARC_INITIATE
                    UserCommonCecRequestSendCecMessage(_CEC_OPCODE_REQUEST_ARC_INITIATION);

                    SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_START();
                    CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_TIMEOUT();
                    CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_COUNT();

                    DebugMessageArcTx("[ARC Tx] Trigger CEC Request_ARC_Initial", 0x00);
                }
            }

            if(SysAudioArcTxCecRequestArcInitiateProc() == _TRUE)
            {
                SysAudioArcTxArcModeInitial();

                SET_AUDIO_ARC_TX_LINK_MODE(_ARC_MODE);

                UserCommonCecRequestSendCecMessage(_CEC_OPCODE_REPORT_ARC_INITIATED);
            }

            break;

        case _ARC_MODE_STATUS_ARC_WAIT_INPUT_READY:

            if(GET_AUDIO_ARC_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                CLR_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();

                SysAudioArcTxArcModeOutputReset();
            }

            if(GET_CEC_ARC_INITIATE_RECEIVE_HAPPENED() == _TRUE)
            {
                CLR_CEC_ARC_INITIATE_RECEIVE_HAPPENED();

                UserCommonCecRequestSendCecMessage(_CEC_OPCODE_REPORT_ARC_INITIATED);

                DebugMessageArcTx("[ARC Tx] ARC_WAIT_INPUT: Report ARC Initiated", 0x00);
            }

            break;

        case _ARC_MODE_STATUS_ARC_AUDIO_OUTPUT:

            if(GET_AUDIO_ARC_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                CLR_AUDIO_ARC_TX_OSD_CHANNEL_NUM_CHANGE();

                // Get Audio Source Info
                ScalerAudioGetArcInterfaceInfo(&g_stAudioArcTxAudioSourceInfo);

                SysAudioArcTxAudioOutputFormatSetting(GET_AUDIO_ARC_TX_OSD_CHANNEL_NUM(), g_stAudioArcTxAudioSourceInfo);
            }

            if(SysAudioArcTxStreamHandler() == _TRUE)
            {
                if(GET_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMER_ACTIVE() == _TRUE)
                {
                    if(GET_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT() == _TRUE)
                    {
                        DebugMessageArcTx("[ARC Tx] Driving Change Timeout", 0x00);

                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT);
                        CLR_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMER_ACTIVE();
                        CLR_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT();

                        SET_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();
                    }
                }
                else
                {
                    SET_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();
                }
            }

            break;

        case _ARC_MODE_STATUS_ARC_STABLE_DETECT:

            if(SysAudioArcTxStableDetect() == _UNSTABLE)
            {
                CLR_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();
            }

            break;
#endif

#if(_AUDIO_EARC_SUPPORT == _ON)
        case _ARC_MODE_STATUS_EARC_DISCOVERY:

            if(GET_AUDIO_ARC_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                SysAudioArcTxClrHpdToggleResetArcTxEvent();
                CLR_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();

                ScalerTimerActiveTimerEvent(_AUDIO_ARC_TX_WAIT_EARC_DISCOVERY_FINISH_TIME, _SCALER_TIMER_EVENT_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT);

                if(GET_AUDIO_ARC_TX_EARC_DISCOVERY_FINISH() == _TRUE)
                {
                    SysAudioArcTxEarcModeOutputReset();

#if(_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY == _ON)
                    // Only retry eARC discovery when _EARC_WAIT_INPUT_READY, _EARC_AUDIO_OUTPUT, _EARC_STABLE_DETECT jump back to _EARC_DISCOVERY state
                    SET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_HAPPENED();
                    SET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT(GET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT() + 1);

                    ScalerAudioTriggerArcPortHpdToggle();

                    DebugMessageArcTx("[ARC Tx] eARC Mode -> Timeout, Retry Discovery", GET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT());
#endif

                    // Trigger JudgeHandler to jump to ARC_CONNECT state if not retry
                    SET_AUDIO_ARC_TX_LINK_MODE(_EARC_ARC_OFF);
                }
                else
                {
                    DebugMessageArcTx("[ARC Tx] Check eARC Discovery Result", 0x00);
                }
            }

            SysAudioArcTxEarcDiscoveryProc();

            break;

        case _ARC_MODE_STATUS_EARC_WAIT_INPUT_READY:

            if(GET_AUDIO_ARC_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                CLR_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();

                SysAudioArcTxEarcModeOutputReset();
            }

            break;

        case _ARC_MODE_STATUS_EARC_AUDIO_OUTPUT:

            if(GET_AUDIO_ARC_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                CLR_AUDIO_ARC_TX_OSD_CHANNEL_NUM_CHANGE();

                // Get Audio Source Info
                ScalerAudioGetArcInterfaceInfo(&g_stAudioArcTxAudioSourceInfo);

                SysAudioArcTxAudioOutputFormatSetting(GET_AUDIO_ARC_TX_OSD_CHANNEL_NUM(), g_stAudioArcTxAudioSourceInfo);
            }

            if(SysAudioArcTxEarcStreamHandler() == _TRUE)
            {
                if(GET_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMER_ACTIVE() == _TRUE)
                {
                    if(GET_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT() == _TRUE)
                    {
                        DebugMessageArcTx("[ARC Tx] Driving Change Timeout", 0x00);

                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT);
                        CLR_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMER_ACTIVE();
                        CLR_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT();

                        SET_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();
                    }
                }
                else
                {
                    SET_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();
                }
            }

            break;

        case _ARC_MODE_STATUS_EARC_STABLE_DETECT:

            SysAudioArcTxEarcCheckChStatusMuteFlagChangeProc();

            if(SysAudioArcTxStableDetect() == _UNSTABLE)
            {
                CLR_AUDIO_ARC_TX_AUDIO_OUTPUT_READY();
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Audio ARC Tx Mode Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxStateChangeEvent(EnumArcTxModeStatus enumModeState)
{
#if(_AUDIO_EARC_SUPPORT == _ON)
    if((GET_AUDIO_ARC_TX_MODE_STATE() == _ARC_MODE_STATUS_ARC_STABLE_DETECT) || (GET_AUDIO_ARC_TX_MODE_STATE() == _ARC_MODE_STATUS_EARC_STABLE_DETECT))
#else
    if(GET_AUDIO_ARC_TX_MODE_STATE() == _ARC_MODE_STATUS_ARC_STABLE_DETECT)
#endif
    {
        // For eARC standard, eARC Tx shall stop driving for at least TeARC_FORMAT_CHG prior to initiating an new audio stream
        ScalerTimerActiveTimerEvent(_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIME, _SCALER_TIMER_EVENT_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMEOUT);
        SET_AUDIO_ARC_TX_DRIVING_CHANGE_KEEPOUT_TIMER_ACTIVE();
    }

    SET_AUDIO_ARC_TX_MODE_STATE(enumModeState);
    SET_AUDIO_ARC_TX_MODE_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Audio ARC Tx HPD Pin Detect Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxHpdPinDetectProc(void)
{
#if(_HDMI20_SUPPORT == _ON)
    EnumUserHdmi5vStatus enumHpd5VPinStatus = _HDMI_5V_STATUS_LOW;
    EnumInputPort enumArcPort = ScalerAudioGetArcDxPort();

    CLR_AUDIO_ARC_TX_HPD_PIN_STATUS_CHANGE();

    enumHpd5VPinStatus = ScalerTmdsMacRxGetHpd5vPinHighFlag(enumArcPort);

    if(GET_AUDIO_ARC_TX_HPD_PIN_STATUS() != enumHpd5VPinStatus)
    {
        DebugMessageArcTx("[ARC Tx] HPD Change", enumHpd5VPinStatus);

        SET_AUDIO_ARC_TX_HPD_PIN_STATUS(enumHpd5VPinStatus);

        SET_AUDIO_ARC_TX_HPD_PIN_STATUS_CHANGE();
    }
#endif
}

//--------------------------------------------------
// Description  : Audio Arc Tx ARC Mode Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxArcModeInitial(void)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    UserCommonArcTxArcModeInitial();
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
    ScalerHdmiArcTxArcModeInitial();
#endif
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_SPDIF_STRONG_DRIVING_PAD)
    // TODO: ADD ARC SPDIF Strong Driving Control
    // TBD
#endif
}

//--------------------------------------------------
// Description  : Audio ARC Tx ARC Mode Output Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxArcModeOutputReset(void)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    UserCommonArcTxArcModeOutputReset();
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
    ScalerHdmiArcTxArcModeOutputReset();
#endif
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_SPDIF_STRONG_DRIVING_PAD)
    // TODO: ADD ARC SPDIF Strong Driving Control
    // TBD
#endif
}

//--------------------------------------------------
// Description  : Audio ARC Tx Audio Output Format Setting
// Input Value  : EnumArcAudioChanelStatus, StructAudioInterfaceInfoForArc
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
void SysAudioArcTxAudioOutputFormatSetting(EnumArcAudioChanelStatus enumArcOsdChannelNum, StructAudioInterfaceInfoForArc stArcAudioSourceInfo)
{
    enumArcOsdChannelNum = enumArcOsdChannelNum;
    stArcAudioSourceInfo = stArcAudioSourceInfo;

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    UserCommonArcTxAudioOutputFormatSetting(enumArcOsdChannelNum, stArcAudioSourceInfo);
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
    ScalerHdmiArcTxAudioOutputFormatSetting(enumArcOsdChannelNum, stArcAudioSourceInfo);
#endif
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_SPDIF_STRONG_DRIVING_PAD)
    // TODO: ADD ARC SPDIF Strong Driving Control
    // TBD
#endif
}

//--------------------------------------------------
// Description  : Audio ARC Tx Stream Handler
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioArcTxStreamHandler(void)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    return UserCommonArcTxStreamHandler();
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
    return ScalerHdmiArcTxStreamHandler();
#endif
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_SPDIF_STRONG_DRIVING_PAD)
    // TODO: ADD ARC SPDIF Strong Driving Control
    // TBD
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio ARC Tx Stable Detect
// Input Value  : None
// Output Value : _STABLE/_UNSTABLE
//--------------------------------------------------
bit SysAudioArcTxStableDetect(void)
{
    if(GET_AUDIO_ARC_TX_RETRY_ARC_EARC_BY_HPD_TOOGLE() == _TRUE)
    {
        DebugMessageArcTx("[ARC Tx] HPD Toggle Retry ARC/eARC by User", 0);

        return _UNSTABLE;
    }

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    return UserCommonArcTxStableDetect();
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
    return ScalerHdmiArcTxStableDetect();
#endif
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_SPDIF_STRONG_DRIVING_PAD)
    // TODO: ADD ARC SPDIF Strong Driving Control
    // TBD
#endif

    return _UNSTABLE;
}

//----------------------------------------
// Description  : Audio ARC Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxInitial(void)
{
#if(_HDMI20_SUPPORT == _ON)
    EnumUserHdmi5vStatus enumHpd5VPinStatus = _HDMI_5V_STATUS_LOW;

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_AUDIO_EARC_SUPPORT == _ON)
    EnumUserHdmi5vStatus enumHpdPinDetectResult = _HDMI_5V_STATUS_LOW;
#endif
#endif

    EnumInputPort enumArcPort = ScalerAudioGetArcDxPort();

    enumHpd5VPinStatus = ScalerTmdsMacRxGetHpd5vPinHighFlag(enumArcPort);

    SET_AUDIO_ARC_TX_HPD_PIN_STATUS(enumHpd5VPinStatus);
#endif

    SysAudioArcTxGetOsdInfo(&g_stAudioArcTxOsdInfo);

    CLR_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE();
    CLR_AUDIO_ARC_TX_OSD_CHANNEL_NUM_CHANGE();

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    UserCommonArcTxInitial(GET_AUDIO_ARC_TX_OSD_ARC_MODE());
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
    ScalerHdmiArcTxPowerOnInitial(GET_AUDIO_ARC_TX_OSD_ARC_MODE());
#endif

#if((_HDMI20_SUPPORT == _ON) && (_AUDIO_EARC_SUPPORT == _ON))
    enumHpdPinDetectResult = ScalerTmdsMacRxHpdDetect(enumArcPort);

    if(enumHpdPinDetectResult == _HDMI_5V_STATUS_LOW)
    {
        ScalerTmdsMacRxEnableHpdDetectRisingIrq(enumArcPort);

        DebugMessageArcTx("[ARC Tx] Enable HPD Rising IRQ", 0x00);
    }
    else
    {
        ScalerTmdsMacRxEnableHpdDetectFallingIrq(enumArcPort);

        DebugMessageArcTx("[ARC Tx] Enable HPD Falling IRQ", 0x00);
    }

    // Initial eARC Rx CDS Info
    memset(&g_stAudioEarcRxCdsInfo, 0, sizeof(StructArcTxEarcCdsInfo));
#endif
#endif

    DebugMessageArcTx("[ARC Tx] Audio ARC Tx Initial", 0x00);
}

//----------------------------------------
// Description  : Audio ARC Tx Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxDisable(void)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    UserCommonArcTxDisable();
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
    ScalerHdmiArcTxDisable();
#endif

#if((_HDMI20_SUPPORT == _ON) && (_AUDIO_EARC_SUPPORT == _ON))
    // TODO: Change to HDMI Mac IP
    ScalerTmdsMacRxDisableHpdDetectIrq(ScalerAudioGetArcDxPort());
#endif
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_SPDIF_STRONG_DRIVING_PAD)
    // TODO: ADD ARC SPDIF Strong Driving Control
    // TBD
#endif

    DebugMessageArcTx("[ARC Tx] Audio ARC Tx Disable", 0x00);
}

//----------------------------------------
// Description  : Audio ARC Tx Output Change
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit SysAudioArcTxOutputChange(void)
{
    EnumAudioArcMode enumOsdArcMode = UserCommonAudioGetArcMode();

#if(_AUDIO_EARC_SUPPORT == _ON)
    EnumArcAudioChanelStatus enumOsdArcChannelNum = UserCommonAudioGetArcChannel();
#endif

    // Need to wait for kernel to respond current change, then just can update new OSD ARC mode
    if((enumOsdArcMode != GET_AUDIO_ARC_TX_OSD_ARC_MODE()) && (GET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE() == _FALSE))
    {
        DebugMessageArcTx("[ARC Tx] OSD ARC Mode Change", enumOsdArcMode);

        SET_AUDIO_ARC_TX_OSD_ARC_MODE(enumOsdArcMode);
        SET_AUDIO_ARC_TX_OSD_ARC_MODE_CHANGE();

        return _TRUE;
    }

#if(_AUDIO_EARC_SUPPORT == _ON)
    if(enumOsdArcChannelNum != GET_AUDIO_ARC_TX_OSD_CHANNEL_NUM())
    {
        DebugMessageArcTx("[ARC Tx] OSD ARC Channel Num Change", enumOsdArcChannelNum);

        SET_AUDIO_ARC_TX_OSD_CHANNEL_NUM(enumOsdArcChannelNum);

        // ARC only support 2ch, ignore OSD channel number change
        if(GET_AUDIO_ARC_TX_LINK_MODE() == _EARC_MODE)
        {
            SET_AUDIO_ARC_TX_OSD_CHANNEL_NUM_CHANGE();

            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//----------------------------------------
// Description  : Audio ARC Tx Check Input Audio Info Change
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit SysAudioArcTxCheckInputAudioInfoChange(void)
{
    StructAudioInterfaceInfoForArc stInputAudioInfo;

    memset(&stInputAudioInfo, 0x00, sizeof(StructAudioInterfaceInfoForArc));

    // Get Current Audio Source Info
    ScalerAudioGetArcInterfaceInfo(&stInputAudioInfo);

    if(memcmp(&g_stAudioArcTxAudioSourceInfo, &stInputAudioInfo, sizeof(StructAudioInterfaceInfoForArc)) != _FALSE)
    {
        DebugMessageArcTx("[ARC Tx] Input Audio Info Change", 0x00);

        return _TRUE;
    }

    return _FALSE;
}

//----------------------------------------
// Description  : Audio ARC Tx Get HPD Toggle Reset ARC Tx Event
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
BYTE SysAudioArcTxGetHpdToggleResetArcTxEvent(void)
{
#if(_HDMI_SUPPORT == _ON)
    return GET_TMDS_MAC_RX_HPD_TOGGLE_RESET_ARC_TX_EVENT();
#endif

    return _FALSE;
}

//----------------------------------------
// Description  : Audio ARC Tx Clear HPD Toggle Reset ARC Tx Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxClrHpdToggleResetArcTxEvent(void)
{
#if(_HDMI_SUPPORT == _ON)
    CLR_TMDS_MAC_RX_HPD_TOGGLE_RESET_ARC_TX_EVENT();
#endif
}

//--------------------------------------------------
// Description  : Audio ARC Tx Cable Unplg Reset Process
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxCableUnplugResetProc(EnumInputPort enumInputPort)
{
    if(ScalerAudioGetArcDxPort() == enumInputPort)
    {
#if(_AUDIO_EARC_SUPPORT == _ON)
#if(_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY == _ON)
        CLR_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_HAPPENED();
        CLR_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT();
#endif
#endif
    }
}

//--------------------------------------------------
// Description  : Audio ARC Tx OSD Change Process(eARC/ARC/OFF)
// Input Value  : enumArcMode
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxOsdChangeProc(EnumAudioArcMode enumArcMode)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    UserCommonArcTxOsdChangeProc(enumArcMode);
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
    ScalerHdmiArcTxOsdChangeProc(enumArcMode);
#endif
#else
    enumArcMode = enumArcMode;
#endif
}

#if(_HDMI_CEC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Arc Tx CEC Request ARC Initiate Proc
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioArcTxCecRequestArcInitiateProc(void)
{
    if(GET_CEC_ARC_INITIATE_RECEIVE_HAPPENED() == _TRUE)
    {
        CLR_CEC_ARC_INITIATE_RECEIVE_HAPPENED();
        CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_START();
        CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_TIMEOUT();
        CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_COUNT();
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_INITIATE);

        DebugMessageArcTx("[ARC Tx] Receive CEC ARC_Initiate", 0x00);

        return _TRUE;
    }
    else if((GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_START() == _TRUE) && (GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_TIMEOUT() == _TRUE))
    {
        CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_TIMEOUT();
        SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_COUNT(GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_COUNT() + 1);

        if(GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_COUNT() < _AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_MAX_COUNT)
        {
            UserCommonCecRequestSendCecMessage(_CEC_OPCODE_REQUEST_ARC_INITIATION);

            DebugMessageArcTx("[ARC Tx] CEC Request_ARC_Initiate Retry", GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_COUNT());
        }
        else
        {
            CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_START();
            CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_TIMEOUT();
            CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_COUNT();
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_INITIATE);

            DebugMessageArcTx("[ARC Tx] CEC Request_ARC_Initiate Timeout", 0x00);
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio Arc Tx CEC Request ARC Terminate Proc
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioArcTxCecRequestArcTerminateProc(void)
{
    if(GET_CEC_ARC_TERMINATE_RECEIVE_HAPPENED() == _TRUE)
    {
        DebugMessageArcTx("[ARC Tx] Receive CEC ARC_Terminate", 0x00);

        CLR_CEC_ARC_TERMINATE_RECEIVE_HAPPENED();
        CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_START();
        CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_TIMEOUT();
        CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_COUNT();
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_TERMINATE);

        UserCommonCecRequestSendCecMessage(_CEC_OPCODE_REPORT_ARC_TERMINATED);

        return _TRUE;
    }
    else if((GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_START() == _TRUE) && (GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_TIMEOUT() == _TRUE))
    {
        CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_TIMEOUT();
        SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_COUNT(GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_COUNT() + 1);

        if(GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_COUNT() < _AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_MAX_COUNT)
        {
            UserCommonCecRequestSendCecMessage(_CEC_OPCODE_REQUEST_ARC_TERMINATION);

            DebugMessageArcTx("[ARC Tx] CEC Request_ARC_Terminate Retry", GET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_COUNT());
        }
        else
        {
            CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_START();
            CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_TIMEOUT();
            CLR_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_COUNT();
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_TERMINATE);

            DebugMessageArcTx("[ARC Tx] CEC Request_ARC_Terminate Timeout", 0x00);

            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio Arc Tx CEC Set Request ARC Initiate Retry Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxCecSetRequestArcInitiateRetryTimeout(void)
{
    SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_TIMEOUT();
}

//--------------------------------------------------
// Description  : Audio Arc Tx CEC Active Request ARC Initiate Retry Timer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxCecActiveRequestArcInitiateRetryTimer(void)
{
    ScalerTimerActiveTimerEvent(_AUDIO_ARC_TX_CEC_REQUEST_ARC_INITIATE_RETRY_DURATION, _SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_INITIATE);
}

//--------------------------------------------------
// Description  : Audio Arc Tx CEC Set Request ARC Terminate Retry Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxCecSetRequestArcTerminateRetryTimeout(void)
{
    SET_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_TIMEOUT();
}

//--------------------------------------------------
// Description  : Audio Arc Tx CEC Active Request ARC Terminate Retry Timer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxCecActiveRequestArcTerminateRetryTimer(void)
{
    ScalerTimerActiveTimerEvent(_AUDIO_ARC_TX_CEC_REQUEST_ARC_TERMINATE_RETRY_DURATION, _SYSTEM_TIMER_EVENT_CEC_RETRY_REQUEST_ARC_TERMINATE);
}
#endif // End of #if(_HDMI_CEC_SUPPORT == _ON)

#if(_AUDIO_EARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio eARC Tx Output Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxEarcModeOutputReset(void)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    UserCommonArcTxEarcModeOutputReset();
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    ScalerHdmiArcTxEarcModeOutputReset();
#endif
#endif
}

//--------------------------------------------------
// Description  : Audio eARC Tx Discovery Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxEarcDiscoveryProc(void)
{
    if(GET_AUDIO_ARC_TX_EARC_DISCOVERY_FINISH() == _FALSE)
    {
        if(SysAudioArcTxEarcCheckDiscoveryPass() == _TRUE)
        {
            SET_AUDIO_ARC_TX_LINK_MODE(_EARC_MODE);

            SET_AUDIO_ARC_TX_EARC_DISCOVERY_FINISH();

            CLR_AUDIO_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT();
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT);

#if(_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY == _ON)
            CLR_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_HAPPENED();
            CLR_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT();
#endif

            DebugMessageArcTx("[ARC Tx] eARC Discovery Pass", 0x00);
        }
        else if(SysAudioArcTxEarcCheckDiscoveryTimeout() == _TRUE)
        {
            SET_AUDIO_ARC_TX_LINK_MODE(_EARC_ARC_OFF);

            SET_AUDIO_ARC_TX_EARC_DISCOVERY_FINISH();

            DebugMessageArcTx("[ARC Tx] eARC Discovery Timeout", 0x00);

            CLR_AUDIO_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT();
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT);

#if(_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY == _ON)
            if((GET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_HAPPENED() == _TRUE) &&
               (GET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT() < _AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_MAX_COUNT))
            {
                SET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT(GET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT() + 1);

                ScalerAudioTriggerArcPortHpdToggle();

                DebugMessageArcTx("[ARC Tx] Retry Discovery", GET_AUDIO_ARC_TX_EARC_PASS_TO_DISC_TIMEOUT_RETRY_COUNT());
            }
#endif
        }
        else if((UserCommonArcTxEarcGetInitiatePermission() == _TRUE) &&
                (GET_AUDIO_ARC_TX_FORCE_EARC_DISC_INIT_BY_HPD_TOGGLE_TIMEOUT() == _TRUE))
        {
            ScalerAudioTriggerArcPortHpdToggle();

            DebugMessageArcTx("[ARC Tx] eARC discovery is not initiated, trigger Rx HPD Toggle", 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Audio eARC Tx Check Discovery Pass
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit SysAudioArcTxEarcCheckDiscoveryPass(void)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    return UserCommonArcTxEarcCheckDiscoveryPass();
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    return ScalerHdmiArcTxEarcCheckDiscoveryPass();
#endif
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio eARC Tx Check Discovery Timeout
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit SysAudioArcTxEarcCheckDiscoveryTimeout(void)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    return UserCommonArcTxEarcCheckDiscoveryTimeout();
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    return ScalerHdmiArcTxEarcCheckDiscoveryTimeout();
#endif
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio eARC Tx Stream Handler
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit SysAudioArcTxEarcStreamHandler(void)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    return UserCommonArcTxEarcStreamHandler();
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    return ScalerHdmiArcTxEarcStreamHandler();
#endif
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio eARC Tx Hearbeat Status Check Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxEarcHeartbeatStatusCheckProc(void)
{
    BYTE ucAudioLatency = 0x00;

    if(GET_AUDIO_ARC_TX_LINK_MODE() == _EARC_MODE)
    {
        if(SysAudioArcTxEarcCheckAudioLatencyUpdate(&ucAudioLatency) == _TRUE)
        {
            DebugMessageArcTx("[ARC Tx] Rx Audio Latency Change", ucAudioLatency);

            // TODO: get video latency to calcuate request audio latency
            if(SysAudioArcTxEarcSetRequestAudioLatency(ucAudioLatency) == _FALSE)
            {
                DebugMessageArcTx("[ARC Tx] Set Request Audio Latency Fail", 0x00);
            }
        }

        if(SysAudioArcTxEarcCheckCdsUpdate() == _TRUE)
        {
            BYTE pucEarcRxCdsTable[256];

            memset(pucEarcRxCdsTable, 0, sizeof(pucEarcRxCdsTable));

            DebugMessageArcTx("[ARC Tx] Rx CDS Update", 0x00);

            if(SysAudioArcTxEarcCdsReload(pucEarcRxCdsTable) == _TRUE)
            {
                memset(&g_stAudioEarcRxCdsInfo, 0, sizeof(StructArcTxEarcCdsInfo));

                if(SysAudioArcTxEarcCdsParser(pucEarcRxCdsTable, &g_stAudioEarcRxCdsInfo) == _TRUE)
                {
                    // Notify user to check EDID audio block and decide whether change EDID or not
                    UserCommonArcTxEarcCdsParseDoneNotify();

                    DebugMessageArcTx("[ARC Tx] Rx CDS Parse Done", 0x00);
                }
            }
            else
            {
                DebugMessageArcTx("[ARC Tx] Rx CDS Reload Fail!!!", 0x00);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Audio eARC Tx Check Audio Latency Update
// Input Value  : pucAudioLatency
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit SysAudioArcTxEarcCheckAudioLatencyUpdate(BYTE *pucAudioLatency)
{
    pucAudioLatency = pucAudioLatency;

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    return UserCommonArcTxEarcCheckAudioLatencyUpdate(pucAudioLatency);
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    return ScalerHdmiArcTxEarcCheckAudioLatencyUpdate(pucAudioLatency);
#endif
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio eARC Tx Set Request Audio Latency
// Input Value  : ucAudioLatency
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit SysAudioArcTxEarcSetRequestAudioLatency(BYTE ucAudioLatency)
{
    ucAudioLatency = ucAudioLatency;

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    return UserCommonArcTxEarcSetRequestAudioLatency(ucAudioLatency);
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    return ScalerHdmiArcTxEarcSetRequestAudioLatency(ucAudioLatency);
#endif
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio eARC Tx Check CDS Update
// Input Value  : None
// Output Value : _FALSE / _TRUE
//--------------------------------------------------
bit SysAudioArcTxEarcCheckCdsUpdate(void)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    return UserCommonArcTxEarcCheckCdsUpdate();
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    return ScalerHdmiArcTxEarcCheckCdsUpdate();
#endif
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio eARC Tx CDS Reload
// Input Value  : pucEarcRxCdsTable
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioArcTxEarcCdsReload(BYTE *pucEarcRxCdsTable)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    return UserCommonArcTxEarcCdsReload(pucEarcRxCdsTable);
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    return ScalerHdmiArcTxEarcCdsReload(pucEarcRxCdsTable);
#endif
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio eARC Tx Capability Data Structure Parser
// Input Value  : pucEarcRxCdsTable, pstEarcRxCdsInfo
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioArcTxEarcCdsParser(BYTE *pucEarcRxCdsTable, StructArcTxEarcCdsInfo *pstEarcRxCdsInfo)
{
    WORD usCdsOffset = 0;
    BYTE ucCdsData = 0;
    BYTE ucBlockId = 0;
    BYTE ucBlockLength = 0;
    BYTE ucBlockStart = 0;
    BYTE ucBlockEnd = 0;
    BYTE ucCheckEndMarker = 0;
    BYTE ucCtaDbStart = 0;
    BYTE ucCtaDbType = 0;
    BYTE ucCtaDbSize = 0;
    BYTE ucCtaDbEnd = 0;
    BYTE ucCtaSldDbStart = 0;
    BYTE ucCtaSldDbEnd = 0;
    BYTE ucDbOffset = 0;
    BYTE pucCtaSad[3] = {0};
    BYTE ucCtaExtendTag = 0;
    BYTE ucCtaExtSlDbCoordFlag = 0;
    BYTE ucDbLength = 0;

    for(usCdsOffset = 0; usCdsOffset < 256; usCdsOffset++)
    {
        ucCdsData = pucEarcRxCdsTable[usCdsOffset];

        if(usCdsOffset == 0x00)
        {
            DebugMessageArcTx("[ARC Tx] CDS Version = ", ucCdsData);

            continue;
        }

        if(usCdsOffset == (ucBlockEnd + 1))
        {
            ucBlockId = ucCdsData;

            if(ucBlockId == 0x00)
            {
                ucCheckEndMarker = _TRUE;
            }
            else
            {
                ucCheckEndMarker = _FALSE;
            }

            continue;
        }

        if(ucCheckEndMarker == _TRUE)
        {
            if(ucCdsData != 0x00)
            {
                DebugMessageArcTx("[ARC Tx] End Marker is not zero!!! offset", usCdsOffset);
                DebugMessageArcTx("[ARC Tx] End Marker is not zero!!! data", ucCdsData);

                return _FALSE;
            }

            continue;
        }

        if(usCdsOffset == (ucBlockEnd + 2))
        {
            ucBlockLength = ucCdsData;
            ucBlockStart = usCdsOffset - 1;
            ucBlockEnd = usCdsOffset + ucBlockLength;

            if(ucBlockId == 0x01)
            {
                ucCtaDbStart = usCdsOffset + 1;
            }
            else if(ucBlockId == 0x02)
            {
                ucCtaSldDbStart = usCdsOffset + 1;

                pstEarcRxCdsInfo->ucEarcCdsSpkLdbOffset = ucCtaSldDbStart;
            }

            continue;
        }

        if((usCdsOffset >= ucBlockStart) && (usCdsOffset <= ucBlockEnd))
        {
            // CTA Descriptor Data Block
            if(ucBlockId == 0x01)
            {
                if(usCdsOffset == ucCtaDbStart)
                {
                    ucCtaDbType = (ucCdsData & 0xE0) >> 5;
                    ucCtaDbSize = (ucCdsData & 0x1F);
                    ucCtaDbEnd = ucCtaDbStart + ucCtaDbSize;
                    ucDbOffset = 0;

                    switch(ucCtaDbType)
                    {
                        case 1:
                            pstEarcRxCdsInfo->ucEarcCdsAdbOffset = usCdsOffset;
                            DebugMessageArcTx("[ARC Tx] CTA Audio Data Block", 0);
                            break;
                        case 2:
                            DebugMessageArcTx("[ARC Tx] CTA Video Data Block", 0);
                            break;
                        case 3:
                            DebugMessageArcTx("[ARC Tx] CTA Vendor Specifuc Data Block", 0);
                            break;
                        case 4:
                            DebugMessageArcTx("[ARC Tx] CTA Speaker Allocation Data Block", 0);
                            break;
                        case 5:
                            DebugMessageArcTx("[ARC Tx] CTA VESA DTC Data Block", 0);
                            break;
                        case 7:
                            DebugMessageArcTx("[ARC Tx] CTA Use Extended Tag Data Block", 0);
                            break;
                        default:
                            DebugMessageArcTx("[ARC Tx] CTA Reserved Data Block", 0);
                            break;
                    }

                    if((ucCtaDbType != 1) && (ucCtaDbType != 4) && (ucCtaDbType != 7))
                    {
                        DebugMessageArcTx("[ARC Tx] This CTA Data Block should not exist in CDS", 0);

                        continue;
                    }
                    else if(ucCtaDbType == 4)
                    {
                        if(ucCtaDbSize == 3)
                        {
                            pstEarcRxCdsInfo->ucEarcCdsSpkAdbOffset = usCdsOffset;
                        }
                        else
                        {
                            DebugMessageArcTx("[ARC Tx] CTA Speaker Allocation Descriptor Size should = 0x3!!!", 0);

                            continue;
                        }
                    }

                    continue;
                }

                switch(ucCtaDbType)
                {
                    case 1:

                        pucCtaSad[ucDbOffset % 3] = ucCdsData;

                        if(ucDbOffset % 3 == 2)
                        {
                            DebugMessageArcTx("[ARC Tx] ------ CTA Short Audio Descriptor Index: ------", (ucDbOffset / 3) + 1);
                            SysAudioArcTxEarcCdsAudioDataBlockParser(pucCtaSad);
                        }

                        ucDbOffset++;
                        break;

                    case 4:

                        if(ucDbOffset == 0)
                        {
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location FL/FR:", (ucCdsData & _BIT0) >> 0);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location LFE:", (ucCdsData & _BIT1) >> 1);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location FC:", (ucCdsData & _BIT2) >> 2);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location RL/RR:", (ucCdsData & _BIT3) >> 3);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location BC:", (ucCdsData & _BIT4) >> 4);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location FLC/FRC:", (ucCdsData & _BIT5) >> 5);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location RLC/RRC:", (ucCdsData & _BIT6) >> 6);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location FLW/FRW:", (ucCdsData & _BIT7) >> 7);
                        }
                        else if(ucDbOffset == 1)
                        {
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location TpFL/TpFH:", (ucCdsData & _BIT0) >> 0);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location TpC:", (ucCdsData & _BIT1) >> 1);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location TpFC:", (ucCdsData & _BIT2) >> 2);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location LS/RS:", (ucCdsData & _BIT3) >> 3);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location LFE2:", (ucCdsData & _BIT4) >> 4);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location TpBC:", (ucCdsData & _BIT5) >> 5);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location SiL/SiR:", (ucCdsData & _BIT6) >> 6);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location TpSiL/TpSiR:", (ucCdsData & _BIT7) >> 7);
                        }
                        else if(ucDbOffset == 2)
                        {
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location TpBL/TpBR:", (ucCdsData & _BIT0) >> 0);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location BtFC:", (ucCdsData & _BIT1) >> 1);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location BtFL/BtFR:", (ucCdsData & _BIT2) >> 2);
                            DebugMessageArcTx("[ARC Tx] Support Speaker Location TpLS/TpRS:", (ucCdsData & _BIT3) >> 3);
                        }

                        ucDbOffset++;
                        break;

                    case 7:

                        if(ucDbOffset == 0)
                        {
                            ucCtaExtendTag = ucCdsData;

                            switch(ucCtaExtendTag)
                            {
                                case 0x00:
                                    DebugMessageArcTx("[ARC Tx] Video Capability Data Block", 0);
                                    break;
                                case 0x01:
                                    DebugMessageArcTx("[ARC Tx] Vendor Specific Video Data Block", 0);
                                    break;
                                case 0x02:
                                    DebugMessageArcTx("[ARC Tx] VESA Display Device Data Block", 0);
                                    break;
                                case 0x03:
                                    DebugMessageArcTx("[ARC Tx] VESA Video Timing Block Extension", 0);
                                    break;
                                case 0x04:
                                    DebugMessageArcTx("[ARC Tx] Reserved for HDMI Video Data Block", 0);
                                    break;
                                case 0x05:
                                    DebugMessageArcTx("[ARC Tx] Colorimetry Data Block", 0);
                                    break;
                                case 0x06:
                                    DebugMessageArcTx("[ARC Tx] HDR Static Metadata Data Block", 0);
                                    break;
                                case 0x07:
                                    DebugMessageArcTx("[ARC Tx] HDR Dynamic Metadata Data Block", 0);
                                    break;
                                case 0x08:
                                case 0x09:
                                case 0x0A:
                                case 0x0B:
                                case 0x0C:
                                    DebugMessageArcTx("[ARC Tx] Reserved for Video Related Block", 0);
                                    break;
                                case 0x0D:
                                    DebugMessageArcTx("[ARC Tx] Video Format Preference Data Block", 0);
                                    break;
                                case 0x0E:
                                    DebugMessageArcTx("[ARC Tx] YCbCr 4:2:0 Vudei Data Block", 0);
                                    break;
                                case 0x0F:
                                    DebugMessageArcTx("[ARC Tx] YCbCr 4:2:0 Capability Map Data Block", 0);
                                    break;
                                case 0x10:
                                    DebugMessageArcTx("[ARC Tx] Reserved for CTA Miscellaneous Audio Fields", 0);
                                    break;
                                case 0x11:
                                    DebugMessageArcTx("[ARC Tx] Vendor Specific Audio Data Block", 0);
                                    break;
                                case 0x12:
                                    DebugMessageArcTx("[ARC Tx] Reserved for HDMI Audio Data Block", 0);
                                    break;
                                case 0x13:
                                    DebugMessageArcTx("[ARC Tx] Room Configuration Data Block", 0);
                                    break;
                                case 0x14:
                                    DebugMessageArcTx("[ARC Tx] Speaker Location Data Block", 0);
                                    break;
                                case 0x15:
                                case 0x16:
                                case 0x17:
                                case 0x18:
                                case 0x19:
                                case 0x1A:
                                case 0x1B:
                                case 0x1C:
                                case 0x1D:
                                case 0x1E:
                                case 0x1F:
                                    DebugMessageArcTx("[ARC Tx] Reserved for Audio Related Block", 0);
                                    break;
                                case 0x20:
                                    DebugMessageArcTx("[ARC Tx] InfoFrame Data Block", 0);
                                    break;
                                default:
                                    DebugMessageArcTx("[ARC Tx] Reserved Tag of Data Block", 0);
                                    break;
                            }

                            if((ucCtaExtendTag != 0x11) && (ucCtaExtendTag != 0x13) && (ucCtaExtendTag != 0x14))
                            {
                                DebugMessageArcTx("[ARC Tx] This CTA Extended Data Block should not exist in CDS", 0);
                            }
                        }

                        // Vendor Specific Audio Data Block
                        if(ucCtaExtendTag == 0x11)
                        {
                            if(ucDbOffset == 1)
                            {
                                DebugMessageArcTx("[ARC Tx] IEEE OUI 3rd two hex digits =", ucCdsData);
                            }
                            else if(ucDbOffset == 2)
                            {
                                DebugMessageArcTx("[ARC Tx] IEEE OUI 2nd two hex digits =", ucCdsData);
                            }
                            else if(ucDbOffset == 3)
                            {
                                DebugMessageArcTx("[ARC Tx] IEEE OUI 1st two hex digits =", ucCdsData);
                            }
                            else if(ucDbOffset >= 4)
                            {
                                DebugMessageArcTx("[ARC Tx] Vendor Specific Audio Data Block Payload =", ucCdsData);
                            }
                        }
                        // Room Configuration Data Block
                        else if(ucCtaExtendTag == 0x13)
                        {
                            if(ucDbOffset == 0)
                            {
                                pstEarcRxCdsInfo->ucEarcCdsRcdbOffset = usCdsOffset - 1;
                            }
                            else if(ucDbOffset == 1)
                            {
                                if(ucCdsData & _BIT6)
                                {
                                    DebugMessageArcTx("[ARC Tx] Speaker Count =", ucCdsData & 0x1F);
                                }
                                else
                                {
                                    DebugMessageArcTx("[ARC Tx] Speaker Count = undefined", 0);
                                }

                                DebugMessageArcTx("[ARC Tx] Display Flag =", (ucCdsData & _BIT7) >> 7);
                                DebugMessageArcTx("[ARC Tx] Speaker Flag =", (ucCdsData & _BIT6) >> 6);
                                DebugMessageArcTx("[ARC Tx] SLD Flag =", (ucCdsData & _BIT5) >> 5);
                            }
                            else if(ucDbOffset == 2)
                            {
                                DebugMessageArcTx("[ARC Tx] Speaker FL/FR       Present:", (ucCdsData & _BIT0) >> 0);
                                DebugMessageArcTx("[ARC Tx] Speaker LFE1        Present:", (ucCdsData & _BIT1) >> 1);
                                DebugMessageArcTx("[ARC Tx] Speaker FC          Present:", (ucCdsData & _BIT2) >> 2);
                                DebugMessageArcTx("[ARC Tx] Speaker BL/BR       Present:", (ucCdsData & _BIT3) >> 3);
                                DebugMessageArcTx("[ARC Tx] Speaker BC          Present:", (ucCdsData & _BIT4) >> 4);
                                DebugMessageArcTx("[ARC Tx] Speaker FLC/FRC     Present:", (ucCdsData & _BIT5) >> 5);
                                DebugMessageArcTx("[ARC Tx] Speaker RLC/RRC     Present:", (ucCdsData & _BIT6) >> 6);
                                DebugMessageArcTx("[ARC Tx] Speaker FLW/FRW     Present:", (ucCdsData & _BIT7) >> 7);
                            }
                            else if(ucDbOffset == 3)
                            {
                                DebugMessageArcTx("[ARC Tx] Speaker TpFL/TpFR   Present:", (ucCdsData & _BIT0) >> 0);
                                DebugMessageArcTx("[ARC Tx] Speaker TpC         Present:", (ucCdsData & _BIT1) >> 1);
                                DebugMessageArcTx("[ARC Tx] Speaker TpFC        Present:", (ucCdsData & _BIT2) >> 2);
                                DebugMessageArcTx("[ARC Tx] Speaker LS/RS       Present:", (ucCdsData & _BIT3) >> 3);
                                DebugMessageArcTx("[ARC Tx] Speaker LFE2        Present:", (ucCdsData & _BIT4) >> 4);
                                DebugMessageArcTx("[ARC Tx] Speaker TpBC        Present:", (ucCdsData & _BIT5) >> 5);
                                DebugMessageArcTx("[ARC Tx] Speaker SiL/SiR     Present:", (ucCdsData & _BIT6) >> 6);
                                DebugMessageArcTx("[ARC Tx] Speaker TpSiL/TpSiR Present:", (ucCdsData & _BIT7) >> 7);
                            }
                            else if(ucDbOffset == 4)
                            {
                                DebugMessageArcTx("[ARC Tx] Speaker TpBL/TpBR   Present:", (ucCdsData & _BIT0) >> 0);
                                DebugMessageArcTx("[ARC Tx] Speaker BtFC        Present:", (ucCdsData & _BIT1) >> 1);
                                DebugMessageArcTx("[ARC Tx] Speaker BtFL/BtFR   Present:", (ucCdsData & _BIT2) >> 2);
                                DebugMessageArcTx("[ARC Tx] Speaker TpLS/TpRS   Present:", (ucCdsData & _BIT3) >> 3);
                            }
                            else if(ucDbOffset == 5)
                            {
                                DebugMessageArcTx("[ARC Tx] The furthest speaker to Primary Listening Position distance at X(meter) =", ucCdsData / 10);
                            }
                            else if(ucDbOffset == 6)
                            {
                                DebugMessageArcTx("[ARC Tx] The furthest speaker to Primary Listening Position distance at Y(meter) =", ucCdsData / 10);
                            }
                            else if(ucDbOffset == 7)
                            {
                                DebugMessageArcTx("[ARC Tx] The furthest speaker to Primary Listening Position distance at Z(meter) =", ucCdsData / 10);
                            }
                            else if(ucDbOffset == 8)
                            {
                                DebugMessageArcTx("[ARC Tx] The display center to Primary Listening Position distance at X(meter) =", ucCdsData / 10);
                            }
                            else if(ucDbOffset == 9)
                            {
                                DebugMessageArcTx("[ARC Tx] The display center to Primary Listening Position distance at Y(meter) =", ucCdsData / 10);
                            }
                            else if(ucDbOffset == 10)
                            {
                                DebugMessageArcTx("[ARC Tx] The display center to Primary Listening Position distance at Z(meter) =", ucCdsData / 10);
                            }
                        }
                        // Speaker Location Data Block
                        else if(ucCtaExtendTag == 0x14)
                        {
                            if((ucDbOffset % 5) == 1)
                            {
                                ucCtaExtSlDbCoordFlag = (ucCdsData & _BIT6) >> 6;

                                DebugMessageArcTx("[ARC Tx] Channel Index =", ucCdsData & 0x1F);
                                DebugMessageArcTx("[ARC Tx] COORD Flag =", ucCtaExtSlDbCoordFlag);
                                DebugMessageArcTx("[ARC Tx] Active Flag =", (ucCdsData & _BIT5) >> 5);
                            }
                            else if((ucDbOffset % 5) == 2)
                            {
                                switch(ucCdsData & 0x1F)
                                {
                                    case 0x00:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: FL", ucCdsData);
                                        break;
                                    case 0x01:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: FR", ucCdsData);
                                        break;
                                    case 0x02:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: FC", ucCdsData);
                                        break;
                                    case 0x03:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: LFE1", ucCdsData);
                                        break;
                                    case 0x04:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: BL", ucCdsData);
                                        break;
                                    case 0x05:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: BR", ucCdsData);
                                        break;
                                    case 0x06:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: FLR", ucCdsData);
                                        break;
                                    case 0x07:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: FRC", ucCdsData);
                                        break;
                                    case 0x08:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: BC", ucCdsData);
                                        break;
                                    case 0x09:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: LFE2", ucCdsData);
                                        break;
                                    case 0x0A:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: SiL", ucCdsData);
                                        break;
                                    case 0x0B:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: SiR", ucCdsData);
                                        break;
                                    case 0x0C:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: TpFL", ucCdsData);
                                        break;
                                    case 0x0D:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: TpFR", ucCdsData);
                                        break;
                                    case 0x0E:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: TpFC", ucCdsData);
                                        break;
                                    case 0x0F:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: TpC", ucCdsData);
                                        break;
                                    case 0x10:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: TpBL", ucCdsData);
                                        break;
                                    case 0x11:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: TpBR", ucCdsData);
                                        break;
                                    case 0x12:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: TpSiL", ucCdsData);
                                        break;
                                    case 0x13:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: TpSiR", ucCdsData);
                                        break;
                                    case 0x14:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: TpBC", ucCdsData);
                                        break;
                                    case 0x15:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: BtFC", ucCdsData);
                                        break;
                                    case 0x16:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: BtFL", ucCdsData);
                                        break;
                                    case 0x17:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: BrFR", ucCdsData);
                                        break;
                                    case 0x18:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: FLw", ucCdsData);
                                        break;
                                    case 0x19:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: FRw", ucCdsData);
                                        break;
                                    case 0x1A:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: LS", ucCdsData);
                                        break;
                                    case 0x1B:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: RS", ucCdsData);
                                        break;
                                    default:
                                        DebugMessageArcTx("[ARC Tx] Speaker ID: Reserved", ucCdsData);
                                        break;
                                }
                            }
                            else
                            {
                                if(ucCtaExtSlDbCoordFlag)
                                {
                                    if((ucDbOffset % 5) == 3)
                                    {
                                        DebugMessageArcTx("[ARC Tx] This speaker to Primary Listening Position distance at X(meter) =", ucCdsData / 10);
                                    }
                                    else if((ucDbOffset % 5) == 4)
                                    {
                                        DebugMessageArcTx("[ARC Tx] This speaker to Primary Listening Position distance at Y(meter) =", ucCdsData / 10);
                                    }
                                    else if((ucDbOffset % 5) == 0)
                                    {
                                        DebugMessageArcTx("[ARC Tx] This speaker to Primary Listening Position distance at Z(meter) =", ucCdsData / 10);
                                    }
                                }
                                else
                                {
                                    // Skip COORD1~3
                                    ucDbOffset += 3;
                                }
                            }
                        }

                        ucDbOffset++;
                        break;

                    default:
                        break;
                }

                if(usCdsOffset == ucCtaDbEnd)
                {
                    if(usCdsOffset != ucBlockEnd)
                    {
                        ucCtaDbStart = ucCtaDbEnd + 1;
                    }

                    continue;
                }
                else
                {
                    continue;
                }
            }
            // CTA Speaker Location Descriptor Data Block
            else if(ucBlockId == 0x2)
            {
                if(usCdsOffset == ucCtaSldDbStart)
                {
                    ucDbOffset = 0;
                    ucCtaSldDbEnd = usCdsOffset + 5;
                }

                if((usCdsOffset >= ucCtaSldDbStart) && (usCdsOffset <= ucCtaSldDbEnd))
                {
                    if(ucDbOffset == 1)
                    {
                        ucCtaExtSlDbCoordFlag = (ucCdsData & _BIT6) >> 6;

                        DebugMessageArcTx("[ARC Tx] Channel Index =", ucCdsData & 0x1F);
                        DebugMessageArcTx("[ARC Tx] COORD Flag =", ucCtaExtSlDbCoordFlag);
                        DebugMessageArcTx("[ARC Tx] Active Flag =", (ucCdsData & _BIT5) >> 5);
                    }
                    else if(ucDbOffset == 2)
                    {
                        switch(ucCdsData & 0x1F)
                        {
                            case 0x00:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: FL", ucCdsData);
                                break;
                            case 0x01:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: FR", ucCdsData);
                                break;
                            case 0x02:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: FC", ucCdsData);
                                break;
                            case 0x03:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: LFE1", ucCdsData);
                                break;
                            case 0x04:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: BL", ucCdsData);
                                break;
                            case 0x05:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: BR", ucCdsData);
                                break;
                            case 0x06:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: FLR", ucCdsData);
                                break;
                            case 0x07:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: FRC", ucCdsData);
                                break;
                            case 0x08:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: BC", ucCdsData);
                                break;
                            case 0x09:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: LFE2", ucCdsData);
                                break;
                            case 0x0A:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: SiL", ucCdsData);
                                break;
                            case 0x0B:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: SiR", ucCdsData);
                                break;
                            case 0x0C:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: TpFL", ucCdsData);
                                break;
                            case 0x0D:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: TpFR", ucCdsData);
                                break;
                            case 0x0E:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: TpFC", ucCdsData);
                                break;
                            case 0x0F:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: TpC", ucCdsData);
                                break;
                            case 0x10:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: TpBL", ucCdsData);
                                break;
                            case 0x11:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: TpBR", ucCdsData);
                                break;
                            case 0x12:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: TpSiL", ucCdsData);
                                break;
                            case 0x13:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: TpSiR", ucCdsData);
                                break;
                            case 0x14:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: TpBC", ucCdsData);
                                break;
                            case 0x15:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: BtFC", ucCdsData);
                                break;
                            case 0x16:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: BtFL", ucCdsData);
                                break;
                            case 0x17:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: BrFR", ucCdsData);
                                break;
                            case 0x18:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: FLw", ucCdsData);
                                break;
                            case 0x19:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: FRw", ucCdsData);
                                break;
                            case 0x1A:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: LS", ucCdsData);
                                break;
                            case 0x1B:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: RS", ucCdsData);
                                break;
                            default:
                                DebugMessageArcTx("[ARC Tx] Speaker ID: Reserved", ucCdsData);
                                break;
                        }
                    }

                    if(ucCtaExtSlDbCoordFlag)
                    {
                        if(ucDbOffset == 3)
                        {
                            DebugMessageArcTx("[ARC Tx] This speaker to Primary Listening Position distance at X(meter) =", ucCdsData / 10);
                        }
                        else if(ucDbOffset == 4)
                        {
                            DebugMessageArcTx("[ARC Tx] This speaker to Primary Listening Position distance at Y(meter) =", ucCdsData / 10);
                        }
                        else if(ucDbOffset == 5)
                        {
                            DebugMessageArcTx("[ARC Tx] This speaker to Primary Listening Position distance at Z(meter) =", ucCdsData / 10);
                        }
                    }
                    else
                    {
                        // Skip COORD1~3
                        ucDbOffset += 3;
                    }

                    ucDbOffset++;
                }

                if(usCdsOffset == ucCtaSldDbEnd)
                {
                    if(usCdsOffset != ucBlockEnd)
                    {
                        ucCtaSldDbStart = ucCtaSldDbEnd + 1;
                    }

                    continue;
                }
                else
                {
                    continue;
                }
            }
            // Audio Stream Layout Data Block
            else if(ucBlockId == 0x3)
            {
                switch(ucCdsData & 0x07)
                {
                    case 0:
                        DebugMessageArcTx("[ARC Tx] MULTI_CH_LPCM_LAYOUT: 2 and 8-channel layouts are supported", ucCdsData);
                        break;
                    case 1:
                        DebugMessageArcTx("[ARC Tx] MULTI_CH_LPCM_LAYOUT: 2, 8 and 16-channel layouts are supported", ucCdsData);
                        break;
                    case 2:
                        DebugMessageArcTx("[ARC Tx] MULTI_CH_LPCM_LAYOUT: 2, 8, 16 and 32-channel layouts are supported", ucCdsData);
                        break;
                    default:
                        DebugMessageArcTx("[ARC Tx] MULTI_CH_LPCM_LAYOUT: Reserved", ucCdsData);
                        break;
                }

                switch((ucCdsData & 0x38) >> 3)
                {
                    case 0:
                        DebugMessageArcTx("[ARC Tx] ONE_BIT_AUDIO_LAYOUT: One Bit Audio is not supported or 6-channel layout is supported", ucCdsData);
                        break;
                    case 1:
                        DebugMessageArcTx("[ARC Tx] ONE_BIT_AUDIO_LAYOUT: 6 and 12-channel layouts are supported", ucCdsData);
                        break;
                    default:
                        DebugMessageArcTx("[ARC Tx] ONE_BIT_AUDIO_LAYOUT: Reserved", ucCdsData);
                        break;
                }

                if(ucCdsData & _BIT7)
                {
                    DebugMessageArcTx("[ARC Tx] Supports_AI (ACP/ISRC1/ISRC2): Yes", ucCdsData);
                }
                else
                {
                    DebugMessageArcTx("[ARC Tx] Supports_AI (ACP/ISRC1/ISRC2): No", ucCdsData);
                }
            }
        }
    }

    if(pstEarcRxCdsInfo->ucEarcCdsAdbOffset > 0)
    {
        ucDbLength = (pucEarcRxCdsTable[pstEarcRxCdsInfo->ucEarcCdsAdbOffset] & 0x1F) + 1;

        for(ucDbOffset = 0; ucDbOffset < ucDbLength; ucDbOffset++)
        {
            *(pstEarcRxCdsInfo->pucEarcCdsAdb + ucDbOffset) = pucEarcRxCdsTable[pstEarcRxCdsInfo->ucEarcCdsAdbOffset + ucDbOffset];
        }
    }

    if(pstEarcRxCdsInfo->ucEarcCdsSpkAdbOffset > 0)
    {
        for(ucDbOffset = 0; ucDbOffset < 4; ucDbOffset++)
        {
            *(pstEarcRxCdsInfo->pucEarcCdsSpkAdb + ucDbOffset) = pucEarcRxCdsTable[pstEarcRxCdsInfo->ucEarcCdsSpkAdbOffset + ucDbOffset];
        }
    }

    /*if(pstEarcRxCdsInfo->ucEarcCdsSpkLdbOffset > 0)
    {
        ucDbLength = (pucEarcRxCdsTable[pstEarcRxCdsInfo->ucEarcCdsSpkLdbOffset] & 0x1F) + 1;

        for(ucDbOffset = 0; ucDbOffset < ucDbLength; ucDbOffset++)
        {
            *(pstEarcRxCdsInfo->pucEarcCdsSpkLdb + ucDbOffset) = pucEarcRxCdsTable[pstEarcRxCdsInfo->ucEarcCdsSpkLdbOffset + ucDbOffset];
        }
    }

    if(pstEarcRxCdsInfo->ucEarcCdsRcdbOffset > 0)
    {
        ucDbLength = (pucEarcRxCdsTable[g_stAudioEarcRxCdsInfo.ucEarcCdsRcdbOffset] & 0x1F) + 1;

        for(ucDbOffset = 0; ucDbOffset < ucDbLength; ucDbOffset++)
        {
            *(pstEarcRxCdsInfo->pucEarcCdsRcdb + ucDbOffset) = pucEarcRxCdsTable[pstEarcRxCdsInfo->ucEarcCdsRcdbOffset + ucDbOffset];
        }
    }*/

    return _TRUE;
}

//--------------------------------------------------
// Description  : Audio eARC Tx CDS Audio Data Block Parser
// Input Value  : pucCtaSad
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxEarcCdsAudioDataBlockParser(BYTE *pucCtaSad)
{
    BYTE ucAudioFormat = 0;
    BYTE ucMaxChannel = 0;
    BYTE ucExtendCode = 0;

    ucAudioFormat = (pucCtaSad[0] & 0x78) >> 3;

    switch(ucAudioFormat)
    {
        case 0x1:
            DebugMessageArcTx("[ARC Tx] Audio Format: LPCM", ucAudioFormat);
            break;
        case 0x2:
            DebugMessageArcTx("[ARC Tx] Audio Format: AC3", ucAudioFormat);
            break;
        case 0x3:
            DebugMessageArcTx("[ARC Tx] Audio Format: MPEG1", ucAudioFormat);
            break;
        case 0x4:
            DebugMessageArcTx("[ARC Tx] Audio Format: MP3", ucAudioFormat);
            break;
        case 0x5:
            DebugMessageArcTx("[ARC Tx] Audio Format: MPEG2", ucAudioFormat);
            break;
        case 0x6:
            DebugMessageArcTx("[ARC Tx] Audio Format: AAC", ucAudioFormat);
            break;
        case 0x7:
            DebugMessageArcTx("[ARC Tx] Audio Format: DTS", ucAudioFormat);
            break;
        case 0x8:
            DebugMessageArcTx("[ARC Tx] Audio Format: ATRAC", ucAudioFormat);
            break;
        case 0x9:
            DebugMessageArcTx("[ARC Tx] Audio Format: One Bit Audio", ucAudioFormat);
            break;
        case 0xA:
            DebugMessageArcTx("[ARC Tx] Audio Format: EAC3(Dolby Digital)", ucAudioFormat);
            break;
        case 0xB:
            DebugMessageArcTx("[ARC Tx] Audio Format: DTS-HD", ucAudioFormat);
            break;
        case 0xC:
            DebugMessageArcTx("[ARC Tx] Audio Format: MAT(Dolby TrueHD)", ucAudioFormat);
            break;
        case 0xD:
            DebugMessageArcTx("[ARC Tx] Audio Format: DST", ucAudioFormat);
            break;
        case 0xE:
            DebugMessageArcTx("[ARC Tx] Audio Format: WMA Pro", ucAudioFormat);
            break;
        case 0xF:
            DebugMessageArcTx("[ARC Tx] Audio Format: Ref. Coding Extension", ucAudioFormat);
            break;
        default:
            DebugMessageArcTx("[ARC Tx] Audio Format: Reserved", ucAudioFormat);
            break;
    }

    if(ucAudioFormat == 0xF)
    {
        ucExtendCode = (pucCtaSad[2] & 0xF8) >> 3;

        switch(ucExtendCode)
        {
            case 0x0:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: Ref. CT field in Data Byte 1", ucExtendCode);
                break;
            case 0x1:
            case 0x2:
            case 0x3:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: Not in use", ucExtendCode);
                break;
            case 0x4:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: MPEG4 HE AAC", ucExtendCode);
                break;
            case 0x5:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: MPEG4 HE AAC v2", ucExtendCode);
                break;
            case 0x6:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: MPEG4 AAC LC", ucExtendCode);
                break;
            case 0x7:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: DRA", ucExtendCode);
                break;
            case 0x8:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: MPEG4 HE AAC + MPEG Surround", ucExtendCode);
                break;
            case 0x9:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: Reserved", ucExtendCode);
                break;
            case 0xA:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: MPEG4 AAC LC + MPEG Surround", ucExtendCode);
                break;
            case 0xB:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: MPEGH 3D Audio", ucExtendCode);
                break;
            case 0xC:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: AC4", ucExtendCode);
                break;
            case 0xD:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: LPCM 3D Audio", ucExtendCode);
                break;
            default:
                DebugMessageArcTx("[ARC Tx] Extension Code Type: Reserved", ucExtendCode);
                break;
        }
    }

    if((ucAudioFormat == 0xF) && ((ucExtendCode == 0xB) || (ucExtendCode == 0xC)))
    {
        DebugMessageArcTx("[ARC Tx] No Max Channel Information", 0);
    }
    else
    {
        ucMaxChannel = (pucCtaSad[0] & 0x7) + 1;

        if((ucAudioFormat == 0xF) && (ucExtendCode == 0xD))
        {
            ucMaxChannel += ((pucCtaSad[0] & 0x80) >> 7) << 3;
            ucMaxChannel += ((pucCtaSad[1] & 0x80) >> 7) << 4;
        }

        DebugMessageArcTx("[ARC Tx] Max Channel =", ucMaxChannel);
    }

    DebugMessageArcTx("[ARC Tx] Support Sampling Frequency:", 0);

    if(pucCtaSad[1] & _BIT0)
    {
        DebugMessageArcTx("[ARC Tx] 32khz:", pucCtaSad[1]);
    }

    if(pucCtaSad[1] & _BIT1)
    {
        DebugMessageArcTx("[ARC Tx] 44.1khz:", pucCtaSad[1]);
    }

    if(pucCtaSad[1] & _BIT2)
    {
        DebugMessageArcTx("[ARC Tx] 48khz:", pucCtaSad[1]);
    }

    if(pucCtaSad[1] & _BIT3)
    {
        DebugMessageArcTx("[ARC Tx] 88.2khz:", pucCtaSad[1]);
    }

    if(pucCtaSad[1] & _BIT4)
    {
        DebugMessageArcTx("[ARC Tx] 96khz:", pucCtaSad[1]);
    }

    if(pucCtaSad[1] & _BIT5)
    {
        DebugMessageArcTx("[ARC Tx] 176.4khz:", pucCtaSad[1]);
    }

    if(pucCtaSad[1] & _BIT6)
    {
        DebugMessageArcTx("[ARC Tx] 192khz:", pucCtaSad[1]);
    }

    if((ucAudioFormat == 0x1) || ((ucAudioFormat == 0xF) && (ucExtendCode == 0xD)))
    {
        DebugMessageArcTx("[ARC Tx] Support Sample Length:", 0);

        if(pucCtaSad[2] & _BIT0)
        {
            DebugMessageArcTx("[ARC Tx] 16bit:", pucCtaSad[2]);
        }

        if(pucCtaSad[2] & _BIT1)
        {
            DebugMessageArcTx("[ARC Tx] 20bit:", pucCtaSad[2]);
        }

        if(pucCtaSad[2] & _BIT2)
        {
            DebugMessageArcTx("[ARC Tx] 24bit:", pucCtaSad[2]);
        }
    }
    else if((ucAudioFormat >= 0x2) && (ucAudioFormat <= 0x8))
    {
        DebugMessageArcTx("[ARC Tx] Maximum Bit Rate(kHz) =", pucCtaSad[2] * 8);
    }
    else if((ucAudioFormat >= 0x9) && (ucAudioFormat <= 0xD))
    {
        DebugMessageArcTx("[ARC Tx] Value Defined by Audio Codec Vendor =", pucCtaSad[2]);
    }
    else if(ucAudioFormat == 0xE)
    {
        DebugMessageArcTx("[ARC Tx] Profile =", pucCtaSad[2] & 0x07);
    }
    else if(ucAudioFormat == 0xF)
    {
        if(((ucExtendCode >= 0x4) && (ucExtendCode <= 0x6)) || ((ucExtendCode >= 0x8) && (ucExtendCode <= 0xA)))
        {
            if(pucCtaSad[0] & _BIT1)
            {
                DebugMessageArcTx("[ARC Tx] Support AAC Frame Length of 960 Samples: Yes", pucCtaSad[2]);
            }
            else
            {
                DebugMessageArcTx("[ARC Tx] Support AAC Frame Length of 960 Samples: No", pucCtaSad[2]);
            }

            if(pucCtaSad[0] & _BIT2)
            {
                DebugMessageArcTx("[ARC Tx] Support AAC Frame Length of 1024 Samples: Yes", pucCtaSad[2]);
            }
            else
            {
                DebugMessageArcTx("[ARC Tx] Support AAC Frame Length of 1024 Samples: No", pucCtaSad[2]);
            }

            if((ucExtendCode >= 0x8) && (ucExtendCode <= 0xA))
            {
                if(pucCtaSad[0] & _BIT0)
                {
                    DebugMessageArcTx("[ARC Tx] Sink Supports Only Implictly Signaled MPEG Surround Data", pucCtaSad[2]);
                }
                else
                {
                    DebugMessageArcTx("[ARC Tx] Sink Supports Only Implictly and Explicitly Signaled MPEG Surround Data", pucCtaSad[2]);
                }
            }
        }
        else if((ucExtendCode == 0xB) || (ucExtendCode == 0xC))
        {
            DebugMessageArcTx("[ARC Tx] Audio Format Code Dependent Value =", pucCtaSad[2] & 0x07);
        }
    }
}

//--------------------------------------------------
// Description  : Audio eARC Tx Check Mute Flag Change Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxEarcCheckChStatusMuteFlagChangeProc(void)
{
    SET_AUDIO_ARC_TX_OSD_ARC_MUTE_STATUS(UserCommonAudioGetArcMuteStatus());

    if(SysAudioArcTxEarcGetChStatusMuteFlag() != GET_AUDIO_ARC_TX_OSD_ARC_MUTE_STATUS())
    {
        SysAudioArcTxEarcSetChStatusMuteFlag(GET_AUDIO_ARC_TX_OSD_ARC_MUTE_STATUS());

        DebugMessageArcTx("[ARC Tx] eARC Tx Mute Flag Change", GET_AUDIO_ARC_TX_OSD_ARC_MUTE_STATUS());
    }
}

//--------------------------------------------------
// Description  : Audio eARC Tx Set Mute Flag
// Input Value  : EnumAudioMuteStatus
// Output Value : None
//--------------------------------------------------
void SysAudioArcTxEarcSetChStatusMuteFlag(EnumAudioMuteStatus enumArcMute)
{
    enumArcMute = enumArcMute;

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    UserCommonArcTxEarcSetChStatusMuteFlag(enumArcMute);
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    ScalerHdmiArcTxEarcSetChStatusMuteFlag(enumArcMute);
#endif
#endif
}

//--------------------------------------------------
// Description  : Audio eARC Tx Get Mute Flag
// Input Value  : None
// Output Value : EnumAudioMuteStatus
//--------------------------------------------------
EnumAudioMuteStatus SysAudioArcTxEarcGetChStatusMuteFlag(void)
{
#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
    return UserCommonArcTxEarcGetChStatusMuteFlag();
#elif(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EMBEDDED_ARC_EARC_IP)
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    return ScalerHdmiArcTxEarcGetChStatusMuteFlag();
#endif
#endif
}
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)

#if((_HDMI_SUPPORT == _ON) && (_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
//--------------------------------------------------
// Description  : HBR Audio Setting For Parallel Mode
// Input Value  : ucPathIndex
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysAudioHbrAudioSettingForParallelMode(BYTE ucPathIndex)
{
#if(_HDMI_IDENTIFY_GAME_SRC_SUPPORT == _ON)
    if((UserCommonTmdsGetHbrAudioSrcInfo(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _PRODUCT_DESCRIPTION_PS_SERIES) || (UserCommonTmdsGetHbrAudioSrcInfo(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) == _PRODUCT_DESCRIPTION_XBOX_SERIES))
#endif
    {
        if(ScalerAudioSamplingFreqDetect(GET_AUDIO_PATH_INPUT_PORT(ucPathIndex)) > _AUDIO_FREQ_PACKET_192K)
        {
            if(ScalerAudioHdmiHbrSettingProc(GET_AUDIO_PATH_OUTPUT_PORT(ucPathIndex)) == _FALSE)
            {
                return _FALSE;
            }
        }
    }
    return _TRUE;
}
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

