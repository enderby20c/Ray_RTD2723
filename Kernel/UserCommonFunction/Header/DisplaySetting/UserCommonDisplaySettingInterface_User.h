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
// ID Code      : UserCommonDisplaySettingInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of User OverScan Status
//--------------------------------------------------
typedef enum
{
    _OVERSCAN_FALSE = _FALSE,
    _OVERSCAN_TRUE = _TRUE,
} EnumOverScanStatus;

//--------------------------------------------------
// Enumerations of Aspect Ratio Type Status
//--------------------------------------------------
typedef enum
{
    _ASPECT_RATIO_FULL,
    _ASPECT_RATIO_FIXED,
    _ASPECT_RATIO_ORIGIN,
    _ASPECT_RATIO_REDUCE,
    _ASPECT_RATIO_ENLARGE,
    _ASPECT_RATIO_USER,
} EnumAspectRatioType;

//--------------------------------------------------
// Enumerations of User PIP Sub Adjust Mute
//--------------------------------------------------
typedef enum
{
    _PIP_SUB_ADJUST_MUTE,
    _PIP_SUB_ADJUST_WITHOUT_MUTE,
} EnumPIPSubAdjustMute;

//--------------------------------------------------
// Enumerations of 2P Frame Sync
//--------------------------------------------------
typedef enum
{
    _FRAME_SYNC_SUPPORT_ON,
    _FRAME_SYNC_SUPPORT_OFF,
} EnumFrameSyncSupport;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of Eagle Sight Setting
//--------------------------------------------------
typedef enum
{
    _EAGLE_SIGHT_ENABLE,
    _EAGLE_SIGHT_TRANSPARENCY,
    _EAGLE_SIGHT_RATIO,
    _EAGLE_SIGHT_CAP_POSITION,
    _EAGLE_SIGHT_DISP_POSITION,
    _EAGLE_SIGHT_BORDER,
    _EAGLE_SIGHT_CIRCLE_WIN,
} EnumEagleSightSetting;

//--------------------------------------------------
// Enumerations of Eagle Sight Enable/ Disable
//--------------------------------------------------
typedef enum
{
    _EAGLE_SIGHT_SETTING_DISABLE,
    _EAGLE_SIGHT_SETTING_ENABLE,
} EnumEagleSightEnable;

//--------------------------------------------------
// Enumerations of Eagle Sight Ratio
//--------------------------------------------------
typedef enum
{
    _EAGLE_SIGHT_RATIO_1_5,
    _EAGLE_SIGHT_RATIO_2_0,
    _EAGLE_SIGHT_RATIO_3_0,
    _EAGLE_SIGHT_RATIO_4_0,
} EnumEagleSightRatio;

//--------------------------------------------------
// Enumerations of Eagle Sight Cap Position
//--------------------------------------------------
typedef enum
{
    _EAGLE_SIGHT_CAP_TOP_LEFT,
    _EAGLE_SIGHT_CAP_TOP_RIGHT,
    _EAGLE_SIGHT_CAP_BOT_LEFT,
    _EAGLE_SIGHT_CAP_BOT_RIGHT,
    _EAGLE_SIGHT_CAP_CENTER,
    _EAGLE_SIGHT_CAP_POSITION_USER,
} EnumEagleSightCapPosition;

//--------------------------------------------------
// Enumerations of Eagle Sight Disp Position
//--------------------------------------------------
typedef enum
{
    _EAGLE_SIGHT_DISP_TOP_LEFT,
    _EAGLE_SIGHT_DISP_TOP_RIGHT,
    _EAGLE_SIGHT_DISP_BOT_LEFT,
    _EAGLE_SIGHT_DISP_BOT_RIGHT,
    _EAGLE_SIGHT_DISP_CENTER,
    _EAGLE_SIGHT_DISP_POSITION_USER,
} EnumEagleSightDispPosition;

//--------------------------------------------------
// Enumerations of Eagle Sight Circle Window Enable
//--------------------------------------------------
typedef enum
{
    _EAGLE_SIGHT_CIRCLE_WIN_DISABLE,
    _EAGLE_SIGHT_CIRCLE_WIN_ENABLE,
} EnumEagleSightCircleWinEnable;

