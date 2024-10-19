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
// ID Code      : ScalerReg.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_REG__

#include "ScalerFunctionInclude.h"
#include "Reg/ScalerReg.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
DWORD g_ulSrcEndFlashAddr32;

__attribute__((section(".fast_data.pData")))
BYTE pData[16] = {0};


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Calculate OSD Burst Write Timeout
// Input Value  :
// Output Value : Burst Write Required Time
//--------------------------------------------------
BYTE ScalerBurstWriteTimeoutCal(void)
{
    WORD usTimeout = 0;
    BYTE ucPath = 1;

    switch(GET_D_DOMAIN_PATH())
    {
        default:
        case _D_DOMAIN_1_PATH:
            ucPath = 1;
            break;
        case _D_DOMAIN_2_PATH:
            ucPath = 2;
            break;
        case _D_DOMAIN_4_PATH:
            ucPath = 4;
            break;
    }

    // Time of MCU Write Cycle > 32 x TDCLK
    // => Tm2pll x Flash Div x Mcu Div x (0xFFFB x 2 + 4) > 32 x TDCLK
    // => 0xFFFB > 32 x TDCLK / (2 x Tm2pll x Flash Div x Mcu Div) - 2
    usTimeout = (DWORD)16 * _M2PLL_CLK_MHZ * 1000 * ucPath / ((DWORD)GET_D_CLK_FREQ() * _FLASH_CLK_DIV * _MCU_CLK_DIV);

    if(usTimeout >= 2)
    {
        usTimeout -= 2;
    }

    if(usTimeout > 0xFF)
    {
        return 0xFF;
    }

    return (BYTE)usTimeout;
}

