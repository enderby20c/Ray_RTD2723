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
// ID Code      : ScalerUsb3RepeaterMac.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_USB3_REPEATER_MAC_H__
#define __SCALER_USB3_REPEATER_MAC_H__

#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
//****************************************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************************************
#define GET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(x)                    (g_pbUsb3RepeaterMacU3EnablePdNoResponse[ScalerTypeCGetTypeCIndex(x)])
#define SET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(x)                    (g_pbUsb3RepeaterMacU3EnablePdNoResponse[ScalerTypeCGetTypeCIndex(x)] = _TRUE)
#define SET_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE_WDINT(x)              (g_pbUsb3RepeaterMacU3EnablePdNoResponse[ScalerTypeCGetTypeCIndex_WDINT(x)] = _TRUE)
#define CLR_USB_REPEATER_MAC_U3_ENBALE_PD_NO_RESPONSE(x)                    (g_pbUsb3RepeaterMacU3EnablePdNoResponse[ScalerTypeCGetTypeCIndex(x)] = _FALSE)


//****************************************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************************************


//****************************************************************************************************
// VARIABLE EXTERN
//****************************************************************************************************


//****************************************************************************************************
// FUNCTION EXTERN
//****************************************************************************************************
#endif

#endif // End of #ifndef __SCALER_USB3_REPEATER_MAC_H__
