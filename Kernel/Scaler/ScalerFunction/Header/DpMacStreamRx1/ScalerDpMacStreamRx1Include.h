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
// ID Code      : ScalerDpMacStreamRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_MAC_RX1_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp CRC Information
//----------------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX1_CRC_CALCULATE()                       (g_bDpMacStreamRx1CrcCalculate)
#define SET_DP_MAC_STREAM_RX1_CRC_CALCULATE()                       (g_bDpMacStreamRx1CrcCalculate = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_CRC_CALCULATE()                       (g_bDpMacStreamRx1CrcCalculate = _FALSE)

#define GET_DP_MAC_STREAM_RX1_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx1MSAFailRsetCount)
#define ADD_DP_MAC_STREAM_RX1_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx1MSAFailRsetCount++)
#define CLR_DP_MAC_STREAM_RX1_MSA_FAIL_RESET_COUNT()                (g_ucDpMacStreamRx1MSAFailRsetCount = 0)

#define GET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH()                   (g_enumDpMacStreamRx1IrqForceBackgrd & _DDOMAIN_RGN_ALL)
#define SET_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH(x)                  (g_enumDpMacStreamRx1IrqForceBackgrd |= (x))
#define CLR_DP_MAC_STREAM_RX1_FORCE_BCKGRD_PATH(x)                  (g_enumDpMacStreamRx1IrqForceBackgrd &= (EnumDDomainRegion)~(x))

#define GET_DP_MAC_STREAM_RX1_VFRONT_PORCH()                        (g_usDpMacStreamRx1Vfrontporch)
#define SET_DP_MAC_STREAM_RX1_VFRONT_PORCH(x)                       (g_usDpMacStreamRx1Vfrontporch = (x))

#define SET_DP_MAC_STREAM_RX1_PORCH_COLOR_RGB()                     {\
                                                                        ScalerSetByte(PB8_51_MN_DPF_BG_RED_M, 0x00);\
                                                                        ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                        ScalerSetByte(PB8_53_MN_DPF_BG_GRN_M, 0x00);\
                                                                        ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                        ScalerSetByte(PB8_55_MN_DPF_BG_BLU_M, 0x00);\
                                                                        ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                    }

