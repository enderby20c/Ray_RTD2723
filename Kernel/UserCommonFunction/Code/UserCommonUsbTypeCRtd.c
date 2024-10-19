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
// ID Code      : UserCommonUsbTypeCRtd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_USBTYPECRTD__

#include "UserCommonInclude.h"
#include "UsbTypeCRtd/UserCommonUsbTypeCRtd.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTD_SUPPORT == _ON))

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructTypeCRtdInfo g_pstUsbTypeCRtdInfo[_TYPE_C_PORT_VALID];


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial RTD Port Ctrl Status
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtdInitial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // Reset All Status to Default Value
    UserCommonUsbTypeCRtdReset(enumTypeCPcbPort);

    // Enable "STATUS_DETECT"
    UserCommonUsbTypeCRtdStatusDetCtrl(enumTypeCPcbPort, _ENABLE);
}

//--------------------------------------------------
// Description  : Reset RTD Port Ctrl Status
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtdReset(EnumTypeCPcbPort enumTypeCPcbPort)
{
    SET_TYPE_C_RTD_CC_ATTACH(enumTypeCPcbPort, _TYPE_C_UNATTACH);
    SET_TYPE_C_RTD_ORIENTATION(enumTypeCPcbPort, _TYPE_C_ORIENTATION_NONE);
    SET_TYPE_C_RTD_POWER_ROLE(enumTypeCPcbPort, _TYPE_C_POWER_ROLE_NONE);
    SET_TYPE_C_RTD_DATA_ROLE(enumTypeCPcbPort, _TYPE_C_DATA_ROLE_NONE);

    SET_TYPE_C_RTD_ALT_MODE_READY(enumTypeCPcbPort, _TYPE_C_ALT_MODE_NOT_READY);
    SET_TYPE_C_RTD_PIN_ASSIGNMENT(enumTypeCPcbPort, _TYPE_C_PIN_ASSIGNMENT_NONE);

    SET_TYPE_C_RTD_PDO_STATUS_VOL(enumTypeCPcbPort, 0x0000);
    SET_TYPE_C_RTD_PDO_STATUS_CUR(enumTypeCPcbPort, 0x0000);
}

//--------------------------------------------------
// Description  : Update RTD Port Ctrl Status
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtdUpdateStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // DebugMessageTypeC("8. -------- Updatae RTD Port Ctrl Status -------- ", enumTypeCPcbPort);

    if(GET_TYPE_C_RTD_STATUS_DETECT(enumTypeCPcbPort) == _TRUE)
    {
        // Clear "STATUS_DETECT" and Active Timer to Re-Detect Later
        UserCommonUsbTypeCRtdStatusDetCtrl(enumTypeCPcbPort, _DISABLE);

        // 1. [Normative] Update Port Ctrl Status : CC Attach, Orientation, Alt Mode Ready, Pin Assignment, PDO Status
        UserCommonUsbTypeCRtdUpdatePortCtrlStatus(enumTypeCPcbPort);

        // 2. [Optional] Update Source PDO
        // 3. [Optional] Update Partner Source PDO
        // 4. [Optional] Update Sink PDO
        // 5. [Optional] Update Partner Sink PDO
        // 6. [Optional] Update RDO
    }
}