//--------------------------------------------------
// Description  : Set some bits of selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ucAnd     --> & operation
// Output Value : Value after & operation
//--------------------------------------------------
void ScalerBurstWrite(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, WORD usHostAddr, BYTE ucTableType, bit bTableLocation)
{
    DWORD ulSrcAddr32 = (DWORD)pucAddress;
    DWORD ulEndAddr32 = g_ulSrcEndFlashAddr32;
    // Check if Use Absolute Flash Address
    if((bTableLocation == _BURSTWRITE_FROM_FLASH) &&
       (ucBankNum != GET_CURRENT_BANK_NUMBER()))
    {
        // Use Absolute Flash Address
        // Convert 24bits Absolute Flash Address to 32bits mapping address
        ulSrcAddr32 = ((((DWORD)ucBankNum) << 16) | ulSrcAddr32);
        if((ulEndAddr32 > ulSrcAddr32) && ((ulEndAddr32 - ulSrcAddr32) < 32))
        {
            ScalerBurstWriteByFW(pucAddress, usWriteLength, usHostAddr, ucTableType);
            return;
        }
        g_ulSrcEndFlashAddr32 = ulSrcAddr32 + usWriteLength - 1;
    }
    else
    {
        switch(ScalerUtilGetAddressType(ulSrcAddr32))
        {
            case _ADDRESS_TYPE_XRAM:
                ulSrcAddr32 = GET_PHY_XRAM_ADDR(ulSrcAddr32);
                break;

            case _ADDRESS_TYPE_FLASH:
                if(ScalerCpuHalGetPhyFlashAddress(ulSrcAddr32, &ulSrcAddr32) != _TRUE)
                {
                    DebugMessageScaler("BurstWrite Flash Phy Flash Addr < FlashBankOffset", ulSrcAddr32);
                    return;
                }
                if((ulEndAddr32 > ulSrcAddr32) && ((ulEndAddr32 - ulSrcAddr32) < 32))
                {
                    ScalerBurstWriteByFW(pucAddress, usWriteLength, usHostAddr, ucTableType);
                    return;
                }
                g_ulSrcEndFlashAddr32 = ulSrcAddr32 + usWriteLength - 1;
                ucBankNum = (BYTE)(ulSrcAddr32 >> 16);
                break;

            default:
                ScalerBurstWriteByFW(pucAddress, usWriteLength, usHostAddr, ucTableType);
                return;
        }
    }

    pucAddress = (BYTE *)ulSrcAddr32;

    {
        // acquire burst write lock
        GET_BURST_WRITE_LOCK();

        MCU_FFF4_SCA_INF_ADDR = 0x9F;
        MCU_FFF5_SCA_INF_DATA = HIBYTE(usHostAddr);

        // Disable burst write data and burst write command function.
        MCU_FFF3_SCA_INF_CONTROL &= 0xE7;

        // Disable Burst write Auto Inc
        MCU_FFF3_SCA_INF_CONTROL |= _BIT5;

        if((ucTableType == _BURSTWRITE_DATA_COMMON) || (ucTableType == _BURSTWRITE_DATA_COMMON_AUTO_INC) || (ucTableType == _BURSTWRITE_DATA_OSD))
        {
            MCU_FFF4_SCA_INF_ADDR = usHostAddr;
        }

        MCU_FFF6_SCA_INF_BWR_ADRH = ucBankNum;

        MCU_FFF7_SCA_INF_BWR_ADRM = HIBYTE((DWORD)pucAddress);
        MCU_FFF8_SCA_INF_BWR_ADRL = LOBYTE((DWORD)pucAddress);

        MCU_FFF9_SCA_INF_BWR_COUNT_H = (BYTE)(((usWriteLength) & 0xFF00) >> 8);
        MCU_FFFA_SCA_INF_BWR_COUNT_L = (BYTE)(((usWriteLength) & 0x00FF));

        if(ucTableType == _BURSTWRITE_DATA_OSD)
        {
            BYTE ucData = 0;

            ucData = ScalerBurstWriteTimeoutCal();

            if(ucData >= 2)
            {
                // Set the interval between two command for OSD Load Font data.
                MCU_FFFB_SCA_INF_PERIOD = ucData;
            }
            else
            {
                MCU_FFFB_SCA_INF_PERIOD = 0x02;
            }
        }
        else
        {
            MCU_FFFB_SCA_INF_PERIOD = 0x03;
        }

        MCU_FFFC_BANK_SWICH_CONTROL |= (_BIT5 & (((BYTE)bTableLocation) << 5));

        if(ucTableType == _BURSTWRITE_COMMAND)
        {
            // Enable burst write command function, disable the function of releasing mcu by interrupt.
            MCU_FFF3_SCA_INF_CONTROL = 0x12;

            // polling Burst Write Finish 100 ms
            ScalerTimerPollingFlagProc(100, PFF_F3_SCA_INF_CONTROL, _BIT4, _FALSE);
        }
        else  // _BURSTWRITE_DATA_COMMON/OSD
        {
            if(ucTableType == _BURSTWRITE_DATA_COMMON_AUTO_INC)
            {
                // Enable burst write data function, enable auto address increase, disable the function of releasing mcu by interrupt.
                MCU_FFF3_SCA_INF_CONTROL = 0x0A;
            }
            else
            {
                // Enable burst write data function, disable auto address increase, disable the function of releasing mcu by interrupt.
                MCU_FFF3_SCA_INF_CONTROL = 0x2A;
            }

            // polling Burst Write Finish 100 ms
            ScalerTimerPollingFlagProc(100, PFF_F3_SCA_INF_CONTROL, _BIT3, _FALSE);
        }

        // disable burst data from int xram.
        MCU_FFFC_BANK_SWICH_CONTROL &= ~_BIT5;

        // release burst write lock
        CLR_BURST_WRITE_LOCK();
    }
}

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : ScalerBurstWrite in 4byte mode
// Input Value  : pucAddress    --> Byte Pointer to Source Table
//                usWriteLength --> Source Table length (by byte)
//                usHostAddr    --> Destination 16bits XDATA Space Reg
//                ucTableType   --> Source Table Type
// Output Value : None
//--------------------------------------------------
void ScalerBurstWrite4ByteMode(BYTE *pucAddress, WORD usWriteLength, WORD usHostAddr, BYTE ucTableType, bit bTableLocation)
{
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        WORD usBankNum = 0;
        DWORD ulSrcAddr32 = (DWORD)pucAddress;
        DWORD ulEndAddr32 = g_ulSrcEndFlashAddr32;

        switch(ScalerUtilGetAddressType(ulSrcAddr32))
        {
            case _ADDRESS_TYPE_XRAM:
                ulSrcAddr32 = GET_PHY_XRAM_ADDR(ulSrcAddr32);
                break;

            case _ADDRESS_TYPE_FLASH:
                if(ScalerCpuHalGetPhyFlashAddress(ulSrcAddr32, &ulSrcAddr32) != _TRUE)
                {
                    DebugMessageScaler("BurstWrite4B Flash Phy Flash Addr < FlashBankOffset", ulSrcAddr32);
                    return;
                }
                if((ulEndAddr32 > ulSrcAddr32) && ((ulEndAddr32 - ulSrcAddr32) < 32))
                {
                    ScalerBurstWriteByFW(pucAddress, usWriteLength, usHostAddr, ucTableType);
                    return;
                }
                g_ulSrcEndFlashAddr32 = ulSrcAddr32 + usWriteLength - 1;
                usBankNum = (WORD)(ulSrcAddr32 >> 16);
                break;

            default:
                ScalerBurstWriteByFW(pucAddress, usWriteLength, usHostAddr, ucTableType);
                return;
        }

        pucAddress = (BYTE *)ulSrcAddr32;

        // acquire burst write lock
        GET_BURST_WRITE_LOCK();

        MCU_FFF4_SCA_INF_ADDR = 0x9F;
        MCU_FFF5_SCA_INF_DATA = HIBYTE(usHostAddr);

        // Disable burst write data and burst write command function.
        MCU_FFF3_SCA_INF_CONTROL &= 0xE7;

        // Disable Burst write Auto Inc
        MCU_FFF3_SCA_INF_CONTROL |= _BIT5;

        if((ucTableType == _BURSTWRITE_DATA_COMMON) || (ucTableType == _BURSTWRITE_DATA_COMMON_AUTO_INC) || (ucTableType == _BURSTWRITE_DATA_OSD))
        {
            MCU_FFF4_SCA_INF_ADDR = usHostAddr;
        }

        MCU_FFBA_SCA_INF_BWR_ADR_4TH = HIBYTE(usBankNum);
        MCU_FFF6_SCA_INF_BWR_ADRH = (BYTE)usBankNum;

        MCU_FFF7_SCA_INF_BWR_ADRM = HIBYTE((DWORD)pucAddress);
        MCU_FFF8_SCA_INF_BWR_ADRL = LOBYTE((DWORD)pucAddress);

        MCU_FFF9_SCA_INF_BWR_COUNT_H = (BYTE)(((usWriteLength) & 0xFF00) >> 8);
        MCU_FFFA_SCA_INF_BWR_COUNT_L = (BYTE)(((usWriteLength) & 0x00FF));

        if(ucTableType == _BURSTWRITE_DATA_OSD)
        {
            BYTE ucData = 0;

            ucData = ScalerBurstWriteTimeoutCal();

            if(ucData >= 2)
            {
                // Set the interval between two command for OSD Load Font data.
                MCU_FFFB_SCA_INF_PERIOD = ucData;
            }
            else
            {
                MCU_FFFB_SCA_INF_PERIOD = 0x02;
            }
        }
        else
        {
            MCU_FFFB_SCA_INF_PERIOD = 0x03;
        }

        MCU_FFFC_BANK_SWICH_CONTROL |= (_BIT5 & (((BYTE)bTableLocation) << 5));

        if(ucTableType == _BURSTWRITE_COMMAND)
        {
            // Enable burst write command function, disable the function of releasing mcu by interrupt.
            MCU_FFF3_SCA_INF_CONTROL = 0x12;

            // polling Burst Write Finish 100 ms
            ScalerTimerPollingFlagProc(100, PFF_F3_SCA_INF_CONTROL, _BIT4, _FALSE);
        }
        else  // _BURSTWRITE_DATA_COMMON/OSD
        {
            if(ucTableType == _BURSTWRITE_DATA_COMMON_AUTO_INC)
            {
                // Enable burst write data function, enable auto address increase, disable the function of releasing mcu by interrupt.
                MCU_FFF3_SCA_INF_CONTROL = 0x0A;
            }
            else
            {
                // Enable burst write data function, disable auto address increase, disable the function of releasing mcu by interrupt.
                MCU_FFF3_SCA_INF_CONTROL = 0x2A;
            }

            // polling Burst Write Finish 100 ms
            ScalerTimerPollingFlagProc(100, PFF_F3_SCA_INF_CONTROL, _BIT3, _FALSE);
        }

        // disable burst data from int xram.
        MCU_FFFC_BANK_SWICH_CONTROL &= ~_BIT5;

        // release burst write lock
        CLR_BURST_WRITE_LOCK();
    }
    else
    {
        ScalerBurstWriteByFW(pucAddress, usWriteLength, usHostAddr, ucTableType);
    }
}
#endif

