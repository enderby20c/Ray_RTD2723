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
// ID Code      : ScalerTypeC0Pd_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeC0Pd/ScalerTypeC0Pd.h"




#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT))
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
// Description  : WD Timer Event Proc of PD RX0
// Input Value  : enumEventID, pucActiveWDID, pucActiveWDTime
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdWDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime)
{
    // Only Run PD WD Timer Event Proc When CC is Attached
    if(GET_TYPE_C_0_CC_ATTACHED() == _FALSE)
    {
        return;
    }

    switch(enumEventID)
    {
        case _SCALER_WD_TIMER_EVENT_PD_0_CBL_TIMEOUT:

            if(GET_TYPE_C_0_PD_FW_STATE() != _PD_HARDRESET)
            {
                ScalerTypeC0PdWDTimerEventCableProc_WDINT(pucActiveWDID, pucActiveWDTime);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_SRC_CAP:

            if(GET_TYPE_C_0_PD_FW_STATE() != _PD_HARDRESET)
            {
#if(_SRC_CAP_NO_RETRY == _TRUE)
                // Do Not Retry Source Capability When Not Rcv. GoodCRC Resp
                ScalerSetBit_EXINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
#else
                // PD Merged Test [TEST.PD.PROT.SRC3.1] : All PD Message Should Implement 0.9~1.1ms Retry
                // Update Retry Counter According to Spec Version
                if(GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_2_0)
                {
                    ScalerSetBit_EXINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
                }
                else
                {
                    ScalerSetBit_EXINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
                }
#endif
                // Send SRC_CAP
                SET_TYPE_C_0_PD_FW_STATE(_PD_SRC_INT_SEND_CAP);
                SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_HARD_RST:
        case _SCALER_WD_TIMER_EVENT_PD_0_SENDER_RESP_TIMEOUT:

            if(GET_TYPE_C_0_PD_FW_STATE() == _PD_SNK_INT_WAIT_SRC_CAP)
            {
                if(GET_TYPE_C_0_PD_WD_TIMER_VALUE() < _SINK_WAIT_CAP_TIMER)
                {
                    if((_SINK_WAIT_CAP_TIMER - GET_TYPE_C_0_PD_WD_TIMER_VALUE()) > _MAX_WD_EVENT_TIME)
                    {
                        *pucActiveWDTime = _MAX_WD_EVENT_TIME;
                        *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_SEND_HARD_RST;

                        SET_TYPE_C_0_PD_WD_TIMER_VALUE(GET_TYPE_C_0_PD_WD_TIMER_VALUE() + _MAX_WD_EVENT_TIME);
                    }
                    else
                    {
                        *pucActiveWDTime = _SINK_WAIT_CAP_TIMER - GET_TYPE_C_0_PD_WD_TIMER_VALUE();
                        *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_SEND_HARD_RST;

                        SET_TYPE_C_0_PD_WD_TIMER_VALUE(_SINK_WAIT_CAP_TIMER);
                    }
                }
                else
                {
#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
                    // Sink does not receive Src_Cap, Set Flag for U3 Function Enable (S4 Only)
                    ScalerUsb3RepeaterMacSetPdNoResponse_WDINT(ScalerTypeCxPcbxMapping_WDINT(_EMB_TYPE_C_0));
#endif

                    // Send Hard Reset
                    ScalerTypeC0PdSendHardRst_WDINT(pucActiveWDID, pucActiveWDTime);
                }
            }
            else
            {
                // Send Hard Reset
                ScalerTypeC0PdSendHardRst_WDINT(pucActiveWDID, pucActiveWDTime);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_PS_TRANSITION_TIMEOUT:

            if(GET_TYPE_C_0_PD_FW_STATE() != _PD_HARDRESET)
            {
                if(GET_TYPE_C_0_PD_WD_TIMER_VALUE() < _PS_TRANSITION_TIMER)
                {
                    if((_PS_TRANSITION_TIMER - GET_TYPE_C_0_PD_WD_TIMER_VALUE()) > _MAX_WD_EVENT_TIME)
                    {
                        *pucActiveWDTime = _MAX_WD_EVENT_TIME;
                        *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_PS_TRANSITION_TIMEOUT;

                        SET_TYPE_C_0_PD_WD_TIMER_VALUE(GET_TYPE_C_0_PD_WD_TIMER_VALUE() + _MAX_WD_EVENT_TIME);
                    }
                    else
                    {
                        *pucActiveWDTime = _PS_TRANSITION_TIMER - GET_TYPE_C_0_PD_WD_TIMER_VALUE();
                        *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_PS_TRANSITION_TIMEOUT;

                        SET_TYPE_C_0_PD_WD_TIMER_VALUE(_PS_TRANSITION_TIMER);
                    }
                }
                else
                {
                    // Send Hard Reset when PSTransitionTimer timeout (450 ~ 550ms)
                    ScalerTypeC0PdSendHardRst_WDINT(pucActiveWDID, pucActiveWDTime);
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_VDM_RESP_TIMEOUT:

            if(GET_TYPE_C_0_PD_FW_STATE() != _PD_HARDRESET)
            {
                switch(GET_TYPE_C_0_PD_DP_ALT_STATE())
                {
                    case _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP:

                        ADD_TYPE_C_0_PD_PARTNER_VDM_NO_RESP_CNT();
                        SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_ID);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP:

                        ADD_TYPE_C_0_PD_PARTNER_VDM_NO_RESP_CNT();
                        SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_SVID);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DISCOVER_MODE_RESP:

                        ADD_TYPE_C_0_PD_PARTNER_VDM_NO_RESP_CNT();
                        SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_MODE);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP:

                        ADD_TYPE_C_0_PD_PARTNER_VDM_NO_RESP_CNT();
                        SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP:

                        ADD_TYPE_C_0_PD_PARTNER_VDM_NO_RESP_CNT();
                        SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DP_STATUS_RESP:

                        SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ATTENTION);

                        break;

                    case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP:

                        ADD_TYPE_C_0_PD_PARTNER_VDM_NO_RESP_CNT();
                        SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);

                        break;

                    case _PD_ALT_MODE_READY:

                        if(GET_TYPE_C_0_PD_FORCE_HPD_IRQ() == _TRUE)
                        {
                            CLR_TYPE_C_0_PD_FORCE_HPD_IRQ();

                            // Push HPD_IRQ into HPD Queue When not Received DP Status ACK during Force Sending HPD IRQ Process, then PD will Re-Send HPD_IRQ in Main loop
                            ScalerTypeC0PdPushHpd_WDINT(_PD_HPD_IRQ, 0);
                        }

                        break;

                    default:

                        break;
                }

                SET_TYPE_C_0_PD_VDMMSG_WAIT_FLAG();

                // Set AMS = None
                SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeC0PdBackToReadyState_WDINT();
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_SRC_TURN_ON_POWER:

            if(GET_TYPE_C_0_PD_FW_STATE() != _PD_HARDRESET)
            {
#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
                // Control PMIC to Turn On Vbus Power
                ScalerTypeC0PmicSetting_WDINT(_ON, _PD_POWER_SRC, GET_TYPE_C_0_PD_SRC_PDO_TYPE(GET_TYPE_C_0_PD_PARTNER_OBJ_POS() - 1), GET_TYPE_C_0_PD_PARTNER_REQ_VOL(), GET_TYPE_C_0_OCP_CURRENT(), GET_TYPE_C_0_PD_SRC_CAP_PEAK(GET_TYPE_C_0_PD_PARTNER_OBJ_POS() - 1));
#endif
                // Update PDO Status
                SET_TYPE_C_0_PD_PDO_STATUS_VOL(GET_TYPE_C_0_PD_PARTNER_REQ_VOL());
                SET_TYPE_C_0_PD_PDO_STATUS_CUR(GET_TYPE_C_0_PD_PARTNER_MAX_CUR());
                SET_TYPE_C_0_PD_PDO_STATUS_OBJ_POS(GET_TYPE_C_0_PD_PARTNER_OBJ_POS());

#if(_EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
                if(GET_TYPE_C_0_PD_PDO_STATUS_VOL() > 500)
                {
                    // Tool Show Warning UI when We Provide Vbus > 5V
                    ScalerTypeC0CcToolWarningUIControl_WDINT(_ENABLE);
                }
                else
                {
                    // Tool Not Show Warning UI when We Provide Vbus <= 5V
                    ScalerTypeC0CcToolWarningUIControl_WDINT(_DISABLE);
                }
#endif

                // State Transition
                SET_TYPE_C_0_PD_FW_STATE(_PD_SRC_WDINT_SEND_PSRDY);

                // Active WD Timer to Check Vbus, Then Start PMIC Protection and Send PS_RDY if Vbus Ready
                *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_CHECK_VBUS;

                if(GET_TYPE_C_0_PD_EPR_MODE() == _TRUE)
                {
                    if(GET_TYPE_C_0_PD_REQ_AVS_VOL_SMALL_STEP() != _TRUE)
                    {
                        *pucActiveWDTime = _SRC_SEND_PS_RDY_EPR_FIX_VOLTAGE_TIMER;
                    }
                    else
                    {
                        *pucActiveWDTime = _SRC_SEND_PS_RDY_EPR_AVS_MODE_TIMER;
                    }
                }
                else
                {
                    if(GET_TYPE_C_0_PD_REQ_PPS_VOL_SMALL_STEP() != _TRUE)
                    {
#if(_TYPE_C_EIZO_CUSTOMIZED_VBUS_CHECK_TIMER_SUPPORT == _ON)
                        *pucActiveWDTime = 28;
#else
                        *pucActiveWDTime = _SRC_SEND_PS_RDY_FIX_VOLTAGE_TIMER;
#endif
                    }
                    else
                    {
                        *pucActiveWDTime = _SRC_SEND_PS_RDY_PPS_MODE_TIMER;
                    }
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_CHECK_VBUS:

            if(GET_TYPE_C_0_PD_FW_STATE() == _PD_WDINT_SEND_CBL_DISCOVER_ID)
            {
                ADD_TYPE_C_0_PD_CHECK_VBUS_CNT();

                if((ScalerTypeCAdcCheckVbusReady_WDINT(_EMB_TYPE_C_0, 500) == _TRUE) || (GET_TYPE_C_0_PD_CHECK_VBUS_CNT() >= 8))
                {
                    ScalerSetBit_EXINT(P65_19_PD_DUMMY_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_TYPE_C_0_PD_CHECK_VBUS_CNT());

                    // Reset Check Vbus Counter
                    CLR_TYPE_C_0_PD_CHECK_VBUS_CNT();

                    // Send Discover_ID_REQ When Vbus Check Pass.
                    ScalerTypeC0PdWDTimerEventCableProc_WDINT(pucActiveWDID, pucActiveWDTime);
                }
                else
                {
                    // Active WD Timer to Check Vbus
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_CHECK_VBUS;
                    *pucActiveWDTime = 10;
                }
            }
            else if(GET_TYPE_C_0_PD_FW_STATE() == _PD_SRC_WDINT_SEND_CAP)
            {
                ADD_TYPE_C_0_PD_CHECK_VBUS_CNT();

                if((ScalerTypeCAdcCheckVbusReady_WDINT(_EMB_TYPE_C_0, 500) == _TRUE) || (GET_TYPE_C_0_PD_CHECK_VBUS_CNT() >= 8))
                {
                    ScalerSetBit_EXINT(P65_19_PD_DUMMY_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_TYPE_C_0_PD_CHECK_VBUS_CNT());

                    // Reset Check Vbus Counter
                    CLR_TYPE_C_0_PD_CHECK_VBUS_CNT();

#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_0_PMIC_CHECK_SUPPORT == _ON))
                    // Start PMIC Protection
                    ScalerTypeC0PmicProtectStart_WDINT(_TYPE_C_POWER_SRC);
#endif

#if(_SRC_CAP_NO_RETRY == _TRUE)
                    // Do Not Retry Source Capability When Not Rcv. GoodCRC Resp
                    ScalerSetBit_EXINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
#else
                    // PD Merged Test [TEST.PD.PROT.SRC3.1] : All PD Message Should Implement 0.9~1.1ms Retry
                    // Update Retry Counter According to Spec Version
                    if(GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_2_0)
                    {
                        ScalerSetBit_EXINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
                    }
                    else
                    {
                        ScalerSetBit_EXINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
                    }
#endif
                    // Send SRC_CAP
                    SET_TYPE_C_0_PD_FW_STATE(_PD_SRC_INT_SEND_CAP);
                    SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                    ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Active WD Timer to Check Vbus
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_CHECK_VBUS;
                    *pucActiveWDTime = 30;
                }
            }
            else if(GET_TYPE_C_0_PD_FW_STATE() == _PD_SRC_WDINT_SEND_PSRDY)
            {
                ADD_TYPE_C_0_PD_CHECK_VBUS_CNT();

#if(_TYPE_C_EIZO_CUSTOMIZED_VBUS_CHECK_TIMER_SUPPORT == _ON)
                if((ScalerTypeCAdcCheckVbusReady_WDINT(_EMB_TYPE_C_0, GET_TYPE_C_0_PD_PDO_STATUS_VOL()) == _TRUE) || (GET_TYPE_C_0_PD_CHECK_VBUS_CNT() >= 10))
#else
                if((ScalerTypeCAdcCheckVbusReady_WDINT(_EMB_TYPE_C_0, GET_TYPE_C_0_PD_PDO_STATUS_VOL()) == _TRUE) || (GET_TYPE_C_0_PD_CHECK_VBUS_CNT() >= 8))
#endif
                {
                    ScalerSetBit_EXINT(P65_19_PD_DUMMY_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_TYPE_C_0_PD_CHECK_VBUS_CNT());

                    // Reset Check Vbus Counter
                    CLR_TYPE_C_0_PD_CHECK_VBUS_CNT();

#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_0_PMIC_CHECK_SUPPORT == _ON))
                    // Start PMIC Protection
                    ScalerTypeC0PmicProtectStart_WDINT(_TYPE_C_POWER_SRC);
#endif

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
                    // [Eizo] SIC437A Customized Power Control : PD as SRC Send PS_RDY During Power Transition
                    ScalerTypeC0PmicSic437aTransitionReadyProc_WDINT();
#endif

                    // Send "PS_RDY" After Accept to Request and Ready to Provide New Negotiated Power Level
                    SET_TYPE_C_0_PD_FW_STATE(_PD_SRC_INT_SEND_PSRDY);
                    SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_HARD_RESET);
                    ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Active WD Timer to Check Vbus
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_CHECK_VBUS;

                    if(GET_TYPE_C_0_PD_EPR_MODE() == _TRUE)
                    {
                        if(GET_TYPE_C_0_PD_REQ_AVS_VOL_SMALL_STEP() != _TRUE)
                        {
                            *pucActiveWDTime = _SRC_SEND_PS_RDY_EPR_FIX_VOLTAGE_TIMER;
                        }
                        else
                        {
                            *pucActiveWDTime = _SRC_SEND_PS_RDY_EPR_AVS_MODE_TIMER;
                        }
                    }
                    else
                    {
                        if(GET_TYPE_C_0_PD_REQ_PPS_VOL_SMALL_STEP() != _TRUE)
                        {
#if(_TYPE_C_EIZO_CUSTOMIZED_VBUS_CHECK_TIMER_SUPPORT == _ON)
                            *pucActiveWDTime = 28;
#else
                            *pucActiveWDTime = _SRC_SEND_PS_RDY_FIX_VOLTAGE_TIMER;
#endif
                        }
                        else
                        {
                            *pucActiveWDTime = _SRC_SEND_PS_RDY_PPS_MODE_TIMER;
                        }
                    }
                }
            }
            else if((GET_TYPE_C_0_PD_FW_STATE() == _PD_SNK_READY) && (GET_TYPE_C_0_PD_SUB_STATE() == _PD_SUB_WDINT_SEND_SRC_ON_PSRDY))
            {
                ADD_TYPE_C_0_PD_CHECK_VBUS_CNT();

                if((ScalerTypeCAdcCheckVbusReady_WDINT(_EMB_TYPE_C_0, 500) == _TRUE) || (GET_TYPE_C_0_PD_CHECK_VBUS_CNT() >= 8))
                {
                    ScalerSetBit_EXINT(P65_19_PD_DUMMY_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), GET_TYPE_C_0_PD_CHECK_VBUS_CNT());

                    // Reset Check Vbus Counter
                    CLR_TYPE_C_0_PD_CHECK_VBUS_CNT();

#if((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_0_PMIC_CHECK_SUPPORT == _ON))
                    // Start PMIC Protection
                    ScalerTypeC0PmicProtectStart_WDINT(_TYPE_C_POWER_SRC);
#endif

                    // PD 2.0 : Only Source && Vconn Source Can Communicate With Cable When Implicit Contract
                    if((GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_2_0) && (GET_TYPE_C_0_PD_VCONN_ROLE() == _PD_VCONN_SRC))
                    {
                        // [0x6534] Setup Rx Valid Packet Type (Vconn SRC : SOP / SOP' / SOP" / Hard Reset)
                        ScalerSetByte_WDINT(P65_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }

                    // Send "PS_RDY" After PRS to SRC and Vbus Has Been Turned On
                    SET_TYPE_C_0_PD_POWER_ROLE(_PD_POWER_SRC);
                    SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_HARD_RESET);
                    ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Active WD Timer to Check Vbus
                    *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_CHECK_VBUS;
                    *pucActiveWDTime = 35;
                }
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_VCONN_ON_PSRDY:

            if(GET_TYPE_C_0_PD_FW_STATE() != _PD_HARDRESET)
            {
                // Set Vconn Role to Vconn SRC
                SET_TYPE_C_0_PD_VCONN_ROLE(_PD_VCONN_SRC);

                // Reset Discover ID Retry Fail Counter After Vconn_Swap
                CLR_TYPE_C_0_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT();

                // PD 2.0 : Only DFP && Vconn Source Can Communicate With Cable During Explicit Contract
                // PD 3.0 : Only Vconn Source Can Communicate With Cable
                if((GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0) || ((GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_2_0) && (GET_TYPE_C_0_PD_DATA_ROLE() == _PD_DATA_DFP)))
                {
                    // [0x6534] Setup Rx Valid Packet Type (Vconn SRC : SOP / SOP' / SOP" / Hard Reset)
                    ScalerSetByte_WDINT(P65_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                }

                // Send "PS_RDY"
                SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_HARD_RESET);
                ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_SRC_TURN_OFF_POWER:

            // From : 1.SRC Rcv Accpet PRS 2.SRC Send Accept PRS 3.HRST_EXINT 4.HRST_WDINT
#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
            // Adjust Power (Turn Off Vbus)
            ScalerTypeC0PmicSetting_WDINT(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
            // Enable Vbus Discharge
            ScalerTypeC0PmicVbusDischarge_WDINT(_ON);
#endif

#if(_EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
            // Tool Not Show Warning UI when We Turn Off Vbus
            ScalerTypeC0CcToolWarningUIControl_WDINT(_DISABLE);
#endif

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_BACK_TO_READY_STATE:

            if(GET_TYPE_C_0_PD_FW_STATE() != _PD_HARDRESET)
            {
                // Set AMS = None
                SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                // If BIST Carrier Mode, Reset PHY State Machine and Turn Off BIST Mode
                if(GET_TYPE_C_0_PD_SUB_STATE() == _PD_SUB_BIST_MODE)
                {
                    // Reset PHY FSM
                    ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~(_BIT0), 0x00);

                    // Turn Off BIST UUT Carrier Mode
                    ScalerSetBit_EXINT(P65_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

                    // Begin PHY FSM
                    ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~(_BIT0), _BIT0);

                    // Enable Rcv Msg INT
                    ScalerTypeC0PdRxIntControl_WDINT(_ENABLE);
                }
                else if(GET_TYPE_C_0_PD_SUB_STATE() == _PD_SUB_INT_WAIT_VCS_RESP)
                {
                    SET_TYPE_C_0_PD_VCS_REJECT();
                }
                else if(GET_TYPE_C_0_PD_SUB_STATE() == _PD_SUB_INT_WAIT_DRS_RESP)
                {
                    SET_TYPE_C_0_PD_DRS_REJECT();
                }
                else if(GET_TYPE_C_0_PD_SUB_STATE() == _PD_SUB_INT_WAIT_PRS_RESP)
                {
                    SET_TYPE_C_0_PD_PRS_REJECT();
                }

                // Back to Ready State
                ScalerTypeC0PdBackToReadyState_WDINT();
            }

            break;
        /*
        case _SCALER_WD_TIMER_EVENT_PD_0_TURN_OFF_VCONN_BACK_TO_HW_MODE:

            // Switch Back to HW Mode
            ScalerSetBit_EXINT(P66_30_CC_HW_MODE_CTRL, ~(_BIT7 | _BIT6 | _BIT3 | _BIT1), (_BIT7 | _BIT6));

            break;
        */
        case _SCALER_WD_TIMER_EVENT_PD_0_SNK_SWITCH_TO_SRC:

            // TO-DO HengYi : Remove Set Rp to Deafult in PD, Should Be Add in CC Switch Power Role
            // 1. Change Rd -> Rp (Switch to Power SRC)
            ScalerTypeC0CcSwitchPowerRole_WDINT(_PD_POWER_SRC);

            // Set OCP Threshlod
            SET_TYPE_C_0_OCP_CURRENT((WORD)(((DWORD)(GET_TYPE_C_0_CC_DEF_CUR()) * (DWORD)(GET_TYPE_C_0_OCP_RATIO(0))) / 100));

#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
            // 2. Turn On Vbus to vSafe5V (500 * 10mV) / Current = Default Current (10mA)
            ScalerTypeC0PmicSetting_WDINT(_ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, 500, GET_TYPE_C_0_OCP_CURRENT(), _PD_PEAK_CUR_NONE);
#endif

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
            // [Eizo] SIC437A Customized Power Control : Sink Receive PS_RDY When Source Turn Off Vbus in PR Swap
            ScalerTypeC0PmicSic437aPRSwapToSrcProc_WDINT();
#endif

            // 3. Check Vbus 35ms (10ms + 25ms) after Received PS_RDY, Then Start PMIC Protection and Send "PS_RDY" if VbusSafe5V
            SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_WDINT_SEND_SRC_ON_PSRDY);
            *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_CHECK_VBUS;
            *pucActiveWDTime = 25;

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_EPR_ENTER_FAILED:

            if(GET_TYPE_C_0_PD_FW_STATE() != _PD_HARDRESET)
            {
                SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);

                // Send Enter Failed : Source Not Vconn Source
                SET_TYPE_C_0_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                SET_TYPE_C_0_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_NOT_VCONN_SOURCE);
                SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_VCONN_SWAP:

            if(GET_TYPE_C_0_PD_FW_STATE() != _PD_HARDRESET)
            {
                SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_INT_SEND_VCONN_SWAP);
                SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_VCONN_SWAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_CHUNK_SENDER_REQ_TIMEOUT:

            if(GET_TYPE_C_0_PD_FW_STATE() != _PD_HARDRESET)
            {
                SET_TYPE_C_0_PD_FW_STATE(_PD_INT_SEND_SOFTRESET);
                SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_STATE_NONE);
                SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_HARD_RESET);
                ScalerTypeC0PdSendSoftRst_WDINT(_PD_SOP_PKT);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_SEND_EPR_SRC_CAP:

            if(GET_TYPE_C_0_PD_FW_STATE() != _PD_HARDRESET)
            {
                // Send EPR Source Cap
                CLR_TYPE_C_0_PD_TX_CHUNK_NUMBER();
                SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_SRC_CAP);
                SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_EPR_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_TX_AVALIABLE:

            switch(GET_TYPE_C_0_PD_SUB_STATE())
            {
                case _PD_SUB_SEND_DP_VDM_REQ:

                    if(GET_TYPE_C_0_PD_FORCE_HPD_IRQ() == _TRUE)
                    {
                        if(GET_TYPE_C_0_PD_DATA_ROLE() == _PD_DATA_UFP)
                        {
                            SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ATTENTION);

                            SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                            // Send "Attention REQ"
                            ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);
                        }
                        else
                        {
                            SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                            // Send "DP Status REQ"
                            ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_10);
                        }
                    }

                    break;

                default:

                    break;
            }

            break;

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
        case _SCALER_WD_TIMER_EVENT_PD_0_DELL_AM_ENTER_TIMEOUT:

            SET_TYPE_C_0_PD_DELL_AM_ENTER_TIMEOUT();

            break;

        case _SCALER_WD_TIMER_EVENT_PD_0_DELL_ATTEN_RETRY:

            ADD_TYPE_C_0_PD_DELL_ATTEN_RETRY_CNT();
            CLR_TYPE_C_0_PD_DELL_ATTEN_WAIT();

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For Cable in WD Timer
// Input Value  : enumEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdWDTimerEventCableProc_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime)
{
    switch(GET_TYPE_C_0_PD_FW_STATE())
    {
        case _PD_WDINT_SEND_CBL_DISCOVER_ID:

#if(_DISCOVER_ID_NO_RETRY == _TRUE)
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
            // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp(For RL6829)
            ScalerSetBit_WDINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
#else
            // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp(For RL6952)
            ScalerSetBit_WDINT(P65_ED_TX_PD_CBL_RTY_CNT, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif
#else
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
            // Update Retry Counter According to Cable Spec Version
            ScalerTypeC0PdUpdateCableRetryCounter_WDINT();
#endif
#endif

            // Send Discover ID (SOP') to Get Cable Info
            SET_TYPE_C_0_PD_FW_STATE(_PD_INT_SEND_CBL_DISCOVER_ID);
            SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
            ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);

            break;

        case _PD_INT_WAIT_CBL_DISCOVER_ID_RESP:

            // Sender Response Timer Timeout After Sending Discover ID to Cable
            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

            SET_TYPE_C_0_PD_FW_STATE(_PD_SRC_WDINT_SEND_CAP);
            SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_STATE_NONE);
            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

            // Active WD Timer Event To Check Vbus, Then Start PMIC Protection and Send SRC_CAP if VbusSafe5V
            *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_CHECK_VBUS;
            *pucActiveWDTime = 20;

            break;

        case _PD_WDINT_SEND_CBL_SOFT_RESET:

#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
            // Update Retry Counter According to Cable Spec Version
            ScalerTypeC0PdUpdateCableRetryCounter_WDINT();
#endif
            // Send Soft Reset (SOP') to Reset Cable
            SET_TYPE_C_0_PD_FW_STATE(_PD_INT_SEND_CBL_SOFT_RESET);
            SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
            ScalerTypeC0PdSendSoftRst_WDINT(_PD_SOP_P_PKT);

            break;

        case _PD_INT_WAIT_CBL_SOFT_RESET_RESP:

            // Sender Response Timer Timeout After Sending Soft Reset to Cable
            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

            SET_TYPE_C_0_PD_FW_STATE(_PD_WDINT_SEND_CBL_DISCOVER_ID);
            SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_STATE_NONE);
            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

            // Active WD Timer Event To Send Discover ID(SOP')
            *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_CBL_TIMEOUT;
            *pucActiveWDTime = 10;

            break;

        case _PD_SRC_READY:
        case _PD_SNK_READY:

            switch(GET_TYPE_C_0_PD_SUB_STATE())
            {
                case _PD_SUB_CABLE_PROC:

                    switch(GET_TYPE_C_0_PD_CBL_STATE())
                    {
                        case _PD_CBL_INT_WAIT_SOFT_RST_RESP:

                            // Sender Response Timer Timeout After Sending Soft Reset to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            if(GET_TYPE_C_0_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
                            {
                                SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);
                                SET_TYPE_C_0_PD_CBL_STATE(_PD_CBL_STATE_NONE);

                                // Send Enter Failed : Cable Not Support EPR Mode
                                SET_TYPE_C_0_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                                SET_TYPE_C_0_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_CABLE_NOT_EPR_CAP);
                                SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                                ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                            }
                            else
                            {
                                // Back to Ready State
                                ScalerTypeC0PdBackToReadyState_WDINT();
                                SET_TYPE_C_0_PD_CBL_STATE(_PD_CBL_STATE_NONE);
                                SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);
                            }

                            break;

                        case _PD_CBL_INT_WAIT_DISCOVER_ID_RESP:

                            // Sender Response Timer Timeout After Sending Discover ID to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                            if(GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();
                                SET_TYPE_C_0_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);
                            }

                            if(GET_TYPE_C_0_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
                            {
                                SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);
                                SET_TYPE_C_0_PD_CBL_STATE(_PD_CBL_STATE_NONE);

                                // Send Enter Failed : Cable Not Support EPR Mode
                                SET_TYPE_C_0_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                                SET_TYPE_C_0_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_CABLE_NOT_EPR_CAP);
                                SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                                ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                            }
                            else
                            {
                                // Back to Ready State
                                ScalerTypeC0PdBackToReadyState_WDINT();
                                SET_TYPE_C_0_PD_CBL_STATE(_PD_CBL_STATE_NONE);
                                SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);
                            }

                            break;

                        default:

                            break;
                    }

                    break;

                case _PD_SUB_WDINT_DISCOVER_CABLE:

                    if(GET_TYPE_C_0_PD_CBL_SOFT_RESET_REQUIRED() == _TRUE)
                    {
                        CLR_TYPE_C_0_PD_CBL_SOFT_RESET_REQUIRED();

                        SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_CABLE_PROC);
                        SET_TYPE_C_0_PD_CBL_STATE(_PD_CBL_INT_SEND_SOFT_RST);

