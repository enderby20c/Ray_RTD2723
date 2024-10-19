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
// ID Code      : RTD2020UserInterfaceUsbTypeC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_USBTYPEC__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceUsbTypeC.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON) || (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))
StructUsbTypeCPowerOffInfo g_stUsbTypeCPowerOffInfo;
#endif

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
StructUsbTypeCLenovoDockEventQueue g_stUsbTypeCLenovoDockEventQueue;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
StructTypeCAcerUserEvent g_stUsbTypeCAcerUserEvent;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
StructTypeCHpUserEvent g_stUsbTypeCHpUserEvent;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
StructTypeCDellUserEvent g_stUsbTypeCDellUserEvent;
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Decide Type-C Pin Assignment E Support or Not
// Input Value  : enumInputPort
// Output Value : _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON / _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF
//--------------------------------------------------
EnumTypeCPinAssignmentESupportStatus UserInterfaceUsbTypeCGetOsdPinAssignmentESupportSelection(EnumInputPort enumInputPort)
{
    EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportStatus = _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON;
    enumInputPort = enumInputPort;

    switch(enumInputPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            enumPinAssignmentESupportStatus = GET_OSD_D0_TYPE_C_PIN_ASSIGNMENT_E_SELECT();

            break;
#endif

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            enumPinAssignmentESupportStatus = GET_OSD_D1_TYPE_C_PIN_ASSIGNMENT_E_SELECT();

            break;
#endif

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            enumPinAssignmentESupportStatus = GET_OSD_D2_TYPE_C_PIN_ASSIGNMENT_E_SELECT();

            break;
#endif

        default:
            break;
    }

    return enumPinAssignmentESupportStatus;
}
#endif  // End of #if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)

//--------------------------------------------------
// Description  : User Decide Sink Pin Config Type
// Input Value  : enumInputPort --> Input Port
//                enumU3ModeSel --> _TYPE_C_U3_ON / _TYPE_C_U3_OFF
//                enumPinAssignmentESupportSel --> _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON / _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF
// Output Value : Pin Config Capability Type
//--------------------------------------------------
EnumTypeCPinCfgCapType UserInterfaceUsbTypeCGetPinAssignmentConfig(EnumInputPort enumInputPort, EnumTypeCU3ModeType enumU3ModeSel, EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportSel)
{
    EnumTypeCPinCfgCapType enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_DEFAULT;
    enumU3ModeSel = enumU3ModeSel;
    enumPinAssignmentESupportSel = enumPinAssignmentESupportSel;

    switch(enumInputPort)
    {
#if(_D0_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+D+E if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    // Use Pin Assignment C+D if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+E if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    // Use Pin Assignment C if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }

            break;
#endif

#if(_D1_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+D+E if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    // Use Pin Assignment C+D if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+E if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    // Use Pin Assignment C if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }

            break;
#endif

#if(_D2_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+D+E if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    // Use Pin Assignment C+D if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+E if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    // Use Pin Assignment C if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }

            break;
#endif

        default:
            break;
    }

    return enumPinAssignmentConfig;
}

//--------------------------------------------------
// Description  : User Decide Multi Function Status
// Input Value  : enumInputPort --> Input Port
//                enumU3ModeSel --> _TYPE_C_U3_ON / _TYPE_C_U3_OFF
// Output Value : Multi Function Status
//--------------------------------------------------
EnumTypeCMultiFuncStatus UserInterfaceUsbTypeCGetMultiFuncConfig(EnumInputPort enumInputPort, EnumTypeCU3ModeType enumU3ModeSel)
{
    EnumTypeCMultiFuncStatus enumMultiFunc = _TYPE_C_MULTI_FUNC_DEFAULT;
    enumU3ModeSel = enumU3ModeSel;

    // ================================ NOTE =================================
    // For _TYPE_C_MULTI_FUNC_DEFAULT :
    // Kernel decides whether to Set Multi-Function Prefer according to Pin Assignment-D Exist or not
    // =======================================================================

    switch(enumInputPort)
    {
#if(_D0_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            enumMultiFunc = _TYPE_C_MULTI_FUNC_DEFAULT;

            break;
#endif

#if(_D1_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            enumMultiFunc = _TYPE_C_MULTI_FUNC_DEFAULT;

            break;
#endif

#if(_D2_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            enumMultiFunc = _TYPE_C_MULTI_FUNC_DEFAULT;

            break;
#endif

        default:
            break;
    }

    return enumMultiFunc;
}
#endif  // End of #if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)

#if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Decide Type-C Tx Pin Assignment E Support or Not
// Input Value  : enumOutputPort
// Output Value : _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON / _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF
//--------------------------------------------------
EnumTypeCPinAssignmentESupportStatus UserInterfaceUsbTypeCGetOsdTxPinAssignmentESupportSelection(EnumOutputPort enumOutputPort)
{
    EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportStatus = _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON;
    enumOutputPort = enumOutputPort;

    switch(enumOutputPort)
    {
#if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P0_OUTPUT_PORT:

            // For Kernel to Get OSD Tx Pin Assignment E Support or Not,
            // Example:
            // enumPinAssignmentESupportStatus = GET_OSD_P0_TYPE_C_PIN_ASSIGNMENT_E_SELECT();

            break;
#endif

#if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P1_OUTPUT_PORT:

            break;
#endif

#if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P2_OUTPUT_PORT:

            break;
#endif

#if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P3_OUTPUT_PORT:

            break;
#endif

#if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P4_OUTPUT_PORT:

            break;
#endif

        default:
            break;
    }

    return enumPinAssignmentESupportStatus;
}
#endif // End of #if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)

//--------------------------------------------------
// Description  : User Decide Tx Pin Config Type
// Input Value  : enumOutputPort --> Output Port
//                enumU3ModeSel --> _TYPE_C_U3_ON / _TYPE_C_U3_OFF
//                enumPinAssignmentESupportSel --> _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON / _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF
// Output Value : Pin Config Capability Type
//--------------------------------------------------
EnumTypeCPinCfgCapType UserInterfaceUsbTypeCGetTxPinAssignmentConfig(EnumOutputPort enumOutputPort, EnumTypeCU3ModeType enumU3ModeSel, EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportSel)
{
    EnumTypeCPinCfgCapType enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_DEFAULT;
    enumPinAssignmentESupportSel = enumPinAssignmentESupportSel;
    enumU3ModeSel = enumU3ModeSel;

    switch(enumOutputPort)
    {
#if(_P0_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _P0_OUTPUT_PORT:

            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+D+E if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    // Use Pin Assignment C+D if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+E if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    // Use Pin Assignment C if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }

            break;
#endif

#if(_P1_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _P1_OUTPUT_PORT:

            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+D+E if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    // Use Pin Assignment C+D if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+E if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    // Use Pin Assignment C if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }

            break;
#endif

#if(_P2_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _P2_OUTPUT_PORT:

            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+D+E if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    // Use Pin Assignment C+D if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+E if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    // Use Pin Assignment C if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }

            break;
#endif

#if(_P3_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _P3_OUTPUT_PORT:

            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+D+E if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    // Use Pin Assignment C+D if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+E if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    // Use Pin Assignment C if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }

            break;
#endif

#if(_P4_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _P4_OUTPUT_PORT:

            if(enumU3ModeSel == _TYPE_C_U3_ON)
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+D+E if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
                }
                else
                {
                    // Use Pin Assignment C+D if U3_ON and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
                }
            }
            else
            {
                if(enumPinAssignmentESupportSel == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
                {
                    // Use Pin Assignment C+E if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_ON
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
                }
                else
                {
                    // Use Pin Assignment C if U3_OFF and PIN_ASSIGNMENT_E_SUPPORT_OFF
                    enumPinAssignmentConfig = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
                }
            }

            break;
#endif

        default:
            break;
    }

    return enumPinAssignmentConfig;
}

//--------------------------------------------------
// Description  : User Decide Tx Multi Function Status
// Input Value  : enumOutputPort --> Output Port
//                enumU3ModeSel --> _TYPE_C_U3_ON / _TYPE_C_U3_OFF
// Output Value : Multi Function Status
//--------------------------------------------------
EnumTypeCMultiFuncStatus UserInterfaceUsbTypeCGetTxMultiFuncConfig(EnumOutputPort enumOutputPort, EnumTypeCU3ModeType enumU3ModeSel)
{
    EnumTypeCMultiFuncStatus enumMultiFunc = _TYPE_C_MULTI_FUNC_DEFAULT;
    enumU3ModeSel = enumU3ModeSel;

    // ================================ NOTE =================================
    // For _TYPE_C_MULTI_FUNC_DEFAULT :
    // Kernel decides whether to Set Multi-Function Prefer according to Pin Assignment-D Exist or not
    // =======================================================================

    switch(enumOutputPort)
    {
#if(_P0_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _P0_OUTPUT_PORT:

            enumMultiFunc = _TYPE_C_MULTI_FUNC_DEFAULT;

            break;
#endif

#if(_P1_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _P1_OUTPUT_PORT:

            enumMultiFunc = _TYPE_C_MULTI_FUNC_DEFAULT;

            break;
#endif

#if(_P2_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _P2_OUTPUT_PORT:

            enumMultiFunc = _TYPE_C_MULTI_FUNC_DEFAULT;

            break;
#endif

#if(_P3_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _P3_OUTPUT_PORT:

            enumMultiFunc = _TYPE_C_MULTI_FUNC_DEFAULT;

            break;
#endif

#if(_P4_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _P4_OUTPUT_PORT:

            enumMultiFunc = _TYPE_C_MULTI_FUNC_DEFAULT;

            break;
#endif

        default:
            break;
    }

    return enumMultiFunc;
}
#endif  // End of #if(_TYPE_C_PX_PORT_CTRL_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check User Action for Pin Assignment Mismatch
// Input Value  : enumTypeCPcbPort
// Output Value : return _TYPE_C_PIN_ASSIGNMENT_MISMATCH_NO_ACTION / _TYPE_C_PIN_ASSIGNMENT_MISMATCH_RECONNECT
//--------------------------------------------------
EnumTypeCPinMismatchAction UserInterfaceUsbTypeCGetPinAssignmentMismatchAction(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCPinMismatchAction enumMismatchAction = _TYPE_C_PIN_ASSIGNMENT_MISMATCH_RECONNECT;
    enumTypeCPcbPort = enumTypeCPcbPort;

    // =============================== WARNING ===============================
    // For _TYPE_C_PIN_ASSIGNMENT_MISMATCH_WAIT_CONFIG :
    // 1. Only Emebedded Port Controller Supports this Function
    // 2. When Select This Function, PD Controller Will Set Alt Mode Not Ready until Receiving New DP Config,
    // User Should Use Timer to Reconnect when No DP Config Message Received.
    // (Ex. ActiveTimerEvent(500ms, PD_Reconnect))
    // =======================================================================

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            enumMismatchAction = _TYPE_C_PIN_ASSIGNMENT_MISMATCH_RECONNECT;

            break;
#endif

        default:
            break;
    }

    return enumMismatchAction;
}

//--------------------------------------------------
// Description  : For User Updating Display Config When DP Alt Mode Ready Status Changes
// Input Value  : enumTypeCPcbPort, enumPinAssignment
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUpdateDisplayConfig(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPinAssignment = enumPinAssignment;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            // User Can Use Pin Assignment to Update EDID or Other Function When DP Alt Mode Ready Status Changes

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TypeC Get Dp Alt Mode Wait Status
// Input Value  : enumTypeCPcbPort
// Output Value : Dp Alt Mode Wait Status (_TYPE_C_ALT_MODE_WAIT / _TYPE_C_ALT_MODE_NOT_WAIT)
//--------------------------------------------------
EnumTypeCAltModeWaitStatus UserInterfaceUsbTypeCGetDpAltModeWaitStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCAltModeWaitStatus enumAltModeWait = _TYPE_C_ALT_MODE_NOT_WAIT;
    enumTypeCPcbPort = enumTypeCPcbPort;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
            // Requirements of HPD Handling during Dell Alt Mode
            if(((SysUsbTypeCGetDellAltModeReady(enumTypeCPcbPort) == _TYPE_C_DELL_ALT_MODE_READY) && (UserInterfaceUsbTypeCGetDellAltModeInitComplete(enumTypeCPcbPort) == _TYPE_C_DELL_INIT_COMPLETE)) ||
               (SysUsbTypeCGetEnterDellAltModeTimeOut(enumTypeCPcbPort) == _TYPE_C_ENTER_DELL_ALT_MODE_TIMEOUT))
            {
                enumAltModeWait = _TYPE_C_ALT_MODE_NOT_WAIT;
            }
            else
            {
                enumAltModeWait = _TYPE_C_ALT_MODE_WAIT;
            }
#else
            enumAltModeWait = _TYPE_C_ALT_MODE_NOT_WAIT;
#endif

            break;
#endif

        default:
            break;
    }

    return enumAltModeWait;
}

//--------------------------------------------------
// Description  : User Decide Type-C Function Support Option
// Input Value  : enumTypeCPcbPort
// Output Value : Type-C Function Support Option (_TYPE_C_SUPPORT_NO_FUNCTION / _TYPE_C_SUPPORT_CC_FUNCTION / _TYPE_C_SUPPORT_CC_AND_PD_FUNCTION...)
//--------------------------------------------------
EnumTypeCFunctionSupport UserInterfaceUsbTypeCGetFunctionSupport(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCFunctionSupport enumFunctionSupport = _TYPE_C_SUPPORT_DEFAULT_FUNCTION;
    enumTypeCPcbPort = enumTypeCPcbPort;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            enumFunctionSupport = _TYPE_C_SUPPORT_FULL_FUNCTION;

            break;
#endif

        default:
            break;
    }

    return enumFunctionSupport;
}

//--------------------------------------------------
// Description  : User Decide Type-C Operation Mode
// Input Value  : enumTypeCPcbPort
// Output Value : Type-C Operation Mode (_TYPE_C_SRC_ONLY_MODE / _TYPE_C_SNK_ONLY_MODE / _TYPE_C_DRP_NO_PREFERENCE_MODE...)
//--------------------------------------------------
EnumTypeCOperationMode UserInterfaceUsbTypeCGetOperationMode(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumTypeCOperationMode enumOperationMode = _TYPE_C_DEFAULT_OPERATION_MODE;
    enumTypeCPcbPort = enumTypeCPcbPort;

    // =============================== WARNING ===============================
    // For Embbeded Type-C:
    // Type-C Operation Mode Should Not be '_TYPE_C_SRC_ONLY_MODE' if '_xx_DP_TYPE_C_EMB_DEAD_BATTERY_SUPPORT' = '_ON'
    // Type-C Operation Mode Should Not be '_TYPE_C_SNK_ONLY_MODE' if '_xx_DP_TYPE_C_EMB_PD3_PPS_SUPPORT' = '_ON'
    // Type-C Operation Mode Should Not be '_TYPE_C_SRC_ONLY_MODE' or '_TYPE_C_SNK_ONLY_MODE' if '_xx_DP_TYPE_C_EMB_PD3_FRSWAP_SUPPORT' = '_ON'
    // Type-C Operation Mode Should be '_TYPE_C_SNK_ONLY_MODE' if '_TYPE_C_POWER_SOURCE' = '_TYPE_C_VBUS_POWER_ONLY'
    // Type-C Operation Mode Should be '_TYPE_C_SNK_ONLY_MODE' for Adaptor Type-C Port
    // Type-C Operation Mode Should Not be '_TYPE_C_DRP_TRY_SRC_MODE' for DP Rx Port (Dx)
    // =======================================================================

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            enumOperationMode = _TYPE_C_DEFAULT_OPERATION_MODE;

            break;
#endif

        default:
            break;
    }

    return enumOperationMode;
}

