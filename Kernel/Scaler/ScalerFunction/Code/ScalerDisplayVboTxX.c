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
// ID Code      : ScalerDisplayVboTxX.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY_VBO_TXX__

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
// Description  : Settings for Vbyone MAC
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXMac(bit bOn)
{
    BYTE ucCount = 0;

    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_04_MAC0_LANE_STATUS_0, ~(_BIT17 | _BIT16), g_ulPLLFifoRateMode);

    if(bOn == _ON)
    {
        // Set Vby1 MAC
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT23, _BIT23);

        // Check Vby1 Cts Fifo Status Twice
        for(ucCount = 0; ucCount < 2; ucCount++)
        {
            ScalerTimerDelayXms(2);

            // Check Vbyone Cts Fifo Condiction
            if(SCALER32_VBO_GET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_24_MAC0_CTS_FIFO_0, (_BIT17 | _BIT16)) != 0x00)
            {
                // Cts Fifo Handler
                ScalerDisplayVboTxXCtsFifoHandler();
            }
        }
    }
    else
    {
        // Reset Vby1 MAC
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT23, 0x00);
    }
}

//--------------------------------------------------
// Description  : Settings for Vbyone Digital Phy
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXDphy(bit bOn)
{
    if(bOn == _ON)
    {
        // Set Vby1 Digital Phy
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_00_MAC0_VIDEO_FORMAT_0, ~_BIT4, _BIT4);

        // Enable Digital Phy output
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_1C_PHY0_LANE_ENABLE0, ~0x0000FFFF, 0x0000FFFF);
    }
    else
    {
        // Disable Digital Phy output
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_1C_PHY0_LANE_ENABLE0, ~0x0000FFFF, 0x00);

        // Reset Vby1 Digital Phy
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_00_MAC0_VIDEO_FORMAT_0, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Control Vby1 Phy
// Input Value  : enumDisplayVboTxPort, bit bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXAPhyControl(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable)
{
    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);
    SET_DISPLAY_VBO_TX_PHY_PORT_ADDR(enumDisplayVboTxPort);

    if(bEnable == _ENABLE)
    {
        // Vby1 Power on
        ScalerDisplayVboTxXPower(_ON);

        // Vby1 PLL on
        ScalerDisplayVboTxXPLL(_ON);
    }
    else
    {
        // Vby1 PLL off
        ScalerDisplayVboTxXPLL(_OFF);

        // Vby1 Power off
        ScalerDisplayVboTxXPower(_OFF);
    }
}

//--------------------------------------------------
// Description  : Control Vby1 Phy
// Input Value  : enumDisplayVboTxPort, bit bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXDPhyControl(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable)
{
    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);
    SET_DISPLAY_VBO_TX_PHY_PORT_ADDR(enumDisplayVboTxPort);

    if(bEnable == _ENABLE)
    {
        // Set Vby1 MAC
        ScalerDisplayVboTxXMac(_ON);

        // Set Vby1 Digital Phy, Enable Output
        ScalerDisplayVboTxXDphy(_ON);
    }
    else
    {
        // Reset Vby1 Digital Phy, disable Output
        ScalerDisplayVboTxXDphy(_OFF);

        // Reset Vby1 MAC
        ScalerDisplayVboTxXMac(_OFF);
    }
}

//--------------------------------------------------
// Description  : Vbyone Latency between CDR and ALN pattern
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXCdr2AlnLatency(void)
{
    DWORD ulCdr2AlnLatency = 0;

    ulCdr2AlnLatency = (_PANEL_CDR_TRANSFER_ALN_LATENCY * 27);

    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~0x003FFFFF, (ulCdr2AlnLatency & 0x003FFFFF));
}

//--------------------------------------------------
// Description  : Vbyone HTPDN Interrupt Enable
// Input Value  : enumDisplayVboTxPort, _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXHtpdnControl(EnumDisplayVboTxPort enumDisplayVboTxPort, EnumDisplayVboTxControlMode enumDisplayVboTxControlMode, bit bValue)
{
    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);

    if(enumDisplayVboTxControlMode == _VBO_FW_CONTROL)
    {
        // Write Clear the HTDPN and LOCKN Flag
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

        // Set HTPDN Pull High or Low
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT1, ((bValue == _HIGH) ? 0x00 : _BIT1));

        // Set Vby1 HTPDN controlled by F/W
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT7, _BIT7);

        ScalerTimerDelayXms(2);

        // Set HTPDN Pull High or Low
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT1, ((bValue == _HIGH) ? _BIT1 : 0x00));
    }
    else
    {
        // Set Vby1 HTPDN controlled by H/W
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT7, 0x00);
    }
}

