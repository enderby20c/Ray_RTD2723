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
// ID Code      : ScalerHdcp2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDCP_2_2_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_HDCP22_AUTHENTICATION_ACTIVE()                          (bit)(g_ucHdcp2AuthActive)

//--------------------------------------------------
// Definitions of HDCP 2.2 Write & Read Message ID
//--------------------------------------------------
#define _HDCP22_NONE                                                0x00
#define _HDCP22_AKE_INIT                                            0x02
#define _HDCP22_AKE_SEND_CERT                                       0x03
#define _HDCP22_AKE_NO_STORED_KM                                    0x04
#define _HDCP22_AKE_STORED_KM                                       0x05
#define _HDCP22_AKE_SEND_H_PRIME                                    0x07
#define _HDCP22_AKE_SEND_PAIRING_INFO                               0x08
#define _HDCP22_LC_INIT                                             0x09
#define _HDCP22_LC_SEND_L_PRIME                                     0x0A
#define _HDCP22_SKE_SEND_EKS                                        0x0B
#define _HDCP22_REPEATERAUTH_SEND_RECID_LIST                        0x0C
#define _HDCP22_REPEATERAUTH_SEND_ACK                               0x0F
#define _HDCP22_REPEATERAUTH_STREAM_MANAGE                          0x10
#define _HDCP22_REPEATERAUTH_STREAM_READY                           0x11
#define _HDCP22_SKE_TYPE_VALUE                                      0x12

//--------------------------------------------------
// Definitions of HDCP 2.2 Online AES Page
//--------------------------------------------------
#define SET_HDCP22_ONLINE_AES_PAGEB_128B132B(x, y)\
{\
    memcpy((volatile BYTE xdata *)PC_18_HDCP_AES_CIPHER_KEY_15, (x), 16);\
    memcpy((volatile BYTE xdata *)PC_08_RIV0, (y), 8);\
}

#define SET_HDCP22_ONLINE_AES_PAGEB_8B10B(x, y)\
{\
    memcpy((volatile BYTE xdata *)PB_81_HDCP_AES_CIPHER_KEY_15, (x), 16);\
    memcpy((volatile BYTE xdata *)PB_55_RIV0, (y), 8);\
}

#if(_HDMI_FRL_MAC_RX3_SUPPORT == _ON)
#define SET_HDCP22_ONLINE_AES_PAGE2E(x, y)\
{\
    memcpy((volatile BYTE xdata *)((ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == 0x00) ? (P2E_00_HDCP_AES_CIPHER_KEY_15) : (P2E_50_HDCP_AES_CIPHER_KEY_1_15)), (x), 16);\
    memcpy((volatile BYTE xdata *)((ScalerGetBit(P67_00_HDMI_TOP_0, _BIT6) == 0x00) ? (P2E_14_HDMI20_RIV0) : (P2E_64_HDMI21_RIV0)), (y), 8);\
}
#else
#define SET_HDCP22_ONLINE_AES_PAGE2E(x, y)\
{\
    memcpy((volatile BYTE xdata *)P2E_00_HDCP_AES_CIPHER_KEY_15, (x), 16);\
    memcpy((volatile BYTE xdata *)P2E_14_HDMI20_RIV0, (y), 8);\
}
#endif

#if(_HDMI_FRL_MAC_RX4_SUPPORT == _ON)
#define SET_HDCP22_ONLINE_AES_PAGE6D(x, y)\
{\
    memcpy((volatile BYTE xdata *)((ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == 0x00) ? (P6D_00_HDCP_AES_CIPHER_KEY_15) : (P6D_50_HDCP_AES_CIPHER_KEY_1_15)), (x), 16);\
    memcpy((volatile BYTE xdata *)((ScalerGetBit(P1E_00_HDMI_TOP_0, _BIT6) == 0x00) ? (P6D_14_HDMI20_RIV0) : (P6D_64_HDMI21_RIV0)), (y), 8);\
}
#else
#define SET_HDCP22_ONLINE_AES_PAGE6D(x, y)\
{\
    memcpy((volatile BYTE xdata *)P6D_00_HDCP_AES_CIPHER_KEY_15, (x), 16);\
    memcpy((volatile BYTE xdata *)P6D_14_HDMI20_RIV0, (y), 8);\
}
#endif

#define SET_HDCP22_RX3_ONLINE_AES(x, y)                             {SET_HDCP22_ONLINE_AES_PAGE2E((x), (y))}
#define SET_HDCP22_RX4_ONLINE_AES(x, y)                             {SET_HDCP22_ONLINE_AES_PAGE6D((x), (y))}

