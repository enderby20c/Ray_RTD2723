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
// ID Code      : ScalerDpHdcp2Rx_EXINT0.c No.0000
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
void ScalerDpHdcp2RxCancelTimerEvent_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_HDCP2_RX0_SUPPORT == _ON)

        case _RX0:

            ScalerDpHdcp2Rx0CancelTimerEvent_EXINT0();

            break;

#endif

#if(_DP_HDCP2_RX1_SUPPORT == _ON)

        case _RX1:

            ScalerDpHdcp2Rx1CancelTimerEvent_EXINT0();

            break;

#endif

#if(_DP_HDCP2_RX2_SUPPORT == _ON)

        case _RX2:

            ScalerDpHdcp2Rx2CancelTimerEvent_EXINT0();

            break;

#endif

        default:

            break;
    }
}
#endif // End of #if(_DP_HDCP2_RX_SUPPORT == _ON)