//--------------------------------------------------
// Description  : Update RTD Port Ctrl Port Ctrl Status
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtdUpdatePortCtrlStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // Port Ctrl Status : CC Attach, Orientation, Alt Mode Ready, Pin Assignment, PDO Status
    BYTE pucPortCtrlStatus[_TYPE_C_RTD_PORT_CTRL_STATUS_SIZE] = {0x00};
    bit bI2CStatus = _FAIL;

    // ================================
    // Get Front Chip Port Ctrl Status
    // ================================
    // Read 4-Byte Data from PDC Table 0x00
    bI2CStatus = UserCommonUsbTypeCRtdGetPortCtrlInfoByI2C(enumTypeCPcbPort, _TYPE_C_RTD_PORT_CTRL_STATUS_START_ADDR, _TYPE_C_RTD_PORT_CTRL_STATUS_SIZE, pucPortCtrlStatus);

    // =================================
    // Update Port Ctrl Status to Macro
    // =================================

    // Port Ctrl Status 0 : [7] CC Attach
    if((pucPortCtrlStatus[0] & _BIT7) == _BIT7)
    {
        // CC Attach : Update Macro Info
        SET_TYPE_C_RTD_CC_ATTACH(enumTypeCPcbPort, _TYPE_C_ATTACH);

        // [6] Orientation
        if((pucPortCtrlStatus[0] & _BIT6) == _BIT6)
        {
            SET_TYPE_C_RTD_ORIENTATION(enumTypeCPcbPort, _TYPE_C_ORIENTATION_UNFLIP);
        }
        else
        {
            SET_TYPE_C_RTD_ORIENTATION(enumTypeCPcbPort, _TYPE_C_ORIENTATION_FLIP);
        }

        // [4] Power Role
        if((pucPortCtrlStatus[0] & _BIT4) == _BIT4)
        {
            SET_TYPE_C_RTD_POWER_ROLE(enumTypeCPcbPort, _TYPE_C_POWER_SRC);
        }
        else
        {
            SET_TYPE_C_RTD_POWER_ROLE(enumTypeCPcbPort, _TYPE_C_POWER_SNK);
        }

        // [3] Data Role
        if((pucPortCtrlStatus[0] & _BIT3) == _BIT3)
        {
            SET_TYPE_C_RTD_DATA_ROLE(enumTypeCPcbPort, _TYPE_C_DFP_U);
        }
        else
        {
            SET_TYPE_C_RTD_DATA_ROLE(enumTypeCPcbPort, _TYPE_C_UFP_U);
        }

        // Port Ctrl Status 1 : [7] Alt Mode Ready
        if((pucPortCtrlStatus[1] & _BIT7) == _BIT7)
        {
            // Update Alt Mode Ready
            SET_TYPE_C_RTD_ALT_MODE_READY(enumTypeCPcbPort, _TYPE_C_ALT_MODE_READY);

            // [4:0] Pin Assignment
            SET_TYPE_C_RTD_PIN_ASSIGNMENT(enumTypeCPcbPort, (EnumTypeCPinCfgType)(pucPortCtrlStatus[1] & 0x1F));
        }
        else
        {
            // Alt Mode Not Ready : Reset Alt Mode Ready & Pin Assignment
            SET_TYPE_C_RTD_ALT_MODE_READY(enumTypeCPcbPort, _TYPE_C_ALT_MODE_NOT_READY);
            SET_TYPE_C_RTD_PIN_ASSIGNMENT(enumTypeCPcbPort, _TYPE_C_PIN_ASSIGNMENT_NONE);
        }

        // Port Ctrl Status 2 : [7:0] Voltage in 100mV, and convert to 10mV
        SET_TYPE_C_RTD_PDO_STATUS_VOL(enumTypeCPcbPort, ((WORD)pucPortCtrlStatus[2] * 10));

        // Port Ctrl Status 3 : [7:0] Voltage in 50mA, and convert to 10mA
        SET_TYPE_C_RTD_PDO_STATUS_CUR(enumTypeCPcbPort, ((WORD)pucPortCtrlStatus[3] * 5));
    }
    else
    {
        // CC Unattach : Reset All Macro
        UserCommonUsbTypeCRtdReset(enumTypeCPcbPort);
    }

    if(bI2CStatus == _SUCCESS)
    {
        DebugMessageTypeC("8. -------- I2C Updatae RTD Status Success --------", 0x00);

        DebugMessageTypeC("8. RTD Port Ctrl Status [0] : ", pucPortCtrlStatus[0]);
        DebugMessageTypeC("8. RTD Port Ctrl Status [1] : ", pucPortCtrlStatus[1]);
        DebugMessageTypeC("8. RTD Port Ctrl Status [2] : ", pucPortCtrlStatus[2]);
        DebugMessageTypeC("8. RTD Port Ctrl Status [3] : ", pucPortCtrlStatus[3]);
    }
}

#if(_PORT_CTRL_RTD_DET_CC_ATTACH_BY_SMBUS == _ON)
//--------------------------------------------------
// Description  : Get RTD Port Ctrl CC Attached Info Through I2C
// Input Value  : enumTypeCPcbPort : _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : CC Attach (_TYPE_C_UNATTACH / _TYPE_C_ATTACH)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonUsbTypeCRtdGetCcAttachByI2C(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return GET_TYPE_C_RTD_CC_ATTACH(enumTypeCPcbPort);
}
#endif

