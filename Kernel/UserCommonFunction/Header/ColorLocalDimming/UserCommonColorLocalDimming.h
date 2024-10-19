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
// ID Code      : UserCommonColorLocalDimming.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_COLOR_LOCAL_DIMMING_H__
#define __USER_COMMON_COLOR_LOCAL_DIMMING_H__

#if(_LOCAL_DIMMING_FUNCTION == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))
#define _LOCAL_DIMMING_EDGE_MAX_REGION                 32
#define _LOCAL_DIMMING_NEW_BOOST_MODE                  0xAA
#define _LOCAL_DIMMING_ADIMMING_TIMEOUT                20  // ms
#endif

#define SET_LOCAL_DIMMING_PWM_TOTAL_RATIO(x)           (g_stColorLocalDimmingExternInfo.ucColorPWMTotalRatio = (x))
#define SET_LOCAL_DIMMING_BLACK_RATIO(x)               (g_stColorLocalDimmingExternInfo.ucColorBlackRatio = (x))
#define SET_LOCAL_DIMMING_FULL_PATTERN(x)              (g_stColorLocalDimmingExternInfo.bColorFullPattern = (x))

#define GET_LOCAL_DIMMING_PICTURE_TYPE()               (g_stColorLocalDimmingPictureType.enumLDPWMPictureType)
#define SET_LOCAL_DIMMING_PICTURE_TYPE(x)              (g_stColorLocalDimmingPictureType.enumLDPWMPictureType = (x))

#define GET_LOCAL_DIMMING_SC_TYPE()                    (g_stColorLocalDimmingPWMType.enumStepChangeType)
#define SET_LOCAL_DIMMING_SC_TYPE(x)                   (g_stColorLocalDimmingPWMType.enumStepChangeType = (x))


#define SET_LOCAL_DIMMING_BACKLIGHT_MODEL_FIRST_ON(x)  (g_bColorLocalDimmingBackLightModelFirstON = (x))
#define GET_LOCAL_DIMMING_BACKLIGHT_MODEL_FIRST_ON()   (g_bColorLocalDimmingBackLightModelFirstON)

#define SET_LOCAL_DIMMING_CASE(x)                      (g_stColorLocalDimmingExternInfo.enumLocalDimmingCase = (x))


#define _LOCAL_DIMMING_LOW_ENTROPY                     200
#if(_HW_LOCAL_DIMMING_MAX_REGION == _HW_LOCAL_DIMMING_GEN1)
#define _LOCAL_DIMMING_ENTROPY_THD                     300
#else
#define _LOCAL_DIMMING_ENTROPY_THD                     440
#endif
#define _LOCAL_DIMMING_ALMOST_GRAY_ENTROPY             80  // 80% same bin with 90% percentile min
#define _LOCAL_DIMMING_G2G_DELTA_ENTROPY_THD           10  // with 95% same bin, (max entropy - min entropy)
#define _LOCAL_DIMMING_G2G_GAIN_ENTROPY_THD            12

// step: normal to gray
#define _LOCAL_DIMMING_STEP_N2G_MAX_FACTOR             20
#define _LOCAL_DIMMING_STEP_N2G_MIN_FACTOR             5
#define _LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH0          10 // two bin second largetst diff
#define _LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH1          5
#define _LOCAL_DIMMING_STEP_N2G_DIFF_RECH_TH2          3

// step: gray to gray
#define _LOCAL_DIMMING_STEP_G2G_APPLY_DIFF_THD0        10 // two bin second largetst diff
#define _LOCAL_DIMMING_STEP_G2G_APPLY_DIFF_THD1        7 // one bin second largetst diff
#define _LOCAL_DIMMING_STEP_G2G_APPLY_DIFF_THD2        4
#define _LOCAL_DIMMING_STEP_G2G_OBI_DIFF_REG           4
#define _LOCAL_DIMMING_STEP_G2G_MIN_FACTOR             3

// step: normal
#define _LOCAL_DIMMING_STEP_NOR_APPLY_DIFF_THD0        20
#define _LOCAL_DIMMING_STEP_NOR_APPLY_DIFF_THD1        10
#define _LOCAL_DIMMING_STEP_NOR_APPLY_DIFF_THD2        6
#define _LOCAL_DIMMING_STEP_NOR_APPLY_DIFF_THD3        3

#define _LOCAL_DIMMING_STEP_NOR_DIFF_REGION_TH0        1
#define _LOCAL_DIMMING_STEP_NOR_DIFF_REGION_TH1        4

#define _LOCAL_DIMMING_STEP_NOR_MAX_FACTOR             20
#define _LOCAL_DIMMING_STEP_NOR_MIN_FACTOR             3


