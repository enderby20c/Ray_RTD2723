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
// ID Code      : ScalerDpAudioRx1.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_AUDIO_RX1_H__
#define __SCALER_DP_AUDIO_RX1_H__

#if(_DP_AUDIO_RX1_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_AUDIO_RX1_AUTO_LOAD_FREQ()           (g_stDpAudioRx1FreqParameter.b1AutoLoad)
#define SET_DP_AUDIO_RX1_AUTO_LOAD_FREQ()           (g_stDpAudioRx1FreqParameter.b1AutoLoad = _TRUE)
#define CLR_DP_AUDIO_RX1_AUTO_LOAD_FREQ()           (g_stDpAudioRx1FreqParameter.b1AutoLoad = _FALSE)

#define GET_DP_RX1_SAMPLING_FREQ_USER_DEFINE()      (g_stDpAudioRx1FreqParameter.enumFsManual)
#define SET_DP_RX1_SAMPLING_FREQ_USER_DEFINE(x)     (g_stDpAudioRx1FreqParameter.enumFsManual = (x))

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
#define GET_DP_RX1_SOURCE_SAMPLING_FREQ()           (g_stDpAudioRx1FreqParameter.enumFsSource)
#define SET_DP_RX1_SOURCE_SAMPLING_FREQ(x)          (g_stDpAudioRx1FreqParameter.enumFsSource = (x))

#define GET_DP_RX1_TARGET_SAMPLING_FREQ()           (g_stDpAudioRx1FreqParameter.enumFsTarget)
#define SET_DP_RX1_TARGET_SAMPLING_FREQ(x)          (g_stDpAudioRx1FreqParameter.enumFsTarget = (x))

#define GET_DP_RX1_SAMPLING_FREQ_LIMIT()            (g_stDpAudioRx1FreqParameter.enumFsLimit)
#define SET_DP_RX1_SAMPLING_FREQ_LIMIT(x)           (g_stDpAudioRx1FreqParameter.enumFsLimit = (x))

#define GET_DP_RX1_SAMPLING_FREQ_LIMIT_CONTROL()    (g_stDpAudioRx1FreqParameter.b1FreqLimitControl)
#define SET_DP_RX1_SAMPLING_FREQ_LIMIT_CONTROL()    (g_stDpAudioRx1FreqParameter.b1FreqLimitControl = _TRUE)
#define CLR_DP_RX1_SAMPLING_FREQ_LIMIT_CONTROL()    (g_stDpAudioRx1FreqParameter.b1FreqLimitControl = _FALSE)
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

#define GET_DP_RX1_AUDIO_CODING_TYPE_FORMAT()       (g_stDpAudioRx1CodingType.enumAudioCodingType)
#define SET_DP_RX1_AUDIO_CODING_TYPE_FORMAT(x)      (g_stDpAudioRx1CodingType.enumAudioCodingType = (x))

#define GET_DP_RX1_AUDIO_CODING_TYPE_CHANGE()       (g_stDpAudioRx1CodingType.b1AudioCodingTypeChange)
#define SET_DP_RX1_AUDIO_CODING_TYPE_CHANGE()       (g_stDpAudioRx1CodingType.b1AudioCodingTypeChange = _TRUE)
#define CLR_DP_RX1_AUDIO_CODING_TYPE_CHANGE()       (g_stDpAudioRx1CodingType.b1AudioCodingTypeChange = _FALSE)

#define GET_DP_RX1_AUDIO_SAMPLING_FREQ_CHANGE()     (g_stDpAudioRx1FreqParameter.b1SamplingFreqChange)
#define SET_DP_RX1_AUDIO_SAMPLING_FREQ_CHANGE()     (g_stDpAudioRx1FreqParameter.b1SamplingFreqChange = _TRUE)
#define CLR_DP_RX1_AUDIO_SAMPLING_FREQ_CHANGE()     (g_stDpAudioRx1FreqParameter.b1SamplingFreqChange = _FALSE)

#define GET_DP_AUDIO_RX1_HBR_RECEIVE_MODE_CHANGE()  (bit)(g_stDpAudioRx1HbrReceiveMode.b1HbrAudioModeChange)
#define SET_DP_AUDIO_RX1_HBR_RECEIVE_MODE_CHANGE()  (g_stDpAudioRx1HbrReceiveMode.b1HbrAudioModeChange = _TRUE)
#define CLR_DP_AUDIO_RX1_HBR_RECEIVE_MODE_CHANGE()  (g_stDpAudioRx1HbrReceiveMode.b1HbrAudioModeChange = _FALSE)

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
#define GET_DP_RX1_AUDIO_FSM_STATUS_BACKUP()        (bit)(g_stDpAudioRx1InternalGen.b1FsmBackup)
#define SET_DP_RX1_AUDIO_FSM_STATUS_BACKUP(x)       (g_stDpAudioRx1InternalGen.b1FsmBackup = (x))

