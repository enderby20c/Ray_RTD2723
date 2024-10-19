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
// ID Code      : ScalerUsbBillboardInterface_User.h
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of BB Custom Command Change Event
//--------------------------------------------------
#define GET_USB_BB_CUSTOM_EVENT_CHANGE()                (g_enumUsbBillboardCustomEventChange)
#define SET_USB_BB_CUSTOM_EVENT_CHANGE(x)               (g_enumUsbBillboardCustomEventChange = (((g_enumUsbBillboardCustomEventChange) & (~(x))) | (x)))
#define CLR_USB_BB_CUSTOM_EVENT_CHANGE(x)               (g_enumUsbBillboardCustomEventChange = ((g_enumUsbBillboardCustomEventChange) & (~(x))))
#endif
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE ucRevCmd;
    BYTE ucOpCode;
    BYTE ucSubOpCode;
} StructUsbBillboardIspCommandInfo;

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
typedef struct
{
    BYTE ucwValue_Low;
    BYTE ucwValue_High;
    BYTE ucwIndex_Low;
    BYTE ucwIndex_High;
    BYTE ucwLength_Low;
    BYTE ucwLength_High;
} StructUsbBillboardCustomCommandInfo;
#endif
#endif
//--------------------------------------------------
// Enumerations of Type-C Billboard Enable/Disable
//--------------------------------------------------
typedef enum
{
    _USB_BB_DISABLE = 0x00,
    _USB_BB_ENABLE = 0x01,
}EnumBillboardCtrl;
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
typedef enum
{
    _BB_CUSTOM_EVENT_NONE = 0x00,
    _BB_CUSTOM_EVENT_00 = 0x01,
    _BB_CUSTOM_EVENT_01 = 0x02,
    _BB_CUSTOM_EVENT_02 = 0x04,
    _BB_CUSTOM_EVENT_03 = 0x08,
    _BB_CUSTOM_EVENT_04 = 0x10,
    _BB_CUSTOM_EVENT_05 = 0x20,
    _BB_CUSTOM_EVENT_06 = 0x40,
    _BB_CUSTOM_EVENT_ERROR = 0x80,
    _BB_CUSTOM_EVENT_RESET = 0xFF,
}EnumBillboardCustomEvent;

typedef enum
{
    _USB_BB_PROGRAM_DISABLE = 0x00,
    _USB_BB_PROGRAM_ENABLE = 0x01,
}EnumBillboardProgramCtrl;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern EnumBillboardCustomEvent g_enumUsbBillboardCustomEventChange;
#endif
#endif
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

