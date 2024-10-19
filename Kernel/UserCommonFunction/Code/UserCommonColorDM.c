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
// ID Code      : UserCommonColorDM.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DM__

#include "UserCommonInclude.h"
#include "ColorDM/UserCommonColorDM.h"

#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
#if(_DM_DEMO_FUNCTION == _ON)
#warning "DM Demo Function should be _OFF in MP FW!!!"
#endif
#if(_DM_CUSTOM_COLOR_SUPPORT == _ON)
#warning "NOTE: DM Custom Color Must Be Confirmed by Customer and Dolby"
#endif
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DM_FUNCTION == _ON)
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
#if(_DM_DEMO_FUNCTION == _ON)
BYTE g_ucColorDMDemoFuncTimer = 0x00;
#endif
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : DM Mute Proc
// Input Value  : Display Region, Enable Mute or Disable Mute
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMMuteProc(EnumDisplayRegion enumDisplayRegion, bit bEn)
{
    if(bEn == _ENABLE)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        ScalerDDomainBackgroundEnable(ScalerRegionGetDDomainRegion(enumDisplayRegion), _ENABLE);

        // if local dimming is enable, use IPG to force data to black
#if(_LOCAL_DIMMING_FUNCTION == _ON)
        if(ScalerColorLDBLModelGetEnableStatus() == _TRUE)
        {
            ScalerIDomainPatternGenEnable(ScalerRegionGetInputDataPath(enumDisplayRegion), _ENABLE);
        }
#endif
    }
    else
    {
#if(_LOCAL_DIMMING_FUNCTION == _ON)
        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, ScalerRegionGetInputDataPath(enumDisplayRegion));
        ScalerIDomainPatternGenEnable(ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);
#endif
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        ScalerDDomainBackgroundEnable(ScalerRegionGetDDomainRegion(enumDisplayRegion), _DISABLE);
    }
}

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
//--------------------------------------------------
// Description  : Clear DM Metadata Info
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMClearMetadata(EnumRegionIndex enumRegionIndex)
{
    SET_DM_INPUT_STATUS_INDEX(enumRegionIndex, _DM_OFF);

    // Initialize Metadata
    CLR_DM_VSIF_INFO_DATA_INDEX(enumRegionIndex);
    CLR_DM_SDP_INFO_DATA_INDEX(enumRegionIndex);
    CLR_DM_EMP_INFO_DATA_INDEX(enumRegionIndex);
    CLR_DM_DRAM_INFO_DATA_INDEX(enumRegionIndex);

    // Clear Metadata chage flag
    CLR_DM_METADATA_CHANGE_VSIF_INDEX(enumRegionIndex);
    CLR_DM_METADATA_CHANGE_EMP_INDEX(enumRegionIndex);
    CLR_DM_METADATA_CHANGE_SDP_INDEX(enumRegionIndex);
    CLR_DM_METADATA_CHANGE_HDMI_DRAM_INDEX(enumRegionIndex);
    CLR_DM_METADATA_CHANGE_DP_DRAM_INDEX(enumRegionIndex);

    // Clear Metadata type
    CLR_DM_METADATA_TYPE(enumRegionIndex);

    // Clear Metadata status flag
    CLR_DM_METADATA_MISS_CNT_INDEX(enumRegionIndex);
    CLR_DM_METADATA_ERROR_INDEX(enumRegionIndex);

    // Clear Metadata Addr
    CLR_DM_METADATA_ADDR_INDEX(enumRegionIndex);
}

//--------------------------------------------------
// Description  : DM Initial Setting
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMInitialSetting(EnumDisplayRegion enumDisplayRegion)
{
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
    {
        return;
    }
#endif

    if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
    {
        return;
    }

    // Disable DM HW
    ScalerDMDisable(enumInputDataPath);

    CLR_DM_INITIAL_READY_INDEX(enumRegionIndex);

    // Reset BEC(TR9) to stand by
    SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_INIT);

    // Reset DM mute status
    SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_NO_MUTE);

    // Reset OSD Change flag
    CLR_DM_OSD_CHANGE_INDEX(enumRegionIndex);

    // Disable Metadata Support
    CLR_DM_METADATA_SUPPORT_INDEX(enumRegionIndex);
    CLR_DM_DRAM_SUPPORT_INDEX(enumRegionIndex);

    // Clear Metadata
    UserCommonColorDMClearMetadata(enumRegionIndex);

    // Update Port Status
    SET_DM_PORT_INDEX(enumRegionIndex, SysRegionGetInputPort(enumDisplayRegion));

#if(_LOCAL_DIMMING_FUNCTION == _ON)
    // Set IPG color for forcing black data
    if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace(GET_DM_PORT_INDEX(enumRegionIndex))) == _TRUE)
    {
        ScalerIDomainPatternGenAdjustColor(enumInputDataPath, 0x00, 0x00, 0x00);
    }
    else
    {
        ScalerIDomainPatternGenAdjustColor(enumInputDataPath, 0x80, 0x00, 0x80);
    }
#endif

    // Get OSD Data
    UserCommonColorDMGetData(UserCommonModeDisplaySettingGetSelRegion(enumDisplayRegion), &(g_pstDMSettingInfo[enumRegionIndex].stDMOSDColorSetting));
#if(_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE)
    SET_DM_BACKUP_NORMAL_MODE_INDEX(enumRegionIndex, GET_DM_PICTURE_MODE_INDEX(enumRegionIndex));
#endif

    // IRQ -> ON
    if(UserCommonColorDMGetEnableStatus(enumDisplayRegion) == _DM_SUPPORT_ON)
    {
        UserCommonColorDMIRQSupportSwitch(enumDisplayRegion, _ENABLE);
    }
    else
    {
        UserCommonColorDMIRQSupportSwitch(enumDisplayRegion, _DISABLE);
    }

    SET_DM_INITIAL_READY_INDEX(enumRegionIndex);

    ScalerDMInitial();

    DebugMessageDM("DM Initial Setting Done", GET_DM_INITIAL_READY_INDEX(enumRegionIndex));

    // Check DM Metadata Receive & BEC Status
    UserCommonColorDMActiveProc(enumDisplayRegion, _DM_CHK_INIT);
}

