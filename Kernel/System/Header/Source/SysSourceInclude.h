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
// ID Code      : SysSourceInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Source Search Delay Mode
//--------------------------------------------------
#define _SOURCE_SEARCH_POLLING_MODE             0
#define _SOURCE_SEARCH_DELAY_DEFAULT_MODE       1
#define _SOURCE_SEARCH_DELAY_REACTIVE_MODE      2
#define _SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE    3

#define GET_SOURCE_SEARCH_TIME_INITIAL()        ((bit)(g_stSourceInputInfo.b1SearchTimeInitial))
#define SET_SOURCE_SEARCH_TIME_INITIAL()        (g_stSourceInputInfo.b1SearchTimeInitial = 1)
#define CLR_SOURCE_SEARCH_TIME_INITIAL()        (g_stSourceInputInfo.b1SearchTimeInitial = 0)

#define GET_SOURCE_SEARCH_PORT_INITIAL()        ((bit)(g_stSourceInputInfo.b1SearchPortInitial))
#define SET_SOURCE_SEARCH_PORT_INITIAL()        (g_stSourceInputInfo.b1SearchPortInitial = 1)
#define CLR_SOURCE_SEARCH_PORT_INITIAL()        (g_stSourceInputInfo.b1SearchPortInitial = 0)

#define GET_SOURCE_DETECTING()                  ((bit)(g_stSourceInputInfo.b1Detecting))
#define SET_SOURCE_DETECTING()                  (g_stSourceInputInfo.b1Detecting = 1)
#define CLR_SOURCE_DETECTING()                  (g_stSourceInputInfo.b1Detecting = 0)

#define GET_SOURCE_SCAN_TYPE()                  (g_stSourceInputInfo.b4SourceSwitchType)
#define SET_SOURCE_SCAN_TYPE(x)                 (g_stSourceInputInfo.b4SourceSwitchType = (x))

#define GET_SOURCE_AUTO_TARGET()                (g_stSourceInputInfo.b2AutoSearchTarget % _MULTI_DISPLAY_MAX)
#define SET_SOURCE_AUTO_TARGET(x)               (g_stSourceInputInfo.b2AutoSearchTarget = (x))

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
#define GET_SOURCE_BG_SCAN_TYPE()               (g_stSourceInputInfo.b1SourceBgSwitchType)
#define SET_SOURCE_BG_SCAN_TYPE(x)              (g_stSourceInputInfo.b1SourceBgSwitchType = (x))

#define GET_SOURCE_BG_STABLE_CHECK_EN()         (g_stSourceInputInfo.b1SourceBgStableCheckEn)
#define SET_SOURCE_BG_STABLE_CHECK_EN()         (g_stSourceInputInfo.b1SourceBgStableCheckEn = 1)
#define CLR_SOURCE_BG_STABLE_CHECK_EN()         (g_stSourceInputInfo.b1SourceBgStableCheckEn = 0)

#if(_SOURCE_BACKGROUND_DETECT_ENABLE_CONTROL_BY_USER == _ON)
#define GET_SOURCE_BG_DETECT_ENABLE()           (g_stSourceInputInfo.b1SourceBgDetectEn)
#define SET_SOURCE_BG_DETECT_ENABLE()           (g_stSourceInputInfo.b1SourceBgDetectEn = 1)
#define CLR_SOURCE_BG_DETECT_ENABLE()           (g_stSourceInputInfo.b1SourceBgDetectEn = 0)
#endif
#endif

#define GET_SOURCE_SWITCH_FINISH()              (g_stSourceInputInfo.b1SourceSwitchCount)
#define SET_SOURCE_SWITCH_FINISH()              (g_stSourceInputInfo.b1SourceSwitchCount = 1)
#define CLR_SOURCE_SWITCH_FINISH()              (g_stSourceInputInfo.b1SourceSwitchCount = 0)

#define GET_SOURCE_SEARCH_TIME_REACTIVE()       (g_stSourceInputInfo.b1SourceSearchTimeReactivate)
#define SET_SOURCE_SEARCH_TIME_REACTIVE()       (g_stSourceInputInfo.b1SourceSearchTimeReactivate = 1)
#define CLR_SOURCE_SEARCH_TIME_REACTIVE()       (g_stSourceInputInfo.b1SourceSearchTimeReactivate = 0)

