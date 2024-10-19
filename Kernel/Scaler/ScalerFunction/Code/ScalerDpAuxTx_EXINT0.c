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
// ID Code      : ScalerDpAuxTx_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPTX_AUX_EXINT0__

#include "ScalerFunctionInclude.h"
#include "DpAuxTx/ScalerDpAuxTx.h"




#if(_DP_PHY_TX_SUPPORT == _ON)
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
// Description  : DP Tx Native Aux Read For Int0
// Input Value  : ucCommand --> Native Aux Read Command
//                ucHighAddress --> High Byte of  Native Aux Read Address
//                ucMidAddress --> Middle Byte of  Native Aux Read Address
//                ucLowAddress --> Low Byte of  Native Aux Read Address
//                ucLength --> Native Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Read
// Output Value : TRUE --> Native Aux Read Sucessful
//--------------------------------------------------
BYTE ScalerDpAuxTxNativeRead_EXINT0(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    bit bReceiveFlag = _FALSE;
    BYTE ucAuxPollingCount = 0;
    BYTE ucDataCount = 0;
    BYTE ucReadRetryNum = 0;
    BYTE ucResidualReceiveTimes = 16;
    BYTE ucCheckLength = 0;
    DWORD ulAddr = TO_DWORD(0x00, ucAddrH, ucAddrM, ucAddrL);

    // if aux_en = 0, return false
    if(Scaler32GetBit_EXINT0(PB18081_40_AUX_TX_CTRL, _BIT0) == 0x00)
    {
        return _FALSE;
    }

    if((ulAddr + ucLength) > 0x100000)
    {
        ucLength = 0x100000 - ulAddr;
    }

    // Disable Short HPD Int.
    ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

    // Enable AUX FW Handle Mode & Disable Address only transaction
    Scaler32SetBit_EXINT0(PB18081_4C_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT5 | _BIT0), _BIT5);

    do
    {
        ucReadRetryNum = 0;

        // Enable Retry Mechanism
        Scaler32SetBit_EXINT0(PB18081_80_AUX_RETRY_2, ~_BIT7, 0x00);

        // Enable Timeout HW Retry
        Scaler32SetBit_EXINT0(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

        // CLR Flag
        Scaler32SetDWord_EXINT0(PB18081_84_AUX_IRQ_EVENT, 0x3F);

        // Reset AUX FIFO
        Scaler32SetBit_EXINT0(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        ucLength = ucLength - ucCheckLength;

        if(ucLength == 0)
        {
            ucLength = 1;
        }
        else if(ucLength > 16)
        {
            ucLength = 16;
        }

        ulAddr += ucCheckLength;

        // Setting DPCD Read Address & TX_LEN = ucLength-1
        Scaler32SetDWord_EXINT0(PB18081_50_AUXTX_REQ_CMD, (_BIT31 | _BIT28 | (ulAddr << 8) | (ucLength - 1)));

        // Reset AUX Start Bit
        Scaler32SetBit_EXINT0(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

        // Enable Aux to Start Read
        Scaler32SetBit_EXINT0(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

        do
        {
            // Delay Time us [400,x] Delay 400us
            DELAY_XUS_EXINT(400);

            // Delay Time us [5,175] Polling AUX Done Bit (Delay 25 Loop = 175us)
            for(ucAuxPollingCount = 0; ucAuxPollingCount < 25; ucAuxPollingCount++)
            {
                DELAY_5US_EXINT();

                if(Scaler32GetBit_EXINT0(PB18081_84_AUX_IRQ_EVENT, _BIT5) == _BIT5)
                {
                    // Reply Error or Nack or Command is not ACK
                    if((Scaler32GetBit_EXINT0(PB18081_84_AUX_IRQ_EVENT, _BIT2) != 0x00) || ((Scaler32GetBit_EXINT0(PB18081_58_AUX_REPLY_CMD, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) & (_BIT5 | _BIT4)) != 0x00))
                    {
                        // CLR Flag
                        Scaler32SetDWord_EXINT0(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                        if(ucReadRetryNum != _DP_AUX_TX_RETRY_LIMIT)
                        {
                            // Reset AUX FIFO
                            Scaler32SetBit_EXINT0(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            // Reset AUX Start Bit
                            Scaler32SetBit_EXINT0(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                            // Enable Aux to Start Read
                            Scaler32SetBit_EXINT0(PB18081_4C_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
                        }
                        else
                        {
                            // Disable Timeout Retry
                            Scaler32SetBit_EXINT0(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            Scaler32SetDWord_EXINT0(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            Scaler32SetBit_EXINT0(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            // Enable Short HPD Int.
                            ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                            // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
                            Scaler32SetBit_EXINT0(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);
                        }
                    }
                    else
                    {
                        ucCheckLength = Scaler32GetBit_EXINT0(PB18081_78_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

                        // Avoid Aux Reply too much data
                        if(ucCheckLength > ucLength)
                        {
                            ucCheckLength = ucLength;
                        }

                        // Read Data From Buffer
                        for(ucDataCount = 0; ucDataCount < ucCheckLength; ucDataCount++)
                        {
                            *pucReadArray = Scaler32GetByte_EXINT0(PB18081_5C_AUX_REPLY_DATA, 0x00);
                            pucReadArray++;
                        }

                        if(ucCheckLength >= ucLength)
                        {
                            // Disable Timeout Retry
                            Scaler32SetBit_EXINT0(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            Scaler32SetDWord_EXINT0(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            Scaler32SetBit_EXINT0(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            // Enable Short HPD Int.
                            ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                            // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
                            Scaler32SetBit_EXINT0(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

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
                    if(Scaler32GetBit_EXINT0(PB18081_84_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                    {
                        // Disable Timeout Retry
                        Scaler32SetBit_EXINT0(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                        // CLR Flag
                        Scaler32SetDWord_EXINT0(PB18081_84_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        Scaler32SetBit_EXINT0(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Enable Short HPD Int.
                        ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                        // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
                        Scaler32SetBit_EXINT0(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

                        return _FALSE;
                    }
                }
            }

            // Increasing Retry Num
            ucReadRetryNum++;
        }
        while((ucReadRetryNum <= _DP_AUX_TX_RETRY_LIMIT) && (Scaler32GetBit_EXINT0(PB18081_78_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00) && (bReceiveFlag == _FALSE));

        // clear receive flag
        bReceiveFlag = _FALSE;

        // residual times decrease
        ucResidualReceiveTimes--;
    }
    while(ucResidualReceiveTimes > 0);

    // Disable Timeout Retry
    Scaler32SetBit_EXINT0(PB18081_80_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    Scaler32SetDWord_EXINT0(PB18081_84_AUX_IRQ_EVENT, 0x3F);

    // Reset AUX FIFO
    Scaler32SetBit_EXINT0(PB18081_6C_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable Short HPD Int.
    ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

    // Delay Time us [400,x] Delay 400us
    DELAY_XUS_EXINT(400);

    // Switch to Native Aux Cmd Mode Prevent form Dp MSG Circuit Break Down
    Scaler32SetBit_EXINT0(PB18081_50_AUXTX_REQ_CMD, ~(_BIT31 | _BIT30 | _BIT29 | _BIT28), _BIT31);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Tx Aux PN Swap
// Input Value  : Orientation
// Output Value : None
//--------------------------------------------------
void ScalerDpAuxTxPNSwap_EXINT0(EnumTypeCOrientation enumTypeCOrientation)
{
    if(enumTypeCOrientation == _TYPE_C_ORIENTATION_UNFLIP)
    {
        // Disable Aux DPHY Swap
        Scaler32SetBit_EXINT0(PB18081_00_AUX_DIG_PHY, ~_BIT0, 0x00);
    }
    else
    {
        // Ensable Aux DPHY Swap
        Scaler32SetBit_EXINT0(PB18081_00_AUX_DIG_PHY, ~_BIT0, _BIT0);
    }
}

#endif // End for #if(_DP_TX_SUPPORT == _ON)
