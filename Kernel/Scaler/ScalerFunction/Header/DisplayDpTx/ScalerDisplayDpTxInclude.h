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
// ID Code      : ScalerDisplayDpTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DISPLAY_DP_TX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_DISPLAY_DPTX_MAX_LANE_NUM == _DISPLAY_DPTX_16_LANE)
#define SET_DISPLAY_DP_TX_PORT_OFFSET(x)                                                (g_ulDisplayDpTxPortOffset = (((x) == _DISPLAY_DP_TX_PORT_0) ? 0x000000 :\
                                                                                         (((x) == _DISPLAY_DP_TX_PORT_1) ? 0x100000 :\
                                                                                         (((x) == _DISPLAY_DP_TX_PORT_2) ? 0x200000 : 0x300000))))
#else
#define SET_DISPLAY_DP_TX_PORT_OFFSET(x)                                                (g_ulDisplayDpTxPortOffset = (((x) == _DISPLAY_DP_TX_PORT_1) ? 0x000000 : 0x100000))
#endif

#define GET_DISPLAY_DP_TX_PORT_OFFSET()                                                 (g_ulDisplayDpTxPortOffset)

#define GET_DISPLAY_DP_TX_PORT()                                                        ((g_ulDisplayDpTxPortOffset == 0x000000) ? _DISPLAY_DP_TX_PORT_0 :\
                                                                                         ((g_ulDisplayDpTxPortOffset == 0x100000) ? _DISPLAY_DP_TX_PORT_1 :\
                                                                                         ((g_ulDisplayDpTxPortOffset == 0x200000) ? _DISPLAY_DP_TX_PORT_2 : _DISPLAY_DP_TX_PORT_3)))

#define SET_DISPLAY_DP_TX_MAC_OFFSET(x)                                                 (g_ulDisplayDpTxMacOffset = (((x) == _DISPLAY_DP_TX_MAC0) ? 0x000000 :\
                                                                                         (((x) == _DISPLAY_DP_TX_MAC1) ? 0x100000 :\
                                                                                         (((x) == _DISPLAY_DP_TX_MAC2) ? 0x200000 : 0x300000))))
#define GET_DISPLAY_DP_TX_MAC_OFFSET()                                                  (g_ulDisplayDpTxMacOffset)

#define SCALER32_DISPLAY_DP_TX_GET_OFFSET_DWORD(ulOffset, pulAddr)                      (SCALER32_GET_OFFSET_DWORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000)))
#define SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD(ulOffset, pulAddr, ulValue)             {SCALER32_SET_OFFSET_DWORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulValue));}
#define SCALER32_DISPLAY_DP_TX_GET_OFFSET_WORD(ulOffset, pulAddr, ucWordIndex)          (SCALER32_GET_OFFSET_WORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucWordIndex)))
#define SCALER32_DISPLAY_DP_TX_SET_OFFSET_WORD(ulOffset, pulAddr, ucWordIndex, ulValue) {SCALER32_SET_OFFSET_WORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucWordIndex), (ulValue));}
#define SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE(ulOffset, pulAddr, ucIndex)              (SCALER32_GET_OFFSET_BYTE((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucIndex)))
#define SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE(ulOffset, pulAddr, ucIndex, ucValue)     {SCALER32_SET_OFFSET_BYTE((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucIndex), (ucValue));}
#define SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT(ulOffset, pulAddr, ulAnd)                 (SCALER32_GET_OFFSET_BIT((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulAnd)))
#define SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT(ulOffset, pulAddr, ulAnd, ulOr)           {SCALER32_SET_OFFSET_BIT((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulAnd), (ulOr));}

#define SCALER32_DISPLAY_DP_TX_GET_OFFSET_DWORD_EXINT0(ulOffset, pulAddr)               (SCALER32_GET_OFFSET_DWORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000)))
#define SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD_EXINT0(ulOffset, pulAddr, ulValue)      {SCALER32_SET_OFFSET_DWORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulValue));}
#define SCALER32_DISPLAY_DP_TX_GET_OFFSET_WORD_EXINT0(ulOffset, pulAddr, ucWordIndex)   (SCALER32_GET_OFFSET_WORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucWordIndex)))
#define SCALER32_DISPLAY_DP_TX_SET_OFFSET_WORD_EXINT0(ulOffset, pulAddr, ucWordIndex, ulValue)\
                                                                                        {SCALER32_SET_OFFSET_WORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucWordIndex), (ulValue));}
#define SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE_EXINT0(ulOffset, pulAddr, ucIndex)       (SCALER32_GET_OFFSET_BYTE_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucIndex)))
#define SCALER32_DISPLAY_DP_TX_SET_OFFSET_BYTE_EXINT0(ulOffset, pulAddr, ucIndex, ucValue)\
                                                                                        {SCALER32_SET_OFFSET_BYTE_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucIndex), (ucValue));}
#define SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT_EXINT0(ulOffset, pulAddr, ulAnd)          (SCALER32_GET_OFFSET_BIT_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulAnd)))
#define SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(ulOffset, pulAddr, ulAnd, ulOr)    {SCALER32_SET_OFFSET_BIT_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulAnd), (ulOr));}

#define _DISPLAY_DP_TX_SSC_FREQ                                                         ((GET_PANEL_DPTX_SPREAD_SPEED() == _SPEED_33K) ? 32 :\
                                                                                         ((GET_PANEL_DPTX_SPREAD_SPEED() == _SPEED_30K) ? 31 : 32))

#define _DISPLAY_DP_TX_AUX_DIFF_MODE                                                    0
#define _DISPLAY_DP_TX_AUX_SINGLE_MODE                                                  1

