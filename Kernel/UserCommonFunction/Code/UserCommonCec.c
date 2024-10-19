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
// ID Code      : UserCommonCec.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "Cec/UserCommonCec.h"

#if(_HDMI_CEC_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
BYTE code tCecSupportPort[_HDMI_CEC_PORT_AMOUNT] =
{
#if(_D1_HDMI_CEC_SUPPORT == _ON)
    _D1_INPUT_PORT,
#endif

#if(_D2_HDMI_CEC_SUPPORT == _ON)
    _D2_INPUT_PORT,
#endif

#if(_D3_HDMI_CEC_SUPPORT == _ON)
    _D3_INPUT_PORT,
#endif

#if(_D4_HDMI_CEC_SUPPORT == _ON)
    _D4_INPUT_PORT,
#endif
};

WORD code tEdidPhysicalAddr[_HDMI_CEC_PORT_AMOUNT] =
{
#if(_D1_HDMI_CEC_SUPPORT == _ON)
    _D1_HDMI_CEC_EDID_PHYSICAL_ADDR,
#endif

#if(_D2_HDMI_CEC_SUPPORT == _ON)
    _D2_HDMI_CEC_EDID_PHYSICAL_ADDR,
#endif

#if(_D3_HDMI_CEC_SUPPORT == _ON)
    _D3_HDMI_CEC_EDID_PHYSICAL_ADDR,
#endif

#if(_D4_HDMI_CEC_SUPPORT == _ON)
    _D4_HDMI_CEC_EDID_PHYSICAL_ADDR,
#endif
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
StructCecServicelInfo g_stCecServiceInfo;

#if(_HDMI_SUPPORT == _ON)
StructCecSrc5VPinInfo g_stCecSrcPowerInfo;
BYTE g_ucCecFirstUpdateSource5V;
#endif
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Received CEC RX INFO bypass to User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecReceiveNotify(void)
{
    if(GET_CEC_RX_READ_DONE() == _TRUE)
    {
        StructCecRxReceivedInfo stCecRxInfo;
        memcpy(&stCecRxInfo, &g_stCecRxReceivedInfo, sizeof(StructCecRxReceivedInfo));

        DebugMessageCEC("CEC RX Read: HB ", g_stCecRxReceivedInfo.ucReceivedHb);
        for(pData[0] = 0; pData[0] < g_stCecRxReceivedInfo.ucDbLength; pData[0]++)
        {
            DebugMessageCEC("CEC RX Read: DB ", g_stCecRxReceivedInfo.pucReceivedDb[pData[0]]);
        }

        DebugMessageCEC("CEC RX Read: Length ", g_stCecRxReceivedInfo.ucDbLength);

        SET_CEC_RX_MSG_ANALYZING();

        // Pass Cec Rx Info to User
        UserInterfaceCecReceivedNotify(&stCecRxInfo);

        CLR_CEC_RX_READ_DONE();

        // reset Cec rx struct
        memset(&g_stCecRxReceivedInfo, 0, sizeof(g_stCecRxReceivedInfo));
    }
}

//--------------------------------------------------
// Description  : Catch Cec Tx
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecTransmitInfoPrepare(void)
{
    StructCecTxTransmitInfo stCecTxInfo;

    memset(&stCecTxInfo, 0x00, sizeof(StructCecTxTransmitInfo));

    if(UserCommonCecGetTxState() == _CEC_TX_IDLE_STATE)
    {
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
        // Update LA Polling State
        if(GET_CEC_LOGICAL_ADDR_POLLING_STATE() == _CEC_TX_LA_POLLING_STATE_SENT)
        {
            if((UserCommonCecTxGetTransmitResult() == _CEC_TX_LINE_ERROR_EVENT) || (UserCommonCecTxGetTransmitResult() == _CEC_TX_HB_NACK_EVENT))
            {
                SET_CEC_LOGICAL_ADDR_POLLING_STATE(_CEC_TX_LA_POLLING_STATE_NACK);
            }
            else if(UserCommonCecTxGetTransmitResult() == _CEC_TX_SENT_EVENT)
            {
                SET_CEC_LOGICAL_ADDR_POLLING_STATE(_CEC_TX_LA_POLLING_STATE_ACK);
            }
        }
#endif

        if(UserInterfaceCecTransmitInfoPrepare(&stCecTxInfo) == _CEC_TX_TASK)
        {
            memcpy(&g_stCecTxTransmitInfo, &stCecTxInfo, sizeof(StructCecTxTransmitInfo));

            SET_CEC_TX_START();
        }
    }
}

//--------------------------------------------------
// Description  : CEC Function Enable Flag Set/ Clear
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void UserCommonCecFunctionEnable(EnumCecFunctionEnable enumCecEnable)
{
    if(enumCecEnable == _CEC_FX_ENABLE)
    {
        SET_CEC_FUNCTION_ENABLE();
    }
    else
    {
        CLR_CEC_FUNCTION_ENABLE();
    }
}

//--------------------------------------------------
// Description  : Cec Rx Pop Queue Message
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecRxPopQueueMsg(void)
{
    if(g_ucCecRxTotalQueueMsgIdx > 0)
    {
        // Total Queue Received Message Remove one
        g_ucCecRxTotalQueueMsgIdx = g_ucCecRxTotalQueueMsgIdx - 1;
    }
}

//--------------------------------------------------
// Description  : Clr Cec Rx Msg Analyzing Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecRxClrIMsgAnalyzingFlag(void)
{
    CLR_CEC_RX_MSG_ANALYZING();

    UserCommonCecRxPopQueueMsg();
}

//--------------------------------------------------
// Description  : Get Cec Rx Msg Analyzing Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonCecRxGetMsgAnalyzingFlag(void)
{
    return GET_CEC_RX_MSG_ANALYZING();
}

//--------------------------------------------------
// Description  : CEC check whether Rx data length is valid or not
// Input Value  : enumOpCode, ucLength
// Output Value : Valid length or not
//--------------------------------------------------
bit UserCommonCecCheckFrameLengthIsLegal(EnumCECOpCode enumOpCode, BYTE ucLength)
{
    BYTE ucResult = _TRUE;

    switch(enumOpCode)
    {
        case _CEC_OPCODE_GIVE_DEVICE_POWER_STATUS:
        case _CEC_OPCODE_GIVE_PHYSICAL_ADDRESS:
        case _CEC_OPCODE_IMAGE_VIEW_ON:
        case _CEC_OPCODE_TEXT_VIEW_ON:
        case _CEC_OPCODE_STANDBY:
        case _CEC_OPCODE_REQUEST_ACTIVE_SOURCE:
        case _CEC_OPCODE_ABORT_MESSAGE:

            if(ucLength != 1)
            {
                ucResult = _FALSE;
            }

            break;

        case _CEC_OPCODE_USER_CONTROL_PRESSED:

            if(ucLength != 2)
            {
                ucResult = _FALSE;
            }

            break;

        case _CEC_OPCODE_ACTIVE_SOURCE:

            if(ucLength != 3)
            {
                ucResult = _FALSE;
            }

            break;

        case _CEC_OPCODE_REPORT_PHYSICAL_ADDRESS:

            if(ucLength != 4)
            {
                ucResult = _FALSE;
            }

            break;

        default:
            break;
    }

    if(ucResult == _FALSE)
    {
        DebugMessageCEC("[CEC][RX] check fail", enumOpCode);
        DebugMessageCEC("[CEC][RX] ucLength", ucLength);
    }

    return ucResult;
}

//--------------------------------------------------
// Description  : Get Result after Cec Tx Transmit
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumCecTxEvent UserCommonCecTxGetTransmitResult(void)
{
    return GET_CEC_TX_EVENT();
}

//--------------------------------------------------
// Description  : Get Result after Cec Tx Transmit
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumCecTxState UserCommonCecGetTxState(void)
{
    return GET_CEC_TX_STATE();
}

//--------------------------------------------------
// Description  : CEC Request Device to Send CEC Message
// Input Value  : enumOpCode
// Output Value : None
//--------------------------------------------------
void UserCommonCecRequestSendCecMessage(EnumCECOpCode enumOpCode)
{
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
    UserCommonCecHalPushTxMessageSendQueue(enumOpCode);
#else
    UserInterfaceCecRequestSendCecMessage(enumOpCode);
#endif
}

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get OSD CEC Enable Status
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonCecGetOsdCecEnable(void)
{
    if(UserInterfaceCecGetOsdCecEnable() == _CEC_OSD_ENABLE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set CEC ARC Initiate Received Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecSetArcInitiateReceivedEvent(void)
{
    if(UserInterfaceCecGetOsdCecEnable() == _CEC_OSD_ENABLE)
    {
        SET_CEC_ARC_INITIATE_RECEIVE_HAPPENED();
    }
}

//--------------------------------------------------
// Description  : Get CEC ARC Initiate Received Event
// Input Value  : None
// Output Value : _TRUE//_FALSE
//--------------------------------------------------
bit UserCommonCecGetArcInitiateReceivedEvent(void)
{
    return GET_CEC_ARC_INITIATE_RECEIVE_HAPPENED();
}

//--------------------------------------------------
// Description  : Set CEC ARC Terminate Received Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecSetArcTerminateReceivedEvent(void)
{
    if(UserInterfaceCecGetOsdCecEnable() == _CEC_OSD_ENABLE)
    {
        SET_CEC_ARC_TERMINATE_RECEIVE_HAPPENED();
    }
}

//--------------------------------------------------
// Description  : Get CEC ARC Terminate Received Event
// Input Value  : None
// Output Value : _TRUE//_FALSE
//--------------------------------------------------
bit UserCommonCecGetArcTerminateReceivedEvent(void)
{
    return GET_CEC_ARC_TERMINATE_RECEIVE_HAPPENED();
}
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Common CEC HAL AC Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalAcOnInitial(void)
{
    memset(&g_stCecServiceInfo, 0, sizeof(StructCecServicelInfo));

#if(_HDMI_SUPPORT == _ON)
    memset(&g_stCecSrcPowerInfo, 0, sizeof(StructCecSrc5VPinInfo));
    g_ucCecFirstUpdateSource5V = _TRUE;
#endif
}

//--------------------------------------------------
// Description  : User Common CEC HAL Push Tx Message Send Queue
// Input Value  : enumOpCode
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalPushTxMessageSendQueue(EnumCECOpCode enumOpCode)
{
    SET_CEC_REQUEST_TO_DEVICE(enumOpCode);
}

//--------------------------------------------------
// Description  : User Common CEC HAL Pop Tx Message Send Queue
// Input Value  : None
// Output Value : EnumCECOpCode
//--------------------------------------------------
EnumCECOpCode UserCommonCecHalGetTxMessageSendQueue(void)
{
    return GET_CEC_REQUEST_TO_DEVICE();
}

//--------------------------------------------------
// Description  : User Common CEC HAL Shift Tx Message Send Queue
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalPopTxMessageSendQueue(void)
{
    CLR_CEC_REQUEST_TO_DEVICE_QUEUE();
}

//--------------------------------------------------
// Description  : User Common CEC HAL Get Tx Message Send Queue Depth
// Input Value  : None
// Output Value : Send Queue Depth
//--------------------------------------------------
BYTE UserCommonCecHalGetTxMessageSendQueueDepth(void)
{
    return GET_CEC_REQUEST_TO_DEVICE_QUEUE_COUNT();
}

//--------------------------------------------------
// Description  : User Common CEC HAL Get the Dx Port Index from Device Logical Address
// Input Value  : ucLogicalAddress
// Output Value : Array Index
//--------------------------------------------------
BYTE UserCommonCecHalGetDxPortByDeviceLogicalAddress(BYTE ucLogicalAddress)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _HDMI_CEC_PORT_AMOUNT; ucTemp++)
    {
        if(GET_CEC_DEVICE_LOGICAL_ADDR_BY_PORT(ucTemp) == ucLogicalAddress)
        {
            return ucTemp;
        }
    }

    return 0;
}

//--------------------------------------------------
// Description  : User Common CEC HAL Get the corresponding Input Port from Physical Address
// Input Value  : usPhysicalAddress
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort UserCommonCecHalGetDxPortByPhysicalAddress(WORD usPhysicalAddress)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _HDMI_CEC_PORT_AMOUNT; ucTemp++)
    {
        if((tEdidPhysicalAddr[ucTemp] & 0xF000) == (usPhysicalAddress & 0xF000))
        {
            return tCecSupportPort[ucTemp];
        }
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : User Common CEC HAL Set Device Logical Address by corresponding input port
// Input Value  : usPhysicalAddress ucLogicalAddress
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalSetDeviceLogicalAddressByPhysicalAddress(WORD usPhysicalAddress, BYTE ucLogicalAddress)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _HDMI_CEC_PORT_AMOUNT; ucTemp++)
    {
        if(tEdidPhysicalAddr[ucTemp] == usPhysicalAddress)
        {
            SET_CEC_DEVICE_LOGICAL_ADDR_BY_PORT(ucTemp, ucLogicalAddress);
            return;
        }
    }
}

