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
// ID Code      : ScalerHdmiAudioRx3.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_HDMI_AUDIO_RX3__

#include "ScalerFunctionInclude.h"
#include "HdmiAudioRx3/ScalerHdmiAudioRx3.h"

#if(_HDMI_AUDIO_RX3_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructAudioDigitalInfo g_stHdmiAudioRx3DigtalInfo;
StructAudioFreqParameter g_stHdmiAudioRx3FreqParameter;

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
StructAudioFwTrackingInfo g_stHdmiAudioRx3FwTrackingInfo;
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Detect RX3 digital audio for HDMI/DP interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3DigitalDetectProc(void)
{
    EnumAudioSamplingFreqType enumAudioFreq = _AUDIO_FREQ_NO_AUDIO;

    // Get Audio Sampling Frequency
    enumAudioFreq = ScalerHdmiAudioRx3SamplingFreqDetect();

    if(enumAudioFreq != 0x00)
    {
#if((_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF) && (_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON))
        // Check Sampling Frequency Limitation
        if(enumAudioFreq > GET_HDMI_RX3_SAMPLING_FREQ_LIMIT())
        {
            // ======================================
            // SRC FS > FS Limint by user define
            // ======================================
            // Set Sampling Frequency to maximum value
            SET_HDMI_RX3_TARGET_SAMPLING_FREQ(GET_HDMI_RX3_SAMPLING_FREQ_LIMIT());

#if(_HDMI_AUDIO_FREQ_LIMIT_FORCE_DEFINE_CLK_SUPPORT == _OFF)
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
                // Disable Audio output
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_30_PORT_PAGE77_HDMI_AVMCR, ~(_BIT6 | _BIT5), _BIT5);
            }
            else
#endif
            {
                // Disable Audio output
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~(_BIT6 | _BIT5), _BIT5);
            }

#endif
            // Disable FIFO Tracking
            ScalerHdmiAudioRx3FifoTrackingProc(_DISABLE);
        }
        else
#endif
        {
            // ======================================
            // SRC FS <= FS Limint by user define
            // ======================================
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
                // Enable Audio output
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_30_PORT_PAGE77_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
            }
            else
#endif
            {
                // Enable Audio output
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
            }

            // Enable FIFO Tracking
            ScalerHdmiAudioRx3FifoTrackingProc(_ENABLE);
        }

        SET_HDMI_AUDIO_RX3_PACKET_DETECT();
        SET_HDMI_AUDIO_RX3_DIGITAL_SOURCE(_DIGITAL_AUDIO_SOURCE_HDMI);

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
        if(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() > _AUDIO_FREQ_48K)
#endif
        {
            if(GET_HDMI_AUDIO_RX3_ICODE_RELOADED() == _FALSE)
            {
                ScalerTimerReactiveTimerEvent(_AUDIO_DYNAMIC_I_CODE_TIMER_MS, _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_LOAD_STABLE_I_CODE);

                SET_HDMI_AUDIO_RX3_ICODE_RELOADED();
            }
        }
    }
    else
    {
        // ======================================
        // SRC no audio packet
        // ======================================
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
        // Set User Define Sampling Frequency when no audio
        SET_HDMI_RX3_TARGET_SAMPLING_FREQ(GET_HDMI_RX3_SAMPLING_FREQ_USER_DEFINE());

        // Enable Audio output when no audio packet
#if((_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON) && (_HDMI_AUDIO_FREQ_LIMIT_FORCE_DEFINE_CLK_SUPPORT == _OFF))
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
        {
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_30_PORT_PAGE77_HDMI_AVMCR, ~_BIT6, _BIT6);
        }
        else
#endif
        {
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~_BIT6, _BIT6);
        }
#endif
#endif
        ScalerHdmiAudioRx3FifoTrackingProc(_DISABLE);

        CLR_HDMI_AUDIO_RX3_PACKET_DETECT();
        SET_HDMI_AUDIO_RX3_DIGITAL_SOURCE(_DIGITAL_AUDIO_SOURCE_NONE);

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
        if(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() > _AUDIO_FREQ_48K)
#endif
        {
            if(GET_HDMI_AUDIO_RX3_ICODE_RELOADED() == _TRUE)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_LOAD_STABLE_I_CODE);

                ScalerHdmiAudioRx3LoadInitialICode();

                CLR_HDMI_AUDIO_RX3_ICODE_RELOADED();
            }
        }
    }
}
//--------------------------------------------------
// Description  : Get RX3 Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerHdmiAudioRx3GetAudioDetected(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    // Check HDMI2.0, 2.1 switch
    if(GET_HDMI_AUDIO_RX3_VERSION() != (ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) >> 6))
    {
        DebugMessageAudio("False : RX3 HDMI Ver Switch", 0);
        return _FALSE;
    }
#endif

    // Check audio packet
    if(GET_HDMI_AUDIO_RX3_PACKET_DETECT() == _FALSE)
    {
        DebugMessageAudio("False : RX3 Audio Packet", 0);
        return _FALSE;
    }

    // Check FW tracking state
#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
    if((GET_HDMI_AUDIO_RX3_FW_TRACKING_STATE() != _AUDIO_FW_TRACKING_PROCESS_PLAYBACK) &&
       (GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() <= _AUDIO_FREQ_48K))
    {
        DebugMessageAudio("False : RX3 Audio FW Tracking preparing", 0);
        return _FALSE;
    }
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        // Check AVMute
        if(ScalerGetBit(P77_CB_HDMI_SR, _BIT6) == _BIT6)
        {
            DebugMessageAudio("False : RX3 AVMute (HDMI21)", 0);
            return _FALSE;
        }

        // Check Audio Tracking
        if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_15_PORT_PAGE77_HDMI_PSCR, (_BIT3 | _BIT2)) == 0x00)
        {
            DebugMessageAudio("False : RX3 HDMI Audio Tracking Disable", 0);
            return _FALSE;
        }

        // Check HDMI audio FIFO overflow and underflow
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
        if((GET_HDMI_RX3_HBR_AUDIO_IS_SETTING() == _FALSE) && (ScalerGetBit(P77_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00))
#else
        if(ScalerGetBit(P77_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
#endif
        {
            DebugMessageAudio("False : RX3 Audio FIFO", ScalerGetBit(P77_CB_HDMI_SR, (_BIT2 | _BIT1)));

            if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, (_BIT2 | _BIT1)) == 0x00)
            {
                // Clear HDMI audio FIFO overflow and underflow status
                ScalerSetBit(P77_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

                ScalerTimerDelayXms(3);

                if(ScalerGetBit(P77_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
                {
                    DebugMessageAudio("False : RX3 Audio DB Retry", ScalerGetBit(P77_CB_HDMI_SR, (_BIT2 | _BIT1)));

                    // Enable Audio Normal Output, when disable fifo water level address = 0
                    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_30_PORT_PAGE77_HDMI_AVMCR, ~_BIT5, _BIT5);

                    // Delay to avoid continuous underflow
                    ScalerTimerDelayXms(3);

                    // Clear HDMI audio FIFO overflow and underflow status
                    ScalerSetBit(P77_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1), (_BIT2 | _BIT1));
                }
            }
            return _FALSE;
        }
    }
    else
#endif
    {
        // Check AVMute
        if(ScalerGetBit(P72_CB_HDMI_SR, _BIT6) == _BIT6)
        {
            DebugMessageAudio("False : RX3 AVMute (HDMI20)", 0);
            return _FALSE;
        }

        // Check Audio Tracking
        if(ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR, (_BIT3 | _BIT2)) == 0x00)
        {
            DebugMessageAudio("False : RX3 HDMI Audio Tracking Disable", 0);
            return _FALSE;
        }

        // Check HDMI audio FIFO overflow and underflow
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
        if((GET_HDMI_RX3_HBR_AUDIO_IS_SETTING() == _FALSE) && (ScalerGetBit(P72_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00))
#else
        if(ScalerGetBit(P72_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
#endif
        {
            DebugMessageAudio("False : RX3 Audio FIFO", ScalerGetBit(P72_CB_HDMI_SR, (_BIT2 | _BIT1)));

            if(ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, (_BIT2 | _BIT1)) == 0x00)
            {
                // Clear HDMI audio FIFO overflow and underflow status
                ScalerSetBit(P72_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

                ScalerTimerDelayXms(3);

                if(ScalerGetBit(P72_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00)
                {
                    DebugMessageAudio("False : RX3 Audio DB Retry", ScalerGetBit(P72_CB_HDMI_SR, (_BIT2 | _BIT1)));

                    // Enable Audio Normal Output, when disable fifo water level address = 0
                    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~_BIT5, _BIT5);

                    // Delay to avoid continuous underflow
                    ScalerTimerDelayXms(3);

                    // Clear HDMI audio FIFO overflow and underflow status
                    ScalerSetBit(P72_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1), (_BIT2 | _BIT1));
                }
            }
            return _FALSE;
        }
    }
    return _TRUE;
}
//--------------------------------------------------
// Description  : Initial RX3 HDMI audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3Initial(void)
{
    ScalerHdmiAudioRx3SetAudioPLL();

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    ScalerHdmiAudioRx3InitialForHdmiFrlMac();
#endif

    ScalerHdmiAudioRx3InitialForHdmiTmdsMac();

    CLR_HDMI_AUDIO_RX3_SAMPLING_FREQ_CHANGE();
    CLR_HDMI_AUDIO_RX3_ICODE_RELOADED();
}

//--------------------------------------------------
// Description  : Initial RX3 HDMI 20 Mac audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3InitialForHdmiTmdsMac(void)
{
    // Disable sine wave generator
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT4, 0x00);

    // Disable AVMUTE function and enable Audio FIFO Tracking main control (I/P code)
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~(_BIT7 | _BIT5), _BIT5);

    // Disable FIFO Boundary Tracking, Disable Trend Tracking, phase error count by audio clk/2
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT1));

    // IIS Freerun Counter Mode New Mode
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_0A_PORT_PAGE72_AUDIO_LD_P_TIME_M, ~(_BIT7 | _BIT1 | _BIT0), _BIT7);

    // Enable SDM
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_2D_PORT_PAGE72_HDMI_AAPNR, ~(_BIT3 | _BIT1), _BIT1);

    // Set auto gain delay mode and final gain
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_07_PORT_PAGE72_HDMI_MAG_M_FINAL, ~(_BIT3 | _BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_08_PORT_PAGE72_HDMI_MAG_L_FINAL, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_09_PORT_PAGE72_HDMI_MAG_R_FINAL, 0x00);

    // Set wait time for load parameter
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_0A_PORT_PAGE72_AUDIO_LD_P_TIME_M, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_0B_PORT_PAGE72_AUDIO_LD_P_TIME_N, 0x10);

    // Set ZCD timeout
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_0D_PORT_PAGE72_ZCD_TIMEOUT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _ZCD_TIMEOUT_DEFAULT);

    // Set Boundary Address = 5 for Boundary Tracking
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_1B_PORT_PAGE72_HDMI_FBR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Set Target afifo depth to 31 (Half of Afifo level)
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_1B_PORT_PAGE72_HDMI_FBR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

    ScalerTmdsMacRx3SetAudioClampNCode();

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
    // Set I code of boundary tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D6_PORT_PAGE72_AUD_BDRY_0, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D7_PORT_PAGE72_AUD_BDRY_1, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D8_PORT_PAGE72_AUD_BDRY_2, 0x08);

    // Set P code of boundary tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D9_PORT_PAGE72_AUD_BDRY_3, 0x07);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DA_PORT_PAGE72_AUD_BDRY_4, 0xFF);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DB_PORT_PAGE72_AUD_BDRY_5, 0xFF);

    // Set I code of trend tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DC_PORT_PAGE72_AUD_BDRY_6, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DD_PORT_PAGE72_AUD_BDRY_7, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DE_PORT_PAGE72_AUD_BDRY_8, 0x08);

    // Set P code of trend tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DF_PORT_PAGE72_AUD_BDRY_9, 0x07);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E0_PORT_PAGE72_AUD_BDRY_A, 0xFF);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E1_PORT_PAGE72_AUD_BDRY_B, 0xFF);
#else
    // Set I code of boundary tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D6_PORT_PAGE72_AUD_BDRY_0, LOBYTE(HIWORD(_HDMI_INITIAL_I_CODE)));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D7_PORT_PAGE72_AUD_BDRY_1, HIBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D8_PORT_PAGE72_AUD_BDRY_2, LOBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));

    // Set P code of boundary tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D9_PORT_PAGE72_AUD_BDRY_3, 0x12);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DA_PORT_PAGE72_AUD_BDRY_4, 0xFB);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DB_PORT_PAGE72_AUD_BDRY_5, 0xB9);

    // Set I code of trend tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DC_PORT_PAGE72_AUD_BDRY_6, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DD_PORT_PAGE72_AUD_BDRY_7, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DE_PORT_PAGE72_AUD_BDRY_8, 0x38);

    // Set P code of trend tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DF_PORT_PAGE72_AUD_BDRY_9, 0x12);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E0_PORT_PAGE72_AUD_BDRY_A, 0xFB);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E1_PORT_PAGE72_AUD_BDRY_B, 0xB9);
