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
// ID Code      : ScalerImgCmpGen1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _IMG_CMP_GEN1_BPP_SHIFT                              4


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
typedef struct
{
    BYTE ucSteamPeriodEnc;
    BYTE ucSteamPeriodDec;
    BYTE b4BitPerComponent : 4;
    BYTE b4LineBufDepth : 4;
    BYTE b1YCCModeEn : 1;
    BYTE b1MultiSliceEn : 1;
    WORD b10BitPerPixel : 10;
    WORD usWidth;
    WORD usHeight;
    WORD usSliceHeight;
} StructImgCmpGen1Param;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
extern void ScalerImgCmpEncEn(BYTE ucRegPage, bit bEn);
extern void ScalerImgCmpDecEn(BYTE ucRegPage, bit bEn);
extern void ScalerImgCmpGen1CommonCtrl(BYTE ucCmpRegPage, BYTE ucDecmpRegPage1, BYTE ucDecmpRegPage2, StructImgCmpGen1Param *pstImgCmpGen1Param);
#endif
