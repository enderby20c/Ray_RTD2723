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
// ID Code      : ScalerDpHdcp2Rx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_HDCP2_RX1_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDCP 2.2 Authentication State
//--------------------------------------------------
#define GET_DP_HDCP2_RX1_AKE_INIT_RECEIVED()                      (bit)(g_ucDpHdcp2Rx1Ctrl0 & _BIT7)
#define SET_DP_HDCP2_RX1_AKE_INIT_RECEIVED()                      (g_ucDpHdcp2Rx1Ctrl0 |= _BIT7)
#define CLR_DP_HDCP2_RX1_AKE_INIT_RECEIVED()                      (g_ucDpHdcp2Rx1Ctrl0 &= ~_BIT7)

#define GET_DP_HDCP2_RX1_AKE_NO_STORED_KM_RECEIVED()              (bit)(g_ucDpHdcp2Rx1Ctrl0 & _BIT6)
#define SET_DP_HDCP2_RX1_AKE_NO_STORED_KM_RECEIVED()              (g_ucDpHdcp2Rx1Ctrl0 |= _BIT6)
#define CLR_DP_HDCP2_RX1_AKE_NO_STORED_KM_RECEIVED()              (g_ucDpHdcp2Rx1Ctrl0 &= ~_BIT6)

#define GET_DP_HDCP2_RX1_AKE_STORED_KM_RECEIVED()                 (bit)(g_ucDpHdcp2Rx1Ctrl0 & _BIT5)
#define SET_DP_HDCP2_RX1_AKE_STORED_KM_RECEIVED()                 (g_ucDpHdcp2Rx1Ctrl0 |= _BIT5)
#define CLR_DP_HDCP2_RX1_AKE_STORED_KM_RECEIVED()                 (g_ucDpHdcp2Rx1Ctrl0 &= ~_BIT5)

#define GET_DP_HDCP2_RX1_LC_INIT_RECEIVED()                       (bit)(g_ucDpHdcp2Rx1Ctrl0 & _BIT4)
#define SET_DP_HDCP2_RX1_LC_INIT_RECEIVED()                       (g_ucDpHdcp2Rx1Ctrl0 |= _BIT4)
#define CLR_DP_HDCP2_RX1_LC_INIT_RECEIVED()                       (g_ucDpHdcp2Rx1Ctrl0 &= ~_BIT4)

#define GET_DP_HDCP2_RX1_SKE_SEND_EKS_RECEIVED()                  (bit)(g_ucDpHdcp2Rx1Ctrl0 & _BIT3)
#define SET_DP_HDCP2_RX1_SKE_SEND_EKS_RECEIVED()                  (g_ucDpHdcp2Rx1Ctrl0 |= _BIT3)
#define CLR_DP_HDCP2_RX1_SKE_SEND_EKS_RECEIVED()                  (g_ucDpHdcp2Rx1Ctrl0 &= ~_BIT3)

#define GET_DP_HDCP2_RX1_STREAM_MANAGE_RECEIVED()                 (bit)(g_ucDpHdcp2Rx1Ctrl0 & _BIT2)
#define SET_DP_HDCP2_RX1_STREAM_MANAGE_RECEIVED()                 (g_ucDpHdcp2Rx1Ctrl0 |= _BIT2)
#define CLR_DP_HDCP2_RX1_STREAM_MANAGE_RECEIVED()                 (g_ucDpHdcp2Rx1Ctrl0 &= ~_BIT2)

#define GET_DP_HDCP2_RX1_AUTHENTICATION_DONE()                    (bit)(g_ucDpHdcp2Rx1Ctrl0 & _BIT1)
#define SET_DP_HDCP2_RX1_AUTHENTICATION_DONE()                    (g_ucDpHdcp2Rx1Ctrl0 |= _BIT1)
#define CLR_DP_HDCP2_RX1_AUTHENTICATION_DONE()                    (g_ucDpHdcp2Rx1Ctrl0 &= ~_BIT1)

