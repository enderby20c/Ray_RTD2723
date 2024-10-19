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
// ID Code      : ScalerDpAuxTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPTX_AUX__

#include "ScalerFunctionInclude.h"
#include "DpAuxTx/ScalerDpAuxTx.h"


#if(_DP_PHY_TX_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
BYTE g_ucDpAuxTxPVth;
BYTE g_ucDpAuxTxNVth;
#endif

EnumDpAuxReceiveMode g_enumDpAuxTxReceiveMode = _AUX_DIFF_MODE;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Tx Aux Write
// Input Value  : ucCommand --> Aux Write Command
//                ucHighAddress --> High Byte of  Aux Write Address
//                ucMidAddress --> Middle Byte of  Aux Write Address
//                ucLowAddress --> Low Byte of  Aux Write Address
//                ucLength --> Aux Write Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of Aux Write
// Output Value : TRUE --> Aux Write Sucessful
//--------------------------------------------------
bit ScalerDpAuxTxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    BYTE ucAuxPollingCount = 0;
    BYTE ucDataCount = 0;
    BYTE ucWriteRetryNum = 0;

    // if aux_en = 0, return false
    if(Scaler32GetBit(PB18081_40_AUX_TX_CTRL, _BIT0) == 0x00)
    {
        return _FALSE;
    }

    // Disable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

    // Enable Timeout Retry
    Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

    // Reset FIFO
    Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // CLR Flag
    Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

    // Enable AUX FW Handle Mode
    Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT5 | _BIT0), _BIT5);

    // Check Length
    if(ucLength == 0)
    {
        // I2C Over Aux Transaction
        if((ucCommandAddrH & _BIT7) == 0x00)
        {
            // Enable I2C Addr Only Mode
            Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT0), _BIT7);
        }
        else
        {
            ucLength = 1;
        }
    }
    else if(ucLength > 16)
    {
        ucLength = 16;
    }

    // Setting DPCD Write Address & TX_LEN = ucLength-1
    Scaler32SetDWord(PB18081_50_AUXTX_REQ_CMD, TO_DWORD(ucCommandAddrH, ucAddrM, ucAddrL, ((ucLength > 0) ? (ucLength - 1) : 0)));

    // Write Data to Buffer
    for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
    {
        Scaler32SetDWord(PB18081_54_AUXTX_REQ_DATA, pucWriteArray[ucDataCount]);
    }

    // Reset AUX Start Bit
    Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

    if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _LOW)
    {
        ScalerTimerDelayXms(2);

        if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _LOW)
        {
            // Disable Timeout Retry
            Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // CLR Flag
            Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

            // Reset FIFO
            Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Enable Short HPD Int.
            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

            // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
            Scaler32SetBit(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

            return _FALSE;
        }
    }

    // Enable Aux to Start Write
    Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

    while(ucWriteRetryNum <= _DP_AUX_TX_RETRY_LIMIT)
    {
        // Delay Time us [400,x] Delay 400us
        DELAY_XUS(400);

        // Delay Time us [5,175] Polling AUX Done Bit (Delay 25 Loop = 175us)
        for(ucAuxPollingCount = 0; ucAuxPollingCount < 25; ucAuxPollingCount++)
        {
            DELAY_5US();

            if(Scaler32GetBit(PB18081_84_AUX_IRQ_EVENT, _BIT5) == _BIT5)
            {
                // Reply Error or Nack or Command is not ACK
                if((Scaler32GetBit(PB18081_84_AUX_IRQ_EVENT, _BIT2) != 0x00) || ((Scaler32GetBit(PB18081_58_AUX_REPLY_CMD, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) & (_BIT5 | _BIT4)) != 0x00))
                {
                    // CLR Flag
                    Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                    if(ucWriteRetryNum != _DP_AUX_TX_RETRY_LIMIT)
                    {
                        // Reset FIFO
                        Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Write Data to Buffer
                        for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
                        {
                            Scaler32SetDWord(PB18081_54_AUXTX_REQ_DATA, pucWriteArray[ucDataCount]);
                        }

                        // Reset AUX Start Bit
                        Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                        if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _LOW)
                        {
                            ScalerTimerDelayXms(2);

                            if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _LOW)
                            {
                                // Disable Timeout Retry
                                Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                                // CLR Flag
                                Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                                // Reset FIFO
                                Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                                // Enable Short HPD Int.
                                ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                                // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
                                Scaler32SetBit(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

                                return _FALSE;
                            }
                        }

                        // Enable Aux to Start Write
                        Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
                    }

                    break;
                }
                else
                {
                    // Disable Timeout Retry
                    Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // Enable Short HPD Int.
                    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                    // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
                    Scaler32SetBit(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

                    return _TRUE;
                }
            }
            else
            {
                // HW Retry Times Reaches RETRY_NUM
                if(Scaler32GetBit(PB18081_84_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                {
                    // Disable Timeout Retry
                    Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // Enable Short HPD Int.
                    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                    // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
                    Scaler32SetBit(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

                    return _FALSE;
                }
            }
        }

        // Increasing Retry Num
        ucWriteRetryNum += 1;
    }

    // Disable Timeout Retry
    Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

    // Reset FIFO
    Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

    // Delay Time us [400,x] Delay 400us
    DELAY_XUS(400);

    // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
    Scaler32SetBit(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

    return _FALSE;
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
bit ScalerDpAuxTxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    bit bReceiveFlag = _FALSE;
    BYTE ucAuxPollingCount = 0;
    BYTE ucDataCount = 0;
    BYTE ucReadRetryNum = 0;
    BYTE ucResidualReceiveTimes = 16;
    BYTE ucCheckLength = 0;
    BYTE ucCommand = ucCommandAddrH & 0xF0;
    DWORD ulAddr = TO_DWORD(0x00, ucCommandAddrH & 0x0F, ucAddrM, ucAddrL);

    // if aux_en = 0, return false
    if(Scaler32GetBit(PB18081_40_AUX_TX_CTRL, _BIT0) == 0x00)
    {
        return _FALSE;
    }

    if((ulAddr + ucLength) > 0x100000)
    {
        ucLength = 0x100000 - ulAddr;
    }

    // Disable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

    // Enable AUX FW Handle Mode & Disable Address only transaction
    Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT5 | _BIT0), _BIT5);

    do
    {
        ucReadRetryNum = 0;

        // Enable Retry Mechanism
        Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~_BIT7, 0x00);

        // Enable Timeout HW Retry
        Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

        // CLR Flag
        Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

        // Reset AUX FIFO
        Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        ucLength = ucLength - ucCheckLength;

        if(ucLength == 0)
        {
            // I2C Over Aux Transaction
            if((ucCommand & _BIT7) == 0x00)
            {
                // Enable I2C Addr Only Mode
                Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT0), _BIT7);
            }
            else
            {
                ucLength = 1;
            }
        }
        else if(ucLength > 16)
        {
            ucLength = 16;
        }

        // Setting Read Address & TX_LEN = ucLength-1
        if((ucCommand & _BIT7) == 0x00)
        {
            // I2c Over Aux Transaction
            Scaler32SetDWord(PB18081_50_AUXTX_REQ_CMD, TO_DWORD(ucCommandAddrH, ucAddrM, ucAddrL, ((ucLength > 0) ? (ucLength - 1) : 0)));
        }
        else
        {
            ulAddr += ucCheckLength;

            // Native Aux Transaction
            Scaler32SetDWord(PB18081_50_AUXTX_REQ_CMD, (_BIT31 | _BIT28 | (ulAddr << 8) | (ucLength - 1)));
        }

        // Reset AUX Start Bit
        Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

        if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _LOW)
        {
            ScalerTimerDelayXms(2);

            if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _LOW)
            {
                // Disable Timeout Retry
                Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                // CLR Flag
                Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                // Reset FIFO
                Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                // Enable Short HPD Int.
                ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
                Scaler32SetBit(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

                return _FALSE;
            }
        }

        // Enable Aux to Start Read
        Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

        do
        {
            // Delay Time us [400,x] Delay 400us
            DELAY_XUS(400);

            // Delay Time us [5,175] Polling AUX Done Bit (Delay 25 Loop = 175us)
            for(ucAuxPollingCount = 0; ucAuxPollingCount < 25; ucAuxPollingCount++)
            {
                DELAY_5US();

                if(Scaler32GetBit(PB18081_84_AUX_IRQ_EVENT, _BIT5) == _BIT5)
                {
                    // Reply Error or Nack or Command is not ACK
                    if((Scaler32GetBit(PB18081_84_AUX_IRQ_EVENT, _BIT2) != 0x00) || ((Scaler32GetBit(PB18081_58_AUX_REPLY_CMD, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) & (_BIT5 | _BIT4)) != 0x00))
                    {
                        // CLR Flag
                        Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                        if(ucReadRetryNum != _DP_AUX_TX_RETRY_LIMIT)
                        {
                            // Reset AUX FIFO
                            Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            // Reset AUX Start Bit
                            Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                            if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _LOW)
                            {
                                ScalerTimerDelayXms(2);

                                if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _LOW)
                                {
                                    // Disable Timeout Retry
                                    Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                                    // CLR Flag
                                    Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                                    // Reset FIFO
                                    Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                                    // Enable Short HPD Int.
                                    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                                    // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
                                    Scaler32SetBit(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

                                    return _FALSE;
                                }
                            }

                            // Enable Aux to Start Read
                            Scaler32SetBit(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
                        }
                        else
                        {
                            // Disable Timeout Retry
                            Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            // Enable Short HPD Int.
                            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                            // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
                            Scaler32SetBit(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);
                        }
                    }
                    else
                    {
                        ucCheckLength = Scaler32GetBit(PB18081_78_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

                        // Avoid Aux Reply too much data
                        if(ucCheckLength > ucLength)
                        {
                            ucCheckLength = ucLength;
                        }

                        // Read Data From Buffer
                        for(ucDataCount = 0; ucDataCount < ucCheckLength; ucDataCount++)
                        {
                            *pucReadArray = Scaler32GetByte(PB18081_5C_AUX_REPLY_DATA, 0x00);
                            pucReadArray++;
                        }

                        if(ucCheckLength == ucLength)
                        {
                            // Disable Timeout Retry
                            Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            // Enable Short HPD Int.
                            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                            // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
                            Scaler32SetBit(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

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
                    if(Scaler32GetBit(PB18081_84_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                    {
                        // Disable Timeout Retry
                        Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                        // CLR Flag
                        Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Enable Short HPD Int.
                        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                        // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
                        Scaler32SetBit(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

                        return _FALSE;
                    }
                }
            }

            // Increasing Retry Num
            ucReadRetryNum++;
        }
        while((ucReadRetryNum <= _DP_AUX_TX_RETRY_LIMIT) && (Scaler32GetBit(PB18081_78_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00) && (bReceiveFlag == _FALSE));

        // clear receive flag
        bReceiveFlag = _FALSE;

        // residual times decrease
        ucResidualReceiveTimes--;
    }
    while(ucResidualReceiveTimes > 0);

    // Disable Timeout Retry
    Scaler32SetBit(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    Scaler32SetDWord(PB18081_84_AUX_IRQ_EVENT, 0x3F);

    // Reset AUX FIFO
    Scaler32SetBit(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

    // Delay Time us [400,x] Delay 400us
    DELAY_XUS(400);

    // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
    Scaler32SetBit(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Native Aux Write
// Input Value  : ucCommand --> Native Aux Write Command
//                ucHighAddress --> High Byte of  Native Aux Write Address
//                ucMidAddress --> Middle Byte of  Native Aux Write Address
//                ucLowAddress --> Low Byte of  Native Aux Write Address
//                ucLength --> Native Aux Write Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Write
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDpAuxTxNativeWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    if(ScalerDpAuxTxWrite((0x80 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucWriteArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

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
bit ScalerDpAuxTxNativeRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    if(ScalerDpAuxTxRead((0x90 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucReadArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Write
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Write
//                ucSubAddress --> SubAddress of I2CoverAux Write
//                ucLength --> Length of I2CoverAux Write
//                pWriteArray --> Data of I2CoverAux Write
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDpAuxTxI2CoverWrite(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT)
{
    if(ScalerDpAuxTxWrite((0x00 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
    {
        if(ScalerDpAuxTxWrite((0x00 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
        {
            return _FALSE;
        }
    }
    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Write
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Read
//                ucSubAddress --> SubAddress of I2CoverAux Read
//                ucLength --> Length of I2CoverAux Read
//                pWriteArray --> Data of I2CoverAux Read
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDpAuxTxI2CoverRead(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT)
{
    if(ScalerDpAuxTxRead((0x10 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
    {
        if(ScalerDpAuxTxRead((0x10 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx Aux Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxTxInitial(void)
{
    // Set Tx Aux Clk Select from IOSC
    ScalerSetBit(P0_0B_POWER_CTRL, ~_BIT6, 0x00);

    // Enable Aux 50/50 Duty, Talk Mode High Period and Low Period Will Keep The Same of 1M Counter
    Scaler32SetBit(PB18081_00_AUX_DIG_PHY, ~_BIT2, _BIT2);

    // Set 1M Count = 28, 50/50 Duty Enable, The High Period and Low Period are The Same = 14 (28M / 28 = 1MHz)
    Scaler32SetByte(PB18081_00_AUX_DIG_PHY, 0x03, 0x1C);

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
    ScalerDpAuxTxAutoCalibration();
#endif

    // Setting Aux
    ScalerDpAuxTxPHYSet(_DP_TX_AUX_DIFF_MODE);

    // Set Aux Timeout Enable
    Scaler32SetBit(PB18081_44_AUX_TIMEOUT, ~_BIT15, _BIT15);

    // Set Aux Timeout
    Scaler32SetByte(PB18081_44_AUX_TIMEOUT, 0x00, 0x15);

    // Set Aux HW Retry
    Scaler32SetBit(PB18081_7C_AUX_RETRY_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_AUX_TX_RETRY_LIMIT);

    // Sync end Pattern Error Handle Disable
    Scaler32SetBit(PB18081_08_AUX_IRQ_EN, ~_BIT1, _BIT1);

    // Power On Aux CH
    Scaler32SetBit(PB18081_40_AUX_TX_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Dp Tx Aux PHY Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpAuxTxPHYSet(BYTE ucMode)
{
#if(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_WITH_AUTO_CALIBRATION)
    BYTE ucPVTH = 0;
    BYTE ucNVTH = 0;

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    if((Scaler32GetByte(PB18080_24_AUX_REV_0, 0x00) & _BIT0) == _BIT0)
    {
        ucPVTH = g_ucDpAuxTxNVth;
        ucNVTH = g_ucDpAuxTxPVth;
    }
    else
#endif
    {
        ucPVTH = g_ucDpAuxTxPVth;
        ucNVTH = g_ucDpAuxTxNVth;
    }
#else
#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    if((Scaler32GetByte(PB18080_24_AUX_REV_0, 0x00) & _BIT0) == _BIT0)
    {
        ucPVTH = 0;
        ucNVTH = _DP_AUX_AUTO_CALIBRATION_VTH;
    }
    else
#endif
    {
        ucPVTH = _DP_AUX_AUTO_CALIBRATION_VTH;
        ucNVTH = 0;
    }
#endif
#endif

    // Set Aux Tx LDO = _DP_TX_AUX_REQUEST_SWING_LEVEL
    Scaler32SetBit(PB18080_14_AUX_5, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_TX_AUX_REQUEST_SWING_LEVEL);

    // Rx Vcom = 0.5V
    Scaler32SetBit(PB18080_10_AUX_4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
    // Reserved For User Adjust
    if(ucMode == _DP_TX_AUX_SINGLE_MODE)
    {
        // Enable Single-Ended Mode
        Scaler32SetBit(PB18080_08_AUX_2, ~_BIT5, _BIT5);

        // Vth = 50mV
#if(_HW_DP_AUX_SINGLE_END_GEN == _DP_AUX_SINGLE_END_ONLY)
        Scaler32SetBit(PB18080_00_DIG_TX_04, ~(_BIT1 | _BIT0), _BIT0);
#elif(_HW_DP_AUX_SINGLE_END_GEN == _DP_AUX_SINGLE_END_COMBO_RX2)
        Scaler32SetBit(PB18080_00_DIG_TX_04, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
#endif

        // Open ADJR_P
        Scaler32SetBit(PB18080_04_AUX_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Open ADJR_N
        Scaler32SetBit(PB18080_18_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
#endif
    {
        switch(GET_DP_AUX_TX_RECEIVE_MODE())
        {
            case _AUX_PN_SWAP_MODE:
                // Enable Aux DPHY Swap
                Scaler32SetBit(PB18081_00_AUX_DIG_PHY, ~_BIT0, _BIT0);

                // aux_inv = 0
                Scaler32SetBit(PB18081_00_AUX_DIG_PHY, ~_BIT1, 0x00);

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
                // Disable Single-Ended Mode
                Scaler32SetBit(PB18080_08_AUX_2, ~_BIT5, 0x00);
#endif

#if(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_ONLY)
                // Vth = 75mV
                Scaler32SetDWord(PB18080_24_AUX_REV_0, (_BIT2 | _BIT1));
#elif(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_WITH_AUTO_CALIBRATION)
                // Set Vth = 75mV + Offset, |(Bit12:8 - Bit20:16)*5| = Vth
                Scaler32SetDWord(PB18081_24_AUX_AUTO_K, TO_DWORD(0, ucNVTH, ucPVTH, 0));
#endif

                // Set Aux Listen Mode ADJR_P
                Scaler32SetBit(PB18080_04_AUX_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_AUX_LISTEN_MODE_Z0);

                // Set Aux Listen Mode ADJR_N
                Scaler32SetBit(PB18080_18_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_AUX_LISTEN_MODE_Z0);

                // Set Aux Talk Mode ADJR
                Scaler32SetByte(PB18080_3C_DIG_TX_03_2, 0x00, 0x17);
                Scaler32SetByte(PB18080_1C_DIG_TX_03_1, 0x00, 0x17);

                break;
            case _AUX_DIFF_MODE:
            default:
                // Disable Aux DPHY Swap
                Scaler32SetBit(PB18081_00_AUX_DIG_PHY, ~_BIT0, 0x00);

                // aux_inv = 0
                Scaler32SetBit(PB18081_00_AUX_DIG_PHY, ~_BIT1, 0x00);

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
                // Disable Single-Ended Mode
                Scaler32SetBit(PB18080_08_AUX_2, ~_BIT5, 0x00);
#endif

#if(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_ONLY)
                // Vth = 75mV
                Scaler32SetDWord(PB18080_24_AUX_REV_0, (_BIT2 | _BIT1));
#elif(_HW_DP_AUX_RX_GEN == _DP_AUX_RX_WITH_AUTO_CALIBRATION)
                // Set Vth = 75mV + Offset, |(Bit12:8 - Bit20:16)*5| = Vth
                Scaler32SetDWord(PB18081_24_AUX_AUTO_K, TO_DWORD(0, ucNVTH, ucPVTH, 0));
#endif

                // Set Aux Listen Mode ADJR_P
                Scaler32SetBit(PB18080_04_AUX_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_AUX_LISTEN_MODE_Z0);

                // Set Aux Listen Mode ADJR_N
                Scaler32SetBit(PB18080_18_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_AUX_LISTEN_MODE_Z0);

                // Set Aux Talk Mode ADJR
                Scaler32SetByte(PB18080_3C_DIG_TX_03_2, 0x00, 0x17);
                Scaler32SetByte(PB18080_1C_DIG_TX_03_1, 0x00, 0x17);

                break;
        }
    }
}

#if(_DP_AUX_AUTO_CALIBRATION_SUPPORT == _ON)
//-------------------------------------------------------
// Description  : Aux Rx Auto Calibration offset
// Input Value  : None
// Output Value : None
//-------------------------------------------------------
void ScalerDpAuxTxAutoCalibration(void)
{
    EnumDpAuxRxAutoKState enumDpAuxTxAutoKState = _AUTO_CALIBRATION_INIT;
    BYTE ucDpAuxTxPVthBackup = 0;
    BYTE ucDpAuxTxNVthBackup = 0;
    BYTE ucDpAuxTxPVthBackup2 = 0;
    BYTE ucDpAuxTxNVthBackup2 = 0;
    BYTE ucTimeout = 0;
    BYTE ucDpAuxTxPVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
    BYTE ucDpAuxTxNVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
    BYTE ucAutoCalibrationCount = 0;

    // debsp_time = Value/Dphy Clk ~ 100ns
    Scaler32SetByte(PB18081_28_AUX_AUTO_K, 0x02, 0x03);

#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    Scaler32SetBit(PB18080_18_AUX_6, ~_BIT6, _BIT6);
#endif

    // Set autok_toggle_num = 3(Bit31:29), autok_chk_num = Value*8/Dphy Clk(Bit28:24) ~ 1us, Detect Range N(Bit20:16)/P(Bit12:8), aux_d1_deb_en = 1(Bit2)
    Scaler32SetDWord(PB18081_24_AUX_AUTO_K, TO_DWORD(0x64, ucDpAuxTxNVthStart, ucDpAuxTxPVthStart, (_BIT7 | _BIT6 | _BIT2)));

    while((enumDpAuxTxAutoKState == _AUTO_CALIBRATION_INIT) && (ucAutoCalibrationCount < 2))
    {
        // Enable auto calibration
        Scaler32SetBit(PB18081_24_AUX_AUTO_K, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), _BIT3);

        // Wait FSM = SET_INIT
        if(Scaler32GetBit(PB18081_28_AUX_AUTO_K, _BIT(23, 21)) != _BIT21)
        {
            DELAY_5US();
        }

        // aux_rx_vth_set_done = 1
        Scaler32SetBit(PB18081_24_AUX_AUTO_K, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // Set Timeout
        ucTimeout = 2 * (ucDpAuxTxNVthStart + ucDpAuxTxPVthStart) / 5;

        // Polling auto_k_done = 1
        while((Scaler32GetBit(PB18081_24_AUX_AUTO_K, _BIT6) != _BIT6) && (ucTimeout != 0))
        {
            DELAY_5US();

            ucTimeout--;
        }

        // Check fail flag
        if(Scaler32GetBit(PB18081_24_AUX_AUTO_K, _BIT7) == _BIT7)
        {
            // Detect from n->p
            if(Scaler32GetBit(PB18081_24_AUX_AUTO_K, _BIT4) == 0x00)
            {
                // Fail result in Aux Trigger at Start Point
                if(Scaler32GetByte(PB18081_28_AUX_AUTO_K, 0x01) == ucDpAuxTxNVthStart)
                {
                    if(ucDpAuxTxNVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDpAuxTxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Negative or Zero
                        ucDpAuxTxPVthStart = 5;
                        ucDpAuxTxNVthStart += 5;

                        // Avoid Vth over limit
                        if(ucDpAuxTxNVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDpAuxTxNVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
                // Fail result in Aux never Trigger
                else if(Scaler32GetByte(PB18081_28_AUX_AUTO_K, 0x00) == ucDpAuxTxPVthStart)
                {
                    if(ucDpAuxTxPVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDpAuxTxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Positive or Zero
                        ucDpAuxTxPVthStart += 5;
                        ucDpAuxTxNVthStart = 5;

                        // Avoid Vth over limit
                        if(ucDpAuxTxPVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDpAuxTxPVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
            }
            // Detect from p->n
            else
            {
                // Fail result in Aux Trigger at Start Point
                if(Scaler32GetByte(PB18081_28_AUX_AUTO_K, 0x00) == ucDpAuxTxPVthStart)
                {
                    if(ucDpAuxTxPVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDpAuxTxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Positive or Zero
                        ucDpAuxTxPVthStart += 5;
                        ucDpAuxTxNVthStart = 5;

                        // Avoid Vth over limit
                        if(ucDpAuxTxPVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDpAuxTxPVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
                // Fail result in Aux never Trigger
                else if(Scaler32GetByte(PB18081_28_AUX_AUTO_K, 0x01) == ucDpAuxTxNVthStart)
                {
                    if(ucDpAuxTxNVthStart == _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                    {
                        // Auto Calibration Fail
                        enumDpAuxTxAutoKState = _AUTO_CALIBRATION_FAIL;
                    }
                    else
                    {
                        // Offset should be Negative or Zero
                        ucDpAuxTxPVthStart = 5;
                        ucDpAuxTxNVthStart += 5;

                        // Avoid Vth over limit
                        if(ucDpAuxTxNVthStart > _HW_DP_AUX_AUTO_CALIBRATION_RANGE)
                        {
                            ucDpAuxTxNVthStart = _HW_DP_AUX_AUTO_CALIBRATION_RANGE;
                        }
                    }
                }
            }

            // Refresh Detect Range P/N, Disable auto calibration
            Scaler32SetDWord(PB18081_24_AUX_AUTO_K, TO_DWORD(0x64, ucDpAuxTxNVthStart, ucDpAuxTxPVthStart, _BIT2));
        }
        else
        {
            // Detect from n->p, First Loop Finish
            if(Scaler32GetBit(PB18081_24_AUX_AUTO_K, _BIT4) == 0x00)
            {
                // Backup First Loop Result
                ucDpAuxTxPVthBackup = Scaler32GetByte(PB18081_28_AUX_AUTO_K, 0x00);
                ucDpAuxTxNVthBackup = Scaler32GetByte(PB18081_28_AUX_AUTO_K, 0x01);

                if(ucDpAuxTxPVthBackup == 0x00)
                {
                    ucDpAuxTxNVthBackup++;
                }
                else
                {
                    ucDpAuxTxPVthBackup--;
                }

                // Change to Detect Fron p->n
                Scaler32SetBit(PB18081_24_AUX_AUTO_K, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
            }
            else
            {
                // Backup Second Loop Result
                ucDpAuxTxPVthBackup2 = Scaler32GetByte(PB18081_28_AUX_AUTO_K, 0x00);
                ucDpAuxTxNVthBackup2 = Scaler32GetByte(PB18081_28_AUX_AUTO_K, 0x01);

                // Finish
                enumDpAuxTxAutoKState = _AUTO_CALIBRATION_DONE;
            }
        }

        // Disable auto calibration
        Scaler32SetBit(PB18081_24_AUX_AUTO_K, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), 0x00);

        // Clear auto_k_done & Fail
        Scaler32SetBit(PB18081_24_AUX_AUTO_K, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

        ucAutoCalibrationCount++;
    }

    if(enumDpAuxTxAutoKState == _AUTO_CALIBRATION_DONE)
    {
        g_ucDpAuxTxPVth = (ucDpAuxTxPVthBackup + ucDpAuxTxPVthBackup2) / 2 + _DP_AUX_AUTO_CALIBRATION_VTH;
        g_ucDpAuxTxNVth = (ucDpAuxTxNVthBackup + ucDpAuxTxNVthBackup2) / 2;
    }
    else
    {
        g_ucDpAuxTxPVth = _DP_AUX_AUTO_CALIBRATION_VTH;
        g_ucDpAuxTxNVth = 0;
    }

#if(_HW_DP_AUX_AUTO_CALIBRATION_ORIENTATION == _DP_AUX_AUTO_CALIBRATION_PN_INVERSE)
    Scaler32SetBit(PB18080_18_AUX_6, ~_BIT6, 0x00);
#endif
}
#endif

//--------------------------------------------------
// Description  : Dp Tx Aux Power Off Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxTxPowerOffProc(void)
{
    // Power Down Downstream
    if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
    {
        pData[0] = 0x02;
        ScalerDpAuxTxNativeWrite(0x00, 0x06, 0x00, 1, pData);
    }

    // Power Down Aux CH
    Scaler32SetBit(PB18081_40_AUX_TX_CTRL, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : Dp Tx Aux PN Swap
// Input Value  : Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxTxPNSwap(EnumTypeCOrientation enumTypeCOrientation)
{
    if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
    {
        // Disable Aux DPHY Swap
        Scaler32SetBit(PB18081_00_AUX_DIG_PHY, ~_BIT0, 0x00);
    }
    else
    {
        // Ensable Aux DPHY Swap
        Scaler32SetBit(PB18081_00_AUX_DIG_PHY, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Dp Tx Aux Set Timeout
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxTxSetTimeout(EnumDpAuxTxTimeoutValue enumDpAuxTxTimeoutValue)
{
    switch(enumDpAuxTxTimeoutValue)
    {
        case _AUX_TIMEOUT_400US:
            // Timeout = (21 + 1) * 512 / 28M = 402us
            Scaler32SetByte(PB18081_44_AUX_TIMEOUT, 0, 0x15);
            break;

        case _AUX_TIMEOUT_800US:
            // Timeout = (43 + 1) * 512 / 28M = 804us
            Scaler32SetByte(PB18081_44_AUX_TIMEOUT, 0, 0x2B);
            break;

        case _AUX_TIMEOUT_1200US:
            // Timeout = (65 + 1) * 512 / 28M = 1207us
            Scaler32SetByte(PB18081_44_AUX_TIMEOUT, 0, 0x41);
            break;

        case _AUX_TIMEOUT_1600US:
            // Timeout = (87 + 1) * 512 / 28M = 1609us
            Scaler32SetByte(PB18081_44_AUX_TIMEOUT, 0, 0x57);
            break;

        case _AUX_TIMEOUT_2000US:
            // Timeout = (109 + 1) * 512 / 28M = 2011us
            Scaler32SetByte(PB18081_44_AUX_TIMEOUT, 0, 0x6D);
            break;

        case _AUX_TIMEOUT_2400US:
            // Timeout = (131 + 1) * 512 / 28M = 2413us
            Scaler32SetByte(PB18081_44_AUX_TIMEOUT, 0, 0x83);
            break;

        case _AUX_TIMEOUT_2800US:
            // Timeout = (153 + 1) * 512 / 28M = 2816us
            Scaler32SetByte(PB18081_44_AUX_TIMEOUT, 0, 0x99);
            break;

        case _AUX_TIMEOUT_3200US:
            // Timeout = (175 + 1) * 512 / 28M = 3218us
            Scaler32SetByte(PB18081_44_AUX_TIMEOUT, 0, 0xAF);
            break;

        case _AUX_TIMEOUT_3600US:
            // Timeout = (196 + 1) * 512 / 28M = 3602us
            Scaler32SetByte(PB18081_44_AUX_TIMEOUT, 0, 0xC4);
            break;

        default:
            break;
    }
}
#endif // End for #if(_DP_PHY_TX_SUPPORT == _ON)
