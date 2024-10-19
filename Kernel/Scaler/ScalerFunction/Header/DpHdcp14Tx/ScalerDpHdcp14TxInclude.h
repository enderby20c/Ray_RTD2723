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
// ID Code      : ScalerDpHdcp14TxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_TX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of DP Tx HDCP Infomation
//--------------------------------------------------
#define GET_DP_TX_HDCP14_M0_0()                             (ScalerGetByte(PBB_43_M0_BYTE_0) ^ 0x9D)
#define GET_DP_TX_HDCP14_M0_1()                             (~(ScalerGetByte(PBB_42_M0_BYTE_1) ^ ScalerGetByte(PBB_43_M0_BYTE_0)))
#define GET_DP_TX_HDCP14_M0_2()                             (ScalerGetByte(PBB_41_M0_BYTE_2) ^ ScalerGetByte(PBB_42_M0_BYTE_1))
#define GET_DP_TX_HDCP14_M0_3()                             (ScalerGetByte(PBB_40_M0_BYTE_3) ^ ScalerGetByte(PBB_41_M0_BYTE_2))
#define GET_DP_TX_HDCP14_M0_4()                             (ScalerGetByte(PBB_3F_M0_BYTE_4) ^ ScalerGetByte(PBB_40_M0_BYTE_3))
#define GET_DP_TX_HDCP14_M0_5()                             (~(ScalerGetByte(PBB_3E_M0_BYTE_5) ^ ScalerGetByte(PBB_3F_M0_BYTE_4)))
#define GET_DP_TX_HDCP14_M0_6()                             (~(ScalerGetByte(PBB_3D_M0_BYTE_6) ^ ScalerGetByte(PBB_3E_M0_BYTE_5)))
#define GET_DP_TX_HDCP14_M0_7()                             (~(ScalerGetByte(PBB_3C_M0_BYTE_7) ^ ScalerGetByte(PBB_3D_M0_BYTE_6)))

#define GET_DP_TX_HDCP_DOWNSTREAM_EVENT()                   (g_stDpHdcp14TxAuthInfo.ucAuthDownstreamEvent)
#define SET_DP_TX_HDCP_DOWNSTREAM_EVENT(x)                  (g_stDpHdcp14TxAuthInfo.ucAuthDownstreamEvent = (x))
#define CLR_DP_TX_HDCP_DOWNSTREAM_EVENT()                   (g_stDpHdcp14TxAuthInfo.ucAuthDownstreamEvent = _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_NONE)

#define GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED()               (g_stDpHdcp14TxAuthInfo.b1IsHDCPSupported)
#define SET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED()               (g_stDpHdcp14TxAuthInfo.b1IsHDCPSupported = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED()               (g_stDpHdcp14TxAuthInfo.b1IsHDCPSupported = _FALSE)

#define GET_DP_TX_HDCP_DOWNSTREAM_REPEATER()                (g_stDpHdcp14TxAuthInfo.b1IsDownstreamRepeater)
#define SET_DP_TX_HDCP_DOWNSTREAM_REPEATER()                (g_stDpHdcp14TxAuthInfo.b1IsDownstreamRepeater = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER()                (g_stDpHdcp14TxAuthInfo.b1IsDownstreamRepeater = _FALSE)

#define GET_DP_TX_HDCP_AUTH_STATE()                         (g_stDpHdcp14TxAuthInfo.b4AuthState)
#define SET_DP_TX_HDCP_AUTH_STATE(x)                        (g_stDpHdcp14TxAuthInfo.b4AuthState = (x))

#define GET_DP_TX_HDCP_AUTH_STATE_CHANGE()                  (g_stDpHdcp14TxAuthInfo.b1AuthStateChange)
#define SET_DP_TX_HDCP_AUTH_STATE_CHANGE()                  (g_stDpHdcp14TxAuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_TX_HDCP_AUTH_STATE_CHANGE()                  (g_stDpHdcp14TxAuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT()            (g_stDpHdcp14TxAuthInfo.ucBInfoDevice & 0x7F)
#define GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_MAX()        (bit)(g_stDpHdcp14TxAuthInfo.ucBInfoDevice & _BIT7)

#define GET_DP_TX_HDCP_DOWNSTREAM_DEPTH()                   (g_stDpHdcp14TxAuthInfo.ucBInfoDepth & 0x07)
#define GET_DP_TX_HDCP_DOWNSTREAM_DEPTH_MAX()               (bit)(g_stDpHdcp14TxAuthInfo.ucBInfoDepth & _BIT3)

#define GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE()            (g_stDpHdcp14TxAuthInfo.ucBInfoDevice)
#define SET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE(x)           (g_stDpHdcp14TxAuthInfo.ucBInfoDevice = (x))
#define CLR_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE()            (g_stDpHdcp14TxAuthInfo.ucBInfoDevice = 0x00)

#define GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH()             (g_stDpHdcp14TxAuthInfo.ucBInfoDepth)
#define SET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH(x)            (g_stDpHdcp14TxAuthInfo.ucBInfoDepth = (x))
#define CLR_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH()             (g_stDpHdcp14TxAuthInfo.ucBInfoDepth = 0x00)

#define GET_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT()              (g_stDpHdcp14TxAuthInfo.b1R0Timeout)
#define SET_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT()              (g_stDpHdcp14TxAuthInfo.b1R0Timeout = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT()              (g_stDpHdcp14TxAuthInfo.b1R0Timeout = _FALSE)

