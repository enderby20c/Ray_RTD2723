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
// ID Code      : ScalerTimerFunctionInterface.h No.0000
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
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
extern volatile BYTE data g_ucTimerQuarterCount;
#endif

extern volatile WORD data g_usTimerCounterDoubleBuffer;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTimerEventProc(EnumScalerTimerEventID enumEventID);
extern WORD ScalerTimerGetEventTime(BYTE ucEventIndex);
extern void ScalerTimerClrEventValid(BYTE ucEventIndex);
extern bit ScalerTimerCheckEventValid(BYTE ucEventIndex);

extern WORD ScalerTimerGetTimerCounter(void);
extern BYTE ScalerTimerGetEventID(BYTE ucEventIndex);
extern void ScalerTimerInitialTimerEvent(void);

extern bit ScalerTimerActiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
extern bit ScalerTimerReactiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
extern void ScalerTimerCancelTimerEvent(EnumScalerTimerEventID enumEventID);
extern WORD ScalerTimerGetEventRemainTime(EnumScalerTimerEventID enumEventID);
extern bit ScalerTimerSearchActiveTimerEvent(EnumScalerTimerEventID enumEventID);

extern void ScalerTimerDelayXms(WORD usNum);

extern void ScalerTimerWaitForActiveTimerEvent(EnumScalerTimerEventID enumEventID);
extern bit ScalerTimerWaitForIDomainEvent(EnumWaitIDomainEventType enumEvent, EnumInputDataPath enumInputDataPath);
extern bit ScalerTimerWaitForDDomainEvent(EnumWaitDDomainEventType enumEvent);

extern void ScalerTimerWDEventProc_WDINT(void);
extern void ScalerTimerWDRefClkChange(void);


