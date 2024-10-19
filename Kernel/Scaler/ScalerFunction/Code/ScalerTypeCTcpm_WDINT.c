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
// ID Code      : ScalerTypeCTcpm_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeCTcpm/ScalerTypeCTcpm.h"


#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
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
// Description  : WD Timer Event Proc of TCPM
// Input Value  : enumTypeCPcbPort, enumTcpmWDEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmWDTimerEventProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCTcpmWDEventID enumTcpmWDEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex_WDINT(enumTypeCPcbPort);

    // Reactive WDINT for 1ms if Already Set FW Busy.
    if(ScalerGetBit_WDINT(PFA_11_TCPM_BUSY + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), _BIT5) == _BIT5)
    {
        // Set Macro to Inform Mainloop Not to Continually use IIC
        SET_TCPM_WD_EVENT_TRIGGERED(ucPortIndex);

        ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, 1, enumTcpmWDEventID);

        enumTcpmWDEventID = _SCALER_WD_TIMER_EVENT_TCPM_INVALID;
    }
    else
    {
        CLR_TCPM_WD_EVENT_TRIGGERED(ucPortIndex);

        // [FW Solution] Avoid HW Trigger Auto Read before FW Using I2C, This will Cause TCPM HW Reset and Trigger Auto Read Again.
#if(_HW_TCPM_0_SUPPORT == _ON)
        if((enumTypeCPcbPort == _HW_TCPM_0_0_MAPPING) || (enumTypeCPcbPort == _HW_TCPM_0_1_MAPPING))
        {
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
            // 1. Disable TCPM_0_0 Alert Det
            ScalerTypeCTcpmAlertDetCtrl_WDINT(ScalerTypeCTcpmGetPortIndex_WDINT(_HW_TCPM_0_0_MAPPING), _DISABLE);
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
            // 2. Disable TCPM_0_1 Alert Det
            ScalerTypeCTcpmAlertDetCtrl_WDINT(ScalerTypeCTcpmGetPortIndex_WDINT(_HW_TCPM_0_1_MAPPING), _DISABLE);
#endif

            // 3. Polling [0xFA11] [4] hw_i2c_busy = 0 Since HW Might Trigger before Disable Alert Det
            ScalerTimerPollingFlagProc_WDINT(2, PFA_11_TCPM_BUSY, _BIT4, _FALSE);

            // 4. Polling [0xFA12] [7] tcpm_irq = 0 to Avoid WDINT being Interrupted by EXINT
            ScalerTimerPollingFlagProc_WDINT(2, PFA_12_TCPM_RELATED_IRQ_1, _BIT7, _FALSE);
        }
#endif // End of #if(_HW_TCPM_0_SUPPORT == _ON)

#if(_HW_TCPM_1_SUPPORT == _ON)
        if((enumTypeCPcbPort == _HW_TCPM_1_0_MAPPING) || (enumTypeCPcbPort == _HW_TCPM_1_1_MAPPING))
        {
#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
            // 1. Disable TCPM_1_0 Alert Det
            ScalerTypeCTcpmAlertDetCtrl_WDINT(ScalerTypeCTcpmGetPortIndex_WDINT(_HW_TCPM_1_0_MAPPING), _DISABLE);
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
            // 2. Disable TCPM_1_1 Alert Det
            ScalerTypeCTcpmAlertDetCtrl_WDINT(ScalerTypeCTcpmGetPortIndex_WDINT(_HW_TCPM_1_1_MAPPING), _DISABLE);
#endif

            // 3. Polling [0xFB11] [4] hw_i2c_busy = 0 Since HW Might Trigger before Disable Alert Det
            ScalerTimerPollingFlagProc_WDINT(2, PFB_11_TCPM_BUSY, _BIT4, _FALSE);

            // 4. Polling [0xFB12] [7] tcpm_irq = 0 to Avoid WDINT being Interrupted by EXINT
            ScalerTimerPollingFlagProc_WDINT(2, PFB_12_TCPM_RELATED_IRQ, _BIT7, _FALSE);
        }
#endif // End of #if(_HW_TCPM_0_SUPPORT == _ON)
    }

    switch(enumTcpmWDEventID)
    {
        case _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE:

            if((GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_WAIT_SRC) || (GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_WAIT_SNK))
            {
                // Set tCcDebounce Done
                SET_TCPM_CC_TCCDEBOUNCE(ucPortIndex);

                // Enable Vbus_Alarm_H/L to Check Vsafe5V or Vsafe0V
                if(GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_WAIT_SRC)
                {
                    // 1. Set Vbus_Alarm_L Thr to Check Vsafe0V
                    CLR_TCPM_CC_SRC_DET_0V(ucPortIndex);
                    CLR_TCPM_CC_SRC_DET_5V(ucPortIndex);
                    ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_VOL_ALARM_L, GET_TCPCI_VOLTAGE_CODE(80));

                    // 2. Enable ALERT.VBUS_ALRM_L
                    ScalerTypeCTcpmAlertControl_WDINT(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_VBUS_ALRM_L, _ENABLE);
                }
                else if(GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_WAIT_SNK)
                {
                    // 1. Set Vbus_Alarm_H Thr to Check Vsafe5V
                    CLR_TCPM_CC_SNK_DET_5V(ucPortIndex);
                    ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_VOL_ALARM_H, GET_TCPCI_VOLTAGE_CODE(475));

                    // 2. Enable ALERT.VBUS_ALRM_H
                    ScalerTypeCTcpmAlertControl_WDINT(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_VBUS_ALRM_H, _ENABLE);
                }

                // 3. Enable Vbus Voltage Alarm Detection
                SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT5));
                ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE:

            if((GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_WAIT_SNK) || (GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_SNK))
            {
                if(GET_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex) == _TRUE)
                {
                    // Sink Unttach Debounce Timeout : Take Sink Unattach Proc and Re-Start Connection
                    ScalerTypeCTcpmCcUnattachSetting_WDINT(ucPortIndex);
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_CC_CHECK_VBUS_0V:

            if(ScalerTypeCTcpmGetVbusVoltage_WDINT(ucPortIndex) <= _TCPM_VSAFE0V_UP_BND)
            {
                ScalerTypeCTcpmVbusDischargeCtrl_WDINT(ucPortIndex, _OFF);
            }
            else
            {
                ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, _UNATTACH_VBUS_DISCHARGE_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CC_CHECK_VBUS_0V);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_HARDRESET)
            {
                ScalerTypeCTcpmPdWDTimerEventCableProc_WDINT(ucPortIndex);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_SEND_SRC_CAP:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_HARDRESET)
            {
                // Send SRC_CAP
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_INT_SEND_CAP);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);

                ScalerTypeCTcpmPdSendMsg_WDINT(ucPortIndex, _PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_SEND_REQUEST:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_HARDRESET)
            {
                // Send REQUEST
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_INT_SEND_REQUEST);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_WDINT(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REQUEST, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST:
        case _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_SNK_INT_WAIT_SRC_CAP)
            {
                if(GET_TCPM_WD_TIME_LEFT(ucPortIndex) != 0)
                {
                    ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, ScalerTypeCTcpmWDTimeCtrl_WDINT(ucPortIndex, GET_TCPM_WD_TIME_LEFT(ucPortIndex)), _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST);
                }
                else
                {
                    // Send Hard Reset
                    ScalerTypeCTcpmPdSendHardRst_WDINT(ucPortIndex);
                }
            }
            else
            {
                // Send Hard Reset
                ScalerTypeCTcpmPdSendHardRst_WDINT(ucPortIndex);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_PS_TRANSITION_TIMEOUT:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_HARDRESET)
            {
                if(GET_TCPM_WD_TIME_LEFT(ucPortIndex) != 0)
                {
                    ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, ScalerTypeCTcpmWDTimeCtrl_WDINT(ucPortIndex, GET_TCPM_WD_TIME_LEFT(ucPortIndex)), _SCALER_WD_TIMER_EVENT_TCPM_PS_TRANSITION_TIMEOUT);
                }
                else
                {
                    // Send Hard Reset
                    ScalerTypeCTcpmPdSendHardRst_WDINT(ucPortIndex);
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_HARDRESET)
            {
                switch(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex))
                {
                    case _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP:

                        ADD_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex);
                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_ID);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP:

                        ADD_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex);
                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_SVID);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DISCOVER_MODE_RESP:

                        ADD_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex);
                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_MODE);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP:

                        ADD_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex);
                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP:

                        ADD_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex);
                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DP_STATUS_RESP:

                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_ATTENTION);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP:

                        ADD_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex);
                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);

                        break;

                    case _PD_ALT_MODE_READY:

                        if(GET_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex) == _TRUE)
                        {
                            CLR_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex);

                            // Push HPD_IRQ into HPD Queue When not Received DP Status ACK during Force Sending HPD IRQ Process, then PD will Re-Send HPD_IRQ in Main loop
                            ScalerTypeCTcpmPdPushHpd_WDINT(ucPortIndex, _PD_HPD_IRQ, 0);
                        }

                        break;

                    default:

                        break;
                }

                SET_TCPM_PD_VDMMSG_WAIT_FLAG(ucPortIndex);

                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_HARDRESET)
            {
                // Control PMIC to Turn On Vbus Power
                // ScalerTypeC0PmicSetting_WDINT(_ON, _PD_POWER_SRC, GET_TCPM_PD_SRC_PDO_TYPE(GET_TCPM_PD_PARTNER_OBJ_POS() - 1), GET_TCPM_PD_PARTNER_REQ_VOL(), GET_TCPM_OCP_CURRENT(), GET_TCPM_PD_SRC_CAP_PEAK(GET_TCPM_PD_PARTNER_OBJ_POS() - 1));
                ScalerTypeCTcpmVbusCtrl_WDINT(ucPortIndex, _ON, _PD_POWER_SRC, GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1), GET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex), GET_TCPM_OCP_CURRENT(ucPortIndex), GET_TCPM_PD_SRC_CAP_PEAK(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1));

                // Update PDO Status
                SET_TCPM_PD_PDO_STATUS_VOL(ucPortIndex, GET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex));
                SET_TCPM_PD_PDO_STATUS_CUR(ucPortIndex, GET_TCPM_PD_PARTNER_MAX_CUR(ucPortIndex));
                SET_TCPM_PD_PDO_STATUS_OBJ_POS(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex));

                // State Transition
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_WDINT_SEND_PSRDY);

                // Active WD Timer to Check Vbus if Vbus Ready
                if(GET_TCPM_PD_REQ_PPS_VOL_SMALL_STEP(ucPortIndex) != _TRUE)
                {
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _SRC_SEND_PS_RDY_FIX_VOLTAGE_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
                }
                else
                {
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _SRC_SEND_PS_RDY_PPS_MODE_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER:

            // From : 1.SRC Rcv Accpet PRS 2.SRC Send Accept PRS 3.HRST_EXINT 4.HRST_WDINT
            if((GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_SRC_OFF_PSRDY) || (GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_HARDRESET))
            {
                // From : (A)Source Rcv/Send Hard Reset, (B)Source Rcv/Send PRS Accept
                // 1. Turn Off Source Vbus
                ScalerTypeCTcpmVbusCtrl_WDINT(ucPortIndex, _OFF, _PD_POWER_SRC, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

                // 2. Turn On Vbus Discharge
                ScalerTypeCTcpmVbusDischargeCtrl_WDINT(ucPortIndex, _ON);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_WDINT_SEND_CBL_DISCOVER_ID)
            {
                ADD_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex);

                if((ScalerTypeCTcpmCheckVbusReady_WDINT(ucPortIndex, 500) == _TRUE) || (GET_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex) >= 8))
                {
                    // Reset Check Vbus Counter
                    CLR_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex);

                    // Send Discover_ID_REQ When Vbus Check Pass.
                    ScalerTypeCTcpmPdWDTimerEventCableProc_WDINT(ucPortIndex);
                }
                else
                {
                    // Active WD Timer to Check Vbus
                    ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, 10, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
                }
            }
            else if(GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_SRC_WDINT_SEND_CAP)
            {
                ADD_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex);

                if((ScalerTypeCTcpmCheckVbusReady_WDINT(ucPortIndex, 500) == _TRUE) || (GET_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex) >= 8))
                {
                    // Reset Check Vbus Counter
                    CLR_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex);

                    // Start PMIC Protection
                    ScalerTypeCTcpmVbusProtectStart_WDINT(ucPortIndex, _TYPE_C_POWER_SRC);

                    // Send SRC_CAP
                    SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_INT_SEND_CAP);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);
                    ScalerTypeCTcpmPdSendMsg_WDINT(ucPortIndex, _PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Active WD Timer to Check Vbus
                    ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, 30, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
                }
            }
            else if(GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_SRC_WDINT_SEND_PSRDY)
            {
                ADD_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex);

                if((ScalerTypeCTcpmCheckVbusReady_WDINT(ucPortIndex, GET_TCPM_PD_PDO_STATUS_VOL(ucPortIndex)) == _TRUE) || (GET_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex) >= 8))
                {
                    // Reset Check Vbus Counter
                    CLR_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex);

                    // Send "PS_RDY" After Accept to Request and Ready to Provide New Negotiated Power Level
                    SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_INT_SEND_PSRDY);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_HARD_RESET);
                    ScalerTypeCTcpmPdSendMsg_WDINT(ucPortIndex, _PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    if(GET_TCPM_PD_REQ_PPS_VOL_SMALL_STEP(ucPortIndex) != _TRUE)
                    {
                        ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, _SRC_SEND_PS_RDY_FIX_VOLTAGE_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
                    }
                    else
                    {
                        ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, _SRC_SEND_PS_RDY_PPS_MODE_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
                    }
                }
            }
            else if((GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_SNK_READY) && (GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_WDINT_SEND_SRC_ON_PSRDY))
            {
                ADD_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex);

                if((ScalerTypeCTcpmCheckVbusReady_WDINT(ucPortIndex, 500) == _TRUE) || (GET_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex) >= 8))
                {
                    // Reset Check Vbus Counter
                    CLR_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex);

                    // Start PMIC Protection
                    ScalerTypeCTcpmVbusProtectStart_WDINT(ucPortIndex, _TYPE_C_POWER_SRC);

                    // PD 2.0 : Only Source && Vconn Source Can Communicate With Cable When Implicit Contract
                    if((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) && (GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC))
                    {
                        // Enable PD Rcv Detect ([0x2F] : [5] HRST, [2] SOP", [1] SOP', [0] SOP)
                        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, (_TCPM_TCPCI_RCV_DET_SOP | _TCPM_TCPCI_RCV_DET_SOP_P | _TCPM_TCPCI_RCV_DET_SOP_PP | _TCPM_TCPCI_RCV_DET_HRST));
                    }

                    // Change PD Power Role to Source
                    SET_TCPM_POWER_ROLE(ucPortIndex, _PD_POWER_SRC);

                    // Set Message Header for GoodCRC Reply
                    ScalerTypeCTcpmPdUpdateGoodCRCInfo_WDINT(ucPortIndex);

                    // Send "PS_RDY" After PRS to SRC and Vbus Has Been Turned On
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_HARD_RESET);
                    ScalerTypeCTcpmPdSendMsg_WDINT(ucPortIndex, _PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, 35, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_HARDRESET)
            {
                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                if(GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_INT_WAIT_VCS_RESP)
                {
                    SET_TCPM_PD_VCS_REJECT(ucPortIndex);
                }
                else if(GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_INT_WAIT_DRS_RESP)
                {
                    SET_TCPM_PD_DRS_REJECT(ucPortIndex);
                }
                else if(GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_INT_WAIT_PRS_RESP)
                {
                    SET_TCPM_PD_PRS_REJECT(ucPortIndex);
                }

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_SNK_SWITCH_TO_SRC:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_HARDRESET)
            {
                // 1. Change Rd -> Rp (Switch to Power SRC)
                ScalerTypeCTcpmSwitchPowerRole_WDINT(ucPortIndex, _PD_POWER_SRC);

                // 2. Set OCP Threshlod
                SET_TCPM_OCP_CURRENT(ucPortIndex, (WORD)(((DWORD)(GET_TCPM_CC_DEF_CUR(ucPortIndex)) * (DWORD)(GET_TCPM_OCP_RATIO(ucPortIndex, 0))) / 100));

                // 3. Turn On Vbus to vSafe5V (500 * 10mV) / Current = Default Current (10mA)
                ScalerTypeCTcpmVbusCtrl_WDINT(ucPortIndex, _ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, 500, GET_TCPM_OCP_CURRENT(ucPortIndex), _PD_PEAK_CUR_NONE);

                // 4. Check Vbus 35ms (10ms + 25ms) after Received PS_RDY, Then Start PMIC Protection and Send "PS_RDY" if VbusSafe5V
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_WDINT_SEND_SRC_ON_PSRDY);

                ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, 25, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_TCPM_SEND_VCONN_ON_PSRDY:

            if(GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_HARDRESET)
            {
                // Set Vconn Role to Vconn SRC
                SET_TCPM_VCONN_ROLE(ucPortIndex, _PD_VCONN_SRC);

                // Reset Discover ID Retry Fail Counter After Vconn_Swap
                CLR_TCPM_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT(ucPortIndex);

                // PD 2.0 : Only DFP && Vconn Source Can Communicate With Cable During Explicit Contract
                // PD 3.0 : Only Vconn Source Can Communicate With Cable
                if((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0) || ((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) && (GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)))
                {
                    // Enable PD Rcv Detect ([0x2F] : [5] HRST, [2] SOP", [1] SOP', [0] SOP)
                    ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, (_TCPM_TCPCI_RCV_DET_SOP | _TCPM_TCPCI_RCV_DET_SOP_P | _TCPM_TCPCI_RCV_DET_SOP_PP | _TCPM_TCPCI_RCV_DET_HRST));
                }

                // Send "PS_RDY"
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_HARD_RESET);
                ScalerTypeCTcpmPdSendMsg_WDINT(ucPortIndex, _PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);
            }

            break;

        default:

            break;
    }

    // Reactive WD Timer Event if Needed
    if(GET_TCPM_PD_WD_TIMER_EVENT_VALID(ucPortIndex) == _TRUE)
    {
        *pucActiveWDID = GET_TCPM_PD_WD_TIMER_EVENT_ID(ucPortIndex);
        *pucActiveWDTime = GET_TCPM_PD_WD_TIMER_EVENT_CNT(ucPortIndex);
        CLR_TCPM_PD_WD_TIMER_EVENT_VALID(ucPortIndex);
    }

    // [FW Solution] Avoid HW Trigger Auto Read before FW Using I2C, This will Cause TCPM HW Reset and Trigger Auto Read Again.
