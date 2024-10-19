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
// ID Code      : ScalerImgCmp.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_IMG_CMP_H__
#define __SCALER_IMG_CMP_H__

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
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
extern void ScalerImgCmpRemapDecoderIndex(EnumDisplayMode enumDisplayMode, BYTE ucCmpIndex, BYTE *pucDecmpIndex1, BYTE *pucDecmpIndex2);
extern void ScalerImgCmpCtrlGen1(WORD usHWidth, WORD usVHeight, EnumImgCmpParamIndex enumCmpParamIndex);
#endif

#endif // End of #ifndef __SCALER_IMG_CMP_H__
