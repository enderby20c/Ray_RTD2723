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
// ID Code      : UserCommonDdcci.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DDCCI__

#include "UserCommonInclude.h"
#include "DDCCI/UserCommonDdcci.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_DDCCI_CODE_REDUCTION == _OFF)

#if(_VGA_SUPPORT == _ON)
BYTE code tCP_STRING_DSUB[] =
{
    _CAPABILITIES_STRING_VGA
};
#endif

#if(_HDMI_SUPPORT == _ON)
BYTE code tCP_STRING_HDMI[] =
{
    _CAPABILITIES_STRING_HDMI
};
#endif

#if(_DP_SUPPORT == _ON)
unsigned char code tCP_STRING_DP[] =
{
    _CAPABILITIES_STRING_DP
};
#endif

#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DDCCI_CODE_REDUCTION == _OFF)
//--------------------------------------------------
// Description  : User Common DDC Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciHandler(void)
{
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
    if(GET_RUN_DDCCI_AUTO_CHANNEL_COMMAND() == _FAIL)
    {
        if(GET_RECEIVE_DDCCI0_CMD_NOT_FINISH() == _TRUE)
        {
            // Polling User Ddcci Cmd Finished
            ScalerTimerActiveTimerEvent(_CLR_DDCCI0_CMD_RECEIVE_NOT_FINISH_TIMEOUT, _SYSTEM_TIMER_EVENT_CLR_DDCCI0_RECEIVE_COMMAND_NOT_FINISH);
        }
        else
        {
            CLR_DDCCI_AUTO_SWITCH();

            // Enable DDCCI Channel Auto Switch
            SET_DDCCI_AUTO_SWITCH();

            // Set Other DDC Enable
            ScalerMcuDdcciAutoSwitchEnableChannel();
        }
    }
#endif
#endif
    if(UserCommonDdcciKernelHandler() == _TRUE)
    {
        return;
    }

    UserInterfaceDdcciHandler();
}

//--------------------------------------------------
// Description  : Initial TX variables and Send Null-Message
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciInitTx(void)
{
    // Send Null-Message
    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG;
    g_pucMcuDdcciTxBuf[_DDCCI_COMMAND] = UserCommonDdcciCalCheckSum();

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    if(GET_RUN_DDCCI_COMMAND_SRC(GET_RUN_DDCCI_HANDLE_CHANNEL()) == _DDCCI_CMD_SRC_I2C)
#endif
    {
        ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);
    }
}

//--------------------------------------------------
// Description  : Initial RX variables
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciInitRx(void)
{
    // Clear temp buffer
    memset(g_pucMcuDdcciRxBuf, 0, _DDCCI0_RXBUF_LENGTH);

    // Clear buffer for new message
    if(g_ucMcuDdcciHandlerInx < _MULTI_DISPLAY_MAX)
    {
        memset(g_ppucMcuDdcciGroupRxBuf[g_ucMcuDdcciHandlerInx], 0, _DDCCI_RXBUF_LENGTH);
    }
}

//--------------------------------------------------
// Description  : Caculate checksum
// Input Value  : None
// Output Value : ucSum --> Checksum value
//--------------------------------------------------
BYTE UserCommonDdcciCalCheckSum(void)
{
    BYTE ucCount = 0;
    BYTE ucCheckLen = 0;
    BYTE ucSum = _DDCCI_VIRTUAL_HOST_ADDRESS;

    ucCheckLen = (g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] & 0x7F) + 2;

    for(ucCount = 0; ucCount < ucCheckLen; ucCount++)
    {
        ucSum = ucSum ^ g_pucMcuDdcciTxBuf[ucCount];
    }

    return ucSum;
}

//--------------------------------------------------
// Description  : DDCCI VCP Feature Reply Max and Present Value
// Input Value  : ucOpcode --> OPCODE
//                  usMax --> Maximum Value
//                  usPresent --> Present Value
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciSetVCPReplyValue(BYTE ucTypeOpcode, WORD usMax, WORD usPresent)
{
    g_pucMcuDdcciTxBuf[_DDCCI_TYPE_CODE] = ucTypeOpcode;
    g_pucMcuDdcciTxBuf[_DDCCI_MAX_HIGH_BYTE] = HIBYTE(usMax);
    g_pucMcuDdcciTxBuf[_DDCCI_MAX_LOW_BYTE] = LOBYTE(usMax);
    g_pucMcuDdcciTxBuf[_DDCCI_PRESENT_HIGH_BYTE] = HIBYTE(usPresent);
    g_pucMcuDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE] = LOBYTE(usPresent);
}