#if(_HW_TCPM_0_SUPPORT == _ON)
    if((enumTypeCPcbPort == _HW_TCPM_0_0_MAPPING) || (enumTypeCPcbPort == _HW_TCPM_0_1_MAPPING))
    {
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 1. Enable TCPM_0_0 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_WDINT(ScalerTypeCTcpmGetPortIndex_WDINT(_HW_TCPM_0_0_MAPPING), _ENABLE);
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 2. Enable TCPM_0_1 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_WDINT(ScalerTypeCTcpmGetPortIndex_WDINT(_HW_TCPM_0_1_MAPPING), _ENABLE);
#endif
    }
#endif // End of #if(_HW_TCPM_0_SUPPORT == _ON)

#if(_HW_TCPM_1_SUPPORT == _ON)
    if((enumTypeCPcbPort == _HW_TCPM_1_0_MAPPING) || (enumTypeCPcbPort == _HW_TCPM_1_1_MAPPING))
    {
#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 1. Enable TCPM_1_0 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_WDINT(ScalerTypeCTcpmGetPortIndex_WDINT(_HW_TCPM_1_0_MAPPING), _ENABLE);
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 2. Enable TCPM_1_1 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_WDINT(ScalerTypeCTcpmGetPortIndex_WDINT(_HW_TCPM_1_1_MAPPING), _ENABLE);
#endif
    }
#endif // End of #if(_HW_TCPM_0_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Get TCPM Port Index
// Input Value  : enumTypeCPcbPort
// Output Value : Type C TCPM Port Index
//--------------------------------------------------
BYTE ScalerTypeCTcpmGetPortIndex_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPortIndex = 0;
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _TCPM_PORT_VALID; ucIndex++)
    {
        if(g_penumTypeCTcpmPort[ucIndex] == enumTypeCPcbPort)
        {
            ucPortIndex = ucIndex;

            break;
        }
    }

    return ucPortIndex;
}

//--------------------------------------------------
// Description  : Convert Tcpm Event ID to Event ID
// Input Value  : ucPortIndex, enumTcpmEventID
// Output Value : enumEventID
//--------------------------------------------------
EnumScalerTimerEventID ScalerTypeCTcpmEventIDMapping_WDINT(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID)
{
    EnumScalerTimerEventID enumEventID = _SCALER_TIMER_EVENT_INVALID;

#if(_HW_TCPM_SUPPORT == _ON)
    switch(g_penumTypeCTcpmPort[ucPortIndex])
    {
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_0_MAPPING:

            enumEventID = (EnumScalerTimerEventID)(enumTcpmEventID + _SCALER_TIMER_EVENT_TCPM_0_0_SNK_HARD_RST_TIMEOUT);

            break;
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_1_MAPPING:

            enumEventID = (EnumScalerTimerEventID)(enumTcpmEventID + _SCALER_TIMER_EVENT_TCPM_0_1_SNK_HARD_RST_TIMEOUT);

            break;
#endif

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_0_MAPPING:

            enumEventID = (EnumScalerTimerEventID)(enumTcpmEventID + _SCALER_TIMER_EVENT_TCPM_1_0_SNK_HARD_RST_TIMEOUT);

            break;
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_1_MAPPING:

            enumEventID = (EnumScalerTimerEventID)(enumTcpmEventID + _SCALER_TIMER_EVENT_TCPM_1_1_SNK_HARD_RST_TIMEOUT);

            break;
#endif
        default:

            break;
    }
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    enumTcpmEventID = enumTcpmEventID;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

    return enumEventID;
}

//--------------------------------------------------
// Description  : Convert Tcpm WD Event ID to WD Event ID
// Input Value  : ucPortIndex, enumTcpmWDEventID
// Output Value : enumWDEventID
//--------------------------------------------------
EnumScalerWDTimerEventID ScalerTypeCTcpmWDEventIDMapping_WDINT(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID)
{
    EnumScalerWDTimerEventID enumWDEventID = _SCALER_WD_TIMER_EVENT_INVALID;

#if(_HW_TCPM_SUPPORT == _ON)
    switch(g_penumTypeCTcpmPort[ucPortIndex])
    {
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_0_MAPPING:

            enumWDEventID = (EnumScalerWDTimerEventID)(enumTcpmWDEventID + _SCALER_WD_TIMER_EVENT_TCPM_0_0_CC_DEBOUNCE);

            break;
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_0_1_MAPPING:

            enumWDEventID = (EnumScalerWDTimerEventID)(enumTcpmWDEventID + _SCALER_WD_TIMER_EVENT_TCPM_0_1_CC_DEBOUNCE);

            break;
#endif

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_0_MAPPING:

            enumWDEventID = (EnumScalerWDTimerEventID)(enumTcpmWDEventID + _SCALER_WD_TIMER_EVENT_TCPM_1_0_CC_DEBOUNCE);

            break;
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        case _HW_TCPM_1_1_MAPPING:

            enumWDEventID = (EnumScalerWDTimerEventID)(enumTcpmWDEventID + _SCALER_WD_TIMER_EVENT_TCPM_1_1_CC_DEBOUNCE);

            break;
#endif
        default:

            break;
    }
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    enumTcpmWDEventID = enumTcpmWDEventID;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

    return enumWDEventID;
}

//--------------------------------------------------
// Description  : Active Tcpm Timer Event
// Input Value  : ucPortIndex, usTime,  enumTcpmEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmActiveTimerEvent_WDINT(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmEventID enumTcpmEventID)
{
    SET_TCPM_PD_TIMER_EVENT_ID(ucPortIndex, enumTcpmEventID);
    SET_TCPM_PD_TIMER_EVENT_CNT(ucPortIndex, usTime);
    SET_TCPM_PD_TIMER_EVENT_VALID(ucPortIndex);
}

//--------------------------------------------------
// Description  : Cancel Tcpm Timer Event
// Input Value  : ucPortIndex, enumTcpmEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCancelTimerEvent_WDINT(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID)
{
    ScalerTimerCancelTimerEvent_WDINT(ScalerTypeCTcpmEventIDMapping_WDINT(ucPortIndex, enumTcpmEventID));

    if((GET_TCPM_PD_TIMER_EVENT_ID(ucPortIndex) == enumTcpmEventID) && (GET_TCPM_PD_TIMER_EVENT_VALID(ucPortIndex) == _TRUE))
    {
        CLR_TCPM_PD_TIMER_EVENT_VALID(ucPortIndex);
    }
}

//--------------------------------------------------
// Description  : Active Tcpm WD Timer Event
// Input Value  : ucPortIndex, usTime,  enumTcpmEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmWDActiveTimerEvent_WDINT(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmWDEventID enumTcpmWDEventID)
{
    SET_TCPM_PD_WD_TIMER_EVENT_ID(ucPortIndex, ScalerTypeCTcpmWDEventIDMapping_WDINT(ucPortIndex, enumTcpmWDEventID));
    SET_TCPM_PD_WD_TIMER_EVENT_CNT(ucPortIndex, usTime);
    SET_TCPM_PD_WD_TIMER_EVENT_VALID(ucPortIndex);
}

//--------------------------------------------------
// Description  : Cancel Tcpm WD Timer Event
// Input Value  : ucPortIndex, enumTcpmWDEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmWDCancelTimerEvent_WDINT(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID)
{
    ScalerTimerWDCancelTimerEvent_WDINT(ScalerTypeCTcpmWDEventIDMapping_WDINT(ucPortIndex, enumTcpmWDEventID));
}

//--------------------------------------------------
// Description  : Control Tcpm WD Time Not Exceed Max Time
// Input Value  : ucPortIndex, enumTcpmWDEventID
// Output Value : enumWDEventID
//--------------------------------------------------
WORD ScalerTypeCTcpmWDTimeCtrl_WDINT(BYTE ucPortIndex, WORD usWDTime)
{
    if(usWDTime > _MAX_WD_EVENT_TIME)
    {
        SET_TCPM_WD_TIME_LEFT(ucPortIndex, (usWDTime - _MAX_WD_EVENT_TIME));

        return _MAX_WD_EVENT_TIME;
    }
    else
    {
        SET_TCPM_WD_TIME_LEFT(ucPortIndex, 0);

        return usWDTime;
    }
}


//--------------------------------------------------
// Description  : Type C TCPM Control Vbus
// Input Value  : ucPortIndex, bAction, bPowerDirection, enumPdoType, usVoltage(Unit = 10mV), usCurrent(Unit = 10mA), enumPeakCurrent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVbusCtrl_WDINT(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent)
{
#if(_TYPE_C_PMIC_SUPPORT == _ON)
    if(GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON)
    {
        ScalerTypeCTcpmPmicSetting_WDINT(ucPortIndex, bAction, bPowerDirection, enumPdoType, usVoltage, usCurrent, enumPeakCurrent);
    }
    else
#endif
    {
        if(bAction == _ON)
        {
            if(bPowerDirection == _PD_POWER_SRC)
            {
                if(usVoltage == 500)
                {
                    // Enable Sourcing Vbus 5V : COMMAND [0x23] : 0x77 (Enable Src 5V)
                    ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_EN_SRC_5V);

                    // ONSEMI_GPIO_1_CFG [0xA4] : [2] GPO_VAL : 0, [0] Output En = 1
                    // ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_A4, 0x01);

                    SET_TCPM_SRC_VBUS(ucPortIndex);
                }
                else
                {
                    // [TO-DO] Dennis : Vbus Nondefault Flow
                }
            }
            else if(bPowerDirection == _PD_POWER_SNK)
            {
                // Enable Sinking Vbus : COMMAND [0x23] : 0x55 (Enable Snk Vbus)
                ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_EN_SNK_VBUS);

                // ONSEMI_GPIO_1_CFG [0xA4] : [2] GPO_VAL : 0, [0] Output En = 1
                // ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_A4, 0x01);

                SET_TCPM_SNK_VBUS(ucPortIndex);
            }
        }
        else
        {
            // Disable Sourcing Vbus : COMMAND [0x23] : 0x66 (Disable Src 5V)
            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_DIS_SRC_VBUS);

            // Disable Sinking Vbus : COMMAND [0x23] : 0x44 (Disable Snk Vbus)
            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_DIS_SNK_VBUS);

            // ONSEMI_GPIO_1_CFG [0xA4] : [2] GPO_VAL : 1, [0] Output En = 1
            // ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_A4, 0x05);

            CLR_TCPM_SRC_VBUS(ucPortIndex);
            CLR_TCPM_SNK_VBUS(ucPortIndex);
        }
    }

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    // ========================================================
    // OCP by TCPC Flow
    // ========================================================
    if(GET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex) == _ON)
    {
        // Clear Fault Status (Vbus OCP) (0x1F[3])
        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VBUS_OCP);

        // Disable Fault Status (Vbus OCP) Mask (0x15[3])
        SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) & (~(_TCPM_TCPCI_FT_STAT_VBUS_OCP)));
        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
    }
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    // ========================================================
    // OVP/UVP Setting Flow
    // ========================================================
    if(GET_TCPM_OVP_UVP_SUPPORT(ucPortIndex) == _ON)
    {
        // Caculate OVP & UVP threshold
        if(bAction == _ON)
        {
            WORD usOVPThreshold = 0x0000;
            WORD usUVPThreshold = 0x0000;

            // Set Threshold for OVP (Unit = 10mV)
            usOVPThreshold = ((WORD)((((DWORD)usVoltage) * GET_TCPM_OVP_THRESHOLD(ucPortIndex)) / 100));

            SET_TCPM_OVP_VOLTAGE(ucPortIndex, usOVPThreshold);

            // Set Threshold for UVP (Unit = 10mV)
            if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
            {
                usUVPThreshold = ((WORD)_TCPM_UVP_PPS_THRESHOLD);
            }
            else
            {
                usUVPThreshold = ((WORD)((((DWORD)usVoltage) * GET_TCPM_UVP_THRESHOLD(ucPortIndex)) / 100));
            }

            SET_TCPM_UVP_VOLTAGE(ucPortIndex, usUVPThreshold);

            // Cancel Timer Event & Macro to Stop OVP / UVP Protect
            ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
            CLR_TCPM_OVP_UVP_CHECK(ucPortIndex);
        }
        else
        {
            // Cancel Timer Event & Macro to Stop OVP / UVP Protect
            ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
            CLR_TCPM_OVP_UVP_CHECK(ucPortIndex);
        }
    }
#endif // End of #if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)

    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC) && (usVoltage > 500))
    {
        // Tool Show Warning UI when We Provide Vbus > 5V
        ScalerTypeCTcpmToolWarningUIControl_WDINT(_ENABLE);
    }
    else
    {
        // Tool Not Show Warning UI when We Provide Vbus <= 5V
        ScalerTypeCTcpmToolWarningUIControl_WDINT(_DISABLE);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Detect Vbus On/Off to transit State
// Input Value  : ucPortIndex, bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVbusDetCtrl_WDINT(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ENABLE)
    {
        // Enable TCPC Auto Discharge Disconnect (POWER_CONTROL [0x1C] [4] Auto Discharge Disconnect)
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT4));
        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
    else
    {
        // Disable TCPC Auto Discharge Disconnect (POWER_CONTROL [0x1C] [4] Auto Discharge Disconnect)
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT4));
        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Discharge Vbus
