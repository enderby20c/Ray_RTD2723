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
// ID Code      : ScalerTypeC1Cc.c No.0000
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
volatile StructTypeCEmbInfo g_stTypeC1CcInfo;
// BYTE g_pucTypeC1CcBackupTrimmingDataArray[9];

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : [Type C 1] CC Clk Setting (Always Use IOSC = 28MHz)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcClkSel(BYTE ucClockSel)
{
    if(ucClockSel == _IOSC_CLK)
    {
        // [0x6C00] [5:4] Clk Sel = IOSC (b'10) / [0x6C01] [3:0] sys_clk_div = b'0001
        ScalerSetBit(P6C_00_GLOBAL_CTL, ~(_BIT5 | _BIT4), _BIT5);
        ScalerSetBit(P6C_01_SYS_CLK_SRC_CFG, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        // [0x6C02] clk_1m_div = 28 (b'0001_1100)
        ScalerSetByte(P6C_02_1M_CLK_SRC_CFG, 0x1C);

        // [0x6C03-04] clk_1k_div = 1000 (b'11_11101000)
        ScalerSetBit(P6C_03_1K_CLK_SRC_CFG_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetByte(P6C_04_1K_CLK_SRC_CFG_1, 0xE8);
    }
}

//--------------------------------------------------
// Description  : Type C CC Logic AC_ON Initail
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcInitial(void)
{
    // ------------------- Type C Initial Setting -------------------

    // global_cc_en = _ENABLE
    ScalerSetBit(P6C_00_GLOBAL_CTL, ~_BIT7, _BIT7);

    // Setting Up CC1/2 De-glitch
    ScalerTypeC1CcSetDeglitch(_TYPE_C_CC1, 3, _TYPE_C_UNIT_100US);
    ScalerTypeC1CcSetDeglitch(_TYPE_C_CC2, 3, _TYPE_C_UNIT_100US);

#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
    // [RL6828 TID] SinkWaitCapTimer
    // For Sink-Only, Powered from Vbus Products, Detect Vbus means Source Already in Attached.SRC
    // Reduce tCCDebounce (2 ms) to Enter Attached.SNK Faster
    if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_SNK_ONLY)
    {
        ScalerTypeC1CcSetDebounce(_TYPE_C_CC, 2);
    }
    else
    {
        ScalerTypeC1CcSetDebounce(_TYPE_C_CC, 110);
    }
#else
    // Set tCCDebounce (150 ms) & tPDDebounce (20 ms), Not Set VS-Debounce
    ScalerTypeC1CcSetDebounce(_TYPE_C_CC, 110);
#endif
    ScalerTypeC1CcSetDebounce(_TYPE_C_PD, 10);

    // Load Trimming Value From E-fuse and Set up AIF Registers
    ScalerTypeC1CcLoadTrimming();

    // Setting Rising / Falling Time
    ScalerSetByte(P6C_23_BMC_TX_DRV_TM, 0x44);

    // Setting LPF
    ScalerSetBit(P6C_24_BMC_LPF, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x08);

    // Initial Flags & Status Setting
    CLR_TYPE_C_1_CC_ATTACHED();
    SET_TYPE_C_1_CC_SRC_FRSWAP_STATUS(_DISABLE);
    SET_TYPE_C_1_CC_SNK_FRSWAP_STATUS(_DISABLE);
    SET_TYPE_C_1_CC_VCONN_STATUS(_OFF);
    CLR_TYPE_C_1_RESET_FLAG();

    // Enable CC
    SET_TYPE_C_1_CC_CONNECT_EN();

    // ------------------- OCP Initial Setting -------------------

    // OCP Mode = HW Auto Mode
    ScalerSetBit(P6C_0D_TPC_OCP_CTRL, ~_BIT6, 0x00);

    // ocp_deg_cc1/2 = _ENABLE, ocp_vref_sel_cc1/2 = b'100 (470mA)
    ScalerSetByte(P6C_0E_TPC_OPC_CFG_0, 0xE4);

    // Escape Vltage = 4V, reg_opcadj_cc1 = 0
    ScalerSetBit(P6C_0F_TPC_OPC_CFG_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

    // OCP HW Auto Mode Timing Setting
    ScalerSetByte(P6C_73_VCONN_OCP_TIMER1, 0xBC);
    ScalerSetByte(P6C_74_VCONN_OCP_TIMER2, 0xFC);
    ScalerSetByte(P6C_75_VCONN_OCP_TIMER3, 0x41);
    ScalerSetByte(P6C_76_VCONN_OCP_TIMER4, 0xBC);
    ScalerSetByte(P6C_77_VCONN_OCP_TIMER5, 0xFC);

    // ----------------- HW CC FSM Vbus Signal Mux Initial Setting -----------------

#if(_HW_TYPE_C_LS_ADC_HW_VERSION != _TYPE_C_5B_LS_ADC_NONE)
#if((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3))
    // HW Vbus Signal Selection [0] = 5Bit LS_ADC (0: Select 5Bit LS_ADC Signal / 1: Select 10Bit SAR_ADC Signal)
    ScalerSetBit(P6C_3C_BMC_DET_1, ~(_BIT3 | _BIT0), 0x00);
#else
    // HW Vbus Signal Selection [0] = 10Bit SAR_ADC (0: Select 5Bit LS_ADC Signal / 1: Select 10Bit SAR_ADC Signal)
    ScalerSetBit(P6C_3C_BMC_DET_1, ~(_BIT3 | _BIT0), _BIT0);
#endif
#endif // End of #if(_HW_TYPE_C_LS_ADC_HW_VERSION != _TYPE_C_5B_LS_ADC_NONE)

    // ----------------- HW Mode Initial Setting -----------------

#if(_TYPE_C_1_CC_CONNECT_MODE == _TYPE_C_HW_MODE)

    // HW Mode Type-C Version Setting [7] (0:_TYPE_C 1_1 / 1:_TYPE_C 1_2)
    ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~_BIT7, _BIT7);

    // DRP Port Toggle Timing Setting (SRC/SNK/TrySRC/TrySNKWait)
    // [0x6C38] drp_hw_src_time = 40 ms (0x28)
    ScalerSetByte(P6C_38_CC_HW_DRP_SRC_TM, 0x28);

    // [0x6C39] drp_hw_snk_time = 40 ms (0x28)
    // [Workshop #114] if Lecroy (Type C Test) TD 4.7.6 Try.SNK DRP Connect SNKAS Test Still Fail, Modify P66_39_CC_HW_DRP_SNK_TM to 0x28(40ms) (Refer to RB:7787)
    ScalerSetByte(P6C_39_CC_HW_DRP_SNK_TM, 0x28);

    // [0x6C3A] [7:3] Try.SRC = 100ms / [2:0] Try.Wait = 400ms
    ScalerSetByte(P6C_3A_CC_HW_TRY_SRC_TM, (_BIT6 | _BIT5));

    // [0x6C35] [3:1] tTryTimeout  = 650 ms
    ScalerSetBit(P6C_35_CC_HW_STATE_TRANSIT, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);

    // ---------- HW Mode Accessory Support Setting ----------

    // [0x6C31] [2] hw_debug_sup_en
    // [0x6C3D] [2] hw_src_side_debug_sup_en
#if((_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_DEBUG) || (_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_DEBUG_POWER) || (_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_DEBUG_AUDIO) || (_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_ALL))
    ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~_BIT2, _BIT2);
    ScalerSetBit(P6C_3D_HW_DGH_EN, ~_BIT2, _BIT2);
#else
    ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~_BIT2, 0x00);
    ScalerSetBit(P6C_3D_HW_DGH_EN, ~_BIT2, 0x00);
#endif

    // [0x6C31] [1] hw_audio_sup_en
    // [0x6C3D] [3] hw_src_side_audio_sup_en
#if((_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_AUDIO) || (_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_AUDIO_POWER) || (_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_DEBUG_AUDIO) || (_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_ALL))
    ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~_BIT1, _BIT1);
    ScalerSetBit(P6C_3D_HW_DGH_EN, ~_BIT3, _BIT3);
#else
    ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~_BIT1, 0x00);
    ScalerSetBit(P6C_3D_HW_DGH_EN, ~_BIT3, 0x00);
#endif

    // [0x6C31] [0] hw_pwr_sup_en
#if((_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_POWER) || (_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_AUDIO_POWER) || (_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_DEBUG_POWER) || (_FW_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_ALL))
    ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~_BIT0, _BIT0);
#else
    ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~_BIT0, 0x00);
