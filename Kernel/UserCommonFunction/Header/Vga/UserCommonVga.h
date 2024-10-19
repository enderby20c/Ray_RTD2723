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
// ID Code      : UserCommonVga.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_VGA_H__
#define __USER_COMMON_VGA_H__

#if(_VGA_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Phase Range
//--------------------------------------------------
#define _ADJUST_PHASE_MAX                           63
#define _ADJUST_PHASE_MIN                           0
#define _ADJUST_PHASE_CENTER                        (((_ADJUST_PHASE_MAX - _ADJUST_PHASE_MIN) / 2) + _ADJUST_PHASE_MIN)

//--------------------------------------------------
// Definitions of Clock Settings Used by COsdFxGetAdcClockRange()
//--------------------------------------------------
#ifndef _CUSTOM_CLOCK_BIAS_VALUE
#define _CLOCK_BIAS                                 50
#else
#define _CLOCK_BIAS                                 _CUSTOM_CLOCK_BIAS_VALUE
#endif

//--------------------------------------------------
// Active Region Percentage Threshold (%)
//--------------------------------------------------
#define _ACTIVE_REGION_PERCENTAGE_THD               ((100 - _AUTO_CLOCK_RANGE) / 2)

//--------------------------------------------------
// Auto config position over direction
//--------------------------------------------------
#define _AUTO_POSITION_OVER_NONE                    0x00
#define _AUTO_POSITION_OVER_LEFT                    _BIT0
#define _AUTO_POSITION_OVER_RIGHT                   _BIT1
#define _AUTO_POSITION_OVER_TOP                     _BIT2
#define _AUTO_POSITION_OVER_BOTTOM                  _BIT3

//--------------------------------------------------
// Definition of auto position before auto clock
//--------------------------------------------------
#define _AUTO_POSITION_FIRST_EN                     _ON
#define _AUTO_POSITION_FOR_IN_REGION_EN             _ON

//--------------------------------------------------
// Definition of results of checking active region
//--------------------------------------------------
#define _AUTO_ACTIVE_REGION_IN                      0xFE
#define _AUTO_ACTIVE_REGION_OUT                     0xFF

//--------------------------------------------------
// Definition of max auto faulure count
//--------------------------------------------------
#define _MAX_AUTO_FAIL_COUNT                        3

//--------------------------------------------------
// Definition of multi measure function tolerance
//--------------------------------------------------
#define _AUTO_MULTI_MEASURE_CHECK_TOL_H             4
#define _AUTO_MULTI_MEASURE_CHECK_TOL_V             1

//--------------------------------------------------
// Set IHS Capture Start (Minimum)
//--------------------------------------------------
#define _IHS_CAPTURE_START                          4

//--------------------------------------------------
// Set Center Position Non-adjusting Range (%) by IHWidth
//--------------------------------------------------
#define _AUTO_POSITION_CENTER_H_RANGE               85

//--------------------------------------------------
// Set Center Position Non-adjusting Range (%) by IVHeight
//--------------------------------------------------
#define _AUTO_POSITION_CENTER_V_RANGE               50

//--------------------------------------------------
// Definitions of Fine Tune Clock Range
//--------------------------------------------------
#define _FINE_TUNE_CLOCK_START                      1
#define _FINE_TUNE_CLOCK_NUMBER                     6
#define _FINE_TUNE_CLOCK_RANGE                      4

//--------------------------------------------------
// Definitions of Hardware Auto Phase Step
//--------------------------------------------------
#define _HWAUTO_STEP_1                              0x00
#define _HWAUTO_STEP_2                              0x01
#define _HWAUTO_STEP_4                              0x02
#define _HWAUTO_STEP_8                              0x03
#define _HWAUTO_STEP_16                             0x04

#define _HWAUTO_STEP                                _HWAUTO_STEP_8
#define _HWAUTO_START                               0
#define _HWAUTO_NUMBER                              8    // _HWAUTO_NUMBER <= (QPhase * VCO_divider - _HWAUTO_START)mod(_HWAUTO_STEP), QPhase = 32, VCO_divider = 2 or 4

//--------------------------------------------------
// Auto config error status
//--------------------------------------------------
#define _AUTO_CONFIG_MEASURE_ERROR                  _BIT0
#define _AUTO_CONFIG_CLOCK_ABORT                    _BIT1
#define _AUTO_CONFIG_PHASE_ABORT                    _BIT2

//--------------------------------------------------
// Auto config Percentage Stage
//--------------------------------------------------
#define _AUTO_CONFIG_CHECK_MULTITIMES_FINISH        5
#define _AUTO_CONFIG_CLOCK_CHECK_WIDTH_FINISH       10
#define _AUTO_CONFIG_CLOCK_ROUGH_ADJUST_FINISH      20
#define _AUTO_CONFIG_CLOCK_FINETUNE_FINISH          75
#define _AUTO_CONFIG_CLOCK_FINISH                   80
#define _AUTO_CONFIG_PHASE_FINISH                   90
#define _AUTO_CONFIG_V_POSITION_FINISH              95
#define _AUTO_CONFIG_H_POSITION_FINISH              100


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit UserCommonVgaAutoClock(void);
extern bit UserCommonVgaAutoHPosition(void);
extern bit UserCommonVgaAutoVPosition(void);
extern bit UserCommonVgaAutoPhase(void);
extern void UserCommonVgaAutoUpdateUserdata(void);
extern bit UserCommonVgaAutoClockRoughAdjust(WORD *pusCurrClock);
extern bit UserCommonVgaAutoClockFineTuneAdjust(WORD *pusCurrClock);
extern bit UserCommonVgaAutoClockCheckPictureRegion(void);
extern bit UserCommonVgaAutoCheckClock(WORD usCurrClock);
//extern void UserCommonVgaAutoPhaseTestFunction(void);

#endif // End of #if(_VGA_SUPPORT == _ON)


#endif // End of #ifndef __USER_COMMON_VGA_H__
