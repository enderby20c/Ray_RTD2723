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
// ID Code      : ScalerDpMacStreamRx4Include.h No.0000
// Update Note  :
#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX4_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp CRC Information
//----------------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX4_CRC_CALCULATE()                       (g_bDpMacStreamRx4CrcCalculate)
#define SET_DP_MAC_STREAM_RX4_CRC_CALCULATE()                       (g_bDpMacStreamRx4CrcCalculate = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_CRC_CALCULATE()                       (g_bDpMacStreamRx4CrcCalculate = _FALSE)

#define GET_DP_MAC_STREAM_RX4_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx4MSAFailRsetCount)
#define ADD_DP_MAC_STREAM_RX4_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx4MSAFailRsetCount++)
#define CLR_DP_MAC_STREAM_RX4_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx4MSAFailRsetCount = 0)

#define GET_DP_MAC_STREAM_RX4_FORCE_BCKGRD_PATH()                   (g_enumDpMacStreamRx4IrqForceBackgrd & _DDOMAIN_RGN_ALL)
#define SET_DP_MAC_STREAM_RX4_FORCE_BCKGRD_PATH(x)                  (g_enumDpMacStreamRx4IrqForceBackgrd |= (x))
#define CLR_DP_MAC_STREAM_RX4_FORCE_BCKGRD_PATH(x)                  (g_enumDpMacStreamRx4IrqForceBackgrd &= (EnumDDomainRegion)~(x))

#define GET_DP_MAC_STREAM_RX4_VFRONT_PORCH()                        (g_usDpMacStreamRx4Vfrontporch)
#define SET_DP_MAC_STREAM_RX4_VFRONT_PORCH(x)                       (g_usDpMacStreamRx4Vfrontporch = (x))

// Delay 5us for Wait Hw Update Period to Prevent MCU Get wrong value, Update Period is 3T, T = 1/14.318M or 1/27M
#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX4_MEASURE_POP_UP_128B132B()             {\
                                                                        ScalerSetBit(PE0_40_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                                        DELAY_5US();\
                                                                    }
#endif
#define SET_DP_MAC_STREAM_RX4_MEASURE_POP_UP_8B10B()                {\
                                                                        ScalerSetBit(PA_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                                        DELAY_5US();\
                                                                    }

#define GET_DP_MAC_STREAM_RX4_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx4VscSdpColorMode)
#define SET_DP_MAC_STREAM_RX4_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx4VscSdpColorMode = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx4VscSdpColorMode = _FALSE)

#define GET_DP_MAC_STREAM_RX4_INTERLACE_VTOTAL_NUMBER()             (g_bDpMacStreamRx4InterlaceVtotalNum)
#define SET_DP_MAC_STREAM_RX4_INTERLACE_VTOTAL_NUMBER(x)            (g_bDpMacStreamRx4InterlaceVtotalNum = (x))

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
#define GET_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx4SPDInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx4SPDInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx4SPDInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_VERSION()              (g_stDpMacStreamRx4SPDInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_VERSION(x)             (g_stDpMacStreamRx4SPDInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_VERSION()              (g_stDpMacStreamRx4SPDInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx4SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx4SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx4SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx4SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx4SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX4_SPD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx4SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX4_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx4SPDInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX4_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx4SPDInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx4SPDInfoFrameCtrl.b1InfoDetecting = _FALSE)

