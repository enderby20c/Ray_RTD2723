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
// ID Code      : ScalerDpMacStreamRx2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX2_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp CRC Information
//----------------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX2_CRC_CALCULATE()                       (g_bDpMacStreamRx2CrcCalculate)
#define SET_DP_MAC_STREAM_RX2_CRC_CALCULATE()                       (g_bDpMacStreamRx2CrcCalculate = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_CRC_CALCULATE()                       (g_bDpMacStreamRx2CrcCalculate = _FALSE)

#define GET_DP_MAC_STREAM_RX2_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx2MSAFailRsetCount)
#define ADD_DP_MAC_STREAM_RX2_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx2MSAFailRsetCount++)
#define CLR_DP_MAC_STREAM_RX2_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx2MSAFailRsetCount = 0)

#define GET_DP_MAC_STREAM_RX2_FORCE_BCKGRD_PATH()                   (g_enumDpMacStreamRx2IrqForceBackgrd & _DDOMAIN_RGN_ALL)
#define SET_DP_MAC_STREAM_RX2_FORCE_BCKGRD_PATH(x)                  (g_enumDpMacStreamRx2IrqForceBackgrd |= (x))
#define CLR_DP_MAC_STREAM_RX2_FORCE_BCKGRD_PATH(x)                  (g_enumDpMacStreamRx2IrqForceBackgrd &= (EnumDDomainRegion)~(x))

#define GET_DP_MAC_STREAM_RX2_VFRONT_PORCH()                        (g_usDpMacStreamRx2Vfrontporch)
#define SET_DP_MAC_STREAM_RX2_VFRONT_PORCH(x)                       (g_usDpMacStreamRx2Vfrontporch = (x))

