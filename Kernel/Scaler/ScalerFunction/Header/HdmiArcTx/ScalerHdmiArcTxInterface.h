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
// ID Code      : ScalerHdmiArcTxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerHdmiArcTxDisable(void);
extern void ScalerHdmiArcTxArcModeInitial(void);
extern void ScalerHdmiArcTxArcModeOutputReset(void);
extern void ScalerHdmiArcTxAudioOutputFormatSetting(EnumArcAudioChanelStatus enumArcOsdChannelNum, StructAudioInterfaceInfoForArc stArcAudioSourceInfo);
extern bit ScalerHdmiArcTxStreamHandler(void);
extern bit ScalerHdmiArcTxStableDetect(void);
extern void ScalerHdmiArcTxMuteProc(bit bMute);
extern void ScalerHdmiArcTxPowerOnInitial(EnumAudioArcMode enumArcMode);
extern void ScalerHdmiArcTxOsdChangeProc(EnumAudioArcMode enumArcMode);

extern void ScalerHdmiArcTxHighIntHandler_EXINT0(EnumPowerStatus enumPowerStatus);
extern void ScalerHdmiArcTxLowIntHandler_EXINT0(EnumPowerStatus enumPowerStatus);

#if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
extern void ScalerHdmiArcTxEarcModeOutputReset(void);
extern bit ScalerHdmiArcTxEarcCheckDiscoveryPass(void);
extern bit ScalerHdmiArcTxEarcCheckDiscoveryTimeout(void);
extern bit ScalerHdmiArcTxEarcStreamHandler(void);
extern bit ScalerHdmiArcTxEarcCheckAudioLatencyUpdate(BYTE *pucAudioLatency);
extern bit ScalerHdmiArcTxEarcSetRequestAudioLatency(BYTE ucAudioLatency);
extern bit ScalerHdmiArcTxEarcCheckCdsUpdate(void);
extern bit ScalerHdmiArcTxEarcCdsReload(BYTE *pucEarcRxCdsTable);
extern void ScalerHdmiArcTxEarcSetChStatusMuteFlag(EnumAudioMuteStatus enumArcMute);
extern EnumAudioMuteStatus ScalerHdmiArcTxEarcGetChStatusMuteFlag(void);
#endif // End of #if(_HDMI_EARC_TX_MAC_SUPPORT == _ON)
#endif // End of #if(_HDMI_ARC_TX_MAC_SUPPORT == _ON)
