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
// ID Code      : UserCommonUsbHubRtsInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Device Attached Detect
//--------------------------------------------------
typedef enum
{
    _HUB_DSP_DEVICE_NOT_ATTACH = 0x00,
    _HUB_DSP_DEVICE_ATTACH_BY_U2 = 0x01,
    _HUB_DSP_DEVICE_ATTACH_BY_U3 = 0x02,
}EnumHubDspDeviceAttachDetect;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_USB_HUB_RTS_SUPPORT == _ON)
#if(_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
extern EnumHubDspDeviceAttachDetect UserCommonUsbHubRtsDspGetUsbAttachInfo(EnumHubDsp enumHubDsp);
#endif // #if(_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
#endif // #if(_USB_HUB_RTS_SUPPORT == _ON)

