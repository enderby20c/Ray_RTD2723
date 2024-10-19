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
// ID Code      : ScalerDpHdcp2TxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_HDCP2_RX_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_HDCP2_TX_IRQ_TYPE(x)                          (g_enumDpHdcp2TxCpirqType & (x))
#define SET_DP_HDCP2_TX_IRQ_TYPE(x)                          (g_enumDpHdcp2TxCpirqType |= (x))
#define CLR_DP_HDCP2_TX_IRQ_TYPE()                           (g_enumDpHdcp2TxCpirqType &= 0x00)
#define CLR_DP_HDCP2_TX_IRQ_TARGET_TYPE(x)                   (g_enumDpHdcp2TxCpirqType &= (EnumHdcp2TxCpirqType)~(x))

#define GET_DP_HDCP2_TX_AUTH_STATE()                         (g_stDpHdcp2TxAuthInfo.b4AuthState)
#define SET_DP_HDCP2_TX_AUTH_STATE(x)                        (g_stDpHdcp2TxAuthInfo.b4AuthState = (x))

#define GET_DP_HDCP2_TX_AUTH_STATE_CHANGE()                  (g_stDpHdcp2TxAuthInfo.b1AuthStateChange)
#define SET_DP_HDCP2_TX_AUTH_STATE_CHANGE()                  (g_stDpHdcp2TxAuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_HDCP2_TX_AUTH_STATE_CHANGE()                  (g_stDpHdcp2TxAuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_HDCP2_TX_VERSION_SUPPORTED()                  (g_stDpHdcp2TxAuthInfo.b1Hdcp2Version)
#define SET_DP_HDCP2_TX_VERSION_SUPPORTED()                  (g_stDpHdcp2TxAuthInfo.b1Hdcp2Version = _TRUE)
#define CLR_DP_HDCP2_TX_VERSION_SUPPORTED()                  (g_stDpHdcp2TxAuthInfo.b1Hdcp2Version = _FALSE)

#define GET_DP_HDCP2_TX_CAPABLE_SUPPORTED()                  (g_stDpHdcp2TxAuthInfo.b1Hdcp2Capable)
#define SET_DP_HDCP2_TX_CAPABLE_SUPPORTED()                  (g_stDpHdcp2TxAuthInfo.b1Hdcp2Capable = _TRUE)
#define CLR_DP_HDCP2_TX_CAPABLE_SUPPORTED()                  (g_stDpHdcp2TxAuthInfo.b1Hdcp2Capable = _FALSE)

#define GET_DP_HDCP2_TX_REPEATER_SUPPORTED()                 (g_stDpHdcp2TxAuthInfo.b1Hdcp2Repeater)
#define SET_DP_HDCP2_TX_REPEATER_SUPPORTED()                 (g_stDpHdcp2TxAuthInfo.b1Hdcp2Repeater = _TRUE)
#define CLR_DP_HDCP2_TX_REPEATER_SUPPORTED()                 (g_stDpHdcp2TxAuthInfo.b1Hdcp2Repeater = _FALSE)

#define GET_DP_HDCP2_TX_AUTH_START()                         (g_stDpHdcp2TxAuthInfo.b1AuthStart)
#define SET_DP_HDCP2_TX_AUTH_START()                         (g_stDpHdcp2TxAuthInfo.b1AuthStart = _TRUE)
#define CLR_DP_HDCP2_TX_AUTH_START()                         (g_stDpHdcp2TxAuthInfo.b1AuthStart = _FALSE)

#define GET_DP_HDCP2_TX_H_PRIME_TIMEOUT()                    (g_stDpHdcp2TxAuthInfo.b1HprimeTimeout)
#define SET_DP_HDCP2_TX_H_PRIME_TIMEOUT()                    (g_stDpHdcp2TxAuthInfo.b1HprimeTimeout = _TRUE)
#define CLR_DP_HDCP2_TX_H_PRIME_TIMEOUT()                    (g_stDpHdcp2TxAuthInfo.b1HprimeTimeout = _FALSE)

#define GET_DP_HDCP2_TX_AUTH_HOLD()                          (g_stDpHdcp2TxAuthInfo.b1AuthHold)
#define SET_DP_HDCP2_TX_AUTH_HOLD()                          (g_stDpHdcp2TxAuthInfo.b1AuthHold = _TRUE)
#define CLR_DP_HDCP2_TX_AUTH_HOLD()                          (g_stDpHdcp2TxAuthInfo.b1AuthHold = _FALSE)