//--------------------------------------------------
// Description  : Get Type-C Status Event
// Input Value  : enumTypeCPcbPort
//                pstStatusEvent --> Status Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCGetStatusEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCStatusEvent *pstStatusEvent)
{
    // 1. User Can Update Status Event Whenever Monitor Status Changes
    // 2. Kernel will Get Status Event in this Function and Send to Port Ctrl
    // Fill in the Corresponding Value according to the Status Message in the PD Standard

    enumTypeCPcbPort = enumTypeCPcbPort;
    pstStatusEvent = pstStatusEvent;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            /* Example :
            if(Power State == S0)
            {
                pstStatusEvent->b3NewPowerState = 0x01;   // S0
                pstStatusEvent->b3NewPSIndicator = 0x01;  // On LED
            }
            else if(Power State == S3)
            {
                pstStatusEvent->b3NewPowerState = 0x03;   // S3
                pstStatusEvent->b3NewPSIndicator = 0x03;  // Breathing LED
            }
            */

            pstStatusEvent->b3NewPowerState = 0x00;   // Status not supported
            pstStatusEvent->b3NewPSIndicator = 0x00;  // Off LED

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Type-C Alert Event
// Input Value  : enumTypeCPcbPort
//                pstAlertEvent --> Alert Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCGetAlertEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAlertEvent *pstAlertEvent)
{
    // 1. User Can Update Alert Event When Monitor Need to Notify Alert Event to Por Partner
    // 2. Kernel will Get Alert Event in this Function and Send to Port Ctrl
    // Fill in the Corresponding Value according to the Alert Message in the PD Standard

    enumTypeCPcbPort = enumTypeCPcbPort;
    pstAlertEvent = pstAlertEvent;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            /* Example :
            if(OCP and OVP happen at the same time)
            {
                pstAlertEvent->enumTypeOfAlert = (_TYPE_C_TYPE_OF_ALERT_OCP | _TYPE_C_TYPE_OF_ALERT_OVP);
                pstAlertEvent->enumBatStatus = _TYPE_C_BAT_NONE;
                pstAlertEvent->enumExtAlertEvent = _TYPE_C_EXT_ALERT_EVENT_NONE;
            }

            if(Power Button Press)
            {
                pstAlertEvent->enumTypeOfAlert = _TYPE_C_TYPE_OF_ALERT_EXTALERTEVENT;             // Extended Alert Event
                pstAlertEvent->enumBatStatus = _TYPE_C_BAT_NONE;                                  // No Battery Status Change
                pstAlertEvent->enumExtAlertEvent = _TYPE_C_EXT_ALERT_EVENT_POWERBUTTON_PRESS;     // Power button press (UFP only)
            }
            else if(Power Button Release)
            {
                pstAlertEvent->enumTypeOfAlert = _TYPE_C_TYPE_OF_ALERT_EXTALERTEVENT;             // Extended Alert Event
                pstAlertEvent->enumBatStatus = _TYPE_C_BAT_NONE;                                  // No Battery Status Change
                pstAlertEvent->enumExtAlertEvent = _TYPE_C_EXT_ALERT_EVENT_POWERBUTTON_RELEASE;   // Power button release (UFP only)
            }
            */

            pstAlertEvent->enumTypeOfAlert = _TYPE_C_TYPE_OF_ALERT_NONE;
            pstAlertEvent->enumBatStatus = _TYPE_C_BAT_NONE;
            pstAlertEvent->enumExtAlertEvent = _TYPE_C_EXT_ALERT_EVENT_NONE;

            break;
#endif

        default:
            break;
    }
}

#if(_TYPE_C_EIZO_CUSTOMIZED_DP_LANE_CNT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : For User to Translate Alt. Mode Pin Assignment to DP Lane Count
// Input Value  : enumTypeCPcbPort, enumPinAssignment : _TYPE_C_PIN_ASSIGNMENT_C / _TYPE_C_PIN_ASSIGNMENT_D / _TYPE_C_PIN_ASSIGNMENT_E
// Output Value : EnumDpLaneCount -> _DP_LINK_1_LANE / _DP_LINK_2_LANE / _DP_LINK_4_LANE
//--------------------------------------------------
EnumDpLaneCount UserInterfaceUsbTypeCGetAltModeLaneCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment)
{
    EnumDpLaneCount enumAltModeLaneCnt = _DP_LINK_4_LANE;
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPinAssignment = enumPinAssignment;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            // User Can Update DP Lane Cnt According to Pin Assignments
            switch(enumPinAssignment)
            {
                case _TYPE_C_PIN_ASSIGNMENT_C:
                case _TYPE_C_PIN_ASSIGNMENT_E:

                    enumAltModeLaneCnt = _DP_LINK_4_LANE;

                    break;

                case _TYPE_C_PIN_ASSIGNMENT_D:

                    enumAltModeLaneCnt = _DP_LINK_2_LANE;

                    break;


                default:

                    break;
            }

            break;
#endif

        default:
            break;
    }

    return enumAltModeLaneCnt;
}
#endif

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : TypeC Lenovo Alt Mode Check Lenovo Device Type Valid
// Input Value  : enumTypeCPcbPort, enumLenovoDeviceType
// Output Value : Lenovo Device Type Check Result (_TYPE_C_LENOVO_DEVICE_TYPE_INVALID / _TYPE_C_LENOVO_DEVICE_TYPE_VALID)
//--------------------------------------------------
EnumTypeCLenovoCheckDeviceTypeResult UserInterfaceUsbTypeCCheckLenovoDeviceTypeValid(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCLenovoDeviceType enumLenovoDeviceType)
{
    EnumTypeCLenovoCheckDeviceTypeResult enumLenovoCheckDeviceTypeResult = _TYPE_C_LENOVO_DEVICE_TYPE_INVALID;
    enumLenovoDeviceType = enumLenovoDeviceType;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            // Check if Lenovo VDM Function is Supported According to Device Type from Port Partner
            // If No Need to Check Device Type, Always Return _TYPE_C_LENOVO_DEVICE_TYPE_VALID
            if(enumLenovoDeviceType == _TYPE_C_LENOVO_DESKTOP_PC)
            {
                enumLenovoCheckDeviceTypeResult = _TYPE_C_LENOVO_DEVICE_TYPE_VALID;
            }

            break;
#endif

        default:
            break;
    }

    return enumLenovoCheckDeviceTypeResult;
}

//--------------------------------------------------
// Description  : TypeC Lenovo Alt Mode System Event or System Acknowledge Handler Process
// Input Value  : enumTypeCPcbPort
//                stLenovoSysEvent --> Lenovo System Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCLenovoAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoSysEvent stLenovoSysEvent)
{
    stLenovoSysEvent = stLenovoSysEvent;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:
            // User can Change its behavior corresponding to System Event
            // User can Retry Last Dock Event or Send Next Dock Event corresponding to System Acknowledge
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TypeC Lenovo Alt Mode Get Docking Event
// Input Value  : enumTypeCPcbPort
//                stLenovoDockEvent --> Lenovo Docking Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCGetLenovoDockingEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoDockEvent *pstLenovoDockEvent)
{
    pstLenovoDockEvent = pstLenovoDockEvent;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            // Check if Docking Event Queue is Empty
            if(GET_D0_TYPE_C_DOCK_EVENT_CNT() > 0)
            {
                // Update Docking Event Struct For Kernal Usage
                memcpy(pstLenovoDockEvent, &GET_D0_TYPE_C_DOCK_EVENT_QUEUE(GET_D0_TYPE_C_DOCK_EVENT_HEAD()), sizeof(StructTypeCLenovoDockEvent));

                CLR_D0_TYPE_C_DOCK_EVENT_QUEUE();
                ADD_D0_TYPE_C_DOCK_EVENT_HEAD();
                SUB_D0_TYPE_C_DOCK_EVENT_CNT();
            }
            else
            {
                // Reset Default Value to Lenovo Docking Event
                pstLenovoDockEvent->b4DockingReserved = 0x00;
                pstLenovoDockEvent->enumDockingPowerSwitch = _TYPE_C_LENOVO_DOCK_POWER_SWITCH_NONE;
                pstLenovoDockEvent->b1DockingWolRequest = _FALSE;
                pstLenovoDockEvent->b1DockingEvent = _FALSE;
            }

            break;
#endif

        default:
            break;
    }
}
#endif // End if #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : TypeC Acer Alt Mode System Event Process
// Input Value  : enumTypeCPcbPort
//                stAcerSysEvent --> Acer System Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCAcerAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAcerSysEvent stAcerSysEvent)
{
    stAcerSysEvent = stAcerSysEvent;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:
            // User can Change its behavior corresponding to System Event
            // stAcerSysEvent.b3VdmCnt : Number of VDO from System
            // stAcerSysEvent.pucVdmData[0] : VDO_0[31:24], pucVdmData[1] : VDO_0[23:16]...
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TypeC Acer Alt Mode Get User Event
// Input Value  : enumTypeCPcbPort
//                pstAcerUserEvent --> Acer User Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCGetAcerUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAcerUserEvent *pstAcerUserEvent)
{
    // 1. User Can Update User Event Macro Whenever Monitor Status Changes
    // 2. Kernel will Get Acer User Event in this Function and send to Port Ctrl

    BYTE ucVdoDataIndex = 0x00;

    pstAcerUserEvent = pstAcerUserEvent;
    ucVdoDataIndex = ucVdoDataIndex;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            /* Example :
            if(Monitor Status Change)
            {
                SET_D0_TYPE_C_ACER_USER_EVENT(_TYPE_C_ACER_USER_EVENT_ATTENTION);   // Ask Kenel Send Attention
                SET_D0_TYPE_C_ACER_USER_VDM_CNT( N );   // Set Number of VDO (Not include VDM Header)
                SET_D0_TYPE_C_ACER_USER_VDM_DATA(0, VDO_0[31:24]);
                SET_D0_TYPE_C_ACER_USER_VDM_DATA(1, VDO_0[23:16]);
                SET_D0_TYPE_C_ACER_USER_VDM_DATA(2, VDO_0[15:8]);
                SET_D0_TYPE_C_ACER_USER_VDM_DATA(3, VDO_0[7:0]);
            }
            */

            // Check Acer User Event
            if(GET_D0_TYPE_C_ACER_USER_EVENT() != _TYPE_C_ACER_USER_EVENT_NONE)
            {
                // Update Acer User Event to Kernel
                pstAcerUserEvent->enumEvent = GET_D0_TYPE_C_ACER_USER_EVENT();
                pstAcerUserEvent->b3VdmCnt = GET_D0_TYPE_C_ACER_USER_VDM_CNT();

                for(ucVdoDataIndex = 0; ucVdoDataIndex < (GET_D0_TYPE_C_ACER_USER_VDM_CNT() * 4); ucVdoDataIndex++)
                {
                    pstAcerUserEvent->pucVdmData[ucVdoDataIndex] = GET_D0_TYPE_C_ACER_USER_VDM_DATA(ucVdoDataIndex);
                }

                // Clear Acer User Evnet in User
                CLR_D0_TYPE_C_ACER_USER_EVENT(_TYPE_C_ACER_USER_EVENT_ALL);
            }

            break;
#endif

        default:
            break;
    }
}
#endif // End if #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : TypeC Hp Alt Mode System Event Process
// Input Value  : enumTypeCPcbPort
//                stHpSysEvent --> Hp System Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCHpAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCHpSysEvent stHpSysEvent)
{
    stHpSysEvent = stHpSysEvent;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:
            // User can Change its behavior corresponding to System Event
            // stHpSysEvent.b3VdmCnt : Number of VDO from System
            // stHpSysEvent.pucVdmData[0] : VDO_0[31:24], pucVdmData[1] : VDO_0[23:16]...
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TypeC Hp Alt Mode Get User Event
// Input Value  : enumTypeCPcbPort
//                pstHpUserEvent --> Hp User Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCGetHpUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCHpUserEvent *pstHpUserEvent)
{
    // 1. User Can Update User Event Macro Whenever Monitor Status Changes
    // 2. Kernel will Get Hp User Event in this Function and send to Port Ctrl

    BYTE ucVdoDataIndex = 0x00;

    pstHpUserEvent = pstHpUserEvent;
    ucVdoDataIndex = ucVdoDataIndex;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            /* Example :
            if(Monitor Status Change)
            {
                SET_D0_TYPE_C_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTENTION);   // Ask Kenel Send Attention
                SET_D0_TYPE_C_HP_USER_VDM_CNT( N );   // Set Number of VDO (Not include VDM Header)
                SET_D0_TYPE_C_HP_USER_VDM_DATA(0, VDO_0[31:24]);
                SET_D0_TYPE_C_HP_USER_VDM_DATA(1, VDO_0[23:16]);
                SET_D0_TYPE_C_HP_USER_VDM_DATA(2, VDO_0[15:8]);
                SET_D0_TYPE_C_HP_USER_VDM_DATA(3, VDO_0[7:0]);
            }
            */

            // Check Hp User Event
            if(GET_D0_TYPE_C_HP_USER_EVENT() != _TYPE_C_HP_USER_EVENT_NONE)
            {
                if(GET_D0_TYPE_C_HP_USER_VDM_CNT() > 5)
                {
                    SET_D0_TYPE_C_HP_USER_VDM_CNT(5);
                }

                // Update Hp User Event to Kernel
                pstHpUserEvent->enumEvent = GET_D0_TYPE_C_HP_USER_EVENT();
                pstHpUserEvent->b3VdmCnt = GET_D0_TYPE_C_HP_USER_VDM_CNT();

                for(ucVdoDataIndex = 0; ucVdoDataIndex < (GET_D0_TYPE_C_HP_USER_VDM_CNT() * 4); ucVdoDataIndex++)
                {
                    pstHpUserEvent->pucVdmData[ucVdoDataIndex] = GET_D0_TYPE_C_HP_USER_VDM_DATA(ucVdoDataIndex);
                }

                // Clear Hp User Evnet in User
                CLR_D0_TYPE_C_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ALL);
            }

            break;
#endif

        default:
            break;
    }
}
#endif // End if #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : TypeC Get Dell Alt Mode Initial Complete Status
// Input Value  : enumTypeCPcbPort
// Output Value : Dell Alt Mode Initial Complete (_TYPE_C_DELL_INIT_COMPLETE / _TYPE_C_DELL_INIT_NOT_COMPLETE)
//--------------------------------------------------
EnumTypeCDellInitCompleteStatus UserInterfaceUsbTypeCGetDellAltModeInitComplete(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        // =======================================================================
        // The following are two conditions for DDM1_INIT_COMPLETE in Dell Alt Mode Spec:
        // (a) Scaler responded RESPONSE_OK on HOST_CMD_PWRBTN_LED from Host.
        // (b) Scaler responded DEVICE_STATUS on HOST_CMD_GET_DEVICE_STATUS from Host.
        //
        // When User Detects that the Dell Alt Mode is Ready, Active a 700ms Timer.
        // If DDM1_INIT_COMPLETE Status has not been Reached within 700ms, Also Return _TYPE_C_DELL_INIT_COMPLETE, so that Kernel can Know when to Start Link Training.
        //
        //
        // To Summarize the above Description:
        // If User Detects these two conditions (Both a and b Conditions) are Met or 700ms Timer Time Out, then Return _TYPE_C_DELL_INIT_COMPLETE.
        // Otherwise, Return _TYPE_C_DELL_INIT_NOT_COMPLETE.
        //
        // Note:
        // When leaving Dell Alt Mode (In Other Words, Dell Alt Mode isn't Ready), Please Clear DDM1_INIT_COMPLETE Status.
        // =======================================================================

#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            /* Example :
            if(Both Condition are Met || 700ms Timer Time Out)
            {
                return _TYPE_C_DELL_INIT_COMPLETE;
            }
            else
            {
                return _TYPE_C_DELL_INIT_NOT_COMPLETE;
            }
            */

            break;
#endif

        default:
            break;
    }

    return _TYPE_C_DELL_INIT_NOT_COMPLETE;
}

