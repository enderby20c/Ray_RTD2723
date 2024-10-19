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
// ID Code      : ScalerDpHdcp14Rx0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpHdcp14Rx0/ScalerDpHdcp14Rx0.h"

#if(_DP_HDCP14_RX0_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
volatile bit g_bDpHdcp14Rx0AksvWritten = 0;
volatile WORD g_usDpHdcp14Rx0KsvFifoOffset;
StructDPMacRxHDCPAuthInfo g_stDpHdcp14Rx0AuthInfo;
#endif
BYTE g_ucDpHdcp14Rx0Caps;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDCP 1.4 Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14Rx0ResetProc(void)
{
#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
    if(GET_DP_HDCP14_RX0_AUTH_STATE() != _DP_RX_HDCP_STATE_IDLE)
#endif
    {
        EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX0);

        // Reset HDCP Block
        ScalerDpMacDphyRxHdcp14ResetProc(enumInputPort);

        // DPCD [0x68029 ~ 0x6803A]
        ScalerDpAuxRx0DpcdGroupReset(0x06, 0x80, 0x29, 18);

        // DPCD [0x68014 ~ 0x68027]
        ScalerDpAuxRx0DpcdGroupReset(0x06, 0x80, 0x14, 20);

#if(_DP_TX_SUPPORT == _ON)
        CLR_DP_HDCP14_RX0_REPEATER_AUTH_1_START();
#if(_DP_MST_SUPPORT == _ON)
        ScalerDpHdcp14RxChangeAuthState(enumInputPort, _DP_RX_HDCP_STATE_IDLE);
#endif
#endif
    }
}

#if(_DP_HDCP14_RX0_REPEATER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx Hdcp 1.4 Auth Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14Rx0RepeaterHandler(void)
{
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX0);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    if((ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_14) &&
       (ScalerDpAuxRxGetHdcpRepeaterSupport(enumInputPort) == _TRUE))
#else
    if(ScalerDpAuxRxGetHdcpRepeaterSupport(enumInputPort) == _TRUE)
#endif
    {
        // After receiving AKSV, handler must initialize authentication
        if(GET_DP_HDCP14_RX0_AUTH_AKSV_WRITTEN() == _TRUE)
        {
            CLR_DP_HDCP14_RX0_AUTH_AKSV_WRITTEN();
            CLR_DP_HDCP14_RX0_AUTH_CPIRQ_TIMRE();
            SET_DP_HDCP14_RX0_REPEATER_AUTH_1_START();

            ScalerDpHdcp14Rx0ChangeAuthState(_DP_RX_HDCP_STATE_IDLE);

#if(_DP_HDCP2_RX0_REPEATER_SUPPORT == _ON)
            ScalerDpHdcp2Rx0ChangeAuthState(_DP_RX_HDCP2_REPEATER_STATE_IDLE);
#endif

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_CPIRQ_EVENT);
        }

        if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
        {
            // In MST mode
            if(ScalerDpMacDphyRxGetMstProtocolEnable(enumInputPort) == _ENABLE)
            {
                if((ScalerDpMacDphyRxHdcpCheckValid(enumInputPort) == _TRUE) && (GET_DP_HDCP14_RX0_AUTH_CPIRQ_TIMRE() == _FALSE))
                {
                    if(ScalerDpMacDphyRxHdcpCheckLvp(enumInputPort) == _FALSE)
                    {
                        SET_DP_HDCP14_RX0_AUTH_CPIRQ_TIMRE();

                        ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

                        ScalerTimerActiveTimerEvent(SEC(0.02), _SCALER_TIMER_EVENT_DP_RX0_HDCP_CPIRQ_EVENT);
                    }
                }
            }
        }

        if((GET_DP_HDCP14_RX0_AUTH_STATE() != _DP_RX_HDCP_STATE_IDLE) &&
           (ScalerDpAuxRxGetLTStatus(enumInputPort) == _DP_LINK_TRAINING_NONE))
        {
            ScalerDpHdcp14Rx0ChangeAuthState(_DP_RX_HDCP_STATE_IDLE);
        }
    }

    switch(GET_DP_HDCP14_RX0_AUTH_STATE())
    {
        case _DP_RX_HDCP_STATE_IDLE:

            if(GET_DP_HDCP14_RX0_AUTH_STATE_CHANGE() == _TRUE)
            {
                // Clear Backup Table of ECF
                memset(g_pucDpHdcpRx0ECFBackup, 0, sizeof(g_pucDpHdcpRx0ECFBackup));

                CLR_DP_HDCP14_RX0_AUTH_STATE_CHANGE();
                CLR_DP_HDCP14_RX0_AUTH_REPEATER_PROC_TIMEOUT();
                CLR_DP_HDCP14_RX0_AUTH_CPIRQ_TIMRE();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_REPEATER_PROC_TIMEOUT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_READ_IRQ_TIMEOUT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_CPIRQ_EVENT);

                ScalerDpHdcp14Rx0EnableReadIrq(_DISABLE);

                ScalerDpHdcp14TxResetKsvBackup();

                SET_DP_HDCP14_RX0_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION);
            }

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            if((ScalerDpHdcpRxGetHdcpMode(enumInputPort) == _HDCP_14) && (ScalerDpAuxRxGetHdcpRepeaterSupport(enumInputPort) == _TRUE))
#else
            if(ScalerDpAuxRxGetHdcpRepeaterSupport(enumInputPort) == _TRUE)
