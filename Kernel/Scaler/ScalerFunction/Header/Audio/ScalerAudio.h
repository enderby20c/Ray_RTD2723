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
// ID Code      : ScalerAudio.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_AUDIO_H__
#define __SCALER_AUDIO_H__

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Audio ADC Frequency Paramater
//--------------------------------------------------
#define _AUDIO_PLL_IN_EXT_XTAL_CLK                  0x40

#define _AUDIO_PLL_OUT_DIV_1                        0
#define _AUDIO_PLL_OUT_DIV_2                        1
#define _AUDIO_PLL_OUT_DIV_4                        2
#define _AUDIO_PLL_OUT_DIV_6                        3
#define _AUDIO_PLL_OUT_DIV_8                        4
#define _AUDIO_PLL_OUT_DIV_10                       5
#define _AUDIO_PLL_OUT_DIV_12                       6
#define _AUDIO_PLL_OUT_DIV_14                       7

#define _AUDIO_PLL_O_DIV_1                          0
#define _AUDIO_PLL_O_DIV_2                          1
#define _AUDIO_PLL_O_DIV_4                          2
#define _AUDIO_PLL_O_DIV_8                          3

#define _AUDIO_PLL_OUT_DIV                          _AUDIO_PLL_OUT_DIV_8 // PageBF 0xA2[2:0]
#define _AUDIO_PLL_PREDIVIDER_BPN                   _ENABLE              // PageBF 0xA5[7]
#define _AUDIO_PLL_PREDIVIDER_N                     (0 + 2)              // PageBF 0xA4[7:0] default value = 0x00
#define _AUDIO_PLL_O_DIV                            _AUDIO_PLL_O_DIV_4   // PageBF 0xA5[1:0] default value = 0x00

//--------------------------------------------------
// Macros of Audio Internal Gen
//--------------------------------------------------
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
#if(_INTERNAL_AUDIO_TEST_FIX_AUDIO_OUTPUT == _ON)
#define GET_AUDIO_INTERNAL_GEN_ENABLE_STATE()       (bit)(g_bAudioInternalGenEnable)
#define SET_AUDIO_INTERNAL_GEN_ENABLE_STATE(x)      (g_bAudioInternalGenEnable = (x))
#endif
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Audio Sampling Frequency in SPDIF Format
//--------------------------------------------------
typedef enum
{
    _AUDIO_SPDIF_FS_22_05KHZ = _BIT2,
    _AUDIO_SPDIF_FS_24KHZ = (_BIT2 | _BIT1),
    _AUDIO_SPDIF_FS_32KHZ = (_BIT1 | _BIT0),
    _AUDIO_SPDIF_FS_44_1KHZ = 0x00,
    _AUDIO_SPDIF_FS_48KHZ = _BIT1,
    _AUDIO_SPDIF_FS_88_2KHZ = _BIT3,
    _AUDIO_SPDIF_FS_96KHZ = (_BIT3 | _BIT1),
    _AUDIO_SPDIF_FS_176_4KHZ = (_BIT3 | _BIT2),
    _AUDIO_SPDIF_FS_192KHZ = (_BIT3 | _BIT2 | _BIT1),
    _AUDIO_SPDIF_FS_NOT_INDICATED = _BIT0,
} EnumAudioSpdifSamplingFrequencyType;

//--------------------------------------------------
// Enumerations of Audio ADC Input Buffer Gain Control
//--------------------------------------------------
typedef enum
{
    _AUDIO_INPUT_BUFFER_ADC_PATH = 0x00,
    _AUDIO_INPUT_BUFFER_AA_PATH,
} EnumAudioInputBufferGainControl;

//--------------------------------------------------
// Enumerations of AIO & HPO DF2SE Input Mux Mode Control
//--------------------------------------------------
typedef enum
{
    _AUDIO_MUTE_PATH = 0x00,
    _AUDIO_RDAC_LDAC_SWAP,
    _AUDIO_DEBUG_PATH,
    _AUDIO_DAC_MODE_PATH,
} EnumAudioDF2SEMUXControl;

//--------------------------------------------------
// Enumerations of Switch DAC AIO & HPO For Depop/Normal Mode
//--------------------------------------------------
typedef enum
{
    _AUDIO_NONE_MODE = 0x00,
    _AUDIO_DAC_DEPOP_MODE,
    _AUDIO_DAC_NORMAL_MODE,
} EnumAudioDACDepopModeControl;

//--------------------------------------------------
// Enumerations of Control HPO Power MOS
//--------------------------------------------------
typedef enum
{
    _AUDIO_POWER_MOS_STATUS_INITIAL = 0x00,
    _AUDIO_POWER_MOS_STATUS_NORMAL,
    _AUDIO_POWER_MOS_STATUS_FAST,
    _AUDIO_POWER_MOS_STATUS_SUPERFAST,
} EnumAudioDACHPOPowerMOSControl;