#endif

    // ---------- HW Mode FSM & BMC De-Glitch Setting ----------

    // [0x6C3D] Enable Setup Hold / Debounce Time
    ScalerSetBit(P6C_3D_HW_DGH_EN, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [0x6C3E] Deglitch HW State Transition = 3ms
    ScalerSetByte(P6C_3E_HW_DGH_TH, 0xC3);

    // [0x6C3F] Hold Time For HW Sync = 1 ms
    ScalerSetByte(P6C_3F_STABLE_TIMER_TH, 0x8A);

    // Enable Resistor Digital Detect Result(include cc1/2_r_chg_irq function and popup result)
    ScalerSetBit(P6C_2B_CC_DIG_DET_R, ~(_BIT6), _BIT6);

    // Vbus Threshold Control Option = Vbus Detection Has 2 Threshold (Use Vbus On Thr When in SNK State, Use Vbus Off Thr When in SRC State)
    ScalerSetBit(P6C_34_CC_HW_STATE_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT2));

    // [WS116] Lecroy TD.4.7.2 Try.SNK DRP Connect DRP Test, HW Solution to Disable vSafe0V Check from Unattached.SRC to AttachWait.SRC
    ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT1), (_BIT1));

#endif  // End of #if(_TYPE_C_CC_CONNECT_MODE == _TYPE_C_HW_MODE)

    // ----------------- Fast Role Swap Setting -----------------

#if(_EMB_TYPE_C_1_PD3_FRSWAP_SUPPORT == _ON)
    // Fast Role Swap CC Pin Select Mode = HW Mode
    ScalerSetBit(P6C_60_FRS_CTRL, ~(_BIT5 | _BIT4), 0x00);

    // CC Pin Voltage < 490mV Signal Deglitch
    ScalerSetByte(P6C_61_FRS_490MV_DGH, 0x41);

    // Vbus Voltage Drop Below Threshold Voltage Deglitch
    ScalerSetByte(P6C_62_FRS_VBUS_DGH, 0x01);

    // Timing For SRC to Drive Low When Sending FR_SWAP Signal (90us)
    ScalerSetBit(P6C_63_SRC_FRS_DRV_TM, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x09);

    // Timing For SNK to Recognize Drive Low Signal from SRC (CC Pin Vol. < 490mV for more than 50us)
    ScalerSetByte(P6C_64_SNK_FRS_DET_TM, 0x20);

    // Configre For SNK to Start Supply Vbus
    ScalerSetByte(P6C_65_SNK_FRS_VTH_MODE, _BIT6);

#endif  // End of #if(_EMB_TYPE_C_1_PD3_FRSWAP_SUPPORT == _ON)
}

#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
//--------------------------------------------------
// Description  : Type C CC Vbus Powered Sink Initial Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcVbusPoweredSnkInitial(void)
{
    // CC FW Initial
    ScalerTypeC1CcInitial();
    ScalerTypeC1PdInitial();
    ScalerTypeCAdcPortInitial(_EMB_TYPE_C_1);
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
    ScalerTypeC1PmicInitial();
#endif

    // CC FW Unattach Reset

    // 1. Reset to Unattached State (Initial to Unattach / Error Recovery : ADC => PMIC => PD => CC)
    ScalerTypeCAdcUnattachReset(_EMB_TYPE_C_1);
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
    ScalerTypeC1PmicReset();
#endif
    ScalerTypeC1PdReset();
    // FW Solution : Samsung S8 Clear Flag When CC Unattach (Not Cleared When PD Reset)
    ScalerTypeC1PdClrInteropS8Flag();
    ScalerTypeC1CcUnattachReset();

    // 2. Setting For Connection
    ScalerTypeC1CcConnectionSet();

    // 3. State Transition
    SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_CONNECTING);

    // 4. [3] Clear IRQ hw_done_irq  = 1, Start HW CC Connection Detection
    ScalerTypeC1CcConnectionStart();
}
#endif

//--------------------------------------------------
// Description  : CC Logic Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcHandler(void)
{
    switch(GET_TYPE_C_1_CC_FW_STATE())
    {
        case _TYPE_C_CC_EMB_FW_FSM_INITIAL:

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
            DebugMessageTypeC("O Type C State : INITIAL", GET_TYPE_C_1_CC_FW_STATE());
#endif
            ScalerTypeC1CcInitial();
            ScalerTypeC1PdInitial();
            ScalerTypeCAdcPortInitial(_EMB_TYPE_C_1);
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
            ScalerTypeC1PmicInitial();
#endif

            if((GET_TYPE_C_1_CC_AC_ON_RECONNECT() == _TRUE) && (ScalerTypeCAdcGetLocPowExist() == _TYPE_C_LOCAL_POWER_EXIST))
            {
                ScalerTypeC1CcFWModeDisconnect();
                ScalerTimerActiveTimerEvent(1000, _SCALER_TIMER_EVENT_CC_1_STATE_TO_UNATTACH);
            }
            else
            {
                ScalerTimerActiveTimerEvent(1, _SCALER_TIMER_EVENT_CC_1_STATE_TO_UNATTACH);
            }

#if(_EMB_TYPE_C_1_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
            // [MM1GENERAL-2282]
            // Tool Usage : [0x6C66] [3] Unattach HW Force Vbus Off Enable Control, 0 = Disble, 1 = Enable

            // Tool Usage : [0x6C66] [2] Unattach HW Force Vbus Off Control Type, 0 = BY_GPIO, 1 = BY_IIC
            // if [0x6C66] [2] = 1 (BY_IIC)  :
            // ------ IIC Flow ------
            // 1. Tool Set [0x7F90] [6] = 1 (Enable FRS IIC)
            // 2. Tool Enable Unattach HW Force Vbus Off Function : [0x6C68] [0] = 1 (Enable)

            // if [0x6C66] [2] = 0 (BY_GPIO) : Refer to [0x6C66] [1:0] to Execute the Following GPIO Flow Step by Step :
            // ------ GPIO Flow ------
            // Tool Usage : [0x6C66] [1] Unattach HW Force Vbus Off GPIO Control
            // Tool Usage : [0x6C66] [0] Unattach HW Force Vbus Off GPIO Type, 0 = OD, 1 = PP
            // For RL6829 :
            // 1. Tool Set TypeC1 [frs_gpio_4] : [0x7F94] [1] Initial Value (= ~([0x6C66] [1])), [0] Triggered Value (= [0x6C66] [1])
            // 2. Tool Set Pinshare [Pin_G3 (0x109D)] : if [0x6C66] [0] = 0 (OD) : Tool Set Pinshare [Pin_G3 (0x109D)] = [_PIN_G3_TYPEC_GPIO4_1_OD (0x04)], if [0x6C66] [0] = 1 (PP) : Tool Set Pinshare [Pin_G3 (0x109D)] = [_PIN_G3_TYPEC_GPIO4_1_PP (0x03)]
            // 3. Tool Set FRS GPIO : [0x7F90] [7] = 1 (Enable FRS GPIO), [0x7F90] [2] = 1 (Use FRS_GPIO 0~7)
            // 4. Tool Enable Unattach HW Force Vbus Off Function : [0x6C68] [0] = 1 (Enable)
            // For RL6952 :
            // 1. Tool Set TypeC1 [frs_gpio_6] : [0x7F94] [5] Initial Value (= ~([0x6C66] [1])), [4] Triggered Value (= [0x6C66] [1])
            // 2. Tool Set Pinshare [Pin_B4 (0x1077)] : if [0x6C66] [0] = 0 (OD) : Tool Set Pinshare [Pin_B4 (0x1077)] = [_PIN_B4_TYPEC_GPIO6_1_OD (0x05)], if [0x6C66] [0] = 1 (PP) : Tool Set Pinshare [Pin_B4 (0x1077)] = [_PIN_B4_TYPEC_GPIO6_1_PP (0x04)]
            // 3. Tool Set FRS GPIO : [0x7F90] [7] = 1 (Enable FRS GPIO), [0x7F90] [2] = 1 (Use FRS_GPIO 0~7)
            // 4. Tool Enable Unattach HW Force Vbus Off Function : [0x6C68] [0] = 1 (Enable)
            ScalerSetBit(P6C_66_SRC_FRS_INT, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | (ScalerTypeC1PmicGetForceOffControlType() << 2) | (ScalerTypeC1PmicGetForceOffGpioPinControl() << 1) | ((ScalerTypeC1PmicGetForceOffGpioPinConfig() == _CONFIG_TYPE_GPO_OD) ? 0x00 : _BIT0)));
#else
            ScalerSetBit(P6C_66_SRC_FRS_INT, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif
#else
            // Tool Usage : [0x6C66] [4] Used to Decide Whether Tool shall Show Warning UI when Disable Unattach HW Force Vbus Off Function, 0 = Not Show UI, 1 = Show UI
            // Tool Not Show Warning UI Initially
            ScalerSetBit(P6C_66_SRC_FRS_INT, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif  // End of #if(_EMB_TYPE_C_1_UNATTACH_HW_FORCE_VBUS_OFF == _ON)

            break;

        case _TYPE_C_CC_EMB_FW_FSM_UNATTACH:

            // Do Unattach Reset Only One Time When CC Function is Disable
            if(GET_TYPE_C_1_RESET_FLAG() == _FALSE)
            {
                SET_TYPE_C_1_RESET_FLAG();

                // 1. Reset to Unattached State (Initial to Unattach / Error Recovery : ADC => PMIC => PD => CC)
                ScalerTypeCAdcUnattachReset(_EMB_TYPE_C_1);
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
                ScalerTypeC1PmicReset();
#endif
                ScalerTypeC1PdReset();
                // FW Solution : Samsung S8 Clear Flag When CC Unattach (Not Cleared When PD Reset)
                ScalerTypeC1PdClrInteropS8Flag();
                ScalerTypeC1CcUnattachReset();
            }

            if(GET_TYPE_C_1_CC_CONNECT_EN() == _TRUE)
            {
                CLR_TYPE_C_1_RESET_FLAG();

                // 2. Setting For Connection
                ScalerTypeC1CcConnectionSet();

                // 3. State Transition
                SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_CONNECTING);

                // 4. [3] Clear IRQ hw_done_irq  = 1, Start HW CC Connection Detection
                ScalerTypeC1CcConnectionStart();
            }
            break;

        case _TYPE_C_CC_EMB_FW_FSM_CONNECTING:

            // FW Waiting for Attached When Connecting in HW_MODE
            // Can Use Debug Message to Monitor the Connecting Status
            //========================================================================
            // When "hw_done_irq" is Triggered, SET_TYPE_C_1_CC_FW_STATE(_EMB_TPC_CONNECTTED) @ SysInt
            // hw_done_irq     = 1;            [0x6C30]
            // hw_done_irq_en  = _DISABLE;     [0x6C30]
            // hw_unattach_irq = 1;            [0x6C30]
            // hw_unattach_irq_en = _ENABLE;   [0x6C30]
            //========================================================================

            // Check if Error Recovery is SET
            if(GET_TYPE_C_1_CC_ERROR_RECOVERY() == _TRUE)
            {
                ScalerTypeC1CcFWModeDisconnect();
                CLR_TYPE_C_1_CC_ERROR_RECOVERY();
                SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_UNATTACH);
            }

            break;

        case _TYPE_C_CC_EMB_FW_FSM_ATTACHED:

            //========================================================================
            // When "hw_unattach_irq" is Triggered,
            // Clear and Disable Unattach_irq, SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_UNATTACH) @ SysInt
            // Otherwise, Run PD Controller and Process Corresponding PD Events
            //========================================================================

            // 1. Run PD Handler if PD Function is Enabled and No Error Recovery Set
            if((GET_TYPE_C_1_CC_ERROR_RECOVERY() == _FALSE) && (GET_TYPE_C_1_PD_FUNCTION_EN() == _TRUE))
            {
                ScalerTypeC1PdHandler();
            }

            // 2. Check Whether CC FW Unattach Event is Triggered, If Triggered, Do Error Recovery
            if(ScalerTypeC1CcUnattachCheck() == _TRUE)
            {
                CLR_TYPE_C_1_CC_ATTACHED();
                SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_UNATTACH);
            }

            // 3. Run PMIC Handler
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
            ScalerTypeC1PmicHandler();
