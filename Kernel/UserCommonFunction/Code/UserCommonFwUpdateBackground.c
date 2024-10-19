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
// ID Code      : UserCommonFwUpdateBackground.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_FW_UPDATE_BACKGROUND__

#include "UserCommonInclude.h"
#include "FwUpdateBackground/UserCommonFwUpdateBackground.h"

#if(_FW_UPDATE_BACKGROUND_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Background Fw Update Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateBackgroundHandler(void)
{
    if((GET_FW_UPDATE_RUN_COMMAND() == _TRUE) && (GET_FW_UPDATE_MODE() == _BACKGROUND_MODE))
    {
        if(g_pucFwUpdateRxBuf[_FW_UPDATE_SUBADDRESS_INDEX] == _BACKGROUND_FW_UPDATE_CMD_SUB_ADDREESS)
        {
            switch(g_pucFwUpdateRxBuf[_FW_UPDATE_OPCODE_INDEX])
            {
                case _BACKGROUND_FW_UPDATE_OPCODE_START_REQ:
                    UserCommonFwUpdateBackgroundStartProcess();
                    break;
                case _BACKGROUND_FW_UPDATE_OPCODE_FINISH_REQ:
                    UserCommonFwUpdateBackgroundFinishProcess();
                    break;
                case _BACKGROUND_FW_UPDATE_OPCODE_GET_ACFWVER_REQ:
                    UserCommonFwUpdateBackgroundGetFwVersionProcess();
                    break;
                case _BACKGROUND_FW_UPDATE_OPCODE_EXIT_REQ:
                    UserCommonFwUpdateBackgroundExitProcess();
                    break;
                case _BACKGROUND_FW_UPDATE_OPCODE_SET_DATA_LEN_REQ:
                    UserCommonFwUpdateBackgroundSetDataPacketLenProcess();
                    break;
#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
                case _BACKGROUND_FW_UPDATE_OPCODE_GET_PROJECT_ID_ADDR_REQ:
                    UserCommonFwUpdateBackgroundGetProjectIDAddrProcess();
                    break;
                case _BACKGROUND_FW_UPDATE_OPCODE_VERIFY_PROJECT_ID_REQ:
                    UserCommonFwUpdateBackgroundVerifyProjectIDProcess();
                    break;
#endif
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
                case _BACKGROUND_FW_UPDATE_OPCODE_CHANGE_BANK_REQ:
                    UserCommonFwUpdateChangeBank();
                    break;
#endif
                default:
                    ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_COMMAND_ERROR);
                    break;
            }
        }
        else if(g_pucFwUpdateRxBuf[_FW_UPDATE_SUBADDRESS_INDEX] == _BACKGROUND_FW_UPDATE_ISP_DATA_SUB_ADDRESS)
        {
            UserCommonFwUpdateBackgroundWriteDataProcess();
        }
        else
        {
            ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_COMMAND_ERROR);
        }
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Background Fw Update Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateBackgroundStartProcess(void)
{
#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
    if(GET_FW_UPDATE_VERIFY_ID_PASS() == _FALSE)
    {
        ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
#endif

    if(ScalerFwUpdateBackgroundGetSystemStatus() == _STATUS_BUSY)
    {
        return;
    }

    // Urgent IP Process when FW Background Update Start
    UserCommonFwUpdateBackgroundUrgentIpProc(_FW_UPDATE_START);

    // Get Start Addrtess
    if(UserCommonFwUpdateStartProcess(_HW_DDCCI_BUF_SIZE, _FALSE) == _FALSE)
    {
        ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
    ScalerFwUpdateSpeedUpInital(g_stFwUpdateUserCommonInfo.ulFwStartAddress, g_stFwUpdateUserCommonInfo.usIspPageCount, _FW_UPDATE_SLAVE_ADDRESS, _BACKGROUND_FW_UPDATE_ISP_DATA_SUB_ADDRESS);
#endif
    // Send Data
    ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);
}

//--------------------------------------------------
// Description  : Background Fw Update Write Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateBackgroundWriteDataProcess(void)
{
    WORD usIspLength = g_stFwUpdateUserCommonInfo.usIspPageCount;
#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_NONE) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD))
#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
    // Digital Signature Append 1 bank Digital signature Info after FW Data
    WORD usBankCount = _DUAL_BANK_USER_FW_CODE_SIZE + 1;
#else
    WORD usBankCount = _DUAL_BANK_USER_FW_CODE_SIZE;
#endif
#endif
#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
    if(GET_FW_UPDATE_VERIFY_ID_PASS() == _FALSE)
    {
        ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
#endif

    if(ScalerFwUpdateBackgroundGetSystemStatus() == _STATUS_BUSY)
    {
        return;
    }

    if(g_stFwUpdateUserCommonInfo.b1IspStartFlag == _FALSE)
    {
        ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_NONE) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD))
    // Save Crc and fullfill last data 0xFF for CalulateCrc
    if(((usBankCount * 65536) % g_stFwUpdateUserCommonInfo.usIspPageCount) == 0)
    {
        // If the data sent each time can be divided by the total data transmitted
        // Save Crc at the last data
        if((g_stFwUpdateUserCommonInfo.ulFwCurrentAddress + g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen) == (g_stFwUpdateUserCommonInfo.ulFwStartAddress + usBankCount * 65536 - g_stFwUpdateUserCommonInfo.usIspPageCount))
        {
            g_stFwUpdateUserCommonInfo.ucFwCrc = g_pucFwUpdateRxBuf[g_stFwUpdateUserCommonInfo.usIspPageCount];
            g_pucFwUpdateRxBuf[g_stFwUpdateUserCommonInfo.usIspPageCount] = 0xFF;
        }
    }
    else
    {
        // If the data sent each time can't be divided by the total data transmitted
        // Save Crc at the last data
        if((g_stFwUpdateUserCommonInfo.ulFwCurrentAddress + g_stFwUpdateUserCommonInfo.ulReceivedKeyAndSigLen) == (g_stFwUpdateUserCommonInfo.ulFwStartAddress + usBankCount * 65536 - ((usBankCount * 65536) % g_stFwUpdateUserCommonInfo.usIspPageCount)))
        {
            // Last packet data
            usIspLength = usBankCount * 65536 % g_stFwUpdateUserCommonInfo.usIspPageCount;
            g_stFwUpdateUserCommonInfo.ucFwCrc = g_pucFwUpdateRxBuf[usIspLength];
            g_pucFwUpdateRxBuf[usIspLength] = 0xFF;
        }
    }
#if(_FW_UPDATE_CLAC_CRC_TYPE == _FW_UPDATE_FW_CLAC_CRC)
    g_stFwUpdateUserCommonInfo.ucCalCrc = UserCommonFwUpdateCalculateCrc(usIspLength, &g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX], g_stFwUpdateUserCommonInfo.ucCalCrc);
