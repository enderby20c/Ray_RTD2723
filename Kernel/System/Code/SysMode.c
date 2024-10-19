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
// ID Code      : SysMode.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_MODE__

#include "SysInclude.h"
#include "Mode/SysMode.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructModeInfoType g_stModeInfo;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Mode related behavior
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeHandler(void)
{
#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return;
    }
#endif

    switch(GET_MODE_STATE())
    {
        case _MODE_STATUS_POWER_OFF:

#if((_BILLBOARD_SCALER_SUPPORT == _ON) && (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON))
            if(g_bUsbBillboardIspProcessingDone == _TRUE)
            {
                if(GET_POWER_STATUS() != _POWER_STATUS_OFF)
                {
                    SET_TARGET_POWER_STATUS(_POWER_STATUS_OFF);
                }
            }
#endif

#if((_USB_HUB_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
            if((SysUsbHubGetAttachStatusChange() == _USB_CABLE_UNPLUG) || (ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_ENTER_P3_PS))
#else
            if(SysUsbHubGetAttachStatusChange() == _USB_CABLE_UNPLUG)
#endif
            {
                if(GET_POWER_STATUS() != _POWER_STATUS_OFF)
                {
                    SET_TARGET_POWER_STATUS(_POWER_STATUS_OFF);
                }
            }
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
            else if(((SysUsbHubGetAttachStatusChange() == _USB_CABLE_PLUG) && (SysUsbHubJudgeUsbPDStatus() == _PD_USB3_ENABLE)) || (ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_EXIT_P3_PS))
#else
            else if((SysUsbHubGetAttachStatusChange() == _USB_CABLE_PLUG) && (SysUsbHubJudgeUsbPDStatus() == _PD_USB3_ENABLE))
#endif
            {
                if(GET_POWER_STATUS() == _POWER_STATUS_OFF)
                {
                    SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);

                    SET_POWER_SWITCH_TO_FAKE_OFF();
                }
            }
#endif

#if((_DP_HDCP_RX_SUPPORT == _ON) && (_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON))
            if(GET_POWER_STATUS() == _POWER_STATUS_OFF)
            {
                if(ScalerDpHdcpRxHandshakeStartCheck() == _TRUE)
                {
                    SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);

                    SET_POWER_SWITCH_TO_FAKE_OFF();

                    ScalerTimerReactiveTimerEvent(_POWER_OFF_HDCP_HANDSHAKE_TIMEOUT, _SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);

                    SET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();
                }
            }
#endif

            break;

        case _MODE_STATUS_INITIAL:

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
            if(GET_MODE_STATE_CHANGE_MODE() == _TRUE)
            {
                g_ucSourceSearchIndex = 0;

                SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSourceSearchIndex);

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
                // g_ucSourceSearchIndex=D14/D15 in NVRAM => convert Index to g_ucSourceSearchIndex=D4 for D14/D15 when DC OFF/ON
                SysSourceConvertSearchIndexExtendedPortToD4Port();
#else
                // g_ucSourceSearchIndex=D12/D13 in NVRAM => convert Index to g_ucSourceSearchIndex=D3 for D12/D13 when DC OFF/ON
                SysSourceConvertSearchIndexExtendedPortToD3Port();
#endif
#endif
            }
#endif

            break;

        case _MODE_STATUS_DISPLAY_INITIAL:

            if(UserInterfaceDisplayGetLogoStatus() == _OSD_LOGO_ON)
            {
                // Skip clearing mode state change flag
                return;
            }

            // Perform display initial setting
            SysModeDisplayInitialSetting();

            break;

        case _MODE_STATUS_DISPLAY_SETTING:

            // Perform display setting only when all conditions met:
            // 1. timing confirmed
            // 2. display state != display ready or OOR
            if(GET_RGN_TIMING_CONFIRM(GET_MODE_DISPLAY_TARGET_INDEX()) == _TRUE)
            {
                if((GET_MODE_DISPLAY_TARGET_STATE() != _DISPLAY_STATE_DISPLAY_READY) &&
                   (GET_MODE_DISPLAY_TARGET_STATE() != _DISPLAY_STATE_OOR))
                {
#if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
                    DWORD ulDclk = GET_D_CLK_FREQ();
#endif

                    if(SysModeDisplaySetting() == _TRUE)
                    {
#if(((_DP_SUPPORT == _ON) && (_DP_PR_MODE_SUPPORT == _ON)) || ((_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_REPLAY_SUPPORT == _ON)))
                        ScalerSyncPRModeCheckProc(SysSourceGetInputPort());
#endif

#if(_DEBUG_MESSAGE_CHECK_MDOMAIN == _ON)
                        ScalerMDomainCheckDisplaySetting();
#endif

#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_2P_FRAME_SYNC_DEBOUNCE_TIME != 0))
                        if((ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE) &&
                           (GET_MODE_DISPLAY_TARGET_INDEX() == 0x00))
                        {
                            SysJudge2pFrameSyncDebounceReset();
                        }
#endif

#if(_PANEL_STYLE == _PANEL_VBO)
                        if(((GET_FORCE_DISPLAY_1P_MODE() == _TRUE) ||
                            (ScalerMDomainCheckMTPFreerunFinetune() == _TRUE)) &&
                           (ABSDWORD(ulDclk, GET_D_CLK_FREQ()) > (ulDclk / 1000)))
                        {
#if(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_RE_LINK_TRAIN)
                            // Turn off Backlight Power to prevent garbage
                            UserCommonPowerPanelAction(_BACKLIGHT_OFF);
#elif(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_PANEL_OFF)
                            // Turn off Panel Power to prevent garbage
                            UserCommonPowerPanelAction(_PANEL_OFF);
#endif
                        }
#endif

#if(_PANEL_STYLE == _PANEL_DPTX)
                        if(((GET_FORCE_DISPLAY_1P_MODE() == _TRUE) ||
                            (ScalerMDomainCheckMTPFreerunFinetune() == _TRUE)) &&
                           (ABSDWORD(ulDclk, GET_D_CLK_FREQ()) > (ulDclk / 1000)))
                        {
                            // Turn off Backlight Power to prevent garbage
                            UserCommonPowerPanelAction(_BACKLIGHT_OFF);
                        }
#endif


#if((_PANEL_POW_SEQ_FAST_MODE == _ON) || (_PANEL_POWER_ON_BEFORE_COLOR_SETTING == _ON))
                        UserCommonPowerPanelAction(_PANEL_ON);
#endif
                        UserCommonModeDisplaySettingColorProc(GET_MODE_DISPLAY_TARGET_REGION());

                        SET_RGN_DISPLAY_ACTION(GET_MODE_DISPLAY_TARGET_INDEX(), _DISPLAY_ACTION_DISPLAY_READY);

                        SET_MODE_RESET_TARGET(_MODE_ACTION_NO_RESET_MODE);

                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                    }
                }
            }

            break;

        case _MODE_STATUS_DISPLAY_CHECK:

            if(GET_MODE_STATE_CHANGE_MODE() == _TRUE)
            {
                SysModeFirstDisplayCheckProc();
            }

            // Perform regular display state process
            SysModeDisplayStateProc();

            // Clear system display state change event
            SysRegionClearAllDisplayEvent(_DISPLAY_EVENT_STATE_CHANGE_SYS);

            break;

        case _MODE_STATUS_POWER_SAVING:

            if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
            {
#if((_BILLBOARD_SCALER_SUPPORT == _ON) && (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON))
                if(g_bUsbBillboardIspProcessingDone == _TRUE)
                {
                    if(GET_POWER_STATUS() != _POWER_STATUS_SAVING)
                    {
                        SET_TARGET_POWER_STATUS(_POWER_STATUS_SAVING);
                    }
                }
#endif

#if((_USB_HUB_SUPPORT == _ON) && (_USB3_REPEATER_MAC_SUPPORT == _ON))
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
                if((SysUsbHubGetAttachStatusChange() == _USB_CABLE_UNPLUG) || (ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_ENTER_P3_PS))
#else
                if(SysUsbHubGetAttachStatusChange() == _USB_CABLE_UNPLUG)
#endif
                {
                    if(GET_POWER_STATUS() != _POWER_STATUS_SAVING)
                    {
                        SET_TARGET_POWER_STATUS(_POWER_STATUS_SAVING);
                    }
                }
#if(_USB3_U3_P3_POWER_SAVING_SUPPORT == _ON)
                else if((SysUsbHubGetAttachStatusChange() == _USB_CABLE_PLUG) || (ScalerUsb3RepeaterMacGetLowPowerStateStatus() == _USB3_RETIMER_EXIT_P3_PS))
#else
                else if(SysUsbHubGetAttachStatusChange() == _USB_CABLE_PLUG)
#endif
                {
                    if(GET_POWER_STATUS() != _POWER_STATUS_NORMAL)
                    {
                        SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
                    }
                }
                else
#endif
                {
                    if((GET_SOURCE_SWITCH_FINISH() == _TRUE) && (UserCommonPowerGetIntoPSStatus() == _PS_PERMISSION_TRUE))
                    {
                        if(SysPowerGetPowerStatus() != _POWER_STATUS_SAVING)
                        {
                            SET_TARGET_POWER_STATUS(_POWER_STATUS_SAVING);

                            CLR_SOURCE_SWITCH_FINISH();

                            DebugMessageSystem("7. wuzanne test : Set Power Target to PS (Form Mode PS)", 0);
                        }
                    }
                }

#if((_DP_HDCP_RX_SUPPORT == _ON) && (_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON))
                // Timer Event Timeout Flag Asserted, Trigger Back To Power Saving
                if(GET_DP_HDCP_POWER_OFF_HANDSHAKE_TIMEOUT_FLAG() == _TRUE)
                {
                    CLR_DP_HDCP_POWER_OFF_HANDSHAKE_TIMEOUT_FLAG();

                    if((GET_POWER_STATUS() == _POWER_STATUS_NORMAL) && (GET_TARGET_POWER_STATUS() != _POWER_STATUS_NORMAL))
                    {
                        SET_TARGET_POWER_STATUS(_POWER_STATUS_SAVING);
                    }
                }
                else
                {
                    // Only When (Scan Mode == Fix Port) && (Fix Port != Current Hdcp Handshake Port)
                    // Switch Power to Fake Saving And Trigger Timer Event
                    if((GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT) ||
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
                       ((GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_TIMING_CHANGE) && (UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)) ||
#endif
                       (_FALSE))
                    {
                        // Before Timing Confirm, (Mode Status == PS) && (Power Status == Normal), No Need Proc Here
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            if(ScalerDpHdcpRxHandshakeStartActiveTimerCheck(SysSourceGetInputPort()) == _TRUE)
                            {
                                if(GET_TARGET_POWER_STATUS() != _POWER_STATUS_NORMAL)
                                {
                                    SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);

                                    ScalerTimerReactiveTimerEvent(_POWER_OFF_HDCP_HANDSHAKE_TIMEOUT, _SYSTEM_TIMER_EVENT_POWER_FAKE_SAVING_TO_SAVING);

                                    SET_DP_HDCP_POWER_OFF_HANDSHAKE_CHECK();
                                }
                            }
                        }
                    }
                }
#endif
            }

            // Perform regular display state process
            SysModeDisplayStateProc();

            break;

        case _MODE_STATUS_FACTORY:

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
            UserCommonQCHandler();
#endif

            break;

        default:

            break;
    }

    CLR_MODE_STATE_CHANGE_MODE();
}

//--------------------------------------------------
// Description  : Return Mode State for other Group
// Input Value  : None
// Output Value : Mode State
//--------------------------------------------------
BYTE SysModeGetModeState(void)
{
    return GET_MODE_STATE();
}

//--------------------------------------------------
// Description  : Clr Mode State Change Flag for OSD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeClrModeStateChange(void)
{
    CLR_MODE_STATE_CHANGE_OSD();
}

//--------------------------------------------------
// Description  : Regular first active process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeFirstDisplayCheckProc(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();
    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();

#if(_FRC_SUPPORT == _ON)
    EnumInputDataPath enumInputPathEnable = _INPUT_PATH_NONE;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if((GET_RGN_DISPLAY_STATE_CHANGE_SYS(ucRegionIndex) == _TRUE) &&
           (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_ACTIVE))
        {
            // Set first active flag; Simplify later reset to display setting flow
            SET_RGN_FIRST_ACTIVE(ucRegionIndex);

            // Perform first active process
            ScalerGlobalFirstActiveProc(GET_RGN_SOURCE_TYPE(ucRegionIndex), GET_RGN_INPUT_PORT(ucRegionIndex), GET_RGN_DISPLAY_REGION(ucRegionIndex));

            UserCommonModeDisplayActiveProc(GET_RGN_DISPLAY_REGION(ucRegionIndex));
        }
    }

#if(_FRC_SUPPORT == _ON)
    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(((GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_ACTIVE) ||
            (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_DISPLAY_READY)) &&
           (ScalerFRCImgCmpGetActive(ucRegionIndex) == _TRUE))
        {
            enumInputPathEnable = (enumInputPathEnable | ScalerRegionGetInputDataPath(SysRegionGetDisplayRegion(ucRegionIndex)));
        }
    }

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
    ScalerImgCmpDecmpPowerControl(enumInputPathEnable, _OFF);
