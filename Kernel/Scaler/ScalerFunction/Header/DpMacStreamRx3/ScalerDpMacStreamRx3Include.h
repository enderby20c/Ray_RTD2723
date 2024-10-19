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
// ID Code      : ScalerDpMacStreamRx3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX3_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp CRC Information
//----------------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX3_CRC_CALCULATE()                       (g_bDpMacStreamRx3CrcCalculate)
#define SET_DP_MAC_STREAM_RX3_CRC_CALCULATE()                       (g_bDpMacStreamRx3CrcCalculate = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_CRC_CALCULATE()                       (g_bDpMacStreamRx3CrcCalculate = _FALSE)

#define GET_DP_MAC_STREAM_RX3_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx3MSAFailRsetCount)
#define ADD_DP_MAC_STREAM_RX3_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx3MSAFailRsetCount++)
#define CLR_DP_MAC_STREAM_RX3_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx3MSAFailRsetCount = 0)

#define GET_DP_MAC_STREAM_RX3_FORCE_BCKGRD_PATH()                   (g_enumDpMacStreamRx3IrqForceBackgrd & _DDOMAIN_RGN_ALL)
#define SET_DP_MAC_STREAM_RX3_FORCE_BCKGRD_PATH(x)                  (g_enumDpMacStreamRx3IrqForceBackgrd |= (x))
#define CLR_DP_MAC_STREAM_RX3_FORCE_BCKGRD_PATH(x)                  (g_enumDpMacStreamRx3IrqForceBackgrd &= (EnumDDomainRegion)~(x))

#define GET_DP_MAC_STREAM_RX3_VFRONT_PORCH()                        (g_usDpMacStreamRx3Vfrontporch)
#define SET_DP_MAC_STREAM_RX3_VFRONT_PORCH(x)                       (g_usDpMacStreamRx3Vfrontporch = (x))

// Delay 5us for Wait Hw Update Period to Prevent MCU Get wrong value, Update Period is 3T, T = 1/14.318M or 1/27M
#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX3_MEASURE_POP_UP_128B132B()             {\
                                                                        ScalerSetBit(PF1_40_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                                        DELAY_5US();\
                                                                    }
#endif
#define SET_DP_MAC_STREAM_RX3_MEASURE_POP_UP_8B10B()                {\
                                                                        ScalerSetBit(PEE_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                                        DELAY_5US();\
                                                                    }

#define GET_DP_MAC_STREAM_RX3_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx3VscSdpColorMode)
#define SET_DP_MAC_STREAM_RX3_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx3VscSdpColorMode = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx3VscSdpColorMode = _FALSE)

#define GET_DP_MAC_STREAM_RX3_INTERLACE_VTOTAL_NUMBER()             (g_bDpMacStreamRx3InterlaceVtotalNum)
#define SET_DP_MAC_STREAM_RX3_INTERLACE_VTOTAL_NUMBER(x)            (g_bDpMacStreamRx3InterlaceVtotalNum = (x))

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
#define GET_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx3SPDInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx3SPDInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx3SPDInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_VERSION()              (g_stDpMacStreamRx3SPDInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_VERSION(x)             (g_stDpMacStreamRx3SPDInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_VERSION()              (g_stDpMacStreamRx3SPDInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx3SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx3SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx3SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx3SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx3SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX3_SPD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx3SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX3_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx3SPDInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX3_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx3SPDInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx3SPDInfoFrameCtrl.b1InfoDetecting = _FALSE)

