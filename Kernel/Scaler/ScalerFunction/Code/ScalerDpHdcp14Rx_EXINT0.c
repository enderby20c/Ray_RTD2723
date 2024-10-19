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
// ID Code      : ScalerDpHdcp14Rx_EXINT0.c No.0000
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
#if(_DP_HDCP14_RX_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 1.4 Reset Proc
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcp14RxGetRepeaterCaps_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping(enumInputPort))
    {
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:

            return GET_DP_HDCP14_RX0_REPEATER_SUPPORT();
#endif

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:

            return GET_DP_HDCP14_RX1_REPEATER_SUPPORT();
#endif

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:

            return GET_DP_HDCP14_RX2_REPEATER_SUPPORT();
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14RxResetKsvFifoToFirst_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:
            ScalerDpHdcp14Rx0ResetKsvFifoToFirst_EXINT0();
            break;
#endif

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:
            ScalerDpHdcp14Rx1ResetKsvFifoToFirst_EXINT0();
            break;
#endif

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:
            ScalerDpHdcp14Rx2ResetKsvFifoToFirst_EXINT0();
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14RxSetKsvFifo_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:
            ScalerDpHdcp14Rx0SetKsvFifo_EXINT0();
            break;
#endif

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:
            ScalerDpHdcp14Rx1SetKsvFifo_EXINT0();
            break;
#endif

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:
            ScalerDpHdcp14Rx2SetKsvFifo_EXINT0();
            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14RxSetAuthAksvWritten_EXINT0(EnumInputPort enumInputPort)
{
    switch(ScalerDpHdcpRxDxRxMapping_EXINT0(enumInputPort))
    {
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
        case _RX0:

            SET_DP_HDCP14_RX0_AUTH_AKSV_WRITTEN();

            break;
#endif

#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
        case _RX1:

            SET_DP_HDCP14_RX1_AUTH_AKSV_WRITTEN();

            break;
#endif

#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
        case _RX2:

            SET_DP_HDCP14_RX2_AUTH_AKSV_WRITTEN();

            break;
#endif
        default:

            break;
    }
}
#endif
#endif