//--------------------------------------------------
// Description  : User Common CEC HAL Get the corresponding Physical Address from Input Port
// Input Value  : enumInputPortType
// Output Value : Physical Address
//--------------------------------------------------
WORD UserCommonCecHalGetPhysicalAddressByDxPort(EnumInputPort enumInputPortType)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _HDMI_CEC_PORT_AMOUNT; ucTemp++)
    {
        if(tCecSupportPort[ucTemp] == enumInputPortType)
        {
            return tEdidPhysicalAddr[ucTemp];
        }
    }

    return 0x0000;
}

//--------------------------------------------------
// Description  : User Common CEC HAL Get the corresponding Logical Address from Input Port
// Input Value  : enumInputPortType
// Output Value : Logical Address
//--------------------------------------------------
BYTE UserCommonCecHalGetLogicalAddressByDxPort(EnumInputPort enumInputPortType)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _HDMI_CEC_PORT_AMOUNT; ucTemp++)
    {
        if(tCecSupportPort[ucTemp] == enumInputPortType)
        {
            return GET_CEC_DEVICE_LOGICAL_ADDR_BY_PORT(ucTemp);
        }
    }

    return _CEC_LA_TV;
}

//--------------------------------------------------
// Description  : User Common CEC HAL Set OSD Name By Dx Port
// Input Value  : pucOsdNameArrayPtr, ucOsdNameArrayLength, ucDxPortIndex
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalSetOsdNameByDxPort(BYTE ucDxPortIndex, BYTE *pucOsdNameArray, BYTE ucOsdNameArrayLength)
{
    CLR_CEC_OSD_NAME_BUFFER_BY_EXIST_LA(ucDxPortIndex);
    SET_CEC_OSD_NAME_BUFFER_BY_EXIST_LA(ucDxPortIndex, pucOsdNameArray, ucOsdNameArrayLength);
    SET_CEC_DEVICE_OSD_NAME_RECEIVED_BY_PORT(ucDxPortIndex, _TRUE);
}

