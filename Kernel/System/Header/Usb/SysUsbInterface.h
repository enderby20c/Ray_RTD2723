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
// ID Code      : SysUsbInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#define GET_USB_TYPE_C_ADAPTOR_POWER()                  (g_usUsbAdaptorPower)
#define SET_USB_TYPE_C_ADAPTOR_POWER(x)                 (g_usUsbAdaptorPower = (x))

#define GET_USB_TYPE_C_TOTAL_SRC_PDO_CNT(x)             (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b4TotalSrcPdoCnt)
#define SET_USB_TYPE_C_TOTAL_SRC_PDO_CNT(x, y)          (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b4TotalSrcPdoCnt = (y))

#define GET_USB_TYPE_C_TOTAL_SNK_PDO_CNT(x)             (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b4TotalSnkPdoCnt)
#define SET_USB_TYPE_C_TOTAL_SNK_PDO_CNT(x, y)          (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b4TotalSnkPdoCnt = (y))
#endif

#if(_USB_HUB_SUPPORT == _ON)
#define GET_USB_HUB_OSD_SWITCH_PORT_RESULT()            (g_enumUsbHubOSDResult)
#define SET_USB_HUB_OSD_SWITCH_PORT_RESULT(x)           (g_enumUsbHubOSDResult = (x))

#define GET_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG()     (g_ucUsbHubEventTimeoutFlag)
#define SET_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG()     (g_ucUsbHubEventTimeoutFlag = _TRUE)
#define CLR_USB_HUB_DISABLE_DURATION_TIMEOUT_FLAG()     (g_ucUsbHubEventTimeoutFlag = _FALSE)
#endif // End of #if(_USB_HUB_SUPPORT == _ON)

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
#define _USB_U2HOST_PROGRAM_LEN_ONCE                    256 // Byte

#define GET_U2_HOST_FW_UPDATE_RATE()                    (g_ucUsbU2HostFWUpdateProcessRate)
#define SET_U2_HOST_FW_UPDATE_RATE(x)                   (g_ucUsbU2HostFWUpdateProcessRate = (x))
#define CLR_U2_HOST_FW_UPDATE_RATE()                    (g_ucUsbU2HostFWUpdateProcessRate = 0)

#define GET_U2HOST_BULK_READ_ENABLE()                   (g_ucUsbFwUpdateFlowStart)
#define SET_U2HOST_BULK_READ_ENABLE()                   (g_ucUsbFwUpdateFlowStart = _ENABLE)
#define CLR_U2HOST_BULK_READ_ENABLE()                   (g_ucUsbFwUpdateFlowStart = _DISABLE)

#define GET_U2HOST_EVENT_STATUS(x)                      (g_penumUsb2HostEventStatus[(x)])
#define SET_U2HOST_EVENT_STATUS(x, y)                   (g_penumUsb2HostEventStatus[(x)] = (y))
#define CLR_U2HOST_EVENT_STATUS(x)                      (g_penumUsb2HostEventStatus[(x)] = _U2HOST_EVENT_NO_ACTION)

#define GET_U2HOST_EVENT_CHANGE(x)                      (g_pucUsb2HostEventChange[(x)])
#define SET_U2HOST_EVENT_CHANGE(x)                      (g_pucUsb2HostEventChange[(x)] = _TRUE)
#define CLR_U2HOST_EVENT_CHANGE(x)                      (g_pucUsb2HostEventChange[(x)] = _FALSE)

#define GET_U2HOST_EVENT_CHANGE_STATUS(x)               (g_pucUsb2HostEventChangeStatus[(x)])
#define SET_U2HOST_EVENT_CHANGE_STATUS(x, y)            (g_pucUsb2HostEventChangeStatus[(x)] = (y))
#define CLR_U2HOST_EVENT_CHANGE_STATUS(x)               (g_pucUsb2HostEventChangeStatus[(x)] = _DISABLE)

#define GET_U2HOST_FLOW_RESET()                         (g_bUsb2HostFlowReset)
#define SET_U2HOST_FLOW_RESET()                         (g_bUsb2HostFlowReset = _TRUE)
#define CLR_U2HOST_FLOW_RESET()                         (g_bUsb2HostFlowReset = _FALSE)
#endif