#if(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_RE_LINK_TRAIN)
//--------------------------------------------------
// Description  : Vbyone Force Link Training Flow
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXForceLinkTraining(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable)
{
    BYTE ucForceLinkTrainCnt = 5;

    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);

    if(bEnable == _ENABLE)
    {
        // LOCKN Ripped off status initial: False
        g_stDisplayVboTxInfo.b1VboLocknRippedOff = _FALSE;

        // Disable Detect Lock Status
        ScalerDisplayVboTxXSetLocknInterrupt(GET_DISPLAY_VBO_TX_MAC_PORT(), _DISABLE);

        // Disable Detect UnLock Stauts
        ScalerDisplayVboTxXSetUnLocknInterrupt(GET_DISPLAY_VBO_TX_MAC_PORT(), _DISABLE);

        // Set LOCKN Pull High
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT0, _BIT0);

        // Set Vby1 LOCKN controlled by F/W
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT6, _BIT6);

        // Set CMU ckusable = FW Mode
        Scaler32SetBit(PB58050_24_DP1P3_TX_CMU31, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        ScalerTimerDelayXms(10);
    }
    else
    {
        // Wait LT stable
        ScalerTimerDelayXms(50);

        // Set CMU ckusable = HW Mode
        Scaler32SetBit(PB58050_24_DP1P3_TX_CMU31, ~(_BIT7 | _BIT6), 0x00);

        // Enable Vby1 LOCKN controlled by H/W
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT6, 0x00);

        // Set LOCKN Pull High
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT0, _BIT0);

        ScalerTimerDelayXms(10);

        // Check Vby1 LOCKN Status
        if(SCALER32_VBO_GET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_14_MAC0_TRANSMIT_STATUS_0, _BIT15) == _BIT15)
        {
            do
            {
                // Enable Vby1 LOCKN controlled by F/W
                SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT6, _BIT6);

                // Set CMU ckusable = FW Mode
                Scaler32SetBit(PB58050_24_DP1P3_TX_CMU31, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                ScalerTimerDelayXms(20);

                // Set CMU ckusable = HW Mode
                Scaler32SetBit(PB58050_24_DP1P3_TX_CMU31, ~(_BIT7 | _BIT6), 0x00);

                // Enable Vby1 LOCKN controlled by H/W
                SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT6, 0x00);

                ScalerTimerDelayXms(2);

                ucForceLinkTrainCnt--;
            }
            while((SCALER32_VBO_GET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_14_MAC0_TRANSMIT_STATUS_0, _BIT15) == _BIT15) && (ucForceLinkTrainCnt > 0));

            DebugMessageCheck("VBO lock status", SCALER32_VBO_GET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_14_MAC0_TRANSMIT_STATUS_0, _BIT15));
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Vbyone Video Output Enable
// Input Value  : enumDisplayVboTxPort, _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXForceVideoOutput(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable)
{
    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);

    if(bEnable == _ENABLE)
    {
        // Set LOCKN Pull High
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT0, _BIT0);

        // Set Vby1 LOCKN controlled by F/W
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT6, _BIT6);

        ScalerTimerDelayXms(20);

        // Set LOCKN Pull Low
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT0, 0x00);
    }
    else
    {
        // Disable Detect Lock Status
        ScalerDisplayVboTxXSetLocknInterrupt(GET_DISPLAY_VBO_TX_MAC_PORT(), _DISABLE);

        // Disable Detect UnLock Stauts
        ScalerDisplayVboTxXSetUnLocknInterrupt(GET_DISPLAY_VBO_TX_MAC_PORT(), _DISABLE);

        // Set LOCKN Pull High
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT0, _BIT0);

        // Set Vby1 LOCKN controlled by H/W
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT6, 0x00);

        // Clear all flag
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
    }
}

