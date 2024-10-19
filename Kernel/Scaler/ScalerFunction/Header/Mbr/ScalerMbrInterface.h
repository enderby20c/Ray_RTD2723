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
// ID Code      : ScalerMbrInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#define SET_MBR_DVTOTAL(x)                      (g_usMbrDVTotal = (x))

#define GET_MBR_BACKLIGHT_MODE()                (g_enumMbrBacklightMode)
#define SET_MBR_BACKLIGHT_MODE(x)               (g_enumMbrBacklightMode = (x))

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#define _MBR_DRR_SWITCH_FRAME_COUNT             (100)
#define _MBR_DRR_TRANSITION_FRAME_CNT_HI        (1)
#define _MBR_DRR_TRANSITION_FRAME_CNT_LO        (2)
#define _MBR_DRR_AVG_IVF_FRAME_CNT              (4)

#define GET_MBR_DRR_VFREQ_AVG()                 (g_usMbrDrrVFreq_avg)
#define GET_MBR_DRR_VFREQ_AVG_EXINT0()          (g_usMbrDrrVFreq_avg)
#define SET_MBR_DRR_VFREQ_AVG(x)                (g_usMbrDrrVFreq_avg = (x))
#define SET_MBR_DRR_VFREQ_AVG_EXINT0(x)         (g_usMbrDrrVFreq_avg = (x))

#define GET_MBR_DRR_STEP_CHG_CNT()              (g_ucMbrDrrStepChangeCnt)
#define SET_MBR_DRR_STEP_CHG_CNT(x)             (g_ucMbrDrrStepChangeCnt = (x))

#define GET_MBR_DRR_BACKLIGHT_MODE()            (g_enumMbrDrrBacklightMode)
#define SET_MBR_DRR_BACKLIGHT_MODE(x)           (g_enumMbrDrrBacklightMode = (x))

#define GET_MBR_DRR_SAFE_CNT()                  (g_usMbrDrrSafeCount)
#define GET_MBR_DRR_SAFE_CNT_EXINT0()           (g_usMbrDrrSafeCount)
#define SET_MBR_DRR_SAFE_CNT()                  (g_usMbrDrrSafeCount = MINOF(g_usMbrDrrSafeCount + 1, 0xFFFF))
#define SET_MBR_DRR_SAFE_CNT_EXINT0()           (g_usMbrDrrSafeCount = MINOF(g_usMbrDrrSafeCount + 1, 0xFFFF))
#define CLR_MBR_DRR_SAFE_CNT()                  (g_usMbrDrrSafeCount = 0)
#define CLR_MBR_DRR_SAFE_CNT_EXINT0()           (g_usMbrDrrSafeCount = 0)

#define GET_MBR_DRR_TCON_TOGGLE_TIME()          (g_ucMbrDrrTconToggleTime)
#define SET_MBR_DRR_TCON_TOGGLE_TIME(x)         (g_ucMbrDrrTconToggleTime = (x))

#define GET_MBR_DRR_HW_SUPPORT()                (g_bMbrDrrHWSupport)
#define SET_MBR_DRR_HW_SUPPORT(x)               (g_bMbrDrrHWSupport = (x))
#endif

#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
#define GET_MBR_BFI_AVAILABLE_MODE()            (g_enumMbrBFIAvailableMode)
#define SET_MBR_BFI_AVAILABLE_MODE(x)           (g_enumMbrBFIAvailableMode = (x))
#define CLR_MBR_BFI_AVAILABLE_MODE()            (g_enumMbrBFIAvailableMode = _BFI_KERNEL_OFF)
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _MBR_DRR_MODE_OFF,
    _MBR_DRR_MODE_STROBE,
    _MBR_DRR_MODE_CONSTANT,
    _MBR_DRR_MODE_STROBE_TO_CONSTANT,
    _MBR_DRR_MODE_CONSTANT_TO_STROBE,
} EnumMbrDrrBacklightMode;

typedef enum
{
    _BACKLIGHT_SEQ_PDIM,
    _BACKLIGHT_SEQ_ADIM,
    _BACKLIGHT_SEQ_DELAY,
} EnumMbrBacklightSeqEvent;

typedef enum
{
    _BFI_KERNEL_OFF = _OFF,
    _BFI_KERNEL_1X,
    _BFI_KERNEL_2X,
} EnumMbrBFIKernelMode;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
extern EnumMbrBacklightMode g_enumMbrBacklightMode;
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern EnumMbrDrrBacklightMode g_enumMbrDrrBacklightMode;
extern volatile WORD g_usMbrDrrSafeCount;
extern volatile WORD g_usMbrDrrVFreq_avg;
extern BYTE g_ucMbrDrrStepChangeCnt;
extern BYTE g_ucMbrDrrTconToggleTime;
extern bit g_bMbrDrrHWSupport;
#endif
#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
extern EnumMbrBFIKernelMode g_enumMbrBFIAvailableMode;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
extern EnumMbrBacklightMode ScalerMbrCheckBacklightMode(EnumMbrBacklightMode enumBacklightMode, EnumInputPort enumInputPort);
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void ScalerMbrDrrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
extern void ScalerMbrDrrStepChange(BYTE ucTcon, WORD usStrobePeriod, BYTE ucDuty, BYTE ucPosition);
extern void ScalerMbrDrrAdjust(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
extern void ScalerMbrDrrClearSetting(BYTE ucTcon);
#endif
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void ScalerMbrRtkAdvMbrCtrl(BYTE ucTcon, BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
#endif

#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
extern EnumMbrBFIMode ScalerMbrGetBlackFrameInsertEnable(void);
extern void ScalerMbrSetBlackFrameInsertAvailableMode(void);
#endif

