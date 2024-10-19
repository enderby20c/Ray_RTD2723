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
// ID Code      : ScalerTimerInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_TIMER32_1MS_TICK_COUNT()                (ScalerGlobalCtrlGetEclkClockRate() / _HW_CPU32_TO_TIMER32_CLK_DIV)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Timer Related Enum
//--------------------------------------------------
typedef enum
{
    _CPU_TIMER_0 = 0x00,  /*!< Timer0                    */
    _CPU_TIMER_1 = 0x01,  /*!< Timer1                    */
    _CPU_TIMER_2 = 0x02,  /*!< Timer2                    */
    _CPU_TIMER_3 = 0x03,  /*!< Timer3                    */
    _CPU_TIMER_4 = 0x04,  /*!< Timer4                    */
    _CPU_TIMER_5 = 0x05,  /*!< Timer5                    */
}EnumCpuTimerID;

typedef enum
{
    _TIMER_X_DISABLE = 0,             /*!< Disable Timerx            */
    _TIMER_X_ENABLE = ((1UL) << 31),  /*!< Enable Timerx            */
}EnumCpuTIMERxEN;

typedef enum
{
    _TIMER_X_COUNTER_MODE = 0,            /*!< TimerX as Counter (once) */
    _TIMER_X_TIMER_MODE = ((1UL) << 30),  /*!< TimerX as Timer (repeat) */
}EnumCpuTIMERxMode;

typedef enum
{
    _TIMER_X_CONTINUE = 0,           /*!< TimerX continue/start count    */
    _TIMER_X_PAUSE = ((1UL) << 29),  /*!< TimerX pause count            */
}EnumCpuTIMERxPause;

typedef enum
{
    _TIMER_X_INT_DISABLE = 0,             /*!< TimerX Disable Interrupt    */
    _TIMER_X_INT_ENABLE = ((1UL) << 31),  /*!< TimerX Enable Interrupt    */
}EnumCpuTIMERxIntEN;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTimerSetTargetValue(EnumCpuTimerID enumTimerID, DWORD ulTargetValue);
extern DWORD ScalerTimerGetTargetValue(EnumCpuTimerID enumTimerID);
extern DWORD ScalerTimerGetCurrentValue(EnumCpuTimerID enumTimerID);
extern void ScalerTimerClearCurrentValue(EnumCpuTimerID enumTimerID);

extern void ScalerTimerSetEnable(EnumCpuTimerID enumTimerID, bit bTimerEnFlag);
extern void ScalerTimerSetWorkMode(EnumCpuTimerID enumTimerID, EnumCpuTIMERxMode enumTimerWorkMode);
extern void ScalerTimerSetPause(EnumCpuTimerID enumTimerID, EnumCpuTIMERxPause enumTimerPauseFlag);

extern bit ScalerTimerGetEnable(EnumCpuTimerID enumTimerID);
extern DWORD ScalerTimerGetWorkMode(EnumCpuTimerID enumTimerID);
extern DWORD ScalerTimerGetPause(EnumCpuTimerID enumTimerID);


extern void ScalerTimerSetINTEn(EnumCpuTimerID enumTimerID, EnumCpuTIMERxIntEN enumTimerIntEnFlag);
extern bit ScalerTimerGet_NMI_Flag(EnumCpuTimerID enumTimerID);
extern void ScalerTimerAck_NMI_Flag(EnumCpuTimerID enumTimerID);
extern bit ScalerTimerGetINTFlag(EnumCpuTimerID enumTimerID);
extern void ScalerTimerAckINTFlag(EnumCpuTimerID enumTimerID);

extern DWORD ScalerTimerInitTimer(EnumCpuTimerID enumTimerID, EnumCpuTIMERxMode enumTimerWorkMode, DWORD ulTargetCountValue, bit bTimerEnFlag, EnumCpuTIMERxIntEN enumTimerIntEnFlag);

extern void ScalerTimerSetTimerCount(EnumScalerTimerOperationMode enumOperationMode);

#if(_INSTANT_TIMER_EVENT_0 == _ON)
extern void ScalerTimer0SetTimerCount(WORD usTimerMs);
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
extern void ScalerTimer1SetTimerCount(WORD usTimerMs);
#endif