//--------------------------------------------------
// Description  : User Common CEC HAL Clear OSD Name By Dx Port
// Input Value  : ucDxPortIndex
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalClrOsdNameByDxPort(BYTE ucDxPortIndex)
{
    SET_CEC_REQUEST_DEVICE_OSD_NAME_BY_PORT(ucDxPortIndex, _FALSE);
    SET_CEC_DEVICE_OSD_NAME_RECEIVED_BY_PORT(ucDxPortIndex, _FALSE);
    CLR_CEC_OSD_NAME_BUFFER_BY_EXIST_LA(ucDxPortIndex);
}

//--------------------------------------------------
// Description  : User Common CEC HAL Polling Logical Address Handler
// Input Value  : penumOpCode, pucLogicalAddress
// Output Value : EnumCecTxTransmitTask
//--------------------------------------------------
EnumCecTxTransmitTask UserCommonCecHalPollingLogicalAddressHandler(EnumCECOpCode *penumOpCode, BYTE *pucLogicalAddress)
{
    EnumCecTxTransmitTask enumTxTansmitTask = _NO_CEC_TX_TASK;

    // "Active" or "Reactive" LA Polling task or "No deivce match LA"
    if((GET_CEC_LOGICAL_ADDR_POLLING_COUNT() == 0) || (GET_CEC_LOGICAL_ADDR_POLLING_CONTINUE() == _TRUE) ||
       (GET_CEC_LOGICAL_ADDR_POLLING_STATE() == _CEC_TX_LA_POLLING_STATE_NACK))
    {
        BYTE ucTemp = 0;

        // scan LA from LA = 1
        for(ucTemp = 0; ucTemp < _HDMI_CEC_PORT_AMOUNT; ucTemp++)
        {
            if((SysSourceGetCableDetect(tCecSupportPort[ucTemp]) == _TRUE) && (GET_CEC_DEVICE_LOGICAL_ADDR_BY_PORT(ucTemp) == 0x00))
            {
                // need to scan
                break;
            }
        }

        if(ucTemp < _HDMI_CEC_PORT_AMOUNT)
        {
            SET_CEC_LOGICAL_ADDR_POLLING_COUNT(GET_CEC_LOGICAL_ADDR_POLLING_COUNT() + 1);
        }
        else
        {
            SET_CEC_LOGICAL_ADDR_POLLING_COUNT(15);
        }

        CLR_CEC_LOGICAL_ADDR_POLLING_CONTINUE();
        CLR_CEC_LOGICAL_ADDR_POLLING_STATE();

        if(GET_CEC_LOGICAL_ADDR_POLLING_COUNT() != 15)
        {
            DebugMessageCEC("[CEC][TX] Polling LA", GET_CEC_LOGICAL_ADDR_POLLING_COUNT());

            // Notify user to send <Polling Message>
            *penumOpCode = _CEC_OPCODE_POLLING_MESSAGE;
            *pucLogicalAddress = GET_CEC_LOGICAL_ADDR_POLLING_COUNT();
            enumTxTansmitTask = _CEC_TX_TASK;

            SET_CEC_LOGICAL_ADDR_POLLING_STATE(_CEC_TX_LA_POLLING_STATE_SENT);
        }
    }
    else if(GET_CEC_LOGICAL_ADDR_POLLING_STATE() == _CEC_TX_LA_POLLING_STATE_ACK)  // Got deivce match LA
    {
        DebugMessageCEC("[CEC][TX] Polling LA Ack", GET_CEC_LOGICAL_ADDR_POLLING_COUNT());
        CLR_CEC_LOGICAL_ADDR_POLLING_STATE();

        // Notify user to send <Give Physical Address>
        *penumOpCode = _CEC_OPCODE_GIVE_PHYSICAL_ADDRESS;
        *pucLogicalAddress = GET_CEC_LOGICAL_ADDR_POLLING_COUNT();
        enumTxTansmitTask = _CEC_TX_TASK;

        SET_CEC_PHYSICAL_ADDR_REPORTING();
        CLR_CEC_PHYSICAL_ADDR_REPORTING_RETRY_COUNT();
        CLR_CEC_PHYSICAL_ADDR_RETRY_TIMEOUT();
        ScalerTimerActiveTimerEvent(500, _SYSTEM_TIMER_EVENT_CEC_RETRY_PHYSICAL_ADDRESS);
    }
    else if((GET_CEC_PHYSICAL_ADDR_REPORTING() == _TRUE) && (GET_CEC_PHYSICAL_ADDR_RETRY_TIMEOUT() == _TRUE))
    {
        // Notify user to send <Give Physical Address>
        *penumOpCode = _CEC_OPCODE_GIVE_PHYSICAL_ADDRESS;
        *pucLogicalAddress = GET_CEC_LOGICAL_ADDR_POLLING_COUNT();
        enumTxTansmitTask = _CEC_TX_TASK;

        CLR_CEC_PHYSICAL_ADDR_RETRY_TIMEOUT();
        SET_CEC_PHYSICAL_ADDR_REPORTING_RETRY_COUNT(GET_CEC_PHYSICAL_ADDR_REPORTING_RETRY_COUNT() + 1);

        if(GET_CEC_PHYSICAL_ADDR_REPORTING_RETRY_COUNT() <= 3)
        {
            ScalerTimerActiveTimerEvent(500, _SYSTEM_TIMER_EVENT_CEC_RETRY_PHYSICAL_ADDRESS);
        }
        else
        {
            CLR_CEC_PHYSICAL_ADDR_REPORTING();
            CLR_CEC_PHYSICAL_ADDR_REPORTING_RETRY_COUNT();
            SET_CEC_LOGICAL_ADDR_POLLING_CONTINUE();
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_RETRY_PHYSICAL_ADDRESS);
        }
    }

    if(GET_CEC_LOGICAL_ADDR_POLLING_COUNT() == 15)
    {
        DebugMessageCEC("[CEC][TX] Polling LA Finish", 0);
        CLR_CEC_LOGICAL_ADDR_POLLING_STATE();
        CLR_CEC_LOGICAL_ADDR_POLLING_START();
        CLR_CEC_REQUEST_DEVICE_OSD_NAME_BY_PORT();
        CLR_CEC_DEVICE_OSD_NAME_RECEIVED_BY_PORT();
        CLR_CEC_OSD_NAME_BUFFER();
    }

    return enumTxTansmitTask;
}

