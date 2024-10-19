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
// ID Code      : ScalerSysTickInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
#define SET_TARGET_SYSTICK_US(ulcntUS)    (g_ulSysTickTargetUS = (ulcntUS))
#define GET_TARGET_SYSTICK_US()           (g_ulSysTickTargetUS)
#else
#define SET_TARGET_SYSTICK_US(ulcntUS)    (g_ulSysTickScpuTargetUS = (ulcntUS))
#define GET_TARGET_SYSTICK_US()           (g_ulSysTickScpuTargetUS)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile DWORD g_ulSysTickTargetUS;

#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
extern volatile DWORD g_ulSysTickScpuTargetUS;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerSysTickInit(DWORD ulTickPriority);
extern void ScalerSysTickIncTick(void);
extern DWORD ScalerSysTickGetTick(void);
extern void ScalerSysTickSuspendTick(void);
extern void ScalerSysTickResumeTick(void);
extern DWORD ScalerSysTickGetCurrentValue(void);
extern DWORD ScalerSysTickGetReloadValue(void);
extern void ScalerSysTickAckFlag(void);