#define SET_DP_MAC_STREAM_RX2_PORCH_COLOR_RGB()                     {\
                                                                        ScalerSetByte(PC6_51_MN_DPF_BG_RED_M, 0x00);\
                                                                        ScalerSetByte(PC6_52_MN_DPF_BG_RED_L, 0x00);\
                                                                        ScalerSetByte(PC6_53_MN_DPF_BG_GRN_M, 0x00);\
                                                                        ScalerSetByte(PC6_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                        ScalerSetByte(PC6_55_MN_DPF_BG_BLU_M, 0x00);\
                                                                        ScalerSetByte(PC6_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                    }

#define SET_DP_MAC_STREAM_RX2_PORCH_COLOR_YCC_LIMIT()\
                                                                    {\
                                                                        if(GET_DP_MAC_STREAM_RX2_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                        {\
                                                                            ScalerSetBit(PC6_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PC6_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PC6_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PC6_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PC6_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PC6_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PC6_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PC6_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PC6_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PC6_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PC6_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PC6_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                    }

#define SET_DP_MAC_STREAM_RX2_PORCH_COLOR_YCC_FULL()\
                                                                    {\
                                                                        if(GET_DP_MAC_STREAM_RX2_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                        {\
                                                                            ScalerSetBit(PC6_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PC6_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PC6_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PC6_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PC6_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PC6_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PC6_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PC6_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PC6_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                            ScalerSetByte(PC6_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PC6_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PC6_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                    }

#define SET_DP_MAC_STREAM_RX2_VFRONT_PORCH_REG_8B10B(x)             {ScalerSetByte(PC6_40_VS_FRONT_PORCH, ((x) & 0xFF));}

#define SET_DP_MAC_STREAM_RX2_V_HEIGHT_REG_8B10B(x)                 {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(PC6_4D_MN_DPF_VHT_M, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(PC6_4E_MN_DPF_VHT_L, LOBYTE(usLocalValue));\
                                                                    }

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX2_VFRONT_PORCH_REG_128B132B(x)          {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(PD3_38_VS_FRONT_PORCH_0, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(PD3_39_VS_FRONT_PORCH_1, LOBYTE(usLocalValue));\
                                                                    }

#define SET_DP_MAC_STREAM_RX2_V_HEIGHT_REG_128B132B(x)              {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(PD3_1C_MN_DPF_VHT_M, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(PD3_1D_MN_DPF_VHT_L, LOBYTE(usLocalValue));\
                                                                    }
#endif

#define GET_DP_MAC_STREAM_RX2_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx2VscSdpColorMode)
#define SET_DP_MAC_STREAM_RX2_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx2VscSdpColorMode = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx2VscSdpColorMode = _FALSE)

//--------------------------------------------------
// Macro of Dp Measure Pop Up Action
//--------------------------------------------------
// Delay 5us for Wait Hw Update Period to Prevent MCU Get wrong value, Update Period is 3T, T = 1/14.318M or 1/27M
#define SET_DP_MAC_STREAM_RX2_MEASURE_POP_UP_8B10B()                {\
                                                                        ScalerSetBit(PC6_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                                        DELAY_5US();\
                                                                    }

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX2_MEASURE_POP_UP_128B132B()             {\
                                                                        ScalerSetBit(PD3_40_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                                        DELAY_5US();\
                                                                    }
#endif
//--------------------------------------------------
// Macro of DP Rx Interlace info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX2_INTERLACE_VTOTAL_NUMBER()             (g_bDpMacStreamRx2InterlaceVtotalNum)
#define SET_DP_MAC_STREAM_RX2_INTERLACE_VTOTAL_NUMBER(x)            (g_bDpMacStreamRx2InterlaceVtotalNum = (x))

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
#define GET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx2SPDInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx2SPDInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx2SPDInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_VERSION()              (g_stDpMacStreamRx2SPDInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_VERSION(x)             (g_stDpMacStreamRx2SPDInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_VERSION()              (g_stDpMacStreamRx2SPDInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx2SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx2SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx2SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx2SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx2SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX2_SPD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx2SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX2_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx2SPDInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX2_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx2SPDInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx2SPDInfoFrameCtrl.b1InfoDetecting = _FALSE)

#define GET_DP_MAC_STREAM_RX2_AMD_SPD_LOCAL_DIMMING()               (g_bDpMacStreamRx2LocalDimmingDisableControl)
#define SET_DP_MAC_STREAM_RX2_AMD_SPD_LOCAL_DIMMING(x)              (g_bDpMacStreamRx2LocalDimmingDisableControl = (x))
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_VERSION()            (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_VERSION(x)           (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_VERSION()            (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_CHANGE_EVENT()       (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_CHANGE_EVENT(x)      (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_CHANGE_EVENT()       (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_RECEIVED_STATE()     (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_RECEIVED_STATE(x)    (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_RECEIVED_STATE()     (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx2HDRInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx2HDRInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx2HDRInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_VERSION()              (g_stDpMacStreamRx2HDRInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_VERSION(x)             (g_stDpMacStreamRx2HDRInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_VERSION()              (g_stDpMacStreamRx2HDRInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx2HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx2HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx2HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx2HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx2HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX2_HDR_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx2HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX2_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx2HDRInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX2_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx2HDRInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx2HDRInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_MAC_RX2_ADVANCED_HDR10_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_ADVANCED_HDR10_RECEIVED_STATE()       (g_stDpMacStreamRx2AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX2_ADVANCED_HDR10_RECEIVED_STATE(x)      (g_stDpMacStreamRx2AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX2_ADVANCED_HDR10_RECEIVED_STATE()       (g_stDpMacStreamRx2AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX2_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx2AdvancedHDR10InfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX2_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx2AdvancedHDR10InfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx2AdvancedHDR10InfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_MAC_RX2_DM_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx2DMVsifInfoFrameCtrl.b1InfoFrameReceive)
#define SET_DP_MAC_STREAM_RX2_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx2DMVsifInfoFrameCtrl.b1InfoFrameReceive = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx2DMVsifInfoFrameCtrl.b1InfoFrameReceive = _FALSE)

#define GET_DP_MAC_STREAM_RX2_DM_VSIF_RECEIVED_STATE()              (g_stDpMacStreamRx2DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX2_DM_VSIF_RECEIVED_STATE(x)             (g_stDpMacStreamRx2DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX2_DM_VSIF_RECEIVED_STATE()              (g_stDpMacStreamRx2DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX2_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx2DMVsifInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX2_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx2DMVsifInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx2DMVsifInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_AUDIO_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx2AudioInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX2_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx2AudioInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx2AudioInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX2_AUD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx2AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX2_AUD_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx2AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX2_AUD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx2AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX2_AUD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx2AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX2_AUD_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx2AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX2_AUD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx2AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX2_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx2AudioInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX2_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx2AudioInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx2AudioInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#define GET_DP_MAC_STREAM_RX2_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx2PpsSdpCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX2_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx2PpsSdpCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx2PpsSdpCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX2_PPS_SDP_CHANGE_EVENT()                (g_stDpMacStreamRx2PpsSdpCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX2_PPS_SDP_CHANGE_EVENT(x)               (g_stDpMacStreamRx2PpsSdpCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX2_PPS_SDP_CHANGE_EVENT()                (g_stDpMacStreamRx2PpsSdpCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX2_PPS_SDP_RECEIVED_STATE()              (g_stDpMacStreamRx2PpsSdpCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX2_PPS_SDP_RECEIVED_STATE(x)             (g_stDpMacStreamRx2PpsSdpCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX2_PPS_SDP_RECEIVED_STATE()              (g_stDpMacStreamRx2PpsSdpCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX2_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx2PpsSdpCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX2_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx2PpsSdpCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx2PpsSdpCtrl.b1InfoDetecting = _FALSE)

#define GET_DP_MAC_STREAM_RX2_DSC_PIC_HEIGHT()                      (g_stDpMacStreamRx2DscInfo.usDscPicHeight)
#define SET_DP_MAC_STREAM_RX2_DSC_PIC_HEIGHT(x)                     (g_stDpMacStreamRx2DscInfo.usDscPicHeight = (x))
#define CLR_DP_MAC_STREAM_RX2_DSC_PIC_HEIGHT()                      (g_stDpMacStreamRx2DscInfo.usDscPicHeight = 0)

#define GET_DP_MAC_STREAM_RX2_DSC_PIC_WIDTH()                       (g_stDpMacStreamRx2DscInfo.usDscPicWidth)
#define SET_DP_MAC_STREAM_RX2_DSC_PIC_WIDTH(x)                      (g_stDpMacStreamRx2DscInfo.usDscPicWidth = (x))
#define CLR_DP_MAC_STREAM_RX2_DSC_PIC_WIDTH()                       (g_stDpMacStreamRx2DscInfo.usDscPicWidth = 0)

#define GET_DP_MAC_STREAM_RX2_DSC_SLICE_HEIGHT()                    (g_stDpMacStreamRx2DscInfo.usDscSliceHeight)
#define SET_DP_MAC_STREAM_RX2_DSC_SLICE_HEIGHT(x)                   (g_stDpMacStreamRx2DscInfo.usDscSliceHeight = (x))
#define CLR_DP_MAC_STREAM_RX2_DSC_SLICE_HEIGHT()                    (g_stDpMacStreamRx2DscInfo.usDscSliceHeight = 0)

#define GET_DP_MAC_STREAM_RX2_DSC_SLICE_WIDTH()                     (g_stDpMacStreamRx2DscInfo.usDscSliceWidth)
#define SET_DP_MAC_STREAM_RX2_DSC_SLICE_WIDTH(x)                    (g_stDpMacStreamRx2DscInfo.usDscSliceWidth = (x))
#define CLR_DP_MAC_STREAM_RX2_DSC_SLICE_WIDTH()                     (g_stDpMacStreamRx2DscInfo.usDscSliceWidth = 0)

#define GET_DP_MAC_STREAM_RX2_DSC_COLOR_BPP()                       (g_stDpMacStreamRx2DscInfo.usDscBitsPerPixel)
#define SET_DP_MAC_STREAM_RX2_DSC_COLOR_BPP(x)                      (g_stDpMacStreamRx2DscInfo.usDscBitsPerPixel = (x))
#define CLR_DP_MAC_STREAM_RX2_DSC_COLOR_BPP()                       (g_stDpMacStreamRx2DscInfo.usDscBitsPerPixel = 0)

#define GET_DP_MAC_STREAM_RX2_DSC_COLOR_BPC()                       (g_stDpMacStreamRx2DscInfo.b4DscBitPerComponent)
#define SET_DP_MAC_STREAM_RX2_DSC_COLOR_BPC(x)                      (g_stDpMacStreamRx2DscInfo.b4DscBitPerComponent = (x))
#define CLR_DP_MAC_STREAM_RX2_DSC_COLOR_BPC()                       (g_stDpMacStreamRx2DscInfo.b4DscBitPerComponent = 0)

#define GET_DP_MAC_STREAM_RX2_DSC_COLOR_NATIVE_420()                (g_stDpMacStreamRx2DscInfo.b1DscNative420)
#define SET_DP_MAC_STREAM_RX2_DSC_COLOR_NATIVE_420(x)               (g_stDpMacStreamRx2DscInfo.b1DscNative420 = (x))
#define CLR_DP_MAC_STREAM_RX2_DSC_COLOR_NATIVE_420()                (g_stDpMacStreamRx2DscInfo.b1DscNative420 = 0)

#define GET_DP_MAC_STREAM_RX2_DSC_COLOR_NATIVE_422()                (g_stDpMacStreamRx2DscInfo.b1DscNative422)
#define SET_DP_MAC_STREAM_RX2_DSC_COLOR_NATIVE_422(x)               (g_stDpMacStreamRx2DscInfo.b1DscNative422 = (x))
#define CLR_DP_MAC_STREAM_RX2_DSC_COLOR_NATIVE_422()                (g_stDpMacStreamRx2DscInfo.b1DscNative422 = 0)

#define GET_DP_MAC_STREAM_RX2_DSC_COLOR_SIMPLE_422()                (g_stDpMacStreamRx2DscInfo.b1DscSimple422)
#define SET_DP_MAC_STREAM_RX2_DSC_COLOR_SIMPLE_422(x)               (g_stDpMacStreamRx2DscInfo.b1DscSimple422 = (x))
#define CLR_DP_MAC_STREAM_RX2_DSC_COLOR_SIMPLE_422()                (g_stDpMacStreamRx2DscInfo.b1DscSimple422 = 0)

#define GET_DP_MAC_STREAM_RX2_DSC_COLOR_NATIVE_MODE()               (((GET_DP_MAC_STREAM_RX2_DSC_COLOR_NATIVE_420() == _TRUE) || (GET_DP_MAC_STREAM_RX2_DSC_COLOR_NATIVE_422() == _TRUE)) ? _TRUE : _FALSE)

//--------------------------------------------------
// Macro of VBID[3] Change to No-Video Flag
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX2_VBID3_CHANGED()                       (g_bDpMacStreamRx2Vbid3Chg)
#define SET_DP_MAC_STREAM_RX2_VBID3_CHANGED()                       (g_bDpMacStreamRx2Vbid3Chg = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_VBID3_CHANGED()                       (g_bDpMacStreamRx2Vbid3Chg = _FALSE)

//----------------------------------------------------------------------------
// Macro of Enlarge DP H Proch
//----------------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX2_H_PORCH_ENLARGE()                     (g_ucDpMacStreamRx2HPorchEnalrge)
#define SET_DP_MAC_STREAM_RX2_H_PORCH_ENLARGE(x)                    (g_ucDpMacStreamRx2HPorchEnalrge = (x))
#define CLR_DP_MAC_STREAM_RX2_H_PORCH_ENLARGE()                     (g_ucDpMacStreamRx2HPorchEnalrge = 0)

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//----------------------------------------------------------------------------
// Macro of Dp Lane Valid Check
//----------------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX2_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx2SourceTypeJudge)
#define SET_DP_MAC_STREAM_RX2_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx2SourceTypeJudge = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx2SourceTypeJudge = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Flag
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX2_NO_VIDEO_IRQ_STATUS_8B10B()           ((ScalerGetBit(PC7_3F_DP_IRQ_CTRL1, _BIT4) == _BIT4) ? _ENABLE : _DISABLE)

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_NO_VIDEO_IRQ_STATUS_128B132B()        ((ScalerGetBit(PD4_3B_DP_IRQ_CTRL1, _BIT4) == _BIT4) ? _ENABLE : _DISABLE)
#endif

//--------------------------------------------------
// DP MAC DSC Flag
//--------------------------------------------------
#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX2_DSC_SUPPORT_8B10B()                   {ScalerSetBit(PC6_91_DP_RSV1, ~(_BIT7 | _BIT6), _BIT7);}
#define GET_DP_MAC_STREAM_RX2_DSC_SUPPORT_8B10B()                   (ScalerGetBit(PC6_91_DP_RSV1, _BIT7) == _BIT7)
#define CLR_DP_MAC_STREAM_RX2_DSC_SUPPORT_8B10B()                   {ScalerSetBit(PC6_91_DP_RSV1, ~(_BIT7 | _BIT6), 0x00);}

#define SET_DP_MAC_STREAM_RX2_DSC_CHUNK_FROM_PPS_8B10B()            {ScalerSetBit(PC6_82_CPMODE, ~_BIT2, _BIT2);}

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX2_DSC_SUPPORT_128B132B()                {ScalerSetBit(PD3_25_DSC_CTRL_0, ~_BIT7, _BIT7);}
#define GET_DP_MAC_STREAM_RX2_DSC_SUPPORT_128B132B()                (ScalerGetBit(PD3_25_DSC_CTRL_0, _BIT7) == _BIT7)
#define CLR_DP_MAC_STREAM_RX2_DSC_SUPPORT_128B132B()                {ScalerSetBit(PD3_25_DSC_CTRL_0, ~_BIT7, 0x00);}

#define SET_DP_MAC_STREAM_RX2_DSC_CHUNK_FROM_PPS_128B132B()         {ScalerSetBit(PD3_25_DSC_CTRL_0, ~_BIT4, _BIT4);}
#endif
#endif

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX2_INTERLACE_VTT_FW_MODE_8B10B(x)        {\
                                                                        if((x) == _EVEN)\
                                                                        {\
                                                                            ScalerSetBit(PC6_91_DP_RSV1, ~(_BIT6 | _BIT4), _BIT4);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PC6_91_DP_RSV1, ~(_BIT6 | _BIT4), 0x00);\
                                                                        }\
                                                                    }
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX2_INTERLACE_VTT_FW_MODE_128B132B(x)     {\
                                                                        if((x) == _EVEN)\
                                                                        {\
                                                                            ScalerSetBit(PD3_03_DPF_CTRL_3, ~_BIT3, _BIT3);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PD3_03_DPF_CTRL_3, ~_BIT3, 0x00);\
                                                                        }\
                                                                    }
#endif
#endif

//--------------------------------------------------
// DP MAC Stream Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX2_STREAM_PREDETECT()                    (g_stDpMacStreamRx2StreamInfo.b1StreamPreDetectFlag)
#define SET_DP_MAC_STREAM_RX2_STREAM_PREDETECT(x)                   (g_stDpMacStreamRx2StreamInfo.b1StreamPreDetectFlag = (x))

#define GET_DP_MAC_STREAM_RX2_STREAM_DATA_PATH()                    (g_stDpMacStreamRx2StreamInfo.enumDpStreamDataPath)
#define SET_DP_MAC_STREAM_RX2_STREAM_DATA_PATH(x)                   (g_stDpMacStreamRx2StreamInfo.enumDpStreamDataPath = (x))

#define GET_DP_MAC_STREAM_RX2_STREAM_INFO_TYPE()                    (g_stDpMacStreamRx2StreamInfo.enumDpStreamInfoType)
#define SET_DP_MAC_STREAM_RX2_STREAM_INFO_TYPE(x)                   (g_stDpMacStreamRx2StreamInfo.enumDpStreamInfoType = (x))

#define GET_DP_MAC_STREAM_RX2_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx2StreamInfo.b1StreamInfoTypeChangeFlag)
#define SET_DP_MAC_STREAM_RX2_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx2StreamInfo.b1StreamInfoTypeChangeFlag = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx2StreamInfo.b1StreamInfoTypeChangeFlag = _FALSE)

#define GET_DP_MAC_STREAM_RX2_STREAM_CLOCK()                        (g_stDpMacStreamRx2StreamInfo.ulStreamPreDetectPixelClock)
#define SET_DP_MAC_STREAM_RX2_STREAM_CLOCK(x)                       (g_stDpMacStreamRx2StreamInfo.ulStreamPreDetectPixelClock = (x))

#define GET_DP_MAC_STREAM_RX2_NATIVE_PIXEL_CLOCK()                  (g_stDpMacStreamRx2StreamInfo.ulDpStreamNativePixelClock)
#define SET_DP_MAC_STREAM_RX2_NATIVE_PIXEL_CLOCK(x)                 (g_stDpMacStreamRx2StreamInfo.ulDpStreamNativePixelClock = (x))

#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx2StreamInfo.b1FreeSyncEnable)
#define SET_DP_MAC_STREAM_RX2_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx2StreamInfo.b1FreeSyncEnable = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx2StreamInfo.b1FreeSyncEnable = _FALSE)
#endif

//--------------------------------------------------
// DP MAC PR Enable
//--------------------------------------------------
#if(_DP_PR_MODE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX2_PR_ENABLE_8B10B()                     {ScalerSetBit(PC7_4A_DUMMY_4A, ~(_BIT0), _BIT0);}
#define GET_DP_MAC_STREAM_RX2_PR_ENABLE_8B10B()                     (ScalerGetBit(PC7_4A_DUMMY_4A, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX2_PR_ENABLE_8B10B()                     {ScalerSetBit(PC7_4A_DUMMY_4A, ~(_BIT0), 0x00);}

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX2_PR_ENABLE_128B132B()                  {ScalerSetBit(PD4_4A_VSC10, ~(_BIT0), _BIT0);}
#define GET_DP_MAC_STREAM_RX2_PR_ENABLE_128B132B()                  (ScalerGetBit(PD4_4A_VSC10, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX2_PR_ENABLE_128B132B()                  {ScalerSetBit(PD4_4A_VSC10, ~(_BIT0), 0x00);}

#define GET_DP_MAC_STREAM_RX2_PR_ENABLE()                           (GET_DP_MAC_STREAM_RX2_PR_ENABLE_8B10B() || GET_DP_MAC_STREAM_RX2_PR_ENABLE_128B132B())
#else
#define GET_DP_MAC_STREAM_RX2_PR_ENABLE()                           (GET_DP_MAC_STREAM_RX2_PR_ENABLE_8B10B())
#endif
#endif

//--------------------------------------------------
// DP MAC ALPM Enable
//--------------------------------------------------
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX2_ALPM_ENABLE_8B10B()                   {ScalerSetBit(PC6_96_DP_ALPM0, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX2_ALPM_ENABLE_8B10B()                   (ScalerGetBit(PC6_96_DP_ALPM0, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX2_ALPM_ENABLE_8B10B()                   {ScalerSetBit(PC6_96_DP_ALPM0, ~_BIT0, 0x00);}

#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX2_ALPM_ENABLE_128B132B()                {ScalerSetBit(PD3_57_DP_ALPM0, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX2_ALPM_ENABLE_128B132B()                (ScalerGetBit(PD3_57_DP_ALPM0, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX2_ALPM_ENABLE_128B132B()                {ScalerSetBit(PD3_57_DP_ALPM0, ~_BIT0, 0x00);}

#define GET_DP_MAC_STREAM_RX2_ALPM_ENABLE()                         (GET_DP_MAC_STREAM_RX2_ALPM_ENABLE_8B10B() || GET_DP_MAC_STREAM_RX2_ALPM_ENABLE_128B132B())
#else
#define GET_DP_MAC_STREAM_RX2_ALPM_ENABLE()                         (GET_DP_MAC_STREAM_RX2_ALPM_ENABLE_8B10B())
#endif
#endif

//--------------------------------------------------
// DP MAC Color Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX2_COLOR_SPACE_PREVALUE()                (g_stDpMacStreamRx2ColorInfo.ucDigitalColorSpacePreValue)
#define SET_DP_MAC_STREAM_RX2_COLOR_SPACE_PREVALUE(x)               (g_stDpMacStreamRx2ColorInfo.ucDigitalColorSpacePreValue = (x))

#define GET_DP_MAC_STREAM_RX2_COLOR_DEPTH_PREVALUE()                (g_stDpMacStreamRx2ColorInfo.b3DigitalColorDepthPreValue)
#define SET_DP_MAC_STREAM_RX2_COLOR_DEPTH_PREVALUE(x)               (g_stDpMacStreamRx2ColorInfo.b3DigitalColorDepthPreValue = (x))

#define GET_DP_MAC_STREAM_RX2_CONTENT_TYPE()                        (g_stDpMacStreamRx2ColorInfo.b3DigitalContentType)
#define SET_DP_MAC_STREAM_RX2_CONTENT_TYPE(x)                       (g_stDpMacStreamRx2ColorInfo.b3DigitalContentType = (x))

#define GET_DP_MAC_STREAM_RX2_COLORIMETRY_PREVALUE()                (g_stDpMacStreamRx2ColorInfo.b4DigitalColorimetryPreValue)
#define SET_DP_MAC_STREAM_RX2_COLORIMETRY_PREVALUE(x)               (g_stDpMacStreamRx2ColorInfo.b4DigitalColorimetryPreValue = (x))

#define GET_DP_MAC_STREAM_RX2_COLORIMETRY_EXT_PREVALUE()            (g_stDpMacStreamRx2ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_DP_MAC_STREAM_RX2_COLORIMETRY_EXT_PREVALUE(x)           (g_stDpMacStreamRx2ColorInfo.b4DigitalColorimetryExtPreValue = (x))

#define GET_DP_MAC_STREAM_RX2_QUANTIZATION_PREVALUE()               (g_stDpMacStreamRx2ColorInfo.b2DigitalQuantizationPreValue)
#define SET_DP_MAC_STREAM_RX2_QUANTIZATION_PREVALUE(x)              (g_stDpMacStreamRx2ColorInfo.b2DigitalQuantizationPreValue = (x))

#define GET_DP_MAC_STREAM_RX2_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx2ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_DP_MAC_STREAM_RX2_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx2ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx2ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX2_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx2ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_DP_MAC_STREAM_RX2_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx2ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx2ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX2_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx2ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_DP_MAC_STREAM_RX2_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx2ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx2ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX2_COLOR_SPACE()                         (g_stDpMacStreamRx2ColorInfo.enumDigitalColorSpace)
#define SET_DP_MAC_STREAM_RX2_COLOR_SPACE(x)                        (g_stDpMacStreamRx2ColorInfo.enumDigitalColorSpace = (x))

#define GET_DP_MAC_STREAM_RX2_COLOR_DEPTH()                         (g_stDpMacStreamRx2ColorInfo.ucDigitalColorDepthValue)
#define SET_DP_MAC_STREAM_RX2_COLOR_DEPTH(x)                        (g_stDpMacStreamRx2ColorInfo.ucDigitalColorDepthValue = (x))

#define GET_DP_MAC_STREAM_RX2_COLORIMETRY()                         (g_stDpMacStreamRx2ColorInfo.enumDigitalColorimetry)
#define SET_DP_MAC_STREAM_RX2_COLORIMETRY(x)                        (g_stDpMacStreamRx2ColorInfo.enumDigitalColorimetry = (x))

#define GET_DP_MAC_STREAM_RX2_EXT_COLORIMETRY()                     (g_stDpMacStreamRx2ColorInfo.enumDigitalColorimetryExt)
#define SET_DP_MAC_STREAM_RX2_EXT_COLORIMETRY(x)                    (g_stDpMacStreamRx2ColorInfo.enumDigitalColorimetryExt = (x))

#define GET_DP_MAC_STREAM_RX2_COLOR_YCC_QUANTIZATION_RANGE()        (g_stDpMacStreamRx2ColorInfo.enumDigitalColorYCCQuantization)
#define SET_DP_MAC_STREAM_RX2_COLOR_YCC_QUANTIZATION_RANGE(x)       (g_stDpMacStreamRx2ColorInfo.enumDigitalColorYCCQuantization = (x))

#define GET_DP_MAC_STREAM_RX2_COLOR_RGB_QUANTIZATION_RANGE()        (g_stDpMacStreamRx2ColorInfo.enumDigitalColorRGBQuantization)
#define SET_DP_MAC_STREAM_RX2_COLOR_RGB_QUANTIZATION_RANGE(x)       (g_stDpMacStreamRx2ColorInfo.enumDigitalColorRGBQuantization = (x))

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx2MiscCheckFail)
#define SET_DP_MAC_STREAM_RX2_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx2MiscCheckFail = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx2MiscCheckFail = _FALSE)
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx2FifoIrqTriggerCheck)
#define SET_DP_MAC_STREAM_RX2_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx2FifoIrqTriggerCheck = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx2FifoIrqTriggerCheck = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Pixel Mode Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX2_STREAM_OUTPUT_X2_CLK()                (g_stDpMacStreamRx2StreamInfo.b1DpStreamOutputX2Clk)

#define SET_DP_MAC_STREAM_RX2_STREAM_OUTPUT_X2_CLK()                {\
                                                                        g_stDpMacStreamRx2StreamInfo.b1DpStreamOutputX2Clk = _TRUE;\
                                                                        ScalerSetBit(PC6_A2_PLL_OUT_CONTROL, ~_BIT6, _BIT6);\
                                                                    }

#define CLR_DP_MAC_STREAM_RX2_STREAM_OUTPUT_X2_CLK()                {\
                                                                        g_stDpMacStreamRx2StreamInfo.b1DpStreamOutputX2Clk = _FALSE;\
                                                                        ScalerSetBit(PC6_A2_PLL_OUT_CONTROL, ~_BIT6, 0x00);\
                                                                    }

//--------------------------------------------------
// DP MAC OOR Info
//--------------------------------------------------
#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX2_JUDGE_OOR()                           (g_bDpMacStreamRx2JudgeOOR)
#define SET_DP_MAC_STREAM_RX2_JUDGE_OOR()                           (g_bDpMacStreamRx2JudgeOOR = _TRUE)
#define CLR_DP_MAC_STREAM_RX2_JUDGE_OOR()                           (g_bDpMacStreamRx2JudgeOOR = _FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile bit g_bDpMacStreamRx2CrcCalculate;
extern bit g_bDpMacStreamRx2InterlaceVtotalNum;

extern WORD g_usDpMacStreamRx2Vfrontporch;
extern EnumDDomainRegion g_enumDpMacStreamRx2IrqForceBackgrd;

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern volatile bit g_bDpMacStreamRx2MiscCheckFail;
#endif

extern bit g_bDpMacStreamRx2VscSdpColorMode;

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx2SPDInfoFrameCtrl;
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx2AdaptiveSyncInfoFrameCtrl;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx2HDRInfoFrameCtrl;
#endif

#if(_DP_MAC_RX2_ADVANCED_HDR10_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx2AdvancedHDR10InfoFrameCtrl;
#endif

#if(_DP_MAC_RX2_DM_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx2DMVsifInfoFrameCtrl;
#endif

#if(_AUDIO_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx2AudioInfoFrameCtrl;
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit g_bDpMacStreamRx2SourceTypeJudge;
#endif

extern StructDpStreamInfo g_stDpMacStreamRx2StreamInfo;
extern StructDpInfo g_stDpMacStreamRx2Info;

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern bit g_bDpMacStreamRx2LocalDimmingDisableControl;
#endif

extern bit g_bDpMacStreamRx2Vbid3Chg;

extern StructDigitalColorInfo g_stDpMacStreamRx2ColorInfo;
extern StructDigitalColorInfoChanged g_stDpMacStreamRx2ColorInfoChanged;

extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx2PpsSdpCtrl;
extern StructDpMacRxDscInfo g_stDpMacStreamRx2DscInfo;

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern bit g_bDpMacStreamRx2FifoIrqTriggerCheck;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
extern void ScalerDpMacStreamRx2MacInitial(void);
extern void ScalerDpMacStreamRx2SdpInitial(void);
extern void ScalerDpMacStreamRx2LowPowerProc(void);
extern void ScalerDpMacStreamRx2SecDataBlockReset(void);

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacStreamRx2PowerProc(EnumPowerAction enumPowerAction);
#endif

extern EnumSourceType ScalerDpMacStreamRx2ScanInputPort(void);
extern BYTE ScalerDpMacStreamRx2StreamPreDetect(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx2StreamVideoSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx2StreamJudgeSetting(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx2StreamVesaVideoSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx2StreamPreDetectReset(void);

extern bit ScalerDpMacStreamRx2StableDetect(void);
extern void ScalerDpMacStreamRx2TimingInfoAdjust(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx2TimingInfoAdjustForReorderTracking(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx2AVMute(void);
extern void ScalerDpMacStreamRx2BsMissFlagClear(void);
extern void ScalerDpMacStreamRx2SetBsMissDetectIRQ(bit bEn);
extern void ScalerDpMacStreamRx2SetFifoIRQ(bit bEn);
extern void ScalerDpMacStreamRx2DisableFifoIRQ(void);
extern void ScalerDpMacStreamRx2SetFifoWD(bit bEn);
extern void ScalerDpMacStreamRx2DisableFifoWD(void);
extern bit ScalerDpMacStreamRx2GetFifoWDStatus(void);

extern bit ScalerDpMacStreamRx2GetVideoStream(void);
extern bit ScalerDpMacStreamRx2GetMsaTimingInfo(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2GetMeasureLinkInfo(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2StreamInfoSetting(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2BsMissCheck(void);
extern bit ScalerDpMacStreamRx2InterlaceCheck(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2GetVideoInfo(void);
extern void ScalerDpMacStreamRx2SetColorInfo(void);

extern bit ScalerDpMacStreamRx2StreamClkRegenerate(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2TrackingSetting(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx2SetPLLNfOffProc(DWORD ulPllVcoClockHz, BYTE ucNcode, BYTE ucpllo, BYTE ucdivs);
extern bit ScalerDpMacStreamRx2SetPLLNfOnProc(BYTE ucNcode, BYTE ucFcode_MSB4b, WORD usFcode_LSB16b, bit bPllVcoHighFreqStatus);


extern bit ScalerDpMacStreamRx2CheckVgipVsBypass(void);
extern void ScalerDpMacStreamRx2SetNoVideoStreamIRQ(bit bEn);
extern void ScalerDpMacStreamRx2DisableNoVideoStreamIRQ(void);
extern EnumDpRxMacPixelMode ScalerDpMacStreamRx2InputPixelMode(void);
extern bit ScalerDpMacStreamRx2InterlaceModeConfig(BYTE ucInterlaceReference);
extern void ScalerDpMacStreamRx2Polarity(void);
extern void ScalerDpMacStreamRx2MacSetting(void);
extern void ScalerDpMacStreamRx2SdpSetting(void);
extern bit ScalerDpMacStreamRx2GetVbidInfo(EnumDpVbidInfo enumDpVbidInfo);
extern UnionDpRxMsaValue ScalerDpMacStreamRx2GetMsaInfo(EnumDpRxMsaType enumDpRxMsaType);
extern void ScalerDpMacStreamRx2SdpDataDetect(void);
extern void ScalerDpMacStreamRx2SdpPacketCheck(EnumDpSdpType enumDpSdpType);
extern EnumDpMacRxSdpReceiveStates ScalerDpMacStreamRx2GetSdpReceived(EnumDpSdpType enumDpSdpType);
extern EnumDpMacRxSdpChangeEvent ScalerDpMacStreamRx2GetSdpChangeEvent(EnumDpSdpType enumDpSdpType);
extern bit ScalerDpMacStreamRx2GetSdpChanged(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx2GetSdpPktData(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);
extern BYTE ScalerDpMacStreamRx2GetSdpInfoHB3(EnumDpSdpType enumDpSdpType);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetSdpMetaSramRcvInitial(void);
extern void ScalerDpMacStreamRx2SdpMetaSramReset(void);
#endif

extern void ScalerDpMacStreamRx2CtsFifoReset(void);
extern bit ScalerDpMacStreamRx2VbiosMsaCheck(void);
extern void ScalerDpMacStreamRx2SdpIrqEnable(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern EnumDpMacRxDPFRegenMode ScalerDpMacStreamRx2GetDPFRegenMode(void);
extern void ScalerDpMacStreamRx2SetDPFRegenMode(EnumDpMacRxDPFRegenMode enumDpMacRxDPFRegenMode);

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetBsMissDetectStart(bit bEn);
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern void ScalerDpMacStreamRx2SetSpdInfoDetectingDone(void);
extern void ScalerDpMacStreamRx2SpdInfoDataRemappingDisable(void);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetPpsSdpInfoDetectingDone(void);
extern bit ScalerDpMacStreamRx2DscStreamChangeCheck(void);
#endif

#if((_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx2DscStatusReset(void);
extern void ScalerDpMacStreamRx2DscInitial(void);
#endif

extern bit ScalerDpMacStreamRx2DscStreamCheck(void);
extern WORD ScalerDpMacStreamRx2GetPpsElementInfo(EnumDpStreamPpsElement enumDpStreamPpsElement);

#if(_DP_HDR10_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetHdrInfoDetectingDone(void);
extern void ScalerDpMacStreamRx2HdrInfoDataRemappingDisable(void);
#endif

#if(_AUDIO_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetAudioInfoDetectingDone(void);
#endif

#if(_DP_MAC_RX2_ADVANCED_HDR10_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetAdvancedHdr10InfoDetectingDone(void);
#endif

#if(_DP_MAC_RX2_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetDMVsifInfoDetectingDone(void);
#endif

#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2DscSetting(void);
extern bit ScalerDpMacStreamRx2GetDscReorder(void);
extern void ScalerDpMacStreamRx2DscSetStreamWD(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpMacStreamRx2DscSetStreamIRQ(EnumInputPort enumInputPort, bit bEnable);
extern  bit ScalerDpMacStreamRx2DscChunkLengthCheck(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
#endif

extern WORD ScalerDpMacStreamRx2GetDisplayFormat(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

#if(_DP_FREESYNC_SUPPORT == _ON)
extern DWORD ScalerDpMacStreamRx2GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
extern void ScalerDpMacStreamRx2GetSPDVfreqMaxMin(void);
extern void ScalerDpMacStreamRx2SetDrrMsaForLut(StructDpInfo *pstDpInfo);
#endif

extern DWORD ScalerDpMacStreamRx2GetHPeriod(void);
extern WORD ScalerDpMacStreamRx2GetHSW(void);
extern WORD ScalerDpMacStreamRx2GetVFreq(void);
extern WORD ScalerDpMacStreamRx2GetVPeriod(void);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2PRModeInitial(void);
extern void ScalerDpMacStreamRx2PRModeSdpReset(void);
extern void ScalerDpMacStreamRx2PRModeCheckProc(EnumInputPort enumInputPort);
#endif

extern bit ScalerDpMacStreamRx2HdcpMeasureCheck(void);

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetBsMissDetectPeriod(StructDpInfo *pstDpInfo);
#endif

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx2MacHighPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx2MacLowPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx2MacBsMissDetectIntHandler_EXINT0(void);

extern void ScalerDpMacStreamRx2SetNoVideoStreamIRQ_EXINT0(bit bEn);
extern bit ScalerDpMacStreamRx2GetFifoWDStatus_EXINT0(void);

#if(_DP_MAC_RX2_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2DscSetStreamIRQ_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpMacStreamRx2DscSetStreamWD_EXINT0(EnumInputPort enumInputPort, bit bEnable);
#endif


///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern BYTE ScalerDpMacStreamRx2StreamPreDetect_8b10b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx2GetVideoInfo_8b10b(void);
extern bit ScalerDpMacStreamRx2GetVbidInfo_8b10b(EnumDpVbidInfo enumDpVbidInfo);
extern bit ScalerDpMacStreamRx2GetMsaTimingInfo_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2GetMeasureLinkInfo_8b10b(StructDpInfo *pstDpInfo);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx2StreamVesaVideoSetting_8b10b(void);
extern bit ScalerDpMacStreamRx2DisplayFormatSetting_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2StableDetect_8b10b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx2MiscCheck_8b10b(void);
extern bit ScalerDpMacStreamRx2MSAActiveChange_8b10b(void);
extern bit ScalerDpMacStreamRx2InterlaceCheck_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2InterlaceVtotalGetMSACheck_8b10b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx2InterlaceReset_8b10b(void);
extern bit ScalerDpMacStreamRx2FifoCheckProc_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx2CrcCalculate_8b10b(void);
extern void ScalerDpMacStreamRx2AVMute_8b10b(void);
extern void ScalerDpMacStreamRx2SetBsToHsDelay_8b10b(StructTimingInfo *pstDpTimingInfo);
extern WORD ScalerDpMacStreamRx2GetDisplayFormat_8b10b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2PRModeCheckProc_8b10b(EnumInputPort enumInputPort);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2SetColorSpaceChangeWD(bit bEn);
extern void ScalerDpMacStreamRx2SstSetMsaChangeIRQ(bit bEn);
extern bit ScalerDpMacStreamRx2MsaMiscChangeSupportCheck(void);
extern bit ScalerDpMacStreamRx2GetMsaDebounceStatus(void);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx2MacHighPriorityIntHandler_8b10b_EXINT0(void);
extern void ScalerDpMacStreamRx2MacLowPriorityIntHandler_8b10b_EXINT0(void);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2PRModeCrcCheck_8b10b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx2PRModeCrcCalculateEnable_8b10b_EXINT0(bit bEnable);
#endif

#if(_DP_MAC_RX2_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2DMPacketReCheck_8b10b_EXINT0(EnumInputPort enumInputPort);
#endif

///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
extern BYTE ScalerDpMacStreamRx2StreamPreDetect_128b132b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx2GetVideoInfo_128b132b(void);
extern bit ScalerDpMacStreamRx2GetVbidInfo_128b132b(EnumDpVbidInfo enumDpVbidInfo);
extern bit ScalerDpMacStreamRx2GetMsaTimingInfo_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2GetMeasureLinkInfo_128b132b(StructDpInfo *pstDpInfo);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx2StreamVesaVideoSetting_128b132b(void);
extern bit ScalerDpMacStreamRx2DisplayFormatSetting_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2StableDetect_128b132b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx2MiscCheck_128b132b(void);
extern bit ScalerDpMacStreamRx2MSAActiveChange_128b132b(void);
extern bit ScalerDpMacStreamRx2InterlaceCheck_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx2InterlaceVtotalGetMSACheck_128b132b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx2InterlaceReset_128b132b(void);
extern bit ScalerDpMacStreamRx2FifoCheckProc_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx2CrcCalculate_128b132b(void);
extern void ScalerDpMacStreamRx2AVMute_128b132b(void);
extern void ScalerDpMacStreamRx2SetBsToHsDelay_128b132b(StructTimingInfo *pstDpTimingInfo);
extern WORD ScalerDpMacStreamRx2GetDisplayFormat_128b132b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2PRModeCheckProc_128b132b(EnumInputPort enumInputPort);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx2MacLowPriorityIntHandler_128b132b_EXINT0(void);
extern void ScalerDpMacStreamRx2MacHighPriorityIntHandler_128b132b_EXINT0(void);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2PRModeCrcCheck_128b132b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx2PRModeCrcCalculateEnable_128b132b_EXINT0(bit bEnable);
#endif

#if(_DP_MAC_RX2_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx2DMPacketReCheck_128b132b_EXINT0(EnumInputPort enumInputPort);
#endif

#endif // End of (_DP_MAC_RX2_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif // End of (_DP_SUPPORT == _ON)
