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
// ID Code      : SysUsb.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SYS_USB_H__
#define __SYS_USB_H__

#if(_USB_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_DB_DUMP_DATA_SUPPORT == _ON)
#define GET_U2HOST_DUMP_CUR_FRAME_FINISH()                  (g_bUsbU2HostDumpCurFrameFinish)
#define SET_U2HOST_DUMP_CUR_FRAME_FINISH()                  (g_bUsbU2HostDumpCurFrameFinish = _TRUE)
#define CLR_U2HOST_DUMP_CUR_FRAME_FINISH()                  (g_bUsbU2HostDumpCurFrameFinish = _FALSE)
#endif
#endif
#endif
#define _USB_U2HOST_CONNECT_CHECK_DURATION_TIME             1000 // Time interval from unplug to next detect connection

#endif

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#define _USB_TYPE_C_RESTART_EMB_CONNECTION_DET_TIME         100 // Time to Restart CcAttach/AltMode Check for Emb Port Ctrl After Reconnected
#define _USB_TYPE_C_RESTART_PCB_CONNECTION_DET_TIME         100 // Time to Restart CcAttach/AltMode Check By PCB Macro After Reconnected
#define _USB_TYPE_C_RESTART_I2C_CONNECTION_DET_TIME         500 // Time to Restart CcAttach/AltMode Check By SMBUS After Reconnected
#define _USB_TYPE_C_ENABLE_BILLBOARD_TIME                   1050 // Timeout Enable Billboard After CC Attach

#define _TYPE_C_LOC_PWR_DEBOUNCE_TIME_100MS                 100 // (ms)
#define _TYPE_C_LOC_PWR_DEBOUNCE_TIME_200MS                 200 // (ms)
#define _TYPE_C_LOC_PWR_DEBOUNCE_TIME_500MS                 500 // (ms)
#define _TYPE_C_PORT_CTRL_LOC_PWR_DEBOUNCE_TIME             _TYPE_C_LOC_PWR_DEBOUNCE_TIME_100MS

// USB Type-C Related Macros
#define GET_USB_TYPE_C_STATE(x)                             (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumUsbTypeCState)
#define SET_USB_TYPE_C_STATE(x, y)                          (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumUsbTypeCState = (y))

#define GET_USB_TYPE_C_ORIENTATION(x)                       (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumOrientation)
#define SET_USB_TYPE_C_ORIENTATION(x, y)                    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumOrientation = (y))

#define GET_USB_TYPE_C_PIN_ASSIGNMENT(x)                    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumPinAssignment)
#define SET_USB_TYPE_C_PIN_ASSIGNMENT(x, y)                 (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumPinAssignment = (y))

#define GET_USB_TYPE_C_CURRENT_PIN_ASSIGNMENT_CAP(x)        (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumCurPinAssignmentCap)
#define SET_USB_TYPE_C_CURRENT_PIN_ASSIGNMENT_CAP(x, y)     (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumCurPinAssignmentCap = (y))

#define GET_USB_TYPE_C_TARGET_PIN_ASSIGNMENT_CAP(x)         (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumTargetPinAssignmentCap)
#define SET_USB_TYPE_C_TARGET_PIN_ASSIGNMENT_CAP(x, y)      (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumTargetPinAssignmentCap = (y))

#define GET_USB_TYPE_C_CURRENT_MULTI_FUNCTION(x)            (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumCurMultiFunc)
#define SET_USB_TYPE_C_CURRENT_MULTI_FUNCTION(x, y)         (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumCurMultiFunc = (y))

#define GET_USB_TYPE_C_TARGET_MULTI_FUNCTION(x)             (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumTargetMultiFunc)
#define SET_USB_TYPE_C_TARGET_MULTI_FUNCTION(x, y)          (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumTargetMultiFunc = (y))

#define GET_USB_TYPE_C_CAPABILITY_CHG(x)                    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usCapChangeFlag)
#define SET_USB_TYPE_C_CAPABILITY_CHG(x, y)                 (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usCapChangeFlag = (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usCapChangeFlag | (y)))
#define CLR_USB_TYPE_C_CAPABILITY_CHG(x, y)                 (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usCapChangeFlag = (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usCapChangeFlag & (~(y))))

