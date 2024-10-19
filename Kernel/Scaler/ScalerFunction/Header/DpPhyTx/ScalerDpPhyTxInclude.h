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
// ID Code      : ScalerDpPhyTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_PHY_TX_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// LTTPR Link Training Setting
//--------------------------------------------------
#define _DP_TX_EQ_MAX_LOOP_CNT                              20
#define _DP_TX_EQ_MAX_TIME_OUT                              450
#define _DP_TX_AUX_RD_INTERVAL_THRESHOLD                    100
#define _DP_TX_AUX_RD_POLLING_THRESHOLD                     16
#define _DP_TX_LTTPR_SEGMENT_COMPLETE_NUM                   3

//--------------------------------------------------
// Macros of DP Tx Link Infomation
//--------------------------------------------------
#define GET_DP_TX_LT_STATE()                                (g_stDpPhyTxLTInfo.b4LinkTrainingState)
#define SET_DP_TX_LT_STATE(x)                               (g_stDpPhyTxLTInfo.b4LinkTrainingState = (x))

#define GET_DP_TX_LT_RESULT()                               (g_stDpPhyTxLTInfo.b5LinkTrainingResult)
#define SET_DP_TX_LT_RESULT(x)                              (g_stDpPhyTxLTInfo.b5LinkTrainingResult = (x))

#define GET_DP_TX_LT_MODE()                                 (g_stDpPhyTxLTInfo.b2LinkTrainingMode)
#define SET_DP_TX_LT_MODE(x)                                (g_stDpPhyTxLTInfo.b2LinkTrainingMode = (x))

#define GET_DP_TX_LT_DFP_REMAIN_NUM()                       (g_stDpPhyTxLTInfo.b4LTDfpNumRemain)
#define SET_DP_TX_LT_DFP_REMAIN_NUM(x)                      (g_stDpPhyTxLTInfo.b4LTDfpNumRemain = (x))

#define GET_DP_TX_LT_PROCESSING()                           (g_stDpPhyTxLTInfo.b1LinkTrainingProcessing)
#define SET_DP_TX_LT_PROCESSING(x)                          (g_stDpPhyTxLTInfo.b1LinkTrainingProcessing = (x))

#define GET_DP_TX_LT_SEGMENT_COMPLETE_NUM()                 (g_stDpPhyTxLTInfo.ucDpPhyTxLTSegmentCompleteNum)
#define ADD_DP_TX_LT_SEGMENT_COMPLETE_NUM()                 (g_stDpPhyTxLTInfo.ucDpPhyTxLTSegmentCompleteNum++)
#define CLR_DP_TX_LT_SEGMENT_COMPLETE_NUM()                 (g_stDpPhyTxLTInfo.ucDpPhyTxLTSegmentCompleteNum = 0)

#define GET_DP_TX_LT_AUX_RD_INTERVAL()                      (g_stDpPhyTxLTInfo.usAuxRdInterval)
#define SET_DP_TX_LT_AUX_RD_INTERVAL(x)                     (g_stDpPhyTxLTInfo.usAuxRdInterval = (x))

#define GET_DP_TX_LT_WAIT_AUX_RD_INTERVAL_DONE()            (g_stDpPhyTxLTInfo.b1LinkTrainingWaitRdIntervalDone)
#define SET_DP_TX_LT_WAIT_AUX_RD_INTERVAL_DONE()            (g_stDpPhyTxLTInfo.b1LinkTrainingWaitRdIntervalDone = _TRUE)
#define CLR_DP_TX_LT_WAIT_AUX_RD_INTERVAL_DONE()            (g_stDpPhyTxLTInfo.b1LinkTrainingWaitRdIntervalDone = _FALSE)

#define GET_DP_TX_LT_TIMEOUT()                              (g_stDpPhyTxLTInfo.b1LinkTrainingTimeout)
#define SET_DP_TX_LT_TIMEOUT()                              (g_stDpPhyTxLTInfo.b1LinkTrainingTimeout = _TRUE)
#define CLR_DP_TX_LT_TIMEOUT()                              (g_stDpPhyTxLTInfo.b1LinkTrainingTimeout = _FALSE)

