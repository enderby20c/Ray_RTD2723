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
// ID Code      : UserCommonTimerInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_INSTANT_TIMER_EVENT_0 == _ON)
extern void UserCommonTimer0SetTimerCount(WORD usTimerMs);
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
extern void UserCommonTimer1SetTimerCount(WORD usTimerMs);
#endif

extern bit UserCommonTimerActiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
extern bit UserCommonTimerReactiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
extern void UserCommonTimerCancelTimerEvent(EnumScalerTimerEventID enumEventID);
extern bit UserCommonTimerSearchActiveTimerEvent(EnumScalerTimerEventID enumEventID);
extern void UserCommonTimerDelayXms(WORD usNum);
extern void UserCommonTimerWaitForActiveTimerEvent(EnumScalerTimerEventID enumEventID);
extern bit UserCommonTimerWaitForIDomainEvent(EnumWaitIDomainEventType enumEvent, EnumInputDataPath enumInputDataPath);
extern bit UserCommonTimerWaitForDDomainEvent(EnumWaitDDomainEventType enumEvent);
extern WORD UserCommonTimerGetEventRemainTime(EnumScalerTimerEventID enumEventID);

