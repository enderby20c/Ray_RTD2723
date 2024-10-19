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
// ID Code      : ScalerDpMacTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_DP_MAC_TX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// DownStream Port Type
//--------------------------------------------------
#define _DP_TX_DP_TYPE                                      0
#define _DP_TX_VGA_TYPE                                     1
#define _DP_TX_DVI_TYPE                                     2
#define _DP_TX_OTHER_TYPE                                   3

//--------------------------------------------------
// DP Sync Polarity Type
//--------------------------------------------------
#define _DP_TX_SYNC_POLARITY_POSITIVE                       0
#define _DP_TX_SYNC_POLARITY_NEGATIVE                       1

//--------------------------------------------------
// Peer Deveice Type
//--------------------------------------------------
#define _DP_TX_NO_DEVICE                                    0
#define _DP_TX_SOURCE_OR_SST_BRANCH_UPSTREAM                1
#define _DP_TX_MST_OR_SST_BRANCH_DOWNSTREAM                 2
#define _DP_TX_SST_SINK                                     3
#define _DP_TX_TO_LEGACY                                    4

//--------------------------------------------------
// Tx Edid Size
//--------------------------------------------------
#define _DP_TX_EDID_SIZE_MAX                                _EDID_SIZE_384
#define _DP_TX_EDID_SHA1_VALUE_SIZE_MAX                     20

//--------------------------------------------------
// MST Status
//--------------------------------------------------
#define _DP_TX_MSG_NO_SUPPORT                               0
#define _DP_TX_MSG_SUPPORT                                  1


#define _DP_TX_SSC_30K                                      30
#define _DP_TX_SSC_32K                                      32
#define _DP_TX_SSC_33K                                      33
#define _DP_TX_SSC_FREQ                                     _DP_TX_SSC_32K


#define _DP_TX_AUX_DIFF_MODE                                0
#define _DP_TX_AUX_SINGLE_MODE                              1

//--------------------------------------------------
// HDCP Info
//--------------------------------------------------
#define _DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_EXCEED          126

#define _DP_TX_LINK_CLK_MHZ                                 (WORD) ((GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() == _DP_LINK_RBR) ? 162 : ((GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() == _DP_LINK_HBR) ? 270 : ((GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() == _DP_LINK_HBR2) ? 540 : 810)))

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
#define _DP_TX_LINK_CLK_MHZ_128B132B                        (WORD) ((GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() == _DP_LINK_UHBR20) ? 2000 : ((GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE() == _DP_LINK_UHBR13_5) ? 1350 : 1000))
#endif

#define GET_DP_TX_HPD_DETECTION_ENABLE()                    (ScalerGetBit(PBB_70_HPD_CTRL, _BIT7) == _BIT7)

#if((_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON) && (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
#define GET_DP_TX_HPD_DEBOUNCE_LEVEL()                      (GET_DP_TX_PD_HPD_LEVEL())
#define GET_DP_TX_PD_HPD_LEVEL()                            (g_ucDpMacTxHpdLevel)
#define SET_DP_TX_PD_HPD_LEVEL(x)                           (g_ucDpMacTxHpdLevel = (x))
#else
#define GET_DP_TX_HPD_DEBOUNCE_LEVEL()                      (ScalerGetBit(PBB_70_HPD_CTRL, _BIT2) >> 2)
#endif

//--------------------------------------------------
// Definitions of DP Tx HPD Debounce
//--------------------------------------------------
#define GET_DP_TX_HPD_DEBOUNCE()                            (g_stDpMacTxModeInfo.b1HPDDebounce)
#define SET_DP_TX_HPD_DEBOUNCE()                            (g_stDpMacTxModeInfo.b1HPDDebounce = _TRUE)
#define CLR_DP_TX_HPD_DEBOUNCE()                            (g_stDpMacTxModeInfo.b1HPDDebounce = _FALSE)

#define GET_DP_TX_MODE_STATE()                              (g_stDpMacTxModeInfo.b3ModeState)
#define SET_DP_TX_MODE_STATE(x)                             (g_stDpMacTxModeInfo.b3ModeState = (x))

#define GET_DP_TX_MODE_STATE_CHANGE()                       (g_stDpMacTxModeInfo.b1ModeStateChanged)
#define SET_DP_TX_MODE_STATE_CHANGE()                       (g_stDpMacTxModeInfo.b1ModeStateChanged = _TRUE)
#define CLR_DP_TX_MODE_STATE_CHANGE()                       (g_stDpMacTxModeInfo.b1ModeStateChanged = _FALSE)

#define GET_DP_TX_HPD_EVENT()                               (g_stDpMacTxModeInfo.b3HPDEvent)
#define SET_DP_TX_HPD_EVENT(x)                              (g_stDpMacTxModeInfo.b3HPDEvent = (x))

#define GET_DP_TX_HPD_FIRST_DETECT()                        (g_stDpMacTxModeInfo.b1FirstHPD)
#define SET_DP_TX_HPD_FIRST_DETECT()                        (g_stDpMacTxModeInfo.b1FirstHPD = _TRUE)
#define CLR_DP_TX_HPD_FIRST_DETECT()                        (g_stDpMacTxModeInfo.b1FirstHPD = _FALSE)

#define GET_DP_TX_FORCE_LINK_TRAINING()                     (g_stDpMacTxModeInfo.b1ForceLT)
#define SET_DP_TX_FORCE_LINK_TRAINING()                     (g_stDpMacTxModeInfo.b1ForceLT = _TRUE)
#define CLR_DP_TX_FORCE_LINK_TRAINING()                     (g_stDpMacTxModeInfo.b1ForceLT = _FALSE)

#define GET_DP_TX_EXCEED_LINK_BANDWIDTH()                   (g_bDpMacTxExceedBW)
#define SET_DP_TX_EXCEED_LINK_BANDWIDTH()                   (g_bDpMacTxExceedBW = _TRUE)
#define CLR_DP_TX_EXCEED_LINK_BANDWIDTH()                   (g_bDpMacTxExceedBW = _FALSE)

#define GET_DP_TX_IRQ_HPD_DETECTED()                        (g_bDpMacTxIRQHPDDetected)
#define SET_DP_TX_IRQ_HPD_DETECTED()                        (g_bDpMacTxIRQHPDDetected = _TRUE)
#define CLR_DP_TX_IRQ_HPD_DETECTED()                        (g_bDpMacTxIRQHPDDetected = _FALSE)

#define GET_DP_TX_HPD_TYPE(x)                               (g_enumDpMacTxHPDType & (x))
#define SET_DP_TX_HPD_TYPE(x)                               (g_enumDpMacTxHPDType |= (x))
#define CLR_DP_TX_HPD_TYPE()                                (g_enumDpMacTxHPDType &= 0x00)

#define GET_DP_TX_IRQ_HPD_TYPE(x)                           (g_enumDpMacTxIRQType & (x))
#define SET_DP_TX_IRQ_HPD_TYPE(x)                           (g_enumDpMacTxIRQType |= (x))
#define CLR_DP_TX_IRQ_HPD_TYPE()                            (g_enumDpMacTxIRQType &= 0x00)
#define CLR_DP_TX_IRQ_HPD_TARGET_TYPE(x)                    (g_enumDpMacTxIRQType &= (EnumDPTxIRQEventType)~(x))

#define GET_DP_TX_IRQ_HPD_TYPE_INT()                        (g_enumDpMacTxIRQTypeInt)
#define SET_DP_TX_IRQ_HPD_TYPE_INT(x)                       (g_enumDpMacTxIRQTypeInt |= (x))
#define CLR_DP_TX_IRQ_HPD_TYPE_INT()                        (g_enumDpMacTxIRQTypeInt &= 0x00)

#define GET_DP_TX_IRQ_HDCP_TYPE(x)                          (g_enumDpMacTxIRQHdcpType & (x))
#define SET_DP_TX_IRQ_HDCP_TYPE(x)                          (g_enumDpMacTxIRQHdcpType |= (x))
#define CLR_DP_TX_IRQ_HDCP_TYPE()                           (g_enumDpMacTxIRQHdcpType &= 0x00)
#define CLR_DP_TX_IRQ_HDCP_TARGET_TYPE(x)                   (g_enumDpMacTxIRQHdcpType &= (EnumDPTxTRQEventHDCPType)~(x))

#define GET_DP_TX_HPD_STATUS_CHANGE()                       (ScalerGetBit(PBB_71_HPD_IRQ, (_BIT6 | _BIT4)) != 0x00)

//--------------------------------------------------
// Definitions of DP Tx PD HPD Queue
//--------------------------------------------------
#if((_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON) && (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
#define GET_DP_TX_HPD_QUEUE_TYPE()                          (g_enumDpMacTxHpdQueueType)
#define SET_DP_TX_HPD_QUEUE_TYPE(x)                         (g_enumDpMacTxHpdQueueType = (x))
#define CLR_DP_TX_HPD_QUEUE_TYPE()                          (g_enumDpMacTxHpdQueueType = 0x00)

#define GET_DP_TX_HPD_QUEUE_TYPE_BACKUP()                   (g_enumDpMacTxHpdQueueTypeBackup)
#define SET_DP_TX_HPD_QUEUE_TYPE_BACKUP(x)                  (g_enumDpMacTxHpdQueueTypeBackup = (x))
#define CLR_DP_TX_HPD_QUEUE_TYPE_BACKUP()                   (g_enumDpMacTxHpdQueueTypeBackup = 0x00)

#define GET_DP_TX_IRQ_HPD_QUEUE()                           (g_bDpMacTxIRQHpdQueue)
#define SET_DP_TX_IRQ_HPD_QUEUE()                           (g_bDpMacTxIRQHpdQueue = _TRUE)
#define CLR_DP_TX_IRQ_HPD_QUEUE()                           (g_bDpMacTxIRQHpdQueue = _FALSE)
#endif

//--------------------------------------------------
// Macros of DP Tx Downstream Infomation
//--------------------------------------------------
#if(_DP_TX_FEC_SUPPORT == _ON)
#define GET_DP_TX_DOWNSTREAM_FEC_SUPPORT()                  (g_bDpMacTxDownStreamFecSupport)
#define SET_DP_TX_DOWNSTREAM_FEC_SUPPORT()                  (g_bDpMacTxDownStreamFecSupport = _TRUE)
#define CLR_DP_TX_DOWNSTREAM_FEC_SUPPORT()                  (g_bDpMacTxDownStreamFecSupport = _FALSE)

#define GET_DP_TX_FEC_READY_8B10B()                         (ScalerGetBit(PBB_F2_FEC_TX_SETTING, _BIT0) == _BIT0)
#define SET_DP_TX_FEC_READY_8B10B(x)                        {\
                                                                if((x) == _ENABLE)\
                                                                {\
                                                                    ScalerSetBit(PBB_F2_FEC_TX_SETTING, ~_BIT0, _BIT0);\
                                                                    ScalerSetBit(PA_01_MST2SST_ASYNC_FIFO, ~_BIT7, _BIT7);\
                                                                }\
                                                                else\
                                                                {\
                                                                    ScalerSetBit(PBB_F2_FEC_TX_SETTING, ~_BIT0, 0x00);\
                                                                    ScalerSetBit(PA_01_MST2SST_ASYNC_FIFO, ~_BIT7, 0x00);\
                                                                    DELAY_XUS(850);\
                                                                }\
                                                            }


#define GET_DP_TX_FEC_ENCODE_8B10B()                        (ScalerGetBit(PBB_F2_FEC_TX_SETTING, _BIT1) == _BIT1)
#define SET_DP_TX_FEC_ENCODE_8B10B(x)                       {\
                                                                if((x) == _ENABLE)\
                                                                {\
                                                                    ScalerSetBit(PBB_F2_FEC_TX_SETTING, ~_BIT1, _BIT1);\
                                                                    ScalerSetBit(PA_01_MST2SST_ASYNC_FIFO, ~_BIT6, _BIT6);\
                                                                }\
                                                                else\
                                                                {\
                                                                    ScalerSetBit(PBB_F2_FEC_TX_SETTING, ~_BIT1, 0x00);\
                                                                    ScalerSetBit(PA_01_MST2SST_ASYNC_FIFO, ~_BIT6, 0x00);\
                                                                    DELAY_XUS(850);\
                                                                }\
                                                            }
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
#define GET_DP_TX_FEC_ENCODE_128B132B()                     (ScalerGetBit(P2B_1E_DPTX_FEC, _BIT7) == _BIT7)
#define SET_DP_TX_FEC_ENCODE_128B132B(x)                    {\
                                                                if((x) == _ENABLE)\
                                                                {\
                                                                    ScalerSetBit(P2B_1E_DPTX_FEC, ~_BIT7, _BIT7);\
                                                                }\
                                                                else\
                                                                {\
                                                                    ScalerSetBit(P2B_1E_DPTX_FEC, ~_BIT7, 0x00);\
                                                                    DELAY_XUS(850);\
                                                                }\
                                                            }