#if(_HW_HDCP_SHA_SRAM_WRITE_DONE_FUNCTION_SUPPORT == _ON)
#define SET_HDCP22_RANDOM_GENERATOR_DISABLE()\
{\
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);\
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT3 | _BIT0), 0x00);\
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);\
}

#define SET_HDCP22_RANDOM_GENERATOR_DISABLE_EXINT()\
{\
    ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);\
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT3 | _BIT0), 0x00);\
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT3 | _BIT0), _BIT3);\
}
#else
#define SET_HDCP22_RANDOM_GENERATOR_DISABLE()\
{\
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);\
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT3 | _BIT0), 0x00);\
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT3 | _BIT0), _BIT3);\
}

#define SET_HDCP22_RANDOM_GENERATOR_DISABLE_EXINT()\
{\
    ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);\
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT3 | _BIT0), 0x00);\
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT3 | _BIT0), _BIT3);\
}
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDCP 2.2 Authentication State
//--------------------------------------------------
typedef enum
{
    _HDCP_2_2_STATE_UNAUTHENTICATED = 0,
    _HDCP_2_2_STATE_COMPUTE_KM,
    _HDCP_2_2_STATE_COMPUTE_L_PRIME,
    _HDCP_2_2_STATE_COMPUTE_KS,
    _HDCP_2_2_STATE_AUTHENTICATED,
    _HDCP_2_2_STATE_WAIT_FOR_DOWNSTREAM,
    _HDCP_2_2_STATE_ASS_RECEIVER_ID_LIST,
    _HDCP_2_2_STATE_VERIFY_RECEIVER_ID_LIST,
    _HDCP_2_2_STATE_CONTENT_STREAM_MANAGEMENT,
} EnumHdcp2AuthState;

//--------------------------------------------------
// Definitions of HDCP 2.2 D-KEY No.
//--------------------------------------------------
typedef enum
{
    _HDCP_2_2_DKEY_0 = 0,
    _HDCP_2_2_DKEY_1,
    _HDCP_2_2_DKEY_2,
} EnumHdcp2DKey;

//--------------------------------------------------
// Struct for RX HDCP Authentication
//--------------------------------------------------
typedef struct
{
    EnumHdcp2AuthState b4AuthState : 4;
} StructHdcp2HDCPAuthInfo;

typedef struct
{
    BYTE pucHdcp2Certrx[522];
    BYTE pucHdcp2DKey[128];
    BYTE pucHdcp2Rrmodn[128];
    BYTE pucHdcp2Lc[16];
    BYTE pucHdcp2Npinv[4];
} StructHdcp2DownLoadKeyType;

//--------------------------------------------------
// Struct of DP Rx0/Rx1 interlace status
//--------------------------------------------------
typedef struct
{
    EnumDpHdcp2RxRepeaterAuthState b4AuthState : 4;
    BYTE b1AuthStateChange : 1;
    BYTE b1AuthRepeaterProcTimeout : 1;
    BYTE ucAuthUpstreamEvent;
    BYTE b1AuthCpIrqTimer : 1;
    BYTE b1AuthHdcp2ContentStreamManage : 1;
    BYTE b1AuthRepeaterAuth1Start : 1;
    BYTE b1AuthRepeaterAuth2Start : 1;
    BYTE b1AuthRepeaterSelfReAuth : 1;
    BYTE ucAuthLongHPDEvent;
} StructDpHdcp2RxAuthInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//----------------------------------------------------------------------------
// Rx Key = 1118 Bytes
//----------------------------------------------------------------------------
extern StructHdcp2DownLoadKeyType g_stHdcp2RxDownLoadKeyType;

//----------------------------------------------------------------------------
// Global Variables (XDATA) for All Interface Shared
//----------------------------------------------------------------------------
extern volatile BYTE g_ucHdcp2AuthActive;

extern BYTE g_pucHdcp2HmacSha256Input[64];
extern BYTE g_pucHdcp2HmacSha256CipherInput[64];

extern BYTE g_pucHdcp2Sha256[32];

extern BYTE g_pucHdcp2BackUp[4];

extern BYTE g_pucHdcp2M[16];
extern BYTE g_pucHdcp2Kh[16];
extern BYTE g_pucHdcp2EkhKm[16];
extern BYTE g_pucHdcp2Ks[16];
extern BYTE g_pucHdcp2EDkeyKs[16];
extern BYTE g_pucHdcp2Riv[8];

