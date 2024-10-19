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
// ID Code      : ScalerVgaAutoInterface.h No.0000
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
extern EnumAutoResult ScalerVgaAutoDoWhiteBalance(EnumAutoColorType enumAutoType);
extern void ScalerVgaAutoGetAutoColorResult(StructAdcDataType *pstAdcData);
extern EnumAutoResult ScalerVgaAutoMeasureColorValue(BYTE ucColor, bit bSelectMax, BYTE *pucResult);

#if(_YPBPR_SUPPORT == _ON)
#if(_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA)
extern StructAdcDataType ScalerVgaAutoBalanceYPbPrFromFormula(StructAdcDataType *pstAdcData);
#endif
#endif

#endif // End of #if(_VGA_SUPPORT == _ON)