#endif

#define GET_DP_TX_FEC_CLONE_ENABLE_8B10B()                  (g_bDpMacTxCloneFecEnable)
#define SET_DP_TX_FEC_CLONE_ENABLE_8B10B()                  (g_bDpMacTxCloneFecEnable = _TRUE)
#define CLR_DP_TX_FEC_CLONE_ENABLE_8B10B()                  (g_bDpMacTxCloneFecEnable = _FALSE)

// Dis seq need to wait 65536 symbols (800us) and en seq must delay 1000 symbol (50us) after sending dis seq
#endif

//--------------------------------------------------
// Macros of DP Tx Input Infomation
//--------------------------------------------------
#define GET_DP_TX_STREAM_SOURCE_CHANGE()                    (g_bDpMacTxSourceChanged)
#define SET_DP_TX_STREAM_SOURCE_CHANGE()                    (g_bDpMacTxSourceChanged = _TRUE)
#define CLR_DP_TX_STREAM_SOURCE_CHANGE()                    (g_bDpMacTxSourceChanged = _FALSE)

#define GET_DP_TX_STREAM_SOURCE()                           (g_ucDpMacTxStreamSource)
#define SET_DP_TX_STREAM_SOURCE(x)                          (g_ucDpMacTxStreamSource = (x))

#define GET_DP_TX_STREAM_DATA_PATH_TYPE()                   (g_ucDpMacTxStreamType)
#define SET_DP_TX_STREAM_DATA_PATH_TYPE(x)                  (g_ucDpMacTxStreamType = (x))

#if(_DP_TX_AUDIO_SUPPORT == _ON)
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_DP) || (_PS_AUDIO_INPUT == _PS_AUDIO_BOTH)))
#define GET_DP_TX_AUDIO_STAND_ALONE_CHANGE_EVENT()          (g_stDpMacTxInputInfo.b1SleepAudioChangeEvent)
#define SET_DP_TX_AUDIO_STAND_ALONE_CHANGE_EVENT()          (g_stDpMacTxInputInfo.b1SleepAudioChangeEvent = _TRUE)
#define CLR_DP_TX_AUDIO_STAND_ALONE_CHANGE_EVENT()          (g_stDpMacTxInputInfo.b1SleepAudioChangeEvent = _FALSE)

#define GET_DP_TX_AUDIO_STAND_ALONE()                       (g_stDpMacTxInputInfo.b1SleepAudioSupport)
#define SET_DP_TX_AUDIO_STAND_ALONE()                       (g_stDpMacTxInputInfo.b1SleepAudioSupport = _TRUE)
#define CLR_DP_TX_AUDIO_STAND_ALONE()                       (g_stDpMacTxInputInfo.b1SleepAudioSupport = _FALSE)
#endif
#endif // End of #if(_DP_TX_AUDIO_SUPPORT == _ON)

#define GET_DP_TX_AUDIO_READY_TO_PLAY()                     (g_stDpMacTxInputInfo.b1AudioReadyToPlay)
#define SET_DP_TX_AUDIO_READY_TO_PLAY()                     (g_stDpMacTxInputInfo.b1AudioReadyToPlay = _TRUE)
#define CLR_DP_TX_AUDIO_READY_TO_PLAY()                     (g_stDpMacTxInputInfo.b1AudioReadyToPlay = _FALSE)

#define GET_DP_TX_AUDIO_SAMPLING_FREQUENCY()                (g_stDpMacTxInputInfo.ucAudioFrequency)
#define SET_DP_TX_AUDIO_SAMPLING_FREQUENCY(x)               (g_stDpMacTxInputInfo.ucAudioFrequency = (x))
#define CLR_DP_TX_AUDIO_SAMPLING_FREQUENCY()                (g_stDpMacTxInputInfo.ucAudioFrequency = _DP_TX_AUDIO_FREQ_NO_AUDIO)

#define GET_DP_TX_AUDIO_CHANNEL_COUNT()                     (g_stDpMacTxInputInfo.b3AudioChannelCount)
#define SET_DP_TX_AUDIO_CHANNEL_COUNT(x)                    (g_stDpMacTxInputInfo.b3AudioChannelCount = (x))
#define CLR_DP_TX_AUDIO_CHANNEL_COUNT()                     (g_stDpMacTxInputInfo.b3AudioChannelCount = (_AUDIO_CHANNEL_COUNT_MONO))

#define GET_DP_TX_AUDIO_CODING_TYPE()                       (g_stDpMacTxInputInfo.b4AudioCodingType)
#define SET_DP_TX_AUDIO_CODING_TYPE(x)                      (g_stDpMacTxInputInfo.b4AudioCodingType = (x))
#define CLR_DP_TX_AUDIO_CODING_TYPE()                       (g_stDpMacTxInputInfo.b4AudioCodingType = (0))

#define GET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ()           (g_stDpMacTxInputInfo.b3AudioInfoframeSamplingFrequency)
#define SET_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ(x)          (g_stDpMacTxInputInfo.b3AudioInfoframeSamplingFrequency = (x))
#define CLR_DP_TX_AUDIO_INFOFRAME_SAMPLING_FREQ()           (g_stDpMacTxInputInfo.b3AudioInfoframeSamplingFrequency = (_DP_TX_AUDIO_INFOFRAME_FREQ_NO_AUDIO))

#define GET_DP_TX_AUDIO_INPUT_PATH()                        (g_stDpMacTxInputInfo.enumAudioInputPath)
#define SET_DP_TX_AUDIO_INPUT_PATH(x)                       (g_stDpMacTxInputInfo.enumAudioInputPath = (x))

#define GET_DP_TX_INPUT_COLOR_DEPTH()                       (g_stDpMacTxInputInfo.b3ColorDepth)
#define SET_DP_TX_INPUT_COLOR_DEPTH(x)                      (g_stDpMacTxInputInfo.b3ColorDepth = (x))

#define GET_DP_TX_INPUT_COLOR_SPACE()                       (g_stDpMacTxInputInfo.b3ColorSpace)
#define SET_DP_TX_INPUT_COLOR_SPACE(x)                      (g_stDpMacTxInputInfo.b3ColorSpace = (x))

#define GET_DP_TX_INPUT_COLOR_CONTENT_TYPE()                (g_stDpMacTxInputInfo.b3ContentType)
#define SET_DP_TX_INPUT_COLOR_CONTENT_TYPE(x)               (g_stDpMacTxInputInfo.b3ContentType = (x))

#define GET_DP_TX_INPUT_COLORIMETRY()                       (g_stDpMacTxInputInfo.b4Colorimetry)
#define SET_DP_TX_INPUT_COLORIMETRY(x)                      (g_stDpMacTxInputInfo.b4Colorimetry = (x))

#define GET_DP_TX_INPUT_EXT_COLORIMETRY()                   (g_stDpMacTxInputInfo.b5ExtColorimetry)
#define SET_DP_TX_INPUT_EXT_COLORIMETRY(x)                  (g_stDpMacTxInputInfo.b5ExtColorimetry = (x))

#define GET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE()      (g_stDpMacTxInputInfo.b2RgbQuantizationRange)
#define SET_DP_TX_INPUT_COLOR_RGB_QUANTIZATION_RANGE(x)     (g_stDpMacTxInputInfo.b2RgbQuantizationRange = (x))

#define GET_DP_TX_INPUT_COLOR_YCC_QUANTIZATION_RANGE()      (g_stDpMacTxInputInfo.b2YccQuantizationRange)
#define SET_DP_TX_INPUT_COLOR_YCC_QUANTIZATION_RANGE(x)     (g_stDpMacTxInputInfo.b2YccQuantizationRange = (x))

#define GET_DP_TX_INPUT_DIGITAL_COLORIMETRY_CHANGED()       (g_stDpMacTxInputDigitalColorInfoChanged.b1DigitalColorimetryChanged)
#define SET_DP_TX_INPUT_DIGITAL_COLORIMETRY_CHANGED()       (g_stDpMacTxInputDigitalColorInfoChanged.b1DigitalColorimetryChanged = _TRUE)
#define CLR_DP_TX_INPUT_DIGITAL_COLORIMETRY_CHANGED()       (g_stDpMacTxInputDigitalColorInfoChanged.b1DigitalColorimetryChanged = _FALSE)

#define GET_DP_TX_INPUT_DIGITAL_COLORIMETRY_EXT_CHANGED()   (g_stDpMacTxInputDigitalColorInfoChanged.b1DigitalColorimetryExtChanged)
#define SET_DP_TX_INPUT_DIGITAL_COLORIMETRY_EXT_CHANGED()   (g_stDpMacTxInputDigitalColorInfoChanged.b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_DP_TX_INPUT_DIGITAL_COLORIMETRY_EXT_CHANGED()   (g_stDpMacTxInputDigitalColorInfoChanged.b1DigitalColorimetryExtChanged = _FALSE)

#define GET_DP_TX_INPUT_DIGITAL_QUANTIZATION_CHANGED()      (g_stDpMacTxInputDigitalColorInfoChanged.b1DigitalQuantizationChanged)
#define SET_DP_TX_INPUT_DIGITAL_QUANTIZATION_CHANGED()      (g_stDpMacTxInputDigitalColorInfoChanged.b1DigitalQuantizationChanged = _TRUE)
#define CLR_DP_TX_INPUT_DIGITAL_QUANTIZATION_CHANGED()      (g_stDpMacTxInputDigitalColorInfoChanged.b1DigitalQuantizationChanged = _FALSE)

#define GET_DP_TX_INPUT_PIXEL_CLK()                         (g_stDpMacTxInputInfo.usInputPixelClk)
#define SET_DP_TX_INPUT_PIXEL_CLK(x)                        (g_stDpMacTxInputInfo.usInputPixelClk = (x))
#define CLR_DP_TX_INPUT_PIXEL_CLK()                         (g_stDpMacTxInputInfo.usInputPixelClk = 0)

#define GET_DP_TX_INPUT_INTERLACE_MODE()                    (g_stDpMacTxInputInfo.b1InterlaceMode)
#define SET_DP_TX_INPUT_INTERLACE_MODE(x)                   (g_stDpMacTxInputInfo.b1InterlaceMode = (x))

#define GET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER()           (g_stDpMacTxInputInfo.b1InterlaceVTotalNumber)
#define SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(x)          (g_stDpMacTxInputInfo.b1InterlaceVTotalNumber = (x))

#define GET_DP_MAC_TX_INPUT_LANE_COUNT()                    (g_stDpMacTxInputInfo.b3TxInputLaneCount)
#define SET_DP_MAC_TX_INPUT_LANE_COUNT(x)                   (g_stDpMacTxInputInfo.b3TxInputLaneCount = (x))

#define GET_DP_MAC_TX_INPUT_PORT()                          (g_stDpMacTxInputInfo.ucTxInputPort)
#define SET_DP_MAC_TX_INPUT_PORT(x)                         (g_stDpMacTxInputInfo.ucTxInputPort = (x))

#define GET_DP_MAC_TX_INPUT_PIXEL_MODE()                    (g_stDpMacTxInputInfo.ucTxInputPixelMode)
#define SET_DP_MAC_TX_INPUT_PIXEL_MODE(x)                   (g_stDpMacTxInputInfo.ucTxInputPixelMode = (x))

#define GET_DP_MAC_TX_INPUT_CHANNEL_CODING()                (g_stDpMacTxInputInfo.b2TxInputChannelCoding)
#define SET_DP_MAC_TX_INPUT_CHANNEL_CODING(x)               (g_stDpMacTxInputInfo.b2TxInputChannelCoding = (x))

#define GET_DP_TX_HORIZONTAL_DE_PERIOD()                    (g_stDpMacTxInputInfo.usHorizontalDataEnablePeriod)
#define SET_DP_TX_HORIZONTAL_DE_PERIOD(x)                   (g_stDpMacTxInputInfo.usHorizontalDataEnablePeriod = (x))

