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
// ID Code      : SysPowerInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Power action
//--------------------------------------------------
#define GET_TARGET_POWER_STATUS()               (g_stPowerInfo.b4PowerAction)
#define SET_TARGET_POWER_STATUS(x)              (g_stPowerInfo.b4PowerAction = (x))

//--------------------------------------------------
// Power status
//--------------------------------------------------
#define GET_POWER_STATUS()                      (g_stPowerInfo.b4PowerStatus)
#define SET_POWER_STATUS(x)                     (g_stPowerInfo.b4PowerStatus = (x))

//--------------------------------------------------
// Power status Switch to Fake Saving
//--------------------------------------------------
#define GET_POWER_SWITCH_TO_FAKE_SAVING()       ((bit)(g_stPowerInfo.b1PowerSwitchtoFakeSaving))
#define SET_POWER_SWITCH_TO_FAKE_SAVING()       (g_stPowerInfo.b1PowerSwitchtoFakeSaving = 1)
#define CLR_POWER_SWITCH_TO_FAKE_SAVING()       (g_stPowerInfo.b1PowerSwitchtoFakeSaving = 0)

//--------------------------------------------------
// Power status Switch to Off
//--------------------------------------------------
#define GET_POWER_SWITCH_TO_FAKE_OFF()          ((bit)(g_stPowerInfo.b1PowerSwitchtoFakeOff))
#define SET_POWER_SWITCH_TO_FAKE_OFF()          (g_stPowerInfo.b1PowerSwitchtoFakeOff = 1)
#define CLR_POWER_SWITCH_TO_FAKE_OFF()          (g_stPowerInfo.b1PowerSwitchtoFakeOff = 0)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    EnumPowerStatus b4PowerAction : 4;
    EnumPowerStatus b4PowerStatus : 4;
    BYTE b1IsolationAFlag : 1;
    BYTE b1IsolationBFlag : 1;
    BYTE b1IsolationCFlag : 1;
    BYTE b1IsolationDFlag : 1;
    BYTE b1IsolationEFlag : 1;
    BYTE b1PowerSwitchtoFakeSaving : 1;
    BYTE b1PowerSwitchtoFakeOff : 1;
} StructPowerInfoType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructPowerInfoType g_stPowerInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void SysPowerInitial(void);
extern void SysPowerHandler(void);

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
extern void SysPowerLoadDPTxHDCPKey(void);
#endif
#endif
