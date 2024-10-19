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
// ID Code      : RTD2020UserInterfaceUsbHub.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_OSD_TYPE == _REALTEK_2020_OSD)
#if(_USB_HUB_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_USER_USB_HUB_OSD_SWITCH_PORT_RESULT()            (g_enumUsbHubUserOSDResult)
#define SET_USER_USB_HUB_OSD_SWITCH_PORT_RESULT(x)           (g_enumUsbHubUserOSDResult = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern EnumUsbHubOSDResult g_enumUsbHubUserOSDResult;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif // End of #if(_USB_HUB_SUPPORT == _ON)
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
