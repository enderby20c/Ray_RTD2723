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
// ID Code      : RTD2020UserInterfaceUsbHub.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_USBHUB__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceUsbHub.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)
#if(_USB_HUB_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
EnumUsbHubOSDResult g_enumUsbHubUserOSDResult = _HUB_NONE_PORT;
EnumInputPort g_enumUsbHubSwitchInputPortIndex = _NO_INPUT_PORT;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User decided how many lanes to switch (Main Loop Polling)
// Input Value  : enumInputPort --> Input Port
//                ucUsbHubInfo:
//                _BIT0 : 1 --> Hub Port0 U3 Device Plug In,  0 --> Hub Port0 U3 Device Plug off
//                _BIT1 : 1 --> Hub Port1 U3 Device Plug In,  0 --> Hub Port1 U3 Device Plug off
//                _BIT2 : 1 --> Hub Port2 U3 Device Plug In,  0 --> Hub Port2 U3 Device Plug off
//                _BIT3 : 1 --> Hub Port3 U3 Device Plug In,  0 --> Hub Port3 U3 Device Plug off
//                _BIT4 ~ _BIT7 : Useless
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbHubDspChangeProc(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            // Here: User Can Use Kernel Extern Function to Get DSP Info
            break;

        case _D1_INPUT_PORT:
            // Here: User Can Use Kernel Extern Function to Get DSP Info
            break;

        case _D6_INPUT_PORT:
            // Here: User Can Use Kernel Extern Function to Get DSP Info
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Usb Hub RTS Series Control Mode Select (Main Loop Polling)
// Input Value  : enumInputPort --> Input Port
// Output Value : _USB_HUB_CTR_BY_USER: User Flow, _USB_HUB_CTR_BY_KERNAL: Kernal Flow
//--------------------------------------------------
EnumUsbHubCtrMode UserInterfaceUsbHubGetCtrlMode(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_USB_HUB_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return _USB_HUB_CTR_BY_KERNEL;

            break;
#endif

#if(_D1_USB_HUB_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return _USB_HUB_CTR_BY_KERNEL;

            break;
#endif

#if(_D2_USB_HUB_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return _USB_HUB_CTR_BY_KERNEL;

            break;
#endif

        default:
            break;
    }

    return _USB_HUB_CTR_BY_KERNEL;
}

//--------------------------------------------------
// Description  : Adjust Type-C Dp Lanes
// Input Value  : None
// Output Value : _USB_HUB_SET_U3_MODE_SUCCESS / _USB_HUB_SET_U3_MODE_FAIL
//--------------------------------------------------
EnumUsbHubSetU3ModeFailureType UserInterfaceUsbHubSetSSMode(EnumInputPort enumInputPort, bit bEn)
{
    enumInputPort = enumInputPort;
    bEn = bEn;

    return _USB_HUB_SET_U3_MODE_FAIL;
}

//--------------------------------------------------
// Description  : Get Hub Plug Info (Main Loop Polling)
// Input Value  : None
// Output Value : HUB Plug Status
//--------------------------------------------------
EnumHubDspDetectStatus UserInterfaceUsbHubGetDFPStatus(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    return _HUB_DSP_DEVICE_NO_CHANGE;
}

//--------------------------------------------------
// Description  : User Set Usb Hub Polling SS Device Step
// Input Value  : enumInputPort --> Input Port
// Output Value : Usb Hub Polling Step Par.
//--------------------------------------------------
WORD UserInterfaceUsbHubSetPollingStep(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;
    return 0;
}
#endif // End of #if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)

#if(_BILLBOARD_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hub Billboard Control
// Input Value  : _USB_BB_DISABLE / _USB_BB_ENABLE
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbHubBillboardControl(EnumInputPort enumInputPort, EnumBillboardCtrl enumAtion)
{
    enumAtion = enumAtion;

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            // Here: User Enable / Disable Hub Billboard
            break;

        case _D1_INPUT_PORT:
            // Here: User Enable / Disable Hub Billboard
            break;

        case _D6_INPUT_PORT:
            // Here: User Enable / Disable Hub Billboard
            break;

        default:
            break;
    }
}
//--------------------------------------------------
// Description  : Hub Billboard Handler (Main Loop Polling)
// Input Value  : enumInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbHubBillboardHandler(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            // Here: User Execute Hub BillboardHandler
            break;

        case _D1_INPUT_PORT:
            // Here: User Execute Hub BillboardHandler
            break;

        case _D6_INPUT_PORT:
            // Here: User Execute Hub BillboardHandler
            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get USB3 Hub Switch to which Port (D0/D1/TypeB) (Main Loop Polling)
