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
// ID Code      : ScalerDpMacStreamRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX0_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp CRC Information
//----------------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX0_CRC_CALCULATE()                       (g_bDpMacStreamRx0CrcCalculate)
#define SET_DP_MAC_STREAM_RX0_CRC_CALCULATE()                       (g_bDpMacStreamRx0CrcCalculate = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_CRC_CALCULATE()                       (g_bDpMacStreamRx0CrcCalculate = _FALSE)

#define GET_DP_MAC_STREAM_RX0_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx0MSAFailRsetCount)
#define ADD_DP_MAC_STREAM_RX0_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx0MSAFailRsetCount++)
#define CLR_DP_MAC_STREAM_RX0_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx0MSAFailRsetCount = 0)

#define GET_DP_MAC_STREAM_RX0_FORCE_BCKGRD_PATH()                   (g_enumDpMacStreamRx0IrqForceBackgrd & _DDOMAIN_RGN_ALL)
#define SET_DP_MAC_STREAM_RX0_FORCE_BCKGRD_PATH(x)                  (g_enumDpMacStreamRx0IrqForceBackgrd |= (x))
#define CLR_DP_MAC_STREAM_RX0_FORCE_BCKGRD_PATH(x)                  (g_enumDpMacStreamRx0IrqForceBackgrd &= (EnumDDomainRegion)~(x))

#define GET_DP_MAC_STREAM_RX0_VFRONT_PORCH()                        (g_usDpMacStreamRx0Vfrontporch)
#define SET_DP_MAC_STREAM_RX0_VFRONT_PORCH(x)                       (g_usDpMacStreamRx0Vfrontporch = (x))

#define SET_DP_MAC_STREAM_RX0_PORCH_COLOR_RGB()                     {\
                                                                        ScalerSetByte(PB5_51_MN_DPF_BG_RED_M, 0x00);\
                                                                        ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                        ScalerSetByte(PB5_53_MN_DPF_BG_GRN_M, 0x00);\
                                                                        ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                        ScalerSetByte(PB5_55_MN_DPF_BG_BLU_M, 0x00);\
                                                                        ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                    }

