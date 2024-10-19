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
// ID Code      : UserCommonColorHDR.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_HDR__

#include "UserCommonInclude.h"
#include "ColorHDR/UserCommonColorHDR.h"

#if(_ULTRA_HDR_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HDR10_SUPPORT == _ON)
StructHDR10Setting g_pstColorHDR10Setting[_MULTI_DISPLAY_MAX];
StructHDR10UserData g_pstColorHDR10UserData[_MULTI_DISPLAY_MAX];
EnumHDR10ModeDef g_penumColorHDR10ModeStatus[_MULTI_DISPLAY_MAX];

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
WORD g_pusColorHDR10LinearOut[129];
#endif

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
BYTE g_pucColorHDR10StepLessTMIGLUT[197];
#endif

#if((_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON) || (_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON))
WORD g_pusColorHDRPanelMaxLv[_MULTI_DISPLAY_MAX];
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
StructFreeSyncIIInfo g_pstColorFreeSyncIISetting[_MULTI_DISPLAY_MAX];
EnumFreeSyncSupport g_penumColorFreesyncIIModeStatus[_MULTI_DISPLAY_MAX];
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
#if(_DEBUG_MESSAGE_HDR == _ON)
volatile StructAdvancedHDR10MetaData g_stColorAdvancedHDR10Setting;
#endif
EnumAdvancedHDR10Support g_enumColorAdvancedHDR10Support;
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
StructHDR10SBTMInfo g_pstColorHDR10SBTMInfo[_SBTM_MAX_REGION_COUNT];
#endif
EnumHDR10ChangeStatus g_penumColorHDR10ChangeStatus[_MULTI_DISPLAY_MAX];

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDR & FreeSync2 Infoframe Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRInitialSetting(EnumDisplayRegion enumDisplayRegion)
{
#if(_HDR10_SUPPORT == _ON)
    BYTE ucHDRMetadataIndex = ScalerSyncDxHDRMetadataIndexMapping(SysRegionGetInputPort(enumDisplayRegion));
#endif

    StructHDRStatusInfo stHDRStatusInfo = {0};

#if(_HDR10_SUPPORT == _ON)
    ScalerSyncHDR10GetCurrentStatus(SysRegionGetInputPort(enumDisplayRegion), _HDR_INFO_CHG_POLLING_CHECK_DISABLE);
    SET_HDR10_MODE_STATUS(enumDisplayRegion, UserInterfaceColorHDRGetHDR10ModeStatus(SysRegionGetInputPort(enumDisplayRegion)));
    CLR_HDR10_USER_DATA(enumDisplayRegion);
    UserInterfaceColorHDRGetHDR10UserData(enumDisplayRegion, &(GET_HDR10_USER_DATA(enumDisplayRegion)));

#if((_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON) || (_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON))
    SET_HDR10_PANEL_MAX_LV(enumDisplayRegion, UserCommonColorHDRGetPanelMaxLv(GET_HDR10_USER_DEF_PANEL_LV_TYPE(enumDisplayRegion)));
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    ScalerDrrFreeSyncIIGetCurrentStatus(SysRegionGetInputPort(enumDisplayRegion), enumDisplayRegion, _HDR_INFO_CHG_POLLING_CHECK_DISABLE);
    SET_FREESYNC_II_MODE_STATUS(enumDisplayRegion, UserInterfaceFreeSyncGetEnable(SysSourceGetInputPort()));
#endif

    UserCommonColorHDRGetTargetStatus(enumDisplayRegion, &stHDRStatusInfo);

    SET_HDR_TARGET_STATUS(enumDisplayRegion, stHDRStatusInfo.enumHDRTargetStatus);
    SET_HDR_CHANGE_STATUS(enumDisplayRegion, stHDRStatusInfo.enumHDR10ChangeStatus);

    DebugMessageHDR("Initial HDR Target Status", stHDRStatusInfo.enumHDRTargetStatus);

#if(_FREESYNC_II_SUPPORT == _ON)
    DebugMessageHDR("FreeSync II Check Display Region", enumDisplayRegion);

    DebugMessageHDR("Native Color Space Enable", g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(enumDisplayRegion)].b1NativeColorSpaceEnable);
    DebugMessageHDR("Backlight Control Enable", g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(enumDisplayRegion)].b1BacklightControlEnable);
    DebugMessageHDR("Local Dimming Disable", g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(enumDisplayRegion)].b1LocalDimmingDisable);
    DebugMessageHDR("EOTF Type", g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(enumDisplayRegion)].b5EOTFType);
    DebugMessageHDR("Backlight Control Ratio", g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(enumDisplayRegion)].ucBacklightControlRatio);

#endif

#if(_HDR10_SUPPORT == _ON)
    ucHDRMetadataIndex = ucHDRMetadataIndex;

    DebugMessageHDR("HDR10 Check Display Region", enumDisplayRegion);

    DebugMessageHDR("HDR10 Metadata EOTF", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].ucEOTF));

    DebugMessageHDR("HDR10 Metadata X0", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesX0));
    DebugMessageHDR("HDR10 Metadata Y0", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesY0));

    DebugMessageHDR("HDR10 Metadata X1", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesX1));
    DebugMessageHDR("HDR10 Metadata Y1", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesY1));

    DebugMessageHDR("HDR10 Metadata X2", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesX2));
    DebugMessageHDR("HDR10 Metadata Y2", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesY2));

    DebugMessageHDR("HDR10 Metadata Wx", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usWhitePointX));
    DebugMessageHDR("HDR10 Metadata Wy", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usWhitePointY));

    DebugMessageHDR("HDR10 Metadata Max Mastering Lv", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usMaxDisplayMasteringLv));
    DebugMessageHDR("HDR10 Metadata Min Mastering Lv", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usMinDisplayMasteringLv));

    DebugMessageHDR("HDR10 Metadata Max CLL", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usMaxCLL));
    DebugMessageHDR("HDR10 Metadata Max FALL", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usMaxFALL));

#if(_HDMI_SBTM_SUPPORT == _ON)
    ScalerSyncHDR10SBTMGetCurrentStatus(SysRegionGetInputPort(enumDisplayRegion), _HDR_INFO_CHG_POLLING_CHECK_DISABLE);
    DebugMessageHDR("usFrmPbLimitInt", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].usFrmPbLimitInt);
    DebugMessageHDR("ucSbtmVer", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].ucSBTMVer);
    DebugMessageHDR("ucSbtmType", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].enumHDR10SBTMType);
    DebugMessageHDR("ucSbtmMode", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].enumHDR10SBTMMode);
    DebugMessageHDR("ucSbtmGrmdLum", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].enumHDR10SBTMGRDMLumMaxType);
    DebugMessageHDR("ucSbtmGrmdMin", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].enumHDR10SBTMGRDMMinType);

#endif
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT) && (enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB))
    {
        return;
    }
#endif

    switch(GET_HDR_TARGET_STATUS(enumDisplayRegion))
    {
#if(_HDR10_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_FORCE_2084:
        case _HDR_TARGET_STATUS_SMPTE_ST_2084:

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
            if(UserCommonColorHDRGetBackLightAdaptiveTMBackLightStatus() == _HDR10_BACKLIGHT_ADAPTIVE_TM_BACKLIGHT_MAX)
#endif
            {
                UserInterfaceColorCalibrationAdjustBacklight(_MAX_BACKLIGHT_RATIO);
            }
            break;
#endif

#if(_HLG_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_AUTO_HLG:
        case _HDR_TARGET_STATUS_FORCE_HLG:

            UserInterfaceColorCalibrationAdjustBacklight(_MAX_BACKLIGHT_RATIO);
            break;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR:
            UserCommonColorHDRAdjustFreeSyncIIMode(enumDisplayRegion);
            break;
#endif

        case _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR:
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : HDR Handler
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRHandler(EnumDisplayRegion enumDisplayRegion)
{
    // check if bypass HDR process
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    if(UserCommonColorDMGetBypassHDRProcStatus(enumDisplayRegion) == _TRUE)
    {
        return;
    }
#endif
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() != _DISPLAY_MODE_4P)
#endif
    {
        if(GET_ON_LINE_CALIBRATION_STATUS() != _CALIBRATION_ON)
        {
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);
#endif
#endif
            StructHDRStatusInfo stHDRStatusInfo = {0};

            UserCommonColorHDRGetTargetStatus(enumDisplayRegion, &stHDRStatusInfo);

            if((stHDRStatusInfo.enumHDRTargetStatus != GET_HDR_TARGET_STATUS(enumDisplayRegion)) ||
               (stHDRStatusInfo.enumHDR10ChangeStatus != _HDR10_INFO_NO_CHANGE) ||
               (stHDRStatusInfo.enumFreeSyncIIChangeStatus != _FREESYNC_II_INFO_NO_CHANGE) ||
               (stHDRStatusInfo.enumHDR10SBTMChangeStatus != _HDR10_SBTM_INFO_NO_CHANGE))
            {
                SET_HDR_TARGET_STATUS(enumDisplayRegion, stHDRStatusInfo.enumHDRTargetStatus);
                SET_HDR_CHANGE_STATUS(enumDisplayRegion, stHDRStatusInfo.enumHDR10ChangeStatus);
                UserCommonColorHDRAdjustHDRProc(enumDisplayRegion);
            }
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
            if(enumRegionIndex < _DM_MAX_REGION_COUNT)
            {
                if((GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_OUT_MUTE) && (GET_DM_HW_DISABLE_FLAG_INDEX(enumRegionIndex) == _TRUE))
                {
                    DebugMessageDM("HDR Handler Finish, DM Out!!", enumRegionIndex);
                    DebugMessageDM("HDR Target Status", GET_HDR_TARGET_STATUS(enumDisplayRegion));

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB) && (GET_DM_MAIN_SUB_SYNC() == _TRUE))
                    {
                        SET_DM_MUTE_STATUS_INDEX(_REGION_INDEX_1, _DM_NO_MUTE);
                        CLR_DM_MAIN_SUB_SYNC();
                    }
                    else
#endif
                    {
                        SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_OUT_UNMUTE_READY);
                        CLR_DM_UNMUTE_MAINLOOP_CNT_INDEX(enumRegionIndex);
                    }

                    CLR_DM_HW_DISABLE_FLAG_INDEX(enumRegionIndex);
                }
            }
#endif
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Integrate HDR Auto Mode FW Flow
// Input Value  : EnumDisplayRegion, EnumHDRFlowStatus
// Output Value : none
//--------------------------------------------------
void UserCommonColorHDRAdjust(EnumDisplayRegion enumDisplayRegion)
{
    StructHDRStatusInfo stHDRStatusInfo = {0};

    EnumDisplayRegion enumStartRegion = enumDisplayRegion;
    EnumDisplayRegion enumStopRegion = enumDisplayRegion;
    EnumDisplayRegion enumIndexRegion = 0;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) || (enumDisplayRegion == _DISPLAY_RGN_1P))
    {
        if((UserInterfaceColorHDRGetEagleSightAdjustFullRegion() == _HDR10_ADJUST_EAGLE_SIGHT_FULL_REGION_ON) &&
           (GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT))
        {
            enumStartRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
            enumStopRegion = _DISPLAY_RGN_EAGLE_SIGHT_SUB;
        }
    }
#endif

    for(enumIndexRegion = enumStartRegion; enumIndexRegion <= enumStopRegion; ++enumIndexRegion)
    {
#if(_HDR10_SUPPORT == _ON)
        SET_HDR10_MODE_STATUS(enumIndexRegion, UserInterfaceColorHDRGetHDR10ModeStatus(SysRegionGetInputPort(enumIndexRegion)));
        UserInterfaceColorHDRGetHDR10UserData(enumIndexRegion, &(GET_HDR10_USER_DATA(enumIndexRegion)));

#if((_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON) || (_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON))
        SET_HDR10_PANEL_MAX_LV(enumIndexRegion, UserCommonColorHDRGetPanelMaxLv(GET_HDR10_USER_DEF_PANEL_LV_TYPE(enumIndexRegion)));
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
        SET_FREESYNC_II_MODE_STATUS(enumIndexRegion, UserInterfaceFreeSyncGetEnable(SysSourceGetInputPort()));
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
        if(UserCommonColorHDRCheckAdvancedHDR10SupportDisplayMode() != _ADVANCED_HDR10_DISP_MODE_SUPPORT_OFF)
        {
            SET_ADVANCED_HDR10_SUPPORT(UserInterfaceColorHDRGetAdvancedHDR10Enable(enumIndexRegion));
        }
#endif
        UserCommonColorHDRGetTargetStatus(enumIndexRegion, &stHDRStatusInfo);
        SET_HDR_TARGET_STATUS(enumIndexRegion, stHDRStatusInfo.enumHDRTargetStatus);
        SET_HDR_CHANGE_STATUS(enumIndexRegion, stHDRStatusInfo.enumHDR10ChangeStatus);
        UserCommonColorHDRAdjustHDRProc(enumIndexRegion);
    }
}

