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
// ID Code      : RTD2020UserInterfaceColorGlobalDimming.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_GLOBALDIMMING__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceColorGlobalDimming.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Adjust PWM in Global Dimming Mode
// Input Value  : PWM Value 0~ 2048
// Output Value : None
//--------------------------------------------------
void UserInterfaceColorGlobalDimmingAdjustPWM(WORD usPWMValue)
{
    WORD usNormPWM = 0;
#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
    {
        usNormPWM = ((DWORD)(usPWMValue) * (_DEVICE_LED_DRIVER_PWM_MAX)) / _GLOBAL_DIMMING_PANEL_PWM_MAX;
#if((_SPI_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))
        UserCommonSpiDimmingSetPwmValueToAllZone(usNormPWM);
        UserCommonSpiDimmingManualApplyUpdateSync();
#endif
    }
#else
    {
        usNormPWM = ((DWORD)usPWMValue * _BACKLIGHT_MAX) / _GLOBAL_DIMMING_PANEL_PWM_MAX;
        PCB_BACKLIGHT_PWM(usNormPWM);
    }
#endif
}

#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_NONE)
//--------------------------------------------------
// Description  : MaxPWM in Global Dimming Mode
// Input Value  : None
// Output Value : MaxPWM
//--------------------------------------------------
WORD UserInterfaceColorGlobalDimmingGetMaxPWM(void)
{
    return _BACKLIGHT_MAX;
}

//--------------------------------------------------
// Description  : MinPWM in Global Dimming Mode
// Input Value  : None
// Output Value : MaxPWM
//--------------------------------------------------
WORD UserInterfaceColorGlobalDimmingGetMinPWM(void)
{
    return _BACKLIGHT_MIN;
}
#endif

//--------------------------------------------------
// Description  : Get Global dimming OSD status
// Input Value  : None
// Output Value : MaxPWM
//--------------------------------------------------
EnumGlobalDimmingStatus UserInterfaceColorGlobalDimmingGetEnableStatus(void)
{
    if(GET_OSD_GLOBAL_DIMMING() != _ON)
    {
        return _GLOBAL_DIMMING_DISABLE;
    }

#if(_SDR_TO_HDR_FUNCTION == _ON)
    // SDRtoHDR can support local dimming
    if(GET_OSD_SDR_TO_HDR(GET_OSD_SELECT_REGION()) == _ON)
    {
        return _GLOBAL_DIMMING_DISABLE;
    }
#endif

    return _GLOBAL_DIMMING_ENABLE;
}

//--------------------------------------------------
// Description  : Restore backlight
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void UserInterfaceColorGlobalDimmingRestoreBacklight(void)
{
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonColorHDRGetHDR10Status(_DISPLAY_RGN_1P) != _HDR10_OFF)
    {
#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
        if(UserCommonColorHDRGetBackLightAdaptiveTMBackLightStatus() == _HDR10_BACKLIGHT_ADAPTIVE_TM_BACKLIGHT_MAX)
#endif
        {
            UserAdjustBacklight(_BACKLIGHT_MAX);
            return;
        }
    }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if(UserCommonColorHDRGetFreesynIIStatus(_DISPLAY_RGN_1P) == _ON)
    {
        UserAdjustBacklight(_BACKLIGHT_MAX);
        return;
    }
#endif
    UserAdjustBacklight(GET_OSD_BACKLIGHT());
}

//--------------------------------------------------
// Description  : Get sub force main parameter
// Input Value  : NONE
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumGlobalDimmingSubStatus UserInterfaceColorGlobalDimmingGetForceMainEffect(void)
{
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        return _GLOBAL_DIMMING_SUB_FORCE_MAIN;
    }
    else
#endif
    {
        return _GLOBAL_DIMMING_SUB_USER;
    }
}
#endif // End of #if(_GLOBAL_DIMMING_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