#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_FREE_RTOS)
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#define GET_U2HOST_COLOR_BULK_WRITE_REQ()               (g_bUsb2HostColorBulkWriteReq)
#define SET_U2HOST_COLOR_BULK_WRITE_REQ()               (g_bUsb2HostColorBulkWriteReq = _TRUE)
#define CLR_U2HOST_COLOR_BULK_WRITE_REQ()               (g_bUsb2HostColorBulkWriteReq = _FALSE)

#define GET_U2HOST_COLOR_BULK_READ_REQ()                (g_bUsb2HostColorBulkReadReq)
#define SET_U2HOST_COLOR_BULK_READ_REQ()                (g_bUsb2HostColorBulkReadReq = _TRUE)
#define CLR_U2HOST_COLOR_BULK_READ_REQ()                (g_bUsb2HostColorBulkReadReq = _FALSE)

#define GET_U2HOST_COLOR_INT_WRITE_REQ()                (g_bUsb2HostColorIntWriteReq)
#define SET_U2HOST_COLOR_INT_WRITE_REQ()                (g_bUsb2HostColorIntWriteReq = _TRUE)
#define CLR_U2HOST_COLOR_INT_WRITE_REQ()                (g_bUsb2HostColorIntWriteReq = _FALSE)

#define GET_U2HOST_COLOR_INT_READ_REQ()                 (g_bUsb2HostColorIntReadReq)
#define SET_U2HOST_COLOR_INT_READ_REQ()                 (g_bUsb2HostColorIntReadReq = _TRUE)
#define CLR_U2HOST_COLOR_INT_READ_REQ()                 (g_bUsb2HostColorIntReadReq = _FALSE)

#define GET_U2HOST_COLOR_BULK_WRITE_DONE()              (g_bUsb2HostColorBulkWriteDone)
#define SET_U2HOST_COLOR_BULK_WRITE_DONE()              (g_bUsb2HostColorBulkWriteDone = _TRUE)
#define CLR_U2HOST_COLOR_BULK_WRITE_DONE()              (g_bUsb2HostColorBulkWriteDone = _FALSE)

#define GET_U2HOST_COLOR_BULK_WRITE_PROCESSING()        (g_bUsb2HostColorBulkWriteProcessing)
#define SET_U2HOST_COLOR_BULK_WRITE_PROCESSING()        (g_bUsb2HostColorBulkWriteProcessing = _TRUE)
#define CLR_U2HOST_COLOR_BULK_WRITE_PROCESSING()        (g_bUsb2HostColorBulkWriteProcessing = _FALSE)

#define GET_U2HOST_COLOR_BULK_READ_DONE()               (g_bUsb2HostColorBulkReadDone)
#define SET_U2HOST_COLOR_BULK_READ_DONE()               (g_bUsb2HostColorBulkReadDone = _TRUE)
#define CLR_U2HOST_COLOR_BULK_READ_DONE()               (g_bUsb2HostColorBulkReadDone = _FALSE)

#define GET_U2HOST_COLOR_BULK_READ_PROCESSING()         (g_bUsb2HostColorBulkReadProcessing)
#define SET_U2HOST_COLOR_BULK_READ_PROCESSING()         (g_bUsb2HostColorBulkReadProcessing = _TRUE)
#define CLR_U2HOST_COLOR_BULK_READ_PROCESSING()         (g_bUsb2HostColorBulkReadProcessing = _FALSE)

#define GET_U2HOST_COLOR_INT_WRITE_DONE()               (g_bUsb2HostColorIntWriteDone)
#define SET_U2HOST_COLOR_INT_WRITE_DONE()               (g_bUsb2HostColorIntWriteDone = _TRUE)
#define CLR_U2HOST_COLOR_INT_WRITE_DONE()               (g_bUsb2HostColorIntWriteDone = _FALSE)

#define GET_U2HOST_COLOR_INT_WRITE_PROCESSING()         (g_bUsb2HostColorIntWriteProcessing)
#define SET_U2HOST_COLOR_INT_WRITE_PROCESSING()         (g_bUsb2HostColorIntWriteProcessing = _TRUE)
#define CLR_U2HOST_COLOR_INT_WRITE_PROCESSING()         (g_bUsb2HostColorIntWriteProcessing = _FALSE)