//--------------------------------------------------
// Description  : Check HDR target status to set DM, DM_Game, HDR 2084, SDR or do nothing
// Input Value  : EnumDisplayRegion, StructHDRStatusInfo
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRGetTargetStatus(EnumDisplayRegion enumDisplayRegion, StructHDRStatusInfo *pstHDRStatusInfo)
{
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    if(enumRegionIndex < _DM_MAX_REGION_COUNT)
    {
        if(GET_DM_BEC_STATUS_INDEX(enumRegionIndex) == _DM_BEC_DONE)
        {
            if(GET_DM_INPUT_STATUS_INDEX(enumRegionIndex) == _DM_ON_NORMAL)
            {
                pstHDRStatusInfo->enumHDRTargetStatus = _HDR_TARGET_STATUS_DM;
                return;
            }
#if(_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE)
            else if(GET_DM_INPUT_STATUS_INDEX(enumRegionIndex) == _DM_ON_GAME)
            {
                pstHDRStatusInfo->enumHDRTargetStatus = _HDR_TARGET_STATUS_DM_GAME;
                return;
            }
#endif
        }
        else if((GET_DM_BEC_STATUS_INDEX(enumRegionIndex) == _DM_BEC_INIT) && (GET_DM_INPUT_STATUS_INDEX(enumRegionIndex) != _DM_OFF))
        {
            pstHDRStatusInfo->enumHDRTargetStatus = GET_HDR_TARGET_STATUS(enumDisplayRegion);
            return;
        }

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB) && (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE))
        {
            if(UserCommonColorDMGetDMStatus(_DISPLAY_RGN_EAGLE_SIGHT_MAIN) == _TRUE)
            {
                pstHDRStatusInfo->enumHDRTargetStatus = GET_HDR_TARGET_STATUS(_DISPLAY_RGN_EAGLE_SIGHT_MAIN);
                return;
            }
        }
#endif
    }
#endif
#endif

#if(_DEBUG_MESSAGE_HDR == _ON)
#if(_ADVANCED_HDR10_SUPPORT == _ON)
    EnumAdvancedHDR10ChangeStatus enumAdvancedHDR10ChangeStatus = UserCommonColorHDRGetAdvancedHDR10ChangeStatus();
#endif
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    BYTE ucFreeSyncIIChangeStatus = UserCommonColorHDRFreeSyncIIChangeStatus(enumDisplayRegion);
#else
    BYTE ucFreeSyncIIChangeStatus = _FREESYNC_II_INFO_NO_CHANGE;
#endif

#if(_HDR10_SUPPORT == _ON)
    EnumHDR10ChangeStatus enumHDR10ChangeStatus = UserCommonColorHDRGetHDR10ChangeStatus(enumDisplayRegion);
#else
    EnumHDR10ChangeStatus enumHDR10ChangeStatus = _HDR10_INFO_NO_CHANGE;
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
    EnumHDR10SBTMChangeStatus enumHDR10SBTMChangeStatus = UserCommonColorHDRGetSBTMChangeStatus(enumDisplayRegion);
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    if((GET_FREESYNC_II_MODE_STATUS(enumDisplayRegion) == _FREESYNC_SUPPORT_ON) &&
       ((ucFreeSyncIIChangeStatus != _FREESYNC_II_INFO_NO_CHANGE) ||
        (enumHDR10ChangeStatus != _HDR10_INFO_NO_CHANGE)))
    {
        DebugMessageHDR("FreeSync II Check Display Region", enumDisplayRegion);

        DebugMessageHDR("Native Color Space Enable", g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(enumDisplayRegion)].b1NativeColorSpaceEnable);
        DebugMessageHDR("Backlight Control Enable", g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(enumDisplayRegion)].b1BacklightControlEnable);
        DebugMessageHDR("Local Dimming Disable", g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(enumDisplayRegion)].b1LocalDimmingDisable);
        DebugMessageHDR("EOTF Type", g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(enumDisplayRegion)].b5EOTFType);
        DebugMessageHDR("Backlight Control Ratio", g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(enumDisplayRegion)].ucBacklightControlRatio);
    }

    if(UserCommonColorHDRGetFreesynIIStatus(enumDisplayRegion) == _ON)
    {
        pstHDRStatusInfo->enumHDRTargetStatus = _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR;
        pstHDRStatusInfo->enumFreeSyncIIChangeStatus = ucFreeSyncIIChangeStatus;
    }
    else if(ucFreeSyncIIChangeStatus != _FREESYNC_II_INFO_NO_CHANGE)
    {
        pstHDRStatusInfo->enumFreeSyncIIChangeStatus = ucFreeSyncIIChangeStatus;
    }
#endif

#if(_DEBUG_MESSAGE_HDR == _ON)
#if(_ADVANCED_HDR10_SUPPORT == _ON)
    if((GET_ADVANCED_HDR10_SUPPORT() == _ADVANCED_HDR10_SUPPORT_ON) &&
       ((enumAdvancedHDR10ChangeStatus != _ADVANCED_HDR10_INFO_NO_CHANGE)))
    {
        DebugMessageHDR("OUICODE[0]", g_stSyncAdvancedHDR10Metadata.pucOUICode[0]);
        DebugMessageHDR("OUICODE[1]", g_stSyncAdvancedHDR10Metadata.pucOUICode[1]);
        DebugMessageHDR("OUICODE[2]", g_stSyncAdvancedHDR10Metadata.pucOUICode[2]);

        DebugMessageHDR("Target Display Lv", g_stColorAdvancedHDR10Setting.ucTargetDisplayLv);
        DebugMessageHDR("Distribution 50%", g_stColorAdvancedHDR10Setting.ucDistribution50);
        DebugMessageHDR("Distribution 99% (SceneMaxRGB)", g_stColorAdvancedHDR10Setting.ucDistribution99);
        DebugMessageHDR("BezierAnchor0", g_stColorAdvancedHDR10Setting.pucBezierAnchor[0]);
        DebugMessageHDR("BezierAnchor1", g_stColorAdvancedHDR10Setting.pucBezierAnchor[1]);
        DebugMessageHDR("BezierAnchor2", g_stColorAdvancedHDR10Setting.pucBezierAnchor[2]);
        DebugMessageHDR("BezierAnchor3", g_stColorAdvancedHDR10Setting.pucBezierAnchor[3]);
        DebugMessageHDR("BezierAnchor4", g_stColorAdvancedHDR10Setting.pucBezierAnchor[4]);
        DebugMessageHDR("BezierAnchor5", g_stColorAdvancedHDR10Setting.pucBezierAnchor[5]);
        DebugMessageHDR("BezierAnchor6", g_stColorAdvancedHDR10Setting.pucBezierAnchor[6]);
        DebugMessageHDR("BezierAnchor7", g_stColorAdvancedHDR10Setting.pucBezierAnchor[7]);
        DebugMessageHDR("BezierAnchor8", g_stColorAdvancedHDR10Setting.pucBezierAnchor[8]);
        DebugMessageHDR("KneePoint X", g_stColorAdvancedHDR10Setting.pusKneePoint[0]);
        DebugMessageHDR("KneePoint Y", g_stColorAdvancedHDR10Setting.pusKneePoint[1]);
        DebugMessageHDR("Graphic Overlay Flag", g_stColorAdvancedHDR10Setting.ucGraphicOverlayFlag);
        DebugMessageHDR("No Delay Flag", g_stColorAdvancedHDR10Setting.ucNoDelayFlag);
    }
#endif
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
    if((UserCommonColorHDRGetSBTMStatus(enumDisplayRegion) == _HDR10_SBTM_ON) &&
       (enumHDR10SBTMChangeStatus != _HDR10_SBTM_INFO_NO_CHANGE))
    {
        BYTE ucHDRMetadataIndex = ScalerSyncDxHDRMetadataIndexMapping(SysRegionGetInputPort(enumDisplayRegion));
        ucHDRMetadataIndex = ucHDRMetadataIndex;

        DebugMessageHDR("usFrmPbLimitInt", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].usFrmPbLimitInt);
        DebugMessageHDR("ucSbtmVer", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].ucSBTMVer);
        DebugMessageHDR("ucSbtmType", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].enumHDR10SBTMType);
        DebugMessageHDR("ucSbtmMode", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].enumHDR10SBTMMode);
        DebugMessageHDR("ucSbtmGrmdLum", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].enumHDR10SBTMGRDMLumMaxType);
        DebugMessageHDR("ucSbtmGrmdMin", g_pstSyncHDR10SBTMMetadata[ucHDRMetadataIndex].enumHDR10SBTMGRDMMinType);
    }

    if(UserCommonColorHDRGetSBTMStatus(enumDisplayRegion) == _HDR10_SBTM_ON)
    {
        pstHDRStatusInfo->enumHDRTargetStatus = _HDR_TARGET_STATUS_SBTM;
        pstHDRStatusInfo->enumHDR10SBTMChangeStatus = enumHDR10SBTMChangeStatus;
    }
    else
    {
        pstHDRStatusInfo->enumHDR10SBTMChangeStatus = _HDR10_SBTM_INFO_NO_CHANGE;
    }
#endif

#if(_HDR10_SUPPORT == _ON)
#if(_HLG_SUPPORT == _ON)
    if(((GET_HDR10_MODE_STATUS(enumDisplayRegion) == _HDR10_MODE_AUTO) || (GET_HDR10_MODE_STATUS(enumDisplayRegion) == _HDR10_HLG_MODE_AUTO)) &&
       ((enumHDR10ChangeStatus != _HDR10_INFO_NO_CHANGE) || (ucFreeSyncIIChangeStatus != _FREESYNC_II_INFO_NO_CHANGE)))
#else
    if((GET_HDR10_MODE_STATUS(enumDisplayRegion) == _HDR10_MODE_AUTO) &&
       ((enumHDR10ChangeStatus != _HDR10_INFO_NO_CHANGE) ||
        (ucFreeSyncIIChangeStatus != _FREESYNC_II_INFO_NO_CHANGE)))
#endif
    {
        BYTE ucHDRMetadataIndex = ScalerSyncDxHDRMetadataIndexMapping(SysRegionGetInputPort(enumDisplayRegion));

        ucHDRMetadataIndex = ucHDRMetadataIndex;

        DebugMessageHDR("HDR10 Check Display Region", enumDisplayRegion);

        DebugMessageHDR("HDR10 Metadata EOTF", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].ucEOTF));

        DebugMessageHDR("HDR10 Metadata X0", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesX0));
        DebugMessageHDR("HDR10 Metadata Y0", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesY0));

        DebugMessageHDR("HDR10 Metadata X1", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesX1));
        DebugMessageHDR("HDR10 Metadata Y1", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesY1));

        DebugMessageHDR("HDR10 Metadata X2", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesX2));
        DebugMessageHDR("HDR10 Metadata Y2", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usDisplayPrimariesY2));

        DebugMessageHDR("HDR10 Metadata Wx", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usWhitePointX));
        DebugMessageHDR("HDR10 Metadata Wy", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usWhitePointY));

        DebugMessageHDR("HDR10 Metadata Max Mastering Lv", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usMaxDisplayMasteringLv));
        DebugMessageHDR("HDR10 Metadata Min Mastering Lv", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usMinDisplayMasteringLv));

        DebugMessageHDR("HDR10 Metadata Max CLL", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usMaxCLL));
        DebugMessageHDR("HDR10 Metadata Max FALL", (g_pstSyncHDR10SaticMetadata[ucHDRMetadataIndex].usMaxFALL));
    }

    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON)
    {
        if(GET_HDR10_MODE_STATUS(enumDisplayRegion) == _HDR10_MODE_FORCE_2084)
        {
            pstHDRStatusInfo->enumHDRTargetStatus = _HDR_TARGET_STATUS_FORCE_2084;
        }
        else if(pstHDRStatusInfo->enumHDRTargetStatus != _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR)
        {
#if(_ADVANCED_HDR10_SUPPORT == _ON)
            if(UserCommonColorHDRGetAdvancedHDR10Status(enumDisplayRegion) == _ADVANCED_HDR10_ON)
            {
                pstHDRStatusInfo->enumHDRTargetStatus = _HDR_TARGET_STATUS_ADVANCED_HDR10;
            }
            else
#endif
            {
#if(_HDMI_SBTM_SUPPORT == _ON)
                if(pstHDRStatusInfo->enumHDRTargetStatus != _HDR_TARGET_STATUS_SBTM)
#endif
                {
                    pstHDRStatusInfo->enumHDRTargetStatus = _HDR_TARGET_STATUS_SMPTE_ST_2084;
                    pstHDRStatusInfo->enumHDR10ChangeStatus = enumHDR10ChangeStatus;
                }
            }
        }
    }
#if(_HLG_SUPPORT == _ON)
    else if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HLG_ON)
    {
        if(GET_HDR10_MODE_STATUS(enumDisplayRegion) == _HDR10_HLG_MODE_FORCE_HLG)
        {
            pstHDRStatusInfo->enumHDRTargetStatus = _HDR_TARGET_STATUS_FORCE_HLG;
        }
        else
        {
            pstHDRStatusInfo->enumHDRTargetStatus = _HDR_TARGET_STATUS_AUTO_HLG;
        }
    }