#endif
            {
                // Check if R0' was read already by upstream device.
                if(ScalerDpMacDphyRxHdcp14Auth1Check(enumInputPort) == _TRUE)
                {
                    if(GET_DP_HDCP14_RX0_REPEATER_AUTH_1_START() == _TRUE)
                    {
                        CLR_DP_HDCP14_RX0_REPEATER_AUTH_1_START();

                        ScalerDpHdcp14Rx0ChangeAuthState(_DP_RX_HDCP_STATE_AUTH_1);
                    }
                }
            }

            break;

        case _DP_RX_HDCP_STATE_AUTH_1:

            if(GET_DP_HDCP14_RX0_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_HDCP14_RX0_AUTH_STATE_CHANGE();

                if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
                {
                    // Check if downstream device support HDCP capability.
                    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                    {
                        // Issue event to make DPTX start HDCP handshake.
                        SET_DP_HDCP14_RX0_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX0_HDCP_REPEATER_PROC_TIMEOUT);
                    }
                    else
                    {
                        ScalerDpHdcp14Rx0ChangeAuthState(_DP_RX_HDCP_STATE_AUTH_2);
                    }
                }
                else
                {
                    ScalerDpHdcp14Rx0ChangeAuthState(_DP_RX_HDCP_STATE_AUTH_FAKE);
                }
            }

            // Wait for downstream pass event or device/depth max event
            if((GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX))
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_REPEATER_PROC_TIMEOUT);

                ScalerDpHdcp14Rx0ChangeAuthState(_DP_RX_HDCP_STATE_AUTH_2);
            }
            else if(GET_DP_HDCP14_RX0_AUTH_REPEATER_PROC_TIMEOUT() == _TRUE)
            {
                CLR_DP_HDCP14_RX0_AUTH_REPEATER_PROC_TIMEOUT();

                if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                {
                    SET_DP_HDCP14_RX0_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT);
                }

                ScalerDpHdcp14Rx0ChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP_STATE_AUTH_2:

            if(GET_DP_HDCP14_RX0_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_HDCP14_RX0_AUTH_STATE_CHANGE();
            }

            if(ScalerDpHdcp14Rx0CheckBinfo() == _TRUE)
            {
                // Load KSV List to RX KSV FIFO
                ScalerDpHdcp14Rx0LoadKsvFifo();

                // Input KSV FIFO to SHA-1 and Compute V'
                ScalerDpMacDphyRxHdcp14WriteShaInput(enumInputPort);

                // Write V' into DPCD table
                ScalerDpMacDphyRxHdcp14LoadShaToDpcd(enumInputPort);

                // Set 1st KSV FIFO to DPCD table
                ScalerDpHdcp14Rx0SetKsvFifoFirst();

                // Enable 68xxx Read INT
                ScalerDpHdcp14Rx0EnableReadIrq(_ENABLE);

                ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_DP_RX0_HDCP_READ_IRQ_TIMEOUT);
            }

            if(GET_DP_HDCP14_RX0_AUTH_AKSV_WRITTEN() == _FALSE)
            {
                // Set V' Ready Bit and Issue CP_IRQ
                ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP_BSTATUS_V_READY);
            }

            ScalerDpHdcp14Rx0ChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);

            break;

        case _DP_RX_HDCP_STATE_AUTH_FAKE:

            if(GET_DP_HDCP14_RX0_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_HDCP14_RX0_AUTH_STATE_CHANGE();
            }

            // Enable 68xxx Read INT
            ScalerDpHdcp14Rx0EnableReadIrq(_DISABLE);

            // Fake Authentication
            ScalerDpMacDphyRxHdcp14FakeAuthenProc(enumInputPort);

            // Set V' Ready Bit and Issue CP_IRQ
            ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP_BSTATUS_V_READY);

            ScalerDpHdcp14Rx0ChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);

            break;

        case _DP_RX_HDCP_STATE_AUTH_DONE:

            if(GET_DP_HDCP14_RX0_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_HDCP14_RX0_AUTH_STATE_CHANGE();
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS)
            {
                // In SST mode
                if((ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x00, 0x01, 0x11) & _BIT0) == 0x00)
                {
                    if((ScalerDpHdcp14Rx0DeviceCountChange() == _TRUE) &&
                       (ScalerDpMacDphyRxHdcpCheckValid(enumInputPort) == _TRUE) &&
                       (ScalerDpMacDphyRxHdcpCheckLvp(enumInputPort) == _TRUE))
                    {
                        // DpTx Device Count Changed (N --> N)
                        ScalerDpHdcp14Rx0ReAuthProcess(enumInputPort);
                    }
                }
            }

            if(GET_DP_HDCP14_RX0_AUTH_READ_IRQ_TIMEOUT() == _TRUE)
            {
                ScalerDpHdcp14Rx0EnableReadIrq(_DISABLE);
            }

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpHdcp14Rx0ChangeECFCheck();
#endif
            break;

        default:

            break;
    }
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check HDCP ECF Change
// Input Value  : Target HDCP Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14Rx0ChangeECFCheck(void)
{
    bit bECFChanged = _FALSE;
    BYTE ucDaisyStreamCnt = 0;
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX0);
    EnumDpHdcpUpstreamPort enumDpHdcpUpstreamPort = GET_DP_RX_HDCP_UPSTREAM_PORT();

    if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT) && (GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT))
    {
        for(ucDaisyStreamCnt = 0; ucDaisyStreamCnt < _HW_DP_MST_DAISY_ST_NUM_MAX; ucDaisyStreamCnt++)
        {
            BYTE ucHdcpTimeSlotEncValue = ScalerDpMacDphyRxHdcpTimeSlotEncValue(enumInputPort, (ScalerGetByte(ScalerDpMacDphyRxStreamStartAddress(enumDpHdcpUpstreamPort, ucDaisyStreamCnt)) & 0x3F));

            if(ucHdcpTimeSlotEncValue != g_pucDpHdcpRx0ECFBackup[ucDaisyStreamCnt])
            {
                g_pucDpHdcpRx0ECFBackup[ucDaisyStreamCnt] = ucHdcpTimeSlotEncValue;

                bECFChanged = _TRUE;
            }
        }
    }

    if(bECFChanged == _TRUE)
    {
        if((GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE) && (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST))
        {
            // Issue event to inform DPTX HDCP ECF Changed.
            SET_DP_HDCP14_RX0_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_ECF_CHANGE);
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Change HDCP Auth State
// Input Value  : Target HDCP Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14Rx0ChangeAuthState(EnumDPRxHDCPAuthState enumHDCPAuthState)
{
    SET_DP_HDCP14_RX0_AUTH_STATE(enumHDCPAuthState);
    SET_DP_HDCP14_RX0_AUTH_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Enable HDCP Read IRQ Function
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14Rx0EnableReadIrq(bit bEnable)
{
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX0);

    if(bEnable == _ENABLE)
    {
        if(ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A) > 3)
        {
            ScalerDpAuxRxHdcp14EnableReadIrq(_ENABLE, enumInputPort);
        }
    }
    else
    {
        ScalerDpAuxRxHdcp14EnableReadIrq(_DISABLE, enumInputPort);

        CLR_DP_HDCP14_RX0_AUTH_READ_IRQ_TIMEOUT();
    }
}

