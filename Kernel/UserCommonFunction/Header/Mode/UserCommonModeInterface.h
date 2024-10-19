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
// ID Code      : UserCommonModeInterface.h No.0000
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
extern EnumBacklightAction UserCommonModeDisplaySettingGetBacklightAction(void);
extern void UserCommonModeDisplayInitialColorProc(EnumDisplayMode enumDisplayMode);
extern void UserCommonModeDisplaySettingInitialization(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonModeDisplaySettingColorProc(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonModeDisplayActiveProc(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonModeResetRegionProc(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonModeResumeRegionProc(EnumDisplayRegion enumDisplayRegion);
extern bit UserCommonModeGetReadyForActiveStatus(EnumDisplayRegion enumDisplayRegion);
extern bit UserCommonModeCheckNoSupport(EnumDisplayRegion enumDisplayRegion);

