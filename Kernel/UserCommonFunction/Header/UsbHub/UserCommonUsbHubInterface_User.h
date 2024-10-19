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
// ID Code      : UserCommonUsbHubInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of USB Hub Mode
//--------------------------------------------------
typedef enum
{
    _USB_HUB_MODE_NONE = 0,
    _USB_HUB_MODE_U2 = 1,
    _USB_HUB_MODE_U3 = 2,
}EnumUsbHubMode;

//--------------------------------------------------
// Enumerations of USB Hub Control Mode
//--------------------------------------------------
typedef enum
{
    _USB_HUB_CTR_BY_KERNEL = _FALSE,
    _USB_HUB_CTR_BY_USER = _TRUE,
}EnumUsbHubCtrMode;

//--------------------------------------------------
// Enumerations of USB Hub Set U3 Mode Status
//--------------------------------------------------
typedef enum
{
    _USB_HUB_SET_U3_MODE_FAIL = _FAIL,
    _USB_HUB_SET_U3_MODE_SUCCESS = _SUCCESS,
}EnumUsbHubSetU3ModeFailureType;

//--------------------------------------------------
// Enumerations of Hub DSP Device Detect
//--------------------------------------------------
typedef enum
{
    _HUB_DSP_DEVICE_NO_CHANGE = 0x00,
    _HUB_DSP_DEVICE_CHANGE = 0x01,
}EnumHubDspDetectStatus;

//--------------------------------------------------
// Enumerations of Type-C Adjust Src Cap When Hub Device Count Change
//--------------------------------------------------
typedef enum
{
    _TYPE_C_HUB_ADJ_SRC_CAP_ENABLE = 0x00,
    _TYPE_C_HUB_ADJ_SRC_CAP_DISABLE = 0x01,
}EnumTypeCHubAdjSrcCap;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