//--------------------------------------------------
// Description  : DM Reset Setting, when display mode change, Hotplug or AC/DC on-off.
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMReset(EnumDisplayRegion enumDisplayRegion)
{
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
    {
        return;
    }

    DebugMessageDM("UserCommonColorDMReset", enumDisplayRegion);

    if(UserCommonColorDMGetEnableStatus(enumDisplayRegion) == _DM_SUPPORT_ON)
    {
        // Disable Interrupt
        ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_DM, ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);

        // Disable Flag for Interface
        ScalerSyncDMSetSupport(GET_DM_PORT_INDEX(enumRegionIndex), _DM_SUPPORT_OFF);

        // Reset BEC(TR9) to stand by
        SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_INIT);

        // Reset OSD Change flag
        CLR_DM_OSD_CHANGE_INDEX(enumRegionIndex);

        // Disable Metadata Support
        CLR_DM_METADATA_SUPPORT_INDEX(enumRegionIndex);
        CLR_DM_DRAM_SUPPORT_INDEX(enumRegionIndex);

        // Clear Metadata
        UserCommonColorDMClearMetadata(enumRegionIndex);

        // Disable DM HW
        ScalerDMDisable(ScalerRegionGetInputDataPath(enumDisplayRegion));

#if(_DM_DEMO_FUNCTION == _ON)
        if(GET_RGN_MAX_DISPLAY_REGION() == 2)
        {
            if(((enumRegionIndex == _REGION_INDEX_0) && (UserCommonColorDMGetDMStatus(SysRegionGetDisplayRegion(_REGION_INDEX_1)) == _FALSE)) ||
               (((enumRegionIndex == _REGION_INDEX_1) && (UserCommonColorDMGetDMStatus(SysRegionGetDisplayRegion(_REGION_INDEX_0)) == _FALSE))))
            {
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_DM_DEMO_FUNCTION);
            }
        }
        else
        {
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_DM_DEMO_FUNCTION);
        }
#endif
    }

    CLR_DM_INITIAL_READY_INDEX(enumRegionIndex);
    CLR_DM_PORT_INDEX(enumRegionIndex);
    CLR_DM_MAIN_SUB_SYNC();
    // Reset HDRTargrtStatus
    SET_HDR_TARGET_STATUS(enumDisplayRegion, _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR);

    // Reset DM mute status
    SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_NO_MUTE);
    CLR_DM_UNMUTE_FRAME_CNT_INDEX(enumRegionIndex);
    CLR_DM_UNMUTE_MAINLOOP_CNT_INDEX(enumRegionIndex);
    CLR_DM_HW_DISABLE_FLAG_INDEX(enumRegionIndex);
}

//--------------------------------------------------
// Description  : DM reset process for muti Display Region
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMResetProc(void)
{
    // Disable Interrupt
    ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_DM, _INPUT_PATH_M1_M2_S1_S2, _DISABLE);

    // Reset Flag for Interface
    memset(&g_stSyncDMSupportInfo, 0, sizeof(g_stSyncDMSupportInfo));

    memset(&g_pstDMSettingInfo, 0, sizeof(g_pstDMSettingInfo));

    // Reset HDRTargrtStatus
    memset(&g_penumColorHDRTargrtStatus, 0, sizeof(g_penumColorHDRTargrtStatus));

    CLR_DM_MAIN_SUB_SYNC();

    CLR_DM_VSIF_INFO_DATA_INDEX(_REGION_INDEX_0);
    CLR_DM_SDP_INFO_DATA_INDEX(_REGION_INDEX_0);
    CLR_DM_EMP_INFO_DATA_INDEX(_REGION_INDEX_0);
    CLR_DM_DRAM_INFO_DATA_INDEX(_REGION_INDEX_0);

    CLR_DM_VSIF_INFO_DATA_INDEX(_REGION_INDEX_1);
    CLR_DM_SDP_INFO_DATA_INDEX(_REGION_INDEX_1);
    CLR_DM_EMP_INFO_DATA_INDEX(_REGION_INDEX_1);
    CLR_DM_DRAM_INFO_DATA_INDEX(_REGION_INDEX_1);

    // Disable DM HW
    ScalerDMDisable(_INPUT_PATH_M1_M2_S1_S2);

#if(_DM_DEMO_FUNCTION == _ON)
    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_DM_DEMO_FUNCTION);
#endif

    DebugMessageDM("DM Reset Proc Done", 0);
}

//--------------------------------------------------
// Description  : DM Handler
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMHandler(EnumDisplayRegion enumDisplayRegion)
{
    if(GET_ON_LINE_CALIBRATION_STATUS() != _CALIBRATION_ON)
    {
        EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

        if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
        {
            return;
        }

        // DM Active Process
        UserCommonColorDMActiveProc(enumDisplayRegion, _DM_CHK_DSP);

        // DM Unmute Process
        if((GET_DM_UNMUTE_MAINLOOP_CNT_INDEX(enumRegionIndex) == _DM_UNMUTE_WAIT_MAINLOOP_CNT) &&
           (GET_DM_UNMUTE_FRAME_CNT_INDEX(enumRegionIndex) == _DM_UNMUTE_WAIT_FRAME_CNT))
        {
            if((GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_OUT_UNMUTE_READY) ||
               (GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_IN_UNMUTE_READY))
            {
                // Do unmute
                if(((GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_OUT_UNMUTE_READY) &&
                    (GET_DM_INPUT_STATUS_INDEX(enumRegionIndex) == _DM_OFF)) ||
                   (GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_IN_UNMUTE_READY))
                {
                    if(UserCommonColorDMGetDMStatus(enumDisplayRegion) == _TRUE)
                    {
                        // DM OSD Entry Event (Activate Show Logo)
                        UserInterfaceColorDMSetOsdEvent(enumDisplayRegion, _DM_OSD_ENTRY);
                    }

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
                    SET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET();
                    SET_DIGITAL_COLOR_INFO_CHANGE_RESET();
                    ScalerGlobalDoubleBufferEnable(ScalerRegionGetInputDataPath(enumDisplayRegion), _ENABLE);
                    ScalerGlobalIDDomainDBApply(ScalerRegionGetInputDataPath(enumDisplayRegion), _DB_APPLY_POLLING);
#endif

                    SET_DM_UNMUTE_FLAG_INDEX(enumRegionIndex);
                    DebugMessageDM("DM Unmute", 0);
                }
                SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_NO_MUTE);
                CLR_DM_UNMUTE_MAINLOOP_CNT_INDEX(enumRegionIndex);
            }
        }
    }
}

