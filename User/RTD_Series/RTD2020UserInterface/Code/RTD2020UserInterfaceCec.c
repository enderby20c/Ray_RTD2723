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
// ID Code      : RTD2020UserInterfaceCec.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_CEC__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceCec.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

#if(_HDMI_CEC_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructCecUserInfo g_stCecUserInfo = {0};


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get CEC Fx Enable from user behavior
// Input Value  : NA
// Output Value : EnumCecFunctionEnable
//--------------------------------------------------
EnumCecFunctionEnable UserInterfaceCecGetCecActive(void)
{
    return _CEC_FX_ENABLE;
}

//--------------------------------------------------
// Description  : Reload data from CEC RX
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceCecReceivedNotify(StructCecRxReceivedInfo *pstCecRxInfo)
{
    BYTE ucArrayIndex = 0;

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
    BYTE ucDxPortIndex = 0;
#endif

    if(UserCommonCecRxGetMsgAnalyzingFlag() == _TRUE)
    {
        UserCommonCecRxClrIMsgAnalyzingFlag();

        if(UserCommonCecCheckFrameLengthIsLegal(pstCecRxInfo->pucReceivedDb[0], pstCecRxInfo->ucDbLength) == _TRUE)
        {
            switch(pstCecRxInfo->pucReceivedDb[0])
            {
                case _CEC_OPCODE_GIVE_DEVICE_POWER_STATUS:

                    DebugMessageCEC("[CEC][RX] GIVE_DEVICE_POWER_STATUS", pstCecRxInfo->pucReceivedDb[0]);
                    DebugMessageCEC("[CEC][RX] LA", pstCecRxInfo->ucReceivedHb);
                    DebugMessageCEC("[CEC][RX] GetPowerStatus", SysPowerGetPowerStatus());

                    if((pstCecRxInfo->ucReceivedHb & 0x0F) != _CEC_LA_BORADCAST)
                    {
                        // Reset cec tx struct
                        CLR_CEC_TX_DATA();

                        // Packing <Report Power Status>
                        SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | ((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4)));
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_REPORT_POWER_STATUS);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_1, ((SysPowerGetPowerStatus() != _POWER_STATUS_NORMAL) ? 0x01 : 0x00));

                        SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 2);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                        SET_CEC_TX_SEND();
                    }

                    break;

                case _CEC_OPCODE_GIVE_DEVICE_VENDOR_ID:

                    DebugMessageCEC("[CEC][RX] GIVE_DEVICE_VENDOR_ID", pstCecRxInfo->pucReceivedDb[0]);
                    DebugMessageCEC("[CEC][RX] LA", pstCecRxInfo->ucReceivedHb);

                    if((pstCecRxInfo->ucReceivedHb & 0x0F) != _CEC_LA_BORADCAST)
                    {
                        // Reset cec tx struct
                        CLR_CEC_TX_DATA();

                        // Receive <Give Device Vendor ID>, respond <Report Device Vendor ID>
                        SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | _CEC_LA_BORADCAST));
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_DEVICE_VENDOR_ID);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_1, 0x00);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_2, 0xE0);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_3, 0x4C);

                        SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 4);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                        SET_CEC_TX_SEND();
                    }

                    break;

                case _CEC_OPCODE_SET_OSD_NAME:

                    DebugMessageCEC("[CEC][RX] SET_OSD_NAME", pstCecRxInfo->ucDbLength);
                    DebugMessageCEC("[CEC][RX] LA", pstCecRxInfo->ucReceivedHb);

                    for(ucArrayIndex = 0; ucArrayIndex < pstCecRxInfo->ucDbLength - 1; ucArrayIndex++)
                    {
                        DebugMessageCEC("[CEC][RX] OSD NAME ASCII", pstCecRxInfo->pucReceivedDb[1 + ucArrayIndex]);
                    }

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
                    ucDxPortIndex = UserCommonCecHalGetDxPortByDeviceLogicalAddress((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4);

                    UserCommonCecHalSetOsdNameByDxPort(ucDxPortIndex, &(pstCecRxInfo->pucReceivedDb[1]), pstCecRxInfo->ucDbLength - 1);
#endif

                    break;

                case _CEC_OPCODE_REPORT_PHYSICAL_ADDRESS:

                    DebugMessageCEC("[CEC][RX] REPORT_PHYSICAL_ADDRESS", pstCecRxInfo->pucReceivedDb[0]);
                    DebugMessageCEC("[CEC][RX] LA", pstCecRxInfo->ucReceivedHb);
                    DebugMessageCEC("[CEC][RX] PA", (((WORD)pstCecRxInfo->pucReceivedDb[1] << 8) | pstCecRxInfo->pucReceivedDb[2]));

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
                    // Record PA of LA
                    UserCommonCecHalSetDeviceLogicalAddressByPhysicalAddress((((WORD)pstCecRxInfo->pucReceivedDb[1] << 8) | pstCecRxInfo->pucReceivedDb[2]), ((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4));

                    // Request OSD Name and clear retry for physical address
                    {
                        ucDxPortIndex = UserCommonCecHalGetDxPortByDeviceLogicalAddress((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4);

                        UserCommonCecHalClrOsdNameByDxPort(ucDxPortIndex);

                        if(UserCommonCecHalGetPollingLogicalAddressStart() == _TRUE)
                        {
                            // stop polling PA & continue LA polling
                            UserCommonCecHalStopPollingPhysicalAddress();

                            DebugMessageCEC("[CEC][RX] Continue polling LA", 0);
                        }
                    }
#endif

                    break;

                case _CEC_OPCODE_GIVE_PHYSICAL_ADDRESS:

                    DebugMessageCEC("[CEC][RX] GIVE_PHYSICAL_ADDRESS", pstCecRxInfo->pucReceivedDb[0]);
                    DebugMessageCEC("[CEC][RX] LA", pstCecRxInfo->ucReceivedHb);

                    if((pstCecRxInfo->ucReceivedHb & 0x0F) != _CEC_LA_BORADCAST)
                    {
                        // Reset cec tx struct
                        CLR_CEC_TX_DATA();

                        // Receive <Give Physical Address>, respond <Report Physical Address>
                        SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | _CEC_LA_BORADCAST));
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_REPORT_PHYSICAL_ADDRESS);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_1, _CEC_LA_TV);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_2, 0x00);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_3, 0x00);

                        SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 4);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 2);
                        SET_CEC_TX_SEND();
                    }

                    break;

                case _CEC_OPCODE_GET_CEC_VERSION:

                    DebugMessageCEC("[CEC][RX] GET_CEC_VERSION", pstCecRxInfo->pucReceivedDb[0]);
                    DebugMessageCEC("[CEC][RX] LA", pstCecRxInfo->ucReceivedHb);

                    if((pstCecRxInfo->ucReceivedHb & 0x0F) == _CEC_LA_TV)
                    {
                        // Reset cec tx struct
                        CLR_CEC_TX_DATA();

                        // Receive <Get CEC Version>, respond <CEC Version>
                        SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | ((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4)));
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_CEC_VERSION);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_1, 0x06); // Version 2.0

                        SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 2);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                        SET_CEC_TX_SEND();
                    }

                    break;

                case _CEC_OPCODE_GIVE_FEATURE:

                    DebugMessageCEC("[CEC][RX] GIVE_FEATURE", pstCecRxInfo->pucReceivedDb[0]);
                    DebugMessageCEC("[CEC][RX] LA", pstCecRxInfo->ucReceivedHb);

                    if((pstCecRxInfo->ucReceivedHb & 0x0F) == _CEC_LA_TV)
                    {
                        // Reset cec tx struct
                        CLR_CEC_TX_DATA();

                        // Receive <Give Feature>, respond <Report Feature>
                        SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | ((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4)));
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_REPORT_FEATURE);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_1, 0x06); // CEC Version: 2.0
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_2, 0x80); // All Device Type: TV
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_3, 0x00); // RC profile: 0
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_4, 0x06); // Device Feature: 0

                        SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 5);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                        SET_CEC_TX_SEND();
                    }

                    break;