//--------------------------------------------------
// Description  : ScalerBurstWrite simulated by FW
// Input Value  : pucAddress    --> Byte Pointer to Source Table
//                usWriteLength --> Source Table length (by byte)
//                usHostAddr    --> Destination 16bits XDATA Space Reg
//                ucTableType   --> Source Table Type
// Output Value : None
//--------------------------------------------------
void ScalerBurstWriteByFW(BYTE *pucAddress, WORD usWriteLength, WORD usHostAddr, BYTE ucTableType)
{
    WORD usTmpDataIdx = 0;
    BYTE ucTmpCmdLength = 0;
    BYTE ucTmpCmdType = 0;
    BYTE ucTmpCmdAddrH = HIBYTE(usHostAddr);
    WORD usTmpCmdAddr = 0;

    // BurstWrite all from ram (org from flash/xram)


    if(ucTableType == _BURSTWRITE_COMMAND)
    {
        // _BURSTWRITE_COMMAND
        // write command table
        usTmpDataIdx = 0;
        while(usTmpDataIdx < usWriteLength)
        {
            ucTmpCmdLength = pucAddress[usTmpDataIdx];
            if(ucTmpCmdLength < 4)
            {
                return;
            }
            ucTmpCmdType = pucAddress[usTmpDataIdx + 1];
            if(pucAddress[usTmpDataIdx + 2] == 0x9F)
            {
                ucTmpCmdAddrH = pucAddress[usTmpDataIdx + 3];
                usTmpDataIdx += ucTmpCmdLength;
                continue;
            }
            else
            {
                usTmpCmdAddr = (((WORD)ucTmpCmdAddrH) << 8) + pucAddress[usTmpDataIdx + 2];
            }

            if(ucTmpCmdType == _AUTOINC)
            {
                ScalerWrite(usTmpCmdAddr, (ucTmpCmdLength - 3), &pucAddress[usTmpDataIdx + 3], _AUTOINC);
            }
            else
            {
                ScalerWrite(usTmpCmdAddr, (ucTmpCmdLength - 3), &pucAddress[usTmpDataIdx + 3], _NON_AUTOINC);
            }
            usTmpDataIdx += ucTmpCmdLength;
        }
    }
    else  // _BURSTWRITE_DATA_COMMON/OSD
    {
        if(ucTableType == _BURSTWRITE_DATA_COMMON_AUTO_INC)
        {
            // _BURSTWRITE_DATA_COMMON_AUTO_INC
            // Enable burst write data function, enable auto address increase, enable the function of releasing mcu by interrupt.
            ScalerWrite(usHostAddr, usWriteLength, pucAddress, _AUTOINC);
        }
        else if(ucTableType == _BURSTWRITE_DATA_OSD)
        {
            // _BURSTWRITE_DATA_OSD
            // Enable burst write data function, disable auto address increase, enable the function of releasing mcu by interrupt.
            // _BURSTWRITE_DATA_COMMON or _BURSTWRITE_DATA_OSD
            // ScalerWrite(usHostAddr,usWriteLength,pucAddress,_NON_AUTOINC);

            if(usWriteLength != 0)
            {
                WORD usIndex = 0;

                for(usIndex = 0; usIndex < usWriteLength; usIndex++)
                {
                    Scaler32SetDWord(GET_XDATA_REG_32BIT_ADDR(usHostAddr), (DWORD)pucAddress[usIndex]);
                    // ScalerTimerDelayXms(1);
                }
            }
        }
        else
        {
            // _BURSTWRITE_DATA_COMMON
            // Enable burst write data function, disable auto address increase, enable the function of releasing mcu by interrupt.
            // _BURSTWRITE_DATA_COMMON or _BURSTWRITE_DATA_OSD
            ScalerWrite(usHostAddr, usWriteLength, pucAddress, _NON_AUTOINC);
        }
    }
}

