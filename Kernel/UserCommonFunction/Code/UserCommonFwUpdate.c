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
// ID Code      : UserCommonFwUpdate.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_FW_UPDATE__

#include "UserCommonInclude.h"
#include "FwUpdate/UserCommonFwUpdate.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if((_FW_UPDATE_PROCESS_SUPPORT == _ON) && (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD))
__attribute__((section(".used_table.tFwPassword")))
BYTE code tFwPassword[] =
{
    _FW_UPDATE_PASSWORD_DATA,
};
#endif


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
StructFwUpdateUserCommonInfo g_stFwUpdateUserCommonInfo =
{
    _FALSE,
    _FALSE,
    0xFF,
    0xFF,
    0x00,
    0x00,
    32,
    0xFFFFFF,
    0xFFFFFF,
    0xFFFFFF,
    0,
    0,
    0,
    {0xFF, 0xFF, 0xFF,   0xFFFF, 0, 0xFFFF, 0xFF, 0},
};
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  :  Fw Update Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateHandler(void)
{
#if(_FW_UPDATE_BACKGROUND_SUPPORT == _ON)
    if(UserCommonFwUpdateBackgroundHandler() == _TRUE)
    {
        return;
    }
#endif

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    if(UserCommonFwUpdateForegroundHandler() == _TRUE)
    {
        return;
    }
#endif
}

//--------------------------------------------------
// Description  : Fw Update Write Done Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateWriteDoneFlag(void)
{
#if(_DUAL_BANK_USER_FLAG_CUSTOMER_TYPE == _DUAL_BANK_KERNEL_TYPE)
    WORD usFlagDoneAddr = (WORD)g_stFwUpdateUserCommonInfo.stUserDataInfo.usFlagStartAddress;
    BYTE pucReadFlag[5] = {0};
    BYTE pucISPDoneFlagRef[5] = {_TAG_UPDATE_FW_PASS, _TAG_VERIFY_FW_NONE, _TAG_SWITCH_CODE_COMPLETE, _TAG_CAN_BE_EXECUTED, _TAG_COPY_FW_NONE};
    // Write Done Flag
    UserCommonFlashWrite(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usFlagDoneAddr, 5, pucISPDoneFlagRef);
    UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usFlagDoneAddr, 5, pucReadFlag);
    if(memcmp(pucISPDoneFlagRef, pucReadFlag, sizeof(pucISPDoneFlagRef)) != 0)
    {
        return _FALSE;
    }

    return _TRUE;
#else
    if(UserInterfaceDualBankFwUpdateWriteDoneFlag(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, g_stFwUpdateUserCommonInfo.stUserDataInfo.usFlagStartAddress) == _FWUPDATE_WRITE_FLAG_FAIL)
    {
        return _FALSE;
    }
    return _TRUE;
#endif
}

//--------------------------------------------------
// Description  : Fw Update Calculate Crc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonFwUpdateCalculateCrc(WORD usLen, BYTE *pucData, BYTE ucCrc)
{
    DWORD  ulIndex = 0;
    BYTE ucCrcTmp = ucCrc;
    while(usLen--)
    {
        ucCrcTmp ^= *pucData++;
        for(ulIndex = 8; ulIndex > 0; --ulIndex)
        {
            if(ucCrcTmp & 0x80)
            {
                ucCrcTmp = (ucCrcTmp << 1) ^ 0x07;
            }
            else
            {
                ucCrcTmp = (ucCrcTmp << 1);
            }
        }
    }

    return ucCrcTmp;
}

//---------------------------------------------------------
// Description  : Fw Update Get Active Fw Version
// Input Value  : None
// Output Value : None
//---------------------------------------------------------
void UserCommonFwUpdateGetFwVersion(BYTE *pucVersionReply)
{
    BYTE pucTmpData[6] = {0};
#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
    ScalerFwInfoGetCurrentVersion(pucTmpData);
#endif
    pucVersionReply[0] = _FW_UPDATE_RESULT_IDLE_AND_SUCCESS;
    pucVersionReply[1] = pucTmpData[0];
    pucVersionReply[2] = pucTmpData[1];
}

