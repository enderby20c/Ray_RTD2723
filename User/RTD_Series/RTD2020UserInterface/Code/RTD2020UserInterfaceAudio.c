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
// ID Code      : RTD2020UserInterfaceAudio.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_AUDIO__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceAudio.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Determine whether to User is Ready to play audio
// Input Value  : None
// Output Value : _TRUE => Free to Play
//--------------------------------------------------
EnumAudioStatus UserInterfaceAudioGetReadyToPlayStatus(void)
{
    EnumDisplayRegion enumAudioPlayRegion = UserInterfaceAudioGetDisplayModeRegion();
    EnumAudioInputSource enumAudioSource = UserInterfaceAudioGetSource();

#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT != _ON)
    if(GET_OSD_VOLUME_MUTE() != _ENABLE)
#endif
    {
#if(_EMBEDDED_DAC_SUPPORT == _ON)
        if(UserCommonAudioDACGetState() == _AUDIO_DAC_READY)
#endif
        {
#if(_LINE_IN_SUPPORT == _ON)
            if(enumAudioSource == _LINE_IN_AUDIO)
            {
#if(_SLEEP_AUDIO_SUPPORT == _ON)
                if(UserInterfaceAudioGetStandAloneStatus() == _AUDIO_STAND_ALONE_TRUE)
                {
#if((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN))
                    return _AUDIO_READY_TRUE;
#endif
                }
#endif
                if(((enumAudioPlayRegion == _DISPLAY_RGN_NONE) &&
                    (SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) != 0)) ||
                   (SysRegionGetDisplayState(enumAudioPlayRegion) == _DISPLAY_STATE_ACTIVE) ||
                   ((SysModeGetModeState() == _MODE_STATUS_DISPLAY_SETTING) &&
                    (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK)))
                {
                    return _AUDIO_READY_TRUE;
                }
            }
            else
#endif
            {
                if(enumAudioSource == _DIGITAL_AUDIO)
                {
#if(_SLEEP_AUDIO_SUPPORT == _ON)
                    if(UserInterfaceAudioGetStandAloneStatus() == _AUDIO_STAND_ALONE_TRUE)
                    {
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
                        EnumInputPort enumInputPort = SysRegionGetInputPort(enumAudioPlayRegion);

                        if(UserCommonAudioGetDigitalAudioSource(enumInputPort) == _DIGITAL_AUDIO_SOURCE_DP)
                        {
                            // When Fixed Port, should not play DP Audio at differentport
                            if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) ||
                               (SysSourceGetAudioPlaybackPort() == enumInputPort))
                            {
                                return _AUDIO_READY_TRUE;
                            }
                        }
#endif
                    }
#endif
                    if((SysRegionGetDisplayState(enumAudioPlayRegion) == _DISPLAY_STATE_ACTIVE) ||
                       (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK))
                    {
                        return _AUDIO_READY_TRUE;
                    }
                }
            }
        }
    }
    return _AUDIO_READY_FALSE;
}

//--------------------------------------------------
// Description  : User OSD Get Audio Source
// Input Value  : None
// Output Value : _DIGITAL_AUDIO or _LINE_IN_AUDIO
//--------------------------------------------------
EnumAudioInputSource UserInterfaceAudioGetSource(void)
{
    EnumDisplayRegion enumAudioPlayRegion = UserInterfaceAudioGetDisplayModeRegion();
    EnumInputPort enumInputPort = SysRegionGetInputPort(enumAudioPlayRegion);

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(UserCommonAudioGetInternalAudioGenEnable(enumInputPort) == _ENABLE)
    {
        return _DIGITAL_AUDIO;
    }
#endif

#if((_SLEEP_AUDIO_SUPPORT == _ON) &&\
    (_LINE_IN_SUPPORT == _ON) &&\
    (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN) &&\
    (_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON))
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
        return _LINE_IN_AUDIO;
    }
#endif

