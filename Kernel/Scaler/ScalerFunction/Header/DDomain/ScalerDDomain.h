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
// ID Code      : ScalerDDomain.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DDOMAIN_H__
#define __SCALER_DDOMAIN_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_FREESYNC_OD_MEASURE == _ON)
#define _FREESYNC_OD_MEASURE_GL_ENABLE_REG      P7_F3_DISP_PG_R_INITIAL
#define _FREESYNC_OD_MEASURE_GL_VALUE_REG       P7_F4_DISP_PG_G_INITIAL
#endif

#if(_FW_DISPLAYTOP_AVG_REQ_SUPPORT == _ON)
#define _DISPLAYTOP_AVG_REQ_FACTOR_BIT          (20)
#define _DISPLAYTOP_AVG_REQ_HW_LIMIT            (13)
#define _DISPLAYTOP_AVG_REQ_BUFFER              (10)
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
#if(_HW_ADJ_A1_LB_START_ADDR == _ON)
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerDDomainSetExtRecapLBStartAddr(EnumDisplayRegion enumDisplayRegion, WORD usHorSize);
#endif
#endif // END OF #if(_HW_ADJ_A1_LB_START_ADDR == _ON)

#endif // End of #ifndef __SCALER_DDOMAIN_H__