//--------------------------------------------------
// Description  : TypeC Dell Alt Mode System Event Process
// Input Value  : enumTypeCPcbPort
//                stDellSysEvent --> Dell System Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCDellAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCDellSysEvent stDellSysEvent)
{
    stDellSysEvent = stDellSysEvent;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:
            // User can Change its behavior corresponding to System Event
            // stDellSysEvent.b3VdmCnt : Number of VDO from System
            // stDellSysEvent.pucVdmData[0] : VDO_0[31:24], pucVdmData[1] : VDO_0[23:16]...
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TypeC Dell Alt Mode Get User Event
// Input Value  : enumTypeCPcbPort
//                pstDellUserEvent --> Dell User Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCGetDellUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCDellUserEvent *pstDellUserEvent)
{
    // 1. User Can Update User Event Macro Whenever Monitor Status Changes
    // 2. Kernel will Get Dell User Event in this Function and send to Port Ctrl

    BYTE ucVdoDataIndex = 0x00;

    pstDellUserEvent = pstDellUserEvent;
    ucVdoDataIndex = ucVdoDataIndex;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            /* Example :
            if(Monitor Status Change)
            {
                SET_D0_TYPE_C_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ATTEN);   // Ask Kenel Send Attention
                SET_D0_TYPE_C_DELL_USER_VDM_CNT( N );   // Set Number of VDO (Not include VDM Header)
                SET_D0_TYPE_C_DELL_USER_VDM_DATA(0, VDO_0[31:24]);
                SET_D0_TYPE_C_DELL_USER_VDM_DATA(1, VDO_0[23:16]);
                SET_D0_TYPE_C_DELL_USER_VDM_DATA(2, VDO_0[15:8]);
                SET_D0_TYPE_C_DELL_USER_VDM_DATA(3, VDO_0[7:0]);
            }
            */

            // Check Dell User Event
            if(GET_D0_TYPE_C_DELL_USER_EVENT() != _TYPE_C_DELL_USER_EVENT_NONE)
            {
                if(GET_D0_TYPE_C_DELL_USER_VDM_CNT() > 6)
                {
                    SET_D0_TYPE_C_DELL_USER_VDM_CNT(6);
                }

                // Update Dell User Event to Kernel
                pstDellUserEvent->enumEvent = GET_D0_TYPE_C_DELL_USER_EVENT();
                pstDellUserEvent->b3VdmCnt = GET_D0_TYPE_C_DELL_USER_VDM_CNT();

                for(ucVdoDataIndex = 0; ucVdoDataIndex < (GET_D0_TYPE_C_DELL_USER_VDM_CNT() * 4); ucVdoDataIndex++)
                {
                    pstDellUserEvent->pucVdmData[ucVdoDataIndex] = GET_D0_TYPE_C_DELL_USER_VDM_DATA(ucVdoDataIndex);
                }

                // Clear Dell User Evnet in User
                CLR_D0_TYPE_C_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ALL);
            }

            break;
#endif

        default:
            break;
    }
}
#endif // End if #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#endif // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

#if(_PORT_CTRL_RTS_SUPPORT == _ON)
#if(_TYPE_C_PORT_CTRL_RTS_SMBUS_MODE == _PORT_CTRL_RTS_INT_MODE)
//--------------------------------------------------
// Description  : TypeC Get Notification Enable
// Input Value  : enumTypeCPcbPort
//                pstTypeCNotifyEn --> Notification Enable
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCRtsGetNotifyEn(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCRtsNotifyEn *pstTypeCNotifyEn)
{
    pstTypeCNotifyEn = pstTypeCNotifyEn;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            // Set Notification Enable to Notify the Event Changes on Interrupt Pin
            // Kernel Require the following Event, so User Must be Set: _TYPE_C_RTS_NOTIFY_EN_B1_CONNECT_CHG, _TYPE_C_RTS_NOTIFY_EN_B2_ALT_FLOW_CHG, and _TYPE_C_RTS_NOTIFY_EN_B2_PORT_OP_MODE_CHG
            // Reserved bit only Needs to be Set if it Becomes Non-Reserved in the Future, otherwise do not Set Notification Enable to Reserved Bit
            pstTypeCNotifyEn->enumNotifyEnByte0 = _TYPE_C_RTS_NOTIFY_EN_B0_NONE;
            pstTypeCNotifyEn->enumNotifyEnByte1 = _TYPE_C_RTS_NOTIFY_EN_B1_CONNECT_CHG;
            pstTypeCNotifyEn->enumNotifyEnByte2 = (EnumUsbTypeCRtsNotifyEnByte2) (_TYPE_C_RTS_NOTIFY_EN_B2_ALT_FLOW_CHG | _TYPE_C_RTS_NOTIFY_EN_B2_PORT_OP_MODE_CHG);
            pstTypeCNotifyEn->enumNotifyEnByte3 = _TYPE_C_RTS_NOTIFY_EN_B3_NONE;

            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : TypeC Turn On 5450 Status Update
// Input Value  : enumTypeCPcbPort --> Input Port
// Output Value : Turn On 5450 Status Update (_TRUE / _FALSE)
//--------------------------------------------------
BYTE UserInterfaceUsbTypeCTurnOnRtsStatusUpdate(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_TYPE_C_PORT:

            return _TRUE;

            break;
#endif

#if(_D1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_TYPE_C_PORT:

            return _TRUE;

            break;
#endif

#if(_D2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D2_TYPE_C_PORT:

            return _TRUE;

            break;
#endif

#if(_P0_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P0_TYPE_C_PORT:

            return _TRUE;

            break;
#endif

#if(_P1_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P1_TYPE_C_PORT:

            return _TRUE;

            break;
#endif

#if(_P2_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P2_TYPE_C_PORT:

            return _TRUE;

            break;
#endif

#if(_P3_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P3_TYPE_C_PORT:

            return _TRUE;

            break;
#endif

#if(_P4_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _P4_TYPE_C_PORT:

            return _TRUE;

            break;
#endif

#if(_ADAPTOR_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _ADAPTOR_TYPE_C_PORT:

            return _TRUE;

            break;
#endif

        default:
            break;
    }

    return _TRUE;
}
#endif // End of #if(_PORT_CTRL_RTS_SUPPORT == _ON)

