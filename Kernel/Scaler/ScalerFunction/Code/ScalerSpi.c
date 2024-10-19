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
// ID Code      : ScalerSpi.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Spi/ScalerSpi.h"

#if((_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON) &&\
    (_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS == _ON))
#if((_LOCAL_DIMMING_FUNCTION == _ON) &&\
    (_SPI_PWM_VALID_CMD_TOTAL_BYTES > _SPI_TX_BUFFER_MAX_LENGTH))
#warning "SPI TX Size Exceed for ScalerSpiDimmingPwmValidByXXXX_EXINT0 Application..."
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_SPI0_SUPPORT == _ON)
#if(_HW_SPI2_EXIST == _ON)
__attribute__((aligned(256)))
volatile BYTE g_pucSpi0RxData[_SPI0_RX_BUFFER_MAX_LENGTH];
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SPI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : SPI Module Initial
// Input Value  : enumTimingMode    --> Timing Mode
//                 enumTransOrder   --> SPI Transceive order
//                enumClkSource     --> SPI Master Clock Source
//                ucClkDiv---> SPI Master Clock divider
// Output Value : none
//--------------------------------------------------
void ScalerSpiInitial(void)
{
#if(_SPI0_SUPPORT == _ON)
    ScalerSpi0Initial();
#endif
#if(_SPI1_SUPPORT == _ON)
    ScalerSpi1Initial();
#endif
#if(_SPI2_SUPPORT == _ON)
    ScalerSpi2Initial();
#endif
}

//--------------------------------------------------
// Description  : SPI Module CLK Select
// Input Value  : EnumClkSel    --> clk select
// Output Value : none
//--------------------------------------------------
void ScalerSpiSclkSel(EnumClkSel enumClock)
{
    if(enumClock == _M2PLL_CLK)
    {
#if(_SPI0_SUPPORT == _ON)
#if(_SPI0_ENUM_CLK_SRC_SEL == _SPI_M2PLL_CLK)
        ScalerSetBit(P22_A3_SPI_MODULE_SETTING, ~(_BIT3 | _BIT2), _BIT2);
#else
        ScalerSetBit(P22_A3_SPI_MODULE_SETTING, ~(_BIT3 | _BIT2), 0x00);
#endif
#endif
#if(_SPI1_SUPPORT == _ON)
#if(_SPI1_ENUM_CLK_SRC_SEL == _SPI_M2PLL_CLK)
        ScalerSetBit(P48_A3_SPI_MODULE_SETTING, ~(_BIT3 | _BIT2), _BIT2);
#else
        ScalerSetBit(P48_A3_SPI_MODULE_SETTING, ~(_BIT3 | _BIT2), 0x00);
#endif
#endif
#if(_SPI2_SUPPORT == _ON)
#if(_SPI2_ENUM_CLK_SRC_SEL == _SPI_M2PLL_CLK)
        ScalerSetBit(P4A_A3_SPI_MODULE_SETTING, ~(_BIT3 | _BIT2), _BIT2);
#else
        ScalerSetBit(P4A_A3_SPI_MODULE_SETTING, ~(_BIT3 | _BIT2), 0x00);
#endif
#endif
    }
    else
    {
#if(_SPI0_SUPPORT == _ON)
        ScalerSetBit(P22_A3_SPI_MODULE_SETTING, ~(_BIT3 | _BIT2), 0x00);
#endif
#if(_SPI1_SUPPORT == _ON)
        ScalerSetBit(P48_A3_SPI_MODULE_SETTING, ~(_BIT3 | _BIT2), 0x00);
#endif
#if(_SPI2_SUPPORT == _ON)
        ScalerSetBit(P4A_A3_SPI_MODULE_SETTING, ~(_BIT3 | _BIT2), 0x00);
#endif
    }
}


#if(_SPI0_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------

bit ScalerSpiData(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf)
{
    BYTE ucIndex = 0;
    BYTE ucIndex2 = 0;
    BYTE ucCommandLength = 0;
    BYTE ucCount = 0;
    BYTE ucTimeOut = _SPI_TRANSACTION_FINISH_COUNT;

    if((bReadWrite == _READ) && (usDataLength > _SPI0_RX_BUFFER_MAX_LENGTH))
    {
        DebugMessageScaler("SPI Read DataLength > _SPI0_RX_BUFFER_MAX_LENGTH", usDataLength);
        return _FALSE;
    }

    // Check if DB trigger is disabled
    if(ScalerGetBit(P22_C5_SPI_DUMMY, _BIT6) == _BIT6)
    {
        ScalerSetBit(P22_C5_SPI_DUMMY, ~(_BIT6), 0x00);
        ScalerSetBit(P22_A2_SPI_MODULE_CTRL, ~(_BIT0), (_BIT0));
    }

    // Face CE pin low after transaction
    ScalerSetBit(P22_C5_SPI_DUMMY, ~(_BIT0), (_BIT0));

    if(bReadWrite == _WRITE)
    {
        ucCount = ((usDataLength / _SPI_TX_BUFFER_MAX_LENGTH) + ((usDataLength % _SPI_TX_BUFFER_MAX_LENGTH) > 0 ? 1 : 0));
    }
    else
    {
        ucCount = 1;
    }

    for(ucIndex2 = 0; ucIndex2 < ucCount; ucIndex2++)
    {
        if(bReadWrite == _WRITE)
        {
            ucCommandLength = ((usDataLength > _SPI_TX_BUFFER_MAX_LENGTH) ? _SPI_TX_BUFFER_MAX_LENGTH : usDataLength);
            usDataLength = ((usDataLength > _SPI_TX_BUFFER_MAX_LENGTH) ? (usDataLength - _SPI_TX_BUFFER_MAX_LENGTH) : usDataLength);

            // Set Read data len
            ScalerSetByte(P22_A7_SPI_S0_READ_LENGTH, 0);

            // Set Write data len
            ScalerSetByte(P22_A6_SPI_S0_WRITE_LENGTH, ucCommandLength);
        }
        else
        {
            // Set Read data len
            ScalerSetByte(P22_A7_SPI_S0_READ_LENGTH, usDataLength);

            // Set Write data len
            ScalerSetByte(P22_A6_SPI_S0_WRITE_LENGTH, 2);
        }

        // Reset FIFO
        ScalerSetBit(P22_C4_SPI_BUF_CLR, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(bReadWrite == _WRITE)
        {
            // Set data
            for(ucIndex = 0; ucIndex < ucCommandLength; ucIndex++)
            {
                ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + (ucIndex + (ucIndex2 * _SPI_TX_BUFFER_MAX_LENGTH))));
            }
        }
        else
        {
            ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + 0));
            ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + 1));
        }

        // Start SPI transaction
        ScalerSetByte(P22_A0_SPI_TRANSACTION_EN, 0x01);

        ucTimeOut = _SPI_TRANSACTION_FINISH_COUNT;

        while(((ScalerGetByte(P22_A1_SPI_TRANSACTION_STATUS) & _BIT0) != _BIT0) && (--ucTimeOut > 0))
        {
            // Wait for SPI tranction finish
            DELAY_5US();
        }

        // Transaction finish
        ScalerSetBit(P22_A1_SPI_TRANSACTION_STATUS, ~(_BIT0), (_BIT0));

        // Face CE pin low after transaction
        ScalerSetByte(P22_C5_SPI_DUMMY, 0x00);
    }

    // Reset SPI
    ScalerSetBit(P22_A2_SPI_MODULE_CTRL, ~(_BIT0), (_BIT0));

    if(bReadWrite == _READ)
    {
        while(usDataLength--)
        {
            *pucDataBuf++ = ScalerGetByte(P22_AD_SPI_S0_RX_BUF);
        }
    }

    return _TRUE;
}


