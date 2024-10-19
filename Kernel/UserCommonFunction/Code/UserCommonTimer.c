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
// ID Code      : UserCommonTimer.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "Timer/UserCommonTimer.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_INSTANT_TIMER_EVENT_0 == _ON)
//--------------------------------------------------
// Description  : Timer0 Set Timer Counter
// Input Value  : ucTimerMs --> Counter in ms (1~65535ms)
//                Stops Timer0 if ucTimerMs = 0 or _TIMER_OFF
// Output Value : None
//--------------------------------------------------
void UserCommonTimer0SetTimerCount(WORD usTimerMs)
{
    ScalerTimer0SetTimerCount(usTimerMs);
}
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
//--------------------------------------------------
// Description  : Timer0 Set Timer Counter
// Input Value  : ucTimerMs --> Counter in ms (1~65535ms)
//                Stops Timer0 if ucTimerMs = 0 or _TIMER_OFF
// Output Value : None
//--------------------------------------------------
void UserCommonTimer1SetTimerCount(WORD usTimerMs)
{
    ScalerTimer1SetTimerCount(usTimerMs);
}
#endif

//--------------------------------------------------
// Description  : Active Timer Event
// Input Value  : usTime --> Time to active Timer Event
//                ucEventID --> Event to be actived
// Output Value : _TRUE if actived successfully
//--------------------------------------------------
bit UserCommonTimerActiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID)
{
    return ScalerTimerActiveTimerEvent(usTime, enumEventID);
}

//--------------------------------------------------
// Description  : Reactive a timer for an event. If the event is exist,
//                this function will reset the executing time and restart.
// Input Value  : usTime    --> Unit in 1ms, range in 0.01 ~ 61 sec
//                Event     --> Execute Event while timeup
// Output Value : _TRUE if actived successfully
//--------------------------------------------------
bit UserCommonTimerReactiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID)
{
    return ScalerTimerReactiveTimerEvent(usTime, enumEventID);
}

//--------------------------------------------------
// Description  : Cancel an event
// Input Value  : Event     --> Event which we want to cancel
// Output Value : None
//--------------------------------------------------
void UserCommonTimerCancelTimerEvent(EnumScalerTimerEventID enumEventID)
{
    ScalerTimerCancelTimerEvent(enumEventID);
}

//--------------------------------------------------
// Description  : Search a timer event
// Input Value  : ucEventID --> Event which has been activated
// Output Value : None
//--------------------------------------------------
bit UserCommonTimerSearchActiveTimerEvent(EnumScalerTimerEventID enumEventID)
{
    return ScalerTimerSearchActiveTimerEvent(enumEventID);
}

//--------------------------------------------------
// Description  : Timer Delay
// Input Value  : usNum --> Delay in ms
// Output Value : None
//--------------------------------------------------
void UserCommonTimerDelayXms(WORD usNum)
{
    ScalerTimerDelayXms(usNum);
}

//--------------------------------------------------
// Description  : Check if Event is Valid
// Input Value  : ucEventID --> Event which has been activated
// Output Value : None
//--------------------------------------------------
void UserCommonTimerWaitForActiveTimerEvent(EnumScalerTimerEventID enumEventID)
{
    ScalerTimerWaitForActiveTimerEvent(enumEventID);
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
//                enumInputDataPath --> I-domain data path
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit UserCommonTimerWaitForIDomainEvent(EnumWaitIDomainEventType enumEvent, EnumInputDataPath enumInputDataPath)
{
    return ScalerTimerWaitForIDomainEvent(enumEvent, enumInputDataPath);
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : enumEvent   --> Specified event
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit UserCommonTimerWaitForDDomainEvent(EnumWaitDDomainEventType enumEvent)
{
    return ScalerTimerWaitForDDomainEvent(enumEvent);
}

//--------------------------------------------------
// Description  : Get Event Remain Time
// Input Value  : ucEventID --> Event which has been activated
// Output Value : Event ID Time
//--------------------------------------------------
WORD UserCommonTimerGetEventRemainTime(EnumScalerTimerEventID enumEventID)
{
    return ScalerTimerGetEventRemainTime(enumEventID);
}

