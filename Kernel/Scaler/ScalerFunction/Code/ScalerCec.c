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
// ID Code      : ScalerCec.c No.0000
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
volatile StructCecRxReceivedInfo g_stCecRxReceivedInfo;
StructCecTxTransmitInfo g_stCecTxTransmitInfo;
volatile StructCecGeneralCtrl g_stCecGeneralCtrl;
volatile BYTE g_ucCecRxBackupFifoWaterLevel;
volatile BYTE g_ucCecRxTotalQueueMsgIdx;
BYTE g_pucCecRxBackupFifo[_CEC_RX_BACKUP_FIFO_SIZE];
StructCecEventNotify g_stCecEventNotify;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initialize CEC setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecInitial(void)
{
    DebugMessageCEC("CEC Initial", 0x00);

    // Disable CEC
    ScalerSetBit(P18_A0_CEC_CR0_1, ~(_BIT7 | _BIT6), 0x00);

    // CEC input clock : iosc (28 MHz)
    // ScalerSetBit(P18_A1_CEC_CR0_2, ~(_BIT7 | _BIT6), 0x00);

    // M2PLL 351MHz
    if(ScalerGetBit(P18_A1_CEC_CR0_2, (_BIT7 | _BIT6)) == _BIT6)
    {
        // -- 3/75(=0x4B) = 0.04Mhz
        ScalerSetByte(P18_A3_CEC_CR0_4, 0x4B);
        // -- 351.0/117(=0x75) = 3.0Mhz
        ScalerSetByte(P18_A4_CEC_CR0_5, 0x75);
    }
    else if(ScalerGetBit(P18_A1_CEC_CR0_2, (_BIT7 | _BIT6)) == 0x00)
    {
        // iosc 28MHz
        // -- 1/25(=0x19) = 0.04Mhz
        ScalerSetByte(P18_A3_CEC_CR0_4, 0x19);
        // -- 28.0/28(=0x1C) = 1.0Mhz
        ScalerSetByte(P18_A4_CEC_CR0_5, 0x1C);
    }

    // close pad rising time
    // ScalerSetByte(P18_A5_CEC1_CR0_6, 0x00);

    // change power source
    // ScalerSetByte(P19_F1_CEC1_POWER_SELECT, 0x84);

    // Physical Signal Property Setting
    // Cec Rx
    ScalerSetByte(P18_E5_CEC_RXTCR0_1, _CEC_RX_START_LOW_TIME);
    ScalerSetByte(P18_E6_CEC_RXTCR0_2, _CEC_RX_START_PERIOD_TIME);
    ScalerSetByte(P18_E7_CEC_RXTCR0_3, _CEC_RX_DATA_SAMPLE_TIME);
    ScalerSetByte(P18_E8_CEC_RXTCR0_4, _CEC_RX_DATA_PERIOD_TIME);
    ScalerSetByte(P18_E9_CEC_RXTCR0_5, _CEC_RX_START_HIGH_TIME);

    // Cec Tx
    ScalerSetByte(P18_EF_CEC_TXTCR0_1, _CEC_TX_START_LOW_TIME);
    ScalerSetByte(P18_F1_CEC_TXTCR0_2, _CEC_TX_START_HIGH_TIME);
    ScalerSetByte(P18_F2_CEC_TXTCR1_1, _CEC_TX_DATA_LOW_TIME);
    ScalerSetByte(P18_F3_CEC_TXTCR1_2, _CEC_TX_DATA_WIDTH_TIME);
    ScalerSetByte(P18_F4_CEC_TXTCR1_3, _CEC_TX_DATA_HIGH_TIME);

    // Setting Line Error Notification = 3.6ms
    ScalerSetBit(P18_F5_CEC_RXTCR1_ACK_0, ~(_BIT6 | _BIT2), _BIT6);
    ScalerSetByte(P18_F8_CEC_RXTCR1_ERR, _CEC_RX_LINE_ERR_NOTIFY_TIME);

    // Set Tx ack reference (due to HW 5T debounce)
    ScalerSetBit(P18_F5_CEC_RXTCR1_ACK_0, ~(_BIT5 | _BIT2), _BIT5);
    ScalerSetByte(P18_F6_CEC_RXTCR1_ACK_1, _CEC_TX_DATA_LOW_TIME - 5);

    // Enable CEC
#if(_HW_HDMI_CEC_ANALOG_GEN == _HW_CEC_ANALOG_GEN_TYPE_0)
    ScalerSetBit(P19_F2_CEC_DRV_CTRL, ~(_BIT1 | _BIT0), _BIT0);  // Revise cec drv to 90uA
#elif(_HW_HDMI_CEC_ANALOG_GEN == _HW_CEC_ANALOG_GEN_TYPE_1)
    ScalerSetBit(P19_F2_CEC_DRV_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));  // Revise cec drv to 100uA (default)
