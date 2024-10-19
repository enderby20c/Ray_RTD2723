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
// ID Code      : UserCommonUsbHub.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_USBHUBCOMMON__

#include "UserCommonInclude.h"
#include "UsbHub/UserCommonUsbHub.h"

#if(_USB_HUB_SUPPORT == _ON)
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
// Description  : User Decide Hub Switch to which Port (D0/D1/TypeB)
// Input Value  : void
// Output Value : EnumUsbHubOSDResult
//--------------------------------------------------
EnumUsbHubOSDResult UserCommonUsbHubGetOSDSelectResult(void)
{
    // Get USB Hub Switch Information From OSD
    return UserInterfaceUsbHubGetOSDSelectResult();
}

//--------------------------------------------------
// Description  : Control Hub BPWR
// Input Value  : enumTypeCPcbPort , bEn
// Output Value : None
//--------------------------------------------------
void UserCommonUsbHubPowerControl(EnumTypeCPcbPort enumTypeCPcbPort, bit bEnable)
{
    bEnable = bEnable;
    // Control Hub Power(BPWR)
    // Reserve EnumTypeCPcbPort for User
    switch(enumTypeCPcbPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            if(bEnable == _ENABLE)
            {
                if(GET_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG() == _TRUE)
                {
                    UserInterfaceUsbHubPowerControl(_D0_INPUT_PORT, _ENABLE);
                }
            }
            else
            {
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
                if((PCB_HUB_BPWR_0_POWER_DETECT() == _VBUS_0_POWER_ON) && (g_bUsbBillboardIspProcessing != _TRUE))
#else
                if(PCB_HUB_BPWR_0_POWER_DETECT() == _VBUS_0_POWER_ON)
#endif
                {
                    UserInterfaceUsbHubPowerControl(_D0_INPUT_PORT, _DISABLE);
                    CLR_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG();
                    SysUsbHubActiveHubDisableDurationTimerEvent(UserCommonUsbHubDisableDurationTime());
                }
            }

            break;
#endif

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:

            if(bEnable == _ENABLE)
            {
                if(GET_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG() == _TRUE)
                {
                    UserInterfaceUsbHubPowerControl(_D1_INPUT_PORT, _ENABLE);
                }
            }
            else
            {
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
                if((PCB_HUB_BPWR_0_POWER_DETECT() == _VBUS_0_POWER_ON) && (g_bUsbBillboardIspProcessing != _TRUE))
#else
                if(PCB_HUB_BPWR_0_POWER_DETECT() == _VBUS_0_POWER_ON)
#endif
                {
                    UserInterfaceUsbHubPowerControl(_D1_INPUT_PORT, _DISABLE);
                    CLR_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG();
                    SysUsbHubActiveHubDisableDurationTimerEvent(UserCommonUsbHubDisableDurationTime());
                }
            }

            break;
#endif

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

            if(bEnable == _ENABLE)
            {
                if(GET_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG() == _TRUE)
                {
                    UserInterfaceUsbHubPowerControl(_D2_INPUT_PORT, _ENABLE);
                }
            }
            else
            {
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
                if((PCB_HUB_BPWR_0_POWER_DETECT() == _VBUS_0_POWER_ON) && (g_bUsbBillboardIspProcessing != _TRUE))
#else
                if(PCB_HUB_BPWR_0_POWER_DETECT() == _VBUS_0_POWER_ON)
#endif
                {
                    UserInterfaceUsbHubPowerControl(_D2_INPUT_PORT, _DISABLE);
                    CLR_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG();
                    SysUsbHubActiveHubDisableDurationTimerEvent(UserCommonUsbHubDisableDurationTime());
                }
            }

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Control Hub Switch GPIO
// Input Value  : enumTypeCPcbPort , enumUSBHubPathEnable
// Output Value : None
//--------------------------------------------------
void UserCommonUsbHubSwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumUSBHubPathEnable enumUSBHubPathEnable)
{
    enumUSBHubPathEnable = enumUSBHubPathEnable;
    switch(enumTypeCPcbPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

#if((_USB3_REPEATER_MAC_SUPPORT == _ON) && (_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON))
            ScalerUsb3RepeaterMacMuxSwitchControl(_D0_INPUT_PORT, enumUSBHubPathEnable);
#endif // End of #if((_USB3_REPEATER_MAC_SUPPORT == _ON) && (_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON))
#if(_HW_USB2_EMB_MUX_SUPPORT == _ON)
            ScalerUsb2MuxSwitchControl(_D0_INPUT_PORT, enumUSBHubPathEnable);
#endif

            if(enumUSBHubPathEnable == _USB_PATH_ENABLE)
            {
                PCB_U2_MUX_SWITCH_CONTROL(_HUB_D0_TYPE_C_PORT);
                PCB_U3_MUX_SWITCH_CONTROL(_HUB_D0_TYPE_C_PORT);
            }
            else
            {
                PCB_U2_MUX_SWITCH_CONTROL(_HUB_NONE_PORT);
                PCB_U3_MUX_SWITCH_CONTROL(_HUB_NONE_PORT);
            }

            break;
#endif

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:


#if((_USB3_REPEATER_MAC_SUPPORT == _ON) && (_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON))
            ScalerUsb3RepeaterMacMuxSwitchControl(_D1_INPUT_PORT, enumUSBHubPathEnable);
#endif // End of #if((_USB3_REPEATER_MAC_SUPPORT == _ON) && (_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON))
#if(_HW_USB2_EMB_MUX_SUPPORT == _ON)
            ScalerUsb2MuxSwitchControl(_D1_INPUT_PORT, enumUSBHubPathEnable);
#endif

            if(enumUSBHubPathEnable == _USB_PATH_ENABLE)
            {
                PCB_U2_MUX_SWITCH_CONTROL(_HUB_D1_TYPE_C_PORT);
                PCB_U3_MUX_SWITCH_CONTROL(_HUB_D1_TYPE_C_PORT);
            }
            else
            {
                PCB_U2_MUX_SWITCH_CONTROL(_HUB_NONE_PORT);
                PCB_U3_MUX_SWITCH_CONTROL(_HUB_NONE_PORT);
            }

            break;
#endif

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

#if((_USB3_REPEATER_MAC_SUPPORT == _ON) && (_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON))
            ScalerUsb3RepeaterMacMuxSwitchControl(_D2_INPUT_PORT, enumUSBHubPathEnable);
#endif // End of #if((_USB3_REPEATER_MAC_SUPPORT == _ON) && (_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON))
#if(_HW_USB2_EMB_MUX_SUPPORT == _ON)
            ScalerUsb2MuxSwitchControl(_D2_INPUT_PORT, enumUSBHubPathEnable);
#endif

            if(enumUSBHubPathEnable == _USB_PATH_ENABLE)
            {
                PCB_U2_MUX_SWITCH_CONTROL(_HUB_D2_TYPE_C_PORT);
                PCB_U3_MUX_SWITCH_CONTROL(_HUB_D2_TYPE_C_PORT);
            }
            else
            {
                PCB_U2_MUX_SWITCH_CONTROL(_HUB_NONE_PORT);
                PCB_U3_MUX_SWITCH_CONTROL(_HUB_NONE_PORT);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Process Hub Switch to TypeB case
// Input Value  : void
// Output Value : None
//--------------------------------------------------
void UserCommonUsbHubTypeBProcess(void)
{
    if((PCB_TYPE_B_VBUS_POWER_DETECT() == _TRUE) && (GET_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG() == _TRUE))
    {
        // Turn On Hub BPWR
        PCB_HUB_0_BPWR_POWER(_VBUS_0_POWER_ON);
    }
    else
    {
        if(PCB_HUB_BPWR_0_POWER_DETECT() == _VBUS_0_POWER_ON)
        {
            // Turn Off Hub BPWR
            PCB_HUB_0_BPWR_POWER(_VBUS_0_POWER_OFF);
            CLR_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG();
            SysUsbHubActiveHubDisableDurationTimerEvent(UserCommonUsbHubDisableDurationTime());
        }
    }

    UserInterfaceUsbHubTypeBProcess();
}

//--------------------------------------------------
// Description  : Get USB3 Hub Disable Duration Time
// Input Value  : void
// Output Value : WORD
//--------------------------------------------------
WORD UserCommonUsbHubDisableDurationTime(void)
{
    return UserInterfaceUsbHubDisableDurationTime();
}

//--------------------------------------------------
// Description  : Get USB Hub Enable Condition
// Input Value  : EnumTypeCPcbPort
// Output Value : BYTE
//--------------------------------------------------
BYTE UserCommonUsbHubPathEnableCond(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            if(UserInterfaceUsbHubPathEnableCond(_D0_INPUT_PORT) == _FALSE)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }

            break;
#endif

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:

            if(UserInterfaceUsbHubPathEnableCond(_D1_INPUT_PORT) == _FALSE)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }

            break;
#endif

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

            if(UserInterfaceUsbHubPathEnableCond(_D1_INPUT_PORT) == _FALSE)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }

            break;
#endif

        default:

            return _FALSE;

            break;
    }

    return _FALSE;
}

