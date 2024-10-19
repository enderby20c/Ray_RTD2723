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
// ID Code      : SysUsbInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// System Source Power Information
//--------------------------------------------------
#define GET_SYSTEM_REMAIN_POWER()                       (WORD)(g_stUsbTypeCPowerInfo.usSystemRemainPower)
#define SET_SYSTEM_REMAIN_POWER(x)                      (g_stUsbTypeCPowerInfo.usSystemRemainPower = (x))

//--------------------------------------------------
// Type-C Port Information
//--------------------------------------------------
#define GET_TYPE_C_POWER_VALUE(x)                       (WORD)(g_stUsbTypeCPowerInfo.pusTypeCPower[SysUsbGetTypeCIndex(x)])
#define SET_TYPE_C_POWER_VALUE(x, y)                    (g_stUsbTypeCPowerInfo.pusTypeCPower[SysUsbGetTypeCIndex(x)] = (y))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Type-C Port Controller Power On Reconnect Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PORT_CTRL_NO_RECONNECT = 0x00,
    _TYPE_C_PORT_CTRL_RECONNECT = 0x01,
}EnumTypeCPortCtrlReconnectStatus;

//--------------------------------------------------
// Enumerations of Type-C Capability Change Info
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PIN_ASSIGNMENT_CAP_CHG = _BIT0,
    _TYPE_C_SEND_SRC_CAP = _BIT1,                       // Notify Kernel to Send Source Cap
    _TYPE_C_SPM_CAP_CHG = _BIT2,
    _TYPE_C_CC_FUNC_CHG_DISABLE = _BIT3,                // If Local Power Not Exist, CC Function Disable is equal to AC Off / On
    _TYPE_C_CC_FUNC_CHG_ENABLE = _BIT4,
    _TYPE_C_POWER_DIRECTION_CHG_TO_SRC = _BIT5,
    _TYPE_C_POWER_DIRECTION_CHG_TO_SNK = _BIT6,
    _TYPE_C_POWER_CHG_TO_OFF = _BIT7,
    _TYPE_C_POWER_CHG_TO_ON = _BIT8,
    _TYPE_C_ALERT_EVENT_CHG = _BIT9,
    _TYPE_C_STATUS_EVENT_CHG = _BIT10,
    _TYPE_C_UPDATE_SRC_CAP = _BIT11,                    // Notify Kernel to Update Source Cap to Embedded Port Ctrl / RTS Port Ctrl / User Port Ctrl
    _TYPE_C_SEND_GET_STATUS_MSG = _BIT12,               // Notify Kernel to Send Get_Status Message
    _TYPE_C_ALL_STATUS_CHG = 0xFFF,
}EnumTypeCCapChgStatus;

//--------------------------------------------------
// Enumerations of Type-C User Event
//--------------------------------------------------
typedef enum
{
    _TYPE_C_USER_EVENT_NONE = 0x00,                     // No Request Event to Embedded PD Ctrl
    _TYPE_C_USER_EVENT_SEND_HARD_RESET = _BIT0,         // Request Embedded PD Ctrl to Send Hard Reset
    _TYPE_C_USER_EVENT_ALL = 0xFF,                      // All User Event
}EnumTypeCUserEvent;

//--------------------------------------------------
// Enumerations of USB Support Under Power Down
//--------------------------------------------------
typedef enum
{
    _PD_USB3_ENABLE = 0x01,
    _PD_USB2_ENABLE = 0x02,
    _PD_USB_DISABLE = 0x03,
}EnumUSBPDSupportStatus;

//--------------------------------------------------
// Enumerations of USB Support Under Power Saving
//--------------------------------------------------
typedef enum
{
    _PS_USB3_ENABLE = 0x01,
    _PS_USB2_ENABLE = 0x02,
    _PS_USB_DISABLE = 0x03,
}EnumUSBPSSupportStatus;

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of U2 Host Event Type
//--------------------------------------------------
typedef enum
{
    _U2HOST_FILE_NAME_SEARCH_EVENT = 0x01,
    _U2HOST_FW_VERSION_CHECK_EVENT = 0x02,
    _U2HOST_FW_UPDATE_EVENT = 0x03,
    _U2HOST_EVENT_COUNT,
    _U2HOST_NONE_EVENT = 0xFF,
}EnumUSB2HostEventType;

