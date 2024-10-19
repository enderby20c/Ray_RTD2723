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
// ID Code      : ScalerHdmiArcTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_HDMI_ARC_TX_OSD_ARC_MODE()                                             (g_enumHdmiArcTxOsdArcMode)

#define GET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ()                               (g_stHdmiArcTxCtrlInfo.enumAudioOutSamplingFreq)
#define SET_HDMI_ARC_TX_AUDIO_OUTPUT_SAMPLING_FREQ(x)                              (g_stHdmiArcTxCtrlInfo.enumAudioOutSamplingFreq = (x))

#define GET_HDMI_ARC_TX_SOURCE_CH_STATUS_CHANGE_EVENT()                            (g_stHdmiArcTxCtrlInfo.ucChStatusChangeEvent != _FALSE)
#define SET_HDMI_ARC_TX_SOURCE_CH_STATUS_CHANGE_EVENT()                            (g_stHdmiArcTxCtrlInfo.ucChStatusChangeEvent = _TRUE)
#define CLR_HDMI_ARC_TX_SOURCE_CH_STATUS_CHANGE_EVENT()                            (g_stHdmiArcTxCtrlInfo.ucChStatusChangeEvent = _FALSE)

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
//--------------------------------------------------
// Macro of eARC Rx Discovery Event
//--------------------------------------------------
#define GET_HDMI_ARC_TX_EARC_DISCOVERY_EVENT()                                     (g_stHdmiArcTxCtrlInfo.ucEarcDiscoveryEvent != _FALSE)
#define SET_HDMI_ARC_TX_EARC_DISCOVERY_EVENT()                                     (g_stHdmiArcTxCtrlInfo.ucEarcDiscoveryEvent = _TRUE)
#define CLR_HDMI_ARC_TX_EARC_DISCOVERY_EVENT()                                     (g_stHdmiArcTxCtrlInfo.ucEarcDiscoveryEvent = _FALSE)

#define GET_HDMI_ARC_TX_EARC_LOST_HEARTBEAT_EVENT()                                (g_stHdmiArcTxCtrlInfo.ucEarcLostHeartbeatEvent != _FALSE)
#define SET_HDMI_ARC_TX_EARC_LOST_HEARTBEAT_EVENT()                                (g_stHdmiArcTxCtrlInfo.ucEarcLostHeartbeatEvent = _TRUE)
#define CLR_HDMI_ARC_TX_EARC_LOST_HEARTBEAT_EVENT()                                (g_stHdmiArcTxCtrlInfo.ucEarcLostHeartbeatEvent = _FALSE)

#define GET_HDMI_ARC_TX_EARC_DISC_TIMEOUT_EVENT()                                  (g_stHdmiArcTxCtrlInfo.ucEarcDiscTimeoutEvent != _FALSE)
#define SET_HDMI_ARC_TX_EARC_DISC_TIMEOUT_EVENT()                                  (g_stHdmiArcTxCtrlInfo.ucEarcDiscTimeoutEvent = _TRUE)
#define CLR_HDMI_ARC_TX_EARC_DISC_TIMEOUT_EVENT()                                  (g_stHdmiArcTxCtrlInfo.ucEarcDiscTimeoutEvent = _FALSE)

#define GET_HDMI_ARC_TX_EARC_AUDIO_LATENCY_CHANGE_EVENT()                          (g_stHdmiArcTxCtrlInfo.ucEarcAudioLatencyChangeEvent != _FALSE)
#define SET_HDMI_ARC_TX_EARC_AUDIO_LATENCY_CHANGE_EVENT()                          (g_stHdmiArcTxCtrlInfo.ucEarcAudioLatencyChangeEvent = _TRUE)
#define CLR_HDMI_ARC_TX_EARC_AUDIO_LATENCY_CHANGE_EVENT()                          (g_stHdmiArcTxCtrlInfo.ucEarcAudioLatencyChangeEvent = _FALSE)

#define GET_HDMI_ARC_TX_EARC_CDS_CHANGE_EVENT()                                    (g_stHdmiArcTxCtrlInfo.ucEarcCdsChangeEvent != _FALSE)
#define SET_HDMI_ARC_TX_EARC_CDS_CHANGE_EVENT()                                    (g_stHdmiArcTxCtrlInfo.ucEarcCdsChangeEvent = _TRUE)
#define CLR_HDMI_ARC_TX_EARC_CDS_CHANGE_EVENT()                                    (g_stHdmiArcTxCtrlInfo.ucEarcCdsChangeEvent = _FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Struct of HDMI eARC Tx Ctrl Info
//--------------------------------------------------
typedef struct
{
    BYTE ucChStatusChangeEvent;
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
    BYTE ucEarcDiscoveryEvent;
    BYTE ucEarcLostHeartbeatEvent;
    BYTE ucEarcDiscTimeoutEvent;
    BYTE ucEarcAudioLatencyChangeEvent;
    BYTE ucEarcCdsChangeEvent;
#endif
    BYTE ucAudioOutWordLength;
    EnumArcAudioLayoutType enumAudioOutLayout;
    EnumAudioSamplingFreqPacket enumAudioOutSamplingFreq;
    EnumAudioChannelCount enumAudioOutChannelNum;
    EnumAudioCodingType enumAudioOutCodingType;
    EnumAudioArcMode enumArcLinkMode;
} StructHdmiArcTxCtrlInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructHdmiArcTxCtrlInfo g_stHdmiArcTxCtrlInfo;
extern EnumAudioArcMode g_enumHdmiArcTxOsdArcMode;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
extern void ScalerHdmiArcTxEarcSetHbHpdStatus(BYTE ucValue);
extern void ScalerHdmiArcTxInitial(void);

extern void ScalerHdmiArcTxEarcStartDiscovery_EXINT0(void);
extern void ScalerHdmiArcTxEarcResetDiscovery_EXINT0(void);
#endif // End of #if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
#endif // End of #if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