//--------------------------------------------------
// Structure of Eagle Sight Setting
//--------------------------------------------------
typedef struct
{
    EnumEagleSightEnable enumEagleSightEnable;
    EnumEagleSightRatio enumEagleSightRatio;
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
    EnumEagleSightCircleWinEnable enumEagleSightCircleWinEnable;
#endif
    EnumEagleSightCapPosition enumEagleSightCapPosition;
    EnumEagleSightDispPosition enumEagleSightDispPosition;
    BYTE ucTransparencyLevel;
} StructEagleSightSetting;

//--------------------------------------------------
// Structure of Eagle Sight Position
//--------------------------------------------------
typedef struct
{
    WORD usHstart;
    WORD usHwidth;
    WORD usVstart;
    WORD usVheight;
} StructEagleSightPosition;
#endif

//--------------------------------------------------
// Enumerations of Backlight Action
//--------------------------------------------------
typedef enum
{
    _BACKLIGHT_DISABLE = _DISABLE,
    _BACKLIGHT_ENABLE = _ENABLE,
} EnumBacklightAction;

#if(_DRR_SUPPORT == _ON)
#if(_SEARCH_DRR_IVF_PRIORITY_BY_USER == _ON)
//--------------------------------------------------
// Enumerations of DRR Get IVF Priority
//--------------------------------------------------
typedef enum
{
    _DRR_GET_IVF_PRIORITY_USER,
    _DRR_GET_IVF_PRIORITY_KERNEL,
} EnumDrrGetIVFPriority;
#endif
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonDisplayModeAdjust(EnumDisplayMode enumDisplayMode);
extern void UserCommonDisplayRegionInputPortAdjust(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort);
extern void UserCommonDisplayHPositionAdjust(BYTE ucUserHPosition, EnumDisplayRegion enumDisplayRegion);
extern void UserCommonDisplayVPositionAdjust(BYTE ucUserVPosition, EnumDisplayRegion enumDisplayRegion);
extern BYTE UserCommonDisplayRealValueToPercentAdjust(WORD usRealValue, WORD usMax, WORD usMin, WORD usCenter);
extern WORD UserCommonDisplayPercentToRealValueAdjust(BYTE ucPercentValue, WORD usMax, WORD usMin, WORD usCenter);

#if((_2P_PIP_DISPLAY_SUPPORT == _ON) || (_EAGLE_SIGHT_SUPPORT == _ON))
extern void UserCommonDisplayGetPipSubBackground(StructTimingFormat *pstTimingFormat);
extern void UserCommonDisplayGetPipSubActiveTiming(StructTimingFormat *pstTimingFormat);
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
extern void UserCommonDisplayGetPbplrRightBackground(StructTimingFormat *pstTimingFormat);
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
extern void UserCommonDisplayGet3PFlagMainRegionBackground(StructTimingFormat *pstTimingFormat);
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
extern void UserCommonDisplayPipSubTimingFormatAdjust(void);
#endif

#if(_FREEZE_SUPPORT == _ON)
extern void UserCommonDisplayFreeze(bit bEn);
#endif

extern void UserCommonDisplayPLLSetDPLLSSC(BYTE ucDclkSpreadSpeed, BYTE ucSpreadRange);

extern void UserCommonDisplayGlobalDDomainDBApply(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);

extern void UserCommonRegionSetWatchDog(EnumDisplayRegion enumDisplayRegion, bit bEnable);
extern EnumDDomainRegion UserCommonRegionGetDDomainRegion(EnumDisplayRegion enumDisplayRegion);
extern EnumSelRegion UserCommonRegionGetInverse(EnumSelRegion enumSelRegion);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit UserCommonRegionGetFrontBackModeSupport(void);
#endif

extern EnumRegionIndex UserCommonRegionGetIndex(EnumDisplayRegion enumDisplayRegion);
extern EnumInputDataPath UserCommonRegionGetInputDataPath(EnumDisplayRegion enumDisplayRegion);

