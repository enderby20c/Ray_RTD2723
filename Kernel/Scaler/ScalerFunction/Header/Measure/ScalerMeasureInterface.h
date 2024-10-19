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
// ID Code      : ScalerMeasureInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of Picture Active Measurement Result
//--------------------------------------------------
#define GET_ACTIVE_V_START()                         (g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveStart)
#define GET_ACTIVE_V_END()                           (g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd)
#define GET_ACTIVE_H_START()                         (g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usHActiveStart)
#define GET_ACTIVE_H_END()                           (g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usHActiveEnd)
#define GET_ACTIVE_H_WIDTH()                         ((g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usHActiveEnd - g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usHActiveStart) + 1)
#define GET_ACTIVE_V_HEIGHT()                        ((g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd - g_pstMeasureRegionTimingInfoPointer->stAutoActiveData.usVActiveStart) + 1)

#if(_HW_IDOMAIN_OFFLINE_HSTART_MEASURE_SUPPORT == _ON)
#define GET_OFFLINE_H_START()                        (g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usHStart)
#define GET_OFFLINE_H_WIDTH()                        (g_pstMeasureRegionTimingInfoPointer->stMeasureSyncData.usHWidth)
#endif

//--------------------------------------------------
// Macros of input timing info. modification
//--------------------------------------------------
#define SET_INPUT_TIMING_HSTART(x)                   (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHStart = (x))
#define SET_INPUT_TIMING_HWIDTH(x)                   (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHWidth = (x))
#define SET_INPUT_TIMING_HTOTAL(x)                   (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHTotal = (x))
#define SET_INPUT_TIMING_HSYNCWIDTH(x)               (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHSWidth = (x))

#define SET_INPUT_TIMING_VSTART(x)                   (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVStart = (x))
#define SET_INPUT_TIMING_VHEIGHT(x)                  (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVHeight = (x))
#define SET_INPUT_TIMING_VTOTAL(x)                   (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVTotal = (x))
#define SET_INPUT_TIMING_VSYNCWIDTH(x)               (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVSWidth = (x))

//--------------------------------------------------
// Macros of Input Timing Info.
//--------------------------------------------------
#define GET_INPUT_TIMING_H_POLARITY()                (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1HSP)
#define GET_INPUT_TIMING_V_POLARITY()                (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1VSP)
#define GET_INPUT_TIMING_INTERLACE_FLG()             (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1Interlace)
#define GET_INPUT_TIMING_DATA_PATH()                 (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.enumInputDataPath)
#define GET_INPUT_TIMING_HFREQ()                     (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHFreq)
#define GET_INPUT_TIMING_HFREQ_ADJUSTED()            (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHFreqAdjusted)
#define GET_INPUT_TIMING_HTOTAL()                    (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHTotal)
#define GET_INPUT_TIMING_HWIDTH()                    (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHWidth)
#define GET_INPUT_TIMING_HSTART()                    (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHStart)
#define GET_INPUT_TIMING_HSYNCWIDTH()                (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usHSWidth)
#define GET_INPUT_TIMING_VFREQ()                     (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVFreq)
#define GET_INPUT_TIMING_VFREQ_ADJUSTED()            (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVFreqAdjusted)
#define GET_INPUT_TIMING_VTOTAL()                    (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVTotal)
#define GET_INPUT_TIMING_VHEIGHT()                   (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVHeight)
#define GET_INPUT_TIMING_VSTART()                    (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVStart)
#define GET_INPUT_TIMING_VSYNCWIDTH()                (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.usVSWidth)

#define GET_INPUT_TIMING_EXTRA_INTERLACE_FLG()       ((GET_INPUT_TIMING_INTERLACE_FLG()) ||\
                                                      (g_pstMeasureRegionTimingInfoPointer->stTimingInfo.b1DpInterlaceVBID))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of AutoFunction Measure Field Select