// Input Value  : ucPortIndex, bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVbusDischargeCtrl_WDINT(BYTE ucPortIndex, bit bAction)
{
#if(_TYPE_C_PMIC_SUPPORT == _ON)
    if(GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON)
    {
        ScalerTypeCTcpmPmicVbusDischarge_WDINT(ucPortIndex, bAction);
    }
    else
#endif
    {
        if(bAction == _ON)
        {
            // Enable TCPC Force Discharge (POWER_CONTROL [0x1C] [2] Force Discharge)
            SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT2));
            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
        }
        else
        {
            // Disable TCPC Force Discharge (POWER_CONTROL [0x1C] [2] Force Discharge)
            SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT2));
            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
        }
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Vbus Protection Start
// Input Value  : ucPortIndex, enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVbusProtectStart_WDINT(BYTE ucPortIndex, EnumTypeCPowerRole enumPowerRole)
{
    ucPortIndex = ucPortIndex;
    enumPowerRole = enumPowerRole;

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    // ========================================================
    // OCP by TCPC Flow
    // ========================================================
    if((enumPowerRole == _TYPE_C_POWER_SRC) && (GET_TCPM_OCP_PROTECT_BY_TCPC(ucPortIndex) == _ON))
    {
        // Clear Fault Status (Vbus OCP) (0x1F[3])
        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VBUS_OCP);

        // Enable Fault Status (Vbus OCP) Mask (0x15[3])
        SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) | (_TCPM_TCPCI_FT_STAT_VBUS_OCP));
        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
    }
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    // ========================================================
    // OVP/UVP Flow
    // ========================================================
    if(GET_TCPM_OVP_UVP_SUPPORT(ucPortIndex) == _ON)
    {
        // Active Timer Event to Detect OVP/UVP
        ScalerTypeCTcpmActiveTimerEvent_WDINT(ucPortIndex, 40, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
        SET_TCPM_OVP_UVP_CHECK(ucPortIndex);
    }
#endif

#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
    // ========================================================
    // 1. OCP by Polling PMIC's ADC Flow   2. PMIC Debug Flow in PPS Mode
    // ========================================================
    if((GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON) && (GET_TCPM_PMIC_CHECK_SUPPORT(ucPortIndex) == _ON))
    {
        // Check if Any PMIC Protection Timer Needs to be Actived
        if(GET_TCPM_PMIC_PROTECT_TIMER_CHECK(ucPortIndex) == _TRUE)
        {
            CLR_TCPM_PMIC_PROTECT_TIMER_CHECK(ucPortIndex);

            // Set PMIC Protection Timer Start Flag to Active PMIC Protection Tracking Timer in Main Loop
            SET_TCPM_PMIC_PROTECT_TIMER_START(ucPortIndex);
        }

        SET_TCPM_PMIC_PROTECT_VALID(ucPortIndex);
    }
#endif
}

//--------------------------------------------------
// Description  : Type C TCPM Control Vbus
// Input Value  : ucPortIndex, usVoltage (Unit = 10mV)
// Output Value : None
//--------------------------------------------------
BYTE ScalerTypeCTcpmCheckVbusReady_WDINT(BYTE ucPortIndex, WORD usVoltage)
{
    WORD usTcpcVbus = ScalerTypeCTcpmGetVbusVoltage_WDINT(ucPortIndex);

    if(usVoltage == 500)
    {
        // Check Vbus = vSafe5V
        if((usTcpcVbus >= _TCPM_VSAFE5V_LOW_BND) && (usTcpcVbus <= _TCPM_VSAFE5V_UP_BND))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else if(usVoltage == 0)
    {
        // Check Vbus = vSafe0V
        if(usTcpcVbus <= _TCPM_VSAFE0V_UP_BND)
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        // Check Other Voltage Reange (0.95 ~ 1.05 vSrcNew)
        if((usTcpcVbus >= ((WORD)((DWORD)usVoltage * 95 / 100 / 10))) && (usTcpcVbus <= ((WORD)((DWORD)usVoltage * 105 / 100 / 10))))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Type C TCPM Get Vbus Voltage
// Input Value  : ucPortIndex
// Output Value : Vbus Voltage (Unit = 100mV)
//--------------------------------------------------
WORD ScalerTypeCTcpmGetVbusVoltage_WDINT(BYTE ucPortIndex)
{
    WORD usVbusVoltage = 0x00;
    WORD usTcpcRegValue = 0x00;
    BYTE ucFactor = 0x00;

    // Read TCPC VBUS_VOLTAGE [0x70~71]
    usTcpcRegValue = ScalerTypeCTcpmTcpciGetWord_WDINT(ucPortIndex, _TCPM_TCPCI_REG_VBUS_VOL);

    // 0x70[3:2] = Scaler Factor (00 : Not Scaled, 01 : Vbus Measure Divided by 2,  10 : Vbus Measure Divided by 4)
    if((usTcpcRegValue & (_BIT11 | _BIT10)) == (_BIT10))
    {
        ucFactor = 0x01;
    }
    else if((usTcpcRegValue & (_BIT11 | _BIT10)) == (_BIT11))
    {
        ucFactor = 0x02;
    }

    // {0x70[1:0],0x71[7:0]} = Vbus Voltage (Unit = 25mV)
    usVbusVoltage = ((usTcpcRegValue & 0x3FF) << ucFactor);

    // Convert Vbus Voltage (Unit = 25mV) to 100mV
    usVbusVoltage = (usVbusVoltage >> 2);

    return usVbusVoltage;
}

//--------------------------------------------------
// Description  : Type C TCPM Control Vconn
// Input Value  : ucPortIndex, bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVconnCtrl_WDINT(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ON)
    {
        if(GET_TCPM_DEVICE_VCONN_OCP_CAP(ucPortIndex) == _TRUE)
        {
            // Clear Fault Status (Vconn OCP) (0x1F[1])
            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VCONN_OCP);

            // Enable Fault Status (Vconn OCP) Mask (0x15[1])
            SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) | (_TCPM_TCPCI_FT_STAT_VCONN_OCP));
            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
        }

        // Turn On Vconn
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT0));
        SET_TCPM_SRC_VCONN(ucPortIndex);
        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
    else
    {
        if(GET_TCPM_DEVICE_VCONN_OCP_CAP(ucPortIndex) == _TRUE)
        {
            // Clear Fault Status (Vconn OCP) (0x1F[1])
            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VCONN_OCP);

            // Disable Fault Status (Vconn OCP) Mask (0x15[1])
            SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) & (~(_TCPM_TCPCI_FT_STAT_VCONN_OCP)));
            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
        }

        // Turn Off Vconn
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT0));
        CLR_TCPM_SRC_VCONN(ucPortIndex);
        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Control TCPC Alert and Alert Mask
// Input Value  : ucPortIndex, AlertType, Action (_ENABLE / _DISABLE)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmAlertControl_WDINT(BYTE ucPortIndex, WORD usAlertType, bit bAction)
{
    WORD usTargetAlertMask = 0x00;

#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_ALERT_UPDATE == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _ENABLE) == _FAIL)
    {
        return;
    }

    // 2. Update Clear Alert Reg
    ScalerSetByte_WDINT(PFA_28_TCPC_0_CLR_ALERT_L + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usAlertType));
    ScalerSetByte_WDINT(PFA_29_TCPC_0_CLR_ALERT_H + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usAlertType >> 8));

    if(bAction == _ENABLE)
    {
        // Un-Mask (Enable) Alert
        usTargetAlertMask = (GET_TCPM_ALERT_MASK(ucPortIndex) | usAlertType);
    }
    else
    {
        // Mask (Disable) Alert
        usTargetAlertMask = (GET_TCPM_ALERT_MASK(ucPortIndex) & (~(usAlertType)));
    }

    // 3. Update Alert Mask Mask  & Reg
    SET_TCPM_ALERT_MASK(ucPortIndex, usTargetAlertMask);
    ScalerSetByte_WDINT(PFA_24_TCPC_0_ALERT_MASK_L + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usTargetAlertMask));
    ScalerSetByte_WDINT(PFA_25_TCPC_0_ALERT_MASK_H + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usTargetAlertMask >> 8));

    // 4. Start Alert Update (Do Not Need to Enable alert_update_irq_en)
    // [0xFA23] [2] tcpc_0_alert_update, [1] tcpc_0_alert_update_irq, [0] tcpc_0_alert_update_irq_en
    ScalerSetBit_WDINT(PFA_23_TCPC_0_ALERT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // 5. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _DISABLE);
#else
    // 1. Clear Alert
    ScalerTypeCTcpmTcpciSetWord_WDINT(ucPortIndex, _TCPM_TCPCI_REG_ALERT, usAlertType);

    if(bAction == _ENABLE)
    {
        // Un-Mask (Enable) Alert
        usTargetAlertMask = (GET_TCPM_ALERT_MASK(ucPortIndex) | usAlertType);
    }
    else
    {
        // Mask (Disable) Alert
        usTargetAlertMask = (GET_TCPM_ALERT_MASK(ucPortIndex) & (~(usAlertType)));
    }

    // 2. Update Alert Mask
    SET_TCPM_ALERT_MASK(ucPortIndex, usTargetAlertMask);
    ScalerTypeCTcpmTcpciSetWord_WDINT(ucPortIndex, _TCPM_TCPCI_REG_ALERT_MASK, usTargetAlertMask);
#endif // End of #if(_HW_TCPM_ALERT_UPDATE == _ON)

    // Enable / Disable Alert IRQ
    ScalerTypeCTcpmAlertIntControl_WDINT(ucPortIndex, usAlertType, bAction);

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    usAlertType = usAlertType;
    bAction = bAction;
    usTargetAlertMask = usTargetAlertMask;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Enable / Disable Receive Interrupt.
// Input Value  : ucPortIndex, b1Action
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmRxIntControl_WDINT(BYTE ucPortIndex, bit b1Action)
{
#if(_HW_TCPM_SUPPORT == _ON)

    if(b1Action == _ENABLE)
    {
        // Enable Rx Msg IRQ [0xFA48] [2] alert_rx_msg_irq_en
        ScalerSetBit_WDINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT2);

        // Enable Rx Overflow IRQ [0xFA44] [2] alert_rx_ov_irq_en
        ScalerSetBit_WDINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT2);
    }
    else
    {
        // Disable Rx Msg IRQ [0xFA48] [2] alert_rx_msg_irq_en
        ScalerSetBit_WDINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), 0x00);

        // Disable Rx Overflow IRQ [0xFA44] [2] alert_rx_ov_irq_en
        ScalerSetBit_WDINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), 0x00);
    }

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    b1Action = b1Action;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Enable Tool to Show Warning UI when We Provide Vbus > 5V
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmToolWarningUIControl_WDINT(bit bAction)
{
    // Tool Usage : [0xFA0E] [4] Used to Decide Whether Tool shall Show Warning UI when Disable Unattach HW Force Vbus Off Function([3]=0), 0 = Not Show UI, 1 = Show UI
    if(bAction == _ENABLE)
    {
        ScalerSetBit_WDINT(PFA_0E_DUMMY_1, ~_BIT4, _BIT4);
    }
    else
    {
        ScalerSetBit_WDINT(PFA_0E_DUMMY_1, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Process For Change Between SRC and SNK w/o Unattach
// Input Value  : ucPortIndex, ucTargetRole
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSwitchPowerRole_WDINT(BYTE ucPortIndex, BYTE ucTargetRole)
{
    if(ucTargetRole == _PD_POWER_SRC)
    {
        SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_ATTACH_SRC);

        // Set Rp to Default CC Rp
        // ROLE_CONTROL [0x1A] ([6] DRP = 1, [5:4] Rp Refer Macro, [3:2] CC1 = [1:0] CC2 = Rp)
        if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_USB)
        {
            SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT2 | _BIT0);
        }
        else if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_1P5A)
        {
            SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT4 | _BIT2 | _BIT0);
        }
        else
        {
            SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT5 | _BIT2 | _BIT0);
        }

        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));
    }
    else
    {
        SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_ATTACH_SNK);

        // Set Rd
        // ROLE_CONTROL [0x1A] ([6] DRP = 1, [5:4] Rp default, [3:2] CC1 = [1:0] CC2 = Rd)
        SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT3 | _BIT1);

        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));
    }
}

//--------------------------------------------------
// Description  : WDINT Process For Unattach Setting
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcUnattachSetting_WDINT(BYTE ucPortIndex)
{
    // From 1. AttachWait.SNK   2. Attach.SNK

    // Disable Alert IRQ
#if(_HW_TCPM_SUPPORT == _ON)
    // Clear & Disabel Alert IRQ : [0xFA23] [5] tcpc_0_alert_irq, [4] tcpc_0_alert_irq_en
    ScalerSetBit_WDINT(PFA_23_TCPC_0_ALERT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT4 | _BIT1), _BIT5);
#endif

    // Reset All Alert
    ScalerTypeCTcpmAlertControl_WDINT(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_ALL, _DISABLE);

    if(GET_TCPM_SRC_VCONN(ucPortIndex) == _TRUE)
    {
        // Turn Off Vconn, if they are turned on when attached
        ScalerTypeCTcpmVconnCtrl_WDINT(ucPortIndex, _OFF);
    }

    // Turn Off Vbus and Turn On Vbus Discharge
    ScalerTypeCTcpmVbusCtrl_WDINT(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
    ScalerTypeCTcpmVbusDischargeCtrl_WDINT(ucPortIndex, _ON);

    // Active WD Timer Event To Detect if Vbus is Already Discharge to vSafe0V
    ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, _UNATTACH_VBUS_DISCHARGE_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CC_CHECK_VBUS_0V);

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    if(GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON)
    {
        ScalerTypeCTcpmPmicReset_WDINT(ucPortIndex);
    }
#endif
    ScalerTypeCTcpmPdReset_WDINT(ucPortIndex);
    // FW Solution : Samsung S8 Clear Flag When CC Unattach (Not Cleared When PD Reset)
    ScalerTypeCTcpmPdClrInteropS8Flag_WDINT(ucPortIndex);
    ScalerTypeCTcpmCcUnattachReset_WDINT(ucPortIndex);

    // Setting for CC FSM Connection
    ScalerTypeCTcpmCcConnectionSet_WDINT(ucPortIndex);

    SET_TCPM_CC_FW_STATE(ucPortIndex, _TCPM_CC_FW_CONNECTING);

    // Enable Alert Detect and Start CC FSM
    ScalerTypeCTcpmCcConnectionStart_WDINT(ucPortIndex);
}

//--------------------------------------------------
// Description  : Type C TCPM Unattach (Turn Off Power / Disconnect Channel / Clear IRQs)
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcUnattachReset_WDINT(BYTE ucPortIndex)
{
    // CC Flags Reset
    CLR_TCPM_CC_ATTACHED(ucPortIndex);
    CLR_TCPM_CC_RA_EXIST(ucPortIndex);
    CLR_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
    CLR_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex);
    CLR_TCPM_CC_SNK_DET_UNATTACH(ucPortIndex);
    CLR_TCPM_CC_STATUS_CHG(ucPortIndex);
    CLR_TCPM_CC_SRC_DET(ucPortIndex);
    CLR_TCPM_CC_SNK_DET(ucPortIndex);

    // Set POWER_CONTROL [0x1C] : Disable All Power Control, Only Enable Voltage Monitor
    // [7] FRS = 0, [6] DIS_VOL_MNT = 0, [5] DIS_VOL_ALARM = 1, [4] AUTO_DISCH = 0, [3] BLD_DISCH = 0, [2] FRC_DISCH = 0, [1] VCONN_PWR = 0, [0] VCONN_EN = 0
    SET_TCPM_POWER_CONTROL(ucPortIndex, 0x20);
    ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
}

//--------------------------------------------------
// Description  : Type C TCPM CC Connection Setting
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcConnectionSet_WDINT(BYTE ucPortIndex)
{
    // Set ROLE_CONTROL [0x1A] : DRP, Rp Value, CC1, CC2
    switch(GET_TCPM_CC_PORT_ROLE(ucPortIndex))
    {
        case _TYPE_C_PORT_SNK_ONLY:

            // ROLE_CONTROL [0x1A] ([6] DRP = 0, [5:4] Rp default, [3:2] CC1 = [1:0] CC2 = Rd)
            SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT3 | _BIT1);

            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

            SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_UNATTACH_SNK);

            break;

        case _TYPE_C_PORT_SRC_ONLY:

            // ROLE_CONTROL [0x1A] ([6] DRP = 0, [5:4] Rp Refer Macro, [3:2] CC1 = [1:0] CC2 = Rp)
            if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_USB)
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT2 | _BIT0);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 90);  // 90 * 10mA = 900mA
            }
            else if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_1P5A)
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT4 | _BIT2 | _BIT0);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 150);  // 150 * 10mA = 1.5A
            }
            else
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT5 | _BIT2 | _BIT0);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 300); // 300 * 10mA = 3.0A
            }

            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

            SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_UNATTACH_SRC);

            break;

        case _TYPE_C_PORT_DRP:

            // ROLE_CONTROL [0x1A] ([6] DRP = 1, [5:4] Rp Refer Macro)
            if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_USB)
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 90);  // 90 * 10mA = 900mA
            }
            else if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_1P5A)
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT4);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 150);  // 150 * 10mA = 1.5A
            }
            else
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT5);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 300); // 300 * 10mA = 3.0A
            }

            if(GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_WAIT_SNK)
            {
                // AttachWait.SNK -> Unattach.SRC
                // ROLE_CONTROL [0x1A] ([3:2] CC1 = [1:0] CC2 = Rp)
                SET_TCPM_ROLE_CONTROL(ucPortIndex, GET_TCPM_ROLE_CONTROL(ucPortIndex) | _BIT2 | _BIT0);
            }
            else
            {
                // ROLE_CONTROL [0x1A] ([3:2] CC1 = [1:0] CC2 = Rd)
                SET_TCPM_ROLE_CONTROL(ucPortIndex, GET_TCPM_ROLE_CONTROL(ucPortIndex) | _BIT3 | _BIT1);
            }

            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

            SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_DRP_TOGGLE);

            break;

        default:

            // Other CC Operation Mode Need to be Implemented

            break;
    }
}