#define GET_DP_TX_LT_LOOP_CNT()                             (g_stDpPhyTxLTInfo.b5LinkTrainingLoopCnt)
#define ADD_DP_TX_LT_LOOP_CNT()                             (g_stDpPhyTxLTInfo.b5LinkTrainingLoopCnt++)
#define CLR_DP_TX_LT_LOOP_CNT()                             (g_stDpPhyTxLTInfo.b5LinkTrainingLoopCnt = 0)

#define GET_DP_TX_LT_SHARE_DFP_FAIL()                       (g_stDpPhyTxLTInfo.b1LinkTrainingShareDfpFail)
#define SET_DP_TX_LT_SHARE_DFP_FAIL()                       (g_stDpPhyTxLTInfo.b1LinkTrainingShareDfpFail = _TRUE)
#define CLR_DP_TX_LT_SHARE_DFP_FAIL()                       (g_stDpPhyTxLTInfo.b1LinkTrainingShareDfpFail = _FALSE)

#define GET_DP_TX_LINK_PBN_PER_TIMESOLT()                   (g_stDpPhyTxLTInfo.ucLinkPBNPerTimeSlot)
#define SET_DP_TX_LINK_PBN_PER_TIMESOLT(x)                  (g_stDpPhyTxLTInfo.ucLinkPBNPerTimeSlot = (x))

#define GET_DP_TX_TP1_LANE0_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane0SameVolCnt)
#define ADD_DP_TX_TP1_LANE0_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane0SameVolCnt++)
#define CLR_DP_TX_TP1_LANE0_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane0SameVolCnt = 0)

#define GET_DP_TX_TP1_LANE1_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane1SameVolCnt)
#define ADD_DP_TX_TP1_LANE1_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane1SameVolCnt++)
#define CLR_DP_TX_TP1_LANE1_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane1SameVolCnt = 0)

#define GET_DP_TX_TP1_LANE2_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane2SameVolCnt)
#define ADD_DP_TX_TP1_LANE2_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane2SameVolCnt++)
#define CLR_DP_TX_TP1_LANE2_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane2SameVolCnt = 0)

#define GET_DP_TX_TP1_LANE3_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane3SameVolCnt)
#define ADD_DP_TX_TP1_LANE3_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane3SameVolCnt++)
#define CLR_DP_TX_TP1_LANE3_SAME_VOL_CNT()                  (g_stDpPhyTxLTInfo.b3TP1Lane3SameVolCnt = 0)

#define GET_DP_TX_TP2_CNT()                                 (g_stDpPhyTxLTInfo.b3TP2count)
#define ADD_DP_TX_TP2_CNT()                                 (g_stDpPhyTxLTInfo.b3TP2count++)
#define CLR_DP_TX_TP2_CNT()                                 (g_stDpPhyTxLTInfo.b3TP2count = 0)

#define GET_DP_TX_LANE0_CR_DONE()                           ((g_stDpPhyTxLTInfo.ucLane01LTStatus & _BIT0) == _BIT0)
#define GET_DP_TX_LANE1_CR_DONE()                           ((g_stDpPhyTxLTInfo.ucLane01LTStatus & _BIT4) == _BIT4)
#define GET_DP_TX_LANE2_CR_DONE()                           ((g_stDpPhyTxLTInfo.ucLane23LTStatus & _BIT0) == _BIT0)
#define GET_DP_TX_LANE3_CR_DONE()                           ((g_stDpPhyTxLTInfo.ucLane23LTStatus & _BIT4) == _BIT4)

#define GET_DP_TX_LANE0_EQ_DONE()                           ((g_stDpPhyTxLTInfo.ucLane01LTStatus & _BIT1) == _BIT1)
#define GET_DP_TX_LANE1_EQ_DONE()                           ((g_stDpPhyTxLTInfo.ucLane01LTStatus & _BIT5) == _BIT5)
#define GET_DP_TX_LANE2_EQ_DONE()                           ((g_stDpPhyTxLTInfo.ucLane23LTStatus & _BIT1) == _BIT1)
#define GET_DP_TX_LANE3_EQ_DONE()                           ((g_stDpPhyTxLTInfo.ucLane23LTStatus & _BIT5) == _BIT5)

