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
// ID Code      : ScalerMbrInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#define GET_MBR_DRR_VFREQ(x)                    (g_pusMbrDrrVFreq[x])
#define GET_MBR_DRR_VFREQ_EXINT0(x)             (g_pusMbrDrrVFreq[x])
#define SET_MBR_DRR_VFREQ(x, y)                 (g_pusMbrDrrVFreq[x] = (y))
#define SET_MBR_DRR_VFREQ_EXINT0(x, y)          (g_pusMbrDrrVFreq[x] = (y))
#endif
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern WORD g_pusMbrDrrVFreq[_MBR_DRR_AVG_IVF_FRAME_CNT];
#endif
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void ScalerMbrSetTconToggleSequence(BYTE ucTconEnd, WORD usDuty, WORD usHTotal);
extern void ScalerMbrIntHandlerDVS_EXINT0(void);
#endif
#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
extern void ScalerMbrUpdateBlackFrameInsertAvailableMode(void);
#endif

