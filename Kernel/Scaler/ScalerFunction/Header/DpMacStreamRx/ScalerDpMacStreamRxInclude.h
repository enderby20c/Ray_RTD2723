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
// ID Code      : ScalerDpMacStreamRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _REF_VBID                                                   0
#define _REF_BS_COUNTER                                             1

//--------------------------------------------------
// Definitions of DP FreeSync AMD SPD Info
//--------------------------------------------------
#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_AMD_SPD_INFO(x)                       (ScalerDpMacStreamRx0GetAmdSpdInfo(x))
#define GET_DP_MAC_STREAM_RX1_AMD_SPD_INFO(x)                       (ScalerDpMacStreamRx1GetAmdSpdInfo(x))
#define GET_DP_MAC_STREAM_RX2_AMD_SPD_INFO(x)                       (ScalerDpMacStreamRx2GetAmdSpdInfo(x))
#define GET_DP_MAC_STREAM_RX3_AMD_SPD_INFO(x)                       (ScalerDpMacStreamRx3GetAmdSpdInfo(x))
#define GET_DP_MAC_STREAM_RX4_AMD_SPD_INFO(x)                       (ScalerDpMacStreamRx4GetAmdSpdInfo(x))

#define GET_DP_MAC_STREAM_RX0_HTOTAL()                              (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx0DrrMsaHtotal)
#define SET_DP_MAC_STREAM_RX0_HTOTAL(x)                             (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx0DrrMsaHtotal = (x))

#define GET_DP_MAC_STREAM_RX1_HTOTAL()                              (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx1DrrMsaHtotal)
#define SET_DP_MAC_STREAM_RX1_HTOTAL(x)                             (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx1DrrMsaHtotal = (x))

#define GET_DP_MAC_STREAM_RX2_HTOTAL()                              (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx2DrrMsaHtotal)
#define SET_DP_MAC_STREAM_RX2_HTOTAL(x)                             (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx2DrrMsaHtotal = (x))

#define GET_DP_MAC_STREAM_RX3_HTOTAL()                              (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx3DrrMsaHtotal)
#define SET_DP_MAC_STREAM_RX3_HTOTAL(x)                             (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx3DrrMsaHtotal = (x))

#define GET_DP_MAC_STREAM_RX4_HTOTAL()                              (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx4DrrMsaHtotal)
#define SET_DP_MAC_STREAM_RX4_HTOTAL(x)                             (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx4DrrMsaHtotal = (x))

#define GET_DP_MAC_STREAM_RX0_HTOTAL_MARGIN()                       (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx0DrrHtotalMargin)
#define SET_DP_MAC_STREAM_RX0_HTOTAL_MARGIN(x)                      (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx0DrrHtotalMargin = (x))

#define GET_DP_MAC_STREAM_RX1_HTOTAL_MARGIN()                       (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx1DrrHtotalMargin)
#define SET_DP_MAC_STREAM_RX1_HTOTAL_MARGIN(x)                      (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx1DrrHtotalMargin = (x))

#define GET_DP_MAC_STREAM_RX2_HTOTAL_MARGIN()                       (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx2DrrHtotalMargin)
#define SET_DP_MAC_STREAM_RX2_HTOTAL_MARGIN(x)                      (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx2DrrHtotalMargin = (x))

#define GET_DP_MAC_STREAM_RX3_HTOTAL_MARGIN()                       (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx3DrrHtotalMargin)
#define SET_DP_MAC_STREAM_RX3_HTOTAL_MARGIN(x)                      (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx3DrrHtotalMargin = (x))

#define GET_DP_MAC_STREAM_RX4_HTOTAL_MARGIN()                       (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx4DrrHtotalMargin)
#define SET_DP_MAC_STREAM_RX4_HTOTAL_MARGIN(x)                      (g_stDpMacStreamRxDrrMsaInfo.usDpMacRx4DrrHtotalMargin = (x))
#endif

#define GET_DP_MAC_STREAM_RX0_H_PERIOD()                            (ScalerDpMacStreamRx0GetHPeriod())
#define GET_DP_MAC_STREAM_RX1_H_PERIOD()                            (ScalerDpMacStreamRx1GetHPeriod())
#define GET_DP_MAC_STREAM_RX2_H_PERIOD()                            (ScalerDpMacStreamRx2GetHPeriod())
#define GET_DP_MAC_STREAM_RX3_H_PERIOD()                            (ScalerDpMacStreamRx3GetHPeriod())
#define GET_DP_MAC_STREAM_RX4_H_PERIOD()                            (ScalerDpMacStreamRx4GetHPeriod())

