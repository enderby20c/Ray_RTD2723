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
// ID Code      : UserCommonFwUpdateInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)

#define _FW_UPDATE_DONE_FLAG_REF_DATA                0x42, 0x47, 0xFF, 0xFF // (ASCII "BG")
#define _FW_UPDATE_DONE_FLAG_OFFSET_ADDR             8   // Done Flag 4 Byte, Start Flag 4 Byte

#define _FW_UPDATE_SUBADDRESS_INDEX                  0
#define _FW_UPDATE_DATA_START_INDEX                  1
#define _FW_UPDATE_OPCODE_INDEX                      1

#define GET_FW_UPDATE_VERIFY_ID_PASS()               (g_stFwUpdateUserCommonInfo.b1VerifyIDPass)
#define SET_FW_UPDATE_VERIFY_ID_PASS(x)              (g_stFwUpdateUserCommonInfo.b1VerifyIDPass = (x))

#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
typedef struct
{
    WORD usUserDataBank;
    BYTE ucUserDataSectorStart;
    BYTE ucUserDataSectorEnd;
    WORD usKeyStartAddress;
    WORD usKeyLen;
    WORD usFlagStartAddress;
    WORD usSignatureStartAddress;
    WORD usSignatureLen;
} StructFwUpdateUserDataInfo;

typedef struct
{
    BYTE b1IspStartFlag : 1;
    BYTE b1VerifyIDPass : 1;
    WORD usLastBank;
    BYTE ucLastSector;
    BYTE ucFwCrc;
    BYTE ucCalCrc;
    WORD usIspPageCount;
    DWORD ulFwStartAddress;
    DWORD ulFwEndAddress;
    DWORD ulFwCurrentAddress;
    DWORD ulReceivedKeyAndSigLen;
    WORD usIspKeyLen;
    WORD usIspSigLen;
    StructFwUpdateUserDataInfo stUserDataInfo;
} StructFwUpdateUserCommonInfo;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
extern StructFwUpdateUserCommonInfo g_stFwUpdateUserCommonInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
extern bit UserCommonFwUpdateWriteDoneFlag(void);
extern BYTE UserCommonFwUpdateCalculateCrc(WORD usLen, BYTE *pucData, BYTE ucCrc);
extern void UserCommonFwUpdateGetFwVersion(BYTE *pucVersionReply);
extern bit UserCommonFwUpdateGetFwStartAddressAndFlagAddress(DWORD *pulFwStartAddress, StructFwUpdateUserDataInfo *pstUserDataInfo);

#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072))
extern bit UserCommonFwUpdateRTKRsaSignatureVerify(void);
#endif
#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)
extern bit UserCommonFwUpdatePasswordVerify(WORD usBank, WORD usAddr);
#endif

#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
extern void UserCommonFwUpdateChangeBank(void);
#endif

#endif


