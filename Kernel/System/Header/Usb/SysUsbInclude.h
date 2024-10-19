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
// ID Code      : SysUsbInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of TypeC Cable Status Change
//--------------------------------------------------
typedef enum
{
    _USB_CABLE_UNPLUG = 0x00,
    _USB_CABLE_PLUG = 0x01,
    _USB_CABLE_UNCHANGE = 0xFF,
} EnumUsbCableChangeStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysUsbInitial(void);
extern void SysUsbHandler(void);
extern void SysUsbPowerSwitch(EnumPowerAction enumSwitch);
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_TYPE_C_CABLE_STATUS_CHANGE_BY_ALT_MODE_SUPPORT == _ON)
extern bit SysUsbTypeCGetAltModeStatusChange(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern void SysUsbTypeCSetLocalPowerDetection(void);
extern void SysUsbTypeCConnectionDetCtrl(EnumTypeCPcbPort enumTypeCPcbPort, bit bEn);
extern StructTypeCDpStatusInfo SysUsbTypeCGetDpStatusInfo(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_DP_SUPPORT == _ON)
extern bit SysUsbTypeCRxCheckTypeCPortControllerExist(EnumInputPort enumInputPort);
#endif

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern void SysUsbTypeCSetLenovoRcvDeviceTypeTimeout(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif

#if(_BILLBOARD_SUPPORT == _ON)
extern void SysUsbBillboardInitial(void);
extern void SysUsbBillboardControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumBillboardCtrl enumAtion);
extern void SysUsbBillBoardSetTimerEventFlag(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_USB_HUB_SUPPORT == _ON)
extern void SysUsbHubSetForceEnableTimerEventFlag(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_USB3_REPEATER_SUPPORT == _ON)
extern EnumUsbCableChangeStatus SysUsbHubGetAttachStatusChange(void);
extern EnumUSBPSSupportStatus SysUsbHubJudgeUsbPSStatus(void);
extern EnumUSBPDSupportStatus SysUsbHubJudgeUsbPDStatus(void);
#endif // End of #if(_USB3_REPEATER_SUPPORT == _ON)
#endif // End of #if(_USB_HUB_SUPPORT == _ON)

#if(_USB2_HOST_SUPPORT == _ON)
#if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
extern BYTE SysUsbU2HostWorkOnCommunication(void);
#endif // End of #if(_USB2_HOST_FW_SUPPORT_TYPE == _FW_MAIN_LOOP)
#endif // End of #if(_USB2_HOST_SUPPORT == _ON)
#endif // End of #if(_USB_SUPPORT == _ON)
