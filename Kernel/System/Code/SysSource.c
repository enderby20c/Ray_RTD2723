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
// ID Code      : SysSource.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_SOURCE__

#include "SysInclude.h"
#include "Source/SysSource.h"

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#warning "NOTE: GPIO of HDMI External Switch Should Be From ON Region!!!"
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tINPUT_PORT_TYPE[] =
{
    _A0_INPUT_PORT_TYPE,
    _D0_INPUT_PORT_TYPE,
    _D1_INPUT_PORT_TYPE,
    _D2_INPUT_PORT_TYPE,
    _D3_INPUT_PORT_TYPE,
    _D4_INPUT_PORT_TYPE,
    _D5_INPUT_PORT_TYPE,
    _D6_INPUT_PORT_TYPE,
    _D7_INPUT_PORT_TYPE,
    _D8_INPUT_PORT_TYPE,
    _D9_INPUT_PORT_TYPE,
    _D12_INPUT_PORT_TYPE,
    _D13_INPUT_PORT_TYPE,
    _D14_INPUT_PORT_TYPE,
    _D15_INPUT_PORT_TYPE,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSourceInfoType g_pstSourceInfo[_INPUT_PORT_VALID];
StructSourceInfoType g_stSourceInfoBackup;

BYTE g_ucSourceSearchIndex;
BYTE g_ucSourceMeasureTargetIndex;

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
StructSourceInfoType g_pstSourceBgInfo[_INPUT_PORT_VALID];
BYTE g_ucSourceBgDetectIndex;
#endif

StructInputInfoType g_stSourceInputInfo;

EnumInputPort g_penumSourceSearchPriority[10] =
{
    _INPUT_PORT_SEARCH_PRI_0,
    _INPUT_PORT_SEARCH_PRI_1,
    _INPUT_PORT_SEARCH_PRI_2,
    _INPUT_PORT_SEARCH_PRI_3,
    _INPUT_PORT_SEARCH_PRI_4,
    _INPUT_PORT_SEARCH_PRI_5,
    _INPUT_PORT_SEARCH_PRI_6,
    _INPUT_PORT_SEARCH_PRI_7,
    _INPUT_PORT_SEARCH_PRI_8,
    _INPUT_PORT_SEARCH_PRI_9,
};

EnumSourceSearchGroup g_penumSourceSearchGroup[15] =
{
    _A0_INPUT_PORT_GROUP,
    _D0_INPUT_PORT_GROUP,
    _D1_INPUT_PORT_GROUP,
    _D2_INPUT_PORT_GROUP,
    _D3_INPUT_PORT_GROUP,
    _D4_INPUT_PORT_GROUP,
    _D5_INPUT_PORT_GROUP,
    _D6_INPUT_PORT_GROUP,
    _D7_INPUT_PORT_GROUP,
    _D8_INPUT_PORT_GROUP,
    _D9_INPUT_PORT_GROUP,
    _D12_INPUT_PORT_GROUP,
    _D13_INPUT_PORT_GROUP,
    _D14_INPUT_PORT_GROUP,
    _D15_INPUT_PORT_GROUP,
};

#if(_VGA_SUPPORT == _ON)
WORD g_usSourceDefaultSearchTimeVga;
WORD g_usSourceNoCableSearchTimeVga;
#endif

#if(_HDMI_SUPPORT == _ON)
WORD g_usSourceDefaultSearchTimeHdmi;
WORD g_usSourceNoCableSearchTimeHdmi;
#endif

#if(_DP_SUPPORT == _ON)
WORD g_usSourceDefaultSearchTimeDp;
WORD g_usSourceNoCableSearchTimeDp;

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
WORD g_usSourceDefaultSearchTimeTypeC;
WORD g_usSourceNoCableSearchTimeTypeC;
#endif

#if(_DP_TBT_SUPPORT == _ON)
WORD g_usSourceDefaultSearchTimeTbt;
WORD g_usSourceNoCableSearchTimeTbt;
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Source Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceHandler(void)
{
    SysSourceCableDetection();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE) &&
       (GET_POWER_STATUS() == _POWER_STATUS_NORMAL))
    {
        return;
    }
#endif

    if((GET_MODE_STATE() != _MODE_STATUS_POWER_OFF) &&
       (GET_MODE_STATE() != _MODE_STATUS_INITIAL) &&
       (UserInterfacePowerGetForcePSStatus() == _FORCE_TO_PS_FALSE) &&
       (UserInterfaceSourceBypassDetection() == _SOURCE_DETECTION_NORMAL))
    {
        if(SysSourceCheckAllSourceJudged() != _TRUE)
        {
            if(GET_SOURCE_DETECTING() == _FALSE)
            {
                SysSourceSwitchPort();
            }

            if(GET_SOURCE_JUDGE(g_ucSourceSearchIndex) == _FALSE)
            {
                if(GET_SOURCE_SEARCH_PORT_INITIAL() == _TRUE)
                {
                    SysSourceScanPortInitial(g_ucSourceSearchIndex);

                    CLR_SOURCE_SEARCH_PORT_INITIAL();
                }

                if(GET_SOURCE_SEARCH_TIME_INITIAL() == _TRUE)
                {
                    SysSourceSearchTimeInitial(g_ucSourceSearchIndex);

                    CLR_SOURCE_SEARCH_TIME_INITIAL();
                }

                // Port Detection
                SysSourceDetectPort(g_ucSourceSearchIndex);

                // Decide if this port is about to be chosen
                SysSourceJudge();
            }
        }
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
        else if(SysSourceBgJudgeDoDetect() == _TRUE)
        {
            if(GET_SOURCE_DETECTING() == _FALSE)
            {
                SysSourceBg1pSwitchPort();
            }

            if(GET_SOURCE_SEARCH_PORT_INITIAL() == _TRUE)
            {
                SysSourceScanPortInitial(g_ucSourceBgDetectIndex);

                CLR_SOURCE_SEARCH_PORT_INITIAL();
            }

            if(GET_SOURCE_SEARCH_TIME_INITIAL() == _TRUE)
            {
                SysSourceSearchTimeInitial(g_ucSourceBgDetectIndex);

                CLR_SOURCE_SEARCH_TIME_INITIAL();
            }

            // Port Detection
            SysSourceDetectPort(g_ucSourceBgDetectIndex);

            // Decide if this port is about to be chosen
            SysSourceBgJudge();
        }
        else if(SysSourceBgJudgeDoStableCheck() == _TRUE)
        {
            if(SysSourceBgStableCheck() == _FALSE)
            {
                DebugMessageSystem("Background Source Unstable!!", GET_SOURCE_TYPE(g_ucSourceBgDetectIndex));

                SysSourceBgInfoReset();
            }
        }
#endif
        // Measure input source
        SysSourceMeasureProc();
    }

    CLR_MODE_STATE_CHANGE_SOURCE();
}

//--------------------------------------------------
// Description  : Port Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceDetectPort(BYTE ucSearchIndex)
{
    FUNC_PTR_PRE_DETECT pfnPsPredetect = 0;
    FUNC_PTR_PRE_DETECT pfnNormalPredetect = 0;
    FUNC_PTR_SCAN_INPUT_PORT pfnScanInputPort = 0;

    EnumInputPort enumInputPort = GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex));
    EnumPortType enumPortType = GET_PORT_TYPE(GET_INPUTPORT_TYPE(ucSearchIndex));

    switch(enumPortType)
    {
#if(_VGA_SUPPORT == _ON)
        case _PORT_VGA:
            pfnPsPredetect = &ScalerVgaSyncProcPreDetect;
            pfnNormalPredetect = &ScalerVgaSyncProcPreDetect;
            pfnScanInputPort = &SysVgaScanInputPort;
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
            pfnPsPredetect = &ScalerTmdsMacRxPSPreDetect;
            pfnNormalPredetect = &ScalerTmdsMacRxNormalPreDetect;

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)

            pfnScanInputPort = &ScalerDscDecoderMacRxScanInputPort;
#else
            pfnScanInputPort = &ScalerTmdsMacRxScanInputPort;
#endif

            if(ScalerTmdsMacRxReactiveSearchTimeCheck(enumInputPort) == _TRUE)
            {
                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:

            // Check if DP mac is assigned
            if(ScalerDpRxGetMacSwitch(enumInputPort) == _DP_MAC_NONE)
            {
                break;
            }

            if(GET_DP_RX_CAPABILITY_SWITCHED() == _TRUE)
            {
                break;
            }

            pfnPsPredetect = &ScalerDpMacDphyRxPSPreDetect;
            pfnNormalPredetect = &ScalerDpMacDphyRxNormalPreDetect;

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            pfnScanInputPort = &ScalerDscDecoderMacRxScanInputPort;
#else
            pfnScanInputPort = &ScalerDpMacStreamRxScanInputPort;
#endif
            break;
#endif

        default:
            break;
    }

    // Clear source type
    SET_SOURCE_TYPE(ucSearchIndex, _SOURCE_NONE);

    // Check if functions are all assigned
    if((pfnPsPredetect == 0) || (pfnNormalPredetect == 0) || (pfnScanInputPort == 0))
    {
        return;
    }

    switch(GET_POWER_STATUS())
    {
        case _POWER_STATUS_SAVING:
            // Perform pre-detect only
            SET_SOURCE_PREDETECT(ucSearchIndex, pfnPsPredetect(enumInputPort));

            if(GET_SOURCE_PREDETECT(ucSearchIndex) == _TRUE)
            {
                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }

            break;

        case _POWER_STATUS_NORMAL:
            SET_SOURCE_PREDETECT(ucSearchIndex, pfnNormalPredetect(enumInputPort));

            if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
            {
                // Perform scan input port on pre-detect pass in non-polling mode
                if((GET_SOURCE_PREDETECT(ucSearchIndex) == _TRUE) &&
                   (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE))
                {
                    // Update source type
                    SET_SOURCE_TYPE(ucSearchIndex, pfnScanInputPort(enumInputPort, enumPortType));

#if(_ULTRA_HDR_SUPPORT == _ON)
                    ScalerSyncUpdateSecData(enumInputPort, SysRegionConvertPortToRegion(enumInputPort), _HDR_INFO_CHG_POLLING_CHECK_ENABLE);
#endif
                }
            }
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Event to clear detection and finish flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceClearDetectingEvent(void)
{
    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    if(enumDisplayMode == _DISPLAY_MODE_1P)
    {
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        // For some of HP scan type, the first loop of source search for checking monitor status needs to be done completely
        if(SysSourceHpGetMonitorStatusCheckProcessing() == _FALSE)
#endif
        {
            if(SysSourceKeepDetectingCheck() == _TRUE)
            {
                if(GET_MODE_STATE() == _MODE_STATUS_DISPLAY_CHECK)
                {
                    SET_SOURCE_SWITCH_FINISH();
                }

                ScalerTimerActiveTimerEvent(SEC(0), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

                if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL)
                {
                    SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                }

                return;
            }
        }
    }

    CLR_SOURCE_DETECTING();

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    CLR_SOURCE_HP_DETECTING();
#endif
}

//--------------------------------------------------
// Description  : Check Source Keep Detecting or Not
// Input Value  : None
// Output Value : _TRUE: keep detecting, _FALSE: stop detecting
//--------------------------------------------------
bit SysSourceKeepDetectingCheck(void)
{
    switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex)))
    {
#if(_DP_SUPPORT == _ON)
        case  _PORT_DP:
            return SysDpSourceKeepDetectingCheck();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Decide how much time will be spent on the first port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceSearchTimeInitial(BYTE ucSearchIndex)
{
    EnumInputPort enumInputPort = GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex));
    EnumPortType enumPortType = GET_PORT_TYPE(GET_INPUTPORT_TYPE(ucSearchIndex));
    WORD usReactiveTime = _NONE_SEARCH_TIME;

    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();
    enumDisplayMode = enumDisplayMode;

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    enumInputPort = enumInputPort;

    SET_SOURCE_DETECTING();

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)

    UserInterfaceSourceAdjustSourceSearchTime();

    if(GET_SOURCE_EIZO_INFO_RESET() == _TRUE)
    {
        ScalerTimerReactiveTimerEvent(UserInterfaceSourceGetEizoSearchFinishTime(), _SYSTEM_TIMER_EVENT_SOURCE_EIZO_SEARCH_FINISH);
        CLR_SOURCE_EIZO_INFO_RESET();
    }

#if(_MULTI_DISPLAY_MAX != 0x01)
    if((enumDisplayMode != _DISPLAY_MODE_1P) &&
       (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE))
    {
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
    }
#endif

#endif

    switch(GET_SOURCE_SEARCH_DELAY_MODE())
    {
        case _SOURCE_SEARCH_POLLING_MODE:
            usReactiveTime = SEC(0);
            break;

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
        case _SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE:
            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
            usReactiveTime = _SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT;
            break;
#endif

        case _SOURCE_SEARCH_DELAY_REACTIVE_MODE:
            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
            SysSourceEizoReactiveTotalSearchTime(enumPortType);
#else
            usReactiveTime = SysSourceGetDelayReactiveSearchTime(enumPortType);
#endif
            break;

        default:

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
            if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT) == _TRUE)
            {
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);
            }
#endif

            switch(GET_SOURCE_SCAN_TYPE())
            {
                case _SOURCE_SWITCH_FIXED_PORT:
                case _SOURCE_SWITCH_AUTO_IN_GROUP:
                case _SOURCE_SWITCH_DELL_HOTKEY_FIXED:
                case _SOURCE_SWITCH_DELL_HOTKEY_AUTO:

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)
#if((_USB_SUPPORT == _ON) && (_DP_SUPPORT == _ON) && (_TYPE_C_PORT_CTRL_SUPPORT == _ON))
                    if(SysUsbTypeCRxCheckTypeCPortControllerExist(enumInputPort) == _TRUE)
                    {
                        usReactiveTime = _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C;
                    }
                    else
#endif
                    {
#if(_HDMI_FRL_SUPPORT == _ON)
                        if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) != _FROM_HDMI_TMDS_MAC)
                        {
                            usReactiveTime = _SOURCE_DEFAULT_SEARCH_TIME_HDMI_FRL;
                        }
                        else
#endif
                        {
                            usReactiveTime = _SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT;
                        }
                    }
#else

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
                    if(((enumInputPort == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4) && (GET_CABLE_DETECT(SysSourceConvertSearchPort(_D4_INPUT_PORT)) == _TRUE)) ||
                       ((enumInputPort == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14) && (GET_CABLE_DETECT(SysSourceConvertSearchPort(_D14_INPUT_PORT)) == _TRUE)) ||
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                       ((enumInputPort == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15) && (GET_CABLE_DETECT(SysSourceConvertSearchPort(_D15_INPUT_PORT)) == _TRUE)) ||
#endif
                       ((enumInputPort != _D4_INPUT_PORT) && (GET_CABLE_DETECT(ucSearchIndex) == _TRUE)))

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

                    if(((enumInputPort == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3) && (GET_CABLE_DETECT(SysSourceConvertSearchPort(_D3_INPUT_PORT)) == _TRUE)) ||
                       ((enumInputPort == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12) && (GET_CABLE_DETECT(SysSourceConvertSearchPort(_D12_INPUT_PORT)) == _TRUE)) ||
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                       ((enumInputPort == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13) && (GET_CABLE_DETECT(SysSourceConvertSearchPort(_D13_INPUT_PORT)) == _TRUE)) ||
#endif
                       ((enumInputPort != _D3_INPUT_PORT) && (GET_CABLE_DETECT(ucSearchIndex) == _TRUE)))
#endif // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

#else // #if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)

                    if(GET_CABLE_DETECT(ucSearchIndex) == _TRUE)
#endif
                    {
                        usReactiveTime = SysSourceGetDefaultSearchTime(enumInputPort, enumPortType);
                    }
                    else
                    {
                        usReactiveTime = SysSourceGetNoCableSearchTime(enumInputPort, enumPortType);
                    }
#endif
                    break;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
                case _SOURCE_SWITCH_HP_PXP_SOURCE_SCAN:
                case _SOURCE_SWITCH_HP_PXP_FIXED_PORT:

                    if(GET_CABLE_DETECT(ucSearchIndex) == _TRUE)
                    {
                        usReactiveTime = SysSourceGetDefaultSearchTime(enumInputPort, enumPortType);
                    }
                    else
                    {
                        usReactiveTime = SEC(0.2);
                    }

                    if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_PXP_FIXED_PORT)
                    {
                        SET_SOURCE_HP_PORT_SWITCH_TARGET(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)));
                    }

                    break;

                case _SOURCE_SWITCH_HP_TIMING_CHANGE:

                    if(GET_MODE_STATE() != _MODE_STATUS_POWER_SAVING)
                    {
                        usReactiveTime = SEC(10);

                        SET_SOURCE_HP_DETECTING();

                        SET_SOURCE_HP_PORT_SWITCH_TARGET(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)));
                    }
                    else
                    {
                        usReactiveTime = SEC(2);
                    }

                    break;

                case _SOURCE_SWITCH_HP_SOURCE_SCAN:
                case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:
                case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:
                case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:
                    if((GET_SOURCE_HP_FROM_TIMING_CHANGE() == _TRUE) && (ucSearchIndex == SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))))
                    {
                        usReactiveTime = SEC(0.2);
                    }
                    else if(GET_CABLE_DETECT(ucSearchIndex) == _TRUE)
                    {
                        usReactiveTime = SysSourceGetDefaultSearchTime(enumInputPort, enumPortType);
                    }
                    else if(GET_SOURCE_SEARCH_TIMES(ucSearchIndex) == 0x00)
                    {
                        usReactiveTime = SEC(0.2);
                    }
                    else
                    {
                        usReactiveTime = SEC(0.5);
                    }

                    break;
#endif

                default:
                    break;
            }

            break;
    }

    if(usReactiveTime != _NONE_SEARCH_TIME)
    {
        // Reactive source detect
        ScalerTimerReactiveTimerEvent(usReactiveTime, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }
}

//--------------------------------------------------
// Description  : Judge if the port with source will be chosen
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceJudge(void)
{
    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:
        case _SOURCE_SWITCH_AUTO_IN_GROUP:
        case _SOURCE_SWITCH_DELL_HOTKEY_FIXED:
        case _SOURCE_SWITCH_DELL_HOTKEY_AUTO:
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        case _SOURCE_SWITCH_HP_TIMING_CHANGE:
        case _SOURCE_SWITCH_HP_PXP_FIXED_PORT:
#endif

            if(GET_SOURCE_TYPE(g_ucSourceSearchIndex) != _SOURCE_NONE)
            {
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                // Choose Current Source to proceed
                SET_SOURCE_JUDGE(g_ucSourceSearchIndex, _TRUE);

                CLR_SOURCE_DETECTING();

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
                if(SysSourceCheckAllSourceJudged() == _TRUE)
                {
                    SysSourceBgDetectReset();
                }
#endif

                if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_FIXED)
                {
                    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_FIXED_PORT);
                }
                else if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_AUTO)
                {
                    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_AUTO_IN_GROUP);
                }

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
                CLR_SOURCE_HP_DETECTING();

                if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_TIMING_CHANGE)
                {
                    CLR_SOURCE_JUDGE(g_ucSourceSearchIndex);

                    if(GET_SOURCE_HP_SOURCE_JUDGE() == _TRUE)
                    {
                        CLR_SOURCE_HP_TARGET_NO_SIGNAL();

                        if(g_ucSourceSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)))
                        {
                            g_ucSourceSearchIndex = 0;

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            SET_SOURCE_SEARCH_PORT_INITIAL();

                            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                            SET_SOURCE_SEARCH_TIME_REACTIVE();

                            SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

                            SET_SOURCE_HP_TIMING_CHANGE();

                            SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);

                            CLR_SOURCE_HP_SOURCE_JUDGE();

                            CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                            SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);

                            return;
                        }

                        SET_SOURCE_JUDGE(g_ucSourceSearchIndex, _TRUE);
                    }
                    else
                    {
                        CLR_SOURCE_DETECTING();

                        CLR_RGN_TIMING_CONFIRM(GET_MODE_DISPLAY_TARGET_INDEX());
                    }
                }
#endif

                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

#if(_DUAL_DP_SUPPORT == _ON)

                if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
                   (SysSourceGetInputPort() != _DUAL_DP_MAIN_PORT) &&
                   (SysSourceGetInputPort() != _DUAL_DP_SUB_PORT) &&
                   (SysSourceGetInputPort() != _DUAL_DP_INPUT_PORT))
                {
                    if(UserInterfaceDpGetDualDefaultPort() == _DP_DUAL_PORT_USE_DUAL_PORT)
                    {
                        if(UserCommonEdidDpGetDualPortEdidSelectStatus() == _FALSE)
                        {
                            UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_INPUT_PORT);
                        }
                    }
                    else
                    {
                        if(UserCommonEdidDpGetDualPortEdidSelectStatus() == _TRUE)
                        {
                            UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_MAIN_PORT);
                            UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_SUB_PORT);
                        }
                    }
                }
#endif
            }
            else if(GET_SOURCE_PREDETECT(g_ucSourceSearchIndex) == _TRUE)
            {
                if(GET_SOURCE_SEARCH_TIME_REACTIVE() == _TRUE)
                {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                    SET_SOURCE_EIZO_EVENT_TIME(SysSourceEizoGetReactiveEventTime());
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
                    if(GET_SOURCE_HP_DETECTING() == _FALSE)
#endif
                    {
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                    }

                    SET_SOURCE_DETECTING();

                    SET_SOURCE_SEARCH_TIME_INITIAL();

                    SET_SOURCE_SEARCH_PORT_INITIAL();

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                    //--------------------------------------------------
                    // Check NVRAM port when:
                    // 1. "NVRAM check" flagged
                    // 2. in auto-search mode, and search index belongs to auto-search target
                    // 3. search index & saved index are in the same group but different
                    // 4. source search times is not 0
                    //--------------------------------------------------
                    if((GET_SOURCE_SEARCH_CHECK_NVRAM_PORT() == _TRUE) &&
                       (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE) &&
                       (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_AUTO_IN_GROUP) &&
                       (g_ucSourceSearchIndex == GET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET())) &&
                       (GET_INPUTPORT_GROUP(g_ucSourceSearchIndex) == GET_INPUTPORT_GROUP(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0 + GET_SOURCE_AUTO_TARGET())))) &&
                       (g_ucSourceSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0 + GET_SOURCE_AUTO_TARGET()))) &&
                       (GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) != 0x00))
                    {
                        DebugMessageSystem("Switch NVRAM port", g_ucSourceSearchIndex);

                        g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0 + GET_SOURCE_AUTO_TARGET()));

                        SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSourceSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE);

                        CLR_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                    }
                    else
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_REACTIVE_MODE);

                        CLR_SOURCE_SEARCH_TIME_REACTIVE();
                    }
