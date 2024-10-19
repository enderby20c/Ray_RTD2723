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
// ID Code      : UserCommonFwUpdateForeground.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_FW_UPDATE_FOREGROUND__

#include "UserCommonInclude.h"
#include "FwUpdateForeground/UserCommonFwUpdateForeground.h"

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructFwUpdateForgroundScalerInfo g_stFwUpdateForegroundInfo = {_FALSE, _IDLE_STATUS};
#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESTORE_SCENE)
EnumPowerStatus g_enumFwUpdateForegroundPowerStatusBackup;
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Background Fw Update Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateForegroundHandler(void)
{
    bit bResult = _FALSE;
    do
    {
        if((GET_FW_UPDATE_RUN_COMMAND() == _TRUE) && (GET_FW_UPDATE_MODE() == _FOREGROUND_MODE))
        {
            if(g_pucFwUpdateRxBuf[_FW_UPDATE_SUBADDRESS_INDEX] == _FW_UPDATE_FOREGROUND_CMD_SUB_ADDREESS)
            {
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT);
                switch(g_pucFwUpdateRxBuf[_FW_UPDATE_OPCODE_INDEX])
                {
                    case _FW_UPDATE_FOREGROUND_OPCODE_SET_HIGH_PRI_REQ:
                        UserCommonFwUpdateForegroundSetHighPriProcess();
                        ScalerTimerReactiveTimerEvent(_FW_UPDATE_FOREGROUND_EXIT_TIMER_COUNT, _SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT);
                        break;
                    case _FW_UPDATE_FOREGROUND_OPCODE_GET_PROJECT_ID_ADDR_REQ:
                        UserCommonFwUpdateForegroundGetProjectIDAddrProcess();
                        ScalerTimerReactiveTimerEvent(_FW_UPDATE_FOREGROUND_EXIT_TIMER_COUNT, _SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT);
                        break;
                    case _FW_UPDATE_FOREGROUND_OPCODE_VERIFY_PROJECT_ID_REQ:
                        UserCommonFwUpdateForegroundVerifyProjectIDProcess();
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _OFF)
                        ScalerTimerReactiveTimerEvent(_FW_UPDATE_FOREGROUND_EXIT_TIMER_COUNT, _SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT);
#endif
                        break;
                    case _FW_UPDATE_FOREGROUND_OPCODE_START_REQ:
                        UserCommonFwUpdateForegroundStartProcess();
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _OFF)
                        ScalerTimerReactiveTimerEvent(_FW_UPDATE_FOREGROUND_EXIT_TIMER_COUNT, _SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT);
#endif
                        break;
                    case _FW_UPDATE_FOREGROUND_OPCODE_FINISH_REQ:
                        UserCommonFwUpdateForegroundFinishProcess();
                        ScalerTimerReactiveTimerEvent(_FW_UPDATE_FOREGROUND_EXIT_TIMER_COUNT, _SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT);
                        break;
                    case _FW_UPDATE_FOREGROUND_OPCODE_GET_ACFWVER_REQ:
                        UserCommonFwUpdateForegroundGetFwVersionProcess();
                        ScalerTimerReactiveTimerEvent(_FW_UPDATE_FOREGROUND_EXIT_TIMER_COUNT, _SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT);
                        break;
                    case _FW_UPDATE_FOREGROUND_OPCODE_EXIT_REQ:
                        UserCommonFwUpdateForegroundExitProcess();
                        break;
                    case _FW_UPDATE_FOREGROUND_OPCODE_CHANGE_MODE_REQ:
                        UserCommonFwUpdateForegroundChangeModeProcess();
                        break;
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
                    case _FW_UPDATE_FOREGROUND_OPCODE_CHANGE_BANK_REQ:
                        UserCommonFwUpdateChangeBank();
                        break;
#endif
                    default:
                        ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_COMMAND_ERROR);
                        break;
                }
                bResult = _TRUE;
            }
            else if(g_pucFwUpdateRxBuf[_FW_UPDATE_SUBADDRESS_INDEX] == _FW_UPDATE_FOREGROUND_ISP_DATA_SUB_ADDRESS)
            {
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT);
                UserCommonFwUpdateForegroundWriteDataProcess();
                ScalerTimerReactiveTimerEvent(_FW_UPDATE_FOREGROUND_EXIT_TIMER_COUNT, _SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT);
                bResult = _TRUE;
            }
            else
            {
                ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_COMMAND_ERROR);
                bResult = _TRUE;
            }
        }

        if(UserCommonFwUpdateForegroundGetHighPriority() == _TRUE)
        {
            SysTimerFwUpdateForegroundHandler();
        }
    }while(UserCommonFwUpdateForegroundGetHighPriority() == _TRUE);
    return bResult;
}