#if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON) || (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))
//--------------------------------------------------
// Description  : User Control Type-C Port Controller Power
// Input Value  : ucSwitch --> Power Action
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCPowerControl(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            // Switch On Port Controller Power By PCB Control
            PCB_D0_PORT_CTRL_POWER(_D0_PORT_CTRL_POWER_ON);
            CLR_D0_TYPE_C_POWER_OFF_FLG();
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            // Switch On Port Controller Power By PCB Control
            PCB_D1_PORT_CTRL_POWER(_D1_PORT_CTRL_POWER_ON);
            CLR_D1_TYPE_C_POWER_OFF_FLG();
#endif  // End of #if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            // Switch On Port Controller Power By PCB Control
            PCB_D2_PORT_CTRL_POWER(_D2_PORT_CTRL_POWER_ON);
            CLR_D2_TYPE_C_POWER_OFF_FLG();
#endif  // End of #if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            // Switch On Port Controller Power By PCB Control
            PCB_P0_PORT_CTRL_POWER(_P0_PORT_CTRL_POWER_ON);
            CLR_P0_TYPE_C_POWER_OFF_FLG();
#endif  // End of #if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            // Switch On Port Controller Power By PCB Control
            PCB_P1_PORT_CTRL_POWER(_P1_PORT_CTRL_POWER_ON);
            CLR_P1_TYPE_C_POWER_OFF_FLG();
#endif  // End of #if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            // Switch On Port Controller Power By PCB Control
            PCB_P2_PORT_CTRL_POWER(_P2_PORT_CTRL_POWER_ON);
            CLR_P2_TYPE_C_POWER_OFF_FLG();
#endif  // End of #if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            // Switch On Port Controller Power By PCB Control
            PCB_P3_PORT_CTRL_POWER(_P3_PORT_CTRL_POWER_ON);
            CLR_P3_TYPE_C_POWER_OFF_FLG();
#endif  // End of #if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            // Switch On Port Controller Power By PCB Control
            PCB_P4_PORT_CTRL_POWER(_P4_PORT_CTRL_POWER_ON);
            CLR_P4_TYPE_C_POWER_OFF_FLG();
#endif  // End of #if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

            break;

        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:

#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(PCB_D0_PORT_CTRL_POWER_STATUS() == _D0_PORT_CTRL_POWER_OFF)
            {
                // Switch On Port Conroller Power By PCB Control
                PCB_D0_PORT_CTRL_POWER(_D0_PORT_CTRL_POWER_ON);
            }
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(PCB_D1_PORT_CTRL_POWER_STATUS() == _D1_PORT_CTRL_POWER_OFF)
            {
                // Switch On Port Conroller Power By PCB Control
                PCB_D1_PORT_CTRL_POWER(_D1_PORT_CTRL_POWER_ON);
            }
#endif  // End of #if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(PCB_D2_PORT_CTRL_POWER_STATUS() == _D2_PORT_CTRL_POWER_OFF)
            {
                // Switch On Port Conroller Power By PCB Control
                PCB_D2_PORT_CTRL_POWER(_D2_PORT_CTRL_POWER_ON);
            }
#endif  // End of #if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(PCB_P0_PORT_CTRL_POWER_STATUS() == _P0_PORT_CTRL_POWER_OFF)
            {
                // Switch On Port Conroller Power By PCB Control
                PCB_P0_PORT_CTRL_POWER(_P0_PORT_CTRL_POWER_ON);
            }
#endif  // End of #if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(PCB_P1_PORT_CTRL_POWER_STATUS() == _P1_PORT_CTRL_POWER_OFF)
            {
                // Switch On Port Conroller Power By PCB Control
                PCB_P1_PORT_CTRL_POWER(_P1_PORT_CTRL_POWER_ON);
            }
#endif  // End of #if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(PCB_P2_PORT_CTRL_POWER_STATUS() == _P2_PORT_CTRL_POWER_OFF)
            {
                // Switch On Port Conroller Power By PCB Control
                PCB_P2_PORT_CTRL_POWER(_P2_PORT_CTRL_POWER_ON);
            }
#endif  // End of #if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(PCB_P3_PORT_CTRL_POWER_STATUS() == _P3_PORT_CTRL_POWER_OFF)
            {
                // Switch On Port Conroller Power By PCB Control
                PCB_P3_PORT_CTRL_POWER(_P3_PORT_CTRL_POWER_ON);
            }
#endif  // End of #if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(PCB_P4_PORT_CTRL_POWER_STATUS() == _P4_PORT_CTRL_POWER_OFF)
            {
                // Switch On Port Conroller Power By PCB Control
                PCB_P4_PORT_CTRL_POWER(_P4_PORT_CTRL_POWER_ON);
            }
#endif  // End of #if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

            break;

        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_PS:

#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(SysSourceGetCableDetect(_D0_INPUT_PORT) == _FALSE)
            {
                // Switch Off Repeater Power By PCB Control
                PCB_D0_PORT_CTRL_POWER(_D0_PORT_CTRL_POWER_OFF);
                SET_D0_TYPE_C_POWER_OFF_FLG();
            }
            else
            {
                CLR_D0_TYPE_C_POWER_OFF_FLG();
            }
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(SysSourceGetCableDetect(_D1_INPUT_PORT) == _FALSE)
            {
                // Switch Off Repeater Power By PCB Control
                PCB_D1_PORT_CTRL_POWER(_D1_PORT_CTRL_POWER_OFF);
                SET_D1_TYPE_C_POWER_OFF_FLG();
            }
            else
            {
                CLR_D1_TYPE_C_POWER_OFF_FLG();
            }
#endif  // End of #if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(SysSourceGetCableDetect(_D2_INPUT_PORT) == _FALSE)
            {
                // Switch Off Repeater Power By PCB Control
                PCB_D2_PORT_CTRL_POWER(_D2_PORT_CTRL_POWER_OFF);
                SET_D2_TYPE_C_POWER_OFF_FLG();
            }
            else
            {
                CLR_D2_TYPE_C_POWER_OFF_FLG();
            }
#endif  // End of #if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if(_DP_TX_SUPPORT == _ON)
#if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(SysDpTxCableDetect(_P0_OUTPUT_PORT) == _FALSE)
            {
                // Switch Off Repeater Power By PCB Control
                PCB_P0_PORT_CTRL_POWER(_P0_PORT_CTRL_POWER_OFF);
                SET_P0_TYPE_C_POWER_OFF_FLG();
            }
            else
            {
                CLR_P0_TYPE_C_POWER_OFF_FLG();
            }
#endif  // End of #if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(SysDpTxCableDetect(_P1_OUTPUT_PORT) == _FALSE)
            {
                // Switch Off Repeater Power By PCB Control
                PCB_P1_PORT_CTRL_POWER(_P1_PORT_CTRL_POWER_OFF);
                SET_P1_TYPE_C_POWER_OFF_FLG();
            }
            else
            {
                CLR_P1_TYPE_C_POWER_OFF_FLG();
            }
#endif  // End of #if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(SysDpTxCableDetect(_P2_OUTPUT_PORT) == _FALSE)
            {
                // Switch Off Repeater Power By PCB Control
                PCB_P2_PORT_CTRL_POWER(_P2_PORT_CTRL_POWER_OFF);
                SET_P2_TYPE_C_POWER_OFF_FLG();
            }
            else
            {
                CLR_P2_TYPE_C_POWER_OFF_FLG();
            }
#endif  // End of #if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(SysDpTxCableDetect(_P3_OUTPUT_PORT) == _FALSE)
            {
                // Switch Off Repeater Power By PCB Control
                PCB_P3_PORT_CTRL_POWER(_P3_PORT_CTRL_POWER_OFF);
                SET_P3_TYPE_C_POWER_OFF_FLG();
            }
            else
            {
                CLR_P3_TYPE_C_POWER_OFF_FLG();
            }
#endif  // End of #if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
            if(SysDpTxCableDetect(_P4_OUTPUT_PORT) == _FALSE)
            {
                // Switch Off Repeater Power By PCB Control
                PCB_P4_PORT_CTRL_POWER(_P4_PORT_CTRL_POWER_OFF);
                SET_P4_TYPE_C_POWER_OFF_FLG();
            }
            else
            {
                CLR_P4_TYPE_C_POWER_OFF_FLG();
            }
#endif  // End of #if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
#endif  // End of #if(_DP_TX_SUPPORT == _ON)

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Power Off Flag to set Capability Change Flag
// Input Value  : enumTypeCPcbPort, enumSwitch
// Output Value : return _TYPE_C_PORT_CTRL_NO_RECONNECT / _TYPE_C_PORT_CTRL_RECONNECT
//--------------------------------------------------
EnumTypeCPortCtrlReconnectStatus UserInterfaceUsbTypeCGetPowerOnReconnectStatus(EnumTypeCPcbPort enumTypeCPcbPort, EnumPowerAction enumSwitch)
{
    switch(enumTypeCPcbPort)
    {
#if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _D0_TYPE_C_PORT:

            switch(enumSwitch)
            {
                case _POWER_ACTION_OFF_TO_NORMAL:
                case _POWER_ACTION_PS_TO_NORMAL:

                    if(GET_D0_TYPE_C_POWER_OFF_FLG() == _TRUE)
                    {
                        return _TYPE_C_PORT_CTRL_RECONNECT;
                    }
                    else
                    {
                        return _TYPE_C_PORT_CTRL_NO_RECONNECT;
                    }
                    break;

                default:

                    return _TYPE_C_PORT_CTRL_NO_RECONNECT;

                    break;
            }

            break;
#endif  // End of #if((_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _D1_TYPE_C_PORT:

            switch(enumSwitch)
            {
                case _POWER_ACTION_OFF_TO_NORMAL:
                case _POWER_ACTION_PS_TO_NORMAL:

                    if(GET_D1_TYPE_C_POWER_OFF_FLG() == _TRUE)
                    {
                        return _TYPE_C_PORT_CTRL_RECONNECT;
                    }
                    else
                    {
                        return _TYPE_C_PORT_CTRL_NO_RECONNECT;
                    }
                    break;

                default:

                    return _TYPE_C_PORT_CTRL_NO_RECONNECT;

                    break;
            }

            break;
#endif  // End of #if((_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _D2_TYPE_C_PORT:

            switch(enumSwitch)
            {
                case _POWER_ACTION_OFF_TO_NORMAL:
                case _POWER_ACTION_PS_TO_NORMAL:

                    if(GET_D2_TYPE_C_POWER_OFF_FLG() == _TRUE)
                    {
                        return _TYPE_C_PORT_CTRL_RECONNECT;
                    }
                    else
                    {
                        return _TYPE_C_PORT_CTRL_NO_RECONNECT;
                    }
                    break;

                default:

                    return _TYPE_C_PORT_CTRL_NO_RECONNECT;

                    break;
            }

            break;
#endif  // End of #if((_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P0_TYPE_C_PORT:

            switch(enumSwitch)
            {
                case _POWER_ACTION_OFF_TO_NORMAL:
                case _POWER_ACTION_PS_TO_NORMAL:

                    if(GET_P0_TYPE_C_POWER_OFF_FLG() == _TRUE)
                    {
                        return _TYPE_C_PORT_CTRL_RECONNECT;
                    }
                    else
                    {
                        return _TYPE_C_PORT_CTRL_NO_RECONNECT;
                    }
                    break;

                default:

                    return _TYPE_C_PORT_CTRL_NO_RECONNECT;

                    break;
            }

            break;
#endif  // End of #if((_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P1_TYPE_C_PORT:

            switch(enumSwitch)
            {
                case _POWER_ACTION_OFF_TO_NORMAL:
                case _POWER_ACTION_PS_TO_NORMAL:

                    if(GET_P1_TYPE_C_POWER_OFF_FLG() == _TRUE)
                    {
                        return _TYPE_C_PORT_CTRL_RECONNECT;
                    }
                    else
                    {
                        return _TYPE_C_PORT_CTRL_NO_RECONNECT;
                    }
                    break;

                default:

                    return _TYPE_C_PORT_CTRL_NO_RECONNECT;

                    break;
            }

            break;
#endif  // End of #if((_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P2_TYPE_C_PORT:

            switch(enumSwitch)
            {
                case _POWER_ACTION_OFF_TO_NORMAL:
                case _POWER_ACTION_PS_TO_NORMAL:

                    if(GET_P2_TYPE_C_POWER_OFF_FLG() == _TRUE)
                    {
                        return _TYPE_C_PORT_CTRL_RECONNECT;
                    }
                    else
                    {
                        return _TYPE_C_PORT_CTRL_NO_RECONNECT;
                    }
                    break;

                default:

                    return _TYPE_C_PORT_CTRL_NO_RECONNECT;

                    break;
            }

            break;
#endif  // End of #if((_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P3_TYPE_C_PORT:

            switch(enumSwitch)
            {
                case _POWER_ACTION_OFF_TO_NORMAL:
                case _POWER_ACTION_PS_TO_NORMAL:

                    if(GET_P3_TYPE_C_POWER_OFF_FLG() == _TRUE)
                    {
                        return _TYPE_C_PORT_CTRL_RECONNECT;
                    }
                    else
                    {
                        return _TYPE_C_PORT_CTRL_NO_RECONNECT;
                    }
                    break;

                default:

                    return _TYPE_C_PORT_CTRL_NO_RECONNECT;

                    break;
            }

            break;
#endif  // End of #if((_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

#if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))
        case _P4_TYPE_C_PORT:

            switch(enumSwitch)
            {
                case _POWER_ACTION_OFF_TO_NORMAL:
                case _POWER_ACTION_PS_TO_NORMAL:

                    if(GET_P4_TYPE_C_POWER_OFF_FLG() == _TRUE)
                    {
                        return _TYPE_C_PORT_CTRL_RECONNECT;
                    }
                    else
                    {
                        return _TYPE_C_PORT_CTRL_NO_RECONNECT;
                    }
                    break;

                default:

                    return _TYPE_C_PORT_CTRL_NO_RECONNECT;

                    break;
            }

            break;
#endif  // End of #if((_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTS) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD) || (_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_USER))

        default:
            // Adaptor TypeC Port Does Not Reconnect
            return _TYPE_C_PORT_CTRL_NO_RECONNECT;

            break;
    }

    return _TYPE_C_PORT_CTRL_NO_RECONNECT;
}
#endif // End of #if((_PORT_CTRL_RTS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON) || (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))

#if(_PORT_CTRL_USER_SERIES_SUPPORT == _ON)
#if(_PORT_CTRL_USER_DET_CC_ATTACH_BY_SMBUS == _ON)
//--------------------------------------------------
// Description  : Get User Port Ctrl CC Attached Info Through I2C
// Input Value  : enumTypeCPcbPort : _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : CC Attach (_TYPE_C_UNATTACH / _TYPE_C_ATTACH)
//--------------------------------------------------
EnumTypeCAttachStatus UserInterfaceUsbTypeCUserGetCcAttachByI2C(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // User Can Use Their Own Way (I2C) to Decide Port Controller CC Attach

    return _TYPE_C_UNATTACH;
}
#endif

#if(_PORT_CTRL_USER_DET_ALT_MODE_READY_BY_SMBUS == _ON)
//--------------------------------------------------
// Description  : Get User Port Ctrl Alt Mode Ready Info Through I2C
// Input Value  : enumTypeCPcbPort : _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : CC Attach (_TYPE_C_ALT_MODE_NOT_READY / _TYPE_C_ALT_MODE_READY)
//--------------------------------------------------
EnumTypeCAltModeStatus UserInterfaceUsbTypeCUserGetAltModeReadyByI2C(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // User Can Use Their Own Way (I2C) to Decide Port Controller (DP) Alt Mode Ready

    return _TYPE_C_ALT_MODE_NOT_READY;
}
#endif

//--------------------------------------------------
// Description  : Ask User Port Controller to Reconnect
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : return _TYPE_C_USER_PORT_CTRL_RESP_SUCCESS / _TYPE_C_USER_PORT_CTRL_RESP_FAIL
//--------------------------------------------------
EnumTypeCUserPortCtrlRespStatus UserInterfaceUsbTypeCUserReconnect(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // Kernel ask User Port Controller to Reconnect

    return _TYPE_C_USER_PORT_CTRL_RESP_FAIL;
}

#if(_PORT_CTRL_EXT_DET_ORIENTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get User Port Ctrl Orientation Status
// Input Value  : enumTypeCPcbPort
// Output Value : Orientation (_TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP)
//--------------------------------------------------
EnumTypeCOrientation UserInterfaceUsbTypeCUserGetOrientation(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // User Can Use Their Own Way to Decide Port Controller Orientation, For Example
    // EnumTypeCOrientation = (GPIO == HIGH) ? _TYPE_C_ORIENTATION_UNFLIP : _TYPE_C_ORIENTATION_FLIP;

    return _TYPE_C_ORIENTATION_UNFLIP;
}
#endif

//--------------------------------------------------
// Description  : Get User Port Controller's Pin Assignment When Alt Mode Ready
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : EnumTypeCPinCfgType --> Pin Assignment
//--------------------------------------------------
EnumTypeCPinCfgType UserInterfaceUsbTypeCUesrGetPinAssignment(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // For Kernel to Get User Port Controller's Negotiated Pin Assignment
    // Example:
    /*
    BYTE ucPinAssignment; // User
    EnumTypeCPinCfgType enumTypeCPinAssignment; // Kernel

    ucPinAssignment = UserTypeCPortControllerGetPinAssignment();
    switch(ucPinAssignment(
    {
        case _TYPE_C_PIN_C:
            enumTypeCPinAssignment = _TYPE_C_PIN_ASSIGNMENT_C;
            break;

        case _TYPE_C_PIN_D:
            enumTypeCPinAssignment = _TYPE_C_PIN_ASSIGNMENT_D;
            break;

        case _TYPE_C_PIN_E:
            enumTypeCPinAssignment = _TYPE_C_PIN_ASSIGNMENT_E;
            break;

        case _TYPE_C_PIN_F:
            enumTypeCPinAssignment = _TYPE_C_PIN_ASSIGNMENT_F;
            break;

        default
            enumTypeCPinAssignment = _TYPE_C_PIN_ASSIGNMENT_NONE;
            break;
    }

    return enumTypeCPinAssignment;
    */

    return _TYPE_C_PIN_ASSIGNMENT_C;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl Power Role
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : EnumTypeCPowerRole (_TYPE_C_POWER_ROLE_NONE / _TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC)
//--------------------------------------------------
EnumTypeCPowerRole UserInterfaceUsbTypeCUserGetPowerRole(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // User Can Use Their Own Way to Decide Port Controller Power Role

    return _TYPE_C_POWER_ROLE_NONE;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl Data Role
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : EnumTypeCDataRole (_TYPE_C_DATA_ROLE_NONE / _TYPE_C_UFP_U / _TYPE_C_DFP_U)
//--------------------------------------------------
EnumTypeCDataRole UserInterfaceUsbTypeCUserGetDataRole(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // User Can Use Their Own Way to Decide Port Controller Data Role

    return _TYPE_C_DATA_ROLE_NONE;
}

//--------------------------------------------------
// Description  : Set User-Defined Number of PDOs to User Port Ctrl
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), Number of PDO Counts (1~7)
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUserSetPdoCnt(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt)
{
    enumInputPort = enumInputPort;
    enumPowerRole = enumPowerRole;
    ucPdoCnt = ucPdoCnt;
}

//--------------------------------------------------
// Description  : Set User-Defined Fix Supply/ PPS PDOs to User Port Ctrl
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex, stTypeCUserPdo
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUserSetPdo(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo)
{
    // Fix Supply PDO Voltage (Unit 50mV) and Current (Unit 10mA)
    // PPS PDO Voltage (Unit 100mV) and Current (Unit 50mA)
    enumInputPort = enumInputPort;
    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;
    stTypeCUserPdo = stTypeCUserPdo;
}

//--------------------------------------------------
// Description  : Set User-Defined RDO to User Port Ctrl
// Input Value  : enumTypeCPcbPort, stTypeCUserRdo
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUserSetRdo(EnumInputPort enumInputPort, StructTypeCUserRDO stTypeCUserRdo)
{
    enumInputPort = enumInputPort;
    stTypeCUserRdo = stTypeCUserRdo;
}

//--------------------------------------------------
// Description  : Update CC Function Control to User Port Ctrl (Connect / Disconnect)
// Input Value  : enumTypeCPcbPort, enumCcFunction
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUserCcFunctionControl(EnumInputPort enumInputPort, EnumTypeCCcFunction enumCcFunction)
{
    enumInputPort = enumInputPort;
    enumCcFunction = enumCcFunction;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl Number of Src/Snk PDOs
// Input Value  : enumInputPort, enumPowerRole (Src/Snk PDO)
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
EnumTypeCPdoNumber UserInterfaceUsbTypeCUserGetPdoCnt(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole)
{
    enumInputPort = enumInputPort;
    enumPowerRole = enumPowerRole;

    // For Kernel to Get User Port Controller's Number of Src/Snk PDOs

    return _TYPE_C_PDO_NUM_1;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl Source/Sink PDO Info
// Input Value  : enumInputPort, enumPowerRole (Src/Snk PDO), ucPdoIndex : 1~7
//                pstPDO --> Voltage Unit = 100mV / Current = 10mA
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUserGetPdo(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO *pstPDO)
{
    enumInputPort = enumInputPort;
    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;

    // For Kernel to Get User Port Controller's Source/Sink PDO Info

    // Reset Default Value to Fix PDO w/ 0V @ 0A
    pstPDO->enumPdoType = _PD_FIX_SUPPLY_PDO;
    pstPDO->enumPeakCurrent = _PD_PEAK_CUR_NONE;
    pstPDO->usMaxVoltage = 0x00;
    pstPDO->usMinVoltage = 0x00;
    pstPDO->usMaxCurrent = 0x00;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl Number of Partner Src/Snk PDOs
// Input Value  : enumInputPort, enumPowerRole (Src/Snk PDO)
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
EnumTypeCPdoNumber UserInterfaceUsbTypeCUserGetPartnerPdoCnt(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole)
{
    enumInputPort = enumInputPort;
    enumPowerRole = enumPowerRole;

    // For Kernel to Get User Port Controller's Number of Partner Src/Snk PDOs

    return _TYPE_C_PDO_NUM_1;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl Partner Source/Sink PDO Info
// Input Value  : enumInputPort, enumPowerRole (Src/Snk PDO), ucPdoIndex : 1~7
//                pstPartnerPDO --> Voltage Unit = 100mV / Current = 10mA
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUserGetPartnerPdo(EnumInputPort enumInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO *pstPartnerPDO)
{
    enumInputPort = enumInputPort;
    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;

    // For Kernel to Get User Port Controller's Partner Source/Sink PDO Info

    // Reset Default Value to Fix PDO w/ 0V @ 0A
    pstPartnerPDO->enumPdoType = _PD_FIX_SUPPLY_PDO;
    pstPartnerPDO->enumPeakCurrent = _PD_PEAK_CUR_NONE;
    pstPartnerPDO->usMaxVoltage = 0x00;
    pstPartnerPDO->usMinVoltage = 0x00;
    pstPartnerPDO->usMaxCurrent = 0x00;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl PDO Status
// Input Value  : enumInputPort, *pusVoltage (Unit: 10mV), *pusCurrent (Unit: 10mA)
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUserGetPdoStatus(EnumInputPort enumInputPort, WORD *pusVoltage, WORD *pusCurrent)
{
    enumInputPort = enumInputPort;

    // For Kernel to Get User Port Controller's PDO Status
    *pusVoltage = 0;
    *pusCurrent = 0;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl Current Source PDO that Sink Request
// Input Value  : enumInputPort
//                pstSrcPDO --> Voltage Unit = 100mV / Current = 10mA
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUserGetRequestedSrcPdo(EnumInputPort enumInputPort, StructTypeCUserPDO *pstSrcPDO)
{
    enumInputPort = enumInputPort;

    // For Kernel to Get User Port Controller's Source PDO that Sink Request

    // Reset Default Value to Fix PDO w/ 0V @ 0A
    pstSrcPDO->enumPdoType = _PD_FIX_SUPPLY_PDO;
    pstSrcPDO->enumPeakCurrent = _PD_PEAK_CUR_NONE;
    pstSrcPDO->usMaxVoltage = 0x00;
    pstSrcPDO->usMinVoltage = 0x00;
    pstSrcPDO->usMaxCurrent = 0x00;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl's FW Version
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
//                *pstTypeCFwVersion --> TypeC FW Version
// Output Value : return _TYPE_C_USER_PORT_CTRL_RESP_SUCCESS / _TYPE_C_USER_PORT_CTRL_RESP_FAIL
//--------------------------------------------------
EnumTypeCUserPortCtrlRespStatus UserInterfaceUsbTypeCUserGetFwVersion(EnumInputPort enumInputPort, StructTypeCPortCtrlFwVersion *pstTypeCFwVersion)
{
    enumInputPort = enumInputPort;
    pstTypeCFwVersion = pstTypeCFwVersion;

    // For Kernel to Get User Port Controller's FW Version
    return _TYPE_C_USER_PORT_CTRL_RESP_FAIL;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl's Cable Info for DPCD
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
//              : *pstTypeCCableInfoForDpcd --> Actvie/Passive Cable, DP Max Rate, UHBR13.5 Support
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUserGetCableInfoForDpcd(EnumInputPort enumInputPort, StructTypeCCableInfoForDpcd *pstTypeCCableInfoForDpcd)
{
    enumInputPort = enumInputPort;

    // User Can Use Their Own Way to Decide Port Controller DPCP Cable Info
    pstTypeCCableInfoForDpcd->enumTypeCCableActiveComponent = _PD_CBL_COMPONENT_PASSIVE;
    pstTypeCCableInfoForDpcd->enumTypeCCableMaxDpRate = _PD_CBL_MAX_DP_RATE_UNCONFIRMED;
    pstTypeCCableInfoForDpcd->b1CableUhbr13p5Support = _FALSE;
}

//--------------------------------------------------
// Description  : Set User Port Ctrl's Pin Assignment when U3 OFF/ON Change
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : return _TYPE_C_USER_PORT_CTRL_RESP_SUCCESS / _TYPE_C_USER_PORT_CTRL_RESP_FAIL
//--------------------------------------------------
EnumTypeCUserPortCtrlRespStatus UserInterfaceUsbTypeCUserConfigPinAssignment(EnumInputPort enumInputPort, EnumTypeCPinCfgCapType enumPinAssignment)
{
    enumInputPort = enumInputPort;
    enumPinAssignment = enumPinAssignment;

    // For Kernel to Config User Port Controller's Pin Assignment when OSD U3 OFF/ON Change

    return _TYPE_C_USER_PORT_CTRL_RESP_FAIL;
}

//--------------------------------------------------
// Description  : Set User Port Ctrl's Multi-Function Bit when U3 OFF/ON Change
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT.
// Output Value : return _TYPE_C_USER_PORT_CTRL_RESP_SUCCESS / _TYPE_C_USER_PORT_CTRL_RESP_FAIL
//--------------------------------------------------
EnumTypeCUserPortCtrlRespStatus UserInterfaceUsbTypeCUserConfigMultiFunction(EnumInputPort enumInputPort, EnumTypeCMultiFuncStatus enumMultiFunction)
{
    enumInputPort = enumInputPort;
    enumMultiFunction = enumMultiFunction;

    // For Kernel to Config User Port Controller's Multi-Function Bit when OSD U3 OFF/ON Change

    return _TYPE_C_USER_PORT_CTRL_RESP_FAIL;
}

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
//--------------------------------------------------
// Description  : Get User Port Controller Lenovo Alt Mode Ready Info
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : Lenovo Alt Mode Ready Status (_TYPE_C_LENOVO_ALT_MODE_READY / _TYPE_C_LENOVO_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCLenovoAltModeStatus UserInterfaceUsbTypeCUserGetLenovoAltModeReady(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    // User Can Use Their Own Way to Decide Port Controller Lenovo Alt Mode Ready or Not, For Example
    // Lenovo Alt Mode Entered ? _TYPE_C_LENOVO_ALT_MODE_READY : _TYPE_C_LENOVO_ALT_MODE_NOT_READY;

    return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
}

//--------------------------------------------------
// Description  : Get Port Partner Lenovo Device Type from User Port Controller
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType UserInterfaceUsbTypeCUserGetLenovoDeviceType(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event (Including System Acknowledge)
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
//                stLenovoSysEvent --> Lenovo System Event
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUserGetLenovoSystemEvent(EnumInputPort enumInputPort, StructTypeCLenovoSysEvent *pstLenovoSysEvent)
{
    enumInputPort = enumInputPort;
    *pstLenovoSysEvent = *pstLenovoSysEvent;

    // Reset Default Value to Lenovo System Event
    pstLenovoSysEvent->enumSystemPowerMode = _TYPE_C_LENOVO_SYS_DC_MODE;
    pstLenovoSysEvent->enumSystemState = _TYPE_C_LENOVO_SYS_STATE_NONE;
    pstLenovoSysEvent->b1SystemEvent = _FALSE;
    pstLenovoSysEvent->b3SystemReserved = 0x00;
    pstLenovoSysEvent->ucSystemAcknowlegde = 0x00;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Set Docking Event
// Input Value  : enumInputPort, stLenovoDockEvent
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCUserSetLenovoDockingEvent(EnumInputPort enumInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    enumInputPort = enumInputPort;
    stLenovoDockEvent = stLenovoDockEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : enumInputPort --> _D0_INPUT_PORT / _D1_INPUT_PORT...
// Output Value : Docking Event Check Busy Result (_TYPE_C_LENOVO_DOCK_EVENT_BUSY / _TYPE_C_LENOVO_DOCK_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCLenovoCheckBusyResult UserInterfaceUsbTypeCUserCheckLenovoDockingEventBusy(EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    return _TYPE_C_LENOVO_DOCK_EVENT_NOT_BUSY;
}
#endif // End of #if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#endif // End of #if(_PORT_CTRL_USER_SERIES_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get TypeC PDO Reference
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//              : enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : _TYPE_C_PDO_FROM_KERNEL / _TYPE_C_PDO_FROM_USER
//--------------------------------------------------
EnumTypeCPdoReference UserInterfaceUsbTypeCPdoReference(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
        case _D1_TYPE_C_PORT:
        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:

            if(enumPowerRole == _TYPE_C_POWER_SRC)
            {
                // Source Capability Default Defined By User
                return _TYPE_C_PDO_FROM_KERNEL;
            }
            else if(enumPowerRole == _TYPE_C_POWER_SNK)
            {
                // Sink Capability Default Difined By Kernel
                return _TYPE_C_PDO_FROM_KERNEL;
            }

            break;

        default:
            break;
    }
    return _TYPE_C_PDO_FROM_KERNEL;
}

//--------------------------------------------------
// Description  : Get TypeC RDO Reference
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
// Output Value : _TYPE_C_RDO_FROM_KERNEL / _TYPE_C_RDO_FROM_USER
//--------------------------------------------------
EnumTypeCRdoReference UserInterfaceUsbTypeCRdoReference(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
        case _D1_TYPE_C_PORT:
        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:

            // Kernel Default Request 5V @ 500mA
            return _TYPE_C_RDO_FROM_KERNEL;

            break;

        default:
            break;
    }
    return _TYPE_C_RDO_FROM_KERNEL;
}

//--------------------------------------------------
// Description  : Port Controller Max Power
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
// Output Value : return Max Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserInterfaceUsbTypeCGetMaxPower(EnumTypeCPcbPort enumTypeCPcbPort)
{
    WORD usTypeCMaxPower = 0;

    // ===============================
    // Allocate Port Power
    // ===============================
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

            usTypeCMaxPower = 270; // Power = 270 * 0.1 = 27W

            break;

        case _D1_TYPE_C_PORT:

            usTypeCMaxPower = 270; // Power = 270 * 0.1 = 27W

            break;

        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        default:

            // Default Max Power = 270 * 0.1 = 27W
            usTypeCMaxPower = 270;

            break;
    }

    return usTypeCMaxPower;
}

//--------------------------------------------------
// Description  : Port Controller Available Power
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
// Output Value : return Max Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserInterfaceUsbTypeCGetAvailablePower(EnumTypeCPcbPort enumTypeCPcbPort, WORD usMaxPower)
{
    WORD usTypeCMaxPower = 0;

    // ===============================
    // Allocate Port Power
    // ===============================
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

            if(UserCommonUsbTypeCSpmOperation() == _TYPE_C_SPM_FIX_DEFAULT_POWER)
            {
                usTypeCMaxPower = usMaxPower;
            }
            else
            {
                usTypeCMaxPower = GET_SYSTEM_REMAIN_POWER() + GET_TYPE_C_POWER_VALUE(_D0_TYPE_C_PORT);

                if(usTypeCMaxPower >= usMaxPower)
                {
                    usTypeCMaxPower = usMaxPower;
                }
            }

            SET_TYPE_C_POWER_VALUE(_D0_TYPE_C_PORT, usTypeCMaxPower);

            DebugMessageTypeC("- D0_Available_Power(0.1W)", usTypeCMaxPower);

            break;

        case _D1_TYPE_C_PORT:

            if(UserCommonUsbTypeCSpmOperation() == _TYPE_C_SPM_FIX_DEFAULT_POWER)
            {
                usTypeCMaxPower = usMaxPower;
            }
            else
            {
                usTypeCMaxPower = GET_SYSTEM_REMAIN_POWER() + GET_TYPE_C_POWER_VALUE(_D1_TYPE_C_PORT);

                if(usTypeCMaxPower >= usMaxPower)
                {
                    usTypeCMaxPower = usMaxPower;
                }
            }

            SET_TYPE_C_POWER_VALUE(_D1_TYPE_C_PORT, usTypeCMaxPower);

            DebugMessageTypeC("- D1_Available_Power(0.1W)", usTypeCMaxPower);

            break;

        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        default:

            // Default Max Power
            usTypeCMaxPower = usMaxPower;

            break;
    }

    return usTypeCMaxPower;
}

//--------------------------------------------------
// Description  : Port Controller Sink Information
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//                *pstTypeCSnkInfo --> Sink Information
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCGetSnkInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCSnkInfo *pstTypeCSnkInfo)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

            // Sink Minimum PDP (150 * 0.1 = 15W) : Minimum Power Required by the Sink.
            // Note : Sink Minimum PDP Shall be less than or equal to the Sink Operational PDP.
            pstTypeCSnkInfo->usSnkMinPDP = 150;

            // Sink Operational PDP (150 * 0.1 = 15W) : Manufacturer Recommended PDP of the Sink.
            pstTypeCSnkInfo->usSnkOpePDP = 150;

            // Sink Maximum PDP (270 * 0.1 = 27W) : Highest Amount of Power the Sink Consumes Under Any Operating Condition.
            // Note : Sink Maximum PDP Shall Not be less than the Sink Operational PDP.
            pstTypeCSnkInfo->usSnkMaxPDP = 270;

            break;

        case _D1_TYPE_C_PORT:

            // Sink Minimum PDP (150 * 0.1 = 15W) : Minimum Power Required by the Sink.
            // Note : Sink Minimum PDP Shall be less than or equal to the Sink Operational PDP.
            pstTypeCSnkInfo->usSnkMinPDP = 150;

            // Sink Operational PDP (150 * 0.1 = 15W) : Manufacturer Recommended PDP of the Sink.
            pstTypeCSnkInfo->usSnkOpePDP = 150;

            // Sink Maximum PDP (270 * 0.1 = 27W) : Highest Amount of Power the Sink Consumes Under Any Operating Condition.
            // Note : Sink Maximum PDP Shall Not be less than the Sink Operational PDP.
            pstTypeCSnkInfo->usSnkMaxPDP = 270;

            break;

        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        default:

            // Default Sink Power Requirement
            pstTypeCSnkInfo->usSnkMinPDP = 150;
            pstTypeCSnkInfo->usSnkOpePDP = 150;
            pstTypeCSnkInfo->usSnkMaxPDP = 270;

            break;
    }
}

//--------------------------------------------------
// Description  : Port Controller SPR PDO Count
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//              : enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : return Number of SPR PDOs (from 0 ~ 7)
//--------------------------------------------------
EnumTypeCPdoNumber UserInterfaceUsbTypeCGetPdoCount(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    EnumTypeCPdoNumber enumPdoCount = _TYPE_C_PDO_NUM_1;

    // User can use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create ucHubDeviceCnt logic
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

            if(enumPowerRole == _TYPE_C_POWER_SRC)
            {
                // User Can Define Different Max Power According to Device Count
#if(_D0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                // Adjust PDO count by avaliale power
                // If Available Power < 27W, 1 Fix PDO : 5V@3A and 1 PPS PDO 3.3V~5.9V@3A
                // If Available Power >= 27W, 2 Fix PDO : 5V@3A / 9V@3A and 1 PPS PDO 3.3V~5.9V@3A
                enumPdoCount = ((GET_TYPE_C_POWER_VALUE(_D0_TYPE_C_PORT) < 270) ? _TYPE_C_PDO_NUM_2 : _TYPE_C_PDO_NUM_3);
#else
                // Adjust PDO count by avaliale power
                // If Available Power < 27W, 1 Fix PDO : 5V@3A
                // If Available Power >= 27W, 2 Fix PDO : 5V@3A / 9V@3A
                enumPdoCount = ((GET_TYPE_C_POWER_VALUE(_D0_TYPE_C_PORT) < 270) ? _TYPE_C_PDO_NUM_1 : _TYPE_C_PDO_NUM_2);
#endif
            }
            else if(enumPowerRole == _TYPE_C_POWER_SNK)
            {
                // Set Number of Sink PDOs, Example : 2 Sink PDOs
                // [MM1AE-3035] For Lecroy TEST.PD.PS.SNK.01 Issue, Vbus Powered Sink Must Set At Least 2 Sink PDOs
                enumPdoCount = _TYPE_C_PDO_NUM_2;
            }

            break;

        case _D1_TYPE_C_PORT:

            if(enumPowerRole == _TYPE_C_POWER_SRC)
            {
                // User Can Define Different Max Power According to Device Count
#if(_D1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                // Adjust PDO count by avaliale power
                // If Available Power < 27W, 1 Fix PDO : 5V@3A and 1 PPS PDO 3.3V~5.9V@3A
                // If Available Power >= 27W, 2 Fix PDO : 5V@3A / 9V@3A and 1 PPS PDO 3.3V~5.9V@3A
                enumPdoCount = ((GET_TYPE_C_POWER_VALUE(_D1_TYPE_C_PORT) < 270) ? _TYPE_C_PDO_NUM_2 : _TYPE_C_PDO_NUM_3);
#else
                // Adjust PDO count by avaliale power
                // If Available Power < 27W, 1 Fix PDO : 5V@3A
                // If Available Power >= 27W, 2 Fix PDO : 5V@3A / 9V@3A
                enumPdoCount = ((GET_TYPE_C_POWER_VALUE(_D1_TYPE_C_PORT) < 270) ? _TYPE_C_PDO_NUM_1 : _TYPE_C_PDO_NUM_2);
#endif
            }
            else if(enumPowerRole == _TYPE_C_POWER_SNK)
            {
                // Set Number of Sink PDOs, Example : 2 Sink PDOs
                // [MM1AE-3035] For Lecroy TEST.PD.PS.SNK.01 Issue, Vbus Powered Sink Must Set At Least 2 Sink PDOs
                enumPdoCount = _TYPE_C_PDO_NUM_2;
            }

            break;

        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:

            if(enumPowerRole == _TYPE_C_POWER_SRC)
            {
                // User Can Define Different Max Power According to Device Count
                enumPdoCount = _TYPE_C_PDO_NUM_2;
            }
            else if(enumPowerRole == _TYPE_C_POWER_SNK)
            {
                // Set Number of Sink PDOs, Example : 2 Sink PDOs
                // [MM1AE-3035] For Lecroy TEST.PD.PS.SNK.01 Issue, Vbus Powered Sink Must Set At Least 2 Sink PDOs
                enumPdoCount = _TYPE_C_PDO_NUM_2;
            }

            break;

        case _ADAPTOR_TYPE_C_PORT:
        default:

            enumPdoCount = _TYPE_C_PDO_NUM_2;

            break;
    }

    // Default 2 Fix PDO (5V/3A, 9V/3A)
    return enumPdoCount;
}

#if(_PORT_CTRL_PD3_1_EPR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Port Controller EPR PDO Count
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//              : enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : return Number of EPR PDOs (from 0 ~ 4)
//--------------------------------------------------
EnumTypeCPdoNumber UserInterfaceUsbTypeCGetEPRPdoCount(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    EnumTypeCPdoNumber enumPdoCount = _TYPE_C_PDO_NUM_0;

    // User can use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create ucHubDeviceCnt logic
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

            if(enumPowerRole == _TYPE_C_POWER_SRC)
            {
                // User Can Define Different Max Power According to Device Count
                // Adjust PDO count by avaliale power
                // If Available Power > 100W & <= 140W, 1 Fix EPR PDO : 28V@(PDP/28)A and 1 AVS PDO 15V~28V@(PDP/AVS Voltage)A
                if((GET_TYPE_C_POWER_VALUE(_D0_TYPE_C_PORT) > 1000) && (GET_TYPE_C_POWER_VALUE(_D0_TYPE_C_PORT) <= 1400))
                {
                    enumPdoCount = _TYPE_C_PDO_NUM_2;
                }
            }
            else if(enumPowerRole == _TYPE_C_POWER_SNK)
            {
                // Warning !!! TypeC do not support EPR Sink, EPR Sink PDO count should be 0 !!!
                enumPdoCount = _TYPE_C_PDO_NUM_0;
            }

            break;

        case _D1_TYPE_C_PORT:

            if(enumPowerRole == _TYPE_C_POWER_SRC)
            {
                // User Can Define Different Max Power According to Device Count
                // Adjust PDO count by avaliale power
                // If Available Power > 100W & <= 140W, 1 Fix EPR PDO : 28V@(PDP/28)A and 1 AVS PDO 15V~28V@(PDP/AVS Voltage)A
                if((GET_TYPE_C_POWER_VALUE(_D1_TYPE_C_PORT) > 1000) && (GET_TYPE_C_POWER_VALUE(_D1_TYPE_C_PORT) <= 1400))
                {
                    enumPdoCount = _TYPE_C_PDO_NUM_2;
                }
            }
            else if(enumPowerRole == _TYPE_C_POWER_SNK)
            {
                // Warning !!! TypeC do not support EPR Sink, EPR Sink PDO count should be 0 !!!
                enumPdoCount = _TYPE_C_PDO_NUM_0;
            }

            break;

        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:
        default:

            enumPdoCount = _TYPE_C_PDO_NUM_0;

            break;
    }

    // Default 0 EPR PDO
    return enumPdoCount;
}
#endif

//--------------------------------------------------
// Description  : Kernel Get Port Controller Src PDO Info
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//                ucPdoIndex --> PDO Index
//                *pstTypeCUserSrcPdo --> Src PDO Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCGetSrcPdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserSrcPdo)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

            switch(ucPdoIndex)
            {
                // =============================== WARNING ===============================
                // 1st PDO Must Be Fix Supply PDO @ 5V
                // ALL PDO Type Must Be In Order : Fix -> PPS
                // ALL PDO Voltage in Same Type Must Be In Order : Lowest To Highest
                // User Can Define Different PDO According to Device Count
                // =======================================================================

                case _TYPE_C_PDO_NUM_1:

                    // -------------------- 1st Source PDO --------------------
                    // PDO Type = Fix Supply PDO, Must Be 5V (Max = 5A)
                    // Peak Current Only for Source Fix Supply PDO & AVS PDO, And enumPeakCurrent Could Not Be _PD_PEAK_CUR_NONE Only When FW_OCP Enabled
                    // Max Voltage (Unit = 100mV) : 50 * 100mV = 5V
                    // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSrcPdo->enumPeakCurrent = _PD_PEAK_CUR_NONE;
                    pstTypeCUserSrcPdo->usMaxVoltage = 50;
                    pstTypeCUserSrcPdo->usMaxCurrent = 300;

                    break;

                case _TYPE_C_PDO_NUM_2:

                    // Adjust PDO by avaliale power
#if(_D0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    if(GET_TYPE_C_POWER_VALUE(_D0_TYPE_C_PORT) < 270) // Available Power < 27W
                    {
                        // -------------------- 2nd Source PDO --------------------
                        // Index = 2
                        // PDO Type = Programmable PDO (5V PPS PDO = 3.3V ~ 5.9V / 9V PPS PDO = 3.3V ~ 11V)
                        // Min Voltage (Unit = 100mV) : 33 * 100mV = 3.3V
                        // Max Voltage (Unit = 100mV) : 59 * 100mV = 5.9V
                        // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                        // User Shall Set Max Current Value in Units of 50 mA, otherwise Value Will be Truncated
                        // --------------------------------------------------------
                        pstTypeCUserSrcPdo->enumPdoType = _PD_3_PROGRAMMABLE_PDO;
                        pstTypeCUserSrcPdo->usMinVoltage = 33;
                        pstTypeCUserSrcPdo->usMaxVoltage = 59;
                        pstTypeCUserSrcPdo->usMaxCurrent = 300;
                    }
                    else
#endif
                    {
                        // -------------------- 2nd Source PDO --------------------
                        // PDO Type = Fix Supply PDO (Max = 20V / 5A)
                        // Peak Current Only for Source Fix Supply PDO & AVS PDO, And enumPeakCurrent Could Not Be _PD_PEAK_CUR_NONE Only When FW_OCP Enabled
                        // Max Voltage (Unit = 100mV) : 90 * 100mV = 9V
                        // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                        // --------------------------------------------------------
                        pstTypeCUserSrcPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                        pstTypeCUserSrcPdo->enumPeakCurrent = _PD_PEAK_CUR_NONE;
                        pstTypeCUserSrcPdo->usMaxVoltage = 90;
                        pstTypeCUserSrcPdo->usMaxCurrent = 300;
                    }

                    break;

                case _TYPE_C_PDO_NUM_3:

#if(_D0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    // -------------------- 3rd Source PDO --------------------
                    // Index = 3
                    // PDO Type = Programmable PDO (5V PPS PDO = 3.3V ~ 5.9V / 9V PPS PDO = 3.3V ~ 11V)
                    // Min Voltage (Unit = 100mV) : 33 * 100mV = 3.3V
                    // Max Voltage (Unit = 100mV) : 59 * 100mV = 5.9V
                    // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                    // User Shall Set Max Current Value in Units of 50 mA, otherwise Value Will be Truncated
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_3_PROGRAMMABLE_PDO;
                    pstTypeCUserSrcPdo->usMinVoltage = 33;
                    pstTypeCUserSrcPdo->usMaxVoltage = 59;
                    pstTypeCUserSrcPdo->usMaxCurrent = 300;
#endif
                    break;

                case _TYPE_C_PDO_NUM_4:
                case _TYPE_C_PDO_NUM_5:
                case _TYPE_C_PDO_NUM_6:
                case _TYPE_C_PDO_NUM_7:

                    break;

#if((_D0_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) || (_D0_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON))
                case _TYPE_C_PDO_NUM_8:

                    // -------------------- 8st Source PDO --------------------
                    // Index = 8
                    // PDO Type = Fix Supply EPR PDO
                    // Peak Current Only for Source Fix Supply PDO & AVS PDO, And enumPeakCurrent Could Not Be _PD_PEAK_CUR_NONE Only When FW_OCP Enabled
                    // Max Voltage (Unit = 100mV) : 280 * 100mV = 28V
                    // Max Current (Unit = 10mA)  : 500 *  10mA = 5A
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSrcPdo->enumPeakCurrent = _PD_PEAK_CUR_NONE;
                    pstTypeCUserSrcPdo->usMaxVoltage = 280;
                    pstTypeCUserSrcPdo->usMaxCurrent = 500;

                    break;

                case _TYPE_C_PDO_NUM_9:

                    // -------------------- 9st Source PDO --------------------
                    // Index = 9
                    // PDO Type = AVS EPR PDO (28V AVS PDO = 15V ~ 28V)
                    // Peak Current Only for Source Fix Supply PDO & AVS PDO, And enumPeakCurrent Could Not Be _PD_PEAK_CUR_NONE Only When FW_OCP Enabled
                    // Min Voltage (Unit = 100mV) : 150 * 100mV = 15V
                    // Max Voltage (Unit = 100mV) : 280 * 100mV = 28V
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_3_1_ADJUSTABLE_PDO;
                    pstTypeCUserSrcPdo->enumPeakCurrent = _PD_PEAK_CUR_NONE;
                    pstTypeCUserSrcPdo->usMinVoltage = 150;
                    pstTypeCUserSrcPdo->usMaxVoltage = 280;

                    break;

                case _TYPE_C_PDO_NUM_10:
                case _TYPE_C_PDO_NUM_11:

                    break;
#endif

                default:

                    break;
            }

            break;

        case _D1_TYPE_C_PORT:

            switch(ucPdoIndex)
            {
                // =============================== WARNING ===============================
                // 1st PDO Must Be Fix Supply PDO @ 5V
                // ALL PDO Type Must Be In Order : Fix -> PPS
                // ALL PDO Voltage in Same Type Must Be In Order : Lowest To Highest
                // User Can Define Different PDO According to Device Count
                // =======================================================================

                case _TYPE_C_PDO_NUM_1:

                    // -------------------- 1st Source PDO --------------------
                    // PDO Type = Fix Supply PDO, Must Be 5V (Max = 5A)
                    // Peak Current Only for Source Fix Supply PDO & AVS PDO, And enumPeakCurrent Could Not Be _PD_PEAK_CUR_NONE Only When FW_OCP Enabled
                    // Max Voltage (Unit = 100mV) : 50 * 100mV = 5V
                    // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSrcPdo->enumPeakCurrent = _PD_PEAK_CUR_NONE;
                    pstTypeCUserSrcPdo->usMaxVoltage = 50;
                    pstTypeCUserSrcPdo->usMaxCurrent = 300;

                    break;

                case _TYPE_C_PDO_NUM_2:

                    // Adjust PDO by avaliale power
#if(_D1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    if(GET_TYPE_C_POWER_VALUE(_D1_TYPE_C_PORT) < 270) // Available Power < 27W
                    {
                        // -------------------- 2nd Source PDO --------------------
                        // Index = 2
                        // PDO Type = Programmable PDO (5V PPS PDO = 3.3V ~ 5.9V / 9V PPS PDO = 3.3V ~ 11V)
                        // Min Voltage (Unit = 100mV) : 33 * 100mV = 3.3V
                        // Max Voltage (Unit = 100mV) : 59 * 100mV = 5.9V
                        // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                        // User Shall Set Max Current Value in Units of 50 mA, otherwise Value Will be Truncated
                        // --------------------------------------------------------
                        pstTypeCUserSrcPdo->enumPdoType = _PD_3_PROGRAMMABLE_PDO;
                        pstTypeCUserSrcPdo->usMinVoltage = 33;
                        pstTypeCUserSrcPdo->usMaxVoltage = 59;
                        pstTypeCUserSrcPdo->usMaxCurrent = 300;
                    }
                    else
#endif
                    {
                        // -------------------- 2nd Source PDO --------------------
                        // PDO Type = Fix Supply PDO (Max = 20V / 5A)
                        // Peak Current Only for Source Fix Supply PDO & AVS PDO, And enumPeakCurrent Could Not Be _PD_PEAK_CUR_NONE Only When FW_OCP Enabled
                        // Max Voltage (Unit = 100mV) : 90 * 100mV = 9V
                        // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                        // --------------------------------------------------------
                        pstTypeCUserSrcPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                        pstTypeCUserSrcPdo->enumPeakCurrent = _PD_PEAK_CUR_NONE;
                        pstTypeCUserSrcPdo->usMaxVoltage = 90;
                        pstTypeCUserSrcPdo->usMaxCurrent = 300;
                    }

                    break;

                case _TYPE_C_PDO_NUM_3:

#if(_D1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    // -------------------- 3rd Source PDO --------------------
                    // Index = 3
                    // PDO Type = Programmable PDO (5V PPS PDO = 3.3V ~ 5.9V / 9V PPS PDO = 3.3V ~ 11V)
                    // Min Voltage (Unit = 100mV) : 33 * 100mV = 3.3V
                    // Max Voltage (Unit = 100mV) : 59 * 100mV = 5.9V
                    // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                    // User Shall Set Max Current Value in Units of 50 mA, otherwise Value Will be Truncated
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_3_PROGRAMMABLE_PDO;
                    pstTypeCUserSrcPdo->usMinVoltage = 33;
                    pstTypeCUserSrcPdo->usMaxVoltage = 59;
                    pstTypeCUserSrcPdo->usMaxCurrent = 300;
#endif
                    break;

                case _TYPE_C_PDO_NUM_4:
                case _TYPE_C_PDO_NUM_5:
                case _TYPE_C_PDO_NUM_6:
                case _TYPE_C_PDO_NUM_7:

                    break;

#if((_D1_TYPE_C_EMB_PD3_1_EPR_SUPPORT == _ON) || (_D1_TYPE_C_EXT_PD3_1_EPR_SUPPORT == _ON))
                case _TYPE_C_PDO_NUM_8:

                    // -------------------- 8st Source PDO --------------------
                    // Index = 8
                    // PDO Type = Fix Supply EPR PDO
                    // Peak Current Only for Source Fix Supply PDO & AVS PDO, And enumPeakCurrent Could Not Be _PD_PEAK_CUR_NONE Only When FW_OCP Enabled
                    // Max Voltage (Unit = 100mV) : 280 * 100mV = 28V
                    // Max Current (Unit = 10mA)  : 500 *  10mA = 5A
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSrcPdo->enumPeakCurrent = _PD_PEAK_CUR_NONE;
                    pstTypeCUserSrcPdo->usMaxVoltage = 280;
                    pstTypeCUserSrcPdo->usMaxCurrent = 500;

                    break;

                case _TYPE_C_PDO_NUM_9:

                    // -------------------- 9st Source PDO --------------------
                    // Index = 9
                    // PDO Type = AVS EPR PDO (28V AVS PDO = 15V ~ 28V)
                    // Peak Current Only for Source Fix Supply PDO & AVS PDO, And enumPeakCurrent Could Not Be _PD_PEAK_CUR_NONE Only When FW_OCP Enabled
                    // Min Voltage (Unit = 100mV) : 150 * 100mV = 15V
                    // Max Voltage (Unit = 100mV) : 280 * 100mV = 28V
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_3_1_ADJUSTABLE_PDO;
                    pstTypeCUserSrcPdo->enumPeakCurrent = _PD_PEAK_CUR_NONE;
                    pstTypeCUserSrcPdo->usMinVoltage = 150;
                    pstTypeCUserSrcPdo->usMaxVoltage = 280;

                    break;

                case _TYPE_C_PDO_NUM_10:
                case _TYPE_C_PDO_NUM_11:

                    break;
#endif

                default:

                    break;
            }

            break;

        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        default:

            switch(ucPdoIndex)
            {
                case _TYPE_C_PDO_NUM_1:

                    // -------------------- 1st Source PDO --------------------
                    // PDO Type = Fix Supply PDO, Must Be 5V (Max = 5A)
                    // Peak Current Only for Source Fix Supply PDO
                    // Max Voltage (Unit = 100mV) : 50 * 100mV = 5V
                    // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSrcPdo->enumPeakCurrent = _PD_PEAK_CUR_NONE;
                    pstTypeCUserSrcPdo->usMaxVoltage = 50;
                    pstTypeCUserSrcPdo->usMaxCurrent = 300;

                    break;

                case _TYPE_C_PDO_NUM_2:

                    // -------------------- 2nd Source PDO --------------------
                    // PDO Type = Fix Supply PDO (Max = 20V / 5A)
                    // Peak Current Only for Source Fix Supply PDO
                    // Max Voltage (Unit = 100mV) : 90 * 100mV = 9V
                    // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserSrcPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSrcPdo->enumPeakCurrent = _PD_PEAK_CUR_NONE;
                    pstTypeCUserSrcPdo->usMaxVoltage = 90;
                    pstTypeCUserSrcPdo->usMaxCurrent = 300;

                    break;

                case _TYPE_C_PDO_NUM_3:
                case _TYPE_C_PDO_NUM_4:
                case _TYPE_C_PDO_NUM_5:
                case _TYPE_C_PDO_NUM_6:
                case _TYPE_C_PDO_NUM_7:
                default:

                    break;
            }

            break;
    }
}

//--------------------------------------------------
// Description  : Kernel Get Port Controller Snk PDO Info
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//                ucPdoIndex --> PDO Index
//                *pstTypeCUserSrcPdo --> Snk PDO Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCGetSnkPdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserSnkPdo)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
        case _D1_TYPE_C_PORT:
        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:

            switch(ucPdoIndex)
            {
                // =============================== WARNING ===============================
                // 1st PDO Must Be Fix Supply PDO @ 5V
                // ALL PDO Type Must Be In Order : Fix -> PPS
                // ALL PDO Voltage in Same Type Must Be In Order : Lowest To Highest
                // User Can Define Different PDO According to Device Count
                // =======================================================================

                case _TYPE_C_PDO_NUM_1:

                    // --------------------- 1st Sink PDO ---------------------
                    // PDO Type = Fix Supply PDO, Must Be 5V (Max = 5A)
                    // Max Voltage (Unit = 100mV) : 50 * 100mV = 5V
                    // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserSnkPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSnkPdo->usMaxVoltage = 50;
                    pstTypeCUserSnkPdo->usMaxCurrent = 300;

                    break;

                case _TYPE_C_PDO_NUM_2:

                    // --------------------- 2nd Sink PDO ---------------------
                    // PDO Type = Fix Supply PDO (Max = 20V / 5A)
                    // Max Voltage (Unit = 100mV) : 90 * 100mV = 9V
                    // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
                    // --------------------------------------------------------
                    pstTypeCUserSnkPdo->enumPdoType = _PD_FIX_SUPPLY_PDO;
                    pstTypeCUserSnkPdo->usMaxVoltage = 90;
                    pstTypeCUserSnkPdo->usMaxCurrent = 300;

                    break;

                case _TYPE_C_PDO_NUM_3:
                case _TYPE_C_PDO_NUM_4:
                case _TYPE_C_PDO_NUM_5:
                case _TYPE_C_PDO_NUM_6:
                case _TYPE_C_PDO_NUM_7:
                default:

                    break;
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Kernel Get Port Controller Initial Request Info When There is No Contract
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//                *pstTypeCUserInitRdo --> Initial Request Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCGetInitRdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserInitRDO *pstTypeCUserInitRdo)
{
    // --------------------------------- NOTE ---------------------------------
    // This is the Initial Request Info that User can Set when There is No Contract.
    // If User Set pstTypeCUserRdo->enumReqType to _TYPE_C_REQ_LOWEST_VOL or
    // _TYPE_C_REQ_HIGHEST_VOL, then No Need to Set pstTypeCUserRdo->enumTargetVolRDO.
    // If User Set pstTypeCUserRdo->enumReqType to _TYPE_C_REQ_TARGET_VOL,
    // then MUST be Set pstTypeCUserRdo->enumTargetVolRDO.
    // [MM1AE-3035] For Lecroy TEST.PD.PS.SNK.01 Issue, Vbus Powered Sink Must Request PDO Other Than 5V.
    // ------------------------------------------------------------------------

    // Set Default Initial Request Info
    pstTypeCUserInitRdo->enumReqType = _TYPE_C_REQ_CUSTOMIZED_RDO;
    pstTypeCUserInitRdo->enumTargetVolRDO = _TYPE_C_RDO_NO_TARGET;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
        case _D1_TYPE_C_PORT:
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
}

//--------------------------------------------------
// Description  : Kernel Get Port Controller Snk PDO Info
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//                *pstTypeCUserRdo --> Request Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCGetRdoInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO *pstTypeCUserRdo)
{
    // ============================== EXAMPLE ================================
    // User can Use "SysUsbTypeCGetPartnerPdoCnt" to Get Num of PDO Source Provided
    // User can Use "SysUsbTypeCGetPartnerPdo" to Read Each PDO Info
    // User can Use "SysUsbTypeCGetPdoStatus" to Get Current PDO Status
    // 1. If 9V @ 2A Exist, Request 9V @ 2A
    // 2. If 9V Exist, But Current < 2A, Request 9V @ Max Cur Source can Provide
    // 3. If 9V Not Exist (or Not Receive Src cAP), Request 5V @ 500mA
    // =======================================================================

    BYTE ucPartnerPdoCnt = SysUsbTypeCGetPartnerPdoCnt(enumTypeCPcbPort, _TYPE_C_POWER_SRC);
    BYTE ucPdoIndex = 0x00;
    StructTypeCUserPDO stTypeCPartnerPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 50, 50, 50};

    // Set Default Request 5V @ 500mA
    pstTypeCUserRdo->enumObjPos = _TYPE_C_PDO_NUM_1; // 1st RDO Must Be 5V Fix
    pstTypeCUserRdo->usReqInfo1 = 50;                // Fix RDO : Op. Cur in 10mA / PPS RDO : Vol in 20mV / AVS RDO (Vol in 25mV)
    pstTypeCUserRdo->usReqInfo2 = 50;                // Fix RDO : Max. Cur in 10mA / PPS RDO : Op.Cur in 50mA / AVS RDO (Op. Cur in 50mA)

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
        case _D1_TYPE_C_PORT:
        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:

            if(ucPartnerPdoCnt != 0x00)
            {
                // If PDO Count NOT 0 (Already Receive PDO from Source), Check PDO Info
                for(ucPdoIndex = 1; ucPdoIndex <= ucPartnerPdoCnt; ucPdoIndex++)
                {
                    // Get Partner Source PDO Info (enumPdoType = PDO Type, usMaxVoltage = Vol in 100mV, usMaxCurrent = Cur in 10mA)
                    stTypeCPartnerPdo = SysUsbTypeCGetPartnerPdo(enumTypeCPcbPort, _TYPE_C_POWER_SRC, ucPdoIndex);

                    // Search if Any PDO Match Fix Supply 9V (90 * 100mV)
                    if((stTypeCPartnerPdo.enumPdoType == _PD_FIX_SUPPLY_PDO) && (stTypeCPartnerPdo.usMaxVoltage == 90))
                    {
                        // Set Obj Pos to 9V PDO
                        pstTypeCUserRdo->enumObjPos = ucPdoIndex;

                        // Check if Current Meet 2A (200 * 10mA)
                        if(stTypeCPartnerPdo.usMaxCurrent >= 200)
                        {
                            // Set Request Op. Cur and Max. Cur = 200 * 10mA = 2A
                            pstTypeCUserRdo->usReqInfo1 = 200;
                            pstTypeCUserRdo->usReqInfo2 = 200;
                        }
                        else
                        {
                            // Set Request Op. Cur and Max. Cur to Source Max Current in 9V PDO
                            pstTypeCUserRdo->usReqInfo1 = stTypeCPartnerPdo.usMaxCurrent;
                            pstTypeCUserRdo->usReqInfo2 = stTypeCPartnerPdo.usMaxCurrent;
                        }
                    }
                }
            }

            // Set Capability Mismatch if Not Able to Meet Target Request (9V @ 2A)
            if((pstTypeCUserRdo->enumObjPos == _TYPE_C_PDO_NUM_1) || (pstTypeCUserRdo->usReqInfo1 != 200))
            {
                pstTypeCUserRdo->b1CapMismatch = _TRUE;
            }
            else
            {
                pstTypeCUserRdo->b1CapMismatch = _FALSE;
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Kernel Get TypeC Unconstrained Power Status
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
// Output Value : _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST / _TYPE_C_UNCONSTRAIN_POWER_EXIST
//--------------------------------------------------
EnumTypeCUnconstrainPowerExist UserInterfaceUsbTypeCGetUnconstrainedPow(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // --------------------------------- NOTE ---------------------------------
    // 1. The Definition of the Unconstrained Power means that System has enough Power
    // to Provide to the Port Partner.
    // 2. According to the Unconstrained Power Status, Kernel will Determine whether
    // to Send PR_SWAP or not.
    // For Example, if D0 Port is set to _TYPE_C_UNCONSTRAIN_POWER_EXIST and the Current
    // Power Role is Sink, then Kernel will Try to Send PR_SWAP to Become Power Source.
    // 3. In General, if System is Powered by Adapator, then User just Needs to
    // Determine the Unconstrained Power Status based on Local Power Status.
    // 4. If there are other Special Applications, such as Cin-Cout Portable Monitor,
    // then User can Customize the Unconstrained Power Status according to the Different Situation.
    // ------------------------------------------------------------------------

    // =======================================================================
    // User can Use "SysUsbTypeCGetLocPowExist" to Get Local Power (Adaptor or Power Board) Status
    // User can Use "SysUsbTypeCGetPowerRole" to Get Port's Power Role
    // User can Use "SysUsbTypeCGetPdoStatus" to Get Port's PDO Status
    // User can Use "SysUsbTypeCGetPartnerPdo" to Get Port Partner Source/Sink PDO Info
    // =======================================================================

    EnumTypeCUnconstrainPowerExist enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
        case _D1_TYPE_C_PORT:
        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        case _ADAPTOR_TYPE_C_PORT:

#if(_TYPE_C_POWER_SOURCE == _TYPE_C_SELF_POWER_ONLY)
            // System is Powered by Adapator
            // Use "SysUsbTypeCGetLocPowExist" to Determine the Unconstrained Power Status.
            if(SysUsbTypeCGetLocPowExist() == _TYPE_C_LOCAL_POWER_EXIST)
            {
                enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_EXIST;
            }
            else if(SysUsbTypeCGetLocPowExist() == _TYPE_C_LOCAL_POWER_NOT_EXIST)
            {
                enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST;
            }
#elif(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
            // System is Powered by Vbus
            if((_TYPE_C_PORT_VALID - 1) <= 0x01)
            {
                // If there is only One TypeC Port, this Port is Sink Only and cannot Become Source through PR_Swap.
                enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST;
            }
            else
            {
                // If there are more than One TypeC Ports,
                // then User can Customize the Unconstrained Power Status according to the Different Situation.
                enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST;

                /* Example :
                if((Power obtained by other ports from Vbus) >= (Power required by the system) + (the Power of Sink_Cap of D0 Port Partner))
                {
                    enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_EXIST;
                }
                else
                {
                    enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST;
                }
                */
            }
#elif(_TYPE_C_POWER_SOURCE == _TYPE_C_SELF_AND_VBUS_POWER)
            // System Works From Both Adaptor and Vbus Power
            if(SysUsbTypeCGetLocPowExist() == _TYPE_C_LOCAL_POWER_EXIST)
            {
                // If Local Power Exists, then Set _TYPE_C_UNCONSTRAIN_POWER_EXIST.
                enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_EXIST;
            }
            else
            {
                // If Local Power does't Exists, then Need to Confirm whether Other Ports have Power from Vbus.
                if((_TYPE_C_PORT_VALID - 1) <= 0x01)
                {
                    // If there is only One TypeC Port and No Local Power, System has No Extra Power to Provide to Port Partner.
                    enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST;
                }
                else
                {
                    // If there are more than One TypeC Ports,
                    // then User can Customize the Unconstrained Power Status according to the Different Situation.
                    enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST;

                    /* Example :
                    if((Power obtained by other ports from Vbus) >= (Power required by the system) + (the Power of Sink_Cap of D0 Port Partner))
                    {
                        enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_EXIST;
                    }
                    else
                    {
                        enumTypeCUPExist = _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST;
                    }
                    */
                }
            }
#endif
            break;

        default:
            break;
    }

    return enumTypeCUPExist;
}

//--------------------------------------------------
// Description  : System Power Management Operation Behavior
// Input Value  : None
// Output Value : _TYPE_C_SPM_FIX_DEFAULT_POWER / _TYPE_C_SPM_ADJUST_DYNAMIC_POWER
//--------------------------------------------------
EnumTypeCSpmOperation UserInterfaceUsbTypeCSpmOperation(void)
{
    // ---------------------- NOTE -----------------------
    // If user don't want to use SPM, then set the return
    // value to "_TYPE_C_SPM_FIX_DEFAULT_POWER" and the
    // SPM will do only 1-time in the initial.
    // ---------------------------------------------------

    return _TYPE_C_SPM_FIX_DEFAULT_POWER;
}

//--------------------------------------------------
// Description  : System Power Management Calculation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCSystemPowerManagement(void)
{
    // Max Power Range From 0 ~ 100W
    BYTE ucIndex = 0;
    WORD usAvailablePower = 0;
    WORD usSystemMaxPower = 0;
    WORD usUsbDevicePower = 0;
    WORD usTypeCAttachMinPower = 0;
    WORD usSystemRemainPower = 0;
    WORD usTempPortPower = 0;
    WORD usPortMinPower = 0;
    EnumTypeCPcbPort enumTypeCAltPowerPort = _NO_TYPE_C_PORT;

    // ===============================
    // Start System Power Management
    // ===============================
    DebugMessageTypeC("[SPM] <Start>", 0x00);

    // ------------------------------------------
    // 1. Get Local or Available Power
    // ------------------------------------------
    usAvailablePower = UserCommonUsbTypeCGetAvailablePower(&enumTypeCAltPowerPort);

    DebugMessageTypeC("- Power Source", enumTypeCAltPowerPort);
    DebugMessageTypeC("- Local_Power(0.1W)", usAvailablePower);

    // ------------------------------------------
    // 2. Default System Power = 120 * 0.1 = 12W
    // ------------------------------------------
    usSystemMaxPower = 120;

    DebugMessageTypeC("- System_Power(0.1W)", usSystemMaxPower);

    // ------------------------------------------
    // 3. Check USB Device Power
    // ------------------------------------------
    usUsbDevicePower = UserCommonUsbTypeCGetHubPower();

    DebugMessageTypeC("- USB_Power(0.1W)", usUsbDevicePower);

    // ------------------------------------------
    // 4. Check Min Power for Type-C Port Attach
    // ------------------------------------------
    for(ucIndex = 0; ucIndex < (_TYPE_C_PORT_VALID - 1); ++ucIndex)
    {
        // Reserve Minimum Power for Each Type-C Port
        usTypeCAttachMinPower += UserCommonUsbTypeCGetPortMinPower(g_penumUsbTypeCPcbPort[ucIndex]);
    }

    DebugMessageTypeC("- Type-C Attach Min Power(0.1W)", usTypeCAttachMinPower);

    // ------------------------------------------
    // 5. System Power Management Calculation
    // ------------------------------------------

    // 5-1. Calculate System Power
    usSystemRemainPower = ((usAvailablePower > usSystemMaxPower) ? (usAvailablePower - usSystemMaxPower) : 0);

    // 5-2. Calculate USB Device Power
    usSystemRemainPower = ((usSystemRemainPower > usUsbDevicePower) ? (usSystemRemainPower - usUsbDevicePower) : 0);

    // 5-3. Calculate Min Power for Type-C Port Attach
    usSystemRemainPower = ((usSystemRemainPower > usTypeCAttachMinPower) ? (usSystemRemainPower - usTypeCAttachMinPower) : 0);

    // 5-4. Calculate Type-C Power for each port
    for(ucIndex = 0; ucIndex < (_TYPE_C_PORT_VALID - 1); ++ucIndex)
    {
        usTempPortPower = UserCommonUsbTypeCGetPortPower(g_penumUsbTypeCPcbPort[ucIndex]);
        usPortMinPower = UserCommonUsbTypeCGetPortMinPower(g_penumUsbTypeCPcbPort[ucIndex]);

        DebugMessageTypeC("- Type-C_Port", g_penumUsbTypeCPcbPort[ucIndex]);
        DebugMessageTypeC("- Port_Power(0.1W)", usTempPortPower);

        if((usTempPortPower != 0) && (SysUsbTypeCGetPowerRole(g_penumUsbTypeCPcbPort[ucIndex]) == _TYPE_C_POWER_SRC))
        {
            // If type-c port attached in source
            SET_TYPE_C_POWER_VALUE(g_penumUsbTypeCPcbPort[ucIndex], ((usTempPortPower > usPortMinPower) ? usTempPortPower : usPortMinPower));
        }
        else
        {
            // Reserve Min Power with Unattached Status for DRP
            if(enumTypeCAltPowerPort != g_penumUsbTypeCPcbPort[ucIndex])
            {
                SET_TYPE_C_POWER_VALUE(g_penumUsbTypeCPcbPort[ucIndex], usPortMinPower);
            }
        }

        // Min Power Compensation
        usSystemRemainPower += usPortMinPower;

        // Decrease total power via type-c power usage
        if(usSystemRemainPower >= GET_TYPE_C_POWER_VALUE(g_penumUsbTypeCPcbPort[ucIndex]))
        {
            usSystemRemainPower = usSystemRemainPower - GET_TYPE_C_POWER_VALUE(g_penumUsbTypeCPcbPort[ucIndex]);
        }
        else
        {
            // Decrease type-c power usage if Max Power is not enough
            SET_TYPE_C_POWER_VALUE(g_penumUsbTypeCPcbPort[ucIndex], usPortMinPower);

            if(usSystemRemainPower < usPortMinPower)
            {
                usSystemRemainPower = 0;
            }
            else
            {
                usSystemRemainPower = usSystemRemainPower - GET_TYPE_C_POWER_VALUE(g_penumUsbTypeCPcbPort[ucIndex]);
            }
        }

        DebugMessageTypeC("- Port_Power_New(0.1W)", GET_TYPE_C_POWER_VALUE(g_penumUsbTypeCPcbPort[ucIndex]));
    }

    // ------------------------------------------
    // 5. Store System Remaining Power
    // ------------------------------------------
    SET_SYSTEM_REMAIN_POWER(usSystemRemainPower);

    DebugMessageTypeC("- Remain_Power(0.1W)", GET_SYSTEM_REMAIN_POWER());

    DebugMessageTypeC("[SPM] <End>", 0x00);
}

//--------------------------------------------------
// Description  : Get Adaptor Available Power
// Input Value  : None
// Output Value : return Adaptor Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserInterfaceUsbTypeCGetAdaptorPower(void)
{
    WORD usAdaptorPower = 0;

    // Default Adaptor Power = 600 * 0.1 = 60W
    usAdaptorPower = 600;

    return usAdaptorPower;
}

//--------------------------------------------------
// Description  : Get Hub Controller Power Usage
// Input Value  : None
// Output Value : return Max Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserInterfaceUsbTypeCGetHubPower(void)
{
    WORD usUsbDevicePower = 0;

#if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
#if(_USB_RTS_SMBUS_SUPPORT == _ON)
    BYTE ucUsbAttachNumber = 0;
    EnumHubDspDeviceAttachDetect enumUsbAttachType = _HUB_DSP_DEVICE_NOT_ATTACH;

    // --------------------------
    // Check DSP 0 Attach Power
    // --------------------------
    if(UserCommonUsbTypeCGetBillboardSupport(_HUB_DSP0) == _USB_BB_DISABLE)
    {
#if(_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
        enumUsbAttachType = UserCommonUsbHubRtsDspGetUsbAttachInfo(_HUB_DSP0);
#else
        enumUsbAttachType = _HUB_DSP_DEVICE_NOT_ATTACH;
#endif

        if(enumUsbAttachType == _HUB_DSP_DEVICE_ATTACH_BY_U2)
        {
            // U2 device consumes 2.5W
            usUsbDevicePower += 25;

            ucUsbAttachNumber++;
        }
        else if(enumUsbAttachType == _HUB_DSP_DEVICE_ATTACH_BY_U3)
        {
            // U3 device consumes 4.5W
            usUsbDevicePower += 45;

            ucUsbAttachNumber++;
        }
    }

    // --------------------------
    // Check DSP 1 Attach Power
    // --------------------------
    if(UserCommonUsbTypeCGetBillboardSupport(_HUB_DSP1) == _USB_BB_DISABLE)
    {
#if(_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
        enumUsbAttachType = UserCommonUsbHubRtsDspGetUsbAttachInfo(_HUB_DSP1);
#else
        enumUsbAttachType = _HUB_DSP_DEVICE_NOT_ATTACH;
#endif

        if(enumUsbAttachType == _HUB_DSP_DEVICE_ATTACH_BY_U2)
        {
            // U2 device consumes 2.5W
            usUsbDevicePower += 25;

            ucUsbAttachNumber++;
        }
        else if(enumUsbAttachType == _HUB_DSP_DEVICE_ATTACH_BY_U3)
        {
            // U3 device consumes 4.5W
            usUsbDevicePower += 45;

            ucUsbAttachNumber++;
        }
    }

    // --------------------------
    // Check DSP 2 Attach Power
    // --------------------------
    if(UserCommonUsbTypeCGetBillboardSupport(_HUB_DSP2) == _USB_BB_DISABLE)
    {
#if(_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
        enumUsbAttachType = UserCommonUsbHubRtsDspGetUsbAttachInfo(_HUB_DSP2);
#else
        enumUsbAttachType = _HUB_DSP_DEVICE_NOT_ATTACH;
#endif

        if(enumUsbAttachType == _HUB_DSP_DEVICE_ATTACH_BY_U2)
        {
            // U2 device consumes 2.5W
            usUsbDevicePower += 25;

            ucUsbAttachNumber++;
        }
        else if(enumUsbAttachType == _HUB_DSP_DEVICE_ATTACH_BY_U3)
        {
            // U3 device consumes 4.5W
            usUsbDevicePower += 45;

            ucUsbAttachNumber++;
        }
    }

    // --------------------------
    // Check DSP 3 Attach Power
    // --------------------------
    if(UserCommonUsbTypeCGetBillboardSupport(_HUB_DSP3) == _USB_BB_DISABLE)
    {
#if(_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
        enumUsbAttachType = UserCommonUsbHubRtsDspGetUsbAttachInfo(_HUB_DSP3);
#else
        enumUsbAttachType = _HUB_DSP_DEVICE_NOT_ATTACH;
#endif

        if(enumUsbAttachType == _HUB_DSP_DEVICE_ATTACH_BY_U2)
        {
            // U2 device consumes 2.5W
            usUsbDevicePower += 25;

            ucUsbAttachNumber++;
        }
        else if(enumUsbAttachType == _HUB_DSP_DEVICE_ATTACH_BY_U3)
        {
            // U3 device consumes 4.5W
            usUsbDevicePower += 45;

            ucUsbAttachNumber++;
        }
    }

    // --------------------------
    // Reserved 4.5W for 1 port
    // --------------------------
    usUsbDevicePower += ((ucUsbAttachNumber <= _HUB_DSP3) ? 45 : 0);
#endif
#endif

    return usUsbDevicePower;
}

//--------------------------------------------------
// Description  : Get Billboard Support Port
// Input Value  : EnumHubDsp --> _HUB_DSP0 ~ _HUB_DSP3
// Output Value : _USB_BB_ENABLE / _USB_BB_DISABLE
//--------------------------------------------------
EnumBillboardCtrl UserInterfaceUsbTypeCGetBillboardSupport(EnumHubDsp enumHubDsp)
{
    EnumBillboardCtrl enumBillboardCtrl = _USB_BB_DISABLE;

    // =========================================
    // User should define which down-string port
    // supports Billboard
    // =========================================

#if(_BILLBOARD_SUPPORT == _ON)
    switch(enumHubDsp)
    {
        case _HUB_DSP0:

            // Down-String Port 0 Support Billboard
            enumBillboardCtrl = _USB_BB_ENABLE;

            break;

        case _HUB_DSP1:
        case _HUB_DSP2:
        case _HUB_DSP3:
        default:

            // Other Port Not Support Billboard
            enumBillboardCtrl = _USB_BB_DISABLE;

            break;
    }
#endif

    return enumBillboardCtrl;
}

#if((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Embedded Port Controller Vbus Protect By User / Kernel
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
// Output Value : _TYPE_C_VBUS_PROTECT_BY_KERNEL / _TYPE_C_VBUS_PROTECT_BY_USER
//--------------------------------------------------
EnumTypeCEmbVbusProtectReference UserInterfaceUsbTypeCEmbeddedGetVbusProtectReference(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // User can use "UserCommonUsbHubGetDspInfo(_HUB_DSP0)" to Create ucHubDeviceCnt logic
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
        case _D1_TYPE_C_PORT:
        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:

            // User Can Define Different Vbus Protect Settings (ex, OCP)
            return _TYPE_C_VBUS_PROTECT_BY_KERNEL;

            break;

        default:
            break;
    }

    return _TYPE_C_VBUS_PROTECT_BY_KERNEL;
}

//--------------------------------------------------
// Description  : Embedded Port Controller User-Defined Vbus Protect Info
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
//                ucPdoIndex --> PDO Index
//                *pstTypeCVbusProtectInfo --> Vbus Protect Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceUsbTypeCEmbeddedGetVbusProtectInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCVbusProtectInfo *pstTypeCVbusProtectInfo)
{
    // User can use "UserCommonUsbHubGetDspInfo()" to Create ucHubDeviceCnt logic
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
        case _D1_TYPE_C_PORT:
        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        default:

            switch(ucPdoIndex)
            {
                case _TYPE_C_PDO_NUM_1:
                case _TYPE_C_PDO_NUM_2:
                case _TYPE_C_PDO_NUM_3:
                case _TYPE_C_PDO_NUM_4:
                case _TYPE_C_PDO_NUM_5:
                case _TYPE_C_PDO_NUM_6:
                case _TYPE_C_PDO_NUM_7:
                case _TYPE_C_PDO_NUM_8:
                case _TYPE_C_PDO_NUM_9:
                case _TYPE_C_PDO_NUM_10:
                case _TYPE_C_PDO_NUM_11:
                default:

                    // User-Defined Vbus Protect Settings

                    // Vbus OCP ratio, Unit: %
                    pstTypeCVbusProtectInfo->ucOcpCurRatio = 105;

                    // Vbus Debounce Time for Protection Judgment before protection trigger
                    // Each debounce time is between 160us ~ 220us
                    // Note: This debounce time only effects on ADC_Related protection!
                    pstTypeCVbusProtectInfo->ucOvpDebounce = 0;
                    pstTypeCVbusProtectInfo->ucUvpDebounce = 0;
                    pstTypeCVbusProtectInfo->ucOcpDebounce = 0;

                    // Vbus OCP Calculation Include Peak Current or not
                    pstTypeCVbusProtectInfo->enumPeakCurrentProtect = _TYPE_C_PEAK_CURRENT_PROTECT_ENABLE;

                    break;
            }

            break;
    }
}

//--------------------------------------------------
// Description  : Embedded Port Controller User-Defined Vbus Discharge Count
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT
// Output Value : return DischargeCount(5 ~ 40)
//--------------------------------------------------
BYTE UserInterfaceUsbTypeCEmbeddedGetVbusDischargeCount(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDischargeCount = 0;

    // =========================================
    // Recommend NOT to set counter over 40
    // Otherwise, CTS will fail in this item:
    // TD 4.5.4 DRP Connect DRP Test
    // =========================================

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

            ucDischargeCount = 20;

            break;

        case _D1_TYPE_C_PORT:

            ucDischargeCount = 20;

            break;

        case _D2_TYPE_C_PORT:
        case _P0_TYPE_C_PORT:
        case _P1_TYPE_C_PORT:
        case _P2_TYPE_C_PORT:
        case _P3_TYPE_C_PORT:
        case _P4_TYPE_C_PORT:
        default:

            // Default Counter
            ucDischargeCount = 20;

            break;
    }

    return ucDischargeCount;
}

