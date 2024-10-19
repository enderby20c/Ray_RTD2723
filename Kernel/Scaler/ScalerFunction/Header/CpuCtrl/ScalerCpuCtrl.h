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
// ID Code      : ScalerCpuCtrl.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_CPU_CTRL_H__
#define __SCALER_CPU_CTRL_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_SCPU_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DW8051 Boot up CPU32 Flow Relative Macro
//--------------------------------------------------
#define SET_KCPU_CODE_FLASH_OFFSET(x)                       {Scaler32SetDWord(PA40010_50_MIPS_CPU1_FLASH_BANK_OFFSET, (x));}

#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
#define SET_SCPU_CODE_FLASH_OFFSET(x)                       {Scaler32SetDWord(PA40010_54_RISCV_CPU1_FLASH_BANK_OFFSET, (x));}
#else
#define SET_SCPU_CODE_FLASH_OFFSET(x)                       (MCU_FD70_CPU1_FLASH_BANK_OFFSET = ((x) + 1))
#endif

#define SET_SCPU_RECEIVE_REQUEST_IRQ()                      (MCU_FD52_NOTIFY_8051_INT_CTRL |= (_BIT7 | _BIT0))
#define CLR_SCPU_RECEIVE_REQUEST_IRQ()                      (MCU_FD52_NOTIFY_8051_INT_CTRL &= ~(_BIT7 | _BIT0))

#define SET_ACCESS_INVALID_ADDR_ON_RBUS_IRQ()               (MCU_FDED_SB2_TIMEOUT_INTSTAT |= (_BIT1 | _BIT0))
#define CLR_ACCESS_INVALID_ADDR_ON_RBUS_IRQ()               (MCU_FDED_SB2_TIMEOUT_INTSTAT &= ~(_BIT1 | _BIT0))

#define CLR_SCPU_GATING_CLOCK_OPTION()                      (MCU_FDEC_CPU32_WDT_CTRL &= ~_BIT1)

#define SET_WHOLE_CHIP_RESET()                              (MCU_FFEE_MCU_CLOCK_CONTROL |= _BIT1)

//--------------------------------------------------
// Definitions of CPU32 IRQ Event Processing Macro
//--------------------------------------------------
#define GET_SB2_TIMEOUT_INT_FLAG()                          (MCU_FDED_SB2_TIMEOUT_INTSTAT & _BIT0)
#define GET_SCPU_WD_IRQ()                                   ((bit)(MCU_FDEC_CPU32_WDT_CTRL & _BIT0))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern const DWORD __flash_bank_count__;

#if(_SCPU_SUPPORT == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern BYTE code tCpuCtrlFlashBankEnd[1];
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_SCPU_SUPPORT == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)

#if(_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)
extern void ScalerCpuCtrlActorInit(void);
#endif

extern BYTE ScalerCpuCtrlFlashBankOffsetGetValue(void);
extern void ScalerCpuCtrlSetScpuGlobalControl(bit bRBusMode, bit bEnableScpuPlatformClk, bit bEnableScpu);
#endif

extern bit ScalerCpuCtrlGetCpu32BusIdleStatus(void);
#endif // End of #if(_SCPU_SUPPORT == _ON))


#endif // End of #ifndef __SCALER_CPU_CTRL_H__
