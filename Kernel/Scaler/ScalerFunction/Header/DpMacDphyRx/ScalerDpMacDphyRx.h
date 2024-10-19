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
// ID Code      : ScalerDpMacDphyRx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MAC_DPHY_RX_H__
#define __SCALER_DP_MAC_DPHY_RX_H__

#if(_DP_SUPPORT == _ON)
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
///////////////////////////////////////////
// Function Group For NONE Postfix
///////////////////////////////////////////


///////////////////////////////////////////
// Function Group For 8B10B Postfix
///////////////////////////////////////////
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpMacDphyRxSetSourceMuxReg_8b10b(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacDphyRxSetSourceMuxReg_8b10b_EXINT0(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacDphyRxResetSourceMuxReg_8b10b(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxResetSourceMuxReg_8b10b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxLoadNewStreamPayload_8b10b(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxLoadNewStreamPayload_8b10b_EXINT0(EnumInputPort enumInputPort);
#endif


///////////////////////////////////////////
// Function Group For 128B132B Postfix
///////////////////////////////////////////
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpMacDphyRxSetSourceMuxReg_128b132b(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacDphyRxSetSourceMuxReg_128b132b_EXINT0(EnumInputPort enumInputPort, EnumDpStreamSourceNum enumSourceNum, EnumDpStreamNum enumDpStreamNum);
extern void ScalerDpMacDphyRxResetSourceMuxReg_128b132b(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxResetSourceMuxReg_128b132b_EXINT0(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxLoadNewStreamPayload_128b132b(EnumInputPort enumInputPort);
extern void ScalerDpMacDphyRxLoadNewStreamPayload_128b132b_EXINT0(EnumInputPort enumInputPort);
#endif

#endif

#endif // End of #ifndef __SCALER_DP_MAC_DPHY_RX_H__