//--------------------------------------------------
// Description  : Enable Access Port
// Input Value  : usAddr    --> Start address of register
//                ucValue   --> Data Port Value we want to set
// Output Value : Return Access Port Value
//--------------------------------------------------
BYTE ScalerEnableAccessPort(WORD usAddr, BYTE ucValue)
{
    usAddr = usAddr;
    return ucValue;
}

//--------------------------------------------------
// Description  : Disable Access Port
// Input Value  : usAddr   --> Start address of register
// Output Value : None
//--------------------------------------------------
void ScalerDisableAccessPort(WORD usAddr)
{
    usAddr = usAddr;
}

//--------------------------------------------------
// Description  : Set the value into selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue1  --> Data Port Value we want to set
//                ucValue2  --> Data Value we want to set
// Output Value : None
//--------------------------------------------------
void ScalerSetDataPortByte(WORD usAddr, BYTE ucValue1, BYTE ucValue2)
{
    ScalerSetByte(usAddr, ScalerEnableAccessPort(usAddr, ucValue1));
    ScalerSetByte(usAddr + 1, ucValue2);

    ScalerDisableAccessPort(usAddr);
}

//--------------------------------------------------
// Description  : Get bytes from selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Address we want to Get
//                ucLength  --> Numbers of data we want to read
//                pArray    --> Pointer of the reading data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void ScalerGetDataPortByte(WORD usAddr, BYTE ucValue, WORD usLength, BYTE *pucArray, bit bAutoInc)
{
    BYTE ucAccessValue = 0;
    WORD usIndex = 0;

    if(usLength > 0)
    {
        ucAccessValue = ScalerEnableAccessPort(usAddr, ucValue);

        for(usIndex = 0; usIndex < usLength; usIndex++)
        {
            if(bAutoInc == _AUTOINC)
            {
                ScalerSetByte(usAddr, ucAccessValue + usIndex);
            }
            else
            {
                ScalerSetByte(usAddr, ucAccessValue);
            }

            pucArray[usIndex] = ScalerGetByte(usAddr + 1);
        }

        ScalerDisableAccessPort(usAddr);
    }
}

