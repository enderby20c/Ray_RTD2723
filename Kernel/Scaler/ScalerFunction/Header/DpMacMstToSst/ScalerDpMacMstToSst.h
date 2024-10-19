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
// ID Code      : ScalerDpMacMstToSst.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MAC_MST_TO_SST_H__
#define __SCALER_DP_MAC_MST_TO_SST_H__


#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)

#define GET_DP_MAC_MST2SST_AUDIO_STATUS()           (g_stDpMacMstToSstAudio.enumStatus)
#define SET_DP_MAC_MST2SST_AUDIO_STATUS(x)          (g_stDpMacMstToSstAudio.enumStatus = (x))

#define GET_DP_MAC_MST2SST_AUDIO_STATUS_CHANGE()    (g_stDpMacMstToSstAudio.b1Change)
#define SET_DP_MAC_MST2SST_AUDIO_STATUS_CHANGE()    (g_stDpMacMstToSstAudio.b1Change = _TRUE)
#define CLR_DP_MAC_MST2SST_AUDIO_STATUS_CHANGE()    (g_stDpMacMstToSstAudio.b1Change = _FALSE)

#endif // End of #if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)

#define GET_DP_MAC_MST2SST_STREAM_STATUS()          (g_stDpMacMstToSstStream.enumStatus)
#define SET_DP_MAC_MST2SST_STREAM_STATUS(x)         (g_stDpMacMstToSstStream.enumStatus = (x))

#define GET_DP_MAC_MST2SST_STREAM_STATUS_CHANGE()   (g_stDpMacMstToSstStream.b1Change)
#define SET_DP_MAC_MST2SST_STREAM_STATUS_CHANGE()   (g_stDpMacMstToSstStream.b1Change = _TRUE)
#define CLR_DP_MAC_MST2SST_STREAM_STATUS_CHANGE()   (g_stDpMacMstToSstStream.b1Change = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Struct for MST2SST Audio
//--------------------------------------------------
typedef struct
{
    EnumDpMacMstToSstAudioStatus enumStatus;
    BYTE b1Change : 1;
} StructMstToSstAudio;

//--------------------------------------------------
// Struct for MST2SST Stream
//--------------------------------------------------
typedef struct
{
    EnumDpMacMstToSstStreamStatus enumStatus;
    BYTE b1Change : 1;
} StructMstToSstStream;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)
extern StructMstToSstAudio g_stDpMacMstToSstAudio;
#endif // End of #if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)

extern StructMstToSstStream g_stDpMacMstToSstStream;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpMacMstToSstInitial(void);
extern void ScalerDpMacMstToSstStreamJudgeHandler(void);
extern void ScalerDpMacMstToSstStreamModeHandler(void);
extern void ScalerDpMacMstToSstStreamChangeState(EnumDpMacMstToSstStreamStatus enumStreamStatus);
extern EnumSourceType ScalerDpMacMstToSstScanInputPort(void);
extern bit ScalerDpMacMstToSstStableDetect(void);
extern bit ScalerDpMacMstToSst4MeasureInput(void);
extern bit ScalerDpMacMstToSstGetMsaTimingInfo(StructDpInfo *pstDpInfo);
extern void ScalerDpMacMstToSstPreDetectReset(void);
extern bit ScalerDpMacMstToSstGetVscSdpColorMode(void);
extern void ScalerDpMacMstToSstStreamInfoSetting(void);
extern void ScalerDpMacMstToSstSetBsMissDetectIRQ(bit bEn);

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern void ScalerDpMacMstToSstSetBsMissDetectPeriod(void);
#endif

#if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)
extern void ScalerDpMacMstToSstAudioJudgeHandler(void);
extern void ScalerDpMacMstToSstAudioModeHandler(void);
extern void ScalerDpMacMstToSstAudioDigitalProc(void);
extern void ScalerDpMacMstToSstAudioChangeState(EnumDpMacMstToSstAudioStatus enumAudioStatus);
extern void ScalerDpMacMstToSstDigitalAudioDetectProc(void);
extern bit ScalerDpMacMstToSstSamplingFreqDetect(void);
extern bit ScalerDpMacMstToSstGetAudioDetected(void);
extern void ScalerDpMacMstToSstSetAudioOutputMute(bit bMute);
extern void ScalerDpMacMstToSstWatchDogProc(bit bOn);
extern void ScalerDpMacMstToSstRsDecoderControl(bit bEnable);
extern void ScalerDpMacMstToSstAudioMuxControl(void);
#endif // End of #if(_DP_RX_MST2SST_AUDIO_SUPPORT == _ON)
#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))


#endif // End of #ifndef __SCALER_DP_MAC_MST_TO_SST_H__
