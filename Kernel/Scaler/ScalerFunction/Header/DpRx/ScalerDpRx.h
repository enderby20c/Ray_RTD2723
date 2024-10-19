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
// ID Code      : ScalerDpRx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_RX_H__
#define __SCALER_DP_RX_H__


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
extern StructDpCableStatus g_stDpRxCableStatus;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumDpHotPlugAssertType ScalerDpRxGetHotPlugEvent(EnumInputPort enumInputPort);
extern void ScalerDpRxClearHotPlugEvent(EnumInputPort enumInputPort);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRxHdcpResetUpstreamEventProc(void);
#endif

#endif // End of #if(_DP_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_DP_RX_H__
