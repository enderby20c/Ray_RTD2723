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
// ID Code      : RL6952_Series_DpAudioRx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DPAUDIORX__

#include "ScalerFunctionInclude.h"
#include "DpAudioRx/ScalerDpAudioRx.h"

#if(_DP_RX_AUDIO_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_MAC_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Channel Status Bit_1 Support
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerDpAudioRxGetChannelStatusBit1Support(void)
{
    return _TRUE;
}
#endif // End of #if(_DP_MAC_RX_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif // End of #if(_DP_RX_AUDIO_SUPPORT == _ON)

