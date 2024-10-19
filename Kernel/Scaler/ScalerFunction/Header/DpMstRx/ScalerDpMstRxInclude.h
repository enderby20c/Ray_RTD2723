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
// ID Code      : ScalerDpMstRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Port Info
//--------------------------------------------------
#define _DP_MST_RX_OUTPUT_PORT                                                                  0
#define _DP_MST_RX_INPUT_PORT                                                                   1

#define _DP_MST_RX_LOGICAL_PORT_NUM                                                             ((_DP_MST_PXP_MODE_SUPPORT == _TRUE) ? 2 : 1)

#if(_DP_TX_SUPPORT == _ON)
#define _DP_MST_RX_NUM_OF_OUTPUT_PORTS                                                          1
#else
#define _DP_MST_RX_NUM_OF_OUTPUT_PORTS                                                          0
#endif

#define _DP_MST_RX_NUM_OF_PORTS                                                                 (_DP_MST_RX_LOGICAL_PORT_NUM + _DP_MST_RX_NUM_OF_OUTPUT_PORTS + 1)

#define GET_DP_MST_RX_MAIN_PORT_MAC_USED()                                                      (ScalerDpRxGetMacSwitch(GET_DP_RX_MAIN_PORT()))

//--------------------------------------------------
// Definitions of Reply Type
//--------------------------------------------------
#define _DP_MST_RX_MSG_ACK                                                                      0
#define _DP_MST_RX_MSG_NACK                                                                     1

//--------------------------------------------------
// Definitions of Secondary Data Info
//--------------------------------------------------
#define _DP_MST_RX_NUM_OF_SDP_STREAMS                                                           1
#define _DP_MST_RX_NUM_OF_SDP_SINKS                                                             1

//--------------------------------------------------
// Definitions of MSG Byte-Wise Access
//--------------------------------------------------
#define _DP_MST_RX_REQUEST_MSG_BYTE_WISE_MAX_LEN                                                24
#define _DP_MST_RX_REPLY_MSG_BYTE_WISE_MAX_LEN                                                  132

#define _DP_MST_RX_TOTAL_TIME_SLOT_NUM                                                          64

//--------------------------------------------------
// Definitions of Buffer Priority Info
//--------------------------------------------------
#define _DP_MST_RX_DOWN_REQUEST_BUF0                                                            0
#define _DP_MST_RX_DOWN_REQUEST_BUF1                                                            1
#define _DP_MST_RX_UP_REPLY_BUF0                                                                0
#define _DP_MST_RX_UP_REPLY_BUF1                                                                1

//--------------------------------------------------
// Definitions of Buffer Priority Info
//--------------------------------------------------
#define _DP_MST_RX_PBN_MARGIN_PERCENTAGE_FOR_ALLOCATE_PAYLOAD                                   1


//--------------------------------------------------
// DP Enum_Path_Resource Rx/Tx PBN Compare Option
//--------------------------------------------------
#ifndef _DP_MST_ENUM_PATH_RESOURCE_REPLY_IGNORE_RX_BW
#define _DP_MST_ENUM_PATH_RESOURCE_REPLY_IGNORE_RX_BW                                           _ON
#endif

//--------------------------------------------------
// DP Down Reply Mannual Mode
//--------------------------------------------------
#define _DP_MST_RX_DOWN_REPLY_MANUAL_MODE_SUPPORT                                               _ON
#define _DP_MST_RX_DOWN_REPLY_MANUAL_MODE_MAX_LEN                                               32


#define GET_DP_MST_RX_HOT_PLUG_STATUS()                                                         (ScalerDpRxGetHotPlugStatus(GET_DP_RX_BASE_PORT()))

//--------------------------------------------------
// Definitions of MST Get DPCD Macro
//--------------------------------------------------
#define GET_DP_MST_RX_REG_DPCD_INFO(x, y, z)                                                    (ScalerDpAuxRxGetDpcdInfo(GET_DP_RX_BASE_PORT(), (x), (y), (z)))
#define SET_DP_MST_RX_REG_DPCD_INFO(x, y, z, w)                                                 (ScalerDpAuxRxSetDpcdValue(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w)))
#define SET_DP_MST_RX_REG_WR_DPCD_INFO(x, y, z, w)                                              (ScalerDpAuxRxSetDpcdWriteValue(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w)))
#define SET_DP_MST_RX_REG_W1C_DPCD_INFO(x, y, z, w)                                             (ScalerDpAuxRxSetDpcdWrite1ClearValue(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w)))
#define SET_DP_MST_RX_REG_W1C_DPCD_MIRROR_BIT(x, y, z, v, w)                                    (ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue(GET_DP_RX_BASE_PORT(), (x), (y), (z), (v), (w)))

#define GET_DP_MST_RX_REG_DPCD_INFO_EXINT0(x, y, z)                                             (ScalerDpAuxRxGetDpcdInfo_EXINT0(GET_DP_RX_BASE_PORT(), (x), (y), (z)))
#define SET_DP_MST_RX_REG_DPCD_INFO_EXINT0(x, y, z, w)                                          (ScalerDpAuxRxSetDpcdValue_EXINT0(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w)))
#define SET_DP_MST_RX_REG_WR_DPCD_INFO_EXINT0(x, y, z, w)                                       (ScalerDpAuxRxSetDpcdWriteValue_EXINT0(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w)))
#define SET_DP_MST_RX_REG_W1C_DPCD_INFO_EXINT0(x, y, z, w)                                      (ScalerDpAuxRxSetDpcdWrite1ClearValue_EXINT0(GET_DP_RX_BASE_PORT(), (x), (y), (z), (w)))
#define SET_DP_MST_RX_REG_W1C_DPCD_MIRROR_BIT_EXINT0(x, y, z, v, w)                             (ScalerDpAuxRxSetDpcdMirrorBitWrite1ClearValue_EXINT0(GET_DP_RX_BASE_PORT(), (x), (y), (z), (v), (w)))

#define SET_DP_MST_RX_HPD_IRQ()                                                                 (ScalerDpAuxRxHpdIrqAssert(GET_DP_RX_BASE_PORT()))
#define GET_DP_MST_RX_CHECK_AUX_CH_POWER_STATUS()                                               (ScalerDpAuxRxGetAuxChPowerStatus(GET_DP_RX_BASE_PORT()))
#define GET_DP_MST_RX_SOURCE_FIRST_POWER_ON()                                                   (ScalerDpAuxRxGetSourceFirstPowerOn(GET_DP_RX_BASE_PORT()))
#define GET_DP_RX_MST_SOURCE_WRITE_POWER_UP()                                                   (ScalerDpAuxRxGetSourceWritePowerUp(GET_DP_RX_BASE_PORT()))

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of Rx HDCP Macro
//--------------------------------------------------
#define GET_DP_MST_RX_HDCP_AUTH_ENCRYPTION()                                                    (ScalerDpMacDphyRxHdcpCheckValid(GET_DP_RX_MAIN_PORT()))
#define GET_DP_MST_RX_HDCP_AUTH_PROC_DONE()                                                     (ScalerSyncDpHdcpGetAuthState() == _DP_RX_HDCP_STATE_AUTH_DONE)
#define GET_DP_MST_RX_HDCP_REPEATER_SUPPORTED()                                                 (ScalerDpAuxRxGetDpcdInfo(GET_DP_RX_MAIN_PORT(), 0x06, 0x80, 0x28) == (_BIT1 | _BIT0))
#define GET_DP_MST_RX_HDCP_POWER_STATUS_NORMAL()                                                ((ScalerDpAuxRxGetDpcdInfo(GET_DP_RX_MAIN_PORT(), 0x00, 0x06, 0x00) & 0x07) == _BIT0)
#define SET_DP_MST_RX_HDCP_SHA_INPUT_RUN(x)                                                     (ScalerDpMacDphyRxHDCPAuthShaRun(GET_DP_RX_MAIN_PORT(), (x)))

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#define GET_DP_MST_RX_HDCP2_MODE()                                                              (ScalerDpHdcpRxGetHdcpMode(GET_DP_RX_MAIN_PORT()))

#define GET_DP_MST_RX_HDCP2_AUTH_PROC_DONE()                                                    (ScalerSyncDpHdcp2GetAuthState() == _DP_RX_HDCP2_REPEATER_STATE_AUTH_DONE)
#define GET_DP_MST_RX_HDCP2_REPEATER_SUPPORTED()                                                (ScalerDpAuxRxGetDpcdInfo(GET_DP_RX_MAIN_PORT(), 0x06, 0x92, 0x1F) == (_BIT1 | _BIT0))
#define SET_DP_MST_RX_HDCP2_LPRIME_CAL(x)                                                       (ScalerDpHdcp2RepeaterLPrimeCalculate(GET_DP_RX_MAIN_PORT(), (x)))
#define GET_DP_MST_RX_HDCP2_V(x)                                                                (ScalerDpHdcp2GetVPrime(GET_DP_RX_MAIN_PORT(), (x)))
#endif
#endif

#define SET_DP_MST_RX_REG_AUX_TO_MANUAL_MODE_EXINT()                                            (ScalerDpAuxRxSetManualMode_EXINT0(GET_DP_RX_BASE_PORT()))

#define SET_DP_MST_RX_REG_AUX_TO_MANUAL_MODE()                                                  (ScalerDpAuxRxSetManualMode(GET_DP_RX_BASE_PORT()))

#define SET_DP_MST_RX_REG_AUX_TO_AUTO_MODE_EXINT()                                              (ScalerDpAuxRxSetAutoMode_EXINT0(GET_DP_RX_BASE_PORT()))

#define SET_DP_MST_RX_REG_AUX_TO_AUTO_MODE()                                                    (ScalerDpAuxRxSetAutoMode(GET_DP_RX_BASE_PORT()))

#define GET_DP_MST_RX_VBIOS_BACKUP_INFO()                                                       (ScalerDpMacDphyRxGetMstInfoBackup(GET_DP_RX_BASE_PORT()))
#define CLR_DP_MST_RX_VBIOS_BACKUP_INFO()                                                       {ScalerDpMacDphyRxClearMstInfoBackup(GET_DP_RX_BASE_PORT());}

#if(_DP_TX_SUPPORT == _ON)
#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
#define GET_DP_MST_RX_REG_HDCP_M0_0()                                                           (ScalerDpMacDphyRxHdcp14GetM0(GET_DP_RX_MAIN_PORT(), 0))
#define GET_DP_MST_RX_REG_HDCP_M0_1()                                                           (ScalerDpMacDphyRxHdcp14GetM0(GET_DP_RX_MAIN_PORT(), 1))
#define GET_DP_MST_RX_REG_HDCP_M0_2()                                                           (ScalerDpMacDphyRxHdcp14GetM0(GET_DP_RX_MAIN_PORT(), 2))
#define GET_DP_MST_RX_REG_HDCP_M0_3()                                                           (ScalerDpMacDphyRxHdcp14GetM0(GET_DP_RX_MAIN_PORT(), 3))
#define GET_DP_MST_RX_REG_HDCP_M0_4()                                                           (ScalerDpMacDphyRxHdcp14GetM0(GET_DP_RX_MAIN_PORT(), 4))
#define GET_DP_MST_RX_REG_HDCP_M0_5()                                                           (ScalerDpMacDphyRxHdcp14GetM0(GET_DP_RX_MAIN_PORT(), 5))
#define GET_DP_MST_RX_REG_HDCP_M0_6()                                                           (ScalerDpMacDphyRxHdcp14GetM0(GET_DP_RX_MAIN_PORT(), 6))
#define GET_DP_MST_RX_REG_HDCP_M0_7()                                                           (ScalerDpMacDphyRxHdcp14GetM0(GET_DP_RX_MAIN_PORT(), 7))
#endif

#define GET_DP_MST_RX_HDCP_AN(x)                                                                (ScalerDpAuxRxGetDpcdInfo(GET_DP_RX_MAIN_PORT(), 0x06, 0x80, (0x0C + (x))))
#define GET_DP_MST_RX_HDCP_V(x)                                                                 (ScalerDpAuxRxGetDpcdInfo(GET_DP_RX_MAIN_PORT(), 0x06, 0x80, (0x14 + (x))))
#endif

//--------------------------------------------------
// HDCP SHA Related Register Macro
//--------------------------------------------------
#if(_DP_TX_SUPPORT == _ON)
#define GET_DP_MST_RX_REG_HDCP_SHA_RESULT(x)                                                    (ScalerGetByte(ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_MAIN_PORT(), PB_36_SHA_0) + (x)))
#define GET_DP_MST_RX_REG_HDCP_SHA256_RESULT(x)                                                 (ScalerGetByte(P63_35_HDCP_SHA_0 + (x)))

#define SET_DP_MST_RX_REG_SHA_INPUT_0(x)                                                        {ScalerSetByte(ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_MAIN_PORT(), PB_31_SHA_DATA1), (x));}
#define SET_DP_MST_RX_REG_SHA_INPUT_1(x)                                                        {ScalerSetByte(ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_MAIN_PORT(), PB_32_SHA_DATA2), (x));}
#define SET_DP_MST_RX_REG_SHA_INPUT_2(x)                                                        {ScalerSetByte(ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_MAIN_PORT(), PB_33_SHA_DATA3), (x));}
#define SET_DP_MST_RX_REG_SHA_INPUT_3(x)                                                        {ScalerSetByte(ScalerDpMacDphyRxGetPagedAddress(GET_DP_RX_MAIN_PORT(), PB_34_SHA_DATA4), (x));}
#endif

//--------------------------------------------------
// Definitions of MST Mode Status Macro
//--------------------------------------------------
#define GET_DP_MST_RX_MODE_STATE()                                                              (g_penumDpMstRxModeStatus[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS])
#define SET_DP_MST_RX_MODE_STATE(x)                                                             (g_penumDpMstRxModeStatus[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS] = (x))

//--------------------------------------------------
// Definitions of Down Request CRC Macro
//--------------------------------------------------
#define GET_DP_MST_RX_REG_DOWN_REQUEST_HEADER_CRC_BACKUP()                                      (g_stDpMstRxReqGetMsgCRC.b4HeaderCRC)
#define SET_DP_MST_RX_REG_DOWN_REQUEST_HEADER_CRC_BACKUP(x)                                     (g_stDpMstRxReqGetMsgCRC.b4HeaderCRC = (x))
#define GET_DP_MST_RX_REG_DOWN_REQUEST_BODY_CRC_BACKUP()                                        (g_stDpMstRxReqGetMsgCRC.ucBodyCRC)
#define SET_DP_MST_RX_REG_DOWN_REQUEST_BODY_CRC_BACKUP(x)                                       (g_stDpMstRxReqGetMsgCRC.ucBodyCRC = (x))

//--------------------------------------------------
// Definitions of Request Memory Pool Macro
//--------------------------------------------------
#define GET_DP_MST_RX_MSG_REQUEST_ARRAY(x)                                                      (g_unDpMstRxRequestPool.pucData[x])
#define SET_DP_MST_RX_MSG_REQUEST_ARRAY(x, y)                                                   (g_unDpMstRxRequestPool.pucData[x] = (y))

//--------------------------------------------------
// Definitions of Reply Memory Pool Macro
//--------------------------------------------------
#define GET_DP_MST_RX_MSG_REPLY_ARRAY(x)                                                        (g_unDpMstRxReplyPool.pucData[x])
#define SET_DP_MST_RX_MSG_REPLY_ARRAY(x, y)                                                     (g_unDpMstRxReplyPool.pucData[x] = (y))

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of Total Receipt Msg Count Macro
//--------------------------------------------------
#define GET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT()                                                (g_ucDpMstRxTotalReceivedMsgCount)
#define SET_DP_MST_RX_TOTAL_RECEIVED_MSG_COUNT(x)                                               (g_ucDpMstRxTotalReceivedMsgCount = (x))
#endif