#endif
#endif
    if(g_stFwUpdateUserCommonInfo.ulFwCurrentAddress < g_stFwUpdateUserCommonInfo.ulFwEndAddress)
    {
        if(UserCommonFwUpdateBackgroundWriteFwData(usIspLength) == _FALSE)
        {
            ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
            return;
        }
    }
    else
    {
        // Write Key and Signature
#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
        if(UserCommonFwUpdateBackgroundWriteKeyAndSignatureData() == _FALSE)
        {
            ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
            return;
        }
#endif
    }
    ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);
}

//--------------------------------------------------
// Description  : Background Fw Update Write Fw
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateBackgroundWriteFwData(WORD usProgramLength)
{
    WORD usCurrentBank = (g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xFFFF0000) >> 16;
    BYTE ucCurrentSector = (g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xF000) >> 12;
    WORD usCurrentAddress = g_stFwUpdateUserCommonInfo.ulFwCurrentAddress & 0xFFFF;
#if(((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_NONE) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)) && (_FW_UPDATE_CLAC_CRC_TYPE == _FW_UPDATE_FW_CLAC_CRC))
    BYTE pucReadBuf[_HW_DDCCI_BUF_SIZE] = {0};
#endif
    // Start and Dont Flag Sector Don't Erase or Write
    if((usCurrentBank != g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank) || (ucCurrentSector != (g_stFwUpdateUserCommonInfo.stUserDataInfo.usFlagStartAddress >> 12)))
    {
        // Erase Flash
        if((usCurrentBank != g_stFwUpdateUserCommonInfo.usLastBank) || (ucCurrentSector != g_stFwUpdateUserCommonInfo.ucLastSector))
        {
            UserCommonFlashErasePage(usCurrentBank, ucCurrentSector);
            g_stFwUpdateUserCommonInfo.usLastBank = usCurrentBank;
            g_stFwUpdateUserCommonInfo.ucLastSector = ucCurrentSector;
        }

        // Write Flash
        if(ScalerFlashWriteByKernel(usCurrentBank, usCurrentAddress, usProgramLength, &g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX], _TRUE, _FALSE) == _FALSE)
        {
            return _FALSE;
        }
#if(((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_NONE) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_PASSWORD)) && (_FW_UPDATE_CLAC_CRC_TYPE == _FW_UPDATE_FW_CLAC_CRC))
        // Read Flash
        memset(pucReadBuf, 0, sizeof(pucReadBuf));
        UserCommonFlashRead(usCurrentBank, usCurrentAddress, usProgramLength, pucReadBuf);
        if(memcmp(&g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX], pucReadBuf, sizeof(pucReadBuf)) != 0)
        {
            return _FALSE;
        }
