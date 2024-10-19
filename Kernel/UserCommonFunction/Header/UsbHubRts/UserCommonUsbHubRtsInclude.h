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
// ID Code      : UserCommonUsbHubRtsInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_USB_HUB_RTS_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
} StructSMBusWrSetSSMode;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
} StructSMBusWRDetectDSPSSMode;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucDSP0;
    BYTE ucDSP1;
    BYTE ucDSP2;
    BYTE ucDSP3;
} StructSMBusRDDetectDSPSSMode;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_USB_HUB_RTS_SMBUS_SUPPORT == _ON)
extern EnumUsbHubSetU3ModeFailureType UserCommonUsbHubRtsSetSSMode(EnumTypeCPcbPort enumTypeCPcbPort, bit bEn);
extern EnumHubDspDetectStatus UserCommonUsbHubRtsDetectDFPStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#endif // End of #if(_USB_HUB_RTS_SUPPORT == _ON)