//--------------------------------------------------
// Definitions of Down Request Allocate Payload MSG Macro
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()                            (g_unDpMstRxRequestPool.stAllocatePayload.b7PayloadID)
#define GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN()                                   (\
                                                                                                    TO_WORD(\
                                                                                                        g_unDpMstRxRequestPool.stAllocatePayload.pucPBN[0],\
                                                                                                        g_unDpMstRxRequestPool.stAllocatePayload.pucPBN[1])\
                                                                                                )
#define GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM()                              (g_unDpMstRxRequestPool.stAllocatePayload.b4PortNum)
#define GET_DP_MST_RX_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_SDP_NUM()                               (g_unDpMstRxRequestPool.stAllocatePayload.b4NumOfSDPStreams)

//--------------------------------------------------
// Definitions of Down Reply Allocate Payload MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REPLY_TYPE(x)                             (g_unDpMstRxReplyPool.stAllocatePayload.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REQUEST_ID(x)                             (g_unDpMstRxReplyPool.stAllocatePayload.b7ReqID = (x))
#define SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PORT_NUM(x)                               (g_unDpMstRxReplyPool.stAllocatePayload.b4PortNum = (x))
#define SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(x)                             (g_unDpMstRxReplyPool.stAllocatePayload.b7PayloadID = (x))
#define GET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()                              (g_unDpMstRxReplyPool.stAllocatePayload.b7PayloadID)
#define SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(x)                                    {\
                                                                                                    WORD usLocalValue = (WORD)(x);\
                                                                                                    g_unDpMstRxReplyPool.stAllocatePayload.pucAllocatePBN[0] = HIBYTE(usLocalValue);\
                                                                                                    g_unDpMstRxReplyPool.stAllocatePayload.pucAllocatePBN[1] = LOBYTE(usLocalValue);\
                                                                                                }
#define GET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN()                                     (\
                                                                                                    TO_WORD(\
                                                                                                        g_unDpMstRxReplyPool.stAllocatePayload.pucAllocatePBN[0],\
                                                                                                        g_unDpMstRxReplyPool.stAllocatePayload.pucAllocatePBN[1])\
                                                                                                )
#define SET_DP_MST_RX_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_ZEROS()                                   {\
                                                                                                    g_unDpMstRxReplyPool.stAllocatePayload.b1Zero1 = 0;\
                                                                                                    g_unDpMstRxReplyPool.stAllocatePayload.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Query Payload MSG Macro
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM()                                 (g_unDpMstRxRequestPool.stQueryPayload.b4PortNum)
#define GET_DP_MST_RX_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PAYLOAD_ID()                               (g_unDpMstRxRequestPool.stQueryPayload.b7PayloadID)

//--------------------------------------------------
// Definitions of Down Reply Query Payload MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_REPLY_TYPE(x)                                (g_unDpMstRxReplyPool.stQueryPayload.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_REQUEST_ID(x)                                (g_unDpMstRxReplyPool.stQueryPayload.b7ReqID = (x))
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_PORT_NUM(x)                                  (g_unDpMstRxReplyPool.stQueryPayload.b4PortNum = (x))
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_ALLOCATED_PBN(x)                             {\
                                                                                                    WORD usLocalValue = (WORD)(x);\
                                                                                                    g_unDpMstRxReplyPool.stQueryPayload.pucAllocatePBN[0] = HIBYTE(usLocalValue);\
                                                                                                    g_unDpMstRxReplyPool.stQueryPayload.pucAllocatePBN[1] = LOBYTE(usLocalValue);\
                                                                                                }
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_PAYLOAD_MSG_ZEROS()                                      {\
                                                                                                    g_unDpMstRxReplyPool.stQueryPayload.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Power Up MSG Macro
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_POWER_UP_MSG_PORT_NUM()                                      (g_unDpMstRxRequestPool.stPowerUpPHY.b4PortNum)

//--------------------------------------------------
// Definitions of Down Reply Power Up MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_POWER_UP_MSG_REPLY_TYPE(x)                                     (g_unDpMstRxReplyPool.stPowerUpPHY.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_POWER_UP_MSG_REQUEST_ID(x)                                     (g_unDpMstRxReplyPool.stPowerUpPHY.b7ReqID = (x))
#define SET_DP_MST_RX_DOWN_REPLY_POWER_UP_MSG_PORT_NUM(x)                                       (g_unDpMstRxReplyPool.stPowerUpPHY.b4PortNum = (x))
#define SET_DP_MST_RX_DOWN_REPLY_POWER_UP_MSG_ZEROS()                                           {\
                                                                                                    g_unDpMstRxReplyPool.stPowerUpPHY.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Power Down MSG Macro
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_POWER_DOWN_MSG_PORT_NUM()                                    (g_unDpMstRxRequestPool.stPowerDownPHY.b4PortNum)

//--------------------------------------------------
// Definitions of Down Reply Power Down MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_POWER_DOWN_MSG_REPLY_TYPE(x)                                   (g_unDpMstRxReplyPool.stPowerDownPHY.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_POWER_DOWN_MSG_REQ_ID(x)                                       (g_unDpMstRxReplyPool.stPowerDownPHY.b7ReqID = (x))
#define SET_DP_MST_RX_DOWN_REPLY_POWER_DOWN_MSG_PORT_NUM(x)                                     (g_unDpMstRxReplyPool.stPowerDownPHY.b4PortNum = (x))
#define SET_DP_MST_RX_DOWN_REPLY_POWER_DOWN_MSG_ZEROS()                                         {\
                                                                                                    g_unDpMstRxReplyPool.stPowerDownPHY.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Remote DPCD Read MSG Macro
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_PORT_NUM()                              (g_unDpMstRxRequestPool.stRemoteDpcdRead.b4PortNum)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ()                           (g_unDpMstRxRequestPool.stRemoteDpcdRead.ucNumOfRead)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_H()                             (g_unDpMstRxRequestPool.stRemoteDpcdRead.b4DpcdAddressH)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M()                             (g_unDpMstRxRequestPool.stRemoteDpcdRead.ucDpcdAddressM)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_L()                             (g_unDpMstRxRequestPool.stRemoteDpcdRead.ucDpcdAddressL)


//--------------------------------------------------
// Definitions of Down Reply Remote DPCD Read MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_REPLY_TYPE(x)                             (g_unDpMstRxReplyPool.stRemoteDpcdRead.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_REQUEST_ID(x)                             (g_unDpMstRxReplyPool.stRemoteDpcdRead.b7ReqID = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_PORT_NUM(x)                               (g_unDpMstRxReplyPool.stRemoteDpcdRead.b4PortNum = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_NUM_OF_READ(x)                            (g_unDpMstRxReplyPool.stRemoteDpcdRead.ucNumOfRead = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(x)                                   (g_unDpMstRxReplyPool.stRemoteDpcdRead.pucDpcdRead[x])
#define SET_DP_MST_RX_DOWN_REPLY_MSG_REMOTE_DPCD_READ_MSG_ZEROS()                               {\
                                                                                                    g_unDpMstRxReplyPool.stRemoteDpcdRead.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Remote DPCD Write MSG Macro
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_PORT_NUM()                             (g_unDpMstRxRequestPool.stRemoteDpcdWrite.b4PortNum)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_H()                            (g_unDpMstRxRequestPool.stRemoteDpcdWrite.b4DpcdAddressH)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_M()                            (g_unDpMstRxRequestPool.stRemoteDpcdWrite.ucDpcdAddressM)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_L()                            (g_unDpMstRxRequestPool.stRemoteDpcdWrite.ucDpcdAddressL)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_DATA(x)                                (g_unDpMstRxRequestPool.stRemoteDpcdWrite.pucDpcdByteToWrite[x])
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_NUM_OF_WRITE()                         (g_unDpMstRxRequestPool.stRemoteDpcdWrite.ucNumOfByteToWrite)

//--------------------------------------------------
// Definitions of Down Reply Remote DPCD Write MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REPLY_TYPE(x)                            (g_unDpMstRxReplyPool.stRemoteDpcdWrite.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REQUEST_ID(x)                            (g_unDpMstRxReplyPool.stRemoteDpcdWrite.b7ReqID = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_PORT_NUM(x)                              (g_unDpMstRxReplyPool.stRemoteDpcdWrite.b4PortNum = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_DPCE_WRITE_MSG_ZEROS()                                  {\
                                                                                                    g_unDpMstRxReplyPool.stRemoteDpcdWrite.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request GET_MESSAGE_TRANSACTION_VERSION MSG Macro
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_GET_MSG_VERSION_MSG_PORT_NUM()                               (g_unDpMstRxRequestPool.stGetMsgVer.b4PortNum)

//--------------------------------------------------
// Definitions of Down Reply GET_MESSAGE_TRANSACTION_VERSION MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_GET_MSG_VERSION_MSG_REPLY_TYPE(x)                              (g_unDpMstRxReplyPool.stGetMsgVer.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_GET_MSG_VERSION_MSG_REQUEST_ID(x)                              (g_unDpMstRxReplyPool.stGetMsgVer.b7ReqID = (x))
#define SET_DP_MST_RX_DOWN_REPLY_GET_MSG_VERSION_MSG_VERSION(x)                                 (g_unDpMstRxReplyPool.stGetMsgVer.ucMsgVersion = (x))

//--------------------------------------------------
// Definitions of Down Reply Link Address MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_REPLY_TYPE(x)                                    (g_unDpMstRxReplyPool.stLinkAddress.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_REQUEST_ID(x)                                    (g_unDpMstRxReplyPool.stLinkAddress.b7ReqID = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_GUID(x, y)                                       (g_unDpMstRxReplyPool.stLinkAddress.pucGuid[x] = (y))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_PORT(x)                                   (g_unDpMstRxReplyPool.stLinkAddress.b4NumOfPort = (x))

#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_TYPE(x)                                    (g_unDpMstRxReplyPool.stLinkAddress.b1InputPort0 = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_NUM(x)                                     (g_unDpMstRxReplyPool.stLinkAddress.b4Port0Num = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_PEER_DEVICE_TYPE(x)                        (g_unDpMstRxReplyPool.stLinkAddress.b3PeerDeviceType0 = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_MSG_CAP(x)                                 (g_unDpMstRxReplyPool.stLinkAddress.b1MsgCapability0 = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_PLUG_STATUS(x)                             (g_unDpMstRxReplyPool.stLinkAddress.b1DpPlugStatus0 = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT0_ZEROS()                                    {\
                                                                                                    g_unDpMstRxReplyPool.stLinkAddress.b4Zero = 0;\
                                                                                                    g_unDpMstRxReplyPool.stLinkAddress.b6Zero1 = 0;\
                                                                                                }

#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_TYPE(index, x)                                   (g_unDpMstRxReplyPool.stLinkAddress.pstPortInfo[index].b1InputPort = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM(index, x)                                    (g_unDpMstRxReplyPool.stLinkAddress.pstPortInfo[index].b4PortNum = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PEER_DEVICE_TYPE(index, x)                       (g_unDpMstRxReplyPool.stLinkAddress.pstPortInfo[index].b3PeerDeviceType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_MSG_CAP(index, x)                                (g_unDpMstRxReplyPool.stLinkAddress.pstPortInfo[index].b1MsgCapability = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PLUG_STATUS(index, x)                            (g_unDpMstRxReplyPool.stLinkAddress.pstPortInfo[index].b1DpPlugStatus = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_LEGACY_PLUG_STATUS(index, x)                     (g_unDpMstRxReplyPool.stLinkAddress.pstPortInfo[index].b1LegacyPlugStatus = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_DPCD_REV(index, x)                               (g_unDpMstRxReplyPool.stLinkAddress.pstPortInfo[index].ucDpcdRevision = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_PORT_GUID(index, x, y)                           (g_unDpMstRxReplyPool.stLinkAddress.pstPortInfo[index].pucPeerGuid[x] = (y))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP(index, x)                             (g_unDpMstRxReplyPool.stLinkAddress.pstPortInfo[index].b4NumSDPStreams = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_SDP_SINK(index, x)                        (g_unDpMstRxReplyPool.stLinkAddress.pstPortInfo[index].b4NumSDPStreamSink = (x))
#define SET_DP_MST_RX_DOWN_REPLY_LINK_ADDR_MSG_ZEROS(index)                                     (g_unDpMstRxReplyPool.stLinkAddress.pstPortInfo[index].b5Zero = 0)

//--------------------------------------------------
// Definitions of Down Request Enum Payload MSG Macro
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_ENUM_PATH_MSG_PORT_NUM()                                     (g_unDpMstRxRequestPool.stEnumPathResource.b4PortNum)


//--------------------------------------------------
// Definitions of Enum Payload MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_REPLY_TYPE(x)                                    (g_unDpMstRxReplyPool.stEnumPathResource.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_REQUEST_ID(x)                                    (g_unDpMstRxReplyPool.stEnumPathResource.b7ReqID = (x))
#define SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_PORT_NUM(x)                                      (g_unDpMstRxReplyPool.stEnumPathResource.b4PortNum = (x))
#define SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FEC_CAP(x)                                       (g_unDpMstRxReplyPool.stEnumPathResource.b1FecCap = (x))
#define SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN(x)                                      {\
                                                                                                    WORD usLocalValue = (WORD)(x);\
                                                                                                    g_unDpMstRxReplyPool.stEnumPathResource.pucFullPBN[0] = HIBYTE(usLocalValue);\
                                                                                                    g_unDpMstRxReplyPool.stEnumPathResource.pucFullPBN[1] = LOBYTE(usLocalValue);\
                                                                                                }
#define GET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN()                                       (\
                                                                                                    TO_WORD(\
                                                                                                        g_unDpMstRxReplyPool.stEnumPathResource.pucFullPBN[0],\
                                                                                                        g_unDpMstRxReplyPool.stEnumPathResource.pucFullPBN[1])\
                                                                                                )
#define SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(x)                                 {\
                                                                                                    WORD usLocalValue = (WORD)(x);\
                                                                                                    g_unDpMstRxReplyPool.stEnumPathResource.pucAvailablePBN[0] = HIBYTE(usLocalValue);\
                                                                                                    g_unDpMstRxReplyPool.stEnumPathResource.pucAvailablePBN[1] = LOBYTE(usLocalValue);\
                                                                                                }
#define GET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN()                                  (\
                                                                                                    TO_WORD(\
                                                                                                        g_unDpMstRxReplyPool.stEnumPathResource.pucAvailablePBN[0],\
                                                                                                        g_unDpMstRxReplyPool.stEnumPathResource.pucAvailablePBN[1])\
                                                                                                )
#define SET_DP_MST_RX_DOWN_REPLY_ENUM_PATH_MSG_ZEROS()                                          {\
                                                                                                    g_unDpMstRxReplyPool.stEnumPathResource.b3Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Clear ID Table MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REQUEST_CLEAR_ID_TABLE_MSG_REQUEST_ID(x)                             (g_unDpMstRxRequestPool.stClearPayloadID.b7ReqID = (x))


//--------------------------------------------------
// Definitions of Clear ID Table MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_CLEAR_ID_TABLE_MSG_REPLY_TYPE(x)                               (g_unDpMstRxReplyPool.stClearPayloadID.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_CLEAR_ID_TABLE_MSG_REQUEST_ID(x)                               (g_unDpMstRxReplyPool.stClearPayloadID.b7ReqID = (x))

//--------------------------------------------------
// Definitions of Down Request Remote I2C Read MSG Macro
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_READ_MSG_PORT_NUM()                               (g_unDpMstRxRequestPool.stRemoteI2CRead.b4PortNum)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_READ_MSG_NUM_OF_WRITE()                           (g_unDpMstRxRequestPool.stRemoteI2CRead.b2NumOfI2CWriteTran)