#define GET_DP_HDCP2_RX1_AKE_NO_STORED_KM_DONE()                  (bit)(g_ucDpHdcp2Rx1Ctrl0 & _BIT0)
#define SET_DP_HDCP2_RX1_AKE_NO_STORED_KM_DONE()                  (g_ucDpHdcp2Rx1Ctrl0 |= _BIT0)
#define CLR_DP_HDCP2_RX1_AKE_NO_STORED_KM_DONE()                  (g_ucDpHdcp2Rx1Ctrl0 &= ~_BIT0)

#if(_DP_HDCP_POWER_OFF_HANDSHAKE_SUPPORT == _ON)
#define GET_DP_HDCP2_RX1_HANDSHAKE_START()                        (bit)(g_ucDpHdcp2Rx1Ctrl1 & _BIT3)
#define SET_DP_HDCP2_RX1_HANDSHAKE_START()                        (g_ucDpHdcp2Rx1Ctrl1 |= _BIT3)
#define CLR_DP_HDCP2_RX1_HANDSHAKE_START()                        (g_ucDpHdcp2Rx1Ctrl1 &= ~_BIT3)
#endif

#define GET_DP_HDCP2_RX1_CLEAR_DPCD_READ_VALUE_DONE()             (bit)(g_ucDpHdcp2Rx1Ctrl1 & _BIT2)
#define SET_DP_HDCP2_RX1_CLEAR_DPCD_READ_VALUE_DONE()             (g_ucDpHdcp2Rx1Ctrl1 |= _BIT2)
#define CLR_DP_HDCP2_RX1_CLEAR_DPCD_READ_VALUE_DONE()             (g_ucDpHdcp2Rx1Ctrl1 &= ~_BIT2)

#define GET_DP_HDCP2_RX1_WAITING_H_PRIME_CPIRQ_ASSERTED()         (bit)(g_ucDpHdcp2Rx1Ctrl1 & _BIT1)
#define SET_DP_HDCP2_RX1_WAITING_H_PRIME_CPIRQ_ASSERTED()         (g_ucDpHdcp2Rx1Ctrl1 |= _BIT1)
#define CLR_DP_HDCP2_RX1_WAITING_H_PRIME_CPIRQ_ASSERTED()         (g_ucDpHdcp2Rx1Ctrl1 &= ~_BIT1)

#define GET_DP_HDCP2_RX1_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED()  (bit)(g_ucDpHdcp2Rx1Ctrl1 & _BIT0)
#define SET_DP_HDCP2_RX1_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED()  (g_ucDpHdcp2Rx1Ctrl1 |= _BIT0)
#define CLR_DP_HDCP2_RX1_RECORD_PAIRING_INFO_CPIRQ_NO_ASSERTED()  (g_ucDpHdcp2Rx1Ctrl1 &= ~_BIT0)

#define SET_DP_HDCP2_RX1_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive |= _BIT1)
#define CLR_DP_HDCP2_RX1_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive &= ~_BIT1)

#define GET_DP_HDCP2_RX1_V_PRIME(x)                               (g_pucDpHdcp2Rx1VPrime[x])

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Macro of RX HDCP2 Authentication
//--------------------------------------------------
#define GET_DP_HDCP2_RX1_AUTH_STATE()                             (g_stDpHdcp2Rx1AuthInfo.b4AuthState)
#define SET_DP_HDCP2_RX1_AUTH_STATE(x)                            (g_stDpHdcp2Rx1AuthInfo.b4AuthState = (x))

#define GET_DP_HDCP2_RX1_AUTH_STATE_CHANGE()                      (g_stDpHdcp2Rx1AuthInfo.b1AuthStateChange)
#define SET_DP_HDCP2_RX1_AUTH_STATE_CHANGE()                      (g_stDpHdcp2Rx1AuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_HDCP2_RX1_AUTH_STATE_CHANGE()                      (g_stDpHdcp2Rx1AuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_HDCP2_RX1_AUTH_REPEATER_PROC_TIMEOUT()             (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterProcTimeout)
#define SET_DP_HDCP2_RX1_AUTH_REPEATER_PROC_TIMEOUT()             (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterProcTimeout = _TRUE)
#define CLR_DP_HDCP2_RX1_AUTH_REPEATER_PROC_TIMEOUT()             (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterProcTimeout = _FALSE)

