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
// ID Code      : UserCommonUsbTypeCRtsInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_TYPE_C_RTS_SMBUS_CMD_TYPE(x)                    (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].enumUsbTypeCRtsInfoType)
#define SET_TYPE_C_RTS_SMBUS_CMD_TYPE(x, y)                 (g_pstUsbTypeCRtsInfo[SysUsbGetTypeCIndex(x)].enumUsbTypeCRtsInfoType = (y))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of RTS Port Controller Info
//--------------------------------------------------
typedef enum
{
    _TYPE_C_GET_RTS_INFO_CC_ATTACH = 0x00,
    _TYPE_C_GET_RTS_INFO_ALT_MODE_READY = 0x01,
    _TYPE_C_GET_RTS_INFO_ORIENTATION = 0x02,
    _TYPE_C_GET_RTS_INFO_DATA_ROLE = 0x03,
    _TYPE_C_GET_RTS_INFO_PIN_ASSIGNMENT = 0x04,
    _TYPE_C_GET_RTS_INFO_FW_VERSION = 0x05,
    _TYPE_C_GET_RTS_INFO_CONNECT_FUJITSU = 0x06,
    _TYPE_C_GET_RTS_INFO_LENOVO_ALT_MODE_STATUS = 0x07,
    _TYPE_C_GET_RTS_INFO_LENOVO_DEVICE_TYPE = 0x08,
    _TYPE_C_GET_RTS_INFO_LENOVO_SYSTEM_EVENT = 0x09,
    _TYPE_C_SET_RTS_INFO_SRC_PDO = 0x0A,
    _TYPE_C_SET_RTS_INFO_SNK_PDO = 0x0B,
    _TYPE_C_SET_RTS_INFO_RDO = 0x0C,
    _TYPE_C_SET_RTS_INFO_CC_DISCONNECT = 0x0D,
    _TYPE_C_SET_RTS_INFO_POWER_MODE = 0x0E,
    _TYPE_C_GET_RTS_INFO_NONE = 0xFF
}EnumUsbTypeCRtsInfoType;

typedef struct
{
    EnumTypeCDataRole enumDataRole;
    EnumTypeCPowerRole enumPowerRole;
    EnumUsbTypeCRtsInfoType enumUsbTypeCRtsInfoType;
    StructTypeCCableInfoForDpcd stCableInfo;
    BYTE ucPortPartnerFlag;
    BYTE ucI2CWrExtendInfo;
#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
    StructTypeCUserPDO pstSrcPdo[_RTS_MAX_DATA_OBJ_CNT];
    StructTypeCUserPDO pstPartnerSrcPdo[_RTS_MAX_DATA_OBJ_CNT];
    StructTypeCUserPDO pstSnkPdo[_RTS_MAX_DATA_OBJ_CNT];
    StructTypeCUserRDO stTargetRdo;
    WORD usPdoStatusVoltage;
    WORD usPdoStatusCurrent;
    WORD usMaxPower;  // Unit = 0.1W
    BYTE ucReqInfo0;
    BYTE ucReqInfo1;
    BYTE ucReqInfo2;
    BYTE b3PortOpMode : 3;
    BYTE b3NumOfSPRSrcCap : 3;
    BYTE b1PowerContract : 1;
    BYTE b1SuspendSupport : 1;
    // -----------------------------
    BYTE b1DualRolePower : 1;
    BYTE b1DualRoleData : 1;
    BYTE b1ExtPower : 1;
    BYTE b3NumOfPartnerSPRSrcCap : 3;
    BYTE b1UsbCapable : 1;
    BYTE b1UnchkSupport : 1;
    // -----------------------------
    BYTE b4ReqObjPos : 4;
    BYTE b3NumOfEPRSrcCap : 3;
    BYTE b3NumOfSPRSnkCap : 3;
    BYTE b3NumOfEPRSnkCap : 3;
    BYTE b3NumOfPartnerEPRSrcCap : 3;
#endif
#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    BYTE ucLenovoDockingEvent;
    BYTE b1DetectLenovoAltModeFlag : 1;
    BYTE b1DetectLenovoDeviceTypeFlag : 1;
    BYTE b1LenovoVdmReceived : 1;
#endif
    BYTE b1DetectStatusFlag : 1;
    BYTE b1I2CEnabledFlag : 1;
}StructTypeCRtsInfo;

