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
// ID Code      : ScalerCec_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_CEC__

#include "ScalerFunctionInclude.h"
#include "Cec/ScalerCec.h"

#if(_HDMI_CEC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


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
// Description  : CEC interrupt routine
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecIntHandler_EXINT0(void)
{
#if(_CEC_RX_INT_SUPPORT == _ON)
#if(_HW_HDMI_IRQ_PRIORITY_MODE == _HDMI_IRQ_NEW_MODE)
    if(GET_HDMI_CEC_IRQ_FLAG() == _TRUE)
#endif
    {
        // rx_int=1 or DB_EOM received in snooping mode
        if((ScalerGetBit_EXINT(P18_B0_CEC_RXCR0_1, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(P18_B1_CEC_RXCR0_2, _BIT6) == _BIT6))
        {
            bit bReturn = 0;

            if((GET_CEC_FUNCTION_ENABLE() == _FALSE) || (ScalerCecCheckRxSituation_EXINT0() == _FALSE))
            {
                bReturn = 1;
            }

            if(bReturn == 0)
            {
                ScalerCecRxMsgReceiving_EXINT0();
            }

            // clr rx_int
            ScalerSetBit_EXINT(P18_B1_CEC_RXCR0_2, ~_BIT6, _BIT6);

            // clr cec_all_irq_keep & wakeup_irq_keep
            ScalerSetBit_EXINT(P19_E0_CEC_POWER_SAVING_MODE, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT1));

            // reset
            ScalerSetBit_EXINT(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
            ScalerSetBit_EXINT(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);
        }
    }
#endif

/*
    // receive
    if(ScalerGetBit_EXINT(P18_B1_CEC_RXCR0_2, _BIT6) == _BIT6)
    {
        ScalerSetBit_EXINT(P18_B1_CEC_RXCR0_2, ~(_BIT6), _BIT6);
    }

    // transmission
    if(ScalerGetBit_EXINT(P18_B5_CEC_TXCR0_2, _BIT1) == _BIT1)
    {
        ScalerSetBit_EXINT(P18_B5_CEC_TXCR0_2, ~(_BIT1), _BIT1);
    }

    // overflow

    // clear all CEC interrupts status
    ScalerSetBit_EXINT(P19_E0_CEC_POWER_SAVING_MODE, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1));
    ScalerSetBit_EXINT(P19_E4_CEC_INTCR_02, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
*/
}

#if(_CEC_RX_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : check Cec Rx situation
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
BYTE ScalerCecCheckRxSituation_EXINT0(void)
{
    // B1[7] -> data EOM, B2[7] -> header EOM
    // check whether rx_fifo overflow or receive another start-bit when dealing with CEC data
    if((ScalerGetBit_EXINT(P18_B1_CEC_RXCR0_2, _BIT7) == 0x00) &&
       (ScalerGetBit_EXINT(P18_B2_CEC_RTCR0_RSV_1, _BIT7) == 0x00))
    {
        // B0[7]: Rx en, B1[6]: Rx int flag
        if((ScalerGetBit_EXINT(P18_B0_CEC_RXCR0_1, _BIT7) == 0x00) &&
           (ScalerGetBit_EXINT(P18_B1_CEC_RXCR0_2, _BIT6) == _BIT6))
        {
            // reset
            ScalerSetBit_EXINT(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
            ScalerSetBit_EXINT(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);
        }

        return 0x00;
    }

    return 0x01;
}

//--------------------------------------------------
// Description  : Cec Rx Receive MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecRxMsgReceiving_EXINT0(void)
{
#if((_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2) || (_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_3))
    BYTE ucDestLa = (ScalerGetByte_EXINT(P18_E3_CEC_RX_FIFO_ADDRESS) & 0x0F);
#else
    BYTE ucDestLa = _CEC_LA_TV;
#endif

    // Check incoming msg available
    // Avaiable Message: 1. <Polling Message> w/ ack  2. Others mesage (DB# > 0)
    if((ScalerGetBit_EXINT(P18_B1_CEC_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00) ||
       (ucDestLa == _CEC_LA_TV))
    {
        // if Last CEC RX MSG hasn't been read by DP SRC
        if((GET_CEC_RX_MSG_ANALYZING() == _TRUE) || (g_ucCecRxTotalQueueMsgIdx > 0x00))
        {
            // Load Cec Rx Received MSG to backup fifo
            ScalerCecRxWriteIntoBackupFifo_EXINT0();
        }
        else
        {
            // Check no CEC msg will be sent to RX DPCD from Cec Rx backup fifo
            if((g_ucCecRxBackupFifoWaterLevel == 0x00) && (GET_CEC_RX_READ_FROM_BACKUP_FIFO() == _FALSE))
            {
                // Load Cec Rx Received MSG to RxInfo struct
                ScalerCecRxWriteIntoRxInfoStruct_EXINT0();
            }
            else
            {
                // Load Cec Rx Received MSG to backup fifo
                ScalerCecRxWriteIntoBackupFifo_EXINT0();
            }
        }
    }
}

//--------------------------------------------------
// Description  : Write Cec Rx Received Msg to Cec Rx BackupUp Fifo
// Input Value  : None
// Output Value : Bit
//--------------------------------------------------
void ScalerCecRxWriteIntoBackupFifo_EXINT0(void)
{
#if((_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2) || (_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_3))
    BYTE ucHbInfo = ScalerGetByte_EXINT(P18_E3_CEC_RX_FIFO_ADDRESS);
#else
    BYTE ucHbInfo = ((ScalerGetByte_EXINT(P18_B0_CEC_RXCR0_1) & 0x0F) << 4);

    // broadcast msg
    if(ScalerGetBit_EXINT(P18_A9_CEC_RTCR0_2, _BIT6) == _BIT6)
    {
        ucHbInfo |= 0x0F;
    }
#endif

    // (BackFifoSize - overflow Buffer) - Waterlevel < Rx Read count. means Not enough space for BackupFIFO
    // Both situation will set CEC Rx force Nack for Next CEC frame.
    if((_CEC_RX_BACKUP_FIFO_SIZE - _CEC_RX_BACKUP_FIFO_OVERFLOW_BUFFER - g_ucCecRxBackupFifoWaterLevel) < ((BYTE)(ScalerGetBit_EXINT(P18_B1_CEC_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) + 2)))
    {
        // Set CEC Rx force Nack/ Negative Ack
        ScalerSetBit_EXINT(P18_A6_CEC_CR0_7, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT5 | _BIT4));
    }

    // 2 Byte for Length and HB Info
    if(_CEC_RX_BACKUP_FIFO_SIZE <= (g_ucCecRxBackupFifoWaterLevel + 2))
    {
        return;
    }

    // Fill CEC RX Info into Backup buffer
    g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel] = ScalerGetBit_EXINT(P18_B1_CEC_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel + 1] = ucHbInfo;

    if((g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel] + g_ucCecRxBackupFifoWaterLevel + 2) > _CEC_RX_BACKUP_FIFO_SIZE)
    {
        g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel] = _CEC_RX_BACKUP_FIFO_SIZE - g_ucCecRxBackupFifoWaterLevel - 2;
    }

    for(BYTE ucLoopIndex = 0; ucLoopIndex < g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel]; ucLoopIndex++)
    {
        g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel + 2 + ucLoopIndex] = ScalerGetByte_EXINT(P18_D3_CEC_RXDR1_1 + ucLoopIndex);
    }

    g_ucCecRxBackupFifoWaterLevel += (g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel] + 2);

    // Total Queue Received Message Add one
    // Although the Backup Fifo is not count by CEC Msg Num, this counter still work
    g_ucCecRxTotalQueueMsgIdx = g_ucCecRxTotalQueueMsgIdx + 1;
}


