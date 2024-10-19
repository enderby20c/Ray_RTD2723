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
// ID Code      : SysJudge.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SYS_JUDGE_H__
#define __SYS_JUDGE_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_2P_FRAME_SYNC_DEBOUNCE_TIME != 0))
#define GET_2P_FRAME_SYNC_DEBOUNCE_START()      (g_stJudge2pFrameSyncDebounce.b1Start != 0)
#define SET_2P_FRAME_SYNC_DEBOUNCE_START(x)     (g_stJudge2pFrameSyncDebounce.b1Start = (x))

#define GET_2P_FRAME_SYNC_DEBOUNCE_STOP()       (g_stJudge2pFrameSyncDebounce.b1Stop != 0)
#define SET_2P_FRAME_SYNC_DEBOUNCE_STOP(x)      (g_stJudge2pFrameSyncDebounce.b1Stop = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_2P_FRAME_SYNC_DEBOUNCE_TIME != 0))
extern StructDebounceStatus g_stJudge2pFrameSyncDebounce;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysJudgeUpdateDisplayState(void);
extern void SysJudgeCheckAllPathStatus(void);
extern bit SysJudgeCheckStatus(BYTE ucRegionIndex);
extern bit SysJudgeStateChangeEvent(EnumModeStatus enumModeState);
extern void SysJudgeModeResetProc(void);
extern WORD SysJudgeGetActiveWaitTime(void);


#endif // End of #ifndef __SYS_JUDGE_H__
