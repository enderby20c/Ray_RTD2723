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
// ID Code      : ScalerTmdsHdcp2Rx3.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TMDS_HDCP2_RX3_H__
#define __SCALER_TMDS_HDCP2_RX3_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
extern volatile StructHdcp2HDCPAuthInfo g_stTmdsHdcp2Rx3AuthInfo;

extern BYTE g_pucTmdsHdcp2Rx3dKey0[16];
extern BYTE g_pucTmdsHdcp2Rx3dKey1[16];

extern BYTE g_pucTmdsHdcp2Rx3Km[16];

extern BYTE g_pucTmdsHdcp2Rx3Rtx[8];
extern BYTE g_pucTmdsHdcp2Rx3TxCaps[3];
extern BYTE g_pucTmdsHdcp2Rx3Rn[8];
extern BYTE g_pucTmdsHdcp2Rx3Rrx[8];
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
extern bit ScalerTmdsHdcp2Rx3LinkIntegrityCheckFail(void);
extern void ScalerTmdsHdcp2Rx3AesOnlineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray);
extern void ScalerTmdsHdcp2Rx3DownLoadWriteSRAMValue_EXINT0(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerTmdsHdcp2Rx3Enable_EXINT0(void);
extern void ScalerTmdsHdcp2Rx3LinkIntegrityCheckEnable_EXINT0(void);
extern void ScalerTmdsHdcp2Rx3RxRsaCalculate_EXINT0(void);
extern void ScalerTmdsHdcp2Rx3SetRdMsgIDCode_EXINT0(BYTE ucValue);
extern void ScalerTmdsHdcp2Rx3SetRdMsgIDCode_WDINT(BYTE ucValue);
extern void ScalerTmdsHdcp2Rx3SetRdMsgValue_EXINT0(WORD usAddress, BYTE *pucReadArray, WORD usLength);
extern void ScalerTmdsHdcp2Rx3SetRdMsgValue_WDINT(WORD usAddress, BYTE *pucReadArray, WORD usLength);
#endif

#endif


#endif // End of #ifndef __SCALER_TMDS_HDCP2_RX3_H__