#if(_AUDIO_ARC_SUPPORT == _ON)
                case _CEC_OPCODE_INITIAL_ARC:

                    DebugMessageCEC("[CEC][RX] INITIAL_ARC", pstCecRxInfo->pucReceivedDb[0]);
                    DebugMessageCEC("[CEC][RX] LA", pstCecRxInfo->ucReceivedHb);

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
                    if(((pstCecRxInfo->ucReceivedHb & 0x0F) == _CEC_LA_TV) &&
                       (((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4) == _CEC_LA_AUDIO_SYSTEM) &&
                       (UserCommonCecHalGetLogicalAddressByDxPort(UserCommonArcTxGetArcOutputPort()) == _CEC_LA_AUDIO_SYSTEM))
                    {
#if(_AUDIO_EARC_SUPPORT == _ON)
                        if(UserCommonArcTxGetLinkMode() == _EARC_MODE)
                        {
                            // Reset cec tx struct
                            CLR_CEC_TX_DATA();

                            // Not in correct mode to respond, respond <Feater Abort> (HF4-2-3)
                            SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | ((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4)));
                            SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_FEATURE_ABORT);
                            SET_CEC_TX_DATA(_CEC_TX_DATA_DB_1, pstCecRxInfo->pucReceivedDb[0]);
                            SET_CEC_TX_DATA(_CEC_TX_DATA_DB_2, 0x01); // Not in correct mode to respond

                            SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 2);
                            SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                            SET_CEC_TX_SEND();
                        }
                        else
