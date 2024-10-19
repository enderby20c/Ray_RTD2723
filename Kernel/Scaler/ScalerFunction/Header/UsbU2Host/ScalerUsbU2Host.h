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
// ID Code      : ScalerUsbU2Host.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_USB_U2HOST_H__
#define __SCALER_USB_U2HOST_H__

#if(_USB2_HOST_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
#define _U2HOST_DEVICE_ADDRESS_START                            2   // Address for first attached device

// Support only 1 device at the same time which the index is set 0
#define _U2HOST_DEVICE_ATTACH_INDEX                             0
#define _U2HOST_DEVICE_NUM                                      1

//----------------------------------------------------------------------------------------------------
// USB2.0 Enumuration Info.
//----------------------------------------------------------------------------------------------------
// bDescriptorType
#define _U2HOST_ENUM_DES_TYPE_DEVICE                            0x01
#define _U2HOST_ENUM_DES_TYPE_CONFIG                            0x02
#define _U2HOST_ENUM_DES_TYPE_INTF                              0x04
#define _U2HOST_ENUM_DES_TYPE_ENDPT                             0x05
#define _U2HOST_ENUM_DES_TYPE_INTF_ASOC                         0x0B
#define _U2HOST_ENUM_DES_TYPE_HID                               0x21

// Descriptor Len (wLength)
#define _U2HOST_ENUM_DES_LEN_DEVICE                             0x12
#define _U2HOST_ENUM_DES_LEN_CONFIG                             0x09
#define _U2HOST_ENUM_DES_LEN_INTF                               0x09
#define _U2HOST_ENUM_DES_LEN_ENDPT                              0x07
#define _U2HOST_ENUM_DES_LEN_INTF_ASOC                          0x08
#define _U2HOST_ENUM_DES_LEN_HID                                0x09
#define _U2HOST_ENUM_SET_LINE_CODE                              0x07
#define _U2HOST_ENUM_GET_LINE_CODE                              0x07

#if(_USB2_HOST_EHCI_SUPPORT == _ON)
#if(_U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _ON)
// DB dump data, U2Host Transfer Length Each Time (Unit KB)
#define _U2HOST_DB_XFER_LEN_ONCE_BULK_DATA                      20 // KB
#else
// DB dump data,U2Host Transfer Length Each Time (Unit KBYTE)
#define _U2HOST_DB_XFER_MAX_LENGTH_ONCE                         20// 16 // 20
#endif

// #define _U2HOST_DB_DOUBLE_CHECK_TEST_DEBUG
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)

/*
//----------------------------------------------------------------------------------------------------
// Bit definition for Hub Port Status Field
//----------------------------------------------------------------------------------------------------
#define _U2HOST_HUB_CHG_DET                                     0x01
#define _U2HOST_HUB_P1_CHG_DET                                  0x02
#define _U2HOST_HUB_P2_CHG_DET                                  0x04
#define _U2HOST_HUB_P3_CHG_DET                                  0x08
#define _U2HOST_HUB_P4_CHG_DET                                  0x10
#define _U2HOST_HUB_P5_CHG_DET                                  0x20
#define _U2HOST_HUB_P6_CHG_DET                                  0x40
#define _U2HOST_HUB_P7_CHG_DET                                  0x80

#define _U2HOST_HUB_PORT_CONNECT                                0x0001
#define _U2HOST_HUB_PORT_ENABLE                                 0x0002
#define _U2HOST_HUB_PORT_SUSPEND                                0x0004
#define _U2HOST_HUB_PORT_OVER_CURRENT                           0x0008
#define _U2HOST_HUB_PORT_RESET                                  0x0010
#define _U2HOST_HUB_PORT_POWER                                  0x0100
#define _U2HOST_HUB_PORT_LOW_SPEED                              0x0200
#define _U2HOST_HUB_PORT_HIGH_SPEED                             0x0400
#define _U2HOST_HUB_PORT_TEST                                   0x0800
#define _U2HOST_HUB_PORT_INDICATOR                              0x1000

#define _U2HOST_HUB_PORT_CONNECT_CHANGE                         0x01
#define _U2HOST_HUB_PORT_ENABLE_CHANGE                          0x02
#define _U2HOST_HUB_PORT_SUSPEND_CHANGE                         0x04
#define _U2HOST_HUB_PORT_OVER_CURRENT_CHANGE                    0x08
#define _U2HOST_HUB_PORT_RESET_CHANGE                           0x10
*/