#define GET_DP_MAC_STREAM_RX3_AMD_SPD_LOCAL_DIMMING()               (g_bDpMacStreamRx3LocalDimmingDisableControl)
#define SET_DP_MAC_STREAM_RX3_AMD_SPD_LOCAL_DIMMING(x)              (g_bDpMacStreamRx3LocalDimmingDisableControl = (x))
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_VERSION()            (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_VERSION(x)           (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_VERSION()            (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_CHANGE_EVENT()       (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_CHANGE_EVENT(x)      (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_CHANGE_EVENT()       (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_RECEIVED_STATE()     (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_RECEIVED_STATE(x)    (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_RECEIVED_STATE()     (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx3HDRInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx3HDRInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx3HDRInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_VERSION()              (g_stDpMacStreamRx3HDRInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_VERSION(x)             (g_stDpMacStreamRx3HDRInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_VERSION()              (g_stDpMacStreamRx3HDRInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx3HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx3HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx3HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx3HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx3HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX3_HDR_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx3HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX3_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx3HDRInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX3_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx3HDRInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx3HDRInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_MAC_RX3_ADVANCED_HDR10_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_ADVANCED_HDR10_RECEIVED_STATE()       (g_stDpMacStreamRx3AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX3_ADVANCED_HDR10_RECEIVED_STATE(x)      (g_stDpMacStreamRx3AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX3_ADVANCED_HDR10_RECEIVED_STATE()       (g_stDpMacStreamRx3AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX3_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx3AdvancedHDR10InfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX3_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx3AdvancedHDR10InfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx3AdvancedHDR10InfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_MAC_RX3_DM_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx3DMVsifInfoFrameCtrl.b1InfoFrameReceive)
#define SET_DP_MAC_STREAM_RX3_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx3DMVsifInfoFrameCtrl.b1InfoFrameReceive = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx3DMVsifInfoFrameCtrl.b1InfoFrameReceive = _FALSE)

#define GET_DP_MAC_STREAM_RX3_DM_VSIF_RECEIVED_STATE()              (g_stDpMacStreamRx3DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX3_DM_VSIF_RECEIVED_STATE(x)             (g_stDpMacStreamRx3DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX3_DM_VSIF_RECEIVED_STATE()              (g_stDpMacStreamRx3DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX3_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx3DMVsifInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX3_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx3DMVsifInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx3DMVsifInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_AUDIO_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx3AudioInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX3_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx3AudioInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx3AudioInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX3_AUD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx3AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX3_AUD_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx3AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX3_AUD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx3AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX3_AUD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx3AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX3_AUD_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx3AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX3_AUD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx3AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX3_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx3AudioInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX3_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx3AudioInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx3AudioInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#define GET_DP_MAC_STREAM_RX3_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx3PpsSdpCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX3_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx3PpsSdpCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx3PpsSdpCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX3_PPS_SDP_CHANGE_EVENT()                (g_stDpMacStreamRx3PpsSdpCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX3_PPS_SDP_CHANGE_EVENT(x)               (g_stDpMacStreamRx3PpsSdpCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX3_PPS_SDP_CHANGE_EVENT()                (g_stDpMacStreamRx3PpsSdpCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX3_PPS_SDP_RECEIVED_STATE()              (g_stDpMacStreamRx3PpsSdpCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX3_PPS_SDP_RECEIVED_STATE(x)             (g_stDpMacStreamRx3PpsSdpCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX3_PPS_SDP_RECEIVED_STATE()              (g_stDpMacStreamRx3PpsSdpCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX3_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx3PpsSdpCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX3_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx3PpsSdpCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx3PpsSdpCtrl.b1InfoDetecting = _FALSE)

#define GET_DP_MAC_STREAM_RX3_DSC_PIC_HEIGHT()                      (g_stDpMacStreamRx3DscInfo.usDscPicHeight)
#define SET_DP_MAC_STREAM_RX3_DSC_PIC_HEIGHT(x)                     (g_stDpMacStreamRx3DscInfo.usDscPicHeight = (x))
#define CLR_DP_MAC_STREAM_RX3_DSC_PIC_HEIGHT()                      (g_stDpMacStreamRx3DscInfo.usDscPicHeight = 0)

#define GET_DP_MAC_STREAM_RX3_DSC_PIC_WIDTH()                       (g_stDpMacStreamRx3DscInfo.usDscPicWidth)
#define SET_DP_MAC_STREAM_RX3_DSC_PIC_WIDTH(x)                      (g_stDpMacStreamRx3DscInfo.usDscPicWidth = (x))
#define CLR_DP_MAC_STREAM_RX3_DSC_PIC_WIDTH()                       (g_stDpMacStreamRx3DscInfo.usDscPicWidth = 0)

#define GET_DP_MAC_STREAM_RX3_DSC_SLICE_HEIGHT()                    (g_stDpMacStreamRx3DscInfo.usDscSliceHeight)
#define SET_DP_MAC_STREAM_RX3_DSC_SLICE_HEIGHT(x)                   (g_stDpMacStreamRx3DscInfo.usDscSliceHeight = (x))
#define CLR_DP_MAC_STREAM_RX3_DSC_SLICE_HEIGHT()                    (g_stDpMacStreamRx3DscInfo.usDscSliceHeight = 0)

#define GET_DP_MAC_STREAM_RX3_DSC_SLICE_WIDTH()                     (g_stDpMacStreamRx3DscInfo.usDscSliceWidth)
#define SET_DP_MAC_STREAM_RX3_DSC_SLICE_WIDTH(x)                    (g_stDpMacStreamRx3DscInfo.usDscSliceWidth = (x))
#define CLR_DP_MAC_STREAM_RX3_DSC_SLICE_WIDTH()                     (g_stDpMacStreamRx3DscInfo.usDscSliceWidth = 0)

#define GET_DP_MAC_STREAM_RX3_DSC_COLOR_BPP()                       (g_stDpMacStreamRx3DscInfo.usDscBitsPerPixel)
#define SET_DP_MAC_STREAM_RX3_DSC_COLOR_BPP(x)                      (g_stDpMacStreamRx3DscInfo.usDscBitsPerPixel = (x))
#define CLR_DP_MAC_STREAM_RX3_DSC_COLOR_BPP()                       (g_stDpMacStreamRx3DscInfo.usDscBitsPerPixel = 0)

#define GET_DP_MAC_STREAM_RX3_DSC_COLOR_BPC()                       (g_stDpMacStreamRx3DscInfo.b4DscBitPerComponent)
#define SET_DP_MAC_STREAM_RX3_DSC_COLOR_BPC(x)                      (g_stDpMacStreamRx3DscInfo.b4DscBitPerComponent = (x))
#define CLR_DP_MAC_STREAM_RX3_DSC_COLOR_BPC()                       (g_stDpMacStreamRx3DscInfo.b4DscBitPerComponent = 0)

#define GET_DP_MAC_STREAM_RX3_DSC_COLOR_NATIVE_420()                (g_stDpMacStreamRx3DscInfo.b1DscNative420)
#define SET_DP_MAC_STREAM_RX3_DSC_COLOR_NATIVE_420(x)               (g_stDpMacStreamRx3DscInfo.b1DscNative420 = (x))
#define CLR_DP_MAC_STREAM_RX3_DSC_COLOR_NATIVE_420()                (g_stDpMacStreamRx3DscInfo.b1DscNative420 = 0)

#define GET_DP_MAC_STREAM_RX3_DSC_COLOR_NATIVE_422()                (g_stDpMacStreamRx3DscInfo.b1DscNative422)
#define SET_DP_MAC_STREAM_RX3_DSC_COLOR_NATIVE_422(x)               (g_stDpMacStreamRx3DscInfo.b1DscNative422 = (x))
#define CLR_DP_MAC_STREAM_RX3_DSC_COLOR_NATIVE_422()                (g_stDpMacStreamRx3DscInfo.b1DscNative422 = 0)

#define GET_DP_MAC_STREAM_RX3_DSC_COLOR_SIMPLE_422()                (g_stDpMacStreamRx3DscInfo.b1DscSimple422)
#define SET_DP_MAC_STREAM_RX3_DSC_COLOR_SIMPLE_422(x)               (g_stDpMacStreamRx3DscInfo.b1DscSimple422 = (x))
#define CLR_DP_MAC_STREAM_RX3_DSC_COLOR_SIMPLE_422()                (g_stDpMacStreamRx3DscInfo.b1DscSimple422 = 0)

#define GET_DP_MAC_STREAM_RX3_DSC_COLOR_NATIVE_MODE()               (((GET_DP_MAC_STREAM_RX3_DSC_COLOR_NATIVE_420() == _TRUE) || (GET_DP_MAC_STREAM_RX3_DSC_COLOR_NATIVE_422() == _TRUE)) ? _TRUE : _FALSE)

//--------------------------------------------------
// Macro of VBID[3] Change to No-Video Flag
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX3_VBID3_CHANGED()                       (g_bDpMacStreamRx3Vbid3Chg)
#define SET_DP_MAC_STREAM_RX3_VBID3_CHANGED()                       (g_bDpMacStreamRx3Vbid3Chg = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_VBID3_CHANGED()                       (g_bDpMacStreamRx3Vbid3Chg = _FALSE)

//---------------------------------------------------------------------
// Macro of Enlarge DP H Proch
//---------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX3_H_PORCH_ENLARGE()                     (g_ucDpMacStreamRx3HPorchEnalrge)
#define SET_DP_MAC_STREAM_RX3_H_PORCH_ENLARGE(x)                    (g_ucDpMacStreamRx3HPorchEnalrge = (x))
#define CLR_DP_MAC_STREAM_RX3_H_PORCH_ENLARGE()                     (g_ucDpMacStreamRx3HPorchEnalrge = 0)

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//---------------------------------------------------------------------
// Macro of Dp Lane Valid Check
//---------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX3_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx3SourceTypeJudge)
#define SET_DP_MAC_STREAM_RX3_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx3SourceTypeJudge = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx3SourceTypeJudge = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Global IRQ Flag
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX3_GLOBAL_IRQ_FLAG()                     (ScalerGetBit(P6F_14_ADI_DP_IRQ2, _BIT6) == _BIT6)

//--------------------------------------------------
// DP MAC Flag
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX3_NO_VIDEO_IRQ_STATUS_8B10B()           ((ScalerGetBit(PEF_3F_DP_IRQ_CTRL1, _BIT4) == _BIT4) ? _ENABLE : _DISABLE)

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_NO_VIDEO_IRQ_STATUS_128B132B()        ((ScalerGetBit(PF2_3B_DP_IRQ_CTRL1, _BIT4) == _BIT4) ? _ENABLE : _DISABLE)
#endif

//--------------------------------------------------
// DP MAC DSC Flag
//--------------------------------------------------
#if(_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX3_DSC_SUPPORT_8B10B()                   {ScalerSetBit(PEE_91_DP_RSV1, ~(_BIT7 | _BIT6), _BIT7);}
#define GET_DP_MAC_STREAM_RX3_DSC_SUPPORT_8B10B()                   (ScalerGetBit(PEE_91_DP_RSV1, _BIT7) == _BIT7)
#define CLR_DP_MAC_STREAM_RX3_DSC_SUPPORT_8B10B()                   {ScalerSetBit(PEE_91_DP_RSV1, ~(_BIT7 | _BIT6), 0x00);}

#define SET_DP_MAC_STREAM_RX3_DSC_CHUNK_FROM_PPS_8B10B()            {ScalerSetBit(PEE_82_CPMODE, ~_BIT2, _BIT2);}

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX3_DSC_SUPPORT_128B132B()                {ScalerSetBit(PF1_25_DSC_CTRL_0, ~_BIT7, _BIT7);}
#define GET_DP_MAC_STREAM_RX3_DSC_SUPPORT_128B132B()                (ScalerGetBit(PF1_25_DSC_CTRL_0, _BIT7) == _BIT7)
#define CLR_DP_MAC_STREAM_RX3_DSC_SUPPORT_128B132B()                {ScalerSetBit(PF1_25_DSC_CTRL_0, ~_BIT7, 0x00);}

#define SET_DP_MAC_STREAM_RX3_DSC_CHUNK_FROM_PPS_128B132B()         {ScalerSetBit(PF1_25_DSC_CTRL_0, ~_BIT4, _BIT4);}
#endif
#endif

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX3_INTERLACE_VTT_FW_MODE_128B132B(x)     {\
                                                                        if((x) == _EVEN)\
                                                                        {\
                                                                            ScalerSetBit(PF1_03_DPF_CTRL_3, ~_BIT3, _BIT3);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PF1_03_DPF_CTRL_3, ~_BIT3, 0x00);\
                                                                        }\
                                                                    }
#endif
#define SET_DP_MAC_STREAM_RX3_INTERLACE_VTT_FW_MODE_8B10B(x)        {\
                                                                        if((x) == _EVEN)\
                                                                        {\
                                                                            ScalerSetBit(PEE_91_DP_RSV1, ~(_BIT6 | _BIT4), _BIT4);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PEE_91_DP_RSV1, ~(_BIT6 | _BIT4), 0x00);\
                                                                        }\
                                                                    }
#endif

//--------------------------------------------------
// DP MAC Stream Info
//--------------------------------------------------

#define GET_DP_MAC_STREAM_RX3_STREAM_PREDETECT()                    (g_stDpMacStreamRx3StreamInfo.b1StreamPreDetectFlag)
#define SET_DP_MAC_STREAM_RX3_STREAM_PREDETECT(x)                   (g_stDpMacStreamRx3StreamInfo.b1StreamPreDetectFlag = (x))

#define GET_DP_MAC_STREAM_RX3_STREAM_DATA_PATH()                    (g_stDpMacStreamRx3StreamInfo.enumDpStreamDataPath)
#define SET_DP_MAC_STREAM_RX3_STREAM_DATA_PATH(x)                   (g_stDpMacStreamRx3StreamInfo.enumDpStreamDataPath = (x))

#define GET_DP_MAC_STREAM_RX3_STREAM_INFO_TYPE()                    (g_stDpMacStreamRx3StreamInfo.enumDpStreamInfoType)
#define SET_DP_MAC_STREAM_RX3_STREAM_INFO_TYPE(x)                   (g_stDpMacStreamRx3StreamInfo.enumDpStreamInfoType = (x))

#define GET_DP_MAC_STREAM_RX3_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx3StreamInfo.b1StreamInfoTypeChangeFlag)
#define SET_DP_MAC_STREAM_RX3_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx3StreamInfo.b1StreamInfoTypeChangeFlag = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx3StreamInfo.b1StreamInfoTypeChangeFlag = _FALSE)

#define GET_DP_MAC_STREAM_RX3_STREAM_CLOCK()                        (g_stDpMacStreamRx3StreamInfo.ulStreamPreDetectPixelClock)
#define SET_DP_MAC_STREAM_RX3_STREAM_CLOCK(x)                       (g_stDpMacStreamRx3StreamInfo.ulStreamPreDetectPixelClock = (x))

#define GET_DP_MAC_STREAM_RX3_NATIVE_PIXEL_CLOCK()                  (g_stDpMacStreamRx3StreamInfo.ulDpStreamNativePixelClock)
#define SET_DP_MAC_STREAM_RX3_NATIVE_PIXEL_CLOCK(x)                 (g_stDpMacStreamRx3StreamInfo.ulDpStreamNativePixelClock = (x))

#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx3StreamInfo.b1FreeSyncEnable)
#define SET_DP_MAC_STREAM_RX3_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx3StreamInfo.b1FreeSyncEnable = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx3StreamInfo.b1FreeSyncEnable = _FALSE)
#endif

//--------------------------------------------------
// DP MAC PR Enable
//--------------------------------------------------
#if(_DP_PR_MODE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX3_PR_ENABLE_8B10B()                     {ScalerSetBit(PEF_4A_DUMMY_4A, ~(_BIT0), _BIT0);}
#define GET_DP_MAC_STREAM_RX3_PR_ENABLE_8B10B()                     (ScalerGetBit(PEF_4A_DUMMY_4A, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX3_PR_ENABLE_8B10B()                     {ScalerSetBit(PEF_4A_DUMMY_4A, ~(_BIT0), 0x00);}

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX3_PR_ENABLE_128B132B()                  {ScalerSetBit(PF2_4A_VSC10, ~(_BIT0), _BIT0);}
#define GET_DP_MAC_STREAM_RX3_PR_ENABLE_128B132B()                  (ScalerGetBit(PF2_4A_VSC10, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX3_PR_ENABLE_128B132B()                  {ScalerSetBit(PF2_4A_VSC10, ~(_BIT0), 0x00);}

#define GET_DP_MAC_STREAM_RX3_PR_ENABLE()                           (GET_DP_MAC_STREAM_RX3_PR_ENABLE_8B10B() || GET_DP_MAC_STREAM_RX3_PR_ENABLE_128B132B())
#else
#define GET_DP_MAC_STREAM_RX3_PR_ENABLE()                           (GET_DP_MAC_STREAM_RX3_PR_ENABLE_8B10B())
#endif
#endif

//--------------------------------------------------
// DP MAC ALPM Enable
//--------------------------------------------------
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX3_ALPM_ENABLE_8B10B()                   {ScalerSetBit(PEE_96_DP_ALPM0, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX3_ALPM_ENABLE_8B10B()                   (ScalerGetBit(PEE_96_DP_ALPM0, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX3_ALPM_ENABLE_8B10B()                   {ScalerSetBit(PEE_96_DP_ALPM0, ~_BIT0, 0x00);}

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX3_ALPM_ENABLE_128B132B()                {ScalerSetBit(PF1_57_DP_ALPM0, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX3_ALPM_ENABLE_128B132B()                (ScalerGetBit(PF1_57_DP_ALPM0, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX3_ALPM_ENABLE_128B132B()                {ScalerSetBit(PF1_57_DP_ALPM0, ~_BIT0, 0x00);}

#define GET_DP_MAC_STREAM_RX3_ALPM_ENABLE()                         (GET_DP_MAC_STREAM_RX3_ALPM_ENABLE_8B10B() || GET_DP_MAC_STREAM_RX3_ALPM_ENABLE_128B132B())
#else
#define GET_DP_MAC_STREAM_RX3_ALPM_ENABLE()                         (GET_DP_MAC_STREAM_RX3_ALPM_ENABLE_8B10B())
#endif
#endif

//--------------------------------------------------
// DP MAC Color Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX3_COLOR_SPACE_PREVALUE()                (g_stDpMacStreamRx3ColorInfo.ucDigitalColorSpacePreValue)
#define SET_DP_MAC_STREAM_RX3_COLOR_SPACE_PREVALUE(x)               (g_stDpMacStreamRx3ColorInfo.ucDigitalColorSpacePreValue = (x))

#define GET_DP_MAC_STREAM_RX3_COLOR_DEPTH_PREVALUE()                (g_stDpMacStreamRx3ColorInfo.b3DigitalColorDepthPreValue)
#define SET_DP_MAC_STREAM_RX3_COLOR_DEPTH_PREVALUE(x)               (g_stDpMacStreamRx3ColorInfo.b3DigitalColorDepthPreValue = (x))

#define GET_DP_MAC_STREAM_RX3_CONTENT_TYPE()                        (g_stDpMacStreamRx3ColorInfo.b3DigitalContentType)
#define SET_DP_MAC_STREAM_RX3_CONTENT_TYPE(x)                       (g_stDpMacStreamRx3ColorInfo.b3DigitalContentType = (x))

#define GET_DP_MAC_STREAM_RX3_COLORIMETRY_PREVALUE()                (g_stDpMacStreamRx3ColorInfo.b4DigitalColorimetryPreValue)
#define SET_DP_MAC_STREAM_RX3_COLORIMETRY_PREVALUE(x)               (g_stDpMacStreamRx3ColorInfo.b4DigitalColorimetryPreValue = (x))

#define GET_DP_MAC_STREAM_RX3_COLORIMETRY_EXT_PREVALUE()            (g_stDpMacStreamRx3ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_DP_MAC_STREAM_RX3_COLORIMETRY_EXT_PREVALUE(x)           (g_stDpMacStreamRx3ColorInfo.b4DigitalColorimetryExtPreValue = (x))

#define GET_DP_MAC_STREAM_RX3_QUANTIZATION_PREVALUE()               (g_stDpMacStreamRx3ColorInfo.b2DigitalQuantizationPreValue)
#define SET_DP_MAC_STREAM_RX3_QUANTIZATION_PREVALUE(x)              (g_stDpMacStreamRx3ColorInfo.b2DigitalQuantizationPreValue = (x))

#define GET_DP_MAC_STREAM_RX3_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx3ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_DP_MAC_STREAM_RX3_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx3ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx3ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX3_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx3ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_DP_MAC_STREAM_RX3_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx3ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx3ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX3_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx3ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_DP_MAC_STREAM_RX3_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx3ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx3ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX3_COLOR_SPACE()                         (g_stDpMacStreamRx3ColorInfo.enumDigitalColorSpace)
#define SET_DP_MAC_STREAM_RX3_COLOR_SPACE(x)                        (g_stDpMacStreamRx3ColorInfo.enumDigitalColorSpace = (x))

#define GET_DP_MAC_STREAM_RX3_COLOR_DEPTH()                         (g_stDpMacStreamRx3ColorInfo.ucDigitalColorDepthValue)
#define SET_DP_MAC_STREAM_RX3_COLOR_DEPTH(x)                        (g_stDpMacStreamRx3ColorInfo.ucDigitalColorDepthValue = (x))

#define GET_DP_MAC_STREAM_RX3_COLORIMETRY()                         (g_stDpMacStreamRx3ColorInfo.enumDigitalColorimetry)
#define SET_DP_MAC_STREAM_RX3_COLORIMETRY(x)                        (g_stDpMacStreamRx3ColorInfo.enumDigitalColorimetry = (x))

#define GET_DP_MAC_STREAM_RX3_EXT_COLORIMETRY()                     (g_stDpMacStreamRx3ColorInfo.enumDigitalColorimetryExt)
#define SET_DP_MAC_STREAM_RX3_EXT_COLORIMETRY(x)                    (g_stDpMacStreamRx3ColorInfo.enumDigitalColorimetryExt = (x))

#define GET_DP_MAC_STREAM_RX3_COLOR_YCC_QUANTIZATION_RANGE()        (g_stDpMacStreamRx3ColorInfo.enumDigitalColorYCCQuantization)
#define SET_DP_MAC_STREAM_RX3_COLOR_YCC_QUANTIZATION_RANGE(x)       (g_stDpMacStreamRx3ColorInfo.enumDigitalColorYCCQuantization = (x))

#define GET_DP_MAC_STREAM_RX3_COLOR_RGB_QUANTIZATION_RANGE()        (g_stDpMacStreamRx3ColorInfo.enumDigitalColorRGBQuantization)
#define SET_DP_MAC_STREAM_RX3_COLOR_RGB_QUANTIZATION_RANGE(x)       (g_stDpMacStreamRx3ColorInfo.enumDigitalColorRGBQuantization = (x))

#define SET_DP_MAC_STREAM_RX3_PORCH_COLOR_RGB()                     {\
                                                                        ScalerSetBit(PEE_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                        ScalerSetByte(PEE_52_MN_DPF_BG_RED_L, 0x00);\
                                                                        ScalerSetBit(PEE_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                        ScalerSetByte(PEE_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                        ScalerSetBit(PEE_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                        ScalerSetByte(PEE_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                    }

#define SET_DP_MAC_STREAM_RX3_PORCH_COLOR_YCC_LIMIT()\
                                                                    {\
                                                                        if(GET_DP_MAC_STREAM_RX3_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                        {\
                                                                            ScalerSetBit(PEE_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PEE_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PEE_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PEE_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PEE_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PEE_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PEE_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PEE_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PEE_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PEE_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PEE_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PEE_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                    }

#define SET_DP_MAC_STREAM_RX3_PORCH_COLOR_YCC_FULL()\
                                                                    {\
                                                                        if(GET_DP_MAC_STREAM_RX3_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                        {\
                                                                            ScalerSetBit(PEE_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PEE_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PEE_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PEE_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PEE_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PEE_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PEE_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PEE_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PEE_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                            ScalerSetByte(PEE_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PEE_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PEE_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                    }

#define SET_DP_MAC_STREAM_RX3_VFRONT_PORCH_REG_8B10B(x)             {ScalerSetByte(PEE_40_VS_FRONT_PORCH, ((x) & 0xFF));}

#define SET_DP_MAC_STREAM_RX3_V_HEIGHT_REG_8B10B(x)                 {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(PEE_4D_MN_DPF_VHT_M, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(PEE_4E_MN_DPF_VHT_L, LOBYTE(usLocalValue));\
                                                                    }

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX3_VFRONT_PORCH_REG_128B132B(x)          {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(PF1_38_VS_FRONT_PORCH_0, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(PF1_39_VS_FRONT_PORCH_1, LOBYTE(usLocalValue));\
                                                                    }

#define SET_DP_MAC_STREAM_RX3_V_HEIGHT_REG_128B132B(x)              {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(PF1_1C_MN_DPF_VHT_M, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(PF1_1D_MN_DPF_VHT_L, LOBYTE(usLocalValue));\
                                                                    }
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx3MiscCheckFail)
#define SET_DP_MAC_STREAM_RX3_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx3MiscCheckFail = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx3MiscCheckFail = _FALSE)
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx3FifoIrqTriggerCheck)
#define SET_DP_MAC_STREAM_RX3_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx3FifoIrqTriggerCheck = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx3FifoIrqTriggerCheck = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Pixel Mode Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX3_STREAM_OUTPUT_X2_CLK()                (g_stDpMacStreamRx3StreamInfo.b1DpStreamOutputX2Clk)

#define SET_DP_MAC_STREAM_RX3_STREAM_OUTPUT_X2_CLK()                {\
                                                                        g_stDpMacStreamRx3StreamInfo.b1DpStreamOutputX2Clk = _TRUE;\
                                                                        ScalerSetBit(PEE_A2_PLL_OUT_CONTROL, ~_BIT6, _BIT6);\
                                                                    }

#define CLR_DP_MAC_STREAM_RX3_STREAM_OUTPUT_X2_CLK()                {\
                                                                        g_stDpMacStreamRx3StreamInfo.b1DpStreamOutputX2Clk = _FALSE;\
                                                                        ScalerSetBit(PEE_A2_PLL_OUT_CONTROL, ~_BIT6, 0x00);\
                                                                    }

//--------------------------------------------------
// DP MAC OOR Info
//--------------------------------------------------
#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX3_JUDGE_OOR()                           (g_bDpMacStreamRx3JudgeOOR)
#define SET_DP_MAC_STREAM_RX3_JUDGE_OOR()                           (g_bDpMacStreamRx3JudgeOOR = _TRUE)
#define CLR_DP_MAC_STREAM_RX3_JUDGE_OOR()                           (g_bDpMacStreamRx3JudgeOOR = _FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile bit g_bDpMacStreamRx3CrcCalculate;
extern BYTE g_ucDpMacStreamRx3MSAFailRsetCount;
extern WORD g_usDpMacStreamRx3Vfrontporch;
extern EnumDDomainRegion g_enumDpMacStreamRx3IrqForceBackgrd;

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern volatile bit g_bDpMacStreamRx3MiscCheckFail;
#endif

extern StructDpStreamInfo g_stDpMacStreamRx3StreamInfo;
extern StructDpInfo g_stDpMacStreamRx3Info;

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx3SPDInfoFrameCtrl;
extern bit g_bDpMacStreamRx3LocalDimmingDisableControl;
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx3AdaptiveSyncInfoFrameCtrl;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx3HDRInfoFrameCtrl;
#endif

#if(_DP_MAC_RX3_ADVANCED_HDR10_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx3AdvancedHDR10InfoFrameCtrl;
#endif

#if(_DP_MAC_RX3_DM_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx3DMVsifInfoFrameCtrl;
#endif

#if(_AUDIO_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx3AudioInfoFrameCtrl;
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit g_bDpMacStreamRx3SourceTypeJudge;
#endif

extern bit g_bDpMacStreamRx3Vbid3Chg;

extern StructDigitalColorInfo g_stDpMacStreamRx3ColorInfo;
extern StructDigitalColorInfoChanged g_stDpMacStreamRx3ColorInfoChanged;
extern bit g_bDpMacStreamRx3VscSdpColorMode;
extern bit g_bDpMacStreamRx3InterlaceVtotalNum;

extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx3PpsSdpCtrl;
extern StructDpMacRxDscInfo g_stDpMacStreamRx3DscInfo;

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern bit g_bDpMacStreamRx3FifoIrqTriggerCheck;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
extern void ScalerDpMacStreamRx3Proc(void);
extern bit ScalerDpMacStreamRx3SetPLLFreqNf(DWORD ulPllTargetClockHz, StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit);
extern void ScalerDpMacStreamRx3SetPLLNfOffProc(DWORD ulPllVcoClockHz, BYTE ucNcode, BYTE ucpllo, BYTE ucdivs);
extern bit ScalerDpMacStreamRx3SetPLLNfOnProc(BYTE ucNcode, BYTE ucFcode_MSB4b, WORD usFcode_LSB16b, bit bPllVcoHighFreqStatus);
extern void ScalerDpMacStreamRx3SetPLLPGainClampValue(BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1);
extern void ScalerDpMacStreamRx3PLLPCodeSpreadCtrl(BYTE ucPCodeCtrl, BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx3SetPllTrackingMode(EnumDpTrackingMode enumDpTrackingMode, BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx3WaitVBlanking(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx3HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
extern void ScalerDpMacStreamRx3GetSdpPktData(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);
extern BYTE ScalerDpMacStreamRx3GetSdpInfoHB3(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx3SdpDataDetect(void);
extern void ScalerDpMacStreamRx3SdpPacketCheck(EnumDpSdpType enumDpSdpType);
extern bit ScalerDpMacStreamRx3InterlaceCheck(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3GetVideoInfo(void);
extern void ScalerDpMacStreamRx3SetColorInfo(void);
extern bit ScalerDpMacStreamRx3GetMsaTimingInfo(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx3SdpInitial(void);
extern void ScalerDpMacStreamRx3MacInitial(void);
extern void ScalerDpMacStreamRx3Polarity(void);

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacStreamRx3PowerProc(EnumPowerAction enumPowerAction);
#endif

extern EnumSourceType ScalerDpMacStreamRx3ScanInputPort(void);
extern void ScalerDpMacStreamRx3MacSetting(void);
extern bit ScalerDpMacStreamRx3GetVbidInfo(EnumDpVbidInfo enumDpVbidInfo);
extern UnionDpRxMsaValue ScalerDpMacStreamRx3GetMsaInfo(EnumDpRxMsaType enumDpRxMsaType);
extern bit ScalerDpMacStreamRx3StableDetect(void);
extern bit ScalerDpMacStreamRx3BsMissCheck(void);
extern BYTE ScalerDpMacStreamRx3StreamPreDetect(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx3StreamVideoSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx3StreamJudgeSetting(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx3StreamVesaVideoSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx3StreamPreDetectReset(void);
extern EnumDpMacRxSdpReceiveStates ScalerDpMacStreamRx3GetSdpReceived(EnumDpSdpType enumDpSdpType);
extern bit ScalerDpMacStreamRx3GetSdpChanged(EnumDpSdpType enumDpSdpType);
extern EnumDpMacRxSdpChangeEvent ScalerDpMacStreamRx3GetSdpChangeEvent(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx3AVMute(void);
extern EnumDpRxMacPixelMode ScalerDpMacStreamRx3InputPixelMode(void);
extern bit ScalerDpMacStreamRx3InterlaceModeConfig(BYTE ucInterlaceReference);
extern bit ScalerDpMacStreamRx3StreamClkRegenerate(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3TrackingSetting(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3GetMeasureLinkInfo(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx3StreamInfoSetting(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx3BsMissFlagClear(void);
extern void ScalerDpMacStreamRx3SetBsMissDetectIRQ(bit bEn);
extern void ScalerDpMacStreamRx3SetFifoIRQ(bit bEn);
extern void ScalerDpMacStreamRx3DisableFifoIRQ(void);
extern void ScalerDpMacStreamRx3SetFifoWD(bit bEn);
extern void ScalerDpMacStreamRx3DisableFifoWD(void);
extern bit ScalerDpMacStreamRx3GetFifoWDStatus(void);
extern void ScalerDpMacStreamRx3TimingInfoAdjust(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx3TimingInfoAdjustForReorderTracking(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx3SecDataBlockReset(void);
extern void ScalerDpMacStreamRx3SetNoVideoStreamIRQ(bit bEn);
extern void ScalerDpMacStreamRx3DisableNoVideoStreamIRQ(void);
extern void ScalerDpMacStreamRx3LowPowerProc(void);
extern bit ScalerDpMacStreamRx3CheckVgipVsBypass(void);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetSdpMetaSramRcvInitial(void);
extern void ScalerDpMacStreamRx3SdpMetaSramReset(void);
#endif

extern void ScalerDpMacStreamRx3CtsFifoReset(void);
extern void ScalerDpMacStreamRx3SdpIrqEnable(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern EnumDpMacRxDPFRegenMode ScalerDpMacStreamRx3GetDPFRegenMode(void);
extern void ScalerDpMacStreamRx3SetDPFRegenMode(EnumDpMacRxDPFRegenMode enumDpMacRxDPFRegenMode);

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetBsMissDetectStart(bit bEn);
#endif

#if((_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx3DscStatusReset(void);
extern void ScalerDpMacStreamRx3DscInitial(void);
#endif

extern bit ScalerDpMacStreamRx3DscStreamCheck(void);
extern WORD ScalerDpMacStreamRx3GetPpsElementInfo(EnumDpStreamPpsElement enumDpStreamPpsElement);

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetPpsSdpInfoDetectingDone(void);
extern bit ScalerDpMacStreamRx3DscStreamChangeCheck(void);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetHdrInfoDetectingDone(void);
extern void ScalerDpMacStreamRx3HdrInfoDataRemappingDisable(void);
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern void ScalerDpMacStreamRx3SetSpdInfoDetectingDone(void);
extern void ScalerDpMacStreamRx3SpdInfoDataRemappingDisable(void);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern DWORD ScalerDpMacStreamRx3GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
extern void ScalerDpMacStreamRx3GetSPDVfreqMaxMin(void);
extern void ScalerDpMacStreamRx3SetDrrMsaForLut(StructDpInfo *pstDpInfo);
#endif

extern DWORD ScalerDpMacStreamRx3GetHPeriod(void);
extern WORD ScalerDpMacStreamRx3GetHSW(void);
extern WORD ScalerDpMacStreamRx3GetVFreq(void);
extern WORD ScalerDpMacStreamRx3GetVPeriod(void);

#if(_AUDIO_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetAudioInfoDetectingDone(void);
#endif

#if(_DP_MAC_RX3_ADVANCED_HDR10_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetAdvancedHdr10InfoDetectingDone(void);
#endif

#if(_DP_MAC_RX3_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetDMVsifInfoDetectingDone(void);
#endif

#if(_DP_MAC_RX3_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3DscSetting(void);
extern bit ScalerDpMacStreamRx3GetDscReorder(void);
extern void ScalerDpMacStreamRx3DscSetStreamWD(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpMacStreamRx3DscSetStreamIRQ(EnumInputPort enumInputPort, bit bEnable);
extern bit ScalerDpMacStreamRx3DscChunkLengthCheck(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3PRModeSdpReset(void);
extern void ScalerDpMacStreamRx3PRModeCheckProc(EnumInputPort enumInputPort);
#endif

extern WORD ScalerDpMacStreamRx3GetDisplayFormat(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetColorSpaceChangeWD(bit bEn);
extern void ScalerDpMacStreamRx3SstSetMsaChangeIRQ(bit bEn);
extern bit ScalerDpMacStreamRx3MsaMiscChangeSupportCheck(void);
extern bit ScalerDpMacStreamRx3GetMsaDebounceStatus(void);
#endif

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3SetBsMissDetectPeriod(StructDpInfo *pstDpInfo);
#endif

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx3MacHighPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx3MacLowPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx3MacBsMissDetectIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx3SetNoVideoStreamIRQ_EXINT0(bit bEn);
extern bit ScalerDpMacStreamRx3GetFifoWDStatus_EXINT0(void);


///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern bit ScalerDpMacStreamRx3FifoCheck_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern BYTE ScalerDpMacStreamRx3StreamPreDetect_8b10b(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx3StreamVesaVideoSetting_8b10b(void);
extern WORD ScalerDpMacStreamRx3GetDisplayFormat_8b10b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);


//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3PRModeCrcCheck_8b10b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx3PRModeCrcCalculateEnable_8b10b_EXINT0(bit bEnable);
#endif

#if(_DP_MAC_RX3_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3DMPacketReCheck_8b10b_EXINT0(EnumInputPort enumInputPort);
#endif

extern void ScalerDpMacStreamRx3MacLowPriorityIntHandler_8b10b_EXINT0(void);
extern void ScalerDpMacStreamRx3MacHighPriorityIntHandler_8b10b_EXINT0(void);


///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////

#if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx3FifoCheck_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern BYTE ScalerDpMacStreamRx3StreamPreDetect_128b132b(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx3StreamVesaVideoSetting_128b132b(void);
extern WORD ScalerDpMacStreamRx3GetDisplayFormat_128b132b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

//--------------------------------------------------
// EXINT0 For 128B132B Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx3MacLowPriorityIntHandler_128b132b_EXINT0(void);
extern void ScalerDpMacStreamRx3MacHighPriorityIntHandler_128b132b_EXINT0(void);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3PRModeCrcCheck_128b132b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx3PRModeCrcCalculateEnable_128b132b_EXINT0(bit bEnable);
#endif

#if(_DP_MAC_RX3_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx3DMPacketReCheck_128b132b_EXINT0(EnumInputPort enumInputPort);
#endif
#endif // End of #if(_DP_MAC_RX3_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_MAC_RX3_SUPPORT == _ON))