//--------------------------------------------------
// Description  : Check B info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpHdcp14Rx0CheckBinfo(void)
{
    BYTE ucBInfoDevice = 0;
    BYTE ucBInfoDepth = 0;
    bit bBInfoDeviceExceed = _FALSE;
    bit bBInfoDepthExceed = _FALSE;
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX0);

    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
        {
            if((GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_MAX() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() > _DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_EXCEED))
            {
                bBInfoDeviceExceed = _TRUE;
            }
            else
            {
                ucBInfoDevice = GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT();
            }

            if((GET_DP_TX_HDCP_DOWNSTREAM_DEPTH_MAX() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_DEPTH() > 6))
            {
                bBInfoDepthExceed = _TRUE;
            }
            else
            {
                ucBInfoDepth = GET_DP_TX_HDCP_DOWNSTREAM_DEPTH();
            }
        }

        if(bBInfoDeviceExceed == _FALSE)
        {
            ucBInfoDevice++;
        }
    }

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_INPUT_PORT() == enumInputPort))
    {
        if(bBInfoDeviceExceed == _FALSE)
        {
            ucBInfoDevice++;
        }
    }
#endif
#endif

    if(bBInfoDeviceExceed == _TRUE)
    {
        ucBInfoDevice = 0x80;
    }

    if(bBInfoDepthExceed == _FALSE)
    {
        ucBInfoDepth++;
    }
    else
    {
        ucBInfoDepth = 0x08;
    }

    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, 0x2A, ucBInfoDevice);
    ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, 0x2B, ucBInfoDepth);

    if((ucBInfoDevice == 0x80) || (ucBInfoDepth == 0x08))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14Rx0LoadKsvFifo(void)
{
    WORD usIndex = 0;
    WORD usKsvOffset = 0;

#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX0);
#endif

    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
        {
            usKsvOffset = (WORD) GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() * 5;
        }

        // Backup BKSV of Downstream Device
        memcpy(g_pucDpHdcp14TxKsvBackup, (volatile BYTE xdata *)PBB_4F_BKSV_0, 5);

        memcpy(&g_pucDpMacTxHdcpKsvFifo[usKsvOffset], (volatile BYTE xdata *)PBB_4F_BKSV_0, 5);
        usKsvOffset += 5;
    }

