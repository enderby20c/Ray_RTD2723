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
// ID Code      : ScalerDisplayVboTxX_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY_VBO_TXX_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DisplayVboTxX/ScalerDisplayVboTxX.h"

#if(_PANEL_STYLE == _PANEL_VBO)
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
// Description  : Vbyone LOCK Detect Exint
// Input Value  : enumDisplayVboTxPort
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxXLockDetect_EXINT0(EnumDisplayVboTxPort enumDisplayVboTxPort)
{
    EnumDisplayVboTxPort enumDisplayVboTxPortBackup = GET_DISPLAY_VBO_TX_MAC_PORT();

    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);

    // Check Lock Flag
    if(SCALER32_VBO_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5))
    {
        // Write Clear the Lock Flag
        SCALER32_VBO_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT5);

        SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPortBackup);

        return _TRUE;
    }

    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPortBackup);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Vbyone Lock Status
// Input Value  : enumDisplayVboTxPort
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxXLockStatus_EXINT0(EnumDisplayVboTxPort enumDisplayVboTxPort)
{
    EnumDisplayVboTxPort enumDisplayVboTxPortBackup = GET_DISPLAY_VBO_TX_MAC_PORT();

    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);

    if(SCALER32_VBO_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_14_MAC0_TRANSMIT_STATUS_0, _BIT15) == 0x00)
    {
        SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPortBackup);

        return _TRUE;
    }

    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPortBackup);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Vbyone Un-LOCK Detect Exint
// Input Value  : enumDisplayVboTxPort
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxXUnLockDetect_EXINT0(EnumDisplayVboTxPort enumDisplayVboTxPort)
{
    EnumDisplayVboTxPort enumDisplayVboTxPortBackup = GET_DISPLAY_VBO_TX_MAC_PORT();

    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);

    // Check UnLock Flag
    if(SCALER32_VBO_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1))
    {
        // Write Clear the UnLock Flag
        SCALER32_VBO_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT1);

        SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPortBackup);

        return _TRUE;
    }

    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPortBackup);

    return _FALSE;
}
#endif // End of #if(_PANEL_STYLE == _PANEL_VBO)