#if(_LINE_IN_SUPPORT == _ON)
    if(GET_OSD_AUDIO_SOURCE() == _OSD_AUDIO_SOURCE_LINEIN)
    {
        return _LINE_IN_AUDIO;
    }
#endif

    switch(enumInputPort)
    {
        case _A0_INPUT_PORT:
#if(_LINE_IN_SUPPORT == _ON)
            return _LINE_IN_AUDIO;
#else
            return _NO_AUDIO_SOURCE;
#endif
        default:

#if((_SLEEP_AUDIO_SUPPORT == _ON) &&\
    ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) ||\
     (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
            // Don't Switch Audio Source if Line In is Currently Playing unless Digital Source is found
            if(UserInterfaceAudioGetStandAloneStatus() == _AUDIO_STAND_ALONE_TRUE)
            {
                if((SysRegionGetSourceType(enumAudioPlayRegion) == _SOURCE_NONE) &&
                   (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK) &&
                   (UserCommonAudioGetInputSource() == _LINE_IN_AUDIO))
                {
                    return _LINE_IN_AUDIO;
                }
            }
#endif

            return _DIGITAL_AUDIO;
    }

    return _NO_AUDIO_SOURCE;
}

//--------------------------------------------------
// Description  : User Decide whether to Mute Audio
// Input Value  : None
// Output Value : _AUDIO_NON_LPCM => Mute Audio
//--------------------------------------------------
EnumAudioMuteStatus UserInterfaceAudioGetOutputMuteStatus(void)
{
#if(_AUDIO_COMPRESS_SUPPORT == _ON)

    return _AUDIO_MUTE_OFF;
#else
    if(UserCommonAudioGetNonLPCMStatus() == _AUDIO_NON_LPCM)
    {
        return _AUDIO_MUTE_ON;
    }
    else
    {
        return _AUDIO_MUTE_OFF;
    }
#endif
}

//--------------------------------------------------
// Description  : Get Current Audio Volume
// Input Value  : None
// Output Value : Current Volume
//--------------------------------------------------
WORD UserInterfaceAudioGetVolume(void)
{
    return UserAdjustAudioVolumeMapping(GET_OSD_VOLUME());
}

#if(_DP_SUPPORT == _ON)
#if(_DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get User Define Dp Audio Capability Initial State
// Input Value  : Input Port
// Output Value : EnumAudioDpDpcdSupport
//--------------------------------------------------
EnumAudioDpDpcdSupport UserInterfaceAudioDpGetCapabilityInitialState(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return _AUDIO_DP_DPCD_SUPPORT;

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return _AUDIO_DP_DPCD_SUPPORT;

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return _AUDIO_DP_DPCD_SUPPORT;

            break;
#endif

        default:

            break;
    }

    return _AUDIO_DP_DPCD_SUPPORT;
}
#endif // End of #if(_DP_DPCD_AUDIO_CAPABILITY_USER_CONTROL_SUPPORT == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_EMBEDDED_DAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DAC Output Switch
// Input Value  : None
// Output Value : EnumAudioDACOutput
//--------------------------------------------------
EnumAudioDACOutput UserInterfaceAudioDACGetOutput(void)
{
#if((_DAC_SPEAKER_OUTPUT_SUPPORT == _ON) && (_DAC_HP_OUTPUT_SUPPORT == _ON))
    return _AUDIO_DAC_OUTPUT_BOTH;
#elif(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
    return _AUDIO_DAC_OUTPUT_SPEAKER;
#elif(_DAC_HP_OUTPUT_SUPPORT == _ON)
    return _AUDIO_DAC_OUTPUT_HEADPHONE;
#else
    return _AUDIO_DAC_OUTPUT_NONE;
#endif
}