#endif

            break;

        default:

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
            DebugMessageTypeC("[WARNING] CC Enter Unexpected State", GET_TYPE_C_1_CC_FW_STATE());
#endif
            // Error : Clear CC Attached Flag and Back to _TYPE_C_CC_EMB_FW_FSM_UNATTACH State
            CLR_TYPE_C_1_CC_ATTACHED();
            SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_UNATTACH);

            break;
    }
}

//--------------------------------------------------
// Description  : Timer Event Proc of CC RX1
// Input Value  : enumEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _SCALER_TIMER_EVENT_CC_1_STATE_TO_UNATTACH:

            SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_UNATTACH);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : CC De-Glitch          [0x6C05 / 0x6C06]
// Input Value  : enumTypeCChannel  : _TYPE_C_CC1(0) / _TYPE_C_CC2(1)
//                ucTime    : 0-63
//                enumUnit  : _TYPE_C_UNIT_1US / _TYPE_C_UNIT_10US / _TYPE_C_UNIT_100US / _TYPE_C_UNIT_1MS
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcSetDeglitch(EnumTypeCChannel enumTypeCChannel, BYTE ucTime, EnumTypeCDeglitchUnit enumUnit)
{
    // [0x6C05] Setting CC1 De-glitch Time Value
    // [0x6C06] Setting CC2 De-glitch Time Value
    if(ucTime < 64)
    {
        // Setting De-glitch Level For Valid Input
        // [7:6] tpc_cc1_dgh_lv / tpc_cc2_dgh_lv (b'00 = 1us / b'01 = 10us / b'10 = 100us / b'11 = 1ms)
        // [5:0] tpc_cc1_dgh_lv / tpc_cc2_dgh_lv = ucTime
        switch(enumUnit)
        {
            case _TYPE_C_UNIT_1US:

                ScalerSetByte(P6C_05_CC1_DGH_LV + enumTypeCChannel, ucTime);
                break;
            case _TYPE_C_UNIT_10US:

                ScalerSetByte(P6C_05_CC1_DGH_LV + enumTypeCChannel, (_BIT6 | ucTime));
                break;
            case _TYPE_C_UNIT_100US:

                ScalerSetByte(P6C_05_CC1_DGH_LV + enumTypeCChannel, (_BIT7 | ucTime));
                break;
            case _TYPE_C_UNIT_1MS:
            default:

                ScalerSetByte(P6C_05_CC1_DGH_LV + enumTypeCChannel, (_BIT7 | _BIT6 | ucTime));
                break;
        }
    }
    else
    {   // Setting De-glitch Level to Default Value (1us) For Invalid Input
        ScalerSetByte(P6C_05_CC1_DGH_LV + enumTypeCChannel, 0x01);
    }   // End of if(ucTime < 64)
}

//--------------------------------------------------
// Description  : Set tCCDeBounce / tPDDebounce [0x6C07 / 0x6C08]
// Input Value  : bDbType   : _TYPE_C_CC / _TYPE_C_PD
//                ucTime    : 0-255
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcSetDebounce(bit bDbType, BYTE ucTime)
{
    if(bDbType == _TYPE_C_CC)
    {   // [0x6C07] tCCDebounce = 100-200ms
        // tpc_db_time_tcc = ucTime
        ScalerSetByte(P6C_07_TPC_TCC_DB_TIME, ucTime);
    }
    else
    {   // [0x6C08] tPDDebounce = 10-20ms
        if((ucTime >= 10) && (ucTime <= 20))
        {   // tpc_db_time_tpd = ucTime
            ScalerSetByte(P6C_08_TPC_TPD_DB_TIME, ucTime);
        }
        else
        {   // tpc_db_time_tpd = 15 ms
            ScalerSetByte(P6C_08_TPC_TPD_DB_TIME, 20);
        }
    }
}

//--------------------------------------------------
// Description  : Set Discharge Count
// Input Value  : ucDischargeCount : 0-255
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcSetDischargeCount(BYTE ucDischargeCount)
{
    SET_TYPE_C_1_CC_DISCHARGE_COUNT(ucDischargeCount);
}

/*
//--------------------------------------------------
// Description  : Backup / Restore TypeC1 Trimming Data
// Input Value  : _TYPE_C_BACKUP / _TYPE_C_RELOAD
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcBackupDataControl(EnumTypeCCCBackupDataControl enumDataControl)
{
    if(enumDataControl == _TYPE_C_BACKUP)
    {
        // Backup All BMC/Vconn Related Trimming Data in AIF_Config.doc
        g_pucTypeC1CcBackupTrimmingDataArray[0] = ScalerGetBit(P6C_80_BMC_RX_SNK_VTH_H, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        g_pucTypeC1CcBackupTrimmingDataArray[1] = ScalerGetBit(P6C_81_BMC_RX_SNK_VTH_L, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        g_pucTypeC1CcBackupTrimmingDataArray[2] = ScalerGetBit(P6C_82_BMC_RX_SRC_VTH_H, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        g_pucTypeC1CcBackupTrimmingDataArray[3] = ScalerGetBit(P6C_83_BMC_RX_SRC_VTH_L, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        g_pucTypeC1CcBackupTrimmingDataArray[4] = ScalerGetBit(P6C_22_BMC_TX_CFG, (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Backup Other Used BMC/Vconn Related Setting in AIF_Config.doc
        g_pucTypeC1CcBackupTrimmingDataArray[5] = ScalerGetByte(P6C_0E_TPC_OPC_CFG_0);
        g_pucTypeC1CcBackupTrimmingDataArray[6] = ScalerGetByte(P6C_0F_TPC_OPC_CFG_1);
        g_pucTypeC1CcBackupTrimmingDataArray[7] = ScalerGetByte(P6C_23_BMC_TX_DRV_TM);
        g_pucTypeC1CcBackupTrimmingDataArray[8] = ScalerGetByte(P6C_24_BMC_LPF);
    }
    else
    {
        // Re-Load All BMC/Vconn Related Trimming Data in AIF_Config.doc
        ScalerSetBit(P6C_80_BMC_RX_SNK_VTH_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTypeC1CcBackupTrimmingDataArray[0] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit(P6C_81_BMC_RX_SNK_VTH_L, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTypeC1CcBackupTrimmingDataArray[1] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit(P6C_82_BMC_RX_SRC_VTH_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTypeC1CcBackupTrimmingDataArray[2] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit(P6C_83_BMC_RX_SRC_VTH_L, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTypeC1CcBackupTrimmingDataArray[3] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit(P6C_22_BMC_TX_CFG, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTypeC1CcBackupTrimmingDataArray[4] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        // Re-Load Other Used BMC/Vconn Related Setting in AIF_Config.doc
        ScalerSetByte(P6C_0E_TPC_OPC_CFG_0, g_pucTypeC1CcBackupTrimmingDataArray[5]);
        ScalerSetByte(P6C_0F_TPC_OPC_CFG_1, g_pucTypeC1CcBackupTrimmingDataArray[6]);
        ScalerSetByte(P6C_23_BMC_TX_DRV_TM, g_pucTypeC1CcBackupTrimmingDataArray[7]);
        ScalerSetByte(P6C_24_BMC_LPF, g_pucTypeC1CcBackupTrimmingDataArray[8]);
    }
}
*/