#define GET_SOURCE_SEARCH_CHECK_NVRAM_PORT()    (g_stSourceInputInfo.b1SourceSearchCheckNVRamPort)
#define SET_SOURCE_SEARCH_CHECK_NVRAM_PORT()    (g_stSourceInputInfo.b1SourceSearchCheckNVRamPort = 1)
#define CLR_SOURCE_SEARCH_CHECK_NVRAM_PORT()    (g_stSourceInputInfo.b1SourceSearchCheckNVRamPort = 0)

#define GET_SOURCE_SEARCH_DELAY_MODE()          (g_stSourceInputInfo.b2SourceSearchDelayMode)
#define SET_SOURCE_SEARCH_DELAY_MODE(x)         (g_stSourceInputInfo.b2SourceSearchDelayMode = (x))

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
#define GET_SOURCE_EIZO_PS_SUPPORT()            (g_stSourceInputInfo.b1SourceEizoPSSupport)
#define SET_SOURCE_EIZO_PS_SUPPORT()            (g_stSourceInputInfo.b1SourceEizoPSSupport = 1)
#define CLR_SOURCE_EIZO_PS_SUPPORT()            (g_stSourceInputInfo.b1SourceEizoPSSupport = 0)

#define GET_SOURCE_EIZO_INFO_RESET()            (g_stSourceInputInfo.b1SourceEizoInfoReset)
#define SET_SOURCE_EIZO_INFO_RESET()            (g_stSourceInputInfo.b1SourceEizoInfoReset = 1)
#define CLR_SOURCE_EIZO_INFO_RESET()            (g_stSourceInputInfo.b1SourceEizoInfoReset = 0)

#define GET_SOURCE_EIZO_EVENT_TIME()            (g_stSourceInputInfo.usSourceEizoEventTime)
#define SET_SOURCE_EIZO_EVENT_TIME(x)           (g_stSourceInputInfo.usSourceEizoEventTime = (x))
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
#define GET_SOURCE_HP_SOURCE_JUDGE()            (g_stSourceInputInfo.b1SourceHpSourceJudge)
#define SET_SOURCE_HP_SOURCE_JUDGE()            (g_stSourceInputInfo.b1SourceHpSourceJudge = 1)
#define CLR_SOURCE_HP_SOURCE_JUDGE()            (g_stSourceInputInfo.b1SourceHpSourceJudge = 0)

#define GET_SOURCE_HP_TIMING_CHANGE()           (g_stSourceInputInfo.b1SourceHpTimingChange)
#define SET_SOURCE_HP_TIMING_CHANGE()           (g_stSourceInputInfo.b1SourceHpTimingChange = 1)
#define CLR_SOURCE_HP_TIMING_CHANGE()           (g_stSourceInputInfo.b1SourceHpTimingChange = 0)

#define GET_SOURCE_HP_TARGET_SEARCH_TIMES()     (g_stSourceInputInfo.b2SourceHpTargetSearchTimes)
#define SET_SOURCE_HP_TARGET_SEARCH_TIMES(x)    (g_stSourceInputInfo.b2SourceHpTargetSearchTimes = (x))

#define GET_SOURCE_HP_PORT_SWITCH_TARGET()      (g_stSourceInputInfo.b3SourceHpPortSwitchTarget)
#define SET_SOURCE_HP_PORT_SWITCH_TARGET(x)     (g_stSourceInputInfo.b3SourceHpPortSwitchTarget = (x))

#define GET_SOURCE_HP_FROM_TIMING_CHANGE()      (g_stSourceInputInfo.b1SourceHpFromTimingChange)
#define SET_SOURCE_HP_FROM_TIMING_CHANGE()      (g_stSourceInputInfo.b1SourceHpFromTimingChange = 1)
#define CLR_SOURCE_HP_FROM_TIMING_CHANGE()      (g_stSourceInputInfo.b1SourceHpFromTimingChange = 0)

#define GET_SOURCE_HP_TARGET_NO_SIGNAL()        (g_stSourceInputInfo.b1SourceHpTargetNoSignal)
#define SET_SOURCE_HP_TARGET_NO_SIGNAL()        (g_stSourceInputInfo.b1SourceHpTargetNoSignal = 1)
#define CLR_SOURCE_HP_TARGET_NO_SIGNAL()        (g_stSourceInputInfo.b1SourceHpTargetNoSignal = 0)