#define GET_DP_MAC_STREAM_RX0_HSW()                                 (ScalerDpMacStreamRx0GetHSW())
#define GET_DP_MAC_STREAM_RX1_HSW()                                 (ScalerDpMacStreamRx1GetHSW())
#define GET_DP_MAC_STREAM_RX2_HSW()                                 (ScalerDpMacStreamRx2GetHSW())
#define GET_DP_MAC_STREAM_RX3_HSW()                                 (ScalerDpMacStreamRx3GetHSW())
#define GET_DP_MAC_STREAM_RX4_HSW()                                 (ScalerDpMacStreamRx4GetHSW())

#define GET_DP_MAC_STREAM_RX0_V_FREQ()                              (ScalerDpMacStreamRx0GetVFreq())
#define GET_DP_MAC_STREAM_RX1_V_FREQ()                              (ScalerDpMacStreamRx1GetVFreq())
#define GET_DP_MAC_STREAM_RX2_V_FREQ()                              (ScalerDpMacStreamRx2GetVFreq())
#define GET_DP_MAC_STREAM_RX3_V_FREQ()                              (ScalerDpMacStreamRx3GetVFreq())
#define GET_DP_MAC_STREAM_RX4_V_FREQ()                              (ScalerDpMacStreamRx4GetVFreq())

#define GET_DP_MAC_STREAM_RX0_V_PERIOD()                            (ScalerDpMacStreamRx0GetVPeriod())
#define GET_DP_MAC_STREAM_RX1_V_PERIOD()                            (ScalerDpMacStreamRx1GetVPeriod())
#define GET_DP_MAC_STREAM_RX2_V_PERIOD()                            (ScalerDpMacStreamRx2GetVPeriod())
#define GET_DP_MAC_STREAM_RX3_V_PERIOD()                            (ScalerDpMacStreamRx3GetVPeriod())
#define GET_DP_MAC_STREAM_RX4_V_PERIOD()                            (ScalerDpMacStreamRx4GetVPeriod())

//--------------------------------------------------
// DP MAC Global IRQ Flag
//--------------------------------------------------
#if(_DP_MAC_RX0_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_MAC_GLOBAL_HIGH_PRIORITY_IRQ_FLAG()   (ScalerGetBit_EXINT(P6F_17_ADI_DP_IRQ5, _BIT3) == _BIT3)
#define GET_DP_MAC_STREAM_RX0_MAC_GLOBAL_LOW_PRIORITY_IRQ_FLAG()    (ScalerGetBit_EXINT(P6F_17_ADI_DP_IRQ5, _BIT0) == _BIT0)
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_MAC_GLOBAL_HIGH_PRIORITY_IRQ_FLAG()   (ScalerGetBit_EXINT(P6F_17_ADI_DP_IRQ5, _BIT4) == _BIT4)
#define GET_DP_MAC_STREAM_RX1_MAC_GLOBAL_LOW_PRIORITY_IRQ_FLAG()    (ScalerGetBit_EXINT(P6F_17_ADI_DP_IRQ5, _BIT1) == _BIT1)
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_MAC_GLOBAL_HIGH_PRIORITY_IRQ_FLAG()   (ScalerGetBit_EXINT(P6F_17_ADI_DP_IRQ5, _BIT5) == _BIT5)
#define GET_DP_MAC_STREAM_RX2_MAC_GLOBAL_LOW_PRIORITY_IRQ_FLAG()    (ScalerGetBit_EXINT(P6F_17_ADI_DP_IRQ5, _BIT2) == _BIT2)
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_MAC_GLOBAL_HIGH_PRIORITY_IRQ_FLAG()   (ScalerGetBit_EXINT(P6F_18_ADI_DP_IRQ6, _BIT7) == _BIT7)
#define GET_DP_MAC_STREAM_RX3_MAC_GLOBAL_LOW_PRIORITY_IRQ_FLAG()    (ScalerGetBit_EXINT(P6F_18_ADI_DP_IRQ6, _BIT6) == _BIT6)
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_MAC_GLOBAL_HIGH_PRIORITY_IRQ_FLAG()   (ScalerGetBit_EXINT(P6F_18_ADI_DP_IRQ6, _BIT5) == _BIT5)
#define GET_DP_MAC_STREAM_RX4_MAC_GLOBAL_LOW_PRIORITY_IRQ_FLAG()    (ScalerGetBit_EXINT(P6F_18_ADI_DP_IRQ6, _BIT4) == _BIT4)
#endif