//--------------------------------------------------
// Description  : Switch to FW Mode to Disconnect Both CC1 / CC2, and Wait 30ms (Should Be More Than tPDDebounce Max)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcFWModeDisconnect(void)
{
    ScalerTypeC1CcFWModeSetResistor(_TYPE_C_PIN_CC1, _TYPE_C_FW_MODE_OPEN);
    ScalerTypeC1CcFWModeSetResistor(_TYPE_C_PIN_CC2, _TYPE_C_FW_MODE_OPEN);
    ScalerSetByte(P6C_30_CC_HW_MODE_CTRL, 0x00);
    ScalerTimerDelayXms(30);
}

//--------------------------------------------------
// Description  : Set CC1/CC2 Resistor for FW Mode
// Input Value  : enumCCPin: _TYPE_C_CC1/_TYPE_C_CC2
//                enumFWModeSetResistor: _TYPE_C_FW_MODE_RD / _TYPE_C_FW_MODE_RP_3_0 / _TYPE_C_FW_MODE_OPEN ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcFWModeSetResistor(EnumTypeCCCPin enumCCPin, EnumTypeCCCFWModeSetResistor enumFWModeSetResistor)
{
    if((enumFWModeSetResistor == _TYPE_C_FW_MODE_RP_3_0) || (enumFWModeSetResistor == _TYPE_C_FW_MODE_RP_1_5) || (enumFWModeSetResistor == _TYPE_C_FW_MODE_RP_DEF))
    {
        ScalerSetByte(P6C_5A_CC_FW_CC1_Z_CFG + enumCCPin, enumFWModeSetResistor);

        // [0x6C5A/0x6C5B] [1] channel_rp_en Shall be Enabled 3T after Any RP Enabled (Note: 1T = 1/(28MHz) for Scaler, or 1T = 1/(27MHz) for Translator)
        ScalerSetBit(P6C_5A_CC_FW_CC1_Z_CFG + enumCCPin, ~(_BIT1), _BIT1);
    }
    else
    {
        // [0x6C5A/0x6C5B] [1] channel_rp_en Shall be Disabled 3T before Any RP Disabled (Note: 1T = 1/(28MHz) for Scaler, or 1T = 1/(27MHz) for Translator)
        ScalerSetBit(P6C_5A_CC_FW_CC1_Z_CFG + enumCCPin, ~(_BIT1), 0x00);

        ScalerSetByte(P6C_5A_CC_FW_CC1_Z_CFG + enumCCPin, enumFWModeSetResistor);
    }
}

//--------------------------------------------------
// Description  : Type C Unattach (Turn Off Power / Disconnect Channel / Clear IRQs)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcUnattachReset(void)
{
    // Turn Off Vconn, if they are turned on when attached
    ScalerTypeC1CcVconnControl(_OFF);

    // Only Initial to Unattach & Error Recovery Will Use Mainloop's Unattach Reset, so It's Allowed Some Delay Times When Vbus Discharge
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
    ScalerTypeC1PmicVbusDischarge(_ON);

    {
        BYTE ucVbusDischargeCnt = 0;

        // Polling Until Vbus Discharge to 0V For User Define Delay times
        while((ucVbusDischargeCnt < GET_TYPE_C_1_CC_DISCHARGE_COUNT()) && (ScalerTypeCAdcCheckVbusSafe0V(_EMB_TYPE_C_1) == _FALSE))
        {
            ucVbusDischargeCnt += 1;
            ScalerTimerDelayXms(1);
        }
    }

    // Disable Vbus Discharge
    ScalerTypeC1PmicVbusDischarge(_OFF);
#endif

// =============================== Control By Power Delivery ??? ===============================
#if(_EMB_TYPE_C_1_PD3_FRSWAP_SUPPORT == _ON)
    // Disable FR_SWAP and FR_SWAP Bypass, if it is turned on when attached
    if((GET_TYPE_C_1_CC_SRC_FRSWAP_STATUS() == _ENABLE) || (GET_TYPE_C_1_CC_SNK_FRSWAP_STATUS() == _ENABLE))
    {
        ScalerTypeC1CcFastRoleSwapControl(_DISABLE);
        SET_TYPE_C_1_CC_SRC_FRSWAP_STATUS(_DISABLE);
        SET_TYPE_C_1_CC_SNK_FRSWAP_STATUS(_DISABLE);
    }
#endif
// =============================================================================================

    // [0x6C30] Reset CC HW FSM
    // [6] hw_mode_fsm_rst = 0, [2] hw_done_irq_en = _DISABLE, [0] hw_unattach_irq_en = _DISABLE
    if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_SRC_ONLY)
    {
        // CTS FW Solution to Transit to Unattached.SRC (hw_mode_fsm_rst = 1 (Normal FSM Running))
        ScalerSetBit(P6C_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        ScalerSetBit(P6C_30_CC_HW_MODE_CTRL, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }

    // [0x6C0C] Disconnect CC1/2 Channel, Detect Circuit
    // [7] tpc_cc1_det_en     = _TYPE_C_DISCONNECT
    // [6] tpc_cc2_det_en     = _TYPE_C_DISCONNECT
    // [5] tpc_cc1_channel_en = _TYPE_C_DISCONNECT
    // [4] tpc_cc2_channel_en = _TYPE_C_DISCONNECT
    ScalerSetBit(P6C_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Disable CC1/2 to BMC and Disable BMC Tx/Rx
    ScalerTypeC1CcSetBMC(_DISABLE);

    // Clear and Disable CC1/2_R_CHG_INT     [0x6C2C] = b'1010_0000
    ScalerSetBit(P6C_2C_CC_R_CHG_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT7 | _BIT5));

    // CC Flags Reset
    CLR_TYPE_C_1_CC_ATTACHED();
    CLR_TYPE_C_1_CC_RA_EXIST();
    CLR_TYPE_C_1_CC_ERROR_RECOVERY();
    CLR_TYPE_C_1_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK();
    CLR_TYPE_C_1_CC_TRY_WAIT_SNK_STATE();
#if(_EMB_TYPE_C_1_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
    // Tool Not Show Warning UI when CC Unattach
    ScalerTypeC1CcToolWarningUIControl(_DISABLE);
#endif

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
    DebugMessageTypeC("O Type C State : UNATTACH", GET_TYPE_C_1_CC_FW_STATE());
    DebugMessageTypeC("    [CC/RST] Vbus Status : ", GET_TYPE_C_1_VBUS_STATUS());
    DebugMessageTypeC("    [CC/RST] Attach Status : ", GET_TYPE_C_1_CC_ATTACHED());
#endif
}

//--------------------------------------------------
// Description  : Type C Setting For Connection (Select Resistor / Initial State / Connect Channels)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcConnectionSet(void)
{
// ===================================== DRP / SRC Switch =====================================
    // [0x6C31] [6:5] HW Mode Type-C Port Role Setting (00:SRC-Only / 01:SNK-Only / 11:DRP)
    // [0x6C35] [7:4] Set Initail State (0000: Unattach.SRC / 0001 : Unattach.SNK)
    if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_SRC_ONLY)
    {
        // [6:5] Source-Only Port ([4:3] Not Support Try.SRC/SNK)
        ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
        ScalerSetBit(P6C_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
    else if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_SNK_ONLY)
    {
        // [6:5] Sink-Only Port ([4:3] Not Support Try.SRC/SNK)
        ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
        ScalerSetBit(P6C_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
    }
    else
    {
        // ======================= DRP Mode =======================
        // [6:5] Dual Role Port ([4:3] Support Try.SRC/SNK)
        ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
        ScalerSetBit(P6C_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

        // Try.SRC/SNK Setting [4] Try.SRC [3] Try.SNK
        if(GET_TYPE_C_1_CC_DRP_PREFER() == _TYPE_C_DRP_TRY_SNK)
        {
            ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~(_BIT4 | _BIT3), _BIT3);
        }
        else if(GET_TYPE_C_1_CC_DRP_PREFER() == _TYPE_C_DRP_TRY_SRC)
        {
            ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~(_BIT4 | _BIT3), _BIT4);
        }
        else
        {
            ScalerSetBit(P6C_31_CC_HW_MODE_CFG, ~(_BIT4 | _BIT3), 0x00);
        }
    }
// ===========================================================================================

#if(_TYPE_C_1_CC_CONNECT_MODE == _TYPE_C_HW_MODE)

    // [0x6C37][7:6] Setting SRC Rp Resistor (36K / 12K / 4.7K)
#if(_EMB_TYPE_C_1_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
    ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_DEF << 6));
    SET_TYPE_C_1_CC_DEF_CUR(90);  // 90 * 10mA = 900mA