#endif
#if(_HW_IMD_POWER_CUT_INDEPENDENT_SUPPORT == _ON)
    if(ScalerFRCGetEOtoFBStatus() == _FALSE)
    {
        ScalerPowerEOtoFBPowerControl(GET_MDOMAIN_INPUT_DATA_PATH(), _OFF);
    }

    if(ScalerFRCGetFBtoEOStatus() == _FALSE)
    {
        ScalerPowerFBtoEOPowerControl(ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH()), _OFF);
    }
#endif
#endif

#if(_FIRST_CHECK_CONTROL_BACKLIGHT_BY_USER == _ON)
    if(UserInterfaceModeFirstDisplayCheckGetBacklightAction(enumDisplayMode) == _BACKLIGHT_ENABLE)
    {
        UserCommonPowerPanelAction(_BACKLIGHT_ON);
    }
#else
    // Turn on back light when:
    // 1. under 2P/4P mode
    // 2. 1P mode in active state
    // Main & Sub Will Loop 1 Times
    if(((enumDisplayMode == _DISPLAY_MODE_1P) && (GET_RGN_DISPLAY_STATE(0) == _DISPLAY_STATE_ACTIVE)) ||
       (enumDisplayMode != _DISPLAY_MODE_1P))
    {
        UserCommonPowerPanelAction(_BACKLIGHT_ON);
    }
#endif

    SysSourceFirstActiveProc();
}

//--------------------------------------------------
// Description  : Regular display state process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeDisplayStateProc(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        switch(GET_RGN_DISPLAY_STATE(ucRegionIndex))
        {
            case _DISPLAY_STATE_ACTIVE:

                // Perform active routine process
                ScalerSyncActiveProc(GET_RGN_SOURCE_TYPE(ucRegionIndex));

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_PHASE_CALIBRATION == _ON) && (_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE))
                // Perform DDR3 calibration in FRC mode
                if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
                {
                    ScalerDDR3OfflinePhaseCalFRCMode();
                }

#endif

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR2) && (_DDR2_PHASE_CALIBRATION == _ON) && (_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE))
                // Perform DDR2 calibration in FRC mode

                if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
                {
                    ScalerDDR2OfflinePhaseCalFRCMode();
                }

#endif

#if(_DDR_BURN_IN_TEST == _ON)
                // Perform DDR/FRC Brun-in Test
                if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
                {
                    ScalerDDRBurnInCRCTest();
                }
#endif

                break;

            case _DISPLAY_STATE_NO_SIGNAL:

                // Reset to display none state if cable status change
                if(UserInterfaceSourceGetCableResetStatus(GET_RGN_DISPLAY_REGION(ucRegionIndex)) == _CABLE_RESET_TRUE)
                {
                    switch(GET_MODE_STATE())
                    {
                        case _MODE_STATUS_DISPLAY_CHECK:

                            DebugMessageSystem("CHK: Cable reset", GET_RGN_DISPLAY_REGION(ucRegionIndex));

                            // Perform user resume process
                            UserCommonModeResumeRegionProc(GET_RGN_DISPLAY_REGION(ucRegionIndex));

                            // Reset display state to _DISPLAY_STATE_NONE
                            SysRegionSetDisplayStateBySearchIndex(GET_RGN_SOURCE_INDEX(ucRegionIndex), _DISPLAY_STATE_NONE);

                            // Reset source search times
                            if((enumDisplayMode == _DISPLAY_MODE_1P) ||
                               (GET_SOURCE_AUTO_TARGET() == ucRegionIndex))
                            {
                                SysSourceSearchTimeReset();
                            }

                            break;


                        case _MODE_STATUS_POWER_SAVING:

                            DebugMessageSystem("PS: Cable reset", GET_RGN_DISPLAY_REGION(ucRegionIndex));

                            if(SysPowerGetPowerStatus() != _POWER_STATUS_NORMAL)
                            {
                                SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
                            }

                            SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);

                            SysSourceCableResetProc();

                            break;

                        default:

                            break;
                    }
                }

                break;

            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Include all required settings for Display
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeDisplayInitialSetting(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

#if(_VGA_SUPPORT == _ON)
    // Disable Vga Top Double Buffer
    ScalerVgaTopDoubleBufferEnable(_DISABLE);
#endif

    ScalerGlobalDoubleBufferEnable(_INPUT_PATH_ALL, _DISABLE);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    SysModeSetEagleSightSupport();
#endif

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        SET_MODE_DISPLAY_TARGET_INDEX(ucRegionIndex);
        SysModeDisplayTimingInitial(GET_DISPLAY_MODE(), GET_MODE_DISPLAY_TARGET_REGION());
        ScalerMDomainSetDisplayTimingGenActiveRegion(ScalerRegionGetDDomainRegion(GET_MODE_DISPLAY_TARGET_REGION()));

        // Set default FIFO Size
        ScalerMemorySetFifoCapture(ScalerRegionGetInputDataPath(GET_MODE_DISPLAY_TARGET_REGION()), GET_MDOMAIN_OUTPUT_HWIDTH(), GET_MDOMAIN_OUTPUT_VHEIGHT());

        // Set Background
        ScalerMDomainSetDisplayTimingGenBackground(GET_MODE_DISPLAY_TARGET_REGION());

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1)
        ScalerGlobalEnableUnderflowMonitor(_DISABLE, ScalerRegionGetDDomainRegion(GET_MODE_DISPLAY_TARGET_REGION()));
#endif
#endif

#if(_FW_DISPLAYTOP_AVG_REQ_SUPPORT == _ON)
        ScalerDDomainSetDdmReqAvgReqEnable(GET_MODE_DISPLAY_TARGET_REGION(), _DISABLE);
#endif

#if(_HW_ADJ_A1_LB_START_ADDR == _ON)
        // Disable LB Start Address
        ScalerDDomainSetDisplayTopLBStartAddr(GET_MODE_DISPLAY_TARGET_REGION(), 0);
#endif
    }
    // Set Display Conversion Line Length
    ScalerDDomainSetDspcLineLength();

    // Set Display Timing Gen Control
    ScalerMDomainSetDisplayTimingGenDisplayMode(GET_DISPLAY_MODE());

#if((_HW_D_DOMAIN_R1_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R2_A2_ACTIVE_SUPPORT == _ON) || (_HW_D_DOMAIN_R3_A2_ACTIVE_SUPPORT == _ON))
    // Set Background Color Vertical Change Midline
    ScalerDDomainSetBackgroundVerticalChange(GET_DISPLAY_MODE());
#endif

    // Global Display Initial
    ScalerGlobalDisplayInitial(GET_DISPLAY_MODE());

    // User Common Display Initial Color Proc
    UserCommonModeDisplayInitialColorProc(GET_DISPLAY_MODE());

    // Enable global double buffer
    ScalerGlobalDoubleBufferEnable(_INPUT_PATH_ALL, _ENABLE);

#if((_GOSD_SUPPORT == _ON) && ((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)))
    ScalerGosdDispOsdDisplayEnableByBackup();
#endif

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
#if(_PBP_LR_FRAME_SYNC_SUPPORT == _ON)
    if(ScalerRegionGet2PMainPathRegion() == _REGION_INDEX_1)
    {
        SET_2P_FRAME_SYNC_MAIN(_FALSE);
    }
    else
#endif
    {
        SET_2P_FRAME_SYNC_MAIN(_TRUE);
    }

#if(_2P_FRAME_SYNC_DEBOUNCE_TIME != 0)
    if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
    {
        SysJudge2pFrameSyncDebounceReset();

        if(SysJudgeCheck2pFrameSyncDebounceSupported() == _TRUE)
        {
            SysJudge2pFrameSyncDebounceStart();
        }
    }
#endif
#endif

    // Set DisplayConverion
    ScalerDisplaySetDspc();
}

//--------------------------------------------------
// Description  : Include all required settings for Display
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysModeDisplaySetting(void)
{
    bit bMdomainsetup = _TRUE;
    BYTE ucDisplaySettingCount = SysModeGetDisplaySettingCount();
    BYTE ucIndex = 0;

    SysModeSetUpDisplayGlobalInitialization();


    if(SysModeBypassDisplaySettingStatus() == _TRUE)
    {
        bMdomainsetup = _TRUE;
        DebugMessageSystem("Bypass display setting!", GET_MODE_DISPLAY_TARGET_INDEX());
    }
    else
    {
        for(ucIndex = 0; ucIndex < ucDisplaySettingCount; ++ucIndex)
        {
            // Set up variables for dispaly setting
            SysModeSetUpDisplayInitialization(ucIndex);

            // Set Up Input Timing to I Domain
            SysModeSetUpInputCapture();

            // Set D Domain Functions
            SysModeSetUpDisplayCapture();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if(ScalerSyncCheckUrgentEvent() == _TRUE)
            {
                return _FALSE;
            }
#endif

            // Set M Domain Functions
            bMdomainsetup &= SysModeSetUpMDomain();

            if(bMdomainsetup == _FALSE)
            {
                break;
            }
        }
    }

    SysModeSetUpDisplayGlobalFinialSetting();

    if(bMdomainsetup == _FALSE)
    {
        DebugMessageSystem("Display Setting Fail", GET_MODE_DISPLAY_TARGET_INDEX());
        return _FALSE;
    }

    DebugMessageSystem("Display Setting Pass", GET_MODE_DISPLAY_TARGET_INDEX());
    return _TRUE;
}

//--------------------------------------------------
// Description  : Return Bypass Display Setting Status
// Input Value  : None
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit SysModeBypassDisplaySettingStatus(void)
{
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
    if ((ScalerDDomainGetPbplrFullStatus() == _TRUE) &&
        (((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_L_LARGE) && (GET_MODE_DISPLAY_TARGET_INDEX() == _REGION_INDEX_1)) ||
         ((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PBP_LR_R_LARGE) && (GET_MODE_DISPLAY_TARGET_INDEX() == _REGION_INDEX_0))))
    {
        ScalerGlobalClrDvsTimeoutFlag();
        ScalerFRCCapFifoOvflWDDisable(ScalerRegionGetInputDataPath(GET_MODE_DISPLAY_TARGET_REGION()));
        SET_MDOMAIN_OUTPUT_RGN(ScalerRegionGetDDomainRegion(GET_MODE_DISPLAY_TARGET_REGION()));
        ScalerMDomainClearStatus(ScalerRegionGetInputDataPath(GET_MODE_DISPLAY_TARGET_REGION()));
        return _TRUE;
    }
#endif
    return _FALSE;
}

//--------------------------------------------------
// Description  : Get required loop count for display setting flow
// Input Value  : None
// Output Value : number of loops
//--------------------------------------------------
BYTE SysModeGetDisplaySettingCount(void)
{
    return 1;
}

//--------------------------------------------------
// Description  : Set Up Global Initial for display setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeSetUpDisplayGlobalInitialization(void)
{
    // Set up testing flow
    DISPLAY_SETTING_TEST_INIT();

    if(GET_DISPLAY_SETTING_DB_ENABLE() == _TRUE)
    {
        // Clear Display Setting Double Buffer Enable Flag
        CLR_DISPLAY_SETTING_DB_ENABLE();
    }
    else
    {
        // Enable Global Double Buffer
        ScalerGlobalDoubleBufferEnable(_INPUT_PATH_ALL, _DISABLE);
    }
}

//--------------------------------------------------
// Description  : Global Finial Setting for display setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeSetUpDisplayGlobalFinialSetting(void)
{
    // Enable global DB
    ScalerGlobalDoubleBufferEnable(_INPUT_PATH_ALL, _ENABLE);

    // Start testing
    DISPLAY_SETTING_TEST_UPDATE();
}

//--------------------------------------------------
// Description  : Set Up variables for display setting
// Input Value  : ucIndex --> index for current display setting flow
// Output Value : None
//--------------------------------------------------
void SysModeSetUpDisplayInitialization(BYTE ucIndex)
{
    ucIndex = ucIndex;

    UserCommonModeDisplaySettingInitialization(GET_MODE_DISPLAY_TARGET_REGION());

    SysModeSetMtPMemorySelect();

    // Check Panel Backlight Action
    if(UserCommonModeDisplaySettingGetBacklightAction() == _BACKLIGHT_DISABLE)
    {
#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
        // Turn off backlight to prevent garbage
        UserCommonPowerPanelAction(_BACKLIGHT_OFF);
#else
        // Turn off backlight to prevent garbage
        UserCommonPowerPanelAction(_PANEL_OFF);
#endif
    }

#if(_HDR10_GET_STATUS_BEFOREHAND_SUPPORT == _ON)
#if(_ULTRA_HDR_SUPPORT == _ON)
    UserCommonColorHDRInitialSetting(GET_MODE_DISPLAY_TARGET_REGION());
#endif
#endif

    // Set input data
    ScalerMeasureSetRegionIndex(GET_MODE_DISPLAY_TARGET_INDEX());
    SET_MDOMAIN_INPUT_STRUCTURE(g_pstMeasureRegionTimingInfo[GET_MODE_DISPLAY_TARGET_INDEX()].stTimingInfo);
    SET_MDOMAIN_INPUT_PORT(GET_RGN_INPUT_PORT(GET_MODE_DISPLAY_TARGET_INDEX()));
    SET_MDOMAIN_SOURCE_TYPE(GET_RGN_SOURCE_TYPE(GET_MODE_DISPLAY_TARGET_INDEX()));
    SET_MDOMAIN_REF_INPUT_HSTART(GET_MODE_DISPLAY_TARGET_INDEX());

#if(_FRAME_RATE_SLOW_DOWN_SUPPORT == _ON)
    ScalerVgipResetSafeMode(GET_MDOMAIN_INPUT_DATA_PATH());
#endif

    ScalerMDomainUpdateInputInfo();

#if(_FRC_SUPPORT == _ON)
#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
    ScalerImgCmpDecmpPowerControl(GET_MDOMAIN_INPUT_DATA_PATH(), _ON);
#endif

#if(_HW_IMD_POWER_CUT_INDEPENDENT_SUPPORT == _ON)
    ScalerPowerEOtoFBPowerControl(GET_MDOMAIN_INPUT_DATA_PATH(), _ON);
    ScalerPowerFBtoEOPowerControl(ScalerFRCGetMDispPath(GET_MDOMAIN_INPUT_DATA_PATH()), _ON);
#endif
#endif

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() - (GET_MDOMAIN_INPUT_VSTART() % 2));
    }