#endif
                        {
                            if(UserCommonArcTxGetLinkMode() == _ARC_MODE)
                            {
                                // Reset cec tx struct
                                CLR_CEC_TX_DATA();

                                // Packing <Report Acr Initial>
                                SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | _CEC_LA_AUDIO_SYSTEM));
                                SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_REPORT_ARC_INITIATED);

                                SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 1);
                                SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                                SET_CEC_TX_SEND();
                            }
                            else
                            {
                                UserCommonCecSetArcInitiateReceivedEvent();

                                if(UserCommonCecHalGetTxMessageSendQueue() == _CEC_OPCODE_REQUEST_ARC_INITIATION)
                                {
                                    UserCommonCecHalPopTxMessageSendQueue();
                                }
                            }
                        }
                    }
#endif

                    break;

                case _CEC_OPCODE_TERMINATE_ARC:

                    DebugMessageCEC("[CEC][RX] TERMINATE_ARC", pstCecRxInfo->pucReceivedDb[0]);
                    DebugMessageCEC("[CEC][RX] LA", pstCecRxInfo->ucReceivedHb);

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
                    if(((pstCecRxInfo->ucReceivedHb & 0x0F) == _CEC_LA_TV) &&
                       (((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4) == _CEC_LA_AUDIO_SYSTEM) &&
                       (UserCommonCecHalGetLogicalAddressByDxPort(UserCommonArcTxGetArcOutputPort()) == _CEC_LA_AUDIO_SYSTEM))
                    {
#if(_AUDIO_EARC_SUPPORT == _ON)
                        if(UserCommonArcTxGetLinkMode() == _EARC_MODE)
                        {
                            // Reset cec tx struct
                            CLR_CEC_TX_DATA();

                            // Not in correct mode to respond, respond <Feater Abort> (HF4-2-3)
                            SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | ((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4)));
                            SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_FEATURE_ABORT);
                            SET_CEC_TX_DATA(_CEC_TX_DATA_DB_1, pstCecRxInfo->pucReceivedDb[0]);
                            SET_CEC_TX_DATA(_CEC_TX_DATA_DB_2, 0x01);

                            SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 2);
                            SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                            SET_CEC_TX_SEND();
                        }
                        else
#endif
                        {
                            if(UserCommonArcTxGetLinkMode() == _ARC_MODE)
                            {
                                UserCommonCecSetArcTerminateReceivedEvent();

                                if(UserCommonCecHalGetTxMessageSendQueue() == _CEC_OPCODE_REQUEST_ARC_TERMINATION)
                                {
                                    UserCommonCecHalPopTxMessageSendQueue();
                                }
                            }
                            else
                            {
                                // Reset cec tx struct
                                CLR_CEC_TX_DATA();

                                // Packing <Report Acr Terminate>
                                SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | _CEC_LA_AUDIO_SYSTEM));
                                SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_REPORT_ARC_TERMINATED);

                                SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 1);
                                SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                                SET_CEC_TX_SEND();
                            }
                        }
                    }