#endif

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
    // Disable P Code Spread
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_E2_PORT_PAGE72_P_SPREAD_0, ~_BIT7, 0x00);
#endif

    // Audio Normal Output
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Disable Audio Watchdog for FIFO Overflow/Underflow
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);

    // Set X Value
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_32_PORT_PAGE72_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set Y Value
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_33_PORT_PAGE72_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Bit2: When no audio or changing sampling rate, AFSM load double buffer one more.
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_9F_PORT_PAGE72_PRESET_AFSM_MOD, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2));

    // Seperate the detected sampling frequency
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8B_PORT_PAGE72_AUDIO_FREQ_RESULT, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set 2ms for auto frequency detecttion
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8C_PORT_PAGE72_AUDIO_FREQ_RESULT_M, ~(_BIT6 | _BIT5), _BIT5);

    // Change audio clk divider according to SYSCLK = 27MHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_8E_PORT_PAGE72_XTAL_DIV, _AUTO_FREQ_DETECT_XTAL_DIV);

    // Set threshold to separate sampling frequency
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_90_PORT_PAGE72_TH1, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_91_PORT_PAGE72_TH2, 0x28);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_92_PORT_PAGE72_TH3, 0x4C);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_93_PORT_PAGE72_TH4, 0x5C);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_94_PORT_PAGE72_TH5, 0x70);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)
    // Disable Auto Load S & NF Code
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT6 | _BIT5), 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // Set S code for 32kHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D5_PORT_PAGE72_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set NF code for 32kHz
    ScalerTmdsMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE);
    ScalerTmdsMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // Set S code for 44.1kHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D5_PORT_PAGE72_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // Set NF code for 44.1kHz
    ScalerTmdsMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE);
    ScalerTmdsMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE);

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // Set S code for 48kHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D5_PORT_PAGE72_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set NF code for 48kHz
    ScalerTmdsMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE);
    ScalerTmdsMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE);

#endif

    // Set Double Buffer bit
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // Load NF code
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);

#else

    // ----- ----------------------------------------
    // Initial 32kHz S/N.F Code of FW load
    // ----------------------------------------------
    // Disable Auto Load S Code
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT6 | _BIT5), 0x00);

    // Set S code for 32kHz
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D5_PORT_PAGE72_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set NF code for 32kHz
    ScalerTmdsMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE);
    ScalerTmdsMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);

    // Set Double Buffer bit
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // Load NF code
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);

    // ----------------------------------------------------
    // Initial 3 Group S/ NF Code value for HW auto load
    // ----------------------------------------------------
    // Set S code for auto load mode
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_CC_PORT_PAGE72_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_CD_PORT_PAGE72_PRESET_S_CODE1, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_CE_PORT_PAGE72_PRESET_S_CODE2, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set NF code for auto load mode
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_C0_PORT_PAGE72_PRESET_NF_CODE_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE & 0x1F));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_C1_PORT_PAGE72_PRESET_NF_CODE_1, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_C2_PORT_PAGE72_PRESET_NF_CODE_2, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE));

    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_C3_PORT_PAGE72_PRESET_NF_CODE_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE & 0x1F));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_C4_PORT_PAGE72_PRESET_NF_CODE_4, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_C5_PORT_PAGE72_PRESET_NF_CODE_5, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE));

    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_C6_PORT_PAGE72_PRESET_NF_CODE_6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE & 0x1F));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_C7_PORT_PAGE72_PRESET_NF_CODE_7, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_C8_PORT_PAGE72_PRESET_NF_CODE_8, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE));

    // Enable Auto Load S Code
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT6 | _BIT5), _BIT6);

    // Set Double Buffer bit
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // Set User Define Frequency When No Audio
    ScalerHdmiAudioRx3AudioFrequencyModeForHdmiTmdsMac(_AUDIO_TRACKING_MANNUAL_MODE);
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
    // Audio Tracking Reset
    ScalerHdmiAudioRx3FwTrackingResetForHdmiTmdsMac();
#endif

#if(_HDMI_AUDIO_IGNORE_FLAT_FLAG_SUPPORT == _ON)
    // Receive flat flag, force 0
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_2E_PORT_PAGE72_HDMI_APDMCR, ~(_BIT7 | _BIT6), _BIT6);
#endif

    // Enable Audio Freq Detect, Disable Samping Freq. Change INT
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), _BIT7);

#if(_DIGITAL_AUDIO_OUTPUT_FORCE_CHANNEL_0_1_SUPPORT == _ON)
    // Force I2S/SPDIF Output Form Channel 0/1
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_61_PORT_PAGE72_HDMI_ALCR, 0x00);
#endif

    // Enable SPDIF/I2S Output
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_62_PORT_PAGE72_HDMI_AOCR, 0xFF);

    // CLR PLL Autoload Status Flag
    CLR_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ();
}

//--------------------------------------------------
// Description  : Load initial I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3LoadInitialICode(void)
{
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        // Set Stable I code for boundary tracking for HDMI audio
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D6_PORT_PAGE77_AUD_BDRY_0, 0x00);
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D7_PORT_PAGE77_AUD_BDRY_1, 0x00);
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D8_PORT_PAGE77_AUD_BDRY_2, 0x08);
    }
    else
#endif
    {
        // Set Stable I code for boundary tracking for HDMI audio
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D6_PORT_PAGE72_AUD_BDRY_0, 0x00);
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D7_PORT_PAGE72_AUD_BDRY_1, 0x00);
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D8_PORT_PAGE72_AUD_BDRY_2, 0x08);
    }
#else
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        // Set Initial I code for boundary tracking for HDMI audio
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D6_PORT_PAGE77_AUD_BDRY_0, LOBYTE(HIWORD(_HDMI_INITIAL_I_CODE)));
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D7_PORT_PAGE77_AUD_BDRY_1, HIBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D8_PORT_PAGE77_AUD_BDRY_2, LOBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));
    }
    else
#endif
    {
        // Set Initial I code for boundary tracking for HDMI audio
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D6_PORT_PAGE72_AUD_BDRY_0, LOBYTE(HIWORD(_HDMI_INITIAL_I_CODE)));
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D7_PORT_PAGE72_AUD_BDRY_1, HIBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D8_PORT_PAGE72_AUD_BDRY_2, LOBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));
    }
#endif

    DebugMessageAudio("Load initial I code", _HDMI_INITIAL_I_CODE);
}

//--------------------------------------------------
// Description  : Timer Event to Load Stable I Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3LoadStableICodeEvent(void)
{
#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        // Set Stable I code for boundary tracking for HDMI audio
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D6_PORT_PAGE77_AUD_BDRY_0, 0x00);
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D7_PORT_PAGE77_AUD_BDRY_1, 0x00);
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D8_PORT_PAGE77_AUD_BDRY_2, 0x08);
    }
    else
#endif
    {
        // Set Stable I code for boundary tracking for HDMI audio
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D6_PORT_PAGE72_AUD_BDRY_0, 0x00);
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D7_PORT_PAGE72_AUD_BDRY_1, 0x00);
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D8_PORT_PAGE72_AUD_BDRY_2, 0x08);
    }
#else
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        // Set Stable I code for boundary tracking for HDMI audio
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D6_PORT_PAGE77_AUD_BDRY_0, LOBYTE(HIWORD(_HDMI_STABLE_I_CODE)));
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D7_PORT_PAGE77_AUD_BDRY_1, HIBYTE(LOWORD(_HDMI_STABLE_I_CODE)));
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D8_PORT_PAGE77_AUD_BDRY_2, LOBYTE(LOWORD(_HDMI_STABLE_I_CODE)));
    }
    else
#endif
    {
        // Set Stable I code for boundary tracking for HDMI audio
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D6_PORT_PAGE72_AUD_BDRY_0, LOBYTE(HIWORD(_HDMI_STABLE_I_CODE)));
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D7_PORT_PAGE72_AUD_BDRY_1, HIBYTE(LOWORD(_HDMI_STABLE_I_CODE)));
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D8_PORT_PAGE72_AUD_BDRY_2, LOBYTE(LOWORD(_HDMI_STABLE_I_CODE)));
    }
#endif

    DebugMessageAudio("Load stable I code", _HDMI_STABLE_I_CODE);
}

//--------------------------------------------------
// Description  : Detect RX3 Audio Sampling Freq
// Input Value  : None
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqType ScalerHdmiAudioRx3SamplingFreqDetect(void)
{
    EnumAudioSamplingFreqType enumAudioFreq = _AUDIO_FREQ_NO_AUDIO;

#if((_AUDIO_SUPPORT == _ON) && (_INTERNAL_AUDIO_TEST_SUPPORT == _ON))
    if(ScalerHdmiAudioRx3GetInternalAudioGenEnable() == _ENABLE)
    {
        // For Audio test pattern
        SET_HDMI_AUDIO_RX3_SAMPLING_FREQ(GET_AUDIO_GEN_FREQ_MAPPING());
        return GET_AUDIO_GEN_FREQ_MAPPING();
    }
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        enumAudioFreq = ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8B_PORT_PAGE77_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
#endif
    {
        enumAudioFreq = ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8B_PORT_PAGE72_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(enumAudioFreq != GET_HDMI_AUDIO_RX3_SAMPLING_FREQ())
    {
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
    }
#endif

    SET_HDMI_AUDIO_RX3_SAMPLING_FREQ(enumAudioFreq);

    return enumAudioFreq;
}

//--------------------------------------------------
// Description  : Initial RX3 Auido PLL Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3SetAudioPLL(void)
{
    // Set Icp, VCO band, O code...
    ScalerTmdsMacRx3SetAudioPLLOffProc();

    // Set N.F Code
    ScalerHdmiAudioRx3SetAudioPLLOnProc();
}

//--------------------------------------------------
// Description  : Set Rx3 HDMI Audio On Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3SetAudioPLLOnProc(void)
{
    // DPLL power on
    ScalerSetBit(P72_87_PORT_PAGE72_HDMI_DPLL_ANASET_1, ~_BIT0, 0x00);

    // Delay 2000us
    ScalerTimerDelayXms(2);

    // Enable CK_VCODIV2 & DIV4 [7]
    ScalerSetBit(P72_86_PORT_PAGE72_HDMI_DPLL_ANASET_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        // Set NF code
        ScalerHdmiFrlMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE);
        ScalerHdmiFrlMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);

        // Set double buffer
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Load N.F code [5]
        // set Normal phase interpolation
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT5 | _BIT4), _BIT5);
    }
    else
#endif
    {
        // Set NF code
        ScalerTmdsMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE);
        ScalerTmdsMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);

        // Set double buffer
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Load N.F code [5]
        // set Normal phase interpolation
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT5 | _BIT4), _BIT5);
    }

    // Delay 2000us
    ScalerTimerDelayXms(2);
}

//--------------------------------------------------
// Description  : RX3 Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3WatchDogProc(bit bOn)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        if(bOn == _ON)
        {
            // Clear audio FIFO overflow and underflow status
            ScalerSetBit(P77_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Audio Watch Dog for FIFO Overflow/Underflow
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
        }
        else
        {
            // Disable Audio Watch Dog for FIFO Overflow/Underflow
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);
        }
    }
    else
#endif
    {
        if(bOn == _ON)
        {
            // Clear audio FIFO overflow and underflow status
            ScalerSetBit(P72_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Audio Watch Dog for FIFO Overflow/Underflow
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
        }
        else
        {
            // Disable Audio Watch Dog for FIFO Overflow/Underflow
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Check Audio Sampling Frequency Ever Change
// Input Value  : None
// Output Value : _TRUE => Change / _FALSE => No Change
//--------------------------------------------------
bit ScalerHdmiAudioRx3SamplingFreqChange(void)
{
    if(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ_CHANGE() == _TRUE)
    {
        // Clear Change Flag when check
        CLR_HDMI_AUDIO_RX3_SAMPLING_FREQ_CHANGE();

        return _TRUE;
    }

    return _FALSE;
}

#if(_HW_HDMI_AUDIO_8CH_LAYOUT_NORMAL_OUTPUT == _OFF)
//--------------------------------------------------
// Description  : Rx3 I2s/Spdif Channel Output Select
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3I2sSpdifChannelOutputSelect(EnumAudioIisSpdifOutput enumAudioIisSpdifOutput)
{
    BYTE ucSelect = ScalerAudioChannelOutputSel(GET_HDMI_AUDIO_RX3_CHANNEL_ALLOCATION());

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        if(enumAudioIisSpdifOutput == _AUDIO_SELECT_BY_CA_MODE)
        {
            // SPDIF/I2S 4 lane Output Select By Audio Channel Allocation
            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_62_PORT_PAGE77_HDMI_AOCR, ((ucSelect << 4) | ucSelect));
        }
        else
        {
            // Enable SPDIF/I2S 4 lane Output
            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_62_PORT_PAGE77_HDMI_AOCR, 0xFF);
        }
    }
    else
#endif
    {
        if(enumAudioIisSpdifOutput == _AUDIO_SELECT_BY_CA_MODE)
        {
            // SPDIF/I2S 4 lane Output Select By Audio Channel Allocation
            ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_62_PORT_PAGE72_HDMI_AOCR, ((ucSelect << 4) | ucSelect));
        }
        else
        {
            // Enable SPDIF/I2S 4 lane Output
            ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_62_PORT_PAGE72_HDMI_AOCR, 0xFF);
        }
    }
}
#endif

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial HDMI/DP audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdmiAudioRx3CheckVersionChange(void)
{
    return (GET_HDMI_AUDIO_RX3_VERSION() != (ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) >> 6)) ? _TRUE : _FALSE;
}

//--------------------------------------------------
// Description  : Initial HDMI/DP audio setting
// Input Value  : None
// Output Value : 1: hdmi2.1    0:hdmi2.0
//--------------------------------------------------
bit ScalerHdmiAudioRx3SetVersion(void)
{
    return SET_HDMI_AUDIO_RX3_VERSION(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) >> 6);
}

