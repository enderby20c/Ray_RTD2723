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
// ID Code      : UserCommonColorGlobalDimmingInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_GLOBAL_DIMMING_FUNCTION == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GLOBAL_DIMMING_MAX_GAIN                   0xA00
#define _GLOBAL_DIMMING_MIN_GAIN                   0x200
#define _GLOBAL_DIMMING_SRGB_MAX                   0x7CC
#define _GLOBAL_DIMMING_WHITE_THD                  668
#define _GLOBAL_DIMMING_ACTIVE_THD                 400
#define _GLOBAL_DIMMING_ONE_STEP_THD               950


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonColorGlobalDimmingInitialSetting(bit bEn);
extern void UserCommonColorGlobalDimmingSetPWMValue(WORD usPWM);

#endif // End of #if(_GLOBAL_DIMMING_SUPPORT == _ON)