#if(_LOCAL_POWER_VBUS_ADC_CHANNEL == _TYPE_C_PMIC_ADC_MAPPING_NONE)
//--------------------------------------------------
// Description  : Kernel Get TypeC Local Power Status
// Input Value  : None
// Output Value : _TYPE_C_LOCAL_POWER_NOT_EXIST / _TYPE_C_LOCAL_POWER_EXIST
//--------------------------------------------------
EnumTypeCLocalPowerExist UserInterfaceUsbTypeCGetLocalPow(void)
{
    // --------------------------------- NOTE ---------------------------------
    // The Definition of the Local Power means that System is Powered by Adapator.
    // ------------------------------------------------------------------------

    EnumTypeCLocalPowerExist enumTypeCLPExist = _TYPE_C_LOCAL_POWER_NOT_EXIST;

    return enumTypeCLPExist;
}
#endif
#endif // End of #if((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON))

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User inform Kernel Eanble BB While BB_Program
// Input Value  : EnumTypeCPcbPort
// Output Value : _USB_BB_PROGRAM_DISABLE / _USB_BB_PROGRAM_ENABLE
//--------------------------------------------------
EnumBillboardProgramCtrl UserInterfaceUsbTypeCBBProgramEnable(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // Here: User Enable / Disable BillBoard For Processing BB_Program
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

#if(_USB_HUB_SUPPORT == _ON)
    switch(enumInputPort)
    {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_USB_HUB_SUPPORT == _ON))
        case _D0_INPUT_PORT:

            if(GET_USER_USB_HUB_SWITCH_TO_INPUT_INDEX() == _D0_INPUT_PORT)
            {
                // Enable BB After AltMode Ready While _USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON
                if(SysUsbTypeCRxGetAltModeReady(_D0_INPUT_PORT) == _TRUE)
                {
                    return _USB_BB_PROGRAM_ENABLE;
                }
                else
                {
                    return _USB_BB_PROGRAM_DISABLE;
                }
            }
            else
            {
                return _USB_BB_PROGRAM_DISABLE;
            }

            break;
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_USB_HUB_SUPPORT == _ON))
        case _D1_INPUT_PORT:

            if(GET_USER_USB_HUB_SWITCH_TO_INPUT_INDEX() == _D1_INPUT_PORT)
            {
                // Enable BB After AltMode Ready While _USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON
                if(SysUsbTypeCRxGetAltModeReady(_D1_INPUT_PORT) == _TRUE)
                {
                    return _USB_BB_PROGRAM_ENABLE;
                }
                else
                {
                    return _USB_BB_PROGRAM_DISABLE;
                }
            }
            else
            {
                return _USB_BB_PROGRAM_DISABLE;
            }

            break;

