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
// ID Code      : ScalerUtil.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Util/ScalerUtil.h"

#undef memcpy
#undef memset
#undef memcmp

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
// Description  : Read DWORD Data from specified 32bits Address Reg(Normal Mode)
// Input Value  : ulAddr32 --> 32bits Reg Start Address (must align to 4)
//                usDwordLength --> Read back length count by DWORD
//                ucAddrAutoInc --> is Address auto increase (+4)
//                pulReadData --> Read Back Data Buffer
// Output Value : None
//--------------------------------------------------
void ScalerUtilReadDWord(DWORD ulAlignedAddr32, WORD usDwordLength, BYTE ucAddrAutoInc, DWORD *pulReadData)
{
    DWORD ulAddrInc = ((ucAddrAutoInc == _AUTOINC) ? (4) : (0));
    WORD usIdx = 0;
    while(usIdx < usDwordLength)
    {
        pulReadData[usIdx++] = Scaler32GetDWord(ulAlignedAddr32);
        ulAlignedAddr32 += ulAddrInc;
    }
}


//--------------------------------------------------
// Description  : Read WORD Data from specified 32bits Address Reg(Normal Mode)
// Input Value  : ulAddr32 --> 32bits Reg Start Address (must align to 4)
//                usWordLength --> Read back length count by WORD
//                ucAddrAutoInc --> is Address auto increase (+4)
//                pusReadData --> Read Back WORD Data Buffer
// Output Value : None
//--------------------------------------------------
void ScalerUtilReadWord(DWORD ulAlignedAddr32, WORD usWordLength, BYTE ucAddrAutoInc, WORD *pusReadData)
{
    DWORD ulAddressOffset = ((ucAddrAutoInc == _AUTOINC) ? (4) : (0));
    DWORD ulAignedLength = (usWordLength & 0xFFFE);
    DWORD ulIndex = 0;

    while(ulIndex < ulAignedLength)
    {
        DWORD ulTmpData = Scaler32GetDWord(ulAlignedAddr32);
        pusReadData[ulIndex++] = HIWORD(ulTmpData);
        pusReadData[ulIndex++] = LOWORD(ulTmpData);

        ulAlignedAddr32 += ulAddressOffset;
    }

    if(usWordLength != ulAignedLength)
    {
        pusReadData[ulIndex] = (Scaler32GetDWord(ulAlignedAddr32) >> 16);
    }
}

