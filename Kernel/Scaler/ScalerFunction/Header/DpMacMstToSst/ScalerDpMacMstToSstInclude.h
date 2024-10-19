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
// ID Code      : ScalerDpMacMstToSstInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_MAC_MST2SST_INITIAL()                                    (g_bDpMacMstToSstInitial)
#define SET_DP_MAC_MST2SST_INITIAL()                                    (g_bDpMacMstToSstInitial = _TRUE)
#define CLR_DP_MAC_MST2SST_INITIAL()                                    (g_bDpMacMstToSstInitial = _FALSE)

#define GET_DP_MAC_MST2SST_STREAM_JUDGE()                               (g_bDpMacMstToSstStreamJudge)
#define SET_DP_MAC_MST2SST_STREAM_JUDGE()                               (g_bDpMacMstToSstStreamJudge = _TRUE)
#define CLR_DP_MAC_MST2SST_STREAM_JUDGE()                               (g_bDpMacMstToSstStreamJudge = _FALSE)

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
#define GET_DP_MAC_MST2SST_DETECT_DSC_DECODE_ENABLE()                   (g_bDpMacMstToSstDscDeodeDetectEnable)
#define SET_DP_MAC_MST2SST_DETECT_DSC_DECODE_ENABLE()                   (g_bDpMacMstToSstDscDeodeDetectEnable = _TRUE)
#define CLR_DP_MAC_MST2SST_DETECT_DSC_DECODE_ENABLE()                   (g_bDpMacMstToSstDscDeodeDetectEnable = _FALSE)

#define GET_DP_MAC_MST2SST_DSC_DECODE_ENABLE()                          (g_bDpMacMstToSstDscDeodeEnable)
#define SET_DP_MAC_MST2SST_DSC_DECODE_ENABLE()                          (g_bDpMacMstToSstDscDeodeEnable = _TRUE)
#define CLR_DP_MAC_MST2SST_DSC_DECODE_ENABLE()                          (g_bDpMacMstToSstDscDeodeEnable = _FALSE)
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Audio Ready To Play Status
//--------------------------------------------------
typedef enum
{
    _MST2SST_AUDIO_STATUS_PREPARING,
    _MST2SST_AUDIO_STATUS_SETTING,
    _MST2SST_AUDIO_STATUS_PLAYBACK,
} EnumDpMacMstToSstAudioStatus;

//--------------------------------------------------
// Enumerations of MST2SST Stream Status
//--------------------------------------------------
typedef enum
{
    _MST2SST_STREAM_STATUS_NO_SIGNAL,
    _MST2SST_STREAM_STATUS_SEARCH,
    _MST2SST_STREAM_STATUS_ACTIVE,
} EnumDpMacMstToSstStreamStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
extern volatile bit g_bDpMacMstToSstDscDeodeEnable;
extern volatile bit g_bDpMacMstToSstDscDeodeDetectEnable;
#endif

extern bit g_bDpMacMstToSstInitial;
extern bit g_bDpMacMstToSstStreamJudge;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpMacMstToSstProc(void);
extern bit ScalerDpMacMstToSstGetInputMsaTimingInfo(void);
extern void ScalerDpMacMstToSstSetColorInfo(void);
extern bit ScalerDpMacMstToSstMeasureInput(void);
extern void ScalerDpMacMstToSstGetSdpPktData(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);
extern BYTE ScalerDpMacMstToSstSdpInfoHB3(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacMstToSstSetFifoWD(bit bEn);
extern BYTE ScalerDpMacMstToSstGetColorimetryExtPreValue(void);
extern BYTE ScalerDpMacMstToSstGetColorimetryPreValue(void);
extern BYTE ScalerDpMacMstToSstGetQuantizationPreValue(void);
extern void ScalerDpMacMstToSstColorimetrySetting(void);
extern void ScalerDpMacMstToSstColorimetryExtSetting(void);
extern void ScalerDpMacMstToSstQuantizationSetting(void);
extern EnumDpRxMacPixelMode ScalerDpMacMstToSstGetInputPixelMode(void);
extern void ScalerDpMacMstToSstStreamAfterJudgeSetting(void);

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern bit ScalerDpMacMstToSstDscReorderDetect(void);
extern bit ScalerDpMacMstToSstReorderStableDetect(EnumDpMacSel enumDpMacSel);
extern void ScalerDpMacMstToSstDscGetPpsInfo(void);
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDpMacMstToSstDscDecoderScanInputPort(void);
extern bit ScalerDpMacMstToSstDscDecodeCheck(void);
extern void ScalerDpMacMstToSstDscDecoderSetFifoWD(bit bEn);
extern void ScalerDpMacMstToSstDscDecoderRxMacReset(void);
#endif

#if((_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacMstToSstDscReset(void);
#endif

#if(_HW_DP_MAC_STREAM_SWITCH_SUPPORT == _ON)
extern void ScalerDpMacMstToSstRestoreSourceMuxBackupToReg(void);
extern void ScalerDpMacMstToSstResetSourceMuxReg(void);
#endif

#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

