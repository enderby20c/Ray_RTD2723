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
// ID Code      : UserCommonDisplaySettingInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_EAGLE_SIGHT_SUPPORT == _ON)
#define SET_EAGLE_SIGHT_USER_ENABLE(x)                  (g_stMDomainEagleSightSetting.enumEagleSightEnable = (x))
#define GET_EAGLE_SIGHT_USER_ENABLE()                   (g_stMDomainEagleSightSetting.enumEagleSightEnable)

#define SET_EAGLE_SIGHT_USER_RATIO(x)                   (g_stMDomainEagleSightSetting.enumEagleSightRatio = (x))
#define GET_EAGLE_SIGHT_USER_RATIO()                    (g_stMDomainEagleSightSetting.enumEagleSightRatio)

#define SET_EAGLE_SIGHT_USER_CAP_POS(x)                 (g_stMDomainEagleSightSetting.enumEagleSightCapPosition = (x))
#define GET_EAGLE_SIGHT_USER_CAP_POS()                  (g_stMDomainEagleSightSetting.enumEagleSightCapPosition)

#define SET_EAGLE_SIGHT_USER_DISP_POS(x)                (g_stMDomainEagleSightSetting.enumEagleSightDispPosition = (x))
#define GET_EAGLE_SIGHT_USER_DISP_POS()                 (g_stMDomainEagleSightSetting.enumEagleSightDispPosition)

#define SET_EAGLE_SIGHT_USER_TRANSPARENCY(x)            (g_stMDomainEagleSightSetting.ucTransparencyLevel = (x))
#define GET_EAGLE_SIGHT_USER_TRANSPARENCY()             (g_stMDomainEagleSightSetting.ucTransparencyLevel)

#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
#define SET_EAGLE_SIGHT_USER_CIRCLE_WIN_ENABLE(x)       (g_stMDomainEagleSightSetting.enumEagleSightCircleWinEnable = (x))
#define GET_EAGLE_SIGHT_USER_CIRCLE_WIN_ENABLE()        (g_stMDomainEagleSightSetting.enumEagleSightCircleWinEnable)
#endif
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of Eagle Sight Display Setting Rgn
//--------------------------------------------------
typedef enum
{
    _EAGLE_SIGHT_RGN_MAIN_SUB,
    _EAGLE_SIGHT_RGN_SUB,
} EnumEagleSightRegion;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern StructEagleSightSetting g_stMDomainEagleSightSetting;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonDisplayAdjustInputTiming(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonDisplayAdjustDisplayTiming(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonDisplayGetMDomainCustomInfo(StructDisplayCustomizedData *pstDisplayCustomizedData);
extern void UserCommonDisplaySetDVCustomizedDefault(void);

#if((_DRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
extern EnumGetIVFFromTableSearch UserCommonDisplayDrrGetIVFmax(WORD *pusVfreqMax, EnumInputPort enumInputPort);
#endif

#if(_DRR_SUPPORT == _ON)
#if(_SEARCH_DRR_IVF_PRIORITY_BY_USER == _ON)
extern EnumDrrGetIVFPriority UserCommonDisplayGetDrrIVFPriority(EnumInputPort enumInputPort, WORD *pusIVfreq);
#endif
#endif

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
extern void UserCommonDisplayMbrStrobeBacklightEnableSeq(bit bLightCtrl);
extern EnumMbrBacklightMode UserCommonDisplayMbrGetBacklightMode(void);
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void UserCommonDisplayMbrDrrHandler(void);
extern bit UserCommonDisplayMbrDrrCheckHW(void);
#endif
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void UserCommonDisplayResetRtkAdvMbrStatus(void);
#endif
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern void UserCommonDisplayEagleSightTransparencySetting(BYTE ucLevel);
#endif
