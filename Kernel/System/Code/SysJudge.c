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
// ID Code      : SysJudge.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_JUDGE__

#include "SysInclude.h"
#include "Judge/SysJudge.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_2P_FRAME_SYNC_DEBOUNCE_TIME != 0))
StructDebounceStatus g_stJudge2pFrameSyncDebounce;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Judge Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysJudgeHandler(void)
{
    CLR_MODE_STATE_CHANGE_OTHERS();

    switch(SysPowerGetPowerStatus())
    {
        case _POWER_STATUS_OFF:

            // Force mode state to power off
            if(GET_MODE_STATE() != _MODE_STATUS_POWER_OFF)
            {
                if(SysJudgeStateChangeEvent(_MODE_STATUS_POWER_OFF) == _FALSE)
                {
                    break;
                }
            }

            break;

        case _POWER_STATUS_SAVING:

            // Force mode state to power saving
            if(GET_MODE_STATE() != _MODE_STATUS_POWER_SAVING)
            {
                if(SysJudgeStateChangeEvent(_MODE_STATUS_POWER_SAVING) == _FALSE)
                {
                    break;
                }
            }

            break;

        case _POWER_STATUS_NORMAL:

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if(ScalerSyncGetUrgentEventFlg() == _TRUE)
            {
                ScalerSyncClrUrgentEventFlg();

                if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE) == _TRUE)
                {
                    ScalerTimerReactiveTimerEvent(SEC(1), _SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
                }

                if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE) == _TRUE)
                {
                    ScalerTimerReactiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
                }

                if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE) == _TRUE)
                {
                    if((GET_MODE_STATE() == _MODE_STATUS_DISPLAY_SETTING) && (GET_MODE_DISPLAY_TARGET_STATE() == _DISPLAY_STATE_DISPLAY_READY))
                    {
                        ScalerTimerReactiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                    }
                }
            }
#endif
            switch(GET_MODE_STATE())
            {
                case _MODE_STATUS_POWER_OFF:

                    if(SysJudgeStateChangeEvent(_MODE_STATUS_INITIAL) == _FALSE)
                    {
                        break;
                    }

                    break;

                case _MODE_STATUS_INITIAL:

                    // Change to display initial
                    if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_INITIAL) == _FALSE)
                    {
                        // Return here to skip path status check & display state reset
                        return;
                    }

                    // Return here to skip path status check & display state reset
                    return;

                case _MODE_STATUS_DISPLAY_INITIAL:

                    // Check logo status
                    if(UserInterfaceDisplayGetLogoStatus() == _OSD_LOGO_ON)
                    {
                        // Skip path status check & display state reset when logo on
                        return;
                    }

                    // Change to display check
                    if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_CHECK) == _FALSE)
                    {
                        break;
                    }

                    break;

                case _MODE_STATUS_DISPLAY_SETTING:

                    // Check timing confirm status
                    if(GET_RGN_TIMING_CONFIRM(GET_MODE_DISPLAY_TARGET_INDEX()) == _FALSE)
                    {
                        // Cancel OOR & active timer events
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);

                        // Change to display check
                        if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_CHECK) == _FALSE)
                        {
                            break;
                        }

                        break;
                    }

                    switch(GET_MODE_DISPLAY_TARGET_STATE())
                    {
                        default:

                            // 2 sec to display OOR state
                            ScalerTimerActiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

                            break;

                        case _DISPLAY_STATE_OOR:

                            // Cancel OOR timer event
                            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);

                            // Change to display check
                            if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_CHECK) == _FALSE)
                            {
                                break;
                            }

                            break;

                        case _DISPLAY_STATE_DISPLAY_READY:

                            // Check Dclk status in frame sync support on
                            if((UserCommonDisplayGetFrameSyncSupport() == _FRAME_SYNC_SUPPORT_ON) &&
                               (UserInterfaceDisplayGetDclkNoSupportStatus() == _DCLK_NO_SUPPORT_TRUE))
                            {
                                DebugMessageSystem("DCLK OOR", GET_MODE_DISPLAY_TARGET_REGION());

                                // Dclk not supported; 0.5 sec to display OOR state
                                ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                            }
                            // Check system active ready status
                            else if(GET_MODE_ACTIVE_READY() == _FALSE)
                            {
                                // Wait for system active ready
                                ScalerTimerActiveTimerEvent(SysJudgeGetActiveWaitTime(), _SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);

                                // Cancel OOR timer event
                                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
                            }
                            // Check user active ready status
                            else if(UserCommonModeGetReadyForActiveStatus(GET_MODE_DISPLAY_TARGET_REGION()) == _TRUE)
                            {
                                // Change to display check
                                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_CHECK) == _FALSE)
                                {
                                    break;
                                }

                                // Display setting completed; Change display state to active
                                SET_RGN_DISPLAY_ACTION(GET_MODE_DISPLAY_TARGET_INDEX(), _DISPLAY_ACTION_ACTIVE);

                                // Clear active ready flag
                                CLR_MODE_ACTIVE_READY();
                            }

                            break;
                    }

                    break;

                case _MODE_STATUS_DISPLAY_CHECK:

                    // Search for display target
                    if(SysModeSearchDisplayTarget() == _TRUE)
                    {
#if(_2P_FRAME_SYNC_SUPPORT == _ON)
                        if((ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE) &&
                           (SysModeResetToDisplayInitial() == _TRUE))
                        {
                            // Reset to display initial
                            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
                            break;
                        }
#endif

                        // Change to display setting
                        if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_SETTING) == _FALSE)
                        {
                            break;
                        }
                    }

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
                    if(UserCommonQCGetStartCondition() == _TRUE)
                    {
                        if(SysJudgeStateChangeEvent(_MODE_STATUS_FACTORY) == _FALSE)
                        {
                            break;
                        }
                    }