extern void UserCommonIDomainResetDataPath(EnumInputDataPath enumVgipInputPath);

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern void UserCommonMDomainAspectOriginMode(bit bOn);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern WORD UserCommonDDomainGetEagleSightDisplayActive_Main(EnumDisplayFormatItem enumItem);
extern WORD UserCommonDisplayGetEagleSightDisplayBackground_Main(EnumDisplayBackgroundItem enumItem);

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
extern WORD UserCommonDisplayGetEagleSightDisplayBackground_Sub(EnumDisplayBackgroundItem enumItem);
#endif
#endif

#if(_PIXEL_SHIFT_SUPPORT == _ON)
#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
extern void UserCommonDisplayGlobalIDomainDBApply(EnumDisplayRegion enumDisplayRegion, EnumDBApply enumDBApply);
extern WORD UserCommonIDomainGetCaptureHStartPosition(void);
extern void UserCommonIDomainSetCaptureHStartPosition(WORD usIHstart);
extern WORD UserCommonIDomainGetCaptureVDelay(void);
extern void UserCommonIDomainSetCaptureVDelay(WORD usIVSDelay);
extern void UserCommonIDomainSetCaptureInputRegion(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_DDOMAIN)
extern void UserCommonDDomainSetDisplayTimingGenBackground(EnumDisplayBackgroundItem enumItem, WORD usData, EnumDBApply enumDBApply);
extern WORD UserCommonDDomainGetDisplayTimingGenBackground(EnumDisplayBackgroundItem enumItem);
extern void UserCommonDDomainSetDisplayTimingGenActiveRegion(EnumDisplayFormatItem enumItem, WORD usData, EnumDBApply enumDBApply);
extern WORD UserCommonDDomainGetDisplayTimingGenActiveRegion(EnumDisplayFormatItem enumItem);
extern void UserCommonDDomainSetCaptureWindowEnable(bit bCapWinEnable, EnumDBApply enumDBApply);
extern void UserCommonDDomainSetCaptureWindowBackground(EnumDisplayBackgroundItem enumItem, WORD usData, EnumDBApply enumDBApply);
extern WORD UserCommonDDomainGetCaptureWindowBackground(EnumDisplayBackgroundItem enumItem);
extern void UserCommonDDomainSetCaptureWindowActiveRegion(EnumDisplayFormatItem enumItem, WORD usData, EnumDBApply enumDBApply);
extern WORD UserCommonDDomainGetCaptureWindowActiveRegion(EnumDisplayFormatItem enumItem);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void UserCommonDDomainSetDspcDenDelay(BYTE ucData, EnumDBApply enumDBApply);
extern BYTE UserCommonDDomainGetDspcDenDelay(void);
extern void UserCommonDDomainSetExtensionExtract(bit bEnable, EnumDBApply enumDBApply);
extern void UserCommonDDomainSetCaptureWindowBackground_Back(EnumDisplayBackgroundItem enumItem, WORD usData, EnumDBApply enumDBApply);
extern WORD UserCommonDDomainGetCaptureWindowBackground_Back(EnumDisplayBackgroundItem enumItem);
extern void UserCommonDDomainSetCaptureWindowActiveRegion_Back(EnumDisplayFormatItem enumItem, WORD usData, EnumDBApply enumDBApply);
extern WORD UserCommonDDomainGetCaptureWindowActiveRegion_Back(EnumDisplayFormatItem enumItem);
extern WORD UserCommonDDomainGetExtension(void);
#endif
#endif
#endif

extern void UserCommonDDomainBackgroundEnableByRegion(EnumDisplayRegion enumDisplayRegion, bit bEnable);
extern void UserCommonDDomainBackgroundEnable(EnumDDomainRegion enumDDomainRegion, bit bEnable);
extern void UserCommonDDomainBackgroundSetColorByRegion(EnumDisplayRegion enumDisplayRegion, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply);
extern bit UserCommonDDomainGetBackgroundStatus(EnumDDomainRegion enumDDomainRegion);
extern void UserCommonDDomainBackgroundSetColor(EnumDDomainRegion enumDDomainRegion, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply);
extern void UserCommonDDomainPatternGenEnable(bit bEnable);
extern void UserCommonDDomainPatternGenModeAdjust(EnumDPatternGenMode enumDPatternGenMode);
extern void UserCommonDDomainPatternGenAdjustColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
extern void UserCommonDDomainPatternGenAdjustColor10bit(WORD usRed, WORD usGreen, WORD usBlue);

