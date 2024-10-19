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
// ID Code      : ScalerOsdSubBlending.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_OSDSUBBLENDING__

#include "ScalerFunctionInclude.h"
#include "OsdSubBlending/ScalerOsdSubBlending.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HW_GOSD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Global Alpha
// Input Value  : ucGlobalAlphaEn
//                ucAlphaValue
// Output Value : None
//--------------------------------------------------
void ScalerOsdSubBlendingSetGlobalAlpha(BYTE ucGlobalAlphaEn, BYTE ucAlphaValue)
{
    ScalerSetBit(P3A_E1_OSD_SUB_BLENDING_CTRL, ~_BIT6, (ucGlobalAlphaEn & _BIT0) << 6);
    ScalerSetByte(P3A_E6_OSD_SUB_BLENDING_GLOBAL_ALPHA_VALUE, ucAlphaValue);
}

//--------------------------------------------------
// Description  : Set Global Alpha
// Input Value  : ucGlobalAlphaEn
//                ucAlphaValue
// Output Value : None
//--------------------------------------------------
void ScalerOsdSubBlendingSetGlobalAlpha_T0INT(BYTE ucGlobalAlphaEn, BYTE ucAlphaValue)
{
    ScalerSetBit_EXINT(P3A_E1_OSD_SUB_BLENDING_CTRL, ~_BIT6, (ucGlobalAlphaEn & _BIT0) << 6);
    ScalerSetByte_EXINT(P3A_E6_OSD_SUB_BLENDING_GLOBAL_ALPHA_VALUE, ucAlphaValue);
}

//--------------------------------------------------
// Description  : Set Mixer Factor
// Input Value  : ucK1
//                ucK2
//                ucK3
//                ucK4
// Output Value : None
//--------------------------------------------------
void ScalerOsdSubBlendingSetMixerFactor(BYTE ucK1, BYTE ucK2, BYTE ucK3, BYTE ucK4)
{
    ScalerSetBit(P3A_E5_OSD_SUB_BLENDING_K1, ~(0x3F), (ucK1 & 0x3F));
    ScalerSetBit(P3A_E4_OSD_SUB_BLENDING_K2, ~(0x3F), (ucK2 & 0x3F));
    ScalerSetBit(P3A_E3_OSD_SUB_BLENDING_K3, ~(0x3F), (ucK3 & 0x3F));
    ScalerSetBit(P3A_E2_OSD_SUB_BLENDING_K4, ~(0x3F), (ucK4 & 0x3F));
}

//--------------------------------------------------
// Description  : Set Bypass Fosd
// Input Value  : ucBypassEn
// Output Value : None
//--------------------------------------------------
void ScalerOsdSubBlendingSetBypassFosdEnable(BYTE ucBypassEn)
{
    ScalerSetBit(P3A_E1_OSD_SUB_BLENDING_CTRL, ~_BIT7, (ucBypassEn & _BIT0) << 7);
}

//--------------------------------------------------
// Description  : Get Bypass Fosd
// Input Value  : None
// Output Value : _ENABLE / _DISABLE
//--------------------------------------------------
bit ScalerOsdSubBlendingGetBypassFosdEnable(void)
{
    return ScalerGetBit(P3A_E1_OSD_SUB_BLENDING_CTRL, _BIT7);
}

//--------------------------------------------------
// Description  : Set mixer fosd enable/disable
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerOsdSubBlendingSetFosdMixerEnable(bit bFosdEn)
{
    ScalerSetBit(P3A_E1_OSD_SUB_BLENDING_CTRL, ~_BIT1, ((BYTE)bFosdEn & _BIT0) << 1);
}

//--------------------------------------------------
// Description  : Get mixer fosd enable/disable
// Input Value  : None
// Output Value : _ENABLE / _DISABLE
//--------------------------------------------------
bit ScalerOsdSubBlendingGetFosdMixerEnable(void)
{
    return ScalerGetBit(P3A_E1_OSD_SUB_BLENDING_CTRL, _BIT1);
}

//--------------------------------------------------
// Description  : Set mixer gosd enable/disable
// Input Value  :  _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerOsdSubBlendingSetGosdMixerEnable(bit bGosdEn)
{
    ScalerSetBit(P3A_E1_OSD_SUB_BLENDING_CTRL, ~_BIT0, ((BYTE)bGosdEn & _BIT0));
}

//--------------------------------------------------
// Description  : Get mixer gosd enable/disable
// Input Value  : None
// Output Value : _ENABLE / _DISABLE
//--------------------------------------------------
bit ScalerOsdSubBlendingGetGosdMixerEnable(void)
{
    return ScalerGetBit(P3A_E1_OSD_SUB_BLENDING_CTRL, _BIT0);
}

#endif

