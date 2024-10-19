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
// ID Code      : ScalerDpAudioRx0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_AUDIO_RX0__

#include "ScalerFunctionInclude.h"
#include "DpAudioRx0/ScalerDpAudioRx0.h"

#if(_DP_AUDIO_RX0_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructAudioDigitalInfo g_stDpAudioRx0DigtalInfo;
volatile StructAudioFreqParameter g_stDpAudioRx0FreqParameter;
volatile StructAudioDpCodingType g_stDpAudioRx0CodingType;
volatile StructAudioDpHbrReceiveMode g_stDpAudioRx0HbrReceiveMode;

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
StructAudioDpInternalGen g_stDpAudioRx0InternalGen;
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
volatile StructAudioDpHbrReceiveType g_stDpAudioRx0HbrReceiveType;
volatile StructAudioChannelInfo g_stDpAudioRx0HbrChannelInfo;
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial RX0 DP audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0AudioInitial(void)
{
    ScalerDpAudioRx0SetAudioPLL();

    ScalerDpAudioRx0FifoTrackingInitial();

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpAudioRx0AudioInitial_128b132b();
#endif

    ScalerDpAudioRx0AudioInitial_8b10b();
}

//--------------------------------------------------
// Description  : Initial RX0 DP audio FIFO Tracking
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0FifoTrackingInitial(void)
{
    // Set Maximum N code for Tracking
    ScalerSetByte(PB6_A4_N_F_MAX, LOBYTE(HIWORD(_DP_SAMPLING_FREQ_48K_GROUP_NF_CODE)) + 1);

    // Set Minimum N code for Tracking
    ScalerSetByte(PB6_A5_N_F_MIN, LOBYTE(HIWORD(_DP_SAMPLING_FREQ_44K_GROUP_NF_CODE)) - 1);

    // Set I code of boundary tracking
    ScalerSetBit(PB6_85_AUD_BDRY_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(LOWORD(_DP_INITIAL_I_CODE)) & 0x0F));
    ScalerSetByte(PB6_86_AUD_BDRY_4, LOBYTE(LOWORD(_DP_INITIAL_I_CODE)));

    // Set P code of boundary tracking
    ScalerSetByte(PB6_87_AUD_BDRY_5, 0x12);
    ScalerSetByte(PB6_88_AUD_BDRY_6, 0xFB);
    ScalerSetByte(PB6_89_AUD_BDRY_7, 0xB9);

    // Set I/P code adjustment of trend tracking New Mode
    // Upbound gain control
    ScalerSetBit(PB6_C1_AUD_BDRY_NEW_MODE_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4)); // 3
    ScalerSetBit(PB6_C1_AUD_BDRY_NEW_MODE_1, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1)); // 6
    ScalerSetBit(PB6_C2_AUD_BDRY_NEW_MODE_2, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4)); // 7

    // Lowbound gain control
    ScalerSetBit(PB6_C2_AUD_BDRY_NEW_MODE_2, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0)); // 3
    ScalerSetBit(PB6_C3_AUD_BDRY_NEW_MODE_3, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5)); // 6
    ScalerSetBit(PB6_C3_AUD_BDRY_NEW_MODE_3, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0)); // 7

    // Disable Boundary tracking I/P code adjustment
    ScalerSetBit(PB6_C0_AUD_BDRY_NEW_MODE_0, ~(_BIT1 | _BIT0), 0x00);

    // Disable boundary tracking method
    ScalerSetBit(PB6_82_AUD_BDRY_0, ~_BIT7, 0x00);

    // Set I code of trend tracking
    ScalerSetByte(PB6_94_AUD_TRND_8, 0x00);
    ScalerSetByte(PB6_95_AUD_TRND_9, 0x38);

    // Set P code of trend tracking
    ScalerSetByte(PB6_96_AUD_TRND_10, 0x12);
    ScalerSetByte(PB6_97_AUD_TRND_11, 0xFB);
    ScalerSetByte(PB6_98_AUD_TRND_12, 0xB9);

    // Disable trend tracking method
    ScalerSetBit(PB6_8C_AUD_TRND_0, ~_BIT7, 0x00);

    // Set P Code of P Code Spread
    ScalerSetByte(PB6_9A_P_CODE_SPREAD_1, 0x00);
    ScalerSetByte(PB6_9B_P_CODE_SPREAD_2, 0x10);
    ScalerSetByte(PB6_9C_P_CODE_SPREAD_3, 0x00);

    // Enable P Code Spread
    ScalerSetBit(PB6_99_P_CODE_SPREAD_0, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Set RX0 DP audio FIFO Tracking NF Code
// Input Value  : NF Code
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0FifoTrackingNFCodeConfig(DWORD ulNFCode)
{
    // Set N code of NF PLL
    ScalerSetBit(PB6_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ulNFCode)));

    // Set F code of NF PLL
    ScalerSetByte(PB6_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ulNFCode)));
    ScalerSetByte(PB6_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ulNFCode)));

    // Set Double Buffer for N.F Code
    ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Initial RX0 DP audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0AudioInitial_8b10b(void)
{
    // Disable Audio Output
    ScalerSetByte(PB6_BF_DP_CHANNEL_EN_2, 0x00);

    // Disable Check VBID[4] to Mute Audio by HW and disable Audio FSM
    ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~(_BIT7 | _BIT1), 0x00);

    // Set Sample_Present transmit refers to rs[31]
    CLR_DP_RX0_AUDIO_SP_BIT_FORCE_1_MODE_8B10B();

    // Set Channel_Status transfer to Ch1 auto transmit mode
    SET_DP_RX0_AUDIO_CS_TRANSFER_BY_CH1_8B10B();

    // Set Sample_Present transmit to Frame 0 from DP Source
    ScalerSetBit(PB6_A9_SPDIF_TX_0, ~_BIT6, _BIT6);

    // Set Sample_Present transmit refers to rs[31]
    // Set Preamble transmit refers to rs[29:28]
    ScalerSetBit(PB6_B4_DP_SEC_MISC_2, ~(_BIT5 | _BIT4 | _BIT3), 0x00);

    // Set chst_cat_md to old mode
    ScalerSetBit(_REG_DP14_RX0_AUDIO_SPDIF_TX_REGEN, ~_BIT7, 0x00);

    // Set SPDIF Tx to free_run mode in HBR mode
    ScalerSetBit(PB6_C7_SPDIFTX_FRAME_1, ~(_BIT7 | _BIT3), 0x00);

    // Disable AFD, set 2ms for auto freq. detect and disable 44.1kHz as 48kHz
    ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT0), _BIT2);

    // Set threshold to separate sampling frequency
    ScalerSetByte(PB6_52_AUD_FREQUENY_TH_0, 0x00);
    ScalerSetByte(PB6_53_AUD_FREQUENY_TH_1, 0x00);
    ScalerSetByte(PB6_54_AUD_FREQUENY_TH_2, 0x28);
    ScalerSetByte(PB6_55_AUD_FREQUENY_TH_3, 0x4C);
    ScalerSetByte(PB6_56_AUD_FREQUENY_TH_4, 0x5C);
    ScalerSetByte(PB6_57_AUD_FREQUENY_TH_5, 0x70);

    // Enable RS Decode
    ScalerSetBit(PB6_2B_MN_RS_DEC_CTRL, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set xtal divider for sampling freq. detection
    ScalerSetByte(PB6_51_AUD_FREQUENY_DET_1, _AUTO_FREQ_DETECT_XTAL_DIV);

    // NF code for 32kHz
    ScalerSetByte(PB6_63_N_F_CODE_0, LOBYTE(HIWORD(_DP_SAMPLING_FREQ_32K_GROUP_NF_CODE)));
    ScalerSetByte(PB6_64_N_F_CODE_1, HIBYTE(LOWORD(_DP_SAMPLING_FREQ_32K_GROUP_NF_CODE)));
    ScalerSetByte(PB6_65_N_F_CODE_2, LOBYTE(LOWORD(_DP_SAMPLING_FREQ_32K_GROUP_NF_CODE)));

    // NF code for 44.1kHz
    ScalerSetByte(PB6_66_N_F_CODE_3, LOBYTE(HIWORD(_DP_SAMPLING_FREQ_44K_GROUP_NF_CODE)));
    ScalerSetByte(PB6_67_N_F_CODE_4, HIBYTE(LOWORD(_DP_SAMPLING_FREQ_44K_GROUP_NF_CODE)));
    ScalerSetByte(PB6_68_N_F_CODE_5, LOBYTE(LOWORD(_DP_SAMPLING_FREQ_44K_GROUP_NF_CODE)));

    // NF code for 48kHz
    ScalerSetByte(PB6_69_N_F_CODE_6, LOBYTE(HIWORD(_DP_SAMPLING_FREQ_48K_GROUP_NF_CODE)));
    ScalerSetByte(PB6_6A_N_F_CODE_7, HIBYTE(LOWORD(_DP_SAMPLING_FREQ_48K_GROUP_NF_CODE)));
    ScalerSetByte(PB6_6B_N_F_CODE_8, LOBYTE(LOWORD(_DP_SAMPLING_FREQ_48K_GROUP_NF_CODE)));

    // Enable Audio Buffer & Valid_Bit Detect
    ScalerSetBit(PB6_B0_DP_AUD_CTRL, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

    // Disable Audio Coding Type Change INT
    ScalerSetBit(PB6_3F_DP_IRQ_CTRL1, ~_BIT0, 0x00);

    // Clear Change Flag
    CLR_DP_RX0_AUDIO_CODING_TYPE_CHANGE();

    // Set AUD PKT ID
    ScalerSetByte(PB6_B1_DP_AUD_ID, 0x00);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Set S code by FW manual
    ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, _BIT7);

    // Set D code by FW manual
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // S code for 32kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set NF code of NF PLL
    ScalerDpAudioRx0FifoTrackingNFCodeConfig(_DP_SAMPLING_FREQ_32K_GROUP_NF_CODE);

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // S code for 44.1kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // Set NF code of NF PLL
    ScalerDpAudioRx0FifoTrackingNFCodeConfig(_DP_SAMPLING_FREQ_44K_GROUP_NF_CODE);

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // S code for 48kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set NF code of NF PLL
    ScalerDpAudioRx0FifoTrackingNFCodeConfig(_DP_SAMPLING_FREQ_48K_GROUP_NF_CODE);

#endif

#else

    // Set Double Buffer for N.F Code
    ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

    // Set S code by HW auto
    ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, 0x00);

    // Set D code by HW auto
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), _BIT6);

    // S code for 32kHz
    ScalerSetBit(PB6_58_SCODE_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // S code for 44.1kHz
    ScalerSetBit(PB6_59_SCODE_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // S code for 48kHz
    ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set User Define Frequency When No Audio
    ScalerDpAudioRx0AudioFrequencyMode_8b10b(_AUDIO_TRACKING_MANNUAL_MODE);

#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // DP Audio DVC Mode Setting
    ScalerDpAudioRx0SetDVCVolumeAdjustType_8b10b(_DP_DVC_ADJUST_TYPE);

    // Enable PI control and Enable Auto Load NF Code By AFD
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

    // Disable AFD Function to Judge 88.2/96 and 176.4/192 As Same Range
    ScalerSetBit(PB6_5B_AUD_BURST_IN_CTR, ~(_BIT1 | _BIT0), 0x00);

    // Enable AFD, Disable Audio Sampling Frequency Changed INT
    ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    // Clear Sampling Change Flag at initial flow
    CLR_DP_RX0_AUDIO_SAMPLING_FREQ_CHANGE();

#if(_DIGITAL_AUDIO_OUTPUT_FORCE_CHANNEL_0_1_SUPPORT == _ON)
    // Force I2S/SPDIF Output Form Channel 0/1
    ScalerSetByte(PB6_BC_AUD_CH_LO_SEL, 0x00);
#endif

    // Enable I2S Output
    ScalerSetBit(PB6_B8_DP_I2S_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable SPDIF Output
    ScalerSetBit(PB6_AA_SPDIF_TX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Clear Flag
    CLR_DP_AUDIO_RX0_ICODE_RELOADED();

    CLR_DP_AUDIO_RX0_AUTO_LOAD_FREQ();

    // Clear HBR Mode Change Flag
    CLR_DP_AUDIO_RX0_HBR_RECEIVE_MODE_CHANGE();

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
    // Initial at HBR 8-ch Receive Mode
    ScalerDpAudioRx0HbrModeControl(_OFF);

    CLR_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH();

    CLR_DP_AUDIO_RX0_HBR_OPERATION_DONE();
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    // Reset Frequency Limit Proc
    ScalerDpAudioRx0ResetSamplingFreqLimitProc();
#endif
}

//--------------------------------------------------
// Description  : Set ZCD Timeout for DP Audio
// Input Value  : bAdjustType, enumSamplingFreqPacket
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetDVCWindowSize(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
    {
        ScalerDpAudioRx0SetDVCWindowSize_128b132b(bAdjustType, enumSamplingFreqPacket);
    }
    else
#endif
    {
        ScalerDpAudioRx0SetDVCWindowSize_8b10b(bAdjustType, enumSamplingFreqPacket);
    }
}

//--------------------------------------------------
// Description  : Set ZCD Timeout for DP Audio
// Input Value  : bAdjustType, enumSamplingFreqPacket
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetDVCWindowSize_8b10b(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket)
{
    if(enumSamplingFreqPacket == _AUDIO_FREQ_PACKET_NO_AUDIO)
    {
        enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_48K;
    }

    if(bAdjustType == _DB_GAIN)
    {
        // Get numbers of the volume step for mute or unmute
        PDATA_WORD(0) = _DVC_DB_STEP_NUMBER << 3;
    }
    else
    {
        // Volume Max = 0x3FFF
        PDATA_WORD(0) = 0x3FFF / _DP_VOLUME_STEP_SIZE_VALUE + 1;
    }

    // Calculate samples of ZCD timeout
    PDATA_DWORD(1) = (DWORD)enumSamplingFreqPacket * _DP_DVC_VOLUME_MUTE_TIMER / PDATA_WORD(0);

    // Avoid Overflow
    if(PDATA_DWORD(1) > 0x0FFF)
    {
        PDATA_WORD(0) = 0x0FFF;
    }
    else
    {
        PDATA_WORD(0) = (WORD)PDATA_DWORD(1);
    }

    // Set DVC ZCD window size
    ScalerSetBit(PB6_78_DVC_WINDOW_CONTROL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
    ScalerSetByte(PB6_79_DVC_WINDOW_CONTROL_1, LOBYTE(PDATA_WORD(0)));
}

//--------------------------------------------------
// Description  : Set ZCD Timeout for DP Audio
// Input Value  : bAdjustType, enumSamplingFreqPacket
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetDVCVolumeAdjustType_8b10b(bit bAdjustType)
{
    if(bAdjustType == _DB_GAIN)
    {
        // Select Value Mode to DB Gain Setp
        ScalerSetBit(PB6_76_DVC_CTRL, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | (_DP_DB_GAIN_DOWN_VALUE << 2) | _DP_DB_GAIN_UP_VALUE));

        // Initial Volume Step Size for DB Gain Mode
        ScalerSetByte(PB6_77_DVC_VA, 0x01);
    }
    else // _VOLUME_STEP_SIZE
    {
        // Select Value Mode to Volume Setp
        ScalerSetBit(PB6_76_DVC_CTRL, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

        // Set Volume Step Size
        ScalerSetByte(PB6_77_DVC_VA, _DP_VOLUME_STEP_SIZE_VALUE);
    }

    // DP Audio DVC Window Setting
    ScalerDpAudioRx0SetDVCWindowSize_8b10b(bAdjustType, _AUDIO_FREQ_PACKET_48K);
}

//--------------------------------------------------
// Description  : Detect RX0 digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0DigitalDetectProc(void)
{
    EnumInputPort enumInputPort = ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0);
    EnumAudioSamplingFreqType enumAudioFreq = _AUDIO_FREQ_NO_AUDIO;

    if(ScalerDpAuxRxGetLTStatus(enumInputPort) != _DP_NORMAL_LINK_TRAINING_PASS)
    {
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
        // Reset Frequency Limit Proc
        ScalerDpAudioRx0ResetSamplingFreqLimitProc();
#endif

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
        if(GET_DP_AUDIO_RX0_HBR_OPERATION_DONE() == _TRUE)
        {
            // Clear Channel Status
            memset(&g_stDpAudioRx0HbrChannelInfo, 0, sizeof(g_stDpAudioRx0HbrChannelInfo));

            // Clear Flag
            CLR_DP_AUDIO_RX0_HBR_OPERATION_DONE();
        }
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

        ScalerDpAudioRx0FifoTrackingProc(_DISABLE);

        CLR_DP_AUDIO_RX0_PACKET_DETECT();
        SET_DP_AUDIO_RX0_DIGITAL_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

        if(GET_DP_AUDIO_RX0_ICODE_RELOADED() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_AUDIO_RX0_LOAD_STABLE_I_CODE);

            ScalerDpAudioRx0LoadInitialICode();

            CLR_DP_AUDIO_RX0_ICODE_RELOADED();
        }

        return;
    }

    // Get Audio Sampling Frequency
    enumAudioFreq = ScalerDpAudioRx0SamplingFreqDetect();

    if(enumAudioFreq != _AUDIO_FREQ_NO_AUDIO)
    {
        bit bFifoControl = _ENABLE;

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
        // Check Source Frequency Change or Not
        if(enumAudioFreq != GET_DP_RX0_SOURCE_SAMPLING_FREQ())
        {
            // Disable FIFO Tracking when frequency changes
            ScalerDpAudioRx0FifoTrackingProc(_DISABLE);

            // Record Source Frequency
            SET_DP_RX0_SOURCE_SAMPLING_FREQ(enumAudioFreq);

            // Check Sampling Frequency Limitation
            if(enumAudioFreq <= GET_DP_RX0_SAMPLING_FREQ_LIMIT())
            {
                // Disable Frequency Limit Control
                CLR_DP_RX0_SAMPLING_FREQ_LIMIT_CONTROL();

                // Set Target Frequency to Current Frequency
                ScalerDpAudioRx0SetTargetAudioFrequency(enumAudioFreq);

                DebugMessageAudio("Dp Rx0 Audio Frequency is in the range", 0);
            }
            else
            {
                // Enable Frequency Limit Control
                SET_DP_RX0_SAMPLING_FREQ_LIMIT_CONTROL();

                // Set Target Frequency to User Default Frequency
                ScalerDpAudioRx0SetTargetAudioFrequency(GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE());

                DebugMessageAudio("Dp Rx0 Audio Frequency is Over Limit", 0);
            }
        }

        // Check FIFO Control
        if(GET_DP_RX0_SAMPLING_FREQ_LIMIT_CONTROL() == _TRUE)
        {
            // Disable FIFO Tracking
            bFifoControl = _DISABLE;
        }

#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
        // Get Channel_Status when in first time
        ScalerDpAudioRx0UpdateHbrAudioChannelStatus();
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

        ScalerDpAudioRx0FifoTrackingProc(bFifoControl);

        if(ScalerDpMacStreamRx0GetVbidInfo(_DP_VBID_AUDIO_STREAM) == _TRUE)
        {
            SET_DP_AUDIO_RX0_PACKET_DETECT();
            SET_DP_AUDIO_RX0_DIGITAL_SOURCE(_DIGITAL_AUDIO_SOURCE_DP);

            // Set DP Receive Port1 In Sync
            ScalerDpAuxRxSinkStatusSet(enumInputPort, _DP_SINK_REVEICE_PORT1, _DP_SINK_IN_SYNC);
        }
        else
        {
            CLR_DP_AUDIO_RX0_PACKET_DETECT();
            SET_DP_AUDIO_RX0_DIGITAL_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

            // Set DP Receive Port1 Out Of Sync
            ScalerDpAuxRxSinkStatusSet(enumInputPort, _DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);
        }

        if(GET_DP_AUDIO_RX0_ICODE_RELOADED() == _FALSE)
        {
            ScalerTimerReactiveTimerEvent(_AUDIO_DYNAMIC_I_CODE_TIMER_MS, _SCALER_TIMER_EVENT_DP_AUDIO_RX0_LOAD_STABLE_I_CODE);

            SET_DP_AUDIO_RX0_ICODE_RELOADED();
        }
    }
    else
    {
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
        // Reset Frequency Limit Proc
        ScalerDpAudioRx0ResetSamplingFreqLimitProc();
#endif

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
        if(GET_DP_AUDIO_RX0_HBR_OPERATION_DONE() == _TRUE)
        {
            // Clear Channel Status
            memset(&g_stDpAudioRx0HbrChannelInfo, 0, sizeof(g_stDpAudioRx0HbrChannelInfo));

            // Clear Flag
            CLR_DP_AUDIO_RX0_HBR_OPERATION_DONE();
        }
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

        ScalerDpAudioRx0FifoTrackingProc(_DISABLE);

        if(GET_DP_AUDIO_RX0_DIGITAL_SOURCE() == _DIGITAL_AUDIO_SOURCE_DP)
        {
            // Set DP Receive Port1 Out Of Sync
            ScalerDpAuxRxSinkStatusSet(enumInputPort, _DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);
        }

        CLR_DP_AUDIO_RX0_PACKET_DETECT();
        SET_DP_AUDIO_RX0_DIGITAL_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

        if(GET_DP_AUDIO_RX0_ICODE_RELOADED() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_AUDIO_RX0_LOAD_STABLE_I_CODE);

            ScalerDpAudioRx0LoadInitialICode();

            CLR_DP_AUDIO_RX0_ICODE_RELOADED();
        }
    }
}

//--------------------------------------------------
// Description  : Set RX0 Audio Mute
// Input Value  : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetAudioOutputMute(bit bMute)
{
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerDpAudioRx0GetInternalAudioGenEnable() == _ENABLE)
    {
        ScalerSetByte(PB6_BF_DP_CHANNEL_EN_2, (((!bMute) == _ENABLE) ? 0xFF : 0x00));

        return;
    }
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
    {
        ScalerSetByte(P1B_BF_DP_CHANNEL_EN_2, (((!bMute) == _ENABLE) ? 0xFF : 0x00));
    }
    else
#endif
    {
        ScalerSetByte(PB6_BF_DP_CHANNEL_EN_2, (((!bMute) == _ENABLE) ? 0xFF : 0x00));
    }
}