#define GET_DP_HDCP2_RX1_UPSTREAM_EVENT()                         (g_stDpHdcp2Rx1AuthInfo.ucAuthUpstreamEvent)
#define SET_DP_HDCP2_RX1_UPSTREAM_EVENT(x)                        (g_stDpHdcp2Rx1AuthInfo.ucAuthUpstreamEvent = (x))
#define CLR_DP_HDCP2_RX1_UPSTREAM_EVENT()                         (g_stDpHdcp2Rx1AuthInfo.ucAuthUpstreamEvent = _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_NONE)

#define GET_DP_HDCP2_RX1_AUTH_CPIRQ_TIMRE()                       (g_stDpHdcp2Rx1AuthInfo.b1AuthCpIrqTimer)
#define SET_DP_HDCP2_RX1_AUTH_CPIRQ_TIMRE()                       (g_stDpHdcp2Rx1AuthInfo.b1AuthCpIrqTimer = _TRUE)
#define CLR_DP_HDCP2_RX1_AUTH_CPIRQ_TIMRE()                       (g_stDpHdcp2Rx1AuthInfo.b1AuthCpIrqTimer = _FALSE)

#define GET_DP_HDCP2_RX1_CONTENT_STREAM_MANAGEMENT()              (g_stDpHdcp2Rx1AuthInfo.b1AuthHdcp2ContentStreamManage)
#define SET_DP_HDCP2_RX1_CONTENT_STREAM_MANAGEMENT()              (g_stDpHdcp2Rx1AuthInfo.b1AuthHdcp2ContentStreamManage = _TRUE)
#define CLR_DP_HDCP2_RX1_CONTENT_STREAM_MANAGEMENT()              (g_stDpHdcp2Rx1AuthInfo.b1AuthHdcp2ContentStreamManage = _FALSE)

#define GET_DP_HDCP2_RX1_REPEATER_AUTH_1_START()                  (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterAuth1Start)
#define SET_DP_HDCP2_RX1_REPEATER_AUTH_1_START()                  (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterAuth1Start = _TRUE)
#define CLR_DP_HDCP2_RX1_REPEATER_AUTH_1_START()                  (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterAuth1Start = _FALSE)

#define GET_DP_HDCP2_RX1_REPEATER_AUTH_2_START()                  (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterAuth2Start)
#define SET_DP_HDCP2_RX1_REPEATER_AUTH_2_START()                  (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterAuth2Start = _TRUE)
#define CLR_DP_HDCP2_RX1_REPEATER_AUTH_2_START()                  (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterAuth2Start = _FALSE)

#define GET_DP_HDCP2_RX1_REPEATER_DFP_REAUTH()                    (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterSelfReAuth)
#define SET_DP_HDCP2_RX1_REPEATER_DFP_REAUTH()                    (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterSelfReAuth = _TRUE)
#define CLR_DP_HDCP2_RX1_REPEATER_DFP_REAUTH()                    (g_stDpHdcp2Rx1AuthInfo.b1AuthRepeaterSelfReAuth = _FALSE)

#define GET_DP_HDCP2_RX1_CAPABLE_SUPPORT()                        (ScalerDpAuxRxGetDpcdBitInfo(ScalerDpHdcpRxRxDxMapping(_RX1), 0x06, 0x92, 0x1F, _BIT1) == _BIT1)

// #define GET_DP_HDCP2_RX1_REPEATER_SUPPORT()                       (ScalerDpAuxRxGetDpcdBitInfo(ScalerDpHdcpRxRxDxMapping(_RX1), 0x06, 0x92, 0x1F, _BIT0) == _BIT0)
#define GET_DP_HDCP2_RX1_REPEATER_SUPPORT()                       (bit)(g_pucDpHdcp2Rx1Caps[2] & _BIT0)

