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
// ID Code      : UserCommonDualBankUser.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "UserCommonInclude.h"
#include "dualbank/UserCommonDualBankUser.h"


#if((_DUAL_BANK_FLASH_PARTITION_SUPPORT == _ON) &&\
    (_DUAL_BANK_TYPE == _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE) &&\
    (_DUAL_BANK_USER_FLAG_LOCATION_AREA != _DUAL_BANK_FLAG_LOCATION_IN_NONE_FW))
#warning "NOTE: Please check _DUAL_BANK_FLASH_PARTITION_DEFAULT_CODE_TABLE should be all 0xFF or equal _DUAL_BANK_FLASH_PARTITION_USER_FLAG_DATA!!"
#endif

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)

#if(_DUAL_BANK_BUNDLE_VERSION_SUPPORT == _ON)
#if((_DUAL_BANK_USER_I_FW_BANK_START <= _DUAL_BANK_BUNDLE_VERSION_LOCATE_BANK) && (_DUAL_BANK_BUNDLE_VERSION_LOCATE_BANK <= _DUAL_BANK_USER_II_FW_BANK_END))
#warning "_DUAL_BANK_USER_I_FW_BANK_START Should not in Fw Area!!!"
#endif

#if((_DUAL_BANK_BUNDLE_VERSION_LOCATE_BANK == _DUAL_BANK_USER_I_USER_DATA_BANK_ADDR) &&\
    ((_DUAL_BANK_USER_I_DATA_SECTOR_START <= _DUAL_BANK_BUNDLE_VERSION_LOCATE_SECTOR) &&\
    (_DUAL_BANK_USER_I_DATA_SECTOR_END >= _DUAL_BANK_BUNDLE_VERSION_LOCATE_SECTOR)))
#warning "_DUAL_BANK_BUNDLE_VERSION_LOCATE_SECTOR Confict with _DUAL_BANK_USER_I_DATA_SECTOR!!!"
#endif

#if((_DUAL_BANK_BUNDLE_VERSION_LOCATE_BANK == _DUAL_BANK_USER_II_USER_DATA_BANK_ADDR) &&\
    ((_DUAL_BANK_USER_II_DATA_SECTOR_START <= _DUAL_BANK_BUNDLE_VERSION_LOCATE_SECTOR) &&\
    (_DUAL_BANK_USER_II_DATA_SECTOR_END >= _DUAL_BANK_BUNDLE_VERSION_LOCATE_SECTOR)))
