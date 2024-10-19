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
// ID Code      : ScalerUsbU2HostInterface.h
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_USB2_HOST_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_FREE_RTOS)
#define _U2HOST_DEV_ATTACH_COUNT                                2   // Temp Value, KCPU is 1, SCPU is 5 Actually
#elif(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
#define _U2HOST_DEV_ATTACH_COUNT                                1   // Only 1 Device at a time for KCPU application
#endif

// FW Solution For DM Dump data use. (Solve 1039 issue - HW will miss or multi transmit 60Byte)
#define _U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE               _OFF // _OFF represent New Mode(ECO Solution)

#define _U2HOST_MEMORY_ST_ADDR                                  0x00000000

//----------------------------------------------------------------------------------------------------
// Memory Allocation for OHCI
//----------------------------------------------------------------------------------------------------
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
#define _U2HOST_CTRL_OHCI_BUFFER_SIZE                           256
#define _U2HOST_INT_OHCI_BUFFER_SIZE                            64 // 32
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#define _U2HOST_BULK_OHCI_BUFFER_SIZE                           512 // 32
#endif
#define _U2HOST_CTRL_OHCI_SETUP_CMD_SIZE                        8

#define _U2HOST_MEMORY_OHCI_ST_ADDR_OFFSET                      0x00000010
#define _U2HOST_OHCI_HCCA_MEMORY_ADDR                           0x00000700   // HCCA Memory Address = 1792 Bytes
#define _U2HOST_OHCI_HCCA_MEMORY_SIZE                           0x00000100   // HCCA Memory Size = 256 Bytes

#define _U2HOST_OHCI_CTRL_ED_NUM                                1
#define _U2HOST_OHCI_CTRL_TD_NUM                                3
#define _U2HOST_OHCI_CTRL_BUFFER_NUM                            1

#define _U2HOST_OHCI_INT_ED_NUM                                 2
#define _U2HOST_OHCI_INT_TD_NUM                                 _U2HOST_OHCI_INT_ED_NUM
#define _U2HOST_OHCI_INT_BUFFER_NUM                             _U2HOST_OHCI_INT_TD_NUM

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#define _U2HOST_OHCI_BULK_IN_ED_NUM                             1
#define _U2HOST_OHCI_BULK_IN_TD_NUM                             1
#define _U2HOST_OHCI_BULK_IN_BUFFER_NUM                         1

#define _U2HOST_OHCI_BULK_OUT_ED_NUM                            1
#define _U2HOST_OHCI_BULK_OUT_TD_NUM                            1
#define _U2HOST_OHCI_BULK_OUT_BUFFER_NUM                        1

#define _U2HOST_OHCI_BULK_ED_NUM                                (_U2HOST_OHCI_BULK_IN_ED_NUM + _U2HOST_OHCI_BULK_OUT_ED_NUM)
#define _U2HOST_OHCI_BULK_TD_NUM                                (_U2HOST_OHCI_BULK_IN_TD_NUM + _U2HOST_OHCI_BULK_OUT_TD_NUM)
#define _U2HOST_OHCI_BULK_BUFFER_NUM                            (_U2HOST_OHCI_BULK_IN_BUFFER_NUM + _U2HOST_OHCI_BULK_OUT_BUFFER_NUM)
#endif

#define _U2HOST_OHCI_ED_SIZE                                    16
#define _U2HOST_OHCI_TD_SIZE                                    16

#define _U2HOST_OHCI_SETUP_CMD_SIZE                             16 // 8 is enough,+8 is for address format

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#define _U2HOST_OHCI_ED_TOTAL_NUM                               (_U2HOST_OHCI_CTRL_ED_NUM + _U2HOST_OHCI_INT_ED_NUM + _U2HOST_OHCI_BULK_ED_NUM)
#define _U2HOST_OHCI_TD_TOTAL_NUM                               (_U2HOST_OHCI_CTRL_TD_NUM + _U2HOST_OHCI_INT_TD_NUM + _U2HOST_OHCI_BULK_TD_NUM)
#define _U2HOST_OHCI_MEMORY_SIZE                                (_U2HOST_OHCI_SETUP_CMD_SIZE + (_U2HOST_OHCI_ED_TOTAL_NUM * _U2HOST_OHCI_ED_SIZE) + (_U2HOST_OHCI_TD_TOTAL_NUM * _U2HOST_OHCI_TD_SIZE) + (_U2HOST_OHCI_CTRL_BUFFER_NUM * _U2HOST_CTRL_OHCI_BUFFER_SIZE) + (_U2HOST_OHCI_INT_BUFFER_NUM * _U2HOST_INT_OHCI_BUFFER_SIZE) + (_U2HOST_OHCI_BULK_BUFFER_NUM * _U2HOST_BULK_OHCI_BUFFER_SIZE))
#else
#define _U2HOST_OHCI_ED_TOTAL_NUM                               (_U2HOST_OHCI_CTRL_ED_NUM + _U2HOST_OHCI_INT_ED_NUM)
#define _U2HOST_OHCI_TD_TOTAL_NUM                               (_U2HOST_OHCI_CTRL_TD_NUM + _U2HOST_OHCI_INT_TD_NUM)
#define _U2HOST_OHCI_MEMORY_SIZE                                (_U2HOST_OHCI_SETUP_CMD_SIZE + (_U2HOST_OHCI_ED_TOTAL_NUM * _U2HOST_OHCI_ED_SIZE) + (_U2HOST_OHCI_TD_TOTAL_NUM * _U2HOST_OHCI_TD_SIZE) + (_U2HOST_OHCI_CTRL_BUFFER_NUM * _U2HOST_CTRL_OHCI_BUFFER_SIZE) + (_U2HOST_OHCI_INT_BUFFER_NUM * _U2HOST_INT_OHCI_BUFFER_SIZE))
#endif

