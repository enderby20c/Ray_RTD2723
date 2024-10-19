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
// ID Code      : UserCommonColorHDRInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HDR10_SUPPORT == _ON)
#define CLR_HDR10_SETTING_DATA(region)                                  (memset(&g_pstColorHDR10Setting[ScalerRegionGetIndex(region)], 0, sizeof(StructHDR10Setting)))
#define CLR_HDR10_USER_DATA(region)                                     (memset(&(g_pstColorHDR10UserData[ScalerRegionGetIndex(region)]), 0, sizeof(StructHDR10UserData)))
#define SET_HDR10_MODE_STATUS(region, x)                                (g_penumColorHDR10ModeStatus[ScalerRegionGetIndex(region)] = (x))
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
#define SET_FREESYNC_II_MODE_STATUS(region, x)                          (g_penumColorFreesyncIIModeStatus[ScalerRegionGetIndex(region)] = (x))
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of max region index for SBTM
//--------------------------------------------------
#define _SBTM_MAX_REGION_COUNT                                          2 // SBTM not support over 2P
#define CLR_SBTM_INFO_DATA(region)                                      (memset(&g_pstColorHDR10SBTMInfo[ScalerRegionGetIndex(region)], 0, sizeof(StructHDR10SBTMInfo)))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_HDR10_SUPPORT == _ON)
extern StructHDR10Setting g_pstColorHDR10Setting[_MULTI_DISPLAY_MAX];
extern StructHDR10UserData g_pstColorHDR10UserData[_MULTI_DISPLAY_MAX];
extern EnumHDR10ModeDef g_penumColorHDR10ModeStatus[_MULTI_DISPLAY_MAX];

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
extern BYTE g_pucColorHDR10StepLessTMIGLUT[197];
#endif
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
extern EnumFreeSyncSupport g_penumColorFreesyncIIModeStatus[_MULTI_DISPLAY_MAX];
#endif
#if(_HDMI_SBTM_SUPPORT == _ON)
extern StructHDR10SBTMInfo  g_pstColorHDR10SBTMInfo[_SBTM_MAX_REGION_COUNT];
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_ULTRA_HDR_SUPPORT == _ON)
extern void UserCommonColorHDRInitialSetting(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonColorHDRHandler(EnumDisplayRegion enumDisplayRegion);
#if(_FREESYNC_II_SUPPORT == _ON)
extern void UserCommonColorHDRAdjustFreeSyncIIMode(EnumDisplayRegion enumDisplayRegion);
#endif
#if(_ADVANCED_HDR10_SUPPORT == _ON)
extern void UserCommonColorAdvancedHDR10Reset(void);
extern EnumAdvancedHDR10EnlargeDelaySupport UserCommonColorAdvancedHDR10GetEnlargeDelaySupport(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonColorAdvancedHDR10InitialSetting(void);
#endif

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
extern void UserCommonColorHDRGetBackLightAdaptiveTMTable(EnumDisplayRegion enumDisplayRegion, WORD usBackLight, WORD usBackLightMax, EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus, StructColorYmappingSetting *pstYmData);
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
extern WORD UserCommonColorHDRGetBackLightAdaptiveTMNode(BYTE ucIGIndex);
#endif
#endif

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
extern void UserCommonColorHDRGetMasteringLvStepLessTMTable(EnumDisplayRegion enumDisplayRegion, WORD usMaxDisplayMasteringLv, EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus);
#if(_GLOBAL_DIMMING_FUNCTION == _ON)
extern WORD UserCommonColorHDRGetMasteringLvStepLessTMNode(BYTE ucIGIndex);
#endif
extern WORD UserCommonColorHDRGetHDR10ApplyLv(EnumDisplayRegion enumDisplayRegion);
#endif
#endif
