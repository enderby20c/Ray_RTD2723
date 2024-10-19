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
// ID Code      : UserCommonUsbTypeCUser.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_PORTCONTROLLERUSER__

#include "UserCommonInclude.h"
#include "UsbTypeCUser/UserCommonUsbTypeCUser.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_PORT_CTRL_USER_DET_CC_ATTACH_BY_SMBUS == _ON)
//--------------------------------------------------
// Description  : Get User Port Ctrl CC Attached Info Through I2C
// Input Value  : enumTypeCPcbPort : _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : CC Attach (_TYPE_C_UNATTACH / _TYPE_C_ATTACH)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonUsbTypeCUserGetCcAttachByI2C(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    return UserInterfaceUsbTypeCUserGetCcAttachByI2C(enumInputPort);
}
#endif

#if(_PORT_CTRL_USER_DET_ALT_MODE_READY_BY_SMBUS == _ON)
//--------------------------------------------------
// Description  : Get User Port Ctrl Alt Mode Ready Info Through I2C
// Input Value  : enumTypeCPcbPort : _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : CC Attach (_TYPE_C_ALT_MODE_NOT_READY / _TYPE_C_ALT_MODE_READY)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonUsbTypeCUserGetAltModeReadyByI2C(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    return UserInterfaceUsbTypeCUserGetAltModeReadyByI2C(enumInputPort);
}
#endif

//--------------------------------------------------
// Description  : Ask User Port Controller to Reconnect
// Input Value  : enumInputPort --> Input Port
// Output Value : return  _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonUsbTypeCUserReconnect(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    if(UserInterfaceUsbTypeCUserReconnect(enumInputPort) == _TYPE_C_USER_PORT_CTRL_RESP_SUCCESS)
    {
        return _SUCCESS;
    }

    return _FAIL;
}

#if(_PORT_CTRL_EXT_DET_ORIENTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get User Port Ctrl Orientation Status
// Input Value  : enumTypeCPcbPort
// Output Value : Orientation (_TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP)
//--------------------------------------------------
EnumTypeCOrientation UserCommonUsbTypeCUserGetOrientation(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    return UserInterfaceUsbTypeCUserGetOrientation(enumInputPort);
}
#endif

//--------------------------------------------------
// Description  : Get User Port Ctrl Pin Assignment and Return Result
// Input Value  : enumTypeCPcbPort / penumPinAssignment pointer
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonUsbTypeCUserGetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    EnumTypeCPinCfgType enumPinCfgType = _TYPE_C_PIN_ASSIGNMENT_C;
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    // Read User Port Controller Alt Mode Pin Assignment Info
    enumPinCfgType = UserInterfaceUsbTypeCUesrGetPinAssignment(enumInputPort);

    if(enumPinCfgType == _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        DebugMessageTypeC("8. Get User Port Controller Pin Assignment Type Fail", 0);

        return _FAIL;
    }

    *penumPinAssignment = enumPinCfgType;

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl Power Role and Return Result
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCPowerRole (_TYPE_C_POWER_ROLE_NONE / _TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC)
//--------------------------------------------------
EnumTypeCPowerRole UserCommonUsbTypeCUserGetPowerRole(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    return UserInterfaceUsbTypeCUserGetPowerRole(enumInputPort);
}

//--------------------------------------------------
// Description  : Get User Port Ctrl Data Role and Return Result
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCDataRole (_TYPE_C_DATA_ROLE_NONE / _TYPE_C_UFP_U / _TYPE_C_DFP_U)
//--------------------------------------------------
EnumTypeCDataRole UserCommonUsbTypeCUserGetDataRole(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    return UserInterfaceUsbTypeCUserGetDataRole(enumInputPort);
}

//--------------------------------------------------
// Description  : Set User-Defined Number of PDOs to User Port Ctrl
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), Number of PDO Counts (1~7)
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCUserSetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    UserInterfaceUsbTypeCUserSetPdoCnt(enumInputPort, enumPowerRole, ucPdoCnt);
}

//--------------------------------------------------
// Description  : Set User-Defined Fix Supply/ PPS PDOs to User Port Ctrl
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex, stTypeCUserPdo
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCUserSetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    UserInterfaceUsbTypeCUserSetPdo(enumInputPort, enumPowerRole, ucPdoIndex, stTypeCUserPdo);
}

//--------------------------------------------------
// Description  : Set User-Defined RDO to User Port Ctrl
// Input Value  : enumTypeCPcbPort, stTypeCUserRdo
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCUserSetRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO stTypeCUserRdo)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    UserInterfaceUsbTypeCUserSetRdo(enumInputPort, stTypeCUserRdo);
}

//--------------------------------------------------
// Description  : Update CC Function Control to User Port Ctrl (Connect / Disconnect)
// Input Value  : enumTypeCPcbPort, enumCcFunction
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCUserCcFunctionControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCcFunction enumCcFunction)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    UserInterfaceUsbTypeCUserCcFunctionControl(enumInputPort, enumCcFunction);
}

//--------------------------------------------------
// Description  : Get User Port Controller Number of Src/Snk PDOs
// Input Value  : enumTypeCPcbPort, enumPowerRole (Src/Snk PDO)
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
EnumTypeCPdoNumber UserCommonUsbTypeCUserGetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    return UserInterfaceUsbTypeCUserGetPdoCnt(enumInputPort, enumPowerRole);
}

//--------------------------------------------------
// Description  : Get User Port Controller Source/Sink PDO Info
// Input Value  : enumTypeCPcbPort, enumPowerRole (Src/Snk PDO), ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonUsbTypeCUserGetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    UserInterfaceUsbTypeCUserGetPdo(enumInputPort, enumPowerRole, ucPdoIndex, &stTypeCPdo);

    return stTypeCPdo;
}