//--------------------------------------------------
// Description  : Initial RX3 HDMI 21 Mac audio setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3InitialForHdmiFrlMac(void)
{
    // Disable sine wave generator
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~_BIT4, 0x00);

    // Disable AVMUTE function and enable Audio FIFO Tracking main control (I/P code)
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~(_BIT7 | _BIT5), _BIT5);

    // Disable FIFO Boundary Tracking, Disable Trend Tracking, phase error count by audio clk/2
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_15_PORT_PAGE77_HDMI_PSCR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT1));

    // IIS Freerun Counter Mode New Mode
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_0A_PORT_PAGE77_AUDIO_LD_P_TIME_M, ~(_BIT7 | _BIT1 | _BIT0), _BIT7);

    // Enable SDM
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_2D_PORT_PAGE77_HDMI_AAPNR, ~(_BIT3 | _BIT1), _BIT1);

    // Set auto gain delay mode and final gain
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_07_PORT_PAGE77_HDMI_MAG_M_FINAL, ~(_BIT3 | _BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_08_PORT_PAGE77_HDMI_MAG_L_FINAL, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_09_PORT_PAGE77_HDMI_MAG_R_FINAL, 0x00);

    // Set wait time for load parameter
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_0A_PORT_PAGE77_AUDIO_LD_P_TIME_M, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_0B_PORT_PAGE77_AUDIO_LD_P_TIME_N, 0x10);

    // Set ZCD timeout
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_0D_PORT_PAGE77_ZCD_TIMEOUT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _ZCD_TIMEOUT_DEFAULT);

    // Set Boundary Address = 5 for Boundary Tracking
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_1B_PORT_PAGE77_HDMI_FBR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Set Target afifo depth to 31 (Half of Afifo level)
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_1B_PORT_PAGE77_HDMI_FBR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

    ScalerHdmiFrlMacRx3SetAudioClampNCode();

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
    // Set I code of boundary tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D6_PORT_PAGE77_AUD_BDRY_0, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D7_PORT_PAGE77_AUD_BDRY_1, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D8_PORT_PAGE77_AUD_BDRY_2, 0x08);

    // Set P code of boundary tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D9_PORT_PAGE77_AUD_BDRY_3, 0x07);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DA_PORT_PAGE77_AUD_BDRY_4, 0xFF);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DB_PORT_PAGE77_AUD_BDRY_5, 0xFF);

    // Set I code of trend tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DC_PORT_PAGE77_AUD_BDRY_6, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DD_PORT_PAGE77_AUD_BDRY_7, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DE_PORT_PAGE77_AUD_BDRY_8, 0x08);

    // Set P code of trend tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DF_PORT_PAGE77_AUD_BDRY_9, 0x07);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E0_PORT_PAGE77_AUD_BDRY_A, 0xFF);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E1_PORT_PAGE77_AUD_BDRY_B, 0xFF);
#else
    // Set I code of boundary tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D6_PORT_PAGE77_AUD_BDRY_0, LOBYTE(HIWORD(_HDMI_INITIAL_I_CODE)));
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D7_PORT_PAGE77_AUD_BDRY_1, HIBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D8_PORT_PAGE77_AUD_BDRY_2, LOBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));

    // Set P code of boundary tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D9_PORT_PAGE77_AUD_BDRY_3, 0x12);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DA_PORT_PAGE77_AUD_BDRY_4, 0xFB);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DB_PORT_PAGE77_AUD_BDRY_5, 0xB9);

    // Set I code of trend tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DC_PORT_PAGE77_AUD_BDRY_6, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DD_PORT_PAGE77_AUD_BDRY_7, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DE_PORT_PAGE77_AUD_BDRY_8, 0x38);

    // Set P code of trend tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DF_PORT_PAGE77_AUD_BDRY_9, 0x12);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E0_PORT_PAGE77_AUD_BDRY_A, 0xFB);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E1_PORT_PAGE77_AUD_BDRY_B, 0xB9);
#endif

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
    // Disable P Code Spread
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_E2_PORT_PAGE77_P_SPREAD_0, ~_BIT7, 0x00);
#endif

    // Audio Normal Output
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_30_PORT_PAGE77_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Disable Audio Watchdog for FIFO Overflow/Underflow
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);

    // Set X Value
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_32_PORT_PAGE77_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set Y Value
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_33_PORT_PAGE77_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Bit2: When no audio or changing sampling rate, AFSM load double buffer one more.
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_9F_PORT_PAGE77_PRESET_AFSM_MOD, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2));

    // Seperate the detected sampling frequency
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8B_PORT_PAGE77_AUDIO_FREQ_RESULT, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

    // Set 2ms for auto frequency detecttion
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8C_PORT_PAGE77_AUDIO_FREQ_RESULT_M, ~(_BIT6 | _BIT5), _BIT5);

    // Change audio clk divider according to SYSCLK = 27MHz
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_8E_PORT_PAGE77_XTAL_DIV, _AUTO_FREQ_DETECT_XTAL_DIV);

    // Set threshold to separate sampling frequency
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_90_PORT_PAGE77_TH1, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_91_PORT_PAGE77_TH2, 0x28);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_92_PORT_PAGE77_TH3, 0x4C);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_93_PORT_PAGE77_TH4, 0x5C);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_94_PORT_PAGE77_TH5, 0x70);

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)
    // Disable Auto Load S & NF Code
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT6 | _BIT5), 0x00);

#if(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_32KHZ)

    // Set S code for 32kHz
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D5_PORT_PAGE77_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set NF code for 32kHz
    ScalerHdmiFrlMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE);
    ScalerHdmiFrlMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);

#elif(_FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_44_1KHZ)

    // Set S code for 44.1kHz
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D5_PORT_PAGE77_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);

    // Set NF code for 44.1kHz
    ScalerHdmiFrlMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE);
    ScalerHdmiFrlMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE);

#else // _FIX_SAMPLING_FREQ_TYPE == _FIX_FREQ_48KHZ

    // Set S code for 48kHz
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D5_PORT_PAGE77_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set NF code for 48kHz
    ScalerHdmiFrlMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE);
    ScalerHdmiFrlMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE);

#endif

    // Set Double Buffer bit
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // Load NF code
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);

#else

    // ----- ----------------------------------------
    // Initial 32kHz S/N.F Code of FW load
    // ----------------------------------------------
    // Disable Auto Load S Code
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT6 | _BIT5), 0x00);

    // Set S code for 32kHz
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D5_PORT_PAGE77_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

    // Set NF code for 32kHz
    ScalerHdmiFrlMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE);
    ScalerHdmiFrlMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);

    // Set Double Buffer bit
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // Load NF code
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);

    // ----------------------------------------------------
    // Initial 3 Group S/ NF Code value for HW auto load
    // ----------------------------------------------------
    // Set S code for auto load mode
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_CC_PORT_PAGE77_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_CD_PORT_PAGE77_PRESET_S_CODE1, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_CE_PORT_PAGE77_PRESET_S_CODE2, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

    // Set NF code for auto load mode
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_C0_PORT_PAGE77_PRESET_NF_CODE_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE & 0x1F));
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_C1_PORT_PAGE77_PRESET_NF_CODE_1, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE));
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_C2_PORT_PAGE77_PRESET_NF_CODE_2, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE));

    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_C3_PORT_PAGE77_PRESET_NF_CODE_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE & 0x1F));
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_C4_PORT_PAGE77_PRESET_NF_CODE_4, HIBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE));
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_C5_PORT_PAGE77_PRESET_NF_CODE_5, LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE));

    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_C6_PORT_PAGE77_PRESET_NF_CODE_6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE & 0x1F));
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_C7_PORT_PAGE77_PRESET_NF_CODE_7, HIBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE));
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_C8_PORT_PAGE77_PRESET_NF_CODE_8, LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE));

    // Enable Auto Load S Code
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT6 | _BIT5), _BIT6);

    // Set Double Buffer bit
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // Set User Define Frequency When No Audio
    ScalerHdmiAudioRx3AudioFrequencyModeForHdmiFrlMac(_AUDIO_TRACKING_MANNUAL_MODE);
#endif // End of #if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _ON)

#if(_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
    // Audio Tracking Reset
    ScalerHdmiAudioRx3FwTrackingResetForHdmiFrlMac();
#endif

#if(_HDMI_AUDIO_IGNORE_FLAT_FLAG_SUPPORT == _ON)
    // Receive flat flag, force 0
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_2E_PORT_PAGE77_HDMI_PCBPSR4, ~(_BIT7 | _BIT6), _BIT6);
#endif

    // Enable Audio Freq Detect, Disable Samping Freq. Change INT
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8A_PORT_PAGE77_AUDIO_FREQDET, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), _BIT7);

#if(_DIGITAL_AUDIO_OUTPUT_FORCE_CHANNEL_0_1_SUPPORT == _ON)
    // Force I2S/SPDIF Output Form Channel 0/1
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_61_PORT_PAGE77_HDMI_ALCR, 0x00);
#endif

    // Enable SPDIF/I2S Output
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_62_PORT_PAGE77_HDMI_AOCR, 0xFF);

    // CLR PLL Autoload Status Flag
    CLR_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ_FOR_FRL();
}

//--------------------------------------------------
// Description  : RX3 Audio Frequency Mode Setting
// Input Value  : _AUDIO_TRACKING_AUTO_LOAD_MODE / _AUDIO_TRACKING_MANNUAL_MODE
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3AudioFrequencyModeForHdmiFrlMac(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode)
{
    if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_AUTO_LOAD_MODE)
    {
        // Set S code for auto load mode
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_CC_PORT_PAGE77_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

        // Set NF code for auto load mode
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_C0_PORT_PAGE77_PRESET_NF_CODE_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE & 0x1F));
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_C1_PORT_PAGE77_PRESET_NF_CODE_1, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE));
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_C2_PORT_PAGE77_PRESET_NF_CODE_2, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE));

        // Enable Auto Load S Code
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT6 | _BIT5), _BIT6);

        // Set Double Buffer bit
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);
    }
    else
    {
        // Disable Auto Load S & NF Code
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT6 | _BIT5), 0x00);

        // Set S code User Define
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D5_PORT_PAGE77_HDMI_SCAPR, ScalerAudioGetUserSamplingFreqSCode(_PORT_HDMI, GET_HDMI_RX3_SAMPLING_FREQ_USER_DEFINE()));

        // Set NF code User Define
        ScalerHdmiFrlMacRx3SetAudioNCode(LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX3_SAMPLING_FREQ_USER_DEFINE()))));
        ScalerHdmiFrlMacRx3SetAudioFCode(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX3_SAMPLING_FREQ_USER_DEFINE())));

        // Set Double Buffer bit
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Load NF code
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);
    }
}

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDMI Rx3 FW tracking Initial For Hdmi2.1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwTrackingInitialForHdmiFrlMac(void)
{
    g_stHdmiAudioRx3FwTrackingInfo.b1AudioFwTrackStable = 0x00;
    g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = 0x00;
    g_stHdmiAudioRx3FwTrackingInfo.ucAudioFreqRecord = ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8B_PORT_PAGE77_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Read afifo Water level New Mode
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_14_PORT_PAGE77_HDMI_DCAPR1, ~(_BIT7 | _BIT6), _BIT7);

    // Set I code of boundary tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D6_PORT_PAGE77_AUD_BDRY_0, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D7_PORT_PAGE77_AUD_BDRY_1, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D8_PORT_PAGE77_AUD_BDRY_2, 0x00);

    // Set P code of boundary tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D9_PORT_PAGE77_AUD_BDRY_3, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DA_PORT_PAGE77_AUD_BDRY_4, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DB_PORT_PAGE77_AUD_BDRY_5, 0x00);

    // Set I code of trend tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DC_PORT_PAGE77_AUD_BDRY_6, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DD_PORT_PAGE77_AUD_BDRY_7, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DE_PORT_PAGE77_AUD_BDRY_8, 0x00);

    // Set P code of trend tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DF_PORT_PAGE77_AUD_BDRY_9, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E0_PORT_PAGE77_AUD_BDRY_A, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E1_PORT_PAGE77_AUD_BDRY_B, 0x00);

    // Disable Auto Load S/D Code
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT6 | _BIT5), 0x00);
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // Initialize N/F Code for FW Audio Tracking
    ScalerHdmiAudioRx3FwLoadNfPll();

    CLR_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT();

    // When the stable N.F Code is not found within 4 seconds, tracking state force to playback for play audio
    ScalerTimerReactiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT);

    // Disable Reset Audio Clock When Set Double Buffer
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8B_PORT_PAGE77_AUDIO_FREQ_RESULT, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : HDMI Rx3 FW Tracking Reset For Hdmi2.1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwTrackingResetForHdmiFrlMac(void)
{
    g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = 0;

    // Enable Reset Audio Clock When Set Double Buffer
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8B_PORT_PAGE77_AUDIO_FREQ_RESULT, ~_BIT7, 0x00);

    CLR_HDMI_AUDIO_RX3_FW_TRACKING_RESET();

    SET_HDMI_AUDIO_RX3_FW_TRACKING_STATE(_AUDIO_FW_TRACKING_INITIAL);

    // Set I code of boundary tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D6_PORT_PAGE77_AUD_BDRY_0, LOBYTE(HIWORD(_HDMI_INITIAL_I_CODE)));
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D7_PORT_PAGE77_AUD_BDRY_1, HIBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D8_PORT_PAGE77_AUD_BDRY_2, LOBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));

    // Set P code of boundary tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D9_PORT_PAGE77_AUD_BDRY_3, 0x12);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DA_PORT_PAGE77_AUD_BDRY_4, 0xFB);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DB_PORT_PAGE77_AUD_BDRY_5, 0xB9);

    // Set I code of trend tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DC_PORT_PAGE77_AUD_BDRY_6, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DD_PORT_PAGE77_AUD_BDRY_7, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DE_PORT_PAGE77_AUD_BDRY_8, 0x38);

    // Set P code of trend tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DF_PORT_PAGE77_AUD_BDRY_9, 0x12);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E0_PORT_PAGE77_AUD_BDRY_A, 0xFB);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E1_PORT_PAGE77_AUD_BDRY_B, 0xB9);

    // Auto Load S/N.F Code
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Set Double Buffer
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // Read afifo Water level Old Mode
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_14_PORT_PAGE77_HDMI_DCAPR1, ~(_BIT7 | _BIT6), 0x00);

    CLR_HDMI_AUDIO_RX3_FW_TRACKING_EVENT();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_FW_TRACKING_PREPARING);

    CLR_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT);

    CLR_HDMI_AUDIO_RX3_WL_TARGET_DIRECTION();
}