#if(_PORT_CTRL_RTD_DET_ALT_MODE_READY_BY_SMBUS == _ON)
//--------------------------------------------------
// Description  : Get RTD Port Ctrl Alt Mode Ready Info Through I2C
// Input Value  : enumTypeCPcbPort : _D0_TYPE_C_PORT / _D1_TYPE_C_PORT...
// Output Value : Alt Mode Ready (_TYPE_C_ALT_MODE_NOT_READY / _TYPE_C_ALT_MODE_READY)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonUsbTypeCRtdGetAltModeReadyByI2C(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return GET_TYPE_C_RTD_ALT_MODE_READY(enumTypeCPcbPort);
}
#endif

//--------------------------------------------------
// Description  : Get RTD Port Ctrl Orientation Status
// Input Value  : enumTypeCPcbPort
// Output Value : Orientation (_TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP)
//--------------------------------------------------
EnumTypeCOrientation UserCommonUsbTypeCRtdGetOrientation(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // For CC Attatch / Alt Mde Ready Det By GPIO, Force Update Info go get Correct Orientation
    // UserCommonUsbTypeCRtdUpdatePortCtrlStatus(enumTypeCPcbPort);

    return GET_TYPE_C_RTD_ORIENTATION(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Get RTD Port Ctrl Pin Assignment and Return Result
// Input Value  : enumTypeCPcbPort / penumPinAssignment pointer
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonUsbTypeCRtdGetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    // For CC Attatch / Alt Mode Ready Det. by GPIO, Force Update Info to get Correct Pin Assignemtn
    // UserCommonUsbTypeCRtdUpdatePortCtrlStatus(enumTypeCPcbPort);

    *penumPinAssignment = GET_TYPE_C_RTD_PIN_ASSIGNMENT(enumTypeCPcbPort);

    if(GET_TYPE_C_RTD_PIN_ASSIGNMENT(enumTypeCPcbPort) == _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Get RTD Port Ctrl Data Role
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCDataRole (_TYPE_C_DATA_ROLE_NONE / _TYPE_C_UFP_U / _TYPE_C_DFP_U)
//--------------------------------------------------
EnumTypeCDataRole UserCommonUsbTypeCRtdGetDataRole(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return GET_TYPE_C_RTD_DATA_ROLE(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Get RTD Port Ctrl Power Role
// Input Value  : enumTypeCPcbPort
// Output Value : EnumTypeCPowerRole (_TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC / _TYPE_C_POWER_ROLE_NONE)
//--------------------------------------------------
EnumTypeCPowerRole UserCommonUsbTypeCRtdGetPowerRole(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return GET_TYPE_C_RTD_POWER_ROLE(enumTypeCPcbPort);
}

//--------------------------------------------------
// Description  : Get RTD Port Ctrl Number of Src/Snk PDOs
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO)
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
BYTE UserCommonUsbTypeCRtdGetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCnt = 0;

    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;

    return ucPdoCnt;
}

//--------------------------------------------------
// Description  : Get RTD Port Ctrl Source/Sink PDO Info
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 50mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonUsbTypeCRtdGetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;

    return stTypeCPdo;
}

//--------------------------------------------------
// Description  : Get RTD Port Ctrl Number of Partner Src/Snk PDOs
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO)
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
BYTE UserCommonUsbTypeCRtdGetPartnerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCnt = 0;

    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;

    return ucPdoCnt;
}

//--------------------------------------------------
// Description  : Get RTD Port Ctrl Partner Source/Sink PDO Info
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 50mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonUsbTypeCRtdGetPartnerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPartnerPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;

    return stTypeCPartnerPdo;
}

//--------------------------------------------------
// Description  : Get RTD Port Ctrl PDO Status
// Input Value  : enumTypeCPcbPort, *pusVoltage (Unit: 10mV), *pusCurrent (Unit: 10mA)
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtdGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // Voltage in 10mV
    // *pusVoltage = GET_TYPE_C_RTS_PDO_STATUS_VOL(enumTypeCPcbPort);
    *pusVoltage = 0;

    // Current in 10mA
    // *pusCurrent = GET_TYPE_C_RTS_PDO_STATUS_CUR(enumTypeCPcbPort);
    *pusCurrent = 0;
}