#define GET_DP_TX_VSC_SDP_SEND_ENABLE()                     ((GET_DP_TX_INPUT_COLORIMETRY() == _COLORIMETRY_EXT) && (GET_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT() == _TRUE))

#define CLR_DP_TX_VSC_COLOR_INFO()                          (memset(g_pucDpMacTxVscSdpDB16to18, 0, sizeof(g_pucDpMacTxVscSdpDB16to18)))

#define SET_DP_TX_VSC_COLOR_SPACE(x)                        (g_pucDpMacTxVscSdpDB16to18[0] = ((g_pucDpMacTxVscSdpDB16to18[0] & ~(_BIT7 | _BIT6 | _BIT5 | _BIT4)) | ((x) << 4)))
#define SET_DP_TX_VSC_COLORIMETRY(x)                        (g_pucDpMacTxVscSdpDB16to18[0] = ((g_pucDpMacTxVscSdpDB16to18[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | (x)))
#define SET_DP_TX_VSC_DYNAMIC_RANGE(x)                      (g_pucDpMacTxVscSdpDB16to18[1] = ((g_pucDpMacTxVscSdpDB16to18[1] & ~_BIT7) | ((BYTE)(x) << 7)))
#define SET_DP_TX_VSC_COLOR_DEPTH(x)                        (g_pucDpMacTxVscSdpDB16to18[1] = ((g_pucDpMacTxVscSdpDB16to18[1] & ~(_BIT2 | _BIT1 | _BIT0)) | (x)))
#define SET_DP_TX_VSC_CONTENT_TYPE(x)                       (g_pucDpMacTxVscSdpDB16to18[2] = ((g_pucDpMacTxVscSdpDB16to18[2] & ~(_BIT2 | _BIT1 | _BIT0)) | (x)))

#define GET_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT()              (g_bDpMacTxDownStreamVscSdpSupport)
#define SET_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT()              (g_bDpMacTxDownStreamVscSdpSupport = _TRUE)
#define CLR_DP_TX_DOWNSTREAM_VSC_SDP_SUPPORT()              (g_bDpMacTxDownStreamVscSdpSupport = _FALSE)

#define GET_DP_TX_DOWNSTREAM_SPLIT_SDP_SUPPORT()            (g_stDpMacTxDownStreamInfo.b1SdpSplitSupport)
#define SET_DP_TX_DOWNSTREAM_SPLIT_SDP_SUPPORT()            (g_stDpMacTxDownStreamInfo.b1SdpSplitSupport = _TRUE)
#define CLR_DP_TX_DOWNSTREAM_SPLIT_SDP_SUPPORT()            (g_stDpMacTxDownStreamInfo.b1SdpSplitSupport = _FALSE)

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
#define GET_DP_TX_DOWNSTREAM_DSC_SUPPORT()                  (g_stDpMacTxDownStreamDscInfo.b1DscSupport)
#define SET_DP_TX_DOWNSTREAM_DSC_SUPPORT()                  (g_stDpMacTxDownStreamDscInfo.b1DscSupport = _TRUE)
#define CLR_DP_TX_DOWNSTREAM_DSC_SUPPORT()                  (g_stDpMacTxDownStreamDscInfo.b1DscSupport = _FALSE)

#define GET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH()              (g_stDpMacTxDownStreamDscInfo.b1DscPassThrough)
#define SET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH()              (g_stDpMacTxDownStreamDscInfo.b1DscPassThrough = _ENABLE)
#define CLR_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH()              (g_stDpMacTxDownStreamDscInfo.b1DscPassThrough = _DISABLE)

#define SET_DP_TX_DOWNSTREAM_DSC_INIT_CHUNK_SIZE(x)         (g_stDpMacTxDownStreamDscInfo.usDscInitChunkSize = (x))
#define GET_DP_TX_DOWNSTREAM_DSC_INIT_CHUNK_SIZE()          (g_stDpMacTxDownStreamDscInfo.usDscInitChunkSize)

#define SET_DP_TX_DOWNSTREAM_DSC_INIT_TU_SIZE(x)            (g_stDpMacTxDownStreamDscInfo.usDscInitTUSize = (x))
#define GET_DP_TX_DOWNSTREAM_DSC_INIT_TU_SIZE()             (g_stDpMacTxDownStreamDscInfo.usDscInitTUSize)

#define GET_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH()       (g_stDpMacTxDownStreamDscInfo.b1DscDetectPassThrough)
#define SET_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH()       (g_stDpMacTxDownStreamDscInfo.b1DscDetectPassThrough = _ENABLE)
#define CLR_DP_TX_DOWNSTREAM_DSC_DETECT_PASSTHROUGH()       (g_stDpMacTxDownStreamDscInfo.b1DscDetectPassThrough = _DISABLE)

#define GET_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE()            (g_stDpMacTxDownStreamDscInfo.b1DscDetectEnable)
#define SET_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE()            (g_stDpMacTxDownStreamDscInfo.b1DscDetectEnable = _ENABLE)
#define CLR_DP_TX_DOWNSTREAM_DSC_DETECT_ENABLE()            (g_stDpMacTxDownStreamDscInfo.b1DscDetectEnable = _DISABLE)

#define GET_DP_TX_DSC_PASSTHROUGH_TYPE()                    (g_stDpMacTxDownStreamDscInfo.b3DscPassThroughType)
#define SET_DP_TX_DSC_PASSTHROUGH_TYPE(x)                   (g_stDpMacTxDownStreamDscInfo.b3DscPassThroughType = (x))

#define GET_DP_TX_INPUT_DSC_PIC_WIDTH()                     (g_stDpMacTxInputDscInfo.usDscPicWidth)
#define SET_DP_TX_INPUT_DSC_PIC_WIDTH(x)                    (g_stDpMacTxInputDscInfo.usDscPicWidth = (x))
#define CLR_DP_TX_INPUT_DSC_PIC_WIDTH()                     (g_stDpMacTxInputDscInfo.usDscPicWidth = 0)

#define GET_DP_TX_INPUT_DSC_SLICE_WIDTH()                   (g_stDpMacTxInputDscInfo.usDscSliceWidth)
#define SET_DP_TX_INPUT_DSC_SLICE_WIDTH(x)                  (g_stDpMacTxInputDscInfo.usDscSliceWidth = (x))
#define CLR_DP_TX_INPUT_DSC_SLICE_WIDTH()                   (g_stDpMacTxInputDscInfo.usDscSliceWidth = 0)

#define GET_DP_TX_INPUT_DSC_COLOR_BPP()                     (g_stDpMacTxInputDscInfo.usDscBitsPerPixel)
#define SET_DP_TX_INPUT_DSC_COLOR_BPP(x)                    (g_stDpMacTxInputDscInfo.usDscBitsPerPixel = (x))
#define CLR_DP_TX_INPUT_DSC_COLOR_BPP()                     (g_stDpMacTxInputDscInfo.usDscBitsPerPixel = 0)

#define GET_DP_TX_INPUT_DSC_COLOR_NATIVE_420()              (g_stDpMacTxInputDscInfo.b1DscNative420)
#define SET_DP_TX_INPUT_DSC_COLOR_NATIVE_420(x)             (g_stDpMacTxInputDscInfo.b1DscNative420 = (x))
#define CLR_DP_TX_INPUT_DSC_COLOR_NATIVE_420()              (g_stDpMacTxInputDscInfo.b1DscNative420 = 0)

#define GET_DP_TX_INPUT_DSC_COLOR_NATIVE_422()              (g_stDpMacTxInputDscInfo.b1DscNative422)
#define SET_DP_TX_INPUT_DSC_COLOR_NATIVE_422(x)             (g_stDpMacTxInputDscInfo.b1DscNative422 = (x))
#define CLR_DP_TX_INPUT_DSC_COLOR_NATIVE_422()              (g_stDpMacTxInputDscInfo.b1DscNative422 = 0)

#define GET_DP_TX_INPUT_DSC_COLOR_NATIVE_MODE()             (((GET_DP_TX_INPUT_DSC_COLOR_NATIVE_420() == _TRUE) || (GET_DP_TX_INPUT_DSC_COLOR_NATIVE_422() == _TRUE)) ? _TRUE : _FALSE)
#endif

#define GET_DP_TX_DIGITAL_COLORIMETRY_CHANGED()             (ScalerDpMacTxDigitalColorimetryChangeCheck() || (GET_DP_MAC_TX_SEC_COLOR_FIRST_APPLYED_DONE() == _FALSE))
#define SET_DP_TX_INPUT_COLORIMETRY_CHANGED_VALUE()         (ScalerDpMacTxSetColorimetryChangeValue())
#define GET_DP_TX_DIGITAL_QUANTIZATION_CHANGED()            (ScalerDpMacTxDigitalQuantizationChangeCheck() || (GET_DP_MAC_TX_SEC_COLOR_FIRST_APPLYED_DONE() == _FALSE))
#define SET_DP_TX_INPUT_QUANTIZATION_CHANGED_VALUE()        (ScalerDpMacTxSetQuantizationChangeValue())

#define CLR_DP_TX_DIGITAL_COLORIMETRY_CHANGED()             (ScalerDpMacTxColorimetryChangeFlagClear())
#define CLR_DP_TX_DIGITAL_QUANTIZATION_CHANGED()            (ScalerDpMacTxQuantizationChangeFlagClear())

#if(_DP_HDR10_SUPPORT == _ON)
#define GET_DP_TX_HDR_INFOFRAME_RECEIVED()                  (ScalerDpMacTxSdpInfoRevStateCheck(_DP_SDP_TYPE_INFOFRAME_HDR))
#define GET_DP_TX_HDR_INFOFRAME_CHANGE()                    (ScalerDpMacTxSdpInfoChgCheck(_DP_SDP_TYPE_INFOFRAME_HDR))
#define GET_DP_TX_HDR_INFOFRAME_CHANGE_EVENT()              (ScalerDpMacTxSdpInfoChgEventCheck(_DP_SDP_TYPE_INFOFRAME_HDR))
#define GET_DP_TX_HDR_INFOFRAME_HB3()                       (ScalerDpMacTxSdpInfoHB3Value(_DP_SDP_TYPE_INFOFRAME_HDR))
#define GET_DP_TX_HDR_INFOFRAME_DATA(ptr)                   (ScalerDpMacTxSdpGetInfoData(_DP_SDP_TYPE_INFOFRAME_HDR, (ptr)))
#define GET_DP_TX_HDR_INFOFRAME_UPDATED()                   (g_stDpMacTxSdpInfoCtrl.b1DpTxHdrInfoUpated)
#define SET_DP_TX_HDR_INFOFRAME_UPDATED()                   (g_stDpMacTxSdpInfoCtrl.b1DpTxHdrInfoUpated = _TRUE)
#define CLR_DP_TX_HDR_INFOFRAME_UPDATED()                   (g_stDpMacTxSdpInfoCtrl.b1DpTxHdrInfoUpated = _FALSE)
#endif

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
#define GET_DP_TX_SPD_INFOFRAME_RECEIVED()                  (ScalerDpMacTxSdpInfoRevStateCheck(_DP_SDP_TYPE_INFOFRAME_SPD))
#define GET_DP_TX_SPD_INFOFRAME_CHANGE()                    (ScalerDpMacTxSdpInfoChgCheck(_DP_SDP_TYPE_INFOFRAME_SPD) || (GET_DP_MAC_TX_SEC_DATA_FIRST_APPLYED_DONE() == _FALSE))
#define GET_DP_TX_SPD_INFOFRAME_CHANGE_EVENT()              (ScalerDpMacTxSdpInfoChgEventCheck(_DP_SDP_TYPE_INFOFRAME_SPD))
#define GET_DP_TX_SPD_INFOFRAME_HB3()                       (ScalerDpMacTxSdpInfoHB3Value(_DP_SDP_TYPE_INFOFRAME_SPD))
#define GET_DP_TX_FREESYNC_INFOFRAME_DATA(ptr)              (ScalerDpMacTxSdpGetInfoData(_DP_SDP_TYPE_INFOFRAME_SPD, (ptr)))
#define GET_DP_TX_SPD_INFOFRAME_UPDATED()                   (g_stDpMacTxSdpInfoCtrl.b1DpTxSpdInfoUpated)
#define SET_DP_TX_SPD_INFOFRAME_UPDATED()                   (g_stDpMacTxSdpInfoCtrl.b1DpTxSpdInfoUpated = _TRUE)
#define CLR_DP_TX_SPD_INFOFRAME_UPDATED()                   (g_stDpMacTxSdpInfoCtrl.b1DpTxSpdInfoUpated = _FALSE)
#endif