#define _U2HOST_OHCI_CTRL_ED_0_ST_ADDR                          (_U2HOST_MEMORY_ST_ADDR + _U2HOST_MEMORY_OHCI_ST_ADDR_OFFSET)   // Addres format : 32-bits, but Max Memory Size is only 3K. (0x000~0x7FF)

#define _U2HOST_OHCI_CTRL_TD_0_ST_ADDR                          (_U2HOST_OHCI_CTRL_ED_0_ST_ADDR + _U2HOST_OHCI_ED_SIZE)
#define _U2HOST_OHCI_CTRL_TD_1_ST_ADDR                          (_U2HOST_OHCI_CTRL_TD_0_ST_ADDR + _U2HOST_OHCI_TD_SIZE)
#define _U2HOST_OHCI_CTRL_TD_2_ST_ADDR                          (_U2HOST_OHCI_CTRL_TD_1_ST_ADDR + _U2HOST_OHCI_TD_SIZE)

#define _U2HOST_OHCI_INT_ED_0_ST_ADDR                           (_U2HOST_OHCI_CTRL_TD_2_ST_ADDR + _U2HOST_OHCI_TD_SIZE)
#define _U2HOST_OHCI_INT_TD_0_ST_ADDR                           (_U2HOST_OHCI_INT_ED_0_ST_ADDR + _U2HOST_OHCI_ED_SIZE)

#define _U2HOST_OHCI_INT_ED_1_ST_ADDR                           (_U2HOST_OHCI_INT_TD_0_ST_ADDR + _U2HOST_OHCI_TD_SIZE)
#define _U2HOST_OHCI_INT_TD_1_ST_ADDR                           (_U2HOST_OHCI_INT_ED_1_ST_ADDR + _U2HOST_OHCI_ED_SIZE)


#define _U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR                     (_U2HOST_OHCI_INT_TD_1_ST_ADDR + _U2HOST_OHCI_TD_SIZE)

#define _U2HOST_OHCI_CTRL_BUFFER_ST_ADDR                        (_U2HOST_OHCI_CTRL_SETUP_CMD_ST_ADDR + _U2HOST_OHCI_SETUP_CMD_SIZE)
#define _U2HOST_OHCI_INT0_BUFFER_ST_ADDR                        (_U2HOST_OHCI_CTRL_BUFFER_ST_ADDR + _U2HOST_CTRL_OHCI_BUFFER_SIZE)
#define _U2HOST_OHCI_INT1_BUFFER_ST_ADDR                        (_U2HOST_OHCI_INT0_BUFFER_ST_ADDR + _U2HOST_INT_OHCI_BUFFER_SIZE)

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#define _U2HOST_OHCI_BULK_IN_ED_0_ST_ADDR                       (_U2HOST_OHCI_INT1_BUFFER_ST_ADDR + _U2HOST_INT_OHCI_BUFFER_SIZE)
#define _U2HOST_OHCI_BULK_IN_TD_0_ST_ADDR                       (_U2HOST_OHCI_BULK_IN_ED_0_ST_ADDR + _U2HOST_OHCI_ED_SIZE)
#define _U2HOST_OHCI_BULK_IN_TD_1_ST_ADDR                       (_U2HOST_OHCI_BULK_IN_TD_0_ST_ADDR + _U2HOST_OHCI_TD_SIZE)

#define _U2HOST_OHCI_BULK_OUT_ED_0_ST_ADDR                      (_U2HOST_OHCI_BULK_IN_TD_1_ST_ADDR + _U2HOST_OHCI_TD_SIZE)
#define _U2HOST_OHCI_BULK_OUT_TD_0_ST_ADDR                      (_U2HOST_OHCI_BULK_OUT_ED_0_ST_ADDR + _U2HOST_OHCI_ED_SIZE)
#define _U2HOST_OHCI_BULK_OUT_TD_1_ST_ADDR                      (_U2HOST_OHCI_BULK_OUT_TD_0_ST_ADDR + _U2HOST_OHCI_TD_SIZE)
#define _U2HOST_OHCI_BULK_IN_BUFFER_ST_ADDR                     (_U2HOST_OHCI_BULK_OUT_TD_1_ST_ADDR + _U2HOST_OHCI_TD_SIZE)
#define _U2HOST_OHCI_BULK_OUT_BUFFER_ST_ADDR                    (_U2HOST_OHCI_BULK_IN_BUFFER_ST_ADDR + _U2HOST_BULK_OHCI_BUFFER_SIZE)
#endif
#endif

//----------------------------------------------------------------------------------------------------
// Memory Allocation for EHCI
//----------------------------------------------------------------------------------------------------
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
#define _U2HOST_CTRL_EHCI_BUFFER_SIZE                           128
#define _U2HOST_BULK_DATA_EHCI_BUFFER_SIZE                      1024
#define _U2HOST_BULK_CSW_EHCI_BUFFER_SIZE                       32
#define _U2HOST_BULK_EHCI_BUFFER_SIZE                           512

#define _U2HOST_EHCI_QH_SIZE                                    64   // (48+16) : +16 for QH Pointer Format
#define _U2HOST_EHCI_QTD_SIZE                                   32

//CTRL QH Related
#define _U2HOST_EHCI_CTRL_QH_ST_ADDR                            _U2HOST_MEMORY_ST_ADDR   // Addres format : 32-bits, Max Memory Size is only 3K In 1039

#define _U2HOST_EHCI_CTRL_QTD_0_ST_ADDR                         (_U2HOST_MEMORY_ST_ADDR + _U2HOST_EHCI_QH_SIZE)
#define _U2HOST_EHCI_CTRL_QTD_1_ST_ADDR                         (_U2HOST_EHCI_CTRL_QTD_0_ST_ADDR + _U2HOST_EHCI_QTD_SIZE)
#define _U2HOST_EHCI_CTRL_QTD_2_ST_ADDR                         (_U2HOST_EHCI_CTRL_QTD_1_ST_ADDR + _U2HOST_EHCI_QTD_SIZE)