//--------------------------------------------------
// Description  : Set Fw Update high Priority
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundSetHighPriProcess(void)
{
    SET_FW_UPDATE_FOREGROUND_HIGH_PRIORITY(g_pucFwUpdateRxBuf[2]);

    // Send Reply
    UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);
}

//--------------------------------------------------
// Description  : Get Project ID Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundGetProjectIDAddrProcess(void)
{
    BYTE pucszBuf[6] = {0};
    pucszBuf[0] = _FW_UPDATE_RESULT_IDLE_AND_SUCCESS;

    ScalerFwCheckGetProjectIDAddress(&pucszBuf[1]);
    // Send Data
    ScalerFwUpdateSendData(6, pucszBuf);
}

//--------------------------------------------------
// Description  : Verify Project ID
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundVerifyProjectIDProcess(void)
{
    EnumProjectIDVerifyResult enumResult = _ISP_FW_CHECK_VERIFY_FAIL;
    enumResult = ScalerFwCheckProjectIDVerify(&g_pucFwUpdateRxBuf[2]);
    if(enumResult == _ISP_FW_CHECK_VERIFY_FAIL)
    {
        UserCommonFwUpdateForegroundExitBeforeProgramData();
        ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }

    SET_FW_UPDATE_VERIFY_ID_PASS(_TRUE);
    // Send Data
    UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);
}

//--------------------------------------------------
// Description  : Background Fw Update Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundStartProcess(void)
{
    if(GET_FW_UPDATE_VERIFY_ID_PASS() == _FALSE)
    {
        UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
    g_stFwUpdateUserCommonInfo.usIspPageCount = (WORD)((WORD)(g_pucFwUpdateRxBuf[2] << 8) | g_pucFwUpdateRxBuf[3]);
#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
    if(((_DUAL_BANK_USER_FW_CODE_SIZE * 65536) % g_stFwUpdateUserCommonInfo.usIspPageCount) != 0)
    {
        UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
#endif

    if(g_stFwUpdateUserCommonInfo.usIspPageCount > _FW_UPDATE_FOREGROUND_MAX_ISP_LEN)
    {
        UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }

#if((_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESET) && (_FW_UPDATE_FOREGROUND_DISABLE_INT0 == _ON))
    // Disable INT0
    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_0, _DISABLE);
#endif

#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESTORE_SCENE)
    UserCommonFwUpdateForegroundSceneBackup();
#endif

    // Get Start Addrtess
    if(UserCommonFwUpdateStartProcess(g_stFwUpdateUserCommonInfo.usIspPageCount, _TRUE) == _FALSE)
    {
        UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
    ScalerFwUpdateSpeedUpInital(g_stFwUpdateUserCommonInfo.ulFwStartAddress, g_stFwUpdateUserCommonInfo.usIspPageCount, _FW_UPDATE_SLAVE_ADDRESS, _FW_UPDATE_FOREGROUND_ISP_DATA_SUB_ADDRESS);
#endif
    SET_FW_UPDATE_FOREGROUND_STATUS(_FW_UPDATE_STATUS);
    if(SysPowerGetPowerStatus() != _POWER_STATUS_NORMAL)
    {
        SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
    }
    // Send Data
    UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);
}
//--------------------------------------------------
// Description  : Background Fw Update Write Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundWriteDataProcess(void)
{
    if(GET_FW_UPDATE_VERIFY_ID_PASS() == _FALSE)
    {
        UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }

    if(g_stFwUpdateUserCommonInfo.b1IspStartFlag == _FALSE)
    {
        UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }

    if(UserCommonFwUpdateWriteDataProcess(GET_ISP_XRAM_BUFFER(0), g_stFwUpdateUserCommonInfo.usIspPageCount, _TRUE) == _FALSE)
    {
        UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
    UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);
}

//--------------------------------------------------
// Description  : Fw Update Write  Fw Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateForegroundWriteFwData(WORD usProgramLength)
{
    WORD usCurrentBank = (g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xFFFF0000) >> 16;
    BYTE ucCurrentSector = (g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xF000) >> 12;
    WORD usCurrentAddress = g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xFFFF;
    WORD usPage = 0;
    WORD usProgramStartPage = 0;
    WORD usProgramEndPage = 0;
    WORD usProgramCurrentAddr = 0;
    WORD usProgramCurrentLength = 0;
#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_NONE) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD))
    BYTE pucReadBuf[256] = {0};
#endif

    if((usCurrentBank != g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank) || (ucCurrentSector != (g_stFwUpdateUserCommonInfo.stUserDataInfo.usFlagStartAddress >> 12)))
    {
        // Start and Dont Flag Sector Don't Erase or Write
        usProgramStartPage = g_stFwUpdateUserCommonInfo.ulFwCurrentAddress / _FLASH_PROGRAM_SIZE;
        usProgramEndPage = ((DWORD)g_stFwUpdateUserCommonInfo.ulFwCurrentAddress + g_stFwUpdateUserCommonInfo.usIspPageCount) / _FLASH_PROGRAM_SIZE;
        if(((DWORD)g_stFwUpdateUserCommonInfo.ulFwCurrentAddress + g_stFwUpdateUserCommonInfo.usIspPageCount) % _FLASH_PROGRAM_SIZE != 0)
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
                    ScalerFlashEraseBank(usCurrentBank, _FALSE, _FALSE);
                }
                g_stFwUpdateUserCommonInfo.usLastBank = usCurrentBank;
                g_stFwUpdateUserCommonInfo.ucLastSector = ucCurrentSector;
                if(ScalerFlashWritePageProgram(usCurrentBank, usCurrentAddress, usProgramCurrentLength, _FALSE, _FALSE) == _FALSE)
                {
                    return _FALSE;
                }
#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_NONE) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD))
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
        g_stFwUpdateUserCommonInfo.ulFwCurrentAddress += g_stFwUpdateUserCommonInfo.usIspPageCount;
    }
    return _TRUE;
}
//--------------------------------------------------
// Description  : Background Fw Update Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundFinishProcess(void)
{
    if(GET_FW_UPDATE_VERIFY_ID_PASS() == _FALSE)
    {
        UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }

    if(UserCommonFwUpdateFinishProcess() == _FALSE)
    {
        UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
    UserCommonFwUpdateForegroundSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);
}

