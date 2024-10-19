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
// ID Code      : UserCommonUsbHubUser.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_USBUSER__

#include "UserCommonInclude.h"
#include "UsbHubUser/UserCommonUsbHubUser.h"

#if(_USB_HUB_USER_SERIES_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set User into SS Mode
// Input Value  : None
// Output Value : _USB_HUB_SET_U3_MODE_SUCCESS / _USB_HUB_SET_U3_MODE_FAIL
//--------------------------------------------------
EnumUsbHubSetU3ModeFailureType UserCommonUsbHubUserSetSSMode(EnumTypeCPcbPort enumTypeCPcbPort, bit bEn)
{
    return UserCommonUsbHubSetSSModeByUser(enumTypeCPcbPort, bEn);
}

//--------------------------------------------------
// Description  : Detect Hub DFP Status
// Input Value  : enumInputPort --> Input Port
// Output Value : Return DFP Status Change or Not
//--------------------------------------------------
EnumHubDspDetectStatus UserCommonUsbHubUserDetectDFPStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    return UserCommonUsbHubGetDFPStatus(enumTypeCPcbPort);
}
#endif

#if(_BILLBOARD_USER_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : For User Hub to Control Billboard
// Input Value  : enumAtion : _USB_BB_DISABLE / _USB_BB_ENABLE
// Output Value : None
//--------------------------------------------------
void UserCommonUsbHubUserBillboardControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumBillboardCtrl enumAtion)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    // Call User Function for User to Enable / Disable Hub Billboard
    UserInterfaceUsbHubBillboardControl(enumInputPort, enumAtion);
}

//--------------------------------------------------
// Description  : For User Hub to Execute BillboardHandler
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void UserCommonUsbHubUserBillboardHandler(EnumTypeCPcbPort enumTypeCPcbPort)
{
    EnumInputPort enumInputPort = SysUsbTypeCConvertToDxPort(enumTypeCPcbPort);

    // Call User Function for User to Execute Hub BillboardHandler
    UserInterfaceUsbHubBillboardHandler(enumInputPort);
}
#endif // End of #if(_BILLBOARD_USER_HUB_SUPPORT == _ON)
#endif // End of #if(_USB_HUB_USER_SERIES_SUPPORT == _ON)