#endif

#if(_DRR_SUPPORT == _ON)
    SysModeDrrSetMdomainInfo();
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
    SysModeHDMI21SetMdomainInfo();
#endif

#if(_COLOR_IP_DM == _ON)
#if(_COLOR_IP_LOCAL_DIMMING == _ON)
    ScalerIDomainPatternGenEnable(GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
#endif
#endif

    // Set output data
    SET_MDOMAIN_OUTPUT_RGN(ScalerRegionGetDDomainRegion(GET_MODE_DISPLAY_TARGET_REGION()));

#if(_HW_FORMAT_CONVERSION_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    // Set format conversion extension
    if((ScalerRegionGetDDomainRegion(GET_MODE_DISPLAY_TARGET_REGION())) == _DDOMAIN_RGN_R1_A1)
    {
        ScalerFmtCnvFBSetInitialExtension();
    }
#endif
#endif

    // Set MDomain custom info.
    UserCommonDisplayGetMDomainCustomInfo(&g_stDisplayCustomizedData);

    // Set memory data bit
    ScalerMDomainSetMemoryDataBit(SysModeSelectMemoryDataBit(g_stDisplayCustomizedData.structCustomizedMdomain.enumMemoryBitSelect));

    // Set Mdomain color space
    SET_MDOMAIN_COLOR_SPACE(ScalerColorGetColorSpace(GET_RGN_INPUT_PORT(GET_MODE_DISPLAY_TARGET_INDEX())));

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
    UserCommonDisplayResetRtkAdvMbrStatus();
#endif
#if(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
    ScalerMbrSetBlackFrameInsertAvailableMode();
#endif

    // Check Case to Disable Global Double Buffer
    if(SysModeCheckToDisableGlobalDoubleBuffer() == _TRUE)
    {
        ScalerGlobalDoubleBufferEnable(GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    // Set rotation
    SET_ROT_TYPE(UserInterfaceDisplayGetRotationDegree());

    if(ScalerRotationCheckStatus(GET_ROT_TYPE(), GET_RGN_INPUT_PORT(GET_MODE_DISPLAY_TARGET_INDEX())) == _TRUE)
    {
        SET_ROT_DISP_SIZE(UserInterfaceDisplayGetRotationDisplayType());
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
#if((_PIXEL_SHIFT_SUPPORT == _ON) && (_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN))
        // Update v front porch min value
        SET_ROT_V_FRONT_PORCH_MIN_VALUE(_ROTATION_V_FRONT_PORCH_MIN_VALUE + UserInterfaceDisplayRotationSetPixelShiftNumInfo());
#else
        // Update v front porch min value
        SET_ROT_V_FRONT_PORCH_MIN_VALUE(_ROTATION_V_FRONT_PORCH_MIN_VALUE);
#endif
#endif
    }
    else
    {
        SET_ROT_TYPE(_ROT_DISABLE);
    }
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
    SET_ADVANCED_HDR10_ENLARGE_DELAY_SUPPORT(UserCommonColorAdvancedHDR10GetEnlargeDelaySupport(GET_MODE_DISPLAY_TARGET_REGION()));
    SET_ADVANCED_HDR10_ENLARGE_DELAY_STATUS(_ADVANCED_HDR10_ENLARGE_DELAY_OFF);
#endif

#if(_OD_FUNCTION == _ON)
    ScalerODEnable(_FUNCTION_OFF);
#endif

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1)
    ScalerGlobalEnableUnderflowMonitor(_DISABLE, ScalerRegionGetDDomainRegion(GET_MODE_DISPLAY_TARGET_REGION()));
#endif
#endif

#if(_FW_DISPLAYTOP_AVG_REQ_SUPPORT == _ON)
    ScalerDDomainSetDdmReqAvgReqEnable(GET_MODE_DISPLAY_TARGET_REGION(), _DISABLE);
#endif

#if(_FRC_SUPPORT == _ON)
    // Disable FRC in change timing / m-domain check fail
    if(ScalerGlobalGetDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _DB_DISABLE)
    {
        EnumInputDataPath enumPath = GET_MDOMAIN_INPUT_DATA_PATH();

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
        // 4P/ 3P-skew/ PBP_TB Top Display, Can't Disable FRC Display
        if(GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE)
        {
            ScalerFRCEn(_FRC_CAPTURE_ONOFF, enumPath, _DISABLE);
        }
        else
#endif
        {
            // Disable FRC Capture and FRC Display
            ScalerFRCEn(_FRC_CAPTURE_ONOFF, enumPath, _DISABLE);
            ScalerFRCEn(_FRC_DISPLAY_ONOFF, enumPath, _DISABLE);

            ScalerFRCSetSourceSelect(enumPath, _DDOMAIN_SRC_FROM_FRAME_SYNC_MODE);
        }
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR2) && (_HW_MEMORY_DDR2_2PC_SEPARATE_SUPPORT == _ON))
    // switch DDR2 mux
    ScalerDDR2RotationSetClientMux();
#endif
#if(_HW_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_IV)
    if(GET_ROT_TYPE() == _ROT_CW180)
    {
        // set(or reset) initial boundary for rotation gen IV (avoid uplimit over)
        ScalerFRCSetInitialBoundaryforRotation();

        if(ScalerGlobalGetDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) != _DB_DISABLE)
        {
            ScalerGlobalIDDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_NO_POLLING);
        }
    }
#endif
#endif
#endif // End of #if(_FRC_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Set Up stuffs into I-Domain
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeSetUpInputCapture(void)
{
    WORD usInputVtotal = GET_MDOMAIN_INPUT_VTOTAL();
    // Apply fix on horizontal resolution
    SET_MDOMAIN_INPUT_HSTART(ScalerIDomainGetInputHorTimingAfterFmtCnv(GET_MDOMAIN_INPUT_HSTART(), GET_MDOMAIN_INPUT_DATA_PATH()));
    SET_MDOMAIN_INPUT_HWIDTH(ScalerIDomainGetInputHorTimingAfterFmtCnv(GET_MDOMAIN_INPUT_HWIDTH(), GET_MDOMAIN_INPUT_DATA_PATH()));
    SET_MDOMAIN_INPUT_HTOTAL(ScalerIDomainGetInputHorTimingAfterFmtCnv(GET_MDOMAIN_INPUT_HTOTAL(), GET_MDOMAIN_INPUT_DATA_PATH()));

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI21_FVA_SUPPORT == _ON)
    if(GET_HDMI21_FVA_ENABLE() == _TRUE)
    {
        usInputVtotal = GET_INPUT_TIMING_VTOTAL();
    }
#endif
#endif

#if(_DRR_SUPPORT == _ON)
    if(GET_DRR_IVF_INFO() == _TRUE)
#endif
    {
        if(usInputVtotal > GET_MDOMAIN_INPUT_VHEIGHT())
        {
            if(GET_MDOMAIN_INPUT_VSTART() > (usInputVtotal - GET_MDOMAIN_INPUT_VHEIGHT()))
            {
                SET_MDOMAIN_INPUT_VSTART((usInputVtotal - GET_MDOMAIN_INPUT_VHEIGHT()));
            }
        }
        else
        {
            DebugMessageScaler("Warning !!!! IVtotal <= GET_MDOMAIN_INPUT_VHEIGHT()", 0);
        }
    }

    if((GET_MDOMAIN_INPUT_HWIDTH() % 2) != 0x00)
    {
        // We should let H-width is even integer in case of the width of memory FIFO read width must even integer.
        SET_MDOMAIN_INPUT_HWIDTH(GET_MDOMAIN_INPUT_HWIDTH() + 1);
    }

    if((GET_MDOMAIN_INPUT_HTOTAL() % 2) != 0x00)
    {
        // if IHtotal is odd value, IHtotal will minus 1 after FC block
        SET_MDOMAIN_INPUT_HTOTAL(GET_MDOMAIN_INPUT_HTOTAL() - 1);
    }

    // Perform user adjust for I-domain
    UserCommonDisplayAdjustInputTiming(GET_MODE_DISPLAY_TARGET_REGION());

    // Set I-domain capture
    ScalerIDomainVgipSetInputCapture();

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
    // Set display latency ratio; 0 if rotation is enabled
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(GET_ROT_TYPE() != _ROT_DISABLE)
    {
        SET_DISP_LATENCY_RATIO(0);
    }
    else
#endif
    {
        SET_DISP_LATENCY_RATIO(UserInterfaceDisplayGetLatencyRatio());
    }
#endif
#if(_HDMI21_ALLM_SUPPORT == _ON)
    SET_FRC_ALLM_LATENCY_RATIO(UserInterfaceDisplayGetHDMIALLMOffLatencyRatio());
#endif
}

//--------------------------------------------------
// Description  : Set Up I-Domain
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeSetUpDisplayCapture(void)
{
    // System initialize default display timing
    SysModeDisplayTimingInitial(GET_DISPLAY_MODE(), GET_MODE_DISPLAY_TARGET_REGION());
    DebugMessageOsd("===TargetRGN", GET_MODE_DISPLAY_TARGET_REGION());

    // User adjust display timing
    UserCommonDisplayAdjustDisplayTiming(GET_MODE_DISPLAY_TARGET_REGION());

    // Check Display Timing
    ScalerMDomainCheckDisplayFormat(GET_MODE_DISPLAY_TARGET_REGION());
}

//--------------------------------------------------
// Description  : Set Up M-Domain
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysModeSetUpMDomain(void)
{
    // Perform M-domain setting
    bit bMDomainSettingResult = ScalerMDomainControl();

    return bMDomainSettingResult;
}

//--------------------------------------------------
// Description  : Mode Reset
// Input Value  : Reset Target
// Output Value : None
//--------------------------------------------------
void SysModeResetState(BYTE ucResetTarget)
{
    DebugMessageSystem("SysModeResetState!!", ucResetTarget);

    switch(ucResetTarget)
    {
        case _MODE_ACTION_RESET_TO_DISPLAY_INITIAL:

            // Reset global DB I domain trigger event
            ScalerGlobalIDDomainDBSetTriggerEventInitial(_INPUT_PATH_ALL, _DB_TRIGGER_EVENT_IVS);

            // User Reset Process
            UserCommonModeResetProc();

            // Reset source to display initial
            SysSourceInfoResetToDisplayInitial();

            // Clear all display info
            CLR_RGN_DISPLAY_INFO_ALL();

            // Clear Mode Active Ready Flag
            CLR_MODE_ACTIVE_READY();

            // Clear Measure Ready Flag
            SET_SOURCE_MEASURE_TARGET_INDEX(0);

#if((_GOSD_SUPPORT == _ON) && ((_IS_MAIN_PROCESS_CPU == _TRUE) || (_CPU32_SCPU_FW_MODE == _SCPU_FW_MODE_ACTOR)))
            ScalerGosdDispOsdDisplayDisableWithBackup();
#endif

            SysModeSetFreeRun();

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_CHECK:
            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG:
        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING:

            if(GET_MODE_DISPLAY_TARGET_STATE() != _DISPLAY_STATE_ACTIVE)
            {
                // User Reset Process
                UserCommonModeResetProc();
            }

            // Clear Mode Active Ready Flag
            CLR_MODE_ACTIVE_READY();

            // Set Display Setting Double Buffer Enable Flag
            SET_DISPLAY_SETTING_DB_ENABLE();

            // Initialize display setting variables
            CLR_RGN_DISPLAY_STATE(GET_MODE_DISPLAY_TARGET_INDEX());
            SET_MDOMAIN_INPUT_STRUCTURE(g_pstMeasureRegionTimingInfo[GET_MODE_DISPLAY_TARGET_INDEX()].stTimingInfo);
            SET_MDOMAIN_OUTPUT_RGN(ScalerRegionGetDDomainRegion(GET_MODE_DISPLAY_TARGET_REGION()));

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
#if(_PIP_TRANSPARENCY_SUPPORT == _ON)
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(GET_DISPLAY_MODE() != _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
#endif
            {
                // Disable PIP blending when main reset
                if(GET_MODE_DISPLAY_TARGET_REGION() == _DISPLAY_RGN_PIP_MAIN)
                {
                    ScalerColorPIPBlendingLevelAdjust(0x00, _DB_APPLY_NO_POLLING);
                }
            }
#endif
#endif

            break;

        case _MODE_ACTION_RESET_TO_POWER_SAVING:

            // User Reset Process
            UserCommonModeResetProc();

            // Clear Region Source Ready Flag
            CLR_RGN_SOURCE_TYPE_ALL();

            // Clear Region Source Judge
            CLR_RGN_SOURCE_JUDGE_ALL();

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
            CLR_SOURCE_BG_JUDGE(g_ucSourceBgDetectIndex);
#endif

            if(UserInterfacePowerGetForcePSStatus() == _FORCE_TO_PS_TRUE)
            {
                // Clear Region Display Info
                CLR_RGN_DISPLAY_INFO_ALL();
            }

            // Clear Source Switch Finish
            CLR_SOURCE_SWITCH_FINISH();

            // Clear Mode Active Ready Flag
            CLR_MODE_ACTIVE_READY();

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

            break;

        case _MODE_ACTION_RESET_TO_POWER_OFF:

            // User Reset Process
            UserCommonModeResetProc();

            // Clear Source Ready Flag
            SysSourceInfoReset();

            // Clear Measure Ready Flag
            SysRegionClearAllDisplayEvent(_DISPLAY_EVENT_ALL);

            // Clear Measure Ready Flag
            CLR_RGN_DISPLAY_INFO_ALL();

            // Clear Mode Active Ready Flag
            CLR_MODE_ACTIVE_READY();

            // Judge Reset Process
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

            break;

        default:

            break;
    }

    ScalerGlobalResetProc(ucResetTarget);
}

//--------------------------------------------------
// Description  : Reset M/D domain process
// Input Value  : enumDisplayRegion --> display region
// Output Value : None
//--------------------------------------------------
void SysModeResetDisplayState(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);
    EnumDDomainRegion enumDDomainRegion = ScalerRegionGetDDomainRegion(enumDisplayRegion);
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);

    EnumDBEnableStatus enumDBBackup = ScalerGlobalGetDBStatus(enumInputDataPath);

    // Disable Global Double Buffer, Only Enable D Domain DB
    ScalerGlobalResetDoubleBuffer(enumInputDataPath, enumDBBackup, _DISABLE);

    // Clear display state & event
    CLR_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex);
    CLR_RGN_DISPLAY_STATE(ucRegionIndex);
    CLR_RGN_DISPLAY_ACTION(ucRegionIndex);

    //=========================================================================
    // Reset D-domain
    //=========================================================================

    // Enable force background
    ScalerDDomainBackgroundEnable(enumDDomainRegion, _ENABLE);

    // Remove port mapping to display data path
    ScalerGlobalRemovePortMapping(GET_RGN_INPUT_PORT(ucRegionIndex), enumDDomainRegion);

    // Disable WD
    ScalerRegionSetWatchDog(enumDisplayRegion, _DISABLE);

    // Reset Ddomain Setting
    ScalerDDomainSetResetDdmRegion(enumDisplayRegion);

    switch(enumDisplayRegion)
    {
        case _DISPLAY_RGN_1P:
            SysModeSetFreeRun();

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
            ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_ALL_FUNCTION, ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_DDOMAIN == _ON)
            ScalerGlobalInterruptProcForDDomain(_GLOBAL_INT_DDOMAIN_ALL_FUNCTION, _DISABLE);