#endif
    ScalerSetBit(P19_F0_GDI_CEC_ANALOG_1, ~_BIT7, _BIT7);
    ScalerSetBit(P18_A0_CEC_CR0_1, ~(_BIT7 | _BIT6), _BIT6);

    // CEC Rx/Tx LA Set to LA = 0
    ScalerSetBit(P18_A0_CEC_CR0_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _CEC_LA_TV);
    ScalerSetBit(P18_B4_CEC_TXCR0_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | (_CEC_LA_TV << 3)));

    // Cec Rx reset
    ScalerSetBit(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);

    // Cec Tx reset
    ScalerSetBit(P18_B4_CEC_TXCR0_1, ~(_BIT2 | _BIT1), _BIT1);

    // Clear interrupt flag
    ScalerSetBit(P18_B1_CEC_RXCR0_2, ~_BIT6, _BIT6);
    ScalerSetBit(P18_B5_CEC_TXCR0_2, ~_BIT1, _BIT1);
    ScalerSetBit(P19_E0_CEC_POWER_SAVING_MODE, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1));
    ScalerSetBit(P19_E4_CEC_INTCR_02, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Disable interrupt
    ScalerSetBit(P19_E0_CEC_POWER_SAVING_MODE, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

#if(_CEC_RX_INT_SUPPORT == _ON)
    ScalerSetBit(P19_E0_CEC_POWER_SAVING_MODE, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6));
    ScalerSetBit(P18_B1_CEC_RXCR0_2, ~_BIT6, _BIT6);
    ScalerSetBit(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6 | _BIT4), (_BIT4));

#if((_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_1) || (_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_3))
    ScalerSetBit(P18_B2_CEC_RTCR0_RSV_1, ~(_BIT7 | _BIT1 | _BIT0), _BIT0);
#endif

#endif

    // Cec Variable Initial Reset
    ScalerCecVariableReset();

    // --------------------------------------
    // Cec Eco Function Enable / Disable
    // --------------------------------------
#if(_HDMI_CEC_ARBITRATION_MODE_FIXED_VERSION == _ON)
    // Arbitration mode CEC mode Enable
    ScalerSetBit(P18_F5_CEC_RXTCR1_ACK_0, ~(_BIT2 | _BIT0), _BIT0);
#else
    // Arbitration mode CEC mode Disable
    ScalerSetBit(P18_F5_CEC_RXTCR1_ACK_0, ~(_BIT2 | _BIT0), 0x00);
#endif

#if(_HDMI_CEC_RX_LOWIMPEDANCE_FIXED_VERSION == _ON)
    // Rx Not detectect Issue ECO Enable
    ScalerSetBit(P18_F9_CEC_RXTCR1_RSV_0, ~(_BIT6 | _BIT3), _BIT3);
#else
    // Rx Not detectect Issue ECO Disable
    ScalerSetBit(P18_F9_CEC_RXTCR1_RSV_0, ~(_BIT6 | _BIT3), 0x00);
#endif

#if(_HDMI_CEC_MULTI_LA_FREETIME_FIXED_VERSION == _ON)
    // Multi LA Freetime Issue ECO Enable
    ScalerSetBit(P18_D1_CEC_TXDR_FIFO_RSV_1, ~_BIT4, _BIT4);
#else
    // Multi LA Freetime Issue ECO Disable
    ScalerSetBit(P18_D1_CEC_TXDR_FIFO_RSV_1, ~_BIT4, 0x00);
#endif

#if(_HDMI_CEC_MATCH_ADDR_CLEAR_FIXED_VERSION == _ON)
    // Match address clear Issue ECO Enable
    ScalerSetBit(P18_D1_CEC_TXDR_FIFO_RSV_1, ~_BIT5, _BIT5);
