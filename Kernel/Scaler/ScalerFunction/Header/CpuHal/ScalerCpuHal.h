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
// ID Code      : ScalerCpuHal.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_CPU_HAL_H__
#define __SCALER_CPU_HAL_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// CPU32_Private_Macros CPU32 Private Macros
#define IS_NVIC_PRIORITY_GROUP(GROUP)           (((GROUP) == _NVIC_PRIORITYGROUP_0) ||\
                                                 ((GROUP) == _NVIC_PRIORITYGROUP_1) ||\
                                                 ((GROUP) == _NVIC_PRIORITYGROUP_2) ||\
                                                 ((GROUP) == _NVIC_PRIORITYGROUP_3) ||\
                                                 ((GROUP) == _NVIC_PRIORITYGROUP_4))

#define IS_NVIC_PREEMPTION_PRIORITY(ulPRIORITY) ((ulPRIORITY) < 0x10U)

#define IS_NVIC_SUB_PRIORITY(ulPRIORITY)        ((ulPRIORITY) < 0x10U)

#define IS_NVIC_DEVICE_IRQ(ulIRQ)               ((ulIRQ) >= (EnumIRQnType)0x00U)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
extern volatile DWORD g_ulCpuHalMainCpuPendSVEventCnt;
#endif

#if(_SCPU_SUPPORT == _ON)
extern volatile DWORD g_ulCpuHalSecondCpuPendSVEventCnt;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


#endif // End of #ifndef __SCALER_CPU_HAL_H__