//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------

bit ScalerSpiSPIDataCeForceLow(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf)
{
    BYTE ucIndex = 0;
    BYTE ucIndex2 = 0;
    BYTE ucCommandLength = 0;
    BYTE ucCount = 0;
    BYTE ucTimeOut = _SPI_TRANSACTION_FINISH_COUNT;

    if((bReadWrite == _READ) && (usDataLength > _SPI0_RX_BUFFER_MAX_LENGTH))
    {
        DebugMessageScaler("SPI Read DataLength > _SPI0_RX_BUFFER_MAX_LENGTH", usDataLength);
        return _FALSE;
    }

    // Face CE pin low after transaction
    ScalerSetBit(P22_C5_SPI_DUMMY, ~(_BIT0), (_BIT0));
    ScalerSetBit(P22_C5_SPI_DUMMY, ~(_BIT6), (_BIT6));

    if(bReadWrite == _WRITE)
    {
        ucCount = ((usDataLength / _SPI_TX_BUFFER_MAX_LENGTH) + ((usDataLength % _SPI_TX_BUFFER_MAX_LENGTH) > 0 ? 1 : 0));
    }
    else
    {
        ucCount = 1;
    }

    for(ucIndex2 = 0; ucIndex2 < ucCount; ucIndex2++)
    {
        if(bReadWrite == _WRITE)
        {
            ucCommandLength = ((usDataLength > _SPI_TX_BUFFER_MAX_LENGTH) ? _SPI_TX_BUFFER_MAX_LENGTH : usDataLength);
            usDataLength = ((usDataLength > _SPI_TX_BUFFER_MAX_LENGTH) ? (usDataLength - _SPI_TX_BUFFER_MAX_LENGTH) : usDataLength);

            // Set Read data len
            ScalerSetByte(P22_A7_SPI_S0_READ_LENGTH, 0);

            // Set Write data len
            ScalerSetByte(P22_A6_SPI_S0_WRITE_LENGTH, ucCommandLength);
        }
        else
        {
            // Set Read data len
            ScalerSetByte(P22_A7_SPI_S0_READ_LENGTH, usDataLength);

            // Set Write data len
            ScalerSetByte(P22_A6_SPI_S0_WRITE_LENGTH, 2);
        }

        // Reset FIFO
        ScalerSetBit(P22_C4_SPI_BUF_CLR, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(bReadWrite == _WRITE)
        {
            // Set data
            for(ucIndex = 0; ucIndex < ucCommandLength; ucIndex++)
            {
                ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + (ucIndex + (ucIndex2 * _SPI_TX_BUFFER_MAX_LENGTH))));
            }
        }
        else
        {
            ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + 0));
            ScalerSetByte(P22_AB_SPI_S0_TX_BUF, *(pucDataBuf + 1));
        }

        // Start SPI transaction
        ScalerSetByte(P22_A0_SPI_TRANSACTION_EN, 0x01);

        ucTimeOut = _SPI_TRANSACTION_FINISH_COUNT;

        while(((ScalerGetByte(P22_A1_SPI_TRANSACTION_STATUS) & _BIT0) != _BIT0) && (--ucTimeOut > 0))
        {
            // Wait for SPI tranction finish
            DELAY_5US();
        }
        // Transaction finish
        ScalerSetBit(P22_A1_SPI_TRANSACTION_STATUS, ~(_BIT0), (_BIT0));
    }

    if(bReadWrite == _READ)
    {
        while(usDataLength--)
        {
            *pucDataBuf++ = ScalerGetByte(P22_AD_SPI_S0_RX_BUF);
        }
    }

    return _TRUE;
}

#endif  // End of #if(_SPI0_SUPPORT == _ON)