#endif
#endif
}

//--------------------------------------------------
// Description  : Return HDR Display Region
// Input Value  : EnumSelRegion
// Output Value : EnumDisplayRegion
//--------------------------------------------------
EnumDisplayRegion UserCommonColorHDRGetDisplayRegion(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _DEMO_INSIDE:
        case _FULL_REGION:
            return (EnumDisplayRegion)GET_DISPLAY_MODE();

        case _DEMO_OUTSIDE:
            return ((UserInterfaceColorHDRGetHDRDemoModeOutsideStatus() == _HDR_DEMO_ON) ? (EnumDisplayRegion)GET_DISPLAY_MODE() : _DISPLAY_RGN_NONE);

#if((_3P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _3P_FLAG_M_OUTSIDE:
        case _3P_FLAG_L_OUTSIDE:
        case _3P_FLAG_R_OUTSIDE:
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_L_M_OUTSIDE:
        case _3P_SKEW_L_T_OUTSIDE:
        case _3P_SKEW_L_B_OUTSIDE:
        case _3P_SKEW_R_M_OUTSIDE:
        case _3P_SKEW_R_T_OUTSIDE:
        case _3P_SKEW_R_B_OUTSIDE:
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _3P_SKEW_T_M_OUTSIDE:
        case _3P_SKEW_T_L_OUTSIDE:
        case _3P_SKEW_T_R_OUTSIDE:
        case _3P_SKEW_B_M_OUTSIDE:
        case _3P_SKEW_B_L_OUTSIDE:
        case _3P_SKEW_B_R_OUTSIDE:
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
#endif
            return _DISPLAY_RGN_NONE;
#endif

        default:
            return (EnumDisplayRegion)enumSelRegion;
    }
}

//--------------------------------------------------
// Description  : Adjust HDR mode Related color IP
// Input Value  : EnumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRAdjustHDRMode(EnumDisplayRegion enumDisplayRegion)
{
    EnumSelRegion enumSelRegion = (EnumSelRegion)enumDisplayRegion;
    EnumInputPort enumInputPort = SysRegionGetInputPort(enumDisplayRegion);
    bit bQuantizationRangeUpdate = _FALSE;

    enumInputPort = enumInputPort;

    if(UserInterfaceColorHDRGetHDRDemoModeEnable() == _HDR_DEMO_ON)
    {
        enumSelRegion = _DEMO_INSIDE;
    }

    DebugMessageHDR("HDR Mode SelRegion", enumSelRegion);

#if(_PCM_FUNCTION == _ON)
    if((GET_HDR_CHANGE_STATUS(enumDisplayRegion) == _HDR10_INFO_MAX_LV_CHANGE) && (GET_HDR_TARGET_STATUS(enumDisplayRegion) == _HDR_TARGET_STATUS_SMPTE_ST_2084))
    {
        UserCommonColorInGammaAdjust(enumSelRegion);

#if(_LOCAL_DIMMING_FUNCTION == _ON)
        if(UserCommonColorHDRGetHDR10Status(_DISPLAY_RGN_1P) == _HDR10_ON)
        {
            if(UserCommonColorHDRGetHDR10ApplyLvType(_DISPLAY_RGN_1P) >= _HDR10_MAX_MASTERING_LV_TYPE_NOTM)
            {
                ScalerColorLDHistoSetCoverRate(_LOCAL_DIMMING_HISTO_COVERRATE);
            }
            else
            {
                ScalerColorLDHistoSetCoverRate(_LOCAL_DIMMING_TM_HISTO_COVERRATE);
            }
        }
        else
        {
            ScalerColorLDHistoSetCoverRate(_LOCAL_DIMMING_HISTO_COVERRATE);
        }

        UserCommonColorLocalDimmingAdjust();
#endif
    }
    else
#endif
    {
#if(((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON)) || ((_YCC_QUANTIZATION_RANGE_FUNCTION == _ON) && (_YCC_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON)))
        EnumDBApply enumDBApply = _DB_APPLY_NO_POLLING;
#endif

#if((_RGB_3D_GAMMA_FUNCTION == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON) || (_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT))
        UserCommonColor3DGammaAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if((_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON) && (_GLOBAL_HUE_SATURATION_HDR_SUPPORT == _OFF))
        if(GET_HDR_TARGET_STATUS(enumDisplayRegion) != _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR)
        {
            UserCommonColorDColorConvertAdjust(enumSelRegion, _DB_APPLY_NONE);
        }
#endif

#if(_PCM_FUNCTION == _ON)
        UserCommonColorPCMAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON)) || ((_YCC_QUANTIZATION_RANGE_FUNCTION == _ON) && (_YCC_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON)))

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
        enumDBApply = _DB_APPLY_NONE;
#endif
        if(ScalerColorGetColorSpaceRGB(UserCommonColorGetColorFormat(enumDisplayRegion)) == _TRUE)
        {
#if((_RGB_QUANTIZATION_RANGE_FUNCTION == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
            UserCommonColorRGBQuantizationRangeAdjust(enumDisplayRegion);
            UserCommonColorSetColorFormatConvert(enumDisplayRegion, enumInputPort, ScalerColorGetColorSpace(enumInputPort), enumDBApply);
            bQuantizationRangeUpdate = _TRUE;
#endif
        }
        else
        {
#if((_YCC_QUANTIZATION_RANGE_FUNCTION == _ON) && (_YCC_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
            UserCommonColorYCCQuantizationRangeAdjust(enumDisplayRegion);
            UserCommonColorSetColorFormatConvert(enumDisplayRegion, enumInputPort, ScalerColorGetColorSpace(enumInputPort), enumDBApply);
            bQuantizationRangeUpdate = _TRUE;
#endif
        }
#endif

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
        UserCommonColorDMRestoreSetting(enumDisplayRegion, enumSelRegion, enumInputPort, bQuantizationRangeUpdate);
#endif
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
#if(_GLOBAL_HUE_SATURATION_HDR_SUPPORT == _OFF)
        if(GET_HDR_TARGET_STATUS(enumDisplayRegion) == _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR)
#endif
        {
            // in order to get correct color convert table
            UserCommonColorDColorConvertAdjust(enumSelRegion, _DB_APPLY_NONE);
            if(bQuantizationRangeUpdate == _TRUE)
            {
                UserCommonColorColorConvertDBApply(enumDisplayRegion, _DB_APPLY_NO_POLLING);
            }
        }
#endif

        if(bQuantizationRangeUpdate == _FALSE)
        {
            UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, _DB_APPLY_POLLING);
        }

#if(_FREESYNC_II_SUPPORT == _ON)
        if(GET_HDR_TARGET_STATUS(enumDisplayRegion) == _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR)
        {
            UserCommonColorHDRAdjustFreeSyncIIMode(enumDisplayRegion);
        }
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
        if(UserCommonColorHDRGetHDR10Status(_DISPLAY_RGN_1P) == _HDR10_ON)
        {
            if(UserCommonColorHDRGetHDR10ApplyLvType(_DISPLAY_RGN_1P) >= _HDR10_MAX_MASTERING_LV_TYPE_NOTM)
            {
                ScalerColorLDHistoSetCoverRate(_LOCAL_DIMMING_HISTO_COVERRATE);
            }
            else
            {
                ScalerColorLDHistoSetCoverRate(_LOCAL_DIMMING_TM_HISTO_COVERRATE);
            }
        }
        else
        {
            ScalerColorLDHistoSetCoverRate(_LOCAL_DIMMING_HISTO_COVERRATE);
        }

        UserCommonColorLocalDimmingAdjust();
#endif

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN)
            {
                UserCommonColorGlobalDimmingAdjust();
            }
            else
            {
                UserCommonColorGlobalDimmingSetForceMainEffect();
            }
        }
        else
#endif
        {
            UserCommonColorGlobalDimmingAdjust();
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Print HDR mode Related Debug Message & update colorimetry flag for seamless change flow
// Input Value  : EnumHDRTargetStatus, EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRAdjustHDRProc(EnumDisplayRegion enumDisplayRegion)
{
    EnumHDRTargetStatus enumHDRTargetStatus = GET_HDR_TARGET_STATUS(enumDisplayRegion);

#if(_ADVANCED_HDR10_SUPPORT == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_NONE); // DB Will be applied in the process UserCommonColorHDRAdjustHDRMode
#endif
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    ScalerColorAdvancedHDR10PCMHLWDBProc(_ADVANCED_HDR10_PCM_HLW_DB_RESET);
    CLR_ADVANCED_HDR10_COLOR_INITIAL_SETTING();

    if(UserCommonColorHDRCheckAdvancedHDR10SupportDisplayMode() != _ADVANCED_HDR10_DISP_MODE_SUPPORT_OFF)
    {
        UserCommonColorAdvancedHDR10VSIFSupportSwitch();
    }
#endif

    UserCommonColorHDRAdjustHDRMode(enumDisplayRegion);

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    if(enumHDRTargetStatus == _HDR_TARGET_STATUS_ADVANCED_HDR10)
    {
        if(GET_ADVANCED_HDR10_FRC_STATUS() == _ADVANCED_HDR10_IN_SLOW)
        {
            ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)enumDisplayRegion), _DB_APPLY_POLLING);
            ScalerColorAdvancedHDR10PCMHLWDBProc(_ADVANCED_HDR10_PCM_HLW_DB_INITIAL);
        }
        SET_ADVANCED_HDR10_COLOR_INITIAL_SETTING();
    }
#endif

    DebugMessageHDR("HDR Target Status", enumHDRTargetStatus);

    switch(enumHDRTargetStatus)
    {
#if(_ADVANCED_HDR10_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_ADVANCED_HDR10:

            UserInterfaceColorHDRAdjustHDR10Proc(enumDisplayRegion);
            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_FORCE_2084:
        case _HDR_TARGET_STATUS_SMPTE_ST_2084:
            UserInterfaceColorHDRAdjustHDR10Proc(enumDisplayRegion);
            DebugMessageHDR("HDR10 Display Region", enumDisplayRegion);

            break;
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_HLG_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_AUTO_HLG:
        case _HDR_TARGET_STATUS_FORCE_HLG:
            UserInterfaceColorHDRAdjustHDR10Proc(enumDisplayRegion);
            DebugMessageHDR("HLG Display Region", enumDisplayRegion);
            break;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR:
            UserInterfaceColorHDRAdjustFreeSyncIIProc(enumDisplayRegion);
            DebugMessageHDR("HDR Target Status Freesync2", 0x00);
            break;
#endif

        case _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR:
            UserInterfaceColorHDRAdjustSDRProc(enumDisplayRegion);
            DebugMessageHDR("HDR Target Status SDR", 0x00);
            break;

#if(_HDMI_SBTM_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_SBTM:
            UserInterfaceColorHDRAdjustHDR10Proc(enumDisplayRegion);
            DebugMessageHDR("HDR Target Status SBTM", enumDisplayRegion);
            break;
#endif

        default:
            break;
    }

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
    switch(enumHDRTargetStatus)
    {
#if(_HDR10_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_SMPTE_ST_2084:
#if(_ADVANCED_HDR10_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_ADVANCED_HDR10:
#endif
#if(_HLG_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_AUTO_HLG:
#endif
            SET_HDR10_UPDATE_COLORIMETRY(enumDisplayRegion);
            break;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
        case _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR:
            SET_FREESYNC_II_UPDATE_COLORIMETRY(enumDisplayRegion);
            break;
#endif

        case _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR:
            SET_SDR_UPDATE_COLORIMETRY(enumDisplayRegion);
            break;

        default:
            break;
    }
#endif
}

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : return applying HDR10 parameter or PCM parameter
// Input Value  : EnumDisplayRegion
// Output Value : _ON(HDR), _OFF(PCM)
//--------------------------------------------------
EnumHDR10Status UserCommonColorHDRGetHDR10Status(EnumDisplayRegion enumDisplayRegion)
{
    switch(SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX))
    {
        default:
        case 0x01:
        case 0x02:
            break;

        case 0x03:
        case 0x04:
            // Disable HDR for 3P/4P modes
            return _HDR10_OFF;
    }

    if(enumDisplayRegion != _DISPLAY_RGN_NONE)
    {
        EnumHDR10ModeDef enumHDR10ModeDef = GET_HDR10_MODE_STATUS(enumDisplayRegion);

        switch(enumHDR10ModeDef)
        {
            case _HDR10_MODE_FORCE_2084:
                return _HDR10_ON;

            case _HDR10_MODE_AUTO:
                if(GET_HDR10_EOTF_SETTING(enumDisplayRegion) == _HDR_INFO_EOTF_SMPTE_ST_2084)
                {
                    return _HDR10_ON;
                }
                break;

#if(_HLG_SUPPORT == _ON)
            case _HDR10_HLG_MODE_FORCE_HLG:
                return _HLG_ON;

            case _HDR10_HLG_MODE_AUTO:
                if(GET_HDR10_EOTF_SETTING(enumDisplayRegion) == _HDR_INFO_EOTF_HLG)
                {
                    return _HLG_ON;
                }
                else if(GET_HDR10_EOTF_SETTING(enumDisplayRegion) == _HDR_INFO_EOTF_SMPTE_ST_2084)
                {
                    return _HDR10_ON;
                }
                break;
#endif

            default:
                break;
        }
    }

    return _HDR10_OFF;
}

