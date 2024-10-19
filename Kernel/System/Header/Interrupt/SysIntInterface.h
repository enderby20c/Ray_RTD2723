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
// ID Code      : SysIntInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
#if(_CPU32_IP == _CPU32_IP_TR9)
#if(_JTAG_DEBUG == _ON)
extern void SysIntTrapError_IRQHandler(DWORD *pulTrapInfo);
#endif
#endif

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern void SysIntMainCpuPendSVCallback(void);
#endif
#if(_IS_MAIN_PROCESS_CPU == _FALSE)
extern void SysIntSecondCpuPendSVCallback(void);
#endif