#define GET_DP_HDCP2_TX_LC_RETRY_COUNTER()                   (g_stDpHdcp2TxAuthInfo.usLcRetryCounter)
#define ADD_DP_HDCP2_TX_LC_RETRY_COUNTER()                   (g_stDpHdcp2TxAuthInfo.usLcRetryCounter++)
#define CLR_DP_HDCP2_TX_LC_RETRY_COUNTER()                   (g_stDpHdcp2TxAuthInfo.usLcRetryCounter = 0)

#define GET_DP_HDCP2_TX_ENCRYPT_DATA_TIMEOUT()               (g_stDpHdcp2TxAuthInfo.b1EncryptDataTimeout)
#define SET_DP_HDCP2_TX_ENCRYPT_DATA_TIMEOUT()               (g_stDpHdcp2TxAuthInfo.b1EncryptDataTimeout = _TRUE)
#define CLR_DP_HDCP2_TX_ENCRYPT_DATA_TIMEOUT()               (g_stDpHdcp2TxAuthInfo.b1EncryptDataTimeout = _FALSE)

#define GET_DP_HDCP2_TX_V_READY_TIMEOUT()                    (g_stDpHdcp2TxAuthInfo.b1VReadyTimeout)
#define SET_DP_HDCP2_TX_V_READY_TIMEOUT()                    (g_stDpHdcp2TxAuthInfo.b1VReadyTimeout = _TRUE)
#define CLR_DP_HDCP2_TX_V_READY_TIMEOUT()                    (g_stDpHdcp2TxAuthInfo.b1VReadyTimeout = _FALSE)

#define GET_DP_HDCP2_TX_POLLING_V_READY()                    (g_stDpHdcp2TxAuthInfo.b1PollingVReady)
#define SET_DP_HDCP2_TX_POLLING_V_READY()                    (g_stDpHdcp2TxAuthInfo.b1PollingVReady = _TRUE)
#define CLR_DP_HDCP2_TX_POLLING_V_READY()                    (g_stDpHdcp2TxAuthInfo.b1PollingVReady = _FALSE)

#define GET_DP_HDCP2_TX_V_READY_BIT()                        (g_stDpHdcp2TxAuthInfo.b1VReadyBit)
#define SET_DP_HDCP2_TX_V_READY_BIT()                        (g_stDpHdcp2TxAuthInfo.b1VReadyBit = _TRUE)
#define CLR_DP_HDCP2_TX_V_READY_BIT()                        (g_stDpHdcp2TxAuthInfo.b1VReadyBit = _FALSE)

#define GET_DP_HDCP2_TX_SEQUENCE_NUMBER_V()                  (g_ulDpHdcp2TxSeqNumV)
#define SET_DP_HDCP2_TX_SEQUENCE_NUMBER_V(x)                 (g_ulDpHdcp2TxSeqNumV = (x))
#define CLR_DP_HDCP2_TX_SEQUENCE_NUMBER_V()                  (g_ulDpHdcp2TxSeqNumV = 0)

#define GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT()                (g_stDpHdcp2TxAuthInfo.b5RxInfoDevice)
#define SET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT(x)               (g_stDpHdcp2TxAuthInfo.b5RxInfoDevice = ((x) & 0x1F))

#define GET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT_EXCEED()         (g_stDpHdcp2TxAuthInfo.b1RxInfoDeviceExceed)
#define SET_DP_HDCP2_TX_RXINFO_DEVICE_COUNT_EXCEED()         (g_stDpHdcp2TxAuthInfo.b1RxInfoDeviceExceed = _TRUE)
#define CLR_DP_HDCP2_TX_RXINFO_DEVICE_COUNT_EXCEED()         (g_stDpHdcp2TxAuthInfo.b1RxInfoDeviceExceed = _FALSE)

#define GET_DP_HDCP2_TX_RXINFO_DEPTH()                       (g_stDpHdcp2TxAuthInfo.b3RxInfoDepth)
#define SET_DP_HDCP2_TX_RXINFO_DEPTH(x)                      (g_stDpHdcp2TxAuthInfo.b3RxInfoDepth = ((x) & 0x07))