//--------------------------------------------------
// Description  : DDCCI Get and Reply Timing Report
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciGetTimingReport(EnumDisplayRegion enumDisplayRegion)
{
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucMcuDdcciTxBuf[_DDCCI_TIMING_MSG_COMMAND] = _DDCCI_CMD_REPLY_TIMING_MESSAGE;
    g_pucMcuDdcciTxBuf[_DDCCI_TIMING_MSG_OPCODE] = _DDCCI_OPCODE_TIMING_MSG;
    g_pucMcuDdcciTxBuf[_DDCCI_TIMING_STATUS] = 0x00;

    // H sync pol :Bit 1 = 1:positive H-sync polarity
    if(GET_INPUT_TIMING_H_POLARITY() != 0)
    {
        g_pucMcuDdcciTxBuf[_DDCCI_TIMING_STATUS] |= _BIT1;
    }

    // V sync pol :Bit 0 = 1:positive V-sync polarity
    if(GET_INPUT_TIMING_V_POLARITY() != 0)
    {
        g_pucMcuDdcciTxBuf[_DDCCI_TIMING_STATUS] |= _BIT0;
    }

    g_pucMcuDdcciTxBuf[_DDCCI_TIMING_HFREQ_HBYTE] = HIBYTE(GET_INPUT_TIMING_HFREQ() * 10);
    g_pucMcuDdcciTxBuf[_DDCCI_TIMING_HFREQ_LBYTE] = LOBYTE(GET_INPUT_TIMING_HFREQ() * 10);
    g_pucMcuDdcciTxBuf[_DDCCI_TIMING_VFREQ_HBYTE] = HIBYTE(GET_INPUT_TIMING_VFREQ() * 10);
    g_pucMcuDdcciTxBuf[_DDCCI_TIMING_VFREQ_LBYTE] = LOBYTE(GET_INPUT_TIMING_VFREQ() * 10);
    g_pucMcuDdcciTxBuf[_DDCCI_TIMING_VFREQ_LBYTE + 1] = UserCommonDdcciCalCheckSum();

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    if(GET_RUN_DDCCI_COMMAND_SRC(GET_RUN_DDCCI_HANDLE_CHANNEL()) == _DDCCI_CMD_SRC_I2C)
#endif
    {
        ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);
    }
}

//--------------------------------------------------
// Description  : DDCCI Capabilities Request & Reply
// Input Value  : enDdcciChannel --> DDCCI Channel Index
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciGetCapabilitiesRequest(EnumDDCCIPort enumDdcciChannel)
{
    WORD usOffset = 0;
    BYTE ucSendLen = 0;
    EnumPortType enumPortType = _PORT_NONE;
    WORD usCreqLen = 0;

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    if(GET_RUN_DDCCI_COMMAND_SRC(GET_RUN_DDCCI_HANDLE_CHANNEL()) == _DDCCI_CMD_SRC_MST)
    {
        enumPortType = _PORT_DP;
    }
    else
#endif
    {
        enumPortType = SysSourceGetPortTypeFromInputPort(ScalerMcuDdcciGetInputPort(enumDdcciChannel));
    }

    usCreqLen = UserCommonDdcciGetCpStringSize(enumPortType);

    // calculate offset & length
    usOffset = TO_WORD(g_pucMcuDdcciRxBuf[_DDCCI_OFS_HIGH_BYTE], g_pucMcuDdcciRxBuf[_DDCCI_OFS_LOW_BYTE]);

    if(usOffset >= usCreqLen)
    {
        ucSendLen = 0;
    }
    else if(usCreqLen > (usOffset + ScalerMcuDdcciGetBufferSize() - 6))
    {
        ucSendLen = ScalerMcuDdcciGetBufferSize() - 6;
    }
    else
    {
        ucSendLen = usCreqLen - usOffset;
    }

    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | (ucSendLen + 3);
    g_pucMcuDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_CAPABILITIES_REQUEST_REPLY;
    g_pucMcuDdcciTxBuf[_DDCCI_OFS_HIGH_BYTE] = g_pucMcuDdcciRxBuf[_DDCCI_OFS_HIGH_BYTE];
    g_pucMcuDdcciTxBuf[_DDCCI_OFS_LOW_BYTE] = g_pucMcuDdcciRxBuf[_DDCCI_OFS_LOW_BYTE];

    UserCommonDdcciGetCpStringData(&g_pucMcuDdcciTxBuf[_DDCCI_OFS_LOW_BYTE + 1], enumPortType, usOffset, ucSendLen);

    g_pucMcuDdcciTxBuf[_DDCCI_OFS_LOW_BYTE + 1 + ucSendLen] = UserCommonDdcciCalCheckSum();

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    if(GET_RUN_DDCCI_COMMAND_SRC(GET_RUN_DDCCI_HANDLE_CHANNEL()) == _DDCCI_CMD_SRC_I2C)
#endif
    {
        ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);
    }
}

//--------------------------------------------------
// Description  : Get capability string data
// Input Value  : pucDest -> destination
//                enumPortType -> port type
//                usStartIndex -> data offset
//                usLength -> data length
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciGetCpStringData(BYTE *pucDest, EnumPortType enumPortType, WORD usStartIndex, WORD usLength)
{
#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _ON)

    UserInterfaceDdcciGetCpStringData(pucDest, enumPortType, usStartIndex, usLength);

#else

    switch(enumPortType)
    {
#if(_VGA_SUPPORT == _ON)
        case _PORT_VGA:
            memcpy(pucDest, &tCP_STRING_DSUB[usStartIndex], usLength);
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
        case _PORT_HDMI20:
            memcpy(pucDest, &tCP_STRING_HDMI[usStartIndex], usLength);
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
            memcpy(pucDest, &tCP_STRING_DP[usStartIndex], usLength);
            break;
#endif

        default:
            break;
    }

#endif
}

