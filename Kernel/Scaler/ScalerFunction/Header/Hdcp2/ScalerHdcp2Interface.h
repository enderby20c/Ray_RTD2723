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
// ID Code      : ScalerHdcp2Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDCP 2.2 RSA input parameter
//--------------------------------------------------
#define _HDCP22_RSA_CIPHER_TEXT                 0
#define _HDCP22_RSA_RRMODN_KEY                  1
#define _HDCP22_RSA_D_KEY                       2
#define _HDCP22_RSA_N_PINV                      4
#define _HDCP22_RSA_D_KEY_ENC                   5
#define _HDCP22_CERT_RX                         6
#define _HDCP22_LC                              7
#define _HDCP22_KPUB_KM                         8
#define _HDCP22_RRX                             9
#define _HDCP22_RX_H_PRIME                      10
#define _HDCP22_RX_PAIRING_INFO                 11
#define _HDCP22_RX_L_PRIME                      12
#define _HDCP22_RX_M_PRIME                      13
#define _HDCP22_RX_V_PRIME                      14

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HDCP_2_2_SUPPORT == _ON)
extern void ScalerHdcp2Handler(void);
extern void ScalerHdcp2DownLoadCalculateKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray, BYTE ucRSAType);
extern void ScalerHdcp2IntHandler_EXINT0(void);
extern bit ScalerHdcp2RxPairingCalculate(BYTE *pucHdcp2KPriv, BYTE ucIndex);

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#if(_TX_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_IROM)
extern void ScalerHdcp2GetTxHdcp2DcpLlcNFromIrom(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void ScalerHdcp2GetTxHdcp2EKeyFromIrom(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void ScalerHdcp2GetTxHdcp2RRMODNFromIrom(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void ScalerHdcp2GetTxHdcp2NPinvFromIrom(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#endif

