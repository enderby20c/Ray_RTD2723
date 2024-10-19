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
// ID Code      : UserCommonColor.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_COLOR_H__
#define __USER_COMMON_COLOR_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_VGA_SUPPORT == _ON)

#if(_DIG_FILTER_ENHANCE_PHASE_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// TABLE DIGITAL FILTER ENHANCE PHASE MODE
//----------------------------------------------------------------------------------------------------
#include _DIGITAL_FILTER_ENHANCE_PHASE_TABLE
#endif

#if(_RINGING_FILTER_FUNCTION == _ON)
//----------------------------------------------------------------------------------------------------
// TABLE RINGING FILTER OFFSET COEFFICIENT
//----------------------------------------------------------------------------------------------------
#include _RINGING_FILTER_TABLE
#endif

#endif  // End of #if(_VGA_SUPPORT == _ON)

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
#define _LIGHTENHANCE_IAPSGAIN_540NIT           0x160C
#define _LIGHTENHANCE_IAPSGAIN_1200NIT          0x18CC
#define _LIGHTENHANCE_IAPSGAIN_4000NIT          0x1CEA
#define _LIGHTENHANCE_IAPSGAIN_10000NIT         0x2000
#endif

#if(_COLOR_IP_LOCAL_DIMMING == _ON)
#define _LOCAL_DIMMING_HDR10_540NIT             701
#if(_HDR10_EETF_TONEMAPPING_SUPPORT == _ON)
#define _LOCAL_DIMMING_HDR10_1200NIT            769 // PQ Code of 1000nit
#else
#define _LOCAL_DIMMING_HDR10_1200NIT            789
#endif
#define _LOCAL_DIMMING_HDR10_4000NIT            923
#define _LOCAL_DIMMING_HDR10_10000NIT           1018
#define _LOCAL_DIMMING_SDR_NATIVE_NIT           1016
#define _LOCAL_DIMMING_NOTM_CODE_TOLERANCE      2
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
#if(_VGA_SUPPORT == _ON)
#if(_DIG_FILTER_ENHANCE_PHASE_SUPPORT == _ON)
#if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
extern void UserCommonColorDigitalFilterEnhancePhaseAdjust(void);
#endif
#endif

#if(_RINGING_FILTER_FUNCTION == _ON)
#if(_HW_RINGING_FILTER_TYPE != _GEN_NONE)
extern void UserCommonColorRingingFilterAdjust(void);
#endif
#endif

#endif // End of #if(_VGA_SUPPORT == _ON)

#endif // End of #ifndef __USER_COMMON_COLOR_H__
