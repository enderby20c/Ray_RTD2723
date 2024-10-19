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
// ID Code      : ScalerDpHdcpRxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


#if(_DP_HDCP_RX_SUPPORT == _ON)
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
extern EnumRx ScalerDpHdcpRxDxRxMapping_EXINT0(EnumInputPort enumInputPort);

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
extern bit ScalerDpHdcpRxHandshakeStartCheck(void);
extern bit ScalerDpHdcpRxHandshakeStartInputPortCheck(EnumInputPort enumInputPort);
extern bit ScalerDpHdcpRxHandshakeStartActiveTimerCheck(EnumInputPort enumFixSearchPort);
#endif
#endif
