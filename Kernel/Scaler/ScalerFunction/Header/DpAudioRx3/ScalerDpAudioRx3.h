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
// ID Code      : ScalerDpAudioRx3.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_AUDIO_RX3_H__
#define __SCALER_DP_AUDIO_RX3_H__

#if(_DP_AUDIO_RX3_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_AUDIO_RX3_AUTO_LOAD_FREQ()           (g_stDpAudioRx3FreqParameter.b1AutoLoad)
#define SET_DP_AUDIO_RX3_AUTO_LOAD_FREQ()           (g_stDpAudioRx3FreqParameter.b1AutoLoad = _TRUE)
#define CLR_DP_AUDIO_RX3_AUTO_LOAD_FREQ()           (g_stDpAudioRx3FreqParameter.b1AutoLoad = _FALSE)

#define GET_DP_RX3_SAMPLING_FREQ_USER_DEFINE()      (g_stDpAudioRx3FreqParameter.enumFsManual)
#define SET_DP_RX3_SAMPLING_FREQ_USER_DEFINE(x)     (g_stDpAudioRx3FreqParameter.enumFsManual = (x))

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
#define GET_DP_RX3_SOURCE_SAMPLING_FREQ()           (g_stDpAudioRx3FreqParameter.enumFsSource)
#define SET_DP_RX3_SOURCE_SAMPLING_FREQ(x)          (g_stDpAudioRx3FreqParameter.enumFsSource = (x))

#define GET_DP_RX3_TARGET_SAMPLING_FREQ()           (g_stDpAudioRx3FreqParameter.enumFsTarget)
#define SET_DP_RX3_TARGET_SAMPLING_FREQ(x)          (g_stDpAudioRx3FreqParameter.enumFsTarget = (x))

#define GET_DP_RX3_SAMPLING_FREQ_LIMIT()            (g_stDpAudioRx3FreqParameter.enumFsLimit)
#define SET_DP_RX3_SAMPLING_FREQ_LIMIT(x)           (g_stDpAudioRx3FreqParameter.enumFsLimit = (x))

#define GET_DP_RX3_SAMPLING_FREQ_LIMIT_CONTROL()    (g_stDpAudioRx3FreqParameter.b1FreqLimitControl)
#define SET_DP_RX3_SAMPLING_FREQ_LIMIT_CONTROL()    (g_stDpAudioRx3FreqParameter.b1FreqLimitControl = _TRUE)
#define CLR_DP_RX3_SAMPLING_FREQ_LIMIT_CONTROL()    (g_stDpAudioRx3FreqParameter.b1FreqLimitControl = _FALSE)
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

#define GET_DP_RX3_AUDIO_CODING_TYPE_FORMAT()       (g_stDpAudioRx3CodingType.enumAudioCodingType)
#define SET_DP_RX3_AUDIO_CODING_TYPE_FORMAT(x)      (g_stDpAudioRx3CodingType.enumAudioCodingType = (x))

#define GET_DP_RX3_AUDIO_CODING_TYPE_CHANGE()       (g_stDpAudioRx3CodingType.b1AudioCodingTypeChange)
#define SET_DP_RX3_AUDIO_CODING_TYPE_CHANGE()       (g_stDpAudioRx3CodingType.b1AudioCodingTypeChange = _TRUE)
#define CLR_DP_RX3_AUDIO_CODING_TYPE_CHANGE()       (g_stDpAudioRx3CodingType.b1AudioCodingTypeChange = _FALSE)

#define GET_DP_RX3_AUDIO_SAMPLING_FREQ_CHANGE()     (g_stDpAudioRx3FreqParameter.b1SamplingFreqChange)
#define SET_DP_RX3_AUDIO_SAMPLING_FREQ_CHANGE()     (g_stDpAudioRx3FreqParameter.b1SamplingFreqChange = _TRUE)
#define CLR_DP_RX3_AUDIO_SAMPLING_FREQ_CHANGE()     (g_stDpAudioRx3FreqParameter.b1SamplingFreqChange = _FALSE)

#define GET_DP_AUDIO_RX3_HBR_RECEIVE_MODE_CHANGE()  (bit)(g_stDpAudioRx3HbrReceiveMode.b1HbrAudioModeChange)
#define SET_DP_AUDIO_RX3_HBR_RECEIVE_MODE_CHANGE()  (g_stDpAudioRx3HbrReceiveMode.b1HbrAudioModeChange = _TRUE)
#define CLR_DP_AUDIO_RX3_HBR_RECEIVE_MODE_CHANGE()  (g_stDpAudioRx3HbrReceiveMode.b1HbrAudioModeChange = _FALSE)

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
#define GET_DP_RX3_AUDIO_FSM_STATUS_BACKUP()        (bit)(g_stDpAudioRx3InternalGen.b1FsmBackup)
#define SET_DP_RX3_AUDIO_FSM_STATUS_BACKUP(x)       (g_stDpAudioRx3InternalGen.b1FsmBackup = (x))