//--------------------------------------------------
// Description  : Get RX0 Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerDpAudioRx0GetAudioDetected(void)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
    {
        return ScalerDpAudioRx0GetAudioDetected_128b132b();
    }
    else
#endif
    {
        return ScalerDpAudioRx0GetAudioDetected_8b10b();
    }
}

//--------------------------------------------------
// Description  : Get RX0 Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerDpAudioRx0GetAudioDetected_8b10b(void)
{
    // Check audio packet
    if(GET_DP_AUDIO_RX0_PACKET_DETECT() == _FALSE)
    {
        DebugMessageAudio("False : RX0 DP 1.4 Audio Packet", 0);
        return _FALSE;
    }

    // Check Audio FSM
    if(ScalerGetBit(PB6_74_AUD_FSM_CTRL_0, _BIT7) == 0x00)
    {
        DebugMessageAudio("False : RX0 DP 1.4 Audio Fsm Disable", 0);

        return _FALSE;
    }

    // Check Audio Tracking
    if(ScalerGetBit(PB6_82_AUD_BDRY_0, _BIT7) == 0x00)
    {
        DebugMessageAudio("False : RX0 DP 1.4 Audio Tracking Disable", 0);

        return _FALSE;
    }

    // Check DP audio buffer overflow and underflow
    if(ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT2 | _BIT1)) != 0x00)
    {
        DebugMessageAudio("False : RX0 DP 1.4 Audio Buffer", ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT2 | _BIT1)));

        if(ScalerGetBit(PB6_3D_DP_WD_CTRL_1, (_BIT7 | _BIT6)) == 0x00)
        {
            // Clear audio FIFO overflow and underflow status
            ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
            ScalerTimerDelayXms(3);

            if(ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT2 | _BIT1)) != 0x00)
            {
                DebugMessageAudio("False : RX0 DP 1.4 Audio FSM Reset", ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT2 | _BIT1)));

                // Reset Audio FSM
                ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

                // Clear audio FIFO overflow and underflow status
                ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

                // Enable Audio FSM
                ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

                // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
                ScalerTimerDelayXms(3);
            }
        }

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Audio Coding Type By Audio Data
// Input Value  : None
// Output Value : _TRUE => LPCM / _FALSE => NON-LPCM
//--------------------------------------------------
bit ScalerDpAudioRx0LPCMCheckData(void)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
    {
        return ScalerDpAudioRx0LPCMCheckData_128b132b();
    }
    else
#endif
    {
        return ScalerDpAudioRx0LPCMCheckData_8b10b();
    }
}

