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
// ID Code      : ScalerVgaAuto.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_VGA_AUTO_H__
#define __SCALER_VGA_AUTO_H__

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_YPBPR_SUPPORT == _ON)
#define _AUTO_Y_MAX_LEVEL                        (235)
#define _AUTO_PBPR_MAX_LEVEL                     (240)
#define GET_TUNE_YPBPR_STATUS()                  (ScalerGetBit(P0_CF_ADC_CTL_RED, _BIT7) == _BIT7)
#endif

#define _DEFAULT_GAIN                            (0xFF)
#define _DEFAULT_OFFSET                          (0x40)
#define _AUTO_RGB_MAX_LEVEL                      (255)

#define _ADC_MAXIMUM_TOLERANCE                   (60)
#define _BLACK_LEVEL_THRESHOLD                   (32)
#define _USER_ADJUST_OFFSET_RANGE                (5)

#define GET_AUTO_RESULT_WORD2()                  (ScalerGetWord(P30_D4_VGATOP_AUTO_PHASE_3))
#define GET_AUTO_RESULT_WORD1()                  (ScalerGetWord(P30_D5_VGATOP_AUTO_PHASE_2))
#define GET_AUTO_RESULT_WORD0()                  (ScalerGetWord(P30_D6_VGATOP_AUTO_PHASE_1))
#define GET_AUTO_RESULT_MAX()                    (ScalerGetByte(P30_D7_VGATOP_AUTO_PHASE_0))
#define GET_AUTO_RESULT_MIN()                    (ScalerGetByte(P30_D7_VGATOP_AUTO_PHASE_0) ^ 0xFF)
#define GET_AUTO_ADC_GAIN()                      (ScalerGetByte((P0_C2_ADC_GAI_BLU_MSB - ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, (_BIT1 | _BIT0)))))
#define GET_AUTO_ADC_OFFSET()                    (ScalerGetByte((P0_C5_ADC_OFF_BLU_MSB - ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, (_BIT1 | _BIT0)))))
#define SET_AUTO_ADC_GAIN(ucValue)               {ScalerSetByte((P0_C2_ADC_GAI_BLU_MSB - ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, (_BIT1 | _BIT0))), (ucValue));}
#define SET_AUTO_ADC_OFFSET(ucValue)             {ScalerSetByte((P0_C5_ADC_OFF_BLU_MSB - ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, (_BIT1 | _BIT0))), (ucValue));}
#define SET_AUTO_ADC_CHANNEL(ucColor)            {ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), (((ucColor) == _AUTO_BLUE_CHANNEL) ? 0 : (((ucColor) == _AUTO_GREEN_CHANNEL) ? 1 : 2)));}
#define SET_AUTO_ADC_NEXT_CHANNEL()              {ScalerSetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, ~(_BIT1 | _BIT0), ((ScalerGetBit(P30_CA_VGATOP_AUTO_ADJ_CTRL0, (_BIT1 | _BIT0)) + 1) % 3));}

//--------------------------------------------------
// Definitions of Internal Auto Color
//--------------------------------------------------
#if(_ADC_SELF_CALIBRATION == _ON)

#define GET_CALIBRATION_STATUS()                 (ScalerGetBit(P0_D2_ADC_GAIN_CALI, _BIT4) == _BIT4)

#if((_SELF_CALIBRATION_CLK > 220) || (_SELF_CALIBRATION_CLK < 15))
#undef _SELF_CALIBRATION_CLK
#define _SELF_CALIBRATION_CLK                    (148) // MHz
#endif

#define _SELF_CALIBRATION_HTOTAL                 (((DWORD)_PANEL_DH_TOTAL * _SELF_CALIBRATION_CLK) / (GET_PANEL_PIXEL_CLOCK_TYPICAL() / 1000)) // pixels
#define _SELF_CALIBRATION_HFREQ                  ((WORD)((DWORD)GET_PANEL_PIXEL_CLOCK_TYPICAL() * 10 / _PANEL_DH_TOTAL)) // 0.1 KHz
#endif

//--------------------------------------------------
// Definitions of known white area
//--------------------------------------------------
#ifndef _AUTO_CUSTOM_WHITE_HSTART
#define _AUTO_CUSTOM_WHITE_HSTART                (ScalerVgaTopGetCaptureHDelay() + ScalerVgaTopGetCaptureHStartPosition() + GET_INPUT_TIMING_HWIDTH() / 2)
#endif

