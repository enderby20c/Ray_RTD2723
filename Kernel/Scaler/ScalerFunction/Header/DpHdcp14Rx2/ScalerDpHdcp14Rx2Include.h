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
// ID Code      : ScalerDpHdcp14Rx2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_HDCP14_RX2_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Macro of RX HDCP Authentication
//--------------------------------------------------
#define GET_DP_HDCP14_RX2_AUTH_STATE()                  (g_stDpHdcp14Rx2AuthInfo.b4AuthState)
#define SET_DP_HDCP14_RX2_AUTH_STATE(x)                 (g_stDpHdcp14Rx2AuthInfo.b4AuthState = (x))

#define GET_DP_HDCP14_RX2_AUTH_STATE_CHANGE()           (g_stDpHdcp14Rx2AuthInfo.b1AuthStateChange)
#define SET_DP_HDCP14_RX2_AUTH_STATE_CHANGE()           (g_stDpHdcp14Rx2AuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_HDCP14_RX2_AUTH_STATE_CHANGE()           (g_stDpHdcp14Rx2AuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_HDCP14_RX2_AUTH_REPEATER_PROC_TIMEOUT()  (g_stDpHdcp14Rx2AuthInfo.b1AuthRepeaterProcTimeout)
#define SET_DP_HDCP14_RX2_AUTH_REPEATER_PROC_TIMEOUT()  (g_stDpHdcp14Rx2AuthInfo.b1AuthRepeaterProcTimeout = _TRUE)
#define CLR_DP_HDCP14_RX2_AUTH_REPEATER_PROC_TIMEOUT()  (g_stDpHdcp14Rx2AuthInfo.b1AuthRepeaterProcTimeout = _FALSE)

#define GET_DP_HDCP14_RX2_AUTH_READ_IRQ_TIMEOUT()       (g_stDpHdcp14Rx2AuthInfo.b1AuthReadIrqTimeout)
#define SET_DP_HDCP14_RX2_AUTH_READ_IRQ_TIMEOUT()       (g_stDpHdcp14Rx2AuthInfo.b1AuthReadIrqTimeout = _TRUE)
#define CLR_DP_HDCP14_RX2_AUTH_READ_IRQ_TIMEOUT()       (g_stDpHdcp14Rx2AuthInfo.b1AuthReadIrqTimeout = _FALSE)

#define GET_DP_HDCP14_RX2_UPSTREAM_EVENT()              (g_stDpHdcp14Rx2AuthInfo.ucAuthUpstreamEvent)
#define SET_DP_HDCP14_RX2_UPSTREAM_EVENT(x)             (g_stDpHdcp14Rx2AuthInfo.ucAuthUpstreamEvent = (x))
#define CLR_DP_HDCP14_RX2_UPSTREAM_EVENT()              (g_stDpHdcp14Rx2AuthInfo.ucAuthUpstreamEvent = _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE)

#define GET_DP_HDCP14_RX2_AUTH_CPIRQ_TIMRE()            (g_stDpHdcp14Rx2AuthInfo.b1AuthCpIrqTimer)
#define SET_DP_HDCP14_RX2_AUTH_CPIRQ_TIMRE()            (g_stDpHdcp14Rx2AuthInfo.b1AuthCpIrqTimer = _TRUE)
#define CLR_DP_HDCP14_RX2_AUTH_CPIRQ_TIMRE()            (g_stDpHdcp14Rx2AuthInfo.b1AuthCpIrqTimer = _FALSE)

#define GET_DP_HDCP14_RX2_AUTH_AKSV_WRITTEN()           (g_bDpHdcp14Rx2AksvWritten)
#define SET_DP_HDCP14_RX2_AUTH_AKSV_WRITTEN()           (g_bDpHdcp14Rx2AksvWritten = _TRUE)
#define CLR_DP_HDCP14_RX2_AUTH_AKSV_WRITTEN()           (g_bDpHdcp14Rx2AksvWritten = _FALSE)

#define GET_DP_HDCP14_RX2_REPEATER_AUTH_1_START()       (g_stDpHdcp14Rx2AuthInfo.b1AuthRepeaterAuth1Start)
#define SET_DP_HDCP14_RX2_REPEATER_AUTH_1_START()       (g_stDpHdcp14Rx2AuthInfo.b1AuthRepeaterAuth1Start = _TRUE)
#define CLR_DP_HDCP14_RX2_REPEATER_AUTH_1_START()       (g_stDpHdcp14Rx2AuthInfo.b1AuthRepeaterAuth1Start = _FALSE)

#define GET_DP_HDCP14_RX2_CAPABLE_SUPPORT()             (ScalerDpAuxRxGetDpcdBitInfo(ScalerDpHdcpRxRxDxMapping(_RX2), 0x06, 0x80, 0x28, _BIT0) == _BIT0)

#define GET_DP_HDCP14_RX2_REPEATER_SUPPORT()            ((g_ucDpHdcp14Rx2Caps & _BIT1) != 0)

#define SET_DP_HDCP14_RX2_REPEATER_SUPPORT()            {\
                                                            ScalerDpAuxRxSetDpcdBitValue(ScalerDpHdcpRxRxDxMapping(_RX2), 0x06, 0x80, 0x28, ~_BIT1, _BIT1);\
                                                            g_ucDpHdcp14Rx2Caps |= _BIT1;\
                                                        }

#define CLR_DP_HDCP14_RX2_REPEATER_SUPPORT()            {\
                                                            ScalerDpAuxRxSetDpcdBitValue(ScalerDpHdcpRxRxDxMapping(_RX2), 0x06, 0x80, 0x28, ~_BIT1, 0x00);\
                                                            g_ucDpHdcp14Rx2Caps &= 0xFD;\
                                                        }
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
extern volatile bit g_bDpHdcp14Rx2AksvWritten;
extern StructDPMacRxHDCPAuthInfo g_stDpHdcp14Rx2AuthInfo;
#endif
extern BYTE g_ucDpHdcp14Rx2Caps;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpHdcp14Rx2ResetProc(void);
#if(_DP_HDCP14_RX2_REPEATER_SUPPORT == _ON)
extern void ScalerDpHdcp14Rx2RepeaterHandler(void);
extern void ScalerDpHdcp14Rx2ChangeAuthState(EnumDPRxHDCPAuthState enumHDCPAuthState);
extern void ScalerDpHdcp14Rx2ResetKsvFifoToFirst_EXINT0(void);
extern void ScalerDpHdcp14Rx2SetKsvFifo_EXINT0(void);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpHdcp14Rx2ChangeECFCheck(void);
#endif
extern void ScalerDpHdcp14Rx2RepeaterSupportProc(void);
extern void ScalerDpHdcp14Rx2ReAuthProcess(EnumInputPort enumInputPort);
#endif

#endif
