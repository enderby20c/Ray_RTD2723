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
// ID Code      : ScalerFwUpdateInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _FW_UPDATE_SLAVE_ADDRESS                 0x3A
#define _FW_UPDATE_BUF_LEN                       (_HW_DDCCI_BUF_SIZE + 1)
#define _SCALER_FW_UPDATE_CMD                    0x31
#define _FW_UPDATE_BACKGROUND_SUB_OP_CODE        0x02
#define _FW_UPDATE_FOREGROUND_SUB_OP_CODE        0x03

#define _FW_UPDATE_RESULT_BUSY                   0xBB

#define _FW_UPDATE_RESULT_IDLE                   0x10
#define _FW_UPDATE_RESULT_SUCCESS                0x01
#define _FW_UPDATE_RESULT_FAIL                   0x02
#define _FW_UPDATE_COMMAND_ERROR                 0x03
#define _FW_UPDATE_RESULT_IDLE_AND_SUCCESS       (_FW_UPDATE_RESULT_IDLE | _FW_UPDATE_RESULT_SUCCESS)
#define _FW_UPDATE_RESULT_IDLE_AND_FAIL          (_FW_UPDATE_RESULT_IDLE | _FW_UPDATE_RESULT_FAIL)
#define _FW_UPDATE_RESULT_COMMAND_ERROR          (_FW_UPDATE_RESULT_IDLE | _FW_UPDATE_COMMAND_ERROR)

#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072))
#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048)
#define _FW_UPDATE_RTK_SIGATURE_RSA_TYPE         _DIGITAL_SIGNATURE_RSA_2048
#elif(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072)
#define _FW_UPDATE_RTK_SIGATURE_RSA_TYPE         _DIGITAL_SIGNATURE_RSA_3072
#endif

#define _FW_UPDATE_RSA_SIGNATURE_SIZE            (_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8)
#define _FW_UPDATE_RSA_RESULT_SIZE               (_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8)

#define _FW_UPDATE_RSA_KEY_NKEY_SIZE             (_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8)
#define _FW_UPDATE_RSA_KEY_RRMODN_SIZE           (_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8)
#define _FW_UPDATE_RSA_KEY_NPINV_SIZE            4
#define _FW_UPDATE_RSA_KEY_EXORKEY_SIZE          (_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8)

#define _FW_UPDATE_RSA_SIGNATURE_OFFESET         0
#define _FW_UPDATE_PUBLIC_KEY_OFFESET            ((_FW_UPDATE_RSA_SIGNATURE_OFFESET) + (_FW_UPDATE_RSA_SIGNATURE_SIZE))
#define _FW_UPDATE_RSA_KEY_NKEY_OFFSET           _FW_UPDATE_PUBLIC_KEY_OFFESET
#define _FW_UPDATE_RSA_KEY_RRMODN_OFFSET         (_FW_UPDATE_RSA_KEY_NKEY_OFFSET + _FW_UPDATE_RSA_KEY_NKEY_SIZE)
#define _FW_UPDATE_RSA_KEY_NPINV_OFFSET          (_FW_UPDATE_RSA_KEY_RRMODN_OFFSET + _FW_UPDATE_RSA_KEY_RRMODN_SIZE)
#define _FW_UPDATE_RSA_KEY_EXORKEY_OFFSET        (_FW_UPDATE_RSA_KEY_NPINV_OFFSET + _FW_UPDATE_RSA_KEY_NPINV_SIZE)

#define _HDCP2_SIGNATURE_FILE_MAX_SIZE           _FW_UPDATE_RSA_SIGNATURE_SIZE
#define _HDCP2_NKEY_MAX_SIZE                     _FW_UPDATE_RSA_KEY_NKEY_SIZE
#define _HDCP2_RRMODN_MAX_SIZE                   _FW_UPDATE_RSA_KEY_RRMODN_SIZE
#define _HDCP2_NPINV_MAX_SIZE                    _FW_UPDATE_RSA_KEY_NPINV_SIZE
#define _HDCP2_EKEY_MAX_SIZE                     _FW_UPDATE_RSA_KEY_EXORKEY_SIZE
#endif

#define GET_FW_UPDATE_STATUS()                   (g_stFwUpdateScalerInfo.b1FwUpdateStatus)
#define SET_FW_UPDATE_STATUS()                   (g_stFwUpdateScalerInfo.b1FwUpdateStatus = _TRUE)
#define CLR_FW_UPDATE_STATUS()                   (g_stFwUpdateScalerInfo.b1FwUpdateStatus = _FALSE)

#define GET_FW_UPDATE_RUN_COMMAND()              (g_stFwUpdateScalerInfo.b1FwUpdateRunCommand)
#define SET_FW_UPDATE_RUN_COMMAND()              (g_stFwUpdateScalerInfo.b1FwUpdateRunCommand = _TRUE)
#define CLR_FW_UPDATE_RUN_COMMAND()              (g_stFwUpdateScalerInfo.b1FwUpdateRunCommand = _FALSE)

