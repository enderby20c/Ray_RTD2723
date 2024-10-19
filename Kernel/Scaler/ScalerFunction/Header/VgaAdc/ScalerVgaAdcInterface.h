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
// ID Code      : ScalerVgaAdcInterface.h No.0000
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
#if(_VGA_SUPPORT == _ON)
extern void ScalerVgaAdcGainAdjust(BYTE *pucGainMSB, BYTE *pucGainLSB);
extern void ScalerVgaAdcOffsetAdjust(BYTE *pucOffsetMSB, BYTE *pucOffsetLSB);
extern void ScalerVgaAdcClampMode(EnumColorSpace enumColorFormat);
extern void ScalerVgaAdcDCRestoreEn(bit bEn);
extern void ScalerVgaAdcSOGClampEn(bit bEn);
#endif // End of #if(_VGA_SUPPORT == _ON)