//--------------------------------------------------
// Definitions of Down Reply Remote I2C Read MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_REPLY_TYPE(x)                              (g_unDpMstRxReplyPool.stRemoteI2CRead.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_REQUEST_ID(x)                              (g_unDpMstRxReplyPool.stRemoteI2CRead.b7ReqID = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_PORT_NUM(x)                                (g_unDpMstRxReplyPool.stRemoteI2CRead.b4PortNum = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_NUM_OF_READ(x)                             (g_unDpMstRxReplyPool.stRemoteI2CRead.ucNumOfRead = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_READ_MSG_ZEROS()                                    {\
                                                                                                    g_unDpMstRxReplyPool.stRemoteI2CRead.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Remote I2C Write MSG Macro
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_PORT_NUM()                              (g_unDpMstRxRequestPool.stRemoteI2CWrite.b4PortNum)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_WRITE_DEVICE_ID()                       (g_unDpMstRxRequestPool.stRemoteI2CWrite.b7WriteI2CDeviceID)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE()                          (g_unDpMstRxRequestPool.stRemoteI2CWrite.ucNumOfByteToWrite)
#define GET_DP_MST_RX_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(x)                        (g_unDpMstRxRequestPool.stRemoteI2CWrite.pucI2CDateToWrite[x])

//--------------------------------------------------
// Definitions of Down Request Remote I2C Reply MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REPLY_TYPE(x)                             (g_unDpMstRxReplyPool.stRemoteI2CWrite.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REQUEST_ID(x)                             (g_unDpMstRxReplyPool.stRemoteI2CWrite.b7ReqID = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_PORT_NUM(x)                               (g_unDpMstRxReplyPool.stRemoteI2CWrite.b4PortNum = (x))
#define SET_DP_MST_RX_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_ZEROS()                                   {\
                                                                                                    g_unDpMstRxReplyPool.stRemoteI2CWrite.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Query Stream Encryption Status MSG Macro
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REQUEST_ID()              (g_unDpMstRxRequestPool.stStructReqQueryStreamEncryptionStatus.b7ReqID)
#define SET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID(x)              (g_unDpMstRxRequestPool.stStructReqQueryStreamEncryptionStatus.ucStreamID = (x))
#define GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID()               (g_unDpMstRxRequestPool.stStructReqQueryStreamEncryptionStatus.ucStreamID)
#define GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_CLIENT_ID(x)              (g_unDpMstRxRequestPool.stStructReqQueryStreamEncryptionStatus.pucClientID[x])
#define GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_EVENT()            (g_unDpMstRxRequestPool.stStructReqQueryStreamEncryptionStatus.b2StreamEvent)
#define GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_EVENT_MASK()       (g_unDpMstRxRequestPool.stStructReqQueryStreamEncryptionStatus.b1StreamEventMask)
#define GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_BEHAVIOR()         (g_unDpMstRxRequestPool.stStructReqQueryStreamEncryptionStatus.b2StreamBehavior)
#define GET_DP_MST_RX_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_BEHAVIOR_MASK()    (g_unDpMstRxRequestPool.stStructReqQueryStreamEncryptionStatus.b1StreamBehaviorMask)

//--------------------------------------------------
// Definitions of Down Reply Query Stream Encryption Status MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REPLY_TYPE(x)               (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b1RepType = (x))
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REQUEST_ID(x)               (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b7ReqID = (x))
#define GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE()              (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b2StreamState)
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE(x)             (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b2StreamState = (x))
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT(x)  (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamRepeaterFunction = (x))
#define GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT()   (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamRepeaterFunction)
#define GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION()         (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamEncryption)
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION(x)        (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamEncryption = (x))
#define GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN()             (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamAuthentication)
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(x)            (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamAuthentication = (x))
#define GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE()   (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b3StreamOuputSinkType)
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE(x)  (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b3StreamOuputSinkType = (x))
#define GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE()     (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b2StreamOuputCpType)
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE(x)    (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b2StreamOuputCpType = (x))
#define GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED()                    (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b1Signed)
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED(x)                   (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b1Signed = (x))
#define GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID()                 (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.ucStreamID)
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID(x)                (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.ucStreamID = (x))
#define GET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(x)       (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.pucSignatureL[x])
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(x, y)    (g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.pucSignatureL[x] = (y))
#define SET_DP_MST_RX_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_ZEROS()                     {\
                                                                                                    g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b3Zero = 0;\
                                                                                                    g_unDpMstRxReplyPool.stStructRepQueryStreamEncryptionStatus.b2Zero = 0;\
                                                                                                }
//--------------------------------------------------
// Definitions of Connection Status Notify Message Macro
//--------------------------------------------------
#define GET_DP_MST_RX_UP_REQUEST_CONNECTION_STATUS_NOTIFY_PLUG_STATUS()                         (g_unDpMstRxRequestPool.stConnectionStatusNotify.b1DpPlugStatus)

//--------------------------------------------------
// Definitions of Connection Status Notify Message Macro
//--------------------------------------------------
#define SET_DP_MST_RX_REPLY_MSG_CONNECTION_STATUS_NOTIFY_REPLY_TYPE(x)                          (g_unDpMstRxReplyPool.stConnectionStatusNotify.b1RepType = (x))
#define SET_DP_MST_RX_REPLY_MSG_CONNECTION_STATUS_NOTIFY_REQUEST_ID(x)                          (g_unDpMstRxReplyPool.stConnectionStatusNotify.b7ReqID = (x))

//--------------------------------------------------
// Definitions of Resource Status Notify Message Macro
//--------------------------------------------------
#define SET_DP_MST_RX_REPLY_MSG_RESOURCE_STATUS_NOTIFY_REPLY_TYPE(x)                            (g_unDpMstRxReplyPool.stResourceStatusNotify.b1RepType = (x))
#define SET_DP_MST_RX_REPLY_MSG_RESOURCE_STATUS_NOTIFY_REQUEST_ID(x)                            (g_unDpMstRxReplyPool.stResourceStatusNotify.b7ReqID = (x))

//--------------------------------------------------
// Definitions of Up Request Sink Event Notify MSG Macro
//--------------------------------------------------
#define SET_DP_MST_RX_REQUEST_MSG_SINK_EVENT_PORT_NUM(x)                                        (g_unDpMstRxRequestPool.stStructReqSinkEventNotify.b4PortNum = (x))
#define SET_DP_MST_RX_REQUEST_MSG_SINK_EVENT_GUID(x, y)                                         (g_unDpMstRxRequestPool.stStructReqSinkEventNotify.pucGUID[x] = (y))
#define GET_DP_MST_RX_REQUEST_MSG_SINK_EVENT_ID(x)                                              (\
                                                                                                    TO_WORD(\
                                                                                                        g_unDpMstRxRequestPool.stStructReqSinkEventNotify.pucEventID[0],\
                                                                                                        g_unDpMstRxRequestPool.stStructReqSinkEventNotify.pucEventID[1])\
                                                                                                )
#define SET_DP_MST_RX_REQUEST_MSG_SINK_EVENT_ID(x)                                              {\
                                                                                                    WORD usLocalValue = (WORD)(x);\
                                                                                                    g_unDpMstRxRequestPool.stStructReqSinkEventNotify.pucEventID[0] = HIBYTE(usLocalValue);\
                                                                                                    g_unDpMstRxRequestPool.stStructReqSinkEventNotify.pucEventID[1] = LOBYTE(usLocalValue);\
                                                                                                }
#define SET_DP_MST_RX_REQUEST_MSG_SINK_EVENT_ZEROS()                                            {\
                                                                                                    g_unDpMstRxRequestPool.stStructReqSinkEventNotify.b1Zero = 0;\
                                                                                                    g_unDpMstRxRequestPool.stStructReqSinkEventNotify.b4Zero1 = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Sink Event Notify Message Macro
//--------------------------------------------------
#define SET_DP_MST_RX_REPLY_MSG_SINK_EVENT_NOTIFY_REPLY_TYPE(x)                                 (g_unDpMstRxReplyPool.stSinkEventNotify.b1RepType = (x))
#define SET_DP_MST_RX_REPLY_MSG_SINK_EVENT_NOTIFY_REQUEST_ID(x)                                 (g_unDpMstRxReplyPool.stSinkEventNotify.b7ReqID = (x))


//--------------------------------------------------
// Definitions of Illegal MSG Reply Macro
//--------------------------------------------------
#define SET_DP_MST_RX_REPLY_ILLEGAL_MSG_REPLY_TYPE(x)                                           (g_unDpMstRxReplyPool.stStructRepNak.b1RepType = (x))
#define SET_DP_MST_RX_REPLY_ILLEGAL_MSG_REQUESET_ID(x)                                          (g_unDpMstRxReplyPool.stStructRepNak.b7ReqID = (x))
#define SET_DP_MST_RX_REPLY_ILLEGAL_MSG_GUID(x, y)                                              (g_unDpMstRxReplyPool.stStructRepNak.pucGuid[x] = (y))
#define SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_REASON(x)                                          (g_unDpMstRxReplyPool.stStructRepNak.ucNakReason = (x))
#define SET_DP_MST_RX_REPLY_ILLEGAL_MSG_NACK_DATA(x)                                            (g_unDpMstRxReplyPool.stStructRepNak.ucNakData = (x))

//--------------------------------------------------
// Definitions of Illegal I2C Read MSG Reply Macro
//--------------------------------------------------
#define SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_REP_TYPE(x)                                     (g_unDpMstRxReplyPool.stRemoteI2CReadNak.b1RepType = (x))
#define SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_REQUESET_ID(x)                                  (g_unDpMstRxReplyPool.stRemoteI2CReadNak.b7ReqID = (x))
#define SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_GUID(x, y)                                      (g_unDpMstRxReplyPool.stRemoteI2CReadNak.pucGuid[x] = (y))
#define SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_PORT(x)                                         (g_unDpMstRxReplyPool.stRemoteI2CReadNak.b4Port = (x))
#define SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_REASON(x)                                       (g_unDpMstRxReplyPool.stRemoteI2CReadNak.ucNakReason = (x))
#define SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_TRANSACTION(x)                                  (g_unDpMstRxReplyPool.stRemoteI2CReadNak.b2I2CNakTransaction = (x))
#define SET_DP_MST_RX_REPLY_REMOTE_I2C_READ_NAK_ZEROS()                                         {\
                                                                                                    g_unDpMstRxReplyPool.stRemoteI2CReadNak.b4zero = 0;\
                                                                                                    g_unDpMstRxReplyPool.stRemoteI2CReadNak.b6zero1 = 0;\
                                                                                                }

//--------------------------------------------------
// Macro of Message Common Array Usage info
//--------------------------------------------------
#define GET_DP_MST_RX_REQUEST_POOL_FREE()                                                       (g_stDpMstRxPoolUsage.b1ReqArray)
#define SET_DP_MST_RX_REQUEST_POOL_FREE()                                                       {\
                                                                                                    g_stDpMstRxPoolUsage.b1ReqArray = _TRUE;\
                                                                                                    CLR_DP_MST_RX_REQUEST_MSG_PORT();\
                                                                                                }
#define CLR_DP_MST_RX_REQUEST_POOL_FREE()                                                       {\
                                                                                                    g_stDpMstRxPoolUsage.b1ReqArray = _FALSE;\
                                                                                                    SET_DP_MST_RX_REQUEST_MSG_PORT(GET_DP_RX_BASE_PORT());\
                                                                                                }
#define GET_DP_MST_RX_REPLY_POOL_FREE()                                                         (g_stDpMstRxPoolUsage.b1ReplyArray)
#define SET_DP_MST_RX_REPLY_POOL_FREE()                                                         {\
                                                                                                    g_stDpMstRxPoolUsage.b1ReplyArray = _TRUE;\
                                                                                                    CLR_DP_MST_RX_REPLY_MSG_PORT();\
                                                                                                }
#define CLR_DP_MST_RX_REPLY_POOL_FREE()                                                         {\
                                                                                                    g_stDpMstRxPoolUsage.b1ReplyArray = _FALSE;\
                                                                                                    SET_DP_MST_RX_REPLY_MSG_PORT(GET_DP_RX_BASE_PORT());\
                                                                                                }

//--------------------------------------------------
// Macro of Message Buffer Usage info
//--------------------------------------------------
#define GET_DP_MST_RX_REPLY_BUF_FREE()                                                          (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1ReplyBufFree)
#define SET_DP_MST_RX_REPLY_BUF_FREE()                                                          (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1ReplyBufFree = _TRUE)
#define CLR_DP_MST_RX_REPLY_BUF_FREE()                                                          (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1ReplyBufFree = _FALSE)

#define GET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY()                                               (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1DownRequestBufPriority)
#define SET_DP_MST_RX_DOWN_REQUEST_BUF_PRIORITY(x)                                              (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1DownRequestBufPriority = (x))

#define GET_DP_MST_RX_UP_REPLY_BUF_PRIORITY()                                                   (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1UpReplyBufPriority)
#define SET_DP_MST_RX_UP_REPLY_BUF_PRIORITY(x)                                                  (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1UpReplyBufPriority = (x))

//--------------------------------------------------
// Macro of Message Function Action info
//--------------------------------------------------
#define GET_DP_MST_RX_DOWN_REQUEST_ANAL()                                                       (g_stDpMstRxMsgFunction.b1DownRequestAnal)
#define SET_DP_MST_RX_DOWN_REQUEST_ANAL()                                                       (g_stDpMstRxMsgFunction.b1DownRequestAnal = _TRUE)
#define CLR_DP_MST_RX_DOWN_REQUEST_ANAL()                                                       (g_stDpMstRxMsgFunction.b1DownRequestAnal = _FALSE)

#define GET_DP_MST_RX_DOWN_REPLY_READY()                                                        (g_stDpMstRxMsgFunction.b1DownReplyReady)
#define SET_DP_MST_RX_DOWN_REPLY_READY()                                                        (g_stDpMstRxMsgFunction.b1DownReplyReady = _TRUE)
#define CLR_DP_MST_RX_DOWN_REPLY_READY()                                                        (g_stDpMstRxMsgFunction.b1DownReplyReady = _FALSE)

#define GET_DP_MST_RX_DOWN_REPLY_SET_HPD()                                                      (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1DpMstRxMacDownReplyHPD)
#define SET_DP_MST_RX_DOWN_REPLY_SET_HPD()                                                      {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1DpMstRxMacDownReplyHPD = _TRUE;}
#define CLR_DP_MST_RX_DOWN_REPLY_SET_HPD()                                                      {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1DpMstRxMacDownReplyHPD = _FALSE;}

#define GET_DP_MST_RX_DOWN_REPLY_RETRY_NUM()                                                    (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyRetryNum)
#define INCREASE_DP_MST_RX_DOWN_REPLY_RETRY_NUM()                                               {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyRetryNum ++;}
#define CLR_DP_MST_RX_DOWN_REPLY_RETRY_NUM()                                                    {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyRetryNum = 0;}

#if(_DP_MST_RX_DOWN_REPLY_MANUAL_MODE_SUPPORT == _ON)
#define GET_DP_MST_RX_DOWN_REPLY_MSG_COUNT()                                                    (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyManualMsgCount)
#define SET_DP_MST_RX_DOWN_REPLY_MSG_COUNT(x)                                                   {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyManualMsgCount = (x);}
#define CLR_DP_MST_RX_DOWN_REPLY_MSG_COUNT()                                                    {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyManualMsgCount = 0;}

#define GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH()                                                   (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyManualMsgLength)
#define SET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH(x)                                                  {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyManualMsgLength = (x);}
#define CLR_DP_MST_RX_DOWN_REPLY_MSG_LENGTH()                                                   {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyManualMsgLength = 0;}

