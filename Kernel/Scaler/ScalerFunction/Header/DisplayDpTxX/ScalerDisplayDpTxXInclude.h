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
// ID Code      : ScalerDisplayDpTxXInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DISPLAY_DP_TXX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Macros of DP Tx Downstream Infomation
//--------------------------------------------------
#define GET_DISPLAY_DP_TXX_LANE_NUM(x)                              (g_pstDisplayDpTxXInfo[x].b3LaneNum)
#define SET_DISPLAY_DP_TXX_LANE_NUM(x, y)                           (g_pstDisplayDpTxXInfo[x].b3LaneNum = (y))

#define GET_DISPLAY_DP_TXX_MAX_LINK_RATE(x)                         (g_pstDisplayDpTxXInfo[x].ucMaxLinkRate)
#define SET_DISPLAY_DP_TXX_MAX_LINK_RATE(x, y)                      (g_pstDisplayDpTxXInfo[x].ucMaxLinkRate = (y))

#define GET_DISPLAY_DP_TXX_ENHANCE_FRAMING(x)                       (g_pstDisplayDpTxXInfo[x].b1EnhanceFraming)
#define SET_DISPLAY_DP_TXX_ENHANCE_FRAMING(x, y)                    (g_pstDisplayDpTxXInfo[x].b1EnhanceFraming = (y))

#define GET_DISPLAY_DP_TXX_ALTERNATE_SR_CAPABLE(x)                  (g_pstDisplayDpTxXInfo[x].b1AlternateSrCapable)
#define SET_DISPLAY_DP_TXX_ALTERNATE_SR_CAPABLE(x, y)               (g_pstDisplayDpTxXInfo[x].b1AlternateSrCapable = (y))

#define GET_DISPLAY_DP_TXX_FRAMING_CHANGE_CAPABLE(x)                (g_pstDisplayDpTxXInfo[x].b1FramingChangeCapable)
#define SET_DISPLAY_DP_TXX_FRAMING_CHANGE_CAPABLE(x, y)             (g_pstDisplayDpTxXInfo[x].b1FramingChangeCapable = (y))

#define GET_DISPLAY_DP_TXX_DOWN_SPREAD(x)                           (g_pstDisplayDpTxXInfo[x].b1SSCSupport)
#define SET_DISPLAY_DP_TXX_DOWN_SPREAD(x, y)                        (g_pstDisplayDpTxXInfo[x].b1SSCSupport = (y))

#define GET_DISPLAY_DP_TXX_TP3_SUPPORT(x)                           (g_pstDisplayDpTxXInfo[x].b1TP3Support)
#define SET_DISPLAY_DP_TXX_TP3_SUPPORT(x)                           (g_pstDisplayDpTxXInfo[x].b1TP3Support = _TRUE)
#define CLR_DISPLAY_DP_TXX_TP3_SUPPORT(x)                           (g_pstDisplayDpTxXInfo[x].b1TP3Support = _FALSE)

#define GET_DISPLAY_DP_TXX_TP4_SUPPORT(x)                           (g_pstDisplayDpTxXInfo[x].b1TP4Support)
#define SET_DISPLAY_DP_TXX_TP4_SUPPORT(x)                           (g_pstDisplayDpTxXInfo[x].b1TP4Support = _TRUE)
#define CLR_DISPLAY_DP_TXX_TP4_SUPPORT(x)                           (g_pstDisplayDpTxXInfo[x].b1TP4Support = _FALSE)

#define GET_DISPLAY_DP_TXX_SCRAMBLE_TYPE(x)                         (g_pstDisplayDpTxXInfo[x].ucScrambleType)
#define SET_DISPLAY_DP_TXX_SCRAMBLE_TYPE(x, y)                      (g_pstDisplayDpTxXInfo[x].ucScrambleType = (y))