#endif
            break;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_PIP_MAIN:
#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
            ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_ALL_FUNCTION, ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);
#endif

#if((_PIP_TRANSPARENCY_SUPPORT == _ON) && (_EAGLE_SIGHT_SUPPORT == _OFF))
            // Disable PIP blending when main reset
            ScalerColorPIPBlendingLevelAdjust(0x00, _DB_APPLY_NO_POLLING);
#endif
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_RGN_EAGLE_SIGHT_MAIN:
#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
            ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_ALL_FUNCTION, ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);
#endif

#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
            // Disable Circle Window when Eagle Sight Support on
            if((GET_EAGLE_SIGHT_USER_ENABLE() == _ON) && (GET_EAGLE_SIGHT_USER_CIRCLE_WIN_ENABLE() == _ON))
            {
                ScalerColorPIPBlendingSetCircleWindowEnable(_FALSE, 0);
                ScalerColorHLWBorderEnable(_FALSE, _FALSE, _FALSE, _FALSE, _DB_APPLY_NONE);
            }
#endif
            // Disable Border Window when Eagle Sight support on
            UserCommonColorBorderWindowDisable(_DB_APPLY_NO_POLLING);
            break;

        case _DISPLAY_RGN_EAGLE_SIGHT_SUB:
#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
            ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_ALL_FUNCTION, ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);
#endif
            ScalerDDomainSetR2DenEnable(_ENABLE, _DB_APPLY_POLLING);
            break;
#endif

#if(_2P_DISPLAY_SUPPORT == _ON)
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_PIP_SUB:
#endif
#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_PBP_LR_EQUAL_LEFT:
        case _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT:
        case _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT:
        case _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT:
        case _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT:
        case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
#endif
#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_TOP:
        case _DISPLAY_RGN_BOTTOM:
#endif
#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
            ScalerGlobalInterruptProcForIDomain(_GLOBAL_INT_IDOMAIN_ALL_FUNCTION, ScalerRegionGetInputDataPath(enumDisplayRegion), _DISABLE);
#endif
            break;
#endif

        default:
            break;
    }

#if(_COLOR_DEMO_FUNCTION == _ON)
    if(UserCommonColorGetDemoModeType() != _DEMO_OFF)
    {
        if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN)
        {
            ScalerColorHLWBorderEnable(_FALSE, _FALSE, _FALSE, _FALSE, _DB_APPLY_NO_POLLING);
        }
        else
        {
            if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) == 0x00)
            {
                ScalerColorHLWBorderEnable(_FALSE, _FALSE, _FALSE, _FALSE, _DB_APPLY_NO_POLLING);
            }
        }
    }
#endif

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
    if((ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE) &&
       (ScalerRegionGetIndex(enumDisplayRegion) == _REGION_INDEX_0))
    {
        DWORD ulDclk = GET_D_CLK_FREQ();

        SET_MDOMAIN_OUTPUT_RGN(ScalerRegionGetDDomainRegion(enumDisplayRegion));
        SET_MODE_DISPLAY_TARGET_INDEX(_REGION_INDEX_0);
        SysModeDisplayTimingInitial(GET_DISPLAY_MODE(), GET_MODE_DISPLAY_TARGET_REGION());
        SET_MEMORY_CONFIG_SELECT(_FREE_RUN_NO_INPUT);
        SET_FS_ACTIVE_INFO_DVF_SELECT(_PANEL_TYP_FRAME_RATE_FREE_RUN);

        ScalerMDomainSetDisplayFormat(_FREE_RUN_NO_INPUT);

        if(ulDclk != GET_D_CLK_FREQ())
        {
#if(_PANEL_STYLE == _PANEL_VBO)
#if(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_RE_LINK_TRAIN)
            // Turn off backlight to prevent garbage
            UserCommonPowerPanelAction(_BACKLIGHT_OFF);
#elif(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_PANEL_OFF)
            // Turn off panel to prevent garbage
            UserCommonPowerPanelAction(_PANEL_OFF);
#endif
#elif(_PANEL_STYLE == _PANEL_DPTX)
#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
            // Turn off backlight to prevent garbage
            UserCommonPowerPanelAction(_BACKLIGHT_OFF);
#else
            // Turn off backlight to prevent garbage
            UserCommonPowerPanelAction(_PANEL_OFF);
#endif
#endif
        }
    }
#endif

    //=========================================================================
    // Reset M-domain
    //=========================================================================

#if((_OD_FUNCTION == _ON) && (_FRC_SUPPORT == _ON))
    // Release FRC bandwidth
    ScalerMDomainReleaseFRCMemoryBW(enumInputDataPath);

    // Check for reactivating OD function
    if(UserInterfaceColorGetODEnableStatus() == _FUNCTION_ON)
    {
        if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) != 0x00)
        {
            ScalerODInitial();
            UserCommonColorODEnable(_FUNCTION_ON);
        }
        else
        {
            UserCommonColorODEnable(_FUNCTION_OFF);
        }
    }
#endif

#if(_FRC_SUPPORT == _ON)
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
    ScalerFRCEOtoFBControl(enumInputDataPath, GET_MDOMAIN_INPUT_HWIDTH(), _DISABLE);
    ScalerFRCFBtoEOControl(enumInputDataPath, GET_MDOMAIN_INPUT_HWIDTH() / 2, _DISABLE);
#endif
    CLR_MDOMAIN_FRC_CTRL_PARAM_INDEX(ucRegionIndex);

#if(_TB_DISPLAY_MODE_SUPPORT == _ON)
    // 4P/ 3P-skew/ PBP_TB Top Display, Can't Disable FRC Display
    if(GET_FRC_TOP_BOTTOM_MODE_STATUS() == _TRUE)
    {
        ScalerFRCEn(_FRC_CAPTURE_ONOFF, enumInputDataPath, _DISABLE);
        ScalerFRCChannelMuteDTGEnable(enumInputDataPath, enumDDomainRegion, enumDisplayRegion, _DISABLE);

        ScalerFRCResetFBTBDisplayModeParam(enumInputDataPath);
    }
    else
#endif
#endif
    {
        // Disable FRC Capture and FRC Display
        ScalerFRCEn(_FRC_CAPTURE_ONOFF, enumInputDataPath, _DISABLE);
        ScalerFRCEn(_FRC_DISPLAY_ONOFF, enumInputDataPath, _DISABLE);
        // Disable DTG Active Region
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
        ScalerMDomainSetDisplayTimingGenActiveEnable(enumDDomainRegion, enumDisplayRegion, _DISABLE);
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    // Disable rotation
    ScalerRotationSetEnable(_DISABLE);
#endif

#if(_M_DOMAIN_IMG_CMP_SUPPORT == _ON)
#if(_HW_M_DOMAIN_IMG_CMP_TYPE == _M_DOMAIN_IMG_CMP_GEN_1)
    ScalerGlobalEnableUnderflowMonitor(_DISABLE, enumDDomainRegion);
#endif
#endif

#if(_FW_DISPLAYTOP_AVG_REQ_SUPPORT == _ON)
    ScalerDDomainSetDdmReqAvgReqEnable(enumDisplayRegion, _DISABLE);
#endif

    // Apply D-domain DB for FRC reset
    ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)enumDisplayRegion), _DB_APPLY_POLLING);

    // Restore Double Buffer Status
    ScalerGlobalResetDoubleBuffer(enumInputDataPath, enumDBBackup, _ENABLE);
}

//--------------------------------------------------
// Description  : Data path reset process
// Input Value  : ucRegionIndex --> region index
// Output Value : None
//--------------------------------------------------
void SysModeResetDataPath(BYTE ucRegionIndex)
{
    if(ucRegionIndex >= _MULTI_DISPLAY_MAX)
    {
        ucRegionIndex = _REGION_INDEX_0;
    }

    EnumDisplayRegion enumDisplayRegion = GET_RGN_DISPLAY_REGION(ucRegionIndex);
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
    EnumDBEnableStatus enumDBBackup = ScalerGlobalGetDBStatus(enumInputDataPath);

    DebugMessageSystem("Reset index", ucRegionIndex);
    DebugMessageSystem("Reset region", enumDisplayRegion);
    DebugMessageSystem("Reset port", GET_RGN_INPUT_PORT(ucRegionIndex));
    DebugMessageSystem("Reset port type", SysSourceGetPortTypeFromInputPort(GET_RGN_INPUT_PORT(ucRegionIndex)));

    // Disable Global Double Buffer, Only Enable D Domain DB
    ScalerGlobalResetDoubleBuffer(enumInputDataPath, enumDBBackup, _DISABLE);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
    // Disable VGIP Double Buffer
    ScalerVgipDoubleBufferEnable(enumInputDataPath, _DISABLE);
#endif

    //=========================================================================
    // Reset user/OSD functions
    //=========================================================================
    UserCommonModeResetRegionProc(enumDisplayRegion);

    //=========================================================================
    // Reset D-domain & M-domain
    //=========================================================================
    SysModeResetDisplayState(enumDisplayRegion);

    //=========================================================================
    // Reset Color
    //=========================================================================
    UserCommonColorResetColor(enumDisplayRegion);

    //=========================================================================
    // Reset I-domain
    //=========================================================================

    // Clear I-domain events
    CLR_RGN_TIMING_CONFIRM(ucRegionIndex);
    CLR_RGN_MEASURE_CHECKING(ucRegionIndex);

    // Reset data path
    ScalerIDomainResetDataPath(enumInputDataPath);

    //=========================================================================
    // Reset Interface
    //=========================================================================
    SysSourceResetRegion(ucRegionIndex);

    // Clear No Wait For Active Flag
    CLR_RGN_FIRST_ACTIVE(ucRegionIndex);

    //=========================================================================
    // Reset System Flow
    //=========================================================================

    // Cancle display setting if currently performing
    if((GET_MODE_STATE() == _MODE_STATUS_DISPLAY_SETTING) &&
       (GET_MODE_DISPLAY_TARGET_INDEX() == ucRegionIndex))
    {
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

        // Clear Mode Active Ready Flag
        CLR_MODE_ACTIVE_READY();

        // Reset to display check
        SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_CHECK);
    }

    // Restore Double Buffer Status
    ScalerGlobalResetDoubleBuffer(enumInputDataPath, enumDBBackup, _ENABLE);
}

//--------------------------------------------------
// Description  : Set Free Run Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeSetFreeRun(void)
{
    EnumDisplayMode enumDisplayModeBackup = GET_DISPLAY_MODE();

    DWORD ulDclk = GET_D_CLK_FREQ();

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        // Reset extension
        ScalerGlobalResetExtension();
    }