#define GET_DISPLAY_DP_TX_SSCG_CONFIG()                                                 (g_bDisplayDpTxSscEn)
#define SET_DISPLAY_DP_TX_SSCG_CONFIG(x)                                                (g_bDisplayDpTxSscEn = (x))

#define _DISPLAY_DP_TX_AUX_RETRY_LIMIT                                                  10

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DISPLAY_DP_TX_LANE_0 = 0x00,
    _DISPLAY_DP_TX_LANE_1,
    _DISPLAY_DP_TX_LANE_2,
    _DISPLAY_DP_TX_LANE_3,
} EnumDisplayDPTxLane;

typedef enum
{
    _DISPLAY_DP_TX_TPS_NONE = 0x00,
    _DISPLAY_DP_TX_TPS_1,
    _DISPLAY_DP_TX_TPS_2,
    _DISPLAY_DP_TX_TPS_3,
    _DISPLAY_DP_TX_TPS_4 = 0x07,
} EnumDisplayDPTxTrainPattern;

typedef enum
{
    _DISPLAY_DP_TX_OUTPUT_IDLE_PATTERN = 0x00,
    _DISPLAY_DP_TX_OUTPUT_TPS1 = _BIT4,
    _DISPLAY_DP_TX_OUTPUT_TPS2 = _BIT5,
    _DISPLAY_DP_TX_OUTPUT_TPS3 = (_BIT5 | _BIT4),
    _DISPLAY_DP_TX_OUTPUT_VIDEO_PATTERN = _BIT6,
    _DISPLAY_DP_TX_OUTPUT_PRBS7 = (_BIT6 | _BIT4),
    _DISPLAY_DP_TX_OUTPUT_80BIT_CUSTOM_PATTERN = (_BIT6 | _BIT5),
    _DISPLAY_DP_TX_OUTPUT_TPS4 = (_BIT6 | _BIT5 | _BIT4),
} EnumDisplayDPTxMainLinkPattern;

typedef enum
{
    _DISPLAY_DP_TX_SCRAMBLE_SEED_NONE = 0x00,
    _DISPLAY_DP_TX_SCRAMBLE_SEED_0XFFFE,
    _DISPLAY_DP_TX_SCRAMBLE_SEED_0XFFFF,
} EnumDisplayDPTxScrambleSeedType;

typedef enum
{
    _DISPLAY_DP_TX_LANE0_MAX_POST_CURSOR2_REACHED = _BIT2,
    _DISPLAY_DP_TX_LANE1_MAX_POST_CURSOR2_REACHED = _BIT6,
    _DISPLAY_DP_TX_LANE2_MAX_POST_CURSOR2_REACHED = _BIT2,
    _DISPLAY_DP_TX_LANE3_MAX_POST_CURSOR2_REACHED = _BIT6,
    _DISPLAY_DP_TX_SCRAMBLING_DISABLE = _BIT5,
} EnumDisplayDPTxLinkTrainAdditionalInfo;

//--------------------------------------------------
// Enumerations of DP Tx Mode State
//--------------------------------------------------
typedef enum
{
    _DISPLAY_DP_TX_TRAINING_PATTERN1 = 0x00,
    _DISPLAY_DP_TX_TRAINING_PATTERN2,
    _DISPLAY_DP_TX_TRAINING_PATTERN_END,
} EnumDisplayDPTxLTStatus;

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

    EnumDisplayDPTxLTStatus b4LinkTrainingState : 4;
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
} StructDisplayDPTxLTInfo;

typedef enum
{
    _DISPLAY_DP_TX_TRAINING_NO_RESULT = 0x00,
    _DISPLAY_DP_TX_TRAINING_PATTERN1_FAIL,
    _DISPLAY_DP_TX_TRAINING_PATTERN2_FAIL,
    _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL,
    _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL,
    _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS,
    _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS,
    _DISPLAY_DP_TX_TRAINING_PASS,
    _DISPLAY_DP_TX_TRAINING_FAIL,
} EnumDisplayDPTxLTResult;

//--------------------------------------------------
// Enumerations of Display DP Tx
//--------------------------------------------------
typedef enum
{
    _DISPLAY_DP_TX_LEVEL_0 = 0x00,
    _DISPLAY_DP_TX_LEVEL_1,
    _DISPLAY_DP_TX_LEVEL_2,
    _DISPLAY_DP_TX_LEVEL_3,
} EnumDisplayDPTxSignalLevel;

typedef enum
{
    _DISPLAY_DP_TX_MAC0 = 0x00,
    _DISPLAY_DP_TX_MAC1,
    _DISPLAY_DP_TX_MAC2,
    _DISPLAY_DP_TX_MAC3,
    _DISPLAY_DP_TX_MAC_MAX,
    _DISPLAY_DP_TX_NO_MAC = 0xFF,
} EnumDisplayDpMacSel;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bDisplayDpTxSscEn;
extern DWORD g_ulDisplayDpTxPortOffset;
extern DWORD g_ulDisplayDpTxMacOffset;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerDisplayDpTxGetPllPowerStatus(void);
extern EnumDisplayDpMacSel ScalerDisplayDpTxGetMacSwitch(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern EnumDisplayDpMacSel ScalerDisplayDpTxGetMacSwitch_EXINT0(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort);
extern void ScalerDisplayDpTxSetMacToPhyMux(void);
extern void ScalerDisplayDpTxSetDspcControl(void);

#if(_PANEL_EXIST_MULTIPANEL == _ON)
extern void ScalerDisplayDpTxPowerSwitch(void);
#endif

extern void ScalerDisplayDpTxSetPowerSequenceCheckPoint(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, bit bLevel);
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