#if(_USB3_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get USB3 PD Support Status
// Input Value  : EnumTypeCPcbPort
// Output Value : EnumUSBPDSupportStatus
//--------------------------------------------------
EnumUSBPDSupportStatus UserCommonUsbHubGetUSBPDSupportStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumUSBPDSupportStatus enumUSBPDSupportStatus = _PD_USB_DISABLE;

    switch(enumTypeCPcbPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            enumUSBPDSupportStatus = UserInterfaceUsbHubGetUSBPDSupportStatus(_D0_INPUT_PORT);

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
            if((g_bUsbBillboardIspProcessing == _TRUE) && (enumUSBPDSupportStatus != _PD_USB_DISABLE))
            {
                return _PD_USB3_ENABLE;
            }
            else
            {
                return enumUSBPDSupportStatus;
            }
#else
            return enumUSBPDSupportStatus;
#endif
            break;
#endif

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:

            enumUSBPDSupportStatus = UserInterfaceUsbHubGetUSBPDSupportStatus(_D1_INPUT_PORT);

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
            if((g_bUsbBillboardIspProcessing == _TRUE) && (enumUSBPDSupportStatus != _PD_USB_DISABLE))
            {
                return _PD_USB3_ENABLE;
            }
            else
            {
                return enumUSBPDSupportStatus;
            }
#else
            return enumUSBPDSupportStatus;
#endif
            break;
#endif

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

            enumUSBPDSupportStatus = UserInterfaceUsbHubGetUSBPDSupportStatus(_D2_INPUT_PORT);

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
            if((g_bUsbBillboardIspProcessing == _TRUE) && (enumUSBPDSupportStatus != _PD_USB_DISABLE))
            {
                return _PD_USB3_ENABLE;
            }
            else
            {
                return enumUSBPDSupportStatus;
            }
#else
            return enumUSBPDSupportStatus;
#endif
            break;
#endif

        default:

            return _PD_USB_DISABLE;

            break;
    }

    return _PD_USB_DISABLE;
}

