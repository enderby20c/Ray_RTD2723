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
// ID Code      : ScalerColorHDR10Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    WORD *pusHDRLinearOut;
    BYTE ucLvMatchBound;
    WORD usLvMatchBoundGain;
} StructHDR10BackLightAdaptiveTMData;

//------------------------------------------------------------
// Definitions of HDR10 Max Mastering Lv Type for Stepless TM
//------------------------------------------------------------
typedef enum
{
    _HDR10_STEPLESS_TM_LV_TYPE_1200, // 1200 nits, or 1000nit when _HDR10_EETF_TONEMAPPING_SUPPORT is On!!
    _HDR10_STEPLESS_TM_LV_TYPE_4000, // 4000 nits
    _HDR10_STEPLESS_TM_LV_TYPE_10000, // 10000 nits
    _HDR10_STEPLESS_TM_LV_TYPE_540, // 540 nits
    _HDR10_STEPLESS_TM_LV_TYPE_NOTM, // Tone Mapping by source based on peak lv
} EnumHDR10MaxMasteringSteplessLvType;

//------------------------------------------------------------
// Definitions of HDR10 Adaptive Lv Type for BackLight Adaptive TM
//------------------------------------------------------------
typedef enum
{
    _HDR10_ADAPTIVE_TM_LV1,
    _HDR10_ADAPTIVE_TM_LV2,
    _HDR10_ADAPTIVE_TM_LV3,
    _HDR10_ADAPTIVE_TM_LV4,
    _HDR10_ADAPTIVE_NOTM,
} EnumHDR10BacklightAdaptiveTMType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON) || (_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON))
extern void ScalerColorPCMGetIG129NodeLUT(BYTE ucBank, BYTE *pucIGLUTFlashAddress, WORD *pusIGLUT, BYTE *pucTH);
extern void ScalerColorPCMSetIG129NodeFlashLUT(WORD *pusIGLUT, BYTE *pucIGFlashLUT);
extern WORD ScalerColorPCMGet129NodetIGLUTNode(BYTE ucBank, BYTE *pucIGLUTFlashAddress, BYTE ucIGLUTIndex, BYTE *pucTH);
#endif
extern void ScalerColorHDRGetBackLightAdaptiveTable(BYTE ucOGCBank, WORD usPanelMaxLv, WORD usBackLight, WORD usBackLightMax, EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus, StructHDR10BackLightAdaptiveTMData *pstHDRData);
extern void ScalerColorYMappingGetHDR10BackLightAdaptiveTMLUT(BYTE ucOGCBank, EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus, BYTE ucLvMatchBound, WORD usLvMatchBoundGain, WORD *pusHDRLinearOut, BYTE *pucYMLUT);
extern void ScalerColorHDRGetMasteringLvStepLessTMTable(BYTE ucOGCBank, WORD usPanelMaxLv, WORD usMaxDisplayMasteringLv, EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus, BYTE *pucIGFlashLUT);