#define GET_DP_MAC_STREAM_RX4_AMD_SPD_LOCAL_DIMMING()               (g_bDpMacStreamRx4LocalDimmingDisableControl)
#define SET_DP_MAC_STREAM_RX4_AMD_SPD_LOCAL_DIMMING(x)              (g_bDpMacStreamRx4LocalDimmingDisableControl = (x))
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_VERSION()            (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_VERSION(x)           (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_VERSION()            (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_CHANGE_EVENT()       (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_CHANGE_EVENT(x)      (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_CHANGE_EVENT()       (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_RECEIVED_STATE()     (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_RECEIVED_STATE(x)    (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_RECEIVED_STATE()     (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx4HDRInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx4HDRInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx4HDRInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_VERSION()              (g_stDpMacStreamRx4HDRInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_VERSION(x)             (g_stDpMacStreamRx4HDRInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_VERSION()              (g_stDpMacStreamRx4HDRInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx4HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx4HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx4HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx4HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx4HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX4_HDR_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx4HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX4_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx4HDRInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX4_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx4HDRInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx4HDRInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_MAC_RX4_ADVANCED_HDR10_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_ADVANCED_HDR10_RECEIVED_STATE()       (g_stDpMacStreamRx4AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX4_ADVANCED_HDR10_RECEIVED_STATE(x)      (g_stDpMacStreamRx4AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX4_ADVANCED_HDR10_RECEIVED_STATE()       (g_stDpMacStreamRx4AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX4_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx4AdvancedHDR10InfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX4_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx4AdvancedHDR10InfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx4AdvancedHDR10InfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_MAC_RX4_DM_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx4DMVsifInfoFrameCtrl.b1InfoFrameReceive)
#define SET_DP_MAC_STREAM_RX4_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx4DMVsifInfoFrameCtrl.b1InfoFrameReceive = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx4DMVsifInfoFrameCtrl.b1InfoFrameReceive = _FALSE)

#define GET_DP_MAC_STREAM_RX4_DM_VSIF_RECEIVED_STATE()              (g_stDpMacStreamRx4DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX4_DM_VSIF_RECEIVED_STATE(x)             (g_stDpMacStreamRx4DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX4_DM_VSIF_RECEIVED_STATE()              (g_stDpMacStreamRx4DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX4_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx4DMVsifInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX4_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx4DMVsifInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx4DMVsifInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_AUDIO_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx4AudioInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX4_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx4AudioInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx4AudioInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX4_AUD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx4AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX4_AUD_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx4AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX4_AUD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx4AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX4_AUD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx4AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX4_AUD_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx4AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX4_AUD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx4AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX4_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx4AudioInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX4_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx4AudioInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx4AudioInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#define GET_DP_MAC_STREAM_RX4_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx4PpsSdpCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX4_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx4PpsSdpCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx4PpsSdpCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX4_PPS_SDP_CHANGE_EVENT()                (g_stDpMacStreamRx4PpsSdpCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX4_PPS_SDP_CHANGE_EVENT(x)               (g_stDpMacStreamRx4PpsSdpCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX4_PPS_SDP_CHANGE_EVENT()                (g_stDpMacStreamRx4PpsSdpCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX4_PPS_SDP_RECEIVED_STATE()              (g_stDpMacStreamRx4PpsSdpCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX4_PPS_SDP_RECEIVED_STATE(x)             (g_stDpMacStreamRx4PpsSdpCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX4_PPS_SDP_RECEIVED_STATE()              (g_stDpMacStreamRx4PpsSdpCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX4_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx4PpsSdpCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX4_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx4PpsSdpCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx4PpsSdpCtrl.b1InfoDetecting = _FALSE)

#define GET_DP_MAC_STREAM_RX4_DSC_PIC_HEIGHT()                      (g_stDpMacStreamRx4DscInfo.usDscPicHeight)
#define SET_DP_MAC_STREAM_RX4_DSC_PIC_HEIGHT(x)                     (g_stDpMacStreamRx4DscInfo.usDscPicHeight = (x))
#define CLR_DP_MAC_STREAM_RX4_DSC_PIC_HEIGHT()                      (g_stDpMacStreamRx4DscInfo.usDscPicHeight = 0)

#define GET_DP_MAC_STREAM_RX4_DSC_PIC_WIDTH()                       (g_stDpMacStreamRx4DscInfo.usDscPicWidth)
#define SET_DP_MAC_STREAM_RX4_DSC_PIC_WIDTH(x)                      (g_stDpMacStreamRx4DscInfo.usDscPicWidth = (x))
#define CLR_DP_MAC_STREAM_RX4_DSC_PIC_WIDTH()                       (g_stDpMacStreamRx4DscInfo.usDscPicWidth = 0)

#define GET_DP_MAC_STREAM_RX4_DSC_SLICE_HEIGHT()                    (g_stDpMacStreamRx4DscInfo.usDscSliceHeight)
#define SET_DP_MAC_STREAM_RX4_DSC_SLICE_HEIGHT(x)                   (g_stDpMacStreamRx4DscInfo.usDscSliceHeight = (x))
#define CLR_DP_MAC_STREAM_RX4_DSC_SLICE_HEIGHT()                    (g_stDpMacStreamRx4DscInfo.usDscSliceHeight = 0)

#define GET_DP_MAC_STREAM_RX4_DSC_SLICE_WIDTH()                     (g_stDpMacStreamRx4DscInfo.usDscSliceWidth)
#define SET_DP_MAC_STREAM_RX4_DSC_SLICE_WIDTH(x)                    (g_stDpMacStreamRx4DscInfo.usDscSliceWidth = (x))
#define CLR_DP_MAC_STREAM_RX4_DSC_SLICE_WIDTH()                     (g_stDpMacStreamRx4DscInfo.usDscSliceWidth = 0)

#define GET_DP_MAC_STREAM_RX4_DSC_COLOR_BPP()                       (g_stDpMacStreamRx4DscInfo.usDscBitsPerPixel)
#define SET_DP_MAC_STREAM_RX4_DSC_COLOR_BPP(x)                      (g_stDpMacStreamRx4DscInfo.usDscBitsPerPixel = (x))
#define CLR_DP_MAC_STREAM_RX4_DSC_COLOR_BPP()                       (g_stDpMacStreamRx4DscInfo.usDscBitsPerPixel = 0)

#define GET_DP_MAC_STREAM_RX4_DSC_COLOR_BPC()                       (g_stDpMacStreamRx4DscInfo.b4DscBitPerComponent)
#define SET_DP_MAC_STREAM_RX4_DSC_COLOR_BPC(x)                      (g_stDpMacStreamRx4DscInfo.b4DscBitPerComponent = (x))
#define CLR_DP_MAC_STREAM_RX4_DSC_COLOR_BPC()                       (g_stDpMacStreamRx4DscInfo.b4DscBitPerComponent = 0)

#define GET_DP_MAC_STREAM_RX4_DSC_COLOR_NATIVE_420()                (g_stDpMacStreamRx4DscInfo.b1DscNative420)
#define SET_DP_MAC_STREAM_RX4_DSC_COLOR_NATIVE_420(x)               (g_stDpMacStreamRx4DscInfo.b1DscNative420 = (x))
#define CLR_DP_MAC_STREAM_RX4_DSC_COLOR_NATIVE_420()                (g_stDpMacStreamRx4DscInfo.b1DscNative420 = 0)

#define GET_DP_MAC_STREAM_RX4_DSC_COLOR_NATIVE_422()                (g_stDpMacStreamRx4DscInfo.b1DscNative422)
#define SET_DP_MAC_STREAM_RX4_DSC_COLOR_NATIVE_422(x)               (g_stDpMacStreamRx4DscInfo.b1DscNative422 = (x))
#define CLR_DP_MAC_STREAM_RX4_DSC_COLOR_NATIVE_422()                (g_stDpMacStreamRx4DscInfo.b1DscNative422 = 0)

#define GET_DP_MAC_STREAM_RX4_DSC_COLOR_SIMPLE_422()                (g_stDpMacStreamRx4DscInfo.b1DscSimple422)
#define SET_DP_MAC_STREAM_RX4_DSC_COLOR_SIMPLE_422(x)               (g_stDpMacStreamRx4DscInfo.b1DscSimple422 = (x))
#define CLR_DP_MAC_STREAM_RX4_DSC_COLOR_SIMPLE_422()                (g_stDpMacStreamRx4DscInfo.b1DscSimple422 = 0)

#define GET_DP_MAC_STREAM_RX4_DSC_COLOR_NATIVE_MODE()               (((GET_DP_MAC_STREAM_RX4_DSC_COLOR_NATIVE_420() == _TRUE) || (GET_DP_MAC_STREAM_RX4_DSC_COLOR_NATIVE_422() == _TRUE)) ? _TRUE : _FALSE)

//--------------------------------------------------
// Macro of VBID[3] Change to No-Video Flag
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX4_VBID3_CHANGED()                       (g_bDpMacStreamRx4Vbid3Chg)
#define SET_DP_MAC_STREAM_RX4_VBID3_CHANGED()                       (g_bDpMacStreamRx4Vbid3Chg = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_VBID3_CHANGED()                       (g_bDpMacStreamRx4Vbid3Chg = _FALSE)

//----------------------------------------------------------------------------
// Macro of Enlarge DP H Proch
//----------------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX4_H_PORCH_ENLARGE()                     (g_ucDpMacStreamRx4HPorchEnalrge)
#define SET_DP_MAC_STREAM_RX4_H_PORCH_ENLARGE(x)                    (g_ucDpMacStreamRx4HPorchEnalrge = (x))
#define CLR_DP_MAC_STREAM_RX4_H_PORCH_ENLARGE()                     (g_ucDpMacStreamRx4HPorchEnalrge = 0)

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//----------------------------------------------------------------------------
// Macro of Dp Lane Valid Check
//----------------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX4_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx4SourceTypeJudge)
#define SET_DP_MAC_STREAM_RX4_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx4SourceTypeJudge = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx4SourceTypeJudge = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Global IRQ Flag
//--------------------------------------------------
/*
#define GET_DP_MAC_RX4_GLOBAL_IRQ_FLAG()                            (ScalerGetBit(P6F_14_ADI_DP_IRQ2, _BIT5) == _BIT5)
*/

//--------------------------------------------------
// DP MAC Flag
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX4_NO_VIDEO_IRQ_STATUS_8B10B()           ((ScalerGetBit(P35_3F_DP_IRQ_CTRL1, _BIT4) == _BIT4) ? _ENABLE : _DISABLE)

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_NO_VIDEO_IRQ_STATUS_128B132B()        ((ScalerGetBit(PE1_3B_DP_IRQ_CTRL1, _BIT4) == _BIT4) ? _ENABLE : _DISABLE)
#endif

//--------------------------------------------------
// DP MAC DSC Flag
//--------------------------------------------------
#if((_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
#define SET_DP_MAC_STREAM_RX4_DSC_SUPPORT_8B10B()                   {ScalerSetBit(PA_91_DP_RSV1, ~(_BIT7 | _BIT6), _BIT7);}
#define GET_DP_MAC_STREAM_RX4_DSC_SUPPORT_8B10B()                   (ScalerGetBit(PA_91_DP_RSV1, _BIT7) == _BIT7)
#define CLR_DP_MAC_STREAM_RX4_DSC_SUPPORT_8B10B()                   {ScalerSetBit(PA_91_DP_RSV1, ~(_BIT7 | _BIT6), 0x00);}

#define SET_DP_MAC_STREAM_RX4_DSC_CHUNK_FROM_PPS_8B10B()            {ScalerSetBit(PA_82_CPMODE, ~_BIT2, _BIT2);}

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX4_DSC_SUPPORT_128B132B()                {ScalerSetBit(PE0_25_DSC_CTRL_0, ~_BIT7, _BIT7);}
#define GET_DP_MAC_STREAM_RX4_DSC_SUPPORT_128B132B()                (ScalerGetBit(PE0_25_DSC_CTRL_0, _BIT7) == _BIT7)
#define CLR_DP_MAC_STREAM_RX4_DSC_SUPPORT_128B132B()                {ScalerSetBit(PE0_25_DSC_CTRL_0, ~_BIT7, 0x00);}

#define SET_DP_MAC_STREAM_RX4_DSC_CHUNK_FROM_PPS_128B132B()         {ScalerSetBit(PE0_25_DSC_CTRL_0, ~_BIT4, _BIT4);}
#endif
#endif

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX4_INTERLACE_VTT_FW_MODE_128B132B(x)     {\
                                                                        if((x) == _EVEN)\
                                                                        {\
                                                                            ScalerSetBit(PE0_03_DPF_CTRL_3, ~_BIT3, _BIT3);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PE0_03_DPF_CTRL_3, ~_BIT3, 0x00);\
                                                                        }\
                                                                    }
#endif
#define SET_DP_MAC_STREAM_RX4_INTERLACE_VTT_FW_MODE_8B10B(x)        {\
                                                                        if((x) == _EVEN)\
                                                                        {\
                                                                            ScalerSetBit(PA_91_DP_RSV1, ~(_BIT6 | _BIT4), _BIT4);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PA_91_DP_RSV1, ~(_BIT6 | _BIT4), 0x00);\
                                                                        }\
                                                                    }
#endif

//--------------------------------------------------
// DP MAC Stream Info
//--------------------------------------------------

#define GET_DP_MAC_STREAM_RX4_STREAM_PREDETECT()                    (g_stDpMacStreamRx4StreamInfo.b1StreamPreDetectFlag)
#define SET_DP_MAC_STREAM_RX4_STREAM_PREDETECT(x)                   (g_stDpMacStreamRx4StreamInfo.b1StreamPreDetectFlag = (x))

#define GET_DP_MAC_STREAM_RX4_STREAM_DATA_PATH()                    (g_stDpMacStreamRx4StreamInfo.enumDpStreamDataPath)
#define SET_DP_MAC_STREAM_RX4_STREAM_DATA_PATH(x)                   (g_stDpMacStreamRx4StreamInfo.enumDpStreamDataPath = (x))

#define GET_DP_MAC_STREAM_RX4_STREAM_INFO_TYPE()                    (g_stDpMacStreamRx4StreamInfo.enumDpStreamInfoType)
#define SET_DP_MAC_STREAM_RX4_STREAM_INFO_TYPE(x)                   (g_stDpMacStreamRx4StreamInfo.enumDpStreamInfoType = (x))

#define GET_DP_MAC_STREAM_RX4_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx4StreamInfo.b1StreamInfoTypeChangeFlag)
#define SET_DP_MAC_STREAM_RX4_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx4StreamInfo.b1StreamInfoTypeChangeFlag = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx4StreamInfo.b1StreamInfoTypeChangeFlag = _FALSE)

#define GET_DP_MAC_STREAM_RX4_STREAM_CLOCK()                        (g_stDpMacStreamRx4StreamInfo.ulStreamPreDetectPixelClock)
#define SET_DP_MAC_STREAM_RX4_STREAM_CLOCK(x)                       (g_stDpMacStreamRx4StreamInfo.ulStreamPreDetectPixelClock = (x))

#define GET_DP_MAC_STREAM_RX4_NATIVE_PIXEL_CLOCK()                  (g_stDpMacStreamRx4StreamInfo.ulDpStreamNativePixelClock)
#define SET_DP_MAC_STREAM_RX4_NATIVE_PIXEL_CLOCK(x)                 (g_stDpMacStreamRx4StreamInfo.ulDpStreamNativePixelClock = (x))

#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx4StreamInfo.b1FreeSyncEnable)
#define SET_DP_MAC_STREAM_RX4_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx4StreamInfo.b1FreeSyncEnable = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx4StreamInfo.b1FreeSyncEnable = _FALSE)
#endif

//--------------------------------------------------
// DP MAC PR Enable
//--------------------------------------------------
#if(_DP_PR_MODE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX4_PR_ENABLE_8B10B()                     {ScalerSetBit(P35_4A_DUMMY_4A, ~(_BIT0), _BIT0);}
#define GET_DP_MAC_STREAM_RX4_PR_ENABLE_8B10B()                     (ScalerGetBit(P35_4A_DUMMY_4A, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX4_PR_ENABLE_8B10B()                     {ScalerSetBit(P35_4A_DUMMY_4A, ~(_BIT0), 0x00);}

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX4_PR_ENABLE_128B132B()                  {ScalerSetBit(PE1_4A_VSC10, ~(_BIT0), _BIT0);}
#define GET_DP_MAC_STREAM_RX4_PR_ENABLE_128B132B()                  (ScalerGetBit(PE1_4A_VSC10, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX4_PR_ENABLE_128B132B()                  {ScalerSetBit(PE1_4A_VSC10, ~(_BIT0), 0x00);}

#define GET_DP_MAC_STREAM_RX4_PR_ENABLE()                           (GET_DP_MAC_STREAM_RX4_PR_ENABLE_8B10B() || GET_DP_MAC_STREAM_RX4_PR_ENABLE_128B132B())
#else
#define GET_DP_MAC_STREAM_RX4_PR_ENABLE()                           (GET_DP_MAC_STREAM_RX4_PR_ENABLE_8B10B())
#endif
#endif

//--------------------------------------------------
// DP MAC ALPM Enable
//--------------------------------------------------
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX4_ALPM_ENABLE_8B10B()                   {ScalerSetBit(PA_96_DP_ALPM0, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX4_ALPM_ENABLE_8B10B()                   (ScalerGetBit(PA_96_DP_ALPM0, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX4_ALPM_ENABLE_8B10B()                   {ScalerSetBit(PA_96_DP_ALPM0, ~_BIT0, 0x00);}

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX4_ALPM_ENABLE_128B132B()                {ScalerSetBit(PE0_57_DP_ALPM0, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX4_ALPM_ENABLE_128B132B()                (ScalerGetBit(PE0_57_DP_ALPM0, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX4_ALPM_ENABLE_128B132B()                {ScalerSetBit(PE0_57_DP_ALPM0, ~_BIT0, 0x00);}

#define GET_DP_MAC_STREAM_RX4_ALPM_ENABLE()                         (GET_DP_MAC_STREAM_RX4_ALPM_ENABLE_8B10B() || GET_DP_MAC_STREAM_RX4_ALPM_ENABLE_128B132B())
#else
#define GET_DP_MAC_STREAM_RX4_ALPM_ENABLE()                         (GET_DP_MAC_STREAM_RX4_ALPM_ENABLE_8B10B())
#endif
#endif

//--------------------------------------------------
// DP MAC Color Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX4_COLOR_SPACE_PREVALUE()                (g_stDpMacStreamRx4ColorInfo.ucDigitalColorSpacePreValue)
#define SET_DP_MAC_STREAM_RX4_COLOR_SPACE_PREVALUE(x)               (g_stDpMacStreamRx4ColorInfo.ucDigitalColorSpacePreValue = (x))

#define GET_DP_MAC_STREAM_RX4_COLOR_DEPTH_PREVALUE()                (g_stDpMacStreamRx4ColorInfo.b3DigitalColorDepthPreValue)
#define SET_DP_MAC_STREAM_RX4_COLOR_DEPTH_PREVALUE(x)               (g_stDpMacStreamRx4ColorInfo.b3DigitalColorDepthPreValue = (x))

#define GET_DP_MAC_STREAM_RX4_CONTENT_TYPE()                        (g_stDpMacStreamRx4ColorInfo.b3DigitalContentType)
#define SET_DP_MAC_STREAM_RX4_CONTENT_TYPE(x)                       (g_stDpMacStreamRx4ColorInfo.b3DigitalContentType = (x))

#define GET_DP_MAC_STREAM_RX4_COLORIMETRY_PREVALUE()                (g_stDpMacStreamRx4ColorInfo.b4DigitalColorimetryPreValue)
#define SET_DP_MAC_STREAM_RX4_COLORIMETRY_PREVALUE(x)               (g_stDpMacStreamRx4ColorInfo.b4DigitalColorimetryPreValue = (x))

#define GET_DP_MAC_STREAM_RX4_COLORIMETRY_EXT_PREVALUE()            (g_stDpMacStreamRx4ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_DP_MAC_STREAM_RX4_COLORIMETRY_EXT_PREVALUE(x)           (g_stDpMacStreamRx4ColorInfo.b4DigitalColorimetryExtPreValue = (x))

#define GET_DP_MAC_STREAM_RX4_QUANTIZATION_PREVALUE()               (g_stDpMacStreamRx4ColorInfo.b2DigitalQuantizationPreValue)
#define SET_DP_MAC_STREAM_RX4_QUANTIZATION_PREVALUE(x)              (g_stDpMacStreamRx4ColorInfo.b2DigitalQuantizationPreValue = (x))

#define GET_DP_MAC_STREAM_RX4_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx4ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_DP_MAC_STREAM_RX4_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx4ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx4ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX4_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx4ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_DP_MAC_STREAM_RX4_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx4ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx4ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX4_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx4ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_DP_MAC_STREAM_RX4_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx4ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx4ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX4_COLOR_SPACE()                         (g_stDpMacStreamRx4ColorInfo.enumDigitalColorSpace)
#define SET_DP_MAC_STREAM_RX4_COLOR_SPACE(x)                        (g_stDpMacStreamRx4ColorInfo.enumDigitalColorSpace = (x))

#define GET_DP_MAC_STREAM_RX4_COLOR_DEPTH()                         (g_stDpMacStreamRx4ColorInfo.ucDigitalColorDepthValue)
#define SET_DP_MAC_STREAM_RX4_COLOR_DEPTH(x)                        (g_stDpMacStreamRx4ColorInfo.ucDigitalColorDepthValue = (x))

#define GET_DP_MAC_STREAM_RX4_COLORIMETRY()                         (g_stDpMacStreamRx4ColorInfo.enumDigitalColorimetry)
#define SET_DP_MAC_STREAM_RX4_COLORIMETRY(x)                        (g_stDpMacStreamRx4ColorInfo.enumDigitalColorimetry = (x))

#define GET_DP_MAC_STREAM_RX4_EXT_COLORIMETRY()                     (g_stDpMacStreamRx4ColorInfo.enumDigitalColorimetryExt)
#define SET_DP_MAC_STREAM_RX4_EXT_COLORIMETRY(x)                    (g_stDpMacStreamRx4ColorInfo.enumDigitalColorimetryExt = (x))

#define GET_DP_MAC_STREAM_RX4_COLOR_YCC_QUANTIZATION_RANGE()        (g_stDpMacStreamRx4ColorInfo.enumDigitalColorYCCQuantization)
#define SET_DP_MAC_STREAM_RX4_COLOR_YCC_QUANTIZATION_RANGE(x)       (g_stDpMacStreamRx4ColorInfo.enumDigitalColorYCCQuantization = (x))

#define GET_DP_MAC_STREAM_RX4_COLOR_RGB_QUANTIZATION_RANGE()        (g_stDpMacStreamRx4ColorInfo.enumDigitalColorRGBQuantization)
#define SET_DP_MAC_STREAM_RX4_COLOR_RGB_QUANTIZATION_RANGE(x)       (g_stDpMacStreamRx4ColorInfo.enumDigitalColorRGBQuantization = (x))

#define SET_DP_MAC_STREAM_RX4_PORCH_COLOR_RGB()                     {\
                                                                        ScalerSetBit(PA_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                        ScalerSetByte(PA_52_MN_DPF_BG_RED_L, 0x00);\
                                                                        ScalerSetBit(PA_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                        ScalerSetByte(PA_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                        ScalerSetBit(PA_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                        ScalerSetByte(PA_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                    }

#define SET_DP_MAC_STREAM_RX4_PORCH_COLOR_YCC_LIMIT()\
                                                                    {\
                                                                        if(GET_DP_MAC_STREAM_RX4_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                        {\
                                                                            ScalerSetBit(PA_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PA_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PA_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PA_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PA_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PA_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PA_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PA_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PA_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PA_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PA_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PA_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                    }

#define SET_DP_MAC_STREAM_RX4_PORCH_COLOR_YCC_FULL()\
                                                                    {\
                                                                        if(GET_DP_MAC_STREAM_RX4_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                        {\
                                                                            ScalerSetBit(PA_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PA_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PA_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PA_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PA_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PA_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PA_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PA_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PA_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                            ScalerSetByte(PA_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PA_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PA_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                    }

#define SET_DP_MAC_STREAM_RX4_VFRONT_PORCH_REG_8B10B(x)             {ScalerSetByte(PA_40_VS_FRONT_PORCH, ((x) & 0xFF));}

#define SET_DP_MAC_STREAM_RX4_V_HEIGHT_REG_8B10B(x)                 {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(PA_4D_MN_DPF_VHT_M, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(PA_4E_MN_DPF_VHT_L, LOBYTE(usLocalValue));\
                                                                    }

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX4_VFRONT_PORCH_REG_128B132B(x)          {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(PE0_38_VS_FRONT_PORCH_0, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(PE0_39_VS_FRONT_PORCH_1, LOBYTE(usLocalValue));\
                                                                    }

#define SET_DP_MAC_STREAM_RX4_V_HEIGHT_REG_128B132B(x)              {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(PE0_1C_MN_DPF_VHT_M, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(PE0_1D_MN_DPF_VHT_L, LOBYTE(usLocalValue));\
                                                                    }
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx4MiscCheckFail)
#define SET_DP_MAC_STREAM_RX4_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx4MiscCheckFail = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx4MiscCheckFail = _FALSE)
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx4FifoIrqTriggerCheck)
#define SET_DP_MAC_STREAM_RX4_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx4FifoIrqTriggerCheck = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx4FifoIrqTriggerCheck = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Pixel Mode Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX4_STREAM_OUTPUT_X2_CLK()                (g_stDpMacStreamRx4StreamInfo.b1DpStreamOutputX2Clk)

#define SET_DP_MAC_STREAM_RX4_STREAM_OUTPUT_X2_CLK()                {\
                                                                        g_stDpMacStreamRx4StreamInfo.b1DpStreamOutputX2Clk = _TRUE;\
                                                                        ScalerSetBit(PA_A2_PLL_OUT_CONTROL, ~_BIT6, _BIT6);\
                                                                    }

#define CLR_DP_MAC_STREAM_RX4_STREAM_OUTPUT_X2_CLK()                {\
                                                                        g_stDpMacStreamRx4StreamInfo.b1DpStreamOutputX2Clk = _FALSE;\
                                                                        ScalerSetBit(PA_A2_PLL_OUT_CONTROL, ~_BIT6, 0x00);\
                                                                    }

//--------------------------------------------------
// DP MAC OOR Info
//--------------------------------------------------
#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX4_JUDGE_OOR()                           (g_bDpMacStreamRx4JudgeOOR)
#define SET_DP_MAC_STREAM_RX4_JUDGE_OOR()                           (g_bDpMacStreamRx4JudgeOOR = _TRUE)
#define CLR_DP_MAC_STREAM_RX4_JUDGE_OOR()                           (g_bDpMacStreamRx4JudgeOOR = _FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile bit g_bDpMacStreamRx4CrcCalculate;
extern BYTE g_ucDpMacStreamRx4MSAFailRsetCount;
extern WORD g_usDpMacStreamRx4Vfrontporch;
extern EnumDDomainRegion g_enumDpMacStreamRx4IrqForceBackgrd;

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern volatile bit g_bDpMacStreamRx4MiscCheckFail;
#endif

extern StructDpStreamInfo g_stDpMacStreamRx4StreamInfo;
extern StructDpInfo g_stDpMacStreamRx4Info;

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx4SPDInfoFrameCtrl;
extern bit g_bDpMacStreamRx4LocalDimmingDisableControl;
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx4AdaptiveSyncInfoFrameCtrl;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx4HDRInfoFrameCtrl;
#endif

#if(_DP_MAC_RX4_ADVANCED_HDR10_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx4AdvancedHDR10InfoFrameCtrl;
#endif

#if(_DP_MAC_RX4_DM_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx4DMVsifInfoFrameCtrl;
#endif

#if(_AUDIO_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx4AudioInfoFrameCtrl;
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit g_bDpMacStreamRx4SourceTypeJudge;
#endif

extern bit g_bDpMacStreamRx4Vbid3Chg;

extern StructDigitalColorInfo g_stDpMacStreamRx4ColorInfo;
extern StructDigitalColorInfoChanged g_stDpMacStreamRx4ColorInfoChanged;
extern bit g_bDpMacStreamRx4VscSdpColorMode;
extern bit g_bDpMacStreamRx4InterlaceVtotalNum;

extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx4PpsSdpCtrl;
extern StructDpMacRxDscInfo g_stDpMacStreamRx4DscInfo;

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern bit g_bDpMacStreamRx4FifoIrqTriggerCheck;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
extern void ScalerDpMacStreamRx4Proc(void);
extern bit ScalerDpMacStreamRx4SetPLLFreqNf(DWORD ulPllTargetClockHz, StructDpInfo *pstDpInfo, DWORD ulDataPathSpeedLimit);
extern void ScalerDpMacStreamRx4SetPLLNfOffProc(DWORD ulPllVcoClockHz, BYTE ucNcode, BYTE ucpllo, BYTE ucdivs);
extern bit ScalerDpMacStreamRx4SetPLLNfOnProc(BYTE ucNcode, BYTE ucFcode_MSB4b, WORD usFcode_LSB16b, bit bPllVcoHighFreqStatus);
extern void ScalerDpMacStreamRx4SetPLLPGainClampValue(BYTE ucPGainB3, BYTE ucPGainB2, BYTE ucPGainB1);
extern void ScalerDpMacStreamRx4PLLPCodeSpreadCtrl(BYTE ucPCodeCtrl, BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx4SetPllTrackingMode(EnumDpTrackingMode enumDpTrackingMode, BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx4WaitVBlanking(BYTE ucOneFrameTime);
extern void ScalerDpMacStreamRx4HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacStreamRx4PowerProc(EnumPowerAction enumPowerAction);
#endif

extern void ScalerDpMacStreamRx4GetSdpPktData(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);
extern BYTE ScalerDpMacStreamRx4GetSdpInfoHB3(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx4SdpDataDetect(void);
extern void ScalerDpMacStreamRx4SdpPacketCheck(EnumDpSdpType enumDpSdpType);
extern bit ScalerDpMacStreamRx4InterlaceCheck(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4GetVideoInfo(void);
extern void ScalerDpMacStreamRx4SetColorInfo(void);
extern bit ScalerDpMacStreamRx4GetMsaTimingInfo(StructDpInfo *pstDpInfo);

extern void ScalerDpMacStreamRx4SdpInitial(void);
extern void ScalerDpMacStreamRx4MacInitial(void);
extern void ScalerDpMacStreamRx4Polarity(void);

extern EnumSourceType ScalerDpMacStreamRx4ScanInputPort(void);
extern void ScalerDpMacStreamRx4MacSetting(void);
extern bit ScalerDpMacStreamRx4GetVbidInfo(EnumDpVbidInfo enumDpVbidInfo);
extern UnionDpRxMsaValue ScalerDpMacStreamRx4GetMsaInfo(EnumDpRxMsaType enumDpRxMsaType);
extern bit ScalerDpMacStreamRx4StableDetect(void);
extern bit ScalerDpMacStreamRx4BsMissCheck(void);
extern BYTE ScalerDpMacStreamRx4StreamPreDetect(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx4StreamVideoSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx4StreamJudgeSetting(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx4StreamVesaVideoSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx4StreamPreDetectReset(void);
extern EnumDpMacRxSdpReceiveStates ScalerDpMacStreamRx4GetSdpReceived(EnumDpSdpType enumDpSdpType);
extern bit ScalerDpMacStreamRx4GetSdpChanged(EnumDpSdpType enumDpSdpType);
extern EnumDpMacRxSdpChangeEvent ScalerDpMacStreamRx4GetSdpChangeEvent(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx4AVMute(void);
extern EnumDpRxMacPixelMode ScalerDpMacStreamRx4InputPixelMode(void);
extern bit ScalerDpMacStreamRx4InterlaceModeConfig(BYTE ucInterlaceReference);
extern bit ScalerDpMacStreamRx4StreamClkRegenerate(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4TrackingSetting(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4GetMeasureLinkInfo(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx4StreamInfoSetting(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx4BsMissFlagClear(void);
extern void ScalerDpMacStreamRx4SetBsMissDetectIRQ(bit bEn);
extern void ScalerDpMacStreamRx4SetFifoIRQ(bit bEn);
extern void ScalerDpMacStreamRx4DisableFifoIRQ(void);
extern void ScalerDpMacStreamRx4SetFifoWD(bit bEn);
extern void ScalerDpMacStreamRx4DisableFifoWD(void);
extern bit ScalerDpMacStreamRx4GetFifoWDStatus(void);
extern void ScalerDpMacStreamRx4TimingInfoAdjust(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx4TimingInfoAdjustForReorderTracking(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx4SecDataBlockReset(void);
extern void ScalerDpMacStreamRx4SetNoVideoStreamIRQ(bit bEn);
extern void ScalerDpMacStreamRx4DisableNoVideoStreamIRQ(void);
extern void ScalerDpMacStreamRx4LowPowerProc(void);
extern bit ScalerDpMacStreamRx4CheckVgipVsBypass(void);
extern void ScalerDpMacStreamRx4CtsFifoReset(void);
extern void ScalerDpMacStreamRx4SdpIrqEnable(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern EnumDpMacRxDPFRegenMode ScalerDpMacStreamRx4GetDPFRegenMode(void);
extern void ScalerDpMacStreamRx4SetDPFRegenMode(EnumDpMacRxDPFRegenMode enumDpMacRxDPFRegenMode);

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4SetBsMissDetectStart(bit bEn);
#endif

#if((_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx4DscInitial(void);
extern void ScalerDpMacStreamRx4DscStatusReset(void);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4SetPpsSdpInfoDetectingDone(void);
extern bit ScalerDpMacStreamRx4DscStreamChangeCheck(void);
#endif

extern WORD ScalerDpMacStreamRx4GetDisplayFormat(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

#if(_DP_HDR10_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4SetHdrInfoDetectingDone(void);
extern void ScalerDpMacStreamRx4HdrInfoDataRemappingDisable(void);
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern void ScalerDpMacStreamRx4SetSpdInfoDetectingDone(void);
extern void ScalerDpMacStreamRx4SpdInfoDataRemappingDisable(void);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern DWORD ScalerDpMacStreamRx4GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
extern void ScalerDpMacStreamRx4GetSPDVfreqMaxMin(void);
extern void ScalerDpMacStreamRx4SetDrrMsaForLut(StructDpInfo *pstDpInfo);
#endif

extern DWORD ScalerDpMacStreamRx4GetHPeriod(void);
extern WORD ScalerDpMacStreamRx4GetHSW(void);
extern WORD ScalerDpMacStreamRx4GetVFreq(void);
extern WORD ScalerDpMacStreamRx4GetVPeriod(void);

#if(_AUDIO_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4SetAudioInfoDetectingDone(void);
#endif

#if(_DP_MAC_RX4_ADVANCED_HDR10_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4SetAdvancedHdr10InfoDetectingDone(void);
#endif

#if(_DP_MAC_RX4_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4SetDMVsifInfoDetectingDone(void);
#endif

extern bit ScalerDpMacStreamRx4DscStreamCheck(void);
extern WORD ScalerDpMacStreamRx4GetPpsElementInfo(EnumDpStreamPpsElement enumDpStreamPpsElement);

#if(_DP_MAC_RX4_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4DscSetting(void);
extern bit ScalerDpMacStreamRx4GetDscReorder(void);
extern bit ScalerDpMacStreamRx4DscChunkLengthCheck(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
extern void ScalerDpMacStreamRx4DscSetStreamWD(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpMacStreamRx4DscSetStreamIRQ(EnumInputPort enumInputPort, bit bEnable);
#endif

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4PRModeSdpReset(void);
extern void ScalerDpMacStreamRx4PRModeCheckProc(EnumInputPort enumInputPort);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4SetColorSpaceChangeWD(bit bEn);
extern void ScalerDpMacStreamRx4SstSetMsaChangeIRQ(bit bEn);
extern bit ScalerDpMacStreamRx4MsaMiscChangeSupportCheck(void);
extern bit ScalerDpMacStreamRx4GetMsaDebounceStatus(void);
#endif

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4SetBsMissDetectPeriod(StructDpInfo *pstDpInfo);
#endif

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx4MacHighPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx4MacLowPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx4MacBsMissDetectIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx4GetSdpPktData_EXINT0(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);
extern void ScalerDpMacStreamRx4SetNoVideoStreamIRQ_EXINT0(bit bEn);

///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern bit ScalerDpMacStreamRx4FifoCheck_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern BYTE ScalerDpMacStreamRx4StreamPreDetect_8b10b(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx4StreamVesaVideoSetting_8b10b(void);
extern WORD ScalerDpMacStreamRx4GetDisplayFormat_8b10b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4PRModeCrcCheck_8b10b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx4PRModeCrcCalculateEnable_8b10b_EXINT0(bit bEnable);
#endif

#if(_DP_MAC_RX4_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4DMPacketReCheck_8b10b_EXINT0(EnumInputPort enumInputPort);
#endif

extern void ScalerDpMacStreamRx4MacLowPriorityIntHandler_8b10b_EXINT0(void);
extern void ScalerDpMacStreamRx4MacHighPriorityIntHandler_8b10b_EXINT0(void);


///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////

#if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)
extern bit ScalerDpMacStreamRx4FifoCheck_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern BYTE ScalerDpMacStreamRx4StreamPreDetect_128b132b(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx4StreamVesaVideoSetting_128b132b(void);
extern WORD ScalerDpMacStreamRx4GetDisplayFormat_128b132b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

//--------------------------------------------------
// EXINT0 For 128B132B Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx4MacLowPriorityIntHandler_128b132b_EXINT0(void);
extern void ScalerDpMacStreamRx4MacHighPriorityIntHandler_128b132b_EXINT0(void);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4PRModeCrcCheck_128b132b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx4PRModeCrcCalculateEnable_128b132b_EXINT0(bit bEnable);
#endif

#if(_DP_MAC_RX4_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx4DMPacketReCheck_128b132b_EXINT0(EnumInputPort enumInputPort);
#endif
#endif // End of #if(_DP_MAC_RX4_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_MAC_RX4_SUPPORT == _ON))