#else
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_REACTIVE_MODE);

                    CLR_SOURCE_SEARCH_TIME_REACTIVE();
#endif
                }

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
                }
            }

            break;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        case _SOURCE_SWITCH_HP_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:
        case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:

            if(GET_SOURCE_TYPE(g_ucSourceSearchIndex) != _SOURCE_NONE)
            {
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                if(GET_SOURCE_HP_SOURCE_JUDGE() == _TRUE)
                {
                    CLR_SOURCE_HP_TARGET_NO_SIGNAL();

                    SET_SOURCE_JUDGE(g_ucSourceSearchIndex, _TRUE);

                    if((GET_SOURCE_HP_TIMING_CHANGE() == _TRUE) &&
                       (g_ucSourceSearchIndex == SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))))
                    {
                        SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_TIMING_CHANGE);
                    }

                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                }
                else
                {
                    CLR_SOURCE_DETECTING();

                    CLR_RGN_TIMING_CONFIRM(GET_MODE_DISPLAY_TARGET_INDEX());
                }

                CLR_SOURCE_HP_DETECTING();

                DebugMessageSystem("7. #############Source Judge HP Case", g_ucSourceSearchIndex);
            }
            else if(GET_SOURCE_PREDETECT(g_ucSourceSearchIndex) == _TRUE)
            {
                if(GET_SOURCE_SEARCH_TIME_REACTIVE() == _TRUE)
                {
                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

                    SET_SOURCE_DETECTING();

                    SET_SOURCE_SEARCH_TIME_INITIAL();

                    SET_SOURCE_SEARCH_PORT_INITIAL();

                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_REACTIVE_MODE);

                    CLR_SOURCE_SEARCH_TIME_REACTIVE();
                }

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
                }
            }

            break;

        case _SOURCE_SWITCH_HP_PXP_SOURCE_SCAN:

            if(GET_SOURCE_TYPE(g_ucSourceSearchIndex) != _SOURCE_NONE)
            {
                CLR_SOURCE_DETECTING();
            }

            break;

#endif // End of #if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Port Switch Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceSwitchPort(void)
{
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        SysSource1pSwitchPort();
    }
#if(_MULTI_DISPLAY_MAX != 0x01)
    else
    {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            SysSource1pSwitchPort();

            SET_RGN_SOURCE_INDEX(_REGION_INDEX_1, GET_RGN_SOURCE_INDEX(_REGION_INDEX_0));
            SET_RGN_DISPLAY_ACTION(_REGION_INDEX_1, GET_RGN_DISPLAY_ACTION(_REGION_INDEX_0));
        }
        else
#endif
        {
            SysSourceMultiSwitchPort();
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Port Switch Function for 1P
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSource1pSwitchPort(void)
{
    BYTE ucCount = 0;
    BYTE ucBackupSearchIndex = 0;

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
    SysSourceRecoverSearchIndexD4ToExtendedPort();
#else
    SysSourceRecoverSearchIndexD3ToExtendedPort();
#endif
#endif

    ucBackupSearchIndex = g_ucSourceSearchIndex;

    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:

            if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                SET_SOURCE_SWITCH_FINISH();
                SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
            }

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
            SysSourceConvertSearchIndexExtendedPortToD4Port();
#else
            SysSourceConvertSearchIndexExtendedPortToD3Port();
#endif
#endif
            break;

        case _SOURCE_SWITCH_AUTO_IN_GROUP:

            // Switch to the next port by search priority with group limit.
            do
            {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                        SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();

                        if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL)
                        {
                            SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);

                            g_ucSourceSearchIndex = ucBackupSearchIndex;

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
                            SysSourceConvertSearchIndexExtendedPortToD4Port();
#else
                            SysSourceConvertSearchIndexExtendedPortToD3Port();
#endif
#endif
                            return;
                        }
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) <= 1)
                {
                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();

                        if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL)
                        {
                            SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);

                            g_ucSourceSearchIndex = ucBackupSearchIndex;

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
                            SysSourceConvertSearchIndexExtendedPortToD4Port();
#else
                            SysSourceConvertSearchIndexExtendedPortToD3Port();
#endif
#endif
                            return;
                        }
                    }

                    if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                    {
                        INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)

                if(GET_SOURCE_ASUS_START_AUTO() == _TRUE)
                {
                    if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                    {
                        INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                        if(SysSourceCheckTargetTimes(1) == _TRUE)
                        {
                            SET_SOURCE_SWITCH_FINISH();
                            SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);

                            SET_SOURCE_ASUS_START_POLLING();
                        }
                    }

                    if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
                    {
                        SET_SOURCE_ASUS_FIRST_START_AUTO();
                    }
                }
                else
                {
                    if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                    {
                        INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                        SET_SOURCE_SWITCH_FINISH();
                        SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);

                        ScalerTimerActiveTimerEvent(_SOURCE_ASUS_START_AUTO_TIME, _SYSTEM_TIMER_EVENT_SOURCE_ASUS_START_AUTO);

                        CLR_SOURCE_ASUS_START_POLLING();
                    }

                    return;
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_DELL_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                        SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL)
                        {
                            SET_SOURCE_SWITCH_FINISH();

                            if(UserInterfaceSourceAdjustOsdCheckTotalSearchFinish() == _AUTO_SEARCH_TRUE)
                            {
                                SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                            }
                        }
                    }
                }

                if((GET_SOURCE_EIZO_PS_SUPPORT() == _TRUE) &&
                   (SysSourceCheckTargetTimes(1) == _TRUE) &&
                   (GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL) &&
                   (GET_SOURCE_SWITCH_FINISH() == _FALSE))
                {
                    return;
                }

#endif // End of #if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

                g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;

                if(GET_INPUTPORT_GROUP(g_ucSourceSearchIndex) == GET_INPUTPORT_GROUP(ucBackupSearchIndex))
                {
#if(_DUAL_DP_SUPPORT == _ON)
                    if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) == _DISPLAY_STATE_NO_SIGNAL) && (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE))
                    {
                        ScalerTimerReactiveTimerEvent(_SOURCE_DP_DUAL_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_DUAL_SWITCH_TIMEOUT);
                        CLR_SOURCE_DP_DUAL_SWITCH_TIMEOUT();
                    }

                    if((SysSourceGetInputPort() == _DUAL_DP_MAIN_PORT) || (SysSourceGetInputPort() == _DUAL_DP_SUB_PORT) || (SysSourceGetInputPort() == _DUAL_DP_INPUT_PORT))
                    {
                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) || (GET_SOURCE_DP_DUAL_SWITCH_TIMEOUT() == _TRUE))
                        {
                            if(UserCommonEdidDpGetDualPortEdidSelectStatus() == _FALSE)
                            {
                                if(SysSourceGetInputPort() == _DUAL_DP_INPUT_PORT)
                                {
                                    UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_INPUT_PORT);

                                    if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE)
                                    {
                                        ScalerTimerActiveTimerEvent(_SOURCE_DP_DUAL_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_DUAL_SWITCH_TIMEOUT);
                                        CLR_SOURCE_DP_DUAL_SWITCH_TIMEOUT();
                                    }
                                }
                            }
                            else
                            {
                                if((SysSourceGetInputPort() == _DUAL_DP_MAIN_PORT) || (SysSourceGetInputPort() == _DUAL_DP_SUB_PORT))
                                {
                                    UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_MAIN_PORT);
                                    UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_SUB_PORT);

                                    if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE)
                                    {
                                        ScalerTimerActiveTimerEvent(_SOURCE_DP_DUAL_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_DUAL_SWITCH_TIMEOUT);
                                        CLR_SOURCE_DP_DUAL_SWITCH_TIMEOUT();
                                    }
                                }
                            }

                            break;
                        }
                        else
                        {
                            if(UserCommonEdidDpGetDualPortEdidSelectStatus() == _TRUE)
                            {
                                if((SysSourceGetInputPort() != _DUAL_DP_MAIN_PORT) && (SysSourceGetInputPort() != _DUAL_DP_SUB_PORT))
                                {
                                    break;
                                }
                            }
                            else
                            {
                                if(SysSourceGetInputPort() != _DUAL_DP_INPUT_PORT)
                                {
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
                        {
                            if(UserInterfaceDpGetDualDefaultPort() == _DP_DUAL_PORT_USE_DUAL_PORT)
                            {
                                if(UserCommonEdidDpGetDualPortEdidSelectStatus() == _FALSE)
                                {
                                    UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_INPUT_PORT);
                                }
                            }
                        }

                        break;
                    }
#else

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
                    if((g_ucSourceSearchIndex != ucBackupSearchIndex) && (SysSource1pCheckD4ExternalHdmiAutoSwitch() == _TRUE))
#else
                    if((g_ucSourceSearchIndex != ucBackupSearchIndex) && (SysSource1pCheckD3ExternalHdmiAutoSwitch() == _TRUE))
#endif
#endif
                    {
                        break;
                    }
#endif
                }

                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            if(g_ucSourceSearchIndex != ucBackupSearchIndex)
            {
                SET_SOURCE_SEARCH_TIME_INITIAL();

                SET_SOURCE_SEARCH_PORT_INITIAL();

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                   ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                {
                    SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                }
#endif
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

#elif((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE) ||\
      (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE) ||\
      (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE))

                if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL)
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                }
                else
                {
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                    if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                       ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                    {
                        SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                    }
#endif
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                   ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                {
                    SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                }
#endif
                if(GET_SOURCE_ASUS_START_POLLING() == _TRUE)
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_DELL_STYLE)

                pData[1] = 0;

                for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                {
                    if(GET_SOURCE_SEARCH_TIMES(pData[0]) == 1)
                    {
                        pData[1]++;
                    }
                }

                if(pData[1] >= _DELL_DELAY_MODE_INPUT_PORT)
                {
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                    if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                       ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                    {
                        SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                    }
#endif
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                }
#endif
                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
            SysSourceConvertSearchIndexExtendedPortToD4Port();
#else
            SysSourceConvertSearchIndexExtendedPortToD3Port();
#endif
#endif

            break;

        case _SOURCE_SWITCH_DELL_HOTKEY_FIXED:
        case _SOURCE_SWITCH_DELL_HOTKEY_AUTO:

            do
            {
                if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                        SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);

                        if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_FIXED)
                        {
                            g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));

                            SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_FIXED_PORT);
                        }
                        else if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_AUTO)
                        {
                            SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_AUTO_IN_GROUP);
                        }

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        return;
                    }
                }

                g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;

                if(GET_INPUTPORT_GROUP(g_ucSourceSearchIndex) == GET_INPUTPORT_GROUP(ucBackupSearchIndex))
                {
                    break;
                }

                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            if(g_ucSourceSearchIndex != ucBackupSearchIndex)
            {
                SET_SOURCE_SEARCH_TIME_INITIAL();

                SET_SOURCE_SEARCH_PORT_INITIAL();

                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }

            break;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        case _SOURCE_SWITCH_HP_SOURCE_SCAN:

            CLR_SOURCE_HP_SOURCE_JUDGE();

            if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) < GET_SOURCE_HP_TARGET_SEARCH_TIMES())
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                DebugMessageSystem("7. == SearchIndex ==", g_ucSourceSearchIndex);
                DebugMessageSystem("7. wuzanee test : Search Times", GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex));
            }

            if(SysSourceCheckTargetTimes(1) == _TRUE)
            {
                CLR_SOURCE_HP_FROM_TIMING_CHANGE();

                if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE)
                {
                    if(GET_SOURCE_HP_PORT_SWITCH_TARGET() < _INPUT_PORT_VALID)
                    {
                        if(GET_SOURCE_TYPE(GET_SOURCE_HP_PORT_SWITCH_TARGET()) != _SOURCE_NONE)
                        {
                            g_ucSourceSearchIndex = GET_SOURCE_HP_PORT_SWITCH_TARGET();

                            DebugMessageSystem("7. Bingo Switch Port!!!!!!!", 0);

                            SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            SET_SOURCE_SEARCH_PORT_INITIAL();

                            SET_SOURCE_SEARCH_TIME_REACTIVE();

                            SET_SOURCE_HP_SOURCE_JUDGE();

                            CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                            SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

                            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

                            SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                            return;
                        }
                    }

                    if(GET_SOURCE_TYPE(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) != _SOURCE_NONE)
                    {
                        g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));

                        DebugMessageSystem("7. Bingo Eeprom!!!!!!!", g_ucSourceSearchIndex);

                        SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        SET_SOURCE_HP_SOURCE_JUDGE();

                        CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                        return;
                    }

                    for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                    {
                        if(GET_SOURCE_TYPE(pData[0]) != _SOURCE_NONE)
                        {
                            g_ucSourceSearchIndex = pData[0];

                            DebugMessageSystem("7. Bingo Priority!!!!!!!", g_ucSourceSearchIndex);

                            SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            SET_SOURCE_SEARCH_PORT_INITIAL();

                            SET_SOURCE_SEARCH_TIME_REACTIVE();

                            SET_SOURCE_HP_SOURCE_JUDGE();

                            CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                            SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                            return;
                        }
                    }
                }
                else
                {
                    if(GET_SOURCE_TYPE(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) != _SOURCE_NONE)
                    {
                        DebugMessageSystem("7. Bingo Eeprom Fix Port!!!!!!!", g_ucSourceSearchIndex);

                        g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));

                        SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        SET_SOURCE_HP_SOURCE_JUDGE();

                        CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                        return;
                    }
                }
            }

            if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL) && (SysSourceCheckTargetTimes(GET_SOURCE_HP_TARGET_SEARCH_TIMES()) == _TRUE))
            {
                if(GET_SOURCE_HP_PORT_SWITCH_TARGET() > _INPUT_PORT_VALID)
                {
                    DebugMessageSystem("7. Search Finish !!!!!!!!!!!!!!!!!!!", g_ucSourceSearchIndex);
                    CLR_SOURCE_HP_TARGET_NO_SIGNAL();
                    SET_SOURCE_SWITCH_FINISH();
                    SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    SET_SOURCE_HP_TARGET_NO_SIGNAL();
                    ScalerTimerActiveTimerEvent(SEC(5), _SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);
                }
            }

            if((UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE) ||
               (((UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)) &&
                (GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL) && (GET_SOURCE_SWITCH_FINISH() == _FALSE)))
            {
                g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;
            }
            else
            {
                g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
            }

            if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
            {
                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_TIMING_CHANGE);

                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

                if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)
                {
                    g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
                }
            }
            else if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) == _DISPLAY_STATE_NO_SIGNAL)
            {
                SET_SOURCE_HP_SOURCE_JUDGE();

                if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)
                {
                    g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
                }
            }

            SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_TIME_REACTIVE();

            CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

            break;

        case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:

            CLR_SOURCE_HP_SOURCE_JUDGE();

            if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) < GET_SOURCE_HP_TARGET_SEARCH_TIMES())
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                DebugMessageSystem("7. == SearchIndex ==", g_ucSourceSearchIndex);
                DebugMessageSystem("7. wuzanee test : Search Times", GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex));
            }

            if(((SysSourceCheckTargetTimes(1) == _TRUE) ||
                (SysSourceCheckTargetTimes(2) == _TRUE) ||
                (SysSourceCheckTargetTimes(3) == _TRUE)))
            {
                if(GET_SOURCE_HP_PORT_SWITCH_TARGET() < (_INPUT_PORT_VALID))
                {
                    if(GET_SOURCE_TYPE(GET_SOURCE_HP_PORT_SWITCH_TARGET()) != _SOURCE_NONE)
                    {
                        g_ucSourceSearchIndex = GET_SOURCE_HP_PORT_SWITCH_TARGET();

                        DebugMessageSystem("7. Bingo Switch Port!!!!!!!", 0);

                        SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        SET_SOURCE_HP_SOURCE_JUDGE();

                        CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

                        SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                        return;
                    }
                }

                if((UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE) && (GET_SOURCE_HP_PORT_SWITCH_TARGET() > _INPUT_PORT_VALID))
                {
                    if(GET_SOURCE_TYPE(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) != _SOURCE_NONE)
                    {
                        g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));

                        DebugMessageSystem("7. Bingo Eeprom!!!!!!!", g_ucSourceSearchIndex);

                        SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        SET_SOURCE_HP_SOURCE_JUDGE();

                        CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                        return;
                    }

                    for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                    {
                        if(GET_SOURCE_TYPE(pData[0]) != _SOURCE_NONE)
                        {
                            g_ucSourceSearchIndex = pData[0];

                            DebugMessageSystem("7. Bingo Priority!!!!!!!", g_ucSourceSearchIndex);

                            SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            SET_SOURCE_SEARCH_PORT_INITIAL();

                            SET_SOURCE_SEARCH_TIME_REACTIVE();

                            SET_SOURCE_HP_SOURCE_JUDGE();

                            CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                            SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                            return;
                        }
                    }
                }
            }

            if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL) && (SysSourceCheckTargetTimes(GET_SOURCE_HP_TARGET_SEARCH_TIMES()) == _TRUE))
            {
                if(GET_SOURCE_HP_PORT_SWITCH_TARGET() > _INPUT_PORT_VALID)
                {
                    DebugMessageSystem("7. Search Finish2 !!!!!!!!!!!!!!!!!!!", g_ucSourceSearchIndex);
                    CLR_SOURCE_HP_TARGET_NO_SIGNAL();
                    SET_SOURCE_SWITCH_FINISH();
                    SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    DebugMessageSystem("7. Switch no signal !!!!!!!!!!!!!!!!!!!", g_ucSourceSearchIndex);
                    SET_SOURCE_HP_TARGET_NO_SIGNAL();
                    ScalerTimerActiveTimerEvent(SEC(UserInterfaceSourceGetHpSwitchOsdEventTime(_SOURCE_SWITCH_HP_SCAN_SWITCH_PORT)), _SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);
                }
            }

            if(((UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE) && (GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) == _DISPLAY_STATE_NO_SIGNAL)) ||
               (((UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)) && (GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL) && (GET_SOURCE_SWITCH_FINISH() == _FALSE)) ||
               (SysSourceCheckTargetTimes(GET_SOURCE_HP_TARGET_SEARCH_TIMES()) == _FALSE))
            {
                g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;
            }
            else
            {
                if(GET_SOURCE_HP_PORT_SWITCH_TARGET() < _INPUT_PORT_VALID)
                {
                    g_ucSourceSearchIndex = GET_SOURCE_HP_PORT_SWITCH_TARGET();
                }
            }

            if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
            {
                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_TIMING_CHANGE);

                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

                if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)
                {
                    g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
                }
            }
            else if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) == _DISPLAY_STATE_NO_SIGNAL)
            {
                SET_SOURCE_HP_SOURCE_JUDGE();

                if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)
                {
                    g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
                }
            }

            CLR_SOURCE_HP_TIMING_CHANGE();

            SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_TIME_REACTIVE();

            CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

            break;

        case _SOURCE_SWITCH_HP_TIMING_CHANGE:

            CLR_SOURCE_HP_SOURCE_JUDGE();

            if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL)
            {
                if(GET_SOURCE_HP_PORT_SWITCH_TARGET() < _INPUT_PORT_VALID)
                {
                    if(GET_SOURCE_TYPE(GET_SOURCE_HP_PORT_SWITCH_TARGET()) != _SOURCE_NONE)
                    {
                        g_ucSourceSearchIndex = GET_SOURCE_HP_PORT_SWITCH_TARGET();

                        DebugMessageSystem("7. Bingo Switch Port!!!!!!!", 0);

                        SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        SET_SOURCE_HP_SOURCE_JUDGE();

                        CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

                        SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                        return;
                    }

                    DebugMessageSystem("7. Switch no signal !!!!!!!!!!!!!!!!!!!", g_ucSourceSearchIndex);

                    SET_SOURCE_HP_TARGET_NO_SIGNAL();

                    ScalerTimerActiveTimerEvent(SEC((UserInterfaceSourceGetHpSwitchOsdEventTime(_SOURCE_SWITCH_HP_TIMING_CHANGE))), _SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);
                }
                else
                {
                    g_ucSourceSearchIndex = 0;

                    SET_SOURCE_SEARCH_TIME_INITIAL();

                    SET_SOURCE_SEARCH_PORT_INITIAL();

                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                    SET_SOURCE_SEARCH_TIME_REACTIVE();

                    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

                    SET_SOURCE_HP_FROM_TIMING_CHANGE();

                    SET_SOURCE_HP_TIMING_CHANGE();

                    SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);

                    CLR_SOURCE_HP_SOURCE_JUDGE();

                    CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                    SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                    return;
                }
            }

            if(GET_SOURCE_HP_PORT_SWITCH_TARGET() > _INPUT_PORT_VALID)
            {
                DebugMessageSystem("7. Search Finish3 !!!!!!!!!!!!!!!!!!!", g_ucSourceSearchIndex);
                CLR_SOURCE_HP_TARGET_NO_SIGNAL();
                SET_SOURCE_SWITCH_FINISH();
                SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
            }

            if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) == _DISPLAY_STATE_NO_SIGNAL) || (GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING))
            {
                SET_SOURCE_HP_SOURCE_JUDGE();
            }

            if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                if(SysSourceCheckTargetTimes(1) == _TRUE)
                {
                    SET_SOURCE_SWITCH_FINISH();
                    SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                }
            }

            if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL)
            {
                g_ucSourceSearchIndex = GET_SOURCE_HP_PORT_SWITCH_TARGET();
            }
            else if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE)
            {
                g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;
            }
            else if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)
            {
                g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
            }

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

            SET_SOURCE_SEARCH_TIME_REACTIVE();

            break;

        case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:

            CLR_SOURCE_HP_SOURCE_JUDGE();

            if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) < GET_SOURCE_HP_TARGET_SEARCH_TIMES())
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                DebugMessageSystem("7. == SearchIndex ==", g_ucSourceSearchIndex);
                DebugMessageSystem("7. wuzanee test : Search Times", GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex));
            }

            if(SysSourceCheckTargetTimes(1) == _TRUE)
            {
                if((GET_SOURCE_HP_PORT_SWITCH_TARGET() < _INPUT_PORT_VALID))
                {
                    BYTE ucTemp = 0;

                    for(ucTemp = 1; ucTemp <= _INPUT_PORT_VALID; ucTemp++)
                    {
                        if(GET_SOURCE_TYPE((GET_SOURCE_HP_PORT_SWITCH_TARGET() + ucTemp) % _INPUT_PORT_VALID) != _SOURCE_NONE)
                        {
                            g_ucSourceSearchIndex = ((GET_SOURCE_HP_PORT_SWITCH_TARGET() + ucTemp) % _INPUT_PORT_VALID);

                            DebugMessageSystem("7. Bingo Next Port!!!!!!!", g_ucSourceSearchIndex);

                            SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            SET_SOURCE_SEARCH_PORT_INITIAL();

                            SET_SOURCE_SEARCH_TIME_REACTIVE();

                            SET_SOURCE_HP_SOURCE_JUDGE();

                            CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                            SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

                            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

                            SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                            return;
                        }
                    }
                }

                // Switch to Target Search Scan Type
                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);
            }

            g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;

            SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_TIME_REACTIVE();

            CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

            break;

        case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:

            CLR_SOURCE_HP_SOURCE_JUDGE();

            if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) < GET_SOURCE_HP_TARGET_SEARCH_TIMES())
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                DebugMessageSystem("7. == SearchIndex ==", g_ucSourceSearchIndex);
                DebugMessageSystem("7. wuzanee test : Search Times", GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex));
            }

            if(SysSourceCheckTargetTimes(1) == _TRUE)
            {
                BYTE ucIndex = 0;

                for(ucIndex = 0; ucIndex < _INPUT_PORT_VALID; ucIndex++)
                {
                    if((GET_SOURCE_TYPE(ucIndex) != _SOURCE_NONE) &&
                       (SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)) != ucIndex))
                    {
                        g_ucSourceSearchIndex = ucIndex;

                        DebugMessageSystem("7. Bingo Priority!!!!!!!", g_ucSourceSearchIndex);

                        SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        SET_SOURCE_HP_SOURCE_JUDGE();

                        CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

                        SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                        return;
                    }
                }

                if(GET_SOURCE_TYPE(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) != _SOURCE_NONE)
                {
                    g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));

                    DebugMessageSystem("7. Bingo Eeprom!!!!!!!", g_ucSourceSearchIndex);

                    SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

                    SET_SOURCE_SEARCH_TIME_INITIAL();

                    SET_SOURCE_SEARCH_PORT_INITIAL();

                    SET_SOURCE_SEARCH_TIME_REACTIVE();

                    SET_SOURCE_HP_SOURCE_JUDGE();

                    CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                    SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);

                    return;
                }
            }

            if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL) && (SysSourceCheckTargetTimes(GET_SOURCE_HP_TARGET_SEARCH_TIMES()) == _TRUE))
            {
                DebugMessageSystem("7. Search Finish !!!!!!!!!!!!!!!!!!!", g_ucSourceSearchIndex);
                SET_SOURCE_SWITCH_FINISH();
                SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);
                SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));
            }

            g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;

            SET_SOURCE_TYPE(g_ucSourceSearchIndex, _SOURCE_NONE);

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_TIME_REACTIVE();

            CLR_SOURCE_PREDETECT(g_ucSourceSearchIndex);

            break;