// COMMUNICATION STATE + ENUM STATE + BULK TRANS STATE + INT TRANS STATE
#define GET_U2HOST_SECOND_PROC_STATUS()                         (g_stUsbU2HostFlowCtrlFlag.b1SecondProcStatus)
#define SET_U2HOST_SECOND_PROC_STATUS()                         (g_stUsbU2HostFlowCtrlFlag.b1SecondProcStatus = 1)
#define CLR_U2HOST_SECOND_PROC_STATUS()                         (g_stUsbU2HostFlowCtrlFlag.b1SecondProcStatus = 0)

#define GET_U2HOST_DEVICE_BULK_IN_ENDPOINT_SIZE(x)              (g_pusUsbU2HostBulkInEndpSize[x])
#define SET_U2HOST_DEVICE_BULK_IN_ENDPOINT_SIZE(x, y)           (g_pusUsbU2HostBulkInEndpSize[x] = (y))

#define GET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_SIZE(x)             (g_pusUsbU2HostBulkOutEndpSize[x])
#define SET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_SIZE(x, y)          (g_pusUsbU2HostBulkOutEndpSize[x] = (y))

#define GET_U2HOST_DEVICE_BULK_IN_ENDPOINT_ADDR(x)              (g_pucUsbU2HostBulkInEndpAddr[x])
#define SET_U2HOST_DEVICE_BULK_IN_ENDPOINT_ADDR(x, y)           (g_pucUsbU2HostBulkInEndpAddr[x] = (y))

#define GET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_ADDR(x)             (g_pucUsbU2HostBulkOutEndpAddr[x])
#define SET_U2HOST_DEVICE_BULK_OUT_ENDPOINT_ADDR(x, y)          (g_pucUsbU2HostBulkOutEndpAddr[x] = (y))

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
#define GET_U2HOST_SEC_REPORT_DESC()                            (g_stUsbU2HostFlowCtrlFlag.b1GetSecReportDes)
#define SET_U2HOST_SEC_REPORT_DESC()                            (g_stUsbU2HostFlowCtrlFlag.b1GetSecReportDes = _TRUE)
#define CLR_U2HOST_SEC_REPORT_DESC()                            (g_stUsbU2HostFlowCtrlFlag.b1GetSecReportDes = _FALSE)

#define GET_U2HOST_OHCI_INT_TRAN_ACTIVE()                       (g_stUsbU2HostFlowCtrlFlag.b1IntProcessActive)
#define SET_U2HOST_OHCI_INT_TRAN_ACTIVE()                       (g_stUsbU2HostFlowCtrlFlag.b1IntProcessActive = _TRUE)
#define CLR_U2HOST_OHCI_INT_TRAN_ACTIVE()                       (g_stUsbU2HostFlowCtrlFlag.b1IntProcessActive = _FALSE)

#define GET_U2HOST_OHCI_1ST_INTERFACE_TYPE()                    (g_ucUsbU2HostOhci1stInterfaceType)
#define SET_U2HOST_OHCI_1ST_INTERFACE_TYPE(x)                   (g_ucUsbU2HostOhci1stInterfaceType = (x))

#define GET_U2HOST_OHCI_2ND_INTERFACE_TYPE()                    (g_ucUsbU2HostOhci2ndInterfaceType)
#define SET_U2HOST_OHCI_2ND_INTERFACE_TYPE(x)                   (g_ucUsbU2HostOhci2ndInterfaceType = (x))
#endif

