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
// ID Code      : ScalerSDRAM.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_SDRAM_H__
#define __SCALER_SDRAM_H__

#if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)

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
extern void ScalerSdramDCPHYInitial(void);
extern DWORD ScalerSdramCalcWrlvlConfig(StructSDRAMPLLPI *pstSDRAMPLLPhase);

extern void ScalerSdramPLLCtrl(bit bEnable);
extern void ScalerSdramPLLOutputCtrl(bit bEnable);
extern void ScalerSdramSetPLLFreq(DWORD ulFreq);
extern void ScalerSdramSetPLLWritePhase(StructSDRAMPLLPI *pstSDRAMPLLPhase);

#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)

#endif // End of #ifndef __SCALER_SDRAM_H__
