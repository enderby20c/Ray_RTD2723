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
// ID Code      : UserCommonMode.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_MODE_H__
#define __USER_COMMON_MODE_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _PROC_REGION_TYPE_INSIDE = 0,
    _PROC_REGION_TYPE_OUTSIDE,
    _PROC_REGION_TYPE_FULL,
    _PROC_REGION_TYPE_NONE,
}EnumProcRegionType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonModeDisplaySettingByPassColorProc(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonModeDisplaySettingSingleColorProc(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonModeDisplaySettingMultiColorProc(EnumSelRegion enumSelRegion);
extern EnumProcRegionType UserCommonModeDisplaySettingTransSelRegionProcType(EnumSelRegion enumSelRegion);

#if(_COLOR_DEMO_FUNCTION == _ON)
extern void UserCommonModeDisplaySettingDemoModeColorProc(EnumDisplayRegion enumDisplayRegion);
#endif

extern void UserCommonModeDisplaySettingNormalModeColorProc(EnumDisplayRegion enumDisplayRegion);
#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT == _ON)
extern void UserCommonModeSetESOriginalModeSUFI(EnumDisplayRegion enumDisplayRegion);
#endif
#endif

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
extern bit UserCommonModeColorimetrySeamlessChangeCheckBypass(EnumInputPort enumInputPort);
#endif
#endif // End of #ifndef __USER_COMMON_MODE_H__