//--------------------------------------------------
// Description  : Get capability string size
// Input Value  : enumPortType -> port type
// Output Value : size
//--------------------------------------------------
WORD UserCommonDdcciGetCpStringSize(EnumPortType enumPortType)
{
#if(_DDCCI_CUSTOM_CAPABILITY_STR_SUPPORT == _ON)

    return UserInterfaceDdcciGetCpStringSize(enumPortType);

#else

    switch(enumPortType)
    {
#if(_VGA_SUPPORT == _ON)
        case _PORT_VGA:
            return (sizeof(tCP_STRING_DSUB) - 1);
#endif

#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
        case _PORT_HDMI20:
            return (sizeof(tCP_STRING_HDMI) - 1);
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
            return (sizeof(tCP_STRING_DP) - 1);
#endif

        default:
            return 0;
    }

#endif
}

//--------------------------------------------------
// Description  : Get Fw Info Requeset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciGetFwInfoRequest(void)
{
    BYTE ucSendLen = 0;

    g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucMcuDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_GET_FW_INFO_REQUEST;

    switch(g_pucMcuDdcciRxBuf[_DDCCI_SINK_OPCODE])
    {
#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
        case _DDCCI_OPCODE_GET_CURRENT_FW_VER_REQUEST:
            ucSendLen = 3;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLen;
            ScalerFwInfoGetCurrentVersion(&g_pucMcuDdcciTxBuf[3]);
            g_pucMcuDdcciTxBuf[5] = UserCommonDdcciCalCheckSum();
            break;
        case _DDCCI_OPCODE_GET_FW_VER_LOCATE_REQUEST:
            ucSendLen = 6;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLen;
            ScalerFwInfoGetFwVersionAddress(&g_pucMcuDdcciTxBuf[3]);
            g_pucMcuDdcciTxBuf[8] = UserCommonDdcciCalCheckSum();
            break;
#endif

        case _DDCCI_OPCODE_GET_DUAL_BANK_INFO_REQUEST:
            ucSendLen = 11;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLen;
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
            UserCommonDualBankUserGetFwInfo(&g_pucMcuDdcciTxBuf[3]);
#else
            // Byte Count
            g_pucMcuDdcciTxBuf[3] = 9;

            // Dual bank Support
            g_pucMcuDdcciTxBuf[4] = _DUAL_BANK_SUPPORT;

            // Dual bank Type
            g_pucMcuDdcciTxBuf[5] = _DUAL_BANK_TYPE;

            // Active User(1)
            g_pucMcuDdcciTxBuf[6] = 0xFF;

#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
            ScalerFwInfoGetCurrentVersion(&g_pucMcuDdcciTxBuf[7]);
            memset(&g_pucMcuDdcciTxBuf[9], 0xFFU, 4);
#else
            // User1 Version(2) + User2 Version(2) + Reserved(2)
            memset(&g_pucMcuDdcciTxBuf[7], 0xFFU, 6);
#endif

#endif
            g_pucMcuDdcciTxBuf[13] = UserCommonDdcciCalCheckSum();
            break;

        default:
            UserCommonDdcciInitTx();
            break;
    }
    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);
}

//--------------------------------------------------
// Description  : RTK DDCCI  Handler for dual bank
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonDdcciKernelHandler(void)
{
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
    BYTE ucOpCode = 0;

    if(UserInterfaceDdcciGetStatus() == _DDCCI_STATUS_ON)
    {
        // Check if Data is needed to be received
        // Reply data to source according to the request
        if(GET_RUN_DDCCI_COMMAND() == _SUCCESS)
        {
            // Copy any rx buffer input message to current DDC-CI port buffer
            UserInterfaceDdcciGetInputMsg();
            if(g_pucMcuDdcciRxBuf[_DDCCI_SOURCE] == _DDCCI_SRC_RTK_ADDRESS)
            {
                if(g_pucMcuDdcciRxBuf[_DDCCI_COMMAND] == _DDCCI_RTK_CMD_TYPE)
                {
                    ucOpCode = g_pucMcuDdcciRxBuf[_DDCCI_SOURCE_OPCODE];
                }
                // compatible  For Old Tool (0x6E, 0x51, 0xAA);
                // New Tool 0x6E, 0x71, 0xAA
                else if(g_pucMcuDdcciRxBuf[_DDCCI_COMMAND] == _DDCCI_CMD_SWITCH_DEBUG_SALVE_REQUEST)
                {
                    ucOpCode = g_pucMcuDdcciRxBuf[_DDCCI_COMMAND];
                }
                else
                {
                    return _FALSE;
                }
                switch(ucOpCode)
                {
                    case _DDCCI_CMD_GET_FW_INFO_REQUEST:
                        UserCommonDdcciGetFwInfoRequest();
                        break;
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
                    case _DDCCI_CMD_SWITCH_DEBUG_SALVE_REQUEST:
                        ScalerDebugSetDdcciSwitchState();
                        // Switch DDCCI to Debug Mode, No Matter Which Port as Auto-Switch
                        ScalerMcuDdcciSwitchPort(_DEBUG_MODE);
                        break;
#endif
#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
                    case _SCALER_FW_CHECK_CMD:
                        UserCommonDdcciFwCheck();
                        break;
#endif

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
                    case _SCALER_FW_UPDATE_CMD:
                        if(((_FW_UPDATE_BACKGROUND_SUPPORT == _ON) && (g_pucMcuDdcciRxBuf[4] == _FW_UPDATE_BACKGROUND_SUB_OP_CODE)) ||
                           ((_FW_UPDATE_FOREGROUND_SUPPORT == _ON) && (g_pucMcuDdcciRxBuf[4] == _FW_UPDATE_FOREGROUND_SUB_OP_CODE)))
                        {
                            ScalerFwUpdateSwitchState(_DDCCI_MODE, g_pucMcuDdcciRxBuf[4], GET_RUN_DDCCI_HANDLE_CHANNEL());
                        }
                        break;
#endif
                    default:
                        UserCommonDdcciInitTx();
                        break;
                }

                UserCommonDdcciInitRx();
                CLR_RUN_DDCCI_COMMAND(GET_RUN_DDCCI_HANDLE_CHANNEL());
                return _TRUE;
            }
        }
    }
    else
#endif
    {
#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
        UserCommonDdcciKernelCustomerDebugCommandHandler();
#endif
    }
    return _FALSE;
}

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Customer Debug Commnd Handler
// Input Value  : None
// Output Value : _ON => DDCCI Support ON
//--------------------------------------------------
void UserCommonDdcciKernelCustomerDebugCommandHandler(void)
{
    BYTE ucReplyLen = 0;
    BYTE pucReplyData[16] = {0};

    if(GET_CUSTOMER_CMD_REV_STATE() == _TRUE)
    {
        UserInterfaceDdcciCustomerDebugHandler(ScalerDebugGetCustomerDebugRevData(), &ucReplyLen, pucReplyData);
        ScalerDebugSendData(ucReplyLen, pucReplyData);
        CLR_CUSTOMER_CMD_REV_STATE();
    }
}
#endif