#define GET_DP_HDCP2_TX_RXINFO_DEPTH_EXCEED()                (g_stDpHdcp2TxAuthInfo.b1RxInfoDepthExceed)
#define SET_DP_HDCP2_TX_RXINFO_DEPTH_EXCEED()                (g_stDpHdcp2TxAuthInfo.b1RxInfoDepthExceed = _TRUE)
#define CLR_DP_HDCP2_TX_RXINFO_DEPTH_EXCEED()                (g_stDpHdcp2TxAuthInfo.b1RxInfoDepthExceed = _FALSE)

#define GET_DP_HDCP2_TX_RXINFO_HDCP20_REPEATER_DOWNSTREAM()  (g_stDpHdcp2TxAuthInfo.b1Hdcp20RepeaterDownstream)
#define SET_DP_HDCP2_TX_RXINFO_HDCP20_REPEATER_DOWNSTREAM()  (g_stDpHdcp2TxAuthInfo.b1Hdcp20RepeaterDownstream = _TRUE)
#define CLR_DP_HDCP2_TX_RXINFO_HDCP20_REPEATER_DOWNSTREAM()  (g_stDpHdcp2TxAuthInfo.b1Hdcp20RepeaterDownstream = _FALSE)

#define GET_DP_HDCP2_TX_RXINFO_HDCP1_DOWNSTREAM()            (g_stDpHdcp2TxAuthInfo.b1Hdcp1DeviceDownstream)
#define SET_DP_HDCP2_TX_RXINFO_HDCP1_DOWNSTREAM()            (g_stDpHdcp2TxAuthInfo.b1Hdcp1DeviceDownstream = _TRUE)
#define CLR_DP_HDCP2_TX_RXINFO_HDCP1_DOWNSTREAM()            (g_stDpHdcp2TxAuthInfo.b1Hdcp1DeviceDownstream = _FALSE)

#define GET_DP_HDCP2_TX_DOWNSTREAM_EVENT()                   (g_stDpHdcp2TxAuthInfo.ucAuthDownstreamEvent)
#define SET_DP_HDCP2_TX_DOWNSTREAM_EVENT(x)                  (g_stDpHdcp2TxAuthInfo.ucAuthDownstreamEvent = (x))
#define CLR_DP_HDCP2_TX_DOWNSTREAM_EVENT()                   (g_stDpHdcp2TxAuthInfo.ucAuthDownstreamEvent = _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_NONE)

#define GET_DP_HDCP2_TX_CONTENT_STREAM_MANAGEMENT()          (g_stDpHdcp2TxAuthInfo.b1AuthContentStreamManage)
#define SET_DP_HDCP2_TX_CONTENT_STREAM_MANAGEMENT()          (g_stDpHdcp2TxAuthInfo.b1AuthContentStreamManage = _TRUE)
#define CLR_DP_HDCP2_TX_CONTENT_STREAM_MANAGEMENT()          (g_stDpHdcp2TxAuthInfo.b1AuthContentStreamManage = _FALSE)

#define GET_DP_HDCP2_TX_SEQUENCE_NUMBER_M()                  (g_ulDpHdcp2TxSeqNumM)
#define ADD_DP_HDCP2_TX_SEQUENCE_NUMBER_M()                  (g_ulDpHdcp2TxSeqNumM++)
#define CLR_DP_HDCP2_TX_SEQUENCE_NUMBER_M()                  (g_ulDpHdcp2TxSeqNumM = 0)

#define GET_DP_HDCP2_TX_M_PRIME_TIMEOUT()                    (g_stDpHdcp2TxAuthInfo.b1MprimeTimeout)
#define SET_DP_HDCP2_TX_M_PRIME_TIMEOUT()                    (g_stDpHdcp2TxAuthInfo.b1MprimeTimeout = _TRUE)
#define CLR_DP_HDCP2_TX_M_PRIME_TIMEOUT()                    (g_stDpHdcp2TxAuthInfo.b1MprimeTimeout = _FALSE)

#define GET_DP_HDCP2_TX_STOP_CONTENT_STREAM()                (g_stDpHdcp2TxAuthInfo.b1StopContentStream)
#define SET_DP_HDCP2_TX_STOP_CONTENT_STREAM()                (g_stDpHdcp2TxAuthInfo.b1StopContentStream = _TRUE)
#define CLR_DP_HDCP2_TX_STOP_CONTENT_STREAM()                (g_stDpHdcp2TxAuthInfo.b1StopContentStream = _FALSE)