#endif

        default:

            return _USB_BB_PROGRAM_DISABLE;

            break;
    }

    return _USB_BB_PROGRAM_DISABLE;
#else
    // Enable BB After AltMode Ready While _USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON
    if(SysUsbTypeCRxGetAltModeReady(enumInputPort) == _TRUE)
    {
        return _USB_BB_PROGRAM_ENABLE;
    }
    else
    {
        return _USB_BB_PROGRAM_DISABLE;
    }
#endif
}

//--------------------------------------------------
// Description  : User Get Kernel BB Custom Command While BB_Program
// Input Value  : pststUsbBillboardCustomCommandInfo
// Output Value : NONE
//--------------------------------------------------
void UserInterfaceUsbTypeCBBCustomCommand(StructUsbBillboardCustomCommandInfo *pststUsbBillboardCustomCommandInfo)
{
    // Here: Using BB Custom Commad to Maintain User Application
    // https://wiki.realtek.com/pages/viewpage.action?pageId=435036857
    pststUsbBillboardCustomCommandInfo->ucwValue_Low = pststUsbBillboardCustomCommandInfo->ucwValue_Low;
    pststUsbBillboardCustomCommandInfo->ucwValue_High = pststUsbBillboardCustomCommandInfo->ucwValue_High;
    pststUsbBillboardCustomCommandInfo->ucwIndex_Low = pststUsbBillboardCustomCommandInfo->ucwIndex_Low;
    pststUsbBillboardCustomCommandInfo->ucwIndex_High = pststUsbBillboardCustomCommandInfo->ucwIndex_High;
    pststUsbBillboardCustomCommandInfo->ucwLength_Low = pststUsbBillboardCustomCommandInfo->ucwLength_Low;
    pststUsbBillboardCustomCommandInfo->ucwLength_High = pststUsbBillboardCustomCommandInfo->ucwLength_High;

    if((UserCommonUsbTypeCBBGetCustomEvent() & _BB_CUSTOM_EVENT_ERROR) != _BB_CUSTOM_EVENT_ERROR)
    {
        if((UserCommonUsbTypeCBBGetCustomEvent() & _BB_CUSTOM_EVENT_00) == _BB_CUSTOM_EVENT_00)
        {
            // Here: User defines the corresponding functions based on the Custom Command definition.


            // Clear Custom_Event_00 Flag to Complete the Kernel/User Handshake
            UserCommonUsbTypeCBBClrCustomEvent(_BB_CUSTOM_EVENT_00);
        }
        else if(UserCommonUsbTypeCBBGetCustomEvent() != _BB_CUSTOM_EVENT_NONE)
        {
            DebugMessageTypeC("10.[USB BB][Warning] Please note that Custom_Event01-06 are not yet supported.", UserCommonUsbTypeCBBGetCustomEvent());
        }
    }
    else
    {
        DebugMessageTypeC("10.[USB BB][BB_Program_User] Custom Event Handling Conflict", UserCommonUsbTypeCBBGetCustomEvent());

        // Clear Custom Event Error Flag
        UserCommonUsbTypeCBBClrCustomEvent(_BB_CUSTOM_EVENT_ERROR);

        if(UserCommonUsbTypeCBBGetCustomEvent() != _BB_CUSTOM_EVENT_NONE)
        {
            DebugMessageTypeC("10.[USB BB][BB_Program_User] Reset All Custom Event Change Flag", UserCommonUsbTypeCBBGetCustomEvent());

            // Reset Custom Event Flag
            UserCommonUsbTypeCBBClrCustomEvent(_BB_CUSTOM_EVENT_RESET);
        }
    }
}
#endif // End of #if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
#endif // End of #if(_BILLBOARD_SCALER_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