#endif

    // Set D Domain Timing
    SysModeDisplayTimingInitial(_DISPLAY_MODE_1P, _DISPLAY_RGN_1P);

    SET_DISPLAY_MODE(_DISPLAY_MODE_1P);
    SET_FORCE_DISPLAY_1P_MODE(_TRUE);
    SET_MDOMAIN_OUTPUT_RGN(ScalerRegionGetDDomainRegion(_DISPLAY_RGN_1P));
    SET_MEMORY_CONFIG_SELECT(_FREE_RUN_NO_INPUT);
    SET_FS_ACTIVE_INFO_DVF_SELECT(_PANEL_TYP_FRAME_RATE_FREE_RUN);

    ScalerMDomainSetDisplayFormat(_FREE_RUN_NO_INPUT);
    SET_DISPLAY_MODE(enumDisplayModeBackup);

    // Set Display Conversion Line Length
    ScalerDDomainSetDspcLineLength();

    // Enable Spread Spectrum
    ScalerPLLSetDPLLSSC(_DCLK_SPREAD_SPEED, _DCLK_SPREAD_RANGE);

    if(ulDclk != GET_D_CLK_FREQ())
    {
#if(_PANEL_STYLE == _PANEL_VBO)
#if(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_RE_LINK_TRAIN)
        // Turn off backlight to prevent garbage
        UserCommonPowerPanelAction(_BACKLIGHT_OFF);
#elif(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_PANEL_OFF)
        // Turn off panel to prevent garbage
        UserCommonPowerPanelAction(_PANEL_OFF);
#endif
#elif(_PANEL_STYLE == _PANEL_DPTX)
#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
        // Turn off backlight to prevent garbage
        UserCommonPowerPanelAction(_BACKLIGHT_OFF);
#else
        // Turn off backlight to prevent garbage
        UserCommonPowerPanelAction(_PANEL_OFF);
#endif
#endif
    }

    // Apply DB
    ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)GET_MODE_DISPLAY_TARGET_REGION()), _DB_APPLY_POLLING);
}

//--------------------------------------------------
// Description  : Mode State Change Flag for other layer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysModeGetModeStateChange(void)
{
    return GET_MODE_STATE_CHANGE_OSD();
}

//--------------------------------------------------
// Description  : Set Reset Status for User
// Input Value  : Target Reset State
// Output Value : None
//--------------------------------------------------
void SysModeSetResetTarget(EnumModeAction enumResetTarget)
{
    if(GET_MODE_STATE() == _MODE_STATUS_INITIAL)
    {
        return;
    }

    SET_MODE_RESET_TARGET(enumResetTarget);
}

//--------------------------------------------------
// Description  : Give Display Timing Initial Value
// Input Value  : enumDisplayMode --> current display mode
// Output Value : DVS height
//--------------------------------------------------
WORD SysModeGetDisplayVSHeight(EnumDisplayMode enumDisplayMode)
{
    enumDisplayMode = enumDisplayMode;

#if((_DP_FREESYNC_SUPPORT == _ON) || (_DSC_MAC_DECODER_SUPPORT == _ON))
#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    if(enumDisplayMode == _DISPLAY_MODE_1P)
    {
        BYTE ucSearchIndex = GET_RGN_SOURCE_INDEX(0);

        if((GET_SOURCE_JUDGE(ucSearchIndex) == _TRUE) &&
           (ScalerDrrIVSProduceByBE(GET_RGN_SOURCE_TYPE(_REGION_INDEX_0), GET_RGN_INPUT_PORT(ScalerRegionGetIndex(_DISPLAY_RGN_1P))) == _TRUE))
        {
            return _DP_SMALL_DV_SYNC_HEIGHT;
        }
    }
#endif

    return _PANEL_DV_SYNC_HEIGHT;
}


//--------------------------------------------------
// Description  : Give Display Timing Initial Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeDisplayTimingInitial(EnumDisplayMode enumDisplayMode, EnumDisplayRegion enumDisplayRegion)
{
    StructTimingFormat stTimingFormat = {0};
    StructHVBActiveDiff stHVBActiveDiff = {0};

    ScalerDDomainGetHVBActiveDiff(enumDisplayRegion, &stHVBActiveDiff);

    stTimingFormat = stTimingFormat;
    enumDisplayRegion = enumDisplayRegion;

    SET_OUTPUT_VFREQ(_PANEL_TYP_FRAME_RATE);

    SET_MDOMAIN_OUTPUT_HTOTAL(_PANEL_DH_TOTAL - (_PANEL_DH_TOTAL % _PANEL_DHTOTAL_MULTIPLE));
    SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);
    SET_MDOMAIN_OUTPUT_VSYNCHEIGHT(SysModeGetDisplayVSHeight(enumDisplayMode));

    // Set Up Display Timing According to display mode
    switch(enumDisplayMode)
    {
        default:
        case _DISPLAY_MODE_1P:
            SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
            SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);

            SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT);
            SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
#if(_PANEL_ASYMMETRIC == _ON)
            SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT);
            SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + _PANEL_ASYMMETRIC_DUMMY_NUM_TOP);
#endif

            break;

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            UserInterfaceDisplayGetPbpTimingFormat(enumDisplayRegion, &stTimingFormat);
            // L/R
            SET_MDOMAIN_OUTPUT_HWIDTH(stTimingFormat.usHWidth);
            SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);

            SET_MDOMAIN_OUTPUT_HSTART(stTimingFormat.usHStart);
            SET_MDOMAIN_OUTPUT_VSTART(stTimingFormat.usVStart);
#if(_PANEL_ASYMMETRIC == _ON)
            SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT);
            SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + _PANEL_ASYMMETRIC_DUMMY_NUM_TOP);
#endif

            break;
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
            if(enumDisplayRegion == _DISPLAY_RGN_PIP_MAIN)
            {
                // MAIN
                SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
                SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);

                SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT);
                SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
            }
            else
            {
                // User adjust sub size
                UserInterfaceDisplayGetPipSubTimingFormat(&stTimingFormat);

                // SUB
                SET_MDOMAIN_OUTPUT_HWIDTH(stTimingFormat.usHWidth);
                SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);

                SET_MDOMAIN_OUTPUT_HSTART(stTimingFormat.usHStart);
                SET_MDOMAIN_OUTPUT_VSTART(stTimingFormat.usVStart);
            }
#if(_PANEL_ASYMMETRIC == _ON)
            SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT);
            SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + _PANEL_ASYMMETRIC_DUMMY_NUM_TOP);
#endif
            break;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            if(enumDisplayRegion == _DISPLAY_RGN_EAGLE_SIGHT_MAIN)
            {
                // MAIN
                SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
                SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);

                SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT);
                SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
            }
            else
            {
                // User adjust Eagle Sight Sub Size
                UserInterfaceDisplayGetEagleSightSubTimingFormat(&stTimingFormat);

                // SUB
                SET_MDOMAIN_OUTPUT_HWIDTH(stTimingFormat.usHWidth);
                SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);

                SET_MDOMAIN_OUTPUT_HSTART(stTimingFormat.usHStart);
                SET_MDOMAIN_OUTPUT_VSTART(stTimingFormat.usVStart);
            }
#if(_PANEL_ASYMMETRIC == _ON)
            SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT);
            SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + _PANEL_ASYMMETRIC_DUMMY_NUM_TOP);
#endif
            break;
#endif


#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:

            stTimingFormat.usVHeight = _PANEL_DV_HEIGHT / 2;

            SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
            SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
            SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);

            if(enumDisplayRegion == _DISPLAY_RGN_TOP)
            {
                SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
            }
            else
            {
                SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2);
            }
            break;
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:

            UserInterfaceDisplayGet3PFlagTimingFormat(enumDisplayRegion, &stTimingFormat);

            SET_MDOMAIN_OUTPUT_HWIDTH(stTimingFormat.usHWidth);
            SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);
            SET_MDOMAIN_OUTPUT_HSTART(stTimingFormat.usHStart);
            SET_MDOMAIN_OUTPUT_VSTART(stTimingFormat.usVStart);

            break;
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
        case _DISPLAY_MODE_3P_SKEW_R:
            UserInterfaceDisplayGet3PSkewLRTimingFormat(enumDisplayRegion, &stTimingFormat);

            SET_MDOMAIN_OUTPUT_HWIDTH(stTimingFormat.usHWidth);
            SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);

            SET_MDOMAIN_OUTPUT_HSTART(stTimingFormat.usHStart);
            SET_MDOMAIN_OUTPUT_VSTART(stTimingFormat.usVStart);

            break;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:

            stTimingFormat.usVHeight = _PANEL_DV_HEIGHT / 2;

            SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);

            switch(enumDisplayRegion)
            {
                case _DISPLAY_RGN_SKEW_T_MAIN:
                    // MAIN
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                    SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);

                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
                    break;

                case _DISPLAY_RGN_SKEW_T_LEFT:
                    // L
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                    SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH / 2);

                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START + GET_MDOMAIN_OUTPUT_VHEIGHT());
                    break;

                case _DISPLAY_RGN_SKEW_T_RIGHT:
                    // R
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START + (_PANEL_DH_WIDTH / 2));
                    SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH / 2);

                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START + GET_MDOMAIN_OUTPUT_VHEIGHT());
                    break;

                default:
                    break;
            }
            break;

        case _DISPLAY_MODE_3P_SKEW_B:

            stTimingFormat.usVHeight = _PANEL_DV_HEIGHT / 2;

            SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);

            switch(enumDisplayRegion)
            {
                case _DISPLAY_RGN_SKEW_B_MAIN:
                    // MAIN
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                    SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);

                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START + GET_MDOMAIN_OUTPUT_VHEIGHT());
                    break;

                case _DISPLAY_RGN_SKEW_B_LEFT:
                    // L
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                    SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH / 2);

                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
                    break;

                case _DISPLAY_RGN_SKEW_B_RIGHT:
                    // R
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START + (_PANEL_DH_WIDTH / 2));
                    SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH / 2);

                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
                    break;

                default:
                    break;
            }
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:

            stTimingFormat.usHWidth = _PANEL_DH_WIDTH / 2;
            stTimingFormat.usVHeight = _PANEL_DV_HEIGHT / 2;
            SET_MDOMAIN_OUTPUT_HWIDTH(stTimingFormat.usHWidth);
            SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);

            switch(enumDisplayRegion)
            {
                case _DISPLAY_RGN_LT:
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
                    break;

                case _DISPLAY_RGN_LB:
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2);
                    break;

                case _DISPLAY_RGN_RT:
                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START + _PANEL_DH_WIDTH / 2);
                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
                    break;

                case _DISPLAY_RGN_RB:

                    SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START + _PANEL_DH_WIDTH / 2);
                    SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START + _PANEL_DV_HEIGHT / 2);
                    break;

                default:
                    break;
            }
            break;
#endif
    }

    SET_MDOMAIN_OUTPUT_HBSTART(GET_MDOMAIN_OUTPUT_HSTART());
    SET_MDOMAIN_OUTPUT_HBWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH());

    SET_MDOMAIN_OUTPUT_VBHEIGHT(GET_MDOMAIN_OUTPUT_VHEIGHT());
    SET_MDOMAIN_OUTPUT_VBSTART(GET_MDOMAIN_OUTPUT_VSTART());



    if(stHVBActiveDiff.b1VBHeightDiff == _TRUE)
    {
        SET_MDOMAIN_OUTPUT_VBHEIGHT(_PANEL_DV_HEIGHT);
#if(_PANEL_ASYMMETRIC == _ON)
        SET_MDOMAIN_OUTPUT_VBHEIGHT(GET_MDOMAIN_OUTPUT_VBHEIGHT() + _PANEL_ASYMMETRIC_DUMMY_NUM_TOP + _PANEL_ASYMMETRIC_DUMMY_NUM_BOTTOM);
#endif
        SET_MDOMAIN_OUTPUT_VBSTART(_PANEL_DV_START);
    }

    if(stHVBActiveDiff.b1HBWidthDiff == _TRUE)
    {
        SET_MDOMAIN_OUTPUT_HBWIDTH(_PANEL_DH_WIDTH);

#if(_PANEL_ASYMMETRIC == _ON)
        SET_MDOMAIN_OUTPUT_HBWIDTH(GET_MDOMAIN_OUTPUT_HBWIDTH() + _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT + _PANEL_ASYMMETRIC_DUMMY_NUM_RIGHT);
#endif
        SET_MDOMAIN_OUTPUT_HBSTART(_PANEL_DH_START);
    }
    ScalerMDomainCheckDisplayFormat(enumDisplayRegion);
}

