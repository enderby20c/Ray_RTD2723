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
// ID Code      : ScalerHdmiArcTx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_HDMI_ARC_TX_H__
#define __SCALER_HDMI_ARC_TX_H__

#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_HDMI_ARC_TX_OSD_CHANNEL_NUM()                             (g_enumHdmiArcTxOsdChannelNum)

#define GET_HDMI_ARC_TX_SOURCE_SAMPLING_FREQ()                        (g_stHdmiArcTxAudioSourceInfo.enumAudioFs)

#define GET_HDMI_ARC_TX_SOURCE_CHANNEL_NUM()                          (g_stHdmiArcTxAudioSourceInfo.enumAudioChannelCount)

#define GET_HDMI_ARC_TX_SOURCE_CODING_TYPE()                          (g_stHdmiArcTxAudioSourceInfo.enumAudioCodingType)

#define GET_HDMI_ARC_TX_SOURCE_WORD_LENGTH()                          (g_stHdmiArcTxAudioSourceInfo.ucAudioChStatusByte4 & 0x0F)

#define GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB4()                  (g_stHdmiArcTxAudioSourceInfo.ucAudioInfoPb4)
#define GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB5()                  (g_stHdmiArcTxAudioSourceInfo.ucAudioInfoPb5)
#define GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB6()                  (g_stHdmiArcTxAudioSourceInfo.ucAudioInfoPb6)
#define GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB7()                  (g_stHdmiArcTxAudioSourceInfo.ucAudioInfoPb7)
#define GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB8()                  (g_stHdmiArcTxAudioSourceInfo.ucAudioInfoPb8)
#define GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB9()                  (g_stHdmiArcTxAudioSourceInfo.ucAudioInfoPb9)
#define GET_HDMI_ARC_TX_SOURCE_AUDIO_INFOFRAME_PB10()                 (g_stHdmiArcTxAudioSourceInfo.ucAudioInfoPb10)

#define GET_HDMI_ARC_TX_SOURCE_AUDIO_CH_STATUS_BYTE0()                (g_stHdmiArcTxAudioSourceInfo.ucAudioChStatusByte0)
#define GET_HDMI_ARC_TX_SOURCE_AUDIO_CH_STATUS_BYTE1()                (g_stHdmiArcTxAudioSourceInfo.ucAudioChStatusByte1)
#define GET_HDMI_ARC_TX_SOURCE_AUDIO_CH_STATUS_BYTE2()                (g_stHdmiArcTxAudioSourceInfo.ucAudioChStatusByte2)
#define GET_HDMI_ARC_TX_SOURCE_AUDIO_CH_STATUS_BYTE3()                (g_stHdmiArcTxAudioSourceInfo.ucAudioChStatusByte3)
#define GET_HDMI_ARC_TX_SOURCE_AUDIO_CH_STATUS_BYTE4()                (g_stHdmiArcTxAudioSourceInfo.ucAudioChStatusByte4)

#define GET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE()                    (g_stHdmiArcTxCtrlInfo.enumAudioOutLayout)
#define SET_HDMI_ARC_TX_AUDIO_OUTPUT_LAYOUT_TYPE(x)                   (g_stHdmiArcTxCtrlInfo.enumAudioOutLayout = (x))

#define GET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM()                    (g_stHdmiArcTxCtrlInfo.enumAudioOutChannelNum)
#define SET_HDMI_ARC_TX_AUDIO_OUTPUT_CHANNEL_NUM(x)                   (g_stHdmiArcTxCtrlInfo.enumAudioOutChannelNum = (x))

#define GET_HDMI_ARC_TX_AUDIO_OUTPUT_CODING_TYPE()                    (g_stHdmiArcTxCtrlInfo.enumAudioOutCodingType)
#define SET_HDMI_ARC_TX_AUDIO_OUTPUT_CODING_TYPE(x)                   (g_stHdmiArcTxCtrlInfo.enumAudioOutCodingType = (x))

#define GET_HDMI_ARC_TX_AUDIO_OUTPUT_WORD_LENGTH()                    (g_stHdmiArcTxCtrlInfo.ucAudioOutWordLength)
#define SET_HDMI_ARC_TX_AUDIO_OUTPUT_WORD_LENGTH(x)                   (g_stHdmiArcTxCtrlInfo.ucAudioOutWordLength = (x))

#define GET_HDMI_ARC_TX_LINK_MODE()                                   (g_stHdmiArcTxCtrlInfo.enumArcLinkMode)
#define SET_HDMI_ARC_TX_LINK_MODE(x)                                  (g_stHdmiArcTxCtrlInfo.enumArcLinkMode = (x))

#define _COMPRESSED_B_LAYOUT_SUPPORT                                  _ON

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerHdmiArcTxPowerOff(void);
extern void ScalerHdmiArcTxReset(void);
extern void ScalerHdmiArcTxSpdifInputConverterInitial(void);
extern EnumAudioSamplingFreqPacket ScalerHdmiArcTxAudioSamplingFreqMulti4(EnumAudioSamplingFreqPacket enumAudioFreq);
extern EnumAudioSamplingFreqPacket ScalerHdmiArcTxAudioSamplingFreqDiv4(EnumAudioSamplingFreqPacket enumAudioFreq);
extern void ScalerHdmiArcTxSetAudioOutputConfig(void);
extern bit ScalerHdmiArcTxMonitorFifoStatus(void);
extern bit ScalerHdmiArcTxSetMnTracking(void);
extern void ScalerHdmiArcTxFirstSetPiCode(void);
extern void ScalerHdmiArcTxSecondSetPiCode(void);
extern void ScalerHdmiArcTxEnableMnTracking(void);
extern bit ScalerHdmiArcTxMonitorPhaseError(void);
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
extern void ScalerHdmiArcTxEarcLoadChannelStatus(void);
extern bit ScalerHdmiArcTxEarcAudioLatencyReload(BYTE *pucAudioLatency);
#endif // End of #if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
#endif // End of #if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_HDMI_ARC_TX_H__