/*
diffbin 10: two bin second largetst diff
diffbin  5: one bin third largest diff
diffbin  2: half one bin third largest diff
*/
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
#define _LOCAL_DIMMING_LUT_STEP                        33
#else
#define _LOCAL_DIMMING_LUT_STEP                        256
#endif

#define _LOCAL_DIMMING_SCENE_ANALYSIS_STEP             33

#define _LOCAL_DIMMING_PWM_BLEND_GAIN                  64
#define _LOCAL_DIMMING_PWM_BLEND_DEFAULT_R             310

#define _LOCAL_DIMMING_PWM_DARK_TH0                    50
#define _LOCAL_DIMMING_PWM_DARK_TH1                    30


#define _LOCAL_DIMMING_CORNER_WANDB_THRESHOLD          995

#define _LOCAL_DIMMING_BLMODEL_POLLING_COUNT_MAX       3
#define _LOCAL_DIMMING_FULL_PATTERN_RGB_THD            2

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
#define _LOCAL_DIMMING_LOCAL_ADIM_FRAME_COUNT          1
#define _LOCAL_DIMMING_OVER_EXP                        3
#define _LOCAL_DIMMING_BLMODEL_LED_GAIN_H_WIDTH        ((_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL <= 16) ? 16 : 32)
#define _LOCAL_DIMMING_BLMODEL_LED_GAIN_SHIFT_THD      (_LOCAL_DIMMING_BLMODEL_LED_GAIN_H_WIDTH / 2)
#define _LOCAL_DIMMING_BLMODEL_GAIN_ZERO_PADDING_LEFT  ((_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL <= _LOCAL_DIMMING_BLMODEL_LED_GAIN_SHIFT_THD) ? _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL : (_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL + 1) / 2)
#define _LOCAL_DIMMING_BLMODEL_GAIN_ZERO_PADDING_RIGHT ((_LOCAL_DIMMING_PANEL_REGION_HORIZONTAL <= _LOCAL_DIMMING_BLMODEL_LED_GAIN_SHIFT_THD) ? _LOCAL_DIMMING_BLMODEL_LED_GAIN_H_WIDTH : (_LOCAL_DIMMING_BLMODEL_LED_GAIN_H_WIDTH - _LOCAL_DIMMING_PANEL_REGION_HORIZONTAL) + _LOCAL_DIMMING_BLMODEL_GAIN_ZERO_PADDING_LEFT)
#define _LOCAL_DIMMING_BOOST_THD                       4095
#endif

#define _LOCAL_DIMMING_BLMODEL_MAX_GAIN_POWER_SAVER    32

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Local Dimming Step Change Mode
//--------------------------------------------------
typedef enum
{
    _LOCAL_DIMMING_PICTURE_NORMAL,
    _LOCAL_DIMMING_PICTURE_TOTAL_WHITE,
    _LOCAL_DIMMING_PICTURE_TOTAL_BLACK,
    _LOCAL_DIMMING_PICTURE_WHITE_AND_BLACK,
    _LOCAL_DIMMING_PICTURE_NEARLY_BLACK,
    _LOCAL_DIMMING_PICTURE_CORNER,
    _LOCAL_DIMMING_PICTURE_ELSE_ONE_STEP,
} EnumLDPictureType;
typedef struct
{
    BYTE b1ColorOsdCurrentPWMEnable : 1;
    BYTE b1ColorTotalWorBOneStep : 1;
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
    BYTE b1BoostContrastModeEnable : 1;
    WORD usRegionBoostAdimStep;
    WORD usRegionBoostGainStep;
#endif
    BYTE ucColorSmoothLevel;
    BYTE ucColorStepLevel;
    BYTE ucColorOsdStepLevel;
    BYTE ucLocalDimmingSmoothParaSel;
#if(_LOCAL_DIMMING_DRR_MODE_SUPPORT == _ON)
    WORD usColorPictureBlackTH;
#endif
    WORD usColorPictureBNWTH;
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
    WORD usMinBlendPWMValue;
#endif

#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
    WORD usAvgStepFrac;
    WORD usPercentileStepFrac;
    WORD usAvgBlackValue;
    WORD usAvgBlackStep;
#endif
    EnumLocalDimmingCase enumLocalDimmingCase;
}StructLocalDimmingPerformanceAdjust;

typedef struct
{
    EnumLDPictureType enumLDPWMPictureType;
}StructLocalDimmingPictureType;

#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
typedef struct
{
    volatile BYTE ucColorApplyAdimValue;
    BYTE ucColorLastApplyAdimValue;
    BYTE ucColorGainValue;
    WORD usColorBoostLv;
    WORD pusColorApplyRegionBoost[_LOCAL_DIMMING_TOTAL_REGION];
}StructLocalDimmingHDR10BoostData;
#endif