//BULK IN QH Related
#define _U2HOST_EHCI_BULK_IN_QH_ST_ADDR                         (_U2HOST_EHCI_CTRL_QTD_2_ST_ADDR + _U2HOST_EHCI_QTD_SIZE)

#define _U2HOST_EHCI_BULK_IN_QTD_0_ST_ADDR                      (_U2HOST_EHCI_BULK_IN_QH_ST_ADDR + _U2HOST_EHCI_QH_SIZE)
#define _U2HOST_EHCI_BULK_IN_QTD_1_ST_ADDR                      (_U2HOST_EHCI_BULK_IN_QTD_0_ST_ADDR + _U2HOST_EHCI_QTD_SIZE)

//BULK OUT QH Related
#define _U2HOST_EHCI_BULK_OUT_QH_ST_ADDR                        (_U2HOST_EHCI_BULK_IN_QTD_1_ST_ADDR + _U2HOST_EHCI_QTD_SIZE)

#define _U2HOST_EHCI_BULK_OUT_QTD_0_ST_ADDR                     (_U2HOST_EHCI_BULK_OUT_QH_ST_ADDR + _U2HOST_EHCI_QH_SIZE)
#define _U2HOST_EHCI_BULK_OUT_QTD_1_ST_ADDR                     (_U2HOST_EHCI_BULK_OUT_QTD_0_ST_ADDR + _U2HOST_EHCI_QTD_SIZE)

#define _U2HOST_EHCI_CTRL_BUFFER_ST_ADDR                        (_U2HOST_EHCI_BULK_OUT_QTD_1_ST_ADDR + _U2HOST_EHCI_QTD_SIZE)

#define _U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR                    (_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR + _U2HOST_CTRL_EHCI_BUFFER_SIZE)
#define _U2HOST_EHCI_BULK_DATA_BUFFER_ST_ADDR                   (_U2HOST_EHCI_BULK_CSW_BUFFER_ST_ADDR + _U2HOST_BULK_CSW_EHCI_BUFFER_SIZE)

#define _U2HOST_EHCI_BULK_OUT_BUFFER_ST_ADDR                    (_U2HOST_EHCI_CTRL_BUFFER_ST_ADDR + _U2HOST_CTRL_EHCI_BUFFER_SIZE)
#define _U2HOST_EHCI_BULK_IN_BUFFER_ST_ADDR                     (_U2HOST_EHCI_BULK_OUT_BUFFER_ST_ADDR + _U2HOST_BULK_EHCI_BUFFER_SIZE)
#endif

#define _U2HOST_NONE                                            0xFF

#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
#define GET_U2HOST_MODE_STATE()                                 (g_ucUsbU2HostModeState)
#define SET_U2HOST_MODE_STATE(x)                                (g_ucUsbU2HostModeState = (x))

#define GET_U2HOST_CONNECT_STATUS()                             (g_ucUsbU2HostConnectStatus)
#define SET_U2HOST_CONNECT_STATUS(x)                            (g_ucUsbU2HostConnectStatus = (x))

#define GET_U2HOST_COMMUNICATE_STATE()                          (g_ucUsbU2HostCommunicateState)
#define SET_U2HOST_COMMUNICATE_STATE(x)                         (g_ucUsbU2HostCommunicateState = (x))

#define GET_U2HOST_ENUM_STATE()                                 (g_ucUsbU2HostEnumState)
#define SET_U2HOST_ENUM_STATE(x)                                (g_ucUsbU2HostEnumState = (x))

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#define GET_U2HOST_COLOR_STATE()                                (g_enumUsbU2HostColorAnalyzerState)
#define SET_U2HOST_COLOR_STATE(x)                               (g_enumUsbU2HostColorAnalyzerState = (x))

// Set by Color FW, Clr by U2 Host FW
#define GET_U2HOST_COLOR_REQ_STATUS()                           (g_enumUsbU2HostColorReqStatus)
#define SET_U2HOST_COLOR_REQ_STATUS(x)                          (g_enumUsbU2HostColorReqStatus = (x))
#define CLR_U2HOST_COLOR_REQ_STATUS()                           (g_enumUsbU2HostColorReqStatus = _U2HOST_COLOR_REQ_NONE)
// Set by U2 Host FW, Clr by Color FW Get Resp
#define GET_U2HOST_COLOR_RSP_STATUS()                           (g_enumUsbU2HostColorRspStatus)
#define SET_U2HOST_COLOR_RSP_STATUS(x)                          (g_enumUsbU2HostColorRspStatus = (x))
#define CLR_U2HOST_COLOR_RSP_STATUS()                           (g_enumUsbU2HostColorRspStatus = _U2HOST_COLOR_RSP_NONE)
#endif

#if(_USB2_HOST_EHCI_SUPPORT == _ON)
#define GET_U2HOST_BULK_SCSI_STATE()                            (g_ucUsbU2HostBulkScsiState)
#define SET_U2HOST_BULK_SCSI_STATE(x)                           (g_ucUsbU2HostBulkScsiState = (x))

#define GET_U2HOST_DDR_STATE()                                  (g_ucUsbU2HostDDRReadyState)
#define SET_U2HOST_DDR_STATE(x)                                 (g_ucUsbU2HostDDRReadyState = (x))

#define GET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG()               (g_ucUsbU2HostBulkInQTDFlag)
#define SET_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG()               (g_ucUsbU2HostBulkInQTDFlag = _TRUE)
#define CLR_U2HOST_BULK_QH_1ST_QTD_PROCESS_FLAG()               (g_ucUsbU2HostBulkInQTDFlag = _FALSE)

#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
#if(_U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _ON)
#define GET_U2HOST_DB_CUR_CRC_SAME_STATE()                      (g_ucUsbU2HostCurCrcValueSame)
#define SET_U2HOST_DB_CUR_CRC_SAME_STATE(x)                     (g_ucUsbU2HostCurCrcValueSame = (x))
#endif