//--------------------------------------------------
// Description  : Type C TCPM CC Start FSM
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcConnectionStart_WDINT(BYTE ucPortIndex)
{
    // Enable ALERT.CC_STATUS
    ScalerTypeCTcpmAlertControl_WDINT(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_CC_STATUS, _ENABLE);

    // Start Look 4 Connection
    ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_LOOK_4_CONNECTION);
}

//--------------------------------------------------
// Description  : TypeC TCPM PD Reset
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdReset_WDINT(BYTE ucPortIndex)
{
    // -------------------- HW Clear, Disable or Reset to Default Value --------------------
    // 1. Disable PD Rcv Detect ([0x2F] : [5] HRST, [2] SOP", [1] SOP', [0] SOP)
    ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, 0x00);

    // 2. Disable BIST Mode
    if(GET_TCPM_PD_BIST_MODE(ucPortIndex) == _PD_BIST_TEST_DATA_MODE)
    {
        // TCPM Would Set TCPC_CONTROL [0x19], [1] = b'1 (BIST Test Data Mode) When Entering Test Data Mode
        // Disable Test Data Mode by Set TCPC_CONTROL [0x19], [1] = b'0
        SET_TCPM_TCPC_CONTROL(ucPortIndex, GET_TCPM_TCPC_CONTROL(ucPortIndex) & (~_BIT1));
        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_TCPC_CTRL, GET_TCPM_TCPC_CONTROL(ucPortIndex));
    }
    SET_TCPM_PD_BIST_MODE(ucPortIndex, _PD_BIST_MODE_NONE);

    // 3. Disable PD Tx/Rx Alert
    ScalerTypeCTcpmAlertControl_WDINT(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_HRST | _TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS | _TCPM_TCPCI_ALERT_RX_OVERFLOW), _DISABLE);

    // ------------------------- FW State & Counter & Flag Reset -------------------------
    // 4. Reset PD Related Macros
    // PD Initial States Setting
    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
    SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_STATE_NONE);
    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_NONE);

    ScalerTypeCTcpmPdClrHpd_WDINT(ucPortIndex);

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
    if((GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX) && (GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG))
    {
        ScalerTypeCTcpmPdPushHpd_WDINT(ucPortIndex, _PD_HPD_LOW, 0);
    }
#endif

    CLR_TCPM_PD_DPAM_ATTENTION_WAIT(ucPortIndex);
    CLR_TCPM_PD_DPAM_ENTER(ucPortIndex);
    SET_TCPM_PD_DPAM_CONFIG(ucPortIndex, _PD_USB_CONFIG);
    CLR_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex);
    CLR_TCPM_PD_PARTNER_INIT_ALT_MODE(ucPortIndex);
    CLR_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex);
    SET_TCPM_PD_HPD_STATUS(ucPortIndex, _LOW);
    SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_NONE);
    CLR_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(ucPortIndex);
    CLR_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE_DONE(ucPortIndex);

    // Reset Force Sending HPD IRQ Macros
    CLR_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex);

    // Swith DP Lane Mapping
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
    {
        ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToDx_WDINT(g_penumTypeCTcpmPort[ucPortIndex]), GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
    {
        ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToPx_WDINT(g_penumTypeCTcpmPort[ucPortIndex]), GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
    }
#endif

    // Cancel Timer Event
    ScalerTypeCTcpmPdUnattachCancelTimerEvent_WDINT(ucPortIndex);

    // Reset Counters
    CLR_TCPM_PD_SRC_CAP_CNT(ucPortIndex);
    CLR_TCPM_PD_HARD_RST_CNT(ucPortIndex);
    CLR_TCPM_PD_CHECK_VBUS_CNT(ucPortIndex);
    CLR_TCPM_PD_CBL_DISC_ID_RETRY_CNT(ucPortIndex);
    CLR_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex);
    CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);
    CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

    // Reset Flags
    CLR_TCPM_PD_GET_SNK_CAP_SENT(ucPortIndex);
    CLR_TCPM_PD_GET_SRC_CAP_SENT(ucPortIndex);
    CLR_TCPM_PD_PRS_REJECT(ucPortIndex);
    CLR_TCPM_PD_DRS_REJECT(ucPortIndex);
    CLR_TCPM_PD_VCS_REJECT(ucPortIndex);
    CLR_TCPM_PD_RCV_SRC_CAP(ucPortIndex);
    CLR_TCPM_PD_RCV_SNK_CAP(ucPortIndex);
    CLR_TCPM_PD_PRS_WAIT_FLAG(ucPortIndex);
    CLR_TCPM_PD_DRS_WAIT_FLAG(ucPortIndex);
    CLR_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex);
    CLR_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex);
    SET_TCPM_PD_GET_SNK_CAP_WAIT_FLAG(ucPortIndex);
    CLR_TCPM_PD_PRS_PROCESSING(ucPortIndex);
    CLR_TCPM_PD_VDMMSG_WAIT_FLAG(ucPortIndex);
    CLR_TCPM_PD_VDM_BUSY_FLAG(ucPortIndex);
    CLR_TCPM_PD_HRST_PWR_OFF(ucPortIndex);
    SET_TCPM_PD_NEW_POWER_STATE(ucPortIndex, 0);
    SET_TCPM_PD_NEW_POWER_INDICATOR(ucPortIndex, 0);
    CLR_TCPM_PD_TYPE_OF_ALERT(ucPortIndex, _TYPE_C_TYPE_OF_ALERT_ALL);
    CLR_TCPM_PD_BAT_STATUS(ucPortIndex, _TYPE_C_BAT_ALL);
    SET_TCPM_PD_EXT_ALERT_EVENT(ucPortIndex, _TYPE_C_EXT_ALERT_EVENT_NONE);
    CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
    SET_TCPM_PD_SPEC_VER(ucPortIndex, _PD_VERSION_3_0);
    SET_TCPM_PD_CBL_SPEC_VER(ucPortIndex, _PD_VERSION_3_0);
#else
    SET_TCPM_PD_SPEC_VER(ucPortIndex, _PD_VERSION_2_0);
    SET_TCPM_PD_CBL_SPEC_VER(ucPortIndex, _PD_VERSION_2_0);
#endif

    // Reset Cable Related Flags
    SET_TCPM_PD_CBL_MAX_CUR(ucPortIndex, _PD_DEFAULT_MAX_CUR);
    SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_PD_CAP_UNCONFIRMED);
    SET_TCPM_PD_CBL_PRODUCT_TYPE(ucPortIndex, _PD_PRODUCT_TYPE_UNDEFINED);
    CLR_TCPM_PD_CBL_MODAL_OPERATION_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_CONNECTOR_TYPE(ucPortIndex, _PD_CABLE_CONNECTOR_TYPE_UNCONFIRMED);
    CLR_TCPM_PD_CBL_EPR_MODE_CAPABLE(ucPortIndex);
    SET_TCPM_PD_CBL_TERMINATION_TYPE(ucPortIndex, _PD_CBL_TERMINATION_TYPE_UNDEFINED);
    SET_TCPM_PD_CBL_VCONN_REQUIRED(ucPortIndex);
    SET_TCPM_PD_CBL_MAX_VOL(ucPortIndex, 200);
    CLR_TCPM_PD_CBL_SBU_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_SBU_TYPE(ucPortIndex, _PD_CBL_SBU_TYPE_UNDEFINED);
    SET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex, _PD_CBL_USB_2_ONLY);
    CLR_TCPM_PD_CBL_VBUS_THROUGH(ucPortIndex);
    CLR_TCPM_PD_CBL_SOP_PP_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_U3_TO_U0_TRANSITION_MODE(ucPortIndex, _PD_CBL_U3_TO_U0_UNDEFINED);
    CLR_TCPM_PD_CBL_USB_4_SUPPORT(ucPortIndex);
    CLR_TCPM_PD_CBL_USB_3_2_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_LANES_SUPPORT(ucPortIndex, _PD_CBL_USB_LANES_SUPPORT_UNDEFINED);
    CLR_TCPM_PD_CBL_CHARGE_THROUGH_SUPPORT(ucPortIndex);
    CLR_TCPM_PD_CBL_SOFT_RESET_REQUIRED(ucPortIndex);

#if(_TYPE_C_SVDM_VERSION >= _SVDM_VERSION_2_1)
    // Default Set to 2.1 and Downgrade to 2.0 if Cable Only Support < 2.1
    SET_TCPM_PD_CBL_SVDM_VERSION(ucPortIndex, _PD_SVDM_VER_2_1);
#else
    SET_TCPM_PD_CBL_SVDM_VERSION(ucPortIndex, _PD_SVDM_VER_2_0_EARLIER);
#endif

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    SET_TCPM_PD_CBL_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_0_EARLIER);
    SET_TCPM_PD_CBL_ENTER_DP_MODE_SUPPORT(ucPortIndex);
    CLR_TCPM_PD_CBL_DP_SVID_SUPPORT(ucPortIndex);
    CLR_TCPM_PD_CBL_DP_MODE_INFO_RECEIVED(ucPortIndex);
    CLR_TCPM_PD_CBL_TBT3_SVID_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_PIN_ASSIGNMENT(ucPortIndex, _PD_CBL_PIN_ASSIGNMENT_UNCONFIRMED);
    SET_TCPM_PD_CBL_TBT3_PRODUCT_TYPE(ucPortIndex, _PD_CBL_TBT3_PRODUCT_TYPE_UNCONFIRMED);
    SET_TCPM_PD_CBL_TBT3_DIRECTION(ucPortIndex, _PD_CBL_TBT3_DIRECTION_UNCONFIRMED);
    CLR_TCPM_PD_CBL_TBT3_RETIMER(ucPortIndex);
    CLR_TCPM_PD_CBL_TBT3_OPTICAL(ucPortIndex);
    SET_TCPM_PD_CBL_TBT3_ROUNDED_SUPPORT(ucPortIndex, _PD_CBL_TBT3_ROUNDED_SUPPORT_UNCONFIRMED);
    SET_TCPM_PD_CBL_TBT3_SPEED(ucPortIndex, _PD_CBL_TBT3_SPEED_UNCONFIRMED);
    SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_PASSIVE);
    CLR_TCPM_PD_CBL_UHBR13P5_SUPPORT(ucPortIndex);
    SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_DP_RATE_UNCONFIRMED);
#endif

    // Reset All EPR Flag
    CLR_TCPM_PD_ENTER_EPR_MODE_FLOW(ucPortIndex);
    CLR_TCPM_PD_EPR_MODE(ucPortIndex);
    SET_TCPM_PD_EPR_MODE_ACTION(ucPortIndex, _PD_EPR_MODE_RESERVED);
    SET_TCPM_PD_ENTER_EPR_FAILED_REASON(ucPortIndex, _PD_EPR_MODE_ENTER_FAILED_UNKNOWN);
    SET_TCPM_PD_PARTNER_EPR_SINK_PDP(ucPortIndex, 0);

    // Clear All Port Partner Info
    SET_TCPM_PD_PARTNER_DRP(ucPortIndex, _FALSE);
    SET_TCPM_PD_PARTNER_DRD(ucPortIndex, _TRUE);
    CLR_TCPM_PD_PARTNER_SUSPEND(ucPortIndex);
    CLR_TCPM_PD_PARTNER_EXT_PWR(ucPortIndex);
    CLR_TCPM_PD_PARTNER_USB_CAP(ucPortIndex);
    CLR_TCPM_PD_PARTNER_UNCHK(ucPortIndex);
    SET_TCPM_PD_PARTNER_EPR_CAP(ucPortIndex, _FALSE);
    CLR_TCPM_PD_PARTNER_HIGH_CAP(ucPortIndex);
    CLR_TCPM_PD_PARTNER_FRS_CUR(ucPortIndex);
    SET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex, 0);
    SET_TCPM_PD_PARTNER_SNK_CAP_CNT(ucPortIndex, 0);
    SET_TCPM_PD_PARTNER_NEW_POWER_STATE(ucPortIndex, 0);
    SET_TCPM_PD_PARTNER_NEW_POWER_INDICATOR(ucPortIndex, 0);
    SET_TCPM_PD_PARTNER_TYPE_OF_ALERT(ucPortIndex, _TYPE_C_TYPE_OF_ALERT_NONE);
    SET_TCPM_PD_PARTNER_BAT_STATUS(ucPortIndex, _TYPE_C_BAT_NONE);
    SET_TCPM_PD_PARTNER_EXT_ALERT_EVENT(ucPortIndex, _TYPE_C_EXT_ALERT_EVENT_NONE);

#if(_TYPE_C_SVDM_VERSION >= _SVDM_VERSION_2_1)
    // Default Set to 2.1 and Downgrade to 2.0 if Port Partner Only Support < 2.1
    SET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex, _PD_SVDM_VER_2_1);
#else
    SET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex, _PD_SVDM_VER_2_0_EARLIER);
#endif

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    // Default Set to 2.1 and Downgrade to 2.0 if Port Partner Only Support < 2.1
    SET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_1_HIGHER);
#else
    SET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_0_EARLIER);
#endif

    // Reset Port Partner DP Status Related Flags
    SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_CONNECT_NONE);
    CLR_TCPM_PD_PARTNER_DPAM_POWER_LOW(ucPortIndex);
    CLR_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(ucPortIndex);
    CLR_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(ucPortIndex);
    CLR_TCPM_PD_PARTNER_DPAM_USB_CONFIG_REQUEST(ucPortIndex);
    CLR_TCPM_PD_PARTNER_DPAM_EXIT_REQ(ucPortIndex);
    SET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex, _PD_HPD_NONE);
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    CLR_TCPM_PD_PARTNER_DPAM_NO_SUSPEND(ucPortIndex);
#endif

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    CLR_TCPM_PD_REQ_PPS_VOL_SMALL_STEP(ucPortIndex);
#endif

    CLR_TCPM_PD_REQ_AVS_VOL_SMALL_STEP(ucPortIndex);
}

//--------------------------------------------------
// Description  : Process For Cable in WD Timer
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdWDTimerEventCableProc_WDINT(BYTE ucPortIndex)
{
    switch(GET_TCPM_PD_FW_STATE(ucPortIndex))
    {
        case _PD_WDINT_SEND_CBL_DISCOVER_ID:

            // Send Discover ID (SOP') to Get Cable Info
            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_INT_SEND_CBL_DISCOVER_ID);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);

            ScalerTypeCTcpmPdSendMsg_WDINT(ucPortIndex, _PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);

            break;

        case _PD_INT_WAIT_CBL_DISCOVER_ID_RESP:

            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_WDINT_SEND_CAP);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

            // Active WD Timer Event To Check Vbus, Then Start PMIC Protection and Send SRC_CAP if VbusSafe5V
            ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, 20, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);

            break;

        case _PD_WDINT_SEND_CBL_SOFT_RESET:

            // Send Soft Reset (SOP') to Reset Cable
            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_INT_SEND_CBL_SOFT_RESET);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_BY_STATE);

            ScalerTypeCTcpmPdSendSoftRst_WDINT(ucPortIndex, _PD_SOP_P_PKT);

            break;

        case _PD_INT_WAIT_CBL_SOFT_RESET_RESP:

            // Sender Response Timer Timeout After Sending Soft Reset to Cable
            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_WDINT_SEND_CBL_DISCOVER_ID);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

            // Active WD Timer Event To Send Discover ID(SOP')
            ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, 10, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

            break;

        case _PD_SRC_READY:
        case _PD_SNK_READY:

            switch(GET_TCPM_PD_SUB_STATE(ucPortIndex))
            {
                case _PD_SUB_CABLE_PROC:

                    switch(GET_TCPM_PD_CBL_STATE(ucPortIndex))
                    {
                        case _PD_CBL_INT_WAIT_SOFT_RST_RESP:

                            // Sender Response Timer Timeout After Sending Soft Reset to Cable
                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_STATE_NONE);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_CBL_INT_WAIT_DISCOVER_ID_RESP:

                            // Sender Response Timer Timeout After Sending Discover ID to Cable
                            ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex) >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);
                                SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_NON_PD_CAPABLE);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_STATE_NONE);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        default:

                            break;
                    }

                    break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))
                case _PD_SUB_INT_WAIT_VDM_RESP:

                    switch(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex))
                    {
                        case _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Discover ID to Cable
                            ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex) >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);
                                SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_NON_PD_CAPABLE);

                                // If No VDO Received, Set Passive Cable & HBR3 According to DPAM2.1
                                SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_PASSIVE);
                                SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_HBR3);

                                // Stop Enter DP Alt Mode Flow Just for Cable
                                CLR_TCPM_PD_CBL_ENTER_DP_MODE_SUPPORT(ucPortIndex);
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Discover SVID to Cable
                            ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex) >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No Response of Discover Svid(SOP' / SOP'') Received
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_WDINT(ucPortIndex));
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_DISCOVER_MODE_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Discover DP Mode to Cable
                            ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex) >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No Response of DP Discover Mode(SOP' / SOP'') Received
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_WDINT(ucPortIndex));
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_TBT3_DISCOVER_MODE_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Discover TBT3 Mode to Cable
                            ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex) >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No Response of TBT3 Discover Mode(SOP' / SOP'') Received
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_WDINT(ucPortIndex));
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Enter DP Mode to Cable
                            ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex) >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_PP:

                            // Sender Response Timer Timeout After Sending Enter DP Mode to Cable
                            ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex) >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending DP Config to Cable
                            ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex) >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_PP:

                            // Sender Response Timer Timeout After Sending DP Config to Cable
                            ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex) >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Exit DP Mode to Cable
                            ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex) >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_PP:

                            // Sender Response Timer Timeout After Sending Exit DP Mode to Cable
                            ADD_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex) >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_WDINT(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        default:

                            break;
                    }

                    break;