//--------------------------------------------------
// Description  : SPI Module Initial
// Input Value  : pstSpiConfigInfo  -->  Structure of SPI ConfigInfo
// Output Value : none
//--------------------------------------------------
void ScalerSpiConfigSetting(StructSpiConfigInfo *pstSpiConfigInfo)
{
    WORD usAddrOffset = 0;

#if(_SPI1_SUPPORT == _ON)
    if(pstSpiConfigInfo->b2SpiInterface == _SPI_INTERFACE_1)
    {
        usAddrOffset = (P48_A0_SPI_TRANSACTION_EN - P22_A0_SPI_TRANSACTION_EN);
    }
#endif
#if(_SPI2_SUPPORT == _ON)
    if(pstSpiConfigInfo->b2SpiInterface == _SPI_INTERFACE_2)
    {
        usAddrOffset = (P4A_A0_SPI_TRANSACTION_EN - P22_A0_SPI_TRANSACTION_EN);
    }
#endif

    // clear SPI Interface tranction status
    ScalerSetBit(P22_A1_SPI_TRANSACTION_STATUS + usAddrOffset, ~_BIT0, _BIT0);

    // Set SPI_TRANSACTION_EN restore to default value (Set SPI Module is Master)
    ScalerSetByte(P22_A0_SPI_TRANSACTION_EN + usAddrOffset, 0x00);

    switch(pstSpiConfigInfo->b1SpiClkSel)
    {
        case _SPI_EXT_XTAL_CLK:
            ScalerSetBit(P22_A3_SPI_MODULE_SETTING + usAddrOffset, ~(_BIT3 | _BIT2), 0x00);
            break;
        case _SPI_M2PLL_CLK:
            ScalerSetBit(P22_A3_SPI_MODULE_SETTING + usAddrOffset, ~(_BIT3 | _BIT2), _BIT2);
            break;
        default:
            break;
    }

    // SPI Clk = (Xtal or M2pll) / FirDiv / SecDiv
    // Setting Previous divider of SPI Master SClk Source
    if(pstSpiConfigInfo->ucSpiClkPreDiv > 15)
    {
        pstSpiConfigInfo->ucSpiClkPreDiv = 15;
    }
    ScalerSetBit(P22_A4_SPI_SCLK_DIV + usAddrOffset, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (pstSpiConfigInfo->ucSpiClkPreDiv << 4));

    // Setting Freq divider of SClk transmitted by SPI Master
    if(pstSpiConfigInfo->ucSpiClkDiv > 15)
    {
        pstSpiConfigInfo->ucSpiClkDiv = 15;
    }
    ScalerSetBit(P22_A4_SPI_SCLK_DIV + usAddrOffset, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), pstSpiConfigInfo->ucSpiClkDiv);

    switch(pstSpiConfigInfo->b1SpiProtocolSel)
    {
        case _SPI_STANDARD_MODE:
            ScalerSetBit(P22_A5_SPI_S0_PROTOCOL_MODE + usAddrOffset, ~_BIT5, 0x00);
            break;
        case _SPI_NORMAL_MODE:
            ScalerSetBit(P22_A5_SPI_S0_PROTOCOL_MODE + usAddrOffset, ~_BIT5, _BIT5);
            break;
        default:
            break;
    }

    // Set MOSI Idel Status is High
    ScalerSetBit(P22_A3_SPI_MODULE_SETTING + usAddrOffset, ~(_BIT1 | _BIT0), (_BIT0 << pstSpiConfigInfo->b1MosiIdleState));

    // Set SCLK Idle Status is High
    ScalerSetBit(P22_C9_SPI_SCLK_CTRL + usAddrOffset, ~(_BIT0), (pstSpiConfigInfo->b1SclkIdleState ? _BIT0 : 0));

    if(pstSpiConfigInfo->b1SpiCsSel == 0)
    {
        // use CS0
        // Set CS0 Setup && Hold Time(base on sclk)
        ScalerSetBit(P22_C7_SPI_CS0_CTRL + usAddrOffset, ~(_BIT(3, 0)), ((BYTE)pstSpiConfigInfo->b2SpiCsSetup << 2) | ((BYTE)pstSpiConfigInfo->b2SpiCsHold));
        // Set CS0 Idle Status
        ScalerSetBit(P22_A3_SPI_MODULE_SETTING + usAddrOffset, ~(_BIT5), (pstSpiConfigInfo->b1SpiCsPol ? _BIT5 : 0));
        // Set SPI Using CSx
        ScalerSetBit(P22_A0_SPI_TRANSACTION_EN + usAddrOffset, ~_BIT6, 0x00);
        // Set SPI Using BUFx
        ScalerSetBit(P22_A0_SPI_TRANSACTION_EN + usAddrOffset, ~_BIT5, 0x00);
    }
    else
    {
        // use CS1
        // Set CS1 Setup && Hold Time(base on sclk)
        ScalerSetBit(P22_C8_SPI_CS1_CTRL + usAddrOffset, ~(_BIT(3, 0)), ((BYTE)pstSpiConfigInfo->b2SpiCsSetup << 2) | ((BYTE)pstSpiConfigInfo->b2SpiCsHold));
        // Set CS1 Idle Status
        ScalerSetBit(P22_A3_SPI_MODULE_SETTING + usAddrOffset, ~(_BIT4), (pstSpiConfigInfo->b1SpiCsPol ? _BIT4 : 0));
        // Set SPI Using CSx
        ScalerSetBit(P22_A0_SPI_TRANSACTION_EN + usAddrOffset, ~_BIT6, _BIT6);
        // Set SPI Using BUFx
        ScalerSetBit(P22_A0_SPI_TRANSACTION_EN + usAddrOffset, ~_BIT5, _BIT5);
    }

    // Read/Write Length Unit Choose Byte
    ScalerSetBit(P22_A5_SPI_S0_PROTOCOL_MODE + usAddrOffset, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // SPI Suppress Bits(value = 0~7)
    if(pstSpiConfigInfo->b3SpiSuppressBits == 0)
    {
        // No Suppress
        ScalerSetBit(P22_DD_SPI_SCLK_SUPPRESS + usAddrOffset, ~(_BIT(7, 4)), 0);
    }
    else
    {
        ScalerSetBit(P22_DD_SPI_SCLK_SUPPRESS + usAddrOffset, ~(_BIT(7, 4)), (_BIT7 | (((BYTE)pstSpiConfigInfo->b3SpiSuppressBits - 1) << 4)));
    }

#if(_SPI0_SUPPORT == _ON)

#if(_HW_SPI2_EXIST == _OFF)
    // Setup SPI0 RX Buffer XRAM location,set spi0 use max 128 byte rx xram fifo
    if(pstSpiConfigInfo->b2SpiInterface == _SPI_INTERFACE_0)
    {
        // SPI0 RX Buffer in XRAM
        ScalerSetBit(P22_CA_SPI_XRAM_TX_CTR0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_SPI0_RX_XRAM_ADDRESS_SEL << 1) | _BIT0));
    }
#else
    // Setup SPI0 RX Buffer ShareRAM location,set spi0 use max 128 byte rx xram fifo
    if(pstSpiConfigInfo->b2SpiInterface == _SPI_INTERFACE_0)
    {
        // SPI0 RX Buffer in Share RAM
#if(_SPI0_RX_BUFFER_MAX_LENGTH > 128)
        ScalerSetByte(P22_CA_SPI_XRAM_TX_CTR0, 0);
#else
        ScalerSetByte(P22_CA_SPI_XRAM_TX_CTR0, _BIT0);
#endif
        ScalerSetDWord(P22_D0_SPI_RX_RAM_ADDR_HH, (((DWORD)g_pucSpi0RxData) - _SHARE_RAM_B_ADDRESS));
    }
#endif  // End of #if(_HW_SPI2_EXIST == _OFF)

#endif  // End of #if(_SPI0_SUPPORT == _ON)

}

