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
// ID Code      : ScalerTypeC1Cc_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeC1Cc/ScalerTypeC1Cc.h"




#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))
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
// Description  : Interrupt Process For Type C
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcIntHandler_EXINT0(void)
{
    EnumTypeCPDState enumPdFwState = _PD_NO_RESPONSE;
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1);
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    EnumInputPort enumInputPort = ScalerTypeCPcbPortConvertToDx_EXINT0(enumTypeCPcbPort);
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    EnumOutputPort enumOutputPort = ScalerTypeCPcbPortConvertToPx_EXINT0(enumTypeCPcbPort);
#endif
    enumTypeCPcbPort = enumTypeCPcbPort;

    if(ScalerGetBit_EXINT(P6C_71_CC1_VCONN_OCP_INT, (_BIT5 | _BIT1)) == (_BIT5 | _BIT1))
    {   // (cc1_vconn_shutdown_irq == 1) && (cc1_vconn_shutdown_irq_en = _ENABLE)

        // Disable and Clear cc1_vconn_shutdown_irq
        ScalerSetBit_EXINT(P6C_71_CC1_VCONN_OCP_INT, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), _BIT1);

        if(GET_TYPE_C_1_CC_CONNECT_EN() == _TRUE)
        {
            // Turn Off Vconn (Should We Turn On Vconn Again Later?)
            ScalerTypeC1CcVconnControl_EXINT0(_OFF);

            ScalerTypeC1PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_VCONN_OCP);
        }
    }

    if(ScalerGetBit_EXINT(P6C_72_CC2_VCONN_OCP_INT, (_BIT5 | _BIT1)) == (_BIT5 | _BIT1))
    {   // (cc2_vconn_shutdown_irq == 1) && (cc2_vconn_shutdown_irq_en == _ENABLE)

        // Disable and Clear cc2_vconn_shutdown_irq
        ScalerSetBit_EXINT(P6C_72_CC2_VCONN_OCP_INT, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), _BIT1);

        if(GET_TYPE_C_1_CC_CONNECT_EN() == _TRUE)
        {
            // Turn Off Vconn (Should We Turn On Vconn Again Later?)
            ScalerTypeC1CcVconnControl_EXINT0(_OFF);

            ScalerTypeC1PdSetSystemEvent_EXINT0(_PD_SYS_EVENT_VCONN_OCP);
        }
    }

    if(ScalerGetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        // (hw_done_irq == 1) && (hw_done_irq_en == Enable)
        // [0x6C30] : [3] hw_done_irq, [2] hw_done_irq_en
        // Disable and Clear hw_done_irq
        ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);

        if(GET_TYPE_C_1_CC_CONNECT_EN() == _TRUE)
        {
            // Set CC to Initial Setting (Orientation / RA_EXIST / Turn on Vconn & Vbus, SNK Unattach Vth to 3.67V)
            if(ScalerTypeC1CcAttachedSetting_EXINT0(&enumPdFwState) == _TRUE)
            {
                // [0x6C30] : [3] hw_done_irq, [2] hw_done_irq_en, [1] hw_unattach_irq, [0] hw_unattach_irq_en
                if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_CC_DRP_PREFER() == _TYPE_C_DRP_TRY_SRC) && (GET_TYPE_C_1_CC_HW_STATE() == _TYPE_C_CC_HW_FSM_ATTACHED_SRC))
                {
                    // DRP Try Src FW Solution : Disable hw_done_irq and hw_unattach_irq
                    ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

                    // Since hw_try_wait_snk_irq is Already Enable, Only Set Attached.SRC to TryWait.Snk Flag
                    SET_TYPE_C_1_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK();
                }
                else
                {
                    // Disable hw_done_irq and Enable hw_unattach_irq
                    ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
                }

                // 1. Run PD if PD Function is Enabled
                if(GET_TYPE_C_1_PD_FUNCTION_EN() == _TRUE)
                {
                    // Set PD to Initail State (Data Role, Vconn Role, Initial State (_PD_SRC_START_UP or _PD_SNK_START_UP), ...)
                    ScalerTypeC1PdAttachedSetting_EXINT0(enumPdFwState);

                    // BMC Related Setting
                    ScalerTypeC1CcSetBMC_EXINT0(_ENABLE);
                }

                // Turn On U3 & Hub Function
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(enumInputPort, _TYPE_C_PIN_ASSIGNMENT_NONE, GET_TYPE_C_1_CC_ORIENTATION());
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(enumOutputPort, _TYPE_C_PIN_ASSIGNMENT_NONE, GET_TYPE_C_1_CC_ORIENTATION());
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

                SET_TYPE_C_1_CC_ATTACHED();
                SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_ATTACHED);
            }
            else
            {
                // If Connect to Unexpected Attached State, Transit to UNATTACH State
                SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_UNATTACH);
            }
        }
    }

    if(ScalerGetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {   // (hw_unattach_irq == 1) && (hw_unattach_irq_en == Enable)

        // [0x6C30] : [3] hw_done_irq, [1] hw_unattach_irq, [0] hw_unattach_irq_en
        // Disable and Clear hw_unattach_irq
        ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

        if(GET_TYPE_C_1_CC_CONNECT_EN() == _TRUE)
        {
            // Do Type C Unattach Flow (ADC / PD / CC Reset), and Start HW CC Connection Detection (Enable hw_done_irq_en)
            ScalerTypeC1CcUnattachFlow_EXINT0();
        }
    }

    if((ScalerGetBit_EXINT(P6C_2C_CC_R_CHG_INT, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6)) || (ScalerGetBit_EXINT(P6C_2C_CC_R_CHG_INT, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4)))
    {   // ((cc1_r_chg_irq == 1) && (cc1_r_chg_irq_en == Enable)) || ((cc2_r_chg_irq == 1) && (cc2_r_chg_irq_en == Enable))

        // Disable and Clear CC1/ CC2 Change IRQ
        ScalerSetBit_EXINT(P6C_2C_CC_R_CHG_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT7 | _BIT5));

        if(GET_TYPE_C_1_CC_CONNECT_EN() == _TRUE)
        {
            ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~_BIT5, 0x00);
            ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~_BIT5, _BIT5);
        }
    }

    if(ScalerGetBit_EXINT(P6C_58_DBCC_SNK_DET_COND, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // DRP Try Src FW Solution : (hw_try_wait_snk_irq == 1) && (hw_try_wait_snk_irq_en == Enable)
        // [0x6C58] : [1] hw_try_wait_snk_irq, [0] hw_try_wait_snk_irq_en
        // Clear and Disable hw_try_wait_snk_irq
        ScalerSetBit_EXINT(P6C_58_DBCC_SNK_DET_COND, ~(_BIT3 | _BIT1 | _BIT0), _BIT1);

        if(GET_TYPE_C_1_CC_CONNECT_EN() == _TRUE)
        {
            // [0x6C30] : [3] hw_done_irq, [2] hw_done_irq_en, [1] hw_unattach_irq, [0] hw_unattach_irq_en
            // Disable hw_done_irq and hw_unattach_irq
            ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

            // Set TryWait.Snk to Attached.SNK Flag
            SET_TYPE_C_1_CC_TRY_WAIT_SNK_STATE();

            // Do Unattach Flow When HW FSM Transition from Attached.SRC to TryWait.SNK
            if(GET_TYPE_C_1_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK() == _TRUE)
            {
                // Clr Attached.SRC to TryWait.Snk Flag
                CLR_TYPE_C_1_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK();

                CLR_TYPE_C_1_CC_ATTACHED();

                SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_CONNECTING);

                // Disable BMC Channel
                ScalerTypeC1CcSetBMC_EXINT0(_DISABLE);

                // Turn Off Vconn Power
                ScalerTypeC1CcVconnControl_EXINT0(_OFF);
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
                // Turn Off Vbus and Turn On Vbus Discharge
                ScalerTypeC1PmicSetting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
                ScalerTypeC1PmicVbusDischarge_EXINT0(_ON);

                // Active WD Timer Event To Detect if Vbus is Already Discharge to vSafe0V
                ScalerTimerWDActivateTimerEvent_EXINT0(_UNATTACH_VBUS_DISCHARGE_TIMER, _SCALER_WD_TIMER_EVENT_CC_1_CHECK_VBUS_0V);
#endif

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
                // [Eizo] SIC437A Customized Power Control : SRC/SNK Unattach
                ScalerTypeC1PmicSic437aUnattachProc_EXINT0(ScalerTypeC1PdGetPowerRole_EXINT0());
#endif
                // Reset PD
                ScalerTypeC1PdReset_EXINT0();

                // [0x6C0C] Connect CC1/2 Channel
                // [7] tpc_cc1_det_en = _TYPE_C_CONNECT
                // [6] tpc_cc2_det_en = _TYPE_C_CONNECT
                // [5] tpc_cc1_channel_en = _TYPE_C_CONNECT
                // [4] tpc_cc2_channel_en = _TYPE_C_CONNECT
                ScalerSetBit_EXINT(P6C_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            }

            // [0x6C5A/5B] Setting FW Mode Rd Resistor
            ScalerSetByte_EXINT(P6C_5A_CC_FW_CC1_Z_CFG, _BIT7);
            ScalerSetByte_EXINT(P6C_5B_CC_FW_CC2_Z_CFG, _BIT7);

            // [0x6C30] Change to FW Mode to Detect Attach or Unattach
            // [7] tpc_cc_mode_sel = 0
            ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT7 | _BIT3 | _BIT1), 0x00);

            // Set Power Role for Detecting CC1/CC2 Resistor = SNK
            ScalerSetBit_EXINT(P6C_2B_CC_DIG_DET_R, ~_BIT7, _BIT7);

            // Set Vth2/Vth3 to 660mV/1230mV
            ScalerSetByte_EXINT(P6C_28_VTH_SEL, 0x00);

            // Set Double CC as SNK Detect Open-Open Enable Bit
            ScalerSetBit_EXINT(P6C_58_DBCC_SNK_DET_COND, ~(_BIT4 | _BIT3 | _BIT1), _BIT4);

            // Set De-Bounce Threshold For Open-Open ([1:0] tPDDebounce = b'01)
            ScalerSetBit_EXINT(P6C_55_DBCC_SNK_DB_SEL, ~(_BIT1 | _BIT0), _BIT0);

            // Set Double CC De-glitch
            ScalerSetBit_EXINT(P6C_50_DBCC_DGH_EN, ~_BIT0, _BIT0);
            ScalerSetByte_EXINT(P6C_51_DBCC_DGH_TH, ScalerGetByte_EXINT(P6C_05_CC1_DGH_LV));

            // [0x6C41/42] Clear & Enable dbcc_det_irq
            ScalerSetBit_EXINT(P6C_41_CC_FW_DET_INT, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT7);
            ScalerSetBit_EXINT(P6C_42_CC_FW_DET_INT_EN, ~_BIT7, _BIT7);

            // Unattach Condition : CC = Open + Open for tPDDebounce
            // Enable Both CC Detect Equal Condition
            ScalerSetBit_EXINT(P6C_40_CC_FW_DET_CTRL, ~_BIT7, _BIT7);

            // Attach Condition : After tCCDebounce & Vbus Detected
            // Active WD Timer Event To Detect Vbus 5V After tCCDebounce
            ScalerTimerWDActivateTimerEvent_EXINT0(110, _SCALER_WD_TIMER_EVENT_CC_1_DETECT_VBUS);
        }
    }

    if((ScalerGetBit_EXINT(P6C_41_CC_FW_DET_INT, _BIT7) == _BIT7) && (ScalerGetBit_EXINT(P6C_42_CC_FW_DET_INT_EN, _BIT7) == _BIT7))
    {
        // DRP Try Src FW Solution : When Both CC Detect Open-Open for tPDDebounce, Set HW State to Unattached.SNK
        // [0x6C41/42] Clear & Disable dbcc_det_irq
        ScalerSetBit_EXINT(P6C_41_CC_FW_DET_INT, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT7);
        ScalerSetBit_EXINT(P6C_42_CC_FW_DET_INT_EN, ~_BIT7, 0x00);

        if(GET_TYPE_C_1_CC_CONNECT_EN() == _TRUE)
        {
            // Cancel WDTimerEvent
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_CC_1_DETECT_VBUS);

            // Disable [adc1_comp_vbus_on_en]
            ScalerTypeCAdcOnOffCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _ON, _DISABLE);

            // Clear TryWait.Snk to Attached.SNK Flag
            CLR_TYPE_C_1_CC_TRY_WAIT_SNK_STATE();

            // [0x6C35] Set HW State to Unattached.SNK
            ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT6 | _BIT3 | _BIT1), 0x00);
            ScalerSetBit_EXINT(P6C_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

            // [0x6C30] : [7] tpc_cc_mode_sel, [6] hw_mode_fsm_rst, [3] hw_done_irq, [1] hw_unattach_irq
            // Change Back to HW Mode, Clear (hw_done_irq) & (hw_unattach_irq)
            ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT7 | _BIT6 | _BIT3 | _BIT1), (_BIT7 | _BIT6 | _BIT3 | _BIT1));

            // Do Type C Unattach Flow (ADC / PD / CC Reset), and Start HW CC Connection Detection (Enable hw_done_irq_en)
            ScalerTypeC1CcUnattachFlow_EXINT0();
        }
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Detect Rp to Transit from Attached.SNK to Unattached.SNK State
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcSnkDetRpCtrl_EXINT0(bit bAction)
{
    // Spec.: For (SNK & Not in PR_Swap Flow), Check if SRC-Rp is Removed, Transition to Unattached.SNK within 40ms
    // [0x6C37] [0] cc_det_rp_opt (0:Enable Detect Rp / 1:Disable Detect Rp)
    if(bAction == _ENABLE)
    {
        // HW FSM will Transit from Attached.SNK to Unattached.SNK when CC Open for tPDDebounce
        ScalerSetBit_EXINT(P6C_37_CC_HW_Z_CFG, ~_BIT0, 0x00);
    }
    else
    {
        ScalerSetBit_EXINT(P6C_37_CC_HW_Z_CFG, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Enable / Disable Vconn Power in Interrupt
// Input Value  : bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcVconnControl_EXINT0(bit bAction)
{
    if(bAction == _ON)
    {
        if(GET_TYPE_C_1_CC_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [0x6C72] Reset and Enable CC2 OCP IRQs
            // [2]cc2_vconn_prot_irq      = 1
            // [1]cc2_vconn_shutdown_irq  = 1
            // [0]cc2_vconn_on_irq        = 1
            ScalerSetBit_EXINT(P6C_72_CC2_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc2_vconn_prot_irq_en    = _DISABLE
            // [5] cc2_vconn_shutdown_irq_en= _ENABLE
            // [4] cc2_vconn_on_irq_en      = _DISABLE
            ScalerSetBit_EXINT(P6C_72_CC2_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT5);

            // [0x6C0D] Turn On CC2 Vconn Switch : [2]tpc_cc2_vconn_en= _ENABLE
            ScalerSetBit_EXINT(P6C_0D_TPC_OCP_CTRL, ~_BIT2, _BIT2);

            SET_TYPE_C_1_CC_VCONN_STATUS(_ON);
        }
        else if(GET_TYPE_C_1_CC_ORIENTATION() == _TYPE_C_ORIENTATION_FLIP)
        {
            // [0x6C71] Reset and Enable CC1 OCP IRQs
            // [2] cc1_vconn_prot_irq      = 1
            // [1] cc1_vconn_shutdown_irq  = 1
            // [0] cc1_vconn_on_irq        = 1
            ScalerSetBit_EXINT(P6C_71_CC1_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc1_vconn_prot_irq_en    = _DISABLE
            // [5] cc1_vconn_shutdown_irq_en= _ENABLE
            // [4] cc1_vconn_on_irq_en      = _DISABLE
            ScalerSetBit_EXINT(P6C_71_CC1_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT5);

            // [0x6C0D] Turn On CC1 Vconn Switch : [3] tpc_cc1_vconn_en= _ENABLE
            ScalerSetBit_EXINT(P6C_0D_TPC_OCP_CTRL, ~_BIT3, _BIT3);

            SET_TYPE_C_1_CC_VCONN_STATUS(_ON);
        }
    }
    else
    {
        // Disable CC1/CC2 Vconn IRQs
        ScalerSetByte_EXINT(P6C_71_CC1_VCONN_OCP_INT, 0x00);
        ScalerSetByte_EXINT(P6C_72_CC2_VCONN_OCP_INT, 0x00);

        // [0x6C0D] Turn Off Both CC1/2 Vconn Switch : [3:2] tpc_cc1/2_vconn_en= _DISABLE
        ScalerSetBit_EXINT(P6C_0D_TPC_OCP_CTRL, ~(_BIT3 | _BIT2), 0x00); // [0x6C0D] <3:2> : tpc_cc1/2_vconn_en = _DISABLE
        SET_TYPE_C_1_CC_VCONN_STATUS(_OFF);
    }
}
/*
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
//--------------------------------------------------
// Description  : Turn off Vconn in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcFWModeTurnOffVconn_EXINT0(void)
{
    // [WS116] Ellisys FW Solution, Turn off Vconn below 0.8V within 35ms
    if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
    {
        // 1. [0x6C5A/5B] Setting FW Mode Rp Resistor (36K / 12K / 4.7K) and Vconn pin to Rd
        if(GET_TYPE_C_1_CC_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            if(ScalerGetBit_EXINT(P6C_37_CC_HW_Z_CFG, (_BIT7 | _BIT6)) == 0x00)
            {
                // Setting Rp 36K
                ScalerTypeC1CcFWModeSetResistor(_TYPE_C_PIN_CC1, _TYPE_C_FW_MODE_RP_DEF);
            }
            else if(ScalerGetBit_EXINT(P6C_37_CC_HW_Z_CFG, (_BIT7 | _BIT6)) == _BIT6)
            {
                // Setting Rp 12K
                ScalerTypeC1CcFWModeSetResistor(_TYPE_C_PIN_CC1, _TYPE_C_FW_MODE_RP_1_5);
            }
            else if(ScalerGetBit_EXINT(P6C_37_CC_HW_Z_CFG, (_BIT7 | _BIT6)) == _BIT7)
            {
                // Setting Rp 4.7K
                ScalerTypeC1CcFWModeSetResistor(_TYPE_C_PIN_CC1, _TYPE_C_FW_MODE_RP_3_0);
            }

            // Assert Rd to ensure Vconn Voltage below 0.8V
            ScalerTypeC1CcFWModeSetResistor(_TYPE_C_PIN_CC2, _TYPE_C_FW_MODE_RD);
        }
        else if(GET_TYPE_C_1_CC_ORIENTATION() == _TYPE_C_ORIENTATION_FLIP)
        {
            if(ScalerGetBit_EXINT(P6C_37_CC_HW_Z_CFG, (_BIT7 | _BIT6)) == 0x00)
            {
                // Setting Rp 36K
                ScalerTypeC1CcFWModeSetResistor(_TYPE_C_PIN_CC2, _TYPE_C_FW_MODE_RP_DEF);
            }
            else if(ScalerGetBit_EXINT(P6C_37_CC_HW_Z_CFG, (_BIT7 | _BIT6)) == _BIT6)
            {
                // Setting Rp 12K
                ScalerTypeC1CcFWModeSetResistor(_TYPE_C_PIN_CC2, _TYPE_C_FW_MODE_RP_1_5);
            }
            else if(ScalerGetBit_EXINT(P6C_37_CC_HW_Z_CFG, (_BIT7 | _BIT6)) == _BIT7)
            {
                // Setting Rp 4.7K
                ScalerTypeC1CcFWModeSetResistor(_TYPE_C_PIN_CC2, _TYPE_C_FW_MODE_RP_3_0);
            }

            // Assert Rd to ensure Vconn Voltage below 0.8V
            ScalerTypeC1CcFWModeSetResistor(_TYPE_C_PIN_CC1, _TYPE_C_FW_MODE_RD);
        }

        // 2. Switch to FW Mode with Resistor Aeesrted
        ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT7 | _BIT3 | _BIT1), 0x00);

        // 3. Set HW Mode FSM to Attached.SRC
        ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT6 | _BIT3 | _BIT1), 0x00);
        ScalerSetBit_EXINT(P6C_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
    }
}
#endif // End of #if(_TYPE_C_EMB_CTS_FLOW == _ON)
*/
//--------------------------------------------------
// Description  : Set Attached Role, Resistors on CC and Orientation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerTypeC1CcAttachedSetting_EXINT0(EnumTypeCPDState *penumPdFwState)
{
    bit bPass = _FALSE;

    switch(GET_TYPE_C_1_CC_HW_STATE())
    {
        case _TYPE_C_CC_HW_FSM_ATTACHED_SRC:

            *penumPdFwState = _PD_SRC_START_UP;

            if(ScalerGetBit_EXINT(P6C_33_CC_HW_FSM, (_BIT7)) == _BIT7)
            {   // Un-Flip : PD BMC Signal : CC1 / Vconn : CC2
                SET_TYPE_C_1_CC_ORIENTATION(_TYPE_C_ORIENTATION_UNFLIP);

                // Get [0x6C2A][3:0], Check if Ra is Presented on CC2
                if((ScalerGetBit_EXINT(P6C_2A_CC_ANA_DET_R, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) & (_BIT3 | _BIT2)) == 0x00)
                {
                    SET_TYPE_C_1_CC_RA_EXIST();
                }

                // [0x6C0C] Disconnect CC2 Detection Channel and CC2 Channel and BMC Channel
                // [6] tpc_cc2_det_en     = _TYPE_C_DISCONNECT
                // [4] tpc_cc2_channel_en = _TYPE_C_DISCONNECT
                // [2] tpc_cc2_en         = _TYPE_C_DISCONNECT (Not Needed)
                ScalerSetBit_EXINT(P6C_0C_TPC_CC_CTRL, ~(_BIT6 | _BIT4 | _BIT2), 0x00);

                bPass = _TRUE;
            }
            else
            {   // Flip : PD BMC Signal : CC2 / Vconn : CC1
                SET_TYPE_C_1_CC_ORIENTATION(_TYPE_C_ORIENTATION_FLIP);

                // Check if Ra is Presented on CC2
                if((ScalerGetBit_EXINT(P6C_2A_CC_ANA_DET_R, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) & (_BIT7 | _BIT6)) == 0x00)
                {
                    SET_TYPE_C_1_CC_RA_EXIST();
                }

                // [0x6C0C] Disconnect CC1 Detection Channel and CC1 Channel and BMC Channel
                // [7] tpc_cc1_det_en     = _TYPE_C_DISCONNECT
                // [5] tpc_cc1_channel_en = _TYPE_C_DISCONNECT
                // [3] tpc_cc1_en         = _TYPE_C_DISCONNECT (Not Needed)
                ScalerSetBit_EXINT(P6C_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT5 | _BIT3), 0x00);

                bPass = _TRUE;
            }

            if(GET_TYPE_C_1_CC_RA_EXIST() == _TRUE)
            {   // If SRC and Ra Exist, Turn On Vconn
                ScalerTypeC1CcVconnControl_EXINT0(_ON);
            }

            // Set OCP Threshlod
            SET_TYPE_C_1_OCP_CURRENT((WORD)(((DWORD)(GET_TYPE_C_1_CC_DEF_CUR()) * (DWORD)(GET_TYPE_C_1_OCP_RATIO(0))) / 100));

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
            // Disable Vbus Discharge
            ScalerTypeC1PmicVbusDischarge_EXINT0(_OFF);

            // Cancel WDTimerEvent (_UNATTACH_VBUS_DISCHARGE_TIMER)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_CC_1_CHECK_VBUS_0V);

            // If SRC, Turn On Vbus to vSafe5V (500 * 10mV) / Current = Default Current (10mA)
            ScalerTypeC1PmicSetting_EXINT0(_ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, 500, GET_TYPE_C_1_OCP_CURRENT(), _PD_PEAK_CUR_NONE);
#endif

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
            // [Eizo] SIC437A Customized Power Control : SRC/SNK Attach
            ScalerTypeC1PmicSic437aAttachProc_EXINT0(_TYPE_C_POWER_SRC);
#endif

            break;

        case _TYPE_C_CC_HW_FSM_ATTACHED_SNK:

            *penumPdFwState = _PD_SNK_START_UP;

            if(ScalerGetBit_EXINT(P6C_33_CC_HW_FSM, (_BIT7)) == _BIT7)
            {   // Un-Flip : PD BMC Signal : CC1 / Vconn : CC2
                SET_TYPE_C_1_CC_ORIENTATION(_TYPE_C_ORIENTATION_UNFLIP);

                // [0x6C0C] Disconnect CC2 Detection Channel and CC2 Channel and BMC Channel
                // [6] tpc_cc2_det_en     = _TYPE_C_DISCONNECT
                // [4] tpc_cc2_channel_en = _TYPE_C_DISCONNECT
                // [2] tpc_cc2_en         = _TYPE_C_DISCONNECT (Not Needed)
                ScalerSetBit_EXINT(P6C_0C_TPC_CC_CTRL, ~(_BIT6 | _BIT4 | _BIT2), 0x00);

                bPass = _TRUE;
            }
            else
            {   // Flip : PD BMC Signal : CC2 / Vconn : CC1
                SET_TYPE_C_1_CC_ORIENTATION(_TYPE_C_ORIENTATION_FLIP);

                // [0x6C0C] Disconnect CC1 Detection Channel and CC1 Channel and BMC Channel
                // [7] tpc_cc1_det_en     = _TYPE_C_DISCONNECT
                // [5] tpc_cc1_channel_en = _TYPE_C_DISCONNECT
                // [3] tpc_cc1_en         = _TYPE_C_DISCONNECT (Not Needed)
                ScalerSetBit_EXINT(P6C_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT5 | _BIT3), 0x00);

                bPass = _TRUE;
            }

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
            // [FW Sol. for _TYPE_C_5B_LS_ADC_GEN_1]
            // 1. Adjust 5Bit Vbus Off Threshold to 3.67V (Unit:10mV)
            ScalerTypeCAdcOnOffCompIntSetting_EXINT0(_TYPE_C_CHANNEL_1_VMON, _OFF, ScalerTypeCAdcCorrectionToRawData_EXINT0(_TYPE_C_CHANNEL_1_VMON, (367 / 10)));

            // 2. Write 1 Clear 5Bit LS_ADC Vbus Off IRQ and Enable IRQ_EN to Detect Unattach Event
            ScalerTypeCAdcOnOffCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _OFF, _ENABLE);
#else
            // Adjust Unattch Vth to 3.67V (Unit:10mV)
            ScalerTypeCAdcUnattachVthAdjust_EXINT0(_TYPE_C_CHANNEL_1_VMON, 500);
#endif

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
            // Disable Vbus Discharge
            ScalerTypeC1PmicVbusDischarge_EXINT0(_OFF);

            // Cancel WDTimerEvent (_UNATTACH_VBUS_DISCHARGE_TIMER)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_CC_1_CHECK_VBUS_0V);

            // Update Vbus Power Info to Support Sink OVP/UVP
            ScalerTypeC1PmicSetting_EXINT0(_ON, _PD_POWER_SNK, _PD_FIX_SUPPLY_PDO, 500, 0, _PD_PEAK_CUR_NONE);
#endif

#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON))
            // Start PMIC Protection
            ScalerTypeC1PmicProtectStart_EXINT0(_TYPE_C_POWER_SNK);
#endif

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
            // [Eizo] SIC437A Customized Power Control : SRC/SNK Attach
            ScalerTypeC1PmicSic437aAttachProc_EXINT0(_TYPE_C_POWER_SNK);
#endif

            break;

        case _TYPE_C_CC_HW_FSM_IDLE:
        case _TYPE_C_CC_HW_FSM_UNATTACHED_SNK:
        case _TYPE_C_CC_HW_FSM_ATTACHWAIT_SNK:
        case _TYPE_C_CC_HW_FSM_UNATTACHED_SRC:
        case _TYPE_C_CC_HW_FSM_ATTACHWAIT_SRC:
        case _TYPE_C_CC_HW_FSM_TRY_SRC:
        case _TYPE_C_CC_HW_FSM_TRY_WAIT_SNK:
        case _TYPE_C_CC_HW_FSM_TRY_SNK:
        case _TYPE_C_CC_HW_FSM_TRY_WAIT_SRC:
        case _TYPE_C_CC_HW_FSM_UNATTACHED_ACCESSORY:
        case _TYPE_C_CC_HW_FSM_ATTACH_WAIT_ACCESSORY:
        case _TYPE_C_CC_HW_FSM_POWER_ACCESSORY:
        case _TYPE_C_CC_HW_FSM_UNSUPORTED_ACCESSORY:
        case _TYPE_C_CC_HW_FSM_DEBUG_ACCESSORY_SNK:
        case _TYPE_C_CC_HW_FSM_AUDIO_ACCESSORY:
        case _TYPE_C_CC_HW_FSM_AUDIO_ACCESSORY_SRC:
        case _TYPE_C_CC_HW_FSM_DEBUG_ACCESSORY_SRC:
        default:
            // Not SRC nor SNK : ERROR !!!
            bPass = _FALSE;

            break;
    }

    return bPass;
}

//--------------------------------------------------
// Description  : Enable / Disable BMC Channel in CC Logic
// Input Value  : Event : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcSetBMC_EXINT0(bit bAction)
{
    if(bAction == _ENABLE)
    {
        // 1. [0x6C25] Auto Switch SRC/SNK BMC Vth_H/L When tpc_cc_mode_sel is HW Auto Mode, Enable BMC Rx and Set BMC Tx Controlled By HW
        // [7:6] bmc_rx/tx_en = b'10 (Enable Rx, [3] Tx Control By HW)
        ScalerSetBit_EXINT(P6C_25_BMC_TX_RX_CFG, ~(_BIT7 | _BIT6 | _BIT3), (_BIT7 | _BIT3));

        // 2. [0x6C0C] Connect CC1 or CC2 to BMC Channel
        if(GET_TYPE_C_1_CC_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [3] tpc_cc1_en = _TYPE_C_CONNECT
            // [2] tpc_cc2_en = _TYPE_C_DISCONNECT (Not Needed)
            ScalerSetBit_EXINT(P6C_0C_TPC_CC_CTRL, ~(_BIT3 | _BIT2), _BIT3);
        }
        else
        {
            // [3] tpc_cc1_en = _TYPE_C_DISCONNECT  (Not Needed)
            // [2] tpc_cc2_en = _TYPE_C_CONNECT
            ScalerSetBit_EXINT(P6C_0C_TPC_CC_CTRL, ~(_BIT3 | _BIT2), _BIT2);
        }
    }
    else
    {   // [0x6C25] Disable BMC Channel
        // [7] bmc_rx_en = _DISABLE
        // [6] bmc_tx_en = _DISABLE
        ScalerSetBit_EXINT(P6C_25_BMC_TX_RX_CFG, ~(_BIT7 | _BIT6), 0x00);

        // [0x6C0C] CC1/CC2 Disconnect to BMC Channel
        // [3] tpc_cc1_en = _TYPE_C_DISCONNECT
        // [2] tpc_cc2_en = _TYPE_C_DISCONNECT
        ScalerSetBit_EXINT(P6C_0C_TPC_CC_CTRL, ~(_BIT3 | _BIT2), 0x00);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Detect Vbus On/Off to transit State
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcVbusDetCtrl_EXINT0(bit bAction)
{
    // [0x6C34] Enable Vbus Detection
    // [7] vbus_det_dis    = _ENABLE
    if(bAction == _ENABLE)
    {
        ScalerSetBit_EXINT(P6C_34_CC_HW_STATE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
    }
    else
    {
        ScalerSetBit_EXINT(P6C_34_CC_HW_STATE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);
    }
}

//--------------------------------------------------
// Description  : Update & Return CC Pin Resistor (Only For CC Pin, Not Vconn Pin)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerTypeC1CcDetResistor_EXINT0(void)
{
    // Only Update Resistor of CC Pin, Not Vconn Pin (Flip : [7:4] CC1, Un-Flip : [3:0] CC2)
    if(GET_TYPE_C_1_CC_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
    {
        if(ScalerGetBit_EXINT(P6C_2A_CC_ANA_DET_R, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0xF0)
        {
            SET_TYPE_C_1_CC_CC1_R(_TYPE_C_DET_RP_3P0A);
        }
        else
        {
            // Setting Default Result = SinkTxNG (Rp 1.5A)
            SET_TYPE_C_1_CC_CC1_R(_TYPE_C_DET_RP_1P5A);
        }

        return GET_TYPE_C_1_CC_CC1_R();
    }
    else
    {
        if(ScalerGetBit_EXINT(P6C_2A_CC_ANA_DET_R, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x0F)
        {
            SET_TYPE_C_1_CC_CC2_R(_TYPE_C_DET_RP_3P0A);
        }
        else
        {
            // Setting Default Result = SinkTxNG (Rp 1.5A)
            SET_TYPE_C_1_CC_CC2_R(_TYPE_C_DET_RP_1P5A);
        }

        return GET_TYPE_C_1_CC_CC2_R();
    }
}

//--------------------------------------------------
// Description  : Get TypeC 1 CC HW State
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeC1CcGetHWState_EXINT0(void)
{
    return GET_TYPE_C_1_CC_HW_STATE();
}

//--------------------------------------------------
// Description  : Get TypeC 1 CC is in TryWait.SNK State
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeC1CcGetTryWaitSNKState_EXINT0(void)
{
    return GET_TYPE_C_1_CC_TRY_WAIT_SNK_STATE();
}

//--------------------------------------------------
// Description  : FW Mode TryWait.SNK to Attached.SNK
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcFWModeTrySrcAttached_EXINT0(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1);
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    EnumInputPort enumInputPort = ScalerTypeCPcbPortConvertToDx_EXINT0(enumTypeCPcbPort);
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    EnumOutputPort enumOutputPort = ScalerTypeCPcbPortConvertToPx_EXINT0(enumTypeCPcbPort);
#endif
    enumTypeCPcbPort = enumTypeCPcbPort;

    // Clr TryWait.Snk to Attached.SNK Flag
    CLR_TYPE_C_1_CC_TRY_WAIT_SNK_STATE();

    // Disable Double CC as SNK Detect Open-Open Enable Bit
    ScalerSetBit_EXINT(P6C_58_DBCC_SNK_DET_COND, ~(_BIT4 | _BIT3 | _BIT1), 0x00);

    // Disable Both CC Detect Equal Condition
    ScalerSetBit_EXINT(P6C_40_CC_FW_DET_CTRL, ~_BIT7, 0x00);

    // Popup Digital Detect Result
    ScalerSetBit_EXINT(P6C_2C_CC_R_CHG_INT, ~(_BIT7 | _BIT5 | _BIT0), _BIT0);

    // [0x6C2B] [5:3]: CC1 = Rp
    if((ScalerGetByte_EXINT(P6C_2B_CC_DIG_DET_R) & (_BIT5 | _BIT4 | _BIT3)) >= (_BIT4 | _BIT3))
    {
        // Un-Flip : PD BMC Signal : CC1 / Vconn : CC2
        SET_TYPE_C_1_CC_ORIENTATION(_TYPE_C_ORIENTATION_UNFLIP);

        // [0x6C0C] Disconnect CC2 Detection Channel and CC2 Channel and BMC Channel
        // [6] tpc_cc2_det_en     = _TYPE_C_DISCONNECT
        // [4] tpc_cc2_channel_en = _TYPE_C_DISCONNECT
        // [2] tpc_cc2_en         = _TYPE_C_DISCONNECT (Not Needed)
        ScalerSetBit_EXINT(P6C_0C_TPC_CC_CTRL, ~(_BIT6 | _BIT4 | _BIT2), 0x00);
    }
    else
    {
        // Flip : PD BMC Signal : CC2 / Vconn : CC1
        SET_TYPE_C_1_CC_ORIENTATION(_TYPE_C_ORIENTATION_FLIP);

        // [0x6C0C] Disconnect CC1 Detection Channel and CC1 Channel and BMC Channel
        // [7] tpc_cc1_det_en     = _TYPE_C_DISCONNECT
        // [5] tpc_cc1_channel_en = _TYPE_C_DISCONNECT
        // [3] tpc_cc1_en         = _TYPE_C_DISCONNECT (Not Needed)
        ScalerSetBit_EXINT(P6C_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT5 | _BIT3), 0x00);
    }

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
    // Disable Vbus Discharge
    ScalerTypeC1PmicVbusDischarge_EXINT0(_OFF);

    // Cancel WDTimerEvent (_UNATTACH_VBUS_DISCHARGE_TIMER)
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_CC_1_CHECK_VBUS_0V);

    // Update Vbus Power Info to Support Sink OVP/UVP
    ScalerTypeC1PmicSetting_EXINT0(_ON, _PD_POWER_SNK, _PD_FIX_SUPPLY_PDO, 500, 0, _PD_PEAK_CUR_NONE);
#endif

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
    // [FW Sol. for _TYPE_C_5B_LS_ADC_GEN_1]
    // 1. Adjust 5Bit Vbus Off Threshold to 3.67V (Unit:10mV)
    ScalerTypeCAdcOnOffCompIntSetting_EXINT0(_TYPE_C_CHANNEL_1_VMON, _OFF, ScalerTypeCAdcCorrectionToRawData_EXINT0(_TYPE_C_CHANNEL_1_VMON, (367 / 10)));

    // 2. Write 1 Clear 5Bit LS_ADC Vbus Off IRQ and Enable IRQ_EN to Detect Unattach Event
    ScalerTypeCAdcOnOffCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _OFF, _ENABLE);
#else
    // Adjust Unattch Vth to 3.67V (Unit:10mV)
    ScalerTypeCAdcUnattachVthAdjust_EXINT0(_TYPE_C_CHANNEL_1_VMON, 500);
#endif

#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON))
    // Start PMIC Protection
    ScalerTypeC1PmicProtectStart_EXINT0(_TYPE_C_POWER_SNK);
#endif

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
    // [Eizo] SIC437A Customized Power Control : SRC/SNK Attach
    ScalerTypeC1PmicSic437aAttachProc_EXINT0(_TYPE_C_POWER_SNK);
#endif

    // 1. Run PD if PD Function is Enabled
    if(GET_TYPE_C_1_PD_FUNCTION_EN() == _TRUE)
    {
        // Set PD to Initail State (Data Role, Vconn Role, Initial State (_PD_SRC_START_UP or _PD_SNK_START_UP), ...)
        ScalerTypeC1PdAttachedSetting_EXINT0(_PD_SNK_START_UP);

        // BMC Related Setting
        ScalerTypeC1CcSetBMC_EXINT0(_ENABLE);
    }

    // Turn On U3 & Hub Function
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(enumInputPort, _TYPE_C_PIN_ASSIGNMENT_NONE, GET_TYPE_C_1_CC_ORIENTATION());
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(enumOutputPort, _TYPE_C_PIN_ASSIGNMENT_NONE, GET_TYPE_C_1_CC_ORIENTATION());
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

    SET_TYPE_C_1_CC_ATTACHED();
    SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_ATTACHED);

    // [0x6C35] Set HW State to Attached.SNK
    ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT6 | _BIT3 | _BIT1), 0x00);
    ScalerSetBit_EXINT(P6C_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);

    // [0x6C30] : [7] tpc_cc_mode_sel, [6] hw_mode_fsm_rst, [3] hw_done_irq, [1] hw_unattach_irq, [0] hw_unattach_irq_en
    // Change Back to HW Mode, Clear (hw_done_irq) & (hw_unattach_irq), Enable hw_unattach_irq_en
    ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT7 | _BIT6 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT3 | _BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Type C Unattach Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcUnattachFlow_EXINT0(void)
{
    // Turn Off Vconn, if they are turned on when attached
    ScalerTypeC1CcVconnControl_EXINT0(_OFF);

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
    // Turn Off Vbus and Turn On Vbus Discharge
    ScalerTypeC1PmicSetting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
    ScalerTypeC1PmicVbusDischarge_EXINT0(_ON);

    // Active WD Timer Event To Detect if Vbus is Already Discharge to vSafe0V
    ScalerTimerWDActivateTimerEvent_EXINT0(_UNATTACH_VBUS_DISCHARGE_TIMER, _SCALER_WD_TIMER_EVENT_CC_1_CHECK_VBUS_0V);
#endif

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
    // [Eizo] SIC437A Customized Power Control : SRC/SNK Unattach
    ScalerTypeC1PmicSic437aUnattachProc_EXINT0(ScalerTypeC1PdGetPowerRole_EXINT0());
#endif

    // 1. Reset to Unattached State (From Attached Back to Unattach : ADC => PMIC => PD => CC)
    ScalerTypeCAdcUnattachReset_EXINT0(_EMB_TYPE_C_1);
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
    ScalerTypeC1PmicReset_EXINT0();
#endif
    ScalerTypeC1PdReset_EXINT0();
    // FW Solution : Samsung S8 Clear Flag When CC Unattach (Not Cleared When PD Reset)
    ScalerTypeC1PdClrInteropS8Flag_EXINT0();
    ScalerTypeC1CcUnattachReset_EXINT0();

    // 2. Setting For Connection
    ScalerTypeC1CcConnectionSet_EXINT0();

    // 3. State Transition
    SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_CONNECTING);

    // 4. [3] Clear IRQ hw_done_irq  = 1, Start HW CC Connection Detection
    ScalerTypeC1CcConnectionStart_EXINT0();
}

//--------------------------------------------------
// Description  : Type C Unattach Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcUnattachReset_EXINT0(void)
{
// =============================== Control By Power Delivery ??? ===============================
#if(_EMB_TYPE_C_1_PD3_FRSWAP_SUPPORT == _ON)
    // Disable FR_SWAP and FR_SWAP Bypass, if it is turned on when attached
    if((GET_TYPE_C_1_CC_SRC_FRSWAP_STATUS() == _ENABLE) || (GET_TYPE_C_1_CC_SNK_FRSWAP_STATUS() == _ENABLE))
    {
        ScalerTypeC1CcFastRoleSwapControl_EXINT0(_DISABLE);
        SET_TYPE_C_1_CC_SRC_FRSWAP_STATUS(_DISABLE);
        SET_TYPE_C_1_CC_SNK_FRSWAP_STATUS(_DISABLE);
    }
#endif
// =============================================================================================

    // Disable CC1/2 to BMC and Disable BMC Tx/Rx
    ScalerTypeC1CcSetBMC_EXINT0(_DISABLE);

    // Clear and Disable CC1/2_R_CHG_INT     [0x6C2C] = b'1010_0000
    ScalerSetBit_EXINT(P6C_2C_CC_R_CHG_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT7 | _BIT5));

    // CC Flags Reset
    CLR_TYPE_C_1_CC_ATTACHED();
    CLR_TYPE_C_1_CC_RA_EXIST();
    CLR_TYPE_C_1_CC_ERROR_RECOVERY();
    CLR_TYPE_C_1_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK();
    CLR_TYPE_C_1_CC_TRY_WAIT_SNK_STATE();
#if(_EMB_TYPE_C_1_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
    // Tool Not Show Warning UI when CC Unattach
    ScalerTypeC1CcToolWarningUIControl_EXINT0(_DISABLE);
#endif
}