//--------------------------------------------------
// Description  : Get RTD Port Ctrl Current Source PDO that Sink Request
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 50mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonUsbTypeCRtdGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructTypeCUserPDO stTypeCSrcPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    enumTypeCPcbPort = enumTypeCPcbPort;

    return stTypeCSrcPdo;
}

//--------------------------------------------------
// Description  : Get RTD Port Ctrl Discovered Cable Info
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCCableInfoForDpcd (ActiveComponent, Uhbr13p5Support, MaxDpRate)
//--------------------------------------------------
StructTypeCCableInfoForDpcd UserCommonUsbTypeCRtdGetCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE pucReadInfo[1] = {0x00};

    StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd = {_PD_CBL_COMPONENT_PASSIVE, _PD_CBL_MAX_DP_RATE_UNCONFIRMED, _FALSE};
    enumTypeCPcbPort = enumTypeCPcbPort;

    // Get RTD Port Controller Discovered Cable Info from PDC Table (0x0A)
    UserCommonUsbTypeCRtdGetPortCtrlInfoByI2C(enumTypeCPcbPort, 0x0A, 0x01, pucReadInfo);

    // DPCD Table Bit[6:5]: Cable Type
    stTypeCCableInfoForDpcd.enumTypeCCableActiveComponent = ((pucReadInfo[0] & (_BIT6 | _BIT5)) >> 5);

    // DPCD Table Bit[4]: Cable UHBR13.5 Support
    stTypeCCableInfoForDpcd.b1CableUhbr13p5Support = ((pucReadInfo[0] & (_BIT4)) >> 4);

    // DPCD Table Bit[2:0]: Cable UHBR10_20 Capability
    stTypeCCableInfoForDpcd.enumTypeCCableMaxDpRate = (pucReadInfo[0] & (_BIT2 | _BIT1 | _BIT0));

    DebugMessageTypeC("8. [Get PDC Discovered Cable Info], Get 0x0A = ", pucReadInfo[0]);
    DebugMessageTypeC("8. [Cable Info] Active Component = ", stTypeCCableInfoForDpcd.enumTypeCCableActiveComponent);
    DebugMessageTypeC("8. [Cable Info] UHBR13.5 = ", stTypeCCableInfoForDpcd.b1CableUhbr13p5Support);
    DebugMessageTypeC("8. [Cable Info] Max DP Rate = ", stTypeCCableInfoForDpcd.enumTypeCCableMaxDpRate);

    return stTypeCCableInfoForDpcd;
}

//--------------------------------------------------
// Description  : Set Pin Assignment & Multi-Func Bit to RTD Port Ctrl
// Input Value  : enumTypeCPcbPort / ucPinAssignment / ucDataRole
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtdSetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignment)
{
    BYTE pucReadInfo[1] = {0x00};
    BYTE pucWriteInfo[1] = {0x00};

    // Check Pin Assignment Update Event from PDC Table (0xA1)
    UserCommonUsbTypeCRtdGetPortCtrlInfoByI2C(enumTypeCPcbPort, 0xA1, 0x01, pucReadInfo);

    DebugMessageTypeC("8. [Config Pin Assignment], Get 0xA1 Event Status = ", pucReadInfo[0]);

    // Check 0xA1[7] : Pin Assignment Update Event
    if((pucReadInfo[0] & _BIT7) == 0x00)
    {
        pucWriteInfo[0] = _BIT7 | ((BYTE)enumPinAssignment & 0x1F);

        if(enumMultiFunc == _TYPE_C_MULTI_FUNC_PREFER)
        {
            pucWriteInfo[0] |= (_BIT5);
        }

        UserCommonUsbTypeCRtdSetPortCtrlInfoByI2C(enumTypeCPcbPort, 0xA1, 0x01, pucWriteInfo);

        DebugMessageTypeC("8. [Config Pin Assignment], Set 0xA1 : [7] Event, [5] Multi-Func, [4:0] Pin Assign ", pucWriteInfo[0]);

        return _SUCCESS;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Set User-Defined Number of PDOs to RTD Port Ctrl
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), Number of PDO Counts (1~7)
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtdSetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;
    ucPdoCnt = ucPdoCnt;
}

//--------------------------------------------------
// Description  : Set User-Defined Fix Supply/ PPS PDOs to RTD Port Ctrl
// Input Value  : enumTypeCPcbPort, enumPowerRole(Src/Snk PDO), ucPdoIndex, stTypeCUserPdo
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtdSetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;
    stTypeCUserPdo = stTypeCUserPdo;
}

