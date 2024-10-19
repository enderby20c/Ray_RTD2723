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
// ID Code      : ScalerGlobalInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DWORD_MUL_DIV(x, y, z)                          (ScalerGlobalComputeDwordMulDiv((x), (y), (z)))

#define MULTIPLY_OVERFLOW32_CHECK(x, y)                     (((x) == 0) || ((y) == 0) || ((DWORD)(x) < (0xFFFFFFFF / (DWORD)(y))))

#define _MAX_ADDRESS_OF_32BIT                               (0xFFFFFFFFUL)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Mode Action
//--------------------------------------------------
typedef enum
{
    _MODE_ACTION_NO_RESET_MODE = 0x00,
    _MODE_ACTION_RESET_TO_DISPLAY_INITIAL,
    _MODE_ACTION_RESET_TO_DISPLAY_SETTING,
    _MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG,
    _MODE_ACTION_RESET_TO_DISPLAY_CHECK,
    _MODE_ACTION_RESET_TO_POWER_SAVING,
    _MODE_ACTION_RESET_TO_POWER_OFF,
    _MODE_ACTION_RESET_TO_FACTORY_MODE,
    _MODE_ACTION_NONE = 0x0F,
} EnumModeAction;

typedef enum
{
    _D_DOMAIN_DB_APPLY_REGION_INDEX_0 = 0x00,
    _D_DOMAIN_DB_APPLY_REGION_INDEX_1 = 0x01,
    _D_DOMAIN_DB_APPLY_REGION_INDEX_2 = 0x02,
    _D_DOMAIN_DB_APPLY_REGION_INDEX_3 = 0x03,
    _D_DOMAIN_DB_APPLY_REGION_EITHER = 0x0E,
    _D_DOMAIN_DB_APPLY_REGION_ALL = 0x0F,
} EnumDDomainDBApplyRegion;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern DWORD ScalerGlobalComputeDwordMulDiv(DWORD ulA, DWORD ulB, DWORD ulC);

