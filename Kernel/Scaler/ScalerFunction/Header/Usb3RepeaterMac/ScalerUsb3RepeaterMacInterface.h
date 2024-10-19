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
// ID Code      : ScalerUsb3RepeaterMacInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
#define _USB_POWER_CUT_HW_MODE                          0x01
#define _USB_POWER_CUT_FW_MODE                          0x02
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _USB3_RETIMER_ENTER_P3_PS = 0x00,
    _USB3_RETIMER_EXIT_P3_PS = 0x01,
    _USB3_RETIMER_AT_P3_PS = 0x02,
    _USB3_RETIMER_NO_ACTION = 0xFF,
}EnumUsb3RetimerP3State;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerUsb3RepeaterMacInitial(EnumTypeCOrientation enumOrientation, EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RepeaterMacEnable(EnumTypeCPcbPort enumTypeCPcbPort, bit bEnable);
extern void ScalerUsb3RepeaterMacSetU3GenSpeed(BYTE ucUsbHubU3Speed);
extern void ScalerUsb3RepeaterMacSetU3LaneCount(BYTE ucUsbHubU3Lane);
extern void ScalerUsb3RepeaterMacCleanU3Capability(void);
extern void ScalerUsb3RepeaterMacSetU3HubOSDResult(EnumUsbHubOSDResult enumUsbHubOSDResult);
extern void ScalerUsb3RepeaterMacSetPdNoResponse(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RepeaterMacSetPdNoResponse_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerUsb3RepeaterMacCleanPdNoResponse(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit ScalerUsb3RepeaterMacGetPdNoResponse(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
extern void ScalerUsb3RepeaterMacMuxSwitchControl(EnumInputPort enumInputPort, EnumUSBHubPathEnable enumUSBHubPathEnable);
#endif // End of #if(_HW_USB3_REPEATER_MAC_MUX_TYPE == _ON)
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
extern void ScalerUsb3RepeaterMacClearLowPowerStateStatus(void);
extern EnumUsb3RetimerP3State ScalerUsb3RepeaterMacGetLowPowerStateStatus(void);
extern void ScalerUsb3RepeaterMacSetAtLowPowerStateStatus(void);
extern void ScalerUsb3RepeaterMacSetPowerCutMode(BYTE ucUsbPowerCutMode);
extern bit ScalerUsb3RepeaterMacGetDetectNSQFlag(void);
extern void ScalerUsb3RepeaterMacDisableU3IRQ(void);
extern bit ScalerUsb3RepeaterMacGetPinDEnterFakeSavingU3Late(void);
extern void ScalerUsb3RepeaterMacClearPinDEnterFakeSavingU3Late(void);
#endif
#if(_USB3_RETIMER_MAC_SUPPORT == _ON)
extern bit ScalerUsb3RepeaterMacBlrPathSupport(void);
#endif // end of #if(_USB3_RETIMER_MAC_SUPPORT == _ON)
#endif