#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
#define GET_DP_TX_ADAPTIVESYNC_RECEIVED()                   (ScalerDpMacTxSdpInfoRevStateCheck(_DP_SDP_TYPE_ADAPTIVESYNC))
#define GET_DP_TX_ADAPTIVESYNC_CHANGE()                     (ScalerDpMacTxSdpInfoChgCheck(_DP_SDP_TYPE_ADAPTIVESYNC))
#define GET_DP_TX_ADAPTIVESYNC_CHANGE_EVENT()               (ScalerDpMacTxSdpInfoChgEventCheck(_DP_SDP_TYPE_ADAPTIVESYNC))
#define GET_DP_TX_ADAPTIVESYNC_HB3()                        (ScalerDpMacTxSdpInfoHB3Value(_DP_SDP_TYPE_ADAPTIVESYNC))
#endif

#if(_DP_TX_AUDIO_SUPPORT == _ON)
#define GET_DP_TX_AUDIO_INFOFRAME_RECEIVED()                (ScalerDpMacTxSdpInfoRevStateCheck(_DP_SDP_TYPE_INFOFRAME_AUDIO))
#define GET_DP_TX_AUDIO_INFOFRAME_CHANGE()                  (ScalerDpMacTxSdpInfoChgCheck(_DP_SDP_TYPE_INFOFRAME_AUDIO))
#define GET_DP_TX_AUDIO_INFOFRAME_CHANGE_EVENT()            (ScalerDpMacTxSdpInfoChgEventCheck(_DP_SDP_TYPE_INFOFRAME_AUDIO))
#define GET_DP_TX_AUDIO_INFOFRAME_DATA(ptr)                 (ScalerDpMacTxSdpGetInfoData(_DP_SDP_TYPE_INFOFRAME_AUDIO, (ptr)))
#define GET_DP_TX_AUIDO_INFOFRAME_UPDATED()                 (g_stDpMacTxSdpInfoCtrl.b1DpTxAudioInfoUpated)
#define SET_DP_TX_AUDIO_INFOFRAME_UPDATED()                 (g_stDpMacTxSdpInfoCtrl.b1DpTxAudioInfoUpated = _TRUE)
#define CLR_DP_TX_AUDIO_INFOFRAME_UPDATED()                 (g_stDpMacTxSdpInfoCtrl.b1DpTxAudioInfoUpated = _FALSE)
#endif

#define GET_DP_TX_INPUT_LANE_COUNT()                        (g_stDpMacTxInputInfo.b1InterlaceMode)
#define SET_DP_TX_INPUT_LANE_COUNT(x)                       (g_stDpMacTxInputInfo.b1InterlaceMode = (x))

//--------------------------------------------------
// Macros of DP Tx SEC Data Bypass
//--------------------------------------------------
#define GET_DP_MAC_TX_SEC_DATA_FIRST_APPLYED_DONE()         (g_bDpMacTxSecDataFirstApplyed)
#define SET_DP_MAC_TX_SEC_DATA_FIRST_APPLYED_DONE()         (g_bDpMacTxSecDataFirstApplyed = _TRUE)
#define CLR_DP_MAC_TX_SEC_DATA_FIRST_APPLYED_DONE()         (g_bDpMacTxSecDataFirstApplyed = _FALSE)

#define GET_DP_MAC_TX_SEC_COLOR_FIRST_APPLYED_DONE()        (g_bDpMacTxSecColorFirstApplyed)
#define SET_DP_MAC_TX_SEC_COLOR_FIRST_APPLYED_DONE()        (g_bDpMacTxSecColorFirstApplyed = _TRUE)
#define CLR_DP_MAC_TX_SEC_COLOR_FIRST_APPLYED_DONE()        (g_bDpMacTxSecColorFirstApplyed = _FALSE)

//--------------------------------------------------
// Macros of DP Tx Clone Mode
//--------------------------------------------------
#define GET_DP_TX_TARGET_CLONE_MODE()                       (g_stDpMacTxCloneModeSwitch.b1CloneModeCap)
#define SET_DP_TX_TARGET_CLONE_MODE(x)                      (g_stDpMacTxCloneModeSwitch.b1CloneModeCap = (x))

#define SET_DP_TX_MVID_FW_MODE()                            {ScalerSetBit(PBB_F8_DPTX_TOP_RSV3, ~_BIT3, 0x00);}
#define SET_DP_TX_MVID_HW_MODE()                            {ScalerSetBit(PBB_F8_DPTX_TOP_RSV3, ~_BIT3, _BIT3);}

#define GET_DP_MAC_TX_CLONE_DATA_PATH()                     (g_stDpMacTxCloneModeSwitch.ucCloneDataPath)
#define SET_DP_MAC_TX_CLONE_DATA_PATH(x)                    (g_stDpMacTxCloneModeSwitch.ucCloneDataPath = (x))

#define GET_DP_MAC_TX_CLONE_STREAM_INFO_TYPE()              (g_stDpMacTxCloneModeSwitch.enumCloneInfoType)
#define SET_DP_MAC_TX_CLONE_STREAM_INFO_TYPE(x)             (g_stDpMacTxCloneModeSwitch.enumCloneInfoType = (x))

#define GET_DP_MAC_TX_CLONE_STREAM_PRECHECK()               (g_stDpMacTxCloneModeSwitch.ucClonePreCheck)
#define SET_DP_MAC_TX_CLONE_STREAM_PRECHECK(x)              (g_stDpMacTxCloneModeSwitch.ucClonePreCheck = (x))

#define GET_DP_MAC_TX_CLONE_INPUT_PORT()                    (g_stDpMacTxCloneModeSwitch.enumcCloneInputPort)
#define SET_DP_MAC_TX_CLONE_INPUT_PORT(x)                   (g_stDpMacTxCloneModeSwitch.enumcCloneInputPort = (x))
#define CLR_DP_MAC_TX_CLONE_INPUT_PORT(x)                   (g_stDpMacTxCloneModeSwitch.enumcCloneInputPort = _NO_INPUT_PORT)

#define GET_DP_MAC_TX_CLONE_INPUT_PORT_TYPE()               (g_stDpMacTxCloneModeSwitch.enumPortType)
#define SET_DP_MAC_TX_CLONE_INPUT_PORT_TYPE(x)              (g_stDpMacTxCloneModeSwitch.enumPortType = (x))
#define CLR_DP_MAC_TX_CLONE_INPUT_PORT_TYPE(x)              (g_stDpMacTxCloneModeSwitch.enumPortType = _PORT_NONE)

//--------------------------------------------------
// DPTX MAC Macro Define
//--------------------------------------------------
#define SET_DP_TX_MNVID_HW_MEASURE_POPUP()                  {\
                                                                ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT6 | _BIT0), _BIT0);\
                                                                DELAY_5US();\
                                                            }

//--------------------------------------------------
// Definitions of FreeSync AMD SPD & HDR Infoframe Length
//--------------------------------------------------
#define _DP_TX_FREESYNC_INFO_LENGTH                         32
#define _DP_TX_HDR10_INFO_LENGTH                            32
#define _DP_TX_AUDIO_INFO_LENGTH                            10
#define _DP_TX_INFOFRAME_DATA_LENGTH_MAX                    32

//--------------------------------------------------
// Macros of DP Tx Downstream Infomation
//--------------------------------------------------
#define GET_DP_MAC_TX_DOWNSTREAM_DPCD_REV()                 (g_stDpMacTxDownStreamInfo.ucDPCDRev)
#define SET_DP_MAC_TX_DOWNSTREAM_DPCD_REV(x)                (g_stDpMacTxDownStreamInfo.ucDPCDRev = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_PEERDEVICE_TYPE()          (g_stDpMacTxDownStreamInfo.b3PeerDeviceType)
#define SET_DP_MAC_TX_DOWNSTREAM_PEERDEVICE_TYPE(x)         (g_stDpMacTxDownStreamInfo.b3PeerDeviceType = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_LINK_RATE()                (g_stDpMacTxDownStreamInfo.ucLinkRate)
#define SET_DP_MAC_TX_DOWNSTREAM_LINK_RATE(x)               (g_stDpMacTxDownStreamInfo.ucLinkRate = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM()                 (g_stDpMacTxDownStreamInfo.b3LaneNum)
#define SET_DP_MAC_TX_DOWNSTREAM_LANE_NUM(x)                (g_stDpMacTxDownStreamInfo.b3LaneNum = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS()            (g_stDpMacTxDownStreamInfo.b1MSGCapStatus)
#define SET_DP_MAC_TX_DOWNSTREAM_MSGCAP_STATUS(x)           (g_stDpMacTxDownStreamInfo.b1MSGCapStatus = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS()            (g_stDpMacTxDownStreamInfo.b1DPPlugStatus)
#define SET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS(x)           (g_stDpMacTxDownStreamInfo.b1DPPlugStatus = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS()    (g_stDpMacTxDownStreamInfo.b1UpRequestCap)
#define SET_DP_MAC_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS(x)   (g_stDpMacTxDownStreamInfo.b1UpRequestCap = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_CHANGE()            (g_stDpMacTxDownStreamInfo.b1DPPlugChange)
#define SET_DP_MAC_TX_DOWNSTREAM_DPPLUG_CHANGE()            (g_stDpMacTxDownStreamInfo.b1DPPlugChange = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_DPPLUG_CHANGE()            (g_stDpMacTxDownStreamInfo.b1DPPlugChange = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_LEGACYPLUG_STATUS()        (g_stDpMacTxDownStreamInfo.b1LegacyPlugStatus)
#define SET_DP_MAC_TX_DOWNSTREAM_LEGACYPLUG_STATUS(x)       (g_stDpMacTxDownStreamInfo.b1LegacyPlugStatus = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE()            (g_stDpMacTxDownStreamInfo.ucMaxLinkRate)
#define SET_DP_MAC_TX_DOWNSTREAM_MAX_LINK_RATE(x)           (g_stDpMacTxDownStreamInfo.ucMaxLinkRate = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM()             (g_stDpMacTxDownStreamInfo.b5MaxLaneNum)
#define SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM(x)            (g_stDpMacTxDownStreamInfo.b5MaxLaneNum = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM_TEMP()        (g_stDpMacTxDownStreamInfo.b5MaxLaneNumTemp)
#define SET_DP_MAC_TX_DOWNSTREAM_MAX_LANE_NUM_TEMP(x)       (g_stDpMacTxDownStreamInfo.b5MaxLaneNumTemp = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE()       (g_stDpMacTxDownStreamInfo.enumTargetCodingType)
#define SET_DP_MAC_TX_DOWNSTREAM_TARGET_CODING_TYPE(x)      (g_stDpMacTxDownStreamInfo.enumTargetCodingType = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_PRE_CODING_TYPE()          (g_stDpMacTxDownStreamInfo.enumPreCodingType)
#define SET_DP_MAC_TX_DOWNSTREAM_PRE_CODING_TYPE(x)         (g_stDpMacTxDownStreamInfo.enumPreCodingType = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE()              (g_stDpMacTxDownStreamInfo.enumCodingType)
#define SET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE(x)             (g_stDpMacTxDownStreamInfo.enumCodingType = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_TP3_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP3Support)
#define SET_DP_MAC_TX_DOWNSTREAM_TP3_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP3Support = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_TP3_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP3Support = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_TP4_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP4Support)
#define SET_DP_MAC_TX_DOWNSTREAM_TP4_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP4Support = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_TP4_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP4Support = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_128B132B_SUPPORT()         (g_stDpMacTxDownStreamInfo.b1Coding128b132bCap)
#define SET_DP_MAC_TX_DOWNSTREAM_128B132B_SUPPORT()         (g_stDpMacTxDownStreamInfo.b1Coding128b132bCap = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_128B132B_SUPPORT()         (g_stDpMacTxDownStreamInfo.b1Coding128b132bCap = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_UHBR10_SUPPORT()           (g_stDpMacTxDownStreamInfo.b1Uhbr10Cap)
#define SET_DP_MAC_TX_DOWNSTREAM_UHBR10_SUPPORT()           (g_stDpMacTxDownStreamInfo.b1Uhbr10Cap = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_UHBR10_SUPPORT()           (g_stDpMacTxDownStreamInfo.b1Uhbr10Cap = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_UHBR13_5_SUPPORT()         (g_stDpMacTxDownStreamInfo.b1Uhbr13_5Cap)
#define SET_DP_MAC_TX_DOWNSTREAM_UHBR13_5_SUPPORT()         (g_stDpMacTxDownStreamInfo.b1Uhbr13_5Cap = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_UHBR13_5_SUPPORT()         (g_stDpMacTxDownStreamInfo.b1Uhbr13_5Cap = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_UHBR20_SUPPORT()           (g_stDpMacTxDownStreamInfo.b1Uhbr20Cap)
#define SET_DP_MAC_TX_DOWNSTREAM_UHBR20_SUPPORT()           (g_stDpMacTxDownStreamInfo.b1Uhbr20Cap = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_UHBR20_SUPPORT()           (g_stDpMacTxDownStreamInfo.b1Uhbr20Cap = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_ENHANCE_FRAMING()          (g_stDpMacTxDownStreamInfo.b1EnhanceFraming)
#define SET_DP_MAC_TX_DOWNSTREAM_ENHANCE_FRAMING(x)         (g_stDpMacTxDownStreamInfo.b1EnhanceFraming = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD()              (g_stDpMacTxDownStreamInfo.b1SSCSupport)
#define SET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD(x)             (g_stDpMacTxDownStreamInfo.b1SSCSupport = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_MSA_IGNORED()              (g_stDpMacTxDownStreamInfo.b1MsaIgnored)
#define SET_DP_MAC_TX_DOWNSTREAM_MSA_IGNORED(x)             (g_stDpMacTxDownStreamInfo.b1MsaIgnored = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT()       (g_stDpMacTxDownStreamInfo.ucCurrentSinkCount)
#define SET_DP_MAC_TX_DOWNSTREAM_CURRENT_SINK_COUNT(x)      (g_stDpMacTxDownStreamInfo.ucCurrentSinkCount = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_PRE_SINK_COUNT()           (g_stDpMacTxDownStreamInfo.ucPreSinkCount)
#define SET_DP_MAC_TX_DOWNSTREAM_PRE_SINK_COUNT(x)          (g_stDpMacTxDownStreamInfo.ucPreSinkCount = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_SINK_COUNT_CHANGE()        (g_stDpMacTxDownStreamInfo.b1DownStreamSinkCountChange)
#define SET_DP_MAC_TX_DOWNSTREAM_SINK_COUNT_CHANGE()        (g_stDpMacTxDownStreamInfo.b1DownStreamSinkCountChange = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_SINK_COUNT_CHANGE()        (g_stDpMacTxDownStreamInfo.b1DownStreamSinkCountChange = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE()               (g_stDpMacTxDownStreamInfo.b1DownStreamCapChange)
#define SET_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE()               (g_stDpMacTxDownStreamInfo.b1DownStreamCapChange = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_CAP_CHANGE()               (g_stDpMacTxDownStreamInfo.b1DownStreamCapChange = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_TP3_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP3Support)
#define SET_DP_MAC_TX_DOWNSTREAM_TP3_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP3Support = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_TP3_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP3Support = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_TP4_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP4Support)
#define SET_DP_MAC_TX_DOWNSTREAM_TP4_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP4Support = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_TP4_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1TP4Support = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP()            (g_stDpMacTxDownStreamInfo.b1NumberOfSDP)
#define SET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP(x)           (g_stDpMacTxDownStreamInfo.b1NumberOfSDP = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK()       (g_stDpMacTxDownStreamInfo.b1NumberOfSDPSink)
#define SET_DP_MAC_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK(x)      (g_stDpMacTxDownStreamInfo.b1NumberOfSDPSink = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_INFO_READY()               (g_stDpMacTxDownStreamInfo.b1DownStreamInfoReady)
#define SET_DP_MAC_TX_DOWNSTREAM_INFO_READY()               (g_stDpMacTxDownStreamInfo.b1DownStreamInfoReady = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_INFO_READY()               (g_stDpMacTxDownStreamInfo.b1DownStreamInfoReady = _FALSE)

