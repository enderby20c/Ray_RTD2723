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
// ID Code      : UserCommonColorDMInterface.h No.0000
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
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern void UserCommonColorDMHandler(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonColorDMReset(EnumDisplayRegion enumDisplayRegion);
#if(_DM_DEMO_FUNCTION == _ON)
extern void UserCommonColorDMDemoFuncProc(void);
#endif
#endif
#if(_IS_MAIN_PROCESS_CPU == _FALSE)
extern void UserCommonColorDMBECHandler(void);
extern void UserCommonColorDMMuteHandler(void);
#endif
#endif
