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
// ID Code      : SysSourceInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Source Switch Type
//--------------------------------------------------
#define _SOURCE_SWITCH_FIXED_PORT               0
#define _SOURCE_SWITCH_AUTO_IN_GROUP            1
#define _SOURCE_SWITCH_DELL_HOTKEY_AUTO         2
#define _SOURCE_SWITCH_DELL_HOTKEY_FIXED        3
#define _SOURCE_SWITCH_HP_SOURCE_SCAN           4
#define _SOURCE_SWITCH_HP_TIMING_CHANGE         5
#define _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT      6
#define _SOURCE_SWITCH_HP_SCAN_NEXT_PORT        7
#define _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN       8
#define _SOURCE_SWITCH_HP_PXP_SOURCE_SCAN       9
#define _SOURCE_SWITCH_HP_PXP_FIXED_PORT        10

//--------------------------------------------------
// Definitions of Source BG Switch Type
//--------------------------------------------------
#define _SOURCE_BG_SWITCH_FIXED_PORT            0
#define _SOURCE_BG_SWITCH_AUTO_WITHOUT_GROUP    1

//--------------------------------------------------
// Macro of Get input port and port type
//--------------------------------------------------
#define GET_INPUT_PORT(x)                       ((EnumInputPort)GET_INPUT_PORT_VALUE(x))
#define GET_PORT_TYPE(x)                        ((EnumPortType)GET_PORT_TYPE_VALUE(x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of User Cable Reset Status
//--------------------------------------------------
typedef enum
{
    _CABLE_RESET_FALSE = _FALSE,
    _CABLE_RESET_TRUE = _TRUE,
} EnumCableResetStatus;

//--------------------------------------------------
// Enumerations of User Auto Search Status
//--------------------------------------------------
typedef enum
{
    _AUTO_SEARCH_FALSE = _FALSE,
    _AUTO_SEARCH_TRUE = _TRUE,
} EnumAutoSearchStatus;

//--------------------------------------------------
// Enumerations of DP Switch Select Port
//--------------------------------------------------
typedef enum
{
    _DP_SWITCH_SELECT_D0_PORT = _D0_INPUT_PORT,
    _DP_SWITCH_SELECT_D6_PORT = _D6_INPUT_PORT,
} EnumDPSwitchPort;

//--------------------------------------------------
// Enumerations of Default DP Dual Port Status
//--------------------------------------------------
typedef enum
{
    _DP_DUAL_PORT_USE_SINGLE_PORT = _FALSE,
    _DP_DUAL_PORT_USE_DUAL_PORT = _TRUE,
} EnumDPDualPortDefaultStatus;

typedef enum
{
    _HDMI_5V_STATUS_OFF = _FALSE,
    _HDMI_5V_STATUS_ON = _TRUE,
} EnumGetHdmi5VStatus;

//--------------------------------------------------
// Enumerations of Input Source Type
//--------------------------------------------------
typedef enum
{
    _SOURCE_INPUT_TYPE_VGA = 0x00,
    _SOURCE_INPUT_TYPE_HDMI,
    _SOURCE_INPUT_TYPE_DP,
    _SOURCE_INPUT_TYPE_TYPE_C,
#if(_DP_TBT_SUPPORT == _ON)
    _SOURCE_INPUT_TYPE_TBT,
#endif
} EnumSourceInputType;

//--------------------------------------------------
// Enumerations of Input Port Priority
//--------------------------------------------------
typedef enum
{
    _INPUT_PORT_PRIORITY_0 = 0x00,
    _INPUT_PORT_PRIORITY_1,
    _INPUT_PORT_PRIORITY_2,
    _INPUT_PORT_PRIORITY_3,
    _INPUT_PORT_PRIORITY_4,
    _INPUT_PORT_PRIORITY_5,
    _INPUT_PORT_PRIORITY_6,
    _INPUT_PORT_PRIORITY_7,
    _INPUT_PORT_PRIORITY_8,
    _INPUT_PORT_PRIORITY_NONE,
}EnumSourceSearchPortPriority;

