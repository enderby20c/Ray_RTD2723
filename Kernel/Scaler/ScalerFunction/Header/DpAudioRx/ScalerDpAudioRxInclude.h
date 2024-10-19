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
// ID Code      : ScalerDpAudioRxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_RX_AUDIO_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DP_MAC_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern bit ScalerDpAudioRxGetChannelStatusBit1Support(void);
#endif // End of #if(_DP_MAC_RX_128B132B_CODING_TYPE_SUPPORT == _ON)

#endif // End of #if(_DP_RX_AUDIO_SUPPORT == _ON)

