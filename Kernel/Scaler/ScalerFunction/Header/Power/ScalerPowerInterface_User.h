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
// ID Code      : ScalerPowerInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Power Action
//--------------------------------------------------
typedef enum
{
    _POWER_ACTION_OFF_TO_NORMAL = 0x00,
    _POWER_ACTION_OFF_TO_FAKE_OFF,
    _POWER_ACTION_AC_ON_TO_NORMAL,
    _POWER_ACTION_AC_ON_TO_OFF,
    _POWER_ACTION_AC_ON_INITIAL,
    _POWER_ACTION_PS_TO_NORMAL,
    _POWER_ACTION_PS_TO_OFF,
    _POWER_ACTION_NORMAL_TO_PS,
    _POWER_ACTION_NORMAL_TO_OFF,
    _POWER_ACTION_NORMAL_TO_FAKE_OFF,
    _POWER_ACTION_NORMAL_TO_FAKE_PS,
    _POWER_ACTION_FAKE_PS_TO_NORMAL,
    _POWER_ACTION_FAKE_OFF_TO_NORMAL,
    _POWER_ACTION_NONE = 0xFF,
} EnumPowerAction;

//--------------------------------------------------
// Enumerations of Power Status/Action
//--------------------------------------------------
typedef enum
{
    _POWER_STATUS_AC_ON = 0x00,
    _POWER_STATUS_OFF,
    _POWER_STATUS_NORMAL,
    _POWER_STATUS_SAVING,
    _POWER_STATUS_NONE = 0x0F,
} EnumPowerStatus;

//--------------------------------------------------
// Enumerations of Power Domain Status
//--------------------------------------------------
typedef enum
{
    _POWER_OFF,
    _POWER_ON,
} EnumPowerTarget;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