#warning "_DUAL_BANK_BUNDLE_VERSION_LOCATE_SECTOR Confict with _DUAL_BANK_USER_II_DATA_SECTOR!!!"
#endif
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dual Bank Boot debug process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDualBankUserHandler(void)
{
    BYTE pucDdcciOutData[_DUAL_BANK_OUT_DATA_MAX_LEN];
    BYTE ucSubOpCode = 0;
    BYTE ucOpCode = 0;
    BYTE ucLength = 0;
#if(_DUAL_BANK_TYPE != _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE)
    WORD usIspStartBank = 0;
    DWORD ulAddress = 0;
#endif

#if((_BILLBOARD_SCALER_SUPPORT == _ON) && (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON))
    if((GET_USB_BB_ISP_REV_CMD_STATUS() == _TRUE) && (GET_USB_BB_ISP_OPCODE() == _USB_VENDOR_DUAL_BANK_PROCESS))
    {
        ucOpCode = GET_USB_BB_ISP_OPCODE();
        ucSubOpCode = GET_USB_BB_ISP_SUB_OPCODE();
    }
    else
#endif
    {
        if(!ScalerDebugDualBankGetDebugInfo(&ucOpCode, &ucSubOpCode))
        {
            return;
        }
    }

    switch(ucSubOpCode)
    {
        case _SCALER_BOOT_ENABLE_ISP_CHANNEL_OP_CODE:
            DebugMessageSystem("rev enable isp channel", _SCALER_BOOT_ENABLE_ISP_CHANNEL_OP_CODE);
            UserCommonDualBankUserEnableISPChannel();
            ucLength = 2;
            pucDdcciOutData[0] = ucOpCode;
            pucDdcciOutData[1] = 0;
            break;

#if(_DUAL_BANK_TYPE != _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE)
        case _SCALER_BOOT_GET_ISP_START_ADDR_OP_CODE:
            ucLength = 5;
            usIspStartBank = UserCommonDualBankUserGetIspStartBank();
            pucDdcciOutData[0] = ucOpCode;
            pucDdcciOutData[1] = LOBYTE(usIspStartBank);
            pucDdcciOutData[2] = HIBYTE(usIspStartBank);
            pucDdcciOutData[3] = _DUAL_BANK_USER_FW_CODE_SIZE;
            pucDdcciOutData[4] = 0;
            DebugMessageSystem("rev isp start", pucDdcciOutData[1]);
            break;

        case _SCALER_BOOT_GET_ISP_USER_KEY_ADDR_OP_CODE:
            ucLength = 5;
            ulAddress = UserCommonDualBankUserGetIspKeyAddr();
            pucDdcciOutData[0] = ucOpCode;
            pucDdcciOutData[1] = (BYTE)((ulAddress >> 24) & 0xFF);
            pucDdcciOutData[2] = (BYTE)((ulAddress >> 16) & 0xFF);
            pucDdcciOutData[3] = (BYTE)((ulAddress >> 8) & 0xFF);
            pucDdcciOutData[4] = (BYTE)(ulAddress & 0xFF);
            DebugMessageSystem("rev key start", ulAddress);
            break;

        case _SCALER_BOOT_GET_ISP_USER_FLAG_ADDR_OP_CODE:
            ucLength = 5;
            ulAddress = UserCommonDualBankUserGetIspFlagAddr();
            pucDdcciOutData[0] = ucOpCode;
            pucDdcciOutData[1] = (BYTE)((ulAddress >> 24) & 0xFF);
            pucDdcciOutData[2] = (BYTE)((ulAddress >> 16) & 0xFF);
            pucDdcciOutData[3] = (BYTE)((ulAddress >> 8) & 0xFF);
            pucDdcciOutData[4] = (BYTE)(ulAddress & 0xFF);
            DebugMessageSystem("rev flag start", ulAddress);
            break;

        case _SCALER_BOOT_GET_ISP_USER_SIGN_ADDR_OP_CODE:
            ucLength = 5;
            ulAddress = UserCommonDualBankUserGetIspSignatureAddr();
            pucDdcciOutData[0] = ucOpCode;
            pucDdcciOutData[1] = (BYTE)((ulAddress >> 24) & 0xFF);
            pucDdcciOutData[2] = (BYTE)((ulAddress >> 16) & 0xFF);
            pucDdcciOutData[3] = (BYTE)((ulAddress >> 8) & 0xFF);
            pucDdcciOutData[4] = (BYTE)(ulAddress & 0xFF);
            DebugMessageSystem("rev signature start", ulAddress);
            break;

        case _SCALER_BOOT_GET_VERIFY_COPY_RESULT_OP_CODE:
            ucLength = 2;
            pucDdcciOutData[0] = ucOpCode;
            pucDdcciOutData[1] = UserCommonDualBankUserGetVerifyCopyResult();
            DebugMessageSystem("rev result", pucDdcciOutData[1]);
            break;

        case _SCALER_BOOT_SWITCH_CODE_OP_CODE:
            break;

        case _SCALER_BOOT_GET_ISP_CURRENT_KEY_ADDR_OP_CODE:
            ucLength = 5;
            ulAddress = UserCommonDualBankUserGetCurrentKeyAddr();
            pucDdcciOutData[0] = ucOpCode;
            pucDdcciOutData[1] = (BYTE)((ulAddress >> 24) & 0xFF);
            pucDdcciOutData[2] = (BYTE)((ulAddress >> 16) & 0xFF);
            pucDdcciOutData[3] = (BYTE)((ulAddress >> 8) & 0xFF);
            pucDdcciOutData[4] = (BYTE)(ulAddress & 0xFF);
            DebugMessageSystem("Current key start", ulAddress);
            break;
#endif
        case _SCALER_BOOT_GET_DUAL_BANK_INFO_OP_CODE:
            ucLength = 11;
            pucDdcciOutData[0] = ucOpCode;
            UserCommonDualBankUserGetFwInfo(&pucDdcciOutData[1]);
            break;

#if(_DUAL_BANK_BUNDLE_VERSION_SUPPORT == _ON)
        case _SCALER_BOOT_GET_DUAL_BANK_BUNDLE_VERSION_OP_CODE:
            pucDdcciOutData[0] = ucOpCode;
            UserCommonDualBankUserGetBundleVersion(&pucDdcciOutData[1]);
            ucLength = pucDdcciOutData[1] + 2;
            break;

        case _SCALER_BOOT_SET_DUAL_BANK_BUNDLE_VERSION_OP_CODE:
            ucLength = 0x02;
            pucDdcciOutData[0] = ucOpCode;
            pucDdcciOutData[1] = UserCommonDualBankUserUpdateBundleVersion();
            break;
#endif

        default:
            ucLength = 2;
            pucDdcciOutData[0] = ucOpCode;
            pucDdcciOutData[1] = 0xEE;
            DebugMessageSystem("rev unknown", ucOpCode);
            break;
    }
#if((_BILLBOARD_SCALER_SUPPORT == _ON) && (_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON))
    if((GET_USB_BB_ISP_REV_CMD_STATUS() == _TRUE) && (GET_USB_BB_ISP_OPCODE() == _USB_VENDOR_DUAL_BANK_PROCESS))
    {
        CLR_USB_BB_ISP_REV_CMD_STATUS();
        ScalerUsbBillboardCopyISPInfo(pucDdcciOutData, ucLength, _TRUE);
    }
    else
#endif
    {
        ScalerDebugSendData(ucLength, pucDdcciOutData);
        ScalerDebugDualBankSetDebugInfo(_FALSE, ucOpCode, ucSubOpCode);
    }
}