#endif
    }

    g_stFwUpdateUserCommonInfo.ulFwCurrentAddress += g_stFwUpdateUserCommonInfo.usIspPageCount;

    return _TRUE;
}
//--------------------------------------------------
// Description  : Background Fw Update Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateBackgroundFinishProcess(void)
{
    BYTE ucResult = _FW_UPDATE_RESULT_IDLE_AND_SUCCESS;

#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
    if(GET_FW_UPDATE_VERIFY_ID_PASS() == _FALSE)
    {
        ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
#endif

    if(ScalerFwUpdateBackgroundGetSystemStatus() == _STATUS_BUSY)
    {
        return;
    }
    if(UserCommonFwUpdateFinishProcess() == _FALSE)
    {
        ucResult = _FW_UPDATE_RESULT_IDLE_AND_FAIL;
    }
    ScalerFwUpdateSendReply(ucResult);

    // Urgent IP Process when FW Background Update End
    UserCommonFwUpdateBackgroundUrgentIpProc(_FW_UPDATE_END);
}

//---------------------------------------------------------
// Description  : Background Fw Update Get Active Fw Version
// Input Value  : None
// Output Value : None
//---------------------------------------------------------
void UserCommonFwUpdateBackgroundGetFwVersionProcess(void)
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
void UserCommonFwUpdateBackgroundExitProcess(void)
{
#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
    SET_FW_UPDATE_VERIFY_ID_PASS(_FALSE);
#endif

#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
    ScalerFwUpdateEnableSpeedUp(_FALSE);
#endif
    ScalerFlashWRDis();
    ScalerFwUpdateExit();
}

//---------------------------------------------------------
// Description  : Background Fw Update Set Data Packet Length
// Input Value  : None
// Output Value : None
//---------------------------------------------------------
void UserCommonFwUpdateBackgroundSetDataPacketLenProcess(void)
{
    WORD usPageCount = (WORD)((WORD)(g_pucFwUpdateRxBuf[2] << 8) | g_pucFwUpdateRxBuf[3]);

#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
    if(((_DUAL_BANK_USER_FW_CODE_SIZE * 65536) % usPageCount) != 0)
    {
        ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
#endif
    g_stFwUpdateUserCommonInfo.usIspPageCount = usPageCount;
#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
    ScalerFwUpdateMdofiySpeedUpIspLen(usPageCount);
#endif
    ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);
}

//-----------------------------------------------------------------------------
// Description  : Urgent IP Process when FW Background Update Start/Finish
// Input Value  : enumStatus :_FW_UPDATE_START/_FW_UPDATE_END
// Output Value : None
//------------------------------------------------------------------------------
void UserCommonFwUpdateBackgroundUrgentIpProc(EnumBackgroundFwUpdateStatus enumStatus)
{
    if(enumStatus == _FW_UPDATE_START)
    {
        // _FW_UPDATE_START
    }
    else
    {
        // _FW_UPDATE_END
    }
}
#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Project ID Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonFwUpdateBackgroundGetProjectIDAddrProcess(void)
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
void UserCommonFwUpdateBackgroundVerifyProjectIDProcess(void)
{
    EnumProjectIDVerifyResult enumResult = _ISP_FW_CHECK_VERIFY_FAIL;

    enumResult = ScalerFwCheckProjectIDVerify(&g_pucFwUpdateRxBuf[2]);
    if(enumResult == _ISP_FW_CHECK_VERIFY_FAIL)
    {
        UserCommonFwUpdateBackgroundExitProcess();
        ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_FAIL);
        return;
    }
    SET_FW_UPDATE_VERIFY_ID_PASS(_TRUE);
    // Send Data
    ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);
}
#endif

