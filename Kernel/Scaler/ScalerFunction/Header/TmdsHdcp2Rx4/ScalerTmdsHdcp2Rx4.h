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
// ID Code      : ScalerTmdsHdcp2Rx4.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TMDS_HDCP2_RX4_H__
#define __SCALER_TMDS_HDCP2_RX4_H__

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
#if(_TMDS_MAC_RX4_SUPPORT == _ON)
extern volatile StructHdcp2HDCPAuthInfo g_stTmdsHdcp2Rx4AuthInfo;

extern BYTE g_pucTmdsHdcp2Rx4dKey0[16];
extern BYTE g_pucTmdsHdcp2Rx4dKey1[16];

extern BYTE g_pucTmdsHdcp2Rx4Km[16];

extern BYTE g_pucTmdsHdcp2Rx4Rtx[8];
extern BYTE g_pucTmdsHdcp2Rx4TxCaps[3];
extern BYTE g_pucTmdsHdcp2Rx4Rn[8];
extern BYTE g_pucTmdsHdcp2Rx4Rrx[8];

#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX4_SUPPORT == _ON)
extern bit ScalerTmdsHdcp2Rx4LinkIntegrityCheckFail(void);
extern void ScalerTmdsHdcp2Rx4AesOnlineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray);
extern void ScalerTmdsHdcp2Rx4DownLoadWriteSRAMValue_EXINT0(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerTmdsHdcp2Rx4Enable_EXINT0(void);
extern void ScalerTmdsHdcp2Rx4LinkIntegrityCheckEnable_EXINT0(void);
extern void ScalerTmdsHdcp2Rx4RxRsaCalculate_EXINT0(void);
extern void ScalerTmdsHdcp2Rx4SetRdMsgIDCode_EXINT0(BYTE ucValue);
extern void ScalerTmdsHdcp2Rx4SetRdMsgIDCode_WDINT(BYTE ucValue);
extern void ScalerTmdsHdcp2Rx4SetRdMsgValue_EXINT0(WORD usAddress, BYTE *pucReadArray, WORD usLength);
extern void ScalerTmdsHdcp2Rx4SetRdMsgValue_WDINT(WORD usAddress, BYTE *pucReadArray, WORD usLength);
#endif

#endif


#endif // End of #ifndef __SCALER_TMDS_HDCP2_RX4_H__
