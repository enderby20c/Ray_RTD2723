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
// ID Code      : ScalerDpHdcp14Tx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_HDCP_14_TX_H__
#define __SCALER_DP_HDCP_14_TX_H__

#if(_DP_TX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_TX_HDCP_R0_RETRY_COUNTER()                   (g_usDpHdcp14TxR0RetryCounter)
#define ADD_DP_TX_HDCP_R0_RETRY_COUNTER()                   (g_usDpHdcp14TxR0RetryCounter++)
#define CLR_DP_TX_HDCP_R0_RETRY_COUNTER()                   (g_usDpHdcp14TxR0RetryCounter = 0)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern WORD g_usDpHdcp14TxR0RetryCounter;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerDpHdcp14TxAuth1Proc(void);
extern bit ScalerDpHdcp14TxAuth1CheckBksv(void);
extern void ScalerDpHdcp14TxAuth1GenAn(void);
extern void ScalerDpHdcp14TxAuth1WriteAnAkey(void);
extern bit ScalerDpHdcp14TxAuth1GenKm(void);
extern bit ScalerDpHdcp14TxAuth1CompareR0(void);
extern bit ScalerDpHdcp14TxAuth2Proc(void);
extern void ScalerDpHdcp14TxAuth2WriteShaInput(void);
extern bit ScalerDpHdcp14TxCheckBinfo(void);
extern bit ScalerDpHdcp14TxAuth2CompareV(void);
extern EnumDPTxTRQEventHDCPType ScalerDpHdcp14TxPollingCpIrqType(void);
#endif // End of #if(_DP_TX_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_DP_HDCP_14_TX_H__
