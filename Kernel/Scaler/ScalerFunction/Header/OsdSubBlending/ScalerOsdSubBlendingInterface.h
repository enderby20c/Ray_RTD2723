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
// ID Code      : ScalerOsdSubBlendingInterface.h No.0000
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
#if(_HW_GOSD_SUPPORT == _ON)
extern void ScalerOsdSubBlendingSetBypassFosdEnable(BYTE ucBypassEn);
extern bit ScalerOsdSubBlendingGetBypassFosdEnable(void);
extern void ScalerOsdSubBlendingSetGlobalAlpha(BYTE ucGlobalAlphaEn, BYTE ucAlphaValue);
extern void ScalerOsdSubBlendingSetGlobalAlpha_T0INT(BYTE ucGlobalAlphaEn, BYTE ucAlphaValue);
extern void ScalerOsdSubBlendingSetMixerFactor(BYTE ucK1, BYTE ucK2, BYTE ucK3, BYTE ucK4);
extern void ScalerOsdSubBlendingSetFosdMixerEnable(bit bFosdEn);
extern bit ScalerOsdSubBlendingGetFosdMixerEnable(void);
extern void ScalerOsdSubBlendingSetGosdMixerEnable(bit bGosdEn);
extern bit ScalerOsdSubBlendingGetGosdMixerEnable(void);
#endif
