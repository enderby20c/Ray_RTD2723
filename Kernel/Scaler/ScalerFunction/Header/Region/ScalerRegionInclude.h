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
// ID Code      : ScalerRegionInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define DISPLAY_INFO(FBMode, mode)                    (((BYTE)(FBMode)) | (mode))
#define DISPLAY_REGION_INFO(FBMode, region)           (((WORD)(FBMode) << 8) | (region))
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumRegionIndex ScalerRegionGetIndexFromInputDataPath(EnumInputDataPath enumInputDataPath);

#if(_HW_I_DOMAIN_PATH_COUNT > 1)
extern WORD ScalerRegionGetIDomainRegisterPage(EnumSelRegion enumSelRegion);
#endif

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
extern WORD ScalerRegionGetDDomainBeforeBlendingRegisterPage(EnumSelRegion enumSelRegion);
extern WORD ScalerRegionGetDDomainAfterBlendingRegisterPage(EnumSelRegion enumSelRegion);
#endif
#if(_2P_DISPLAY_SUPPORT == _ON)
extern bit ScalerRegion2PRegionEqual(EnumDisplayMode enumDisplayMode);
#endif

extern EnumInputDataPath ScalerRegionGetInputDataPathFromSelRegion(EnumSelRegion enumSelRegion);