//--------------------------------------------------
// Enumerations of Input Port Search Group List
//--------------------------------------------------
typedef enum
{
    _INPUT_PORT_GROUP_0 = 0x00,
    _INPUT_PORT_GROUP_1,
    _INPUT_PORT_GROUP_2,
    _INPUT_PORT_GROUP_3,
    _INPUT_PORT_GROUP_4,
    _INPUT_PORT_GROUP_5,
    _INPUT_PORT_GROUP_6,
    _INPUT_PORT_GROUP_7,
    _INPUT_PORT_GROUP_8,
    _INPUT_PORT_GROUP_NONE,
}EnumSourceSearchGroup;

//--------------------------------------------------
// Enumerations of Source Handler ByPass Info
//--------------------------------------------------
typedef enum
{
    _SOURCE_DETECTION_NORMAL,
    _SOURCE_DETECTION_BYPASS,
} EnumSourceDetectionInfo;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of HP Pxp Sub Scan Type
//--------------------------------------------------
typedef enum
{
    _HP_PXP_SUB_FIX_PORT,
    _HP_PXP_SUB_AUTO_SCAN,
} EnumSourceHpPxpSubScanType;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumSourceType SysSourceGetSourceType(void);
extern EnumInputPort SysSourceGetInputPort(void);
extern EnumPortType SysSourceGetPortTypeFromInputPort(EnumInputPort enumInputPort);

#if(_AUDIO_SUPPORT == _ON)
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP))))
extern EnumInputPort SysSourceGetAudioPlaybackPort(void);
#endif
#endif

extern void SysSourceSwitchInputPort(EnumInputPort enumInputPort);
extern bit SysSourceCheckTargetTimes(BYTE ucTargetTimes);
extern BYTE SysSourceGetScanType(void);
extern bit SysSourceGetCableDetect(EnumInputPort enumInputPort);
extern bit SysSourceGetCableStatusChange(EnumInputPort enumInputPort);
extern bit SysSourceGetPreDetect(EnumInputPort enumInputPort);

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
extern BYTE SysSourceBgGetInputPort(void);
extern bit SysSourceBgGetJudge(void);
extern void SysSourceBgDetectReset(void);
extern void SysSourceBgSetInputPort(EnumInputPort enumInputPort);
extern void SysSourceBgSetScanType(BYTE ucScanBgType);
extern BYTE SysSourceBgGetScanType(void);
extern bit SysSourceBgGetStableCheckEnable(void);
extern void SysSourceBgSetStableCheckEnable(void);
extern void SysSourceBgClrStableCheckEnable(void);

#if(_SOURCE_BACKGROUND_DETECT_ENABLE_CONTROL_BY_USER == _ON)
extern void SysSourceBgDetectEnable(void);
extern void SysSourceBgDetectDisable(void);
#endif
#endif

extern void SysSource1PSetSearchPriority(EnumInputPort enumInputPort, EnumSourceSearchPortPriority enumSourcePriority);
extern void SysSourceSetSearchGroup(EnumInputPort enumInputPort, EnumSourceSearchGroup enumSourceGroup);
extern void SysSourceSetDefaultSearchTime(EnumSourceInputType enumInputType, WORD usDefaultSearchTime);
extern void SysSourceSetNoCableSearchTime(EnumSourceInputType enumInputType, WORD usNoCableSearchTime);
extern void SysSourceSetMultiAutoSearchTarget(EnumDisplayRegion enumDisplayRegion);
extern BYTE SysSourceConvertSearchPort(EnumInputPort enumInputPort);
extern EnumInputPort SysSourceGetSpecificInputPort(BYTE ucIndex);
#if(_DP_SUPPORT == _ON)
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
extern EnumInputPort SysSourceGetMstRxPxpInputPort(void);
#endif
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
extern void SysSourceEizoSetPowerSavingSupport(bit bOn);
extern bit SysSourceGetSourceSwitchFinish(void);
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
extern bit SysSourceHpGetSourceJudge(void);
extern BYTE SysSourceHpGetTargetSourceType(BYTE ucSearchIndex);
extern BYTE SysSourceHpGetTargetSearchTimes(void);
extern bit SysSourceHpGetTargetPortNoSignal(void);
extern bit SysSourceHpGetPxpMainSourceAutoScan(void);
extern void SysSourceHpSetPxpMainSourceAutoScan(void);
extern void SysSourceHpClearPxpMainSourceAutoScan(void);
#endif