//--------------------------------------------------
// Description  : Check HDR change status according to EOTF, (primaries color), max mastering luminance
// Input Value  : EnumDisplayRegion
// Output Value : HDR chagne status
//--------------------------------------------------
EnumHDR10ChangeStatus UserCommonColorHDRGetHDR10ChangeStatus(EnumDisplayRegion enumDisplayRegion)
{
#if(_4P_DISPLAY_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() != _DISPLAY_MODE_4P)
#endif
    {
        BYTE ucEOTF = g_pstSyncHDR10SaticMetadata[ScalerSyncDxHDRMetadataIndexMapping(SysRegionGetInputPort(enumDisplayRegion))].ucEOTF;
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
        WORD usHDR10MaxMasteringLv = UserCommonColorHDRGetHDR10ApplyLv(enumDisplayRegion);
#endif
        EnumHDR10MaxMasteringLvType enumLvType = UserCommonColorHDRGetHDR10LvType(enumDisplayRegion, GET_HDR10_USER_DATA(enumDisplayRegion));

#if(_HDR10_USER_MASTERING_LV_CHANGE_SUPPORT == _ON)
        WORD usHDR10UserMaxMasteringLv = UserCommonColorHDRGetHDR10MaxDisplayLv(enumDisplayRegion);
#endif

        if(GET_HDR10_EOTF_SETTING(enumDisplayRegion) != ucEOTF)
        {
            SET_HDR10_EOTF_SETTING(enumDisplayRegion, ucEOTF);

            if(GET_HDR10_EOTF_SETTING(enumDisplayRegion) == _HDR_INFO_EOTF_SMPTE_ST_2084)
            {
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
                SET_HDR10_STEPLESS_MAX_LV_SETTING(enumDisplayRegion, usHDR10MaxMasteringLv);
#endif
#if(_HDR10_USER_MASTERING_LV_CHANGE_SUPPORT == _ON)
                SET_HDR10_USER_MAX_LV_SETTING(enumDisplayRegion, usHDR10UserMaxMasteringLv);
#endif
                SET_HDR10_MAX_LV_SETTING(enumDisplayRegion, enumLvType);
            }
            return _HDR10_INFO_EOTF_CHANGE;
        }

        if(GET_HDR10_EOTF_SETTING(enumDisplayRegion) == _HDR_INFO_EOTF_SMPTE_ST_2084)
        {
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
            if(GET_HDR10_USER_MASTERING_STEPLESS_TM_STATUS(enumDisplayRegion) == _MASTERING_LV_STEPLESS_TM_ON)
            {
                if(GET_HDR10_STEPLESS_MAX_LV_SETTING_CHG(enumDisplayRegion, usHDR10MaxMasteringLv) == _TRUE)
                {
                    SET_HDR10_STEPLESS_MAX_LV_SETTING(enumDisplayRegion, usHDR10MaxMasteringLv);
                    return _HDR10_INFO_MAX_LV_CHANGE;
                }
            }
            else
#endif
            {
#if(_HDR10_USER_MASTERING_LV_CHANGE_SUPPORT == _ON)
                if(GET_HDR10_USER_FORCE_MASTERING_LV_STATUS(enumDisplayRegion) == _USER_FORCE_MASTERING_LV_OFF)
                {
                    if(GET_HDR10_USER_MAX_LV_SETTING_CHG(enumDisplayRegion, usHDR10UserMaxMasteringLv) == _TRUE)
                    {
                        SET_HDR10_USER_MAX_LV_SETTING(enumDisplayRegion, usHDR10UserMaxMasteringLv);
                        return _HDR10_INFO_MAX_LV_CHANGE;
                    }
                }
                else
#endif
                {
                    if(GET_HDR10_MAX_LV_SETTING(enumDisplayRegion) != enumLvType)
                    {
                        SET_HDR10_MAX_LV_SETTING(enumDisplayRegion, enumLvType);
                        return _HDR10_INFO_MAX_LV_CHANGE;
                    }
                }
            }
        }
    }

    return _HDR10_INFO_NO_CHANGE;
}

//--------------------------------------------------
// Description  : Return HDR Max Mastering Lv Type by infoframe mastering Lv in HDR Auto Mode
// Input Value  : EnumDisplayRegion, StructHDR10UserData
// Output Value : HDR max mastering Lv type
//--------------------------------------------------
EnumHDR10MaxMasteringLvType UserCommonColorHDRGetHDR10LvType(EnumDisplayRegion enumDisplayRegion, StructHDR10UserData stHDR10UserData)
{
    WORD usMaxDisplayLv = UserCommonColorHDRGetHDR10MaxDisplayLv(enumDisplayRegion);
    WORD usMaxPanelLv = UserCommonColorHDRGetPanelMaxLv(stHDR10UserData.enumHDR10UserDefineMaxPanelLvType);

    if(usMaxDisplayLv > 0)
    {
        if(stHDR10UserData.enumHDR10UserForceMasteringLvStatus == _USER_FORCE_MASTERING_LV_ON)
        {
            return UserCommonColorHDRGetHDR10ModifyLvType(usMaxPanelLv, stHDR10UserData, _HDR10_MAX_MASTERING_LV_RECIEVED_TYPE);
        }
        if(usMaxDisplayLv <= usMaxPanelLv)
        {
            return UserCommonColorHDRGetHDR10NOTMLvType(stHDR10UserData.enumHDR10UserDefineMaxPanelLvType);
        }
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
        else if(stHDR10UserData.enumHDR10MasteringLvStepLessTMStatus == _MASTERING_LV_STEPLESS_TM_ON)
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_STEPLESS_TM;
        }
#endif
        else if(usMaxDisplayLv <= _HDR10_MAX_MASTERING_LV_540)
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_540;
        }
        else if(usMaxDisplayLv <= _HDR10_MAX_MASTERING_LV_1200)
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_1200;
        }
        else if(usMaxDisplayLv <= _HDR10_MAX_MASTERING_LV_4000)
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_4000;
        }
        else
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_10000;
        }
    }
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
    if(stHDR10UserData.enumHDR10MasteringLvStepLessTMStatus == _MASTERING_LV_STEPLESS_TM_ON)
    {
        if(stHDR10UserData.usHDR10StepLessMaxMasteringLv0 <= usMaxPanelLv)
        {
            return UserCommonColorHDRGetHDR10NOTMLvType(stHDR10UserData.enumHDR10UserDefineMaxPanelLvType);
        }
        else
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_STEPLESS_TM;
        }
    }
#endif
    return UserCommonColorHDRGetHDR10ModifyLvType(usMaxPanelLv, stHDR10UserData, _HDR10_MAX_MASTERING_LV_NONE_TYPE);
}

//--------------------------------------------------
// Description  : Protect User-assigned Mastering Lv Type from being lower than Panel Max Lv
// Input Value  : usMaxPanelLv, StructHDR10UserData
// Output Value : EnumHDR10MaxMasteringLvType
//--------------------------------------------------
EnumHDR10MaxMasteringLvType UserCommonColorHDRGetHDR10ModifyLvType(WORD usMaxPanelLv, StructHDR10UserData stHDR10UserData, EnumHDR10MasteringLvRecievedType enumHDR10MasteringLvRecievedType)
{
    WORD usMasteringLv = _HDR10_MAX_MASTERING_LV_540;
    EnumHDR10MaxMasteringLvType enumHDR10UserMaxMasteringLvType = _HDR10_MAX_MASTERING_LV_TYPE_540;
    if(enumHDR10MasteringLvRecievedType == _HDR10_MAX_MASTERING_LV_NONE_TYPE)
    {
        enumHDR10UserMaxMasteringLvType = stHDR10UserData.enumHDR10MaxMasteringLv0Type;
    }
    else
    {
        enumHDR10UserMaxMasteringLvType = stHDR10UserData.enumHDR10UserForceMaxMasteringLvType;
    }

    if(enumHDR10UserMaxMasteringLvType < _HDR10_MAX_MASTERING_LV_TYPE_NOTM)
    {
        switch(enumHDR10UserMaxMasteringLvType)
        {
            case _HDR10_MAX_MASTERING_LV_TYPE_540:
                usMasteringLv = _HDR10_MAX_MASTERING_LV_540;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_1200:
                usMasteringLv = _HDR10_MAX_MASTERING_LV_1200;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_4000:
                usMasteringLv = _HDR10_MAX_MASTERING_LV_4000;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_10000:
                usMasteringLv = _HDR10_MAX_MASTERING_LV_10000;
                break;

            default:
                break;
        }

        if(usMasteringLv <= usMaxPanelLv)
        {
            return UserCommonColorHDRGetHDR10NOTMLvType(stHDR10UserData.enumHDR10UserDefineMaxPanelLvType);
        }
        else
        {
            return enumHDR10UserMaxMasteringLvType;
        }
    }
    return enumHDR10UserMaxMasteringLvType;
}

//--------------------------------------------------
// Description  : Return applied HDR Max Mastering Lv Type according to HDR Auto/Force Mode
// Input Value  : EnumDisplayRegion
// Output Value : HDR max mastering Lv type
//--------------------------------------------------
EnumHDR10MaxMasteringLvType UserCommonColorHDRGetHDR10ApplyLvType(EnumDisplayRegion enumDisplayRegion)
{
    EnumHDR10MaxMasteringLvType enumHDR10MaxMasteringLvType = _HDR10_MAX_MASTERING_LV_TYPE_540;

    if(GET_HDR10_MODE_STATUS(enumDisplayRegion) == _HDR10_MODE_FORCE_2084)
    {
        enumHDR10MaxMasteringLvType = GET_HDR10_USER_FORCE_MODE_MASTERING_LV_TYPE(enumDisplayRegion);
    }
    else
    {
        enumHDR10MaxMasteringLvType = UserCommonColorHDRGetHDR10LvType(enumDisplayRegion, GET_HDR10_USER_DATA(enumDisplayRegion));
    }
    return enumHDR10MaxMasteringLvType;
}

//--------------------------------------------------
// Description  : Return HDR NOTM Max Mastering Lv Type by
// Input Value  : EnumHDR10UserDefineMaxPanelLvType
// Output Value : HDR max mastering Lv type
//--------------------------------------------------
EnumHDR10MaxMasteringLvType UserCommonColorHDRGetHDR10NOTMLvType(EnumHDR10UserDefineMaxPanelLvType enumHDR10UserDefineMaxPanelLvType)
{
    switch(enumHDR10UserDefineMaxPanelLvType)
    {
        case _HDR10_PANEL_MAX_PEAK_LV:
        default:
            return _HDR10_MAX_MASTERING_LV_TYPE_NOTM;
            break;

#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
        case _HDR10_PANEL_MAX_FRAME_AVERAGE_LV:
            return _HDR10_MAX_MASTERING_LV_TYPE_NOTM_FRAME_AVERAGE_LV;
            break;

        case _HDR10_PANEL_MAX_USER_DEFINE_LV:
            return _HDR10_MAX_MASTERING_LV_TYPE_NOTM_USER_DEFINE_LV;
            break;
#endif
    }

    return _HDR10_MAX_MASTERING_LV_TYPE_NOTM;
}