//--------------------------------------------------
// Description  : Vbyone LOCKN Interrupt Enable
// Input Value  : enumDisplayVboTxPort, _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXSetLocknInterrupt(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable)
{
    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);

    // Write Clear the Lock Flag
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT5);

    if(bEnable == _ENABLE)
    {
        // Set LOCKN Interrupt Enable
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT7);
    }
    else
    {
        // Set LOCKN Interrupt Disable
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : Vbyone LOCKN_FAIL Interrupt Enable
// Input Value  : enumDisplayVboTxPort, _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXSetUnLocknInterrupt(EnumDisplayVboTxPort enumDisplayVboTxPort, bit bEnable)
{
    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);

    // Write Clear the UnLock Flag
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT1);

    if(bEnable == _ENABLE)
    {
        // Set LOCKN_FAIL Interrupt Enable
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), _BIT3);
    }
    else
    {
        // Set LOCKN_FAIL Interrupt Disable
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : Vbyone CTS-FIFO Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXCtsFifoHandler(void)
{
    BYTE ucCount = 0;

    // Set CTS FIFO Initial Address For Reading
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_24_MAC0_CTS_FIFO_0, ~(_BIT17 | _BIT16 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Set CTS FIFO PLL Tracking Boundary
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_24_MAC0_CTS_FIFO_0, ~0x0003FF20, 0x00);

    // Toggle Vby1 MAC
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT23, 0x00);
    ScalerTimerDelayXms(2);
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT23, _BIT23);

    // Toggle Vby1 Cts Fifo 4 Times
    for(ucCount = 0; ucCount < 4; ucCount++)
    {
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_24_MAC0_CTS_FIFO_0, ~(_BIT19 | _BIT17 | _BIT16 | _BIT5), 0x00);
        ScalerTimerDelayXms(2);

        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_24_MAC0_CTS_FIFO_0, ~(_BIT19 | _BIT17 | _BIT16 | _BIT5), _BIT19);
        ScalerTimerDelayXms(2);
    }

    // Reset CTS FIFO PLL Tracking Boundary
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_24_MAC0_CTS_FIFO_0, ~0x0003FF20, 0x00001100);
}

//--------------------------------------------------
// Description  : Detect for Vbyone Htpdn
// Input Value  : enumDisplayVboTxPort
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxXHpdnStatus(EnumDisplayVboTxPort enumDisplayVboTxPort)
{
    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);

    if(SCALER32_VBO_GET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, _BIT4) == _BIT4)
    {
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT4);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Detect for Vbyone LOCKN
// Input Value  : enumDisplayVboTxPort
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxXLocknStatus(EnumDisplayVboTxPort enumDisplayVboTxPort)
{
    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);

    if(SCALER32_VBO_GET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, _BIT5) == _BIT5)
    {
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_4C_MAC0_VBY1_IRQ_CTRL_0, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT5);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Detect for Vbyone Lockn Voltage Level
// Input Value  : enumDisplayVboTxPort
// Output Value : High, Low
//--------------------------------------------------
bit ScalerDisplayVboTxXGetLocknVoltageLevel(EnumDisplayVboTxPort enumDisplayVboTxPort)
{
    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);
    return ((SCALER32_VBO_GET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_14_MAC0_TRANSMIT_STATUS_0, _BIT15) == _BIT15) ? _HIGH : _LOW);
}

//--------------------------------------------------
// Description  : Detect for Vbyone ALN Pattern
// Input Value  : enumDisplayVboTxPort
// Output Value : True, False
//--------------------------------------------------
bit ScalerDisplayVboTxXAlnPatternStatus(EnumDisplayVboTxPort enumDisplayVboTxPort)
{
    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);

    return ((SCALER32_VBO_GET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_14_MAC0_TRANSMIT_STATUS_0, _BIT1) == _BIT1) ? _TRUE : _FALSE);
}

