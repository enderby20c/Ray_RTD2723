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
// ID Code      : ScalerAudioTts.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_AUDIO_TTS__

#include "ScalerFunctionInclude.h"
#include "AudioTts/ScalerAudioTts.h"

#if(_AUDIO_SUPPORT == _ON)
#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructAudioTtsInfo g_stAudioTtsInfo;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : TTS Initial Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsInitial(void)
{
    // Disable Clcok Gatting
    ScalerAudioClockGatting(_DISABLE);

    // Disable Mixer INT & Clear Flag
    ScalerAudioTtsPlayDoneDetect(_DISABLE);

    // Soft Reset SPIC
    ScalerAudioTtsSpicReset();

    // Set Data Width
    ScalerSetBit(P8_61_BWR_CONTROL, ~_BIT7, ((BYTE)_AUDIO_TTS_CONTENT_BIT_FORMAT) << 7);

    // Enable Block 0/1 BW Int
    ScalerSetBit(P8_60_BWR_INT_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Enable TTS Upsampling, Set PCM Generatoer, TTS FIFO Normal
    ScalerSetBit(P8_00_TTS_UP_SAMPLING_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

#if(_AUDIO_TTS_CONTENT_BIT_FORMAT == _AUDIO_TTS_CONTENT_8_BIT)
    // Input Data 8 Bit Mode
    ScalerSetBit(P8_00_TTS_UP_SAMPLING_CTRL_1, ~(_BIT3 | _BIT2 | _BIT1), 0x00);
#elif(_AUDIO_TTS_CONTENT_BIT_FORMAT == _AUDIO_TTS_CONTENT_16_BIT)
    // Input Data 16 Bit Mode
    ScalerSetBit(P8_00_TTS_UP_SAMPLING_CTRL_1, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
#endif

    // PCM Gen Force Mode Enable(Force To 0)
    ScalerSetBit(P8_09_TTS_UP_SAMPLING_CTRL_5, ~(_BIT7 | _BIT6), _BIT7);

    // Other TTS Reset Flow To Add

    // =====================
    // Audio DVC Initial
    // =====================

    // Enable DVC function and counter
    ScalerSetBit(P8_90_DVC_EN, ~(_BIT7 | _BIT6), _BIT7);

    // Set DVC ZCD window size
    ScalerSetBit(P8_93_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_DVC_ZCD_TIMEOUT_DEFAULT));
    ScalerSetByte(P8_94_DVC_ZC_WIN_CTRL_1, LOBYTE(_DVC_ZCD_TIMEOUT_DEFAULT));

    // Select value mode
    ScalerSetBit(P8_90_DVC_EN, ~_BIT4, _BIT4);

    // Set volume step size
    ScalerSetBit(P8_91_DVC_VA_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_VOLUME_STEP_SIZE_VALUE));
    ScalerSetByte(P8_92_DVC_VA_LSB, LOBYTE(_VOLUME_STEP_SIZE_VALUE));


    // =====================
    // TTS DVC Initial
    // =====================

    // Enable DVC function and counter
    ScalerSetBit(P8_B0_DVC_EN, ~(_BIT7 | _BIT6), _BIT7);

    // Set DVC ZCD window size
    ScalerSetBit(P8_B3_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_DVC_ZCD_TIMEOUT_DEFAULT));
    ScalerSetByte(P8_B4_DVC_ZC_WIN_CTRL_1, LOBYTE(_DVC_ZCD_TIMEOUT_DEFAULT));

    // Select value mode
    ScalerSetBit(P8_B0_DVC_EN, ~_BIT4, _BIT4);

    // Set volume step size
    ScalerSetBit(P8_B1_DVC_VA_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(_VOLUME_STEP_SIZE_VALUE));
    ScalerSetByte(P8_B2_DVC_VA_LSB, LOBYTE(_VOLUME_STEP_SIZE_VALUE));

    // Mute TTS Volume
    ScalerAudioTtsDvcGainControl(_DIGITAL_VOLUME_MIN, _DIGITAL_VOLUME_MAX);
}