//--------------------------------------------------
// Macros of DP Tx Input Infomation
//--------------------------------------------------
#define GET_DISPLAY_DP_TXX_INPUT_COLOR_DEPTH(x)                     (g_pstDisplayDpTxXInputInfo[x].b3ColorDepth)
#define SET_DISPLAY_DP_TXX_INPUT_COLOR_DEPTH(x, y)                  (g_pstDisplayDpTxXInputInfo[x].b3ColorDepth = (y))

#define GET_DISPLAY_DP_TXX_INPUT_COLOR_SPACE(x)                     (g_pstDisplayDpTxXInputInfo[x].b3ColorSpace)
#define SET_DISPLAY_DP_TXX_INPUT_COLOR_SPACE(x, y)                  (g_pstDisplayDpTxXInputInfo[x].b3ColorSpace = (y))

#define GET_DISPLAY_DP_TXX_LINK_CONFIG(x)                           (g_pstDisplayDpTxXInputInfo[x].b1LinkConfig)
#define SET_DISPLAY_DP_TXX_LINK_CONFIG(x, y)                        (g_pstDisplayDpTxXInputInfo[x].b1LinkConfig = (y))

#if(_PANEL_DPTX_HPD_DETECT == _ON)
#define GET_DISPLAY_DP_TXX_STREAM_OUTPUT(x)                         (g_pstDisplayDpTxXInputInfo[x].b1StremOutput)
#define SET_DISPLAY_DP_TXX_STREAM_OUTPUT(x, y)                      (g_pstDisplayDpTxXInputInfo[x].b1StremOutput = (y))
#endif

//--------------------------------------------------
// Macros of DP Tx Link Infomation
//--------------------------------------------------
#define GET_DISPLAY_DP_TXX_LT_STATE(x)                              (g_pstDisplayDpTxXLTInfo[x].b4LinkTrainingState)
#define SET_DISPLAY_DP_TXX_LT_STATE(x, y)                           (g_pstDisplayDpTxXLTInfo[x].b4LinkTrainingState = (y))

#define GET_DISPLAY_DP_TXX_LT_RESULT(x)                             (g_pstDisplayDpTxXLTInfo[x].b5LinkTrainingResult)
#define SET_DISPLAY_DP_TXX_LT_RESULT(x, y)                          (g_pstDisplayDpTxXLTInfo[x].b5LinkTrainingResult = (y))

#define GET_DISPLAY_DP_TXX_TP1_LANE0_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane0SameVolCnt)
#define ADD_DISPLAY_DP_TXX_TP1_LANE0_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane0SameVolCnt++)
#define CLR_DISPLAY_DP_TXX_TP1_LANE0_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane0SameVolCnt = 0)

#define GET_DISPLAY_DP_TXX_TP1_LANE1_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane1SameVolCnt)
#define ADD_DISPLAY_DP_TXX_TP1_LANE1_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane1SameVolCnt++)
#define CLR_DISPLAY_DP_TXX_TP1_LANE1_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane1SameVolCnt = 0)

#define GET_DISPLAY_DP_TXX_TP1_LANE2_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane2SameVolCnt)
#define ADD_DISPLAY_DP_TXX_TP1_LANE2_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane2SameVolCnt++)
#define CLR_DISPLAY_DP_TXX_TP1_LANE2_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane2SameVolCnt = 0)

#define GET_DISPLAY_DP_TXX_TP1_LANE3_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane3SameVolCnt)
#define ADD_DISPLAY_DP_TXX_TP1_LANE3_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane3SameVolCnt++)
#define CLR_DISPLAY_DP_TXX_TP1_LANE3_SAME_VOL_CNT(x)                (g_pstDisplayDpTxXLTInfo[x].b3TP1Lane3SameVolCnt = 0)

#define GET_DISPLAY_DP_TXX_TP2_CNT(x)                               (g_pstDisplayDpTxXLTInfo[x].b3TP2count)
#define ADD_DISPLAY_DP_TXX_TP2_CNT(x)                               (g_pstDisplayDpTxXLTInfo[x].b3TP2count++)
#define CLR_DISPLAY_DP_TXX_TP2_CNT(x)                               (g_pstDisplayDpTxXLTInfo[x].b3TP2count = 0)

