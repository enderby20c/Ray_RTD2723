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
// ID Code      : ScalerCpuCtrlInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_SCPU_SUPPORT == _ON)
//--------------------------------------------------
// Definations of CPU32 JTAG Debug Channel
//--------------------------------------------------
#define _JTAG_SWD_VGA                           0
#define _JTAG_SWD_DDC3                          1
#define _JTAG_SWD_DDC4                          2
#define _JTAG_JTAG_VGA_PA                       3
#define _JTAG_JTAG_DDC3_PA                      4
#define _JTAG_JTAG_DDC4_PA                      5
#define _JTAG_JTAG_VGA_P3                       6
#define _JTAG_JTAG_DDC3_P3                      7
#define _JTAG_JTAG_DDC4_P3                      8
#define _NO_JTAG                                9

#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_SCPU_SUPPORT == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern bit ScalerCpuCtrlCheckScpuActive(void);
extern void ScalerCpuCtrlBootInit(void);
extern void ScalerCpuCtrlSystemOff(void);
extern void ScalerCpuCtrlHandler(void);
#endif

#endif // End of #if(_SCPU_SUPPORT == _ON)

extern void ScalerCpuCtrlBusErrorProcess(EnumDebugSysBusErrorType enumDebugSysBusErrorType);
extern void ScalerCpuCtrlBusError_Handler(void);