//--------------------------------------------------
// Enumerations of Control Audio Output Control
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OUTPUT_NONE_PATH = 0x00,
    _AUDIO_DAC_OUTPUT_DAC_PATH,
    _AUDIO_DAC_OUTPUT_AA_PATH,
} EnumAudioDACOutputControl;

//--------------------------------------------------
// Enumerations of Control DAC HPO Mode Select
//--------------------------------------------------
typedef enum
{
    _AUDIO_HPO_32_OHM_MODE = 0x00,
    _AUDIO_HPO_10K_OHM_MODE,
} EnumAudioDACHPOModeControl;

//--------------------------------------------------
// Enumerations of Select DAC Output Type AIO & HPO Path
//--------------------------------------------------
typedef enum
{
    _AUDIO_AIO_MODE = 0x00,
    _AUDIO_HPO_MODE,
    _AUDIO_AIO_HPO_MODE,
} EnumAudioDACAIOHPOPATHControl;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerAudioDigitalAudioInitial(void);

extern void ScalerAudioDisableAudioPLL(void);
extern void ScalerAudioInputPortSwitch(EnumAudioInputPort enumAudioInput);
extern EnumAudioInputPort ScalerAudioGetDigitalAudioPort_EXINT0(EnumAudioOutputType enumAudioOutput);
extern EnumAudioInputPort ScalerAudioDxToRxMapping_EXINT0(EnumInputPort enumInputPort, EnumAudioPortMapType enumAudioPortMapType);
extern void ScalerAudioDVCInitial(void);
extern void ScalerAudioDVCVolumeAdjustType(bit bAdjustType);

#if(_AUDIO_DVC_FAST_CONTROL_SUPPORT == _ON)
extern void ScalerAudioDVCVolumeFastAdjustType(bit bAdjustType);
#endif

extern void ScalerAudioDVCVolumeMute(bit bMute, WORD usVolume);

extern void ScalerAudioDVCSetMuteZCDTimeout(bit bMute, WORD usVolume, bit bAdjustType, WORD usTimeout);
extern void ScalerAudioDVCSetVolumeZCDTimeout(WORD usVolume);
extern void ScalerAudioHbrModeControl(bit bOn, EnumInputPort enumInputPort, EnumAudioOutputType enumAudioOutput);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
extern void ScalerAudioResetSamplingFreqLimitProc(EnumInputPort enumInputPort, EnumAudioOutputType enumAudioOutput);
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

extern void ScalerAudioDACSoftReset(void);
extern void ScalerAudioClockGatingControl(bit bEnable);
extern void ScalerAudioADCDigitalOutputSetting(void);
extern void ScalerAudioSetInputSource(EnumAudioInputSource enumAudioInputSource);
extern void ScalerAudioSettingAAPathMode(void);
extern void ScalerAudioChargeVrefFastControl(bit bEnable);
extern void ScalerAudioChargeVrefControl(bit bEnable);
extern void ScalerAudioDACDepopModeStatus(bit bEnable);
extern void ScalerAudioDACPowerControl(bit bEnable);
extern void ScalerAudioDACUsePowerControl(bit bEnable);
extern void ScalerAudioDACOutputControl(EnumAudioDACOutputControl enumAudioDACOutputControl);
extern void ScalerAudioDACDF2SEInputMux(EnumAudioDACAIOHPOPATHControl enumAudioDACAIOHPOPATHControl, EnumAudioDF2SEMUXControl enumDF2SEControl);

#if(_LINE_IN_SUPPORT == _ON)
extern void ScalerAudioADCDACSoftReset(void);
extern void ScalerAudioADCADGainSetting(void);
extern void ScalerAudioSetADCAudioPLL(void);
extern void ScalerAudioSetADCAudioPLLOnProc(void);
extern void ScalerAudioSetADCAudioPLLOffProc(void);
extern void ScalerAudioADCPowerControl(bit bEnable);
extern void ScalerAudioADCInputbufferGain(EnumAudioInputBufferGainControl enumGainControl);
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern void ScalerAudioDACAIOHPOPowerControl(bit bEnable);
extern void ScalerAudioDACSetOutputGain(EnumAudioDACOutput enumOutputType, EnumAudioDacOutputGain enumOutputGain);
extern void ScalerAudioDACHPOModeControl(EnumAudioDACHPOModeControl enumAudioDACHPOModeControl);
extern void ScalerAudioDACDepopModeControl(EnumAudioDACDepopModeControl enumAudioDACDepopModeControl);
extern void ScalerAudioDACOutputGainInitial(void);
extern void ScalerAudioDACDigitalVolumeSetting(void);
extern void ScalerAudioDACHPOPowerMOSControl(EnumAudioDACHPOPowerMOSControl enumPowerMosStatus);
extern void ScalerAudioDACDCOffSetState(bit bEnable);
extern void ScalerAudioDACGainControl(bit bEnable);
#endif

#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
extern void ScalerAudioSpdifCheckIfSamplingFrequencyChange(EnumInputPort enumInputPort);
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
extern BYTE ScalerAudioGetArcAudioInfo(EnumAudioInfoContent enumAudioInfoContent);
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_AUDIO_H__
