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
// ID Code      : ScalerTypeCTcpm_EXINT0.c No.0000
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
volatile BYTE g_pucTypeCTcpmRxBuffer_EXINT[(_MAX_DATA_OBJ_CNT * 4) + 4];   // READABLE_BYTE_CNT + FRAME_TYPE + Message_Header_L + Message_Header_H + Data Object
volatile BYTE g_pucTypeCTcpmPdDataObj_EXINT[_MAX_DATA_OBJ_CNT * 4];


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Interrupt Process For Type C TCPM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmIntHandler_EXINT0(void)
{
#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_0_SUPPORT == _ON)
    // ==================== "TCPM0 IRQ" =========================
    // [0xFA12] [7] tcpm_irq, [6] tcpm_irq_en
    if(ScalerGetBit_EXINT(PFA_12_TCPM_RELATED_IRQ_1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        // [FW Solution] Avoid HW Trigger Auto Read before FW Using I2C, This will Cause TCPM HW Reset and Trigger Auto Read Again.

#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        BYTE ucTcpm00PortIndex = ScalerTypeCTcpmGetPortIndex_EXINT0(_HW_TCPM_0_0_MAPPING);
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        BYTE ucTcpm01PortIndex = ScalerTypeCTcpmGetPortIndex_EXINT0(_HW_TCPM_0_1_MAPPING);
#endif

#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)

        // 1-1. Disable TCPM_0_0 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_EXINT0(ucTcpm00PortIndex, _DISABLE);

        // 1-2. Clear All Alert Valid
        SET_TCPM_ALERT_VALID(ucTcpm00PortIndex, _TCPM_TCPCI_ALERT_NONE);

        // 1-3. Record all TCPM_0_0 Alert IRQ & Auto Read Reg
        // [0xFA12] [3] tcpc_0_irq, [2] tcpc_0_irq_en
        if(ScalerGetBit_EXINT(PFA_12_TCPM_RELATED_IRQ_1, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
        {
            ScalerTypeCTcpmCheckAlertValid_EXINT0(ucTcpm00PortIndex);
        }
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 2-1. Disable TCPM_0_1 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_EXINT0(ucTcpm01PortIndex, _DISABLE);

        // 2-2. Clear All Alert Valid
        SET_TCPM_ALERT_VALID(ucTcpm01PortIndex, _TCPM_TCPCI_ALERT_NONE);

        // 2-3. Record all TCPM_0_1 Alert IRQ & Auto Read Reg
        // [0xFA12] [1] tcpc_1_irq, [0] tcpc_1_irq_en
        if(ScalerGetBit_EXINT(PFA_12_TCPM_RELATED_IRQ_1, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            ScalerTypeCTcpmCheckAlertValid_EXINT0(ucTcpm01PortIndex);
        }
#endif

#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 3. Processing TCPM_0_0 Int Handler
        if(GET_TCPM_ALERT_VALID(ucTcpm00PortIndex) != _TCPM_TCPCI_ALERT_NONE)
        {
            ScalerTypeCTcpmAlertIntHandler_EXINT0(ucTcpm00PortIndex);
        }
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 4. Processing TCPM_0_1 Int Handler
        if(GET_TCPM_ALERT_VALID(ucTcpm01PortIndex) != _TCPM_TCPCI_ALERT_NONE)
        {
            ScalerTypeCTcpmAlertIntHandler_EXINT0(ucTcpm01PortIndex);
        }
#endif

#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 5. Enable TCPM_0_0 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_EXINT0(ucTcpm00PortIndex, _ENABLE);
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 5. Enable TCPM_0_1 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_EXINT0(ucTcpm01PortIndex, _ENABLE);
#endif
    }
#endif // End of #if(_HW_TCPM_0_SUPPORT == _ON)

#if(_HW_TCPM_1_SUPPORT == _ON)
    // ==================== "TCPM1 IRQ" =========================
    // [0xFB12] [7] tcpm_irq, [6] tcpm_irq_en
    if(ScalerGetBit_EXINT(PFB_12_TCPM_RELATED_IRQ, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        // [FW Solution] Avoid HW Trigger Auto Read before FW Using I2C, This will Cause TCPM HW Reset and Trigger Auto Read Again.

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        BYTE ucTcpm10PortIndex = ScalerTypeCTcpmGetPortIndex_EXINT0(_HW_TCPM_1_0_MAPPING);
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        BYTE ucTcpm11PortIndex = ScalerTypeCTcpmGetPortIndex_EXINT0(_HW_TCPM_1_1_MAPPING);
#endif

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 1-1. Disable TCPM_1_0 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_EXINT0(ucTcpm10PortIndex, _DISABLE);

        // 1-2. Clear All Alert Valid
        SET_TCPM_ALERT_VALID(ucTcpm10PortIndex, _TCPM_TCPCI_ALERT_NONE);

        // 1-3. Record all TCPM_1_0 Alert IRQ & Auto Read Reg
        // [0xFB12] [3] tcpc_0_irq, [2] tcpc_0_irq_en
        if(ScalerGetBit_EXINT(PFB_12_TCPM_RELATED_IRQ, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
        {
            ScalerTypeCTcpmCheckAlertValid_EXINT0(ucTcpm10PortIndex);
        }
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 2-1. Disable TCPM_1_1 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_EXINT0(ucTcpm11PortIndex, _DISABLE);

        // 2-2. Clear All Alert Valid
        SET_TCPM_ALERT_VALID(ucTcpm11PortIndex, _TCPM_TCPCI_ALERT_NONE);

        // 2-3. Record all TCPM_1_1 Alert IRQ & Auto Read Reg
        // [0xFB12] [1] tcpc_1_irq, [0] tcpc_1_irq_en
        if(ScalerGetBit_EXINT(PFB_12_TCPM_RELATED_IRQ, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            ScalerTypeCTcpmCheckAlertValid_EXINT0(ucTcpm11PortIndex);
        }
#endif

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 3. Processing TCPM_1_0 Int Handler
        if(GET_TCPM_ALERT_VALID(ucTcpm10PortIndex) != _TCPM_TCPCI_ALERT_NONE)
        {
            ScalerTypeCTcpmAlertIntHandler_EXINT0(ucTcpm10PortIndex);
        }
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 4. Processing TCPM_1_1 Int Handler
        if(GET_TCPM_ALERT_VALID(ucTcpm11PortIndex) != _TCPM_TCPCI_ALERT_NONE)
        {
            ScalerTypeCTcpmAlertIntHandler_EXINT0(ucTcpm11PortIndex);
        }
#endif

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 5. Enable TCPM_1_0 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_EXINT0(ucTcpm10PortIndex, _ENABLE);
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
        // 5. Enable TCPM_1_1 Alert Det
        ScalerTypeCTcpmAlertDetCtrl_EXINT0(ucTcpm11PortIndex, _ENABLE);
#endif
    }
#endif // End of #if(_HW_TCPM_1_SUPPORT == _ON)

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Interrupt Process When Type C TCPM Detect Alert Low
// Input Value  : enumTypeCPcbPort
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmAlertIntHandler_EXINT0(BYTE ucPortIndex)
{
    // ------------------------------
    // ALERT.[9] FAULT_STATUS Process
    // ------------------------------
    if((GET_TCPM_ALERT_VALID(ucPortIndex) & _TCPM_TCPCI_ALERT_FAULT) == _TCPM_TCPCI_ALERT_FAULT)
    {
        // Clear Alert Valid
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) & (~(_TCPM_TCPCI_ALERT_FAULT))));

        if((GET_TCPM_FAULT_STATUS(ucPortIndex) & _TCPM_TCPCI_FT_STAT_VCONN_OCP) == _TCPM_TCPCI_FT_STAT_VCONN_OCP)
        {
            // 1. Turn Off Vconn
            // 2. Clear Fault Status (Vconn OCP) & Disable Fault Status (Vconn OCP) Mask
            ScalerTypeCTcpmVconnCtrl_EXINT0(ucPortIndex, _OFF);

            // 3. Set Vconn OCP System Event
            ScalerTypeCTcpmSetPdSystemEvent_EXINT0(ucPortIndex, _PD_SYS_EVENT_VCONN_OCP);
        }

#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
        if((GET_TCPM_FAULT_STATUS(ucPortIndex) & _TCPM_TCPCI_FT_STAT_VBUS_OCP) == _TCPM_TCPCI_FT_STAT_VBUS_OCP)
        {
            // 1. Turn off Vbus
            // 2. Clear Fault Status (Vbus OCP) & Disable Fault Status (Vbus OCP) Mask
            ScalerTypeCTcpmVbusCtrl_EXINT0(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

            // Set OCP Event
            ScalerTypeCTcpmSetPdSystemEvent_EXINT0(ucPortIndex, _PD_SYS_EVENT_POWER_OCP);
        }
#endif

        // Clear and Disable ALERT.FAULT
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_FAULT), _DISABLE);
    }

    // ------------------------------
    // ALERT.[0] CC_STATUS Process
    // ------------------------------
    if((GET_TCPM_ALERT_VALID(ucPortIndex) & _TCPM_TCPCI_ALERT_CC_STATUS) == _TCPM_TCPCI_ALERT_CC_STATUS)
    {
        // Clear Alert Valid
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) & (~(_TCPM_TCPCI_ALERT_CC_STATUS))));

        // Clear and Enable ALERT.CC_STATUS
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_CC_STATUS, _ENABLE);

        // Read CC Status [0x1D] Info
        SET_TCPM_CC_STATUS(ucPortIndex, ScalerTypeCTcpmGetCcStatus_EXINT0(ucPortIndex));

        SET_TCPM_CC_STATUS_CHG(ucPortIndex);

        switch(GET_TCPM_CC_FSM(ucPortIndex))
        {
            case _TCPM_CC_FSM_DRP_TOGGLE:

                // Check TCPM is Asking TCPC to Look 4 Connection and Find the Potential Connection
                ScalerTypeCTcpmCcDrpToggleProc_EXINT0(ucPortIndex);

                break;

            case _TCPM_CC_FSM_UNATTACH_SNK:

                // Unattach.SRC Process
                ScalerTypeCTcpmCcUnattachSnkProc_EXINT0(ucPortIndex);

                break;

            case _TCPM_CC_FSM_ATTACH_WAIT_SNK:

                // AttachWait.SNK Process
                ScalerTypeCTcpmCcAttachWaitSnkProc_EXINT0(ucPortIndex);

                break;

            case _TCPM_CC_FSM_ATTACH_SNK:

                // Attach.SNK Process
                ScalerTypeCTcpmCcAttachSnkProc_EXINT0(ucPortIndex);

                break;

            case _TCPM_CC_FSM_UNATTACH_SRC:

                // Unattach.SRC Process
                ScalerTypeCTcpmCcUnattachSrcProc_EXINT0(ucPortIndex);

                break;

            case _TCPM_CC_FSM_ATTACH_WAIT_SRC:

                // AttachWait.SRC Process
                ScalerTypeCTcpmCcAttachWaitSrcProc_EXINT0(ucPortIndex);

                break;

            case _TCPM_CC_FSM_ATTACH_SRC:

                // Attach.SRC Process
                ScalerTypeCTcpmCcAttachSrcProc_EXINT0(ucPortIndex);

                break;

            default:

                // Disable ALERT.CC_STATUS
                ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_CC_STATUS, _DISABLE);

                break;
        }

        CLR_TCPM_CC_STATUS_CHG(ucPortIndex);
    }

    // ------------------------------
    // ALERT.[7] VBUS_ALRM_H Process
    // ------------------------------
    if((GET_TCPM_ALERT_VALID(ucPortIndex) & _TCPM_TCPCI_ALERT_VBUS_ALRM_H) == _TCPM_TCPCI_ALERT_VBUS_ALRM_H)
    {
        // Clear Alert Valid
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) & (~(_TCPM_TCPCI_ALERT_VBUS_ALRM_H))));

        // Clear and Disable ALERT.VBUS_ALRM_H
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_VBUS_ALRM_H, _DISABLE);

        if(GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_WAIT_SNK)
        {
            SET_TCPM_CC_SNK_DET_5V(ucPortIndex);

            // From AttachWait.SNK and tCcDebounce Done
            ScalerTypeCTcpmCcAttachWaitSnkProc_EXINT0(ucPortIndex);
        }

        if(GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_WAIT_SRC)
        {
            SET_TCPM_CC_SRC_DET_5V(ucPortIndex);

            // From AttachWait.SRC Detect vSafe0V and Turn on Vbus
            ScalerTypeCTcpmCcAttachWaitSrcProc_EXINT0(ucPortIndex);
        }

        // From Hard Reset After : (1)Source Turned Off Vbus (2) Sink Detect Vbus Off, Wait Vbus On
        if(GET_TCPM_PD_HRST_PWR_OFF(ucPortIndex) == _TRUE)
        {
            if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
            {
                // Attach Setting for PD Function in POWER_SRC
                ScalerTypeCTcpmPdAttachSetting_EXINT0(ucPortIndex, _PD_POWER_SRC);
            }
            else
            {
                // Setup Auto Discharge (Unattach) Start Thr.(3.65V)
                ScalerTypeCTcpmCcUnattachVthAdjust_EXINT0(ucPortIndex, 500);

                // Enable Sinking Vbus
                ScalerTypeCTcpmVbusCtrl_EXINT0(ucPortIndex, _ON, _PD_POWER_SNK, _PD_FIX_SUPPLY_PDO, 500, 0, _PD_PEAK_CUR_NONE);

                // Start PMIC Protection
                ScalerTypeCTcpmVbusProtectStart_EXINT0(ucPortIndex, _TYPE_C_POWER_SNK);

                // Attach Setting for PD Function in POWER_SNK
                ScalerTypeCTcpmPdAttachSetting_EXINT0(ucPortIndex, _PD_POWER_SNK);

                // Enable Sink Detect Disconnect (Disabled When Sending/Rcving HRST)
                ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_SNK_DISC), _ENABLE);
            }
        }
    }

    // ------------------------------
    // ALERT.[8] VBUS_ALRM_L Process
    // ------------------------------
    if((GET_TCPM_ALERT_VALID(ucPortIndex) & _TCPM_TCPCI_ALERT_VBUS_ALRM_L) == _TCPM_TCPCI_ALERT_VBUS_ALRM_L)
    {
        // Clear Alert Valid
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) & (~(_TCPM_TCPCI_ALERT_VBUS_ALRM_L))));

        // Clear and Disable ALERT.VBUS_ALRM_L
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_VBUS_ALRM_L, _DISABLE);

        if(GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_WAIT_SRC)
        {
            SET_TCPM_CC_SRC_DET_0V(ucPortIndex);

            // from AttachWait.SRC and tCcDebounce Done
            ScalerTypeCTcpmCcAttachWaitSrcProc_EXINT0(ucPortIndex);
        }
    }

    // ------------------------------
    // ALERT.[11] VBUS_SINK_DISCONNECT Process
    // ------------------------------
    if((GET_TCPM_ALERT_VALID(ucPortIndex) & _TCPM_TCPCI_ALERT_SNK_DISC) == _TCPM_TCPCI_ALERT_SNK_DISC)
    {
        // Clear Alert Valid
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) & (~(_TCPM_TCPCI_ALERT_SNK_DISC))));

        // Clear and Disable ALERT.VBUS_SNK_DISC
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_SNK_DISC, _DISABLE);

        // TCPC Detect Sink Disconnect, Cancel FW CC Status Open Debounce (tPDDeounce)
        ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);

        ScalerTypeCTcpmCcUnattachSetting_EXINT0(ucPortIndex);
    }

    // ------------------------------
    // ALERT.[6] TX_SUCCESS Process + ALERT.[4] TX_FAIL Process (Send Hard Reset)
    // ------------------------------
    if((GET_TCPM_ALERT_VALID(ucPortIndex) & (_TCPM_TCPCI_ALERT_TX_SUCCESS | _TCPM_TCPCI_ALERT_TX_FAIL)) == (_TCPM_TCPCI_ALERT_TX_SUCCESS | _TCPM_TCPCI_ALERT_TX_FAIL))
    {
        // Clear Alert Valid
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) & (~(_TCPM_TCPCI_ALERT_TX_SUCCESS | _TCPM_TCPCI_ALERT_TX_FAIL))));

        // Clear and Disable ALERT.Tx_SUCCESS & ALERT.Tx_FAIL
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_TX_SUCCESS | _TCPM_TCPCI_ALERT_TX_FAIL), _DISABLE);
    }

    // [Warning] Tx Alert Should Servise Before Rx Alert to Prevent from Enter INT too Late and Port Partner Already Response
    // ------------------------------
    // ALERT.[6] TX_SUCCESS Process
    // ------------------------------
    if((GET_TCPM_ALERT_VALID(ucPortIndex) & _TCPM_TCPCI_ALERT_TX_SUCCESS) == _TCPM_TCPCI_ALERT_TX_SUCCESS)
    {
        // Clear Alert Valid
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) & (~(_TCPM_TCPCI_ALERT_TX_SUCCESS))));

        // Clear and Re-Enable ALERT.Tx_SUCCESS
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_TX_SUCCESS), _ENABLE);

        ScalerTypeCTcpmPdIntTxSuccessProc_EXINT0(ucPortIndex);

        // --------------- [Warning] On-Semi -------------
        // TCPC Dose Not Detect Unattach When "Unattach" Happens During PD Rcv/Sending Message
        // Set Flag for Main Loop to Check CC Status
        if((GET_TCPM_TCPC_TYPE(ucPortIndex) == _TCPC_ON_SEMI) && (GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_SNK))
        {
            SET_TCPM_CC_SNK_DET_UNATTACH(ucPortIndex);
        }
    }

    // ------------------------------
    // ALERT.[4] TX_FAIL Process
    // ------------------------------
    if((GET_TCPM_ALERT_VALID(ucPortIndex) & _TCPM_TCPCI_ALERT_TX_FAIL) == _TCPM_TCPCI_ALERT_TX_FAIL)
    {
        // Clear Alert Valid
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) & (~(_TCPM_TCPCI_ALERT_TX_FAIL))));

        // Clear and Re-Enable ALERT.Tx_FAIL
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_TX_FAIL), _ENABLE);

        ScalerTypeCTcpmPdIntTxFailProc_EXINT0(ucPortIndex);
    }

    // ------------------------------
    // ALERT.[5] TX_DISCARD Process
    // ------------------------------
    if((GET_TCPM_ALERT_VALID(ucPortIndex) & _TCPM_TCPCI_ALERT_TX_DISCARD) == _TCPM_TCPCI_ALERT_TX_DISCARD)
    {
        // Clear Alert Valid
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) & (~(_TCPM_TCPCI_ALERT_TX_FAIL))));

        // Clear and Re-Enable ALERT.Tx_DISCARD
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_TX_DISCARD), _ENABLE);

        if((GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_SRC_READY) && (GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_SNK_READY))
        {
            // SET_TCPM_PD_FW_STATE(_PD_HARDRESET) in ScalerTypeCTcpmPdProcHardRst_EXINT0
            ScalerTypeCTcpmPdSendHardRst_EXINT0(ucPortIndex);
        }
        else
        {
            if((GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_USB_CONFIG) && (GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_INT_SEND_VDM_RESP) && (GET_TCPM_PD_VDM_RESP_CONFLICT_CNT(ucPortIndex) < 2))
            {
                ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, 1000, _SCALER_TIMER_EVENT_TCPM_VDM_RESP_CONFLICT_TIMEOUT);
            }

            // Set AMS = None
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

            // Back to Ready State
            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
        }
    }

    // ------------------------------
    // ALERT.[2] RX_RCV_SOP or ALERT.[10] RX_OVERFLOW Process
    // ------------------------------
    if((GET_TCPM_ALERT_VALID(ucPortIndex) & (_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_OVERFLOW)) != _TCPM_TCPCI_ALERT_NONE)
    {
        // 1. Clear Alert Valid
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) & (~(_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_OVERFLOW))));

        // 2. Clear and Re-Enable ALERT.Rx_RCV_SOP + ALERT.RX_Overflow
        // [Warning] TCPM Should Clear Rx Alert Before Writing Tx Buffer and Asking TCPC to Send Message
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_OVERFLOW), _ENABLE);

        // 3. Check Message ID
        if(ScalerTypeCTcpmPdRxMsgIdCheck_EXINT0(ucPortIndex) == _SUCCESS)
        {
            // Notify Main Loop that Send Msg Has Been Interrupted
            SET_TCPM_PD_INT_OVERWRITE(ucPortIndex);

            // 4. Decode Rcv. Msg
            ScalerTypeCTcpmPdRxMsgDecode_EXINT0(ucPortIndex);

            // 5. Process Received Message
            if(GET_TCPM_RX_BUF_FRAME_TYPE() == _TCPM_TCPCI_RX_FRAME_TYPE_SOP)
            {
                // Process SOP Packet
                if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_SOFT_RESET)
                {
                    ScalerTypeCTcpmPdRcvSoftRstProc_EXINT0(ucPortIndex);
                }
                else
                {
                    ScalerTypeCTcpmPdIntRcvMsgProc_EXINT0(ucPortIndex);
                }
            }
            else if((GET_TCPM_RX_BUF_FRAME_TYPE() == _TCPM_TCPCI_RX_FRAME_TYPE_SOP_P) ||
                    (GET_TCPM_RX_BUF_FRAME_TYPE() == _TCPM_TCPCI_RX_FRAME_TYPE_SOP_PP))
            {
                // Process SOP'/SOP" Packet
                ScalerTypeCTcpmPdIntRcvCableMsgProc_EXINT0(ucPortIndex);
            }
        }

        // --------------- [Warning] On-Semi -------------
        // TCPC Dose Not Detect Unattach When "Unattach" Happens During PD Rcv/Sending Message
        // Set Flag for Main Loop to Check CC Status
        if((GET_TCPM_TCPC_TYPE(ucPortIndex) == _TCPC_ON_SEMI) && (GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_SNK))
        {
            SET_TCPM_CC_SNK_DET_UNATTACH(ucPortIndex);
        }
    }

    // ------------------------------
    // ALERT.[3] RX_HRST Process
    // ------------------------------
    if((GET_TCPM_ALERT_VALID(ucPortIndex) & _TCPM_TCPCI_ALERT_RX_HRST) == _TCPM_TCPCI_ALERT_RX_HRST)
    {
        // 1. Clear Alert Valid
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) & (~(_TCPM_TCPCI_ALERT_RX_HRST))));

        // 2. Disable Tx, Rx, Sink Disconnect (TCPC Will Set TX_Success + TX_Discard After Sending HRST)
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_HRST | _TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS | _TCPM_TCPCI_ALERT_RX_OVERFLOW | _TCPM_TCPCI_ALERT_SNK_DISC), _DISABLE);

        // 3. Do TCPM Hard Reset Proc
        ScalerTypeCTcpmPdProcHardRst_EXINT0(ucPortIndex);

        // --------------- [Warning] On-Semi -------------
        // TCPC Dose Not Detect Unattach When "Unattach" Happens During PD Rcv/Sending Message
        // Set Flag for Main Loop to Check CC Status
        if((GET_TCPM_TCPC_TYPE(ucPortIndex) == _TCPC_ON_SEMI) && (GET_TCPM_CC_FSM(ucPortIndex) == _TCPM_CC_FSM_ATTACH_SNK))
        {
            SET_TCPM_CC_SNK_DET_UNATTACH(ucPortIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Get TCPM Port Index
// Input Value  : enumTypeCPcbPort
// Output Value : Type C TCPM Port Index
//--------------------------------------------------
BYTE ScalerTypeCTcpmGetPortIndex_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
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
// Description  : Type C TCPM Check which Alert set by TCPC
// Input Value  : ucPortIndex
// Output Value : Alert Set by TCPC
//--------------------------------------------------
WORD ScalerTypeCTcpmGetAlertType_EXINT0(BYTE ucPortIndex)
{
    WORD usAlertStatus = 0;

#if(_HW_TCPM_SUPPORT == _ON)

#if(_HW_TCPM_ALERT_AUTO_CTRL == _ON)
    usAlertStatus = TO_WORD(ScalerGetByte_EXINT(PFA_2B_TCPC_0_ALERT_VALID_H + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex)), ScalerGetByte_EXINT(PFA_2A_TCPC_0_ALERT_VALID_L + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex)));
#else
    usAlertStatus = (GET_TCPM_ALERT_MASK(ucPortIndex) & ScalerTypeCTcpmTcpciGetWord_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ALERT));
#endif // End of #if(_HW_TCPM_ALERT_AUTO_CTRL == _ON)

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    usAlertStatus = usAlertStatus;

#endif // End of (_HW_TCPM_SUPPORT == _ON)

    if(usAlertStatus == 0)
    {
        // TCPC Triggered Illegal Alert, Clear all Alert
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_ALL, _DISABLE);
    }

    return usAlertStatus;
}

//--------------------------------------------------
// Description  : Type C TCPM Get TCPC CC Status
// Input Value  : ucPortIndex
// Output Value : Alert Set by TCPC
//--------------------------------------------------
BYTE ScalerTypeCTcpmGetCcStatus_EXINT0(BYTE ucPortIndex)
{
    BYTE ucCcStatus = 0;

#if(_HW_TCPM_SUPPORT == _ON)

#if(_HW_TCPM_CS_AUTO_CTRL == _ON)
    ucCcStatus = ScalerGetByte_EXINT(PFA_33_TCPC_0_CC_STAT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex));
#else
    ucCcStatus = ScalerTypeCTcpmTcpciGetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_CC_STATUS);
#endif // End of #if(_HW_TCPM_CS_AUTO_CTRL == _ON)

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    ucCcStatus = ucCcStatus;

#endif // End of (_HW_TCPM_SUPPORT == _ON)

    return ucCcStatus;
}

//--------------------------------------------------
// Description  : Type C TCPM Get TCPC Fault Status
// Input Value  : ucPortIndex
// Output Value : Alert Set by TCPC
//--------------------------------------------------
BYTE ScalerTypeCTcpmGetFaultStatus_EXINT0(BYTE ucPortIndex)
{
    BYTE ucFaultStatus = 0;

#if(_HW_TCPM_SUPPORT == _ON)

#if(_HW_TCPM_FS_AUTO_CTRL == _ON)
    ucFaultStatus = (GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) & ScalerGetByte_EXINT(PFA_37_TCPC_0_FAULT_STAT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex)));
#else
    ucFaultStatus = (GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) & ScalerTypeCTcpmTcpciGetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS));
#endif // End of #if(_HW_TCPM_FS_AUTO_CTRL == _ON)

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    ucFaultStatus = ucFaultStatus;

#endif // End of (_HW_TCPM_SUPPORT == _ON)

    return ucFaultStatus;
}

//--------------------------------------------------
// Description  : Set TCPM System Event
// Input Value  : ucPortIndex, enumPdSysEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmSetPdSystemEvent_EXINT0(BYTE ucPortIndex, EnumTypeCPDSysEvent enumPdSysEvent)
{
    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_ERROR_RECOVERY) == _PD_SYS_EVENT_ERROR_RECOVERY)
    {
        SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
    }
    else
    {
        SET_TCPM_PD_SYS_EVENT(ucPortIndex, enumPdSysEvent);
    }

    // Update Port Controller Event to inform System / User of Specific Events Occurred
    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
    {
        SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_POWER_OCP);
    }

    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
    {
        SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_POWER_OVP);
    }

    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_UVP) == _PD_SYS_EVENT_POWER_UVP)
    {
        SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_POWER_UVP);
    }

    if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_VCONN_OCP) == _PD_SYS_EVENT_VCONN_OCP)
    {
        SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_VCONN_OCP);
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Check Alert Valid & Get Related Status
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCheckAlertValid_EXINT0(BYTE ucPortIndex)
{
#if(_HW_TCPM_SUPPORT == _ON)
    // Record CC Status IRQ : [0xFA32] [1] alert_cs_irq, [0] alert_cs_irq_en
    if(ScalerGetBit_EXINT(PFA_32_TCPC_0_CS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_CC_STATUS));

        // Read CC Status [0x1D] Info in ScalerTypeCTcpmAlertIntHandler_EXINT0 to Avoid CC Status Changes before TCPM Processes it.
    }

    // Record Power Status IRQ : [0xFA34] [1] alert_ps_irq, [0] alert_ps_irq_en
    if(ScalerGetBit_EXINT(PFA_34_TCPC_0_PS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_PWR_STATUS));
    }

    // Record Fault Status IRQ : [0xFA36] [1] alert_fault_irq, [0] alert_fault_irq_en
    if(ScalerGetBit_EXINT(PFA_36_TCPC_0_FS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_FAULT));

        // Read Fault Status [0x1F] Info
        SET_TCPM_FAULT_STATUS(ucPortIndex, ScalerTypeCTcpmGetFaultStatus_EXINT0(ucPortIndex));
    }

    // Record Extended Status IRQ : [0xFA38] [1] alert_ext_stat_irq, [0] alert_ext_stat_irq_en
    if(ScalerGetBit_EXINT(PFA_38_TCPC_0_ES_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_EXT_STATUS));
    }

    // Record Alert Extended IRQ : [0xFA3A] [1] alert_alert_ext_irq, [0] alert_alert_ext_irq_en
    if(ScalerGetBit_EXINT(PFA_3A_TCPC_0_ALERT_EXT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_ALERT_EXT));
    }

    // Record Vendor Define IRQ : [0xFA3C] [1] alert_vendor_def_irq, [0] alert_vendor_def_irq_en
    if(ScalerGetBit_EXINT(PFA_3C_TCPC_0_VENDOR_DEF_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_VENDOR_DEF));
    }

    // Record High-Voltage Alarm IRQ : [0xFA3F] [1] alert_valm_h_irq, [0] alert_valm_h_irq_en
    if(ScalerGetBit_EXINT(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_VBUS_ALRM_H));
    }

    // Record Low-Voltage Alarm IRQ : [0xFA3F] [3] alert_valm_l_irq, [2] alert_valm_l_irq_en
    if(ScalerGetBit_EXINT(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_VBUS_ALRM_L));
    }

    // Record Hard Reset IRQ : [0xFA43] [7] alert_hrst_irq, [6] alert_hrst_irq_en
    if(ScalerGetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_RX_HRST));
    }

    // Record Tx Fail IRQ : [0xFA43] [5] alert_tx_fail_irq, [4] alert_tx_fail_irq_en
    if(ScalerGetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        // Enable Rx Int
        ScalerTypeCTcpmRxIntControl_EXINT0(ucPortIndex, _ENABLE);

        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_TX_FAIL));
    }

    // Record Tx Discard IRQ : [0xFA43] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
    if(ScalerGetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        // Enable Rx Int
        ScalerTypeCTcpmRxIntControl_EXINT0(ucPortIndex, _ENABLE);

        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_TX_DISCARD));
    }

    // Record Tx Success IRQ : [0xFA43] [1] alert_tx_success_irq, [0] alert_tx_success_irq_en
    if(ScalerGetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Enable Rx Int
        ScalerTypeCTcpmRxIntControl_EXINT0(ucPortIndex, _ENABLE);

        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_TX_SUCCESS));
    }

    // Record Rx Msg IRQ : [0xFA48] [3] alert_rx_msg_irq, [2] alert_rx_msg_irq_en
    if(ScalerGetBit_EXINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_RX_RCV_SOP));

        // Read TCPC Rx Buffer
        ScalerTypeCTcpmTcpciGetRxBuffer_EXINT0(ucPortIndex);
    }

    // Record Rx Bgn IRQ : [0xFA48] [1] alert_rx_bgn_irq, [0] alert_rx_bgn_irq_en
    if(ScalerGetBit_EXINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_RX_SOP_BEGIN));

        // Read TCPC Rx Buffer
        ScalerTypeCTcpmTcpciGetRxBuffer_EXINT0(ucPortIndex);
    }

    // Record Rx Overflow IRQ : [0xFA44] [3] alert_rx_ov_irq, [2] alert_rx_ov_irq_en
    if(ScalerGetBit_EXINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_RX_OVERFLOW));

        // Read TCPC Rx Buffer
        ScalerTypeCTcpmTcpciGetRxBuffer_EXINT0(ucPortIndex);
    }

    // Record Sink Disconnect IRQ : [0xFA44] [1] alert_snk_disc_irq, [0] alert_snk_disc_irq_en
    if(ScalerGetBit_EXINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        SET_TCPM_ALERT_VALID(ucPortIndex, (GET_TCPM_ALERT_VALID(ucPortIndex) | _TCPM_TCPCI_ALERT_SNK_DISC));
    }

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Convert Tcpm Event ID to Event ID
// Input Value  : ucPortIndex, enumTcpmEventID
// Output Value : enumEventID
//--------------------------------------------------
EnumScalerTimerEventID ScalerTypeCTcpmEventIDMapping_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID)
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
EnumScalerWDTimerEventID ScalerTypeCTcpmWDEventIDMapping_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID)
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
void ScalerTypeCTcpmActiveTimerEvent_EXINT0(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmEventID enumTcpmEventID)
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
void ScalerTypeCTcpmCancelTimerEvent_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmEventID enumTcpmEventID)
{
    ScalerTimerCancelTimerEvent_EXINT0(ScalerTypeCTcpmEventIDMapping_EXINT0(ucPortIndex, enumTcpmEventID));

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
void ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(BYTE ucPortIndex, WORD usTime, EnumTypeCTcpmWDEventID enumTcpmWDEventID)
{
    ScalerTimerWDActivateTimerEvent_EXINT0(usTime, ScalerTypeCTcpmWDEventIDMapping_EXINT0(ucPortIndex, enumTcpmWDEventID));
}

//--------------------------------------------------
// Description  : Cancel Tcpm WD Timer Event
// Input Value  : ucPortIndex, enumTcpmWDEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmWDEventID enumTcpmWDEventID)
{
    ScalerTimerWDCancelTimerEvent_EXINT0(ScalerTypeCTcpmWDEventIDMapping_EXINT0(ucPortIndex, enumTcpmWDEventID));
}

//--------------------------------------------------
// Description  : Control Tcpm WD Time Not Exceed Max Time
// Input Value  : ucPortIndex, enumTcpmWDEventID
// Output Value : enumWDEventID
//--------------------------------------------------
WORD ScalerTypeCTcpmWDTimeCtrl_EXINT0(BYTE ucPortIndex, WORD usWDTime)
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
void ScalerTypeCTcpmVbusCtrl_EXINT0(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent)
{
#if(_TYPE_C_PMIC_SUPPORT == _ON)
    if(GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON)
    {
        ScalerTypeCTcpmPmicSetting_EXINT0(ucPortIndex, bAction, bPowerDirection, enumPdoType, usVoltage, usCurrent, enumPeakCurrent);
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
                    ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_EN_SRC_5V);

                    // ONSEMI_GPIO_1_CFG [0xA4] : [2] GPO_VAL : 0, [0] Output En = 1
                    // ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_A4, 0x01);

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
                ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_EN_SNK_VBUS);

                // ONSEMI_GPIO_1_CFG [0xA4] : [2] GPO_VAL : 0, [0] Output En = 1
                // ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_A4, 0x01);

                SET_TCPM_SNK_VBUS(ucPortIndex);
            }
        }
        else
        {
            // Disable Sourcing Vbus : COMMAND [0x23] : 0x66 (Disable Src 5V)
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_DIS_SRC_VBUS);

            // Disable Sinking Vbus : COMMAND [0x23] : 0x44 (Disable Snk Vbus)
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_DIS_SNK_VBUS);

            // ONSEMI_GPIO_1_CFG [0xA4] : [2] GPO_VAL : 1, [0] Output En = 1
            // ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_A4, 0x05);

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
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VBUS_OCP);

        // Disable Fault Status (Vbus OCP) Mask (0x15[3])
        SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) & (~(_TCPM_TCPCI_FT_STAT_VBUS_OCP)));
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
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
            ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
            CLR_TCPM_OVP_UVP_CHECK(ucPortIndex);
        }
        else
        {
            // Cancel Timer Event & Macro to Stop OVP / UVP Protect
            ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
            CLR_TCPM_OVP_UVP_CHECK(ucPortIndex);
        }
    }
#endif // End of #if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)

    if((bAction == _ON) && (bPowerDirection == _PD_POWER_SRC) && (usVoltage > 500))
    {
        // Tool Show Warning UI when We Provide Vbus > 5V
        ScalerTypeCTcpmToolWarningUIControl_EXINT0(_ENABLE);
    }
    else
    {
        // Tool Not Show Warning UI when We Provide Vbus <= 5V
        ScalerTypeCTcpmToolWarningUIControl_EXINT0(_DISABLE);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Detect Vbus On/Off to transit State
// Input Value  : ucPortIndex, bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVbusDetCtrl_EXINT0(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ENABLE)
    {
        // Enable TCPC Auto Discharge Disconnect (POWER_CONTROL [0x1C] [4] Auto Discharge Disconnect)
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT4));
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
    else
    {
        // Disable TCPC Auto Discharge Disconnect (POWER_CONTROL [0x1C] [4] Auto Discharge Disconnect)
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT4));
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Discharge Vbus
// Input Value  : ucPortIndex, bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVbusDischargeCtrl_EXINT0(BYTE ucPortIndex, bit bAction)
{
#if(_TYPE_C_PMIC_SUPPORT == _ON)
    if(GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON)
    {
        ScalerTypeCTcpmPmicVbusDischarge_EXINT0(ucPortIndex, bAction);
    }
    else
#endif
    {
        if(bAction == _ON)
        {
            // Enable TCPC Force Discharge (POWER_CONTROL [0x1C] [2] Force Discharge)
            SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT2));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
        }
        else
        {
            // Disable TCPC Force Discharge (POWER_CONTROL [0x1C] [2] Force Discharge)
            SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT2));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
        }
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Vbus Protection Start
// Input Value  : ucPortIndex, enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVbusProtectStart_EXINT0(BYTE ucPortIndex, EnumTypeCPowerRole enumPowerRole)
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
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VBUS_OCP);

        // Enable Fault Status (Vbus OCP) Mask (0x15[3])
        SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) | (_TCPM_TCPCI_FT_STAT_VBUS_OCP));
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
    }
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    // ========================================================
    // OVP/UVP Flow
    // ========================================================
    if(GET_TCPM_OVP_UVP_SUPPORT(ucPortIndex) == _ON)
    {
        // Active Timer Event to Detect OVP/UVP
        ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, 40, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
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
// Description  : Type C TCPM Control Vconn
// Input Value  : ucPortIndex, bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmVconnCtrl_EXINT0(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ON)
    {
        if(GET_TCPM_DEVICE_VCONN_OCP_CAP(ucPortIndex) == _TRUE)
        {
            // Clear Fault Status (Vconn OCP) (0x1F[1])
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VCONN_OCP);

            // Enable Fault Status (Vconn OCP) Mask (0x15[1])
            SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) | (_TCPM_TCPCI_FT_STAT_VCONN_OCP));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
        }

        // Turn On Vconn
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT0));
        SET_TCPM_SRC_VCONN(ucPortIndex);
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
    else
    {
        if(GET_TCPM_DEVICE_VCONN_OCP_CAP(ucPortIndex) == _TRUE)
        {
            // Clear Fault Status (Vconn OCP) (0x1F[1])
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS, _TCPM_TCPCI_FT_STAT_VCONN_OCP);

            // Disable Fault Status (Vconn OCP) Mask (0x15[1])
            SET_TCPM_FAULT_STATUS_MASK(ucPortIndex, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex) & (~(_TCPM_TCPCI_FT_STAT_VCONN_OCP)));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_FAULT_STATUS_MASK, GET_TCPM_FAULT_STATUS_MASK(ucPortIndex));
        }

        // Turn Off Vconn
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) & (~_BIT0));
        CLR_TCPM_SRC_VCONN(ucPortIndex);
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Control TCPC Alert and Alert Mask
// Input Value  : ucPortIndex, AlertType, Action (_ENABLE / _DISABLE)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmAlertControl_EXINT0(BYTE ucPortIndex, WORD usAlertType, bit bAction)
{
    WORD usTargetAlertMask = 0x00;

#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_ALERT_UPDATE == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _ENABLE) == _FAIL)
    {
        return;
    }

    // 2. Update Clear Alert Reg
    ScalerSetByte_EXINT(PFA_28_TCPC_0_CLR_ALERT_L + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usAlertType));
    ScalerSetByte_EXINT(PFA_29_TCPC_0_CLR_ALERT_H + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usAlertType >> 8));

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
    ScalerSetByte_EXINT(PFA_24_TCPC_0_ALERT_MASK_L + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usTargetAlertMask));
    ScalerSetByte_EXINT(PFA_25_TCPC_0_ALERT_MASK_H + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usTargetAlertMask >> 8));

    // 4. Start Alert Update (Do Not Need to Enable alert_update_irq_en)
    // [0xFA23] [2] tcpc_0_alert_update, [1] tcpc_0_alert_update_irq, [0] tcpc_0_alert_update_irq_en
    ScalerSetBit_EXINT(PFA_23_TCPC_0_ALERT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // 5. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);
#else
    // 1. Clear Alert
    ScalerTypeCTcpmTcpciSetWord_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ALERT, usAlertType);

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
    ScalerTypeCTcpmTcpciSetWord_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ALERT_MASK, usTargetAlertMask);
#endif // End of #if(_HW_TCPM_ALERT_UPDATE == _ON)

    // Enable / Disable Alert IRQ
    ScalerTypeCTcpmAlertIntControl_EXINT0(ucPortIndex, usAlertType, bAction);

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
void ScalerTypeCTcpmRxIntControl_EXINT0(BYTE ucPortIndex, bit b1Action)
{
#if(_HW_TCPM_SUPPORT == _ON)

    if(b1Action == _ENABLE)
    {
        // Enable Rx Msg IRQ [0xFA48] [2] alert_rx_msg_irq_en
        ScalerSetBit_EXINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT2);

        // Enable Rx Overflow IRQ [0xFA44] [2] alert_rx_ov_irq_en
        ScalerSetBit_EXINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT2);
    }
    else
    {
        // Disable Rx Msg IRQ [0xFA48] [2] alert_rx_msg_irq_en
        ScalerSetBit_EXINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), 0x00);

        // Disable Rx Overflow IRQ [0xFA44] [2] alert_rx_ov_irq_en
        ScalerSetBit_EXINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), 0x00);
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
void ScalerTypeCTcpmToolWarningUIControl_EXINT0(bit bAction)
{
    // Tool Usage : [0xFA0E] [4] Used to Decide Whether Tool shall Show Warning UI when Disable Unattach HW Force Vbus Off Function([3]=0), 0 = Not Show UI, 1 = Show UI
    if(bAction == _ENABLE)
    {
        ScalerSetBit_EXINT(PFA_0E_DUMMY_1, ~_BIT4, _BIT4);
    }
    else
    {
        ScalerSetBit_EXINT(PFA_0E_DUMMY_1, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Interrupt Process For CC (DRP_TOGGLE) State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcDrpToggleProc_EXINT0(BYTE ucPortIndex)
{
    if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_L4C) == 0x00)
    {
        if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CONNECT_RESULT) == 0x00)
        {
            ScalerTypeCTcpmCcAttachWaitSrcCheck_EXINT0(ucPortIndex);
        }
        else
        {
            ScalerTypeCTcpmCcAttachWaitSnkCheck_EXINT0(ucPortIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Interrupt Process For CC (UNATTACH_SNK) State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcUnattachSnkProc_EXINT0(BYTE ucPortIndex)
{
    if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_L4C) == 0x00)
    {
        if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CONNECT_RESULT) != 0x00)
        {
            ScalerTypeCTcpmCcAttachWaitSnkCheck_EXINT0(ucPortIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Check Unattach.SRC -> AttachWait.SRC Condition
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcAttachWaitSnkCheck_EXINT0(BYTE ucPortIndex)
{
    // CC_STATUS [4] = b'1 = TCPC Apply Rd (SNK)
    SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_ATTACH_WAIT_SNK);

    // Check Condition : Unattach.SNK -> AttachWait.SNK
    // Refer to CC Spec Ver2.1 (4.5.2.2.3.2) : CC1 or CC2 = Rp
    if((((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) != 0x00) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) == 0x00)) ||
       (((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) == 0x00) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) != 0x00)))
    {
        // Sink Detect (Rp + Open) or (Open + Rp)
        SET_TCPM_CC_SRC_DET(ucPortIndex);

        // Start tCcDebounce
        CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
        ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _TCPM_CC_DEBOUNCE_TIME, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);

        // Cancel tPdDebounce
        CLR_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex);
        ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);
    }
    else if(((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) == 0x00) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) == 0x00))
    {
        // Sink Detect Open + Open : Unattach Detected
        CLR_TCPM_CC_SRC_DET(ucPortIndex);

        // Cancel tCcDebounce
        CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
        ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);

        // Debounce for tPdDebounce
        SET_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex);
        ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _TCPM_PD_DEBOUNCE_TIME, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);
    }
    else
    {
        // Not Valid Source Detect for Attached.SNK, nor Source Remove for Unattach.SNK
        // Sink Detect Rp + Rp : Stay in AttachWait.SNK and Wait for CC Status Change
        CLR_TCPM_CC_SRC_DET(ucPortIndex);

        // Cancel tCcDebounce
        CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
        ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);

        // Cancel tPdDebounce
        CLR_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex);
        ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);
    }
}

//--------------------------------------------------
// Description  : Interrupt Process For CC (ATTACH_WAIT_SNK) State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcAttachWaitSnkProc_EXINT0(BYTE ucPortIndex)
{
    if(GET_TCPM_CC_STATUS_CHG(ucPortIndex) == _TRUE)
    {
        // CC Status Change in AttachWait.SNK, Re-Judge Source Detect and Re-Start tCcDebounce
        // Refer to CC Spec Ver2.1 (4.5.2.2.3.2) : CC1 or CC2 = Rp
        if((((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) != 0x00) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) == 0x00)) ||
           (((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) == 0x00) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) != 0x00)))
        {
            // Sink Detecting (Rp + Open) or (Open + Rp)
            // if Source Already Detected, Could be Attach.SRC Toggle Rp between Rp-Def, Rp-1.5, Rp-3.0
            // if Source Not Detected Yet, Set Valid Source Detected, and Start tCcDebounce
            if(GET_TCPM_CC_SRC_DET(ucPortIndex) == _FALSE)
            {
                // Sink Detect (Rp + Open) or (Open + Rp) : Valid Source Detected, Start tCcDebounce
                SET_TCPM_CC_SRC_DET(ucPortIndex);

                // Start tCcDebounce
                CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
                ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _TCPM_CC_DEBOUNCE_TIME, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);

                // Cancel tPdDebounce
                CLR_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex);
                ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);
            }
        }
        else if(((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) == 0x00) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) == 0x00))
        {
            // Sink Detect Open + Open : Unattach Detected
            CLR_TCPM_CC_SRC_DET(ucPortIndex);

            // Disable Vbus_Alarm Detection
            SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT5));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));

            // Disable ALERT.VBUS_ALRM_H
            ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_VBUS_ALRM_H, _DISABLE);

            // Cancel tCcDebounce
            CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);

            // Debounce for tPdDebounce
            SET_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex);
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _TCPM_PD_DEBOUNCE_TIME, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);
        }
        else
        {
            // Not Valid Source Detect for Attached.SNK, nor Source Remove for Unattach.SNK
            // Sink Detect Rp + Rp : Stay in AttachWait.SNK and Wait for CC Status Change
            CLR_TCPM_CC_SRC_DET(ucPortIndex);

            // Disable Vbus_Alarm Detection
            SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT5));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));

            // Disable ALERT.VBUS_ALRM_H
            ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_VBUS_ALRM_H, _DISABLE);

            // Cancel tCcDebounce
            CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);

            // Cancel tPdDebounce
            CLR_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex);
            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);
        }
    }
    else
    {
        // Check if AttachWait.SNK -> Attach.SNK condition is Statisfied : (Source Detect for tCcDebounce) & (Vbus Detect)
        if((GET_TCPM_CC_SRC_DET(ucPortIndex) == _TRUE) && (GET_TCPM_CC_TCCDEBOUNCE(ucPortIndex) == _TRUE) && (GET_TCPM_CC_SNK_DET_5V(ucPortIndex) == _TRUE))
        {
            // Attach Setting for CC Function in POWER_SNK
            if(ScalerTypeCTcpmCcSnkAttachSetting_EXINT0(ucPortIndex) == _TRUE)
            {
                if(GET_TCPM_PD_FUNCTION_EN(ucPortIndex) == _TRUE)
                {
                    // Attach Setting for PD Function in POWER_SNK
                    ScalerTypeCTcpmPdAttachSetting_EXINT0(ucPortIndex, _PD_POWER_SNK);
                }

                // Turn On U3 & Hub Function
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                {
                    ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToDx_EXINT0(g_penumTypeCTcpmPort[ucPortIndex]), _TYPE_C_PIN_ASSIGNMENT_NONE, GET_TCPM_ORIENTATION(ucPortIndex));
                }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                {
                    ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToPx_EXINT0(g_penumTypeCTcpmPort[ucPortIndex]), _TYPE_C_PIN_ASSIGNMENT_NONE, GET_TCPM_ORIENTATION(ucPortIndex));
                }
#endif

                // SET FSM to ATTACH_SNK
                SET_TCPM_CC_ATTACHED(ucPortIndex);
                SET_TCPM_CC_FW_STATE(ucPortIndex, _TCPM_CC_FW_ATTACHED);
                SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_ATTACH_SNK);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Interrupt Process For CC (ATTACH_SNK) State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcAttachSnkProc_EXINT0(BYTE ucPortIndex)
{
    BYTE ucCcStatus = 0x00;

    if(GET_TCPM_CC_STATUS_CHG(ucPortIndex) == _TRUE)
    {
        if(GET_TCPM_ORIENTATION(ucPortIndex) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Un-Flip : ChecK CC1 Rp Value (CC_STATUS [0x1D] [1:0] CC1_STATE)
            ucCcStatus = (GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE);
        }
        else
        {
            // Flip : Check CC2 Rp Value (CC_STATUS [0x1D] [3:2] CC2_STATE)
            ucCcStatus = ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) >> 2);
        }

        if(ucCcStatus == 0x00)
        {
            // CC Pin = Open (b'00), Start tPdDebounce
            CLR_TCPM_CC_SRC_DET(ucPortIndex);

            // Debounce for tPdDebounce
            SET_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex);
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _TCPM_PD_DEBOUNCE_TIME, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);
        }
        else
        {
            // CC Pin != Open (b'00)
            if(GET_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex) == _TRUE)
            {
                // if Sink is Doing Unattach Debounce, Cancel tPdDebounce
                SET_TCPM_CC_SRC_DET(ucPortIndex);

                // Cancel tPdDebounce
                CLR_TCPM_CC_SNK_UNATTACH_DBC(ucPortIndex);
                ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Interrupt Process For CC Entry into Attached.SNK State
// Input Value  : ucPortIndex
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCTcpmCcSnkAttachSetting_EXINT0(BYTE ucPortIndex)
{
    // For Align "ScalerTypeCTcpmCcSrcAttachSetting_EXINT0", Sink Always Return _TRUE
    BYTE ucSnkAttachValid = _TRUE;

    // 1. Check CC Pin to Judge Orientation : CC_STATUS [0x1D]
    if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) != 0x00)
    {
        // 1-1. [1:0] CC1 != b'00 (Open) : Orientation = Unflip
        SET_TCPM_ORIENTATION(ucPortIndex, _TYPE_C_ORIENTATION_UNFLIP);

        // 2. Apply Rd on CC1 : ROLE_CONTROL [0x1A], [6] DRP :0, [3:2] CC2 = b'11 (Open), [1:0] CC1 = b'10 (Rd)
        SET_TCPM_ROLE_CONTROL(ucPortIndex, (GET_TCPM_ROLE_CONTROL(ucPortIndex) & (~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0))) | (_BIT3 | _BIT2 | _BIT1));
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

        // 3. Set Orientation to TCPC : TCPC_CONTROL [0x19], [0] = b'0 (CC1 = BMC, CC2 = Vconn)
        SET_TCPM_TCPC_CONTROL(ucPortIndex, GET_TCPM_TCPC_CONTROL(ucPortIndex) & (~_BIT0));
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_TCPC_CTRL, GET_TCPM_TCPC_CONTROL(ucPortIndex));
    }
    else if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) != 0x00)
    {
        // 1-1. [3:2] CC2 != b'00 (Open) : Orientation = Flip
        SET_TCPM_ORIENTATION(ucPortIndex, _TYPE_C_ORIENTATION_FLIP);

        // 2. Apply Rd on CC2 : ROLE_CONTROL [0x1A], [6] DRP :0, [3:2] CC2 = b'10 (Rd), [1:0] CC1 = b'11 (Open)
        SET_TCPM_ROLE_CONTROL(ucPortIndex, (GET_TCPM_ROLE_CONTROL(ucPortIndex) & (~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0))) | (_BIT3 | _BIT1 | _BIT0));
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

        // 3. Set Orientation to TCPC : TCPC_CONTROL [0x19], [0] = b'1 (CC1 = Vconn, CC2 = BMC)
        SET_TCPM_TCPC_CONTROL(ucPortIndex, GET_TCPM_TCPC_CONTROL(ucPortIndex) | (_BIT0));
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_TCPC_CTRL, GET_TCPM_TCPC_CONTROL(ucPortIndex));
    }

    // Orientation Un-Flip, Flip Common Flow
    // 4-1. Setup Auto Discharge (Unattach) Start Thr.(3.65V)
    ScalerTypeCTcpmCcUnattachVthAdjust_EXINT0(ucPortIndex, 500);

    // 4-2 Setup Discharge Stop Thr. 12-Bit w/ 25mV LSB (0.8V = 80 * 10mV)
    ScalerTypeCTcpmTcpciSetWord_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_STOP_DISC_THR, GET_TCPCI_VOLTAGE_CODE(80));

    // 5-1. Enable ALERT.VBUS_SNK_DISC
    ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_SNK_DISC, _ENABLE);

    // 5-2.Enable TCPC Auto Detect Unattach (POWER_CONTROL [0x1C] [4] Auto Discharge Disconnect)
    ScalerTypeCTcpmVbusDetCtrl_EXINT0(ucPortIndex, _ENABLE);

    // 6-1. Disable Vbus Discharge
    ScalerTypeCTcpmVbusDischargeCtrl_EXINT0(ucPortIndex, _OFF);

    // 6-2. Cancel WDTimerEvent (_UNATTACH_VBUS_DISCHARGE_TIMER)
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_CHECK_VBUS_0V);

    // 6-3. Enable Sinking Vbus
    ScalerTypeCTcpmVbusCtrl_EXINT0(ucPortIndex, _ON, _PD_POWER_SNK, _PD_FIX_SUPPLY_PDO, 500, 0, _PD_PEAK_CUR_NONE);

    // 6-4 Start PMIC Protection
    ScalerTypeCTcpmVbusProtectStart_EXINT0(ucPortIndex, _TYPE_C_POWER_SNK);

    return ucSnkAttachValid;
}

//--------------------------------------------------
// Description  : Interrupt Process For CC (UNATTACH_SRC) State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcUnattachSrcProc_EXINT0(BYTE ucPortIndex)
{
    if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_L4C) == 0x00)
    {
        if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CONNECT_RESULT) == 0x00)
        {
            ScalerTypeCTcpmCcAttachWaitSrcCheck_EXINT0(ucPortIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Check Unattach.SRC -> AttachWait.SRC Condition
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcAttachWaitSrcCheck_EXINT0(BYTE ucPortIndex)
{
    // CC_STATUS [4] = b'0 = TCPC Apply Rp (SRC)
    SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_ATTACH_WAIT_SRC);

    // Check Condition : Unattach.SRC -> AttachWait.SRC
    // Refer to CC Spec Ver2.1 (4.5.2.2.7.2) : CC1 or CC2 = Rd, CC1 and CC2 = Ra
    if((((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) == (_BIT1)) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) != (_BIT3))) ||
       (((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) != (_BIT1)) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) == (_BIT3))))
    {
        // Refer to CC Spec Ver2.1 (4.5.2.2.8.2) : AttachWait.SRC -> Attach.SRC Check Exactly One CC Pin = Rd
        // Source Detect (Rd + Not_Rd or Not_Rd + Rd) : Valid Sink Detected, Start tCcDebounce
        SET_TCPM_CC_SNK_DET(ucPortIndex);

        // Start tCcDebounce
        CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
        ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _TCPM_CC_DEBOUNCE_TIME, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);
    }
    else if(((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) == 0x00) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) == 0x00))
    {
        // Source Detect Open + Open : Unattach Detected
        CLR_TCPM_CC_SNK_DET(ucPortIndex);

        // Cancel tCcDebounce
        CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
        ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);

        // Take Source Unattach Flow
        ScalerTypeCTcpmCcUnattachSetting_EXINT0(ucPortIndex);
    }
    else
    {
        // Not Valid Sink Detect for Attached.SRC, nor Sink Remove for Unattach.SRC
        // Source Detect (Rd + Rd), (Ra + Ra) : Stay in AttachWait.SRC and Wait for CC Status Change
        CLR_TCPM_CC_SNK_DET(ucPortIndex);

        // Cancel tCcDebounce
        CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
        ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);
    }
}

//--------------------------------------------------
// Description  : Interrupt Process For CC (ATTACH_WAIT_SRC) State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcAttachWaitSrcProc_EXINT0(BYTE ucPortIndex)
{
    if(GET_TCPM_CC_STATUS_CHG(ucPortIndex) == _TRUE)
    {
        // Check Condition : Unattach.SRC -> AttachWait.SRC
        // Refer to CC Spec Ver2.1 (4.5.2.2.7.2) : CC1 or CC2 = Rd, CC1 and CC2 = Ra
        if((((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) == (_BIT1)) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) != (_BIT3))) ||
           (((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) != (_BIT1)) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) == (_BIT3))))
        {
            // Refer to CC Spec Ver2.1 (4.5.2.2.8.2) : AttachWait.SRC -> Attach.SRC Check Exactly One CC Pin = Rd
            // Source Detecting (Rd + Not_Rd or Not_Rd + Rd)
            // if Sink Already Detected, Could be Rd/Ra Change (May Happens when CC Attach Remove Vconn Pin Rp)
            // if Sink Not Detected Yet, Set Valid Source Detected, and Start tCcDebounce
            if(GET_TCPM_CC_SNK_DET(ucPortIndex) == _FALSE)
            {
                SET_TCPM_CC_SNK_DET(ucPortIndex);

                // Start tCcDebounce
                CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
                ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _TCPM_CC_DEBOUNCE_TIME, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);
            }
        }
        else if(((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) == 0x00) && ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) == 0x00))
        {
            // Source Detect Open + Open : Unattach Detected
            CLR_TCPM_CC_SNK_DET(ucPortIndex);

            // Disable Vbus_Alarm Detection
            SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT5));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));

            // Disable ALERT.VBUS_ALRM_L
            ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_VBUS_ALRM_L, _DISABLE);

            // Cancel tCcDebounce
            CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);

            // Take Source Unattach Flow
            ScalerTypeCTcpmCcUnattachSetting_EXINT0(ucPortIndex);
        }
        else
        {
            // Not Valid Sink Detect for Attached.SRC, nor Sink Remove for Unattach.SRC
            // Source Detect (Rd + Rd), (Ra + Ra) : Stay in AttachWait.SRC and Wait for CC Status Change
            CLR_TCPM_CC_SNK_DET(ucPortIndex);

            // Disable Vbus_Alarm Detection
            SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT5));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));

            // Disable ALERT.VBUS_ALRM_L
            ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_VBUS_ALRM_L, _DISABLE);

            // Cancel tCcDebounce
            CLR_TCPM_CC_TCCDEBOUNCE(ucPortIndex);
            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);
        }
    }
    else
    {
        // Check if AttachWait.SRC -> Attach.SRC condition is Statisfied : (Sink Detect for tCcDebounce) & (Vsafe0V)
        // Should (Vbus Not Detect) Change to vSafe0V?
        if((GET_TCPM_CC_SNK_DET(ucPortIndex) == _TRUE) && (GET_TCPM_CC_TCCDEBOUNCE(ucPortIndex) == _TRUE) && (GET_TCPM_CC_SRC_DET_0V(ucPortIndex) == _TRUE))
        {
            // Attach Setting for CC Function in POWER_SRC
            if(ScalerTypeCTcpmCcSrcAttachSetting_EXINT0(ucPortIndex) == _TRUE)
            {
                if(GET_TCPM_PD_FUNCTION_EN(ucPortIndex) == _TRUE)
                {
                    // Attach Setting for PD Function in POWER_SRC
                    ScalerTypeCTcpmPdAttachSetting_EXINT0(ucPortIndex, _PD_POWER_SRC);
                }

                // Turn On U3 & Hub Function
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                {
                    ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToDx_EXINT0(g_penumTypeCTcpmPort[ucPortIndex]), _TYPE_C_PIN_ASSIGNMENT_NONE, GET_TCPM_ORIENTATION(ucPortIndex));
                }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                {
                    ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToPx_EXINT0(g_penumTypeCTcpmPort[ucPortIndex]), _TYPE_C_PIN_ASSIGNMENT_NONE, GET_TCPM_ORIENTATION(ucPortIndex));
                }
#endif

                // SET FSM to ATTACH_SRC
                SET_TCPM_CC_ATTACHED(ucPortIndex);
                SET_TCPM_CC_FW_STATE(ucPortIndex, _TCPM_CC_FW_ATTACHED);
                SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_ATTACH_SRC);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Interrupt Process For CC (ATTACH_SRC) State
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcAttachSrcProc_EXINT0(BYTE ucPortIndex)
{
    BYTE ucCcStatus = 0x00;

    if(GET_TCPM_CC_STATUS_CHG(ucPortIndex) == _TRUE)
    {
        if(GET_TCPM_ORIENTATION(ucPortIndex) == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // Un-Flip : ChecK CC1 Rp Value (CC_STATUS [0x1D] [1:0] CC1_STATE)
            ucCcStatus = (GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE);
        }
        else
        {
            // Flip : Check CC2 Rp Value (CC_STATUS [0x1D] [3:2] CC2_STATE)
            ucCcStatus = ((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) >> 2);
        }

        if(ucCcStatus == 0x00)
        {
            // CC Pin = Open (b'00), Take Source Unattach Flow
            ScalerTypeCTcpmCcUnattachSetting_EXINT0(ucPortIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Interrupt Process For CC Entry into Attached.SRC State
// Input Value  : ucPortIndex
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCTcpmCcSrcAttachSetting_EXINT0(BYTE ucPortIndex)
{
    BYTE ucSrcAttachValid = _FALSE;

    // Source Detect vSafe0V, Judege Orientation and Enable Vbus + Vconn
    if(GET_TCPM_CC_SRC_DET_5V(ucPortIndex) == _FALSE)
    {
        // 1. Check CC Pin to Judge Orientation : CC_STATUS [0x1D]
        if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) == (_BIT1))
        {
            // 1-1. [1:0] CC1 = b'10 (Rd) : Orientation = Unflip
            SET_TCPM_ORIENTATION(ucPortIndex, _TYPE_C_ORIENTATION_UNFLIP);

            // 1-2.Check if Ra Exist on CC2 : [3:2] CC2 = b'01 (Ra)
            if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) == (_BIT2))
            {
                SET_TCPM_CC_RA_EXIST(ucPortIndex);
            }
            else
            {
                CLR_TCPM_CC_RA_EXIST(ucPortIndex);
            }

            // 2. Apply Rp on CC1 : ROLE_CONTROL [0x1A], [6] DRP :0, [3:2] CC2 = b'11 (Open), [1:0] CC1 = b'01 (Rp)
            SET_TCPM_ROLE_CONTROL(ucPortIndex, (GET_TCPM_ROLE_CONTROL(ucPortIndex) & (~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0))) | (_BIT3 | _BIT2 | _BIT0));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

            // 3. Set Orientation to TCPC : TCPC_CONTROL [0x19], [0] = b'0 (CC1 = BMC, CC2 = Vconn)
            SET_TCPM_TCPC_CONTROL(ucPortIndex, GET_TCPM_TCPC_CONTROL(ucPortIndex) & (~_BIT0));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_TCPC_CTRL, GET_TCPM_TCPC_CONTROL(ucPortIndex));
        }
        else if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC2_STATE) == (_BIT3))
        {
            // 1-1. [3:2] CC2 = b'10 (Rd) : Orientation = Flip
            SET_TCPM_ORIENTATION(ucPortIndex, _TYPE_C_ORIENTATION_FLIP);

            // 1-2.Check if Ra Exist on CC1 : [1:0] CC2 = b'01 (Ra)
            if((GET_TCPM_CC_STATUS(ucPortIndex) & _TCPM_TCPCI_CC_STAT_CC1_STATE) == (_BIT0))
            {
                SET_TCPM_CC_RA_EXIST(ucPortIndex);
            }
            else
            {
                CLR_TCPM_CC_RA_EXIST(ucPortIndex);
            }

            // 2. Apply Rp on CC2 : ROLE_CONTROL [0x1A], [6] DRP :0, [3:2] CC2 = b'01 (Rp), [1:0] CC1 = b'11 (Open)
            SET_TCPM_ROLE_CONTROL(ucPortIndex, (GET_TCPM_ROLE_CONTROL(ucPortIndex) & (~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0))) | (_BIT2 | _BIT1 | _BIT0));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

            // 3. Set Orientation to TCPC : TCPC_CONTROL [0x19], [0] = b'1 (CC1 = Vconn, CC2 = BMC)
            SET_TCPM_TCPC_CONTROL(ucPortIndex, GET_TCPM_TCPC_CONTROL(ucPortIndex) | (_BIT0));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_TCPC_CTRL, GET_TCPM_TCPC_CONTROL(ucPortIndex));
        }

        // Orientation Un-Flip, Flip Common Flow
        // 4-1. if Ra Exist, Enable Vconn (POWER_CONTROL [0x1C] [0] Vconn Enable)
        if(GET_TCPM_CC_RA_EXIST(ucPortIndex) == _TRUE)
        {
            ScalerTypeCTcpmVconnCtrl_EXINT0(ucPortIndex, _ON);
        }

        // Set OCP Threshlod
        SET_TCPM_OCP_CURRENT(ucPortIndex, (WORD)(((DWORD)(GET_TCPM_CC_DEF_CUR(ucPortIndex)) * (DWORD)(GET_TCPM_OCP_RATIO(ucPortIndex, 0))) / 100));

        // 4.2. Disable Vbus Discharge
        ScalerTypeCTcpmVbusDischargeCtrl_EXINT0(ucPortIndex, _OFF);

        // Cancel WDTimerEvent (_UNATTACH_VBUS_DISCHARGE_TIMER)
        ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_CHECK_VBUS_0V);

        // 4-2. Enable Sourceing Vbus
        ScalerTypeCTcpmVbusCtrl_EXINT0(ucPortIndex, _ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, 500, GET_TCPM_OCP_CURRENT(ucPortIndex), _PD_PEAK_CUR_NONE);

        // 5-1. Set Vbus_Alarm_H Thr to Check Vbus Reach Vsafe5V
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_VOL_ALARM_H, GET_TCPCI_VOLTAGE_CODE(475));

        // 5-2. Enable ALERT.VBUS_ALRM_H
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_VBUS_ALRM_H, _ENABLE);

        // 6. Wait for Vbus On to Confirm Source Attach
        ucSrcAttachValid = _FALSE;
    }
    else
    {
        // Vbus Reach vSafe5V, Enter Attached.SRC State
        // 7-1 Setup Discharge Stop Thr. 12-Bit w/ 25mV LSB (0.8V = 800mV/25 = 32)
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_STOP_DISC_THR, GET_TCPCI_VOLTAGE_CODE(80));

        // 7-2.Enable TCPC Auto Detect Unattach to Stop Sourcing Vbus (POWER_CONTROL [0x1C] [4] Auto Discharge Disconnect)
        SET_TCPM_POWER_CONTROL(ucPortIndex, GET_TCPM_POWER_CONTROL(ucPortIndex) | (_BIT4));
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));

        ucSrcAttachValid = _TRUE;
    }

    return ucSrcAttachValid;
}

//--------------------------------------------------
// Description  : Interrupt Process For Unattach Setting
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcUnattachSetting_EXINT0(BYTE ucPortIndex)
{
    // From 1. AttachWait.SRC   2. Attach.SRC   3. Attach.SNK

#if(_HW_TCPM_SUPPORT == _ON)
    // Clear & Disabel Alert IRQ : [0xFA23] [5] tcpc_0_alert_irq, [4] tcpc_0_alert_irq_en
    ScalerSetBit_EXINT(PFA_23_TCPC_0_ALERT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT4 | _BIT1), _BIT5);
#endif

    // Reset All Alert
    ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_ALL, _DISABLE);

    if(GET_TCPM_SRC_VCONN(ucPortIndex) == _TRUE)
    {
        // Turn Off Vconn, if they are turned on when attached
        ScalerTypeCTcpmVconnCtrl_EXINT0(ucPortIndex, _OFF);
    }

    // Turn Off Vbus and Turn On Vbus Discharge
    ScalerTypeCTcpmVbusCtrl_EXINT0(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
    ScalerTypeCTcpmVbusDischargeCtrl_EXINT0(ucPortIndex, _ON);

    // Active WD Timer Event To Detect if Vbus is Already Discharge to vSafe0V
    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _UNATTACH_VBUS_DISCHARGE_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CC_CHECK_VBUS_0V);

#if(_TYPE_C_PMIC_SUPPORT == _ON)
    if(GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON)
    {
        ScalerTypeCTcpmPmicReset_EXINT0(ucPortIndex);
    }
#endif
    ScalerTypeCTcpmPdReset_EXINT0(ucPortIndex);
    // FW Solution : Samsung S8 Clear Flag When CC Unattach (Not Cleared When PD Reset)
    ScalerTypeCTcpmPdClrInteropS8Flag_EXINT0(ucPortIndex);
    ScalerTypeCTcpmCcUnattachReset_EXINT0(ucPortIndex);

    // Setting for CC FSM Connection
    ScalerTypeCTcpmCcConnectionSet_EXINT0(ucPortIndex);

    SET_TCPM_CC_FW_STATE(ucPortIndex, _TCPM_CC_FW_CONNECTING);

    // Enable Alert Detect and Start CC FSM
    ScalerTypeCTcpmCcConnectionStart_EXINT0(ucPortIndex);
}

//--------------------------------------------------
// Description  : Type C TCPM Unattach (Turn Off Power / Disconnect Channel / Clear IRQs)
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcUnattachReset_EXINT0(BYTE ucPortIndex)
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
    ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_PWR_CTRL, GET_TCPM_POWER_CONTROL(ucPortIndex));
}

//--------------------------------------------------
// Description  : Interrupt Process For CC Entry into Attached.SRC/SNK State
// Input Value  : ucPortIndex, usVoltage (Negotiated Voltage in 10mV)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcUnattachVthAdjust_EXINT0(BYTE ucPortIndex, WORD usVoltage)
{
    // TCPCI Register VBUS_SNK_DISCONNECT_THRESHOLD 0x72~73 (12-Bit w/ 25mV LSB)
    WORD usUnattachVol = 0x00;

    // Sink Unattach Voltage "Refer to CC Spec Table 4-3" (Unit:10mV)
    if(usVoltage == 500)
    {
        // When PD Contract = 5V or No PD : Use 3.65V (365 * 10mV) / 25mV
        usUnattachVol = GET_TCPCI_VOLTAGE_CODE(365);
    }
    else
    {
        // When PD Contract Above 5V : [(Vnew * 0.95) - 1250mV] * 0.9
        usUnattachVol = ((((usVoltage * 19 / 20) - 125) * 9 / 10) * 10 / 25);
    }

    ScalerTypeCTcpmTcpciSetWord_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_SNK_DISC_THR, usUnattachVol);
}

//--------------------------------------------------
// Description  : Type C TCPM CC Connection Setting
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmCcConnectionSet_EXINT0(BYTE ucPortIndex)
{
    // Set ROLE_CONTROL [0x1A] : DRP, Rp Value, CC1, CC2
    switch(GET_TCPM_CC_PORT_ROLE(ucPortIndex))
    {
        case _TYPE_C_PORT_SNK_ONLY:

            // ROLE_CONTROL [0x1A] ([6] DRP = 0, [5:4] Rp default, [3:2] CC1 = [1:0] CC2 = Rd)
            SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT3 | _BIT1);

            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

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

            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

            SET_TCPM_CC_FSM(ucPortIndex, _TCPM_CC_FSM_UNATTACH_SRC);

            break;

        case _TYPE_C_PORT_DRP:

            // ROLE_CONTROL [0x1A] ([6] DRP = 1, [5:4] Rp Refer Macro, [3:2] CC1 = [1:0] CC2 = Rd)
            if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_USB)
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT3 | _BIT1);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 90);  // 90 * 10mA = 900mA
            }
            else if(GET_TCPM_CC_RP_DEF_VALUE(ucPortIndex) == _TYPE_C_SRC_DEF_1P5A)
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT4 | _BIT3 | _BIT1);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 150);  // 150 * 10mA = 1.5A
            }
            else
            {
                SET_TCPM_ROLE_CONTROL(ucPortIndex, _BIT6 | _BIT5 | _BIT3 | _BIT1);

                SET_TCPM_CC_DEF_CUR(ucPortIndex, 300); // 300 * 10mA = 3.0A
            }

            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));

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
void ScalerTypeCTcpmCcConnectionStart_EXINT0(BYTE ucPortIndex)
{
    // Enable ALERT.CC_STATUS
    ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_CC_STATUS, _ENABLE);

    // Start Look 4 Connection
    ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_COMMAND, _TCPM_TCPCI_CMD_LOOK_4_CONNECTION);
}

//--------------------------------------------------
// Description  : TypeC TCPM PD Reset
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdReset_EXINT0(BYTE ucPortIndex)
{
    // -------------------- HW Clear, Disable or Reset to Default Value --------------------
    // 1. Disable PD Rcv Detect ([0x2F] : [5] HRST, [2] SOP", [1] SOP', [0] SOP)
    ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, 0x00);

    // 2. Disable BIST Mode
    if(GET_TCPM_PD_BIST_MODE(ucPortIndex) == _PD_BIST_TEST_DATA_MODE)
    {
        // TCPM Would Set TCPC_CONTROL [0x19], [1] = b'1 (BIST Test Data Mode) When Entering Test Data Mode
        // Disable Test Data Mode by Set TCPC_CONTROL [0x19], [1] = b'0
        SET_TCPM_TCPC_CONTROL(ucPortIndex, GET_TCPM_TCPC_CONTROL(ucPortIndex) & (~_BIT1));
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_TCPC_CTRL, GET_TCPM_TCPC_CONTROL(ucPortIndex));
    }
    SET_TCPM_PD_BIST_MODE(ucPortIndex, _PD_BIST_MODE_NONE);

    // 3. Disable PD Tx/Rx Alert
    ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_HRST | _TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS | _TCPM_TCPCI_ALERT_RX_OVERFLOW), _DISABLE);

    // ------------------------- FW State & Counter & Flag Reset -------------------------
    // 4. Reset PD Related Macros
    // PD Initial States Setting
    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
    SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_STATE_NONE);
    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_NONE);

    ScalerTypeCTcpmPdClrHpd_EXINT0(ucPortIndex);

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
    if((GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX) && (GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG))
    {
        ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], _PD_HPD_LOW, 0);
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
        ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToDx_EXINT0(g_penumTypeCTcpmPort[ucPortIndex]), GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
    {
        ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToPx_EXINT0(g_penumTypeCTcpmPort[ucPortIndex]), GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
    }
#endif

    // Cancel Timer Event
    ScalerTypeCTcpmPdUnattachCancelTimerEvent_EXINT0(ucPortIndex);

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
// Description  : Interrupt Process For PD Entry into Attached.SRC/SNK State
// Input Value  : enumTypeCPcbPort, Power Role
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdAttachSetting_EXINT0(BYTE ucPortIndex, bit bPowerRole)
{
    if(bPowerRole == _PD_POWER_SRC)
    {
        // 1. Set Default Power Role, Data Role, Vconn Role
        SET_TCPM_POWER_ROLE(ucPortIndex, _PD_POWER_SRC);
        SET_TCPM_DATA_ROLE(ucPortIndex, _PD_DATA_DFP);
        SET_TCPM_VCONN_ROLE(ucPortIndex, _PD_VCONN_SRC);

        // 2-1. If PD 3.0, Change Rp to SinkTxOK (Rp-3A)
        if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
        {
            // ROLE_CONTROL [0x1A], [5:4] = b'00(Rp-Def), b'01(Rp-1.5A), b'10(Rp-3A)
            SET_TCPM_ROLE_CONTROL(ucPortIndex, (GET_TCPM_ROLE_CONTROL(ucPortIndex) & (~(_BIT5 | _BIT4))) | (_BIT5));
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));
        }

        // 2-2. Set Message Header for GoodCRC Reply
        ScalerTypeCTcpmPdUpdateGoodCRCInfo_EXINT0(ucPortIndex);

        // 2-3. Enable PD Rcv Detect ([0x2F] : [5] HRST, [2] SOP", [1] SOP', [0] SOP)
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, (_TCPM_TCPCI_RCV_DET_SOP | _TCPM_TCPCI_RCV_DET_SOP_P | _TCPM_TCPCI_RCV_DET_SOP_PP | _TCPM_TCPCI_RCV_DET_HRST));

        // 3. Set PD FW Initial State and Start PD Flow
        SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_START_UP);
    }
    else
    {
        // 1. Set Default Power Role, Data Role, Vconn Role
        SET_TCPM_POWER_ROLE(ucPortIndex, _PD_POWER_SNK);
        SET_TCPM_DATA_ROLE(ucPortIndex, _PD_DATA_UFP);
        SET_TCPM_VCONN_ROLE(ucPortIndex, _PD_VCONN_NOT_SRC);

        // 2-1. Set Message Header for GoodCRC Reply
        ScalerTypeCTcpmPdUpdateGoodCRCInfo_EXINT0(ucPortIndex);

        // 2-2. Enable PD Rcv Detect ([0x2F] : [5] HRST, [0] SOP)
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, (_TCPM_TCPCI_RCV_DET_SOP | _TCPM_TCPCI_RCV_DET_HRST));

        // 3. Set PD FW Initial State and Start PD Flow
        SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_START_UP);
    }

    ScalerTypeCTcpmPdStartUpProc_EXINT0(ucPortIndex);

    // Clear and Enable ALERT.Rx_RCV_SOP + ALERT.Rx_Overflow + ALERT.Rx_HRST + FAULT
    ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_HRST | _TCPM_TCPCI_ALERT_RX_OVERFLOW | _TCPM_TCPCI_ALERT_FAULT), _ENABLE);
}

//--------------------------------------------------
// Description  : PD_FW_STATE Start Up State Process
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdStartUpProc_EXINT0(BYTE ucPortIndex)
{
    // From 1. Unattach to Attach   2. After Hard Reset     3. After PR_SWAP    4. After FR_SWAP

    // -------------------------------------------------
    // Refer to "ScalerTypeCTcpmPdStartUpSetting_EXINT0"
    // -------------------------------------------------
    // Clear Explicit Power Contract
    CLR_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex);

    // Reset Message ID
    CLR_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex);
    CLR_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex);
    CLR_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex);
    CLR_TCPM_PD_RX_MSG_ID_SOP(ucPortIndex);
    CLR_TCPM_PD_RX_MSG_ID_SOP_P(ucPortIndex);
    CLR_TCPM_PD_RX_MSG_ID_SOP_PP(ucPortIndex);

    CLR_TCPM_PD_SRC_CAP_CNT(ucPortIndex);
    SET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex, 0);
    CLR_TCPM_PD_PRS_PROCESSING(ucPortIndex);

    if(GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_SRC_START_UP)
    {
        // Enable Rx IRQ
        ScalerTypeCTcpmRxIntControl_EXINT0(ucPortIndex, _ENABLE);

        // Enable ALERT.CC_STATUS
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_CC_STATUS, _ENABLE);

        if((GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC) && (GET_TCPM_SRC_VCONN(ucPortIndex) == _TRUE))
        {
            // Discover Cable When (Vconn SRC) & (Ra Exist)
            if(GET_TCPM_PD_CBL_SOFT_RESET_REQUIRED(ucPortIndex) == _TRUE)
            {
                CLR_TCPM_PD_CBL_SOFT_RESET_REQUIRED(ucPortIndex);

                // After VCS + PRS, Do Cable Soft Reset
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_WDINT_SEND_CBL_SOFT_RESET);
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Active WD Timer Event To Do Cable Soft Reset
                ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 10, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);
            }
            else
            {
                // After Attach / Hard Reset, Do Cable Discovery if VbusSafe5V
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_WDINT_SEND_CBL_DISCOVER_ID);
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Active WD Timer Event To Check Vbus, Then Do Cable Proc if VbusSafe5V
                ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 70, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
            }
        }
        else
        {
            // Send Source Cap When (Not Vconn SRC) or (Not Ra Exist)
            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_WDINT_SEND_CAP);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

            // Active WD Timer Event To Send SRC_CAP
            // Active WD Timer Event To Check Vbus, Then Start PMIC Protection and Send SRC_CAP if VbusSafe5V
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 20, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
        }
    }
    else if(GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_SNK_START_UP)
    {
        // Enable Rx IRQ
        ScalerTypeCTcpmRxIntControl_EXINT0(ucPortIndex, _ENABLE);

        // Enable ALERT.CC_STATUS
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_CC_STATUS, _ENABLE);

        // Transit FW_STATE to _PD_SNK_INT_WAIT_SRC_CAP and Start Power Negitiation
        SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_INT_WAIT_SRC_CAP);
        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
        SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

        // Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
        ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, ScalerTypeCTcpmWDTimeCtrl_EXINT0(ucPortIndex, _SINK_WAIT_CAP_TIMER), _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST);
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Decode TCPCI Rx Buffer
// Input Value  : ucPortIndex
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ScalerTypeCTcpmPdRxMsgIdCheck_EXINT0(BYTE ucPortIndex)
{
    BYTE ucCheckResult = _FAIL;
    BYTE ucMessageID;

    // Check and Update Rx Message ID (Message Header[11:9] = Rx_Buffer[3][3:1])
    ucMessageID = ((GET_TCPM_RX_BUF_MSG_HEADER_H() & (_BIT3 | _BIT2 | _BIT1)) >> 1);

    if(GET_TCPM_RX_BUF_FRAME_TYPE() == _TCPM_TCPCI_RX_FRAME_TYPE_SOP)
    {
        if(GET_TCPM_PD_RX_MSG_ID_SOP(ucPortIndex) != ucMessageID)
        {
            SET_TCPM_PD_RX_MSG_ID_SOP(ucPortIndex, ucMessageID);

            ucCheckResult = _SUCCESS;
        }
    }
    else if(GET_TCPM_RX_BUF_FRAME_TYPE() == _TCPM_TCPCI_RX_FRAME_TYPE_SOP_P)
    {
        if(GET_TCPM_PD_RX_MSG_ID_SOP_P(ucPortIndex) != ucMessageID)
        {
            SET_TCPM_PD_RX_MSG_ID_SOP_P(ucPortIndex, ucMessageID);

            ucCheckResult = _SUCCESS;
        }
    }
    else if(GET_TCPM_RX_BUF_FRAME_TYPE() == _TCPM_TCPCI_RX_FRAME_TYPE_SOP_PP)
    {
        if(GET_TCPM_PD_RX_MSG_ID_SOP_PP(ucPortIndex) != ucMessageID)
        {
            SET_TCPM_PD_RX_MSG_ID_SOP_PP(ucPortIndex, ucMessageID);

            ucCheckResult = _SUCCESS;
        }
    }

    // Soft Reset Message DO NOT Check Message ID
    // Soft Reset Message : Header[15] Extended = 0, Header[14:12] NOD = 0, Header[4:0] Msg Type = 0_1101,
    if(((GET_TCPM_RX_BUF_MSG_HEADER_H() & 0xF0) == 0x00) && ((GET_TCPM_RX_BUF_MSG_HEADER_L() & (0x1F)) == 0x0D))
    {
        ucCheckResult = _SUCCESS;
    }

    return ucCheckResult;
}

//--------------------------------------------------
// Description  : Type C TCPM Decode TCPCI Rx Buffer
// Input Value  : ucPortIndex
// Output Value : Rx Message Valid or Not
//--------------------------------------------------
void ScalerTypeCTcpmPdRxMsgDecode_EXINT0(BYTE ucPortIndex)
{
    CLR_TCPM_PD_RCV_MSG(ucPortIndex);
    CLR_TCPM_PD_RCV_VDM_CMD(ucPortIndex);

    // Message Header : [14:12] Number Of Data Object
    SET_TCPM_PD_RCV_NOD_CNT(ucPortIndex, (GET_TCPM_RX_BUF_MSG_HEADER_H() & (_BIT6 | _BIT5 | _BIT4)) >> 4);

    // Check Control / Data / Extended Message
    if((GET_TCPM_RX_BUF_MSG_HEADER_H() & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
    {
        // Control Message (Message Header : [15] Extended = 0, [14:12] NoD = 0)
        SET_TCPM_PD_RCV_MSG(ucPortIndex, _PD_CMD_TYPE_CTRL | (GET_TCPM_RX_BUF_MSG_HEADER_L() & (0x1F)));
    }
    else if((GET_TCPM_RX_BUF_MSG_HEADER_H() & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) < 0x80)
    {
        // Data Message (Message Header : [15] Extended = 0, [14:12] NoD != 0)
        SET_TCPM_PD_RCV_MSG(ucPortIndex, _PD_CMD_TYPE_DATA | (GET_TCPM_RX_BUF_MSG_HEADER_L() & (0x1F)));

        ScalerTypeCTcpmPdRxReadDataObj_EXINT0(ucPortIndex, _PD_CMD_TYPE_DATA);

        if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_VDM)
        {
            // Get Standard & Vender ID : VDM Header[31:16]
            SET_TCPM_PD_RCV_VDM_SVID_H(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0]);
            SET_TCPM_PD_RCV_VDM_SVID_L(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[1]);

            // Check If Rcv. an Structured VDM Message
            if((g_pucTypeCTcpmPdDataObj_EXINT[2] & _BIT7) == _BIT7)
            {
                // Set VDM Type = Structured VDM
                SET_TCPM_PD_RCV_VDM_TYPE(ucPortIndex, _PD_STRUCTURED_VDM);

                // Get VDM Object Position : VDM Header[10:8]
                SET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[2] & (_BIT2 | _BIT1 | _BIT0));

                // Get VDM Command Type : VDM Header[7:0] ([7:6] VDM CMD Type  [4:0] VDM CMD)
                SET_TCPM_PD_RCV_VDM_CMD(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[3]);
            }
            else
            {
                // Set VDM Type = Unstructured VDM
                SET_TCPM_PD_RCV_VDM_TYPE(ucPortIndex, _PD_UNSTRUCTURED_VDM);
            }
        }
    }
    else
    {
        // Extended Message (Message Header : [15] Extended = 1)
        SET_TCPM_PD_RCV_MSG(ucPortIndex, _PD_CMD_TYPE_EXT | (GET_TCPM_RX_BUF_MSG_HEADER_L() & (0x1F)));

        ScalerTypeCTcpmPdRxReadDataObj_EXINT0(ucPortIndex, _PD_CMD_TYPE_EXT);

        // Check If This Ext Msg is Chunked : Ext Message Header [15]
        SET_TCPM_PD_RCV_EXT_CHUNKED(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 7);

        // Get Ext Msg Chunk Number
        SET_TCPM_PD_RCV_EXT_CHUNK_NUM(ucPortIndex, (g_pucTypeCTcpmPdDataObj_EXINT[0] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3);

        // Get Ext Msg Chunk Request
        SET_TCPM_PD_RCV_EXT_CHUNK_REQ(ucPortIndex, (g_pucTypeCTcpmPdDataObj_EXINT[0] >> 2));

        // Get Ext Msg Total Size
        SET_TCPM_PD_RCV_EXT_DATA_SIZE(ucPortIndex, ((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[0] & _BIT0) << 8) | (WORD)(g_pucTypeCTcpmPdDataObj_EXINT[1]));
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Process Data Object align with Emb PD
// Input Value  : ucPortIndex, enumCmdType
// Output Value : Rx Message Valid or Not
//--------------------------------------------------
void ScalerTypeCTcpmPdRxReadDataObj_EXINT0(BYTE ucPortIndex, EnumTypeCPDCmdType enumCmdType)
{
    // BYTE ucNoDCount = (GET_TCPM_RX_BUF_MSG_HEADER_H() & (_BIT6 | _BIT5 | _BIT4));
    BYTE ucNoDCount = GET_TCPM_PD_RCV_NOD_CNT(ucPortIndex);

    if(enumCmdType == _PD_CMD_TYPE_DATA)
    {
        // ---- TCPCI RX BUFFER ----
        // g_pucRxBuffer [0](READALE_BYTE_CNT), [1](FRAME_TYPE),        [2](MSG_HEADER_L),      [3](MSG_HEADER_H)
        // g_pucRxBuffer [4](Data_Object_7_0),  [5](Data_Object_15_8),  [6](Data_Object_23_16), [7](Data_Object_31_24)
        // ---- Embedded PD Data Object ----
        // PdDataObj     [0](Data_Object_31_24),[1](Data_Object_23_16), [2](Data_Object_15_8),  [3](Data_Object_7_0)

        // Start Reading Data Object Contents from FIFO
        for(BYTE ucLoopIndex = 0; ucLoopIndex < ucNoDCount; ucLoopIndex++)
        {
            // Data Object_N [31:24] = RX_BUF_DATA [4 + (N * 4 + 3)]
            g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] = g_pucTypeCTcpmRxBuffer_EXINT[4 + (ucLoopIndex * 4 + 3)];

            // Data Object_N [23:16] = RX_BUF_DATA [4 + (N * 4 + 2)]
            g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] = g_pucTypeCTcpmRxBuffer_EXINT[4 + (ucLoopIndex * 4 + 2)];

            // Data Object_N [15:8] = RX_BUF_DATA [4 + (N * 4 + 1)]
            g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2] = g_pucTypeCTcpmRxBuffer_EXINT[4 + (ucLoopIndex * 4 + 1)];

            // Data Object_N [7:0] = RX_BUF_DATA [4 + (N * 4 + 0)]
            g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 3] = g_pucTypeCTcpmRxBuffer_EXINT[4 + (ucLoopIndex * 4)];
        }
    }
    else if(enumCmdType == _PD_CMD_TYPE_EXT)
    {
        // ---- TCPCI RX BUFFER ----
        // g_pucRxBuffer [0](READALE_BYTE_CNT), [1](FRAME_TYPE),        [2](MSG_HEADER_L),      [3](MSG_HEADER_H)
        // g_pucRxBuffer [4](EXT_MSG_HEADER_L), [5](EXT_MSG_HEADER_H)
        // g_pucRxBuffer [6](Data_Block_0),     [7](Data_Block_1),      [8](Data_Block_2),      [9](Data_Block_3)
        // ---- Embedded PD Data Object ----
        // PdDataObj     [0](EXT_MSG_HEADER_H), [1](EXT_MSG_HEADER_L),  [2](Data_Block_0),      [3](Data_Block_1)

        // Store Extended Message Header to Data Object
        g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmRxBuffer_EXINT[5];
        g_pucTypeCTcpmPdDataObj_EXINT[1] = g_pucTypeCTcpmRxBuffer_EXINT[4];

        // Start Reading Data Object Contents from FIFO
        for(BYTE ucLoopIndex = 2; ucLoopIndex < (ucNoDCount * 4); ucLoopIndex++)
        {
            // Data Object_N = RX_BUF_DATA [(N + 4)]
            g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex] = g_pucTypeCTcpmRxBuffer_EXINT[(ucLoopIndex + 4)];
        }
    }
}

//--------------------------------------------------
// Description  : Process When Rcv. Msg. in Interrupt Before Ready
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntRcvMsgProc_EXINT0(BYTE ucPortIndex)
{
    switch(GET_TCPM_PD_FW_STATE(ucPortIndex))
    {
        case _PD_SRC_INT_WAIT_REQ:

            // Cancel WDTimerEvent (_SENDER_RESP_TIMER)
            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_REQUEST)
            {
                // 1. Get Port Partner's Spec Version, and decide the version for communication
                if((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ||
                   ((GET_TCPM_RX_BUF_MSG_HEADER_L() & (_BIT7 | _BIT6)) == _BIT6))
                {   // if(Our PD Version is 2.0 || Port Partner Support Only PD 2.0)

                    // Change Spec Vesion to PD 2.0
                    SET_TCPM_PD_SPEC_VER(ucPortIndex, _PD_VERSION_2_0);

                    // Change Cable Spec Vesion to PD 2.0
                    SET_TCPM_PD_CBL_SPEC_VER(ucPortIndex, _PD_VERSION_2_0);
                }
                else
                {
                    // Set Spec Vesion to PD 3.0
                    SET_TCPM_PD_SPEC_VER(ucPortIndex, _PD_VERSION_3_0);
                }

                // Evaluate if Received Request is Valid
                if(ScalerTypeCTcpmPdCheckRequestValid_EXINT0(ucPortIndex) == _PD_REQUEST_VALID)
                {
                    SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_INT_SEND_ACCEPT_REQ);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_INT_SEND_REJECT_REQ);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {   // TD.PD.SRC.E14 : Receive Unexpected Msg. in "_PD_SRC_INT_WAIT_REQ", Do Soft Reset
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;

        case _PD_SNK_INT_WAIT_SRC_CAP:

            // Enable Vbus Detection
            ScalerTypeCTcpmVbusDetCtrl_EXINT0(ucPortIndex, _ENABLE);

            // Cancel SinkWaitCapTimer (310~620ms) = _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST
            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_SRC_CAP)
            {
                // 1. Get Port Partner's Spec Version, and Decide the Version for Communication
                if((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ||
                   ((GET_TCPM_RX_BUF_MSG_HEADER_L() & (_BIT7 | _BIT6)) == _BIT6))
                {   // if(Our PD Version is 2.0 || Port Partner Support Only PD 2.0)

                    // Change Spec Vesion to PD 2.0
                    SET_TCPM_PD_SPEC_VER(ucPortIndex, _PD_VERSION_2_0);

                    // Change Cable Spec Vesion to PD 2.0
                    SET_TCPM_PD_CBL_SPEC_VER(ucPortIndex, _PD_VERSION_2_0);
                }
                else
                {
                    // Set Spec Vesion to PD 3.0
                    SET_TCPM_PD_SPEC_VER(ucPortIndex, _PD_VERSION_3_0);
                }

                // 2. Store Src_Cap Info from Data Objects
                SET_TCPM_PD_PARTNER_DRP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 5);
                SET_TCPM_PD_PARTNER_SUSPEND(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 4);
                SET_TCPM_PD_PARTNER_EXT_PWR(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 3);
                SET_TCPM_PD_PARTNER_USB_CAP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 2);
                SET_TCPM_PD_PARTNER_DRD(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 1);
                SET_TCPM_PD_PARTNER_UNCHK(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 0);
                SET_TCPM_PD_PARTNER_EPR_CAP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[1] >> 7);

                // Get Number Of Capabilities
                SET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex, GET_TCPM_PD_RCV_NOD_CNT(ucPortIndex));

                // Evaluate and Set Request Data Objects
                for(BYTE ucLoopIndex = 0; ucLoopIndex < _TYPE_C_PDO_NUM_7; ucLoopIndex++)
                {
                    if(ucLoopIndex < GET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex))
                    {
                        if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                        {
                            // Set APDO Type
                            SET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                        }
                        else
                        {
                            // Set PDO Type
                            SET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) >> 6));
                        }

                        if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                        {
                            // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                            SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex, (((((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & 0x01)) << 7) | (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] & 0xFE)) >> 1)) * 10));
                            SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, ucLoopIndex, (((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2]) * 10));
                            SET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, ucLoopIndex, (((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 3] & 0x7F) * 5));
                        }
                        else
                        {
                            // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                            SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex, (((((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2] & 0xFC)) >> 2)) * 5));
                            SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, ucLoopIndex, GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex));
                            SET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, ucLoopIndex, (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 3]));
                            SET_TCPM_PD_PARTNER_SRC_PEAK_CUR(ucPortIndex, ucLoopIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] & (_BIT5 | _BIT4)) >> 4));

                            // If Target Voltage Matches Partner's Voltage, Set the Macros of Capability Mismatch and Object Position.
                            if((GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_TARGET_VOL) && (GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex) == (GET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex) * 100)))
                            {
                                SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _FALSE);
                                SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, (EnumTypeCPdoNumber)(ucLoopIndex + 1));
                            }
                        }
                    }
                    else
                    {
                        // If ucLoopIndex >= GET_TCPM_PD_PARTNER_SRC_CAP_CNT(), Clear the Related Macros to 0x00.
                        SET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex, _PD_NONE_SETTING_PDO);
                        SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex, 0x00);
                        SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, ucLoopIndex, 0x00);
                        SET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, ucLoopIndex, 0x00);
                        SET_TCPM_PD_PARTNER_SRC_PEAK_CUR(ucPortIndex, ucLoopIndex, 0x00);
                    }
                }

                // According to the corresponding Request Type, Set the Macros of Capability Mismatch and Object Position.
                if(GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_LOWEST_VOL)
                {
                    SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _FALSE);
                    SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, _TYPE_C_PDO_NUM_1);
                }
                else if(GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_HIGHEST_VOL)
                {
                    SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _FALSE);

                    // Select Highest Fix PDO
                    for(BYTE ucLoopIndex = GET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex); ucLoopIndex > 0; ucLoopIndex--)
                    {
                        if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex - 1) == _PD_FIX_SUPPLY_PDO)
                        {
                            SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, (EnumTypeCPdoNumber)(ucLoopIndex));

                            break;
                        }
                    }
                }
                else if((GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_TARGET_VOL) && (GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) != (GET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex) * 100)))
                {
                    SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _TRUE);
                    SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, _TYPE_C_PDO_NUM_1);
                }

                // If Request Type isn't Customized RDO, Need to be Set Operating and Max. Current.
                if(GET_TCPM_PD_REQ_TYPE(ucPortIndex) != _TYPE_C_REQ_CUSTOMIZED_RDO)
                {
                    SET_TCPM_PD_REQ_INFO_1(ucPortIndex, GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1));
                    SET_TCPM_PD_REQ_INFO_2(ucPortIndex, GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1));
                }

                // Send Request (Success : Wait Resp / Fail : Hard Reset)
                SET_TCPM_PD_RCV_SRC_CAP(ucPortIndex);
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_INT_SEND_REQUEST);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REQUEST, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Receive Unexpected Msg. in "_PD_SNK_INT_WAIT_SRC_CAP", Do Hard Reset
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;

        case _PD_SNK_INT_WAIT_REQ_RESP:

            // Cancel WDTimerEvent(SENDER_RESP_TIMEOUT)
            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_ACCEPT)
            {
                // Disable Detect Sink OVP/UVP
                ScalerTypeCTcpmVbusCtrl_EXINT0(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

                // Turn Off Type-C Unattach Vbus Detection
                ScalerTypeCTcpmVbusDetCtrl_EXINT0(ucPortIndex, _DISABLE);

                // Update PDO Status (Voltage in 10mV / Current in 10mA)
                if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) == _PD_FIX_SUPPLY_PDO)
                {
                    // Request to Fix PDO (REQ_INFO_1 = Op. Cur in 10mA / REQ_INFO_2 = Max. Cur in 10mA)
                    SET_TCPM_PD_PDO_STATUS_VOL(ucPortIndex, GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1));
                    SET_TCPM_PD_PDO_STATUS_CUR(ucPortIndex, GET_TCPM_PD_REQ_INFO_2(ucPortIndex));
                }
                else
                {
                    // Request to PPS PDO (REQ_INFO_1 = Vol in 20mV / REQ_INFO_2 = Op. Cur in 50mA)
                    SET_TCPM_PD_PDO_STATUS_VOL(ucPortIndex, GET_TCPM_PD_REQ_INFO_1(ucPortIndex) * 2);
                    SET_TCPM_PD_PDO_STATUS_CUR(ucPortIndex, GET_TCPM_PD_REQ_INFO_2(ucPortIndex) * 5);
                }

                // Transit to _PD_SNK_INT_WAIT_PS_RDY
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_INT_WAIT_PS_RDY);

                // Source Begin to Transit Power
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_POWER_TRANSITION);

                // Active WD Timer Event For PS Transition Timer (450-550ms), Timeout : Hard Reset
                ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, ScalerTypeCTcpmWDTimeCtrl_EXINT0(ucPortIndex, _PS_TRANSITION_TIMER), _SCALER_WD_TIMER_EVENT_TCPM_PS_TRANSITION_TIMEOUT);
            }
            else if((GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_REJECT) || (GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_WAIT))
            {
                if(GET_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex) == _TRUE)
                {
                    // Set AMS = None
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                    if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_WAIT)
                    {
                        SET_TCPM_PD_REQ_WAIT_FLAG(ucPortIndex);

                        // Re-Evaluate and Send Request After 100 ms if New Power Needed in Snk Ready State Flow
                        ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _WAIT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_REQ_WAIT);
                    }
                }
                else
                {
                    SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_INT_WAIT_SRC_CAP);
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

                    // Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, ScalerTypeCTcpmWDTimeCtrl_EXINT0(ucPortIndex, _SINK_WAIT_CAP_TIMER), _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST);
                }
            }
            else
            {
                // Receive Unexpected Msg. in "_PD_SNK_INT_WAIT_REQ_RESP", Do Soft Reset
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;

        case _PD_SNK_INT_WAIT_PS_RDY:

            // Cancel WDTimerEvent (PS_TRANSITION_TIMER, SEND_HARD_RST)
            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PS_TRANSITION_TIMEOUT);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_PS_RDY)
            {
                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                SET_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex);

#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
                // Clear OCP/OVP/UVP/Vconn OCP Event and Alert Macro due to New Power Contract Established
                CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);
                CLR_TCPM_PD_ALERT_SENT(ucPortIndex);
#endif


#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
                if(GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _ON)
                {
                    // Set PARTNER_ALT_SUPPORT FLAG for Sink in Ready to Wait For Port Partner Initiating Alt Mode Flow
                    SET_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex);

                    // Sink Start PR_SWAP to Provide Power, if Not Enter ALt Mode in 2 Sec After Power Contract, timeout: Clear PARTNER_ALT_SUPPORT Macro
                    ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _PARTNER_ALT_SUPPORT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_PARTNER_ALT_SUPPORT);
                }
#endif

                // Adjust Sink Unattach Vth
                ScalerTypeCTcpmCcUnattachVthAdjust_EXINT0(ucPortIndex, GET_TCPM_PD_PDO_STATUS_VOL(ucPortIndex));

                // Enable Sinking Vbus
                ScalerTypeCTcpmVbusCtrl_EXINT0(ucPortIndex, _ON, _PD_POWER_SNK, GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1), GET_TCPM_PD_PDO_STATUS_VOL(ucPortIndex), GET_TCPM_PD_PDO_STATUS_CUR(ucPortIndex), _PD_PEAK_CUR_NONE);

                // Start PMIC Protection
                ScalerTypeCTcpmVbusProtectStart_EXINT0(ucPortIndex, _TYPE_C_POWER_SNK);

                // Enable Vbus Detection For CC HW to Detect Unattach Event
                ScalerTypeCTcpmVbusDetCtrl_EXINT0(ucPortIndex, _ENABLE);
            }
            else
            {
                // Receive Unexpected Msg. in "_PD_SNK_INT_WAIT_PS_RDY", Do Hard Reset
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;

        case _PD_INT_WAIT_SOFTRESET_RESP:

            // Cancel WD TimerEvent (INT Send Soft Rst)
            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT);

            // [LECROY] TD PD.LL.E04 Hard Reset Usage : Send SoftReset, Then Rcv. Accept with Msg.ID = 1 Shall Ignore.
            if((GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_ACCEPT) && (((GET_TCPM_RX_BUF_MSG_HEADER_H() & (_BIT3 | _BIT2 | _BIT1)) >> 1) == 0x00))
            {
                if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
                {
                    // Clear Explicit Power Contract and Flags
                    CLR_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex);

                    SET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex, 0);
                    CLR_TCPM_PD_SRC_CAP_CNT(ucPortIndex);

                    SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_WDINT_SEND_CAP);
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                    // Active WD Timer Event To Send 1st SRC_CAP, Timeout : Send SRC_CAP.
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 20, _SCALER_WD_TIMER_EVENT_TCPM_SEND_SRC_CAP);
                }
                else
                {
                    // Clear Explicit Power Contract and Flags
                    CLR_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex);

                    // Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, ScalerTypeCTcpmWDTimeCtrl_EXINT0(ucPortIndex, _SINK_WAIT_CAP_TIMER), _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST);

                    SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_INT_WAIT_SRC_CAP);
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);
                }
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;


        case _PD_SNK_READY:

            if((GET_TCPM_PD_AMS_STATUS(ucPortIndex) == _PD_AMS_NONE) || (GET_TCPM_PD_AMS_STATUS(ucPortIndex) == _PD_AMS_INTERRUPTIBLE))
            {
                // Receive Any Message When Not in AMS or in Interruptible AMS
                ScalerTypeCTcpmPdIntSnkRcvMsgNoAmsProc_EXINT0(ucPortIndex);
            }
            else
            {
                // Rcv. Msg. During Non-Interruptible AMS / Power Transition
                ScalerTypeCTcpmPdIntRcvMsgInAmsProc_EXINT0(ucPortIndex);
            }
            break;

        case _PD_SRC_READY:

            if((GET_TCPM_PD_AMS_STATUS(ucPortIndex) == _PD_AMS_NONE) || (GET_TCPM_PD_AMS_STATUS(ucPortIndex) == _PD_AMS_INTERRUPTIBLE))
            {
                // Receive Any Message When Not in AMS or in Interruptible AMS
                ScalerTypeCTcpmPdIntSrcRcvMsgNoAmsProc_EXINT0(ucPortIndex);
            }
            else
            {
                // Rcv. Msg. During Non-Interruptible AMS / Power Transition
                ScalerTypeCTcpmPdIntRcvMsgInAmsProc_EXINT0(ucPortIndex);
            }
            break;

        case _PD_WDINT_SEND_CBL_DISCOVER_ID:
        case _PD_INT_SEND_CBL_DISCOVER_ID:
        case _PD_INT_WAIT_CBL_DISCOVER_ID_RESP:
        case _PD_WDINT_SEND_CBL_SOFT_RESET:
        case _PD_INT_SEND_CBL_SOFT_RESET:
        case _PD_INT_WAIT_CBL_SOFT_RESET_RESP:

            // Receive Unexpected Msg. Do Soft Reset.
            ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);

            break;

        // Not Expected to Receive Msg. in These States
        case _PD_SRC_START_UP:
        case _PD_SRC_WDINT_SEND_CAP:
        case _PD_SRC_INT_SEND_CAP:
        case _PD_SRC_INT_SEND_ACCEPT_REQ:
        case _PD_SRC_INT_SEND_REJECT_REQ:
        case _PD_SRC_INT_SEND_WAIT_REQ:
        case _PD_SRC_WDINT_TRANSIT_POWER:
        case _PD_SRC_WDINT_SEND_PSRDY:
        case _PD_SRC_INT_SEND_PSRDY:
        case _PD_SNK_INT_SEND_REQUEST:
        case _PD_INT_SEND_SOFTRESET:
        case _PD_INT_SEND_SOFTRESET_RESP:

            ScalerTypeCTcpmPdSendHardRst_EXINT0(ucPortIndex);

            break;

        // Not Ready to Rcv. Message (But May be Possible), Just Ignore
        case _PD_SNK_START_UP:
        case _PD_HARDRESET:
        case _PD_NO_RESPONSE:
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process Rcv. Msg. in Interrupt in SRC_READY During _AMS_NONE/_INTERRUPTIBLE
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntSrcRcvMsgNoAmsProc_EXINT0(BYTE ucPortIndex)
{
    // Set Rp to SinkTxOK (Rp-3A) When Source Receive Message Before Initiate AMS
    if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
    {
        // ROLE_CONTROL [0x1A], [5:4] = b'00(Rp-Def), b'01(Rp-1.5A), b'10(Rp-3A)
        SET_TCPM_ROLE_CONTROL(ucPortIndex, (GET_TCPM_ROLE_CONTROL(ucPortIndex) & (~(_BIT5 | _BIT4))) | (_BIT5));
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));
    }

    // Receive Any Message When Not in AMS or in Interruptible AMS @ _PD_SRC_READY
    switch(GET_TCPM_PD_RCV_MSG(ucPortIndex))
    {
        case _PD_CMD_REQUEST:

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            if(GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON)
            {
                // Cancel TimerEvent for PPS PDO
                ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_PPS_TIMEOUT);
            }
#endif

            // Set AMS to Non-Interruptible
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            // Evaluate if Received Request is Valid
            if(ScalerTypeCTcpmPdCheckRequestValid_EXINT0(ucPortIndex) == _PD_REQUEST_VALID)
            {
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_INT_SEND_ACCEPT_REQ);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_INT_SEND_REJECT_REQ);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_CMD_GET_SRC_CAP:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            // Send "Source Capabilities"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_SRC_CAP);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);

            // FW Solution : Samsung S8 Plug-in then Start, Fail to Light Up
#if((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) && (_TYPE_C_MODAL_OPERATION_SUPPORT == _ON))
            if(GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex))
            {
                // S8 Send "Get Src Cap" When Start, but Not Trying to Initiate Alt Mode as DFP (Scaler UFP / No Alt Mode)
                if((GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_UFP) && (GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) != _PD_DP_CONFIG) && (GET_TCPM_PD_INTEROP_S8(ucPortIndex) == _FALSE))
                {
                    // Wait 5 sec for other Devices to Enter Alt Mode, Timeout : Hard Reset (Cancel : PD Reset, Rcv Discover ID)
                    ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, 5000, _SCALER_TIMER_EVENT_TCPM_S8_HRST);

                    // Set Interop Flag to Prevent From "Non-AM Device with Get Src Cap" Device will be Infinitly Triggered
                    SET_TCPM_PD_INTEROP_S8(ucPortIndex);
                }
            }
#endif
            break;

        case _PD_CMD_GET_SNK_CAP:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            if((GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP) && ((GET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex) == _TRUE)))
            {
                // Send "Sink Capabilities"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_SNK_CAP);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_SNK_CAP, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "Reject"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_PR_SWAP:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            if((GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP) && (GET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex) == _TRUE))
            {
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                {
                    if(GET_TCPM_PD_GET_SNK_CAP_SENT(ucPortIndex) == _FALSE)
                    {
                        // Send "WAIT" Until Get Partnet's Sink Cap
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_WAIT);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_WAIT, _PD_VDM_CMD_RESERVED);
                    }
                    else if(GET_TCPM_PD_PARTNER_EXT_PWR(ucPortIndex) == _TRUE)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_ACCEPT_PRS);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        // Send "Reject"
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                    }
                }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                {
                    if(GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _FALSE)
                    {
                        if(GET_TCPM_PD_GET_SRC_CAP_SENT(ucPortIndex) == _FALSE)
                        {
                            // Send "WAIT" Until Get Partnet's Src Cap
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_WAIT);
                            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_WAIT, _PD_VDM_CMD_RESERVED);
                        }
                        else if(GET_TCPM_PD_PARTNER_SRC_CAP_CHECK_RESULT(ucPortIndex) == _PD_SRC_CAP_VALID)
                        {
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_ACCEPT_PRS);
                            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                        }
                    }
                    else
                    {
                        // Send "Reject"
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                    }
                }
#endif
            }
            else
            {
                if((GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_SRC_ONLY) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0))
                {
                    // Send "Not Support"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "Reject"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_DR_SWAP:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            if(GET_TCPM_PD_DPAM_ENTER(ucPortIndex) == _FALSE)
            {
                if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
                {
                    if(GET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex) == _TRUE)
                    {
                        // Accept Swap from DFP -> UFP
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_ACCEPT_DRS);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        // Reject Swap from DFP -> UFP
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                    }
                }
                else
                {
                    if(GET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex) == _TRUE)
                    {
                        // Accept Swap from UFP -> DFP
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_ACCEPT_DRS);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        // Reject Swap from UFP -> DFP
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                    }
                }
            }
            else
            {
                // Receive DR_SWAP When in Alt Mode : Hard Reset
                ScalerTypeCTcpmPdSendHardRst_EXINT0(ucPortIndex);
            }

            break;

        case _PD_CMD_VCONN_SWAP:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            // Evaluate Vconn Swap : Vconn Source Must "Accept", Not Vconn Source Can "Accept/Reject/Wait"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_ACCEPT_VCS);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_BIST:

            // BIST Mode Operate Only in vSafe5v
            if(GET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex) == 500)
            {
                // BIST Data Object_0 [31:28] BIST Mode
                SET_TCPM_PD_BIST_MODE(ucPortIndex, (g_pucTypeCTcpmPdDataObj_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

                if(GET_TCPM_PD_BIST_MODE(ucPortIndex) == _PD_BIST_CARRIER_MODE)
                {
                    // [31:28] BIST Mode : b'0101 = BIST Carrier Mode

                    // 1. Clear and Enable Tx_SUCCESS + Tx_DISCARD
                    // TCPC will Generate Tx_SUCCESS or Tx_DISCARD after Exit BIST Carrier Mode 2
                    ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, ((WORD)(_TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS)), _ENABLE);

                    // 2. Control TCPC into BIST Carrier Mode : TRANSMIT [0x50] [2:0] SOP Type : 111b (BIST Carrier Mode 2)
                    // On-Semi TCPC Enter Carrier Mode and Exit Mode after 30~60ms
                    ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_TRANSMIT, 0x07);

                    // Back to SRC/SNK Ready in Tx INT (Tx_SUCCESS or Tx_DISCARD)
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_BIST_MODE);
                }
                else if(GET_TCPM_PD_BIST_MODE(ucPortIndex) == _PD_BIST_TEST_DATA_MODE)
                {
                    // [31:28] BIST Mode : b'1000 = BIST Test Data Mode

                    // 1. Control TCPC into BIST Test Data Mode : TCPC_CONTROL [0x19], [1] = b'1 (BIST Test Data Mode)
                    // On-Semi TCPC Auto Resp. GoodCRC and Flush Buffer. Exit Mode When Disconnect or Rcv HRST
                    SET_TCPM_TCPC_CONTROL(ucPortIndex, GET_TCPM_TCPC_CONTROL(ucPortIndex) | (_BIT1));
                    ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_TCPC_CTRL, GET_TCPM_TCPC_CONTROL(ucPortIndex));

                    // Back to SRC/SNK Ready when Disconnect or Rcv HRST
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_BIST_MODE);
                }
            }

            break;

        case _PD_CMD_VDM:

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
            if((GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex)) && (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _TRUE))
            {
                if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
                {   // DFP Rcv Any VDM Resp. or Attention Request When Alt Mode Ready
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
                    if(GET_TCPM_PD_DPAM_SUPPORT(ucPortIndex) == _ON)
                    {
                        ScalerTypeCTcpmPdIntDfpRcvVdmMsgProc_EXINT0(ucPortIndex);
                    }
#endif
                }
                else
                {   // Receive VDM Request, UFP Responds According to Rcv. VDM Msg.
                    ScalerTypeCTcpmPdIntUfpRcvVdmMsgProc_EXINT0(ucPortIndex);
                }
            }
            else
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
            {
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        // PD 3.0 Control Message
        case _PD_CMD_GET_SRC_CAP_EXT:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            // Send "Source Capability Extended"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_SRC_CAP_EXT);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_SRC_CAP_EXT, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_GET_SNK_CAP_EXT:

            if(GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_SRC_ONLY)
            {
                // Send "Not Support"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

                // Send "Sink Capability Extended"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_SNK_CAP_EXT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_SNK_CAP_EXT, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_CMD_GET_STATUS:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            // Send "Status"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_STATUS);

            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_STATUS, _PD_VDM_CMD_RESERVED);

            break;

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
        case _PD_CMD_GET_PPS_STATUS:

            if(GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON)
            {
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

                // Send "Status"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_PPS_STATUS);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_PPS_STATUS, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "Reject"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;
#endif

        // PD 3.0 Data Message
        case _PD_CMD_ALERT:

            SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_ALERT_EVENT);
            SET_TCPM_PD_PARTNER_TYPE_OF_ALERT(ucPortIndex, (EnumTypeCTypeOfAlert)(g_pucTypeCTcpmPdDataObj_EXINT[0]));
            SET_TCPM_PD_PARTNER_BAT_STATUS(ucPortIndex, (EnumTypeCBatteryStatus)(g_pucTypeCTcpmPdDataObj_EXINT[1]));
            SET_TCPM_PD_PARTNER_EXT_ALERT_EVENT(ucPortIndex, (EnumTypeCExtAlertEventType)(g_pucTypeCTcpmPdDataObj_EXINT[3] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            // Check Battery Status
            if((g_pucTypeCTcpmPdDataObj_EXINT[0] & (_BIT1)) == _BIT1)
            {
                // Send "Get Battery Status Message" if Needed
            }

            // Check Status
            if((g_pucTypeCTcpmPdDataObj_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
            {
                // Send "Get Status Message"
                // [MQP] : PROT-SNK3-STATUS(Rev3.0), Shall Initiate GET_STATUS Msg. When SnkTXOK
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_STATUS);
            }

            break;

        // PD 3.0 Extended Message
        case _PD_CMD_GET_MFC_INFO:
#if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
            // Send "Not Support"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
#else
            // Follow Standard Spec.
            // for DRP, PD 3.0 Standard Spec(USB_PD_R3_0 V1.2 20180621 - with ECRs 2018-09-24): Ignore
            if(GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_SRC_ONLY)
            {
                // for SRC Only, Send "Not Support"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
#endif // End of #if(_TYPE_C_EMB_CTS_FLOW == _ON)
#else
            // Byte 0-1 are Ext. Msg Header
            // Manufacturer Info Target "g_pucTypeCTcpmPdDataObj_EXINT[2]" : 0 = Port / 1 = Battery
            if(g_pucTypeCTcpmPdDataObj_EXINT[2] == 0x00)
            {
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

                // Send "Manufacturer Info"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_MFC_INFO);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_MFC_INFO, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Not Support"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
#endif  // End of #if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
            break;

        case _PD_CMD_CHUNK_TEST:

            // Check If This Ext Msg is Chunked : Ext Message Header [15]
            if((GET_TCPM_PD_RCV_EXT_CHUNKED(ucPortIndex) == _TRUE) && (GET_TCPM_PD_RCV_EXT_CHUNK_REQ(ucPortIndex) == _FALSE))
            {
                // If Received Chunk Response Data < Total Message Data Size, Sent Chunk Request
                if(((GET_TCPM_PD_RCV_EXT_CHUNK_NUM(ucPortIndex) + 1) * 26) < GET_TCPM_PD_RCV_EXT_DATA_SIZE(ucPortIndex))
                {
                    // Set Chunk Message As an Chunk Request
                    SET_TCPM_PD_RCV_EXT_CHUNK_REQ(ucPortIndex, _TRUE);

                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

                    // Send "Chunk Test" REQUEST
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_CHK_TEST_REQ);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_CHUNK_TEST, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }

            break;

        // PD 3.0 Control Message
        case _PD_CMD_GET_REVISION:

            // Send "Revision Message"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REVISION);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REVISION, _PD_VDM_CMD_RESERVED);

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        // Receive Unexpected Message in READY State
        case _PD_CMD_RSV:
        case _PD_CMD_GOTOMIN:
        case _PD_CMD_ACCEPT:
        case _PD_CMD_REJECT:
        case _PD_CMD_PS_RDY:
        case _PD_CMD_WAIT:
        case _PD_CMD_SRC_CAP:
        case _PD_CMD_SNK_CAP:
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_NOT_SUPPORT:
        case _PD_CMD_STATUS:
        case _PD_CMD_MFC_INFO:
#endif
            ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);

            break;

        // Receive Redundent Messages in READY State (Ignore)
        case _PD_CMD_GOODCRC:
        case _PD_CMD_PING:

            break;

        // Receive Un-Supported or Un-Recognized Msg. in READY State
        case _PD_CMD_UNDEFINED:
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_GET_COUNTRY_CODES:
        case _PD_CMD_BAT_STATUS:
        case _PD_CMD_GET_COUNTRY_INFO:
        case _PD_CMD_GET_BAT_CAP:
        case _PD_CMD_GET_BAT_STATUS:
        case _PD_CMD_BAT_CAP:
        case _PD_CMD_SEC_REQ:
        case _PD_CMD_SEC_RESP:
        case _PD_CMD_FW_UPDATE_REQ:
        case _PD_CMD_FW_UPDATE_RESP:
        case _PD_CMD_PPS_STATUS:
        case _PD_CMD_COUNTRY_INFO:
        case _PD_CMD_COUNTRY_CODES:
        case _PD_CMD_FR_SWAP:
#endif
        default:

            if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;
    }
}

//--------------------------------------------------
// Description  : Process Rcv. Msg. in Interrupt in SNK_READY During _AMS_NONE/_INTERRUPTIBLE
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntSnkRcvMsgNoAmsProc_EXINT0(BYTE ucPortIndex)
{
    // Receive Any Message When Not in AMS or in Interruptible AMS @ _PD_SNK_READY
    switch(GET_TCPM_PD_RCV_MSG(ucPortIndex))
    {
        case _PD_CMD_SRC_CAP:

            // 1. Store Src_Cap Info from Data Objects
            SET_TCPM_PD_PARTNER_DRP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 5);
            SET_TCPM_PD_PARTNER_SUSPEND(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 4);
            SET_TCPM_PD_PARTNER_EXT_PWR(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 3);
            SET_TCPM_PD_PARTNER_USB_CAP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 2);
            SET_TCPM_PD_PARTNER_DRD(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 1);
            SET_TCPM_PD_PARTNER_UNCHK(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 0);
            SET_TCPM_PD_PARTNER_EPR_CAP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[1] >> 7);

            // Get Number Of Capabilities
            SET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex, GET_TCPM_PD_RCV_NOD_CNT(ucPortIndex));

            // Evaluate and Set Request Data Objects
            for(BYTE ucLoopIndex = 0; ucLoopIndex < _TYPE_C_PDO_NUM_7; ucLoopIndex++)
            {
                if(ucLoopIndex < GET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex))
                {
                    if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                    {
                        // Set APDO Type
                        SET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                    }
                    else
                    {
                        // Set PDO Type
                        SET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) >> 6));
                    }

                    if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                        SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex, (((((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & 0x01)) << 7) | (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] & 0xFE)) >> 1)) * 10));
                        SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, ucLoopIndex, (((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2]) * 10));
                        SET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, ucLoopIndex, (((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 3] & 0x7F) * 5));
                    }
                    else
                    {
                        // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                        SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex, (((((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2] & 0xFC)) >> 2)) * 5));
                        SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, ucLoopIndex, GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex));
                        SET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, ucLoopIndex, (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 3]));
                        SET_TCPM_PD_PARTNER_SRC_PEAK_CUR(ucPortIndex, ucLoopIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] & (_BIT5 | _BIT4)) >> 4));

                        // If Target Voltage Matches Partner's Voltage, Set the Macros of Capability Mismatch and Object Position.
                        if((GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_TARGET_VOL) && (GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex) == (GET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex) * 100)))
                        {
                            SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _FALSE);
                            SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, (EnumTypeCPdoNumber)(ucLoopIndex + 1));
                        }
                    }
                }
                else
                {
                    // If ucLoopIndex >= GET_TCPM_PD_PARTNER_SRC_CAP_CNT(), Clear the Related Macros to 0x00.
                    SET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex, _PD_NONE_SETTING_PDO);
                    SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex, 0x00);
                    SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, ucLoopIndex, 0x00);
                    SET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, ucLoopIndex, 0x00);
                    SET_TCPM_PD_PARTNER_SRC_PEAK_CUR(ucPortIndex, ucLoopIndex, 0x00);
                }
            }

            // According to the corresponding Request Type, Set the Macros of Capability Mismatch and Object Position.
            if(GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_LOWEST_VOL)
            {
                SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _FALSE);
                SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, _TYPE_C_PDO_NUM_1);
            }
            else if(GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_HIGHEST_VOL)
            {
                SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _FALSE);

                // Select Highest Fix PDO
                for(BYTE ucLoopIndex = GET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex); ucLoopIndex > 0; ucLoopIndex--)
                {
                    if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex - 1) == _PD_FIX_SUPPLY_PDO)
                    {
                        SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, (EnumTypeCPdoNumber)(ucLoopIndex));

                        break;
                    }
                }
            }
            else if((GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_TARGET_VOL) && (GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) != (GET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex) * 100)))
            {
                SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _TRUE);
                SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, _TYPE_C_PDO_NUM_1);
            }

            // If Request Type isn't Customized RDO, Need to be Set Operating and Max. Current.
            if(GET_TCPM_PD_REQ_TYPE(ucPortIndex) != _TYPE_C_REQ_CUSTOMIZED_RDO)
            {
                SET_TCPM_PD_REQ_INFO_1(ucPortIndex, GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1));
                SET_TCPM_PD_REQ_INFO_2(ucPortIndex, GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1));
            }

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);

            // Send Request (Success : Wait Resp / Fail : Hard Reset)
            SET_TCPM_PD_RCV_SRC_CAP(ucPortIndex);
            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_INT_SEND_REQUEST);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REQUEST, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_GET_SRC_CAP:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            // if Able to Become Src, Reply "Src_Cap", Otherwise "Reject"
            if((GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP) && ((GET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex) == _TRUE)))
            {
                // Send "Source Capabilities"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_SRC_CAP);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "Reject"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_GET_SNK_CAP:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            // Send "Sink Capabilities"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_SNK_CAP);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_SNK_CAP, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_PR_SWAP:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            if((GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP) && (GET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex) == _TRUE) && (GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _TRUE))
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_ACCEPT_PRS);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "Reject"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_DR_SWAP:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            if(GET_TCPM_PD_DPAM_ENTER(ucPortIndex) == _FALSE)
            {
                if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
                {
                    if(GET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex) == _TRUE)
                    {
                        // Accept Swap from DFP -> UFP
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_ACCEPT_DRS);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        // Reject Swap from DFP -> UFP
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                    }
                }
                else
                {
                    if(GET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex) == _TRUE)
                    {
                        // Accept Swap from UFP -> DFP
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_ACCEPT_DRS);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        // Reject Swap from UFP -> DFP
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                    }
                }
            }
            else
            {
                // Receive DR_SWAP When in Alt Mode : Hard Reset
                ScalerTypeCTcpmPdSendHardRst_EXINT0(ucPortIndex);
            }

            break;

        case _PD_CMD_VCONN_SWAP:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            if(GET_TCPM_CC_PORT_ROLE(ucPortIndex) != _TYPE_C_PORT_SNK_ONLY)
            {
                // Evaluate Vconn Swap : Vconn Source Must "Accept", Not Vconn Source Can "Accept/Reject/Wait"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_ACCEPT_VCS);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Sink Only : Send Reject to Vconn Swap
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_CMD_BIST:

            // BIST Mode Operate Only in vSafe5v
            if(GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) == 1)
            {
                // BIST Data Object_0 [31:28] BIST Mode
                SET_TCPM_PD_BIST_MODE(ucPortIndex, (g_pucTypeCTcpmPdDataObj_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

                if(GET_TCPM_PD_BIST_MODE(ucPortIndex) == _PD_BIST_CARRIER_MODE)
                {
                    // [31:28] BIST Mode : b'0101 = BIST Carrier Mode

                    // 1. Clear and Enable Tx_SUCCESS + Tx_DISCARD
                    // TCPC will Generate Tx_SUCCESS or Tx_DISCARD after Exit BIST Carrier Mode 2
                    ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, ((WORD)(_TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS)), _ENABLE);

                    // 2. Control TCPC into BIST Carrier Mode : TRANSMIT [0x50] [2:0] SOP Type : 111b (BIST Carrier Mode 2)
                    // On-Semi TCPC Enter Carrier Mode and Exit Mode after 30~60ms
                    ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_TRANSMIT, 0x07);

                    // Back to SRC/SNK Ready in Tx INT (Tx_SUCCESS or Tx_DISCARD)
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_BIST_MODE);
                }
                else if(GET_TCPM_PD_BIST_MODE(ucPortIndex) == _PD_BIST_TEST_DATA_MODE)
                {
                    // [31:28] BIST Mode : b'1000 = BIST Test Data Mode

                    // 1. Control TCPC into BIST Test Data Mode : TCPC_CONTROL [0x19], [1] = b'1 (BIST Test Data Mode)
                    // On-Semi TCPC Auto Resp. GoodCRC and Flush Buffer. Exit Mode When Disconnect or Rcv HRST
                    SET_TCPM_TCPC_CONTROL(ucPortIndex, GET_TCPM_TCPC_CONTROL(ucPortIndex) | (_BIT1));
                    ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_TCPC_CTRL, GET_TCPM_TCPC_CONTROL(ucPortIndex));

                    // Back to SRC/SNK Ready when Disconnect or Rcv HRST
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_BIST_MODE);
                }
            }

            break;

        case _PD_CMD_VDM:

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
            if((GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex)) && (GET_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex) == _TRUE))
            {
                if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
                {   // DFP Rcv Any VDM Resp. or Attention Request When Alt Mode Ready
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
                    if(GET_TCPM_PD_DPAM_SUPPORT(ucPortIndex) == _ON)
                    {
                        ScalerTypeCTcpmPdIntDfpRcvVdmMsgProc_EXINT0(ucPortIndex);
                    }
#endif
                }
                else
                {   // Receive VDM Request, UFP Responds According to Rcv. VDM Msg.
                    ScalerTypeCTcpmPdIntUfpRcvVdmMsgProc_EXINT0(ucPortIndex);
                }
            }
            else
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
            {
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
            }


            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        // PD 3.0 Control Message
        case _PD_CMD_GET_SRC_CAP_EXT:

            if(GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_SNK_ONLY)
            {
                // Send "Not Support"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

                // Send "Source Capability Extended"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_SRC_CAP_EXT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_SRC_CAP_EXT, _PD_VDM_CMD_RESERVED);
            }
            break;

        case _PD_CMD_GET_SNK_CAP_EXT:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            // Send "Sink Capability Extended"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_SNK_CAP_EXT);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_SNK_CAP_EXT, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_GET_STATUS:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            // Send "Status"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_STATUS);

            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_STATUS, _PD_VDM_CMD_RESERVED);

            break;

        // PD 3.0 Data Message
        case _PD_CMD_ALERT:

            SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_ALERT_EVENT);
            SET_TCPM_PD_PARTNER_TYPE_OF_ALERT(ucPortIndex, (EnumTypeCTypeOfAlert)(g_pucTypeCTcpmPdDataObj_EXINT[0]));
            SET_TCPM_PD_PARTNER_BAT_STATUS(ucPortIndex, (EnumTypeCBatteryStatus)(g_pucTypeCTcpmPdDataObj_EXINT[1]));
            SET_TCPM_PD_PARTNER_EXT_ALERT_EVENT(ucPortIndex, (EnumTypeCExtAlertEventType)(g_pucTypeCTcpmPdDataObj_EXINT[3] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            // Check Battery Status
            if((g_pucTypeCTcpmPdDataObj_EXINT[0] & (_BIT1)) == _BIT1)
            {
                // Send "Get Battery Status Message" if Needed
            }

            // Check Status
            if((g_pucTypeCTcpmPdDataObj_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
            {
                // Send "Get Status Message"
                // [MQP] : PROT-SNK3-STATUS(Rev3.0), Shall Initiate GET_STATUS Msg. When SnkTXOK
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_GET_STATUS);
            }

            break;

        // PD 3.0 Extended Message
        case _PD_CMD_GET_MFC_INFO:
#if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
            // PD 3.0 Standard Spec(USB_PD_R3_0 V1.2 20180621 - with ECRs 2018-09-24): Ignore
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
            // Send "Not Support"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
#endif // End of #if(_TYPE_C_EMB_CTS_FLOW == _ON)
#else
            // Byte 0-1 are Ext. Msg Header
            // Manufacturer Info Target "g_pucTypeCTcpmPdDataObj_EXINT[2]" : 0 = Port / 1 = Battery
            if(g_pucTypeCTcpmPdDataObj_EXINT[2] == 0x00)
            {
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

                // Send "Manufacturer Info"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_MFC_INFO);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_MFC_INFO, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Not Support"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
#endif  // End of #if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
            break;

        case _PD_CMD_CHUNK_TEST:

            // Check If This Ext Msg is Chunked : Ext Message Header [15]
            if((GET_TCPM_PD_RCV_EXT_CHUNKED(ucPortIndex) == _TRUE) && (GET_TCPM_PD_RCV_EXT_CHUNK_REQ(ucPortIndex) == _FALSE))
            {
                // If Received Chunk Response Data < Total Message Data Size, Sent Chunk Request
                if(((GET_TCPM_PD_RCV_EXT_CHUNK_NUM(ucPortIndex) + 1) * 26) < GET_TCPM_PD_RCV_EXT_DATA_SIZE(ucPortIndex))
                {
                    // Set Chunk Message As an Chunk Request
                    SET_TCPM_PD_RCV_EXT_CHUNK_REQ(ucPortIndex, _TRUE);

                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

                    // Send "Chunk Test" REQUEST
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_CHK_TEST_REQ);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_CHUNK_TEST, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }

            break;

        // PD 3.0 Control Message
        case _PD_CMD_GET_REVISION:

            // Send "Revision Message"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REVISION);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REVISION, _PD_VDM_CMD_RESERVED);

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        // Receive Unexpected Message in READY State
        case _PD_CMD_ACCEPT:
        case _PD_CMD_REJECT:
        case _PD_CMD_PS_RDY:
        case _PD_CMD_WAIT:
        case _PD_CMD_REQUEST:
        case _PD_CMD_SNK_CAP:
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_NOT_SUPPORT:
        case _PD_CMD_STATUS:
        case _PD_CMD_MFC_INFO:
#endif
            ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);

            break;


        // Receive Redundent Message in READY State (Ignore)
        case _PD_CMD_GOODCRC:
        case _PD_CMD_PING:

            break;

        // Receive Un-Supported or Un-Recognized Messages
        case _PD_CMD_RSV:
        case _PD_CMD_GOTOMIN:
        case _PD_CMD_UNDEFINED:
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_GET_PPS_STATUS:
        case _PD_CMD_GET_COUNTRY_CODES:
        case _PD_CMD_BAT_STATUS:
        case _PD_CMD_GET_COUNTRY_INFO:
        case _PD_CMD_GET_BAT_CAP:
        case _PD_CMD_BAT_CAP:
        case _PD_CMD_GET_BAT_STATUS:
        case _PD_CMD_SEC_REQ:
        case _PD_CMD_SEC_RESP:
        case _PD_CMD_FW_UPDATE_REQ:
        case _PD_CMD_FW_UPDATE_RESP:
        case _PD_CMD_PPS_STATUS:
        case _PD_CMD_COUNTRY_INFO:
        case _PD_CMD_COUNTRY_CODES:
        case _PD_CMD_FR_SWAP:
#endif
        default:

            if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_REJECT);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;
    }
}

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DFP Rcv. SOP VDM Message Proc
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntDfpRcvVdmMsgProc_EXINT0(BYTE ucPortIndex)
{
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
    EnumInputPort enumInputPort = ScalerTypeCPcbPortConvertToDx_EXINT0(g_penumTypeCTcpmPort[ucPortIndex]);
#endif

    if(GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_INT_WAIT_VDM_RESP)
    {
        CLR_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex);

        // Cancel TimerEvent (Sender Response Timer = 24-30ms)
        ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);

        switch(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex))
        {
            case _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP:

                if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_ID_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'00(2.0), b'01 (2.1)
                    if((GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1) && ((g_pucTypeCTcpmPdDataObj_EXINT[2] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) <= (_BIT5)))
                    {
                        // if((Current SVDM >= 2.1) & (Rcv SVDM <= 2.0)), Downgrade to SVDM 2.0 Earlier & DPAM 2.0 Earlier
                        SET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex, _PD_SVDM_VER_2_0_EARLIER);
                        SET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_0_EARLIER);
                    }

                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_SVID);
                }
                else
                {
                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP:

                if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_SVID_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID))
                {
                    if(ScalerTypeCTcpmPdSearchSvid_EXINT0(ucPortIndex) == _TRUE)
                    {   // If Find DP_SID = 0xFF01, Send Discover Mode
                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_MODE);
                    }
                    else
                    {
                        // If Search Fnish = FALSE, Send Discover SVID Again to Get More SVID
                        if(GET_TCPM_PD_DPAM_SVID_SEARCH_FINISH(ucPortIndex) == _FALSE)
                        {
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_SVID);
                        }
                        else
                        {   // No More SVID and Cannot Find DP_SID, Stop Alt. Mode Flow
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                        }
                    }
                }
                else
                {
                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DISCOVER_MODE_RESP:

                if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_MODE_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                {
                    // Search All Modes to Get DP Port Capability (DP_Tx) and Pin Assignment ( C / D / E )
                    ScalerTypeCTcpmPdSearchMode_EXINT0(ucPortIndex);

                    if(GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex) == 0)
                    {   // Cannot Find Any Acceptable Configuration, Stop Alt. Mode Flow
                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                    }
                    else
                    {
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
                        // Start to Discover Cable According to DPAM 2.1
                        if(GET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex) == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)
                        {
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P);
                        }
                        else if(GET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex) == _TYPE_C_CABLE_NON_PD_CAPABLE)
                        {
                            // If Cable is Non-PD Capable, Set Passive Cable & HBR3 According to DPAM2.1
                            SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_PASSIVE);
                            SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_HBR3);

                            // Stop Enter DP Alt Mode Flow Just for Cable
                            CLR_TCPM_PD_CBL_ENTER_DP_MODE_SUPPORT(ucPortIndex);
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
                        }
                        else
                        {
                            // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable(When Ack Vdo Received For Discover Id(SOP'/SOP''))
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableId_EXINT0(ucPortIndex));
                        }
#else
                        // Use the Object Position Selected in Function to Initiate Enter Mode
                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
#endif  // End of #if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
                    }
                }
                else
                {
                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP:

                if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_ENTER_MODE_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID) && (GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex) == GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex)))
                {
                    // Set DP Enter Mode Flag
                    SET_TCPM_PD_DPAM_ENTER(ucPortIndex);

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                    {
                        // Push _PD_HPD_LOW into HPD_Queue
                        ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], _PD_HPD_LOW, 0);
                    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                    {
                        // Clear HPD Queue
                        ScalerTypeCTcpmPdClrHpd_EXINT0(ucPortIndex);
                    }
#endif

                    // Transit to "DP_STATUS" to Send DP_Status REQ
                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_STATUS);
                }
                else
                {
                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP:

                if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_EXIT_MODE_ACK) || (GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_EXIT_MODE_NAK))
                {
                    CLR_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex);

                    // Clear Alt. Mode Status
                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_NONE);
                    CLR_TCPM_PD_DPAM_ENTER(ucPortIndex);
                    SET_TCPM_PD_DPAM_CONFIG(ucPortIndex, _PD_USB_CONFIG);

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                    {
                        ScalerDpAuxRxHpdTogglePhyResetProc(enumInputPort, _LOW);
                        SET_TCPM_PD_HPD_STATUS(ucPortIndex, _LOW);
                    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                    {
                        ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], _PD_HPD_LOW, 0);
                    }
#endif
                }
                else
                {
                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DP_STATUS_RESP:

                if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_50) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID) && (GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex) == GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex)))
                {
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                    {
                        // Pop Out One HPD From Queue
                        ScalerTypeCTcpmPdPopHpd_EXINT0(ucPortIndex);
                    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                    {
                        // DP_TX Update DP_RX HPD Status
                        ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], ScalerTypeCTcpmPdDecodePartnerHpdStatus_EXINT0(), 0);
                    }
#endif
                    if(ScalerTypeCTcpmPdCheckDpStatus_EXINT0(ucPortIndex) == _PD_CONFIG_REQUIRED)
                    {
                        if(GET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex) == _PD_DP_CONFIG)
                        {
                            // Check Avaliable Pin Assignment
                            if(ScalerTypeCTcpmPdDfpJudgePinAssignment_EXINT0(ucPortIndex) == _TRUE)
                            {
                                // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                                if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                                }
                                else
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                                }
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }
                        }
                        else
                        {
                            SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_NONE);

                            // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                            if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                        }
                    }
                    else
                    {
                        if(GET_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex) == _TRUE)
                        {
                            // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Exit Mode First
                            if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                        }
                        else
                        {
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_ATTENTION);
                        }
                    }

                    // Update Port Partner DP Status
                    // Warning : PartnerDpStatus Shall Update After CheckDpStatus, Otherwise, MULTI_FUNCTION_CHANGE Macro Would Judge Incorrectly !!!
                    ScalerTypeCTcpmPdUpdatePortPartnerDpStatus_EXINT0(ucPortIndex, _PD_VDM_DP_CMD_DP_STATUS_ACK);
                }
                else
                {
                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_ATTENTION);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP:

                if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_51) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID) && (GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex) == GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex)))
                {
                    // Swith DP Lane Mapping
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                    {
                        ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(enumInputPort, GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
                    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                    {
                        ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToPx_EXINT0(g_penumTypeCTcpmPort[ucPortIndex]), GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
                    }
#endif

                    SET_TCPM_PD_DPAM_CONFIG(ucPortIndex, GET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex));

                    if(GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG)
                    {
                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_READY);

                        // Multi-Function Bit Change Process(Pin Assignment C <=> Pin Assignment D) Done.
                        if(GET_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(ucPortIndex) == _TRUE)
                        {
                            SET_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE_DONE(ucPortIndex);
                        }
                    }
                    else
                    {
                        if(GET_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex) == _TRUE)
                        {
                            // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Exit Mode First
                            if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                        }
                        else
                        {
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_ATTENTION);
                        }
                    }
                }
                else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_91) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                {
                    // Rcv DP Config Nak
                    if(GET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex) == _PD_USB_CONFIG)
                    {
                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_ATTENTION);
                    }
                    else
                    {
                        SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_NONE);
                        SET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex, _PD_USB_CONFIG);

                        // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                        if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                        {
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                        }
                        else
                        {
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                        }
                    }
                }
                else
                {
                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                }

                // Clear Multi-Function Change When Rcv DP Config Ack / Nak
                if(GET_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(ucPortIndex) == _TRUE)
                {
                    CLR_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(ucPortIndex);
                }

                break;

            case _PD_ALT_MODE_READY:

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                {
                    if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_50) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID) && (GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex) == GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex)))
                    {
                        if(GET_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex) == _TRUE)
                        {
                            CLR_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex);
                        }
                        else
                        {
                            // Set WAIT FLAG to Prevent from Sending Attention in HPD Space Time
                            if(GET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)) != 0)
                            {
                                SET_TCPM_PD_DPAM_ATTENTION_WAIT(ucPortIndex);
                                ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, GET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)), _SCALER_TIMER_EVENT_TCPM_CLR_ATTENTION_WAIT);
                            }

                            // Pop Out One HPD From Queue
                            ScalerTypeCTcpmPdPopHpd_EXINT0(ucPortIndex);
                        }

                        if(ScalerTypeCTcpmPdCheckDpStatus_EXINT0(ucPortIndex) == _PD_CONFIG_REQUIRED)
                        {
                            if(GET_TCPM_PD_HPD_STATUS(ucPortIndex) == _LOW)
                            {
                                SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_NONE);

                                // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                                if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                                }
                                else
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                                }
                            }
                            else
                            {
                                // Push _PD_HPD_LOW into HPD_Queue
                                ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], _PD_HPD_LOW, 0);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_STATUS);
                            }
                        }

                        // Update Port Partner DP Status
                        // Warning : PartnerDpStatus Shall Update After CheckDpStatus, Otherwise, MULTI_FUNCTION_CHANGE Macro Would Judge Incorrectly !!!
                        ScalerTypeCTcpmPdUpdatePortPartnerDpStatus_EXINT0(ucPortIndex, _PD_VDM_DP_CMD_DP_STATUS_ACK);
                    }
                    else
                    {
                        if(GET_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex) == _TRUE)
                        {
                            CLR_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex);

                            // Push HPD_IRQ into HPD Queue When Received Unexpected Msg during Force Sending HPD IRQ Process, then PD will Re-Send HPD_IRQ in Main loop
                            ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], _PD_HPD_IRQ, 0);
                        }
                    }
                }
#endif

                break;

            case _PD_ALT_MODE_NONE:
            case _PD_ALT_MODE_ERROR:
            default:
                // Not Expected to Receive Any Message (Except For ALT_MODE_READY Which May Rcv DP_Status ACK)
                break;
        }

        SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

        // Back to Ready State
        ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
    }
    else
    {
        switch((EnumTypeCVdmCmd)GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex))
        {
            case _PD_VDM_CMD_DISCOVER_ID_REQ:

                // PD Merged Test [TEST.PD.VDM.SRC.1], and [TEST.PD.VDM.SRC.2]
                if((GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0))
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover ID ACK"
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_ACK);
                }
                else
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover ID NAK" or "Ignore"
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_NAK);
                }

                break;

            case _PD_VDM_CMD_DISCOVER_SVID_REQ:

                // PD Merged Test [TEST.PD.VDM.SRC.1], and [TEST.PD.VDM.SRC.2]
                if((GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0))
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover SVID ACK"
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_ACK);
                }
                else
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover SVID NAK" or "Ignore"
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_NAK);
                }

                break;

            case _PD_VDM_CMD_DISCOVER_MODE_REQ:

                // PD Merged Test [TEST.PD.VDM.SRC.1], and [TEST.PD.VDM.SRC.2]
                if((GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0))
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover Mode ACK" to Display Port
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);
                }
                else
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover Mode NAK" to Uncongnized SID
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_NAK);
                }

                break;

            case _PD_VDM_CMD_ATTENTION_REQ:

                // Check if SVID is correct, and Valid State to Receive Attention (DO Not Check Object Position)
                if((GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID) && ((GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) == _PD_ALT_MODE_INT_WAIT_ATTENTION) || (GET_TCPM_PD_DP_ALT_STATE(ucPortIndex) == _PD_ALT_MODE_READY)))
                {
#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                    {
                        // DP_TX Update DP_RX HPD Status
                        ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], ScalerTypeCTcpmPdDecodePartnerHpdStatus_EXINT0(), 0);
                    }
#endif
                    if(ScalerTypeCTcpmPdCheckDpStatus_EXINT0(ucPortIndex) == _PD_CONFIG_REQUIRED)
                    {
                        if(GET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex) == _PD_DP_CONFIG)
                        {
                            // Check Avaliable Pin Assignment
                            if(ScalerTypeCTcpmPdDfpJudgePinAssignment_EXINT0(ucPortIndex) == _TRUE)
                            {
                                // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                                if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                                }
                                else
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                                }
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }
                        }
                        else
                        {
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                            {
                                if(GET_TCPM_PD_HPD_STATUS(ucPortIndex) == _LOW)
                                {
                                    SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_NONE);

                                    // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                                    if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                                    {
                                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                                    }
                                    else
                                    {
                                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                                    }
                                }
                                else
                                {
                                    // Push _PD_HPD_LOW into HPD_Queue
                                    ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], _PD_HPD_LOW, 0);

                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_STATUS);
                                }
                            }
#endif  // End of #if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                            {
                                ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], _PD_HPD_LOW, 0);

                                SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_NONE);

                                // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                                if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                                }
                                else
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                                }
                            }
#endif  // End of #if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                        }
                    }
                    else
                    {
                        if(GET_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex) == _TRUE)
                        {
                            // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Exit Mode First
                            if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                        }
                    }

                    // Update Port Partner DP Status
                    // Warning : PartnerDpStatus Shall Update After CheckDpStatus, Otherwise, MULTI_FUNCTION_CHANGE Macro Would Judge Incorrectly !!!
                    ScalerTypeCTcpmPdUpdatePortPartnerDpStatus_EXINT0(ucPortIndex, _PD_VDM_DP_CMD_ATTENTION_REQ);
                }

                break;

            default:
                // Not Going to Happens, Receive Un-Recognized VDM Request, Reply NAK or Ignore?
                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : UFP Rcv. SOP VDM Message Proc
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntUfpRcvVdmMsgProc_EXINT0(BYTE ucPortIndex)
{
    // UFP Only Response to VDM Request, Ignore All Illegal ACK/NAK/BUSY
    if((GET_TCPM_PD_RCV_VDM_TYPE(ucPortIndex) == _PD_STRUCTURED_VDM) && (GET_TCPM_PD_RCV_VDM_CMD_TYPE(ucPortIndex) == _PD_VDM_CMD_TYPE_REQ))
    {
        if(GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID)
        {
            switch((EnumTypeCVdmCmd)GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex))
            {
                case _PD_VDM_CMD_DISCOVER_ID_REQ:

                    // FW Solution : Samsung S8 Plug-in then Start, Fail to Light Up
#if((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) && (_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON))
                    if(GET_TCPM_PD_DPAM_SUPPORT(ucPortIndex))
                    {
                        // If Rcv Discover ID, Cancel S8 HRST, Since Alt Mode Flow Start
                        ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_S8_HRST);

                        // Clear Interop to Enable S8 FW Solution, When Alt Mode Flow Has Been Start
                        CLR_TCPM_PD_INTEROP_S8(ucPortIndex);
                    }
#endif

                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'00(2.0), b'01 (2.1)
                    if((GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1) && ((g_pucTypeCTcpmPdDataObj_EXINT[2] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) <= (_BIT5)))
                    {
                        // if((Current SVDM >= 2.1) & (Rcv SVDM <= 2.0)), Downgrade to SVDM 2.0 Earlier & DPAM 2.0 Earlier
                        SET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex, _PD_SVDM_VER_2_0_EARLIER);
                        SET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_0_EARLIER);
                    }

                    if(GET_TCPM_PD_DPAM_ENTER(ucPortIndex) == _FALSE)
                    {
                        // If Dp Alt Mode has not entered, Set Partner Initial Alt Mode Macro
                        SET_TCPM_PD_PARTNER_INIT_ALT_MODE(ucPortIndex);
                    }

                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover ID ACK"
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_ACK);

                    break;

                case _PD_VDM_CMD_DISCOVER_SVID_REQ:

                    if(GET_TCPM_PD_DPAM_ENTER(ucPortIndex) == _FALSE)
                    {
                        // If Dp Alt Mode has not entered, Set Partner Initial Alt Mode Macro
                        SET_TCPM_PD_PARTNER_INIT_ALT_MODE(ucPortIndex);
                    }

                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                    if((GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SNK) && (GET_TCPM_PD_DPAM_ENTER(ucPortIndex) == _TRUE) && (GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_USB_CONFIG))
                    {
                        // FW Solution For Lenovol T480 : Fail To Light Up When Received Twice SVID(Second Svid Received Between Enter Mode and Dp Configure)
                        // Time Out: Do Error Recovery, Start From Unattach.SRC. If Go to DP Configure Successfully in 1s, Cancel WD Timer Event.
                        ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _T480_ERROR_RECOVERY_TIMER, _SCALER_TIMER_EVENT_TCPM_T480_ERROR_RECOVERY);
                    }

                    // Send "Discover SVID ACK"
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_ACK);

                    break;

                default:

                    // If Attention Command request is an Unrecognized Message it Shall be Ignored
                    // Otherwise, Send NAK Command to Uncongnized Message
                    if(!((EnumTypeCVdmCmd)GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_ATTENTION_REQ))
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                        // Send NAK Command to Uncongnized SVID
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) | _BIT7);
                    }

                    break;
            }
        }
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
        else if((GET_TCPM_PD_DPAM_SUPPORT(ucPortIndex)) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
        {   // Receive DP Alt Mode VDM Request, UFP Responds According to Rcv. VDM Msg.
            ScalerTypeCTcpmPdIntUfpRcvDpVdmMsgProc_EXINT0(ucPortIndex);
        }
#endif
        else
        {
            // If Attention Command request is an Unrecognized Message it Shall be Ignored
            // Otherwise, Send NAK Command to Uncongnized SVID
            if(!((EnumTypeCVdmCmd)GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_ATTENTION_REQ))
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send NAK Command to Uncongnized SVID
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) | _BIT7);
            }
        }
    }
    else if(GET_TCPM_PD_RCV_VDM_TYPE(ucPortIndex) == _PD_UNSTRUCTURED_VDM)
    {
        // PD Merged Test [TEST.PD.VDM.SNK.7] :
        // For Rcv. Unstructured VDM : PD2.0 Should Ignore, PD3.0 Should Resp. w/ Not Support
        if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
        {
            // Send "Not Support"
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
        }
    }
}

#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : UFP Rcv. SOP Dp VDM Message Proc
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntUfpRcvDpVdmMsgProc_EXINT0(BYTE ucPortIndex)
{
    switch((EnumTypeCVdmDpCmd)GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex))
    {
        case _PD_VDM_DP_CMD_DISCOVER_MODE_REQ:

            if(GET_TCPM_PD_DPAM_ENTER(ucPortIndex) == _FALSE)
            {
                // If Dp Alt Mode has not entered, Set Partner Initial Alt Mode Macro
                SET_TCPM_PD_PARTNER_INIT_ALT_MODE(ucPortIndex);
            }

            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

            // Send "Discover Mode ACK" to Display Port
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);

            break;

        case _PD_VDM_DP_CMD_ENTER_MODE_REQ:

            if(GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex) == 1)
            {
                // If Source Choose to Enter DP Alt Mode. Set Object Position to 1
                SET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex, GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex));

                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK);
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Enter Mode ACK"
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_ACK);
            }
            else
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Enter Mode NAK"
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_NAK);
            }

            break;

        case _PD_VDM_DP_CMD_EXIT_MODE_REQ:

            // If Obj Pos = DP_Alt_Mode or Exit All Modes & Already in Alt_Mode
            if(((GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex) == GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex)) || (GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex) == 7)) && (GET_TCPM_PD_DPAM_ENTER(ucPortIndex) == _TRUE))
            {
                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK);
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode ACK"
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_ACK);
            }
            else
            {
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode NAK"
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_NAK);
            }

            break;

        case _PD_VDM_DP_CMD_DP_STATUS_REQ:

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
            // If Obj Pos = DP_Alt_Mode & Already in Alt_Mode
            // Lecroy [TD.DP.10.2.05] and DP Alt Mode Standard 3.9.2.1 : When DP Alt Mode is not enabled, PD shall not transmit any DisplayPort Status Update Command.
            if((GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex) == GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex)) && (GET_TCPM_PD_DPAM_ENTER(ucPortIndex) == _TRUE))
#endif
            {
#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                {
                    // DP_TX Update DP_RX HPD Status
                    ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], ScalerTypeCTcpmPdDecodePartnerHpdStatus_EXINT0(), 0);
                }
#endif
                // Update Port Partner DP Status
                ScalerTypeCTcpmPdUpdatePortPartnerDpStatus_EXINT0(ucPortIndex, _PD_VDM_DP_CMD_DP_STATUS_REQ);

                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_SEND_DP_STATUS_ACK);
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "DP_Status ACK"
                ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_50);
            }

            break;

        case _PD_VDM_DP_CMD_DP_CONFIG_REQ:

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
            // If Obj Pos = DP_Alt_Mode & Already in Alt_Mode
            if((GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex) == GET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex)) && (GET_TCPM_PD_DPAM_ENTER(ucPortIndex) == _TRUE))
#endif
            {
#if(_TYPE_C_DPAM_VERSION == _DPAM_VERSION_2_1)
                // Save Related DP Capabilities Info(From Dp Configure REQ) of Cable To Fill Into DPCD(DPAM v2.1)
                ScalerTypeCTcpmPdUfpSaveCableInfoForDpcd_EXINT0(ucPortIndex);
#endif
                // REQ as DP_RX & Pin Assignment C / D / E || Config USB & Pin Assignment NONE
                if(ScalerTypeCTcpmPdCheckDpConfig_EXINT0(ucPortIndex) == _TRUE)
                {
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                    {
                        ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToDx_EXINT0(g_penumTypeCTcpmPort[ucPortIndex]), GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
                    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                    {
                        ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToPx_EXINT0(g_penumTypeCTcpmPort[ucPortIndex]), GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex), GET_TCPM_ORIENTATION(ucPortIndex));
                    }
#endif

                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_SEND_DP_CONFIG_ACK);
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "DP_Configure ACK"
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_51);
                }
                else
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_VDM_RESP);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "DP_Configure NAK"
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_91);
                }
            }

            break;

        default:
            // Not Going to Happens, Receive Un-Recognized VDM Request, Reply NAK or Ignore?
            break;
    }
}
#endif // End of #if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Process Rcv. Msg. in Interrupt in SNK_READY During _AMS_NON_INTERRUPTIBLE/_AMS_POWER_TRANSITION
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntRcvMsgInAmsProc_EXINT0(BYTE ucPortIndex)
{
    switch(GET_TCPM_PD_SUB_STATE(ucPortIndex))
    {
        case _PD_SUB_INT_WAIT_SRC_CAP:

            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_SRC_CAP)
            {
                // 1. Store Src_Cap Info from Data Objects
                SET_TCPM_PD_PARTNER_DRP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 5);
                SET_TCPM_PD_PARTNER_SUSPEND(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 4);
                SET_TCPM_PD_PARTNER_EXT_PWR(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 3);
                SET_TCPM_PD_PARTNER_USB_CAP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 2);
                SET_TCPM_PD_PARTNER_DRD(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 1);
                SET_TCPM_PD_PARTNER_UNCHK(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 0);
                SET_TCPM_PD_PARTNER_EPR_CAP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[1] >> 7);

                // Get Number Of Capabilities
                SET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex, GET_TCPM_PD_RCV_NOD_CNT(ucPortIndex));

                // Evaluate and Set Request Data Objects
                for(BYTE ucLoopIndex = 0; ucLoopIndex < _TYPE_C_PDO_NUM_7; ucLoopIndex++)
                {
                    if(ucLoopIndex < GET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex))
                    {
                        if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                        {
                            // Set APDO Type
                            SET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                        }
                        else
                        {
                            // Set PDO Type
                            SET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) >> 6));
                        }

                        if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                        {
                            // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                            SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex, (((((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & 0x01)) << 7) | (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] & 0xFE)) >> 1)) * 10));
                            SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, ucLoopIndex, (((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2]) * 10));
                            SET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, ucLoopIndex, (((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 3] & 0x7F) * 5));
                        }
                        else
                        {
                            // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                            SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex, (((((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2] & 0xFC)) >> 2)) * 5));
                            SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, ucLoopIndex, GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex));
                            SET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, ucLoopIndex, (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 3]));
                            SET_TCPM_PD_PARTNER_SRC_PEAK_CUR(ucPortIndex, ucLoopIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] & (_BIT5 | _BIT4)) >> 4));

                            // If Target Voltage Matches Partner's Voltage, Set the Macros of Capability Mismatch and Object Position.
                            if((GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_TARGET_VOL) && (GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex) == (GET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex) * 100)))
                            {
                                SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _FALSE);
                                SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, (EnumTypeCPdoNumber)(ucLoopIndex + 1));
                            }
                        }
                    }
                    else
                    {
                        // If ucLoopIndex >= GET_TCPM_PD_PARTNER_SRC_CAP_CNT(), Clear the Related Macros to 0x00.
                        SET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, ucLoopIndex, _PD_NONE_SETTING_PDO);
                        SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, ucLoopIndex, 0x00);
                        SET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, ucLoopIndex, 0x00);
                        SET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, ucLoopIndex, 0x00);
                        SET_TCPM_PD_PARTNER_SRC_PEAK_CUR(ucPortIndex, ucLoopIndex, 0x00);
                    }
                }

                // According to the corresponding Request Type, Set the Macros of Capability Mismatch and Object Position.
                if(GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_LOWEST_VOL)
                {
                    SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _FALSE);
                    SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, _TYPE_C_PDO_NUM_1);
                }
                else if(GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_HIGHEST_VOL)
                {
                    SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _FALSE);
                    SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, (EnumTypeCPdoNumber)(GET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex)));
                }
                else if((GET_TCPM_PD_REQ_TYPE(ucPortIndex) == _TYPE_C_REQ_TARGET_VOL) && (GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) != (GET_TCPM_PD_INIT_REQ_TARGET_VOL(ucPortIndex) * 100)))
                {
                    SET_TCPM_PD_REQ_CAP_MIS(ucPortIndex, _TRUE);
                    SET_TCPM_PD_REQ_OBJ_POS(ucPortIndex, _TYPE_C_PDO_NUM_1);
                }

                // If Request Type isn't Customized RDO, Need to be Set Operating and Max. Current.
                if(GET_TCPM_PD_REQ_TYPE(ucPortIndex) != _TYPE_C_REQ_CUSTOMIZED_RDO)
                {
                    SET_TCPM_PD_REQ_INFO_1(ucPortIndex, GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1));
                    SET_TCPM_PD_REQ_INFO_2(ucPortIndex, GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1));
                }

                // 2. Evaluate if Received Source Capability is Valid
                SET_TCPM_PD_PARTNER_SRC_CAP_CHECK_RESULT(ucPortIndex, ScalerTypeCTcpmPdCheckSrcCapValid_EXINT0(ucPortIndex));

                // 3. Update Flag and Transit State
                SET_TCPM_PD_RCV_SRC_CAP(ucPortIndex);
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else if((GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_REJECT) || (GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_NOT_SUPPORT))
            {
                // Port Partner Does Not Support DRP
                SET_TCPM_PD_PARTNER_DRP(ucPortIndex, _FALSE);

                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;

        case _PD_SUB_INT_WAIT_SNK_CAP:

            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_SNK_CAP)
            {
                // 1. Store Snk_Cap Info from Data Objects
                SET_TCPM_PD_PARTNER_DRP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 5);
                SET_TCPM_PD_PARTNER_HIGH_CAP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 4);
                SET_TCPM_PD_PARTNER_EXT_PWR(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 3);
                SET_TCPM_PD_PARTNER_USB_CAP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 2);
                SET_TCPM_PD_PARTNER_DRD(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 1);

                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    // [24:23] Fast Role Swap Default Require Current
                    SET_TCPM_PD_PARTNER_FRS_CUR(ucPortIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[0] & _BIT0) << 1) | ((g_pucTypeCTcpmPdDataObj_EXINT[1] & _BIT7) >> 7));
                }

                // Get Number Of Capabilities
                SET_TCPM_PD_PARTNER_SNK_CAP_CNT(ucPortIndex, GET_TCPM_PD_RCV_NOD_CNT(ucPortIndex));

                // Evaluate and Set Request Data Objects
                for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TCPM_PD_PARTNER_SNK_CAP_CNT(ucPortIndex); ucLoopIndex++)
                {
                    if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                    {
                        // Set APDO Type
                        SET_TCPM_PD_PARTNER_SNK_CAP_TYPE(ucPortIndex, ucLoopIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                    }
                    else
                    {
                        // Set PDO Type
                        SET_TCPM_PD_PARTNER_SNK_CAP_TYPE(ucPortIndex, ucLoopIndex, ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) >> 6));
                    }

                    if(GET_TCPM_PD_PARTNER_SNK_CAP_TYPE(ucPortIndex, ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                        SET_TCPM_PD_PARTNER_SNK_CAP_VOL_MAX(ucPortIndex, ucLoopIndex, (((((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4] & 0x01)) << 7) | (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] & 0xFE)) >> 1)) * 10));
                        SET_TCPM_PD_PARTNER_SNK_CAP_VOL_MIN(ucPortIndex, ucLoopIndex, (((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2]) * 10));
                        SET_TCPM_PD_PARTNER_SNK_CAP_CUR(ucPortIndex, ucLoopIndex, (((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 3] & 0x7F) * 5));
                    }
                    else
                    {
                        // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                        SET_TCPM_PD_PARTNER_SNK_CAP_VOL_MAX(ucPortIndex, ucLoopIndex, (((((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2] & 0xFC)) >> 2)) * 5));
                        SET_TCPM_PD_PARTNER_SNK_CAP_VOL_MIN(ucPortIndex, ucLoopIndex, GET_TCPM_PD_PARTNER_SNK_CAP_VOL_MAX(ucPortIndex, ucLoopIndex));
                        SET_TCPM_PD_PARTNER_SNK_CAP_CUR(ucPortIndex, ucLoopIndex, (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex * 4 + 3]));
                    }
                }

                SET_TCPM_PD_RCV_SNK_CAP(ucPortIndex);

                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else if((GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_REJECT) || (GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_NOT_SUPPORT))
            {
                // Port Partner Does Not Support DRP
                SET_TCPM_PD_PARTNER_DRP(ucPortIndex, _FALSE);

                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;

        case _PD_SUB_INT_WAIT_PRS_RESP:

            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_ACCEPT)
            {
                // "Accept" Message Has Been Sent Successfully
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_POWER_TRANSITION);

                if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
                {
                    // 1. Turn Off Power After 25-35ms
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _SRC_ADJUST_POWER_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER);
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_SRC_OFF_PSRDY);
                }
                else
                {
                    // 1. Turn Off Sink Power, Disable Detect Sink OVP/UVP
                    ScalerTypeCTcpmVbusCtrl_EXINT0(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

                    // 2. Disable TypeC Vbus Detach Detect Function
                    ScalerTypeCTcpmVbusDetCtrl_EXINT0(ucPortIndex, _DISABLE);

                    // 3. Disable ALERT.CC_STATUS to Avoid Unattach
                    ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_CC_STATUS, _DISABLE);

                    // PD Merged Test [TEST.PD.PROT.SNK.12]
                    ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _PS_SRC_OFF_TIMER, _SCALER_TIMER_EVENT_TCPM_TPC_ERROR_RECOVERY);
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_SRC_OFF);
                }

                // Receive Accept to PR_Swap, Set Flag For Retimer Usage
                SET_TCPM_PD_PRS_PROCESSING(ucPortIndex);
            }
            else if((GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_REJECT) || (GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_NOT_SUPPORT))
            {
                // Port Partner Reject PR Swap
                SET_TCPM_PD_PRS_REJECT(ucPortIndex);

                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_WAIT)
            {
                // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                SET_TCPM_PD_PRS_WAIT_FLAG(ucPortIndex);
                ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _WAIT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_PRS_WAIT);

                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;

        case _PD_SUB_INT_WAIT_SRC_OFF:

            // Cancel TimerEvent(_PS_SRC_OFF_TIMER)
            ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_TPC_ERROR_RECOVERY);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_PS_RDY)
            {
                // Wait > 5ms for Google Pixelbook Interop Issue (MM1AE-2956). Timeout : Switch Power Role to SRC and Turn on Vbus.
                ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 10, _SCALER_WD_TIMER_EVENT_TCPM_SNK_SWITCH_TO_SRC);
            }
            else
            {
                // Rcv Unexpected Message During Rp-Rd Switch
                SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
                CLR_TCPM_PD_PRS_PROCESSING(ucPortIndex);
            }

            break;

        case _PD_SUB_INT_WAIT_SRC_ON:

            // Cancel TimerEvent(PS_SRC_ON_TIMER);
            ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_TPC_ERROR_RECOVERY);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_PS_RDY)
            {
                // Set FW State to "_PD_SNK_START_UP" and Run PdStartUpProc
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_START_UP);

                ScalerTypeCTcpmPdStartUpProc_EXINT0(ucPortIndex);

                // Update Vbus Power Info to Support Sink OVP/UVP
                ScalerTypeCTcpmVbusCtrl_EXINT0(ucPortIndex, _ON, _PD_POWER_SNK, _PD_FIX_SUPPLY_PDO, 500, 0, _PD_PEAK_CUR_NONE);

                // Start PMIC Protection
                ScalerTypeCTcpmVbusProtectStart_EXINT0(ucPortIndex, _TYPE_C_POWER_SNK);
            }
            else
            {
                // Receive Unexpected Message in Power-Transition AMS
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
                CLR_TCPM_PD_PRS_PROCESSING(ucPortIndex);
            }

            break;

        case _PD_SUB_INT_WAIT_DRS_RESP:

            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_ACCEPT)
            {
                if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
                {
                    // Update FW Data Role to UFP
                    SET_TCPM_DATA_ROLE(ucPortIndex, _PD_DATA_UFP);

                    // PD 2.0 : Prevent Receiving Cable Message When Data Role is UFP During Explicit Contract
                    if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
                    {
                        // Enable PD Rcv Detect ([0x2F] : [5] HRST, [0] SOP)
                        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, (_TCPM_TCPCI_RCV_DET_SOP | _TCPM_TCPCI_RCV_DET_HRST));
                    }

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
                    if(GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _ON)
                    {
                        // Set PARTNER_ALT_SUPPORT FLAG for Sink in Ready to Wait For Port Partner Initiating Alt Mode Flow
                        SET_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex);

                        // Sink Start PR_SWAP to Provide Power, if Not Enter ALt Mode in 2 Sec After Power Contract, timeout: Clear PARTNER_ALT_SUPPORT Macro
                        ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _PARTNER_ALT_SUPPORT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_PARTNER_ALT_SUPPORT);
                    }
#endif
                }
                else
                {
                    // Update FW Data Role to DFP
                    SET_TCPM_DATA_ROLE(ucPortIndex, _PD_DATA_DFP);

                    // PD 2.0 : Only DFP && Vconn Source Can Communicate With Cable During Explicit Contract
                    if((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) && (GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC))
                    {
                        // Enable PD Rcv Detect ([0x2F] : [5] HRST, [2] SOP", [1] SOP', [0] SOP)
                        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, (_TCPM_TCPCI_RCV_DET_SOP | _TCPM_TCPCI_RCV_DET_SOP_P | _TCPM_TCPCI_RCV_DET_SOP_PP | _TCPM_TCPCI_RCV_DET_HRST));
                    }
                }

                // MSG_HEADER_INFO [0x2E] : Update FW/HW Data Role to DFP/UFP
                // Set Message Header for GoodCRC Reply
                ScalerTypeCTcpmPdUpdateGoodCRCInfo_EXINT0(ucPortIndex);

                // DR Swap AMS Finished
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else if((GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_REJECT) || (GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_NOT_SUPPORT))
            {
                // Port Partner Reject DR Swap
                SET_TCPM_PD_DRS_REJECT(ucPortIndex);

                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                // [Interop] Data Role Correction : Some Sources Have Wrong Data Role and Do Not Accept DR_SWAP
                // For Data Role Swap Reject & Data Role Error => Swith Our Data Role to Prevent From Both Side Start Alt Mode
                if(((GET_TCPM_RX_BUF_MSG_HEADER_L() & (_BIT5)) >> 5) == (GET_TCPM_DATA_ROLE(ucPortIndex)))
                {
                    if((GET_TCPM_RX_BUF_MSG_HEADER_L() & (_BIT5)) == _BIT5)
                    {
                        // Update FW Data Role to UFP
                        SET_TCPM_DATA_ROLE(ucPortIndex, _PD_DATA_UFP);
                    }
                    else
                    {
                        // Update FW Data Role to DFP
                        SET_TCPM_DATA_ROLE(ucPortIndex, _PD_DATA_DFP);
                    }

                    // MSG_HEADER_INFO [0x2E] : Update FW/HW Data Role to DFP/UFP
                    // Set Message Header for GoodCRC Reply
                    ScalerTypeCTcpmPdUpdateGoodCRCInfo_EXINT0(ucPortIndex);
                }
            }
            else if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_WAIT)
            {
                // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                SET_TCPM_PD_DRS_WAIT_FLAG(ucPortIndex);
                ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _WAIT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_DRS_WAIT);

                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;

        case _PD_SUB_INT_WAIT_VCS_RESP:

            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_ACCEPT)
            {
                // "Accept" Message Has Been Sent Successfully
                if(GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC)
                {
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VCONN_ON);
                    ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _WAIT_VCONN_ON_TIMER, _SCALER_TIMER_EVENT_TCPM_SEND_HARD_RST);
                }
                else
                {
                    // Turn On Vconn Power
                    ScalerTypeCTcpmVconnCtrl_EXINT0(ucPortIndex, _ON);

                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_WDINT_SEND_VCONN_ON_PSRDY);
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 5, _SCALER_WD_TIMER_EVENT_TCPM_SEND_VCONN_ON_PSRDY);
                }
            }
            else if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_REJECT)
            {
                // Port Partner Reject Vconn Swap
                SET_TCPM_PD_VCS_REJECT(ucPortIndex);

                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_NOT_SUPPORT)
            {
                if(GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC)
                {
                    // Port Partner Reject Vconn Swap
                    SET_TCPM_PD_VCS_REJECT(ucPortIndex);
                }
                else
                {
                    // Turn On Vconn Power
                    ScalerTypeCTcpmVconnCtrl_EXINT0(ucPortIndex, _ON);

                    // Set Vconn Role to Vconn SRC
                    SET_TCPM_VCONN_ROLE(ucPortIndex, _PD_VCONN_SRC);

                    // PD 2.0 : Only DFP && Vconn Source Can Communicate With Cable During Explicit Contract
                    // PD 3.0 : Only Vconn Source Can Communicate With Cable
                    if((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0) || ((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) && (GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)))
                    {
                        // Enable PD Rcv Detect ([0x2F] : [5] HRST, [2] SOP", [1] SOP', [0] SOP)
                        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, (_TCPM_TCPCI_RCV_DET_SOP | _TCPM_TCPCI_RCV_DET_SOP_P | _TCPM_TCPCI_RCV_DET_SOP_PP | _TCPM_TCPCI_RCV_DET_HRST));
                    }
                }
            }
            else if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_WAIT)
            {
                // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                SET_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex);
                ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _WAIT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_VCS_WAIT);

                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;

        case _PD_SUB_INT_WAIT_VCONN_ON:

            // Cancel TimerEvent(WAIT_VCONN_ON_TIMER)
            ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SEND_HARD_RST);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_PS_RDY)
            {
                // Turn Off Vconn
                ScalerTypeCTcpmVconnCtrl_EXINT0(ucPortIndex, _OFF);

                // Set Vconn Role to Vconn SNK
                SET_TCPM_VCONN_ROLE(ucPortIndex, _PD_VCONN_NOT_SRC);

                // Enable PD Rcv Detect ([0x2F] : [5] HRST, [0] SOP)
                ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, (_TCPM_TCPCI_RCV_DET_SOP | _TCPM_TCPCI_RCV_DET_HRST));

                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Reset Discover ID Retry Fail Counter After Vconn_Swap
                CLR_TCPM_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT(ucPortIndex);

                // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                SET_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex);
                ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _WAIT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_VCS_WAIT);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        // After Rcving Chunk_Test
        case _PD_SUB_INT_WAIT_CHK_TEST_RESP:

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_CHUNK_TEST)
            {
                // Check If This Ext Msg is Chunked : Ext Message Header [15]
                if((GET_TCPM_PD_RCV_EXT_CHUNKED(ucPortIndex) == _TRUE) && (GET_TCPM_PD_RCV_EXT_CHUNK_REQ(ucPortIndex) == _FALSE))
                {
                    // If Received Chunk Response Data < Total Message Data Size, Sent Chunk Request
                    if(((GET_TCPM_PD_RCV_EXT_CHUNK_NUM(ucPortIndex) + 1) * 26) < GET_TCPM_PD_RCV_EXT_DATA_SIZE(ucPortIndex))
                    {
                        // Set Chunk Message As an Chunk Request
                        SET_TCPM_PD_RCV_EXT_CHUNK_REQ(ucPortIndex, _TRUE);

                        SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

                        // Send "Chunk Test" REQUEST
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_CHK_TEST_REQ);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_CHUNK_TEST, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                        SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                    }
                }
                else
                {
                    // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;

        case _PD_SUB_INT_WAIT_STATUS:

            ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);

            if(GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_STATUS)
            {
                SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_STATUS_EVENT);
                SET_TCPM_PD_PARTNER_NEW_POWER_STATE(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[8] & (_BIT2 | _BIT1 | _BIT0));
                SET_TCPM_PD_PARTNER_NEW_POWER_INDICATOR(ucPortIndex, (g_pucTypeCTcpmPdDataObj_EXINT[8] >> 3) & (_BIT2 | _BIT1 | _BIT0));

                // Receive Status Message, Temporary do nothing, Only Protocol For CTS
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);
            }

            break;
#endif

        default:

            // Receive Unexpected Message in Unexpected FW State
            ScalerTypeCTcpmPdPrlErrHandle_EXINT0(ucPortIndex);

            break;
    }
}

//--------------------------------------------------
// Description  : Process When Receive Soft Reset Message
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdRcvSoftRstProc_EXINT0(BYTE ucPortIndex)
{
    if(GET_TCPM_PD_FW_STATE(ucPortIndex) != _PD_HARDRESET)
    {
        if((GET_TCPM_PD_AMS_STATUS(ucPortIndex) == _PD_AMS_POWER_TRANSITION) || (GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_INT_WAIT_SOFTRESET_RESP))
        {   // 1. If Rcv. Soft Reset During Power Transition or Already in Soft Reset => HARD RESET
            ScalerTypeCTcpmPdSendHardRst_EXINT0(ucPortIndex);
        }
        else if((GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_INT_WAIT_DRS_RESP) || (GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_INT_SEND_ACCEPT_DRS))
        {   // 2. If Rcv. Soft Reset During DR_SWAP => Type-C Error Recovery (8.3.3.4.1)
            SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);
        }
        else
        {
            // 3. Else Do Soft Reset, Response Accept (Include Rcv. Soft Reset Again Before Reply Accept)
            // Reset Message ID
            CLR_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex);
            CLR_TCPM_PD_RX_MSG_ID_SOP(ucPortIndex);

            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_INT_SEND_SOFTRESET_RESP);
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_HARD_RESET);

            // Send "Accept"
            ScalerTypeCTcpmPdSendMsg_EXINT0(ucPortIndex, _PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
        }
    }
}

//--------------------------------------------------
// Description  : Process Rcv. SOP' /SOP" Msg. in Interrupt
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntRcvCableMsgProc_EXINT0(BYTE ucPortIndex)
{
    // Cancel TimerEvent(SENDER_RESP_TIMER)
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

    if(GET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex) == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)
    {
        // Update Cable Spec Version According to Our Spec Version and Cable Spec Version
        if((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ||
           ((GET_TCPM_RX_BUF_MSG_HEADER_L() & (_BIT7 | _BIT6)) == _BIT6))
        {
            SET_TCPM_PD_CBL_SPEC_VER(ucPortIndex, _PD_VERSION_2_0);
        }
        else
        {
            SET_TCPM_PD_CBL_SPEC_VER(ucPortIndex, _PD_VERSION_3_0);
        }
    }

    switch(GET_TCPM_PD_FW_STATE(ucPortIndex))
    {
        case _PD_INT_WAIT_CBL_DISCOVER_ID_RESP:

            if((GET_TCPM_PD_RCV_MSG(ucPortIndex) == _PD_CMD_VDM) && (GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_ID_ACK))
            {
                // Record Cable Info Of Discover ID Ack
                ScalerTypeCTcpmPdSaveCableDiscoverIdAckInfo_EXINT0(ucPortIndex);
                SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED);
            }

            // Send SRC_CAP After Discover ID NAK/BUSY or Unexpected Msg Received Before Power Contract
            // Send Discover ID to Cable After Power Contract If Discover ID ACK Not Received
            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_WDINT_SEND_CAP);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

            // Active WD Timer Event To Check Vbus, Then Start PMIC Protection and Send SRC_CAP if VbusSafe5V
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 20, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);

            break;

        case _PD_INT_WAIT_CBL_SOFT_RESET_RESP:

            if(GET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex) == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)
            {
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_WDINT_SEND_CBL_DISCOVER_ID);
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Active WD Timer Event To Wait To Send Discover_ID_REQ, Timeout : Send Discover_ID Msg.
                ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 10, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);
            }
            else
            {
                // PD Transit to On-going PD Flow
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_WDINT_SEND_CAP);
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Active WD Timer Event To Wait To Send SRC_CAP, Timeout : Send SRC_CAP.
                ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 20, _SCALER_WD_TIMER_EVENT_TCPM_SEND_SRC_CAP);
            }

            break;

        case _PD_SRC_READY:
        case _PD_SNK_READY:

            switch(GET_TCPM_PD_SUB_STATE(ucPortIndex))
            {
                case _PD_SUB_CABLE_PROC:

                    switch(GET_TCPM_PD_CBL_STATE(ucPortIndex))
                    {
                        case _PD_CBL_INT_WAIT_SOFT_RST_RESP:

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_STATE_NONE);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_CBL_INT_WAIT_DISCOVER_ID_RESP:

                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_ID_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                // Record Cable Info Of Discover ID Ack
                                ScalerTypeCTcpmPdSaveCableDiscoverIdAckInfo_EXINT0(ucPortIndex);
                                SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED);

                                // Re-send SRC Cap since new cable max current get, new power contract is needed, set system event
                                if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
                                {
                                    if(ScalerTypeCTcpmPdCheckRebuildPowerContract_EXINT0(ucPortIndex) == _PD_REBUILD_REQUIRED)
                                    {
                                        SET_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_SEND_SRC_CAP);
                                    }
                                }
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_ID_NAK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);
                                SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_NON_PD_CAPABLE);
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_ID_BUSY) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID))
                            {
                                ADD_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                if(GET_TCPM_PD_VDM_BUSY_CNT(ucPortIndex) >= _MAX_VDM_BUSY_CNT)
                                {
                                    CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);
                                    SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_NON_PD_CAPABLE);
                                }
                                else
                                {
                                    SET_TCPM_PD_VDM_BUSY_FLAG(ucPortIndex);

                                    // Clear VDM Busy Flag after 50ms.
                                    ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _VDM_BUSY_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_VDM_BUSY_FLAG);
                                }
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
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

                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_ID_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                // Record Cable Info Of Discover ID Ack
                                ScalerTypeCTcpmPdSaveCableDiscoverIdAckInfo_EXINT0(ucPortIndex);
                                SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED);

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable(When Ack Vdo Received For Discover Id(SOP'/SOP''))
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableId_EXINT0(ucPortIndex));

                                // Re-send SRC Cap since new cable max current get, new power contract is needed, set system event
                                if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
                                {
                                    if(ScalerTypeCTcpmPdCheckRebuildPowerContract_EXINT0(ucPortIndex) == _PD_REBUILD_REQUIRED)
                                    {
                                        SET_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_SEND_SRC_CAP);
                                    }
                                }
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_ID_NAK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);
                                SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_NON_PD_CAPABLE);

                                // If No VDO Received, Set Passive Cable & HBR3 According to DPAM2.1
                                SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_PASSIVE);
                                SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_HBR3);

                                // Stop Enter DP Alt Mode Flow Just for Cable
                                CLR_TCPM_PD_CBL_ENTER_DP_MODE_SUPPORT(ucPortIndex);
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_ID_BUSY) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID))
                            {
                                ADD_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                if(GET_TCPM_PD_VDM_BUSY_CNT(ucPortIndex) >= _MAX_VDM_BUSY_CNT)
                                {
                                    CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);
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
                                    SET_TCPM_PD_VDM_BUSY_FLAG(ucPortIndex);

                                    // Clear VDM Busy Flag after 50ms.
                                    ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _VDM_BUSY_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_VDM_BUSY_FLAG);
                                }
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP_SOP_P:

                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_SVID_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                // Search Through All SVIDs to All Svid The Cable Supports
                                ScalerTypeCTcpmPdSearchCableSvid_EXINT0(ucPortIndex);

                                if(GET_TCPM_PD_CBL_SVID_SEARCH_FINISH(ucPortIndex) == _FALSE)
                                {
                                    // If Search Finish = FALSE, Send Cable Discover SVID Again to Get More SVID
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P);
                                }
                                else
                                {
                                    if(GET_TCPM_PD_CBL_DP_SVID_SUPPORT(ucPortIndex) == _TRUE)
                                    {
                                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P);
                                    }
                                    else if(GET_TCPM_PD_CBL_TBT3_SVID_SUPPORT(ucPortIndex) == _TRUE)
                                    {
                                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P);
                                    }
                                    else
                                    {
                                        // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When Cable Don't Support DP or TBT3 SVID
                                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(ucPortIndex));
                                    }
                                }
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_SVID_NAK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When NAK of Discover Svid(SOP' / SOP'') Received
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(ucPortIndex));
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_SVID_BUSY) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID))
                            {
                                ADD_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                if(GET_TCPM_PD_VDM_BUSY_CNT(ucPortIndex) >= _MAX_VDM_BUSY_CNT)
                                {
                                    CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                    // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When BUSY of Discover Svid(SOP' / SOP'') Received
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(ucPortIndex));
                                }
                                else
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P);
                                    SET_TCPM_PD_VDM_BUSY_FLAG(ucPortIndex);

                                    // Clear VDM Busy Flag after 50ms.
                                    ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _VDM_BUSY_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_VDM_BUSY_FLAG);
                                }
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_DISCOVER_MODE_RESP_SOP_P:

                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_MODE_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                // Record Cable Info Of Discover DP Mode Ack
                                ScalerTypeCTcpmPdSaveCableDpModeInfo_EXINT0(ucPortIndex);
                                SET_TCPM_PD_CBL_DP_MODE_INFO_RECEIVED(ucPortIndex);

                                if(GET_TCPM_PD_CBL_TBT3_SVID_SUPPORT(ucPortIndex) == _TRUE)
                                {
                                    // If Cable Also Support TBT3 Mode, Discover Cable TBT3 Mode Before Enter Mode
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P);
                                }
                                else
                                {
                                    // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Enter Mode First
                                    if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                                    {
                                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE_SOP_P);
                                    }
                                    else
                                    {
                                        SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
                                    }
                                }
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_MODE_NAK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When NAK of DP Discover Mode(SOP' / SOP'') Received
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(ucPortIndex));
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_MODE_BUSY) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                ADD_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                if(GET_TCPM_PD_VDM_BUSY_CNT(ucPortIndex) >= _MAX_VDM_BUSY_CNT)
                                {
                                    CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                    // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When BUSY of DP Discover Mode(SOP' / SOP'') Received
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(ucPortIndex));
                                }
                                else
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P);
                                    SET_TCPM_PD_VDM_BUSY_FLAG(ucPortIndex);

                                    // Clear VDM Busy Flag after 50ms.
                                    ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _VDM_BUSY_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_VDM_BUSY_FLAG);
                                }
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_TBT3_DISCOVER_MODE_RESP_SOP_P:

                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_MODE_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _TBT3_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                // Record Cable Info Of TBT3 Discover Mode Ack
                                ScalerTypeCTcpmPdSaveCableTbt3ModeInfo_EXINT0(ucPortIndex);

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When ACK of TBT3 Discover Mode(SOP' / SOP'') Received
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableTbt3Mode_EXINT0(ucPortIndex));
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_MODE_NAK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _TBT3_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When NAK of TBT3 Discover Mode(SOP' / SOP'') Received
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(ucPortIndex));
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_DISCOVER_MODE_BUSY) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _TBT3_SID))
                            {
                                ADD_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                if(GET_TCPM_PD_VDM_BUSY_CNT(ucPortIndex) >= _MAX_VDM_BUSY_CNT)
                                {
                                    CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                    // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When BUSY of TBT3 Discover Mode(SOP' / SOP'') Received
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(ucPortIndex));
                                }
                                else
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P);
                                    SET_TCPM_PD_VDM_BUSY_FLAG(ucPortIndex);

                                    // Clear VDM Busy Flag after 50ms.
                                    ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _VDM_BUSY_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_VDM_BUSY_FLAG);
                                }
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_P:

                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_ENTER_MODE_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                if(GET_TCPM_PD_CBL_SOP_PP_SUPPORT(ucPortIndex) == _TRUE)
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP);
                                }
                                else
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
                                }
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_ENTER_MODE_NAK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_PP:

                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_ENTER_MODE_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_ENTER_MODE_NAK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_P:

                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_51) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                if(GET_TCPM_PD_CBL_SOP_PP_SUPPORT(ucPortIndex) == _TRUE)
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP);
                                }
                                else
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                                }
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_91) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_PP:

                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_51) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_91) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_P:

                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_EXIT_MODE_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                if(GET_TCPM_PD_CBL_SOP_PP_SUPPORT(ucPortIndex) == _TRUE)
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP);
                                }
                                else
                                {
                                    SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE);
                                }
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_EXIT_MODE_NAK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_PP:

                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);

                            if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_EXIT_MODE_ACK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                            else if((GET_TCPM_PD_RCV_VDM_CMD(ucPortIndex) == _PD_VDM_CMD_EXIT_MODE_NAK) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
                            {
                                CLR_TCPM_PD_VDM_BUSY_CNT(ucPortIndex);

                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                            else
                            {
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                            break;

                        default:

                            break;
                    }

                    break;
#endif  // End of #if((_EMB_TCPM_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TCPM_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))

                default:

                    break;
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For Handling Protocol Error
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdPrlErrHandle_EXINT0(BYTE ucPortIndex)
{
    if(GET_TCPM_PD_FW_STATE(ucPortIndex) == _PD_INT_WAIT_SOFTRESET_RESP)
    {
        // If  : Rcv Unexpected Msg. During Soft Reset, Do "HARD RESET"
        ScalerTypeCTcpmPdSendHardRst_EXINT0(ucPortIndex);
    }
    else
    {
        switch(GET_TCPM_PD_AMS_STATUS(ucPortIndex))
        {
            case _PD_AMS_NONE:
            case _PD_AMS_INTERRUPTIBLE:
            case _PD_AMS_NON_INTERRUPTIBLE:

                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_INT_SEND_SOFTRESET);
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
                SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_HARD_RESET);

                ScalerTypeCTcpmPdSendSoftRst_EXINT0(ucPortIndex, _PD_SOP_PKT);

                break;

            case _PD_AMS_POWER_TRANSITION:

                ScalerTypeCTcpmPdSendHardRst_EXINT0(ucPortIndex);

                break;

            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Process When Tx Transmission Success in Interrupt
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntTxSuccessProc_EXINT0(BYTE ucPortIndex)
{
    WORD usSrcAdjustPowerTime = 0;

    switch(GET_TCPM_PD_FW_STATE(ucPortIndex))
    {
        case _PD_INT_SEND_CBL_DISCOVER_ID:
        case _PD_INT_SEND_CBL_SOFT_RESET:

            ScalerTypeCTcpmPdIntTxCableReqSuccessProc_EXINT0(ucPortIndex);

            break;

        case _PD_SRC_INT_SEND_CAP:

            // Reset Source Cap Counter and Hard Reset Counter
            CLR_TCPM_PD_SRC_CAP_CNT(ucPortIndex);
            CLR_TCPM_PD_HARD_RST_CNT(ucPortIndex);
            CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_SEND_SRC_CAP);

            // State Transition, AMS & Timer Setting
            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_INT_WAIT_REQ);
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Hard Reset
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT);

            break;

        case _PD_SRC_INT_SEND_ACCEPT_REQ:

            // State Transition
            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_WDINT_TRANSIT_POWER);
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_POWER_TRANSITION);

            if(GET_TCPM_PD_REQ_PPS_VOL_SMALL_STEP(ucPortIndex) != _TRUE)
            {
                usSrcAdjustPowerTime = _SRC_ADJUST_POWER_TIMER;
            }
            else
            {
                usSrcAdjustPowerTime = 5;
            }

            // Set WD Timer to Wait 25-35ms, then Turn On Vbus
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, usSrcAdjustPowerTime, _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER);

            break;

        case _PD_SRC_INT_SEND_REJECT_REQ:
        case _PD_SRC_INT_SEND_WAIT_REQ:

            if(GET_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex) == _TRUE)
            {
                // If Reject Request & Power Contract Exist,
                if(ScalerTypeCTcpmPdCheckPowerContractValid_EXINT0(ucPortIndex) == _TRUE)
                {
                    // Set AMS = None
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                }
                else
                {
                    // If Power Contract is no more Valid, Do Hard Reset
                    ScalerTypeCTcpmPdSendHardRst_EXINT0(ucPortIndex);
                }
            }
            else
            {
                // If Reject Request & No Power Contract, Wait 120ms and Re-Send Src_Cap
                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_WDINT_SEND_CAP);
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Active WD Timer Event To Wait To Send SRC_CAP, Timeout : Send SRC_CAP.
                ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 120, _SCALER_WD_TIMER_EVENT_TCPM_SEND_SRC_CAP);
            }

            break;

        case _PD_SRC_INT_SEND_PSRDY:

            // Set AMS = None
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

            // Back to Ready State
            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

            // Set Power Contract = TRUE
            SET_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex);

#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
            // Clear OCP/OVP/UVP/Vconn OCP Event and Alert Macro due to New Power Contract Established
            CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);
            CLR_TCPM_PD_ALERT_SENT(ucPortIndex);
#endif

            break;

        case _PD_SNK_INT_SEND_REQUEST:

            CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_SEND_REQUEST);

            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Hard Reset
            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_INT_WAIT_REQ_RESP);
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT);

            break;

        case _PD_INT_SEND_SOFTRESET:

            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Hard Reset
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT);

            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_INT_WAIT_SOFTRESET_RESP);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);

            break;

        case _PD_INT_SEND_SOFTRESET_RESP:

            if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
            {
                // Clear Explicit Power Contract and Flags
                CLR_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex);

                SET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex, 0);
                CLR_TCPM_PD_SRC_CAP_CNT(ucPortIndex);

                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_WDINT_SEND_CAP);
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Active WD Timer Event To Send 1st SRC_CAP, Timeout : Send SRC_CAP.
                ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 20, _SCALER_WD_TIMER_EVENT_TCPM_SEND_SRC_CAP);
            }
            else
            {
                // Clear Explicit Power Contract and Flags
                CLR_TCPM_PD_EXPLICIT_CONTRACT(ucPortIndex);

                // Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
                ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, ScalerTypeCTcpmWDTimeCtrl_EXINT0(ucPortIndex, _SINK_WAIT_CAP_TIMER), _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST);

                SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_INT_WAIT_SRC_CAP);
                SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);
            }

            break;

        case _PD_SRC_READY:
        case _PD_SNK_READY:

            switch(GET_TCPM_PD_SUB_STATE(ucPortIndex))
            {
                case _PD_SUB_INT_SEND_SRC_CAP:
                case _PD_SUB_SEND_SRC_CAP:

                    CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_SEND_SRC_CAP);
                    if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
                    {
                        CLR_TCPM_PD_SRC_CAP_CNT(ucPortIndex);
                        SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_INT_WAIT_REQ);
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
                        SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);
                        ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT);
                    }
                    else
                    {
                        SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                        // Back to Ready State
                        ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                    }

                    break;

                case _PD_SUB_SEND_GET_SRC_CAP:

                    SET_TCPM_PD_GET_SRC_CAP_SENT(ucPortIndex);
                    if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
                    {
                        SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_SRC_CAP);

                        // Turn On Sender Response Timer 24~30 ms, Wait "Src_Cap" @ INT
                        ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);
                    }
                    else
                    {   // Sink Shoud Transit to Ready State, And Should Rcv. Src_Cap Later
                        SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);
                        ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                    }

                    break;

                case _PD_SUB_SEND_GET_SNK_CAP:

                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_SNK_CAP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "Snk_Cap" @ INT
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);

                    break;

                case _PD_SUB_CABLE_PROC:
                case _PD_SUB_SEND_CBL_DP_VDM_REQ:

                    ScalerTypeCTcpmPdIntTxCableReqSuccessProc_EXINT0(ucPortIndex);

                    break;

                case _PD_SUB_SEND_PR_SWAP:

                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_PRS_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "Snk_Cap" @ INT
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);

                    break;

                case _PD_SUB_INT_SEND_ACCEPT_PRS:

                    // Port Partner Initiates PR_Swap, which Means It Has the Ability to Change the Power Role, so CLR_TCPM_PD_PRS_REJECT().
                    CLR_TCPM_PD_PRS_REJECT(ucPortIndex);

                    // "Accept" Message Has Been Sent Successfully
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_POWER_TRANSITION);

                    if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
                    {
                        // 1. Turn Off Power After 25-35ms
                        ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _SRC_ADJUST_POWER_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER);
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SEND_SRC_OFF_PSRDY);
                    }
                    else
                    {
                        // 1. Turn Off Sink Power, Disable Detect Sink OVP/UVP
                        ScalerTypeCTcpmVbusCtrl_EXINT0(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

                        // 2. Disable TypeC Vbus Detach Detect Function
                        ScalerTypeCTcpmVbusDetCtrl_EXINT0(ucPortIndex, _DISABLE);

                        // 3. Disable ALERT.CC_STATUS to Avoid Unattach
                        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)_TCPM_TCPCI_ALERT_CC_STATUS, _DISABLE);

                        // PD Merged Test [TEST.PD.PROT.SNK.12]
                        ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _PS_SRC_OFF_TIMER, _SCALER_TIMER_EVENT_TCPM_TPC_ERROR_RECOVERY);
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_SRC_OFF);
                    }

                    // Receive Accept to PR_Swap, Set Flag For Retimer Usage
                    SET_TCPM_PD_PRS_PROCESSING(ucPortIndex);

                    break;

                case _PD_SUB_SEND_SRC_OFF_PSRDY:

                    // SRC OFF "PS_RDY" Has Been Sent, Active Timer Event to Wait for SRC ON "PS_RDY"
                    ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _PS_SRC_ON_TIMER, _SCALER_TIMER_EVENT_TCPM_TPC_ERROR_RECOVERY);
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_SRC_ON);

                    break;

                case _PD_SUB_WDINT_SEND_SRC_ON_PSRDY:

                    // Transit to _PE_SRC_START_UP, and Send Soft Reset to Cable
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);
                    SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_START_UP);

                    ScalerTypeCTcpmPdStartUpProc_EXINT0(ucPortIndex);

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                    {
                        if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
                        {
                            CLR_TCPM_PD_PARTNER_VDM_NO_RESP_CNT(ucPortIndex);
                            CLR_TCPM_PD_CBL_VDM_NO_RESP_CNT(ucPortIndex);
                            CLR_TCPM_PD_GET_SRC_CAP_SENT(ucPortIndex);
                        }
                        else
                        {
                            CLR_TCPM_PD_VCS_REJECT(ucPortIndex);
                            CLR_TCPM_PD_DRS_REJECT(ucPortIndex);
                            CLR_TCPM_PD_PRS_REJECT(ucPortIndex);

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
                            if(GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex))
                            {
                                // Set PARTNER_ALT_SUPPORT FLAG to Wait For Port Partner Initiating Alt Mode Flow
                                SET_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex);

                                // After PR_SWAP, if Not Enter ALt Mode in 2 Sec After Power Contract, timeout: Clear PARTNER_ALT_SUPPORT Macro
                                ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _PARTNER_ALT_SUPPORT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_PARTNER_ALT_SUPPORT);
                            }
#endif
                        }
                    }
#endif

                    break;

                case _PD_SUB_SEND_DR_SWAP:

                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_DRS_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "Snk_Cap" @ INT
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);

                    break;

                case _PD_SUB_INT_SEND_ACCEPT_DRS:

                    // Port Partner Initiates DR_Swap, which Means It Has the Ability to Change the Data Role, so CLR_TCPM_PD_DRS_REJECT().
                    CLR_TCPM_PD_DRS_REJECT(ucPortIndex);

                    if(GET_TCPM_DATA_ROLE(ucPortIndex) == _PD_DATA_DFP)
                    {
                        // Update FW Data Role to UFP
                        SET_TCPM_DATA_ROLE(ucPortIndex, _PD_DATA_UFP);

                        // PD 2.0 : Prevent Receiving Cable Message When Data Role is UFP During Explicit Contract
                        if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0)
                        {
                            // Enable PD Rcv Detect ([0x2F] : [5] HRST, [0] SOP)
                            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, (_TCPM_TCPCI_RCV_DET_SOP | _TCPM_TCPCI_RCV_DET_HRST));
                        }

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
                        if(GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _ON)
                        {
                            // Set PARTNER_ALT_SUPPORT FLAG for Sink in Ready to Wait For Port Partner Initiating Alt Mode Flow
                            SET_TCPM_PD_PARTNER_ALT_SUPPORT(ucPortIndex);

                            // Sink Start PR_SWAP to Provide Power, if Not Enter ALt Mode in 2 Sec After Power Contract, timeout: Clear PARTNER_ALT_SUPPORT Macro
                            ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _PARTNER_ALT_SUPPORT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_PARTNER_ALT_SUPPORT);
                        }
#endif
                    }
                    else
                    {
                        // Update FW Data Role to DFP
                        SET_TCPM_DATA_ROLE(ucPortIndex, _PD_DATA_DFP);

                        // PD 2.0 : Only DFP && Vconn Source Can Communicate With Cable During Explicit Contract
                        if((GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) && (GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC))
                        {
                            // Enable PD Rcv Detect ([0x2F] : [5] HRST, [2] SOP", [1] SOP', [0] SOP)
                            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_RCV_DETECT, (_TCPM_TCPCI_RCV_DET_SOP | _TCPM_TCPCI_RCV_DET_SOP_P | _TCPM_TCPCI_RCV_DET_SOP_PP | _TCPM_TCPCI_RCV_DET_HRST));
                        }
                    }

                    // MSG_HEADER_INFO [0x2E] : Update FW/HW Data Role to DFP/UFP
                    // Set Message Header for GoodCRC Reply
                    ScalerTypeCTcpmPdUpdateGoodCRCInfo_EXINT0(ucPortIndex);

                    // DR Swap AMS Finished
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                    break;

                case _PD_SUB_SEND_VCONN_SWAP:

                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VCS_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "Snk_Cap" @ INT
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);

                    break;

                case _PD_SUB_INT_SEND_ACCEPT_VCS:

                    // Port Partner Initiates Vconn_Swap, which Means It Has the Ability to Change the Vconn Role, so CLR_TCPM_PD_VCS_REJECT().
                    CLR_TCPM_PD_VCS_REJECT(ucPortIndex);

                    // "Accept" Message Has Been Sent Successfully
                    if(GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC)
                    {
                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VCONN_ON);
                        ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _WAIT_VCONN_ON_TIMER, _SCALER_TIMER_EVENT_TCPM_SEND_HARD_RST);
                    }
                    else
                    {
                        // Turn On Vconn Power
                        ScalerTypeCTcpmVconnCtrl_EXINT0(ucPortIndex, _ON);

                        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_WDINT_SEND_VCONN_ON_PSRDY);
                        ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 5, _SCALER_WD_TIMER_EVENT_TCPM_SEND_VCONN_ON_PSRDY);
                    }

                    break;

                case _PD_SUB_WDINT_SEND_VCONN_ON_PSRDY:

                    // Vconn Swap AMS Finished
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                    // Do Soft Reset to Cable After Vconn_Swap Success & We Are Vconn Src
                    SET_TCPM_PD_CBL_SOFT_RESET_REQUIRED(ucPortIndex);

                    // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                    SET_TCPM_PD_VCS_WAIT_FLAG(ucPortIndex);
                    ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _WAIT_TIMER, _SCALER_TIMER_EVENT_TCPM_CLR_VCS_WAIT);

                    break;

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
                case _PD_SUB_SEND_DP_VDM_REQ:

                    ScalerTypeCTcpmPdIntTxDpVdmReqSuccessProc_EXINT0(ucPortIndex);

                    break;
#endif

                case _PD_SUB_INT_SEND_VDM_RESP:

                    ScalerTypeCTcpmPdIntTxVdmRespSuccessProc_EXINT0(ucPortIndex);

                    break;
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
                case _PD_SUB_SEND_GET_STATUS:

                    CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_SEND_GET_STATUS_MSG);
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NON_INTERRUPTIBLE);
                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_STATUS);

                    // Turn On Sender Response Timer 24~30 ms, Wait "ACCEPT / REJECT / WAIT" @ INT
                    ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);

                    break;

                case _PD_SUB_SEND_ALERT:

                    SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_ALERT_EVENT_SUCCESS);
                    CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_ALERT_EVENT);
                    CLR_TCPM_PD_TYPE_OF_ALERT(ucPortIndex, _TYPE_C_TYPE_OF_ALERT_ALL);
                    SET_TCPM_PD_EXT_ALERT_EVENT(ucPortIndex, _TYPE_C_EXT_ALERT_EVENT_NONE);

                    // Set Macro to Avoid Sending Alert Msg. Repeatedly in ReadyProc()
                    SET_TCPM_PD_ALERT_SENT(ucPortIndex);

                    // Set AMS = None
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                    break;

                case _PD_SUB_INT_SEND_CHK_TEST_REQ:

                    SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_CHK_TEST_RESP);

                    break;
#endif

                case _PD_SUB_BIST_MODE:     // TCPC will Generate Tx_SUCCESS after Exit BIST Carrier Mode 2
                case _PD_SUB_INT_SEND_SNK_CAP:
                case _PD_SUB_INT_SEND_REJECT:
                case _PD_SUB_INT_SEND_WAIT:
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
                case _PD_SUB_INT_SEND_NOT_SUPPORT:
                case _PD_SUB_INT_SEND_SRC_CAP_EXT:
                case _PD_SUB_INT_SEND_SNK_CAP_EXT:
                case _PD_SUB_INT_SEND_STATUS:
                case _PD_SUB_INT_SEND_MFC_INFO:
                case _PD_SUB_INT_SEND_PPS_STATUS:
                case _PD_SUB_INT_SEND_REVISION:
#endif

                    // Set AMS = None
                    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                    break;

                default:

                    break;
            } // End of switch(GET_TCPM_PD_SUB_STATE())

        default:

            break;
    } // End of switch(GET_TCPM_PD_FW_STATE())
}

//--------------------------------------------------
// Description  : Process When Tx Transmission Retry Fail in Interrupt
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntTxFailProc_EXINT0(BYTE ucPortIndex)
{
    switch(GET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex))
    {
        case _PD_TX_RETRY_FAIL_BY_STATE:

            switch(GET_TCPM_PD_FW_STATE(ucPortIndex))
            {
                case _PD_INT_SEND_CBL_DISCOVER_ID:
                case _PD_INT_SEND_CBL_SOFT_RESET:

                    ScalerTypeCTcpmPdIntTxCableReqFailProc_EXINT0(ucPortIndex);

                    break;

                case _PD_SRC_INT_SEND_CAP:

                    ADD_TCPM_PD_SRC_CAP_CNT(ucPortIndex);

                    // Check if Source Capability is sent More than Difined Max Times
                    if(GET_TCPM_PD_SRC_CAP_CNT(ucPortIndex) > _MAX_SRC_CAP_CNT)
                    {
                        // Transit to PD No-Response
                        SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_NO_RESPONSE);

                        // Disable ALERT.Rx_RCV_SOP + ALERT.Rx_Overflow
                        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_OVERFLOW), _DISABLE);
                    }
                    else
                    {
                        // Wait 120ms and Send Re-Src_Cap
                        ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 120, _SCALER_WD_TIMER_EVENT_TCPM_SEND_SRC_CAP);
                    }

                    break;

                case _PD_SRC_READY:
                case _PD_SNK_READY:

                    if((GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_CABLE_PROC) || (GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_CBL_DP_VDM_REQ))
                    {
                        ScalerTypeCTcpmPdIntTxCableReqFailProc_EXINT0(ucPortIndex);
                    }

                    if(GET_TCPM_PD_SUB_STATE(ucPortIndex) == _PD_SUB_SEND_ALERT)
                    {
                        // Set AMS = None
                        SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                        // Back to Ready State
                        ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                        SET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex, _PD_PORT_CTRL_EVENT_ALERT_EVENT_FAILED);
                        CLR_TCPM_PD_SYS_EVENT(ucPortIndex, _PD_SYS_EVENT_ALERT_EVENT);
                        CLR_TCPM_PD_TYPE_OF_ALERT(ucPortIndex, _TYPE_C_TYPE_OF_ALERT_ALL);
                        SET_TCPM_PD_EXT_ALERT_EVENT(ucPortIndex, _TYPE_C_EXT_ALERT_EVENT_NONE);
                    }

                    break;

                default:

                    break;
            }

            break;

        case _PD_TX_RETRY_FAIL_ERROR_RECOVERY:

            SET_TCPM_CC_ERROR_RECOVERY(ucPortIndex);

            break;

        case _PD_TX_RETRY_FAIL_SOFT_RESET:

            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_INT_SEND_SOFTRESET);
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_STATE_NONE);
            SET_TCPM_PD_TX_RETRY_FAIL_EVENT(ucPortIndex, _PD_TX_RETRY_FAIL_HARD_RESET);

            ScalerTypeCTcpmPdSendSoftRst_EXINT0(ucPortIndex, _PD_SOP_PKT);

            break;

        case _PD_TX_RETRY_FAIL_HARD_RESET:

            ScalerTypeCTcpmPdSendHardRst_EXINT0(ucPortIndex);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process When Tx Transmit Cable Request Success in Interrupt
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntTxCableReqSuccessProc_EXINT0(BYTE ucPortIndex)
{
    switch(GET_TCPM_PD_FW_STATE(ucPortIndex))
    {
        case _PD_INT_SEND_CBL_DISCOVER_ID:

            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_INT_WAIT_CBL_DISCOVER_ID_RESP);
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);

            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Send Src_Cap
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

            break;

        case _PD_INT_SEND_CBL_SOFT_RESET:

            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_INT_WAIT_CBL_SOFT_RESET_RESP);
            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);

            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Send Discover ID(SOP')
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

            break;

        case _PD_SRC_READY:
        case _PD_SNK_READY:

            switch(GET_TCPM_PD_SUB_STATE(ucPortIndex))
            {
                case _PD_SUB_CABLE_PROC:

                    switch(GET_TCPM_PD_CBL_STATE(ucPortIndex))
                    {
                        case _PD_CBL_SEND_SOFT_RST:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_INT_WAIT_SOFT_RST_RESP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Back to Ready State
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

                            break;

                        case _PD_CBL_SEND_DISCOVER_ID:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_INT_WAIT_DISCOVER_ID_RESP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Back to Ready State
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

                            break;

                        default:

                            break;
                    }

                    break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))
                case _PD_SUB_SEND_CBL_DP_VDM_REQ:

                    switch(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex))
                    {
                        case _PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Discover ID
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Discover SVID
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_DP_DISCOVER_MODE_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Discover DP Mode
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_TBT3_DISCOVER_MODE_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Discover TBT3 Mode
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_P:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Enter DP Mode
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_PP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Enter DP Mode
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send DP Config
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_PP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send DP Config
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Exit DP Mode
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP:

                            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
                            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_PP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Exit DP Mode
                            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

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
// Description  : Process When Tx Transmit Cable Request Fail in Interrupt
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntTxCableReqFailProc_EXINT0(BYTE ucPortIndex)
{
    switch(GET_TCPM_PD_FW_STATE(ucPortIndex))
    {
        case _PD_INT_SEND_CBL_DISCOVER_ID:

            ADD_TCPM_PD_CBL_DISC_ID_RETRY_CNT(ucPortIndex);

            // If Retry Fail, Set FW State to Continue On-going PD Flow
            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SRC_WDINT_SEND_CAP);

            // Active WD Timer Event To Check Vbus, Then Start PMIC Protection and Send SRC_CAP if VbusSafe5V
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 20, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);

            break;

        case _PD_INT_SEND_CBL_SOFT_RESET:

            SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_WDINT_SEND_CBL_DISCOVER_ID);

            // Active WD Timer Event to Send Discover ID (SOP')
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, 10, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);

            break;

        case _PD_SRC_READY:
        case _PD_SNK_READY:

            switch(GET_TCPM_PD_SUB_STATE(ucPortIndex))
            {
                case _PD_SUB_CABLE_PROC:

                    switch(GET_TCPM_PD_CBL_STATE(ucPortIndex))
                    {
                        case _PD_CBL_SEND_SOFT_RST:

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_STATE_NONE);

                            break;

                        case _PD_CBL_SEND_DISCOVER_ID:

                            ADD_TCPM_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT(ucPortIndex) >= _MAX_HW_RETRY_CBL_DISCOVER_ID_RETRY_FAIL_CNT)
                            {
                                SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_NON_PD_CAPABLE);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
                            SET_TCPM_PD_CBL_STATE(ucPortIndex, _PD_CBL_STATE_NONE);

                            break;

                        default:

                            break;
                    }

                    break;

#if((_TYPE_C_MODAL_OPERATION_SUPPORT == _ON) && (_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))
                case _PD_SUB_SEND_CBL_DP_VDM_REQ:

                    switch(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex))
                    {
                        case _PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P:

                            ADD_TCPM_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT(ucPortIndex);

                            if(GET_TCPM_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT(ucPortIndex) >= _MAX_HW_RETRY_CBL_DISCOVER_ID_RETRY_FAIL_CNT)
                            {
                                SET_TCPM_PD_CBL_PD_CAPABILITY(ucPortIndex, _TYPE_C_CABLE_NON_PD_CAPABLE);

                                // If No VDO Received, Set Passive Cable & HBR3 According to DPAM2.1
                                SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_PASSIVE);
                                SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_HBR3);

                                // Stop Enter DP Alt Mode Flow Just for Cable
                                CLR_TCPM_PD_CBL_ENTER_DP_MODE_SUPPORT(ucPortIndex);
                                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);
                            }

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                            break;

                        case _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P:

                            // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No GoodCRC of Discover Svid(SOP' / SOP'') Received
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(ucPortIndex));

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                            break;

                        case _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P:

                            // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No GoodCRC of DP Discover Mode(SOP' / SOP'') Received
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(ucPortIndex));

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                            break;

                        case _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P:

                            // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No GoodCRC of TBT3 Discover Mode(SOP' / SOP'') Received
                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(ucPortIndex));

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                            break;

                        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_P:
                        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP:

                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_ENTER_MODE);

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                            break;

                        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P:
                        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP:

                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_DP_CONFIG);

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

                            break;

                        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P:
                        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP:

                            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_SEND_EXIT_MODE);

                            // Back to Ready State
                            ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);

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

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process When Tx Transmit Dp VDM Request Msg Success in Interrupt
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntTxDpVdmReqSuccessProc_EXINT0(BYTE ucPortIndex)
{
    switch(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex))
    {
        case _PD_ALT_MODE_SEND_DISCOVER_ID:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DISCOVER_ID
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_SVID:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DISCOVER_SVID
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_MODE:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_DISCOVER_MODE_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DISCOVER_MODE
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_ENTER_MODE:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP);

            // Start VDMModeEntryTimer (40-50ms), Timeout : back to Sub SRC/SNK Ready and Re-Send ENTER_MODE
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _VDM_MODE_ENTRY_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_DP_STATUS:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_DP_STATUS_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DP_STATUS
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_DP_CONFIG:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DP_CONFIG
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_READY:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DP_STATUS
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_EXIT_MODE:

            SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_INTERRUPTIBLE);
            SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_INT_WAIT_VDM_RESP);
            SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP);

            // Start VDMModeExitTimer (40-50ms), Timeout : back to Sub SRC/SNK Ready and Re-Send EXIT_MODE
            ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _VDM_MODE_EXIT_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_ATTENTION:

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
            {
                if(GET_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex) == _TRUE)
                {
                    CLR_TCPM_PD_FORCE_HPD_IRQ(ucPortIndex);
                }
                else
                {
                    // Set WAIT FLAG to Prevent from Sending Attention in HPD Space Time
                    if(GET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)) != 0)
                    {
                        SET_TCPM_PD_DPAM_ATTENTION_WAIT(ucPortIndex);
                        ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, GET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)), _SCALER_TIMER_EVENT_TCPM_CLR_ATTENTION_WAIT);
                    }

                    // Pop Out One HPD From Queue
                    ScalerTypeCTcpmPdPopHpd_EXINT0(ucPortIndex);
                }

                // Set AMS = None
                SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
            }
#endif  // End of #if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)

            break;

        default:

            break;
    }
}
#endif // End of #if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Process When Tx Transmit VDM Response Msg Success in Interrupt
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdIntTxVdmRespSuccessProc_EXINT0(BYTE ucPortIndex)
{
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
    EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];

    if(GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID)
    {
        switch(GET_TCPM_PD_DP_ALT_STATE(ucPortIndex))
        {
            case _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK:

                // Set Enter Mode Flag
                SET_TCPM_PD_DPAM_ENTER(ucPortIndex);

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                if((GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX) && (GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_USB_CONFIG))
                {
                    // Push _PD_HPD_LOW into HPD_Queue
                    ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], _PD_HPD_LOW, 0);
                }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                {
                    // Clear HPD Queue
                    ScalerTypeCTcpmPdClrHpd_EXINT0(ucPortIndex);
                }
#endif

                break;

            case _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK:

                // For DC_OFF Option = Charge Function Only
                if(GET_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex) == _TRUE)
                {
                    // Disable Alt. Mode Resp When DC_OFF
                    CLR_TCPM_PD_ALT_MODE_FUNCTION(ucPortIndex);

                    // Clear Exit Mode Request
                    CLR_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex);
                }

                // Clear Alt. Mode Status
                SET_TCPM_PD_DP_ALT_STATE(ucPortIndex, _PD_ALT_MODE_NONE);
                CLR_TCPM_PD_DPAM_ENTER(ucPortIndex);
                SET_TCPM_PD_DPAM_CONFIG(ucPortIndex, _PD_USB_CONFIG);
                CLR_TCPM_PD_PARTNER_INIT_ALT_MODE(ucPortIndex);

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                {
                    ScalerDpAuxRxHpdTogglePhyResetProc(ScalerTypeCPcbPortConvertToDx_EXINT0(enumTypeCPcbPort), _LOW);
                    SET_TCPM_PD_HPD_STATUS(ucPortIndex, _LOW);
                }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                {
                    ScalerTypeCTcpmPdPushHpd_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], _PD_HPD_LOW, 0);
                }
#endif

                break;

            case _PD_ALT_MODE_INT_SEND_DP_STATUS_ACK:

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                {
                    // "DP Status Ack" Only Access HPD Queue when (HPD Count > 0) & (Not Attn Wait)
                    if((GET_TCPM_PD_HPD_CNT(ucPortIndex) > 0) && (GET_TCPM_PD_DPAM_ATTENTION_WAIT(ucPortIndex) == _FALSE))
                    {
                        // Set WAIT FLAG to Prevent from Sending Attention in HPD Space Time
                        if(GET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)) != 0)
                        {
                            SET_TCPM_PD_DPAM_ATTENTION_WAIT(ucPortIndex);
                            ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, GET_TCPM_PD_HPD_SPACE_TIME(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)), _SCALER_TIMER_EVENT_TCPM_CLR_ATTENTION_WAIT);
                        }

                        // Pop Out One HPD From Queue
                        ScalerTypeCTcpmPdPopHpd_EXINT0(ucPortIndex);
                    }
                }
#endif

                break;

            case _PD_ALT_MODE_INT_SEND_DP_CONFIG_ACK:

                if(GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex) == _TYPE_C_PIN_ASSIGNMENT_NONE)
                {
                    SET_TCPM_PD_DPAM_CONFIG(ucPortIndex, _PD_USB_CONFIG);
                }
                else
                {
                    CLR_TCPM_PD_DPAM_WAIT_CONFIG(ucPortIndex);
                    SET_TCPM_PD_DPAM_CONFIG(ucPortIndex, _PD_DP_CONFIG);

                    // If in DP Config, Clear Partner Initial Alt Mode Macro
                    CLR_TCPM_PD_PARTNER_INIT_ALT_MODE(ucPortIndex);

                    // Clear VDM Response Conflict Cnt and Cancel TimerEvent
                    CLR_TCPM_PD_VDM_RESP_CONFLICT_CNT(ucPortIndex);
                    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_VDM_RESP_CONFLICT_TIMEOUT);

                    // Cancel CLR_PARTNER_ALT_SUPPORT TimerEvent When Already Dp Config
                    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_PARTNER_ALT_SUPPORT);

                    // Cancel _T480_ERROR_RECOVERY TimerEvent When Already Dp Config
                    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_T480_ERROR_RECOVERY);
                }

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_EMB_TCPM_DP_ALT_MODE_SUPPORT == _ON)

    // Set AMS = None
    SET_TCPM_PD_AMS_STATUS(ucPortIndex, _PD_AMS_NONE);

    // Back to Ready State
    ScalerTypeCTcpmPdBackToReadyState_EXINT0(ucPortIndex);
}
#endif // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Type C TCPM Send PD Message
// Input Value  : ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSendMsg_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucTransmitInfo = 0x00;

    // 1. Clear and Enable Tx_SUCCESS + Tx_FAIL + Tx_DISCARD
    ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, ((WORD)(_TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS)), _ENABLE);

    // 2. Construct Message and Write Data to Tx Buffer [0x51~]
    ScalerTypeCTcpmPdConstructMsg_EXINT0(ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd);

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
    ScalerTypeCTcpmRxIntControl_EXINT0(ucPortIndex, _DISABLE);

    // Set Transmit
    ScalerTypeCTcpmTcpciSetTransmit_EXINT0(ucPortIndex, ucTransmitInfo);
}

//--------------------------------------------------
// Description  : Type C TCPM Construct PD Message to Send
// Input Value  : ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructMsg_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucExtendedBit_EXINT = 0;
    BYTE ucDataObjectCnt_EXINT = 0;
    WORD usMsgHeader_EXINT = 0;

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
        case _PD_CMD_NOT_SUPPORT:
        case _PD_CMD_GET_SRC_CAP_EXT:
        case _PD_CMD_GET_STATUS:
        case _PD_CMD_FR_SWAP:
        case _PD_CMD_GET_PPS_STATUS:
        case _PD_CMD_GET_COUNTRY_CODES:

            ucExtendedBit_EXINT = 0;
            ucDataObjectCnt_EXINT = 0;

            break;

        // ------------------------------------
        // Data Message
        // Extended = 0, Data Object = According to Message Type
        // ------------------------------------
        case _PD_CMD_SRC_CAP:

            ucExtendedBit_EXINT = 0;
            ucDataObjectCnt_EXINT = GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex);

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            // Do not send PPS PDO when the Spec Version is PD2.0 or not support PPS
            if((GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON) && (GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_2_0))
#endif
            {
                for(BYTE ucLoopIndex = GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex) - 1; ucLoopIndex > 0; ucLoopIndex--)
                {
                    if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        ucDataObjectCnt_EXINT --;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            break;

        case _PD_CMD_REQUEST:

            ucDataObjectCnt_EXINT = 1;

            break;

        case _PD_CMD_SNK_CAP:

            ucDataObjectCnt_EXINT = GET_TCPM_PD_SPR_SNK_PDO_CNT(ucPortIndex);

            break;

        case _PD_CMD_VDM:

            ucDataObjectCnt_EXINT = ScalerTypeCTcpmPdSetVdmDataObjCnt_EXINT0(ucPortIndex, enumVdmCmd);

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_BAT_STATUS:        // Not Implemented
        case _PD_CMD_ALERT:
        case _PD_CMD_GET_COUNTRY_INFO:  // Not Implemented
        case _PD_CMD_REVISION:

            ucDataObjectCnt_EXINT = 1;

            break;

        // ------------------------------------
        // Extended Message
        // Extended = 1, Data Object = According to Message Type
        // ------------------------------------
        case _PD_CMD_SRC_CAP_EXT:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 7;

            break;

        case _PD_CMD_SNK_CAP_EXT:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 7;

            break;

        case _PD_CMD_STATUS:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 3;

            break;

        case _PD_CMD_MFC_INFO:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 5;

            break;

        case _PD_CMD_CHUNK_TEST:

            if(GET_TCPM_PD_RCV_EXT_CHUNK_REQ(ucPortIndex) == _TRUE)
            {
                ucExtendedBit_EXINT = 1;
                ucDataObjectCnt_EXINT = 1;
            }

            break;

        case _PD_CMD_PPS_STATUS:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 2;

            break;

        case _PD_CMD_GET_BAT_CAP:
        case _PD_CMD_GET_BAT_STATUS:
        case _PD_CMD_BAT_CAP:
        case _PD_CMD_GET_MFC_INFO:
        case _PD_CMD_SEC_REQ:
        case _PD_CMD_SEC_RESP:
        case _PD_CMD_FW_UPDATE_REQ:
        case _PD_CMD_FW_UPDATE_RESP:
        case _PD_CMD_COUNTRY_INFO:
        case _PD_CMD_COUNTRY_CODES:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 0;

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        default:

            ucExtendedBit_EXINT = 0;
            ucDataObjectCnt_EXINT = 0;

            break;
    }

    // 2. Construct Data Object into Tx FIFO, if Number of Data Object is not 0
    if(ucDataObjectCnt_EXINT != 0)
    {
        ScalerTypeCTcpmPdConstructDataObj_EXINT0(ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd);
    }

    // 3. Construct Message Header
    // [15] Extended, [14:12] Num of Data Obj., [4:0] Command
    usMsgHeader_EXINT = (((ucExtendedBit_EXINT & (_BIT0)) << 15) | ((ucDataObjectCnt_EXINT & (_BIT2 | _BIT1 | _BIT0)) << 12) | (enumPdCmd & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

    if(enumPacketType == _PD_SOP_PKT)
    {
        // [11:9] Message ID, [8] Power Role, [7:6] Spec Ver, [5] Data Role
        usMsgHeader_EXINT = (usMsgHeader_EXINT | (GET_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex) << 9) | (GET_TCPM_POWER_ROLE(ucPortIndex) << 8) | (GET_TCPM_PD_SPEC_VER(ucPortIndex) << 6) | (GET_TCPM_DATA_ROLE(ucPortIndex) << 5));
    }
    else if(enumPacketType == _PD_SOP_P_PKT)
    {
        // [11:9] Message ID, [8] Cable Plug : Device(0), [7:6] Spec Ver, [5] Rsv.
        usMsgHeader_EXINT = (usMsgHeader_EXINT | (GET_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex) << 9) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }
    else if(enumPacketType == _PD_SOP_PP_PKT)
    {
        // [11:9] Message ID, [8] Cable Plug : Device(0), [7:6] Spec Ver, [5] Rsv.
        usMsgHeader_EXINT = (usMsgHeader_EXINT | (GET_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex) << 9) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }

    // 4. Write Message to TCPC Tx Buffer (Port, TxByteCnt, Message Header)
    ScalerTypeCTcpmTcpciSetTxBuffer_EXINT0(ucPortIndex, enumPdCmd, (2 + (ucDataObjectCnt_EXINT * 4)), usMsgHeader_EXINT);
}

//--------------------------------------------------
// Description  : Type C TCPM Construct PD Message to Send
// Input Value  : ucPortIndex, enumPacketType, enumPdCmd, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructDataObj_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
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

        case _PD_CMD_SNK_CAP:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| PR | HC | UP | UC | DR | -- |
            if((GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP) && ((GET_TCPM_PD_SRC_ACCEPT_SWAP_TO_SNK(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SNK_ACCEPT_SWAP_TO_SRC(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SRC_REQUEST_SWAP_TO_SNK(ucPortIndex) == _TRUE) || (GET_TCPM_PD_SNK_REQUEST_SWAP_TO_SRC(ucPortIndex) == _TRUE)))
            {
                if(GET_TCPM_CC_PORT_ROLE(ucPortIndex) == _TYPE_C_PORT_DRP)
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT5);
                }
            }

#if(_HIGHER_CAP == _TRUE)
            g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT4);
#endif

            if(GET_TCPM_PD_UNCONSTRAIN_POWER(ucPortIndex) == _TRUE)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT3);
            }

            if((GET_TCPM_USB_ROLE(ucPortIndex) != _TYPE_C_USB_NOT_SUPPORT) || (GET_TCPM_USB_SPEED(ucPortIndex) == _USB_BILLBOARD_ONLY))
            {
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT2);
            }


            if((GET_TCPM_PD_DFP_SWAP_TO_UFP(ucPortIndex) == _TRUE) || (GET_TCPM_PD_UFP_SWAP_TO_DFP(ucPortIndex) == _TRUE))
            {
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT1);
            }

            for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TCPM_PD_SPR_SNK_PDO_CNT(ucPortIndex); ucLoopIndex ++)
            {
                if(GET_TCPM_PD_SNK_PDO_TYPE(ucPortIndex, ucLoopIndex) == _PD_FIX_SUPPLY_PDO)
                {
                    // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] | (((BYTE)GET_TCPM_PD_SNK_PDO_TYPE(ucPortIndex, ucLoopIndex)) << 6);

                    // | 23 | 22 | 21 | 20 | 19 .. 16 | 15 .. 10 | 09 | 08 | 07 .. 00 |
                    // | FR | Reserved(0)  | Voltage(50mV)[9:0]  |   Max.Cur [9:0]    |
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)((GET_TCPM_PD_SNK_CAP_VOL_MAX(ucPortIndex, ucLoopIndex) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)((GET_TCPM_PD_SNK_CAP_VOL_MAX(ucPortIndex, ucLoopIndex) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)(GET_TCPM_PD_SNK_CAP_CUR(ucPortIndex, ucLoopIndex) >> 8) & (_BIT1 | _BIT0));
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)(GET_TCPM_PD_SNK_CAP_CUR(ucPortIndex, ucLoopIndex)));
                }
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
                else if(GET_TCPM_PD_SNK_PDO_TYPE(ucPortIndex, ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                {
                    // [31:30] PDO Type = 2'b11 (Programmabl Power Supply)
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] | (((BYTE)GET_TCPM_PD_SNK_PDO_TYPE(ucPortIndex, ucLoopIndex)) << 6);

                    // [24:17] Max Voltage in 100mV
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4)] | ((BYTE)((GET_TCPM_PD_SNK_CAP_VOL_MAX(ucPortIndex, ucLoopIndex) / 10) >> 7) & (_BIT0));
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)((GET_TCPM_PD_SNK_CAP_VOL_MAX(ucPortIndex, ucLoopIndex) / 10) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 2] = (BYTE)(GET_TCPM_PD_SNK_CAP_VOL_MIN(ucPortIndex, ucLoopIndex) / 10);

                    // [6:0] Max Current in 50mA
                    g_pucTypeCTcpmPdDataObj_EXINT[(ucLoopIndex * 4) + 3] = (((BYTE)GET_TCPM_PD_SNK_CAP_CUR(ucPortIndex, ucLoopIndex)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
#endif
            }

            break;

        case _PD_CMD_VDM:

            ScalerTypeCTcpmPdConstructVdmDataObj_EXINT0(ucPortIndex, enumPacketType, enumVdmCmd);

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

        case _PD_CMD_SRC_CAP_EXT:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 25
            g_pucTypeCTcpmPdDataObj_EXINT[1] = 25;

            // ---------- SECDB : Source Cap Ext Data Blocks (23 Bytes) ----------
            // Byte 00 - 01 :   Vender ID - 0x0BDA (RealTek)
            g_pucTypeCTcpmPdDataObj_EXINT[2] = _USB_VENDOR_ID_L;
            g_pucTypeCTcpmPdDataObj_EXINT[3] = _USB_VENDOR_ID_H;

            // Byte 02 - 03 :   Product ID
            g_pucTypeCTcpmPdDataObj_EXINT[4] = _USB_PRODUCT_ID_L;
            g_pucTypeCTcpmPdDataObj_EXINT[5] = _USB_PRODUCT_ID_H;

            // Byte 04 - 07 :   XID
            g_pucTypeCTcpmPdDataObj_EXINT[6] = _USB_XID_BYTE0;
            g_pucTypeCTcpmPdDataObj_EXINT[7] = _USB_XID_BYTE1;
            g_pucTypeCTcpmPdDataObj_EXINT[8] = _USB_XID_BYTE2;
            g_pucTypeCTcpmPdDataObj_EXINT[9] = _USB_XID_BYTE3;

            // Byte 08 : FW Version
            g_pucTypeCTcpmPdDataObj_EXINT[10] = _PD_FW_VERSION;

            // Byte 09 : HW Version
            g_pucTypeCTcpmPdDataObj_EXINT[11] = _PD_HW_VERSION;

            // Byte 10 : Voltage Regulation
            // Byte 11 : Holdup Time
            // Byte 12 : Compliance
            // Byte 13 : Touch Current
            // Byte 14 - 15 : Peak Current 1
            // Byte 16 - 17 : Peak Current 2
            // Byte 18 - 19 : Peak Current 3
            // Byte 20 : Touch Temp
            // Byte 21 : Source Input [0] Ext Power / [1] Ext Power Unconstrained / [2] Internal Battery Exist
            g_pucTypeCTcpmPdDataObj_EXINT[23] = (_BIT1 | _BIT0);

            // Byte 22 : Battries
            // Byte 23 : SPR Source PDP Rating [Unit = W]
            if(GET_TCPM_MAX_POWER(ucPortIndex) > 1000)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[25] = 100;
            }
            else
            {
                g_pucTypeCTcpmPdDataObj_EXINT[25] = (GET_TCPM_MAX_POWER(ucPortIndex) / 10);
            }

            // Byte 24 : EPR Source PDP Rating [Unit = W]
            if(GET_TCPM_PD_EPR_SRC_CAPABLE(ucPortIndex) == _TRUE)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[26] = (GET_TCPM_MAX_POWER(ucPortIndex) / 10);
            }

            break;

        case _PD_CMD_SNK_CAP_EXT:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 24
            g_pucTypeCTcpmPdDataObj_EXINT[1] = 24;

            // ---------- SKEDB : Sink Cap Ext Data Blocks (24 Bytes) ----------
            // Byte 00 - 01 :   Vender ID - 0x0BDA (RealTek)
            g_pucTypeCTcpmPdDataObj_EXINT[2] = _USB_VENDOR_ID_L;
            g_pucTypeCTcpmPdDataObj_EXINT[3] = _USB_VENDOR_ID_H;

            // Byte 02 - 03 :   Product ID
            g_pucTypeCTcpmPdDataObj_EXINT[4] = _USB_PRODUCT_ID_L;
            g_pucTypeCTcpmPdDataObj_EXINT[5] = _USB_PRODUCT_ID_H;

            // Byte 04 - 07 :   XID
            g_pucTypeCTcpmPdDataObj_EXINT[6] = _USB_XID_BYTE0;
            g_pucTypeCTcpmPdDataObj_EXINT[7] = _USB_XID_BYTE1;
            g_pucTypeCTcpmPdDataObj_EXINT[8] = _USB_XID_BYTE2;
            g_pucTypeCTcpmPdDataObj_EXINT[9] = _USB_XID_BYTE3;

            // Byte 08 : FW Version
            g_pucTypeCTcpmPdDataObj_EXINT[10] = _PD_FW_VERSION;

            // Byte 09 : HW Version
            g_pucTypeCTcpmPdDataObj_EXINT[11] = _PD_HW_VERSION;

            // Byte 10 : SKEDB Version : 1 (Version 1.0)
            g_pucTypeCTcpmPdDataObj_EXINT[12] = 1;

            // Byte 11 : Load Step
            // Byte 12 - 13 : Sink Load Characteristics
            // Byte 14 : Compliance
            // Byte 15 : Touch Temp
            // Byte 16 : Battery Info
            // Byte 17 : Sink Modes [0] PPS charging supported / [1] VBUS powered / [2] Mains powered / [3] Battery powered /
            // -------------------- [4] Battery essentially unlimited / [5] AVS Supported
#if(_TYPE_C_POWER_SOURCE == _TYPE_C_SELF_POWER_ONLY)
            g_pucTypeCTcpmPdDataObj_EXINT[19] = _BIT2;
#elif(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
            g_pucTypeCTcpmPdDataObj_EXINT[19] = _BIT1;
#elif(_TYPE_C_POWER_SOURCE == _TYPE_C_SELF_AND_VBUS_POWER)
            g_pucTypeCTcpmPdDataObj_EXINT[19] = (_BIT2 | _BIT1);
#endif

            // Byte 18 : Sink Minimum PDP [Unit = W] (Rounded Up to the Next Integer)
            g_pucTypeCTcpmPdDataObj_EXINT[20] = (GET_TCPM_PD_SNK_MIN_PDP(ucPortIndex) / 10) + ((GET_TCPM_PD_SNK_MIN_PDP(ucPortIndex) % 10) != 0);

            // Byte 19 : Sink Operational PDP [Unit = W] (Rounded Up to the Next Integer)
            g_pucTypeCTcpmPdDataObj_EXINT[21] = (GET_TCPM_PD_SNK_OPERATIONAL_PDP(ucPortIndex) / 10) + ((GET_TCPM_PD_SNK_OPERATIONAL_PDP(ucPortIndex) % 10) != 0);

            // Byte 20 : Sink Maximum PDP [Unit = W] (Rounded Up to the Next Integer)
            g_pucTypeCTcpmPdDataObj_EXINT[22] = (GET_TCPM_PD_SNK_MAX_PDP(ucPortIndex) / 10) + ((GET_TCPM_PD_SNK_MAX_PDP(ucPortIndex) % 10) != 0);

            // Byte 21 : EPR Sink Minimum PDP
            // Byte 22 : EPR Sink Operational PDP
            // Byte 23 : EPR Sink Maximum PDP

            break;

        case _PD_CMD_STATUS:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 7
            g_pucTypeCTcpmPdDataObj_EXINT[1] = 7;

            // ---------- SDB : Status Data Blocks (6 Bytes) ----------
            // Byte 00 : Internal Temp (Unit = Temp in C / 0 = Not Support)

            // Byte 01 : Present Input [7:5] Reserved
            // [4] Internal Power From Non Battery
            // [3] Internal Power From Battery
            // [2] External Power DC = 0 / AC = 1
            // [1] External Power Exist
            g_pucTypeCTcpmPdDataObj_EXINT[3] = g_pucTypeCTcpmPdDataObj_EXINT[3] | (_BIT4 | _BIT2 | _BIT1);

            // Byte 02 : Present Battery Input [7:4] : Hot Swappable / [3:0] Fixed Battery
            // Byte 03 : Event Flag [7:5] : Reserved / [4] : CC,CV / [3] : OVP / [2] OTP / [1] OCP / [0] Reserved
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_BY_USER)
            if(((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP) || ((GET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex) & _PD_PORT_CTRL_EVENT_POWER_OVP) == _PD_PORT_CTRL_EVENT_POWER_OVP))
            {
                g_pucTypeCTcpmPdDataObj_EXINT[5] = g_pucTypeCTcpmPdDataObj_EXINT[5] | (_BIT3);
            }
            if(((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP) || ((GET_TCPM_PD_PORT_CTRL_EVENT(ucPortIndex) & _PD_PORT_CTRL_EVENT_POWER_OCP) == _PD_PORT_CTRL_EVENT_POWER_OCP))
            {
                g_pucTypeCTcpmPdDataObj_EXINT[5] = g_pucTypeCTcpmPdDataObj_EXINT[5] | (_BIT1);
            }
#else
            if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[5] = g_pucTypeCTcpmPdDataObj_EXINT[5] | (_BIT3);
            }
            if((GET_TCPM_PD_SYS_EVENT(ucPortIndex) & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[5] = g_pucTypeCTcpmPdDataObj_EXINT[5] | (_BIT1);
            }
#endif

            // Byte 04 : Temperature State
            // Byte 05 : Power Status [1] Source power limited due to cable supported current
            for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex); ucLoopIndex ++)
            {
                if(GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucLoopIndex) > GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex))
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[7] = g_pucTypeCTcpmPdDataObj_EXINT[7] | (_BIT1);
                }
            }

            // Byte 06 : Power State Change
            g_pucTypeCTcpmPdDataObj_EXINT[8] = g_pucTypeCTcpmPdDataObj_EXINT[8] | ((BYTE)(GET_TCPM_PD_NEW_POWER_STATE(ucPortIndex)) & (_BIT2 | _BIT1 | _BIT0));
            g_pucTypeCTcpmPdDataObj_EXINT[8] = g_pucTypeCTcpmPdDataObj_EXINT[8] | ((BYTE)(GET_TCPM_PD_NEW_POWER_INDICATOR(ucPortIndex) << 3) & (_BIT5 | _BIT4 | _BIT3));

            break;

        case _PD_CMD_MFC_INFO:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 4 ~ 26.
            // [MQP] PD3.0 Protocol test (Source) : GPROT-SRC3-MNINF.
            // Rcv. Get_Manu_Info with Invalid Target/Reference Shall Resp. Manu_Info with (VID + PID + Null-Ended "Not Supported" ASCII String).
            g_pucTypeCTcpmPdDataObj_EXINT[1] = 18;

            // ---------- MIDB : Manufacturer Into Data Blocks (18 Bytes) ----------
            // Byte 00 - 01 :   Vender ID - 0x0BDA (RealTek)
            g_pucTypeCTcpmPdDataObj_EXINT[2] = _USB_VENDOR_ID_L;
            g_pucTypeCTcpmPdDataObj_EXINT[3] = _USB_VENDOR_ID_H;

            // Byte 02 - 03 :   Product ID
            g_pucTypeCTcpmPdDataObj_EXINT[4] = _USB_PRODUCT_ID_L;
            g_pucTypeCTcpmPdDataObj_EXINT[5] = _USB_PRODUCT_ID_H;

            // Byte 04 - 26 :   Manufacturer String
            g_pucTypeCTcpmPdDataObj_EXINT[6] = 0x4E; // N
            g_pucTypeCTcpmPdDataObj_EXINT[7] = 0x6F; // o

            g_pucTypeCTcpmPdDataObj_EXINT[8] = 0x74; // t
            g_pucTypeCTcpmPdDataObj_EXINT[9] = 0x20; // " "

            g_pucTypeCTcpmPdDataObj_EXINT[10] = 0x53; // S
            g_pucTypeCTcpmPdDataObj_EXINT[11] = 0x75; // u

            g_pucTypeCTcpmPdDataObj_EXINT[12] = 0x70; // p
            g_pucTypeCTcpmPdDataObj_EXINT[13] = 0x70; // p

            g_pucTypeCTcpmPdDataObj_EXINT[14] = 0x6F; // o
            g_pucTypeCTcpmPdDataObj_EXINT[15] = 0x72; // r

            g_pucTypeCTcpmPdDataObj_EXINT[16] = 0x74; // t
            g_pucTypeCTcpmPdDataObj_EXINT[17] = 0x65; // e

            g_pucTypeCTcpmPdDataObj_EXINT[18] = 0x64; // d
            g_pucTypeCTcpmPdDataObj_EXINT[19] = 0x00; // NULL

            break;

        case _PD_CMD_CHUNK_TEST:

            // If More Chunk Resp. Need to  Be Requested
            if(GET_TCPM_PD_RCV_EXT_CHUNK_REQ(ucPortIndex) == _TRUE)
            {
                // ---------- Extended Message Header (2 Bytes) ----------
                // [15] Ext Msg. is Sent in Chunk, [10] Chunk Request, [8:0] Data Size of Chunk Request Should Be 0
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT7 | _BIT2);

                // [14:11] Requested Next Chunk
                g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | ((GET_TCPM_PD_RCV_EXT_CHUNK_NUM(ucPortIndex) + 1) << 3);
            }

            break;

        case _PD_CMD_PPS_STATUS:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeCTcpmPdDataObj_EXINT[0] = g_pucTypeCTcpmPdDataObj_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 4
            g_pucTypeCTcpmPdDataObj_EXINT[1] = 4;

            // ---------- PPSSDB : PPS Status Data Blocks (4 Bytes) ----------
            // Byte 00 - 01 : Output Voltage in 20mV (0xFFFF Not Support)
            g_pucTypeCTcpmPdDataObj_EXINT[2] = 0xFF;
            g_pucTypeCTcpmPdDataObj_EXINT[3] = 0xFF;

            // Byte 02 : Output Current in 50mA (0xFF Not Support)
            g_pucTypeCTcpmPdDataObj_EXINT[4] = 0xFF;

            // Byte 03 : Real Time Flag
            // [3] OMF (1 : Current Fold Back / 0 : Constant Voltge)
#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON))
            if((GET_TCPM_PMIC_SUPPORT(ucPortIndex) == _ON) && (GET_TCPM_PD_PPS_SUPPORT(ucPortIndex) == _ON))
            {
                if(ScalerTypeCTcpmPmicReadPpsOperationModeStatus_EXINT0(ucPortIndex) == _TYPE_C_PMIC_CC_MODE_OPERATION)
                {
                    // Set Current Limit Mode
                    g_pucTypeCTcpmPdDataObj_EXINT[5] |= _BIT3;
                }
                else
                {
                    // Set Constant Voltage Mode
                    g_pucTypeCTcpmPdDataObj_EXINT[5] &= ~_BIT3;
                }
            }
            else
            {
                // Set Constant Voltage Mode
                g_pucTypeCTcpmPdDataObj_EXINT[5] &= ~_BIT3;
            }
#else
            // Set Constant Voltage Mode
            g_pucTypeCTcpmPdDataObj_EXINT[5] &= ~_BIT3;
#endif

            break;

        case _PD_CMD_REVISION:

            // ---------- Data Message (1 Data Object) ----------
            // [31:28] Revision.major, [27:24] Revision.minor,
            g_pucTypeCTcpmPdDataObj_EXINT[0] = _PD_SPEC_REVISION;

            // [23:20] Version.major, [19:16] Version.minor, [15:0] Reserved
            g_pucTypeCTcpmPdDataObj_EXINT[1] = _PD_SPEC_VERSION;
            g_pucTypeCTcpmPdDataObj_EXINT[2] = 0x00;
            g_pucTypeCTcpmPdDataObj_EXINT[3] = 0x00;

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        default:

            break;
    }// End of switch(enumPdCmd)
}

//--------------------------------------------------
// Description  : Set Up Number of VDM Data Objects(Data Blocks) @ Interrupt
// Input Value  : ucPortIndex, enumVdmCmd
// Output Value : Number of VDM Data Objects
//--------------------------------------------------
BYTE ScalerTypeCTcpmPdSetVdmDataObjCnt_EXINT0(BYTE ucPortIndex, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucVdmDataObjectCnt_EXINT = 0;

    if(enumVdmCmd == _PD_VDM_CMD_DISCOVER_ID_REQ)
    {
        ucVdmDataObjectCnt_EXINT = 1;
    }
    else if((enumVdmCmd == _PD_VDM_CMD_ATTENTION_REQ) || (enumVdmCmd == _PD_VDM_CMD_10))
    {
        ucVdmDataObjectCnt_EXINT = 2;
    }
    else if(GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID)
    {
        switch(enumVdmCmd)
        {
            case _PD_VDM_CMD_DISCOVER_SVID_ACK:

                ucVdmDataObjectCnt_EXINT = 1 + (GET_TCPM_PD_DPAM_SUPPORT(ucPortIndex) == _ON);

                break;

            case _PD_VDM_CMD_DISCOVER_ID_ACK:

                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    if((GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) != _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED) && (GET_TCPM_PD_DFP_PRODUCT_TYPE(ucPortIndex) != _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED))
                    {
                        ucVdmDataObjectCnt_EXINT = 7;
                    }
                    else if((GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) != _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED) || (GET_TCPM_PD_DFP_PRODUCT_TYPE(ucPortIndex) != _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED))
                    {
                        ucVdmDataObjectCnt_EXINT = 5;
                    }
                    else
                    {
                        ucVdmDataObjectCnt_EXINT = 4;
                    }
                }
                else
                {
#if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)
                    ucVdmDataObjectCnt_EXINT = 5;
#else
                    if((GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_UFP_PRODUCT_TYPE_HUB) || (GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL) || (GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED))
                    {
                        ucVdmDataObjectCnt_EXINT = 4;
                    }
#endif
                }

                break;

            case _PD_VDM_CMD_DISCOVER_ID_NAK:
            case _PD_VDM_CMD_DISCOVER_SVID_NAK:
            case _PD_VDM_CMD_DISCOVER_ID_BUSY:
            case _PD_VDM_CMD_DISCOVER_SVID_BUSY:
            default:

                ucVdmDataObjectCnt_EXINT = 1;

                break;
        }
    }
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
    else if((GET_TCPM_PD_DPAM_SUPPORT(ucPortIndex) == _ON) && (GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID))
    {
        EnumTypeCVdmDpCmd enumVdmDpCmd = (EnumTypeCVdmDpCmd)enumVdmCmd;

        switch(enumVdmDpCmd)
        {
            case _PD_VDM_DP_CMD_ENTER_MODE_ACK:
            case _PD_VDM_DP_CMD_EXIT_MODE_ACK:
            case _PD_VDM_DP_CMD_DP_CONFIG_ACK:
            case _PD_VDM_DP_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_DP_CMD_ENTER_MODE_NAK:
            case _PD_VDM_DP_CMD_EXIT_MODE_NAK:
            case _PD_VDM_DP_CMD_DP_STATUS_NAK:
            case _PD_VDM_DP_CMD_DP_CONFIG_NAK:
            case _PD_VDM_DP_CMD_DISCOVER_MODE_BUSY:
            case _PD_VDM_DP_CMD_ENTER_MODE_BUSY:
            case _PD_VDM_DP_CMD_EXIT_MODE_BUSY:
            case _PD_VDM_DP_CMD_DP_STATUS_BUSY:
            case _PD_VDM_DP_CMD_DP_CONFIG_BUSY:

                ucVdmDataObjectCnt_EXINT = 1;

                break;

            case _PD_VDM_DP_CMD_DISCOVER_MODE_ACK:
            case _PD_VDM_DP_CMD_DP_STATUS_ACK:

                ucVdmDataObjectCnt_EXINT = 2;

                break;

            default:

                ucVdmDataObjectCnt_EXINT = 0;

                break;
        }
    }
#endif  // End of #if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
    else
    {
        ucVdmDataObjectCnt_EXINT = 1;
    }

    return ucVdmDataObjectCnt_EXINT;
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO @ Interrupt
// Input Value  : ucPortIndex, enumPacketType, enumVdmCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructVdmDataObj_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucIndex = 0;

    enumPacketType = enumPacketType;

    if(GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _PD_SID)
    {
        switch(enumVdmCmd)
        {
            case _PD_VDM_CMD_DISCOVER_ID_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] PD SID = 0xFF00
                g_pucTypeCTcpmPdDataObj_EXINT[0] = GET_TCPM_PD_RCV_VDM_SVID_H(ucPortIndex);
                g_pucTypeCTcpmPdDataObj_EXINT[1] = GET_TCPM_PD_RCV_VDM_SVID_L(ucPortIndex);

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos = b'000
                g_pucTypeCTcpmPdDataObj_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Discover ID Ack (0x41)
                g_pucTypeCTcpmPdDataObj_EXINT[3] = enumVdmCmd;

                // According to the PD Version, Set Product Type VDO Differently
                ScalerTypeCTcpmPdSetProductTypeVDO_EXINT0(ucPortIndex);

                break;

            case _PD_VDM_CMD_DISCOVER_SVID_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] PD SID = 0xFF00
                g_pucTypeCTcpmPdDataObj_EXINT[0] = GET_TCPM_PD_RCV_VDM_SVID_H(ucPortIndex);
                g_pucTypeCTcpmPdDataObj_EXINT[1] = GET_TCPM_PD_RCV_VDM_SVID_L(ucPortIndex);

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucTypeCTcpmPdDataObj_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Discover SVID Ack (0x42)
                g_pucTypeCTcpmPdDataObj_EXINT[3] = enumVdmCmd;

                // -------- Data Obj : SVIDs --------
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
                if(GET_TCPM_PD_DPAM_SUPPORT(ucPortIndex) == _ON)
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[4 + ucIndex] = 0xFF;
                    g_pucTypeCTcpmPdDataObj_EXINT[5 + ucIndex] = 0x01;
                    ucIndex = ucIndex + 2;
                }
#endif

                if((ucIndex % 4) == 0)
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[4 + ucIndex] = 0x00;
                    g_pucTypeCTcpmPdDataObj_EXINT[5 + ucIndex] = 0x00;
                    g_pucTypeCTcpmPdDataObj_EXINT[6 + ucIndex] = 0x00;
                    g_pucTypeCTcpmPdDataObj_EXINT[7 + ucIndex] = 0x00;
                }
                else
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[4 + ucIndex] = 0x00;
                    g_pucTypeCTcpmPdDataObj_EXINT[5 + ucIndex] = 0x00;
                }

                break;

            case _PD_VDM_CMD_DISCOVER_ID_NAK:
            case _PD_VDM_CMD_DISCOVER_SVID_NAK:
            case _PD_VDM_CMD_DISCOVER_ID_BUSY:
            case _PD_VDM_CMD_DISCOVER_SVID_BUSY:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucTypeCTcpmPdDataObj_EXINT[0] = GET_TCPM_PD_RCV_VDM_SVID_H(ucPortIndex);
                g_pucTypeCTcpmPdDataObj_EXINT[1] = GET_TCPM_PD_RCV_VDM_SVID_L(ucPortIndex);

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucTypeCTcpmPdDataObj_EXINT[2] = (_BIT7) | (GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex));

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD
                g_pucTypeCTcpmPdDataObj_EXINT[3] = enumVdmCmd;

                break;

            default:

                break;
        }
    }
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
    else if(GET_TCPM_PD_RCV_VDM_SVID(ucPortIndex) == _DP_SID)
    {
        EnumTypeCVdmDpCmd enumVdmDpCmd = (EnumTypeCVdmDpCmd)enumVdmCmd;

        switch(enumVdmDpCmd)
        {
            case _PD_VDM_DP_CMD_DISCOVER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucTypeCTcpmPdDataObj_EXINT[0] = GET_TCPM_PD_RCV_VDM_SVID_H(ucPortIndex);
                g_pucTypeCTcpmPdDataObj_EXINT[1] = GET_TCPM_PD_RCV_VDM_SVID_L(ucPortIndex);

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucTypeCTcpmPdDataObj_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Discover Mode Ack (0x43)
                g_pucTypeCTcpmPdDataObj_EXINT[3] = enumVdmDpCmd;

                // -------- Data Obj 1 : DP Capability -----
                // [31:30] VDO Version = b'01(DPAM v2.1) / b'00(Not DPAM v2.1), [29:24] Rsv
                if((GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1) && (GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER))
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT6);
                }

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                {
                    if(GET_TCPM_CONNECTOR_TYPE(ucPortIndex) == _TYPE_C_PORT_PLUG)
                    {
                        // [23:16] DP_RX Pin Assignment Support (Not Supprt As DP Rx)
                        g_pucTypeCTcpmPdDataObj_EXINT[5] = 0x00;

                        // [15:8] DP_TX Pin Assignment Support
                        g_pucTypeCTcpmPdDataObj_EXINT[6] = GET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(ucPortIndex);

                        // [7] U2 Not Use = 0, [6] Plug = 0, [5:2] Signal Support (DP 1.3) = b'001, [1:0] DP Config.(RX) = b'01
                        g_pucTypeCTcpmPdDataObj_EXINT[7] = 0x05;
                    }
                    else
                    {
                        // [23:16] DP_RX Pin Assignment Support
                        g_pucTypeCTcpmPdDataObj_EXINT[5] = GET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(ucPortIndex);

                        // [15:8] DP_TX Pin Assignment Support (Not Supprt As DP Tx)
                        g_pucTypeCTcpmPdDataObj_EXINT[6] = 0x00;

                        // [7] U2 Not Use = 0, [6] Receptable = 1, [5:2] Signal Support (DP 1.3) = b'001, [1:0] DP Config.(RX) = b'01
                        g_pucTypeCTcpmPdDataObj_EXINT[7] = 0x45;
                    }
                }
#endif // End of #if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                {
                    if(GET_TCPM_CONNECTOR_TYPE(ucPortIndex) == _TYPE_C_PORT_PLUG)
                    {
                        // [23:16] DP_RX Pin Assignment Support
                        g_pucTypeCTcpmPdDataObj_EXINT[5] = GET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(ucPortIndex);

                        // [15:8] DP_TX Pin Assignment Support (Not Supprt As DP Tx)
                        g_pucTypeCTcpmPdDataObj_EXINT[6] = 0x00;

                        // [7] U2 Not Use = 0, [6] Plug = 0, [5:2] Signal Support (DP 1.3) = b'001, [1:0] DP Config.(TX) = b'10
                        g_pucTypeCTcpmPdDataObj_EXINT[7] = 0x06;
                    }
                    else
                    {
                        // [23:16] DP_RX Pin Assignment Support (Not Supprt As DP Rx)
                        g_pucTypeCTcpmPdDataObj_EXINT[5] = 0x00;

                        // [15:8] DP_TX Pin Assignment Support
                        g_pucTypeCTcpmPdDataObj_EXINT[6] = GET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(ucPortIndex);

                        // [7] U2 Not Use = 0, [6] Receptable = 1, [5:2] Signal Support (DP 1.3) = b'001, [1:0] DP Config.(TX) = b'10
                        g_pucTypeCTcpmPdDataObj_EXINT[7] = 0x46;
                    }
                }
#endif  // End of #if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)

                break;

            case _PD_VDM_DP_CMD_DP_STATUS_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucTypeCTcpmPdDataObj_EXINT[0] = GET_TCPM_PD_RCV_VDM_SVID_H(ucPortIndex);
                g_pucTypeCTcpmPdDataObj_EXINT[1] = GET_TCPM_PD_RCV_VDM_SVID_L(ucPortIndex);

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucTypeCTcpmPdDataObj_EXINT[2] = ((_BIT7) | (GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex)));

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = DP Status Ack (0x50)
                g_pucTypeCTcpmPdDataObj_EXINT[3] = enumVdmDpCmd;

                // -------- Data Obj 1 : DP Status ---------
                // [31:16] Reserved = 0x00
                g_pucTypeCTcpmPdDataObj_EXINT[4] = 0x00;
                g_pucTypeCTcpmPdDataObj_EXINT[5] = 0x00;

                // [15:9] Reserved, [8] HPD IRQ : No
                g_pucTypeCTcpmPdDataObj_EXINT[6] = 0x00;

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
                {
                    // [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No, [4] Multi-Func,
                    // [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
                    g_pucTypeCTcpmPdDataObj_EXINT[7] = (0x0A) | (GET_TCPM_PD_DPAM_MULTI_FUNC(ucPortIndex) << 4);

                    // If (HPD Count != 0) & (Not Attn Wait), Get Status from HPD Queue; else Use Current Status
                    if((GET_TCPM_PD_HPD_CNT(ucPortIndex) > 0) && (GET_TCPM_PD_DPAM_ATTENTION_WAIT(ucPortIndex) == _FALSE))
                    {
                        // Check "HPD High/Low" and "HPD Status" from HPD Queue
                        if(GET_TCPM_PD_HPD_QUEUE(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)) != _PD_HPD_LOW)
                        {
                            g_pucTypeCTcpmPdDataObj_EXINT[7] = g_pucTypeCTcpmPdDataObj_EXINT[7] | (_BIT7);

                            if(GET_TCPM_PD_HPD_QUEUE(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)) == _PD_HPD_IRQ)
                            {
                                g_pucTypeCTcpmPdDataObj_EXINT[6] = g_pucTypeCTcpmPdDataObj_EXINT[6] | (_BIT0);
                            }
                        }
                    }
                    else
                    {
                        // "HPD Count = 0" or "During Attn Wait" (May Cause By DP Source Update Info During Alt Mode), Use Current HPD Status
                        g_pucTypeCTcpmPdDataObj_EXINT[7] = g_pucTypeCTcpmPdDataObj_EXINT[7] | (GET_TCPM_PD_HPD_STATUS(ucPortIndex) << 7);
                    }
                }
#endif // End of #if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
                if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
                {
                    // [7] HPD State : LOW, [6] Exit DP : No, [5] USB Config = No, [4] Multi-Func,
                    // [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_TX(b'01)
                    g_pucTypeCTcpmPdDataObj_EXINT[7] = (0x09) | (GET_TCPM_PD_DPAM_MULTI_FUNC(ucPortIndex) << 4);
                }
#endif  // End of #if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)

                break;

            case _PD_VDM_DP_CMD_ENTER_MODE_ACK:
            case _PD_VDM_DP_CMD_EXIT_MODE_ACK:
            case _PD_VDM_DP_CMD_DP_CONFIG_ACK:
            case _PD_VDM_DP_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_DP_CMD_ENTER_MODE_NAK:
            case _PD_VDM_DP_CMD_EXIT_MODE_NAK:
            case _PD_VDM_DP_CMD_DP_STATUS_NAK:
            case _PD_VDM_DP_CMD_DP_CONFIG_NAK:
            case _PD_VDM_DP_CMD_DISCOVER_MODE_BUSY:
            case _PD_VDM_DP_CMD_ENTER_MODE_BUSY:
            case _PD_VDM_DP_CMD_EXIT_MODE_BUSY:
            case _PD_VDM_DP_CMD_DP_STATUS_BUSY:
            case _PD_VDM_DP_CMD_DP_CONFIG_BUSY:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucTypeCTcpmPdDataObj_EXINT[0] = GET_TCPM_PD_RCV_VDM_SVID_H(ucPortIndex);
                g_pucTypeCTcpmPdDataObj_EXINT[1] = GET_TCPM_PD_RCV_VDM_SVID_L(ucPortIndex);

                // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
                g_pucTypeCTcpmPdDataObj_EXINT[2] = (_BIT7) | (GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex));

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
                {
                    g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD
                g_pucTypeCTcpmPdDataObj_EXINT[3] = enumVdmDpCmd;

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
    else
    {
        // -------- Data Obj 0 : VDM Header --------
        // [31:16] SVID
        g_pucTypeCTcpmPdDataObj_EXINT[0] = GET_TCPM_PD_RCV_VDM_SVID_H(ucPortIndex);
        g_pucTypeCTcpmPdDataObj_EXINT[1] = GET_TCPM_PD_RCV_VDM_SVID_L(ucPortIndex);

        // [15] Struct. VDM = 1, [14:13] VDM Ver, [12:11] Rsv., [10:8] Obj. Pos
        g_pucTypeCTcpmPdDataObj_EXINT[2] = (_BIT7) | (GET_TCPM_PD_RCV_VDM_OBJ_POS(ucPortIndex));

        // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
        if(GET_TCPM_PD_SPEC_VER(ucPortIndex) == _PD_VERSION_3_0)
        {
            g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT5);

            // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
            if(GET_TCPM_PD_PARTNER_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1)
            {
                // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                g_pucTypeCTcpmPdDataObj_EXINT[2] = g_pucTypeCTcpmPdDataObj_EXINT[2] | (_BIT3);
            }
        }

        // [7:0] VDM CMD
        g_pucTypeCTcpmPdDataObj_EXINT[3] = enumVdmCmd;
    }
}

//--------------------------------------------------
// Description  : According to the PD Version, Set Product Type VDO Differently
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSetProductTypeVDO_EXINT0(BYTE ucPortIndex)
{
    BYTE ucIndex = 0;

    switch(GET_TCPM_PD_SPEC_VER(ucPortIndex))
    {
        case _PD_VERSION_3_0:

            // PD Version = 3.0, Products with USB Hub IC, Product Type UFP choose Hub , Product Type DFP choose Undefined;
            // Products without USB Hub IC, Product Type UFP choose Peripheral, Product Type DFP choose Undefined.

            // -------- Data Obj 1 : ID Header ---------
            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // |Host|Dev.|      UFP     |Mode|   DFP   |

            if((GET_TCPM_USB_ROLE(ucPortIndex) == _TYPE_C_USB_HOST_ONLY) || (GET_TCPM_USB_ROLE(ucPortIndex) == _TYPE_C_USB_HOST_DEVICE))
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT7);
            }

            if((GET_TCPM_USB_ROLE(ucPortIndex) == _TYPE_C_USB_DEVICE_ONLY) || (GET_TCPM_USB_ROLE(ucPortIndex) == _TYPE_C_USB_HOST_DEVICE) || (GET_TCPM_USB_SPEED(ucPortIndex) == _USB_BILLBOARD_ONLY))
            {
                // Support USB Device
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT6);
            }

            // UFP Product Type = 3b'000 Undefined/ 3b'001 PDUSB Hub/ 3b'010 PDUSB Peripheral
            if(GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] & (~(_BIT5 | _BIT4 | _BIT3));
            }
            else if(GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_UFP_PRODUCT_TYPE_HUB)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT3);
            }
            else if(GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT4);
            }

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
            if(GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _ON)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT2);
            }
#endif

            // [25:23] DFP Product Type = 3b'000 Undefined/ 3b'001 PDUSB Hub/ 3b'010 PDUSB Host/ 3b'011 Power Brick
            if(GET_TCPM_PD_DFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] & (~(_BIT1 | _BIT0));
                g_pucTypeCTcpmPdDataObj_EXINT[5] = g_pucTypeCTcpmPdDataObj_EXINT[5] & (~(_BIT7));
            }
            else if(GET_TCPM_PD_DFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_DFP_PRODUCT_TYPE_HUB)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[5] = g_pucTypeCTcpmPdDataObj_EXINT[5] | (_BIT7);
            }
            else if(GET_TCPM_PD_DFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_DFP_PRODUCT_TYPE_HOST)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT0);
            }
            else if(GET_TCPM_PD_DFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_DFP_PRODUCT_TYPE_BRICK)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT0);
                g_pucTypeCTcpmPdDataObj_EXINT[5] = g_pucTypeCTcpmPdDataObj_EXINT[5] | (_BIT7);
            }


            if(GET_TCPM_CONNECTOR_TYPE(ucPortIndex) == _TYPE_C_PORT_PLUG)
            {
                // [22:21] = Connector Type: USB Type-C Plug = 2b'11
                g_pucTypeCTcpmPdDataObj_EXINT[5] = g_pucTypeCTcpmPdDataObj_EXINT[5] | (_BIT6 | _BIT5);
            }
            else
            {
                // [22:21] = Connector Type: USB Type-C Receptacle = 2b'10
                g_pucTypeCTcpmPdDataObj_EXINT[5] = g_pucTypeCTcpmPdDataObj_EXINT[5] | (_BIT6);
            }


            g_pucTypeCTcpmPdDataObj_EXINT[5] = g_pucTypeCTcpmPdDataObj_EXINT[5] | (_BIT6);

            // [15:0] = USB Vender ID 0x0BDA (RealTek)
            g_pucTypeCTcpmPdDataObj_EXINT[6] = _USB_VENDOR_ID_H;
            g_pucTypeCTcpmPdDataObj_EXINT[7] = _USB_VENDOR_ID_L;

            // -------- Data Obj 2 : Cert State (XID)
            g_pucTypeCTcpmPdDataObj_EXINT[8] = _USB_XID_BYTE3;
            g_pucTypeCTcpmPdDataObj_EXINT[9] = _USB_XID_BYTE2;
            g_pucTypeCTcpmPdDataObj_EXINT[10] = _USB_XID_BYTE1;
            g_pucTypeCTcpmPdDataObj_EXINT[11] = _USB_XID_BYTE0;

            // -------- Data Obj 3 : Product -----------
            // [31:16] bcd Device = 0x0300, [15:0] Product ID = _USB_PRODUCT_ID_H / _USB_PRODUCT_ID_L
            g_pucTypeCTcpmPdDataObj_EXINT[12] = _USB_PRODUCT_ID_H;
            g_pucTypeCTcpmPdDataObj_EXINT[13] = _USB_PRODUCT_ID_L;
            g_pucTypeCTcpmPdDataObj_EXINT[14] = 0x03;
            g_pucTypeCTcpmPdDataObj_EXINT[15] = 0x00;

            // If (UFP Product Type != Undefined) && (DFP Product Type == Undefined), Product Type VDO [UFP | Pad | Pad].
            // If (UFP Product Type == Undefined) && (DFP Product Type != Undefined), Product Type VDO [DFP | Pad | Pad].
            // If (UFP Product Type != Undefined) && (DFP Product Type != Undefined), Product Type VDO [UFP | Pad | DFP].
            ucIndex = 15;

            if((GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_UFP_PRODUCT_TYPE_HUB) || (GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL))
            {
                // -------- Data Obj 4 : UFP VDO ---------
                // [31:29] UFP VDO Ver. : Ver. 1.2 = 3b'010
                g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] | (_BIT6);

                // [27:24] Device Cap.
                if((GET_TCPM_USB_SPEED(ucPortIndex) == _USB_3_GEN1) || (GET_TCPM_USB_SPEED(ucPortIndex) == _USB_3_GEN2))
                {
                    // USB3.2/ USB2.0 = 4b'0101
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] | (_BIT2 | _BIT0);
                }
                else if(GET_TCPM_USB_SPEED(ucPortIndex) == _USB_BILLBOARD_ONLY)
                {
                    // USB2.0 (Billboard only) = 4b'0010
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] | (_BIT1);
                }
                else if(GET_TCPM_USB_SPEED(ucPortIndex) == _USB_2)
                {
                    // USB2.0 = 4b'0001
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] | (_BIT0);
                }

                // [23:22] Connector Type (Legacy) : Shall be set to 10b, [21:16] Reserved = 0x00
                g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 2] = 0x80;

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
                if(GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _ON)
                {
                    // [15:11] Reserved = 0x00, [10:8] Vconn Power
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 3] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 3] | (_VCONN_POW);

#if(_VCONN_REQUIRE == _TRUE)
                    // [7] Vconn Required
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] | (_BIT7);
#endif

                    if(GET_TCPM_PD_SNK_CAP_CUR(ucPortIndex, 0) != 0x00)
                    {
                        // [6] Vbus Required = TRUE when 1st 5V Sink Cap Need More than 0mA
                        g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] | (_BIT6);
                    }

                    // [5:3] Alternate Modes;
#if(_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE)
                    // [5] Supports Alternate Modes that do not Reconfigure the Signals on the [USB Type-C 2.0] Connector
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] | (_BIT5);
#endif

                    // [4] Supports Alternate Modes that Reconfigure the Signals on the [USB Type-C 2.0] Connector
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] | (_BIT4);

                    // [3] Supports TBT3 Alternate Mode (Need to Add in the Future)
                }
#endif // End of #if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)

                // [2:0] USB Highest Speed
                if(GET_TCPM_USB_SPEED(ucPortIndex) == _USB_3_GEN2)
                {
                    // USB3.2 Gen2 = 3b'010
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] | (_BIT1);
                }
                else if(GET_TCPM_USB_SPEED(ucPortIndex) == _USB_3_GEN1)
                {
                    // USB3.2 Gen1 = 3b'001
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] | (_BIT0);
                }
                else if(GET_TCPM_USB_SPEED(ucPortIndex) == _USB_2)
                {
                    // USB2.0 = 3b'000
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] | (0x00);
                }

                ucIndex = ucIndex + 8;
            }

            if(GET_TCPM_PD_DFP_PRODUCT_TYPE(ucPortIndex) != _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED)
            {
                // -------- Data Obj 6 : DFP VDO ---------
                // [31:29] DFP VDO Ver. : Ver. 1.2 = 3b'010
                g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] | (_BIT6);

                // [26:24] Host Cap.

                if((GET_TCPM_USB_SPEED(ucPortIndex) == _USB_3_GEN1) || (GET_TCPM_USB_SPEED(ucPortIndex) == _USB_3_GEN2))
                {
                    // USB3.2/ USB2.0 = 3b'011
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] | (_BIT1 | _BIT0);
                }
                else if(GET_TCPM_USB_SPEED(ucPortIndex) == _USB_2)
                {
                    // USB2.0 = 3b'001
                    g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 1] | (_BIT0);
                }

                // [23:22] Connector Type (Legacy) : Shall be set to 00b
                g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 2] = 0x00;

                // [4:0] Port Number: Port 0 = 5b'00001
                g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] = g_pucTypeCTcpmPdDataObj_EXINT[ucIndex + 4] | (_BIT0);
            }

            break;

        case _PD_VERSION_2_0:
        default:

            // PD Version = 2.0, Products with USB Hub IC, Product Type UFP choose Hub;
            // Products without USB Hub IC, Product Type UFP choose Peripheral.

            // -------- Data Obj 1 : ID Header ---------
            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // |Host|Dev.|      UFP     |Mode|   DFP   |

            if((GET_TCPM_USB_ROLE(ucPortIndex) == _TYPE_C_USB_HOST_ONLY) || (GET_TCPM_USB_ROLE(ucPortIndex) == _TYPE_C_USB_HOST_DEVICE))
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT7);
            }

            if((GET_TCPM_USB_ROLE(ucPortIndex) == _TYPE_C_USB_DEVICE_ONLY) || (GET_TCPM_USB_ROLE(ucPortIndex) == _TYPE_C_USB_HOST_DEVICE) || (GET_TCPM_USB_SPEED(ucPortIndex) == _USB_BILLBOARD_ONLY))
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT6);
            }

#if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)
            // For the PD2.0 version, Discover_ID_ACK Responds to AMA
            // (UFP Product Type = AMA) does not Meet the Latest Standard. This setting is for Compatibility.
            // UFP Product Type = 3b'101 (AMA)
            g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT5 | _BIT3);
#else
            // UFP Product Type = 3b'000 Undefined/ 3b'001 PDUSB Hub/ 3b'010 PDUSB Peripheral
            if(GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] & (~(_BIT5 | _BIT4 | _BIT3));
            }
            else if(GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_UFP_PRODUCT_TYPE_HUB)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT3);
            }
            else if(GET_TCPM_PD_UFP_PRODUCT_TYPE(ucPortIndex) == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT4);
            }
#endif

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
            if(GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _ON)
            {
                g_pucTypeCTcpmPdDataObj_EXINT[4] = g_pucTypeCTcpmPdDataObj_EXINT[4] | (_BIT2);
            }
#endif

            // [15:0] = USB Vender ID 0x0BDA (RealTek)
            g_pucTypeCTcpmPdDataObj_EXINT[6] = _USB_VENDOR_ID_H;
            g_pucTypeCTcpmPdDataObj_EXINT[7] = _USB_VENDOR_ID_L;

            // -------- Data Obj 2 : Cert State (XID)
            g_pucTypeCTcpmPdDataObj_EXINT[8] = _USB_XID_BYTE3;
            g_pucTypeCTcpmPdDataObj_EXINT[9] = _USB_XID_BYTE2;
            g_pucTypeCTcpmPdDataObj_EXINT[10] = _USB_XID_BYTE1;
            g_pucTypeCTcpmPdDataObj_EXINT[11] = _USB_XID_BYTE0;

            // -------- Data Obj 3 : Product -----------
            // [31:16] bcd Device = 0x0300, [15:0] Product ID = _USB_PRODUCT_ID_H / _USB_PRODUCT_ID_L
            g_pucTypeCTcpmPdDataObj_EXINT[12] = _USB_PRODUCT_ID_H;
            g_pucTypeCTcpmPdDataObj_EXINT[13] = _USB_PRODUCT_ID_L;
            g_pucTypeCTcpmPdDataObj_EXINT[14] = 0x03;
            g_pucTypeCTcpmPdDataObj_EXINT[15] = 0x00;

#if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)
            // -------- Data Obj 4 : Alt. Mode ---------
            // [31:28] HW Ver. = 0, [27:24] FW Ver. = 0
            g_pucTypeCTcpmPdDataObj_EXINT[16] = g_pucTypeCTcpmPdDataObj_EXINT[16] | (_PD_HW_VERSION << 4);
            g_pucTypeCTcpmPdDataObj_EXINT[16] = g_pucTypeCTcpmPdDataObj_EXINT[16] | (_PD_FW_VERSION);

            // [23:16] Reserved = 0x00
            g_pucTypeCTcpmPdDataObj_EXINT[17] = 0x00;

            // [15:8] Reserved = 0x00
            g_pucTypeCTcpmPdDataObj_EXINT[18] = 0x00;

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
            if(GET_TCPM_PD_MODAL_OPERATION_SUPPORT(ucPortIndex) == _ON)
            {
                // [7:5] Vconn Power
                g_pucTypeCTcpmPdDataObj_EXINT[19] = g_pucTypeCTcpmPdDataObj_EXINT[19] | (_VCONN_POW << 5);

#if(_VCONN_REQUIRE == _TRUE)
                // [4] Vconn Required
                g_pucTypeCTcpmPdDataObj_EXINT[19] = g_pucTypeCTcpmPdDataObj_EXINT[19] | (_BIT4);
#endif

                if(GET_TCPM_PD_SNK_CAP_CUR(ucPortIndex, 0) != 0x00)
                {
                    // [3] Vbus Required = TRUE when 1st 5V Sink Cap Need More than 0mA
                    g_pucTypeCTcpmPdDataObj_EXINT[19] = g_pucTypeCTcpmPdDataObj_EXINT[19] | (_BIT3);
                }
            }
#endif // End of #if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)

            // [2:0] USB Highest Speed
            if(GET_TCPM_USB_ROLE(ucPortIndex) == _USB_BILLBOARD_ONLY)
            {
                // Billboard only = 3b'011
                g_pucTypeCTcpmPdDataObj_EXINT[19] = g_pucTypeCTcpmPdDataObj_EXINT[19] | (_BIT1 | _BIT0);
            }
            else if(GET_TCPM_USB_ROLE(ucPortIndex) == _USB_3_GEN2)
            {
                // USB3.2 Gen2 = 3b'010
                g_pucTypeCTcpmPdDataObj_EXINT[19] = g_pucTypeCTcpmPdDataObj_EXINT[19] | (_BIT1);
            }
            else if(GET_TCPM_USB_ROLE(ucPortIndex) == _USB_3_GEN1)
            {
                // USB3.2 Gen1 = 3b'001
                g_pucTypeCTcpmPdDataObj_EXINT[19] = g_pucTypeCTcpmPdDataObj_EXINT[19] | (_BIT0);
            }
            else if(GET_TCPM_USB_ROLE(ucPortIndex) == _USB_2)
            {
                // USB2.0 = 3b'000
                g_pucTypeCTcpmPdDataObj_EXINT[19] = g_pucTypeCTcpmPdDataObj_EXINT[19] | (0x00);
            }

#endif // End of #if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)
            break;
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Send PD  Soft Reset Message
// Input Value  : ucPortIndex, enumPacketType
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSendSoftRst_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType)
{
    BYTE ucTransmitInfo = 0x00;

    // 1. Clear and Enable Tx_SUCCESS + Tx_FAIL + Tx_DISCARD
    ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, ((WORD)(_TCPM_TCPCI_ALERT_TX_FAIL | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_TX_SUCCESS)), _ENABLE);

    // 2. Construct Message and Write Data to Tx Buffer [0x51~]
    ScalerTypeCTcpmPdConstructSoftRst_EXINT0(ucPortIndex, enumPacketType);

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

    ScalerTypeCTcpmTcpciSetTransmit_EXINT0(ucPortIndex, ucTransmitInfo);
}

//--------------------------------------------------
// Description  : Type C TCPM Construct PD Soft Reset Message
// Input Value  : ucPortIndex, enumPacketType
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdConstructSoftRst_EXINT0(BYTE ucPortIndex, EnumTypeCPDPacketType enumPacketType)
{
    WORD usMsgHeader_EXINT = 0;

    // 1. Construct Soft Reset Message Header
    // [15] Extended, [14:12] Num of Data Obj., [4:0] Command = _PD_CMD_SOFT_RESET
    usMsgHeader_EXINT = (_PD_CMD_SOFT_RESET & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    if(enumPacketType == _PD_SOP_PKT)
    {
        // Reset Message ID
        CLR_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex);
        CLR_TCPM_PD_RX_MSG_ID_SOP(ucPortIndex);

        // [11:9] Message ID, [8] Power Role, [7:6] Spec Ver, [5] Data Role
        usMsgHeader_EXINT = (usMsgHeader_EXINT | (GET_TCPM_PD_TX_MSG_ID_SOP(ucPortIndex) << 9) | (GET_TCPM_POWER_ROLE(ucPortIndex) << 8) | (GET_TCPM_PD_SPEC_VER(ucPortIndex) << 6) | (GET_TCPM_DATA_ROLE(ucPortIndex) << 5));
    }
    else if(enumPacketType == _PD_SOP_P_PKT)
    {
        // Reset Message ID
        CLR_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex);
        CLR_TCPM_PD_RX_MSG_ID_SOP_P(ucPortIndex);

        // [11:9] Message ID, [8] Cable Plug : Device(1), [7:6] Spec Ver, [5] Rsv.
        usMsgHeader_EXINT = (usMsgHeader_EXINT | (GET_TCPM_PD_TX_MSG_ID_SOP_P(ucPortIndex) << 9) | (_BIT8) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }
    else if(enumPacketType == _PD_SOP_PP_PKT)
    {
        // Reset Message ID
        CLR_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex);
        CLR_TCPM_PD_RX_MSG_ID_SOP_PP(ucPortIndex);

        // [11:9] Message ID, [8] Cable Plug, [7:6] Spec Ver, [5] Rsv.
        usMsgHeader_EXINT = (usMsgHeader_EXINT | (GET_TCPM_PD_TX_MSG_ID_SOP_PP(ucPortIndex) << 9) | (_BIT8) | (GET_TCPM_PD_CBL_SPEC_VER(ucPortIndex) << 6));
    }

    // 4. Write Message to TCPC Tx Buffer (Port, Cmd = Soft Reset, TxByteCnt = 2(Message Header), Message Header)
    ScalerTypeCTcpmTcpciSetTxBuffer_EXINT0(ucPortIndex, _PD_CMD_SOFT_RESET, 2, usMsgHeader_EXINT);
}

//--------------------------------------------------
// Description  : Type C TCPM Send PD Hard Reset Message
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSendHardRst_EXINT0(BYTE ucPortIndex)
{
    if(GET_TCPM_PD_HARD_RST_CNT(ucPortIndex) <= _MAX_HARD_RST_CNT)
    {
        ADD_TCPM_PD_HARD_RST_CNT(ucPortIndex);

        // Disable Tx Discard, Rx, Sink Disconnect (TCPC Will Set TX_Success + TX_Fail After Sending HRST)
        ScalerTypeCTcpmAlertControl_EXINT0(ucPortIndex, (WORD)(_TCPM_TCPCI_ALERT_RX_RCV_SOP | _TCPM_TCPCI_ALERT_RX_HRST | _TCPM_TCPCI_ALERT_TX_DISCARD | _TCPM_TCPCI_ALERT_RX_OVERFLOW | _TCPM_TCPCI_ALERT_SNK_DISC), _DISABLE);

        // TRANSMIT [0x50] [5:4] Retry Counter (00b), [2:0] SOP Type : 101b (HRST)
        ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_TRANSMIT, 0x05);

        // Process Hard Reset
        ScalerTypeCTcpmPdProcHardRst_EXINT0(ucPortIndex);
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
void ScalerTypeCTcpmPdProcHardRst_EXINT0(BYTE ucPortIndex)
{
    // Clear Hard Reset Turn Off Power Flag (Set When 1.Power Already Turned Off to vSafe0v for SRC 2.Vbus Already Not vSafe5v)
    CLR_TCPM_PD_HRST_PWR_OFF(ucPortIndex);

    if(GET_TCPM_POWER_ROLE(ucPortIndex) == _PD_POWER_SRC)
    {
        // Source can Start Changing Power After tSrcTransition = 25-35 ms (Vbus + Vconn)
        ScalerTypeCTcpmWDActiveTimerEvent_EXINT0(ucPortIndex, _SRC_ADJUST_POWER_TIMER, _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER);
    }
    else
    {
        // 1. Turn Off Power Draw, Vbus should be drive to vSafe0V by Source (PD 7.1.5).
        ScalerTypeCTcpmVbusCtrl_EXINT0(ucPortIndex, _OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);

        // 2. Turn Off Type-C Unattach Vbus Detection
        // (On-Semi) "DO NOT" Turn Off Vbus Detection, It Will Cause Unattach Immediately
        if(GET_TCPM_TCPC_TYPE(ucPortIndex) != _TCPC_ON_SEMI)
        {
            ScalerTypeCTcpmVbusDetCtrl_EXINT0(ucPortIndex, _DISABLE);
        }

        // 3. Active Wait 3sec for Source to Complete Hard Reset (MM1AE-2705), Canceled when Hard Reset Complete (PD Reset)
        ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, _SNK_HARD_RST_TIMER, _SCALER_TIMER_EVENT_TCPM_SNK_HARD_RST_TIMEOUT);
    }

    // Turn Off Vconn, If Already Turned On
    if(GET_TCPM_VCONN_ROLE(ucPortIndex) == _PD_VCONN_SRC)
    {
        ScalerTypeCTcpmVconnCtrl_EXINT0(ucPortIndex, _OFF);
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
void ScalerTypeCTcpmPdUpdateGoodCRCInfo_EXINT0(BYTE ucPortIndex)
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
    ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_MSG_HEADER_INFO, ucMsgHeaderInfo);
}

//--------------------------------------------------
// Description  : Cancel All Timer Events When CC Unattach
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdUnattachCancelTimerEvent_EXINT0(BYTE ucPortIndex)
{
    CLR_TCPM_PD_TIMER_EVENT_VALID(ucPortIndex);

    // Cancel Timer Event
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SNK_HARD_RST_TIMEOUT);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_REQ_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_PARTNER_ALT_SUPPORT);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_T480_ERROR_RECOVERY);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_VDM_RESP_CONFLICT_TIMEOUT);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_ATTENTION_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_GET_SNK_CAP_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_S8_HRST);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_SEND_HARD_RST);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_TPC_ERROR_RECOVERY);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_PRS_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_DRS_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_VCS_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_VDMMSG_WAIT);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_CLR_VDM_BUSY_FLAG);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_DFP_START_ALT_MODE);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_PPS_TIMEOUT);
#endif
#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK);
#endif
#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_PMIC_TRACKING);
    ScalerTypeCTcpmCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_TIMER_EVENT_TCPM_PMIC_POLLING_OCP);
#endif

    SET_TCPM_WD_TIME_LEFT(ucPortIndex, 0);
    CLR_TCPM_WD_EVENT_TRIGGERED(ucPortIndex);

    // Cancel WD Timer Event
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_SRC_CAP);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_PS_TRANSITION_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_REQUEST);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SNK_SWITCH_TO_SRC);
    ScalerTypeCTcpmWDCancelTimerEvent_EXINT0(ucPortIndex, _SCALER_WD_TIMER_EVENT_TCPM_SEND_VCONN_ON_PSRDY);
}

//--------------------------------------------------
// Description  : Record Cable Info Of Discover ID Ack
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSaveCableDiscoverIdAckInfo_EXINT0(BYTE ucPortIndex)
{
    // Update Cable SVDM Version [14:13] Major = b'01 (2.x), [12:11] Minor = b'00(2.0), b'01 (2.1)
    if((GET_TCPM_PD_CBL_SVDM_VERSION(ucPortIndex) >= _PD_SVDM_VER_2_1) && ((g_pucTypeCTcpmPdDataObj_EXINT[2] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) <= (_BIT5)))
    {
        // if((Current SVDM >= 2.1) & (Rcv SVDM <= 2.0)), Downgrade to SVDM 2.0 Earlier
        SET_TCPM_PD_CBL_SVDM_VERSION(ucPortIndex, _PD_SVDM_VER_2_0_EARLIER);
    }

    // ID Header VDO, Bit[29:27] SOP' Product Type(Passive Cable / Active Cable / VPD)
    if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT5 | _BIT4 | _BIT3)) == (_BIT4 | _BIT3))
    {
        SET_TCPM_PD_CBL_PRODUCT_TYPE(ucPortIndex, _PD_PASSIVE_CABLE);

        // DPAM v2.1: Store Cable Info For DPCD Table(02217h For DPRX / 00110h For DPTX), When Not In DPAM, Discover Identity Takes Priority
        SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_PASSIVE);
    }
    else if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT5 | _BIT4 | _BIT3)) == _BIT5)
    {
        SET_TCPM_PD_CBL_PRODUCT_TYPE(ucPortIndex, _PD_ACTIVE_CABLE);
    }
    else if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4))
    {
        SET_TCPM_PD_CBL_PRODUCT_TYPE(ucPortIndex, _PD_VCONN_POWERED_USB_DEVICE);
    }

    // Bit[26] Modal Operation Support: Y/N
    if((g_pucTypeCTcpmPdDataObj_EXINT[4] & _BIT2) == _BIT2)
    {
        SET_TCPM_PD_CBL_MODAL_OPERATION_SUPPORT(ucPortIndex);
    }

    // Bit[22:21] Connector Type(TypeC Receptacle / TypeC Plug)
    if((g_pucTypeCTcpmPdDataObj_EXINT[5] & (_BIT6 | _BIT5)) == _BIT6)
    {
        SET_TCPM_PD_CBL_CONNECTOR_TYPE(ucPortIndex, _PD_CABLE_TYPEC_RECEPTACLE);
    }
    else if((g_pucTypeCTcpmPdDataObj_EXINT[5] & (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
    {
        SET_TCPM_PD_CBL_CONNECTOR_TYPE(ucPortIndex, _PD_CABLE_TYPEC_PLUG);
    }

    // Passive Cable VDO
    if(GET_TCPM_PD_CBL_PRODUCT_TYPE(ucPortIndex) == _PD_PASSIVE_CABLE)
    {
        // Bit[17] EPR Mode Capable
        if((g_pucTypeCTcpmPdDataObj_EXINT[17] & _BIT1) == _BIT1)
        {
            SET_TCPM_PD_CBL_EPR_MODE_CAPABLE(ucPortIndex);
        }
        else
        {
            CLR_TCPM_PD_CBL_EPR_MODE_CAPABLE(ucPortIndex);
        }

        // Bit[12:11] Cable Termination Type
        if((g_pucTypeCTcpmPdDataObj_EXINT[18] & (_BIT4 | _BIT3)) == 0x00)
        {
            CLR_TCPM_PD_CBL_VCONN_REQUIRED(ucPortIndex);
        }

        // Bit[10:9] Max Vbus Voltage
        if((g_pucTypeCTcpmPdDataObj_EXINT[18] & (_BIT2 | _BIT1)) == (_BIT2 | _BIT1))
        {
            // Cable Max Voltage = 50V = 500 * 100mV
            SET_TCPM_PD_CBL_MAX_VOL(ucPortIndex, 500);
        }
        else
        {
            // Cable Max Voltage = 20V = 200 * 100mV
            SET_TCPM_PD_CBL_MAX_VOL(ucPortIndex, 200);
        }

        // Bit[6:5] Cable Max Vbus Current
        if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT6 | _BIT5)) == _BIT5)
        {
            // Cable Max Current = 3.0A = 300 * 10mA
            SET_TCPM_PD_CBL_MAX_CUR(ucPortIndex, 300);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT6 | _BIT5)) == _BIT6)
        {
            SET_TCPM_PD_CBL_MAX_CUR(ucPortIndex, 500);
        }

        // Bit[2:0] Cable USB Highest Speed
        if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == 0x00)
        {
            SET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex, _PD_CBL_USB_2_ONLY);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
        {
            SET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex, _PD_CBL_USB_3_GEN1);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
        {
            SET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex, _PD_CBL_USB_3OR4_GEN2);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            SET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex, _PD_CBL_USB_4_GEN3);
        }
    }
    else if(GET_TCPM_PD_CBL_PRODUCT_TYPE(ucPortIndex) == _PD_ACTIVE_CABLE)
    {
        // Active Cable VDO1
        // Bit[17] EPR Mode Capable
        if((g_pucTypeCTcpmPdDataObj_EXINT[17] & _BIT1) == _BIT1)
        {
            SET_TCPM_PD_CBL_EPR_MODE_CAPABLE(ucPortIndex);
        }
        else
        {
            CLR_TCPM_PD_CBL_EPR_MODE_CAPABLE(ucPortIndex);
        }

        // Bit[12:11] Cable Termination Type
        if((g_pucTypeCTcpmPdDataObj_EXINT[18] & (_BIT4 | _BIT3)) == _BIT4)
        {
            SET_TCPM_PD_CBL_TERMINATION_TYPE(ucPortIndex, _PD_CBL_ONE_ACTIVE_ONE_PASSIVE);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[18] & (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
        {
            SET_TCPM_PD_CBL_TERMINATION_TYPE(ucPortIndex, _PD_CBL_BOTH_END_ACTIVE);
        }

        // Bit[10:9] Max Vbus Voltage
        if((g_pucTypeCTcpmPdDataObj_EXINT[18] & (_BIT2 | _BIT1)) == (_BIT2 | _BIT1))
        {
            // Cable Max Voltage = 50V = 500 * 100mV
            SET_TCPM_PD_CBL_MAX_VOL(ucPortIndex, 500);
        }
        else
        {
            // Cable Max Voltage = 20V = 200 * 100mV
            SET_TCPM_PD_CBL_MAX_VOL(ucPortIndex, 200);
        }

        // Bit[8] SBU Supported :Y/N
        if((g_pucTypeCTcpmPdDataObj_EXINT[18] & _BIT0) == 0x00)
        {
            SET_TCPM_PD_CBL_SBU_SUPPORT(ucPortIndex);
        }

        // If Bit[8] == 0, set Bit[7]: SBU Type, otherwise ignore Bit[7]
        if(GET_TCPM_PD_CBL_SBU_SUPPORT(ucPortIndex) == _TRUE)
        {
            if((g_pucTypeCTcpmPdDataObj_EXINT[19] & _BIT7) == 0x00)
            {
                SET_TCPM_PD_CBL_SBU_TYPE(ucPortIndex, _PD_CBL_SBU_PASSIVE);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[19] & _BIT7) == _BIT7)
            {
                SET_TCPM_PD_CBL_SBU_TYPE(ucPortIndex, _PD_CBL_SBU_ACTIVE);
            }
        }

        // Bit[4] Vbus Through Cable: Y/N.
        if((g_pucTypeCTcpmPdDataObj_EXINT[19] & _BIT4) == _BIT4)
        {
            SET_TCPM_PD_CBL_VBUS_THROUGH(ucPortIndex);
        }

        // Bit[3] SOP'' Controller Present : Y/N
        if((g_pucTypeCTcpmPdDataObj_EXINT[19] & _BIT3) == _BIT3)
        {
            SET_TCPM_PD_CBL_SOP_PP_SUPPORT(ucPortIndex);
        }

        // Bit[2:0] Cable USB Highest Speed
        if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == 0x00)
        {
            SET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex, _PD_CBL_USB_2_ONLY);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
        {
            SET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex, _PD_CBL_USB_3_GEN1);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
        {
            SET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex, _PD_CBL_USB_3OR4_GEN2);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            SET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex, _PD_CBL_USB_4_GEN3);
        }

        // Active Cable VDO2
        // Bit[11] U3 to U0 Transition Mode
        if((g_pucTypeCTcpmPdDataObj_EXINT[22] & _BIT3) == 0x00)
        {
            SET_TCPM_PD_CBL_U3_TO_U0_TRANSITION_MODE(ucPortIndex, _PD_CBL_U3_TO_U0_DIRECT);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[22] & _BIT3) == _BIT3)
        {
            SET_TCPM_PD_CBL_U3_TO_U0_TRANSITION_MODE(ucPortIndex, _PD_CBL_U3_TO_U0_THROUGH_U3S);
        }

        // Bit[9] Active Element
        if((g_pucTypeCTcpmPdDataObj_EXINT[22] & _BIT1) == 0x00)
        {
            // Store Cable Info For DPCD Table(02217h For DPRX / 00110h For DPTX), When Not In DPAM, Discover Identity Takes Priority
            SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_ACTIVE_REDRIVER);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[22] & _BIT1) == _BIT1)
        {
            // Store Cable Info For DPCD Table(02217h For DPRX / 00110h For DPTX), When Not In DPAM, Discover Identity Takes Priority
            SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_ACTIVE_RETIMER);
        }

        // Bit[8] USB4 Support: Y/N
        if((g_pucTypeCTcpmPdDataObj_EXINT[22] & _BIT0) == _BIT0)
        {
            SET_TCPM_PD_CBL_USB_4_SUPPORT(ucPortIndex);
        }

        // Bit[4] USB3.2 Support: Y/N
        if((g_pucTypeCTcpmPdDataObj_EXINT[23] & _BIT4) == _BIT4)
        {
            SET_TCPM_PD_CBL_USB_3_2_SUPPORT(ucPortIndex);
        }

        // Bit[3] USB Lanes Supported: One Lane / Two Lanes
        if((g_pucTypeCTcpmPdDataObj_EXINT[23] & _BIT3) == 0x00)
        {
            SET_TCPM_PD_CBL_LANES_SUPPORT(ucPortIndex, _PD_CBL_ONE_LANE);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[23] & _BIT3) == _BIT3)
        {
            SET_TCPM_PD_CBL_LANES_SUPPORT(ucPortIndex, _PD_CBL_TWO_LANES);
        }

        // If VDO1 Bit[4] == 1, set Bit[6:5]: CBL max Vbus current, otherwise ignore Bit[6:5]
        if(GET_TCPM_PD_CBL_VBUS_THROUGH(ucPortIndex) == _TRUE)
        {
            if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT6 | _BIT5)) == _BIT5)
            {
                // Cable Max Vbus Current = 3.0A = 300 * 10mA
                SET_TCPM_PD_CBL_MAX_CUR(ucPortIndex, 300);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT6 | _BIT5)) == _BIT6)
            {
                SET_TCPM_PD_CBL_MAX_CUR(ucPortIndex, 500);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[19] & (_BIT6 | _BIT5)) == 0x00)
            {
                // PD 3.0 Spec P150: 500mA USB2, 900mA USB3.2 x1, 1.5A USB3.2 x2.
                if(GET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex) == _PD_CBL_USB_2_ONLY)
                {
                    SET_TCPM_PD_CBL_MAX_CUR(ucPortIndex, 50);
                }
                else if((GET_TCPM_PD_CBL_USB_3_2_SUPPORT(ucPortIndex) == _TRUE) && (GET_TCPM_PD_CBL_LANES_SUPPORT(ucPortIndex) == _PD_CBL_ONE_LANE))
                {
                    SET_TCPM_PD_CBL_MAX_CUR(ucPortIndex, 90);
                }
                else if((GET_TCPM_PD_CBL_USB_3_2_SUPPORT(ucPortIndex) == _TRUE) && (GET_TCPM_PD_CBL_LANES_SUPPORT(ucPortIndex) == _PD_CBL_TWO_LANES))
                {
                    SET_TCPM_PD_CBL_MAX_CUR(ucPortIndex, 150);
                }
            }
        }
    }
    else if(GET_TCPM_PD_CBL_PRODUCT_TYPE(ucPortIndex) == _PD_VCONN_POWERED_USB_DEVICE)
    {
        // VPD VDO
        // Bit[16:15] Max Vbus Voltage
        if(((g_pucTypeCTcpmPdDataObj_EXINT[17] & _BIT0) == 0x00) && ((g_pucTypeCTcpmPdDataObj_EXINT[18] & _BIT7) == 0x00))
        {
            // Max Voltage = 20V = 200 * 100mV
            SET_TCPM_PD_CBL_MAX_VOL(ucPortIndex, 200);
        }
        else if(((g_pucTypeCTcpmPdDataObj_EXINT[17] & _BIT0) == 0x00) && ((g_pucTypeCTcpmPdDataObj_EXINT[18] & _BIT7) == _BIT7))
        {
            SET_TCPM_PD_CBL_MAX_VOL(ucPortIndex, 300);
        }
        else if(((g_pucTypeCTcpmPdDataObj_EXINT[17] & _BIT0) == _BIT0) && ((g_pucTypeCTcpmPdDataObj_EXINT[18] & _BIT7) == 0x00))
        {
            SET_TCPM_PD_CBL_MAX_VOL(ucPortIndex, 400);
        }
        else if(((g_pucTypeCTcpmPdDataObj_EXINT[17] & _BIT0) == _BIT0) && ((g_pucTypeCTcpmPdDataObj_EXINT[18] & _BIT7) == _BIT7))
        {
            SET_TCPM_PD_CBL_MAX_VOL(ucPortIndex, 500);
        }

        // Bit[0] Charge Through Support
        if((g_pucTypeCTcpmPdDataObj_EXINT[19] & _BIT0) == _BIT0)
        {
            SET_TCPM_PD_CBL_CHARGE_THROUGH_SUPPORT(ucPortIndex);
        }

        // Bit[14] Charge Through Current Support; if Bit[0] = 1, Set Max Current Macro
        if(GET_TCPM_PD_CBL_CHARGE_THROUGH_SUPPORT(ucPortIndex) == _TRUE)
        {
            if((g_pucTypeCTcpmPdDataObj_EXINT[18] & _BIT6) == 0x00)
            {
                // Charge Through Current = 3.0A = 300 * 10mA
                SET_TCPM_PD_CBL_MAX_CUR(ucPortIndex, 300);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[18] & _BIT6) == _BIT6)
            {
                SET_TCPM_PD_CBL_MAX_CUR(ucPortIndex, 500);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Check if Received Request is Valid
// Input Value  : ucPortIndex
// Output Value : _PD_REQUEST_INVALID / _PD_REQUEST_VALID
//--------------------------------------------------
EnumTypeCPDRequestValid ScalerTypeCTcpmPdCheckRequestValid_EXINT0(BYTE ucPortIndex)
{
    EnumTypeCPDRequestValid enumReqCheckResult = _PD_REQUEST_INVALID_CURRENT;

    SET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex, (g_pucTypeCTcpmPdDataObj_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

    // 1. Check if Object Position is Valid
    if((GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) > 0) && (GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) <= GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex)))
    {
        if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1) == _PD_FIX_SUPPLY_PDO)
        {
            // Get Fix Supply RDO Operating / Max Current (Unit = 10mA)
            SET_TCPM_PD_PARTNER_OP_CUR(ucPortIndex, (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[1] & 0x0F)) << 6) | (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[2] & 0xFC)) >> 2));
            SET_TCPM_PD_PARTNER_MAX_CUR(ucPortIndex, (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[2] & 0x03)) << 8) | ((WORD)g_pucTypeCTcpmPdDataObj_EXINT[3]));

            // 2.1. Check if Requested "Operating Current" <= Src PDO Current / Cable Max Current
            if((GET_TCPM_PD_PARTNER_OP_CUR(ucPortIndex) <= GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1)) &&
               (GET_TCPM_PD_PARTNER_OP_CUR(ucPortIndex) <= GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex)))
            {
                // Record Requested Voltage
                SET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex, GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1));

                // Set OCP Threshlod according to Min(Requested Max Cur, Cable Max Cur)
                if((GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1)) <= GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex))
                {
                    SET_TCPM_OCP_CURRENT(ucPortIndex, (WORD)(((DWORD)(GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1)) * (DWORD)(GET_TCPM_OCP_RATIO(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1))) / 100));
                }
                else
                {
                    SET_TCPM_OCP_CURRENT(ucPortIndex, (WORD)(((DWORD)(GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex)) * (DWORD)(GET_TCPM_OCP_RATIO(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1))) / 100));
                }

                // Clear Small Step Flag to Avoid Using Wrong Timer when Power Transition.
                CLR_TCPM_PD_REQ_PPS_VOL_SMALL_STEP(ucPortIndex);
                CLR_TCPM_PD_REQ_AVS_VOL_SMALL_STEP(ucPortIndex);

                enumReqCheckResult = _PD_REQUEST_VALID;
            }
        }
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
        else if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1) == _PD_3_PROGRAMMABLE_PDO)
        {
            WORD usNewVoltage = 0x00;

            // Get PPS RDO Operating / Max Current (Unit = 50mA)
            SET_TCPM_PD_PARTNER_OP_CUR(ucPortIndex, (WORD)(g_pucTypeCTcpmPdDataObj_EXINT[3] & 0x7F));
            SET_TCPM_PD_PARTNER_MAX_CUR(ucPortIndex, (WORD)(g_pucTypeCTcpmPdDataObj_EXINT[3] & 0x7F));

            // Request PPS Voltage with Unit 20mV and Convert to 10mV
            usNewVoltage = (((((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[1] & 0x0F)) << 7) | (((WORD)(g_pucTypeCTcpmPdDataObj_EXINT[2] & 0xFE)) >> 1)) * 2);

            if(((usNewVoltage >= (WORD)GET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex)) && ((usNewVoltage - (WORD)GET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex)) <= 50)) ||
               ((usNewVoltage < (WORD)GET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex)) && (((WORD)GET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex) - usNewVoltage) <= 50)))
            {
                SET_TCPM_PD_REQ_PPS_VOL_SMALL_STEP(ucPortIndex, _TRUE);
            }
            else
            {
                SET_TCPM_PD_REQ_PPS_VOL_SMALL_STEP(ucPortIndex, _FALSE);
            }

            SET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex, usNewVoltage);

            // 2.2. Check if (Req "Operating Current" <= Source PDO Cur / Cable Max Current) & (Req Voltage is Valid)
            if((GET_TCPM_PD_PARTNER_OP_CUR(ucPortIndex) <= GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1)) &&
               (GET_TCPM_PD_PARTNER_OP_CUR(ucPortIndex) <= (GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex) / 5)) &&
               (GET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex) >= GET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1)) &&
               (GET_TCPM_PD_PARTNER_REQ_VOL(ucPortIndex) <= GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1)))
            {
                // Convert Requested Current From 50mA to 10mA (PPS PDO : Max Current = Operating Current)
                SET_TCPM_PD_PARTNER_OP_CUR(ucPortIndex, GET_TCPM_PD_PARTNER_OP_CUR(ucPortIndex) * 5);
                SET_TCPM_PD_PARTNER_MAX_CUR(ucPortIndex, GET_TCPM_PD_PARTNER_MAX_CUR(ucPortIndex) * 5);

                // Set OCP Threshlod according to Min(PDO Max Cur, Cable Max Cur)
                if((GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1)) <= (GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex) / 5))
                {
                    SET_TCPM_OCP_CURRENT(ucPortIndex, (GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_PARTNER_OBJ_POS(ucPortIndex) - 1)) * 5);
                }
                else
                {
                    SET_TCPM_OCP_CURRENT(ucPortIndex, GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex));
                }

                // Start Timer Event 13.5 Sec, Sink Should Request PPS PDO every 10 sec
                ScalerTypeCTcpmActiveTimerEvent_EXINT0(ucPortIndex, 13500, _SCALER_TIMER_EVENT_TCPM_PPS_TIMEOUT);

                enumReqCheckResult = _PD_REQUEST_VALID;
            }
        }
#endif  // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)

        // For Valid Request, Update Port Partner(Sink) Info
        if(enumReqCheckResult == _PD_REQUEST_VALID)
        {
            SET_TCPM_PD_PARTNER_GIVE_BACK(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 3);
            SET_TCPM_PD_PARTNER_CAP_MIS(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 2);
            SET_TCPM_PD_PARTNER_USB_CAP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[0] >> 1);
            SET_TCPM_PD_PARTNER_SUSPEND(ucPortIndex, ~(g_pucTypeCTcpmPdDataObj_EXINT[0] >> 0));
            SET_TCPM_PD_PARTNER_UNCHK(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[1] >> 7);
            SET_TCPM_PD_PARTNER_EPR_CAP(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[1] >> 6);
        }
    }

    return enumReqCheckResult;
}

//--------------------------------------------------
// Description  : Go Back To Src/Snk Ready State According to Power Role
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdBackToReadyState_EXINT0(BYTE ucPortIndex)
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
            ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_ROLE_CTRL, GET_TCPM_ROLE_CONTROL(ucPortIndex));
        }
    }
    else
    {
        SET_TCPM_PD_FW_STATE(ucPortIndex, _PD_SNK_READY);
        SET_TCPM_PD_SUB_STATE(ucPortIndex, _PD_SUB_SNK_READY);
    }
}

//--------------------------------------------------
// Description  : Check if Received Source Capability is Valid
// Input Value  : ucPortIndex
// Output Value : _PD_SRC_CAP_INVALID/_PD_SRC_CAP_VALID
//--------------------------------------------------
EnumTypeCPDSrcCapValid ScalerTypeCTcpmPdCheckSrcCapValid_EXINT0(BYTE ucPortIndex)
{
    EnumTypeCPDSrcCapValid enumSrcCapCheckResult = _PD_SRC_CAP_INVALID;

    // 1. Check if Object Position is Valid
    if((GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) > 0) && (GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) <= GET_TCPM_PD_PARTNER_SRC_CAP_CNT(ucPortIndex)) && (GET_TCPM_PD_PARTNER_EXT_PWR(ucPortIndex) == _TRUE))
    {
        if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) == _PD_FIX_SUPPLY_PDO)
        {
            // Check if Max Current Provided >= Requested Current
            if(GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) >= GET_TCPM_PD_REQ_INFO_2(ucPortIndex))
            {
                enumSrcCapCheckResult = _PD_SRC_CAP_VALID;
            }
        }
        else if(GET_TCPM_PD_PARTNER_SRC_CAP_TYPE(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) == _PD_3_PROGRAMMABLE_PDO)
        {
            // Check if (Max Current Provided >= Requested Current) & (Source Capability Voltage is Valid)
            if(((GET_TCPM_PD_PARTNER_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) / 5) >= GET_TCPM_PD_REQ_INFO_2(ucPortIndex)) &&
               ((GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MIN(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) / 2) <= GET_TCPM_PD_REQ_INFO_1(ucPortIndex)) &&
               ((GET_TCPM_PD_PARTNER_SRC_CAP_VOL_MAX(ucPortIndex, GET_TCPM_PD_REQ_OBJ_POS(ucPortIndex) - 1) / 2) >= GET_TCPM_PD_REQ_INFO_1(ucPortIndex)))
            {
                enumSrcCapCheckResult = _PD_SRC_CAP_VALID;
            }
        }
    }

    return enumSrcCapCheckResult;
}

//--------------------------------------------------
// Description  : Check if Present Power Contract is still Valid
// Input Value  : ucPortIndex
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCTcpmPdCheckPowerContractValid_EXINT0(BYTE ucPortIndex)
{
    // When Previously Negotiated Voltage and Current are Included in the New Capabilities, Return _TRUE
    if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, GET_TCPM_PD_PDO_STATUS_OBJ_POS(ucPortIndex) - 1) == _PD_FIX_SUPPLY_PDO)
    {
        // New Source Capabilities : _SRC_CAP_VOL_MAX / _SRC_CAP_CUR (Unit : 10mV / 10mA)
        // Previously Negotiated Voltage and Current : _PDO_STATUS_VOL / _PDO_STATUS_CUR (Unit : 10mV / 10mA)
        if((GET_TCPM_PD_PDO_STATUS_VOL(ucPortIndex) == GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, GET_TCPM_PD_PDO_STATUS_OBJ_POS(ucPortIndex) - 1)) &&
           (GET_TCPM_PD_PDO_STATUS_CUR(ucPortIndex) <= GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_PDO_STATUS_OBJ_POS(ucPortIndex) - 1)))
        {
            return _TRUE;
        }
    }
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    else if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, GET_TCPM_PD_PDO_STATUS_OBJ_POS(ucPortIndex) - 1) == _PD_3_PROGRAMMABLE_PDO)
    {
        // New Source Capabilities : _SRC_CAP_VOL_MAX / _SRC_CAP_VOL_MIN / _SRC_CAP_CUR (Unit : 10mV / 10mV / 50mA)
        // Previously Negotiated Voltage and Current : _PDO_STATUS_VOL / _PDO_STATUS_CUR (Unit : 10mV / 10mA)
        if((GET_TCPM_PD_PDO_STATUS_VOL(ucPortIndex) <= GET_TCPM_PD_SRC_CAP_VOL_MAX(ucPortIndex, GET_TCPM_PD_PDO_STATUS_OBJ_POS(ucPortIndex) - 1)) &&
           (GET_TCPM_PD_PDO_STATUS_VOL(ucPortIndex) >= GET_TCPM_PD_SRC_CAP_VOL_MIN(ucPortIndex, GET_TCPM_PD_PDO_STATUS_OBJ_POS(ucPortIndex) - 1)) &&
           (GET_TCPM_PD_PDO_STATUS_CUR(ucPortIndex) <= (GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, GET_TCPM_PD_PDO_STATUS_OBJ_POS(ucPortIndex) - 1) * 5)))
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if Power Contract Need to be Rebuild
// Input Value  : ucPortIndex
// Output Value : _PD_REBUILD_REQUIRED / _PD_REBUILD_NOT_REQUIRED
//--------------------------------------------------
EnumTypeCPDRebuildPowerContract ScalerTypeCTcpmPdCheckRebuildPowerContract_EXINT0(BYTE ucPortIndex)
{
    EnumTypeCPDRebuildPowerContract enumRebuildCheckResult = _PD_REBUILD_NOT_REQUIRED;

    if(GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex) == 500)
    {
        for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex); ucLoopIndex ++)
        {
            if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucLoopIndex) == _PD_FIX_SUPPLY_PDO)
            {
                // When Get CBL Max Current = 5A , SRC CAP CUR > 3A, Rebuild is Required
                if(GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucLoopIndex) > 300)
                {
                    enumRebuildCheckResult = _PD_REBUILD_REQUIRED;
                }
            }
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            else if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
            {
                if(((GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucLoopIndex)) * 5) > 300)
                {
                    enumRebuildCheckResult = _PD_REBUILD_REQUIRED;
                }
            }
#endif
        }
    }
    else if(GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex) < 300)
    {
        for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TCPM_PD_SPR_SRC_PDO_CNT(ucPortIndex); ucLoopIndex ++)
        {
            if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucLoopIndex) == _PD_FIX_SUPPLY_PDO)
            {
                // When Get CBL Max Current = USB Type-C Default Current(500mA/900mA/1.5A), SRC CAP CUR > CBL MAX CUR, Rebuild is Required
                if(GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucLoopIndex) > GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex))
                {
                    enumRebuildCheckResult = _PD_REBUILD_REQUIRED;
                }
            }
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
            else if(GET_TCPM_PD_SRC_PDO_TYPE(ucPortIndex, ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
            {
                if(((GET_TCPM_PD_SRC_CAP_CUR(ucPortIndex, ucLoopIndex)) * 5) > GET_TCPM_PD_CBL_MAX_CUR(ucPortIndex))
                {
                    enumRebuildCheckResult = _PD_REBUILD_REQUIRED;
                }
            }
#endif
        }
    }

    return enumRebuildCheckResult;
}

//--------------------------------------------------
// Description  : Clear HPD Queue When PD Reset TO Prevent DP Urgent Event DeadLock
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdClrHpd_EXINT0(BYTE ucPortIndex)
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
    ScalerDpAuxRxHpdTogglePhyResetProc(ScalerTypeCPcbPortConvertToDx_EXINT0(enumTypeCPcbPort), _LOW);
#endif

    SET_TCPM_PD_HPD_STATUS(ucPortIndex, _LOW);
    CLR_TCPM_PD_HPD_WPTR(ucPortIndex);
    CLR_TCPM_PD_HPD_RPTR(ucPortIndex);
    CLR_TCPM_PD_HPD_CNT(ucPortIndex);
}

//--------------------------------------------------
// Description  : Push HPD into HPD Queue
// Input Value  : enumTypeCPcbPort, enumHpdType : _PD_HPD_LOW / _PD_HPD_HIGH..., HPD Space Time(ms)
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdPushHpd_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex_EXINT0(enumTypeCPcbPort);
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
void ScalerTypeCTcpmPdClrInteropS8Flag_EXINT0(BYTE ucPortIndex)
{
    CLR_TCPM_PD_INTEROP_S8(ucPortIndex);
}

#if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Search Through All SVIDs to Check if DP_SID Exist
// Input Value  : ucPortIndex
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCTcpmPdSearchSvid_EXINT0(BYTE ucPortIndex)
{
    BYTE ucSearchResult = _FALSE;

    CLR_TCPM_PD_DPAM_SVID_SEARCH_FINISH(ucPortIndex);

    for(BYTE ucLoopIndex = 0; ucLoopIndex < (GET_TCPM_PD_RCV_NOD_CNT(ucPortIndex) * 4); ucLoopIndex = ucLoopIndex + 2)
    {
        if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex] == 0xFF) && (g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 1] == 0x01))
        {   // if SVID = DP_SID (0xFF01), Set Result to TRUE
            ucSearchResult = _TRUE;
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex] == 0x00) && (g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 1] == 0x00))
        {   // if SVID = 0x00, Search Finish
            SET_TCPM_PD_DPAM_SVID_SEARCH_FINISH(ucPortIndex);
        }
    }

    return ucSearchResult;
}

//--------------------------------------------------
// Description  : Search All Modes to Get DP Port Capability (DP_Tx) and Pin Assignment ( C / D / E )
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSearchMode_EXINT0(BYTE ucPortIndex)
{
    CLR_TCPM_PD_DPAM_OBJ_POS(ucPortIndex);

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
    {
        for(BYTE ucLoopIndex = 4; ucLoopIndex < (GET_TCPM_PD_RCV_NOD_CNT(ucPortIndex) * 4); ucLoopIndex = ucLoopIndex + 4)
        {
            // if(Support DP Tx), Get Supported Pin Assignments
            if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 3] & _BIT1) == _BIT1)
            {
                // Discover Mode [31:30] DPAM Version = b'00(2.0), b'01 (2.1)
                if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex] & (_BIT7 | _BIT6)) == 0x00))
                {
                    // if((Current DPAM >= 2.1) & (Rcv DPAM = 2.0)), Downgrade to DPAM 2.0
                    SET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_0_EARLIER);
                }

                // If Connect to Receptacle, Refer to DFP_D Pin Assignment
                if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 3] & _BIT6) == _BIT6)
                {
                    SET_TCPM_PD_PARTNER_DPAM_PIN_ASSIGNMENT(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 2]);
                }
                else
                {
                    // If Connect to Plug, Refer to UFP_D Pin Assignment
                    SET_TCPM_PD_PARTNER_DPAM_PIN_ASSIGNMENT(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 1]);
                }

                // Check If There is Any Pin Assignment Avaliable (Partner & Our Cap Both Support)
                if((GET_TCPM_PD_PARTNER_DPAM_PIN_ASSIGNMENT(ucPortIndex) & GET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(ucPortIndex)) != 0x00)
                {
                    SET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex, ucLoopIndex / 4);
                }
            }
            // Else, Keep Target Object Position = 0x00
        }
    }
#endif  // End of #if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
    {
        for(BYTE ucLoopIndex = 4; ucLoopIndex < (GET_TCPM_PD_RCV_NOD_CNT(ucPortIndex) * 4); ucLoopIndex = ucLoopIndex + 4)
        {
            // if(Support DP Rx), Get Supported Pin Assignments
            if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 3] & _BIT0) == _BIT0)
            {
                // Discover Mode [31:30] DPAM Version = b'00(2.0), b'01 (2.1)
                if((GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER) && ((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex] & (_BIT7 | _BIT6)) == 0x00))
                {
                    // if((Current DPAM >= 2.1) & (Rcv DPAM = 2.0)), Downgrade to DPAM 2.0
                    SET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_0_EARLIER);
                }

                // If Connect to Receptacle, Refer to UFP_D Pin Assignment
                if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 3] & _BIT6) == _BIT6)
                {
                    SET_TCPM_PD_PARTNER_DPAM_PIN_ASSIGNMENT(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 1]);
                }
                else
                {
                    // If Connect to Plug, Refer to DFP_D Pin Assignment
                    SET_TCPM_PD_PARTNER_DPAM_PIN_ASSIGNMENT(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 2]);
                }

                // Check If There is Any Pin Assignment Avaliable (Partner & Our Cap Both Support)
                if((GET_TCPM_PD_PARTNER_DPAM_PIN_ASSIGNMENT(ucPortIndex) & GET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(ucPortIndex)) != 0x00)
                {
                    SET_TCPM_PD_DPAM_OBJ_POS(ucPortIndex, ucLoopIndex / 4);
                }
            }
            // Else, Keep Target Object Position = 0x00
        }
    }
#endif  // End of #if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Update Port Partner DP Status
// Input Value  : ucPortIndex, enumVdmDpCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdUpdatePortPartnerDpStatus_EXINT0(BYTE ucPortIndex, EnumTypeCVdmDpCmd enumVdmDpCmd)
{
    switch(enumVdmDpCmd)
    {
        case _PD_VDM_DP_CMD_DP_STATUS_REQ:

            // Bit[1:0] DP Connect Status
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x00)
            {
                // Bit[1:0] = b'00 => Both DP_TX / DP_RX Disconnected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_CONNECT_NONE);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x01)
            {
                // Bit[1:0] = b'01 => DP_TX Connected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_TX_CONNECTED);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x02)
            {
                // Bit[1:0] = b'10 => DP_RX Connected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_RX_CONNECTED);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x03)
            {
                // Bit[1:0] = b'11 => Both DP_TX / DP_RX Connected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_TX_RX_BOTH_CONNECTED);
            }

#if(_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1)
            // Bit[2] DP Power Low, DP2.0 : Only DFP Need to Update
            // Bit[3] DP Function Enabled, DP2.0 : Only DFP Need to Update
            // Bit[4] Multi-Function Prefer, DP2.0 : Only DFP Need to Update
            // Bit[5] Usb Config Request, DP2.0 : Only DFP Need to Update
            // Bit[6] DP ALT Mode Exit Request, DP2.0 : Only DFP Need to Update
#else
            // Bit[2] DP Power Low, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT2) == _BIT2)
            {
                SET_TCPM_PD_PARTNER_DPAM_POWER_LOW(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_POWER_LOW(ucPortIndex);
            }

            // Bit[3] DP Function Enabled, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT3) == _BIT3)
            {
                SET_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(ucPortIndex);
            }

            // Bit[4] Multi-Function Prefer, DP2.1 : Only DFP Need to Update
            // Bit[5] Usb Config Request, DP2.1 : Only DFP Need to Update When Receive Attention
            // Bit[6] DP ALT Mode Exit Request, DP2.1 : Only DFP Need to Update When Receive Attention
#endif  // End of #if(_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1)

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                // Bit[8:7] IRQ_HPD / HPD State, Only DPTX Need to Update
                if((g_pucTypeCTcpmPdDataObj_EXINT[6] & _BIT0) == _BIT0)
                {
                    SET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex, _PD_HPD_IRQ);
                }
                else
                {
                    if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT7) == _BIT7)
                    {
                        SET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex, _PD_HPD_HIGH);
                    }
                    else
                    {
                        SET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex, _PD_HPD_LOW);
                    }
                }
            }
#endif  // End of #if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)

            break;

        case _PD_VDM_DP_CMD_DP_STATUS_ACK:

            // Bit[1:0] DP Connect Status
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x00)
            {
                // Bit[1:0] = b'00 => Both DP_TX / DP_RX Disconnected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_CONNECT_NONE);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x01)
            {
                // Bit[1:0] = b'01 => DP_TX Connected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_TX_CONNECTED);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x02)
            {
                // Bit[1:0] = b'10 => DP_RX Connected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_RX_CONNECTED);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x03)
            {
                // Bit[1:0] = b'11 => Both DP_TX / DP_RX Connected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_TX_RX_BOTH_CONNECTED);
            }

#if(_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1)
            // Bit[2] DP Power Low, DP2.0 : Only DFP Need to Update
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT2) == _BIT2)
            {
                SET_TCPM_PD_PARTNER_DPAM_POWER_LOW(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_POWER_LOW(ucPortIndex);
            }

            // Bit[3] DP Function Enabled, DP2.0 : Only DFP Need to Update
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT3) == _BIT3)
            {
                SET_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(ucPortIndex);
            }

            // Bit[4] Multi-Function Prefer, DP2.0 : Only DFP Need to Update
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT4) == _BIT4)
            {
                SET_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(ucPortIndex);
            }

            // Bit[5] Usb Config Request, DP2.0 : Only DFP Need to Update
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT5) == _BIT5)
            {
                SET_TCPM_PD_PARTNER_DPAM_USB_CONFIG_REQUEST(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_USB_CONFIG_REQUEST(ucPortIndex);
            }

            // Bit[6] DP ALT Mode Exit Request, DP2.0 : Only DFP Need to Update
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT6) == _BIT6)
            {
                SET_TCPM_PD_PARTNER_DPAM_EXIT_REQ(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_EXIT_REQ(ucPortIndex);
            }
#else
            // Bit[2] DP Power Low, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention
            // Bit[3] DP Function Enabled, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention

            // Bit[4] Multi-Function Prefer, DP2.1 : Only DFP Need to Update
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT4) == _BIT4)
            {
                SET_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(ucPortIndex);
            }

            // Bit[5] Usb Config Request, DP2.1 : Only DFP Need to Update When Receive Attention
            // Bit[6] DP ALT Mode Exit Request, DP2.1 : Only DFP Need to Update When Receive Attention
#endif  // End of #if(_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1)

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                // Bit[8:7] IRQ_HPD / HPD State, Only DPTX Need to Update
                if((g_pucTypeCTcpmPdDataObj_EXINT[6] & _BIT0) == _BIT0)
                {
                    SET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex, _PD_HPD_IRQ);
                }
                else
                {
                    if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT7) == _BIT7)
                    {
                        SET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex, _PD_HPD_HIGH);
                    }
                    else
                    {
                        SET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex, _PD_HPD_LOW);
                    }
                }
            }
#endif  // End of #if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)

            break;

        case _PD_VDM_DP_CMD_ATTENTION_REQ:

            // Bit[1:0] DP Connect Status
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x00)
            {
                // Bit[1:0] = b'00 => Both DP_TX / DP_RX Disconnected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_CONNECT_NONE);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x01)
            {
                // Bit[1:0] = b'01 => DP_TX Connected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_TX_CONNECTED);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x02)
            {
                // Bit[1:0] = b'10 => DP_RX Connected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_RX_CONNECTED);
            }
            else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x03)
            {
                // Bit[1:0] = b'11 => Both DP_TX / DP_RX Connected
                SET_TCPM_PD_PARTNER_DPAM_CONNECT_STATUS(ucPortIndex, _PD_DP_TX_RX_BOTH_CONNECTED);
            }

            // Bit[2] DP Power Low, DP2.0 : Only DFP Need to Update
            // Bit[2] DP Power Low, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT2) == _BIT2)
            {
                SET_TCPM_PD_PARTNER_DPAM_POWER_LOW(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_POWER_LOW(ucPortIndex);
            }

            // Bit[3] DP Function Enabled, DP2.0 : Only DFP Need to Update
            // Bit[3] DP Function Enabled, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT3) == _BIT3)
            {
                SET_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_FUNCTION_ENABLE(ucPortIndex);
            }

            // Bit[4] Multi-Function Prefer, DP2.0 : Only DFP Need to Update
            // Bit[4] Multi-Function Prefer, DP2.1 : Only DFP Need to Update
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT4) == _BIT4)
            {
                SET_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(ucPortIndex);
            }

            // Bit[5] Usb Config Request, DP2.0 : Only DFP Need to Update
            // Bit[5] Usb Config Request, DP2.1 : Only DFP Need to Update When Receive Attention
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT5) == _BIT5)
            {
                SET_TCPM_PD_PARTNER_DPAM_USB_CONFIG_REQUEST(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_USB_CONFIG_REQUEST(ucPortIndex);
            }

            // Bit[6] DP ALT Mode Exit Request, DP2.0 : Only DFP Need to Update
            // Bit[6] DP ALT Mode Exit Request, DP2.1 : Only DFP Need to Update When Receive Attention
            if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT6) == _BIT6)
            {
                SET_TCPM_PD_PARTNER_DPAM_EXIT_REQ(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_EXIT_REQ(ucPortIndex);
            }

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
            if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
            {
                // Bit[8:7] IRQ_HPD / HPD State, Only DPTX Need to Update
                if((g_pucTypeCTcpmPdDataObj_EXINT[6] & _BIT0) == _BIT0)
                {
                    SET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex, _PD_HPD_IRQ);
                }
                else
                {
                    if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT7) == _BIT7)
                    {
                        SET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex, _PD_HPD_HIGH);
                    }
                    else
                    {
                        SET_TCPM_PD_PARTNER_HPD_TYPE(ucPortIndex, _PD_HPD_LOW);
                    }
                }
            }
#endif  // End of #if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
            // Bit[9] No DP ALT Suspend, DP2.1 : Only DFP Need to Update When Receive Attention
            if((g_pucTypeCTcpmPdDataObj_EXINT[6] & _BIT1) == _BIT1)
            {
                SET_TCPM_PD_PARTNER_DPAM_NO_SUSPEND(ucPortIndex);
            }
            else
            {
                CLR_TCPM_PD_PARTNER_DPAM_NO_SUSPEND(ucPortIndex);
            }
#endif  // End of #if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check if to Send DP Config
// Input Value  : ucPortIndex
// Output Value : _PD_CONFIG_REQUIRED (Send DP Config)/ _PD_CONFIG_NOT_REQUIRED (Maintain Current Config or Exit Mode)
//--------------------------------------------------
EnumTypeCPDDpStatusCheckResult ScalerTypeCTcpmPdCheckDpStatus_EXINT0(BYTE ucPortIndex)
{
    BYTE ucMultiFunctionPrefer = (((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT4) == _BIT4) ? _TRUE : _FALSE);

    SET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex, _PD_DP_CONFIG);

    // Display Port Status : [6] Exit DP Request / [5] USB Config Request / [4] Multi-Func = X
    // [3] Adaptor Func = 1 / [2] Power Low = 0 / [1:0] DP_TX Connected = 01/DP_RX Connected = 10
#if((_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON) && (_TYPE_C_EMB_CTS_FLOW == _ON))
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
    {
        // DFP Check DP_TX Connected
        if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT0)) != _BIT0)
        {
            SET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex, _PD_USB_CONFIG);
        }
    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
    {
        // DFP Check DP_RX Connected
        if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1)) != _BIT1)
        {
            SET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex, _PD_USB_CONFIG);
        }
    }
#endif

    if((ucMultiFunctionPrefer == _TRUE) && (GET_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(ucPortIndex) == _FALSE))
    {
        // Set Multi-Function Bit Change in DP Config(Pin Assignment C <=> Pin Assignment D)
        if(GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG)
        {
            SET_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(ucPortIndex);
        }
    }
    else if((ucMultiFunctionPrefer == _FALSE) && (GET_TCPM_PD_PARTNER_DPAM_MULTI_FUNCTION(ucPortIndex) == _TRUE))
    {
        // Set Multi-Function Bit Change in DP Config(Pin Assignment C <=> Pin Assignment D)
        if(GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG)
        {
            SET_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(ucPortIndex);
        }
    }
    else
    {
        CLR_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(ucPortIndex);
    }

    // DFP Check USB Configuration Request Bit
    if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT5) == _BIT5)
    {
        SET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex, _PD_USB_CONFIG);
    }

    // DFP Check Exit Mode Bit
    if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT6) == _BIT6)
    {
        SET_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex);
        SET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex, _PD_USB_CONFIG);

        if(GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex) == _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // For C-DP Cable: DFP Shall not Send Exit Mode, But Still Send DP Config(USB) to DP_RX
            CLR_TCPM_PD_DPAM_EXIT_REQ(ucPortIndex);
        }
    }

    // Check: Multi-Function Bit Change in DP Config(Pin Assignment C <=> Pin Assignment D)
    if((GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == _PD_DP_CONFIG) && (GET_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(ucPortIndex) == _TRUE))
    {
        // DP Config Required(Pin C => Pin D): (Current Pin Assignment = C) && (Both Support Pin Assignment D) && (Multi-Function = _TRUE)
        if((GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex) == _TYPE_C_PIN_ASSIGNMENT_C) && ((GET_TCPM_PD_PARTNER_DPAM_PIN_ASSIGNMENT(ucPortIndex) & GET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(ucPortIndex) & _TYPE_C_PIN_ASSIGNMENT_D) != 0x00) && (ucMultiFunctionPrefer == _TRUE))
        {
            return _PD_CONFIG_REQUIRED;
        }
        // DP Config Required(Pin D => Pin C): (Current Pin Assignment = D) && (Both Support Pin Assignment C) && (Multi-Function = _FALSE)
        else if((GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex) == _TYPE_C_PIN_ASSIGNMENT_D) && ((GET_TCPM_PD_PARTNER_DPAM_PIN_ASSIGNMENT(ucPortIndex) & GET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(ucPortIndex) & _TYPE_C_PIN_ASSIGNMENT_C) != 0x00) && (ucMultiFunctionPrefer == _FALSE))
        {
            return _PD_CONFIG_REQUIRED;
        }
        else
        {
            CLR_TCPM_PD_DPAM_MULTI_FUNCTION_CHANGE(ucPortIndex);
        }
    }

    if(GET_TCPM_PD_DPAM_CONFIG(ucPortIndex) == GET_TCPM_PD_DPAM_TARGET_CONFIG(ucPortIndex))
    {
        return _PD_CONFIG_NOT_REQUIRED;
    }
    else
    {
        return _PD_CONFIG_REQUIRED;
    }
}

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
//--------------------------------------------------
// Description  : Judge DP Functionality Support Of Cable(When Ack Vdo Received For Discover Id(SOP'/SOP''))
// Input Value  : ucPortIndex
// Output Value : EnumTypeCPDAltModeState(_PD_ALT_MODE_SEND_ENTER_MODE / _PD_ALT_MODE_ERROR)
//--------------------------------------------------
EnumTypeCPDAltModeState ScalerTypeCTcpmPdJudgeCableId_EXINT0(BYTE ucPortIndex)
{
    // Judge Whether The Cable Supports DP Functionality, and Switch DP_ALT_STATE
    if(GET_TCPM_PD_CBL_PRODUCT_TYPE(ucPortIndex) == _PD_PASSIVE_CABLE)
    {
        if(GET_TCPM_PD_CBL_USB_HIGHEST_SPEED(ucPortIndex) == _PD_CBL_USB_2_ONLY)
        {
            // Stop Enter DP Alt Mode Flow Both for Device & Cable
            return _PD_ALT_MODE_ERROR;
        }
        else if(GET_TCPM_PD_CBL_MODAL_OPERATION_SUPPORT(ucPortIndex) == _FALSE)
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
            // On-going Enter DP Alt Mode Flow Both for Device & Cable
            return _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P;
        }
    }
    else if(GET_TCPM_PD_CBL_PRODUCT_TYPE(ucPortIndex) == _PD_ACTIVE_CABLE)
    {
        if(GET_TCPM_PD_CBL_MODAL_OPERATION_SUPPORT(ucPortIndex) == _FALSE)
        {
            // Stop Enter DP Alt Mode Flow Both for Device & Cable
            return _PD_ALT_MODE_ERROR;
        }
        else
        {
            // On-going Enter DP Alt Mode Flow Both for Device & Cable
            return _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P;
        }
    }
    else
    {
        // If Cable Type is VPD, Stop Enter DP Alt Mode Flow Both for Device & Cable
        return _PD_ALT_MODE_ERROR;
    }
}

//--------------------------------------------------
// Description  : Search Through All SVIDs to All Svid The Cable Supports
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSearchCableSvid_EXINT0(BYTE ucPortIndex)
{
    CLR_TCPM_PD_CBL_SVID_SEARCH_FINISH(ucPortIndex);

    for(BYTE ucLoopIndex = 0; ucLoopIndex < (GET_TCPM_PD_RCV_NOD_CNT(ucPortIndex) * 4); ucLoopIndex = ucLoopIndex + 2)
    {
        if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex] == 0xFF) && (g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 1] == 0x01))
        {   // if SVID = DP_SID (0xFF01), Set Cable DP Svid Support
            SET_TCPM_PD_CBL_DP_SVID_SUPPORT(ucPortIndex);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex] == 0x80) && (g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 1] == 0x87))
        {   // if SVID = TBT3_SID (0x8087), Set Cable TBT3 Svid Support
            SET_TCPM_PD_CBL_TBT3_SVID_SUPPORT(ucPortIndex);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex] == 0x00) && (g_pucTypeCTcpmPdDataObj_EXINT[ucLoopIndex + 1] == 0x00))
        {   // if SVID = 0x00, Search Finish
            SET_TCPM_PD_CBL_SVID_SEARCH_FINISH(ucPortIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Record Cable Info Of Discover Dp Mode Ack
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSaveCableDpModeInfo_EXINT0(BYTE ucPortIndex)
{
    // Bit[31:30] VDO Version
    if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT7 | _BIT6)) == 0x00)
    {
        SET_TCPM_PD_CBL_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_0_EARLIER);
    }
    else if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT7 | _BIT6)) == _BIT6)
    {
        SET_TCPM_PD_CBL_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_1_HIGHER);
    }

    // Bit[29:28] Active Components.
    // When In DPAM:  1.[31:30] VDO Version = 1, Discover Mode Ack Takes Priority;  2.[31:30] VDO Version = 0, Discover ID Ack Takes Priotity.
    if(GET_TCPM_PD_CBL_DPAM_VERSION(ucPortIndex) == _PD_DPAM_VER_2_1_HIGHER)
    {
        if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT5 | _BIT4)) == 0x00)
        {
            SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_PASSIVE);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT5 | _BIT4)) == _BIT4)
        {
            SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_ACTIVE_RETIMER);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT5 | _BIT4)) == _BIT5)
        {
            SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_ACTIVE_REDRIVER);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
        {
            SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_OPTICAL);
        }

        // Bit[26] Cable UHBR13.5 Support: Y/N
        if((g_pucTypeCTcpmPdDataObj_EXINT[4] & _BIT2) == _BIT2)
        {
            SET_TCPM_PD_CBL_UHBR13P5_SUPPORT(ucPortIndex);
        }

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
        if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
        {
            // Bit[23:16] DP Sink Device Pin Assignments Supported
            if(g_pucTypeCTcpmPdDataObj_EXINT[5] == 0x0C)
            {
                SET_TCPM_PD_CBL_PIN_ASSIGNMENT(ucPortIndex, _PD_CBL_PIN_ASSIGNMENT_C_AND_D);
            }
            else if(g_pucTypeCTcpmPdDataObj_EXINT[5] == 0x10)
            {
                SET_TCPM_PD_CBL_PIN_ASSIGNMENT(ucPortIndex, _PD_CBL_PIN_ASSIGNMENT_E);
            }
        }
#endif

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
        if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
        {
            // Bit[15:8] DP Source Device Pin Assignments Supported
            if(g_pucTypeCTcpmPdDataObj_EXINT[6] == 0x0C)
            {
                SET_TCPM_PD_CBL_PIN_ASSIGNMENT(ucPortIndex, _PD_CBL_PIN_ASSIGNMENT_C_AND_D);
            }
            else if(g_pucTypeCTcpmPdDataObj_EXINT[6] == 0x10)
            {
                SET_TCPM_PD_CBL_PIN_ASSIGNMENT(ucPortIndex, _PD_CBL_PIN_ASSIGNMENT_E);
            }
        }
#endif

        // Bit[5:2] Signalling for Cable Information Transport of DisplayPort Protocol
        if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT4) == _BIT4)
        {
            SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_UHBR20);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT3) == _BIT3)
        {
            SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_UHBR10);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT2) == _BIT2)
        {
            SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_HBR3);
        }
    }
    else // Save DPAM 2.0 Cable Info.
    {
#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
        if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
        {
            // Bit[23:16] DP Sink Device Pin Assignments Supported
            if(g_pucTypeCTcpmPdDataObj_EXINT[5] == 0x0C)
            {
                SET_TCPM_PD_CBL_PIN_ASSIGNMENT(ucPortIndex, _PD_CBL_PIN_ASSIGNMENT_C_AND_D);
            }
        }
#endif

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
        if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
        {
            // Bit[15:8] DP Source Device Pin Assignments Supported
            if(g_pucTypeCTcpmPdDataObj_EXINT[6] == 0x0C)
            {
                SET_TCPM_PD_CBL_PIN_ASSIGNMENT(ucPortIndex, _PD_CBL_PIN_ASSIGNMENT_C_AND_D);
            }
        }
#endif

        // Bit[5:2] Signalling for Cable Information Transport of DisplayPort Protocol
        if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT2) == _BIT2)
        {
            SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_HBR3);
        }
    }
}

//--------------------------------------------------
// Description  : Record Cable Info Of TBT3 Discover Mode Ack
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdSaveCableTbt3ModeInfo_EXINT0(BYTE ucPortIndex)
{
    // Bit[25] TBT3 Passive Cable(0b') / Active Cable(1b')
    if((g_pucTypeCTcpmPdDataObj_EXINT[4] & _BIT1) == _BIT1)
    {
        SET_TCPM_PD_CBL_TBT3_PRODUCT_TYPE(ucPortIndex, _PD_CBL_TBT3_ACTIVE_CABLE);
    }
    else
    {
        SET_TCPM_PD_CBL_TBT3_PRODUCT_TYPE(ucPortIndex, _PD_CBL_TBT3_PASSIVE_CABLE);
    }

    // Bit[23] Active Cable Plug Link Training:  Active With Bi-Directional LSRX Or When Passive(0b') / Active With Uni-Directional LSRX(1b')
    if((g_pucTypeCTcpmPdDataObj_EXINT[5] & _BIT7) == _BIT7)
    {
        SET_TCPM_PD_CBL_TBT3_DIRECTION(ucPortIndex, _PD_CBL_TBT3_UNIDIRECTION);
    }
    else
    {
        SET_TCPM_PD_CBL_TBT3_DIRECTION(ucPortIndex, _PD_CBL_TBT3_BIDIRECTION);
    }

    // Bit[22] Re-Timer Y/N
    if((g_pucTypeCTcpmPdDataObj_EXINT[5] & _BIT6) == _BIT6)
    {
        SET_TCPM_PD_CBL_TBT3_RETIMER(ucPortIndex);
    }

    // Bit[21] Cable Type Optical Y/N
    if((g_pucTypeCTcpmPdDataObj_EXINT[5] & _BIT5) == _BIT5)
    {
        SET_TCPM_PD_CBL_TBT3_OPTICAL(ucPortIndex);
    }

    // Bit[20:19] TBT Rounded Support
    if((g_pucTypeCTcpmPdDataObj_EXINT[5] & (_BIT4 | _BIT3)) == 0x00)
    {
        SET_TCPM_PD_CBL_TBT3_ROUNDED_SUPPORT(ucPortIndex, _PD_CBL_TBT3_3RD_GEN_NON_ROUNDED);
    }
    else if((g_pucTypeCTcpmPdDataObj_EXINT[5] & (_BIT4 | _BIT3)) == _BIT3)
    {
        SET_TCPM_PD_CBL_TBT3_ROUNDED_SUPPORT(ucPortIndex, _PD_CBL_TBT3_3RD_AND_4TH_GEN_ROUNDED);
    }

    // Bit[18:16] Cable Speed
    if((g_pucTypeCTcpmPdDataObj_EXINT[5] & (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
    {
        SET_TCPM_PD_CBL_TBT3_SPEED(ucPortIndex, _PD_CBL_TBT3_U3P1_GEN1);
    }
    else if((g_pucTypeCTcpmPdDataObj_EXINT[5] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
    {
        SET_TCPM_PD_CBL_TBT3_SPEED(ucPortIndex, _PD_CBL_TBT3_10G);
    }
    else if((g_pucTypeCTcpmPdDataObj_EXINT[5] & (_BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        SET_TCPM_PD_CBL_TBT3_SPEED(ucPortIndex, _PD_CBL_TBT3_20G);
    }
}

//--------------------------------------------------
// Description  : Judge DP Functionality Support Of Cable
// Input Value  : ucPortIndex
// Output Value : EnumTypeCPDAltModeState(_PD_ALT_MODE_SEND_ENTER_MODE / _PD_ALT_MODE_ERROR)
//--------------------------------------------------
EnumTypeCPDAltModeState ScalerTypeCTcpmPdJudgeCableDpFunctionality_EXINT0(BYTE ucPortIndex)
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

//--------------------------------------------------
// Description  : Judge DP Functionality Support Of Cable(When Ack Vdo Received For TBT3 Discover Mode(SOP'/SOP''))
// Input Value  : ucPortIndex
// Output Value : EnumTypeCPDAltModeState(_PD_ALT_MODE_SEND_ENTER_MODE / _PD_ALT_MODE_ERROR)
//--------------------------------------------------
EnumTypeCPDAltModeState ScalerTypeCTcpmPdJudgeCableTbt3Mode_EXINT0(BYTE ucPortIndex)
{
    if(GET_TCPM_PD_CBL_DP_MODE_INFO_RECEIVED(ucPortIndex) == _TRUE)
    {
        // If Cable Support DP Mode + TBT3 Mode : Update Cable Active Component and Do Enter Mode When Received Cable TBT3 Discover Mode Ack.
        if((GET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex) == _PD_CBL_COMPONENT_PASSIVE) && (GET_TCPM_PD_CBL_TBT3_PRODUCT_TYPE(ucPortIndex) == _PD_CBL_TBT3_ACTIVE_CABLE))
        {
            if(GET_TCPM_PD_CBL_TBT3_RETIMER(ucPortIndex) == _TRUE)
            {
                SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_ACTIVE_RETIMER);
            }
            else
            {
                SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_ACTIVE_REDRIVER);
            }
        }

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
        // If Cable Only Support TBT3 Mode : Judge DP Functionality Support Of Cable Base on Cable TBT3 Mode Info
        if((GET_TCPM_PD_CBL_TBT3_RETIMER(ucPortIndex) == _FALSE) && (GET_TCPM_PD_CBL_TBT3_PRODUCT_TYPE(ucPortIndex) == _PD_CBL_TBT3_PASSIVE_CABLE))
        {
            if((GET_TCPM_PD_CBL_TBT3_SPEED(ucPortIndex) == _PD_CBL_TBT3_U3P1_GEN1) || ((GET_TCPM_PD_CBL_TBT3_SPEED(ucPortIndex) == _PD_CBL_TBT3_10G)))
            {
                SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_UHBR10);
            }
            else if(GET_TCPM_PD_CBL_TBT3_SPEED(ucPortIndex) == _PD_CBL_TBT3_20G)
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
            return _PD_ALT_MODE_ERROR;
        }
    }
}

//--------------------------------------------------
// Description  : UFP Save Related DP Capabilities Info(From Dp Configure REQ) of Cable To Fill Into DPCD
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdUfpSaveCableInfoForDpcd_EXINT0(BYTE ucPortIndex)
{
    // Bit[31:30] VDO Version
    if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT7 | _BIT6)) == 0x00)
    {
        SET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_0_EARLIER);
    }
    else if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT7 | _BIT6)) == _BIT6)
    {
        SET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex, _PD_DPAM_VER_2_1_HIGHER);
    }

    if(GET_TCPM_PD_PARTNER_DPAM_VERSION(ucPortIndex) >= _PD_DPAM_VER_2_1_HIGHER)
    {
        // Bit[29:28] Cable Active Components
        if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT5 | _BIT4)) == 0x00)
        {
            SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_PASSIVE);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT5 | _BIT4)) == _BIT4)
        {
            SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_ACTIVE_RETIMER);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT5 | _BIT4)) == _BIT5)
        {
            SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_ACTIVE_REDRIVER);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[4] & (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
        {
            SET_TCPM_PD_CBL_ACTIVE_COMPONENT(ucPortIndex, _PD_CBL_COMPONENT_OPTICAL);
        }

        // Bit[26] Cable UHBR13.5 Support: Y/N
        if((g_pucTypeCTcpmPdDataObj_EXINT[4] & _BIT2) == _BIT2)
        {
            SET_TCPM_PD_CBL_UHBR13P5_SUPPORT(ucPortIndex);
        }

        // Bit[5:2] Signalling for Cable Information Transport of DisplayPort Protocol
        if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT4) == _BIT4)
        {
            SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_UHBR20);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT3) == _BIT3)
        {
            SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_UHBR10);
        }
        else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT2) == _BIT2)
        {
            SET_TCPM_PD_CBL_MAX_DP_RATE(ucPortIndex, _PD_CBL_MAX_HBR3);
        }
    }
}
#endif  // End of #if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)

//--------------------------------------------------
// Description  : Check if DP_Config is Valid @ Interrupt
// Input Value  : ucPortIndex
// Output Value : _TRUE(REQ as DP_RX & Pin Assignment C / D / E || Config USB & Pin Assignment NONE)/_FALSE
//--------------------------------------------------
BYTE ScalerTypeCTcpmPdCheckDpConfig_EXINT0(BYTE ucPortIndex)
{
    BYTE ucCheckResult = _FALSE;
#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_RX)
    {
        // Check if Request DP_RX (VDO1[1:0] = b'10)
        if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == _BIT1)
        {
            switch(g_pucTypeCTcpmPdDataObj_EXINT[6])
            {
                case _TYPE_C_PIN_ASSIGNMENT_C:
                case _TYPE_C_PIN_ASSIGNMENT_D:
                case _TYPE_C_PIN_ASSIGNMENT_E:

                    SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[6]);
                    ucCheckResult = _TRUE;

                    break;

                default:

                    ucCheckResult = _FALSE;

                    break;
            }
        }
        // Check if Request USB Configuration (VDO1[1:0] = b'00)
        else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x00)
        {
            SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_NONE);
            ucCheckResult = _TRUE;
        }
        else
        {
            ucCheckResult = _FALSE;
        }
    }
#endif

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
    if(GET_TCPM_PD_BEHAVIOR_TYPE(ucPortIndex) == _TYPE_C_DP_TX)
    {
        if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == _BIT0)
        {
            switch(g_pucTypeCTcpmPdDataObj_EXINT[6])
            {
                case _TYPE_C_PIN_ASSIGNMENT_C:
                case _TYPE_C_PIN_ASSIGNMENT_D:
                case _TYPE_C_PIN_ASSIGNMENT_E:

                    SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, g_pucTypeCTcpmPdDataObj_EXINT[6]);
                    ucCheckResult = _TRUE;

                    break;

                default:

                    ucCheckResult = _FALSE;

                    break;
            }
        }
        // Check if Request USB Configuration (VDO1[1:0] = b'00)
        else if((g_pucTypeCTcpmPdDataObj_EXINT[7] & (_BIT1 | _BIT0)) == 0x00)
        {
            SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_NONE);
            ucCheckResult = _TRUE;
        }
        else
        {
            ucCheckResult = _FALSE;
        }
    }
#endif

    return ucCheckResult;
}

//--------------------------------------------------
// Description  : DFP Judge Target Pin Assignment By Partner Capability
// Input Value  : ucPortIndex
// Output Value : Target Pin Assignment to be Configured
//--------------------------------------------------
BYTE ScalerTypeCTcpmPdDfpJudgePinAssignment_EXINT0(BYTE ucPortIndex)
{
    BYTE ucMultiFunctionPrefer = (((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT4) == _BIT4) ? _TRUE : _FALSE);
    BYTE ucPinAssignment = (GET_TCPM_PD_PARTNER_DPAM_PIN_ASSIGNMENT(ucPortIndex) & (BYTE)GET_TCPM_PD_DPAM_PIN_ASSIGNMENT_CAP(ucPortIndex));
    SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_NONE);

    if((ucMultiFunctionPrefer == _TRUE) && ((ucPinAssignment & _BIT3) == _BIT3))
    {
        // If "Multi-Function = 1" and "Pin Assignment D Support"
        SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_D);
    }
    else if((ucPinAssignment & _BIT2) == _BIT2)
    {
        // If "Pin Assignment C Support"
        SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_C);
    }
    else if((ucPinAssignment & _BIT3) == _BIT3)
    {
        // If "Pin Assignment D Support"
        SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_D);
    }
    else if((ucPinAssignment & _BIT4) == _BIT4)
    {
        // If "Pin Assignment E Support"
        SET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex, _TYPE_C_PIN_ASSIGNMENT_E);
    }

    if(GET_TCPM_PD_DPAM_PIN_ASSIGNMENT(ucPortIndex) != _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

#if(_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Pop HPD from HPD Queue @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmPdPopHpd_EXINT0(BYTE ucPortIndex)
{
    EnumInputPort enumInputPort = ScalerTypeCPcbPortConvertToDx_EXINT0(g_penumTypeCTcpmPort[ucPortIndex]);

    if(GET_TCPM_PD_HPD_CNT(ucPortIndex) > 0)
    {
        // Update HPD Status For DP Usage
        if(GET_TCPM_PD_HPD_QUEUE(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)) == _PD_HPD_LOW)
        {
            ScalerDpAuxRxHpdTogglePhyResetProc(enumInputPort, _LOW);
            SET_TCPM_PD_HPD_STATUS(ucPortIndex, _LOW);
        }
        else if(GET_TCPM_PD_HPD_QUEUE(ucPortIndex, GET_TCPM_PD_HPD_RPTR(ucPortIndex)) == _PD_HPD_HIGH)
        {
            ScalerDpAuxRxHpdTogglePhyResetProc(enumInputPort, _HIGH);
            SET_TCPM_PD_HPD_STATUS(ucPortIndex, _HIGH);
        }

        CLR_TCPM_PD_HPD_QUEUE(ucPortIndex);
        CLR_TCPM_PD_HPD_SPACE_TIME(ucPortIndex);

        // Adjust HPD Queue
        ADD_TCPM_PD_HPD_RPTR(ucPortIndex);
        SUB_TCPM_PD_HPD_CNT(ucPortIndex);
    }
}
#endif // End of #if (_PORT_CTRL_EMB_DP_RX_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP_TX Update DP_RX HPD Status @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumTypeCPDHpdType ScalerTypeCTcpmPdDecodePartnerHpdStatus_EXINT0(void)
{
    EnumTypeCPDHpdType enumHpdType = _PD_HPD_NONE;

    if((g_pucTypeCTcpmPdDataObj_EXINT[6] & _BIT0) == _BIT0)
    {
        enumHpdType = _PD_HPD_IRQ;
    }
    else
    {
        if((g_pucTypeCTcpmPdDataObj_EXINT[7] & _BIT7) == _BIT7)
        {
            enumHpdType = _PD_HPD_HIGH;
        }
        else
        {
            enumHpdType = _PD_HPD_LOW;
        }
    }

    return enumHpdType;
}
#endif  // End of #if(_PORT_CTRL_EMB_DP_TX_SUPPORT == _ON)
#endif  // End of #if(_PORT_CTRL_EMB_DP_ALT_MODE_SUPPORT == _ON)
#endif  // End of #if(_TYPE_C_MODAL_OPERATION_SUPPORT == _ON)


//--------------------------------------------------
// Description  : Type C TCPM Get TCPCI Byte Register (for 1-Byte Reg)
// Input Value  : ucPortIndex, enumReg
// Output Value : pucTcpciData (1-Byte)
//--------------------------------------------------
BYTE ScalerTypeCTcpmTcpciGetByte_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg)
{
    BYTE pucTcpciData[1] = {0xFF};

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _ENABLE) == _FAIL)
    {
        return pucTcpciData[0];
    }

    // 2. Read TCPC Data by TCPM HW IIC
    ScalerTypeCTcpmHwIICRead_EXINT0(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 1, pucTcpciData);

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);
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
void ScalerTypeCTcpmTcpciSetByte_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, BYTE ucData)
{
    BYTE pucTcpciData[1];

    pucTcpciData[0] = ucData;

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _ENABLE) == _FAIL)
    {
        return;
    }

    // 2. Write TCPC Data by TCPM HW IIC
    ScalerTypeCTcpmHwIICWrite_EXINT0(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 1, pucTcpciData);

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);
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
WORD ScalerTypeCTcpmTcpciGetWord_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg)
{
    BYTE pucTcpciData[2] = {0xFF, 0xFF};

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _ENABLE) == _FAIL)
    {
        return TO_WORD(pucTcpciData[1], pucTcpciData[0]);
    }

    // 2. Read TCPC Data by TCPM HW IIC
    ScalerTypeCTcpmHwIICRead_EXINT0(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 2, pucTcpciData);

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);
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
void ScalerTypeCTcpmTcpciSetWord_EXINT0(BYTE ucPortIndex, EnumTypeCTcpmTcpciReg enumReg, WORD usData)
{
    BYTE pucTcpciData[2];

    pucTcpciData[0] = (BYTE)(usData);
    pucTcpciData[1] = (BYTE)(usData >> 8);

    // --------------------------------------------------------------
    // NOTE : TCPC will not Write Register if TCPM intends to Write Data to Reserved Field (Bit) in Certain Register
    // --------------------------------------------------------------

#if(_HW_TCPM_SUPPORT == _ON)
    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _ENABLE) == _FAIL)
    {
        return;
    }

    // 2. Write TCPC Data by TCPM HW IIC
    ScalerTypeCTcpmHwIICWrite_EXINT0(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)enumReg, 2, pucTcpciData);

    // 3. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);
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
void ScalerTypeCTcpmTcpciSetTxBuffer_EXINT0(BYTE ucPortIndex, EnumTypeCPDCmd enumPdCmd, BYTE ucTxByteCnt, WORD usMessageHeader)
{
#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_TX_AUTO_CTRL == _ON)

    // 1. Set Write Byte Cnt
    ScalerSetByte_EXINT(PFA_50_TCPC_0_TX_BUFFER_0 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ucTxByteCnt);

    // 2. Re-arrange Data for TCPCI Tx Buffer
    // 2-1. Set Message Header (L, H)
    ScalerSetByte_EXINT(PFA_51_TCPC_0_TX_BUFFER_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)usMessageHeader);
    ScalerSetByte_EXINT(PFA_52_TCPC_0_TX_BUFFER_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), (BYTE)(usMessageHeader >> 8));

    // 2-2. Set Data Object (Data Obj_0 [7:0], Data Obj_0 [15:8], Data Obj_0 [23:16], Data Obj_0 [31:24])
    if((enumPdCmd & (_BIT7 | _BIT6)) == _PD_CMD_TYPE_DATA)
    {
        // ucTxBuffer[3] = Data Obj_0 [7:0]
        // ucTxBuffer[4] = Data Obj_0 [15:8]
        // ucTxBuffer[5] = Data Obj_0 [23:16]
        // ucTxBuffer[6] = Data Obj_0 [31:24]
        for(BYTE ucLoopIndex = 0; ucLoopIndex < ((ucTxByteCnt - 2) / 4); ucLoopIndex++)
        {
            ScalerSetByte_EXINT(PFA_53_TCPC_0_TX_BUFFER_3 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (ucLoopIndex * 4), g_pucTypeCTcpmPdDataObj_EXINT[3 + (ucLoopIndex * 4)]);
            ScalerSetByte_EXINT(PFA_54_TCPC_0_TX_BUFFER_4 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (ucLoopIndex * 4), g_pucTypeCTcpmPdDataObj_EXINT[2 + (ucLoopIndex * 4)]);
            ScalerSetByte_EXINT(PFA_55_TCPC_0_TX_BUFFER_5 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (ucLoopIndex * 4), g_pucTypeCTcpmPdDataObj_EXINT[1 + (ucLoopIndex * 4)]);
            ScalerSetByte_EXINT(PFA_56_TCPC_0_TX_BUFFER_6 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + (ucLoopIndex * 4), g_pucTypeCTcpmPdDataObj_EXINT[0 + (ucLoopIndex * 4)]);
        }
    }
    else if((enumPdCmd & (_BIT7 | _BIT6)) == _PD_CMD_TYPE_EXT)
    {
        // ucTxBuffer[3] = Ext Message Header [7:0]
        // ucTxBuffer[4] = Ext Message Header [15:8]
        ScalerSetByte_EXINT(PFA_53_TCPC_0_TX_BUFFER_3 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), g_pucTypeCTcpmPdDataObj_EXINT[1]);
        ScalerSetByte_EXINT(PFA_54_TCPC_0_TX_BUFFER_4 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), g_pucTypeCTcpmPdDataObj_EXINT[0]);

        // ucTxBuffer[5] = Data Block_0
        // ucTxBuffer[6] = Data Block_1
        for(BYTE ucLoopIndex = 0; ucLoopIndex < (ucTxByteCnt - 4); ucLoopIndex++)
        {
            ScalerSetByte_EXINT(PFA_55_TCPC_0_TX_BUFFER_5 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + ucLoopIndex, g_pucTypeCTcpmPdDataObj_EXINT[2 + ucLoopIndex]);
        }
    }

    // 3. Set Tx Length [0xFA42] [4:0] tcpc_0_tx_len
    ScalerSetBit_EXINT(PFA_42_TCPC_0_TRANSMIT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucTxByteCnt);

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
    if(ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _ENABLE) == _FAIL)
    {
        return;
    }

    // 4. Write TCPC Data by TCPM HW IIC
    ScalerTypeCTcpmHwIICWrite_EXINT0(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)_TCPM_TCPCI_REG_TX_BUF, ucTxByteCnt + 1, (BYTE *)(&pucTxBuffer[0]));

    // 5. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);

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
void ScalerTypeCTcpmTcpciSetTransmit_EXINT0(BYTE ucPortIndex, BYTE ucTransmitInfo)
{
#if(_HW_TCPM_SUPPORT == _ON)
#if(_HW_TCPM_TX_AUTO_CTRL == _ON)

    // 1. Set Transmit
    ScalerSetByte_EXINT(PFA_6F_TCPC_0_TRANSMIT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ucTransmitInfo);

    // 2. Start Transmit Tx Buffer + Transmit (Do Not Need to Enable tcpc_0_auto_tx_irq_en)
    // [0xFA42] [7] tcpc_0_auto_tx_en, [6] tcpc_0_auto_tx_irq, [5] tcpc_0_auto_tx_irq_en
    ScalerSetBit_EXINT(PFA_42_TCPC_0_TRANSMIT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));

#else

    // 1. Set Transmit
    ScalerTypeCTcpmTcpciSetByte_EXINT0(ucPortIndex, _TCPM_TCPCI_REG_TRANSMIT, ucTransmitInfo);

#endif // End of #if(_HW_TCPM_TX_AUTO_CTRL == _ON)

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;
    ucTransmitInfo = ucTransmitInfo;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Type C TCPM Get TCPCI Rx Buffer
// Input Value  : ucPortIndex
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmTcpciGetRxBuffer_EXINT0(BYTE ucPortIndex)
{
#if(_HW_TCPM_SUPPORT == _ON)

#if(_HW_TCPM_RX_MSG_AUTO_CTRL == _ON)

    // 1. Get READABLE_BYTE_CNT
    g_pucTypeCTcpmRxBuffer_EXINT[0] = ScalerGetByte_EXINT(PFA_70_TCPC_0_RX_BUFFER_0 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex));

    // 2. Get Reset Rx Buffer
    for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TCPM_RX_BYTE_CNT(); ucLoopIndex++)
    {
        g_pucTypeCTcpmRxBuffer_EXINT[1 + ucLoopIndex] = ScalerGetByte_EXINT(PFA_71_TCPC_0_RX_BUFFER_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex) + ucLoopIndex);
    }

#else

    //------------------------------------
    // Rx Buffer[0]     : READABLE_BYTE_CNT
    // Rx Buffer[1]     : FRAME_TYPE
    // Rx Buffer[2]     : MSG_HEADER_L
    // Rx Buffer[3]     : MSG_HEADER_H
    // Rx Buffer[4..7]  :  DATA_OBJECT_0 [7:0], [15:8], [23:16], [31:24]
    // Rx Buffer[8..11] : DATA_OBJECT_1 [7:0], [15:8], [23:16], [31:24]
    //------------------------------------

    // 1. Set Fw Busy Flag to Prevent Interrupting by HW
    if(ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _ENABLE) == _FAIL)
    {
        return;
    }

    // 2. Get TCPCI Rx Buffer 0x30~34 READABLE_BYTE_CNT + FRAME_TYPE + Message_Header_L + Message_Header_H
    ScalerTypeCTcpmHwIICRead_EXINT0(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)_TCPM_TCPCI_REG_RX_BUF, 4, g_pucTypeCTcpmRxBuffer_EXINT);

    // 3. For Data/Exteded Message, Readable Byte Cnt > 3 (Frame Type, Message_Header_L + Message_Header_H)
    // Read Reveived Message according to READABLE_BYTE_CNT
    if(GET_TCPM_RX_BYTE_CNT() > 3)
    {
        BYTE ucDataLength = 0;
        BYTE ucTransactionIndex = 0;
        BYTE pucReadData[(_MAX_DATA_OBJ_CNT * 4) + 4];

        // Frame Type (1-Byte) + Message Header (2-Byte) Has Been Read
        ucDataLength = GET_TCPM_RX_BYTE_CNT() - 3;

        // --------------------------------------------------------
        // For On-Semi TCPC Only
        // --------------------------------------------------------
        // On-Semi Do Not Support TCPCI Re-Read Mechanism, Use Offset to Get Rx Buffer Instead
        if(GET_TCPM_TCPC_TYPE(ucPortIndex) == _TCPC_ON_SEMI)
        {
            ucTransactionIndex = 4;
        }

        ScalerTypeCTcpmHwIICRead_EXINT0(ucPortIndex, GET_TCPM_TCPC_SLAVE_ADDR(ucPortIndex), 1, (BYTE)_TCPM_TCPCI_REG_RX_BUF + ucTransactionIndex, ucDataLength, pucReadData);

        // Copy Read Data (ucDataLength) to Global Rx Buffer ([3:0] Already Has Data)
        memcpy((BYTE *)(&g_pucTypeCTcpmRxBuffer_EXINT[4]), pucReadData, ucDataLength);
    }

    // 4. Clear Fw Busy Flag
    ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);

#endif // End of #if(_HW_TCPM_TX_AUTO_CTRL == _ON)

#else

    // [TO-DO] Dennis : TypeC HW IIC Flow
    ucPortIndex = ucPortIndex;

#endif // End of #if(_HW_TCPM_SUPPORT == _ON)
}

#if(_HW_TCPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by TCPM IIC
// Input Value  : ucPortIndex, ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucReadArray
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmHwIICRead_EXINT0(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray)
{
    BYTE ucI = 0;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _HW_TCPM_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    // Reset(Block) IIC module
    ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            ScalerSetBit_EXINT(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), 0x00);

            // Set no repeat start
            ScalerSetBit_EXINT(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _READ));

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit_EXINT(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit_EXINT(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _WRITE));

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _READ));

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit_EXINT(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit_EXINT(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _WRITE));

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _READ));

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucDataLength - 1) << 1));

    // IIC command Start
    ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT6, _BIT6);

    // Wait until Master Receive Complete
    if(ScalerTimerPollingFlagProc_EXINT0(4, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT1, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = ScalerGetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex));
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetByte_EXINT(PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by TypeC IIC
// Input Value  : ucPortIndex, ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucWriteArray
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmHwIICWrite_EXINT0(BYTE ucPortIndex, BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray)
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
    ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit_EXINT(PFA_02_I2CM_CR2 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit_EXINT(PFA_03_I2CM_CR3 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc_EXINT0(2, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (ucSlaveAddr | _WRITE));

    ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((ucDataLength - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (ucDataLength << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((ucDataLength + 1) << 1);

            break;

        default:

            break;
    }

    // Load data to IIC buffer for transmission
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        ScalerSetByte_EXINT(PFA_09_I2CM_TD + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), pucWriteArray[ucI]);
    }

    // Send IIC command Start
    ScalerSetByte_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (0xC0 + ucTempLength));

    // Wait until Master Transmit Complete
    if(ScalerTimerPollingFlagProc_EXINT0(4, (PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT0, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit_EXINT(PFA_00_I2CM_CR0 + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Clear all flags
    ScalerSetByte_EXINT(PFA_08_I2CM_SR + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Enable/Disable TCPM Alert Detect
// Input Value  : ucPortIndex, bAction
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmAlertDetCtrl_EXINT0(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ENABLE)
    {
        // 1. If alert_det_en = 0, Polling alert_status = 1 before Enable alert_det_en
        if(ScalerGetBit_EXINT(PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), _BIT7) == 0x00)
        {
            // Polling [0xFA20] [4] alert_status = 1 (Alert High)
            if(ScalerTimerPollingFlagProc_EXINT0(1, (PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex)), _BIT0, _TRUE) == _FALSE)
            {
                return;
            }
        }

        // Set [0xFA20] [7] alert_det_en = 1 & [3:1] alert_det_deb = b000
        ScalerSetBit_EXINT(PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT3 | _BIT2 | _BIT1), _BIT7);
    }
    else
    {
        // 1. Set FW Busy Flag
        if(ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _ENABLE) == _FAIL)
        {
            return;
        }

        // 2. Disable [0xFA20] [7] alert_det_en
        ScalerSetBit_EXINT(PFA_20_TCPC_0_ALERT_DETECT + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~_BIT7, 0x00);

        // 3. Clear FW Busy Flag
        ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);
    }
}

//--------------------------------------------------
// Description  : Type C TCPM FW Busy Flag Control
// Input Value  : ucPortIndex, bAction
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
bit ScalerTypeCTcpmFwBusyCtrl_EXINT0(BYTE ucPortIndex, bit bAction)
{
    if(bAction == _ENABLE)
    {
        // Polling [0xFA11] [4] hw_i2c_busy = 0
        if(ScalerTimerPollingFlagProc_EXINT0(2, (PFA_11_TCPM_BUSY + GET_TCPM_IIC_HW_SHIFT(ucPortIndex)), _BIT4, _FALSE) == _FALSE)
        {
            return _FAIL;
        }

        // Set [0xFA11] [5] fw_i2c_busy to Prevent Interruptions from Exint & WDINT
        ScalerSetBit_EXINT(PFA_11_TCPM_BUSY + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT5, _BIT5);

        return _SUCCESS;
    }
    else
    {
        // Clear [0xFA11] [5] fw_i2c_busy
        ScalerSetBit_EXINT(PFA_11_TCPM_BUSY + GET_TCPM_IIC_HW_SHIFT(ucPortIndex), ~_BIT5, 0x00);

        return _SUCCESS;
    }
}

//--------------------------------------------------
// Description  : Type C TCPM Alert INT Control
// Input Value  : ucPortIndex, usAlertType, b1Action
// Output Value : None
//--------------------------------------------------
void ScalerTypeCTcpmAlertIntControl_EXINT0(BYTE ucPortIndex, WORD usAlertType, bit b1Action)
{
    if((usAlertType & _TCPM_TCPCI_ALERT_CC_STATUS) == _TCPM_TCPCI_ALERT_CC_STATUS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable CC Status IRQ : [0xFA32] [1] alert_cs_irq, [0] alert_cs_irq_en
            ScalerSetBit_EXINT(PFA_32_TCPC_0_CS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable CC Status IRQ : [0xFA32] [1] alert_cs_irq, [0] alert_cs_irq_en
            ScalerSetBit_EXINT(PFA_32_TCPC_0_CS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_PWR_STATUS) == _TCPM_TCPCI_ALERT_PWR_STATUS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Power Status IRQ : [0xFA34] [1] alert_ps_irq, [0] alert_ps_irq_en
            ScalerSetBit_EXINT(PFA_34_TCPC_0_PS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Power Status IRQ : [0xFA34] [1] alert_ps_irq, [0] alert_ps_irq_en
            ScalerSetBit_EXINT(PFA_34_TCPC_0_PS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_FAULT) == _TCPM_TCPCI_ALERT_FAULT)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Fault Status IRQ : [0xFA36] [1] alert_fault_irq, [0] alert_fault_irq_en
            ScalerSetBit_EXINT(PFA_36_TCPC_0_FS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Fault Status IRQ : [0xFA36] [1] alert_fault_irq, [0] alert_fault_irq_en
            ScalerSetBit_EXINT(PFA_36_TCPC_0_FS_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_EXT_STATUS) == _TCPM_TCPCI_ALERT_EXT_STATUS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Extended Status IRQ : [0xFA38] [1] alert_ext_stat_irq, [0] alert_ext_stat_irq_en
            ScalerSetBit_EXINT(PFA_38_TCPC_0_ES_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Extended Status IRQ : [0xFA38] [1] alert_ext_stat_irq, [0] alert_ext_stat_irq_en
            ScalerSetBit_EXINT(PFA_38_TCPC_0_ES_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_ALERT_EXT) == _TCPM_TCPCI_ALERT_ALERT_EXT)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Alert Extended IRQ : [0xFA3A] [1] alert_alert_ext_irq, [0] alert_alert_ext_irq_en
            ScalerSetBit_EXINT(PFA_3A_TCPC_0_ALERT_EXT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Alert Extended IRQ : [0xFA3A] [1] alert_alert_ext_irq, [0] alert_alert_ext_irq_en
            ScalerSetBit_EXINT(PFA_3A_TCPC_0_ALERT_EXT_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_VENDOR_DEF) == _TCPM_TCPCI_ALERT_VENDOR_DEF)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Vendor Define IRQ : [0xFA3C] [1] alert_vendor_def_irq, [0] alert_vendor_def_irq_en
            ScalerSetBit_EXINT(PFA_3C_TCPC_0_VENDOR_DEF_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Vendor Define IRQ : [0xFA3C] [1] alert_vendor_def_irq, [0] alert_vendor_def_irq_en
            ScalerSetBit_EXINT(PFA_3C_TCPC_0_VENDOR_DEF_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_VBUS_ALRM_H) == _TCPM_TCPCI_ALERT_VBUS_ALRM_H)
    {
        if(b1Action == _ENABLE)
        {
            // Enable High-Voltage Alarm IRQ : [0xFA3F] [1] alert_valm_h_irq, [0] alert_valm_h_irq_en
            ScalerSetBit_EXINT(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable High-Voltage Alarm IRQ : [0xFA3F] [1] alert_valm_h_irq, [0] alert_valm_h_irq_en
            ScalerSetBit_EXINT(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_VBUS_ALRM_L) == _TCPM_TCPCI_ALERT_VBUS_ALRM_L)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Low-Voltage Alarm IRQ : [0xFA3F] [3] alert_valm_l_irq, [2] alert_valm_l_irq_en
            ScalerSetBit_EXINT(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Low-Voltage Alarm IRQ : [0xFA3F] [3] alert_valm_l_irq, [2] alert_valm_l_irq_en
            ScalerSetBit_EXINT(PFA_3F_TCPC_0_VALM_HL_AUTO_CTRL + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_RCV_SOP) == _TCPM_TCPCI_ALERT_RX_RCV_SOP)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Rx Msg IRQ : [0xFA48] [3] alert_rx_msg_irq, [2] alert_rx_msg_irq_en
            ScalerSetBit_EXINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Rx Msg IRQ : [0xFA48] [3] alert_rx_msg_irq, [2] alert_rx_msg_irq_en
            ScalerSetBit_EXINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_SOP_BEGIN) == _TCPM_TCPCI_ALERT_RX_SOP_BEGIN)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Rx Bgn IRQ : [0xFA48] [1] alert_rx_bgn_irq, [0] alert_rx_bgn_irq_en
            ScalerSetBit_EXINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Rx Bgn IRQ : [0xFA48] [1] alert_rx_bgn_irq, [0] alert_rx_bgn_irq_en
            ScalerSetBit_EXINT(PFA_48_TCPC_0_RX_MSG_AUTO_CTRL_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_HRST) == _TCPM_TCPCI_ALERT_RX_HRST)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Hard Reset IRQ : [0xFA43] [7] alert_hrst_irq, [6] alert_hrst_irq_en
            ScalerSetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), (_BIT7 | _BIT6));
        }
        else
        {
            // Disable Hard Reset IRQ : [0xFA43] [7] alert_hrst_irq, [6] alert_hrst_irq_en
            ScalerSetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT7);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_TX_FAIL) == _TCPM_TCPCI_ALERT_TX_FAIL)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Tx Fail IRQ : [0xFA43] [5] alert_tx_fail_irq, [4] alert_tx_fail_irq_en
            ScalerSetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), (_BIT5 | _BIT4));
        }
        else
        {
            // Disable Tx Fail IRQ : [0xFA43] [5] alert_tx_fail_irq, [4] alert_tx_fail_irq_en
            ScalerSetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT5);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_TX_DISCARD) == _TCPM_TCPCI_ALERT_TX_DISCARD)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Tx Discard IRQ : [0xFA43] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Tx Discard IRQ : [0xFA43] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_TX_SUCCESS) == _TCPM_TCPCI_ALERT_TX_SUCCESS)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Tx Success IRQ : [0xFA43] [1] alert_tx_discard_irq, [0] alert_tx_discard_irq_en
            ScalerSetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Tx Success IRQ : [0xFA43] [1] alert_tx_discard_irq, [0] alert_tx_discard_irq_en
            ScalerSetBit_EXINT(PFA_43_TCPC_0_ALERT_RELATED_IRQ_1 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT7 | _BIT5 | _BIT3 | _BIT1 | _BIT0), _BIT1);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_RX_OVERFLOW) == _TCPM_TCPCI_ALERT_RX_OVERFLOW)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Rx Overflow IRQ : [0xFA44] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit_EXINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable Rx Overflow IRQ : [0xFA44] [3] alert_tx_discard_irq, [2] alert_tx_discard_irq_en
            ScalerSetBit_EXINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT2 | _BIT1), _BIT3);
        }
    }

    if((usAlertType & _TCPM_TCPCI_ALERT_SNK_DISC) == _TCPM_TCPCI_ALERT_SNK_DISC)
    {
        if(b1Action == _ENABLE)
        {
            // Enable Sink Disconnect IRQ : [0xFA44] [1] alert_snk_disc_irq, [0] alert_snk_disc_irq_en
            ScalerSetBit_EXINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
        {
            // Disable Sink Disconnect IRQ : [0xFA44] [1] alert_snk_disc_irq, [0] alert_snk_disc_irq_en
            ScalerSetBit_EXINT(PFA_44_TCPC_0_ALERT_RELATED_IRQ_2 + GET_TCPM_TCPC_HW_SHIFT(ucPortIndex), ~(_BIT3 | _BIT1 | _BIT0), _BIT1);
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
bit ScalerTypeCTcpmPmicIICRead_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex_EXINT0(enumTypeCPcbPort);
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
        if(ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _ENABLE) == _FAIL)
        {
            return _FAIL;
        }

        // 2. Read PMIC Data by TCPM HW IIC
        if(ScalerTypeCTcpmHwIICRead_EXINT0(ucPortIndex, ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray) == _FAIL)
        {
            // Clear Fw Busy Flag
            ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);

            return _FAIL;
        }

        // 3. Clear Fw Busy Flag
        ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);
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
bit ScalerTypeCTcpmPmicIICWrite_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray)
{
    BYTE ucPortIndex = ScalerTypeCTcpmGetPortIndex_EXINT0(enumTypeCPcbPort);
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
        if(ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _ENABLE) == _FAIL)
        {
            return _FAIL;
        }

        // 2. Write PMIC Data by TCPM HW IIC
        if(ScalerTypeCTcpmHwIICWrite_EXINT0(ucPortIndex, ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
        {
            // Clear Fw Busy Flag
            ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);

            return _FAIL;
        }

        // 3. Clear Fw Busy Flag
        ScalerTypeCTcpmFwBusyCtrl_EXINT0(ucPortIndex, _DISABLE);
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
void ScalerTypeCTcpmPmicReset_EXINT0(BYTE ucPortIndex)
{
    EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];

    // ========================================================
    // Reset HW Setting
    // ========================================================
    ExternalDeviceInterfaceTypeCPmicUnattachReset_EXINT0(enumTypeCPcbPort);

    // ========================================================
    // Clear Flag and Reset Value
    // ========================================================

    // Reset PMIC Output Type
    SET_TCPM_PMIC_OUTPUT_MODE_STATUS(ucPortIndex, _PD_NONE_SETTING_PDO);

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    if (GET_TCPM_PMIC_OCP_PROTECT_METHOD(ucPortIndex) == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
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
bit ScalerTypeCTcpmPmicSetting_EXINT0(BYTE ucPortIndex, bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent)
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
        ScalerTypeCTcpmPmicSwitchControl_EXINT0(ucPortIndex, _ON, bPowerDirection);

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
                if(ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumDirection, enumPdoType) == _TYPE_C_PMIC_CONTROL_FAIL)
                {
                    return _FAIL;
                }
            }
#endif
            SET_TCPM_PMIC_OUTPUT_MODE_STATUS(ucPortIndex, enumPdoType);
        }

        enumResult = ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumDirection, usVoltage, usCurrent);
    }
    else
    {
        // Reset PMIC Output Type
        SET_TCPM_PMIC_OUTPUT_MODE_STATUS(enumPdoType, enumPdoType);

        enumResult = ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0(enumTypeCPcbPort);
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
bit ScalerTypeCTcpmPmicVbusDischarge_EXINT0(BYTE ucPortIndex, bit bEn)
{
    EnumTypeCPmicDischarge enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;

    if(bEn == _ON)
    {
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_ENABLE;
    }
    else
    {
        ScalerTypeCTcpmPmicSwitchControl_EXINT0(ucPortIndex, _OFF, _PD_POWER_SNK);
        enumDischarge = _TYPE_C_PMIC_DISCHARGE_DISABLE;
    }

    if(ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], enumDischarge) == _TYPE_C_PMIC_CONTROL_SUCCESS)
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
bit ScalerTypeCTcpmPmicSwitchControl_EXINT0(BYTE ucPortIndex, bit bEn, bit bPowerDirection)
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


    if(ExternalDeviceInterfaceTypeCPmicSwitchControl_EXINT0(g_penumTypeCTcpmPort[ucPortIndex], enumSwitchControl, enumDirection) == _TYPE_C_PMIC_CONTROL_SUCCESS)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Read Output Status
// Input Value  : ucPortIndex
// Output Value : Output Mode (Fixed Voltage/PPS)
//--------------------------------------------------
EnumTypeCPmicOperationMode ScalerTypeCTcpmPmicReadPpsOperationModeStatus_EXINT0(BYTE ucPortIndex)
{
    EnumTypeCPcbPort enumTypeCPcbPort = g_penumTypeCTcpmPort[ucPortIndex];

    // Check GPIO status
    if(ScalerTypeCTcpmGetPmicAlertDetectStatus_EXINT0(enumTypeCPcbPort) == _TRUE)
    {
        if(ExternalDeviceInterfaceTypeCPmicReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort) == _TYPE_C_PMIC_CC_MODE_OPERATION)
        {
            SET_TCPM_PMIC_OMF_INFO(ucPortIndex, _TYPE_C_PMIC_CC_MODE_OPERATION);
        }
        else
        {
            SET_TCPM_PMIC_OMF_INFO(ucPortIndex, _TYPE_C_PMIC_CV_MODE_OPERATION);
        }
    }

    return GET_TCPM_PMIC_OMF_INFO(ucPortIndex);
}

//--------------------------------------------------
// Description  : Get PMIC alert detect status
// Input Value  : enumTypeCPcbPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTypeCTcpmGetPmicAlertDetectStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    bit bPinCheck = _FALSE;

    // Get GPIO status
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
            bPinCheck = (PCB_D0_PMIC_ALERT_DETECT() == _D0_PMIC_ALERT_ON);
            break;

        case _D1_TYPE_C_PORT:
            bPinCheck = (PCB_D1_PMIC_ALERT_DETECT() == _D1_PMIC_ALERT_ON);
            break;

        case _D2_TYPE_C_PORT:
            bPinCheck = (PCB_D2_PMIC_ALERT_DETECT() == _D2_PMIC_ALERT_ON);
            break;

        case _P0_TYPE_C_PORT:
            bPinCheck = (PCB_P0_PMIC_ALERT_DETECT() == _P0_PMIC_ALERT_ON);
            break;

        case _P1_TYPE_C_PORT:
            bPinCheck = (PCB_P1_PMIC_ALERT_DETECT() == _P1_PMIC_ALERT_ON);
            break;

        case _P2_TYPE_C_PORT:
            bPinCheck = (PCB_P2_PMIC_ALERT_DETECT() == _P2_PMIC_ALERT_ON);
            break;

        case _P3_TYPE_C_PORT:
            bPinCheck = (PCB_P3_PMIC_ALERT_DETECT() == _P3_PMIC_ALERT_ON);
            break;

        case _P4_TYPE_C_PORT:
            bPinCheck = (PCB_P4_PMIC_ALERT_DETECT() == _P4_PMIC_ALERT_ON);
            break;

        case _ADAPTOR_TYPE_C_PORT:
            bPinCheck = (PCB_ADAPTOR_PMIC_ALERT_DETECT() == _ADAPTOR_PMIC_ALERT_ON);
            break;

        default:
            break;
    }

    return bPinCheck;
}
#endif // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PMIC_SUPPORT == _ON)
#endif // End of #if(_PORT_CTRL_TCPM_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