// Input Value  : void
// Output Value : EnumUsbHubOSDResult
//--------------------------------------------------
EnumUsbHubOSDResult UserInterfaceUsbHubGetOSDSelectResult(void)
{
    // OSD Switch Set Previous Port (Initial Set to NONE)
    EnumUsbHubOSDResult enumUsbHubOSDResult = GET_USER_USB_HUB_OSD_SWITCH_PORT_RESULT();

    // Hub Switch OSD flow
    switch(GET_USER_USB_HUB_SWITCH_MODE())
    {
        // _OSD_HUB_AUTO will be determined by the first U3 attached Port searched by SysRegionGetInputPort
        case _OSD_HUB_AUTO:

            if(SysUsbHubGetCableAttachStatus(GET_USER_USB_HUB_OSD_SWITCH_PORT_RESULT()) == _FALSE)
            {
                if(SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_0)) != GET_USER_USB_HUB_SWITCH_TO_INPUT_INDEX())
                {
                    switch(SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_0)))
                    {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_USB_HUB_SUPPORT == _ON))
                        case _D0_INPUT_PORT:

                            if(SysUsbTypeCRxGetCcAttach(_D0_INPUT_PORT) == _TRUE)
                            {
                                enumUsbHubOSDResult = _HUB_D0_TYPE_C_PORT;

                                // Update Which Source Index Using USB Hub
                                SET_USER_USB_HUB_SWITCH_TO_INPUT_INDEX(SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_0)));
                            }

                            break;
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_USB_HUB_SUPPORT == _ON))
                        case _D1_INPUT_PORT:

                            if(SysUsbTypeCRxGetCcAttach(_D1_INPUT_PORT) == _TRUE)
                            {
                                enumUsbHubOSDResult = _HUB_D1_TYPE_C_PORT;

                                // Update Which Source Index Using USB Hub
                                SET_USER_USB_HUB_SWITCH_TO_INPUT_INDEX(SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_0)));
                            }

                            break;
#endif

                        default:

                            if(PCB_TYPE_B_VBUS_POWER_DETECT() == _TRUE)
                            {
                                enumUsbHubOSDResult = _HUB_TYPE_B_PORT;

                                // Update Which Source Index Using USB Hub
                                SET_USER_USB_HUB_SWITCH_TO_INPUT_INDEX(SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_0)));
                            }

                            break;
                    }
                }
            }

            break;

        case _OSD_HUB_D0:

            enumUsbHubOSDResult = _HUB_D0_TYPE_C_PORT;
            SET_USER_USB_HUB_SWITCH_TO_INPUT_INDEX(_D0_INPUT_PORT);

            break;

        case _OSD_HUB_D1:

            enumUsbHubOSDResult = _HUB_D1_TYPE_C_PORT;
            SET_USER_USB_HUB_SWITCH_TO_INPUT_INDEX(_D1_INPUT_PORT);

            break;

        case _OSD_HUB_TYPEB:

            enumUsbHubOSDResult = _HUB_TYPE_B_PORT;
            SET_USER_USB_HUB_SWITCH_TO_INPUT_INDEX(_NO_INPUT_PORT);

            break;

        default:

            break;
    }

    // Update OSD Hub Switch Result
    SET_USER_USB_HUB_OSD_SWITCH_PORT_RESULT(enumUsbHubOSDResult);

    return enumUsbHubOSDResult;
}

//--------------------------------------------------
// Description  : Control Hub BPWR when Hub switch to TypeB (Main Loop Polling)
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserInterfaceUsbHubTypeBProcess(void)
{
    // Resever For User
}

//--------------------------------------------------
// Description  : Control Hub BPWR when Hub switch to Dx Port
// Input Value  : enumInputPort , bEnable
// Output Value : void
//--------------------------------------------------
void UserInterfaceUsbHubPowerControl(EnumInputPort enumInputPort, bit bEnable)
{
    // Reserve EnumInputPort for User
    enumInputPort = enumInputPort;

    if(bEnable == _ENABLE)
    {
        PCB_HUB_0_BPWR_POWER(_VBUS_0_POWER_ON);
    }
    else
    {
        PCB_HUB_0_BPWR_POWER(_VBUS_0_POWER_OFF);
    }
}