#define GET_U2HOST_DEVICE_ACTIVE(x)                             (g_pstUsbU2HostDeviceInfo[x].b1DeviceActive)
#define SET_U2HOST_DEVICE_ACTIVE(x)                             (g_pstUsbU2HostDeviceInfo[x].b1DeviceActive = _TRUE)
#define CLR_U2HOST_DEVICE_ACTIVE(x)                             (g_pstUsbU2HostDeviceInfo[x].b1DeviceActive = _FALSE)

#define GET_U2HOST_DEVICE_ADDRESS(x)                            (g_pstUsbU2HostDeviceInfo[x].b3DeviceAddr)
#define SET_U2HOST_DEVICE_ADDRESS(x, y)                         (g_pstUsbU2HostDeviceInfo[x].b3DeviceAddr = (y))

#define GET_U2HOST_DEVICE_SPEED(x)                              (g_pstUsbU2HostDeviceInfo[x].b2DeviceSpd)
#define SET_U2HOST_DEVICE_SPEED(x, y)                           (g_pstUsbU2HostDeviceInfo[x].b2DeviceSpd = (y))

#define GET_U2HOST_DEVICE_TYPE(x)                               (g_pstUsbU2HostDeviceInfo[x].b3DeviceTyp)
#define SET_U2HOST_DEVICE_TYPE(x, y)                            (g_pstUsbU2HostDeviceInfo[x].b3DeviceTyp = (y))

#define GET_U2HOST_DEVICE_INT_DATA_SIZE(x)                      (g_pstUsbU2HostEndptDesInfo[x].usMaxPacketSize)
#define SET_U2HOST_DEVICE_INT_DATA_SIZE(x, y)                   (g_pstUsbU2HostEndptDesInfo[x].usMaxPacketSize = (y))

#define GET_U2HOST_CTS_EN_STATUS()                              (g_stUsbU2HostCTSFlowCtrlFlag.b1CTSStatus)
#define SET_U2HOST_CTS_EN_STATUS()                              (g_stUsbU2HostCTSFlowCtrlFlag.b1CTSStatus = _TRUE)
#define CLR_U2HOST_CTS_EN_STATUS()                              (g_stUsbU2HostCTSFlowCtrlFlag.b1CTSStatus = _FALSE)

#define GET_U2HOST_CTS_MODE_STATUS()                            (g_stUsbU2HostCTSFlowCtrlFlag.b3CTSMode)
#define SET_U2HOST_CTS_MODE_STATUS(y)                           (g_stUsbU2HostCTSFlowCtrlFlag.b3CTSMode = (y))
#endif // End of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)

#if(_USB2_HOST_EHCI_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Memory Allocation for EHCI
//----------------------------------------------------------------------------------------------------
#define _U2HOST_EHCI_CTRL_QH_NUM                                1
#define _U2HOST_EHCI_CTRL_QTD_NUM                               3
#define _U2HOST_EHCI_CTRL_BUFFER_NUM                            1

#define _U2HOST_EHCI_BULK_IN_QH_NUM                             1
#define _U2HOST_EHCI_BULK_OUT_QH_NUM                            1

#define _U2HOST_EHCI_BULK_QH_NUM                                (_U2HOST_EHCI_BULK_IN_QH_NUM + _U2HOST_EHCI_BULK_OUT_QH_NUM)

#define _U2HOST_EHCI_BULK_IN_QTD_NUM                            2
#define _U2HOST_EHCI_BULK_OUT_QTD_NUM                           2

#define _U2HOST_EHCI_QH_TOTAL_NUM                               (_U2HOST_EHCI_CTRL_QH_NUM + _U2HOST_EHCI_BULK_IN_QH_NUM + _U2HOST_EHCI_BULK_OUT_QH_NUM)
#define _U2HOST_EHCI_QTD_TOTAL_NUM                              (_U2HOST_EHCI_CTRL_QTD_NUM + _U2HOST_EHCI_BULK_IN_QTD_NUM + _U2HOST_EHCI_BULK_OUT_QTD_NUM)
#define _U2HOST_EHCI_MEMORY_SIZE                                ((_U2HOST_EHCI_QH_TOTAL_NUM * _U2HOST_EHCI_QH_SIZE) + (_U2HOST_EHCI_QTD_TOTAL_NUM * _U2HOST_EHCI_QTD_SIZE) + (_U2HOST_EHCI_CTRL_BUFFER_NUM * _U2HOST_CTRL_EHCI_BUFFER_SIZE) + (_U2HOST_BULK_CSW_EHCI_BUFFER_SIZE + _U2HOST_BULK_DATA_EHCI_BUFFER_SIZE))