#endif // End of #if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        default:
            break;
    }

    // Assign search index to 1P
    SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);
}

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
//--------------------------------------------------
// Description  : HDMI Externl Switch
// Input Value  : search port
// Output Value : TRUE -> Switch Port Success
//--------------------------------------------------
bit SysSource1pCheckD4ExternalHdmiAutoSwitch(void)
{
    if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT) == _FALSE)
    {
        // Transition: Default Mode -> Polling Mode
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        // when HP SCAN, set _SOURCE_SEARCH_POLLING_MODE then set _DISPLAY_STATE_NO_SIGNAL next loop
        if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE))
#else

#if((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE) || (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE))
        // when RTD SCAN, set _DISPLAY_STATE_NO_SIGNAL(JudgeHandler), then judge this `if`(SourceHandler) , set _SOURCE_SEARCH_POLLING_MODE(SourceHandler) this loop
        if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) == _DISPLAY_STATE_NO_SIGNAL) && (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE))
#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)
        if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE))
#endif

#endif
        {
            DebugMessageSystem("7. wuzanne test : Delay Switch to Polling 1st Active TimerEvent", 0);
            ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);
            CLR_SOURCE_HDMI_SWITCH_TIMEOUT();
        }
    }

#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    if((SysSourceGetInputPort() == _D4_INPUT_PORT) || (SysSourceGetInputPort() == _D14_INPUT_PORT) || (SysSourceGetInputPort() == _D15_INPUT_PORT))
#else
    if((SysSourceGetInputPort() == _D4_INPUT_PORT) || (SysSourceGetInputPort() == _D14_INPUT_PORT))
#endif
    {
        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
        {
            if(SysSourceGetInputPort() == _D4_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D4 Port Switch Select to D4", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D4_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D4);
            }
            else if(SysSourceGetInputPort() == _D14_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D14 Port Switch Select to D14", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D14_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D14);
            }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
            else if(SysSourceGetInputPort() == _D15_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D15 Port Switch Select to D15", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D15_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D15);
            }
#endif
            return _TRUE;
        }
        else
        {
            if(GET_SOURCE_HDMI_SWITCH_TIMEOUT() == _TRUE)
            {
                if((SysSourceGetInputPort() == _D14_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D14))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D14", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                    ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D14_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D14);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();
                    return _TRUE;
                }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                else if((SysSourceGetInputPort() == _D15_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D15))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D15", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                    ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D15_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D15);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();

                    return _TRUE;
                }

#endif
                else if((SysSourceGetInputPort() == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D4))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D4", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                    ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D4_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D4);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();

                    return _TRUE;
                }
            }
            else
            {
                if((SysSourceGetInputPort() == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4))
                {
                    return _TRUE;
                }
                else if((SysSourceGetInputPort() == _D14_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14))
                {
                    return _TRUE;
                }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                else if((SysSourceGetInputPort() == _D15_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15))
                {
                    return _TRUE;
                }
#endif
            }
        }
    }
    else
    {
        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
        {
            SysSourceHdmiExternalSwitchDefaultPort();
        }

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Convert Search Index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceConvertSearchIndexExtendedPortToD4Port(void)
{
    if(SysSourceGetInputPort() == _D14_INPUT_PORT)
    {
        if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)
        {
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
        }
    }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    else if(SysSourceGetInputPort() == _D15_INPUT_PORT)
    {
        if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)
        {
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Recover Search Index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceRecoverSearchIndexD4ToExtendedPort(void)
{
    if(SysSourceGetInputPort() == _D4_INPUT_PORT)
    {
        if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)
        {
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D14_INPUT_PORT);
        }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
        else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)
        {
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D15_INPUT_PORT);
        }
#endif
    }
}

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

//--------------------------------------------------
// Description  : HDMI Externl Switch
// Input Value  : search port
// Output Value : TRUE -> Switch Port Success
//--------------------------------------------------
bit SysSource1pCheckD3ExternalHdmiAutoSwitch(void)
{
    if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT) == _FALSE)
    {
        // Transition: Default Mode -> Polling Mode
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        // when HP SCAN, set _SOURCE_SEARCH_POLLING_MODE then set _DISPLAY_STATE_NO_SIGNAL next loop
        if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE))
#else

#if((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE) || (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE))
        // when RTD SCAN, set _DISPLAY_STATE_NO_SIGNAL(JudgeHandler), then judge this `if`(SourceHandler) , set _SOURCE_SEARCH_POLLING_MODE(SourceHandler) this loop
        if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) == _DISPLAY_STATE_NO_SIGNAL) && (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE))
#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)
        if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE))
#endif

#endif
        {
            DebugMessageSystem("7. wuzanne test : Delay Switch to Polling 1st Active TimerEvent", 0);
            ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);
            CLR_SOURCE_HDMI_SWITCH_TIMEOUT();
        }
    }

#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    if((SysSourceGetInputPort() == _D3_INPUT_PORT) || (SysSourceGetInputPort() == _D12_INPUT_PORT) || (SysSourceGetInputPort() == _D13_INPUT_PORT))
#else
    if((SysSourceGetInputPort() == _D3_INPUT_PORT) || (SysSourceGetInputPort() == _D12_INPUT_PORT))
#endif
    {
        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
        {
            if(SysSourceGetInputPort() == _D3_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D3 Port Switch Select to D3", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D3_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D3);
            }
            else if(SysSourceGetInputPort() == _D12_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D12 Port Switch Select to D12", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D12_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D12);
            }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
            else if(SysSourceGetInputPort() == _D13_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D13 Port Switch Select to D13", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D13_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D13);
            }
#endif
            return _TRUE;
        }
        else
        {
            if(GET_SOURCE_HDMI_SWITCH_TIMEOUT() == _TRUE)
            {
                if((SysSourceGetInputPort() == _D12_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D12))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D12", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                    ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D12_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D12);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();
                    return _TRUE;
                }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                else if((SysSourceGetInputPort() == _D13_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D13))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D13", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                    ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D13_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D13);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();

                    return _TRUE;
                }

#endif
                else if((SysSourceGetInputPort() == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D3))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D3", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                    ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D3_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D3);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();

                    return _TRUE;
                }
            }
            else
            {
                if((SysSourceGetInputPort() == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3))
                {
                    return _TRUE;
                }
                else if((SysSourceGetInputPort() == _D12_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12))
                {
                    return _TRUE;
                }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                else if((SysSourceGetInputPort() == _D13_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13))
                {
                    return _TRUE;
                }
#endif
            }
        }
    }
    else
    {
        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
        {
            SysSourceHdmiExternalSwitchDefaultPort();
        }

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Convert Search Index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceConvertSearchIndexExtendedPortToD3Port(void)
{
    if(SysSourceGetInputPort() == _D12_INPUT_PORT)
    {
        if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)
        {
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
        }
    }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    else if(SysSourceGetInputPort() == _D13_INPUT_PORT)
    {
        if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)
        {
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Recover Search Index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceRecoverSearchIndexD3ToExtendedPort(void)
{
    if(SysSourceGetInputPort() == _D3_INPUT_PORT)
    {
        if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)
        {
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D12_INPUT_PORT);
        }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
        else if(PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)
        {
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D13_INPUT_PORT);
        }
#endif
    }
}
#endif // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

//--------------------------------------------------
// Description  : Select HDMI Extended Port DDC Channel
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceHdmiExternalSwitchDefaultPort(void)
{
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
    // determine DDC channel from D4 or D14 when _SOURCE_SEARCH_DELAY_DEFAULT_MODE
    if(UserInterfaceSourceHdmiExternalSwitchDefaultPort() == _D4_INPUT_PORT)
    {
        DebugMessageSystem("7. wuzanne test : DDC Channel Default Switch to D4", 0);

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D4_INPUT_PORT);
#endif

        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D4);
    }
    else if(UserInterfaceSourceHdmiExternalSwitchDefaultPort() == _D14_INPUT_PORT)
    {
        DebugMessageSystem("7. wuzanne test : DDC Channel Default Switch to D14", 0);

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D14_INPUT_PORT);
#endif

        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D14);
    }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    else if(UserInterfaceSourceHdmiExternalSwitchDefaultPort() == _D15_INPUT_PORT)
    {
        DebugMessageSystem("7. wuzanne test : DDC Channel Default Switch to D15", 0);

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D15_INPUT_PORT);
#endif

        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D15);
    }
#endif

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

    // determine DDC channel from D3 or D12 when _SOURCE_SEARCH_DELAY_DEFAULT_MODE
    if(UserInterfaceSourceHdmiExternalSwitchDefaultPort() == _D3_INPUT_PORT)
    {
        DebugMessageSystem("7. wuzanne test : DDC Channel Default Switch to D3", 0);

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D3_INPUT_PORT);
#endif

        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D3);
    }
    else if(UserInterfaceSourceHdmiExternalSwitchDefaultPort() == _D12_INPUT_PORT)
    {
        DebugMessageSystem("7. wuzanne test : DDC Channel Default Switch to D12", 0);

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D12_INPUT_PORT);
#endif

        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D12);
    }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    else if(UserInterfaceSourceHdmiExternalSwitchDefaultPort() == _D13_INPUT_PORT)
    {
        DebugMessageSystem("7. wuzanne test : DDC Channel Default Switch to D13", 0);

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D13_INPUT_PORT);
#endif

        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D13);
    }
#endif
#endif
}
#endif // #if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Multi Port Switch Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceMultiSwitchPort(void)
{
    BYTE ucCount = 0;
    BYTE ucBackupSearchIndex = 0;
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    bit bHpPxpSubAutoScan = (UserInterfaceSourceGetHpPxpSubAutoScan() == _HP_PXP_SUB_AUTO_SCAN);
#endif

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
    SysSourceRecoverSearchIndexD4ToExtendedPort();
#else
    SysSourceRecoverSearchIndexD3ToExtendedPort();
#endif
#endif

    ucBackupSearchIndex = g_ucSourceSearchIndex;

    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
            // change SearchIndex to D4, due to GET_SOURCE_JUDGE() and GET_RGN_SOURCE_INDEX() is D4
            if((SysSourceGetInputPort() == _D14_INPUT_PORT) || (SysSourceGetInputPort() == _D15_INPUT_PORT))
            {
                g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
            }
#else
            // change SearchIndex to D3, due to GET_SOURCE_JUDGE() and GET_RGN_SOURCE_INDEX() is D3
            if((SysSourceGetInputPort() == _D12_INPUT_PORT) || (SysSourceGetInputPort() == _D13_INPUT_PORT))
            {
                g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
            }
#endif
#endif

            for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ucRegionIndex++)
            {
                if((GET_SOURCE_JUDGE(g_ucSourceSearchIndex) == _FALSE) &&
                   (GET_RGN_SOURCE_INDEX(ucRegionIndex) == g_ucSourceSearchIndex) &&
                   (GET_RGN_DISPLAY_STATE(ucRegionIndex) != _DISPLAY_STATE_NO_SIGNAL) &&
                   (GET_RGN_DISPLAY_ACTION(ucRegionIndex) != _DISPLAY_ACTION_NO_SIGNAL))
                {
#if(_SOURCE_AUTO_SEARCH_STYLE != _SOURCE_POLLING_EIZO_STYLE)
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_NO_SIGNAL);
#endif

                    // Flag switch finish when all no signal
                    if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                    }
                }
            }

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
            // change SearchIndex to D12/D13/D14/D15
            g_ucSourceSearchIndex = ucBackupSearchIndex;
#endif

            do
            {
                g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;

                if(SysSourceCheckMultiFixedPortTarget(g_ucSourceSearchIndex) == _TRUE)
                {
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
                    if(SysSourceMtpCheckD4ExternalHdmiAutoSwitch() == _TRUE)
#else
                    if(SysSourceMtpCheckD3ExternalHdmiAutoSwitch() == _TRUE)
#endif
#endif
                    {
                        break;
                    }
                }

                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            SET_SOURCE_SEARCH_TIME_INITIAL();
            SET_SOURCE_SEARCH_PORT_INITIAL();
            SET_SOURCE_SEARCH_TIME_REACTIVE();

            if((g_ucSourceSearchIndex != ucBackupSearchIndex) ||
               (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE))
            {
                if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    if((SysRegionGetDisplayStateCount(_DISPLAY_STATE_NO_SIGNAL) +
                        SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) +
                        SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE)) == ucRegionCount)
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                        SET_SOURCE_SEARCH_TIME_REACTIVE();
                    }
                    else
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                    }
                }
            }

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
            SysSourceConvertSearchIndexExtendedPortToD4Port();
#else
            SysSourceConvertSearchIndexExtendedPortToD3Port();
#endif
#endif
            break;

        case _SOURCE_SWITCH_AUTO_IN_GROUP:

#if(_SOURCE_AUTO_SEARCH_STYLE != _SOURCE_POLLING_EIZO_STYLE)
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
            // change SearchIndex to D4, due to GET_SOURCE_JUDGE() and GET_RGN_SOURCE_INDEX() is D4
            if((SysSourceGetInputPort() == _D14_INPUT_PORT) || (SysSourceGetInputPort() == _D15_INPUT_PORT))
            {
                g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
            }
#else
            // change SearchIndex to D3, due to GET_SOURCE_JUDGE() and GET_RGN_SOURCE_INDEX() is D3
            if((SysSourceGetInputPort() == _D12_INPUT_PORT) || (SysSourceGetInputPort() == _D13_INPUT_PORT))
            {
                g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
            }
#endif
#endif

            for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ucRegionIndex++)
            {
                if((GET_SOURCE_JUDGE(g_ucSourceSearchIndex) == _FALSE) &&
                   (GET_RGN_SOURCE_INDEX(ucRegionIndex) == g_ucSourceSearchIndex) &&
                   (ucRegionIndex != GET_SOURCE_AUTO_TARGET()) &&
                   (GET_RGN_DISPLAY_STATE(ucRegionIndex) != _DISPLAY_STATE_NO_SIGNAL) &&
                   (GET_RGN_DISPLAY_ACTION(ucRegionIndex) != _DISPLAY_ACTION_NO_SIGNAL))
                {
                    // Set display no signal for non-auto source
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_NO_SIGNAL);

                    // Flag switch finish when all signal
                    if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                    }
                }
            }
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
            // change SearchIndex to D12/D13/D14/D15
            g_ucSourceSearchIndex = ucBackupSearchIndex;
#endif
#endif

            // Switch to the next port by search priority with group limit.
            do
            {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        // Flag switch finish when all signal
                        if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                        {
                            SET_SOURCE_SWITCH_FINISH();
                        }

                        if((GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _FALSE) &&
                           (GET_RGN_DISPLAY_STATE(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_STATE_NO_SIGNAL) &&
                           (GET_RGN_DISPLAY_ACTION(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_ACTION_NO_SIGNAL))
                        {
                            // Set display no signal for auto search source
                            SysRegionSetDisplayStateBySearchIndex(GET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET()), _DISPLAY_STATE_NO_SIGNAL);

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
                            SysSourceConvertSearchIndexExtendedPortToD4Port();
#else
                            SysSourceConvertSearchIndexExtendedPortToD3Port();
#endif
#endif
                            return;
                        }
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) <= 1)
                {
                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        // Flag switch finish when all signal
                        if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                        {
                            SET_SOURCE_SWITCH_FINISH();
                        }

                        if((GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _FALSE) &&
                           (GET_RGN_DISPLAY_STATE(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_STATE_NO_SIGNAL) &&
                           (GET_RGN_DISPLAY_ACTION(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_ACTION_NO_SIGNAL))
                        {
                            // Set display no signal for auto search source
                            SysRegionSetDisplayStateBySearchIndex(GET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET()), _DISPLAY_STATE_NO_SIGNAL);

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
                            SysSourceConvertSearchIndexExtendedPortToD4Port();
#else
                            SysSourceConvertSearchIndexExtendedPortToD3Port();
#endif
#endif
                            return;
                        }
                    }

                    if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                    {
                        INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        if((SysRegionGetDisplayStateCount(_DISPLAY_STATE_NO_SIGNAL) +
                            SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) +
                            SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE)) != ucRegionCount)
                        {
                            SET_SOURCE_SWITCH_FINISH();
                        }
                    }
                }

#else
                if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        if((GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _FALSE) &&
                           (GET_RGN_DISPLAY_STATE(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_STATE_NO_SIGNAL) &&
                           (GET_RGN_DISPLAY_ACTION(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_ACTION_NO_SIGNAL))
                        {
                            // Set display no signal for auto search source
                            SysRegionSetDisplayStateBySearchIndex(GET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET()), _DISPLAY_STATE_NO_SIGNAL);
                        }

                        // Flag switch finish when all signal
                        if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                        {
                            SET_SOURCE_SWITCH_FINISH();
                        }
                    }
                }
#endif
                g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;

                if(SysSourceMultiSwitchInGroupCheck(ucBackupSearchIndex) == _TRUE)
                {
                    // Check source valid as fixed port or auto-search candidate
                    if((SysSourceCheckMultiFixedPortTarget(g_ucSourceSearchIndex) == _TRUE) ||
                       (SysSourceCheckMultiAutoSearchTarget(g_ucSourceSearchIndex) == _TRUE))
                    {
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
                        if(SysSourceMtpCheckD4ExternalHdmiAutoSwitch() == _TRUE)
#else
                        if(SysSourceMtpCheckD3ExternalHdmiAutoSwitch() == _TRUE)
#endif
#endif
                        {
                            break;
                        }
                    }
                }
                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            if(g_ucSourceSearchIndex != ucBackupSearchIndex)
            {
                SET_SOURCE_SEARCH_TIME_INITIAL();
                SET_SOURCE_SEARCH_PORT_INITIAL();
                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }

            if((g_ucSourceSearchIndex != ucBackupSearchIndex) ||
               (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE))
            {
                if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)

                    if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                        SET_SOURCE_SEARCH_TIME_REACTIVE();
                    }