#endif  // End of #if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))

                default:

                    break;
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Send PD Message
// Input Value  : ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSendMsg_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucTransmitInfo = 0x00;

    // 1. Clear and Enable Tx_SUCCESS + Tx_FAIL + Tx_DISCARD
    ScalerTypeCTcpmAlertControl_WDINT(ucPortIndex, ((WORD)(_TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS)), _ENABLE);

    // 2. Construct Message and Write Data to Tx Buffer [0x51~]
    ScalerTypeCTcpmPdConstructMsg_WDINT(ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd);

    // 3. Send Message
    // TRANSMIT [0x50] [5:4] Retry Counter (PD2.0 = 3, PD3.0 = 2)
    // TRANSMIT [0x50] [2:0] SOP Type : 000b (SOP), 001b (SOP'), 010b (SOP"),
    if(enumPacketType == _PD_SOP_PKT)
    {
        if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex);
    }
    else if(enumPacketType == _PD_SOP_P_PKT)
    {
        if(GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4 | _BIT0);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT0);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex);
    }
    else if(enumPacketType == _PD_SOP_PP_PKT)
    {
        if(GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4 | _BIT1);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT1);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex);
    }

    // Disable Rx Int
    ScalerTypeCTcpmRxIntControl_WDINT(ucPortIndex, _DISABLE);

    // Set Transmit
    ScalerTypeCTcpmTcpciSetTransmit_WDINT(ucPortIndex, ucTransmitInfo);
}

//--------------------------------------------------
// Description  : Type C TCPM Construct PD Message to Send
// Input Value  : ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructMsg_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucExtendedBit_WDINT = 0;
    BYTE ucDataObjectCnt_WDINT = 0;
    WORD usMsgHeader_WDINT = 0;

    // 1. Set Up Number of Data Objects(Data Blocks) if Needed
    switch(enumPdCmd)
    {
        // ------------------------------------
        // Control Message
        // Extended = 0, Data Object = 0
        // ------------------------------------
        case _PD_CMD_RSV:
        case _PD_CMD_GOODCRC:
        case _PD_CMD_GOTOMIN:
        case _PD_CMD_ACCEPT:
        case _PD_CMD_REJECT:
        case _PD_CMD_PING:
        case _PD_CMD_PS_RDY:
        case _PD_CMD_GET_SRC_CAP:
        case _PD_CMD_GET_SNK_CAP:
        case _PD_CMD_DR_SWAP:
        case _PD_CMD_PR_SWAP:
        case _PD_CMD_VCONN_SWAP:
        case _PD_CMD_WAIT:
        case _PD_CMD_SOFT_RESET:
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_NOT_SUPPORT:
        case _PD_CMD_GET_SRC_CAP_EXT:
        case _PD_CMD_GET_STATUS:
        case _PD_CMD_FR_SWAP:
        case _PD_CMD_GET_PPS_STATUS:
        case _PD_CMD_GET_COUNTRY_CODES:
#endif

            ucExtendedBit_WDINT = 0;
            ucDataObjectCnt_WDINT = 0;

            break;

        // ------------------------------------
        // Data Message
        // Extended = 0, Data Object = According to Message Type
        // ------------------------------------
        case _PD_CMD_SRC_CAP:

            ucExtendedBit_WDINT = 0;
            ucDataObjectCnt_WDINT = GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex);

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            // Do not send PPS PDO when the Spec Version is PD2.0 or not support PPS
            if((GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0))
#endif
            {
                for(BYTE ucLoopIndex = GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex) - 1; ucLoopIndex > 0; ucLoopIndex--)
                {
                    if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        ucDataObjectCnt_WDINT --;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            break;

        case _PD_CMD_REQUEST:

            ucDataObjectCnt_WDINT = 1;

            break;

        case _PD_CMD_VDM:

            switch(enumVdmCmd)
            {
                case _PD_VDM_CMD_DISCOVER_ID_REQ:

                    ucExtendedBit_WDINT = 0;
                    ucDataObjectCnt_WDINT = 1;

                    break;

                default:

                    break;
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_ALERT:

            ucExtendedBit_WDINT = 0;
            ucDataObjectCnt_WDINT = 1;

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        // ------------------------------------
        // Extended Message
        // Extended = 1, Data Object = According to Message Type
        // ------------------------------------

        default:

            ucExtendedBit_WDINT = 0;
            ucDataObjectCnt_WDINT = 0;

            break;
    }

    // 2. Construct Data Object into Tx FIFO, if Number of Data Object is not 0
    if(ucDataObjectCnt_WDINT != 0)
    {
        ScalerTypeCTcpmPdConstructDataObj_WDINT(ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd);
    }

    // 3. Construct Message Header
    // [15] Extended, [14:12] Num of Data Obj., [4:0] Command
    usMsgHeader_WDINT = (((ucExtendedBit_WDINT & (_BIT0)) << 15) | ((ucDataObjectCnt_WDINT & (_BIT2 | _BIT1 | _BIT0)) << 12) | (enumPdCmd & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

    if(enumPacketType == _PD_SOP_PKT)
    {
        // [11:9] Message ID, [8] Power Role, [7:6] Spec Ver, [5] Data Role
        usMsgHeader_WDINT = (usMsgHeader_WDINT | (GET_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex) << 9) | (GET_TCPM_POWER_ROLE(ucPortIndex) << 8) | (GET_TCPM_PD_SPEC_VER(ucPortIndex) << 6) | (GET_TCPM_DATA_ROLE(ucPortIndex) << 5));
    }
    else if(enumPacketType == _PD_SOP_P_PKT)
    {
        // [11:9] Message ID, [8] Cable Plug : Device(0), [7:6] Spec Ver, [5] Rsv.
        usMsgHeader_WDINT = (usMsgHeader_WDINT | (GET_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex) << 9) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }
    else if(enumPacketType == _PD_SOP_PP_PKT)
    {
        // [11:9] Message ID, [8] Cable Plug : Device(0), [7:6] Spec Ver, [5] Rsv.
        usMsgHeader_WDINT = (usMsgHeader_WDINT | (GET_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex) << 9) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }

    // 4. Write Message to TCPC Tx Buffer (Port, TxByteCnt, Message Header)
    ScalerTypeCTcpmTcpciSetTxBuffer_WDINT(ucPortIndex, enumPdCmd, (2 + (ucDataObjectCnt_WDINT * 4)), usMsgHeader_WDINT);
}

//--------------------------------------------------
// Description  : Type C TCPM Construct PD Message to Send
// Input Value  : ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructDataObj_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    // Clear ucDataObj_EXINT
    memset(g_pucTypeCTcpmPdDataObj_EXINT, 0, sizeof(g_pucTypeCTcpmPdDataObj_EXINT));

    // Process Data Object Fields For FIFO Fill
    switch(enumPdCmd)
    {
        case _PD_CMD_SRC_CAP:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| DRP| Sus| UP | UC | DRD| Unc|
            if((GET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex) == _TRUE))
            {
                if(GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP)
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT5);
                }
            }

#if(_USB_SUSPEND == _TRUE)
            g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT4);
#endif
            if(GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _TRUE)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT3);
            }

            if(GET_TCPM_USB_ROLE(ucPortIndex) != _TYPE_C_USB_NOT_SUPPORT)
            {
                // TCPM Enable USB Support
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT2);
            }

            if((GET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex) == _TRUE) || (GET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex) == _TRUE))
            {
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT1);
            }

#if(_UNCHUNK_SUPPORT == _TRUE)
            if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT0);
            }
#endif

            // [23] EPR Mode Capable
            if(GET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex) == _TRUE)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[1] = g_pucTypeCTcpmPdDataObj_EXINT[1] | (_BIT7);
            }

            for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex); ucLoopIndex ++)
            {
                if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucLoopIndex) == _PD_FIX_SUPPLY_PDO)
                {
                    // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] | (((BYTE)GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucLoopIndex)) << 6);

                    // | 23 | 22 | 21 | 20 | 19 | 18 | 17 | 16 |
                    // |  Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)(GET_TCPM_PD_SRC_CAP_PEAK(ucPortIndex, ucLoopIndex) << 4) & (_BIT5 | _BIT4));
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)((GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                    // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)((GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    if((GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC) && (GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucLoopIndex) > GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex)))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)(GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex) >> 8) & (_BIT1 | _BIT0));
                        g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex));
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)(GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucLoopIndex) >> 8) & (_BIT1 | _BIT0));
                        g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)(GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucLoopIndex)));
                    }
                }
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
                else if((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0) && (GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO))
                {
                    // [31:30] PDO Type = 2'b11 (Programmabl Power Supply)
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] | (((BYTE)GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucLoopIndex)) << 6);

                    // [24:17] Max Voltage in 100mV
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] | ((BYTE)((GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex) / 10) >> 7) & (_BIT0));
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)((GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex) / 10) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] = (BYTE)(GET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, ucLoopIndex) / 10);

                    // [6:0] Max Current in 50mA
                    if((GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC) && (((GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucLoopIndex)) * 5) > GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex)))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 3] = (((BYTE)(GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex) / 5)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 3] = (((BYTE)GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucLoopIndex)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }
#endif  // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            }

            break;

        case _PD_CMD_REQUEST:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | 0  |   Obj. Pos   | GB | CM | UC | Sus|
            g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) << 4);
            g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (GET_TCPM_PD_REQ_GIVE_BACK(ucPortIndex) << 3);

            if((GET_TCPM_USB_ROLE(ucPortIndex) != _TYPE_C_USB_NOT_SUPPORT) || (GET_TCPM_USB_SPEED(ucPortIndex) == _USB_BILLBOARD_ONLY))
            {
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT1);
            }

#if(_USB_SUSPEND == _FALSE)
            g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT0);
#endif

            // | 23 | 22 | 21 | 20 | 19 | ... | 16 | 15 | ... | 10 | 09 | 08 | 07 | ... | 00 |
            // | UC | Reserved(0)  |         Info1 [19:10]         |       Info2 [9:0]       |
#if(_UNCHUNK_SUPPORT == _TRUE)
            g_pucTypeCTcpmPdDataObj_EXINT[1] = g_pucTypeCTcpmPdDataObj_EXINT[1] | (_BIT7);
#endif

            if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) == _PD_FIX_SUPPLY_PDO)
            {
                if((WORD)GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) < GET_TCPM_PD_REQ_INFO_2(ucPortIndex))
                {
                    // Set Capability Mismatch Flag
                    g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT2);

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucTypeCTcpmPdDataObj_EXINT[1] = g_pucTypeCTcpmPdDataObj_EXINT[1] | ((BYTE)(GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | ((BYTE)(GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | ((BYTE)(GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) >> 8) & (_BIT1 | _BIT0));
                    g_pucTypeCTcpmPdDataObj_EXINT[3] = g_pucTypeCTcpmPdDataObj_EXINT[3] | (BYTE)(GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1));
                }
                else
                {
                    // Set Capability Mismatch Flag
                    g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | ((GET_TCPM_PD_REQ_CAP_MIS(ucPortIndex) << 2) & (_BIT2));

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucTypeCTcpmPdDataObj_EXINT[1] = g_pucTypeCTcpmPdDataObj_EXINT[1] | ((BYTE)(GET_TCPM_PD_REQ_INFO_1(ucPortIndex) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | ((BYTE)(GET_TCPM_PD_REQ_INFO_1(ucPortIndex) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | ((BYTE)(GET_TCPM_PD_REQ_INFO_2(ucPortIndex) >> 8) & (_BIT1 | _BIT0));
                    g_pucTypeCTcpmPdDataObj_EXINT[3] = g_pucTypeCTcpmPdDataObj_EXINT[3] | (BYTE)(GET_TCPM_PD_REQ_INFO_2(ucPortIndex));
                }
            }
            else
            {
                // Set Capability Mismatch Flag
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | ((GET_TCPM_PD_REQ_CAP_MIS(ucPortIndex) << 2) & (_BIT2));

                // RDO[19:9] : PPS (Vol in 20mV)
                g_pucTypeCTcpmPdDataObj_EXINT[1] = g_pucTypeCTcpmPdDataObj_EXINT[1] | ((BYTE)(GET_TCPM_PD_REQ_INFO_1(ucPortIndex) >> 7) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | ((BYTE)(GET_TCPM_PD_REQ_INFO_1(ucPortIndex) << 1) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

                // RDO[6:0] : PPS (Op. Cur in 50mA)
                g_pucTypeCTcpmPdDataObj_EXINT[3] = g_pucTypeCTcpmPdDataObj_EXINT[3] | ((BYTE)(GET_TCPM_PD_REQ_INFO_2(ucPortIndex)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            }

            break;

        case _PD_CMD_VDM:

            ScalerTypeCTcpmPdConstructVdmDataObj_WDINT(ucPortIndex, enumPacketType, enumVdmCmd);

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_ALERT:

            // ---------- Data Message (1 Data Object) ----------
            // Set Type of Alert : [30] OVP Event, [26] OCP Event
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
            if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT6);
            }
            if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT2);
            }
#endif

            // [31:24] Type of Alert
            g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (BYTE)(GET_TCPM_PD_TYPE_OF_ALERT(ucPortIndex));

            // [23:20] Fixed Batteries, [19:16] Hot Swappable Batteries
            g_pucTypeCTcpmPdDataObj_EXINT[1] = g_pucTypeCTcpmPdDataObj_EXINT[1] | (BYTE)(GET_TCPM_PD_BAT_STATUS(ucPortIndex));

            // [15:4] Rsv., [3:0] Extended Alert Event Type
            g_pucTypeCTcpmPdDataObj_EXINT[3] = g_pucTypeCTcpmPdDataObj_EXINT[3] | ((BYTE)(GET_TCPM_PD_EXT_ALERT_EVENT(ucPortIndex)) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        default:

            break;
    }// End of switch(enumPdCmd)
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO @ WD Timer
// Input Value  : ucPortIndex, enumPacketType, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructVdmDataObj_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd)
{
    switch(enumVdmCmd)
    {
        case _PD_VDM_CMD_DISCOVER_ID_REQ:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] PD SID = 0xFF00
            g_pucTypeCTcpmPdDataObj_EXINT[0] = 0xFF;
            g_pucTypeCTcpmPdDataObj_EXINT[1] = 0x00;

            // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos = b'000
            g_pucTypeCTcpmPdDataObj_EXINT[2] = (_BIT7);

            // For SOP Packet : If Port Partners Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            // For SOP' Packet : If Port Partners & Cable Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(((enumPacketType == _PD_SOP_PKT) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)) ||
               ((enumPacketType == _PD_SOP_P_PKT) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0) && (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)))
            {
                g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT5);

                // SVDM Version = 2.1 Only when Port Partner or Cable Support 2.1 or Higher
                if(((enumPacketType == _PD_SOP_PKT) && (GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)) ||
                   ((enumPacketType == _PD_SOP_P_PKT) && (GET_TCPM_PD_CBL_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Discover ID Request (0x01) / Discover SVID Request (0x02)
            g_pucTypeCTcpmPdDataObj_EXINT[3] = enumVdmCmd;

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Send PD  Soft Reset Message
// Input Value  : ucPortIndex, enumPacketType
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSendSoftRst_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType)
{
    BYTE ucTransmitInfo = 0x00;

    // 1. Clear and Enable Tx_SUCCESS + Tx_FAIL + Tx_DISCARD
    ScalerTypeCTcpmAlertControl_WDINT(ucPortIndex, ((WORD)(_TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS)), _ENABLE);

    // 2. Construct Message and Write Data to Tx Buffer [0x51~]
    ScalerTypeCTcpmPdConstructSoftRst_WDINT(ucPortIndex, enumPacketType);

    // 3. Send Message
    // TRANSMIT [0x50] [5:4] Retry Counter (PD2.0 = 3, PD3.0 = 2)
    // TRANSMIT [0x50] [2:0] SOP Type : 000b (SOP), 001b (SOP'), 010b (SOP"),
    if(enumPacketType == _PD_SOP_PKT)
    {
        if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex);
    }
    else if(enumPacketType == _PD_SOP_P_PKT)
    {
        if(GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4 | _BIT0);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT0);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex);
    }
    else if(enumPacketType == _PD_SOP_PP_PKT)
    {
        if(GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT4 | _BIT1);
        }
        else
        {
            ucTransmitInfo = ucTransmitInfo | (_BIT5 | _BIT1);
        }

        ADD_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex);
    }

    ScalerTypeCTcpmTcpciSetTransmit_WDINT(ucPortIndex, ucTransmitInfo);
}

