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
// ID Code      : UserCommonUsbHubInclude.h No.0000
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
#if(_USB_HUB_COMMUNICATION_SUPPORT == _ON)
extern EnumUsbHubSetU3ModeFailureType UserCommonUsbHubSetSSModeByUser(EnumTypeCPcbPort enumTypeCPcbPort, bit bEn);
extern EnumHubDspDetectStatus UserCommonUsbHubGetDFPStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif  // End of #if(_USB_HUB_SUPPORT == _ON)