//--------------------------------------------------
// Description  : Type C Setting For Connection (Connect Channels)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcConnectionSet_EXINT0(void)
{
    // Reset Rp Resistor Based On Default CC Current
#if(_TYPE_C_1_CC_CONNECT_MODE == _TYPE_C_HW_MODE)

    // [0x6C37][7:6] Setting SRC Rp Resistor (36K / 12K / 4.7K)
#if(_EMB_TYPE_C_1_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
    ScalerSetBit_EXINT(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_DEF << 6));
    SET_TYPE_C_1_CC_DEF_CUR(90);  // 90 * 10mA = 900mA
#elif(_EMB_TYPE_C_1_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
    ScalerSetBit_EXINT(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_1P5A << 6));
    SET_TYPE_C_1_CC_DEF_CUR(150); // 150 * 10mA = 1.5A
#else
    ScalerSetBit_EXINT(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_3P0A << 6));
    SET_TYPE_C_1_CC_DEF_CUR(300); // 300 * 10mA = 3.0A
#endif  // End of #if(_EMB_TYPE_C_1_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)

#endif  // End of #if(_TYPE_C_1_CC_CONNECT_MODE == _TYPE_C_HW_MODE)

    // [0x6C0C] Connect CC1/2 Channel
    // [7] tpc_cc1_det_en = _TYPE_C_CONNECT
    // [6] tpc_cc2_det_en = _TYPE_C_CONNECT
    // [5] tpc_cc1_channel_en = _TYPE_C_CONNECT
    // [4] tpc_cc2_channel_en = _TYPE_C_CONNECT
    ScalerSetBit_EXINT(P6C_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
    // [FW Sol. for _TYPE_C_5B_LS_ADC_GEN_1] Disable Vbus Detect
    ScalerTypeC1CcVbusDetCtrl_EXINT0(_DISABLE);
#else
    // Enable Vbus Detect
    ScalerTypeC1CcVbusDetCtrl_EXINT0(_ENABLE);
#endif
}

