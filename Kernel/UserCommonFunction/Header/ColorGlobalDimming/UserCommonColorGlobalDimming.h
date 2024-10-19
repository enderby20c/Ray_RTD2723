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
// ID Code      : UserCommonColorGlobalDimming.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_COLOR_GLOBAL_DIMMING_H__
#define __USER_COMMON_COLOR_GLOBAL_DIMMING_H__


#if(_GLOBAL_DIMMING_FUNCTION == _ON)
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
extern void UserCommonColorGlobalDimmingProcess(void);
extern void UserCommonColorGlobalDimmingDCRToLv(WORD usDCRMaxY, WORD *pusDCRToLV);
extern void UserCommonColorGlobalDimmingStepToTarget(WORD *pusApplyLv, WORD *pusTargetLv, WORD *pusLastApplyLv, WORD usDCRResult, WORD *pusLastDCRResult);
extern void UserCommonColorGlobalDimmingCalPWMValue(WORD usApplyLv);
extern void UserCommonColorGlobalDimmingSetGainValue(void);
extern void UserCommonColorGlobalDimmingBlackPerCal(void);
#if(_GLOBAL_DIMMING_ONLINE_CALIBRATION_SUPPORT == _ON)
extern WORD UserCommonColorGlobalDimmingGetWordFromFlash(BYTE ucBank, BYTE ucPage, WORD usStartAddress, WORD usIndex, BYTE ucSwap);
#endif
extern WORD UserCommonColorGlobalDimmingGetPWMTableValue(WORD usIndex);
#endif // End of #if(_GLOBAL_DIMMING_SUPPORT == _ON)


#endif // End of #ifndef __USER_COMMON_COLOR_GLOBAL_DIMMING_H__
