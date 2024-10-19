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
// ID Code      : UserCommonColorHDRInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_ULTRA_HDR_SUPPORT == _ON) && (_FREESYNC_II_SUPPORT == _ON))
#define CLR_FREESYNC_II_SETTING_DATA(region)                            (memset(&g_pstColorFreeSyncIISetting[ScalerRegionGetIndex(region)], 0, sizeof(StructFreeSyncIIInfo)))

#define GET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING(region)              (g_pstColorFreeSyncIISetting[ScalerRegionGetIndex(region)].b1NativeColorSpaceEnable)
#define SET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING(region, x)           (g_pstColorFreeSyncIISetting[ScalerRegionGetIndex(region)].b1NativeColorSpaceEnable = (x))

#define GET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING(region)        (g_pstColorFreeSyncIISetting[ScalerRegionGetIndex(region)].b1BacklightControlEnable)
#define SET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING(region, x)     (g_pstColorFreeSyncIISetting[ScalerRegionGetIndex(region)].b1BacklightControlEnable = (x))

#define GET_FREESYNC_II_LOCAL_DIMMING_DISABLE_SETTING(region)           (g_pstColorFreeSyncIISetting[ScalerRegionGetIndex(region)].b1LocalDimmingDisable)
#define SET_FREESYNC_II_LOCAL_DIMMING_DISABLE_SETTING(region, x)        (g_pstColorFreeSyncIISetting[ScalerRegionGetIndex(region)].b1LocalDimmingDisable = (x))

#define GET_FREESYNC_II_EOTF_TYPE_SETTING(region)                       (g_pstColorFreeSyncIISetting[ScalerRegionGetIndex(region)].b5EOTFType)
#define SET_FREESYNC_II_EOTF_TYPE_SETTING(region, x)                    (g_pstColorFreeSyncIISetting[ScalerRegionGetIndex(region)].b5EOTFType = (x))

#define GET_FREESYNC_II_BACKLIGHT_CONTROL_RATIO_SETTING(region)         (g_pstColorFreeSyncIISetting[ScalerRegionGetIndex(region)].ucBacklightControlRatio)
#define SET_FREESYNC_II_BACKLIGHT_CONTROL_RATIO_SETTING(region, x)      (g_pstColorFreeSyncIISetting[ScalerRegionGetIndex(region)].ucBacklightControlRatio = (x))
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of HDR Max Mastering Lv
//--------------------------------------------------
#define _HDR10_MAX_MASTERING_LV_540                                     540
#if(_HDR10_EETF_TONEMAPPING_SUPPORT == _ON)
#define _HDR10_MAX_MASTERING_LV_1200                                    1000
#else
#define _HDR10_MAX_MASTERING_LV_1200                                    1200
#endif
#define _HDR10_MAX_MASTERING_LV_4000                                    4000
#define _HDR10_MAX_MASTERING_LV_10000                                   10000
#define _HDR10_STEPLESS_MAX_MASTERING_LV_CHG_THRESHOLD                  10 // the amount of lv difference to judge if mastering lv changes
#define _HDR10_USER_MODE_MAX_MASTERING_LV_CHG_THRESHOLD                 100 // the amount of lv difference to judge if mastering lv changes

#define GET_HDR10_EOTF_SETTING(region)                                  (g_pstColorHDR10Setting[ScalerRegionGetIndex(region)].enumHDR10EOTFSetting)
#define SET_HDR10_EOTF_SETTING(region, x)                               (g_pstColorHDR10Setting[ScalerRegionGetIndex(region)].enumHDR10EOTFSetting = (x))

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
#define GET_HDR10_STEPLESS_MAX_LV_SETTING(region)                       (g_pstColorHDR10Setting[ScalerRegionGetIndex(region)].usHDR10StepLessMaxLVSetting)
#define SET_HDR10_STEPLESS_MAX_LV_SETTING(region, x)                    (g_pstColorHDR10Setting[ScalerRegionGetIndex(region)].usHDR10StepLessMaxLVSetting = (x))
#define GET_HDR10_STEPLESS_MAX_LV_SETTING_CHG(region, x)                (ABSDWORD(g_pstColorHDR10Setting[ScalerRegionGetIndex(region)].usHDR10StepLessMaxLVSetting, (x)) >= _HDR10_STEPLESS_MAX_MASTERING_LV_CHG_THRESHOLD)
#endif

