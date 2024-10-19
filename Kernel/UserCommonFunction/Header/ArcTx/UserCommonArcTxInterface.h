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
// ID Code      : UserCommonArcTxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_ARC_SUPPORT == _ON)
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
extern void UserCommonArcTxHandler(void);
extern bit UserCommonArcTxEdidModify(BYTE *pucEdidAddr, WORD *pusCtaDataBlockAddr);

#if(_AUDIO_EARC_SUPPORT == _ON)
extern bit UserCommonArcTxEarcGetInitiatePermission(void);
extern bit UserCommonArcTxEarcGetDowngradeToArcPermission(void);
extern void UserCommonArcTxEarcCdsParseDoneNotify(void);
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)

#if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
extern void UserCommonArcTxMuteProc(bit bMute);
extern void UserCommonArcTxArcModeInitial(void);
extern void UserCommonArcTxArcModeOutputReset(void);
extern void UserCommonArcTxAudioOutputFormatSetting(EnumArcAudioChanelStatus enumArcOsdChannelNum, StructAudioInterfaceInfoForArc stArcAudioSourceInfo);
extern bit UserCommonArcTxStreamHandler(void);
extern bit UserCommonArcTxStableDetect(void);
extern void UserCommonArcTxInitial(EnumAudioArcMode enumArcMode);
extern void UserCommonArcTxDisable(void);
extern void UserCommonArcTxOsdChangeProc(EnumAudioArcMode enumArcMode);

#if(_AUDIO_EARC_SUPPORT == _ON)
extern void UserCommonArcTxEarcModeOutputReset(void);
extern bit UserCommonArcTxEarcCheckDiscoveryPass(void);
extern bit UserCommonArcTxEarcCheckDiscoveryTimeout(void);
extern bit UserCommonArcTxEarcStreamHandler(void);
extern bit UserCommonArcTxEarcCheckAudioLatencyUpdate(BYTE *pucAudioLatency);
extern bit UserCommonArcTxEarcSetRequestAudioLatency(BYTE ucAudioLatency);
extern bit UserCommonArcTxEarcCheckCdsUpdate(void);
extern bit UserCommonArcTxEarcCdsReload(BYTE *pucEarcRxCdsTable);
extern void UserCommonArcTxEarcSetChStatusMuteFlag(EnumAudioMuteStatus enumArcMute);
extern EnumAudioMuteStatus UserCommonArcTxEarcGetChStatusMuteFlag(void);
#endif // End of #if(_AUDIO_EARC_SUPPORT == _ON)
#endif // End of #if(_AUDIO_ARC_TX_SUPPORT_TYPE == _AUDIO_ARC_TX_EXTERNAL_DEVICE)
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)