#define GET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(x)               (g_pstDisplayDpTxXLTInfo[x].ucLane0Adjust & 0x03)
#define SET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING(x, y)            (g_pstDisplayDpTxXLTInfo[x].ucLane0Adjust = ((g_pstDisplayDpTxXLTInfo[x].ucLane0Adjust & 0xFC) | (y)))

#define GET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING_MAX_REACH(x)     (bit)((g_pstDisplayDpTxXLTInfo[x].ucLane0Adjust & _BIT2) >> 2)
#define SET_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING_MAX_REACH(x)     (g_pstDisplayDpTxXLTInfo[x].ucLane0Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TXX_LANE0_CURRENT_VOL_SWING_MAX_REACH(x)     (g_pstDisplayDpTxXLTInfo[x].ucLane0Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(x)               (g_pstDisplayDpTxXLTInfo[x].ucLane1Adjust & 0x03)
#define SET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING(x, y)            (g_pstDisplayDpTxXLTInfo[x].ucLane1Adjust = ((g_pstDisplayDpTxXLTInfo[x].ucLane1Adjust & 0xFC) | (y)))

#define GET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING_MAX_REACH(x)     (bit)((g_pstDisplayDpTxXLTInfo[x].ucLane1Adjust & _BIT2) >> 2)
#define SET_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING_MAX_REACH(x)     (g_pstDisplayDpTxXLTInfo[x].ucLane1Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TXX_LANE1_CURRENT_VOL_SWING_MAX_REACH(x)     (g_pstDisplayDpTxXLTInfo[x].ucLane1Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING(x)               (g_pstDisplayDpTxXLTInfo[x].ucLane2Adjust & 0x03)
#define SET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING(x, y)            (g_pstDisplayDpTxXLTInfo[x].ucLane2Adjust = ((g_pstDisplayDpTxXLTInfo[x].ucLane2Adjust & 0xFC) | (y)))

#define GET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING_MAX_REACH(x)     (bit)((g_pstDisplayDpTxXLTInfo[x].ucLane2Adjust & _BIT2) >> 2)
#define SET_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING_MAX_REACH(x)     (g_pstDisplayDpTxXLTInfo[x].ucLane2Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TXX_LANE2_CURRENT_VOL_SWING_MAX_REACH(x)     (g_pstDisplayDpTxXLTInfo[x].ucLane2Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING(x)               (g_pstDisplayDpTxXLTInfo[x].ucLane3Adjust & 0x03)
#define SET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING(x, y)            (g_pstDisplayDpTxXLTInfo[x].ucLane3Adjust = ((g_pstDisplayDpTxXLTInfo[x].ucLane3Adjust & 0xFC) | (y)))