//--------------------------------------------------
// Description  : User Common CEC HAL Get Polling Logical Address Start
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonCecHalGetPollingLogicalAddressStart(void)
{
    return GET_CEC_LOGICAL_ADDR_POLLING_START();
}

//--------------------------------------------------
// Description  : User Common CEC HAL Stop Polling Physical Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalStopPollingPhysicalAddress(void)
{
    SET_CEC_LOGICAL_ADDR_POLLING_CONTINUE();
    CLR_CEC_PHYSICAL_ADDR_REPORTING();

    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_RETRY_PHYSICAL_ADDRESS);
    CLR_CEC_PHYSICAL_ADDR_RETRY_TIMEOUT();

    if(GET_CEC_REQUEST_TO_DEVICE() == _CEC_OPCODE_GIVE_PHYSICAL_ADDRESS)
    {
        CLR_CEC_REQUEST_TO_DEVICE_QUEUE();
    }
}

//--------------------------------------------------
// Description  : User Common CEC HAL Check Polling Logical Address Finish
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonCecHalCheckPollingLogicalAddressFinish(void)
{
    if(GET_CEC_LOGICAL_ADDR_POLLING_COUNT() == 15)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User Common CEC HAL Set PA Addr Retry Timeout Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalSetPhysicalAddressRetryTimeout(void)
{
    SET_CEC_PHYSICAL_ADDR_RETRY_TIMEOUT();
}

//--------------------------------------------------
// Description  : User Common CEC HAL Request Device OSD Name Handler
// Input Value  : pucLogicalAddr
// Output Value : EnumCecTxTransmitTask
//--------------------------------------------------
EnumCecTxTransmitTask UserCommonCecHalRequestDeviceOsdNameHandler(BYTE *pucLogicalAddr)
{
    BYTE ucTemp = 0;

    for(ucTemp = 0; ucTemp < _HDMI_CEC_PORT_AMOUNT; ucTemp++)
    {
        if((GET_CEC_DEVICE_LOGICAL_ADDR_BY_PORT(ucTemp) != 0x00) && (GET_CEC_REQUEST_DEVICE_OSD_NAME_BY_PORT(ucTemp) == _FALSE))
        {
            SET_CEC_REQUEST_DEVICE_OSD_NAME_BY_PORT(ucTemp, _TRUE);

            DebugMessageCEC("[CEC][TX] Send GIVE_OSD_NAME", GET_CEC_DEVICE_LOGICAL_ADDR_BY_PORT(ucTemp));

            *pucLogicalAddr = GET_CEC_DEVICE_LOGICAL_ADDR_BY_PORT(ucTemp);

            // Notify user to send <GIVE_OSD_NAME>
            return _CEC_TX_TASK;
        }
    }

    return _NO_CEC_TX_TASK;
}

//--------------------------------------------------
// Description  : User Common CEC HAL Topology Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalTopologyHandler(void)
{
    BYTE ucTemp = 0;
    BYTE ucInputPort = _NO_INPUT_PORT;
    EnumPortType enumPortType = _PORT_NONE;

    for(ucTemp = 0; ucTemp < _INPUT_PORT_VALID; ucTemp++)
    {
        ucInputPort = SysSourceGetSpecificInputPort(ucTemp);
        enumPortType = SysSourceGetPortTypeFromInputPort(ucInputPort);

#if(_HDMI_SUPPORT == _ON)
        if(enumPortType == _PORT_HDMI)
        {
            EnumUserHdmi5vStatus enumHpdPinDetectResult = _HDMI_5V_STATUS_LOW;
            EnumUserHdmi5vStatus enumSourcePowerBackup = UserCommonCecHalGetSourcePowerStatus(ucInputPort);

#if(_HDMI20_SUPPORT == _ON)
            enumHpdPinDetectResult = ScalerTmdsMacRxGetHpd5vPinHighFlag(ucInputPort);
#endif

            // AC on, first time detect 5V
            if(g_ucCecFirstUpdateSource5V == _TRUE)
            {
                if(enumHpdPinDetectResult == _HDMI_5V_STATUS_HIGH)
                {
                    UserCommonCecHalSetSourcePowerStatus(ucInputPort, _HDMI_5V_STATUS_HIGH);
                    SET_CEC_LA_POLLING_BY_SOURCE_POWER();

                    DebugMessageCEC("[CEC][RX] First 5V High", ucInputPort);
                }
            }
            else
            {
                if((enumHpdPinDetectResult == _HDMI_5V_STATUS_LOW) && (enumSourcePowerBackup != _HDMI_5V_STATUS_LOW))
                {
                    UserCommonCecHalSetSourcePowerStatus(ucInputPort, _HDMI_5V_STATUS_LOW);

                    DebugMessageCEC("[CEC][RX] 5V High -> Low", ucInputPort);
                }
                else if(enumHpdPinDetectResult == _HDMI_5V_STATUS_HIGH)
                {
                    // 5V Low -> High
                    if(enumSourcePowerBackup == _HDMI_5V_STATUS_LOW)
                    {
                        UserCommonCecHalSetSourcePowerStatus(ucInputPort, _HDMI_5V_STATUS_HIGH);
                        SET_CEC_LA_POLLING_BY_SOURCE_POWER();

                        DebugMessageCEC("[CEC][RX] 5V Low -> High", ucInputPort);
                    }
                }
            }
        }
    }

    // start polling when cable plug in
    if(GET_CEC_LA_POLLING_BY_SOURCE_POWER() == _TRUE)
    {
        if(g_ucCecFirstUpdateSource5V == _TRUE)
        {
            g_ucCecFirstUpdateSource5V = _FALSE;
        }

        CLR_CEC_LA_POLLING_BY_SOURCE_POWER();
        REBUILD_CEC_TOPOLOGY();
        DebugMessageCEC("[CEC][RX] Rebuild Topology", 0);
    }
    else
    {
        for(ucTemp = 0; ucTemp < _HDMI_CEC_PORT_AMOUNT; ucTemp++)
        {
            if((SysSourceGetCableStatusChange(tCecSupportPort[ucTemp]) == _TRUE) && (SysSourceGetCableDetect(tCecSupportPort[ucTemp]) == _FALSE))
            {
                // Reset Action Port and the PA of that LA
                DebugMessageCEC("[CEC][RX] Unplug HDMI Cable", tCecSupportPort[ucTemp]);
                DELETE_CEC_UNPLUGGED_DEVICE(ucTemp);
            }
        }
#endif
    }
}

//--------------------------------------------------
// Description  : User Common CEC HAL Receive Audio Descriptor Porcess
// Input Value  : pstCecRxInfo
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalReceiveAudioDescriptorProc(StructCecRxReceivedInfo *pstCecRxInfo)
{
    BYTE ucArrayIndex = 0;

    if(pstCecRxInfo->pucReceivedDb[0] == _CEC_OPCODE_REPORT_SHORT_AUDIO_DESCRIPTOR)
    {
        if(GET_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY() == _TRUE)
        {
            CLR_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY();
            CLR_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_TIMEOUT();
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY);

            for(ucArrayIndex = 0; ucArrayIndex < (pstCecRxInfo->ucDbLength - 1); ucArrayIndex++)
            {
                DebugMessageCEC("[CEC][RX] SHORT AUDIO DESCRIPTOR index", GET_CEC_SINK_AUDIO_DESCRIPTOR_LENGTH());
                SET_CEC_SINK_AUDIO_DESCRIPTOR_BUFFER(pstCecRxInfo->pucReceivedDb[1 + ucArrayIndex]);
                DebugMessageCEC("[CEC][RX] SHORT AUDIO DESCRIPTOR value", GET_CEC_SINK_AUDIO_DESCRIPTOR_BUFFER(GET_CEC_SINK_AUDIO_DESCRIPTOR_LENGTH() - 1));
            }
        }
    }
    else if((pstCecRxInfo->pucReceivedDb[0] == _CEC_OPCODE_FEATURE_ABORT) &&
            (pstCecRxInfo->pucReceivedDb[1] == _CEC_OPCODE_REQUEST_SHORT_AUDIO_DESCRIPTOR))
    {
        if(GET_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY() == _TRUE)
        {
            CLR_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY();
            CLR_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_TIMEOUT();
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY);
        }
    }
}

