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
// ID Code      : UserCommonUsbHubUserInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB_HUB_USER_SERIES_SUPPORT == _ON)

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
#if(_BILLBOARD_USER_HUB_SUPPORT == _ON)
extern void UserCommonUsbHubUserBillboardControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumBillboardCtrl enumAtion);
extern void UserCommonUsbHubUserBillboardHandler(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif  // End of #if(_USB_HUB_USER_SERIES_SUPPORT == _ON)

