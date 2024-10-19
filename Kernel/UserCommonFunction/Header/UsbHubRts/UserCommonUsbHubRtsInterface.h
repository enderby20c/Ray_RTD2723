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
// ID Code      : UserCommonUsbHubRtsInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB_HUB_RTS_SUPPORT == _ON)

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
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_BILLBOARD_RTS_HUB_SUPPORT == _ON)
extern void UserCommonUsbHubRtsBillboardControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumBillboardCtrl enumAtion);
extern void UserCommonUsbHubRtsBillboardHandler(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif
#endif  // End of #if(_USB_HUB_RTS_SUPPORT == _ON)
