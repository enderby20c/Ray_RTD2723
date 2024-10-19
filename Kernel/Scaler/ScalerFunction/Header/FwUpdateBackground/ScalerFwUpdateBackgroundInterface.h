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
// ID Code      : ScalerFwUpdateBackgroundInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_FW_UPDATE_BACKGROUND_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Affective IP Define
//--------------------------------------------------
typedef enum
{
    _AFFECTED_IP_DPTX = 0x00,
    _AFFECTED_IP_DPRX,
    _AFFECTED_IP_HDCP,
    _AFFECTED_IP_TYPEC,
    _AFFECTED_IP_MCCS,
} EnumBackgroundFwUpdateAffectedIp;

//--------------------------------------------------
// Enumerations of Busy or Idle Status
//--------------------------------------------------
typedef enum
{
    _STATUS_IDLE = 0x00,
    _STATUS_BUSY
} EnumBusyStatusInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumBusyStatusInfo ScalerFwUpdateBackgroundGetSystemStatus(void);
extern void ScalerFwUpdateBackgroundSetBusyStatus(EnumBackgroundFwUpdateAffectedIp enumIp, EnumBusyStatusInfo enumStatus, WORD usTime);
extern void ScalerFwUpdateBackgroundClrMCCSBusyStatus(void);
#endif