//--------------------------------------------------
// Description  : Set display settting target
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysModeSearchDisplayTarget(void)
{
    BYTE ucDisplayIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    // Skip display target search when mode reset is going to happen
    if(GET_MODE_RESET_TARGET() != _MODE_ACTION_NO_RESET_MODE)
    {
        return _FALSE;
    }

    // Search display target
    for(ucDisplayIndex = 0; ucDisplayIndex < ucRegionCount; ++ucDisplayIndex)
    {
        if((GET_RGN_TIMING_CONFIRM(ucDisplayIndex) == _TRUE) &&
           (GET_RGN_MEASURE_CHECKING(ucDisplayIndex) == _FALSE) &&
           (GET_RGN_DISPLAY_ACTION(ucDisplayIndex) == _DISPLAY_ACTION_NO_ACTION))
        {
#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_2P_FRAME_SYNC_DEBOUNCE_TIME != 0))
            if((ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE) &&
               (ucDisplayIndex == 1) &&
               (SysJudgeCheck2pFrameSyncDebounce() == _TRUE))
            {
                continue;
            }
#endif

            switch(GET_RGN_DISPLAY_STATE(ucDisplayIndex))
            {
                case _DISPLAY_STATE_NO_SIGNAL:

                    DebugMessageSystem("CHK: Display target reset", ucDisplayIndex);

                    // Perform user resume process
                    UserCommonModeResumeRegionProc(GET_RGN_DISPLAY_REGION(ucDisplayIndex));

                    // Reset display state
                    SET_RGN_DISPLAY_ACTION(ucDisplayIndex, _DISPLAY_ACTION_RESET_TO_NONE);

                    // Set new display target
                    SysModeSetDisplayTarget(GET_RGN_DISPLAY_REGION(ucDisplayIndex));

                    return _TRUE;

                case _DISPLAY_STATE_NONE:

                    // Set new display target
                    SysModeSetDisplayTarget(GET_RGN_DISPLAY_REGION(ucDisplayIndex));

                    return _TRUE;

                default:

                    break;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set select region for display setting
// Input Value  : display region
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
void SysModeSetDisplayTarget(EnumDisplayRegion enumDisplayRegion)
{
    SET_MODE_DISPLAY_TARGET_INDEX(ScalerRegionGetIndex(enumDisplayRegion));

    DebugMessageSystem("New display target", ScalerRegionGetIndex(enumDisplayRegion));
}

//--------------------------------------------------
// Description  : Get select region for display setting
// Input Value  : None
// Output Value : display region
//--------------------------------------------------
EnumDisplayRegion SysModeGetDisplayTarget(void)
{
    return GET_MODE_DISPLAY_TARGET_REGION();
}

//--------------------------------------------------
// Description  : Get system display mode
// Input Value  : None
// Output Value : display mode
//--------------------------------------------------
EnumDisplayMode SysModeGetDisplayMode(void)
{
    return GET_DISPLAY_MODE();
}

//--------------------------------------------------
// Description  : Set Multi P Memory Select
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeSetMtPMemorySelect(void)
{
#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
    bit bFixLastlineReset = _TRUE;
#endif

    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        SET_FORCE_DISPLAY_1P_MODE(_TRUE);
    }
    else
    {
#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))

        if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
        {
            BYTE ucMainIndex = _REGION_INDEX_0;
            BYTE ucSubIndex = _REGION_INDEX_1;

            if(GET_2P_FRAME_SYNC_MAIN() == _FALSE)
            {
                ucMainIndex = _REGION_INDEX_1;
                ucSubIndex = _REGION_INDEX_0;
            }

            if(GET_MODE_DISPLAY_TARGET_INDEX() == ucMainIndex)
            {
                if((GET_RGN_DISPLAY_STATE(ucSubIndex) == _DISPLAY_STATE_DISPLAY_READY) ||
                   (GET_RGN_DISPLAY_STATE(ucSubIndex) == _DISPLAY_STATE_ACTIVE) ||
                   ((GET_RGN_DISPLAY_STATE(ucSubIndex) == _DISPLAY_STATE_OOR) &&
                    (GET_RGN_TIMING_CONFIRM(ucSubIndex) == _TRUE)))
                {
                    SET_MTP_MEMORY_SELECT(_MAIN_DISPLAY_SETTING_SUB_READY);
                }
                else
                {
                    SET_MTP_MEMORY_SELECT(_MAIN_DISPLAY_SETTING_SUB_NONE);
                }
            }
            else if(GET_MODE_DISPLAY_TARGET_INDEX() == ucSubIndex)
            {
                if((GET_RGN_DISPLAY_STATE(ucMainIndex) == _DISPLAY_STATE_DISPLAY_READY) ||
                   (GET_RGN_DISPLAY_STATE(ucMainIndex) == _DISPLAY_STATE_ACTIVE) ||
                   ((GET_RGN_DISPLAY_STATE(ucMainIndex) == _DISPLAY_STATE_OOR) &&
                    (GET_RGN_TIMING_CONFIRM(ucMainIndex) == _TRUE)))
                {
                    SET_MTP_MEMORY_SELECT(_SUB_DISPLAY_SETTING_MAIN_READY);
                }
                else
                {
                    SET_MTP_MEMORY_SELECT(_SUB_DISPLAY_SETTING_MAIN_NONE);
                }
            }

            if(GET_2P_FRAME_SYNC_MAIN() == _TRUE)
            {
                switch(GET_MTP_MEMORY_SELECT())
                {
                    case _MAIN_DISPLAY_SETTING_SUB_NONE:

                        SET_FORCE_DISPLAY_1P_MODE(_TRUE);

                        break;

                    case _MAIN_DISPLAY_SETTING_SUB_READY:

                        // Main reset to display setting, e.g. Main select aspect ratio
                        if(ScalerMDomainGetFrameSyncMode() != _FREE_RUN_MODE)
                        {
                            SET_FORCE_DISPLAY_1P_MODE(_TRUE);
                        }
                        else
                        {
                            SET_FORCE_DISPLAY_1P_MODE(_FALSE);

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
                            bFixLastlineReset = _FALSE;
#endif
                        }

                        break;

                    case _SUB_DISPLAY_SETTING_MAIN_READY:

                        SET_FORCE_DISPLAY_1P_MODE(_FALSE);

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
                        bFixLastlineReset = _FALSE;
#endif
                        break;

                    default:
                        SET_FORCE_DISPLAY_1P_MODE(_FALSE);
                        break;
                }
            }
            else
            {
                switch(GET_MTP_MEMORY_SELECT())
                {
                    case _SUB_DISPLAY_SETTING_MAIN_NONE:
                        SET_FORCE_DISPLAY_1P_MODE(_TRUE);
                        break;

                    case _SUB_DISPLAY_SETTING_MAIN_READY:

                        // Sub reset to display setting, e.g. Sub select aspect ratio
                        if(ScalerMDomainGetFrameSyncMode() != _FREE_RUN_MODE)
                        {
                            SET_FORCE_DISPLAY_1P_MODE(_TRUE);
                        }
                        else
                        {
                            SET_FORCE_DISPLAY_1P_MODE(_FALSE);

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
                            bFixLastlineReset = _FALSE;
#endif
                        }

                        break;

                    case _MAIN_DISPLAY_SETTING_SUB_READY:

                        SET_FORCE_DISPLAY_1P_MODE(_FALSE);

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
                        bFixLastlineReset = _FALSE;
#endif
                        break;

                    default:
                        SET_FORCE_DISPLAY_1P_MODE(_FALSE);
                        break;
                }
            }
        }
        else
        {
            SET_MTP_MEMORY_SELECT(_MTP_FREE_RUN);
            SET_FORCE_DISPLAY_1P_MODE(_FALSE);
        }
#else
        SET_FORCE_DISPLAY_1P_MODE(_FALSE);

#endif
    }

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
    if(bFixLastlineReset == _TRUE)
    {
        ScalerMemorySetFramesyncFixLastlineEnable(_DISABLE);
    }
#endif
}

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Reset to Display Initial condition
// Input Value  : None
// Output Value : _TRUE: Reset, _FALSE: not reset
//--------------------------------------------------
bit SysModeResetToDisplayInitial(void)
{
#if(_FRC_SUPPORT == _ON)
    if(ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE)
    {
        if(GET_MODE_DISPLAY_TARGET_INDEX() == 0)
        {
            if((GET_RGN_DISPLAY_STATE(1) == _DISPLAY_STATE_DISPLAY_READY) ||
               (GET_RGN_DISPLAY_STATE(1) == _DISPLAY_STATE_ACTIVE) ||
               (GET_RGN_DISPLAY_STATE(1) == _DISPLAY_STATE_OOR))
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Set system display mode
// Input Value  : display mode
// Output Value : None
//--------------------------------------------------
void SysModeSetDisplayMode(EnumDisplayMode enumDisplayMode)
{
    // Update display mode
    SET_DISPLAY_MODE(enumDisplayMode);

    // Update region count
    SET_RGN_MAX_DISPLAY_REGION(ScalerRegionGetMaxRegionCount());
}

//--------------------------------------------------
// Description  : Check To Disable Global Double Buffer
// Input Value  : None
// Output Value : _TRUE: Disale Global Global Double Buffer
//--------------------------------------------------
bit SysModeCheckToDisableGlobalDoubleBuffer(void)
{
    if(ScalerGlobalGetDBStatus(GET_MDOMAIN_INPUT_DATA_PATH()) != _DB_DISABLE)
    {
        if(GET_FORCE_DISPLAY_1P_MODE() == _TRUE)
        {
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            if(GET_ROT_TYPE() != UserInterfaceDisplayGetRotationDegree())
            {
                return _TRUE;
            }
#endif

            if(GET_FS_ACTIVE_INFO_DVF_SELECT() != ScalerDisplaySelectDVFMode())
            {
                return _TRUE;
            }
        }
    }
    return _FALSE;
}

#if(_DRR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Drr Mdomain Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeDrrSetMdomainInfo(void)
{
    EnumInputPort enumInputPort = GET_RGN_INPUT_PORT(GET_MODE_DISPLAY_TARGET_INDEX());

#if(_FREESYNC_SUPPORT == _ON)
    ScalerDrrFreeSyncSpdInfoReceive(enumInputPort);
#endif

    ScalerDrrSetPanelVfeqInfo(enumInputPort);

    if(ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE)
    {
        WORD usIVfreq = 0;
        WORD usIVtotalFromIHFreq = 0;

        if(GET_DRR_VFREQ_MAX() == 590)
        {
            SET_DRR_VFREQ_MAX(600);
        }

        SET_DRR_VFREQ_MIN(GET_DRR_PANEL_MIN_FRAME_RATE());

#if(_SEARCH_DRR_IVF_PRIORITY_BY_USER == _ON)
        if(UserCommonDisplayGetDrrIVFPriority(enumInputPort, &usIVfreq) == _DRR_GET_IVF_PRIORITY_KERNEL)
#endif
        {
            usIVfreq = 0;

            if(ScalerDrrReceiveSourceIVF(enumInputPort, SysSourceGetPortTypeFromInputPort(enumInputPort), &usIVfreq) == _TRUE)
            {
                DebugMessageScaler("DRR Get IVF from Source info", GET_DRR_VFREQ_MAX());
            }
            else
            {
#if((_DT_RANGE_TEST_SUPPORT == _ON) && ((_DP_FORCE_FREESYNC_SUPPORT == _ON) || (_HDMI_FORCE_FREESYNC_SUPPORT == _ON)))
                usIVfreq = GET_MDOMAIN_INPUT_VFREQ();
                DebugMessageScaler("DRR DP HDMI Force Freesync Support ON", GET_MDOMAIN_INPUT_VFREQ());
#else
                usIVfreq = SysModeDrrGetIVFreq(enumInputPort);
#endif
            }
        }


        if(usIVfreq != 0)
        {
            usIVtotalFromIHFreq = ((DWORD)GET_MDOMAIN_INPUT_HFREQ() * 1000 / usIVfreq);
        }

        if((usIVfreq != 0) && (usIVtotalFromIHFreq > GET_MDOMAIN_INPUT_VHEIGHT()))
        {
            SET_DRR_IVF_INFO(_TRUE);
            SET_MDOMAIN_INPUT_VTOTAL(usIVtotalFromIHFreq);
        }
        else
        {
            // "usIVfreq = 0" or "GET_MDOMAIN_INPUT_VTOTAL() is unreasonable, usIVfreq and GET_MDOMAIN_INPUT_HFREQ() are not match"
            SET_DRR_IVF_INFO(_FALSE);
            SET_MDOMAIN_INPUT_VTOTAL((DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * 105 / 100);

            usIVfreq = ((DWORD)GET_MDOMAIN_INPUT_HFREQ() * 1000 / GET_MDOMAIN_INPUT_VHEIGHT());

            if(usIVfreq > GET_DRR_PANEL_MAX_FRAME_RATE())
            {
                usIVfreq = GET_DRR_PANEL_MAX_FRAME_RATE();
            }
        }

        DebugMessageScaler("DRR new Vfreq max", usIVfreq);
        SET_MDOMAIN_INPUT_VFREQ(usIVfreq);
    }
}

//--------------------------------------------------
// Description  : Get DRR IVF
// Input Value  : Input port, EnumDisplayRegion
// Output Value : IVF in DRR; 0 if not available
//--------------------------------------------------
WORD SysModeDrrGetIVFreq(EnumInputPort enumInputPort)
{
    if(ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE)
    {
        WORD usIVfreq = 0;
        EnumGetIVFFromTableSearch enumEdidScanResult = _TABLE_SEARCHING_WITHOUT_IVF_MAX;

        StructTableSearchingSourceInfo stSourceInfo;
        StructEdidInfo stCatchEdidInfo;
        StructTimingInfo stTimingInfo;
        memset(&stSourceInfo, 0, sizeof(stSourceInfo));
        memset(&stCatchEdidInfo, 0, sizeof(stCatchEdidInfo));
        memset(&stTimingInfo, 0, sizeof(StructTimingInfo));

        // Read timing info
        SysRegionGetMeasureResultByRegion(SysRegionGetDisplayRegion(SysRegionConvertPortToRegionIndex(enumInputPort)), &stTimingInfo);
        ScalerMDomainGetSourceInfoForTableSearch(enumInputPort, &stSourceInfo, &stTimingInfo);

        // ---------------------
        // Timing Scan from EDID
        // ---------------------
#if((_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE) && ((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI21_VRR_SUPPORT == _ON)))
        if((SysSourceGetPortTypeFromInputPort(enumInputPort) == _PORT_HDMI) && (UserCommonEdidCheckHdmiCurrentEdidLocation(enumInputPort) == _HDMI_EDID_EXTERNAL))
        {
            // current EDID is external
            BYTE pucReadArray[_EDID_EXTERNAL_EEPROM_MAX_SIZE] = {0};
            UserInterfaceEdidGetExternalEdid(enumInputPort, pucReadArray);

            enumEdidScanResult = ScalerMDomainEdidTimingInfoComparison(pucReadArray, &stSourceInfo, &stCatchEdidInfo, enumInputPort, &stTimingInfo);
        }
        else
#endif
        {
#if(_EMBEDDED_EDID_SUPPORT == _ON)
            // current EDID is embedded
            BYTE *pucReadArray = UserCommonEdidGetDDCRamAddress(enumInputPort);

            if(pucReadArray == _NULL_POINTER)
            {
                DebugMessageScaler("warning!!!!  Without EDID, Not Get IVF from EDID analysis", 0);
            }
            else
            {
                enumEdidScanResult = ScalerMDomainEdidTimingInfoComparison(pucReadArray, &stSourceInfo, &stCatchEdidInfo, enumInputPort, &stTimingInfo);
            }
#endif
        }

        if(enumEdidScanResult == _TABLE_SEARCHING_WITH_IVF_MAX)
        {
            usIVfreq = ((GET_DWORD_MUL_DIV(stCatchEdidInfo.usPixelClk, 1000000, stCatchEdidInfo.usVtotal) + (stCatchEdidInfo.usHtotal / 2)) / stCatchEdidInfo.usHtotal);
            DebugMessageScaler("DRR Get IVF from EDID analysis", usIVfreq);

            return usIVfreq;
        }
        else
        {
            DebugMessageScaler("warning!!!!  Not Get IVF from EDID analysis", 0);
        }


        // ---------------------
        // Timing Scan from CVT Cal -> User LUT
        // ---------------------
        // Get IVF Calculated by CVT, for QD980 (if EDID Scan not match)
        if(ScalerMDomainCalculateIVFmaxFromCVT(&usIVfreq, &stSourceInfo, enumInputPort, &stTimingInfo) == _TABLE_SEARCHING_WITH_IVF_MAX)
        {
            DebugMessageScaler("DRR Get IVF Calculated by CVT", usIVfreq);
            return usIVfreq;
        }

        // Get IVF from user info, if any
        if(UserCommonDisplayDrrGetIVFmax(&usIVfreq, enumInputPort) == _TABLE_SEARCHING_WITH_IVF_MAX)
        {
            DebugMessageScaler("DRR Get IVF from user define", usIVfreq);
            return usIVfreq;
        }
    }

    DebugMessageScaler("DRR not Get IVF", 0);
    return 0;
}
#endif

#if(_HDMI21_FVA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set HDMI21 Mdomain Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeHDMI21SetMdomainInfo(void)
{
    EnumInputPort enumInputPort = GET_RGN_INPUT_PORT(GET_MODE_DISPLAY_TARGET_INDEX());
    BYTE ucFvaFactor = ScalerTmdsMacRxHdmi21GetFvaFactor(enumInputPort);

    SET_HDMI21_FVA_ENABLE(_FALSE);
    SET_HDMI21_FVA_IVF_INFO(_FALSE);

    switch(SysSourceGetPortTypeFromInputPort(enumInputPort))
    {
        case _PORT_HDMI:
        case _PORT_HDMI20:
            // Current HDMI Port with FVA feature incoming
            if(ucFvaFactor > 0x01)
            {
                WORD usIVfreq = SysModeHdmi21GetFvaMaxIVf(enumInputPort);
#if(_DRR_SUPPORT == _ON)
                WORD usPanelMaxFrameRate = GET_DRR_PANEL_MAX_FRAME_RATE();
#endif
                SET_HDMI21_FVA_ENABLE(_TRUE);

                // FVA get IVF from EDID
                if(usIVfreq != 0)
                {
                    DebugMessageScaler("FVA Get IVF", 0);

                    SET_HDMI21_FVA_IVF_INFO(_TRUE);
                }
                else
                {
                    DebugMessageScaler("FVA not Get IVF", 0);

                    // Due to No EDID Timing catch, Predict Max Vfreq multiple by fva_factor
                    usIVfreq = (GET_MDOMAIN_INPUT_VFREQ() * ucFvaFactor);
                }

#if(_DRR_SUPPORT == _ON)
                if((ScalerDrrGetType(enumInputPort) != _DRR_NONE_TYPE) &&
                   (usIVfreq > usPanelMaxFrameRate))
                {
                    usIVfreq = usPanelMaxFrameRate;
                    DebugMessageScaler("Warning!!!! IVF * FVA_factor larger then Panel Vfreq", 0);
                }
#endif

                DebugMessageScaler("FVA IVfreq", usIVfreq);

                SET_MDOMAIN_INPUT_VFREQ(usIVfreq);
                SET_MDOMAIN_INPUT_VTOTAL((DWORD)GET_MDOMAIN_INPUT_HFREQ() * 1000 / GET_MDOMAIN_INPUT_VFREQ());
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get HDMI21 FVA IVF
// Input Value  : None
// Output Value : FVA IVF
//--------------------------------------------------
WORD SysModeHdmi21GetFvaMaxIVf(EnumInputPort enumInputPort)
{
    WORD usIVfreq = 0;
    BYTE ucFvaFactor = ScalerTmdsMacRxHdmi21GetFvaFactor(enumInputPort);
    EnumGetIVFFromTableSearch enumEdidScanResult = _TABLE_SEARCHING_WITHOUT_IVF_MAX;

    StructTableSearchingSourceInfo stSourceInfo;
    StructEdidInfo stCatchEdidInfo;
    StructTimingInfo stTimingInfo;
    memset(&stSourceInfo, 0, sizeof(stSourceInfo));
    memset(&stCatchEdidInfo, 0, sizeof(stCatchEdidInfo));
    memset(&stTimingInfo, 0, sizeof(StructTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(SysRegionGetDisplayRegion(SysRegionConvertPortToRegionIndex(enumInputPort)), &stTimingInfo);
    ScalerMDomainGetSourceInfoForTableSearch(enumInputPort, &stSourceInfo, &stTimingInfo);

    // ---------------------
    // Timing Scan from EDID
    // ---------------------
#if(_EDID_EXTERNAL_EEPROM_MAX_SIZE != _EDID_SIZE_NONE)
    if((SysSourceGetPortTypeFromInputPort(enumInputPort) == _PORT_HDMI) && (UserCommonEdidCheckHdmiCurrentEdidLocation(enumInputPort) == _HDMI_EDID_EXTERNAL))
    {
        // current EDID is external
        BYTE pucReadArray[_EDID_EXTERNAL_EEPROM_MAX_SIZE] = {0};
        UserInterfaceEdidGetExternalEdid(enumInputPort, pucReadArray);

        enumEdidScanResult = ScalerMDomainEdidTimingInfoComparison(pucReadArray, &stSourceInfo, &stCatchEdidInfo, enumInputPort, &stTimingInfo);
    }
    else
#endif
    {
        // current EDID is embedded
        BYTE *pucReadArray = UserCommonEdidGetDDCRamAddress(enumInputPort);

        if(pucReadArray == _NULL_POINTER)
        {
            DebugMessageScaler("warning!!!!  Without EDID, Not Get IVF from EDID analysis", 0);
        }
        else
        {
            enumEdidScanResult = ScalerMDomainEdidTimingInfoComparison(pucReadArray, &stSourceInfo, &stCatchEdidInfo, enumInputPort, &stTimingInfo);
        }
    }

    // Get IVF from EDID info
    if(enumEdidScanResult == _TABLE_SEARCHING_WITH_IVF_MAX)
    {
        usIVfreq = ScalerTmdsMacRxCalFvaVfreqMax(&stCatchEdidInfo, ucFvaFactor);

        DebugMessageScaler("Predict IVF from EDID analysis", usIVfreq);
    }
    else
    {
        // ---------------------
        // Timing Scan from CVT Cal -> User LUT
        // ---------------------
        StructEdidInfo stCatchTimingInfo;
        memset(&stCatchTimingInfo, 0, sizeof(stCatchTimingInfo));

        // Get IVF Calculated by CVT, for QD980
        if(ScalerMDomainCalculateIVFmaxFromCVT(&usIVfreq, &stSourceInfo, enumInputPort, &stTimingInfo) == _TABLE_SEARCHING_WITH_IVF_MAX)
        {
            SysModeHdmi21GetFvaTimingInfo(usIVfreq, &stCatchTimingInfo, enumInputPort, &stTimingInfo);

            usIVfreq = ScalerTmdsMacRxCalFvaVfreqMax(&stCatchTimingInfo, ucFvaFactor);

            DebugMessageScaler("DRR Get IVF Calculated by CVT", usIVfreq);
            return usIVfreq;
        }

        // Get IVF from user info, if any
        if(UserCommonDisplayDrrGetIVFmax(&usIVfreq, enumInputPort) == _TABLE_SEARCHING_WITH_IVF_MAX)
        {
            SysModeHdmi21GetFvaTimingInfo(usIVfreq, &stCatchTimingInfo, enumInputPort, &stTimingInfo);

            usIVfreq = ScalerTmdsMacRxCalFvaVfreqMax(&stCatchTimingInfo, ucFvaFactor);

            DebugMessageScaler("DRR Get IVF from user define", usIVfreq);
            return usIVfreq;
        }
    }

    return usIVfreq;
}

//--------------------------------------------------
// Description  : Get HDMI21 FVA Timing Info for Calculate IVFmax
// Input Value  : IVFmax, pstCatchTimingInfo, enumInputPort
// Output Value : none
//--------------------------------------------------
void SysModeHdmi21GetFvaTimingInfo(WORD usVfreqMax, StructEdidInfo *pstCatchTimingInfo, EnumInputPort enumInputPort, StructTimingInfo *pstTimingInfo)
{
    pstCatchTimingInfo->usHtotal = pstTimingInfo->usHTotal;
    pstCatchTimingInfo->usVtotal = ((DWORD)pstTimingInfo->usHFreq * 1000 / usVfreqMax);
    pstCatchTimingInfo->usVheight = pstTimingInfo->usVHeight;
    pstCatchTimingInfo->usPixelClk = ScalerSyncGetNativeInputPixelClk(enumInputPort);
}
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Eagle Sight Support
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeSetEagleSightSupport(void)
{
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        SET_RGN_SOURCE_INDEX(_REGION_INDEX_1, GET_RGN_SOURCE_INDEX(_REGION_INDEX_0));
        SysModeEagleSightGetUserSetting();
    }
}

//--------------------------------------------------
// Description  : Eagle Sight Display Setting: Input Capture
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeEagleSightInputCapture(void)
{
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT) &&
       (GET_MDOMAIN_INPUT_DATA_PATH() == ScalerRegionGetInputDataPath(_DISPLAY_RGN_EAGLE_SIGHT_SUB)))
    {
        StructEagleSightPosition stInputTiming = {0};
        StructEagleSightPosition stEagleSightPosition = {0};

        stInputTiming.usVstart = GET_INPUT_TIMING_VSTART();
        stInputTiming.usVheight = GET_INPUT_TIMING_VHEIGHT();

        WORD usHwidthDiff = 0;
        WORD usVHeightDiff = 0;

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
        if(ScalerFmtCnvEagleSightEnableStatus() == _TRUE)
        {
            stInputTiming.usHstart = 0;
            stInputTiming.usHwidth = ScalerIDomainGetInputHorTimingAfterFmtCnv(g_pstMeasureRegionTimingInfo[_REGION_INDEX_0].stTimingInfo.usHWidth, GET_MDOMAIN_INPUT_DATA_PATH());
        }
        else
#endif
        {
            stInputTiming.usHstart = ScalerIDomainGetInputHorTimingAfterFmtCnv(GET_INPUT_TIMING_HSTART(), GET_MDOMAIN_INPUT_DATA_PATH());
            stInputTiming.usHwidth = ScalerIDomainGetInputHorTimingAfterFmtCnv(GET_INPUT_TIMING_HWIDTH(), GET_MDOMAIN_INPUT_DATA_PATH());
        }

#if(_OVERSCAN_SUPPORT == _ON)
        if(stInputTiming.usHwidth > g_stMDomainFSActiveInfo.stMDomainFSActiveInputData.usHWidth)
        {
            usHwidthDiff = ((stInputTiming.usHwidth - g_stMDomainFSActiveInfo.stMDomainFSActiveInputData.usHWidth) / 2);
        }

        if(stInputTiming.usVheight > GET_MDOMAIN_INPUT_VHEIGHT())
        {
            usVHeightDiff = ((stInputTiming.usVheight - GET_MDOMAIN_INPUT_VHEIGHT()) / 2);
        }
#endif
        stEagleSightPosition.usHstart = stInputTiming.usHstart;
        stEagleSightPosition.usVstart = stInputTiming.usVstart;
        stEagleSightPosition.usHwidth = stInputTiming.usHwidth;
        stEagleSightPosition.usVheight = stInputTiming.usVheight;

        if(GET_EAGLE_SIGHT_USER_CAP_POS() == _EAGLE_SIGHT_CAP_POSITION_USER)
        {
            // User define Eagle Sight Input Capture Position
            UserInterfaceDisplayAdjustEagleSightInputCapturePosition(&stEagleSightPosition);
        }
        else
        {
            stEagleSightPosition.usHwidth = (stEagleSightPosition.usHwidth >> 2);
            stEagleSightPosition.usVheight = (stEagleSightPosition.usVheight >> 2);

            switch(GET_EAGLE_SIGHT_USER_RATIO())
            {
                case _EAGLE_SIGHT_RATIO_1_5:
                default:
                    stEagleSightPosition.usHwidth = stEagleSightPosition.usHwidth * 2 / 3;
                    stEagleSightPosition.usVheight = stEagleSightPosition.usVheight * 2 / 3;
                    break;

                case _EAGLE_SIGHT_RATIO_2_0:
                    stEagleSightPosition.usHwidth = stEagleSightPosition.usHwidth / 2;
                    stEagleSightPosition.usVheight = stEagleSightPosition.usVheight / 2;
                    break;

                case _EAGLE_SIGHT_RATIO_3_0:
                    stEagleSightPosition.usHwidth = stEagleSightPosition.usHwidth / 3;
                    stEagleSightPosition.usVheight = stEagleSightPosition.usVheight / 3;
                    break;

                case _EAGLE_SIGHT_RATIO_4_0:
                    stEagleSightPosition.usHwidth = stEagleSightPosition.usHwidth / 4;
                    stEagleSightPosition.usVheight = stEagleSightPosition.usVheight / 4;
                    break;
            }

            stEagleSightPosition.usHwidth &= 0xFFFC;
            stEagleSightPosition.usVheight &= 0xFFFC;

            switch(GET_EAGLE_SIGHT_USER_CAP_POS())
            {
                case _EAGLE_SIGHT_CAP_TOP_LEFT:
                    stEagleSightPosition.usHstart += usHwidthDiff;
                    stEagleSightPosition.usVstart += usVHeightDiff;
                    break;

                case _EAGLE_SIGHT_CAP_BOT_LEFT:
                    stEagleSightPosition.usHstart += usHwidthDiff;
                    stEagleSightPosition.usVstart += (stInputTiming.usVheight - stEagleSightPosition.usVheight) - usVHeightDiff;
                    break;

                case _EAGLE_SIGHT_CAP_TOP_RIGHT:
                    stEagleSightPosition.usHstart += (stInputTiming.usHwidth - stEagleSightPosition.usHwidth) - usHwidthDiff;
                    stEagleSightPosition.usVstart += usVHeightDiff;
                    break;

                case _EAGLE_SIGHT_CAP_BOT_RIGHT:
                    stEagleSightPosition.usHstart += (stInputTiming.usHwidth - stEagleSightPosition.usHwidth) - usHwidthDiff;
                    stEagleSightPosition.usVstart += (stInputTiming.usVheight - stEagleSightPosition.usVheight) - usVHeightDiff;
                    break;

                case _EAGLE_SIGHT_CAP_POSITION_USER:

                    stEagleSightPosition.usHwidth = stInputTiming.usHwidth;
                    stEagleSightPosition.usVheight = stInputTiming.usVheight;

                    // User define Eagle Sight Input Capture Position
                    UserInterfaceDisplayAdjustEagleSightInputCapturePosition(&stEagleSightPosition);
                    break;

                case _EAGLE_SIGHT_CAP_CENTER:
                default:
                    stEagleSightPosition.usHstart += ((stInputTiming.usHwidth - stEagleSightPosition.usHwidth) / 2);
                    stEagleSightPosition.usVstart += ((stInputTiming.usVheight - stEagleSightPosition.usVheight) / 2);
                    break;
            }
        }

        SET_MDOMAIN_INPUT_VHEIGHT(stEagleSightPosition.usVheight);
        SET_MDOMAIN_INPUT_VSTART(stEagleSightPosition.usVstart);

#if(_COLOR_IP_FC_EAGLESIGHT_SUPPORT == _ON)
        if(ScalerFmtCnvEagleSightEnableStatus() == _TRUE)
        {
            if(ScalerFmtCnvEagleSightGetPixelMode() != _FC_1_PIXEL_MODE)
            {
                if(stEagleSightPosition.usHwidth > (stInputTiming.usHwidth / 2))
                {
                    // Avoid capture den overlap capture hsync
                    stEagleSightPosition.usHwidth = stInputTiming.usHwidth / 2;
                }
            }

            if(stEagleSightPosition.usHwidth > _FC_CAPTURE_HWIDTH)
            {
                stEagleSightPosition.usHwidth = _FC_CAPTURE_HWIDTH;
            }

            if(ScalerFmtCnvEagleSightGetCaptureWidth() != stEagleSightPosition.usHwidth)
            {
                ScalerFmtCnvEagleSightSetCaptureWidth(stEagleSightPosition.usHwidth);
            }

            SET_MDOMAIN_INPUT_HWIDTH(ScalerFmtCnvEagleSightGetCaptureWidth());
#if(_HW_FORMAT_CONVERSION_EO_MODE == _ON)
#if((_HW_FORMAT_CONVERSION_PATH4_SUPPORT == _ON) && (_HW_FORMAT_CONVERSION_PATH5_SUPPORT == _ON))
            ScalerFmtCnvP4P5SetEvenOddHwidth(GET_MDOMAIN_INPUT_HWIDTH());
#endif
#endif

            if(ScalerFmtCnvEagleSightGetCaptureStart() != stEagleSightPosition.usHstart)
            {
                ScalerFmtCnvEagleSightSetCaptureStart(stEagleSightPosition.usHstart);
                ScalerFmtCnvEagleSightSetSyncDelay(stEagleSightPosition.usHstart);
            }
        }
        else
#endif
        {
            SET_MDOMAIN_INPUT_HWIDTH(stEagleSightPosition.usHwidth);
            SET_MDOMAIN_INPUT_HSTART(stEagleSightPosition.usHstart);
        }
    }
}

//--------------------------------------------------
// Description  : Eagle Sight Display Setting: Output Capture
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeEagleSightDisplayCapture(void)
{
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT) &&
       (GET_MDOMAIN_INPUT_DATA_PATH() == ScalerRegionGetInputDataPath(_DISPLAY_RGN_EAGLE_SIGHT_SUB)))
    {
        StructEagleSightPosition stEagleSightPosition = {0};

        stEagleSightPosition.usHstart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_START);
        stEagleSightPosition.usVstart = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START);
        stEagleSightPosition.usHwidth = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_WIDTH) >> 2);
        stEagleSightPosition.usVheight = (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_HEIGHT) >> 2);

        stEagleSightPosition.usHwidth &= 0xFFFC;
        stEagleSightPosition.usVheight &= 0xFFFC;

        switch(GET_EAGLE_SIGHT_USER_DISP_POS())
        {
            case _EAGLE_SIGHT_DISP_TOP_LEFT:
                break;

            case _EAGLE_SIGHT_DISP_BOT_LEFT:
                stEagleSightPosition.usVstart += (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_HEIGHT) - stEagleSightPosition.usVheight);
                break;

            case _EAGLE_SIGHT_DISP_TOP_RIGHT:
                stEagleSightPosition.usHstart += (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_WIDTH) - stEagleSightPosition.usHwidth);
                break;

            case _EAGLE_SIGHT_DISP_BOT_RIGHT:
                stEagleSightPosition.usHstart += (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_WIDTH) - stEagleSightPosition.usHwidth);
                stEagleSightPosition.usVstart += (ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_HEIGHT) - stEagleSightPosition.usVheight);
                break;

            case _EAGLE_SIGHT_DISP_POSITION_USER:

                stEagleSightPosition.usHwidth = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_WIDTH);
                stEagleSightPosition.usVheight = ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_HEIGHT);

                // User define Eagle Sight Display Capture Position
                UserInterfaceDisplayAdjustEagleSightDisplayCapturePosition(&stEagleSightPosition);
                break;

            case _EAGLE_SIGHT_DISP_CENTER:
            default:
                stEagleSightPosition.usHstart += ((ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_WIDTH) - stEagleSightPosition.usHwidth) / 2);
                stEagleSightPosition.usVstart += ((ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_HEIGHT) - stEagleSightPosition.usVheight) / 2);
                break;
        }

        SET_MDOMAIN_OUTPUT_HWIDTH(stEagleSightPosition.usHwidth);
        SET_MDOMAIN_OUTPUT_VHEIGHT(stEagleSightPosition.usVheight);

        SET_MDOMAIN_OUTPUT_HSTART(stEagleSightPosition.usHstart);
        SET_MDOMAIN_OUTPUT_VSTART(stEagleSightPosition.usVstart);

        SET_MDOMAIN_OUTPUT_HBWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH());
        SET_MDOMAIN_OUTPUT_VBHEIGHT(GET_MDOMAIN_OUTPUT_VHEIGHT());

        SET_MDOMAIN_OUTPUT_HBSTART(GET_MDOMAIN_OUTPUT_HSTART());
        SET_MDOMAIN_OUTPUT_VBSTART(GET_MDOMAIN_OUTPUT_VSTART());

        // Check resoultion constraint
        ScalerMDomainCheckDisplayFormat(_DISPLAY_RGN_EAGLE_SIGHT_SUB);

