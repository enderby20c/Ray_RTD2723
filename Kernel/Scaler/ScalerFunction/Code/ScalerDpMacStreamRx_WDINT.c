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
// ID Code      : ScalerDpMacStreamRx_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_MAC_STREAM_RX_WDINT__

#include "ScalerFunctionInclude.h"
#include "DpMacStreamRx/ScalerDpMacStreamRx.h"

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Rx Source Type Judge Status
// Input Value  : EnumInputPort
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpMacStreamRxGetSourceTypeJudgeStatus_WDINT(EnumInputPort enumInputPort)
{
    switch(ScalerDpRxGetMacSwitch_WDINT(enumInputPort))
    {
#if(_DP_MAC_RX0_SUPPORT == _ON)
        case _DP_MAC_0:

            return GET_DP_MAC_STREAM_RX0_SOURCE_TYPE_JUDGE();
#endif

#if(_DP_MAC_RX1_SUPPORT == _ON)
        case _DP_MAC_1:

            return GET_DP_MAC_STREAM_RX1_SOURCE_TYPE_JUDGE();
#endif

#if(_DP_MAC_RX2_SUPPORT == _ON)
        case _DP_MAC_2:

            return GET_DP_MAC_STREAM_RX2_SOURCE_TYPE_JUDGE();
#endif

#if(_DP_MAC_RX3_SUPPORT == _ON)
        case _DP_MAC_3:

            return GET_DP_MAC_STREAM_RX3_SOURCE_TYPE_JUDGE();
#endif

#if(_DP_MAC_RX4_SUPPORT == _ON)
        case _DP_MAC_4:

            return GET_DP_MAC_STREAM_RX4_SOURCE_TYPE_JUDGE();
#endif

        default:

            return _FALSE;
    }
}
#endif

#endif
