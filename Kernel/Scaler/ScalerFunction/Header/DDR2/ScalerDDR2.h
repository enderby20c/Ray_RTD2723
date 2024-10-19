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
// ID Code      : ScalerDDR2.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DDR2_H__
#define __SCALER_DDR2_H__

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Memory BW Ctrl Related
//--------------------------------------------------
#define TABLE_INFO(t)                                     {(t), (sizeof((t)) / sizeof((t)[0]))}
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Memory BW Ctrl Related
//--------------------------------------------------
typedef struct
{
    EnumMemoryClient *penumTable;
    BYTE ucTableSize;
} StructMemoryClientTableInfo;

typedef struct
{
    EnumMemoryClientType enumType;
    StructMemoryClientTableInfo stClients;
} StructMemoryClientTypeInfo;

typedef struct
{
    DWORD ulAddr;
    DWORD ulBit;
} StructCtrlBit;

typedef struct
{
    EnumMemoryClient enumClient;
    StructCtrlBit stEnCtrl;
    StructCtrlBit stModeCtrl;
    DWORD ulReqThdRegAddr;
    DWORD ulTimeThdRegAddr;
} StructBwCtrlRegInfo;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDDR2SystemBridgeInitial(void);

#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
extern EnumMemoryClient ScalerDDR2GetMemoryClient(EnumMemoryClientType enumClientType, BYTE ucClientIndex);
#endif

#if((_DISPLAY_ROTATION_SUPPORT == _ON) && (_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_I))
extern void ScalerDDR2DCSysSetPictureSetInfo(BYTE ucPictNum, BYTE ucPictWidthScale, DWORD ulPictInitPage);
#endif

#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)


#endif // End of #ifndef __SCALER_DDR2_H__