#define GET_DP_RX1_AUDIO_FIFO_TRACKING_BACKUP()     (bit)(g_stDpAudioRx1InternalGen.b1FifoTrackingBackup)
#define SET_DP_RX1_AUDIO_FIFO_TRACKING_BACKUP(x)    (g_stDpAudioRx1InternalGen.b1FifoTrackingBackup = (x))
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructAudioFreqParameter g_stDpAudioRx1FreqParameter;
extern volatile StructAudioDpCodingType g_stDpAudioRx1CodingType;
extern volatile StructAudioDpHbrReceiveMode g_stDpAudioRx1HbrReceiveMode;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpAudioRx1SetDVCWindowSize(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket);
extern void ScalerDpAudioRx1SetDVCWindowSize_8b10b(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket);
extern void ScalerDpAudioRx1SetDVCVolumeAdjustType_8b10b(bit bAdjustType);
extern bit ScalerDpAudioRx1GetAudioDetected_8b10b(void);
extern bit ScalerDpAudioRx1LPCMCheckData_8b10b(void);
extern void ScalerDpAudioRx1LoadInitialICode(void);
extern void ScalerDpAudioRx1FifoTrackingInitial(void);
extern void ScalerDpAudioRx1FifoTrackingNFCodeConfig(DWORD ulNFCode);
extern void ScalerDpAudioRx1AudioInitial_8b10b(void);
extern void ScalerDpAudioRx1SetAudioPLL(void);
extern void ScalerDpAudioRx1SetAudioPLLOnProc(void);
extern void ScalerDpAudioRx1SetAudioPLLOffProc(void);
extern void ScalerDpAudioRx1WatchDogProc_8b10b(bit bOn);
extern void ScalerDpAudioRx1FifoTrackingEnableControl_8b10b(bit bEnable);
extern void ScalerDpAudioRx1FifoTrackingEnableControl_8b10b_EXINT0(bit bEnable);
extern void ScalerDpAudioRx1FifoTrackingProc(bit bEnable);
extern void ScalerDpAudioRx1FifoTrackingProc_8b10b(bit bEnable);
extern void ScalerDpAudioRx1FifoTrackingProc_8b10b_EXINT0(void);
extern void ScalerDpAudioRx1DisableSetting_8b10b_EXINT0(void);
extern void ScalerDpAudioRx1AudioFrequencyMode_8b10b(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
extern void ScalerDpAudioRx1AudioFrequencyMode_8b10b_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
extern void ScalerDpAudioRx1SetTargetAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq);
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

extern void ScalerDpAudioRx1HbrAudioDetect(EnumAudioSamplingFreqType enumAudioFreq);

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpAudioRx1AudioInitial_128b132b(void);
extern void ScalerDpAudioRx1SetDVCWindowSize_128b132b(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket);
extern void ScalerDpAudioRx1SetDVCVolumeAdjustType_128b132b(bit bAdjustType);
extern bit ScalerDpAudioRx1GetAudioDetected_128b132b(void);
extern bit ScalerDpAudioRx1LPCMCheckData_128b132b(void);
extern void ScalerDpAudioRx1WatchDogProc_128b132b(bit bOn);
extern void ScalerDpAudioRx1FifoTrackingEnableControl_128b132b(bit bEnable);
extern void ScalerDpAudioRx1FifoTrackingEnableControl_128b132b_EXINT0(bit bEnable);
extern void ScalerDpAudioRx1FifoTrackingProc_128b132b(bit bEnable);
extern void ScalerDpAudioRx1FifoTrackingProc_128b132b_EXINT0(void);
extern void ScalerDpAudioRx1DisableSetting_128b132b_EXINT0(void);
extern void ScalerDpAudioRx1AudioFrequencyMode_128b132b(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
extern void ScalerDpAudioRx1AudioFrequencyMode_128b132b_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#endif // End of #if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif // End of #if(_DP_AUDIO_RX1_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_DP_AUDIO_RX1_H__

