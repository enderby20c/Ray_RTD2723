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
// ID Code      : ScalerDpHdcp2Rx0.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_HDCP2_RX0_H__
#define __SCALER_DP_HDCP2_RX0_H__

#if((_DP_HDCP2_RX0_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_pucDpHdcp2Rx0Km[16];
extern BYTE g_pucDpHdcp2Rx0Rtx[8];
extern BYTE g_pucDpHdcp2Rx0TxCaps[3];
extern BYTE g_pucDpHdcp2Rx0Rn[8];
extern BYTE g_pucDpHdcp2Rx0Rrx[8];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpHdcp2Rx0LoadDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerDpHdcp2Rx0ResetProc_EXINT0(void);
extern void ScalerDpHdcp2Rx0SetDpcdReadValue_EXINT0(BYTE ucRSAType, BYTE *pucReadArray, WORD usLength);
extern void ScalerDpHdcp2Rx0ClearDpcdReadValue_EXINT0(BYTE ucRSAType, WORD usLength);

extern void ScalerDpHdcp2Rx0ClearDpcdReadValue(BYTE ucRSAType, WORD usLength);
extern bit ScalerDpHdcp2Rx0CaptureKpubKm(void);
extern void ScalerDpHdcp2Rx0CalculateKmKh(void);

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpHdcp2Rx0CheckRxInfo(void);
extern void ScalerDpHdcp2Rx0LoadReceiverIdList(void);
extern bit ScalerDpHdcp2Rx0VComputeProc(void);
extern bit ScalerDpHdcp2Rx0FakeAuthenProc(void);
extern bit ScalerDpHdcp2Rx0ReauthEventCheck(void);
extern void ScalerDpHdcp2Rx0ClearDpcdRepeaterInfo(void);
#endif

extern void ScalerDpHdcp2Rx0LoadDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucLength, BYTE *pucReadArray);

#endif // End of #if((_DP_HDCP2_RX0_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))


#endif // End of #ifndef __SCALER_DP_HDCP2_RX0_H__
