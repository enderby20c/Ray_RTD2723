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
// ID Code      : SysSource.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SYS_SOURCE_H__
#define __SYS_SOURCE_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of Getting Input Port Group Type
//--------------------------------------------------
#define GET_INPUTPORT_GROUP(x)              (g_penumSourceSearchGroup[g_penumSourceSearchPriority[x]])

//--------------------------------------------------
// Macro of Get Input Port Type
//--------------------------------------------------
#define GET_INPUTPORT_TYPE(x)               (tINPUT_PORT_TYPE[g_penumSourceSearchPriority[x]])

//--------------------------------------------------
// Macro of search time
//--------------------------------------------------
#define _NONE_SEARCH_TIME                   (0xFFFF)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef bit (*FUNC_PTR_PRE_DETECT)(EnumInputPort);
typedef EnumSourceType (*FUNC_PTR_SCAN_INPUT_PORT)(EnumInputPort, EnumPortType);

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE code tINPUT_PORT_TYPE[];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysSourceDetectPort(BYTE ucSearchIndex);
extern bit SysSourceKeepDetectingCheck(void);
extern void SysSourceSearchTimeInitial(BYTE ucSearchIndex);
extern void SysSourceJudge(void);
extern void SysSourceSwitchPort(void);
extern void SysSource1pSwitchPort(void);

#if(_MULTI_DISPLAY_MAX != 0x01)
extern void SysSourceMultiSwitchPort(void);

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
extern bit SysSourceMtpCheckD4ExternalHdmiAutoSwitch(void);
#else
extern bit SysSourceMtpCheckD3ExternalHdmiAutoSwitch(void);
#endif
extern BYTE SysSourceMtpAutoSearchSkipExtendedPort(BYTE ucIndex);
#endif

extern bit SysSourceMultiSwitchInGroupCheck(BYTE ucPreSearchIndex);
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
extern void SysSourceBg1pSwitchPort(void);
extern void SysSourceBgJudge(void);
extern void SysSourceBgInfoReset(void);
extern bit SysSourceBgJudgeDoStableCheck(void);
extern bit SysSourceBgStableCheck(void);
#endif

extern void SysSourceScanPortInitial(BYTE ucSearchIndex);
extern void SysSourceCableDetection(void);
extern bit SysSourceCheckCableStatusChange(BYTE ucSearchIndex, EnumInputPort enumInputPort);
extern void SysSourceUpdateCableInfo(BYTE ucSearchIndex, EnumInputPort enumInputPort);
extern void SysSourceCableStatustChangeProc(BYTE ucSearchIndex, EnumInputPort enumInputPort);

extern WORD SysSourceGetDelayReactiveSearchTime(EnumPortType enumPortType);
extern WORD SysSourceGetDefaultSearchTime(EnumInputPort enumInputPort, EnumPortType enumPortType);
extern WORD SysSourceGetNoCableSearchTime(EnumInputPort enumInputPort, EnumPortType enumPortType);

#if(_MULTI_DISPLAY_MAX != 0x01)
extern bit SysSourceCheckMultiFixedPortTarget(BYTE ucSearchIndex);
extern bit SysSourceCheckMultiAutoSearchTarget(BYTE ucSearchIndex);
#endif

#if(_HDMI_SUPPORT == _ON)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
extern void SysSourceHdmi5VDetection(void);
#endif
#endif

extern void SysSourceSetPortStatus(EnumInputPort enumInputPort, StructPortSwitchedStatus *pstPortStatus);
extern void SysSourceGetInterfaceSwitchStatus(EnumInputPort enumInputPort, StructPortSwitchedStatus *pstPortStatus);
extern void SysSourceInterfaceSwitch(EnumInputPort enumInputPort, EnumPortType enumPortType, BYTE ucSourceSearchDelayMode);
extern void SysSourceMeasureProc(void);
extern bit SysSourceUpdateMeasureTarget(void);
extern void SysSourceMeasureInputTiming(void);

#if(_MULTI_DISPLAY_MAX != 0x01)
extern bit SysSourceDuplicateInputTiming(void);
#endif

#if(_DP_SUPPORT == _ON)
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_PXP_MODE_SUPPORT == _ON))
extern bit SysSourceMultiSwitchInPxpCheck(BYTE ucCurSearchIndex, BYTE ucPreSearchIndex);
#endif
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
extern WORD SysSourceEizoGetReactiveEventTime(void);
extern void SysSourceEizoReactiveTotalSearchTime(EnumPortType enumPortType);
#endif

#if(_HDMI_EXTERNAL_SWITCH_SUPPORT == _ON)
#if(_D14_INPUT_PORT_TYPE == _D14_HDMI_PORT)
extern bit SysSource1pCheckD4ExternalHdmiAutoSwitch(void);
extern void SysSourceRecoverSearchIndexD4ToExtendedPort(void);
#else
extern bit SysSource1pCheckD3ExternalHdmiAutoSwitch(void);
extern void SysSourceRecoverSearchIndexD3ToExtendedPort(void);
#endif
extern void SysSourceHdmiExternalSwitchDefaultPort(void);
#endif

#endif // End of #ifndef __SYS_SOURCE_H__