#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
#if(_DP_MST_PXP_MODE_SUPPORT == _ON)
    if((GET_DP_MST_RX_PXP_MODE_SUPPORT() == _ON) && (GET_DP_MST_RX_PXP_INPUT_PORT() == enumInputPort))
    {
        memcpy(&g_pucDpMacTxHdcpKsvFifo[usKsvOffset], g_pucSyncHdcpBksvBackup, 5);

        usKsvOffset += 5;
    }
#endif
#endif

    for(usIndex = usKsvOffset; usIndex < ((WORD) _DP_TX_HDCP14_DEVICE_COUNT_MAX * 5); usIndex++)
    {
        g_pucDpMacTxHdcpKsvFifo[usIndex] = 0x00;
    }
}

//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14Rx0SetKsvFifoFirst(void)
{
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX0);
    EnumDpAuxRxModeStatus enumDpAuxRxModeStatus = GET_DP_AUX_RX0_MODE();

    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetManualMode(enumInputPort);
    }

    for(g_usDpHdcp14Rx0KsvFifoOffset = 0; g_usDpHdcp14Rx0KsvFifoOffset < 15; g_usDpHdcp14Rx0KsvFifoOffset++)
    {
        if(GET_DP_TX_HDCP_KSV_FIFO_MAX() > g_usDpHdcp14Rx0KsvFifoOffset)
        {
            // DPCD [0x6802C ~ 0x6803A]
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, (0x2C + g_usDpHdcp14Rx0KsvFifoOffset), g_pucDpMacTxHdcpKsvFifo[g_usDpHdcp14Rx0KsvFifoOffset]);
        }
        else
        {
            // DPCD [0x6802C ~ 0x6803A]
            ScalerDpAuxRxSetDpcdValue(enumInputPort, 0x06, 0x80, (0x2C + g_usDpHdcp14Rx0KsvFifoOffset), 0x00);
        }
    }

    // Aux HW Control
    if(enumDpAuxRxModeStatus == _DP_RX_AUX_AUTO_MODE)
    {
        ScalerDpAuxRxSetAutoMode(enumInputPort);
    }
}