#endif



//--------------------------------------------------
// Description  : DDCCI Maping to DDC Channel
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciMapping(void)
{
    if(ScalerDebugGetDDCCIDebugMode() == _DDCCI_MODE)
    {
        BYTE ucUsedDdcciCount = 0;
#if(_MULTI_DISPLAY_MAX >= 0x02)
        BYTE ucMaxDisplayCount = SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX);
#endif

        // 1P mode
        // Region 0 Ddcci Mapping
        if(GET_DDCCI_AUTO_SWITCH() == _TRUE)
        {
            CLR_DDCCI_AUTO_SWITCH();
        }

        ScalerMcuDdcciSelectDdcChannel(_DDCCI0, SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_0)));

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
        // Reopen Auto Switch
        if(GET_DDCCI_AUTO_SWITCH() == _FALSE)
        {
            SET_DDCCI_AUTO_SWITCH();
        }
#endif

#if(_MULTI_DISPLAY_MAX >= 0x02)
        // 2P mode
        if(ucMaxDisplayCount >= 0x02)
        {
            // Region 1 Ddcci Mapping
            if(SysRegionGetSourceIndex(_REGION_INDEX_1) != SysRegionGetSourceIndex(_REGION_INDEX_0))
            {
                ScalerMcuDdcciSelectDdcChannel(_DDCCI1 + ucUsedDdcciCount, SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_1)));
                ucUsedDdcciCount++;
            }
        }
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
        // 3P mode
        if(ucMaxDisplayCount >= 0x03)
        {
            // Region 2 Ddcci Mapping
            if((SysRegionGetSourceIndex(_REGION_INDEX_2) != SysRegionGetSourceIndex(_REGION_INDEX_1)) &&
               (SysRegionGetSourceIndex(_REGION_INDEX_2) != SysRegionGetSourceIndex(_REGION_INDEX_0)))
            {
                ScalerMcuDdcciSelectDdcChannel(_DDCCI1 + ucUsedDdcciCount, SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_2)));
                ucUsedDdcciCount++;
            }
        }
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
        // 4P mode
        if(ucMaxDisplayCount >= 0x04)
        {
            // Region 3 Ddcci Mapping
            if((SysRegionGetSourceIndex(_REGION_INDEX_3) != SysRegionGetSourceIndex(_REGION_INDEX_2)) &&
               (SysRegionGetSourceIndex(_REGION_INDEX_3) != SysRegionGetSourceIndex(_REGION_INDEX_1)) &&
               (SysRegionGetSourceIndex(_REGION_INDEX_3) != SysRegionGetSourceIndex(_REGION_INDEX_0)))
            {
                ScalerMcuDdcciSelectDdcChannel(_DDCCI1 + ucUsedDdcciCount, SysRegionGetInputPort(SysRegionGetDisplayRegion(_REGION_INDEX_3)));
                ucUsedDdcciCount++;
            }
        }
