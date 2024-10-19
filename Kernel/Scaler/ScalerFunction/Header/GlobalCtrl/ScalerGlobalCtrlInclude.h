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
// ID Code      : ScalerGlobalCtrlInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
#define SET_CURRENT_CPU_CLK_KHZ(ulKHz)                  (g_ulGlobalCtrlCpuClk_KHz = (ulKHz))
#define GET_CURRENT_CPU_CLK_KHZ()                       (g_ulGlobalCtrlCpuClk_KHz)
#define SET_PREVIOUS_CPU_CLK_KHZ(ulKHz)                 (g_ulGlobalCtrlPrevCpuClk_KHz = (ulKHz))
#define GET_PREVIOUS_CPU_CLK_KHZ()                      (g_ulGlobalCtrlPrevCpuClk_KHz)
#else
#define SET_CURRENT_CPU_CLK_KHZ(ulKHz)                  (g_ulGlobalCtrlScpuClk_KHz = (ulKHz))
#define GET_CURRENT_CPU_CLK_KHZ()                       (g_ulGlobalCtrlScpuClk_KHz)
#define SET_PREVIOUS_CPU_CLK_KHZ(ulKHz)                 (g_ulGlobalCtrlPrevScpuClk_KHz = (ulKHz))
#define GET_PREVIOUS_CPU_CLK_KHZ()                      (g_ulGlobalCtrlPrevScpuClk_KHz)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile DWORD g_ulGlobalCtrlCpuClk_KHz;
extern volatile DWORD g_ulGlobalCtrlPrevCpuClk_KHz;

#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
extern volatile DWORD g_ulGlobalCtrlScpuClk_KHz;
extern volatile DWORD g_ulGlobalCtrlPrevScpuClk_KHz;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