//--------------------------------------------------
// DP MAC Stream Power Cut Status Flag
//--------------------------------------------------
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
#if(_DP_MAC_RX0_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_POWER_CUT_STATUS()                    (g_stDpMacStreamRxPowerStatus.b1DpMacStreamRx0PowerCutStatus)
#define SET_DP_MAC_STREAM_RX0_POWER_CUT_STATUS(x)                   (g_stDpMacStreamRxPowerStatus.b1DpMacStreamRx0PowerCutStatus = (x))
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_POWER_CUT_STATUS()                    (g_stDpMacStreamRxPowerStatus.b1DpMacStreamRx1PowerCutStatus)
#define SET_DP_MAC_STREAM_RX1_POWER_CUT_STATUS(x)                   (g_stDpMacStreamRxPowerStatus.b1DpMacStreamRx1PowerCutStatus = (x))
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_POWER_CUT_STATUS()                    (g_stDpMacStreamRxPowerStatus.b1DpMacStreamRx2PowerCutStatus)
#define SET_DP_MAC_STREAM_RX2_POWER_CUT_STATUS(x)                   (g_stDpMacStreamRxPowerStatus.b1DpMacStreamRx2PowerCutStatus = (x))
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_POWER_CUT_STATUS()                    (g_stDpMacStreamRxPowerStatus.b1DpMacStreamRx3PowerCutStatus)
#define SET_DP_MAC_STREAM_RX3_POWER_CUT_STATUS(x)                   (g_stDpMacStreamRxPowerStatus.b1DpMacStreamRx3PowerCutStatus = (x))
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_POWER_CUT_STATUS()                    (g_stDpMacStreamRxPowerStatus.b1DpMacStreamRx4PowerCutStatus)
#define SET_DP_MAC_STREAM_RX4_POWER_CUT_STATUS(x)                   (g_stDpMacStreamRxPowerStatus.b1DpMacStreamRx4PowerCutStatus = (x))
#endif
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Struct for Recording MSA Info From Source
//--------------------------------------------------
#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Struct for DP MST Backup Info
//--------------------------------------------------
typedef struct
{
    WORD usDpMacRx0DrrMsaHtotal;
    WORD usDpMacRx1DrrMsaHtotal;
    WORD usDpMacRx2DrrMsaHtotal;
    WORD usDpMacRx3DrrMsaHtotal;
    WORD usDpMacRx4DrrMsaHtotal;

    WORD usDpMacRx0DrrHtotalMargin;
    WORD usDpMacRx1DrrHtotalMargin;
    WORD usDpMacRx2DrrHtotalMargin;
    WORD usDpMacRx3DrrHtotalMargin;
    WORD usDpMacRx4DrrHtotalMargin;

} StructDPMacRxDrrMsaInfo;
#endif

//--------------------------------------------------
// Enumerations of Source State
//--------------------------------------------------
typedef enum
{
    _DP_STREAM_NONE = 0x00,
    _DP_STREAM_PASS,
    _DP_STREAM_FAIL,
}EnumDpMacRxStreamVideoType;

//--------------------------------------------------
// Enumerations Dp Stream Display Format Regen Mode
//--------------------------------------------------
typedef enum
{
    _DPF_MODE_NONE = 0x00,
    _DPF_MODE_FRAME_SYNC,
    _DPF_MODE_FRAME_SYNC_BE,
    _DPF_MODE_FULL_LAST_LINE,
    _DPF_MODE_DE_ONLY,
    _DPF_MODE_DE_ONLY_FULL_LAST_LINE,
} EnumDpMacRxDPFRegenMode;

//--------------------------------------------------
// Enumerations of DP Stream Secondary Data Packet Event
//--------------------------------------------------
typedef enum
{
    _SDP_STATE_NOT_RECEIVED = 0x00,
    _SDP_STATE_RECEIVED,
}EnumDpMacRxSdpReceiveStates;

typedef enum
{
    _SDP_EVENT_NONE = 0x00,
    _SDP_EVENT_DATA_CHANGE,
    _SDP_EVENT_HEADER_CHANGE,
}EnumDpMacRxSdpChangeEvent;

