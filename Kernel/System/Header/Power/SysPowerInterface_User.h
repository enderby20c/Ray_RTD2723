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
// ID Code      : SysPowerInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of User Force to Power Saving Status
//--------------------------------------------------
typedef enum
{
    _FORCE_TO_PS_FALSE = _FALSE,
    _FORCE_TO_PS_TRUE = _TRUE,
} EnumForcePSStatus;

//--------------------------------------------------
// Enumerations of User Permission to Enter Power Saving
//--------------------------------------------------
typedef enum
{
    _PS_PERMISSION_FALSE = _FALSE,
    _PS_PERMISSION_TRUE = _TRUE,
} EnumPSPermissionStatus;

//--------------------------------------------------
// Enumerations of User Force into Fake Power Saving Status/Action
//--------------------------------------------------
typedef enum
{
    _FORCE_POWER_SAVING = 0x00,
    _FORCE_FAKE_POWER_SAVING,
} EnumForceFakePS;

//--------------------------------------------------
// Enumerations of User Force into Fake Power Off Status/Action
//--------------------------------------------------
typedef enum
{
    _FORCE_POWER_OFF = 0x00,
    _FORCE_FAKE_POWER_OFF,
} EnumForceFakePowerOff;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE SysPowerGetPowerStatus(void);
extern void SysPowerSetTargetPowerStatus(EnumPowerStatus enumPorStatus);