//--------------------------------------------------
// Description  : Enable ISP Channel
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDualBankUserEnableISPChannel(void)
{
#if(_ISP_CHANNEL_PROTECT_SUPPORT == _ON)
    ScalerMcuSetISPChannel(_ISP_CHANNEL_EN_FW_UPDATE);
    ScalerMcuSetISPSlaveAddr(_ENABLE);
#endif
}

#if(_DUAL_BANK_TYPE != _DUAL_BANK_FLASH_PARTITION_USER_FLAG_MODE)
//--------------------------------------------------
// Description  : Get to be program region information
// Input Value  : None
// Output Value : to be program user start bank
//--------------------------------------------------
WORD UserCommonDualBankUserGetIspStartBank(void)
{
    WORD usIspBank = 0;
#if(_DUAL_BANK_TYPE != _DUAL_BANK_FLASH_PARTITION)
    WORD usCurBank = ScalerDualBankUserGetKCPUBankOffset();

    if((usCurBank >= _DUAL_BANK_USER_I_FW_BANK_START) && (usCurBank <= _DUAL_BANK_USER_I_FW_BANK_END))
    {
        usIspBank = _DUAL_BANK_USER_II_FW_BANK_START;
    }
    else
    {
        usIspBank = _DUAL_BANK_USER_I_FW_BANK_START;
    }
#else
    usIspBank = _DUAL_BANK_USER_I_FW_BANK_START;
#endif
    return usIspBank;
}

//--------------------------------------------------
// Description  : Get to be program region information
// Input Value  : None
// Output Value : to be program user key address
//--------------------------------------------------
DWORD UserCommonDualBankUserGetIspKeyAddr(void)
{
    DWORD ulAddr = 0;
#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _OFF)
    WORD usCurBank = ScalerDualBankUserGetKCPUBankOffset();

    if((usCurBank >= _DUAL_BANK_USER_I_FW_BANK_START) && (usCurBank <= _DUAL_BANK_USER_I_FW_BANK_END))
    {
        ulAddr = (DWORD)_DUAL_BANK_USER_II_USER_DATA_BANK_ADDR << 16;
        ulAddr += _DUAL_BANK_USER_II_KEY_START_ADDR;
    }
    else
    {
        ulAddr = (DWORD)_DUAL_BANK_USER_I_USER_DATA_BANK_ADDR << 16;
        ulAddr += _DUAL_BANK_USER_I_KEY_START_ADDR;
    }
#else
    ulAddr = (DWORD)_DUAL_BANK_USER_I_USER_DATA_BANK_ADDR << 16;
    ulAddr += _DUAL_BANK_USER_I_KEY_START_ADDR;
#endif
    return ulAddr;
}