//--------------------------------------------------
// Description  : Setting Hub Disable Duration Time
// Input Value  : void
// Output Value : WORD : Unit in 1ms, range in 0.01 ~ 61 sec
//--------------------------------------------------
WORD UserInterfaceUsbHubDisableDurationTime(void)
{
    // Disable Hub BPWR Duration
    // The Duration Time is recommended to be at least 10 ms
    return 10;
}

//--------------------------------------------------
// Description  : Setting Hub Enable Condition (Main Loop Polling)
// Input Value  : EnumInputPort
// Output Value : BYTE
//--------------------------------------------------
BYTE UserInterfaceUsbHubPathEnableCond(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
        case _D0_INPUT_PORT:

            if(SysUsbTypeCGetDataRole(_D0_TYPE_C_PORT) == _TYPE_C_UFP_U)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;
#endif

#if(_D1_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
        case _D1_INPUT_PORT:

            if(SysUsbTypeCGetDataRole(_D1_TYPE_C_PORT) == _TYPE_C_UFP_U)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;
#endif

#if(_D2_TYPE_C_PORT_CTRL_TYPE != _PORT_CTRL_NONE)
        case _D2_INPUT_PORT:

            if(SysUsbTypeCGetDataRole(_D2_TYPE_C_PORT) == _TYPE_C_UFP_U)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;
#endif

        default:

            break;
    }

    return _TRUE;
}

#if(_USB3_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get USB3 PD Support Status
// Input Value  : void
// Output Value : EnumUSBPDSupportStatus
//--------------------------------------------------
EnumUSBPDSupportStatus UserInterfaceUsbHubGetUSBPDSupportStatus(EnumInputPort enumInputPort)
{
    EnumUSBPDSupportStatus enumUSBPDSupportStatus = _PD_USB3_ENABLE;

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:

            if(GET_OSD_D0_USB3_RETIMER_PD_WAKEUP() == _TRUE)
            {
                enumUSBPDSupportStatus = _PD_USB3_ENABLE;
            }
            else
            {
                enumUSBPDSupportStatus = _PD_USB_DISABLE;
            }

            break;

        case _D1_INPUT_PORT:

            if(GET_OSD_D1_USB3_RETIMER_PD_WAKEUP() == _TRUE)
            {
                enumUSBPDSupportStatus = _PD_USB3_ENABLE;
            }
            else
            {
                enumUSBPDSupportStatus = _PD_USB_DISABLE;
            }

            break;

        case _D2_INPUT_PORT:

            if(GET_OSD_D2_USB3_RETIMER_PD_WAKEUP() == _TRUE)
            {
                enumUSBPDSupportStatus = _PD_USB3_ENABLE;
            }
            else
            {
                enumUSBPDSupportStatus = _PD_USB_DISABLE;
            }

            break;

        default:
            break;
    }

    return enumUSBPDSupportStatus;
}

//--------------------------------------------------
// Description  : Get USB3 PS Support Status
// Input Value  : void
// Output Value : EnumUSBPSSupportStatus
//--------------------------------------------------
EnumUSBPSSupportStatus UserInterfaceUsbHubGetUSBPSSupportStatus(EnumInputPort enumInputPort)
{
    EnumUSBPSSupportStatus enumUSBPSSupportStatus = _PS_USB3_ENABLE;

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:

            if(GET_OSD_D0_USB3_RETIMER_PS_WAKEUP() == _TRUE)
            {
                enumUSBPSSupportStatus = _PS_USB3_ENABLE;
            }
            else
            {
                enumUSBPSSupportStatus = _PS_USB_DISABLE;
            }

            break;

        case _D1_INPUT_PORT:

            if(GET_OSD_D1_USB3_RETIMER_PS_WAKEUP() == _TRUE)
            {
                enumUSBPSSupportStatus = _PS_USB3_ENABLE;
            }
            else
            {
                enumUSBPSSupportStatus = _PS_USB_DISABLE;
            }

            break;

        case _D2_INPUT_PORT:

            if(GET_OSD_D2_USB3_RETIMER_PS_WAKEUP() == _TRUE)
            {
                enumUSBPSSupportStatus = _PS_USB3_ENABLE;
            }
            else
            {
                enumUSBPSSupportStatus = _PS_USB_DISABLE;
            }

            break;

        default:
            break;
    }

    return enumUSBPSSupportStatus;
}
#endif // End of #if(_USB3_REPEATER_SUPPORT == _ON)
#endif // End of #if(_USB_HUB_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