#define GET_USB_TYPE_C_USER_EVENT(x)                        (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usUserEventFlag)
#define SET_USB_TYPE_C_USER_EVENT(x, y)                     (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usUserEventFlag = (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usUserEventFlag | (y)))
#define CLR_USB_TYPE_C_USER_EVENT(x, y)                     (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usUserEventFlag = (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usUserEventFlag & (~(y))))

#define GET_USB_TYPE_C_RECONNECT(x)                         (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1ReconnectReq)
#define SET_USB_TYPE_C_RECONNECT(x)                         (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1ReconnectReq = _TRUE)
#define CLR_USB_TYPE_C_RECONNECT(x)                         (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1ReconnectReq = _FALSE)

#define GET_USB_TYPE_C_CONNECTION_DET(x)                    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1ConnectionDet)
#define SET_USB_TYPE_C_CONNECTION_DET(x)                    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1ConnectionDet = _TRUE)
#define CLR_USB_TYPE_C_CONNECTION_DET(x)                    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1ConnectionDet = _FALSE)

#define GET_USB_TYPE_C_ATTACH_STATUS(x)                     (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumCcAttachStatus)
#define SET_USB_TYPE_C_ATTACH_STATUS(x, y)                  (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumCcAttachStatus = (y))

#define GET_USB_TYPE_C_ATTACH_STATUS_CHG(x)                 (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1AttachStatusChange)
#define SET_USB_TYPE_C_ATTACH_STATUS_CHG(x)                 (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1AttachStatusChange = _TRUE)
#define CLR_USB_TYPE_C_ATTACH_STATUS_CHG(x)                 (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1AttachStatusChange = _FALSE)

#define GET_USB_TYPE_C_ALT_MODE_STATUS(x)                   (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumAltModeStatus)
#define SET_USB_TYPE_C_ALT_MODE_STATUS(x, y)                (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumAltModeStatus = (y))

#define GET_USB_TYPE_C_ALT_MODE_STATUS_CHG(x)               (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1AltModeStatusChange)
#define SET_USB_TYPE_C_ALT_MODE_STATUS_CHG(x)               (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1AltModeStatusChange = _TRUE)
#define CLR_USB_TYPE_C_ALT_MODE_STATUS_CHG(x)               (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1AltModeStatusChange = _FALSE)

#define GET_USB_TYPE_C_POWER_ROLE(x)                        (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumPowerRole)
#define SET_USB_TYPE_C_POWER_ROLE(x, y)                     (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumPowerRole = (y))

#define GET_USB_TYPE_C_PDO_VOLTAGE(x)                       (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usVoltage)
#define SET_USB_TYPE_C_PDO_VOLTAGE(x, y)                    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usVoltage = (y))

#define GET_USB_TYPE_C_PDO_CURRENT(x)                       (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usCurrent)
#define SET_USB_TYPE_C_PDO_CURRENT(x, y)                    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].usCurrent = (y))

#define GET_USB_TYPE_C_PDO_CHG_STATUS(x)                    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1PdoChg)
#define SET_USB_TYPE_C_PDO_CHG_STATUS(x)                    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1PdoChg = _TRUE)
#define CLR_USB_TYPE_C_PDO_CHG_STATUS(x)                    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1PdoChg = _FALSE)

#define GET_USB_TYPE_C_POWER_CONTROL_STATUS(x)              (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumPowerControlStatus)
#define SET_USB_TYPE_C_POWER_CONTROL_STATUS(x, y)           (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumPowerControlStatus = (y))

#define GET_USB_TYPE_C_EXT_PORT_CTRL_AC_ON_FLAG(x)          (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1ExtPortCtrlACOnFlag)
#define SET_USB_TYPE_C_EXT_PORT_CTRL_AC_ON_FLAG(x)          (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1ExtPortCtrlACOnFlag = _TRUE)
#define CLR_USB_TYPE_C_EXT_PORT_CTRL_AC_ON_FLAG(x)          (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1ExtPortCtrlACOnFlag = _FALSE)