#define GET_SOURCE_HP_PXP_MAIN_SOURCE_AUTO_SCAN()\
                                                (g_stSourceInputInfo.b1SourceHpPxpMainSourceAutoScan)
#define SET_SOURCE_HP_PXP_MAIN_SOURCE_AUTO_SCAN()\
                                                (g_stSourceInputInfo.b1SourceHpPxpMainSourceAutoScan = 1)
#define CLR_SOURCE_HP_PXP_MAIN_SOURCE_AUTO_SCAN()\
                                                (g_stSourceInputInfo.b1SourceHpPxpMainSourceAutoScan = 0)

#define GET_SOURCE_HP_DETECTING()               (g_stSourceInputInfo.b1SourceHpDetecting)
#define SET_SOURCE_HP_DETECTING()               (g_stSourceInputInfo.b1SourceHpDetecting = 1)
#define CLR_SOURCE_HP_DETECTING()               (g_stSourceInputInfo.b1SourceHpDetecting = 0)
#endif

#define GET_SOURCE_TYPE(x)                      (g_pstSourceInfo[x].b3SourceType)
#define SET_SOURCE_TYPE(x, y)                   (g_pstSourceInfo[x].b3SourceType = (y))

#define GET_SOURCE_SEARCH_TIMES(x)              ((g_pstSourceInfo[x].b2SearchTimes))
#define INCREASE_SOURCE_SEARCH_TIMES(x)         (g_pstSourceInfo[x].b2SearchTimes++)
#define SET_SOURCE_SEARCH_TIMES(x, y)           (g_pstSourceInfo[x].b2SearchTimes = (y))
#define CLR_SOURCE_SEARCH_TIMES(x)              (g_pstSourceInfo[x].b2SearchTimes = 0)

#define GET_CABLE_DETECT(x)                     (g_pstSourceInfo[x].b1CableDetect)
#define SET_CABLE_DETECT(x, y)                  (g_pstSourceInfo[x].b1CableDetect = (y))

#define GET_CABLE_STATUS_CHANGE(x)              (g_pstSourceInfo[x].b1CableStatusChange)
#define SET_CABLE_STATUS_CHANGE(x, y)           (g_pstSourceInfo[x].b1CableStatusChange = (y))

#define GET_SOURCE_JUDGE(x)                     ((bit)(g_pstSourceInfo[x].b1SourceChosen))
#define SET_SOURCE_JUDGE(x, y)                  (g_pstSourceInfo[x].b1SourceChosen = (y))
#define CLR_SOURCE_JUDGE(x)                     (g_pstSourceInfo[x].b1SourceChosen = 0)

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
#define GET_SOURCE_BG_JUDGE(x)                  ((bit)(g_pstSourceBgInfo[x].b1SourceChosen))
#define SET_SOURCE_BG_JUDGE(x, y)               (g_pstSourceBgInfo[x].b1SourceChosen = (y))
#define CLR_SOURCE_BG_JUDGE(x)                  (g_pstSourceBgInfo[x].b1SourceChosen = 0)
#endif

#define GET_SOURCE_PREDETECT(x)                 ((bit)(g_pstSourceInfo[x].b1SourcePreDetect))
#define SET_SOURCE_PREDETECT(x, y)              (g_pstSourceInfo[x].b1SourcePreDetect = (y))
#define CLR_SOURCE_PREDETECT(x)                 (g_pstSourceInfo[x].b1SourcePreDetect = 0)

#define GET_SOURCE_TYPE_BACKUP()                (g_stSourceInfoBackup.b3SourceType)
#define SET_SOURCE_TYPE_BACKUP(x)               (g_stSourceInfoBackup.b3SourceType = (x))

#define GET_SOURCE_SEARCH_TIMES_BACKUP()        ((g_stSourceInfoBackup.b2SearchTimes))
#define SET_SOURCE_SEARCH_TIMES_BACKUP(x)       (g_stSourceInfoBackup.b2SearchTimes = (x))

#define GET_CABLE_DETECT_BACKUP()               (g_stSourceInfoBackup.b1CableDetect)
#define SET_CABLE_DETECT_BACKUP(x)              (g_stSourceInfoBackup.b1CableDetect = (x))