//--------------------------------------------------
// Description  : Write Cec Rx Received Msg to CEC RX Info Struct
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecRxWriteIntoRxInfoStruct_EXINT0(void)
{
    // Fill CEC RX Info into xdata
    g_stCecRxReceivedInfo.ucDbLength = ScalerGetBit_EXINT(P18_B1_CEC_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#if((_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2) || (_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_3))
    g_stCecRxReceivedInfo.ucReceivedHb = ScalerGetByte_EXINT(P18_E3_CEC_RX_FIFO_ADDRESS);
#else
    g_stCecRxReceivedInfo.ucReceivedHb = ((ScalerGetByte_EXINT(P18_B0_CEC_RXCR0_1) & 0x0F) << 4);

    // broadcast msg
    if(ScalerGetBit_EXINT(P18_A9_CEC_RTCR0_2, _BIT6) == _BIT6)
    {
        g_stCecRxReceivedInfo.ucReceivedHb |= 0x0F;
    }
#endif

    __real_memset(g_stCecRxReceivedInfo.pucReceivedDb, 0, 16);
    for(BYTE ucLoopIndex = 0; ucLoopIndex < g_stCecRxReceivedInfo.ucDbLength; ucLoopIndex++)
    {
        g_stCecRxReceivedInfo.pucReceivedDb[ucLoopIndex] = ScalerGetByte_EXINT(P18_D3_CEC_RXDR1_1 + ucLoopIndex);
    }

    // Total Queue Received Message Add one
    // Although the Backup Fifo is not count by CEC Msg Num, this counter still work
    g_ucCecRxTotalQueueMsgIdx = g_ucCecRxTotalQueueMsgIdx + 1;

    SET_CEC_RX_READ_DONE();
}
#endif
#endif