#define GET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH_MAX()                                               (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyManualMsgBodyLengthMax)
#define SET_DP_MST_RX_DOWN_REPLY_MSG_LENGTH_MAX(x)                                              {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyManualMsgBodyLengthMax = (x);}
#define CLR_DP_MST_RX_DOWN_REPLY_MSG_LENGTH_MAX()                                               {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucDownReplyManualMsgBodyLengthMax = 0;}
#endif

#define GET_DP_MST_RX_DOWN_REPLY_DIRECTLY()                                                     (g_stDpMstRxMsgFunction.b1DownReplyDirect)
#define SET_DP_MST_RX_DOWN_REPLY_DIRECTLY()                                                     (g_stDpMstRxMsgFunction.b1DownReplyDirect = _TRUE)
#define CLR_DP_MST_RX_DOWN_REPLY_DIRECTLY()                                                     (g_stDpMstRxMsgFunction.b1DownReplyDirect = _FALSE)

#define GET_DP_MST_RX_DOWN_REPLY_BYPASS()                                                       (g_stDpMstRxMsgFunction.b1DownReplyBypass)
#define SET_DP_MST_RX_DOWN_REPLY_BYPASS()                                                       (g_stDpMstRxMsgFunction.b1DownReplyBypass = _TRUE)
#define CLR_DP_MST_RX_DOWN_REPLY_BYPASS()                                                       (g_stDpMstRxMsgFunction.b1DownReplyBypass = _FALSE)

#define GET_DP_MST_RX_UP_REQUEST_READY()                                                        (g_stDpMstRxMsgFunction.b1UpRequestReady)
#define SET_DP_MST_RX_UP_REQUEST_READY()                                                        (g_stDpMstRxMsgFunction.b1UpRequestReady = _TRUE)
#define CLR_DP_MST_RX_UP_REQUEST_READY()                                                        (g_stDpMstRxMsgFunction.b1UpRequestReady = _FALSE)

#define GET_DP_MST_RX_UP_REQUEST_ANAL()                                                         (g_stDpMstRxMsgFunction.b1UpRequestAnal)
#define SET_DP_MST_RX_UP_REQUEST_ANAL()                                                         (g_stDpMstRxMsgFunction.b1UpRequestAnal = _TRUE)
#define CLR_DP_MST_RX_UP_REQUEST_ANAL()                                                         (g_stDpMstRxMsgFunction.b1UpRequestAnal = _FALSE)

#define GET_DP_MST_RX_UP_REPLY_ANAL()                                                           (g_stDpMstRxMsgFunction.b1UpReplyAnal)
#define SET_DP_MST_RX_UP_REPLY_ANAL()                                                           (g_stDpMstRxMsgFunction.b1UpReplyAnal = _TRUE)
#define CLR_DP_MST_RX_UP_REPLY_ANAL()                                                           (g_stDpMstRxMsgFunction.b1UpReplyAnal = _FALSE)

#define GET_DP_MST_RX_UP_REPLY_DIRECTLY()                                                       (g_stDpMstRxMsgFunction.b1UpReplyDirect)
#define SET_DP_MST_RX_UP_REPLY_DIRECTLY()                                                       (g_stDpMstRxMsgFunction.b1UpReplyDirect = _TRUE)
#define CLR_DP_MST_RX_UP_REPLY_DIRECTLY()                                                       (g_stDpMstRxMsgFunction.b1UpReplyDirect = _FALSE)

#define GET_DP_MST_RX_GEN_DOWN_REQUEST_MSG()                                                    (g_stDpMstRxMsgFunction.ucGenDownRequestMsg)
#define SET_DP_MST_RX_GEN_DOWN_REQUEST_MSG(x)                                                   (g_stDpMstRxMsgFunction.ucGenDownRequestMsg = (x))
#define CLR_DP_MST_RX_GEN_DOWN_REQUEST_MSG()                                                    (g_stDpMstRxMsgFunction.ucGenDownRequestMsg = _DP_MSG_NONE)

#define GET_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG()                                               (g_stDpMstRxMsgFunction.b1SelfGenDownRequest)
#define SET_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG()                                               (g_stDpMstRxMsgFunction.b1SelfGenDownRequest = _TRUE)
#define CLR_DP_MST_RX_SELF_GEN_DOWN_REQUEST_MSG()                                               (g_stDpMstRxMsgFunction.b1SelfGenDownRequest = _FALSE)

#if(_DP_TX_SUPPORT == _ON)
#define GET_DP_MST_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY()                                          (g_stDpMstRxMsgFunction.b1WaitRemoteLinkAddressReply)
#define SET_DP_MST_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY()                                          (g_stDpMstRxMsgFunction.b1WaitRemoteLinkAddressReply = _TRUE)
#define CLR_DP_MST_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY()                                          (g_stDpMstRxMsgFunction.b1WaitRemoteLinkAddressReply = _FALSE)
#endif

#define GET_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT()                                                (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1CancelMsgTimeoutEvent)
#define SET_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT()                                                (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1CancelMsgTimeoutEvent = _TRUE)
#define CLR_DP_MST_RX_CANCEL_MSG_TIMEOUT_EVENT()                                                (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1CancelMsgTimeoutEvent = _FALSE)

#define GET_DP_MST_RX_UP_REQUEST_RETRY_NUM()                                                    (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucUpRequestRetryNum)
#define INCREASE_DP_MST_RX_UP_REQUEST_RETRY_NUM()                                               {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucUpRequestRetryNum ++;}
#define CLR_DP_MST_RX_UP_REQUEST_RETRY_NUM()                                                    {g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].ucUpRequestRetryNum = 0;}

#define GET_DP_MST_RX_UP_REQUEST_PROCESSING()                                                   (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1DpUpRequestProcessing)
#define SET_DP_MST_RX_UP_REQUEST_PROCESSING()                                                   (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1DpUpRequestProcessing = _TRUE)
#define CLR_DP_MST_RX_UP_REQUEST_PROCESSING()                                                   {\
                                                                                                    g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1DpUpRequestProcessing = _FALSE;\
                                                                                                    ScalerTimerCancelTimerEvent(ScalerDpMstRxGetTimerEvent(GET_DP_RX_BASE_PORT(), _SCALER_TIMER_EVENT_DP_UP_REQUEST_PROCESSING));\
                                                                                                }

#define GET_DP_MST_RX_UP_REQUEST_ISSUED_ID()                                                    (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].enumIssuedUpRequestID)
#define SET_DP_MST_RX_UP_REQUEST_ISSUED_ID(x)                                                   (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].enumIssuedUpRequestID = (x))
#define CLR_DP_MST_RX_UP_REQUEST_ISSUED_ID()                                                    (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].enumIssuedUpRequestID = _DP_MSG_NONE)

#define GET_DP_MST_RX_UP_REQUEST_INITIATED_QUEUE()                                              (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].enumUpReqIntiatedQueue)
#define SET_DP_MST_RX_UP_REQUEST_INITIATED_QUEUE(x)                                             (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].enumUpReqIntiatedQueue = (x))
#define CLR_DP_MST_RX_UP_REQUEST_INITIATED_QUEUE()                                              (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].enumUpReqIntiatedQueue = _RX_UP_REQ_QUEUE_NONE)

#define GET_DP_MST_RX_UP_REQUEST_BYPASS_DONE()                                                  (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1UpRequestBypassDone)
#define SET_DP_MST_RX_UP_REQUEST_BYPASS_DONE()                                                  (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1UpRequestBypassDone = _TRUE)
#define CLR_DP_MST_RX_UP_REQUEST_BYPASS_DONE()                                                  (g_pstDpMstRxMsgPortInfo[(GET_DP_RX_BASE_PORT() - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1UpRequestBypassDone = _FALSE)

#define GET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG()                                                (g_stDpMstRxMsgOtherInfo.b1IllegalDownRequestMSG)
#define SET_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG()                                                (g_stDpMstRxMsgOtherInfo.b1IllegalDownRequestMSG = _TRUE)
#define CLR_DP_MST_RX_ILLEGAL_DOWN_REQUEST_MSG()                                                (g_stDpMstRxMsgOtherInfo.b1IllegalDownRequestMSG = _FALSE)
#define GET_DP_MST_RX_ILLEGAL_UP_REQUEST_MSG()                                                  (g_stDpMstRxMsgOtherInfo.b1IllegalUpRequestMSG)
#define SET_DP_MST_RX_ILLEGAL_UP_REQUEST_MSG()                                                  (g_stDpMstRxMsgOtherInfo.b1IllegalUpRequestMSG = _TRUE)
#define CLR_DP_MST_RX_ILLEGAL_UP_REQUEST_MSG()                                                  (g_stDpMstRxMsgOtherInfo.b1IllegalUpRequestMSG = _FALSE)

#define GET_DP_MST_RX_REMOTE_I2C_READ_FAIL()                                                    (g_stDpMstRxMsgOtherInfo.b1RemoteI2CReadFail)
#define SET_DP_MST_RX_REMOTE_I2C_READ_FAIL()                                                    (g_stDpMstRxMsgOtherInfo.b1RemoteI2CReadFail = _TRUE)
#define CLR_DP_MST_RX_REMOTE_I2C_READ_FAIL()                                                    (g_stDpMstRxMsgOtherInfo.b1RemoteI2CReadFail = _FALSE)

#define GET_DP_MST_RX_GEN_UP_REQUEST_MSG()                                                      (g_stDpMstRxMsgOtherInfo.enumGenUpRequestID)
#define SET_DP_MST_RX_GEN_UP_REQUEST_MSG(x)                                                     (g_stDpMstRxMsgOtherInfo.enumGenUpRequestID = (x))
#define CLR_DP_MST_RX_GEN_UP_REQUEST_MSG()                                                      (g_stDpMstRxMsgOtherInfo.enumGenUpRequestID = _DP_MSG_NONE)

#define GET_DP_MST_RX_UP_REQUEST_ISSUED_SINK_EVENT_ID()                                         (g_stDpMstRxMsgOtherInfo.enumSinkEventID)
#define SET_DP_MST_RX_UP_REQUEST_ISSUED_SINK_EVENT_ID(x)                                        (g_stDpMstRxMsgOtherInfo.enumSinkEventID = (x))
#define CLR_DP_MST_RX_UP_REQUEST_ISSUED_SINK_EVENT_ID()                                         (g_stDpMstRxMsgOtherInfo.enumSinkEventID = _SINK_EVENT_NONE)

#define GET_DP_MST_RX_UP_REQUEST_QUEUE(enumInputPort, enumDpMstPort)                            ((EnumDpMstRxUpReqQueue)(((enumInputPort) << 4) | (enumDpMstPort)))
#define GET_DP_MST_RX_UP_REQUEST_QUEUE_INPUT_PORT(enumDpMstRxUpReqQueue)                        ((EnumInputPort)((enumDpMstRxUpReqQueue) >> 4))
#define GET_DP_MST_RX_UP_REQUEST_QUEUE_PORT_NUM(enumDpMstRxUpReqQueue)                          ((EnumDpMstPort)((enumDpMstRxUpReqQueue) & 0x0F))

#define GET_DP_MST_RX_MSG_REQUEST_ID()                                                          (g_unDpMstRxRequestPool.pucData[0] & 0x7F)
#define SET_DP_MST_RX_MSG_REQUEST_ID(x)                                                         (g_unDpMstRxRequestPool.pucData[0] = (x))

#define GET_DP_MST_RX_MSG_REPLY_ID()                                                            (g_unDpMstRxReplyPool.pucData[0] & 0x7F)
#define GET_DP_MST_RX_MSG_REPLY_TYPE()                                                          ((g_unDpMstRxReplyPool.pucData[0]) >> 7)
#define GET_DP_MST_RX_MSG_UP_REPLY_TYPE()                                                       ((g_unDpMstRxReplyPool.pucData[0]) >> 7)

//--------------------------------------------------
// DP Rx MSG Port
//--------------------------------------------------
#define GET_DP_MST_RX_REQUEST_MSG_PORT()                                                        (g_stDpMstRxPoolUsage.enumDpMstRxRequestMsgPort)
#define SET_DP_MST_RX_REQUEST_MSG_PORT(x)                                                       (g_stDpMstRxPoolUsage.enumDpMstRxRequestMsgPort = (x))
#define CLR_DP_MST_RX_REQUEST_MSG_PORT()                                                        (g_stDpMstRxPoolUsage.enumDpMstRxRequestMsgPort = _NO_INPUT_PORT)
#define GET_DP_MST_RX_REPLY_MSG_PORT()                                                          (g_stDpMstRxPoolUsage.enumDpMstRxReplyMsgPort)
#define SET_DP_MST_RX_REPLY_MSG_PORT(x)                                                         (g_stDpMstRxPoolUsage.enumDpMstRxReplyMsgPort = (x))
#define CLR_DP_MST_RX_REPLY_MSG_PORT()                                                          (g_stDpMstRxPoolUsage.enumDpMstRxReplyMsgPort = _NO_INPUT_PORT)

#define GET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM()                                               (g_enumDpMstRxDownRequestPortNum)
#define SET_DP_MST_RX_DOWN_REQUEST_MSG_PORT_NUM(x)                                              (g_enumDpMstRxDownRequestPortNum = (x))

#define GET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT()                                             (g_stDpMstRxMsgPort.enumDpMstRxDownRequestMsgInputPort)
#define SET_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT(x)                                            (g_stDpMstRxMsgPort.enumDpMstRxDownRequestMsgInputPort = (x))
#define CLR_DP_MST_RX_DOWN_REQUEST_MSG_INPUT_PORT()                                             (g_stDpMstRxMsgPort.enumDpMstRxDownRequestMsgInputPort = _NO_INPUT_PORT)

#define GET_DP_MST_RX_UP_REPLY_MSG_INPUT_PORT()                                                 (g_stDpMstRxMsgPort.enumDpMstRxUpReplyMsgInputPort)
#define SET_DP_MST_RX_UP_REPLY_MSG_INPUT_PORT(x)                                                (g_stDpMstRxMsgPort.enumDpMstRxUpReplyMsgInputPort = (x))
#define CLR_DP_MST_RX_UP_REPLY_MSG_INPUT_PORT()                                                 (g_stDpMstRxMsgPort.enumDpMstRxUpReplyMsgInputPort = _NO_INPUT_PORT)

#define GET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT()                                              (g_stDpMstRxMsgPort.enumDpMstRxDownReplyMsgTargetPort)
#define SET_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT(x)                                             (g_stDpMstRxMsgPort.enumDpMstRxDownReplyMsgTargetPort = (x))
#define CLR_DP_MST_RX_DOWN_REPLY_MSG_TARGET_PORT()                                              (g_stDpMstRxMsgPort.enumDpMstRxDownReplyMsgTargetPort = _NO_INPUT_PORT)

#define GET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT()                                              (g_stDpMstRxMsgPort.enumDpMstRxUpRequestMsgTargetPort)
#define SET_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT(x)                                             (g_stDpMstRxMsgPort.enumDpMstRxUpRequestMsgTargetPort = (x))
#define CLR_DP_MST_RX_UP_REQUEST_MSG_TARGET_PORT()                                              (g_stDpMstRxMsgPort.enumDpMstRxUpRequestMsgTargetPort = _NO_INPUT_PORT)

//--------------------------------------------------
// DP Rx EVENT
//--------------------------------------------------
#define GET_DP_MST_RX_EVENT()                                                                   (g_ucDpMstRxEvent)
#define SET_DP_MST_RX_EVENT(x)                                                                  (g_ucDpMstRxEvent = (x))

//--------------------------------------------------
// Definitions of Down Request Related Register Macro
//--------------------------------------------------