#define _U2HOST_EHCI_BULK_WRITE_FROM_DM_CLIENT_ST_ADDR          0x00

WORD code tUSB_EHCI_CTRL_QH_ADDR_TABLE[] =
{
    _U2HOST_EHCI_CTRL_QH_ST_ADDR,

};

WORD code tUSB_EHCI_CTRL_QTD_ADDR_TABLE[] =
{
    _U2HOST_EHCI_CTRL_QTD_0_ST_ADDR,
    _U2HOST_EHCI_CTRL_QTD_1_ST_ADDR,
    _U2HOST_EHCI_CTRL_QTD_2_ST_ADDR,
};

WORD code tUSB_EHCI_BULK_IN_QH_ADDR_TABLE[] =
{
    _U2HOST_EHCI_BULK_IN_QH_ST_ADDR,
};

WORD code tUSB_EHCI_BULK_IN_QTD_ADDR_TABLE[] =
{
    _U2HOST_EHCI_BULK_IN_QTD_0_ST_ADDR,
    _U2HOST_EHCI_BULK_IN_QTD_1_ST_ADDR,
};

WORD code tUSB_EHCI_BULK_OUT_QH_ADDR_TABLE[] =
{
    _U2HOST_EHCI_BULK_OUT_QH_ST_ADDR,
};

WORD code tUSB_EHCI_BULK_OUT_QTD_ADDR_TABLE[] =
{
    _U2HOST_EHCI_BULK_OUT_QTD_0_ST_ADDR,
    _U2HOST_EHCI_BULK_OUT_QTD_1_ST_ADDR,
};
#endif

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
WORD code tUSB_OHCI_CTRL_ED_ADDR_TABLE[] =
{
    _U2HOST_OHCI_CTRL_ED_0_ST_ADDR,
};

WORD code tUSB_OHCI_CTRL_TD_ADDR_TABLE[] =
{
    _U2HOST_OHCI_CTRL_TD_0_ST_ADDR,
    _U2HOST_OHCI_CTRL_TD_1_ST_ADDR,
    _U2HOST_OHCI_CTRL_TD_2_ST_ADDR,
};

WORD code tUSB_OHCI_INT_ED_ADDR_TABLE[] =
{
    _U2HOST_OHCI_INT_ED_0_ST_ADDR,
    _U2HOST_OHCI_INT_ED_1_ST_ADDR,
};

WORD code tUSB_OHCI_INT_TD_ADDR_TABLE[] =
{
    _U2HOST_OHCI_INT_TD_0_ST_ADDR,
    _U2HOST_OHCI_INT_TD_1_ST_ADDR,
};

WORD code tUSB_OHCI_INT_BUFFER_ADDR_TABLE[] =
{
    _U2HOST_OHCI_INT0_BUFFER_ST_ADDR,
    _U2HOST_OHCI_INT1_BUFFER_ST_ADDR,
};

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
WORD code tUSB_OHCI_BULK_IN_ED_ADDR_TABLE[] =
{
    _U2HOST_OHCI_BULK_IN_ED_0_ST_ADDR,
};

WORD code tUSB_OHCI_BULK_IN_TD_ADDR_TABLE[] =
{
    _U2HOST_OHCI_BULK_IN_TD_0_ST_ADDR,
    _U2HOST_OHCI_BULK_IN_TD_1_ST_ADDR,
};

