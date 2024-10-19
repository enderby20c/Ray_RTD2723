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
// ID Code      : ScalerCpuSyncInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
//--------------------------------------------------
// Definitions of SCPU NOTIFY INT Event Processing Macro
//--------------------------------------------------
#define CLR_SCPU_NOTIFY_INT_MORE_PROCESS_FLAG()             (g_stCpuSyncCmdInfo.b1CpuIntMoreProcessFlag = _FALSE)
#define SET_SCPU_NOTIFY_INT_MORE_PROCESS_FLAG()             (g_stCpuSyncCmdInfo.b1CpuIntMoreProcessFlag = _TRUE)
#define GET_SCPU_NOTIFY_INT_MORE_PROCESS_FLAG()             (g_stCpuSyncCmdInfo.b1CpuIntMoreProcessFlag)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern volatile StructCpuCmdSyncInfo g_stCpuSyncCmdInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern DWORD ScalerCpuSyncGetDWord(DWORD ulAddress);
extern void ScalerCpuSyncSetDWord(DWORD ulAddress, DWORD ulData);
extern void ScalerCpuSyncShutDownCmd(void);
#endif

#endif // End of #if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))