//--------------------------------------------------
// Description  : Set User-Defined RDO to RTD Port Ctrl
// Input Value  : enumTypeCPcbPort, stTypeCUserRdo
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtdSetRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO stTypeCUserRdo)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    stTypeCUserRdo = stTypeCUserRdo;
}

//--------------------------------------------------
// Description  : Update CC Function Control to RTD Port Ctrl (Connect / Disconnect)
// Input Value  : enumTypeCPcbPort, enumCcFunction
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtdCcFunctionControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCcFunction enumCcFunction)
{
    BYTE pucReadInfo[1] = {0x00};
    BYTE pucWriteInfo[1] = {0x00};

    // Check CC Function Disable/Enable Event from PDC Table (0xA0)
    UserCommonUsbTypeCRtdGetPortCtrlInfoByI2C(enumTypeCPcbPort, 0xA0, 0x01, pucReadInfo);

    // Check 0xA0[7] : CC Function Disable Event
    if((enumCcFunction == _TYPE_C_CC_FUNCTION_DISABLE) && ((pucReadInfo[0] & (_BIT7)) == 0x00))
    {
        pucWriteInfo[0] |= _BIT7;
    }

    // Check 0xA0[6] : CC Function Enable Event
    if((enumCcFunction == _TYPE_C_CC_FUNCTION_ENABLE) && ((pucReadInfo[0] & (_BIT6)) == 0x00))
    {
        pucWriteInfo[0] |= _BIT6;
    }

    // Set CC Function Disable/Enable Event to PDC Table (0xA0)
    if(((pucWriteInfo[0]) & (_BIT7 | _BIT6)) != 0x00)
    {
        UserCommonUsbTypeCRtdSetPortCtrlInfoByI2C(enumTypeCPcbPort, 0xA0, 0x01, pucWriteInfo);
    }
    else
    {
        DebugMessageTypeC("8. RTD Port Ctrl : CC Function Ctrl Fail, 0xA0 Event Status = ", pucReadInfo[0]);
    }
}

//--------------------------------------------------
// Description  : Set Power Mode to RTD Port Ctrl
// Input Value  : enumTypeCPcbPort, enumPowerRole
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtdSetTargetPowerMode(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    // RTD Does NOT Support Real-Time Change Target Power Role
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;
}

//--------------------------------------------------
// Description  : Ask RTD Port Ctrl to Reconnect
// Input Value  : enumTypeCPcbPort
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtdReconnect(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE pucReadInfo[1] = {0x00};
    BYTE pucWriteInfo[1] = {0x00};

    // Check CC Function Disable/Enable Event from PDC Table (0xA0)
    UserCommonUsbTypeCRtdGetPortCtrlInfoByI2C(enumTypeCPcbPort, 0xA0, 0x01, pucReadInfo);

    // Check 0xA0[7:6] : CC Function Disable/Enable Event
    if((pucReadInfo[0] & (_BIT7 | _BIT6)) != (_BIT7 | _BIT6))
    {
        pucWriteInfo[0] |= (_BIT7 | _BIT6);
        UserCommonUsbTypeCRtdSetPortCtrlInfoByI2C(enumTypeCPcbPort, 0xA0, 0x01, pucWriteInfo);

        return _SUCCESS;
    }
    else
    {
        DebugMessageTypeC("8. RTD Port Ctrl : Reconnect Fail, 0xA0 Event Status = ", pucReadInfo[0]);
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Control RTD Port Ctrl I2C Status Detection Flag
// Input Value  : enumTypeCPcbPort, bAction : _ENABLE/_DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonUsbTypeCRtdStatusDetCtrl(EnumTypeCPcbPort enumTypeCPcbPort, bit bAction)
{
    switch(enumTypeCPcbPort)
    {
#if(_D0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _D0_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_TYPE_C_RTD_STATUS_DETECT(_D0_TYPE_C_PORT);
            }
            else
            {
                // Clear Status Detect Flag, Active Timer Event to Re-Enable RTD PD Info Read Via I2C
                CLR_TYPE_C_RTD_STATUS_DETECT(_D0_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_D0_TYPE_C_RTD_STATUS_DETECT);
            }

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_D1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _D1_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_TYPE_C_RTD_STATUS_DETECT(_D1_TYPE_C_PORT);
            }
            else
            {
                // Clear Status Detect Flag, Active Timer Event to Re-Enable RTD PD Info Read Via I2C
                CLR_TYPE_C_RTD_STATUS_DETECT(_D1_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_D1_TYPE_C_RTD_STATUS_DETECT);
            }

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_D2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _D2_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_TYPE_C_RTD_STATUS_DETECT(_D2_TYPE_C_PORT);
            }
            else
            {
                // Clear Status Detect Flag, Active Timer Event to Re-Enable RTD PD Info Read Via I2C
                CLR_TYPE_C_RTD_STATUS_DETECT(_D2_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_D2_TYPE_C_RTD_STATUS_DETECT);
            }

            break;
#endif  // End of #if(_D2_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_P0_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _P0_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_TYPE_C_RTD_STATUS_DETECT(_P0_TYPE_C_PORT);
            }
            else
            {
                // Clear Status Detect Flag, Active Timer Event to Re-Enable RTD PD Info Read Via I2C
                CLR_TYPE_C_RTD_STATUS_DETECT(_P0_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_P0_TYPE_C_RTD_STATUS_DETECT);
            }

            break;