#elif(_EMB_TYPE_C_1_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
    ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_1P5A << 6));
    SET_TYPE_C_1_CC_DEF_CUR(150); // 150 * 10mA = 1.5A
#else
    ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_3P0A << 6));
    SET_TYPE_C_1_CC_DEF_CUR(300); // 300 * 10mA = 3.0A
#endif  // End of #if(_EMB_TYPE_C_1_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)

    // [5:4] Setting SNK CC1 Resistor
    ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT5 | _BIT4), (_TYPE_C_SET_RD << 4));
    // [3:2] Setting SNK CC2 Resistor
    ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT3 | _BIT2), (_TYPE_C_SET_RD << 2));

#endif  // End of #if(_TYPE_C_1_CC_CONNECT_MODE == _TYPE_C_HW_MODE)

    // [0x6C0C] Connect CC1/2 Channel
    // [7] tpc_cc1_det_en = _TYPE_C_CONNECT
    // [6] tpc_cc2_det_en = _TYPE_C_CONNECT
    // [5] tpc_cc1_channel_en = _TYPE_C_CONNECT
    // [4] tpc_cc2_channel_en = _TYPE_C_CONNECT
    ScalerSetBit(P6C_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
    // [FW Sol. for _TYPE_C_5B_LS_ADC_GEN_1] Disable Vbus Detect
    ScalerTypeC1CcVbusDetCtrl(_DISABLE);
#else
    // Enable Vbus Detect
    ScalerTypeC1CcVbusDetCtrl(_ENABLE);
#endif

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
    DebugMessageTypeC("O Type C State : CONNECTING...", GET_TYPE_C_1_CC_FW_STATE());
    DebugMessageTypeC("    [CC/Connect Set] Default Current : ", GET_TYPE_C_1_CC_DEF_CUR());
#endif
}