//--------------------------------------------------
// Description  : Get to be program region information
// Input Value  : None
// Output Value : to be program user flag address
//--------------------------------------------------
DWORD UserCommonDualBankUserGetIspFlagAddr(void)
{
    DWORD ulAddr = 0;
#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _OFF)
    WORD usCurBank = ScalerDualBankUserGetKCPUBankOffset();

    if((usCurBank >= _DUAL_BANK_USER_I_FW_BANK_START) && (usCurBank <= _DUAL_BANK_USER_I_FW_BANK_END))
    {
        ulAddr = (DWORD)_DUAL_BANK_USER_II_USER_DATA_BANK_ADDR << 16;
        ulAddr += _DUAL_BANK_USER_II_FLAG_START_ADDR;
    }
    else
    {
        ulAddr = (DWORD)_DUAL_BANK_USER_I_USER_DATA_BANK_ADDR << 16;
        ulAddr += _DUAL_BANK_USER_I_FLAG_START_ADDR;
    }
#else
    ulAddr = (DWORD)_DUAL_BANK_USER_I_USER_DATA_BANK_ADDR << 16;
    ulAddr += _DUAL_BANK_USER_I_FLAG_START_ADDR;
#endif
    return ulAddr;
}

//--------------------------------------------------
// Description  : Get to be program region information
// Input Value  : None
// Output Value : to be program user signature address
//--------------------------------------------------
DWORD UserCommonDualBankUserGetIspSignatureAddr(void)
{
    DWORD ulAddr = 0;
#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _OFF)
    WORD usCurBank = ScalerDualBankUserGetKCPUBankOffset();

    if((usCurBank >= _DUAL_BANK_USER_I_FW_BANK_START) && (usCurBank <= _DUAL_BANK_USER_I_FW_BANK_END))
    {
        ulAddr = (DWORD)_DUAL_BANK_USER_II_USER_DATA_BANK_ADDR << 16;
        ulAddr += _DUAL_BANK_USER_II_SIGNATURE_START_ADDR;
    }
    else
    {
        ulAddr = (DWORD)_DUAL_BANK_USER_I_USER_DATA_BANK_ADDR << 16;
        ulAddr += _DUAL_BANK_USER_I_SIGNATURE_START_ADDR;
    }
#else
    ulAddr = (DWORD)_DUAL_BANK_USER_I_USER_DATA_BANK_ADDR << 16;
    ulAddr += _DUAL_BANK_USER_I_SIGNATURE_START_ADDR;
#endif
    return ulAddr;
}


//--------------------------------------------------
// Description  : Get to be program region information
// Input Value  : None
// Output Value : Current user key address
//--------------------------------------------------
DWORD UserCommonDualBankUserGetCurrentKeyAddr(void)
{
    DWORD ulAddr = 0;
#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _OFF)
    WORD usCurBank = ScalerDualBankUserGetKCPUBankOffset();

    if((usCurBank >= _DUAL_BANK_USER_II_FW_BANK_START) && (usCurBank <= _DUAL_BANK_USER_II_FW_BANK_END))
    {
        ulAddr = (DWORD)_DUAL_BANK_USER_II_USER_DATA_BANK_ADDR << 16;
        ulAddr += _DUAL_BANK_USER_II_KEY_START_ADDR;
    }
    else
    {
        ulAddr = (DWORD)_DUAL_BANK_USER_I_USER_DATA_BANK_ADDR << 16;
        ulAddr += _DUAL_BANK_USER_I_KEY_START_ADDR;
    }
#else
    ulAddr = (DWORD)_DUAL_BANK_USER_I_USER_DATA_BANK_ADDR << 16;
    ulAddr += _DUAL_BANK_USER_I_KEY_START_ADDR;
#endif
    return ulAddr;
}