//--------------------------------------------------
// Description  : DM Active Process
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMActiveProc(EnumDisplayRegion enumDisplayRegion, EnumDMCheckPoint enumDMCheckPoint)
{
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    // in EagleSight, Sub don't have to do DM Proc itself
    if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
    {
        return;
    }
#endif

    if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
    {
        return;
    }

    // Check DM Metadata Receive & BEC Status
    if((GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) != _DM_OUT_MUTE) && (GET_DM_BEC_STATUS_INDEX(enumRegionIndex) != _DM_BEC_INIT))
    {
        bit bPolling = (enumDMCheckPoint == _DM_CHK_DSP) ? (_FALSE) : (_TRUE);

        DebugMessageDM("DM Active Proc", enumDMCheckPoint);

        // check BEC finish
        if(((bPolling == _FALSE) && (GET_DM_BEC_STATUS_INDEX(enumRegionIndex) == _DM_BEC_DONE)) ||
           ((bPolling == _TRUE) && (UserCommonColorDMPollingBECStatus(enumRegionIndex, _DM_POLLING_BEC_TIMEOUT, _DM_BEC_DONE) == _TRUE)))
        {
            StructHDRStatusInfo stHDRStatusInfo = {0};

            DebugMessageDM("DM BEC Done", GET_DM_BEC_STATUS_INDEX(enumRegionIndex));

#if(_DM_DEMO_FUNCTION == _ON)
            // Activate Demo Function Timer
            ScalerTimerActiveTimerEvent(_DM_DEMO_FUNCTION_TIME_UNIT, _SYSTEM_TIMER_EVENT_DM_DEMO_FUNCTION);
#endif

            // update HDR target status
            UserCommonColorHDRGetTargetStatus(enumDisplayRegion, &stHDRStatusInfo);
            CLR_DM_HW_DISABLE_FLAG_INDEX(enumRegionIndex);

            if((stHDRStatusInfo.enumHDRTargetStatus != _HDR_TARGET_STATUS_DM) && (stHDRStatusInfo.enumHDRTargetStatus != _HDR_TARGET_STATUS_DM_GAME))
            {
                SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_INIT);
                return;
            }

            // if check in inital setting, apply I-DB (DM HW effective)
            if(enumDMCheckPoint == _DM_CHK_INIT)
            {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) && (GET_DM_MAIN_SUB_SYNC() == _TRUE))
                {
                    ScalerGlobalIDomainDBApply(ScalerRegionGetInputDataPath(_DISPLAY_RGN_EAGLE_SIGHT_SUB), _DB_APPLY_NO_POLLING);
                    ScalerGlobalIDomainDBApply(ScalerRegionGetInputDataPath(_DISPLAY_RGN_EAGLE_SIGHT_MAIN), _DB_APPLY_POLLING);
                }
                else
#endif
                {
                    ScalerGlobalIDomainDBApply(ScalerRegionGetInputDataPath(enumDisplayRegion), _DB_APPLY_POLLING);
                }
            }

            DebugMessageDM("DM Target Status New", stHDRStatusInfo.enumHDRTargetStatus);
            DebugMessageDM("DM Target Status Prev", GET_HDR_TARGET_STATUS(enumDisplayRegion));

            // if HDR target status change
            if(stHDRStatusInfo.enumHDRTargetStatus != GET_HDR_TARGET_STATUS(enumDisplayRegion))
            {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) && (GET_DM_MAIN_SUB_SYNC() == _TRUE))
                {
                    SET_HDR_TARGET_STATUS(_DISPLAY_RGN_EAGLE_SIGHT_MAIN, stHDRStatusInfo.enumHDRTargetStatus);
                    SET_HDR_TARGET_STATUS(_DISPLAY_RGN_EAGLE_SIGHT_SUB, stHDRStatusInfo.enumHDRTargetStatus);

                    // Update OSD DM Picture Mode to align with newest kernel status
                    UserInterfaceColorDMUpdatePictureMode(_DISPLAY_RGN_EAGLE_SIGHT_MAIN, GET_DM_PICTURE_MODE_INDEX(ScalerRegionGetIndex(_DISPLAY_RGN_EAGLE_SIGHT_MAIN)));
                    UserInterfaceColorDMUpdatePictureMode(_DISPLAY_RGN_EAGLE_SIGHT_SUB, GET_DM_PICTURE_MODE_INDEX(ScalerRegionGetIndex(_DISPLAY_RGN_EAGLE_SIGHT_MAIN)));

                    // Overwrite other Color IP setting when not in initial setting
                    if(enumDMCheckPoint != _DM_CHK_INIT)
                    {
                        UserCommonColorDMAdjustDMProc(_DISPLAY_RGN_EAGLE_SIGHT_MAIN, _DM_ADJUST_DM_AND_COLOR);
                        UserCommonColorDMAdjustDMProc(_DISPLAY_RGN_EAGLE_SIGHT_SUB, _DM_ADJUST_DM_AND_COLOR);
                    }
                }
                else
#endif
                {
                    SET_HDR_TARGET_STATUS(enumDisplayRegion, stHDRStatusInfo.enumHDRTargetStatus);

                    // Update OSD DM Picture Mode to align with newest kernel status
                    UserInterfaceColorDMUpdatePictureMode(enumDisplayRegion, GET_DM_PICTURE_MODE_INDEX(enumRegionIndex));

                    // Overwrite other Color IP setting when not in initial setting
                    if(enumDMCheckPoint != _DM_CHK_INIT)
                    {
                        UserCommonColorDMAdjustDMProc(enumDisplayRegion, _DM_ADJUST_DM_AND_COLOR);
                    }
                }

                // DM unmute process
                if(GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_IN_MUTE)
                {
                    // if during display, DM have to do unmute itself
                    if(enumDMCheckPoint == _DM_CHK_DSP)
                    {
                        SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_IN_UNMUTE_READY);
                        CLR_DM_UNMUTE_MAINLOOP_CNT_INDEX(enumRegionIndex);
                    }
                    // before display, the unmute process depends on user unmute process
                    else
                    {
                        // DM OSD Entry Event (Activate Show Logo)
                        UserInterfaceColorDMSetOsdEvent(enumDisplayRegion, _DM_OSD_ENTRY);

#if(_LOCAL_DIMMING_FUNCTION == _ON)
                        ScalerIDomainPatternGenEnable(ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);
#endif

                        SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_NO_MUTE);
                    }
                }

                SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_INIT);

                DebugMessageDM("DM_HDR_Target_Status No Change", stHDRStatusInfo.enumHDRTargetStatus);
            }
            // if HDR target status doesn't change
            else
            {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
                if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) && (GET_DM_MAIN_SUB_SYNC() == _TRUE))
                {
                    // Update OSD DM Picture Mode to align with newest kernel status
                    UserInterfaceColorDMUpdatePictureMode(_DISPLAY_RGN_EAGLE_SIGHT_MAIN, GET_DM_PICTURE_MODE_INDEX(ScalerRegionGetIndex(_DISPLAY_RGN_EAGLE_SIGHT_MAIN)));
                    UserInterfaceColorDMUpdatePictureMode(_DISPLAY_RGN_EAGLE_SIGHT_SUB, GET_DM_PICTURE_MODE_INDEX(ScalerRegionGetIndex(_DISPLAY_RGN_EAGLE_SIGHT_MAIN)));

                    // I-DB Apply for DM HW
                    ScalerGlobalIDomainDBApply((ScalerRegionGetInputDataPath(_DISPLAY_RGN_EAGLE_SIGHT_MAIN)) | (ScalerRegionGetInputDataPath(_DISPLAY_RGN_EAGLE_SIGHT_SUB)), _DB_APPLY_POLLING);

                    SET_DM_BEC_STATUS_INDEX(_REGION_INDEX_0, _DM_BEC_INIT);
                }
                else
