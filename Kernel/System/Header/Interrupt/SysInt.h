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
// ID Code      : SysInt.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SYS_INT_H__
#define __SYS_INT_H__

#include "ExceptionHandlers.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define CHECK_INT_PENDING_FLAG(value, flag)           (((value) & (1UL << (flag))) != 0)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
__attribute__((section(".itcm_section.SysInt0Proc_EXINT0")))
extern void SysInt0Proc_EXINT0(void);

extern void SysIntDdc_IRQHandler(void);

#if(_HW_IIC_1_SUPPORT == _ON)
#if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
extern void SysIntI2CM_IRQHandler(void);
#endif
#endif

#if(_USB3_REPEATER_SUPPORT == _ON)
extern void SysInt3Proc_EXINT3(void);
#endif

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
__attribute__((section(".itcm_section.SysIntMainCpuSw0IRQHandler")))
extern void SysIntMainCpuSw0IRQHandler(void);

__attribute__((section(".itcm_section.SysIntMainCpuSw1IRQHandler")))
extern void SysIntMainCpuSw1IRQHandler(void);

__attribute__((section(".itcm_section.SysIntMainCpuHw0IRQHandler")))
extern void SysIntMainCpuHw0IRQHandler(void);

__attribute__((section(".itcm_section.SysIntMainCpuHw1IRQHandler")))
extern void SysIntMainCpuHw1IRQHandler(void);

__attribute__((section(".itcm_section.SysIntMainCpuHw2IRQHandler")))
extern void SysIntMainCpuHw2IRQHandler(void);

__attribute__((section(".itcm_section.SysIntMainCpuHw3IRQHandler")))
extern void SysIntMainCpuHw3IRQHandler(void);

__attribute__((section(".itcm_section.SysIntMainCpuHw4IRQHandler")))
extern void SysIntMainCpuHw4IRQHandler(void);

__attribute__((section(".itcm_section.SysIntMainCpuHw5IRQHandler")))
extern void SysIntMainCpuHw5IRQHandler(void);

extern void SysIntMainCpuScalerErrorIRQHandler(void);

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON))
extern bit SysIntMainCpuNotifyIRQHandler(EnumCpuSyncCommand enumCpuSyncCommand);
#endif
#endif

#if((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR))
__attribute__((section(".itcm_section.SysIntTimer0_IRQHandler")))
extern void SysIntTimer0_IRQHandler(void);

__attribute__((section(".itcm_section.SysIntTimer1_IRQHandler")))
extern void SysIntTimer1_IRQHandler(void);

__attribute__((section(".itcm_section.SysIntTimer2_IRQHandler")))
extern void SysIntTimer2_IRQHandler(void);
#endif

#if(_UART_SUPPORT == _ON)
extern void SysIntExtUart_IRQHandler(void);
#endif

extern void SysIntTimer0Proc_T0INT(void);
extern void SysIntTimer1Proc_T1INT(void);

__attribute__((section(".itcm_section.SysIntTimer2Proc_T2INT")))
extern void SysIntTimer2Proc_T2INT(void);

extern void SysIntTimerWDProc_WDINT(void);

#if(_IS_MAIN_PROCESS_CPU == _FALSE)
__attribute__((section(".itcm_section.SysIntSecondCpuSw0IRQHandler")))
extern void SysIntSecondCpuSw0IRQHandler(void);

__attribute__((section(".itcm_section.SysIntSecondCpuSw1IRQHandler")))
extern void SysIntSecondCpuSw1IRQHandler(void);

__attribute__((section(".itcm_section.SysIntSecondCpuHw0IRQHandler")))
extern void SysIntSecondCpuHw0IRQHandler(void);

__attribute__((section(".itcm_section.SysIntSecondCpuHw1IRQHandler")))
extern void SysIntSecondCpuHw1IRQHandler(void);

__attribute__((section(".itcm_section.SysIntSecondCpuHw2IRQHandler")))
extern void SysIntSecondCpuHw2IRQHandler(void);

__attribute__((section(".itcm_section.SysIntSecondCpuHw3IRQHandler")))
extern void SysIntSecondCpuHw3IRQHandler(void);

__attribute__((section(".itcm_section.SysIntSecondCpuHw4IRQHandler")))
extern void SysIntSecondCpuHw4IRQHandler(void);

__attribute__((section(".itcm_section.SysIntSecondCpuHw5IRQHandler")))
extern void SysIntSecondCpuHw5IRQHandler(void);

extern void SysIntSecondCpuScalerErrorIRQHandler(void);

#if((_HW_CPU32_NOTIFY_INT_SUPPORT == _ON) && (_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_SCPU_SUPPORT == _ON))
__attribute__((section(".itcm_section.SysIntSecondCpuNotifyIRQHandler")))
extern void SysIntSecondCpuNotifyIRQHandler(void);
#endif
#endif

__attribute__((section(".itcm_section.SysIntWdt_IRQHandler")))
extern void SysIntWdt_IRQHandler(void);


#endif // End of #ifndef __SYS_INT_H__
