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
// ID Code      : UserCommonUsbTypeCEmbeddedInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON))

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
extern void UserCommonUsbTypeCEmbeddedGetVbusProtectInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucPdoIndex, StructTypeCVbusProtectInfo *pstTypeCVbusProtectInfo);
extern BYTE UserCommonUsbTypeCEmbeddedGetVbusDischargeCount(EnumTypeCPcbPort enumTypeCPcbPort);
#endif // End of #if((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON))
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