#define GET_FW_UPDATE_STATE_BACKUPDDCCIMODE()    (g_stFwUpdateScalerInfo.enumBackupDDCCIMode)
#define SET_FW_UPDATE_STATE_BACKUPDDCCIMODE(x)   (g_stFwUpdateScalerInfo.enumBackupDDCCIMode = (x))


#define GET_FW_UPDATE_MODE()                     (g_stFwUpdateScalerInfo.enumFwUpdateMode)
#define SET_FW_UPDATE_MODE(x)                    (g_stFwUpdateScalerInfo.enumFwUpdateMode = (x))
#define GET_ISP_XRAM_BUFFER(x)                   ((volatile BYTE xdata *)(_HW_XRAM_ISP_MAPPING_ADDR_START + (x)))



//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Enumerations of Fw Update Type
//--------------------------------------------------
typedef enum
{
    _INVALID_MODE = 0x00,
    _BACKGROUND_MODE,
    _FOREGROUND_MODE
} EnumFwUpdateMode;

//--------------------------------------------------
// Struct of FwUpdate
//--------------------------------------------------
typedef struct
{
    BYTE b1FwUpdateStatus : 1;
    BYTE b1FwUpdateRunCommand : 1;
    EnumDDCCIDebugMode enumBackupDDCCIMode;
    EnumFwUpdateMode enumFwUpdateMode;
} StructFwUpdateScalerInfo;

#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072))
//--------------------------------------------------
// Definitions of Signature Enum
//--------------------------------------------------
typedef enum
{
    _SIGN_FILE,
    _SIGN_NKEY,
    _SIGN_RRMODN,
    _SIGN_NPINV,
    _SIGN_EKEY,
} EnumSignKeyInfo;


typedef struct
{
    BYTE pucSignFile[_HDCP2_SIGNATURE_FILE_MAX_SIZE];
    BYTE pucSignNKey[_HDCP2_NKEY_MAX_SIZE];
    BYTE pucSignRrmodn[_HDCP2_RRMODN_MAX_SIZE];
    BYTE pucSignNpinv[_HDCP2_NPINV_MAX_SIZE];
    BYTE pucSignEKey[_HDCP2_EKEY_MAX_SIZE];
}StructSignKeyInfoType;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructFwUpdateScalerInfo g_stFwUpdateScalerInfo;
extern volatile BYTE g_pucFwUpdateRxBuf[_FW_UPDATE_BUF_LEN];
extern volatile WORD g_usFwUpdateDdcciCountEXINT;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerFwUpdateGetState(void);
extern void ScalerFwUpdateIntProc(void);
extern void ScalerFwUpdateSwitchState(EnumDDCCIDebugMode enumDdcciMode, BYTE ucOpCode, EnumDDCCIPort enumDdcciChannel);
extern void ScalerFwUpdateExit(void);
extern void ScalerFwUpdateSendReply(BYTE ucResult);
extern void ScalerFwUpdateSendData(BYTE ucLen, BYTE *pucData);
extern void ScalerFwUpdateInitRxBuf(void);
#if(((_FW_UPDATE_FOREGROUND_SUPPORT == _ON) && (_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESET)) || (_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON))
extern void ScalerFwUpdateReset(void);
#endif

#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072))
extern bit ScalerFwUpdateDeRsaCalculateforSign(StructSignKeyInfoType *pstHdcp2SignKeyInfoType, WORD usRsaMode, WORD usSigSize, WORD usRRModNSize, WORD usNKeySize, WORD usEKeySize, WORD usNPivSize);
extern bit ScalerFwUpdateSha256CalculateforSign(BYTE *pucInputArray, BYTE ucCalCount);
extern void ScalerFwUpdateDownLoadCalculateKeyforSign(StructSignKeyInfoType *pstHdcp2SignKeyInfoType, WORD usLength, BYTE *pucReadArray, EnumSignKeyInfo enumRSAType);
extern void ScalerFwUpdateReadoutHashforSign(BYTE *pucArray);
extern void ScalerFwUpdateReadoutRsaforSign(BYTE *pucArray, WORD usRsaSize);
extern void ScalerFwUpdateReleaseRsaforSign(void);
#endif

#if(((_MULTI_DISPLAY_MAX == 0x01) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)) || (_MULTI_DISPLAY_MAX > 0x01))
extern void ScalerFwUpdateDdcci0IntProc(void);
#endif
#if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
extern void ScalerFwUpdateDdcci1IntProc(void);
#endif
#if((_MULTI_DISPLAY_MAX >= 0x03) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
extern void ScalerFwUpdateDdcci2IntProc(void);
#endif
#if((_MULTI_DISPLAY_MAX >= 0x04) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
extern void ScalerFwUpdateDdcci3IntProc(void);
#endif
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
extern void ScalerFwUpdateDdcci4IntProc(void);
#endif

#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
extern void ScalerFwUpdateSpeedUpInital(DWORD ulStartAddr, WORD usPageLen, BYTE ucSlave, BYTE ucSub);
extern void ScalerFwUpdateMdofiySpeedUpIspLen(WORD usPageLen);
extern void ScalerFwUpdateDisableNormalDdcci(void);
extern void ScalerFwUpdateEnableSpeedUp(bit bEnable);
#endif
#endif
