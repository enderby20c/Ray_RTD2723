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
// ID Code      : ScalerDpHdcp2Tx.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_HDCP2_TX_H__
#define __SCALER_DP_HDCP2_TX_H__

#if((_DP_HDCP2_RX_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DP_HDCP2_TX_LC_RETRY_MAX_NUMBER                    1024

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpHdcp2TxResetAuthInfo(void);
extern void ScalerDpHdcp2TxChangeAuthState(EnumHdcp2TxAuthState enumHdcp2AuthState);
extern EnumHdcp2TxCpirqType ScalerDpHdcp2TxPollingCpIrqType(void);
extern bit ScalerDpHdcp2TxAkeInitial(void);
extern bit ScalerDpHdcp2TxRandomGenerate(void);
extern bit ScalerDpHdcp2TxDcpLlcRsaCalculate(void);
extern bit ScalerDpHdcp2TxVerifySignature(void);
extern bit ScalerDpHdcp2TxRsaCalculate(BYTE *pucEmKmArray, BYTE *pucRrmodn);
extern bit ScalerDpHdcp2TxNoStoredKmProc(void);
extern bit ScalerDpHdcp2TxRrmodnCalculate(BYTE *pucPubN);
extern WORD ScalerDpHdcp2TxGetNShiftCounter(BYTE *pucPubN);
extern DWORD ScalerDpHdcp2TxNpinvCalculate(DWORD ulA);
extern bit ScalerDpHdcp2TxStoredKmProc(void);
extern bit ScalerDpHdcp2TxComputeH(BYTE *pucDpTxHdcp2Rtx, BYTE *pucDpTxHdcp2Rrx, BYTE *pucDpTxHdcp2Km);
extern bit ScalerDpHdcp2TxVerifyHprime(void);
extern bit ScalerDpHdcp2TxStorePairingInfo(void);
extern void ScalerDpHdcp2TxClearPairingInfo(void);
extern bit ScalerDpHdcp2TxCheckPairingInfo(void);
extern bit ScalerDpHdcp2TxLocalityCheck(void);
extern bit ScalerDpHdcp2TxSessionKeyExchangeProc(void);
extern bit ScalerDpHdcp2TxChecRxInfo(void);
extern bit ScalerDpHdcp2TxVerifyVprime(void);
extern bit ScalerDpHdcp2TxContentStreamManagement(void);
extern bit ScalerDpHdcp2TxVerifyMprime(void);
extern void ScalerDpHdcp2TxContentStreamManagementHandler(void);
extern BYTE ScalerDpHdcp2TxGetUpstreamDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern bit ScalerDpHdcp2TxContentStreamManagement_8b10b(void);
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern bit ScalerDpHdcp2TxContentStreamManagement_128b132b(void);
#endif

#endif // End of #if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))


#endif // End of #ifndef __SCALER_DP_HDCP2_TX_H__