#endif

                    break;

                case _MODE_STATUS_POWER_SAVING:

                    // Wake up when:
                    // 1. display state change
                    // 2. display target found
                    if((SysRegionCheckSystemDisplayStateChange() == _TRUE) ||
                       (SysModeSearchDisplayTarget() == _TRUE))
                    {
                        // Perform user reset
                        UserCommonModeResetProc();

                        // Change to display initial
                        if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_INITIAL) == _FALSE)
                        {
                            break;
                        }
                    }

                    break;

                case _MODE_STATUS_FACTORY:

                    break;

                default:

                    break;
            }

            break;

        default:

            break;
    }

    // Update display state
    SysJudgeUpdateDisplayState();

    // Handle Status Check and Manual Reset Requests
    SysJudgeModeResetProc();

    // Check data path status
    SysJudgeCheckAllPathStatus();
}

//--------------------------------------------------
// Description  : Update display state
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysJudgeUpdateDisplayState(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();
    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();

    // Update display state
    for(ucRegionIndex = 0x00; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        switch(GET_RGN_DISPLAY_ACTION(ucRegionIndex))
        {
            default:
            case _DISPLAY_ACTION_NO_ACTION:
                break;

            case _DISPLAY_ACTION_RESET_TO_NONE:
                DebugMessageSystem(">> NON", ucRegionIndex);
                SET_RGN_DISPLAY_STATE(ucRegionIndex, _DISPLAY_STATE_NONE);
                break;

            case _DISPLAY_ACTION_NO_SIGNAL:
                DebugMessageSystem(">> NSG", ucRegionIndex);
                SET_RGN_DISPLAY_STATE(ucRegionIndex, _DISPLAY_STATE_NO_SIGNAL);
                CLR_SOURCE_SWITCH_FINISH();
                break;

            case _DISPLAY_ACTION_OOR:
                DebugMessageSystem(">> OOR", ucRegionIndex);
                SET_RGN_DISPLAY_STATE(ucRegionIndex, _DISPLAY_STATE_OOR);

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif
                if(enumDisplayMode == _DISPLAY_MODE_1P)
                {
                    SysModeSetFreeRun();
                }
                break;

            case _DISPLAY_ACTION_DISPLAY_READY:
                DebugMessageSystem(">> DSP", ucRegionIndex);
                SET_RGN_DISPLAY_STATE(ucRegionIndex, _DISPLAY_STATE_DISPLAY_READY);
                break;

            case _DISPLAY_ACTION_ACTIVE:
                DebugMessageSystem(">> ACT", ucRegionIndex);
                SET_RGN_DISPLAY_STATE(ucRegionIndex, _DISPLAY_STATE_ACTIVE);
                break;
        }

        // Clear display target
        CLR_RGN_DISPLAY_ACTION(ucRegionIndex);
    }
}

