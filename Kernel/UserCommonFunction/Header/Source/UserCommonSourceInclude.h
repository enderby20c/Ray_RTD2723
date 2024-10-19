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
// ID Code      : UserCommonSourceInclude.h No.0000
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
extern EnumInputPort UserCommonSourceGetInputPort0(void);

#if(_MULTI_DISPLAY_MAX >= 0x02)
extern EnumInputPort UserCommonSourceGetInputPort1(void);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
extern EnumInputPort UserCommonSourceGetInputPort2(void);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
extern EnumInputPort UserCommonSourceGetInputPort3(void);
#endif

