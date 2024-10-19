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
// ID Code      : RTD2020UserInterfacePower.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_POWER__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfacePower.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
bit g_bPowerForcePowSavStatus = _FALSE;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_PANEL_POWER_SEQUENCE_CONTROL_BY_USER == _ON)
//--------------------------------------------------
// Description  : Power Power On/Off Sequence
// Input Value  : enumEvent --> _PANEL_ON
//                              _PANEL_OFF
//                              _BACKLIGHT_ON
//                              _BACKLIGHT_OFF
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerPanelAction(EnumPanelPowerSeq enumEvent)
{
    enumEvent = enumEvent;
}
#endif

//--------------------------------------------------
// Description  : Power Power Timer action handler
// Input Value  : ucAction --> _PANEL_POWER_OFF_STATE
//                              _WAITING_FOR_BACKLIGHT
//                              _READY_FOR_BACKLIGHT
//                              _BACKLIGHT_ON_ALREADY
//                              _PANEL_BACKLIGHT_OFF
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerPanelTimerEventHandler(BYTE ucAction)
{
    SET_PANELPOWERSTATUS(ucAction);
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerPanelWaitT1(void)
{
    UserCommonTimerDelayXms(_PANEL_POWER_ON_T1);
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerPanelWaitT2(void)
{
#if(_PANEL_STYLE == _PANEL_LVDS)

    UserCommonTimerDelayXms(_PANEL_POWER_ON_T2);

#elif(_PANEL_STYLE == _PANEL_VBO)

    UserCommonDisplayTxVboPollingHotPlug(_PANEL_POWER_ON_T2);

#elif(_PANEL_STYLE == _PANEL_DPTX)

    UserCommonDisplayTxDpTxPollingHotPlug(_PANEL_POWER_ON_T2);

#endif
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerPanelWaitT3(void)
{
    UserCommonTimerDelayXms(_PANEL_POWER_ON_T3);
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T4
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerPanelWaitT4(void)
{
    UserCommonTimerDelayXms(_PANEL_POWER_OFF_T4);
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T5
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerPanelWaitT5(void)
{
    UserCommonTimerDelayXms(_PANEL_POWER_OFF_T5);
}

//--------------------------------------------------
// Description  : User Power Switch
// Input Value  : ucSwitch --> Power Action
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerSwitch(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            // Update LED Status
            RTDKeyPadLedControl(_LED_POWER_ON);

            UserCommonOsdResetToDefaultValue();
            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            // Update LED Status
            RTDKeyPadLedControl(_LED_POWER_ON);

            // Set Monitor Power On Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _ON);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;


        case _POWER_ACTION_AC_ON_TO_OFF:

            // Update LED Status
            RTDKeyPadLedControl(_LED_POWER_OFF);

            // Panel pown down.
            UserCommonPowerPanelAction(_PANEL_OFF);

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:

            // Update LED Status
            RTDKeyPadLedControl(_LED_POWER_OFF);

            // Panel pown down.
            UserCommonPowerPanelAction(_PANEL_OFF);

            // Set Monitor Power Off Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _OFF);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;

        case _POWER_ACTION_PS_TO_OFF:

            // Update LED Status
            RTDKeyPadLedControl(_LED_POWER_OFF);

            // Set Monitor Power Off Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _OFF);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

            // Update LED Status
            RTDKeyPadLedControl(_LED_POWER_SAVING);

            UserCommonModeResetProc();

            // Panel pown down.
            UserCommonPowerPanelAction(_PANEL_OFF);

            break;

        default:

            break;
    }

#if((_GOSD_SUPPORT == _ON) && (_IS_MAIN_PROCESS_CPU == _TRUE))
    UserCommonGosdContinuousReset(_GOSD_PLANE_ALL);
#endif // #if((_GOSD_SUPPORT == _ON) && (_IS_MAIN_PROCESS_CPU == _TRUE))
#if(_INSTANT_TIMER_EVENT_0 == _ON)
    UserCommonTimer0SetTimerCount(_TIMER_OFF);
#endif
}

//--------------------------------------------------
// Description  : User Power AC On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerAcOnInitial(void)
{
    PCB_PWM_SETTING();
    RTDNVRamStartup();

    UserCommonDdcciSwitchPort(UserAdjustDdcciGetStatus());
    UserCommonDdcciMapping();
    RTDKeyInitial();
    SET_PANELPOWERSTATUS(_PANEL_POWER_OFF_STATE);

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _OFF)
    // Adjust Backlight
    UserAdjustBacklight(GET_OSD_BACKLIGHT());
#endif

    // Adjust IR Decode
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    UserAdjustIR();
#endif

    SET_OSD_DOUBLE_SIZE(_OFF);
    if((_PANEL_DH_WIDTH >= 3840) && (_PANEL_DV_HEIGHT >= 2160))
    {
        SET_OSD_DOUBLE_SIZE(_ON);
    }

#if(_USB3_REPEATER_SUPPORT == _ON)
    // Initilize PSPD USB Function marco
    SET_OSD_D0_USB3_RETIMER_PD_WAKEUP(_TRUE);
    SET_OSD_D0_USB3_RETIMER_PS_WAKEUP(_TRUE);
    SET_OSD_D1_USB3_RETIMER_PD_WAKEUP(_TRUE);
    SET_OSD_D1_USB3_RETIMER_PS_WAKEUP(_TRUE);
    SET_OSD_D2_USB3_RETIMER_PD_WAKEUP(_TRUE);
    SET_OSD_D2_USB3_RETIMER_PS_WAKEUP(_TRUE);
#endif

#if(_ASSERT_SUPPORT == _ON)
#if(_PANEL_EXIST_MULTIPANEL == _ON)
    {
        BYTE ucPanelIndexBackup = g_ucDDomainPanelIndex;
        BYTE ucIndex = 0;

        // Check multi-panel parameters
        for(; ucIndex < _PANEL_AMOUNT; ++ucIndex)
        {
            SET_MDOMAIN_PANEL_INDEX(ucIndex);
            SysDebugCheckPanelParameter();
        }

        g_ucDDomainPanelIndex = ucPanelIndexBackup;
    }
#endif
#endif

#if(_HDMI_SUPPORT == _ON)
    UserCommonTmdsSetHdmiZ0HpdType(_HDMI_HPD_Z0_TOGGLE_AT_SAME_TIME, 0, 0);
#endif

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
    SET_OSD_FW_UPDATE_COUNT(0);
    SET_OSD_FW_UPDATE_NOW(_OFF);
#endif
}

//--------------------------------------------------
// Description  : OSD Power On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerOnInitial(void)
{
    // Adjust Color Palette
    UserCommonOsdMapABFunctionEnable(_OSD_A, _ENABLE);

#if(_GOSD_SUPPORT == _ON)
    // Adjust Gosd Display Sharpness
    GosdFuncDisplaySharpnessSetting(_GOSD_PLANE_ALL, 1, _DB_APPLY_NO_POLLING);
#endif
}

//--------------------------------------------------
// Description  : Get Forced Power Saving Status
// Input Value  : None
// Output Value : _FORCE_TO_PS_TRUE --> User force to PS
//                _FORCE_TO_PS_FALSE --> User not force to PS
//--------------------------------------------------
EnumForcePSStatus UserInterfacePowerGetForcePSStatus(void)
{
    if(GET_FORCE_POW_SAV_STATUS() == _TRUE)
    {
        return _FORCE_TO_PS_TRUE;
    }
    else
    {
        return _FORCE_TO_PS_FALSE;
    }
}

//--------------------------------------------------
// Description  : User Check Into Power Saving
// Input Value  : None
// Output Value : _PS_PERMISSION_TRUE --> User Check Ready to Power Saving
//                _PS_PERMISSION_FALSE --> User Check Not Ready to Power Saving
//--------------------------------------------------
EnumPSPermissionStatus UserInterfacePowerGetIntoPSStatus(void)
{
    if(UserCommonOsdGetOsdEnable() == _TRUE)
    {
        return _PS_PERMISSION_FALSE;
    }

    return _PS_PERMISSION_TRUE;
}

//--------------------------------------------------
// Description  : User Setting Fake Power Saving
// Input Value  : None
// Output Value : _FORCE_FAKE_PS --> User Set Power Status into Fake Power Saving
//                _FORCE_POWER_SAVING --> User Set Power Status into Power saving
//--------------------------------------------------
EnumForceFakePS UserInterfacePowerGetFakePSStatus(void)
{
    return _FORCE_POWER_SAVING;
}

//--------------------------------------------------
// Description  : User Setting Fake Power Status
// Input Value  : None
// Output Value : _FORCE_FAKE_POWER_OFF ==> Fake Power Off
//                _FORCE_POWER_OFF ==> Power off
//--------------------------------------------------
EnumForceFakePowerOff UserInterfacePowerGetFakeOffStatus(void)
{
    return _FORCE_POWER_OFF;
}

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