#else
    // Match address clear Issue ECO Disable
    ScalerSetBit(P18_D1_CEC_TXDR_FIFO_RSV_1, ~_BIT5, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Cec Rx Received MSG Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecRxProcess(void)
{
    if(GET_CEC_FUNCTION_ENABLE() == _FALSE)
    {
        return;
    }

    // Check && Load to Struct Fifo
    ScalerCecRxReadOutFromBackupFifo();

#if(_CEC_RX_INT_SUPPORT == _OFF)
    if(ScalerCecCheckRxSituation() == _FALSE)
    {
        return;
    }

    ScalerCecRxMsgReceiving();
#endif

#if((_CEC_RX_INT_SUPPORT == _ON) && ((_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_0) || (_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2)))
    ScalerCecPollingMsgReceiving();
#endif
}

//--------------------------------------------------
// Description  : Set Cec Rx struct from Cec Rx BackupUp Fifo
// Input Value  : None
// Output Value : Bit
//--------------------------------------------------
void ScalerCecRxReadOutFromBackupFifo(void)
{
    CLR_CEC_RX_READ_FROM_BACKUP_FIFO();

    // Polling Backup Buffer
    if((GET_CEC_RX_READ_DONE() == _FALSE) && (GET_CEC_RX_MSG_ANALYZING() == _FALSE) && (g_ucCecRxBackupFifoWaterLevel != 0x00))
    {
        // Fill CEC RX Info into xdata
        g_stCecRxReceivedInfo.ucDbLength = g_pucCecRxBackupFifo[0];
        g_stCecRxReceivedInfo.ucReceivedHb = g_pucCecRxBackupFifo[1];

        DebugMessageCEC("<= Cec0 Rx Backup Fifo: HB ", g_stCecRxReceivedInfo.ucReceivedHb);

        memset(g_stCecRxReceivedInfo.pucReceivedDb, 0, 16);
        for(pData[0] = 0; pData[0] < g_stCecRxReceivedInfo.ucDbLength; pData[0]++)
        {
            g_stCecRxReceivedInfo.pucReceivedDb[pData[0]] = g_pucCecRxBackupFifo[2 + pData[0]];
            DebugMessageCEC("<= Cec0 Rx Backup Fifo: DB ", g_stCecRxReceivedInfo.pucReceivedDb[pData[0]]);
        }

        DebugMessageCEC("CEC0 RX Backup Fifo Finished", 0x00);
        SET_CEC_RX_READ_DONE();

        // Shift Cec Rx Backup buffer
        BYTE pucBackupFifoTemp[_CEC_RX_BACKUP_FIFO_SIZE] = {0};
        memcpy(pucBackupFifoTemp, &g_pucCecRxBackupFifo[g_stCecRxReceivedInfo.ucDbLength + 2], (_CEC_RX_BACKUP_FIFO_SIZE - (g_stCecRxReceivedInfo.ucDbLength + 2)));
        memcpy(g_pucCecRxBackupFifo, &pucBackupFifoTemp, _CEC_RX_BACKUP_FIFO_SIZE);

        g_ucCecRxBackupFifoWaterLevel -= (g_stCecRxReceivedInfo.ucDbLength + 2);

        // Use 10 as a Buffer to check there is enough space for CEC Rx to receive new CEC Msg
        if(g_ucCecRxBackupFifoWaterLevel < _CEC_RX_BACKUP_FIFO_SIZE - 10)
        {
            // CEC RX Ack Set to HW Mode
            ScalerSetBit(P18_A6_CEC_CR0_7, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), 0x00);
        }

        SET_CEC_RX_READ_FROM_BACKUP_FIFO();
    }
}