#define SET_DP_MST_RX_REG_DOWN_REQUEST_MSG_RECEIVE_CRC_IGNORE_ENABLE()                          {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_00_AUX_RX_MSG_RX_CTRL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));}
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_MSG_FINISH()                                             {SCALER32_DP_SET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_08_MSG_RX_IRQ_FLAG, _REG8TO32_BYTE_0, 0xFF);}
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_MSG_ERROR()                                              {SCALER32_DP_SET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_0C_MSG_RX_STATUS, _REG8TO32_BYTE_0, 0xFF);}
#define SET_DP_MST_RX_REG_DOWN_REQUEST_MSG_DOUBLE_BUFFER_ENABLE()                               {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_10_MSG_RX_BUF_CLR, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);}
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_BUF1()                                              {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_10_MSG_RX_BUF_CLR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));}
#define SET_DP_MST_RX_REG_DOWN_REQUEST_WRITE_1000_RST_FSM()                                     {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_00_AUX_RX_MSG_RX_CTRL, ~(_BIT15 | _BIT14), (_BIT15 | _BIT14));}
#define SET_DP_MST_RX_REG_DOWN_REQUEST_WRITE_1000_RST_FLAG()                                    {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_00_AUX_RX_MSG_RX_CTRL, ~_BIT13, _BIT13);}
#define SET_DP_MST_RX_REG_DOWN_REQUEST_WRITE_1000_RST_BUF()                                     {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_00_AUX_RX_MSG_RX_CTRL, ~_BIT11, _BIT11);}
#define SET_DP_MST_RX_REG_DOWN_REQUEST_FORCE_ACK_ADDRESS_UNEXPECT()                             {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_00_AUX_RX_MSG_RX_CTRL, ~_BIT19, _BIT19);}

#define SET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_BUF1_MSG_RECEIVE_ENABLE()                           {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_00_AUX_RX_MSG_RX_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));}
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_BUF1_MSG_RECEIVE_ENABLE()                           {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_00_AUX_RX_MSG_RX_CTRL, ~(_BIT1 | _BIT0), 0x00);}

#define SET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE()                                {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_00_AUX_RX_MSG_RX_CTRL, ~_BIT0, _BIT0);}
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE()                                {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_00_AUX_RX_MSG_RX_CTRL, ~_BIT0, 0x00);}

#define GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_FINISH_IRQ_ENABLE()                             ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_04_MSG_RX_IRQ_EN, _BIT0))
#define SET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_FINISH_IRQ_ENABLE()                             {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_04_MSG_RX_IRQ_EN, ~_BIT0, _BIT0);}
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_FINISH_IRQ_ENABLE()                             {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_04_MSG_RX_IRQ_EN, ~_BIT0, 0x00);}

#define GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_FINISH()                                        ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_08_MSG_RX_IRQ_FLAG, _BIT0))
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_FINISH()                                        {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_08_MSG_RX_IRQ_FLAG, _BIT0);}

#define GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_LENGTH()                                        (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_20_MSG_RX_BUF0, _REG8TO32_BYTE_0) & 0x7F)
#define GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_ERROR()                                         (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_0C_MSG_RX_STATUS, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0_MSG_ERROR()                                         {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_0C_MSG_RX_STATUS, (_BIT3 | _BIT2 | _BIT1 | _BIT0));}
#define SET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_READ_PTR(x)                                         {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_28_MSG_RX_BUF0_RDPTR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x));}
#define GET_DP_MST_RX_REG_DOWN_REQUEST_BUF0_DATA()                                              (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_2C_MSG_RX_BUF0_RD_DATA, _REG8TO32_BYTE_0))
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF0()                                                   {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_10_MSG_RX_BUF_CLR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));}

#define GET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN()                                           ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_08_MSG_RX_IRQ_FLAG, _BIT8))
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN()                                           {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_08_MSG_RX_IRQ_FLAG, _BIT8);}

#define GET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE()                                ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_04_MSG_RX_IRQ_EN, _BIT8))
#define SET_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE()                                {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_04_MSG_RX_IRQ_EN, ~_BIT8, _BIT8);}
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_ADDR_WRITTEN_IRQ_ENABLE()                                {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_04_MSG_RX_IRQ_EN, ~_BIT8, 0x00);}

#define SET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE()                                {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_00_AUX_RX_MSG_RX_CTRL, ~_BIT1, _BIT1);}
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE()                                {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_00_AUX_RX_MSG_RX_CTRL, ~_BIT1, 0x00);}

#define GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH_IRQ_ENABLE()                             ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_04_MSG_RX_IRQ_EN, _BIT4))
#define SET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH_IRQ_ENABLE()                             {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_04_MSG_RX_IRQ_EN, ~_BIT4, _BIT4);}
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH_IRQ_ENABLE()                             {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_04_MSG_RX_IRQ_EN, ~_BIT4, 0x00);}

#define GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH()                                        ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_08_MSG_RX_IRQ_FLAG, _BIT4))
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_FINISH()                                        {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_08_MSG_RX_IRQ_FLAG, _BIT4);}

#define GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_LENGTH()                                        (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_30_MSG_RX_BUF1_LEN, _REG8TO32_BYTE_0) & 0x7F)
#define GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_ERROR()                                         (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_0C_MSG_RX_STATUS, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1_MSG_ERROR()                                         {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_0C_MSG_RX_STATUS, (_BIT7 | _BIT6 | _BIT5 | _BIT4));}
#define SET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_READ_PTR(x)                                         {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_38_MSG_RX_BUF1_RDPTR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x));}
#define GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_WRITE_PTR()                                         (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_34_MSG_RX_BUF1_WRPTR, _REG8TO32_BYTE_0) & 0x7F)
#define GET_DP_MST_RX_REG_DOWN_REQUEST_BUF1_DATA()                                              (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_3C_MSG_RX_BUF1_RD_DATA, _REG8TO32_BYTE_0))
#define CLR_DP_MST_RX_REG_DOWN_REQUEST_BUF1()                                                   {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_10_MSG_RX_BUF_CLR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));}

#define GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCT()                                                (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_14_MSG_RX_DATA0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4)
#define GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_LCR()                                                (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_14_MSG_RX_DATA0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BYPASS_PORT_NUM()                                    (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_14_MSG_RX_DATA0, (_BIT15 | _BIT14 | _BIT13 | _BIT12)) >> 12)

#define GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_BROADCAST()                                          (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_1C_MSG_RX_DATA2, _BIT7))
#define GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_PATH()                                               (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_1C_MSG_RX_DATA2, _BIT6))
#define GET_DP_MST_RX_REG_DOWN_REQUEST_MSG_MSN()                                                (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_1C_MSG_RX_DATA2, _BIT12))

#define SET_DP_MST_RX_REG_DOWN_REQUEST_HEADER0_INFO()                                           {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_10_MSG_RX_BUF_CLR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);}
#define SET_DP_MST_RX_REG_DOWN_REQUEST_HEADER1_INFO()                                           {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_10_MSG_RX_BUF_CLR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);}

#define GET_DP_MST_RX_REG_DOWN_REQUEST_HEADER_CRC()                                             (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_1C_MSG_RX_DATA2, (_BIT11 | _BIT10 | _BIT9 | _BIT8)))
#define GET_DP_MST_RX_REG_DOWN_REQUEST_BODY_CRC()                                               (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_1C_MSG_RX_DATA2, 0x02))

//--------------------------------------------------
// Definitions of AUX MSG IRQ Flag
//--------------------------------------------------
#define GET_DP_AUX_RX0_MSG_IRQ_FLAG()                                                           (ScalerGetBit_EXINT(P6F_1B_ADI_DP_IRQ9, _BIT0) == _BIT0)
#define GET_DP_AUX_RX1_MSG_IRQ_FLAG()                                                           (ScalerGetBit_EXINT(P6F_1B_ADI_DP_IRQ9, _BIT1) == _BIT1)
#define GET_DP_AUX_RX2_MSG_IRQ_FLAG()                                                           (ScalerGetBit_EXINT(P6F_1B_ADI_DP_IRQ9, _BIT2) == _BIT2)

//--------------------------------------------------
// Definitions of Down Reply Related Register Macro
//--------------------------------------------------
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#define GET_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ()                                            (g_stDpAuxRxMsgFlag.pbDpAuxRxMsgDownRepIrqEnable[ScalerDpAuxRxMsgFlagMapping(GET_DP_RX_BASE_PORT())])
#define SET_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ()                                            {g_stDpAuxRxMsgFlag.pbDpAuxRxMsgDownRepIrqEnable[ScalerDpAuxRxMsgFlagMapping(GET_DP_RX_BASE_PORT())] = _ENABLE;}
#define CLR_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ()                                            {g_stDpAuxRxMsgFlag.pbDpAuxRxMsgDownRepIrqEnable[ScalerDpAuxRxMsgFlagMapping(GET_DP_RX_BASE_PORT())] = _DISABLE;}

#define GET_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ_FLAG()                                       ((bit)(g_stDpAuxRxMsgFlag.pucDpAuxRxDpcdIrqVector[ScalerDpAuxRxMsgFlagMapping(GET_DP_RX_BASE_PORT())] & _BIT4))
#define CLR_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ_FLAG()                                       {g_stDpAuxRxMsgFlag.pucDpAuxRxDpcdIrqVector[ScalerDpAuxRxMsgFlagMapping(GET_DP_RX_BASE_PORT())] &= ~_BIT4;}
#else
#define GET_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ()                                            ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18002_58_AUX_DPCD_MISC1_IRQ_EN, _BIT13))
#define SET_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ()                                            {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18002_58_AUX_DPCD_MISC1_IRQ_EN, ~_BIT13, _BIT13);}
#define CLR_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ()                                            {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18002_58_AUX_DPCD_MISC1_IRQ_EN, ~_BIT13, 0x00);}

#define GET_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ_FLAG()                                       ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18002_5C_AUX_DPCD_MISC1_IRQ_FLAG, _BIT13))
#define CLR_DP_MST_RX_REG_DOWN_REPLY_READY_BIT_IRQ_FLAG()                                       {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18002_5C_AUX_DPCD_MISC1_IRQ_FLAG, _BIT13);}
#endif

#define GET_DP_MST_RX_REG_DOWN_REPLY_MSG_IS_READ_EXINT()                                        ((bit)SCALER32_DP_GET_OFFSET_BIT_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18003_E8_TX_READ_FLAG, _BIT1))
#define CLR_DP_MST_RX_REG_DOWN_REPLY_MSG_IS_READ()                                              {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_E8_TX_READ_FLAG, _BIT1);}
#define CLR_DP_MST_RX_REG_DOWN_REPLY_MSG_IS_READ_EXINT()                                        {SCALER32_DP_SET_OFFSET_DWORD_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18003_E8_TX_READ_FLAG, _BIT1);}

//--------------------------------------------------
// Definitions of Up Request Related Register Macro
//--------------------------------------------------
#if(_FW_DP_AUX_RX_MAC_SRAM_DPCD_SUPPORT == _ON)
#define GET_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ()                                            (g_stDpAuxRxMsgFlag.pbDpAuxRxMsgUpReqIrqEnable[ScalerDpAuxRxMsgFlagMapping(GET_DP_RX_BASE_PORT())])
#define SET_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ()                                            {g_stDpAuxRxMsgFlag.pbDpAuxRxMsgUpReqIrqEnable[ScalerDpAuxRxMsgFlagMapping(GET_DP_RX_BASE_PORT())] = _ENABLE;}
#define CLR_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ()                                            {g_stDpAuxRxMsgFlag.pbDpAuxRxMsgUpReqIrqEnable[ScalerDpAuxRxMsgFlagMapping(GET_DP_RX_BASE_PORT())] = _DISABLE;}

#define GET_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ_FLAG()                                       ((bit)(g_stDpAuxRxMsgFlag.pucDpAuxRxDpcdIrqVector[ScalerDpAuxRxMsgFlagMapping(GET_DP_RX_BASE_PORT())] & _BIT5))
#define CLR_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ_FLAG()                                       {g_stDpAuxRxMsgFlag.pucDpAuxRxDpcdIrqVector[ScalerDpAuxRxMsgFlagMapping(GET_DP_RX_BASE_PORT())] &= ~_BIT5;}
#else
#define GET_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ()                                            ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18002_58_AUX_DPCD_MISC1_IRQ_EN, _BIT14))
#define SET_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ()                                            {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18002_58_AUX_DPCD_MISC1_IRQ_EN, ~_BIT14, _BIT14);}
#define CLR_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ()                                            {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18002_58_AUX_DPCD_MISC1_IRQ_EN, ~_BIT14, 0x00);}

#define GET_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ_FLAG()                                       ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18002_5C_AUX_DPCD_MISC1_IRQ_FLAG, _BIT14))
#define CLR_DP_MST_RX_REG_UP_REQUEST_READY_BIT_IRQ_FLAG()                                       {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18002_5C_AUX_DPCD_MISC1_IRQ_FLAG, _BIT14);}
#endif

//--------------------------------------------------
// Definitions of Upstream Reply RelatedRegister Macro
//--------------------------------------------------
#define GET_DP_MST_RX_REG_UPSTREAM_REPLY()                                                      ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, _BIT0))
#define SET_DP_MST_RX_REG_UPSTREAM_REPLY()                                                      {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, ~_BIT0, _BIT0);}
#define CLR_DP_MST_RX_REG_UPSTREAM_REPLY()                                                      {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, ~_BIT0, 0x00);}
#define CLR_DP_MST_RX_REG_UPSTREAM_REPLY_EXINT()                                                {SCALER32_DP_SET_OFFSET_BIT_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, ~_BIT0, 0x00);}
#define SET_DP_MST_RX_REG_UPSTREAM_HW_AUTO_MODE()                                               {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, ~_BIT2, 0x00);}
#define SET_DP_MST_RX_REG_UPSTREAM_HW_MANUAL_MODE()                                             {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, ~_BIT2, _BIT2);}
#define SET_DP_MST_RX_REG_UPSTREAM_START_BIT()                                                  {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_B4_MSG_TX_SET2, ~_BIT15, _BIT15);}
#define CLR_DP_MST_RX_REG_UPSTREAM_START_BIT()                                                  {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_B4_MSG_TX_SET2, ~_BIT15, 0x00);}
#define SET_DP_MST_RX_REG_UPSTREAM_END_BIT()                                                    {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_B4_MSG_TX_SET2, ~_BIT14, _BIT14);}
#define CLR_DP_MST_RX_REG_UPSTREAM_END_BIT()                                                    {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_B4_MSG_TX_SET2, ~_BIT14, 0x00);}
#define SET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH(x)                                              {SCALER32_DP_SET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_A8_MSG_TX_LENGTH, _REG8TO32_BYTE_0, (x));}
#define GET_DP_MST_RX_REG_UPSTREAM_REPLY_LENGTH()                                               (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_A8_MSG_TX_LENGTH, _REG8TO32_BYTE_0))
#define SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT(x)                                                 {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_AC_MSG_TX_SET0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((x) << 4));}
#define GET_DP_MST_RX_REG_UPSTREAM_REPLY_LCT()                                                  ((SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_AC_MSG_TX_SET0, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> 4)
#define SET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR(x)                                                 {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_AC_MSG_TX_SET0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x));}
#define GET_DP_MST_RX_REG_UPSTREAM_REPLY_LCR()                                                  (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_AC_MSG_TX_SET0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))