#else
                    if((SysRegionGetDisplayStateCount(_DISPLAY_STATE_NO_SIGNAL) +
                        SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) +
                        SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE)) == ucRegionCount)
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                        SET_SOURCE_SEARCH_TIME_REACTIVE();
                    }
                    else
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                    }
#endif
                }
            }

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
            SysSourceConvertSearchIndexExtendedPortToD4Port();
#else
            SysSourceConvertSearchIndexExtendedPortToD3Port();
#endif
#endif
            break;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        case _SOURCE_SWITCH_HP_PXP_FIXED_PORT:

            for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ucRegionIndex++)
            {
                if((GET_SOURCE_JUDGE(g_ucSourceSearchIndex) == _FALSE) &&
                   (GET_RGN_SOURCE_INDEX(ucRegionIndex) == g_ucSourceSearchIndex) &&
                   (GET_RGN_DISPLAY_STATE(ucRegionIndex) != _DISPLAY_STATE_NO_SIGNAL) &&
                   (GET_RGN_DISPLAY_ACTION(ucRegionIndex) != _DISPLAY_ACTION_NO_SIGNAL))
                {
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_NO_SIGNAL);
                }
            }

            do
            {
                g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;

                if(SysSourceCheckMultiFixedPortTarget(g_ucSourceSearchIndex) == _TRUE)
                {
                    break;
                }

                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            SET_SOURCE_SEARCH_TIME_INITIAL();
            SET_SOURCE_SEARCH_PORT_INITIAL();
            SET_SOURCE_SEARCH_TIME_REACTIVE();

            if((g_ucSourceSearchIndex != ucBackupSearchIndex) ||
               (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE))
            {
                if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    if((SysRegionGetDisplayStateCount(_DISPLAY_STATE_NO_SIGNAL) +
                        SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) +
                        SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE)) == ucRegionCount)
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                        SET_SOURCE_SEARCH_TIME_REACTIVE();
                    }
                    else
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                    }
                }
            }

            if(bHpPxpSubAutoScan == _TRUE)
            {
                if((g_ucSourceSearchIndex == GET_RGN_SOURCE_INDEX(_REGION_INDEX_1)) &&
                   (GET_SOURCE_JUDGE(GET_RGN_SOURCE_INDEX(_REGION_INDEX_1)) == _FALSE) &&
                   (GET_SOURCE_SEARCH_TIMES(GET_RGN_SOURCE_INDEX(_REGION_INDEX_1)) == 0x01))
                {
                    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_PXP_SOURCE_SCAN);
                    SysSourceSearchTimeReset();
                }
                else
                {
                    if((g_ucSourceSearchIndex == GET_RGN_SOURCE_INDEX(_REGION_INDEX_1)) &&
                       (GET_SOURCE_SEARCH_TIMES((GET_RGN_SOURCE_INDEX(_REGION_INDEX_1))) == 0x00))
                    {
                        INCREASE_SOURCE_SEARCH_TIMES((GET_RGN_SOURCE_INDEX(_REGION_INDEX_1)));
                    }
                }
            }
            else if(GET_SOURCE_HP_PXP_MAIN_SOURCE_AUTO_SCAN() == _TRUE)
            {
                if(GET_SOURCE_HP_PORT_SWITCH_TARGET() < _INPUT_PORT_VALID)
                {
                    ScalerTimerActiveTimerEvent(SEC((UserInterfaceSourceGetHpSwitchOsdEventTime(_SOURCE_SWITCH_HP_PXP_FIXED_PORT))), _SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);
                }
                else
                {
                    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_PXP_SOURCE_SCAN);
                    DebugMessageSystem("7. PxP main start to scan other port", 0);
                }
            }

            break;

        case _SOURCE_SWITCH_HP_PXP_SOURCE_SCAN:

            if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);
            }

            g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;

            if(bHpPxpSubAutoScan == _TRUE)
            {
                if((GET_RGN_SOURCE_INDEX(_REGION_INDEX_0) == g_ucSourceSearchIndex) || (GET_RGN_SOURCE_INDEX(_REGION_INDEX_1) == g_ucSourceSearchIndex))
                {
                    if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                    {
                        INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);
                    }
                    g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;
                }
            }
            else if(GET_SOURCE_HP_PXP_MAIN_SOURCE_AUTO_SCAN() == _TRUE)
            {
                if(GET_RGN_SOURCE_INDEX(_REGION_INDEX_1) == g_ucSourceSearchIndex)
                {
                    if(GET_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex) == 0x00)
                    {
                        INCREASE_SOURCE_SEARCH_TIMES(g_ucSourceSearchIndex);
                    }

                    g_ucSourceSearchIndex = (g_ucSourceSearchIndex + 1) % _INPUT_PORT_VALID;
                }
            }

            if(SysSourceCheckTargetTimes(1) == _TRUE)
            {
                DebugMessageSystem("7. PxP scan first round ready", 0);
            }

            if(g_ucSourceSearchIndex != ucBackupSearchIndex)
            {
                SET_SOURCE_SEARCH_TIME_INITIAL();
                SET_SOURCE_SEARCH_PORT_INITIAL();
                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }

            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

            break;
#endif

        default:
            break;
    }
}

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
//--------------------------------------------------
// Description  : HDMI Externl Switch
// Input Value  : search port
// Output Value : TRUE -> Switch Port Success
//--------------------------------------------------
bit SysSourceMtpCheckD4ExternalHdmiAutoSwitch(void)
{
    if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT) == _FALSE)
    {
#if((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE) || (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE) || (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE))
        // when RTD SCAN, set _DISPLAY_STATE_NO_SIGNAL(JudgeHandler), then judge this `if`(SourceHandler) , set _SOURCE_SEARCH_POLLING_MODE(SourceHandler) this loop
        if(((SysRegionGetDisplayStateCount(_DISPLAY_STATE_NO_SIGNAL) + SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) + SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE)) == GET_RGN_MAX_DISPLAY_REGION()) &&
           (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE))
#endif
        {
            DebugMessageSystem("7. wuzanne test : Delay Switch to Polling 1st Active TimerEvent", 0);
            ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);
            CLR_SOURCE_HDMI_SWITCH_TIMEOUT();
        }
    }

#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    if((SysSourceGetInputPort() == _D4_INPUT_PORT) || (SysSourceGetInputPort() == _D14_INPUT_PORT) || (SysSourceGetInputPort() == _D15_INPUT_PORT))
#else
    if((SysSourceGetInputPort() == _D4_INPUT_PORT) || (SysSourceGetInputPort() == _D14_INPUT_PORT))
#endif
    {
        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
        {
            if(SysSourceGetInputPort() == _D4_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D4 Port Switch Select to D4", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D4_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D4);
            }
            else if(SysSourceGetInputPort() == _D14_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D14 Port Switch Select to D14", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D14_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D14);
            }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
            else if(SysSourceGetInputPort() == _D15_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D15 Port Switch Select to D15", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D15_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D15);
            }
#endif
            return _TRUE;
        }
        else
        {
            if(GET_SOURCE_HDMI_SWITCH_TIMEOUT() == _TRUE)
            {
                if((SysSourceGetInputPort() == _D14_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D14))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D14", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                    ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D14_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D14);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();

                    return _TRUE;
                }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                else if((SysSourceGetInputPort() == _D15_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D15))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D15", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                    ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D15_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D15);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();

                    return _TRUE;
                }

#endif
                else if((SysSourceGetInputPort() == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D4))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D4", 0);
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                    ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D4_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D4);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();

                    return _TRUE;
                }
            }
            else
            {
                if((SysSourceGetInputPort() == _D4_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4))
                {
                    return _TRUE;
                }
                else if((SysSourceGetInputPort() == _D14_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14))
                {
                    return _TRUE;
                }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
                else if((SysSourceGetInputPort() == _D15_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15))
                {
                    return _TRUE;
                }
#endif
            }
        }
    }
    else
    {
        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
        {
            SysSourceHdmiExternalSwitchDefaultPort();
        }

        return _TRUE;
    }

    return _FALSE;
}

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

//--------------------------------------------------
// Description  : HDMI Externl Switch
// Input Value  : search port
// Output Value : TRUE -> Switch Port Success
//--------------------------------------------------
bit SysSourceMtpCheckD3ExternalHdmiAutoSwitch(void)
{
    if(ScalerTimerSearchActiveTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT) == _FALSE)
    {
#if((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE) || (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE) || (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE))
        // when RTD SCAN, set _DISPLAY_STATE_NO_SIGNAL(JudgeHandler), then judge this `if`(SourceHandler) , set _SOURCE_SEARCH_POLLING_MODE(SourceHandler) this loop
        if(((SysRegionGetDisplayStateCount(_DISPLAY_STATE_NO_SIGNAL) + SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) + SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE)) == GET_RGN_MAX_DISPLAY_REGION()) &&
           (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE))
#endif
        {
            DebugMessageSystem("7. wuzanne test : Delay Switch to Polling 1st Active TimerEvent", 0);
            ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);
            CLR_SOURCE_HDMI_SWITCH_TIMEOUT();
        }
    }

#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    if((SysSourceGetInputPort() == _D3_INPUT_PORT) || (SysSourceGetInputPort() == _D12_INPUT_PORT) || (SysSourceGetInputPort() == _D13_INPUT_PORT))
#else
    if((SysSourceGetInputPort() == _D3_INPUT_PORT) || (SysSourceGetInputPort() == _D12_INPUT_PORT))
#endif
    {
        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
        {
            if(SysSourceGetInputPort() == _D3_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D3 Port Switch Select to D3", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D3_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D3);
            }
            else if(SysSourceGetInputPort() == _D12_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D12 Port Switch Select to D12", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D12_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D12);
            }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
            else if(SysSourceGetInputPort() == _D13_INPUT_PORT)
            {
                DebugMessageSystem("7. wuzanne test : D13 Port Switch Select to D13", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D13_INPUT_PORT);
#endif

                PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D13);
            }
#endif
            return _TRUE;
        }
        else
        {
            if(GET_SOURCE_HDMI_SWITCH_TIMEOUT() == _TRUE)
            {
                if((SysSourceGetInputPort() == _D12_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D12))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D12", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                    ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D12_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D12);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();

                    return _TRUE;
                }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                else if((SysSourceGetInputPort() == _D13_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D13))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D13", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                    ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D13_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D13);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();

                    return _TRUE;
                }

#endif
                else if((SysSourceGetInputPort() == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D3))
                {
                    DebugMessageSystem("7. wuzanne test : Polling Timeout switch to D3", 0);
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                    ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D3_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D3);

                    ScalerTimerActiveTimerEvent(_SOURCE_HDMI_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_HDMI_SWITCH_TIMEOUT);

                    CLR_SOURCE_HDMI_SWITCH_TIMEOUT();

                    return _TRUE;
                }
            }
            else
            {
                if((SysSourceGetInputPort() == _D3_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3))
                {
                    return _TRUE;
                }
                else if((SysSourceGetInputPort() == _D12_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12))
                {
                    return _TRUE;
                }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
                else if((SysSourceGetInputPort() == _D13_INPUT_PORT) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13))
                {
                    return _TRUE;
                }
#endif
            }
        }
    }
    else
    {
        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
        {
            SysSourceHdmiExternalSwitchDefaultPort();
        }

        return _TRUE;
    }

    return _FALSE;
}
#endif // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

//--------------------------------------------------
// Description  : Check whether Skip Extended Port when Auto Search
// Input Value  : ucSearchIndex --> source index
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
BYTE SysSourceMtpAutoSearchSkipExtendedPort(BYTE ucIndex)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(ucRegionIndex != GET_SOURCE_AUTO_TARGET())
        {
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
            // if any Fixed Region select D4/D14/D15, Auto Search will skip D4/D14/D15
            if((GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE) &&
               ((GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D4_INPUT_PORT)) ||
                (GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D14_INPUT_PORT)) ||
                (GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D15_INPUT_PORT))))
#else
            // if any Fixed Region select D4/D14, Auto Search will skip D4/D14
            if((GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE) &&
               ((GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D4_INPUT_PORT)) ||
                (GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D14_INPUT_PORT))))
#endif
            {
                if((SysSourceGetSpecificInputPort(ucIndex) == _D4_INPUT_PORT) || (SysSourceGetSpecificInputPort(ucIndex) == _D14_INPUT_PORT) || (SysSourceGetSpecificInputPort(ucIndex) == _D15_INPUT_PORT))
                {
                    return _TRUE;
                }
            }

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
            // if any Fixed Region select D3/D12/D13, Auto Search will skip D3/D12/D13
            if((GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE) &&
               ((GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D3_INPUT_PORT)) ||
                (GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D12_INPUT_PORT)) ||
                (GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D13_INPUT_PORT))))
#else
            // if any Fixed Region select D3/D12, Auto Search will skip D3/D12
            if((GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE) &&
               ((GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D3_INPUT_PORT)) ||
                (GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D12_INPUT_PORT))))
#endif
            {
                if((SysSourceGetSpecificInputPort(ucIndex) == _D3_INPUT_PORT) || (SysSourceGetSpecificInputPort(ucIndex) == _D12_INPUT_PORT) || (SysSourceGetSpecificInputPort(ucIndex) == _D13_INPUT_PORT))
                {
                    return _TRUE;
                }
            }
#endif
        }
    }

    return _FALSE;
}
#endif // #if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Multi Port Switch In Group Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysSourceMultiSwitchInGroupCheck(BYTE ucPreSearchIndex)
{
    bit bMultiSwitchInGroup = _FALSE;

    if(GET_INPUTPORT_GROUP(g_ucSourceSearchIndex) == GET_INPUTPORT_GROUP(ucPreSearchIndex))
    {
        bMultiSwitchInGroup = _TRUE;
    }
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
    else if(SysSourceMultiSwitchInPxpCheck(g_ucSourceSearchIndex, ucPreSearchIndex) == _TRUE)
    {
        bMultiSwitchInGroup = _TRUE;
    }
#endif

    return bMultiSwitchInGroup;
}
#endif

//--------------------------------------------------
// Description  : Port Initial Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceScanPortInitial(BYTE ucSearchIndex)
{
    EnumInputPort enumInputPort = GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex));
    EnumPortType enumPortType = GET_PORT_TYPE(GET_INPUTPORT_TYPE(ucSearchIndex));

    // Switch interface to target port
    SysSourceInterfaceSwitch(enumInputPort, enumPortType, GET_SOURCE_SEARCH_DELAY_MODE());

    // Initialize target port
    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
    {
        switch(enumPortType)
        {
#if(_VGA_SUPPORT == _ON)
            case _PORT_VGA:
                DebugMessageSystem("7. VGA Port Initial", enumInputPort);
                ScalerVgaSyncProcScanInitial(enumInputPort);
                break;
#endif

#if(_HDMI_SUPPORT == _ON)
            case _PORT_HDMI:
                DebugMessageSystem("7. TMDS Port Initial", enumInputPort);
                ScalerTmdsMacRxScanInitial(enumInputPort);
                break;
#endif

#if(_DP_SUPPORT == _ON)
            case _PORT_DP:
                DebugMessageSystem("7. DP Port Initial", enumInputPort);
                ScalerSyncDpScanInitial(enumInputPort);
                break;
#endif

            default:
                break;
        }
    }

#if(_DSC_DECODER_SUPPORT == _ON)
    SysDscDecoderMacArbiter(enumInputPort, enumPortType, _DSC_MAC_APPLY_DX_PORT);

#if(_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT == _ON)
    SysDscDecoderDxSupportJudge(enumInputPort, enumPortType);
#endif
#endif
}

//--------------------------------------------------
// Description  : Initial Source Switch Flags
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceInitial(void)
{
    BYTE ucIndex = 0;

    SysSourceSetSearchGroup(_NO_INPUT_PORT, _INPUT_PORT_GROUP_NONE);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_VGA, _SOURCE_DEFAULT_SEARCH_TIME_VGA);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_HDMI, _SOURCE_DEFAULT_SEARCH_TIME_HDMI);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_DP, _SOURCE_DEFAULT_SEARCH_TIME_DP);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_TYPE_C, _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C);

    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_VGA, _SOURCE_DEFAULT_SEARCH_TIME_VGA_NO_CABLE);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_HDMI, _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_DP, _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_TYPE_C, _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C_NO_CABLE);

#if(_DP_TBT_SUPPORT == _ON)
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_TBT, _SOURCE_DEFAULT_SEARCH_TIME_TBT);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_TBT, _SOURCE_DEFAULT_SEARCH_TIME_TBT_NO_CABLE);
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    g_ucSourceSearchIndex = 0;

#if(_MULTI_DISPLAY_MAX > 1)
    if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
    {
        SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_PXP_SOURCE_SCAN);
    }
    else
#endif
    {
        SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);
    }

    CLR_SOURCE_HP_TIMING_CHANGE();

    SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);

    SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));
#else
    if((UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != _SOURCE_SWITCH_AUTO_IN_GROUP) &&
       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != _SOURCE_SWITCH_FIXED_PORT))
    {
        UserCommonNVRamRestoreSystemData();
    }

    SET_SOURCE_SCAN_TYPE(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE));
#endif

#if(_MULTI_DISPLAY_MAX != 0x01)
    SET_SOURCE_AUTO_TARGET(UserCommonNVRamGetSystemData(_AUTO_SEARCH_TARGET));
#else
    SET_SOURCE_AUTO_TARGET(_REGION_INDEX_0);
#endif

    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:
            // Switch to region 0
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
            break;

        default:
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
            // Get Search Index from NVRam, it can distingusih D3/D12/D13's different Search Index
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemRegionPortData(GET_RGN_DISPLAY_REGION(GET_SOURCE_AUTO_TARGET())));
#else
            // Switch to auto target source
            g_ucSourceSearchIndex = GET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET());
#endif
            break;
    }

    // BG Scan Type, Stable Check Initial
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
    SET_SOURCE_BG_SCAN_TYPE(UserCommonNVRamGetSystemData(_SOURCE_BG_SCAN_TYPE));
    CLR_SOURCE_BG_STABLE_CHECK_EN();
#endif

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
    if(SysSourceGetInputPort() == _D4_INPUT_PORT)
    {
#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D4_INPUT_PORT);
#endif
        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D4);
        g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
    }
    else if(SysSourceGetInputPort() == _D14_INPUT_PORT)
    {
#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D14_INPUT_PORT);
#endif
        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D14);

        g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
    }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
    else if(SysSourceGetInputPort() == _D15_INPUT_PORT)
    {
#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D15_INPUT_PORT);
#endif

        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D15);

        g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
    }
#endif

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

    if(SysSourceGetInputPort() == _D3_INPUT_PORT)
    {
#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D3_INPUT_PORT);
#endif
        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D3);
        g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
    }
    else if(SysSourceGetInputPort() == _D12_INPUT_PORT)
    {
#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D12_INPUT_PORT);
#endif
        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D12);

        g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
    }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
    else if(SysSourceGetInputPort() == _D13_INPUT_PORT)
    {
#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D13_INPUT_PORT);
#endif

        PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D13);

        g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
    }
#endif
#endif // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
#endif // #if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)

    for(ucIndex = 0; ucIndex < _INPUT_PORT_VALID; ucIndex++)
    {
        SET_CABLE_DETECT(ucIndex, _FALSE);
    }

#if(_DIGITAL_PORT_SUPPORT == _ON)

    if(UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH) == _TRUE)
    {
        SET_DP_DC_OFF_HPD_HIGH();
    }
    else
    {
        CLR_DP_DC_OFF_HPD_HIGH();
    }

#if(_DP_SUPPORT == _ON)
    if(UserCommonNVRamGetSystemData(_DP_AUX_DIFF_MODE) == _TRUE)
    {
        SET_DP_AUX_DIFF_MODE();
    }
    else
    {
        CLR_DP_AUX_DIFF_MODE();
    }

    SET_DP_AUX_ADJR_SETTING(UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING));

    SET_DP_IRQ_TIME_10US(UserCommonNVRamGetSystemData(_DP_IRQ_TIME));

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    if(UserCommonNVRamGetSystemData(_DP_ILLEGAL_IDLE_PATTERN_CHECK) == _TRUE)
    {
        SET_DP_ILLEGAL_IDLE_PATTERN_CHECK();
    }
    else
#endif
    {
        CLR_DP_ILLEGAL_IDLE_PATTERN_CHECK();
    }
#endif

    if(UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT) == _TRUE)
    {
        SET_HDMI_HOTPLUG_TOGGLE();
        SET_HDMI_HOTPLUG_TIME(UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME));
    }
    else
    {
        CLR_HDMI_HOTPLUG_TOGGLE();
    }

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
    if(UserCommonNVRamGetSystemData(_COLORIMETRY_SEAMLESS_CHANGE) == _TRUE)
    {
        CLR_DIGITAL_COLOR_INFO_CHANGE_RESET();
    }
    else
#endif
    {
        SET_DIGITAL_COLOR_INFO_CHANGE_RESET();
    }

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
    SET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET();
#endif

// HDMI FreeSync Initial
#if((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_FREESYNC_SUPPORT_TMDS_D0(UserInterfaceFreeSyncGetEnable(_D0_INPUT_PORT));
#endif

#if((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_FREESYNC_SUPPORT_TMDS_D1(UserInterfaceFreeSyncGetEnable(_D1_INPUT_PORT));
#endif

#if((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_FREESYNC_SUPPORT_TMDS_D2(UserInterfaceFreeSyncGetEnable(_D2_INPUT_PORT));
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_FREESYNC_SUPPORT_TMDS_D3(UserInterfaceFreeSyncGetEnable(_D3_INPUT_PORT));
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_FREESYNC_SUPPORT_TMDS_D4(UserInterfaceFreeSyncGetEnable(_D4_INPUT_PORT));
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_FREESYNC_SUPPORT_TMDS_D5(UserInterfaceFreeSyncGetEnable(_D5_INPUT_PORT));
#endif

    // HDR10 Initial