#define GET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM()                (g_stDpMacTxDownStreamInfo.ucLTTPRNum)
#define SET_DP_MAC_TX_DOWNSTREAM_LTTPR_NUM(x)               (g_stDpMacTxDownStreamInfo.ucLTTPRNum = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_LTTPR_EXT_WAKE_TIMEOUT()   (g_stDpMacTxDownStreamInfo.ucExtWakeTimeout)
#define SET_DP_MAC_TX_DOWNSTREAM_LTTPR_EXT_WAKE_TIMEOUT(x)  (g_stDpMacTxDownStreamInfo.ucExtWakeTimeout = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_SINK_EXT_WAKE_TIMEOUT()    (g_stDpMacTxDownStreamInfo.ucSinkExWakeTimeOut)
#define SET_DP_MAC_TX_DOWNSTREAM_SINK_EXT_WAKE_TIMEOUT(x)   (g_stDpMacTxDownStreamInfo.ucSinkExWakeTimeOut = (x))

#define GET_DP_MAC_TX_DOWNSTREAM_420_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1DownStreamSink420Support)
#define SET_DP_MAC_TX_DOWNSTREAM_420_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1DownStreamSink420Support = _TRUE)
#define CLR_DP_MAC_TX_DOWNSTREAM_420_SUPPORT()              (g_stDpMacTxDownStreamInfo.b1DownStreamSink420Support = _FALSE)
//--------------------------------------------------
// Macros of Mac TX ACT
//--------------------------------------------------
#define GET_DP_MAC_TX_REG_SEND_ACT_FLAG()                   (ScalerDpMacTxGetSendActFlag())
#define CLR_DP_MAC_TX_REG_SEND_ACT_FLAG()                   (ScalerDpMacTxClearSendActFlag())
#define SET_DP_MAC_TX_REG_SEND_ACT_ENABLE()                 (ScalerDpMacTxEnableSendAct())

//--------------------------------------------------
// Macro of MST Tx Infomation
//--------------------------------------------------
#define GET_DP_MST_TX_ENABLE()                              (ScalerGetBit(PBB_00_DP_PHY_CTRL, _BIT1) == _BIT1)
#define SET_DP_MST_TX_ENABLE()                              {ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, _BIT1);}
#define CLR_DP_MST_TX_ENABLE()                              {ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);}

//--------------------------------------------------
// Macro of Mac TX Stream to PayloadID mapping
//--------------------------------------------------
#define GET_DP_MAC_TX_DAISY_NO_EMPTY_STREAM()               (ScalerDpMacTxSearchMatchStream(0) == _DP_ST_NONE)
#define GET_DP_MAC_TX_DAISY_STREAM_EXIST(x)                 (ScalerDpMacTxSearchMatchStream(x) != _DP_ST_NONE)
#define GET_DP_MAC_TX_DAISY_STREAM_NOT_EXIST(x)             (ScalerDpMacTxSearchMatchStream(x) == _DP_ST_NONE)
//--------------------------------------------------
// Definitions of MST Stream Backup Infomation
//--------------------------------------------------
#define SET_DP_MAC_TX_ST_SOURCE_BACKUP(x, y)                (g_stDpMacTxStreamInfoBackup.pucSTx_Source[x] = (y))
#define GET_DP_MAC_TX_ST_SOURCE_BACKUP(x)                   (g_stDpMacTxStreamInfoBackup.pucSTx_Source[x])
#define SET_DP_MAC_TX_ST_SOURCE_CHANGE()                    (g_stDpMacTxStreamInfoBackup.b1SourceChange = _TRUE)
#define CLR_DP_MAC_TX_ST_SOURCE_CHANGE()                    (g_stDpMacTxStreamInfoBackup.b1SourceChange = _FALSE)
#define GET_DP_MAC_TX_ST_SOURCE_CHANGE()                    (g_stDpMacTxStreamInfoBackup.b1SourceChange)

//--------------------------------------------------
// Define Tx Daisy Stream Position Macro
//--------------------------------------------------
#define SET_DP_MAC_TX_REG_DAISY_CHAIN_LANE_NUM(x)           {ScalerSetBit(PA_05_DAISY_CTRL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), ((x) << 4));}

#define GET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(x)        (ScalerGetBit(ScalerDpMacTxGetDaisyStreamStartPositionRegAddress(x), 0x3F))
#define SET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(x, y)     {ScalerSetBit(ScalerDpMacTxGetDaisyStreamStartPositionRegAddress(x), ~0x3F, ((y) & 0x3F));}

#define GET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(x)          (ScalerGetBit((ScalerDpMacTxGetDaisyStreamStartPositionRegAddress(x) + 1), 0x3F))
#define SET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(x, y)       {ScalerSetBit((ScalerDpMacTxGetDaisyStreamStartPositionRegAddress(x) + 1), ~0x3F, ((y) & 0x3F));}

#define GET_DP_MAC_TX_DAISY_ST_STATUS_REG(x)                (ScalerDpMacTxGetDaisyStreamStatusReg(x))
#define SET_DP_MAC_TX_DAISY_ST_STATUS_REG(x, y)             (ScalerDpMacTxSetDaisyStreamStatusReg((x), (y)))

#define GET_DP_MAC_TX_DAISY_ST_TIMESLOT_LENGTH(x)           (GET_DP_MAC_TX_DAISY_ST_END_POSITION_REG(x) - GET_DP_MAC_TX_DAISY_ST_START_POSITION_REG(x) + 1)

// Macros of DP Tx Edid Information
//--------------------------------------------------
#define GET_DP_MAC_TX_EDID_VENDOR_MODEL()                   (g_enumDpMacTxEdidVendorModel)
#define SET_DP_MAC_TX_EDID_VENDOR_MODEL(x)                  (g_enumDpMacTxEdidVendorModel = (x))
#define CLR_DP_MAC_TX_EDID_VENDOR_MODEL()                   (g_enumDpMacTxEdidVendorModel = 0)

//--------------------------------------------------
// Macros of DP Tx Edid Bandwith
//--------------------------------------------------
#define GET_DP_MAC_TX_EDID_BW()                             (g_usDpMacTxEdidBw)
#define SET_DP_MAC_TX_EDID_BW(x)                            (g_usDpMacTxEdidBw = (x))

//--------------------------------------------------
// Macros of DP Tx Lttpr Mode
//--------------------------------------------------
#define GET_DP_MAC_TX_LTTPR_MODE_8B10B()                    (_DP_TX_LTTPR_MODE_8B10B)

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Define Output Stream Link Establish Status
//--------------------------------------------------
#define GET_DP_MAC_TX_LINK_ESTABLISH_STATUS()               (g_enumDpMacTxLinkEstablishStatus)
#define SET_DP_MAC_TX_LINK_ESTABLISH_STATUS(x)              (g_enumDpMacTxLinkEstablishStatus = (x))
#define CLR_DP_MAC_TX_LINK_ESTABLISH_STATUS()               (g_enumDpMacTxLinkEstablishStatus = _LINK_ESTABLISH_NONE)

//--------------------------------------------------
// Define Tx backup Rx coding type
//--------------------------------------------------
#define GET_DP_MAC_TX_BACKUP_RX_CODING_TYPE()               (g_enumDpMacTxBackupRxCodingType)
#define SET_DP_MAC_TX_BACKUP_RX_CODING_TYPE(x)              (g_enumDpMacTxBackupRxCodingType = (x))
#define CLR_DP_MAC_TX_BACKUP_RX_CODING_TYPE()               (g_enumDpMacTxBackupRxCodingType = _CODING_TYPE_NONE)

//--------------------------------------------------
// Define Tx backup Rx coding type
//--------------------------------------------------
#define GET_DP_MAC_TX_MAIN_PORT_CHANGE()                    (g_ucDpMacTxMainPortChange)
#define SET_DP_MAC_TX_MAIN_PORT_CHANGE()                    (g_ucDpMacTxMainPortChange = _TRUE)
#define CLR_DP_MAC_TX_MAIN_PORT_CHANGE()                    (g_ucDpMacTxMainPortChange = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1DpTxSpdInfoUpated : 1;
    BYTE b1DpTxHdrInfoUpated : 1;
    BYTE b1DpTxAudioInfoUpated : 1;
} StructDpTxSdpCtrl;

//--------------------------------------------------
// Struct for Stream Info Backup
//--------------------------------------------------
typedef struct
{
    BYTE pucSTx_Source[_HW_DP_MST_ST_SOURCE_COUNT];
    BYTE pucSTx_Start[_HW_DP_MST_ST_SOURCE_COUNT];
    BYTE pucSTx_End[_HW_DP_MST_ST_SOURCE_COUNT];
    BYTE pucSTx_Status[_HW_DP_MST_ST_SOURCE_COUNT];
    BYTE b1SourceChange : 1;
    BYTE b1TimeSlotChange : 1;
}StructTxStreamInfoBackup;