//---------------------------------------------------------------------------------
// Description  : Background Fw Update Get Program Fw Start Address and Flag Address
// Input Value  : pulFwStartAddress, pstUserDataInfo
// Output Value : None
//---------------------------------------------------------------------------------
bit UserCommonFwUpdateGetFwStartAddressAndFlagAddress(DWORD *pulFwStartAddress, StructFwUpdateUserDataInfo *pstUserDataInfo)
{
    WORD usCurBank = ScalerDualBankUserGetKCPUBankOffset();
    // if run User 1
    if((usCurBank >= _DUAL_BANK_USER_I_FW_BANK_START) && (usCurBank <= _DUAL_BANK_USER_I_FW_BANK_END))
    {
        *pulFwStartAddress = ((DWORD)_DUAL_BANK_USER_II_FW_BANK_START << 16) | 0x00;
        pstUserDataInfo->usUserDataBank = _DUAL_BANK_USER_II_USER_DATA_BANK_ADDR;
        pstUserDataInfo->ucUserDataSectorStart = _DUAL_BANK_USER_II_DATA_SECTOR_START;
        pstUserDataInfo->ucUserDataSectorEnd = _DUAL_BANK_USER_II_DATA_SECTOR_END;
        pstUserDataInfo->usFlagStartAddress = _DUAL_BANK_USER_II_FLAG_START_ADDR;
        pstUserDataInfo->usKeyStartAddress = _DUAL_BANK_USER_II_KEY_START_ADDR;
        pstUserDataInfo->usKeyLen = _DUAL_BANK_USER_KEY_LENGTH;
        pstUserDataInfo->usSignatureStartAddress = _DUAL_BANK_USER_II_SIGNATURE_START_ADDR;
        pstUserDataInfo->usSignatureLen = _DUAL_BANK_USER_SIGNATURE_LENGTH;
        return _TRUE;
    }
    else if((usCurBank >= _DUAL_BANK_USER_II_FW_BANK_START) && (usCurBank <= _DUAL_BANK_USER_II_FW_BANK_END))
    {
        *pulFwStartAddress = ((DWORD)_DUAL_BANK_USER_I_FW_BANK_START << 16) | 0x00;
        pstUserDataInfo->usUserDataBank = _DUAL_BANK_USER_I_USER_DATA_BANK_ADDR;
        pstUserDataInfo->ucUserDataSectorStart = _DUAL_BANK_USER_I_DATA_SECTOR_START;
        pstUserDataInfo->ucUserDataSectorEnd = _DUAL_BANK_USER_I_DATA_SECTOR_END;
        pstUserDataInfo->usFlagStartAddress = _DUAL_BANK_USER_I_FLAG_START_ADDR;
        pstUserDataInfo->usKeyStartAddress = _DUAL_BANK_USER_I_KEY_START_ADDR;
        pstUserDataInfo->usKeyLen = _DUAL_BANK_USER_KEY_LENGTH;
        pstUserDataInfo->usSignatureStartAddress = _DUAL_BANK_USER_I_SIGNATURE_START_ADDR;
        pstUserDataInfo->usSignatureLen = _DUAL_BANK_USER_SIGNATURE_LENGTH;
        return _TRUE;
    }
    else
    {
        *pulFwStartAddress = 0xFFFFFF;
        pstUserDataInfo->usUserDataBank = 0xFFFF;
        pstUserDataInfo->ucUserDataSectorStart = 0xFF;
        pstUserDataInfo->ucUserDataSectorEnd = 0xFF;
        pstUserDataInfo->usFlagStartAddress = 0xFFFF;
        pstUserDataInfo->usKeyStartAddress = 0xFFFF;
        pstUserDataInfo->usKeyLen = 0;
        pstUserDataInfo->usSignatureStartAddress = 0xFFFF;
        pstUserDataInfo->usSignatureLen = 0;
    }
    return _FALSE;
}

