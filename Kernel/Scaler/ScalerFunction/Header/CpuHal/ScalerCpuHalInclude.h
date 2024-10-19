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
// ID Code      : ScalerCpuHalInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// CPU32_Exported_Constants CPU32 Exported Constants
#define NVIC_GET_ENABLE_IRQ(enumIRQn)                   (NVIC_GetEnableIRQ(enumIRQn))

// CPU32_Preemption_Priority_Group CPU32 Preemption Priority Group
#define _NVIC_PRIORITYGROUP_0                           (0x07)  /*!< 0 bits for pre-emption priority 4 bits for subpriority */
#define _NVIC_PRIORITYGROUP_1                           (0x06)  /*!< 1 bits for pre-emption priority 3 bits for subpriority */
#define _NVIC_PRIORITYGROUP_2                           (0x05)  /*!< 2 bits for pre-emption priority 2 bits for subpriority */
#define _NVIC_PRIORITYGROUP_3                           (0x04)  /*!< 3 bits for pre-emption priority 1 bits for subpriority */
#define _NVIC_PRIORITYGROUP_4                           (0x03)  /*!< 4 bits for pre-emption priority 0 bits for subpriority */


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerCpuHalSetPrioritygrouping(DWORD ulPrioritygroup);
extern void ScalerCpuHalSetPriority(EnumIRQnType enumIRQn, DWORD ulPreemptPriority);
extern DWORD ScalerCpuHalGetPrioritygrouping(void);
extern DWORD ScalerCpuHalGetPriority(EnumIRQnType enumIRQn);
extern void ScalerCpuHalSetPendingIRQ(EnumIRQnType enumIRQn);
extern DWORD ScalerCpuHalGetPendingIRQ(EnumIRQnType enumIRQn);
extern void ScalerCpuHalClearPendingIRQ(EnumIRQnType enumIRQn);
extern DWORD ScalerCpuHalGetActive(EnumIRQnType enumIRQn);

__attribute__((warn_unused_result))
extern bit ScalerCpuHalGetPhyFlashAddress(DWORD ulCpuFlashAddress, DWORD *pulPhyFlashAddrPtrAddress);
__attribute__((warn_unused_result))
extern bit ScalerCpuHalGetCpuFlashAddress(DWORD ulPhyFlashAddress, DWORD *pulCpuFlashAddrPtrAddress);