//--------------------------------------------------
// Description  : Check Audio Coding Type By Audio Data
// Input Value  : None
// Output Value : _TRUE => LPCM / _FALSE => NON-LPCM
//--------------------------------------------------
bit ScalerDpAudioRx0LPCMCheckData_8b10b(void)
{
    // Enable IRQ for Audio Coding Type Change
    if(ScalerGetBit(PB6_3F_DP_IRQ_CTRL1, _BIT0) == 0x00)
    {
        WORD usDelayTime = 12;
        EnumAudioSamplingFreqType enumAudioFreq = ScalerDpAudioRx0SamplingFreqDetect();
        EnumAudioSamplingFreqPacket enumAudioPacket = ScalerAudioGetSamplingFreqPacket(enumAudioFreq);

        // =================================
        // Detect Coding Type at First Time
        // =================================

        DebugMessageAudio("[Audio] Rx0 DP 1.4 Coding Type First Time Detect", 0);


        // -----------------------------
        // Header Byte Detect Flow
        // -----------------------------

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
        // Check IEC61937 HBR Format
        if(GET_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH() == _TRUE)
        {
            // Set Audio Coding Type Source to Channel_Status
            ScalerSetBit(PB6_B0_DP_AUD_CTRL, ~_BIT5, 0x00);

            DebugMessageAudio("[Audio] Rx0 initial at Non-LPCM HBR via HB3[7:4]", 1);

            SET_DP_RX0_AUDIO_CODING_TYPE_FORMAT(_AUDIO_NON_LPCM);

            return _FALSE;
        }
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)


        // -----------------------------
        // Channel Status Detect Flow
        // -----------------------------

        // Set Audio Coding Type Source to Channel_Status
        ScalerSetBit(PB6_B0_DP_AUD_CTRL, ~_BIT5, 0x00);

        // Calculate Minimum Delay for Receiving 192*2 Audio Samples
        // Avoid 0Hz Value
        if(enumAudioPacket == _AUDIO_FREQ_PACKET_NO_AUDIO)
        {
            enumAudioPacket = _AUDIO_FREQ_PACKET_32K;
        }

        // (192Samples * 2) / AudioFreq
        usDelayTime = (192 * 2) / enumAudioPacket;

        // Delay with 2ms margin added
        ScalerTimerDelayXms(usDelayTime + 2);

        // Update Detect Result
        if(ScalerGetBit(PB6_B0_DP_AUD_CTRL, _BIT4) == _BIT4)
        {
            DebugMessageAudio("[Audio] Rx0 initial at Non-LPCM via Channel_Status", 1);

            SET_DP_RX0_AUDIO_CODING_TYPE_FORMAT(_AUDIO_NON_LPCM);
        }
        else
        {
            DebugMessageAudio("[Audio] Rx0 initial at LPCM via Channel_Status", 0);

            SET_DP_RX0_AUDIO_CODING_TYPE_FORMAT(_AUDIO_LPCM);
        }


        // =================================
        // Use HW INT Auto Detect
        // =================================

        // Clear Audio Coding Type Change Flag
        ScalerSetBit(PB6_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

        // Clear Change Flag
        CLR_DP_RX0_AUDIO_CODING_TYPE_CHANGE();

        // Enable Audio Coding Type Change INT
        ScalerSetBit(PB6_3F_DP_IRQ_CTRL1, ~_BIT0, _BIT0);
    }

    // =================================
    // Return Coding Type Status
    // =================================
    if(GET_DP_RX0_AUDIO_CODING_TYPE_FORMAT() == _AUDIO_NON_LPCM)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Audio Coding Type Ever Change
// Input Value  : None
// Output Value : _TRUE => Change / _FALSE => No Change
//--------------------------------------------------
bit ScalerDpAudioRx0LPCMCheckChange(void)
{
    if(GET_DP_RX0_AUDIO_CODING_TYPE_CHANGE() == _TRUE)
    {
        // Clear Change Flag
        CLR_DP_RX0_AUDIO_CODING_TYPE_CHANGE();

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Reset Audio Coding Type Detect INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0LPCMResetProc(void)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Disable Audio Coding Type Change INT
    ScalerSetBit(P1B_3B_DP_IRQ_CTRL1, ~_BIT0, 0x00);
#endif

    // Disable Audio Coding Type Change INT
    ScalerSetBit(PB6_3F_DP_IRQ_CTRL1, ~_BIT0, 0x00);

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
    // Clear Channel Status
    memset(&g_stDpAudioRx0HbrChannelInfo, 0, sizeof(g_stDpAudioRx0HbrChannelInfo));

    // Clear Flag
    CLR_DP_AUDIO_RX0_HBR_OPERATION_DONE();
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
}

//--------------------------------------------------
// Description  : Load initial I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0LoadInitialICode(void)
{
    // Set I code for boundary tracking for DP audio
    ScalerSetBit(PB6_85_AUD_BDRY_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(LOWORD(_DP_INITIAL_I_CODE)) & 0x0F));
    ScalerSetByte(PB6_86_AUD_BDRY_4, LOBYTE(LOWORD(_DP_INITIAL_I_CODE)));

    DebugMessageAudio("Load initial I code", _DP_INITIAL_I_CODE);
}

//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0LoadStableICodeEvent(void)
{
    // Set I code for boundary tracking for DP audio
    ScalerSetBit(PB6_85_AUD_BDRY_3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(LOWORD(_DP_STABLE_I_CODE)) & 0x0F));
    ScalerSetByte(PB6_86_AUD_BDRY_4, LOBYTE(LOWORD(_DP_STABLE_I_CODE)));

    DebugMessageAudio("Load stable I code", _DP_STABLE_I_CODE);
}

//--------------------------------------------------
// Description  : Detect RX0 Audio Sampling Freq
// Input Value  : None
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqType ScalerDpAudioRx0SamplingFreqDetect(void)
{
    EnumAudioSamplingFreqType enumAudioFreq = _AUDIO_FREQ_NO_AUDIO;

#if((_AUDIO_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_SUPPORT == _ON))
    if(ScalerDpAudioRx0GetInternalAudioGenEnable() == _ENABLE)
    {
        // For Audio test pattern
        SET_DP_AUDIO_RX0_SAMPLING_FREQ(GET_AUDIO_GEN_FREQ_MAPPING());
        return GET_AUDIO_GEN_FREQ_MAPPING();
    }
#endif

    // Get Audio Sample Count
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
    {
        enumAudioFreq = (ScalerGetBit(P1B_52_AUD_SAMPLE_CNT_0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
    }
    else
#endif
    {
        enumAudioFreq = (ScalerGetBit(PB6_61_AUD_SAMPLE_CNT_0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
    }

    // HBR Audio Detect
    ScalerDpAudioRx0HbrAudioDetect(enumAudioFreq);

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

    // Check HBR Audio Receive in 8-ch Packet Type
    if(GET_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH() == _TRUE)
    {
        // Transfer 8-ch frequency to 2-ch raw frequency
        enumAudioFreq = ScalerAudioDpRecoverHbrAudioFrequency(enumAudioFreq);
    }

#else

    // Check HBR Receive Mode Change or Not
    if(GET_DP_AUDIO_RX0_HBR_RECEIVE_MODE_CHANGE() == _TRUE)
    {
        // Transfer 8-ch frequency to 2-ch raw frequency
        enumAudioFreq = ScalerAudioDpRecoverHbrAudioFrequency(enumAudioFreq);

        // Clear Change Flag
        CLR_DP_AUDIO_RX0_HBR_RECEIVE_MODE_CHANGE();
    }

#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

    if(enumAudioFreq != GET_DP_AUDIO_RX0_SAMPLING_FREQ())
    {
#if(_EMBEDDED_DAC_SUPPORT == _ON)
        if(enumAudioFreq <= _AUDIO_FREQ_64K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
        else if(enumAudioFreq <= _AUDIO_FREQ_128K)
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT7 | _BIT6), _BIT7);
        }
#endif

        // Audio DVC Setting
        ScalerDpAudioRx0SetDVCWindowSize(_DP_DVC_ADJUST_TYPE, ScalerAudioGetSamplingFreqPacket(enumAudioFreq));
    }

    SET_DP_AUDIO_RX0_SAMPLING_FREQ(enumAudioFreq);

    return enumAudioFreq;
}

//--------------------------------------------------
// Description  : Check Audio Sampling Frequency Ever Change
// Input Value  : None
// Output Value : _TRUE => Change / _FALSE => No Change
//--------------------------------------------------
bit ScalerDpAudioRx0SamplingFreqChange(void)
{
    if(GET_DP_RX0_AUDIO_SAMPLING_FREQ_CHANGE() == _TRUE)
    {
        // Clear Change Flag when check
        CLR_DP_RX0_AUDIO_SAMPLING_FREQ_CHANGE();

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Initial RX0 Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetAudioPLL(void)
{
    // Set Icp, VCO band, O code
    ScalerDpAudioRx0SetAudioPLLOffProc();

    // Set N.F Code
    ScalerDpAudioRx0SetAudioPLLOnProc();
}

//--------------------------------------------------
// Description  : Set RX0 DP Audio On Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetAudioPLLOnProc(void)
{
    // DPLL power up
    ScalerSetBit(PB6_D8_AUDIO_PLL_CONTROL, ~_BIT0, 0x00);

    // Enable VCO/4 clk, Disable High VCO Frequncy, DPLL VCORSTB Set to Normal
    ScalerSetBit(PB6_D8_AUDIO_PLL_CONTROL, ~(_BIT7 | _BIT6 | _BIT1), _BIT7 | (((BYTE)_HW_DPLL_VCORSTB_NORMAL_VALUE) << 1));

    // Set N code of NF PLL
    ScalerSetBit(PB6_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_PLL_N);

    // Set F code of NF PLL
    ScalerSetByte(PB6_A2_AUD_N_F_CODE_2, HIBYTE(_AUDIO_PLL_F));
    ScalerSetByte(PB6_A3_AUD_N_F_CODE_3, LOBYTE(_AUDIO_PLL_F));

    // Set Double Buffer for N.F Code
    ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

    // Select Default Audio Clock to DP 1.4
    ScalerSetBit(PB6_D3_PLL_IN_CONTROL, ~_BIT2, 0x00);

    // Enable DP 1.4 / DP 2.0 Audio Clock
    ScalerSetBit(PB6_D2_PLL_OUT_CONTROL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Set RX0 DP Audio On Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetAudioPLLOffProc(void)
{
    // DPLL power down
    ScalerSetBit(PB6_D8_AUDIO_PLL_CONTROL, ~_BIT0, _BIT0);

    // Reserved for Enable LDO
    // Only LV_Detect Can Control

    // Set DPLL Divider
    ScalerSetBit(PB6_D5_AUDIO_PLL_DIVIDER1, ~(_BIT1 | _BIT0), 0x00);

    //**********************************************************************
    // Pll Parameters Setting
    // Fref = GDI_CLK = 27MHz
    // Target Clock = 939.2172MHz => N = 14, F = 0.5636
    // N = 14 = 12 + 2 => 0x0C
    // F = 0.5636 x 2^16 = 0 => 0x9045
    // Ipi = 2.5uA(315MHz ~ 400MHz)
    // VCO band = 2b'10 (315MHz ~ 400MHz) => Kvco = 1804
    // Icp = (700 * loopdivider * 2 * pi) / (Kvco * Rs)
    // Icp = (700 * 14 * 2 * 3.14) / (1804 * 6.5)
    // Icp = 5.24uA
    //**********************************************************************

    // Set Rs = 6.5k, Cs = 66pF, Icp = 5uA
    ScalerSetBit(PB6_D6_AUDIO_PLL_0, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

    // Initial VCO Band = 2'b10, PI Normal Mode, Ipi = 2.5uA(315 ~ 400MHz)
    ScalerSetBit(PB6_D7_AUDIO_PLL_1, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT5);

    // Set CP Enable, Vc = 0.5V, LPF Enable
    ScalerSetBit(PB6_DA_AUDIO_PLL_DUMMY, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT0));

    // Set VCO Mode
    ScalerSetBit(PB6_D7_AUDIO_PLL_1, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Power Down RX0 Auido PLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0AudioPLLPowerDown(void)
{
    // Disable DP 1.4 / DP 2.0 Audio Clock
    ScalerSetBit(PB6_D2_PLL_OUT_CONTROL, ~(_BIT1 | _BIT0), 0x00);

    // Audio PLL Power Down
    ScalerSetBit(PB6_D8_AUDIO_PLL_CONTROL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : RX0 Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0WatchDogProc(bit bOn)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
    {
        ScalerDpAudioRx0WatchDogProc_128b132b(bOn);
    }
    else
#endif
    {
        ScalerDpAudioRx0WatchDogProc_8b10b(bOn);
    }
}

//--------------------------------------------------
// Description  : RX0 Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0WatchDogProc_8b10b(bit bOn)
{
    if(bOn == _ON)
    {
        // Clear audio buffer overflow and underflow status
        ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Enable Audio Watch Dog for Buffer Overflow/Underflow
        ScalerSetBit(PB6_3D_DP_WD_CTRL_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else
    {
        // Disable Audio Watch Dog for Buffer Overflow/Underflow
        ScalerSetBit(PB6_3D_DP_WD_CTRL_1, ~(_BIT7 | _BIT6), 0x00);

        if(ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT2 | _BIT1)) != 0x00)
        {
            DebugMessageAudio("WD : RX0 DP Audio Over/Underflow", ScalerGetBit(PB6_70_AUD_BUFFER_CTRL_0, (_BIT2 | _BIT1)));

            // Reset Audio FSM
            ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

            // Clear audio FIFO overflow and underflow status
            ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Audio FSM
            ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

            // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
            ScalerTimerDelayXms(3);
        }
    }
}

//--------------------------------------------------
// Description  : RX0 Audio FSM Control
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0AudioEnableControl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable Dp 1.4/2.0 Audio via Channel Coding Type
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
        {
            ScalerSetBit(P1B_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);
        }
        else
#endif
        {
            ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);
        }
    }
    else
    {
        // Disable Both Dp 1.4/2.0 Audio
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerSetBit(P1B_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);
#endif

        ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : RX0 Audio FIFO Tracking Enable Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0FifoTrackingEnableControl_8b10b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set I code of trend tracking
        ScalerSetByte(PB6_94_AUD_TRND_8, 0x00);
        ScalerSetByte(PB6_95_AUD_TRND_9, 0x00);

        // Set P code of trend tracking
        ScalerSetByte(PB6_96_AUD_TRND_10, 0x00);
        ScalerSetByte(PB6_97_AUD_TRND_11, 0x00);
        ScalerSetByte(PB6_98_AUD_TRND_12, 0x00);

        // Set Boundary Tracking Water Level

        // Set boundary tracking water level final upper boound
        ScalerSetBit(PB6_85_AUD_BDRY_3, ~_BIT4, _BIT4);
        ScalerSetByte(PB6_DC_AUD_BDRY_10, 0x4C);

        // Set boundary tracking water level initial upper boound
        ScalerSetBit(PB6_85_AUD_BDRY_3, ~_BIT5, 0x00);
        ScalerSetByte(PB6_8A_AUD_BDRY_8, 0xC0);

        // Set boundary tracking water level Target Depth
        ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(PB6_71_AUD_BUFFER_CTRL_1, 0xB0);

        // Set boundary tracking water level initial lower boound
        ScalerSetByte(PB6_8B_AUD_BDRY_9, 0xA0);

        // Set boundary tracking water level final lower boound
        ScalerSetByte(PB6_DE_AUD_BDRY_11, 0x14);

        // Set boundary tracking Step for next boundary threshold
        ScalerSetBit(PB6_82_AUD_BDRY_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

        // Enable Boundary Tracking Method
        ScalerSetBit(PB6_82_AUD_BDRY_0, ~_BIT7, _BIT7);

        // Disable Boundary tracking I/P code adjustment
        ScalerSetBit(PB6_C0_AUD_BDRY_NEW_MODE_0, ~(_BIT1 | _BIT0), 0x00);

        // Enable Trend Tracking Method
        ScalerSetBit(PB6_8C_AUD_TRND_0, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable Boundary Tracking Method
        ScalerSetBit(PB6_82_AUD_BDRY_0, ~_BIT7, 0x00);

        // Disable Boundary tracking I/P code adjustment
        ScalerSetBit(PB6_C0_AUD_BDRY_NEW_MODE_0, ~(_BIT1 | _BIT0), 0x00);

        // Disable Trend Tracking Method
        ScalerSetBit(PB6_8C_AUD_TRND_0, ~_BIT7, 0x00);

        // Set Double Buffer for N.F Code
        ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : RX0 Audio FIFO Tracking Proc
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0FifoTrackingProc(bit bEnable)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
    {
        ScalerDpAudioRx0FifoTrackingProc_128b132b(bEnable);
    }
    else
#endif
    {
        ScalerDpAudioRx0FifoTrackingProc_8b10b(bEnable);
    }
}

//--------------------------------------------------
// Description  : RX0 Audio FIFO Tracking Proc
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0FifoTrackingProc_8b10b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        if(GET_DP_AUDIO_RX0_AUTO_LOAD_FREQ() == _FALSE)
        {
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

            // -----------------------------------------
            // Set Fix Frequency to Current Frequency
            // -----------------------------------------
            ScalerDpAudioRx0AudioFrequencyMode_8b10b(_AUDIO_TRACKING_MANNUAL_MODE_FIX_TARGET_FREQ);

#else

            // -----------------------------------------
            // Set HW Auto Load Frequency
            // -----------------------------------------
            ScalerDpAudioRx0AudioFrequencyMode_8b10b(_AUDIO_TRACKING_AUTO_LOAD_MODE);

#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

            // Set Auto Load Done Flag
            SET_DP_AUDIO_RX0_AUTO_LOAD_FREQ();

            DebugMessageAudio("Dp Rx0 Audio Auto_Load Mode", 0);
        }
#endif

        if(ScalerGetBit(PB6_82_AUD_BDRY_0, _BIT7) == 0x00)
        {
            // -----------------------------------------
            // Enable Tracking Function
            // -----------------------------------------

            // Select Audio Clock to DP 1.4
            ScalerSetBit(PB6_D3_PLL_IN_CONTROL, ~_BIT2, 0x00);

            // Disable INT for Auido Sampling Change
            ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), 0x00);

            // Disable Audio FSM
            ScalerDpAudioRx0AudioEnableControl(_DISABLE);

            DELAY_5US();

            // Enable FIFO Tracking
            ScalerDpAudioRx0FifoTrackingEnableControl_8b10b(_ENABLE);

            // Enable Audio FSM
            ScalerDpAudioRx0AudioEnableControl(_ENABLE);

            // Wait for New Audio Packet Recive 4 times via detect interval + 1ms
            ScalerTimerDelayXms(((ScalerGetBit(PB6_50_AUD_FREQUENY_DET_0, (_BIT3 | _BIT2)) >> 2) + 1) * 4 + 1);

            // Clear Auido Sampling Change Flag
            ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);

            // Enable INT for Auido Sampling Change
            ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), _BIT6);

            DebugMessageAudio("Dp Rx0 Audio Tracking Enable", 0);
        }
    }
    else
    {
        if(ScalerGetBit(PB6_82_AUD_BDRY_0, _BIT7) == _BIT7)
        {
            // -----------------------------------------
            // Disable Tracking Function
            // -----------------------------------------

            // Disable INT for Auido Sampling Change
            ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), 0x00);

            // Disable FIFO Tracking
            ScalerDpAudioRx0FifoTrackingEnableControl_8b10b(_DISABLE);

            DebugMessageAudio("Dp Rx0 Audio Tracking Disable", 0);
        }

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        if(GET_DP_AUDIO_RX0_AUTO_LOAD_FREQ() == _TRUE)
        {
            // -----------------------------------------
            // Set User Define Frequency When No Audio
            // -----------------------------------------
            ScalerDpAudioRx0AudioFrequencyMode_8b10b(_AUDIO_TRACKING_MANNUAL_MODE);

            // Clear Auto Load Done Flag
            CLR_DP_AUDIO_RX0_AUTO_LOAD_FREQ();

            DebugMessageAudio("Dp Rx0 Audio Manual Mode", 0);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : RX0 Audio Frequency Mode Setting
// Input Value  : _AUDIO_TRACKING_AUTO_LOAD_MODE / _AUDIO_TRACKING_MANNUAL_MODE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0AudioFrequencyMode_8b10b(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode)
{
    if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_AUTO_LOAD_MODE)
    {
        // Set S code by HW auto
        ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, 0x00);

        // Set D code by HW auto
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), _BIT6);

        // S code for 48kHz
        ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set N code of NF PLL
        ScalerSetBit(PB6_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));

        // Set F code of NF PLL
        ScalerSetByte(PB6_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));
        ScalerSetByte(PB6_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);
    }
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    else if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_MANNUAL_MODE_FIX_TARGET_FREQ)
    {
        // S code for Current Frequency
        ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerAudioGetUserSamplingFreqSCode(_PORT_DP, GET_DP_RX0_TARGET_SAMPLING_FREQ()));

        // Set N code of NF PLL
        ScalerSetBit(PB6_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_TARGET_SAMPLING_FREQ()))));

        // Set F code of NF PLL
        ScalerSetByte(PB6_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_TARGET_SAMPLING_FREQ()))));
        ScalerSetByte(PB6_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_TARGET_SAMPLING_FREQ()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

        // Set S code by FW manual
        ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, _BIT7);

        // Set D code by FW manual
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), 0x00);
    }
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    else
    {
        // S code for User Define
        ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerAudioGetUserSamplingFreqSCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()));

        // Set N code of NF PLL
        ScalerSetBit(PB6_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));

        // Set F code of NF PLL
        ScalerSetByte(PB6_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));
        ScalerSetByte(PB6_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

        // Set S code by FW manual
        ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, _BIT7);

        // Set D code by FW manual
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), 0x00);
    }
}

