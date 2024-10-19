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
// ID Code      : ScalerDisplayDpTxX_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY_DP_TX__

#include "ScalerFunctionInclude.h"
#include "DisplayDpTxX/ScalerDisplayDpTxX.h"

#if(_DISPLAY_DP_TXX_SUPPORT == _ON)
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
// Description  : DP Tx Native Aux Read
// Input Value  : ucCommand --> Native Aux Read Command
//                ucHighAddress --> High Byte of  Native Aux Read Address
//                ucMidAddress --> Middle Byte of  Native Aux Read Address
//                ucLowAddress --> Low Byte of  Native Aux Read Address
//                ucLength --> Native Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Read
// Output Value : TRUE --> Native Aux Read Sucessful
//--------------------------------------------------
bit ScalerDisplayDpTxXNativeAuxRead_EXINT0(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    if(ScalerDisplayDpTxXAuxRead_EXINT0((0x90 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucReadArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Aux Read
// Input Value  : ucCommand --> Aux Read Command
//                ucHighAddress --> High Byte of  Aux Read Address
//                ucMidAddress --> Middle Byte of  Aux Read Address
//                ucLowAddress --> Low Byte of  Aux Read Address
//                ucLength --> Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of Aux Read
// Output Value : TRUE --> Aux Read Sucessful
//--------------------------------------------------
bit ScalerDisplayDpTxXAuxRead_EXINT0(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    bit bReceiveFlag = _FALSE;
    BYTE ucAuxPollingCount = 0;
    BYTE ucDataCount = 0;
    BYTE ucReadRetryNum = 0;
    BYTE ucResidualReceiveTimes = 16;
    BYTE ucCheckLength = 0;
    DWORD ulCommandAddr = TO_DWORD(0x00, ucCommandAddrH, ucAddrM, ucAddrL);

    // if aux_en = 0, return false
    if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_40_AUX_TX_CTRL, _BIT0) == 0x00)
    {
        return _FALSE;
    }

    if(((ulCommandAddr & 0xFFFFF) + ucLength) > 0x100000)
    {
        ucLength = 0x100000 - (ulCommandAddr & 0xFFFFF);
    }

    // Enable AUX FW Handle Mode & Disable Address only transaction
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT5 | _BIT0), _BIT5);

    do
    {
        ucReadRetryNum = 0;

        // Reset Retry Mechanism
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~_BIT7, 0x00);

        // Enable Retry Mechanism & Timeout HW Retry
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

        // CLR Flag
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

        // Reset AUX FIFO
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        ucLength = ucLength - ucCheckLength;

        if(ucLength == 0)
        {
            ucLength = 1;
        }
        else if(ucLength > 16)
        {
            ucLength = 16;
        }

        ulCommandAddr += ucCheckLength;

        // Setting Tx REQ Addr & TX_LEN = ucLength-1
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_50_AUXTX_REQ_CMD, ((ulCommandAddr << 8) | (ucLength - 1)));

        // Reset AUX Start Bit
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

        // Enable Aux to Start Read
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

        do
        {
            // Delay Time us [400,x] Delay 400us
            DELAY_XUS(400);

            // Delay Time us [5,175] Polling AUX Done Bit (Delay 25 Loop = 175us)
            for(ucAuxPollingCount = 0; ucAuxPollingCount < 25; ucAuxPollingCount++)
            {
                DELAY_5US();

                if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, _BIT5) == _BIT5)
                {
                    // Reply Error or Nack or Command is not ACK
                    if((SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, _BIT2) != 0x00) || (SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_58_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                    {
                        // CLR Flag
                        SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

                        if(ucReadRetryNum != _DISPLAY_DP_TX_AUX_RETRY_LIMIT)
                        {
                            // Reset AUX FIFO
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            // Reset AUX Start Bit
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                            // Enable Aux to Start Read
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
                        }
                        else
                        {
                            // Disable Timeout Retry
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                        }
                    }
                    else
                    {
                        ucCheckLength = SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_78_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

                        // Avoid Aux Reply too much data
                        if(ucCheckLength > ucLength)
                        {
                            ucCheckLength = ucLength;
                        }

                        // Read Data From Buffer
                        for(ucDataCount = 0; ucDataCount < ucCheckLength; ucDataCount++)
                        {
                            *pucReadArray = SCALER32_DISPLAY_DP_TX_GET_OFFSET_BYTE_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_5C_AUX_REPLY_DATA, 0x00);
                            pucReadArray++;
                        }

                        if(ucCheckLength == ucLength)
                        {
                            // Disable Timeout Retry
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            return _TRUE;
                        }
                        else
                        {
                            // break loop to retry read residual data
                            bReceiveFlag = _TRUE;
                        }
                    }

                    break;
                }
                else
                {
                    // HW Retry Times Reaches RETRY_NUM
                    if(SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                    {
                        // Disable Timeout Retry
                        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                        // CLR Flag
                        SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        return _FALSE;
                    }
                }
            }

            // Increasing Retry Num
            ucReadRetryNum++;
        }
        while((ucReadRetryNum <= _DISPLAY_DP_TX_AUX_RETRY_LIMIT) && (SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_78_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00) && (bReceiveFlag == _FALSE));

        // clear receive flag
        bReceiveFlag = _FALSE;

        // residual times decrease
        ucResidualReceiveTimes--;
    }
    while(ucResidualReceiveTimes > 0);

    // Disable Timeout Retry
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_DWORD_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_84_AUX_IRQ_EVENT, 0x3F);

    // Reset AUX FIFO
    SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58001_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Delay Time us [400,x] Delay 400us
    DELAY_XUS(400);

    return _FALSE;
}

