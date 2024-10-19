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
// ID Code      : RL6952_Series_Audio.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_AUDIO__

#include "ScalerFunctionInclude.h"
#include "Audio/ScalerAudio.h"


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
// Description  : Control Audio Clock Gating
// Input Value  : EnumAudioInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioClockGatingControl(bit bEnable)
{
    if(bEnable == _OFF)
    {
        // Disable Clcok Gating
        ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT0, _BIT0);
    }
    else
    {
        // Enable Clcok Gating
        ScalerSetBit(P6_D5_SOFT_RESET_DAC, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Transfer depop mode to Normal mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDacDisable(void)
{
#if(_EMBEDDED_DAC_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_INITIAL);
    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL);
    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_CHARGE);

    ScalerAudioDACNormalToDepop();

    ScalerAudioDACSetVcmReady(_OFF);

    // Power Down Depop CLK
    ScalerAudioDACDepopModeStatus(_OFF);

    // Disable AIO and HPO Power
    ScalerAudioDACAIOHPOPowerControl(_OFF);

    // Disable DAC Power and Depop Circuit and DAC Vref & DAC LDO
    ScalerAudioDACPowerControl(_OFF);

    SET_AUDIO_DAC_STATE(_AUDIO_DAC_OFF);
#endif

#if(_LINE_IN_SUPPORT == _ON)
    // Disable ADC Power
    ScalerAudioADCPowerControl(_OFF);
#elif(_EMBEDDED_DAC_SUPPORT == _ON)
    // Disable Power Charge For mbias and Vref
    ScalerAudioChargeVrefControl(_OFF);
#endif

    // Disable DVC counter for power saving
    ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, _BIT6);

    // Power Down DPLL
    ScalerAudioDisableAudioPLL();
}

//--------------------------------------------------
// Description  : Switch audio Input (AIN / DAC)
// Input Value  : bAudioSource
// Output Value : None
//--------------------------------------------------
void ScalerAudioSourceInputSwitch(EnumAudioInputSource enumAudioSourceType, EnumInputPort enumInputPort)
{
    if(enumAudioSourceType == _DIGITAL_AUDIO)
    {
        EnumAudioInputPort enumAudioInputPort = ScalerAudioDxToRxMapping(enumInputPort, _AUDIO_PORT_MAP_TO_TARGET);

#if(_DUAL_DP_SUPPORT == _ON)
        CLR_AUDIO_DUAL_DP_STATUS();
#endif

        // Disable HPF
        ScalerSetBit(P6_D0_DA_CTRL, ~_BIT6, 0x00);

        // Select DAC Mux to Digital input
        ScalerAudioSetInputSource(_DIGITAL_AUDIO);

#if(_LINE_IN_SUPPORT == _ON)
        // Audio PLL Power On
        ScalerSetBit(PBF_A8_AUDIO_PLL_CONTROL, ~_BIT0, _BIT0);

#if(_LINE_IN_AA_PATH_SUPPORT == _ON)
        // Set DAC Path
        ScalerAudioDACOutputControl(_AUDIO_DAC_OUTPUT_DAC_PATH);
#endif
#endif

        ScalerAudioInputPortSwitch(enumAudioInputPort);

#if(_DUAL_DP_SUPPORT == _ON)
        if(enumInputPort == _DUAL_DP_INPUT_PORT)
        {
            SET_AUDIO_DUAL_DP_STATUS();
        }
#endif
        // Reset DVC Counter
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, _BIT6);
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, 0x00);

        // Audio Soft Reset of DAC path
        ScalerAudioDACSoftReset();

#if(_EMBEDDED_DAC_SUPPORT == _ON)
#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        // Set SOUT Gain After DAC Block
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_SPEAKER, _DIGITAL_DAC_AOUT_GAIN_DB);
#endif

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        // Set HPOUT Gain After DAC Block
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_HEADPHONE, _DIGITAL_DAC_HPOUT_GAIN_DB);
#endif
#endif

#if(_AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT == _ON)
        // Set Hard Gain for Digital Audio
        ScalerSetBit(P8_A9_DVC_GAIN_DONE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _DIGITAL_HARD_GAIN_VALUE);
#endif
    }
#if(_LINE_IN_SUPPORT == _ON)
    else if(enumAudioSourceType == _LINE_IN_AUDIO)
    {
#if(_LINE_IN_AA_PATH_SUPPORT == _OFF)
        // Enable Audio ADC PLL
        ScalerAudioSetADCAudioPLL();
#endif
        // Select DAC Mux to ADC input
        ScalerAudioSetInputSource(_LINE_IN_AUDIO);

        // Switch port to Audio ADC
        ScalerAudioInputPortSwitch(_AUDIO_FROM_ADC_PORT);

        // Enable HPF
        ScalerSetBit(P6_D0_DA_CTRL, ~_BIT6, _BIT6);

        // Reset DVC Counter
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, _BIT6);
        ScalerSetBit(P8_A0_DVC_EN, ~_BIT6, 0x00);

        // Audio Soft Reset of all path
        ScalerAudioADCDACSoftReset();

#if(_EMBEDDED_DAC_SUPPORT == _ON)
#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        // Set SOUT Gain After DAC Block
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_SPEAKER, _LINE_IN_DAC_AOUT_GAIN_DB);
#endif

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        // Set HPOUT Gain After DAC Block
        ScalerAudioDACSetOutputGain(_AUDIO_DAC_OUTPUT_HEADPHONE, _LINE_IN_DAC_HPOUT_GAIN_DB);
