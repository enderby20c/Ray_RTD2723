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
// ID Code      : ScalerDpHdcp2Rx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcp2Rx/ScalerDpHdcp2Rx.h"

#if(_DP_HDCP2_RX_SUPPORT == _ON)
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
// Description  : Cancel Timer Event for HDCP2
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp2RxCancelTimerEvent(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)

        case _RX0:

            ScalerDpHdcp2Rx0CancelTimerEvent();

            break;

#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)

        case _RX1:

            ScalerDpHdcp2Rx1CancelTimerEvent();

            break;

#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)

        case _RX2:

            ScalerDpHdcp2Rx2CancelTimerEvent();

            break;

#endif

        default:

            break;
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set HDCP Repeater Proc Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumDpHdcp2AESType ScalerDpHdcp2RxGetStxType(BYTE ucStreamId)
{
    switch(GET_DP_RX_HDCP2_UPSTREAM_PORT())
    {
        case _HDCP_D0_PORT:

            return ScalerDpMacDphyRxHdcp2GetStxType(_D0_INPUT_PORT, ucStreamId);

        case _HDCP_D1_PORT:

            return ScalerDpMacDphyRxHdcp2GetStxType(_D1_INPUT_PORT, ucStreamId);

        case _HDCP_D2_PORT:

            return ScalerDpMacDphyRxHdcp2GetStxType(_D2_INPUT_PORT, ucStreamId);

        default:

            break;
    }

    return _HDCP2_TYPE_0;
}

//--------------------------------------------------
// Description  : Check DP Hdcp2 ReAuth Process
// Input Value  : enumInputPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp2RxReAuthStatusCheck(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)

        case _RX0:

            return ScalerDpHdcp2Rx0ReAuthStatusCheck();

#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)

        case _RX1:

            return ScalerDpHdcp2Rx1ReAuthStatusCheck();

#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)

        case _RX2:

            return ScalerDpHdcp2Rx2ReAuthStatusCheck();

#endif

        default:

            return _FALSE;
    }
}
#endif
#endif