//--------------------------------------------------
// Description  : Get USB3 PS Support Status
// Input Value  : EnumTypeCPcbPort
// Output Value : EnumUSBPSSupportStatus
//--------------------------------------------------
EnumUSBPSSupportStatus UserCommonUsbHubGetUSBPSSupportStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumUSBPSSupportStatus enumUSBPSSupportStatus = _PS_USB_DISABLE;

    switch(enumTypeCPcbPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            enumUSBPSSupportStatus = UserInterfaceUsbHubGetUSBPSSupportStatus(_D0_INPUT_PORT);

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
            if((g_bUsbBillboardIspProcessing == _TRUE) && (enumUSBPSSupportStatus != _PS_USB_DISABLE))
            {
                return _PS_USB3_ENABLE;
            }
            else
            {
                return enumUSBPSSupportStatus;
            }
#else
            return enumUSBPSSupportStatus;
#endif
            break;
#endif

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:

            enumUSBPSSupportStatus = UserInterfaceUsbHubGetUSBPSSupportStatus(_D1_INPUT_PORT);

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
            if((g_bUsbBillboardIspProcessing == _TRUE) && (enumUSBPSSupportStatus != _PS_USB_DISABLE))
            {
                return _PS_USB3_ENABLE;
            }
            else
            {
                return enumUSBPSSupportStatus;
            }
#else
            return enumUSBPSSupportStatus;
#endif
            break;
#endif

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

            enumUSBPSSupportStatus = UserInterfaceUsbHubGetUSBPSSupportStatus(_D2_INPUT_PORT);

#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
            if((g_bUsbBillboardIspProcessing == _TRUE) && (enumUSBPSSupportStatus != _PS_USB_DISABLE))
            {
                return _PS_USB3_ENABLE;
            }
            else
            {
                return enumUSBPSSupportStatus;
            }
#else
            return enumUSBPSSupportStatus;
#endif
            break;
#endif

        default:

            return _PS_USB_DISABLE;

            break;
    }

    return _PS_USB_DISABLE;
}
#endif // End of #if(_USB3_REPEATER_SUPPORT == _ON)

#if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set User into SS Mode
// Input Value  : None
// Output Value : _USB_HUB_SET_U3_MODE_SUCCESS / _USB_HUB_SET_U3_MODE_FAIL
//--------------------------------------------------
EnumUsbHubSetU3ModeFailureType UserCommonUsbHubSetSSMode(EnumTypeCPcbPort enumTypeCPcbPort, bit bEn)
{
    EnumUsbHubSetU3ModeFailureType enumSetResult = _USB_HUB_SET_U3_MODE_FAIL;
    bEn = bEn;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

#if(_D0_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
            enumSetResult = UserCommonUsbHubRtsSetSSMode(_D0_TYPE_C_PORT, bEn);
#elif(_D0_USB_HUB_USER_SERIES_SUPPORT == _ON)
            enumSetResult = UserCommonUsbHubUserSetSSMode(_D0_TYPE_C_PORT, bEn);
#endif

            break;

        case _D1_TYPE_C_PORT:

#if(_D1_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
            enumSetResult = UserCommonUsbHubRtsSetSSMode(_D1_TYPE_C_PORT, bEn);
#elif(_D1_USB_HUB_USER_SERIES_SUPPORT == _ON)
            enumSetResult = UserCommonUsbHubUserSetSSMode(_D1_TYPE_C_PORT, bEn);
#endif

            break;

        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:
        default:

            break;
    }

    return enumSetResult;
}