#endif

        switch(ucUsedDdcciCount)
        {
            case 0:
                // Disable DDC-CI 1~3
                ScalerMcuDdcciSelectDdcChannel(_DDCCI1, _NO_INPUT_PORT);
                ScalerMcuDdcciSelectDdcChannel(_DDCCI2, _NO_INPUT_PORT);
                ScalerMcuDdcciSelectDdcChannel(_DDCCI3, _NO_INPUT_PORT);
                break;

#if(_MULTI_DISPLAY_MAX >= 0x02)
            case 1:
                // Disable DDC-CI 2~3
                ScalerMcuDdcciSelectDdcChannel(_DDCCI2, _NO_INPUT_PORT);
                ScalerMcuDdcciSelectDdcChannel(_DDCCI3, _NO_INPUT_PORT);
                break;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
            case 2:
                // Disable DDC-CI 3
                ScalerMcuDdcciSelectDdcChannel(_DDCCI3, _NO_INPUT_PORT);
                break;
#endif

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : DDC-CI Switch Port
// Input Value  : DDCCI/Debug Mode
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciSwitchPort(EnumDDCCIDebugMode enumMode)
{
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
    if((ScalerFwUpdateGetState() == _FALSE) && (ScalerDebugGetDdcciSwitchState() == _FALSE))
#else
    if(ScalerDebugGetDdcciSwitchState() == _FALSE)
#endif
#endif
    {
        ScalerMcuDdcciSwitchPort(enumMode);
    }
}

//--------------------------------------------------
// Description  : Get DDC-CI Switch Port
// Input Value  : enumDdcciChannel -> DDCCI port
// Output Value : input port
//--------------------------------------------------
EnumInputPort UserCommonDdcciGetInputPort(EnumDDCCIPort enumDdcciChannel)
{
    return ScalerMcuDdcciGetInputPort(enumDdcciChannel);
}

//--------------------------------------------------
// Description  : Send DDC Data
// Input Value  : enDdcciChannel --> DDCCI Channel Index
//                pWriteArray --> Data to be sent
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciSendData(EnumDDCCIPort enumDdcciChannel, BYTE *pucWriteArray)
{
#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    if(GET_RUN_DDCCI_COMMAND_SRC(GET_RUN_DDCCI_HANDLE_CHANNEL()) == _DDCCI_CMD_SRC_I2C)
#endif
    {
        ScalerMcuDdcciSendData(enumDdcciChannel, pucWriteArray);
    }
}
#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FW check Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciFwCheck(void)
{
    g_pucMcuDdcciTxBuf[0] = _DDCCI_DEST_ADDRESS;
    g_pucMcuDdcciTxBuf[_DDCCI_COMMAND] = _SCALER_FW_CHECK_CMD;

    switch(g_pucMcuDdcciRxBuf[_DDCCI_SINK_OPCODE])
    {
        case _SCALER_FW_CHECK_SUB_OP_GET_ADDR:
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x07;
            ScalerFwCheckGetProjectIDAddress(&g_pucMcuDdcciTxBuf[3]);
            g_pucMcuDdcciTxBuf[9] = UserCommonDdcciCalCheckSum();
            break;

        case _SCALER_FW_CHECK_SUB_OP_VERIFY:
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x03;
            g_pucMcuDdcciTxBuf[3] = ScalerFwCheckProjectIDVerify(&g_pucMcuDdcciRxBuf[5]);
            g_pucMcuDdcciTxBuf[5] = UserCommonDdcciCalCheckSum();
            break;

        default:
            UserCommonDdcciInitTx();
            break;
    }
    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucMcuDdcciTxBuf);
}
#endif


#if(_DDCCI_CODE_REDUCTION == _OFF)
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)

//--------------------------------------------------
// Description  : Get DDC-CI Data in Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciIntGetData(void)
{
    UserCommonDdcci0IntGetData();

#if(_MULTI_DISPLAY_MAX >= 0x02)
    UserCommonDdcci1IntGetData();
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
    UserCommonDdcci2IntGetData();
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
    UserCommonDdcci3IntGetData();
#endif
}