//--------------------------------------------------
// Description  : Type C TCPM Construct PD Soft Reset Message
// Input Value  : ucPortIndex, enumPacketType
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructSoftRst_WDINT(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType)
{
    WORD usMsgHeader_WDINT = 0;

    // 1. Construct Soft Reset Message Header
    // [15] Extended, [14:12] Num of Data Obj., [4:0] Command = _PD_CMD_SOFT_RESET
    usMsgHeader_WDINT = (_PD_CMD_SOFT_RESET & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    if(enumPacketType == _PD_SOP_PKT)
    {
        // Reset Message ID
        CLR_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex);
        CLR_TCPM_PD_RX_MSG_ID_SOP(ucPortIndex);

        // [11:9] Message ID, [8] Power Role, [7:6] Spec Ver, [5] Data Role
        usMsgHeader_WDINT = (usMsgHeader_WDINT | (GET_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex) << 9) | (GET_TCPM_POWER_ROLE(ucPortIndex) << 8) | (GET_TCPM_PD_SPEC_VER(ucPortIndex) << 6) | (GET_TCPM_DATA_ROLE(ucPortIndex) << 5));
    }
    else if(enumPacketType == _PD_SOP_P_PKT)
    {
        // Reset Message ID
        CLR_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex);
        CLR_TCPM_PD_RX_MSG_ID_SOP_P(ucPortIndex);

        // [11:9] Message ID, [8] Cable Plug : Device(1), [7:6] Spec Ver, [5] Rsv.
        usMsgHeader_WDINT = (usMsgHeader_WDINT | (GET_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex) << 9) | (_BIT8) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }
    else if(enumPacketType == _PD_SOP_PP_PKT)
    {
        // Reset Message ID
        CLR_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex);
        CLR_TCPM_PD_RX_MSG_ID_SOP_PP(ucPortIndex);

        // [11:9] Message ID, [8] Cable Plug, [7:6] Spec Ver, [5] Rsv.
        usMsgHeader_WDINT = (usMsgHeader_WDINT | (GET_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex) << 9) | (_BIT8) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }

    // 4. Write Message to TCPC Tx Buffer (Port, Cmd = Soft Reset, TxByteCnt = 2(Message Header), Message Header)
    ScalerTypeCTcpmTcpciSetTxBuffer_WDINT(ucPortIndex, _PD_CMD_SOFT_RESET, 2, usMsgHeader_WDINT);
}

//--------------------------------------------------
// Description  : Type C TCPM Send PD  Soft Reset Message
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSendHardRst_WDINT(BYTE ucPortIndex)
{
    if(GET_TCPM_PD_HARD_RST_CNT(ucPortIndex) <= _MAX_HARD_RST_CNT)
    {
        ADD_TCPM_PD_HARD_RST_CNT(ucPortIndex);

        // Disable Tx Discard, Rx, Sink Disconnect (TCPC Will Set TX_Success + TX_Fail After Sending HRST)
        ScalerTypeCTcpmAlertControl_WDINT(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_HRST | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_RX_OVERFLOW | _TCPM_TCPCI_ALERT_SNK_DISC), _DISABLE);

        // TRANSMIT [0x50] [5:4] Retry Counter (00b), [2:0] SOP Type : 101b (HRST)
        ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_TRANSMIT, 0x05);

        // Process Hard Reset
        ScalerTypeCTcpmPdProcHardRst_WDINT(ucPortIndex);
    }
    else
    {
        SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Hard Reset Process when Receive, Sent Hard Reset
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdProcHardRst_WDINT(BYTE ucPortIndex)
{
    // Clear Hard Reset Turn Off Power Flag (Set When 1.Power Already Turned Off to vSafe0v for SRC 2.Vbus Already Not vSafe5v)
    CLR_TCPM_PD_HRST_PWR_OFF(ucPortIndex);

    if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
    {
        // Source can Start Changing Power After tSrcTransition = 25-35 ms (Vbus + Vconn)
        ScalerTypeCTcpmWDActiveTimerEvent_WDINT(ucPortIndex, _SRC_ADJUST_POWER_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER);
    }
    else
    {
        // 1. Turn Off Power Draw, Vbus should be drive to vSafe0V by Source (PD 7.1.5).
        ScalerTypeCTcpmVbusCtrl_WDINT(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

        // 2. Turn Off Type-C Unattach Vbus Detection
        // (On-Semi) "DO NOT" Turn Off Vbus Detection, It Will Cause Unattach Immediately
        if(GET_TCPM_TCPC_TYPE(ucPortIndex) != _TCPC_ON_SEMI)
        {
            ScalerTypeCTcpmVbusDetCtrl_WDINT(ucPortIndex, _DISABLE);
        }

        // 3. Active Wait 3sec for Source to Complete Hard Reset (MM1AE-2705), Canceled when Hard Reset Complete (PD Reset)
        ScalerTypeCTcpmActiveTimerEvent_WDINT(ucPortIndex, _SNK_HARD_RST_TIMER, _SCALER_TIMER_EVENT_TCPM_SNK_HARD_RST_TIMEOUT);
    }

    // Turn Off Vconn, If Already Turned On
    if(GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC)
    {
        ScalerTypeCTcpmVconnCtrl_WDINT(ucPortIndex, _OFF);
    }

    // RECEIVE_DETECT Disabled by TCPC
    // Hard Reset Related ALERT Has Been Cleared when Receive Hard Reset

    // State Transition
    SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_HARDRESET);
    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);
    SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_STATE_NONE);
}

//--------------------------------------------------
// Description  : PD Update Message Info for GoodCRC
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdUpdateGoodCRCInfo_WDINT(BYTE ucPortIndex)
{
    // [4] CABLE_PLUG = 0 (Port), [2:1] SPEC_VER = b'01 (Rev 2.0) for GoodCRC Resp. Always Use Rev 2.0 for Response
    BYTE ucMsgHeaderInfo = 0x02;

    // [3] DATA_ROLE = by Macro (0:UFP, 1:DFP)
    if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
    {
        ucMsgHeaderInfo |= (_BIT3);
    }

    // [0] POWER_ROLE = by Macro (0:Sink, 1:Source)
    if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
    {
        ucMsgHeaderInfo |= (_BIT0);
    }

    // Set MSG_HEADER_INFO [0x2E] :
    ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_MSG_HEADER_INFO, ucMsgHeaderInfo);
}

//--------------------------------------------------
// Description  : Go Back To Src/Snk Ready State According to Power Role
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdBackToReadyState_WDINT(BYTE ucPortIndex)
{
    // Back to Ready State
    if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
    {
        SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_READY);
        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SRC_READY);

        // If PD 3.0, Change Rp to SinkTxOK (Rp-3A)
        if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
        {
            // ROLE_CONTROL [0x1A], [5:4] = b'00(Rp-Def), b'01(Rp-1.5A), b'10(Rp-3A)
            SET_TCPM_ROLE_CONTROL(ucPortIndex, (GET_TCPM_ROLE_CONTROL(ucPortIndex) & (~(_BIT5 | _BIT4))) | (_BIT5));
            ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));
        }
    }
    else
    {
        SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_READY);
        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SNK_READY);
    }
}

//--------------------------------------------------
// Description  : Cancel All Timer Events When CC Unattach
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdUnattachCancelTimerEvent_WDINT(BYTE ucPortIndex)
{
    CLR_TCPM_PD_TIMER_EVENT_VALID(ucPortIndex);

    // Cancel Timer Event
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SNK_HARD_RST_TIMEOUT);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_REQ_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_PARTNER_ALT_SUPPORT);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_T480_ERROR_RECOVERY);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_VDM_RESP_CONFLICT_TIMEOUT);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_ATTENTION_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_GET_SNK_CAP_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_S8_HRST);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SEND_HARD_RST);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_TPC_ERROR_RECOVERY);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_PRS_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_DRS_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_VCS_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_VDMMSG_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_VDM_BUSY_FLAG);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_DFP_START_ALT_MODE);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_PPS_TIMEOUT);
#endif
#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
#endif
#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_PMIC_TRACKING);
    ScalerTypeCTcpmCancelTimerEvent_WDINT(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_PMIC_POLLING_OCP);
#endif

    SET_TCPM_WD_TIME_LEFT(ucPortIndex, 0);
    CLR_TCPM_WD_EVENT_TRIGGERED(ucPortIndex);

    // Cancel WD Timer Event
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_SRC_CAP);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PS_TRANSITION_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_REQUEST);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SNK_SWITCH_TO_SRC);
    ScalerTypeCTcpmWDCancelTimerEvent_WDINT(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_VCONN_ON_PSRDY);
}

//--------------------------------------------------
// Description  : Clear HPD Queue When PD Reset TO Prevent DP Urgent Event DeadLock
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdClrHpd_WDINT(BYTE ucPortIndex)
{
    BYTE ucIndex = 0;
    EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];

    for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
    {
        SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_NONE);
        SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, 0);
        ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
    }

#if(_DP_SUPPORT == _ON)
    ScalerDpAuxRxHpdTogglePhyResetProc(ScalerTypeCPcbPortConvertToDx_WDINT(enumTypeCPcbPort), _LOW);
#endif

    SET_TCPM_PD_HPD_STATUS(ucPortIndex, _LOW);
    CLR_TCPM_PD_HPD_WPTR(ucPortIndex);
    CLR_TCPM_PD_HPD_RPTR(ucPortIndex);
    CLR_TCPM_PD_HPD_CNT(ucPortIndex);
}

//--------------------------------------------------
// Description  : Push HPD into HPD Queue
// Input Value  : ucPortIndex, enumHpdType : _PD_HPD_LOW / _PD_HPD_HIGH..., HPD Space Time(ms)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdPushHpd_WDINT(BYTE ucPortIndex, EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime)
{
    BYTE ucIndex = 0;

    // Push Queue Only Vlid When Alt Mode is Ready
    if(GET_TCPM_PD_DPAM_ENTER(ucPortIndex) != _TRUE)
    {
        return;
    }

    switch(enumHpdType)
    {
        case _PD_HPD_LOW:

            for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
            {
                SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_NONE);
                SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, 0);
                ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
            }

            CLR_TCPM_PD_HPD_WPTR(ucPortIndex);
            CLR_TCPM_PD_HPD_RPTR(ucPortIndex);
            CLR_TCPM_PD_HPD_CNT(ucPortIndex);

            SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_LOW);
            SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, usHpdSpaceTime);

            ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
            ADD_TCPM_PD_HPD_CNT(ucPortIndex);

            break;

        case _PD_HPD_HIGH:

            if((GET_TCPM_PD_HPD_CNT(ucPortIndex) == 0) || (GET_TCPM_PD_HPD_QUEUE(ucPortIndex, (GET_TCPM_PD_HPD_WPTR(ucPortIndex) + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_HIGH))
            {
                SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_HIGH);
                SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, usHpdSpaceTime);

                ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
                ADD_TCPM_PD_HPD_CNT(ucPortIndex);
            }

            break;

        case _PD_HPD_IRQ:

            // Make sure HPD_IRQ has a minumun spacing time of 10ms (DP Alt Mode 5.2.2)
            usHpdSpaceTime = (usHpdSpaceTime < _ATTENTION_SPACING_TIMER) ? _ATTENTION_SPACING_TIMER : usHpdSpaceTime;

            if(GET_TCPM_PD_HPD_CNT(ucPortIndex) <= 1)
            {
                SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_IRQ);
                SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, usHpdSpaceTime);

                ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
                ADD_TCPM_PD_HPD_CNT(ucPortIndex);
            }
            else
            {
                // If Last 2 HPDs are Not Both HPD_IRQs, Push New HPD_IRQ
                if((GET_TCPM_PD_HPD_QUEUE(ucPortIndex, (GET_TCPM_PD_HPD_WPTR(ucPortIndex) + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ) ||
                   (GET_TCPM_PD_HPD_QUEUE(ucPortIndex, (GET_TCPM_PD_HPD_WPTR(ucPortIndex) + _HPD_QUEUE_DEPTH - 2) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ))
                {
                    SET_TCPM_PD_HPD_QUEUE(ucPortIndex, _PD_HPD_IRQ);
                    SET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, usHpdSpaceTime);

                    ADD_TCPM_PD_HPD_WPTR(ucPortIndex);
                    ADD_TCPM_PD_HPD_CNT(ucPortIndex);
                }
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Clear Interop S8 Flag to Enable FW Solution
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdClrInteropS8Flag_WDINT(BYTE ucPortIndex)
{
    CLR_TCPM_PD_INTEROP_S8(ucPortIndex);
}

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
//--------------------------------------------------
// Description  : Judge DP Functionality Support Of Cable(No Ack Vdo Received For Discover Svid(SOP'/SOP'') / Discover Mode(SOP'/SOP''))
// Input Value  : ucPortIndex
// Output Value : EnumTypeCPDAltModeState(_PD_ALT_MODE_SEND_ENTER_MODE / _PD_ALT_MODE_ERROR)
//--------------------------------------------------
EnumTypeCPDAltModeState ScalerTypeCTcpmPdJudgeCableDpFunctionality_WDINT(BYTE ucPortIndex)
{
    if(GET_TCPM_PD_CBL_DP_MODE_INFO_RECEIVED(ucPortIndex) == _TRUE)
    {
        // If Already Received Cable DP Discover Mode Ack, Do Enter Mode When Not Received Cable TBT3 Discover Mode ACK.
        // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Enter Mode First
        if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
        {
            return _PD_ALT_MODE_SEND_ENTER_MODE_SOP_P;
        }
        else
        {
            return _PD_ALT_MODE_SEND_ENTER_MODE;
        }
    }
    else
    {
        // Use Discover ID Ack (SOP'/SOP'') to Judge Cable DP Functionality When No Ack Vdo Received For Discover Svid(SOP'/SOP'') / Discover Mode(SOP'/SOP'')
        if(GET_TCPM_PD_CBL_PRODUCT_TYPE(ucPortIndex) == _PD_PASSIVE_CABLE)
        {
            if((GET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex) == _PD_CBL_USB_3_GEN1) || (GET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex) == _PD_CBL_USB_3OR4_GEN2))
            {
                SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_UHBR10);
            }
            else if(GET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex) == _PD_CBL_USB_4_GEN3)
            {
                SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_UHBR20);

                // UHBR20 Capable Passive Cable Shall Support UHBR13.5
                SET_TCPM_PD_CBL_UHBR13P5_SUPPORT(ucPortIndex);
            }

            // Stop Enter DP Alt Mode Flow Just for Cable
            CLR_TCPM_PD_CBL_ENTER_DP_MODE_SUPPORT(ucPortIndex);

            return _PD_ALT_MODE_SEND_ENTER_MODE;
        }
        else
        {
            // If Cable Type is Active Cable, Stop Enter DP Alt Mode Flow Both for Device & Cable
            return _PD_ALT_MODE_ERROR;
        }
    }
}
#endif
#endif
#endif