//--------------------------------------------------
// Description  : Detect Hub DFP Status
// Input Value  : enumInputPort --> Input Port
// Output Value : Return DFP Status Change or Not
//--------------------------------------------------
EnumHubDspDetectStatus UserCommonUsbHubDetectDFPStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumHubDspDetectStatus enumDspDetStatus = _HUB_DSP_DEVICE_NO_CHANGE;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

#if(_D0_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
            enumDspDetStatus = UserCommonUsbHubRtsDetectDFPStatus(_D0_TYPE_C_PORT);
#elif(_D0_USB_HUB_USER_SERIES_SUPPORT == _ON)
            enumDspDetStatus = UserCommonUsbHubUserDetectDFPStatus(_D0_TYPE_C_PORT);
#endif

            break;

        case _D1_TYPE_C_PORT:

#if(_D1_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
            enumDspDetStatus = UserCommonUsbHubRtsDetectDFPStatus(_D1_TYPE_C_PORT);
#elif(_D1_USB_HUB_USER_SERIES_SUPPORT == _ON)
            enumDspDetStatus = UserCommonUsbHubUserDetectDFPStatus(_D1_TYPE_C_PORT);
#endif

            break;

        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:
        default:

            break;
    }

    return enumDspDetStatus;
}

//--------------------------------------------------
// Description  : User decided how many lanes to switch
// Input Value  : enumInputPort --> Input Port
//                ucUsbHubInfo:
//                _BIT0 : 1 --> Hub Port0 U3 Device Plug In,  0 --> Hub Port0 U3 Device Plug off
//                _BIT1 : 1 --> Hub Port1 U3 Device Plug In,  0 --> Hub Port1 U3 Device Plug off
//                _BIT2 : 1 --> Hub Port2 U3 Device Plug In,  0 --> Hub Port2 U3 Device Plug off
//                _BIT3 : 1 --> Hub Port3 U3 Device Plug In,  0 --> Hub Port3 U3 Device Plug off
//                _BIT4 ~ _BIT7 : Useless
// Output Value : None
//--------------------------------------------------
void UserCommonUsbHubDspChangeProc(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // User Can Use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create Draw Notice U3 Device Menu Event
    UserInterfaceUsbHubDspChangeProc(SysUsbTypeCConvertToDxPort(enumTypeCPcbPort));
}

//--------------------------------------------------
// Description  : Usb Hub RTS Series Control Mode Select
// Input Value  : enumInputPort --> Input Port
// Output Value : _USB_HUB_CTR_BY_USER: User Flow, _USB_HUB_CTR_BY_KERNAL: Kernal Flow
//--------------------------------------------------
EnumUsbHubCtrMode UserCommonUsbHubGetControlMode(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return UserInterfaceUsbHubGetCtrlMode(SysUsbTypeCConvertToDxPort(enumTypeCPcbPort));
}

//--------------------------------------------------
// Description  : Adjust Type-C Dp Lanes
// Input Value  : None
// Output Value : _USB_HUB_SET_U3_MODE_SUCCESS / _USB_HUB_SET_U3_MODE_FAIL
//--------------------------------------------------
EnumUsbHubSetU3ModeFailureType UserCommonUsbHubSetSSModeByUser(EnumTypeCPcbPort enumTypeCPcbPort, bit bEn)
{
    return UserInterfaceUsbHubSetSSMode(SysUsbTypeCConvertToDxPort(enumTypeCPcbPort), bEn);
}

//--------------------------------------------------
// Description  : Config Config Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumHubDspDetectStatus UserCommonUsbHubGetDFPStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return UserInterfaceUsbHubGetDFPStatus(SysUsbTypeCConvertToDxPort(enumTypeCPcbPort));
}

//--------------------------------------------------
// Description  : User Set Usb Hub Polling SS Device Step
// Input Value  : enumInputPort --> Input Port
// Output Value : Usb Hub Polling Step Par.
//--------------------------------------------------
WORD UserCommonUsbHubSetPollingStep(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return UserInterfaceUsbHubSetPollingStep(SysUsbTypeCConvertToDxPort(enumTypeCPcbPort));
}
#endif // End of #if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
#endif // End of #if(_USB_HUB_SUPPORT == _ON)
