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
// ID Code      : ScalerDDR3.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DDR3_H__
#define __SCALER_DDR3_H__

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

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
extern void ScalerDDR3SystemBridgeInitial(void);
extern bit ScalerDDR3DcPhyScrambleAvaiable(void);

#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
extern EnumMemoryClient ScalerDDR3GetMemoryClient(EnumMemoryClientType enumClientType, BYTE ucClientIndex);
#endif

#if(_HW_MEMORY_DDR3_DPIDLL_GEN_TYPE == _MEMORY_DDR3_DPIDLL_GEN_1)
extern void ScalerDDR3DpiDllGen1(void);
#elif(_HW_MEMORY_DDR3_DPIDLL_GEN_TYPE == _MEMORY_DDR3_DPIDLL_GEN_2)
extern void ScalerDDR3DpiDllGen2(void);
#endif

#if(_DDR3_KGD_DCC_SUPPORT == _OFF)
extern void ScalerDDR3KGDDCCOff(void);
#endif

#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)


#endif // End of #ifndef __SCALER_DDR3_H__