//--------------------------------------------------
// Description  : RX0 Audio Frequency Set By User Define
// Input Value  : ucSCode / ulNFCode
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetUserDefineAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq)
{
    SET_DP_RX0_SAMPLING_FREQ_USER_DEFINE(enumAudioFreq);
}

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : RX0 Audio Frequency Limitation Set By User Define
// Input Value  : enumAudioFreq
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetUserDefineSamplingFreqLimit(EnumAudioSamplingFreqType enumAudioFreq)
{
    SET_DP_RX0_SAMPLING_FREQ_LIMIT(enumAudioFreq);
}

//--------------------------------------------------
// Description  : RX0 Audio Target Frequency Record
// Input Value  : enumAudioFreq
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetTargetAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq)
{
    SET_DP_RX0_TARGET_SAMPLING_FREQ(enumAudioFreq);
}

//--------------------------------------------------
// Description  : RX0 Audio Frequency Limitation Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0ResetSamplingFreqLimitProc(void)
{
    // Reset Frequency Limit Control Flag
    CLR_DP_RX0_SAMPLING_FREQ_LIMIT_CONTROL();

    // Reset Frequency Record
    SET_DP_RX0_SOURCE_SAMPLING_FREQ(_AUDIO_FREQ_NO_AUDIO);
    SET_DP_RX0_TARGET_SAMPLING_FREQ(_AUDIO_FREQ_NO_AUDIO);
}
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Set User Define Audio Frequency S/N.F Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SyncUserDefineFrequencyPllSetting(void)
{
    if(GET_DP_AUDIO_RX0_AUTO_LOAD_FREQ() == _FALSE)
    {
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
        {
            ScalerDpAudioRx0AudioFrequencyMode_128b132b(_AUDIO_TRACKING_MANNUAL_MODE);
        }
        else
#endif
        {
            ScalerDpAudioRx0AudioFrequencyMode_8b10b(_AUDIO_TRACKING_MANNUAL_MODE);
        }
    }
}

//--------------------------------------------------
// Description  : RX0 Audio HBR Packet Detect
// Input Value  : EnumAudioSamplingFreqType
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0HbrAudioDetect(EnumAudioSamplingFreqType enumAudioFreq)
{
    // Enable Dp 1.4/2.0 Audio HBR Detect via Channel Coding Type
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
    {
        // Check HBR Audio Receive
        if((enumAudioFreq != _AUDIO_FREQ_NO_AUDIO) && (ScalerGetBit(P1B_5F_SDP_AUD_STR_HB3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == _BIT4))
        {
#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
            // Set 8-ch HBR Packet Flag
            SET_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH();
#else
            // Check Current Detect Mode
            if(ScalerGetBit(P1B_C8_DP_AUD_CTRL, _BIT6) != _BIT6)
            {
                // Enable Audio HBR Mode Detect
                ScalerDpAudioRx0HbrModeControl(_ON);

                // Wait for New Audio Packet Recived via detect interval + 1ms
                ScalerTimerDelayXms(((ScalerGetBit(P1B_50_AUD_FREQUENY_DET_0, (_BIT3 | _BIT2)) >> 2) + 1) + 1);

                // Set Mode Change
                SET_DP_AUDIO_RX0_HBR_RECEIVE_MODE_CHANGE();

                DebugMessageAudio("Dp Rx0 2.0 HBR Mode Detect Enable", _ENABLE);
            }
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
        }
        else
        {
            // Check Current Detect Mode
            if(ScalerGetBit(P1B_C8_DP_AUD_CTRL, _BIT6) != 0x00)
            {
                // Disable Audio HBR Mode Detect
                ScalerDpAudioRx0HbrModeControl(_OFF);

                // Wait for New Audio Packet Recived via detect interval + 1ms
                ScalerTimerDelayXms(((ScalerGetBit(P1B_50_AUD_FREQUENY_DET_0, (_BIT3 | _BIT2)) >> 2) + 1) + 1);

                // Set Mode Change
                SET_DP_AUDIO_RX0_HBR_RECEIVE_MODE_CHANGE();

                DebugMessageAudio("Dp Rx0 2.0 HBR Mode Detect Disable", _DISABLE);
            }

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
            // Clear 8-ch HBR Packet Flag
            CLR_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH();
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
        }
    }
    else
#endif
    {
        // Check HBR Audio Receive
        if((enumAudioFreq != _AUDIO_FREQ_NO_AUDIO) && (ScalerGetBit(PB6_CF_SDP_AUD_STR_HB3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == _BIT4))
        {
#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
            // Set 8-ch HBR Packet Flag
            SET_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH();
#else
            // Check Current Detect Mode
            if(ScalerGetBit(PB6_B0_DP_AUD_CTRL, _BIT6) != _BIT6)
            {
                // Enable Audio HBR Mode Detect
                ScalerDpAudioRx0HbrModeControl(_ON);

                // Wait for New Audio Packet Recived via detect interval + 1ms
                ScalerTimerDelayXms(((ScalerGetBit(PB6_50_AUD_FREQUENY_DET_0, (_BIT3 | _BIT2)) >> 2) + 1) + 1);

                // Set Mode Change
                SET_DP_AUDIO_RX0_HBR_RECEIVE_MODE_CHANGE();

                DebugMessageAudio("Dp Rx0 1.4 HBR Mode Detect Enable", _ENABLE);
            }
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
        }
        else
        {
            // Check Current Detect Mode
            if(ScalerGetBit(PB6_B0_DP_AUD_CTRL, _BIT6) != 0x00)
            {
                // Disable Audio HBR Mode Detect
                ScalerDpAudioRx0HbrModeControl(_OFF);

                // Wait for New Audio Packet Recived via detect interval + 1ms
                ScalerTimerDelayXms(((ScalerGetBit(PB6_50_AUD_FREQUENY_DET_0, (_BIT3 | _BIT2)) >> 2) + 1) + 1);

                // Set Mode Change
                SET_DP_AUDIO_RX0_HBR_RECEIVE_MODE_CHANGE();

                DebugMessageAudio("Dp Rx0 1.4 HBR Mode Detect Disable", _DISABLE);
            }

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
            // Clear 8-ch HBR Packet Flag
            CLR_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH();
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
        }
    }
}

//--------------------------------------------------
// Description  : RX0 Audio HBR Mode Control
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0HbrModeControl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable Dp 1.4/2.0 Audio HBR Mode Detect via Channel Coding Type
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
        {
            ScalerSetBit(P1B_C8_DP_AUD_CTRL, ~(_BIT6 | _BIT1 | _BIT0), _BIT6);
        }
        else
#endif
        {
            ScalerSetBit(PB6_B0_DP_AUD_CTRL, ~_BIT6, _BIT6);
        }
    }
    else
    {
        // Disable Audio HBR Mode Detect
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerSetBit(P1B_C8_DP_AUD_CTRL, ~(_BIT6 | _BIT1 | _BIT0), 0x00);
#endif

        ScalerSetBit(PB6_B0_DP_AUD_CTRL, ~_BIT6, 0x00);
    }
}