#define GET_U2HOST_DDR_FRC_CLIENT_EN_STATUS()                   (g_bUsbU2HostDDRFRCClientEnStatus)
#define SET_U2HOST_DDR_FRC_CLIENT_EN_STATUS()                   (g_bUsbU2HostDDRFRCClientEnStatus = _TRUE)
#define CLR_U2HOST_DDR_FRC_CLIENT_EN_STATUS()                   (g_bUsbU2HostDDRFRCClientEnStatus = _FALSE)
#endif

#define GET_U2HOST_DB_CUR_PATH_FINISH_STATE()                   (g_stUsbU2HostDBCurPath.b1UsbU2HostDBCurPathFinishState)
#define SET_U2HOST_DB_CUR_PATH_FINISH_STATE()                   (g_stUsbU2HostDBCurPath.b1UsbU2HostDBCurPathFinishState = _TRUE)
#define CLR_U2HOST_DB_CUR_PATH_FINISH_STATE()                   (g_stUsbU2HostDBCurPath.b1UsbU2HostDBCurPathFinishState = _FALSE)

#define GET_U2HOST_DB_CUR_PATH()                                (g_stUsbU2HostDBCurPath.enumUsbU2HostDBCurPath)
#define SET_U2HOST_DB_CUR_PATH(x)                               (g_stUsbU2HostDBCurPath.enumUsbU2HostDBCurPath = (x))

#define GET_U2HOST_DM_CLIENT_INITIAL()                          (g_stUsbU2HostDBCurPath.b1UsbU2HostDMClientInitial)
#define SET_U2HOST_DM_CLIENT_INITIAL()                          (g_stUsbU2HostDBCurPath.b1UsbU2HostDMClientInitial = _TRUE)
#define CLR_U2HOST_DM_CLIENT_INITIAL()                          (g_stUsbU2HostDBCurPath.b1UsbU2HostDMClientInitial = _FALSE)
#endif

#define GET_U2HOST_NEXT_STATE_AFTER_HALT()                      (g_ucUsbU2HostNextStateAfterHalt)
#define SET_U2HOST_NEXT_STATE_AFTER_HALT(x)                     (g_ucUsbU2HostNextStateAfterHalt = (x))
#define CLR_U2HOST_NEXT_STATE_AFTER_HALT()                      (g_ucUsbU2HostNextStateAfterHalt = _U2HOST_NONE)

#define GET_U2HOST_CONNECT_DET_READY_FLAG()                     (g_bUsbU2HostConnectDetReadyFlag)
#define SET_U2HOST_CONNECT_DET_READY_FLAG()                     (g_bUsbU2HostConnectDetReadyFlag = _TRUE)
#define CLR_U2HOST_CONNECT_DET_READY_FLAG()                     (g_bUsbU2HostConnectDetReadyFlag = _FALSE)

#define GET_U2HOST_MODE_STATE_CHANGE_FLAG()                     (g_bUsbU2HostModeStateChangeFlag)
#define SET_U2HOST_MODE_STATE_CHANGE_FLAG()                     (g_bUsbU2HostModeStateChangeFlag = _TRUE)
#define CLR_U2HOST_MODE_STATE_CHANGE_FLAG()                     (g_bUsbU2HostModeStateChangeFlag = _FALSE)

#define GET_U2HOST_OWENER()                                     (g_ucUsbU2HostOwner)
#define SET_U2HOST_OWENER(x)                                    (g_ucUsbU2HostOwner = (x))

#define GET_U2HOST_COMPLETE_STATUS()                            (g_stUsbU2HostFlowCtrlFlag.b1CompleteStatus)
#define SET_U2HOST_COMPLETE_STATUS()                            (g_stUsbU2HostFlowCtrlFlag.b1CompleteStatus = _TRUE)
#define CLR_U2HOST_COMPLETE_STATUS()                            (g_stUsbU2HostFlowCtrlFlag.b1CompleteStatus = _FALSE)

#define GET_U2HOST_TRANSFER_STATUS()                            (g_stUsbU2HostFlowCtrlFlag.b1TransferStatus)
#define SET_U2HOST_TRANSFER_STATUS()                            (g_stUsbU2HostFlowCtrlFlag.b1TransferStatus = _TRUE)
#define CLR_U2HOST_TRANSFER_STATUS()                            (g_stUsbU2HostFlowCtrlFlag.b1TransferStatus = _FALSE)
#endif // End of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _U2HOST_OWNER_EHCI = 0x01,
    _U2HOST_OWNER_OHCI = 0x02,
    _U2HOST_OWNER_NONE = _U2HOST_NONE,
} EnumUsbU2HostOwner;

typedef enum
{
    _U2HOST_SCHEDULE_ASYNC = 0x01,
    _U2HOST_SCHEDULE_PERIODIC = 0x02,
    _U2HOST_SCHEDULE_NONE = 0x03,
} EnumUsbScheduleType;

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
typedef enum
{
    _U2HOST_NONE_TRANSFER = 0x00,
    _U2HOST_CONTROL_TRANSFER = 0x01,
    _U2HOST_BULK_TRANSFER = 0x02,
    _U2HOST_INT_TRANSFER = 0x03,
    _U2HOST_ISOCHRONOUS_TRANSFER = 0x04,
}EnumUsbU2HostTransferType;

typedef enum
{
    _U2HOST_VID_NONE = 0x0000,
    _U2HOST_VID_XRITE = 0x0765,
    _U2HOST_VID_CA410 = 0x132B,
    _U2HOST_VID_ERROR = 0xFFFF,
}EnumUsbU2HostDevVid;

typedef enum
{
    _U2HOST_PID_NONE = 0x0000,
    _U2HOST_PID_CA410 = 0x210D,
    _U2HOST_PID_XRITE = 0x5020,
    _U2HOST_PID_XRITE2 = 0x5021,
    _U2HOST_PID_ERROR = 0xFFFF,
}EnumUsbU2HostDevPid;
#endif // END OF #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)