//--------------------------------------------------
// Description  : HDMI Rx3 FW Preparing Tracking For Hdmi2.1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwPreparingTrackingForHdmiFrlMac(void)
{
    // check WL, adjust N.Fcode
    WORD usbackupSumc = 0x00;
    BYTE ucAfifoCurrent = 0x00;

    // Pop up afifo Water level
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_14_PORT_PAGE77_HDMI_DCAPR1, ~_BIT6, _BIT6);

    // Get Current AFIFO Water level
    ucAfifoCurrent = ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_16_PORT_PAGE77_HDMI_FDDR);

    // Get current SUMC
    ScalerGetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E9_PORT_PAGE77_NF_FINAL1, 2, &pData[0], _AUTOINC);
    usbackupSumc = (((WORD)pData[0] << 8) | pData[1]);

    // AFIFO water level going up -> Increase N.F code
    if((ucAfifoCurrent > (g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup + 0x04)) ||
       (ucAfifoCurrent >= 0x30))
    {
        if(ucAfifoCurrent < 0x30)
        {
            if((GET_HDMI_AUDIO_RX3_WL_TARGET_DIRECTION() == _AUDIO_WL_GOES_UP) &&
               (ucAfifoCurrent >= (g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup + 0x04)))
            {
                DebugMessageAudio("RX3 Audio: AFIFO has gone up", ucAfifoCurrent);

                // set stable count = _stable_cnt/2
                g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2);
            }
            else
            {
                if(g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt < (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2))
                {
                    usbackupSumc += ((_AUDIO_FW_TRCK_FIRST_STABLE_CNT - g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt) * (ucAfifoCurrent - (g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup + 0x01)));
                }
                else
                {
                    usbackupSumc += 0x02;
                }

                // Set F code
                ScalerHdmiFrlMacRx3SetAudioFCode(usbackupSumc);

                // Set Double Buffer bit
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

                // Load N.F code
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);

                // Set stable count = 0
                g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = 0x00;

                DebugMessageAudio("RX3 Audio: AFIFO current", ucAfifoCurrent);
                DebugMessageAudio("RX3 Audio: SUMC+", usbackupSumc);
            }
        }
        else
        {
            usbackupSumc += 0x10;

            // Set F code
            ScalerHdmiFrlMacRx3SetAudioFCode(usbackupSumc);

            // Set Double Buffer bit
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

            // Load NF code
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);

            // Set stable count = 0
            g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = 0x00;

            DebugMessageAudio("RX3 Audio: AFIFO Full", ucAfifoCurrent);
            DebugMessageAudio("RX3 Audio: SUMC+ Full", usbackupSumc);
        }

        SET_HDMI_AUDIO_RX3_WL_TARGET_DIRECTION(_AUDIO_WL_GOES_DOWN);

        // Reset AFIFO water level backup
        g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;
    }
    else if((ucAfifoCurrent < (g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup - 0x04)) ||
            (ucAfifoCurrent <= 0x10))  // AFIFO water level going down -> Decrease N.Fcode
    {
        if(ucAfifoCurrent > 0x10)
        {
            if((GET_HDMI_AUDIO_RX3_WL_TARGET_DIRECTION() == _AUDIO_WL_GOES_DOWN) &&
               (ucAfifoCurrent <= (g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup - 0x04)))
            {
                DebugMessageAudio("RX3 Audio: AFIFO has gone down", ucAfifoCurrent);

                // set stable count = _stable_cnt/2
                g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2);
            }
            else
            {
                if(g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt < (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2))
                {
                    usbackupSumc -= ((_AUDIO_FW_TRCK_FIRST_STABLE_CNT - g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt) * ((g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup - 0x01) - ucAfifoCurrent));
                }
                else
                {
                    usbackupSumc -= 0x02;
                }

                // Set F code
                ScalerHdmiFrlMacRx3SetAudioFCode(usbackupSumc);

                // Set Double Buffer bit
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

                // Load N.F code
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);

                // Set stable count = 0
                g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = 0x00;

                DebugMessageAudio("RX3 Audio: AFIFO current", ucAfifoCurrent);
                DebugMessageAudio("RX3 Audio: SUMC-", usbackupSumc);
            }
        }
        else
        {
            usbackupSumc -= 0x10;

            // Set F code
            ScalerHdmiFrlMacRx3SetAudioFCode(usbackupSumc);

            // Set Double Buffer bit
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

            // Load NF code
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);

            // Set stable count = 0
            g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = 0x00;

            DebugMessageAudio("RX3 Audio: AFIFO Empty", ucAfifoCurrent);
            DebugMessageAudio("RX3 Audio: SUMC- Empty", usbackupSumc);
        }

        SET_HDMI_AUDIO_RX3_WL_TARGET_DIRECTION(_AUDIO_WL_GOES_UP);

        // Reset AFIFO water level backup
        g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;
    }
    else    // AfifoBackup-4 < AfifoCurrent < AfifoBackup+4
    {
        if(g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt < _AUDIO_FW_TRCK_FIRST_STABLE_CNT)
        {
            g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt++;
        }
    }

    // check stable
    if(g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt >= _AUDIO_FW_TRCK_FIRST_STABLE_CNT)
    {
        // Set stable SUMC
        g_stHdmiAudioRx3FwTrackingInfo.b1AudioFwTrackStable = 0x01;

        DebugMessageAudio("RX3 Audio: Find Stable SUMC", g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup);
    }
}

//--------------------------------------------------
// Description  : HDMI Rx3 FW Boundary Tracking For Hdmi2.0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwBoundaryTrackingForHdmiFrlMac(void)
{
    // check WL, adjust N.Fcode
    WORD usbackupSumc = 0x00;
    BYTE ucAfifoCurrent = 0x00;

    // Pop up afifo Water level
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_14_PORT_PAGE77_HDMI_DCAPR1, ~_BIT6, _BIT6);

    // get current WL
    ucAfifoCurrent = ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_16_PORT_PAGE77_HDMI_FDDR);

    // get current Dcode
    ScalerGetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E9_PORT_PAGE77_NF_FINAL1, 2, &pData[0], _AUTOINC);
    usbackupSumc = (((WORD)pData[0] << 8) | pData[1]);

    // WL goes up, set larger N.Fcode
    if(((ucAfifoCurrent > 0x24) && (ucAfifoCurrent > g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup)) ||
       (ucAfifoCurrent > 0x30))
    {
        DebugMessageAudio("RX3 Audio: Boundary up", g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup);
        DebugMessageAudio("RX3 Audio: SUMC+", usbackupSumc);

        if(ucAfifoCurrent > 0x30)
        {
            usbackupSumc += 0x10;
        }
        else
        {
            usbackupSumc += ((ucAfifoCurrent - 0x24 + 0x01) * 0x02);
        }

        // Reset AFIFO water level backup
        g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;

        // Set F code
        ScalerHdmiFrlMacRx3SetAudioFCode(usbackupSumc);

        // Set Double Buffer bit
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Load NF code
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);
    }

    // WL goes down, set smaller Dcode
    if(((ucAfifoCurrent < 0x1C) && (ucAfifoCurrent < g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup)) ||
       (ucAfifoCurrent < 0x10))
    {
        DebugMessageAudio("RX3 Audio: Boundary down", g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup);
        DebugMessageAudio("RX3 Audio: SUMC-", usbackupSumc);

        if(ucAfifoCurrent < 0x10)
        {
            usbackupSumc -= 0x10;
        }
        else
        {
            usbackupSumc -= ((0x1C - ucAfifoCurrent + 0x01) * 0x02);
        }

        // Reset AFIFO water level backup
        g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;

        // Set F code
        ScalerHdmiFrlMacRx3SetAudioFCode(usbackupSumc);

        // Set Double Buffer bit
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Load NF code
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);
    }
}
#endif
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerHdmiAudioRx3GetInternalAudioGenEnable(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, _BIT4) == _BIT4)
        {
            return _ENABLE;
        }
        else
        {
            return _DISABLE;
        }
    }
    else
#endif
    {
        if(ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, _BIT4) == _BIT4)
        {
            return _ENABLE;
        }
        else
        {
            return _DISABLE;
        }
    }
}
//--------------------------------------------------
// Description  : RX3 Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3InternalAudioGenSwitch(bit bOn, EnumAudioLeftRightChannelSelect enumAudioLeftRightChannelSelect)
{
    enumAudioLeftRightChannelSelect = enumAudioLeftRightChannelSelect;

    if(bOn == _ON)
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
        {
            DebugMessageAudio("RX3 HDMI 2.1 Audio Test On", ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, _BIT4));

            // Disable audio FIFO and Enable audio internal generator
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

            // Audio Normal Output
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_30_PORT_PAGE77_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            // Set S code by user define
            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D5_PORT_PAGE77_HDMI_SCAPR, GET_AUDIO_GEN_FREQ_S_CODE());

            // Set NF code by user define
            ScalerHdmiFrlMacRx3SetAudioNCode(GET_AUDIO_GEN_FREQ_N_CODE());
            ScalerHdmiFrlMacRx3SetAudioFCode(GET_AUDIO_GEN_FREQ_F_CODE());

            // Disable sample freq. detection and auto load S code / D code
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8A_PORT_PAGE77_AUDIO_FREQDET, ~(_BIT7 | _BIT1 | _BIT0), 0x00);
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT6 | _BIT5), 0x00);

            // Set Double Buffer bit
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

            // Load NF code
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);

            if(enumAudioLeftRightChannelSelect == _AUDIO_LEFT_CHANNEL)
            {
                // HDMI MAC DVC Mute Off Left channel
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_07_PORT_PAGE77_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), (_BIT1));
            }
            else if(enumAudioLeftRightChannelSelect == _AUDIO_RIGHT_CHANNEL)
            {
                // HDMI MAC DVC Mute Off Right channel
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_07_PORT_PAGE77_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), (_BIT0));
            }
            else
            {
                // HDMI MAC DVC Mute Off
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_07_PORT_PAGE77_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            }

            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_08_PORT_PAGE77_HDMI_MAG_L_FINAL, 0x00);
            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_09_PORT_PAGE77_HDMI_MAG_R_FINAL, 0x00);
        }
        else
#endif
        {
            DebugMessageAudio("RX3 HDMI 2.0 Audio Test On", ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, _BIT4));

            // Disable audio FIFO and Enable audio internal generator
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

            // Audio Normal Output
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            // Set S code by user define
            ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D5_PORT_PAGE72_HDMI_SCAPR, GET_AUDIO_GEN_FREQ_S_CODE());

            // Set NF code by user define
            ScalerTmdsMacRx3SetAudioNCode(GET_AUDIO_GEN_FREQ_N_CODE());
            ScalerTmdsMacRx3SetAudioFCode(GET_AUDIO_GEN_FREQ_F_CODE());

            // Disable sample freq. detection and auto load S code / D code
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET, ~(_BIT7 | _BIT1 | _BIT0), 0x00);
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT6 | _BIT5), 0x00);

            // Set Double Buffer bit
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

            // Load NF code
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);

            if(enumAudioLeftRightChannelSelect == _AUDIO_LEFT_CHANNEL)
            {
                // HDMI MAC DVC Mute Off Left channel
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_07_PORT_PAGE72_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), (_BIT1));
            }
            else if(enumAudioLeftRightChannelSelect == _AUDIO_RIGHT_CHANNEL)
            {
                // HDMI MAC DVC Mute Off Right channel
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_07_PORT_PAGE72_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), (_BIT0));
            }
            else
            {
                // HDMI MAC DVC Mute Off
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_07_PORT_PAGE72_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            }

            ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_08_PORT_PAGE72_HDMI_MAG_L_FINAL, 0x00);
            ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_09_PORT_PAGE72_HDMI_MAG_R_FINAL, 0x00);
        }
    }
    else
    {
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
        if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
        {
            DebugMessageAudio("RX3 HDMI 2.1 Audio Test Off", ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, _BIT4));

            // HDMI MAC DVC Mute On
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_07_PORT_PAGE77_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_08_PORT_PAGE77_HDMI_MAG_L_FINAL, 0x00);
            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_09_PORT_PAGE77_HDMI_MAG_R_FINAL, 0x00);

            // Enable sample freq. detection and auto load S code
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8A_PORT_PAGE77_AUDIO_FREQDET, ~(_BIT7 | _BIT1 | _BIT0), _BIT7);
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT6 | _BIT5), _BIT6);

            // Set Double Buffer bit
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

            // Enable audio FIFO and Disable audio internal generator
            ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2 | _BIT1));
        }
        else