//--------------------------------------------------
// Struct for DP Info frame
//--------------------------------------------------
typedef struct
{
    BYTE b1InfoFrameChange : 1;
    BYTE b1InfoDetecting : 1;
    BYTE b1InfoFrameReceive : 1;
    BYTE ucVersion;
    EnumDpMacRxSdpChangeEvent enumDpMacRxSdpChangeEvent;
    EnumDpMacRxSdpReceiveStates enumDpMacRxSdpReceiveStates;
}StructDpMacRxInfoFrameCtrl;

//--------------------------------------------------
// Struct for DP DSC PPS Info
//--------------------------------------------------
typedef struct
{
    WORD usDscPicHeight;
    WORD usDscPicWidth;
    WORD usDscSliceHeight;
    WORD usDscSliceWidth;
    WORD usDscBitsPerPixel;
    BYTE b4DscBitPerComponent : 4;
    BYTE b1DscNative420 : 1;
    BYTE b1DscNative422 : 1;
    BYTE b1DscSimple422 : 1;
}StructDpMacRxDscInfo;

//--------------------------------------------------
// Struct for DP SDP Meta Sram
//--------------------------------------------------
typedef struct
{
    EnumDpSdpMetaIndex enumIndex;
    BYTE ucPacketDBLength; // Num Data Byte of one Packet, pps = 128
}StructDpSdpMetaInfo;

//--------------------------------------------------
// Struct for DP MAC Stream Power Status
//--------------------------------------------------
#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
typedef struct
{
#if(_DP_MAC_RX0_SUPPORT == _ON)
    BYTE b1DpMacStreamRx0PowerCutStatus : 1;
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
    BYTE b1DpMacStreamRx1PowerCutStatus : 1;
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
    BYTE b1DpMacStreamRx2PowerCutStatus : 1;
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
    BYTE b1DpMacStreamRx3PowerCutStatus : 1;
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
    BYTE b1DpMacStreamRx4PowerCutStatus : 1;
#endif
}StructDpMacStreamRxPowerStatus;
#endif

//--------------------------------------------------
// Enumerations of DP SDP Meta Rcv Mode
//--------------------------------------------------
typedef enum
{
    _DP_SDP_META_RCV_NO_CHAIN = 0x00,
    _DP_SDP_META_RCV_CHAIN,
}EnumDpSdpMetaRcvMd;

