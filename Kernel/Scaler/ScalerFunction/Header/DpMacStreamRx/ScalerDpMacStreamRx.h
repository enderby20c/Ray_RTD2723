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
// ID Code      : ScalerDpMacStreamRx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_MAC_STREAM_RX_H__
#define __SCALER_DP_MAC_STREAM_RX_H__

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
extern bit ScalerDpMacStreamRxSclkWithinPllCapabilityCheck(EnumInputPort enumInputPort, DWORD ulTargetStreamClockHz);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDpMacStreamRxDscSetStreamWD(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDpMacStreamRxDscSetStreamIRQ(EnumInputPort enumInputPort, bit bEnable);
#endif

#if(_HW_DP_MAC_POWER_CUT_GEN == _DP_MAC_POWER_CUT_SEPARATE)
extern bit ScalerDpMacStreamRxCheckMacInUse(EnumDpMacSel enumDpMacSel);
#endif
#endif

#endif // End of #ifndef __SCALER_DP_MAC_STREAM_RX_H__
