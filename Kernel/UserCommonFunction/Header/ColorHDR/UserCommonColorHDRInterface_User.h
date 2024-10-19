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
// ID Code      : UserCommonColorHDRInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HDR10_SUPPORT == _ON)
#define _MAX_BACKLIGHT_RATIO                                            255
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of HDR Flow
//--------------------------------------------------
typedef enum
{
    _HDR_FLOW_COLOR_PROC_INITIAL,
    _HDR_FLOW_MODE_STATUS_ACTIVE,
    _HDR_FLOW_OSD_MODE_CHANGE,
    _HDR_FLOW_OSD_DARK_ENHANCE,
}EnumHDRFlowStatus;

//--------------------------------------------------
// Enumerations of HDR10 Info EOTF
//--------------------------------------------------
typedef enum
{
    _HDR_INFO_EOTF_TRADITIONAL_GAMMA_SDR = 0x00,
    _HDR_INFO_EOTF_TRADITIONAL_GAMMA_HDR = 0x01,
    _HDR_INFO_EOTF_SMPTE_ST_2084 = 0x02,
    _HDR_INFO_EOTF_HLG = 0x03,
    _HDR_INFO_EOTF_RESERVED = 0x04,
} EnumHDR10InfoEOTF;

//--------------------------------------------------
// Definitions of HDR Change Mode
//--------------------------------------------------
typedef enum
{
    _HDR10_INFO_NO_CHANGE = 0x00,
    _HDR10_INFO_EOTF_CHANGE = 0x01,
    _HDR10_INFO_PRIMARIES_CHANGE = 0x02,
    _HDR10_INFO_MAX_LV_CHANGE = 0x03,
}EnumHDR10ChangeStatus;

//--------------------------------------------------
// Definitions of HDR10 STATIC Max Mastering Lv Type
//--------------------------------------------------
typedef enum
{
    _HDR10_STATIC_MASTERING_LV_TYPE_540, // 540 nits
    _HDR10_STATIC_MASTERING_LV_TYPE_1200, // 1200 nits
    _HDR10_STATIC_MASTERING_LV_TYPE_4000, // 4000 nits
    _HDR10_STATIC_MASTERING_LV_TYPE_10000, // 10000 nits
}EnumHDR10StaticMasteringLvType;

//--------------------------------------------------
// Definitions of Advanced HDR10 Support Display Mode
//--------------------------------------------------
typedef enum
{
    _ADVANCED_HDR10_DISP_MODE_SUPPORT_OFF, // Display Mode not support
    _ADVANCED_HDR10_DISP_MODE_SUPPORT_ON_DEMO_MODE_ON, // Display Mode support, but Demo Mode is on
    _ADVANCED_HDR10_DISP_MODE_SUPPORT_ON_DEMO_MODE_OFF, // Display Mode support, and Demo Mode is off
}EnumAdvancedHDR10SupportDisplayMode;

//--------------------------------------------------
// Structure of HDR10 Setting
//--------------------------------------------------
typedef struct
{
    EnumHDR10InfoEOTF enumHDR10EOTFSetting;
    EnumHDR10MaxMasteringLvType enumHDR10MaxLVSetting;
    WORD usHDR10StepLessMaxLVSetting;
    WORD usHDR10UserModeMaxLVSetting;
} StructHDR10Setting;

//--------------------------------------------------
// Enumerations of HDR10 Info EOTF
//--------------------------------------------------
typedef enum
{
    _HDR10_BACKLIGHT_ADAPTIVE_TM_BACKLIGHT_OSD = 0x00,
    _HDR10_BACKLIGHT_ADAPTIVE_TM_BACKLIGHT_MAX = 0x01,
} EnumHDR10BackLightAdaptiveTMBackLightStatus;

//--------------------------------------------------
// Enumerations of HDR10 Adjust EagleSight Full Region
//--------------------------------------------------
typedef enum
{
    _HDR10_ADJUST_EAGLE_SIGHT_FULL_REGION_OFF = 0x00,
    _HDR10_ADJUST_EAGLE_SIGHT_FULL_REGION_ON = 0x01, // HDR adjust Main & Sub Region at the same time
} EnumHDR10AdjustEagleSightFullStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_ULTRA_HDR_SUPPORT == _ON)
extern void UserCommonColorHDRAdjust(EnumDisplayRegion enumDisplayRegion);
extern EnumDisplayRegion UserCommonColorHDRGetDisplayRegion(EnumSelRegion enumSelRegion);

#if(_HDR10_SUPPORT == _ON)
extern EnumHDR10Status UserCommonColorHDRGetHDR10Status(EnumDisplayRegion enumDisplayRegion);
extern EnumHDR10MaxMasteringLvType UserCommonColorHDRGetHDR10LvType(EnumDisplayRegion enumDisplayRegion, StructHDR10UserData stHDR10UserData);
extern EnumHDR10MaxMasteringLvType UserCommonColorHDRGetHDR10ApplyLvType(EnumDisplayRegion enumDisplayRegion);
extern EnumHDR10InfoEOTF UserCommonColorHDR10GetEOTFSetting(EnumDisplayRegion enumDisplayRegion);
extern EnumHDR10ColorMatrix UserCommonColorHDRGetHDR10ColorMatrix(EnumDisplayRegion enumDisplayRegion);
extern EnumHDR10ChangeStatus UserCommonColorHDR10GetHDRChangeStatus(EnumDisplayRegion enumDisplayRegion);
extern WORD UserCommonColorHDRGetHDR10MaxDisplayLv(EnumDisplayRegion enumDisplayRegion);
extern WORD UserCommonColorHDRUserGetPanelMaxLv(EnumDisplayRegion enumDisplayRegion);

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
extern void UserCommonColorHDRAdjustHDR10LightEnhance(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif

#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
extern void UserCommonColorHDRAdjustHDR10ColorEnhance(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif

extern WORD UserCommonColorHDRGetHDR10ColorMatrixAddress(EnumHDR10ColorMatrix enumHDR10ColorMatrix);
extern WORD UserCommonColorHDRGetHDR10IGLUTAddr(EnumHDR10MaxMasteringLvType enumHDR10MaxMasteringLvType, EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus, EnumHDR10FixedPointToneMappingStatus enumHDR10FixedPointToneMappingStatus);
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
extern bit UserCommonColorHDRGetFreesynIIStatus(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
extern EnumAdvancedHDR10SupportDisplayMode UserCommonColorHDRCheckAdvancedHDR10SupportDisplayMode(void);
extern EnumAdvancedHDR10Status UserCommonColorHDRGetAdvancedHDR10Status(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_HLG_SUPPORT == _ON)
extern void UserCommonColorHDRHLGUserModeAdjust(EnumSelRegion enumSelRegion);
#endif

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
extern EnumHDR10BackLightAdaptiveTMStatus UserCommonColorHDRGetBackLightAdaptiveTMStatus(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonColorHDRBackLightAdaptiveTMAdjust(EnumSelRegion enumSelRegion);
extern EnumHDR10BackLightAdaptiveTMBackLightStatus UserCommonColorHDRGetBackLightAdaptiveTMBackLightStatus(void);
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
extern EnumHDR10SBTMStatus UserCommonColorHDRGetSBTMStatus(EnumDisplayRegion enumDisplayRegion);
extern EnumHDR10SBTMMode UserCommonColorHDR10GetSBTMMode(EnumDisplayRegion enumDisplayRegion);
#endif
#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)