//--------------------------------------------------
// Description  : Initial Settings for Vbyone Interface
// Input Value  : enumDisplayVboTxPort
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXInitialTable(EnumDisplayVboTxPort enumDisplayVboTxPort)
{
    SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(enumDisplayVboTxPort);
    SET_DISPLAY_VBO_TX_PHY_PORT_ADDR(enumDisplayVboTxPort);

    // Set Link Clk Source
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_54_MAC0_VBY1_LCLK_SOURCE_CTRL_0, ~_BIT0, _BIT0);

    // Set Vby1 VS/HS Control
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_00_MAC0_VIDEO_FORMAT_0, ~0x00F00000, (((DWORD)_PANEL_VBO_VS_CONTROL << 22) | ((DWORD)_PANEL_VBO_HS_CONTROL << 20)));

    // Set Vby1 Display Data Bit Resolution
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_00_MAC0_VIDEO_FORMAT_0, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _PANEL_VBO_BIT_MODE);

    // Set Vby1 Display Data Lane
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_04_MAC0_LANE_STATUS_0, 0, ((GET_PANEL_VBO_PIXEL_MODE() << 5) | (((GET_PANEL_VBO_PIXEL_MODE() == _VBO_4_PIXEL_MODE) || (_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE)) ? 16 : _PANEL_VBO_OUTPUT_PORT)));

    // Set Vby1 Display Type
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_04_MAC0_LANE_STATUS_0, 1, (((WORD)((_PANEL_VBO_OUTPUT_PORT == _VBO_32_DATA_LANE) ? (_PANEL_VBO_PANEL_SECTION >> 1) : _PANEL_VBO_PANEL_SECTION) << 3) | ((WORD)_PANEL_VBO_BYTE_MODE << 0)));

    // Set Vby1 Display Data Lane Merge Type
    SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_04_MAC0_LANE_STATUS_0, 2, ((GET_PANEL_VBO_PIXEL_MODE() == _VBO_4_PIXEL_MODE) && (_PANEL_VBO_OUTPUT_PORT < _VBO_16_DATA_LANE)) ? ((_PANEL_VBO_OUTPUT_PORT == _VBO_8_DATA_LANE) ? _BIT7 : _BIT6) : 0x00);

    if(_PANEL_VBO_ML_SWAP == _ENABLE)
    {
        // Set Vby1 MSB/LSB Swap
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_00_MAC0_VIDEO_FORMAT_0, ~_BIT6, _BIT6);
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT5, _BIT5);
    }
    else
    {
        // Set Vby1 MSB/LSB Swap
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_00_MAC0_VIDEO_FORMAT_0, ~_BIT6, 0x00);
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_48_MAC0_VBY1_FW_CTRL_0, ~_BIT5, 0x00);
    }

    // Set Vby1 Transmit Control
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~(_BIT29 | _BIT28 | _BIT22), (_BIT29 | ((WORD)_PANEL_VBO_VIDEO_TRANSFER_TYPE << 28)));
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_14_MAC0_TRANSMIT_STATUS_0, ~_BIT7, _BIT7);

    // Set ASY FIFO PLL Tracking Boundary
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_0C_MAC0_PLL_TRACKING_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Set Vby1 Digital Phy Initial
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_14_PHY0_TXBIST_CTRL0, ~(_BIT12 | _BIT0), _BIT0);

    // Set Vby1 Slave Mode Control
    SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_24_MAC0_CTS_FIFO_0, ~(_BIT23 | _BIT17 | _BIT16 | _BIT5), ((enumDisplayVboTxPort == _VBO_TX_PORT_0) ? 0x00 : _BIT23));

#if(_HW_DISPLAY_VBO_MAX_LANE_NUM > _VBO_16_DATA_LANE)
    if(enumDisplayVboTxPort == _VBO_TX_PORT_1)
    {
        // Set Vby1 Lane16 ~ Lane31 PN Swap Control
        SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_00_PHY0_PN_SWAP0, ((_PANEL_VBO_SECTION_1_PN_SWAP == _ENABLE) ? 0x0000FFFF : 0x00000000));
    }
    else
#endif
    {
        // Set Vby1 Lane0 ~ Lane15 PN Swap Control
        SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_00_PHY0_PN_SWAP0, ((_PANEL_VBO_SECTION_0_PN_SWAP == _ENABLE) ? 0x0000FFFF : 0x00000000));
    }

    SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_1C_PHY0_LANE_ENABLE0, 0x00);

    // Set Vby1 Tx Data
    ScalerDisplayVboTxXDataSel();

    // Set HTPDN control by F/W, pull high
    ScalerDisplayVboTxXHtpdnControl(GET_DISPLAY_VBO_TX_MAC_PORT(), _VBO_FW_CONTROL, _HIGH);

    // Reset Vby1 Digital Phy, disable Output
    ScalerDisplayVboTxXDphy(_OFF);

    // Reset Vby1 MAC
    ScalerDisplayVboTxXMac(_OFF);

    // Set Vby1 Z0
    ScalerDisplayVboTxXSetZ0();

    // Set Vby1 Driving Control
    ScalerDisplayVboTxXDrivingControl(_PANEL_VBO_LANE_DRIV_CONTROL, _PANEL_VBO_PRE_EMPHASIS_CONTROL);

    // Set Vby1 CDR to ALN Latency Control
    ScalerDisplayVboTxXCdr2AlnLatency();
}