#define SET_DP_MAC_STREAM_RX1_PORCH_COLOR_YCC_LIMIT()\
                                                                    {\
                                                                        if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                        {\
                                                                            ScalerSetBit(PB8_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PB8_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PB8_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PB8_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PB8_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PB8_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                    }

#define SET_DP_MAC_STREAM_RX1_PORCH_COLOR_YCC_FULL()\
                                                                    {\
                                                                        if(GET_DP_MAC_STREAM_RX1_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                        {\
                                                                            ScalerSetBit(PB8_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PB8_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                            ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PB8_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PB8_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                            ScalerSetBit(PB8_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                            ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                            ScalerSetBit(PB8_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                            ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                        }\
                                                                    }

#define SET_DP_MAC_STREAM_RX1_VFRONT_PORCH_REG_8B10B(x)             {ScalerSetByte(PB8_40_VS_FRONT_PORCH, ((x) & 0xFF));}

#define SET_DP_MAC_STREAM_RX1_V_HEIGHT_REG_8B10B(x)                 {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(PB8_4D_MN_DPF_VHT_M, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(PB8_4E_MN_DPF_VHT_L, LOBYTE(usLocalValue));\
                                                                    }

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX1_VFRONT_PORCH_REG_128B132B(x)          {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(P70_38_VS_FRONT_PORCH_0, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(P70_39_VS_FRONT_PORCH_1, LOBYTE(usLocalValue));\
                                                                    }

#define SET_DP_MAC_STREAM_RX1_V_HEIGHT_REG_128B132B(x)              {\
                                                                        WORD usLocalValue = (WORD)(x);\
                                                                        ScalerSetByte(P70_1C_MN_DPF_VHT_M, HIBYTE(usLocalValue));\
                                                                        ScalerSetByte(P70_1D_MN_DPF_VHT_L, LOBYTE(usLocalValue));\
                                                                    }
#endif

#define GET_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx1VscSdpColorMode)
#define SET_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx1VscSdpColorMode = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_VSC_SDP_COLOR_MODE()                  (g_bDpMacStreamRx1VscSdpColorMode = _FALSE)

//--------------------------------------------------
// Macro of Dp Measure Pop Up Action
//--------------------------------------------------
// Delay 5us for Wait Hw Update Period to Prevent MCU Get wrong value, Update Period is 3T, T = 1/14.318M or 1/27M
#define SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_8B10B()                {\
                                                                        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                                        DELAY_5US();\
                                                                    }

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX1_MEASURE_POP_UP_128B132B()             {\
                                                                        ScalerSetBit(P70_40_MN_MEAS_CTRL, ~_BIT5, _BIT5);\
                                                                        DELAY_5US();\
                                                                    }
#endif
//--------------------------------------------------
// Macro of DP Rx Interlace info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX1_INTERLACE_VTOTAL_NUMBER()             (g_bDpMacStreamRx1InterlaceVtotalNum)
#define SET_DP_MAC_STREAM_RX1_INTERLACE_VTOTAL_NUMBER(x)            (g_bDpMacStreamRx1InterlaceVtotalNum = (x))

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
#define GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx1SPDInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx1SPDInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx1SPDInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_VERSION()              (g_stDpMacStreamRx1SPDInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_VERSION(x)             (g_stDpMacStreamRx1SPDInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_VERSION()              (g_stDpMacStreamRx1SPDInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx1SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx1SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx1SPDInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx1SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx1SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX1_SPD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx1SPDInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX1_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx1SPDInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX1_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx1SPDInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_SPD_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx1SPDInfoFrameCtrl.b1InfoDetecting = _FALSE)

#define GET_DP_MAC_STREAM_RX1_AMD_SPD_LOCAL_DIMMING()               (g_bDpMacStreamRx1LocalDimmingDisableControl)
#define SET_DP_MAC_STREAM_RX1_AMD_SPD_LOCAL_DIMMING(x)              (g_bDpMacStreamRx1LocalDimmingDisableControl = (x))
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE()             (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_VERSION()            (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_VERSION(x)           (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_VERSION()            (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE_EVENT()       (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE_EVENT(x)      (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_CHANGE_EVENT()       (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_RECEIVED_STATE()     (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_RECEIVED_STATE(x)    (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_RECEIVED_STATE()     (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_ADAPTIVESYNC_SDP_DETECTING()          (g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_HDR10_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx1HDRInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx1HDRInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE()               (g_stDpMacStreamRx1HDRInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_VERSION()              (g_stDpMacStreamRx1HDRInfoFrameCtrl.ucVersion)
#define SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_VERSION(x)             (g_stDpMacStreamRx1HDRInfoFrameCtrl.ucVersion = (x))
#define CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_VERSION()              (g_stDpMacStreamRx1HDRInfoFrameCtrl.ucVersion = 0x00)

#define GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx1HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx1HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx1HDRInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx1HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx1HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX1_HDR_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx1HDRInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX1_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx1HDRInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX1_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx1HDRInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_HDR_IFNOFRAME_DETECTING()             (g_stDpMacStreamRx1HDRInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_ADVANCED_HDR10_RECEIVED_STATE()       (g_stDpMacStreamRx1AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX1_ADVANCED_HDR10_RECEIVED_STATE(x)      (g_stDpMacStreamRx1AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX1_ADVANCED_HDR10_RECEIVED_STATE()       (g_stDpMacStreamRx1AdvancedHDR10InfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX1_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx1AdvancedHDR10InfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX1_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx1AdvancedHDR10InfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_ADVANCED_HDR10_DETECTING()            (g_stDpMacStreamRx1AdvancedHDR10InfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx1DMVsifInfoFrameCtrl.b1InfoFrameReceive)
#define SET_DP_MAC_STREAM_RX1_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx1DMVsifInfoFrameCtrl.b1InfoFrameReceive = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_DM_DRAM_INFO_FRAME_RECEIVED()         (g_stDpMacStreamRx1DMVsifInfoFrameCtrl.b1InfoFrameReceive = _FALSE)

#define GET_DP_MAC_STREAM_RX1_DM_VSIF_RECEIVED_STATE()              (g_stDpMacStreamRx1DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX1_DM_VSIF_RECEIVED_STATE(x)             (g_stDpMacStreamRx1DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX1_DM_VSIF_RECEIVED_STATE()              (g_stDpMacStreamRx1DMVsifInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX1_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx1DMVsifInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX1_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx1DMVsifInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_DM_VSIF_DETECTING()                   (g_stDpMacStreamRx1DMVsifInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#if(_AUDIO_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx1AudioInfoFrameCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX1_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx1AudioInfoFrameCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_AUDIO_INFO_FRAME_CHANGE()             (g_stDpMacStreamRx1AudioInfoFrameCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx1AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_CHANGE_EVENT(x)        (g_stDpMacStreamRx1AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_CHANGE_EVENT()         (g_stDpMacStreamRx1AudioInfoFrameCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx1AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_RECEIVED_STATE(x)      (g_stDpMacStreamRx1AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX1_AUD_INFO_FRAME_RECEIVED_STATE()       (g_stDpMacStreamRx1AudioInfoFrameCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX1_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx1AudioInfoFrameCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX1_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx1AudioInfoFrameCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_AUDIO_IFNOFRAME_DETECTING()           (g_stDpMacStreamRx1AudioInfoFrameCtrl.b1InfoDetecting = _FALSE)
#endif

#define GET_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx1PpsSdpCtrl.b1InfoFrameChange)
#define SET_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx1PpsSdpCtrl.b1InfoFrameChange = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE()                      (g_stDpMacStreamRx1PpsSdpCtrl.b1InfoFrameChange = _FALSE)

#define GET_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE_EVENT()                (g_stDpMacStreamRx1PpsSdpCtrl.enumDpMacRxSdpChangeEvent)
#define SET_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE_EVENT(x)               (g_stDpMacStreamRx1PpsSdpCtrl.enumDpMacRxSdpChangeEvent = (x))
#define CLR_DP_MAC_STREAM_RX1_PPS_SDP_CHANGE_EVENT()                (g_stDpMacStreamRx1PpsSdpCtrl.enumDpMacRxSdpChangeEvent = _SDP_EVENT_NONE)

#define GET_DP_MAC_STREAM_RX1_PPS_SDP_RECEIVED_STATE()              (g_stDpMacStreamRx1PpsSdpCtrl.enumDpMacRxSdpReceiveStates)
#define SET_DP_MAC_STREAM_RX1_PPS_SDP_RECEIVED_STATE(x)             (g_stDpMacStreamRx1PpsSdpCtrl.enumDpMacRxSdpReceiveStates = (x))
#define CLR_DP_MAC_STREAM_RX1_PPS_SDP_RECEIVED_STATE()              (g_stDpMacStreamRx1PpsSdpCtrl.enumDpMacRxSdpReceiveStates = _SDP_STATE_NOT_RECEIVED)

#define GET_DP_MAC_STREAM_RX1_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx1PpsSdpCtrl.b1InfoDetecting)
#define SET_DP_MAC_STREAM_RX1_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx1PpsSdpCtrl.b1InfoDetecting = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_PPS_SDP_DETECTING()                   (g_stDpMacStreamRx1PpsSdpCtrl.b1InfoDetecting = _FALSE)

#define GET_DP_MAC_STREAM_RX1_DSC_PIC_HEIGHT()                      (g_stDpMacStreamRx1DscInfo.usDscPicHeight)
#define SET_DP_MAC_STREAM_RX1_DSC_PIC_HEIGHT(x)                     (g_stDpMacStreamRx1DscInfo.usDscPicHeight = (x))
#define CLR_DP_MAC_STREAM_RX1_DSC_PIC_HEIGHT()                      (g_stDpMacStreamRx1DscInfo.usDscPicHeight = 0)

#define GET_DP_MAC_STREAM_RX1_DSC_PIC_WIDTH()                       (g_stDpMacStreamRx1DscInfo.usDscPicWidth)
#define SET_DP_MAC_STREAM_RX1_DSC_PIC_WIDTH(x)                      (g_stDpMacStreamRx1DscInfo.usDscPicWidth = (x))
#define CLR_DP_MAC_STREAM_RX1_DSC_PIC_WIDTH()                       (g_stDpMacStreamRx1DscInfo.usDscPicWidth = 0)

#define GET_DP_MAC_STREAM_RX1_DSC_SLICE_HEIGHT()                    (g_stDpMacStreamRx1DscInfo.usDscSliceHeight)
#define SET_DP_MAC_STREAM_RX1_DSC_SLICE_HEIGHT(x)                   (g_stDpMacStreamRx1DscInfo.usDscSliceHeight = (x))
#define CLR_DP_MAC_STREAM_RX1_DSC_SLICE_HEIGHT()                    (g_stDpMacStreamRx1DscInfo.usDscSliceHeight = 0)

#define GET_DP_MAC_STREAM_RX1_DSC_SLICE_WIDTH()                     (g_stDpMacStreamRx1DscInfo.usDscSliceWidth)
#define SET_DP_MAC_STREAM_RX1_DSC_SLICE_WIDTH(x)                    (g_stDpMacStreamRx1DscInfo.usDscSliceWidth = (x))
#define CLR_DP_MAC_STREAM_RX1_DSC_SLICE_WIDTH()                     (g_stDpMacStreamRx1DscInfo.usDscSliceWidth = 0)

#define GET_DP_MAC_STREAM_RX1_DSC_COLOR_BPP()                       (g_stDpMacStreamRx1DscInfo.usDscBitsPerPixel)
#define SET_DP_MAC_STREAM_RX1_DSC_COLOR_BPP(x)                      (g_stDpMacStreamRx1DscInfo.usDscBitsPerPixel = (x))
#define CLR_DP_MAC_STREAM_RX1_DSC_COLOR_BPP()                       (g_stDpMacStreamRx1DscInfo.usDscBitsPerPixel = 0)

#define GET_DP_MAC_STREAM_RX1_DSC_COLOR_BPC()                       (g_stDpMacStreamRx1DscInfo.b4DscBitPerComponent)
#define SET_DP_MAC_STREAM_RX1_DSC_COLOR_BPC(x)                      (g_stDpMacStreamRx1DscInfo.b4DscBitPerComponent = (x))
#define CLR_DP_MAC_STREAM_RX1_DSC_COLOR_BPC()                       (g_stDpMacStreamRx1DscInfo.b4DscBitPerComponent = 0)

#define GET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_420()                (g_stDpMacStreamRx1DscInfo.b1DscNative420)
#define SET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_420(x)               (g_stDpMacStreamRx1DscInfo.b1DscNative420 = (x))
#define CLR_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_420()                (g_stDpMacStreamRx1DscInfo.b1DscNative420 = 0)

#define GET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_422()                (g_stDpMacStreamRx1DscInfo.b1DscNative422)
#define SET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_422(x)               (g_stDpMacStreamRx1DscInfo.b1DscNative422 = (x))
#define CLR_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_422()                (g_stDpMacStreamRx1DscInfo.b1DscNative422 = 0)

#define GET_DP_MAC_STREAM_RX1_DSC_COLOR_SIMPLE_422()                (g_stDpMacStreamRx1DscInfo.b1DscSimple422)
#define SET_DP_MAC_STREAM_RX1_DSC_COLOR_SIMPLE_422(x)               (g_stDpMacStreamRx1DscInfo.b1DscSimple422 = (x))
#define CLR_DP_MAC_STREAM_RX1_DSC_COLOR_SIMPLE_422()                (g_stDpMacStreamRx1DscInfo.b1DscSimple422 = 0)

#define GET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_MODE()               (((GET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_420() == _TRUE) || (GET_DP_MAC_STREAM_RX1_DSC_COLOR_NATIVE_422() == _TRUE)) ? _TRUE : _FALSE)

//--------------------------------------------------
// Macro of VBID[3] Change to No-Video Flag
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX1_VBID3_CHANGED()                       (g_bDpMacStreamRx1Vbid3Chg)
#define SET_DP_MAC_STREAM_RX1_VBID3_CHANGED()                       (g_bDpMacStreamRx1Vbid3Chg = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_VBID3_CHANGED()                       (g_bDpMacStreamRx1Vbid3Chg = _FALSE)

//---------------------------------------------------------------------
// Macro of Enlarge DP H Proch
//---------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE()                     (g_ucDpMacStreamRx1HPorchEnalrge)
#define SET_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE(x)                    (g_ucDpMacStreamRx1HPorchEnalrge = (x))
#define CLR_DP_MAC_STREAM_RX1_H_PORCH_ENLARGE()                     (g_ucDpMacStreamRx1HPorchEnalrge = 0)

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//---------------------------------------------------------------------
// Macro of Dp Lane Valid Check
//---------------------------------------------------------------------
#define GET_DP_MAC_STREAM_RX1_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx1SourceTypeJudge)
#define SET_DP_MAC_STREAM_RX1_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx1SourceTypeJudge = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_SOURCE_TYPE_JUDGE()                   (g_bDpMacStreamRx1SourceTypeJudge = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Flag
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX1_NO_VIDEO_IRQ_STATUS_8B10B()           ((ScalerGetBit(PB9_3F_DP_IRQ_CTRL1, _BIT4) == _BIT4) ? _ENABLE : _DISABLE)

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_NO_VIDEO_IRQ_STATUS_128B132B()        ((ScalerGetBit(P75_3B_DP_IRQ_CTRL1, _BIT4) == _BIT4) ? _ENABLE : _DISABLE)
#endif

//--------------------------------------------------
// DP MAC DSC Flag
//--------------------------------------------------
#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX1_DSC_SUPPORT_8B10B()                   {ScalerSetBit(PB8_91_DP_RSV1, ~(_BIT7 | _BIT6), _BIT7);}
#define GET_DP_MAC_STREAM_RX1_DSC_SUPPORT_8B10B()                   (ScalerGetBit(PB8_91_DP_RSV1, _BIT7) == _BIT7)
#define CLR_DP_MAC_STREAM_RX1_DSC_SUPPORT_8B10B()                   {ScalerSetBit(PB8_91_DP_RSV1, ~(_BIT7 | _BIT6), 0x00);}

#define SET_DP_MAC_STREAM_RX1_DSC_CHUNK_FROM_PPS_8B10B()            {ScalerSetBit(PB8_82_CPMODE, ~_BIT2, _BIT2);}

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX1_DSC_SUPPORT_128B132B()                {ScalerSetBit(P70_25_DSC_CTRL_0, ~_BIT7, _BIT7);}
#define GET_DP_MAC_STREAM_RX1_DSC_SUPPORT_128B132B()                (ScalerGetBit(P70_25_DSC_CTRL_0, _BIT7) == _BIT7)
#define CLR_DP_MAC_STREAM_RX1_DSC_SUPPORT_128B132B()                {ScalerSetBit(P70_25_DSC_CTRL_0, ~_BIT7, 0x00);}

#define SET_DP_MAC_STREAM_RX1_DSC_CHUNK_FROM_PPS_128B132B()         {ScalerSetBit(P70_25_DSC_CTRL_0, ~_BIT4, _BIT4);}
#endif
#endif

#if(_DP_RX_INTERLACE_NEW_MODE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX1_INTERLACE_VTT_FW_MODE_8B10B(x)        {\
                                                                        if((x) == _EVEN)\
                                                                        {\
                                                                            ScalerSetBit(PB8_91_DP_RSV1, ~(_BIT6 | _BIT4), _BIT4);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(PB8_91_DP_RSV1, ~(_BIT6 | _BIT4), 0x00);\
                                                                        }\
                                                                    }
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX1_INTERLACE_VTT_FW_MODE_128B132B(x)     {\
                                                                        if((x) == _EVEN)\
                                                                        {\
                                                                            ScalerSetBit(P70_03_DPF_CTRL_3, ~_BIT3, _BIT3);\
                                                                        }\
                                                                        else\
                                                                        {\
                                                                            ScalerSetBit(P70_03_DPF_CTRL_3, ~_BIT3, 0x00);\
                                                                        }\
                                                                    }
#endif
#endif

//--------------------------------------------------
// DP MAC Stream Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX1_STREAM_PREDETECT()                    (g_stDpMacStreamRx1StreamInfo.b1StreamPreDetectFlag)
#define SET_DP_MAC_STREAM_RX1_STREAM_PREDETECT(x)                   (g_stDpMacStreamRx1StreamInfo.b1StreamPreDetectFlag = (x))

#define GET_DP_MAC_STREAM_RX1_STREAM_DATA_PATH()                    (g_stDpMacStreamRx1StreamInfo.enumDpStreamDataPath)
#define SET_DP_MAC_STREAM_RX1_STREAM_DATA_PATH(x)                   (g_stDpMacStreamRx1StreamInfo.enumDpStreamDataPath = (x))

#define GET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE()                    (g_stDpMacStreamRx1StreamInfo.enumDpStreamInfoType)
#define SET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE(x)                   (g_stDpMacStreamRx1StreamInfo.enumDpStreamInfoType = (x))

#define GET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx1StreamInfo.b1StreamInfoTypeChangeFlag)
#define SET_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx1StreamInfo.b1StreamInfoTypeChangeFlag = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_STREAM_INFO_TYPE_CHANGE()             (g_stDpMacStreamRx1StreamInfo.b1StreamInfoTypeChangeFlag = _FALSE)

#define GET_DP_MAC_STREAM_RX1_STREAM_CLOCK()                        (g_stDpMacStreamRx1StreamInfo.ulStreamPreDetectPixelClock)
#define SET_DP_MAC_STREAM_RX1_STREAM_CLOCK(x)                       (g_stDpMacStreamRx1StreamInfo.ulStreamPreDetectPixelClock = (x))

#define GET_DP_MAC_STREAM_RX1_NATIVE_PIXEL_CLOCK()                  (g_stDpMacStreamRx1StreamInfo.ulDpStreamNativePixelClock)
#define SET_DP_MAC_STREAM_RX1_NATIVE_PIXEL_CLOCK(x)                 (g_stDpMacStreamRx1StreamInfo.ulDpStreamNativePixelClock = (x))

#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx1StreamInfo.b1FreeSyncEnable)
#define SET_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx1StreamInfo.b1FreeSyncEnable = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_STREAM_FREESYNC_ENABLE()              (g_stDpMacStreamRx1StreamInfo.b1FreeSyncEnable = _FALSE)
#endif

//--------------------------------------------------
// DP MAC PR Enable
//--------------------------------------------------
#if(_DP_PR_MODE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX1_PR_ENABLE_8B10B()                     {ScalerSetBit(PB9_4A_DUMMY_4A, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX1_PR_ENABLE_8B10B()                     (ScalerGetBit(PB9_4A_DUMMY_4A, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX1_PR_ENABLE_8B10B()                     {ScalerSetBit(PB9_4A_DUMMY_4A, ~_BIT0, 0x00);}

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX1_PR_ENABLE_128B132B()                  {ScalerSetBit(P75_4A_VSC10, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX1_PR_ENABLE_128B132B()                  (ScalerGetBit(P75_4A_VSC10, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX1_PR_ENABLE_128B132B()                  {ScalerSetBit(P75_4A_VSC10, ~_BIT0, 0x00);}

#define GET_DP_MAC_STREAM_RX1_PR_ENABLE()                           (GET_DP_MAC_STREAM_RX1_PR_ENABLE_8B10B() || GET_DP_MAC_STREAM_RX1_PR_ENABLE_128B132B())
#else
#define GET_DP_MAC_STREAM_RX1_PR_ENABLE()                           (GET_DP_MAC_STREAM_RX1_PR_ENABLE_8B10B())
#endif
#endif

//--------------------------------------------------
// DP MAC ALPM Enable
//--------------------------------------------------
#if(_DP_AUXLESS_ALPM_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX1_ALPM_ENABLE_8B10B()                   {ScalerSetBit(PB8_96_DP_ALPM0, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX1_ALPM_ENABLE_8B10B()                   (ScalerGetBit(PB8_96_DP_ALPM0, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX1_ALPM_ENABLE_8B10B()                   {ScalerSetBit(PB8_96_DP_ALPM0, ~_BIT0, 0x00);}

#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#define SET_DP_MAC_STREAM_RX1_ALPM_ENABLE_128B132B()                {ScalerSetBit(P70_57_DP_ALPM0, ~_BIT0, _BIT0);}
#define GET_DP_MAC_STREAM_RX1_ALPM_ENABLE_128B132B()                (ScalerGetBit(P70_57_DP_ALPM0, _BIT0) == _BIT0)
#define CLR_DP_MAC_STREAM_RX1_ALPM_ENABLE_128B132B()                {ScalerSetBit(P70_57_DP_ALPM0, ~_BIT0, 0x00);}

#define GET_DP_MAC_STREAM_RX1_ALPM_ENABLE()                         (GET_DP_MAC_STREAM_RX1_ALPM_ENABLE_8B10B() || GET_DP_MAC_STREAM_RX1_ALPM_ENABLE_128B132B())
#else
#define GET_DP_MAC_STREAM_RX1_ALPM_ENABLE()                         (GET_DP_MAC_STREAM_RX1_ALPM_ENABLE_8B10B())
#endif
#endif

//--------------------------------------------------
// DP MAC Color Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE()                (g_stDpMacStreamRx1ColorInfo.ucDigitalColorSpacePreValue)
#define SET_DP_MAC_STREAM_RX1_COLOR_SPACE_PREVALUE(x)               (g_stDpMacStreamRx1ColorInfo.ucDigitalColorSpacePreValue = (x))

#define GET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE()                (g_stDpMacStreamRx1ColorInfo.b3DigitalColorDepthPreValue)
#define SET_DP_MAC_STREAM_RX1_COLOR_DEPTH_PREVALUE(x)               (g_stDpMacStreamRx1ColorInfo.b3DigitalColorDepthPreValue = (x))

#define GET_DP_MAC_STREAM_RX1_CONTENT_TYPE()                        (g_stDpMacStreamRx1ColorInfo.b3DigitalContentType)
#define SET_DP_MAC_STREAM_RX1_CONTENT_TYPE(x)                       (g_stDpMacStreamRx1ColorInfo.b3DigitalContentType = (x))

#define GET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE()                (g_stDpMacStreamRx1ColorInfo.b4DigitalColorimetryPreValue)
#define SET_DP_MAC_STREAM_RX1_COLORIMETRY_PREVALUE(x)               (g_stDpMacStreamRx1ColorInfo.b4DigitalColorimetryPreValue = (x))

#define GET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_PREVALUE()            (g_stDpMacStreamRx1ColorInfo.b4DigitalColorimetryExtPreValue)
#define SET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_PREVALUE(x)           (g_stDpMacStreamRx1ColorInfo.b4DigitalColorimetryExtPreValue = (x))

#define GET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE()               (g_stDpMacStreamRx1ColorInfo.b2DigitalQuantizationPreValue)
#define SET_DP_MAC_STREAM_RX1_QUANTIZATION_PREVALUE(x)              (g_stDpMacStreamRx1ColorInfo.b2DigitalQuantizationPreValue = (x))

#define GET_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx1ColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx1ColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_COLORIMETRY_CHANGED()                 (g_stDpMacStreamRx1ColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx1ColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx1ColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_COLORIMETRY_EXT_CHANGED()             (g_stDpMacStreamRx1ColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx1ColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx1ColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_QUANTIZATION_CHANGED()                (g_stDpMacStreamRx1ColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)

#define GET_DP_MAC_STREAM_RX1_COLOR_SPACE()                         (g_stDpMacStreamRx1ColorInfo.enumDigitalColorSpace)
#define SET_DP_MAC_STREAM_RX1_COLOR_SPACE(x)                        (g_stDpMacStreamRx1ColorInfo.enumDigitalColorSpace = (x))

#define GET_DP_MAC_STREAM_RX1_COLOR_DEPTH()                         (g_stDpMacStreamRx1ColorInfo.ucDigitalColorDepthValue)
#define SET_DP_MAC_STREAM_RX1_COLOR_DEPTH(x)                        (g_stDpMacStreamRx1ColorInfo.ucDigitalColorDepthValue = (x))

#define GET_DP_MAC_STREAM_RX1_COLORIMETRY()                         (g_stDpMacStreamRx1ColorInfo.enumDigitalColorimetry)
#define SET_DP_MAC_STREAM_RX1_COLORIMETRY(x)                        (g_stDpMacStreamRx1ColorInfo.enumDigitalColorimetry = (x))

#define GET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY()                     (g_stDpMacStreamRx1ColorInfo.enumDigitalColorimetryExt)
#define SET_DP_MAC_STREAM_RX1_EXT_COLORIMETRY(x)                    (g_stDpMacStreamRx1ColorInfo.enumDigitalColorimetryExt = (x))

#define GET_DP_MAC_STREAM_RX1_COLOR_YCC_QUANTIZATION_RANGE()        (g_stDpMacStreamRx1ColorInfo.enumDigitalColorYCCQuantization)
#define SET_DP_MAC_STREAM_RX1_COLOR_YCC_QUANTIZATION_RANGE(x)       (g_stDpMacStreamRx1ColorInfo.enumDigitalColorYCCQuantization = (x))

#define GET_DP_MAC_STREAM_RX1_COLOR_RGB_QUANTIZATION_RANGE()        (g_stDpMacStreamRx1ColorInfo.enumDigitalColorRGBQuantization)
#define SET_DP_MAC_STREAM_RX1_COLOR_RGB_QUANTIZATION_RANGE(x)       (g_stDpMacStreamRx1ColorInfo.enumDigitalColorRGBQuantization = (x))

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx1MiscCheckFail)
#define SET_DP_MAC_STREAM_RX1_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx1MiscCheckFail = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_MISC_CHECK_FAIL()                     (g_bDpMacStreamRx1MiscCheckFail = _FALSE)
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx1FifoIrqTriggerCheck)
#define SET_DP_MAC_STREAM_RX1_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx1FifoIrqTriggerCheck = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_FIFO_IRQ_TRIGGER_CHECK()              (g_bDpMacStreamRx1FifoIrqTriggerCheck = _FALSE)
#endif

//--------------------------------------------------
// DP MAC Pixel Mode Info
//--------------------------------------------------
#define GET_DP_MAC_STREAM_RX1_STREAM_OUTPUT_X2_CLK()                (g_stDpMacStreamRx1StreamInfo.b1DpStreamOutputX2Clk)

#define SET_DP_MAC_STREAM_RX1_STREAM_OUTPUT_X2_CLK()                {\
                                                                        g_stDpMacStreamRx1StreamInfo.b1DpStreamOutputX2Clk = _TRUE;\
                                                                        ScalerSetBit(PB8_A2_PLL_OUT_CONTROL, ~_BIT6, _BIT6);\
                                                                    }

#define CLR_DP_MAC_STREAM_RX1_STREAM_OUTPUT_X2_CLK()                {\
                                                                        g_stDpMacStreamRx1StreamInfo.b1DpStreamOutputX2Clk = _FALSE;\
                                                                        ScalerSetBit(PB8_A2_PLL_OUT_CONTROL, ~_BIT6, 0x00);\
                                                                    }

//--------------------------------------------------
// DP MAC OOR Info
//--------------------------------------------------
#if(_DP_IVF_OOR_EXTEND_SUPPORT == _ON)
#define GET_DP_MAC_STREAM_RX1_JUDGE_OOR()                           (g_bDpMacStreamRx1JudgeOOR)
#define SET_DP_MAC_STREAM_RX1_JUDGE_OOR()                           (g_bDpMacStreamRx1JudgeOOR = _TRUE)
#define CLR_DP_MAC_STREAM_RX1_JUDGE_OOR()                           (g_bDpMacStreamRx1JudgeOOR = _FALSE)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile bit g_bDpMacStreamRx1CrcCalculate;
extern bit g_bDpMacStreamRx1InterlaceVtotalNum;

extern WORD g_usDpMacStreamRx1Vfrontporch;
extern EnumDDomainRegion g_enumDpMacStreamRx1IrqForceBackgrd;

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern volatile bit g_bDpMacStreamRx1MiscCheckFail;
#endif

extern bit g_bDpMacStreamRx1VscSdpColorMode;

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1SPDInfoFrameCtrl;
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1AdaptiveSyncInfoFrameCtrl;
#endif

#if(_DP_HDR10_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1HDRInfoFrameCtrl;
#endif

#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1AdvancedHDR10InfoFrameCtrl;
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1DMVsifInfoFrameCtrl;
#endif

#if(_AUDIO_SUPPORT == _ON)
extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1AudioInfoFrameCtrl;
#endif

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
extern bit g_bDpMacStreamRx1SourceTypeJudge;
#endif

extern StructDpStreamInfo g_stDpMacStreamRx1StreamInfo;
extern StructDpInfo g_stDpMacStreamRx1Info;

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern bit g_bDpMacStreamRx1LocalDimmingDisableControl;
#endif

extern bit g_bDpMacStreamRx1Vbid3Chg;

extern StructDigitalColorInfo g_stDpMacStreamRx1ColorInfo;
extern StructDigitalColorInfoChanged g_stDpMacStreamRx1ColorInfoChanged;

extern StructDpMacRxInfoFrameCtrl g_stDpMacStreamRx1PpsSdpCtrl;
extern StructDpMacRxDscInfo g_stDpMacStreamRx1DscInfo;

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern bit g_bDpMacStreamRx1FifoIrqTriggerCheck;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

///////////////////////////////////////////
// Function Group For None Postfix
///////////////////////////////////////////
extern void ScalerDpMacStreamRx1MacInitial(void);
extern void ScalerDpMacStreamRx1SdpInitial(void);
extern void ScalerDpMacStreamRx1LowPowerProc(void);
extern void ScalerDpMacStreamRx1SecDataBlockReset(void);

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern void ScalerDpMacStreamRx1PowerProc(EnumPowerAction enumPowerAction);
#endif

extern EnumSourceType ScalerDpMacStreamRx1ScanInputPort(void);
extern BYTE ScalerDpMacStreamRx1StreamPreDetect(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx1StreamVideoSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx1StreamJudgeSetting(EnumInputPort enumInputPort);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx1StreamVesaVideoSetting(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx1StreamPreDetectReset(void);

extern bit ScalerDpMacStreamRx1StableDetect(void);
extern void ScalerDpMacStreamRx1TimingInfoAdjust(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx1TimingInfoAdjustForReorderTracking(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx1AVMute(void);
extern void ScalerDpMacStreamRx1BsMissFlagClear(void);
extern void ScalerDpMacStreamRx1SetBsMissDetectIRQ(bit bEn);
extern void ScalerDpMacStreamRx1SetFifoIRQ(bit bEn);
extern void ScalerDpMacStreamRx1DisableFifoIRQ(void);
extern void ScalerDpMacStreamRx1SetFifoWD(bit bEn);
extern void ScalerDpMacStreamRx1DisableFifoWD(void);
extern bit ScalerDpMacStreamRx1GetFifoWDStatus(void);

extern bit ScalerDpMacStreamRx1GetVideoStream(void);
extern bit ScalerDpMacStreamRx1GetMsaTimingInfo(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1GetMeasureLinkInfo(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1StreamInfoSetting(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1BsMissCheck(void);
extern bit ScalerDpMacStreamRx1InterlaceCheck(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1GetVideoInfo(void);
extern void ScalerDpMacStreamRx1SetColorInfo(void);

extern bit ScalerDpMacStreamRx1StreamClkRegenerate(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1TrackingSetting(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx1SetPLLNfOffProc(DWORD ulPllVcoClockHz, BYTE ucNcode, BYTE ucpllo, BYTE ucdivs);
extern bit ScalerDpMacStreamRx1SetPLLNfOnProc(BYTE ucNcode, BYTE ucFcode_MSB4b, WORD usFcode_LSB16b, bit bPllVcoHighFreqStatus);


extern bit ScalerDpMacStreamRx1CheckVgipVsBypass(void);
extern void ScalerDpMacStreamRx1SetNoVideoStreamIRQ(bit bEn);
extern void ScalerDpMacStreamRx1DisableNoVideoStreamIRQ(void);
extern EnumDpRxMacPixelMode ScalerDpMacStreamRx1InputPixelMode(void);
extern bit ScalerDpMacStreamRx1InterlaceModeConfig(BYTE ucInterlaceReference);
extern void ScalerDpMacStreamRx1Polarity(void);
extern void ScalerDpMacStreamRx1MacSetting(void);
extern void ScalerDpMacStreamRx1SdpSetting(void);
extern bit ScalerDpMacStreamRx1GetVbidInfo(EnumDpVbidInfo enumDpVbidInfo);
extern UnionDpRxMsaValue ScalerDpMacStreamRx1GetMsaInfo(EnumDpRxMsaType enumDpRxMsaType);
extern void ScalerDpMacStreamRx1SdpDataDetect(void);
extern void ScalerDpMacStreamRx1SdpPacketCheck(EnumDpSdpType enumDpSdpType);
extern EnumDpMacRxSdpReceiveStates ScalerDpMacStreamRx1GetSdpReceived(EnumDpSdpType enumDpSdpType);
extern EnumDpMacRxSdpChangeEvent ScalerDpMacStreamRx1GetSdpChangeEvent(EnumDpSdpType enumDpSdpType);
extern bit ScalerDpMacStreamRx1GetSdpChanged(EnumDpSdpType enumDpSdpType);
extern void ScalerDpMacStreamRx1GetSdpPktData(EnumDpSdpType enumDpSdpType, BYTE *pucSdpData, BYTE ucOffset, BYTE ucLength);
extern BYTE ScalerDpMacStreamRx1GetSdpInfoHB3(EnumDpSdpType enumDpSdpType);

#if(_DP_SDP_META_SRAM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetSdpMetaSramRcvInitial(void);
extern void ScalerDpMacStreamRx1SdpMetaSramReset(void);
#endif

extern void ScalerDpMacStreamRx1CtsFifoReset(void);
extern bit ScalerDpMacStreamRx1VbiosMsaCheck(void);
extern void ScalerDpMacStreamRx1SdpIrqEnable(EnumDpSdpRamIndex enumDpSdpRamIndex, bit bEnable);
extern EnumDpMacRxDPFRegenMode ScalerDpMacStreamRx1GetDPFRegenMode(void);
extern void ScalerDpMacStreamRx1SetDPFRegenMode(EnumDpMacRxDPFRegenMode enumDpMacRxDPFRegenMode);

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetBsMissDetectStart(bit bEn);
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern void ScalerDpMacStreamRx1SetSpdInfoDetectingDone(void);
extern void ScalerDpMacStreamRx1SpdInfoDataRemappingDisable(void);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetPpsSdpInfoDetectingDone(void);
extern bit ScalerDpMacStreamRx1DscStreamChangeCheck(void);
#endif

#if((_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON) || (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
extern void ScalerDpMacStreamRx1DscStatusReset(void);
extern void ScalerDpMacStreamRx1DscInitial(void);
#endif

extern bit ScalerDpMacStreamRx1DscStreamCheck(void);
extern WORD ScalerDpMacStreamRx1GetPpsElementInfo(EnumDpStreamPpsElement enumDpStreamPpsElement);

#if(_DP_HDR10_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetHdrInfoDetectingDone(void);
extern void ScalerDpMacStreamRx1HdrInfoDataRemappingDisable(void);
#endif

#if(_AUDIO_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetAudioInfoDetectingDone(void);
#endif

#if(_DP_MAC_RX1_ADVANCED_HDR10_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetAdvancedHdr10InfoDetectingDone(void);
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetDMVsifInfoDetectingDone(void);
#endif

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1DscSetting(void);
extern bit ScalerDpMacStreamRx1GetDscReorder(void);
extern void ScalerDpMacStreamRx1DscSetStreamWD(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpMacStreamRx1DscSetStreamIRQ(EnumInputPort enumInputPort, bit bEnable);
extern  bit ScalerDpMacStreamRx1DscChunkLengthCheck(EnumInputPort enumInputPort, WORD usDscPpsChunkLength, BYTE ucDscPpsSliceCnt);
#endif

extern WORD ScalerDpMacStreamRx1GetDisplayFormat(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

#if(_DP_FREESYNC_SUPPORT == _ON)
extern DWORD ScalerDpMacStreamRx1GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
extern void ScalerDpMacStreamRx1GetSPDVfreqMaxMin(void);
extern void ScalerDpMacStreamRx1SetDrrMsaForLut(StructDpInfo *pstDpInfo);
#endif

extern DWORD ScalerDpMacStreamRx1GetHPeriod(void);
extern WORD ScalerDpMacStreamRx1GetHSW(void);
extern WORD ScalerDpMacStreamRx1GetVFreq(void);
extern WORD ScalerDpMacStreamRx1GetVPeriod(void);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1PRModeInitial(void);
extern void ScalerDpMacStreamRx1PRModeSdpReset(void);
extern void ScalerDpMacStreamRx1PRModeCheckProc(EnumInputPort enumInputPort);
#endif

extern bit ScalerDpMacStreamRx1HdcpMeasureCheck(void);

#if(_HW_DP_RX_BS_MISS_DETECT_PERIOD_ENABLE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetBsMissDetectPeriod(StructDpInfo *pstDpInfo);
#endif

//--------------------------------------------------
// EXINT0 For NONE Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx1MacHighPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx1MacLowPriorityIntHandler_EXINT0(void);
extern void ScalerDpMacStreamRx1MacBsMissDetectIntHandler_EXINT0(void);

extern void ScalerDpMacStreamRx1SetNoVideoStreamIRQ_EXINT0(bit bEn);
extern bit ScalerDpMacStreamRx1GetFifoWDStatus_EXINT0(void);

#if(_DP_MAC_RX1_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1DscSetStreamIRQ_EXINT0(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpMacStreamRx1DscSetStreamWD_EXINT0(EnumInputPort enumInputPort, bit bEnable);
#endif


///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
extern BYTE ScalerDpMacStreamRx1StreamPreDetect_8b10b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx1GetVideoInfo_8b10b(void);
extern bit ScalerDpMacStreamRx1GetVbidInfo_8b10b(EnumDpVbidInfo enumDpVbidInfo);
extern bit ScalerDpMacStreamRx1GetMsaTimingInfo_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1GetMeasureLinkInfo_8b10b(StructDpInfo *pstDpInfo);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx1StreamVesaVideoSetting_8b10b(void);
extern bit ScalerDpMacStreamRx1DisplayFormatSetting_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1StableDetect_8b10b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx1MiscCheck_8b10b(void);
extern bit ScalerDpMacStreamRx1MSAActiveChange_8b10b(void);
extern bit ScalerDpMacStreamRx1InterlaceCheck_8b10b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1InterlaceVtotalGetMSACheck_8b10b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx1InterlaceReset_8b10b(void);
extern bit ScalerDpMacStreamRx1FifoCheckProc_8b10b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx1CrcCalculate_8b10b(void);
extern void ScalerDpMacStreamRx1AVMute_8b10b(void);
extern void ScalerDpMacStreamRx1SetBsToHsDelay_8b10b(StructTimingInfo *pstDpTimingInfo);
extern WORD ScalerDpMacStreamRx1GetDisplayFormat_8b10b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1PRModeCheckProc_8b10b(EnumInputPort enumInputPort);
#endif

#if(_DP_RX_MSA_MISC_CHANGE_IRQ_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1SetColorSpaceChangeWD(bit bEn);
extern void ScalerDpMacStreamRx1SstSetMsaChangeIRQ(bit bEn);
extern bit ScalerDpMacStreamRx1MsaMiscChangeSupportCheck(void);
extern bit ScalerDpMacStreamRx1GetMsaDebounceStatus(void);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx1MacHighPriorityIntHandler_8b10b_EXINT0(void);
extern void ScalerDpMacStreamRx1MacLowPriorityIntHandler_8b10b_EXINT0(void);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1PRModeCrcCheck_8b10b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx1PRModeCrcCalculateEnable_8b10b_EXINT0(bit bEnable);
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1DMPacketReCheck_8b10b_EXINT0(EnumInputPort enumInputPort);
#endif

///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
extern BYTE ScalerDpMacStreamRx1StreamPreDetect_128b132b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx1GetVideoInfo_128b132b(void);
extern bit ScalerDpMacStreamRx1GetVbidInfo_128b132b(EnumDpVbidInfo enumDpVbidInfo);
extern bit ScalerDpMacStreamRx1GetMsaTimingInfo_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1GetMeasureLinkInfo_128b132b(StructDpInfo *pstDpInfo);
extern EnumDpMacRxStreamVideoType ScalerDpMacStreamRx1StreamVesaVideoSetting_128b132b(void);
extern bit ScalerDpMacStreamRx1DisplayFormatSetting_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1StableDetect_128b132b(EnumInputPort enumInputPort);
extern bit ScalerDpMacStreamRx1MiscCheck_128b132b(void);
extern bit ScalerDpMacStreamRx1MSAActiveChange_128b132b(void);
extern bit ScalerDpMacStreamRx1InterlaceCheck_128b132b(StructDpInfo *pstDpInfo);
extern bit ScalerDpMacStreamRx1InterlaceVtotalGetMSACheck_128b132b(StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx1InterlaceReset_128b132b(void);
extern bit ScalerDpMacStreamRx1FifoCheckProc_128b132b(EnumDpFifoCheckCondition enumFifoCheckCondition, StructDpInfo *pstDpInfo);
extern void ScalerDpMacStreamRx1CrcCalculate_128b132b(void);
extern void ScalerDpMacStreamRx1AVMute_128b132b(void);
extern void ScalerDpMacStreamRx1SetBsToHsDelay_128b132b(StructTimingInfo *pstDpTimingInfo);
extern WORD ScalerDpMacStreamRx1GetDisplayFormat_128b132b(EnumDpDisplayFormatInfo enumDpDisplayFormatInfo);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1PRModeCheckProc_128b132b(EnumInputPort enumInputPort);
#endif

//--------------------------------------------------
// EXINT0 For 8B10B Postfix
//--------------------------------------------------
extern void ScalerDpMacStreamRx1MacLowPriorityIntHandler_128b132b_EXINT0(void);
extern void ScalerDpMacStreamRx1MacHighPriorityIntHandler_128b132b_EXINT0(void);

#if(_DP_PR_MODE_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1PRModeCrcCheck_128b132b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacStreamRx1PRModeCrcCalculateEnable_128b132b_EXINT0(bit bEnable);
#endif

#if(_DP_MAC_RX1_DM_SUPPORT == _ON)
extern void ScalerDpMacStreamRx1DMPacketReCheck_128b132b_EXINT0(EnumInputPort enumInputPort);
#endif

#endif // End of (_DP_MAC_RX1_128B132B_CODING_TYPE_SUPPORT == _ON)
#endif // End of (_DP_SUPPORT == _ON)