//--------------------------------------------------
// Description  : 32bits REG/XRAM Burst Write Function
// Input Value  : pucAddress32  --> Write Table Address from XRAM/flash/DDR/IMEM/DMEM
//                usWriteLength32  --> Write Table Size(unit:BYTE, must be multiple of 4)
//                ucBankNum32  --> Flash Bank Number of Write Table from flash
//                ulHostAddr32  --> Destination RBUSD32/XRAM/DDR 32bits Address of BurstWrite
//                ucTableType32  --> cmd/data
//                bTableLocation32  --> xram/flash
//                enumEndianType --> Endian Type
// Output Value : None
//--------------------------------------------------
void ScalerUtilBurstWrite32(const BYTE *pucAddress32, WORD usWriteLength32, BYTE ucBankNum32, DWORD ulHostAddr32, BYTE ucTableType32, BYTE ucTableLocation32, EnumEndianType enumEndianType)
{
    BYTE *pucSrcAddress32 = pucAddress32;
    DWORD ulTempData = 0;
    WORD usIndex = 0;
    BYTE ucAddrAutoInc = 0;

    if((ucTableLocation32 == _BURSTWRITE_FROM_FLASH) && (ucBankNum32 != GET_CURRENT_BANK_NUMBER()))
    {
        // DataSource from absolute flash address
        DWORD ulAbsPhyFlashAddress = (((DWORD)ucBankNum32) << 16) + (((DWORD)pucSrcAddress32) & 0x0000FFFF);

        if(ScalerCpuHalGetCpuFlashAddress(ulAbsPhyFlashAddress, (DWORD *)&pucSrcAddress32) != _TRUE)
        {
            DebugMessageScaler("ScalerUtilBurstWrite32 Phy Flash Addr < FlashBankOffset", ulAbsPhyFlashAddress);
            return;
        }
    }

    if(ucTableType32 == _BURSTWRITE32_CMD)
    {
        DWORD ulTempAddr32 = 0;
        BYTE pucSrcCmdBuf[255] = {0};
        BYTE *pucSrcCmdBufPtr = pucSrcCmdBuf;
        BYTE ucBwAddrIncType = _AUTOINC;
        BYTE ucTempAddr = 0;
        BYTE ucTempData = 0;
        BYTE ucTempPage = 0;

        // _BURSTWRITE32_CMD
        for(usIndex = 0; usIndex < usWriteLength32; usIndex += pucSrcCmdBuf[0])
        {
            // read one byte and store to pucSrcCmdBuf[0]
            pucSrcCmdBuf[0] = pucSrcAddress32[usIndex];

            if(pucSrcCmdBuf[0] == 0)
            {
                return;
            }

            if(ucTableLocation32 != _BURSTWRITE_FROM_FLASH)
            {
                // XRAM or IMEM or DMEM
                pucSrcCmdBufPtr = (BYTE *)(&pucSrcAddress32[usIndex]);
            }
            else
            {
                // continue read from flash to Buffer for speeding up process
                ucTempAddr = 1; // as temp buffer
                while(ucTempAddr < pucSrcCmdBuf[0])
                {
                    pucSrcCmdBuf[ucTempAddr] = pucSrcAddress32[(usIndex + ucTempAddr)];
                    ucTempAddr++;
                }
            }

            ucTempAddr = pucSrcCmdBufPtr[2];

            if(pucSrcCmdBufPtr[0] == 4)
            {
                ucTempData = pucSrcCmdBufPtr[3];

                if(ucTempAddr == 0x9F)
                {
                    ucTempPage = ucTempData;
                }
                else
                {
                    WORD usTmpXDataSpaceRegAddr = TO_WORD(ucTempPage, ucTempAddr);

                    if(usTmpXDataSpaceRegAddr == PFD_E8_BURST_WRITE_CTRL)
                    {
                        if((ucTempData & _BIT4) == _BIT4)
                        {
                            // turn-off address auto inc
                            ucBwAddrIncType = _NON_AUTOINC;
                        }
                        else
                        {
                            // turn-on address auto inc
                            ucBwAddrIncType = _AUTOINC;
                        }
                    }
                    ScalerSetByte(usTmpXDataSpaceRegAddr, ucTempData);
                }
            }
            else if(pucSrcCmdBufPtr[0] > 6)
            {
                WORD usTmpXDataSpaceRegAddr = TO_WORD(ucTempPage, ucTempAddr);

                ulTempData = TO_DWORD(pucSrcCmdBufPtr[3], pucSrcCmdBufPtr[4], pucSrcCmdBufPtr[5], pucSrcCmdBufPtr[6]);

                if(usTmpXDataSpaceRegAddr == PFD_E0_EMCU_TO32B_INF_ADDR3)
                {
                    if(pucSrcCmdBufPtr[1] == _AUTOINC)
                    {
                        // 8to32 BurstWrite Address Port
                        ulTempAddr32 = ulTempData;
                    }
                    else
                    {
                        // ucAddrAutoInc as temp buffer
                        ucAddrAutoInc = 3;
                        while(ucAddrAutoInc < pucSrcCmdBufPtr[0])
                        {
                            ScalerSetByte(usTmpXDataSpaceRegAddr, pucSrcCmdBufPtr[(ucAddrAutoInc)]);
                            ucAddrAutoInc++;
                        }
                    }
                }
                else if(usTmpXDataSpaceRegAddr == PFD_E4_EMCU_TO32B_INF_DATA)
                {
                    if(pucSrcCmdBufPtr[1] == _AUTOINC)
                    {
                        // ucAddrAutoInc as temp buffer
                        ucAddrAutoInc = 3;
                        while(ucAddrAutoInc < pucSrcCmdBufPtr[0])
                        {
                            ScalerSetByte(usTmpXDataSpaceRegAddr, pucSrcCmdBufPtr[(ucAddrAutoInc)]);
                            usTmpXDataSpaceRegAddr++;
                            ucAddrAutoInc++;
                        }
                    }
                    else
                    {
                        // write to 0xFDE4 BurstWrite one Byte Data port
                        if(ucBwAddrIncType == _AUTOINC)
                        {
                            ucAddrAutoInc = 4;
                        }
                        else
                        {
                            ucAddrAutoInc = 0;
                        }

                        if(ulTempAddr32 != 0)
                        {
                            Scaler32SetDWord(ulTempAddr32, ulTempData);

                            if(pucSrcCmdBufPtr[0] > 7)
                            {
                                BYTE ucDataIndex = 7;

                                while(ucDataIndex < pucSrcCmdBufPtr[0])
                                {
                                    ulTempAddr32 += ucAddrAutoInc;
                                    ulTempData = TO_DWORD(pucSrcCmdBufPtr[ucDataIndex], pucSrcCmdBufPtr[(ucDataIndex + 1)], pucSrcCmdBufPtr[(ucDataIndex + 2)], pucSrcCmdBufPtr[(ucDataIndex + 3)]);
                                    Scaler32SetDWord(ulTempAddr32, ulTempData);
                                    ucDataIndex += 4;
                                }
                            }
                        }
                    }
                }
                else
                {
                    // Others
                    BYTE ucIdx = 3;

                    if(pucSrcCmdBufPtr[1] == _AUTOINC)
                    {
                        ucAddrAutoInc = 1;
                    }
                    else
                    {
                        ucAddrAutoInc = 0;
                    }

                    while(ucIdx < pucSrcCmdBufPtr[0])
                    {
                        ScalerSetByte(usTmpXDataSpaceRegAddr, pucSrcCmdBufPtr[(ucIdx)]);
                        usTmpXDataSpaceRegAddr += ucAddrAutoInc;
                        ucIdx++;
                    }
                }
            }
            else
            {
                return;
            }
        }
    }
    else
    {
        // _BURSTWRITE32_DATA
        if(ucTableType32 == _BURSTWRITE32_DATA_AUTO_INC)
        {
            ucAddrAutoInc = 4;
        }

        if(enumEndianType == _ENDIAN_TYPE_LITTLE)
        {
            // LITTLE ENDIAN
            // Check Source Data Table address if aligned to 4
            if((((DWORD)pucSrcAddress32) % 4) == 0)
            {
                // Source Data Table Address align to 4
#if((_CPU32_IP == _CPU32_IP_TR9) && (_HW_CPU32_BW32_SUPPORT == _ON))
                if((ScalerUtilGetAddressType((DWORD)pucAddress32) == _ADDRESS_TYPE_DDR) &&
                   (usWriteLength32 > 256) &&
                   ((((DWORD)pucSrcAddress32) % (_BURST_WRITE32_DATA_ALIGNMENT)) == 0))
                {
                    EnumAddressType enumTmpDestAddrType = ScalerUtilGetAddressType(ulHostAddr32);

                    if((enumTmpDestAddrType == _ADDRESS_TYPE_RBUSD32) ||
                       (enumTmpDestAddrType == _ADDRESS_TYPE_XDATA_REG) ||
                       ((enumTmpDestAddrType == _ADDRESS_TYPE_XRAM) && ((usWriteLength32 % 4) == 0)))
                    {
                        // BW32 From DDR to RBUSD reg avg consume 200ns per reg, 65536 byte max consume 3.28ms , so set 5ms max timeout
                        StructBW32CmdInfo stTmpBW32CmdInfo;
                        stTmpBW32CmdInfo.stBW32BaseInfo.enumBW32CmdFormat = _BW32_DATA_FORMAT;
                        stTmpBW32CmdInfo.stBW32BaseInfo.ulDdrSrcAddr = (DWORD)pucSrcAddress32;
                        stTmpBW32CmdInfo.stBW32BaseInfo.ulDestRBusdRegAddr = ulHostAddr32;
                        stTmpBW32CmdInfo.stBW32BaseInfo.ulTotalCmdNum = (usWriteLength32 / 4);
                        stTmpBW32CmdInfo.stBW32BaseInfo.bAddrAutoInc = ((ucAddrAutoInc != 0) ? _TRUE : _FALSE);
                        stTmpBW32CmdInfo.enumBW32TriggerSource = _BW32_TRIGGER_MANUAL;

                        if(ScalerBW32LaunchCmdX(1, &stTmpBW32CmdInfo, 0, _TRUE, 5, _BW32_CALLBACK_NULL) == _TRUE)
                        {
                            // execute done by BW32
                            return;
                        }
                    }
                }
#endif
                {
                    DWORD *pulTmpAddress32 = (DWORD *)pucSrcAddress32;

                    usWriteLength32 = usWriteLength32 >> 2;

                    while(usIndex < usWriteLength32)
                    {
                        Scaler32SetDWord(ulHostAddr32, pulTmpAddress32[usIndex]);

                        ulHostAddr32 += ucAddrAutoInc;
                        usIndex ++;
                    }
                }
            }
            else
            {
                // Source Data Table Address NOT align to 4
                while(usIndex < usWriteLength32)
                {
                    ulTempData = ((DWORD)pucSrcAddress32[(usIndex)]);
                    ulTempData += (((DWORD)pucSrcAddress32[(usIndex + 1)]) << 8);
                    ulTempData += (((DWORD)pucSrcAddress32[(usIndex + 2)]) << 16);
                    ulTempData += (((DWORD)pucSrcAddress32[(usIndex + 3)]) << 24);
                    Scaler32SetDWord(ulHostAddr32, ulTempData);

                    ulHostAddr32 += ucAddrAutoInc;
                    usIndex += 4;
                }
            }
        }
        else
        {
            // BIG ENDIAN
            // Check Source Data Table address if aligned to 4
            if((((DWORD)pucSrcAddress32) % 4) == 0)
            {
                // Source Data Table Address align to 4
                {
                    DWORD *pulTmpAddress32 = (DWORD *)pucSrcAddress32;

                    usWriteLength32 = usWriteLength32 >> 2;

                    while(usIndex < usWriteLength32)
                    {
                        Scaler32SetDWord(ulHostAddr32, __REV(pulTmpAddress32[usIndex]));

                        ulHostAddr32 += ucAddrAutoInc;
                        usIndex ++;
                    }
                }
            }
            else
            {
                // Source Data Table Address NOT align to 4
                while(usIndex < usWriteLength32)
                {
                    ulTempData = (((DWORD)pucSrcAddress32[(usIndex)]) << 24);
                    ulTempData += (((DWORD)pucSrcAddress32[(usIndex + 1)]) << 16);
                    ulTempData += (((DWORD)pucSrcAddress32[(usIndex + 2)]) << 8);
                    ulTempData += (((DWORD)pucSrcAddress32[(usIndex + 3)]) << 0);
                    Scaler32SetDWord(ulHostAddr32, ulTempData);

                    ulHostAddr32 += ucAddrAutoInc;
                    usIndex += 4;
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get address type
// Input Value  : ulAddress --> target address
// Output Value : EnumAddressType
//--------------------------------------------------
EnumAddressType ScalerUtilGetAddressType(DWORD ulAddress)
{
    // Check Addr32 Memory Type
    // XRAM(ShareRAM)
    if((ulAddress <= _SHARE_RAM_E_ADDRESS) &&
       (ulAddress >= _SHARE_RAM_B_ADDRESS))
    {
        return _ADDRESS_TYPE_XRAM;
    }

    // FLASH
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
#if(_KCPU_FLASH_BASE_ADDR != 0)
    if((ulAddress <= _KCPU_FLASH_MAX_ADDR) &&
       (ulAddress >= _KCPU_FLASH_BASE_ADDR))
    {
        return _ADDRESS_TYPE_FLASH;
    }
#else
    if(ulAddress <= _KCPU_FLASH_MAX_ADDR)
    {
        return _ADDRESS_TYPE_FLASH;
    }
#endif
#endif

#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
#if(_SCPU_FLASH_BASE_ADDR != 0)
    if((ulAddress <= _SCPU_FLASH_MAX_ADDR) &&
       (ulAddress >= _SCPU_FLASH_BASE_ADDR))
    {
        return _ADDRESS_TYPE_FLASH;
    }
#else
    if(ulAddress <= _SCPU_FLASH_MAX_ADDR)
    {
        return _ADDRESS_TYPE_FLASH;
    }
#endif
#endif

    // XDATA_REG
    if((ulAddress <= GET_XDATA_REG_32BIT_ADDR(_XDATA_16B_SCALER_IP_E_ADDR)) &&
       (ulAddress >= GET_XDATA_REG_32BIT_ADDR(_XDATA_16B_SCALER_IP_B_ADDR)))
    {
        return _ADDRESS_TYPE_XDATA_REG;
    }

    // IMEM
    if((ulAddress <= _ITCM_E_ADDRESS) &&
       (ulAddress >= _ITCM_B_ADDRESS))
    {
        return _ADDRESS_TYPE_IMEM;
    }

    // DMEM
    if((ulAddress <= _DTCM_E_ADDRESS) &&
       (ulAddress >= _DTCM_B_ADDRESS))
    {
        return _ADDRESS_TYPE_DMEM;
    }

    // ROM
    if((ulAddress <= _ROM_CODE_MAX_ADDR) &&
       (ulAddress >= _ROM_CODE_BASE_ADDR))
    {
        return _ADDRESS_TYPE_ROM;
    }

    // DDR
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
    if((ulAddress <= _KCPU_DDR_MAX_ADDR) &&
       (ulAddress >= _KCPU_DDR_BASE_ADDR))
    {
        return _ADDRESS_TYPE_DDR;
    }
#endif

#if(_HW_CPU32_IS_BOOT_CPU != _TRUE)
    if((ulAddress <= _SCPU_DDR_MAX_ADDR) &&
       (ulAddress >= _SCPU_DDR_BASE_ADDR))
    {
        return _ADDRESS_TYPE_DDR;
    }
#endif

    // RBUS REG
    if((ulAddress < _DEVICE_CPU2_BASE_ADDR) &&
       (ulAddress >= _DEVICE_PERIPHERAL_BASE_ADDR))
    {
        return _ADDRESS_TYPE_RBUS32;
    }

    // RBUSD REG
    if((ulAddress <= _DEVICE_32BSCALERIP_MAX_ADDR) &&
       (ulAddress >= _DEVICE_16BSCALERIP_BASE_ADDR))
    {
        return _ADDRESS_TYPE_RBUSD32;
    }

    return _ADDRESS_TYPE_OTHER;
}

//--------------------------------------------------
// Description  : Perform address mapping for special address range
// Input Value  : ulAddress --> address to be mapped
// Output Value : mapped address
//--------------------------------------------------
DWORD ScalerUtilGetAddressMapping(DWORD ulAddress)
{
    if(ulAddress <= _XDATA_16B_SCALER_IP_E_ADDR)
    {
        // ((ulAddress <= _XDATA_16B_SCALER_IP_E_ADDR) && (ulAddress >= _XDATA_16B_SCALER_IP_B_ADDR))
        // transfrom to 16-bit address
        return GET_XDATA_REG_32BIT_ADDR(ulAddress);
    }

    return ulAddress;
}

//--------------------------------------------------
// Description  : Set data in target address up to 4-byte alignment
// Input Value  : ulAddress -> target addrss
//                pucData --> valid data starts from pucData[0]
//                ucCount -> 1 ~ 4
// Output Value : None
//--------------------------------------------------
void ScalerUtilSetData(DWORD ulAddress, BYTE *pucData, BYTE ucCount)
{
    BYTE ucIndex = 0;

    if((ucCount == 0) || (ucCount > 4))
    {
        return;
    }

    switch(ScalerUtilGetAddressType(ulAddress))
    {
        case _ADDRESS_TYPE_XDATA_REG:
            for(; ucIndex < ucCount; ucIndex++)
            {
                Scaler32SetDWord(ulAddress + (ucIndex * 4), pucData[ucIndex]);
            }
            break;

        default:
            // fallback to original memcpy
            memcpy((BYTE *)ulAddress, pucData, ucCount);
            break;
    }
}

//--------------------------------------------------
// Description  : Get data in target address up to 4-byte alignment
// Input Value  : ulAddress -> target addrss
//                pucData --> valid data starts from pucData[0]
//                ucCount -> 1 ~ 4
// Output Value : None
//--------------------------------------------------
void ScalerUtilGetData(DWORD ulAddress, BYTE *pucData, BYTE ucCount)
{
    BYTE ucIndex = 0;

    if((ucCount == 0) || (ucCount > 4))
    {
        return;
    }

    switch(ScalerUtilGetAddressType(ulAddress))
    {
        case _ADDRESS_TYPE_XDATA_REG:
            for(; ucIndex < ucCount; ucIndex++)
            {
                pucData[ucIndex] = Scaler32GetDWord((ulAddress + (ucIndex * 4)));
            }
            break;

        default:
            // fallback to original memcpy
            memcpy(pucData, (BYTE *)ulAddress, ucCount);
            break;
    }
}

//--------------------------------------------------
// Description  : memcpy CPU32 version
// Input Value  : pulDestAddr32 --> Destination Address
//                pulSrcAddr32 --> Source Address
//                usLength --> copy length (by Byte)
// Output Value : None
//--------------------------------------------------
void *ScalerUtilMEMCPY(void *pulDestAddr32, const void *pulSrcAddr32, size_t  usLength)
{
    if(usLength != 0)
    {
        DWORD ulDestAddr32 = ScalerUtilGetAddressMapping((DWORD)pulDestAddr32);
        DWORD ulSrcAddr32 = ScalerUtilGetAddressMapping((DWORD)pulSrcAddr32);
        EnumAddressType enumSrcAddrType = ScalerUtilGetAddressType(ulSrcAddr32);
        EnumAddressType enumDestAddrType = ScalerUtilGetAddressType(ulDestAddr32);

        if((IS_REG_ADDR(enumSrcAddrType) == _FALSE) && (IS_REG_ADDR(enumDestAddrType) == _FALSE))
        {
            return memcpy(pulDestAddr32, pulSrcAddr32, usLength);
        }

        BYTE ucDestAddr32Offset = ((enumDestAddrType == _ADDRESS_TYPE_XDATA_REG) ? 4 : 1);
        BYTE ucSrcAddr32Offset = ((enumSrcAddrType == _ADDRESS_TYPE_XDATA_REG) ? 4 : 1);
        BYTE pucData[4] = {0};

        // Set upper boundary
        if((ulDestAddr32 % 0x04) != 0)
        {
            BYTE ucWriteLength = MINOF(4 - (ulDestAddr32 % 0x04), usLength);
            ScalerUtilGetData(ulSrcAddr32, pucData, ucWriteLength);
            ScalerUtilSetData(ulDestAddr32, pucData, ucWriteLength);

            ulSrcAddr32 += (ucWriteLength * ucSrcAddr32Offset);
            ulDestAddr32 += (ucWriteLength * ucDestAddr32Offset);
            usLength -= ucWriteLength;
        }

        // Set aligned boundary
        while(usLength >= 4)
        {
            ScalerUtilGetData(ulSrcAddr32, pucData, 4);
            ScalerUtilSetData(ulDestAddr32, pucData, 4);

            ulSrcAddr32 += (4 * ucSrcAddr32Offset);
            ulDestAddr32 += (4 * ucDestAddr32Offset);
            usLength -= 4;
        }

        // Set lower boundary
        if(usLength != 0x00)
        {
            ScalerUtilGetData(ulSrcAddr32, pucData, usLength);
            ScalerUtilSetData(ulDestAddr32, pucData, usLength);
        }
    }

    return pulDestAddr32;
}

//--------------------------------------------------
// Description  : memset CPU32 version
// Input Value  : pulDestAddr32 --> Destination Address
//                chValue --> Set Value
//                usLength --> copy length (by Byte)
// Output Value : None
//--------------------------------------------------
void *ScalerUtilMEMSET(void *pulDestAddr32, int chValue, size_t usLength)
{
    if(usLength != 0)
    {
        DWORD ulDestAddr32 = ScalerUtilGetAddressMapping((DWORD)pulDestAddr32);

        EnumAddressType enumDestAddrType = ScalerUtilGetAddressType(ulDestAddr32);

        if(IS_REG_ADDR(enumDestAddrType) == _FALSE)
        {
            return memset(pulDestAddr32, chValue, usLength);
        }

        BYTE ucDestAddr32Offset = ((enumDestAddrType == _ADDRESS_TYPE_XDATA_REG) ? 4 : 1);
        BYTE pucData[4] = {chValue, chValue, chValue, chValue};

        // Set upper boundary
        if((ulDestAddr32 % 0x04) != 0)
        {
            BYTE ucWriteLength = MINOF(4 - (ulDestAddr32 % 0x04), usLength);
            ScalerUtilSetData(ulDestAddr32, pucData, ucWriteLength);
            ulDestAddr32 += ucWriteLength;
            usLength -= ucWriteLength;
        }

        // Set aligned boundary
        while(usLength >= 4)
        {
            ScalerUtilSetData(ulDestAddr32, pucData, 4);
            ulDestAddr32 += (4 * ucDestAddr32Offset);
            usLength -= 4;
        }

        // Set lower boundary
        if(usLength != 0x00)
        {
            ScalerUtilSetData(ulDestAddr32, pucData, usLength);
        }
    }

    return pulDestAddr32;
}

//--------------------------------------------------
// Description  : memcmp CPU32 version
// Input Value  : pulSrc1Addr32 --> Source1 Address
//                pulSrc2Addr32 --> Source2 Address
//                usLength --> compare length (by Byte)
// Output Value : None
//--------------------------------------------------
int ScalerUtilMEMCMP(const void *pulSrc1Addr32, const void *pulSrc2Addr32, size_t usLength)
{
    if(usLength != 0)
    {
        DWORD ulSrc1Addr32 = ScalerUtilGetAddressMapping((DWORD)pulSrc1Addr32);
        DWORD ulSrc2Addr32 = ScalerUtilGetAddressMapping((DWORD)pulSrc2Addr32);
        EnumAddressType enumSrc1AddrType = ScalerUtilGetAddressType(ulSrc1Addr32);
        EnumAddressType enumSrc2AddrType = ScalerUtilGetAddressType(ulSrc2Addr32);

        if((IS_REG_ADDR(enumSrc1AddrType) == _FALSE) && (IS_REG_ADDR(enumSrc2AddrType) == _FALSE))
        {
            return memcmp(pulSrc1Addr32, pulSrc2Addr32, usLength);
        }

        BYTE ucSrc1Addr32Offset = ((enumSrc1AddrType == _ADDRESS_TYPE_XDATA_REG) ? 4 : 1);
        BYTE ucSrc2Addr32Offset = ((enumSrc2AddrType == _ADDRESS_TYPE_XDATA_REG) ? 4 : 1);
        BYTE pucData1[4] = {0};
        BYTE pucData2[4] = {0};

        // Set upper boundary
        if((ulSrc1Addr32 % 0x04) != 0)
        {
            BYTE ucWriteLength = MINOF(4 - (ulSrc1Addr32 % 0x04), usLength);
            ScalerUtilGetData(ulSrc1Addr32, pucData1, ucWriteLength);
            ScalerUtilGetData(ulSrc2Addr32, pucData2, ucWriteLength);
            BYTE ucIdx = 0;

            while(ucIdx < ucWriteLength)
            {
                SBYTE chTmpValue = ((SBYTE)pucData1[ucIdx]) - ((SBYTE)pucData2[ucIdx]);
                if(chTmpValue != 0)
                {
                    return chTmpValue;
                }
                ucIdx++;
            }

            ulSrc2Addr32 += (ucWriteLength * ucSrc2Addr32Offset);
            ulSrc1Addr32 += (ucWriteLength * ucSrc1Addr32Offset);
            usLength -= ucWriteLength;
        }

        // Set aligned boundary
        while(usLength >= 4)
        {
            ScalerUtilGetData(ulSrc1Addr32, pucData1, 4);
            ScalerUtilGetData(ulSrc2Addr32, pucData2, 4);
            BYTE ucIdx = 0;

            while(ucIdx < 4)
            {
                SBYTE chTmpValue = ((SBYTE)pucData1[ucIdx]) - ((SBYTE)pucData2[ucIdx]);
                if(chTmpValue != 0)
                {
                    return chTmpValue;
                }
                ucIdx++;
            }

            ulSrc2Addr32 += (4 * ucSrc2Addr32Offset);
            ulSrc1Addr32 += (4 * ucSrc1Addr32Offset);
            usLength -= 4;
        }

        // Set lower boundary
        if(usLength != 0x00)
        {
            ScalerUtilGetData(ulSrc1Addr32, pucData1, usLength);
            ScalerUtilGetData(ulSrc2Addr32, pucData2, usLength);
            BYTE ucIdx = 0;

            while(ucIdx < usLength)
            {
                SBYTE chTmpValue = ((SBYTE)pucData1[ucIdx]) - ((SBYTE)pucData2[ucIdx]);
                if(chTmpValue != 0)
                {
                    return chTmpValue;
                }
                ucIdx++;
            }
        }
    }

    return 0;
}
