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
// ID Code      : ScalerMemoryDevicePLLInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD ulDdrPllInitialPhase0;
    DWORD ulDdrPllInitialPhase1;
    DWORD ulDdrPllInitialPhase2;
    DWORD ulDdrTxFifoStr0;
    DWORD ulDdrTxFifoStr1;
    DWORD ulDdrRxFifoStr2;
} StructDDRPhaseInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMemoryDevicePLLEnableControl(bit bEnable);
extern void ScalerMemoryDevicePLLWritePhase(StructDDRPhaseInfo *pstDdrPhaseData);

