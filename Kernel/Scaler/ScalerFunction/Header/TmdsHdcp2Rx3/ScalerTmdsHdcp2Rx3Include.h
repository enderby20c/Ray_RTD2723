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
// ID Code      : ScalerTmdsHdcp2Rx3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDCP 2.2 Authentication State
//--------------------------------------------------
#define GET_TMDS_HDCP2_RX3_AKE_INIT_RECEIVED()                      (bit)(g_ucTmdsHdcp2Rx3Ctrl & _BIT7)
#define SET_TMDS_HDCP2_RX3_AKE_INIT_RECEIVED()                      (g_ucTmdsHdcp2Rx3Ctrl |= _BIT7)
#define CLR_TMDS_HDCP2_RX3_AKE_INIT_RECEIVED()                      (g_ucTmdsHdcp2Rx3Ctrl &= ~_BIT7)

#define GET_TMDS_HDCP2_RX3_AKE_NO_STORED_KM_RECEIVED()              (bit)(g_ucTmdsHdcp2Rx3Ctrl & _BIT6)
#define SET_TMDS_HDCP2_RX3_AKE_NO_STORED_KM_RECEIVED()              (g_ucTmdsHdcp2Rx3Ctrl |= _BIT6)
#define CLR_TMDS_HDCP2_RX3_AKE_NO_STORED_KM_RECEIVED()              (g_ucTmdsHdcp2Rx3Ctrl &= ~_BIT6)

#define GET_TMDS_HDCP2_RX3_AKE_STORED_KM_RECEIVED()                 (bit)(g_ucTmdsHdcp2Rx3Ctrl & _BIT5)
#define SET_TMDS_HDCP2_RX3_AKE_STORED_KM_RECEIVED()                 (g_ucTmdsHdcp2Rx3Ctrl |= _BIT5)
#define CLR_TMDS_HDCP2_RX3_AKE_STORED_KM_RECEIVED()                 (g_ucTmdsHdcp2Rx3Ctrl &= ~_BIT5)

#define GET_TMDS_HDCP2_RX3_LC_INIT_RECEIVED()                       (bit)(g_ucTmdsHdcp2Rx3Ctrl & _BIT4)
#define SET_TMDS_HDCP2_RX3_LC_INIT_RECEIVED()                       (g_ucTmdsHdcp2Rx3Ctrl |= _BIT4)
#define CLR_TMDS_HDCP2_RX3_LC_INIT_RECEIVED()                       (g_ucTmdsHdcp2Rx3Ctrl &= ~_BIT4)

#define GET_TMDS_HDCP2_RX3_SKE_SEND_EKS_RECEIVED()                  (bit)(g_ucTmdsHdcp2Rx3Ctrl & _BIT3)
#define SET_TMDS_HDCP2_RX3_SKE_SEND_EKS_RECEIVED()                  (g_ucTmdsHdcp2Rx3Ctrl |= _BIT3)
#define CLR_TMDS_HDCP2_RX3_SKE_SEND_EKS_RECEIVED()                  (g_ucTmdsHdcp2Rx3Ctrl &= ~_BIT3)

#define GET_TMDS_HDCP2_RX3_AUTHENTICATION_DONE()                    (bit)(g_ucTmdsHdcp2Rx3Ctrl & _BIT2)
#define SET_TMDS_HDCP2_RX3_AUTHENTICATION_DONE()                    (g_ucTmdsHdcp2Rx3Ctrl |= _BIT2)
#define CLR_TMDS_HDCP2_RX3_AUTHENTICATION_DONE()                    (g_ucTmdsHdcp2Rx3Ctrl &= ~_BIT2)

#define SET_TMDS_HDCP2_RX3_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive |= _BIT3)
#define CLR_TMDS_HDCP2_RX3_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive &= ~_BIT3)

#define GET_TMDS_HDCP2_RX3_MODE()                                   (ScalerGetBit(P2E_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7)

//--------------------------------------------------
// Macro of HDCP 2.2 Authentication State
//--------------------------------------------------
#define GET_TMDS_HDCP2_RX3_AUTH_STATE()                             (g_stTmdsHdcp2Rx3AuthInfo.b4AuthState)
#define SET_TMDS_HDCP2_RX3_AUTH_STATE(x)                            (g_stTmdsHdcp2Rx3AuthInfo.b4AuthState = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)
extern volatile BYTE g_ucTmdsHdcp2Rx3Ctrl;
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_MAC_RX3_SUPPORT == _ON)

extern void ScalerTmdsHdcp2Rx3Handler(void);
extern bit ScalerTmdsHdcp2Rx3GetHdcpContentEncStatus(void);
extern void ScalerTmdsHdcp2Rx3IntHandler_EXINT0(void);
extern void ScalerTmdsHdcp2Rx3ResetProc_EXINT0(void);
extern void ScalerTmdsHdcp2Rx3ReAuthEvent(void);

extern void ScalerTmdsHdcp2Rx3ResetProc(void);

extern void ScalerTmdsHdcp2Rx3RxRsaCalculate_WDINT(void);
extern void ScalerTmdsHdcp2Rx3HPrime_WDINT(BYTE *pucTemp1);
#endif
#endif

