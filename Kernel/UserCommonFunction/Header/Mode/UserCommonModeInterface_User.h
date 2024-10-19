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
// ID Code      : UserCommonModeInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// MACRO for OSD Fail Safe Mode
//--------------------------------------------------
#define GET_FAIL_SAFE_MODE(index)                       (g_pstModetRegionUserInfo[(index) % _MULTI_DISPLAY_MAX].b1FailSafeMode)
#define SET_FAIL_SAFE_MODE(index, x)                    (g_pstModetRegionUserInfo[(index) % _MULTI_DISPLAY_MAX].b1FailSafeMode = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of User No Support Status
//--------------------------------------------------
typedef enum
{
    _NO_SUPPORT_FALSE = _FALSE,
    _NO_SUPPORT_TRUE = _TRUE,
} EnumNoSupportStatus;

typedef struct
{
    BYTE b1FailSafeMode : 1;
} StructRegionUserInfoType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructRegionUserInfoType g_pstModetRegionUserInfo[_MULTI_DISPLAY_MAX];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonModeResetProc(void);

#if(_FRC_SUPPORT == _ON)
extern bit UserCommonModeGetImgCmpStatus(EnumDisplayRegion enumDisplayRegion);
#endif
