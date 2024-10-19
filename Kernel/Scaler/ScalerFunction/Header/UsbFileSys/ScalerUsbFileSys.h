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
// ID Code      : ScalerUsbFileSys.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_USB_FAT_32_H__
#define __SCALER_USB_FAT_32_H__

#if(_USB2_HOST_EHCI_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_U2HOST_FAT32_FILENAME_TYPE()                               (g_enumUsbFileSysFat32FileNameType)
#define SET_U2HOST_FAT32_FILENAME_TYPE(x)                              (g_enumUsbFileSysFat32FileNameType = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _ONLY_SFN = 0x00,
    _SFN_AND_LFN,
}EnumUsbFileSysFat32FileNameType;

typedef enum
{
    _1ST_NAME_ENTRY = 0x00,
    _1ST_AND_2ND_NAME_ENTRY = 0x01,
}EnumUsbFileSysExfatFileNameType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE ScalerUsbFileSysFat32MapSfn(BYTE ucFileNameOffset, code BYTE *pucGoldenName);
extern WORD ScalerUsbFileSysFat32MapLfn(BYTE ucFileNameOffset, code BYTE *pucGoldenName);
extern BYTE ScalerUsbFileSysFat32GetLfnChar(BYTE ucCharOffset, BYTE *pucLfn);

#endif // End of #if(_USB2_HOST_EHCI_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_USB_FAT_32_H__