#if(((_D0_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D0_DP_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON)))
    SET_RX0_HDR10_SUPPORT(UserInterfaceColorHDRGetHDR10ModeStatus(_D0_INPUT_PORT));
#endif

#if(((_D1_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D1_DP_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON)))
    SET_RX1_HDR10_SUPPORT(UserInterfaceColorHDRGetHDR10ModeStatus(_D1_INPUT_PORT));
#endif

#if(((_D2_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D2_DP_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON)))
    SET_RX2_HDR10_SUPPORT(UserInterfaceColorHDRGetHDR10ModeStatus(_D2_INPUT_PORT));
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    SET_RX3_HDR10_SUPPORT(UserInterfaceColorHDRGetHDR10ModeStatus(_D3_INPUT_PORT));
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    SET_RX4_HDR10_SUPPORT(UserInterfaceColorHDRGetHDR10ModeStatus(_D4_INPUT_PORT));
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    SET_RX5_HDR10_SUPPORT(UserInterfaceColorHDRGetHDR10ModeStatus(_D5_INPUT_PORT));
#endif

#endif

#if(_DUAL_DP_SUPPORT == _ON)
    CLR_SOURCE_DP_DUAL_SWITCH_TIMEOUT();
#endif
}

//--------------------------------------------------
// Description  : Source Stable Check Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysSourceStableCheck(BYTE ucRegionIndex)
{
    EnumSourceType enumSourceType = GET_RGN_SOURCE_TYPE(ucRegionIndex);
    EnumInputPort enumInputPort = GET_RGN_INPUT_PORT(ucRegionIndex);

    switch(enumSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            return ScalerVgaSyncProcStableDetect(enumInputPort, enumSourceType);
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            return ScalerTmdsMacRxStableDetect(enumInputPort, enumSourceType);

#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            return ScalerDpMacStreamRxStableDetect(enumInputPort, enumSourceType);
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Source Type
// Input Value  : None
// Output Value : Source Type --> VGA/DVI/HDMI/DP
//--------------------------------------------------
EnumSourceType SysSourceGetSourceType(void)
{
    return GET_SOURCE_TYPE(g_ucSourceSearchIndex);
}

//--------------------------------------------------
// Description  : Get Input Port
// Input Value  : None
// Output Value : enumInputPort --> Input Port
//--------------------------------------------------
EnumInputPort SysSourceGetInputPort(void)
{
    return SysSourceGetSpecificInputPort(g_ucSourceSearchIndex);
}

//--------------------------------------------------
// Description  : Get Input Port
// Input Value  : Search Index
// Output Value : enumInputPort --> Input Port
//--------------------------------------------------
EnumInputPort SysSourceGetSpecificInputPort(BYTE ucIndex)
{
    EnumInputPort enumInputPort = GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucIndex));

    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _NO_INPUT_PORT;
    }

    return enumInputPort;
}

//--------------------------------------------------
// Description  : Get port type from input port
// Input Value  : enumInputPort
// Output Value : EnumPortType
//--------------------------------------------------
EnumPortType SysSourceGetPortTypeFromInputPort(EnumInputPort enumInputPort)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _PORT_NONE;
    }

    return GET_PORT_TYPE(tINPUT_PORT_TYPE[enumInputPort]);
}

#if(_AUDIO_SUPPORT == _ON)
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP))))
//--------------------------------------------------
// Description  : Get Current Playback Search Index
// Input Value  : None
// Output Value : Search Index
//--------------------------------------------------
EnumInputPort SysSourceGetAudioPlaybackPort(void)
{
    return GET_AUDIO_PLAYBACK_SEARCH_INDEX();
}
#endif
#endif

//--------------------------------------------------
// Description  : Get Source Type
// Input Value  : enumInputPort --> Input Port(A0,A1,D0,D1,V1)
// Output Value : None
//--------------------------------------------------
void SysSourceSwitchInputPort(EnumInputPort enumInputPort)
{
    switch(GET_SOURCE_SCAN_TYPE())
    {
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        case _SOURCE_SWITCH_HP_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_TIMING_CHANGE:
        case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:
        case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:

            CLR_SOURCE_HP_TARGET_NO_SIGNAL();

            g_ucSourceSearchIndex = SysSourceConvertSearchPort(enumInputPort);

            DebugMessageSystem("7. OSD Switch Port to --> ", SysSourceConvertSearchPort(enumInputPort));

            SET_SOURCE_HP_PORT_SWITCH_TARGET(SysSourceConvertSearchPort(enumInputPort));

            CLR_SOURCE_HP_SOURCE_JUDGE();

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

            break;

        case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:

            g_ucSourceSearchIndex = 0;

            CLR_SOURCE_HP_SOURCE_JUDGE();

            CLR_SOURCE_HP_TIMING_CHANGE();

            SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);

            SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

            SysSourceInfoReset();

            break;

        case _SOURCE_SWITCH_HP_PXP_FIXED_PORT:

            g_ucSourceSearchIndex = SysSourceConvertSearchPort(enumInputPort);

            // Initialize source search if not judged already
            if(GET_SOURCE_JUDGE(g_ucSourceSearchIndex) == _FALSE)
            {
                SET_SOURCE_DETECTING();
                SET_SOURCE_SEARCH_TIME_INITIAL();
                SET_SOURCE_SEARCH_PORT_INITIAL();
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                SET_SOURCE_SEARCH_TIME_REACTIVE();
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
            }

            break;
#endif

        default:
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
            if(enumInputPort == _D4_INPUT_PORT)
            {
                // Before change External Switch's Setting, need to check Other Region is D4/D14/D15 or not
                // if((PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D4) && (SysSourceMtpAutoSearchSkipExtendedPort(SysSourceConvertSearchPort(_D4_INPUT_PORT)) == _FALSE))
                if(PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D4)
                {
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                    ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D4_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D4);
                }

                g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
            }
            else if(enumInputPort == _D14_INPUT_PORT)
            {
                // Before change External Switch's Setting, need to check Other Region is D4/D14/D15 or not
                // if((PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D14) && (SysSourceMtpAutoSearchSkipExtendedPort(SysSourceConvertSearchPort(_D4_INPUT_PORT)) == _FALSE))
                if(PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D14)
                {
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                    ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D14_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D14);
                }

                g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
            }
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
            else if(enumInputPort == _D15_INPUT_PORT)
            {
                // Before change External Switch's Setting, need to check Other Region is D4/D14/D15 or not
                // if((PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D15) && (SysSourceMtpAutoSearchSkipExtendedPort(SysSourceConvertSearchPort(_D4_INPUT_PORT)) == _FALSE))
                if(PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D15)
                {
#if((_TMDS_PHY_RX4_SUPPORT == _ON) || (_DP_PHY_RX4_SUPPORT == _ON))
                    ScalerGDIPhyRx4Z0Switch(_OFF);
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D15_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D15);
                }

                g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
            }
#endif

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

            if(enumInputPort == _D3_INPUT_PORT)
            {
                // Before change External Switch's Setting, need to check Other Region is D3/D12/D13 or not
                // if((PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D3) && (SysSourceMtpAutoSearchSkipExtendedPort(SysSourceConvertSearchPort(_D3_INPUT_PORT)) == _FALSE))
                if(PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D3)
                {
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                    ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D3_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D3);
                }

                g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
            }
            else if(enumInputPort == _D12_INPUT_PORT)
            {
                // Before change External Switch's Setting, need to check Other Region is D3/D12/D13 or not
                // if((PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D12) && (SysSourceMtpAutoSearchSkipExtendedPort(SysSourceConvertSearchPort(_D3_INPUT_PORT)) == _FALSE))
                if(PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D12)
                {
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                    ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D12_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D12);
                }

                g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
            }
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
            else if(enumInputPort == _D13_INPUT_PORT)
            {
                // Before change External Switch's Setting, need to check Other Region is D3/D12/D13 or not
                // if((PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D13) && (SysSourceMtpAutoSearchSkipExtendedPort(SysSourceConvertSearchPort(_D3_INPUT_PORT)) == _FALSE))
                if(PCB_GET_HDMI_SW_SELECT() != _SW_SEL_HDMI_D13)
                {
#if((_TMDS_PHY_RX3_SUPPORT == _ON) || (_DP_PHY_RX3_SUPPORT == _ON))
                    ScalerGDIPhyRx3Z0Switch(_OFF);
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
                    UserCommonEdidReloadHdmiExternalSwitchEmbeddedEdid(_D13_INPUT_PORT);
#endif

                    PCB_HDMI_SW_SELECT(_SW_SEL_HDMI_D13);
                }

                g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
            }
#endif
#endif // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
            else
#endif // #if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
            {
                g_ucSourceSearchIndex = SysSourceConvertSearchPort(enumInputPort);
            }

            // Initialize source search if not judged already
            if(GET_SOURCE_JUDGE(g_ucSourceSearchIndex) == _FALSE)
            {
                SET_SOURCE_DETECTING();
                SET_SOURCE_SEARCH_TIME_INITIAL();
                SET_SOURCE_SEARCH_PORT_INITIAL();
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                SET_SOURCE_SEARCH_TIME_REACTIVE();
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
            }

            break;
    }

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    if(GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_HP_TIMING_CHANGE)
    {
        CLR_SOURCE_HP_DETECTING();
    }

#else
    // Check region source index for auto search target
    if(SysRegionConvertPortToRegion(enumInputPort) == _DISPLAY_RGN_NONE)
    {
        if(GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_FIXED_PORT)
        {
#if(_EAGLE_SIGHT_SUPPORT == _ON)
            if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
            {
                SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, g_ucSourceSearchIndex);
                SET_RGN_SOURCE_INDEX(_REGION_INDEX_1, g_ucSourceSearchIndex);
            }
            else
#endif
            {
                SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSourceSearchIndex);
            }
        }
    }
#endif

#if(_DUAL_DP_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        if(SysSourceGetInputPort() == _DUAL_DP_INPUT_PORT)
        {
            if(UserCommonEdidDpGetDualPortEdidSelectStatus() == _FALSE)
            {
                UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_INPUT_PORT);
            }
        }
        else if((SysSourceGetInputPort() == _DUAL_DP_MAIN_PORT) || (SysSourceGetInputPort() == _DUAL_DP_SUB_PORT))
        {
            if(UserCommonEdidDpGetDualPortEdidSelectStatus() == _TRUE)
            {
                UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_MAIN_PORT);
                UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_SUB_PORT);
            }
        }
        else
        {
            if(UserInterfaceDpGetDualDefaultPort() == _DP_DUAL_PORT_USE_DUAL_PORT)
            {
                if(UserCommonEdidDpGetDualPortEdidSelectStatus() == _FALSE)
                {
                    UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_INPUT_PORT);
                }
            }
            else
            {
                if(UserCommonEdidDpGetDualPortEdidSelectStatus() == _TRUE)
                {
                    UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_MAIN_PORT);
                    UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_SUB_PORT);
                }
            }
        }
    }
    else
    {
        if(UserCommonEdidDpGetDualPortEdidSelectStatus() == _TRUE)
        {
            UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_MAIN_PORT);
            UserCommonEdidDpDualPortEdidTableSwitch(_DUAL_DP_SUB_PORT);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Get Source Type
// Input Value  : enumInputPort --> Input Port(A0,A1,D0,D1,V1)
// Output Value : None
//--------------------------------------------------
void SysSourceSwitchRegionSearchPort(EnumInputPort enumInputPort)
{
    g_ucSourceSearchIndex = SysSourceConvertSearchPort(enumInputPort);

    // Initialize source search if not judged already
    if(GET_SOURCE_JUDGE(g_ucSourceSearchIndex) == _FALSE)
    {
        SET_SOURCE_DETECTING();
        SET_SOURCE_SEARCH_TIME_INITIAL();
        SET_SOURCE_SEARCH_PORT_INITIAL();
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
        SET_SOURCE_SEARCH_TIME_REACTIVE();
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }

    // Check region source index for auto search target
    if(SysRegionConvertPortToRegion(enumInputPort) == _DISPLAY_RGN_NONE)
    {
        if(GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_FIXED_PORT)
        {
            SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSourceSearchIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Source Search Time Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceSearchTimeReset(void)
{
    BYTE ucSearchIndex = 0x00;

    for(ucSearchIndex = 0; ucSearchIndex < _INPUT_PORT_VALID; ucSearchIndex++)
    {
        CLR_SOURCE_SEARCH_TIMES(ucSearchIndex);
    }
}

//--------------------------------------------------
// Description  : Source Information Reset To Display Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceInfoResetToDisplayInitial(void)
{
    BYTE ucSearchIndex = 0x00;

    for(ucSearchIndex = 0; ucSearchIndex < _INPUT_PORT_VALID; ucSearchIndex++)
    {
        // Reset variables for unused interfaces
        if((GET_SOURCE_JUDGE(ucSearchIndex) == _FALSE) ||
           (SysRegionConvertSourceIndexToRegionIndex(ucSearchIndex) == _REGION_INDEX_NONE))
        {
            SET_SOURCE_TYPE(ucSearchIndex, _SOURCE_NONE);
            CLR_SOURCE_SEARCH_TIMES(ucSearchIndex);
            CLR_SOURCE_JUDGE(ucSearchIndex);
            CLR_SOURCE_PREDETECT(ucSearchIndex);

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
            CLR_SOURCE_BG_JUDGE(ucSearchIndex);
#endif

            // sync reset
            ScalerSyncResetProc(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex)));
        }
    }

    CLR_SOURCE_SWITCH_FINISH();

    // Clear Source Flags
    if(GET_SOURCE_JUDGE(g_ucSourceSearchIndex) == _FALSE)
    {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)

        if(GET_MODE_STATE() != _MODE_STATUS_POWER_SAVING)
        {
            CLR_SOURCE_ASUS_START_AUTO();
            CLR_SOURCE_ASUS_FIRST_START_AUTO();
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_ASUS_START_AUTO);
        }

#endif
        SET_SOURCE_DETECTING();
        SET_SOURCE_SEARCH_TIME_INITIAL();
        SET_SOURCE_SEARCH_TIME_REACTIVE();

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
        if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) ||
           ((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE) && (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE)))
#else
        if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) || (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE))
#endif
        {
            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
        }

        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }
    else
    {
        // Clear source detecting for interface switch
        CLR_SOURCE_DETECTING();
    }

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
    SET_SOURCE_EIZO_INFO_RESET();
    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_EIZO_SEARCH_FINISH);
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    CLR_SOURCE_HP_DETECTING();
#endif

    // Switch off unused interfaces
    SysSourceInterfaceSwitch(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex)), GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex)), GET_SOURCE_SEARCH_DELAY_MODE());
}

//--------------------------------------------------
// Description  : Source Information Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceInfoReset(void)
{
    BYTE ucSearchIndex = 0x00;

    for(ucSearchIndex = 0; ucSearchIndex < _INPUT_PORT_VALID; ucSearchIndex++)
    {
        // Interface Reset Process
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        if((GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_HP_SOURCE_SCAN) && (GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT) &&
           (GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_HP_SCAN_NEXT_PORT) && (GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN))
#endif
        {
            SET_SOURCE_TYPE(ucSearchIndex, _SOURCE_NONE);
        }
        CLR_SOURCE_SEARCH_TIMES(ucSearchIndex);
        CLR_SOURCE_JUDGE(ucSearchIndex);
        CLR_SOURCE_PREDETECT(ucSearchIndex);
    }

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
    CLR_SOURCE_BG_JUDGE(g_ucSourceBgDetectIndex);
#endif

    SET_SOURCE_SEARCH_PORT_INITIAL();

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)

    if(GET_MODE_STATE() != _MODE_STATUS_POWER_SAVING)
    {
        CLR_SOURCE_ASUS_START_AUTO();
        CLR_SOURCE_ASUS_FIRST_START_AUTO();
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_ASUS_START_AUTO);
    }

#endif

    // Clear Source Flags
    SET_SOURCE_DETECTING();
    SET_SOURCE_SEARCH_TIME_INITIAL();
    CLR_SOURCE_SWITCH_FINISH();

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
    SET_SOURCE_EIZO_INFO_RESET();
    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_EIZO_SEARCH_FINISH);
#endif

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
    if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) ||
       ((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE) && (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE)))
#else
    if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) || (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE))
#endif
    {
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

        SET_SOURCE_SEARCH_TIME_REACTIVE();
    }

    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
}

//--------------------------------------------------
// Description  : Source reset region process
// Input Value  : ucRegionIndex --> region index
// Output Value : None
//--------------------------------------------------
void SysSourceResetRegion(BYTE ucRegionIndex)
{
    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    if(enumDisplayMode == _DISPLAY_MODE_1P)
    {
        // Clear all source ready flags
        SysSourceInfoReset();

        // Perform sync reset
        ScalerSyncResetProc(GET_RGN_INPUT_PORT(ucRegionIndex));

        //=========================================================================
        // Reset DSC functions
        //=========================================================================

#if(_DSC_DECODER_SUPPORT == _ON)
        // For Mtp DSC Source On to Off Case, Check if OSD DSC Port Does Not Receive DSC Information, and Power off DSC block
        ScalerDscDecoderPowerCutControl(ScalerDscDecoderDxInputPortGetDscDecoderMac(GET_RGN_INPUT_PORT(ucRegionIndex)), _DSC_POWER_CUT_ON);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
        if(UserCommonNVRamGetSystemData(_COLORIMETRY_SEAMLESS_CHANGE) == _TRUE)
        {
            CLR_DIGITAL_COLOR_INFO_CHANGE_RESET();
        }
        else
        {
            SET_DIGITAL_COLOR_INFO_CHANGE_RESET();
        }
#endif

#if(_DM_COLORFORMAT_CHANGE_WO_RESET_SUPPORT == _ON)
        SET_DIGITAL_DM_COLOR_INFO_CHANGE_RESET();
#endif
#endif

        // Cancel timer events
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
    }
#if(_MULTI_DISPLAY_MAX != 0x01)
    else
    {
        BYTE ucIndex = 0x00;
        BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

        // Search for dulicated display region
        for(ucIndex = 0x00; ucIndex < ucRegionCount; ++ucIndex)
        {
            if((ucIndex != ucRegionIndex) &&
               (GET_RGN_SOURCE_INDEX(ucRegionIndex) == GET_RGN_SOURCE_INDEX(ucIndex)))
            {
                break;
            }
        }

        // Reset when no duplicate region exist, or source not judged
        if((ucIndex == ucRegionCount) ||
           (GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _FALSE))
        {
            DebugMessageSystem("SRC reset region", ucRegionIndex);

            // Clear source ready flags
            CLR_SOURCE_JUDGE(GET_RGN_SOURCE_INDEX(ucRegionIndex));
            SET_SOURCE_TYPE(GET_RGN_SOURCE_INDEX(ucRegionIndex), _SOURCE_NONE);
            CLR_SOURCE_PREDETECT(GET_RGN_SOURCE_INDEX(ucRegionIndex));

            // Clear source search times
            if((GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_AUTO_IN_GROUP) &&
               (GET_SOURCE_AUTO_TARGET() == ucRegionIndex))
            {
                SysSourceSearchTimeReset();
            }
            else
            {
                CLR_SOURCE_SEARCH_TIMES(GET_RGN_SOURCE_INDEX(ucRegionIndex));
            }

            // Clear source switch finished flag
            CLR_SOURCE_SWITCH_FINISH();

            // Reset source handler if current search index being reset
            if(GET_RGN_SOURCE_INDEX(ucRegionIndex) == g_ucSourceSearchIndex)
            {
                SET_SOURCE_DETECTING();
                SET_SOURCE_SEARCH_TIME_INITIAL();
                SET_SOURCE_SEARCH_TIME_REACTIVE();
                SET_SOURCE_SEARCH_PORT_INITIAL();
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
            }

            // Perform sync reset
            ScalerSyncResetProc(GET_RGN_INPUT_PORT(ucRegionIndex));

            //=========================================================================
            // Reset DSC functions
            //=========================================================================

#if(_DSC_DECODER_SUPPORT == _ON)
            ScalerDscDecoderPowerCutControl(ScalerDscDecoderDxInputPortGetDscDecoderMac(GET_RGN_INPUT_PORT(ucRegionIndex)), _DSC_POWER_CUT_ON);
#endif

            // Cancel measure related timing events
            if(ucRegionIndex == GET_SOURCE_MEASURE_TARGET_INDEX())
            {
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
            }

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
            SET_SOURCE_EIZO_INFO_RESET();
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_EIZO_SEARCH_FINISH);
#endif
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Source Cable Status Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceCableDetection(void)
{
    BYTE ucSearchIndex = 0;
#if(_HDMI_SUPPORT == _ON)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
    SysSourceHdmi5VDetection();
#endif
#endif

    for(ucSearchIndex = 0; ucSearchIndex < _INPUT_PORT_VALID; ++ucSearchIndex)
    {
        EnumInputPort enumInputPort = GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex));

        // Update cable status from pin
        ScalerSyncSetCableStatus(enumInputPort, ScalerSyncGetCablePinStatus(enumInputPort));

        // Update cable-related info
        SysSourceUpdateCableInfo(ucSearchIndex, enumInputPort);
    }

    for(ucSearchIndex = 0; ucSearchIndex < _INPUT_PORT_VALID; ++ucSearchIndex)
    {
        EnumInputPort enumInputPort = GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex));

        // Check if cable status changed
        if(SysSourceCheckCableStatusChange(ucSearchIndex, enumInputPort) == _TRUE)
        {
            // Update cable status with de-bounce
            ScalerTimerDelayXms(10);
            ScalerSyncSetCableStatus(enumInputPort, ScalerSyncGetCablePinStatus(enumInputPort));

            // Double-check cable status
            if(SysSourceCheckCableStatusChange(ucSearchIndex, enumInputPort) == _TRUE)
            {
                // Perform cable change process
                SysSourceCableStatustChangeProc(ucSearchIndex, enumInputPort);
            }
        }
    }
}

