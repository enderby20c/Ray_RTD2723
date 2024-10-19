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
// ID Code      : ScalerMcuUart.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Mcu/ScalerMcu.h"

#if(_UART_SUPPORT == _ON)
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
// Description  : Set External UART0 PN/PS Baud Rate
// Input Value  : ulPwrNormalBaudRate --->  PowerNormal BaudRate(bps)
//                ulPwrSavingBaudRate --->  PowerSaving BaudRate(bps)
// Output Value : None
//--------------------------------------------------
EnumClkSel ScalerMcuUartGetUartClkSource(void)
{
    if(_SYS_USE_ISO_CLK == _TRUE)
    {
        return _IOSC_CLK;
    }
    if((MCU_FFBD_MCU_CLK_DIV_R & _BIT7) == _BIT7)
    {
        return _M2PLL_CLK;
    }
    else
    {
        return _EXT_XTAL_CLK;
    }
}

#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
//--------------------------------------------------
// Description  : Set External UART0 Baud Rate
// Input Value  : enumClock --->  MCU Clock
//                ulBaudRate --->  BaudRate(bps)
// Output Value : None
//--------------------------------------------------
void ScalerMcuUartExt0SetBaudRate(EnumClkSel enumClock, DWORD ulBaudRate)
{
    WORD usDivisor = 0;

    switch(enumClock)
    {
        case _M2PLL_CLK:

            usDivisor = GET_EXT_UART_DIVISOR(_M2PLL_CLK_KHZ, ulBaudRate);

            MCU_FFBD_MCU_CLK_DIV_R |= _BIT7;

            break;

        case _IOSC_CLK:

            usDivisor = GET_EXT_UART_DIVISOR(_HW_INTERNAL_OSC_XTAL, ulBaudRate);

            MCU_FFBD_MCU_CLK_DIV_R &= ~_BIT7;

            break;

        case _EXT_XTAL_CLK:

            usDivisor = GET_EXT_UART_DIVISOR(_EXT_XTAL, ulBaudRate);

            MCU_FFBD_MCU_CLK_DIV_R &= ~_BIT7;

            break;

        default:

            break;
    }

    // DLAB = 1
    ScalerSetByte((P59_03_U0LCR_0C), (_BIT7 | _BIT1 | _BIT0));

    // Setup Divisor
    ScalerSetByte((P59_00_U0RBR_THR_DLL_00), (usDivisor & 0x00FF));

    ScalerSetByte((P59_01_U0IER_DLH_04), ((usDivisor >> 8) & 0x00FF));

    // DLAB = 0
    ScalerSetByte((P59_03_U0LCR_0C), (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Initialize External UART0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuUartExt0Initial(void)
{
    // Reset Uart
    ScalerSetByte((P59_22_U0SRR_88), (_BIT2 | _BIT1 | _BIT0));

    // Disable FIFO && Flush TX/RX FIFO
    ScalerSetByte((P59_02_U0IIR_FCR_08), (_BIT2 | _BIT1));

    // Non-Parity, 1 Stop bit , 8 data bits
    ScalerSetBit((P59_03_U0LCR_0C), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable UART RX_Available Interrupt
    ScalerSetBit((P59_01_U0IER_DLH_04), ~(_BIT0), _BIT0);

    // Enable EXINT 4
    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_4, _ENABLE);
}

//--------------------------------------------------
// Description  : Check serial receive status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMcuUartExt0CheckReceiveStatus(void)
{
    if(ScalerGetBit((P59_05_U0LSR_14), _BIT0) != 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Serial Int ID
// Input Value  : None
// Output Value : Int ID
//--------------------------------------------------
EnumMcuExtUartIntID ScalerMcuUartExt0CheckIntID(void)
{
    return ScalerGetByte(P59_02_U0IIR_FCR_08);
}

//--------------------------------------------------
// Description  : Get External UART0 Data
// Input Value  : None
// Output Value : serial port data
//--------------------------------------------------
BYTE ScalerMcuUartExt0GetByte(void)
{
    return ScalerGetByte(P59_00_U0RBR_THR_DLL_00);
}

//--------------------------------------------------
// Description  : Write data to the selected device by UART 0
// Input Value  : ucValue ---> Data to be send
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuUartExt0SetByte(BYTE ucValue)
{
    WORD usTimeOut = 1800;

    // Load Data to Serial Port Buffer
    ScalerSetByte((P59_00_U0RBR_THR_DLL_00), ucValue);

    while((ScalerGetBit((P59_05_U0LSR_14), _BIT6) == 0) && (usTimeOut-- != 0))
    {
        DELAY_5US();
    }

    return (usTimeOut != 0);
}
#endif // End of #if(_EXTERNAL_UART0_SUPPORT == _ON)

#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
//--------------------------------------------------
// Description  : Set External UART1 Baud Rate
// Input Value  : enumClock --->  MCU Clock
//                ulBaudRate --->  BaudRate(bps)
// Output Value : None
//--------------------------------------------------
void ScalerMcuUartExt1SetBaudRate(EnumClkSel enumClock, DWORD ulBaudRate)
{
    WORD usDivisor = 0;

    switch(enumClock)
    {
        case _M2PLL_CLK:

            usDivisor = GET_EXT_UART_DIVISOR(_M2PLL_CLK_KHZ, ulBaudRate);

            MCU_FFBD_MCU_CLK_DIV_R |= _BIT7;

            break;

        case _IOSC_CLK:

            usDivisor = GET_EXT_UART_DIVISOR(_HW_INTERNAL_OSC_XTAL, ulBaudRate);

            MCU_FFBD_MCU_CLK_DIV_R &= ~_BIT7;

            break;

        case _EXT_XTAL_CLK:

            usDivisor = GET_EXT_UART_DIVISOR(_EXT_XTAL, ulBaudRate);

            MCU_FFBD_MCU_CLK_DIV_R &= ~_BIT7;

            break;

        default:

            break;
    }

    // DLAB = 1
    ScalerSetByte((P59_43_U1LCR_0C), (_BIT7 | _BIT1 | _BIT0));

    // Setup Divisor
    ScalerSetByte((P59_40_U1RBR_THR_DLL_00), (usDivisor & 0x00FF));

    ScalerSetByte((P59_41_U1IER_DLH_04), ((usDivisor >> 8) & 0x00FF));

    // DLAB = 0
    ScalerSetByte((P59_43_U1LCR_0C), (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Initialize External UART1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuUartExt1Initial(void)
{
    // Reset Uart32
    ScalerSetByte((P59_62_U1SRR_88), (_BIT2 | _BIT1 | _BIT0));

    // Disable FIFO && Flush TX/RX FIFO
    ScalerSetByte((P59_42_U1IIR_FCR_08), (_BIT2 | _BIT1));

    // Non-Parity, 1 Stop bit , 8 data bits
    ScalerSetBit((P59_43_U1LCR_0C), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable UART RX_Available Interrupt
    ScalerSetBit((P59_41_U1IER_DLH_04), ~(_BIT0), _BIT0);

    // Enable EXINT 4
    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_4, _ENABLE);
}

//--------------------------------------------------
// Description  : Check serial receive status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMcuUartExt1CheckReceiveStatus(void)
{
    if(ScalerGetBit((P59_45_U1LSR_14), _BIT0) != 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Serial Int ID
// Input Value  : None
// Output Value : Int ID
//--------------------------------------------------
EnumMcuExtUartIntID ScalerMcuUartExt1CheckIntID(void)
{
    return ScalerGetByte(P59_42_U1IIR_FCR_08);
}

//--------------------------------------------------
// Description  : Get serial port data
// Input Value  : None
// Output Value : serial port data
//--------------------------------------------------
BYTE ScalerMcuUartExt1GetByte(void)
{
    return ScalerGetByte(P59_40_U1RBR_THR_DLL_00);
}

//--------------------------------------------------
// Description  : Write data to the selected device by UART 1
// Input Value  : enumUart32ID  Uart32ID
//                ucValue       Data to be send
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuUartExt1SetByte(BYTE ucValue)
{
    WORD usTimeOut = 1800;

    // Load Data to Serial Port Buffer
    ScalerSetByte((P59_40_U1RBR_THR_DLL_00), ucValue);

    while((ScalerGetBit((P59_45_U1LSR_14), _BIT6) == 0) && (usTimeOut-- != 0))
    {
        DELAY_5US();
    }

    return (usTimeOut != 0);
}

#endif // End of #if(_EXTERNAL_UART1_SUPPORT == _ON)

#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
//--------------------------------------------------
// Description  : Set External UART2 Baud Rate
// Input Value  : enumClock --->  MCU Clock
//                ulBaudRate --->  BaudRate(bps)
// Output Value : None
//--------------------------------------------------
void ScalerMcuUartExt2SetBaudRate(EnumClkSel enumClock, DWORD ulBaudRate)
{
    WORD usDivisor = 0;

    switch(enumClock)
    {
        case _M2PLL_CLK:

            usDivisor = GET_EXT_UART_DIVISOR(_M2PLL_CLK_KHZ, ulBaudRate);

            MCU_FFBD_MCU_CLK_DIV_R |= _BIT7;

            break;

        case _IOSC_CLK:

            usDivisor = GET_EXT_UART_DIVISOR(_HW_INTERNAL_OSC_XTAL, ulBaudRate);

            MCU_FFBD_MCU_CLK_DIV_R &= ~_BIT7;

            break;

        case _EXT_XTAL_CLK:

            usDivisor = GET_EXT_UART_DIVISOR(_EXT_XTAL, ulBaudRate);

            MCU_FFBD_MCU_CLK_DIV_R &= ~_BIT7;

            break;

        default:

            break;
    }

    // DLAB = 1
    ScalerSetByte((P59_C3_U2LCR_0C), (_BIT7 | _BIT1 | _BIT0));

    // Setup Divisor
    ScalerSetByte((P59_C0_U2RBR_THR_DLL_00), (usDivisor & 0x00FF));

    ScalerSetByte((P59_C1_U2IER_DLH_04), ((usDivisor >> 8) & 0x00FF));

    // DLAB = 0
    ScalerSetByte((P59_C3_U2LCR_0C), (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Initialize External UART2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuUartExt2Initial(void)
{
    // Reset Uart32
    ScalerSetByte((P59_E2_U2SRR_88), (_BIT2 | _BIT1 | _BIT0));

    // Disable FIFO && Flush TX/RX FIFO
    ScalerSetByte((P59_C2_U2IIR_FCR_08), (_BIT2 | _BIT1));

    // Non-Parity, 1 Stop bit , 8 data bits
    ScalerSetBit((P59_C3_U2LCR_0C), ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable UART RX_Available Interrupt
    ScalerSetBit((P59_C1_U2IER_DLH_04), ~(_BIT0), _BIT0);

    // Enable EXINT 4
    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_4, _ENABLE);
}

//--------------------------------------------------
// Description  : Check serial receive status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMcuUartExt2CheckReceiveStatus(void)
{
    if(ScalerGetBit((P59_C5_U2LSR_14), _BIT0) != 0)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Serial Int ID
// Input Value  : None
// Output Value : Int ID
//--------------------------------------------------
EnumMcuExtUartIntID ScalerMcuUartExt2CheckIntID(void)
{
    return ScalerGetByte(P59_C2_U2IIR_FCR_08);
}

//--------------------------------------------------
// Description  : Get serial port data
// Input Value  : None
// Output Value : serial port data
//--------------------------------------------------
BYTE ScalerMcuUartExt2GetByte(void)
{
    return ScalerGetByte(P59_C0_U2RBR_THR_DLL_00);
}

//--------------------------------------------------
// Description  : Write data to the selected device by UART 2
// Input Value  : ucValue ---> Data to be send
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuUartExt2SetByte(BYTE ucValue)
{
    WORD usTimeOut = 1800;

    // Load Data to Serial Port Buffer
    ScalerSetByte((P59_C0_U2RBR_THR_DLL_00), ucValue);

    while((ScalerGetBit((P59_C5_U2LSR_14), _BIT6) == 0) && (usTimeOut-- != 0))
    {
        DELAY_5US();
    }

    return (usTimeOut != 0);
}
#endif // End of #if(_EXTERNAL_UART2_SUPPORT == _ON)
#endif // End of #if(_EXTERNAL_UART_SUPPORT == _ON)

