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
// ID Code      : ScalerTimerFunction.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TIMER_FUNCTION_H__
#define __SCALER_TIMER_FUNCTION_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of WD Timer Event Structure
//--------------------------------------------------
#define GET_WD_EVENT_TIME(x)                    (g_pstTimerWDEvent[x].ulTime)
#define SET_WD_EVENT_TIME(x, y)                 (g_pstTimerWDEvent[x].ulTime = (y))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTimerEventTableType g_pstTimerEvent[_TIMER_EVENT_COUNT];
extern DWORD g_ulTimerPrevWdtEventProcessTime;
extern volatile StructWDTimerEventType g_pstTimerWDEvent[_WD_TIMER_EVENT_COUNT];
extern volatile BYTE g_pucTimerDeferActiveWDID[_WD_TIMER_EVENT_COUNT];
extern volatile BYTE g_pucTimerDeferActiveWDTime[_WD_TIMER_EVENT_COUNT];
extern volatile BYTE g_ucTimerKcpuDeferActiveWDIndex;
extern volatile bit g_bTimerWDEventProcessNowFlag;

#if(_SCPU_SUPPORT == _ON)
extern volatile BYTE g_ucTimerScpuDeferActiveWDIndex;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_RECORD_TIMER_SUPPORT == _ON)
extern void ScalerTimerResetRecordTimer_WDINT(void);
extern BYTE ScalerTimerGetRecordTimer_EXINT0(void);
#endif

extern WORD ScalerTimerCheckTimerEvent(WORD usTime);
extern void ScalerTimerWDEventProcess(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
extern void ScalerTimerWDEventProcess_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime);


#endif // End of #ifndef __SCALER_TIMER_FUNCTION_H__
