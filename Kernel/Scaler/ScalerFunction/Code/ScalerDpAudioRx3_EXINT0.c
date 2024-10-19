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
// ID Code      : ScalerDpAudioRx3_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpAudioRx3/ScalerDpAudioRx3.h"

#if(_DP_AUDIO_RX3_SUPPORT == _ON)

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
// Description  : RX3 Audio FSM Control
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3AudioEnableControl_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable Dp 1.4/2.0 Audio via Channel Coding Type
#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpAuxRxGetCodingType_EXINT0(ScalerDpRxMacGetInputPortSwitch_EXINT0(_DP_MAC_3)) == _CODING_TYPE_128B132B)
        {
            ScalerSetBit_EXINT(PF2_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);
        }
        else
#endif
        {
            ScalerSetBit_EXINT(PEF_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);
        }
    }
    else
    {
        // Disable Both Dp 1.4/2.0 Audio
#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
        ScalerSetBit_EXINT(PF2_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);
#endif

        ScalerSetBit_EXINT(PEF_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : RX3 Audio LPCM Change Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3LPCMFormatChangeProc_EXINT0(void)
{
#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
    // Check Change Flag
    if((ScalerGetBit_EXINT(PF2_3B_DP_IRQ_CTRL1, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(PF2_37_DP_GLB_STATUS, _BIT2) == _BIT2))
    {
        // Disable Audio Coding Type Change INT
        ScalerSetBit_EXINT(PF2_3B_DP_IRQ_CTRL1, ~_BIT0, 0x00);

        // Clear Audio Coding Type Change Flag
        ScalerSetBit_EXINT(PF2_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

        // Disable Audio Output
        ScalerSetByte_EXINT(PF2_BF_DP_CHANNEL_EN_2, 0x00);

        // Set Change Flag
        SET_DP_RX3_AUDIO_CODING_TYPE_CHANGE();

#if((_AUDIO_SUPPORT == _ON) && (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))
        // Turn-off FIFO Tracking
        // Disable Boundary Tracking Method
        ScalerSetBit_EXINT(PEF_82_AUD_BDRY_0, ~_BIT7, 0x00);

        // Disable Trend Tracking Method
        ScalerSetBit_EXINT(PEF_8C_AUD_TRND_0, ~_BIT7, 0x00);

        // Set Double Buffer for N.F Code
        ScalerSetBit_EXINT(PEF_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

        // Set FW Mannual Mode
        ScalerDpAudioRx3AudioFrequencyMode_128b132b_EXINT0(_AUDIO_TRACKING_MANNUAL_MODE);

        // Set TTS Play Error Flag
        SET_TTS_PLAYBACK_ERROR();
#endif
    }
#endif

    // Check Change Flag
    if((ScalerGetBit_EXINT(PEF_3F_DP_IRQ_CTRL1, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(PEF_3B_DP_GLB_STATUS, _BIT2) == _BIT2))
    {
        // Disable Audio Coding Type Change INT
        ScalerSetBit_EXINT(PEF_3F_DP_IRQ_CTRL1, ~_BIT0, 0x00);

        // Clear Audio Coding Type Change Flag
        ScalerSetBit_EXINT(PEF_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

        // Disable Audio Output
        ScalerSetByte_EXINT(PEF_BF_DP_CHANNEL_EN_2, 0x00);

        // Set Change Flag
        SET_DP_RX3_AUDIO_CODING_TYPE_CHANGE();

#if((_AUDIO_SUPPORT == _ON) && (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))
        // Turn-off FIFO Tracking
        // Disable Boundary Tracking Method
        ScalerSetBit_EXINT(PEF_82_AUD_BDRY_0, ~_BIT7, 0x00);

        // Disable Trend Tracking Method
        ScalerSetBit_EXINT(PEF_8C_AUD_TRND_0, ~_BIT7, 0x00);

        // Set Double Buffer for N.F Code
        ScalerSetBit_EXINT(PEF_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

        // Set FW Mannual Mode
        ScalerDpAudioRx3AudioFrequencyMode_8b10b_EXINT0(_AUDIO_TRACKING_MANNUAL_MODE);

        // Set TTS Play Error Flag
        SET_TTS_PLAYBACK_ERROR();
#endif
    }
}

//--------------------------------------------------
// Description  : RX3 Audio FIFO Tracking Enable Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3FifoTrackingEnableControl_8b10b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set I code of trend tracking
        ScalerSetByte_EXINT(PEF_94_AUD_TRND_8, 0x00);
        ScalerSetByte_EXINT(PEF_95_AUD_TRND_9, 0x00);

        // Set P code of trend tracking
        ScalerSetByte_EXINT(PEF_96_AUD_TRND_10, 0x00);
        ScalerSetByte_EXINT(PEF_97_AUD_TRND_11, 0x00);
        ScalerSetByte_EXINT(PEF_98_AUD_TRND_12, 0x00);

        // Set Boundary Tracking Water Level

        // Set boundary tracking water level final upper boound
        ScalerSetBit_EXINT(PEF_85_AUD_BDRY_3, ~_BIT4, _BIT4);
        ScalerSetByte_EXINT(PEF_DC_AUD_BDRY_10, 0x4C);

        // Set boundary tracking water level initial upper boound
        ScalerSetBit_EXINT(PEF_85_AUD_BDRY_3, ~_BIT5, 0x00);
        ScalerSetByte_EXINT(PEF_8A_AUD_BDRY_8, 0xC0);

        // Set boundary tracking water level Target Depth
        ScalerSetBit_EXINT(PEF_70_AUD_BUFFER_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(PEF_71_AUD_BUFFER_CTRL_1, 0xB0);

        // Set boundary tracking water level initial lower boound
        ScalerSetByte_EXINT(PEF_8B_AUD_BDRY_9, 0xA0);

        // Set boundary tracking water level final lower boound
        ScalerSetByte_EXINT(PEF_DE_AUD_BDRY_11, 0x14);

        // Set boundary tracking Step for next boundary threshold
        ScalerSetBit_EXINT(PEF_82_AUD_BDRY_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

        // Enable Boundary Tracking Method
        ScalerSetBit_EXINT(PEF_82_AUD_BDRY_0, ~_BIT7, _BIT7);

        // Enable Boundary tracking I/P code adjustment
        ScalerSetBit_EXINT(PEF_C0_AUD_BDRY_NEW_MODE_0, ~(_BIT1 | _BIT0), 0x00);

        // Enable Trend Tracking Method
        ScalerSetBit_EXINT(PEF_8C_AUD_TRND_0, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable Boundary Tracking Method
        ScalerSetBit_EXINT(PEF_82_AUD_BDRY_0, ~_BIT7, 0x00);

        // Disable Boundary tracking I/P code adjustment
        ScalerSetBit_EXINT(PEF_C0_AUD_BDRY_NEW_MODE_0, ~(_BIT1 | _BIT0), 0x00);

        // Disable Trend Tracking Method
        ScalerSetBit_EXINT(PEF_8C_AUD_TRND_0, ~_BIT7, 0x00);

        // Set Double Buffer for N.F Code
        ScalerSetBit_EXINT(PEF_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : RX3 Audio FIFO Tracking Proc
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3FifoTrackingProc_EXINT0(void)
{
#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpAudioRx3FifoTrackingProc_128b132b_EXINT0();
#endif

    ScalerDpAudioRx3FifoTrackingProc_8b10b_EXINT0();
}

//--------------------------------------------------
// Description  : RX3 Audio Disable Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3DisableSetting_EXINT0(void)
{
#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
    ScalerDpAudioRx3DisableSetting_128b132b_EXINT0();
#endif

    ScalerDpAudioRx3DisableSetting_8b10b_EXINT0();
}

//--------------------------------------------------
// Description  : RX3 Audio FIFO Tracking Proc
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3FifoTrackingProc_8b10b_EXINT0(void)
{
    // Detect if Auido Sampling is Changed
    if(ScalerGetBit_EXINT(PEF_50_AUD_FREQUENY_DET_0, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
    {
        // Clear Auido Sampling Change Flag
        ScalerSetBit_EXINT(PEF_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);

        // Set Sampling Change Flag
        SET_DP_RX3_AUDIO_SAMPLING_FREQ_CHANGE();

        // Disable FIFO Tracking
        ScalerDpAudioRx3FifoTrackingEnableControl_8b10b_EXINT0(_DISABLE);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        // No Audio Detect
        if((ScalerGetBit_EXINT(PEF_61_AUD_SAMPLE_CNT_0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4) == 0x00)
        {
            // -----------------------------------------
            // Set User Define Frequency When No Audio
            // -----------------------------------------
            ScalerDpAudioRx3AudioFrequencyMode_8b10b_EXINT0(_AUDIO_TRACKING_MANNUAL_MODE);

            // Clear Flag
            CLR_DP_AUDIO_RX3_AUTO_LOAD_FREQ();
        }
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)

#if((_AUDIO_SUPPORT == _ON) && (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))
        // Set TTS Play Error Flag
        SET_TTS_PLAYBACK_ERROR();
#endif
    }
}

//--------------------------------------------------
// Description  : RX3 Audio Disable Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3DisableSetting_8b10b_EXINT0(void)
{
    // Disable INT for Auido Sampling Change
    ScalerSetBit_EXINT(PEF_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), 0x00);

    // -----------------------------------------
    // Disable Tracking Function
    // -----------------------------------------
    ScalerDpAudioRx3FifoTrackingEnableControl_8b10b_EXINT0(_DISABLE);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
    // No Audio Detect
    if((ScalerGetBit_EXINT(PEF_61_AUD_SAMPLE_CNT_0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4) == 0x00)
    {
        // -----------------------------------------
        // Set User Define Frequency When No Audio
        // -----------------------------------------
        ScalerDpAudioRx3AudioFrequencyMode_8b10b_EXINT0(_AUDIO_TRACKING_MANNUAL_MODE);

        // Clear Flag
        CLR_DP_AUDIO_RX3_AUTO_LOAD_FREQ();
    }
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)

    // Disable Audio Coding Type Change INT
    ScalerSetBit_EXINT(PEF_3F_DP_IRQ_CTRL1, ~_BIT0, 0x00);

    // Clear Audio Coding Type Change Flag
    ScalerSetBit_EXINT(PEF_3B_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

    // Disable Audio Output
    ScalerSetByte_EXINT(PEF_BF_DP_CHANNEL_EN_2, 0x00);
}

//--------------------------------------------------
// Description  : RX3 Audio Frequency Mode Setting
// Input Value  : _AUDIO_TRACKING_AUTO_LOAD_MODE / _AUDIO_TRACKING_MANNUAL_MODE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3AudioFrequencyMode_8b10b_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode)
{
    if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_AUTO_LOAD_MODE)
    {
        // Set S code by HW auto
        ScalerSetBit_EXINT(PEF_58_SCODE_0, ~_BIT7, 0x00);

        // Set D code by HW auto
        ScalerSetBit_EXINT(PEF_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), _BIT6);

        // S code for 48kHz
        ScalerSetBit_EXINT(PEF_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set N code of NF PLL
        ScalerSetBit_EXINT(PEF_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));

        // Set F code of NF PLL
        ScalerSetByte_EXINT(PEF_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));
        ScalerSetByte_EXINT(PEF_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit_EXINT(PEF_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);
    }
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    else if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_MANNUAL_MODE_FIX_TARGET_FREQ)
    {
        // S code for Current Frequency
        ScalerSetBit_EXINT(PEF_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerAudioGetUserSamplingFreqSCode_EXINT0(_PORT_DP, GET_DP_RX3_TARGET_SAMPLING_FREQ()));

        // Set N code of NF PLL
        ScalerSetBit_EXINT(PEF_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_TARGET_SAMPLING_FREQ()))));

        // Set F code of NF PLL
        ScalerSetByte_EXINT(PEF_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_TARGET_SAMPLING_FREQ()))));
        ScalerSetByte_EXINT(PEF_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_TARGET_SAMPLING_FREQ()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit_EXINT(PEF_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

        // Set S code by FW manual
        ScalerSetBit_EXINT(PEF_58_SCODE_0, ~_BIT7, _BIT7);

        // Set D code by FW manual
        ScalerSetBit_EXINT(PEF_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), 0x00);
    }
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    else
    {
        // S code for User Define
        ScalerSetBit_EXINT(PEF_5A_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerAudioGetUserSamplingFreqSCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()));

        // Set N code of NF PLL
        ScalerSetBit_EXINT(PEF_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));

        // Set F code of NF PLL
        ScalerSetByte_EXINT(PEF_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));
        ScalerSetByte_EXINT(PEF_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit_EXINT(PEF_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

        // Set S code by FW manual
        ScalerSetBit_EXINT(PEF_58_SCODE_0, ~_BIT7, _BIT7);

        // Set D code by FW manual
        ScalerSetBit_EXINT(PEF_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), 0x00);
    }
}

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : RX3 Audio FIFO Tracking Enable Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3FifoTrackingEnableControl_128b132b_EXINT0(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set Boundary Tracking Water Level

        // Set boundary tracking water level final upper boound
        ScalerSetBit_EXINT(PEF_85_AUD_BDRY_3, ~_BIT4, 0x00);
        ScalerSetByte_EXINT(PEF_DC_AUD_BDRY_10, 0xA6);

        // Set boundary tracking water level initial upper boound
        ScalerSetBit_EXINT(PEF_85_AUD_BDRY_3, ~_BIT5, 0x00);
        ScalerSetByte_EXINT(PEF_8A_AUD_BDRY_8, 0x68);

        // Set boundary tracking water level Target Depth
        ScalerSetByte_EXINT(PF2_71_AUD_BUFFER_CTRL_1, 0x58);

        // Set boundary tracking water level initial lower boound
        ScalerSetByte_EXINT(PEF_8B_AUD_BDRY_9, 0x48);

        // Set boundary tracking water level final lower boound
        ScalerSetByte_EXINT(PEF_DE_AUD_BDRY_11, 0x0A);

        // Set boundary tracking Step for next boundary threshold
        ScalerSetBit_EXINT(PEF_82_AUD_BDRY_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x05);

        // Enable Boundary Tracking Method
        ScalerSetBit_EXINT(PEF_82_AUD_BDRY_0, ~_BIT7, _BIT7);

        // Enable Boundary tracking I/P code adjustment
        ScalerSetBit_EXINT(PEF_C0_AUD_BDRY_NEW_MODE_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Enable Trend Tracking Method
        ScalerSetBit_EXINT(PEF_8C_AUD_TRND_0, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable Boundary Tracking Method
        ScalerSetBit_EXINT(PEF_82_AUD_BDRY_0, ~_BIT7, 0x00);

        // Disable Boundary tracking I/P code adjustment
        ScalerSetBit_EXINT(PEF_C0_AUD_BDRY_NEW_MODE_0, ~(_BIT1 | _BIT0), 0x00);

        // Disable Trend Tracking Method
        ScalerSetBit_EXINT(PEF_8C_AUD_TRND_0, ~_BIT7, 0x00);

        // Set Double Buffer for N.F Code
        ScalerSetBit_EXINT(PEF_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : RX3 Audio FIFO Tracking Proc
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3FifoTrackingProc_128b132b_EXINT0(void)
{
    // Detect if Auido Sampling is Changed
    if(ScalerGetBit_EXINT(PF2_50_AUD_FREQUENY_DET_0, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
    {
        // Clear Auido Sampling Change Flag
        ScalerSetBit_EXINT(PF2_50_AUD_FREQUENY_DET_0, ~_BIT5, _BIT5);

        // Set Sampling Change Flag
        SET_DP_RX3_AUDIO_SAMPLING_FREQ_CHANGE();

        // Disable FIFO Tracking
        ScalerDpAudioRx3FifoTrackingEnableControl_128b132b_EXINT0(_DISABLE);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        // No Audio Detect
        if((ScalerGetBit_EXINT(PF2_52_AUD_SAMPLE_CNT_0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4) == 0x00)
        {
            // -----------------------------------------
            // Set User Define Frequency When No Audio
            // -----------------------------------------
            ScalerDpAudioRx3AudioFrequencyMode_128b132b_EXINT0(_AUDIO_TRACKING_MANNUAL_MODE);

            // Clear Flag
            CLR_DP_AUDIO_RX3_AUTO_LOAD_FREQ();
        }
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)

#if((_AUDIO_SUPPORT == _ON) && (_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE))
        // Set TTS Play Error Flag
        SET_TTS_PLAYBACK_ERROR();
#endif
    }
}

//--------------------------------------------------
// Description  : RX3 Audio Disable Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3DisableSetting_128b132b_EXINT0(void)
{
    // Disable INT for Auido Sampling Change
    ScalerSetBit_EXINT(PF2_50_AUD_FREQUENY_DET_0, ~(_BIT6 | _BIT5), 0x00);

    // -----------------------------------------
    // Disable Tracking Function
    // -----------------------------------------
    ScalerDpAudioRx3FifoTrackingEnableControl_128b132b_EXINT0(_DISABLE);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
    // No Audio Detect
    if((ScalerGetBit_EXINT(PF2_52_AUD_SAMPLE_CNT_0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4) == 0x00)
    {
        // -----------------------------------------
        // Set User Define Frequency When No Audio
        // -----------------------------------------
        ScalerDpAudioRx3AudioFrequencyMode_128b132b_EXINT0(_AUDIO_TRACKING_MANNUAL_MODE);

        // Clear Flag
        CLR_DP_AUDIO_RX3_AUTO_LOAD_FREQ();
    }
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)

    // Disable Audio Coding Type Change INT
    ScalerSetBit_EXINT(PF2_3B_DP_IRQ_CTRL1, ~_BIT0, 0x00);

    // Clear Audio Coding Type Change Flag
    ScalerSetBit_EXINT(PF2_37_DP_GLB_STATUS, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

    // Disable Audio Output
    ScalerSetByte_EXINT(PF2_BF_DP_CHANNEL_EN_2, 0x00);
}

//--------------------------------------------------
// Description  : RX3 Audio Frequency Mode Setting
// Input Value  : _AUDIO_TRACKING_AUTO_LOAD_MODE / _AUDIO_TRACKING_MANNUAL_MODE
// Output Value : None
//--------------------------------------------------
void ScalerDpAudioRx3AudioFrequencyMode_128b132b_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode)
{
    if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_AUTO_LOAD_MODE)
    {
        // Set S code by HW auto
        ScalerSetBit_EXINT(PF2_5A_SCODE_0, ~_BIT7, 0x00);

        // Set D code by HW auto
        ScalerSetBit_EXINT(PEF_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), _BIT6);

        // S code for 48kHz
        ScalerSetBit_EXINT(PF2_5C_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_SAMPLING_FREQ_48K_GROUP_S_CODE);

        // Set N code of NF PLL
        ScalerSetBit_EXINT(PEF_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));

        // Set F code of NF PLL
        ScalerSetByte_EXINT(PEF_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));
        ScalerSetByte_EXINT(PEF_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit_EXINT(PEF_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);
    }
#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    else if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_MANNUAL_MODE_FIX_TARGET_FREQ)
    {
        // S code for Current Frequency
        ScalerSetBit_EXINT(PF2_5C_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerAudioGetUserSamplingFreqSCode_EXINT0(_PORT_DP, GET_DP_RX3_TARGET_SAMPLING_FREQ()));

        // Set N code of NF PLL
        ScalerSetBit_EXINT(PEF_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_TARGET_SAMPLING_FREQ()))));

        // Set F code of NF PLL
        ScalerSetByte_EXINT(PEF_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_TARGET_SAMPLING_FREQ()))));
        ScalerSetByte_EXINT(PEF_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_TARGET_SAMPLING_FREQ()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit_EXINT(PEF_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

        // Set S code by FW manual
        ScalerSetBit_EXINT(PF2_5A_SCODE_0, ~_BIT7, _BIT7);

        // Set D code by FW manual
        ScalerSetBit_EXINT(PEF_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), 0x00);
    }
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
    else
    {
        // S code for User Define
        ScalerSetBit_EXINT(PF2_5C_SCODE_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ScalerAudioGetUserSamplingFreqSCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()));

        // Set N code of NF PLL
        ScalerSetBit_EXINT(PEF_A1_AUD_N_F_CODE_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));

        // Set F code of NF PLL
        ScalerSetByte_EXINT(PEF_A2_AUD_N_F_CODE_2, HIBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));
        ScalerSetByte_EXINT(PEF_A3_AUD_N_F_CODE_3, LOBYTE(LOWORD(ScalerAudioGetUserSamplingFreqNFCode_EXINT0(_PORT_DP, GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()))));

        // Set Double Buffer for N.F Code
        ScalerSetBit_EXINT(PEF_A0_AUD_N_F_CODE_0, ~_BIT7, _BIT7);

        // Set S code by FW manual
        ScalerSetBit_EXINT(PF2_5A_SCODE_0, ~_BIT7, _BIT7);

        // Set D code by FW manual
        ScalerSetBit_EXINT(PEF_80_AUD_PS_CTRL_0, ~(_BIT6 | _BIT5), 0x00);
    }
}
#endif // End of #if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif // End of #if(_DP_AUDIO_RX3_SUPPORT == _ON)