//--------------------------------------------------
// Description  : Set some bits of selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ulAnd     --> & operation
//                ucOr      --> | operation
// Output Value : None
//--------------------------------------------------
void ScalerSetDataPortBit(WORD usAddr, BYTE ucValue, DWORD ulAnd, BYTE ucOr)
{
    BYTE ucValueTemp = 0;

    ScalerSetByte(usAddr, ScalerEnableAccessPort(usAddr, ucValue));
    ucValueTemp = ScalerGetByte(usAddr + 1);

    ucValueTemp = (ucValueTemp & (BYTE)ulAnd) | ucOr;

    ScalerSetByte(usAddr, ScalerEnableAccessPort(usAddr, ucValue));
    ScalerSetByte(usAddr + 1, ucValueTemp);

    ScalerDisableAccessPort(usAddr);
}

//--------------------------------------------------
// Description  : Set some bits of selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ucAnd     --> & operation
// Output Value : Value after & operation
//--------------------------------------------------
BYTE ScalerGetDataPortBit(WORD usAddr, BYTE ucValue, BYTE ucAnd)
{
    BYTE ucValueTemp = 0;

    ScalerSetByte(usAddr, ScalerEnableAccessPort(usAddr, ucValue));
    ucValueTemp = (ScalerGetByte(usAddr + 1) & ucAnd);
    ScalerDisableAccessPort(usAddr);

    return ucValueTemp;
}