//---------------------------------------------------------
// Description  : Background Fw Update Get Active Fw Version
// Input Value  : None
// Output Value : None
//---------------------------------------------------------
void UserCommonFwUpdateForegroundGetFwVersionProcess(void)
{
    BYTE pucVersionReply[7] = {0};

    UserCommonFwUpdateGetFwVersion(pucVersionReply);

    // Enable mcu write and reset buffer
    ScalerFwUpdateSendData(7, pucVersionReply);
}

//---------------------------------------------------------
// Description  : Background Fw Update ExiT
// Input Value  : None
// Output Value : None
//---------------------------------------------------------
void UserCommonFwUpdateForegroundExitProcess(void)
{
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
    ScalerFwUpdateEnableSpeedUp(_FALSE);
#endif
#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESET)
    UserCommonFwUpdateForegroundReset();
#elif(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESTORE_SCENE)
    UserCommonFwUpdateForegroundRestoreScene();
#endif
}

//---------------------------------------------------------
// Description  :  Foreground Fw Update Change Mode
// Input Value  : None
// Output Value : None
//---------------------------------------------------------
void UserCommonFwUpdateForegroundChangeModeProcess(void)
{
    ScalerFwUpdateExit();
}


//--------------------------------------------------
// Description  : Fw Update Forground Send Reply
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundSendReply(BYTE ucResult)
{
    ScalerFwUpdateSendReply(ucResult);
}

//--------------------------------------------------
// Description  : User Common Get High Priority
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateForegroundGetHighPriority(void)
{
    if(ScalerFwUpdateForegroundGetStatus() == _TRUE)
    {
        if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
        {
            return GET_FW_UPDATE_FOREGROUND_HIGH_PRIORITY();
        }
        else
        {
            SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
            return _FALSE;
        }
    }
    return GET_FW_UPDATE_FOREGROUND_HIGH_PRIORITY();
}
//--------------------------------------------------
// Description  : Commnad Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundTimeoutExit(void)
{
    if(GET_FW_UPDATE_FOREGROUND_STATUS() != _FW_UPDATE_STATUS)
    {
        UserCommonFwUpdateForegroundExitBeforeProgramData();
    }
    else
    {
        UserCommonFwUpdateForegroundExitProcess();
    }
}

//--------------------------------------------------
// Description  : Exit Before Program Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundExitBeforeProgramData(void)
{
    SET_FW_UPDATE_FOREGROUND_HIGH_PRIORITY(_FALSE);
    SET_FW_UPDATE_FOREGROUND_STATUS(_IDLE_STATUS);
    SET_FW_UPDATE_VERIFY_ID_PASS(_FALSE);
    ScalerFwUpdateExit();
}