#define GET_DP_TX_LANE0_SYMBOL_LOCKED()                     ((g_stDpPhyTxLTInfo.ucLane01LTStatus & _BIT2) == _BIT2)
#define GET_DP_TX_LANE1_SYMBOL_LOCKED()                     ((g_stDpPhyTxLTInfo.ucLane01LTStatus & _BIT6) == _BIT6)
#define GET_DP_TX_LANE2_SYMBOL_LOCKED()                     ((g_stDpPhyTxLTInfo.ucLane23LTStatus & _BIT2) == _BIT2)
#define GET_DP_TX_LANE3_SYMBOL_LOCKED()                     ((g_stDpPhyTxLTInfo.ucLane23LTStatus & _BIT6) == _BIT6)

#define GET_DP_TX_LANE_ALIGN_DONE()                         ((g_stDpPhyTxLTInfo.ucLaneAlignStatus & _BIT0) == _BIT0)

#define GET_DP_TX_DP_RX_LANE_ALIGN_DONE()                   ((g_stDpPhyTxLTInfo.ucLaneAlignStatus & _BIT2) == _BIT2)

#define GET_DP_TX_LANE_CDS_ALIGN_DONE()                     ((g_stDpPhyTxLTInfo.ucLaneAlignStatus & _BIT3) == _BIT3)

#define GET_DP_TX_LANE0_ADJUST_VOL_SWING()                  (g_stDpPhyTxLTInfo.ucAdjustReqLane01 & (_BIT1 | _BIT0))
#define SET_DP_TX_LANE0_ADJUST_VOL_SWING(x)                 (g_stDpPhyTxLTInfo.ucAdjustReqLane01 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane01 & ~(_BIT1 | _BIT0)) | (x)))

#define GET_DP_TX_LANE1_ADJUST_VOL_SWING()                  ((g_stDpPhyTxLTInfo.ucAdjustReqLane01 & (_BIT5 | _BIT4)) >> 4)
#define SET_DP_TX_LANE1_ADJUST_VOL_SWING(x)                 (g_stDpPhyTxLTInfo.ucAdjustReqLane01 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane01 & ~(_BIT5 | _BIT4)) | ((x) << 4)))

#define GET_DP_TX_LANE2_ADJUST_VOL_SWING()                  (g_stDpPhyTxLTInfo.ucAdjustReqLane23 & (_BIT1 | _BIT0))
#define SET_DP_TX_LANE2_ADJUST_VOL_SWING(x)                 (g_stDpPhyTxLTInfo.ucAdjustReqLane23 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane23 & ~(_BIT1 | _BIT0)) | (x)))

#define GET_DP_TX_LANE3_ADJUST_VOL_SWING()                  ((g_stDpPhyTxLTInfo.ucAdjustReqLane23 & (_BIT5 | _BIT4)) >> 4)
#define SET_DP_TX_LANE3_ADJUST_VOL_SWING(x)                 (g_stDpPhyTxLTInfo.ucAdjustReqLane23 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane23 & ~(_BIT5 | _BIT4)) | ((x) << 4)))

#define GET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS()               ((g_stDpPhyTxLTInfo.ucAdjustReqLane01 & (_BIT3 | _BIT2)) >> 2)
#define SET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS(x)              (g_stDpPhyTxLTInfo.ucAdjustReqLane01 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane01 & ~(_BIT3 | _BIT2)) | ((x) << 2)))

#define GET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS()               ((g_stDpPhyTxLTInfo.ucAdjustReqLane01 & (_BIT7 | _BIT6)) >> 6)
#define SET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS(x)              (g_stDpPhyTxLTInfo.ucAdjustReqLane01 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane01 & ~(_BIT7 | _BIT6)) | ((x) << 6)))

#define GET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS()               ((g_stDpPhyTxLTInfo.ucAdjustReqLane23 & (_BIT3 | _BIT2)) >> 2)
#define SET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS(x)              (g_stDpPhyTxLTInfo.ucAdjustReqLane23 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane23 & ~(_BIT3 | _BIT2)) | ((x) << 2)))

#define GET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS()               ((g_stDpPhyTxLTInfo.ucAdjustReqLane23 & (_BIT7 | _BIT6)) >> 6)
#define SET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS(x)              (g_stDpPhyTxLTInfo.ucAdjustReqLane23 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane23 & ~(_BIT7 | _BIT6)) | ((x) << 6)))