#define GET_DP_HDCP2_TX_BACKUP_CONTENT_STREAM()              (g_stDpHdcp2TxAuthInfo.b1BackupContentStream)
#define SET_DP_HDCP2_TX_BACKUP_CONTENT_STREAM()              (g_stDpHdcp2TxAuthInfo.b1BackupContentStream = _TRUE)
#define CLR_DP_HDCP2_TX_BACKUP_CONTENT_STREAM()              (g_stDpHdcp2TxAuthInfo.b1BackupContentStream = _FALSE)

#define GET_DP_HDCP2_TX_PAIRING_INFO_READY()                 (g_stDpHdcp2TxAuthInfo.b1PairingInfoReady)
#define SET_DP_HDCP2_TX_PAIRING_INFO_READY()                 (g_stDpHdcp2TxAuthInfo.b1PairingInfoReady = _TRUE)
#define CLR_DP_HDCP2_TX_PAIRING_INFO_READY()                 (g_stDpHdcp2TxAuthInfo.b1PairingInfoReady = _FALSE)

#define GET_DP_HDCP2_TX_PAIRING_INFO_TIMEOUT()               (g_stDpHdcp2TxAuthInfo.b1PairingInfoTimeout)
#define SET_DP_HDCP2_TX_PAIRING_INFO_TIMEOUT()               (g_stDpHdcp2TxAuthInfo.b1PairingInfoTimeout = _TRUE)
#define CLR_DP_HDCP2_TX_PAIRING_INFO_TIMEOUT()               (g_stDpHdcp2TxAuthInfo.b1PairingInfoTimeout = _FALSE)

#define GET_DP_HDCP2_TX_DOWNSTREAM_PLUG_CHANGE()             (g_stDpHdcp2TxAuthInfo.b1DownstreamPlugChange)
#define SET_DP_HDCP2_TX_DOWNSTREAM_PLUG_CHANGE()             (g_stDpHdcp2TxAuthInfo.b1DownstreamPlugChange = _TRUE)
#define CLR_DP_HDCP2_TX_DOWNSTREAM_PLUG_CHANGE()             (g_stDpHdcp2TxAuthInfo.b1DownstreamPlugChange = _FALSE)

#define GET_DP_HDCP2_TX_RECEIVER_ID_LIST_MAX()               (sizeof(g_pucDpHdcp2TxReceiverIdList))

#define GET_DP_HDCP2_TX_ECF_CHANGE()                         (g_ucDpHdcp2TxECFChange)
#define SET_DP_HDCP2_TX_ECF_CHANGE()                         (g_ucDpHdcp2TxECFChange = _TRUE)
#define CLR_DP_HDCP2_TX_ECF_CHANGE()                         (g_ucDpHdcp2TxECFChange = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDCP 2.2 Tx Authentication State
//--------------------------------------------------
typedef enum
{
    _HDCP_2_2_TX_STATE_IDLE = 0,
    _HDCP_2_2_TX_STATE_AKE_INIT,
    _HDCP_2_2_TX_STATE_VERIFY_SIGNATURE,
    _HDCP_2_2_TX_STATE_NO_STORED_KM,
    _HDCP_2_2_TX_STATE_STORED_KM,
    _HDCP_2_2_TX_STATE_VERIFY_H_PRIME,
    _HDCP_2_2_TX_STATE_PAIRING,
    _HDCP_2_2_TX_STATE_LOCALITY_CHECK,
    _HDCP_2_2_TX_STATE_SKE,
    _HDCP_2_2_TX_STATE_VERIFY_V_PRIME,
    _HDCP_2_2_TX_STATE_AUTHEN_DONE,
} EnumHdcp2TxAuthState;

//--------------------------------------------------
// Definitions of HDCP2 Tx CPIRQ Type
//--------------------------------------------------
typedef enum
{
    _HDCP_2_2_TX_CPIRQ_NONE = 0,
    _HDCP_2_2_TX_CPIRQ_V_READY = _BIT0,
    _HDCP_2_2_TX_CPIRQ_H_PRIME_AVAILABLE = _BIT1,
    _HDCP_2_2_TX_CPIRQ_PAIRING_AVAILABLE = _BIT2,
    _HDCP_2_2_TX_CPIRQ_REAUTH_REQUEST = _BIT3,
    _HDCP_2_2_TX_CPIRQ_LINK_INTEGRITY_FAIL = _BIT4,
} EnumHdcp2TxCpirqType;

