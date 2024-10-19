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
// ID Code      : ScalerFwUpdateBackground.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_BACKGROUND_FW_UPDATE__

#include "ScalerFunctionInclude.h"
#include "FwUpdateBackground/ScalerFwUpdateBackground.h"

#if(_FW_UPDATE_BACKGROUND_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSysBusyStatusInfo g_stFwUpdateBackgroundSysStatusInfo =
{
#if(_DP_TX_SUPPORT == _ON)
    _STATUS_IDLE,
#endif
#if(_DP_SUPPORT == _ON)
    _STATUS_IDLE,
#endif
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    _STATUS_IDLE,
#endif
#if(_DIGITAL_PORT_SUPPORT == _ON)
    _STATUS_IDLE,
#endif
    _STATUS_IDLE
};


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Systerm Busy Status
// Input Value  : enumInputPort, enumInSync
// Output Value : None
//--------------------------------------------------
EnumBusyStatusInfo ScalerFwUpdateBackgroundGetSystemStatus(void)
{
#if(_DP_TX_SUPPORT == _ON)
    if(g_stFwUpdateBackgroundSysStatusInfo.b1DpTxBusyStatus == _STATUS_BUSY)
    {
        return _STATUS_BUSY;
    }
#endif

#if(_DP_SUPPORT == _ON)
    if(g_stFwUpdateBackgroundSysStatusInfo.b1DpRxBusyStatus == _STATUS_BUSY)
    {
        return _STATUS_BUSY;
    }
#endif

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    if(g_stFwUpdateBackgroundSysStatusInfo.b1TypeCBusyStatus == _STATUS_BUSY)
    {
        return _STATUS_BUSY;
    }
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
    if(g_stFwUpdateBackgroundSysStatusInfo.b1MCCSBusyStatus == _STATUS_BUSY)
    {
        return _STATUS_BUSY;
    }
#endif

    if(g_stFwUpdateBackgroundSysStatusInfo.b1HdcpBusyStatus == _STATUS_BUSY)
    {
        return _STATUS_BUSY;
    }
    return _STATUS_IDLE;
}

//--------------------------------------------------
// Description  : For affective Ip to Set Busy Status
// Input Value  : enumIp, enumStatus, ultimeout
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateBackgroundSetBusyStatus(EnumBackgroundFwUpdateAffectedIp enumIp, EnumBusyStatusInfo enumStatus, WORD usTime)
{
    switch(enumIp)
    {
#if(_DP_TX_SUPPORT == _ON)
        case _AFFECTED_IP_DPTX:
            g_stFwUpdateBackgroundSysStatusInfo.b1DpTxBusyStatus = enumStatus;
            if(enumStatus == _STATUS_BUSY)
            {
                ScalerTimerReactiveTimerEvent(usTime, _SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_DPTX_BUSY);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_DPTX_BUSY);
            }
            break;
#endif
#if(_DP_SUPPORT == _ON)
        case _AFFECTED_IP_DPRX:
            g_stFwUpdateBackgroundSysStatusInfo.b1DpRxBusyStatus = enumStatus;
            if(enumStatus == _STATUS_BUSY)
            {
                ScalerTimerReactiveTimerEvent(usTime, _SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_DPRX_BUSY);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_DPRX_BUSY);
            }
            break;
#endif

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _AFFECTED_IP_TYPEC:
            g_stFwUpdateBackgroundSysStatusInfo.b1TypeCBusyStatus = enumStatus;
            if(enumStatus == _STATUS_BUSY)
            {
                ScalerTimerReactiveTimerEvent(usTime, _SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_TYPEC_BUSY);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_TYPEC_BUSY);
            }
            break;
#endif
#if(_DIGITAL_PORT_SUPPORT == _ON)
        case _AFFECTED_IP_MCCS:
            g_stFwUpdateBackgroundSysStatusInfo.b1MCCSBusyStatus = enumStatus;
            if(enumStatus == _STATUS_BUSY)
            {
                ScalerTimerReactiveTimerEvent(usTime, _SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_MCCS_BUSY);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_MCCS_BUSY);
            }
            break;
#endif
        case _AFFECTED_IP_HDCP:
            g_stFwUpdateBackgroundSysStatusInfo.b1HdcpBusyStatus = enumStatus;
            if(enumStatus == _STATUS_BUSY)
            {
                ScalerTimerReactiveTimerEvent(usTime, _SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_HDCP_BUSY);
            }
            else
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_BACKGROUND_FW_UPDATE_HDCP_BUSY);
            }
            break;
        default:
            break;
    }
}
#endif