#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                        // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                        ScalerTypeC0PdUpdateCableRetryCounter_WDINT();
#endif

                        // Send Soft Reset(SOP') to Reset Cable
                        SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                        ScalerTypeC0PdSendSoftRst_WDINT(_PD_SOP_P_PKT);
                    }
                    else
                    {
                        SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_CABLE_PROC);
                        SET_TYPE_C_0_PD_CBL_STATE(_PD_CBL_INT_SEND_DISCOVER_ID);

#if(_DISCOVER_ID_NO_RETRY == _TRUE)
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                        // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp(For RL6829)
                        ScalerSetBit_WDINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
#else
                        // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp(For RL6952)
                        ScalerSetBit_WDINT(P65_ED_TX_PD_CBL_RTY_CNT, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif
#else
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                        // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                        ScalerTypeC0PdUpdateCableRetryCounter_WDINT();
#endif
#endif

                        // Send Discover ID (SOP') to Get Cable Info
                        SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                        ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);
                    }

                    break;

#if((_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))
                case _PD_SUB_INT_WAIT_VDM_RESP:

                    switch(GET_TYPE_C_0_PD_DP_ALT_STATE())
                    {
                        case _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Discover ID to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                            if(GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();
                                SET_TYPE_C_0_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);

                                // If No VDO Received, Set Passive Cable & HBR3 According to DPAM2.1
                                SET_TYPE_C_0_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_PASSIVE);
                                SET_TYPE_C_0_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_HBR3);

                                // Stop Enter DP Alt Mode Flow Just for Cable
                                CLR_TYPE_C_0_PD_CBL_ENTER_DP_MODE_SUPPORT();
                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else
                            {
                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeC0PdBackToReadyState_WDINT();
                            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Discover SVID to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                            if(GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No Response of Discover Svid(SOP' / SOP'') Received
                                SET_TYPE_C_0_PD_DP_ALT_STATE(ScalerTypeC0PdJudgeCableDpFunctionality_WDINT());
                            }
                            else
                            {
                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeC0PdBackToReadyState_WDINT();
                            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_DISCOVER_MODE_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Discover DP Mode to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                            if(GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No Response of DP Discover Mode(SOP' / SOP'') Received
                                SET_TYPE_C_0_PD_DP_ALT_STATE(ScalerTypeC0PdJudgeCableDpFunctionality_WDINT());
                            }
                            else
                            {
                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeC0PdBackToReadyState_WDINT();
                            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_TBT3_DISCOVER_MODE_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Discover TBT3 Mode to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                            if(GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No Response of TBT3 Discover Mode(SOP' / SOP'') Received
                                SET_TYPE_C_0_PD_DP_ALT_STATE(ScalerTypeC0PdJudgeCableDpFunctionality_WDINT());
                            }
                            else
                            {
                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeC0PdBackToReadyState_WDINT();
                            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Enter DP Mode to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                            if(GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else
                            {
                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeC0PdBackToReadyState_WDINT();
                            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_PP:

                            // Sender Response Timer Timeout After Sending Enter DP Mode to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                            if(GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else
                            {
                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP);
                            }

                            // Back to Ready State
                            ScalerTypeC0PdBackToReadyState_WDINT();
                            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending DP Config to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                            if(GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else
                            {
                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeC0PdBackToReadyState_WDINT();
                            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_PP:

                            // Sender Response Timer Timeout After Sending DP Config to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                            if(GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else
                            {
                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP);
                            }

                            // Back to Ready State
                            ScalerTypeC0PdBackToReadyState_WDINT();
                            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_P:

                            // Sender Response Timer Timeout After Sending Exit DP Mode to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                            if(GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                            else
                            {
                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE_SOP_P);
                            }

                            // Back to Ready State
                            ScalerTypeC0PdBackToReadyState_WDINT();
                            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_PP:

                            // Sender Response Timer Timeout After Sending Exit DP Mode to Cable
                            // Update PR/DR/Spec Version In Msg Header For SOP Communication.
                            ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT();

                            ADD_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                            if(GET_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT() >= _MAX_VDM_NO_RESP_CNT)
                            {
                                CLR_TYPE_C_0_PD_CBL_VDM_NO_RESP_CNT();

                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                            else
                            {
                                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP);
                            }

                            // Back to Ready State
                            ScalerTypeC0PdBackToReadyState_WDINT();
                            SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        default:

                            break;
                    }

                    break;
#endif  // End of #if((_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))

                default:

                    break;
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set Flag & Time in Interrupt For Main Loop to Active Timer Event
// Input Value  : enumEventID : Timer Event / usTime : Timeout Time
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdActiveTimerEvent_WDINT(WORD usTime, EnumScalerTimerEventID enumEventID)
{
    SET_TYPE_C_0_PD_TIMER_EVENT_ID(enumEventID);
    SET_TYPE_C_0_PD_TIMER_EVENT_CNT(usTime);
    SET_TYPE_C_0_PD_TIMER_EVENT_VALID();
}

//--------------------------------------------------
// Description  : Send Power Delivery Message in WD Timer
// Input Value  : enumPacketType : _PD_SOP_PKT
//                enumPdCmd : _PD_CMD_SRC_CAP / _PD_CMD_PS_RDY
//                enumVdmCmd : _PD_VDM_CMD_RESERVED
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdSendMsg_WDINT(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    // 1. Clear Flags
    CLR_TYPE_C_0_PD_INT_OVERWRITE();
    CLR_TYPE_C_0_PD_TRANSMIT_RESULT();

    // 2. Construct Msg.
    ScalerTypeC0PdConstructMsg_WDINT(enumPacketType, enumPdCmd, enumVdmCmd);

    // Start Disable Rcv Msg.
    ScalerTypeC0PdRxIntControl_WDINT(_DISABLE);

    // 3. Only Send Msg. When Tx FIFO Has Not Been Overwritten by INT during Msg. Construct Flow
    if(GET_TYPE_C_0_PD_INT_OVERWRITE() == _TRUE)
    {
        // Enable Rcv Msg.
        ScalerTypeC0PdRxIntControl_WDINT(_ENABLE);

        // Function Has Been Interrupted Before Sending, Set "_PD_SENT_DISCARDED" and Just Not Start Transmit.
        SET_TYPE_C_0_PD_TRANSMIT_RESULT(_PD_SENT_DISCARDED);
    }
    else
    {
        // [0x65DC] Clear IRQs
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
        ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
        ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

        // [0x65DD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
        ScalerSetBit_EXINT(P65_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

        // [0x65DA] Start Transmit ([1] = 0, Wait For GoodCRC Response After Transmission)
        ScalerSetBit_EXINT(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

        // [0x65E5] Set Tx FIFO [2:1] Spec Ver = 2.0, For PD2.0/3.0 CTS
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (_BIT1));
    }
}

//--------------------------------------------------
// Description  : Construct Power Delivery Message in WD Timer
// Input Value  : enumPacketType : _PD_SOP_PKT
//                enumPdCmd : _PD_CMD_SRC_CAP / _PD_CMD_PS_RDY
//                enumVdmCmd : _PD_VDM_CMD_RESERVED
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdConstructMsg_WDINT(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucExtendedBit_WDINT = 0;
    BYTE ucDataObjectCnt_WDINT = 0;
    BYTE ucMsgHeader_WDINT = 0;

    // 1. [0x65E9-EA] Set Up Number of Data Objects(Data Blocks) if Needed
    switch(enumPdCmd)
    {
        // Control Message Has No Data Object
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

        // Data Message
        case _PD_CMD_SRC_CAP:

            ucExtendedBit_WDINT = 0;
            ucDataObjectCnt_WDINT = GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT();

#if(_EMB_TYPE_C_0_PD3_PPS_SUPPORT == _ON)
            // Do not send PPS PDO when the Spec Version is PD2.0 or not support PPS
            if(GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_2_0)
#endif
            {
                for(BYTE ucLoopIndex = GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() - 1; ucLoopIndex > 0; ucLoopIndex--)
                {
                    if(GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
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

        case _PD_CMD_VDM:

            switch(enumVdmCmd)
            {
                case _PD_VDM_CMD_DISCOVER_ID_REQ:

                    ucExtendedBit_WDINT = 0;
                    ucDataObjectCnt_WDINT = 1;

                    break;

                case _PD_VDM_CMD_ATTENTION_REQ:
                case _PD_VDM_CMD_10:

                    ucDataObjectCnt_WDINT = 2;

                    break;

                default:

                    break;
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_ALERT:

            ucDataObjectCnt_WDINT = 1;

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        case _PD_CMD_EPR_MODE:

            ucDataObjectCnt_WDINT = 1;

            break;

        case _PD_CMD_EPR_SRC_CAP:

            ucExtendedBit_WDINT = 1;

            if((GET_TYPE_C_0_PD_EPR_SRC_PDO_CNT() == 0) && (GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() < 7))
            {
                // If Only SPR PDO and PDO Count < 7, Do Not Use Chunked to Send EPR Source Cap
                // Data Object = SPR PDO Count + 1 (Extended Header)
                ucDataObjectCnt_WDINT = GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() + 1;

                CLR_TYPE_C_0_PD_TX_CHUNKED_MESSAGE();
            }
            else
            {
                // If PDO Count > 7, Use Chunked to Send EPR Source Cap
                if(GET_TYPE_C_0_PD_TX_CHUNK_NUMBER() == 0)
                {
                    // Chunk 0 : Data Object = 7
                    ucDataObjectCnt_WDINT = 7;

                    SET_TYPE_C_0_PD_TX_CHUNKED_MESSAGE();
                }
                else
                {
                    // Chunk 1 : Data Object = EPR PDO Count + 1 (Extended Header)
                    ucDataObjectCnt_WDINT = GET_TYPE_C_0_PD_EPR_SRC_PDO_CNT() + 1;
                }
            }

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        default:

            break;
    }

    // 2. Construct Data Object into Tx FIFO, if Number of Data Object is not 0
    if(ucDataObjectCnt_WDINT != 0)
    {
        ScalerTypeC0PdConstructDataObj_WDINT(enumPacketType, enumPdCmd, enumVdmCmd);
    }

    // 3. [0x65E5] Construct Msg. Header 0
    // ===================================================================
    // | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    // |Ext| Num. of DO| PR|  Spec | DR|
    ucMsgHeader_WDINT = ucMsgHeader_WDINT | (BYTE)(ucExtendedBit_WDINT << 7);
    ucMsgHeader_WDINT = ucMsgHeader_WDINT | (BYTE)(ucDataObjectCnt_WDINT << 4);

    if(enumPacketType == _PD_SOP_PKT)
    {
        ucMsgHeader_WDINT = ucMsgHeader_WDINT | (GET_TYPE_C_0_PD_POWER_ROLE() << 3);
        ucMsgHeader_WDINT = ucMsgHeader_WDINT | (GET_TYPE_C_0_PD_SPEC_VER() << 1);
        ucMsgHeader_WDINT = ucMsgHeader_WDINT | GET_TYPE_C_0_PD_DATA_ROLE();
    }
    else if((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT))
    {
        ucMsgHeader_WDINT = ucMsgHeader_WDINT | (BYTE)(_PD_DEVICE << 3);
        ucMsgHeader_WDINT = ucMsgHeader_WDINT | (GET_TYPE_C_0_PD_CBL_SPEC_VER() << 1);
    }

    // ====================================================================

    // 4. Disable Rcv Msg. INT
    ScalerTypeC0PdRxIntControl_WDINT(_DISABLE);

    // 5. Start to Fill Packet Type, Msg. Header & Data Object
    if(ScalerGetBit_EXINT(P65_DA_TX_TRANSMIT_CTRL, _BIT7) == 0x00)
    {   // Do Not Write Tx FIFO When Tx is Transmitting During INT

        // [0x65E0] Select Transmission Mode
        // [7:6] b'00 = Preamble + SOP + Msg. Header + Data + CRC + EOP
        ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), 0x00);

        // [0x65E0] Set Packet Type [5:3]
        ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), ((enumPacketType << 3) & (_BIT5 | _BIT4 | _BIT3)));

        // [0x65E5] Fill in Msg. Header 0
        ScalerSetByte_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ucMsgHeader_WDINT);

        // [0x65E6] Fill in Msg. Header 1 ( Msg. Header[4:0] : Command Type = enumCtrlMsg )
        ScalerSetBit_EXINT(P65_E6_TX_FIFO_MSG_HEADER1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (enumPdCmd & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

        // Clear Tx FIFO Addr.
        ScalerSetByte_EXINT(P65_E9_TX_FIFO_ADDR, 0x00);

        // Fill Data Object into Tx FIFO
        for(BYTE ucLoopIndex = 0; ucLoopIndex < (ucDataObjectCnt_WDINT * 4); ucLoopIndex++)
        {
            ScalerSetByte_EXINT(P65_EA_TX_FIFO_DATA, g_pucTypeC0PdDataObject_EXINT[ucLoopIndex]);

            // Manual Increase Tx FIFO Address
            ScalerSetByte_EXINT(P65_E9_TX_FIFO_ADDR, ScalerGetByte_EXINT(P65_E9_TX_FIFO_ADDR) + 1);
        }
    }

    // 6. Enable Rcv Msg. INT
    ScalerTypeC0PdRxIntControl_WDINT(_ENABLE);
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO @ WD Timer
// Input Value  : enumPacketType : _PD_SOP_PKT / _PD_SOP_P_PKT
//                enumPdCmd : _PD_CMD_SRC_CAP / _PD_CMD_VDM
//                enumVdmCmd : _PD_VDM_CMD_RESERVED / _PD_VDM_CMD_DISCOVER_ID_REQ
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdConstructDataObj_WDINT(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    enumPdCmd = enumPdCmd;
    enumVdmCmd = enumVdmCmd;

    // Clear ucDataObj_EXINT
    for(BYTE ucLoopIndex = 0; ucLoopIndex < _MAX_DATA_OBJ_CNT * 4; ucLoopIndex ++)
    {
        g_pucTypeC0PdDataObject_EXINT[ucLoopIndex] = 0;
    }

    // Process Data Object Fields For FIFO Fill
    switch(enumPdCmd)
    {
        case _PD_CMD_SRC_CAP:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| DRP| Sus| UP | UC | DRD| Unc|
#if((_TYPE_C_0_PD_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_TYPE_C_0_PD_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_TYPE_C_0_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_TYPE_C_0_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
            if(GET_TYPE_C_0_CC_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                g_pucTypeC0PdDataObject_EXINT[0] = g_pucTypeC0PdDataObject_EXINT[0] | (_BIT5);
            }
#endif

#if(_USB_SUSPEND == _TRUE)
            g_pucTypeC0PdDataObject_EXINT[0] = g_pucTypeC0PdDataObject_EXINT[0] | (_BIT4);
#endif
            if(GET_TYPE_C_0_PD_UNCONSTRAIN_POWER() == _TRUE)
            {
                g_pucTypeC0PdDataObject_EXINT[0] = g_pucTypeC0PdDataObject_EXINT[0] | (_BIT3);
            }

#if(_EMB_TYPE_C_0_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
            g_pucTypeC0PdDataObject_EXINT[0] = g_pucTypeC0PdDataObject_EXINT[0] | (_BIT2);
#endif

#if((_TYPE_C_0_PD_DFP_SWAP_TO_UFP == _TRUE) || (_TYPE_C_0_PD_UFP_SWAP_TO_DFP == _TRUE))
            g_pucTypeC0PdDataObject_EXINT[0] = g_pucTypeC0PdDataObject_EXINT[0] | (_BIT1);
#endif

#if(_UNCHUNK_SUPPORT == _TRUE)
            if(GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucTypeC0PdDataObject_EXINT[0] = g_pucTypeC0PdDataObject_EXINT[0] | (_BIT0);
            }
#endif

            // [23] EPR Mode Capable
            if(GET_TYPE_C_0_PD_EPR_SRC_CAPABLE() == _TRUE)
            {
                g_pucTypeC0PdDataObject_EXINT[1] = g_pucTypeC0PdDataObject_EXINT[1] | (_BIT7);
            }

            for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT(); ucLoopIndex ++)
            {
                if(GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_FIX_SUPPLY_PDO)
                {
                    // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                    g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4)] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4)] | (((BYTE)GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex)) << 6);

                    // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                    // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                    g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)(GET_TYPE_C_0_PD_SRC_CAP_PEAK(ucLoopIndex) << 4) & (_BIT5 | _BIT4));
                    g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                    // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                    g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    if((GET_TYPE_C_0_PD_POWER_ROLE() == _PD_POWER_SRC) && (GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex) > GET_TYPE_C_0_PD_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)(GET_TYPE_C_0_PD_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)GET_TYPE_C_0_PD_CBL_MAX_CUR());
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)(GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex) >> 8) & (_BIT1 | _BIT0));
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)(GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex)));
                    }
                }
#if(_EMB_TYPE_C_0_PD3_PPS_SUPPORT == _ON)
                else if((GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO))
                {
                    // [31:28] PDO Type = 4'b1100 (Programmabl Power Supply)
                    g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4)] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4)] | (((BYTE)GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex)) << 4);

                    // [24:17] Max Voltage in 100mV
                    g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4)] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4)] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 10) >> 7) & (_BIT0));
                    g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 10) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = (BYTE)(GET_TYPE_C_0_PD_SRC_CAP_VOL_MIN(ucLoopIndex) / 10);

                    // [6:0] Max Current in 50mA
                    if((GET_TYPE_C_0_PD_POWER_ROLE() == _PD_POWER_SRC) && (((GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex)) * 5) > GET_TYPE_C_0_PD_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = (((BYTE)(GET_TYPE_C_0_PD_CBL_MAX_CUR() / 5)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = (((BYTE)GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            }

            break;

        case _PD_CMD_VDM:

            ScalerTypeC0PdConstructVdmDataObj_WDINT(enumPacketType, enumVdmCmd);

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_ALERT:

            // ---------- Data Message (1 Data Object) ----------
            // Set Type of Alert : [30] OVP Event, [26] OCP Event
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
            if((GET_TYPE_C_0_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
            {
                g_pucTypeC0PdDataObject_EXINT[0] = g_pucTypeC0PdDataObject_EXINT[0] | (_BIT6);
            }
            if((GET_TYPE_C_0_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
            {
                g_pucTypeC0PdDataObject_EXINT[0] = g_pucTypeC0PdDataObject_EXINT[0] | (_BIT2);
            }
#endif

            // [31:24] Type of Alert
            g_pucTypeC0PdDataObject_EXINT[0] = g_pucTypeC0PdDataObject_EXINT[0] | (BYTE)(GET_TYPE_C_0_PD_TYPE_OF_ALERT());

            // [23:20] Fixed Batteries, [19:16] Hot Swappable Batteries
            g_pucTypeC0PdDataObject_EXINT[1] = g_pucTypeC0PdDataObject_EXINT[1] | (BYTE)(GET_TYPE_C_0_PD_BAT_STATUS());

            // [15:4] Rsv., [3:0] Extended Alert Event Type
            g_pucTypeC0PdDataObject_EXINT[3] = g_pucTypeC0PdDataObject_EXINT[3] | ((BYTE)(GET_TYPE_C_0_PD_EXT_ALERT_EVENT()) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        case _PD_CMD_EPR_MODE:

            // [31:24] Action :
            g_pucTypeC0PdDataObject_EXINT[0] = GET_TYPE_C_0_PD_EPR_MODE_ACTION();

            // [23:16] Data :
            if(GET_TYPE_C_0_PD_EPR_MODE_ACTION() == _PD_EPR_MODE_ENTER_FAILED)
            {
                // EPR Mode Enter Failed Reason
                g_pucTypeC0PdDataObject_EXINT[1] = GET_TYPE_C_0_PD_ENTER_EPR_FAILED_REASON();
            }

            break;

        case _PD_CMD_EPR_SRC_CAP:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeC0PdDataObject_EXINT[0] = g_pucTypeC0PdDataObject_EXINT[0] | (_BIT7);
#endif

            if(GET_TYPE_C_0_PD_TX_CHUNKED_MESSAGE() == _TRUE)
            {
                // [14:11] Chunk Number
                g_pucTypeC0PdDataObject_EXINT[0] = g_pucTypeC0PdDataObject_EXINT[0] | ((GET_TYPE_C_0_PD_TX_CHUNK_NUMBER()) << 3);

                // [8:0] Data Size : Total Num Of Data Blocks = [ 7 (Max SPR PDO Count) + EPR PDO Count ] * 4
                g_pucTypeC0PdDataObject_EXINT[1] = ((7 + GET_TYPE_C_0_PD_EPR_SRC_PDO_CNT()) * 4);
            }
            else
            {
                // [8:0] Data Size : Total Num Of Data Blocks = Total PDO Count * 4
                g_pucTypeC0PdDataObject_EXINT[1] = (GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() * 4);
            }

            // ---------- EPR Source Cap Data Blocks (1 PDO = 4 Bytes) ----------
            // ----------- | Byte 00 | Byte 01 | Byte 02 | Byte 03 | ------------
            // ----------- |  [7:0]  | [15:8]  | [23:16] | [31:24] | ------------
            if(((GET_TYPE_C_0_PD_TX_CHUNKED_MESSAGE() == _TRUE) && (GET_TYPE_C_0_PD_TX_CHUNK_NUMBER() == 0)) || (GET_TYPE_C_0_PD_TX_CHUNKED_MESSAGE() == _FALSE))
            {
                // Construct EPR Source Cap Chunk 0

                // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
                // | PDO Type| DRP| Sus| UP | UC | DRD| Unc|
#if((_TYPE_C_0_PD_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_TYPE_C_0_PD_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_TYPE_C_0_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_TYPE_C_0_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
                if(GET_TYPE_C_0_CC_PORT_ROLE() == _TYPE_C_PORT_DRP)
                {
                    g_pucTypeC0PdDataObject_EXINT[5] = g_pucTypeC0PdDataObject_EXINT[5] | (_BIT5);
                }
#endif

#if(_USB_SUSPEND == _TRUE)
                g_pucTypeC0PdDataObject_EXINT[5] = g_pucTypeC0PdDataObject_EXINT[5] | (_BIT4);
#endif
                if(GET_TYPE_C_0_PD_UNCONSTRAIN_POWER() == _TRUE)
                {
                    g_pucTypeC0PdDataObject_EXINT[5] = g_pucTypeC0PdDataObject_EXINT[5] | (_BIT3);
                }

#if(_EMB_TYPE_C_0_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
                g_pucTypeC0PdDataObject_EXINT[5] = g_pucTypeC0PdDataObject_EXINT[5] | (_BIT2);
#endif

#if((_TYPE_C_0_PD_DFP_SWAP_TO_UFP == _TRUE) || (_TYPE_C_0_PD_UFP_SWAP_TO_DFP == _TRUE))
                g_pucTypeC0PdDataObject_EXINT[5] = g_pucTypeC0PdDataObject_EXINT[5] | (_BIT1);
#endif

#if(_UNCHUNK_SUPPORT == _TRUE)
                if(GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC0PdDataObject_EXINT[5] = g_pucTypeC0PdDataObject_EXINT[5] | (_BIT0);
                }
#endif

                // [23] EPR Mode Capable
                if(GET_TYPE_C_0_PD_EPR_SRC_CAPABLE() == _TRUE)
                {
                    g_pucTypeC0PdDataObject_EXINT[4] = g_pucTypeC0PdDataObject_EXINT[4] | (_BIT7);
                }

                for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT(); ucLoopIndex ++)
                {
                    if(GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_FIX_SUPPLY_PDO)
                    {
                        // Only Fill Half of The 7th SPR PDO [15:0] When Use Chunked Message to Send EPR Source Cap
                        if(ucLoopIndex < 6)
                        {
                            // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | (((BYTE)GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex)) << 6);

                            // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                            // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 4] | ((BYTE)(GET_TYPE_C_0_PD_SRC_CAP_PEAK(ucLoopIndex) << 4) & (_BIT5 | _BIT4));
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 4] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                        }

                        // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                        // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                        if((GET_TYPE_C_0_PD_POWER_ROLE() == _PD_POWER_SRC) && (GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex) > GET_TYPE_C_0_PD_CBL_MAX_CUR()))
                        {
                            // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)(GET_TYPE_C_0_PD_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)GET_TYPE_C_0_PD_CBL_MAX_CUR());
                        }
                        else
                        {
                            // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                            // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)(GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex) >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)(GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex)));
                        }
                    }
#if(_EMB_TYPE_C_0_PD3_PPS_SUPPORT == _ON)
                    else if((GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO))
                    {
                        // Only Fill Half of The 7th SPR PDO [15:0] When Use Chunked Message to Send EPR Source Cap
                        if(ucLoopIndex < 6)
                        {
                            // [31:28] PDO Type = 4'b1100 (Programmabl Power Supply)
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | (((BYTE)GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex)) << 4);

                            // [24:17] Max Voltage in 100mV
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 10) >> 7) & (_BIT0));
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 4] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 10) << 1) & (~_BIT0));
                        }

                        // [15:8] Min Voltage in 100mV
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = (BYTE)(GET_TYPE_C_0_PD_SRC_CAP_VOL_MIN(ucLoopIndex) / 10);

                        // [6:0] Max Current in 50mA
                        if((GET_TYPE_C_0_PD_POWER_ROLE() == _PD_POWER_SRC) && (((GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex)) * 5) > GET_TYPE_C_0_PD_CBL_MAX_CUR()))
                        {
                            // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = (((BYTE)(GET_TYPE_C_0_PD_CBL_MAX_CUR() / 5)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                        }
                        else
                        {
                            // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                            // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = (((BYTE)GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                        }
                    }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                }
            }
            else
            {
                // Construct EPR Source Cap Chunk 1

                // If SPR PDO Count = 7, Fill Remaining Half of The 7th SPR PDO
                if(GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() == 7)
                {
                    if(GET_TYPE_C_0_PD_SRC_PDO_TYPE(GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() - 1) == _PD_FIX_SUPPLY_PDO)
                    {
                        // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                        g_pucTypeC0PdDataObject_EXINT[3] = g_pucTypeC0PdDataObject_EXINT[3] | (((BYTE)GET_TYPE_C_0_PD_SRC_PDO_TYPE(GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() - 1)) << 6);

                        // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                        // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                        g_pucTypeC0PdDataObject_EXINT[2] = g_pucTypeC0PdDataObject_EXINT[2] | ((BYTE)(GET_TYPE_C_0_PD_SRC_CAP_PEAK(GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() - 1) << 4) & (_BIT5 | _BIT4));
                        g_pucTypeC0PdDataObject_EXINT[2] = g_pucTypeC0PdDataObject_EXINT[2] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() - 1) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
#if(_EMB_TYPE_C_0_PD3_PPS_SUPPORT == _ON)
                    else if((GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_0_PD_SRC_PDO_TYPE(GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() - 1) == _PD_3_PROGRAMMABLE_PDO))
                    {
                        // [31:28] PDO Type = 4'b1100 (Programmabl Power Supply)
                        g_pucTypeC0PdDataObject_EXINT[3] = g_pucTypeC0PdDataObject_EXINT[3] | (((BYTE)GET_TYPE_C_0_PD_SRC_PDO_TYPE(GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() - 1)) << 4);

                        // [24:17] Max Voltage in 100mV
                        g_pucTypeC0PdDataObject_EXINT[3] = g_pucTypeC0PdDataObject_EXINT[3] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() - 1) / 10) >> 7) & (_BIT0));
                        g_pucTypeC0PdDataObject_EXINT[2] = g_pucTypeC0PdDataObject_EXINT[2] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_0_PD_SPR_SRC_PDO_CNT() - 1) / 10) << 1) & (~_BIT0));
                    }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                }

                for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TYPE_C_0_PD_EPR_SRC_PDO_CNT(); ucLoopIndex ++)
                {
                    if(GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex + 7) == _PD_FIX_SUPPLY_PDO)
                    {
                        // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 7] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 7] | (((BYTE)GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex + 7)) << 6);

                        // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                        // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 6] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 6] | ((BYTE)(GET_TYPE_C_0_PD_SRC_CAP_PEAK(ucLoopIndex + 7) << 4) & (_BIT5 | _BIT4));
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 6] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 6] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex + 7) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                        // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                        // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex + 7) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                        if((GET_TYPE_C_0_PD_POWER_ROLE() == _PD_POWER_SRC) && (GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex + 7) > GET_TYPE_C_0_PD_CBL_MAX_CUR()))
                        {
                            // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | ((BYTE)(GET_TYPE_C_0_PD_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 4] | ((BYTE)GET_TYPE_C_0_PD_CBL_MAX_CUR());
                        }
                        else
                        {
                            // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                            // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | ((BYTE)(GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex + 7) >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 4] | ((BYTE)(GET_TYPE_C_0_PD_SRC_CAP_CUR(ucLoopIndex + 7)));
                        }
                    }
                    else if(GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex + 7) == _PD_3_1_ADJUSTABLE_PDO)
                    {
                        // [31:28] PDO Type = 4'b1101 (Adjustable Voltage Supply)
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 7] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 7] | (((BYTE)GET_TYPE_C_0_PD_SRC_PDO_TYPE(ucLoopIndex + 7)) << 4);

                        // [27:26] Peak Current
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 7] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 7] | ((BYTE)(GET_TYPE_C_0_PD_SRC_CAP_PEAK(ucLoopIndex + 7) << 2) & (_BIT3 | _BIT2));

                        // [25:17] Max Voltage in 100mV
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 7] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 7] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex + 7) / 10) >> 7) & (_BIT1 | _BIT0));
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 6] = g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 6] | ((BYTE)((GET_TYPE_C_0_PD_SRC_CAP_VOL_MAX(ucLoopIndex + 7) / 10) << 1) & (~_BIT0));

                        // [15:8] Min Voltage in 100mV
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = (BYTE)(GET_TYPE_C_0_PD_SRC_CAP_VOL_MIN(ucLoopIndex + 7) / 10);

                        // [7:0] PDP in 1W
                        g_pucTypeC0PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = (BYTE)(GET_TYPE_C_0_MAX_POWER() / 10);
                    }
                }
            }

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO in WD Timer
// Input Value  : enumPacketType : _PD_SOP_PKT / _PD_SOP_P_PKT
//                enumVdmCmd : _PD_VDM_CMD_DISCOVER_ID_REQ
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdConstructVdmDataObj_WDINT(EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd)
{
    switch(enumVdmCmd)
    {
        case _PD_VDM_CMD_DISCOVER_ID_REQ:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] PD SID = 0xFF00
            g_pucTypeC0PdDataObject_EXINT[0] = 0xFF;
            g_pucTypeC0PdDataObject_EXINT[1] = 0x00;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos = b'000
            g_pucTypeC0PdDataObject_EXINT[2] = (_BIT7);

            // For SOP Packet : If Port Partners Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            // For SOP' Packet : If Port Partners & Cable Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0)) ||
               ((enumPacketType == _PD_SOP_P_PKT) && (GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_0_PD_CBL_SPEC_VER() == _PD_VERSION_3_0)))
            {
                g_pucTypeC0PdDataObject_EXINT[2] = g_pucTypeC0PdDataObject_EXINT[2] | (_BIT5);

                // SVDM Version = 2.1 Only when Port Partner or Cable Support 2.1 or Higher
                if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_0_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)) ||
                   ((enumPacketType == _PD_SOP_P_PKT) && (GET_TYPE_C_0_PD_CBL_SVDM_VERSION() >= _PD_SVDM_VER_2_1)))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeC0PdDataObject_EXINT[2] = g_pucTypeC0PdDataObject_EXINT[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Discover ID Request (0x01) / Discover SVID Request (0x02)
            g_pucTypeC0PdDataObject_EXINT[3] = enumVdmCmd;

            break;

        case _PD_VDM_CMD_ATTENTION_REQ:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucTypeC0PdDataObject_EXINT[0] = 0xFF;
            g_pucTypeC0PdDataObject_EXINT[1] = 0x01;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
            g_pucTypeC0PdDataObject_EXINT[2] = (_BIT7) | (GET_TYPE_C_0_PD_DP_OBJ_POS());

            // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucTypeC0PdDataObject_EXINT[2] = g_pucTypeC0PdDataObject_EXINT[2] | (_BIT5);

                // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                if(GET_TYPE_C_0_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeC0PdDataObject_EXINT[2] = g_pucTypeC0PdDataObject_EXINT[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Attention Req (0x06)
            g_pucTypeC0PdDataObject_EXINT[3] = enumVdmCmd;

            // -------- Data Obj 1 : DP Status ---------
            // [31:16] Reserved = 0x00
            g_pucTypeC0PdDataObject_EXINT[4] = 0x00;
            g_pucTypeC0PdDataObject_EXINT[5] = 0x00;

#if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
            // [15:9] Reserved, [8] HPD IRQ, [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No
            // [4] Multi-Func = No, [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
            g_pucTypeC0PdDataObject_EXINT[6] = 0x00;
            g_pucTypeC0PdDataObject_EXINT[7] = (0x0A) | (GET_TYPE_C_0_PD_MULTI_FUNCTION() << 4);

            if(GET_TYPE_C_0_PD_FORCE_HPD_IRQ() == _TRUE)
            {
                // HPD = IRQ, HPD_High = 1
                g_pucTypeC0PdDataObject_EXINT[7] = (g_pucTypeC0PdDataObject_EXINT[7]) | (_BIT7);

                // HPD IRQ = 1
                g_pucTypeC0PdDataObject_EXINT[6] = _BIT0;
            }
            else if(GET_TYPE_C_0_PD_HPD_QUEUE(GET_TYPE_C_0_PD_HPD_RPTR()) != _PD_HPD_LOW)
            {
                // HPD = HIGH or IRQ, HPD_High = 1
                g_pucTypeC0PdDataObject_EXINT[7] = (g_pucTypeC0PdDataObject_EXINT[7]) | (_BIT7);

                if(GET_TYPE_C_0_PD_HPD_QUEUE(GET_TYPE_C_0_PD_HPD_RPTR()) == _PD_HPD_IRQ)
                {
                    g_pucTypeC0PdDataObject_EXINT[6] = _BIT0;
                }
            }

            if(GET_TYPE_C_0_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
            {
                g_pucTypeC0PdDataObject_EXINT[7] = g_pucTypeC0PdDataObject_EXINT[7] | (_BIT6);
            }

#elif(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
            // [15:9] Reserved, [8] HPD IRQ : No, [7] HPD State : LOW, [6] Exit DP : No, [5] USB Config = No
            // [4] Multi-Func, [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_TX(b'01)
            g_pucTypeC0PdDataObject_EXINT[6] = 0x00;
            g_pucTypeC0PdDataObject_EXINT[7] = (0x09) | (GET_TYPE_C_0_PD_MULTI_FUNCTION() << 4);

            if(GET_TYPE_C_0_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
            {
                g_pucTypeC0PdDataObject_EXINT[7] = g_pucTypeC0PdDataObject_EXINT[7] | (_BIT6);
            }
#endif  // End of #if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

            break;

        case _PD_VDM_CMD_10:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucTypeC0PdDataObject_EXINT[0] = 0xFF;
            g_pucTypeC0PdDataObject_EXINT[1] = 0x01;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
            g_pucTypeC0PdDataObject_EXINT[2] = (_BIT7) | (GET_TYPE_C_0_PD_DP_OBJ_POS());

            // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucTypeC0PdDataObject_EXINT[2] = g_pucTypeC0PdDataObject_EXINT[2] | (_BIT5);

                // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                if(GET_TYPE_C_0_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeC0PdDataObject_EXINT[2] = g_pucTypeC0PdDataObject_EXINT[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = DP Status Req (0x10)
            g_pucTypeC0PdDataObject_EXINT[3] = enumVdmCmd;

            // -------- Data Obj 1 : DP Status ---------
            // [31:16] Reserved = 0x00
            g_pucTypeC0PdDataObject_EXINT[4] = 0x00;
            g_pucTypeC0PdDataObject_EXINT[5] = 0x00;

#if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
            // [15:9] Reserved, [8] HPD IRQ, [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No
            // [4] Multi-Func = No, [3] DP En = No, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
            g_pucTypeC0PdDataObject_EXINT[6] = 0x00;
            g_pucTypeC0PdDataObject_EXINT[7] = 0x02;

            if(GET_TYPE_C_0_PD_FORCE_HPD_IRQ() == _TRUE)
            {
                // HPD = IRQ, HPD_High = 1
                g_pucTypeC0PdDataObject_EXINT[7] = (g_pucTypeC0PdDataObject_EXINT[7]) | (_BIT7);

                // HPD IRQ = 1
                g_pucTypeC0PdDataObject_EXINT[6] = _BIT0;
            }
            else if(GET_TYPE_C_0_PD_HPD_QUEUE(GET_TYPE_C_0_PD_HPD_RPTR()) != _PD_HPD_LOW)
            {
                // HPD = HIGH or IRQ, HPD_High = 1
                g_pucTypeC0PdDataObject_EXINT[7] = (g_pucTypeC0PdDataObject_EXINT[7]) | (_BIT7);

                if(GET_TYPE_C_0_PD_HPD_QUEUE(GET_TYPE_C_0_PD_HPD_RPTR()) == _PD_HPD_IRQ)
                {
                    g_pucTypeC0PdDataObject_EXINT[6] = _BIT0;
                }
            }

            if(GET_TYPE_C_0_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
            {
                g_pucTypeC0PdDataObject_EXINT[7] = g_pucTypeC0PdDataObject_EXINT[7] | (_BIT6);
            }

#elif(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
            // [15:2] Reserved, [1:0] Connected DP Role : DP_TX(b'01)
            g_pucTypeC0PdDataObject_EXINT[6] = 0x00;
            g_pucTypeC0PdDataObject_EXINT[7] = 0x01;
#endif  // End of #if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

            break;

        case _PD_VDM_CMD_DISCOVER_SVID_REQ:
        case _PD_VDM_CMD_DISCOVER_MODE_REQ:
        case _PD_VDM_CMD_ENTER_MODE_REQ:
        case _PD_VDM_CMD_EXIT_MODE_REQ:
        case _PD_VDM_CMD_11:
        case _PD_VDM_CMD_DISCOVER_ID_ACK:
        case _PD_VDM_CMD_DISCOVER_SVID_ACK:
        case _PD_VDM_CMD_DISCOVER_MODE_ACK:
        case _PD_VDM_CMD_ENTER_MODE_ACK:
        case _PD_VDM_CMD_EXIT_MODE_ACK:
        case _PD_VDM_CMD_50:
        case _PD_VDM_CMD_51:
        case _PD_VDM_CMD_DISCOVER_ID_NAK:
        case _PD_VDM_CMD_DISCOVER_SVID_NAK:
        case _PD_VDM_CMD_DISCOVER_MODE_NAK:
        case _PD_VDM_CMD_ENTER_MODE_NAK:
        case _PD_VDM_CMD_EXIT_MODE_NAK:
        case _PD_VDM_CMD_90:
        case _PD_VDM_CMD_91:
        case _PD_VDM_CMD_DISCOVER_ID_BUSY:
        case _PD_VDM_CMD_DISCOVER_SVID_BUSY:
        case _PD_VDM_CMD_DISCOVER_MODE_BUSY:
        case _PD_VDM_CMD_ENTER_MODE_BUSY:
        case _PD_VDM_CMD_EXIT_MODE_BUSY:
        case _PD_VDM_CMD_D0:
        case _PD_VDM_CMD_D1:
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Send Soft Reset Message
// Input Value  : enumPacketType : _SOP_PKT
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdSendSoftRst_WDINT(EnumTypeCPDPacketType enumPacketType)
{
    // 1. Clear Flags & Reset PRL Layer [0x6503]
    CLR_TYPE_C_0_PD_INT_OVERWRITE();
    CLR_TYPE_C_0_PD_TRANSMIT_RESULT();
    ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~_BIT0, 0x00);

    // 2. Construct Msg.
    ScalerTypeC0PdConstructSoftReset_WDINT(enumPacketType);

    // Start Disable Rcv Msg.
    ScalerTypeC0PdRxIntControl_WDINT(_DISABLE);

    // 3. Enable PRL Layer & Release Message ID Reset [0x6503/E4]
    ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P65_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // 4. Only Send Msg. When Tx FIFO Has Not Been Overwritten by INT during Msg. Construct Flow
    if(GET_TYPE_C_0_PD_INT_OVERWRITE() == _TRUE)
    {
        // Enable Rcv Msg.
        ScalerTypeC0PdRxIntControl_WDINT(_ENABLE);

        // Function Has Been Interrupted Before Sending, Set "_PD_SENT_DISCARDED" and Just Not Start Transmit.
        SET_TYPE_C_0_PD_TRANSMIT_RESULT(_PD_SENT_DISCARDED);
    }
    else
    {
        // [0x65DC] Clear IRQs
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
        ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
        ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

        // [0x65DD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
        ScalerSetBit_EXINT(P65_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

        // [0x65DA] Start Transmit ([1] = 0, Wait For GoodCRC Response After Transmission)
        ScalerSetBit_EXINT(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

        // [0x65E5] Set Tx FIFO [2:1] Spec Ver = 2.0, For PD2.0/3.0 CTS
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (_BIT1));
    }
}

//--------------------------------------------------
// Description  : Construct Soft Reset Msg. in Interrupt
// Input Value  : enumPacketType : _SOP_PKT
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdConstructSoftReset_WDINT(EnumTypeCPDPacketType enumPacketType)
{
    // Disable Rcv Msg. INT
    ScalerTypeC0PdRxIntControl_WDINT(_DISABLE);

    // Start to Fill Packet Type, Msg. Header
    if(ScalerGetBit_EXINT(P65_DA_TX_TRANSMIT_CTRL, _BIT7) == 0x00)
    {   // Do Not Write Tx FIFO When Tx is Transmitting During INT

        // 1. [0x65E0] Set Transmit Type : b'00 = Preamble + SOP + Msg. Header + Data + CRC + EOP
        ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), 0x00);

        // 2. [0x65E0] Set Packet Type [5:3]
        ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), ((enumPacketType << 3) & (_BIT5 | _BIT4 | _BIT3)));

        // 3. [0x65E5] Fill in Msg. Header0
        // [7]   Msg. Header[15]     : Extended Field = 0
        // [6:4] Msg. Header[14:12]  : Number of Data Object = 0
        ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // [3] Msg. Header[8]  : Power Role
        // [0] Msg. Header[5]  : Data Role
        if(enumPacketType == _PD_SOP_PKT)
        {
            // [3] Power Role / [2:1] Spec Version / [0] Data Role
            ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, GET_TYPE_C_0_PD_POWER_ROLE() << 3);
            ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_TYPE_C_0_PD_SPEC_VER() << 1);
            ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_TYPE_C_0_PD_DATA_ROLE());

            // Reset Message ID [0x65E4]
            ScalerSetBit_EXINT(P65_E4_TX_MSG_ID_RST, ~_BIT2, 0x00);
        }
        else
        {
            ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, (BYTE)_PD_DEVICE << 3);
            ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_TYPE_C_0_PD_CBL_SPEC_VER() << 1);
            ScalerSetBit_EXINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);

            if(enumPacketType == _PD_SOP_P_PKT)
            {
                // Reset Message ID [0x65E4]
                ScalerSetBit_EXINT(P65_E4_TX_MSG_ID_RST, ~_BIT1, 0x00);
            }
            else if(enumPacketType == _PD_SOP_PP_PKT)
            {
                // Reset Message ID [0x65E4]
                ScalerSetBit_EXINT(P65_E4_TX_MSG_ID_RST, ~_BIT0, 0x00);
            }
        }

        // [0x65E6] Fill in Msg. Header1
        // [4:0]  Msg. Header[4:0] : Command Type = b'0_1101
        ScalerSetBit_EXINT(P65_E6_TX_FIFO_MSG_HEADER1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
    }

    // Enable Rcv Msg. INT
    ScalerTypeC0PdRxIntControl_WDINT(_ENABLE);
}

