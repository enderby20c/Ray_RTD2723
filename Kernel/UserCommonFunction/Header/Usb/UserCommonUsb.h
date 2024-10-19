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
// ID Code      : UserCommonUsb.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_USB_H__
#define __USER_COMMON_USB_H__

#if((_USB_SUPPORT == _ON) || (_TYPE_C_PORT_CTRL_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _SMBUS_READ_DATA_LEN                        32
#define _SMBUS_WRITE_DATA_LEN                       (4 + (_RTS_MAX_DATA_OBJ_CNT * 4)) // WR_DATA_LEN(1 Byte) + SUB_CMD(1 Byte) + PORT_NUM(1 Byte) + Set PDO Num(1 Byte) + Max Data Objects * 4 Bytes

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_USB_RTS_SMBUS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON))
extern bit UserCommonUsbCommunicationSMBArbitration(void);
extern void UserCommonUsbCommunicationReleaseSMbusCtlPin(void);
extern bit UserCommonUsbCommunicationShortRead(BYTE ucDeviceAddr, BYTE *pucReadArray, EnumTypeCPcbPort enumTypeCPcbPort);
extern bit UserCommonUsbCommunicationSMBRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
extern bit UserCommonUsbCommunicationSMBWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
#endif // End of #if((_USB_RTS_SMBUS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON))
#endif // End of #if((_USB_SUPPORT == _ON) || (_TYPE_C_PORT_CTRL_SUPPORT == _ON))


#endif // End of #ifndef __USER_COMMON_USB_H__