//--------------------------------------------------
// Description  : Get DDC-CI0 Data in Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcci0IntGetData(void)
{
    // Clear Unused DDCCI IRQ Flag
    SET_DDCCI0_STATUS2(GET_DDCCI0_STATUS2() & ~(_BIT5 | _BIT4));
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
    if(GET_DDCCI0_DDC_CHANNEL() == GET_DDCCI4_DDC_CHANNEL())
    {
        ScalerMcuDdcci0ClearWrongIntFlag();
    }
#endif
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
    if((GET_RUN_DDCCI0_COMMAND() == _SUCCESS) ||
       (GET_DDCCI0_DDC_CHANNEL() == GET_DDCCI1_DDC_CHANNEL()) ||
       (GET_DDCCI0_DDC_CHANNEL() == GET_DDCCI2_DDC_CHANNEL()) ||
       (GET_DDCCI0_DDC_CHANNEL() == GET_DDCCI3_DDC_CHANNEL()))
#elif(_MULTI_DISPLAY_MAX >= 0x03)
    if((GET_RUN_DDCCI0_COMMAND() == _SUCCESS) ||
       (GET_DDCCI0_DDC_CHANNEL() == GET_DDCCI1_DDC_CHANNEL()) ||
       (GET_DDCCI0_DDC_CHANNEL() == GET_DDCCI2_DDC_CHANNEL()))
#elif(_MULTI_DISPLAY_MAX >= 0x02)
    if((GET_RUN_DDCCI0_COMMAND() == _SUCCESS) ||
       (GET_DDCCI0_DDC_CHANNEL() == GET_DDCCI1_DDC_CHANNEL()))
#else
    if(GET_RUN_DDCCI0_COMMAND() == _SUCCESS)
#endif
    {
        // Clear Flags
        if((GET_DDCCI0_STATUS1() & _BIT0) == _BIT0)
        {
            CLR_DDCCI0_STATUS1(_BIT0);
        }

        if((GET_DDCCI0_STATUS1() & _BIT1) == _BIT1)
        {
            CLR_DDCCI0_STATUS1(_BIT1);
        }

        if((GET_DDCCI0_STATUS1() & _BIT2) == _BIT2)
        {
            volatile BYTE ucTemp = GET_DDCCI0_DATA_IN();
            ucTemp = ucTemp;

// For HP case, return Null Msg if Command isn't finish, Clear IIC Buffer
#if(_HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT == _ON)
            SET_DDCCI0_IRQ_STATUS(GET_DDCCI0_IRQ_STATUS() | _BIT6);
#endif
        }
    }
    else
    {
        SET_RUN_DDCCI_COMMAND_SRC(_DDCCI0, _DDCCI_CMD_SRC_I2C);

        if(GET_DDCCI0_SLAVE_ADDRESS() == _DDCCI_DEST_ADDRESS)
        {
#if((_OGC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_OCC_FUNCTION == _ON))

            if(ScalerMcuDdcciColorCalibrationCheckDisplayMode() == _TRUE) // 1P Mode or EagleSight Mode When OGC/OCC Support On
            {
                SET_RUN_DDCCI0_COMMAND(ScalerMcuDdcci0IntGetData(g_pucMcuDdcciRxBuf, _DDCCI0_RXBUF_LENGTH));
            }
            else
            {
                SET_RUN_DDCCI0_COMMAND(ScalerMcuDdcci0IntGetData(g_ppucMcuDdcciGroupRxBuf[_DDCCI0], _DDCCI_RXBUF_LENGTH));
            }
#else
            SET_RUN_DDCCI0_COMMAND(ScalerMcuDdcci0IntGetData(g_ppucMcuDdcciGroupRxBuf[_DDCCI0], _DDCCI_RXBUF_LENGTH));

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)

            ScalerMcuDdcciAutoSwitchDisableInactiveChannel();

            if((GET_RUN_DDCCI0_COMMAND() == _FAIL) && (g_pucMcuDdcciRetry[_DDCCI0] == _FALSE))
            {
                if(GET_RECEIVE_DDCCI0_CMD_NOT_FINISH() == _FALSE)
                {
                    SET_RECEIVE_DDCCI0_CMD_NOT_FINISH();
                }
            }
            else
            {
                if(GET_RECEIVE_DDCCI0_CMD_NOT_FINISH() == _TRUE)
                {
                    CLR_RECEIVE_DDCCI0_CMD_NOT_FINISH();

                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_CLR_DDCCI0_RECEIVE_COMMAND_NOT_FINISH);
                }
            }
#endif
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
            if(GET_RUN_DDCCI0_COMMAND() == _SUCCESS)
            {
                if(UserCommonDdcciHDMIFreesyncHandle(_DDCCI0) == _TRUE)
                {
                    SET_RUN_DDCCI0_COMMAND(_FAIL);
                }
            }
#endif

            g_pucMcuDdcciRetry[_DDCCI0] = _FALSE;
        }
        else
        {
            SET_RUN_DDCCI0_COMMAND(UserInterfaceDdcciGetFactoryCommand());
        }
    }
}

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Description  : Get DDC-CI1 Data in Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcci1IntGetData(void)
{
    // Clear Unused DDCCI IRQ Flag
    SET_DDCCI1_STATUS2(GET_DDCCI1_STATUS2() & ~(_BIT5 | _BIT4));

    if(GET_RUN_DDCCI1_COMMAND() == _SUCCESS)
    {
        // Clear Flags
        if((GET_DDCCI1_STATUS1() & _BIT0) == _BIT0)
        {
            CLR_DDCCI1_STATUS1(_BIT0);
        }

        if((GET_DDCCI1_STATUS1() & _BIT1) == _BIT1)
        {
            CLR_DDCCI1_STATUS1(_BIT1);
        }

        if((GET_DDCCI1_STATUS1() & _BIT2) == _BIT2)
        {
            volatile BYTE ucTemp = GET_DDCCI1_DATA_IN();
            ucTemp = ucTemp;

// For HP case, return Null Msg if Command isn't finish, Clear IIC Buffer
#if(_HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT == _ON)
            SET_DDCCI1_IRQ_STATUS(GET_DDCCI1_IRQ_STATUS() | _BIT6);
#endif
        }
    }
    else
    {
        SET_RUN_DDCCI_COMMAND_SRC(_DDCCI1, _DDCCI_CMD_SRC_I2C);

        if(GET_DDCCI1_SLAVE_ADDRESS() == _DDCCI_DEST_ADDRESS)
        {
            SET_RUN_DDCCI1_COMMAND(ScalerMcuDdcci1IntGetData(g_ppucMcuDdcciGroupRxBuf[_DDCCI1]));

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
            if(GET_RUN_DDCCI1_COMMAND() == _SUCCESS)
            {
                if(UserCommonDdcciHDMIFreesyncHandle(_DDCCI1) == _TRUE)
                {
                    SET_RUN_DDCCI1_COMMAND(_FAIL);
                }
            }
#endif

            g_pucMcuDdcciRetry[_DDCCI1] = _FALSE;
        }
        else
        {
            SET_RUN_DDCCI1_COMMAND(UserInterfaceDdcciGetFactoryCommand());
        }
    }
}
#endif // End of #if(_MULTI_DISPLAY_MAX >= 0x02)