#if(_HDMI_SUPPORT == _ON)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
//--------------------------------------------------
// Description  : HDMI +5V Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceHdmi5VDetection(void)
{
#if(_D1_HDMI_SUPPORT == _ON)
    if(GET_HDMI_HOTPLUG_TOGGLE() == _TRUE)
    {
        if(UserInterfaceDpGetHdmi5VStatus(_D1_INPUT_PORT) == _TRUE)
        {
            if(GET_D1_HDMI_5V_STATUS() == _FALSE)
            {
                SET_D1_HDMI_5V_STATUS();
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_D1_TMDS_HPD_ASSERTED);
            }
        }
        else
        {
            if(GET_D1_HDMI_5V_STATUS() == _TRUE)
            {
                CLR_D1_HDMI_5V_STATUS();
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_D1_TMDS_HPD_ASSERTED);
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
            }
        }
    }
    else
    {
        SET_D1_HDMI_5V_STATUS();
        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
    }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
    if(GET_HDMI_HOTPLUG_TOGGLE() == _TRUE)
    {
        if(UserInterfaceDpGetHdmi5VStatus(_D2_INPUT_PORT) == _TRUE)
        {
            if(GET_D2_HDMI_5V_STATUS() == _FALSE)
            {
                SET_D2_HDMI_5V_STATUS();
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_D2_TMDS_HPD_ASSERTED);
            }
        }
        else
        {
            if(GET_D2_HDMI_5V_STATUS() == _TRUE)
            {
                CLR_D2_HDMI_5V_STATUS();
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_D2_TMDS_HPD_ASSERTED);
                PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
            }
        }
    }
    else
    {
        SET_D2_HDMI_5V_STATUS();
        PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
    }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    if(GET_HDMI_HOTPLUG_TOGGLE() == _TRUE)
    {
        if(UserInterfaceDpGetHdmi5VStatus(_D3_INPUT_PORT) == _TRUE)
        {
            if(GET_D3_HDMI_5V_STATUS() == _FALSE)
            {
                SET_D3_HDMI_5V_STATUS();
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_D3_TMDS_HPD_ASSERTED);
            }
        }
        else
        {
            if(GET_D3_HDMI_5V_STATUS() == _TRUE)
            {
                CLR_D3_HDMI_5V_STATUS();
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_D3_TMDS_HPD_ASSERTED);
                PCB_D3_HOTPLUG(_D3_HOT_PLUG_LOW);
            }
        }
    }
    else
    {
        SET_D3_HDMI_5V_STATUS();
        PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
    }
#endif

#if(_D4_HDMI_SUPPORT == _ON)
    if(GET_HDMI_HOTPLUG_TOGGLE() == _TRUE)
    {
        if(UserInterfaceDpGetHdmi5VStatus(_D4_INPUT_PORT) == _TRUE)
        {
            if(GET_D4_HDMI_5V_STATUS() == _FALSE)
            {
                SET_D4_HDMI_5V_STATUS();
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_D4_TMDS_HPD_ASSERTED);
            }
        }
        else
        {
            if(GET_D4_HDMI_5V_STATUS() == _TRUE)
            {
                CLR_D4_HDMI_5V_STATUS();
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_D4_TMDS_HPD_ASSERTED);
                PCB_D4_HOTPLUG(_D4_HOT_PLUG_LOW);
            }
        }
    }
    else
    {
        SET_D4_HDMI_5V_STATUS();
        PCB_D4_HOTPLUG(_D4_HOT_PLUG_HIGH);
    }
#endif

#if(_D5_HDMI_SUPPORT == _ON)
    if(GET_HDMI_HOTPLUG_TOGGLE() == _TRUE)
    {
        if(UserInterfaceDpGetHdmi5VStatus(_D5_INPUT_PORT) == _TRUE)
        {
            if(GET_D5_HDMI_5V_STATUS() == _FALSE)
            {
                SET_D5_HDMI_5V_STATUS();
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_D5_TMDS_HPD_ASSERTED);
            }
        }
        else
        {
            if(GET_D5_HDMI_5V_STATUS() == _TRUE)
            {
                CLR_D5_HDMI_5V_STATUS();
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_D5_TMDS_HPD_ASSERTED);
                PCB_D5_HOTPLUG(_D5_HOT_PLUG_LOW);
            }
        }
    }
    else
    {
        SET_D5_HDMI_5V_STATUS();
        PCB_D5_HOTPLUG(_D5_HOT_PLUG_HIGH);
    }
#endif
}
#endif
#endif

#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Freesync InputPort
// Input Value  : None
// Output Value : EnumInputPort
//--------------------------------------------------
EnumInputPort SysSourceGetFreesyncInputPort(void)
{
    return GET_RGN_INPUT_PORT(GET_SOURCE_MEASURE_TARGET_INDEX());
}
#endif

//--------------------------------------------------
// Description  : Check if cable status changed
// Input Value  : ucSearchIndex -> source search index
//                enumInputPort --> source search port
// Output Value : _TRUE of _FALSE
//--------------------------------------------------
bit SysSourceCheckCableStatusChange(BYTE ucSearchIndex, EnumInputPort enumInputPort)
{
    if(GET_CABLE_DETECT(ucSearchIndex) != ScalerSyncGetCablePinStatus(enumInputPort))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Update cable related port info
// Input Value  : ucSearchIndex --> search index
//                enumInputPort --> input port
// Output Value : None
//--------------------------------------------------
void SysSourceUpdateCableInfo(BYTE ucSearchIndex, EnumInputPort enumInputPort)
{
    enumInputPort = enumInputPort;

    SET_CABLE_STATUS_CHANGE(ucSearchIndex, _FALSE);

#if(_TYPE_C_DX_PORT_CTRL_SUPPORT == _ON)
    if(ScalerSyncGetTypeCSupportStatus(enumInputPort) == _TRUE)
    {
        ScalerSyncSetTypeCAltModeStatus(enumInputPort, SysUsbTypeCRxGetAltModeReady(enumInputPort));
    }
#endif
}

//--------------------------------------------------
// Description  : Process for each port on cable status change
// Input Value  : ucSearchIndex -> source search index
//                enumInputPort --> input port
// Output Value : None
//--------------------------------------------------
void SysSourceCableStatustChangeProc(BYTE ucSearchIndex, EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
        case _A0_INPUT_PORT:
#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:
#endif
            break;
        default:
            SET_SOURCE_SEARCH_PORT_INITIAL();
            break;
    }

    SET_CABLE_DETECT(ucSearchIndex, ScalerSyncGetCableStatus(enumInputPort));
    SET_CABLE_STATUS_CHANGE(ucSearchIndex, _TRUE);

    DebugMessageSystem("0. Cable Status Changed", enumInputPort);
}

//--------------------------------------------------
// Description  : Judge Source Search Times
// Input Value  : target search times
// Output Value : True --> search times of valid ports equal to target times
//--------------------------------------------------
bit SysSourceCheckTargetTimes(BYTE ucTargetTimes)
{
    BYTE ucSearchIndex = 0x00;

    for(ucSearchIndex = 0; ucSearchIndex < _INPUT_PORT_VALID; ucSearchIndex++)
    {
        if(GET_SOURCE_SEARCH_TIMES(ucSearchIndex) != ucTargetTimes)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Scan Type for User
// Input Value  : Preferred Scan Type
// Output Value : None
//--------------------------------------------------
void SysSourceSetScanType(BYTE ucScanType)
{
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

    if(ucScanType == _SOURCE_SWITCH_HP_TIMING_CHANGE)
    {
        SET_SOURCE_HP_SOURCE_JUDGE();
    }

    if(ucScanType == _SOURCE_SWITCH_HP_SOURCE_SCAN)
    {
        CLR_SOURCE_HP_SOURCE_JUDGE();
    }
#endif

    SET_SOURCE_SCAN_TYPE(ucScanType);
}

//--------------------------------------------------
// Description  : Get Scan Type for User
// Input Value  : None
// Output Value : Current Scan Type
//--------------------------------------------------
BYTE SysSourceGetScanType(void)
{
    return GET_SOURCE_SCAN_TYPE();
}

//--------------------------------------------------
// Description  : Convert Search Port to Search Index
// Input Value  : Input Port
// Output Value : Search Index
//--------------------------------------------------
BYTE SysSourceConvertSearchPort(EnumInputPort enumInputPort)
{
    BYTE ucSearchIndex = 0;

    while(ucSearchIndex < _INPUT_PORT_VALID)
    {
        if(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex)) == enumInputPort)
        {
            return ucSearchIndex;
        }

        ucSearchIndex++;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Source Cable Detect
// Input Value  : enumInputPort
// Output Value : _TRUE => Cable Detected, _FALSE => Cable Undected
//--------------------------------------------------
bit SysSourceGetCableDetect(EnumInputPort enumInputPort)
{
    return GET_CABLE_DETECT(SysSourceConvertSearchPort(enumInputPort));
}

//--------------------------------------------------
// Description  : Get Source Cable Status Change
// Input Value  : enumInputPort
// Output Value : _TRUE => Cable Status Changed
//--------------------------------------------------
bit SysSourceGetCableStatusChange(EnumInputPort enumInputPort)
{
#if(_TYPE_C_CABLE_STATUS_CHANGE_BY_ALT_MODE_SUPPORT == _ON)
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    if(ScalerTypeCRxCheckTypeCSupportOn(enumInputPort) == _TRUE)
    {
        return SysUsbTypeCGetAltModeStatusChange(ScalerTypeCDxConvertToPcbPort(enumInputPort));
    }
    else
#endif
#endif
    {
        return GET_CABLE_STATUS_CHANGE(SysSourceConvertSearchPort(enumInputPort));
    }
}

//--------------------------------------------------
// Description  : Get Source predetect status
// Input Value  : enumInputPort
// Output Value : _TRUE if pre-detect passed
//--------------------------------------------------
bit SysSourceGetPreDetect(EnumInputPort enumInputPort)
{
    return GET_SOURCE_PREDETECT(SysSourceConvertSearchPort(enumInputPort));
}

//--------------------------------------------------
// Description  : Source Reset when Cable Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceCableResetProc(void)
{
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_TIMING_CHANGE)
    {
        SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);
    }

    SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);
#endif
}

//--------------------------------------------------
// Description  : Source First Active Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceFirstActiveProc(void)
{
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    EnumDisplayMode enumDisplayMode = _DISPLAY_MODE_NONE;
    enumDisplayMode = GET_DISPLAY_MODE();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(SysModeGetEagleSightSupport(enumDisplayMode), enumDisplayMode);
#endif

    if((enumDisplayMode == _DISPLAY_MODE_1P) &&
       ((SysRegionGetDisplayState(GET_RGN_DISPLAY_REGION(_REGION_INDEX_0)) == _DISPLAY_STATE_DISPLAY_READY) || (SysRegionGetDisplayState(GET_RGN_DISPLAY_REGION(_REGION_INDEX_0)) == _DISPLAY_STATE_ACTIVE)))
    {
        SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));
    }
#endif
}

//--------------------------------------------------
// Description  : Source Power Off Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourcePowerOffProc(void)
{
    // Clear Display event flag
    CLR_RGN_DISPLAY_INFO_ALL();

    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:
            // Switch to region 0
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
            // g_ucSourceSearchIndex=D14/D15 in NVRAM => convert Index to g_ucSourceSearchIndex=D4 for D14/D15 when DC OFF/ON
            SysSourceConvertSearchIndexExtendedPortToD4Port();
#else
            // g_ucSourceSearchIndex=D12/D13 in NVRAM => convert Index to g_ucSourceSearchIndex=D3 for D12/D13 when DC OFF/ON
            SysSourceConvertSearchIndexExtendedPortToD3Port();
#endif
#endif
            break;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        case _SOURCE_SWITCH_HP_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_TIMING_CHANGE:
        case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:
        case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:

            CLR_SOURCE_HP_SOURCE_JUDGE();

            SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

            CLR_SOURCE_HP_TIMING_CHANGE();

            CLR_SOURCE_HP_TARGET_NO_SIGNAL();

            SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);
            CLR_SOURCE_HP_FROM_TIMING_CHANGE();

            SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

            break;
#endif

        default:
            // Switch to auto-search region
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemRegionPortData(SysRegionGetDisplayRegion(GET_SOURCE_AUTO_TARGET())));

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
            // g_ucSourceSearchIndex=D14/D14 in NVRAM => convert Index to g_ucSourceSearchIndex=D4 for D14/D15 when DC OFF/ON
            SysSourceConvertSearchIndexExtendedPortToD4Port();
#else
            // g_ucSourceSearchIndex=D12/D13 in NVRAM => convert Index to g_ucSourceSearchIndex=D3 for D12/D13 when DC OFF/ON
            SysSourceConvertSearchIndexExtendedPortToD3Port();
#endif
#endif

            SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSourceSearchIndex);
            break;
    }

    if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_FIXED)
    {
        SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_FIXED_PORT);
    }
    else if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_AUTO)
    {
        SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_AUTO_IN_GROUP);
    }

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DIGITAL_PORT_SUPPORT == _ON))

    if(GET_HDMI_HOTPLUG_TOGGLE() == _OFF)
    {
        if((GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex))) == _D1_INPUT_PORT)
        {
            ScalerSyncCompatibleModeConfigAllSwitchToDxFlag(_D1_INPUT_PORT);
        }
        else if((GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex))) == _D2_INPUT_PORT)
        {
            ScalerSyncCompatibleModeConfigAllSwitchToDxFlag(_D2_INPUT_PORT);
        }
        else if((GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex))) == _D3_INPUT_PORT)
        {
            ScalerSyncCompatibleModeConfigAllSwitchToDxFlag(_D3_INPUT_PORT);
        }
        else if((GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex))) == _D4_INPUT_PORT)
        {
            ScalerSyncCompatibleModeConfigAllSwitchToDxFlag(_D4_INPUT_PORT);
        }
        else if((GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex))) == _D5_INPUT_PORT)
        {
            ScalerSyncCompatibleModeConfigAllSwitchToDxFlag(_D5_INPUT_PORT);
        }
    }
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    CLR_SOURCE_HP_DETECTING();
#endif
}

//--------------------------------------------------
// Description  : Input Port Search Priority Select
// Input Value  : Priority and Input Port
// Output Value : None
//--------------------------------------------------
void SysSource1PSetSearchPriority(EnumInputPort enumInputPort, EnumSourceSearchPortPriority enumSourcePriority)
{
    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    enumDisplayMode = ScalerRegionEagleSightTransDisplayMode(enumDisplayMode);
#endif

    if(enumDisplayMode != _DISPLAY_MODE_1P)
    {
        return;
    }

    if((enumSourcePriority < _INPUT_PORT_PRIORITY_NONE) &&
       (enumSourcePriority < _INPUT_PORT_VALID) &&
       (enumInputPort < _NO_INPUT_PORT))
    {
        BYTE ucSearchIndexBackup = SysSourceConvertSearchPort(enumInputPort);
        BYTE ucInputPortBackup = SysSourceGetSpecificInputPort(enumSourcePriority);

        if(ucSearchIndexBackup == enumSourcePriority)
        {
            return;
        }

        SET_SOURCE_TYPE_BACKUP(GET_SOURCE_TYPE(enumSourcePriority));
        SET_SOURCE_SEARCH_TIMES_BACKUP(GET_SOURCE_SEARCH_TIMES(enumSourcePriority));
        SET_SOURCE_JUDGE_BACKUP(GET_SOURCE_JUDGE(enumSourcePriority));
        SET_SOURCE_PREDETECT_BACKUP(GET_SOURCE_PREDETECT(enumSourcePriority));
        SET_CABLE_DETECT_BACKUP(GET_CABLE_DETECT(enumSourcePriority));
        SET_CABLE_STATUS_CHANGE_BACKUP(GET_CABLE_STATUS_CHANGE(enumSourcePriority));

        SET_SOURCE_TYPE(enumSourcePriority, GET_SOURCE_TYPE(ucSearchIndexBackup));
        SET_SOURCE_SEARCH_TIMES(enumSourcePriority, GET_SOURCE_SEARCH_TIMES(ucSearchIndexBackup));
        SET_SOURCE_JUDGE(enumSourcePriority, GET_SOURCE_JUDGE(ucSearchIndexBackup));
        SET_SOURCE_PREDETECT(enumSourcePriority, GET_SOURCE_PREDETECT(ucSearchIndexBackup));
        SET_CABLE_DETECT(enumSourcePriority, GET_CABLE_DETECT(ucSearchIndexBackup));
        SET_CABLE_STATUS_CHANGE(enumSourcePriority, GET_CABLE_STATUS_CHANGE(ucSearchIndexBackup));

        SET_SOURCE_TYPE(ucSearchIndexBackup, GET_SOURCE_TYPE_BACKUP());
        SET_SOURCE_SEARCH_TIMES(ucSearchIndexBackup, GET_SOURCE_SEARCH_TIMES_BACKUP());
        SET_SOURCE_JUDGE(ucSearchIndexBackup, GET_SOURCE_JUDGE_BACKUP());
        SET_SOURCE_PREDETECT(ucSearchIndexBackup, GET_SOURCE_PREDETECT_BACKUP());
        SET_CABLE_DETECT(ucSearchIndexBackup, GET_CABLE_DETECT_BACKUP());
        SET_CABLE_STATUS_CHANGE(ucSearchIndexBackup, GET_CABLE_STATUS_CHANGE_BACKUP());

        if(GET_RGN_SOURCE_INDEX(_REGION_INDEX_0) == enumSourcePriority)
        {
            SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, ucSearchIndexBackup);
        }
        else if(GET_RGN_SOURCE_INDEX(_REGION_INDEX_0) == ucSearchIndexBackup)
        {
            SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, enumSourcePriority);
        }

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            SET_RGN_SOURCE_INDEX(_REGION_INDEX_1, GET_RGN_SOURCE_INDEX(_REGION_INDEX_0));
        }
#endif

        if(enumSourcePriority == g_ucSourceSearchIndex)
        {
            g_ucSourceSearchIndex = ucSearchIndexBackup;
        }
        else if(ucSearchIndexBackup == g_ucSourceSearchIndex)
        {
            g_ucSourceSearchIndex = enumSourcePriority;
        }


        g_penumSourceSearchPriority[enumSourcePriority] = enumInputPort;
        g_penumSourceSearchPriority[ucSearchIndexBackup] = ucInputPortBackup;

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
        CLR_SOURCE_BG_JUDGE(g_ucSourceBgDetectIndex);

        if(GET_SOURCE_BG_SCAN_TYPE() == _SOURCE_BG_SWITCH_AUTO_WITHOUT_GROUP)
        {
            g_ucSourceBgDetectIndex = 0;
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Input Port Search Group Select
// Input Value  : Group and Input Port
// Output Value : None
//--------------------------------------------------
void SysSourceSetSearchGroup(EnumInputPort enumInputPort, EnumSourceSearchGroup enumSourceGroup)
{
    if((enumInputPort >= _NO_INPUT_PORT) ||
       (enumSourceGroup >= _INPUT_PORT_GROUP_NONE))
    {
        return;
    }

    g_penumSourceSearchGroup[enumInputPort] = enumSourceGroup;
}

//--------------------------------------------------
// Description  : Input Port Default Search Time Setting
// Input Value  : enumInputType --> VGA/HDMI/DP
///               usDefaultSearchTime --> Default Search Time
// Output Value : None
//--------------------------------------------------
void SysSourceSetDefaultSearchTime(EnumSourceInputType enumInputType, WORD usDefaultSearchTime)
{
    switch(enumInputType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_VGA:
            g_usSourceDefaultSearchTimeVga = usDefaultSearchTime;
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_HDMI:
            g_usSourceDefaultSearchTimeHdmi = usDefaultSearchTime;
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_DP:
            g_usSourceDefaultSearchTimeDp = usDefaultSearchTime;
            break;

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_TYPE_C:
            g_usSourceDefaultSearchTimeTypeC = usDefaultSearchTime;
            break;
#endif

#if(_DP_TBT_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_TBT:
            g_usSourceDefaultSearchTimeTbt = usDefaultSearchTime;
            break;
#endif
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Input Port No Cable Search Time Setting
// Input Value  : enumInputType --> VGA/HDMI/DP
///               usNoCableSearchTime --> No Cable Search Time
// Output Value : None
//--------------------------------------------------
void SysSourceSetNoCableSearchTime(EnumSourceInputType enumInputType, WORD usNoCableSearchTime)
{
    switch(enumInputType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_VGA:
            g_usSourceNoCableSearchTimeVga = usNoCableSearchTime;
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_HDMI:
            g_usSourceNoCableSearchTimeHdmi = usNoCableSearchTime;
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_DP:
            g_usSourceNoCableSearchTimeDp = usNoCableSearchTime;
            break;

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_TYPE_C:
            g_usSourceNoCableSearchTimeTypeC = usNoCableSearchTime;
            break;
#endif

#if(_DP_TBT_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_TBT:
            g_usSourceNoCableSearchTimeTbt = usNoCableSearchTime;
            break;
#endif
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Input Port Delay Reactive time
// Input Value  : enumPortType --> VGA/HDMI/DP
// Output Value : Search Time
//--------------------------------------------------
WORD SysSourceGetDelayReactiveSearchTime(EnumPortType enumPortType)
{
    switch(enumPortType)
    {
        case _PORT_VGA:
            return SEC(2);

#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
            return ScalerTmdsMacRxGetReactiveSearchTime(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex)));
#endif

        case _PORT_DP:

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
            if((GET_SOURCE_HP_DETECTING() == _TRUE) && (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_TIMING_CHANGE))
            {
                return _NONE_SEARCH_TIME;
            }
#endif

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_DP_SUPPORT == _ON) && (_USB_SUPPORT == _ON))
            if(SysUsbTypeCRxCheckTypeCPortControllerExist(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex))) == _TRUE)
            {
                return SEC(5);
            }
            else
#endif
            {
                return SEC(4.5);
            }

        default:
            return _NONE_SEARCH_TIME;
    }
}