//--------------------------------------------------
// Description  : Check all data path status, including source stability, measure result, memory status, etc.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysJudgeCheckAllPathStatus(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();
    BYTE ucResetIndex = 0;
    bit bResetAll = _FALSE;

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(SysJudgeCheckStatus(ucRegionIndex) == _FALSE)
        {
#if(_DP_SUPPORT == _ON)
            if(GET_RGN_SOURCE_TYPE(ucRegionIndex) == _SOURCE_DP)
            {
                // Link Status Check
                ScalerDpMacDphyRxLinkStatusIRQAssertCheck(GET_RGN_INPUT_PORT(ucRegionIndex));
            }
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
            if((ucRegionIndex == 0) && (ucRegionCount > 1) &&
               ((GET_RGN_DISPLAY_STATE(0) == _DISPLAY_STATE_OOR) ||
                (GET_RGN_DISPLAY_STATE(0) == _DISPLAY_STATE_ACTIVE)))
            {
                SET_SOURCE_HP_PXP_MAIN_SOURCE_AUTO_SCAN();
            }
#endif

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
            if((ScalerFRC2PFrameSyncEnable(GET_DISPLAY_MODE()) == _ENABLE) &&
               (ucRegionIndex == 0))
            {
                bResetAll = _TRUE;

#if(_2P_FRAME_SYNC_DEBOUNCE_TIME != 0)
                SysJudge2pFrameSyncDebounceStart();
#endif
            }
#endif
            // Clear source judge flag
            CLR_RGN_SOURCE_JUDGE(ucRegionIndex);

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
            // Clear Source BG Judge because source judge was reset
            if(GET_SOURCE_BG_JUDGE(g_ucSourceBgDetectIndex) == _TRUE)
            {
                CLR_SOURCE_BG_JUDGE(g_ucSourceBgDetectIndex);
            }
#endif

            // Reset all duplicated regions
            for(ucResetIndex = 0; ucResetIndex < ucRegionCount; ++ucResetIndex)
            {
                if((bResetAll == _TRUE) || (GET_RGN_INPUT_PORT(ucResetIndex) == GET_RGN_INPUT_PORT(ucRegionIndex)))
                {
                    SysModeResetDataPath(ucResetIndex);
                }
            }

            // Auto search Port has high priority
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
            if((GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT) ||
               (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_PXP_FIXED_PORT))
#else
            if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT)
#endif
            {
                // Switch to reset port
                SysSourceSwitchRegionSearchPort(GET_RGN_INPUT_PORT(ucRegionIndex));
            }
            else if((GET_SOURCE_AUTO_TARGET() == ucRegionIndex) ||
                    (GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _TRUE) ||
                    (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE))
            {
                // Switch to reset port
                SysSourceSwitchRegionSearchPort(GET_RGN_INPUT_PORT(ucRegionIndex));
            }
        }
    }

    // Handle mode reset after check status failed
    SysJudgeModeResetProc();
}

//--------------------------------------------------
// Description  : Check Status
// Input Value  : Select Region Index
// Output Value : _FALSE => Status Changed
//--------------------------------------------------
bit SysJudgeCheckStatus(BYTE ucRegionIndex)
{
    if((GET_MODE_STATE() != _MODE_STATUS_FACTORY) && (GET_MODE_STATE() != _MODE_STATUS_POWER_OFF))
    {
        if(GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE)
        {
            if(SysSourceStableCheck(ucRegionIndex) == _FALSE)
            {
                DebugMessageSystem("Source Unstable!!", ucRegionIndex);
                return _FALSE;
            }

#if(_ULTRA_HDR_SUPPORT == _ON)
            ScalerSyncUpdateSecData(GET_RGN_INPUT_PORT(ucRegionIndex), GET_RGN_DISPLAY_REGION(ucRegionIndex), _HDR_INFO_CHG_POLLING_CHECK_ENABLE);
#endif
        }
        else
        {
            if(GET_RGN_TIMING_CONFIRM(ucRegionIndex) == _TRUE)
            {
                DebugMessageSystem("Duplicated Source Unstable!!", ucRegionIndex);
                return _FALSE;
            }
        }

        if(GET_RGN_TIMING_CONFIRM(ucRegionIndex) == _TRUE)
        {
            if(ScalerMeasureCheckTimingChange(GET_RGN_SOURCE_TYPE(ucRegionIndex), GET_RGN_INPUT_PORT(ucRegionIndex), ucRegionIndex) == _TRUE)
            {
                DebugMessageSystem("Measured Input HV Changed", ucRegionIndex);
                return _FALSE;
            }

            // double check input timing
            if((GET_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex) == _TRUE) &&
               ((GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_DISPLAY_READY) ||
                (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_ACTIVE) ||
                (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_OOR)))
            {
                if(ScalerMeasureDoubleCheck(GET_RGN_SOURCE_TYPE(ucRegionIndex), GET_RGN_INPUT_PORT(ucRegionIndex), ucRegionIndex) == _FALSE)
                {
                    DebugMessageSystem("Input Timing Double Check Failed", ucRegionIndex);
                    return _FALSE;
                }

                CLR_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex);
            }
        }
