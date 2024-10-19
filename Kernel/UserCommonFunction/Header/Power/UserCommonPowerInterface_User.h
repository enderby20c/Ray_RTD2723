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
// ID Code      : UserCommonPowerInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Panel Power Status
//--------------------------------------------------
#define _PANEL_POWER_OFF_STATE                          0
#define _WAITING_FOR_BACKLIGHT                          1
#define _READY_FOR_BACKLIGHT                            2
#define _BACKLIGHT_ON_ALREADY                           3
#define _PANEL_BACKLIGHT_OFF                            4
#define _WAITING_FOR_PANEL_OFF                          5

//--------------------------------------------------
// MACRO of Panel Power Sequence
//--------------------------------------------------
#define GET_PANELPOWERSTATUS()                          (g_stPowerPanelInfo.b3Status)
#define SET_PANELPOWERSTATUS(x)                         (g_stPowerPanelInfo.b3Status = (x))

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
#define GET_PANELPOWERACTION()                          (g_stPowerPanelInfo.b2Action)
#define SET_PANELPOWERACTION(x)                         (g_stPowerPanelInfo.b2Action = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Panel Power Action
//--------------------------------------------------
typedef enum
{
    _PANEL_ON,
    _PANEL_OFF,
    _BACKLIGHT_ON,
    _BACKLIGHT_OFF,
} EnumPanelPowerSeq;

//--------------------------------------------------
// Structure of Panel Power Action
//--------------------------------------------------
typedef struct
{
    BYTE b3Status : 3;

#if(_PANEL_POW_SEQ_T6_TIMER_EVENT_MODE == _ON)
    BYTE b2Action : 2;
#endif

} StructPanelPowerInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructPanelPowerInfo g_stPowerPanelInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit UserCommonPowerCheckFakeOff(void);
extern void UserCommonPowerPanelAction(EnumPanelPowerSeq enumEvent);