#endif
                {
                    // Update OSD DM Picture Mode to align with newest kernel status
                    UserInterfaceColorDMUpdatePictureMode(enumDisplayRegion, GET_DM_PICTURE_MODE_INDEX(enumRegionIndex));

                    // I-DB Apply for DM HW
                    ScalerGlobalIDomainDBApply(ScalerRegionGetInputDataPath(enumDisplayRegion), _DB_APPLY_POLLING);

                    // DM unmute process
                    if(GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_IN_MUTE)
                    {
                        // if during display, DM have to do unmute itself
                        if(enumDMCheckPoint == _DM_CHK_DSP)
                        {
                            SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_IN_UNMUTE_READY);
                            CLR_DM_UNMUTE_MAINLOOP_CNT_INDEX(enumRegionIndex);
                        }
                        // before display, the unmute process depends on user unmute process
                        else
                        {
                            // DM OSD Entry Event (Activate Show Logo)
                            UserInterfaceColorDMSetOsdEvent(enumDisplayRegion, _DM_OSD_ENTRY);

#if(_LOCAL_DIMMING_FUNCTION == _ON)
                            ScalerIDomainPatternGenEnable(ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);
#endif

                            SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_NO_MUTE);
                        }
                    }

                    SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_INIT);
                }
            }

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) && (GET_DM_MAIN_SUB_SYNC() == _TRUE))
            {
                DebugMessageDM("Eagle Sight Main/Sub Finish", GET_DM_MAIN_SUB_SYNC());

                // copy main setting to sub
                ScalerDMSyncMainSubData();

                // turn off main/sub sync
                CLR_DM_MAIN_SUB_SYNC();
            }
#endif
            // unmute flow for prevent mishaps or unexpected mute status
            if(GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) != _DM_NO_MUTE)
            {
                // if during display, DM have to do unmute itself
                if(enumDMCheckPoint == _DM_CHK_DSP)
                {
                    SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_IN_UNMUTE_READY);
                    CLR_DM_UNMUTE_MAINLOOP_CNT_INDEX(enumRegionIndex);
                }
                // before display, the unmute process depends on user unmute process
                else
                {
                    // DM OSD Entry Event (Activate Show Logo)
                    UserInterfaceColorDMSetOsdEvent(enumDisplayRegion, _DM_OSD_ENTRY);

#if(_LOCAL_DIMMING_FUNCTION == _ON)
                    ScalerIDomainPatternGenEnable(ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);
#endif

                    SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_NO_MUTE);
                }
            }
        }
    }
    else if(GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_OUT_MUTE)
    {
        DebugMessageDM("DM Out Detected!!", enumDisplayRegion);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) && (GET_DM_MAIN_SUB_SYNC() == _TRUE))
        {
            // turn off main/sub sync
            CLR_DM_MAIN_SUB_SYNC();

            // Reset OSD Change flag
            CLR_DM_OSD_CHANGE_INDEX(_REGION_INDEX_0);
            CLR_DM_OSD_CHANGE_INDEX(_REGION_INDEX_1);

            // check if out DM caused by wrong metadata
            if(GET_DM_METADATA_ERROR_INDEX(_REGION_INDEX_0) == _FALSE)
            {
                // Clear Metadata
                UserCommonColorDMClearMetadata(_REGION_INDEX_0);
                UserCommonColorDMClearMetadata(_REGION_INDEX_1);
            }

            // Set Eagle Sight Sub to _DM_OUT_MUTE for UserCommonColorHDRAdjustHDRMode
            SET_DM_MUTE_STATUS_INDEX(_REGION_INDEX_1, _DM_OUT_MUTE);

            // Reset BEC Status
            SET_DM_BEC_STATUS_INDEX(_REGION_INDEX_0, _DM_BEC_INIT);

            // Disable DM HW
            ScalerDMDisable(ScalerRegionGetInputDataPath(_DISPLAY_RGN_EAGLE_SIGHT_MAIN) | ScalerRegionGetInputDataPath(_DISPLAY_RGN_EAGLE_SIGHT_SUB));
            SET_DM_HW_DISABLE_FLAG_INDEX(_REGION_INDEX_0);
            SET_DM_HW_DISABLE_FLAG_INDEX(_REGION_INDEX_1);

#if(_DM_DEMO_FUNCTION == _ON)
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_DM_DEMO_FUNCTION);
#endif
        }
        else
#endif
        {
            // Reset OSD Change flag
            CLR_DM_OSD_CHANGE_INDEX(enumRegionIndex);

            // check if out DM caused by wrong metadata
            if(GET_DM_METADATA_ERROR_INDEX(enumRegionIndex) == _FALSE)
            {
                // Clear Metadata
                UserCommonColorDMClearMetadata(enumRegionIndex);
            }

            // Reset BEC Status
            SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_INIT);

            // Disable DM HW
            ScalerDMDisable(ScalerRegionGetInputDataPath(enumDisplayRegion));
            SET_DM_HW_DISABLE_FLAG_INDEX(enumRegionIndex);

#if(_DM_DEMO_FUNCTION == _ON)
            if(GET_RGN_MAX_DISPLAY_REGION() == 2)
            {
                if(((enumRegionIndex == _REGION_INDEX_0) && (UserCommonColorDMGetDMStatus(SysRegionGetDisplayRegion(_REGION_INDEX_1)) == _FALSE)) ||
                   (((enumRegionIndex == _REGION_INDEX_1) && (UserCommonColorDMGetDMStatus(SysRegionGetDisplayRegion(_REGION_INDEX_0)) == _FALSE))))
                {
                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_DM_DEMO_FUNCTION);
                }
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_DM_DEMO_FUNCTION);
            }
