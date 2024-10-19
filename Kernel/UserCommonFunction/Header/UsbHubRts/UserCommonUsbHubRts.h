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
// ID Code      : UserCommonUsbHubRts.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_USB_HUB_RTS_H__
#define __USER_COMMON_USB_HUB_RTS_H__

#if(_USB_HUB_RTS_SUPPORT == _ON)
#if(_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#define GET_USB_HUB_RTS_DSP_U2_INFO()                           (g_ucUsbHubRtsU2InfoByDsp)
#define SET_USB_HUB_RTS_DSP_U2_INFO(x)                          (g_ucUsbHubRtsU2InfoByDsp = (x))
#define GET_USB_HUB_RTS_DSP_U3_INFO()                           (g_ucUsbHubRtsU3InfoByDsp)
#define SET_USB_HUB_RTS_DSP_U3_INFO(x)                          (g_ucUsbHubRtsU3InfoByDsp = (x))
#define GET_USB_HUB_RTS_DSP0_INFO()                             (g_ucUsbHubRtsDSP0RawInfo)
#define SET_USB_HUB_RTS_DSP0_INFO(x)                            (g_ucUsbHubRtsDSP0RawInfo = (x))
#define GET_USB_HUB_RTS_DSP1_INFO()                             (g_ucUsbHubRtsDSP1RawInfo)
#define SET_USB_HUB_RTS_DSP1_INFO(x)                            (g_ucUsbHubRtsDSP1RawInfo = (x))
#define GET_USB_HUB_RTS_DSP2_INFO()                             (g_ucUsbHubRtsDSP2RawInfo)
#define SET_USB_HUB_RTS_DSP2_INFO(x)                            (g_ucUsbHubRtsDSP2RawInfo = (x))
#define GET_USB_HUB_RTS_DSP3_INFO()                             (g_ucUsbHubRtsDSP3RawInfo)
#define SET_USB_HUB_RTS_DSP3_INFO(x)                            (g_ucUsbHubRtsDSP3RawInfo = (x))
#define GET_USB_HUB_RTS_DSP_U2_CHANGE()                         (g_bUsbHubRtsDspU2Change)
#define SET_USB_HUB_RTS_DSP_U2_CHANGE(x)                        (g_bUsbHubRtsDspU2Change = (x))
#define GET_USB_HUB_RTS_DSP_U3_CHANGE()                         (g_bUsbHubRtsDspU3Change)
#define SET_USB_HUB_RTS_DSP_U3_CHANGE(x)                        (g_bUsbHubRtsDspU3Change = (x))
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE UserCommonUsbHubRtsGetHubAddr(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbHubRtsDspU2InfoChange(void);
extern void UserCommonUsbHubRtsDspU3InfoChange(void);
#endif // End of #if(_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
#endif // End of #if(_USB_HUB_RTS_SUPPORT == _ON)


#endif // End of #ifndef __USER_COMMON_USB_HUB_RTS_H__