#if(_MULTI_DISPLAY_MAX >= 0x03)
//--------------------------------------------------
// Description  : Get DDC-CI2 Data in Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcci2IntGetData(void)
{
    // Clear Unused DDCCI IRQ Flag
    SET_DDCCI2_STATUS2(GET_DDCCI2_STATUS2() & ~(_BIT5 | _BIT4));

    if(GET_RUN_DDCCI2_COMMAND() == _SUCCESS)
    {
        // Clear Flags
        if((GET_DDCCI2_STATUS1() & _BIT0) == _BIT0)
        {
            CLR_DDCCI2_STATUS1(_BIT0);
        }

        if((GET_DDCCI2_STATUS1() & _BIT1) == _BIT1)
        {
            CLR_DDCCI2_STATUS1(_BIT1);
        }

        if((GET_DDCCI2_STATUS1() & _BIT2) == _BIT2)
        {
            volatile BYTE ucTemp = GET_DDCCI2_DATA_IN();
            ucTemp = ucTemp;

// For HP case, return Null Msg if Command isn't finish, Clear IIC Buffer
#if(_HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT == _ON)
            SET_DDCCI2_IRQ_STATUS(GET_DDCCI2_IRQ_STATUS() | _BIT6);
#endif
        }
    }
    else
    {
        SET_RUN_DDCCI_COMMAND_SRC(_DDCCI2, _DDCCI_CMD_SRC_I2C);

        if(GET_DDCCI2_SLAVE_ADDRESS() == _DDCCI_DEST_ADDRESS)
        {
            SET_RUN_DDCCI2_COMMAND(ScalerMcuDdcci2IntGetData(g_ppucMcuDdcciGroupRxBuf[_DDCCI2]));

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
            if(GET_RUN_DDCCI2_COMMAND() == _SUCCESS)
            {
                if(UserCommonDdcciHDMIFreesyncHandle(_DDCCI2) == _TRUE)
                {
                    SET_RUN_DDCCI2_COMMAND(_FAIL);
                }
            }
#endif

            g_pucMcuDdcciRetry[_DDCCI2] = _FALSE;
        }
        else
        {
            SET_RUN_DDCCI2_COMMAND(UserInterfaceDdcciGetFactoryCommand());
        }
    }
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// Description  : Get DDC-CI3 Data in Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcci3IntGetData(void)
{
    // Clear Unused DDCCI IRQ Flag
    SET_DDCCI3_STATUS2(GET_DDCCI3_STATUS2() & ~(_BIT5 | _BIT4));

    if(GET_RUN_DDCCI3_COMMAND() == _SUCCESS)
    {
        // Clear Flags
        if((GET_DDCCI3_STATUS1() & _BIT0) == _BIT0)
        {
            CLR_DDCCI3_STATUS1(_BIT0);
        }

        if((GET_DDCCI3_STATUS1() & _BIT1) == _BIT1)
        {
            CLR_DDCCI3_STATUS1(_BIT1);
        }

        if((GET_DDCCI3_STATUS1() & _BIT2) == _BIT2)
        {
            volatile BYTE ucTemp = GET_DDCCI3_DATA_IN();
            ucTemp = ucTemp;

// For HP case, return Null Msg if Command isn't finish, Clear IIC Buffer
#if(_HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT == _ON)
            SET_DDCCI3_IRQ_STATUS(GET_DDCCI3_IRQ_STATUS() | _BIT6);
#endif
        }
    }
    else
    {
        SET_RUN_DDCCI_COMMAND_SRC(_DDCCI3, _DDCCI_CMD_SRC_I2C);

        if(GET_DDCCI3_SLAVE_ADDRESS() == _DDCCI_DEST_ADDRESS)
        {
            SET_RUN_DDCCI3_COMMAND(ScalerMcuDdcci3IntGetData(g_ppucMcuDdcciGroupRxBuf[_DDCCI3]));

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
            if(GET_RUN_DDCCI3_COMMAND() == _SUCCESS)
            {
                if(UserCommonDdcciHDMIFreesyncHandle(_DDCCI3) == _TRUE)
                {
                    SET_RUN_DDCCI3_COMMAND(_FAIL);
                }
            }
#endif

            g_pucMcuDdcciRetry[_DDCCI3] = _FALSE;
        }
        else
        {
            SET_RUN_DDCCI3_COMMAND(UserInterfaceDdcciGetFactoryCommand());
        }
    }
}
#endif // End of #if(_MULTI_DISPLAY_MAX >= 0x04)

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Get HDMI Freesync support
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonDdcciHDMIFreesyncHandle(EnumDDCCIPort enumDdcciPort)
{
    BYTE ucDdcciCount = 0;
    BYTE pucDdcciRxBuf[3] = {0};

#if((_OGC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_OCC_FUNCTION == _ON))

    if(ScalerMcuDdcciColorCalibrationCheckDisplayMode() == _TRUE) // 1P Mode or EagleSight Mode When OGC/OCC Support On
    {
        pucDdcciRxBuf[0] = g_pucMcuDdcciRxBuf[_DDCCI_COMMAND];
        pucDdcciRxBuf[1] = g_pucMcuDdcciRxBuf[_DDCCI_SOURCE_OPCODE];
        pucDdcciRxBuf[2] = g_pucMcuDdcciRxBuf[_DDCCI_SET_HIGH_BYTE];
    }
    else
#endif
    {
        pucDdcciRxBuf[0] = g_ppucMcuDdcciGroupRxBuf[enumDdcciPort][_DDCCI_COMMAND];
        pucDdcciRxBuf[1] = g_ppucMcuDdcciGroupRxBuf[enumDdcciPort][_DDCCI_SOURCE_OPCODE];
        pucDdcciRxBuf[2] = g_ppucMcuDdcciGroupRxBuf[enumDdcciPort][_DDCCI_SET_HIGH_BYTE];
    }

    if(UserInterfaceDdcciCheckHDMIFreesyncOpcode(pucDdcciRxBuf[1]) == _DDCCI_STATUS_ON)
    {
        if(pucDdcciRxBuf[0] == _DDCCI_CMD_SET_VCP_FEATURE)
        {
            ScalerDrrFreeSyncSetHdmiVcp(pucDdcciRxBuf[2]);
        }

        if(pucDdcciRxBuf[0] == _DDCCI_CMD_GET_VCP_FEATURE)
        {
            g_pucMcuDdcciTxBuf[_DDCCI_SOURCE] = 0x6E;
            g_pucMcuDdcciTxBuf[_DDCCI_LENGTH] = 0x88;
            g_pucMcuDdcciTxBuf[_DDCCI_COMMAND] = 0x02;
            g_pucMcuDdcciTxBuf[_DDCCI_RESULT_CODE] = 0x00;
            g_pucMcuDdcciTxBuf[_DDCCI_SINK_OPCODE] = pucDdcciRxBuf[1];
            g_pucMcuDdcciTxBuf[_DDCCI_TYPE_CODE] = 0x00;
            g_pucMcuDdcciTxBuf[_DDCCI_MAX_HIGH_BYTE] = 0x00;
            g_pucMcuDdcciTxBuf[_DDCCI_MAX_LOW_BYTE] = 0x00;
            g_pucMcuDdcciTxBuf[_DDCCI_PRESENT_HIGH_BYTE] = ScalerDrrFreeSyncGetHdmiVcp();
            g_pucMcuDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE] = ScalerDrrFreeSyncHdmiGetFreeSyncSupport(ScalerMcuDdcciGetInputPort(enumDdcciPort));

            g_pucMcuDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE + 1] = (((0xB4 ^ g_pucMcuDdcciTxBuf[_DDCCI_SINK_OPCODE]) ^ g_pucMcuDdcciTxBuf[_DDCCI_PRESENT_HIGH_BYTE]) ^ g_pucMcuDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE]);

            switch(enumDdcciPort)
            {
                case _DDCCI0:

                    // Enable mcu write
                    MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                    while(ucDdcciCount < 11)
                    {
                        // Load data to DDC-CI buffer
                        MCU_FF26_IIC_DATA_OUT = g_pucMcuDdcciTxBuf[ucDdcciCount++];
                    }

                    // Disable mcu write
                    MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
                    break;

#if(_MULTI_DISPLAY_MAX >= 0x02)
                case _DDCCI1:

                    // Enable mcu write
                    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                    while(ucDdcciCount < 11)
                    {
                        MCU_FE8A_IIC_1_DATA_OUT = g_pucMcuDdcciTxBuf[ucDdcciCount++];
                    }

                    // Disable mcu write
                    MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;
                    break;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
                case _DDCCI2:

                    // Enable mcu write
                    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                    while(ucDdcciCount < 11)
                    {
                        MCU_FE98_IIC_2_DATA_OUT = g_pucMcuDdcciTxBuf[ucDdcciCount++];
                    }

                    // Disable mcu write
                    MCU_FE9C_IIC_2_IRQ_CONTROL2 &= ~_BIT5;
                    break;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
                case _DDCCI3:

                    // Enable mcu write
                    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                    while(ucDdcciCount < 11)
                    {
                        MCU_FEA7_IIC_3_DATA_OUT = g_pucMcuDdcciTxBuf[ucDdcciCount++];
                    }

                    // Disable mcu write
                    MCU_FEAB_IIC_3_IRQ_CONTROL2 &= ~_BIT5;
                    break;
#endif
                default:
                    break;
            }

#if((_OGC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON) || (_OCC_FUNCTION == _ON))

            if(ScalerMcuDdcciColorCalibrationCheckDisplayMode() == _TRUE) // 1P Mode or EagleSight Mode When OGC/OCC Support On
            {
                // Clear buffer for new message
                memset(g_pucMcuDdcciRxBuf, 0, _DDCCI_RXBUF_LENGTH);
            }
            else
#endif
            {
                // Clear buffer for new message
                if(g_ucMcuDdcciHandlerInx < _MULTI_DISPLAY_MAX)
                {
                    memset(g_ppucMcuDdcciGroupRxBuf[g_ucMcuDdcciHandlerInx], 0, _DDCCI_RXBUF_LENGTH);
                }
            }
        }

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Get DDC-CI Status in Interrupt Process
// Input Value  : None
// Output Value : _TURE or _False
//--------------------------------------------------
bit UserCommonDdcciGetStatus(void)
{
    if(UserInterfaceDdcciGetStatus() == _DDCCI_STATUS_ON)
    {
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
        if(ScalerDebugGetDdcciSwitchState() == _TRUE)
        {
            return _FALSE;
        }
#endif
        return _TRUE;
    }
    return _FALSE;
}

#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#endif


