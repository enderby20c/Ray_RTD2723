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
// ID Code      : ScalerDpHdcp14Rx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_HDCP14_RX1_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Macro of RX HDCP Authentication
//--------------------------------------------------
#define GET_DP_HDCP14_RX1_AUTH_STATE()                  (g_stDpHdcp14Rx1AuthInfo.b4AuthState)
#define SET_DP_HDCP14_RX1_AUTH_STATE(x)                 (g_stDpHdcp14Rx1AuthInfo.b4AuthState = (x))

#define GET_DP_HDCP14_RX1_AUTH_STATE_CHANGE()           (g_stDpHdcp14Rx1AuthInfo.b1AuthStateChange)
#define SET_DP_HDCP14_RX1_AUTH_STATE_CHANGE()           (g_stDpHdcp14Rx1AuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_HDCP14_RX1_AUTH_STATE_CHANGE()           (g_stDpHdcp14Rx1AuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_HDCP14_RX1_AUTH_REPEATER_PROC_TIMEOUT()  (g_stDpHdcp14Rx1AuthInfo.b1AuthRepeaterProcTimeout)
#define SET_DP_HDCP14_RX1_AUTH_REPEATER_PROC_TIMEOUT()  (g_stDpHdcp14Rx1AuthInfo.b1AuthRepeaterProcTimeout = _TRUE)
#define CLR_DP_HDCP14_RX1_AUTH_REPEATER_PROC_TIMEOUT()  (g_stDpHdcp14Rx1AuthInfo.b1AuthRepeaterProcTimeout = _FALSE)

#define GET_DP_HDCP14_RX1_AUTH_READ_IRQ_TIMEOUT()       (g_stDpHdcp14Rx1AuthInfo.b1AuthReadIrqTimeout)
#define SET_DP_HDCP14_RX1_AUTH_READ_IRQ_TIMEOUT()       (g_stDpHdcp14Rx1AuthInfo.b1AuthReadIrqTimeout = _TRUE)
#define CLR_DP_HDCP14_RX1_AUTH_READ_IRQ_TIMEOUT()       (g_stDpHdcp14Rx1AuthInfo.b1AuthReadIrqTimeout = _FALSE)

#define GET_DP_HDCP14_RX1_UPSTREAM_EVENT()              (g_stDpHdcp14Rx1AuthInfo.ucAuthUpstreamEvent)
#define SET_DP_HDCP14_RX1_UPSTREAM_EVENT(x)             (g_stDpHdcp14Rx1AuthInfo.ucAuthUpstreamEvent = (x))
#define CLR_DP_HDCP14_RX1_UPSTREAM_EVENT()              (g_stDpHdcp14Rx1AuthInfo.ucAuthUpstreamEvent = _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE)

#define GET_DP_HDCP14_RX1_AUTH_CPIRQ_TIMRE()            (g_stDpHdcp14Rx1AuthInfo.b1AuthCpIrqTimer)
#define SET_DP_HDCP14_RX1_AUTH_CPIRQ_TIMRE()            (g_stDpHdcp14Rx1AuthInfo.b1AuthCpIrqTimer = _TRUE)
#define CLR_DP_HDCP14_RX1_AUTH_CPIRQ_TIMRE()            (g_stDpHdcp14Rx1AuthInfo.b1AuthCpIrqTimer = _FALSE)

#define GET_DP_HDCP14_RX1_AUTH_AKSV_WRITTEN()           (g_bDpHdcp14Rx1AksvWritten)
#define SET_DP_HDCP14_RX1_AUTH_AKSV_WRITTEN()           (g_bDpHdcp14Rx1AksvWritten = _TRUE)
#define CLR_DP_HDCP14_RX1_AUTH_AKSV_WRITTEN()           (g_bDpHdcp14Rx1AksvWritten = _FALSE)

#define GET_DP_HDCP14_RX1_REPEATER_AUTH_1_START()       (g_stDpHdcp14Rx1AuthInfo.b1AuthRepeaterAuth1Start)
#define SET_DP_HDCP14_RX1_REPEATER_AUTH_1_START()       (g_stDpHdcp14Rx1AuthInfo.b1AuthRepeaterAuth1Start = _TRUE)
#define CLR_DP_HDCP14_RX1_REPEATER_AUTH_1_START()       (g_stDpHdcp14Rx1AuthInfo.b1AuthRepeaterAuth1Start = _FALSE)

#define GET_DP_HDCP14_RX1_CAPABLE_SUPPORT()             (ScalerDpAuxRxGetDpcdBitInfo(ScalerDpHdcpRxRxDxMapping(_RX1), 0x06, 0x80, 0x28, _BIT0) == _BIT0)

#define GET_DP_HDCP14_RX1_REPEATER_SUPPORT()            ((g_ucDpHdcp14Rx1Caps & _BIT1) != 0)

#define SET_DP_HDCP14_RX1_REPEATER_SUPPORT()            {\
                                                            ScalerDpAuxRxSetDpcdBitValue(ScalerDpHdcpRxRxDxMapping(_RX1), 0x06, 0x80, 0x28, ~_BIT1, _BIT1);\
                                                            g_ucDpHdcp14Rx1Caps |= _BIT1;\
                                                        }

#define CLR_DP_HDCP14_RX1_REPEATER_SUPPORT()            {\
                                                            ScalerDpAuxRxSetDpcdBitValue(ScalerDpHdcpRxRxDxMapping(_RX1), 0x06, 0x80, 0x28, ~_BIT1, 0x00);\
                                                            g_ucDpHdcp14Rx1Caps &= 0xFD;\
                                                        }
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
extern volatile bit g_bDpHdcp14Rx1AksvWritten;
extern StructDPMacRxHDCPAuthInfo g_stDpHdcp14Rx1AuthInfo;
#endif
extern BYTE g_ucDpHdcp14Rx1Caps;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpHdcp14Rx1ResetProc(void);
#if(_DP_HDCP14_RX1_REPEATER_SUPPORT == _ON)
extern void ScalerDpHdcp14Rx1RepeaterHandler(void);
extern void ScalerDpHdcp14Rx1ChangeAuthState(EnumDPRxHDCPAuthState enumHDCPAuthState);
extern void ScalerDpHdcp14Rx1ResetKsvFifoToFirst_EXINT0(void);
extern void ScalerDpHdcp14Rx1SetKsvFifo_EXINT0(void);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpHdcp14Rx1ChangeECFCheck(void);
#endif
extern void ScalerDpHdcp14Rx1RepeaterSupportProc(void);
extern void ScalerDpHdcp14Rx1ReAuthProcess(EnumInputPort enumInputPort);
#endif
#endif