typedef struct
{
    BYTE b1DetectCcAttachFlag : 1;
    BYTE b1DetectAltModeFlag : 1;
}StructPortCtrlDetectInfo;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucOffset1;
    BYTE ucOffset2;
    BYTE ucReportDataLength;
} StructSMBusWRGetICStatus;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucFWMainVer;
    BYTE ucFWSubVer1;
    BYTE ucFWSubVer2;
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucPDTypeCStatus;
    BYTE ucByte9;
    BYTE ucByte10;
    BYTE ucByte11;
    BYTE ucByte12;
    BYTE ucSMBusReadyStatus;
    BYTE ucByte14;
    BYTE ucByte15;
    BYTE ucByte16;
    BYTE ucByte17;
    BYTE ucByte18;
    BYTE ucByte19;
} StructSMBusRDGetICStatus;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
    BYTE ucDPCapVDOByte0;
    BYTE ucDPCapVDOByte1;
    BYTE ucDPCapVDOByte2;
    BYTE ucDPCapVDOByte3;
} StructSMBusWRSetDPLanes;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
} StructSMBusWRReadDPLanes;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucPortNum;
    BYTE ucDPCapVDOByte0;
    BYTE ucDPCapVDOByte1;
    BYTE ucDPCapVDOByte2;
} StructSMBusRDReadDPLanes;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucDPCfgVDOByte0;
    BYTE ucDPCfgPinConfig;
    BYTE ucDPCfgVDOByte2;
    BYTE ucDPCfgVDOByte3;
} StructSMBusRDReadDPLanesCfg;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
    BYTE ucDPCapVDOByte0;
    BYTE ucDPCapVDOByte1;
    BYTE ucDPCapVDOByte2;
    BYTE ucDPCapVDOByte3;
} StructSMBusWRSetDPMultiFunction;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
} StructSMBusWRReadDPMultiFunction;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucDPStatusVDOByte0;
    BYTE ucDPStatusVDOByte1;
    BYTE ucDPStatusVDOByte2;
    BYTE ucDPStatusVDOByte3;
} StructSMBusRDReadDPMultiFunction;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucPortNum;
    BYTE ucByte2;
} StructSMBusWRReconnect;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
} StructSMBusWRDisconnect;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucPortNum;
    BYTE ucByte2;
} StructSMBusWROperation;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucNotifyEnByte0;
    BYTE ucNotifyEnByte1;
    BYTE ucNotifyEnByte2;
    BYTE ucNotifyEnByte3;
} StructSMBusWRNotifyEn;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucOffset;
    BYTE ucPortNum;
    BYTE ucStatusLen;
} StructSMBusWRGetStatus;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucByte3;                   // [1] VDM Received
    BYTE ucByte4;                   // [6] Power Role (SRC:1 / SNK:0)
    BYTE ucByte5_PortPartnerFlag;   // Port Partner Flag (BIT0 : USB / BIT1 : Alt Mode)
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucByte8;
    BYTE ucByte9;
    BYTE ucByte10_DFP_UFP;
    BYTE ucByte11_Orientation;      // [5] Plug Direction
    BYTE ucByte12;
    BYTE ucByte13_AltModeStatus;    // [7] Fujitsu / Lenovo Alt Mode Ready, [2:0] DP Alt Mode Ready
} StructSMBusRDGetStatus;

