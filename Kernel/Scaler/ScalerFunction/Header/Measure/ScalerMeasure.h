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
// ID Code      : ScalerMeasure.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_MEASURE_H__
#define __SCALER_MEASURE_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of DP Measure Check Change Range
//--------------------------------------------------
#define _MEASURE_DP_H_PERIOD_MAX_CHANGE              5

#if(_HW_IDOMAIN_OFFLINE_HSTART_MEASURE_SUPPORT == _ON)
#if(_HW_IDOMAIN_OFFLINE_VSTART_MEASURE_SUPPORT == _ON)
#define _MEASURE_OFFLINE_START_REG                   P30_20_MEAS_START_CTRL
#define _MEASURE_OFFLINE_HSTART_RESULT_REG           P30_21_MEAS_HSTART_RESULT_L
#else
#define _MEASURE_OFFLINE_START_REG                   P30_20_MEAS_HSTART_CTRL
#define _MEASURE_OFFLINE_HSTART_RESULT_REG           P30_21_MEAS_HSTART_RESULT
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of AutoFunction Measure Main/Sub Enable Status
//--------------------------------------------------
typedef enum
{
    _MEASURE_MAIN_ONLY_ENABLE = 0x01,
    _MEASURE_SUB_ONLY_ENABLE = 0x02,
    _MEASURE_MAIN_SUB_ENABLE = 0x03,
} EnumMeasureMainSubStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#if(_HDMI_SUPPORT == _ON)
extern BYTE ScalerMeasureGetTmdsPage(EnumInputPort enumInputPort);
#endif

extern void ScalerMeasureInitialSetting(EnumSourceType enumSourceType, EnumInputPort enumInputPort);
extern bit ScalerMeasureCheckInterfaceNoSupport(EnumInputPort enumInputPort);
extern bit ScalerMeasureCheckIDomainNoSupport(EnumInputPort enumInputPort);
extern void ScalerMeasureInterfaceInitial(EnumSourceType enumSourceType, EnumInputPort *penumSourceSearchPort);
extern bit ScalerMeasureFinalSetting(EnumSourceType enumSourceType, EnumInputPort enumInputPort);

extern bit ScalerMeasureCheckInputInfoConsistency(EnumSourceType enumSourceType, EnumInputPort enumInputPort);
extern bit ScalerMeasureCheckWDTriggerStatus(BYTE ucRegionIndex);
extern bit ScalerMeasureCheckVsBypass(EnumSourceType enumSourceType, EnumInputPort enumInputPort);

extern void ScalerMeasureSetOfflineMeasure(EnumInputPort enumInputPort);
extern void ScalerMeasureSetOfflineMeasureSource(EnumInputPort enumInputPort);
extern bit ScalerMeasureGetOfflineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV, EnumInputPort enumInputPort);
extern bit ScalerMeasureOfflineMeasureDoubleCheck(EnumSourceType enumSourceType, EnumInputPort enumInputPort);
extern bit ScalerMeasureGetOfflineMeasureDiv2(void);

extern bit ScalerMeasureGetOnlineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV, EnumInputDataPath enumInputDataPath);
extern bit ScalerMeasureCheckOnlineMeasureChange(EnumSourceType enumSourceType, EnumInputPort enumInputPort, BYTE ucRegionIndex);

extern bit ScalerMeasureAutoFuncWaitFinish(EnumInputDataPath enumInputDataPath);
extern void ScalerMeasureSetAutoFuncHBoundary(WORD usHBoundStart, WORD usHBoundEnd, EnumInputDataPath enumInputDataPath);
extern void ScalerMeasureSetAutoFuncVBoundary(WORD usVBoundStart, WORD usVBoundEnd, EnumInputDataPath enumInputDataPath);

extern bit ScalerMeasureInterlaceCheck(EnumSourceType enumSourceType, EnumInputPort enumInputPort);
extern bit ScalerMeasureInterlaceDoubleCheck(EnumSourceType enumSourceType, EnumInputPort enumInputPort, EnumRegionIndex enumRegionIndex);
extern void ScalerMeasureInterlaceInitial(EnumSourceType enumSourceType, EnumInputPort enumInputPort);

extern void ScalerMeasureUpdateInputHorzontalTimingData(StructMeasureSyncData *pstMeasureSyncHV, StructAutoActiveData *pstActiveRegion);
extern void ScalerMeasureUpdateInputVerticalTimingData(StructMeasureSyncData *pstMeasureSyncHV, StructAutoActiveData *pstActiveRegion, EnumSourceType enumSourceType, EnumInputPort enumInputPort);
extern void ScalerMeasureUpdateInputTimingData(StructMeasureSyncData *pstMeasureSyncHV, StructAutoActiveData *pstActiveRegion, EnumSourceType enumSourceType, EnumInputPort enumInputPort);
extern void ScalerMeasureUpdateInputTimingPolarity(EnumSourceType enumSourceType, EnumInputPort enumInputPort, StructMeasureSyncData *pstMeasureSyncHV);

#if(_VGA_SUPPORT == _ON)
extern bit ScalerMeasureGetVgaStableMeasureResult(StructMeasureSyncData *pstMeasureSyncHV);
extern bit ScalerMeasureVgaInterlaceCheck(EnumInputPort enumInputPort);
#endif

#if(_HDMI_SUPPORT == _ON)
extern bit ScalerMeasureCheckInterlaceVst(WORD usVstart, WORD usVend);
extern void ScalerMeasureCheckFirstLineShift(EnumInputPort enumInputPort, WORD usFrameHwidth);
extern bit ScalerMeasureCheckTmdsDeOnlyTiming(StructMeasureSyncData *pstMeasureSyncHV, WORD usIVFreq);
#endif

#if(_DP_SUPPORT == _ON)
extern bit ScalerMeasureDpInterlaceCheck(EnumInputPort enumInputPort, BYTE ucIDomainPage);
#endif

#if(_HDMI_SUPPORT == _ON)
extern bit ScalerMeasureTmdsInterlaceCheck(EnumInputPort enumInputPort, BYTE ucIDomainPage);
#endif

#if(_MULTI_DISPLAY_MAX != 0x01)
extern void ScalerMeasureDuplicateInterlaceSetting(EnumInputDataPath enumDuplicatePath);
#endif

extern WORD ScalerMeasureTransDDomainToIDomainHorizonalPosition(WORD usIHWidth, WORD usDDomainHpos);
extern WORD ScalerMeasureTransDDomainToIDomainVerticalPosition(WORD usIVHeight, WORD usDDomainVpos);

#if(_DYNAMIC_COLOR_AUTO_MEASURE == _ON)
extern EnumMeasureMainSubStatus ScalerMeasureDynamicColorGetMainSubStatus(WORD usDHStart, WORD usDHEnd);
#endif

extern bit ScalerMeasureCheckAutoBoundaryResult(StructAutoActiveData *pstActiveRegion, EnumInputDataPath enumInputDataPath);
extern EnumActiveRegionType ScalerMeasureGetInputRegionType(void);
extern EnumInputDataPath ScalerMeasureGetInputRegionSourceSelect(void);


#endif // End of #ifndef __SCALER_MEASURE_H__