#define SET_DP_MST_RX_REG_UPSTREAM_REPLY_BROADCAST(x)                                           {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_B4_MSG_TX_SET2, ~_BIT7, ((DWORD)((bit)(x)) << 7));}
#define SET_DP_MST_RX_REG_UPSTREAM_REPLY_PATH(x)                                                {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_B4_MSG_TX_SET2, ~_BIT6, ((DWORD)((bit)(x)) << 6));}
#define GET_DP_MST_RX_REG_UPSTREAM_REPLY_MSN()                                                  ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_B4_MSG_TX_SET2, _BIT12))
#define SET_DP_MST_RX_REG_UPSTREAM_REPLY_MSN(x)                                                 {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_B4_MSG_TX_SET2, ~_BIT12, ((DWORD)((bit)(x)) << 12));}
#define CLR_DP_MST_RX_REG_UPSTREAM_REPLY_BUF()                                                  {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_BC_BUF_CLR, _BIT0);}
#define CLR_DP_MST_RX_REG_UPSTREAM_REPLY_WRITE_PTR()                                            {SCALER32_DP_SET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_E0_BUF_FW_WRPTR, _REG8TO32_BYTE_0, 0x00);}
#define SET_DP_MST_RX_REG_UPSTREAM_REPLY_BUF_DATA(x)                                            {SCALER32_DP_SET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_E4_BUF_FW_WR_DATA, _REG8TO32_BYTE_0, (x));}
#define GET_DP_MST_RX_REG_UPSTREAM_REPLY_DOWN_REPLY_ADDRESS()                                   (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, _BIT8) == 0x00)
#define GET_DP_MST_RX_REG_UPSTREAM_REPLY_DOWN_REPLY_ADDRESS_EXINT()                             (SCALER32_DP_GET_OFFSET_BIT_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, _BIT8) == 0x00)
#define SET_DP_MST_RX_REG_UPSTREAM_REPLY_DOWN_REPLY_ADDRESS()                                   {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, ~_BIT8, 0x00);}
#define GET_DP_MST_RX_REG_UPSTREAM_REPLY_UP_REQUEST_ADDRESS()                                   (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, _BIT8) == _BIT8)
#define GET_DP_MST_RX_REG_UPSTREAM_REPLY_UP_REQUEST_ADDRESS_EXINT()                             (SCALER32_DP_GET_OFFSET_BIT_EXINT0(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, _BIT8) == _BIT8)
#define SET_DP_MST_RX_REG_UPSTREAM_REPLY_UP_REQUEST_ADDRESS()                                   {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_A0_AUX_RX_MSG_TX_CTRL, ~_BIT8, _BIT8);}
#define GET_DP_MST_RX_REG_UPSTREAM_LAST_SIDEBAND_IS_READ()                                      ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_E8_TX_READ_FLAG, _BIT0))

#if(_HW_DP_AUX_RX_MAC_DPCD_ACCESS_TYPE == _DP_AUX_RX_MAC_DPCD_ACCESS_WAIT_BUSY)
#define SET_DP_MST_RX_REG_UPSTREAM_REPLY_WRITE_PTR_DONE()                                       {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_BC_BUF_CLR, _BIT2);}
#define GET_DP_MST_RX_REG_UPSTREAM_REPLY_WRITE_PTR_DONE()                                       ((bit)(SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_BC_BUF_CLR, _BIT2) == 0x00))
#define SET_DP_MST_RX_REG_UPSTREAM_REPLY_BUF_DATA_DONE()                                        {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_BC_BUF_CLR, _BIT1);}
#define GET_DP_MST_RX_REG_UPSTREAM_REPLY_BUF_DATA_DONE()                                        ((bit)(SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_BC_BUF_CLR, _BIT1) == 0x00))
#endif

//--------------------------------------------------
// Definitions of Up Reply Related Register Macro
//--------------------------------------------------
#define SET_DP_MST_RX_REG_UP_REPLY_MSG_RECEIVE_CRC_IGNORE_ENABLE()                              {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_50_AUX_RX_MSG_RX_CTRL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));}
#define SET_DP_MST_RX_REG_UP_REPLY_WRITE_1000_RST_FSM()                                         {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_50_AUX_RX_MSG_RX_CTRL, ~(_BIT15 | _BIT14), (_BIT15 | _BIT14));}
#define SET_DP_MST_RX_REG_UP_REPLY_WRITE_1000_RST_FLAG()                                        {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_50_AUX_RX_MSG_RX_CTRL, ~_BIT13, _BIT13);}
#define SET_DP_MST_RX_REG_UP_REPLY_WRITE_1000_RST_BUF()                                         {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_50_AUX_RX_MSG_RX_CTRL, ~_BIT11, _BIT11);}
#define SET_DP_MST_RX_REG_UP_REPLY_FORCE_ACK_ADDRESS_UNEXPECT()                                 {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_50_AUX_RX_MSG_RX_CTRL, ~_BIT19, _BIT19);}

#define GET_DP_MST_RX_REG_UP_REPLY_ADDR_WRITTEN()                                               ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_58_MSG_RX_FINISH, _BIT8))
#define CLR_DP_MST_RX_REG_UP_REPLY_ADDR_WRITTEN()                                               {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_58_MSG_RX_FINISH, _BIT8);}

#define SET_DP_MST_RX_REG_UP_REPLY_HEADER0_INFO()                                               {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_60_MSG_RX_BUF_CLR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);}
#define SET_DP_MST_RX_REG_UP_REPLY_HEADER1_INFO()                                               {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_60_MSG_RX_BUF_CLR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);}

#define SET_DP_MST_RX_REG_UP_REPLY_BUF0_BUF1_MSG_RECEIVE_ENABLE()                               {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_50_AUX_RX_MSG_RX_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));}
#define CLR_DP_MST_RX_REG_UP_REPLY_BUF0_BUF1_MSG_RECEIVE_ENABLE()                               {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_50_AUX_RX_MSG_RX_CTRL, ~(_BIT1 | _BIT0), 0x00);}

#define SET_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE()                                    {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_50_AUX_RX_MSG_RX_CTRL, ~_BIT0, _BIT0);}
#define CLR_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE()                                    {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_50_AUX_RX_MSG_RX_CTRL, ~_BIT0, 0x00);}

#define GET_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_FINISH_IRQ_ENABLE()                                 ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_54_MSG_RX_FINISH_IRQ_EN, _BIT0))
#define SET_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_FINISH_IRQ_ENABLE()                                 {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_54_MSG_RX_FINISH_IRQ_EN, ~_BIT0, _BIT0);}
#define CLR_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_FINISH_IRQ_ENABLE()                                 {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_54_MSG_RX_FINISH_IRQ_EN, ~_BIT0, 0x00);}

#define GET_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_FINISH()                                            ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_58_MSG_RX_FINISH, _BIT0))
#define CLR_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_FINISH()                                            {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_58_MSG_RX_FINISH, _BIT0);}
#define GET_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_LENGTH()                                            (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_70_MSG_RX_BUF0_LEN, _REG8TO32_BYTE_0) & 0x7F)

#define GET_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_ERROR()                                             (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_5C_MSG_RX_FLAG, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define CLR_DP_MST_RX_REG_UP_REPLY_BUF0_MSG_ERROR()                                             {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_5C_MSG_RX_FLAG, (_BIT3 | _BIT2 | _BIT1 | _BIT0));}
#define SET_DP_MST_RX_REG_UP_REPLY_BUF0_RDAD_PTR(x)                                             {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_78_MSG_RX_BUF0_RDPTR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x));}
#define GET_DP_MST_RX_REG_UP_REPLY_BUF0_DATA()                                                  (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_7C_MSG_RX_BUF0_RD_DATA, _REG8TO32_BYTE_0))
#define CLR_DP_MST_RX_REG_UP_REPLY_BUF0()                                                       {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_60_MSG_RX_BUF_CLR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));}

#define SET_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_RECEIVE_ENABLE()                                    {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_50_AUX_RX_MSG_RX_CTRL, ~_BIT1, _BIT1);}
#define CLR_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_RECEIVE_ENABLE()                                    {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_50_AUX_RX_MSG_RX_CTRL, ~_BIT1, 0x00);}

#define GET_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_FINISH_IRQ_ENABLE()                                 ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_54_MSG_RX_FINISH_IRQ_EN, _BIT4))
#define SET_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_FINISH_IRQ_ENABLE()                                 {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_54_MSG_RX_FINISH_IRQ_EN, ~_BIT4, _BIT4);}
#define CLR_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_FINISH_IRQ_ENABLE()                                 {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_54_MSG_RX_FINISH_IRQ_EN, ~_BIT4, 0x00);}

#define GET_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_FINISH()                                            ((bit)SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_58_MSG_RX_FINISH, _BIT4))
#define CLR_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_FINISH()                                            {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_58_MSG_RX_FINISH, _BIT4);}

#define GET_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_LENGTH()                                            (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_80_MSG_RX_BUF1_LEN, _REG8TO32_BYTE_0) & 0x7F)
#define GET_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_ERROR()                                             (SCALER32_DP_GET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_5C_MSG_RX_FLAG, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define CLR_DP_MST_RX_REG_UP_REPLY_BUF1_MSG_ERROR()                                             {SCALER32_DP_SET_OFFSET_DWORD(g_ulDpAuxRxBase32AddressOffset, PB18003_5C_MSG_RX_FLAG, (_BIT7 | _BIT6 | _BIT5 | _BIT4));}
#define SET_DP_MST_RX_REG_UP_REPLY_BUF1_RDAD_PTR(x)                                             {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_88_MSG_RX_BUF1_RDPTR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x));}
#define GET_DP_MST_RX_REG_UP_REPLY_BUF1_WRITE_PTR()                                             (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_84_MSG_RX_BUF1_WRPTR, _REG8TO32_BYTE_0) & 0x7F)
#define GET_DP_MST_RX_REG_UP_REPLY_BUF1_DATA()                                                  (SCALER32_DP_GET_OFFSET_BYTE(g_ulDpAuxRxBase32AddressOffset, PB18003_8C_MSG_RX_BUF1_RD_DATA, _REG8TO32_BYTE_0))
#define CLR_DP_MST_RX_REG_UP_REPLY_BUF1()                                                       {SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, PB18003_60_MSG_RX_BUF_CLR, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));}

//--------------------------------------------------
// Definitions of MSG Reset
//--------------------------------------------------
#define SET_DP_MST_RX_REG_MSG_RESET()                                                           {\
                                                                                                    SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, _REG_DP_AUX_RX0_MAC_CTRL, ~_BIT6, _BIT6);\
                                                                                                    SCALER32_DP_SET_OFFSET_BIT(g_ulDpAuxRxBase32AddressOffset, _REG_DP_AUX_RX0_MAC_CTRL, ~_BIT6, 0x00);\
                                                                                                }

//--------------------------------------------------
// Macro of MST Timer Event Structure (for INT Used)
//--------------------------------------------------
#define GET_MST_TIMER_EVENT_VALID(x)                                                            (g_pstDpMstRxTimerEvent[x].enumEventID != _SCALER_TIMER_EVENT_INVALID)
#define CLR_MST_TIMER_EVENT_VALID(x)                                                            (g_pstDpMstRxTimerEvent[x].enumEventID = _SCALER_TIMER_EVENT_INVALID)

#define GET_MST_TIMER_EVENT_ID(x)                                                               (g_pstDpMstRxTimerEvent[x].enumEventID)
#define SET_MST_TIMER_EVENT_ID(x, y)                                                            (g_pstDpMstRxTimerEvent[x].enumEventID = (y))

#define GET_MST_TIMER_EVENT_TIME(x)                                                             (g_pstDpMstRxTimerEvent[x].usTime)
#define SET_MST_TIMER_EVENT_TIME(x, y)                                                          (g_pstDpMstRxTimerEvent[x].usTime = (y))

//--------------------------------------------------
// Definitions of MSG Urgent Event Check Skip
//--------------------------------------------------
#if(_URGENT_EVENT_CHECK_MODE == _ON)
#define GET_DP_MST_RX_URGENT_EVENT_CHECK_SKIP(enumInputPort)                                    (g_pstDpMstRxMsgPortInfo[((enumInputPort) - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1UrgentEventCheckSkip)
#define SET_DP_MST_RX_URGENT_EVENT_CHECK_SKIP(enumInputPort)                                    {g_pstDpMstRxMsgPortInfo[((enumInputPort) - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1UrgentEventCheckSkip = _TRUE;}
#define CLR_DP_MST_RX_URGENT_EVENT_CHECK_SKIP(enumInputPort)                                    {g_pstDpMstRxMsgPortInfo[((enumInputPort) - _D0_INPUT_PORT) % _DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS].b1UrgentEventCheckSkip = _FALSE;}
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Message Type
//--------------------------------------------------
typedef enum
{
    _DP_RX_MST_MODE_STATUS_NONE_MSG = 0x00,
    _DP_RX_MST_MODE_STATUS_BUILD_TOPOLOGY,
    _DP_RX_MST_MODE_STATUS_ALLOCATED_PBN,
} EnumDpMstModeStatus;

//--------------------------------------------------
// Enumerations of Message Type
//--------------------------------------------------
typedef enum
{
    _DP_DOWN_REQUEST_MSG,
    _DP_DOWN_REPLY_MSG,
    _DP_UP_REQUEST_MSG,
    _DP_UP_REPLY_MSG,
} EnumDpMessageType;

//--------------------------------------------------
// Enumerations of Message Type
//--------------------------------------------------
typedef enum
{
    _DP_MSG_GET_MESSAGE_TRANSACTION_VERSION = 0x00,
    _DP_MSG_LINK_ADDRESS = 0x01,
    _DP_MSG_CONNECTION_STATUS_NOTIFY = 0x02,
    _DP_MSG_ENUM_PATH_RESOURCES = 0x10,
    _DP_MSG_ALLOCATE_PAYLOAD = 0x11,
    _DP_MSG_QUERY_PAYLOAD = 0x12,
    _DP_MSG_RESOURCE_STATUS_NOTIFY = 0x13,
    _DP_MSG_CLEAR_PAYLOAD_ID_TABLE = 0x14,
    _DP_MSG_REMOTE_DPCD_READ = 0x20,
    _DP_MSG_REMOTE_DPCD_WRITE = 0x21,
    _DP_MSG_REMOTE_I2C_READ = 0x22,
    _DP_MSG_REMOTE_I2C_WRITE = 0x23,
    _DP_MSG_POWER_UP_PHY = 0x24,
    _DP_MSG_POWER_DOWN_PHY = 0x25,
    _DP_MSG_SINK_EVENT_NOTIFY = 0x30,
    _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS = 0x38,
    _DP_MSG_NONE = 0xFF,
} EnumMessageReuqestID;

//--------------------------------------------------
// Enumerations of Message NAK Reasons
//--------------------------------------------------
typedef enum
{
    _NONE_MSG_ERROR = 0x00,
    _WRITE_FAILURE = 0x01,
    _INVALID_RAD = 0x02,
    _CRC_FAILURE = 0x03,
    _BAD_PARAM = 0x04,
    _DEFER = 0x05,
    _LINK_FAILURE = 0x06,
    _NO_RESOURCES = 0x07,
    _DPCD_FAIL = 0x08,
    _I2C_NAK = 0x09,
    _ALLOCATE_FAIL = 0x0A,
} EnumMessageNakReasons;

//--------------------------------------------------
// Enumerations of DP Rx Event Which Result From Message
//--------------------------------------------------
typedef enum
{
    _DP_RX_NONE_EVENT,
    _DP_RX_DPCD_WRITE_REQUEST,
    _DP_RX_DPCD_READ_REQUEST,
#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
    _DP_RX_VIRTUAL_DPCD_WRITE_REQUEST,
    _DP_RX_VIRTUAL_DPCD_READ_REQUEST,
#endif
    _DP_RX_NATIVE_PORT8_DISPLAY,
    _DP_RX_NATIVE_PORT8_DELETE,
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    _DP_RX_NATIVE_PORT9_DISPLAY,
    _DP_RX_NATIVE_PORT9_DELETE,
#endif
#if(_DP_TX_SUPPORT == _ON)
    _DP_RX_REMOTE_DAISY_TRANSPORT,
    _DP_RX_REMOTE_MST2SST_TRANSPORT,
    _DP_RX_REMOTE_DAISY_DELETE,
    _DP_RX_REMOTE_MST2SST_DELETE,
#endif
    _DP_RX_I2C_READ,
    _DP_RX_I2C_WRITE,
    _DP_RX_QUERY_STREAM_ECRYPTION_STATUS,
} EnumRxEventType;