//--------------------------------------------------
// Description  : Get HDR10 Color Matrix
// Input Value  : EnumDisplayRegion
// Output Value : EnumHDR10ColorMatrix
//--------------------------------------------------
EnumHDR10ColorMatrix UserCommonColorHDRGetHDR10ColorMatrix(EnumDisplayRegion enumDisplayRegion)
{
#if(_FREESYNC_II_FORCE_HDR10_BT2020_SUPPORT == _ON)
    enumDisplayRegion = enumDisplayRegion;
    DebugMessageHDR("HDR apply BT2020 matrix", 0x00);
    return _HDR10_COLOR_MATRIX_BT2020;
#else
    switch(ScalerColorSpaceGetColorimetry(SysRegionGetInputPort(enumDisplayRegion)))
    {
        case _COLORIMETRY_RGB_SRGB:
        case _COLORIMETRY_RGB_XRRGB:
        case _COLORIMETRY_RGB_SCRGB:
        case _COLORIMETRY_YCC_SMPTE_170M:
        case _COLORIMETRY_YCC_ITUR_BT601:
        case _COLORIMETRY_YCC_ITUR_BT709:
        case _COLORIMETRY_YCC_XVYCC601:
        case _COLORIMETRY_YCC_XVYCC709:

            DebugMessageHDR("HDR apply SRGB matrix", 0x00);
            return _HDR10_COLOR_MATRIX_SRGB;

        case _COLORIMETRY_RGB_ADOBERGB:

            DebugMessageHDR("HDR apply AdobeRGB matrix", 0x00);
            return _HDR10_COLOR_MATRIX_ADOBE;

        case _COLORIMETRY_RGB_DCI_P3:

            DebugMessageHDR("HDR apply DCIP3_D65 matrix", 0x00);
            return _HDR10_COLOR_MATRIX_DCIP3_D65;

        case _COLORIMETRY_EXT:

            switch(ScalerColorSpaceGetExtColorimetry(SysRegionGetInputPort(enumDisplayRegion)))
            {
                case _COLORIMETRY_EXT_RGB_SRGB:
                case _COLORIMETRY_EXT_RGB_XRRGB:
                case _COLORIMETRY_EXT_RGB_SCRGB:
                case _COLORIMETRY_EXT_YCC_ITUR_BT601:
                case _COLORIMETRY_EXT_YCC_ITUR_BT709:
                case _COLORIMETRY_EXT_YCC_XVYCC601:
                case _COLORIMETRY_EXT_YCC_XVYCC709:
                case _COLORIMETRY_EXT_YCC_SYCC601:

                    DebugMessageHDR("HDR apply SRGB matrix EXT", 0x00);
                    return _HDR10_COLOR_MATRIX_SRGB;

                case _COLORIMETRY_EXT_RGB_ADOBERGB:
                case _COLORIMETRY_EXT_YCC_ADOBEYCC601:

                    DebugMessageHDR("HDR apply AdobeRGB matrix EXT", 0x00);
                    return _HDR10_COLOR_MATRIX_ADOBE;

                case _COLORIMETRY_EXT_RGB_DCI_P3:

                    DebugMessageHDR("HDR apply DCIP3_D65 matrix EXT", 0x00);
                    return _HDR10_COLOR_MATRIX_DCIP3_D65;

#if((_HW_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2) || (_HW_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_4))
                case _COLORIMETRY_EXT_RGB_ITUR_BT2020:
                case _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL:
                case _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL:

                    DebugMessageHDR("HDR apply BT2020 matrix", 0x00);
                    return _HDR10_COLOR_MATRIX_BT2020;
#endif
                default:

                    DebugMessageHDR("HDR apply BT2020 matrix EXT default", 0x00);
                    return _HDR10_COLOR_MATRIX_BT2020;
            }
            break;

        default:

            DebugMessageHDR("HDR apply BT2020 matrix default", 0x00);
            return _HDR10_COLOR_MATRIX_BT2020;
    }

    return _HDR10_COLOR_MATRIX_BT2020;
#endif
}

//--------------------------------------------------
// Description  : Get HDR10 Color Matrix address
// Input Value  : EnumDisplayRegion
// Output Value : WORD
//--------------------------------------------------
WORD UserCommonColorHDRGetHDR10ColorMatrixAddress(EnumHDR10ColorMatrix enumHDR10ColorMatrix)
{
    switch(enumHDR10ColorMatrix)
    {
        case _HDR10_COLOR_MATRIX_SRGB:
            return _OCC_HDR10_SRGB_MATRIX_ADDRESS;

        case _HDR10_COLOR_MATRIX_ADOBE:
            return _OCC_HDR10_ADOBE_MATRIX_ADDRESS;

        case _HDR10_COLOR_MATRIX_DCIP3_D65:
            return _OCC_HDR10_DCIP3_D65_MATRIX_ADDRESS;

        case _HDR10_COLOR_MATRIX_BT2020:
            return _OCC_HDR10_BT2020_MATRIX_ADDRESS;

        default:
            return _OCC_HDR10_BT2020_MATRIX_ADDRESS;
    }
}

//--------------------------------------------------
// Description  : Return HDR LocalContrast Max Mastering Lv Type (540/1200/4000/10000 nit)
// Input Value  : EnumDisplayRegion
// Output Value : HDR LightEnhance max mastering Lv type (540/1200/4000/10000 nit)
//--------------------------------------------------
EnumHDR10StaticMasteringLvType UserCommonColorHDRGetHDR10LvTypeForStaticMastering(EnumSelRegion enumSelRegion)
{
    EnumDisplayRegion enumDisplayRegion = UserCommonColorHDRGetDisplayRegion(enumSelRegion);
    EnumHDR10MaxMasteringLvType enumHDR10MaxMasteringLvType = UserCommonColorHDRGetHDR10ApplyLvType(enumDisplayRegion);

    // NoTM case Need to Modify MaxMasteringLvType
    if(enumHDR10MaxMasteringLvType > _HDR10_MAX_MASTERING_LV_TYPE_10000)
    {
        WORD usMaxDisplayLv = UserCommonColorHDRGetHDR10MaxDisplayLv(enumDisplayRegion);

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
        if(enumHDR10MaxMasteringLvType == _HDR10_MAX_MASTERING_LV_TYPE_STEPLESS_TM)
        {
            usMaxDisplayLv = UserCommonColorHDRGetHDR10ApplyLv(enumDisplayRegion);
        }
        else
#endif
        {
            // Check mastering level is 0
            if(usMaxDisplayLv == 0)
            {
                usMaxDisplayLv = UserCommonColorHDRGetPanelMaxLv(GET_HDR10_USER_DEF_PANEL_LV_TYPE(enumDisplayRegion));
            }
        }

        if(usMaxDisplayLv <= _HDR10_MAX_MASTERING_LV_540)
        {
            enumHDR10MaxMasteringLvType = _HDR10_MAX_MASTERING_LV_TYPE_540;
        }
        else if(usMaxDisplayLv <= _HDR10_MAX_MASTERING_LV_1200)
        {
            enumHDR10MaxMasteringLvType = _HDR10_MAX_MASTERING_LV_TYPE_1200;
        }
        else if(usMaxDisplayLv <= _HDR10_MAX_MASTERING_LV_4000)
        {
            enumHDR10MaxMasteringLvType = _HDR10_MAX_MASTERING_LV_TYPE_4000;
        }
        else
        {
            enumHDR10MaxMasteringLvType = _HDR10_MAX_MASTERING_LV_TYPE_10000;
        }
    }

    return (EnumHDR10StaticMasteringLvType)enumHDR10MaxMasteringLvType;
}