typedef struct
{
    WORD usDscPicWidth;
    WORD usDscSliceWidth;
    WORD usDscBitsPerPixel;
    BYTE b1DscNative420 : 1;
    BYTE b1DscNative422 : 1;
}StructDpMacTxInputDscInfo;

typedef enum
{
    _DP_TX_LEVEL_0 = 0x00,
    _DP_TX_LEVEL_1,
    _DP_TX_LEVEL_2,
    _DP_TX_LEVEL_3,
} EnumDpTxSignalLevel;

typedef enum
{
    _DP_TP_NONE = 0x00,
    _DP_TP_1 = 0x01,
    _DP_TP_2 = 0x02,
    _DP_TP_3 = 0x03,
    _DP_TP_4 = 0x07,
} EnumDpTxTrainPattern;

typedef enum
{
    _DP_LANE0_MAX_POST_CURSOR2_REACHED = _BIT2,
    _DP_LANE1_MAX_POST_CURSOR2_REACHED = _BIT6,
    _DP_LANE2_MAX_POST_CURSOR2_REACHED = _BIT2,
    _DP_LANE3_MAX_POST_CURSOR2_REACHED = _BIT6,
    _DP_SCRAMBLING_DISABLE = _BIT5,
} EnumDpTxLinkTrainAdditionalInfo;

// Main Link Pattern
typedef enum
{
    _DP_TX_OUTPUT_IDLE_PATTERN = 0x00,
    _DP_TX_OUTPUT_TPS1 = _BIT4,
    _DP_TX_OUTPUT_TPS2 = _BIT5,
    _DP_TX_OUTPUT_TPS3 = (_BIT5 | _BIT4),
    _DP_TX_OUTPUT_VIDEO_PATTERN = _BIT6,
    _DP_TX_OUTPUT_PRBS7 = (_BIT6 | _BIT4),
    _DP_TX_OUTPUT_80BIT_CUSTOM_PATTERN = (_BIT6 | _BIT5),
    _DP_TX_OUTPUT_EYE_PATTERN = (_BIT6 | _BIT5 | _BIT4),
} EnumDPTxMainLinkPattern;

//--------------------------------------------------
// Enumerations of DP Tx Mode State
//--------------------------------------------------
typedef enum
{
    _DP_TX_MODE_STATUS_UNPLUG = 0x00,
    _DP_TX_MODE_STATUS_LINK_OFF,
    _DP_TX_MODE_STATUS_INITIAL,
    _DP_TX_MODE_STATUS_LINK_TRAINING,
    _DP_TX_MODE_STATUS_LINK_ON,
    _DP_TX_MODE_STATUS_DC_OFF,
    _DP_TX_MODE_STATUS_AUTOTEST,
} EnumDPTxModeStatus;

typedef enum
{
    _DP_TX_HPD_5_TIMER = 0x00,
    _DP_TX_HPD_10_TIMER,
    _DP_TX_HPD_20_TIMER,
    _DP_TX_HPD_100_TIMER,
} EnumDPTxHPDTimer;

typedef enum
{
    _DP_TX_HPD_NONE = 0x00,
    _DP_TX_HPD_UNPLUG = _BIT0,
    _DP_TX_HPD_REPLUG = _BIT1,
    _DP_TX_HPD_IRQ = _BIT2,
} EnumDPTxHPDEventType;

typedef enum
{
    _DP_TX_HPD_NO_EVENT = 0x00,
    _DP_TX_HPD_UNPLUG_EVENT,
    _DP_TX_HPD_PLUG_EVENT,
    _DP_TX_HPD_IRQ_EVENT,
} EnumDPTxHPDEvent;

typedef enum
{
    _DP_TX_IRQ_HPD_NONE = 0x00,
    _DP_TX_IRQ_HPD_CP_IRQ = _BIT0,
    _DP_TX_IRQ_HPD_MCCS_IRQ = _BIT1,
    _DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ = _BIT2,
    _DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ = _BIT3,
    _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ = _BIT4,
    _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ = _BIT5,
    _DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ = _BIT6,
    _DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST = _BIT7,
    _DP_TX_IRQ_HPD_DOWNSTREAM_PORT_STATUS_CHANGE = _BIT8,
    _DP_TX_IRQ_HPD_CEC_IRQ = _BIT9,
    _DP_TX_IRQ_HPD_DSC_ERROR_STATUS_IRQ = _BIT10,
} EnumDPTxIRQEventType;

//--------------------------------------------------
// Enumerations of Embeded Typec Tx HPD Queue Type
//--------------------------------------------------
typedef enum
{
    _DP_TX_HPD_QUEUE_NONE = 0x00,
    _DP_TX_HPD_QUEUE_LOW = _BIT1,
    _DP_TX_HPD_QUEUE_HIGH = _BIT2,
    _DP_TX_HPD_QUEUE_LOW_HIGH = _BIT3,
    _DP_TX_HPD_QUEUE_HIGH_LOW = _BIT4,
    _DP_TX_HPD_QUEUE_IRQ = _BIT5,
} EnumDpTxHpdQueueType;

typedef enum
{
    _DP_TX_TRAINING_NO_RESULT = 0x00,
    _DP_TX_TRAINING_PATTERN1_FAIL,
    _DP_TX_TRAINING_PATTERN2_FAIL,
    _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL,
    _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL,
    _DP_TX_TRAINING_PATTERN1_PASS,
    _DP_TX_TRAINING_PATTERN2_PASS,
    _DP_TX_TRAINING_LTTPR_PASS, // LT LTTPR Partial Pass
    _DP_TX_TRAINING_PASS,       // LT DP Rx Pass
    _DP_TX_TRAINING_FAIL,
    _DP_TX_TRAINING_LTTPR_EQ_FAIL,
    _DP_TX_TRAINING_LTTPR_EQ_PASS,
    _DP_TX_TRAINING_EQ_FAIL,
    _DP_TX_TRAINING_EQ_PASS,
    _DP_TX_TRAINING_CDS_FAIL,
    _DP_TX_TRAINING_CDS_FAIL_POLLING,
    _DP_TX_TRAINING_CDS_PASS,
} EnumDPTxLTResult;

//--------------------------------------------------
//  DP Rx Pixel Mode
//--------------------------------------------------
typedef enum
{
    _DP_TX_1_PIXEL_MODE = 0x00,
    _DP_TX_2_PIXEL_MODE = 0x01,
    _DP_TX_4_PIXEL_MODE = 0x02,
    _DP_TX_NONE_PIXEL_MODE = 0xFF,
} EnumDpTxPixelMode;

//--------------------------------------------------
//Audio Packet Type
//--------------------------------------------------
typedef enum
{
#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
    _SEC_PACKET_TYPE_PPS = 0x00,
#endif
    _SEC_PACKET_TYPE_AUDIO_TIMESTAMP = 0x01,
    _SEC_PACKET_TYPE_AUDIO_STREAM = 0x02,
    _SEC_PACKET_TYPE_VSC = 0x07,
    _SEC_PACKET_TYPE_RSV0 = 0x08,
    _SEC_PACKET_TYPE_VSIF = 0x09,
#if(_DP_FREESYNC_SUPPORT == _ON)
    _SEC_PACKET_TYPE_INFOFRAME_FREESYNC = _SEC_PACKET_TYPE_VSIF,
#endif
    _SEC_PACKET_TYPE_INFOFRAME_AVI = 0x0A,
    _SEC_PACKET_TYPE_INFOFRAME_AUDIO = 0x0C,
    _SEC_PACKET_TYPE_INFOFRAME_MPEG = 0x0D,
#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    _SEC_PACKET_TYPE_INFOFRAME_HDR = _SEC_PACKET_TYPE_INFOFRAME_MPEG,
#endif
} EnumDPTxSecDataPacketType;

//--------------------------------------------------
// SDP Packet Type for Data Bytes Assignment Used
//--------------------------------------------------
typedef enum
{
    _SDP_DB_TYPE_VSIF = 0x00,
#if(_DP_FREESYNC_SUPPORT == _ON)
    _SDP_DB_TYPE_INFOFRAME_FREESYNC = _SDP_DB_TYPE_VSIF,
#endif
    _SDP_DB_TYPE_INFOFRAME_AUDIO = 0x01,
    _SDP_DB_TYPE_INFOFRAME_AVI = 0x02,
    _SDP_DB_TYPE_INFOFRAME_MPEG = 0x03,
#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    _SDP_DB_TYPE_INFOFRAME_HDR = _SDP_DB_TYPE_INFOFRAME_MPEG,
#endif
    _SDP_DB_TYPE_RSV0 = 0x04,
    _SDP_DB_TYPE_INFOFRAME_VSC = 0x07,
    _SDP_DB_TYPE_NONE,
} EnumDPTxSdpTypeForDB;

//--------------------------------------------------
// SDP Packet Type for Data Bytes Assignment Used
//--------------------------------------------------
typedef enum
{
    _SDP_AUDIO_EN = _BIT0,
    _SDP_AUDIO_TIMESTAMP_EN = _BIT1,
    _SDP_VSC_EN = _BIT2,
    _SDP_INFOFRAME_AUDIO_EN = _BIT3,
    _SDP_INFOFRAME_AVI_EN = _BIT4,
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
    _SDP_ADAPTIVESYNC_EN = _SDP_INFOFRAME_AVI_EN,
#endif
    _SDP_INFOFRAME_MPEG_EN = _BIT5,
#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    _SDP_INFOFRAME_HDR_EN = _SDP_INFOFRAME_MPEG_EN,
#endif
    _SDP_INFOFRAME_VS_EN = _BIT6,
#if(_DP_FREESYNC_SUPPORT == _ON)
    _SDP_INFOFRAME_FREESYNC_EN = _SDP_INFOFRAME_VS_EN,
#endif
    _SDP_INFOFRAME_RSV0_EN = _BIT7,
} EnumDPTxSecFunctionCtrl;

//--------------------------------------------------
// SDP Double Buffer Type
//--------------------------------------------------
typedef enum
{
    _DP_TX_SDP_DBUF_NONE,
    _DP_TX_SDP_DBUF_IMMEDIATE_ACTIVE = _BIT0,
    _DP_TX_SDP_DBUF_WAIT_FOR_VBLANK_RISING = (_BIT1 | _BIT0),
} EnumDPTxSdpDoubleBufferType;

//--------------------------------------------------
// Enumerations of Audio Play State
//--------------------------------------------------
typedef enum
{
    _DP_TX_AUDIO_OFF = 0x00,
    _DP_TX_AUDIO_PRESET,
    _DP_TX_AUDIO_FORMAT_CHANGE,
    _DP_TX_AUDIO_ON,
} EnumDPTxAudioPlayState;

//--------------------------------------------------
// Enumerations of Audio Sampling Freq
//--------------------------------------------------
typedef enum
{
    _DP_TX_AUDIO_INFOFRAME_FREQ_NO_AUDIO = 0,
    _DP_TX_AUDIO_INFOFRAME_FREQ_32K = 1,
    _DP_TX_AUDIO_INFOFRAME_FREQ_44_1K = 2,
    _DP_TX_AUDIO_INFOFRAME_FREQ_48K = 3,
    _DP_TX_AUDIO_INFOFRAME_FREQ_88_2K = 4,
    _DP_TX_AUDIO_INFOFRAME_FREQ_96K = 5,
    _DP_TX_AUDIO_INFOFRAME_FREQ_176_4K = 6,
    _DP_TX_AUDIO_INFOFRAME_FREQ_192K = 7,
} EnumDPTxAudioInfoframeSamplingFreq;

