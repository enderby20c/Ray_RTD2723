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
// ID Code      : ScalerPower.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_POWER_H__
#define __SCALER_POWER_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Power Cut Group
//--------------------------------------------------
#define _POWER_CUT_ON_GROUP_DPMAC               0
#define _POWER_CUT_ON_GROUP_VCCK_ON             1
#define _POWER_CUT_ON_GROUP_VCCK_OFF            2
#define _POWER_CUT_ON_GROUP_PHY                 3
#define _POWER_CUT_ON_GROUP_TOPOFF              4

//--------------------------------------------------
// Clock Control status in Fake Saving
//--------------------------------------------------
#define GET_POWER_FAKE_SAVING_CLOCK_CONTROL()   ((bit)(g_stPowerClockControl.b1PowerFakeSavingClkControl))
#define SET_POWER_FAKE_SAVING_CLOCK_CONTROL()   (g_stPowerClockControl.b1PowerFakeSavingClkControl = 1)
#define CLR_POWER_FAKE_SAVING_CLOCK_CONTROL()   (g_stPowerClockControl.b1PowerFakeSavingClkControl = 0)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Power Domain PS/PD Mode
//--------------------------------------------------
typedef enum
{
    _POWER_DOMAIN_PSPD_MODE_ACTION_NORMAL = 0x00,
    _POWER_DOMAIN_PSPD_MODE_KEEP_POWER_ON,
    _POWER_DOMAIN_PSPD_MODE_USER_CONTROL,
    _POWER_DOMAIN_PSPD_MODE_BY_FUNCTION,
} EnumPowerPsPdMode;

//--------------------------------------------------
// Power Domain Support Condition
//--------------------------------------------------
typedef enum
{
    _POWER_DOMAIN_PROJECT_SUPPORT_DISABLE = 0,
    _POWER_DOMAIN_PROJECT_SUPPORT_ENABLE = 1,
    _POWER_DOMAIN_PROJECT_SUPPORT_BY_FUNCTION = 2,
} EnumPowerDomainSupport;

//--------------------------------------------------
// Power Domain Related Structure
//--------------------------------------------------
typedef struct
{
    EnumPowerGroup enumPowerGroup;
    EnumPowerPsPdMode b2PsPdModeOperation : 2;
    EnumPowerDomainSupport b2PowerDomainSupport : 2;
} StructPowerCutGroup;

//--------------------------------------------------
// Power Domain Grouping Structure
//--------------------------------------------------
typedef struct
{
    StructPowerCutGroup *pstPowerCutGroup;
    BYTE ucMaxSize;
} StructPowerFlow;

//--------------------------------------------------
// Power Fake Saving PLL Control Structure
//--------------------------------------------------
typedef struct
{
    BYTE b1PowerFakeSavingClkControl : 1;
} StructPowerClockControl;

//--------------------------------------------------
// Clock Gating Related Structure
//--------------------------------------------------
typedef struct
{
    EnumPowerClockGatingGroup enumPowerClockGatingGroup;
    EnumPowerPsPdMode b2PsPdModeOperation : 2;
    EnumPowerDomainSupport b2PowerDomainSupport : 2;
} StructPowerClockGatingGroup;

//--------------------------------------------------
// Clock Gating Grouping Structure
//--------------------------------------------------
typedef struct
{
    StructPowerClockGatingGroup *pstPowerClockGatingGroup;
    BYTE ucMaxSize;
} StructClockGatingFlow;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerPowerDomainEnableStatus(void);
extern EnumPowerDomainSupport ScalerPowerGetPowerDomainSupport(EnumPowerGroup enumPowerGroup);
extern EnumPowerPsPdMode ScalerPowerGetPowerDomainPsPdMode(EnumPowerGroup enumPowerGroup);
extern void ScalerPowerGroupRecoverData(EnumPowerRecoverGroup enumPowerRecoverGroup);
extern void ScalerPowerGroupDefaultStateAlign(void);
extern void ScalerPowerGroupPowerACOnSetting(void);
extern BYTE ScalerPowerSubGroupGetControlReady(EnumPowerGroup enumPowerGroup, EnumPowerCut enumPowerCut);
extern void ScalerPowerDomainEnableDelay(EnumPowerOnDelay enumPowerOnDelay);
#if(_HW_IMD_POWER_CUT_INDEPENDENT_SUPPORT == _ON)
extern void ScalerPowerIDomainInitialSetting(EnumDisplayMode enumDisplayMode);
extern void ScalerPowerMDomainInitialSetting(EnumDisplayMode enumDisplayMode);
extern void ScalerPowerDDomainBeforeBlendingInitialSetting(EnumDisplayMode enumDisplayMode);
extern void ScalerPowerDDomainAfterBlendingInitialSetting(EnumDisplayMode enumDisplayMode);
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
extern bit ScalerPowerCutSwitchCheck(EnumPowerGroup enumPowerGroup, EnumPowerCut enumPowerCut);
#endif

extern EnumPowerDomainSupport ScalerPowerGetPowerDomainClockGatingSupport(EnumPowerClockGatingGroup enumPowerClockGatingGroup);
extern EnumPowerPsPdMode ScalerPowerGetPowerDomainClockGatingPsPdMode(EnumPowerClockGatingGroup enumPowerClockGatingGroup);
extern void ScalerPowerGroupClockGating(EnumPowerClockGatingGroup enumPowerClockGatingGroup, EnumPowerClockGating enumPowerClockGating);
extern EnumPowerClockGating ScalerPowerGroupGetClockGatingStatus(EnumPowerClockGatingGroup enumPowerClockGatingGroup);
extern void ScalerPowerGroupClockGatingACOnSetting(void);
extern BYTE ScalerPowerGroupGetClockGatingControlReady(EnumPowerClockGatingGroup enumPowerClockGatingGroup, EnumPowerClockGating enumPowerClockGating);

#endif // End of #ifndef __SCALER_POWER_H__