#define GET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING_MAX_REACH(x)     (bit)((g_pstDisplayDpTxXLTInfo[x].ucLane3Adjust & _BIT2) >> 2)
#define SET_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING_MAX_REACH(x)     (g_pstDisplayDpTxXLTInfo[x].ucLane3Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TXX_LANE3_CURRENT_VOL_SWING_MAX_REACH(x)     (g_pstDisplayDpTxXLTInfo[x].ucLane3Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(x)            ((g_pstDisplayDpTxXLTInfo[x].ucLane0Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS(x, y)         (g_pstDisplayDpTxXLTInfo[x].ucLane0Adjust = ((g_pstDisplayDpTxXLTInfo[x].ucLane0Adjust & ~(_BIT4 | _BIT3)) | ((y) << 3)))
#define SET_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH(x)  (g_pstDisplayDpTxXLTInfo[x].ucLane0Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TXX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH(x)  (g_pstDisplayDpTxXLTInfo[x].ucLane0Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(x)            ((g_pstDisplayDpTxXLTInfo[x].ucLane1Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS(x, y)         (g_pstDisplayDpTxXLTInfo[x].ucLane1Adjust = ((g_pstDisplayDpTxXLTInfo[x].ucLane1Adjust & ~(_BIT4 | _BIT3)) | ((y) << 3)))
#define SET_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH(x)  (g_pstDisplayDpTxXLTInfo[x].ucLane1Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TXX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH(x)  (g_pstDisplayDpTxXLTInfo[x].ucLane1Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS(x)            ((g_pstDisplayDpTxXLTInfo[x].ucLane2Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS(x, y)         (g_pstDisplayDpTxXLTInfo[x].ucLane2Adjust = ((g_pstDisplayDpTxXLTInfo[x].ucLane2Adjust & ~(_BIT4 | _BIT3)) | ((y) << 3)))
#define SET_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH(x)  (g_pstDisplayDpTxXLTInfo[x].ucLane2Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TXX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH(x)  (g_pstDisplayDpTxXLTInfo[x].ucLane2Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS(x)            ((g_pstDisplayDpTxXLTInfo[x].ucLane3Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS(x, y)         (g_pstDisplayDpTxXLTInfo[x].ucLane3Adjust = ((g_pstDisplayDpTxXLTInfo[x].ucLane3Adjust & ~(_BIT4 | _BIT3)) | ((y) << 3)))
#define SET_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH(x)  (g_pstDisplayDpTxXLTInfo[x].ucLane3Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TXX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH(x)  (g_pstDisplayDpTxXLTInfo[x].ucLane3Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TXX_LANE0_CR_DONE(x)                         ((g_pstDisplayDpTxXLTInfo[x].ucLane01LTStatus & _BIT0) == _BIT0)
#define GET_DISPLAY_DP_TXX_LANE1_CR_DONE(x)                         ((g_pstDisplayDpTxXLTInfo[x].ucLane01LTStatus & _BIT4) == _BIT4)
#define GET_DISPLAY_DP_TXX_LANE2_CR_DONE(x)                         ((g_pstDisplayDpTxXLTInfo[x].ucLane23LTStatus & _BIT0) == _BIT0)
#define GET_DISPLAY_DP_TXX_LANE3_CR_DONE(x)                         ((g_pstDisplayDpTxXLTInfo[x].ucLane23LTStatus & _BIT4) == _BIT4)

#define GET_DISPLAY_DP_TXX_LANE0_EQ_DONE(x)                         ((g_pstDisplayDpTxXLTInfo[x].ucLane01LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_DISPLAY_DP_TXX_LANE1_EQ_DONE(x)                         ((g_pstDisplayDpTxXLTInfo[x].ucLane01LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))
#define GET_DISPLAY_DP_TXX_LANE2_EQ_DONE(x)                         ((g_pstDisplayDpTxXLTInfo[x].ucLane23LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_DISPLAY_DP_TXX_LANE3_EQ_DONE(x)                         ((g_pstDisplayDpTxXLTInfo[x].ucLane23LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))

#define GET_DISPLAY_DP_TXX_LANE_ALIGN_DONE(x)                       ((g_pstDisplayDpTxXLTInfo[x].ucLaneAlignStatus & _BIT0) == _BIT0)


#define GET_DISPLAY_DP_TXX_LANE0_ADJUST_VOL_SWING(x)                (g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane01 & (_BIT1 | _BIT0))
#define SET_DISPLAY_DP_TXX_LANE0_ADJUST_VOL_SWING(x, y)             (g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane01 = ((g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane01 & ~(_BIT1 | _BIT0)) | (y)))

#define GET_DISPLAY_DP_TXX_LANE1_ADJUST_VOL_SWING(x)                ((g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane01 & (_BIT5 | _BIT4)) >> 4)
#define SET_DISPLAY_DP_TXX_LANE1_ADJUST_VOL_SWING(x, y)             (g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane01 = ((g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane01 & ~(_BIT5 | _BIT4)) | ((y) << 4)))