#define GET_DP_TX_LANE0_CURRENT_FFE_PRESET()                (g_stDpPhyTxLTInfo.ucLane0Adjust & 0x0F)
#define SET_DP_TX_LANE0_CURRENT_FFE_PRESET(x)               (g_stDpPhyTxLTInfo.ucLane0Adjust = ((g_stDpPhyTxLTInfo.ucLane0Adjust & 0xF0) | (x)))

#define GET_DP_TX_LANE1_CURRENT_FFE_PRESET()                (g_stDpPhyTxLTInfo.ucLane1Adjust & 0x0F)
#define SET_DP_TX_LANE1_CURRENT_FFE_PRESET(x)               (g_stDpPhyTxLTInfo.ucLane1Adjust = ((g_stDpPhyTxLTInfo.ucLane1Adjust & 0xF0) | (x)))

#define GET_DP_TX_LANE2_CURRENT_FFE_PRESET()                (g_stDpPhyTxLTInfo.ucLane2Adjust & 0x0F)
#define SET_DP_TX_LANE2_CURRENT_FFE_PRESET(x)               (g_stDpPhyTxLTInfo.ucLane2Adjust = ((g_stDpPhyTxLTInfo.ucLane2Adjust & 0xF0) | (x)))

#define GET_DP_TX_LANE3_CURRENT_FFE_PRESET()                (g_stDpPhyTxLTInfo.ucLane3Adjust & 0x0F)
#define SET_DP_TX_LANE3_CURRENT_FFE_PRESET(x)               (g_stDpPhyTxLTInfo.ucLane3Adjust = ((g_stDpPhyTxLTInfo.ucLane3Adjust & 0xF0) | (x)))

#define GET_DP_TX_LANE0_ADJUST_FFE_PRESET()                 (g_stDpPhyTxLTInfo.ucAdjustReqLane01 & (_BIT3 | _BIT2 | _BIT1 | _BIT0))
#define SET_DP_TX_LANE0_ADJUST_FFE_PRESET(x)                (g_stDpPhyTxLTInfo.ucAdjustReqLane01 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane01 & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | (x)))

#define GET_DP_TX_LANE1_ADJUST_FFE_PRESET()                 ((g_stDpPhyTxLTInfo.ucAdjustReqLane01 & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4)
#define SET_DP_TX_LANE1_ADJUST_FFE_PRESET(x)                (g_stDpPhyTxLTInfo.ucAdjustReqLane01 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane01 & ~(_BIT7 | _BIT6 | _BIT5 | _BIT4)) | ((x) << 4)))

#define GET_DP_TX_LANE2_ADJUST_FFE_PRESET()                 (g_stDpPhyTxLTInfo.ucAdjustReqLane23 & (_BIT3 | _BIT2 | _BIT1 | _BIT0))
#define SET_DP_TX_LANE2_ADJUST_FFE_PRESET(x)                (g_stDpPhyTxLTInfo.ucAdjustReqLane23 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane23 & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | (x)))

#define GET_DP_TX_LANE3_ADJUST_FFE_PRESET()                 ((g_stDpPhyTxLTInfo.ucAdjustReqLane23 & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4)
#define SET_DP_TX_LANE3_ADJUST_FFE_PRESET(x)                (g_stDpPhyTxLTInfo.ucAdjustReqLane23 = ((g_stDpPhyTxLTInfo.ucAdjustReqLane23 & ~(_BIT7 | _BIT6 | _BIT5 | _BIT4)) | ((x) << 4)))

//--------------------------------------------------
// Macros of DP Tx Link Training Infomation
//--------------------------------------------------
#define GET_DP_TX_LANE0_CURRENT_VOL_SWING()                 (g_stDpPhyTxLTInfo.ucLane0Adjust & 0x03)
#define SET_DP_TX_LANE0_CURRENT_VOL_SWING(x)                (g_stDpPhyTxLTInfo.ucLane0Adjust = ((g_stDpPhyTxLTInfo.ucLane0Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH()       (g_stDpPhyTxLTInfo.ucLane0Adjust |= _BIT2)
#define CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH()       (g_stDpPhyTxLTInfo.ucLane0Adjust &= ~_BIT2)