//--------------------------------------------------
// Description  : Initiate Hard Reset When Error Happens in WD Timer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdSendHardRst_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime)
{
    if(GET_TYPE_C_0_PD_HARD_RST_CNT() <= _MAX_HARD_RST_CNT)
    {
        // Start Disable Rcv Msg.
        ScalerTypeC0PdRxIntControl_WDINT(_DISABLE);

        // 1. [0x65E0] Select Transmission Mode [7:6] : b'01 = Preamble + SOP
        ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), _BIT6);

        // 2. [0x65E0] Set Packet Type [5:3] : b'011 = HARD_RESET
        ScalerSetBit_EXINT(P65_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

        // 3. [0x65DC] Clear IRQs
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
        ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
        ScalerSetBit_EXINT(P65_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

        // 4. [0x65DA] Start Transmit
        ScalerSetBit_EXINT(P65_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));
        ADD_TYPE_C_0_PD_HARD_RST_CNT();

        // 5. Process Hard Reset
        ScalerTypeC0PdProcHardRst_WDINT(pucActiveWDID, pucActiveWDTime);
    }
    else
    {
        // Do Type-C Error Recovery
        SET_TYPE_C_0_CC_ERROR_RECOVERY();
    }
}

//--------------------------------------------------
// Description  : Process Hard Reset When Hard Reset Sent/Rcv. in WD Timer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdProcHardRst_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime)
{
    pucActiveWDID = pucActiveWDID;
    pucActiveWDTime = pucActiveWDTime;

    // Clear Hard Reset Turn Off Power Flag (Set When 1.Power Already Turned Off to vSafe0v for SRC 2.Vbus Already Not vSafe5v for SNK)
    CLR_TYPE_C_0_PD_HRST_PWR_OFF();

    if(GET_TYPE_C_0_PD_POWER_ROLE() == _PD_POWER_SRC)
    {
#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
        // Adjust Power (Turn Off Vbus)
        ScalerTypeC0PmicSetting_WDINT(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
        // Enable Vbus Discharge
        ScalerTypeC0PmicVbusDischarge_WDINT(_ON);
#endif

        // [Eizo] SIC437A Customized Power Control : Send/Receive Hard Reset
        ScalerTypeC0PmicSic437aHardRstStartProc_WDINT(_TYPE_C_POWER_SRC);

#if(_EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
        // Tool Not Show Warning UI when We Turn Off Vbus
        ScalerTypeC0CcToolWarningUIControl_WDINT(_DISABLE);
#endif
#else
        *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_SRC_TURN_OFF_POWER;
        *pucActiveWDTime = _SRC_ADJUST_POWER_TIMER;
#endif
    }
    else
    {
#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
        // 1. Turn Off Power Draw, Vbus should be drive to vSafe0V by Source (PD 7.1.5). Disable Detect Sink OVP/UVP
        ScalerTypeC0PmicSetting_WDINT(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
#endif

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_0_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
        // [FW Sol. for _TYPE_C_5B_LS_ADC_GEN_1] Write 1 Clear 5Bit LS_ADC Vbus Off IRQ and Disable IRQ_EN
        ScalerTypeCAdcOnOffCompIntControl_WDINT(_TYPE_C_CHANNEL_0_VMON, _OFF, _DISABLE);
#else
        // 2. Turn Off Type-C Unattach Vbus Detection
        ScalerTypeC0CcVbusDetCtrl_WDINT(_DISABLE);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
        // [Eizo] SIC437A Customized Power Control : Send/Receive Hard Reset
        ScalerTypeC0PmicSic437aHardRstStartProc_WDINT(_TYPE_C_POWER_SNK);
#endif
#endif

        ScalerTypeC0PdActiveTimerEvent_WDINT(_SNK_HARD_RST_TIMER, _SCALER_TIMER_EVENT_PD_0_SNK_HARD_RST_TIMEOUT);
    }

    // Turn Off Vconn, If Already Turned On
    if(GET_TYPE_C_0_PD_VCONN_ROLE() == _PD_VCONN_SRC)
    {
        ScalerTypeC0CcVconnControl_WDINT(_OFF);
    }

    // [0x6502] Disable PHY Layer BMC Tx/Rx
    ScalerSetBit_EXINT(P65_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), 0x00);

    // [0x6543] Clear and Disable Hard Reset IRQ
    ScalerSetBit_EXINT(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    // State Transition
    SET_TYPE_C_0_PD_FW_STATE(_PD_HARDRESET);
    SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_STATE_NONE);
    SET_TYPE_C_0_PD_AMS_STATUS(_PD_AMS_NONE);
    SET_TYPE_C_0_PD_CBL_STATE(_PD_CBL_STATE_NONE);
}

//--------------------------------------------------
// Description  : Check if Tx HW is Avaliable (PD 3.0 : Check TxSinkOK/NG, PD 2.0 : Check PHY Idle)
// Input Value  : pucActiveWDID, pucActiveWDTime
// Output Value : _PD_TX_NOT_AVAILABLE / _PD_TX_AVAILABLE / _PD_TX_WAIT_SRC_INIT_AMS_TIMER
//--------------------------------------------------
EnumTypeCTxCheckResult ScalerTypeC0PdTxAvaliable_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime)
{
    EnumTypeCTxCheckResult enumTxCheckResult = _PD_TX_NOT_AVAILABLE;

    if(GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0)
    {
        if(GET_TYPE_C_0_PD_POWER_ROLE() == _PD_POWER_SRC)
        {
            // Source Can Initiate AMS 16-20ms After Change Rp to SinkTxNG
            ScalerSetBit_WDINT(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), _PD_SINK_TX_NG);

            *pucActiveWDID = _SCALER_WD_TIMER_EVENT_PD_0_TX_AVALIABLE;
            *pucActiveWDTime = _SRC_INIT_AMS_TIMER;

            enumTxCheckResult = _PD_TX_WAIT_SRC_INIT_AMS_TIMER;

            if(GET_TYPE_C_0_PD_EPR_MODE() == _TRUE)
            {
                // Cancel SourceEPRKeepAliveTimer (750~1000ms)
                // Note : Since PD Timer Can't be Canceled in WDINT, Set Macro to Cancel SourceEPRKeepAliveTimer in Mainloop or Skip Sending Hard Reset When it Timeout.
                SET_TYPE_C_0_PD_CANCEL_SRC_EPR_KEEP_ALIVE();

                if((GET_TYPE_C_0_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_0_SRC_EPR_KEEP_ALIVE_TIMEOUT) && (GET_TYPE_C_0_PD_TIMER_EVENT_VALID() == _TRUE))
                {
                    CLR_TYPE_C_0_PD_TIMER_EVENT_VALID();
                }
            }
        }
        else
        {
            if(ScalerTypeC0CcDetResistor_WDINT() == _TYPE_C_DET_RP_3P0A)
            {   // Rp = SinkTxOK (Rp 3.0A)
                enumTxCheckResult = _PD_TX_AVAILABLE;
            }
            else
            {   // Rp = SinkTxNG (Rp 1.5A)
                enumTxCheckResult = _PD_TX_NOT_AVAILABLE;
            }
        }
    }
    else
    {   // Check PHY Idle
        if(ScalerGetBit_WDINT(P65_05_PD_PHY_IDLE_INT, _BIT2) == _BIT2)
        {   // PHY Idle Flag = 1
            enumTxCheckResult = _PD_TX_AVAILABLE;
        }
        else
        {   // PHY Idle Flag = 0
            enumTxCheckResult = _PD_TX_NOT_AVAILABLE;
        }
    }

    return enumTxCheckResult;
}