#if(_DOLBY_CERTIFICATION_SUPPORT == _OFF)
        if((GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_DISPLAY_READY) ||
           (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_ACTIVE))
        {
            if((ScalerMDomainMemoryCheck(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(ucRegionIndex))) == _FALSE) ||
               (ScalerMDomainDisplayTimingGenCheck(GET_RGN_INPUT_PORT(ucRegionIndex)) == _FALSE))
            {
                DebugMessageSystem("Memory Check Failed", ucRegionIndex);
                return _FALSE;
            }

#if((_FRC_SUPPORT == _ON) && (_HDMI21_ALLM_SUPPORT == _ON))
            if(GET_RGN_SOURCE_TYPE(ucRegionIndex) == _SOURCE_HDMI)
            {
                ScalerFRCAdjustAllmDelay(GET_RGN_INPUT_PORT(ucRegionIndex), _SOURCE_HDMI);
            }
#endif
            ScalerMeasureSetRegionIndex(ucRegionIndex);
        }
#endif

#if(_PANEL_STYLE == _PANEL_DPTX)
#if(_PANEL_DPTX_HPD_DETECT == _ON)
        if(GET_MODE_STATE() == _MODE_STATUS_DISPLAY_CHECK)
        {
            if(ScalerDisplayDpTxStableDetect() == _FALSE)
            {
#if(_PANEL_POW_SEQ_FAST_MODE == _OFF)
                CLR_DISPLAY_DP_TX_FORCE_TO_LT();
#endif
                DebugMessageSystem("eDP unstable", 0x00);
                return _FALSE;
            }
        }
#endif
#endif
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Switch to Active State
// Input Value  : mode state
// Output Value : _TRUE => Successfully Changed
//--------------------------------------------------
bit SysJudgeStateChangeEvent(EnumModeStatus enumModeState)
{
    // Check mode reset target
    if(GET_MODE_RESET_TARGET() != _MODE_ACTION_NO_RESET_MODE)
    {
        return _FALSE;
    }

    if((GET_MODE_STATE_CHANGE_SOURCE() == _FALSE) &&
       (GET_MODE_STATE_CHANGE_MODE() == _FALSE) &&
       (GET_MODE_STATE_CHANGE_OSD() == _FALSE) &&
       (GET_MODE_STATE_CHANGE_OTHERS() == _FALSE))
    {
        SET_MODE_STATE(enumModeState);
        SET_MODE_STATE_CHANGE_SOURCE();
        SET_MODE_STATE_CHANGE_MODE();
        SET_MODE_STATE_CHANGE_OSD();
        SET_MODE_STATE_CHANGE_OTHERS();

#if(_DEBUG_MESSAGE_SYSTEM == _ON)
        switch(enumModeState)
        {
            case _MODE_STATUS_INITIAL:
                DebugMessageSystem("--INI--", enumModeState);
                break;
            case _MODE_STATUS_DISPLAY_INITIAL:
                DebugMessageSystem("--DINI-", enumModeState);
                break;
            case _MODE_STATUS_DISPLAY_CHECK:
                DebugMessageSystem("--CHK--", enumModeState);
                break;
            case _MODE_STATUS_DISPLAY_SETTING:
                DebugMessageSystem("--DISP-", enumModeState);
                break;
            case _MODE_STATUS_POWER_SAVING:
                DebugMessageSystem("--PS---", enumModeState);
                break;
            case _MODE_STATUS_POWER_OFF:
                DebugMessageSystem("--OFF--", enumModeState);
                break;
            default:
                break;
        }
#endif

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Mode Reset Process according to reset target
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysJudgeModeResetProc(void)
{
    BYTE ucModeResetTarget = GET_MODE_RESET_TARGET();

    // Clear reset target first
    SET_MODE_RESET_TARGET(_MODE_ACTION_NO_RESET_MODE);

    switch(ucModeResetTarget)
    {
        case _MODE_ACTION_RESET_TO_DISPLAY_INITIAL:

            if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_INITIAL) == _FALSE)
                {
                    // Resume mode reset target
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_CHECK:

            if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_DISPLAY_CHECK);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_CHECK) == _FALSE)
                {
                    // Resume mode reset target
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_CHECK);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG:

            if(GET_MODE_STATE() == _MODE_STATUS_DISPLAY_CHECK)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_SETTING) == _FALSE)
                {
                    // Resume mode reset target
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING:

            if(GET_MODE_STATE() == _MODE_STATUS_DISPLAY_CHECK)
            {
                SysModeResetState(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);

                if(SysJudgeStateChangeEvent(_MODE_STATUS_DISPLAY_SETTING) == _FALSE)
                {
                    // Resume mode reset target
                    SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
                    return;
                }
            }

            break;

        case _MODE_ACTION_RESET_TO_FACTORY_MODE:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);

            if(SysJudgeStateChangeEvent(_MODE_STATUS_FACTORY) == _FALSE)
            {
                // Resume mode reset target
                SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_FACTORY_MODE);
                return;
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Required Wait Time before Active
// Input Value  : None
// Output Value : Required Wait Time
//--------------------------------------------------
WORD SysJudgeGetActiveWaitTime(void)
{
    WORD usActiveWaitTime = 0;

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
    WORD usPanelOffTime = ScalerTimerGetEventRemainTime(_SYSTEM_TIMER_EVENT_PANEL_POWER_OFF);
#endif

    usActiveWaitTime = UserInterfaceDisplayGetExtendedActiveWaitTime();

    if(GET_RGN_FIRST_ACTIVE(GET_MODE_DISPLAY_TARGET_INDEX()) == _FALSE)
    {
        switch(GET_RGN_SOURCE_TYPE(GET_MODE_DISPLAY_TARGET_INDEX()))
        {
#if(_VGA_SUPPORT == _ON)
            case _SOURCE_VGA:
                usActiveWaitTime += _WAIT_TIME_TO_ACTIVE_VGA;
                break;
#endif

#if(_HDMI_SUPPORT == _ON)
            case _SOURCE_DVI:
                usActiveWaitTime += _WAIT_TIME_TO_ACTIVE_DVI;
                break;
#endif

#if(_HDMI_SUPPORT == _ON)
            case _SOURCE_HDMI:
                usActiveWaitTime += _WAIT_TIME_TO_ACTIVE_HDMI;
                break;
#endif

#if(_DP_SUPPORT == _ON)
            case _SOURCE_DP:
                usActiveWaitTime += _WAIT_TIME_TO_ACTIVE_DP;
                break;
#endif

            default:
                break;
        }
    }

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
    return ((usPanelOffTime >= usActiveWaitTime) ? usPanelOffTime : usActiveWaitTime);
#else
    return usActiveWaitTime;
#endif
}

