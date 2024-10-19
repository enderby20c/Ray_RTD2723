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
// ID Code      : ScalerDpMacTx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MAC_TX_H__
#define __SCALER_DP_MAC_TX_H__


#if(_DP_MAC_TX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DP_SHA1_INPUT_SIZE                         _DP_HDCP_SHA1_INPUT_SIZE

#define _DP_TX_SST_TU_SIZE                          32

#define GET_DP_TX_SDP_DECODE_TYPE()                 (g_enumDpMacTxSdpDecodeType)

#define SET_DP_TX_SDP_DECODE_TYPE(x)                {\
                                                        g_enumDpMacTxSdpDecodeType |= (x);\
                                                        ScalerSetBit(PBC_96_DUMMY_96, ~(_DP_TX_SDP_DECODE_ALL), g_enumDpMacTxSdpDecodeType);\
                                                        ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, PBC_96_DUMMY_96, (x), _TRUE);\
                                                    }

#define CLR_DP_TX_SDP_DECODE_TYPE(x)                {\
                                                        g_enumDpMacTxSdpDecodeType &= (EnumDpTxSdpDecodeType)~(x);\
                                                        ScalerSetBit(PBC_96_DUMMY_96, ~(_DP_TX_SDP_DECODE_ALL), g_enumDpMacTxSdpDecodeType);\
                                                        ScalerTimerPollingFlagProc(_DP_ONE_FRAME_TIME_MAX, PBC_96_DUMMY_96, (x), _FALSE);\
                                                    }

#if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_SHA_CODE)
#define GET_DP_TX_EDID_SHA1_TOTAL_COUNT()           (g_usDpMacTxSha1ImportDataTotalCount)
#define SET_DP_TX_EDID_SHA1_TOTAL_COUNT(x)          (g_usDpMacTxSha1ImportDataTotalCount = (x))