//--------------------------------------------------
// Description  : User Common CEC HAL Set Wait For Audio Descriptor Reply Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalSetWaitForAudioDescriptorReplyTimeout(void)
{
    SET_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_TIMEOUT();
}

//--------------------------------------------------
// Description  : User Common CEC HAL Get Polling Audio Descriptor Count
// Input Value  : pstCecRxInfo
// Output Value : Polling Audio Descriptor Count
//--------------------------------------------------
BYTE UserCommonCecHalGetPollingAudioDescriptorCount(void)
{
    return GET_CEC_POLLING_AUDIO_DESCRIPTOR_COUNT();
}

//--------------------------------------------------
// Description  : User Common CEC HAL Active Wait for Audio Descriptor Reply Timer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalActiveWaitForAudioDescriptorReplyTimer(void)
{
    CLR_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_TIMEOUT();
    ScalerTimerActiveTimerEvent(_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_DURATION, _SYSTEM_TIMER_EVENT_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY);
}

//--------------------------------------------------
// Description  : User Common CEC HAL Start Polling Audio Descriptor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalStartPollingAudioDescriptor(void)
{
    SET_CEC_POLLING_AUDIO_DESCRIPTOR_START();
    SET_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY();
    CLR_CEC_POLLING_AUDIO_DESCRIPTOR_COUNT();
    CLR_CEC_SINK_AUDIO_DESCRIPTOR_RECEIVED();

    UserCommonCecHalPushTxMessageSendQueue(_CEC_OPCODE_REQUEST_SHORT_AUDIO_DESCRIPTOR);
}