#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072))
//--------------------------------------------------
// Description  : Fw Update RTK RSA2048 Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateRTKRsaSignatureVerify(void)
{
    BYTE pucCurHash[_FW_UPDATE_SHA256_RESULT_SIZE] = {0};
    BYTE pucOrgHash[_FW_UPDATE_RSA_RESULT_SIZE] = {0};

    ScalerFwUpdateReleaseRsaforSign();

    // step 1: calculate fw bin data hash based on SHA-256
    if(UserCommonFwUpdateHwHashCalculateBasedSHA256(pucCurHash) == _FALSE)
    {
        return _FALSE;
    }

    // step 2: load signature and key, then calculate original hash based RSA-1024/2048/3072
    if(UserCommonFwUpdateRTKRsaCalculate(pucOrgHash) == _FALSE)
    {
        return _FALSE;
    }
    if(UserCommonFwUpdateCompareHashResult(pucCurHash, pucOrgHash) == _FALSE)
    {
        return _FALSE;
    }
    return _TRUE;
}
//--------------------------------------------------
// Description  : Fw Update RTK RSA2048 Load Key And Signautre
// Input Value  : pstHdcp2SignKeyInfoType
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateRTKRsaLoadKeyAndSignature(StructSignKeyInfoType *pstHdcp2SignKeyInfoType)
{
    BYTE pucTemp[_FW_UPDATE_RTK_SIGATURE_RSA_TYPE / 8] = {0};
    WORD usBank = (WORD)((g_stFwUpdateUserCommonInfo.ulFwStartAddress >> 16) + _DUAL_BANK_USER_FW_CODE_SIZE - 1);

#if(_DIGITAL_PORT_SUPPORT == _ON)
    ScalerSyncHdcpEnableDownLoadKey(_ENABLE);
#endif

    // load Signature file
    UserCommonFlashRead(usBank, (WORD)(_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS) + _FW_UPDATE_RSA_SIGNATURE_OFFESET, _FW_UPDATE_RSA_SIGNATURE_SIZE, pucTemp);
    ScalerFwUpdateDownLoadCalculateKeyforSign(pstHdcp2SignKeyInfoType, _FW_UPDATE_RSA_SIGNATURE_SIZE, pucTemp, _SIGN_FILE);

    // load N key
    UserCommonFlashRead(usBank, ((WORD)(_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS) + _FW_UPDATE_RSA_KEY_NKEY_OFFSET), _FW_UPDATE_RSA_KEY_NKEY_SIZE, pucTemp);
    ScalerFwUpdateDownLoadCalculateKeyforSign(pstHdcp2SignKeyInfoType, _FW_UPDATE_RSA_KEY_NKEY_SIZE, pucTemp, _SIGN_NKEY);

    // load RRMODN
    UserCommonFlashRead(usBank, ((WORD)(_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS) + _FW_UPDATE_RSA_KEY_RRMODN_OFFSET), _FW_UPDATE_RSA_KEY_RRMODN_SIZE, pucTemp);
    ScalerFwUpdateDownLoadCalculateKeyforSign(pstHdcp2SignKeyInfoType, _FW_UPDATE_RSA_KEY_RRMODN_SIZE, pucTemp, _SIGN_RRMODN);

    // load NPINV
    UserCommonFlashRead(usBank, ((WORD)(_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS) + _FW_UPDATE_RSA_KEY_NPINV_OFFSET), _FW_UPDATE_RSA_KEY_NPINV_SIZE, pucTemp);
    ScalerFwUpdateDownLoadCalculateKeyforSign(pstHdcp2SignKeyInfoType, _FW_UPDATE_RSA_KEY_NPINV_SIZE, pucTemp, _SIGN_NPINV);

    // load E key
    UserCommonFlashRead(usBank, ((WORD)(_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS) + _FW_UPDATE_RSA_KEY_EXORKEY_OFFSET), _FW_UPDATE_RSA_KEY_EXORKEY_SIZE, pucTemp);
    ScalerFwUpdateDownLoadCalculateKeyforSign(pstHdcp2SignKeyInfoType, _FW_UPDATE_RSA_KEY_EXORKEY_SIZE, pucTemp, _SIGN_EKEY);

    return _TRUE;
}
//--------------------------------------------------
// Description  : Fw Update RTK RSA2048 Caculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateRTKRsaCalculate(BYTE *pucResult)
{
    StructSignKeyInfoType stHdcp2SignKeyInfoType;
    UserCommonFwUpdateRTKRsaLoadKeyAndSignature(&stHdcp2SignKeyInfoType);
    if(ScalerFwUpdateDeRsaCalculateforSign(&stHdcp2SignKeyInfoType, _FW_UPDATE_RTK_SIGATURE_RSA_TYPE, _FW_UPDATE_RSA_SIGNATURE_SIZE, _FW_UPDATE_RSA_KEY_RRMODN_SIZE, _FW_UPDATE_RSA_KEY_NKEY_SIZE, _FW_UPDATE_RSA_KEY_EXORKEY_SIZE, _FW_UPDATE_RSA_KEY_NPINV_SIZE) == _FALSE)
    {
        return _FALSE;
    }
    ScalerFwUpdateReadoutRsaforSign(pucResult, _FW_UPDATE_RSA_RESULT_SIZE);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Fw Update Compare Hash Result
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateCompareHashResult(BYTE *pucCurHash, BYTE *pucOrgHash)
{
    WORD usIndex = 0;

    for(usIndex = 0; usIndex <= (_FW_UPDATE_RSA_RESULT_SIZE - _FW_UPDATE_SHA256_RESULT_SIZE); usIndex++)
    {
        if(memcmp(pucCurHash, &pucOrgHash[usIndex], _FW_UPDATE_SHA256_RESULT_SIZE) == 0)
        {
            DebugMessageSystem("signature verify success", 0);
            return _TRUE;
        }
    }

    DebugMessageSystem("signature verify fail", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Fw Update Hw hash Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateHwHashCalculateBasedSHA256(BYTE *pucResult)
{
    DWORD ulIndex = 0;
    DWORD ulFwAddr = g_stFwUpdateUserCommonInfo.ulFwStartAddress;
    DWORD ulFwLength = (DWORD)_DUAL_BANK_USER_FW_CODE_SIZE << 16;
    DWORD ulCount = ulFwLength / _FW_UPDATE_SHA256_ARRAY_SIZE;
    BYTE pucArray[_FW_UPDATE_SHA256_ARRAY_SIZE] = {0};
    WORD usBank = (WORD)((g_stFwUpdateUserCommonInfo.ulFwStartAddress >> 16) + _DUAL_BANK_USER_FW_CODE_SIZE - 1);
    WORD usAddr = 0;
    bit bReturn = _TRUE;
    DWORD ulRTKSignDataStartAddr = ((DWORD)usBank << 16) + ((DWORD)_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS);
    DWORD ulRTKSignDataDataEndAddr = ((DWORD)usBank << 16) + ((DWORD)_FW_UPDATE_SIGN_INFO_SECTOR_ADDRESS + _FLASH_PAGE_SIZE);

    DWORD ulUserDataStartAddr = ((DWORD)g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank << 16) + ((DWORD)g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataSectorStart << 12);
    DWORD ulUserDataEndAddr = ((DWORD)g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank << 16) + ((DWORD)(g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataSectorEnd + 1) << 12);

    for(ulIndex = 0; ulIndex < ulCount; ++ulIndex)
    {
        usBank = HIWORD(ulFwAddr);
        usAddr = LOWORD(ulFwAddr);

        if(((ulFwAddr >= ulUserDataStartAddr) && (ulFwAddr < ulUserDataEndAddr)) || ((ulFwAddr >= ulRTKSignDataStartAddr) && (ulFwAddr < ulRTKSignDataDataEndAddr)))
        {
            memset(pucArray, 0xFFU, sizeof(pucArray));
        }
        else
        {
            memset(pucArray, 0xFFU, sizeof(pucArray));
            UserCommonFlashRead(usBank, usAddr, _FW_UPDATE_SHA256_ARRAY_SIZE, pucArray);
        }
        if(ulIndex == 0)
        {
            bReturn = ScalerFwUpdateSha256CalculateforSign(pucArray, 0);
        }
        else
        {
            bReturn = ScalerFwUpdateSha256CalculateforSign(pucArray, 1);
        }

        if(!bReturn)
        {
            DebugMessageSystem("HASH error, fw addr:", ulFwAddr);
            return bReturn;
        }

        ulFwAddr += _FW_UPDATE_SHA256_ARRAY_SIZE;
    }

    // Hash last package

    memset(pucArray, 0, sizeof(pucArray));
    pucArray[0] = 0x80;
    pucArray[61] = (BYTE)(((8 * ulFwLength) >> 16) & 0xFF);
    pucArray[62] = (BYTE)(((8 * ulFwLength) >> 8) & 0xFF);
    pucArray[63] = (BYTE)((8 * ulFwLength) & 0xFF);

    bReturn = ScalerFwUpdateSha256CalculateforSign(pucArray, 1);
    if(!bReturn)
    {
        DebugMessageSystem("HASH error, last data", 0);
        return bReturn;
    }

    // read out hash result
    ScalerFwUpdateReadoutHashforSign(pucResult);

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Fw Update Start
// Input Value  : usIspPageLen, isp bytes count each time
//                  shoud <=256.
//                  bCanBankErase: can bank Erase or not
// Output Value : _FALSE: Fail, _TRUE:Success
//--------------------------------------------------
bit UserCommonFwUpdateStartProcess(WORD usIspPageLen, bit bBankErase)
{
    BYTE ucIndex = 0;
    WORD usStartBank = 0;

    if(_FLASH_PROGRAM_SIZE < usIspPageLen)
    {
        return _FALSE;
    }
    // Get Start Addrtess
    UserCommonFwUpdateGetFwStartAddressAndFlagAddress(&g_stFwUpdateUserCommonInfo.ulFwStartAddress, &g_stFwUpdateUserCommonInfo.stUserDataInfo);
    if(g_stFwUpdateUserCommonInfo.ulFwStartAddress == 0xFFFFFF)
    {
        return _FALSE;
    }
    g_stFwUpdateUserCommonInfo.usIspPageCount = usIspPageLen;
    g_stFwUpdateUserCommonInfo.b1IspStartFlag = _TRUE;
    g_stFwUpdateUserCommonInfo.ucCalCrc = 0;
    g_stFwUpdateUserCommonInfo.ucFwCrc = 0;
    g_stFwUpdateUserCommonInfo.usLastBank = 0xFFFF;
    g_stFwUpdateUserCommonInfo.ucLastSector = 0xFF;
    g_stFwUpdateUserCommonInfo.ulFwCurrentAddress = g_stFwUpdateUserCommonInfo.ulFwStartAddress;
    g_stFwUpdateUserCommonInfo.ulFwEndAddress = g_stFwUpdateUserCommonInfo.ulFwStartAddress + _DUAL_BANK_USER_FW_CODE_SIZE * 65536;
    g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen = 0;
    g_stFwUpdateUserCommonInfo.usIspKeyLen = 0;
    g_stFwUpdateUserCommonInfo.usIspSigLen = 0;

    // Clear Flag
    usStartBank = HIWORD(g_stFwUpdateUserCommonInfo.ulFwStartAddress);
    if((bBankErase == _TRUE) && (g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank >= usStartBank) && (g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank < (usStartBank + _DUAL_BANK_USER_FW_CODE_SIZE)))
    {
        ScalerFlashWREN(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, 0xFF);
        ScalerFlashEraseBank(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, _TRUE, _FALSE);
    }
    else
    {
        for(ucIndex = g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataSectorStart; ucIndex <= g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataSectorEnd; ucIndex++)
        {
            ScalerFlashErasePage(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, ucIndex, _TRUE, _TRUE);
        }
    }
    return _TRUE;
}

//--------------------------------------------------
// Description  : Fw Update  Check
// Input Value  : None
// Output Value : TRUE: Success, FALSE: Fail
//--------------------------------------------------
bit UserCommonFwUpdateCheckProcess(void)
{
#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)
    // Check Password
    WORD usBank = ((g_stFwUpdateUserCommonInfo.ulFwStartAddress >> 16) & 0xFF) + _FW_UPDATE_PASSWORD_BANK;
#endif

#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_NONE) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD))
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
    if(GET_FW_UPDATE_STATUS() == _TRUE)
    {
        BYTE ucLastCrcByte = 0xFF;
        WORD usCRCAddr = LOWORD(g_stFwUpdateUserCommonInfo.ulFwEndAddress - 1);

        ScalerMcuFlashCRCCal(g_stFwUpdateUserCommonInfo.ulFwStartAddress, g_stFwUpdateUserCommonInfo.ulFwEndAddress - 2, &g_stFwUpdateUserCommonInfo.ucCalCrc);
        g_stFwUpdateUserCommonInfo.ucCalCrc = UserCommonFwUpdateCalculateCrc(1, &ucLastCrcByte, g_stFwUpdateUserCommonInfo.ucCalCrc);
        UserCommonFlashRead(HIWORD((g_stFwUpdateUserCommonInfo.ulFwEndAddress - 1)), usCRCAddr, 1, &g_stFwUpdateUserCommonInfo.ucFwCrc);
    }
    else
#endif
    {
#if(_FW_UPDATE_CLAC_CRC_TYPE == _FW_UPDATE_HW_CLAC_CRC)
        ScalerMcuFlashCRCCal(g_stFwUpdateUserCommonInfo.ulFwStartAddress, g_stFwUpdateUserCommonInfo.ulFwEndAddress - 1, &g_stFwUpdateUserCommonInfo.ucCalCrc);
#endif
    }

    // Check CRC
    if(g_stFwUpdateUserCommonInfo.ucFwCrc != g_stFwUpdateUserCommonInfo.ucCalCrc)
    {
        return _FALSE;
    }
#endif

#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)
    // Check Password
    return UserCommonFwUpdatePasswordVerify(usBank, _FW_UPDATE_PASSWORD_ADDRESS);
#endif

#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072))
    // Check RTK RSA
    return UserCommonFwUpdateRTKRsaSignatureVerify();
#endif
    return _TRUE;
}

//--------------------------------------------------
// Description  : Background Fw Update Finish
// Input Value  : None
// Output Value : TRUE: Success, FALSE: Fail
//--------------------------------------------------
bit UserCommonFwUpdateFinishProcess(void)
{
    if(g_stFwUpdateUserCommonInfo.b1IspStartFlag == _FALSE)
    {
        return _FALSE;
    }
    if(UserCommonFwUpdateCheckProcess() == _FALSE)
    {
        return _FALSE;
    }
    else
    {
        if(UserCommonFwUpdateWriteDoneFlag() == _FALSE)
        {
            return _FALSE;
        }
    }
    g_stFwUpdateUserCommonInfo.b1IspStartFlag = _FALSE;
    g_stFwUpdateUserCommonInfo.ucCalCrc = 0;
    g_stFwUpdateUserCommonInfo.ucFwCrc = 0;
    g_stFwUpdateUserCommonInfo.usLastBank = 0xFFFF;
    g_stFwUpdateUserCommonInfo.ucLastSector = 0xFF;
    g_stFwUpdateUserCommonInfo.ulFwStartAddress = 0xFFFFFFFF;
    g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank = 0xFFFF;
    g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataSectorStart = 0xFF;
    g_stFwUpdateUserCommonInfo.stUserDataInfo.ucUserDataSectorEnd = 0xFF;
    g_stFwUpdateUserCommonInfo.stUserDataInfo.usFlagStartAddress = 0xFFFF;
    g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyStartAddress = 0xFFFF;
    g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyLen = 0;
    g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureStartAddress = 0xFFFF;
    g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureLen = 0;

    return _TRUE;
}

#if((_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON) || (_FW_UPDATE_FOREGROUND_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Background Fw Update Write Data
// Input Value  : pucBuf: Write Buff,
//                  usProgramLength : ISP Length
//                  bIspXramBuff: _TRUE: is Isp Xram Buffer
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateWriteDataProcess(BYTE *pucBuf, WORD usProgramLength, bit bIspXramBuff)
{
    WORD usIspLength = usProgramLength;
#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_NONE) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD))
#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
    WORD usBankCount = _DUAL_BANK_USER_FW_CODE_SIZE + 1;
#else
    WORD usBankCount = _DUAL_BANK_USER_FW_CODE_SIZE;
#endif
    BYTE xdata *pucIspXram = GET_ISP_XRAM_BUFFER(0);
#endif

    if(usProgramLength > g_stFwUpdateUserCommonInfo.usIspPageCount)
    {
        return _FALSE;
    }

    if(bIspXramBuff == _FALSE)
    {
        memcpy(GET_ISP_XRAM_BUFFER(0), pucBuf, usProgramLength);
    }

#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_NONE) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD))
    // Save Crc and fullfill last data 0xFF for CalulateCrc
    if((((DWORD)usBankCount * 65536) % g_stFwUpdateUserCommonInfo.usIspPageCount) == 0)
    {
        if((g_stFwUpdateUserCommonInfo.ulFwCurrentAddress + g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen) == (g_stFwUpdateUserCommonInfo.ulFwStartAddress + usBankCount * 65536 - g_stFwUpdateUserCommonInfo.usIspPageCount))
        {
            g_stFwUpdateUserCommonInfo.ucFwCrc = pucIspXram[g_stFwUpdateUserCommonInfo.usIspPageCount - 1];
            pucIspXram[g_stFwUpdateUserCommonInfo.usIspPageCount - 1] = 0xFF;
        }
    }
    else
    {
        if((g_stFwUpdateUserCommonInfo.ulFwCurrentAddress + g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen) == (g_stFwUpdateUserCommonInfo.ulFwStartAddress + usBankCount * 65536 - ((usBankCount * 65536) % g_stFwUpdateUserCommonInfo.usIspPageCount)))
        {
            // Last packet data
            usIspLength = usBankCount * 65536 % g_stFwUpdateUserCommonInfo.usIspPageCount;
            g_stFwUpdateUserCommonInfo.ucFwCrc = pucIspXram[usIspLength - 1];
            pucIspXram[usIspLength - 1] = 0xFF;
        }
    }
#if(_FW_UPDATE_CLAC_CRC_TYPE == _FW_UPDATE_FW_CLAC_CRC)
    g_stFwUpdateUserCommonInfo.ucCalCrc = UserCommonFwUpdateCalculateCrc(usIspLength, pucIspXram, g_stFwUpdateUserCommonInfo.ucCalCrc);
#endif
#endif

    if(g_stFwUpdateUserCommonInfo.ulFwCurrentAddress < g_stFwUpdateUserCommonInfo.ulFwEndAddress)
    {
        if(UserCommonFwUpdateWriteFwData(usIspLength) == _FALSE)
        {
            return _FALSE;
        }
    }
    else
    {
        // Write Key and Signature
#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
        if(UserCommonFwUpdateWriteKeyAndSignatureData(usIspLength) == _FALSE)
        {
            return _FALSE;
        }
#endif
    }
    return _TRUE;
}
//--------------------------------------------------
// Description  : Fw Update Write  Fw Data
// Input Value : usProgramLength: ISP Length
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateWriteFwData(WORD usProgramLength)
{
    WORD usCurrentBank = (g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xFFFF0000) >> 16;
    BYTE ucCurrentSector = (g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xF000) >> 12;
    WORD usCurrentAddress = g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xFFFF;
    WORD usPage = 0;
    WORD usProgramStartPage = 0;
    WORD usProgramEndPage = 0;
    WORD usProgramCurrentAddr = 0;
    WORD usProgramCurrentLength = 0;
#if(((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_NONE) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)) && (_FW_UPDATE_CLAC_CRC_TYPE == _FW_UPDATE_FW_CLAC_CRC))
    BYTE pucReadBuf[256] = {0};
#endif

    if((usCurrentBank != g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank) || (ucCurrentSector != (g_stFwUpdateUserCommonInfo.stUserDataInfo.usFlagStartAddress >> 12)))
    {
        // Start and Dont Flag Sector Don't Erase or Write
        usProgramStartPage = g_stFwUpdateUserCommonInfo.ulFwCurrentAddress / _FLASH_PROGRAM_SIZE;
        usProgramEndPage = ((DWORD)g_stFwUpdateUserCommonInfo.ulFwCurrentAddress + usProgramLength) / _FLASH_PROGRAM_SIZE;
        if(((DWORD)g_stFwUpdateUserCommonInfo.ulFwCurrentAddress + usProgramLength) % _FLASH_PROGRAM_SIZE != 0)
        {
            usProgramEndPage = usProgramEndPage + 1;
        }
        for(usPage = usProgramStartPage; usPage < usProgramEndPage; usPage++)
        {
            // Assign usCurrentLength
            if(((WORD)_FLASH_PROGRAM_SIZE) < ((usCurrentAddress % _FLASH_PROGRAM_SIZE) + usProgramLength))
            {
                usProgramCurrentLength = (WORD)_FLASH_PROGRAM_SIZE - (usCurrentAddress % 256);
            }
            else
            {
                usProgramCurrentLength = usProgramLength;
            }
            // Erase Flash
            if((usCurrentBank != g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank) || (ucCurrentSector != (g_stFwUpdateUserCommonInfo.stUserDataInfo.usFlagStartAddress >> 12)))
            {
                if(((usCurrentBank != g_stFwUpdateUserCommonInfo.usLastBank)) && (usCurrentBank != g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank))
                {
                    ScalerFlashWREN(usCurrentBank, 0xFF);
                    ScalerFlashEraseBank(usCurrentBank, _TRUE, _FALSE);
                }
                g_stFwUpdateUserCommonInfo.usLastBank = usCurrentBank;
                g_stFwUpdateUserCommonInfo.ucLastSector = ucCurrentSector;
                if(ScalerFlashWritePageProgram(usCurrentBank, usCurrentAddress, usProgramCurrentLength, _TRUE, _FALSE) == _FALSE)
                {
                    return _FALSE;
                }
#if(((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_NONE) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)) && (_FW_UPDATE_CLAC_CRC_TYPE == _FW_UPDATE_FW_CLAC_CRC))
                // Read Check
                memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                UserCommonFlashRead(usCurrentBank, usCurrentAddress, usProgramCurrentLength, pucReadBuf);
                if(memcmp(GET_ISP_XRAM_BUFFER(0), pucReadBuf, usProgramCurrentLength) != 0)
                {
                    return _FALSE;
                }
#endif
            }
            g_stFwUpdateUserCommonInfo.ulFwCurrentAddress += usProgramCurrentLength;
            usProgramLength = usProgramLength - usProgramCurrentLength;
            if((usProgramStartPage != usProgramEndPage) && (usProgramLength != 0))
            {
                usProgramCurrentAddr = usProgramCurrentAddr + usProgramCurrentLength;
                usCurrentBank = (g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xFFFF0000) >> 16;
                ucCurrentSector = (g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xF000) >> 12;
                usCurrentAddress = g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xFFFF;
                memcpy(GET_ISP_XRAM_BUFFER(0), GET_ISP_XRAM_BUFFER(usProgramCurrentLength), usProgramLength);
            }
        }
    }
    else
    {
        g_stFwUpdateUserCommonInfo.ulFwCurrentAddress += usProgramLength;
    }
    return _TRUE;
}

#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
//--------------------------------------------------
// Description  : Fw Update Write Key and Signature Data
// Input Value  : usProgramLength: ISP Length
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateWriteKeyAndSignatureData(WORD usProgramLength)
{
    BYTE pucReadBuf[256] = {0};
    WORD usCurrentAddress = 0;
    WORD usTmpKeyLen = 0;
    WORD usTmpSigLen = 0;
    DWORD ulTotalLen = ((DWORD)_DIGITAL_SIGNATURE_INFO_HEADER_SIZE + g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyLen + g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureLen);

    if(g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen >= ulTotalLen)
    {
        g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen += usProgramLength;
        return _TRUE;
    }

    if(g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen > _DIGITAL_SIGNATURE_INFO_HEADER_SIZE)
    {
        // ISP Key;
        if(g_stFwUpdateUserCommonInfo.usIspKeyLen < g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyLen)
        {
            if((g_stFwUpdateUserCommonInfo.usIspKeyLen + usProgramLength) < g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyLen)
            {
                usCurrentAddress = g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyStartAddress + g_stFwUpdateUserCommonInfo.usIspKeyLen;
                ScalerFlashWrite(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usProgramLength, GET_ISP_XRAM_BUFFER(0));
                // Read Check
                memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usProgramLength, pucReadBuf);
                if(memcmp(GET_ISP_XRAM_BUFFER(0), pucReadBuf, usProgramLength) != 0)
                {
                    return _FALSE;
                }
                g_stFwUpdateUserCommonInfo.usIspKeyLen += usProgramLength;
            }
            else
            {
                usCurrentAddress = g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyStartAddress + g_stFwUpdateUserCommonInfo.usIspKeyLen;
                usTmpKeyLen = g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyLen - g_stFwUpdateUserCommonInfo.usIspKeyLen;
                if(usTmpKeyLen > 0)
                {
                    ScalerFlashWrite(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, GET_ISP_XRAM_BUFFER(0));
                    // Read Check
                    memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                    UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, pucReadBuf);
                    if(memcmp(GET_ISP_XRAM_BUFFER(0), pucReadBuf, usTmpKeyLen) != 0)
                    {
                        return _FALSE;
                    }
                    g_stFwUpdateUserCommonInfo.usIspKeyLen += usTmpKeyLen;
                }
                // isp Signaure data
                usTmpSigLen = usProgramLength - usTmpKeyLen;
                if(usTmpSigLen > 0)
                {
                    usCurrentAddress = g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureStartAddress;
                    memcpy(GET_ISP_XRAM_BUFFER(0), GET_ISP_XRAM_BUFFER(usTmpKeyLen), usTmpSigLen);
                    ScalerFlashWrite(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpSigLen, GET_ISP_XRAM_BUFFER(0));
                    // Read Check
                    memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                    UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpSigLen, pucReadBuf);
                    if(memcmp(GET_ISP_XRAM_BUFFER(0), pucReadBuf, usTmpSigLen) != 0)
                    {
                        return _FALSE;
                    }
                    g_stFwUpdateUserCommonInfo.usIspSigLen += usTmpSigLen;
                }
            }
        }
        else
        {
            // ISP Signature;
            if(g_stFwUpdateUserCommonInfo.usIspSigLen < g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureLen)
            {
                if((g_stFwUpdateUserCommonInfo.usIspSigLen + usProgramLength) < g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureLen)
                {
                    usCurrentAddress = g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureStartAddress + g_stFwUpdateUserCommonInfo.usIspSigLen;
                    ScalerFlashWrite(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usProgramLength, GET_ISP_XRAM_BUFFER(0));
                    // Read Check
                    UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usProgramLength, pucReadBuf);
                    if(memcmp(GET_ISP_XRAM_BUFFER(0), pucReadBuf, usProgramLength) != 0)
                    {
                        return _FALSE;
                    }
                    g_stFwUpdateUserCommonInfo.usIspSigLen += usProgramLength;
                }
                else
                {
                    usCurrentAddress = g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureStartAddress + g_stFwUpdateUserCommonInfo.usIspSigLen;
                    usTmpSigLen = g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureLen - g_stFwUpdateUserCommonInfo.usIspSigLen;
                    if(usTmpSigLen > 0)
                    {
                        ScalerFlashWrite(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpSigLen, GET_ISP_XRAM_BUFFER(0));
                        // Read Check
                        memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                        UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpSigLen, pucReadBuf);
                        if(memcmp(GET_ISP_XRAM_BUFFER(0), pucReadBuf, usTmpSigLen) != 0)
                        {
                            return _FALSE;
                        }
                        g_stFwUpdateUserCommonInfo.usIspSigLen += usTmpKeyLen;
                    }
                }
            }
        }
    }
    else
    {
        if((g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen + usProgramLength) > _DIGITAL_SIGNATURE_INFO_HEADER_SIZE)
        {
            if(usProgramLength > _DIGITAL_SIGNATURE_INFO_HEADER_SIZE)
            {
                usTmpKeyLen = usProgramLength - _DIGITAL_SIGNATURE_INFO_HEADER_SIZE;
                usCurrentAddress = g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyStartAddress;
                memcpy(GET_ISP_XRAM_BUFFER(0), GET_ISP_XRAM_BUFFER(_DIGITAL_SIGNATURE_INFO_HEADER_SIZE), usTmpKeyLen);
                ScalerFlashWrite(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, GET_ISP_XRAM_BUFFER(0));
                // Read Check
                memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, pucReadBuf);
                if(memcmp(GET_ISP_XRAM_BUFFER(0), pucReadBuf, usTmpKeyLen) != 0)
                {
                    return _FALSE;
                }
                g_stFwUpdateUserCommonInfo.usIspKeyLen += usTmpKeyLen;
            }
            else
            {
                usTmpKeyLen = (g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen + usProgramLength) - _DIGITAL_SIGNATURE_INFO_HEADER_SIZE;
                usCurrentAddress = g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyStartAddress;
                usTmpSigLen = usProgramLength - usTmpKeyLen;
                memcpy(GET_ISP_XRAM_BUFFER(0), GET_ISP_XRAM_BUFFER(usTmpSigLen), usTmpKeyLen);
                ScalerFlashWrite(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, GET_ISP_XRAM_BUFFER(0));
                // Read Check
                memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, pucReadBuf);
                if(memcmp(GET_ISP_XRAM_BUFFER(0), pucReadBuf, usTmpKeyLen) != 0)
                {
                    return _FALSE;
                }
                g_stFwUpdateUserCommonInfo.usIspKeyLen += usTmpKeyLen;
            }
        }
    }
    g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen += usProgramLength;

    return _TRUE;
}
#endif