#define GET_CABLE_STATUS_CHANGE_BACKUP()        (g_stSourceInfoBackup.b1CableStatusChange)
#define SET_CABLE_STATUS_CHANGE_BACKUP(x)       (g_stSourceInfoBackup.b1CableStatusChange = (x))

#define GET_SOURCE_JUDGE_BACKUP()               ((bit)(g_stSourceInfoBackup.b1SourceChosen))
#define SET_SOURCE_JUDGE_BACKUP(x)              (g_stSourceInfoBackup.b1SourceChosen = (x))
#define CLR_SOURCE_JUDGE_BACKUP()               (g_stSourceInfoBackup.b1SourceChosen = 0)

#define GET_SOURCE_PREDETECT_BACKUP()           ((bit)(g_stSourceInfoBackup.b1SourcePreDetect))
#define SET_SOURCE_PREDETECT_BACKUP(x)          (g_stSourceInfoBackup.b1SourcePreDetect = (x))
#define CLR_SOURCE_PREDETECT_BACKUP()           (g_stSourceInfoBackup.b1SourcePreDetect = 0)

#define GET_SOURCE_ASUS_START_AUTO()            (g_stSourceInputInfo.b1SourceAsusStartAuto)
#define SET_SOURCE_ASUS_START_AUTO()            (g_stSourceInputInfo.b1SourceAsusStartAuto = 1)
#define CLR_SOURCE_ASUS_START_AUTO()            (g_stSourceInputInfo.b1SourceAsusStartAuto = 0)

#define GET_SOURCE_ASUS_FIRST_START_AUTO()      (g_stSourceInputInfo.b1SourceAsusFirstStartAuto)
#define SET_SOURCE_ASUS_FIRST_START_AUTO()      (g_stSourceInputInfo.b1SourceAsusFirstStartAuto = 1)
#define CLR_SOURCE_ASUS_FIRST_START_AUTO()      (g_stSourceInputInfo.b1SourceAsusFirstStartAuto = 0)

#define GET_SOURCE_ASUS_START_POLLING()         (g_stSourceInputInfo.b1SourceAsusStartPolling)
#define SET_SOURCE_ASUS_START_POLLING()         (g_stSourceInputInfo.b1SourceAsusStartPolling = 1)
#define CLR_SOURCE_ASUS_START_POLLING()         (g_stSourceInputInfo.b1SourceAsusStartPolling = 0)

#define GET_SOURCE_DP_SWITCH_TIMEOUT()          (g_stSourceInputInfo.b1SourceDpSwitchTimeout)
#define SET_SOURCE_DP_SWITCH_TIMEOUT()          (g_stSourceInputInfo.b1SourceDpSwitchTimeout = 1)
#define CLR_SOURCE_DP_SWITCH_TIMEOUT()          (g_stSourceInputInfo.b1SourceDpSwitchTimeout = 0)