#define GET_DISPLAY_DP_TXX_LANE2_ADJUST_VOL_SWING(x)                (g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane23 & (_BIT1 | _BIT0))
#define SET_DISPLAY_DP_TXX_LANE2_ADJUST_VOL_SWING(x, y)             (g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane23 = ((g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane23 & ~(_BIT1 | _BIT0)) | (y)))

#define GET_DISPLAY_DP_TXX_LANE3_ADJUST_VOL_SWING(x)                ((g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane23 & (_BIT5 | _BIT4)) >> 4)
#define SET_DISPLAY_DP_TXX_LANE3_ADJUST_VOL_SWING(x, y)             (g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane23 = ((g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane23 & ~(_BIT5 | _BIT4)) | ((y) << 4)))

#define GET_DISPLAY_DP_TXX_LANE0_ADJUST_PRE_EMPHASIS(x)             ((g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane01 & (_BIT3 | _BIT2)) >> 2)
#define GET_DISPLAY_DP_TXX_LANE1_ADJUST_PRE_EMPHASIS(x)             ((g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane01 & (_BIT7 | _BIT6)) >> 6)
#define GET_DISPLAY_DP_TXX_LANE2_ADJUST_PRE_EMPHASIS(x)             ((g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane23 & (_BIT3 | _BIT2)) >> 2)
#define GET_DISPLAY_DP_TXX_LANE3_ADJUST_PRE_EMPHASIS(x)             ((g_pstDisplayDpTxXLTInfo[x].ucAdjustReqLane23 & (_BIT7 | _BIT6)) >> 6)

#define GET_DISPLAY_DP_TXX_HPD_DEBOUNCE_LEVEL()                     ((SCALER32_GET_OFFSET_BIT(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C0_HPD_CTRL, _BIT2) == _BIT2) ? _HIGH : _LOW)

//--------------------------------------------------
// Macro of DP Tx Current AUX Receive Mode
//--------------------------------------------------
#define GET_DISPLAY_DP_TXX_AUX_RECEIVE_MODE(x)                      (g_penumDisplayDpTxXAuxReceiveMode[x])
#define SET_DISPLAY_DP_TXX_AUX_RECEIVE_MODE(x, y)                   (g_penumDisplayDpTxXAuxReceiveMode[x] = (y))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

extern StructDownStreamInfo g_pstDisplayDpTxXInfo[_DISPLAY_DP_TX_PORT_MAX];
extern StructDisplayDPTxLTInfo g_pstDisplayDpTxXLTInfo[_DISPLAY_DP_TX_PORT_MAX];

extern EnumDpAuxReceiveMode g_penumDisplayDpTxXAuxReceiveMode[_DISPLAY_DP_TX_PORT_MAX];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDisplayDpTxXInitial(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXLinkConfig(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXVideoStreamOutput(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, bit bOutput);
extern bit ScalerDisplayDpTxXLinkTraining(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern bit ScalerDisplayDpTxXNativeAuxWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
extern bit ScalerDisplayDpTxXNativeAuxRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
extern bit ScalerDisplayDpTxXAuxI2CoverWrite(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT);
extern bit ScalerDisplayDpTxXAuxI2CoverRead(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT);

#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
extern void ScalerDisplayDpTxXLinkForceOutput(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxXForceOutputPreCheck(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
#endif

extern void ScalerDisplayDpTxXTraininPatternEndSequence(void);
extern void ScalerDisplayDpTxXVendorSpecific004F1hAuxWrite(void);

#if(_PANEL_DPTX_HPD_DETECT == _ON)
extern bit ScalerDisplayDpTxXStableDetectCheck(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
#if(_PANEL_DPTX_IRQ_HPD_DETECT == _ON)
extern void ScalerDisplayDpTxXIrqHpdHandler_EXINT0(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
#endif
#endif

#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