//--------------------------------------------------
// Description  : Clear IRQ hw_done_irq  = 1, Start HW CC Connection Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcConnectionStart_EXINT0(void)
{
#if(_TYPE_C_1_CC_CONNECT_MODE == _TYPE_C_HW_MODE)
    // [0x6C30] : [3] hw_done_irq, [2] hw_done_irq_en, [1] hw_unattach_irq, [0] hw_unattach_irq_en
    // Enable hw_done_irq, Disable hw_unattach_irq and Clear IRQs
    ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

    if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_CC_DRP_PREFER() == _TYPE_C_DRP_TRY_SRC))
    {
        // DRP Try Src FW Solution
        // [0x6C58] : [1] hw_try_wait_snk_irq, [0] hw_try_wait_snk_irq_en
        // Clear and Enable hw_try_wait_snk_irq
        ScalerSetBit_EXINT(P6C_58_DBCC_SNK_DET_COND, ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    }
#else
    // FW_MODE Reset
    ScalerSetBit_EXINT(P6C_30_CC_HW_MODE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
#endif
}

#if(_EMB_TYPE_C_1_PD3_FRSWAP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable / Disable Fast Role Swap
// Input Value  : bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcFastRoleSwapControl_EXINT0(bit bAction)
{
    if(bAction == _ENABLE)
    {
        if(ScalerTypeC1PdGetPowerRole_EXINT0() == _TYPE_C_POWER_SRC)
        {
            // [0x6C66] Clear and Enable SRC FR_SWAP INT
            // [7] src_frs_done_int    = 1
            // [6] src_frs_done_int_en = _ENABLE
            ScalerSetBit_EXINT(P6C_66_SRC_FRS_INT, ~_BIT7, _BIT7);
            ScalerSetBit_EXINT(P6C_66_SRC_FRS_INT, ~(_BIT7 | _BIT6), _BIT6);

            // [0x6C60] Turn On Source-Side FR_SWAP
            // [7] src_frs_en = _ENABLE
            ScalerSetBit_EXINT(P6C_60_FRS_CTRL, ~(_BIT7 | _BIT5), _BIT7);

            SET_TYPE_C_1_CC_SRC_FRSWAP_STATUS(_ENABLE);
        }
        else
        {
            // [0x6C67] Clear and Enable SNK FR_SWAP INT
            // [7] snk_frs_done_int    = 1
            // [6] snk_frs_done_int_en = _ENABLE
            // [3] snk_frs_tri_int     = 1
            // [2] snk_frs_tri_int_en  = _ENABLE
            ScalerSetBit_EXINT(P6C_67_SNK_FRS_INT, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));

            // [0x6C60] Turn On Sink-Side FR_SWAP
            // [6] snk_frs_en = _ENABLE
            ScalerSetBit_EXINT(P6C_60_FRS_CTRL, ~(_BIT6 | _BIT5), _BIT6);

            SET_TYPE_C_1_CC_SNK_FRSWAP_STATUS(_ENABLE);
        }   // End of if(ScalerTypeC1PdGetPowerRole() == _TYPE_C_POWER_SRC)
    }
    else
    {   // [0x6C66] Disable SRC FR_SWAP INT
        // [6] src_frs_done_int_en = _DISABLE
        ScalerSetBit_EXINT(P6C_66_SRC_FRS_INT, ~(_BIT7 | _BIT6), 0x00);

        // [0x6C67] Disable SNK FR_SWAP INT
        // [6] snk_frs_done_int_en = _DISABLE
        // [2] snk_frs_tri_int_en  = _DISABLE
        ScalerSetBit_EXINT(P6C_67_SNK_FRS_INT, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

        // [0x6C60] Turn Off Source/Sink-Side FR_SWAP
        // [7] src_frs_en = _DISABLE
        // [6] snk_frs_en = _DISABLE
        ScalerSetBit_EXINT(P6C_60_FRS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [0x6C68] Turn Off Fast-Role Swap
        ScalerSetBit_EXINT(P6C_68_FRS_BYPASS_MODE, ~_BIT7, 0x00);

        SET_TYPE_C_1_CC_SRC_FRSWAP_STATUS(_DISABLE);
        SET_TYPE_C_1_CC_SNK_FRSWAP_STATUS(_DISABLE);
    }
}
#endif  // End of #if(_EMB_TYPE_C_1_PD3_FRSWAP_SUPPORT == _ON)

#if(_EMB_TYPE_C_1_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
//--------------------------------------------------
// Description  : Enable Tool to Show Warning UI when We Provide Vbus > 5V
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcToolWarningUIControl_EXINT0(bit bAction)
{
    // Tool Usage : [0x6C66] [4] Used to Decide Whether Tool shall Show Warning UI when Disable Unattach HW Force Vbus Off Function([3]=0), 0 = Not Show UI, 1 = Show UI
    if(bAction == _ENABLE)
    {
        ScalerSetBit_EXINT(P6C_66_SRC_FRS_INT, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    }
    else
    {
        ScalerSetBit_EXINT(P6C_66_SRC_FRS_INT, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
}
#endif  // End of #if(_EMB_TYPE_C_1_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)

#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))