#define GET_DP_RX3_AUDIO_FIFO_TRACKING_BACKUP()     (bit)(g_stDpAudioRx3InternalGen.b1FifoTrackingBackup)
#define SET_DP_RX3_AUDIO_FIFO_TRACKING_BACKUP(x)    (g_stDpAudioRx3InternalGen.b1FifoTrackingBackup = (x))
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructAudioFreqParameter g_stDpAudioRx3FreqParameter;
extern volatile StructAudioDpCodingType g_stDpAudioRx3CodingType;
extern volatile StructAudioDpHbrReceiveMode g_stDpAudioRx3HbrReceiveMode;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpAudioRx3SetDVCWindowSize(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket);
extern void ScalerDpAudioRx3SetDVCWindowSize_8b10b(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket);
extern void ScalerDpAudioRx3SetDVCVolumeAdjustType_8b10b(bit bAdjustType);
extern bit ScalerDpAudioRx3GetAudioDetected_8b10b(void);
extern bit ScalerDpAudioRx3LPCMCheckData_8b10b(void);
extern void ScalerDpAudioRx3LoadInitialICode(void);
extern void ScalerDpAudioRx3FifoTrackingInitial(void);
extern void ScalerDpAudioRx3FifoTrackingNFCodeConfig(DWORD ulNFCode);
extern void ScalerDpAudioRx3AudioInitial_8b10b(void);
extern void ScalerDpAudioRx3SetAudioPLL(void);
extern void ScalerDpAudioRx3SetAudioPLLOnProc(void);
extern void ScalerDpAudioRx3SetAudioPLLOffProc(void);
extern void ScalerDpAudioRx3WatchDogProc_8b10b(bit bOn);
extern void ScalerDpAudioRx3FifoTrackingEnableControl_8b10b(bit bEnable);
extern void ScalerDpAudioRx3FifoTrackingEnableControl_8b10b_EXINT0(bit bEnable);
extern void ScalerDpAudioRx3FifoTrackingProc(bit bEnable);
extern void ScalerDpAudioRx3FifoTrackingProc_8b10b(bit bEnable);
extern void ScalerDpAudioRx3FifoTrackingProc_8b10b_EXINT0(void);
extern void ScalerDpAudioRx3DisableSetting_8b10b_EXINT0(void);
extern void ScalerDpAudioRx3AudioFrequencyMode_8b10b(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
extern void ScalerDpAudioRx3AudioFrequencyMode_8b10b_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);

#if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)
extern void ScalerDpAudioRx3SetTargetAudioFrequency(EnumAudioSamplingFreqType enumAudioFreq);
#endif // End of #if(_AUDIO_OUTPUT_SAMPLING_FREQ_LIMIT_SUPPORT == _ON)

extern void ScalerDpAudioRx3HbrAudioDetect(EnumAudioSamplingFreqType enumAudioFreq);

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpAudioRx3AudioInitial_128b132b(void);
extern void ScalerDpAudioRx3SetDVCWindowSize_128b132b(bit bAdjustType, EnumAudioSamplingFreqPacket enumSamplingFreqPacket);
extern void ScalerDpAudioRx3SetDVCVolumeAdjustType_128b132b(bit bAdjustType);
extern bit ScalerDpAudioRx3GetAudioDetected_128b132b(void);
extern bit ScalerDpAudioRx3LPCMCheckData_128b132b(void);
extern void ScalerDpAudioRx3WatchDogProc_128b132b(bit bOn);
extern void ScalerDpAudioRx3FifoTrackingEnableControl_128b132b(bit bEnable);
extern void ScalerDpAudioRx3FifoTrackingEnableControl_128b132b_EXINT0(bit bEnable);
extern void ScalerDpAudioRx3FifoTrackingProc_128b132b(bit bEnable);
extern void ScalerDpAudioRx3FifoTrackingProc_128b132b_EXINT0(void);
extern void ScalerDpAudioRx3DisableSetting_128b132b_EXINT0(void);
extern void ScalerDpAudioRx3AudioFrequencyMode_128b132b(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
extern void ScalerDpAudioRx3AudioFrequencyMode_128b132b_EXINT0(EnumAudioFreqTrackingMode enumAudioFreqTrackingMode);
#endif // End of #if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif // End of #if(_DP_AUDIO_RX3_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_DP_AUDIO_RX3_H__

