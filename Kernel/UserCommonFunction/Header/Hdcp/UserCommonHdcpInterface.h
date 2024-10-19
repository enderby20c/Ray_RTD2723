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
// ID Code      : UserCommonHdcpInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
#if(_DIGITAL_PORT_SUPPORT == _ON)
extern void UserCommonHdcpGetKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonHdcpGetKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonHdcpLoadKey(void);

#if(_HDCP_2_2_SUPPORT == _ON)
extern void UserCommonHdcp2GetCertrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonHdcp2GetRSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonHdcp2GetRSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonHdcp2GetRSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonHdcp2GetRSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonHdcp2GetLCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern void UserCommonHdcp2GetDpTxRRMODN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonHdcp2GetDpTxDcpLlcN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonHdcp2GetDpTxEKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonHdcp2GetDpTxNPinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif

#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonHdcpGetTxKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonHdcpGetTxKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