typedef struct
{
    EnumLocalDimmingStatus enumLocalDimmingStatus;
    BYTE ucLocalDimmingBoostValue;
#if(_LOCAL_DIMMING_COMPENSATE_MODE != _LD_COMPENSATE_NONE)
    BYTE ucLocalDimmingLastCompADdim;
    BYTE ucLocalDimmingCompADdim;
#endif
#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
    bit bYavgReadEnableStatus;
#endif

}StructLocalDimmingKCPUStateValue;


typedef struct
{
    BYTE ucObiDiffRegion;
    BYTE ucObiDiffRegionChange;
    WORD usEntropy;
    WORD usLastEntropy;
    WORD usMaxHistoValue;
    DWORD ulBlackNum;
    DWORD ulWhiteNum;
    DWORD ulLastBlackNum;
    DWORD ulLastWhiteNum;
    BYTE ucMaxR;
    BYTE ucMaxG;
    BYTE ucMaxB;
    BYTE ucMinR;
    BYTE ucMinG;
    BYTE ucMinB;
}StructLocalDimmingSceneData;


typedef struct
{
    WORD usApplyBinDiff;
    WORD usExposureRegion;
}StructLocalDimmingApplyData;

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
typedef enum
{
    _LOCAL_DIMMING_LOCAL_ADIM_FALL,
    _LOCAL_DIMMING_LOCAL_ADIM_CLL,
}EnumLocalDimmingLocalAdimIG;

typedef enum
{
    _LOCAL_DIMMING_TRUE_PQ,
    _LOCAL_DIMMING_TRUE_CONTRAST,
}EnumLocalDimmingLocalAdimMode;


typedef enum
{
    _LOCAL_DIMMING_AREA_THD,
    _LOCAL_DIMMING_STAGE_BOOST_ADIM,
    _LOCAL_DIMMING_PQ_NO_BOOST_GAIN,
    _LOCAL_DIMMING_PQ_BOOST_GAIN,
    _LOCAL_DIMMING_CONTRAST_NO_BOOST_GAIN,
    _LOCAL_DIMMING_CONTRAST_BOOST_GAIN,
    _LOCAL_DIMMING_IGCODE_HDR,
    _LOCAL_DIMMING_IGCODE_FSII,
}EnumLocalDimmingLocalBoostDataIndex;

typedef struct
{
    BYTE b1HistoIndexFix : 1;
    EnumLocalDimmingLocalAdimMode enumLDAdimMode;
    BYTE ucCurrentGainIndex;
    EnumLocalDimmingLocalAdimIG enumLocalDimmingIGGoal;
    WORD pusBoostGain[_LOCAL_DIMMING_TOTAL_REGION];
#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
    WORD usGlobalBoostAdim;
    WORD usGlobalLedGain;
#endif
}StructLocalDimmingLocalAdim;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
#if(_LOCAL_DIMMING_MULTI_TIME_APPLY_SUPPORT == _OFF)
extern void UserCommonColorLocalDimmingProcess(void);
#if((_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))
extern void UserCommonColorLocalDimmingMBRAdimAdjust(void);
#endif
#else
extern void UserCommonColorLocalDimmingMultiTimeApplyProcess(void);
#endif
extern bit UserCommonColorLocalDimmingPWMStepFW(void);
extern void UserCommonColorLocalDimmingAdjustFWMode(void);
extern void UserCommonColorLocalDimmingSmoothFWMode(void);
extern void UserCommonColorLocalDimmingOSDPWMAdjust(void);
extern void UserCommonColorLocalDimmingSceneAnalysis(WORD *pusHistoPWM, WORD *pusLastHistoPWM, StructLocalDimmingSceneData *pstLocalDimmingSceneData);
extern void UserCommonColorLocalDimmingApplyDegree(WORD *pusApplyPWM, StructLocalDimmingSceneData stLocalDimmingSceneData);
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
#if(_LOCAL_DIMMING_USING_YAVG_INFO == _ON)
extern void UserCommonColorLocalDimmingGetYAVG(WORD *pusAVGY);
extern void UserCommonColorLocalDimmingBlendPWMUsingYavg(WORD *pusSmoothPWM, WORD *pusHistoPWM, WORD *pusApplyBlendPWM, WORD usMinBlendPWMValue);
#else
extern void UserCommonColorLocalDimmingBlendPWM(WORD *pusSmoothPWM, WORD *pusHistoPWM, WORD *pusApplyBlendPWM, StructLocalDimmingSceneData stLocalDimmingSceneData, WORD usMinBlendPWMValue);
#endif
#endif
extern void UserCommonColorLocalDimmingApplyAnalysis(WORD *pusColorApplyPWM, WORD *pusColorLastApplyPWM, StructLocalDimmingApplyData *pstLocalDimmingApplyData);
extern void UserCommonColorLocalDimmingStepTrueDirectMode(const StructLocalDimmingSceneData *pstColorLocalDimmingSceneData, const StructLocalDimmingApplyData *pstColorLocalDimmingApplyData);
#if(_LOCAL_DIMMING_UP_REGION_SUPPORT == _ON)
extern void UserCommonColorLocalDimmingCombineHistoPWM(WORD *pusColorHistoPWM, WORD *pusColorHistoPWMUP);
extern void UserCommonColorLocalDimmingPWMProcChangeHVRegion(EnumPWMProcRegionType enumPWMProcRegionType);
#endif
#if(_LOCAL_DIMMING_ENERGY_SAVE_MODE_SUPPORT == _ON)
#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
extern void UserCommonColorLocalDimmingLowerPowerPWMDirectType(WORD *pusColorHistoPWM, WORD *pusColorAvgY);
#else
extern void UserCommonColorLocalDimmingLowerPowerPWMEdgeType(WORD *pusColorHistoPWMUP, WORD *pusColorHistoPWM);
#endif
#endif
#endif