#endif
#endif

#if(_LINE_IN_AA_PATH_SUPPORT == _ON)
        // Audio Setting AA Path Mode
        ScalerAudioSettingAAPathMode();
#endif

#if(_AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT == _ON)
        // Set Hard Gain for Line in Audio
        ScalerSetBit(P8_A9_DVC_GAIN_DONE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _LINE_IN_HARD_GAIN_VALUE);
#endif
    }
#endif
}

//--------------------------------------------------
// Description  : Audio ADC S/PDIF & I2S Output For ADC Input
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioADCDigitalOutputSetting(void)
{
    // Set Channel Count "2 ch" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E3_AD_SPDIF_CS_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Enable I2S Output for ADC In
    ScalerSetBit(P6_E7_AD_I2S_CTRL, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Set Current DAC Input Source
// Input Value  : _LINE_IN_AUDIO/ _DIGITAL_AUDIO
// Output Value : None
//--------------------------------------------------
void ScalerAudioSetInputSource(EnumAudioInputSource enumAudioInputSource)
{
    ScalerSetBit(P6_D1_DA_MUTE, ~_BIT3, ((enumAudioInputSource == _DIGITAL_AUDIO) ? 0x00 : _BIT3));
}

//--------------------------------------------------
// Description  : Audio Setting AA Path Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioSettingAAPathMode(void)
{
#if(_LINE_IN_AA_PATH_SUPPORT == _ON)
    // Set input buff gain = 0.42dB
    ScalerAudioADCInputbufferGain(_AUDIO_INPUT_BUFFER_AA_PATH);

    // Switch DF2SE All-Mute
    ScalerAudioDACDF2SEInputMux(_AUDIO_AIO_HPO_MODE, _AUDIO_MUTE_PATH);

    // Set A-A Path
    ScalerAudioDACOutputControl(_AUDIO_DAC_OUTPUT_AA_PATH);
#endif
}

//--------------------------------------------------
// Description  : Charge Audio Vref to AVDD/2 Fast Control
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerAudioChargeVrefFastControl(bit bEnable)
{
    if(bEnable == _ON)
    {
        // Enable Fast Charge Control
        ScalerSetBit(P6_CA_REG_DAC_CUR8, ~_BIT4, _BIT4);

        // Fast Mode for mbias RC Filter
        ScalerSetBit(P6_CB_REG_DAC_CUR9, ~_BIT4, _BIT4);

        // Fast Mode for mbias RC Filter
        ScalerSetBit(P6_CB_REG_DAC_CUR9, ~_BIT3, _BIT3);
    }
    else
    {
        // Disable Fast Charge Control
        ScalerSetBit(P6_CA_REG_DAC_CUR8, ~_BIT4, 0x00);

        // Normal Mode for mbias RC Filter
        ScalerSetBit(P6_CB_REG_DAC_CUR9, ~_BIT4, 0x00);

        // Normal Mode for mbias RC Filter
        ScalerSetBit(P6_CB_REG_DAC_CUR9, ~_BIT3, 0x00);
    }
}

//--------------------------------------------------
// Description  : Charge Audio Vref to AVDD/2
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerAudioChargeVrefControl(bit bEnable)
{
    // Control Power Charge For mbias and Vref
    ScalerSetBit(P6_B0_REG_ADC_POWER, ~(_BIT7 | _BIT6), (((BYTE) bEnable << 7) | ((BYTE) bEnable << 6)));
}

//--------------------------------------------------
// Description  : Control DAC Depop Mode Status
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACDepopModeStatus(bit bEnable)
{
    if(bEnable == _ON)
    {
        // Depop Clock Setting 55.75KHz
        ScalerSetBit(P6_D4_DA_CLK_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

        // Enable Depop Clock
        ScalerSetBit(P6_D4_DA_CLK_CTRL, ~_BIT4, _BIT4);
    }
    else
    {
        // Disable Depop Clock
        ScalerSetBit(P6_D4_DA_CLK_CTRL, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Control DAC Power Status
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACPowerControl(bit bEnable)
{
    if(bEnable == _ON)
    {
        // Enable  DAC L/R Channel Power
        ScalerSetBit(P6_C1_REG_DAC_POWER1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // DAC Current Setting 10uA
        ScalerSetBit(P6_C1_REG_DAC_POWER1, ~(_BIT3 | _BIT2), _BIT3);

        // Enable DAC Use Power Type
        ScalerAudioDACUsePowerControl(_ON);
    }
    else
    {
        // Disable  DAC L/R Channel Power
        ScalerSetBit(P6_C1_REG_DAC_POWER1, ~(_BIT7 | _BIT6), 0x00);

        // Disable DAC Use Power Type
        ScalerAudioDACUsePowerControl(_OFF);
    }
}

//--------------------------------------------------
// Description  : Switch Audio DAC Use Power Control
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACUsePowerControl(bit bEnable)
{
#if(_AUDIO_DAC_USE_POWER_TYPE == _EXTERNAL_PCB_V33S)
    // Switch DAC Power Use External PCB AUDIO_V33S
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT7 | _BIT6), ((BYTE) bEnable << 6));
#elif(_AUDIO_DAC_USE_POWER_TYPE == _TEST_MODE_INTERNAL_LDO_V33S)
    // Switch DAC Power Use Internal LDO_V33S
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT7 | _BIT6), ((BYTE) bEnable << 7));
#endif
}

//--------------------------------------------------
// Description  : Switch Audio (AIO/HPO) Output Signal
// Input Value  : enumAudioDACOutputControl
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACOutputControl(EnumAudioDACOutputControl enumAudioDACOutputControl)
{
    if(enumAudioDACOutputControl == _AUDIO_DAC_OUTPUT_DAC_PATH)
    {
        // Set Speaker L/R Output
        ScalerSetBit(P6_E0_REG_MUX_ANA_OUT1, ~(_BIT5 | _BIT4), 0x00);

        // Set Headphone L/R Output
        ScalerSetBit(P6_E0_REG_MUX_ANA_OUT1, ~(_BIT1 | _BIT0), 0x00);

        DebugMessageAudio("0.[Top Audio]Audio AFE Switch DAC Path", 0x00);
    }
    else if(enumAudioDACOutputControl == _AUDIO_DAC_OUTPUT_AA_PATH)
    {
#if(_DAC_SPEAKER_OUTPUT_SWAP == _OFF)
        // Set Speaker L/R Output
        ScalerSetBit(P6_E0_REG_MUX_ANA_OUT1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
#else
        // Swap Speaker L/R Output
        ScalerSetBit(P6_E0_REG_MUX_ANA_OUT1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5 | _BIT4));
#endif

#if(_DAC_HP_OUTPUT_SWAP == _OFF)
        // Set Headphone L/R Output
        ScalerSetBit(P6_E0_REG_MUX_ANA_OUT1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#else
        // Swap Headphone L/R Output
        ScalerSetBit(P6_E0_REG_MUX_ANA_OUT1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
#endif
        DebugMessageAudio("0.[Top Audio]Audio AFE Switch AA Path", 0x00);
    }
}

//--------------------------------------------------
// Description  : AIO & HPO DF2SE Input Mux Mode Control
// Input Value  : None
// Output Value : _ALLMUTE / _RDAC_LDAC_SWAP / _DEBUG / _DAC_MODE
//--------------------------------------------------
void ScalerAudioDACDF2SEInputMux(EnumAudioDACAIOHPOPATHControl enumAudioDACAIOHPOPATHControl, EnumAudioDF2SEMUXControl enumDF2SEControl)
{
    DebugMessageAudio("0.[Top Audio]Audio DF2SE Path", enumAudioDACAIOHPOPATHControl);
    DebugMessageAudio("0.[Top Audio]Audio DF2SE Control", enumDF2SEControl);

    switch(enumAudioDACAIOHPOPATHControl)
    {
        case _AUDIO_AIO_MODE:

            switch(enumDF2SEControl)
            {
#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
                case _AUDIO_MUTE_PATH:

                    // AIO DF2SE Input MUX Switch All-Mute Path
                    ScalerSetBit(P6_C7_REG_DAC_CUR5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    break;

                case _AUDIO_RDAC_LDAC_SWAP:

                    // AIO DF2SE Input MUX Switch L/R Swap
                    ScalerSetBit(P6_C7_REG_DAC_CUR5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
                    break;

                case _AUDIO_DEBUG_PATH:

                    // AIO DF2SE Input MUX Switch Debug Path
                    ScalerSetBit(P6_C7_REG_DAC_CUR5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT2 | _BIT0));
                    break;

                case _AUDIO_DAC_MODE_PATH:

                    // AIO DF2SE Input MUX Switch DAC Path
                    ScalerSetBit(P6_C7_REG_DAC_CUR5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT1));
                    break;
#endif
                default:
                    break;
            }

            break;

        case _AUDIO_HPO_MODE:

            switch(enumDF2SEControl)
            {
#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
                case _AUDIO_MUTE_PATH:

                    // HPO DF2SE Input MUX Switch All-Mute Path
                    ScalerSetBit(P6_C9_REG_DAC_CUR7, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    break;

                case _AUDIO_RDAC_LDAC_SWAP:

                    // HPO DF2SE Input MUX Switch L/R Swap
                    ScalerSetBit(P6_C9_REG_DAC_CUR7, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
                    break;

                case _AUDIO_DEBUG_PATH:

                    // HPO DF2SE Input MUX Switch Debug Path
                    ScalerSetBit(P6_C9_REG_DAC_CUR7, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT2 | _BIT0));
                    break;

                case _AUDIO_DAC_MODE_PATH:

                    // HPO DF2SE Input MUX Switch DAC Path
                    ScalerSetBit(P6_C9_REG_DAC_CUR7, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT1));
                    break;
#endif
                default:
                    break;
            }

            break;

        case _AUDIO_AIO_HPO_MODE:

            switch(enumDF2SEControl)
            {
#if((_DAC_SPEAKER_OUTPUT_SUPPORT == _ON) || (_DAC_HP_OUTPUT_SUPPORT == _ON))
                case _AUDIO_MUTE_PATH:

                    // AIO DF2SE Input MUX Switch All-Mute Path
                    ScalerSetBit(P6_C7_REG_DAC_CUR5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // HPO DF2SE Input MUX Switch All-Mute Path
                    ScalerSetBit(P6_C9_REG_DAC_CUR7, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    break;

                case _AUDIO_RDAC_LDAC_SWAP:

                    // AIO DF2SE Input MUX Switch L/R Swap
                    ScalerSetBit(P6_C7_REG_DAC_CUR5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));

                    // HPO DF2SE Input MUX Switch L/R Swap
                    ScalerSetBit(P6_C9_REG_DAC_CUR7, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
                    break;

                case _AUDIO_DEBUG_PATH:

                    // AIO DF2SE Input MUX Switch Debug Path
                    ScalerSetBit(P6_C7_REG_DAC_CUR5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT2 | _BIT0));

                    // HPO DF2SE Input MUX Switch Debug Path
                    ScalerSetBit(P6_C9_REG_DAC_CUR7, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT2 | _BIT0));
                    break;

                case _AUDIO_DAC_MODE_PATH:

                    // AIO DF2SE Input MUX Switch DAC Path
                    ScalerSetBit(P6_C7_REG_DAC_CUR5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT1));

                    // HPO DF2SE Input MUX Switch DAC Path
                    ScalerSetBit(P6_C9_REG_DAC_CUR7, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT1));
                    break;
#endif
                default:
                    break;
            }
        default:
            break;
    }
}

#if(_LINE_IN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial Audio ADC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioADCInitial(void)
{
    // Disable Clcok Gating
    ScalerAudioClockGatingControl(_OFF);

    // Enable ADDA Loop, High Pass Filter and Set ADC ZCD Type
    ScalerSetBit(P6_B6_AD_CTRL_0, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT6 | _BIT3));

    // Enable Power Fast Charge Mode
    ScalerAudioChargeVrefFastControl(_ON);

    // Enable Power Charge For mbias/ Vref
    ScalerAudioChargeVrefControl(_ON);

    // Enable ADC Power Control
    ScalerAudioADCPowerControl(_ON);

    // Setting ADC Input Buffer Gain
    ScalerAudioADCInputbufferGain(_AUDIO_INPUT_BUFFER_ADC_PATH);

    // ADC Unmute and Set Boost Gain
    ScalerSetByte(P6_B7_AD_MUTE, 0x00);

    ScalerAudioADCADGainSetting();

    // Set ADC Input Clock
    ScalerSetBit(_REG_AD_GAIN_DB_L, ~_BIT6, 0x00)

    // Set Sampling Frequency "48kHz" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);

    // Set S/PDIF & I2S From ADC Input
    ScalerAudioADCDigitalOutputSetting();
}

//--------------------------------------------------
// Description  : Audio ADC AD Gain Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioADCADGainSetting(void)
{
    // Set AD Gail of L Ch
    ScalerSetBit(_REG_AD_GAIN_DB_L, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _LINE_IN_BOOST_GAIN_DB);

    // Set AD Gail of R Ch
    ScalerSetBit(_REG_AD_GAIN_DB_R, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _LINE_IN_BOOST_GAIN_DB);

    // Set Double Buffer
    ScalerSetBit(_REG_AD_GAIN_DB_L, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Audio ADC Power Control
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerAudioADCPowerControl(bit bEnable)
{
    if(bEnable == _ON)
    {
        // Enable Audio ADC Power
        ScalerSetBit(P6_B0_REG_ADC_POWER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Enable ADC Chopper
        ScalerSetBit(P6_B1_REG_ADC_CTRL1, ~_BIT3, _BIT3);
    }
    else
    {
        // Disable ADC Chopper
        ScalerSetBit(P6_B1_REG_ADC_CTRL1, ~_BIT3, 0x00);

        // Disable Audio ADC Power
        ScalerSetBit(P6_B0_REG_ADC_POWER, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : Audio ADC Input Buffer Gain Control
// Input Value  : None
// Output Value : _AUDIO_INPUT_BUFFER_ADC_PATH
//                _AUDIO_INPUT_BUFFER_AUDIO_AA_PATH
//--------------------------------------------------
void ScalerAudioADCInputbufferGain(EnumAudioInputBufferGainControl enumGainControl)
{
    if(enumGainControl == _AUDIO_INPUT_BUFFER_ADC_PATH)
    {
        // ADC Input Buffer Gain = 0dB
        ScalerSetBit(P6_B1_REG_ADC_CTRL1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
    }
    else if(enumGainControl == _AUDIO_INPUT_BUFFER_AA_PATH)
    {
        // ADC Input Buffer Gain = +0.42dB
        ScalerSetBit(P6_B1_REG_ADC_CTRL1, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    }
}
#endif // End of #if(_LINE_IN_SUPPORT == _ON)

#if(_EMBEDDED_DAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial Audio DAC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACInitial(void)
{
    // Disable Clcok Gating
    ScalerAudioClockGatingControl(_OFF);

    // Set DAC DC OffSet
    ScalerAudioDACDCOffSetState(_OFF);

    // AIO & HPO DF2SE Input Mux Mode Control
    ScalerAudioDACDF2SEInputMux(_AUDIO_AIO_HPO_MODE, _AUDIO_MUTE_PATH);

#if(_LINE_IN_SUPPORT == _OFF)
    // Enable Power Fast Charge Mode
    ScalerAudioChargeVrefFastControl(_ON);

    // Enable Power Charge For mbias/ Audio Vref
    ScalerAudioChargeVrefControl(_ON);
#endif

    // Setting DAC HPO 32ohm Mode
    ScalerAudioDACHPOModeControl(_AUDIO_HPO_32_OHM_MODE);

    // Control HPO Power MOS for Initial
    ScalerAudioDACHPOPowerMOSControl(_AUDIO_POWER_MOS_STATUS_INITIAL);

    // Enable AIO & HPO Power
    ScalerAudioDACAIOHPOPowerControl(_ON);

    // Enable Depop Clock / Depop Clock Setting 55.75KHz
    ScalerAudioDACDepopModeStatus(_ON);

    // Enable DAC AIO & HPO Depop Mode
    ScalerAudioDACDepopModeControl(_AUDIO_DAC_DEPOP_MODE);

    // Enable DAC Power
    ScalerAudioDACPowerControl(_ON);

    // Initial DAC Output Gain for 0dB
    ScalerAudioDACOutputGainInitial();

    ////////// Digital //////////
    // Set DAC Dither Function
    ScalerSetBit(P6_D0_DA_CTRL, ~(_BIT5 | _BIT4), (_DAC_DITHER_FUNCTION_LEVEL << 4));

    // Un-Mute DAC For Digital Circuit
    ScalerSetBit(P6_D1_DA_MUTE, ~(_BIT7 | _BIT6), 0x00);

    // Select DAC Mux to Digital input
    ScalerAudioSetInputSource(_DIGITAL_AUDIO);

    // Set Audio DAC Digital Volume
    ScalerAudioDACDigitalVolumeSetting();

    // Set AIO & HPO L/R Output
    ScalerAudioDACOutputControl(_AUDIO_DAC_OUTPUT_DAC_PATH);
}

//--------------------------------------------------
// Description  : Control Audio DAC(AIO/HPO) Power Output
// Input Value  : enumDACOutput
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACOutputSwitch(EnumAudioDACOutput enumDACOutput)
{
    switch(enumDACOutput)
    {
#if((_DAC_SPEAKER_OUTPUT_SUPPORT == _ON) && (_DAC_HP_OUTPUT_SUPPORT == _ON))
        case _AUDIO_DAC_OUTPUT_BOTH:

            SET_AUDIO_AIO_POWER();
            SET_AUDIO_HPO_POWER();
#endif
        break;

#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        case _AUDIO_DAC_OUTPUT_SPEAKER:

            SET_AUDIO_AIO_POWER();
            CLR_AUDIO_HPO_POWER();
#endif
        break;

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        case _AUDIO_DAC_OUTPUT_HEADPHONE:

            SET_AUDIO_HPO_POWER();
            CLR_AUDIO_AIO_POWER();
#endif
        break;

        default:

            CLR_AUDIO_AIO_POWER();
            CLR_AUDIO_HPO_POWER();

            break;
    }
}

//--------------------------------------------------
// Description  : When Vcm already charge to AVDD/2, Vo(Output Voltage) should charge as Vcm
// Input Value  : bReady
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACSetVcmReady(bit bReady)
{
    if(bReady == _ON)
    {
        // Enable Power for DPRAMP
        ScalerSetBit(P6_C5_REG_DAC_CUR3, ~_BIT7, _BIT7);

        ScalerTimerDelayXms(2);

        // Enable Power for RAMPGEN
        ScalerSetBit(P6_C5_REG_DAC_CUR3, ~_BIT6, _BIT6);

        DebugMessageAudio("0.[Top Audio]Audio VCM Charge _ON", 0x00);
    }
    else
    {
        // Enable Power for DPRAMP
        ScalerSetBit(P6_C5_REG_DAC_CUR3, ~_BIT7, 0x00);

        ScalerTimerDelayXms(2);

        // Enable Power for RAMPGEN
        ScalerSetBit(P6_C5_REG_DAC_CUR3, ~_BIT6, 0x00);

        DebugMessageAudio("0.[Top Audio]Audio VCM Charge _OFF", 0x00);
    }
}

//--------------------------------------------------
// Description  : Transfer depop mode to Normal mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACNormalToDepop(void)
{
    // Disable VCM Charge
    ScalerAudioDACSetVcmReady(_OFF);

    // Enable Depop Clock
    ScalerAudioDACDepopModeStatus(_ON);

    // Setting DAC HPO 10Kohm Mode
    ScalerAudioDACHPOModeControl(_AUDIO_HPO_10K_OHM_MODE);

    // Enable DAC Depop Mode / DAC Control Depop Mode
    ScalerAudioDACDepopModeControl(_AUDIO_DAC_DEPOP_MODE);

    // DAC DF2SE Input MUX Switch All-Mute Path
    ScalerAudioDACDF2SEInputMux(_AUDIO_AIO_HPO_MODE, _AUDIO_MUTE_PATH);

    // Enable VCM Charge
    ScalerAudioDACSetVcmReady(_ON);

    ScalerAudioDACSetState(_AUDIO_DAC_DEPOP);
}

//--------------------------------------------------
// Description  : Transfer depop mode to normal mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACDepopToNormal(void)
{
    // Disable Power Fast Charge Mode
    ScalerAudioChargeVrefFastControl(_OFF);

    // Enable DAC HPO Power MOS Control
    ScalerAudioDACHPOPowerMOSControl(_AUDIO_POWER_MOS_STATUS_NORMAL);

    // Disable DAC Depop Mode / DAC Control Normal Mode
    ScalerAudioDACDepopModeControl(_AUDIO_DAC_NORMAL_MODE);

    // Disable Depop Clock
    ScalerAudioDACDepopModeStatus(_OFF);

    // Setting DAC HPO 32ohm Mode
    ScalerAudioDACHPOModeControl(_AUDIO_HPO_32_OHM_MODE);

    // Enable AIO & HPO Gain Control
    ScalerAudioDACGainControl(_ON);

    // Setting DAC HPO 32ohm Mode
    ScalerAudioDACHPOModeControl(_AUDIO_HPO_32_OHM_MODE);

    // Disable VCM Charge
    ScalerAudioDACSetVcmReady(_OFF);

    ScalerAudioDACSetState(_AUDIO_DAC_READY);
}

//--------------------------------------------------
// Description  : Switch AOUT/HPOUT to Normal Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACOutputEnable(void)
{
#if((_LINE_IN_SUPPORT == _ON) && (_LINE_IN_AA_PATH_SUPPORT == _ON))
    if(ScalerAudioGetInputSource(_AUDIO_DAC_OUT) == _LINE_IN_AUDIO)
    {
        return;
    }
#endif
    // Disable VCM Charge
    ScalerAudioDACSetVcmReady(_OFF);

    if(ScalerGetBit(P6_C0_REG_DAC_POWER0, _BIT5) == _BIT5)
    {
#if(_DAC_SPEAKER_OUTPUT_SWAP == _OFF)
        // Set AIO L/R Output
        ScalerAudioDACDF2SEInputMux(_AUDIO_AIO_MODE, _AUDIO_DAC_MODE_PATH);
#else
        // Set AIO L/R Swap utput
        ScalerAudioDACDF2SEInputMux(_AUDIO_AIO_MODE, _AUDIO_RDAC_LDAC_SWAP);
#endif
    }

    if(ScalerGetBit(P6_C0_REG_DAC_POWER0, _BIT4) == _BIT4)
    {
#if(_DAC_HP_OUTPUT_SWAP == _OFF)
        // Set HPO L/R Output
        ScalerAudioDACDF2SEInputMux(_AUDIO_HPO_MODE, _AUDIO_DAC_MODE_PATH);
#else
        // Set HPO L/R Swap utput
        ScalerAudioDACDF2SEInputMux(_AUDIO_HPO_MODE, _AUDIO_RDAC_LDAC_SWAP);
#endif
    }

    // Enable VCM Charge
    ScalerAudioDACSetVcmReady(_ON);
}

//--------------------------------------------------
// Description  : Get Current DAC Output Channel
// Input Value  : None
// Output Value : EnumAudioDACOutput
//--------------------------------------------------
EnumAudioDACOutput ScalerAudioDACGetOutput(void)
{
    if(ScalerGetBit(P6_C0_REG_DAC_POWER0, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        return _AUDIO_DAC_OUTPUT_BOTH;
    }
    else if(ScalerGetBit(P6_C0_REG_DAC_POWER0, (_BIT5 | _BIT4)) == _BIT5)
    {
        return _AUDIO_DAC_OUTPUT_SPEAKER;
    }
    else if(ScalerGetBit(P6_C0_REG_DAC_POWER0, (_BIT5 | _BIT4)) == _BIT4)
    {
        return _AUDIO_DAC_OUTPUT_HEADPHONE;
    }
    return _AUDIO_DAC_OUTPUT_NONE;
}

//--------------------------------------------------
// Description  : Set DAC Output Gain
// Input Value  : EnumAudioDACOutput, ucOutputGain
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACSetOutputGain(EnumAudioDACOutput enumOutputType, EnumAudioDacOutputGain enumOutputGain)
{
    if(enumOutputType == _AUDIO_DAC_OUTPUT_SPEAKER)
    {
#if(_AUDIO_DAC_USE_POWER_TYPE == _EXTERNAL_PCB_V33S)
        if(enumOutputGain == _AUDIO_DAC_OUTPUT_GAIN_0_DB)
        {
            // Set AOUT Gain After DAC Block
            ScalerSetBit(P6_C6_REG_DAC_CUR4, ~(_BIT7 | _BIT6), 0x00);
        }
        else
        {
            // Set AOUT Gain After DAC Block
            ScalerSetBit(P6_C6_REG_DAC_CUR4, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((enumOutputGain << 3) | enumOutputGain));
        }

#elif(_AUDIO_DAC_USE_POWER_TYPE == _TEST_MODE_INTERNAL_LDO_V33S)
        // Set AOUT Gain After DAC Block
        ScalerSetBit(P6_C6_REG_DAC_CUR4, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((enumOutputGain << 3) | enumOutputGain));
#endif
    }
    else if(enumOutputType == _AUDIO_DAC_OUTPUT_HEADPHONE)
    {
#if(_AUDIO_DAC_USE_POWER_TYPE == _EXTERNAL_PCB_V33S)
        if(enumOutputGain == _AUDIO_DAC_OUTPUT_GAIN_0_DB)
        {
            // Set HPOUT Gain After DAC Block
            ScalerSetBit(P6_C8_REG_DAC_CUR6, ~(_BIT7 | _BIT6), 0x00);
        }
        else
        {
            // Set HPOUT Gain After DAC Block
            ScalerSetBit(P6_C8_REG_DAC_CUR6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((enumOutputGain << 3) | enumOutputGain));
        }

#elif(_AUDIO_DAC_USE_POWER_TYPE == _TEST_MODE_INTERNAL_LDO_V33S)
        // Set HPOUT Gain After DAC Block
        ScalerSetBit(P6_C8_REG_DAC_CUR6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((enumOutputGain << 3) | enumOutputGain));
#endif
    }
    else if(enumOutputType == _AUDIO_DAC_OUTPUT_BOTH)
    {
#if(_AUDIO_DAC_USE_POWER_TYPE == _EXTERNAL_PCB_V33S)
        if(enumOutputGain == _AUDIO_DAC_OUTPUT_GAIN_0_DB)
        {
            // Set AOUT Gain After DAC Block
            ScalerSetBit(P6_C6_REG_DAC_CUR4, ~(_BIT7 | _BIT6), 0x00);

            // Set HPOUT Gain After DAC Block
            ScalerSetBit(P6_C8_REG_DAC_CUR6, ~(_BIT7 | _BIT6), 0x00);
        }
        else
        {
            // Set AOUT Gain After DAC Block
            ScalerSetBit(P6_C6_REG_DAC_CUR4, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((enumOutputGain << 3) | enumOutputGain));

            // Set HPOUT Gain After DAC Block
            ScalerSetBit(P6_C8_REG_DAC_CUR6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((enumOutputGain << 3) | enumOutputGain));
        }

#elif(_AUDIO_DAC_USE_POWER_TYPE == _TEST_MODE_INTERNAL_LDO_V33S)
        // Set AOUT Gain After DAC Block
        ScalerSetBit(P6_C6_REG_DAC_CUR4, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((enumOutputGain << 3) | enumOutputGain));

        // Set HPOUT Gain After DAC Block
        ScalerSetBit(P6_C8_REG_DAC_CUR6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((enumOutputGain << 3) | enumOutputGain));
#endif
    }
    SET_DAC_AOUT_GAIN_DB(enumOutputGain);
    SET_DAC_HPOUT_GAIN_DB(enumOutputGain);
}

//--------------------------------------------------
// Description  : Control DAC AIO & HPO Power Status
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACAIOHPOPowerControl(bit bEnable)
{
    if(bEnable == _ON)
    {
#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        // Power On for Headphone Power
        SET_AUDIO_HPO_POWER();
#endif

#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        // Power On for Line Out Power
        SET_AUDIO_AIO_POWER();
#endif
    }
    else
    {
#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        // Power OFF for HPO Power
        CLR_AUDIO_HPO_POWER();
#endif

#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        // Power OFF for AIO Power
        CLR_AUDIO_AIO_POWER();
#endif
    }
}

//--------------------------------------------------
// Description  : Control DAC HPO Mode Select
// Input Value  : EnumAudioDACHPOModeControl
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACHPOModeControl(EnumAudioDACHPOModeControl enumAudioDACHPOModeControl)
{
    if(enumAudioDACHPOModeControl == _AUDIO_HPO_32_OHM_MODE)
    {
#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        // HPO Output Select Loading 32ohm Mode
        ScalerSetBit(P6_C2_REG_DAC_CUR0, ~_BIT0, _BIT0);
#endif
    }
    else
    {
        // HPO Output Select Loading 10Kohm Mode
        ScalerSetBit(P6_C2_REG_DAC_CUR0, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Control HPO Power MOS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACHPOPowerMOSControl(EnumAudioDACHPOPowerMOSControl enumPowerMosStatus)
{
    switch(enumPowerMosStatus)
    {
        case _AUDIO_POWER_MOS_STATUS_INITIAL:

            // Control HPO Power MOS Initial
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            break;

        case _AUDIO_POWER_MOS_STATUS_NORMAL:

            // Control HPO Power MOS Switch Normal -> Total:21msec
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerTimerDelayXms(3);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerTimerDelayXms(3);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerTimerDelayXms(3);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerTimerDelayXms(3);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerTimerDelayXms(3);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            ScalerTimerDelayXms(3);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerTimerDelayXms(3);
            break;

        case _AUDIO_POWER_MOS_STATUS_FAST:

            // Control HPO Power MOS Switch Normal -> Total:14msec
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerTimerDelayXms(2);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerTimerDelayXms(2);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerTimerDelayXms(2);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerTimerDelayXms(2);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerTimerDelayXms(2);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            ScalerTimerDelayXms(2);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerTimerDelayXms(2);
            break;

        case _AUDIO_POWER_MOS_STATUS_SUPERFAST:

            // Control HPO Power MOS Switch Normal -> Total:8msec
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerTimerDelayXms(2);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerTimerDelayXms(2);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);
            ScalerTimerDelayXms(2);
            ScalerSetBit(P6_C4_REG_DAC_CUR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerTimerDelayXms(2);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Switch DAC AIO & HPO For Depop/Normal Mode
// Input Value  : EnumAudioDACDepopModeControl
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACDepopModeControl(EnumAudioDACDepopModeControl enumAudioDACDepopModeControl)
{
    if(enumAudioDACDepopModeControl == _AUDIO_DAC_DEPOP_MODE)
    {
#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        // Switch AIO For Depop Mode
        ScalerSetBit(P6_C5_REG_DAC_CUR3, ~(_BIT3 | _BIT2), _BIT2);
#endif

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        // Switch HPO For Depop Mode
        ScalerSetBit(P6_C5_REG_DAC_CUR3, ~(_BIT1 | _BIT0), _BIT0);
#endif
    }
    else if(enumAudioDACDepopModeControl == _AUDIO_DAC_NORMAL_MODE)
    {
#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        // Switch AIO For Normal Mode
        ScalerSetBit(P6_C5_REG_DAC_CUR3, ~(_BIT3 | _BIT2), _BIT3);
#endif

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        // Switch HPO For Normal Mode
        ScalerSetBit(P6_C5_REG_DAC_CUR3, ~(_BIT1 | _BIT0), _BIT1);
#endif
    }
}

//--------------------------------------------------
// Description  : Initial DAC Output Gain
// Input Value  : EnumAudioDACOutput, ucOutputGain
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACOutputGainInitial(void)
{
#if(_AUDIO_DAC_USE_POWER_TYPE == _EXTERNAL_PCB_V33S)
    // Control AIO Gain
    ScalerSetBit(P6_C6_REG_DAC_CUR4, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Control HPO Gain
    ScalerSetBit(P6_C8_REG_DAC_CUR6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#elif(_AUDIO_DAC_USE_POWER_TYPE == _TEST_MODE_INTERNAL_LDO_V33S)
    // Control AIO Gain
    ScalerSetBit(P6_C6_REG_DAC_CUR4, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1));

    // Control HPO Gain
    ScalerSetBit(P6_C8_REG_DAC_CUR6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));
#endif

    // Enable AIO & HPO Gain Control
    ScalerAudioDACGainControl(_ON);
}

//--------------------------------------------------
// Description  : Control Audio DAC Digital Volume Setting
// Input Value  : EnumAudioInputPort
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACDigitalVolumeSetting(void)
{
    // Set DAC Volume Of L/R Ch
    ScalerSetByte(P6_D2_DA_GAIN_L, 0x57);
    ScalerSetByte(P6_D3_DA_GAIN_R, 0x57);

    // Set Double Buffer
    ScalerSetBit(P6_D2_DA_GAIN_L, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : Audio DAC DC Off Set
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACDCOffSetState(bit bEnable)
{
    if(bEnable == _ON)
    {
        // Set DC off set 375uV for Right channel
        ScalerSetByte(P6_D7_DA_DC_OFFSET_R_MSB, 0x00);
        ScalerSetByte(P6_D8_DA_DC_OFFSET_R_LSB, 0xC5);

        // Set DC off set 375uV for Left channel
        ScalerSetByte(P6_D9_DA_DC_OFFSET_L_MSB, 0x00);
        ScalerSetByte(P6_DA_DA_DC_OFFSET_L_LSB, 0xC5);
    }
    else // DC Offset OFF
    {
        // Set DC off set 375uV for Right channel
        ScalerSetByte(P6_D7_DA_DC_OFFSET_R_MSB, 0x00);
        ScalerSetByte(P6_D8_DA_DC_OFFSET_R_LSB, 0x00);

        // Set DC off set 375uV for Left channel
        ScalerSetByte(P6_D9_DA_DC_OFFSET_L_MSB, 0x00);
        ScalerSetByte(P6_DA_DA_DC_OFFSET_L_LSB, 0x00);
    }
}

//--------------------------------------------------
// Description  : Control DAC Output Gain Control
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerAudioDACGainControl(bit bEnable)
{
    if(bEnable == _ON)
    {
#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        // Output > 0dB, DAC Amplifier Needs to be turned on
        if(GET_DAC_AOUT_GAIN_DB() != _AUDIO_DAC_OUTPUT_GAIN_0_DB)
        {
            // Enable AIO Gain
            ScalerSetBit(P6_C6_REG_DAC_CUR4, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
        else
        {
            // Diable AIO Gain
            ScalerSetBit(P6_C6_REG_DAC_CUR4, ~(_BIT7 | _BIT6), 0x00);
        }
#endif

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        // Output > 0dB, DAC Amplifier Needs to be turned on
        if(GET_DAC_HPOUT_GAIN_DB() != _AUDIO_DAC_OUTPUT_GAIN_0_DB)
        {
            // Enable HPO Gain
            ScalerSetBit(P6_C8_REG_DAC_CUR6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
        else
        {
            // Diable HPO Gain
            ScalerSetBit(P6_C8_REG_DAC_CUR6, ~(_BIT7 | _BIT6), 0x00);
        }
#endif
    }
    else
    {
#if(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
        // Diable AIO Gain
        ScalerSetBit(P6_C6_REG_DAC_CUR4, ~(_BIT7 | _BIT6), 0x00);
#endif

#if(_DAC_HP_OUTPUT_SUPPORT == _ON)
        // Diable HPO Gain
        ScalerSetBit(P6_C8_REG_DAC_CUR6, ~(_BIT7 | _BIT6), 0x00);
#endif
    }
}
#endif // End of #if(_EMBEDDED_DAC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)