WORD code tUSB_OHCI_BULK_OUT_ED_ADDR_TABLE[] =
{
    _U2HOST_OHCI_BULK_OUT_ED_0_ST_ADDR,
};

WORD code tUSB_OHCI_BULK_OUT_TD_ADDR_TABLE[] =
{
    _U2HOST_OHCI_BULK_OUT_TD_0_ST_ADDR,
    _U2HOST_OHCI_BULK_OUT_TD_1_ST_ADDR,
};

WORD code tUSB_OHCI_BULK_OUT_BUFFER_ADDR_TABLE[] =
{
    _U2HOST_OHCI_BULK_OUT_BUFFER_ST_ADDR,
};

WORD code tUSB_OHCI_BULK_IN_BUFFER_ADDR_TABLE[] =
{
    _U2HOST_OHCI_BULK_IN_BUFFER_ST_ADDR,
};
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
typedef enum
{
    _U2HOST_DEVICE_NONE = 0x00,
    _U2HOST_DEVICE_MASS_STORAGE = 0x01,
    _U2HOST_DEVICE_HID = 0x02,
    _U2HOST_DEVICE_HID_XRITE = 0x03,
    _U2HOST_DEVICE_CDC_CA410 = 0x04,
} EnumUsbDeviceType;

typedef struct
{
    BYTE b3DeviceTyp : 3;
    BYTE b3DeviceAddr : 3;
    BYTE b2DeviceSpd : 2;   // 00:Full / 01:Low / 10:High / 11:other
    BYTE b1DeviceActive : 1;
} StructUsbDeviceInfo;

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    WORD usTotalLength;
    BYTE ucNumInterface;
    BYTE ucConfigValue;
    BYTE ucAttributes;
}StructUsbConfigDesInfo;

typedef struct
{
    BYTE ucFirstInterface;
    BYTE ucInterfaceCnt;
    BYTE ucFuncClass;
    BYTE ucFuncSubClass;
    BYTE ucFuncProtocol;
}StructUsbIntfAsocDesInfo;

typedef struct
{
    BYTE ucInterfaceNum;
    BYTE ucNumEndpoint;
    BYTE ucInterfaceClass;
    BYTE ucInterfaceSubClass;
    BYTE ucInterfaceProtocol;
}StructUsbIntfDesInfo;

typedef struct
{
    BYTE ucEndpointAddress;
    BYTE ucAttributes;
    WORD usMaxPacketSize;
    BYTE ucInterval;
}StructUsbEndptDesInfo;

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
typedef struct
{
    BYTE ucDescripType1;
    WORD usBcdHID;
    BYTE ucCountryCode;
    BYTE ucNumDescriptor;
    BYTE ucDescripType2;
    WORD usHIDReportLength;
    BYTE pucHIDReport[_U2HOST_CTRL_OHCI_BUFFER_SIZE];
} StructUsbHIDDesInfo;

typedef struct
{
    DWORD ulDTERate;
    BYTE ucCharFormat;
    BYTE ucParityType;
    BYTE ucDataBits;
}StructUsbU2HostLineCodeInfo;

typedef struct
{
    // BYTE b1IntQHActive : 1;

    BYTE ucDataLength;
    BYTE pucData[_U2HOST_INT_OHCI_BUFFER_SIZE];
} StructUsbIntEDInfo;
#endif

typedef struct
{
    BYTE ucMaxLun;
    // BYTE ucDeviceClass;
    // BYTE ucDeviceSubClass;
    // WORD usLanguageID;
}StructUsbStorageDeviceInfoTable;

typedef enum
{
    _U2HOST_OHCI_INTERFACE_NONE = 0x00,
    _U2HOST_OHCI_INTERFACE_KEYBOARD = 0x01,
    _U2HOST_OHCI_INTERFACE_MOUSE = 0x02,
    _U2HOST_OHCI_INTERFACE_CDC_CTRL = 0x03,
    _U2HOST_OHCI_INTERFACE_CDC_DATA = 0x04,
} EnumUsbU2HostOHCIInterfaceType;