#define GET_U2HOST_COLOR_INT_READ_DONE()                (g_bUsb2HostColorIntReadDone)
#define SET_U2HOST_COLOR_INT_READ_DONE()                (g_bUsb2HostColorIntReadDone = _TRUE)
#define CLR_U2HOST_COLOR_INT_READ_DONE()                (g_bUsb2HostColorIntReadDone = _FALSE)

#define GET_U2HOST_COLOR_INT_READ_PROCESSING()          (g_bUsb2HostColorIntReadProcessing)
#define SET_U2HOST_COLOR_INT_READ_PROCESSING()          (g_bUsb2HostColorIntReadProcessing = _TRUE)
#define CLR_U2HOST_COLOR_INT_READ_PROCESSING()          (g_bUsb2HostColorIntReadProcessing = _FALSE)

#define GET_U2HOST_COLOR_QUEUE_BUFFER_DONE()            (g_bUsb2HostColorQueueBufferDone)
#define SET_U2HOST_COLOR_QUEUE_BUFFER_DONE()            (g_bUsb2HostColorQueueBufferDone = _TRUE)
#define CLR_U2HOST_COLOR_QUEUE_BUFFER_DONE()            (g_bUsb2HostColorQueueBufferDone = _FALSE)

#define GET_U2HOST_COLOR_DEQUEUE_BUFFER_DONE()          (g_bUsb2HostColorDequeueBufferDone)
#define SET_U2HOST_COLOR_DEQUEUE_BUFFER_DONE()          (g_bUsb2HostColorDequeueBufferDone = _TRUE)
#define CLR_U2HOST_COLOR_DEQUEUE_BUFFER_DONE()          (g_bUsb2HostColorDequeueBufferDone = _FALSE)

#define GET_U2HOST_COLOR_START_READ_DATA()              (g_bUsb2HostColorStartReadData)
#define SET_U2HOST_COLOR_START_READ_DATA()              (g_bUsb2HostColorStartReadData = _TRUE)
#define CLR_U2HOST_COLOR_START_READ_DATA()              (g_bUsb2HostColorStartReadData = _FALSE)
#endif // End of #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#endif // End of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_FREE_RTOS)

#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _USB_TYPE_C_UNATTACH_STATE = 0x00,
    _USB_TYPE_C_ATTACHED_STATE = 0x01,
    _USB_TYPE_C_DP_ALT_MODE_READY_STATE = 0x02,
}EnumUsbTypeCState;

typedef struct
{
    EnumUsbTypeCState enumUsbTypeCState;
    // -----------------------------
    EnumTypeCPinCfgType enumPinAssignment;
    EnumTypeCPinCfgCapType enumCurPinAssignmentCap;
    EnumTypeCPinCfgCapType enumTargetPinAssignmentCap;
    EnumTypeCMultiFuncStatus enumCurMultiFunc;
    EnumTypeCMultiFuncStatus enumTargetMultiFunc;
    // -----------------------------
    EnumTypeCAttachStatus enumCcAttachStatus;
    // -----------------------------
    EnumTypeCAltModeStatus enumAltModeStatus;
    // -----------------------------
    EnumTypeCOrientation enumOrientation;
    // -----------------------------
    EnumTypeCPowerRole enumPowerRole;
    // -----------------------------
    EnumTypeCPowerControlStatus enumPowerControlStatus;
    // -----------------------------
    WORD usVoltage;
    // -----------------------------
    WORD usCurrent;
    // -----------------------------
    WORD usCapChangeFlag;
    // -----------------------------
    WORD usUserEventFlag;
    // -----------------------------
#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    EnumTypeCLenovoAltModeStatus enumLenovoAltModeStatus;
    EnumTypeCLenovoDeviceType enumLenovoDeviceType;
    BYTE b1LenovoRcvDeviceTypeTimeout : 1;
#endif
    // -----------------------------
    BYTE b4TotalSrcPdoCnt : 4;
    BYTE b4TotalSnkPdoCnt : 4;
    // -----------------------------
    BYTE b1ReconnectReq : 1;
    BYTE b1ConnectionDet : 1;
    BYTE b1AttachStatusChange : 1;
    BYTE b1AltModeStatusChange : 1;
    BYTE b1ExtPortCtrlACOnFlag : 1;
    BYTE b1PdoChg : 1;
}StructUsbTypeCStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
extern WORD g_usUsbAdaptorPower;
extern StructUsbTypeCStatus g_pstUsbTypeCStatus[_TYPE_C_PORT_VALID];
#endif