extern void UserCommonColorLocalDimmingInitialSetting(void);
extern void UserCommonColorLocalDimmingSmoothAdjust(void);
extern void UserCommonColorLocalDimmingDeepBlackEnable(EnumLocalDimmingCase enumLocalDimmingCase);
extern void UserCommonColorLocalDimmingSoftClampAdjust(void);
extern void UserCommonColorLocalDimmingRestoreBacklight(void);

#if(_FW_CPU32_IS_HIGH_SPEED_CPU == _TRUE)
extern EnumLDPictureType UserCommonColorLocalDimmingGetPictureType(WORD *pusColorHistoPWM, const StructLocalDimmingSceneData *pstLocalDimmingSceneData);
extern EnumLDSmoothType UserCommonColorLocalDimmingSmoothEffectAdjust(EnumLDPictureType enumLDPictureType);
extern EnumLDStepChangeType UserCommonColorLocalDimmingStepChangeEffectAdjust(EnumLDPictureType enumLDPictureType);
extern EnumLDSmoothType UserCommonColorLocalDimmingGetCornerSmoothMode(void);
extern bit UserCommonColorLocalDimmingCheckFullPattern(const StructLocalDimmingSceneData *pstLocalDimmingSceneData);
#endif

#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
extern bit UserCommonColorLocalDimmingSceneChangeModify(WORD *pusColorApplyPWM, WORD *pusColorLastApplyPWM, WORD *pusColorHistoPWM, WORD *pusColorLastHistoPWM, WORD *pusColorHistoPWM2);
#endif
#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
extern void UserCommonColorLocalDimmingBoostModify(void);
#endif

#if((_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))
extern void UserCommonColorLocalDimmingBoostSendCommand(void);
#endif

#if(_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM)
extern void UserCommonColorLocalDimmingCompByAdim(void);
#endif

#if(_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_DDIM)
extern void UserCommonColorLocalDimmingCompByDdim(WORD *pusSmoothPWM);
#endif

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
#if(_LOCAL_DIMMING_GLOBAL_BOOST_SUPPORT == _ON)
extern void UserCommonColorLocalDimmingSyncBoostModify(void);
#endif
#if(_LOCAL_DIMMING_SCENE_CHANGE_SUPPORT == _ON)
extern bit UserCommonColorLocalDimmingSyncSceneChangeModify(WORD *pusColorApplyPWM, WORD *pusColorLastApplyPWM, WORD *pusColorHistoPWM, WORD *pusColorLastHistoPWM, WORD *pusColorHistoPWM2);
#endif
#endif
extern bit UserCommonColorLocalDimmingCheckStatusBeforeBLFW(void);
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
extern void UserCommonColorLocalDimmingRegionBoostModify(void);
extern bit UserCommonColorLocalDimmingRegionBoostCheckSource(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonColorLocalDimmingRegionBoostSmooth(WORD *pusCurrentAdim, WORD *pusCurrentGainTable);
extern void UserCommonColorLocalDimmingRegionBoostFALLSwitch(void);
extern WORD UserCommonColorLocalDimmingRegionBoostGetBoostStage(void);
extern BYTE UserCommonColorLocalDimmingRegionBoostLoadingMod(BYTE ucAdimGainIndex);
extern bit UserCommonColorLocalDimmingRegionBoostContrastModeCheck(WORD *pusIGCode);
extern BYTE UserCommonColorLocalDimmingRegionBoostGetMaxRGBRatio(BYTE ucMaxRGBTHD, WORD usIndexBeam);
#endif

#if(_LOCAL_DIMMING_ADIM_MODIFY_SUPPORT == _ON)
extern void UserCommonColorLocalDimmingLocalAdimModify(void);
extern void UserCommonColorLocalDimmingLocalAdimSendCommand(void);
#endif
#endif


#endif // End of #ifndef __USER_COMMON_COLOR_LOCAL_DIMMING_H__
