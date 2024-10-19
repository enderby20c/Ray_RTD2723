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
// ID Code      : ScalerDpHdcp2Rx2.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_HDCP2_RX2_H__
#define __SCALER_DP_HDCP2_RX2_H__

#if((_DP_HDCP2_RX2_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_pucDpHdcp2Rx2Km[16];
extern BYTE g_pucDpHdcp2Rx2Rtx[8];
extern BYTE g_pucDpHdcp2Rx2TxCaps[3];
extern BYTE g_pucDpHdcp2Rx2Rn[8];
extern BYTE g_pucDpHdcp2Rx2Rrx[8];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpHdcp2Rx2LoadDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerDpHdcp2Rx2ResetProc_EXINT0(void);
extern void ScalerDpHdcp2Rx2SetDpcdReadValue_EXINT0(BYTE ucRSAType, BYTE *pucReadArray, WORD usLength);
extern void ScalerDpHdcp2Rx2ClearDpcdReadValue_EXINT0(BYTE ucRSAType, WORD usLength);

extern void ScalerDpHdcp2Rx2ClearDpcdReadValue(BYTE ucRSAType, WORD usLength);
extern bit ScalerDpHdcp2Rx2CaptureKpubKm(void);
extern void ScalerDpHdcp2Rx2CalculateKmKh(void);

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpHdcp2Rx2CheckRxInfo(void);
extern void ScalerDpHdcp2Rx2LoadReceiverIdList(void);
extern bit ScalerDpHdcp2Rx2VComputeProc(void);
extern bit ScalerDpHdcp2Rx2FakeAuthenProc(void);
extern bit ScalerDpHdcp2Rx2ReauthEventCheck(void);
extern void ScalerDpHdcp2Rx2ClearDpcdRepeaterInfo(void);
#endif

extern void ScalerDpHdcp2Rx2LoadDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray);

#endif // End of #if((_DP_HDCP2_RX2_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))


#endif // End of #ifndef __SCALER_DP_HDCP2_RX2_H__