//--------------------------------------------------
// Enumerations of DP MSG I2C Device ID
//--------------------------------------------------
typedef enum
{
    _DP_MSG_IIC_DEVICE_NONE = 0x00,
    _DP_MSG_IIC_DEVICE_EDID = 0x50,
    _DP_MSG_IIC_DEVICE_EDID_SEGMENT = 0x30,
    _DP_MSG_IIC_DEVICE_DDCCI = 0x37,
} EnumDpMsgI2cDeviceId;

//--------------------------------------------------
// Enumerations of DP Query Msg
//--------------------------------------------------
typedef enum
{
    _DP_STREAM_NOT_EXIST = 0x00,
    _DP_STREAM_NOT_ACTIVE = _BIT0,
    _DP_STREAM_ACTIVE = _BIT1,
} EnumDpQueryEncryptStreamState;

typedef enum
{
    _DP_OUTPUT_SINK_TYPE_NON_AUTHENTICABLE = _BIT0,
    _DP_OUTPUT_SINK_TYPE_MSG_NO_SUPPORT = _BIT1,
    _DP_OUTPUT_SINK_TYPE_MSG_SUPPORT = _BIT2,
} EnumDpQueryEncryptOutputSinkType;

//--------------------------------------------------
// Enumerations of Sink Event ID
//--------------------------------------------------
typedef enum
{
    _SINK_EVENT_NONE = 0x00,
    _SINK_EVENT_ID_PR_CRC_ERROR = _BIT0,
    _SINK_EVENT_ID_PR_RFB_STORAGE_ERROR = _BIT1,
    _SINK_EVENT_ID_DSC_RC_BUF_UNDERRUN = _BIT2,
    _SINK_EVENT_ID_DSC_RC_BUF_OVERFLOW = _BIT3,
    _SINK_EVENT_ID_DSC_CHUNCK_LEN_ERROR = _BIT4,
    _SINK_EVENT_ID_CEC_IRQ = _BIT5,
    _SINK_EVENT_ALL = 0xFF,
} EnumDpMSTSinkEventID;

//--------------------------------------------------
// Enumerations of DP Rx Up Request Queue
//--------------------------------------------------
typedef enum
{
    _RX_UP_REQ_QUEUE_NONE = 0,
    _RX_UP_REQ_QUEUE_PORT8_D0 = (_D0_INPUT_PORT << 4 | _DP_PORT8),
    _RX_UP_REQ_QUEUE_PORT8_D1 = (_D1_INPUT_PORT << 4 | _DP_PORT8),
    _RX_UP_REQ_QUEUE_PORT8_D2 = (_D2_INPUT_PORT << 4 | _DP_PORT8),
#if(_DP_TX_SUPPORT == _ON)
    _RX_UP_REQ_QUEUE_PORT1 = _DP_PORT1,
#endif
} EnumDpMstRxUpReqQueue;

//--------------------------------------------------
// Definitions for DP GET_MESSAGE_TRANSACTION_CRC
//--------------------------------------------------
typedef struct
{
    BYTE b4HeaderCRC : 4;
    BYTE ucBodyCRC;
}StructReqGetMsgCRC;

//--------------------------------------------------
// Enumerations of DP MST Timerevent
//--------------------------------------------------
typedef enum
{
    _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT,
    _SCALER_TIMER_EVENT_DP_UP_REQUEST_PROCESSING,
} EnumDpMstRxTimerEventType;

//--------------------------------------------------
// Enumerations of DP MST Allocate Payload Tx Data Path
//--------------------------------------------------
typedef enum
{
    _DP_RX_MSG_ALLOCATE_PAYLOAD_DAISY_PATH = 0x00,
    _DP_RX_MSG_ALLOCATE_PAYLOAD_MST2SST_PATH = 0x01,
} EnumDpRxMsgAllocatePayloadTxDataPath;

//--------------------------------------------------
// Enumerations of DP MST Allocate Payload Rx Data Path
//--------------------------------------------------
typedef enum
{
    _DP_RX_MSG_ALLOCATE_PAYLOAD_PORT8_PATH = 0x00,
    _DP_RX_MSG_ALLOCATE_PAYLOAD_PORT9_PATH = 0x01,
} EnumDpRxMsgAllocatePayloadRxDataPath;

//--------------------------------------------------
// Definitions for DP GET_MESSAGE_TRANSACTION_VERSION REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
}StructReqGetMsgVer;

//--------------------------------------------------
// Definitions for DP LINK ADDRESS  REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
}StructReqLinkAddress;

//--------------------------------------------------
// Definitions of DP ALLOCATE PAYLOAD REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4NumOfSDPStreams : 4;
    BYTE b4PortNum : 4;
    BYTE b7PayloadID : 7;
    BYTE b1Zero1 : 1;
    BYTE pucPBN[2];
    BYTE pucRemainPart[8];
}StructReqAllocatePayload;

//--------------------------------------------------
// Definitions of DP CLEAR PAYLOAD ID TABLE REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
}StructReqClearPayloadIDTable;

//--------------------------------------------------
// Definitions of DP ENUM PATH RESOURCE REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
}StructReqEnumPathResource;

//--------------------------------------------------
// Definitions of DP CONNECTION STATUS NOTIFY REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    EnumDpMstPort b4PortNum : 4;
    BYTE pucGUID[16];
    BYTE b3PeerDeviceType : 3;
    BYTE b1InputPort : 1;
    BYTE b1MsgCabability : 1;
    BYTE b1DpPlugStatus : 1;
    BYTE b1LegacyPlugStatus : 1;
    BYTE b1Zero2 : 1;
}StructReqConnectionStatusNotify;

//--------------------------------------------------
// Definitions of DP SINK EVENT NOTIFY REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    EnumDpMstPort b4PortNum : 4;
    BYTE pucGUID[16];
    BYTE pucEventID[2];
} StructReqSinkEventNotify;

//--------------------------------------------------
// Definitions of DP POWER DOWN PHY REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
}StructReqPowerDownPHY;

//--------------------------------------------------
// Definitions of DP POWER UP PHY REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
}StructReqPowerUpPHY;

//--------------------------------------------------
// Definitions of DP QUERY PAYLOAD REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    EnumDpMstPort b4PortNum : 4;
    BYTE b7PayloadID : 7;
    BYTE b1Zero2 : 1;
}StructReqQueryPayload;

//--------------------------------------------------
// Definitions of DP REMOTE DPCD READ REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4DpcdAddressH : 4;
    BYTE b4PortNum : 4;
    BYTE ucDpcdAddressM;
    BYTE ucDpcdAddressL;
    BYTE ucNumOfRead;
}StructReqRemoteDpcdRead;

//--------------------------------------------------
// Definitions of DP REMOTE DPCD WRITE REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4DpcdAddressH : 4;
    BYTE b4PortNum : 4;
    BYTE ucDpcdAddressM;
    BYTE ucDpcdAddressL;
    BYTE ucNumOfByteToWrite;
    BYTE pucDpcdByteToWrite[16];
}StructReqRemoteDpcdWrite;

//--------------------------------------------------
// Definitions of DP REMOTE I2C READ REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b2NumOfI2CWriteTran : 2;
    BYTE b2Zero1 : 2;
    BYTE b4PortNum : 4;
    BYTE pucRemainPart[46];
}StructReqRemoteI2CRead;

//--------------------------------------------------
// Definitions of DP REMOTE I2C WRITE REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
    EnumDpMsgI2cDeviceId b7WriteI2CDeviceID : 7;
    BYTE b1Zero2 : 1;
    BYTE ucNumOfByteToWrite;
    BYTE pucI2CDateToWrite[44];
}StructReqRemoteI2CWrite;

//--------------------------------------------------
// Definitions of DP RESOURCE STATUS NOTIFY REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
    BYTE pucGUID[16];
    BYTE pucAvailablePBN[2];
}StructReqResourceStatusNotify;

//--------------------------------------------------
// Definitions of DP QUERY STREAM ENCRYPTION STATUS REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE ucStreamID;
    BYTE pucClientID[7];
    BYTE b2Zero : 2;
    BYTE b1StreamBehaviorMask : 1;
    BYTE b2StreamBehavior : 2;
    BYTE b1StreamEventMask : 1;
    BYTE b2StreamEvent : 2;
}StructReqQueryStreamEncryptionStatus;

//--------------------------------------------------
// Definitions for DP GET_MESSAGE_TRANSACTION_VERSION REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE ucMsgVersion;
}StructRepGetMsgVer;

//--------------------------------------------------
// Definitions for DP LINK ADDRESS Port Info
//--------------------------------------------------
typedef struct
{
    EnumDpMstPort b4PortNum : 4;
    BYTE b3PeerDeviceType : 3;
    BYTE b1InputPort : 1;
    BYTE b5Zero : 5;
    BYTE b1LegacyPlugStatus : 1;
    BYTE b1DpPlugStatus : 1;
    BYTE b1MsgCapability : 1;
    BYTE ucDpcdRevision;
    BYTE pucPeerGuid[16];
    BYTE b4NumSDPStreamSink : 4;
    BYTE b4NumSDPStreams : 4;
} StructLinkAddressPortInfo;

//--------------------------------------------------
// Definitions for DP LINK ADDRESS REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE pucGuid[16];
    BYTE b4NumOfPort : 4;
    BYTE b4Zero : 4;
    EnumDpMstPort b4Port0Num : 4;
    BYTE b3PeerDeviceType0 : 3;

    BYTE b1InputPort0 : 1;
    BYTE b6Zero1 : 6;
    BYTE b1DpPlugStatus0 : 1;
    BYTE b1MsgCapability0 : 1;

    StructLinkAddressPortInfo pstPortInfo[_DP_MST_RX_LOGICAL_PORT_NUM + _DP_MST_RX_NUM_OF_OUTPUT_PORTS];
}StructRepLinkAddress;

//--------------------------------------------------
// Definitions for DP ALLOCATE PAYLOAD REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4Zero : 4;
    EnumDpMstPort b4PortNum : 4;
    BYTE b7PayloadID : 7;
    BYTE b1Zero1 : 1;
    BYTE pucAllocatePBN[2];
}StructRepAllocatePayload;

//--------------------------------------------------
// Definitions for DP CLEAR PAYLOAD ID TABLE REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
}StructRepClearPayloadIDTable;

//--------------------------------------------------
// Definitions for DP ENUM PATH RESOURCE REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b1FecCap : 1;
    BYTE b3Zero : 3;
    EnumDpMstPort b4PortNum : 4;
    BYTE pucFullPBN[2];
    BYTE pucAvailablePBN[2];
}StructRepEnumPathResource;

//--------------------------------------------------
// Definitions for DP CONNECTION STATUS NOTIFY REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
}StructRepConnectionStatusNotify;

//--------------------------------------------------
// Definitions for DP POWER DOWN PHY REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4Zero : 4;
    BYTE b4PortNum : 4;
}StructRepPowerDownPHY;

//--------------------------------------------------
// Definitions for DP POWER UP PHY REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4Zero : 4;
    BYTE b4PortNum : 4;
}StructRepPowerUpPHY;

//--------------------------------------------------
// Definitions for DP QUERY PAYLOAD REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4Zero : 4;
    BYTE b4PortNum : 4;
    BYTE pucAllocatePBN[2];
}StructRepQueryPayload;

//--------------------------------------------------
// Definitions for DP REMOTE DPCD READ REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4PortNum : 4;
    BYTE b4Zero : 4;
    BYTE ucNumOfRead;
    BYTE pucDpcdRead[32];
}StructRepRemoteDpcdRead;

//--------------------------------------------------
// Definitions for DP REMOTE DPCD WRITE REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4PortNum : 4;
    BYTE b4Zero : 4;
}StructRepRemoteDpcdWrite;

//--------------------------------------------------
// Definitions for DP REMOTE I2C READ REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4PortNum : 4;
    BYTE b4Zero : 4;
    BYTE ucNumOfRead;
    BYTE pucI2CRead[256];
}StructRepRemoteI2CRead;

//--------------------------------------------------
// Definitions for DP REMOTE I2C WRITE REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4PortNum : 4;
    BYTE b4Zero : 4;
}StructRepRemoteI2CWrite;

//--------------------------------------------------
// Definitions for DP RESOURCE STATUS NOTIFY REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
}StructRepResourceStatusNotify;

//--------------------------------------------------
// Definitions for DP SINK EVENT NOTIFY REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
}StructRepSinkEventNotify;

//--------------------------------------------------
// Definitions for DP NAK REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE pucGuid[16];
    BYTE ucNakReason;
    BYTE ucNakData;
}StructRepNak;

//--------------------------------------------------
// Definitions for DP REMOTE I2C READ NAK REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE pucGuid[16];
    BYTE b4zero : 4;
    BYTE b4Port : 4;
    BYTE ucNakReason;
    BYTE b2I2CNakTransaction : 2;
    BYTE b6zero1 : 6;
}StructRepRemoteI2CReadNak;

//--------------------------------------------------
// Definitions for DP QUERY STREAM ENCRYPTION STATUS MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b3Zero : 3;
    BYTE b1StreamAuthentication : 1;
    BYTE b1StreamEncryption : 1;
    BYTE b1StreamRepeaterFunction : 1;
    BYTE b2StreamState : 2;
    BYTE b1Signed : 1;
    BYTE b2Zero : 2;
    BYTE b2StreamOuputCpType : 2;
    BYTE b3StreamOuputSinkType : 3;
    BYTE ucStreamID;
    BYTE pucSignatureL[32];
}StructRepQueryStreamEncryptionStatus;

//--------------------------------------------------
// Struct for Pool Usage Info
//--------------------------------------------------
typedef struct
{
    BYTE b1ReqArray : 1;
    BYTE b1ReplyArray : 1;
    EnumInputPort enumDpMstRxRequestMsgPort;
    EnumInputPort enumDpMstRxReplyMsgPort;
}StructPoolUsageInfo;

//--------------------------------------------------
// Struct for Message Function Action Info
//--------------------------------------------------
typedef struct
{
    BYTE b1DownRequestAnal : 1;
    BYTE b1DownReplyReady : 1;
    BYTE b1DownReplyBypass : 1;
    BYTE b1DownReplyDirect : 1;
    BYTE b1UpRequestReady : 1;
    BYTE b1UpRequestAnal : 1;
    BYTE b1UpReplyAnal : 1;
    BYTE b1UpReplyDirect : 1;
    BYTE ucGenDownRequestMsg;
    BYTE b1SelfGenDownRequest : 1;
#if(_DP_TX_SUPPORT == _ON)
    BYTE b1WaitRemoteLinkAddressReply : 1;
#endif
}StructRxMsgFunctionInfo;

//--------------------------------------------------
// Struct for Other Message Info
//--------------------------------------------------
typedef struct
{
    BYTE ucRetryNum;
    EnumMessageReuqestID enumGenUpRequestID;
    EnumDpMSTSinkEventID enumSinkEventID;
    BYTE b1IllegalDownRequestMSG : 1;
    BYTE b1IllegalUpRequestMSG : 1;
    BYTE b1RemoteI2CReadFail : 1;
}StructRxMsgOtherInfo;