//--------------------------------------------------
// Description  : Audio SDP Contains Pakage Number
// Input Value  : None
// Output Value : _TRUE ->Use first 16 byte
//                _FALSE->Use second 16 byte
//--------------------------------------------------
BYTE ScalerDpAudioRx0GetAudioInfoFrame(EnumAudioInfoContent enumAudioInfoContent)
{
    BYTE ucAudioInfoSdpData = 0;
    BYTE ucAudioInfoContent = enumAudioInfoContent;

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
    {
        // Check ISRC Offset
        if(ScalerGetBit(P1B_E3_SDP_ISRC_0, _BIT3) == _BIT3)
        {
            // ISRC SDP Contains Second 16Byte[31:16]
            ucAudioInfoContent = (ucAudioInfoContent + 16);
        }
    }
    else
#endif
    {
        // Check ISRC Offset
        if(ScalerGetBit(PB6_E3_SDP_ISRC_0, _BIT3) == _BIT3)
        {
            // ISRC SDP Contains Second 16Byte[31:16]
            ucAudioInfoContent = (enumAudioInfoContent + 16);
        }
    }

    // Get SDP Audio Infoframe for Channel Allocation
    ScalerDpMacStreamRx0GetSdpPktData(_DP_SDP_TYPE_INFOFRAME_AUDIO, &ucAudioInfoSdpData, ucAudioInfoContent, 1);

    // DebugMessageAudio("Audio RX0: InfoFrame SDP Data", ucAudioInfoSdpData);

    return ucAudioInfoSdpData;
}

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
//--------------------------------------------------
// Description  : Update Audio Channel Status of Rx Port
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0UpdateHbrAudioChannelStatus(void)
{
    // Check HBR Audio Receive in 8-ch Packet Type
    if(GET_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH() == _FALSE)
    {
        return;
    }

    // Check HBR Operation in First Time
    if(GET_DP_AUDIO_RX0_HBR_OPERATION_DONE() == _TRUE)
    {
        return;
    }

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
    {
        DebugMessageAudio("[Audio] Rx0 DP 2.0 Update HBR channel status", 0);

        // Disable INT for Auido Sampling Change
        ScalerSetBit(P1B_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), 0x00);

        ScalerDpAudioRx0FifoTrackingProc_128b132b(_DISABLE);

        // Enable Dp 2.0 Audio HBR Mode Detect via Channel Coding Type
        ScalerSetBit(P1B_C8_DP_AUD_CTRL, ~(_BIT6 | _BIT1 | _BIT0), _BIT6);

        // Load Ch1 Channel_Status
        ScalerSetBit(P1B_AD_SPDIF_CS_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

        // Delay with 48kHz@8-ch HBR Audio(6.144Mbps) and add 2ms margin
        // Delay Time = ((192Samples * 2) / 48kHz) + 2ms
        ScalerTimerDelayXms(10);

        // Get Channel_Status[7:0]
        ScalerSetByte(P1B_AB_CS_ADDR, 0x33);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_0(ScalerGetByte(P1B_AC_CS_DATA));

        // Get Channel_Status[15:8]
        ScalerSetByte(P1B_AB_CS_ADDR, 0x32);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_1(ScalerGetByte(P1B_AC_CS_DATA));

        // Get Channel_Status[23:16]
        ScalerSetByte(P1B_AB_CS_ADDR, 0x31);
        // Channel_Status[23:20] Set Dummy and Reference by AudioChannelNumStaus1 ~ 8
        SET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_2(ScalerGetByte(P1B_AC_CS_DATA) & 0x0F);

        // Get Channel_Status[31:24]
        ScalerSetByte(P1B_AB_CS_ADDR, 0x30);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_3(ScalerGetByte(P1B_AC_CS_DATA));

        // Get Channel_Status[39:32]
        ScalerSetByte(P1B_AB_CS_ADDR, 0x2F);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_4(ScalerGetByte(P1B_AC_CS_DATA));

        // Get Channel_Number 1/2
        ScalerSetByte(P1B_AB_CS_ADDR, 0x34);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_12(ScalerGetByte(P1B_AC_CS_DATA));

        // Get Channel_Number 3/4
        ScalerSetByte(P1B_AB_CS_ADDR, 0x35);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_34(ScalerGetByte(P1B_AC_CS_DATA));

        // Get Channel_Number 5/6
        ScalerSetByte(P1B_AB_CS_ADDR, 0x36);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_56(ScalerGetByte(P1B_AC_CS_DATA));

        // Get Channel_Number 7/8
        ScalerSetByte(P1B_AB_CS_ADDR, 0x37);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_78(ScalerGetByte(P1B_AC_CS_DATA));

        // Disable Audio HBR Mode Detect
        ScalerSetBit(P1B_C8_DP_AUD_CTRL, ~(_BIT6 | _BIT1 | _BIT0), 0x00);

        // Reset Audio FSM
        ScalerSetBit(P1B_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

        // Clear audio FIFO overflow and underflow status
        ScalerSetBit(P1B_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Enable Audio FSM
        ScalerSetBit(P1B_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

        // Wait for New Audio Packet Recived 2 times via detect interval + 1ms
        ScalerTimerDelayXms(((ScalerGetBit(P1B_50_AUD_FREQUENY_DET_0, (_BIT3 | _BIT2)) >> 2) + 1) * 3 + 1);

        // Clear Auido Sampling Change Flag
        ScalerSetBit(P1B_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);
    }
    else
#endif
    {
        DebugMessageAudio("[Audio] Rx0 DP 1.4 Update HBR channel status", 0);

        // Disable INT for Auido Sampling Change
        ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), 0x00);

        ScalerDpAudioRx0FifoTrackingProc_8b10b(_DISABLE);

        // Enable Dp 1.4 Audio HBR Mode Detect via Channel Coding Type
        ScalerSetBit(PB6_B0_DP_AUD_CTRL, ~_BIT6, _BIT6);

        // Load Ch1 Channel_Status
        ScalerSetBit(PB6_AD_SPDIF_CS_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

        // Delay with 48kHz@8-ch HBR Audio(6.144Mbps) and add 2ms margin
        // Delay Time = ((192Samples * 2) / 48kHz) + 2ms
        ScalerTimerDelayXms(10);

        // Get Channel_Status[7:0]
        ScalerSetByte(PB6_AB_CS_ADDR, 0x33);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_0(ScalerGetByte(PB6_AC_CS_DATA));

        // Get Channel_Status[15:8]
        ScalerSetByte(PB6_AB_CS_ADDR, 0x32);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_1(ScalerGetByte(PB6_AC_CS_DATA));

        // Get Channel_Status[23:16]
        ScalerSetByte(PB6_AB_CS_ADDR, 0x31);
        // Channel_Status[23:20] Set Dummy and Reference by AudioChannelNumStaus1 ~ 8
        SET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_2(ScalerGetByte(PB6_AC_CS_DATA) & 0x0F);

        // Get Channel_Status[31:24]
        ScalerSetByte(PB6_AB_CS_ADDR, 0x30);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_3(ScalerGetByte(PB6_AC_CS_DATA));

        // Get Channel_Status[39:32]
        ScalerSetByte(PB6_AB_CS_ADDR, 0x2F);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_4(ScalerGetByte(PB6_AC_CS_DATA));

        // Get Channel_Number 1/2
        ScalerSetByte(PB6_AB_CS_ADDR, 0x34);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_12(ScalerGetByte(PB6_AC_CS_DATA));

        // Get Channel_Number 3/4
        ScalerSetByte(PB6_AB_CS_ADDR, 0x35);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_34(ScalerGetByte(PB6_AC_CS_DATA));

        // Get Channel_Number 5/6
        ScalerSetByte(PB6_AB_CS_ADDR, 0x36);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_56(ScalerGetByte(PB6_AC_CS_DATA));

        // Get Channel_Number 7/8
        ScalerSetByte(PB6_AB_CS_ADDR, 0x37);
        SET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_78(ScalerGetByte(PB6_AC_CS_DATA));

        // Disable Audio HBR Mode Detect
        ScalerSetBit(PB6_B0_DP_AUD_CTRL, ~_BIT6, 0x00);

        // Reset Audio FSM
        ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

        // Clear audio FIFO overflow and underflow status
        ScalerSetBit(PB6_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Enable Audio FSM
        ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

        // Wait for New Audio Packet Recived 2 times via detect interval + 1ms
        ScalerTimerDelayXms(((ScalerGetBit(PB6_50_AUD_FREQUENY_DET_0, (_BIT3 | _BIT2)) >> 2) + 1) * 3 + 1);

        // Clear Auido Sampling Change Flag
        ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);
    }

    // Synchronize HBR Operation Flag
    SET_DP_AUDIO_RX0_HBR_OPERATION_DONE();

    // Show HBR Audio Channel Status
    DebugMessageAudio("  - Channel Status 0", GET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_0());
    DebugMessageAudio("  - Channel Status 1", GET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_1());
    DebugMessageAudio("  - Channel Status 2", GET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_2());
    DebugMessageAudio("  - Channel Status 3", GET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_3());
    DebugMessageAudio("  - Channel Status 4", GET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_4());
    DebugMessageAudio("  - Channel Number 1/2", GET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_12());
    DebugMessageAudio("  - Channel Number 3/4", GET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_34());
    DebugMessageAudio("  - Channel Number 5/6", GET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_56());
    DebugMessageAudio("  - Channel Number 7/8", GET_DP_AUDIO_RX0_HBR_CHANNEL_NUMBER_78());
}
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

//--------------------------------------------------
// Description  : Get Rx0 Audio Channel Status
// Input Value  : None
// Output Value : Channel Status
//--------------------------------------------------
StructAudioChannelInfo ScalerDpAudioRx0GetChannelStatus(void)
{
    StructAudioChannelInfo stAudioStatus = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
    // Return backup channel status when in HBR audio
    if(GET_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH() == _TRUE)
    {
        return GET_DP_AUDIO_RX0_HBR_CHANNEL_STATUS_TOTAL();
    }
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
    {
#if(_HW_DP_AUDIO_CHANNEL_STATUS_1S1D2S_RECEIVE_SUPPORT == _OFF)
        EnumAudioChannelCount enumChannelCount = ScalerGetBit(P1B_5F_SDP_AUD_STR_HB3, (_BIT2 | _BIT1 | _BIT0));
        EnumAudioSamplingFreqType enumAudioFreq = (EnumAudioSamplingFreqType)GET_DP_AUDIO_RX0_SAMPLING_FREQ();
        EnumAudioCodingType enumCodingType = GET_DP_RX0_AUDIO_CODING_TYPE_FORMAT();

        // Check if audio coding type is matching 2-Ch L-PCM audio
        if((enumCodingType == _AUDIO_LPCM) && (enumChannelCount <= _AUDIO_CHANNEL_COUNT_2))
        {
            DebugMessageAudio("[Audio] Rx0 DP 2.0 channel status re-write", 0);

            // Set Channel_Status[7:0]
            // [1:0] = 2'b00, IEC 60958-3(consumer application)
            // [2] = 1'b1, software for which no copyright
            // [5:3] = 3'b000, 2 audio channels without pre-emphasis
            // [7:6] = 2'b00, mode 0(channel status is for consumer use)
            stAudioStatus.ucChannelStaus0 = 0x04;

            // Set Channel_Status[15:8]
            // [15:8] = 8'b00000000, general, used temporarily
            stAudioStatus.ucChannelStaus1 = 0x00;

            // Set Channel_Status[23:16]
            // [19:16] = 4'b0000, source number do not take into account
            // [23:20] = 4'b0000, channel number do not take into account(refers to AudioChannelNumStaus1 ~ 8)
            stAudioStatus.ucChannelStaus2 = 0x00;

            // Set Channel_Status[31:24]
            ScalerAudioSetChannelStatusFrequency(enumAudioFreq, &stAudioStatus);

            // Get Channel_Status[39:32]
            // [32] = 1'b0, maximum audio sample word length is 20 bits
            // [35:33] = 3'b000, audio sample word length is not indicated
            // [39:36] = 4'b0000, original sampling frequency is not indicated
            stAudioStatus.ucChannelStaus4 = 0x00;

            // Set Channel Number via Header Byte
            ScalerAudioSetChannelStatusNumber(enumChannelCount, &stAudioStatus);
        }
        else
#endif // End of #if(_HW_DP_AUDIO_CHANNEL_STATUS_1S1D2S_RECEIVE_SUPPORT == _OFF)
        {
            DebugMessageAudio("[Audio] Rx0 DP 2.0 channel status bypass", 0);

            // Load Ch1 Channel_Status
            ScalerSetBit(P1B_AD_SPDIF_CS_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // Get Channel_Status[7:0]
            ScalerSetByte(P1B_AB_CS_ADDR, 0x33);
            stAudioStatus.ucChannelStaus0 = ScalerGetByte(P1B_AC_CS_DATA);

            // Get Channel_Status[15:8]
            ScalerSetByte(P1B_AB_CS_ADDR, 0x32);
            stAudioStatus.ucChannelStaus1 = ScalerGetByte(P1B_AC_CS_DATA);

            // Get Channel_Status[23:16]
            ScalerSetByte(P1B_AB_CS_ADDR, 0x31);
            // Channel_Status[23:20] Set Dummy and Reference by AudioChannelNumStaus1 ~ 8
            stAudioStatus.ucChannelStaus2 = (ScalerGetByte(P1B_AC_CS_DATA) & 0x0F);

            // Get Channel_Status[31:24]
            ScalerSetByte(P1B_AB_CS_ADDR, 0x30);
            stAudioStatus.ucChannelStaus3 = ScalerGetByte(P1B_AC_CS_DATA);

            // Get Channel_Status[39:32]
            ScalerSetByte(P1B_AB_CS_ADDR, 0x2F);
            stAudioStatus.ucChannelStaus4 = ScalerGetByte(P1B_AC_CS_DATA);

            // Get Channel_Number 1/2
            ScalerSetByte(P1B_AB_CS_ADDR, 0x34);
            stAudioStatus.ucChannelNumber12 = ScalerGetByte(P1B_AC_CS_DATA);

            // Get Channel_Number 3/4
            ScalerSetByte(P1B_AB_CS_ADDR, 0x35);
            stAudioStatus.ucChannelNumber34 = ScalerGetByte(P1B_AC_CS_DATA);

            // Get Channel_Number 5/6
            ScalerSetByte(P1B_AB_CS_ADDR, 0x36);
            stAudioStatus.ucChannelNumber56 = ScalerGetByte(P1B_AC_CS_DATA);

            // Get Channel_Number 7/8
            ScalerSetByte(P1B_AB_CS_ADDR, 0x37);
            stAudioStatus.ucChannelNumber78 = ScalerGetByte(P1B_AC_CS_DATA);
        }
    }
    else
#endif
    {
        DebugMessageAudio("[Audio] Rx0 DP 1.4 channel status bypass", 0);

        // Load Ch1 Channel_Status
        ScalerSetBit(PB6_AD_SPDIF_CS_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

        // Get Channel_Status[7:0]
        ScalerSetByte(PB6_AB_CS_ADDR, 0x33);
        stAudioStatus.ucChannelStaus0 = ScalerGetByte(PB6_AC_CS_DATA);

        // Get Channel_Status[15:8]
        ScalerSetByte(PB6_AB_CS_ADDR, 0x32);
        stAudioStatus.ucChannelStaus1 = ScalerGetByte(PB6_AC_CS_DATA);

        // Get Channel_Status[23:16]
        ScalerSetByte(PB6_AB_CS_ADDR, 0x31);
        // Channel_Status[23:20] Set Dummy and Reference by AudioChannelNumStaus1 ~ 8
        stAudioStatus.ucChannelStaus2 = (ScalerGetByte(PB6_AC_CS_DATA) & 0x0F);

        // Get Channel_Status[31:24]
        ScalerSetByte(PB6_AB_CS_ADDR, 0x30);
        stAudioStatus.ucChannelStaus3 = ScalerGetByte(PB6_AC_CS_DATA);

        // Get Channel_Status[39:32]
        ScalerSetByte(PB6_AB_CS_ADDR, 0x2F);
        stAudioStatus.ucChannelStaus4 = ScalerGetByte(PB6_AC_CS_DATA);

        // Get Channel_Number 1/2
        ScalerSetByte(PB6_AB_CS_ADDR, 0x34);
        stAudioStatus.ucChannelNumber12 = ScalerGetByte(PB6_AC_CS_DATA);

        // Get Channel_Number 3/4
        ScalerSetByte(PB6_AB_CS_ADDR, 0x35);
        stAudioStatus.ucChannelNumber34 = ScalerGetByte(PB6_AC_CS_DATA);

        // Get Channel_Number 5/6
        ScalerSetByte(PB6_AB_CS_ADDR, 0x36);
        stAudioStatus.ucChannelNumber56 = ScalerGetByte(PB6_AC_CS_DATA);

        // Get Channel_Number 7/8
        ScalerSetByte(PB6_AB_CS_ADDR, 0x37);
        stAudioStatus.ucChannelNumber78 = ScalerGetByte(PB6_AC_CS_DATA);
    }

    return stAudioStatus;
}

#if(_DP_TX_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : RX0 Audio RS Decoder Control
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0RsDecoderControl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable Dp 1.4/2.0 Audio RS Decoder
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0)) == _CODING_TYPE_128B132B)
        {
            return;
        }
        else
#endif
        {
            ScalerSetBit(PB6_2B_MN_RS_DEC_CTRL, ~(_BIT7 | _BIT3 | _BIT2), _BIT7);
        }
    }
    else
    {
        // Disable Audio RS Decoder
        ScalerSetBit(PB6_2B_MN_RS_DEC_CTRL, ~(_BIT7 | _BIT3 | _BIT2), 0x00);
    }
}
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerDpAudioRx0GetInternalAudioGenEnable(void)
{
    if(ScalerGetBit(P60_10_AUD_PG_SET, _BIT7) == _BIT7)
    {
        return _ENABLE;
    }
    else
    {
        return _DISABLE;
    }
}