//--------------------------------------------------
// Definitions of MSA Colorimetry Value
//--------------------------------------------------
typedef enum
{
    _DP_MSA_COLORIMETRY_RGB_SRGB_VESA = 0,
    _DP_MSA_COLORIMETRY_RGB_SRGB_CEA = _BIT3,
    _DP_MSA_COLORIMETRY_RGB_XRRGB = (_BIT2 | _BIT1),
    _DP_MSA_COLORIMETRY_RGB_SCRGB = (_BIT4 | _BIT2 | _BIT1),
    _DP_MSA_COLORIMETRY_Y_ONLY = _BIT7,
    _DP_MSA_COLORIMETRY_RAW = (_BIT7 | _BIT1),
    _DP_MSA_COLORIMETRY_YCC422_ITUR_BT601 = (_BIT3 | _BIT1),
    _DP_MSA_COLORIMETRY_YCC444_ITUR_BT601 = (_BIT3 | _BIT2),
    _DP_MSA_COLORIMETRY_YCC422_ITUR_BT709 = (_BIT4 | _BIT3 | _BIT1),
    _DP_MSA_COLORIMETRY_YCC444_ITUR_BT709 = (_BIT4 | _BIT3 | _BIT2),
    _DP_MSA_COLORIMETRY_YCC422_XVYCC601 = _BIT1,
    _DP_MSA_COLORIMETRY_YCC444_XVYCC601 = _BIT2,
    _DP_MSA_COLORIMETRY_YCC422_XVYCC709 = (_BIT4 | _BIT1),
    _DP_MSA_COLORIMETRY_YCC444_XVYCC709 = (_BIT4 | _BIT2),
    _DP_MSA_COLORIMETRY_RGB_ADOBERGB = (_BIT4 | _BIT3),
    _DP_MSA_COLORIMETRY_RGB_DCI_P3 = (_BIT3 | _BIT2 | _BIT1),
    _DP_MSA_COLORIMETRY_RGB_COLOR_PROFILE = (_BIT4 | _BIT3 | _BIT2 | _BIT1),
} EnumDpMsaColorimetry;

//--------------------------------------------------
// Definitions of VSC SDP Color Space
//--------------------------------------------------
typedef enum
{
    _DP_VSC_COLOR_SPACE_RGB = 0x00,
    _DP_VSC_COLOR_SPACE_YCBCR444 = 0x01,
    _DP_VSC_COLOR_SPACE_YCBCR422 = 0x02,
    _DP_VSC_COLOR_SPACE_YCBCR420 = 0x03,
    _DP_VSC_COLOR_SPACE_Y_ONLY = 0x04,
    _DP_VSC_COLOR_SPACE_RAW = 0x05,
    _DP_VSC_COLOR_SPACE_RESERVED,
} EnumDpVscSdpColorSpace;

//--------------------------------------------------
// Definitions of VSC SDP Colorimetry Value for RGB
//--------------------------------------------------
typedef enum
{
    _DP_VSC_COLORIMETRY_RGB_SRGB = 0x00,
    _DP_VSC_COLORIMETRY_RGB_XRRGB = 0x01,
    _DP_VSC_COLORIMETRY_RGB_SCRGB = 0x02,
    _DP_VSC_COLORIMETRY_RGB_ADOBERGB = 0x03,
    _DP_VSC_COLORIMETRY_RGB_DCI_P3 = 0x04,
    _DP_VSC_COLORIMETRY_RGB_COLOR_PROFILE = 0x05,
    _DP_VSC_COLORIMETRY_RGB_ITUR_BT2020 = 0x06,
    _DP_VSC_COLORIMETRY_RGB_RESERVED,
} EnumDpVscSdpRgbColorimetry;

//--------------------------------------------------
// Definitions of VSC SDP Colorimetry Value for YUV
//--------------------------------------------------
typedef enum
{
    _DP_VSC_COLORIMETRY_YCC_ITUR_BT601 = 0x00,
    _DP_VSC_COLORIMETRY_YCC_ITUR_BT709 = 0x01,
    _DP_VSC_COLORIMETRY_YCC_XVYCC601 = 0x02,
    _DP_VSC_COLORIMETRY_YCC_XVYCC709 = 0x03,
    _DP_VSC_COLORIMETRY_YCC_SYCC601 = 0x04,
    _DP_VSC_COLORIMETRY_YCC_ADOBEYCC601 = 0x05,
    _DP_VSC_COLORIMETRY_YCC_ITUR_BT2020_CL = 0x06,
    _DP_VSC_COLORIMETRY_YCC_ITUR_BT2020_NCL = 0x07,
    _DP_VSC_COLORIMETRY_YCC_RESERVED,
} EnumDpVscSdpYuvColorimetry;

//--------------------------------------------------
// Definitions of VSC SDP Colorimetry Value for Y Only
//--------------------------------------------------
typedef enum
{
    _DP_VSC_COLORIMETRY_Y_ONLY_DICOM_PART14 = 0x00,
    _DP_VSC_COLORIMETRY_Y_ONLY_RESERVED,
} EnumDpVscSdpYOnlyColorimetry;

//--------------------------------------------------
// Definitions of VSC SDP Colorimetry Value for RAW
//--------------------------------------------------
typedef enum
{
    _DP_VSC_COLORIMETRY_RAW_CUSTOM_COLOR_PROFILE = 0x00,
    _DP_VSC_COLORIMETRY_RAW_RESERVED,
} EnumDpVscSdpRawColorimetry;

//--------------------------------------------------
// Definitions of VSC SDP Quantization Range Value
//--------------------------------------------------
typedef enum
{
    _DP_VSC_QUANTIZATION_FULL_RANGE = 0x00,
    _DP_VSC_QUANTIZATION_LIMIT_RANGE = 0x01,
} EnumDpVscSdpQuantizationRange;

//--------------------------------------------------
// Definitions of VSC SDP Content Type
//--------------------------------------------------
typedef enum
{
    _DP_VSC_CONTENT_TYPE_NOT_DEFINED = 0x00,
    _DP_VSC_CONTENT_TYPE_GRAPHICS,
    _DP_VSC_CONTENT_TYPE_PHOTO,
    _DP_VSC_CONTENT_TYPE_VIDEO,
    _DP_VSC_CONTENT_TYPE_GAME,
    _DP_VSC_CONTENT_TYPE_RESERVED,
} EnumDpVscSdpContentType;

//--------------------------------------------------
// Enumerations of DP TX CTS Test
//--------------------------------------------------
typedef enum
{
    _DP_TX_CTS_NONE = 0x00,
    _DP_TX_CTS_TEST_LINK_TRAINING = _BIT0,
    _DP_TX_CTS_TEST_PATTERN = _BIT1,
    _DP_TX_CTS_TEST_EDID_READ = _BIT2,
    _DP_TX_CTS_PHY_TEST_PATTERN = _BIT3,
    _DP_TX_CTS_PHY_DP20 = _BIT4,
} EnumDPTxCtsTestRequestType;

typedef enum
{
    _TEST_ACK = _BIT0,
    _TEST_NAK = _BIT1,
    _TEST_EDID_CHECKSUM_WRITE = _BIT2,
} EnumDPTxCtsTestResponseType;


//--------------------------------------------------
// Enumerations of Audio Sampling Freq
//--------------------------------------------------
typedef enum
{
    _DP_TX_AUDIO_FREQ_NO_AUDIO = 0,
    _DP_TX_AUDIO_FREQ_32K = 1,
    _DP_TX_AUDIO_FREQ_44_1K = 2,
    _DP_TX_AUDIO_FREQ_48K = 3,
    _DP_TX_AUDIO_FREQ_64K = 4,
    _DP_TX_AUDIO_FREQ_88_2K = 5,
    _DP_TX_AUDIO_FREQ_96K = 6,
    _DP_TX_AUDIO_FREQ_128K = 7,
    _DP_TX_AUDIO_FREQ_176_4K = 8,
    _DP_TX_AUDIO_FREQ_192K = 9,
    _DP_TX_AUDIO_FREQ_256K = 10,
    _DP_TX_AUDIO_FREQ_352_8K = 11,
    _DP_TX_AUDIO_FREQ_384K = 12,
    _DP_TX_AUDIO_FREQ_512K = 13,
    _DP_TX_AUDIO_FREQ_705_6K = 14,
    _DP_TX_AUDIO_FREQ_768K = 15,
} EnumDPTxAudioSamplingFreq;

//--------------------------------------------------
// Enumerations of EDID Vendor Model
//--------------------------------------------------
typedef enum
{
    _EDID_VENDOR_NONE = 0x00,
    _EDID_VENDOR_ASUS_PA248,
} EnumDPTxEdidVendorModel;

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of MST MST Reply status
//--------------------------------------------------
typedef enum
{
    _LINK_ESTABLISH_INITIAL = 0x00,
    _LINK_ESTABLISH_WAIT,
    _LINK_ESTABLISH_FAIL,
    _LINK_ESTABLISH_READY,
    _LINK_ESTABLISH_NONE,
} EnumDpMacTxLinkEstablishStatus;
#endif

//--------------------------------------------------
// Enumerations of DSC Stream Transmit Mode
//--------------------------------------------------
typedef enum
{
    _SOURCE_PASSTHROUGH_DSC_BY_NONE = 0x00,
    _SOURCE_PASSTHROUGH_DSC_BY_ENABLE_BRANCH,
    _SOURCE_PASSTHROUGH_DSC_BY_ENABLE_DFP_SINK,
    _SOURCE_PASSTHROUGH_DSC_BY_ENABLE_BRANCH_AND_DFP_SINK,
    _SOURCE_PASSTHROUGH_DSC_BY_ENABLE_DSC_STREAM,
} EnumDPTxDscPassThroughType;

//--------------------------------------------------
// Struct for DSC Info Backup
//--------------------------------------------------
typedef struct
{
    BYTE b1DscSupport : 1;
    BYTE b1DscPassThrough : 1;
    BYTE b1DscDetectPassThrough : 1;
    BYTE b1DscDetectEnable : 1;
    EnumDPTxDscPassThroughType b3DscPassThroughType : 3;
    WORD usDscInitChunkSize;
    WORD usDscInitTUSize;
} StructDpTxDownStreamDscInfo;

typedef enum
{
    _FORCE_DFP_DSC_BY_NONE = 0x00,
    _FORCE_DFP_DSC_ENABLE,
    _FORCE_DFP_DSC_DISABLE,
} EnumDPTxDscForceDfpEnableType;

typedef struct
{
    EnumDPTxModeStatus b3ModeState : 3;
    BYTE b1ModeStateChanged : 1;
    EnumDPTxHPDEvent b3HPDEvent : 3;
    BYTE b1HPDDebounce : 1;
//------------------------------------
    BYTE b1FirstHPD : 1;
    BYTE b1IRQHPDDetected : 1;
    BYTE b1ForceLT : 1;
} StructDPTxModeInfoType;

typedef struct
{
    BYTE b3ColorDepth : 3;
    EnumColorSpace b3ColorSpace : 3;
    BYTE b1AudioReadyToPlay : 1;
    BYTE b1InterlaceMode : 1;
//------------------------------------
    BYTE b4AudioCodingType : 4;
    EnumColorimetry b4Colorimetry : 4;
//------------------------------------
    EnumColorimetryExt b5ExtColorimetry : 5;
    EnumAudioChannelCount b3AudioChannelCount : 3;
//------------------------------------
    EnumDPTxAudioInfoframeSamplingFreq b3AudioInfoframeSamplingFrequency : 3;
    BYTE b1InterlaceVTotalNumber : 1;
    EnumColorRGBQuantization b2RgbQuantizationRange : 2;
    EnumColorYCCQuantization b2YccQuantizationRange : 2;
//------------------------------------
    BYTE b3ContentType : 3;
    EnumDpLaneCount b3TxInputLaneCount : 3;
    EnumDpLinkChannelCodingType b2TxInputChannelCoding : 2;
//------------------------------------
    BYTE b1SleepAudioSupport : 1;
    BYTE b1SleepAudioChangeEvent : 1;
//------------------------------------
    EnumDPTxAudioPath enumAudioInputPath;
    BYTE ucTxInputPort;
    BYTE ucAudioFrequency;
    WORD usInputPixelClk;
    WORD usHorizontalDataEnablePeriod;
    BYTE ucTxInputPixelMode;
} StructDPTxInputInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDPTxModeInfoType g_stDpMacTxModeInfo;
extern StructDigitalColorInfoChanged g_stDpMacTxInputDigitalColorInfoChanged;
extern StructDPTxInputInfo g_stDpMacTxInputInfo;
extern EnumDPTxIRQEventType g_enumDpMacTxIRQType;
extern volatile EnumDPTxIRQEventType g_enumDpMacTxIRQTypeInt;
extern EnumDPTxTRQEventHDCPType g_enumDpMacTxIRQHdcpType;

#if((_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON) && (_PX_PORT_CTRL_EMBEDDED_SUPPORT == _ON))
extern EnumDpTxHpdQueueType g_enumDpMacTxHpdQueueType;
extern EnumDpTxHpdQueueType g_enumDpMacTxHpdQueueTypeBackup;
extern bit g_bDpMacTxIRQHpdQueue;
extern BYTE g_ucDpMacTxHpdLevel;
#endif

