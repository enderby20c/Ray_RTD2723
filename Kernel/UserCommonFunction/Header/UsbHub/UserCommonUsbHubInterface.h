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
// ID Code      : UserCommonUsbHubInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB_HUB_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumUsbHubOSDResult UserCommonUsbHubGetOSDSelectResult(void);
extern BYTE UserCommonUsbHubPathEnableCond(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbHubPowerControl(EnumTypeCPcbPort enumTypeCPcbPort, bit bEnable);
extern void UserCommonUsbHubSwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumUSBHubPathEnable enumUSBHubPathEnable);
extern void UserCommonUsbHubTypeBProcess(void);
extern WORD UserCommonUsbHubDisableDurationTime(void);
#if(_USB3_REPEATER_SUPPORT == _ON)
extern EnumUSBPDSupportStatus UserCommonUsbHubGetUSBPDSupportStatus(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumUSBPSSupportStatus UserCommonUsbHubGetUSBPSSupportStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif  // End of #if(_USB3_REPEATER_SUPPORT == _ON)

#if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
extern EnumUsbHubSetU3ModeFailureType UserCommonUsbHubSetSSMode(EnumTypeCPcbPort enumTypeCPcbPort, bit bEn);
extern EnumHubDspDetectStatus UserCommonUsbHubDetectDFPStatus(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbHubDspChangeProc(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumUsbHubCtrMode UserCommonUsbHubGetControlMode(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD UserCommonUsbHubSetPollingStep(EnumTypeCPcbPort enumTypeCPcbPort);
#endif  // End of #if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
#endif  // End of #if(_USB_HUB_SUPPORT == _ON)