//--------------------------------------------------
// Description  : Input Port Default Search Time Setting
// Input Value  : enumInputPort --> source search port
//                enumPortType --> VGA/HDMI/DP
// Output Value : Default Search Time
//--------------------------------------------------
WORD SysSourceGetDefaultSearchTime(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    enumInputPort = enumInputPort;

    switch(enumPortType)
    {
#if(_VGA_SUPPORT == _ON)
        case _PORT_VGA:
            return g_usSourceDefaultSearchTimeVga;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
#if(_HDMI_FRL_SUPPORT == _ON)
            if(ScalerTmdsMacRxGetHdmiVer(enumInputPort) != _FROM_HDMI_TMDS_MAC)
            {
                return _SOURCE_DEFAULT_SEARCH_TIME_HDMI_FRL;
            }
            else
#endif
            {
                return g_usSourceDefaultSearchTimeHdmi;
            }
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:

#if((_USB_SUPPORT == _ON) && (_TYPE_C_PORT_CTRL_SUPPORT == _ON))
            if(SysUsbTypeCRxCheckTypeCPortControllerExist(enumInputPort) == _TRUE)
            {
                return g_usSourceDefaultSearchTimeTypeC;
            }
#endif

#if(_DP_TBT_SUPPORT == _ON)
            if(SysDpGetConnectorType(enumInputPort) == _DP_CONNECTOR_TBT)
            {
                return g_usSourceDefaultSearchTimeTbt;
            }
#endif

            return g_usSourceDefaultSearchTimeDp;
#endif

        default:
            return _NONE_SEARCH_TIME;
    }
}

//--------------------------------------------------
// Description  : Input Port No Cable Search Time Setting
// Input Value  : enumInputPort --> source search port
//                enumPortType --> VGA/HDMI/DP
// Output Value : No Cable Search Time
//--------------------------------------------------
WORD SysSourceGetNoCableSearchTime(EnumInputPort enumInputPort, EnumPortType enumPortType)
{
    enumInputPort = enumInputPort;

    switch(enumPortType)
    {
#if(_VGA_SUPPORT == _ON)
        case _PORT_VGA:
            return g_usSourceNoCableSearchTimeVga;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
            return g_usSourceNoCableSearchTimeHdmi;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:

#if((_USB_SUPPORT == _ON) && (_TYPE_C_PORT_CTRL_SUPPORT == _ON))
            if(SysUsbTypeCRxCheckTypeCPortControllerExist(enumInputPort) == _TRUE)
            {
                return g_usSourceNoCableSearchTimeTypeC;
            }
#endif

#if(_DP_TBT_SUPPORT == _ON)
            if(SysDpGetConnectorType(enumInputPort) == _DP_CONNECTOR_TBT)
            {
                return g_usSourceNoCableSearchTimeTbt;
            }
#endif

            return g_usSourceNoCableSearchTimeDp;

#endif

        default:
            return _NONE_SEARCH_TIME;
    }
}

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Check whether source can be switch to in auto-search scan mode
// Input Value  : ucSearchIndex --> source index
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceCheckMultiFixedPortTarget(BYTE ucSearchIndex)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE)
        {
            continue;
        }

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
        if(((GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D4_INPUT_PORT)) && (ucSearchIndex == SysSourceConvertSearchPort(_D4_INPUT_PORT)) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D4)) ||
           ((GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D4_INPUT_PORT)) && (ucSearchIndex == SysSourceConvertSearchPort(_D14_INPUT_PORT)) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D14)) ||
#if((_D15_INPUT_PORT_TYPE == _D15_HDMI_PORT) && (_D15_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D4))
           ((GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D4_INPUT_PORT)) && (ucSearchIndex == SysSourceConvertSearchPort(_D15_INPUT_PORT)) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D15)) ||
#endif
           ((GET_RGN_SOURCE_INDEX(ucRegionIndex) != SysSourceConvertSearchPort(_D4_INPUT_PORT)) && (GET_RGN_SOURCE_INDEX(ucRegionIndex) == ucSearchIndex)))

#else // #if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)

        if(((GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D3_INPUT_PORT)) && (ucSearchIndex == SysSourceConvertSearchPort(_D3_INPUT_PORT)) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D3)) ||
           ((GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D3_INPUT_PORT)) && (ucSearchIndex == SysSourceConvertSearchPort(_D12_INPUT_PORT)) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D12)) ||
#if((_D13_INPUT_PORT_TYPE == _D13_HDMI_PORT) && (_D13_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D3))
           ((GET_RGN_SOURCE_INDEX(ucRegionIndex) == SysSourceConvertSearchPort(_D3_INPUT_PORT)) && (ucSearchIndex == SysSourceConvertSearchPort(_D13_INPUT_PORT)) && (PCB_GET_HDMI_SW_SELECT() == _SW_SEL_HDMI_D13)) ||
#endif
           ((GET_RGN_SOURCE_INDEX(ucRegionIndex) != SysSourceConvertSearchPort(_D3_INPUT_PORT)) && (GET_RGN_SOURCE_INDEX(ucRegionIndex) == ucSearchIndex)))
#endif

#else // #if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
        if(GET_RGN_SOURCE_INDEX(ucRegionIndex) == ucSearchIndex)
#endif
        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE)

            if((GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_FIXED_PORT) &&
               (GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _FALSE))
            {
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
                if((SysSourceGetInputPort() == _D14_INPUT_PORT) || (SysSourceGetInputPort() == _D15_INPUT_PORT))
                {
                    g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
                }
#else
                if((SysSourceGetInputPort() == _D12_INPUT_PORT) || (SysSourceGetInputPort() == _D13_INPUT_PORT))
                {
                    g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
                }
#endif
#endif
                SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSourceSearchIndex);

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
                g_ucSourceSearchIndex = ucSearchIndex;
#endif
            }
#endif
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether source can be switch to in auto-search scan mode
// Input Value  : ucSearchIndex --> source index
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceCheckMultiAutoSearchTarget(BYTE ucSearchIndex)
{
#if(_DUAL_DP_SUPPORT == _ON)
    // Skip Dual DP Port from multi-display auto-search
    if(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex)) == _DUAL_DP_INPUT_PORT)
    {
        return _FALSE;
    }
#endif

    if((GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _FALSE) &&
       (UserInterfaceSourceGetRegionAutoSearchStatus(GET_RGN_DISPLAY_REGION(GET_SOURCE_AUTO_TARGET()), SysSourceGetSpecificInputPort(ucSearchIndex)) == _AUTO_SEARCH_TRUE))
    {
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
        if((SysSourceGetInputPort() == _D14_INPUT_PORT) || (SysSourceGetInputPort() == _D15_INPUT_PORT))
        {
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D4_INPUT_PORT);
        }

        SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSourceSearchIndex);
#else
        if((SysSourceGetInputPort() == _D12_INPUT_PORT) || (SysSourceGetInputPort() == _D13_INPUT_PORT))
        {
            g_ucSourceSearchIndex = SysSourceConvertSearchPort(_D3_INPUT_PORT);
        }

        SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSourceSearchIndex);
#endif
#else
        SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), ucSearchIndex);
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
        {
            SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, ucSearchIndex);
            SET_RGN_SOURCE_INDEX(_REGION_INDEX_1, ucSearchIndex);
        }
#endif

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
        // If Mtp and one Region is fix on D3/D12/D13, then Auto search port will skip D3/D12/D13
        if(SysSourceMtpAutoSearchSkipExtendedPort(ucSearchIndex) == _FALSE)
#endif
        {
#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
            g_ucSourceSearchIndex = ucSearchIndex;
#endif
            return _TRUE;
        }
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Set auto search target region
// Input Value  : enumDisplayRegion --> select region
// Output Value : None
//--------------------------------------------------
void SysSourceSetMultiAutoSearchTarget(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucAutoTargetIndex = ScalerRegionGetIndex(enumDisplayRegion);

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    return;
#endif

    if((enumDisplayRegion == _DISPLAY_RGN_NONE) ||
       (ucAutoTargetIndex > GET_RGN_MAX_DISPLAY_REGION()))
    {
        // Set fixed port scan type
        SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

        // Save system data
        if(GET_SOURCE_SCAN_TYPE() != UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE))
        {
            UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, GET_SOURCE_SCAN_TYPE());
            UserCommonNVRamSaveSystemData();
        }
    }
    else
    {
        // Set auto search scan type
        SET_SOURCE_AUTO_TARGET(ucAutoTargetIndex);
        SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);

        // Save system data
        if((GET_SOURCE_AUTO_TARGET() != UserCommonNVRamGetSystemData(_AUTO_SEARCH_TARGET)) ||
           (GET_SOURCE_SCAN_TYPE() != UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE)))
        {
            UserCommonNVRamSetSystemData(_AUTO_SEARCH_TARGET, GET_SOURCE_AUTO_TARGET());
            UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, GET_SOURCE_SCAN_TYPE());
            UserCommonNVRamSaveSystemData();
        }

        // Reset search times
        SysSourceSearchTimeReset();
    }
}

#if(_DP_SUPPORT == _ON)
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Source Switch Between Dx~D9
// Input Value  : Current Input Port, Previous Inputpot
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceMultiSwitchInPxpCheck(BYTE ucCurSearchIndex, BYTE ucPreSearchIndex)
{
    if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON)
    {
        if(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucPreSearchIndex)) == _D9_INPUT_PORT)
        {
            return _TRUE;
        }

        // Pxp on case current or previous port D9 can switch port
        if(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucCurSearchIndex)) == _D9_INPUT_PORT)
        {
            return _TRUE;
        }
    }
    else
    {
        // Pxp off case previous D9 port can switch to D0~D5
        if(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucPreSearchIndex)) == _D9_INPUT_PORT)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
#endif
#endif

//--------------------------------------------------
// Description  : Set Port Status
// Input Value  : Input Port, switch status pointers
// Output Value : None
//--------------------------------------------------
void SysSourceSetPortStatus(EnumInputPort enumInputPort, StructPortSwitchedStatus *pstPortStatus)
{
    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            pstPortStatus->b1A0 = _TRUE;
            break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            pstPortStatus->b1D0 = _TRUE;
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            pstPortStatus->b1D1 = _TRUE;
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            pstPortStatus->b1D2 = _TRUE;
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            pstPortStatus->b1D3 = _TRUE;
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            pstPortStatus->b1D4 = _TRUE;
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            pstPortStatus->b1D5 = _TRUE;
            break;
#endif

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
        case _D7_INPUT_PORT:
            pstPortStatus->b1D0 = _TRUE;
            pstPortStatus->b1D1 = _TRUE;
            break;
#endif

#if(_D8_INPUT_PORT_TYPE != _D8_NO_PORT)
        case _D8_INPUT_PORT:
            pstPortStatus->b1D1 = _TRUE;
            pstPortStatus->b1D2 = _TRUE;
            break;
#endif

#if(_D9_INPUT_PORT_TYPE != _D9_NO_PORT)
        case _D9_INPUT_PORT:
            pstPortStatus->b1D9 = _TRUE;

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Source Switch Between Interfaces
// Input Value  : Current Input Port, switch status pointers
// Output Value : None
//--------------------------------------------------
void SysSourceGetInterfaceSwitchStatus(EnumInputPort enumInputPort, StructPortSwitchedStatus *pstPortStatus)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    BYTE ucSearchIndex = 0;
#endif

    for(ucRegionIndex = 0; ucRegionIndex < ucRegionCount; ucRegionIndex++)
    {
        EnumInputPort enumRegionSourceSearchPort = GET_RGN_INPUT_PORT(ucRegionIndex);

        // Get Multi P Every Port type
        if(enumInputPort != enumRegionSourceSearchPort)
        {
            SysSourceSetPortStatus(enumRegionSourceSearchPort, pstPortStatus);
        }
    }

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if(GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON)
    {
        SysSourceSetPortStatus(GET_DP_MST_RX_PXP_INPUT_PORT(), pstPortStatus);
    }
#endif
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    // For some of HP scan type, the first loop of source search for checking monitor status
    if(SysSourceHpGetMonitorStatusCheckProcessing() == _TRUE)
    {
        for(ucSearchIndex = 0; ucSearchIndex < _INPUT_PORT_VALID; ucSearchIndex++)
        {
            if(GET_SOURCE_TYPE(ucSearchIndex) != _SOURCE_NONE)
            {
                SysSourceSetPortStatus(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex)), pstPortStatus);
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Source Switch Between Interfaces
// Input Value  : Current Input Port, Target Source Type, Source Search Mode
// Output Value : None
//--------------------------------------------------
void SysSourceInterfaceSwitch(EnumInputPort enumInputPort, EnumPortType enumPortType, BYTE ucSourceSearchDelayMode)
{
    StructPortSwitchedStatus stPortStatus = {0};

    ucSourceSearchDelayMode = ucSourceSearchDelayMode;

    // Get interface switch status
    SysSourceGetInterfaceSwitchStatus(enumInputPort, &stPortStatus);

    // Switch ports by port type
    SysVgaInterfaceSwitch(enumInputPort, enumPortType, &stPortStatus);
    SysTmdsInterfaceSwitch(enumInputPort, enumPortType, &stPortStatus);
    SysDpInterfaceSwitch(enumInputPort, enumPortType, &stPortStatus);

    // GDIPHY Switch Port
    ScalerGDIPhyRxComboPhySwitch(enumInputPort);

    // Enable selected port
    ScalerSyncInterfaceProc(enumInputPort, _ENABLE);

    // Disable unselected ports
    if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        if((stPortStatus.b1D0 == _FALSE) &&
           ((enumInputPort != _D0_INPUT_PORT) && (enumInputPort != _D7_INPUT_PORT)))
        {
#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerCutProc(_D0_INPUT_PORT, GET_PORT_TYPE(_D0_INPUT_PORT_TYPE), enumInputPort, enumPortType);
#endif

            ScalerSyncInterfaceProc(_D0_INPUT_PORT, _DISABLE);
        }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        if((stPortStatus.b1D1 == _FALSE) &&
           ((enumInputPort != _D1_INPUT_PORT) && (enumInputPort != _D7_INPUT_PORT) && (enumInputPort != _D8_INPUT_PORT)))
        {
#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerCutProc(_D1_INPUT_PORT, GET_PORT_TYPE(_D1_INPUT_PORT_TYPE), enumInputPort, enumPortType);
#endif

            ScalerSyncInterfaceProc(_D1_INPUT_PORT, _DISABLE);
        }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        if((stPortStatus.b1D2 == _FALSE) &&
           (enumInputPort != _D2_INPUT_PORT) && (enumInputPort != _D8_INPUT_PORT))
        {
#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerCutProc(_D2_INPUT_PORT, GET_PORT_TYPE(_D2_INPUT_PORT_TYPE), enumInputPort, enumPortType);
#endif

            ScalerSyncInterfaceProc(_D2_INPUT_PORT, _DISABLE);
        }
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        if((stPortStatus.b1D3 == _FALSE) &&
           (enumInputPort != _D3_INPUT_PORT))
        {
#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerCutProc(_D3_INPUT_PORT, GET_PORT_TYPE(_D3_INPUT_PORT_TYPE), enumInputPort, enumPortType);
#endif

            ScalerSyncInterfaceProc(_D3_INPUT_PORT, _DISABLE);
        }
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        if((stPortStatus.b1D4 == _FALSE) &&
           (enumInputPort != _D4_INPUT_PORT))
        {
#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerCutProc(_D4_INPUT_PORT, GET_PORT_TYPE(_D4_INPUT_PORT_TYPE), enumInputPort, enumPortType);
#endif

            ScalerSyncInterfaceProc(_D4_INPUT_PORT, _DISABLE);
        }
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        if((stPortStatus.b1D5 == _FALSE) &&
           (enumInputPort != _D5_INPUT_PORT))
        {
#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerCutProc(_D5_INPUT_PORT, GET_PORT_TYPE(_D5_INPUT_PORT_TYPE), enumInputPort, enumPortType);
#endif

            ScalerSyncInterfaceProc(_D5_INPUT_PORT, _DISABLE);
        }
#endif

#if((_DP_SUPPORT == _ON) && (_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE))
        ScalerDpMacStreamRxUnusedMacPowerOffProc();
#endif
    }
}

//--------------------------------------------------
// Description  : Update measure target & perform measure process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceMeasureProc(void)
{
    EnumDBEnableStatus enumDBBackup = _DB_DISABLE;

    // Update measure target
    if(SysSourceUpdateMeasureTarget() == _TRUE)
    {
        EnumInputDataPath enumInputPath = ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(GET_SOURCE_MEASURE_TARGET_INDEX()));

        DebugMessageSystem("Measure Target", GET_SOURCE_MEASURE_TARGET_INDEX());

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        if(GET_SOURCE_MEASURE_TARGET_INDEX() == 0)
        {
            CLR_SOURCE_HP_PXP_MAIN_SOURCE_AUTO_SCAN();

            if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_PXP_FIXED_PORT)
            {
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);
            }
        }
#endif
        // Backup Double Buffer Status
        enumDBBackup = ScalerGlobalGetDBStatus(enumInputPath);

        // Set measure region index
        ScalerMeasureSetRegionIndex(GET_SOURCE_MEASURE_TARGET_INDEX());
        ScalerMeasureSetInputPath(enumInputPath);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
        // Disable Global Double Buffer
        ScalerGlobalDoubleBufferEnable(enumInputPath, _DISABLE);
#else
        // Disable Global Double Buffer
        ScalerGlobalDoubleBufferEnable(_INPUT_PATH_ALL, _DISABLE);
#endif
        // Clear timing double check flag
        CLR_RGN_TIMING_DOUBLE_CHECK(GET_SOURCE_MEASURE_TARGET_INDEX());

#if(_MULTI_DISPLAY_MAX != 0x01)
        // Check duplicate port in 2P/4P mode
        if(SysSourceDuplicateInputTiming() == _FALSE)