#define GET_USB_TYPE_C_LOCAL_POWER_DETECT()                 (g_stUsbTypeCPowerInfo.b1LocalPowerDetectFlag)
#define SET_USB_TYPE_C_LOCAL_POWER_DETECT()                 (g_stUsbTypeCPowerInfo.b1LocalPowerDetectFlag = _TRUE)
#define CLR_USB_TYPE_C_LOCAL_POWER_DETECT()                 (g_stUsbTypeCPowerInfo.b1LocalPowerDetectFlag = _FALSE)

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#define GET_USB_TYPE_C_LENOVO_ALT_MODE_STATUS(x)            (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumLenovoAltModeStatus)
#define SET_USB_TYPE_C_LENOVO_ALT_MODE_STATUS(x, y)         (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumLenovoAltModeStatus = (y))

#define GET_USB_TYPE_C_LENOVO_DEVICE_TYPE(x)                (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumLenovoDeviceType)
#define SET_USB_TYPE_C_LENOVO_DEVICE_TYPE(x, y)             (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].enumLenovoDeviceType = (y))

#define GET_USB_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(x)    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1LenovoRcvDeviceTypeTimeout)
#define SET_USB_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(x)    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1LenovoRcvDeviceTypeTimeout = _TRUE)
#define CLR_USB_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(x)    (g_pstUsbTypeCStatus[SysUsbGetTypeCIndex(x)].b1LenovoRcvDeviceTypeTimeout = _FALSE)
#endif

#if(_BILLBOARD_SUPPORT == _ON)
#if((_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON) && (_BILLBOARD_SCALER_SUPPORT == _ON))
#define GET_USB_BB_USER_PROGRAM_ENABLE(x)                   (g_penumUsbBBUserProgramEnable[SysUsbGetTypeCIndex(x)])
#define SET_USB_BB_USER_PROGRAM_ENABLE(x, y)                (g_penumUsbBBUserProgramEnable[SysUsbGetTypeCIndex(x)] = (y))
#endif
//USB BillBoard Realated Macros
#define GET_USB_BB_STATE(x)                                 (g_pstUsbBillBoardStatus[SysUsbGetTypeCIndex(x)].enumBillBoardState)
#define SET_USB_BB_STATE(x, y)                              (g_pstUsbBillBoardStatus[SysUsbGetTypeCIndex(x)].enumBillBoardState = (y))

#define GET_USB_BB_ENABLE_STATUS()                          (g_ucUsbBBEnableStatus)
#define SET_USB_BB_ENABLE_STATUS()                          (g_ucUsbBBEnableStatus = _TRUE)
#define CLR_USB_BB_ENABLE_STATUS()                          (g_ucUsbBBEnableStatus = _FALSE)

#define GET_USB_DP_ALT_MODE_NOT_READY_CONFIRM(x)            (g_pstUsbBillBoardStatus[SysUsbGetTypeCIndex(x)].b1DpAltModeNotReadyConfirmFlag)
#define SET_USB_DP_ALT_MODE_NOT_READY_CONFIRM(x)            (g_pstUsbBillBoardStatus[SysUsbGetTypeCIndex(x)].b1DpAltModeNotReadyConfirmFlag = _TRUE)
#define CLR_USB_DP_ALT_MODE_NOT_READY_CONFIRM(x)            (g_pstUsbBillBoardStatus[SysUsbGetTypeCIndex(x)].b1DpAltModeNotReadyConfirmFlag = _FALSE)

#define GET_USB_BB_ENABLE_ALTMODE_READY_FLAG(x)             (g_pstUsbBillBoardStatus[SysUsbGetTypeCIndex(x)].b1BBEnableAltModeReadyFlag)
#define SET_USB_BB_ENABLE_ALTMODE_READY_FLAG(x)             (g_pstUsbBillBoardStatus[SysUsbGetTypeCIndex(x)].b1BBEnableAltModeReadyFlag = _TRUE)
#define CLR_USB_BB_ENABLE_ALTMODE_READY_FLAG(x)             (g_pstUsbBillBoardStatus[SysUsbGetTypeCIndex(x)].b1BBEnableAltModeReadyFlag = _FALSE)
#endif
#endif // #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_USB_HUB_SUPPORT == _ON)
// USB Hub Function Define
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
#define _USB_HUB_ENABLE_BY_TC_VBUS                          _ENABLE
#else
#define _USB_HUB_ENABLE_BY_TC_VBUS                          _DISABLE
#endif
#define _USB_HUB_TOGGLE_POWER_TO_U2                         _DISABLE
#define _USB_TYPE_C_ENABLE_USB3_TIME                        1000 // Timeout Enable USB3 After Port Attach