extern StructCloneModeSwitchInfo g_stDpMacTxCloneModeSwitch;
extern BYTE g_pucDpMacTxHdcpKsvFifo[_DP_TX_HDCP14_DEVICE_COUNT_MAX * 5];
extern BYTE g_pucDpMacTxHdcpDownStreamV[20];
extern StructTimingInfo g_stDpMacTxInputTimingInfo;

extern volatile bit g_bDpMacTxExceedBW;
extern volatile bit g_bDpMacTxIRQHPDDetected;
extern volatile bit g_bDpMacTxSourceChanged;
extern volatile BYTE g_ucDpMacTxStreamSource;

#if(_DP_TX_FEC_SUPPORT == _ON)
extern bit g_bDpMacTxCloneFecEnable;
#endif

extern bit g_bDpMacTxDownStreamVscSdpSupport;
extern bit g_bDpMacTxDownStreamFecSupport;

extern BYTE g_pucDpMacTxVscSdpDB16to18[3];

extern StructDownStreamInfo g_stDpMacTxDownStreamInfo;
extern EnumDPTxEdidVendorModel g_enumDpMacTxEdidVendorModel;

// Tx Daisy Stream
extern BYTE g_pucDpMacTxStreamToIdMapping[];
extern volatile StructTxStreamInfoBackup g_stDpMacTxStreamInfoBackup;

extern WORD g_usDpMacTxEdidBw;

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern StructDpTxDownStreamDscInfo g_stDpMacTxDownStreamDscInfo;
extern StructDpMacTxInputDscInfo g_stDpMacTxInputDscInfo;
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern EnumDpMacTxLinkEstablishStatus g_enumDpMacTxLinkEstablishStatus;
extern EnumDpLinkChannelCodingType g_enumDpMacTxBackupRxCodingType;
extern BYTE g_ucDpMacTxMainPortChange;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpMacTxMainLinkPatternSetting_8b10b(EnumDPTxMainLinkPattern enumDPTxMainLinkPattern);
extern void ScalerDpMacTxInitial(void);
extern void ScalerDpMacTxSetHpdTimer(EnumDPTxHPDTimer enumDpTxHpdTimer, WORD usHpdTargetTimer);
extern void ScalerDpMacTxStateChangeEvent(EnumDPTxModeStatus enumModeState);

#if(_MST_DFP_SINK_EDID_REPORT_SOURCE_METHOD == _BYPASS_RAW_DATA)
extern bit ScalerDpMacTxReadDfpDeviceEdid(WORD usOffset, BYTE ucLength, BYTE *pucDataArray);
#else
extern bit ScalerDpMacTxGetDfpDeviceStoredEdid(WORD usOffset, BYTE ucLength, BYTE *pucDataArray);
#endif

#if(_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON)
extern void ScalerDpMacTxDscPassThroughReset(void);
#endif

extern bit ScalerDpMacTxHdcpGetEncryptStatus(void);
extern void ScalerDpMacTxForceIdlePatternSetting(void);
extern void ScalerDpMacTxForceIdlePattern_EXINT0(void);
extern void ScalerDpMacTxSetStreamSource(EnumDPTxInputSource enumStreamSource);
extern void ScalerDpMacTxSetStreamSource_EXINT0(EnumDPTxInputSource enumStreamSource);
extern void ScalerDpMacTxSdpReset(void);
extern void ScalerDpMacTxSdpReset_8b10b(void);
extern void ScalerDpMacTxSdpSetHeaderByte(EnumDPTxSecDataPacketType enumPackettype, EnumDPTxSdpDoubleBufferType enumDoubleBufferType);
extern void ScalerDpMacTxSdpSetHeaderByte_8b10b(BYTE *pucData, EnumDPTxSdpDoubleBufferType enumDoubleBufferType);
extern bit ScalerDpMacTxDigitalColorimetryChangeCheck(void);
extern void ScalerDpMacTxSetColorimetryChangeValue(void);
extern bit ScalerDpMacTxDigitalQuantizationChangeCheck(void);
extern void ScalerDpMacTxSetQuantizationChangeValue(void);
extern void ScalerDpMacTxColorimetryChangeFlagClear(void);
extern void ScalerDpMacTxQuantizationChangeFlagClear(void);
extern void ScalerDpMacTxMainLinkPatternSetting(EnumDPTxMainLinkPattern enumDPTxMainLinkPattern);
extern bit ScalerDpMacTxDfpLTTPRInitial(void);
extern void ScalerDpMacTxLTTPRExtWakeTimeOut(void);
extern EnumDpLinkChannelCodingType ScalerDpMacTxGetChannelCodingType(void);
extern void ScalerDpMacTxGetDfpDeviceDownUHBRStatus(BYTE *pucDpMaxLinkRate);
extern void ScalerDpMacTxSyncTableProcess(void);

#if(_DP_SUPPORT == _ON)
extern EnumDpStreamDataPath ScalerDpMacTxGetStreamDataPathType(void);
extern void ScalerDpMacTxCloneSetDataPath(EnumDpStreamDataPath enumDataPath);
extern EnumDpStreamDataPath ScalerDpMacTxCloneGetDataPath(void);
#endif

extern void ScalerDpMacTxSyncInputInfo(EnumDPTxInputSource enumStreamSource);
extern void ScalerDpMacTxDataMuxConfig(void);
extern void ScalerDpMacTxSetMst2SstLaneConfig(void);
extern void ScalerDpMacTxSetDpStreamSelect(void);
extern void ScalerDpMacTxStreamReorderSetting(void);
extern void ScalerDpMacTxDataMuxConfig_8b10b(void);
#if(_DP_ADAPTIVESYNC_SUPPORT == _ON)
extern void ScalerDpMacTxSdpHwBypassSettingforVesaPath(void);
#endif
extern void ScalerDpMacTxSyncTableProcess_8b10b(void);
extern void ScalerDpMacTxSSTSetting_8b10b(void);
extern void ScalerDpMacTxSdpHwBypassSetting(bit bEnable);
extern void ScalerDpMacTxSdpHwBypassSetting_8b10b(bit bEnable);
extern void ScalerDpMacTxSSTDisplayFormatSetting_8b10b(void);
extern void ScalerDpMacTxSSTMSASetting_8b10b(void);
extern EnumDpLinkRate ScalerDpMacTxGetMaxLinkRate(void);
extern EnumDpTxPixelMode ScalerDpMacTxGetInputPixelMode(EnumInputPort enumDpTxInputPort);
extern bit ScalerDpMacTxGetSendActFlag(void);
extern void ScalerDpMacTxClearSendActFlag(void);
extern void ScalerDpMacTxEnableSendAct(void);
extern void ScalerDpMacTxCtsFifoReset(void);
extern void ScalerDpMacTxMstEnableSetting(void);

#if(_DP_TX_FEC_SUPPORT == _ON)
extern bit ScalerDpMacTxFecInitialSetting(void);
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpMacTxPreCodingSet(bit bPreCodingEn);
#endif
extern bit ScalerDpMacTxFecSetting(bit bEn);
extern void ScalerDpMacTxFecDisableFailReLinkTraining(void);
#endif

extern bit ScalerDpMacTxMeasureGetMeasureResult(StructMeasureSyncData *pstMeasureSyncHV);
extern bit ScalerDpMacTxGetInputMeasureTimingInfo(EnumInputPort enumInputPort);

#if(_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON)
extern bit ScalerDpMacTxBlockStatusCheck(EnumInputPort enumInputPort);
#endif
extern EnumInputPort ScalerDpMacTxCloneGetCurrentInputPort(void);
extern bit ScalerDpMacTxNewComponentModeAvailable(void);
extern bit ScalerDpMacTxCloneCheckInputPortSupport(EnumInputPort enumInputPort);
extern bit ScalerDpMacTxClonePreCheck(EnumInputPort enumInputPort, EnumPortType enumPortType);
extern bit ScalerDpMacTxCloneGetInputInfo(EnumInputPort enumInputPort, EnumPortType enumPortType);
extern bit ScalerDpMacTxLinkStatusCheck(void);

#if((_DP_MST_SUPPORT == _ON) || (_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON))
extern bit ScalerDpMacTxSyncPayloadIDTable(BYTE ucPayloadID, WORD usPBN);
extern bit ScalerDpMacTxSyncDownStreamTableSetting(BYTE ucPayloadID, BYTE ucStartPosition, BYTE ucLength);
extern void ScalerDpMacTxDaisyClearPayloadIDProc(void);
extern BYTE ScalerDpMacTxDaisyModifyPayloadIDProc(BYTE ucPayloadID, BYTE ucTxTargeTimeSlotLength);
extern BYTE ScalerDpMacTxDaisyAddNewPayloadIDProc(BYTE ucPayloadID, BYTE ucTxTargeTimeSlotLength);
extern BYTE ScalerDpMacTxCalTimeslotNeed(WORD usPBN);
extern BYTE ScalerDpMacTxSetDaisyFirstStreamStart(void);
extern EnumDpStreamNum ScalerDpMacTxSearchMatchStream(BYTE ucTargetID);
extern bit ScalerDpMacTxCheckIDExisted(BYTE ucPayloadID);
extern bit ScalerDpMacTxCheckDaisyNoStream(void);
extern void ScalerDpMacTxResetDaisyStreamPositionReg(void);
extern bit ScalerDpMacTxGetDaisyStreamStatusReg(EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacTxSetDaisyStreamStatusReg(EnumDpStreamNum enumDpStreamNum, bit bEn);
extern void ScalerDpMacTxSetStreamToIdMapping(EnumDpStreamNum enumDpStreamNum, BYTE ucPayloadID);
extern void ScalerDpMacTxResetStreamToIdMapping(void);
extern void ScalerDpMacTxResetStreamToIdMapping_EXINT0(void);
extern EnumDpStreamNum ScalerDpMacTxGetDaisySourceMuxBackup(EnumDpStreamSourceNum enumDpStreamSourceNum);
extern void ScalerDpMacTxSetDaisySourceMuxBackup(EnumDpStreamSourceNum enumDpStreamSourceNum, EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacTxResetDaisySourceMuxBackup(void);
extern void ScalerDpMacTxSetDaisySourceMuxReg(EnumDpStreamSourceNum enumDpStreamSourceNum, EnumDpStreamNum enumDpStreamNum);
extern BYTE ScalerDpMacTxJudgeDaisySourceMuxCodingType(void);
extern void ScalerDpMacTxResetDaisySourceMuxReg(void);
extern void ScalerDpMacTxResetDaisySourceMux(void);
extern WORD ScalerDpMacTxGetDaisyStreamStartPositionRegAddress(EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacTxRestoreDaisySourceMuxBackupToReg(void);
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpMacTxMainLinkPatternSetting_128b132b(EnumDPTxMainLinkPattern enumDPTxMainLinkPattern);
extern WORD ScalerDpMacTxCalculateAllocatePBN_128b132b(void);
extern WORD ScalerDpMacTxMeasureAllocatePBN_128b132b(void);
extern void ScalerDpMacTxSyncTableProcess_128b132b(void);
extern void ScalerDpMacTxDataMuxConfig_128b132b(void);
extern void ScalerDpMacTxSSTSetting_128b132b(void);
extern void ScalerDpMacTxSSTMSASetting_128b132b(void);
extern void ScalerDpMacTxSSTDisplayFormatSetting_128b132b(void);
extern void ScalerDpMacTxSdpHwBypassSetting_128b132b(bit bEnable);
extern void ScalerDpMacTxSdpSetHeaderByte_128b132b(BYTE *pucData, EnumDPTxSdpDoubleBufferType enumDoubleBufferType);
extern void ScalerDpMacTxSdpSetDataByte_128b132b(EnumDPTxSdpTypeForDB enumSdpTypeSel, BYTE *pucInfoFrameData, BYTE ucLength, EnumDPTxSdpDoubleBufferType enumDoubleBufferType);
extern void ScalerDpMacTxSdpClearHeaderByte_128b132b(EnumDPTxSecDataPacketType enumPackettype);
extern void ScalerDpMacTxSdpReset_128b132b(void);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern bit ScalerDpMacTxDrrCloneOutputCheck(EnumInputPort enumInputPort);
#endif

extern void ScalerDpMacTxLttprExtWakeTimeOutGrant(void);
#endif // End of #if(_DP_MAC_TX_SUPPORT == _ON)