#endif
        {
            DebugMessageAudio("RX3 HDMI 2.0 Audio Test Off", ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, _BIT4));

            // HDMI MAC DVC Mute On
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_07_PORT_PAGE72_HDMI_MAG_M_FINAL, ~(_BIT1 | _BIT0), 0x00);
            ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_08_PORT_PAGE72_HDMI_MAG_L_FINAL, 0x00);
            ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_09_PORT_PAGE72_HDMI_MAG_R_FINAL, 0x00);

            // Enable sample freq. detection and auto load S code
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET, ~(_BIT7 | _BIT1 | _BIT0), _BIT7);
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT6 | _BIT5), _BIT6);

            // Set Double Buffer bit
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

            // Enable audio FIFO and Disable audio internal generator
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2 | _BIT1));
        }
    }
}
#endif
//--------------------------------------------------
// Description  : RX3 Audio FIFO Tracking Proc
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FifoTrackingProc(bit bEnable)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        if(bEnable == _ENABLE)
        {
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
            if(GET_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ_FOR_FRL() == _FALSE)
            {
                // Set HW Auto Load Frequency
                ScalerHdmiAudioRx3AudioFrequencyModeForHdmiFrlMac(_AUDIO_TRACKING_AUTO_LOAD_MODE);

                // Set Flag
                SET_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ_FOR_FRL();

                DebugMessageAudio("HDMI FRL Rx3 Audio Auto_Load Mode", 0);
            }
#endif
            if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_15_PORT_PAGE77_HDMI_PSCR, (_BIT3 | _BIT2)) == 0x00)
            {
                // Enable Audio FIFO Tracking
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_15_PORT_PAGE77_HDMI_PSCR, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Set Double Buffer bit
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

                // Clear Audio Freq Changed Flag
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8A_PORT_PAGE77_AUDIO_FREQDET, ~(_BIT1 | _BIT0), _BIT1);

                // Enable Audio Freq Changed INT
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8A_PORT_PAGE77_AUDIO_FREQDET, ~(_BIT3 | _BIT1 | _BIT0), _BIT3);

                DebugMessageAudio("HDMI FRL RX3 Audio Tracking Enable", 0);

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
                // set AFIFO water level backup
                g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_16_PORT_PAGE77_HDMI_FDDR);
#endif
            }
        }
        else
        {
            if(ScalerGetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_15_PORT_PAGE77_HDMI_PSCR, (_BIT3 | _BIT2)) != 0x00)
            {
                // Diable Audio Freq Changed INT
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_8A_PORT_PAGE77_AUDIO_FREQDET, ~(_BIT3 | _BIT1 | _BIT0), 0x00);

                // Disable Audio FIFO Tracking
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_15_PORT_PAGE77_HDMI_PSCR, ~(_BIT3 | _BIT2), 0x00);

                // Set Double Buffer bit
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
                // Disable P Code Spread
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_E2_PORT_PAGE77_P_SPREAD_0, ~_BIT7, 0x00);
#endif

                // Load NF code
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
                ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);

                DebugMessageAudio("HDMI FRL RX3 Audio Tracking Disable", 0);
            }

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
            if(GET_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ_FOR_FRL() == _TRUE)
            {
                // Set User Define Frequency When No Audio
                ScalerHdmiAudioRx3AudioFrequencyModeForHdmiFrlMac(_AUDIO_TRACKING_MANNUAL_MODE);

                // CLR PLL Autoload Status Flag
                CLR_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ_FOR_FRL();

                DebugMessageAudio("HDMI FRL Rx3 Audio Mannual Mode", 0);
            }
#endif
        }
    }
    else
#endif
    {
        if(bEnable == _ENABLE)
        {
#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
            if(GET_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ() == _FALSE)
            {
                // Set HW Auto Load Frequency
                ScalerHdmiAudioRx3AudioFrequencyModeForHdmiTmdsMac(_AUDIO_TRACKING_AUTO_LOAD_MODE);

                // Set Flag
                SET_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ();

                DebugMessageAudio("HDMI Rx3 Audio Auto_Load Mode", 0);
            }
#endif
            if(ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR, (_BIT3 | _BIT2)) == 0x00)
            {
                // Enable Audio FIFO Tracking
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Set Double Buffer bit
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

                // Clear Audio Freq Changed Flag
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET, ~(_BIT1 | _BIT0), _BIT1);

                // Enable Audio Freq Changed INT
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET, ~(_BIT3 | _BIT1 | _BIT0), _BIT3);

                DebugMessageAudio("HDMI RX3 Audio Tracking Enable", 0);

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
                // set AFIFO water level backup
                g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_16_PORT_PAGE72_HDMI_FDDR);
#endif
            }
        }
        else
        {
            if(ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR, (_BIT3 | _BIT2)) != 0x00)
            {
                // Diable Audio Freq Changed INT
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8A_PORT_PAGE72_AUDIO_FREQDET, ~(_BIT3 | _BIT1 | _BIT0), 0x00);

                // Disable Audio FIFO Tracking
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR, ~(_BIT3 | _BIT2), 0x00);

                // Set Double Buffer bit
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
                // Disable P Code Spread
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_E2_PORT_PAGE72_P_SPREAD_0, ~_BIT7, 0x00);
#endif

                // Load NF code
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);

                DebugMessageAudio("HDMI RX3 Audio Tracking Disable", 0);
            }

#if(_AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT == _OFF)
            if(GET_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ() == _TRUE)
            {
                // Set User Define Frequency When No Audio
                ScalerHdmiAudioRx3AudioFrequencyModeForHdmiTmdsMac(_AUDIO_TRACKING_MANNUAL_MODE);

                // CLR PLL Autoload Status Flag
                CLR_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ();

                DebugMessageAudio("HDMI Rx3 Audio Mannual Mode", 0);
            }
#endif
        }
    }
}

//--------------------------------------------------
// Description  : RX3 Audio Frequency Mode Setting
// Input Value  : _AUDIO_TRACKING_AUTO_LOAD_MODE / _AUDIO_TRACKING_MANNUAL_MODE
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3AudioFrequencyModeForHdmiTmdsMac(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode)
{
    if(enumAudioFreqTrackingMode == _AUDIO_TRACKING_AUTO_LOAD_MODE)
    {
        // Set S code for auto load mode
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_CC_PORT_PAGE72_PRESET_S_CODE0, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

        // Set NF code for auto load mode
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_C0_PORT_PAGE72_PRESET_NF_CODE_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE & 0x1F));
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_C1_PORT_PAGE72_PRESET_NF_CODE_1, HIBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE));
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_C2_PORT_PAGE72_PRESET_NF_CODE_2, LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE));

        // Enable Auto Load S Code
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT6 | _BIT5), _BIT6);

        // Set Double Buffer bit
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);
    }
    else
    {
        // Disable Auto Load S & NF Code
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT6 | _BIT5), 0x00);

        // Set S code User Define
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D5_PORT_PAGE72_HDMI_SCAPR, ScalerAudioGetUserSamplingFreqSCode(_PORT_HDMI, GET_HDMI_RX3_TARGET_SAMPLING_FREQ()));

        // Set NF code User Define
        ScalerTmdsMacRx3SetAudioNCode(LOBYTE(HIWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX3_TARGET_SAMPLING_FREQ()))));
        ScalerTmdsMacRx3SetAudioFCode(LOWORD(ScalerAudioGetUserSamplingFreqNFCode(_PORT_HDMI, GET_HDMI_RX3_TARGET_SAMPLING_FREQ())));

        // Set Double Buffer bit
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Load NF code
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  : RX3 Audio Frequency Set By User Define
// Input Value  : enumAudioFreq
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3SetUserDefineAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq)
{
    SET_HDMI_RX3_SAMPLING_FREQ_USER_DEFINE(enumAudioFreq);
}

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : RX3 Audio Frequency Limitation Set By User Define
// Input Value  : enumAudioFreq
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3SetUserDefineSamplingFreqLimit(EnumAudioSamplingFreqType enumAudioFreq)
{
    SET_HDMI_RX3_SAMPLING_FREQ_LIMIT(enumAudioFreq);
}
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Set User Define Audio Frequency S/N.F Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3SyncUserDefineFrequencyPllSetting(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ_FOR_FRL() == _FALSE)
    {
        ScalerHdmiAudioRx3AudioFrequencyModeForHdmiFrlMac(_AUDIO_TRACKING_MANNUAL_MODE);
    }
#endif

    if(GET_HDMI_AUDIO_RX3_AUTO_LOAD_FREQ() == _FALSE)
    {
        ScalerHdmiAudioRx3AudioFrequencyModeForHdmiTmdsMac(_AUDIO_TRACKING_MANNUAL_MODE);
    }
}

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Audio Frequency N.F Code Check
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerHdmiAudioRx3CheckNfCodeStable(void)
{
    switch(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ())
    {
        case _AUDIO_FREQ_32K:
        case _AUDIO_FREQ_64K:
        case _AUDIO_FREQ_128K:
        case _AUDIO_FREQ_256K:
        case _AUDIO_FREQ_512K:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
                if((ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_EA_PORT_PAGE77_NF_FINAL2) > (LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)) ||
                   (ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_EA_PORT_PAGE77_NF_FINAL2) < (LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)))
                {
                    return _FALSE;
                }
            }
            else
#endif
            {
                if((ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_EA_PORT_PAGE72_NF_FINAL2) > (LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)) ||
                   (ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_EA_PORT_PAGE72_NF_FINAL2) < (LOBYTE(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)))
                {
                    return _FALSE;
                }
            }
            break;

        case _AUDIO_FREQ_44_1K:
        case _AUDIO_FREQ_88_2K:
        case _AUDIO_FREQ_176_4K:
        case _AUDIO_FREQ_352_8K:
        case _AUDIO_FREQ_705_6K:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
                if((ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_EA_PORT_PAGE77_NF_FINAL2) > (LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)) ||
                   (ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_EA_PORT_PAGE77_NF_FINAL2) < (LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)))
                {
                    return _FALSE;
                }
            }
            else
#endif
            {
                if((ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_EA_PORT_PAGE72_NF_FINAL2) > (LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)) ||
                   (ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_EA_PORT_PAGE72_NF_FINAL2) < (LOBYTE(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)))
                {
                    return _FALSE;
                }
            }
            break;

        case _AUDIO_FREQ_48K:
        case _AUDIO_FREQ_96K:
        case _AUDIO_FREQ_192K:
        case _AUDIO_FREQ_384K:
        case _AUDIO_FREQ_768K:

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
            if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
            {
                if((ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_EA_PORT_PAGE77_NF_FINAL2) > (LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)) ||
                   (ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_EA_PORT_PAGE77_NF_FINAL2) < (LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)))
                {
                    return _FALSE;
                }
            }
            else
#endif
            {
                if((ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_EA_PORT_PAGE72_NF_FINAL2) > (LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)) ||
                   (ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_EA_PORT_PAGE72_NF_FINAL2) < (LOBYTE(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE) + _AUDIO_HDMI_STABLE_FCODE_RANGE)))
                {
                    return _FALSE;
                }
            }
            break;

        default:
            break;
    }
    return _TRUE;
}
#endif

#if(_HDMI_AUDIO_FW_TRACKING_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDMI Rx3 FW tracking Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwTrackingHandler(void)
{
    switch(GET_HDMI_AUDIO_RX3_FW_TRACKING_STATE())
    {
        case _AUDIO_FW_TRACKING_INITIAL:

            if(GET_HDMI_AUDIO_RX3_DIGITAL_SOURCE() != _DIGITAL_AUDIO_SOURCE_NONE)
            {
                SET_HDMI_AUDIO_RX3_FW_TRACKING_STATE(_AUDIO_FW_TRACKING_PROCESS_PREPARING);

                // Initialize Audio Tracking By FW Control
                ScalerHdmiAudioRx3FwTrackingInitial();

                SET_HDMI_AUDIO_RX3_FW_TRACKING_EVENT();

                CLR_HDMI_AUDIO_RX3_FW_TRACKING_RESET();

                DebugMessageAudio("RX3 Audio: FW Tracking Start", 0);
            }

            break;

        case _AUDIO_FW_TRACKING_PROCESS_PREPARING:

            if(GET_HDMI_AUDIO_RX3_FW_TRACKING_EVENT() == _TRUE)
            {
                CLR_HDMI_AUDIO_RX3_FW_TRACKING_EVENT();

                // Find stable SUMC or already 4s --> boundary tracking
                if((g_stHdmiAudioRx3FwTrackingInfo.b1AudioFwTrackStable != 0x00) || (GET_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT() == _TRUE))
                {
                    if(g_stHdmiAudioRx3FwTrackingInfo.b1AudioFwTrackStable != 0x00)
                    {
                        g_stHdmiAudioRx3FwTrackingInfo.b1AudioFwTrackStable = 0x00;

                        DebugMessageAudio("RX3 Audio: SUMC Stable", g_stHdmiAudioRx3FwTrackingInfo.b1AudioFwTrackStable);
                    }
                    else
                    {
                        DebugMessageAudio("RX3 Audio: SUMC Final", 0);
                    }

                    SET_HDMI_AUDIO_RX3_FW_TRACKING_STATE(_AUDIO_FW_TRACKING_PROCESS_PLAYBACK);

                    CLR_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT();
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT);
                }
                else
                {
                    // FW tracking - preparing tracking
                    ScalerHdmiAudioRx3FwPreparingTracking();
                }

                ScalerTimerActiveTimerEvent(ScalerHdmiAudioRx3FwTrackingTimerEventPeriod(), _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_FW_TRACKING_PREPARING);
            }

            break;

        case _AUDIO_FW_TRACKING_PROCESS_PLAYBACK:

            if(GET_HDMI_AUDIO_RX3_FW_TRACKING_EVENT() == _TRUE)
            {
                CLR_HDMI_AUDIO_RX3_FW_TRACKING_EVENT();

                // FW tracking - boundary tracking
                ScalerHdmiAudioRx3FwBoundaryTracking();

                ScalerTimerActiveTimerEvent(ScalerHdmiAudioRx3FwTrackingTimerEventPeriod(), _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_FW_TRACKING_PREPARING);
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : HDMI Rx3 FW tracking Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwTrackingInitial(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        ScalerHdmiAudioRx3FwTrackingInitialForHdmiFrlMac();
    }
    else
#endif
    {
        ScalerHdmiAudioRx3FwTrackingInitialForHdmiTmdsMac();
    }
}

//--------------------------------------------------
// Description  : HDMI Rx3 FW tracking Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwTrackingReset(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        ScalerHdmiAudioRx3FwTrackingResetForHdmiFrlMac();
    }
    else