#endif



#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
//--------------------------------------------------
// Description  :  Fw Update MCU Reset
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateReset(void)
{
    ScalerFlashWRDis();
    ScalerFwUpdateReset();
}
#endif

//--------------------------------------------------
// Description  : Get DDC-CI Data in Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateIntProc(void)
{
#if(((_MULTI_DISPLAY_MAX == 0x01) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)) || (_MULTI_DISPLAY_MAX > 0x01))
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
    if(((GET_BG_ISP_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS) && (GET_BG_ISP_ISP_CHANNEL() == _DDCCI0)) || (GET_DDCCI0_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS))
#else
    if(GET_DDCCI0_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS)
#endif
    {
        ScalerFwUpdateDdcci0IntProc();
    }
#endif

#if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
    if(((GET_BG_ISP_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS) && (GET_BG_ISP_ISP_CHANNEL() == _DDCCI1)) || (GET_DDCCI1_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS))
#else
    if(GET_DDCCI1_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS)
#endif
    {
        ScalerFwUpdateDdcci1IntProc();
    }
#endif

#if((_MULTI_DISPLAY_MAX >= 0x03) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
    if(((GET_BG_ISP_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS) && (GET_BG_ISP_ISP_CHANNEL() == _DDCCI2)) || (GET_DDCCI2_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS))
#else
    if(GET_DDCCI2_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS)
#endif
    {
        ScalerFwUpdateDdcci2IntProc();
    }
#endif

#if((_MULTI_DISPLAY_MAX >= 0x04) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
    if(((GET_BG_ISP_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS) && (GET_BG_ISP_ISP_CHANNEL() == _DDCCI3)) || (GET_DDCCI3_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS))
#else
    if(GET_DDCCI3_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS)
#endif
    {
        ScalerFwUpdateDdcci3IntProc();
    }
#endif

#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
    if(((GET_BG_ISP_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS) && (GET_BG_ISP_ISP_CHANNEL() == _DDCCI4)) || (GET_DDCCI4_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS))
#else
    if(GET_DDCCI4_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS)
#endif
    {
        ScalerFwUpdateDdcci4IntProc();
    }
#endif
}

