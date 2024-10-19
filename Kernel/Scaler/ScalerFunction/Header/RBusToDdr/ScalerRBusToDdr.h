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
// ID Code      : ScalerRBusToDdr.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_RBUS_TO_DDR_H__
#define __SCALER_RBUS_TO_DDR_H__


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
#if(_HW_CPU32_RBUS2DDR_SUPPORT == _ON)
extern bit ScalerRBusToDdrPrepareCmdX(BYTE ucTotalCmdXcnt, StructRBus2DdrCmdInfo *pstRbus2DdrCmdInfo, WORD usWaitResourceLockTimeoutMS);
extern bit ScalerRBusToDdrExecuteCmdX(BYTE ucTotalCmdXcnt, StructRBus2DdrCmdInfo *pstRbus2DdrCmdInfo, bit bWaitExecuteDone, WORD usWaitExeTimeoutMS, EnumRBusToDdrCallbackFuncId enumCallbackFuncId);
extern void ScalerRBusToDdrPostProcess(void);
extern void ScalerRBusToDdrSetMBistMode(DWORD ulRegValue);
extern DWORD ScalerRBusToDdrGetMBistMode(void);
extern void ScalerRBusToDdrCallbackFunction(void);
#endif


#endif // End of #ifndef __SCALER_RBUS_TO_DDR_H__