//--------------------------------------------------
// Description  : Type C TCPM Get TCPCI Byte Register (for 1-Byte Reg)
// Input Value  : ucPortIndex, enumReg
// Output Value : pucTcpciData (1-Byte)
//--------------------------------------------------
BYTE ScalerTypeCTcpmTcpciGetByte_WDINT(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg)
{
    BYTE pucTcpciData[1] = {0xFF};

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _ENABLE) == _FAIL)
    {
        return pucTcpciData[0];
    }

    // 2. Read TCPC Data by TCPM HW IIC
    ScalerTypeCTcpmHwIICRead_WDINT(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 1, pucTcpciData);

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _DISABLE);
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    enumReg = enumReg;
    ucPortIndex = ucPortIndex;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

    return pucTcpciData[0];
}

//--------------------------------------------------
// Description  : Type C TCPM Set TCPCI Byte Register (for 1-Byte Reg)
// Input Value  : ucPortIndex, enumReg, ucData
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmTcpciSetByte_WDINT(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, BYTE ucData)
{
    BYTE pucTcpciData[1];

    pucTcpciData[0] = ucData;

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _ENABLE) == _FAIL)
    {
        return;
    }

    // 2. Write TCPC Data by TCPM HW IIC
    ScalerTypeCTcpmHwIICWrite_WDINT(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 1, pucTcpciData);

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _DISABLE);
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    enumReg = enumReg;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Type C TCPM Get TCPCI Word Register (for 2-Byte Reg)
// Input Value  : ucPortIndex, enumReg
// Output Value : pucTcpciData (2-Byte)
//--------------------------------------------------
WORD ScalerTypeCTcpmTcpciGetWord_WDINT(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg)
{
    BYTE pucTcpciData[2] = {0xFF, 0xFF};

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _ENABLE) == _FAIL)
    {
        return TO_WORD(pucTcpciData[1], pucTcpciData[0]);
    }

    // 2. Read TCPC Data by TCPM HW IIC
    ScalerTypeCTcpmHwIICRead_WDINT(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 2, pucTcpciData);

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _DISABLE);
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    enumReg = enumReg;
    ucPortIndex = ucPortIndex;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

    return TO_WORD(pucTcpciData[1], pucTcpciData[0]);
}

//--------------------------------------------------
// Description  : Type C TCPM Set TCPCI Word Register (for 2-Byte Reg)
// Input Value  : ucPortIndex, enumReg, usData
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmTcpciSetWord_WDINT(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, WORD usData)
{
    BYTE pucTcpciData[2];

    pucTcpciData[0] = (BYTE)(usData);
    pucTcpciData[1] = (BYTE)(usData >> 8);

    // --------------------------------------------------------------
    // NOTE : TCPC will not Write Register if TCPM intends to Write Data to Reserved Field (Bit) in Certain Register
    // --------------------------------------------------------------

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _ENABLE) == _FAIL)
    {
        return;
    }

    // 2. Write TCPC Data by TCPM HW IIC
    ScalerTypeCTcpmHwIICWrite_WDINT(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 2, pucTcpciData);

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _DISABLE);
#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    enumReg = enumReg;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Type C TCPM Set TCPCI Tx Buffer
// Input Value  : ucPortIndex, enumPdCmd, ucTxByteCnt, usMessageHeader
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmTcpciSetTxBuffer_WDINT(BYTE ucPortIndex, EnumTypeCPDCmd enumPdCmd, BYTE ucTxByteCnt, WORD usMessageHeader)
{
#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_TX_AUTO_CTRL == _ON)

    // 1. Set Write Byte Cnt
    ScalerSetByte_WDINT(PFA_50_TCPC_0_TX_BUFFER_0 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ucTxByteCnt);

    // 2. Re-arrange Data for TCPCI Tx Buffer
    // 2-1. Set Message Header (L, H)
    ScalerSetByte_WDINT(PFA_51_TCPC_0_TX_BUFFER_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)usMessageHeader);
    ScalerSetByte_WDINT(PFA_52_TCPC_0_TX_BUFFER_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usMessageHeader >> 8));

    // 2-2. Set Data Object (Data Obj_0 [7:0], Data Obj_0 [15:8], Data Obj_0 [23:16], Data Obj_0 [31:24])
    if((enumPdCmd & (_BIT7 | _BIT6)) == _PD_CMD_TYPE_DATA)
    {
        // ucTxBuffer[3] = Data Obj_0 [7:0]
        // ucTxBuffer[4] = Data Obj_0 [15:8]
        // ucTxBuffer[5] = Data Obj_0 [23:16]
        // ucTxBuffer[6] = Data Obj_0 [31:24]
        for(BYTE ucLoopIndex = 0; ucLoopIndex < ((ucTxByteCnt - 2) / 4); ucLoopIndex++)
        {
            ScalerSetByte_WDINT(PFA_53_TCPC_0_TX_BUFFER_3 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (ucLoopIndex * 4), g_pucTypeCTcpmPdDataObj_EXINT[3 + (ucLoopIndex * 4)]);
            ScalerSetByte_WDINT(PFA_54_TCPC_0_TX_BUFFER_4 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (ucLoopIndex * 4), g_pucTypeCTcpmPdDataObj_EXINT[2 + (ucLoopIndex * 4)]);
            ScalerSetByte_WDINT(PFA_55_TCPC_0_TX_BUFFER_5 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (ucLoopIndex * 4), g_pucTypeCTcpmPdDataObj_EXINT[1 + (ucLoopIndex * 4)]);
            ScalerSetByte_WDINT(PFA_56_TCPC_0_TX_BUFFER_6 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (ucLoopIndex * 4), g_pucTypeCTcpmPdDataObj_EXINT[0 + (ucLoopIndex * 4)]);
        }
    }
    else if((enumPdCmd & (_BIT7 | _BIT6)) == _PD_CMD_TYPE_EXT)
    {
        // ucTxBuffer[3] = Ext Message Header [7:0]
        // ucTxBuffer[4] = Ext Message Header [15:8]
        ScalerSetByte_WDINT(PFA_53_TCPC_0_TX_BUFFER_3 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), g_pucTypeCTcpmPdDataObj_EXINT[1]);
        ScalerSetByte_WDINT(PFA_54_TCPC_0_TX_BUFFER_4 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), g_pucTypeCTcpmPdDataObj_EXINT[0]);

        // ucTxBuffer[5] = Data Block_0
        // ucTxBuffer[6] = Data Block_1
        for(BYTE ucLoopIndex = 0; ucLoopIndex < (ucTxByteCnt - 4); ucLoopIndex++)
        {
            ScalerSetByte_WDINT(PFA_55_TCPC_0_TX_BUFFER_5 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + ucLoopIndex, g_pucTypeCTcpmPdDataObj_EXINT[2 + ucLoopIndex]);
        }
    }

    // 3. Set Tx Length [0xFA42] [4:0] tcpc_0_tx_len
    ScalerSetBit_WDINT(PFA_42_TCPC_0_TRANSMIT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucTxByteCnt);

#else

    BYTE pucTxBuffer[_MAX_DATA_OBJ_CNT * 4];

    // 1. Set Write Byte Cnt
    pucTxBuffer[0] = ucTxByteCnt;

    // 2. Re-arrange Data for TCPCI Tx Buffer
    // 2-1. Set Message Header (L, H)
    pucTxBuffer[1] = (BYTE)usMessageHeader;
    pucTxBuffer[2] = (BYTE)(usMessageHeader >> 8);

    // 2-2. Set Data Object (Data Obj_0 [7:0], Data Obj_0 [15:8], Data Obj_0 [23:16], Data Obj_0 [31:24])
    if((enumPdCmd & (_BIT7 | _BIT6)) == _PD_CMD_TYPE_DATA)
    {
        // ucTxBuffer[3] = Data Obj_0 [7:0]
        // ucTxBuffer[4] = Data Obj_0 [15:8]
        // ucTxBuffer[5] = Data Obj_0 [23:16]
        // ucTxBuffer[6] = Data Obj_0 [31:24]
        for(BYTE ucLoopIndex = 0; ucLoopIndex < ((ucTxByteCnt - 2) / 4); ucLoopIndex++)
        {
            pucTxBuffer[3 + (ucLoopIndex * 4)] = g_pucTypeCTcpmPdDataObj_EXINT[3 + (ucLoopIndex * 4)];
            pucTxBuffer[4 + (ucLoopIndex * 4)] = g_pucTypeCTcpmPdDataObj_EXINT[2 + (ucLoopIndex * 4)];
            pucTxBuffer[5 + (ucLoopIndex * 4)] = g_pucTypeCTcpmPdDataObj_EXINT[1 + (ucLoopIndex * 4)];
            pucTxBuffer[6 + (ucLoopIndex * 4)] = g_pucTypeCTcpmPdDataObj_EXINT[0 + (ucLoopIndex * 4)];
        }
    }
    else if((enumPdCmd & (_BIT7 | _BIT6)) == _PD_CMD_TYPE_EXT)
    {
        // ucTxBuffer[3] = Ext Message Header [7:0]
        // ucTxBuffer[4] = Ext Message Header [15:8]
        pucTxBuffer[3] = g_pucTypeCTcpmPdDataObj_EXINT[1];
        pucTxBuffer[4] = g_pucTypeCTcpmPdDataObj_EXINT[0];

        // ucTxBuffer[5] = Data Block_0
        // ucTxBuffer[6] = Data Block_1
        for(BYTE ucLoopIndex = 0; ucLoopIndex < (ucTxByteCnt - 4); ucLoopIndex++)
        {
            pucTxBuffer[5 + ucLoopIndex] = g_pucTypeCTcpmPdDataObj_EXINT[2 + ucLoopIndex];
        }
    }

    // 3. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _ENABLE) == _FAIL)
    {
        return;
    }

    // 4. Write TCPC Data by TCPM HW IIC
    ScalerTypeCTcpmHwIICWrite_WDINT(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)_TCPM_TCPCI_REG_TX_BUF, ucTxByteCnt + 1, (BYTE *)(&pucTxBuffer[0]));

    // 5. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _DISABLE);

#endif // End of #if(_HW_TCPM_TX_AUTO_CTRL == _ON)

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    enumPdCmd = enumPdCmd;
    ucTxByteCnt = ucTxByteCnt;
    usMessageHeader = usMessageHeader;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Type C TCPM Set TCPCI Transmit
// Input Value  : ucPortIndex, ucTransmitInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmTcpciSetTransmit_WDINT(BYTE ucPortIndex, BYTE ucTransmitInfo)
{
#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_TX_AUTO_CTRL == _ON)

    // 1. Set Transmit
    ScalerSetByte_WDINT(PFA_6F_TCPC_0_TRANSMIT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ucTransmitInfo);

    // 2. Start Transmit Tx Buffer + Transmit (Do Not Need to Enable tcpc_0_auto_tx_irq_en)
    // [0xFA42] [7] tcpc_0_auto_tx_en, [6] tcpc_0_auto_tx_irq, [5] tcpc_0_auto_tx_irq_en
    ScalerSetBit_WDINT(PFA_42_TCPC_0_TRANSMIT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

#else

    // 1. Set Transmit
    ScalerTypeCTcpmTcpciSetByte_WDINT(ucPortIndex, _TCPM_TCPCI_REG_TRANSMIT, ucTransmitInfo);

#endif // End of #if(_HW_TCPM_TX_AUTO_CTRL == _ON)

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    ucTransmitInfo = ucTransmitInfo;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

#if(_HW_TCPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by TCPM IIC
// Input Value  : ucPortIndex, ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucReadArray
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmHwIICRead_WDINT(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray)
{
    BYTE ucI = 0;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _HW_TCPM_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            ScalerSetBit_WDINT(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), 0x00);

            // Set no repeat start
            ScalerSetBit_WDINT(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _READ));

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit_WDINT(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit_WDINT(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _WRITE));

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _READ));

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit_WDINT(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit_WDINT(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _WRITE));

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _READ));

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucDataLength - 1) << 1));

    // IIC command Start
    ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT6, _BIT6);

    // Wait until Master Receive Complete
    if(ScalerTimerPollingFlagProc_WDINT(4, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT1, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_WDINT(2, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = ScalerGetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex));
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetByte_WDINT(PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucPortIndex, ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucWriteArray
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmHwIICWrite_WDINT(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray)
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    // Return fail if Data to be transmitted is greater than IIC buffer size
    // Max Data Length = Buffer Size - Slave Addr Length (1 Byte) - Sub Addr Length (ucSubAddrLength)
    if(ucDataLength > (_HW_TCPM_IIC_BUFFER_SIZE - 1 - ucSubAddrLength))
    {
        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit_WDINT(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit_WDINT(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_WDINT(2, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _WRITE));

    ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00)

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((ucDataLength - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (ucDataLength << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((ucDataLength + 1) << 1);

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        ScalerSetByte_WDINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), pucWriteArray[ucI]);
    }

    // Send IIC command Start
    ScalerSetByte_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (0xC0 + ucTempLength));

    // Wait until Master Transmit Complete
    if(ScalerTimerPollingFlagProc_WDINT(4, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT0, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_WDINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Clear all flags
    ScalerSetByte_WDINT(PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Enable/Disable TCPM Alert Detect
// Input Value  : ucPortIndex, bAction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmAlertDetCtrl_WDINT(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ENABLE)
    {
        // 1. If alert_det_en = 0, Polling alert_status = 1 before Enable alert_det_en
        if(ScalerGetBit_WDINT(PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), _BIT7) == 0x00)
        {
            // Polling [0xFA20] [4] alert_status = 1 (Alert High)
            if(ScalerTimerPollingFlagProc_WDINT(1, (PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex)), _BIT0, _TRUE) == _FALSE)
            {
                return;
            }
        }

        // Set [0xFA20] [7] alert_det_en = 1 & [3:1] alert_det_deb = b000
        ScalerSetBit_WDINT(PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT3 | _BIT2 | _BIT1), _BIT7);
    }
    else
    {
        // 1. Set FW Busy Flag
        if(ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _ENABLE) == _FAIL)
        {
            return;
        }

        // 2. Disable [0xFA20] [7] alert_det_en
        ScalerSetBit_WDINT(PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // 3. Clear FW Busy Flag
        ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _DISABLE);
    }
}