#define GET_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT()         (g_stDpHdcp14TxAuthInfo.b1VReadyTimeout)
#define SET_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT()         (g_stDpHdcp14TxAuthInfo.b1VReadyTimeout = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT()         (g_stDpHdcp14TxAuthInfo.b1VReadyTimeout = _FALSE)

#define GET_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY()         (g_stDpHdcp14TxAuthInfo.b1PollingVReady)
#define SET_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY()         (g_stDpHdcp14TxAuthInfo.b1PollingVReady = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY()         (g_stDpHdcp14TxAuthInfo.b1PollingVReady = _FALSE)

#define GET_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT()             (g_stDpHdcp14TxAuthInfo.b1VReadyBit)
#define SET_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT()             (g_stDpHdcp14TxAuthInfo.b1VReadyBit = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT()             (g_stDpHdcp14TxAuthInfo.b1VReadyBit = _FALSE)

#define GET_DP_TX_HDCP_AUTH_START()                         (g_stDpHdcp14TxAuthInfo.b1AuthStart)
#define SET_DP_TX_HDCP_AUTH_START()                         (g_stDpHdcp14TxAuthInfo.b1AuthStart = _TRUE)
#define CLR_DP_TX_HDCP_AUTH_START()                         (g_stDpHdcp14TxAuthInfo.b1AuthStart = _FALSE)

#define GET_DP_TX_HDCP_AUTH_HOLD()                          (g_stDpHdcp14TxAuthInfo.b1AuthHold)
#define SET_DP_TX_HDCP_AUTH_HOLD()                          (g_stDpHdcp14TxAuthInfo.b1AuthHold = _TRUE)
#define CLR_DP_TX_HDCP_AUTH_HOLD()                          (g_stDpHdcp14TxAuthInfo.b1AuthHold = _FALSE)

#define GET_DP_TX_HDCP_KSV_FIFO_MAX()                       (sizeof(g_pucDpMacTxHdcpKsvFifo))

#define GET_DP_TX_HDCP_ECF_CHANGE()                         (g_ucDpHdcp14TxECFChange)
#define SET_DP_TX_HDCP_ECF_CHANGE()                         (g_ucDpHdcp14TxECFChange = _TRUE)
#define CLR_DP_TX_HDCP_ECF_CHANGE()                         (g_ucDpHdcp14TxECFChange = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
//HDCP IRQ Type
//--------------------------------------------------
typedef enum
{
    _DP_TX_IRQ_HDCP_NONE = 0,
    _DP_TX_IRQ_HDCP_V_READY = _BIT0,
    _DP_TX_IRQ_HDCP_R0_AVAILABLE = _BIT1,
    _DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL = _BIT2,
    _DP_TX_IRQ_HDCP_REAUTH_REQUEST = _BIT3,
} EnumDPTxTRQEventHDCPType;

//--------------------------------------------------
//HDCP RX Authentication Downstream Event
//--------------------------------------------------
typedef enum
{
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_NONE = 0,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_LINK_INTEGRITY_FAIL,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_MSG_QUERY_REAUTH,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PLUG_CHANGED,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX,
} EnumDPTxHDCPDownstreamAuthStatus;

//--------------------------------------------------
// HDCP Auth State
//--------------------------------------------------
typedef enum
{
    _DP_TX_HDCP_STATE_IDLE = 0,
    _DP_TX_HDCP_STATE_AUTH_1,
    _DP_TX_HDCP_STATE_AUTH_1_COMPARE_R0,
    _DP_TX_HDCP_STATE_AUTH_2,
    _DP_TX_HDCP_STATE_AUTH_PASS,
} EnumDPTxHDCPAuthState;

typedef struct
{
    EnumDPTxHDCPAuthState b4AuthState : 4;
    BYTE b1AuthStateChange : 1;
    BYTE b1IsHDCPSupported : 1;
    BYTE b1IsDownstreamRepeater : 1;
    BYTE b1R0Timeout : 1;
//------------------------------------
    BYTE b1VReadyTimeout : 1;
    BYTE b1PollingVReady : 1;
    BYTE b1VReadyBit : 1;
    BYTE b1AuthStart : 1;
    BYTE b1AuthHold : 1;
    BYTE ucAuthDownstreamEvent;
    BYTE ucBInfoDevice;
    BYTE ucBInfoDepth;
} StructDPTxHDCPAuthInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDPTxHDCPAuthInfo g_stDpHdcp14TxAuthInfo;
extern BYTE g_pucDpHdcp14TxKsvBackup[5];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpHdcp14TxHandler(void);
extern void ScalerDpHdcp14TxCheckDownstreamCapability(void);
extern void ScalerDpHdcp14TxAuth2ShaRun(bit bIsFirst);
extern void ScalerDpHdcp14TxChangeAuthState(EnumDPTxHDCPAuthState enumHDCPAuthState);
extern void ScalerDpHdcp14TxTimeoutToReadR0Event(void);
extern void ScalerDpHdcp14TxTimeoutForVReadyEvent(void);
extern void ScalerDpHdcp14TxPollingVReadyEvent(void);
extern void ScalerDpHdcp14TxEncryptSignalProc(bit bEnable);
extern void ScalerDpHdcp14TxResetInfo(void);

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpHdcp14TxSetECFProc(void);
#endif
extern void ScalerDpHdcp14TxResetKsvBackup(void);
extern bit ScalerDpHdcp14TxDownstreamBksvChange(void);

#endif // End of #if(_DP_TX_SUPPORT == _ON)