#define GET_DP_TX_EDID_SHA1_FIRST_FLAG()            (g_bDpMacTxSha1ImportFirstBlockFlag)
#define SET_DP_TX_EDID_SHA1_FIRST_FLAG()            (g_bDpMacTxSha1ImportFirstBlockFlag = _TRUE)
#define CLR_DP_TX_EDID_SHA1_FIRST_FLAG()            (g_bDpMacTxSha1ImportFirstBlockFlag = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of SDP Decode Type
//--------------------------------------------------
typedef enum
{
    _DP_TX_SDP_DECODE_OFF = 0x00,
    _DP_TX_SDP_DECODE_PPS = _BIT0,
    _DP_TX_SDP_DECODE_META_CEA = _BIT1,
    _DP_TX_SDP_DECODE_META_VESA = _BIT2,
    _DP_TX_SDP_DECODE_AUDIO = _BIT3,
    _DP_TX_SDP_DECODE_ALL = 0x0F,
} EnumDpTxSdpDecodeType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON) && (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern void ScalerDpMacTxGetHpdQueueProc(void);
extern void ScalerDpMacTxGetIRQTypeProc(void);
#endif
extern void ScalerDpMacTxIRQEventCheck(void);
extern bit ScalerDpMacTxLinkConfigInitial(void);
extern bit ScalerDpMacTxDfpDeviceWakeUpInitial(void);
extern bit ScalerDpMacTxSetSourceOui(void);
extern bit ScalerDpMacTxDfpDeviceCapChangeCheck(void);
extern void ScalerDpMacTxDfpDeviceBasicCapSetting(void);
extern bit ScalerDpMacTxGetDfpDeviceSinkCountProc(void);

#if(_DFP_SINK_EDID_CHANGE_CHECK_METHOD == _EDID_SHA_CODE)
extern bit ScalerDpMacTxDfpDeviceEdidChangeCheck(void);
extern bit ScalerDpMacTxReadDfpDeviceEdidOneBlock(BYTE *pucEdid, BYTE ucBlockIndex);
extern void ScalerDpMacTxReadOutShaCode(BYTE *pucShaValue, BYTE ucShaLength);
extern void ScalerDpMacTxSha1Run(bit bIsFirst);
extern void ScalerDpMacTxSha1CircuitReset(void);
extern void ScalerDpMacTxSha1DataInput(BYTE *pucDataIn, WORD usDataInLength, bit bMOT);
#else
extern bit ScalerDpMacTxGetDfpDeviceReadEdid(void);
#endif

extern bit ScalerDpMacTxEdidAnalysisYcbcr420Capable(void);
extern bit ScalerDpMacTxGetDfpDeviceExtendCapProc(BYTE *pucExtenFieldCapInfo);

#if(_DP_MST_SUPPORT == _ON)
extern bit ScalerDpMacTxGetDfpDeviceMstCapProc(void);
extern void ScalerDpMacTxMstInfoReset(void);
extern bit ScalerDpMacTxMstCancelDebounceCheck(void);
extern bit ScalerDpMacTxGetUpReqEnableStatusChange(void);
extern void ScalerDpMacTxUpdateDfpDeviceMsgCapFieldStatus(void);
extern bit ScalerDpMacTxMstStreamChangeCheck(void);
#endif

#if(_DP_TX_FEC_SUPPORT == _ON)
extern bit ScalerDpMacTxGetDfpDeviceFecCapProc(void);
extern void ScalerDpMacTxFecStreamChangeCheck(void);
extern void ScalerDpMacTxFecStreamEnableCheck(void);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacTxGetDfpDeviceDscCapProc(void);
extern void ScalerDpMacTxDscPpsPktTransmit(void);
extern void ScalerDpMacTxDscPassThroughSetting(void);
extern void ScalerDpMacTxDscStreamIrq(bit bEnable);
extern void ScalerDpMacTxDscStreamWD(bit bEnable);
extern void ScalerDpMacTxDfpDscEnableProc(bit bEnable);
extern WORD ScalerDpMacTxGetDscPassThroughBpp(void);
extern void ScalerDpMacTxSetDscTuSizeAuto(bit bEnable);
extern void ScalerDpMacTxDscIntHandle_EXINT0(void);
extern void ScalerDpMacTxDscPassThroughReset_EXINT0(void);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDpMacTxDfpDeviceFreesyncEnable(void);
#endif

extern bit ScalerDpMacTxGetDfpDeviceExtendReceiverCapProc(void);
extern void ScalerDpMacTxDfpDeviceVersionProc(void);
extern void ScalerDpMacTxGetDfpDeviceLinkBandwidth(void);
extern void ScalerDpMacTxGetDfpDeviceDownSpreadStatus(void);
extern void ScalerDpMacTxGetDfpDeviceMsaIgnored(void);
extern void ScalerDpMacTxGetDfpDeviceYcbcr420Support(void);
extern void ScalerDpMacTxMstPeerDeviceCapProc(void);
extern void ScalerDpMacTxStreamHandler(void);
extern void ScalerDpMacTxLinkConfigInfoReset(void);
extern void ScalerDpMacTxStreamInfoReset(void);
extern void ScalerDpMacTxCapInfoReset(void);
extern void ScalerDpMacTxSSTSecDataHandler(void);
extern void ScalerDpMacTxSdpHandler(void);
#if(_DP_SUPPORT == _ON)
#if(_DP_HDR10_SUPPORT == _ON)
extern void ScalerDpMacTxSdpHdrHandler(void);
#endif
#if(_DP_TX_AUDIO_SUPPORT == _ON)
extern void ScalerDpMacTxSdpAudioHandler(void);
#endif
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern void ScalerDpMacTxSdpFreeSyncHandler(void);
#endif
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern void ScalerDpMacTxSdpAdaptiveSyncHandler(void);
#endif
extern bit ScalerDpMacTxSdpInfoRevStateCheck(EnumDpSdpType enumDpSdpType);
extern bit ScalerDpMacTxSdpInfoChgCheck(EnumDpSdpType enumDpSdpType);
extern EnumDpMacRxSdpChangeEvent ScalerDpMacTxSdpInfoChgEventCheck(EnumDpSdpType enumDpSdpType);
#endif
extern bit ScalerDpMacTxSdpWaitUpdateSafeRegion(void);
extern bit ScalerDpMacTxPollingFlagAfterSetProc(WORD usTimeout, WORD usRegister, BYTE ucSetValue, BYTE ucBit, bit bSuccess);
extern void ScalerDpMacTxSdpSetDataByte(EnumDPTxSecDataPacketType enumPackettype, EnumDPTxSdpDoubleBufferType enumDoubleBufferType);
extern void ScalerDpMacTxSdpSetDataByte_8b10b(EnumDPTxSdpTypeForDB enumSdpTypeSel, BYTE *pucInfoFrameData, BYTE ucLength, EnumDPTxSdpDoubleBufferType enumDoubleBufferType);
extern void ScalerDpMacTxColorimetryChangeHandler(void);
extern bit ScalerDpMacTxSpdInfoRevCheck(EnumDpSdpType enumDpSdpType);
extern bit ScalerDpMacTxSpdInfoChgCheck(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacTxSdpGetInfoData(EnumDpSdpType enumDpSdpType, BYTE *pucInfoData);
extern BYTE ScalerDpMacTxSdpInfoHB3Value(EnumDpSdpType enumDpSdpType);
extern bit ScalerDpMacTxCloneModeSdpInfoRevCheck(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacTxCloneModeGetSdpPktData(EnumInputPort enumInputPort, EnumDpSdpType enumDpSdpType, BYTE *pucInfoData);
extern BYTE ScalerDpMacTxCloneModeSdpInfoHB3(EnumInputPort enumInputPort, EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacTxReorderReset(void);

#if(_DP_SUPPORT == _ON)
extern bit ScalerDpMacTxTrackingEnableCheck(EnumDPTxInputSource enumStreamSource);
extern bit ScalerDpMacTxReorderTrackingPllSetting(EnumDPTxInputSource enumStreamSource);
extern EnumDpMacRxTrackingSource ScalerDpMacTxGetRxReorderTrackingMode(EnumDPTxInputSource enumStreamSource);
#endif
extern void ScalerDpMacTxSSTSetting(void);
extern void ScalerDpMacTxSdpClearHeaderByte(EnumDPTxSecDataPacketType enumPackettype);
extern void ScalerDpMacTxSdpClearHeaderByte_8b10b(EnumDPTxSecDataPacketType enumPackettype);
extern BYTE ScalerDpMacTxSdpGetParity(BYTE ucHeader);
extern bit ScalerDpMacTxSdpSendEnableCheck(EnumDPTxSecFunctionCtrl enumDPTxSecFunctionCtrl);
extern void ScalerDpMacTxSdpSendEnableSwitch(EnumDPTxSecFunctionCtrl enumDPTxSecFunctionCtrl, bit bEnable);
extern void ScalerDpMacTxSSTDisplayFormatSetting(void);
extern void ScalerDpMacTxSSTMSASetting(void);
extern void ScalerDpMacTxMsaMiscSetting(void);
extern void ScalerDpMacTxMsaSetColorFormat(EnumDpMsaColorimetry enumMsaColorimetry);
extern void ScalerDpMacTxVscSdpSetting(void);
extern bit ScalerDpMacTxSdpVscEnable(void);
extern void ScalerDpMacTxSdpSplit(bit bEnable);
extern void ScalerDpMacTxCloneOutputRxMACSelect(EnumInputPort enumInputPort, EnumPortType enumPortType);
extern bit ScalerDpMacTxCloneCheckInterlaceVtotal(void);
extern void ScalerDpMacTxCloneBandwidthCheck(EnumInputPort enumInputPort);
extern void ScalerDpMacTxColorInfoSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacTxInterlaceInfoSetting(EnumInputPort enumInputPort, EnumPortType enumPortType);

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
extern void ScalerDpMacTxBlockStatusSet(bit bEnable);
#endif

#if(_DP_TX_AUDIO_SUPPORT == _ON)
extern void ScalerDpMacTxSdpAudioFormatSetting(void);
extern void ScalerDpMacTxSdpAudioFormatSetting_8b10b(void);
#if(_AUDIO_SUPPORT == _ON)
extern void ScalerDpMacTxSdpAudioChannelStatusSetting_8b10b(void);
#endif
extern bit ScalerDpMacTxSdpAudioGetFormatChange(void);
extern bit ScalerDpMacTxSdpAudioGetFormatChange_8b10b(void);
extern WORD ScalerDpMacTxSdpAudioGetSamplingFreqPacket(EnumDPTxAudioSamplingFreq enumSamplingFrequency);
extern BYTE ScalerDpMacTxSdpAudioGetSamplingFreqRange(void);
extern BYTE ScalerDpMacTxSdpAudioGetSamplingFreqRange_8b10b(void);
extern void ScalerDpMacTxSdpAudioPlayProc(EnumDPTxAudioPlayState enumPlayState);
extern void ScalerDpMacTxSdpAudioPlayProc_8b10b(EnumDPTxAudioPlayState enumPlayState);
extern void ScalerDpMacTxSdpAudioTimestampProc(bit bEnable);
extern void ScalerDpMacTxSdpAudioTimestampProc_8b10b(bit bEnable);
extern void ScalerDpMacTxSdpAudioStreamProc(bit bEnable);
extern void ScalerDpMacTxSdpAudioStreamProc_8b10b(bit bEnable);
extern void ScalerDpMacTxSdpAudioDecodeEnable(BYTE ucDpTxStreamSource);
extern void ScalerDpMacTxSdpAudioDecodeEnable_8b10b(BYTE ucDpTxStreamSource);
extern void ScalerDpMacTxSdpAudioDecodeDisable(void);
extern void ScalerDpMacTxSdpAudioDecodeDisable_8b10b(void);
extern void ScalerDpMacTxSetAudioMuteFlag(bit bEnable);
extern void ScalerDpMacTxSetAudioMuteFlag_8b10b(bit bEnable);

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
extern void ScalerDpMacTxSleepAudioControl(void);
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpMacTxSdpAudioFormatSetting_128b132b(void);
extern void ScalerDpMacTxSdpAudioChannelStatusSetting_128b132b(void);
extern bit ScalerDpMacTxSdpAudioGetFormatChange_128b132b(void);
extern BYTE ScalerDpMacTxSdpAudioGetSamplingFreqRange_128b132b(void);
extern void ScalerDpMacTxSdpAudioPlayProc_128b132b(EnumDPTxAudioPlayState enumPlayState);
extern void ScalerDpMacTxSdpAudioTimestampProc_128b132b(bit bEnable);
extern void ScalerDpMacTxSdpAudioStreamProc_128b132b(bit bEnable);
extern void ScalerDpMacTxSdpAudioDecodeEnable_128b132b(BYTE ucDpTxStreamSource);
extern void ScalerDpMacTxSdpAudioDecodeDisable_128b132b(void);
extern void ScalerDpMacTxSetAudioMuteFlag_128b132b(bit bEnable);
#endif // End of #if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

extern bit ScalerDpMacTxReAuthCheck(EnumPortType enumPortType);
extern bit ScalerDpMacTxBypass420Check(EnumInputPort enumInputPort);
extern void ScalerDpMacTxBypass420Setting(EnumPortType enumPortType);

extern void ScalerDpMacTxDownStreamEdidCheckSpecialVendor(void);
#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
extern void ScalerDpMacTxLinkConfigAdjust(EnumDpMacTxConfig enumDpMacTxConfig);
#endif

extern void ScalerDpMacTxDownStreamEdidBwSetting(void);

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
extern WORD ScalerDpMacTxGetDaisyStreamStartPositionRegAddress_8b10b(EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacTxResetDaisyStreamPositionReg_8b10b(void);
extern void ScalerDpMacTxSetDaisySourceMuxReg_8b10b(EnumDpStreamSourceNum enumDpStreamSourceNum, EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacTxResetDaisySourceMuxReg_8b10b(void);
#endif

#if((_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
extern WORD ScalerDpMacTxGetDaisyStreamStartPositionRegAddress_128b132b(EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacTxResetDaisyStreamPositionReg_128b132b(void);
extern void ScalerDpMacTxSetDaisySourceMuxReg_128b132b(EnumDpStreamSourceNum enumDpStreamSourceNum, EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacTxResetDaisySourceMuxReg_128b132b(void);
#endif

#endif // End of #if(_DP_MAC_TX_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_DP_MAC_TX_H__