extern void UserCommonDDomainPatternGenAdjustBoxColor10bit_Inside(WORD usRed, WORD usGreen, WORD usBlue);
extern void UserCommonDDomainPatternGenAdjustBoxColor10bit_Outside(WORD usRed, WORD usGreen, WORD usBlue);
extern void UserCommonDDomainPatternGenSetBoxWidthHeight(WORD usWidth1, WORD usWidth2, WORD usHeight1, WORD usHeight2);
extern void UserCommonDDomainPatternGenSetBoxRegionInOut(bit bEnable, StructDPatternGenBoxSetting *pstDPatternGenBoxSetting);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void UserCommonDDomainPatternGenSetBoxWidthHeight_Back(WORD usWidth1, WORD usWidth2, WORD usHeight1, WORD usHeight2);
extern void UserCommonDDomainPatternGenSetBoxRegionInOut_Back(bit bEnable, StructDPatternGenBoxSetting *pstDPatternGenBoxSetting);
#endif

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
extern void UserCommonDisplayMbrStrobeBacklightCtrl(bit bLightCtrl);
extern EnumMbrBacklightMode UserCommonDisplayMbrGetCurrentBacklightMode(void);
#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern bit UserCommonDisplayMbrDrrGetHWSupport(void);
#endif
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern bit UserCommonDisplayGetAdvMbrStatus(void);
#endif
#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
extern void UserCommonDisplayMbrAdvAdjust(BYTE ucBacklightDuty, BYTE ucBacklightPos, bit bLightCtrl);
#endif

#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
extern EnumMbrBFIMode UserCommonDisplayMbrGetBlackFrameInsertAvailable(void);
extern EnumMbrBFIMode UserCommonDisplayMbrGetBlackFrameInsertEnable(void);
extern void UserCommonDisplayMbrBlackFrameInsertAdjust(void);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
extern EnumEagleSightMainSubSynchronous UserCommonDisplayGetEagleSightMainSubSync(void);
extern void UserCommonDisplayEagleSightAdjust(EnumEagleSightSetting enumEagleSightSetting);
extern bit UserCommonDisplayGetShowEagleSightWindow(void);
#endif

#if((_2P_PIP_DISPLAY_SUPPORT == _ON) || (_EAGLE_SIGHT_SUPPORT == _ON))
extern bit UserCommonDisplayGetSubDenEnable(void);
extern void UserCommonDisplaySetSubDenEnable(bit bEnable, EnumDBApply enumDBApply);
#endif

#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
extern bit UserCommonDisplayGet2PFrameSyncEnable(void);
#endif

extern EnumFrameSyncSupport UserCommonDisplayGetFrameSyncSupport(void);
extern void UserCommonDisplayGlobalDisableAllWatchDog(void);
extern void UserCommonDisplayGetScalingStatus(StructScalingStatus *pstData);
extern EnumMemoryWorkMode UserCommonDisplayGetMemoryConfig(void);

extern EnumSelRegion UserCommonRegionCheckSystemSelectRegion(EnumSelRegion enumSelRegion);
extern EnumFrameSyncModeType UserCommonDisplayGetFrameSyncMode(void);
extern WORD UserCommonDisplayGetMeasureDVtotal(void);

#if((_DRR_SUPPORT == _ON) || (_HDMI21_FVA_SUPPORT == _ON))
extern WORD UserCommonDisplayGetInterfaceSpecificIVFreq(EnumInputPort enumInputPort);
#endif

#if(_FRAME_RATE_SLOW_DOWN_SUPPORT == _ON)
extern void UserCommonDisplaySetDropIVFAction(EnumDropIVFAction enumDropIVFAction);
extern bit UserCommonDisplayGetDropIVFAction(EnumInputDataPath enumVgipInputPath);
#endif

#if(_DYNAMIC_DATA_BOUNDARY_AUTO_MEASURE == _ON)
extern bit UserCommonDisplayGetImageBoundary(BYTE ucNoiseMargin, StructImageRegion *pstImageRegion, EnumDisplayRegion enumDisplayRegion, bit bWait);
#endif