//--------------------------------------------------
// Description  : User Common CEC HAL Stop Polling Audio Descriptor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalStopPollingAudioDescriptor(void)
{
    CLR_CEC_POLLING_AUDIO_DESCRIPTOR_START();
    CLR_CEC_SINK_AUDIO_DESCRIPTOR_RECEIVED();
    CLR_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY();
    CLR_CEC_POLLING_AUDIO_DESCRIPTOR_COUNT();
    CLR_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_TIMEOUT();
    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY);
}

//--------------------------------------------------
// Description  : User Common CEC HAL Polling Audio Descriptor Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalPollingAudioDescriptorHandler(void)
{
    if(GET_CEC_POLLING_AUDIO_DESCRIPTOR_START() == _TRUE)
    {
        if((GET_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY() == _FALSE) || (GET_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_TIMEOUT() == _TRUE))
        {
            if(GET_CEC_POLLING_AUDIO_DESCRIPTOR_COUNT() < 3)
            {
                SET_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY();
                SET_CEC_POLLING_AUDIO_DESCRIPTOR_COUNT(GET_CEC_POLLING_AUDIO_DESCRIPTOR_COUNT() + 1);

                UserCommonCecHalPushTxMessageSendQueue(_CEC_OPCODE_REQUEST_SHORT_AUDIO_DESCRIPTOR);

                DebugMessageCEC("[CEC][TX]: Audio Decriptor Polling Count", GET_CEC_POLLING_AUDIO_DESCRIPTOR_COUNT());
            }
            else
            {
                // Polling Done

                if(GET_CEC_SINK_AUDIO_DESCRIPTOR_LENGTH() > 0)
                {
                    SET_CEC_SINK_AUDIO_DESCRIPTOR_RECEIVED();
                }

                CLR_CEC_POLLING_AUDIO_DESCRIPTOR_START();
                CLR_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY();
                CLR_CEC_POLLING_AUDIO_DESCRIPTOR_COUNT();
                CLR_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY_TIMEOUT();
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CEC_WAIT_FOR_AUDIO_DESCRIPTOR_REPLY);
            }
        }
    }
}