#if(_SPI0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset SPI0 Interface
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerSpi0Reset(void)
{
    // clear SPI Interface tranction status
    ScalerSetBit(P22_A1_SPI_TRANSACTION_STATUS, ~_BIT0, _BIT0);
    // Reset SPI Interface0 FSM
    ScalerSetBit(P22_A2_SPI_MODULE_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : SPI0 Module Initial
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerSpi0Initial(void)
{
    StructSpiConfigInfo stSpi0ConfigInfo =
    {
        _SPI0_CLK_PRE_DIV,          // SPI CLK PreDivider
        _SPI0_CLK_DIV,              // SPI CLK Divider
        _SPI_INTERFACE_0,           // 0:Use 1 SPI Interface ; 1:Use 2 SPI Interfaces
        _SPI0_ENUM_PROTOCOL_SEL,    // SPI Protocol Select
        _SPI_EXT_XTAL_CLK,          // SPI CLK Source
        _SPI0_MOSI_IDLE_STATE,      // 0:low ; 1:high
        _SPI0_SCLK_IDLE_STATE,      // 0:low ; 1:high
        _SPI0_CS_SEL,               // SPI CS Pin Select, 0:CS0 ; 1:CS1
        _SPI0_CS_POLARITY,          // SPI CS Pin Polarity Select, 0:low active ; 1:high active
        _SPI0_CS_SETUP,             // SPI CS Pin Setup Number(base on sclk)
        _SPI0_CS_HOLD,              // SPI CS Pin Hold Number(base on sclk)
        _SPI0_SUPPRESS_BITS,        // SPI Suppress Bits(value = 0~7)

    };

    ScalerSpi0Reset();
    ScalerSpiConfigSetting(&stSpi0ConfigInfo);
}

//--------------------------------------------------
// Description  : SPI0 Data I/O Common Process
// Input Value  : ucTxRxBufIndex    --> SPI TX/RX buffer index
//                ucWritelength     --> SPI Write Data Length
//                ucReadlength      --> SPI Read Data Length(must <= _SPI1_RX_BUFFER_MAX_LENGTH)
//                usOffsetIndex     --> SPI Write Data Buffer Address Offset
//                pucWriteArray     --> SPI Write Data Buffer
// Output Value : SPI0 Data I/O Status
//--------------------------------------------------
bit ScalerSpi0CommonProcess(BYTE ucTxRxBufIndex, BYTE ucWriteLength, BYTE ucReadLength, WORD usOffsetIndex, BYTE *pucWriteBuf)
{
    BYTE ucIdx = 0;

    if(ucTxRxBufIndex == 0)
    {
        // use Tx0/Rx0 Buffer

        // Set Read data len
        ScalerSetByte(P22_A7_SPI_S0_READ_LENGTH, ucReadLength);
        // Set Write data len
        ScalerSetByte(P22_A6_SPI_S0_WRITE_LENGTH, ucWriteLength);
        // Reset FIFO
        ScalerSetBit(P22_C4_SPI_BUF_CLR, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        // Set data
        for(ucIdx = 0; ucIdx < ucWriteLength; ucIdx++)
        {
            ScalerSetByte(P22_AB_SPI_S0_TX_BUF, pucWriteBuf[ucIdx + (usOffsetIndex * _SPI_TX_BUFFER_MAX_LENGTH)]);
        }
    }
    else
    {
        // use Tx1/Rx1 Buffer

        // Set Read data len
        ScalerSetByte(P22_B7_SPI_S1_READ_LENGTH, ucReadLength);
        // Set Write data len
        ScalerSetByte(P22_B6_SPI_S1_WRITE_LENGTH, ucWriteLength);
        // Reset FIFO
        ScalerSetBit(P22_C4_SPI_BUF_CLR, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
        // Set data
        for(ucIdx = 0; ucIdx < ucWriteLength; ucIdx++)
        {
            ScalerSetByte(P22_BD_SPI_S1_TX_BUF, pucWriteBuf[ucIdx + (usOffsetIndex * _SPI_TX_BUFFER_MAX_LENGTH)]);
        }
    }

    // Start SPI transaction
    ScalerSetBit(P22_A0_SPI_TRANSACTION_EN, ~_BIT0, _BIT0);

    // Polling Finish Status
    if(ScalerTimerPollingFlagProc(100, P22_A1_SPI_TRANSACTION_STATUS, _BIT0, _TRUE) == _TRUE)
    {
        // Clr Transaction finish Flag
        ScalerSetBit(P22_A1_SPI_TRANSACTION_STATUS, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSpi0SetCS(_SPI_CS_DEASSERT);
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : SPI0 Data I/O
// Input Value  : usWritelength     --> SPI Write Data Length
//                ucReadlength      --> SPI Read Data Length(must <= _SPI1_RX_BUFFER_MAX_LENGTH)
//                pucWriteArray      --> SPI Write Data Buffer
//                pucReadArray      --> SPI Read Data Buffer
// Output Value : SPI0 Data I/O Status
//--------------------------------------------------
bit ScalerSpi0DataIo(WORD usWritelength, BYTE ucReadlength, BYTE *pucWriteArray, BYTE *pucReadArray)
{
    BYTE ucLastWriteByte = 0;
    BYTE ucTxRxBufferIndex = 0;
    BYTE ucTxLength = 0;
    WORD usIdx = 0;
    WORD usLoopIdx = 0;
    WORD usRemindLength = usWritelength;

    if(usWritelength == 0)
    {
        DebugMessageScaler("usWritelength can't be 0 (ScalerSpi0DataIo)", 0);
        return _FALSE;
    }

    if(ucReadlength > _SPI0_RX_BUFFER_MAX_LENGTH)
    {
        DebugMessageScaler("SPI0 ReadLength > _SPI0_RX_BUFFER_MAX_LENGTH", ucReadlength);
        return _FALSE;
    }

    // backup last write data byte
    if(ucReadlength > 0)
    {
        ucLastWriteByte = pucWriteArray[usRemindLength - 1];
        usRemindLength--;
    }

    // Check use which Tx/Rx Buf
    ucTxRxBufferIndex = ScalerGetBit(P22_A0_SPI_TRANSACTION_EN, _BIT5);

    ScalerSpi0Reset();  // Reset SPI state machine

    ScalerSpi0SetCS(_SPI_CS_ASSERT);

    if(usRemindLength > 0)
    {
        // over 1 write data byte, send (usWritelength - 1) bytes first
        usLoopIdx = ((usRemindLength / _SPI_TX_BUFFER_MAX_LENGTH) + ((usRemindLength % _SPI_TX_BUFFER_MAX_LENGTH) > 0 ? 1 : 0));

        for(usIdx = 0; usIdx < usLoopIdx; usIdx++)
        {
            if(usRemindLength > _SPI_TX_BUFFER_MAX_LENGTH)
            {
                usRemindLength = usRemindLength - _SPI_TX_BUFFER_MAX_LENGTH;
                ucTxLength = _SPI_TX_BUFFER_MAX_LENGTH;
            }
            else
            {
                ucTxLength = usRemindLength;
            }

            if(ScalerSpi0CommonProcess(ucTxRxBufferIndex, ucTxLength, 0, usIdx, pucWriteArray) == _FALSE)
            {
                return _FALSE;
            }
        }
    }

    if(ucReadlength > 0)
    {
        // perform read data operation
        if(ScalerSpi0CommonProcess(ucTxRxBufferIndex, 1, ucReadlength, 0, &ucLastWriteByte) == _FALSE)
        {
            return _FALSE;
        }

        if(ucTxRxBufferIndex == 0)
        {
            // use Tx0/Rx0 Buffer
            // Get data
            for(usLoopIdx = 0; usLoopIdx < ucReadlength; usLoopIdx++)
            {
                pucReadArray[usLoopIdx] = ScalerGetByte(P22_AD_SPI_S0_RX_BUF);
            }
        }
        else
        {
            // use Tx1/Rx1 Buffer
            // Get data
            for(usLoopIdx = 0; usLoopIdx < ucReadlength; usLoopIdx++)
            {
                pucReadArray[usLoopIdx] = ScalerGetByte(P22_BF_SPI_S1_RX_BUF);
            }
        }
    }
    ScalerSpi0SetCS(_SPI_CS_DEASSERT);

    return _TRUE;
}

//--------------------------------------------------
// Description  : SPI0 CS Pin Select
// Input Value  : enumSpiCsSel      --> CS Pin Select(CS0/CS1)
// Output Value : None
//--------------------------------------------------
void ScalerSpi0CSPinSel(EnumSpiCsSel enumSpiCsSel)
{
    // Set SPI0 use CS0 or CS1
    ScalerSetBit(P22_A0_SPI_TRANSACTION_EN, ~_BIT6, (enumSpiCsSel << 6));
}

//--------------------------------------------------
// Description  : SPI0 CS Pin Set
// Input Value  : enumSpiCsState    --> CS Pin Status(Low/High)
// Output Value : None
//--------------------------------------------------
void ScalerSpi0SetCS(EnumSpiCsState enumSpiCsState)
{
    // Set SPI0 CS Status
    if(enumSpiCsState == _SPI_CS_ASSERT)
    {
        ScalerSetBit(P22_C5_SPI_DUMMY, ~(_BIT3 | _BIT0), _BIT0);
    }
    else
    {
        ScalerSetBit(P22_A2_SPI_MODULE_CTRL, ~_BIT0, _BIT0);
    }
}
#endif

#if(_SPI1_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset SPI1 Interface
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerSpi1Reset(void)
{
    // clear SPI Interface tranction status
    ScalerSetBit(P48_A1_SPI_TRANSACTION_STATUS, ~_BIT0, _BIT0);
    // Reset SPI Interface1 FSM
    ScalerSetBit(P48_A2_SPI_MODULE_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : SPI1 Module Initial
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerSpi1Initial(void)
{
    StructSpiConfigInfo stSpi1ConfigInfo =
    {
        _SPI1_CLK_PRE_DIV,          // SPI CLK PreDivider
        _SPI1_CLK_DIV,              // SPI CLK Divider
        _SPI_INTERFACE_1,           // 0:Use 1 SPI Interface ; 1:Use 2 SPI Interfaces
        _SPI1_ENUM_PROTOCOL_SEL,    // SPI Protocol Select
        _SPI_EXT_XTAL_CLK,          // SPI CLK Source
        _SPI1_MOSI_IDLE_STATE,      // 0:low ; 1:high
        _SPI1_SCLK_IDLE_STATE,      // 0:low ; 1:high
        _SPI1_CS_SEL,               // SPI CS Pin Select, 0:CS0 ; 1:CS1
        _SPI1_CS_POLARITY,          // SPI CS Pin Polarity Select, 0:low active ; 1:high active
        _SPI1_CS_SETUP,             // SPI CS Pin Setup Number(base on sclk)
        _SPI1_CS_HOLD,              // SPI CS Pin Hold Number(base on sclk)
        _SPI1_SUPPRESS_BITS,        // SPI Suppress Bits(value = 0~7)
    };

    ScalerSpi1Reset();
    ScalerSpiConfigSetting(&stSpi1ConfigInfo);
}

//--------------------------------------------------
// Description  : SPI1 Data I/O Common Process
// Input Value  : ucTxRxBufIndex    --> SPI TX/RX buffer index
//                ucWritelength     --> SPI Write Data Length
//                ucReadlength      --> SPI Read Data Length(must <= _SPI1_RX_BUFFER_MAX_LENGTH)
//                usOffsetIndex     --> SPI Write Data Buffer Address Offset
//                pucWriteArray     --> SPI Write Data Buffer
// Output Value : SPI1 Data I/O Status
//--------------------------------------------------
bit ScalerSpi1CommonProcess(BYTE ucTxRxBufIndex, BYTE ucWriteLength, BYTE ucReadLength, WORD usOffsetIndex, BYTE *pucWriteBuf)
{
    BYTE ucIdx = 0;

    if(ucTxRxBufIndex == 0)
    {
        // use Tx0/Rx0 Buffer

        // Set Read data len
        ScalerSetByte(P48_A7_SPI_S0_READ_LENGTH, ucReadLength);
        // Set Write data len
        ScalerSetByte(P48_A6_SPI_S0_WRITE_LENGTH, ucWriteLength);
        // Reset FIFO
        ScalerSetBit(P48_C4_SPI_BUF_CLR, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        // Set data
        for(ucIdx = 0; ucIdx < ucWriteLength; ucIdx++)
        {
            ScalerSetByte(P48_AB_SPI_S0_TX_BUF, pucWriteBuf[ucIdx + (usOffsetIndex * _SPI_TX_BUFFER_MAX_LENGTH)]);
        }
    }
    else
    {
        // use Tx1/Rx1 Buffer

        // Set Read data len
        ScalerSetByte(P48_B7_SPI_S1_READ_LENGTH, ucReadLength);
        // Set Write data len
        ScalerSetByte(P48_B6_SPI_S1_WRITE_LENGTH, ucWriteLength);
        // Reset FIFO
        ScalerSetBit(P48_C4_SPI_BUF_CLR, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
        // Set data
        for(ucIdx = 0; ucIdx < ucWriteLength; ucIdx++)
        {
            ScalerSetByte(P48_BD_SPI_S1_TX_BUF, pucWriteBuf[ucIdx + (usOffsetIndex * _SPI_TX_BUFFER_MAX_LENGTH)]);
        }
    }

    // Start SPI transaction
    ScalerSetBit(P48_A0_SPI_TRANSACTION_EN, ~_BIT0, _BIT0);

    // Polling Finish Status
    if(ScalerTimerPollingFlagProc(100, P48_A1_SPI_TRANSACTION_STATUS, _BIT0, _TRUE) == _TRUE)
    {
        // Clr Transaction finish Flag
        ScalerSetBit(P48_A1_SPI_TRANSACTION_STATUS, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSpi1SetCS(_SPI_CS_DEASSERT);
        return _FALSE;
    }

    return _TRUE;
}


//--------------------------------------------------
// Description  : SPI1 Data I/O
// Input Value  : usWritelength     --> SPI Write Data Length
//                ucReadlength      --> SPI Read Data Length(must <= _SPI1_RX_BUFFER_MAX_LENGTH)
//                pucWriteArray      --> SPI Write Data Buffer
//                pucReadArray      --> SPI Read Data Buffer
// Output Value : SPI1 Data I/O Status
//--------------------------------------------------
bit ScalerSpi1DataIo(WORD usWritelength, BYTE ucReadlength, BYTE *pucWriteArray, BYTE *pucReadArray)
{
    BYTE ucLastWriteByte = 0;
    BYTE ucTxRxBufferIndex = 0;
    BYTE ucTxLength = 0;
    WORD usIdx = 0;
    WORD usLoopIdx = 0;
    WORD usRemindLength = usWritelength;

    if(usWritelength == 0)
    {
        DebugMessageScaler("usWritelength can't be 0 (ScalerSpi1DataIo)", 0);
        return _FALSE;
    }

    if(ucReadlength > _SPI1_RX_BUFFER_MAX_LENGTH)
    {
        DebugMessageScaler("SPI1 ReadLength > _SPI1_RX_BUFFER_MAX_LENGTH", ucReadlength);
        return _FALSE;
    }

    if(ucReadlength > 0)
    {
        // backup last write data byte
        ucLastWriteByte = pucWriteArray[usRemindLength - 1];
        usRemindLength--;
    }

    // Check use which Tx/Rx Buf
    ucTxRxBufferIndex = ScalerGetBit(P48_A0_SPI_TRANSACTION_EN, _BIT5);

    ScalerSpi1Reset();  // Reset SPI state machine

    ScalerSpi1SetCS(_SPI_CS_ASSERT);

    if(usRemindLength > 0)
    {
        // over 1 write data byte, send (usWritelength - 1) bytes first
        usLoopIdx = ((usRemindLength / _SPI_TX_BUFFER_MAX_LENGTH) + ((usRemindLength % _SPI_TX_BUFFER_MAX_LENGTH) > 0 ? 1 : 0));

        for(usIdx = 0; usIdx < usLoopIdx; usIdx++)
        {
            if(usRemindLength > _SPI_TX_BUFFER_MAX_LENGTH)
            {
                usRemindLength = usRemindLength - _SPI_TX_BUFFER_MAX_LENGTH;
                ucTxLength = _SPI_TX_BUFFER_MAX_LENGTH;
            }
            else
            {
                ucTxLength = usRemindLength;
            }

            if(ScalerSpi1CommonProcess(ucTxRxBufferIndex, ucTxLength, 0, usIdx, pucWriteArray) == _FALSE)
            {
                return _FALSE;
            }
        }
    }

    if(ucReadlength > 0)
    {
        // perform read data operation
        if(ScalerSpi1CommonProcess(ucTxRxBufferIndex, 1, ucReadlength, 0, &ucLastWriteByte) == _FALSE)
        {
            return _FALSE;
        }

        for(usLoopIdx = 0; usLoopIdx < ucReadlength; usLoopIdx++)
        {
            // Set SPI1 Small FIFO read index
            ScalerSetByte(P48_DC_SPI_SFIFO_SEL, usLoopIdx);

            // Get data
            pucReadArray[usLoopIdx] = ScalerGetByte(P48_DB_SPI_SFIFO);
        }
    }
    ScalerSpi1SetCS(_SPI_CS_DEASSERT);

    return _TRUE;
}

//--------------------------------------------------
// Description  : SPI1 CS Pin Select
// Input Value  : enumSpiCsSel      --> CS Pin Select(CS0/CS1)
// Output Value : None
//--------------------------------------------------
void ScalerSpi1CSPinSel(EnumSpiCsSel enumSpiCsSel)
{
    // Set SPI1 use CS0 or CS1
    ScalerSetBit(P48_A0_SPI_TRANSACTION_EN, ~_BIT6, (enumSpiCsSel << 6));
}

//--------------------------------------------------
// Description  : SPI1 CS Pin Set
// Input Value  : enumSpiCsState    --> CS Pin Status(Low/High)
// Output Value : None
//--------------------------------------------------
void ScalerSpi1SetCS(EnumSpiCsState enumSpiCsState)
{
    // Set SPI1 CS Status
    if(enumSpiCsState == _SPI_CS_ASSERT)
    {
        ScalerSetBit(P48_C5_SPI_DUMMY, ~(_BIT3 | _BIT0), _BIT0);
    }
    else
    {
        ScalerSetBit(P48_A2_SPI_MODULE_CTRL, ~_BIT0, _BIT0);
    }
}

#endif // End of #if(_MCU_2_SPI_INTERFACE_SUPPORT == _ON)


#if(_SPI2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset SPI2 Interface
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerSpi2Reset(void)
{
    // clear SPI Interface tranction status
    ScalerSetBit(P4A_A1_SPI_TRANSACTION_STATUS, ~_BIT0, _BIT0);
    // Reset SPI Interface1 FSM
    ScalerSetBit(P4A_A2_SPI_MODULE_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : SPI2 Module Initial
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerSpi2Initial(void)
{
    StructSpiConfigInfo stSpi2ConfigInfo =
    {
        _SPI2_CLK_PRE_DIV,          // SPI CLK PreDivider
        _SPI2_CLK_DIV,              // SPI CLK Divider
        _SPI_INTERFACE_2,           // 0:Use 1 SPI Interface ; 1:Use 2 SPI Interfaces
        _SPI2_ENUM_PROTOCOL_SEL,    // SPI Protocol Select
        _SPI_EXT_XTAL_CLK,          // SPI CLK Source
        _SPI2_MOSI_IDLE_STATE,      // 0:low ; 1:high
        _SPI2_SCLK_IDLE_STATE,      // 0:low ; 1:high
        _SPI2_CS_SEL,               // SPI CS Pin Select, 0:CS0 ; 1:CS1
        _SPI2_CS_POLARITY,          // SPI CS Pin Polarity Select, 0:low active ; 1:high active
        _SPI2_CS_SETUP,             // SPI CS Pin Setup Number(base on sclk)
        _SPI2_CS_HOLD,              // SPI CS Pin Hold Number(base on sclk)
        _SPI2_SUPPRESS_BITS,        // SPI Suppress Bits(value = 0~7)
    };

    ScalerSpi2Reset();
    ScalerSpiConfigSetting(&stSpi2ConfigInfo);
}

//--------------------------------------------------
// Description  : SPI2 Data I/O Common Process
// Input Value  : ucTxRxBufIndex    --> SPI TX/RX buffer index
//                ucWritelength     --> SPI Write Data Length
//                ucReadlength      --> SPI Read Data Length(must <= _SPI2_RX_BUFFER_MAX_LENGTH)
//                usOffsetIndex     --> SPI Write Data Buffer Address Offset
//                pucWriteArray     --> SPI Write Data Buffer
// Output Value : SPI2 Data I/O Status
//--------------------------------------------------
bit ScalerSpi2CommonProcess(BYTE ucTxRxBufIndex, BYTE ucWriteLength, BYTE ucReadLength, WORD usOffsetIndex, BYTE *pucWriteBuf)
{
    BYTE ucIdx = 0;

    if(ucTxRxBufIndex == 0)
    {
        // use Tx0/Rx0 Buffer

        // Set Read data len
        ScalerSetByte(P4A_A7_SPI_S0_READ_LENGTH, ucReadLength);
        // Set Write data len
        ScalerSetByte(P4A_A6_SPI_S0_WRITE_LENGTH, ucWriteLength);
        // Reset FIFO
        ScalerSetBit(P4A_C4_SPI_BUF_CLR, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        // Set data
        for(ucIdx = 0; ucIdx < ucWriteLength; ucIdx++)
        {
            ScalerSetByte(P4A_AB_SPI_S0_TX_BUF, pucWriteBuf[ucIdx + (usOffsetIndex * _SPI_TX_BUFFER_MAX_LENGTH)]);
        }
    }
    else
    {
        // use Tx1/Rx1 Buffer

        // Set Read data len
        ScalerSetByte(P4A_B7_SPI_S1_READ_LENGTH, ucReadLength);
        // Set Write data len
        ScalerSetByte(P4A_B6_SPI_S1_WRITE_LENGTH, ucWriteLength);
        // Reset FIFO
        ScalerSetBit(P4A_C4_SPI_BUF_CLR, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
        // Set data
        for(ucIdx = 0; ucIdx < ucWriteLength; ucIdx++)
        {
            ScalerSetByte(P4A_BD_SPI_S1_TX_BUF, pucWriteBuf[ucIdx + (usOffsetIndex * _SPI_TX_BUFFER_MAX_LENGTH)]);
        }
    }

    // Start SPI transaction
    ScalerSetBit(P4A_A0_SPI_TRANSACTION_EN, ~_BIT0, _BIT0);

    // Polling Finish Status
    if(ScalerTimerPollingFlagProc(100, P4A_A1_SPI_TRANSACTION_STATUS, _BIT0, _TRUE) == _TRUE)
    {
        // Clr Transaction finish Flag
        ScalerSetBit(P4A_A1_SPI_TRANSACTION_STATUS, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSpi2SetCS(_SPI_CS_DEASSERT);
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : SPI2 Data I/O
// Input Value  : usWritelength     --> SPI Write Data Length
//                ucReadlength      --> SPI Read Data Length(must <= _SPI2_RX_BUFFER_MAX_LENGTH)
//                pucWriteArray      --> SPI Write Data Buffer
//                pucReadArray      --> SPI Read Data Buffer
// Output Value : SPI2 Data I/O Status
//--------------------------------------------------
bit ScalerSpi2DataIo(WORD usWritelength, BYTE ucReadlength, BYTE *pucWriteArray, BYTE *pucReadArray)
{
    BYTE ucLastWriteByte = 0;
    BYTE ucTxRxBufferIndex = 0;
    BYTE ucTxLength = 0;
    WORD usIdx = 0;
    WORD usLoopIdx = 0;
    WORD usRemindLength = usWritelength;

    if(usWritelength == 0)
    {
        DebugMessageScaler("usWritelength can't be 0 (ScalerSpi2DataIo)", 0);
        return _FALSE;
    }

    if(ucReadlength > _SPI2_RX_BUFFER_MAX_LENGTH)
    {
        DebugMessageScaler("SPI2 ReadLength > _SPI2_RX_BUFFER_MAX_LENGTH", ucReadlength);
        return _FALSE;
    }

    if(ucReadlength > 0)
    {
        // backup last write data byte
        ucLastWriteByte = pucWriteArray[usRemindLength - 1];
        usRemindLength--;
    }

    // Check use which Tx/Rx Buf
    ucTxRxBufferIndex = ScalerGetBit(P4A_A0_SPI_TRANSACTION_EN, _BIT5);

    ScalerSpi2Reset();  // Reset SPI state machine

    ScalerSpi2SetCS(_SPI_CS_ASSERT);

    if(usRemindLength > 0)
    {
        // over 1 write data byte, send (usWritelength - 1) bytes first
        usLoopIdx = ((usRemindLength / _SPI_TX_BUFFER_MAX_LENGTH) + ((usRemindLength % _SPI_TX_BUFFER_MAX_LENGTH) > 0 ? 1 : 0));

        for(usIdx = 0; usIdx < usLoopIdx; usIdx++)
        {
            if(usRemindLength > _SPI_TX_BUFFER_MAX_LENGTH)
            {
                usRemindLength = usRemindLength - _SPI_TX_BUFFER_MAX_LENGTH;
                ucTxLength = _SPI_TX_BUFFER_MAX_LENGTH;
            }
            else
            {
                ucTxLength = usRemindLength;
            }

            if(ScalerSpi2CommonProcess(ucTxRxBufferIndex, ucTxLength, 0, usIdx, pucWriteArray) == _FALSE)
            {
                return _FALSE;
            }
        }
    }

    if(ucReadlength > 0)
    {
        // perform read data operation
        if(ScalerSpi2CommonProcess(ucTxRxBufferIndex, 1, ucReadlength, 0, &ucLastWriteByte) == _FALSE)
        {
            return _FALSE;
        }

        for(usLoopIdx = 0; usLoopIdx < ucReadlength; usLoopIdx++)
        {
            // Set SPI2 Small FIFO read index
            ScalerSetByte(P4A_DC_SPI_SFIFO_SEL, usLoopIdx);

            // Get data
            pucReadArray[usLoopIdx] = ScalerGetByte(P4A_DB_SPI_SFIFO);
        }
    }
    ScalerSpi2SetCS(_SPI_CS_DEASSERT);

    return _TRUE;
}

//--------------------------------------------------
// Description  : SPI2 CS Pin Select
// Input Value  : enumSpiCsSel      --> CS Pin Select(CS0/CS1)
// Output Value : None
//--------------------------------------------------
void ScalerSpi2CSPinSel(EnumSpiCsSel enumSpiCsSel)
{
    // Set SPI2 use CS0 or CS1
    ScalerSetBit(P4A_A0_SPI_TRANSACTION_EN, ~_BIT6, (enumSpiCsSel << 6));
}

//--------------------------------------------------
// Description  : SPI2 CS Pin Set
// Input Value  : enumSpiCsState    --> CS Pin Status(Low/High)
// Output Value : None
//--------------------------------------------------
void ScalerSpi2SetCS(EnumSpiCsState enumSpiCsState)
{
    // Set SPI2 CS Status
    if(enumSpiCsState == _SPI_CS_ASSERT)
    {
        ScalerSetBit(P4A_C5_SPI_DUMMY, ~(_BIT3 | _BIT0), _BIT0);
    }
    else
    {
        ScalerSetBit(P4A_A2_SPI_MODULE_CTRL, ~_BIT0, _BIT0);
    }
}

#endif // End of #if(_SPI2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : SPI Data I/O
// Input Value  : enumSpiInterface  --> SPI Interface(0 or 1)
//                ucWritelength     --> SPI Write Data Length
//                ucReadlength      --> SPI Read Data Length(must <= _SPI1_RX_BUFFER_MAX_LENGTH)
//                pucWriteArray     --> SPI Write Data Buffer
//                pucReadArray      --> SPI Read Data Buffer
// Output Value : SPI0 Data I/O Status
//--------------------------------------------------
bit ScalerSpiDataIo(EnumSpiInterface enumSpiInterface, WORD usWritelength, BYTE ucReadlength, BYTE *pucWriteArray, BYTE *pucReadArray)
{
#if(_SPI0_SUPPORT == _ON)
    if(enumSpiInterface == _SPI_INTERFACE_0)
    {
        return ScalerSpi0DataIo(usWritelength, ucReadlength, pucWriteArray, pucReadArray);
    }
#endif
#if(_SPI1_SUPPORT == _ON)
    if(enumSpiInterface == _SPI_INTERFACE_1)
    {
        return ScalerSpi1DataIo(usWritelength, ucReadlength, pucWriteArray, pucReadArray);
    }
#endif
#if(_SPI2_SUPPORT == _ON)
    if(enumSpiInterface == _SPI_INTERFACE_2)
    {
        return ScalerSpi2DataIo(usWritelength, ucReadlength, pucWriteArray, pucReadArray);
    }
#endif
    return _FALSE;
}

//--------------------------------------------------
// Description  : Force Control SPI CS/CLK/MOSI Pins State
// Input Value  : enumSpiInterface  --> SPI Interface(0/1/2)
//                enumPowerTarget   --> Power Status(_POWER_OFF/_POWER_ON)
// Output Value : None
//--------------------------------------------------
void ScalerSpiSetPinConfigForPowerState(EnumSpiInterface enumSpiInterface, EnumPowerTarget enumPowerTarget)
{
    WORD usAddrOffset = 0;
    bit bCsIdleState = _LOW;
    bit bSclkIdleState = _LOW;
    bit bMosiIdleState = _LOW;

#if(_SPI0_SUPPORT == _ON)
    if(enumSpiInterface == _SPI_INTERFACE_0)
    {
        if(enumPowerTarget == _POWER_ON)
        {
            bCsIdleState = (_SPI0_CS_POLARITY ? _LOW : _HIGH);
            bSclkIdleState = _SPI0_SCLK_IDLE_STATE;
            bMosiIdleState = _SPI0_MOSI_IDLE_STATE;
        }
    }
#endif
#if(_SPI1_SUPPORT == _ON)
    if(enumSpiInterface == _SPI_INTERFACE_1)
    {
        if(enumPowerTarget == _POWER_ON)
        {
            bCsIdleState = (_SPI1_CS_POLARITY ? _LOW : _HIGH);
            bSclkIdleState = _SPI1_SCLK_IDLE_STATE;
            bMosiIdleState = _SPI1_MOSI_IDLE_STATE;
        }
        usAddrOffset = (P48_A0_SPI_TRANSACTION_EN - P22_A0_SPI_TRANSACTION_EN);
    }
#endif
#if(_SPI2_SUPPORT == _ON)
    if(enumSpiInterface == _SPI_INTERFACE_2)
    {
        if(enumPowerTarget == _POWER_ON)
        {
            bCsIdleState = (_SPI2_CS_POLARITY ? _LOW : _HIGH);
            bSclkIdleState = _SPI2_SCLK_IDLE_STATE;
            bMosiIdleState = _SPI2_MOSI_IDLE_STATE;
        }
        usAddrOffset = (P4A_A0_SPI_TRANSACTION_EN - P22_A0_SPI_TRANSACTION_EN);
    }
#endif

    // Set MOSI Idel Status is Low
    ScalerSetBit((P22_A3_SPI_MODULE_SETTING + usAddrOffset), ~(_BIT1 | _BIT0), (_BIT0 << bMosiIdleState));
    // Set SCLK Idle Status is Low
    ScalerSetBit((P22_C9_SPI_SCLK_CTRL + usAddrOffset), ~(_BIT0), (bSclkIdleState ? _BIT0 : 0));
    if(ScalerGetBit((P22_A0_SPI_TRANSACTION_EN + usAddrOffset), _BIT5) == _BIT5)
    {
        // use Tx1/Rx1 Buffer
        // Set CS1 pin Assert State = Low
        ScalerSetBit((P22_A3_SPI_MODULE_SETTING + usAddrOffset), ~(_BIT4), (bCsIdleState ? 0 : _BIT4));
    }
    else
    {
        // use Tx0/Rx0 Buffer
        // Set CS0 pin Assert State = Low
        ScalerSetBit((P22_A3_SPI_MODULE_SETTING + usAddrOffset), ~(_BIT5), (bCsIdleState ? 0 : _BIT5));
    }
}
#endif // End of #if(_SPI_SUPPORT == _ON)