#if(_HDR10_USER_MASTERING_LV_CHANGE_SUPPORT == _ON)
#define GET_HDR10_USER_MAX_LV_SETTING(region)                           (g_pstColorHDR10Setting[ScalerRegionGetIndex(region)].usHDR10UserModeMaxLVSetting)
#define SET_HDR10_USER_MAX_LV_SETTING(region, x)                        (g_pstColorHDR10Setting[ScalerRegionGetIndex(region)].usHDR10UserModeMaxLVSetting = (x))
#define GET_HDR10_USER_MAX_LV_SETTING_CHG(region, x)                    (ABSDWORD(g_pstColorHDR10Setting[ScalerRegionGetIndex(region)].usHDR10UserModeMaxLVSetting, (x)) >= _HDR10_USER_MODE_MAX_MASTERING_LV_CHG_THRESHOLD)
#endif
#define GET_HDR10_MAX_LV_SETTING(region)                                (g_pstColorHDR10Setting[ScalerRegionGetIndex(region)].enumHDR10MaxLVSetting)
#define SET_HDR10_MAX_LV_SETTING(region, x)                             (g_pstColorHDR10Setting[ScalerRegionGetIndex(region)].enumHDR10MaxLVSetting = (x))

#define SET_HDR10_USER_DATA(region, x)                                  (memcpy(&(g_pstColorHDR10UserData[ScalerRegionGetIndex(region)]), &(x), sizeof(StructHDR10UserData)))
#define GET_HDR10_USER_DATA(region)                                     (g_pstColorHDR10UserData[ScalerRegionGetIndex(region)])
#define GET_HDR10_USER_MASTERING_LV0_TYPE(region)                       (g_pstColorHDR10UserData[ScalerRegionGetIndex(region)].enumHDR10MaxMasteringLv0Type)
#define GET_HDR10_USER_FORCE_MODE_MASTERING_LV_TYPE(region)             (g_pstColorHDR10UserData[ScalerRegionGetIndex(region)].enumHDR10Force2084MasteringLvType)
#define GET_HDR10_USER_DEF_PANEL_LV_TYPE(region)                        (g_pstColorHDR10UserData[ScalerRegionGetIndex(region)].enumHDR10UserDefineMaxPanelLvType)
#define GET_HDR10_USER_MASTERING_STEPLESS_TM_STATUS(region)             (g_pstColorHDR10UserData[ScalerRegionGetIndex(region)].enumHDR10MasteringLvStepLessTMStatus)
#define GET_HDR10_USER_FORCE_MASTERING_LV_STATUS(region)                (g_pstColorHDR10UserData[ScalerRegionGetIndex(region)].enumHDR10UserForceMasteringLvStatus)

#define GET_HDR10_MODE_STATUS(region)                                   (g_penumColorHDR10ModeStatus[ScalerRegionGetIndex(region)])

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
#define GET_HDR10_USER_STEPLESS_FORCE_MODE_MASTERING_LV(region)         (g_pstColorHDR10UserData[ScalerRegionGetIndex(region)].usHDR10StepLessForce2084MasteringLv)
#define GET_HDR10_USER_STEPLESS_MASTERING_LV0(region)                   (g_pstColorHDR10UserData[ScalerRegionGetIndex(region)].usHDR10StepLessMaxMasteringLv0)
#endif
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
#define SET_ADVANCED_HDR10_SUPPORT(x)                                   (g_enumColorAdvancedHDR10Support = (x))
#define GET_ADVANCED_HDR10_SUPPORT()                                    (g_enumColorAdvancedHDR10Support)
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
#define GET_FREESYNC_II_MODE_STATUS(region)                             (g_penumColorFreesyncIIModeStatus[ScalerRegionGetIndex(region)])
#endif