//--------------------------------------------------
// Description  : Type C TCPM FW Busy Flag Control
// Input Value  : ucPortIndex, bAction
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmFwBusyCtrl_WDINT(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ENABLE)
    {
        // Polling [0xFA11] [4] hw_i2c_busy = 0
        if(ScalerTimerPollingFlagProc_WDINT(2, (PFA_11_TCPM_BUSY + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT4, _FALSE) == _FALSE)
        {
            return _FAIL;
        }

        // Set [0xFA11] [5] fw_i2c_busy to Prevent Interruptions from Exint & WDINT
        ScalerSetBit_WDINT(PFA_11_TCPM_BUSY + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT5, _BIT5);

        return _SUCCESS;
    }
    else
    {
        // Clear [0xFA11] [5] fw_i2c_busy
        ScalerSetBit_WDINT(PFA_11_TCPM_BUSY + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT5, 0x00);

        return _SUCCESS;
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Clear Alert INT
// Input Value  : ucPortIndex, usAlertType, b1Action
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmAlertIntControl_WDINT(BYTE ucPortIndex, WORD usAlertType, bit b1Action)
{
    if((usAlertType & _TCPM_TCPCI_ALERT_CC_STATUS) == _TCPM_TCPCI_ALERT_CC_STATUS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable CC Status IRQ : [0xFA32] [1] alert_cs_irq, [0] alert_cs_irq_en
            ScalerSetBit_WDINT(PFA_32_TCPC_0_CS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable CC Status IRQ : [0xFA32] [1] alert_cs_irq, [0] alert_cs_irq_en
            ScalerSetBit_WDINT(PFA_32_TCPC_0_CS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_PWR_STATUS) == _TCPM_TCPCI_ALERT_PWR_STATUS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Power Status IRQ : [0xFA34] [1] alert_ps_irq, [0] alert_ps_irq_en
            ScalerSetBit_WDINT(PFA_34_TCPC_0_PS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Power Status IRQ : [0xFA34] [1] alert_ps_irq, [0] alert_ps_irq_en
            ScalerSetBit_WDINT(PFA_34_TCPC_0_PS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_FAULT) == _TCPM_TCPCI_ALERT_FAULT)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Fault Status IRQ : [0xFA36] [1] alert_fault_irq, [0] alert_fault_irq_en
            ScalerSetBit_WDINT(PFA_36_TCPC_0_FS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Fault Status IRQ : [0xFA36] [1] alert_fault_irq, [0] alert_fault_irq_en
            ScalerSetBit_WDINT(PFA_36_TCPC_0_FS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_EXT_STATUS) == _TCPM_TCPCI_ALERT_EXT_STATUS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Extended Status IRQ : [0xFA38] [1] alert_ext_stat_irq, [0] alert_ext_stat_irq_en
            ScalerSetBit_WDINT(PFA_38_TCPC_0_ES_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Extended Status IRQ : [0xFA38] [1] alert_ext_stat_irq, [0] alert_ext_stat_irq_en
            ScalerSetBit_WDINT(PFA_38_TCPC_0_ES_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_ALERT_EXT) == _TCPM_TCPCI_ALERT_ALERT_EXT)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Alert Extended IRQ : [0xFA3A] [1] alert_alert_ext_irq, [0] alert_alert_ext_irq_en
            ScalerSetBit_WDINT(PFA_3A_TCPC_0_ALERT_EXT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Alert Extended IRQ : [0xFA3A] [1] alert_alert_ext_irq, [0] alert_alert_ext_irq_en
            ScalerSetBit_WDINT(PFA_3A_TCPC_0_ALERT_EXT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_VENDOR_DEF) == _TCPM_TCPCI_ALERT_VENDOR_DEF)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Vendor Define IRQ : [0xFA3C] [1] alert_vendor_def_irq, [0] alert_vendor_def_irq_en
            ScalerSetBit_WDINT(PFA_3C_TCPC_0_VENDOR_DEF_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Vendor Define IRQ : [0xFA3C] [1] alert_vendor_def_irq, [0] alert_vendor_def_irq_en
            ScalerSetBit_WDINT(PFA_3C_TCPC_0_VENDOR_DEF_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_VBUS_ALRM_H) == _TCPM_TCPCI_ALERT_VBUS_ALRM_H)
    {
        if(b1Action == _ENABLE)
        {
            // Enable High-Voltage Alarm IRQ : [0xFA3F] [1] alert_valm_h_irq, [0] alert_valm_h_irq_en
            ScalerSetBit_WDINT(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable High-Voltage Alarm IRQ : [0xFA3F] [1] alert_valm_h_irq, [0] alert_valm_h_irq_en
            ScalerSetBit_WDINT(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_VBUS_ALRM_L) == _TCPM_TCPCI_ALERT_VBUS_ALRM_L)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Low-Voltage Alarm IRQ : [0xFA3F] [3] alert_valm_l_irq, [2] alert_valm_l_irq_en
            ScalerSetBit_WDINT(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Low-Voltage Alarm IRQ : [0xFA3F] [3] alert_valm_l_irq, [2] alert_valm_l_irq_en
            ScalerSetBit_WDINT(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_RCV_SOP) == _TCPM_TCPCI_ALERT_RX_RCV_SOP)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Rx Msg IRQ : [0xFA48] [3] alert_rx_msg_irq, [2] alert_rx_msg_irq_en
            ScalerSetBit_WDINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Rx Msg IRQ : [0xFA48] [3] alert_rx_msg_irq, [2] alert_rx_msg_irq_en
            ScalerSetBit_WDINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_SOP_BEGIN) == _TCPM_TCPCI_ALERT_RX_SOP_BEGIN)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Rx Bgn IRQ : [0xFA48] [1] alert_rx_bgn_irq, [0] alert_rx_bgn_irq_en
            ScalerSetBit_WDINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Rx Bgn IRQ : [0xFA48] [1] alert_rx_bgn_irq, [0] alert_rx_bgn_irq_en
            ScalerSetBit_WDINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_HRST) == _TCPM_TCPCI_ALERT_RX_HRST)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Hard Reset IRQ : [0xFA43] [7] alert_hrst_irq, [6] alert_hrst_irq_en
            ScalerSetBit_WDINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), (_BIT7 | _BIT6));
        }
        else
        {
            // Disable Hard Reset IRQ : [0xFA43] [7] alert_hrst_irq, [6] alert_hrst_irq_en
            ScalerSetBit_WDINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT7);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_TX_FAIL) == _TCPM_TCPCI_ALERT_TX_FAIL)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Tx Fail IRQ : [0xFA43] [5] alert_tx_fail_irq, [4] alert_tx_fail_irq_en
            ScalerSetBit_WDINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), (_BIT5 | _BIT4));
        }
        else
        {
            // Disable Tx Fail IRQ : [0xFA43] [5] alert_tx_fail_irq, [4] alert_tx_fail_irq_en
            ScalerSetBit_WDINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT5);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_TX_DISCARD) == _TCPM_TCPCI_ALERT_TX_DISCARD)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Tx Discard IRQ : [0xFA43] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit_WDINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Tx Discard IRQ : [0xFA43] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit_WDINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_TX_SUCCESS) == _TCPM_TCPCI_ALERT_TX_SUCCESS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Tx Success IRQ : [0xFA43] [1] alert_tx_discard_irq, [0] alert_tx_discard_irq_en
            ScalerSetBit_WDINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Tx Success IRQ : [0xFA43] [1] alert_tx_discard_irq, [0] alert_tx_discard_irq_en
            ScalerSetBit_WDINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_OVERFLOW) == _TCPM_TCPCI_ALERT_RX_OVERFLOW)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Rx Overflow IRQ : [0xFA44] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit_WDINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Rx Overflow IRQ : [0xFA44] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit_WDINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_SNK_DISC) == _TCPM_TCPCI_ALERT_SNK_DISC)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Sink Disconnect IRQ : [0xFA44] [1] alert_snk_disc_irq, [0] alert_snk_disc_irq_en
            ScalerSetBit_WDINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Sink Disconnect IRQ : [0xFA44] [1] alert_snk_disc_irq, [0] alert_snk_disc_irq_en
            ScalerSetBit_WDINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), _BIT1);
        }
    }
}
#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

#if(_TYPE_C_PMIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by IIC
// Input Value  : enumTypeCPcbPort, ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray
// Output Value : Read result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmPmicIICRead_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex_WDINT(enumTypeCPcbPort);
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;

    if(usLength == 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

#if(_HW_TCPM_SUPPORT == _ON)
        ucDataCnt = _HW_TCPM_IIC_BUFFER_SIZE;

        // Check if more than Max Buffer Size are needed to be received
        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // 1. Set Fw Busy Flag to Prevent Interrupting by HW
        if(ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _ENABLE) == _FAIL)
        {
            return _FAIL;
        }

        // 2. Read PMIC Data by TCPM HW IIC
        if(ScalerTypeCTcpmHwIICRead_WDINT(ucPortIndex, ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray) == _FAIL)
        {
            // 3. Clear Fw Busy Flag
            ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _DISABLE);

            return _FAIL;
        }

        // 3. Clear Fw Busy Flag
        ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _DISABLE);
#else

        // [TO-DO] Dennis : TypeC HW IIC Flow
        ucPortIndex = ucPortIndex;
        pucReadArray = pucReadArray;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by IIC
// Input Value  : enumTypeCPcbPort, ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmPmicIICWrite_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex_WDINT(enumTypeCPcbPort);
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
#if(_HW_TCPM_SUPPORT == _ON)
    BYTE pucTempData[_HW_TCPM_IIC_BUFFER_SIZE + 1];
#endif

    if(usLength == 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

#if(_HW_TCPM_SUPPORT == _ON)
        // Transmit max bytes each time (Buffer Size - Slave Addr Length (1 Byte) - Sub Addr Length (ucSubAddrLength))
        ucDataCnt = _HW_TCPM_IIC_BUFFER_SIZE - 1 - ucSubAddrLength;

        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // 1. Set Fw Busy Flag to Prevent Interrupting by HW
        if(ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _ENABLE) == _FAIL)
        {
            return _FAIL;
        }

        // 2. Write PMIC Data by TCPM HW IIC
        if(ScalerTypeCTcpmHwIICWrite_WDINT(ucPortIndex, ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
        {
            // Clear Fw Busy Flag
            ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _DISABLE);

            return _FAIL;
        }

        // 3. Clear Fw Busy Flag
        ScalerTypeCTcpmFwBusyCtrl_WDINT(ucPortIndex, _DISABLE);
#else

        // [TO-DO] Dennis : TypeC HW IIC Flow
        ucPortIndex = ucPortIndex;
        pucWriteArray = pucWriteArray;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C TCPM PMIC Reset Settings
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPmicReset_WDINT(BYTE ucPortIndex)
{
    EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];

    // ========================================================
    // Reset HW Setting
    // ========================================================
    ExternalDeviceInterfaceTypeCPmicUnattachReset_WDINT(enumTypeCPcbPort);

    // ========================================================
    // Clear Flag and Reset Value
    // ========================================================

    // Reset PMIC Output Type
    SET_TCPM_PMIC_OUTPUT_MODE_STATUS(ucPortIndex, _PD_NONE_SETTING_PDO);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    if(GET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex) == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    {
        SET_TCPM_PMIC_OCP_CURRENT_VALUE(ucPortIndex, 0);
        CLR_TCPM_PMIC_OCP_PROTECT_TRIGGER(ucPortIndex);
    }
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    if(GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON)
    {
        CLR_TCPM_PMIC_GET_OMF_INFO_START(ucPortIndex);
        SET_TCPM_PMIC_OMF_INFO(ucPortIndex, _TYPE_C_PMIC_CV_MODE_OPERATION);
    }
#endif
}

//--------------------------------------------------
// Description  : Control TCPM PMIC to Directed Voltage
// Input Value  : ucPortIndex, bAction, bPowerDirection, enumPdoType, usVoltage(Unit = 10mV), usCurrent(Unit = 10mA), enumPeakCurrent
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmPmicSetting_WDINT(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent)
{
    EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];
    EnumTypeCPmicControlResult enumResult = _TYPE_C_PMIC_CONTROL_FAIL;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    // Avoid Warning
    enumPeakCurrent = enumPeakCurrent;

    // ========================================================
    // CTS Parameter Adjustment
    // ========================================================

    // Minimum Current Setting for different PDO type
    if(enumPdoType == _PD_3_PROGRAMMABLE_PDO)
    {
        usCurrent = MAXOF(usCurrent, _TCPM_PMIC_MIN_PPS_CURRENT);
    }
    else
    {
        usCurrent = MAXOF(usCurrent, _TCPM_PMIC_MIN_CURRENT);
    }

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    if(GET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex) == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    {
        // ========================================================
        // OCP by Polling PMIC's ADC Value Setting Flow
        // ========================================================

        // Clear PMIC OCP Protect Trigger Flag
        CLR_TCPM_PMIC_OCP_PROTECT_TRIGGER(ucPortIndex);

        if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
        {
            // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
            SET_TCPM_PMIC_PROTECT_TIMER_CHECK(ucPortIndex);

            // Set Safety Current Value
            SET_TCPM_PMIC_OCP_CURRENT_VALUE(ucPortIndex, (WORD)(((DWORD)usCurrent * GET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex)) / 100));

            // ====================================================
            // PMIC Current Setting Adjustment
            // ====================================================

            // Add more 66% OCP value in order to avoid triggering the PMIC self OCP
            usCurrent = ((WORD)((((DWORD)usCurrent) * (GET_TCPM_PMIC_FW_OCP_CURRENT_VALUE(ucPortIndex) + 66)) / 100));
        }
    }
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    if(GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON)
    {
        // ====================================================
        // PD 3.0 PPS Support Flow
        // ====================================================
        if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
        {
            SET_TCPM_PMIC_GET_OMF_INFO_START(ucPortIndex);
        }
        else
        {
            CLR_TCPM_PMIC_GET_OMF_INFO_START(ucPortIndex);
        }
    }
#endif

#if(_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON)
    if(GET_TCPM_PMIC_CHECK_SUPPORT(ucPortIndex) == _ON)
    {
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
        // ========================================================
        // PMIC Debug Setting Flow
        // ========================================================
        if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
        {
            // Set Flag to Active PMIC Protection Timer When Vbus Power Stable
            SET_TCPM_PMIC_PROTECT_TIMER_CHECK(ucPortIndex);
        }
#endif

        // ========================================================
        // PMIC Check Support Setting Flow
        // ========================================================
        if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC))
        {
            SET_TCPM_PMIC_OUTPUT_ENABLE(ucPortIndex);
            SET_TCPM_PMIC_BIDIR_MODE(ucPortIndex, _PD_POWER_SRC);
        }
        else
        {
            CLR_TCPM_PMIC_OUTPUT_ENABLE(ucPortIndex);
            SET_TCPM_PMIC_BIDIR_MODE(ucPortIndex, _PD_POWER_SNK);

            // Clear PMIC Protection Timer Check Flag When Turn off Vbus Power
            CLR_TCPM_PMIC_PROTECT_TIMER_CHECK(ucPortIndex);
        }

        CLR_TCPM_PMIC_PROTECT_VALID(ucPortIndex);
    }
#endif

    // ====================================================
    // PMIC Setting Flow
    // ====================================================
    if(bAction == _ON)
    {
        ScalerTypeCTcpmPmicSwitchControl_WDINT(ucPortIndex, _ON, bPowerDirection);

        if(bPowerDirection == _PD_POWER_SRC)
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
        }
        else
        {
            enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
        }

        if(GET_TCPM_PMIC_OUTPUT_MODE_STATUS(ucPortIndex) != enumPdoType)
        {
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            if(GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON)
            {
                if(ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumDirection, enumPdoType) == _TYPE_C_PMIC_CONTROL_FAIL)
                {
                    return _FAIL;
                }
            }
#endif
            SET_TCPM_PMIC_OUTPUT_MODE_STATUS(ucPortIndex, enumPdoType);
        }

        enumResult = ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumDirection, usVoltage, usCurrent);
    }
    else
    {
        // Reset PMIC Output Type
        SET_TCPM_PMIC_OUTPUT_MODE_STATUS(enumPdoType, enumPdoType);

        enumResult = ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT(enumTypeCPcbPort);
    }

    // ====================================================
    // Check PMIC Control Result
    // ====================================================
    if(enumResult == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        // ================================================
        // Update Setting Information
        // ================================================
        SET_TCPM_REQ_PWR(ucPortIndex, (WORD)((DWORD)usVoltage * usCurrent / 1000)); // Calculate Requested Power to Unit = 0.1W
        SET_TCPM_OUTPUT_VOL(ucPortIndex, usVoltage);
        SET_TCPM_OUTPUT_CUR(ucPortIndex, usCurrent);
        SET_TCPM_VBUS_STATUS(ucPortIndex, bAction);

        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Type-C TCPM PMIC VBUS Discharge Control
// Input Value  : ucPortIndex, bEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmPmicVbusDischarge_WDINT(BYTE ucPortIndex, bit bEn)
{
    EnumTypeCPmicDischarge enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;

    if(bEn == _ON)
    {
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_ENABLE;
    }
    else
    {
        ScalerTypeCTcpmPmicSwitchControl_WDINT(ucPortIndex, _OFF, _PD_POWER_SNK);
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;
    }

    if(ExternalDeviceInterfaceTypeCPmicVbusDischarge_WDINT(g_penumTypeCTcpmPort[ucPortIndex], enumDischarge) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : TCPM PMIC Switch Control
// Input Value  : ucPortIndex, bEn, bPowerDirection
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmPmicSwitchControl_WDINT(BYTE ucPortIndex, bit bEn, bit bPowerDirection)
{
    EnumTypeCPmicSwitchControl enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    EnumTypeCPmicDirection enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;

    if(bEn == _ON)
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE;
    }
    else
    {
        enumSwitchControl = _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE;
    }

    if(bPowerDirection == _PD_POWER_SRC)
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SRC;
    }
    else
    {
        enumDirection = _TYPE_C_PMIC_DIRECTION_SNK;
    }


    if(ExternalDeviceInterfaceTypeCPmicSwitchControl_WDINT(g_penumTypeCTcpmPort[ucPortIndex], enumSwitchControl, enumDirection) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}
#endif // End of #if(_TYPE_C_PMIC_SUPPORT == _ON)
#endif // End of #if(_PORT_CTRL_TCPM_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