//--------------------------------------------------
typedef enum
{
    _EVEN_FIELD_MEASURE = 0x00,
    _ODD_FIELD_MEASURE = 0x01,
    _NORMAL_MEASURE = 0x02,
} EnumMeasureFieldSelect;

//--------------------------------------------------
// Enumerations of AutoFunction Measure Boundary Type
//--------------------------------------------------
typedef enum
{
    _FULL_BOUNDARY = 0x00,
    _OVERSCAN_BOUNDARY = 0x01,
} EnumMeasureBoundType;

//--------------------------------------------------
// Enumerations of AutoFunction Measure Field Select
//--------------------------------------------------
typedef enum
{
    _MEASURE_RESULT_PASS,
    _MEASURE_RESULT_FAIL,
    _MEASURE_RESULT_OOR,
} EnumMeasureResult;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructRegionTimingInfo g_pstMeasureRegionTimingInfo[_MULTI_DISPLAY_MAX];
extern StructRegionTimingInfo *g_pstMeasureRegionTimingInfoPointer;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMeasureSetRegionIndex(EnumRegionIndex enumRegionIndex);
extern EnumDisplayRegion ScalerMeasureGetResultPointerRegion(void);
extern void ScalerMeasureSetInputPath(EnumInputDataPath enumInputDataPath);
extern EnumMeasureResult ScalerMeasureInputInfo(EnumSourceType enumSourceType, EnumInputPort enumInputPort);
extern bit ScalerMeasureDoubleCheck(EnumSourceType enumSourceType, EnumInputPort enumInputPort, EnumRegionIndex enumRegionIndex);
extern bit ScalerMeasureCheckTimingChange(EnumSourceType enumSourceType, EnumInputPort enumInputPort, BYTE ucRegionIndex);

extern void ScalerMeasureSetOnlineMeasure(EnumSourceType enumSourceType, EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath, WORD usIVFreq);
extern void ScalerMeasureUpdateActiveRegion(void);
extern bit ScalerMeasureIgnoreHFreqCheck(EnumInputPort enumInputPort);

#if(_VGA_SUPPORT == _ON)
extern bit ScalerMeasureVgaInputInfo(void);
#endif

#if(_MULTI_DISPLAY_MAX != 0x01)
extern EnumMeasureResult ScalerMeasureDuplicateInputInfo(BYTE ucDuplicateIndex, EnumSourceType enumSourceType, EnumInputPort enumInputPort);
#endif

#if(_GLOBAL_DIMMING_PATTERN_ESTIMATE == _ON)
extern void ScalerMeasureGlobalDimmingPatternEstimateInitial(void);
extern void ScalerMeasureGlobalDimmingPatternEstimateStart(void);
extern BYTE ScalerMeasureGlobalDimmingPatternEstimateGetResult(BYTE ucColor);
#endif

#if(_DYNAMIC_COLOR_AUTO_MEASURE == _ON)
extern void ScalerMeasureDynamicColorInitial(StructTimingInfo *pstTimingInfo, WORD usDHStart, WORD usDHEnd, WORD usDVStart, WORD usDVEnd);
extern void ScalerMeasureDynamicColorSetAutoMeasure(WORD usDHStart, WORD usDHEnd, EnumAutoChannelType enumAutoChannelType);
extern bit ScalerMeasureDynamicColorGetResult(BYTE *pucColorAverageValue, WORD usDHStart, WORD usDHEnd, bit bWait);
#endif

#if(_DYNAMIC_DATA_BOUNDARY_AUTO_MEASURE == _ON)
extern bit ScalerMeasureImageBoundary(BYTE ucNoiseMargin, StructAutoActiveData *pstActiveRegion, EnumDisplayRegion enumDisplayRegion, EnumColorSpace enumColorSpace, bit bWait);
extern void ScalerMeasureUpdateHVtiming(StructAutoActiveData *pstActiveRegion, StructImageRegion *pstImageRegion, EnumDisplayRegion enumDisplayRegion);
extern bit ScalerMeasureGetHwAutoPhaseEnable(EnumInputDataPath enumInputDataPath);
#endif