#endif  // End of #if(_P0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_P1_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _P1_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_TYPE_C_RTD_STATUS_DETECT(_P1_TYPE_C_PORT);
            }
            else
            {
                // Clear Status Detect Flag, Active Timer Event to Re-Enable RTD PD Info Read Via I2C
                CLR_TYPE_C_RTD_STATUS_DETECT(_P1_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_P1_TYPE_C_RTD_STATUS_DETECT);
            }

            break;
#endif  // End of #if(_P1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_P2_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _P2_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_TYPE_C_RTD_STATUS_DETECT(_P2_TYPE_C_PORT);
            }
            else
            {
                // Clear Status Detect Flag, Active Timer Event to Re-Enable RTD PD Info Read Via I2C
                CLR_TYPE_C_RTD_STATUS_DETECT(_P2_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_P2_TYPE_C_RTD_STATUS_DETECT);
            }

            break;
#endif  // End of #if(_P2_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_P3_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _P3_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_TYPE_C_RTD_STATUS_DETECT(_P3_TYPE_C_PORT);
            }
            else
            {
                // Clear Status Detect Flag, Active Timer Event to Re-Enable RTD PD Info Read Via I2C
                CLR_TYPE_C_RTD_STATUS_DETECT(_P3_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_P3_TYPE_C_RTD_STATUS_DETECT);
            }

            break;
#endif  // End of #if(_P3_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_P4_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _P4_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_TYPE_C_RTD_STATUS_DETECT(_P4_TYPE_C_PORT);
            }
            else
            {
                // Clear Status Detect Flag, Active Timer Event to Re-Enable RTD PD Info Read Via I2C
                CLR_TYPE_C_RTD_STATUS_DETECT(_P4_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_P4_TYPE_C_RTD_STATUS_DETECT);
            }

            break;
#endif  // End of #if(_P4_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

#if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)
        case _ADAPTOR_TYPE_C_PORT:

            if(bAction == _ENABLE)
            {
                SET_TYPE_C_RTD_STATUS_DETECT(_ADAPTOR_TYPE_C_PORT);
            }
            else
            {
                // Clear Status Detect Flag, Active Timer Event to Re-Enable RTD PD Info Read Via I2C
                CLR_TYPE_C_RTD_STATUS_DETECT(_ADAPTOR_TYPE_C_PORT);
                ScalerTimerActiveTimerEvent(_TYPE_C_PORT_CTRL_RTS_STATUS_POLLING_TIME, _SYSTEM_TIMER_EVENT_ADAPTOR_TYPE_C_RTD_STATUS_DETECT);
            }

            break;
#endif  // End of #if(_ADAPTOR_TYPE_C_PORT_CTRL_TYPE == _PORT_CTRL_RTD)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Port Controller Slave Address
// Input Value  : enumTypeCPcbPort
// Output Value : Slave Address
//--------------------------------------------------
BYTE UserCommonUsbTypeCRtdGetSlaveAddr(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucSlaveAddr = 0x00;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:

            ucSlaveAddr = _D0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _D1_TYPE_C_PORT:

            ucSlaveAddr = _D1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _D2_TYPE_C_PORT:

            ucSlaveAddr = _D2_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _P0_TYPE_C_PORT:

            ucSlaveAddr = _P0_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _P1_TYPE_C_PORT:

            ucSlaveAddr = _P1_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _P2_TYPE_C_PORT:

            ucSlaveAddr = _P2_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _P3_TYPE_C_PORT:

            ucSlaveAddr = _P3_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _P4_TYPE_C_PORT:

            ucSlaveAddr = _P4_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        case _ADAPTOR_TYPE_C_PORT:

            ucSlaveAddr = _ADAPTOR_TYPE_C_RTS_PORT_CTRL_SLAVE_ADDR;

            break;

        default:
            break;
    }

    return ucSlaveAddr;
}

