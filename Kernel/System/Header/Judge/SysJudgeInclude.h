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
// ID Code      : SysJudgeInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1Start : 1;
    BYTE b1Stop : 1;
} StructDebounceStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysJudgeHandler(void);

#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_2P_FRAME_SYNC_DEBOUNCE_TIME != 0))
extern void SysJudge2pFrameSyncDebounceStart(void);
extern void SysJudge2pFrameSyncDebounceStop(void);
extern void SysJudge2pFrameSyncDebounceReset(void);
extern bit SysJudgeCheck2pFrameSyncDebounceSupported(void);
extern bit SysJudgeCheck2pFrameSyncDebounce(void);
#endif