#endif

                    break;

                case _CEC_OPCODE_REPORT_SHORT_AUDIO_DESCRIPTOR:

                    DebugMessageCEC("[CEC][RX] REPORT_SHORT_AUDIO_DESCRIPTOR", pstCecRxInfo->pucReceivedDb[0]);
                    DebugMessageCEC("[CEC][RX] LA", pstCecRxInfo->ucReceivedHb);

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
                    if(((pstCecRxInfo->ucReceivedHb & 0x0F) == _CEC_LA_TV) &&
                       (((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4) == _CEC_LA_AUDIO_SYSTEM) &&
                       (UserCommonCecHalGetLogicalAddressByDxPort(UserCommonArcTxGetArcOutputPort()) == _CEC_LA_AUDIO_SYSTEM))
                    {
                        UserCommonCecHalReceiveAudioDescriptorProc(pstCecRxInfo);
                    }
#endif

                    break;
#endif

                case _CEC_OPCODE_FEATURE_ABORT:

                    DebugMessageCEC("[CEC][RX] FEATURE_ABORT", pstCecRxInfo->pucReceivedDb[0]);
                    DebugMessageCEC("[CEC][RX] LA", pstCecRxInfo->ucReceivedHb);

#if((_AUDIO_ARC_SUPPORT == _ON) && (_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON))
                    if(((pstCecRxInfo->ucReceivedHb & 0x0F) == _CEC_LA_TV) &&
                       (((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4) == _CEC_LA_AUDIO_SYSTEM) &&
                       (UserCommonCecHalGetLogicalAddressByDxPort(UserCommonArcTxGetArcOutputPort()) == _CEC_LA_AUDIO_SYSTEM))
                    {
                        UserCommonCecHalReceiveAudioDescriptorProc(pstCecRxInfo);
                    }
#endif

                    break;

                default:

                    DebugMessageCEC("[CEC][RX] unsupported opcode:", pstCecRxInfo->pucReceivedDb[0]);

                    if((pstCecRxInfo->ucReceivedHb & 0x0F) != _CEC_LA_BORADCAST)
                    {
                        // Reset cec tx struct
                        CLR_CEC_TX_DATA();

                        // Unknown Message, respond <Feater Abort> (HF4-2-3)
                        SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | ((pstCecRxInfo->ucReceivedHb & 0xF0) >> 4)));
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_FEATURE_ABORT);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_1, pstCecRxInfo->pucReceivedDb[0]);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_2, 0x00);

                        SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 2);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                        SET_CEC_TX_SEND();
                    }

                    break;
            }
        }
        else
        {
            DebugMessageCEC("[CEC][RX] cmd length error, opcode:", pstCecRxInfo->pucReceivedDb[0]);
            DebugMessageCEC("[CEC][RX] cmd length error, length:", pstCecRxInfo->ucDbLength);
        }
    }
}