// USB Hub Related Macros
#define GET_USB_HUB_STATE(x)                                (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].enumUsbHubState)
#define SET_USB_HUB_STATE(x, y)                             (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].enumUsbHubState = (y))

#define GET_USB_HUB_INITIALIZED(x)                          (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1UsbInitialized)
#define SET_USB_HUB_INITIALIZED(x)                          (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1UsbInitialized = _TRUE)
#define CLR_USB_HUB_INITIALIZED(x)                          (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1UsbInitialized = _FALSE)

#define GET_USB_HUB_DSP_DEVICE_DETECT_FLG(x)                (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1SSDeviceDetecting)
#define SET_USB_HUB_DSP_DEVICE_DETECT_FLG(x)                (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1SSDeviceDetecting = _TRUE)
#define CLR_USB_HUB_DSP_DEVICE_DETECT_FLG(x)                (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1SSDeviceDetecting = _FALSE)

#define GET_USB_HUB_PLUG_DEVICE_CHANGE_FLG(x)               (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].enumHubDspChange)
#define SET_USB_HUB_PLUG_DEVICE_CHANGE_FLG(x, y)            (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].enumHubDspChange = (y))

#define GET_USB_HUB_CAPABILITY_SUPPORT()                    (g_enumUsbHubSupportMode)
#define SET_USB_HUB_CAPABILITY_SUPPORT(x)                   (g_enumUsbHubSupportMode = (x))
#define CLR_USB_HUB_CAPABILITY_SUPPORT()                    (g_enumUsbHubSupportMode = _USB_HUB_MODE_NONE)

#define GET_USB_HUB_PD_STATUS(x)                            (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].enumUsbPdStatus)
#define SET_USB_HUB_PD_STATUS(x, y)                         (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].enumUsbPdStatus = (y))

#define GET_USB_HUB_PS_STATUS(x)                            (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].enumUsbPsStatus)
#define SET_USB_HUB_PS_STATUS(x, y)                         (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].enumUsbPsStatus = (y))

#define GET_USB_HUB_OSD_CAPABILITY_CHG(x)                   (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1UsbOsdChange)
#define SET_USB_HUB_OSD_CAPABILITY_CHG(x)                   (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1UsbOsdChange = _TRUE)
#define CLR_USB_HUB_OSD_CAPABILITY_CHG(x)                   (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1UsbOsdChange = _FALSE)

#define GET_USB_HUB_FORCE_USB3_ENABLE(x)                    (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1ForceUsb3EnableFlag)
#define SET_USB_HUB_FORCE_USB3_ENABLE(x)                    (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1ForceUsb3EnableFlag = _TRUE)
#define CLR_USB_HUB_FORCE_USB3_ENABLE(x)                    (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1ForceUsb3EnableFlag = _FALSE)

#define GET_HUB_SWITCH_OSD_EVENT()                          (g_enumUsbHubSwitchOSDEvent)
#define SET_HUB_SWITCH_OSD_EVENT(x)                         (g_enumUsbHubSwitchOSDEvent = (x))

#define GET_USB_TYPE_B_ATTACH_STATUS(x)                     (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1TypeBAttachStatus)
#define SET_USB_TYPE_B_ATTACH_STATUS(x, y)                  (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1TypeBAttachStatus = (y))

#define GET_USB_TYPE_B_ATTACH_STATUS_CHG(x)                 (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1TypeBAttachStatusChange)
#define SET_USB_TYPE_B_ATTACH_STATUS_CHG(x)                 (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1TypeBAttachStatusChange = _TRUE)
#define CLR_USB_TYPE_B_ATTACH_STATUS_CHG(x)                 (g_pstUsbHubStatus[SysUsbHubGetIndex(x)].b1TypeBAttachStatusChange = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _BB_INITIAL_STATE = 0x00,
    _BB_UNATTACH_STATE = 0x01,
    _BB_ATTACHED_STATE = 0x02,
}EnumBillBoardState;

typedef struct
{
    EnumBillBoardState enumBillBoardState;
    BYTE b1DpAltModeNotReadyConfirmFlag  : 1;
    BYTE b1BBEnableAltModeReadyFlag : 1;
}StructBillBoardStatus;