//--------------------------------------------------
// Description  : RX0 Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0InternalAudioGenSwitch(bit bOn, EnumAudioLeftRightChannelSelect enumAudioLeftRightChannelSelect)
{
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
    EnumDpLinkChannelCodingType enumDpCodingType = ScalerDpAuxRxGetCodingType(ScalerDpRxMacGetInputPortSwitch(_DP_MAC_0));
#endif
    enumAudioLeftRightChannelSelect = enumAudioLeftRightChannelSelect;

    if(bOn == _ON)
    {
        DWORD ulNFcode = 0;
        WORD usFcode = 0;
        WORD usStableTime = 0;
        BYTE ucNcode = 0;

        DebugMessageAudio("[Audio] Rx0 DP Audio Test On", 0);

        // =====================
        // Tracking Control
        // =====================

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(enumDpCodingType == _CODING_TYPE_128B132B)
        {
            // Disable FIFO_OVF/UVF INT
            ScalerSetBit(P1B_39_DP_WD_CTRL_1, ~(_BIT7 | _BIT6), 0x00);
        }
        else
#endif
        {
            // Disable FIFO_OVF/UVF INT
            ScalerSetBit(PB6_3D_DP_WD_CTRL_1, ~(_BIT7 | _BIT6), 0x00);
        }

        // Check Audio FIFO Tracking
        if(ScalerGetBit(PB6_82_AUD_BDRY_0, _BIT7) == 0x00)
        {
            SET_DP_RX0_AUDIO_FIFO_TRACKING_BACKUP(_DISABLE);
        }
        else
        {
            SET_DP_RX0_AUDIO_FIFO_TRACKING_BACKUP(_ENABLE);
        }

        // Disable Boundary Tracking
        ScalerSetBit(PB6_82_AUD_BDRY_0, ~_BIT7, 0x00);

        // Disable Trend Tracking
        ScalerSetBit(PB6_8C_AUD_TRND_0, ~_BIT7, 0x00);


        // =====================
        // Frequency Config
        // =====================

        // Enable N.F Code FW Mode
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), 0x00);

        // Enable S Code FW Mode
        ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, _BIT7);

        // Set S code
        ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (((WORD)(GET_AUDIO_GEN_FREQ_S_CODE() & 0x7F) * 5) / 2));

        // NF code Calculation
        ulNFcode = ((DWORD)(GET_AUDIO_GEN_FREQ_N_CODE() + 2) * 1000) + (((DWORD)GET_AUDIO_GEN_FREQ_F_CODE() * 1000) >> 16);
        ulNFcode = ulNFcode * 1000 / 1021;

        ucNcode = (ulNFcode / 1000) - 2;
        usFcode = ulNFcode - ((WORD)ucNcode * 1000);
        usFcode = ((DWORD)usFcode << 16) / 1000;

        // Set N code
        ScalerSetBit(PB6_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucNcode);

        // Set F code
        ScalerSetByte(PB6_A2_AUD_N_F_CODE_2, HIBYTE(usFcode));
        ScalerSetByte(PB6_A3_AUD_N_F_CODE_3, LOBYTE(usFcode));

        // Set Double Buffer bit
        ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);


        // =====================
        // Sine Wave Config
        // =====================

        // Ch1/Ch2 Divider set to 4
        ScalerSetBit(P60_1A_AUD_PG_SINEWAVE_PARAMETER10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

        // Disable CRC repeated
        ScalerSetBit(P60_1A_AUD_PG_SINEWAVE_PARAMETER10, ~_BIT0, 0x00);

        // Sine Offset
        ScalerSetByte(P60_17_AUD_PG_SINEWAVE_PARAMETER7, 0x00);
        ScalerSetByte(P60_18_AUD_PG_SINEWAVE_PARAMETER8, 0x00);
        ScalerSetByte(P60_19_AUD_PG_SINEWAVE_PARAMETER9, 0x00);


        // =====================
        // Pattern  Control
        // =====================

        // Select Audio Clock to DP 1.4
        ScalerSetBit(PB6_D3_PLL_IN_CONTROL, ~_BIT2, 0x00);

        // Enable Sine Wave Gen
        ScalerSetBit(P60_10_AUD_PG_SET, ~_BIT7, _BIT7);


        // =====================
        // Audio FSM Control
        // =====================

        // Check Audio FSM
        if(ScalerGetBit(PB6_74_AUD_FSM_CTRL_0, _BIT7) == 0x00)
        {
            // Audio FSM Enable
            ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

            SET_DP_RX0_AUDIO_FSM_STATUS_BACKUP(_DISABLE);

            DebugMessageAudio("[Audio] Rx0 DP Aduio FSM Enable", _ENABLE);
        }
        else
        {
            SET_DP_RX0_AUDIO_FSM_STATUS_BACKUP(_ENABLE);
        }

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(enumDpCodingType == _CODING_TYPE_128B132B)
        {
            // Wait for AUD_FSM stable
            usStableTime = ((WORD)ScalerGetByte(P1B_7C_AUD_FSM_CTRL_1) << 8) + ScalerGetByte(P1B_7D_AUD_FSM_CTRL_2);
            ScalerTimerDelayXms((usStableTime / 5) + 20);

            // Disable Audio Frequency Detection
            ScalerSetBit(P1B_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
        }
        else
#endif
        {
            // Wait for AUD_FSM stable
            usStableTime = ((WORD)ScalerGetByte(PB6_7C_AUD_FSM_CTRL_1) << 8) + ScalerGetByte(PB6_7D_AUD_FSM_CTRL_2);
            ScalerTimerDelayXms((usStableTime / 5) + 20);

            // Disable Audio Frequency Detection
            ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);
        }

        // Audio Manual Mode Enable
        ScalerSetBit(PB6_75_AUD_MAN_FSM_CTRL_1, ~_BIT7, _BIT7);


        // =====================
        // Output Control
        // =====================

        // DP Audio Channel Enable
        if(enumAudioLeftRightChannelSelect == _AUDIO_LEFT_CHANNEL)
        {
            // DP Audio Left Channel Enable
            ScalerSetByte(PB6_BF_DP_CHANNEL_EN_2, 0x55);
        }
        else if(enumAudioLeftRightChannelSelect == _AUDIO_RIGHT_CHANNEL)
        {
            // DP Audio Right Channel Enable
            ScalerSetByte(PB6_BF_DP_CHANNEL_EN_2, 0xAA);
        }
        else
        {
            // DP Audio All Channel Enable
            ScalerSetByte(PB6_BF_DP_CHANNEL_EN_2, 0xFF);
        }
    }
    else
    {
        DebugMessageAudio("[Audio] Rx0 DP Aduio Test Off", 0);

        // =====================
        // Output Control
        // =====================

        // DP Audio Channel Disable
        ScalerSetByte(PB6_BF_DP_CHANNEL_EN_2, 0x00);


        // =====================
        // Audio FSM Control
        // =====================

        // Audio Manual Mode Disable
        ScalerSetBit(PB6_75_AUD_MAN_FSM_CTRL_1, ~_BIT7, 0x00);

        // Recover to Previous Audio FSM
        if(GET_DP_RX0_AUDIO_FSM_STATUS_BACKUP() == _DISABLE)
        {
            // Audio FSM Disable
            ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

            DebugMessageAudio("[Audio] Rx0 DP Aduio FSM Disable", _DISABLE);
        }


        // =====================
        // Frequency Config
        // =====================

        // Enable N.F Auto Mode
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), _BIT6);

        // Enable S Code Auto Mode
        ScalerSetBit(PB6_58_SCODE_0, ~_BIT7, 0x00);

        // Recover S code to 48kHz
        ScalerSetBit(PB6_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set Double Buffer bit
        ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);


        // =====================
        // Tracking Control
        // =====================

        // Recover to Previous Audio FIFO Tracking
        if(GET_DP_RX0_AUDIO_FIFO_TRACKING_BACKUP() == _ENABLE)
        {
            // Enable Boundary Tracking
            ScalerSetBit(PB6_82_AUD_BDRY_0, ~_BIT7, _BIT7);

            // Enable Trend Tracking
            ScalerSetBit(PB6_8C_AUD_TRND_0, ~_BIT7, _BIT7);
        }


        // =====================
        // Pattern Control
        // =====================

        // Disable Sine Wave Gen
        ScalerSetBit(P60_10_AUD_PG_SET, ~_BIT7, 0x00);

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(enumDpCodingType == _CODING_TYPE_128B132B)
        {
            // Select Audio Clock to DP 2.0
            ScalerSetBit(PB6_D3_PLL_IN_CONTROL, ~_BIT2, _BIT2);

            // Disable Audio Frequency Detection
            ScalerSetBit(P1B_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
        }
        else
#endif
        {
            // Select Audio Clock to DP 1.4
            ScalerSetBit(PB6_D3_PLL_IN_CONTROL, ~_BIT2, 0x00);

            // Disable Audio Frequency Detection
            ScalerSetBit(PB6_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
        }
    }
}
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial RX0 DP audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0AudioInitial_128b132b(void)
{
    // Disable Audio Output
    ScalerSetByte(P1B_BF_DP_CHANNEL_EN_2, 0x00);

    // Disable Check VBID[4] to Mute Audio by HW and disable Audio FSM
    ScalerSetBit(P1B_74_AUD_FSM_CTRL_0, ~(_BIT7 | _BIT1), 0x00);

#if(_HW_DP_AUDIO_CHANNEL_STATUS_1S1D2S_RECEIVE_SUPPORT == _ON)
    // Set Channel_Status reception can support 1S1D/2S mix layout
    SET_DP_RX0_AUDIO_CH_STATUS_NEW_MODE_128B132B();
#endif // End of #if(_HW_DP_AUDIO_CHANNEL_STATUS_1S1D2S_RECEIVE_SUPPORT == _ON)

    // Set Sample_Present transmit refers to rs[31]
    CLR_DP_RX0_AUDIO_SP_BIT_FORCE_1_MODE_128B132B();

    // Set Channel_Status transfer to bypass mode
    SET_DP_RX0_AUDIO_CS_TRANSFER_BYPASS_128B132B();

    // Set Sample_Present transmit to Frame 0 from DP Source
    ScalerSetBit(P1B_A9_SPDIF_TX_0, ~_BIT6, _BIT6);

    // Set Sample_Present transmit refers to Ch1
    // Set Preamble transmit refers to Ch1
    // Note: These setting is only for 8-ch audio format. For 2-ch audio format, references of SP/PR are "don't care".
    ScalerSetBit(P1B_B5_DP_AUD_CRC_0, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Disable SPDIF Channel_Status Regen method
    ScalerSetBit(_REG_DP20_RX0_AUDIO_SPDIF_TX_REGEN, ~_BIT7, 0x00);

    // Set SPDIF Tx to free_run mode in HBR mode
    ScalerSetBit(P1B_C1_SPDIFTX_FRAME_1, ~(_BIT7 | _BIT3), 0x00);

    // Disable AFD, set 2ms for auto freq. detect and disable 44.1kHz as 48kHz
    ScalerSetBit(P1B_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT0), _BIT2);

    // Set threshold to separate sampling frequency
    ScalerSetByte(P1B_54_AUD_FREQUENY_TH_0, 0x00);
    ScalerSetByte(P1B_55_AUD_FREQUENY_TH_1, 0x00);
    ScalerSetByte(P1B_56_AUD_FREQUENY_TH_2, 0x28);
    ScalerSetByte(P1B_57_AUD_FREQUENY_TH_3, 0x4C);
    ScalerSetByte(P1B_58_AUD_FREQUENY_TH_4, 0x5C);
    ScalerSetByte(P1B_59_AUD_FREQUENY_TH_5, 0x70);

    // Set xtal divider for sampling freq. detection
    ScalerSetByte(P1B_51_AUD_FREQUENY_DET_1, _AUTO_FREQ_DETECT_XTAL_DIV);

    // NF code for 32kHz
    ScalerSetByte(P1B_60_N_F_CODE_0, LOBYTE(HIWORD(_DP_SAMPLING_FREQ_32K_GROUP_NF_CODE)));
    ScalerSetByte(P1B_61_N_F_CODE_1, HIBYTE(LOWORD(_DP_SAMPLING_FREQ_32K_GROUP_NF_CODE)));
    ScalerSetByte(P1B_62_N_F_CODE_2, LOBYTE(LOWORD(_DP_SAMPLING_FREQ_32K_GROUP_NF_CODE)));

    // NF code for 44.1kHz
    ScalerSetByte(P1B_63_N_F_CODE_3, LOBYTE(HIWORD(_DP_SAMPLING_FREQ_44K_GROUP_NF_CODE)));
    ScalerSetByte(P1B_64_N_F_CODE_4, HIBYTE(LOWORD(_DP_SAMPLING_FREQ_44K_GROUP_NF_CODE)));
    ScalerSetByte(P1B_65_N_F_CODE_5, LOBYTE(LOWORD(_DP_SAMPLING_FREQ_44K_GROUP_NF_CODE)));

    // NF code for 48kHz
    ScalerSetByte(P1B_66_N_F_CODE_6, LOBYTE(HIWORD(_DP_SAMPLING_FREQ_48K_GROUP_NF_CODE)));
    ScalerSetByte(P1B_67_N_F_CODE_7, HIBYTE(LOWORD(_DP_SAMPLING_FREQ_48K_GROUP_NF_CODE)));
    ScalerSetByte(P1B_68_N_F_CODE_8, LOBYTE(LOWORD(_DP_SAMPLING_FREQ_48K_GROUP_NF_CODE)));

    // Enable Audio Buffer & Valid_Bit Detect
    ScalerSetBit(P1B_C8_DP_AUD_CTRL, ~(_BIT7 | _BIT5 | _BIT1 | _BIT0), (_BIT7 | _BIT5));

    // Disable Audio Coding Type Change INT
    ScalerSetBit(P1B_3B_DP_IRQ_CTRL1, ~_BIT0, 0x00);

    // Clear Change Flag
    CLR_DP_RX0_AUDIO_CODING_TYPE_CHANGE();

    // Set AUD PKT ID
    ScalerSetByte(P1B_C9_DP_AUD_ID, 0x00);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // Set S code by FW manual
    ScalerSetBit(P1B_5A_SCODE_0, ~_BIT7, _BIT7);

    // Set D code by FW manual
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // S code for 32kHz
    ScalerSetBit(P1B_5C_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set NF code of NF PLL
    ScalerDpAudioRx0FifoTrackingNFCodeConfig(_DP_SAMPLING_FREQ_32K_GROUP_NF_CODE);

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // S code for 44.1kHz
    ScalerSetBit(P1B_5C_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_44K_GROUP_S_CODE);
    // Set NF code of NF PLL
    ScalerDpAudioRx0FifoTrackingNFCodeConfig(_DP_SAMPLING_FREQ_44K_GROUP_NF_CODE);

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // S code for 48kHz
    ScalerSetBit(P1B_5C_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set NF code of NF PLL
    ScalerDpAudioRx0FifoTrackingNFCodeConfig(_DP_SAMPLING_FREQ_48K_GROUP_NF_CODE);

#endif

#else

    // Set Double Buffer for N.F Code
    ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

    // Set S code by HW auto
    ScalerSetBit(P1B_5A_SCODE_0, ~_BIT7, 0x00);

    // Set D code by HW auto
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), _BIT6);

    // S code for 32kHz
    ScalerSetBit(P1B_5A_SCODE_0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // S code for 44.1kHz
    ScalerSetBit(P1B_5B_SCODE_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // S code for 48kHz
    ScalerSetBit(P1B_5C_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set User Define Frequency When No Audio
    ScalerDpAudioRx0AudioFrequencyMode_128b132b(_AUDIO_TRACKING_MANNUAL_MODE);

#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

    // DP Audio DVC Mode Setting
    ScalerDpAudioRx0SetDVCVolumeAdjustType_128b132b(_DP_DVC_ADJUST_TYPE);

    // Enable PI control and Enable Auto Load NF Code By AFD
    ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

    // Disable AFD Function to Judge 88.2/96 and 176.4/192 As Same Range
    ScalerSetBit(P1B_5D_AUD_BURST_IN_CTR, ~(_BIT1 | _BIT0), 0x00);

    // Enable AFD, Disable Audio Sampling Frequency Changed INT
    ScalerSetBit(P1B_50_AUD_FREQUENY_DET_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    // Clear Sampling Change Flag at initial flow
    CLR_DP_RX0_AUDIO_SAMPLING_FREQ_CHANGE();

#if(_DIGITAL_AUDIO_OUTPUT_FORCE_CHANNEL_0_1_SUPPORT == _ON)
    // Force I2S/SPDIF Output Form Channel 0/1
    ScalerSetByte(P1B_BC_AUD_CH_LO_SEL, 0x00);
#endif

    // Enable I2S Output
    ScalerSetBit(P1B_B8_DP_I2S_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable SPDIF Output
    ScalerSetBit(P1B_AA_SPDIF_TX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Clear Flag
    CLR_DP_AUDIO_RX0_ICODE_RELOADED();

    CLR_DP_AUDIO_RX0_AUTO_LOAD_FREQ();

    // Clear HBR Mode Change Flag
    CLR_DP_AUDIO_RX0_HBR_RECEIVE_MODE_CHANGE();

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
    // Initial at HBR 8-ch Receive Mode
    ScalerDpAudioRx0HbrModeControl(_OFF);

    CLR_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH();

    CLR_DP_AUDIO_RX0_HBR_OPERATION_DONE();
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    // Reset Frequency Limit Proc
    ScalerDpAudioRx0ResetSamplingFreqLimitProc();
#endif
}

//--------------------------------------------------
// Description  : Set ZCD Timeout for DP Audio
// Input Value  : bAdjustType, enumSamplingFreqPacket
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetDVCWindowSize_128b132b(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket)
{
    if(enumSamplingFreqPacket == _AUDIO_FREQ_PACKET_NO_AUDIO)
    {
        enumSamplingFreqPacket = _AUDIO_FREQ_PACKET_48K;
    }

    if(bAdjustType == _DB_GAIN)
    {
        // Get numbers of the volume step for mute or unmute
        PDATA_WORD(0) = _DVC_DB_STEP_NUMBER << 3;
    }
    else
    {
        // Volume Max = 0x3FFF
        PDATA_WORD(0) = 0x3FFF / _DP_VOLUME_STEP_SIZE_VALUE + 1;
    }

    // Calculate samples of ZCD timeout
    PDATA_DWORD(1) = (DWORD)enumSamplingFreqPacket * _DP_DVC_VOLUME_MUTE_TIMER / PDATA_WORD(0);

    // Avoid Overflow
    if(PDATA_DWORD(1) > 0x0FFF)
    {
        PDATA_WORD(0) = 0x0FFF;
    }
    else
    {
        PDATA_WORD(0) = (WORD)PDATA_DWORD(1);
    }

    // Set DVC ZCD window size
    ScalerSetBit(P1B_78_DVC_WINDOW_CONTROL_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE(PDATA_WORD(0)));
    ScalerSetByte(P1B_79_DVC_WINDOW_CONTROL_1, LOBYTE(PDATA_WORD(0)));
}

//--------------------------------------------------
// Description  : Set ZCD Timeout for DP Audio
// Input Value  : bAdjustType, enumSamplingFreqPacket
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0SetDVCVolumeAdjustType_128b132b(bit bAdjustType)
{
    if(bAdjustType == _DB_GAIN)
    {
        // Select Value Mode to DB Gain Setp
        ScalerSetBit(P1B_76_DVC_CTRL, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | (_DP_DB_GAIN_DOWN_VALUE << 2) | _DP_DB_GAIN_UP_VALUE));

        // Initial Volume Step Size for DB Gain Mode
        ScalerSetByte(P1B_77_DVC_VA, 0x01);
    }
    else // _VOLUME_STEP_SIZE
    {
        // Select Value Mode to Volume Setp
        ScalerSetBit(P1B_76_DVC_CTRL, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

        // Set Volume Step Size
        ScalerSetByte(P1B_77_DVC_VA, _DP_VOLUME_STEP_SIZE_VALUE);
    }

    // DP Audio DVC Window Setting
    ScalerDpAudioRx0SetDVCWindowSize_128b132b(bAdjustType, _AUDIO_FREQ_PACKET_48K);
}

//--------------------------------------------------
// Description  : Get RX0 Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerDpAudioRx0GetAudioDetected_128b132b(void)
{
    // Check audio packet
    if(GET_DP_AUDIO_RX0_PACKET_DETECT() == _FALSE)
    {
        DebugMessageAudio("False : RX0 DP 2.0 Audio Packet", 0);
        return _FALSE;
    }

    // Check Audio FSM
    if(ScalerGetBit(P1B_74_AUD_FSM_CTRL_0, _BIT7) == 0x00)
    {
        DebugMessageAudio("False : RX0 DP 2.0 Audio Fsm Disable", 0);

        return _FALSE;
    }

    // Check Audio Tracking
    if(ScalerGetBit(PB6_82_AUD_BDRY_0, _BIT7) == 0x00)
    {
        DebugMessageAudio("False : RX0 DP 2.0 Audio Tracking Disable", 0);

        return _FALSE;
    }

    // Check DP audio buffer overflow and underflow
    if(ScalerGetBit(P1B_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
    {
        DebugMessageAudio("False : RX0 DP 2.0 Audio Buffer", ScalerGetBit(P1B_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

        if(ScalerGetBit(P1B_39_DP_WD_CTRL_1, (_BIT7 | _BIT6)) == 0x00)
        {
            // Clear audio FIFO overflow and underflow status
            ScalerSetBit(P1B_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
            ScalerTimerDelayXms(3);

            if(ScalerGetBit(P1B_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
            {
                DebugMessageAudio("False : RX0 DP 2.0 Audio FSM Reset", ScalerGetBit(P1B_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

                // Reset Audio FSM
                ScalerSetBit(P1B_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

                // Clear audio FIFO overflow and underflow status
                ScalerSetBit(P1B_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Enable Audio FSM
                ScalerSetBit(P1B_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

                // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
                ScalerTimerDelayXms(3);
            }
        }

        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Audio Coding Type By Audio Data
// Input Value  : None
// Output Value : _TRUE => LPCM / _FALSE => NON-LPCM
//--------------------------------------------------
bit ScalerDpAudioRx0LPCMCheckData_128b132b(void)
{
    // Enable IRQ for Audio Coding Type Change
    if(ScalerGetBit(P1B_3B_DP_IRQ_CTRL1, _BIT0) == 0x00)
    {
        WORD usDelayTime = 12;
        EnumAudioSamplingFreqType enumAudioFreq = ScalerDpAudioRx0SamplingFreqDetect();
        EnumAudioSamplingFreqPacket enumAudioPacket = ScalerAudioGetSamplingFreqPacket(enumAudioFreq);

        // =================================
        // Detect Coding Type at First Time
        // =================================

        DebugMessageAudio("[Audio] Rx0 DP 2.0 Coding Type First Time Detect", 0);


        // -----------------------------
        // Header Byte Detect Flow
        // -----------------------------

#if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)
        // Check IEC61937 HBR Format
        if(GET_DP_AUDIO_RX0_HBR_RECEIVE_IN_8_CH() == _TRUE)
        {
            // Set Audio Coding Type Source to Channel_Status
            ScalerSetBit(P1B_C8_DP_AUD_CTRL, ~(_BIT5 | _BIT1 | _BIT0), 0x00);

            DebugMessageAudio("[Audio] Rx0 initial at Non-LPCM HBR via HB3[7:4]", 1);

            SET_DP_RX0_AUDIO_CODING_TYPE_FORMAT(_AUDIO_NON_LPCM);

            return _FALSE;
        }
#endif // End of #if(_DP_RX_AUDIO_HBR_RECEIVE_IN_8_CHANNEL == _ON)


#if(_HW_DP_AUDIO_CHANNEL_STATUS_1S1D2S_RECEIVE_SUPPORT == _OFF)
        // Check if audio channel count is 2-Ch
        if(ScalerGetBit(P1B_5F_SDP_AUD_STR_HB3, (_BIT2 | _BIT1 | _BIT0)) <= _AUDIO_CHANNEL_COUNT_2)
        {
            // Check HW Support Channel Status Bit_1 directly fetch or not
            if(ScalerDpAudioRxGetChannelStatusBit1Support() == _TRUE)
            {
                // Check Channel Status Bit_1 Status
                if(ScalerGetBit(P1B_CD_DUMMY_CD, _BIT3) == 0x00)
                {
                    DebugMessageAudio("[Audio] Rx0 initial at LPCM via Channel_Status Bit_1", 0);

                    SET_DP_RX0_AUDIO_CODING_TYPE_FORMAT(_AUDIO_LPCM);
                }
                else
                {
                    DebugMessageAudio("[Audio] Rx0 initial at Non-LPCM via Channel_Status Bit_1", 0);

                    SET_DP_RX0_AUDIO_CODING_TYPE_FORMAT(_AUDIO_NON_LPCM);
                }

                // Set Audio Coding Type Source to Valid_Bit for HW INT
                ScalerSetBit(P1B_C8_DP_AUD_CTRL, ~(_BIT5 | _BIT1 | _BIT0), _BIT5);
            }
            else
            {
                // Use Ch1's valid_bit to check audio coding type

                // ---------------------------------
                // Valid_Bit Detect Flow
                // ---------------------------------

                // Set Audio Coding Type Source to Valid_Bit
                ScalerSetBit(P1B_C8_DP_AUD_CTRL, ~(_BIT5 | _BIT1 | _BIT0), _BIT5);

                // Update Detect Result
                if(ScalerGetBit(P1B_C8_DP_AUD_CTRL, _BIT4) == 0x00)
                {
                    DebugMessageAudio("[Audio] Rx0 initial at LPCM via Valid_Bit", 0);

                    SET_DP_RX0_AUDIO_CODING_TYPE_FORMAT(_AUDIO_LPCM);
                }
                else
                {
                    DebugMessageAudio("[Audio] Rx0 initial at Non-LPCM via Valid_Bit", 0);

                    SET_DP_RX0_AUDIO_CODING_TYPE_FORMAT(_AUDIO_NON_LPCM);
                }
            }
        }
        else
#endif // End of #if(_HW_DP_AUDIO_CHANNEL_STATUS_1S1D2S_RECEIVE_SUPPORT == _OFF)
        {
            // Use Channel_Status[1:0] to check audio coding type

            // -----------------------------
            // Channel Status Detect Flow
            // -----------------------------

            // Set Audio Coding Type Source to Channel_Status
            ScalerSetBit(P1B_C8_DP_AUD_CTRL, ~(_BIT5 | _BIT1 | _BIT0), 0x00);

            // Calculate Minimum Delay for Receiving 192*2 Audio Samples
            // Avoid 0Hz Value
            if(enumAudioPacket == _AUDIO_FREQ_PACKET_NO_AUDIO)
            {
                enumAudioPacket = _AUDIO_FREQ_PACKET_32K;
            }

            // (192Samples * 2) / AudioFreq
            usDelayTime = (192 * 2) / enumAudioPacket;

            // Delay with 2ms margin added
            ScalerTimerDelayXms(usDelayTime + 2);

            // Update Detect Result
            if(ScalerGetBit(P1B_C8_DP_AUD_CTRL, _BIT4) == _BIT4)
            {
                DebugMessageAudio("[Audio] Rx0 initial at Non-LPCM via Channel_Status", 1);

                SET_DP_RX0_AUDIO_CODING_TYPE_FORMAT(_AUDIO_NON_LPCM);
            }
            else
            {
                DebugMessageAudio("[Audio] Rx0 initial at LPCM via Channel_Status", 0);

                SET_DP_RX0_AUDIO_CODING_TYPE_FORMAT(_AUDIO_LPCM);
            }
        }

        // =================================
        // Use HW INT Auto Detect
        // =================================

        // Clear Audio Coding Type Change Flag
        ScalerSetBit(P1B_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

        // Clear Change Flag
        CLR_DP_RX0_AUDIO_CODING_TYPE_CHANGE();

        // Enable Audio Coding Type Change INT
        ScalerSetBit(P1B_3B_DP_IRQ_CTRL1, ~_BIT0, _BIT0);
    }

    // =================================
    // Return Coding Type Status
    // =================================
    if(GET_DP_RX0_AUDIO_CODING_TYPE_FORMAT() == _AUDIO_NON_LPCM)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : RX0 Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0WatchDogProc_128b132b(bit bOn)
{
    if(bOn == _ON)
    {
        // Clear audio buffer overflow and underflow status
        ScalerSetBit(P1B_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Enable Audio Watch Dog for Buffer Overflow/Underflow
        ScalerSetBit(P1B_39_DP_WD_CTRL_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else
    {
        // Disable Audio Watch Dog for Buffer Overflow/Underflow
        ScalerSetBit(P1B_39_DP_WD_CTRL_1, ~(_BIT7 | _BIT6), 0x00);

        if(ScalerGetBit(P1B_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)) != 0x00)
        {
            DebugMessageAudio("WD : RX0 DP 2.0 Audio Over/Underflow", ScalerGetBit(P1B_70_AUD_BUFFER_CTRL_0, (_BIT1 | _BIT0)));

            // Reset Audio FSM
            ScalerSetBit(P1B_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);

            // Clear audio FIFO overflow and underflow status
            ScalerSetBit(P1B_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Enable Audio FSM
            ScalerSetBit(P1B_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);

            // Waiting for 2ms(Audio Freq. Detect || Audio FIFO Write (1/2 FIFO depth = 64 packet)) + 1ms(Audio Stable Time Count = 5 x 200us)
            ScalerTimerDelayXms(3);
        }
    }
}

//--------------------------------------------------
// Description  : RX0 Audio FIFO Tracking Enable Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0FifoTrackingEnableControl_128b132b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set I code of trend tracking
        ScalerSetByte(PB6_94_AUD_TRND_8, 0x00);
        ScalerSetByte(PB6_95_AUD_TRND_9, 0x02);

        // Set P code of trend tracking
        ScalerSetByte(PB6_96_AUD_TRND_10, 0x00);
        ScalerSetByte(PB6_97_AUD_TRND_11, 0x7F);
        ScalerSetByte(PB6_98_AUD_TRND_12, 0xFF);

        // Set Boundary Tracking Water Level

        // Set boundary tracking water level final upper boound
        ScalerSetBit(PB6_85_AUD_BDRY_3, ~_BIT4, 0x00);
        ScalerSetByte(PB6_DC_AUD_BDRY_10, 0x9C);

        // Set boundary tracking water level initial upper boound
        ScalerSetBit(PB6_85_AUD_BDRY_3, ~_BIT5, 0x00);
        ScalerSetByte(PB6_8A_AUD_BDRY_8, 0x68);

        // Set boundary tracking water level Target Depth
        ScalerSetByte(P1B_71_AUD_BUFFER_CTRL_1, 0x58);

        // Set boundary tracking water level initial lower boound
        ScalerSetByte(PB6_8B_AUD_BDRY_9, 0x48);

        // Set boundary tracking water level final lower boound
        ScalerSetByte(PB6_DE_AUD_BDRY_11, 0x14);

        // Set boundary tracking Step for next boundary threshold
        ScalerSetBit(PB6_82_AUD_BDRY_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

        // Enable Boundary Tracking Method
        ScalerSetBit(PB6_82_AUD_BDRY_0, ~_BIT7, _BIT7);

        // Disable Boundary tracking I/P code adjustment
        ScalerSetBit(PB6_C0_AUD_BDRY_NEW_MODE_0, ~(_BIT1 | _BIT0), 0x00);

        // Enable Trend Tracking Method
        ScalerSetBit(PB6_8C_AUD_TRND_0, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable Boundary Tracking Method
        ScalerSetBit(PB6_82_AUD_BDRY_0, ~_BIT7, 0x00);

        // Disable Boundary tracking I/P code adjustment
        ScalerSetBit(PB6_C0_AUD_BDRY_NEW_MODE_0, ~(_BIT1 | _BIT0), 0x00);

        // Disable Trend Tracking Method
        ScalerSetBit(PB6_8C_AUD_TRND_0, ~_BIT7, 0x00);

        // Set Double Buffer for N.F Code
        ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : RX0 Audio FIFO Tracking Proc
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0FifoTrackingProc_128b132b(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        if(GET_DP_AUDIO_RX0_AUTO_LOAD_FREQ() == _FALSE)
        {
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

            // -----------------------------------------
            // Set Fix Frequency to Current Frequency
            // -----------------------------------------
            ScalerDpAudioRx0AudioFrequencyMode_128b132b(_AUDIO_TRACKING_MANNUAL_MODE_FIX_TARGET_FREQ);

#else

            // -----------------------------------------
            // Set HW Auto Load Frequency
            // -----------------------------------------
            ScalerDpAudioRx0AudioFrequencyMode_128b132b(_AUDIO_TRACKING_AUTO_LOAD_MODE);

#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

            // Set Auto Load Done Flag
            SET_DP_AUDIO_RX0_AUTO_LOAD_FREQ();

            DebugMessageAudio("Dp 2.0 Rx0 Audio Auto_Load Mode", 0);
        }
#endif

        if(ScalerGetBit(PB6_82_AUD_BDRY_0, _BIT7) == 0x00)
        {
            // -----------------------------------------
            // Enable Tracking Function
            // -----------------------------------------

            // Select Audio Clock to DP 2.0
            ScalerSetBit(PB6_D3_PLL_IN_CONTROL, ~_BIT2, _BIT2);

            // Disable INT for Auido Sampling Change
            ScalerSetBit(P1B_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), 0x00);

            // Disable Audio FSM
            ScalerDpAudioRx0AudioEnableControl(_DISABLE);

            DELAY_5US();

            // Enable FIFO Tracking
            ScalerDpAudioRx0FifoTrackingEnableControl_128b132b(_ENABLE);

            // Enable Audio FSM
            ScalerDpAudioRx0AudioEnableControl(_ENABLE);

            // Wait for New Audio Packet Recive 4 times via detect interval + 1ms
            ScalerTimerDelayXms(((ScalerGetBit(P1B_50_AUD_FREQUENY_DET_0, (_BIT3 | _BIT2)) >> 2) + 1) * 4 + 1);

            // Clear Auido Sampling Change Flag
            ScalerSetBit(P1B_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);

            // Enable INT for Auido Sampling Change
            ScalerSetBit(P1B_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), _BIT6);

            DebugMessageAudio("Dp 2.0 Rx0 Audio Tracking Enable", 0);
        }
    }
    else
    {
        if(ScalerGetBit(PB6_82_AUD_BDRY_0, _BIT7) == _BIT7)
        {
            // -----------------------------------------
            // Disable Tracking Function
            // -----------------------------------------

            // Disable INT for Auido Sampling Change
            ScalerSetBit(P1B_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), 0x00);

            // Disable FIFO Tracking
            ScalerDpAudioRx0FifoTrackingEnableControl_128b132b(_DISABLE);

            DebugMessageAudio("Dp 2.0 Rx0 Audio Tracking Disable", 0);
        }

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        if(GET_DP_AUDIO_RX0_AUTO_LOAD_FREQ() == _TRUE)
        {
            // -----------------------------------------
            // Set User Define Frequency When No Audio
            // -----------------------------------------
            ScalerDpAudioRx0AudioFrequencyMode_128b132b(_AUDIO_TRACKING_MANNUAL_MODE);

            // Clear Auto Load Done Flag
            CLR_DP_AUDIO_RX0_AUTO_LOAD_FREQ();

            DebugMessageAudio("Dp 2.0 Rx0 Audio Manual Mode", 0);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : RX0 Audio Frequency Mode Setting
// Input Value  : _AUDIO_TRACKING_AUTO_LOAD_MODE / _AUDIO_TRACKING_MANNUAL_MODE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx0AudioFrequencyMode_128b132b(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode)
{
    if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_AUTO_LOAD_MODE)
    {
        // Set S code by HW auto
        ScalerSetBit(P1B_5A_SCODE_0, ~_BIT7, 0x00);

        // Set D code by HW auto
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), _BIT6);

        // S code for 48kHz
        ScalerSetBit(P1B_5C_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set N code of NF PLL
        ScalerSetBit(PB6_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));

        // Set F code of NF PLL
        ScalerSetByte(PB6_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));
        ScalerSetByte(PB6_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);
    }
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    else if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_MANNUAL_MODE_FIX_TARGET_FREQ)
    {
        // S code for Current Frequency
        ScalerSetBit(P1B_5C_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerAudioGetUserSamplingFreqSCode(_PORT_DP, GET_DP_RX0_TARGET_SAMPLING_FREQ()));

        // Set N code of NF PLL
        ScalerSetBit(PB6_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_TARGET_SAMPLING_FREQ()))));

        // Set F code of NF PLL
        ScalerSetByte(PB6_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_TARGET_SAMPLING_FREQ()))));
        ScalerSetByte(PB6_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_TARGET_SAMPLING_FREQ()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

        // Set S code by FW manual
        ScalerSetBit(P1B_5A_SCODE_0, ~_BIT7, _BIT7);

        // Set D code by FW manual
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), 0x00);
    }
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    else
    {
        // S code for User Define
        ScalerSetBit(P1B_5C_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerAudioGetUserSamplingFreqSCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()));

        // Set N code of NF PLL
        ScalerSetBit(PB6_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));

        // Set F code of NF PLL
        ScalerSetByte(PB6_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));
        ScalerSetByte(PB6_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_DP, GET_DP_RX0_SAMPLING_FREQ_USER_DEFINE()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit(PB6_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

        // Set S code by FW manual
        ScalerSetBit(P1B_5A_SCODE_0, ~_BIT7, _BIT7);

        // Set D code by FW manual
        ScalerSetBit(PB6_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), 0x00);
    }
}
#endif // End of #if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif // End of #if(_DP_AUDIO_RX0_SUPPORT == _ON)