#ifndef _AUTO_CUSTOM_WHITE_VSTART
#define _AUTO_CUSTOM_WHITE_VSTART                (ScalerVgaTopGetCaptureVDelay() + ScalerVgaTopGetCaptureVStartPosition() + GET_INPUT_TIMING_VHEIGHT() / 2)
#endif

#ifndef _AUTO_CUSTOM_WHITE_HEND
#define _AUTO_CUSTOM_WHITE_HEND                  (_AUTO_CUSTOM_WHITE_HSTART + 0x0F)
#endif

#ifndef _AUTO_CUSTOM_WHITE_VEND
#define _AUTO_CUSTOM_WHITE_VEND                  (_AUTO_CUSTOM_WHITE_VSTART + 0x0F)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of stages in auto-color process
//--------------------------------------------------
typedef enum
{
    _AUTO_COLOR_TUNING = 0x00,
    _AUTO_COLOR_STAGE1,
    _AUTO_COLOR_STAGE2,
    _AUTO_COLOR_COMPENSTE,
    _AUTO_COLOR_END,
} EnumAutoColorTuningStage;

//--------------------------------------------------
// Definitions image auto-function boundary setting
//--------------------------------------------------
typedef enum
{
    _MEASURE_ACTIVE_REGION = 0x00,
    _MEASURE_PORCH_REGION,
    _MEASURE_MANUAL_REGION,
} EnumMeasureBoundary;

typedef EnumAutoResult (*FUNC_PTR_UPDATE_GAIN)(BYTE, BYTE);
typedef EnumAutoResult (*FUNC_PTR_COMPENSATE)(EnumAutoColorType);

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumAutoResult ScalerVgaAutoBalanceHandler(EnumAutoColorType enumAutoType);
extern void ScalerVgaAutoInitializeAutoColor(EnumAutoColorType enumAutoType);
extern EnumAutoResult ScalerVgaAutoUpdateAdcGain(BYTE ucGainBias, BYTE ucStepRatio);
extern EnumAutoResult ScalerVgaAutoUpdateAdcGainOnly(BYTE ucGainBias, BYTE ucStepRatio);
extern EnumAutoResult ScalerVgaAutoCompensateRGB(EnumAutoColorType enumAutoType);
extern EnumAutoResult ScalerVgaAutoHardwareAbl(BYTE ucTarget, BYTE ucFrameCount);
extern BYTE ScalerVgaAutoConvertAdcGainStep(BYTE ucGain, BYTE ucTarget, BYTE ucCurrent);
extern EnumAutoResult ScalerVgaAutoCompensateChannel(BYTE ucColor, EnumAutoColorType enumAutoType);
extern EnumAutoResult ScalerVgaAutoCompensateOffset(BYTE ucColor);
extern void ScalerVgaAutoSetBoundary(EnumMeasureBoundary enumBoundary);
extern EnumAutoResult ScalerVgaAutoCompareMeasure(EnumMeasureType enumType);
extern EnumAutoResult ScalerVgaAutoAccumulationMeasure(EnumMeasureType enumType, BYTE ucThreshold);
extern EnumAutoResult ScalerVgaAutoMainToneMeasure(BYTE ucStartLevel, BYTE *pucMainTone);

#if(_YPBPR_SUPPORT == _ON)
#if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE)
extern EnumAutoResult ScalerVgaAutoCompensateYPbPr(EnumAutoColorType enumAutoType);
#endif
#endif // End of #if(_YPBPR_SUPPORT == _ON)

#if(_ADC_SELF_CALIBRATION == _ON)
extern EnumAutoResult ScalerVgaAutoUpdateAdcGainCalibrationRGB(BYTE ucGainBias, BYTE ucStepRatio);
extern EnumAutoResult ScalerVgaAutoCompensateCalibrationRGB(EnumAutoColorType enumAutoType);
extern void ScalerVgaAutoInitializeCalibration(void);
extern void ScalerVgaAutoResetCalibration(void);
extern EnumAutoResult ScalerVgaAutoAblMeasure(void);
#endif

extern EnumAutoResult ScalerVgaAutoCustomUpdateAdcGain(BYTE ucGainBias, BYTE ucStepRatio);
extern EnumAutoResult ScalerVgaAutoCustomUpdateAdcGainChannel(BYTE ucColor, BYTE ucGainBias, BYTE ucStepRatio);

#endif // End of #if(_VGA_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_VGA_AUTO_H__