//--------------------------------------------------
//HDCP RX Authentication Downstream Event
//--------------------------------------------------
typedef enum
{
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_NONE = 0,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_LINK_INTEGRITY_FAIL,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_REAUTH,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_MSG_QUERY_REAUTH,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PLUG_CHANGED,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_PASS,
    _DP_TX_HDCP2_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_EXCEED,
} EnumDpTxHdcp2DownstreamAuthEvent;

//--------------------------------------------------
// Struct for RX HDCP Authentication
//--------------------------------------------------
typedef struct
{
    EnumHdcp2TxAuthState b4AuthState : 4;
    BYTE b1AuthStateChange : 1;
    BYTE b1Hdcp2Version : 1;
    BYTE b1Hdcp2Capable : 1;
    BYTE b1Hdcp2Repeater : 1;
    BYTE b1AuthStart : 1;
    BYTE b1HprimeTimeout : 1;
    BYTE b1AuthHold : 1;
    BYTE b1EncryptDataTimeout : 1;
    BYTE b1VReadyTimeout : 1;
    BYTE b1PollingVReady : 1;
    BYTE b1VReadyBit : 1;
    WORD usLcRetryCounter;
    BYTE b5RxInfoDevice : 5;
    BYTE b3RxInfoDepth : 3;
    BYTE ucAuthDownstreamEvent;
    BYTE b1RxInfoDeviceExceed : 1;
    BYTE b1RxInfoDepthExceed : 1;
    BYTE b1Hdcp20RepeaterDownstream : 1;
    BYTE b1Hdcp1DeviceDownstream : 1;
    BYTE b1AuthContentStreamManage : 1;
    BYTE b1MprimeTimeout : 1;
    BYTE b1StopContentStream : 1;
    BYTE b1BackupContentStream : 1;
    BYTE b1PairingInfoReady : 1;
    BYTE b1PairingInfoTimeout : 1;
    BYTE b1DownstreamPlugChange : 1;
} StructHdcp2TxAuthInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructHdcp2TxAuthInfo g_stDpHdcp2TxAuthInfo;
extern EnumHdcp2TxCpirqType g_enumDpHdcp2TxCpirqType;
extern BYTE g_pucDpHdcp2TxReceiverId[5];
extern BYTE g_pucDpHdcp2TxReceiverIdList[_DP_TX_HDCP2_DEVICE_COUNT_MAX * 5];

extern BYTE g_pucDpHdcp2TxdKey0[16];
extern BYTE g_pucDpHdcp2TxdKey1[16];
extern BYTE g_pucDpHdcp2TxDownStreamV[20];
extern BYTE g_pucDpHdcp2TxRiv[8];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpHdcp2TxHandler(void);
extern void ScalerDpHdcp2TxInitial(void);
extern void ScalerDpHdcp2TxCheckCapability(void);
extern void ScalerDpHdcp2TxTimeoutToReadCertificateEvent(void);
extern void ScalerDpHdcp2TxTimeoutToReadHPrimeEvent(void);
extern void ScalerDpHdcp2TxTimeoutToReadPairingInfoEvent(void);
extern void ScalerDpHdcp2TxTimeoutToEncyptDataEvent(void);
extern void ScalerDpHdcp2TxTimeoutForVReadyEvent(void);
extern void ScalerDpHdcp2TxPollingVReadyEvent(void);
extern void ScalerDpHdcp2TxTimeoutToReadMPrimeEvent(void);
extern void ScalerDpHdcp2TxOutputContentStreamHandler(void);
extern void ScalerDpHdcp2TxEncryptSignalProc(bit bEnable);
extern void ScalerDpHdcp2TxEncryptSignalProc_8b10b(bit bEnable);
extern bit ScalerDpHdcp2TxGetHdcpMode(void);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpHdcp2TxSetECFProc_8b10b(void);
#endif
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
extern void ScalerDpHdcp2TxEncryptSignalProc_128b132b(bit bEnable);
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpHdcp2TxSetECFProc_128b132b(void);
#endif
#endif

#endif // End of #if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