//--------------------------------------------------
// Description  : Read RTD Port Ctrl Info by SMBus
// Input Value  : enumTypeCPcbPort, ucStartAddr, ucLength, pucReadInfo
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtdGetPortCtrlInfoByI2C(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucStartAddr, BYTE ucLength, BYTE *pucReadInfo)
{
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtdGetSlaveAddr(enumTypeCPcbPort);
    BYTE ucCmdLength = 0x03;    // 3-Byte : Command | Start Addr | Read Length
    BYTE pucReadCmd[3] = {0x00};

    pucReadCmd[0] = (_BIT6) | (enumTypeCPcbPort & 0x3F);  // Command : [7:6] Write(00)/Read(01), [5:0] TypeC Port
    pucReadCmd[1] = ucStartAddr;  // PDC Table Start Addr
    pucReadCmd[2] = ucLength;     // PDC Table Read Length (Number of Data to be Read)

    // Set Read Info to RTD PD Controller (Slave Addr | Command | Start Addr | Length)
    if(UserCommonUsbCommunicationWrite(ucSlaveAddr, 0x00, 0x00, ucCmdLength, pucReadCmd, enumTypeCPcbPort) == _FAIL)
    {
        DebugMessageTypeC("8. IIC Write Command to RTD Port Ctrl Fail", enumTypeCPcbPort);

        return _FAIL;
    }

    // Wait for RTD Port Ctrl to Prepare Reply Data
    ScalerTimerDelayXms(5);

    // Read Data from I2C RTD Port Ctrl, and Set to pucReadInfo
    if(UserCommonUsbCommunicationRead(ucSlaveAddr, 0x00, 0x00, pucReadCmd[2], pucReadInfo, enumTypeCPcbPort) == _FAIL)
    {
        DebugMessageTypeC("8. IIC Read RTD Port Ctrl Info Fail", enumTypeCPcbPort);

        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Set RTD Port Ctrl Info by SMBus
// Input Value  : enumTypeCPcbPort, ucStartAddr, ucLength, pucWriteInfo
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbTypeCRtdSetPortCtrlInfoByI2C(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucStartAddr, BYTE ucLength, BYTE *pucWriteInfo)
{
    BYTE ucSlaveAddr = UserCommonUsbTypeCRtdGetSlaveAddr(enumTypeCPcbPort);
    BYTE ucCmdLength = ucLength + 3;
    BYTE pucWriteCmd[16] = {0x00}; // Command | Start Addr | Read Length | Data 0..N

    // Command : [7:6] Write(00), [5:0] TypeC Port
    pucWriteCmd[0] = (enumTypeCPcbPort & 0x3F);
    pucWriteCmd[1] = ucStartAddr;  // PDC Table Start Addr
    pucWriteCmd[2] = ucLength;     // PDC Table Read Length (Number of Data to be Read)

    // Copy Write Info to Array Start from ucWriteCmd[3]
    memcpy(&pucWriteCmd[3], pucWriteInfo, ucLength);
    /*
    for(pData[0] = 0x00; pData[0] < ucLength; pData[0]++)
    {
        ucWriteCmd[3 + pData[0]] = *(pucWriteInfo + pData[0]);
    }
    */

    // Set Write Info to RTD PD Controller (Slave Addr | Command | Start Addr | Length)
    if(UserCommonUsbCommunicationWrite(ucSlaveAddr, 0x00, 0x00, ucCmdLength, pucWriteCmd, enumTypeCPcbPort) == _FAIL)
    {
        DebugMessageTypeC("8. IIC Write Command to RTD Port Ctrl Fail", enumTypeCPcbPort);

        return _FAIL;
    }

    return _SUCCESS;
}

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTD_SUPPORT == _ON))