//--------------------------------------------------
// Description  : Get verify and copy result
// Input Value  : None
// Output Value : result
//--------------------------------------------------
BYTE UserCommonDualBankUserGetVerifyCopyResult(void)
{
    BYTE pucUserFlag[_DUAL_BANK_USER_FLAG_LENGTH] = {0};
    BYTE ucResult = 0;
    DWORD ulUserFlagAddr = ((DWORD)_DUAL_BANK_USER_I_USER_DATA_BANK_ADDR << 16) + _DUAL_BANK_USER_I_FLAG_START_ADDR;
    WORD usAddr = 0;

#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _OFF)
    DWORD ulUser2FlagAddr = 0;
    BYTE pucUser2Flag[_DUAL_BANK_USER_FLAG_LENGTH] = {0};

    ulUser2FlagAddr = ((DWORD)_DUAL_BANK_USER_II_USER_DATA_BANK_ADDR << 16) + _DUAL_BANK_USER_II_FLAG_START_ADDR;
    usAddr = (ulUserFlagAddr & 0xFFFF);
    ScalerFlashRead(HIWORD(ulUserFlagAddr), (BYTE *)(DWORD)usAddr, _DUAL_BANK_USER_FLAG_LENGTH, pucUserFlag);
    usAddr = (ulUser2FlagAddr & 0xFFFF);
    ScalerFlashRead(HIWORD(ulUser2FlagAddr), (BYTE *)(DWORD)usAddr, _DUAL_BANK_USER_FLAG_LENGTH, pucUser2Flag);

    // verify result
    if((pucUserFlag[_USER_FLAG_VERIFY_TAG] == _TAG_VERIFY_FW_FAIL) || (pucUser2Flag[_USER_FLAG_VERIFY_TAG] == _TAG_VERIFY_FW_FAIL))
    {
        ucResult |= 0x10;
    }
    else if(pucUserFlag[_USER_FLAG_VERIFY_TAG] == _TAG_VERIFY_FW_PASS)
    {
        ucResult |= 0x00;
    }
    else if(pucUserFlag[_USER_FLAG_VERIFY_TAG] == _TAG_VERIFY_FW_NONE)
    {
        ucResult |= 0x20;
    }
    else
    {
        ucResult |= 0x30;
    }

#else
    if(ulUserFlagAddr == 0xFFFF)
    {
        ucResult = 0x32;
        return ucResult;
    }

    // read user tag
    usAddr = (ulUserFlagAddr & 0xFFFF);
    ScalerFlashRead(HIWORD(ulUserFlagAddr), (BYTE *)(DWORD)usAddr, _DUAL_BANK_USER_FLAG_LENGTH, pucUserFlag);
    // verify result
    if(pucUserFlag[_USER_FLAG_VERIFY_TAG] == _TAG_VERIFY_FW_PASS)
    {
        ucResult |= 0x00;
    }
    else if(pucUserFlag[_USER_FLAG_VERIFY_TAG] == _TAG_VERIFY_FW_FAIL)
    {
        ucResult |= 0x10;
    }
    else if(pucUserFlag[_USER_FLAG_VERIFY_TAG] == _TAG_VERIFY_FW_NONE)
    {
        ucResult |= 0x20;
    }
    else
    {
        ucResult |= 0x30;
    }
#endif
    // copy result
    if(pucUserFlag[_USER_FLAG_COPY_TAG] == _TAG_COPY_FW_PASS)
    {
        ucResult |= 0x00;
    }
    else if(pucUserFlag[_USER_FLAG_COPY_TAG] == _TAG_COPY_FW_NONE)
    {
        ucResult |= 0x01;
    }
    else
    {
        ucResult |= 0x02;
    }
    return ucResult;
}
#endif