#endif
        }

        // OSD Exit Event
        UserInterfaceColorDMSetOsdEvent(enumDisplayRegion, _DM_OSD_EXIT);

        // force update HDR data
        ScalerSyncUpdateSecData(GET_DM_PORT_INDEX(enumRegionIndex), enumDisplayRegion, _HDR_INFO_CHG_POLLING_CHECK_DISABLE);
    }
    else if((GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_OUT_UNMUTE_READY) ||
            (GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_IN_UNMUTE_READY))
    {
        if(GET_DM_UNMUTE_MAINLOOP_CNT_INDEX(enumRegionIndex) < _DM_UNMUTE_WAIT_MAINLOOP_CNT)
        {
            SET_DM_UNMUTE_MAINLOOP_CNT_INDEX(enumRegionIndex, GET_DM_UNMUTE_MAINLOOP_CNT_INDEX(enumRegionIndex) + 0x01);
        }
    }
}

//--------------------------------------------------
// Description  : Switch DM Metadata support
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMIRQSupportSwitch(EnumDisplayRegion enumDisplayRegion, bit bEn)
{
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
    {
        return;
    }

    if(bEn == _ENABLE)
    {
        DebugMessageDM("DM IRQ Support Enable", enumDisplayRegion);

        // Tell Interface DM IRQ is ON
        ScalerSyncDMSetSupport(GET_DM_PORT_INDEX(enumRegionIndex), _DM_SUPPORT_ON);

        // Metadata IRQ -> ON
        SET_DM_METADATA_SUPPORT_INDEX(enumRegionIndex, _DM_SUPPORT_ON);

        // I_den_start IRQ -> ON
        SET_DM_DRAM_SUPPORT_INDEX(enumRegionIndex, _DM_SUPPORT_ON);
        ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_DM, ScalerRegionGetInputDataPath(enumDisplayRegion), _ENABLE);
    }
    else
    {
        DebugMessageDM("DM IRQ Support Disable", enumDisplayRegion);

        // Tell Interface DM IRQ is OFF
        ScalerSyncDMSetSupport(GET_DM_PORT_INDEX(enumRegionIndex), _DM_SUPPORT_OFF);

        // Metadata IRQ -> OFF
        CLR_DM_METADATA_SUPPORT_INDEX(enumRegionIndex);

        // I_den_start IRQ -> OFF
        CLR_DM_DRAM_SUPPORT_INDEX(enumRegionIndex);
        ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_DM, ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);

        // clear metadata
        UserCommonColorDMClearMetadata(enumRegionIndex);
    }
}

//--------------------------------------------------
// Description  : Check User Enable Status & Supported Display Mode
// Input Value  : EnumDisplayRegion
// Output Value : EnumDMSupport
//--------------------------------------------------
EnumDMSupport UserCommonColorDMGetEnableStatus(EnumDisplayRegion enumDisplayRegion)
{
    // Check User Status
    if(UserInterfaceColorDMGetEnableStatus(enumDisplayRegion) == _DM_SUPPORT_OFF)
    {
        DebugMessageDM("DM Disable for User Setting", 0);
        return _DM_SUPPORT_OFF;
    }

    // Check Display Count
    if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX) > _DM_MAX_REGION_COUNT)
    {
        DebugMessageDM("DM Disable for Over 2P", 0);
        return _DM_SUPPORT_OFF;
    }

    // Interlace Mode NOT Support
    if((SysRegionCheckDisplayEvent(enumDisplayRegion, _DISPLAY_EVENT_TIMING_CONFIRMED) == _TRUE) && (g_pstMeasureRegionTimingInfo[SysRegionGetDisplayRegionIndex(enumDisplayRegion)].stTimingInfo.b1Interlace == _TRUE))
    {
        DebugMessageDM("DM Disable for Interlace Mode", 0);
        return _DM_SUPPORT_OFF;
    }

    // Check Display Mode
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        switch(GET_DISPLAY_MODE())
        {
            case _DISPLAY_MODE_1P:
                return _DM_SUPPORT_ON;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                return (_DM_FB_EAGLE_SIGHT_SUPPORT == _ON) ? _DM_SUPPORT_ON : _DM_SUPPORT_OFF;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PBP_TB:
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PIP:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
            case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#endif
#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_3P_FLAG:
#endif
#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_3P_SKEW_L:
            case _DISPLAY_MODE_3P_SKEW_R:
#endif
#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_3P_SKEW_T:
            case _DISPLAY_MODE_3P_SKEW_B:
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_4P:
#endif
            case _DISPLAY_MODE_NONE:
                DebugMessageDM("DM Disable for Un-supported Display Mode", GET_DISPLAY_MODE());
                return _DM_SUPPORT_OFF;

            default:
                return _DM_SUPPORT_OFF;
        }
    }
    else
    {
        return _DM_SUPPORT_ON;
    }
}

//--------------------------------------------------
// Description  : Parser OSD data for color adjust and DM source code
// Input Value  : enumSelRegion
// Output Value : if adjust success
//--------------------------------------------------
bit UserCommonColorDMOSDAdjust(EnumSelRegion enumSelRegion, EnumDMAdjustType enumAdjustType)
{
    EnumDisplayRegion enumDisplayRegion = UserCommonColorDMGetDisplayRegion(enumSelRegion);
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
    {
        return _FALSE;
    }

    // Only adjust when Dolby is ON
    if(UserCommonColorDMGetDMStatus(enumDisplayRegion) == _FALSE)
    {
        return _FALSE;
    }

    if((GET_DM_BEC_STATUS_INDEX(enumRegionIndex) == _DM_BEC_INIT) && (GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_NO_MUTE))
    {
        bit bBecPolling = _FALSE;
        DebugMessageDM("DM OSD Adjust", enumRegionIndex);

        UserCommonColorDMGetData(enumSelRegion, &(g_pstDMSettingInfo[enumRegionIndex].stDMOSDColorSetting));
#if(_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE)
        SET_DM_BACKUP_NORMAL_MODE_INDEX(enumRegionIndex, GET_DM_PICTURE_MODE_INDEX(enumRegionIndex));
#endif

        // DM HW issue
        // if Display Region 1P or Eagle Sight Main, use B05 DB to change DM param
        // if Multi P or Eagle Sight Sub, use FRC freeze to prevent garbage
        if(enumDisplayRegion == _DISPLAY_RGN_1P) // B05 DB
        {
            ScalerDMB05DoubleBufferEnable(enumDisplayRegion, _ENABLE);
        }
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        else if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) // B05 DB
        {
            ScalerDMB05DoubleBufferEnable(enumDisplayRegion, _ENABLE);
        }
#endif
#if(_FRC_SUPPORT == _ON)
        else // FRC Freeze
        {
            ScalerFRCFixSlowSideBlkSel(enumInputDataPath, _ENABLE);
            ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, enumInputDataPath);
        }
