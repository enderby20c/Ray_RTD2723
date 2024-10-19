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
// ID Code      : ScalerDDR1.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DDR1_H__
#define __SCALER_DDR1_H__

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// DDR1 Data Rate
//--------------------------------------------------
#define _DDR1_DATA_RATE_440M                               440
#define _DDR1_DATA_RATE_400M                               400

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDDR1DCPHYInitial(void);
extern DWORD ScalerDDR1CalcWrlvlConfig(StructDDR1PLLPI *pstDDR1PLLPhase);

extern void ScalerDDR1PLLCtrl(bit bEnable);
extern void ScalerDDR1PLLOutputCtrl(bit bEnable);
extern void ScalerDDR1SetPLLFreq(DWORD ulFreq);
extern void ScalerDDR1SetPLLWritePhase(StructDDR1PLLPI *pstDDR1PLLPhase);

#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)



#endif // End of #ifndef __SCALER_DDR1_H__