//--------------------------------------------------
// Description  : Enable / Disable FIFO_0/1/2 Interrupt when Rcv Msg.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdRxIntControl_WDINT(bit b1Action)
{
    if(b1Action == _ENABLE)
    {
        // Enable Rx Rcv Msg IRQ
        ScalerSetBit_EXINT(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT6);
    }
    else
    {
        // Disable Rx Rcv Msg IRQ
        ScalerSetBit_EXINT(P65_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), 0x00);
    }
}

#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
//--------------------------------------------------
// Description  : Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdUpdateCableRetryCounter_WDINT(void)
{
    // For Old IC(RL6829) Use, Set Cable Retry Cnt to 0x65EC
    if((GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_0_PD_CBL_SPEC_VER() == _PD_VERSION_3_0))
    {
        ScalerSetBit_WDINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
    }
    else
    {
        ScalerSetBit_WDINT(P65_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
}
#endif

//--------------------------------------------------
// Description  : Update PR/DR/Spec Version In Msg Header For SOP Communication.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdUpdateTxFifoMsgHeader_WDINT(void)
{
    // [3] Power Role / [2:1] Spec Version / [0] Data Role
    ScalerSetBit_WDINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, GET_TYPE_C_0_PD_POWER_ROLE() << 3);
    ScalerSetBit_WDINT(P65_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_TYPE_C_0_PD_SPEC_VER() << 1);
    ScalerSetBit_WDINT(P65_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_TYPE_C_0_PD_DATA_ROLE());
}

#if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
//--------------------------------------------------
// Description  : Judge DP Functionality Support Of Cable(No Ack Vdo Received For Discover Svid(SOP'/SOP'') / Discover Mode(SOP'/SOP''))
// Input Value  : None
// Output Value : EnumTypeCPDAltModeState(_PD_ALT_MODE_SEND_ENTER_MODE / _PD_ALT_MODE_ERROR)
//--------------------------------------------------
EnumTypeCPDAltModeState ScalerTypeC0PdJudgeCableDpFunctionality_WDINT(void)
{
    if(GET_TYPE_C_0_PD_CBL_DP_MODE_INFO_RECEIVED() == _TRUE)
    {
        // If Already Received Cable DP Discover Mode Ack, Do Enter Mode When Not Received Cable TBT3 Discover Mode ACK.
        // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Enter Mode First
        if((GET_TYPE_C_0_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_0_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_0_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
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
        if(GET_TYPE_C_0_PD_CBL_PRODUCT_TYPE() == _PD_PASSIVE_CABLE)
        {
            if((GET_TYPE_C_0_PD_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_3_GEN1) || (GET_TYPE_C_0_PD_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_3OR4_GEN2))
            {
                SET_TYPE_C_0_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR10);
            }
            else if(GET_TYPE_C_0_PD_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_4_GEN3)
            {
                SET_TYPE_C_0_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR20);

                // UHBR20 Capable Passive Cable Shall Support UHBR13.5
                SET_TYPE_C_0_PD_CBL_UHBR13P5_SUPPORT();
            }

            // Stop Enter DP Alt Mode Flow Just for Cable
            CLR_TYPE_C_0_PD_CBL_ENTER_DP_MODE_SUPPORT();

            return _PD_ALT_MODE_SEND_ENTER_MODE;
        }
        else
        {
            // If Cable Type is Active Cable, Stop Enter DP Alt Mode Flow Both for Device & Cable
            return _PD_ALT_MODE_ERROR;
        }
    }
}
#endif  // End of #if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)

#if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
//--------------------------------------------------
// Description  : Force Sending HPD IRQ for DP CTS @ WD Timer
// Input Value  : pucActiveWDID, pucActiveWDTime
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdDpCTSForceHpdIrq_WDINT(BYTE *pucActiveWDID, BYTE *pucActiveWDTime)
{
    BYTE ucSendResult = _FAIL;
    EnumTypeCTxCheckResult enumTxCheckResult = _PD_TX_NOT_AVAILABLE;

    if((GET_TYPE_C_0_PD_HANDLER_ONGOING() == _FALSE) && (GET_TYPE_C_0_PD_HPD_STATUS() == _HIGH) &&
       (((GET_TYPE_C_0_PD_FW_STATE() == _PD_SRC_READY) && (GET_TYPE_C_0_PD_SUB_STATE() == _PD_SUB_SRC_READY)) || ((GET_TYPE_C_0_PD_FW_STATE() == _PD_SNK_READY) && (GET_TYPE_C_0_PD_SUB_STATE() == _PD_SUB_SNK_READY))) &&
       (GET_TYPE_C_0_PD_AMS_STATUS() == _PD_AMS_NONE) && (GET_TYPE_C_0_PD_SYS_EVENT() == _PD_SYS_EVENT_NONE) && (GET_TYPE_C_0_PD_ATTENTION_WAIT() == _FALSE))
    {
        if(GET_TYPE_C_0_PD_DATA_ROLE() == _PD_DATA_UFP)
        {
            enumTxCheckResult = ScalerTypeC0PdTxAvaliable_WDINT(pucActiveWDID, pucActiveWDTime);

            if(enumTxCheckResult == _PD_TX_AVAILABLE)
            {
                SET_TYPE_C_0_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ATTENTION);
                SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Set Macro to Force Sending HPD IRQ (ignore HPD Queue When Costruct DP Status's or Attention's Data Object)
                // Clear Macro When :
                // 1. PD Reset
                // 2. Sent Failed :
                // ----(1) Retry Fail
                // ----(2) For Main loop : Clear Macro When Send Msg Has Been Interrupted (Sent Discarded)
                // ----(3) For EXINT0 / WDINT : Clear Macro When Received any Msg before _SRC_INIT_AMS_TIMER Timeout
                // 3. Sent Success :
                // ----(1) For Attention Req : Clear Macro When Tx Success
                // ----(2) For DP Status Req :
                // --------(a) Clear Macro When Received DP Status ACK or Other Msg
                // --------(b) Clear Macro When Not Received Msg within _SENDER_RESP_TIMER
                SET_TYPE_C_0_PD_FORCE_HPD_IRQ();

                // Send "Attention REQ"
                ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);

                ucSendResult = _SUCCESS;
            }
            else if(enumTxCheckResult == _PD_TX_WAIT_SRC_INIT_AMS_TIMER)
            {
                SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);

                // Set Macro to Force Sending HPD IRQ (ignore HPD Queue When Costruct DP Status's or Attention's Data Object)
                SET_TYPE_C_0_PD_FORCE_HPD_IRQ();

                ucSendResult = _SUCCESS;
            }
        }
        else
        {
            enumTxCheckResult = ScalerTypeC0PdTxAvaliable_WDINT(pucActiveWDID, pucActiveWDTime);

            if(enumTxCheckResult == _PD_TX_AVAILABLE)
            {
                SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                SET_TYPE_C_0_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Set Macro to Force Sending HPD IRQ (ignore HPD Queue When Costruct DP Status's or Attention's Data Object)
                // Clear Macro When :
                // 1. PD Reset
                // 2. Sent Failed :
                // ----(1) Retry Fail
                // ----(2) For Main loop : Clear Macro When Send Msg Has Been Interrupted (Sent Discarded)
                // ----(3) For EXINT0 / WDINT : Clear Macro When Received any Msg before _SRC_INIT_AMS_TIMER Timeout
                // 3. Sent Success :
                // ----(1) For Attention Req : Clear Macro When Tx Success
                // ----(2) For DP Status Req :
                // --------(a) Clear Macro When Received DP Status ACK or Other Msg
                // --------(b) Clear Macro When Not Received Msg within _SENDER_RESP_TIMER
                SET_TYPE_C_0_PD_FORCE_HPD_IRQ();

                // Send "DP Status REQ"
                ScalerTypeC0PdSendMsg_WDINT(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_10);

                ucSendResult = _SUCCESS;
            }
            else if(enumTxCheckResult == _PD_TX_WAIT_SRC_INIT_AMS_TIMER)
            {
                SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);

                // Set Macro to Force Sending HPD IRQ (ignore HPD Queue When Costruct DP Status's or Attention's Data Object)
                SET_TYPE_C_0_PD_FORCE_HPD_IRQ();

                ucSendResult = _SUCCESS;
            }
        }
    }

    if(ucSendResult == _FAIL)
    {
        // Push HPD_IRQ into HPD Queue When Force Sending HPD IRQ Failed, then PD will Re-Send HPD_IRQ in Main loop
        ScalerTypeC0PdPushHpd_WDINT(_PD_HPD_IRQ, 0);
    }
}
#endif  // End of #if(_EMB_TYPE_C_0_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
#endif  // End of #if(_EMB_TYPE_C_0_DP_ALT_MODE_SUPPORT == _ON)
#endif  // End of #if(_EMB_TYPE_C_0_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Go Back To Src/Snk Ready State According to Power Role
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdBackToReadyState_WDINT(void)
{
    // Back to Ready State
    if(GET_TYPE_C_0_PD_POWER_ROLE() == _PD_POWER_SRC)
    {
        SET_TYPE_C_0_PD_FW_STATE(_PD_SRC_READY);
        SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_SRC_READY);

        // If PD 3.0, Change Rp to SinkTxOK
        if(GET_TYPE_C_0_PD_SPEC_VER() == _PD_VERSION_3_0)
        {
            ScalerSetBit_WDINT(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), _PD_SINK_TX_OK);
        }

        // Active SourceEPRKeepAliveTimer (750~1000ms) When Back to Ready State in EPR Mode, Timeout : Hard Reset
        if(GET_TYPE_C_0_PD_EPR_MODE() == _TRUE)
        {
            ScalerTypeC0PdActiveTimerEvent_WDINT(_SRC_EPR_KEEP_ALIVE_TIMER, _SCALER_TIMER_EVENT_PD_0_SRC_EPR_KEEP_ALIVE_TIMEOUT);

            // Clear Macro When Active SourceEPRKeepAliveTimer to Avoid Canceling it in Mainloop
            CLR_TYPE_C_0_PD_CANCEL_SRC_EPR_KEEP_ALIVE();
        }
    }
    else
    {
        SET_TYPE_C_0_PD_FW_STATE(_PD_SNK_READY);
        SET_TYPE_C_0_PD_SUB_STATE(_PD_SUB_SNK_READY);
    }
}

