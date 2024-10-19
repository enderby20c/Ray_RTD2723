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
// ID Code      : SysModeInterface.h No.0000
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
extern void SysModeClrModeStateChange(void);
extern void SysModeResetDataPath(BYTE ucRegionIndex);
extern void SysModeSetDisplayMode(EnumDisplayMode enumDisplayMode);

#if(_DRR_SUPPORT == _ON)
extern WORD SysModeDrrGetIVFreq(EnumInputPort enumInputPort);
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
extern WORD SysModeHdmi21GetFvaMaxIVf(EnumInputPort enumInputPort);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern void SysModeSetEagleSightSupport(void);
extern void SysModeEagleSightInputCapture(void);
extern void SysModeEagleSightDisplayCapture(void);
extern void SysModeEagleSightGetUserSetting(void);
#endif