//--------------------------------------------------
// Description  : Write Cec Rx Received Msg to Cec Rx BackupUp Fifo
// Input Value  : None
// Output Value : Bit
//--------------------------------------------------
void ScalerCecRxWriteIntoBackupFifo(void)
{
#if((_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2) || (_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_3))
    BYTE ucHbInfo = ScalerGetByte(P18_E3_CEC_RX_FIFO_ADDRESS);
#else
    BYTE ucHbInfo = ((ScalerGetByte(P18_B0_CEC_RXCR0_1) & 0x0F) << 4);

    // broadcast msg
    if(ScalerGetBit(P18_A9_CEC_RTCR0_2, _BIT6) == _BIT6)
    {
        ucHbInfo |= 0x0F;
    }
#endif

    // (BackFifoSize - overflow Buffer) - Waterlevel < Rx Read count. means Not enough space for BackupFIFO
    // Both situation will set CEC Rx force Nack for Next CEC frame.
    if((_CEC_RX_BACKUP_FIFO_SIZE - _CEC_RX_BACKUP_FIFO_OVERFLOW_BUFFER - g_ucCecRxBackupFifoWaterLevel) < ((BYTE)(ScalerGetBit(P18_B1_CEC_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) + 2)))
    {
        // Set CEC Rx force Nack/ Negative Ack
        ScalerSetBit(P18_A6_CEC_CR0_7, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT5 | _BIT4));
    }

    // 2 Byte for Length and HB Info
    if(_CEC_RX_BACKUP_FIFO_SIZE <= (g_ucCecRxBackupFifoWaterLevel + 2))
    {
        return;
    }

    // Fill CEC RX Info into Backup buffer
    g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel] = ScalerGetBit(P18_B1_CEC_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel + 1] = ucHbInfo;

    if((g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel] + g_ucCecRxBackupFifoWaterLevel + 2) > _CEC_RX_BACKUP_FIFO_SIZE)
    {
        g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel] = _CEC_RX_BACKUP_FIFO_SIZE - g_ucCecRxBackupFifoWaterLevel - 2;
    }

    DebugMessageCEC("Cec Rx Read: HB (load to backup)", g_stCecRxReceivedInfo.ucReceivedHb);

    for(pData[0] = 0; pData[0] < g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel]; pData[0]++)
    {
        g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel + 2 + pData[0]] = ScalerGetByte(P18_D3_CEC_RXDR1_1 + pData[0]);
        DebugMessageCEC("Cec Rx Read: DB (load to backup)", g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel + 2 + pData[0]]);
    }

    g_ucCecRxBackupFifoWaterLevel += (g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel] + 2);

    // Total Queue Received Message Add one
    // Although the Backup Fifo is not count by CEC Msg Num, this counter still work
    g_ucCecRxTotalQueueMsgIdx = g_ucCecRxTotalQueueMsgIdx + 1;
}