//--------------------------------------------------
// Description  : Vbo TX Port output Data Selection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXDataSel(void)
{
    if(_PANEL_VBO_OUTPUT_PORT == _VBO_1_DATA_LANE)
    {
        if(_PANEL_VBO_LANE_SWAP == _ENABLE)
        {
            // Set Port Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00000000);

            // Set Lane Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_08_PHY0_LANE_SWAP0, 0x00000000);
        }
        else
        {
            // Set Port Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00000000);

            // Set Lane Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_08_PHY0_LANE_SWAP0, 0x00000000);
        }
    }
    else if(_PANEL_VBO_OUTPUT_PORT == _VBO_2_DATA_LANE)
    {
        if(_PANEL_VBO_LANE_SWAP == _ENABLE)
        {
            // Set Port Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00000000);

            // Set Lane Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_08_PHY0_LANE_SWAP0, 0x00000040);
        }
        else
        {
            // Set Port Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00000000);

            // Set Lane Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_08_PHY0_LANE_SWAP0, 0x00000010);
        }
    }
    else if(_PANEL_VBO_OUTPUT_PORT == _VBO_4_DATA_LANE)
    {
        if(_PANEL_VBO_LANE_SWAP == _ENABLE)
        {
            // Set Port Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00000000);

            // Set Lane Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_08_PHY0_LANE_SWAP0, 0x000000E4);
        }
        else
        {
            // Set Port Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00000000);

            // Set Lane Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_08_PHY0_LANE_SWAP0, 0x0000001B);
        }
    }
    else if(_PANEL_VBO_OUTPUT_PORT == _VBO_8_DATA_LANE)
    {
        if(_PANEL_VBO_LANE_SWAP == _ENABLE)
        {
            // Set Port Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00000040);

            // Set Lane Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_08_PHY0_LANE_SWAP0, 0x0000E4E4);
        }
        else
        {
            // Set Port Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00000010);

            // Set Lane Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_08_PHY0_LANE_SWAP0, 0x00001B1B);
        }
    }
#if(_HW_DISPLAY_VBO_MAX_LANE_NUM > _VBO_8_DATA_LANE)
    else
    {
        if(_PANEL_VBO_LANE_SWAP == _ENABLE)
        {
            // Set Port Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x000000E4);

            // Set Lane Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_08_PHY0_LANE_SWAP0, 0xE4E4E4E4);
        }
        else
        {
            // Set Port Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x0000001B);

            // Set Lane Swap Control
            SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_08_PHY0_LANE_SWAP0, 0x1B1B1B1B);
        }

        if(_PANEL_VBO_OUTPUT_PORT < _VBO_32_DATA_LANE)
        {
            if(_PANEL_VBO_FB_SWAP == _ENABLE)
            {
                BYTE ucPort0_source = (SCALER32_VBO_GET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00) & 0xC0) >> 6;
                BYTE ucPort1_source = (SCALER32_VBO_GET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00) & 0x30) >> 4;
                BYTE ucPort2_source = (SCALER32_VBO_GET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00) & 0x0C) >> 2;
                BYTE ucPort3_source = (SCALER32_VBO_GET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00) & 0x03) >> 0;

                // Set Front/Back Swap Control
                SCALER32_VBO_SET_OFFSET_BYTE(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58080_04_PHY0_PORT_SWAP0, 0x00, ((ucPort2_source << 6) | (ucPort3_source << 4) | (ucPort0_source << 2) | (ucPort1_source)))
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Vbyone PLL Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXPLL(bit bOn)
{
    if(bOn == _ON)
    {
        // Power Up Vby1 PLL for LCLK
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT30, _BIT30);
    }
    else
    {
        // Power Down Vby1 PLL for LCLK
        SCALER32_VBO_SET_OFFSET_BIT(GET_DISPLAY_VBO_TX_MAC_PORT_ADDR(), PB58070_10_MAC0_TRANSMIT_CONTROL_0, ~_BIT30, 0x00);
    }
}

//--------------------------------------------------
// Description  : Settings for Vbyone Z0 Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboTxXSetZ0(void)
{
    // Set Vby1 Z0 Value
    SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_40_DP14_TX_TXTERM_RES_0, 0x02020202);
    SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_44_DP14_TX_TXTERM_RES_4, 0x02020202);

#if(_HW_DISPLAY_VBO_MAX_LANE_NUM > _VBO_8_DATA_LANE)
    SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_48_DP14_TX_TXTERM_RES_8, 0x02020202);
    SCALER32_VBO_SET_OFFSET_DWORD(GET_DISPLAY_VBO_TX_PHY_PORT_ADDR(), PB58060_4C_DP14_TX_TXTERM_RES_12, 0x02020202);
#endif
}
#endif // End of #if(_PANEL_STYLE == _PANEL_VBO)