#define SET_DP_MAC_STREAM_RX0_PORCH_COLOR_YCC_LIMIT()\
                                                                    {\
                                                                        if(GET_DP_MAC_STREAM_RX0_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                        {\
                                                                            ScalerSetBit(PB5_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PB5_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PB5_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PB5_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PB5_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PB5_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                    }

#define SET_DP_MAC_STREAM_RX0_PORCH_COLOR_YCC_FULL()\
                                                                    {\
                                                                        if(GET_DP_MAC_STREAM_RX0_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                        {\
                                                                            ScalerSetBit(PB5_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PB5_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PB5_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PB5_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PB5_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                            ScalerSetByte(PB5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PB5_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                    }

#define SET_DP_MAC_STREAM_RX0_VFRONT_PORCH_REG_8B10B(x)             {ScalerSetByte(PB5_40_VS_FRONT_PORCH, ((x) & 0xFF));}

#define SET_DP_MAC_STREAM_RX0_V_HEIGHT_REG_8B10B(x)                 {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(PB5_4D_MN_DPF_VHT_M, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(PB5_4E_MN_DPF_VHT_L, LOBYTE(usLocalValue));\
                                                                    }

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX0_VFRONT_PORCH_REG_128B132B(x)          {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(P2_38_VS_FRONT_PORCH_0, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(P2_39_VS_FRONT_PORCH_1, LOBYTE(usLocalValue));\
                                                                    }

#define SET_DP_MAC_STREAM_RX0_V_HEIGHT_REG_128B132B(x)              {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(P2_1C_MN_DPF_VHT_M, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(P2_1D_MN_DPF_VHT_L, LOBYTE(usLocalValue));\
                                                                    }
#endif

#define GET_DP_MAC_STREAM_RX0_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx0VscSdpColorMode)
#define SET_DP_MAC_STREAM_RX0_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx0VscSdpColorMode = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx0VscSdpColorMode = _FALSE)

//--------------------------------------------------
// Macro of Dp Measure Pop Up Action
//--------------------------------------------------
// Delay 5us for Wait Hw Update Period to Prevent MCU Get wrong value, Update Period is 3T, T = 1/14.318M or 1/27M
#define SET_DP_MAC_STREAM_RX0_MEASURE_POP_UP_8B10B()                {\
                                                                        ScalerSetBit(PB5_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                                        DELAY_5US();\
                                                                    }

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX0_MEASURE_POP_UP_128B132B()             {\
                                                                        ScalerSetBit(P2_40_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                                        DELAY_5US();\
                                                                    }
#endif
//--------------------------------------------------
// Macro of DP Rx Interlace info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX0_INTERLACE_VTOTAL_NUMBER()             (g_bDpMacStreamRx0InterlaceVtotalNum)
#define SET_DP_MAC_STREAM_RX0_INTERLACE_VTOTAL_NUMBER(x)            (g_bDpMacStreamRx0InterlaceVtotalNum = (x))

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
#define GET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx0SPDInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx0SPDInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx0SPDInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_VERSION()              (g_stDpMacStreamRx0SPDInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_VERSION(x)             (g_stDpMacStreamRx0SPDInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_VERSION()              (g_stDpMacStreamRx0SPDInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx0SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx0SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx0SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx0SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx0SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX0_SPD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx0SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX0_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx0SPDInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX0_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx0SPDInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx0SPDInfoFrameCtrl.b1InfoDetecting = _FALSE)

#define GET_DP_MAC_STREAM_RX0_AMD_SPD_LOCAL_DIMMING()               (g_bDpMacStreamRx0LocalDimmingDisableControl)
#define SET_DP_MAC_STREAM_RX0_AMD_SPD_LOCAL_DIMMING(x)              (g_bDpMacStreamRx0LocalDimmingDisableControl = (x))
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_VERSION()            (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_VERSION(x)           (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_VERSION()            (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_CHANGE_EVENT()       (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_CHANGE_EVENT(x)      (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_CHANGE_EVENT()       (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_RECEIVED_STATE()     (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_RECEIVED_STATE(x)    (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_RECEIVED_STATE()     (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx0HDRInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx0HDRInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx0HDRInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_VERSION()              (g_stDpMacStreamRx0HDRInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_VERSION(x)             (g_stDpMacStreamRx0HDRInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_VERSION()              (g_stDpMacStreamRx0HDRInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx0HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx0HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx0HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx0HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx0HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX0_HDR_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx0HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX0_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx0HDRInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX0_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx0HDRInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx0HDRInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_MAC_RX0_ADVANCED_HDR10_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_ADVANCED_HDR10_RECEIVED_STATE()       (g_stDpMacStreamRx0AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX0_ADVANCED_HDR10_RECEIVED_STATE(x)      (g_stDpMacStreamRx0AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX0_ADVANCED_HDR10_RECEIVED_STATE()       (g_stDpMacStreamRx0AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX0_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx0AdvancedHDR10InfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX0_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx0AdvancedHDR10InfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx0AdvancedHDR10InfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_MAC_RX0_DM_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx0DMVsifInfoFrameCtrl.b1InfoFrameReceive)
#define SET_DP_MAC_STREAM_RX0_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx0DMVsifInfoFrameCtrl.b1InfoFrameReceive = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx0DMVsifInfoFrameCtrl.b1InfoFrameReceive = _FALSE)

#define GET_DP_MAC_STREAM_RX0_DM_VSIF_RECEIVED_STATE()              (g_stDpMacStreamRx0DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX0_DM_VSIF_RECEIVED_STATE(x)             (g_stDpMacStreamRx0DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX0_DM_VSIF_RECEIVED_STATE()              (g_stDpMacStreamRx0DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX0_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx0DMVsifInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX0_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx0DMVsifInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx0DMVsifInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_AUDIO_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx0AudioInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX0_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx0AudioInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx0AudioInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX0_AUD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx0AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX0_AUD_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx0AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX0_AUD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx0AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX0_AUD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx0AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX0_AUD_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx0AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX0_AUD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx0AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX0_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx0AudioInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX0_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx0AudioInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx0AudioInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#define GET_DP_MAC_STREAM_RX0_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx0PpsSdpCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX0_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx0PpsSdpCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx0PpsSdpCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX0_PPS_SDP_CHANGE_EVENT()                (g_stDpMacStreamRx0PpsSdpCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX0_PPS_SDP_CHANGE_EVENT(x)               (g_stDpMacStreamRx0PpsSdpCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX0_PPS_SDP_CHANGE_EVENT()                (g_stDpMacStreamRx0PpsSdpCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX0_PPS_SDP_RECEIVED_STATE()              (g_stDpMacStreamRx0PpsSdpCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX0_PPS_SDP_RECEIVED_STATE(x)             (g_stDpMacStreamRx0PpsSdpCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX0_PPS_SDP_RECEIVED_STATE()              (g_stDpMacStreamRx0PpsSdpCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX0_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx0PpsSdpCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX0_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx0PpsSdpCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx0PpsSdpCtrl.b1InfoDetecting = _FALSE)

#define GET_DP_MAC_STREAM_RX0_DSC_PIC_HEIGHT()                      (g_stDpMacStreamRx0DscInfo.usDscPicHeight)
#define SET_DP_MAC_STREAM_RX0_DSC_PIC_HEIGHT(x)                     (g_stDpMacStreamRx0DscInfo.usDscPicHeight = (x))
#define CLR_DP_MAC_STREAM_RX0_DSC_PIC_HEIGHT()                      (g_stDpMacStreamRx0DscInfo.usDscPicHeight = 0)

#define GET_DP_MAC_STREAM_RX0_DSC_PIC_WIDTH()                       (g_stDpMacStreamRx0DscInfo.usDscPicWidth)
#define SET_DP_MAC_STREAM_RX0_DSC_PIC_WIDTH(x)                      (g_stDpMacStreamRx0DscInfo.usDscPicWidth = (x))
#define CLR_DP_MAC_STREAM_RX0_DSC_PIC_WIDTH()                       (g_stDpMacStreamRx0DscInfo.usDscPicWidth = 0)

#define GET_DP_MAC_STREAM_RX0_DSC_SLICE_HEIGHT()                    (g_stDpMacStreamRx0DscInfo.usDscSliceHeight)
#define SET_DP_MAC_STREAM_RX0_DSC_SLICE_HEIGHT(x)                   (g_stDpMacStreamRx0DscInfo.usDscSliceHeight = (x))
#define CLR_DP_MAC_STREAM_RX0_DSC_SLICE_HEIGHT()                    (g_stDpMacStreamRx0DscInfo.usDscSliceHeight = 0)

#define GET_DP_MAC_STREAM_RX0_DSC_SLICE_WIDTH()                     (g_stDpMacStreamRx0DscInfo.usDscSliceWidth)
#define SET_DP_MAC_STREAM_RX0_DSC_SLICE_WIDTH(x)                    (g_stDpMacStreamRx0DscInfo.usDscSliceWidth = (x))
#define CLR_DP_MAC_STREAM_RX0_DSC_SLICE_WIDTH()                     (g_stDpMacStreamRx0DscInfo.usDscSliceWidth = 0)

#define GET_DP_MAC_STREAM_RX0_DSC_COLOR_BPP()                       (g_stDpMacStreamRx0DscInfo.usDscBitsPerPixel)
#define SET_DP_MAC_STREAM_RX0_DSC_COLOR_BPP(x)                      (g_stDpMacStreamRx0DscInfo.usDscBitsPerPixel = (x))
#define CLR_DP_MAC_STREAM_RX0_DSC_COLOR_BPP()                       (g_stDpMacStreamRx0DscInfo.usDscBitsPerPixel = 0)

#define GET_DP_MAC_STREAM_RX0_DSC_COLOR_BPC()                       (g_stDpMacStreamRx0DscInfo.b4DscBitPerComponent)
#define SET_DP_MAC_STREAM_RX0_DSC_COLOR_BPC(x)                      (g_stDpMacStreamRx0DscInfo.b4DscBitPerComponent = (x))
#define CLR_DP_MAC_STREAM_RX0_DSC_COLOR_BPC()                       (g_stDpMacStreamRx0DscInfo.b4DscBitPerComponent = 0)

#define GET_DP_MAC_STREAM_RX0_DSC_COLOR_NATIVE_420()                (g_stDpMacStreamRx0DscInfo.b1DscNative420)
#define SET_DP_MAC_STREAM_RX0_DSC_COLOR_NATIVE_420(x)               (g_stDpMacStreamRx0DscInfo.b1DscNative420 = (x))
#define CLR_DP_MAC_STREAM_RX0_DSC_COLOR_NATIVE_420()                (g_stDpMacStreamRx0DscInfo.b1DscNative420 = 0)

#define GET_DP_MAC_STREAM_RX0_DSC_COLOR_NATIVE_422()                (g_stDpMacStreamRx0DscInfo.b1DscNative422)
#define SET_DP_MAC_STREAM_RX0_DSC_COLOR_NATIVE_422(x)               (g_stDpMacStreamRx0DscInfo.b1DscNative422 = (x))
#define CLR_DP_MAC_STREAM_RX0_DSC_COLOR_NATIVE_422()                (g_stDpMacStreamRx0DscInfo.b1DscNative422 = 0)

#define GET_DP_MAC_STREAM_RX0_DSC_COLOR_SIMPLE_422()                (g_stDpMacStreamRx0DscInfo.b1DscSimple422)
#define SET_DP_MAC_STREAM_RX0_DSC_COLOR_SIMPLE_422(x)               (g_stDpMacStreamRx0DscInfo.b1DscSimple422 = (x))
#define CLR_DP_MAC_STREAM_RX0_DSC_COLOR_SIMPLE_422()                (g_stDpMacStreamRx0DscInfo.b1DscSimple422 = 0)

#define GET_DP_MAC_STREAM_RX0_DSC_COLOR_NATIVE_MODE()               (((GET_DP_MAC_STREAM_RX0_DSC_COLOR_NATIVE_420() == _TRUE) || (GET_DP_MAC_STREAM_RX0_DSC_COLOR_NATIVE_422() == _TRUE)) ? _TRUE : _FALSE)

//--------------------------------------------------
// Macro of VBID[3] Change to No-Video Flag
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX0_VBID3_CHANGED()                       (g_bDpMacStreamRx0Vbid3Chg)
#define SET_DP_MAC_STREAM_RX0_VBID3_CHANGED()                       (g_bDpMacStreamRx0Vbid3Chg = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_VBID3_CHANGED()                       (g_bDpMacStreamRx0Vbid3Chg = _FALSE)

//----------------------------------------------------------------------------
// Macro of Enlarge DP H Proch
//----------------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX0_H_PORCH_ENLARGE()                     (g_ucDpMacStreamRx0HPorchEnalrge)
#define SET_DP_MAC_STREAM_RX0_H_PORCH_ENLARGE(x)                    (g_ucDpMacStreamRx0HPorchEnalrge = (x))
#define CLR_DP_MAC_STREAM_RX0_H_PORCH_ENLARGE()                     (g_ucDpMacStreamRx0HPorchEnalrge = 0)

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//----------------------------------------------------------------------------
// Macro of Dp Lane Valid Check
//----------------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX0_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx0SourceTypeJudge)
#define SET_DP_MAC_STREAM_RX0_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx0SourceTypeJudge = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx0SourceTypeJudge = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Flag
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX0_NO_VIDEO_IRQ_STATUS_8B10B()           ((ScalerGetBit(PB6_3F_DP_IRQ_CTRL1, _BIT4) == _BIT4) ? _ENABLE : _DISABLE)

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_NO_VIDEO_IRQ_STATUS_128B132B()        ((ScalerGetBit(P1B_3B_DP_IRQ_CTRL1, _BIT4) == _BIT4) ? _ENABLE : _DISABLE)
#endif

//--------------------------------------------------
// DP MAC DSC Flag
//--------------------------------------------------
#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX0_DSC_SUPPORT_8B10B()                   {ScalerSetBit(PB5_91_DP_RSV1, ~(_BIT7 | _BIT6), _BIT7);}
#define GET_DP_MAC_STREAM_RX0_DSC_SUPPORT_8B10B()                   (ScalerGetBit(PB5_91_DP_RSV1, _BIT7) == _BIT7)
#define CLR_DP_MAC_STREAM_RX0_DSC_SUPPORT_8B10B()                   {ScalerSetBit(PB5_91_DP_RSV1, ~(_BIT7 | _BIT6), 0x00);}

#define SET_DP_MAC_STREAM_RX0_DSC_CHUNK_FROM_PPS_8B10B()            {ScalerSetBit(PB5_82_CPMODE, ~_BIT2, _BIT2);}

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX0_DSC_SUPPORT_128B132B()                {ScalerSetBit(P2_25_DSC_CTRL_0, ~_BIT7, _BIT7);}
#define GET_DP_MAC_STREAM_RX0_DSC_SUPPORT_128B132B()                (ScalerGetBit(P2_25_DSC_CTRL_0, _BIT7) == _BIT7)
#define CLR_DP_MAC_STREAM_RX0_DSC_SUPPORT_128B132B()                {ScalerSetBit(P2_25_DSC_CTRL_0, ~_BIT7, 0x00);}

#define SET_DP_MAC_STREAM_RX0_DSC_CHUNK_FROM_PPS_128B132B()         {ScalerSetBit(P2_25_DSC_CTRL_0, ~_BIT4, _BIT4);}
#endif
#endif

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX0_INTERLACE_VTT_FW_MODE_8B10B(x)        {\
                                                                        if((x) == _EVEN)\
                                                                        {\
                                                                            ScalerSetBit(PB5_91_DP_RSV1, ~(_BIT6 | _BIT4), _BIT4);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PB5_91_DP_RSV1, ~(_BIT6 | _BIT4), 0x00);\
                                                                        }\
                                                                    }
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX0_INTERLACE_VTT_FW_MODE_128B132B(x)     {\
                                                                        if((x) == _EVEN)\
                                                                        {\
                                                                            ScalerSetBit(P2_03_DPF_CTRL_3, ~_BIT3, _BIT3);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(P2_03_DPF_CTRL_3, ~_BIT3, 0x00);\
                                                                        }\
                                                                    }
#endif
#endif

//--------------------------------------------------
// DP MAC Stream Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX0_STREAM_PREDETECT()                    (g_stDpMacStreamRx0StreamInfo.b1StreamPreDetectFlag)
#define SET_DP_MAC_STREAM_RX0_STREAM_PREDETECT(x)                   (g_stDpMacStreamRx0StreamInfo.b1StreamPreDetectFlag = (x))

#define GET_DP_MAC_STREAM_RX0_STREAM_DATA_PATH()                    (g_stDpMacStreamRx0StreamInfo.enumDpStreamDataPath)
#define SET_DP_MAC_STREAM_RX0_STREAM_DATA_PATH(x)                   (g_stDpMacStreamRx0StreamInfo.enumDpStreamDataPath = (x))

#define GET_DP_MAC_STREAM_RX0_STREAM_INFO_TYPE()                    (g_stDpMacStreamRx0StreamInfo.enumDpStreamInfoType)
#define SET_DP_MAC_STREAM_RX0_STREAM_INFO_TYPE(x)                   (g_stDpMacStreamRx0StreamInfo.enumDpStreamInfoType = (x))

#define GET_DP_MAC_STREAM_RX0_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx0StreamInfo.b1StreamInfoTypeChangeFlag)
#define SET_DP_MAC_STREAM_RX0_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx0StreamInfo.b1StreamInfoTypeChangeFlag = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx0StreamInfo.b1StreamInfoTypeChangeFlag = _FALSE)

#define GET_DP_MAC_STREAM_RX0_STREAM_CLOCK()                        (g_stDpMacStreamRx0StreamInfo.ulStreamPreDetectPixelClock)
#define SET_DP_MAC_STREAM_RX0_STREAM_CLOCK(x)                       (g_stDpMacStreamRx0StreamInfo.ulStreamPreDetectPixelClock = (x))

#define GET_DP_MAC_STREAM_RX0_NATIVE_PIXEL_CLOCK()                  (g_stDpMacStreamRx0StreamInfo.ulDpStreamNativePixelClock)
#define SET_DP_MAC_STREAM_RX0_NATIVE_PIXEL_CLOCK(x)                 (g_stDpMacStreamRx0StreamInfo.ulDpStreamNativePixelClock = (x))

#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx0StreamInfo.b1FreeSyncEnable)
#define SET_DP_MAC_STREAM_RX0_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx0StreamInfo.b1FreeSyncEnable = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx0StreamInfo.b1FreeSyncEnable = _FALSE)
#endif

//--------------------------------------------------
// DP MAC PR Enable
//--------------------------------------------------
#if(_DP_PR_MODE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX0_PR_ENABLE_8B10B()                     {ScalerSetBit(PB6_4A_DUMMY_4A, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX0_PR_ENABLE_8B10B()                     (ScalerGetBit(PB6_4A_DUMMY_4A, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX0_PR_ENABLE_8B10B()                     {ScalerSetBit(PB6_4A_DUMMY_4A, ~_BIT0, 0x00);}

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX0_PR_ENABLE_128B132B()                  {ScalerSetBit(P1B_4A_VSC10, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX0_PR_ENABLE_128B132B()                  (ScalerGetBit(P1B_4A_VSC10, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX0_PR_ENABLE_128B132B()                  {ScalerSetBit(P1B_4A_VSC10, ~_BIT0, 0x00);}

#define GET_DP_MAC_STREAM_RX0_PR_ENABLE()                           (GET_DP_MAC_STREAM_RX0_PR_ENABLE_8B10B() || GET_DP_MAC_STREAM_RX0_PR_ENABLE_128B132B())
#else
#define GET_DP_MAC_STREAM_RX0_PR_ENABLE()                           (GET_DP_MAC_STREAM_RX0_PR_ENABLE_8B10B())
#endif
#endif

//--------------------------------------------------
// DP MAC ALPM Enable
//--------------------------------------------------
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX0_ALPM_ENABLE_8B10B()                   {ScalerSetBit(PB5_96_DP_ALPM0, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX0_ALPM_ENABLE_8B10B()                   (ScalerGetBit(PB5_96_DP_ALPM0, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX0_ALPM_ENABLE_8B10B()                   {ScalerSetBit(PB5_96_DP_ALPM0, ~_BIT0, 0x00);}

#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX0_ALPM_ENABLE_128B132B()                {ScalerSetBit(P2_57_DP_ALPM0, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX0_ALPM_ENABLE_128B132B()                (ScalerGetBit(P2_57_DP_ALPM0, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX0_ALPM_ENABLE_128B132B()                {ScalerSetBit(P2_57_DP_ALPM0, ~_BIT0, 0x00);}

#define GET_DP_MAC_STREAM_RX0_ALPM_ENABLE()                         (GET_DP_MAC_STREAM_RX0_ALPM_ENABLE_8B10B() || GET_DP_MAC_STREAM_RX0_ALPM_ENABLE_128B132B())
#else
#define GET_DP_MAC_STREAM_RX0_ALPM_ENABLE()                         (GET_DP_MAC_STREAM_RX0_ALPM_ENABLE_8B10B())
#endif
#endif

//--------------------------------------------------
// DP MAC Color Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX0_COLOR_SPACE_PREVALUE()                (g_stDpMacStreamRx0ColorInfo.ucDigitalColorSpacePreValue)
#define SET_DP_MAC_STREAM_RX0_COLOR_SPACE_PREVALUE(x)               (g_stDpMacStreamRx0ColorInfo.ucDigitalColorSpacePreValue = (x))

#define GET_DP_MAC_STREAM_RX0_COLOR_DEPTH_PREVALUE()                (g_stDpMacStreamRx0ColorInfo.b3DigitalColorDepthPreValue)
#define SET_DP_MAC_STREAM_RX0_COLOR_DEPTH_PREVALUE(x)               (g_stDpMacStreamRx0ColorInfo.b3DigitalColorDepthPreValue = (x))

#define GET_DP_MAC_STREAM_RX0_CONTENT_TYPE()                        (g_stDpMacStreamRx0ColorInfo.b3DigitalContentType)
#define SET_DP_MAC_STREAM_RX0_CONTENT_TYPE(x)                       (g_stDpMacStreamRx0ColorInfo.b3DigitalContentType = (x))

#define GET_DP_MAC_STREAM_RX0_COLORIMETRY_PREVALUE()                (g_stDpMacStreamRx0ColorInfo.b4DigitalColorimetryPreValue)
#define SET_DP_MAC_STREAM_RX0_COLORIMETRY_PREVALUE(x)               (g_stDpMacStreamRx0ColorInfo.b4DigitalColorimetryPreValue = (x))

#define GET_DP_MAC_STREAM_RX0_COLORIMETRY_EXT_PREVALUE()            (g_stDpMacStreamRx0ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_DP_MAC_STREAM_RX0_COLORIMETRY_EXT_PREVALUE(x)           (g_stDpMacStreamRx0ColorInfo.b4DigitalColorimetryExtPreValue = (x))

#define GET_DP_MAC_STREAM_RX0_QUANTIZATION_PREVALUE()               (g_stDpMacStreamRx0ColorInfo.b2DigitalQuantizationPreValue)
#define SET_DP_MAC_STREAM_RX0_QUANTIZATION_PREVALUE(x)              (g_stDpMacStreamRx0ColorInfo.b2DigitalQuantizationPreValue = (x))

#define GET_DP_MAC_STREAM_RX0_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx0ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_DP_MAC_STREAM_RX0_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx0ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx0ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX0_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx0ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_DP_MAC_STREAM_RX0_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx0ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx0ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX0_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx0ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_DP_MAC_STREAM_RX0_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx0ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx0ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX0_COLOR_SPACE()                         (g_stDpMacStreamRx0ColorInfo.enumDigitalColorSpace)
#define SET_DP_MAC_STREAM_RX0_COLOR_SPACE(x)                        (g_stDpMacStreamRx0ColorInfo.enumDigitalColorSpace = (x))

#define GET_DP_MAC_STREAM_RX0_COLOR_DEPTH()                         (g_stDpMacStreamRx0ColorInfo.ucDigitalColorDepthValue)
#define SET_DP_MAC_STREAM_RX0_COLOR_DEPTH(x)                        (g_stDpMacStreamRx0ColorInfo.ucDigitalColorDepthValue = (x))

#define GET_DP_MAC_STREAM_RX0_COLORIMETRY()                         (g_stDpMacStreamRx0ColorInfo.enumDigitalColorimetry)
#define SET_DP_MAC_STREAM_RX0_COLORIMETRY(x)                        (g_stDpMacStreamRx0ColorInfo.enumDigitalColorimetry = (x))

#define GET_DP_MAC_STREAM_RX0_EXT_COLORIMETRY()                     (g_stDpMacStreamRx0ColorInfo.enumDigitalColorimetryExt)
#define SET_DP_MAC_STREAM_RX0_EXT_COLORIMETRY(x)                    (g_stDpMacStreamRx0ColorInfo.enumDigitalColorimetryExt = (x))

#define GET_DP_MAC_STREAM_RX0_COLOR_YCC_QUANTIZATION_RANGE()        (g_stDpMacStreamRx0ColorInfo.enumDigitalColorYCCQuantization)
#define SET_DP_MAC_STREAM_RX0_COLOR_YCC_QUANTIZATION_RANGE(x)       (g_stDpMacStreamRx0ColorInfo.enumDigitalColorYCCQuantization = (x))

#define GET_DP_MAC_STREAM_RX0_COLOR_RGB_QUANTIZATION_RANGE()        (g_stDpMacStreamRx0ColorInfo.enumDigitalColorRGBQuantization)
#define SET_DP_MAC_STREAM_RX0_COLOR_RGB_QUANTIZATION_RANGE(x)       (g_stDpMacStreamRx0ColorInfo.enumDigitalColorRGBQuantization = (x))

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx0MiscCheckFail)
#define SET_DP_MAC_STREAM_RX0_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx0MiscCheckFail = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx0MiscCheckFail = _FALSE)
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx0FifoIrqTriggerCheck)
#define SET_DP_MAC_STREAM_RX0_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx0FifoIrqTriggerCheck = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx0FifoIrqTriggerCheck = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Pixel Mode Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX0_STREAM_OUTPUT_X2_CLK()                (g_stDpMacStreamRx0StreamInfo.b1DpStreamOutputX2Clk)

#define SET_DP_MAC_STREAM_RX0_STREAM_OUTPUT_X2_CLK()                {\
                                                                        g_stDpMacStreamRx0StreamInfo.b1DpStreamOutputX2Clk = _TRUE;\
                                                                        ScalerSetBit(PB5_A2_PLL_OUT_CONTROL, ~_BIT6, _BIT6);\
                                                                    }

#define CLR_DP_MAC_STREAM_RX0_STREAM_OUTPUT_X2_CLK()                {\
                                                                        g_stDpMacStreamRx0StreamInfo.b1DpStreamOutputX2Clk = _FALSE;\
                                                                        ScalerSetBit(PB5_A2_PLL_OUT_CONTROL, ~_BIT6, 0x00);\
                                                                    }

//--------------------------------------------------
// DP MAC OOR Info
//--------------------------------------------------
#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX0_JUDGE_OOR()                           (g_bDpMacStreamRx0JudgeOOR)
#define SET_DP_MAC_STREAM_RX0_JUDGE_OOR()                           (g_bDpMacStreamRx0JudgeOOR = _TRUE)
#define CLR_DP_MAC_STREAM_RX0_JUDGE_OOR()                           (g_bDpMacStreamRx0JudgeOOR = _FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile bit g_bDpMacStreamRx0CrcCalculate;
extern bit g_bDpMacStreamRx0InterlaceVtotalNum;

extern WORD g_usDpMacStreamRx0Vfrontporch;
extern EnumDDomainRegion g_enumDpMacStreamRx0IrqForceBackgrd;

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern volatile bit g_bDpMacStreamRx0MiscCheckFail;
#endif

extern bit g_bDpMacStreamRx0VscSdpColorMode;

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx0SPDInfoFrameCtrl;
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx0AdaptiveSyncInfoFrameCtrl;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx0HDRInfoFrameCtrl;
#endif

#if(_DP_MAC_RX0_ADVANCED_HDR10_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx0AdvancedHDR10InfoFrameCtrl;
#endif

#if(_DP_MAC_RX0_DM_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx0DMVsifInfoFrameCtrl;
#endif

#if(_AUDIO_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx0AudioInfoFrameCtrl;
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit g_bDpMacStreamRx0SourceTypeJudge;
#endif

extern StructDpStreamInfo g_stDpMacStreamRx0StreamInfo;
extern StructDpInfo g_stDpMacStreamRx0Info;

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern bit g_bDpMacStreamRx0LocalDimmingDisableControl;
#endif

extern bit g_bDpMacStreamRx0Vbid3Chg;

extern StructDigitalColorInfo g_stDpMacStreamRx0ColorInfo;
extern StructDigitalColorInfoChanged g_stDpMacStreamRx0ColorInfoChanged;

extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx0PpsSdpCtrl;
extern StructDpMacRxDscInfo g_stDpMacStreamRx0DscInfo;

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern bit g_bDpMacStreamRx0FifoIrqTriggerCheck;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
extern void ScalerDpMacStreamRx0MacInitial(void);
extern void ScalerDpMacStreamRx0SdpInitial(void);
extern void ScalerDpMacStreamRx0LowPowerProc(void);
extern void ScalerDpMacStreamRx0SecDataBlockReset(void);

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacStreamRx0PowerProc(EnumPowerAction enumPowerAction);
#endif

extern EnumSourceType ScalerDpMacStreamRx0ScanInputPort(void);
extern BYTE ScalerDpMacStreamRx0StreamPreDetect(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx0StreamInfoSetting(StructDpInfo *pstDpInfo);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx0StreamVideoSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx0StreamJudgeSetting(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx0StreamVesaVideoSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx0StreamPreDetectReset(void);

extern bit ScalerDpMacStreamRx0StableDetect(void);
extern void ScalerDpMacStreamRx0TimingInfoAdjust(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx0TimingInfoAdjustForReorderTracking(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx0AVMute(void);
extern void ScalerDpMacStreamRx0BsMissFlagClear(void);
extern void ScalerDpMacStreamRx0SetBsMissDetectIRQ(bit bEn);
extern void ScalerDpMacStreamRx0SetFifoIRQ(bit bEn);
extern void ScalerDpMacStreamRx0DisableFifoIRQ(void);
extern void ScalerDpMacStreamRx0SetFifoWD(bit bEn);
extern void ScalerDpMacStreamRx0DisableFifoWD(void);
extern bit ScalerDpMacStreamRx0GetFifoWDStatus(void);

extern bit ScalerDpMacStreamRx0GetVideoStream(void);
extern bit ScalerDpMacStreamRx0GetMsaTimingInfo(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0GetMeasureLinkInfo(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0BsMissCheck(void);
extern bit ScalerDpMacStreamRx0InterlaceCheck(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0GetVideoInfo(void);
extern void ScalerDpMacStreamRx0SetColorInfo(void);

extern bit ScalerDpMacStreamRx0StreamClkRegenerate(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0TrackingSetting(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx0SetPLLNfOffProc(DWORD ulPllVcoClockHz, BYTE ucNcode, BYTE ucpllo, BYTE ucdivs);
extern bit ScalerDpMacStreamRx0SetPLLNfOnProc(BYTE ucNcode, BYTE ucFcode_MSB4b, WORD usFcode_LSB16b, bit bPllVcoHighFreqStatus);


extern bit ScalerDpMacStreamRx0CheckVgipVsBypass(void);
extern void ScalerDpMacStreamRx0SetNoVideoStreamIRQ(bit bEn);
extern void ScalerDpMacStreamRx0DisableNoVideoStreamIRQ(void);
extern EnumDpRxMacPixelMode ScalerDpMacStreamRx0InputPixelMode(void);
extern bit ScalerDpMacStreamRx0InterlaceModeConfig(BYTE ucInterlaceReference);
extern void ScalerDpMacStreamRx0Polarity(void);
extern void ScalerDpMacStreamRx0MacSetting(void);
extern void ScalerDpMacStreamRx0SdpSetting(void);
extern bit ScalerDpMacStreamRx0GetVbidInfo(EnumDpVbidInfo enumDpVbidInfo);
extern UnionDpRxMsaValue ScalerDpMacStreamRx0GetMsaInfo(EnumDpRxMsaType enumDpRxMsaType);

extern void ScalerDpMacStreamRx0SdpDataDetect(void);
extern void ScalerDpMacStreamRx0SdpPacketCheck(EnumDpSdpType enumDpSdpType);
extern EnumDpMacRxSdpReceiveStates ScalerDpMacStreamRx0GetSdpReceived(EnumDpSdpType enumDpSdpType);
extern EnumDpMacRxSdpChangeEvent ScalerDpMacStreamRx0GetSdpChangeEvent(EnumDpSdpType enumDpSdpType);
extern bit ScalerDpMacStreamRx0GetSdpChanged(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx0GetSdpPktData(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);
extern BYTE ScalerDpMacStreamRx0GetSdpInfoHB3(EnumDpSdpType enumDpSdpType);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetSdpMetaSramRcvInitial(void);
extern void ScalerDpMacStreamRx0SdpMetaSramReset(void);
#endif

extern void ScalerDpMacStreamRx0CtsFifoReset(void);
extern bit ScalerDpMacStreamRx0VbiosMsaCheck(void);
extern void ScalerDpMacStreamRx0SdpIrqEnable(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern EnumDpMacRxDPFRegenMode ScalerDpMacStreamRx0GetDPFRegenMode(void);
extern void ScalerDpMacStreamRx0SetDPFRegenMode(EnumDpMacRxDPFRegenMode enumDpMacRxDPFRegenMode);

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetBsMissDetectStart(bit bEn);
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern void ScalerDpMacStreamRx0SetSpdInfoDetectingDone(void);
extern void ScalerDpMacStreamRx0SpdInfoDataRemappingDisable(void);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetPpsSdpInfoDetectingDone(void);
extern bit ScalerDpMacStreamRx0DscStreamChangeCheck(void);
#endif

#if(_DP_HDR10_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetHdrInfoDetectingDone(void);
extern void ScalerDpMacStreamRx0HdrInfoDataRemappingDisable(void);
#endif

#if(_AUDIO_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetAudioInfoDetectingDone(void);
#endif

#if(_DP_MAC_RX0_ADVANCED_HDR10_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetAdvancedHdr10InfoDetectingDone(void);
#endif

#if(_DP_MAC_RX0_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetDMVsifInfoDetectingDone(void);
#endif

#if((_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx0DscInitial(void);
extern void ScalerDpMacStreamRx0DscStatusReset(void);
#endif

extern bit ScalerDpMacStreamRx0DscStreamCheck(void);
extern WORD ScalerDpMacStreamRx0GetPpsElementInfo(EnumDpStreamPpsElement enumDpStreamPpsElement);

#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0DscSetting(void);
extern bit ScalerDpMacStreamRx0GetDscReorder(void);
extern void ScalerDpMacStreamRx0DscSetStreamWD(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpMacStreamRx0DscSetStreamIRQ(EnumInputPort enumInputPort, bit bEnable);
extern  bit ScalerDpMacStreamRx0DscChunkLengthCheck(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
#endif

extern WORD ScalerDpMacStreamRx0GetDisplayFormat(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

#if(_DP_FREESYNC_SUPPORT == _ON)
extern DWORD ScalerDpMacStreamRx0GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
extern void ScalerDpMacStreamRx0GetSPDVfreqMaxMin(void);
extern void ScalerDpMacStreamRx0SetDrrMsaForLut(StructDpInfo *pstDpInfo);
#endif

extern DWORD ScalerDpMacStreamRx0GetHPeriod(void);
extern WORD ScalerDpMacStreamRx0GetHSW(void);
extern WORD ScalerDpMacStreamRx0GetVFreq(void);
extern WORD ScalerDpMacStreamRx0GetVPeriod(void);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0PRModeInitial(void);
extern void ScalerDpMacStreamRx0PRModeSdpReset(void);
extern void ScalerDpMacStreamRx0PRModeCheckProc(EnumInputPort enumInputPort);
#endif

extern bit ScalerDpMacStreamRx0HdcpMeasureCheck(void);

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetBsMissDetectPeriod(StructDpInfo *pstDpInfo);
#endif

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx0MacHighPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx0MacLowPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx0MacBsMissDetectIntHandler_EXINT0(void);

extern void ScalerDpMacStreamRx0SetNoVideoStreamIRQ_EXINT0(bit bEn);
extern bit ScalerDpMacStreamRx0GetFifoWDStatus_EXINT0(void);

#if(_DP_MAC_RX0_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0DscSetStreamIRQ_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpMacStreamRx0DscSetStreamWD_EXINT0(EnumInputPort enumInputPort, bit bEnable);
#endif


///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern BYTE ScalerDpMacStreamRx0StreamPreDetect_8b10b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx0GetVideoInfo_8b10b(void);
extern bit ScalerDpMacStreamRx0GetVbidInfo_8b10b(EnumDpVbidInfo enumDpVbidInfo);
extern bit ScalerDpMacStreamRx0GetMsaTimingInfo_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0GetMeasureLinkInfo_8b10b(StructDpInfo *pstDpInfo);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx0StreamVesaVideoSetting_8b10b(void);
extern bit ScalerDpMacStreamRx0DisplayFormatSetting_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0StableDetect_8b10b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx0MiscCheck_8b10b(void);
extern bit ScalerDpMacStreamRx0MSAActiveChange_8b10b(void);
extern bit ScalerDpMacStreamRx0InterlaceCheck_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0InterlaceVtotalGetMSACheck_8b10b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx0InterlaceReset_8b10b(void);
extern bit ScalerDpMacStreamRx0FifoCheckProc_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx0CrcCalculate_8b10b(void);
extern void ScalerDpMacStreamRx0AVMute_8b10b(void);
extern void ScalerDpMacStreamRx0SetBsToHsDelay_8b10b(StructTimingInfo *pstDpTimingInfo);
extern WORD ScalerDpMacStreamRx0GetDisplayFormat_8b10b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0PRModeCheckProc_8b10b(EnumInputPort enumInputPort);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0SetColorSpaceChangeWD(bit bEn);
extern void ScalerDpMacStreamRx0SstSetMsaChangeIRQ(bit bEn);
extern bit ScalerDpMacStreamRx0MsaMiscChangeSupportCheck(void);
extern bit ScalerDpMacStreamRx0GetMsaDebounceStatus(void);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx0MacHighPriorityIntHandler_8b10b_EXINT0(void);
extern void ScalerDpMacStreamRx0MacLowPriorityIntHandler_8b10b_EXINT0(void);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0PRModeCrcCheck_8b10b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx0PRModeCrcCalculateEnable_8b10b_EXINT0(bit bEnable);
#endif

#if(_DP_MAC_RX0_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0DMPacketReCheck_8b10b_EXINT0(EnumInputPort enumInputPort);
#endif

///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
extern BYTE ScalerDpMacStreamRx0StreamPreDetect_128b132b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx0GetVideoInfo_128b132b(void);
extern bit ScalerDpMacStreamRx0GetVbidInfo_128b132b(EnumDpVbidInfo enumDpVbidInfo);
extern bit ScalerDpMacStreamRx0GetMsaTimingInfo_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0GetMeasureLinkInfo_128b132b(StructDpInfo *pstDpInfo);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx0StreamVesaVideoSetting_128b132b(void);
extern bit ScalerDpMacStreamRx0DisplayFormatSetting_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0StableDetect_128b132b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx0MiscCheck_128b132b(void);
extern bit ScalerDpMacStreamRx0MSAActiveChange_128b132b(void);
extern bit ScalerDpMacStreamRx0InterlaceCheck_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx0InterlaceVtotalGetMSACheck_128b132b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx0InterlaceReset_128b132b(void);
extern bit ScalerDpMacStreamRx0FifoCheckProc_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx0CrcCalculate_128b132b(void);
extern void ScalerDpMacStreamRx0AVMute_128b132b(void);
extern void ScalerDpMacStreamRx0SetBsToHsDelay_128b132b(StructTimingInfo *pstDpTimingInfo);
extern WORD ScalerDpMacStreamRx0GetDisplayFormat_128b132b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0PRModeCheckProc_128b132b(EnumInputPort enumInputPort);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx0MacLowPriorityIntHandler_128b132b_EXINT0(void);
extern void ScalerDpMacStreamRx0MacHighPriorityIntHandler_128b132b_EXINT0(void);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0PRModeCrcCheck_128b132b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx0PRModeCrcCalculateEnable_128b132b_EXINT0(bit bEnable);
#endif

#if(_DP_MAC_RX0_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx0DMPacketReCheck_128b132b_EXINT0(EnumInputPort enumInputPort);
#endif

#endif // End of (_DP_MAC_RX0_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif // End of (_DP_SUPPORT == _ON)