//--------------------------------------------------
// Description  : Return HDR EOTF Setting
// Input Value  : EnumDisplayRegion
// Output Value : EnumHDR10InfoEOTF
//--------------------------------------------------
EnumHDR10InfoEOTF UserCommonColorHDR10GetEOTFSetting(EnumDisplayRegion enumDisplayRegion)
{
    return GET_HDR10_EOTF_SETTING(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Return HDR Change Status
// Input Value  : EnumDisplayRegion
// Output Value : EnumHDR10InfoEOTF
//--------------------------------------------------
EnumHDR10ChangeStatus UserCommonColorHDR10GetHDRChangeStatus(EnumDisplayRegion enumDisplayRegion)
{
    return GET_HDR_CHANGE_STATUS(enumDisplayRegion);
}

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Ajust Light Enhance
// Input Value  : EnumDisplayRegion, EnumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRAdjustHDR10LightEnhance(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    StructColorDCCSetting stDCC = {0};
    StructColorIAPSSetting stIAPS = {0};

    if((GET_DCC_REGION_ENABLE(enumSelRegion) != _OFF) && (GET_IAPS_REGION_ENABLE(enumSelRegion) != _OFF))   // Not in Multi-Function.
    {
        UserCommonColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        UserCommonColorIAPSRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
    }

    UserCommonColorGetDCCData(enumSelRegion, &stDCC);
    ScalerColorIPDCCAdjust(enumSelRegion, &stDCC);
    UserCommonColorGetIAPSData(enumSelRegion, &stIAPS);
    ScalerColorIPIAPSAdjust(enumSelRegion, &stIAPS);

    if(stDCC.stDCCSetting.enumDCCMode != _DCC_OFF)
    {
        UserCommonColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
    }

    if(stIAPS.stIAPSSetting.enumIAPSMode != _IAPS_OFF)
    {
        UserCommonColorIAPSRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
    }
    UserCommonDisplayGlobalDDomainDBApply(enumSelRegion, enumDBApply);
}
#endif

#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Ajust Color Enhance
// Input Value  : EnumDisplayRegion, EnumDBApply
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRAdjustHDR10ColorEnhance(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    StructColorICMSetting stICM = {0};

#if(_HW_ICM_DB_TYPE == _ICM_DB_GEN_0)
    UserCommonColorICMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
#endif

    UserCommonColorGetICMData(enumSelRegion, &stICM);
    ScalerColorIPICMAdjust(enumSelRegion, &stICM);

#if(_HW_ICM_DB_TYPE == _ICM_DB_GEN_0)
    if(stICM.stICMSetting.enumICMMode != _ICM_OFF)
    {
        UserCommonColorICMRegionEnable(enumSelRegion, enumDBApply, _ON);
    }
#else
    // Always keep region _ON when ICM _OFF(need to load lc bypass table), so not need to polling region apply
    UserCommonColorICMRegionEnable(enumSelRegion, enumDBApply, _ON);
#endif
}
#endif

//--------------------------------------------------
// Description  : return HDR10 No ToneMapping Bound Lv Address
// Input Value  : EnumHDR10UserDefineMaxPanelLvType
// Output Value : _ON(Freesync II), _OFF(PCM)
//--------------------------------------------------
WORD UserCommonColorHDRGetHDR10NOTMBoundAddr(EnumHDR10UserDefineMaxPanelLvType enumHDR10UserDefineMaxPanelLvType)
{
    switch(enumHDR10UserDefineMaxPanelLvType)
    {
        case _HDR10_PANEL_MAX_PEAK_LV:
        default:
            return _OGC_HDR10_NOTM_BOUND_ADDRESS;
            break;
#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
        case _HDR10_PANEL_MAX_FRAME_AVERAGE_LV:
            return _OGC_HDR10_NOTM_BOUND_FRAME_AVG_LV_ADDRESS;
            break;

        case _HDR10_PANEL_MAX_USER_DEFINE_LV:
            return _OGC_HDR10_NOTM_BOUND_USER_DEF_LV_ADDRESS;
            break;
#endif
    }

    return _OGC_HDR10_NOTM_BOUND_ADDRESS;
}

//--------------------------------------------------
// Description  : Calculate HDR LUT Address
// Input Value  : enumDisplayRegion
// Output Value : pucHDR10LUTAddr
//--------------------------------------------------
WORD UserCommonColorHDRGetHDR10IGLUTAddr(EnumHDR10MaxMasteringLvType enumHDR10MaxMasteringLvType, EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus, EnumHDR10FixedPointToneMappingStatus enumHDR10FixedPointToneMappingStatus)
{
    WORD usHDR10LUTAddr = _OGC_HDR10_IG_540_NOR_ADDRESS;

#if(_HDR10_USER_DEFINE_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
    if(enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_USER)
    {
        switch(enumHDR10MaxMasteringLvType)
        {
            case _HDR10_MAX_MASTERING_LV_TYPE_540:
            default:
                usHDR10LUTAddr = _OGC_HDR10_IG_540_USER_FIXED_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_1200:
                usHDR10LUTAddr = _OGC_HDR10_IG_1200_USER_FIXED_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_4000:
                usHDR10LUTAddr = _OGC_HDR10_IG_4000_USER_FIXED_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_10000:
                usHDR10LUTAddr = _OGC_HDR10_IG_10000_USER_FIXED_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_NOTM:
                usHDR10LUTAddr = _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                break;

#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
            case _HDR10_MAX_MASTERING_LV_TYPE_NOTM_FRAME_AVERAGE_LV:
                usHDR10LUTAddr = _OGC_HDR10_IG_NOTM_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_NOTM_USER_DEFINE_LV:
                usHDR10LUTAddr = _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                break;
#endif
        }
    }
    else
#endif
    {
#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
        if(enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON)
        {
            switch(enumHDR10MaxMasteringLvType)
            {
                case _HDR10_MAX_MASTERING_LV_TYPE_540:
                default:
                    usHDR10LUTAddr = _OGC_HDR10_IG_540_FIXED_POINT_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_1200:
                    usHDR10LUTAddr = _OGC_HDR10_IG_1200_FIXED_POINT_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_4000:
                    usHDR10LUTAddr = _OGC_HDR10_IG_4000_FIXED_POINT_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_10000:
                    usHDR10LUTAddr = _OGC_HDR10_IG_10000_FIXED_POINT_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_NOTM:
                    usHDR10LUTAddr = _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
                case _HDR10_MAX_MASTERING_LV_TYPE_NOTM_FRAME_AVERAGE_LV:
                    usHDR10LUTAddr = _OGC_HDR10_IG_NOTM_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_NOTM_USER_DEFINE_LV:
                    usHDR10LUTAddr = _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;
#endif
            }
        }
        else
#endif
        {
            enumHDR10FixedPointToneMappingStatus = enumHDR10FixedPointToneMappingStatus;
            switch(enumHDR10MaxMasteringLvType)
            {
                case _HDR10_MAX_MASTERING_LV_TYPE_540:
                default:
                    usHDR10LUTAddr = _OGC_HDR10_IG_540_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_1200:
                    usHDR10LUTAddr = _OGC_HDR10_IG_1200_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_4000:
                    usHDR10LUTAddr = _OGC_HDR10_IG_4000_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_10000:
                    usHDR10LUTAddr = _OGC_HDR10_IG_10000_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_NOTM:
                    usHDR10LUTAddr = _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
                case _HDR10_MAX_MASTERING_LV_TYPE_NOTM_FRAME_AVERAGE_LV:
                    usHDR10LUTAddr = _OGC_HDR10_IG_NOTM_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;

                case _HDR10_MAX_MASTERING_LV_TYPE_NOTM_USER_DEFINE_LV:
                    usHDR10LUTAddr = _OGC_HDR10_IG_NOTM_USER_DEF_PEAK_NOR_ADDRESS + _OGC_HDR10_IG_TABLE_SIZE * enumHDR10DarkEnhanceStatus;
                    break;
#endif
            }
        }
    }
    return usHDR10LUTAddr;
}

//--------------------------------------------------
// Description  : Get HDR10 Panel Max Lv
// Input Value  : pucIGLUTFlashAddress
// Output Value : pucTH
//--------------------------------------------------
WORD UserCommonColorHDRGetPanelMaxLv(EnumHDR10UserDefineMaxPanelLvType enumHDR10UserDefineMaxPanelLvType)
{
    WORD usPanelMaxLv = 0;
    WORD usHDR10NOTMBoundAddr = UserCommonColorHDRGetHDR10NOTMBoundAddr(enumHDR10UserDefineMaxPanelLvType);
    BYTE pucTemp[2] = {0};

    ScalerFlashRead(_OGC_FLASH_BANK, (BYTE *)((((WORD)_OGC_FLASH_PAGE) << 12) + usHDR10NOTMBoundAddr + 2), 2, pucTemp);
    usPanelMaxLv = TO_WORD(pucTemp[0], pucTemp[1]);
    return usPanelMaxLv;
}

//--------------------------------------------------
// Description  : return HDR parameter Max Display Lv
// Input Value  : None
// Output Value : HDR Max Display Lv
//--------------------------------------------------
WORD UserCommonColorHDRGetHDR10MaxDisplayLv(EnumDisplayRegion enumDisplayRegion)
{
#if(_HDR10_TONEMAPPING_BY_MAXCLL_SUPPORT == _ON)
    if(g_pstSyncHDR10SaticMetadata[ScalerSyncDxHDRMetadataIndexMapping(SysRegionGetInputPort(enumDisplayRegion))].usMaxCLL == 0)
    {
        return (g_pstSyncHDR10SaticMetadata[ScalerSyncDxHDRMetadataIndexMapping(SysRegionGetInputPort(enumDisplayRegion))].usMaxDisplayMasteringLv);
    }
    else
    {
        return (g_pstSyncHDR10SaticMetadata[ScalerSyncDxHDRMetadataIndexMapping(SysRegionGetInputPort(enumDisplayRegion))].usMaxCLL);
    }
#else
    return (g_pstSyncHDR10SaticMetadata[ScalerSyncDxHDRMetadataIndexMapping(SysRegionGetInputPort(enumDisplayRegion))].usMaxDisplayMasteringLv);
#endif
}

//--------------------------------------------------
// Description  : User Get HDR10 Panel Max Lv
// Input Value  : enumDisplayRegion
// Output Value : Max Lv
//--------------------------------------------------
WORD UserCommonColorHDRUserGetPanelMaxLv(EnumDisplayRegion enumDisplayRegion)
{
    StructHDR10UserData structHDR10UserData;
    memset(&structHDR10UserData, 0, sizeof(StructHDR10UserData));

    structHDR10UserData = GET_HDR10_USER_DATA(enumDisplayRegion);
    return UserCommonColorHDRGetPanelMaxLv(structHDR10UserData.enumHDR10UserDefineMaxPanelLvType);
}

#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : return applying Freesync II parameter or PCM parameter
// Input Value  : bit
// Output Value : _ON(Freesync II), _OFF(PCM)
//--------------------------------------------------
bit UserCommonColorHDRGetFreesynIIStatus(EnumDisplayRegion enumDisplayRegion)
{
    if((UserCommonColorHDRGetFreesyncIIDisplayMode() == _ON) && (enumDisplayRegion != _DISPLAY_RGN_NONE))
    {
        if((GET_FREESYNC_II_MODE_STATUS(enumDisplayRegion) != _FREESYNC_SUPPORT_OFF) &&
           (GET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING(enumDisplayRegion) == _ON))
        {
            return _ON;
        }
    }

    return _OFF;
}
//--------------------------------------------------
// Description  : Check AMD HDR change status
// Input Value  : EnumInputPort
// Output Value : HDR chagne status
//--------------------------------------------------
BYTE UserCommonColorHDRFreeSyncIIChangeStatus(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucFreeSyncIIChangeStatus = _FREESYNC_II_INFO_NO_CHANGE;

    if(UserCommonColorHDRGetFreesyncIIDisplayMode() == _ON)
    {
        StructFreeSyncIIInfo *pstMetaData = &g_pstSyncFreeIIMetadata[ScalerRegionGetIndex(enumDisplayRegion)];

        if(GET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING(enumDisplayRegion) != (pstMetaData->b1NativeColorSpaceEnable))
        {
            SET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING(enumDisplayRegion, (pstMetaData->b1NativeColorSpaceEnable));
            ucFreeSyncIIChangeStatus |= _FREESYNC_II_COLOR_SPACE_CHANGE;
        }

        if(GET_FREESYNC_II_LOCAL_DIMMING_DISABLE_SETTING(enumDisplayRegion) != (pstMetaData->b1LocalDimmingDisable))
        {
            SET_FREESYNC_II_LOCAL_DIMMING_DISABLE_SETTING(enumDisplayRegion, (pstMetaData->b1LocalDimmingDisable));
            ucFreeSyncIIChangeStatus |= _FREESYNC_II_LOCAL_DIMMING_CHANGE;
        }

        if(GET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING(enumDisplayRegion) == _ON)
        {
            if(GET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING(enumDisplayRegion) != (pstMetaData->b1BacklightControlEnable))
            {
                SET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING(enumDisplayRegion, (pstMetaData->b1BacklightControlEnable));
                ucFreeSyncIIChangeStatus |= _FREESYNC_II_BACKLIGHT_CONTROL_CHANGE;
            }

            if(GET_FREESYNC_II_EOTF_TYPE_SETTING(enumDisplayRegion) != (pstMetaData->b5EOTFType))
            {
                SET_FREESYNC_II_EOTF_TYPE_SETTING(enumDisplayRegion, (pstMetaData->b5EOTFType));
                ucFreeSyncIIChangeStatus |= _FREESYNC_II_EOTF_TYPE_CHANGE;
            }

            if(GET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING(enumDisplayRegion) == _ON)
            {
                if(GET_FREESYNC_II_BACKLIGHT_CONTROL_RATIO_SETTING(enumDisplayRegion) != (pstMetaData->ucBacklightControlRatio))
                {
                    SET_FREESYNC_II_BACKLIGHT_CONTROL_RATIO_SETTING(enumDisplayRegion, (pstMetaData->ucBacklightControlRatio));
                    ucFreeSyncIIChangeStatus |= _FREESYNC_II_BACKLIGHT_RATIO_CHANGE;
                }
            }
        }
    }

    return ucFreeSyncIIChangeStatus;
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRAdjustFreeSyncIIMode(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucBacklight = 255;

    enumDisplayRegion = enumDisplayRegion;

    UserInterfaceColorCalibrationAdjustBacklight(ucBacklight);
}

//--------------------------------------------------
// Description  : Get FreeSync II Local Dimming Support Status
// Input Value  : Display Region
// Output Value : Local Dimming Support
//--------------------------------------------------
bit UserCommonColorHDRGetFreeSyncIILDDisable(EnumDisplayRegion enumDisplayRegion)
{
    if(UserCommonColorHDRGetFreesyncIIDisplayMode() == _ON)
    {
        return GET_FREESYNC_II_LOCAL_DIMMING_DISABLE_SETTING(enumDisplayRegion);
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get FreeSync II EOTF Type
// Input Value  : Display Region
// Output Value : EnumFreeSyncIIEOTFType
//--------------------------------------------------
EnumFreeSyncIIEOTFType UserCommonColorHDRGetFreeSyncIIEOTFType(EnumDisplayRegion enumDisplayRegion)
{
    if(UserCommonColorHDRGetFreesyncIIDisplayMode() == _ON)
    {
        switch(GET_FREESYNC_II_EOTF_TYPE_SETTING(enumDisplayRegion))
        {
            case _FREESYNC_II_EOTF_SRGB_GET_BIT:
                return _FREESYNC_II_EOTF_SRGB;

            case _FREESYNC_II_EOTF_BT709_GET_BIT:
                return _FREESYNC_II_EOTF_BT709;

            case _FREESYNC_II_EOTF_GAMMA_22_GET_BIT:
                return _FREESYNC_II_EOTF_GAMMA_22;

            case _FREESYNC_II_EOTF_GAMMA_26_GET_BIT:
                return _FREESYNC_II_EOTF_GAMMA_26;

            case _FREESYNC_II_EOTF_PQ_INTERIM_GET_BIT:
                return _FREESYNC_II_EOTF_PQ_INTERIM;

            default:
                return _FREESYNC_II_EOTF_GAMMA_22;
        }
    }

    return _FREESYNC_II_EOTF_GAMMA_22;
}

//--------------------------------------------------
// Description  : return applying Freesync II parameter or PCM parameter
// Input Value  : bit
// Output Value : _ON(Freesync II), _OFF(PCM)
//--------------------------------------------------
bit UserCommonColorHDRGetFreesyncIIDisplayMode(void)
{
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_1P))
#else
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
#endif
    {
        return _ON;
    }
    return _OFF;
}
#endif // End of #if(_FREESYNC_II_SUPPORT == _ON)

#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : return HDR10 BackLight Adaptive ToneMapping Status
// Input Value  : None
// Output Value : EnumHDR10BackLightAdaptiveTMStatus
//--------------------------------------------------
EnumHDR10BackLightAdaptiveTMStatus UserCommonColorHDRGetBackLightAdaptiveTMStatus(EnumDisplayRegion enumDisplayRegion)
{
    if((UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON) && (UserCommonColorHDRGetHDR10ApplyLvType(enumDisplayRegion) == _HDR10_MAX_MASTERING_LV_TYPE_NOTM))
    {
        return _BACKLIGHT_ADAPTIVE_TM_ON;
    }

    return _BACKLIGHT_ADAPTIVE_TM_OFF;
}

//--------------------------------------------------
// Description  : HDR10 BackLight Adaptive ToneMapping Adjust
// Input Value  : EnumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRBackLightAdaptiveTMAdjust(EnumSelRegion enumSelRegion)
{
    StructColorYmappingSetting stYmapping = {0};

    UserCommonColorGetYmappingData(enumSelRegion, &stYmapping);
    ScalerColorIPYmappingAdjust(enumSelRegion, &stYmapping);
}

//--------------------------------------------------
// Description  : Get HDR10 BackLight Adaptive ToneMapping Ymapping Table
// Input Value  : enumDisplayRegion, ucBackLight, enumHDR10DarkEnhanceStatus
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRGetBackLightAdaptiveTMTable(EnumDisplayRegion enumDisplayRegion, WORD usBackLight, WORD usBackLightMax, EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus, StructColorYmappingSetting *pstYmData)
{
    WORD usPanelMaxLv = GET_HDR10_PANEL_MAX_LV(enumDisplayRegion);
    StructHDR10BackLightAdaptiveTMData stHDRData;

    stHDRData.pusHDRLinearOut = g_pusColorHDR10LinearOut;
    ScalerColorHDRGetBackLightAdaptiveTable(_OGC_FLASH_BANK, usPanelMaxLv, usBackLight, usBackLightMax, enumHDR10DarkEnhanceStatus, &stHDRData);
    pstYmData->unKernelYmappingData.stKernelYmappingHDR10BackLightAdaptiveTMData.ucLvMatchBound = stHDRData.ucLvMatchBound;
    pstYmData->unKernelYmappingData.stKernelYmappingHDR10BackLightAdaptiveTMData.usLvMatchBoundGain = stHDRData.usLvMatchBoundGain;
    pstYmData->unKernelYmappingData.stKernelYmappingHDR10BackLightAdaptiveTMData.pusHDRLinearOut = stHDRData.pusHDRLinearOut;
}

//--------------------------------------------------
// Description  : Get HDR10 Back Light Status when BackLight Adaptive TM Suppoer is On
// Input Value  : none
// Output Value : EnumHDR10BackLightAdaptiveTMBackLightStatus
//--------------------------------------------------
EnumHDR10BackLightAdaptiveTMBackLightStatus UserCommonColorHDRGetBackLightAdaptiveTMBackLightStatus(void)
{
    BYTE ucIndex = 0x00;
    BYTE ucMaxIndex = SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX);
    EnumHDR10BackLightAdaptiveTMBackLightStatus enumBackLightStatus = _HDR10_BACKLIGHT_ADAPTIVE_TM_BACKLIGHT_OSD;

    if(ucMaxIndex <= 2) // HDR does't support > 2P, so there will be no any region in HDR Satus, backlight should follow OSD
    {
        // Check separate display state
        for(ucIndex = 0x00; ucIndex < ucMaxIndex; ++ucIndex)
        {
#if(_HLG_SUPPORT == _ON)
            EnumHDR10Status enumHDR10Status = UserCommonColorHDRGetHDR10Status(SysRegionGetDisplayRegion(ucIndex));
            if(enumHDR10Status == _HLG_ON)
            {
                enumBackLightStatus |= _HDR10_BACKLIGHT_ADAPTIVE_TM_BACKLIGHT_MAX; // if BackLight Adaptive TM Support is off, when there is any region in HLG Status, backlight should be max
            }
#endif
        }
    }

    return enumBackLightStatus;
}

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get HDR10 BackLight Adaptive ToneMapping Node
// Input Value  : ucIGIndex (0~255)
// Output Value : BackLight Adaptive ToneMapping Node, normalize to 0 ~1000
//--------------------------------------------------
WORD UserCommonColorHDRGetBackLightAdaptiveTMNode(BYTE ucIGIndex)
{
    BYTE ucIGNodeIndex = ucIGIndex / 2;
    WORD usMaxHDRLinearOut = g_pusColorHDR10LinearOut[ucIGNodeIndex];

    if((ucIGIndex & _BIT0) == _BIT0)
    {
        usMaxHDRLinearOut = (WORD)(((DWORD)usMaxHDRLinearOut + g_pusColorHDR10LinearOut[ucIGNodeIndex + 1]) / 2);
    }

    return (WORD)(((DWORD)usMaxHDRLinearOut * 1000) / 65472);
}
#endif
#endif

#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDR10 Mastering Lv StepLess ToneMapping Table
// Input Value  : EnumDisplayRegion, usMaxDisplayMasteringLv, EnumHDR10DarkEnhanceStatus
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRGetMasteringLvStepLessTMTable(EnumDisplayRegion enumDisplayRegion, WORD usMaxDisplayMasteringLv, EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus)
{
    WORD usPanelMaxLv = GET_HDR10_PANEL_MAX_LV(enumDisplayRegion);

    if(usMaxDisplayMasteringLv <= usPanelMaxLv)
    {
        EnumHDR10MaxMasteringLvType enumHDR10MaxMasteringLvType = UserCommonColorHDRGetHDR10NOTMLvType(GET_HDR10_USER_DEF_PANEL_LV_TYPE(enumDisplayRegion));
        WORD usHDR10NOTMLUTAddr = UserCommonColorHDRGetHDR10IGLUTAddr(enumHDR10MaxMasteringLvType, enumHDR10DarkEnhanceStatus, _HDR10_FIXED_POINT_TM_OFF);
        ScalerFlashRead(_OGC_FLASH_BANK, (BYTE *)(DWORD)usHDR10NOTMLUTAddr, 197, g_pucColorHDR10StepLessTMIGLUT);
        return;
    }
    else
    {
        ScalerColorHDRGetMasteringLvStepLessTMTable(_OGC_FLASH_BANK, usPanelMaxLv, usMaxDisplayMasteringLv, enumHDR10DarkEnhanceStatus, g_pucColorHDR10StepLessTMIGLUT);
    }
}

#if(_GLOBAL_DIMMING_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get HDR10 Mastering Lv StepLess ToneMapping Node
// Input Value  : IG_Index (0~255)
// Output Value : Mastering Lv StepLess ToneMapping Node, normalize to 0 ~1000
//--------------------------------------------------
WORD UserCommonColorHDRGetMasteringLvStepLessTMNode(BYTE ucIGIndex)
{
    BYTE ucIGNode = ucIGIndex / 2;
    BYTE ucIGFlashNode = ucIGNode / 2 * 3;
    BYTE ucTHLow = g_pucColorHDR10StepLessTMIGLUT[195];
    BYTE ucTHHigh = g_pucColorHDR10StepLessTMIGLUT[196];
    WORD usLUTInterpRes = 0;

    if((ucIGIndex & _BIT0) == _BIT0) // Index % 2 != 0
    {
        WORD pusLUTRes[2] = {0};

        if((ucIGNode & _BIT0) == _BIT0)
        {
            pusLUTRes[0] = (WORD)((g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode + 1] & 0x0F) << 8) | g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode + 2];
            pusLUTRes[1] = (WORD)(g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode + 3] << 4) | (g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode + 4] >> 4);
        }
        else
        {
            pusLUTRes[0] = (WORD)(g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode] << 4) | (g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode + 1] >> 4);
            pusLUTRes[1] = (WORD)((g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode + 1] & 0x0F) << 8) | g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode + 2];
        }

        if(ucIGNode > ucTHHigh)
        {
            pusLUTRes[0] = (pusLUTRes[0] << 4);
        }
        else if(ucIGNode > ucTHLow)
        {
            pusLUTRes[0] = (pusLUTRes[0] << 2);
        }

        if((ucIGNode + 1) > ucTHHigh)
        {
            pusLUTRes[1] = (pusLUTRes[1] << 4);
        }
        else if((ucIGNode + 1) > ucTHLow)
        {
            pusLUTRes[1] = (pusLUTRes[1] << 2);
        }

        usLUTInterpRes = (WORD)(((DWORD)pusLUTRes[0] + (DWORD)pusLUTRes[1] + 1) / 2);

        if(usLUTInterpRes >= 16382)
        {
            usLUTInterpRes = ((usLUTInterpRes + 8) >> 4) << 4;
        }
        else if(usLUTInterpRes >= 4096)
        {
            usLUTInterpRes = ((usLUTInterpRes + 2) >> 2) << 2;
        }
    }
    else
    {
        if((ucIGNode & _BIT0) == _BIT0)
        {
            usLUTInterpRes = (WORD)((g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode + 1] & 0x0F) << 8) | g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode + 2];
        }
        else
        {
            usLUTInterpRes = (WORD)(g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode] << 4) | (g_pucColorHDR10StepLessTMIGLUT[ucIGFlashNode + 1] >> 4);
        }

        if(ucIGNode > ucTHHigh)
        {
            usLUTInterpRes = (usLUTInterpRes << 4);
        }
        else if(ucIGNode > ucTHLow)
        {
            usLUTInterpRes = (usLUTInterpRes << 2);
        }
    }

    return (WORD)(((DWORD)usLUTInterpRes * 1000) / 65472);
}
#endif