//--------------------------------------------------
// Description  : Get Duanl bank Info
// Dual Bank Type, Current Area, Version
// Input Value  : None
// Output Value : Duanl Bank Info 6 Byte
//--------------------------------------------------
void UserCommonDualBankUserGetFwInfo(BYTE *pucArry)
{
    WORD usCurBank = ScalerDualBankUserGetKCPUBankOffset();

    // Byte Count
    pucArry[0] = 9;

    // Dual bank Support
    pucArry[1] = _DUAL_BANK_SUPPORT;

    // Dual bank Type
    pucArry[2] = _DUAL_BANK_TYPE;

    // Active User(1) + User1 Version(2) + User2 Version(2) + Reserved(2)
    // Active User(1)
    if((usCurBank >= _DUAL_BANK_USER_I_FW_BANK_START) && (usCurBank <= _DUAL_BANK_USER_I_FW_BANK_END))
    {
        pucArry[3] = _REGION_USER_I - 1;
    }
#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _OFF)
    else if((usCurBank >= _DUAL_BANK_USER_II_FW_BANK_START) && (usCurBank <= _DUAL_BANK_USER_II_FW_BANK_END))
    {
        pucArry[3] = _REGION_USER_II - 1;
    }
#endif
    else
    {
        pucArry[3] = _REGION_BOOT - 1;
    }
    memset(&pucArry[4], 0xFFU, 6);

#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
    // User 2 Version
    ScalerFlashRead(_DUAL_BANK_USER_I_FW_BANK_START + _CUSTOMER_FW_VERSION_LOCATE_BANK, (BYTE *)_CUSTOMER_FW_VERSION_LOCATE_ADDRESS, 2, &pucArry[4]);
#if(_DUAL_BANK_FLASH_PARTITION_SUPPORT == _OFF)
    ScalerFlashRead(_DUAL_BANK_USER_II_FW_BANK_START + _CUSTOMER_FW_VERSION_LOCATE_BANK, (BYTE *)_CUSTOMER_FW_VERSION_LOCATE_ADDRESS, 2, &pucArry[6]);
#endif
#endif

#if(_DIGITAL_SIGNATURE_SUPPORT == _OFF)
    pucArry[8] = 0x00;
#else
#if(_DIGITAL_SIGNATURE_HW_RSA_TYPE == _DIGITAL_SIGNATURE_RSA_512)
    pucArry[8] = (_DIGITAL_SIGNATURE_TYPE << 4) | 0;
#elif(_DIGITAL_SIGNATURE_HW_RSA_TYPE == _DIGITAL_SIGNATURE_RSA_1024)
    pucArry[8] = (_DIGITAL_SIGNATURE_TYPE << 4) | 1;
#elif(_DIGITAL_SIGNATURE_HW_RSA_TYPE == _DIGITAL_SIGNATURE_RSA_2048)
    pucArry[8] = (_DIGITAL_SIGNATURE_TYPE << 4) | 2;
#elif(_DIGITAL_SIGNATURE_HW_RSA_TYPE == _DIGITAL_SIGNATURE_RSA_3072)
    pucArry[8] = (_DIGITAL_SIGNATURE_TYPE << 4) | 3;
#endif
#endif
}

//--------------------------------------------------
// Description  : Get KCPU Flash Bank Offset
// Input Value  : None
// Output Value : BankIndex
//--------------------------------------------------
WORD UserCommonDualBankUserGetKCPUBankOffset(void)
{
    return ScalerDualBankUserGetKCPUBankOffset();
}

#if(_DUAL_BANK_BUNDLE_VERSION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Merge Fw Info
// Input Value  : None
// Output Value : N Bytes Fw info
//--------------------------------------------------
void UserCommonDualBankUserGetBundleVersion(BYTE *pucArry)
{
    WORD usReadAddr = (WORD)((_DUAL_BANK_BUNDLE_VERSION_LOCATE_SECTOR) << 12);

    pucArry[0] = _DUAL_BANK_BUNDLE_VERSION_COUNT;
    ScalerFlashRead(_DUAL_BANK_BUNDLE_VERSION_LOCATE_BANK, (BYTE *)(DWORD)usReadAddr, _DUAL_BANK_BUNDLE_VERSION_COUNT, pucArry + 1);
}

//--------------------------------------------------
// Description  : isp Duanl bank bundle version Info
// Input Value  : None
// Output Value : success or fail
//--------------------------------------------------
EnumISPBundleVerResult UserCommonDualBankUserUpdateBundleVersion(void)
{
    return ScalerDebugUpdateBundleVersion();
}
#endif // #if(_DUAL_BANK_BUNDLE_VERSION_SUPPORT == _ON)

#endif

#if(_ISP_CHANNEL_PROTECT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : ISP Channel Setting
// Input Value  : ISPChannel -> VGA_DDC: _BIT0; DDC0: _BIT1; DDC1: _BIT2;... DDC5: _BIT6;
//                _NO_DDC: _BIT7; VGA_DDC2: _BIT8
// Output Value : NONE
//--------------------------------------------------
void UserCommonDualBankUserSetISPChannel(WORD usISPChannel)
{
    ScalerMcuSetISPChannel(usISPChannel);
}

//--------------------------------------------------
// Description  : Modify ISP addr
// Input Value :_ISP_SLAVE_ENABLE: Normal Slave Address
//                _ISP_SLAVE_DISABLE: Error Slave Address
// Output Value : NONE
//--------------------------------------------------
void UserCommonDualBankUserSetISPSlaveAddr(EnumIspSlaveAddrState enumISPStatus)
{
    ScalerMcuSetISPSlaveAddr(enumISPStatus);
}
#endif