//--------------------------------------------------
// Description  : Prepare data need to send out
// Input Value  : pstCecTxInfo
// Output Value : EnumCecTxTransmitTask
//--------------------------------------------------
EnumCecTxTransmitTask UserInterfaceCecTransmitInfoPrepare(StructCecTxTransmitInfo *pstCecTxInfo)
{
    // check user event if there is no Rx reply message
    if(GET_CEC_TX_SEND() == _FALSE)
    {
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
        EnumCECOpCode enumCecOpcode = _CEC_OPCODE_NONE;
        BYTE ucLogicalAddress = 0;

        // Polling LA & Request PA
        if(UserCommonCecHalGetPollingLogicalAddressStart() == _TRUE)
        {
            if(UserCommonCecHalPollingLogicalAddressHandler(&enumCecOpcode, &ucLogicalAddress) == _CEC_TX_TASK)
            {
                DebugMessageCEC("[CEC][TX]  Polling LA & Request PA", 0);

                // Reset cec tx struct
                CLR_CEC_TX_DATA();

                SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | ucLogicalAddress));

                if(enumCecOpcode == _CEC_OPCODE_POLLING_MESSAGE)
                {
                    // Packing <Polling Message>
                    SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 0);
                    SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 2);

                    DebugMessageCEC("[CEC][TX] POLLING_MESSAGE", enumCecOpcode);
                }
                else if(enumCecOpcode == _CEC_OPCODE_GIVE_PHYSICAL_ADDRESS)
                {
                    // Packing <Give Physical Address>
                    SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_GIVE_PHYSICAL_ADDRESS);

                    SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 1);
                    SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);

                    DebugMessageCEC("[CEC][TX] GIVE_PHYSICAL_ADDRESS", enumCecOpcode);
                }

                SET_CEC_TX_SEND();
            }
        }
        else if(UserCommonCecHalGetTxMessageSendQueueDepth() > 0)
        {
            enumCecOpcode = UserCommonCecHalGetTxMessageSendQueue();

            switch(enumCecOpcode)
            {
#if(_AUDIO_ARC_SUPPORT == _ON)
                case _CEC_OPCODE_REQUEST_ARC_INITIATION:

                    DebugMessageCEC("[CEC][TX] REQUEST_ARC_INITIATION", enumCecOpcode);

                    if((UserCommonArcTxGetLinkMode() != _ARC_MODE) && (UserCommonCecGetArcInitiateReceivedEvent() == _FALSE))
                    {
                        // Reset cec tx struct
                        CLR_CEC_TX_DATA();

                        // Packing <Request Acr Initial>
                        SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | _CEC_LA_AUDIO_SYSTEM));
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_REQUEST_ARC_INITIATION);

                        SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 1);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                        SET_CEC_TX_SEND();

                        SysAudioArcTxCecActiveRequestArcInitiateRetryTimer();
                    }

                    break;

                case _CEC_OPCODE_REPORT_ARC_INITIATED:

                    DebugMessageCEC("[CEC][TX] REPORT_ARC_INITIATED:", enumCecOpcode);

                    // Reset cec tx struct
                    CLR_CEC_TX_DATA();

                    // Packing <Report Acr Initial>
                    SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | _CEC_LA_AUDIO_SYSTEM));
                    SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_REPORT_ARC_INITIATED);

                    SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 1);
                    SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                    SET_CEC_TX_SEND();

                    break;

                case _CEC_OPCODE_REQUEST_ARC_TERMINATION:

                    DebugMessageCEC("[CEC][TX] REQUEST_ARC_TERMINATION", enumCecOpcode);

                    if(UserCommonCecGetArcTerminateReceivedEvent() == _FALSE)
                    {
                        // Reset cec tx struct
                        CLR_CEC_TX_DATA();

                        // Packing <Request Arc Termination>
                        SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | _CEC_LA_AUDIO_SYSTEM));
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_REQUEST_ARC_TERMINATION);

                        SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 1);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 2);
                        SET_CEC_TX_SEND();

                        SysAudioArcTxCecActiveRequestArcTerminateRetryTimer();
                    }

                    break;

                case _CEC_OPCODE_REPORT_ARC_TERMINATED:

                    DebugMessageCEC("[CEC][TX] REPORT_ARC_TERMINATED:", enumCecOpcode);

                    // Reset cec tx struct
                    CLR_CEC_TX_DATA();

                    // Packing <Report Acr Termination>
                    SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | _CEC_LA_AUDIO_SYSTEM));
                    SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_REPORT_ARC_TERMINATED);

                    SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 1);
                    SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                    SET_CEC_TX_SEND();

                    break;

                case _CEC_OPCODE_REQUEST_SHORT_AUDIO_DESCRIPTOR:

                    DebugMessageCEC("[CEC][TX] REQUEST_SHORT_AUDIO_DESCRIPTOR:", enumCecOpcode);

                    // Reset cec tx struct
                    CLR_CEC_TX_DATA();

                    // Packing <Request Short Audio Descriptor>
                    SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | _CEC_LA_AUDIO_SYSTEM));
                    SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_REQUEST_SHORT_AUDIO_DESCRIPTOR);
                    SET_CEC_TX_DATA(_CEC_TX_DATA_DB_1, (UserCommonCecHalGetPollingAudioDescriptorCount() * 4) + 1);
                    SET_CEC_TX_DATA(_CEC_TX_DATA_DB_2, (UserCommonCecHalGetPollingAudioDescriptorCount() * 4) + 2);

                    if(UserCommonCecHalGetPollingAudioDescriptorCount() < 3)
                    {
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_3, (UserCommonCecHalGetPollingAudioDescriptorCount() * 4) + 3);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_DB_4, (UserCommonCecHalGetPollingAudioDescriptorCount() * 4) + 4);
                        SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 5);
                    }
                    else
                    {
                        SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 3);
                    }

                    SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                    SET_CEC_TX_SEND();

                    UserCommonCecHalActiveWaitForAudioDescriptorReplyTimer();
                    break;