//--------------------------------------------------
// Description  : User CEC Get Polling Audio Descriptor Result
// Input Value  : None
// Output Value : EnumCecPollingAudioDescriptorResult
//--------------------------------------------------
EnumCecPollingAudioDescriptorResult UserCommonCecHalGetPollingAudioDescriptorResult(void)
{
    if(GET_CEC_SINK_AUDIO_DESCRIPTOR_RECEIVED() == _TRUE)
    {
        return _SINK_AUDIO_DESCRIPTOR_RECEIVED;
    }

    return _SINK_AUDIO_DESCRIPTOR_NOT_RECEIVED;
}

//--------------------------------------------------
// Description  : User Common CEC HAL Get Sink Audio Descriptor Buffer Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalGetSinkAudioDescriptorInfo(StructCecAudioDescriptorInfo *pstCecAudioDescriptorInfo)
{
    pstCecAudioDescriptorInfo->pucBufferPtr = &GET_CEC_SINK_AUDIO_DESCRIPTOR_BUFFER(0);
    pstCecAudioDescriptorInfo->ucBufferSize = _CEC_SINK_AUDIO_DESCRIPTOR_MAX_LENGTH;
    pstCecAudioDescriptorInfo->ucAudioDescriptorLength = GET_CEC_SINK_AUDIO_DESCRIPTOR_LENGTH();
}

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Common CEC HAL Set Source Power Status
// Input Value  : enumInputPort, enumHdmi5vStatus
// Output Value : None
//--------------------------------------------------
void UserCommonCecHalSetSourcePowerStatus(EnumInputPort enumInputPort, EnumUserHdmi5vStatus enumHdmi5vStatus)
{
    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            SET_CEC_D0_HDMI_SOURCE_POWER(enumHdmi5vStatus);
            break;

        case _D1_INPUT_PORT:
            SET_CEC_D1_HDMI_SOURCE_POWER(enumHdmi5vStatus);
            break;

        case _D2_INPUT_PORT:
            SET_CEC_D2_HDMI_SOURCE_POWER(enumHdmi5vStatus);
            break;

        case _D3_INPUT_PORT:
            SET_CEC_D3_HDMI_SOURCE_POWER(enumHdmi5vStatus);
            break;

        case _D4_INPUT_PORT:
            SET_CEC_D4_HDMI_SOURCE_POWER(enumHdmi5vStatus);
            break;

        case _D5_INPUT_PORT:
            SET_CEC_D5_HDMI_SOURCE_POWER(enumHdmi5vStatus);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : User Common CEC HAL Get Source Power Status
// Input Value  : enumInputPort
// Output Value : EnumUserHdmi5vStatus
//--------------------------------------------------
EnumUserHdmi5vStatus UserCommonCecHalGetSourcePowerStatus(EnumInputPort enumInputPort)
{
    EnumUserHdmi5vStatus enumHdmi5vStatus = _HDMI_5V_STATUS_LOW;

    switch(enumInputPort)
    {
        case _D0_INPUT_PORT:
            enumHdmi5vStatus = GET_CEC_D0_HDMI_SOURCE_POWER();
            break;

        case _D1_INPUT_PORT:
            enumHdmi5vStatus = GET_CEC_D1_HDMI_SOURCE_POWER();
            break;

        case _D2_INPUT_PORT:
            enumHdmi5vStatus = GET_CEC_D2_HDMI_SOURCE_POWER();
            break;

        case _D3_INPUT_PORT:
            enumHdmi5vStatus = GET_CEC_D3_HDMI_SOURCE_POWER();
            break;

        case _D4_INPUT_PORT:
            enumHdmi5vStatus = GET_CEC_D4_HDMI_SOURCE_POWER();
            break;

        case _D5_INPUT_PORT:
            enumHdmi5vStatus = GET_CEC_D5_HDMI_SOURCE_POWER();
            break;

        default:
            break;
    }

    return enumHdmi5vStatus;
}
#endif // End of #if(_HDMI_SUPPORT == _ON)
#endif // End of #if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
#endif // End of #if(_HDMI_CEC_SUPPORT == _ON)