//--------------------------------------------------
// Description  : Get bytes from selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Address we want to Get
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
DWORD ScalerGetDataPortDword(WORD usAddr, BYTE ucValue, bit bAutoInc)
{
    BYTE pucArray[4] = {0};

    ScalerGetDataPortByte(usAddr, ucValue, 4, pucArray, bAutoInc);

    return ((DWORD)pucArray[0] << 24) +
           ((DWORD)pucArray[1] << 16) +
           ((DWORD)pucArray[2] << 8) +
           ((DWORD)pucArray[3] << 0);
}

//--------------------------------------------------
// Description  : Get bytes from selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Address we want to Get
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
BYTE ScalerGetDataPortSingleByte(WORD usAddr, BYTE ucValue)
{
    BYTE ucLength = 1;
    BYTE pucArray[1] = {0};

    ScalerGetDataPortByte(usAddr, ucValue, ucLength, pucArray, _NON_AUTOINC);

    return pucArray[0];
}

//--------------------------------------------------
// Description  : Get bytes from selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Address we want to Get
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
WORD ScalerGetDataPortWord(WORD usAddr, BYTE ucValue, bit bAutoInc)
{
    BYTE pucArray[2] = {0};

    ScalerGetDataPortByte(usAddr, ucValue, 2, pucArray, bAutoInc);

    return (WORD)pucArray[0] * 256 + pucArray[1];
}

//--------------------------------------------------
// Description  : Set the value into selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue1  --> Data Port Value we want to set
//                ulValue2  --> Data Value we want to set
// Output Value : None
//--------------------------------------------------
void ScalerSetDataPortDword(WORD usAddr, BYTE ucValue1, DWORD ulValue2)
{
    ScalerSetDataPortByte(usAddr, ucValue1, (BYTE)(ulValue2 >> 24));
    ScalerSetDataPortByte(usAddr, ucValue1 + 1, (BYTE)(ulValue2 >> 16));
    ScalerSetDataPortByte(usAddr, ucValue1 + 2, (BYTE)(ulValue2 >> 8));
    ScalerSetDataPortByte(usAddr, ucValue1 + 3, (BYTE)(ulValue2 >> 0));
}

//--------------------------------------------------
// Description  : Set the value into selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue1  --> Data Port Value we want to set
//                usValue2  --> Data Value we want to set
// Output Value : None
//--------------------------------------------------
void ScalerSetDataPortWord(WORD usAddr, BYTE ucValue1, WORD usValue2)
{
    ScalerSetDataPortByte(usAddr, ucValue1, HIBYTE(usValue2));
    ScalerSetDataPortByte(usAddr, ucValue1 + 1, LOBYTE(usValue2));
}

//--------------------------------------------------
// Description  : Read data from registers of scaler and put it into an reading data array
// Input Value  : usAddr    --> Start address of register
//                usLength  --> Numbers of data we want to read
//                pArray    --> Pointer of the reading data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void ScalerRead(WORD usAddr, WORD usLength, BYTE *pucArray, bit bAutoInc)
{
    if(usLength != 0)
    {
        if(bAutoInc == _AUTOINC)
        {
            memcpy(pucArray, (BYTE xdata *)REG_MAPPING(usAddr), usLength);
        }
        else
        {
            WORD usIndex = 0;

            for(usIndex = 0; usIndex < usLength; usIndex++)
            {
                pucArray[usIndex] = ScalerGetByte(usAddr);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Write a data array into registers
// Input Value  : usAddr    --> Start address of register
//                usLength  --> Numbers of data we want to write
//                pArray    --> Pointer of the writing data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void ScalerWrite(WORD usAddr, WORD usLength, BYTE *pucArray, bit bAutoInc)
{
    if(usLength != 0)
    {
        if(bAutoInc == _AUTOINC)
        {
            memcpy((BYTE xdata *)REG_MAPPING(usAddr), pucArray, usLength);
        }
        else
        {
            WORD usIndex = 0;

            for(usIndex = 0; usIndex < usLength; usIndex++)
            {
                ScalerSetByte(usAddr, pucArray[usIndex]);
            }
        }
    }
}