#if(_USB_HUB_SUPPORT == _ON)
extern BYTE g_ucUsbHubEventTimeoutFlag;
extern EnumUsbHubOSDResult g_enumUsbHubOSDResult;
#endif // End of #if(_USB_HUB_SUPPORT == _ON)

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
extern volatile BYTE g_ucUsbU2HostFWUpdateProcessRate;
extern volatile BYTE g_ucUsbFwUpdateFlowStart;
extern volatile EnumUSB2HostEventResult g_penumUsb2HostEventStatus[_U2HOST_EVENT_COUNT];
extern volatile BYTE g_pucUsb2HostEventChange[_U2HOST_EVENT_CHANGE_COUNT];
extern volatile BYTE g_pucUsb2HostEventChangeStatus[_U2HOST_EVENT_CHANGE_COUNT];
#endif

#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_FREE_RTOS)
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
extern bit g_bUsb2HostColorBulkWriteReq;
extern bit g_bUsb2HostColorBulkReadReq;
extern bit g_bUsb2HostColorIntWriteReq;
extern bit g_bUsb2HostColorIntReadReq;
extern bit g_bUsb2HostColorBulkWriteDone;
extern bit g_bUsb2HostColorBulkWriteProcessing;
extern bit g_bUsb2HostColorBulkReadDone;
extern bit g_bUsb2HostColorBulkReadProcessing;
extern bit g_bUsb2HostColorIntWriteDone;
extern bit g_bUsb2HostColorIntWriteProcessing;
extern bit g_bUsb2HostColorIntReadDone;
extern bit g_bUsb2HostColorIntReadProcessing;
extern bit g_bUsb2HostColorQueueBufferDone;
extern bit g_bUsb2HostColorDequeueBufferDone;
extern bit g_bUsb2HostColorStartReadData;
#endif // End of #if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
#endif // End of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_FREE_RTOS)
#endif // End of #if(_USB2_HOST_SUPPORT == _ON)

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
extern bit SysUsbTypeCGetCcAttach(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbTypeCGetAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumPdoCheck SysUsbTypeCUpdatePortCtrlSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCUpdatePortCtrlSnkPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCOperationMode SysUsbTypeCGetDefaultOperationMode(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbTypeCGetExtPortCtrlAcOnFlag(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
// USB Hub Functions
#if(_USB_HUB_SUPPORT == _ON)
extern void SysUsbHubActiveHubDisableDurationTimerEvent(WORD usTimeoutCnt);
#if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
extern void SysUsbHubSetDspDeviceDetectFlag(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbHubOsdProc(void);
#endif // End of #if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
#endif // End of #if(_USB_HUB_SUPPORT == _ON)

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
extern BYTE SysUsbU2HostGetValidDevIndex(void);
extern WORD SysUsbU2HostGetVendorID(BYTE ucDevIndex);
extern WORD SysUsbU2HostGetProductID(BYTE ucDevIndex);
extern bit SysUsbU2HostSetColorInitial(WORD usVid, WORD usPid, EnumUsbU2HostTransferType enumTransferType);
extern bit SysUsbU2HostSetColorWriteReq(WORD usVid, WORD usPid, EnumUsbU2HostTransferType enumTransferType, BYTE *pucWriteReqData, BYTE ucWriteReqLen);
extern bit SysUsbU2HostSetColorReadReq(WORD usVid, WORD usPid, EnumUsbU2HostTransferType enumTransferType);
extern bit SysUsbU2HostGetColorReadRspStatus(WORD usVid, WORD usPid, EnumUsbU2HostTransferType enumTransferType, BYTE *pucReadGetDataLen);
extern bit SysUsbU2HostGetColorReadRspData(WORD usVid, WORD usPid, EnumUsbU2HostTransferType enumTransferType, BYTE *pucReadData, BYTE ucReadReqLen);
#endif
#endif // End of #if(_USB2_HOST_SUPPORT == _ON)
#endif // End of #if(_USB_SUPPORT == _ON)
