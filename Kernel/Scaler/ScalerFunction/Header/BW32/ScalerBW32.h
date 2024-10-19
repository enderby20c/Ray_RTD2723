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
// ID Code      : ScalerBW32.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_BW32_H__
#define __SCALER_BW32_H__

#if(_HW_CPU32_BW32_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD ulBW32_ADDRESS;
    DWORD ulBW32_DATA;
} StructBW32CmdPair;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerBW32PrepareCmdX(BYTE ucTotalCmdXcnt, StructBW32CmdInfo *pstBW32CmdInfo, WORD usWaitResourceLockTimeoutMS);
extern bit ScalerBW32ExecuteCmdX(BYTE ucTotalCmdXcnt, StructBW32CmdInfo *pstBW32CmdInfo, bit bWaitExecuteDone, WORD usWaitExeTimeoutMS, EnumBW32CallBackFuncId enumCallBackFuncId);

extern void ScalerBW32SetMBistMode(DWORD ulRegValue);
extern DWORD ScalerBW32GetMBistMode(void);
extern void ScalerBW32RunCallbackFunction(void);
#endif  // End of #if(_HW_CPU32_BW32_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_BW32_H__
