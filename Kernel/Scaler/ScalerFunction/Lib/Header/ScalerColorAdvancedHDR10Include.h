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
// ID Code      : ScalerColorAdvancedHDR10Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _ADVANCEDHDR10_NPCOEFF                                       9

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE pucBezierAnchor[_ADVANCEDHDR10_NPCOEFF];
    WORD pusKneePoint[2];
}StructColorAdvancedHDR10Coeff;

typedef struct
{
    WORD pusBezierAnchor[_ADVANCEDHDR10_NPCOEFF];
    WORD pusKneePoint[2];
}StructColorAdvancedHDR10DHDRCoeff;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_ADVANCED_HDR10_SUPPORT == _ON)
extern void ScalerColorAdvancedHDR10SyncGetLUT(BYTE *pucAdvancedHDR10LUT, const StructColorAdvancedHDR10Coeff *pstColorAdvancedHDR10Coeff, WORD usYMGainCompensate);
extern void ScalerColorAdvancedHDR10SyncBasisOOTF(StructAdvancedHDR10MetaData *pstAdvancedHDR10Metadata, WORD usPanelMaxLv, StructColorAdvancedHDR10Coeff *pstColorAdvancedHDR10Coeff);
extern void ScalerColorAdvancedHDR10SyncGuidedOOTF(StructAdvancedHDR10MetaData *pstAdvancedHDR10Metadata, WORD usPanelMaxLv, StructColorAdvancedHDR10Coeff *pstColorAdvancedHDR10Coeff);
extern WORD ScalerColorAdvancedHDR10SyncGetYMCompensate(EnumAdvancedHDR10HDRMetadataType enumAdvancedHDR10HDRMetadataType, WORD usDistrbution99, WORD usPanelMaxLv);
extern void ScalerColorAdvancedHDR10DHDRSyncBasisOOTF(StructAdvancedHDR10DHDRMetaData *pstAdvancedHDR10DHDRMetaData, WORD usPanelMaxLv, StructColorAdvancedHDR10DHDRCoeff *pstColorAdvancedHDR10DHDRCoeff);
extern void ScalerColorAdvancedHDR10DHDRSyncGuidedOOTF(StructAdvancedHDR10DHDRMetaData *pstAdvancedHDR10DHDRMetaData, WORD usPanelMaxLv, StructColorAdvancedHDR10DHDRCoeff *pstColorAdvancedHDR10DHDRCoeff);
extern void ScalerColorAdvancedHDR10DHDRSyncGetLUT(BYTE *pucAdvancedHDR10LUT, const StructColorAdvancedHDR10DHDRCoeff *pstColorAdvancedHDR10DHDRCoeff, WORD usYMGainCompensate);
#endif