//--------------------------------------------------
// Description  : Get DP Alt. Mode Pin Assignment
// Input Value  : None
// Output Value : Enumeration of Pin Assignment C/D/E
//--------------------------------------------------
EnumTypeCPinCfgType ScalerTypeC0PdGetPinAssignment_WDINT(void)
{
    return GET_TYPE_C_0_PD_PIN_ASSIGNMENT();
}

//--------------------------------------------------
// Description  : Set TypeC 0 System Event
// Input Value  : enumPdSysEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdSetSystemEvent_WDINT(EnumTypeCPDSysEvent enumPdSysEvent)
{
    if((GET_TYPE_C_0_PD_SYS_EVENT() & _PD_SYS_EVENT_ERROR_RECOVERY) == _PD_SYS_EVENT_ERROR_RECOVERY)
    {
        SET_TYPE_C_0_CC_ERROR_RECOVERY();
    }
    else
    {
        SET_TYPE_C_0_PD_SYS_EVENT(enumPdSysEvent);
    }

    // Update Port Controller Event to inform System / User of Specific Events Occurred
    if((GET_TYPE_C_0_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
    {
        SET_TYPE_C_0_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_POWER_OCP);
    }

    if((GET_TYPE_C_0_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
    {
        SET_TYPE_C_0_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_POWER_OVP);
    }

    if((GET_TYPE_C_0_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_UVP) == _PD_SYS_EVENT_POWER_UVP)
    {
        SET_TYPE_C_0_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_POWER_UVP);
    }

    if((GET_TYPE_C_0_PD_SYS_EVENT() & _PD_SYS_EVENT_VCONN_OCP) == _PD_SYS_EVENT_VCONN_OCP)
    {
        SET_TYPE_C_0_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_VCONN_OCP);
    }
}

