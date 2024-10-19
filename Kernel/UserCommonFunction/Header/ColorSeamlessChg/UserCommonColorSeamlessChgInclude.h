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
// ID Code      : UserCommonColorSeamlessChgInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
#define GET_COLORIMETRY_SETTING(region)                (g_pstColorimetrySetting[ScalerRegionGetIndex(region)].enumColorimetrySetting)
#define SET_COLORIMETRY_SETTING(region, x)             (g_pstColorimetrySetting[ScalerRegionGetIndex(region)].enumColorimetrySetting = (x))

#define GET_EXT_COLORIMETRY_SETTING(region)            (g_pstColorimetrySetting[ScalerRegionGetIndex(region)].enumColorimetryEXTSetting)
#define SET_EXT_COLORIMETRY_SETTING(region, x)         (g_pstColorimetrySetting[ScalerRegionGetIndex(region)].enumColorimetryEXTSetting = (x))

#if(_HDR10_SUPPORT == _ON)
#define GET_HDR10_UPDATE_COLORIMETRY(region)           (g_pstColorimetryUpdate[ScalerRegionGetIndex(region)].b1HDR10UpdateColorimetry)
#define SET_HDR10_UPDATE_COLORIMETRY(region)           (g_pstColorimetryUpdate[ScalerRegionGetIndex(region)].b1HDR10UpdateColorimetry = (_TRUE))
#define CLR_HDR10_UPDATE_COLORIMETRY(region)           (g_pstColorimetryUpdate[ScalerRegionGetIndex(region)].b1HDR10UpdateColorimetry = (_FALSE))
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
#define GET_FREESYNC_II_UPDATE_COLORIMETRY(region)     (g_pstColorimetryUpdate[ScalerRegionGetIndex(region)].b1FreesyncIIUpdateColorimetry)
#define SET_FREESYNC_II_UPDATE_COLORIMETRY(region)     (g_pstColorimetryUpdate[ScalerRegionGetIndex(region)].b1FreesyncIIUpdateColorimetry = (_TRUE))
#define CLR_FREESYNC_II_UPDATE_COLORIMETRY(region)     (g_pstColorimetryUpdate[ScalerRegionGetIndex(region)].b1FreesyncIIUpdateColorimetry = (_FALSE))
#endif

#define GET_SDR_UPDATE_COLORIMETRY(region)             (g_pstColorimetryUpdate[ScalerRegionGetIndex(region)].b1SDRUpdateColorimetry)
#define SET_SDR_UPDATE_COLORIMETRY(region)             (g_pstColorimetryUpdate[ScalerRegionGetIndex(region)].b1SDRUpdateColorimetry = (_TRUE))
#define CLR_SDR_UPDATE_COLORIMETRY(region)             (g_pstColorimetryUpdate[ScalerRegionGetIndex(region)].b1SDRUpdateColorimetry = (_FALSE))
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
#define GET_COLORSPACE_SETTING(region)                 (g_pstColorFormatSetting[ScalerRegionGetIndex(region)].enumColorSpaceSetting)
#define SET_COLORSPACE_SETTING(region, x)              (g_pstColorFormatSetting[ScalerRegionGetIndex(region)].enumColorSpaceSetting = (x))

#define GET_COLORDEPTH_SETTING(region)                 (g_pstColorFormatSetting[ScalerRegionGetIndex(region)].ucColorDepthSetting)
#define SET_COLORDEPTH_SETTING(region, x)              (g_pstColorFormatSetting[ScalerRegionGetIndex(region)].ucColorDepthSetting = (x))
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Structure of Colorimetry Setting
//--------------------------------------------------
typedef struct
{
    EnumColorimetry enumColorimetrySetting;
    EnumColorimetryExt enumColorimetryEXTSetting;
} StructColorimetrySetting;

//--------------------------------------------------
// Definitions of Colorimetry Change Mode
//--------------------------------------------------
typedef enum
{
    _COLORIMETRY_NO_CHANGE = 0x00,
    _COLORIMETRY_CHANGE = 0x01,
}EnumColorimetryChangeStatus;

//--------------------------------------------------
// Structure of Colorimetry Setting
//--------------------------------------------------
typedef struct
{
    BYTE b1HDR10UpdateColorimetry : 1;
    BYTE b1SDRUpdateColorimetry : 1;
    BYTE b1FreesyncIIUpdateColorimetry : 1;
} StructColorimetryUpdate;
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
//--------------------------------------------------
// Structure of Colorformat Setting
//--------------------------------------------------
typedef struct
{
    EnumColorSpace enumColorSpaceSetting;
    BYTE ucColorDepthSetting;
} StructColorFormatSetting;

//--------------------------------------------------
// Definitions of Colorimetry Change Mode
//--------------------------------------------------
typedef enum
{
    _COLORFORMAT_NO_CHANGE = 0x00,
    _COLORFORMAT_CHANGE = 0x01,
}EnumColorFormatChangeStatus;
#endif
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
extern StructColorimetrySetting g_pstColorimetrySetting[_MULTI_DISPLAY_MAX];
extern StructColorimetryUpdate g_pstColorimetryUpdate[_MULTI_DISPLAY_MAX];
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern StructColorFormatSetting g_pstColorFormatSetting[_MULTI_DISPLAY_MAX];
#endif
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
extern void UserCommonColorSeamlessChgInitial(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
extern void UserCommonColorDMFormatChgWoResetInitial(EnumDisplayRegion enumDisplayRegion);
#endif

