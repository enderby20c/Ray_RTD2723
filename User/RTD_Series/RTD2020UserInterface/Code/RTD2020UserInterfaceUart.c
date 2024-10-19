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
// ID Code      : RTD2020UserInterfaceUart.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_UART__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceUart.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_pucUartData[3];

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
//--------------------------------------------------
// Description  : Action in Ext UART0 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUartExt0IntHandler(void)
{
    if(UserCommonMcuUartExt0CheckReceiveStatus() == _TRUE)
    {
        g_pucUartData[0] = UserCommonMcuUartExt0GetByte();
    }
}

//--------------------------------------------------
// Description  : Get Ext UART0 Power Normal BaudRate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
DWORD UserInterfaceUartExt0GetPowerNormalBaudRate(void)
{
    return _UART_BAUD_RATE_POWER_NORMAL;
}

//--------------------------------------------------
// Description  : Get Ext UART0 Power Saving BaudRate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
DWORD UserInterfaceUartExt0GetPowerSavingBaudRate(void)
{
    return _UART_BAUD_RATE_POWER_SAVING;
}
#endif // End of #if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))

#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
//--------------------------------------------------
// Description  : Action in Ext UART1 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUartExt1IntHandler(void)
{
    if(UserCommonMcuUartExt1CheckReceiveStatus() == _TRUE)
    {
        g_pucUartData[1] = UserCommonMcuUartExt1GetByte();
    }
}

//--------------------------------------------------
// Description  : Get Ext UART1 Power Normal BaudRate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
DWORD UserInterfaceUartExt1GetPowerNormalBaudRate(void)
{
    return _UART_BAUD_RATE_POWER_NORMAL;
}

//--------------------------------------------------
// Description  : Get Ext UART1 Power Saving BaudRate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
DWORD UserInterfaceUartExt1GetPowerSavingBaudRate(void)
{
    return _UART_BAUD_RATE_POWER_SAVING;
}
#endif // End of #if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))

#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
//--------------------------------------------------
// Description  : Action in Ext UART2 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUartExt2IntHandler(void)
{
    if(UserCommonMcuUartExt2CheckReceiveStatus() == _TRUE)
    {
        g_pucUartData[2] = UserCommonMcuUartExt2GetByte();
    }
}

//--------------------------------------------------
// Description  : Get Ext UART2 Power Normal BaudRate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
DWORD UserInterfaceUartExt2GetPowerNormalBaudRate(void)
{
    return _UART_BAUD_RATE_POWER_NORMAL;
}

//--------------------------------------------------
// Description  : Get Ext UART2 Power Saving BaudRate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
DWORD UserInterfaceUartExt2GetPowerSavingBaudRate(void)
{
    return _UART_BAUD_RATE_POWER_SAVING;
}
#endif // End of #if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