#endif
        {
            // Measure input timing
            SysSourceMeasureInputTiming();
        }

        // Clear display action to no signal
        if((GET_RGN_TIMING_CONFIRM(GET_SOURCE_MEASURE_TARGET_INDEX()) == _TRUE) &&
           (GET_RGN_DISPLAY_ACTION(GET_SOURCE_MEASURE_TARGET_INDEX()) == _DISPLAY_ACTION_NO_SIGNAL))
        {
            SET_RGN_DISPLAY_ACTION(GET_SOURCE_MEASURE_TARGET_INDEX(), _DISPLAY_ACTION_NO_ACTION);
        }

        if(enumDBBackup != _DB_DISABLE)
        {
#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
            // Restore Double Buffer Status
            ScalerGlobalDoubleBufferEnable(enumInputPath, _ENABLE);
#else
            // Restore Double Buffer Status
            ScalerGlobalDoubleBufferEnable(_INPUT_PATH_ALL, _ENABLE);
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Search for measure target
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceUpdateMeasureTarget(void)
{
    // Perform measure only after display initial state
    // - to allow D-domain settings to be effective
#if(_HP_SOURCE_SCAN_SUPPORT)
    if((GET_MODE_STATE() == _MODE_STATUS_DISPLAY_INITIAL) ||
       (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_PXP_SOURCE_SCAN))
#else
    if(GET_MODE_STATE() == _MODE_STATUS_DISPLAY_INITIAL)
#endif
    {
        return _FALSE;
    }

    // Check measure target validity
    if(GET_SOURCE_MEASURE_TARGET_INDEX() >= GET_RGN_MAX_DISPLAY_REGION())
    {
        // Reset measure target related events & flags
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
        CLR_RGN_TIMING_CONFIRM(GET_SOURCE_MEASURE_TARGET_INDEX());
        CLR_RGN_TIMING_DOUBLE_CHECK(GET_SOURCE_MEASURE_TARGET_INDEX());
        CLR_RGN_MEASURE_CHECKING(GET_SOURCE_MEASURE_TARGET_INDEX());

        // Reset measure target to 0
        SET_SOURCE_MEASURE_TARGET_INDEX(0);
    }

#if(_EAGLE_SIGHT_SUPPORT == _ON)
    if(GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT)
    {
        SET_SOURCE_MEASURE_TARGET_INDEX(0);
    }
#endif

#if(_MULTI_DISPLAY_MAX != 0x01)
    if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
    {
        // Skip updating measure target index when checking OOR
        if(GET_RGN_MEASURE_CHECKING(GET_SOURCE_MEASURE_TARGET_INDEX()) == _FALSE)
        {
            // Skip when current target is feasible
            if((GET_RGN_SOURCE_JUDGE(GET_SOURCE_MEASURE_TARGET_INDEX()) == _FALSE) ||
               (GET_RGN_TIMING_CONFIRM(GET_SOURCE_MEASURE_TARGET_INDEX()) == _TRUE) ||
               (GET_RGN_DISPLAY_STATE(GET_SOURCE_MEASURE_TARGET_INDEX()) == _DISPLAY_STATE_OOR))
            {
                BYTE ucRegionIndex = 0x00;
                BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

                // Search for new measure target
                do
                {
                    if((GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE) &&
                       (GET_RGN_TIMING_CONFIRM(ucRegionIndex) == _FALSE) &&
                       (GET_RGN_DISPLAY_STATE(ucRegionIndex) != _DISPLAY_STATE_OOR))
                    {
                        SET_SOURCE_MEASURE_TARGET_INDEX(ucRegionIndex);

                        DebugMessageSystem("New measure target", GET_SOURCE_MEASURE_TARGET_INDEX());
                        return _TRUE;
                    }
                }
                while(++ucRegionIndex < ucRegionCount);

                // Search failed; Reset measure target to 0
                SET_SOURCE_MEASURE_TARGET_INDEX(0);
                return _FALSE;
            }
        }
    }
#endif // End of #if(_MULTI_DISPLAY_MAX != 0x01)

    return ((GET_RGN_SOURCE_JUDGE(GET_SOURCE_MEASURE_TARGET_INDEX()) == _TRUE) &&
            (GET_RGN_TIMING_CONFIRM(GET_SOURCE_MEASURE_TARGET_INDEX()) == _FALSE) &&
            (GET_RGN_DISPLAY_STATE(GET_SOURCE_MEASURE_TARGET_INDEX()) != _DISPLAY_STATE_OOR));
}

//--------------------------------------------------
// Description  : Measure input timing
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceMeasureInputTiming(void)
{
    // Measure Current Input Timing to gather all required timing Info
    EnumMeasureResult enumResult =
        ScalerMeasureInputInfo(GET_RGN_SOURCE_TYPE(GET_SOURCE_MEASURE_TARGET_INDEX()),
                               GET_RGN_INPUT_PORT(GET_SOURCE_MEASURE_TARGET_INDEX()));

    switch(enumResult)
    {
        case _MEASURE_RESULT_PASS:
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);

            if(GET_INPUT_TIMING_H_POLARITY() == _HIGH)
            {
                DebugMessageSystem("Input Timing HP is Positive", 0);
            }
            else
            {
                DebugMessageSystem("Input Timing HP is Negative", 0);
            }
            if(GET_INPUT_TIMING_V_POLARITY() == _HIGH)
            {
                DebugMessageSystem("Input Timing VP is Positive", 0);
            }
            else
            {
                DebugMessageSystem("Input Timing VP is Negative", 0);
            }
            DebugMessageSystem("Input Timing InterLace", GET_INPUT_TIMING_INTERLACE_FLG());
            DebugMessageSystem("Input Timing HFreq", GET_INPUT_TIMING_HFREQ());
            DebugMessageSystem("Input Timing HTotal", GET_INPUT_TIMING_HTOTAL());
            DebugMessageSystem("Input Timing HStart", GET_INPUT_TIMING_HSTART());
            DebugMessageSystem("Input Timing HWidth", GET_INPUT_TIMING_HWIDTH());
            DebugMessageSystem("Input Timing HSW", GET_INPUT_TIMING_HSYNCWIDTH());
            DebugMessageSystem("Input Timing VFreq", GET_INPUT_TIMING_VFREQ());
            DebugMessageSystem("Input Timing VTotal", GET_INPUT_TIMING_VTOTAL());
            DebugMessageSystem("Input Timing VStart", GET_INPUT_TIMING_VSTART());
            DebugMessageSystem("Input Timing VHeight", GET_INPUT_TIMING_VHEIGHT());
            DebugMessageSystem("Input Timing VSW", GET_INPUT_TIMING_VSYNCWIDTH());

            // Set timing confirmed flag
            SET_RGN_TIMING_CONFIRM(GET_SOURCE_MEASURE_TARGET_INDEX());
            SET_RGN_TIMING_DOUBLE_CHECK(GET_SOURCE_MEASURE_TARGET_INDEX());

            // Perform I-domain OOR check here
            if(UserCommonModeCheckNoSupport(GET_RGN_DISPLAY_REGION(GET_SOURCE_MEASURE_TARGET_INDEX())) == _TRUE)
            {
                // Set measure checking flag
                SET_RGN_MEASURE_CHECKING(GET_SOURCE_MEASURE_TARGET_INDEX());

                // Wait until really into source OOR state
                ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
            }
            break;

        case _MEASURE_RESULT_FAIL:
            DebugMessageSystem("Digital Measure Fail", GET_SOURCE_MEASURE_TARGET_INDEX());

            // If Timing can't be confirmed for 1 sec, clear source judged flag
            ScalerTimerActiveTimerEvent(SEC(1), _SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
            break;

        case _MEASURE_RESULT_OOR:
            DebugMessageSystem("Digital Measure OOR", GET_SOURCE_MEASURE_TARGET_INDEX());
            SET_RGN_DISPLAY_ACTION(GET_SOURCE_MEASURE_TARGET_INDEX(), _DISPLAY_ACTION_OOR);
            break;

        default:
            break;
    }
}

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Duplicate input timing
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceDuplicateInputTiming(void)
{
    BYTE ucDuplicateIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();
    EnumInputPort enumTargetPort = GET_RGN_INPUT_PORT(GET_SOURCE_MEASURE_TARGET_INDEX());
    EnumSourceType enumTargetSourceType = GET_RGN_SOURCE_TYPE(GET_SOURCE_MEASURE_TARGET_INDEX());

    // Search duplicate port
    for(ucDuplicateIndex = 0; ucDuplicateIndex < ucRegionCount; ++ucDuplicateIndex)
    {
        if((GET_RGN_INPUT_PORT(ucDuplicateIndex) == enumTargetPort) &&
           (GET_RGN_TIMING_CONFIRM(ucDuplicateIndex) == _TRUE))
        {
            // Duplicate timing info
            EnumMeasureResult enumResult =
                ScalerMeasureDuplicateInputInfo(ucDuplicateIndex,
                                                enumTargetSourceType,
                                                enumTargetPort);

            switch(enumResult)
            {
                case _MEASURE_RESULT_PASS:
                    SET_RGN_TIMING_CONFIRM(GET_SOURCE_MEASURE_TARGET_INDEX());
                    SET_RGN_TIMING_DOUBLE_CHECK(GET_SOURCE_MEASURE_TARGET_INDEX());

                    DebugMessageSystem("Timing info duplicated", GET_SOURCE_MEASURE_TARGET_INDEX());
                    if(GET_INPUT_TIMING_H_POLARITY() == _HIGH)
                    {
                        DebugMessageSystem("Input Timing HP is Positive", 0);
                    }
                    else
                    {
                        DebugMessageSystem("Input Timing HP is Negative", 0);
                    }
                    if(GET_INPUT_TIMING_V_POLARITY() == _HIGH)
                    {
                        DebugMessageSystem("Input Timing VP is Positive", 0);
                    }
                    else
                    {
                        DebugMessageSystem("Input Timing VP is Negative", 0);
                    }
                    DebugMessageSystem("Input Timing InterLace", GET_INPUT_TIMING_INTERLACE_FLG());
                    DebugMessageSystem("Input Timing HFreq", GET_INPUT_TIMING_HFREQ());
                    DebugMessageSystem("Input Timing HTotal", GET_INPUT_TIMING_HTOTAL());
                    DebugMessageSystem("Input Timing HStart", GET_INPUT_TIMING_HSTART());
                    DebugMessageSystem("Input Timing HWidth", GET_INPUT_TIMING_HWIDTH());
                    DebugMessageSystem("Input Timing HSW", GET_INPUT_TIMING_HSYNCWIDTH());
                    DebugMessageSystem("Input Timing VFreq", GET_INPUT_TIMING_VFREQ());
                    DebugMessageSystem("Input Timing VTotal", GET_INPUT_TIMING_VTOTAL());
                    DebugMessageSystem("Input Timing VStart", GET_INPUT_TIMING_VSTART());
                    DebugMessageSystem("Input Timing VHeight", GET_INPUT_TIMING_VHEIGHT());
                    DebugMessageSystem("Input Timing VSW", GET_INPUT_TIMING_VSYNCWIDTH());

                    // Perform I-domain OOR check here
                    if(UserCommonModeCheckNoSupport(GET_RGN_DISPLAY_REGION(GET_SOURCE_MEASURE_TARGET_INDEX())) == _TRUE)
                    {
                        SET_RGN_DISPLAY_ACTION(GET_SOURCE_MEASURE_TARGET_INDEX(), _DISPLAY_ACTION_OOR);
                    }
                    break;

                case _MEASURE_RESULT_FAIL:
                    DebugMessageSystem("Duplicate Fail", GET_SOURCE_MEASURE_TARGET_INDEX());
                    break;

                case _MEASURE_RESULT_OOR:
                    DebugMessageSystem("Duplicate OOR", GET_SOURCE_MEASURE_TARGET_INDEX());
                    SET_RGN_DISPLAY_ACTION(GET_SOURCE_MEASURE_TARGET_INDEX(), _DISPLAY_ACTION_OOR);
                    break;

                default:
                    break;
            }
            return _TRUE;
        }
    }
    return _FALSE;
}
#endif // End of #if(_MULTI_DISPLAY_MAX != 0x01)

//--------------------------------------------------
// Description  : Check All Source Judge Status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceCheckAllSourceJudged(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    for(; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _FALSE)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Any Source Judge Status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceCheckAnySourceJudged(void)
{
    BYTE ucRegionIndex = 0;
    BYTE ucRegionCount = GET_RGN_MAX_DISPLAY_REGION();

    for(; ucRegionIndex < ucRegionCount; ++ucRegionIndex)
    {
        if(GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE)
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Source Enter Power Saving Check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceEnterPowerSavingCheck(void)
{
#if(_HDMI_FRL_SUPPORT == _ON)
    EnumInputPort enumInputPort = GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex));

    if(ScalerHdmiFrlMacRxEnterPowerSavingCheck(enumInputPort) == _FALSE)
    {
        return _FALSE;
    }
#endif

    return _TRUE;
}

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
//--------------------------------------------------
// Description  : Eizo Power Saving Support Selection
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void SysSourceEizoSetPowerSavingSupport(bit bOn)
{
    if(bOn == _ON)
    {
        SET_SOURCE_EIZO_PS_SUPPORT();
    }
    else
    {
        CLR_SOURCE_EIZO_PS_SUPPORT();
    }
}

//--------------------------------------------------
// Description  : Report SysSource Search Finish Flag
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceGetSourceSwitchFinish(void)
{
    return GET_SOURCE_SWITCH_FINISH();
}

//--------------------------------------------------
// Description  : Reactive event time
// Input Value  : None
// Output Value : EIZO event time
//--------------------------------------------------
WORD SysSourceEizoGetReactiveEventTime(void)
{
    if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
    {
        EnumInputPort enumInputPort = GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex));
        EnumPortType enumPortType = GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSourceSearchIndex));

        return SysSourceGetDefaultSearchTime(enumInputPort, enumPortType);
    }

    return ScalerTimerGetEventRemainTime(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
}

//--------------------------------------------------
// Description  : Reactive Total Search time
// Input Value  : usTime    --> Unit in 1ms, range in 0.01 ~ 61 sec
// Output Value : None
//--------------------------------------------------
void SysSourceEizoReactiveTotalSearchTime(EnumPortType enumPortType)
{
    WORD usTime = 0;
    WORD usSearchTime = 0;

    switch(enumPortType)
    {
#if(_VGA_SUPPORT == _ON)
        case _PORT_VGA:
            usTime = SEC(2);
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
            usTime = SEC(4.5);
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
            usTime = SEC(4);
            break;
#endif

        default:
            break;
    }

    switch(enumPortType)
    {
#if(_VGA_SUPPORT == _ON)
        case _PORT_VGA:
            usSearchTime = g_usSourceDefaultSearchTimeVga;
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _PORT_HDMI:
            usSearchTime = g_usSourceDefaultSearchTimeHdmi;
            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:
            usSearchTime = g_usSourceDefaultSearchTimeDp;
            break;
#endif

        default:
            break;
    }

    if(usTime <= usSearchTime)
    {
        ScalerTimerReactiveTimerEvent(GET_SOURCE_EIZO_EVENT_TIME(), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }
    else
    {
        ScalerTimerReactiveTimerEvent(usTime, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

        PDATA_WORD(0) = ScalerTimerGetEventRemainTime(_SYSTEM_TIMER_EVENT_SOURCE_EIZO_SEARCH_FINISH);

        ScalerTimerReactiveTimerEvent((PDATA_WORD(0) + (usTime - GET_SOURCE_EIZO_EVENT_TIME())), _SYSTEM_TIMER_EVENT_SOURCE_EIZO_SEARCH_FINISH);
    }
}
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HP Source Judge Flag
// Input Value  : None
// Output Value : True --> HP Judge
//--------------------------------------------------
bit SysSourceHpGetSourceJudge(void)
{
    return (bit)GET_SOURCE_HP_SOURCE_JUDGE();
}

//--------------------------------------------------
// Description  : Get Target Source Type
// Input Value  : Target SearchIndex
// Output Value : Target Souce Type
//--------------------------------------------------
BYTE SysSourceHpGetTargetSourceType(BYTE ucSearchIndex)
{
    return GET_SOURCE_TYPE(ucSearchIndex);
}

//--------------------------------------------------
// Description  : Get Target Source Search Times
// Input Value  : None
// Output Value : Target Source Search Times
//--------------------------------------------------
BYTE SysSourceHpGetTargetSearchTimes(void)
{
    return GET_SOURCE_HP_TARGET_SEARCH_TIMES();
}

//--------------------------------------------------
// Description  : Get Switch Port Nosignal Status
// Input Value  : None
// Output Value : True --> Show Monitor Status
//--------------------------------------------------
bit SysSourceHpGetTargetPortNoSignal(void)
{
    return GET_SOURCE_HP_TARGET_NO_SIGNAL();
}

//--------------------------------------------------
// Description  : Get HP Monitor Status Check Is Processing or Not
// Input Value  : None
// Output Value : True --> HP Monitor Status Check Is Processing
//--------------------------------------------------
bit SysSourceHpGetMonitorStatusCheckProcessing(void)
{
    if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL) &&
       ((GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_SOURCE_SCAN) ||
        (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN) ||
        (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT) ||
        (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_SCAN_NEXT_PORT)))
    {
        if((SysSourceCheckTargetTimes(1) == _FALSE) && (GET_SOURCE_HP_SOURCE_JUDGE() == _FALSE))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Hp Get Pxp Main Source Auto Scan
// Input Value  : None
// Output Value : boolean
//--------------------------------------------------
bit SysSourceHpGetPxpMainSourceAutoScan(void)
{
    return GET_SOURCE_HP_PXP_MAIN_SOURCE_AUTO_SCAN();
}

//--------------------------------------------------
// Description  : Hp Set Pxp Main Source Auto Scan
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceHpSetPxpMainSourceAutoScan(void)
{
    SET_SOURCE_HP_PXP_MAIN_SOURCE_AUTO_SCAN();
}

//--------------------------------------------------
// Description  : Hp Clear Pxp Main Source Auto Scan
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceHpClearPxpMainSourceAutoScan(void)
{
    CLR_SOURCE_HP_PXP_MAIN_SOURCE_AUTO_SCAN();
}
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Judge whether to do source bg detect flow
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit SysSourceBgJudgeDoDetect(void)
{
    // Don't do BG detect under the following conditions
    if(GET_DISPLAY_MODE() != _DISPLAY_MODE_1P)
    {
        return _FALSE;
    }

#if(_SOURCE_BACKGROUND_DETECT_ENABLE_CONTROL_BY_USER == _ON)
    if(GET_SOURCE_BG_DETECT_ENABLE() == _FALSE)
    {
        return _FALSE;
    }

#else
    if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT)
    {
        return _FALSE;
    }
#endif

    if(GET_SOURCE_BG_JUDGE(g_ucSourceBgDetectIndex) == _TRUE)
    {
        return _FALSE;
    }

    switch(GET_SOURCE_BG_SCAN_TYPE())
    {
        case _SOURCE_BG_SWITCH_FIXED_PORT:

            if(g_ucSourceBgDetectIndex != g_ucSourceSearchIndex)
            {
                return _TRUE;
            }

            return _FALSE;

        case _SOURCE_BG_SWITCH_AUTO_WITHOUT_GROUP:

            if(g_ucSourceBgDetectIndex < g_ucSourceSearchIndex)
            {
                return _TRUE;
            }

            return _FALSE;

        default:

            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Port Switch Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceBg1pSwitchPort(void)
{
    BYTE ucCount = 0;
    BYTE ucBackupSearchIndex = g_ucSourceBgDetectIndex;

    switch(GET_SOURCE_BG_SCAN_TYPE())
    {
        // Fixed Port Initial by SysSourceBgSetInputPort()
        case _SOURCE_BG_SWITCH_FIXED_PORT:

            break;

        case _SOURCE_BG_SWITCH_AUTO_WITHOUT_GROUP:

            do
            {
                g_ucSourceBgDetectIndex = (g_ucSourceBgDetectIndex + 1) % _INPUT_PORT_VALID;

                if(g_ucSourceBgDetectIndex < g_ucSourceSearchIndex)
                {
                    break;
                }

                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            if(g_ucSourceBgDetectIndex != ucBackupSearchIndex)
            {
                SET_SOURCE_SEARCH_TIME_INITIAL();

                SET_SOURCE_SEARCH_PORT_INITIAL();

                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }
            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Judge if the port with source will be chosen
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceBgJudge(void)
{
    if(GET_SOURCE_TYPE(g_ucSourceBgDetectIndex) != _SOURCE_NONE)
    {
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

        // Choose Current Source to proceed
        SET_SOURCE_BG_JUDGE(g_ucSourceBgDetectIndex, _TRUE);

        CLR_SOURCE_DETECTING();

        DebugMessageSystem("Background source judge !! Port =", GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceBgDetectIndex)));
    }
    else if(GET_SOURCE_PREDETECT(g_ucSourceBgDetectIndex) == _TRUE)
    {
        if(GET_SOURCE_SEARCH_TIME_REACTIVE() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

            SET_SOURCE_DETECTING();

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_REACTIVE_MODE);

            CLR_SOURCE_SEARCH_TIME_REACTIVE();
        }
    }
}

//--------------------------------------------------
// Description  : Get Input Port
// Input Value  : None
// Output Value : ucInputPort --> Input Port
//--------------------------------------------------
BYTE SysSourceBgGetInputPort(void)
{
    return SysSourceGetSpecificInputPort(g_ucSourceBgDetectIndex);
}

//--------------------------------------------------
// Description  : Get Background Detection Judge or Not
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit SysSourceBgGetJudge(void)
{
    return GET_SOURCE_BG_JUDGE(g_ucSourceBgDetectIndex);
}

//--------------------------------------------------
// Description  : Reset Background Detection Index
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceBgDetectReset(void)
{
    SysSourceBgInfoReset();

    SET_SOURCE_SEARCH_TIME_REACTIVE();

    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

    if(GET_SOURCE_BG_SCAN_TYPE() == _SOURCE_BG_SWITCH_AUTO_WITHOUT_GROUP)
    {
        g_ucSourceBgDetectIndex = 0;
    }
}

//--------------------------------------------------
// Description  : Background Source Information Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceBgInfoReset(void)
{
    // Clear Source Flags
    SET_SOURCE_DETECTING();
    SET_SOURCE_SEARCH_PORT_INITIAL();
    SET_SOURCE_SEARCH_TIME_INITIAL();

    CLR_SOURCE_BG_JUDGE(g_ucSourceBgDetectIndex);
}

//--------------------------------------------------
// Description  : Set Source BG detect input port and clear previous judge
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void SysSourceBgSetInputPort(EnumInputPort enumInputPort)
{
    SysSourceBgDetectReset();

    g_ucSourceBgDetectIndex = SysSourceConvertSearchPort(enumInputPort);

    DebugMessageSystem("set BG detect port", enumInputPort);
}

//--------------------------------------------------
// Description  : Set Source Bg Scan Type for User
// Input Value  : Preferred Scan Type
// Output Value : None
//--------------------------------------------------
void SysSourceBgSetScanType(BYTE ucScanBgType)
{
    SET_SOURCE_BG_SCAN_TYPE(ucScanBgType);
}

//--------------------------------------------------
// Description  : Get Source Bg Scan Type for User
// Input Value  : None
// Output Value : Current Scan Type
//--------------------------------------------------
BYTE SysSourceBgGetScanType(void)
{
    return GET_SOURCE_BG_SCAN_TYPE();
}

//--------------------------------------------------
// Description  : Get Source Bg Stable Check Enable Status
// Input Value  : None
// Output Value : Current Bg Stable Check Enable Status
//--------------------------------------------------
bit SysSourceBgGetStableCheckEnable(void)
{
    return GET_SOURCE_BG_STABLE_CHECK_EN();
}

//--------------------------------------------------
// Description  : Set Source Bg Stable Check Enable Status
// Input Value  : bit _TRUE or _FALSE
// Output Value : void
//--------------------------------------------------
void SysSourceBgSetStableCheckEnable(void)
{
    SET_SOURCE_BG_STABLE_CHECK_EN();
}

//--------------------------------------------------
// Description  : Clr Source Bg Stable Check Enable Status
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void SysSourceBgClrStableCheckEnable(void)
{
    CLR_SOURCE_BG_STABLE_CHECK_EN();
}

//--------------------------------------------------
// Description  : Judge Whether DO Background Source Stable Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysSourceBgJudgeDoStableCheck(void)
{
    if((GET_SOURCE_BG_STABLE_CHECK_EN() == _TRUE) &&
       (GET_SOURCE_BG_JUDGE(g_ucSourceBgDetectIndex) == _TRUE))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Background Source Stable Check Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysSourceBgStableCheck(void)
{
    EnumSourceType enumSourceType = GET_SOURCE_TYPE(g_ucSourceBgDetectIndex);
    EnumInputPort enumInputPort = GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSourceBgDetectIndex));

    switch(enumSourceType)
    {
#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_HDMI:

            return ScalerTmdsMacRxStableDetect(enumInputPort, enumSourceType);

#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            return ScalerDpMacStreamRxStableDetect(enumInputPort, enumSourceType);
#endif

        default:

            break;
    }

    return _FALSE;
}

#if(_SOURCE_BACKGROUND_DETECT_ENABLE_CONTROL_BY_USER == _ON)
//--------------------------------------------------
// Description  : Enable Source Bg Detect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceBgDetectEnable(void)
{
    SET_SOURCE_BG_DETECT_ENABLE();
}

//--------------------------------------------------
// Description  : Disable Source Bg Detect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceBgDetectDisable(void)
{
    CLR_SOURCE_BG_DETECT_ENABLE();
}
#endif
#endif