#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
//--------------------------------------------------
// Description  : Fw Update Write Key and Signature Data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonFwUpdateBackgroundWriteKeyAndSignatureData(void)
{
    BYTE pucReadBuf[_HW_DDCCI_BUF_SIZE];
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
                ScalerFlashWriteByKernel(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, g_stFwUpdateUserCommonInfo.usIspPageCount, &g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX], _TRUE, _FALSE);
                // Read Check
                memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, g_stFwUpdateUserCommonInfo.usIspPageCount, pucReadBuf);
                if(memcmp(&g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX], pucReadBuf, g_stFwUpdateUserCommonInfo.usIspPageCount) != 0)
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
                    ScalerFlashWriteByKernel(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, &g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX], _TRUE, _FALSE);
                    // Read Check
                    memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                    UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, pucReadBuf);
                    if(memcmp(&g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX], pucReadBuf, usTmpKeyLen) != 0)
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
                    ScalerFlashWriteByKernel(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpSigLen, &g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX + usTmpKeyLen], _TRUE, _FALSE);
                    // Read Check
                    memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                    UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpSigLen, pucReadBuf);
                    if(memcmp(&g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX + usTmpKeyLen], pucReadBuf, usTmpSigLen) != 0)
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
                    ScalerFlashWriteByKernel(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, g_stFwUpdateUserCommonInfo.usIspPageCount, &g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX], _TRUE, _FALSE);
                    // Read Check
                    UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, g_stFwUpdateUserCommonInfo.usIspPageCount, pucReadBuf);
                    if(memcmp(&g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX], pucReadBuf, g_stFwUpdateUserCommonInfo.usIspPageCount) != 0)
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
                        ScalerFlashWriteByKernel(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpSigLen, &g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX], _TRUE, _FALSE);
                        // Read Check
                        memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                        UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpSigLen, pucReadBuf);
                        if(memcmp(&g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX], pucReadBuf, usTmpSigLen) != 0)
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
                ScalerFlashWriteByKernel(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, &g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX + _DIGITAL_SIGNATURE_INFO_HEADER_SIZE], _TRUE, _FALSE);
                // Read Check
                memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, pucReadBuf);
                if(memcmp(&g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX + _DIGITAL_SIGNATURE_INFO_HEADER_SIZE], pucReadBuf, usTmpKeyLen) != 0)
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
                ScalerFlashWriteByKernel(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, &g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX + usTmpSigLen], _TRUE, _FALSE);
                // Read Check
                memset(pucReadBuf, 0xFF, sizeof(pucReadBuf));
                UserCommonFlashRead(g_stFwUpdateUserCommonInfo.stUserDataInfo.usUserDataBank, usCurrentAddress, usTmpKeyLen, pucReadBuf);
                if(memcmp(&g_pucFwUpdateRxBuf[_FW_UPDATE_DATA_START_INDEX + usTmpSigLen], pucReadBuf, usTmpKeyLen) != 0)
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


#endif