//--------------------------------------------------
// Enumerations of DP RX MAC Tracking Source
//--------------------------------------------------
typedef enum
{
    _DP_MAC_RX_TRACKING_SOURCE_BS = 0x00,
    _DP_MAC_RX_TRACKING_SOURCE_BE,
}EnumDpMacRxTrackingSource;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_FREESYNC_SUPPORT == _ON)
extern StructDPMacRxDrrMsaInfo g_stDpMacStreamRxDrrMsaInfo;
#endif

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern StructDpMacStreamRxPowerStatus g_stDpMacStreamRxPowerStatus;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
extern void ScalerDpMacStreamRxMacInitial(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxSdpDataDetect(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxSdpPacketCheck(EnumDpMacSel enumDpMacSel, EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRxGetSdpPktData(EnumInputPort enumInputPort, EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);
extern EnumDpMacRxSdpReceiveStates ScalerDpMacStreamRxGetSdpReceived(EnumDpMacStreamSourceType enumMacSource, EnumDpSdpType enumDpSdpType);
extern EnumDpMacRxSdpChangeEvent ScalerDpMacStreamRxGetSdpChangeEvent(EnumDpMacStreamSourceType enumMacSource, EnumDpSdpType enumDpSdpType);
extern bit ScalerDpMacStreamRxGetSdpChanged(EnumDpMacStreamSourceType enumMacSource, EnumDpSdpType enumDpSdpType);
extern BYTE ScalerDpMacStreamRxGetSdpHB3(EnumInputPort enumInputPort, EnumDpSdpType enumDpSdpType);
extern EnumDpSdpRamIndex ScalerDpMacStreamRxGetSdpBufferType(EnumDpSdpType enumDpSdpType);

extern bit ScalerDpMacStreamRxGetCRCCalculate(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxLowPowerProc(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxGetMsaTimingInfo(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRxCheckInterlaceVtotal(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxAVMute(EnumInputPort enumInputPort);
extern EnumDpRxMacPixelMode ScalerDpMacStreamRxInputPixelMode(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxInterlaceModeConfig(EnumInputPort enumInputPort, BYTE ucInterlaceReference);
extern EnumInputPort ScalerDpMacStreamRxGetSourcePort(EnumDpMacStreamSourceType enumDpMacStreamSourceType);

extern bit ScalerDpMacStreamRxDeOnlyTimngCheck(StructDpInfo *pstDpInfo, DWORD ulFrameRate);
extern bit ScalerDpMacStreamRxDeOnlyJudge_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRxInterlaceCheck(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRxStreamClkRegenerate(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRxTrackingSetting(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRxPllSettingForReorderTracking(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo);

extern void ScalerDpMacStreamRxSetPLLNfOffProc(EnumInputPort enumInputPort, DWORD ulPllVcoClockHz, BYTE ucNcode, BYTE ucpllo, BYTE ucdivs);
extern bit ScalerDpMacStreamRxSetPLLNfOnProc(EnumInputPort enumInputPort, BYTE ucNcode, BYTE ucFcode_MSB4b, WORD usFcode_LSB16b, bit bPllVcoHighFreqStatus);
extern bit ScalerDpMacStreamRxGetVideoInfo(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxSetColorInfo(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxMacSetting(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxGetMeasureLinkInfo(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRxSetVfrontPorch(EnumInputPort enumInputPort, BYTE ucVfrontporch);
extern void ScalerDpMacStreamRxSetVheight(EnumInputPort enumInputPort, WORD usVheight);
extern void ScalerDpMacStreamRxTimingInfoAdjust(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRxTimingInfoAdjustForReorderTracking(EnumDpMacSel enumDpMacSel, StructDpInfo *pstDpInfo);

extern bit ScalerDpMacStreamRxMeasureInfoCheck(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRxPolarity(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxGetInterlaceMode(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxDigitalClrColorimetryChanged(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxDigitalClrColorimetryExtChanged(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxDigitalClrQuantizationChanged(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxForceBckgrdPath(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion);
extern void ScalerDpMacStreamRxClrForceBckgrdPath(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion);
extern bit ScalerDpMacStreamRxGetVideoStream(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxGetDscStream(EnumDpMacSel enumDpMacSel);
extern WORD ScalerDpMacStreamRxGetPpsElementInfo(EnumDpMacSel enumDpMacSel, EnumDpStreamPpsElement enumDpStreamPpsElement);
extern bit ScalerDpMacStreamRxGetAudioStream(EnumInputPort enumInputPort);

extern void ScalerDpMacStreamRxStreamReset(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxStreamPreDetectReset(EnumInputPort enumInputPort);
extern EnumDpStreamInfoType ScalerDpMacStreamRxGetStreamInfoType(EnumDpMacStreamSourceType enumMacSource);
extern void ScalerDpMacStreamRxSetDataPath(EnumDpMacStreamSourceType enumMacSource, EnumDpStreamDataPath enumDpStreamDataPath);
extern EnumDpStreamDataPath ScalerDpMacStreamRxGetDataPath(EnumDpMacStreamSourceType enumMacSource);
extern WORD ScalerDpMacStreamRxGetColorDepthPreValue(EnumDpMacStreamSourceType enumMacSource);
extern WORD ScalerDpMacStreamRxGetContentType(EnumDpMacStreamSourceType enumMacSource);
extern WORD ScalerDpMacStreamRxGetColorSpacePreValue(EnumDpMacStreamSourceType enumMacSource);
extern bit ScalerDpMacStreamRxGetColorimetryChange(EnumDpMacStreamSourceType enumMacSource);
extern void ScalerDpMacStreamRxClrColorimetryChange(EnumDpMacStreamSourceType enumMacSource);
extern bit ScalerDpMacStreamRxGetColorimetryExtChange(EnumDpMacStreamSourceType enumMacSource);
extern void ScalerDpMacStreamRxClrColorimetryExtChange(EnumDpMacStreamSourceType enumMacSource);
extern bit ScalerDpMacStreamRxGetQuantizationChange(EnumDpMacStreamSourceType enumMacSource);
extern void ScalerDpMacStreamRxClrQuantizationChange(EnumDpMacStreamSourceType enumMacSource);
extern EnumColorSpace ScalerDpMacStreamRxGetColorSpace(EnumDpMacStreamSourceType enumMacSource);
extern BYTE ScalerDpMacStreamRxGetColorDepth(EnumDpMacStreamSourceType enumMacSource);
extern EnumColorimetry ScalerDpMacStreamRxGetColorimetry(EnumDpMacStreamSourceType enumMacSource);
extern EnumColorimetryExt ScalerDpMacStreamRxGetExtColorimetry(EnumDpMacStreamSourceType enumMacSource);
extern EnumColorYCCQuantization ScalerDpMacStreamRxGetYCCQuantizationRange(EnumDpMacStreamSourceType enumMacSource);
extern EnumColorRGBQuantization ScalerDpMacStreamRxGetRGBQuantizationRange(EnumDpMacStreamSourceType enumMacSource);
extern DWORD ScalerDpMacStreamRxGetPredectStreamClock(EnumDpMacStreamSourceType enumMacSource);
extern DWORD ScalerDpMacStreamRxGetNativePixelClock(EnumDpMacStreamSourceType enumMacSource);
extern DWORD ScalerDpMacStreamRxGetElement(EnumDpMacStreamSourceType enumMacSource, EnumDpStreamElement enumElement);
extern bit ScalerDpMacStreamRxTrackingStatusCheck(EnumInputPort enumInputPort);
extern EnumDpMacRxTrackingSource ScalerDpMacStreamRxGetTrackingSource(EnumDpMacSel enumDpMacSel);
extern bit ScalerDpMacStreamRxVbiosMsaCheck(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxBsMissCheck(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern void ScalerDpMacStreamRxBsMissFlagClear(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxSinkStatusSetting(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxCheckVgipVsBypass(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxSdpIrqEnable(EnumInputPort enumInputPort, EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern void ScalerDpMacStreamRxPowerDataRecover(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxHdcpMeasureCheck(EnumInputPort enumInputPort);
extern EnumDpMacRxDPFRegenMode ScalerDpMacStreamRxGetDPFRegenMode(EnumInputPort enumInputPort);

extern void ScalerDpMacStreamRxSetBsMissDetectIRQ(EnumInputPort enumInputPort, bit bEn);

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacStreamRxPowerProc(EnumDpMacSel enumDpMacSel, EnumPowerAction enumPowerAction);
#endif

#if(_AUDIO_SUPPORT == _ON)
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern bit ScalerDpMacStreamRxGetInternalAudioGenEnable(EnumDpMacSel enumDpMacSel);
#endif
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit ScalerDpMacStreamRxGetSourceTypeJudgeStatus(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxGetSourceTypeJudgeStatus_WDINT(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxClrSourceTypeJudge(EnumInputPort enumInputPort);
#endif

#if(_DP_HBLANKING_MODIFY_SUPPORT == _ON)
extern WORD ScalerDpMacStreamRxHblankingModifyFifoOffsetUpdate(StructDpInfo *pstDpInfo, WORD usFifoOffset);
extern bit ScalerDpMacStreamRxHlankingModifyCheck(EnumInputPort enumInputPort, StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRxHblankingModifyDpfUpdate(StructDpInfo *pstDpInfo);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
extern void ScalerDpMacStreamRxHDR10GetCurrentStatus(EnumInputPort enumInputPort, bit *pbHDRInfoReceive, BYTE *pucSdpInfoData);
#endif

#if((_DP_FREESYNC_II_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON))
extern void ScalerDpMacStreamRxFreeSyncIIGetCurrentStatus(EnumInputPort enumInputPort, BYTE *pucFreeSyncIIInfoReceive, BYTE *pucFreeSyncIIInfoChange, BYTE *pucSdpInfoData);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDpMacStreamRxFreeSyncGetStreamConfig(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern DWORD ScalerDpMacStreamRxFreeSyncGetAmdSpdInfo(EnumInputPort enumInputPort, EnumAmdSpdInfoContent enumContent);
extern bit ScalerDpMacStreamRxFreeSyncGetAmdSpdInfoReceive(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxGetFreeSyncEnable(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
#endif

extern DWORD ScalerDpMacStreamRxGetHSPeriod(EnumInputPort enumInputPort);
extern WORD ScalerDpMacStreamRxGetHSW(EnumInputPort enumInputPort);
extern WORD ScalerDpMacStreamRxGetVFreq(EnumInputPort enumInputPort);
extern WORD ScalerDpMacStreamRxGetVSPeriod(EnumInputPort enumInputPort);

#if((_DP_RX_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern bit ScalerDpMacStreamRxDscGetFlagStatus(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern bit ScalerDpMacStreamRxDscStreamChangeCheck(EnumDpMacSel enumDpMacSel);
#endif

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRxDscSetStreamIRQAndWD(EnumInputPort enumInputPort, bit bEnable);
#endif

extern WORD ScalerDpMacStreamRxGetHwidth(EnumInputPort enumInputPort);
extern WORD ScalerDpMacStreamRxGetVheight(EnumInputPort enumInputPort);
extern WORD ScalerDpMacStreamRxGetHstart(EnumInputPort enumInputPort);

#if(_3DDI_FUNCTION == _ON)
extern bit ScalerDpMacStreamRxGetInterlace3ddiAvaible(StructDpInfo *pstDpInfo);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern bit ScalerDpMacStreamRxPRModeFlagStatus(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern bit ScalerDpMacStreamRxGetPRModeEnable(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern bit ScalerDpMacStreamRxPRModeGetFlagChange(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern void ScalerDpMacStreamRxPRModeSdpReset(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxPRModeCheckProc(EnumInputPort enumInputPort);
#endif

#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
extern bit ScalerDpMacStreamRxGetAuxlessAlpmEnable(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern bit ScalerDpMacStreamRxColorSpaceChangeSupportCheck(void);
extern void ScalerDpMacStreamRxSetColorSpaceChangeWD(EnumInputPort enumInputPort, bit bEn);
extern bit ScalerDpMacStreamRxMsaMiscChangeSupportCheck(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxSstSetMsaChangeIRQ(EnumInputPort enumInputPort, bit bEn);
#endif

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
extern EnumDpStreamSourceNum ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern EnumDpStreamSourceNum ScalerDpMacStreamRxGetMacToSourceMux(EnumDpMacSel enumDpMacSel);
#endif

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern WORD ScalerDpMacStreamRxBsMissDetectPeriodCalculate(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRxSetBsMissDetectPeriod(EnumInputPort enumInputPort);
#endif

extern bit ScalerDpMacStreamRxHblankNoSfModeSupport(void);

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
extern EnumDpSdpRamIndex ScalerDpMacStreamRxGetSdpBufferType_EXINT0(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRxSetNoVideoStreamIRQ_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern bit ScalerDpMacStreamRxGetFifoWDStatus_EXINT0(EnumInputPort enumInputPort);

extern void ScalerDpMacStreamRxCRCCalculate_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRxGetCRCCalculate_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxClrCRCCalculate_EXINT0(EnumInputPort enumInputPort);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRxDscSetStreamIRQ_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpMacStreamRxDscSetStreamWD_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern EnumDDomainRegion ScalerDpMacStreamRxGetForceBackgroundPath_EXINT0(EnumInputPort enumInputPort);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRxPRModeCrcCalculateEnable_EXINT0(EnumInputPort enumInputPort, bit bEnable);
#endif

#if(_DP_ADVANCED_HDR10_SUPPORT_MODE != _ADVANCED_HDR10_NONE)
extern void ScalerDpMacStreamRxAdvancedHdr10VsifDataStrcutMapping_EXINT0(BYTE *pucSdpData, StructAdvancedHDR10MetaData *pstSyncAdvancedHDR10Metadata);
#endif

#if(_DM_FUNCTION == _ON)
extern bit ScalerDpMacStreamRxGetDMDRAMReceived_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRxDMPacketReCheck_EXINT0(EnumInputPort enumInputPort);
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
extern void ScalerDpMacStreamRxPxpStreamMuxCheck(EnumInputPort enumInputPort);
#endif

extern bit ScalerDpMacStreamRxGetStreamPredetect(EnumInputPort enumInputPort);

#if((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
extern EnumDpStreamSourceNum ScalerDpMacStreamRxGetStreamSourceTypeToSourceMux_EXINT0(EnumDpMacStreamSourceType enumDpMacStreamSourceType);
extern EnumDpStreamSourceNum ScalerDpMacStreamRxGetMacToSourceMux_EXINT0(EnumDpMacSel enumDpMacSel);
#endif

///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern bit ScalerDpMacStreamRxDeOnlyJudge_128b132b(StructDpInfo *pstDpInfo);
#endif

// Special
extern StructDpInfo *ScalerDpMacStreamRxGetDpInfoPointer(EnumDpMacStreamSourceType enumMacSource);
#endif
