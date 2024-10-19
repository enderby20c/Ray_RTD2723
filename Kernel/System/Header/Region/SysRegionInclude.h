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
// ID Code      : SysRegionInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_RGN_TIMING_CONFIRM(x)               ((g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent & _DISPLAY_EVENT_TIMING_CONFIRMED) == _DISPLAY_EVENT_TIMING_CONFIRMED)
#define SET_RGN_TIMING_CONFIRM(x)               (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent |= _DISPLAY_EVENT_TIMING_CONFIRMED)
#define CLR_RGN_TIMING_CONFIRM(x)               (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent &= ~_DISPLAY_EVENT_TIMING_CONFIRMED)

#define GET_RGN_TIMING_DOUBLE_CHECK(x)          ((g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent & _DISPLAY_EVENT_TIMING_DOUBLE_CHECK) == _DISPLAY_EVENT_TIMING_DOUBLE_CHECK)
#define SET_RGN_TIMING_DOUBLE_CHECK(x)          (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent |= _DISPLAY_EVENT_TIMING_DOUBLE_CHECK)
#define CLR_RGN_TIMING_DOUBLE_CHECK(x)          (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent &= ~_DISPLAY_EVENT_TIMING_DOUBLE_CHECK)

#define GET_RGN_MEASURE_CHECKING(x)             ((g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent & _DISPLAY_EVENT_MEASURE_CHECKING) == _DISPLAY_EVENT_MEASURE_CHECKING)
#define SET_RGN_MEASURE_CHECKING(x)             (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent |= _DISPLAY_EVENT_MEASURE_CHECKING)
#define CLR_RGN_MEASURE_CHECKING(x)             (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent &= ~_DISPLAY_EVENT_MEASURE_CHECKING)

#define GET_RGN_FIRST_ACTIVE(x)                 ((g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent & _DISPLAY_EVENT_FIRST_ACTIVE) == _DISPLAY_EVENT_FIRST_ACTIVE)
#define SET_RGN_FIRST_ACTIVE(x)                 (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent |= _DISPLAY_EVENT_FIRST_ACTIVE)
#define CLR_RGN_FIRST_ACTIVE(x)                 (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent &= ~_DISPLAY_EVENT_FIRST_ACTIVE)

#define GET_RGN_DISPLAY_STATE_CHANGE_SYS(x)     ((g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent & _DISPLAY_EVENT_STATE_CHANGE_SYS) == _DISPLAY_EVENT_STATE_CHANGE_SYS)
#define SET_RGN_DISPLAY_STATE_CHANGE_SYS(x)     (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent |= _DISPLAY_EVENT_STATE_CHANGE_SYS)
#define CLR_RGN_DISPLAY_STATE_CHANGE_SYS(x)     (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent &= ~_DISPLAY_EVENT_STATE_CHANGE_SYS)

#define GET_RGN_DISPLAY_STATE_CHANGE_USR(x)     ((g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent & _DISPLAY_EVENT_STATE_CHANGE_USR) == _DISPLAY_EVENT_STATE_CHANGE_USR)
#define SET_RGN_DISPLAY_STATE_CHANGE_USR(x)     (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent |= _DISPLAY_EVENT_STATE_CHANGE_USR)
#define CLR_RGN_DISPLAY_STATE_CHANGE_USR(x)     (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent &= ~_DISPLAY_EVENT_STATE_CHANGE_USR)

#define GET_RGN_DISPLAY_EVENT(x)                (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent)
#define SET_RGN_DISPLAY_EVENT(x, event)         (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent = (event))
#define CLR_RGN_DISPLAY_EVENT(x)                (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayEvent = (EnumDisplayEvent)0x00)

#define GET_RGN_DISPLAY_STATE(x)                (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayState)
#define SET_RGN_DISPLAY_STATE(x, state)         {\
                                                    if((state) != g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayState)\
                                                    {\
                                                        g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayState = (state);\
                                                        SET_RGN_DISPLAY_STATE_CHANGE_SYS(x);\
                                                        SET_RGN_DISPLAY_STATE_CHANGE_USR(x);\
                                                    }\
                                                }

#define CLR_RGN_DISPLAY_STATE(x)                {SET_RGN_DISPLAY_STATE((x), _DISPLAY_STATE_NONE)}