//--------------------------------------------------
// Description  : Push HPD into HPD Queue @ WD Timer
// Input Value  : enumHpdType : _PD_HPD_LOW / _PD_HPD_HIGH..., HPD Space Time(ms)
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0PdPushHpd_WDINT(EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime)
{
    BYTE ucIndex = 0;

    // Push Queue Only Vlid When Alt Mode is Ready
    if(GET_TYPE_C_0_PD_DP_ALT_MODE_ENTER() != _TRUE)
    {
        return;
    }

    switch(enumHpdType)
    {
        case _PD_HPD_LOW:

            for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
            {
                SET_TYPE_C_0_PD_HPD_QUEUE(_PD_HPD_NONE);
                SET_TYPE_C_0_PD_HPD_SPACE_TIME(0);
                ADD_TYPE_C_0_PD_HPD_WPTR();
            }

            CLR_TYPE_C_0_PD_HPD_WPTR();
            CLR_TYPE_C_0_PD_HPD_RPTR();
            CLR_TYPE_C_0_PD_HPD_CNT();

            SET_TYPE_C_0_PD_HPD_QUEUE(_PD_HPD_LOW);
            SET_TYPE_C_0_PD_HPD_SPACE_TIME(usHpdSpaceTime);

            ADD_TYPE_C_0_PD_HPD_WPTR();
            ADD_TYPE_C_0_PD_HPD_CNT();

            break;

        case _PD_HPD_HIGH:

            if((GET_TYPE_C_0_PD_HPD_CNT() == 0) || (GET_TYPE_C_0_PD_HPD_QUEUE((GET_TYPE_C_0_PD_HPD_WPTR() + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_HIGH))
            {
                SET_TYPE_C_0_PD_HPD_QUEUE(_PD_HPD_HIGH);
                SET_TYPE_C_0_PD_HPD_SPACE_TIME(usHpdSpaceTime);

                ADD_TYPE_C_0_PD_HPD_WPTR();
                ADD_TYPE_C_0_PD_HPD_CNT();
            }

            break;

        case _PD_HPD_IRQ:

            // Make sure HPD_IRQ has a minumun spacing time of 10ms (DP Alt Mode 5.2.2)
            usHpdSpaceTime = (usHpdSpaceTime < _ATTENTION_SPACING_TIMER) ? _ATTENTION_SPACING_TIMER : usHpdSpaceTime;

            if(GET_TYPE_C_0_PD_HPD_CNT() <= 1)
            {
                SET_TYPE_C_0_PD_HPD_QUEUE(_PD_HPD_IRQ);
                SET_TYPE_C_0_PD_HPD_SPACE_TIME(usHpdSpaceTime);

                ADD_TYPE_C_0_PD_HPD_WPTR();
                ADD_TYPE_C_0_PD_HPD_CNT();
            }
            else
            {
                // If Last 2 HPDs are Not Both HPD_IRQs, Push New HPD_IRQ
                if((GET_TYPE_C_0_PD_HPD_QUEUE((GET_TYPE_C_0_PD_HPD_WPTR() + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ) ||
                   (GET_TYPE_C_0_PD_HPD_QUEUE((GET_TYPE_C_0_PD_HPD_WPTR() + _HPD_QUEUE_DEPTH - 2) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ))
                {
                    SET_TYPE_C_0_PD_HPD_QUEUE(_PD_HPD_IRQ);
                    SET_TYPE_C_0_PD_HPD_SPACE_TIME(usHpdSpaceTime);

                    ADD_TYPE_C_0_PD_HPD_WPTR();
                    ADD_TYPE_C_0_PD_HPD_CNT();
                }
            }

            break;

        default:

            break;
    }
}

#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT))