//--------------------------------------------------
// Description  : Clear IRQ hw_done_irq  = 1, Start HW CC Connection Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcConnectionStart(void)
{
#if(_TYPE_C_1_CC_CONNECT_MODE == _TYPE_C_HW_MODE)
    // [0x6C30] Enable HW Mode, Release FSM Reset : Disable connect_en and Clear IRQs
    // [6] hw_mode_fsm_rst = 1
    // [5] hw_connect_en = _DISABLE
    // [3] hw_done_irq  = 1
    // [2] hw_done_irq_en = _ENABLE
    // [1] hw_unattach_irq = 1
    // [0] hw_unattach_irq_en = _DISABLE
    ScalerSetBit(P6C_30_CC_HW_MODE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1));

    if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_CC_DRP_PREFER() == _TYPE_C_DRP_TRY_SRC))
    {
        // DRP Try Src FW Solution
        // [0x6C58] : [1] hw_try_wait_snk_irq, [0] hw_try_wait_snk_irq_en
        // Clear and Enable hw_try_wait_snk_irq
        ScalerSetBit(P6C_58_DBCC_SNK_DET_COND, ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    }
#else
    // FW_MODE Reset
    ScalerSetBit(P6C_30_CC_HW_MODE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
#endif
    // Enable connect_en
    ScalerSetBit(P6C_30_CC_HW_MODE_CTRL, ~(_BIT5 | _BIT3 | _BIT1), _BIT5);
}

//--------------------------------------------------
// Description  : CC Check if Unattach Event is Triggered
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerTypeC1CcUnattachCheck(void)
{
    bit bUnattach = _FALSE;
    BYTE ucUnattachWaitPhyIdleCnt = 0;

    // 1. Check if Error Recovery is SET
    if(GET_TYPE_C_1_CC_ERROR_RECOVERY() == _TRUE)
    {
        // [0x6C30] : [3] hw_done_irq, [1] hw_unattach_irq, [0] hw_unattach_irq_en
        // Disable hw_unattach_irq to Prevent IRQ Triggered during Error Recovery
        ScalerSetBit(P6C_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

        // Polling 1ms * 5 to Check PHY Idle, Don't Do Error Recovery When BMC Is Not Idle
        while((ucUnattachWaitPhyIdleCnt < 5) && (ScalerGetBit(P6B_05_PD_PHY_IDLE_INT, _BIT2) == 0x00))
        {
            ucUnattachWaitPhyIdleCnt += 1;
            ScalerTimerDelayXms(1);
        }

        if(ScalerTypeC1PdGetPowerRole() == _TYPE_C_POWER_SRC)
        {
            // Turn Off Vconn, if they are turned on when attached
            ScalerTypeC1CcVconnControl(_OFF);

            // Turn Off Vbus, then Enable Vbus Discharge For Source to Discharge 5V
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
            ScalerTypeC1PmicSetting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
            ScalerTypeC1PmicVbusDischarge(_ON);
#endif
        }

        // Switch to FW Mode to Disconnect Both CC1 / CC2, and Wait 30ms (Should Be More Than tPDDebounce Max)
        ScalerTypeC1CcFWModeDisconnect();

        // Any Fatal Error Happens in PD, and Need to Unattach Type C Function
        bUnattach = _TRUE;
        CLR_TYPE_C_1_CC_ERROR_RECOVERY();
    }

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
    if(bUnattach == _TRUE)
    {
        // [Eizo] SIC437A Customized Power Control : SRC/SNK Unattach
        ScalerTypeC1PmicSic437aUnattachProc(ScalerTypeC1PdGetPowerRole());
    }
#endif

    return bUnattach;
}

//--------------------------------------------------
// Description  : Enable/Disable Detect Rp to Transit from Attached.SNK to Unattached.SNK State
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcSnkDetRpCtrl(bit bAction)
{
    // Spec.: For (SNK & Not in PR_Swap Flow), Check if SRC-Rp is Removed, Transition to Unattached.SNK within 40ms
    // [0x6C37] [0] cc_det_rp_opt (0:Enable Detect Rp / 1:Disable Detect Rp)
    if(bAction == _ENABLE)
    {
        // HW FSM will Transit from Attached.SNK to Unattached.SNK when CC Open for tPDDebounce
        ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~_BIT0, 0x00);
    }
    else
    {
        ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Enable / Disable Vconn Power
// Input Value  : bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcVconnControl(bit bAction)
{
    if(bAction == _ON)
    {
        if(GET_TYPE_C_1_CC_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [0x6C72] Reset and Enable CC2 OCP IRQs
            // [2]cc2_vconn_prot_irq      = 1
            // [1]cc2_vconn_shutdown_irq  = 1
            // [0]cc2_vconn_on_irq        = 1
            ScalerSetBit(P6C_72_CC2_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc2_vconn_prot_irq_en    = _DISABLE
            // [5] cc2_vconn_shutdown_irq_en= _ENABLE
            // [4] cc2_vconn_on_irq_en      = _DISABLE
            ScalerSetBit(P6C_72_CC2_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT5);

            // [0x6C0D] Turn On CC2 Vconn Switch : [2]tpc_cc2_vconn_en= _ENABLE
            ScalerSetBit(P6C_0D_TPC_OCP_CTRL, ~_BIT2, _BIT2);

            SET_TYPE_C_1_CC_VCONN_STATUS(_ON);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
            DebugMessageTypeC("    [CC/Vconn] Vconn on CC2 : ", _TYPE_C_CC2);
            DebugMessageTypeC("    [CC/Vconn] Turn On Vconn : ", GET_TYPE_C_1_CC_VCONN_STATUS());
#endif
        }
        else if(GET_TYPE_C_1_CC_ORIENTATION() == _TYPE_C_ORIENTATION_FLIP)
        {
            // [0x6C71] Reset and Enable CC1 OCP IRQs
            // [2] cc1_vconn_prot_irq      = 1
            // [1] cc1_vconn_shutdown_irq  = 1
            // [0] cc1_vconn_on_irq        = 1
            ScalerSetBit(P6C_71_CC1_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc1_vconn_prot_irq_en    = _DISABLE
            // [5] cc1_vconn_shutdown_irq_en= _ENABLE
            // [4] cc1_vconn_on_irq_en      = _DISABLE
            ScalerSetBit(P6C_71_CC1_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT5);

            // [0x6C0D] Turn On CC1 Vconn Switch : [3] tpc_cc1_vconn_en= _ENABLE
            ScalerSetBit(P6C_0D_TPC_OCP_CTRL, ~_BIT3, _BIT3);

            SET_TYPE_C_1_CC_VCONN_STATUS(_ON);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
            DebugMessageTypeC("    [CC/Vconn] Vconn on CC1 : ", _TYPE_C_CC1);
            DebugMessageTypeC("    [CC/Vconn] Turn On Vconn : ", GET_TYPE_C_1_CC_VCONN_STATUS());
#endif
        }
    }
    else
    {
        // Disable CC1/CC2 Vconn IRQs
        ScalerSetByte(P6C_71_CC1_VCONN_OCP_INT, 0x00);
        ScalerSetByte(P6C_72_CC2_VCONN_OCP_INT, 0x00);

        // [0x6C0D] Turn Off Both CC1/2 Vconn Switch : [3:2] tpc_cc1/2_vconn_en= _DISABLE
        ScalerSetBit(P6C_0D_TPC_OCP_CTRL, ~(_BIT3 | _BIT2), 0x00); // [0x6C0D] <3:2> : tpc_cc1/2_vconn_en = _DISABLE
        SET_TYPE_C_1_CC_VCONN_STATUS(_OFF);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
        DebugMessageTypeC("    [CC/Vconn] Turn Off Vconn : ", GET_TYPE_C_1_CC_VCONN_STATUS());
#endif
    }
}

//--------------------------------------------------
// Description  : Enable / Disable BMC Channel in CC Logic
// Input Value  : Event : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcSetBMC(bit bAction)
{
    if(bAction == _ENABLE)
    {
        // 1. [0x6C25] Auto Switch SRC/SNK BMC Vth_H/L When tpc_cc_mode_sel is HW Auto Mode, Enable BMC Rx and Set BMC Tx Controlled By HW
        // [7:6] bmc_rx/tx_en = b'10 (Enable Rx, [3] Tx Control By HW)
        ScalerSetBit(P6C_25_BMC_TX_RX_CFG, ~(_BIT7 | _BIT6 | _BIT3), (_BIT7 | _BIT3));

        // 2. [0x6C0C] Connect CC1 or CC2 to BMC Channel
        if(GET_TYPE_C_1_CC_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [3] tpc_cc1_en = _TYPE_C_CONNECT
            // [2] tpc_cc2_en = _TYPE_C_DISCONNECT (Not Needed)
            ScalerSetBit(P6C_0C_TPC_CC_CTRL, ~(_BIT3 | _BIT2), _BIT3);
        }
        else
        {
            // [3] tpc_cc1_en = _TYPE_C_DISCONNECT  (Not Needed)
            // [2] tpc_cc2_en = _TYPE_C_CONNECT
            ScalerSetBit(P6C_0C_TPC_CC_CTRL, ~(_BIT3 | _BIT2), _BIT2);
        }

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
        if(GET_TYPE_C_1_CC_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            DebugMessageTypeC("    [CC/BMC] BMC Connected to CC1", bAction);
        }
        else
        {
            DebugMessageTypeC("    [CC/BMC] BMC Connected to CC2", bAction);
        }
#endif
    }
    else
    {   // [0x6C25] Disable BMC Channel
        // [7] bmc_rx_en = _DISABLE
        // [6] bmc_tx_en = _DISABLE
        ScalerSetBit(P6C_25_BMC_TX_RX_CFG, ~(_BIT7 | _BIT6), 0x00);

        // [0x6C0C] CC1/CC2 Disconnect to BMC Channel
        // [3] tpc_cc1_en = _TYPE_C_DISCONNECT
        // [2] tpc_cc2_en = _TYPE_C_DISCONNECT
        ScalerSetBit(P6C_0C_TPC_CC_CTRL, ~(_BIT3 | _BIT2), 0x00);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
        DebugMessageTypeC("    [CC/BMC] BMC Disconnected", bAction);
#endif
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Detect Vbus On/Off to transit State
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcVbusDetCtrl(bit bAction)
{
    // [0x6C34] [7] vbus_det_dis
    if(bAction == _ENABLE)
    {   // Enable Vbus Detection : vbus_det_dis = _DISABLE
        ScalerSetBit(P6C_34_CC_HW_STATE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
        DebugMessageTypeC("    [CC/Det Vbus] Start Vbus Detect", bAction);
#endif
    }
    else
    {   // Enable Vbus Detection : vbus_det_dis = _ENABLE
        ScalerSetBit(P6C_34_CC_HW_STATE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
        DebugMessageTypeC("    [CC/Det Vbus] Stop Vbus Detect", bAction);
#endif
    }
}

//--------------------------------------------------
// Description  : Update & Return CC Pin Resistor (Only For CC Pin, Not Vconn Pin)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerTypeC1CcDetResistor(void)
{
    // Only Update Resistor of CC Pin, Not Vconn Pin (Flip : [7:4] CC1, Un-Flip : [3:0] CC2)
    if(GET_TYPE_C_1_CC_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
    {
        if(ScalerGetBit(P6C_2A_CC_ANA_DET_R, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0xF0)
        {
            SET_TYPE_C_1_CC_CC1_R(_TYPE_C_DET_RP_3P0A);
        }
        else
        {
            // Setting Default Result = SinkTxNG (Rp 1.5A)
            SET_TYPE_C_1_CC_CC1_R(_TYPE_C_DET_RP_1P5A);
        }

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
        DebugMessageTypeC("[CC]  Resistor Detect CC1", GET_TYPE_C_1_CC_ORIENTATION());
        DebugMessageTypeC("[CC]  Resistor Detect Result", GET_TYPE_C_1_CC_CC1_R());
#endif
        return GET_TYPE_C_1_CC_CC1_R();
    }
    else
    {
        if(ScalerGetBit(P6C_2A_CC_ANA_DET_R, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x0F)
        {
            SET_TYPE_C_1_CC_CC2_R(_TYPE_C_DET_RP_3P0A);
        }
        else
        {
            // Setting Default Result = SinkTxNG (Rp 1.5A)
            SET_TYPE_C_1_CC_CC2_R(_TYPE_C_DET_RP_1P5A);
        }

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
        DebugMessageTypeC("[CC]  Resistor Detect CC2", GET_TYPE_C_1_CC_ORIENTATION());
        DebugMessageTypeC("[CC]  Resistor Detect Result", GET_TYPE_C_1_CC_CC2_R());
#endif
        return GET_TYPE_C_1_CC_CC2_R();
    }
}

//--------------------------------------------------
// Description  : Process For Change Between SRC and SNK w/o Unattach
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcSwitchPowerRole(BYTE ucTargetRole)
{
    if(ucTargetRole == _PD_POWER_SRC)
    {
        // 1. Set Rp to Default CC Rp
#if(_EMB_TYPE_C_1_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
        ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_DEF << 6));
#elif(_EMB_TYPE_C_1_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
        ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_1P5A << 6));
#else
        ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_3P0A << 6));
#endif

        // 2. Switch Type-C HW State From SNK to SRC
        ScalerSetBit(P6C_34_CC_HW_STATE_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT6);

        if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_CC_DRP_PREFER() == _TYPE_C_DRP_TRY_SRC))
        {
            // DRP Try Src FW Solution
            // [0x6C30] : [3] hw_done_irq, [2] hw_done_irq_en, [1] hw_unattach_irq, [0] hw_unattach_irq_en
            // Disable hw_done_irq and hw_unattach_irq
            ScalerSetBit(P6C_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

            // [0x6C58] : [1] hw_try_wait_snk_irq, [0] hw_try_wait_snk_irq_en
            // Clear and Enable hw_try_wait_snk_irq
            ScalerSetBit(P6C_58_DBCC_SNK_DET_COND, ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Set Attached.SRC to TryWait.Snk Flag
            SET_TYPE_C_1_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK();
        }
    }
    else
    {
        // Switch Type-C HW State From SRC to SNK
        ScalerSetBit(P6C_34_CC_HW_STATE_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);

        if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_CC_DRP_PREFER() == _TYPE_C_DRP_TRY_SRC))
        {
            // DRP Try Src FW Solution
            // [0x6C30] : [3] hw_done_irq, [2] hw_done_irq_en, [1] hw_unattach_irq, [0] hw_unattach_irq_en
            // Disable hw_done_irq and Enable hw_unattach_irq
            ScalerSetBit(P6C_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            // [0x6C58] : [1] hw_try_wait_snk_irq, [0] hw_try_wait_snk_irq_en
            // Clear and Disable hw_try_wait_snk_irq
            ScalerSetBit(P6C_58_DBCC_SNK_DET_COND, ~(_BIT3 | _BIT1 | _BIT0), _BIT1);

            // Clear Attached.SRC to TryWait.Snk Flag
            CLR_TYPE_C_1_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK();
        }
    }

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_CC_FW_DEBUG == _ON))
    DebugMessageTypeC("    [CC/Resistor] Switch to SNK(0) / SRC(1): ", ucTargetRole);
#endif
}

//--------------------------------------------------
// Description  : TypeC1 Cc Power Switch Proc
// Input Value  : enumPowerAction : Power Switch Enum
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcPowerSwitch(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_AC_ON_TO_OFF:

#if(_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY)
#if(_EMB_TYPE_C_1_AC_ON_RECONNECT == _TRUE)
            SET_TYPE_C_1_CC_AC_ON_RECONNECT();
#else
            CLR_TYPE_C_1_CC_AC_ON_RECONNECT();
#endif

            // Cancel Unattach Timer Event When Power On TypeC
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_CC_1_STATE_TO_UNATTACH);

            // AC On Start From INITIAL State
            SET_TYPE_C_1_CC_FW_STATE(_TYPE_C_CC_EMB_FW_FSM_INITIAL);
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : TypeC1 Cc Function Control
// Input Value  : enumCcFunction : _TYPE_C_CC_FUNCTION_DISABLE/ENABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcFunctionControl(EnumTypeCCcFunction enumCcFunction)
{
    if(enumCcFunction == _TYPE_C_CC_FUNCTION_DISABLE)
    {
        CLR_TYPE_C_1_CC_CONNECT_EN();
        SET_TYPE_C_1_CC_ERROR_RECOVERY();
    }
    else if(enumCcFunction == _TYPE_C_CC_FUNCTION_ENABLE)
    {
        SET_TYPE_C_1_CC_CONNECT_EN();
    }
}

//--------------------------------------------------
// Description  : Set CC Function Support Option
// Input Value  : enumFunctionSupport
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcSetFunctionSupport(EnumTypeCFunctionSupport enumFunctionSupport)
{
    if(enumFunctionSupport == _TYPE_C_SUPPORT_NO_FUNCTION)
    {
        CLR_TYPE_C_1_CC_CONNECT_EN();
    }
    else
    {
        SET_TYPE_C_1_CC_CONNECT_EN();
    }
}

//--------------------------------------------------
// Description  : Set Type-C Operation Mode
// Input Value  : enumOperationMode
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcSetOperationMode(EnumTypeCOperationMode enumOperationMode)
{
    switch(enumOperationMode)
    {
        case _TYPE_C_SRC_ONLY_MODE:

            SET_TYPE_C_1_CC_PORT_ROLE(_TYPE_C_PORT_SRC_ONLY);
            SET_TYPE_C_1_CC_DRP_PREFER(_TYPE_C_DRP_NO_PREFERENCE);

            break;

        case _TYPE_C_SNK_ONLY_MODE:

            SET_TYPE_C_1_CC_PORT_ROLE(_TYPE_C_PORT_SNK_ONLY);
            SET_TYPE_C_1_CC_DRP_PREFER(_TYPE_C_DRP_NO_PREFERENCE);

            break;

        case _TYPE_C_DRP_NO_PREFERENCE_MODE:

            SET_TYPE_C_1_CC_PORT_ROLE(_TYPE_C_PORT_DRP);
            SET_TYPE_C_1_CC_DRP_PREFER(_TYPE_C_DRP_NO_PREFERENCE);

            break;

        case _TYPE_C_DRP_TRY_SNK_MODE:

            SET_TYPE_C_1_CC_PORT_ROLE(_TYPE_C_PORT_DRP);
            SET_TYPE_C_1_CC_DRP_PREFER(_TYPE_C_DRP_TRY_SNK);

            break;

        case _TYPE_C_DRP_TRY_SRC_MODE:

            SET_TYPE_C_1_CC_PORT_ROLE(_TYPE_C_PORT_DRP);
            SET_TYPE_C_1_CC_DRP_PREFER(_TYPE_C_DRP_TRY_SRC);

            break;

        default:

            break;
    }
}

#if(_EMB_TYPE_C_1_PD3_FRSWAP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable / Disable Fast Role Swap
// Input Value  : bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcFastRoleSwapControl(bit bAction)
{
    if(bAction == _ENABLE)
    {
        if(ScalerTypeC1PdGetPowerRole() == _TYPE_C_POWER_SRC)
        {
            // [0x6C66] Clear and Enable SRC FR_SWAP INT
            // [7] src_frs_done_int    = 1
            // [6] src_frs_done_int_en = _ENABLE
            ScalerSetBit(P6C_66_SRC_FRS_INT, ~_BIT7, _BIT7);
            ScalerSetBit(P6C_66_SRC_FRS_INT, ~(_BIT7 | _BIT6), _BIT6);

            // [0x6C60] Turn On Source-Side FR_SWAP
            // [7] src_frs_en = _ENABLE
            ScalerSetBit(P6C_60_FRS_CTRL, ~(_BIT7 | _BIT5), _BIT7);

            SET_TYPE_C_1_CC_SRC_FRSWAP_STATUS(_ENABLE);
        }
        else
        {
            // [0x6C67] Clear and Enable SNK FR_SWAP INT
            // [7] snk_frs_done_int    = 1
            // [6] snk_frs_done_int_en = _ENABLE
            // [3] snk_frs_tri_int     = 1
            // [2] snk_frs_tri_int_en  = _ENABLE
            ScalerSetBit(P6C_67_SNK_FRS_INT, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT3 | _BIT2));

            // [0x6C60] Turn On Sink-Side FR_SWAP
            // [6] snk_frs_en = _ENABLE
            ScalerSetBit(P6C_60_FRS_CTRL, ~(_BIT6 | _BIT5), _BIT6);

            SET_TYPE_C_1_CC_SNK_FRSWAP_STATUS(_ENABLE);
        }   // End of if(ScalerTypeC1PdGetPowerRole() == _TYPE_C_POWER_SRC)
    }
    else
    {   // [0x6C66] Disable SRC FR_SWAP INT
        // [6] src_frs_done_int_en = _DISABLE
        ScalerSetBit(P6C_66_SRC_FRS_INT, ~(_BIT7 | _BIT6), 0x00);

        // [0x6C67] Disable SNK FR_SWAP INT
        // [6] snk_frs_done_int_en = _DISABLE
        // [2] snk_frs_tri_int_en  = _DISABLE
        ScalerSetBit(P6C_67_SNK_FRS_INT, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

        // [0x6C60] Turn Off Source/Sink-Side FR_SWAP
        // [7] src_frs_en = _DISABLE
        // [6] snk_frs_en = _DISABLE
        ScalerSetBit(P6C_60_FRS_CTRL, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [0x6C68] Turn Off Fast-Role Swap
        ScalerSetBit(P6C_68_FRS_BYPASS_MODE, ~_BIT7, 0x00);

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
void ScalerTypeC1CcToolWarningUIControl(bit bAction)
{
    // Tool Usage : [0x6C66] [4] Used to Decide Whether Tool shall Show Warning UI when Disable Unattach HW Force Vbus Off Function([3]=0), 0 = Not Show UI, 1 = Show UI
    if(bAction == _ENABLE)
    {
        ScalerSetBit(P6C_66_SRC_FRS_INT, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    }
    else
    {
        ScalerSetBit(P6C_66_SRC_FRS_INT, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
}
#endif  // End of #if(_EMB_TYPE_C_1_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)

#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))

#if(((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)) || ((_TYPE_C_GPIO_MODE_SUPPORT == _ON) && (_HW_EMB_TYPE_C_1_SUPPORT == _ON)))
//--------------------------------------------------
// Description  : Load Trimming Value From E-Fuse
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcLoadTrimming(void)
{
#if(_FACTORY_RTD_QC_SUPPORT == _OFF)
#if(_HW_FUSE_TYPE != _TYPE_NONE)
    BYTE pucEfuseArray[_HW_OTPFUSE_TYPE_C_1_TRIMDATA_LEN] = {0};

    if(ScalerOTPMemoryCheckDoneBit() == _TRUE)
    {
        // Read all TypeC1 PD/CC related Efuse address
        ScalerOTPMemoryReadData(_OTPMEMORY_TYPE_C_1_TRIMDATA, &pucEfuseArray[0]);

        // CC1 Attach Thershold :
        ScalerSetByte(P6C_10_CC1_VTH_CFG_0, pucEfuseArray[0]);  // 200 / 400 mV
        ScalerSetByte(P6C_11_CC1_VTH_CFG_1, pucEfuseArray[1]);  // 660 / 800 mV
        ScalerSetByte(P6C_12_CC1_VTH_CFG_2, pucEfuseArray[2]);  // 1230 / 1600 mV
        ScalerSetByte(P6C_13_CC1_VTH_CFG_3, pucEfuseArray[3]);  // 2600 / 490 mV

        // CC2 Attach Thershold :
        ScalerSetByte(P6C_14_CC2_VTH_CFG_0, pucEfuseArray[4]);  // 200 / 400 mV
        ScalerSetByte(P6C_15_CC2_VTH_CFG_1, pucEfuseArray[5]);  // 660 / 800 mV
        ScalerSetByte(P6C_16_CC2_VTH_CFG_2, pucEfuseArray[6]);  // 1230 / 1600 mV
        ScalerSetByte(P6C_17_CC2_VTH_CFG_3, pucEfuseArray[7]);  // 2600 / 490 mV

        // Read CC Resistance
        // CC1/CC2 Rp 12k :
        ScalerSetByte(P6C_1A_TPC_CC1_RP12K_CFG, (pucEfuseArray[8] & 0x1F));
        ScalerSetByte(P6C_1E_TPC_CC2_RP12K_CFG, (pucEfuseArray[9] & 0x1F));

        // CC1/CC2 Rp 36k :
        ScalerSetByte(P6C_1B_TPC_CC1_RP36K_CFG, (pucEfuseArray[10] & 0x1F));
        ScalerSetByte(P6C_1F_TPC_CC2_RP36K_CFG, (pucEfuseArray[11] & 0x1F));

        // CC1/CC2 Rp 4.7k :
        ScalerSetByte(P6C_19_TPC_CC1_RP4P7K_CFG, (pucEfuseArray[12] & 0x1F));
        ScalerSetByte(P6C_1D_TPC_CC2_RP4P7K_CFG, (pucEfuseArray[13] & 0x1F));

        // CC1/CC2 Rd 5.1k :
        ScalerSetByte(P6C_18_TPC_CC1_RD_CFG, (pucEfuseArray[14] & 0x1F));
        ScalerSetByte(P6C_1C_TPC_CC2_RD_CFG, (pucEfuseArray[15] & 0x1F));

        // CC1/CC2 Ra 1K :
        ScalerSetByte(P6C_86_TPC_CC1_RA_CFG, ((pucEfuseArray[14] & 0xE0) >> 5));
        ScalerSetByte(P6C_87_TPC_CC2_RA_CFG, ((pucEfuseArray[15] & 0xE0) >> 5));

        // BMC RX Voltage Thershold :
        ScalerSetByte(P6C_80_BMC_RX_SNK_VTH_H, (pucEfuseArray[16] & 0x1F));
        ScalerSetByte(P6C_81_BMC_RX_SNK_VTH_L, (pucEfuseArray[17] & 0x1F));
        ScalerSetByte(P6C_82_BMC_RX_SRC_VTH_H, (pucEfuseArray[18] & 0x1F));
        ScalerSetByte(P6C_83_BMC_RX_SRC_VTH_L, (pucEfuseArray[19] & 0x1F));

        // BMC TX Swing Voltage :
        ScalerSetBit(P6C_22_BMC_TX_CFG, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (((pucEfuseArray[16] & _BIT5) >> 2) | ((pucEfuseArray[17] & _BIT5) >> 3) | ((pucEfuseArray[18] & _BIT5) >> 4) | ((pucEfuseArray[19] & _BIT5) >> 5)));
    }
    else
#endif
#endif
    {
        // Setting Voltage Triming Value : CC1/2 200/400/660/800/1230/1600/2600/490 mV
        ScalerSetByte(P6C_10_CC1_VTH_CFG_0, 0x77);  // 200 / 400 mV
        ScalerSetByte(P6C_11_CC1_VTH_CFG_1, 0x66);  // 660 / 800 mV
        ScalerSetByte(P6C_12_CC1_VTH_CFG_2, 0x65);  // 1230 / 1600 mV
        ScalerSetByte(P6C_13_CC1_VTH_CFG_3, 0x66);  // 2600 / 490 mV

        ScalerSetByte(P6C_14_CC2_VTH_CFG_0, 0x77);  // 200 / 400 mV
        ScalerSetByte(P6C_15_CC2_VTH_CFG_1, 0x66);  // 660 / 800 mV
        ScalerSetByte(P6C_16_CC2_VTH_CFG_2, 0x65);  // 1230 / 1600 mV
        ScalerSetByte(P6C_17_CC2_VTH_CFG_3, 0x66);  // 2600 / 490 mV

        // Setting Resistor Triming Value : CC1/2 Rd/Rp-4.7K/Rp-12K/Rp-36K
        ScalerSetBit(P6C_18_TPC_CC1_RD_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x12);
        ScalerSetBit(P6C_19_TPC_CC1_RP4P7K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
        ScalerSetBit(P6C_1A_TPC_CC1_RP12K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x08);
        ScalerSetBit(P6C_1B_TPC_CC1_RP36K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);

        ScalerSetBit(P6C_1C_TPC_CC2_RD_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x12);
        ScalerSetBit(P6C_1D_TPC_CC2_RP4P7K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
        ScalerSetBit(P6C_1E_TPC_CC2_RP12K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x08);
        ScalerSetBit(P6C_1F_TPC_CC2_RP36K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);

        // CC1/CC2 Ra 1K
        ScalerSetBit(P6C_86_TPC_CC1_RA_CFG, ~(_BIT2 | _BIT1 | _BIT0), 0x03);
        ScalerSetBit(P6C_87_TPC_CC2_RA_CFG, ~(_BIT2 | _BIT1 | _BIT0), 0x03);

        // Setting SRC/SNK VTH
        ScalerSetBit(P6C_80_BMC_RX_SNK_VTH_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x06);
        ScalerSetBit(P6C_81_BMC_RX_SNK_VTH_L, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x10);
        ScalerSetBit(P6C_82_BMC_RX_SRC_VTH_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0B);
        ScalerSetBit(P6C_83_BMC_RX_SRC_VTH_L, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);

        // BMC TX Swing Voltage
        ScalerSetBit(P6C_22_BMC_TX_CFG, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
    }
}
#endif  // End of #if(((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)) || ((_TYPE_C_GPIO_MODE_SUPPORT == _ON) && (_HW_EMB_TYPE_C_1_SUPPORT == _ON)))

#if((_TYPE_C_GPIO_MODE_SUPPORT == _ON) && (_HW_EMB_TYPE_C_1_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TypeC1 GPIO Mode Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1CcGpioModeInitialSetting(void)
{
    // Set cc1_det_vth3 / cc2_det_vth3 to 2.6V
    ScalerSetBit(P6C_28_VTH_SEL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));

    // CC1/2 Not Connect Rp/Rd
    ScalerSetByte(P6C_5A_CC_FW_CC1_Z_CFG, 0x00);
    ScalerSetByte(P6C_5B_CC_FW_CC2_Z_CFG, 0x00);

    // Switch to FW Mode
    ScalerSetByte(P6C_30_CC_HW_MODE_CTRL, 0x00);

    // Enable cc1_channel_en and cc1_det_en / cc2_channel_en and cc2_det_en
    ScalerSetBit(P6C_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
}

//--------------------------------------------------
// Description  : Get TypeC1 CC Pin Status
// Input Value  : enumTypeCChannel (_TYPE_C_CC1, _TYPE_C_CC2)
// Output Value : EnumTypeCCcDetectStatus : _TYPE_C_CC_DETECT_HIGH (if CC Voltage >= 2.6V) / _TYPE_C_CC_DETECT_LOW (if CC Voltage < 2.6V)
//--------------------------------------------------
EnumTypeCCcDetectStatus ScalerTypeC1CcGetCcPinStatus(EnumTypeCChannel enumTypeCChannel)
{
    EnumTypeCCcDetectStatus enumTypeCCcDetectStatus = _TYPE_C_CC_DETECT_LOW;

    if(enumTypeCChannel == _TYPE_C_CC1)
    {
        // Check whether CC1 > 2.6V
        if((ScalerGetBit(P6C_2A_CC_ANA_DET_R, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) & _BIT7) == _BIT7)
        {
            enumTypeCCcDetectStatus = _TYPE_C_CC_DETECT_HIGH;
        }
    }
    else if(enumTypeCChannel == _TYPE_C_CC2)
    {
        // Check whether CC2 > 2.6V
        if((ScalerGetBit(P6C_2A_CC_ANA_DET_R, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) & _BIT3) == _BIT3)
        {
            enumTypeCCcDetectStatus = _TYPE_C_CC_DETECT_HIGH;
        }
    }

    return enumTypeCCcDetectStatus;
}
#endif  // End of #if((_TYPE_C_GPIO_MODE_SUPPORT == _ON) && (_HW_EMB_TYPE_C_1_SUPPORT == _ON))