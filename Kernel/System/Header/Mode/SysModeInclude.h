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
// ID Code      : SysModeInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_MODE_STATE()                        (g_stModeInfo.b4ModeState)
#define SET_MODE_STATE(x)                       (g_stModeInfo.b4ModeState = (x))

#define GET_MODE_STATE_CHANGE_OTHERS()          (bit)(g_stModeInfo.b1ModeStateChangedForOthers)
#define SET_MODE_STATE_CHANGE_OTHERS()          (g_stModeInfo.b1ModeStateChangedForOthers = _TRUE)
#define CLR_MODE_STATE_CHANGE_OTHERS()          (g_stModeInfo.b1ModeStateChangedForOthers = _FALSE)

#define GET_MODE_STATE_CHANGE_SOURCE()          (bit)(g_stModeInfo.b1ModeStateChangedForSource)
#define SET_MODE_STATE_CHANGE_SOURCE()          (g_stModeInfo.b1ModeStateChangedForSource = _TRUE)
#define CLR_MODE_STATE_CHANGE_SOURCE()          (g_stModeInfo.b1ModeStateChangedForSource = _FALSE)

#define GET_MODE_STATE_CHANGE_MODE()            (bit)(g_stModeInfo.b1ModeStateChangedForMode)
#define SET_MODE_STATE_CHANGE_MODE()            (g_stModeInfo.b1ModeStateChangedForMode = _TRUE)
#define CLR_MODE_STATE_CHANGE_MODE()            (g_stModeInfo.b1ModeStateChangedForMode = _FALSE)

#define GET_MODE_STATE_CHANGE_OSD()             (bit)(g_stModeInfo.b1ModeStateChangedForOsd)
#define SET_MODE_STATE_CHANGE_OSD()             (g_stModeInfo.b1ModeStateChangedForOsd = _TRUE)
#define CLR_MODE_STATE_CHANGE_OSD()             (g_stModeInfo.b1ModeStateChangedForOsd = _FALSE)


#define GET_MODE_RESET_TARGET()                 (g_stModeInfo.b4ModeResetFlag)
#define SET_MODE_RESET_TARGET(x)                (g_stModeInfo.b4ModeResetFlag = (x))

#define GET_MODE_ACTIVE_READY()                 (bit)(g_stModeInfo.b1ActiveReady)
#define SET_MODE_ACTIVE_READY()                 (g_stModeInfo.b1ActiveReady = _TRUE)
#define CLR_MODE_ACTIVE_READY()                 (g_stModeInfo.b1ActiveReady = _FALSE)

#define GET_MODE_DISPLAY_TARGET_STATE()         (g_pstRegionInfo[GET_MODE_DISPLAY_TARGET_INDEX()].stDisplayStatusInfo.enumDisplayState)

#ifndef _DISPLAY_SETTING_TEST
#define _DISPLAY_SETTING_TEST                   _OFF
#endif

#if(_DISPLAY_SETTING_TEST == _ON)
#define DISPLAY_SETTING_TEST_INIT()             {\
                                                    SysModeTestingInit();\
                                                }
#define DISPLAY_SETTING_TEST_UPDATE()           {\
                                                    if(SysModeTestUpdateSetting() == _FALSE)\
                                                    {\
                                                        return _FALSE;\
                                                    }\
                                                }
#else
#define DISPLAY_SETTING_TEST_INIT()             {}
#define DISPLAY_SETTING_TEST_UPDATE()           {}
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    EnumModeStatus b4ModeState : 4;
    EnumModeAction b4ModeResetFlag : 4;
    BYTE b1ModeStateChangedForOthers : 1;
    BYTE b1ModeStateChangedForOsd : 1;
    BYTE b1ModeStateChangedForSource : 1;
    BYTE b1ModeStateChangedForMode : 1;
    BYTE b1ActiveReady : 1;
} StructModeInfoType;

#if(_IS_MAIN_PROCESS_CPU == _FALSE)
typedef struct
{
    BYTE ucModeState;
    BYTE ucModeResetFlag;
    BYTE ucDisplayMode;
    BYTE ucModeStateChangedForMode;
} StructMode32InfoType;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructModeInfoType g_stModeInfo;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysModeHandler(void);
extern void SysModeResetState(BYTE ucResetTarget);
extern bit SysModeSearchDisplayTarget(void);

#if(_DISPLAY_SETTING_TEST == _ON)
extern void SysModeTestingInit(void);
extern bit SysModeTestUpdateSetting(void);
#endif

#if(_2P_FRAME_SYNC_SUPPORT == _ON)
extern bit SysModeResetToDisplayInitial(void);
#endif