typedef struct
{
    BYTE ucValidDevIndex;    // Dev Valid Info, which is a BitMap format
    WORD pusUsb2HostValidDevVID[_U2HOST_DEV_ATTACH_COUNT];   // Valid Dev VID
    WORD pusUsb2HostValidDevPID[_U2HOST_DEV_ATTACH_COUNT];   // Valid Dev PID
} StructUsbU2HostDevConnectInfo;

#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
// COMMUNICATION STATE + ENUM STATE + BULK TRANS STATE + INT TRANS STATE
typedef enum
{
    _U2HOST_COMMUNICATE_STATE_ENUMERATION = 0x00,
    _U2HOST_COMMUNICATE_STATE_BULK_TRANS_OPERATION,
    _U2HOST_COMMUNICATE_STATE_INT_TRANS_OPERATION,
    _U2HOST_COMMUNICATE_STATE_COLOR_ANALYZER_OPERATION,
    _U2HOST_COMMUNICATE_STATE_NONE = 0x04,
} EnumUsbU2HostCommunicateStatus;

typedef enum
{
    _U2HOST_MODE_STATE_POWER_OFF = 0x00,
    _U2HOST_MODE_STATE_EHCI_RH_PORT_ENABLE,
    _U2HOST_MODE_STATE_COMMUNICATION,
    _U2HOST_MODE_STATE_ROOT_HUB_REMOVE_DEVICE,
    _U2HOST_MODE_STATE_OHCI_POWER_ON,
    _U2HOST_MODE_STATE_OHCI_RH_PORT_ENABLE,
} EnumUsbU2HostModeStatus;

typedef enum
{
    _U2HOST_CONNECT_NO_CHANGE = 0x00,
    _U2HOST_CONNECT_INSERT_DEVICE,
    _U2HOST_CONNECT_REMOVE_DEVICE,
    _U2HOST_CONNECT_STATUS_NONE = 0x03,
} EnumUsbU2HostConnectStatus;

typedef enum
{
    _U2HOST_CONNECT_CHANGE_TO_ATTACH = 0x00,
    _U2HOST_CONNECT_CHANGE_TO_UNATTACH = 0x01,
    _U2HOST_CONNECT_CHANGE_NONE = 0x02,
} EnumUsbU2HostConnectChange;

typedef enum
{
    _U2HOST_DDR_READY = 0x01,
    _U2HOST_DDR_NOT_READY = 0x02,
    _U2HOST_DDR_NONE = _U2HOST_NONE,
} EnumUsbU2HostDDRReadyState;

typedef enum
{
    // Non-Reply from Device : [BIT5,BIT4] = [0,0]
    _U2HOST_ENUM_STATE_ADD_CTRL_QH = 0x00,

    _U2HOST_ENUM_STATE_ABORT,
    _U2HOST_ENUM_STATE_FINISH,

    // Set Command Type : [BIT5,BIT4] = [0,1]
    _U2HOST_ENUM_STATE_SET_ADDRESS = 0x10,
    _U2HOST_ENUM_STATE_SET_IDLE,
    _U2HOST_ENUM_STATE_SET_CONFIGURATION,
    _U2HOST_ENUM_STATE_SET_LINE_CODING,
    _U2HOST_ENUM_STATE_SET_CONTROL_LINE_STATE,

    // GET Command Type : [BIT5,BIT4] = [1,0]
    _U2HOST_ENUM_STATE_GET_DEVICE_DESCRIPTOR = 0x20,
    _U2HOST_ENUM_STATE_GET_CONFIG_DESCRIPTOR,
    _U2HOST_ENUM_STATE_GET_OTHER_DESCRIPTOR,
    _U2HOST_ENUM_STATE_GET_LANGUAGE_ID,
    _U2HOST_ENUM_STATE_GET_PRODUCT_NAME,
    _U2HOST_ENUM_STATE_GET_MANUFACTURE_NAME,
    _U2HOST_ENUM_STATE_GET_SERIAL_NUMBER,
    _U2HOST_ENUM_STATE_GET_HID_REPORT,
    _U2HOST_ENUM_STATE_GET_MAX_LUN,
    _U2HOST_ENUM_STATE_GET_LINE_CODING,

    _U2HOST_ENUM_STATE_NONE = _U2HOST_NONE,
} EnumUsbU2HostEnumerationStatus;