#if((_2P_FRAME_SYNC_SUPPORT == _ON) && (_2P_FRAME_SYNC_DEBOUNCE_TIME != 0))
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void SysJudge2pFrameSyncDebounceStart(void)
{
    if((GET_2P_FRAME_SYNC_DEBOUNCE_START() == _TRUE) &&
       (GET_2P_FRAME_SYNC_DEBOUNCE_STOP() == _FALSE))
    {
        return;
    }

    SET_2P_FRAME_SYNC_DEBOUNCE_START(_TRUE);
    SET_2P_FRAME_SYNC_DEBOUNCE_STOP(_FALSE);

    ScalerTimerActiveTimerEvent(_2P_FRAME_SYNC_DEBOUNCE_TIME, _SYSTEM_TIMER_EVENT_2P_FRAME_SYNC_DEBOUNCE);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void SysJudge2pFrameSyncDebounceStop(void)
{
    SET_2P_FRAME_SYNC_DEBOUNCE_STOP(_TRUE);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void SysJudge2pFrameSyncDebounceReset(void)
{
    SET_2P_FRAME_SYNC_DEBOUNCE_START(_FALSE);
    SET_2P_FRAME_SYNC_DEBOUNCE_STOP(_FALSE);

    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_2P_FRAME_SYNC_DEBOUNCE);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysJudgeCheck2pFrameSyncDebounceSupported(void)
{
    switch(GET_DISPLAY_MODE())
    {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
            return _FALSE;
#endif

#if(_PIP_FRAME_SYNC_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
            return _FALSE;
#endif

#if(_PBP_LR_FRAME_SYNC_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
            return _FALSE;
#endif

        default:
            return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysJudgeCheck2pFrameSyncDebounce(void)
{
    if(SysJudgeCheck2pFrameSyncDebounceSupported() == _FALSE)
    {
        return _FALSE;
    }

    if((GET_2P_FRAME_SYNC_DEBOUNCE_START() == _TRUE) &&
       (GET_2P_FRAME_SYNC_DEBOUNCE_STOP() == _FALSE))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif
