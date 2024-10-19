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
// ID Code      : ScalerMeasureInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Measure Clock Frequency
//--------------------------------------------------
#define _MEASURE_CLK_DIV                             (ScalerGetBit(P40_07_MEASURE_CLK_DIVIDER, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define _MEASURE_USE_M2PLL_CLK                       ((bit)ScalerGetBit(P40_07_MEASURE_CLK_DIVIDER, _BIT4) ? _TRUE : _FALSE)
#define _MEASURE_CLK                                 (DWORD)((GET_M2PLL_POWER_STATUS() == _FALSE) ? _EXT_XTAL : (_MEASURE_USE_M2PLL_CLK ? (((DWORD)_M2PLL_CLK_KHZ) / _MEASURE_CLK_DIV) : _EXT_XTAL))

//--------------------------------------------------
// Definitions Of Measure Polling Time
// timeout clk = measure clk / 16384
// timeout = 512 / timeout clock + 10(tolerance) (ms)
// reset time = 1 / timeout clock, with min = 2 (ms)
//--------------------------------------------------
#define _MEASURE_TIMEOUT_CLK                         (_MEASURE_CLK / (16384 / 10)) // (0.1k)
#define _MEASURE_TIMEOUT                             ((WORD)(((DWORD)512 * 10 / _MEASURE_TIMEOUT_CLK) + 10)) // (ms)
#define _MEASURE_RESET_TIME                          ((_MEASURE_TIMEOUT_CLK >= 10) ? 2 : (2 * 10 / _MEASURE_TIMEOUT_CLK)) // (ms)

//--------------------------------------------------
// Definitions of Measure block limitation
//--------------------------------------------------
#define _MEASURE_H_FREQ_MIN                          (_MEASURE_CLK * 10 / (WORD)0x1FFF) // Unit: 0.1k

//--------------------------------------------------
// Macro of Sync Measurement Result
//--------------------------------------------------
#define GET_SYNC_H_POLARITY()                        (g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.b1HSP)
#define GET_SYNC_V_POLARITY()                        (g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.b1VSP)
#define GET_SYNC_H_PERIOD()                          (g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usHSPeriod)
#define GET_SYNC_H_SYNCWIDTH()                       (g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usHSWidth)
#define GET_SYNC_V_PERIOD()                          (g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usVSPeriod)
#define GET_SYNC_V_SYNCWIDTH()                       (g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usVSWidth)
#define GET_SYNC_H_TOTAL()                           (g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usHTotal)
#define GET_SYNC_H_WIDTH()                           (g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usHWidth)
#define GET_SYNC_V_HEIGHT()                          (g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usVHeight)

//--------------------------------------------------
// Macro of input timing infor. modification
//--------------------------------------------------
#define GET_MEASURE_INPUT_PATH()                     (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.enumInputDataPath)
#define SET_MEASURE_INPUT_PATH(x)                    (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.enumInputDataPath = (x))

//--------------------------------------------------
// Macro of input timing active region count
//--------------------------------------------------
#define GET_INPUT_TIMING_ACTIVE_REGION()             (g_pstMeasureRegionTimingInfoPointer->ulActiveRegionCount)
#define SET_INPUT_TIMING_ACTIVE_REGION(x)            (g_pstMeasureRegionTimingInfoPointer->ulActiveRegionCount = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _ACTIVE_REGION_TYPE = 0x00,
    _WHOLE_FRAME_TYPE = _BIT3,
    _BACK_PORCH_TYPE = _BIT4,
    _FRONT_PORCH_TYPE = (_BIT4 | _BIT3),
}EnumActiveRegionType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE ScalerMeasureGetIDomainPage(EnumInputDataPath enumInputDataPath);
extern BYTE ScalerMeasureGetOnlineMeasurePage(EnumInputDataPath enumInputDataPath);
extern void ScalerMeasureResetAllTimingInfo(void);
extern void ScalerMeasureResetTimingInfo(EnumInputDataPath enumInputDataPath);
extern bit ScalerMeasureSetSourceResultIndex(EnumFormatConversionSourceType enumFormatConversionSourceType);

extern void ScalerMeasureSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumInputDataPath enumInputDataPath);
extern bit ScalerMeasureGetAutoBoundaryResult(StructAutoActiveData *pstActiveRegion, EnumInputDataPath enumInputDataPath, bit bWait);
extern bit ScalerMeasureUpdateAutoPosition(EnumSourceType enumSourceType, EnumInputPort enumInputPort);

extern void ScalerMeasureSetInputRegionCount(EnumInputDataPath enumInputDataPath, EnumActiveRegionType enumRegionType);
extern DWORD ScalerMeasureGetInputRegionCountResult(bit bWait);
extern void ScalerMeasureSetDisplayRegionCount(EnumDDomainRegion enumDDomainRegion, EnumActiveRegionType enumRegionType);
extern DWORD ScalerMeasureGetDisplayRegionCountResult(bit bWait);
extern DWORD ScalerMeasureGetAdjustedActiveRegionCount(EnumInputDataPath enumInputDataPath, WORD usNewHWidth, WORD usNewVHeight);
extern DWORD ScalerMeasureGetHFreq(EnumInputDataPath enumInputDataPath);
extern DWORD ScalerMeasureGetdActiveRegionPixels(EnumInputDataPath enumInputDataPath, WORD usHWidth, WORD usVHeight, WORD usHTotal);