#define GET_DP_TX_LANE1_CURRENT_VOL_SWING()                 (g_stDpPhyTxLTInfo.ucLane1Adjust & 0x03)
#define SET_DP_TX_LANE1_CURRENT_VOL_SWING(x)                (g_stDpPhyTxLTInfo.ucLane1Adjust = ((g_stDpPhyTxLTInfo.ucLane1Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH()       (g_stDpPhyTxLTInfo.ucLane1Adjust |= _BIT2)
#define CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH()       (g_stDpPhyTxLTInfo.ucLane1Adjust &= ~_BIT2)

#define GET_DP_TX_LANE2_CURRENT_VOL_SWING()                 (g_stDpPhyTxLTInfo.ucLane2Adjust & 0x03)
#define SET_DP_TX_LANE2_CURRENT_VOL_SWING(x)                (g_stDpPhyTxLTInfo.ucLane2Adjust = ((g_stDpPhyTxLTInfo.ucLane2Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH()       (g_stDpPhyTxLTInfo.ucLane2Adjust |= _BIT2)
#define CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH()       (g_stDpPhyTxLTInfo.ucLane2Adjust &= ~_BIT2)

#define GET_DP_TX_LANE3_CURRENT_VOL_SWING()                 (g_stDpPhyTxLTInfo.ucLane3Adjust & 0x03)
#define SET_DP_TX_LANE3_CURRENT_VOL_SWING(x)                (g_stDpPhyTxLTInfo.ucLane3Adjust = ((g_stDpPhyTxLTInfo.ucLane3Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH()       (g_stDpPhyTxLTInfo.ucLane3Adjust |= _BIT2)
#define CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH()       (g_stDpPhyTxLTInfo.ucLane3Adjust &= ~_BIT2)

#define GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()              ((g_stDpPhyTxLTInfo.ucLane0Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(x)             (g_stDpPhyTxLTInfo.ucLane0Adjust = ((g_stDpPhyTxLTInfo.ucLane0Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()\
                                                            (g_stDpPhyTxLTInfo.ucLane0Adjust |= _BIT5)
#define CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()\
                                                            (g_stDpPhyTxLTInfo.ucLane0Adjust &= ~_BIT5)

#define GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()              ((g_stDpPhyTxLTInfo.ucLane1Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(x)             (g_stDpPhyTxLTInfo.ucLane1Adjust = ((g_stDpPhyTxLTInfo.ucLane1Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()\
                                                            (g_stDpPhyTxLTInfo.ucLane1Adjust |= _BIT5)
#define CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()\
                                                            (g_stDpPhyTxLTInfo.ucLane1Adjust &= ~_BIT5)

#define GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()              ((g_stDpPhyTxLTInfo.ucLane2Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(x)             (g_stDpPhyTxLTInfo.ucLane2Adjust = ((g_stDpPhyTxLTInfo.ucLane2Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()\
                                                            (g_stDpPhyTxLTInfo.ucLane2Adjust |= _BIT5)
#define CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()\
                                                            (g_stDpPhyTxLTInfo.ucLane2Adjust &= ~_BIT5)

#define GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()              ((g_stDpPhyTxLTInfo.ucLane3Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(x)             (g_stDpPhyTxLTInfo.ucLane3Adjust = ((g_stDpPhyTxLTInfo.ucLane3Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()\
                                                            (g_stDpPhyTxLTInfo.ucLane3Adjust |= _BIT5)
#define CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()\
                                                            (g_stDpPhyTxLTInfo.ucLane3Adjust &= ~_BIT5)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DP_TX_TRAINING_PATTERN1 = 0x00,
    _DP_TX_TRAINING_PATTERN2,
    _DP_TX_TRAINING_EQ_PHASE,
    _DP_TX_TRAINING_EQ_PHASE_POLLING,
    _DP_TX_TRAINING_CDS_PHASE,
    _DP_TX_TRAINING_CDS_PHASE_POLLING,
    _DP_TX_TRAINING_PATTERN_END,
} EnumDPTxLTStatus;

