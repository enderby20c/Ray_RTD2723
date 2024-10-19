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
// ID Code      : ScalerDpHdcp2TxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_HDCP2_RX_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_HDCP2_TX_LOAD_KEY_EN()                          (bit)(g_ucDpHdcp2TxLoadKey & _BIT7)
#define SET_DP_HDCP2_TX_LOAD_KEY_EN()                          (g_ucDpHdcp2TxLoadKey |= _BIT7)
#define CLR_DP_HDCP2_TX_LOAD_KEY_EN()                          (g_ucDpHdcp2TxLoadKey &= ~_BIT7)

#define GET_DP_HDCP2_TX_LOAD_KEY_FINISH()                      (bit)(g_ucDpHdcp2TxLoadKey & _BIT6)
#define SET_DP_HDCP2_TX_LOAD_KEY_FINISH()                      (g_ucDpHdcp2TxLoadKey |= _BIT6)
#define CLR_DP_HDCP2_TX_LOAD_KEY_FINISH()                      (g_ucDpHdcp2TxLoadKey &= ~_BIT6)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucDpHdcp2TxLoadKey;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpHdcp2TxDcpLlcRsaInit(void);
extern void ScalerDpHdcp2TxLoadKeyProc(BYTE ucLoadKeyType, BYTE *pucDpTxHdcp2Key);
#endif // End of #if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