extern BYTE g_pucHdcp2InputCipher[16];
extern BYTE g_pucHdcp2AesInput[16];
extern BYTE g_pucHdcp2AesCipherInput[16];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerHdcp2DkeyCalculate_EXINT0(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn);
extern BYTE ScalerHdcp2HPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps);
extern void ScalerHdcp2Initial(void);
extern BYTE ScalerHdcp2LPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn);
extern BYTE ScalerHdcp2RsaAvailable_EXINT0(void);
extern void ScalerHdcp2RxAesOfflineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray);
extern void ScalerHdcp2RxGenRrx_EXINT0(BYTE *pucInputArray);
extern BYTE ScalerHdcp2RxHmacSha256Calculate_EXINT0(BYTE *pucInputArray1, BYTE *pucInputArray2);
extern bit ScalerHdcp2RxSha256Calculate(BYTE *pucInputArray, BYTE ucCalCount);
extern BYTE ScalerHdcp2RxSha256Calculate_EXINT0(BYTE *pucInputArray, BYTE ucCalCount);
extern void ScalerHdcp2RxAesOfflineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray);
extern void ScalerHdcp2RxRsaWriteData(void);
extern void ScalerHdcp2RxRsaReadData(void);
extern void ScalerHdcp2RxShaWriteData(void);
#if(_HW_HDCP_SHA384_AES192_AES256_FUNCTION_SUPPORT == _ON)
extern bit ScalerHdcp2RxSha384Calculate(BYTE *pucInputArray, BYTE ucCalCount);
extern void ScalerHdcp2RxAes192OfflineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray);
extern void ScalerHdcp2RxAes256OfflineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray);
#endif
extern void ScalerHdcp2Proc1(BYTE *pucData1, BYTE *pucData2);
extern void ScalerHdcp2Proc1_EXINT0(BYTE *pucData1, BYTE *pucData2);
extern void ScalerHdcp2Proc2(BYTE *pucData1, BYTE *pucData2);
extern void ScalerHdcp2Proc2_EXINT0(BYTE *pucData1, BYTE *pucData2);
extern void ScalerHdcp2Proc3(BYTE *pucData);
extern void ScalerHdcp2Proc4_EXINT0(BYTE *pucData);

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern bit ScalerHdcp2MprimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucStreamIdType, DWORD ulSeqNumM, WORD usK);
extern bit ScalerHdcp2VprimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucReceiverIdList, BYTE *pucRxinfo, BYTE *pucSeqNumV);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void ScalerHdcp2DkeyCalculate(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn);
extern bit ScalerHdcp2HPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps);
extern bit ScalerHdcp2RxHmacSha256Calculate(BYTE *pucInputArray1, BYTE *pucInputArray2);
extern bit ScalerHdcp2RxRsaCalculate(BYTE *pucEkpubKmArray);
extern bit ScalerHdcp2RxRsaOaepCalculate(BYTE *pucKmArray);

#if(_DP_MST_SUPPORT == _ON)
extern bit ScalerHdcp2RepeaterLPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucInputArray);
#endif

#endif

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern bit ScalerHdcp2LPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
extern void ScalerHdcp2ReAuthEvent(EnumScalerTimerEventID enumEventID);
extern void ScalerHdcp2RxRsaCal_EXINT0(BYTE *pucEkpubKmArray);
extern BYTE ScalerHdcp2RxRsaOaepCalculate_EXINT0(BYTE *pucKmArray);
#endif

extern BYTE ScalerHdcp2RsaAvailable_WDINT(void);
extern BYTE ScalerHdcp2RxHmacSha256Calculate_WDINT(BYTE *pucInputArray1, BYTE *pucInputArray2);
extern BYTE ScalerHdcp2RxSha256Calculate_WDINT(BYTE *pucInputArray, BYTE ucCalCount);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
extern BYTE ScalerHdcp2RxRsaOaepCalculate_WDINT(BYTE *pucKmArray);
extern void ScalerHdcp2RxRsaCal_WDINT(BYTE *pucEkpubKmArray);
#endif

extern void ScalerHdcp2DkeyCalculate_WDINT(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn);
extern void ScalerHdcp2RxAesOfflineCtrl_WDINT(BYTE *pucInputArray, BYTE *pucCipherArray);
extern BYTE ScalerHdcp2HPrimeCalculate_WDINT(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps);

extern void ScalerHdcp2Proc1_WDINT(BYTE *pucData1, BYTE *pucData2);
extern void ScalerHdcp2Proc2_WDINT(BYTE *pucData1, BYTE *pucData2);

#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

