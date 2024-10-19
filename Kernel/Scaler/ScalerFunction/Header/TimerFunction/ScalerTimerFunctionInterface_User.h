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
// ID Code      : ScalerTimerFunctionInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of KCPU/SCPU timer2 int status variable
//--------------------------------------------------
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
#define GET_TIMER2_INT_STATUS()                       (g_bTimer2NotifyInt)
#define SET_TIMER2_INT_STATUS(x)                      (g_bTimer2NotifyInt = (x))
#else
#define GET_TIMER2_INT_STATUS()                       (g_bTimer2ScpuNotifyInt)
#define SET_TIMER2_INT_STATUS(x)                      (g_bTimer2ScpuNotifyInt = (x))
#endif

#if(_SCPU_SUPPORT == _OFF)
#define SET_TIMER2_ALL_INT_STATUS(x)                  (g_bTimer2NotifyInt = (x))
#else
#define SET_TIMER2_ALL_INT_STATUS(x)                  {\
                                                          g_bTimer2NotifyInt = (x);\
                                                          g_bTimer2ScpuNotifyInt = (x);\
                                                      }
#endif

//--------------------------------------------------
// Definition of Instant Timer0/1 Counter Options
//--------------------------------------------------
#define _TIMER_OFF                                    0

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of I-Domain Waiting Events
//--------------------------------------------------
typedef enum
{
    _EVENT_IVS = _BIT7,
    _EVENT_IEN_START = _BIT6,
    _EVENT_IEN_STOP = _BIT5,
} EnumWaitIDomainEventType;

//--------------------------------------------------
// Enumerations of D-Domain Waiting Events
//--------------------------------------------------
typedef enum
{
    _EVENT_DVS = _BIT5,
    _EVENT_DEN_START = _BIT6,
    _EVENT_DEN_STOP = _BIT7,
} EnumWaitDDomainEventType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile bit g_bTimer2NotifyInt;

#if(_SCPU_SUPPORT == _ON)
extern volatile bit g_bTimer2ScpuNotifyInt;
#endif

extern volatile WORD data g_usTimerCounter;

#if(_TIME_CURSOR_SUPPORT == _ON)
extern volatile WORD data g_usTimerMeasureCounter;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