#endif
    {
        ScalerHdmiAudioRx3FwTrackingResetForHdmiTmdsMac();
    }
}

//--------------------------------------------------
// Description  : HDMI Rx3 FW tracking Process - Preparing Tracking
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwPreparingTracking(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        ScalerHdmiAudioRx3FwPreparingTrackingForHdmiFrlMac();
    }
    else
#endif
    {
        ScalerHdmiAudioRx3FwPreparingTrackingForHdmiTmdsMac();
    }
}

//--------------------------------------------------
// Description  : HDMI Rx3 FW tracking Process - Boundary Tracking
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwBoundaryTracking(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        ScalerHdmiAudioRx3FwBoundaryTrackingForHdmiFrlMac();
    }
    else
#endif
    {
        ScalerHdmiAudioRx3FwBoundaryTrackingForHdmiTmdsMac();
    }
}

//--------------------------------------------------
// Description  : Audio FW tracking timer event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwTrackingEventSet(void)
{
    SET_HDMI_AUDIO_RX3_FW_TRACKING_EVENT();
}

//--------------------------------------------------
// Description  : Audio FW tracking 4s timeout event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3TimeoutEventSet(void)
{
    SET_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT();
}

//--------------------------------------------------
// Description  : Audio FW tracking timer event period
// Input Value  : None
// Output Value : Timer event period
//--------------------------------------------------
BYTE ScalerHdmiAudioRx3FwTrackingTimerEventPeriod(void)
{
    if(GET_HDMI_AUDIO_RX3_FW_TRACKING_STATE() == _AUDIO_FW_TRACKING_PROCESS_PREPARING)
    {
        return (_AUDIO_FW_TRCK_PREPARING_CHECK);
    }
    else
    {
        return (_AUDIO_FW_TRCK_PLAYBACK_CHECK);
    }
}

//--------------------------------------------------
// Description  : HDMI Rx3 FW tracking Initial For Hdmi2.0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwTrackingInitialForHdmiTmdsMac(void)
{
    g_stHdmiAudioRx3FwTrackingInfo.b1AudioFwTrackStable = 0x00;
    g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = 0x00;
    g_stHdmiAudioRx3FwTrackingInfo.ucAudioFreqRecord = ScalerGetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8B_PORT_PAGE72_AUDIO_FREQ_RESULT, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Read afifo Water level New Mode
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_14_PORT_PAGE72_HDMI_DCAPR1, ~(_BIT7 | _BIT6), _BIT7);

    // Set I code of boundary tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D6_PORT_PAGE72_AUD_BDRY_0, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D7_PORT_PAGE72_AUD_BDRY_1, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D8_PORT_PAGE72_AUD_BDRY_2, 0x00);

    // Set P code of boundary tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D9_PORT_PAGE72_AUD_BDRY_3, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DA_PORT_PAGE72_AUD_BDRY_4, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DB_PORT_PAGE72_AUD_BDRY_5, 0x00);

    // Set I code of trend tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DC_PORT_PAGE72_AUD_BDRY_6, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DD_PORT_PAGE72_AUD_BDRY_7, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DE_PORT_PAGE72_AUD_BDRY_8, 0x00);

    // Set P code of trend tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DF_PORT_PAGE72_AUD_BDRY_9, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E0_PORT_PAGE72_AUD_BDRY_A, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E1_PORT_PAGE72_AUD_BDRY_B, 0x00);

    // Disable Auto Load S/N.F Code
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT6 | _BIT5), 0x00);
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // Initialize N/F Code for FW Audio Tracking
    ScalerHdmiAudioRx3FwLoadNfPll();

    CLR_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT();

    // When the stable N.F Code is not found within 4 seconds, tracking state force to playback for play audio
    ScalerTimerReactiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT);

    // Disable Reset Audio Clock When Set Double Buffer
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8B_PORT_PAGE72_AUDIO_FREQ_RESULT, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : HDMI Rx3 FW Preparing Tracking For Hdmi2.0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwTrackingResetForHdmiTmdsMac(void)
{
    g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = 0;

    // Enable Reset Audio Clock When Set Double Buffer
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_8B_PORT_PAGE72_AUDIO_FREQ_RESULT, ~_BIT7, 0x00);

    CLR_HDMI_AUDIO_RX3_FW_TRACKING_RESET();

    SET_HDMI_AUDIO_RX3_FW_TRACKING_STATE(_AUDIO_FW_TRACKING_INITIAL);

    // Set I code of boundary tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D6_PORT_PAGE72_AUD_BDRY_0, LOBYTE(HIWORD(_HDMI_INITIAL_I_CODE)));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D7_PORT_PAGE72_AUD_BDRY_1, HIBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D8_PORT_PAGE72_AUD_BDRY_2, LOBYTE(LOWORD(_HDMI_INITIAL_I_CODE)));

    // Set P code of boundary tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D9_PORT_PAGE72_AUD_BDRY_3, 0x12);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DA_PORT_PAGE72_AUD_BDRY_4, 0xFB);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DB_PORT_PAGE72_AUD_BDRY_5, 0xB9);

    // Set I code of trend tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DC_PORT_PAGE72_AUD_BDRY_6, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DD_PORT_PAGE72_AUD_BDRY_7, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DE_PORT_PAGE72_AUD_BDRY_8, 0x38);

    // Set P code of trend tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DF_PORT_PAGE72_AUD_BDRY_9, 0x12);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E0_PORT_PAGE72_AUD_BDRY_A, 0xFB);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E1_PORT_PAGE72_AUD_BDRY_B, 0xB9);

    // Auto Load S Code
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // Read afifo Water level Old Mode
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_14_PORT_PAGE72_HDMI_DCAPR1, ~(_BIT7 | _BIT6), 0x00);

    CLR_HDMI_AUDIO_RX3_FW_TRACKING_EVENT();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_FW_TRACKING_PREPARING);

    CLR_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_HDMI_AUDIO_RX3_FW_TRACKING_TIMEOUT);

    CLR_HDMI_AUDIO_RX3_WL_TARGET_DIRECTION();
}

//--------------------------------------------------
// Description  : HDMI Rx3 FW Preparing Tracking For Hdmi2.0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwPreparingTrackingForHdmiTmdsMac(void)
{
    // check WL, adjust N.Fcode
    WORD usbackupSumc = 0x00;
    BYTE ucAfifoCurrent = 0x00;

    // Pop up afifo Water level
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_14_PORT_PAGE72_HDMI_DCAPR1, ~_BIT6, _BIT6);

    // get current aFIFO water level
    ucAfifoCurrent = ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_16_PORT_PAGE72_HDMI_FDDR);

    // get current N.Fcode
    ScalerGetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E9_PORT_PAGE72_NF_FINAL1, 2, &pData[0], _AUTOINC);
    usbackupSumc = (((WORD)pData[0] << 8) | pData[1]);

    // AFIFO water level going up -> Increase N.Fcode
    if((ucAfifoCurrent > (g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup + 0x04)) ||
       (ucAfifoCurrent >= 0x30))
    {
        if(ucAfifoCurrent < 0x30)
        {
            if((GET_HDMI_AUDIO_RX3_WL_TARGET_DIRECTION() == _AUDIO_WL_GOES_UP) &&
               (ucAfifoCurrent >= (g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup + 0x04)))
            {
                DebugMessageAudio("RX3 Audio: AFIFO has gone up", ucAfifoCurrent);

                // set stable count = STABLE_CNT(0X20)/2
                g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2);
            }
            else
            {
                if(g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt < (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2))
                {
                    usbackupSumc += ((_AUDIO_FW_TRCK_FIRST_STABLE_CNT - g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt) * (ucAfifoCurrent - (g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup + 0x01)));
                }
                else
                {
                    usbackupSumc += 0x02;
                }

                // Set F code
                ScalerTmdsMacRx3SetAudioFCode(usbackupSumc);

                // Set Double Buffer bit
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

                // Load N.Fcode
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);

                // set stable count = 0
                g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = 0x00;

                DebugMessageAudio("RX3 Audio: AFIFO current", ucAfifoCurrent);
                DebugMessageAudio("RX3 Audio: SUMC+", usbackupSumc);
            }
        }
        else
        {
            usbackupSumc += 0x10;

            // Set F code
            ScalerTmdsMacRx3SetAudioFCode(usbackupSumc);

            // Set Double Buffer bit
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

            // Load N.Fcode
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);

            // set stable count = 0
            g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = 0x00;

            DebugMessageAudio("RX3 Audio: AFIFO Full", ucAfifoCurrent);
            DebugMessageAudio("RX3 Audio: SUMC+ Full", usbackupSumc);
        }

        SET_HDMI_AUDIO_RX3_WL_TARGET_DIRECTION(_AUDIO_WL_GOES_DOWN);

        // Reset AFIFO water level backup
        g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;
    }
    else if((ucAfifoCurrent < (g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup - 0x04)) ||
            (ucAfifoCurrent <= 0x10))  // aFIFO water level going down -> Decrease N.Fcode
    {
        if(ucAfifoCurrent > 0x10)
        {
            if((GET_HDMI_AUDIO_RX3_WL_TARGET_DIRECTION() == _AUDIO_WL_GOES_DOWN) &&
               (ucAfifoCurrent <= (g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup - 0x04)))
            {
                DebugMessageAudio("RX3 Audio: AFIFO has gone down", ucAfifoCurrent);

                // set stable count = STABLE_CNT(0X20)/2
                g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2);
            }
            else
            {
                if(g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt < (_AUDIO_FW_TRCK_FIRST_STABLE_CNT / 2))
                {
                    usbackupSumc -= ((_AUDIO_FW_TRCK_FIRST_STABLE_CNT - g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt) * ((g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup - 0x01) - ucAfifoCurrent));
                }
                else
                {
                    usbackupSumc -= 0x02;
                }

                // Set F code
                ScalerTmdsMacRx3SetAudioFCode(usbackupSumc);

                // Set Double Buffer bit
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

                // Load N.Fcode
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);

                // set stable count = 0
                g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = 0x00;

                DebugMessageAudio("RX3 Audio: AFIFO current", ucAfifoCurrent);
                DebugMessageAudio("RX3 Audio: SUMC-", usbackupSumc);
            }
        }
        else
        {
            usbackupSumc -= 0x10;

            // Set F code
            ScalerTmdsMacRx3SetAudioFCode(usbackupSumc);

            // Set Double Buffer bit
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

            // Load N.Fcode
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);

            // set stable count = 0
            g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt = 0;

            DebugMessageAudio("RX3 Audio: AFIFO Empty", ucAfifoCurrent);
            DebugMessageAudio("RX3 Audio: SUMC- Empty", usbackupSumc);
        }

        SET_HDMI_AUDIO_RX3_WL_TARGET_DIRECTION(_AUDIO_WL_GOES_UP);

        // Reset AFIFO water level backup
        g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;
    }
    else    // AfifoBackup-2 < AfifoCurrent < AfifoBackup+2
    {
        if(g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt < _AUDIO_FW_TRCK_FIRST_STABLE_CNT)
        {
            g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt++;
        }
    }

    // check stable
    if(g_stHdmiAudioRx3FwTrackingInfo.ucAfifoTrackStableCnt >= _AUDIO_FW_TRCK_FIRST_STABLE_CNT)
    {
        // set stable SUMC
        g_stHdmiAudioRx3FwTrackingInfo.b1AudioFwTrackStable = 0x01;

        DebugMessageAudio("Rx3 Audio: Find Stable SUMC", g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup);
    }
}