#endif

                default:
                    DebugMessageCEC("[CEC][TX] Request unsupported opcode", enumCecOpcode);
                    break;
            }

            // remove & shift queue buffer
            UserCommonCecHalPopTxMessageSendQueue();
        }
        else if(UserCommonCecHalCheckPollingLogicalAddressFinish() == _TRUE)
        {
            if(UserCommonCecHalRequestDeviceOsdNameHandler(&ucLogicalAddress) == _CEC_TX_TASK)
            {
                // Reset cec tx struct
                CLR_CEC_TX_DATA();

                // Packing <GIVE_OSD_NAME>
                SET_CEC_TX_DATA(_CEC_TX_DATA_HB, ((_CEC_LA_TV << 4) | ucLogicalAddress));
                SET_CEC_TX_DATA(_CEC_TX_DATA_DB_0, _CEC_OPCODE_GIVE_OSD_NAME);

                SET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH, 1);
                SET_CEC_TX_DATA(_CEC_TX_DATA_RETRY, 3);
                SET_CEC_TX_SEND();
            }
        }
#endif // End of #if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
    }

    if(GET_CEC_TX_SEND() == _TRUE)
    {
        CLR_CEC_TX_SEND();

        DebugMessageCEC("[CEC][TX] Send Out Header", GET_CEC_TX_DATA(_CEC_TX_DATA_HB));
        DebugMessageCEC("[CEC][TX] Send Out Opcode", GET_CEC_TX_DATA(_CEC_TX_DATA_DB_0));

        pstCecTxInfo->ucTransmitHb = GET_CEC_TX_DATA(_CEC_TX_DATA_HB);
        pstCecTxInfo->pucTransmitDb[0] = GET_CEC_TX_DATA(_CEC_TX_DATA_DB_0);
        pstCecTxInfo->pucTransmitDb[1] = GET_CEC_TX_DATA(_CEC_TX_DATA_DB_1);
        pstCecTxInfo->pucTransmitDb[2] = GET_CEC_TX_DATA(_CEC_TX_DATA_DB_2);
        pstCecTxInfo->pucTransmitDb[3] = GET_CEC_TX_DATA(_CEC_TX_DATA_DB_3);
        pstCecTxInfo->pucTransmitDb[4] = GET_CEC_TX_DATA(_CEC_TX_DATA_DB_4);
        pstCecTxInfo->ucDbLength = GET_CEC_TX_DATA(_CEC_TX_DATA_LENGTH);
        pstCecTxInfo->b3RetryCnt = GET_CEC_TX_DATA(_CEC_TX_DATA_RETRY);

        return _CEC_TX_TASK;
    }

    return _NO_CEC_TX_TASK;
}

//--------------------------------------------------
// Description  : User CEC High Level Flow Process
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserInterfaceCecHighLevelFlow(void)
{
    // --------------------------------------------
    // Part 1: Action & Reply CEC Message
    // reply msg has already done in UserCommonCecRxReceived
    // --------------------------------------------

    // --------------------------------------------
    // Part 2: Check Tx Send Task is done?
    // --------------------------------------------

    // kernel has already checked Tx idle state before UserCommonCecTransmitInfoPrepare

    // --------------------------------------------
    // Part 3: Active CEC TX Send task by user behavior
    // Trigger by end user behavior or Topology build by scan LA
    // --------------------------------------------

    // Build Topology
#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
    UserCommonCecHalTopologyHandler();
#endif
}

//--------------------------------------------------
// Description  : User CEC Request Device to Send CEC Message
// Input Value  : enumOpCode
// Output Value : None
//--------------------------------------------------
void UserInterfaceCecRequestSendCecMessage(EnumCECOpCode enumOpCode)
{
    enumOpCode = enumOpCode;

    // Implement by User.
}

#if(_AUDIO_ARC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User CEC Get OSD CEC Enable Status
// Input Value  : None
// Output Value : _CEC_OSD_ENABLE/_CEC_OSD_DISABLE
//--------------------------------------------------
EnumCecOsdEnable UserInterfaceCecGetOsdCecEnable(void)
{
    // Implement by User
    return _CEC_OSD_ENABLE;
}
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)
#endif // End of #if(_HDMI_CEC_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)