#define SET_DP_HDCP2_RX1_REPEATER_SUPPORT()                       {\
                                                                    ScalerDpAuxRxSetDpcdBitValue(ScalerDpHdcpRxRxDxMapping(_RX1), 0x06, 0x92, 0x1F, ~_BIT0, _BIT0);\
                                                                    g_pucDpHdcp2Rx1Caps[2] |= _BIT0;\
                                                                  }

#define CLR_DP_HDCP2_RX1_REPEATER_SUPPORT()                       {\
                                                                    ScalerDpAuxRxSetDpcdBitValue(ScalerDpHdcpRxRxDxMapping(_RX1), 0x06, 0x92, 0x1F, ~_BIT0, 0x00);\
                                                                    g_pucDpHdcp2Rx1Caps[2] &= 0xFE;\
                                                                  }

#define GET_DP_HDCP2_RX1_REAUTH_LONG_HPD()                        (g_stDpHdcp2Rx1AuthInfo.ucAuthLongHPDEvent)
#define SET_DP_HDCP2_RX1_REAUTH_LONG_HPD()                        (g_stDpHdcp2Rx1AuthInfo.ucAuthLongHPDEvent = _TRUE)
#define CLR_DP_HDCP2_RX1_REAUTH_LONG_HPD()                        {\
                                                                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP2_LONG_HOTPLUG_EVENT);\
                                                                    g_stDpHdcp2Rx1AuthInfo.ucAuthLongHPDEvent = _FALSE;\
                                                                  }

#define CLR_DP_HDCP2_RX1_REAUTH_LONG_HPD_EXINT()                  {\
                                                                    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_DP_RX1_HDCP2_LONG_HOTPLUG_EVENT);\
                                                                    g_stDpHdcp2Rx1AuthInfo.ucAuthLongHPDEvent = _FALSE;\
                                                                  }
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile BYTE g_ucDpHdcp2Rx1Ctrl0;
extern volatile BYTE g_ucDpHdcp2Rx1Ctrl1;
extern BYTE g_pucDpHdcp2Rx1dKey0[16];
extern BYTE g_pucDpHdcp2Rx1dKey1[16];
extern BYTE g_pucDpHdcp2Rx1VPrime[20];
extern BYTE g_pucDpHdcp2Rx1Caps[3];

#if(_DP_TX_SUPPORT == _ON)
extern volatile StructDpHdcp2RxAuthInfo g_stDpHdcp2Rx1AuthInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpHdcp2Rx1Handler(void);
extern void ScalerDpHdcp2Rx1Handler_EXINT0(void);
extern void ScalerDpHdcp2Rx1ResetProc(void);
extern void ScalerDpHdcp2Rx1CancelTimerEvent(void);
extern void ScalerDpHdcp2Rx1CancelTimerEvent_EXINT0(void);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpHdcp2Rx1RepeaterHandler(void);
extern void ScalerDpHdcp2Rx1ChangeAuthState(EnumDpHdcp2RxRepeaterAuthState enumHdcp2AuthState);
extern void ScalerDpHdcp2Rx1SetRepeaterProcTimeout(void);
extern void ScalerDpHdcp2Rx1RepeaterSupportProc(void);
extern bit ScalerDpHdcp2Rx1ReAuthStatusCheck(void);
extern void ScalerDpHdcp2Rx1ReAuthProcess(EnumInputPort enumInputPort);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpHdcp2Rx1ChangeECFCheck(void);
#endif
#endif

extern void ScalerDpHdcp2Rx1SkeProc_WDINT(void);
extern void ScalerDpHdcp2Rx1HPrimeProc_WDINT(void);
#if(_DP_HDCP2_RX1_REPEATER_SUPPORT == _ON)
extern void ScalerDpHdcp2Rx1MPrimeProc_WDINT(void);
extern BYTE ScalerDpHdcp2Rx1MPrimeCalculate_WDINT(EnumInputPort enumInputPort);
#endif
extern void ScalerDpHdcp2Rx1SetDpcdReadValue_WDINT(BYTE ucRSAType, BYTE *pucReadArray, WORD usLength);

#endif // End of #if((_DP_HDCP2_RX1_SUPPORT == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))