#define GET_HDR_CHANGE_STATUS(region)                                   (g_penumColorHDR10ChangeStatus[ScalerRegionGetIndex(region)])
#define SET_HDR_CHANGE_STATUS(region, x)                                (g_penumColorHDR10ChangeStatus[ScalerRegionGetIndex(region)] = (x))

#if(_HDMI_SBTM_SUPPORT == _ON)
#define GET_HDR10_SBTM_MODE(region)                                     (g_pstColorHDR10SBTMInfo[ScalerRegionGetIndex(region)].enumHDR10SBTMMode)
#define SET_HDR10_SBTM_MODE(region, x)                                  (g_pstColorHDR10SBTMInfo[ScalerRegionGetIndex(region)].enumHDR10SBTMMode = (x))
#define GET_HDR10_SBTM_GRDM_LUM_TYPE(region)                            (g_pstColorHDR10SBTMInfo[ScalerRegionGetIndex(region)].enumHDR10SBTMGRDMLumMaxType)
#define SET_HDR10_SBTM_GRDM_LUM_TYPE(region, x)                         (g_pstColorHDR10SBTMInfo[ScalerRegionGetIndex(region)].enumHDR10SBTMGRDMLumMaxType = (x))
#define GET_HDR10_SBTM_GRDM_MIN_TYPE(region)                            (g_pstColorHDR10SBTMInfo[ScalerRegionGetIndex(region)].enumHDR10SBTMGRDMMinType)
#define SET_HDR10_SBTM_GRDM_MIN_TYPE(region, x)                         (g_pstColorHDR10SBTMInfo[ScalerRegionGetIndex(region)].enumHDR10SBTMGRDMMinType = (x))
#define GET_HDR10_SBTM_TYPE(region)                                     (g_pstColorHDR10SBTMInfo[ScalerRegionGetIndex(region)].enumHDR10SBTMType)
#define SET_HDR10_SBTM_TYPE(region, x)                                  (g_pstColorHDR10SBTMInfo[ScalerRegionGetIndex(region)].enumHDR10SBTMType = (x))
#define GET_HDR10_SBTM_PBLIMITINT(region)                               (g_pstColorHDR10SBTMInfo[ScalerRegionGetIndex(region)].usFrmPbLimitInt)
#define SET_HDR10_SBTM_PBLIMITINT(region, x)                            (g_pstColorHDR10SBTMInfo[ScalerRegionGetIndex(region)].usFrmPbLimitInt = (x))
#endif
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDR10 Light Enhance Max Mastering Lv Type
//--------------------------------------------------
typedef enum
{
    _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_540, // 540 nits
    _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_1200, // 1200 nits
    _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_4000, // 4000 nits
    _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_10000, // 10000 nits
}EnumHDR10LightEnhanceMaxMasteringLv;

//--------------------------------------------------
// Definitions of FreeSync II Change Mode
//--------------------------------------------------
typedef enum
{
    _FREESYNC_II_INFO_NO_CHANGE = 0x00,
    _FREESYNC_II_COLOR_SPACE_CHANGE = _BIT0,
    _FREESYNC_II_BACKLIGHT_CONTROL_CHANGE = _BIT1,
    _FREESYNC_II_LOCAL_DIMMING_CHANGE = _BIT2,
    _FREESYNC_II_EOTF_TYPE_CHANGE = _BIT3,
    _FREESYNC_II_BACKLIGHT_RATIO_CHANGE = _BIT4,
}EnumFreeSyncIIChangeStatus;

//--------------------------------------------------
// Definitions of Advanced HDR10 Change Mode
//--------------------------------------------------
typedef enum
{
    _ADVANCED_HDR10_INFO_NO_CHANGE = 0x00,
    _ADVANCED_HDR10_INFO_CHANGE = 0x01,
}EnumAdvancedHDR10ChangeStatus;