typedef enum
{
    _U2HOST_CTS_MODE_NONE = 0x00,
    _U2HOST_CTS_MODE_TEST,
    _U2HOST_CTS_MODE_ENUM,
    _U2HOST_CTS_MODE_SIGN_GET_DEV_DESC,
    _U2HOST_CTS_MODE_SUSPEND,
    _U2HOST_CTS_MODE_RESUME,
} EnumUsbU2HostCTSMode;

typedef struct
{
    BYTE b1CTSStatus : 1;
    BYTE b3CTSMode : 3;
} StructUsbU2HostCTSFlowCtrlFlag;
#endif // End of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
extern void ScalerUsbU2HostClearHaltFeature(EnumUsbU2HostOwner enumOwner);
extern void ScalerUsbU2HostMacReset(void);
extern void ScalerUsbU2HostConnectCheck(EnumUsbU2HostOwner enumMode);

extern void ScalerUsbU2HostCtsTestModeContol(void);
extern void ScalerUsbU2HostCtsModeJudge(void);


extern void ScalerUsbU2HostGetDeviceDesInfo(BYTE *pucData);
extern void ScalerUsbU2HostGetConfigDesInfo(BYTE *pucData);
extern void ScalerUsbU2HostGetIntfAsocDesInfo(BYTE *pucData);
extern void ScalerUsbU2HostGetIntfDesInfo(BYTE ucIntfIdx, BYTE *pucData);
extern void ScalerUsbU2HostGetEndptDesInfo(BYTE ucEndptIdx, BYTE *pucData);

#if(_USB2_HOST_EHCI_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
#if(_U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _OFF)
extern void ScalerUsbU2HostClrDMAddrErrFlag(void);
extern void ScalerUsbU2HostDMClientInitial(void);
#else
extern void ScalerUsbU2HostDMClientDoubleChkInitial(void);
extern void ScalerUsbU2HostGetCurDMOnlyCrcEnResult(void);
extern void ScalerUsbU2HostDMClientDoubleChkUpdate(void);
#endif
extern bit g_bUsbU2HostFirstUpdateFlag;
#endif

extern void ScalerUsbU2HostAddBulkReadQH(void);
extern void ScalerUsbU2HostAddBulkWriteQH(void);
extern void ScalerUsbU2HostBulkScsiInquiryOutQh(void);
extern void ScalerUsbU2HostBulkScsiInquiryInQh(void);

extern void ScalerUsbU2HostBulkScsiReadFormatCapOutQh(void);
extern void ScalerUsbU2HostBulkScsiReadFormatCapInQh(void);
extern void ScalerUsbU2HostBulkScsiReqSenseOutQh(void);
extern void ScalerUsbU2HostBulkScsiReqSenseInQh(void);

extern void ScalerUsbU2HostBulkScsiReadCapacity10OutQh(void);
extern void ScalerUsbU2HostBulkScsiReadCapacity10InQh(void);
extern void ScalerUsbU2HostBulkScsiModeSense6OutQh(void);
extern void ScalerUsbU2HostBulkScsiModeSense6InQh(void);
extern void ScalerUsbU2HostBulkScsiTestUnitReadyOutQh(void);
extern void ScalerUsbU2HostBulkScsiTestUnitReadyInQh(void);
extern void ScalerUsbU2HostBulkScsiRead10MBROutQh(void);
extern void ScalerUsbU2HostBulkScsiRead10MBRInQh(void);
extern void ScalerUsbU2HostBulkScsiRead10GPTOutQh(void);
extern void ScalerUsbU2HostBulkScsiRead10GPTInQh(void);
extern void ScalerUsbU2HostBulkScsiRead10DBROutQh(void);
extern void ScalerUsbU2HostBulkScsiRead10DBRInQh(void);

extern void ScalerUsbU2HostBulkScsiRead10NTFSInQh(void);
extern void ScalerUsbU2HostBulkScsiRead10NTFSOutQh(void);

