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
// ID Code      : ScalerTconInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _TCON1_GATED_BY_PWM = _TCON1,
    _TCON2_GATED_BY_PWM = _TCON2,
    _TCON3_GATED_BY_PWM = _TCON3,
    _TCON4_GATED_BY_PWM = _TCON4,
    _TCON6_GATED_BY_PWM = _TCON6,
    _TCON8_GATED_BY_PWM = _TCON8,
    _TCON10_GATED_BY_PWM = _TCON10,
    _TCON12_GATED_BY_PWM = _TCON12,
}EnumTconGatedByPwmSet;

typedef enum
{
    _TCON3_LOGICAL_OP = _TCON3,
    _TCON4_LOGICAL_OP = _TCON4,
    _TCON5_LOGICAL_OP = _TCON5,
    _TCON6_LOGICAL_OP = _TCON6,
    _TCON7_LOGICAL_OP = _TCON7,
    _TCON8_LOGICAL_OP = _TCON8,
    _TCON9_LOGICAL_OP = _TCON9,
    _TCON10_LOGICAL_OP = _TCON10,
    _TCON11_LOGICAL_OP = _TCON11,
    _TCON12_LOGICAL_OP = _TCON12,
    _TCON13_LOGICAL_OP = _TCON13,
} EnumTconLogicalOpSet;

typedef enum
{
    _TCON_LOGICAL_OP_AND,
    _TCON_LOGICAL_OP_OR,
    _TCON_LOGICAL_OP_XOR,
    _TCON_TOGGLE_OP_NORMAL,
    _TCON_TOGGLE_OP_AND,
    _TCON_TOGGLE_OP_OR,
} EnumTconLogicalOp;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


