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
// ID Code      : UserCommonUsbInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_USB_SUPPORT == _ON) || (_TYPE_C_PORT_CTRL_SUPPORT == _ON))

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
#if((_USB_RTS_SMBUS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON))
extern bit UserCommonUsbCommunicationWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, EnumTypeCPcbPort enumTypeCPcbPort);
extern bit UserCommonUsbCommunicationRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, EnumTypeCPcbPort enumTypeCPcbPort);
extern bit UserCommonUsbCommunicationPollingPDReady(BYTE ucDeviceAddr, WORD usTime, EnumTypeCPcbPort enumTypeCPcbPort);
#endif // End of #if((_USB_RTS_SMBUS_SUPPORT == _ON) || (_PORT_CTRL_RTD_SUPPORT == _ON))
#if(_DP_SUPPORT == _ON)
extern void UserCommonUsbTypeCRxSetLaneCountCapabilitySwitch(void);
#endif
#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
extern BYTE UserCommonUsb2HostGetFileName(BYTE ucUsbUserFileNameOffset);
extern bit UserCommonUsb2HostGetConnectStatus(void);
extern StructUsbFileSysUserFileInfo UserCommonUsb2HostGetFileInfo(void);
#endif
#endif // End of #if((_USB_SUPPORT == _ON) || (_TYPE_C_PORT_CTRL_SUPPORT == _ON))