#if(_HW_D_DOMAIN_R2_A1_ACTIVE_SUPPORT == _ON)
        ScalerMDomainSetActiveRegion_R2a1();
#endif

#if(_HW_D_DOMAIN_R2_BACKGROUND_SUPPORT == _ON)
        ScalerMDomainSetBackground_R2();
#endif

        if(ScalerGlobalGetDDomainDBStatus() == _ENABLE)
        {
            if(ScalerDDomainGetR2DenEnable() == _ENABLE)
            {
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
                UserCommonColorCircleWindowAdjust(_DB_APPLY_NONE);
#else
#if(_COLOR_IP_HL_WIN == _ON)
                UserCommonColorHLWinTypeAdjust(_DB_APPLY_NONE);
#endif
                UserCommonColorBorderWindowAdjust(_DB_APPLY_NONE);
#endif
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get Eagle Sight User Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysModeEagleSightGetUserSetting(void)
{
    StructEagleSightSetting stEagleSightSetting =
    {
        _EAGLE_SIGHT_SETTING_DISABLE,
        _EAGLE_SIGHT_RATIO_1_5,
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
        _EAGLE_SIGHT_CIRCLE_WIN_DISABLE,
#endif
        _EAGLE_SIGHT_CAP_CENTER,
        _EAGLE_SIGHT_DISP_CENTER,
        0xFF,
    };

    UserInterfaceDisplaySetEagleSightSettingDefault(&stEagleSightSetting);

    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        UserInterfaceDisplayGetEagleSightSetting(&stEagleSightSetting);
    }

    SET_EAGLE_SIGHT_USER_ENABLE(stEagleSightSetting.enumEagleSightEnable);
    SET_EAGLE_SIGHT_USER_RATIO(stEagleSightSetting.enumEagleSightRatio);
    SET_EAGLE_SIGHT_USER_CAP_POS(stEagleSightSetting.enumEagleSightCapPosition);
    SET_EAGLE_SIGHT_USER_DISP_POS(stEagleSightSetting.enumEagleSightDispPosition);
    SET_EAGLE_SIGHT_USER_TRANSPARENCY(stEagleSightSetting.ucTransparencyLevel);
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
    SET_EAGLE_SIGHT_USER_CIRCLE_WIN_ENABLE(stEagleSightSetting.enumEagleSightCircleWinEnable);
#endif

    DebugMessageScaler("Eagle sight user eanble", GET_EAGLE_SIGHT_USER_ENABLE());
    DebugMessageScaler("Eagle sight user ratio", GET_EAGLE_SIGHT_USER_RATIO());
    DebugMessageScaler("Eagle sight user capture position", GET_EAGLE_SIGHT_USER_CAP_POS());
    DebugMessageScaler("Eagle sight user display position", GET_EAGLE_SIGHT_USER_DISP_POS());
    DebugMessageScaler("Eagle sight user transparency", GET_EAGLE_SIGHT_USER_TRANSPARENCY());
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
    DebugMessageScaler("Eagle sight user circle window", GET_EAGLE_SIGHT_USER_CIRCLE_WIN_ENABLE());
#endif
}
#endif

//--------------------------------------------------
// Description  : Select Memory Data Bit
// Input Value  : enumMemoryDataBitSelect
// Output Value : ucColorDepth Bit
//--------------------------------------------------
BYTE SysModeSelectMemoryDataBit(EnumMemoryDataBitSelect enumMemoryDataBitSelect)
{
#if((_DT_RANGE_TEST_SUPPORT == _ON) && (_DT_TEST_FORCE_10_BITS == _ON))

    enumMemoryDataBitSelect = enumMemoryDataBitSelect;
    return _COLOR_DEPTH_10_BITS;

#else

    switch(enumMemoryDataBitSelect)
    {
        case _MEMORY_REF_SOURCE_BIT:
        default:
            return (ScalerColorGetColorDepth(GET_RGN_INPUT_PORT(GET_MODE_DISPLAY_TARGET_INDEX())));

#if(_BW_CUSTOME_MODE == _ENABLE)
        case _MEMORY_FORCE_8_BIT:
            return _COLOR_DEPTH_8_BITS;

        case _MEMORY_FORCE_10_BIT:
            return _COLOR_DEPTH_10_BITS;
#endif
    }

#endif
}