//--------------------------------------------------
// Description  : Return applied HDR Max Mastering Lv according to HDR Auto/Force Mode
// Input Value  : EnumDisplayRegion
// Output Value : HDR max mastering Lv
//--------------------------------------------------
WORD UserCommonColorHDRGetHDR10ApplyLv(EnumDisplayRegion enumDisplayRegion)
{
    WORD usHDR10ApplyMaxMasteringLv = 0;

    if(GET_HDR10_MODE_STATUS(enumDisplayRegion) == _HDR10_MODE_FORCE_2084)
    {
        usHDR10ApplyMaxMasteringLv = GET_HDR10_USER_STEPLESS_FORCE_MODE_MASTERING_LV(enumDisplayRegion);
    }
    else
    {
#if(_HDR10_TONEMAPPING_BY_MAXCLL_SUPPORT == _ON)
        usHDR10ApplyMaxMasteringLv = UserCommonColorHDRGetHDR10MaxDisplayLv(enumDisplayRegion);
#else
        BYTE ucIndex = ScalerSyncDxHDRMetadataIndexMapping(SysRegionGetInputPort(enumDisplayRegion));

        usHDR10ApplyMaxMasteringLv = g_pstSyncHDR10SaticMetadata[ucIndex].usMaxDisplayMasteringLv;
#endif
        if(usHDR10ApplyMaxMasteringLv == 0)
        {
            usHDR10ApplyMaxMasteringLv = GET_HDR10_USER_STEPLESS_MASTERING_LV0(enumDisplayRegion);
        }
    }
    return usHDR10ApplyMaxMasteringLv;
}
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : return applying Advanced HDR10 parameter or not
// Input Value  : EnumDisplayRegion
// Output Value : EnumAdvancedHDR10Status
//--------------------------------------------------
EnumAdvancedHDR10Status UserCommonColorHDRGetAdvancedHDR10Status(EnumDisplayRegion enumDisplayRegion)
{
    if((UserCommonColorHDRCheckAdvancedHDR10SupportDisplayMode() == _ADVANCED_HDR10_DISP_MODE_SUPPORT_ON_DEMO_MODE_OFF) &&
       (GET_ADVANCED_HDR10_PCM_HLW_MODE() == _HLW_KERNEL))
    {
        // HDR10 EOTF should be received in HDR10+ status
        if((GET_HDR10_EOTF_SETTING(enumDisplayRegion) == _HDR_INFO_EOTF_SMPTE_ST_2084) &&
           (GET_ADVANCED_HDR10_SUPPORT() == _ADVANCED_HDR10_SUPPORT_ON))
        {
#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
            if(GET_ADVANCED_HDR10_METADATA_TYPE() == _ADVANDED_HDR10_DHDR_METADATA)
            {
                if(GET_ADVANCED_HDR10_DHDR_DATA_STATUS() == _TRUE)
                {
                    return _ADVANCED_HDR10_ON;
                }
            }
            else
#endif
            {
                if(GET_ADVANCED_HDR10_DELAY_MODE() == _TRUE)
                {
                    if(GET_ADVANCED_HDR10_BACK_UP_INFO_DATA_STATUS() == _TRUE)
                    {
                        return _ADVANCED_HDR10_ON;
                    }
                }
                else
                {
                    if(GET_ADVANCED_HDR10_INFO_DATA_STATUS() == _TRUE)
                    {
                        return _ADVANCED_HDR10_ON;
                    }
                }
            }
        }
    }

    return _ADVANCED_HDR10_OFF;
}

//--------------------------------------------------
// Description  : return applying Advanced HDR10 parameter or not
// Input Value  : EnumDisplayRegion
// Output Value : EnumAdvancedHDR10Status
//--------------------------------------------------
void UserCommonColorAdvancedHDR10VSIFSupportSwitch(void)
{
    EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_1P;
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(SysModeGetDisplayMode() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        enumDisplayRegion = _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
    }
#endif

    if((UserCommonColorHDRCheckAdvancedHDR10SupportDisplayMode() == _ADVANCED_HDR10_DISP_MODE_SUPPORT_ON_DEMO_MODE_OFF) &&
       (UserInterfaceColorHDRGetAdvancedHDR10Enable(enumDisplayRegion) == _ADVANCED_HDR10_SUPPORT_ON))
    {
        SET_ADVANCED_HDR10_METADATA_SUPPORT(_ADVANCED_HDR10_SUPPORT_ON);
    }
    else
    {
        // when Advanced HDR10 metadata support is off, Advanced HDR10 metadata should be clear
        CLR_ADVANCED_HDR10_INFO_DATA();
        CLR_ADVANCED_HDR10_BACK_UP_INFO_DATA();
#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
        CLR_ADVANCED_HDR10_DHDR_DATA();
#endif
        CLR_ADVANCED_HDR10_METADATA_SUPPORT();
    }
}

//--------------------------------------------------
// Description  : return applying Advanced HDR10 parameter or not
// Input Value  : EnumDisplayRegion
// Output Value : EnumAdvancedHDR10Status
//--------------------------------------------------
EnumAdvancedHDR10SupportDisplayMode UserCommonColorHDRCheckAdvancedHDR10SupportDisplayMode(void)
{
    switch(SysModeGetDisplayMode())
    {
        case _DISPLAY_MODE_1P:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
#if(_COLOR_DEMO_FUNCTION == _ON)
            if(UserCommonColorGetDemoModeType() != _DEMO_OFF)
            {
                return _ADVANCED_HDR10_DISP_MODE_SUPPORT_ON_DEMO_MODE_ON;
            }
#endif
            return _ADVANCED_HDR10_DISP_MODE_SUPPORT_ON_DEMO_MODE_OFF;
            break;

        case _DISPLAY_MODE_2P_PIP:
        default:
            break;
    }

    return _ADVANCED_HDR10_DISP_MODE_SUPPORT_OFF;
}

#if(_DEBUG_MESSAGE_HDR == _ON)
//--------------------------------------------------
// Description  : Check Advanced HDR10 change status according to EOTF, (primaries color), max mastering luminance
// Input Value  : EnumDisplayRegion
// Output Value : EnumAdvancedHDR10ChangeStatus
//--------------------------------------------------
EnumAdvancedHDR10ChangeStatus UserCommonColorHDRGetAdvancedHDR10ChangeStatus(void)
{
    if(UserCommonColorHDRCheckAdvancedHDR10SupportDisplayMode() == _ADVANCED_HDR10_DISP_MODE_SUPPORT_ON_DEMO_MODE_OFF)
    {
        if(memcmp(&g_stColorAdvancedHDR10Setting, &g_stSyncAdvancedHDR10Metadata, sizeof(StructAdvancedHDR10MetaData)) != 0)
        {
            memcpy(&g_stColorAdvancedHDR10Setting, &g_stSyncAdvancedHDR10Metadata, sizeof(StructAdvancedHDR10MetaData));
            return _ADVANCED_HDR10_INFO_CHANGE;
        }
    }

    return _ADVANCED_HDR10_INFO_NO_CHANGE;
}
#endif

