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
// ID Code      : SysModeInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of User Osd Logo Status
//--------------------------------------------------
typedef enum
{
    _OSD_LOGO_OFF = _OFF,
    _OSD_LOGO_ON = _ON,
} EnumOsdLogoStatus;

//--------------------------------------------------
// Enumerations of User DCLK No Support Status
//--------------------------------------------------
typedef enum
{
    _DCLK_NO_SUPPORT_FALSE = _FALSE,
    _DCLK_NO_SUPPORT_TRUE = _TRUE,
} EnumDclkNoSupportStatus;

//--------------------------------------------------
// Enumerations of User Bypass Color Process Status
//--------------------------------------------------
typedef enum
{
    _BYPASS_COLOR_PROC_FALSE = _FALSE,
    _BYPASS_COLOR_PROC_TRUE = _TRUE,
} EnumBypassColorProcStatus;

//--------------------------------------------------
// Enumerations of Mode State
//--------------------------------------------------
typedef enum
{
    _MODE_STATUS_INITIAL = 0x00,
    _MODE_STATUS_DISPLAY_INITIAL,
    _MODE_STATUS_DISPLAY_SETTING,
    _MODE_STATUS_DISPLAY_CHECK,
    _MODE_STATUS_POWER_SAVING,
    _MODE_STATUS_POWER_OFF,
    _MODE_STATUS_FACTORY,
    _MODE_STATUS_NONE = 0x0F,
} EnumModeStatus;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE SysModeGetModeState(void);
extern void SysModeResetDisplayState(EnumDisplayRegion enumDisplayRegion);
extern void SysModeSetFreeRun(void);
extern bit SysModeGetModeStateChange(void);
extern void SysModeSetResetTarget(EnumModeAction enumResetTarget);
extern void SysModeSetDisplayTarget(EnumDisplayRegion enumDisplayRegion);
extern EnumDisplayRegion SysModeGetDisplayTarget(void);
extern EnumDisplayMode SysModeGetDisplayMode(void);

