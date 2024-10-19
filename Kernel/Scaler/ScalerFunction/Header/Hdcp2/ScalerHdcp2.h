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
// ID Code      : ScalerHdcp2.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_HDCP2_H__
#define __SCALER_HDCP2_H__

#if(_HDCP_2_2_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_pucHdcp2SHA256Input[64];

extern BYTE g_pucHdcp2DpRrxErrta0[8];
extern BYTE g_pucHdcp2DpRrxErrta1[8];


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerHdcp2RxDownLoadCalculateKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray, BYTE ucRSAType);
extern void ScalerHdcp2RxGetRrx_EXINT0(BYTE *pucHdcp2Rrx);

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern bit ScalerHdcp2RepeaterHmacSha256Calculate(BYTE *pucInputArray1, BYTE *pucInputArray2, BYTE ucInputArray1BlockNumber);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_DP_MST_SUPPORT == _ON)
extern bit ScalerHdcp2RepeaterLPrimeHmacSha256Calculate(BYTE *pucInputArray1, BYTE *pucInputArray2, BYTE *pucInputArray3);
#endif
#endif

#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_HDCP2_H__