//--------------------------------------------------
// Description  : Get User Port Controller Number of Partner Src/Snk PDOs
// Input Value  : enumTypeCPcbPort, enumPowerRole (Src/Snk PDO)
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
EnumTypeCPdoNumber UserCommonUsbTypeCUserGetPartnerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    return UserInterfaceUsbTypeCUserGetPartnerPdoCnt(enumInputPort, enumPowerRole);
}

//--------------------------------------------------
// Description  : Get User Port Controller Partner Source/Sink PDO Info
// Input Value  : enumTypeCPcbPort, enumPowerRole (Src/Snk PDO), ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonUsbTypeCUserGetPartnerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPartnerPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    UserInterfaceUsbTypeCUserGetPartnerPdo(enumInputPort, enumPowerRole, ucPdoIndex, &stTypeCPartnerPdo);

    return stTypeCPartnerPdo;
}

//--------------------------------------------------
// Description  : Get User Port Controller PDO Status
// Input Value  : enumTypeCPcbPort, *pusVoltage (Unit: 10mV), *pusCurrent (Unit: 10mA)
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCUserGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    UserInterfaceUsbTypeCUserGetPdoStatus(enumInputPort, pusVoltage, pusCurrent);
}

//--------------------------------------------------
// Description  : Get User Port Controller Current Source PDO that Sink Request
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonUsbTypeCUserGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructTypeCUserPDO stTypeCSrcPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    UserInterfaceUsbTypeCUserGetRequestedSrcPdo(enumInputPort, &stTypeCSrcPdo);

    return stTypeCSrcPdo;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl FW Version and Return Result
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
//                *pstTypeCFwVersion --> TypeC FW Version
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonUsbTypeCUserGetFwVersion(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCPortCtrlFwVersion *pstTypeCFwVersion)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    if(UserInterfaceUsbTypeCUserGetFwVersion(enumInputPort, pstTypeCFwVersion) == _TYPE_C_USER_PORT_CTRL_RESP_SUCCESS)
    {
        return _SUCCESS;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Get User Port Ctrl Cable Info for DPCD
// Input Value  : enumTypeCPcbPort --> _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : Actvie/Passive Cable, DP Max Rate, UHBR13.5 Support
//--------------------------------------------------
StructTypeCCableInfoForDpcd UserCommonUsbTypeCUserGetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd = {_PD_CBL_COMPONENT_PASSIVE, _PD_CBL_MAX_DP_RATE_UNCONFIRMED, _FALSE};
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    UserInterfaceUsbTypeCUserGetCableInfoForDpcd(enumInputPort, &stTypeCCableInfoForDpcd);

    return stTypeCCableInfoForDpcd;
}

//--------------------------------------------------
// Description  : Config Pin Assignment to User Port Controller
// Input Value  : enumTypeCPcbPort
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCUserConfigPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgCapType enumPinAssignment)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    if(UserInterfaceUsbTypeCUserConfigPinAssignment(enumInputPort, enumPinAssignment) == _TYPE_C_USER_PORT_CTRL_RESP_SUCCESS)
    {
        return _SUCCESS;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Config Multi-Function Bit to User Port Controller
// Input Value  : enumTypeCPcbPort
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCUserConfigMultiFunction(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCMultiFuncStatus enumMultiFunction)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    if(UserInterfaceUsbTypeCUserConfigMultiFunction(enumInputPort, enumMultiFunction) == _TYPE_C_USER_PORT_CTRL_RESP_SUCCESS)
    {
        return _SUCCESS;
    }

    return _FAIL;
}

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
//--------------------------------------------------
// Description  : Get User Port Controller Lenovo Alt Mode Ready Info
// Input Value  : enumTypeCPcbPort
// Output Value : Lenovo Alt Mode Ready Status (_TYPE_C_LENOVO_ALT_MODE_READY / _TYPE_C_LENOVO_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCLenovoAltModeStatus UserCommonUsbTypeCUserGetLenovoAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    return UserInterfaceUsbTypeCUserGetLenovoAltModeReady(enumInputPort);
}

//--------------------------------------------------
// Description  : Get Port Partner Lenovo Device Type from User Port Controller
// Input Value  : enumTypeCPcbPort
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType UserCommonUsbTypeCUserGetLenovoDeviceType(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    return UserInterfaceUsbTypeCUserGetLenovoDeviceType(enumInputPort);
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event (Including System Acknowledge)
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCLenovoSysEvent
//--------------------------------------------------
StructTypeCLenovoSysEvent UserCommonUsbTypeCUserGetLenovoSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructTypeCLenovoSysEvent stLenovoSysEvent = {_TYPE_C_LENOVO_SYS_DC_MODE, _TYPE_C_LENOVO_SYS_STATE_NONE, _FALSE, 0x00, 0x00};
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    UserInterfaceUsbTypeCUserGetLenovoSystemEvent(enumInputPort, &stLenovoSysEvent);

    return stLenovoSysEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Set Docking Event
// Input Value  : enumTypeCPcbPort, stLenovoDockEvent
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCUserSetLenovoDockingEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    UserInterfaceUsbTypeCUserSetLenovoDockingEvent(enumInputPort, stLenovoDockEvent);
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : enumTypeCPcbPort
// Output Value : Docking Event Check Busy Result (_TYPE_C_LENOVO_DOCK_EVENT_BUSY / _TYPE_C_LENOVO_DOCK_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCLenovoCheckBusyResult UserCommonUsbTypeCUserCheckLenovoDockingEventBusy(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    return UserInterfaceUsbTypeCUserCheckLenovoDockingEventBusy(enumInputPort);
}
#endif // End of #if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_USER_SERIES_SUPPORT == _ON))