#endif

        SET_DM_OSD_CHANGE_INDEX(enumRegionIndex);
        SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_BUSY); // signal TR9 to run BEC

        if(UserCommonColorDMPollingBECStatus(enumRegionIndex, _DM_POLLING_BEC_TIMEOUT, _DM_BEC_DONE) == _TRUE)
        {
            DebugMessageDM("DM OSD BEC Done", enumRegionIndex);

            UserCommonColorDMAdjust(enumDisplayRegion, enumRegionIndex, enumAdjustType);
            CLR_DM_OSD_CHANGE_INDEX(enumRegionIndex);
            SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_INIT);

            bBecPolling = _TRUE;
        }
        else // not supposed to enter this condition
        {
            CLR_DM_OSD_CHANGE_INDEX(enumRegionIndex);
            SET_DM_BEC_STATUS_INDEX(enumRegionIndex, _DM_BEC_INIT);

            if(ScalerDMStatusChange(enumDisplayRegion) == _TRUE)
            {
                UserCommonColorDMMuteProc(enumDisplayRegion, _DISABLE);
                SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_NO_MUTE);
            }

            DebugMessageDM("DM OSDAdjust TimeOut", 0);

            bBecPolling = _FALSE;
        }

        // Disable B05 DB or FRC Freeze
        if(enumDisplayRegion == _DISPLAY_RGN_1P) // B05 DB
        {
            ScalerDMB05DoubleBufferEnable(enumDisplayRegion, _DISABLE);
        }
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        else if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN) // B05 DB
        {
            ScalerDMB05DoubleBufferEnable(enumDisplayRegion, _DISABLE);
        }
#endif
#if(_FRC_SUPPORT == _ON)
        else // FRC Freeze
        {
            ScalerFRCFixSlowSideBlkSel(enumInputDataPath, _DISABLE);
        }
#endif

        return bBecPolling;
    }
    else // not supposed to enter this condition
    {
        DebugMessageDM("DM BEC Not INIT", GET_DM_BEC_STATUS_INDEX(enumRegionIndex));
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DM color adjust
// Input Value  : EnumSelRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMAdjust(EnumDisplayRegion enumDisplayRegion, EnumRegionIndex enumRegionIndex, EnumDMAdjustType enumAdjustType)
{
    if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
    {
        return;
    }

    StructHDRStatusInfo stHDRStatusInfo = {0};

    // update HDR target status
    UserCommonColorHDRGetTargetStatus(enumDisplayRegion, &stHDRStatusInfo);
    SET_HDR_TARGET_STATUS(enumDisplayRegion, stHDRStatusInfo.enumHDRTargetStatus);

    UserCommonColorDMAdjustDMProc(enumDisplayRegion, enumAdjustType);

    // OSD out Game flow
    if(GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_OSD_MUTE)
    {
        UserCommonColorDMMuteProc(enumDisplayRegion, _DISABLE);
        SET_DM_MUTE_STATUS_INDEX(enumRegionIndex, _DM_NO_MUTE);
    }
}

//--------------------------------------------------
// Description  : User Common function Adjust for DM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMGetData(EnumSelRegion enumSelRegion, StructColorDMOsdSetting *pstDMOsdData)
{
    memset(pstDMOsdData, 0, sizeof(StructColorDMOsdSetting));
    UserInterfaceColorDMGetData(enumSelRegion, &(pstDMOsdData->stDMOsdSetting));
}

#if(_DM_CONFIG_GAME_MODE_INDEX != _DM_PICTURE_MODE_NONE)
//--------------------------------------------------
// Description  : User Common function Adjust for DM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMSetBackupMode(EnumDisplayRegion enumDisplayRegion, BYTE ucPictureModeIndex)
{
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
    {
        return;
    }

    SET_DM_BACKUP_NORMAL_MODE_INDEX(enumRegionIndex, ucPictureModeIndex);
}
#endif

//--------------------------------------------------
// Description  : Get DM Mute Status
// Input Value  : Display Region
// Output Value : True: Mute, False: No mute
//--------------------------------------------------
bit UserCommonColorDMGetMuteStatus(EnumDisplayRegion enumDisplayRegion)
{
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
    {
        return _FALSE;
    }

    return (GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) != _DM_NO_MUTE);
}