//--------------------------------------------------
// Description  : Check Downstream Device Count/Depth is changed or not
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpHdcp14Rx0DeviceCountChange(void)
{
    EnumInputPort enumInputPort = ScalerDpHdcpRxRxDxMapping(_RX0);
    BYTE ucBInfoDevice = 0;
    BYTE ucBInfoDepth = 0;
    bit bBInfoDeviceExceed = _FALSE;
    bit bBInfoDepthExceed = _FALSE;

    if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
    {
        if((GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_MAX() == _TRUE) ||
           (GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() > _DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT_EXCEED))
        {
            bBInfoDeviceExceed = _TRUE;
        }
        else
        {
            ucBInfoDevice = GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT();
        }

        if((GET_DP_TX_HDCP_DOWNSTREAM_DEPTH_MAX() == _TRUE) || (GET_DP_TX_HDCP_DOWNSTREAM_DEPTH() > 6))
        {
            bBInfoDepthExceed = _TRUE;
        }
        else
        {
            ucBInfoDepth = GET_DP_TX_HDCP_DOWNSTREAM_DEPTH();
        }
    }

    if(bBInfoDeviceExceed == _FALSE)
    {
        ucBInfoDevice++;
    }
    else
    {
        ucBInfoDevice = 0x80;
    }

    if(bBInfoDepthExceed == _FALSE)
    {
        ucBInfoDepth++;
    }
    else
    {
        ucBInfoDepth = 0x08;
    }

    if((ucBInfoDevice != ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2A)) ||
       (ucBInfoDepth != ScalerDpAuxRxGetDpcdInfo(enumInputPort, 0x06, 0x80, 0x2B)))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Change DP HDCP1.4 Repeater Capable for Rx0 Base On DPTX Clone Status
// Input Value  : InputPort, PortType, Clone Mode or not
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14Rx0RepeaterSupportProc(void)
{
    bit bDpRx0HdcpSetRepeater = _OFF;
    EnumInputPort enumHdcpInputPort = ScalerDpHdcpRxRxDxMapping(_RX0);

    if(GET_DP_HDCP14_RX0_CAPABLE_SUPPORT() == _FALSE)
    {
        return;
    }

    if(GET_DP_MAC_TX_DOWNSTREAM_DPPLUG_STATUS() != _DP_UNPLUG)
    {
        if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
        {
            bDpRx0HdcpSetRepeater = _ON;
        }
    }

    if(bDpRx0HdcpSetRepeater != GET_DP_HDCP14_RX0_REPEATER_SUPPORT())
    {
        DebugMessageHDCP2("[D0]Hdcp1.4 Repeater Bit Changed", bDpRx0HdcpSetRepeater);

        if(bDpRx0HdcpSetRepeater == _ON)
        {
            SET_DP_HDCP14_RX0_REPEATER_SUPPORT();
        }
        else
        {
            CLR_DP_HDCP14_RX0_REPEATER_SUPPORT();
        }

        switch(GET_DP_RX0_HOTPLUG_ASSERT_TYPE())
        {
            case _DP_HPD_NONE:
            case _DP_HPD_ASSERTED:

                if((ScalerDpHdcpRxGetHdcpMode(enumHdcpInputPort) == _HDCP_14) && (ScalerDpMacDphyRxHdcpCheckValid(enumHdcpInputPort) == _TRUE))
                {
                    if(ScalerDpRxGetHotPlugStatus(enumHdcpInputPort) == _HIGH)
                    {
                        // DpTx Sink Count 0 --> N or N --> 0
                        ScalerDpMacDphyRxCpIRQ(enumHdcpInputPort, _DP_HDCP_BSTATUS_REAUTH_REQ);

#if(_DP_LONG_HPD_AFTER_CPIRQ_SUPPORT == _ON)
                        if(ScalerDpMacDphyRxGetMstProtocolEnable(enumHdcpInputPort) == _DISABLE)
                        {
                            ScalerDpAuxRxReactiveHdcpLongHotplug(enumHdcpInputPort);
                        }
#endif
                    }
                }

                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : HDCP ReAuth Process
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDpHdcp14Rx0ReAuthProcess(EnumInputPort enumInputPort)
{
    ScalerDpMacDphyRxCpIRQ(enumInputPort, _DP_HDCP_BSTATUS_REAUTH_REQ);

    // In SST mode, issue Long HPD Event caused by Reauth Event issued after 1 sec.
    // In MST mode, notify source by CPIRQ only. Don't issue long HPD.
    if((ScalerDpAuxRxGetDpcdBitInfo(enumInputPort, 0x00, 0x01, 0x11, (_BIT1 | _BIT0)) == 0x00) &&
       (GET_DP_HDCP14_RX0_AUTH_STATE() != _DP_RX_HDCP_STATE_IDLE) &&
       (ScalerDpMacDphyRxHdcpCheckValid(enumInputPort) == _TRUE))
    {
        ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
    }
}
#endif
#endif
