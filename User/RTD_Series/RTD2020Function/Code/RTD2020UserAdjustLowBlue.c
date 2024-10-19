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
// ID Code      : RTD2020UserAdjustLowBlue.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST_LOWBLUE__

#include "RTD2020UserInclude.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)
#if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : User Get Low Blue Panel Data
// Input Value  : StructColorEyeProtectSetting
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorLowBlueGetData(StructColorEyeProtectSetting *pstColorEyeProtectSetting)
{
    // Get osd data and user table ( low blue type and level from user)
    pstColorEyeProtectSetting->enumDynamicLowBlueType = GET_OSD_EYEPROTECT_LOWBLUE();
    pstColorEyeProtectSetting->stColorLowBlueUserSetting.enumEyeProtectLevel = GET_OSD_EYEPROTECT_LOWBLUE_LEVEL();
    pstColorEyeProtectSetting->stColorLowBlueUserSetting.pucParaSetting = UserAdjustGetLowBlueUserParaAddress();
    pstColorEyeProtectSetting->stColorLowBlueUserSetting.pucBlurMatrix = UserAdjustGetLowBlueMatrixAddress(GET_OSD_EYEPROTECT_LOWBLUE_LEVEL());
    pstColorEyeProtectSetting->stColorLowBlueUserSetting.ucBank = UserAdjustGetLowBlueTableBank();

    // user set start time or wait time to start
    if(GET_OSD_EYEPROTECT_NIGHTMODE_TIME() != _EYEPROTECT_TIME_OFF)
    {
        pstColorEyeProtectSetting->stColorLowBlueUserSetting.bNightModeEnable = _ON;
        // '30' is the user set transition time
        pstColorEyeProtectSetting->stColorLowBlueUserSetting.ucNightModeGainPercent = (WORD)(100 * GET_OSD_EYEPROTECT_TIME_MIN_COUNT()) / 30;
        // '30' is the user set transition time
        if(GET_OSD_EYEPROTECT_TIME_MIN_COUNT() >= 30)
        {
            DebugMessageSystem("Night Mode done...", pstColorEyeProtectSetting->stColorLowBlueUserSetting.ucNightModeGainPercent);
            pstColorEyeProtectSetting->stColorLowBlueUserSetting.bNightModeEnable = _OFF;
        }
        else
        {
            UserCommonTimerReactiveTimerEvent(SEC(1), _USER_TIMER_EVENT_EYE_PROTECT_TIMEOUT);
        }
    }
    else
    {
        pstColorEyeProtectSetting->stColorLowBlueUserSetting.bNightModeEnable = _OFF;
    }
}

//--------------------------------------------------
// Description  : User Get LowBlue Enable Status
// Input Value  : None
// Output Value : EnumDynamicLowBlueType
//--------------------------------------------------
EnumDynamicLowBlueType UserInterfaceColorLowBlueGetEnableStatus(void)
{
    if(GET_OSD_EYEPROTECT_LOWBLUE() == _LOWBLUE_MODE_OFF)
    {
        return _LOWBLUE_MODE_OFF;
    }
#if(_UNIFORMITY_FUNCTION == _ON)
    // Currently can't support uniformity and lowblue the same time
    if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
    {
        return _LOWBLUE_MODE_OFF;
    }
#endif
    return GET_OSD_EYEPROTECT_LOWBLUE();
}

//--------------------------------------------------
// Description  : Get Low Blue User Panel Para
// Input Value  : None
// Output Value :  Low Blue Blur Panel Para Table Data
//--------------------------------------------------
BYTE *UserAdjustGetLowBlueUserParaAddress(void)
{
    return tDynamicLowBluePara;
}

//--------------------------------------------------
// Description  : Get User Low Blue Blur Matrix Data
// Input Value  : None
// Output Value : Low Blue Blur Matrix Table Data
//--------------------------------------------------
BYTE *UserAdjustGetLowBlueMatrixAddress(EnumEyeProtectLevel enumEyeProtectLevel)
{
    if(enumEyeProtectLevel == _EYE_PROTECT_LEVEL3)
    {
        return tDynamicLowBlueMatrixSize121;
    }
    return tDynamicLowBlueMatrixSize81;
}

//--------------------------------------------------
// Description  : Get Low Blue Data Bank
// Input Value  : None
// Output Value : Low Blue User table bank
//--------------------------------------------------
BYTE UserAdjustGetLowBlueTableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}

#endif // End of #if(_DYNAMIC_LOWBLUE_FUNCTION == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
