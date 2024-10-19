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
// ID Code      : ScalerScalingInterface.h No.0000
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
#if(_SD_TABLE_SEL_FUNCTION == _OFF)
extern void ScalerScalingSetScalingDownCoef(void);
#else
extern void ScalerScalingSetFlexibleScalingDownCoef(EnumSelRegion enumSelRegion, BYTE *pucAddressH, BYTE *pucAddressV);
extern WORD ScalerScalingCheckRegPageSel(EnumSelRegion enumSelRegion);
extern EnumByPassEnable ScalerScalingCheckFSBypassEnable(EnumSelRegion enumSelRegion);
#endif

extern void ScalerScalingSetScalingUpBypassTable(EnumDDomainRegion enumDDomainRegion, bit bEnable, EnumDBApply enumDBApply);

#if(_SHARPNESS_FUNCTION == _OFF)
extern void ScalerScalingSetScalingUpCoef(void);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_ORIGINAL_MODE_SUPPORT == _ON)
extern bit ScalerScalingGetESOriginalModeStatus(WORD usInputHWidth, WORD usInputVHeight);
extern void ScalerScalingModifyESOriginalModeSUFI(void);
#endif
#endif