//--------------------------------------------------
// Description  : HDMI Rx3 FW Boundary Tracking For Hdmi2.0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwBoundaryTrackingForHdmiTmdsMac(void)
{
    // check WL, adjust N.Fcode
    WORD usbackupSumc = 0x00;
    BYTE ucAfifoCurrent = 0x00;

    // Pop up afifo Water level
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_14_PORT_PAGE72_HDMI_DCAPR1, ~_BIT6, _BIT6);

    // get current aFIFO water level
    ucAfifoCurrent = ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_16_PORT_PAGE72_HDMI_FDDR);

    // get current N.Fcode
    ScalerGetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E9_PORT_PAGE72_NF_FINAL1, 2, &pData[0], _AUTOINC);
    usbackupSumc = (((WORD)pData[0] << 8) | pData[1]);

    // AFIFO water level going up -> Increase N.Fcode
    if(((ucAfifoCurrent > 0x24) && (ucAfifoCurrent > g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup)) ||
       (ucAfifoCurrent > 0x30))
    {
        DebugMessageAudio("RX3 Audio: Boundary up", g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup);
        DebugMessageAudio("RX3 Audio: SUMC+", usbackupSumc);

        if(ucAfifoCurrent > 0x30)
        {
            usbackupSumc += 0x10;
        }
        else
        {
            usbackupSumc += ((ucAfifoCurrent - 0x24 + 0x01) * 0x02);
        }

        // Reset AFIFO water level backup
        g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;

        // Set F code
        ScalerTmdsMacRx3SetAudioFCode(usbackupSumc);

        // Set Double Buffer bit
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Load NF code
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);
    }

    // AFIFO water level going up -> Decrease N.Fcode
    if(((ucAfifoCurrent < 0x1C) && (ucAfifoCurrent < g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup)) ||
       (ucAfifoCurrent < 0x10))
    {
        DebugMessageAudio("RX3 Audio: Boundary down", g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup);
        DebugMessageAudio("RX3 Audio: SUMC-", usbackupSumc);

        if(ucAfifoCurrent < 0x10)
        {
            usbackupSumc -= 0x10;
        }
        else
        {
            usbackupSumc -= ((0x1C - ucAfifoCurrent + 0x01) * 0x02);
        }

        // Reset AFIFO water level backup
        g_stHdmiAudioRx3FwTrackingInfo.ucAfifoBackup = ucAfifoCurrent;

        // Set F code
        ScalerTmdsMacRx3SetAudioFCode(usbackupSumc);

        // Set Double Buffer bit
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Load NF code
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  : Initial N.F code setting by fs
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3FwLoadNfPll(void)
{
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        if(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() == _AUDIO_FREQ_32K)
        {
            // Set S code for 32kHz
            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D5_PORT_PAGE77_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);
            // Set NF code for 32kHz
            ScalerHdmiFrlMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE);
            ScalerHdmiFrlMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);
        }
        else if(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() == _AUDIO_FREQ_44_1K)
        {
            // Set S code for 44kHz
            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D5_PORT_PAGE77_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);
            // Set NF code for 44kHz
            ScalerHdmiFrlMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE);
            ScalerHdmiFrlMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE);
        }
        else if(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() == _AUDIO_FREQ_48K)
        {
            // Set S code for 48kHz
            ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_D5_PORT_PAGE77_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);
            // Set NF code for 48kHz
            ScalerHdmiFrlMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE);
            ScalerHdmiFrlMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE);
        }

        // Set Double Buffer bit
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Load NF code
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, _BIT5);
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~_BIT5, 0x00);
    }
    else
#endif
    {
        if(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() == _AUDIO_FREQ_32K)
        {
            // Set S code for 32kHz
            ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D5_PORT_PAGE72_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_32K_GROUP_S_CODE);

            // Set NF code for 32kHz
            ScalerTmdsMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_32K_GROUP_N_CODE);
            ScalerTmdsMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_32K_GROUP_F_CODE);
        }
        else if(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() == _AUDIO_FREQ_44_1K)
        {
            // Set S code for 44kHz
            ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D5_PORT_PAGE72_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_44K_GROUP_S_CODE);

            // Set NF code for 44kHz
            ScalerTmdsMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_44K_GROUP_N_CODE);
            ScalerTmdsMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_44K_GROUP_F_CODE);
        }
        else if(GET_HDMI_AUDIO_RX3_SAMPLING_FREQ() == _AUDIO_FREQ_48K)
        {
            // Set S code for 48kHz
            ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_D5_PORT_PAGE72_HDMI_SCAPR, _HDMI_SAMPLING_FREQ_48K_GROUP_S_CODE);

            // Set NF code for 48kHz
            ScalerTmdsMacRx3SetAudioNCode(_HDMI_SAMPLING_FREQ_48K_GROUP_N_CODE);
            ScalerTmdsMacRx3SetAudioFCode(_HDMI_SAMPLING_FREQ_48K_GROUP_F_CODE);
        }

        // Set Double Buffer bit
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

        // Load NF code
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, _BIT5);
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~_BIT5, 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Get Rx3 Audio Channel Status
// Input Value  : None
// Output Value : Channel Status
//--------------------------------------------------
StructAudioChannelInfo ScalerHdmiAudioRx3GetChannelStatus(void)
{
    StructAudioChannelInfo stAudioStatus = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    BYTE ucTemp = 0;

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6)
    {
        // Load Ch1 Channel_Status
        ucTemp = ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_51_PORT_PAGE77_HDMI_ACRCR);
        ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_51_PORT_PAGE77_HDMI_ACRCR, ((ucTemp & 0xFC) | 0x01));

        // Get Channel_Status[7:0]
        stAudioStatus.ucChannelStaus0 = ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_57_PORT_PAGE77_HDMI_ACS0);

        // Get Channel_Status[15:8]
        stAudioStatus.ucChannelStaus1 = ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_58_PORT_PAGE77_HDMI_ACS1);

        // Get Channel_Status[23:16]
        // Channel_Status[23:20] Set Dummy and Reference by AudioChannelNumStaus1 ~ 8
        stAudioStatus.ucChannelStaus2 = ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_59_PORT_PAGE77_HDMI_ACS2);

        // Get Channel_Status[31:24]
        stAudioStatus.ucChannelStaus3 = ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_5A_PORT_PAGE77_HDMI_ACS3);

        // Get Channel_Status[39:32]
        stAudioStatus.ucChannelStaus4 = ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_5B_PORT_PAGE77_HDMI_ACS4);
    }
    else
#endif // End of #if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    {
        // Load Ch1 Channel_Status
        ucTemp = ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_51_PORT_PAGE72_HDMI_ACRCR);
        ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_51_PORT_PAGE72_HDMI_ACRCR, ((ucTemp & 0xFC) | 0x01));

        // Get Channel_Status[7:0]
        stAudioStatus.ucChannelStaus0 = ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_57_PORT_PAGE72_HDMI_ACS0);

        // Get Channel_Status[15:8]
        stAudioStatus.ucChannelStaus1 = ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_58_PORT_PAGE72_HDMI_ACS1);

        // Get Channel_Status[23:16]
        // Channel_Status[23:20] Set Dummy and Reference by AudioChannelNumStaus1 ~ 8
        stAudioStatus.ucChannelStaus2 = ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_59_PORT_PAGE72_HDMI_ACS2);

        // Get Channel_Status[31:24]
        stAudioStatus.ucChannelStaus3 = ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_5A_PORT_PAGE72_HDMI_ACS3);

        // Get Channel_Status[39:32]
        stAudioStatus.ucChannelStaus4 = ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_5B_PORT_PAGE72_HDMI_ACS4);
    }

    // Check Channel Number
    switch(GET_HDMI_AUDIO_RX3_CHANNEL_COUNT())
    {
        case _AUDIO_CHANNEL_COUNT_MONO:

            stAudioStatus.ucChannelNumber12 = 0x10;
            stAudioStatus.ucChannelNumber34 = 0x00;
            stAudioStatus.ucChannelNumber56 = 0x00;
            stAudioStatus.ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_2:

            stAudioStatus.ucChannelNumber12 = 0x12;
            stAudioStatus.ucChannelNumber34 = 0x00;
            stAudioStatus.ucChannelNumber56 = 0x00;
            stAudioStatus.ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_3:

            stAudioStatus.ucChannelNumber12 = 0x12;
            stAudioStatus.ucChannelNumber34 = 0x30;
            stAudioStatus.ucChannelNumber56 = 0x00;
            stAudioStatus.ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_4:

            stAudioStatus.ucChannelNumber12 = 0x12;
            stAudioStatus.ucChannelNumber34 = 0x34;
            stAudioStatus.ucChannelNumber56 = 0x00;
            stAudioStatus.ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_5:

            stAudioStatus.ucChannelNumber12 = 0x12;
            stAudioStatus.ucChannelNumber34 = 0x34;
            stAudioStatus.ucChannelNumber56 = 0x50;
            stAudioStatus.ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_6:

            stAudioStatus.ucChannelNumber12 = 0x12;
            stAudioStatus.ucChannelNumber34 = 0x34;
            stAudioStatus.ucChannelNumber56 = 0x56;
            stAudioStatus.ucChannelNumber78 = 0x00;

            break;

        case _AUDIO_CHANNEL_COUNT_7:

            stAudioStatus.ucChannelNumber12 = 0x12;
            stAudioStatus.ucChannelNumber34 = 0x34;
            stAudioStatus.ucChannelNumber56 = 0x56;
            stAudioStatus.ucChannelNumber78 = 0x70;

            break;

        case _AUDIO_CHANNEL_COUNT_8:

            stAudioStatus.ucChannelNumber12 = 0x12;
            stAudioStatus.ucChannelNumber34 = 0x34;
            stAudioStatus.ucChannelNumber56 = 0x56;
            stAudioStatus.ucChannelNumber78 = 0x78;

            break;

        default:

            // Set 2-Ch Audio
            stAudioStatus.ucChannelNumber12 = 0x12;
            stAudioStatus.ucChannelNumber34 = 0x00;
            stAudioStatus.ucChannelNumber56 = 0x00;
            stAudioStatus.ucChannelNumber78 = 0x00;

            break;
    }

    return stAudioStatus;
}

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Rx3 Audio Info
// Input Value  : None
// Output Value : Audio Info
//--------------------------------------------------
BYTE ScalerHdmiAudioRx3GetAudioInfo(EnumAudioInfoContent enumAudioInfoContent)
{
    switch(enumAudioInfoContent)
    {
        case _ADUIO_INFO_PB4:
            return ((ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6) ? (ScalerGetDataPortSingleByte(P77_CD_HDMI_PSAP, 0x18)) : (ScalerGetDataPortSingleByte(P72_CD_HDMI_PSAP, 0x18)));

        case _ADUIO_INFO_PB5:
            return ((ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6) ? (ScalerGetDataPortSingleByte(P77_CD_HDMI_PSAP, 0x19)) : (ScalerGetDataPortSingleByte(P72_CD_HDMI_PSAP, 0x19)));

        case _ADUIO_INFO_PB6:
            return ((ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6) ? (ScalerGetDataPortSingleByte(P77_CD_HDMI_PSAP, 0x1A)) : (ScalerGetDataPortSingleByte(P72_CD_HDMI_PSAP, 0x1A)));

        case _ADUIO_INFO_PB7:
            return ((ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6) ? (ScalerGetDataPortSingleByte(P77_CD_HDMI_PSAP, 0x1B)) : (ScalerGetDataPortSingleByte(P72_CD_HDMI_PSAP, 0x1B)));

        case _ADUIO_INFO_PB8:
            return ((ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6) ? (ScalerGetDataPortSingleByte(P77_CD_HDMI_PSAP, 0x1C)) : (ScalerGetDataPortSingleByte(P72_CD_HDMI_PSAP, 0x1C)));

        case _ADUIO_INFO_PB9:
            return ((ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6) ? (ScalerGetDataPortSingleByte(P77_CD_HDMI_PSAP, 0x1D)) : (ScalerGetDataPortSingleByte(P72_CD_HDMI_PSAP, 0x1D)));

        case _ADUIO_INFO_PB10:
            return ((ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == _BIT6) ? (ScalerGetDataPortSingleByte(P77_CD_HDMI_PSAP, 0x1E)) : (ScalerGetDataPortSingleByte(P72_CD_HDMI_PSAP, 0x1E)));

        default:
            break;
    }

    return 0x00;
}
#endif