typedef enum
{
    _USB_HUB_OFF = 0x00,
    _USB_HUB_INITIAL = 0x01,
    _USB_HUB_CHECK = 0x02,
}EnumUsbHubState;

typedef struct
{
    EnumUsbHubState enumUsbHubState;
    // -----------------------------
    EnumHubDspDetectStatus enumHubDspChange;
    // -----------------------------
    EnumUSBPSSupportStatus enumUsbPsStatus;
    EnumUSBPDSupportStatus enumUsbPdStatus;
    // -----------------------------
    EnumUSBHubPathEnable enumUSBHubPathEnable;
    // -----------------------------
    BYTE b1UsbInitialized : 1;
    // -----------------------------
    BYTE b1SSDeviceDetecting : 1;
    BYTE b4UsbHubStatus : 4;
    // -----------------------------
    BYTE b1UsbOsdChange : 1;
    // -----------------------------
    BYTE b1TypeBAttachStatus : 1;
    BYTE b1TypeBAttachStatusChange : 1;
    // -----------------------------
    BYTE b1ForceUsb3EnableFlag : 1;
}StructUsbHubStatus;


//--------------------------------------------------
// Enumerations of USB Hub OSD Event Judgement
//--------------------------------------------------
typedef enum
{
    _USB_HUB_STILL_AT_D0 = 0x00,
    _USB_HUB_STILL_AT_D1 = 0x01,
    _USB_HUB_STILL_AT_D2 = 0x02,
    _USB_HUB_STILL_AT_B = 0x0B,

    _USB_HUB_SWITCH_TO_D0 = 0x10,
    _USB_HUB_SWITCH_TO_D1 = 0x11,
    _USB_HUB_SWITCH_TO_D2 = 0x12,
    _USB_HUB_SWITCH_TO_B = 0x1B,

    _USB_HUB_SWITCH_NONE = 0xFF,
}EnumUsbHubSwitchOSDEvent;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// USB Type-C Related Functions
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
extern void SysUsbTypeCInitial(void);
extern void SysUsbTypeCPowerSwitch(EnumPowerAction enumSwitch);
extern void SysUsbTypeCHandler(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCUpdateSysModeStatus(void);
extern void SysUsbTypeCCheckAttachStatusChange(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCCheckAltModeReadyStatusChange(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbTypeCCheckPowerStatusChange(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD SysUsbTypeCGetAdaptorPower(void);
extern void SysUsbTypeCCheckAdaptorPowerExist(void);
extern bit SysUsbTypeCCheckAdaptorPowerChange(void);
extern void SysUsbTypeCSystemPowerManagement(void);
extern void SysUsbTypeCCheckSrcPdoChange(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo);
extern void SysUsbTypeCUpdatePortCtrlInitRdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCUpdatePortCtrlUnconstrainedPow(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCPortCtrlProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCAttachStatus SysUsbTypeCGetPortControllerCcAttach(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCOrientation SysUsbTypeCGetPortControllerOrientation(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCAltModeStatus SysUsbTypeCGetPortControllerAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbTypeCGetPortControllerPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbTypeCGetPortControllerExplicitContract(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbTypeCGetPortControllerFwVersion(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCPortCtrlFwVersion *pstTypeCFwVersion);
extern bit SysUsbTypeCGetPortControllerMultiFunctionChangeDone(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCCableInfoForDpcd SysUsbTypeCGetPortControllerCableInfoForDpcd(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE SysUsbTypeCGetPortControllerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO SysUsbTypeCGetPortControllerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern void SysUsbTypeCUpdateDisplayConfig(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCSetPortControllerMaxPower(EnumTypeCPcbPort enumTypeCPcbPort, WORD usMaxPower);
extern void SysUsbTypeCSetPortControllerSnkInfo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCSnkInfo stTypeCSnkInfo);
extern void SysUsbTypeCSetPortControllerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucSPRPdoCnt, BYTE ucEPRPdoCnt);
extern void SysUsbTypeCSetPortControllerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, StructTypeCUserPDO stTypeCUserPdo);
extern void SysUsbTypeCSetPortControllerInitRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserInitRDO stTypeCUserInitRdo);
extern void SysUsbTypeCSetPortControllerRdo(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCUserRDO stTypeCUserRdo);
extern void SysUsbTypeCSetPortControllerPdoByKernel(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern void SysUsbTypeCSetPortControllerFunctionSupport(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCFunctionSupport enumFunctionSupport);
extern void SysUsbTypeCSetPortControllerOperationMode(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCOperationMode enumOperationMode);
extern void SysUsbTypeCSetPortControllerStatusEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCStatusEvent stTypeCStatusEvent);
extern void SysUsbTypeCSetPortControllerAlertEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAlertEvent stTypeCAlertEvent);
#if(_DP_SUPPORT == _ON)
extern void SysUsbTypeCSetDpLaneMapping(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation);
extern void SysUsbTypeCDpLaneCountSwitch(EnumTypeCPcbPort enumTypeCPcbPort, EnumDpLaneCount enumDpLaneCount);
#endif
extern bit SysUsbTypeCCheckCapabilityChange(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCapChgStatus enumCapability);
extern void SysUsbTypeCPinAssignmentCapabilityChangeProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCCapabilityChangeProc(EnumTypeCPcbPort enumTypeCPcbPort, WORD usCapability);
extern void SysUsbTypeCPowerControlChangeProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerControlStatus enumPowerControlStatus);
extern bit SysUsbTypeCPowerControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerControlStatus enumPowerControlStatus);
extern void SysUsbTypeCSetPowerControlStatus(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerControlStatus enumPowerControlStatus);
extern void SysUsbTypeCPortCtrlPowerOnProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCSendSrcCapability(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCSendGetStatusMsg(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCCcFunctionChangeProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCcFunction enumCcFunction);
extern void SysUsbTypeCPowerDirectionChangeProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern void SysUsbTypeCClrCapabilityChangeFlag(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCCapChgStatus enumCapability);
extern bit SysUsbTypeCCheckUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCUserEvent enumUserEvent);
extern void SysUsbTypeCUserEventProc(EnumTypeCPcbPort enumTypeCPcbPort, WORD usUserEvent);
extern void SysUsbTypeCClrUserEventFlag(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCUserEvent enumUserEvent);
extern void SysUsbTypeCSetPdSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDSysEvent enumPdSysEvent);
extern void SysUsbTypeCUnattachReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbTypeCReconnect(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCWaitDpConfigUpdate(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCRestartConnectionDet(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbTypeCUpdatePortControllerConfig(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCSetOrientation(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCOrientation enumOrientation);
extern void SysUsbTypeCSetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment);
extern void SysUsbTypeCSetExplicitContract(EnumTypeCPcbPort enumTypeCPcbPort, bit bGetExplicitContract);
extern EnumDpLaneCount SysUsbTypeCGetAltModeLaneCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPinCfgType enumPinAssignment);
extern void SysUsbTypeCSetSysDataLaneCount(EnumTypeCPcbPort enumTypeCPcbPort, EnumDpLaneCount enumDpLaneCount);
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
extern void SysUsbTypeCAltModeHandler(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern EnumTypeCLenovoAltModeStatus SysUsbTypeCGetPortControllerLenovoAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCLenovoDeviceType SysUsbTypeCGetPortControllerLenovoDeviceType(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCActiveLenovoRcvDeviceTypeTimerEvent(EnumTypeCPcbPort enumTypeCPcbPort, WORD usTimeoutCnt);
extern void SysUsbTypeCCancelLenovoRcvDeviceTypeTimerEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCLenovoSysEvent SysUsbTypeCGetPortControllerLenovoSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCSetPortControllerLenovoDockingEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
extern EnumTypeCLenovoCheckBusyResult SysUsbTypeCCheckPortControllerLenovoDockingEventBusy(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern EnumTypeCAcerAltModeStatus SysUsbTypeCGetPortControllerAcerAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCAcerSysEvent SysUsbTypeCGetPortControllerAcerSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCSetPortControllerAcerUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCAcerUserEvent stAcerUserEvent);
extern EnumTypeCAcerBusyStatus SysUsbTypeCCheckPortControllerAcerUserEventBusy(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern EnumTypeCHpAltModeStatus SysUsbTypeCGetPortControllerHpAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCHpSysEvent SysUsbTypeCGetPortControllerHpSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCSetPortControllerHpUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCHpUserEvent stHpUserEvent);
extern EnumTypeCHpBusyStatus SysUsbTypeCCheckPortControllerHpUserEventBusy(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern EnumTypeCDellAltModeStatus SysUsbTypeCGetPortControllerDellAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCDellSysEvent SysUsbTypeCGetPortControllerDellSystemEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCSetPortControllerDellUserEvent(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCDellUserEvent stDellUserEvent);
extern void SysUsbTypeCSetPortControllerDellAltModeInitComplete(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCDellInitCompleteStatus enumDellInitCompleteStatus);
extern EnumTypeCDellBusyStatus SysUsbTypeCCheckPortControllerDellUserEventBusy(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCEnterDellAltModeTimeOut SysUsbTypeCGetPortControllerEnterDellAltModeTimeOut(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

// USB Billboard Functions
#if(_BILLBOARD_SUPPORT == _ON)
extern void SysUsbBillboardStartTimer(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbBillboardCancelTimer(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbBillboardHandler(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbBillboardProcess(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
extern void SysUsbBillboardCustomCommand(StructUsbBillboardCustomCommandInfo *pststUsbBillboardCustomCommandInfo);
#endif // End of #if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
#endif // End of #if(_BILLBOARD_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

// USB Hub & Repeater Functions
#if(_USB_HUB_SUPPORT == _ON)
extern BYTE SysUsbHubGetIndex(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbHubInitial(void);
extern void SysUsbHubStartForceEnableTimer(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbHubCancelForceEnableTimer(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbHubPathStartCondition(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbHubReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbHubHandler(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbHubInitialStateProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbHubCheckStateProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbHubJudgeOSDEvent(void);
extern void SysUsbHubTypeBProcess(void);
extern void SysUsbHubConfigU3ByPinAssignment(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbHubJudgeCpModeCondition(EnumTypeCPinCfgType enumTypeCPinCfgType, EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbHubJudgeU2U3ModeCapability(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbHubReStart(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumUSBHubPathEnable SysUsbJudgeHubPathEnable(EnumUsbHubOSDResult enumUsbHubOSDResult, EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbHubDisableUSBPath(void);
extern bit SysUsbHubGetUfpPortAttachStatus(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbHubGetPortAttachStatusChange(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbHubPowerSwitch(EnumPowerAction enumSwitch);
extern void SysUsbHubDxPortPowerSwitchProc(EnumPowerAction enumSwitch, EnumTypeCPcbPort enumTypeCPcbPort);
#if(_USB3_REPEATER_SUPPORT == _ON)
extern void SysUsbRepeaterDisableAllFsm(void);
extern EnumTypeCOrientation SysUsbHubGetUfpOrientationStatus(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPinCfgType SysUsbHubGetUfpPinAssignmentStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

#if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
extern void SysUsbHubSetSSModebySMBus(EnumTypeCPcbPort enumTypeCPcbPort, bit bEn);
extern void SysUsbHubCommunicationControl(EnumTypeCPcbPort enumTypeCPcbPort, bit bEn);
extern void SysUsbHubDetectDspProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD SysUsbHubGetU3ReadyDelayTime(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif // End of #if(_USB_HUB_SUPPORT == _ON)

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
extern void SysUsbU2HostAcOnInitial(void);
extern void SysUsbU2HostHandler(void);
extern void SysUsbU2HostModeHandler(void);
extern void SysUsbU2HostCommunication(void);
extern void SysUsbU2HostRootHubRemoveDevice(EnumUsbU2HostOwner enumOwner);
extern void SysUsbU2HostActiveDetConnectDurationTimerEvent(void);
extern void SysUsbU2HostDataProcHandler(EnumUsbU2HostOwner enumOwner);
extern void SysUsbU2HostReconnect(void);
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
extern void SysUsbU2HostBulkTransOperationDataHandler(EnumUsbU2HostOwner enumOwner);
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)

#if(_USB2_HOST_OHCI_COLOR_ANALYZER_SUPPORT == _ON)
extern void SysUsbU2HostColorOperationDataHandler(void);
#endif
#endif // End of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
#endif // End of #if(_USB2_HOST_SUPPORT == _ON)
#endif // End of #if(_USB_SUPPORT == _ON)

#endif // End of #ifndef __SYS_USB_H__