#if(_CEC_RX_INT_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Cec Rx Receive MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecRxMsgReceiving(void)
{
#if((_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2) || (_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_3))
    BYTE ucDestLa = (ScalerGetByte(P18_E3_CEC_RX_FIFO_ADDRESS) & 0x0F);
#else
    BYTE ucDestLa = 0xFF;
#endif

    if(GET_CEC_TX_STATE() != _CEC_TX_SENDING_STATE)
    {
        // Check incoming msg available
        // Avaiable Message: 1. <Polling Message> w/ ack  2. Others mesage (DB# > 0)
        if((ScalerGetBit(P18_B1_CEC_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00) ||
           (ucDestLa == _CEC_LA_TV))
        {
            // if Last CEC RX MSG hasn't been analyzed done by user
            if((GET_CEC_RX_MSG_ANALYZING() == _TRUE) || (g_ucCecRxTotalQueueMsgIdx > 0x00))
            {
                // Load Cec Rx Received MSG to backup fifo
                ScalerCecRxWriteIntoBackupFifo();
            }
            else
            {
                // Check no CEC msg will be sent to RX DPCD from Cec Rx backup fifo
                if((g_ucCecRxBackupFifoWaterLevel == 0x00) && (GET_CEC_RX_READ_FROM_BACKUP_FIFO() == _FALSE))
                {
                    // Load Cec Rx Received MSG to RxInfo struct
                    ScalerCecRxWriteIntoRxInfoStruct();
                }
                else
                {
                    // Load Cec Rx Received MSG to backup fifo
                    ScalerCecRxWriteIntoBackupFifo();
                }

                DebugMessageCEC("Cec RX Read Finished", 0x00);
            }
        }

        // reset
        ScalerSetBit(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetBit(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);
    }
}

//--------------------------------------------------
// Description  : check Cec Rx situation
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerCecCheckRxSituation(void)
{
    // Check EOM (B1[7]: Rx EOM, B2[7]: Header EOM)
    if((ScalerGetBit(P18_B1_CEC_RXCR0_2, _BIT7) == 0x00) &&
       (ScalerGetBit(P18_B2_CEC_RTCR0_RSV_1, _BIT7) == 0x00))
    {
        // B0[7]: Rx en, B1[6]: Rx int flag
        if((ScalerGetBit(P18_B0_CEC_RXCR0_1, _BIT7) == 0x00) &&
           (ScalerGetBit(P18_B1_CEC_RXCR0_2, _BIT6) == _BIT6))
        {
            DebugMessageCEC("CEC: Unexpected RX condition.....", 0);

            // reset
            ScalerSetBit(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
            ScalerSetBit(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);
        }

        return _FALSE;
    }

    return _TRUE;
}
#endif

#if((_CEC_RX_INT_SUPPORT == _ON) && ((_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_0) || (_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2)))
//--------------------------------------------------
// Description  : Cec Rx Receive Polling MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecPollingMsgReceiving(void)
{
#if((_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2) || (_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_3))
    BYTE ucDestLa = (ScalerGetByte(P18_E3_CEC_RX_FIFO_ADDRESS) & 0x0F);
#else
    BYTE ucDestLa = 0xFF;
#endif

    // header_eom = 1
    if((ScalerGetBit(P18_B2_CEC_RTCR0_RSV_1, _BIT7) == _BIT7) && (GET_CEC_TX_STATE() != _CEC_TX_SENDING_STATE))
    {
        // Check incoming msg available
        // Avaiable Message: 1. <Polling Message> w/ ack
        if(ScalerGetBit(P18_B1_CEC_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
        {
            if(ucDestLa == _CEC_LA_TV)
            {
                // if Last CEC RX MSG hasn't been analyzed done by user
                if((GET_CEC_RX_MSG_ANALYZING() == _TRUE) || (g_ucCecRxTotalQueueMsgIdx > 0x00))
                {
                    // Load Cec Rx Received MSG to backup fifo
                    ScalerCecRxWriteIntoBackupFifo();
                }
                else
                {
                    // Check no CEC msg will be sent to RX DPCD from Cec Rx backup fifo
                    if((g_ucCecRxBackupFifoWaterLevel == 0x00) && (GET_CEC_RX_READ_FROM_BACKUP_FIFO() == _FALSE))
                    {
                        // Load Cec Rx Received MSG to RxInfo struct
                        ScalerCecRxWriteIntoRxInfoStruct();
                    }
                    else
                    {
                        // Load Cec Rx Received MSG to backup fifo
                        ScalerCecRxWriteIntoBackupFifo();
                    }

                    DebugMessageCEC("Cec RX Read Finished", 0x00);
                }
            }
        }

        // Reset Cec Rx
        ScalerSetBit(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetBit(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);
    }
}
#endif

//--------------------------------------------------
// Description  : Cec TX Send Msg Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecTxProcess(void)
{
    if(GET_CEC_FUNCTION_ENABLE() == _FALSE)
    {
        return;
    }

    if(GET_CEC_TX_STATE() == _CEC_TX_SENDING_STATE)
    {
        // Check Current CEC TX is avaible to send
        if(ScalerCecIsSending() == _TRUE)
        {
            DebugMessageCEC("CEC TX is Busy", 0x00);

            return;
        }
        else // cec tx free
        {
            if(ScalerGetBit(P18_B5_CEC_TXCR0_2, _BIT2) == _BIT2)
            {
                // w1c tx_eom
                // ScalerSetBit(P18_B5_CEC_TXCR0_2, ~(_BIT2 | _BIT1), _BIT2);

                SET_CEC_TX_EVENT(_CEC_TX_SENT_EVENT);
                DebugMessageCEC("CEC TX has been Ack", 0x00);
            }
            else
            {
#if(_HW_HDMI_CEC_GEN >= _HW_CEC_GEN_TYPE_1)
                // Check CEC Line error, Nack Happened?
                if(ScalerGetBit(P18_B7_CEC_TXCR0_RSV_0, _BIT7) == _BIT7)
                {
                    SET_CEC_TX_EVENT(_CEC_TX_LINE_ERROR_EVENT);
                    DebugMessageCEC("CEC0 TX Line Error Happened!!", 0x00);

                    ScalerSetBit(P18_B7_CEC_TXCR0_RSV_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                }
                else if(ScalerGetBit(P18_B7_CEC_TXCR0_RSV_0, _BIT6) == _BIT6)
                {
                    SET_CEC_TX_EVENT(_CEC_TX_HB_NACK_EVENT);
                    DebugMessageCEC("CEC TX HB Nack Happened!!", _CEC_TX_HB_NACK_EVENT);

                    ScalerSetBit(P18_B7_CEC_TXCR0_RSV_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                }
                else if(ScalerGetBit(P18_B7_CEC_TXCR0_RSV_0, _BIT5) == _BIT5)
                {
                    SET_CEC_TX_EVENT(_CEC_TX_DB_NACK_EVENT);
                    DebugMessageCEC("CEC TX DB Nack Happened!!", 0x00);

                    ScalerSetBit(P18_B7_CEC_TXCR0_RSV_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                }
                // FW workaround sol for Cec tx sent finish but none of result below..
                else if(ScalerGetBit(P18_B5_CEC_TXCR0_2, _BIT1) == _BIT1)
                {
                    SET_CEC_TX_EVENT(_CEC_TX_LINE_ERROR_EVENT);
                    DebugMessageCEC("CEC TX FAKE Line Error Happened Orz.........", 0x00);

                    ScalerSetBit(P18_B7_CEC_TXCR0_RSV_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                }
#else
                SET_CEC_TX_EVENT(_CEC_TX_HB_NACK_EVENT);
                DebugMessageCEC("CEC TX has been Nack", 0x00);
#endif
            }

            // Check if CEC TX just sent <Polling Message>, clear header_eom for Tx Rx feedback circuit
            if(g_stCecTxTransmitInfo.ucDbLength == 0)
            {
                // w1c header eom
                ScalerSetBit(P18_B2_CEC_RTCR0_RSV_1, ~(_BIT7 | _BIT1), _BIT7);
            }

            // Check Cec Tx finish transmit last message
            SET_CEC_TX_STATE(_CEC_TX_IDLE_STATE);
        }
    }

    if((GET_CEC_TX_START() == _TRUE) && (GET_CEC_TX_STATE() == _CEC_TX_IDLE_STATE))
    {
        // Fill Info into CEC TX Fifo & Send
        ScalerCecSendNewFx();
        DebugMessageCEC("CEC TX MSG Sned!!", 0x00);

        CLR_CEC_TX_START();
        SET_CEC_TX_STATE(_CEC_TX_SENDING_STATE);
    }
}

//--------------------------------------------------
// Description  : Write Cec Rx Received Msg to CEC RX Info Struct
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecRxWriteIntoRxInfoStruct(void)
{
#if((_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2) || (_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_3))
    BYTE ucHbInfo = ScalerGetByte(P18_E3_CEC_RX_FIFO_ADDRESS);
#else
    BYTE ucHbInfo = ((ScalerGetByte(P18_B0_CEC_RXCR0_1) & 0x0F) << 4);

    // broadcast msg
    if(ScalerGetBit(P18_A9_CEC_RTCR0_2, _BIT6) == _BIT6)
    {
        ucHbInfo |= 0x0F;
    }
#endif

    // Fill CEC RX Info into xdata
    g_stCecRxReceivedInfo.ucDbLength = ScalerGetBit(P18_B1_CEC_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    g_stCecRxReceivedInfo.ucReceivedHb = ucHbInfo;

    DebugMessageCEC("<= Cec Rx Read: HB", g_stCecRxReceivedInfo.ucReceivedHb);

    memset(g_stCecRxReceivedInfo.pucReceivedDb, 0, 16);
    for(pData[0] = 0; pData[0] < g_stCecRxReceivedInfo.ucDbLength; pData[0]++)
    {
        g_stCecRxReceivedInfo.pucReceivedDb[pData[0]] = ScalerGetByte(P18_D3_CEC_RXDR1_1 + pData[0]);
        DebugMessageCEC("<= Cec Rx Read: DB", g_stCecRxReceivedInfo.pucReceivedDb[pData[0]]);
    }

    // Total Queue Received Message Add one
    // Although the Backup Fifo is not count by CEC Msg Num, this counter still work
    g_ucCecRxTotalQueueMsgIdx = g_ucCecRxTotalQueueMsgIdx + 1;

    SET_CEC_RX_READ_DONE();
}

//--------------------------------------------------
// Description  : Set Cec Variable Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecVariableReset(void)
{
    // Cec rx/ tx xdata reset
    memset(&g_stCecRxReceivedInfo, 0, sizeof(g_stCecRxReceivedInfo));
    memset(&g_stCecTxTransmitInfo, 0, sizeof(g_stCecTxTransmitInfo));

    // FW flag reset
    SET_CEC_TX_STATE(_CEC_TX_IDLE_STATE);
    CLR_CEC_TX_EVENT();
    CLR_CEC_RX_READ_DONE();
    CLR_CEC_TX_START();
    CLR_CEC_FUNCTION_ENABLE();

    CLR_CEC_RX_MSG_ANALYZING();
    CLR_CEC_RX_READ_FROM_BACKUP_FIFO();

    // Cec Rx backup fifo reset
    g_ucCecRxBackupFifoWaterLevel = 0x00;
    memset(g_pucCecRxBackupFifo, 0, _CEC_RX_BACKUP_FIFO_SIZE);

    g_ucCecRxTotalQueueMsgIdx = 0x00;

    // CEC RX/ TX LA Reset
    ScalerSetBit(P18_A0_CEC_CR0_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _CEC_LA_TV);
    ScalerSetBit(P18_B4_CEC_TXCR0_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | (_CEC_LA_TV << 3)));

    DebugMessageCEC("CEC Reset", 0);
}

//--------------------------------------------------
// Description  : CEC Tx send set (w/ retry cnt)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecSendNewFx(void)
{
    BYTE ucParam = 0;

    // Cec Tx Reset
    ScalerSetBit(P18_B4_CEC_TXCR0_1, ~(_BIT2 | _BIT1), _BIT1);

    // Set Follower(destination) & Initator LA
    ScalerSetBit(P18_B5_CEC_TXCR0_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1), (GET_CEC_TX_DEST_LA_TO_SEND() << 3));
    ScalerSetBit(P18_B4_CEC_TXCR0_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (GET_CEC_TX_INIT_LA_TO_SEND() << 3));

    // Set length of data fill to CecTx Ffio & Enable CecTx fifo cnt
    ScalerSetBit(P18_B9_CEC_TXDR0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), g_stCecTxTransmitInfo.ucDbLength);
    ScalerSetBit(P18_B9_CEC_TXDR0, ~(_BIT6 | _BIT5), _BIT6); // settle down

    DebugMessageCEC("=> Cec Tx send: HB", g_stCecTxTransmitInfo.ucTransmitHb);

    // Clear & Set message into CEC Tx Fifo
    memset((volatile BYTE xdata *)P18_C0_CEC_TXDR1_1, 0x00, 16);
    for(ucParam = 0; ucParam < g_stCecTxTransmitInfo.ucDbLength; ucParam += 1)
    {
        ScalerSetByte((P18_C0_CEC_TXDR1_1 + ucParam), g_stCecTxTransmitInfo.pucTransmitDb[ucParam]);
        DebugMessageCEC("=> Cec Tx send: DB", g_stCecTxTransmitInfo.pucTransmitDb[ucParam]);
    }

    // Set Retry#
    ScalerSetBit(P18_A8_CEC_RTCR0_1, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), g_stCecTxTransmitInfo.b3RetryCnt);

    // CecTx Transmit Enable
    ScalerSetBit(P18_B4_CEC_TXCR0_1, ~(_BIT2 | _BIT1), _BIT2);
}

//--------------------------------------------------
// Description  : CEC is sending
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerCecIsSending(void)
{
    // Check cec_tx_en & EOM
    return ((ScalerGetBit(P18_B4_CEC_TXCR0_1, _BIT2) == _BIT2) &&
            (ScalerGetBit(P18_B5_CEC_TXCR0_2, _BIT2) == 0x00));
}

//--------------------------------------------------
// Description  : Eanble/Disable cec related irq
// Input Value  : Eanble/Disable
// Output Value : None
//--------------------------------------------------
void ScalerCecIrqEnable(bit bEnable, StructHdmiIrqStatus *pstTmdsMacIrqStatus)
{
#if(_CEC_RX_INT_SUPPORT == _ON)
    if(bEnable == _ENABLE)
    {
        ScalerSetBit(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6 | _BIT4), (pstTmdsMacIrqStatus->b1CecIrqBackup << 4));
    }
    else
    {
        pstTmdsMacIrqStatus->b1CecIrqBackup = (ScalerGetBit(P18_B0_CEC_RXCR0_1, _BIT4) >> 4);
        ScalerSetBit(P18_B0_CEC_RXCR0_1, ~(_BIT7 | _BIT6 | _BIT4), 0x00);
    }
#else
    // Checker usage
    bEnable = bEnable;
    *pstTmdsMacIrqStatus = *pstTmdsMacIrqStatus;
#endif
}
#endif