typedef struct
{
    BYTE ucLinkPBNPerTimeSlot;
    BYTE ucLane0Adjust;
    BYTE ucLane1Adjust;
    BYTE ucLane2Adjust;
    BYTE ucLane3Adjust;
    BYTE ucLane01LTStatus;
    BYTE ucLane23LTStatus;
    BYTE ucLaneAlignStatus;
    BYTE ucAdjustReqLane01;
    BYTE ucAdjustReqLane23;
    BYTE ucDpPhyTxLTSegmentCompleteNum;
    WORD usAuxRdInterval;

    BYTE b3TP1Lane0SameVolCnt : 3;
    BYTE b3TP1Lane1SameVolCnt : 3;
    BYTE b2LinkTrainingMode : 2;

    EnumDPTxLTStatus b4LinkTrainingState : 4;
    BYTE b4LTDfpNumRemain : 4;

    BYTE b1LinkTrainingProcessing : 1;
    BYTE b1LinkTrainingShareDfpFail : 1;
    BYTE b1LinkTrainingTimeout : 1;
    BYTE b5LinkTrainingLoopCnt : 5;

    WORD b3TP2count : 3;
    WORD b1LinkTrainingWaitRdIntervalDone : 1;
    WORD b5LinkTrainingResult : 5;
    WORD b3TP1Lane2SameVolCnt : 3;
    WORD b3TP1Lane3SameVolCnt : 3;
} StructDPTxLTInfo;

typedef enum
{
    _DP_TX_LANE_0 = 0x00,
    _DP_TX_LANE_1,
    _DP_TX_LANE_2,
    _DP_TX_LANE_3,
} EnumDpTxLane;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_PHY_TX_SUPPORT == _ON)
extern StructDPTxLTInfo g_stDpPhyTxLTInfo;

//--------------------------------------------------
// Macros of DP Tx CTS Test
//--------------------------------------------------
#define GET_DP_TX_CTS_TEST_REQUEST_TYPE(x)                  (g_ucDpPhyTxCtsRequestType & (x))
#define SET_DP_TX_CTS_TEST_REQUEST_TYPE(x)                  (g_ucDpPhyTxCtsRequestType = (x))
#define CLR_DP_TX_CTS_TEST_REQUEST_TARGET_TYPE(x)           (g_ucDpPhyTxCtsRequestType &= (EnumDPTxCtsTestRequestType)~(x))
#define CLR_DP_TX_CTS_TEST_REQUEST_TYPE()                   (g_ucDpPhyTxCtsRequestType = _DP_TX_CTS_NONE)
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Dp Aux Tx Read Type
//--------------------------------------------------
typedef enum
{
    _DP_TX_TRAINING_PATTERN_SET = 0x00,
    _DP_TX_TRAINING_LANEX_SET,
    _DP_TX_TRAINING_LANEX_STATUS,
    _DP_TX_TRAINING_AUX_RD_INTERVAL,
} EnumDpTxLTReadWriteType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucDpPhyTxCtsRequestType;
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpPhyTxLinkTraining(void);
extern void ScalerDpPhyTxBandWidthConfig(void);
extern bit ScalerDpPhyTxAutoTestConfig(void);
extern bit ScalerDpPhyTxAutoTest(void);
extern void ScalerDpPhyTxPowerProcess(EnumPowerTarget enumPowerTarget);
extern void ScalerDpPhyTxPowerOnInitial(void);
extern void ScalerDpPhyTxSetAltModeLaneMapping(EnumOutputPort enumOutputPort, EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation);
extern void ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(EnumOutputPort enumOutputPort, EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCOrientation enumTypeCOrientation);
extern BYTE ScalerDpPhyTxGetPcbTypeCLaneMapping(EnumTypeCOrientation enumTypecOrientation, BYTE ucDpTypecPcbLaneMapping);
extern BYTE ScalerDpPhyTxGetPcbTypeCLaneMapping_EXINT0(EnumTypeCOrientation enumTypecOrientation, BYTE ucDpTypecPcbLaneMapping);
extern void ScalerDpPhyTxMLPowerOff(void);
extern void ScalerDpPhyTxCMUPowerOff(void);
extern void ScalerDpPhyTxFLDSet(DWORD ulCMUFreq);
extern void ScalerDpPhyTxFLD(void);
extern void ScalerDpPhyTxLCCMUParaSet(DWORD ulCMUFreq);
extern void ScalerDpPhyTxLCCMUPara(void);
extern void ScalerDpPhyTxSSCSet(BYTE ucSSCEn);
extern void ScalerDpPhyTxPowerControl(EnumPowerAction enumPowerAction);
extern void ScalerDpPhyTxPowerCutControl(EnumPowerTarget enumPowerTarget);
#endif // End of #if(_DP_PHY_TX_SUPPORT == _ON)
