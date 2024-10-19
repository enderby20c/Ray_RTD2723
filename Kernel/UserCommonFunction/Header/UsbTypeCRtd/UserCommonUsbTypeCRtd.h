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
// ID Code      : UserCommonUsbTypeCRtd.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_USB_TYPE_CRTD_H__
#define __USER_COMMON_USB_TYPE_CRTD_H__

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTD_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _TYPE_C_RTD_PORT_CTRL_STATUS_START_ADDR             0x00
#define _TYPE_C_RTD_PORT_CTRL_STATUS_SIZE                   4

#define _TYPE_C_RTD_SET_PIN_ASSIGNMENT_START_ADDR           0x00
#define _TYPE_C_RTD_SET_PIN_ASSIGNMENT_SIZE                 1

//--------------------------------------------------
// Definition of Type-C RTD Port Controller Related Macro
//--------------------------------------------------
#define GET_TYPE_C_RTD_STATUS_DETECT(x)                     (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].b1DetectStatusFlag)
#define SET_TYPE_C_RTD_STATUS_DETECT(x)                     (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].b1DetectStatusFlag = _TRUE)
#define CLR_TYPE_C_RTD_STATUS_DETECT(x)                     (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].b1DetectStatusFlag = _FALSE)

#define GET_TYPE_C_RTD_CC_ATTACH(x)                         (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumCcAttach)
#define SET_TYPE_C_RTD_CC_ATTACH(x, y)                      (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumCcAttach = (y))

#define GET_TYPE_C_RTD_ORIENTATION(x)                       (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumOrientation)
#define SET_TYPE_C_RTD_ORIENTATION(x, y)                    (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumOrientation = (y))

#define GET_TYPE_C_RTD_POWER_ROLE(x)                        (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumPowerRole)
#define SET_TYPE_C_RTD_POWER_ROLE(x, y)                     (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumPowerRole = (y))

#define GET_TYPE_C_RTD_DATA_ROLE(x)                         (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumDataRole)
#define SET_TYPE_C_RTD_DATA_ROLE(x, y)                      (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumDataRole = (y))

#define GET_TYPE_C_RTD_ALT_MODE_READY(x)                    (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumAltModeReady)
#define SET_TYPE_C_RTD_ALT_MODE_READY(x, y)                 (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumAltModeReady = (y))

#define GET_TYPE_C_RTD_PIN_ASSIGNMENT(x)                    (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumPinAssignment)
#define SET_TYPE_C_RTD_PIN_ASSIGNMENT(x, y)                 (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumPinAssignment = (y))

#define GET_TYPE_C_RTD_PDO_STATUS_VOL(x)                    (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].usPdoStatusVoltage)
#define SET_TYPE_C_RTD_PDO_STATUS_VOL(x, y)                 (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].usPdoStatusVoltage = (y))

#define GET_TYPE_C_RTD_PDO_STATUS_CUR(x)                    (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].usPdoStatusCurrent)
#define SET_TYPE_C_RTD_PDO_STATUS_CUR(x, y)                 (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].usPdoStatusCurrent = (y))

//      GET_TYPE_C_RTD_PARTNER_SRC_PDO_PEAK_CUR(x)          (g_pstUsbTypeCRtdInfo[SysUsbGetTypeCIndex(x)].enumDataRole)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonUsbTypeCRtdUpdatePortCtrlStatus(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCRtdReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE UserCommonUsbTypeCRtdGetSlaveAddr(EnumTypeCPcbPort enumTypeCPcbPort);
extern bit UserCommonUsbTypeCRtdGetPortCtrlInfoByI2C(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucStartAddr, BYTE ucLength, BYTE *pucReadInfo);
extern bit UserCommonUsbTypeCRtdSetPortCtrlInfoByI2C(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucStartAddr, BYTE ucLength, BYTE *pucWriteInfo);
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))

#endif // End of #ifndef __USER_COMMON_USB_TYPE_CRTD_H__