#define GET_RGN_DISPLAY_ACTION(x)               (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayAction)
#define SET_RGN_DISPLAY_ACTION(x, act)          (g_pstRegionInfo[x].stDisplayStatusInfo.enumDisplayAction = (act))
#define CLR_RGN_DISPLAY_ACTION(x)               (SET_RGN_DISPLAY_ACTION((x), _DISPLAY_ACTION_NO_ACTION))

#define CLR_RGN_DISPLAY_INFO(x)                 (memset(&g_pstRegionInfo[x].stDisplayStatusInfo, 0x00, sizeof(StructDisplayStatusInfoType)))
#define CLR_RGN_DISPLAY_INFO_ALL()              {\
                                                    BYTE ucRegionSourceIndex = 0x00;\
                                                    while(ucRegionSourceIndex < _MULTI_DISPLAY_MAX)\
                                                    {\
                                                        CLR_RGN_DISPLAY_INFO(ucRegionSourceIndex++);\
                                                    }\
                                                }

#define GET_RGN_SOURCE_INDEX(x)                 (g_pstRegionInfo[x].ucSourceIndex)
#define SET_RGN_SOURCE_INDEX(x, index)          (g_pstRegionInfo[x].ucSourceIndex = (index))

#define GET_RGN_INPUT_PORT(x)                   (SysSourceGetSpecificInputPort(GET_RGN_SOURCE_INDEX(x)))

#define GET_RGN_SOURCE_TYPE(x)                  (GET_SOURCE_TYPE(GET_RGN_SOURCE_INDEX(x)))
#define CLR_RGN_SOURCE_TYPE(x)                  (SET_SOURCE_TYPE(GET_RGN_SOURCE_INDEX(x), _SOURCE_NONE))
#define CLR_RGN_SOURCE_TYPE_ALL()               {\
                                                    BYTE ucRegionSourceIndex = 0x00;\
                                                    while(ucRegionSourceIndex < _MULTI_DISPLAY_MAX)\
                                                    {\
                                                        CLR_RGN_SOURCE_TYPE(ucRegionSourceIndex++);\
                                                    }\
                                                }

#define GET_RGN_SOURCE_JUDGE(x)                 (GET_SOURCE_JUDGE(GET_RGN_SOURCE_INDEX(x)))
#define CLR_RGN_SOURCE_JUDGE(x)                 (CLR_SOURCE_JUDGE(GET_RGN_SOURCE_INDEX(x)))
#define CLR_RGN_SOURCE_JUDGE_ALL()              {\
                                                    BYTE ucRegionSourceIndex = 0x00;\
                                                    while(ucRegionSourceIndex < _MULTI_DISPLAY_MAX)\
                                                    {\
                                                        CLR_RGN_SOURCE_JUDGE(ucRegionSourceIndex++);\
                                                    }\
                                                }

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Display State Action
//--------------------------------------------------
typedef enum
{
    _DISPLAY_ACTION_NO_ACTION = 0x00,

    _DISPLAY_ACTION_RESET_TO_NONE,
    _DISPLAY_ACTION_NO_SIGNAL,
    _DISPLAY_ACTION_OOR,
    _DISPLAY_ACTION_DISPLAY_READY,
    _DISPLAY_ACTION_ACTIVE,
} EnumDisplayAction;

//--------------------------------------------------
// Structure of Display Status
//--------------------------------------------------
typedef struct
{
    //! For display event: timing confirm, timing check, display state change, etc.
    EnumDisplayEvent enumDisplayEvent;

    //! For display state: active, OOR or no signal
    EnumDisplayState enumDisplayState;

    //! For display action: to active, OOR or no signal
    EnumDisplayAction enumDisplayAction;
} StructDisplayStatusInfoType;

//--------------------------------------------------
// Structure of Region Info
//--------------------------------------------------
typedef struct
{
    //! related source search index
    BYTE ucSourceIndex;

    //! related display state
    StructDisplayStatusInfoType stDisplayStatusInfo;
} StructRegionInfoType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructRegionInfoType g_pstRegionInfo[_MULTI_DISPLAY_MAX];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysRegionInitial(void);
extern bit SysRegionCheckSystemDisplayStateChange(void);
extern void SysRegionSetDisplayStateBySearchIndex(BYTE ucSearchIndex, EnumDisplayState enumDisplayState);