//--------------------------------------------------
// Struct for Other Message Info
//--------------------------------------------------
typedef struct
{
#if(_DP_MST_RX_DOWN_REPLY_MANUAL_MODE_SUPPORT == _ON)
    BYTE ucDownReplyManualMsgCount;
    BYTE ucDownReplyManualMsgLength;
    BYTE ucDownReplyManualMsgBodyLengthMax;
#endif
    BYTE ucUpRequestRetryNum;
    BYTE ucDownReplyRetryNum;
    EnumMessageReuqestID enumIssuedUpRequestID;
    EnumDpMstRxUpReqQueue enumUpReqIntiatedQueue;
    BYTE b1DpUpRequestProcessing : 1;
    BYTE b1ReplyBufFree : 1;
    BYTE b1CancelMsgTimeoutEvent : 1;
    BYTE b1UpRequestBypassDone : 1;
    BYTE b1DownRequestBufPriority : 1;
    BYTE b1UpReplyBufPriority : 1;
    BYTE b1DpMstRxMacDownReplyHPD : 1;

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    BYTE b1UrgentEventCheckSkip : 1;
#endif
} StructRxMsgPortInfo;

//--------------------------------------------------
// Struct for MSG port
//--------------------------------------------------
typedef struct
{
    EnumInputPort enumDpMstRxDownRequestMsgInputPort;
    EnumInputPort enumDpMstRxUpReplyMsgInputPort;
    EnumInputPort enumDpMstRxDownReplyMsgTargetPort;
    EnumInputPort enumDpMstRxUpRequestMsgTargetPort;
} StructDpMstRxMsgPort;

#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Enum of Virtual DPCD Entries
//--------------------------------------------------
typedef enum
{
    _VIRTUAL_DPCD_00005H,

    _VIRTUAL_DPCD_00007H,
    _VIRTUAL_DPCD_00008H,
    _VIRTUAL_DPCD_00009H,

    _VIRTUAL_DPCD_00021H,

    _VIRTUAL_DPCD_00030H,
    _VIRTUAL_DPCD_0003FH = _VIRTUAL_DPCD_00030H + 0x0F,

    _VIRTUAL_DPCD_00060H,
    _VIRTUAL_DPCD_0006FH = _VIRTUAL_DPCD_00060H + 0x0F,

    _VIRTUAL_DPCD_00080H,
    _VIRTUAL_DPCD_00083H = _VIRTUAL_DPCD_00080H + 0x03,

    _VIRTUAL_DPCD_000A0H,
    _VIRTUAL_DPCD_000A2H = _VIRTUAL_DPCD_000A0H + 0x02,

    _VIRTUAL_DPCD_00107H,

    _VIRTUAL_DPCD_00160H,
    _VIRTUAL_DPCD_00161H,

    _VIRTUAL_DPCD_00200H,
    _VIRTUAL_DPCD_02002H = _VIRTUAL_DPCD_00200H,

    _VIRTUAL_DPCD_0020FH,
    _VIRTUAL_DPCD_02011H = _VIRTUAL_DPCD_0020FH,

    _VIRTUAL_DPCD_00240H,
    _VIRTUAL_DPCD_00245H = _VIRTUAL_DPCD_00240H + 0x05,

    _VIRTUAL_DPCD_03050H,
    _VIRTUAL_DPCD_03059H = _VIRTUAL_DPCD_03050H + 0x09,

    _VIRTUAL_DPCD_ENTRY_NONE,
    _VIRTUAL_DPCD_ENTRY_NUM = _VIRTUAL_DPCD_ENTRY_NONE,

    // -----------------------------------------------
    // Special cases below, which are not using xdata
    // -----------------------------------------------
    _VIRTUAL_DPCD_0004XH_GUID_2,
} EnumVirtualDpcdEntry;

//--------------------------------------------------
// Struct for Virtual Dp
//--------------------------------------------------
typedef struct
{
    BYTE b1VirtualDpEnable : 1;
    BYTE pucVirtualDpcd[_VIRTUAL_DPCD_ENTRY_NUM];
    EnumDpMSTSinkEventID enumSinkEventID;
} StructVirtualDp;

//--------------------------------------------------
// Struct for Mst Muti-function
//--------------------------------------------------
typedef struct
{
    StructVirtualDp pstLogicPort8[_DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS];

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    StructVirtualDp pstLogicPort9[_DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS];
#endif

#if(_DP_TX_SUPPORT == _ON)
    StructVirtualDp pstPhyPort[_DP_MST_RX_NUM_OF_OUTPUT_PORTS];
#endif
} StructMstMutiFunction;
#endif // End of #if(_DP_MST_MULTI_FUNCTION_SUPPORT== _ON)

//****************************************************************************
// Union
//****************************************************************************
//--------------------------------------------------
// Unior for All Request Message Info
//--------------------------------------------------
typedef union
{
    BYTE pucData[_DP_MST_RX_REQUEST_MSG_BYTE_WISE_MAX_LEN];
    StructReqGetMsgVer stGetMsgVer;
    StructReqLinkAddress stLinkAddress;
    StructReqAllocatePayload stAllocatePayload;
    StructReqClearPayloadIDTable stClearPayloadID;
    StructReqEnumPathResource stEnumPathResource;
    StructReqConnectionStatusNotify stConnectionStatusNotify;
    StructReqPowerDownPHY stPowerDownPHY;
    StructReqPowerUpPHY stPowerUpPHY;
    StructReqQueryPayload stQueryPayload;
    StructReqRemoteDpcdRead stRemoteDpcdRead;
    StructReqRemoteDpcdWrite stRemoteDpcdWrite;
    StructReqRemoteI2CRead stRemoteI2CRead;
    StructReqRemoteI2CWrite stRemoteI2CWrite;
    StructReqResourceStatusNotify stStructReqResourceStatusNotify;
    StructReqSinkEventNotify stStructReqSinkEventNotify;
    StructReqQueryStreamEncryptionStatus stStructReqQueryStreamEncryptionStatus;
}UnionDpMacRxReqStrct;

//--------------------------------------------------
// Unior for All Reply Message Info
//--------------------------------------------------
typedef union
{
    BYTE pucData[_DP_MST_RX_REPLY_MSG_BYTE_WISE_MAX_LEN];
    StructRepGetMsgVer stGetMsgVer;
    StructRepLinkAddress stLinkAddress;
    StructRepAllocatePayload stAllocatePayload;
    StructRepClearPayloadIDTable stClearPayloadID;
    StructRepEnumPathResource stEnumPathResource;
    StructRepConnectionStatusNotify stConnectionStatusNotify;
    StructRepPowerUpPHY stPowerDownPHY;
    StructRepPowerUpPHY stPowerUpPHY;
    StructRepQueryPayload stQueryPayload;
    StructRepRemoteDpcdRead stRemoteDpcdRead;
    StructRepRemoteDpcdWrite stRemoteDpcdWrite;
    StructRepRemoteI2CRead stRemoteI2CRead;
    StructRepRemoteI2CWrite stRemoteI2CWrite;
    StructRepResourceStatusNotify stResourceStatusNotify;
    StructRepSinkEventNotify stSinkEventNotify;
    StructRepRemoteI2CReadNak stRemoteI2CReadNak;
    StructRepNak stStructRepNak;
    StructRepQueryStreamEncryptionStatus stStructRepQueryStreamEncryptionStatus;
}UnionDpMacRxRepStrct;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile EnumDpMstModeStatus g_penumDpMstRxModeStatus[_DP_MAC_DPHY_RX_NUM_OF_INPUT_PORTS];
extern volatile BYTE g_ucDpMstRxEvent;
extern volatile StructPoolUsageInfo g_stDpMstRxPoolUsage;
extern volatile bit g_bDpMstRxMacReplyBufFree;
extern volatile bit g_bDpMstRxCancelMsgTimeoutEvent;

extern volatile StructRxMsgFunctionInfo g_stDpMstRxMsgFunction;
extern volatile StructRxMsgOtherInfo g_stDpMstRxMsgOtherInfo;
extern volatile StructRxMsgPortInfo g_pstDpMstRxMsgPortInfo[];
extern UnionDpMacRxReqStrct g_unDpMstRxRequestPool;
extern UnionDpMacRxRepStrct g_unDpMstRxReplyPool;
extern EnumDpMstPort g_enumDpMstRxDownRequestPortNum;
extern StructDpMstRxMsgPort g_stDpMstRxMsgPort;

#if(_DP_TX_SUPPORT == _ON)
extern volatile BYTE g_ucDpMstRxTotalReceivedMsgCount;
#endif

extern BYTE g_pucDpMstRxMsgQueryEncryptClientId[7];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// General
extern void ScalerDpMstRxResetStream_EXINT0(EnumInputPort enumInputPort);

extern void ScalerDpMstRxIntHandle_EXINT0(EnumInputPort enumInputPort);
extern EnumDpVersionType ScalerDpMstRxGetDpVersion(EnumInputPort enumInputPort);
extern void ScalerDpMstRxPowerProc(EnumPowerAction enumPowerAction);
extern bit ScalerDpMstRxFakePowerSavingCheck(EnumInputPort enumInputPort);

// DPRX MSG
extern void ScalerDpMstRxDownRequestBufferRelease(EnumInputPort enumInputPort);
extern bit ScalerDpMstRxCheckMsgTransition(EnumInputPort enumInputPort);
extern void ScalerDpMstRxMsgCountResetEvent(void);
extern void ScalerDpMstRxMsgTimeoutEvent(EnumInputPort enumInputPort);
extern void ScalerDpMstRxIllegalMsgReply(void);
extern bit ScalerDpMstRxCheckMsgBufferFree(EnumInputPort enumInputPort);
extern EnumScalerTimerEventID ScalerDpMstRxGetTimerEvent(EnumInputPort enumInputPort, EnumDpMstRxTimerEventType enumEventType);
extern EnumScalerTimerEventID ScalerDpMstRxGetTimerEvent_EXINT0(EnumInputPort enumInputPort, EnumDpMstRxTimerEventType enumEventType);
extern void ScalerDpMstRxSetMsgReadyIrqEnable(EnumInputPort enumInputPort, EnumDpMessageType enumDpMessageType, bit bEnable);
extern void ScalerDpMstRxSetMsgReadyIrqEnable_EXINT0(EnumInputPort enumInputPort, EnumDpMessageType enumDpMessageType, bit bEnable);
extern void ScalerDpMstRxMsgJudgeAllocatePayloadRxEvent(EnumDpRxMsgAllocatePayloadRxDataPath enumRxDataPath);
extern bit ScalerDpMstRxDownReplyProc(void);
extern bit ScalerDpMstRxActiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
extern bit ScalerDpMstRxReactiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
extern void ScalerDpMstRxCancelTimerEvent(EnumScalerTimerEventID enumEventID);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpMstRxMsgJudgeAllocatePayloadTxEvent(EnumDpRxMsgAllocatePayloadTxDataPath enumTxDataPath);
extern EnumDpRxMsgAllocatePayloadTxDataPath ScalerDpMstRxMsgJudgeTxDataPath(void);
extern bit ScalerDpMstRxReactiveSearchTimeCheck(EnumInputPort enumInputPort);
#endif

#if((_DP_TX_SUPPORT == _ON) || (_DP_MST_MULTI_FUNCTION_SUPPORT == _ON))
extern bit ScalerDpMstRxUpRequestAllowedCheck(EnumInputPort enumInputPort);
#endif

// DPRX MST STREAM
extern EnumDpStreamNum ScalerDpMstRxGetSourceMuxBackup(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumDpStreamSourceNum);
extern EnumDpStreamNum ScalerDpMstRxSearchMatchStream(EnumInputPort enumInputPort, BYTE ucTargetID);
extern bit ScalerDpMstRxCheckIDExisted(EnumInputPort enumInputPort, BYTE ucPayloadID);

extern void ScalerDpMstRxMainPortSwitchProc(EnumInputPort enumInputPort);
extern WORD ScalerDpMstRxGetMaxPBN(EnumInputPort enumInputPort);
extern WORD ScalerDpMstRxGetAvailablePBN(EnumInputPort enumInputPort);
extern BYTE ScalerDpMstRxGetAvailableTimeslot(EnumInputPort enumInputPort);

// HDCP
#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpMstRxQueryEncryptionWriteShaInput(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerDpMstRxQueryEncryptionWriteSha256Input(bit bRepeater);
#endif
#endif
extern BYTE ScalerDpMstRxPortNumMappingIndex(EnumInputPort enumInputPort, EnumDpMstPort enumMstPortNum);
extern bit ScalerDpMstRxValidLogicalPortJudge(EnumDpMstPort enumMstPort);

// Multi function
#if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)
extern void ScalerDpMstRxMultiFunctionInitial(EnumInputPort enumInputPort);
extern void ScalerDpMstRxVirtualDpInitial(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort);
extern bit ScalerDpMstRxGetMultiFuncEnableStatus(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort);
extern void ScalerDpMstRxVirtualDpcdInitial(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort);
extern bit ScalerDpMstRxGetVirtualDpEnable(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort);
extern void ScalerDpMstRxSetVirtualDpEnable(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, bit bEn);
extern BYTE ScalerDpMstRxGetVirtualDpcdInfo(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL);
extern BYTE ScalerDpMstRxGetVirtualDpcdBitInfo(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL, BYTE ucDpcdBit);
extern void ScalerDpMstRxSetVirtualDpcdInfo(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL, BYTE ucValue);
extern void ScalerDpMstRxSetVirtualDpcdBitInfo(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL, DWORD ulNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpMstRxSetVirtualDpcdInfoBySrc(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, BYTE ucDpcdAddrH, BYTE ucDpcdAddrM, BYTE ucDpcdAddrL, BYTE ucValue);
extern void ScalerDpMstRxSetVirtualDpSinkEventNotify(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort, EnumDpMSTSinkEventID enumSinkEventID);

extern void ScalerDpMstRxDscVirtualDpcdSetting(EnumInputPort enumInputPort, EnumDpMstPort enumMstPort);
extern void ScalerDpMstRxDscSupportSwitch(EnumInputPort enumInputPort);

#endif // End of #if(_DP_MST_MULTI_FUNCTION_SUPPORT == _ON)

extern BYTE ScalerDpMstRxGetRegDownRequestRad(EnumInputPort enumInputPort, BYTE ucRadIndex);
extern void ScalerDpMstRxSetRegUpstreamReplyRad(EnumInputPort enumInputPort, BYTE ucRadIndex, BYTE ucValue);

#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))

#if((_DP_SUPPORT == _ON) && ((_DP_MST_SUPPORT == _ON) || (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)))
extern void ScalerDpMstRxResetStreamToIdMapping(EnumInputPort enumInputPort);
extern void ScalerDpMstRxSetStreamStartBackup(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, BYTE ucValue);
extern void ScalerDpMstRxSetStreamEndBackup(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, BYTE ucValue);
extern void ScalerDpMstRxSetStreamStatusBackup(EnumInputPort enumInputPort, EnumDpStreamNum enumDpStreamNum, bit bEnable);
extern void ScalerDpMstRxResetSourceMuxBackup(EnumInputPort enumInputPort);
extern void ScalerDpMstRxResetStreamStartBackup(EnumInputPort enumInputPort);
extern void ScalerDpMstRxResetStreamEndBackup(EnumInputPort enumInputPort);
extern void ScalerDpMstRxResetStreamStatusBackup(EnumInputPort enumInputPort);
extern void ScalerDpMstRxResetActSignalCodingType(EnumInputPort enumInputPort);
extern EnumDpMstPort ScalerDpMstRxDxPortNumMapping(EnumInputPort enumInputPort);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpMstRxSetTxStreamSourceMux(void);
extern void ScalerDpMstRxResetTxStreamSourceMux(EnumInputPort enumInputPort);
#endif

#if(_DP_MST_SUPPORT == _ON)
extern EnumInputPort ScalerDpMstRxPortNumDxMapping(EnumDpMstPort enumDpMstPort);
extern EnumInputPort ScalerDpMstRxInputPortJudge(EnumInputPort enumInputPort, EnumDpMstPort enumDpMstPort);
#endif
#endif

#if((_DP_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern void ScalerDpMstRxInitialSetting(void);
#endif