//--------------------------------------------------
// Description  : DMStatus for User
// Input Value  : EnumDisplayRegion, EnumHDRTargetStatus
// Output Value : T/F
//--------------------------------------------------
bit UserCommonColorDMGetDMStatus(EnumDisplayRegion enumDisplayRegion)
{
    EnumHDRTargetStatus enumHDRTargetStatus = GET_HDR_TARGET_STATUS(enumDisplayRegion);

    switch(enumHDRTargetStatus)
    {
        case _HDR_TARGET_STATUS_DM:
        case _HDR_TARGET_STATUS_DM_GAME:
            return _TRUE;

        case _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR:
        case _HDR_TARGET_STATUS_SMPTE_ST_2084:
        case _HDR_TARGET_STATUS_FORCE_2084:
        case _HDR_TARGET_STATUS_AUTO_HLG:
        case _HDR_TARGET_STATUS_FORCE_HLG:
        case _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR:
        case _HDR_TARGET_STATUS_ADVANCED_HDR10:
        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DM Game Mode for User
// Input Value  : EnumDisplayRegion, EnumHDRTargetStatus
// Output Value : T/F
//--------------------------------------------------
bit UserCommonColorDMGetDMGameMode(EnumDisplayRegion enumDisplayRegion)
{
    EnumHDRTargetStatus enumHDRTargetStatus = GET_HDR_TARGET_STATUS(enumDisplayRegion);

    switch(enumHDRTargetStatus)
    {
        case _HDR_TARGET_STATUS_DM_GAME:
            return _TRUE;

        case _HDR_TARGET_STATUS_DM:
        case _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR:
        case _HDR_TARGET_STATUS_SMPTE_ST_2084:
        case _HDR_TARGET_STATUS_FORCE_2084:
        case _HDR_TARGET_STATUS_AUTO_HLG:
        case _HDR_TARGET_STATUS_FORCE_HLG:
        case _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR:
        case _HDR_TARGET_STATUS_ADVANCED_HDR10:
        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Polling BEC Status
// Input Value  : enumRegionIndex
//                ulWaitTimeout --> wait timeout (unit: ms)
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonColorDMPollingBECStatus(EnumRegionIndex enumRegionIndex, DWORD ulWaitTimeout, EnumDMBECStatus enumDMBECStatus)
{
    if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
    {
        return _FALSE;
    }

    DWORD ulTimeElapsed = 0;
    WORD usPreviousTime = g_usTimerCounter;

    while(ulTimeElapsed <= ulWaitTimeout)
    {
        if(GET_DM_BEC_STATUS_INDEX(enumRegionIndex) == enumDMBECStatus)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            ulTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }

    DebugMessageDM("DM Polling BEC Time Out", 0);
    return _FALSE;
}

//--------------------------------------------------
// Description  : Judje input status change or not
// Input Value  : enumDisplayRegion
// Output Value : T/F
//--------------------------------------------------
bit UserCommonColorDMStatusChange(EnumDisplayRegion enumDisplayRegion)
{
    return ScalerDMStatusChange(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : DM OSD turn Off DM
// Input Value  : enumDisplayRegion
// Output Value : T/F
//--------------------------------------------------
void UserCommonColorDMOSDSupportSwitch(EnumInputPort enumInputPort)
{
    BYTE ucIndex = 0;

    DebugMessageDM("DM OSD Support Switch", enumInputPort);

    for(ucIndex = 0; ucIndex < _DM_MAX_REGION_COUNT; ucIndex++)
    {
        if(GET_DM_PORT_INDEX(ucIndex) == enumInputPort)
        {
            EnumDisplayRegion enumDisplayRegion = GET_RGN_DISPLAY_REGION(ucIndex);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if((enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB) && (ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _FALSE))
            {
                SET_DM_MAIN_SUB_SYNC();
                break;
            }
#endif

            // IRQ ON/OFF
            if(UserCommonColorDMGetEnableStatus(enumDisplayRegion) == _DM_SUPPORT_ON)
            {
                UserCommonColorDMIRQSupportSwitch(enumDisplayRegion, _ENABLE);
            }
            else if(GET_DM_MUTE_STATUS_INDEX(ucIndex) == _DM_NO_MUTE)
            {
                UserCommonColorDMIRQSupportSwitch(enumDisplayRegion, _DISABLE);

                if(UserCommonColorDMGetDMStatus(enumDisplayRegion) == _TRUE)
                {
                    // DM Out Process
                    UserCommonColorDMMuteProc(enumDisplayRegion, _ENABLE);
                    // IRQ off, unmute frame count won't count, manual set to _DM_UNMUTE_WAIT_FRAME_CNT
                    SET_DM_UNMUTE_FRAME_CNT_INDEX(ucIndex, _DM_UNMUTE_WAIT_FRAME_CNT);
                    SET_DM_MUTE_STATUS_INDEX(ucIndex, _DM_OUT_MUTE);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Return DM Display Region
// Input Value  : EnumSelRegion
// Output Value : EnumDisplayRegion
//--------------------------------------------------
EnumDisplayRegion UserCommonColorDMGetDisplayRegion(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _FULL_REGION:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
            {
                return _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
            }
            else
#endif
            {
                return _DISPLAY_RGN_NONE;
            }

        case _DEMO_INSIDE:
        case _DEMO_OUTSIDE:

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

        default:
            return (EnumDisplayRegion)enumSelRegion;
    }
}

//--------------------------------------------------
// Description  : Return if DM Active/Prepare, skip HDR process
// Input Value  : EnumDisplayRegion
// Output Value : bypass HDR process or not
//--------------------------------------------------
bit UserCommonColorDMGetBypassHDRProcStatus(EnumDisplayRegion enumDisplayRegion)
{
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    if(enumRegionIndex >= _DM_MAX_REGION_COUNT)
    {
        return _FALSE;
    }

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_SUB)
    {
        // if Eagle Sight main is not in Dolby, sub still in Dolby, must do HDR process for sub
        if((UserCommonColorDMGetDMStatus(_DISPLAY_RGN_EAGLE_SIGHT_MAIN) == _FALSE) && (UserCommonColorDMGetDMStatus(_DISPLAY_RGN_EAGLE_SIGHT_SUB) == _TRUE))
        {
            return _FALSE;
        }
    }
#endif

    if(GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) != _DM_OUT_MUTE)
    {
        // preparing going to DM state, or remaining in DM state, skip HDR process
        if((GET_DM_BEC_STATUS_INDEX(enumRegionIndex) != _DM_BEC_INIT) || (UserCommonColorDMGetDMStatus(enumDisplayRegion) == _TRUE))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Out DM mode, restore color setting
// Input Value  : EnumDisplayRegion, EnumSelRegion, EnumInputPort
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMRestoreSetting(EnumDisplayRegion enumDisplayRegion, EnumSelRegion enumSelRegion, EnumInputPort enumInputPort, bit bColorFormatConvert)
{
    EnumRegionIndex enumRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    if(enumRegionIndex < _DM_MAX_REGION_COUNT)
    {
        if(GET_DM_MUTE_STATUS_INDEX(enumRegionIndex) == _DM_OUT_MUTE)
        {
#if(_COLOR_IP_SHARPNESS == _ON)
            // Sharpness
            UserCommonColorSharpnessAdjust(enumSelRegion, _DB_APPLY_NO_POLLING);
#endif
            // Color Sampling
            ScalerColor422To444(enumInputPort, enumDisplayRegion);

            if(bColorFormatConvert == _FALSE)
            {
                UserCommonColorSetColorFormatConvert(enumDisplayRegion, enumInputPort, ScalerColorGetColorSpace(enumInputPort), _DB_APPLY_NO_POLLING);
            }
        }
    }
}

//--------------------------------------------------
// Description  : DM mode color setting
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMAdjustDMProc(EnumDisplayRegion enumDisplayRegion, EnumDMAdjustType enumAdjustType)
{
    EnumHDRTargetStatus enumHDRTargetStatus = GET_HDR_TARGET_STATUS(enumDisplayRegion);
    EnumSelRegion enumSelRegion = (EnumSelRegion)enumDisplayRegion;

    WORD usColorFunction = (_COLOR_FUNCTION_SHARPNESS |
                            _COLOR_FUNCTION_ULTRA_VIVID |
                            _COLOR_FUNCTION_LOCAL_CONTRAST |
                            _COLOR_FUNCTION_DCC |
                            _COLOR_FUNCTION_ICM |
                            _COLOR_FUNCTION_COLOR_ENHANCE |
                            _COLOR_FUNCTION_CTS_BRI |
                            _COLOR_FUNCTION_3DGAMMA |
                            _COLOR_FUNCTION_UNIFORMITY |
                            _COLOR_FUNCTION_PCM |
                            _COLOR_FUNCTION_LIGHT_ENHANCE);

    if(enumAdjustType == _DM_ADJUST_DM_AND_COLOR)
    {
        UserCommonColorMultiFunctionRegionEnableStart(enumSelRegion, usColorFunction);

#if(_COLOR_IP_SHARPNESS == _ON)
        UserCommonColorSharpnessAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_ULTRA_VIVID_FUNCTION == _ON)
        UserCommonColorUltraVividAdjust(enumSelRegion);
#endif

#if(_LOCAL_CONTRAST_FUNCTION == _ON)
        UserCommonColorLocalContrastAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_HDR10_LIGHT_ENHANCE_FUNCTION == _ON)
        UserCommonColorHDRAdjustHDR10LightEnhance(enumSelRegion, _DB_APPLY_NONE);
#elif(_DCC_FUNCTION == _ON)
        UserCommonColorDCCAdjust(enumSelRegion);
#endif

#if(_HDR10_COLOR_ENHANCE_FUNCTION == _ON)
        UserCommonColorHDRAdjustHDR10ColorEnhance(enumSelRegion, _DB_APPLY_NONE);
#elif(_ICM_FUNCTION == _ON)
        UserCommonColorICMAdjust(enumSelRegion);
#endif

#if((_RGB_3D_GAMMA_FUNCTION == _ON) || (_ADVANCED_HDR10_SUPPORT == _ON) || (_RGB_3D_GAMMA_HDR10_GAMUT_CMP_SUPPORT == _ON))
        UserCommonColor3DGammaAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_CONTRAST_FUNCTION == _ON)
        UserCommonColorContrastAdjust(enumSelRegion);
#endif

#if(_BRIGHTNESS_FUNCTION == _ON)
        UserCommonColorBrightnessAdjust(enumSelRegion);
#endif

#if(_UNIFORMITY_FUNCTION == _ON)
        UserCommonColorPanelUniformityAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_PCM_FUNCTION == _ON)
        UserCommonColorPCMAdjust(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_COLOR_IP_COLOR_CONVERT == _ON)
        // Force DM Mode Color Convert
        UserCommonColorSetColorFormatConvertDM(enumDisplayRegion, _DB_APPLY_NONE);
#endif

        UserCommonColorMultiFunctionRegionEnableEnd(enumSelRegion, usColorFunction);

        // No Double Buffer
        // Force DM Mode to Disable 422 to 444
        ScalerColor422To444DM(SysRegionGetInputPort(enumDisplayRegion), enumDisplayRegion, _OFF);
    }
    else
    {
        // Apply DM
        ScalerGlobalIDomainDBApply(UserCommonRegionGetInputDataPath(UserCommonColorDMGetDisplayRegion(enumSelRegion)), _DB_APPLY_POLLING);
    }

    UserInterfaceColorDMAdjust(enumDisplayRegion, enumHDRTargetStatus, enumAdjustType);
}

#if(_DM_DEMO_FUNCTION == _ON)
//--------------------------------------------------
// Description  : DM Demo Function Processing
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonColorDMDemoFuncProc(void)
{
    g_ucColorDMDemoFuncTimer++;

    if(g_ucColorDMDemoFuncTimer == _DM_DEMO_FUNCTION_TIME_LIMIT)
    {
        ScalerGlobalWholeChipReset();
        while(_TRUE)
        {
            ScalerDebug();
        }
    }
    else
    {
        UserCommonTimerReactiveTimerEvent(_DM_DEMO_FUNCTION_TIME_UNIT, _SYSTEM_TIMER_EVENT_DM_DEMO_FUNCTION);
    }
}
#endif
#endif

#if(_IS_MAIN_PROCESS_CPU == _FALSE)
//--------------------------------------------------
// Description  : DM Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMBECHandler(void)
{
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    if(ucRegionCount > _DM_MAX_REGION_COUNT)
    {
        return;
    }

    for(BYTE ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        EnumDisplayRegion enumDisplayRegion = GET_RGN_DISPLAY_REGION(ucRegionIndex);

        if((GET_DM_BEC_STATUS_INDEX(ucRegionIndex) == _DM_BEC_BUSY) &&
           (SysRegionCheckDisplayEvent(enumDisplayRegion, _DISPLAY_EVENT_TIMING_CONFIRMED) == _TRUE))
        {
            bit bDMBecResult = _FALSE;
            EnumInputPort enumInputPort = SysRegionGetInputPort(enumDisplayRegion);
            EnumColorSpace enumColorSpace = ScalerColorGetColorSpace(enumInputPort);
            BYTE ucColorDepth = ScalerColorGetColorDepth(enumInputPort);

            g_pstDMSettingInfo[ucRegionIndex].enumDMColorSpace = enumColorSpace;
            g_pstDMSettingInfo[ucRegionIndex].ucDMColorDepth = ucColorDepth;
            bDMBecResult = ScalerDMRunBEC(enumDisplayRegion, ucColorDepth, enumColorSpace);

            if(bDMBecResult == _TRUE)
            {
                SET_DM_BEC_STATUS_INDEX(ucRegionIndex, _DM_BEC_DONE);
            }
            else
            {
                if(GET_DM_METADATA_ERROR_INDEX(ucRegionIndex) == _FALSE)
                {
                    g_pstDMSettingInfo[ucRegionIndex].ucFrameCnt = ScalerDMGetFrameCnt(enumDisplayRegion);
                    SET_DM_METADATA_ERROR_INDEX(ucRegionIndex);
                }
                SET_DM_BEC_STATUS_INDEX(ucRegionIndex, _DM_BEC_INIT);
            }
        }
    }
}

//--------------------------------------------------
// Description  : DM Mute Hander
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonColorDMMuteHandler(void)
{
    BYTE ucRegionIndex = 0;
    for(ucRegionIndex = 0; ucRegionIndex < _DM_MAX_REGION_COUNT; ucRegionIndex++)
    {
        if(GET_DM_UNMUTE_FLAG_INDEX(ucRegionIndex) == _TRUE)
        {
            UserCommonColorDMMuteProc(GET_RGN_DISPLAY_REGION(ucRegionIndex), _DISABLE);

            CLR_DM_UNMUTE_FLAG_INDEX(ucRegionIndex);
        }

        if(GET_DM_MUTE_FLAG_INDEX(ucRegionIndex) == _TRUE)
        {
            UserCommonColorDMMuteProc(GET_RGN_DISPLAY_REGION(ucRegionIndex), _ENABLE);

            CLR_DM_MUTE_FLAG_INDEX(ucRegionIndex);
        }
    }
}
#endif
#endif