#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
//--------------------------------------------------
// Description  : Fw Update Write Key and Signature Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateForegroundWriteKeyAndSignatureData(void)
{
    BYTE pucReadBuf[256] = {0};
    WORD usCurrentAddress = 0;
    WORD usTmpKeyLen = 0;
    WORD usTmpSigLen = 0;
    DWORD ulTotalLen = ((DWORD)_DIGITAL_SIGNATURE_INFO_HEADER_SIZE + g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyLen + g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureLen);

    if(g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen >= ulTotalLen)
    {
        g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen += g_stFwUpdateUserCommonInfo.usIspPageCount;
        return _TRUE;
    }

    if(g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen > _DIGITAL_SIGNATURE_INFO_HEADER_SIZE)
    {
        // ISP Key;
        if(g_stFwUpdateUserCommonInfo.usIspKeyLen < g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyLen)
        {
            if((g_stFwUpdateUserCommonInfo.usIspKeyLen + g_stFwUpdateUserCommonInfo.usIspPageCount) < g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyLen)
            {
                usCurrentAddress = g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyStartAddress + g_stFwUpdateUserCommonInfo.usIspKeyLen;
                ScalerFlashWrite(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, g_stFwUpdateUserCommonInfo.usIspPageCount, GET_ISP_XRAM_BUFFER(0));
                // Read Check
                memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, g_stFwUpdateUserCommonInfo.usIspPageCount, pucReadBuf);
                if(memcmp(GET_ISP_XRAM_BUFFER(0), pucReadBuf, g_stFwUpdateUserCommonInfo.usIspPageCount) != 0)
                {
                    return _FALSE;
                }
                g_stFwUpdateUserCommonInfo.usIspKeyLen += g_stFwUpdateUserCommonInfo.usIspPageCount;
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
                usTmpSigLen = g_stFwUpdateUserCommonInfo.usIspPageCount - usTmpKeyLen;
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
                if((g_stFwUpdateUserCommonInfo.usIspSigLen + g_stFwUpdateUserCommonInfo.usIspPageCount) < g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureLen)
                {
                    usCurrentAddress = g_stFwUpdateUserCommonInfo.stUserDataInfo.usSignatureStartAddress + g_stFwUpdateUserCommonInfo.usIspSigLen;
                    ScalerFlashWrite(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, g_stFwUpdateUserCommonInfo.usIspPageCount, GET_ISP_XRAM_BUFFER(0));
                    // Read Check
                    UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, g_stFwUpdateUserCommonInfo.usIspPageCount, pucReadBuf);
                    if(memcmp(GET_ISP_XRAM_BUFFER(0), pucReadBuf, g_stFwUpdateUserCommonInfo.usIspPageCount) != 0)
                    {
                        return _FALSE;
                    }
                    g_stFwUpdateUserCommonInfo.usIspSigLen += g_stFwUpdateUserCommonInfo.usIspPageCount;
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
        if((g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen + g_stFwUpdateUserCommonInfo.usIspPageCount) > _DIGITAL_SIGNATURE_INFO_HEADER_SIZE)
        {
            if(g_stFwUpdateUserCommonInfo.usIspPageCount > _DIGITAL_SIGNATURE_INFO_HEADER_SIZE)
            {
                usTmpKeyLen = g_stFwUpdateUserCommonInfo.usIspPageCount - _DIGITAL_SIGNATURE_INFO_HEADER_SIZE;
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
                usTmpKeyLen = (g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen + g_stFwUpdateUserCommonInfo.usIspPageCount) - _DIGITAL_SIGNATURE_INFO_HEADER_SIZE;
                usCurrentAddress = g_stFwUpdateUserCommonInfo.stUserDataInfo.usKeyStartAddress;
                usTmpSigLen = g_stFwUpdateUserCommonInfo.usIspPageCount - usTmpKeyLen;
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
    g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen += g_stFwUpdateUserCommonInfo.usIspPageCount;

    return _TRUE;
}
#endif

#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESET)
//--------------------------------------------------
// Description  : Foreground Fw Update Restore Reset
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundReset(void)
{
    ScalerFlashWRDis();
    ScalerFwUpdateForegroundReset();
}
#endif

#if(_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESTORE_SCENE)
//--------------------------------------------------
// Description  : Foreground Fw Update Scene Backup
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundSceneBackup(void)
{
    g_enumFwUpdateForegroundPowerStatusBackup = SysPowerGetPowerStatus();
}

//--------------------------------------------------
// Description  : Foreground Fw Update Restore Scene
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateForegroundRestoreScene(void)
{
    ScalerFlashWRDis();
    UserCommonFwUpdateForegroundExitBeforeProgramData();
    SysPowerSetTargetPowerStatus(g_enumFwUpdateForegroundPowerStatusBackup);
}
#endif

#endif