typedef enum
{
    //--------------------------------------------
    // [Part 0] BULK QH INITIAL - Non-Reply from Device : [BIT7, BIT6, BIT5] = [0, 0, 0]
    //--------------------------------------------
    _U2HOST_ADD_BULK_READ_QH = 0x00,
    _U2HOST_ADD_BULK_WRITE_QH,
    _U2HOST_IDLE,
    _U2HOST_JUDGE_PARTITION_ID,
    _U2HOST_CUR_PARTITION_ABORT,
    _U2HOST_WAIT_USER_OSD_ENABLE,
    _U2HOST_WAIT_USER_OSD_REBOOT,

    //--------------------------------------------
    // [Part 1] SCSI READ PROCESS - (OUT QH: CBW) Range 0x10-0x1E, [BIT7, BIT6, BIT5] = [0, 0, 1]
    //--------------------------------------------
    _U2HOST_BULK_SCSI_INQUIRY_OUT_QH = 0x20,
    _U2HOST_BULK_SCSI_READ_FORMAT_CAP_OUT_QH,
    _U2HOST_BULK_SCSI_REQ_SENSE_OUT_QH,
    _U2HOST_BULK_SCSI_READ_CAPACITY10_OUT_QH,
    _U2HOST_BULK_SCSI_MODE_SENSE6_OUT_QH,
    _U2HOST_BULK_SCSI_TEST_UNIT_READY_OUT_QH,

    // SCSI READ PROCESS - Customized flow to parse File System
    _U2HOST_BULK_SCSI_READ10_MBR_OUT_QH,
    _U2HOST_BULK_SCSI_READ10_GPT_HDR_OUT_QH,
    _U2HOST_BULK_SCSI_READ10_GPT_ENT_OUT_QH,
    _U2HOST_BULK_SCSI_READ10_DBR_OUT_QH,

    // SCSI READ PROCESS - Customized flow to parse File System - FAT32
    _U2HOST_BULK_SCSI_READ10_FAT_DIR_CLUS_NUM_OUT_QH,
    _U2HOST_BULK_SCSI_READ10_FAT_DIR_SRCH_OUT_QH,

    // SCSI READ PROCESS - Customized flow to parse File System - NTFS
    _U2HOST_BULK_SCSI_READ10_NTFS_ROOT_ENTRY_OUT_QH,
    _U2HOST_BULK_SCSI_READ10_NTFS_IDX_RECORD_OUT_QH,
    _U2HOST_BULK_SCSI_READ10_NTFS_FILE_ENTRY_OUT_QH,

    // SCSI READ PROCESS - Customized flow to check / get Target File
    _U2HOST_BULK_SCSI_READ10_FILE_GET_TGT_OUT_QH,
    _U2HOST_BULK_SCSI_READ10_FILE_CHK_END_OUT_QH,
    _U2HOST_BULK_SCSI_READ10_FW_VERSION_CHK_OUT_QH,
    _U2HOST_BULK_SCSI_READ10_FILE_DATA_OUT_QH,

    //--------------------------------------------
    // [Part 2] SCSI READ PROCESS - (IN QH: Data IN + CSW), [BIT7, BIT6, BIT5] = [0, 1, 0]
    //--------------------------------------------
    _U2HOST_BULK_SCSI_INQUIRY_IN_QH = 0x40,
    _U2HOST_BULK_SCSI_READ_FORMAT_CAP_IN_QH,
    _U2HOST_BULK_SCSI_REQ_SENSE_IN_QH,
    _U2HOST_BULK_SCSI_READ_CAPACITY10_IN_QH,
    _U2HOST_BULK_SCSI_MODE_SENSE6_IN_QH,
    // Test Unit State do not have Data Stage
    _U2HOST_BULK_SCSI_TEST_UNIT_READY_IN_QH,

    // SCSI READ PROCESS - Customized flow to parse File System
    _U2HOST_BULK_SCSI_READ10_MBR_IN_QH,
    _U2HOST_BULK_SCSI_READ10_GPT_HDR_IN_QH,
    _U2HOST_BULK_SCSI_READ10_GPT_ENT_IN_QH,
    _U2HOST_BULK_SCSI_READ10_DBR_IN_QH,

    // SCSI READ PROCESS - Customized flow to parse File System - FAT32
    _U2HOST_BULK_SCSI_READ10_FAT_DIR_CLUS_NUM_IN_QH,
    _U2HOST_BULK_SCSI_READ10_FAT_DIR_SRCH_IN_QH,

    // SCSI READ PROCESS - Customized flow to parse File System - NTFS
    _U2HOST_BULK_SCSI_READ10_NTFS_ROOT_ENTRY_IN_QH,
    _U2HOST_BULK_SCSI_READ10_NTFS_IDX_RECORD_IN_QH,
    _U2HOST_BULK_SCSI_READ10_NTFS_FILE_ENTRY_IN_QH,

    // SCSI READ PROCESS - Customized flow to check / get Target File
    _U2HOST_BULK_SCSI_READ10_FILE_GET_TGT_IN_QH,
    _U2HOST_BULK_SCSI_READ10_FILE_CHK_END_IN_QH,
    _U2HOST_BULK_SCSI_READ10_FW_VERSION_CHK_IN_QH,
    _U2HOST_BULK_SCSI_READ10_FILE_DATA_IN_QH,

    //--------------------------------------------
    // [Part 3] SCSI WRITE PROCESS - (OUT QH: CBW + Data OUT), [BIT7, BIT6, BIT5] = [1, 0, 1]
    //--------------------------------------------
    _U2HOST_BULK_SCSI_WRITE10_DATA_OUT_QH = 0xA0,

    //--------------------------------------------
    // [Part 4] BULK WRITE PROCESS - (IN QH: CSW), [BIT7, BIT6, BIT5] = [1, 1, 0]
    //--------------------------------------------
    _U2HOST_BULK_SCSI_WRITE10_DATA_IN_QH = 0xC0,

    //--------------------------------------------
    // [Part 5] CLEAR HALT DURING BULK (by Ctrl xfer), [BIT7, BIT6, BIT5] = [1, 1, 1]
    //--------------------------------------------
    _U2HOST_CLEAR_HALT_DUR_BULK = 0XE0,

    //--------------------------------------------
    _U2HOST_BULK_SCSI_NONE = _U2HOST_NONE,
} EnumUsbU2HostBulkScsiStatus;

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
typedef enum
{
    _U2HOST_COLOR_ADD_BULK_ED = 0x00,
    _U2HOST_COLOR_ADD_INT_ED,
    _U2HOST_COLOR_IDLE,
    _U2HOST_COLOR_CONTROL_OUT,
    _U2HOST_COLOR_CONTROL_IN,
    _U2HOST_COLOR_BULK_OUT,
    _U2HOST_COLOR_BULK_IN,
    _U2HOST_COLOR_INT_OUT,
    _U2HOST_COLOR_INT_IN,
    _U2HOST_COLOR_NONE = _U2HOST_NONE,
}EnumUsbU2HostColorAnalyzerState;

typedef enum
{
    _U2HOST_COLOR_REQ_NONE = 0x00,
    _U2HOST_COLOR_REQ_CONTROL_OUT,
    _U2HOST_COLOR_REQ_CONTROL_IN,
    _U2HOST_COLOR_REQ_BULK_INITIAL,
    _U2HOST_COLOR_REQ_BULK_OUT,
    _U2HOST_COLOR_REQ_BULK_IN,
    _U2HOST_COLOR_REQ_INT_INITIAL,
    _U2HOST_COLOR_REQ_INT_OUT,
    _U2HOST_COLOR_REQ_INT_IN,
}EnumUsbU2HostColorReqStatus;