#if(_PANEL_DPTX_HPD_DETECT == _ON)
#if(_PANEL_DPTX_IRQ_HPD_DETECT == _ON)
//--------------------------------------------------
// Description  : Dp Tx Irq Hpd Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDpTxXIrqHpdHandler_EXINT0(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort)
{
    BYTE pucDpcdTemp[6];

    // Short HPD IRQ
    if((SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C8_HPD_IRQ_EN, _BIT6) == _BIT6) &&
       (SCALER32_DISPLAY_DP_TX_GET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C4_HPD_IRQ, _BIT6) == _BIT6))
    {
        SCALER32_DISPLAY_DP_TX_SET_OFFSET_BIT_EXINT0(GET_DISPLAY_DP_TX_PORT_OFFSET(), PB58010_C4_HPD_IRQ, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

        if(ScalerDisplayDpTxXNativeAuxRead_EXINT0(0x00, 0x02, 0x00, 6, pucDpcdTemp) == _TRUE)
        {
            // Link Status Change Irq
            if(((GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort) == 1) && ((pucDpcdTemp[2] & 0x07) != 0x07)) ||
               ((GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort) == 2) && ((pucDpcdTemp[2] & 0x77) != 0x77)) ||
               ((GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort) == 4) && (((pucDpcdTemp[2] & 0x77) != 0x77) || ((pucDpcdTemp[3] & 0x77) != 0x77))) ||
               ((GET_DISPLAY_DP_TXX_LANE_NUM(enumDisplayDpTxOutputPort) != 1) && ((pucDpcdTemp[4] & 0x01) != 0x01)))
            {
                SET_DISPLAY_DP_TXX_IRQ_HPD_DETECTED(enumDisplayDpTxOutputPort);
            }

            // Downstream Port Status Change
            if((pucDpcdTemp[4] & _BIT6) == _BIT6)
            {
                SET_DISPLAY_DP_TXX_IRQ_HPD_DETECTED(enumDisplayDpTxOutputPort);
            }
        }
    }
}
#endif
#endif

#endif // End of #if(_DISPLAY_DP_TXX_SUPPORT == _ON)