//--------------------------------------------------
// Description  : Get DDC-CI Status in Interrupt Process
// Input Value  : None
// Output Value : _TURE or _False
//--------------------------------------------------
BYTE UserCommonFwUpdateGetStatus(void)
{
    if(ScalerFwUpdateGetState() == _TRUE)
    {
        return _TRUE;
    }
    return _FALSE;
}

#if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)
//--------------------------------------------------
// Description  : Fw Update Password Verify
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdatePasswordVerify(WORD usBank, WORD usAddr)
{
    BYTE pucPasswordTable[sizeof(tFwPassword)];

    // Read BootTable data from Flash
    UserCommonFlashRead(usBank, usAddr, sizeof(tFwPassword), pucPasswordTable);

    // Check user-defined user/boot code id
    if(memcmp(tFwPassword, pucPasswordTable, sizeof(tFwPassword)) == 0)
    {
        // Check success; return user bank address
        return _TRUE;
    }
    return _FALSE;
}
#endif // End #if(_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)

#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
//---------------------------------------------------------
// Description  : FW Update Change Bank
// Input Value  : None
// Output Value : None
//---------------------------------------------------------
void UserCommonFwUpdateChangeBank(void)
{
    WORD usBankIndex = ((WORD)(g_pucFwUpdateRxBuf[2] << 8) | g_pucFwUpdateRxBuf[3]);
    WORD usFWBankIndex = HIWORD(g_stFwUpdateUserCommonInfo.ulFwStartAddress) + usBankIndex;

    ScalerFlashEraseBank(usFWBankIndex, _TRUE, _FALSE);
    g_stFwUpdateUserCommonInfo.ulFwCurrentAddress += 65536;
    ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);
}
#endif

#endif