//--------------------------------------------------
// Description  : Get if Keep Audio Depop State
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumAudioDacDepopState UserInterfaceAudioDACGetKeepDepopState(void)
{
    return _AUDIO_DAC_KEEP_DEPOP_FALSE;
}
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current Audio Stand Alone Status
// Input Value  : None
// Output Value : Audio Standalone status
//--------------------------------------------------
EnumAudioStandAloneStatus UserInterfaceAudioGetStandAloneStatus(void)
{
    if(GET_OSD_AUDIO_STAND_ALONE() == _TRUE)
    {
        return _AUDIO_STAND_ALONE_TRUE;
    }
    else
    {
        return _AUDIO_STAND_ALONE_FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Audio Power Process
// Input Value  : enumPowStatus
// Output Value : Node
//--------------------------------------------------
void UserInterfaceAudioPowerProc(EnumPowerStatus enumPowStatus)
{
    switch(enumPowStatus)
    {
        case _POWER_STATUS_NORMAL:
            // Add User function
            break;

        case _POWER_STATUS_SAVING:
            // Add User function
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Control User Audio Mute Process
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void UserInterfaceAudioAmpMuteProc(bit bMute)
{
    bMute = bMute;

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(UserInterfaceAudioDACGetOutput() != _AUDIO_DAC_OUTPUT_NONE)
    {
        // External Amp Mute
        PCB_AMP_MUTE((bMute == _ON) ? _AMP_MUTE_ON : _AMP_MUTE_OFF);
        DebugMessageAudio("0.[Ext.Amp]Normal Mute Proc", bMute);
    }
#endif
}

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Control User Audio Fast Mute Process
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void UserInterfaceAudioAmpFastMuteProc(bit bMute)
{
    bMute = bMute;

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(UserInterfaceAudioDACGetOutput() != _AUDIO_DAC_OUTPUT_NONE)
    {
        // External Amp Fast Mute
        PCB_AMP_MUTE((bMute == _ON) ? _AMP_MUTE_ON : _AMP_MUTE_OFF);
        DebugMessageAudio("0.[Ext.Amp]Fast Mute Proc", bMute);
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : Get Audio Digital Mode Region By User
// Input Value  : None
// Output Value : Dispaly Region
//--------------------------------------------------
EnumDisplayRegion UserInterfaceAudioGetDisplayModeRegion(void)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(GET_OSD_AUDIO_SOURCE() == _OSD_AUDIO_SOURCE_LINEIN)
    {
        return _DISPLAY_RGN_NONE;
    }
    else
#endif
    {
#if(_MULTI_DISPLAY_MAX > 1)
        // Sync Audio Source Region Index with Display Region Index
        BYTE ucTempAudioSource = GET_OSD_AUDIO_SOURCE() - _OSD_AUDIO_SOURCE_DIGITAL_REGION_1;

        switch(GET_OSD_DISPLAY_MODE())
        {
#if(_4P_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_4P:
                return ((ucTempAudioSource <= _REGION_INDEX_3) ? (EnumDisplayRegion)(_DISPLAY_MODE_4P | ucTempAudioSource) : _DISPLAY_RGN_1P);
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_2P_PIP:
                return ((ucTempAudioSource <= _REGION_INDEX_1) ? (EnumDisplayRegion)(_DISPLAY_MODE_2P_PIP | ucTempAudioSource) : _DISPLAY_RGN_1P);
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_2P_TB:
                return ((ucTempAudioSource <= _REGION_INDEX_1) ? (EnumDisplayRegion)(_DISPLAY_MODE_2P_PBP_TB | ucTempAudioSource) : _DISPLAY_RGN_1P);
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_2P_LR:

                if(GET_OSD_PBP_LR_RATIO() > _OSD_PBP_LR_RATIO_CENTER)
                {
                    return ((ucTempAudioSource <= _REGION_INDEX_1) ? (EnumDisplayRegion)(_DISPLAY_MODE_2P_PBP_LR_L_LARGE | ucTempAudioSource) : _DISPLAY_RGN_1P);
                }
                else if(GET_OSD_PBP_LR_RATIO() < _OSD_PBP_LR_RATIO_CENTER)
                {
                    return ((ucTempAudioSource <= _REGION_INDEX_1) ? (EnumDisplayRegion)(_DISPLAY_MODE_2P_PBP_LR_R_LARGE | ucTempAudioSource) : _DISPLAY_RGN_1P);
                }
                else
                {
                    return ((ucTempAudioSource <= _REGION_INDEX_1) ? (EnumDisplayRegion)(_DISPLAY_MODE_2P_PBP_LR_EQUAL | ucTempAudioSource) : _DISPLAY_RGN_1P);
                }

                break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_3P_FLAG:
                return ((ucTempAudioSource <= _REGION_INDEX_2) ? (EnumDisplayRegion)(_DISPLAY_MODE_3P_FLAG | ucTempAudioSource) : _DISPLAY_RGN_1P);
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_3P_SKEW_L:
                return ((ucTempAudioSource <= _REGION_INDEX_2) ? (EnumDisplayRegion)(_DISPLAY_MODE_3P_SKEW_L | ucTempAudioSource) : _DISPLAY_RGN_1P);
            case _OSD_DM_3P_SKEW_R:
                return ((ucTempAudioSource <= _REGION_INDEX_2) ? (EnumDisplayRegion)(_DISPLAY_MODE_3P_SKEW_R | ucTempAudioSource) : _DISPLAY_RGN_1P);
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_3P_SKEW_T:
                return ((ucTempAudioSource <= _REGION_INDEX_2) ? (EnumDisplayRegion)(_DISPLAY_MODE_3P_SKEW_T | ucTempAudioSource) : _DISPLAY_RGN_1P);
            case _OSD_DM_3P_SKEW_B:
                return ((ucTempAudioSource <= _REGION_INDEX_2) ? (EnumDisplayRegion)(_DISPLAY_MODE_3P_SKEW_B | ucTempAudioSource) : _DISPLAY_RGN_1P);
#endif

            case _OSD_DM_1P:
            default:
                break;
        }
#endif

        return _DISPLAY_RGN_1P;
    }
}

//--------------------------------------------------
// Description  : Get Audio Digital Mode Region Index By User
// Input Value  : None
// Output Value : _REGION_INDEX_x
//--------------------------------------------------
EnumRegionIndex UserInterfaceAudioGetRegionIndex(void)
{
    switch(GET_OSD_AUDIO_SOURCE())
    {
        case _OSD_AUDIO_SOURCE_DIGITAL_REGION_2:

            return _REGION_INDEX_1;

        case _OSD_AUDIO_SOURCE_DIGITAL_REGION_3:

            return _REGION_INDEX_2;

        case _OSD_AUDIO_SOURCE_DIGITAL_REGION_4:

            return _REGION_INDEX_3;

        case _OSD_AUDIO_SOURCE_LINEIN:
        case _OSD_AUDIO_SOURCE_DIGITAL_REGION_1:
        default:
            return _REGION_INDEX_0;
    }
}

//--------------------------------------------------
// Description  : Get User Define Audio Sampling Freq when no Audio
// Input Value  : None
// Output Value : EnumAudioSamplingFreqType
//--------------------------------------------------
EnumAudioSamplingFreqType UserInterfaceAudioGetUserSamplingFreq(void)
{
    return _AUDIO_FREQ_48K;
}

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get User Define Audio Sampling Freq Limitation
// Input Value  : None
// Output Value : EnumAudioSamplingFreqType
//--------------------------------------------------
EnumAudioSamplingFreqType UserInterfaceAudioGetSamplingFreqLimit(void)
{
    // =============================================
    // User should define the sampling frequency
    // limitation. Once the source's audio frequency
    // is over limitation, scaler will mute the
    // output and fix the sampling frequency to the
    // limitation value.
    // =============================================

    return _AUDIO_FREQ_192K;
}
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

#if(_AUDIO_OSD_MUTE_SEPARATE_CONTROL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Control User Audio Mute DSP Process
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void UserInterfaceAudioExternalCodecProc(bit bEnable)
{
    if(bEnable == _DISABLE)
    {
        // Mute On External DSP
    }
    else
    {
        // Mute Off External DSP
    }
    DebugMessageAudio("0.[Ext.Codec]Normal Mute Proc", bEnable);
}

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Control User Audio Mute DSP Fast Process
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void UserInterfaceAudioExternalCodecFastProc(bit bEnable)
{
    if(bEnable == _DISABLE)
    {
        // Fast-Mute On External DSP
    }
    else
    {
        // Fast-Mute Off External DSP
    }
    DebugMessageAudio("0.[Ext.Codec]Fast Mute Proc", bEnable);
}
#endif

//--------------------------------------------------
// Description  : Get Current Audio Mute Status
// Input Value  : Node
// Output Value : GET_OSD_VOLUME_MUTE()
//--------------------------------------------------
EnumAudioMuteStatus UserInterfaceAudioGetMuteStatus(void)
{
    return GET_OSD_VOLUME_MUTE();
}
#endif

#if(_SPDIF_PARALLEL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get SPDIF Parallel Mode
// Input Value  : Node
// Output Value : Parallel Mode SPDIF Mode
//--------------------------------------------------
EnumAudioSpdifParallelMode UserInterfaceAudioSpdifParallelMode(void)
{
    return _SPDIF_1_TO_4;
}
#endif

#if(_I2S_PARALLEL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get I2S Parallel Mode
// Input Value  : Node
// Output Value : Parallel Mode SPDIF Mode
//--------------------------------------------------
EnumAudioI2sParallelMode UserInterfaceAudioI2sParallelMode(void)
{
    return _I2S_1_TO_4;
}

//--------------------------------------------------
// Description  : Get I2S Parallel Type
// Input Value  : Node
// Output Value : Parallel Mode SPDIF Type
//--------------------------------------------------
EnumAudioI2sParallelType UserInterfaceAudioI2sParallelType(void)
{
    return _I2S_PHILIP32_24BIT;
}
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get User Define Audio Gen Freq
// Input Value  : None
// Output Value : 500 ~ 3000Hz
//--------------------------------------------------
EnumAudioInternalGenFreq UserInterfaceAudioGetUserDefineAudioGenFreq(void)
{
    // 1000Hz
    return _AUDIO_GEN_FREQ_1000HZ;
}

#if(_INTERNAL_AUDIO_CHANNEL_CONFIG_BY_USER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get User Select R/L Channel
// Input Value  : None
// Output Value : 500 ~ 3000Hz
//--------------------------------------------------
EnumAudioLeftRightChannelSelect UserInterfaceAudioGetUserLeftRightChanelSelect(void)
{
    return _AUDIO_LEFT_RIGHT_CHANNEL;
}
#endif
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
//--------------------------------------------------
// Description  : Determine TTS is support or not
// Input Value  : None
// Output Value : EnumAudioTtsOsdSupport
//--------------------------------------------------
EnumAudioTtsOsdSupport UserInterfaceAudioGetTtsSupport(void)
{
    if(GET_OSD_AUDIO_TTS_SUPPORT() == _TRUE)
    {
        return _AUDIO_TTS_OSD_SUPPORT_ON;
    }

    return _AUDIO_TTS_OSD_SUPPORT_OFF;
}

//--------------------------------------------------
// Description  : Determine Audio Volume when TTS is play
// Input Value  : None
// Output Value : ucAudioVolume
//--------------------------------------------------
BYTE UserInterfaceAudioGetTtsPlayAudioVolume(void)
{
    return GET_OSD_AUDIO_TTS_AUDIO_VOLUME();
}

//--------------------------------------------------
// Description  : Determine TTS Volume when TTS is play
// Input Value  : None
// Output Value : ucAudioVolume
//--------------------------------------------------
BYTE UserInterfaceAudioGetTtsPlayTextVolume(void)
{
    return GET_OSD_AUDIO_TTS_TEXT_VOLUME();
}

//--------------------------------------------------
// Description  : Determine TTS is Ready for Play or not
// Input Value  : None
// Output Value : EnumAudioTtsPlayReady
//--------------------------------------------------
EnumAudioTtsPlayReady UserInterfaceAudioGetTtsAudioReady(void)
{
#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(UserCommonAudioDACGetState() != _AUDIO_DAC_READY)
    {
        return _AUDIO_TTS_PLAY_NOT_READY;
    }
#endif

    return _AUDIO_TTS_PLAY_READY;
}
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Get Audio Source
// Input Value  : None
// Output Value : _DIGITAL_AUDIO or _LINE_IN_AUDIO
//--------------------------------------------------
EnumAudioInputSource UserInterfaceAudioGetArcSource(void)
{
    EnumAudioArcPortType enumInputPort = GET_OSD_ARC_PORT();

    switch(enumInputPort)
    {
        case _ARC_PORT_LINE_IN:
#if(_LINE_IN_SUPPORT == _ON)
            return _LINE_IN_AUDIO;
#else
            return _NO_AUDIO_SOURCE;
#endif
        default:

            return _DIGITAL_AUDIO;
    }

    return _NO_AUDIO_SOURCE;
}

//--------------------------------------------------
// Description  : Get Arc Audio Inputport
// Input Value  : None
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort UserInterfaceAudioGetArcInputport(void)
{
    switch(GET_OSD_ARC_PORT())
    {
        case _ARC_PORT_LINE_IN:
            return _A0_INPUT_PORT;

        case _ARC_PORT_D0:
            return _D0_INPUT_PORT;

        case _ARC_PORT_D1:
            return _D1_INPUT_PORT;

        case _ARC_PORT_D2:
            return _D2_INPUT_PORT;

        case _ARC_PORT_D3:
            return _D3_INPUT_PORT;

        case _ARC_PORT_D4:
            return _D4_INPUT_PORT;

        default:
            return _NO_INPUT_PORT;
    }
}

//--------------------------------------------------
// Description  : Get Arc Mode
// Input Value  : None
// Output Value : EnumAudioArcMode
//--------------------------------------------------
EnumAudioArcMode UserInterfaceAudioGetArcMode(void)
{
    switch(GET_OSD_ARC_MODE())
    {
        case _AUDIO_ARC_EARC_OFF:
            return _EARC_ARC_OFF;

        case _AUDIO_ARC_ON:
            return _ARC_MODE;

        case _AUDIO_EARC_ON:
            return _EARC_MODE;

        default:
            return _EARC_ARC_OFF;
    }
}

//--------------------------------------------------
// Description  : Get Arc Mute Status
// Input Value  : None
// Output Value : EnumAudioMuteStatus
//--------------------------------------------------
EnumAudioMuteStatus UserInterfaceAudioGetArcMuteStatus(void)
{
    if(GET_OSD_ARC_MUTE_STATUS() == _ON)
    {
        return _AUDIO_MUTE_ON;
    }
    else
    {
        return _AUDIO_MUTE_OFF;
    }
}

//--------------------------------------------------
// Description  : Get Arc Channel
// Input Value  : None
// Output Value : EnumArcAudioChanelStatus
//--------------------------------------------------
EnumArcAudioChanelStatus UserInterfaceAudioGetArcChannel(void)
{
    switch(GET_OSD_ARC_CHANEL())
    {
        case _ARC_2_CH:
            return _ARC_AUDIO_2CH;

        case _ARC_8_CH:
            return _ARC_AUDIO_8CH;

        default:
            return _ARC_AUDIO_2CH;
    }
}

//--------------------------------------------------
// Description  : Get Arc Channel
// Input Value  : None
// Output Value : EnumArcAudioChanelStatus
//--------------------------------------------------
EnumArcAudioOutputType UserInterfaceAudioGetArcAudioOutput(void)
{
    switch(GET_OSD_ARC_OUT())
    {
        case _ARC_DAC:
            return _ARC_AUDIO_DAC_OUT;

        case _ARC_ARC:
            return _ARC_AUDIO_ARC_OUT;

        default:
            return _ARC_AUDIO_ARC_OUT;
    }
}

//--------------------------------------------------
// Description  : User Decide whether to Mute Audio
// Input Value  : None
// Output Value : _AUDIO_NON_LPCM => Mute Audio
//--------------------------------------------------
EnumAudioMuteStatus UserInterfaceAudioGetArcOutputMuteStatus(void)
{
#if(_AUDIO_COMPRESS_SUPPORT == _ON)

    return _AUDIO_MUTE_OFF;
#else
    if(UserCommonAudioGetArcNonLPCMStatus() == _AUDIO_NON_LPCM)
    {
        return _AUDIO_MUTE_ON;
    }
    else
    {
        return _AUDIO_MUTE_OFF;
    }
#endif
}

//--------------------------------------------------
// Description  : User Common Ready to play audio
// Input Value  : None
// Output Value : _TRUE => Free to Play
//--------------------------------------------------
EnumAudioStatus UserInterfaceAudioGetArcReadyToPlayStatus(void)
{
    EnumAudioInputSource enumAudioSourceType = UserInterfaceAudioGetArcSource();
    EnumInputPort enumInputPort = UserInterfaceAudioGetArcInputport();
    EnumDisplayRegion enumAudioPlayRegion = UserInterfaceAudioGetDisplayModeRegion();

    // Check inputport change or not
    if(UserCommonArcTxGetArcAudioState() == _AUDIO_STATUS_PLAYBACK)
    {
        if(UserCommonArcTxGetArcInputPort() != enumInputPort)
        {
            return _AUDIO_READY_FALSE;
        }
    }

    // Unmute
    if(GET_OSD_ARC_MUTE_STATUS() != _ENABLE)
    {
#if(_LINE_IN_SUPPORT == _ON)
        if(enumAudioSourceType == _LINE_IN_AUDIO)
        {
            // Check Line Audio
            if(((enumAudioPlayRegion == _DISPLAY_RGN_NONE) &&
                (SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) != 0)) ||
               (SysRegionGetDisplayState(enumAudioPlayRegion) == _DISPLAY_STATE_ACTIVE) ||
               ((SysModeGetModeState() == _MODE_STATUS_DISPLAY_SETTING) &&
                (UserCommonArcTxGetArcAudioState() == _AUDIO_STATUS_PLAYBACK)))
            {
                return _AUDIO_READY_TRUE;
            }
        }
        else
#endif
        {
            // Check Digital Audio
            if(enumAudioSourceType == _DIGITAL_AUDIO)
            {
                if(((SysRegionGetDisplayState(enumAudioPlayRegion) == _DISPLAY_STATE_ACTIVE) || (UserCommonArcTxGetArcAudioState() == _AUDIO_STATUS_PLAYBACK)) &&
                   (UserInterfaceArcTxEdidGetType() != _EDID_AUDIO_NORMAL))
                {
                    return _AUDIO_READY_TRUE;
                }
            }
        }
    }
    // Mute
    else
    {
#if(_AUDIO_EARC_SUPPORT == _ON)
        if((UserCommonArcTxGetLinkMode() == _EARC_MODE) && (UserCommonArcTxGetArcAudioState() == _AUDIO_STATUS_PLAYBACK))
        {
            // Don't jump back to preparing when playback, only set channel status Mute Flag = 1
            return _AUDIO_READY_TRUE;
        }
        else
#endif
        {
            return _AUDIO_READY_FALSE;
        }
    }

    return _AUDIO_READY_FALSE;
}
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