extern void ScalerUsbU2HostBulkScsiRead10RootDirClusNumOutQh(void);
extern void ScalerUsbU2HostBulkScsiRead10RootDirClusNumInQh(void);
extern void ScalerUsbU2HostBulkScsiRead10RootDirDataOutQh(void);
extern void ScalerUsbU2HostBulkScsiRead10RootDirDataInQh(void);
extern void ScalerUsbU2HostBulkScsiRead10FileClusNumOutQh(void);
extern void ScalerUsbU2HostBulkScsiRead10FileClusNumInQh(void);
extern void ScalerUsbU2HostBulkScsiRead10FileDataOutQh(void);
extern void ScalerUsbU2HostBulkScsiRead10FileDataInQh(void);
extern void ScalerUsbU2HostBulkScsiWrite10DataOutQh(EnumUsbU2HostDDRReadyState enumUsbU2HostDDRReadyState);
extern void ScalerUsbU2HostBulkScsiWrite10DataInQh(void);
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)

extern void ScalerUsbU2HostConnectHandler(EnumUsbU2HostOwner enumMode);
extern void ScalerUsbU2HostCurOwerInitDeviceAddr(void);
extern void ScalerUsbU2HostAddCtrlQH(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostSetAddress(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostGetDeviceDescriptor(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostGetOtherDescriptor(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostGetLanguageID(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostGetManufactureName(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostGetProductName(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostGetSerialNumber(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostGetMaxLun(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostSetConfiguration(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostGetConfigDescriptor(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
extern void ScalerUsbU2HostSetIdle(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostGetHIDReport(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostGetHIDDesInfo(BYTE ucHidIdx, BYTE *pucData);
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
extern void ScalerUsbU2HostGetLineCoding(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostGetLineCodeInfo(BYTE *pucData);
extern void ScalerUsbU2HostSetLineCoding(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostSetControlLineState(EnumUsbU2HostOwner enumOwner, BYTE ucDeviceNo);
extern void ScalerUsbU2HostAddBulkED(void);
extern void ScalerUsbU2HostAddIntED(void);
extern void ScalerUsbU2HostUserControlOut(BYTE ucDeviceNo);
extern void ScalerUsbU2HostUserControlIn(BYTE ucDeviceNo);
extern void ScalerUsbU2HostUserBulkOut(void);
extern void ScalerUsbU2HostUserBulkIn(void);
extern void ScalerUsbU2HostUserIntOut(void);
extern void ScalerUsbU2HostUserIntIn(void);
#endif
#endif // End of #if(_USB2_HOST_OHCI_SUPPORT == _ON)
#endif // End of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)

extern void ScalerUsbU2HostCurOwerInitHostController(EnumUsbU2HostOwner enumOwner);
extern void ScalerUsbU2HostCurOwerInitSchedule(EnumUsbU2HostOwner enumOwner);

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
extern WORD ScalerUsbU2HostGetOHCIHcCmdStsRegAddr(void);
#endif
extern void ScalerUsbU2HostSetPhyRegAddr(WORD usAddr);
extern void ScalerUsbU2HostSetPhyRegPage(WORD usAddr);
extern BYTE ScalerUsbU2HostGetPhyRegByte(WORD usAddr);
extern void ScalerUsbU2HostSetPhyRegByte(WORD usAddr, BYTE ucValue);
extern BYTE ScalerUsbU2HostGetPhyRegBitField(WORD usAddr, BYTE ucAnd);
extern BYTE ScalerUsbU2HostGetDataPortByte(WORD usAddr);
extern void ScalerUsbU2HostSetDataPortByte(WORD usAddr, BYTE ucValue);
extern void ScalerUsbU2HostSetBufferField(WORD usAddr, DWORD ulByteField, BYTE *pucData);
extern WORD ScalerUsbU2HostGetBufferField(WORD usAddr, DWORD ulByteField);

extern bit ScalerUsbU2HostWaitRegRdy(void);
#endif


#endif // End of #ifndef __SCALER_USB_U2HOST_H__
