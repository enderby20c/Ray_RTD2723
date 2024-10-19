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
// ID Code      : ScalerDpHdcp14Rx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcp14Rx/ScalerDpHdcp14Rx.h"

#if(_DP_HDCP14_RX_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDCP 1.4 Unplug Reset Proc
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14RxUnplugResetProc(EnumInputPort enumInputPort)
{
    ScalerDpHdcp14RxResetProc(enumInputPort);
    ScalerDpHdcp14RxResetDpcd(enumInputPort, _DP_RX_HDCP_UNPLUG_RESET);
}

//--------------------------------------------------
// Description  : HDCP 1.4 Reset Proc
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14RxResetProc(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP14_RX0_SUPPORT == _ON)
        case _RX0:

            ScalerDpHdcp14Rx0ResetProc();

            break;
#endif

#if(_DP_HDCP14_RX1_SUPPORT == _ON)
        case _RX1:

            ScalerDpHdcp14Rx1ResetProc();

            break;
#endif

#if(_DP_HDCP14_RX2_SUPPORT == _ON)
        case _RX2:

            ScalerDpHdcp14Rx2ResetProc();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 1.4 Reset Source Write Dpcd
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14RxResetDpcd(EnumInputPort enumInputPort, EnumDPRxHDCPResetDpcdField enumDPRxHDCPResetDpcdField)
{
    switch(enumDPRxHDCPResetDpcdField)
    {
        case _DP_RX_HDCP_REAUTH:

            ScalerDpAuxRxSetManualMode(enumInputPort);

            // Clear Aksv
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x07, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x08, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x09, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x0A, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x0B, 0x00);

            ScalerDpAuxRxSetAutoMode(enumInputPort);

            break;

        case _DP_RX_HDCP_UNPLUG_RESET:

            // Clear Aksv
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x07, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x08, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x09, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x0A, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x0B, 0x00);

            // Clear An
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x0C, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x0D, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x0E, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x0F, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x10, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x11, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x12, 0x00);
            ScalerDpAuxRxSetDpcdWriteValue(enumInputPort, 0x06, 0x80, 0x13, 0x00);

            break;

        default:

            break;
    }
}

#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set HDCP Repeater Proc Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14RxSetRepeaterProcTimeout(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:

            SET_DP_HDCP14_RX0_AUTH_REPEATER_PROC_TIMEOUT();

            break;
#endif

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:

            SET_DP_HDCP14_RX1_AUTH_REPEATER_PROC_TIMEOUT();

            break;
#endif

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:

            SET_DP_HDCP14_RX2_AUTH_REPEATER_PROC_TIMEOUT();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set HDCP Read IRQ Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14RxSetReadIrqTimeout(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:

            SET_DP_HDCP14_RX0_AUTH_READ_IRQ_TIMEOUT();

            break;
#endif

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:

            SET_DP_HDCP14_RX1_AUTH_READ_IRQ_TIMEOUT();

            break;
#endif

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:

            SET_DP_HDCP14_RX2_AUTH_READ_IRQ_TIMEOUT();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Change HDCP Auth State
// Input Value  : Target HDCP Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14RxChangeAuthState(EnumInputPort enumInputPort, EnumDPRxHDCPAuthState enumHDCPAuthState)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:

            ScalerDpHdcp14Rx0ChangeAuthState(enumHDCPAuthState);

            break;
#endif

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:

            ScalerDpHdcp14Rx1ChangeAuthState(enumHDCPAuthState);

            break;
#endif

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:

            ScalerDpHdcp14Rx2ChangeAuthState(enumHDCPAuthState);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear Hdcp14 Auth Aksv Written
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14RxClrAuthAksvWritten(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:

            CLR_DP_HDCP14_RX0_AUTH_AKSV_WRITTEN();

            break;
#endif

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:

            CLR_DP_HDCP14_RX1_AUTH_AKSV_WRITTEN();

            break;
#endif

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:

            CLR_DP_HDCP14_RX2_AUTH_AKSV_WRITTEN();

            break;
#endif
        default:

            break;
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Cancel DP HDCP CPIRQ
// Input Value  : INPUT PORT
// Output Value : NONE
//--------------------------------------------------
void ScalerDpHdcp14RxCancelHdcpCpIRQ(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_CPIRQ_EVENT);
            break;
#endif

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_CPIRQ_EVENT);
            break;
#endif

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_HDCP_CPIRQ_EVENT);
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Cancel DP HDCP CPIRQ
// Input Value  : INPUT PORT
// Output Value : NONE
//--------------------------------------------------
void ScalerDpHdcp14RxCancelHdcpRepeaterProcTimeout(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_REPEATER_PROC_TIMEOUT);
            break;
#endif

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_REPEATER_PROC_TIMEOUT);
            break;
#endif

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_HDCP_REPEATER_PROC_TIMEOUT);
            break;
#endif
        default:

            break;
    }
}


//--------------------------------------------------
// Description  : Cancel DP HDCP CPIRQ
// Input Value  : INPUT PORT
// Output Value : NONE
//--------------------------------------------------
void ScalerDpHdcp14RxCancelHdcpReadIRQTimeout(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_READ_IRQ_TIMEOUT);
            break;
#endif

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_READ_IRQ_TIMEOUT);
            break;
#endif

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX2_HDCP_READ_IRQ_TIMEOUT);
            break;
#endif
        default:

            break;
    }
}
#endif
#endif
#endif