//--------------------------------------------------
// Description  : Advanced HDR10 Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorAdvancedHDR10InitialSetting(void)
{
    // Initialize global variables
    CLR_ADVANCED_HDR10_METADATA_SUPPORT();
    CLR_ADVANCED_HDR10_BACKUP_METADATA_CHANGE();
    CLR_ADVANCED_HDR10_BACK_UP_INFO_DATA();
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    CLR_ADVANCED_HDR10_MAIN_CPU_IRQ_FLAG();
#endif
#if(_SCPU_SUPPORT == _TRUE)
    CLR_ADVANCED_HDR10_SECOND_CPU_IRQ_FLAG();
#endif
    CLR_ADVANCED_HDR10_NOTIFY_INT();
    CLR_ADVANCED_HDR10_YM_TABLE_READY();
    CLR_ADVANCED_HDR10_COLOR_INITIAL_SETTING();
    CLR_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS();
    CLR_ADVANCED_HDR10_METADATA_REAPPLY();

    // Initialize Metadata & Ymapping Table
    CLR_ADVANCED_HDR10_INFO_DATA();
#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
    CLR_ADVANCED_HDR10_DHDR_DATA();
#endif
#if(_DEBUG_MESSAGE_HDR == _ON)
    CLR_ADVANCED_HDR10_SETTING_DATA();
#endif
    CLR_ADVANCED_HDR10_YM_TABLE();

    ScalerColorAdvancedHDR10PCMHLWDBProc(_ADVANCED_HDR10_PCM_HLW_DB_RESET);
    ScalerColorPCMSetEffectiveRegion(_HLW_INSIDEB_OUTSIDEA, _DB_APPLY_POLLING);

    if(UserCommonColorHDRCheckAdvancedHDR10SupportDisplayMode() != _ADVANCED_HDR10_DISP_MODE_SUPPORT_OFF)
    {
        WORD usHDR10NOTMBoundAddr = _OGC_HDR10_NOTM_BOUND_ADDRESS;
        BYTE pucTemp[2] = {0};

#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
        usHDR10NOTMBoundAddr = UserCommonColorHDRGetHDR10NOTMBoundAddr(GET_HDR10_USER_DEF_PANEL_LV_TYPE(_DISPLAY_RGN_1P));
#endif
        ScalerFlashRead(_OGC_FLASH_BANK, (BYTE *)((((WORD)_OGC_FLASH_PAGE) << 12) + usHDR10NOTMBoundAddr + 2), 2, pucTemp);
        SET_ADVANCED_HDR10_PANEL_MAX_LV(TO_WORD(pucTemp[0], pucTemp[1]));
        SET_ADVANCED_HDR10_METADATA_DETECT_TIME(_ADVANCED_HDR10_NO_METADATA_DEBOUNCE_NUM * (1000 / (GET_INPUT_TIMING_VFREQ() / 10)));
        SET_ADVANCED_HDR10_FRC_STATUS(_ADVANCED_HDR10_FRAME_SYNC);

#if(_FRC_SUPPORT == _ON)
        SET_ADVANCED_HDR10_FRC_STATUS(ScalerFRCGetAdvancedHDR10FRCStatus());
#endif

        UserCommonColorAdvancedHDR10VSIFSupportSwitch();

        SET_ADVANCED_HDR10_SUPPORT(UserInterfaceColorHDRGetAdvancedHDR10Enable(_DISPLAY_RGN_1P));
    }

    SET_ADVANCED_HDR10_INITIAL_READY();
}

//--------------------------------------------------
// Description  : Advanced HDR10 Reset Setting, when display mode change, Hotplug or AC/DC on-off.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorAdvancedHDR10Reset(void)
{
    if(UserCommonColorHDRCheckAdvancedHDR10SupportDisplayMode() != _ADVANCED_HDR10_DISP_MODE_SUPPORT_OFF)
    {
        // Initialize global variables
        CLR_ADVANCED_HDR10_METADATA_SUPPORT();
        CLR_ADVANCED_HDR10_BACKUP_METADATA_CHANGE();
        CLR_ADVANCED_HDR10_BACK_UP_INFO_DATA();
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
        CLR_ADVANCED_HDR10_MAIN_CPU_IRQ_FLAG();
#endif
#if(_SCPU_SUPPORT == _TRUE)
        CLR_ADVANCED_HDR10_SECOND_CPU_IRQ_FLAG();
#endif
        CLR_ADVANCED_HDR10_NOTIFY_INT();
        CLR_ADVANCED_HDR10_YM_TABLE_READY();
        CLR_ADVANCED_HDR10_COLOR_INITIAL_SETTING();
        CLR_ADVANCED_HDR10_PCM_HLW_DB_ERROR_STATUS();
        CLR_ADVANCED_HDR10_METADATA_REAPPLY();

        // Initialize Metadata & Ymapping Table
        CLR_ADVANCED_HDR10_INFO_DATA();
#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
        CLR_ADVANCED_HDR10_DHDR_DATA();
#endif
#if(_DEBUG_MESSAGE_HDR == _ON)
        CLR_ADVANCED_HDR10_SETTING_DATA();
#endif
        CLR_ADVANCED_HDR10_YM_TABLE();

        ScalerColorAdvancedHDR10PCMHLWDBProc(_ADVANCED_HDR10_PCM_HLW_DB_RESET);
    }

    CLR_ADVANCED_HDR10_INITIAL_READY();
    SET_ADVANCED_HDR10_SUPPORT(_ADVANCED_HDR10_SUPPORT_OFF);
}

//--------------------------------------------------
// Description  : Get Advanced HDR10 Enlarge Delay Support
// Input Value  : None
// Output Value : EnumAdvancedHDR10EnlargeDelaySupport
//--------------------------------------------------
EnumAdvancedHDR10EnlargeDelaySupport UserCommonColorAdvancedHDR10GetEnlargeDelaySupport(EnumDisplayRegion enumDisplayRegion)
{
    if((UserCommonColorHDRCheckAdvancedHDR10SupportDisplayMode() != _ADVANCED_HDR10_DISP_MODE_SUPPORT_OFF) &&
       (UserInterfaceColorHDRGetAdvancedHDR10Enable(enumDisplayRegion) == _ADVANCED_HDR10_SUPPORT_ON))
    {
        return _ADVANCED_HDR10_ENLARGE_DELAY_SUPPORT;
    }
    else
    {
        return _ADVANCED_HDR10_ENLARGE_DELAY_NO_SUPPORT;
    }
}
#endif

#if(_HDMI_SBTM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : return applying SBTM parameter or not
// Input Value  : EnumDisplayRegion
// Output Value : EnumAdvancedHDR10Status
//--------------------------------------------------
EnumHDR10SBTMStatus UserCommonColorHDRGetSBTMStatus(EnumDisplayRegion enumDisplayRegion)
{
    if((UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON) &&
       (GET_HDR10_SBTM_MODE(enumDisplayRegion) != _HDR10_SBTM_MODE_OFF))
    {
        return _HDR10_SBTM_ON;
    }
    return _HDR10_SBTM_OFF;
}

//--------------------------------------------------
// Description  : Check HDR10 SBTM change status according to SBTM mode, GRDM LumTye
// Input Value  : EnumDisplayRegion
// Output Value : EnumHDR10SBTMChangeStatus
//--------------------------------------------------
EnumHDR10SBTMChangeStatus UserCommonColorHDRGetSBTMChangeStatus(EnumDisplayRegion enumDisplayRegion)
{
    EnumHDR10SBTMChangeStatus enumHDR10SBTMChangeStatus = _HDR10_SBTM_INFO_NO_CHANGE;
    BYTE ucMaxRegion = SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX);

    // Disable HDR SBTM for 3P/4P modes
    if(ucMaxRegion <= _SBTM_MAX_REGION_COUNT)
    {
        StructHDR10SBTMInfo *pstSBTMMetaData = &g_pstSyncHDR10SBTMMetadata[ScalerSyncDxHDRMetadataIndexMapping(SysRegionGetInputPort(enumDisplayRegion))];

        if(GET_HDR10_SBTM_MODE(enumDisplayRegion) != pstSBTMMetaData->enumHDR10SBTMMode)
        {
            SET_HDR10_SBTM_MODE(enumDisplayRegion, pstSBTMMetaData->enumHDR10SBTMMode);
            enumHDR10SBTMChangeStatus |= _HDR10_SBTM_MODE_CHANGE;
        }
        if(GET_HDR10_SBTM_TYPE(enumDisplayRegion) != pstSBTMMetaData->enumHDR10SBTMType)
        {
            SET_HDR10_SBTM_TYPE(enumDisplayRegion, pstSBTMMetaData->enumHDR10SBTMType);
        }
        if(GET_HDR10_SBTM_MODE(enumDisplayRegion) == _HDR10_SBTM_MODE_G_RDM)
        {
            if(GET_HDR10_SBTM_GRDM_LUM_TYPE(enumDisplayRegion) != pstSBTMMetaData->enumHDR10SBTMGRDMLumMaxType)
            {
                SET_HDR10_SBTM_GRDM_LUM_TYPE(enumDisplayRegion, pstSBTMMetaData->enumHDR10SBTMGRDMLumMaxType);
                enumHDR10SBTMChangeStatus |= _HDR10_SBTM_GRDM_LUM_CHANGE;
            }
            if(GET_HDR10_SBTM_GRDM_MIN_TYPE(enumDisplayRegion) != pstSBTMMetaData->enumHDR10SBTMGRDMMinType)
            {
                SET_HDR10_SBTM_GRDM_MIN_TYPE(enumDisplayRegion, pstSBTMMetaData->enumHDR10SBTMGRDMMinType);
            }
        }
        else if(GET_HDR10_SBTM_MODE(enumDisplayRegion) == _HDR10_SBTM_MODE_D_RDM)
        {
            if(GET_HDR10_SBTM_PBLIMITINT(enumDisplayRegion) != pstSBTMMetaData->usFrmPbLimitInt)
            {
                SET_HDR10_SBTM_PBLIMITINT(enumDisplayRegion, pstSBTMMetaData->usFrmPbLimitInt);
            }
        }
    }
    return enumHDR10SBTMChangeStatus;
}

//--------------------------------------------------
// Description  : Return HDR SBTM Type
// Input Value  : EnumDisplayRegion
// Output Value : EnumHDR10SBTMMode
//--------------------------------------------------
EnumHDR10SBTMMode UserCommonColorHDR10GetSBTMMode(EnumDisplayRegion enumDisplayRegion)
{
    if(UserCommonColorHDRGetHDR10Status(enumDisplayRegion) == _HDR10_ON)
    {
        return GET_HDR10_SBTM_MODE(enumDisplayRegion);
    }
    else
    {
        return _HDR10_SBTM_MODE_OFF;
    }
}

//--------------------------------------------------
// Description  : Return HDR SBTM GRDM Type
// Input Value  : EnumDisplayRegion
// Output Value : EnumHDR10SBTMGRDMLumMaxType
//--------------------------------------------------
EnumHDR10SBTMGRDMLumMaxType UserCommonColorHDR10GetSBTMGRDMLumType(EnumDisplayRegion enumDisplayRegion)
{
    return GET_HDR10_SBTM_GRDM_LUM_TYPE(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Return HDR SBTM GRDM Min Type
// Input Value  : EnumDisplayRegion
// Output Value : EnumHDR10SBTMGRDMMinType
//--------------------------------------------------
EnumHDR10SBTMGRDMMinType UserCommonColorHDR10GetSBTMGRDMMinType(EnumDisplayRegion enumDisplayRegion)
{
    return GET_HDR10_SBTM_GRDM_MIN_TYPE(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Return HDR SBTM Type
// Input Value  : EnumDisplayRegion
// Output Value : EnumHDR10SBTMType
//--------------------------------------------------
EnumHDR10SBTMType UserCommonColorHDR10GetSBTMType(EnumDisplayRegion enumDisplayRegion)
{
    return GET_HDR10_SBTM_TYPE(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Return HDR SBTM PBLimit
// Input Value  : EnumDisplayRegion
// Output Value : WORD
//--------------------------------------------------
WORD UserCommonColorHDR10GetSBTMPBLIMITINT(EnumDisplayRegion enumDisplayRegion)
{
    return GET_HDR10_SBTM_PBLIMITINT(enumDisplayRegion);
}

#endif
#if(_HLG_SUPPORT == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorHDRHLGUserModeAdjust(EnumSelRegion enumSelRegion)
{
    StructColorYmappingSetting stYmapping = {0};

    UserCommonColorGetYmappingData(enumSelRegion, &stYmapping);

    ScalerColorIPYmappingAdjust(enumSelRegion, &stYmapping);
}
#endif
#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)