typedef enum
{
    _U2HOST_COLOR_RSP_NONE = 0x00,
    _U2HOST_COLOR_RSP_CONTROL_OUT,
    _U2HOST_COLOR_RSP_CONTROL_IN,
    _U2HOST_COLOR_RSP_BULK_OUT,
    _U2HOST_COLOR_RSP_BULK_IN,
    _U2HOST_COLOR_RSP_INT_OUT,
    _U2HOST_COLOR_RSP_INT_IN,
}EnumUsbU2HostColorRspStatus;
#endif // END OF #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)

typedef enum
{
    _U2HOST_DB_NONE = 0x00,
    _U2HOST_DB_M1 = 0x01,
    _U2HOST_DB_M2 = 0x02,
    _U2HOST_DB_S1 = 0x04,
    _U2HOST_DB_S2 = 0x08,
    _U2HOST_DB_S3 = 0x10,
    _U2HOST_DB_S4 = 0x20,
}EnumUsbU2HostDBCurPath;

typedef enum
{
    _U2HOST_DB_CRC_NONE = 0x00,
    _U2HOST_DB_CRC_SAME = 0x01,
    _U2HOST_DB_CRC_DIFF = 0x02,
}EnumUsbU2HostDBCurXferCrcStatus;

// Related to tUsbFat32GoldenLongFileNameReplace[0] - [3]
typedef enum
{
    _U2HOST_DB_M1_INDEX = 0x00,
    _U2HOST_DB_M2_INDEX = 0x01,
    _U2HOST_DB_S1_INDEX = 0x02,
    _U2HOST_DB_S2_INDEX = 0x03,
    _U2HOST_DB_INDEX_NONE = 0x0F, // make sure != 0/1/2/3
}EnumUsbU2HostDBCurPathIndex;

typedef struct
{
    EnumUsbU2HostDBCurPath enumUsbU2HostDBCurPath;
#if(_U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _ON)
    BYTE ucUsbU2HostDBCalcCrcXferCntOnce; // How many BulkOut Data Stage should be transmit once Crc Calc(may contain multiple Bulk out Data stage).
    BYTE ucUsbU2HostDBCalcCrcXferCntOnceShadow;
    BYTE ucUsbU2HostDBXferVHNumCalcCrc;  // How many vehight should be transmit once Crc Calc  (=  ucUsbU2HostDBXferVHOnceSetting *  ucUsbU2HostDBCalcCrcXferCntOnce )
    WORD usUsbU2HostDBNextXferVHNO;

    BYTE ucUsbU2HostDBCalcCrcDiffCnt;
    DWORD ulUsbU2HostDBCalcCrcXferLenEachTime;

    DWORD ulUsbU2HostDBStartCapAddrCurCrcCalc;
    DWORD ulUsbU2HostDBtoDeviceStartAddrCurCrcCalc;
#endif
    BYTE b1UsbU2HostDBCurPathFinishState : 1;
    BYTE b1UsbU2HostDMClientInitial : 1;
    BYTE ucUsbU2HostCurDBPatternIndex; // CurDBPatternIndex will be defined by others for Final version.
    BYTE b1UsbU2HostDBCurPathLastXferNotFull : 1;
    WORD usUsbU2HostDBCurPathVehight;
    WORD usUsbU2HostDBCurXferLen; // Unit : Byte
    WORD usUsbU2HostDBCurPathLastXferLen; // Unit : Byte
    WORD usUsbU2HostDBtoDeviceLastXferLen;// // Unit : Byte
    WORD usUsbU2HostDBCurPathXferCnt;
    WORD usUsbU2HostDBCurPathXferCntShadow;
    WORD usUsbU2HostDBCurPathLineStep; // unit:64bit
    DWORD ulUsbU2HostDBCapAddr;
    DWORD ulUsbU2HostDBInitCapAddr;
}StructUsbU2HostDBCurPathInfo;

typedef struct
{
    BYTE b1TransferStatus : 1;
    BYTE b1CompleteStatus : 1;
    BYTE b1SecondProcStatus : 1;
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
    BYTE b1GetSecReportDes : 1;
    BYTE b1IntProcessActive : 1;
#endif
} StructUsbFlowCtrlFlag;

typedef struct
{
    BYTE ucDeviceDesLen;

    BYTE ucDeviceClass;
    BYTE ucDeviceSubClass;
    BYTE ucDeviceProtocol;

    BYTE ucMaxPacketSize0;

    WORD usVendorID;
    WORD usProductID;
    WORD usBcdDevice;
    BYTE ucManufacturerIndex;
    BYTE ucProductIndex;
    BYTE ucSerialNumberIndex;

    BYTE ucNumConfig;

    WORD usLanguageID;
    BYTE ucManufacturerNameSize;
    BYTE ucProductNameSize;
    BYTE ucSerialNumberSize;
    BYTE pucManufacturerName[64];
    BYTE pucProductName[64];
    BYTE pucSerialNumber[64];
} StructUsbDeviceInfoTable;
#endif // End of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructUsbU2HostDevConnectInfo g_stUsbU2HostDevConnectInfo;
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
extern BYTE g_ucUsbU2HostColorWriteReqLen;
extern BYTE g_pucUsbU2HostColorWriteReqData[24];
extern BYTE g_ucUsbU2HostColorReadRspLen;
#endif // END OF #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#endif // END OF #if(_USB2_HOST_OHCI_SUPPORT == _ON)

#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
extern BYTE g_ucUsbU2HostModeState;
extern BYTE g_ucUsbU2HostConnectStatus;
extern BYTE g_ucUsbU2HostCommunicateState;
extern BYTE g_ucUsbU2HostEnumState;
extern StructUsbDeviceInfoTable g_stUsbU2HostDeviceInfo;

