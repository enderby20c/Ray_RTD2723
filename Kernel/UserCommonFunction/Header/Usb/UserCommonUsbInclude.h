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
// ID Code      : UserCommonUsbInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_USB_SUPPORT == _ON) || (_TYPE_C_PORT_CTRL_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if((_USB_RTS_SMBUS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON))
typedef enum
{
    _SMBUS_CMD_STATUS_NOTPROCEED = 0x00,
    _SMBUS_CMD_STATUS_COMPLETE = 0x01,
    _SMBUS_CMD_STATUS_DEFER = 0x02,
    _SMBUS_CMD_STATUS_ERROR = 0x03,
} EnumSMBusCmdStatus;

typedef union
{
#if(_PORT_CTRL_RTS_SUPPORT == _ON)
    StructSMBusWRGetICStatus stWrGetICStatus;
    StructSMBusWRSetDPMultiFunction stWrSetDPMultiFunction;
    StructSMBusWRReadDPMultiFunction stWrReadDPMultiFunction;
    StructSMBusWRSetDPLanes stWrSetDPLanes;
    StructSMBusWRReadDPLanes stWrReadDPLanes;
    StructSMBusWRGetStatus stWRGetStatus;
    StructSMBusWRReconnect stWrReconnect;
    StructSMBusWRDisconnect stWrDisconnect;
    StructSMBusWROperation stWrOperation;
#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
    StructSMBusWRSetPDO stWrSetSrcPdo;
    StructSMBusWRSetPDO stWrSetSnkPdo;
    StructSMBusWRSetRDO stWrSetRdo;
    StructSMBusWRGetPdo stWrGetPdo;
#endif

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    StructSMBusWRGetLenovoInfo stWrGetLenovoInfo;
    StructSMBusWRGetLenovoVdm stWrGetLenovoVdm;
    StructSMBusWRSendLenovoVdmAck stWrSendLenovoVdmAck;
    StructSMBusWRSendLenovoVdmReq stWrSendLenovoVdmReq;
#endif
    StructSMBusWRAckCCCI stWrAckCCCI;
#endif

#if((_USB_HUB_RTS_SUPPORT == _ON) && (_USB_HUB_COMMUNICATION_SUPPORT == _ON))
    StructSMBusWrSetSSMode stWrSetSSMode;
    StructSMBusWRDetectDSPSSMode stWrSetDetectDspSSMode;
#endif
} UnionSMBusWRCommandStrct;

typedef union
{
#if(_PORT_CTRL_RTS_SUPPORT == _ON)
    StructSMBusRDCommandReadyStatus stRdCommandReadyStatus;
    StructSMBusRDGetICStatus stRdGetICStatus;
    StructSMBusRDReadDPMultiFunction stRdDPMultiFunction;
    StructSMBusRDReadDPLanes stRdDPlanes;
    StructSMBusRDReadDPLanesCfg stRdDPlanesCfg;
    StructSMBusRDReadDPLanesCfg stRdDpCap;
    StructSMBusRDGetStatus stRdGetStatus;
#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
    StructSMBusRDGetPdo stRdGetPdo;
#endif

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    StructSMBusRDGetLenovoInfo stRdGetLenovoInfo;
    StructSMBusRDGetLenovoVdm stRdGetLenovoVdm;
#endif
#endif

#if((_USB_HUB_RTS_SUPPORT == _ON) && (_USB_HUB_COMMUNICATION_SUPPORT == _ON))
    StructSMBusRDDetectDSPSSMode stRdDetectDspSSMode;
#endif
} UnionSMBusRDCommandStrct;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern UnionSMBusRDCommandStrct g_unUsbSMBusRdDataPool;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#endif  // End of #if(_USB_RTS_SMBUS_SUPPORT == _ON)
#endif // End of #if((_USB_SUPPORT == _ON) || (_TYPE_C_PORT_CTRL_SUPPORT == _ON))