#define GET_SOURCE_DP_DUAL_SWITCH_TIMEOUT()     (g_stSourceInputInfo.b1SourceDpDualSwitchTimeout)
#define SET_SOURCE_DP_DUAL_SWITCH_TIMEOUT()     (g_stSourceInputInfo.b1SourceDpDualSwitchTimeout = 1)
#define CLR_SOURCE_DP_DUAL_SWITCH_TIMEOUT()     (g_stSourceInputInfo.b1SourceDpDualSwitchTimeout = 0)

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI Switch
//--------------------------------------------------
#define GET_SOURCE_HDMI_SWITCH_TIMEOUT()        (g_stSourceInputInfo.b1SourceHdmiSwitchTimeout)
#define SET_SOURCE_HDMI_SWITCH_TIMEOUT()        (g_stSourceInputInfo.b1SourceHdmiSwitchTimeout = _TRUE)
#define CLR_SOURCE_HDMI_SWITCH_TIMEOUT()        (g_stSourceInputInfo.b1SourceHdmiSwitchTimeout = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1SearchTimeInitial : 1;
    BYTE b1SearchPortInitial : 1;
    BYTE b1Detecting : 1;
    // Auto Search Target
    BYTE b2AutoSearchTarget : 2;
    BYTE b1SourceSwitchCount : 1;
    BYTE b1SourceSearchTimeReactivate : 1;
    BYTE b1SourceSearchCheckNVRamPort : 1;

    BYTE b2SourceSearchDelayMode : 2;
    // 00 : Polling
    // 01 : Defualt Search Time
    // 10 : Reactivate Search Time
    BYTE b1SourceDpSwitchTimeout : 1;
    BYTE b1SourceDpDualSwitchTimeout : 1;
    BYTE b4SourceSwitchType : 4;
    // 0000 : fixed;
    // 0001 : auto in group;
    // 0010 : Dell hotkey auto
    // 0011 : Dell hotkey fixed

    BYTE b1SourceAsusStartAuto : 1;
    BYTE b1SourceAsusFirstStartAuto : 1;
    BYTE b1SourceAsusStartPolling : 1;

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
    BYTE b1SourceHdmiSwitchTimeout : 1;
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
    BYTE b1SourceEizoPSSupport : 1;
    BYTE b1SourceEizoInfoReset : 1;
    WORD usSourceEizoEventTime;
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    BYTE b1SourceHpSourceJudge : 1;
    BYTE b1SourceHpTimingChange : 1;
    BYTE b1SourceHpFromTimingChange : 1;

    BYTE b2SourceHpTargetSearchTimes : 2;
    BYTE b3SourceHpPortSwitchTarget : 3;
    BYTE b1SourceHpTargetNoSignal : 1;
    BYTE b1SourceHpPxpMainSourceAutoScan : 1;
    BYTE b1SourceHpDetecting : 1;
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
    // 0: fixed port
    // 1: auto without group
    BYTE b1SourceBgSwitchType : 1;
    BYTE b1SourceBgStableCheckEn : 1; // 0: disable, 1: enable
    BYTE b1SourceBgDetectEn : 1; // 0: disable, 1: enable
#endif

} StructInputInfoType;

typedef struct
{
    EnumSourceType b3SourceType : 3;
    // SourceInfo bit[0:2] -- Source Type

    BYTE b2SearchTimes : 2;
    // SourceInfo bit[3:4] -- Source Search Times
    // 0~3 => Counter

    BYTE b1CableDetect : 1;
    // SourceInfo bit[5] -- Cable detect
    // 0 => No
    // 1 => Yes

    BYTE b1CableStatusChange : 1;
    BYTE b1SourceChosen : 1;
    // SourceInfo bit[7] -- Source Chosen
    // 0 => Unchosen
    // 1 => Chosen

    BYTE b1SourcePreDetect : 1;
} StructSourceInfoType;

typedef struct
{
    BYTE b1A0 : 1;
    BYTE b1D0 : 1;
    BYTE b1D1 : 1;
    BYTE b1D2 : 1;
    BYTE b1D3 : 1;
    BYTE b1D4 : 1;
    BYTE b1D5 : 1;
    BYTE b1D9 : 1;
} StructPortSwitchedStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructSourceInfoType g_pstSourceInfo[_INPUT_PORT_VALID];
extern StructSourceInfoType g_stSourceInfoBackup;
extern EnumInputPort g_penumSourceSearchPriority[10];
extern BYTE g_ucSourceSearchIndex;
extern StructInputInfoType g_stSourceInputInfo;

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
extern StructSourceInfoType g_pstSourceBgInfo[_INPUT_PORT_VALID];
extern BYTE g_ucSourceBgDetectIndex;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysSourceHandler(void);
extern void SysSourceInitial(void);
extern bit SysSourceStableCheck(BYTE ucRegionIndex);
extern void SysSourceClearDetectingEvent(void);
extern void SysSourceSwitchRegionSearchPort(EnumInputPort enumInputPort);
extern void SysSourceSearchTimeReset(void);
extern void SysSourceInfoResetToDisplayInitial(void);
extern void SysSourceResetRegion(BYTE ucRegionIndex);
extern void SysSourceCableResetProc(void);
extern void SysSourceFirstActiveProc(void);
extern void SysSourcePowerOffProc(void);
extern bit SysSourceEnterPowerSavingCheck(void);
extern bit SysSourceCheckAllSourceJudged(void);

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
extern bit SysSourceBgJudgeDoDetect(void);
#endif

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
extern void SysSourceConvertSearchIndexExtendedPortToD4Port(void);
#else
extern void SysSourceConvertSearchIndexExtendedPortToD3Port(void);
#endif
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
extern bit SysSourceHpGetMonitorStatusCheckProcessing(void);
#endif