#if(_USB2_HOST_EHCI_SUPPORT == _ON)
extern BYTE g_ucUsbU2HostBulkScsiState;
extern BYTE g_ucUsbU2HostDDRReadyState;
extern StructUsbU2HostDBCurPathInfo g_stUsbU2HostDBCurPath;
extern BYTE g_ucUsbU2HostScsiFlowFlag;
extern BYTE g_ucUsbU2HostBulkInQTDFlag;
#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
#if(_U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _ON)
extern BYTE g_ucUsbU2HostCurCrcValueSame;
#endif
extern bit g_bUsbU2HostDDRFRCClientEnStatus;
#endif // END OF #if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
#endif // END OF #if(_USB2_HOST_EHCI_SUPPORT == _ON)

extern BYTE g_ucUsbU2HostNextStateAfterHalt;
extern bit g_bUsbU2HostConnectDetReadyFlag;
extern bit g_bUsbU2HostModeStateChangeFlag;
extern BYTE g_ucUsbU2HostOwner;
extern StructUsbFlowCtrlFlag g_stUsbU2HostFlowCtrlFlag;
extern bit g_bUsbU2HostDummyRegBit0; // temp use, Will be instead in normal use by cychen2

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
extern EnumUsbU2HostColorAnalyzerState g_enumUsbU2HostColorAnalyzerState;
extern EnumUsbU2HostColorReqStatus g_enumUsbU2HostColorReqStatus;
extern EnumUsbU2HostColorRspStatus g_enumUsbU2HostColorRspStatus;
#endif // END OF #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#endif // END OF #if(_USB2_HOST_OHCI_SUPPORT == _ON)
#endif // END OF #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)

#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_FREE_RTOS)
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
extern BYTE g_pucUsbU2HostColorReadRspData[128];
extern BYTE g_ucUsbU2HostColorReadDataLen;
#endif // END OF #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#endif // END OF #if(_USB2_HOST_OHCI_SUPPORT == _ON)
#endif // END OF #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_FREE_RTOS)

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerUsbU2HostScheduleEnable(EnumUsbScheduleType enumSchType, bit bEnType);
extern void ScalerUsbU2HostGetBufferBulkData(WORD usBufAddr, WORD usStartAddr, BYTE *pucArray, WORD usDataLength);

#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
extern void ScalerUsbU2HostClrContent(EnumUsbU2HostOwner enumOwner);
extern void ScalerUsbU2HostPowerControl(EnumUsbU2HostOwner enumMode, bit bOn);
extern void ScalerUsbU2HostJudgeHandler(void);
extern void ScalerUsbU2HostEnum(EnumUsbU2HostOwner enumOwner);
extern bit ScalerUsbU2HostChkCtrlQueueErrSts(EnumUsbU2HostOwner enumOwner);
extern bit ScalerUsbU2HostChkCtrlQueueComplete(EnumUsbU2HostOwner enumOwner);
extern bit ScalerUsbU2HostChkBulkQueueErrSts(EnumUsbU2HostOwner enumOwner);
extern bit ScalerUsbU2HostChkBulkQueueComplete(EnumUsbU2HostOwner enumOwner);
extern BYTE ScalerUsbU2HostGetRspDataLen(EnumUsbU2HostOwner enumOwner);
#if(_USB2_HOST_OHCI_SUPPORT == _ON)
extern bit ScalerUsbU2HostChkIntQueueErrSts(EnumUsbU2HostOwner enumOwner, BYTE ucInterfaceNumUse);
extern bit ScalerUsbU2HostChkIntQueueComplete(EnumUsbU2HostOwner enumOwner, BYTE ucInterfaceNumUse);
#endif
extern void ScalerUsbU2HostDebugReg(void);
extern bit ScalerUsbU2HostCheckLastTransactionCompleteStatus(EnumUsbU2HostOwner enumOwner);
extern void ScalerUsbU2HostEnumDataHandler(EnumUsbU2HostOwner enumOwner);
extern bit ScalerUsbU2HostPortOwnerSwitch(EnumUsbU2HostOwner enumOwner);
extern bit ScalerUsbU2HostRhPortEnable(EnumUsbU2HostOwner enumMode);

#if(_USB2_HOST_EHCI_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
extern void ScalerUsbU2HostBulkReadOperation(void);
#endif

#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)

#if(_U2HOST_DM_DUMP_DATA_ERR_HANDLER_OLD_MODE == _OFF)
extern bit ScalerUsbU2HostGetDMAddrErrFlag(void);
extern void ScalerUsbU2HostDMClientUpdate(void);
#else
extern void ScalerUsbU2HostGetCurDMCrcAndXferEnResult(void);
extern bit ScalerUsbU2HostCheckCrcResultSame(void);
#endif

extern void ScalerUsbU2HostBulkWriteOperation(EnumUsbU2HostDDRReadyState enumUsbU2HostDDRReadyState);
extern void ScalerUsbU2HostDBDumpFrameNameUpdate(BYTE ucCaseIndex, BYTE ucFrameIndex);
extern void ScalerUsbU2HostDBDumpSubFrameNameUpdate(EnumUsbU2HostDBCurPathIndex  enumUsbU2HostDBCurPathIndex);
#endif

extern void ScalerUsbU2HostBulkCswErrResetRecovery(void);
extern bit ScalerUsbU2HostBulkCheckCswStatus(BYTE *pucData);
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)

#if(_USB2_HOST_OHCI_SUPPORT == _ON)
extern void ScalerUsbU2HostIntTransOperation(void);
extern void ScalerUsbU2HostIntTransOperationDataHandler(void);

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
extern void ScalerUsbU2HostColorOperation(void);
#endif
#endif // End of #if(_USB2_HOST_OHCI_SUPPORT == _ON)
#endif // End of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
#endif // End of #if(_USB2_HOST_SUPPORT == _ON)
