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
// ID Code      : ScalerTypeC0Cc_WDINT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeC0Cc/ScalerTypeC0Cc.h"




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
// Description  : WD Timer Event Proc of CC RX0
// Input Value  : enumEventID, pucActiveWDID, pucActiveWDTime
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0CcWDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime)
{
    pucActiveWDID = pucActiveWDID;
    pucActiveWDTime = pucActiveWDTime;

    switch(enumEventID)
    {
        case _SCALER_WD_TIMER_EVENT_CC_0_DETECT_VBUS:

            // Set Vbus_On_Thr to vSafe5V(4.6V) to Detect Vbus On
            ScalerTypeCAdcOnOffCompIntSetting_WDINT(_TYPE_C_CHANNEL_0_VMON, _ON, GET_TYPE_C_0_5V_LOW_BND());

            // Enable [adc0_comp_vbus_on_en], and Wait ADC VbusSafe5V [adc0_comp_vbus_on] INT Triggered, then Set HW FSM to Attached.SNK
            ScalerTypeCAdcOnOffCompIntControl_WDINT(_TYPE_C_CHANNEL_0_VMON, _ON, _ENABLE);

            break;

#if(_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE)
        case _SCALER_WD_TIMER_EVENT_CC_0_CHECK_VBUS_0V:

            if(ScalerTypeCAdcCheckVbusSafe0V_WDINT(_EMB_TYPE_C_0) == _TRUE)
            {
                ScalerTypeC0PmicVbusDischarge_WDINT(_OFF);
            }
            else
            {
                *pucActiveWDID = _SCALER_WD_TIMER_EVENT_CC_0_CHECK_VBUS_0V;
                *pucActiveWDTime = _UNATTACH_VBUS_DISCHARGE_TIMER;
            }

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Enable / Disable Vconn Power in WD Timer
// Input Value  : bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0CcVconnControl_WDINT(bit bAction)
{
    if(bAction == _ON)
    {
        if(GET_TYPE_C_0_CC_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [0x6672] Reset and Enable CC2 OCP IRQs
            // [2]cc2_vconn_prot_irq      = 1
            // [1]cc2_vconn_shutdown_irq  = 1
            // [0]cc2_vconn_on_irq        = 1
            ScalerSetBit_EXINT(P66_72_CC2_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc2_vconn_prot_irq_en    = _DISABLE
            // [5] cc2_vconn_shutdown_irq_en= _ENABLE
            // [4] cc2_vconn_on_irq_en      = _DISABLE
            ScalerSetBit_EXINT(P66_72_CC2_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT5);

            // [0x660D] Turn On CC2 Vconn Switch : [2]tpc_cc2_vconn_en= _ENABLE
            ScalerSetBit_EXINT(P66_0D_TPC_OCP_CTRL, ~_BIT2, _BIT2);

            SET_TYPE_C_0_CC_VCONN_STATUS(_ON);
        }
        else if(GET_TYPE_C_0_CC_ORIENTATION() == _TYPE_C_ORIENTATION_FLIP)
        {
            // [0x6671] Reset and Enable CC1 OCP IRQs
            // [2] cc1_vconn_prot_irq      = 1
            // [1] cc1_vconn_shutdown_irq  = 1
            // [0] cc1_vconn_on_irq        = 1
            ScalerSetBit_EXINT(P66_71_CC1_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc1_vconn_prot_irq_en    = _DISABLE
            // [5] cc1_vconn_shutdown_irq_en= _ENABLE
            // [4] cc1_vconn_on_irq_en      = _DISABLE
            ScalerSetBit_EXINT(P66_71_CC1_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), _BIT5);

            // [0x660D] Turn On CC1 Vconn Switch : [3] tpc_cc1_vconn_en= _ENABLE
            ScalerSetBit_EXINT(P66_0D_TPC_OCP_CTRL, ~_BIT3, _BIT3);

            SET_TYPE_C_0_CC_VCONN_STATUS(_ON);
        }
    }
    else
    {
        // Disable CC1/CC2 Vconn IRQs
        ScalerSetByte_EXINT(P66_71_CC1_VCONN_OCP_INT, 0x00);
        ScalerSetByte_EXINT(P66_72_CC2_VCONN_OCP_INT, 0x00);

        // [0x660D] Turn Off Both CC1/2 Vconn Switch : [3:2] tpc_cc1/2_vconn_en= _DISABLE
        ScalerSetBit_EXINT(P66_0D_TPC_OCP_CTRL, ~(_BIT3 | _BIT2), 0x00); // [0x660D] <3:2> : tpc_cc1/2_vconn_en = _DISABLE
        SET_TYPE_C_0_CC_VCONN_STATUS(_OFF);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Detect Vbus On/Off to transit State
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0CcVbusDetCtrl_WDINT(bit bAction)
{
    // [0x6634] Enable Vbus Detection
    // [7] vbus_det_dis    = _ENABLE
    if(bAction == _ENABLE)
    {
        ScalerSetBit_EXINT(P66_34_CC_HW_STATE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
    }
    else
    {
        ScalerSetBit_EXINT(P66_34_CC_HW_STATE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);
    }
}

//--------------------------------------------------
// Description  : Update & Return CC Pin Resistor (Only For CC Pin, Not Vconn Pin)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerTypeC0CcDetResistor_WDINT(void)
{
    // Only Update Resistor of CC Pin, Not Vconn Pin (Flip : [7:4] CC1, Un-Flip : [3:0] CC2)
    if(GET_TYPE_C_0_CC_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
    {
        if(ScalerGetBit_WDINT(P66_2A_CC_ANA_DET_R, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0xF0)
        {
            SET_TYPE_C_0_CC_CC1_R(_TYPE_C_DET_RP_3P0A);
        }
        else
        {
            // Setting Default Result = SinkTxNG (Rp 1.5A)
            SET_TYPE_C_0_CC_CC1_R(_TYPE_C_DET_RP_1P5A);
        }

        return GET_TYPE_C_0_CC_CC1_R();
    }
    else
    {
        if(ScalerGetBit_WDINT(P66_2A_CC_ANA_DET_R, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x0F)
        {
            SET_TYPE_C_0_CC_CC2_R(_TYPE_C_DET_RP_3P0A);
        }
        else
        {
            // Setting Default Result = SinkTxNG (Rp 1.5A)
            SET_TYPE_C_0_CC_CC2_R(_TYPE_C_DET_RP_1P5A);
        }

        return GET_TYPE_C_0_CC_CC2_R();
    }
}

//--------------------------------------------------
// Description  : Process For Change Between SRC and SNK w/o Unattach
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0CcSwitchPowerRole_WDINT(BYTE ucTargetRole)
{
    if(ucTargetRole == _PD_POWER_SRC)
    {
        // 1. Set Rp to Default CC Rp
#if(_EMB_TYPE_C_0_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
        ScalerSetBit_WDINT(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_DEF << 6));
#elif(_EMB_TYPE_C_0_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
        ScalerSetBit_WDINT(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_1P5A << 6));
#else
        ScalerSetBit_WDINT(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_3P0A << 6));
#endif

        // 2. Switch Type-C HW State From SNK to SRC
        ScalerSetBit_WDINT(P66_34_CC_HW_STATE_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT6);

        if((GET_TYPE_C_0_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_0_CC_DRP_PREFER() == _TYPE_C_DRP_TRY_SRC))
        {
            // DRP Try Src FW Solution
            // [0x6630] : [3] hw_done_irq, [2] hw_done_irq_en, [1] hw_unattach_irq, [0] hw_unattach_irq_en
            // Disable hw_done_irq and hw_unattach_irq
            ScalerSetBit_WDINT(P66_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

            // [0x6658] : [1] hw_try_wait_snk_irq, [0] hw_try_wait_snk_irq_en
            // Clear and Enable hw_try_wait_snk_irq
            ScalerSetBit_WDINT(P66_58_DBCC_SNK_DET_COND, ~(_BIT3 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Set Attached.SRC to TryWait.Snk Flag
            SET_TYPE_C_0_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK();
        }
    }
    else
    {
        // Switch Type-C HW State From SRC to SNK
        ScalerSetBit_WDINT(P66_34_CC_HW_STATE_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);

        if((GET_TYPE_C_0_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_0_CC_DRP_PREFER() == _TYPE_C_DRP_TRY_SRC))
        {
            // DRP Try Src FW Solution
            // [0x6630] : [3] hw_done_irq, [2] hw_done_irq_en, [1] hw_unattach_irq, [0] hw_unattach_irq_en
            // Disable hw_done_irq and Enable hw_unattach_irq
            ScalerSetBit_WDINT(P66_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            // [0x6658] : [1] hw_try_wait_snk_irq, [0] hw_try_wait_snk_irq_en
            // Clear and Disable hw_try_wait_snk_irq
            ScalerSetBit_WDINT(P66_58_DBCC_SNK_DET_COND, ~(_BIT3 | _BIT1 | _BIT0), _BIT1);

            // Clear Attached.SRC to TryWait.Snk Flag
            CLR_TYPE_C_0_CC_ATTACHED_SRC_TO_TRY_WAIT_SNK();
        }
    }
}

#if(_EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
//--------------------------------------------------
// Description  : Enable Tool to Show Warning UI when We Provide Vbus > 5V
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeC0CcToolWarningUIControl_WDINT(bit bAction)
{
    // Tool Usage : [0x6666] [4] Used to Decide Whether Tool shall Show Warning UI when Disable Unattach HW Force Vbus Off Function([3]=0), 0 = Not Show UI, 1 = Show UI
    if(bAction == _ENABLE)
    {
        ScalerSetBit_EXINT(P66_66_SRC_FRS_INT, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    }
    else
    {
        ScalerSetBit_EXINT(P66_66_SRC_FRS_INT, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }
}
#endif  // End of #if(_EMB_TYPE_C_0_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)

#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT))