//--------------------------------------------------
// Enumerations of U2 Host OSD Event Type
//--------------------------------------------------
typedef enum
{
    _U2HOST_OSD_FW_UPDATE_ENABLE = 0x01,
    _U2HOST_OSD_FW_UPDATE_START = 0x02,
    _U2HOST_OSD_FW_REBOOT_ENABLE = 0x03,
    _U2HOST_EVENT_CHANGE_COUNT,
}EnumUSB2HostEventChangeType;

//--------------------------------------------------
// Enumerations of U2 Host Event Result
//--------------------------------------------------
typedef enum
{
    _U2HOST_EVENT_NO_ACTION = 0x01,
    _U2HOST_EVENT_ON_GOING = 0x02,
    _U2HOST_EVENT_PASS = 0x03,
    _U2HOST_EVENT_FAIL = 0x04,
}EnumUSB2HostEventResult;
#endif // End of #if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT==_ON)
#endif // End of #if(_USB2_HOST_SUPPORT==_ON)

//--------------------------------------------------
// Enumerations of External Port Controller Fw Version
//--------------------------------------------------
typedef struct
{
    BYTE ucMainVersion;
    BYTE ucSubVersion1;
    BYTE ucSubVersion2;
}StructTypeCPortCtrlFwVersion;

//--------------------------------------------------
// Structure of System Power Management Port Power
//--------------------------------------------------
typedef struct
{
    WORD usSystemRemainPower;
    WORD pusTypeCPower[_TYPE_C_PORT_VALID];
    BYTE b1LocalPowerDetectFlag : 1;
}StructUsbTypeCPowerInfo;

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern EnumTypeCPcbPort g_penumUsbTypeCPcbPort[_TYPE_C_PORT_VALID];
extern StructUsbTypeCPowerInfo g_stUsbTypeCPowerInfo;
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE SysUsbGetTypeCIndex(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPcbPort SysUsbDxConvertToTypeCPort(EnumInputPort enumInputPort);
extern EnumTypeCPcbPort SysUsbPxConvertToTypeCPort(EnumOutputPort enumOutputPort);
extern EnumInputPort SysUsbTypeCConvertToDxPort(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumOutputPort SysUsbTypeCConvertToPxPort(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCRxSetCapabilityChangeFlag(EnumInputPort enumInputPort, EnumTypeCCapChgStatus enumCapability);
extern void SysUsbTypeCTxSetCapabilityChangeFlag(EnumOutputPort enumOutputPort, EnumTypeCCapChgStatus enumCapability);

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
extern EnumTypeCLocalPowerExist SysUsbTypeCGetLocPowExist(void);
extern void SysUsbTypeCUpdatePortCtrlRdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCStatusEvent SysUsbTypeCGetPartnerStatusInfo(EnumTypeCPcbPort enumTypeCPcbPort);
extern StructTypeCAlertEvent SysUsbTypeCGetPartnerAlertInfo(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCDataRole SysUsbTypeCGetDataRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPowerRole SysUsbTypeCGetPowerRole(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE SysUsbTypeCGetPortPartnerFlag(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE SysUsbTypeCGetPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO SysUsbTypeCGetPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern BYTE SysUsbTypeCGetPartnerPdoCnt(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO SysUsbTypeCGetPartnerPdo(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern void SysUsbTypeCGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent);
extern StructTypeCUserPDO SysUsbTypeCGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCCablePdCapability SysUsbTypeCGetCablePdCapability(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCUFPProductType SysUsbTypeCGetUFPProductType(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCDFPProductType SysUsbTypeCGetDFPProductType(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD SysUsbTypeCGetCableMaxCurrent(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPDPortCtrlEvent SysUsbTypeCGetPortCtrlEvent(EnumTypeCPcbPort enumTypeCPcbPort);
extern void SysUsbTypeCClrPortCtrlEvent(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDPortCtrlEvent enumTypeCPortCtrlEvent);
extern void SysUsbTypeCSetUserEventFlag(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCUserEvent enumUserEvent);
extern bit SysUsbTypeCGetFwVersion(EnumTypeCPcbPort enumTypeCPcbPort, StructTypeCPortCtrlFwVersion *pstTypeCFwVersion);
extern BYTE SysUsbTypeCGetPortOperationMode(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit SysUsbTypeCRxGetCcAttach(EnumInputPort enumInputPort);
extern bit SysUsbTypeCRxGetAltModeReady(EnumInputPort enumInputPort);
extern EnumTypeCPinCfgType SysUsbTypeCRxGetPinAssignment(EnumInputPort enumInputPort);
extern EnumTypeCOrientation SysUsbTypeCRxGetOrientation(EnumInputPort enumInputPort);
extern bit SysUsbTypeCTxGetCcAttach(EnumOutputPort enumOutputPort);
extern bit SysUsbTypeCTxGetAltModeReady(EnumOutputPort enumOutputPort);
extern EnumTypeCPinCfgType SysUsbTypeCTxGetPinAssignment(EnumOutputPort enumOutputPort);
extern EnumTypeCOrientation SysUsbTypeCTxGetOrientation(EnumOutputPort enumOutputPort);
#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern EnumTypeCLenovoAltModeStatus SysUsbTypeCGetLenovoAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCLenovoDeviceType SysUsbTypeCGetLenovoDeviceType(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern EnumTypeCAcerAltModeStatus SysUsbTypeCGetAcerAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern EnumTypeCHpAltModeStatus SysUsbTypeCGetHpAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
extern EnumTypeCDellAltModeStatus SysUsbTypeCGetDellAltModeReady(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCEnterDellAltModeTimeOut SysUsbTypeCGetEnterDellAltModeTimeOut(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif
#if(_BILLBOARD_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
extern EnumBillboardCustomEvent SysUsbBillboardGetCustomEvent(void);
extern void SysUsbBillboardClrCustomEvent(EnumBillboardCustomEvent enumBillboardCustomEvent);
#endif // End of #if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
#endif // End of #if(_BILLBOARD_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_USB_HUB_SUPPORT == _ON)
extern bit SysUsbHubGetCableAttachStatus(EnumUsbHubOSDResult enumUsbHubOSDResult);
#if(_USB3_REPEATER_SUPPORT == _ON)
extern bit SysUsbHubC2ACableAttachStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
extern void SysUsbU2HostSetEventChange(EnumUSB2HostEventChangeType enumUSB2HostEventChangeType, BYTE ucEnable);
extern BYTE SysUsbU2HostGetEventChange(void);
extern EnumUSB2HostEventResult SysUsbU2HostGetEventStatus(EnumUSB2HostEventType enumUSB2HostEventType);
extern void SysUsbU2HostClearEventStatus(EnumUSB2HostEventType enumUSB2HostEventType);
extern BYTE SysUsbU2HostFwUpdateProgressRate(void);
#endif // End of #if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_FREE_RTOS)
#if(_USB2_HOST_EHCI_SUPPORT == _ON)
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
extern void SysUsbU2HostIspInital(void);
#endif // End of #if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)
#endif // End of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_FREE_RTOS)
#endif // End of #if(_USB2_HOST_SUPPORT == _ON)
#endif // End of #if(_USB_SUPPORT == _ON)

#if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
extern EnumTypeCCcDetectStatus SysUsbTypeCGetCcPinStatus(EnumTypeCEmbeddedList enumEmbTypeCIndex, EnumTypeCChannel enumTypeCChannel);
#endif  // End of #if(_TYPE_C_GPIO_MODE_SUPPORT == _ON)
