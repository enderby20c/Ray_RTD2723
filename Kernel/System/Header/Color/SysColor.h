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
// ID Code      : SysColor.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SYS_COLOR_H__
#define __SYS_COLOR_H__


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
#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
extern void SysColorDCCHistogramHandler(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_COLOR_IP_DCR == _ON)
extern void SysColorDCRHandler(EnumDisplayRegion enumDisplayRegion);
#endif


#endif // End of #ifndef __SYS_COLOR_H__