#if((_AUDIO_PARALLEL_MODE_SUPPORT == _ON) && (_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE))
#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Rx3 Audio HBR Setting
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerHdmiAudioRx3HbrAudioSettingForFrl(void)
{
    BYTE ucRecheckTime = 0;
    ScalerHdmiAudioRx3ClkStableCheckTime();

    // Set X Value = 0x00
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_32_PORT_PAGE77_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set Y Value = 0x00
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_33_PORT_PAGE77_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set I code of trend tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DC_PORT_PAGE77_AUD_BDRY_6, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DD_PORT_PAGE77_AUD_BDRY_7, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DE_PORT_PAGE77_AUD_BDRY_8, 0x00);

    // Set P code of trend tracking
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_DF_PORT_PAGE77_AUD_BDRY_9, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E0_PORT_PAGE77_AUD_BDRY_A, 0x00);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E1_PORT_PAGE77_AUD_BDRY_B, 0x00);

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
    // Set spread p code
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E4_PORT_PAGE77_P_SPREAD_2, 0x04);
    ScalerSetDataPortByte(P77_C9_HDMI_AP, _P77_CA_PT_E5_PORT_PAGE77_P_SPREAD_3, 0x00);

    // Enable P Code Spread
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_E2_PORT_PAGE77_P_SPREAD_0, ~_BIT7, _BIT7);
#endif

    ScalerHdmiAudioRx3HbrAudioResetForFrl();

    ScalerHdmiAudioRx3HbrAudioOutputForFrl();

    ScalerMcuDelayXus(999);

    while((ucRecheckTime < 10) && ((ScalerGetBit(P77_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00) || (ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_18_PORT_PAGE77_HDMI_MFDDR) >= 0x3C) || (GET_HDMI_RX3_HBR_AUDIO_FIFO_ERROR() == _TRUE)))
    {
        ScalerHdmiAudioRx3HbrAudioResetForFrl();

        ScalerHdmiAudioRx3HbrAudioOutputForFrl();

        ScalerMcuDelayXus(999);

        ucRecheckTime ++;
    }

    if(ucRecheckTime >= 10)
    {
        DebugMessageAudio("hbr audio fifo reset", ucRecheckTime);
        SET_HDMI_RX3_HBR_AUDIO_IS_SETTING();
        return _FALSE;
    }
    else
    {
        DebugMessageAudio("hbr audio output", ucRecheckTime);
        CLR_HDMI_RX3_HBR_AUDIO_IS_SETTING();

        // audio wd enable
        ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Get Rx3 Audio HBR Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3HbrAudioResetForFrl(void)
{
    DebugMessageAudio("hbr audio reset", 0x00);

    // audio wd disable
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);

    // audio i/p code not work
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_31_PORT_PAGE77_HDMI_WDCR0, ~_BIT5, 0x00);

    // tracking disable
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_15_PORT_PAGE77_HDMI_PSCR, ~(_BIT3 | _BIT2), 0x00);
    // double buffer
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_D0_PORT_PAGE77_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // fifo W/R disable
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~_BIT2, 0x00);
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~(_BIT1 | _BIT0), 0x00);

    // Mac I2S output disable
    ScalerSetByte(P77_C9_HDMI_AP, _P77_CA_PT_62_PORT_PAGE77_HDMI_AOCR);
    ScalerSetByte(P77_CA_HDMI_DP, 0x00);

    // parallel mode reset
    SET_IIS_PARALLEL_MODE_RESET();
}

#ifdef __GNUC__
#pragma GCC push_options
#pragma GCC optimize("Os")
#endif
//--------------------------------------------------
// Description  : HBR Audio Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3HbrAudioOutputForFrl(void)
{
    bit bAfifoUnderFlow = _FALSE;
    WORD usAfifoCheckTime = 400;

    CLR_HDMI_RX3_HBR_AUDIO_FIFO_ERROR();

    // audio manual mode
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~_BIT6, 0x00);

    // manual gain enable
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~_BIT3, 0x00);

    // afifo R en
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~_BIT2, 0x00);
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~(_BIT1 | _BIT0), _BIT1);

    // w1c over/under flow flag
    ScalerSetBit(P77_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    DebugMessageAudio("HBR Audio FIFO reset", 0x00);

    // reset afifo to empty
    while((usAfifoCheckTime != 0) && (bAfifoUnderFlow == _FALSE))
    {
        if(ScalerGetBit(P77_CB_HDMI_SR, _BIT1) == _BIT1)
        {
            DebugMessageAudio("HBR Audio FIFO underflow", usAfifoCheckTime);

            bAfifoUnderFlow = _TRUE;
        }
        ScalerMcuDelayXus(20);
        usAfifoCheckTime--;
    }

    // fifo W/R disable
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~_BIT2, 0x00);
    ScalerSetDataPortBit(P77_C9_HDMI_AP, _P77_CA_PT_03_PORT_PAGE77_HDMI_AFCR, ~(_BIT1 | _BIT0), 0x00);

    ScalerMcuDelayXus(5000);

    BYTE ucIntStatus = GET_INTERRUPT_GLOBAL_ENABLE_STATUS();

#if(_SCPU_SUPPORT == _ON)
    WORD usHbrResetCheckTime = 6400;

    SET_AUDIO_SCPU_AUDIO_STATE(_PARALLELMODE_HBR_FIRST_STATE_FOR_RX3_FRL);
    // wait max 32ms(5us*6400) for SCPU entering ScalerSyncDelayForHbrAudioSetting
    while(usHbrResetCheckTime != 0)
    {
        if(GET_AUDIO_SCPU_AUDIO_STATE() == _PARALLELMODE_HBR_SECOND_STATE)
        {
            break;
        }
        ScalerMcuDelayXus(5);
        usHbrResetCheckTime--;
    }
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

    SET_AUDIO_SCPU_AUDIO_STATE(_PARALLELMODE_HBR_THIRD_STATE);

    usHbrResetCheckTime = 10;
    // wait max 700us(70us*10) for SCPU executing ScalerSyncSetHdmiAudioRx3HbrAudioOutputForTmds
    while(usHbrResetCheckTime != 0)
    {
        ScalerMcuDelayXus(70);
        if(GET_AUDIO_SCPU_AUDIO_STATE() == _PARALLELMODE_HBR_FOURTH_STATE)
        {
            break;
        }
        usHbrResetCheckTime--;
    }
    SET_AUDIO_SCPU_AUDIO_STATE(_PARALLELMODE_HBR_IDLE_STATE);
#else
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

    ScalerCpuSyncSetHdmiAudioRx3HbrAudioOutputForFrl();
#endif

    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(ucIntStatus);
}
#ifdef __GNUC__
#pragma GCC pop_options
#endif
#endif

//--------------------------------------------------
// Description  : Get Rx3 Audio Info
// Input Value  : None
// Output Value : Audio Info
//--------------------------------------------------
void ScalerHdmiAudioRx3ClkStableCheckTime(void)
{
    BYTE ucFcode = 0x00;

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
    if(GET_HDMI_AUDIO_RX3_VERSION() == _AUDIO_INPUT_FROM_FRL)
    {
        ucFcode = ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_EA_PORT_PAGE77_NF_FINAL2);

        ScalerTimerDelayXms(100);

        for(BYTE ucTimeout = 0; ucTimeout < 15; ucTimeout++)
        {
            if(abs(ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_EA_PORT_PAGE77_NF_FINAL2) - ucFcode) >= 2)
            {
                ScalerTimerDelayXms(100);

                ucFcode = ScalerGetDataPortSingleByte(P77_C9_HDMI_AP, _P77_CA_PT_EA_PORT_PAGE77_NF_FINAL2);
            }
            else
            {
                break;
            }
        }
    }
    else
#endif
    {
        ucFcode = ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_EA_PORT_PAGE72_NF_FINAL2);

        ScalerTimerDelayXms(100);

        for(BYTE ucTimeout = 0; ucTimeout < 15; ucTimeout++)
        {
            if(abs(ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_EA_PORT_PAGE72_NF_FINAL2) - ucFcode) >= 2)
            {
                ScalerTimerDelayXms(100);

                ucFcode = ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_EA_PORT_PAGE72_NF_FINAL2);
            }
            else
            {
                break;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get Rx3 Audio HBR Setting
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerHdmiAudioRx3HbrAudioSettingForTmds(void)
{
    BYTE ucRecheckTime = 0;
    ScalerHdmiAudioRx3ClkStableCheckTime();

    // Set X Value = 0x00
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_32_PORT_PAGE72_HDMI_WDCR1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set Y Value = 0x00
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_33_PORT_PAGE72_HDMI_WDCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set I code of trend tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DC_PORT_PAGE72_AUD_BDRY_6, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DD_PORT_PAGE72_AUD_BDRY_7, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DE_PORT_PAGE72_AUD_BDRY_8, 0x00);

    // Set P code of trend tracking
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_DF_PORT_PAGE72_AUD_BDRY_9, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E0_PORT_PAGE72_AUD_BDRY_A, 0x00);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E1_PORT_PAGE72_AUD_BDRY_B, 0x00);

#if(_HDMI_AUDIO_SPREAD_PCODE_SUPPORT == _ON)
    // Set spread p code
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E4_PORT_PAGE72_P_SPREAD_2, 0x04);
    ScalerSetDataPortByte(P72_C9_HDMI_AP, _P72_CA_PT_E5_PORT_PAGE72_P_SPREAD_3, 0x00);

    // Enable P Code Spread
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_E2_PORT_PAGE72_P_SPREAD_0, ~_BIT7, _BIT7);
#endif

    ScalerHdmiAudioRx3HbrAudioResetForTmds();

    ScalerHdmiAudioRx3HbrAudioOutputForTmds();

    ScalerMcuDelayXus(999);

    while((ucRecheckTime < 10) && ((ScalerGetBit(P72_CB_HDMI_SR, (_BIT2 | _BIT1)) != 0x00) || (ScalerGetDataPortSingleByte(P72_C9_HDMI_AP, _P72_CA_PT_18_PORT_PAGE72_HDMI_MFDDR) >= 0x3C) || (GET_HDMI_RX3_HBR_AUDIO_FIFO_ERROR() == _TRUE)))
    {
        ScalerHdmiAudioRx3HbrAudioResetForTmds();

        ScalerHdmiAudioRx3HbrAudioOutputForTmds();

        ScalerMcuDelayXus(999);

        ucRecheckTime ++;
    }

    if(ucRecheckTime >= 10)
    {
        DebugMessageAudio("hbr audio fifo reset", ucRecheckTime);

        SET_HDMI_RX3_HBR_AUDIO_IS_SETTING();

        return _FALSE;
    }
    else
    {
        DebugMessageAudio("hbr audio output", 0x00);

        CLR_HDMI_RX3_HBR_AUDIO_IS_SETTING();

        // audio wd enable
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Get Rx3 Audio HBR Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3HbrAudioResetForTmds(void)
{
    DebugMessageAudio("HBR audio reset", 0x00);

    // audio wd disable
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~(_BIT2 | _BIT1), 0x00);

    // audio i/p code not work
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_31_PORT_PAGE72_HDMI_WDCR0, ~_BIT5, 0x00);

    // tracking disable
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_15_PORT_PAGE72_HDMI_PSCR, ~(_BIT3 | _BIT2), 0x00);
    // double buf
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_D0_PORT_PAGE72_HDMI_CMCR, ~(_BIT7 | _BIT5), _BIT7);

    // fifo W/R disable
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT2, 0x00);
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~(_BIT1 | _BIT0), 0x00);

    // Mac I2S output disable
    ScalerSetByte(P72_C9_HDMI_AP, _P72_CA_PT_62_PORT_PAGE72_HDMI_AOCR);
    ScalerSetByte(P72_CA_HDMI_DP, 0x00);

    // parallel mode reset
    SET_IIS_PARALLEL_MODE_RESET();
}


#ifdef __GNUC__
#pragma GCC push_options
#pragma GCC optimize("Os")
#endif
//--------------------------------------------------
// Description  : HBR Audio Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdmiAudioRx3HbrAudioOutputForTmds(void)
{
    bit bAfifoUnderFlow = _FALSE;
    WORD usAfifoCheckTime = 400;

    CLR_HDMI_RX3_HBR_AUDIO_FIFO_ERROR();

    // audio manual mode
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT6, 0x00);

    // manual gain enable
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT3, 0x00);

    // afifo R en
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT2, 0x00);
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~(_BIT1 | _BIT0), _BIT1);

    // w1c over/under flow flag
    ScalerSetBit(P72_CB_HDMI_SR, ~(_BIT7 | _BIT5 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    DebugMessageAudio("HBR Audio FIFO reset", 0x00);

    // reset afifo to empty
    while((usAfifoCheckTime != 0) && (bAfifoUnderFlow == _FALSE))
    {
        if(ScalerGetBit(P72_CB_HDMI_SR, _BIT1) == _BIT1)
        {
            DebugMessageAudio("HBR Audio FIFO underflow", usAfifoCheckTime);

            bAfifoUnderFlow = _TRUE;
        }
        ScalerMcuDelayXus(20);
        usAfifoCheckTime--;
    }

    // fifo W/R disable
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~_BIT2, 0x00);
    ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_03_PORT_PAGE72_HDMI_AFCR, ~(_BIT1 | _BIT0), 0x00);

    ScalerMcuDelayXus(5000);

    BYTE ucIntStatus = GET_INTERRUPT_GLOBAL_ENABLE_STATUS();
#if(_SCPU_SUPPORT == _ON)
    WORD usHbrResetCheckTime = 6400;

    SET_AUDIO_SCPU_AUDIO_STATE(_PARALLELMODE_HBR_FIRST_STATE_FOR_RX3_TMDS);
    // wait max 32ms(5us*6400) for SCPU entering ScalerSyncDelayForHbrAudioSetting
    while(usHbrResetCheckTime != 0)
    {
        if(GET_AUDIO_SCPU_AUDIO_STATE() == _PARALLELMODE_HBR_SECOND_STATE)
        {
            break;
        }
        ScalerMcuDelayXus(5);
        usHbrResetCheckTime--;
    }
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

    SET_AUDIO_SCPU_AUDIO_STATE(_PARALLELMODE_HBR_THIRD_STATE);

    usHbrResetCheckTime = 10;
    // wait max 700us(70us*10) for SCPU executing ScalerSyncSetHdmiAudioRx3HbrAudioOutputForTmds
    while(usHbrResetCheckTime != 0)
    {
        ScalerMcuDelayXus(70);
        if(GET_AUDIO_SCPU_AUDIO_STATE() == _PARALLELMODE_HBR_FOURTH_STATE)
        {
            break;
        }
        usHbrResetCheckTime--;
    }
    SET_AUDIO_SCPU_AUDIO_STATE(_PARALLELMODE_HBR_IDLE_STATE);
#else
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

    ScalerCpuSyncSetHdmiAudioRx3HbrAudioOutputForTmds();
#endif

    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(ucIntStatus);
}
#ifdef __GNUC__
#pragma GCC pop_options
#endif
#endif
#endif // End of #if(_HDMI_AUDIO_RX3_SUPPORT == _ON)