#if(_TYPE_C_PORT_CTRL_RTS_PDO_INFO_SUPPORT == _ON)
typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucByte3;
    BYTE ucByte4;
    BYTE ucByte5;
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucByte8;
    BYTE ucByte9;
    BYTE ucByte10;
    BYTE ucByte11;
    BYTE ucByte12;
    BYTE ucByte13;
    BYTE ucByte14;
    BYTE ucByte15;
    BYTE ucByte16;
    BYTE ucByte17;
    BYTE ucByte18;
    BYTE ucByte19;
    BYTE ucByte20;
    BYTE ucByte21;
    BYTE ucByte22;
    BYTE ucByte23;
    BYTE ucByte24;
    BYTE ucByte25;
    BYTE ucByte26;
    BYTE ucByte27;
    BYTE ucByte28;
    BYTE ucByte29;
    BYTE ucByte30;
} StructSMBusWRSetPDO;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucByte3;
    BYTE ucByte4;
    BYTE ucByte5;
} StructSMBusWRSetRDO;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucPdodata;
} StructSMBusWRGetPdo;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucByte3;
    BYTE ucByte4;
    BYTE ucByte5;
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucByte8;
    BYTE ucByte9;
    BYTE ucByte10;
    BYTE ucByte11;
    BYTE ucByte12;
    BYTE ucByte13;
    BYTE ucByte14;
    BYTE ucByte15;
    BYTE ucByte16;
    BYTE ucByte17;
    BYTE ucByte18;
    BYTE ucByte19;
    BYTE ucByte20;
    BYTE ucByte21;
    BYTE ucByte22;
    BYTE ucByte23;
    BYTE ucByte24;
    BYTE ucByte25;
    BYTE ucByte26;
    BYTE ucByte27;
} StructSMBusRDGetPdo;
#endif

typedef struct
{
    BYTE ucCommandStatus;
    BYTE ucDataLength;
} StructSMBusRDCommandReadyStatus;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
} StructSMBusWRGetLenovoInfo;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0_DeviceType;
    BYTE ucByte1_SystemState;
} StructSMBusRDGetLenovoInfo;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
} StructSMBusWRGetLenovoVdm;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucVdmHeader0;
    BYTE ucVdmHeader1;
    BYTE ucVdmHeader2;
    BYTE ucVdmHeader3;
    BYTE ucByte5;
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucByte8;
    BYTE ucByte9;
    BYTE ucByte10;
    BYTE ucByte11;
    BYTE ucByte12;
} StructSMBusRDGetLenovoVdm;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVdmHeader0;
    BYTE ucVdmHeader1;
    BYTE ucVdmHeader2;
    BYTE ucVdmHeader3;
    BYTE ucByte4;
    BYTE ucByte5;
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucByte8;
    BYTE ucByte9;
    BYTE ucByte10;
    BYTE ucByte11;
} StructSMBusWRSendLenovoVdmAck;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVdmHeader0;
    BYTE ucVdmHeader1;
    BYTE ucVdmHeader2;
    BYTE ucVdmHeader3;
} StructSMBusWRSendLenovoVdmReq;
#endif

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucRsvByte;
    BYTE ucPortNum;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucByte3;
    BYTE ucByte4;
} StructSMBusWRAckCCCI;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTypeCRtsInfo g_pstUsbTypeCRtsInfo[_TYPE_C_PORT_VALID];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_PORT_CTRL_RTS_DET_CC_ATTACH_BY_SMBUS == _ON)
extern EnumTypeCAttachStatus UserCommonUsbTypeCRtsGetCcAttachByI2C(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_PORT_CTRL_RTS_DET_ALT_MODE_READY_BY_SMBUS == _ON)
extern EnumTypeCAltModeStatus UserCommonUsbTypeCRtsGetAltModeReadyByI2C(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

extern bit UserCommonUsbTypeCRtsConfigPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgCapType enumPinAssignment);
extern bit UserCommonUsbTypeCRtsConfigMultiFunction(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCMultiFuncStatus enumMultiFunction);
#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))
