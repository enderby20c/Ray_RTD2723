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
// ID Code      : UserCommonUsbInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_USB_SUPPORT == _ON) || (_TYPE_C_PORT_CTRL_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// Definitions of FW Usage Counters
#if(_PORT_CTRL_EXT_PD3_1_EPR_SUPPORT == _ON)
#define _RTS_MAX_DATA_OBJ_CNT                               11
#else
#define _RTS_MAX_DATA_OBJ_CNT                               7
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumUsbHubMode UserCommonUsbGetOsdU3Mode(EnumTypeCPcbPort enumTypeCPcbPort);
#endif // End of #if((_USB_SUPPORT == _ON) || (_TYPE_C_PORT_CTRL_SUPPORT == _ON))