//--------------------------------------------------
// Description  : TTS Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsResetProc(void)
{
    // =====================
    // Reset Audio DVC
    // =====================

    // Reset DVC Counter
    ScalerSetBit(P8_90_DVC_EN, ~_BIT6, _BIT6);

    // At Least Delay 2 Cycle of 1 / 256 * FS (= 32KHz)
    DELAY_5US();

    // Enable DVC Counter
    ScalerSetBit(P8_90_DVC_EN, ~_BIT6, 0x00);


    // =====================
    // Reset TTS DVC
    // =====================

    // Reset DVC Counter
    ScalerSetBit(P8_B0_DVC_EN, ~_BIT6, _BIT6);

    // At Least Delay 2 Cycle of 1 / 256 * FS (= 32KHz)
    DELAY_5US();

    // Enable DVC Counter
    ScalerSetBit(P8_B0_DVC_EN, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : TTS Recover Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsRecoverProc(void)
{
    // Volume Recover
    ScalerAudioTtsDvcGainControl(_DIGITAL_VOLUME_MIN, _DIGITAL_VOLUME_MAX);

    // Path Recover
    // Reserved for non-LPCM audio path
}

//--------------------------------------------------
// Description  : Check TTS FIFO Stable or Not
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerAudioTtsPlaybackStableCheck(void)
{
    // Check TTS Upsampling FIFO overflow and underflow
    if(ScalerGetBit(P8_00_TTS_UP_SAMPLING_CTRL_1, (_BIT2 | _BIT1)) != 0x00)
    {
        DebugMessageAudio("False : TTS Audio FIFO", ScalerGetBit(P8_00_TTS_UP_SAMPLING_CTRL_1, (_BIT2 | _BIT1)));

        // Clear TTS FIFO overflow and underflow status
        ScalerSetBit(P8_00_TTS_UP_SAMPLING_CTRL_1, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Set Error Flag
        SET_TTS_PLAYBACK_ERROR();
    }

    return GET_TTS_PLAYBACK_ERROR();
}

//--------------------------------------------------
// Description  : Check TTS Play Done or Not
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerAudioTtsGetPlayDoneStatus(void)
{
    return GET_TTS_PLAY_DONE_FLAG();
}

//--------------------------------------------------
// Description  : TTS Config for Data Play
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsPlayConfig(void)
{
    // =================
    // Upsampling Config
    // =================

    // Set Upsampling Frequency
    ScalerAudioTtsUpsamplingSetFrequency();


    // =================
    // SPIC Config
    // =================

    // Config in WD Event


    // =================
    // Event Active
    // =================

    // Set WD Event
    ScalerAudioTtsSetTimerEvent(_ENABLE);
}

//--------------------------------------------------
// Description  : TTS DVC Gain Control
// Input Value  : usTtsVolume   --> 0x0000 ~ 0x3FFF
//                usAudioVolume --> 0x0000 ~ 0x3FFF
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsDvcGainControl(WORD usTtsVolume, WORD usAudioVolume)
{
    WORD usZCDtime = 0;
    DWORD ulZCDtime_temp = 0;
    EnumAudioSamplingFreqPacket enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_NO_AUDIO;

    // =====================
    // Set Audio Frequency
    // =====================

    // Get Sampling Rate
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetInputSource(_AUDIO_DAC_OUT) == _LINE_IN_AUDIO)
    {
        enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_48K;
    }
    else
#endif
    {
        enumSamplingFreqPacket = ScalerAudioSamplingFreqDetect(ScalerAudioGetDigitalAudioPortMapping(_AUDIO_DAC_OUT));
    }


    // =====================
    // Audio ZCD Timeout
    // =====================

    // Get Current Volume
    usZCDtime = ((WORD)(ScalerGetByte(P8_95_DVC_GAIN_MSB) & 0x3F) << 8) | ((WORD)ScalerGetByte(P8_96_DVC_GAIN_LSB));

    usZCDtime = (usZCDtime > usAudioVolume) ? (usZCDtime - usAudioVolume) : (usAudioVolume - usZCDtime);

    usZCDtime = usZCDtime / _VOLUME_STEP_SIZE_VALUE + 1;

    // Calculate samples of ZCD timeout
    ulZCDtime_temp = (DWORD)enumSamplingFreqPacket * _DVC_VOLUME_ADJUST_TIMER / usZCDtime;

    // Avoid Overflow
    if(ulZCDtime_temp > 0x0FFF)
    {
        usZCDtime = 0x0FFF;
    }
    else
    {
        usZCDtime = (WORD)ulZCDtime_temp;
    }

    // Set DVC ZCD window size
    ScalerSetBit(P8_93_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usZCDtime));
    ScalerSetByte(P8_94_DVC_ZC_WIN_CTRL_1, LOBYTE(usZCDtime));


    // =====================
    // Audio Volume Control
    // =====================

    // DVC gain MSB
    ScalerSetBit(P8_95_DVC_GAIN_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usAudioVolume));

    // DVC gain LSB  (double buffer)
    ScalerSetByte(P8_96_DVC_GAIN_LSB, LOBYTE(usAudioVolume));

    // Set Double Buffer
    ScalerSetBit(P8_97_DVC_GAIN_READ_MSB, ~_BIT6, _BIT6);


    // =====================
    // TTS ZCD Timeout
    // =====================

    // Get Current Volume
    usZCDtime = ((WORD)(ScalerGetByte(P8_B5_DVC_GAIN_MSB) & 0x3F) << 8) | ((WORD)ScalerGetByte(P8_B6_DVC_GAIN_LSB));

    usZCDtime = (usZCDtime > usTtsVolume) ? (usZCDtime - usTtsVolume) : (usTtsVolume - usZCDtime);

    usZCDtime = usZCDtime / _VOLUME_STEP_SIZE_VALUE + 1;

    // Calculate samples of ZCD timeout
    ulZCDtime_temp = (DWORD)enumSamplingFreqPacket * _DVC_VOLUME_ADJUST_TIMER / usZCDtime;

    // Avoid Overflow
    if(ulZCDtime_temp > 0x0FFF)
    {
        usZCDtime = 0x0FFF;
    }
    else
    {
        usZCDtime = (WORD)ulZCDtime_temp;
    }

    // Set DVC ZCD window size
    ScalerSetBit(P8_B3_DVC_ZC_WIN_CTRL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usZCDtime));
    ScalerSetByte(P8_B4_DVC_ZC_WIN_CTRL_1, LOBYTE(usZCDtime));


    // =====================
    // TTS Volume Control
    // =====================

    // DVC gain MSB
    ScalerSetBit(P8_B5_DVC_GAIN_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(usTtsVolume));

    // DVC gain LSB  (double buffer)
    ScalerSetByte(P8_B6_DVC_GAIN_LSB, LOBYTE(usTtsVolume));

    // Set Double Buffer
    ScalerSetBit(P8_B7_DVC_GAIN_READ_MSB, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : TTS SPIC Reset Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsSpicReset(void)
{
    // TTS SPIC Burst data reset
    ScalerSetBit(P8_60_BWR_INT_CTRL, ~(_BIT7 | _BIT3 | _BIT1), _BIT7);

    // For Delay 100 us
    DELAY_XUS(100);

    // Clear to 0
    ScalerSetBit(P8_60_BWR_INT_CTRL, ~(_BIT7 | _BIT3 | _BIT1), 0x00);

    // clr current segment data
    CLR_TTS_DATA_SEGMENT_CURRENT();
}

//--------------------------------------------------
// Description  : TTS SPIC Reset Flow for Int
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsSpicReset_EXINT0(void)
{
    // TTS SPIC Burst data reset
    ScalerSetBit_EXINT(P8_60_BWR_INT_CTRL, ~(_BIT7 | _BIT3 | _BIT1), _BIT7);

    // For Delay 100 us
    DELAY_XUS_EXINT(100);

    // Clear to 0
    ScalerSetBit_EXINT(P8_60_BWR_INT_CTRL, ~(_BIT7 | _BIT3 | _BIT1), 0x00);

    CLR_TTS_DATA_SEGMENT_CURRENT();
}

//--------------------------------------------------
// Description  : TTS SPIC Reset Flow for Int
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsSpicReset_WDINT(void)
{
    // TTS SPIC Burst data reset
    ScalerSetBit_EXINT(P8_60_BWR_INT_CTRL, ~(_BIT7 | _BIT3 | _BIT1), _BIT7);

    // For Delay 100 us
    DELAY_XUS_EXINT(100);

    // Clear to 0
    ScalerSetBit_EXINT(P8_60_BWR_INT_CTRL, ~(_BIT7 | _BIT3 | _BIT1), 0x00);

    CLR_TTS_DATA_SEGMENT_CURRENT();
}
//--------------------------------------------------
// Description  : Audio TTS SPIC blk0 Config for Int
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsSpicBlk0_EXINT0(void)
{
    // increase block 0 current segment data index
    INC_TTS_DATA_SEGMENT_CURRENT();

    ScalerAudioTtsBlk0BurstReadConfig_EXINT0(GET_TTS_DATA_SEGMENT_ADDRESS(GET_TTS_DATA_SEGMENT_CURRENT()), GET_TTS_DATA_SEGMENT_LENGTH(GET_TTS_DATA_SEGMENT_CURRENT()));
}
//--------------------------------------------------
// Description  : Audio TTS SPIC blk1 Config for Int
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsSpicBlk1_EXINT0(void)
{
    // increase block 0 current segment data index
    INC_TTS_DATA_SEGMENT_CURRENT();

    ScalerAudioTtsBlk1BurstReadConfig_EXINT0(GET_TTS_DATA_SEGMENT_ADDRESS(GET_TTS_DATA_SEGMENT_CURRENT()), GET_TTS_DATA_SEGMENT_LENGTH(GET_TTS_DATA_SEGMENT_CURRENT()));
}

//--------------------------------------------------
// Description  : Audio TTS SPIC blk0 read for Int
// Input Value  : ulAddress -- > Data Address
//                usLength -- > Data Length
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsBlk0BurstReadConfig_EXINT0(DWORD ulAddress, WORD usLength)
{
    // Set BW Start Address
    ScalerSetByte_EXINT(P8_62_BLK0_BWR_ADR_4TH, HIBYTE(HIWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_63_BLK0_BWR_ADR_H, LOBYTE(HIWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_64_BLK0_BWR_ADR_M, HIBYTE(LOWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_65_BLK0_BWR_ADR_L, LOBYTE(LOWORD(ulAddress)));

    // Set BW Length
#if(_HW_AUDIO_TTS_BWR_COUNT_GEN == _AUDIO_TTS_BWR_COUNT_GEN_0)
    ScalerSetByte_EXINT(P8_66_BLK0_BWR_COUNT_H, HIBYTE(usLength));
#else
    ScalerSetByte_EXINT(P8_66_BLK0_BWR_COUNT_M, HIBYTE(usLength));
#endif

    ScalerSetByte_EXINT(P8_67_BLK0_BWR_COUNT_L, LOBYTE(usLength));

    // Start BW
    ScalerSetBit_EXINT(P8_61_BWR_CONTROL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Audio TTS SPIC blk1 read for Int
// Input Value  : ulAddress -- > Data Address
//                usLength -- > Data Length
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsBlk1BurstReadConfig_EXINT0(DWORD ulAddress, WORD usLength)
{
    // Set BW Start Address
    ScalerSetByte_EXINT(P8_68_BLK1_BWR_ADR_4TH, HIBYTE(HIWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_69_BLK1_BWR_ADR_H, LOBYTE(HIWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_6A_BLK1_BWR_ADR_M, HIBYTE(LOWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_6B_BLK1_BWR_ADR_L, LOBYTE(LOWORD(ulAddress)));

    // Set BW Length
#if(_HW_AUDIO_TTS_BWR_COUNT_GEN == _AUDIO_TTS_BWR_COUNT_GEN_0)
    ScalerSetByte_EXINT(P8_6C_BLK1_BWR_COUNT_H, HIBYTE(usLength));
#else
    ScalerSetByte_EXINT(P8_6C_BLK1_BWR_COUNT_M, HIBYTE(usLength));
#endif

    ScalerSetByte_EXINT(P8_6D_BLK1_BWR_COUNT_L, LOBYTE(usLength));

    // Start BW
    ScalerSetBit_EXINT(P8_61_BWR_CONTROL, ~_BIT1, _BIT1);
}

//--------------------------------------------------
// Description  : TTS Upsampling Control
// Input Value  : *pstAudioTtsSegment
//                ucSegmentSize
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerAudioTtsGetCommandData(StructAudioTtsSegment *pstAudioTtsSegment, BYTE ucSegmentSize)
{
    BYTE ucCount = 0;

    DebugMessageAudio("[TTS] Set Command Data", ucSegmentSize);

    // Clip the max segment size
    ucSegmentSize = ((ucSegmentSize > _AUDIO_TTS_DATA_SEGMENT_SIZE) ? _AUDIO_TTS_DATA_SEGMENT_SIZE : ucSegmentSize);

    for(ucCount = 0; ((ucCount < ucSegmentSize) && (pstAudioTtsSegment->usDataLength != 0x000000)); ucCount++)
    {
        // Set TTS Data Address & Length
        SET_TTS_DATA_SEGMENT_ADDRESS(ucCount, pstAudioTtsSegment->ulDataAddress);
        SET_TTS_DATA_SEGMENT_LENGTH(ucCount, pstAudioTtsSegment->usDataLength);

        pstAudioTtsSegment++;

        DebugMessageAudio("--------------------------------", ucCount);
        DebugMessageAudio("    - Address", GET_TTS_DATA_SEGMENT_ADDRESS(ucCount));
        DebugMessageAudio("    - Length", GET_TTS_DATA_SEGMENT_LENGTH(ucCount));
    }

    // Set Max TTS Data Number
    SET_TTS_DATA_SEGMENT_TARGET(ucCount);
    CLR_TTS_DATA_SEGMENT_CURRENT();

    DebugMessageAudio("--------------------------------", ucCount);
    DebugMessageAudio("    => Total Data", GET_TTS_DATA_SEGMENT_TARGET());
    DebugMessageAudio("--------------------------------", ucCount);

    return _TRUE;
}

//--------------------------------------------------
// Description  : TTS Upsampling Control
// Input Value  : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsUpsamplingControl(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Enable TTS Upsampling, Set PCM Generatoer, TTS FIFO Normal
        ScalerSetBit(P8_00_TTS_UP_SAMPLING_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Enable TTS FIFO
        ScalerSetBit(P8_02_TTS_UP_SAMPLING_CTRL_3, ~(_BIT3 | _BIT2 | _BIT1), _BIT1);
    }
    else
    {
        // Disable TTS FIFO, Prevent SPI Controller Write Data In.
        ScalerSetBit(P8_02_TTS_UP_SAMPLING_CTRL_3, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

        // Reset PCM Generatoer, TTS FIFO
        ScalerSetBit(P8_00_TTS_UP_SAMPLING_CTRL_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1), 0x00);
    }
}

//--------------------------------------------------
// Description  : TTS Upsampling Control
// Input Value  : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsUpsamplingControl_EXINT0(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Enable TTS Upsampling, Set PCM Generatoer, TTS FIFO Normal
        ScalerSetBit_EXINT(P8_00_TTS_UP_SAMPLING_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Enable TTS FIFO
        ScalerSetBit_EXINT(P8_02_TTS_UP_SAMPLING_CTRL_3, ~(_BIT3 | _BIT2 | _BIT1), _BIT1);
    }
    else
    {
        // Disable TTS FIFO, Prevent SPI Controller Write Data In.
        ScalerSetBit_EXINT(P8_02_TTS_UP_SAMPLING_CTRL_3, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

        // Reset PCM Generatoer, TTS FIFO
        ScalerSetBit_EXINT(P8_00_TTS_UP_SAMPLING_CTRL_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1), 0x00);
    }
}

//--------------------------------------------------
// Description  : TTS Upsampling Control
// Input Value  : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsUpsamplingControl_WDINT(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Enable TTS Upsampling, Set PCM Generatoer, TTS FIFO Normal
        ScalerSetBit_EXINT(P8_00_TTS_UP_SAMPLING_CTRL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Enable TTS FIFO
        ScalerSetBit_EXINT(P8_02_TTS_UP_SAMPLING_CTRL_3, ~(_BIT3 | _BIT2 | _BIT1), _BIT1);
    }
    else
    {
        // Disable TTS FIFO, Prevent SPI Controller Write Data In.
        ScalerSetBit_EXINT(P8_02_TTS_UP_SAMPLING_CTRL_3, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

        // Reset PCM Generatoer, TTS FIFO
        ScalerSetBit_EXINT(P8_00_TTS_UP_SAMPLING_CTRL_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1), 0x00);
    }
}

//--------------------------------------------------
// Description  : TTS Audio Frequency Set By User Define
// Input Value  : EnumAudioSamplingFreqType
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsSetUserDefineAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq)
{
    SET_TTS_SAMPLING_FREQ_USER_DEFINE(enumAudioFreq);
}

//--------------------------------------------------
// Description  : Set TTS Upsampling Data Frequency
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsUpsamplingSetFrequency(void)
{
    EnumAudioSamplingFreqPacket enumSamplingFreqPacket = ScalerAudioSamplingFreqDetect(ScalerAudioGetDigitalAudioPortMapping(_AUDIO_DAC_OUT));

    if(enumSamplingFreqPacket == _AUDIO_FREQ_PACKET_NO_AUDIO)
    {
        enumSamplingFreqPacket = ScalerAudioGetSamplingFreqPacket(GET_TTS_SAMPLING_FREQ_USER_DEFINE());
    }

    switch(enumSamplingFreqPacket)
    {
        case _AUDIO_FREQ_PACKET_32K:
            // Set TTS up sampling Factor By Frequency
#if(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_8_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x04);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0x00);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x00);
#elif(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_16_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x08);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0x00);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x00);
#endif

            // Set PCM Force Gen Sample Counter By Frequency(100ms)
            ScalerSetByte(P8_0A_TTS_UP_SAMPLING_CTRL_6, 0x01);
            ScalerSetByte(P8_0B_TTS_UP_SAMPLING_CTRL_7, 0x3F);

            break;

        case _AUDIO_FREQ_PACKET_44_1K:
            // Set TTS up sampling Factor By Frequency
#if(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_8_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x02);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0xE7);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x09);
#elif(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_16_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x05);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0xCE);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x13);
#endif

            // Set PCM Force Gen Sample Counter By Frequency(100ms)
            ScalerSetByte(P8_0A_TTS_UP_SAMPLING_CTRL_6, 0x01);
            ScalerSetByte(P8_0B_TTS_UP_SAMPLING_CTRL_7, 0x88);

            break;

        case _AUDIO_FREQ_PACKET_48K:
        default:
            // Set TTS up sampling Factor By Frequency
#if(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_8_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x02);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0xAA);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0xAA);
#elif(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_16_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x05);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0x55);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x55);
#endif

            // Set PCM Force Gen Sample Counter By Frequency(100ms)
            ScalerSetByte(P8_0A_TTS_UP_SAMPLING_CTRL_6, 0x01);
            ScalerSetByte(P8_0B_TTS_UP_SAMPLING_CTRL_7, 0xDF);

            break;

        case _AUDIO_FREQ_PACKET_64K:
            // Set TTS up sampling Factor By Frequency
#if(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_8_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x02);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0x00);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x00);
#elif(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_16_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x04);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0x00);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x00);
#endif

            // Set PCM Force Gen Sample Counter By Frequency(100ms)
            ScalerSetByte(P8_0A_TTS_UP_SAMPLING_CTRL_6, 0x02);
            ScalerSetByte(P8_0B_TTS_UP_SAMPLING_CTRL_7, 0x7F);

            break;

        case _AUDIO_FREQ_PACKET_88_2K:
            // Set TTS up sampling Factor By Frequency
#if(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_8_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x01);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0x73);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x84);
#elif(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_16_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x02);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0xE7);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x09);
#endif

            // Set PCM Force Gen Sample Counter By Frequency(100ms)
            ScalerSetByte(P8_0A_TTS_UP_SAMPLING_CTRL_6, 0x03);
            ScalerSetByte(P8_0B_TTS_UP_SAMPLING_CTRL_7, 0x71);

            break;

        case _AUDIO_FREQ_PACKET_96K:
            // Set TTS up sampling Factor By Frequency
#if(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_8_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x01);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0x55);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x55);
#elif(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_16_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x02);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0xAA);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0xAA);
#endif

            // Set PCM Force Gen Sample Counter By Frequency(100ms)
            ScalerSetByte(P8_0A_TTS_UP_SAMPLING_CTRL_6, 0x03);
            ScalerSetByte(P8_0B_TTS_UP_SAMPLING_CTRL_7, 0xBF);

            break;

        case _AUDIO_FREQ_PACKET_128K:
            // Set TTS up sampling Factor By Frequency
#if(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_8_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x01);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0x00);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x00);
#elif(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_16_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x02);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0x00);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x00);
#endif

            // Set PCM Force Gen Sample Counter By Frequency(100ms)
            ScalerSetByte(P8_0A_TTS_UP_SAMPLING_CTRL_6, 0x04);
            ScalerSetByte(P8_0B_TTS_UP_SAMPLING_CTRL_7, 0xFF);

            break;

        case _AUDIO_FREQ_PACKET_176_4K:
            // Set TTS up sampling Factor By Frequency
#if(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_8_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x00);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0xB9);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0xC2);
#elif(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_16_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x01);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0x73);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x84);
#endif

            // Set PCM Force Gen Sample Counter By Frequency(100ms)
            ScalerSetByte(P8_0A_TTS_UP_SAMPLING_CTRL_6, 0x06);
            ScalerSetByte(P8_0B_TTS_UP_SAMPLING_CTRL_7, 0xE3);

            break;

        case _AUDIO_FREQ_PACKET_192K:
            // Set TTS up sampling Factor By Frequency
#if(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_8_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x00);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0xAA);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0xAA);
#elif(_AUDIO_TTS_CONTENT_FREQUENCY == _AUDIO_TTS_CONTENT_16_KHZ)
            ScalerSetByte(P8_06_TTS_SCALE_FACTOR_1, 0x01);
            ScalerSetByte(P8_07_TTS_SCALE_FACTOR_2, 0x55);
            ScalerSetByte(P8_08_TTS_SCALE_FACTOR_3, 0x55);
#endif

            // Set PCM Force Gen Sample Counter By Frequency(100ms)
            ScalerSetByte(P8_0A_TTS_UP_SAMPLING_CTRL_6, 0x07);
            ScalerSetByte(P8_0B_TTS_UP_SAMPLING_CTRL_7, 0x7F);

            break;
    }
}

//--------------------------------------------------
// Description  : TTS Play Done INT Proccess
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsPlayDone_EXINT0(void)
{
    // If TTS IRQ Trigger
    if((ScalerGetBit_EXINT(P8_F0_TTS_CTRL_1, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P8_F0_TTS_CTRL_1, _BIT6) == _BIT6))
    {
        // Disable INT & Clear Flag
        ScalerAudioTtsPlayDoneDetect_EXINT0(_DISABLE);

        // Disable Upsampling
        ScalerAudioTtsUpsamplingControl_EXINT0(_OFF);

        // Reset SPIC
        ScalerAudioTtsSpicReset_EXINT0();

        // Set Play Done Flag
        SET_TTS_PLAY_DONE_FLAG();
    }
}

//--------------------------------------------------
// Description  : TTS SPIC Ping-Pong INT Proccess
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsSpicPingPong_EXINT0(void)
{
    // Last Segment Judgment
    if(GET_TTS_DATA_SEGMENT_CURRENT() >= GET_TTS_DATA_SEGMENT_TARGET())
    {
        // Enable TTS_Play_Done INT
        ScalerAudioTtsPlayDoneDetect_EXINT0(_ENABLE);
    }
    else
    {
        // Disable INT & Clear Flag
        ScalerAudioTtsPlayDoneDetect_EXINT0(_DISABLE);

        // Ping-Pong Operation
        if((ScalerGetBit_EXINT(P8_60_BWR_INT_CTRL, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P8_60_BWR_INT_CTRL, _BIT1) == _BIT1))
        {
            // clear Block 0 irq flag
            // ScalerSetByte_EXINT(P8_60_BWR_INT_CTRL, 0x07);
            ScalerSetBit_EXINT(P8_60_BWR_INT_CTRL, ~(_BIT3 | _BIT1), _BIT1); // TEST!!!

            ScalerAudioTtsSpicBlk0_EXINT0();
        }

        if((ScalerGetBit_EXINT(P8_60_BWR_INT_CTRL, _BIT2) == _BIT2) && (ScalerGetBit_EXINT(P8_60_BWR_INT_CTRL, _BIT3) == _BIT3))
        {
            // clear Block 1 irq flag
            // ScalerSetByte_EXINT(P8_60_BWR_INT_CTRL, 0x0D);
            ScalerSetBit_EXINT(P8_60_BWR_INT_CTRL, ~(_BIT3 | _BIT1), _BIT3); // TEST!!!

            ScalerAudioTtsSpicBlk1_EXINT0();
        }
    }
}

//--------------------------------------------------
// Description  : TTS Play Done Detect Control
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsPlayDoneDetect(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Enable INT
        ScalerSetBit(P8_F0_TTS_CTRL_1, ~(_BIT7 | _BIT6), _BIT7);
    }
    else
    {
        // Disable INT & Clear Flag
        ScalerSetBit(P8_F0_TTS_CTRL_1, ~(_BIT7 | _BIT6), _BIT6);
    }
}

//--------------------------------------------------
// Description  : TTS Play Done Detect Control
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsPlayDoneDetect_EXINT0(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Enable INT
        ScalerSetBit_EXINT(P8_F0_TTS_CTRL_1, ~(_BIT7 | _BIT6), _BIT7);
    }
    else
    {
        // Disable INT & Clear Flag
        ScalerSetBit_EXINT(P8_F0_TTS_CTRL_1, ~(_BIT7 | _BIT6), _BIT6);
    }
}

//--------------------------------------------------
// Description  : TTS WD Event Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsDataPlay_WDINT(void)
{
    // Enable Upsampling
    ScalerAudioTtsUpsamplingControl_WDINT(_ON);

    // Ready to Play Text
    ScalerAudioTtsStartCommandData_WDINT();
}

//--------------------------------------------------
// Description  : TTS Data Start to Play
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsStartCommandData_WDINT(void)
{
    // SPIC get data & Enable ping-pong INT
    ScalerAudioTtsBurstReadStart_WDINT();
}

//--------------------------------------------------
// Description  : TTS INT Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsIntHandler_EXINT0(void)
{
    ScalerAudioTtsPlayDone_EXINT0();

    ScalerAudioTtsSpicPingPong_EXINT0();
}

//--------------------------------------------------
// Description  : TTS SPIC burst read Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsBurstReadStart_WDINT(void)
{
    // Get Total segment count
    BYTE ucSegmentCnt = GET_TTS_DATA_SEGMENT_TARGET();

    // reset SPIC
    ScalerAudioTtsSpicReset_WDINT();

    if(ucSegmentCnt < 2)
    {
        // use block 0
        ScalerAudioTtsBlk0BurstReadConfig_WDINT(GET_TTS_DATA_SEGMENT_ADDRESS(0), GET_TTS_DATA_SEGMENT_LENGTH(0));
    }
    else
    {
        // use block 0/1 ping pang
        ScalerAudioTtsBlk0BurstReadConfig_WDINT(GET_TTS_DATA_SEGMENT_ADDRESS(0), GET_TTS_DATA_SEGMENT_LENGTH(0));
        ScalerAudioTtsBlk1BurstReadConfig_WDINT(GET_TTS_DATA_SEGMENT_ADDRESS(1), GET_TTS_DATA_SEGMENT_LENGTH(1));
    }

    // increase block 0 current segment data index
    INC_TTS_DATA_SEGMENT_CURRENT();
}

//--------------------------------------------------
// Description  : Auido TTS Get burst status
// Input Value  : None
// Output Value : SPIC BW status
//--------------------------------------------------
EnumAudioSpicStatus ScalerAudioTtsGetBurstStatus(void)
{
    if((GET_TTS_DATA_SEGMENT_CURRENT() + 1) == GET_TTS_DATA_SEGMENT_TARGET())
    {
        return _AUDIO_TTS_SPIC_IDLE;
    }
    else
    {
        return _AUDIO_TTS_SPIC_BUSY;
    }
}

//--------------------------------------------------
// Description  : Audio TTS SPIC blk0 read
// Input Value  : ulAddress -- > Data Address
//                usLength -- > Data Length
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsBlk0BurstReadConfig_WDINT(DWORD ulAddress, WORD usLength)
{
    // Set BW Start Address
    ScalerSetByte_EXINT(P8_62_BLK0_BWR_ADR_4TH, HIBYTE(HIWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_63_BLK0_BWR_ADR_H, LOBYTE(HIWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_64_BLK0_BWR_ADR_M, HIBYTE(LOWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_65_BLK0_BWR_ADR_L, LOBYTE(LOWORD(ulAddress)));

    // Set BW Length
#if(_HW_AUDIO_TTS_BWR_COUNT_GEN == _AUDIO_TTS_BWR_COUNT_GEN_0)
    ScalerSetByte_EXINT(P8_66_BLK0_BWR_COUNT_H, HIBYTE(usLength));
#else
    ScalerSetByte_EXINT(P8_66_BLK0_BWR_COUNT_M, HIBYTE(usLength));
#endif

    ScalerSetByte_EXINT(P8_67_BLK0_BWR_COUNT_L, LOBYTE(usLength));

    // Start BW
    ScalerSetBit_EXINT(P8_61_BWR_CONTROL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Audio TTS SPIC blk1 read
// Input Value  : ulAddress -- > Data Address
//                usLength -- > Data Length
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsBlk1BurstReadConfig_WDINT(DWORD ulAddress, WORD usLength)
{
    // Set BW Start Address
    ScalerSetByte_EXINT(P8_68_BLK1_BWR_ADR_4TH, HIBYTE(HIWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_69_BLK1_BWR_ADR_H, LOBYTE(HIWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_6A_BLK1_BWR_ADR_M, HIBYTE(LOWORD(ulAddress)));
    ScalerSetByte_EXINT(P8_6B_BLK1_BWR_ADR_L, LOBYTE(LOWORD(ulAddress)));

    // Set BW Length
#if(_HW_AUDIO_TTS_BWR_COUNT_GEN == _AUDIO_TTS_BWR_COUNT_GEN_0)
    ScalerSetByte_EXINT(P8_6C_BLK1_BWR_COUNT_H, HIBYTE(usLength));
#else
    ScalerSetByte_EXINT(P8_6C_BLK1_BWR_COUNT_M, HIBYTE(usLength));
#endif

    ScalerSetByte_EXINT(P8_6D_BLK1_BWR_COUNT_L, LOBYTE(usLength));

    // Start BW
    ScalerSetBit_EXINT(P8_61_BWR_CONTROL, ~_BIT1, _BIT1);
}

//--------------------------------------------------
// Description  : Get TTS SPIC Burst Data Width
// Input Value  : None
// Output Value : _TTS_DATA_8BIT / _TTS_DATA_16BIT
//--------------------------------------------------
EnumAudioTtsDataWidth ScalerAudioTtsGetDataWidth(void)
{
    // Get Data Width Info
    if(ScalerGetBit(P8_61_BWR_CONTROL, _BIT7) == _BIT7)
    {
        return _AUDIO_TTS_CONTENT_16_BIT;
    }
    else
    {
        return _AUDIO_TTS_CONTENT_8_BIT;
    }
}

//--------------------------------------------------
// Description  : Check Audio TTS Playback Event
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerAudioTtsGetPlaybackEvent(void)
{
    return GET_TTS_PLAYBACK_EVENT_ACTIVE();
}

//--------------------------------------------------
// Description  : Set Audio TTS Playback Event
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsSetPlaybackEvent(bit bEn)
{
    if(bEn == _ENABLE)
    {
        SET_TTS_PLAYBACK_EVENT_ACTIVE();
    }
    else
    {
        CLR_TTS_PLAYBACK_EVENT_ACTIVE();
    }
}

//--------------------------------------------------
// Description  : Set Audio TTS Timer Event
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsSetTimerEvent(bit bEn)
{
    if(bEn == _ENABLE)
    {
        ScalerTimerWDActivateTimerEvent(10, _SCALER_WD_TIMER_EVENT_AUDIO_TTS_PLAYBACK_PROC);
    }
    else
    {
        ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_AUDIO_TTS_PLAYBACK_PROC);
    }
}

//--------------------------------------------------
// Description  : Set Audio TTS Timer Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioTtsClearFlag(void)
{
    // Clear TTS_Play_Done Flag
    CLR_TTS_PLAY_DONE_FLAG();

    // Clear Error Flag
    CLR_TTS_PLAYBACK_ERROR();
}
#endif // End of #if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