//--------------------------------------------------
// Definitions of HDR10 SBTM Change Mode
//--------------------------------------------------
typedef enum
{
    _HDR10_SBTM_INFO_NO_CHANGE = 0x00,
    _HDR10_SBTM_MODE_CHANGE = _BIT0,
    _HDR10_SBTM_TYPE_CHANGE = _BIT1,
    _HDR10_SBTM_GRDM_LUM_CHANGE = _BIT2,
    _HDR10_SBTM_GRDM_MIN_CHANGE = _BIT3,
    _HDR10_SBTM_PBLIMIT_CHANGE = _BIT4,
}EnumHDR10SBTMChangeStatus;


#if(_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of FreeSync II Info
//--------------------------------------------------
typedef enum
{
    _FREESYNC_II_EOTF_NO_SUPPORT_GET_BIT = 0x00,
    _FREESYNC_II_EOTF_SRGB_GET_BIT = _BIT0,
    _FREESYNC_II_EOTF_BT709_GET_BIT = _BIT1,
    _FREESYNC_II_EOTF_GAMMA_22_GET_BIT = _BIT2,
    _FREESYNC_II_EOTF_GAMMA_26_GET_BIT = _BIT3,
    _FREESYNC_II_EOTF_PQ_INTERIM_GET_BIT = _BIT4,
}EnumFreeSyncIIEOTFGetBit;
#endif

typedef struct
{
    EnumHDRTargetStatus enumHDRTargetStatus;
    EnumFreeSyncIIChangeStatus enumFreeSyncIIChangeStatus;
    EnumHDR10ChangeStatus enumHDR10ChangeStatus;
    EnumHDR10SBTMChangeStatus enumHDR10SBTMChangeStatus;
} StructHDRStatusInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_ULTRA_HDR_SUPPORT == _ON)
extern EnumHDR10ChangeStatus g_penumColorHDR10ChangeStatus[_MULTI_DISPLAY_MAX];
#if(_FREESYNC_II_SUPPORT == _ON)
extern StructFreeSyncIIInfo g_pstColorFreeSyncIISetting[_MULTI_DISPLAY_MAX];
#endif
#endif
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_ULTRA_HDR_SUPPORT == _ON)
extern void UserCommonColorHDRGetTargetStatus(EnumDisplayRegion enumDisplayRegion, StructHDRStatusInfo *pstHDRStatusInfo);

#if(_HDR10_SUPPORT == _ON)
extern EnumHDR10StaticMasteringLvType UserCommonColorHDRGetHDR10LvTypeForStaticMastering(EnumSelRegion enumSelRegion);
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
extern bit UserCommonColorHDRGetFreeSyncIILDDisable(EnumDisplayRegion enumDisplayRegion);
extern EnumFreeSyncIIEOTFType UserCommonColorHDRGetFreeSyncIIEOTFType(EnumDisplayRegion enumDisplayRegion);
extern bit UserCommonColorHDRGetFreesyncIIDisplayMode(void);
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
extern void UserCommonColorAdvancedHDR10VSIFSupportSwitch(void);
#endif
#if(_HDMI_SBTM_SUPPORT == _ON)
extern EnumHDR10SBTMGRDMLumMaxType UserCommonColorHDR10GetSBTMGRDMLumType(EnumDisplayRegion enumDisplayRegion);
extern EnumHDR10SBTMGRDMMinType UserCommonColorHDR10GetSBTMGRDMMinType(EnumDisplayRegion enumDisplayRegion);
extern EnumHDR10SBTMType UserCommonColorHDR10GetSBTMType(EnumDisplayRegion enumDisplayRegion);
extern WORD UserCommonColorHDR10GetSBTMPBLIMITINT(EnumDisplayRegion enumDisplayRegion);
#endif

#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)
