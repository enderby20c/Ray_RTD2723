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
// ID Code      : ScalerTypeC1Pd_EXINT0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeC1Pd/ScalerTypeC1Pd.h"




#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_pucTypeC1PdDataObject_EXINT[_MAX_DATA_OBJ_CNT * 4];

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : TypeC 1 PD Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdReset_EXINT0(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1);
    enumTypeCPcbPort = enumTypeCPcbPort;

    // -------------------- HW Clear, Disable or Reset to Default Value --------------------

    // Enable SNK Detect Rp to Transit from Attached.SNK to Unattached.SNK State
    ScalerTypeC1CcSnkDetRpCtrl_EXINT0(_ENABLE);

    // [0x6B02] Disable PHY Layer BMC Tx/Rx
    ScalerSetBit_EXINT(P6B_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), 0x00);

    // [0x6B03] Reset CRCReceiver Timer / Retry Counter & Msg. ID Counter / Protocol and PHY Layer FSM
    ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P6B_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P6B_32_RX_MSG_ID_RST, ~_BIT3, 0x00);

    // WS111 GRL 2.1.2.1 PHY_BUSIDLE : Reset Rx/Tx Interframe to Default Value
    // [0x6B08] Tx Interframe Setting : [6]Interframe Gap Rst When High to Low [5:0] Interframe Gap = 63us
    ScalerSetByte_EXINT(P6B_08_PD_PHY_INTERFRAME_CFG0, 0x3F);

    // CTS TD.PD.PHY.E5 Collision Avoidance Test (Must less than 8)
    // [0x6B09] Rx Interframe Setting : [6]Interframe Gap Rst When High to Low [5:0] Interframe Gap = 6us
    ScalerSetByte_EXINT(P6B_09_PD_PHY_INTERFRAME_CFG1, 0x06);

    // [0x6BF0] Turn Off BIST Mode
    ScalerSetBit_EXINT(P6B_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // [0x6BF5-F6] Clear BIST Mode Error Counter
    ScalerSetByte_EXINT(P6B_F5_PD_BIST_ERROR_CNT1, 0x01);
    ScalerSetByte_EXINT(P6B_F6_PD_BIST_ERROR_CNT0, 0x01);

    // [0x6BDB/DC/DD] Clear and Disable Tx IRQs
    ScalerSetBit_EXINT(P6B_DB_TX_PHY_TRANS_INT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
    ScalerSetBit_EXINT(P6B_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P6B_DD_TX_PD_MSG_INT_EN, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#else
    ScalerSetBit_EXINT(P6B_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit_EXINT(P6B_DD_TX_PD_MSG_INT_EN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

    // [0x6BE8] Clear Tx FIFO
    ScalerSetByte_EXINT(P6B_E0_TX_PACKET_CFG, 0x00);
    ScalerSetBit_EXINT(P6B_E8_TX_FIFO_CTRL, ~(_BIT4 | _BIT2 | _BIT1), (_BIT4));

    // [0x6B2E] Clear and Disable Rx PHY Status IRQ
    ScalerSetBit_EXINT(P6B_2E_RX_PHY_ERR_INT, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [0x6543] Clear and Disable Rx Protocol Receive Status IRQ
    ScalerSetByte_EXINT(P6B_43_RX_RCV_STATUS_INT, 0xAA);

    // Clear Rx FIFO 0/1/2
    ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_0);
    ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_1);
    ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_2);

    // ------------------------- FW State & Counter & Flag Reset -------------------------
    // PD Initial States Setting
    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
    SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_STATE_NONE);
    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_NONE);
    ScalerTypeC1PdClrHpd_EXINT0();
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    if(GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG)
    {
        ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_LOW, 0);
    }
#endif
    CLR_TYPE_C_1_PD_ATTENTION_WAIT();
    CLR_TYPE_C_1_PD_DP_ALT_MODE_ENTER();
    SET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG(_PD_USB_CONFIG);
    CLR_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ();
    CLR_TYPE_C_1_PD_PARTNER_INIT_ALT_MODE();
    CLR_TYPE_C_1_PD_PARTNER_ALT_SUPPORT();
    SET_TYPE_C_1_PD_HPD_STATUS(_LOW);
    SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);
    CLR_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE();
    CLR_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE_DONE();

    // Reset Force Sending HPD IRQ Macros
    CLR_TYPE_C_1_PD_FORCE_HPD_IRQ();

    // Reset Lenovo Alt Mode Flags
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
    SET_TYPE_C_1_PD_LENOVO_ALT_STATE(_PD_ALT_MODE_NONE);
    CLR_TYPE_C_1_PD_LENOVO_ATTN_SENT_FLAG();
    CLR_TYPE_C_1_PD_LENOVO_ATTN_CNT();
    CLR_TYPE_C_1_PD_LENOVO_OBJ_POS();
    SET_TYPE_C_1_PD_LENOVO_DEVICE_TYPE(_TYPE_C_LENOVO_DEVICE_TYPE_NONE);
    CLR_TYPE_C_1_PD_LENOVO_ALT_MODE_ENTER();
    CLR_TYPE_C_1_PD_LENOVO_DOCK_EVENT();
    CLR_TYPE_C_1_PD_LENOVO_SYS_ACKNOWLEDGE();
    CLR_TYPE_C_1_PD_LENOVO_SYS_EVENT();
#endif

    // Reset Acer Alt Mode Flags
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
    SET_TYPE_C_1_PD_ACER_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
    CLR_TYPE_C_1_PD_ACER_ALT_MODE_ENTER();
    CLR_TYPE_C_1_PD_ACER_USER_EVENT(_TYPE_C_ACER_USER_EVENT_ALL);
    CLR_TYPE_C_1_PD_ACER_SYS_EVENT(_TYPE_C_ACER_SYS_EVENT_ALL);
#endif

    // Reset Hp Alt Mode Flags
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
    SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
    CLR_TYPE_C_1_PD_HP_ALT_MODE_ENTER();
    CLR_TYPE_C_1_PD_HP_ATTEN_RETRY_CNT();
    CLR_TYPE_C_1_PD_HP_I2C_ADDR();
    CLR_TYPE_C_1_PD_HP_OWN_AM_ADDR_H();
    CLR_TYPE_C_1_PD_HP_OWN_AM_ADDR_M();
    CLR_TYPE_C_1_PD_HP_OWN_AM_ADDR_L();
    CLR_TYPE_C_1_PD_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ALL);
    CLR_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_CNT();
    CLR_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_HEAD();
    CLR_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_TAIL();
#endif

    // Reset Dell Alt Mode Flags
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    SET_TYPE_C_1_PD_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
    CLR_TYPE_C_1_PD_DELL_ALT_MODE_ENTER();
    CLR_TYPE_C_1_PD_DELL_AM_ENTER_TIMEOUT();
    CLR_TYPE_C_1_PD_DELL_OBJ_POS();
    CLR_TYPE_C_1_PD_DELL_ATTEN_RETRY_CNT();
    CLR_TYPE_C_1_PD_DELL_ATTEN_WAIT();
    CLR_TYPE_C_1_PD_DELL_AM_INIT_COMPLETE();
    CLR_TYPE_C_1_PD_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ALL);
    CLR_TYPE_C_1_PD_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ALL);
#endif

    // Swith DP Lane Mapping
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToDx_EXINT0(enumTypeCPcbPort), GET_TYPE_C_1_PD_PIN_ASSIGNMENT(), GET_TYPE_C_1_CC_ORIENTATION());
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToPx_EXINT0(enumTypeCPcbPort), GET_TYPE_C_1_PD_PIN_ASSIGNMENT(), GET_TYPE_C_1_CC_ORIENTATION());
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    ScalerTypeC1PdUnattachCancelTimerEvent_EXINT0();

    // Reset Counters
    CLR_TYPE_C_1_PD_SRC_CAP_CNT();
    ScalerSetBit_EXINT(P6B_01_PHY_STATE_L, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_TYPE_C_1_PD_SRC_CAP_CNT());
    CLR_TYPE_C_1_PD_HARD_RST_CNT();
    CLR_TYPE_C_1_PD_CHECK_VBUS_CNT();
    CLR_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT();
    CLR_TYPE_C_1_PD_PARTNER_VDM_NO_RESP_CNT();
    CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();
    CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

    // Reset Flags
    CLR_TYPE_C_1_PD_GET_SNK_CAP_SENT();
    CLR_TYPE_C_1_PD_GET_SRC_CAP_SENT();
    CLR_TYPE_C_1_PD_PRS_REJECT();
    CLR_TYPE_C_1_PD_DRS_REJECT();
    CLR_TYPE_C_1_PD_VCS_REJECT();
    CLR_TYPE_C_1_PD_RCV_SRC_CAP();
    CLR_TYPE_C_1_PD_RCV_SNK_CAP();
    CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();
    CLR_TYPE_C_1_PD_PRS_WAIT_FLAG();
    CLR_TYPE_C_1_PD_DRS_WAIT_FLAG();
    CLR_TYPE_C_1_PD_VCS_WAIT_FLAG();
    CLR_TYPE_C_1_PD_EXPLICIT_CONTRACT();
    SET_TYPE_C_1_PD_GET_SNK_CAP_WAIT_FLAG();
    CLR_TYPE_C_1_PD_PRS_PROCESSING();
    CLR_TYPE_C_1_PD_VDMMSG_WAIT_FLAG();
    CLR_TYPE_C_1_PD_VDM_BUSY_FLAG();
    CLR_TYPE_C_1_PD_HRST_PWR_OFF();
    SET_TYPE_C_1_PD_NEW_POWER_STATE(0);
    SET_TYPE_C_1_PD_NEW_POWER_INDICATOR(0);
    CLR_TYPE_C_1_PD_TYPE_OF_ALERT(_TYPE_C_TYPE_OF_ALERT_ALL);
    CLR_TYPE_C_1_PD_BAT_STATUS(_TYPE_C_BAT_ALL);
    SET_TYPE_C_1_PD_EXT_ALERT_EVENT(_TYPE_C_EXT_ALERT_EVENT_NONE);
    CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
    SET_TYPE_C_1_PD_SPEC_VER(_PD_VERSION_3_0);
    SET_TYPE_C_1_PD_CBL_SPEC_VER(_PD_VERSION_3_0);

    // Reset Port Partner & Cable Retry Cnt
    ScalerSetBit_EXINT(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
    // Reset Cable Retry Cnt, if PD Gen >= GEN2
    ScalerSetBit_EXINT(P6B_ED_TX_PD_CBL_RTY_CNT, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
#endif
#else
    SET_TYPE_C_1_PD_SPEC_VER(_PD_VERSION_2_0);
    SET_TYPE_C_1_PD_CBL_SPEC_VER(_PD_VERSION_2_0);

    // Reset Port Partner & Cable Retry Cnt
    ScalerSetBit_EXINT(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
    // Reset Cable Retry Cnt, if PD Gen >= GEN2
    ScalerSetBit_EXINT(P6B_ED_TX_PD_CBL_RTY_CNT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
#endif
#endif

    // Reset Cable Related Flags
    SET_TYPE_C_1_PD_CBL_MAX_CUR(_PD_DEFAULT_MAX_CUR);
    SET_TYPE_C_1_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_PD_CAP_UNCONFIRMED);
    SET_TYPE_C_1_PD_CBL_PRODUCT_TYPE(_PD_PRODUCT_TYPE_UNDEFINED);
    CLR_TYPE_C_1_PD_CBL_MODAL_OPERATION_SUPPORT();
    SET_TYPE_C_1_PD_CBL_CONNECTOR_TYPE(_PD_CABLE_CONNECTOR_TYPE_UNCONFIRMED);
    CLR_TYPE_C_1_PD_CBL_EPR_MODE_CAPABLE();
    SET_TYPE_C_1_PD_CBL_TERMINATION_TYPE(_PD_CBL_TERMINATION_TYPE_UNDEFINED);
    SET_TYPE_C_1_PD_CBL_VCONN_REQUIRED();
    SET_TYPE_C_1_PD_CBL_MAX_VOL(200);
    CLR_TYPE_C_1_PD_CBL_SBU_SUPPORT();
    SET_TYPE_C_1_PD_CBL_SBU_TYPE(_PD_CBL_SBU_TYPE_UNDEFINED);
    SET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_2_ONLY);
    CLR_TYPE_C_1_PD_CBL_VBUS_THROUGH();
    CLR_TYPE_C_1_PD_CBL_SOP_PP_SUPPORT();
    SET_TYPE_C_1_PD_CBL_U3_TO_U0_TRANSITION_MODE(_PD_CBL_U3_TO_U0_UNDEFINED);
    CLR_TYPE_C_1_PD_CBL_USB_4_SUPPORT();
    CLR_TYPE_C_1_PD_CBL_USB_3_2_SUPPORT();
    SET_TYPE_C_1_PD_CBL_LANES_SUPPORT(_PD_CBL_USB_LANES_SUPPORT_UNDEFINED);
    CLR_TYPE_C_1_PD_CBL_CHARGE_THROUGH_SUPPORT();
    CLR_TYPE_C_1_PD_CBL_SOFT_RESET_REQUIRED();

#if(_TYPE_C_SVDM_VERSION >= _SVDM_VERSION_2_1)
    // Default Set to 2.1 and Downgrade to 2.0 if Cable Only Support < 2.1
    SET_TYPE_C_1_PD_CBL_SVDM_VERSION(_PD_SVDM_VER_2_1);
#else
    SET_TYPE_C_1_PD_CBL_SVDM_VERSION(_PD_SVDM_VER_2_0_EARLIER);
#endif

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    SET_TYPE_C_1_PD_CBL_DPAM_VERSION(_PD_DPAM_VER_2_0_EARLIER);
    SET_TYPE_C_1_PD_CBL_ENTER_DP_MODE_SUPPORT();
    CLR_TYPE_C_1_PD_CBL_DP_SVID_SUPPORT();
    CLR_TYPE_C_1_PD_CBL_DP_MODE_INFO_RECEIVED();
    CLR_TYPE_C_1_PD_CBL_TBT3_SVID_SUPPORT();
    SET_TYPE_C_1_PD_CBL_PIN_ASSIGNMENT(_PD_CBL_PIN_ASSIGNMENT_UNCONFIRMED);
    SET_TYPE_C_1_PD_CBL_TBT3_PRODUCT_TYPE(_PD_CBL_TBT3_PRODUCT_TYPE_UNCONFIRMED);
    SET_TYPE_C_1_PD_CBL_TBT3_DIRECTION(_PD_CBL_TBT3_DIRECTION_UNCONFIRMED);
    CLR_TYPE_C_1_PD_CBL_TBT3_RETIMER();
    CLR_TYPE_C_1_PD_CBL_TBT3_OPTICAL();
    SET_TYPE_C_1_PD_CBL_TBT3_ROUNDED_SUPPORT(_PD_CBL_TBT3_ROUNDED_SUPPORT_UNCONFIRMED);
    SET_TYPE_C_1_PD_CBL_TBT3_SPEED(_PD_CBL_TBT3_SPEED_UNCONFIRMED);
    SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_PASSIVE);
    CLR_TYPE_C_1_PD_CBL_UHBR13P5_SUPPORT();
    SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_DP_RATE_UNCONFIRMED);
#endif

    // Reset All EPR Flag
    CLR_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW();
    CLR_TYPE_C_1_PD_EPR_MODE();
    SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_RESERVED);
    SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_UNKNOWN);
    SET_TYPE_C_1_PD_PARTNER_EPR_SINK_PDP(0);

    // Clear All Port Partner Info
    SET_TYPE_C_1_PD_PARTNER_DRP(_FALSE);
    SET_TYPE_C_1_PD_PARTNER_DRD(_TRUE);
    CLR_TYPE_C_1_PD_PARTNER_SUSPEND();
    CLR_TYPE_C_1_PD_PARTNER_EXT_PWR();
    CLR_TYPE_C_1_PD_PARTNER_USB_CAP();
    CLR_TYPE_C_1_PD_PARTNER_UNCHK();
    SET_TYPE_C_1_PD_PARTNER_EPR_CAP(_FALSE);
    CLR_TYPE_C_1_PD_PARTNER_HIGH_CAP();
    CLR_TYPE_C_1_PD_PARTNER_FRS_CUR();
    SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT(0);
    SET_TYPE_C_1_PD_PARTNER_SNK_CAP_CNT(0);
    SET_TYPE_C_1_PD_PARTNER_NEW_POWER_STATE(0);
    SET_TYPE_C_1_PD_PARTNER_NEW_POWER_INDICATOR(0);
    SET_TYPE_C_1_PD_PARTNER_TYPE_OF_ALERT(_TYPE_C_TYPE_OF_ALERT_NONE);
    SET_TYPE_C_1_PD_PARTNER_BAT_STATUS(_TYPE_C_BAT_NONE);
    SET_TYPE_C_1_PD_PARTNER_EXT_ALERT_EVENT(_TYPE_C_EXT_ALERT_EVENT_NONE);

#if(_TYPE_C_SVDM_VERSION >= _SVDM_VERSION_2_1)
    // Default Set to 2.1 and Downgrade to 2.0 if Port Partner Only Support < 2.1
    SET_TYPE_C_1_PD_PARTNER_SVDM_VERSION(_PD_SVDM_VER_2_1);
#else
    SET_TYPE_C_1_PD_PARTNER_SVDM_VERSION(_PD_SVDM_VER_2_0_EARLIER);
#endif

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    // Default Set to 2.1 and Downgrade to 2.0 if Port Partner Only Support < 2.1
    SET_TYPE_C_1_PD_PARTNER_DPAM_VERSION(_PD_DPAM_VER_2_1_HIGHER);
#else
    SET_TYPE_C_1_PD_PARTNER_DPAM_VERSION(_PD_DPAM_VER_2_0_EARLIER);
#endif

    // Reset Port Partner DP Status Related Flags
    SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_CONNECT_NONE);
    CLR_TYPE_C_1_PD_PARTNER_DP_POWER_LOW();
    CLR_TYPE_C_1_PD_PARTNER_DP_FUNCTION_ENABLE();
    CLR_TYPE_C_1_PD_PARTNER_MULTI_FUNCTION();
    CLR_TYPE_C_1_PD_PARTNER_USB_CONFIG_REQUEST();
    CLR_TYPE_C_1_PD_PARTNER_DP_ALT_MODE_EXIT_REQ();
    SET_TYPE_C_1_PD_PARTNER_HPD_TYPE(_PD_HPD_NONE);
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    CLR_TYPE_C_1_PD_PARTNER_NO_DP_ALT_SUSPEND();
#endif

#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
    CLR_TYPE_C_1_PD_REQ_PPS_VOL_SMALL_STEP();
#endif

    CLR_TYPE_C_1_PD_REQ_AVS_VOL_SMALL_STEP();
}

//--------------------------------------------------
// Description  : Set PD to Default State When Attached or After Hard Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdAttachedSetting_EXINT0(EnumTypeCPDState enumPdFwState)
{
    if(enumPdFwState == _PD_SRC_START_UP)
    {
        SET_TYPE_C_1_PD_POWER_ROLE(_PD_POWER_SRC);
        SET_TYPE_C_1_PD_DATA_ROLE(_PD_DATA_DFP);
        SET_TYPE_C_1_PD_VCONN_ROLE(_PD_VCONN_SRC);

        // [0x6BE5] Setting Tx FIFO [3] Power Role / [2:1] Spec Ver = 2.0 / [0] Data Role For GoodCRC Response
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

        // [0x6B34] Setup Rx Valid Packet Type (Vconn SRC : SOP / SOP' / SOP" / Hard Reset)
        ScalerSetByte_EXINT(P6B_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        // enumPdFwState = _PD_SNK_START_UP
        SET_TYPE_C_1_PD_POWER_ROLE(_PD_POWER_SNK);
        SET_TYPE_C_1_PD_DATA_ROLE(_PD_DATA_UFP);
        SET_TYPE_C_1_PD_VCONN_ROLE(_PD_VCONN_NOT_SRC);

        // [0x6BE5] Setting Tx FIFO [3] Power Role / [2:1] Spec Ver = 2.0 / [0] Data Role For GoodCRC Response
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));

        // [0x6B34] Setup Rx Valid Packet Type (Not Vconn SRC : SOP / Hard Reset)
        ScalerSetByte_EXINT(P6B_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT0));
    }
    // [0x6B35-36] Setup Rx Msg Header Data Role/Cable Plug Golden Pattern
    // [0x6B35] [5:4] Do Not Check Power Role ('b00) / [3:2] Cable Plug ('b00) / [1:0] Data Role ('b00)
    // [0x6B36] [2:0] Support All Spec Ver ('b111)
    // Do Not Check Data Role For Interop
    ScalerSetBit_EXINT(P6B_35_RX_PORT_ROLE, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P6B_36_RX_SPEC_VER, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    SET_TYPE_C_1_PD_FW_STATE(enumPdFwState);

    // Start Up State Process
    ScalerTypeC1PdStartUpProc_EXINT0();
}

//--------------------------------------------------
// Description  : PD_FW_STATE Start Up State Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdStartUpProc_EXINT0(void)
{
    if(GET_TYPE_C_1_PD_FW_STATE() == _PD_SRC_START_UP)
    {
        ScalerTypeC1PdStartUpSetting_EXINT0();

        // Do Cable Proc Only When We Are (Vconn SRC) & (Ra Exist)
        if((GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC) && (GET_TYPE_C_1_CC_VCONN_STATUS() == _ON))
        {
            if(GET_TYPE_C_1_PD_CBL_SOFT_RESET_REQUIRED() == _TRUE)
            {
                CLR_TYPE_C_1_PD_CBL_SOFT_RESET_REQUIRED();

                // After VCS + PRS, Do Cable Soft Reset
                SET_TYPE_C_1_PD_FW_STATE(_PD_WDINT_SEND_CBL_SOFT_RESET);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Active WD Timer Event To Do Cable Soft Reset
                ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);
            }
            else
            {
                // After Attach / Hard Reset, Do Cable Discovery if VbusSafe5V
                SET_TYPE_C_1_PD_FW_STATE(_PD_WDINT_SEND_CBL_DISCOVER_ID);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Active WD Timer Event To Check Vbus, Then Do Cable Proc if VbusSafe5V
                ScalerTimerWDActivateTimerEvent_EXINT0(70, _SCALER_WD_TIMER_EVENT_PD_1_CHECK_VBUS);
            }
        }
        else
        {
            SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_WDINT_SEND_CAP);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

            // Active WD Timer Event To Check Vbus, Then Start PMIC Protection and Send SRC_CAP if VbusSafe5V
            ScalerTimerWDActivateTimerEvent_EXINT0(20, _SCALER_WD_TIMER_EVENT_PD_1_CHECK_VBUS);
        }
    }
    else if(GET_TYPE_C_1_PD_FW_STATE() == _PD_SNK_START_UP)
    {
        ScalerTypeC1PdStartUpSetting_EXINT0();

        // Transit FW_STATE to _PD_SNK_INT_WAIT_SRC_CAP and Start Power Negitiation
        SET_TYPE_C_1_PD_FW_STATE(_PD_SNK_INT_WAIT_SRC_CAP);
        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
    }
}

//--------------------------------------------------
// Description  : PD_FW_STATE Start Up State Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdStartUpSetting_EXINT0(void)
{
    BYTE ucSnkRcvSrcCapWaitPhyIdleCnt = 0;

    if(GET_TYPE_C_1_PD_FW_STATE() == _PD_SRC_START_UP)
    {
        // From 1. Unattach to Attach   2. After Hard Reset     3. After PR_SWAP    4. After FR_SWAP

        // [0x6B03] Reset PHY / Protocol Layer State
        ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT0), 0x00);

        // Update FW Usage Flags
        CLR_TYPE_C_1_PD_EXPLICIT_CONTRACT();
        ScalerSetBit_EXINT(P6B_18_VENDOR_SPECIFIC_SOP3_CFG1, ~(_BIT7 | _BIT6), (GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() << 7));

        // [0x6B03] Reset and Enable Protocol Layer State / Run CRCReceiver Timer, Retry Counter & Msg. ID
        ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P6B_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P6B_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P6B_32_RX_MSG_ID_RST, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P6B_32_RX_MSG_ID_RST, ~_BIT3, _BIT3);

        // [0x6B43] Enable Rx Rcv Msg IRQ
        ScalerTypeC1PdRxIntControl_EXINT0(_ENABLE);

        // [0x6B43] Clear and Enable Hard Reset IRQ
        ScalerSetBit_EXINT(P6B_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));

        // [0x6B02] Enable PHY Layer BMC Tx/Rx
        ScalerSetBit_EXINT(P6B_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        SET_TYPE_C_1_PD_PARTNER_REQ_VOL(0);
        CLR_TYPE_C_1_PD_SRC_CAP_CNT();

        // PR_SWAP Done, Clear Flag For Retimer Usage,
        // Spec. Require The New SRC after PR_SWAP Process Shall Wait at Least 20ms before Sending a SRC_Cap Msg., so We Comply with This Rule by Active WD Timer Event 20ms.
        CLR_TYPE_C_1_PD_PRS_PROCESSING();
    }
    else if(GET_TYPE_C_1_PD_FW_STATE() == _PD_SNK_START_UP)
    {
        // [0x6B03] Reset Phy/Protocol Layer State Machine
        ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

        // Clear Explicit Power Contract and Flags
        CLR_TYPE_C_1_PD_EXPLICIT_CONTRACT();
        ScalerSetBit_EXINT(P6B_18_VENDOR_SPECIFIC_SOP3_CFG1, ~(_BIT7 | _BIT6), (GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() << 7));

        // [0x6B32/E4] Reset and Enable Msg. ID
        ScalerSetBit_EXINT(P6B_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P6B_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P6B_32_RX_MSG_ID_RST, ~_BIT3, 0x00);
        ScalerSetBit_EXINT(P6B_32_RX_MSG_ID_RST, ~_BIT3, _BIT3);

        // [0x6B43] Enable Rx Rcv Msg IRQ
        ScalerTypeC1PdRxIntControl_EXINT0(_ENABLE);

        // [0x6B43] Clear and Enable Hard Reset IRQ
        ScalerSetBit_EXINT(P6B_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));

        // [0x6B02] Enable PHY Layer BMC Tx/Rx
        ScalerSetBit_EXINT(P6B_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Polling 200us * 10 to Wait Phy Idle (Not Concern About CRCReceive Timer)
        // To Prevent From Rcving Uncompleted Msg. and May Cause Phy/Protocol Layer State Machine to have Unexpected Behavior.
        while((ucSnkRcvSrcCapWaitPhyIdleCnt < 10) && (ScalerGetBit_EXINT(P6B_05_PD_PHY_IDLE_INT, _BIT2) == 0x00))
        {
            ucSnkRcvSrcCapWaitPhyIdleCnt += 1;
            DELAY_XUS_EXINT(200);
        }

        // [0x6B03] Enable Phy/Protocol Layer State Machine / Run CRCReceiver Timer, Retry Counter
        ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1 | _BIT0));

#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
        // [RL6828 TID] SinkWaitCapTimer
        // For Sink-Only, Powered from Vbus Products, Detect Vbus means Source Already in Attached.SRC
        // Reduce SinkWaitCapTimer "ONLY" when AC ON to Prevent >620ms Fail Afetr Hard Reset Complete
        // SinkWaitCapTimer should > 200 to Prevent from Inter-Src Cap Timer
        if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_SNK_ONLY)
        {
            SET_TYPE_C_1_PD_WD_TIMER_VALUE(_SINK_WAIT_CAP_TIMER);
            ScalerTimerWDActivateTimerEvent_EXINT0(205, _SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST);
        }
        else
        {
            SET_TYPE_C_1_PD_WD_TIMER_VALUE(_MAX_WD_EVENT_TIME);
            ScalerTimerWDActivateTimerEvent_EXINT0(_MAX_WD_EVENT_TIME, _SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST);
        }
#else
        // Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
        SET_TYPE_C_1_PD_WD_TIMER_VALUE(_MAX_WD_EVENT_TIME);
        ScalerTimerWDActivateTimerEvent_EXINT0(_MAX_WD_EVENT_TIME, _SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST);
#endif

        // PR_SWAP Done, Clear Flag For Retimer Usage
        CLR_TYPE_C_1_PD_PRS_PROCESSING();

        // Enable SNK Detect Rp to Transit from Attached.SNK to Unattached.SNK State
        ScalerTypeC1CcSnkDetRpCtrl_EXINT0(_ENABLE);
    }
}

//--------------------------------------------------
// Description  : Interrupt Handler For PD Controller
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntHandler_EXINT0(void)
{
    EnumTypeCRxFifoIndex enumRxProcFifo = _PD_RX_FIFO_RSV;

    if(GET_TYPE_C_1_PD_FUNCTION_EN() == _TRUE)
    {
        // ==================== "Hard Reset IRQ" =========================
        if(ScalerGetBit_EXINT(P6B_43_RX_RCV_STATUS_INT, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
        {
            // (rx_rcv_hardreset_irq == 1) & (irq_en = Enable)
            ScalerTypeC1PdProcHardRst_EXINT0();
        }

        // ================ " MSG TRANSMISSION DONE @ INT " ====================
        if((ScalerGetBit_EXINT(P6B_DC_TX_PD_MSG_INT, _BIT5) == _BIT5) && (ScalerGetBit_EXINT(P6B_DD_TX_PD_MSG_INT_EN, _BIT5) == _BIT5))
        {   // (tx_prl_trans_done_irq = TRUE) && (tx_prl_trans_done_irq_en = ENABLE)
            // Get PD Transmit Result
            SET_TYPE_C_1_PD_TRANSMIT_RESULT(ScalerGetBit_EXINT(P6B_DC_TX_PD_MSG_INT, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

            // Enable Rcv Msg. INT
            ScalerTypeC1PdRxIntControl_EXINT0(_ENABLE);

            // [0x6BDC] Clear IRQs
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
            ScalerSetBit_EXINT(P6B_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
            ScalerSetBit_EXINT(P6B_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

            // [0x6BDD] Disable tx_prl_trans_done IRQ
            ScalerSetBit_EXINT(P6B_DD_TX_PD_MSG_INT_EN, ~_BIT5, 0x00);

            switch(GET_TYPE_C_1_PD_TRANSMIT_RESULT())
            {
                case _PD_SENT_SUCCESS:

                    ScalerTypeC1PdIntTxSuccessProc_EXINT0();

                    break;

                case _PD_SENT_RETRY_FAIL:

                    ScalerTypeC1PdIntTxFailProc_EXINT0();

                    break;

                case _PD_SENT_DISCARDED:
                case _PD_SENT_CONFLICT:

#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                    // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
                    ScalerTypeC1PdUpdatePortPartnerRetryCounter_EXINT0();
#endif

                    if((GET_TYPE_C_1_PD_FW_STATE() != _PD_SRC_READY) && (GET_TYPE_C_1_PD_FW_STATE() != _PD_SNK_READY))
                    {
                        // SET_TYPE_C_1_PD_FW_STATE(_PD_HARDRESET) in ScalerTypeC1PdProcHardRst_EXINT0
                        ScalerTypeC1PdSendHardRst_EXINT0();
                    }
                    else
                    {
                        // TEST.PD.PROT.ALL.1 Corrupted GoodCRC : Discard the Old AMS Transmission and Send Soft_Reset (via IntRcvMsgInAmsProc Default Case) when Receiving a New AMS Message (AMS is Interrupted)
                        if(GET_TYPE_C_1_PD_AMS_STATUS() != _PD_AMS_NON_INTERRUPTIBLE)
                        {
                            if((GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_USB_CONFIG) && (GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_INT_SEND_VDM_RESP) && (GET_TYPE_C_1_PD_VDM_RESP_CONFLICT_CNT() < 2))
                            {
                                ScalerTypeC1PdActiveTimerEvent_EXINT0(1000, _SCALER_TIMER_EVENT_PD_1_VDM_RESP_CONFLICT_TIMEOUT);
                            }

                            // Set AMS = None
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                        }
                    }

                    break;

                case _PD_SENT_HARD_RST:
                default:

#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                    // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
                    ScalerTypeC1PdUpdatePortPartnerRetryCounter_EXINT0();
#endif

                    if((GET_TYPE_C_1_PD_FW_STATE() != _PD_SRC_READY) && (GET_TYPE_C_1_PD_FW_STATE() != _PD_SNK_READY))
                    {
                        // SET_TYPE_C_1_PD_FW_STATE(_PD_HARDRESET) in ScalerTypeC1PdProcHardRst_EXINT0
                        ScalerTypeC1PdSendHardRst_EXINT0();
                    }
                    else
                    {
                        // Set AMS = None
                        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                        // Back to Ready State
                        ScalerTypeC1PdBackToReadyState_EXINT0();
                    }

                    break;
            }
        }

        // ================= " Rx FIFO RCV MSG IRQ " =====================
        if(ScalerGetBit_EXINT(P6B_43_RX_RCV_STATUS_INT, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // (rx_msg_rcv_done_irq = 1) & (irq_en = Enable)
            // 1. Filter Invalid Packet (invlid_pkt || crc_err || abn_msg || goodcrc_fail || msg_id_err)
            ScalerTypeC1PdRxInvalidPktFilter_EXINT0();

            if(ScalerGetBit_EXINT(P6B_42_RX_FIFO_GENERAL_INFO, (_BIT2 | _BIT1 | _BIT0)) != 0x00)
            {
                // Check if BMC Channel and Rx PTCL State are Idle
                if((ScalerGetBit_EXINT(P6B_05_PD_PHY_IDLE_INT, _BIT2) == _BIT2) && (ScalerGetByte_EXINT(P6B_21_RX_STATE_MACHINE_L) == _BIT0))
                {
                    SET_TYPE_C_1_PD_BUS_IDLE();
                }
                else
                {
                    CLR_TYPE_C_1_PD_BUS_IDLE();
                }

                // 2. Select FIFO to Process and Set FIFO Clear Flag
                enumRxProcFifo = ScalerTypeC1PdRxFifoSelect_EXINT0();
                SET_TYPE_C_1_PD_FIFO_CLR();

                // 3. Check Message Header OK
                SET_TYPE_C_1_PD_FIFO_ERR_STATUS(ScalerGetByte_EXINT(P6B_53_RX_FIFO0_MSG_MIS_FLAG + (enumRxProcFifo * 0x20)));

                if(GET_TYPE_C_1_PD_FIFO_ERR_STATUS() == _PD_RX_MSG_CORRECT)
                {
                    // Notify Main Loop that Send Msg Has Been Interrupted
                    SET_TYPE_C_1_PD_INT_OVERWRITE();

                    // 4. Decode Rcv. Msg, and Proc According to Current State
                    ScalerTypeC1PdRxFifoMsgDecode_EXINT0(enumRxProcFifo);

                    // 5. Process FIFO According to Current State and Rcv. Message
                    if(ScalerGetByte_EXINT(P6B_54_RX_FIFO0_RCV_SOP + (enumRxProcFifo * 0x20)) == _BIT0)
                    {
                        // Rcv SOP Packet
                        if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_SOFT_RESET)
                        {
                            ScalerTypeC1PdRcvSoftRstProc_EXINT0();
                        }
                        else
                        {
                            ScalerTypeC1PdIntRcvMsgProc_EXINT0(enumRxProcFifo);
                        }
                    }
                    else if((ScalerGetByte_EXINT(P6B_54_RX_FIFO0_RCV_SOP + (enumRxProcFifo * 0x20)) == _BIT1) ||
                            (ScalerGetByte_EXINT(P6B_54_RX_FIFO0_RCV_SOP + (enumRxProcFifo * 0x20)) == _BIT2))
                    {   // Rcv SOP'/SOP" Packet
                        ScalerTypeC1PdIntRcvCableMsgProc_EXINT0(enumRxProcFifo);
                    }
                }

                // 6. Clear Processed FIFO
                if(GET_TYPE_C_1_PD_FIFO_CLR() == _TRUE)
                {
                    ScalerTypeC1PdRxFifoClear_EXINT0(enumRxProcFifo);
                }
            }

            // 7. Clear PHY Error Flags
            // ScalerSetBit_EXINT(P6B_2E_RX_PHY_ERR_INT, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            if((ScalerGetByte_EXINT(P6B_42_RX_FIFO_GENERAL_INFO) & (_BIT2 | _BIT1 | _BIT0)) == 0x00)
            {
                // 8. Clear rx_msg_rcv_done_irq Only When FIFO0/1/2 Are Empty
                ScalerSetBit_EXINT(P6B_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Process When Rcv. Msg. in Interrupt Before Ready
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntRcvMsgProc_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo)
{
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
    EnumTypeCPDRequestValid enumReqCheckResult = _PD_REQUEST_INVALID_CURRENT;
#endif

    switch(GET_TYPE_C_1_PD_FW_STATE())
    {
        case _PD_SRC_INT_WAIT_REQ:

            // Cancel WDTimerEvent (_SENDER_RESP_TIMER)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_REQUEST)
            {
                // 1. Get Port Partner's Spec Version, and decide the version for communication
                if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ||
                   ((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20)) & (_BIT7 | _BIT6)) == _BIT6))
                {   // if(Our PD Version is 2.0 || Port Partner Support Only PD 2.0)

                    // Change Spec Vesion to PD 2.0
                    SET_TYPE_C_1_PD_SPEC_VER(_PD_VERSION_2_0);

                    // Change Cable Spec Vesion to PD 2.0
                    SET_TYPE_C_1_PD_CBL_SPEC_VER(_PD_VERSION_2_0);
                }
                else
                {
                    // Set Spec Vesion to PD 3.0
                    SET_TYPE_C_1_PD_SPEC_VER(_PD_VERSION_3_0);
                }

#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
                ScalerTypeC1PdSetPortPartnerRetryCounter_EXINT0();
                ScalerTypeC1PdSetCableRetryCounter_EXINT0();
#else
                // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
                ScalerTypeC1PdUpdatePortPartnerRetryCounter_EXINT0();
#endif

                // Evaluate if Received Request is Valid
                if(ScalerTypeC1PdCheckRequestValid_EXINT0() == _PD_REQUEST_VALID)
                {
                    SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_INT_SEND_ACCEPT_REQ);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {   // TD.PD.SRC.E14 : Receive Unexpected Msg. in "_PD_SRC_INT_WAIT_REQ", Do Soft Reset
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        case _PD_SRC_INT_WAIT_EPR_REQ:

            // Cancel WDTimerEvent (_SENDER_RESP_TIMER)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_EPR_REQUEST)
            {
                enumReqCheckResult = ScalerTypeC1PdCheckRequestValid_EXINT0();

                // Evaluate if Received Request is Valid
                if(enumReqCheckResult == _PD_REQUEST_VALID)
                {
                    SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_INT_SEND_ACCEPT_REQ);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                }
                else if(enumReqCheckResult == _PD_REQUEST_INVALID_COPY_PDO)
                {
                    ScalerTypeC1PdSendHardRst_EXINT0();
                }
                else
                {
                    SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }
            else if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_REQUEST)
            {
                ScalerTypeC1PdSendHardRst_EXINT0();
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;
#endif

        case _PD_SNK_INT_WAIT_SRC_CAP:

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
            // [FW Sol. for _TYPE_C_5B_LS_ADC_GEN_1] Write 1 Clear 5Bit LS_ADC Vbus Off IRQ and Enable IRQ_EN to Detect Unattach Event
            ScalerTypeCAdcOnOffCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _OFF, _ENABLE);
#else
            // Enable Vbus Detection For CC HW to Detect Unattach Event
            ScalerTypeC1CcVbusDetCtrl_EXINT0(_ENABLE);
#endif

            // Cancel WDTimerEvent (_SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST);

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_SRC_CAP)
            {
                // 1. Get Port Partner's Spec Version, and Decide the Version for Communication
                if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ||
                   ((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20)) & (_BIT7 | _BIT6)) == _BIT6))
                {   // if(Our PD Version is 2.0 || Port Partner Support Only PD 2.0)

                    // Change Spec Vesion to PD 2.0
                    SET_TYPE_C_1_PD_SPEC_VER(_PD_VERSION_2_0);

                    // Change Cable Spec Vesion to PD 2.0
                    SET_TYPE_C_1_PD_CBL_SPEC_VER(_PD_VERSION_2_0);
                }
                else
                {
                    // Set Spec Vesion to PD 3.0
                    SET_TYPE_C_1_PD_SPEC_VER(_PD_VERSION_3_0);
                }

#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
                ScalerTypeC1PdSetPortPartnerRetryCounter_EXINT0();
                ScalerTypeC1PdSetCableRetryCounter_EXINT0();
#else
                // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
                ScalerTypeC1PdUpdatePortPartnerRetryCounter_EXINT0();
#endif

                // 2. Store Src_Cap Info from Data Objects
                SET_TYPE_C_1_PD_PARTNER_DRP(g_pucTypeC1PdDataObject_EXINT[0] >> 5);
                SET_TYPE_C_1_PD_PARTNER_SUSPEND(g_pucTypeC1PdDataObject_EXINT[0] >> 4);
                SET_TYPE_C_1_PD_PARTNER_EXT_PWR(g_pucTypeC1PdDataObject_EXINT[0] >> 3);
                SET_TYPE_C_1_PD_PARTNER_USB_CAP(g_pucTypeC1PdDataObject_EXINT[0] >> 2);
                SET_TYPE_C_1_PD_PARTNER_DRD(g_pucTypeC1PdDataObject_EXINT[0] >> 1);
                SET_TYPE_C_1_PD_PARTNER_UNCHK(g_pucTypeC1PdDataObject_EXINT[0] >> 0);
                SET_TYPE_C_1_PD_PARTNER_EPR_CAP(g_pucTypeC1PdDataObject_EXINT[1] >> 7);

                // Get Number Of Capabilities
                SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT(GET_TYPE_C_1_PD_RCV_NOD_CNT());

                // Evaluate and Set Request Data Objects
                for(BYTE ucLoopIndex = 0; ucLoopIndex < _TYPE_C_PDO_NUM_7; ucLoopIndex++)
                {
                    if(ucLoopIndex < GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT())
                    {
                        if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                        {
                            // Set APDO Type
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex, ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                        }
                        else
                        {
                            // Set PDO Type
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex, ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) >> 6));
                        }

                        if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                        {
                            // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex, (((((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & 0x01)) << 7) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 1] & 0xFE)) >> 1)) * 10));
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(ucLoopIndex, (((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2]) * 10));
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(ucLoopIndex, (((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 3] & 0x7F) * 5));
                        }
                        else
                        {
                            // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex, (((((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2] & 0xFC)) >> 2)) * 5));
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(ucLoopIndex, GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex));
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(ucLoopIndex, (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 3]));
                            SET_TYPE_C_1_PD_PARTNER_SRC_PEAK_CUR(ucLoopIndex, ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 1] & (_BIT5 | _BIT4)) >> 4));

                            // If Target Voltage Matches Partner's Voltage, Set the Macros of Capability Mismatch and Object Position.
                            if((GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_TARGET_VOL) && (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex) == (GET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL() * 10)))
                            {
                                SET_TYPE_C_1_PD_REQ_CAP_MIS(_FALSE);
                                SET_TYPE_C_1_PD_REQ_OBJ_POS((EnumTypeCPdoNumber)(ucLoopIndex + 1));
                            }
                        }
                    }
                    else
                    {
                        // If ucLoopIndex >= GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT(), Clear the Related Macros to 0x00.
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex, _PD_NONE_SETTING_PDO);
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex, 0x00);
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(ucLoopIndex, 0x00);
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(ucLoopIndex, 0x00);
                        SET_TYPE_C_1_PD_PARTNER_SRC_PEAK_CUR(ucLoopIndex, 0x00);
                    }
                }

                // According to the corresponding Request Type, Set the Macros of Capability Mismatch and Object Position.
                if(GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_LOWEST_VOL)
                {
                    SET_TYPE_C_1_PD_REQ_CAP_MIS(_FALSE);
                    SET_TYPE_C_1_PD_REQ_OBJ_POS(_TYPE_C_PDO_NUM_1);
                }
                else if(GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_HIGHEST_VOL)
                {
                    SET_TYPE_C_1_PD_REQ_CAP_MIS(_FALSE);

                    // Select Highest Fix PDO
                    for(BYTE ucLoopIndex = GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT(); ucLoopIndex > 0; ucLoopIndex--)
                    {
                        if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex - 1) == _PD_FIX_SUPPLY_PDO)
                        {
                            SET_TYPE_C_1_PD_REQ_OBJ_POS((EnumTypeCPdoNumber)(ucLoopIndex));

                            break;
                        }
                    }
                }
                else if((GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_TARGET_VOL) && (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) != (GET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL() * 10)))
                {
#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
                    // [MM1AE-4187] Don't Set Capability Mismatch for Powered from Vbus 5.1V RDO
                    if(GET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL() != 51)
                    {
                        SET_TYPE_C_1_PD_REQ_CAP_MIS(_TRUE);
                    }
#else
                    SET_TYPE_C_1_PD_REQ_CAP_MIS(_TRUE);
#endif

                    SET_TYPE_C_1_PD_REQ_OBJ_POS(_TYPE_C_PDO_NUM_1);
                }

                // If Request Type isn't Customized RDO, Need to be Set Operating and Max. Current.
                if(GET_TYPE_C_1_PD_REQ_TYPE() != _TYPE_C_REQ_CUSTOMIZED_RDO)
                {
                    SET_TYPE_C_1_PD_REQ_INFO_1(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1));
                    SET_TYPE_C_1_PD_REQ_INFO_2(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1));
                }

                // Send Request (Success : Wait Resp / Fail : Hard Reset)
                SET_TYPE_C_1_PD_RCV_SRC_CAP();
                SET_TYPE_C_1_PD_FW_STATE(_PD_SNK_INT_SEND_REQUEST);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REQUEST, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Receive Unexpected Msg. in "_PD_SNK_INT_WAIT_SRC_CAP", Do Hard Reset
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SNK_INT_WAIT_REQ_RESP:

            // Cancel WDTimerEvent(SENDER_RESP_TIMEOUT)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_ACCEPT)
            {
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
                // Disable Detect Sink OVP/UVP
                ScalerTypeC1PmicSetting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
#endif

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
                // [FW Sol. for _TYPE_C_5B_LS_ADC_GEN_1] Write 1 Clear 5Bit LS_ADC Vbus Off IRQ and Disable IRQ_EN
                ScalerTypeCAdcOnOffCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _OFF, _DISABLE);
#else
                // Turn Off Type-C Unattach Vbus Detection
                ScalerTypeC1CcVbusDetCtrl_EXINT0(_DISABLE);
#endif

                // Update PDO Status (Voltage in 10mV / Current in 10mA)
                if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
                {
                    // Request to Fix PDO (REQ_INFO_1 = Op. Cur in 10mA / REQ_INFO_2 = Max. Cur in 10mA)
                    SET_TYPE_C_1_PD_PDO_STATUS_VOL(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1));
                    SET_TYPE_C_1_PD_PDO_STATUS_CUR(GET_TYPE_C_1_PD_REQ_INFO_2());
                }
                else
                {
                    // Request to PPS PDO (REQ_INFO_1 = Vol in 20mV / REQ_INFO_2 = Op. Cur in 50mA)
                    SET_TYPE_C_1_PD_PDO_STATUS_VOL(GET_TYPE_C_1_PD_REQ_INFO_1() * 2);
                    SET_TYPE_C_1_PD_PDO_STATUS_CUR(GET_TYPE_C_1_PD_REQ_INFO_2() * 5);
                }

                // Transit to _PD_SNK_INT_WAIT_PS_RDY
                SET_TYPE_C_1_PD_FW_STATE(_PD_SNK_INT_WAIT_PS_RDY);

                // Source Begin to Transit Power
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_POWER_TRANSITION);

                // Active WD Timer Event For PS Transition Timer (450-550ms), Timeout : Hard Reset
                SET_TYPE_C_1_PD_WD_TIMER_VALUE(_MAX_WD_EVENT_TIME);
                ScalerTimerWDActivateTimerEvent_EXINT0(_MAX_WD_EVENT_TIME, _SCALER_WD_TIMER_EVENT_PD_1_PS_TRANSITION_TIMEOUT);
            }
            else if((GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_REJECT) || (GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_WAIT))
            {
                if(GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() == _TRUE)
                {
                    // Set AMS = None
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeC1PdBackToReadyState_EXINT0();

                    if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_WAIT)
                    {
                        SET_TYPE_C_1_PD_REQ_WAIT_FLAG();

                        // Re-Evaluate and Send Request After 100 ms if New Power Needed in Snk Ready State Flow
                        ScalerTypeC1PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_REQ_WAIT);
                    }
                }
                else
                {
                    SET_TYPE_C_1_PD_FW_STATE(_PD_SNK_INT_WAIT_SRC_CAP);
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                    // Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
                    SET_TYPE_C_1_PD_WD_TIMER_VALUE(_MAX_WD_EVENT_TIME);
                    ScalerTimerWDActivateTimerEvent_EXINT0(_MAX_WD_EVENT_TIME, _SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST);
                }
            }
            else
            {
                // Receive Unexpected Msg. in "_PD_SNK_INT_WAIT_REQ_RESP", Do Soft Reset
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SNK_INT_WAIT_PS_RDY:

            // Cancel WDTimerEvent (PS_TRANSITION_TIMER, SEND_HARD_RST)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_PS_TRANSITION_TIMEOUT);

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_PS_RDY)
            {
                // Set AMS = None
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeC1PdBackToReadyState_EXINT0();

                SET_TYPE_C_1_PD_EXPLICIT_CONTRACT();
                ScalerSetBit_EXINT(P6B_18_VENDOR_SPECIFIC_SOP3_CFG1, ~(_BIT7 | _BIT6), (GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() << 7));

#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
                // Clear OCP/OVP/UVP/Vconn OCP Event and Alert Macro due to New Power Contract Established
                CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);
                CLR_TYPE_C_1_PD_ALERT_SENT();
#endif

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
                // Set PARTNER_ALT_SUPPORT FLAG for Sink in Ready to Wait For Port Partner Initiating Alt Mode Flow
                SET_TYPE_C_1_PD_PARTNER_ALT_SUPPORT();

                // Sink Start PR_SWAP to Provide Power, if Not Enter ALt Mode in 2 Sec After Power Contract, timeout: Clear PARTNER_ALT_SUPPORT Macro
                ScalerTypeC1PdActiveTimerEvent_EXINT0(_PARTNER_ALT_SUPPORT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_PARTNER_ALT_SUPPORT);
#endif

                // Adjust Sink Unattach Vth
                ScalerTypeCAdcUnattachVthAdjust_EXINT0(_TYPE_C_CHANNEL_1_VMON, GET_TYPE_C_1_PD_PDO_STATUS_VOL());

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
                // Update Vbus Power Info to Support Sink OVP/UVP
                ScalerTypeC1PmicSetting_EXINT0(_ON, _PD_POWER_SNK, GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1), GET_TYPE_C_1_PD_PDO_STATUS_VOL(), GET_TYPE_C_1_PD_PDO_STATUS_CUR(), _PD_PEAK_CUR_NONE);
#endif

#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON))
                // Start PMIC Protection
                ScalerTypeC1PmicProtectStart_EXINT0(_TYPE_C_POWER_SNK);
#endif

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
                // [FW Sol. for _TYPE_C_5B_LS_ADC_GEN_1] Write 1 Clear 5Bit LS_ADC Vbus Off IRQ and Enable IRQ_EN to Detect Unattach Event
                ScalerTypeCAdcOnOffCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _OFF, _ENABLE);
#else
                // Enable Vbus Detection For CC HW to Detect Unattach Event
                ScalerTypeC1CcVbusDetCtrl_EXINT0(_ENABLE);
#endif
            }
            else
            {
                // Receive Unexpected Msg. in "_PD_SNK_INT_WAIT_PS_RDY", Do Hard Reset
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_INT_WAIT_SOFTRESET_RESP:

            // Cancel WD TimerEvent (INT Send Soft Rst)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);

            // [LECROY] TD PD.LL.E04 Hard Reset Usage : Send SoftReset, Then Rcv. Accept with Msg.ID = 1 Shall Ignore.
            if((GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_ACCEPT) && (ScalerGetBit_EXINT(P6B_56_RX_FIFO0_MSG_HEADER0 + (enumRxProcFifo * 0x20), (_BIT3 | _BIT2 | _BIT1)) == 0x00))
            {
                if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
                {
                    if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
                    {
                        SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_READY);
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_WDINT_SEND_EPR_SRC_CAP);

                        // Active WD Timer Event To Send EPR_SRC_CAP, Timeout : Send EPR_SRC_CAP.
                        ScalerTimerWDActivateTimerEvent_EXINT0(20, _SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_SRC_CAP);
                    }
                    else
                    {
                        // Clear Explicit Power Contract and Flags
                        CLR_TYPE_C_1_PD_EXPLICIT_CONTRACT();
                        ScalerSetBit_EXINT(P6B_18_VENDOR_SPECIFIC_SOP3_CFG1, ~(_BIT7 | _BIT6), (GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() << 7));

                        SET_TYPE_C_1_PD_PARTNER_REQ_VOL(0);
                        CLR_TYPE_C_1_PD_SRC_CAP_CNT();

                        SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_WDINT_SEND_CAP);
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
                        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                        // Active WD Timer Event To Send 1st SRC_CAP, Timeout : Send SRC_CAP.
                        ScalerTimerWDActivateTimerEvent_EXINT0(20, _SCALER_WD_TIMER_EVENT_PD_1_SEND_SRC_CAP);
                    }
                }
                else
                {
                    // Clear Explicit Power Contract and Flags
                    CLR_TYPE_C_1_PD_EXPLICIT_CONTRACT();
                    ScalerSetBit_EXINT(P6B_18_VENDOR_SPECIFIC_SOP3_CFG1, ~(_BIT7 | _BIT6), (GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() << 7));

                    // Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
                    SET_TYPE_C_1_PD_WD_TIMER_VALUE(_MAX_WD_EVENT_TIME);
                    ScalerTimerWDActivateTimerEvent_EXINT0(_MAX_WD_EVENT_TIME, _SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST);

                    SET_TYPE_C_1_PD_FW_STATE(_PD_SNK_INT_WAIT_SRC_CAP);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                }
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SNK_READY:

            if((GET_TYPE_C_1_PD_AMS_STATUS() == _PD_AMS_NONE) || (GET_TYPE_C_1_PD_AMS_STATUS() == _PD_AMS_INTERRUPTIBLE))
            {
                // Receive Any Message When Not in AMS or in Interruptible AMS
                ScalerTypeC1PdIntSnkRcvMsgNoAmsProc_EXINT0();
            }
            else
            {
                // Rcv. Msg. During Non-Interruptible AMS / Power Transition
                ScalerTypeC1PdIntRcvMsgInAmsProc_EXINT0(enumRxProcFifo);
            }
            break;

        case _PD_SRC_READY:

            if((GET_TYPE_C_1_PD_AMS_STATUS() == _PD_AMS_NONE) || (GET_TYPE_C_1_PD_AMS_STATUS() == _PD_AMS_INTERRUPTIBLE))
            {
                // Receive Any Message When Not in AMS or in Interruptible AMS
                ScalerTypeC1PdIntSrcRcvMsgNoAmsProc_EXINT0();
            }
            else
            {
                // Rcv. Msg. During Non-Interruptible AMS / Power Transition
                ScalerTypeC1PdIntRcvMsgInAmsProc_EXINT0(enumRxProcFifo);
            }
            break;

        case _PD_WDINT_SEND_CBL_DISCOVER_ID:
        case _PD_INT_SEND_CBL_DISCOVER_ID:
        case _PD_INT_WAIT_CBL_DISCOVER_ID_RESP:
        case _PD_WDINT_SEND_CBL_SOFT_RESET:
        case _PD_INT_SEND_CBL_SOFT_RESET:
        case _PD_INT_WAIT_CBL_SOFT_RESET_RESP:

            // Receive Unexpected Msg. Do Soft Reset.
            ScalerTypeC1PdPrlErrHandle_EXINT0();

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

            ScalerTypeC1PdSendHardRst_EXINT0();

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
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntSrcRcvMsgNoAmsProc_EXINT0(void)
{
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
    EnumTypeCPDRequestValid enumReqCheckResult = _PD_REQUEST_INVALID_CURRENT;
#endif

    // Set Rp to SinkTxOK When Source Receive Message Before Initiate AMS
    if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
    {
        ScalerSetBit_EXINT(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), _PD_SINK_TX_OK);

        if(GET_TYPE_C_1_PD_FORCE_HPD_IRQ() == _TRUE)
        {
            CLR_TYPE_C_1_PD_FORCE_HPD_IRQ();

            // Push HPD_IRQ into HPD Queue When Force Sending HPD IRQ Failed, then PD will Re-Send HPD_IRQ in Main loop
            ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_IRQ, 0);

            // Cancel _SRC_INIT_AMS_TIMER (16 ~ 20ms) When Received any Msg before _SRC_INIT_AMS_TIMER Timeout
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_TX_AVALIABLE);
        }
    }

    if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
    {
        // Cancel SourceEPRKeepAliveTimer (750~1000ms)
        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT);

        if((GET_TYPE_C_1_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT) && (GET_TYPE_C_1_PD_TIMER_EVENT_VALID() == _TRUE))
        {
            CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();
        }
    }

    // Receive Any Message When Not in AMS or in Interruptible AMS @ _PD_SRC_READY
    switch(GET_TYPE_C_1_PD_RCV_MSG())
    {
        case _PD_CMD_REQUEST:

            if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
            {
                // Send Hard Reset When Receives a Request in EPR Mode
                ScalerTypeC1PdSendHardRst_EXINT0();
            }
            else
            {
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
                // Cancel TimerEvent for PPS PDO
                ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_PPS_TIMEOUT);
#endif

                // Set AMS to Non-Interruptible
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                // Evaluate if Received Request is Valid
                if(ScalerTypeC1PdCheckRequestValid_EXINT0() == _PD_REQUEST_VALID)
                {
                    SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_INT_SEND_ACCEPT_REQ);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_GET_SRC_CAP:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Source Capabilities"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_SRC_CAP);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);

            // FW Solution : Samsung S8 Plug-in then Start, Fail to Light Up
#if((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) && (_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON))
            // S8 Send "Get Src Cap" When Start, but Not Trying to Initiate Alt Mode as DFP (Scaler UFP / No Alt Mode)
            if((GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_UFP) && (GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() != _PD_DP_CONFIG) && (GET_TYPE_C_1_PD_INTEROP_S8() == _FALSE))
            {
                // Wait 5 sec for other Devices to Enter Alt Mode, Timeout : Hard Reset (Cancel : PD Reset, Rcv Discover ID)
                ScalerTypeC1PdActiveTimerEvent_EXINT0(5000, _SCALER_TIMER_EVENT_PD_1_S8_HRST);

                // Set Interop Flag to Prevent From "Non-AM Device with Get Src Cap" Device will be Infinitly Triggered
                SET_TYPE_C_1_PD_INTEROP_S8();
            }
#endif

            break;

        case _PD_CMD_GET_SNK_CAP:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

#if((_TYPE_C_1_PD_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
            if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                // Send "Sink Capabilities"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_SNK_CAP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SNK_CAP, _PD_VDM_CMD_RESERVED);
            }
            else
#endif
            {
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "Reject"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_PR_SWAP:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

#if(_TYPE_C_1_PD_SRC_ACCEPT_SWAP_TO_SNK == _TRUE)
            if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                if(GET_TYPE_C_1_PD_GET_SNK_CAP_SENT() == _FALSE)
                {
                    // Send "WAIT" Until Get Partnet's Sink Cap
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_WAIT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_WAIT, _PD_VDM_CMD_RESERVED);
                }
                else if(GET_TYPE_C_1_PD_PARTNER_EXT_PWR() == _TRUE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_PRS);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                }
                else

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                if(GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _FALSE)
                {
                    if(GET_TYPE_C_1_PD_GET_SRC_CAP_SENT() == _FALSE)
                    {
                        // Send "WAIT" Until Get Partnet's Src Cap
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_WAIT);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_WAIT, _PD_VDM_CMD_RESERVED);
                    }
                    else if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CHECK_RESULT() == _PD_SRC_CAP_VALID)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_PRS);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                    }
                }
                else
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                {
                    // CTS Spec: DRP shall respond with Reject Msg.
                    // Send "Reject"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }
            else
#endif  // End of #if(_TYPE_C_1_PD_SRC_ACCEPT_SWAP_TO_SNK == _TRUE)
            {
                if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_SRC_ONLY) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0))
                {
                    // CTS Spec: Provider Only shall respond with Not_Supported Msg.
                    // Send "Not Support"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // PD 2.0 Standard Spec: Respond with Reject Msg.
                    // CTS Spec: DRP shall respond with Reject Msg.
                    // Send "Reject"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_DR_SWAP:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_VENDOR_ALT_MODE_NONE)
            if(GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE)
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
            if((GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE) && (GET_TYPE_C_1_PD_LENOVO_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
            if((GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE) && (GET_TYPE_C_1_PD_ACER_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
            if((GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE) && (GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
            if((GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE) && (GET_TYPE_C_1_PD_DELL_ALT_MODE_ENTER() == _FALSE))
#endif
            {
                if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
                {
#if(_TYPE_C_1_PD_DFP_SWAP_TO_UFP == _TRUE)
                    // Accept Swap from DFP -> UFP
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_DRS);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);

                    // Fix Lecroy [COMMON.CHECK.PD.3 Check GoodCRC]
                    ScalerSetBit_EXINT(P6B_3A_RX_CRC_RESPONSE_CTRL, ~(_BIT4), _BIT4);
#else
                    // Reject Swap from DFP -> UFP
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
#endif
                }
                else
                {
#if(_TYPE_C_1_PD_UFP_SWAP_TO_DFP == _TRUE)
                    // Accept Swap from UFP -> DFP
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_DRS);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
#else
                    // Reject Swap from UFP -> DFP
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
#endif
                }
            }
            else
            {
                // Receive DR_SWAP When in Alt Mode : Hard Reset
                ScalerTypeC1PdSendHardRst_EXINT0();
            }

            break;

        case _PD_CMD_VCONN_SWAP:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Evaluate Vconn Swap : Vconn Source Must "Accept", Not Vconn Source Can "Accept/Reject/Wait"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_VCS);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_BIST:

            // BIST Mode Operate Only in vSafe5v
            if(GET_TYPE_C_1_PD_PARTNER_REQ_VOL() == 500)
            {
                SET_TYPE_C_1_PD_BIST_MODE((g_pucTypeC1PdDataObject_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

                if(GET_TYPE_C_1_PD_BIST_MODE() == (_BIT2 | _BIT0))
                {
                    // If Carrier Mode : Output 0101... for 30-60ms
                    // Turn On BIST UUT Carrier Mode
                    ScalerSetBit_EXINT(P6B_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
                    ScalerSetBit_EXINT(P6B_F1_PD_BIST_PATTERN, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

                    // Disable Rcv Msg INT
                    ScalerTypeC1PdRxIntControl_EXINT0(_DISABLE);

                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_BIST_MODE);

                    // Begin BIST Mode
                    ScalerSetBit_EXINT(P6B_F0_PD_BIST_CFG, ~_BIT2, _BIT2);

                    // If BIST Carrier Mode, Back to Ready State After 30-60ms
                    ScalerTimerWDActivateTimerEvent_EXINT0(45, _SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);
                }
                else if(GET_TYPE_C_1_PD_BIST_MODE() == _BIT3)
                {
                    // If Test Data Mode : Do Nothing, Turn Off Rcv. Msg INT and Wait For HardReset
                    // Turn On BIST UUT Test Data Mode
                    ScalerSetBit_EXINT(P6B_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_BIST_MODE);

                    // [0x6B34] Setup Rx Valid Packet Type (SOP / Hard Reset)
                    ScalerSetByte_EXINT(P6B_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT0));

                    // Begin BIST Mode in Interrupt for CTS
                    ScalerSetBit_EXINT(P6B_F0_PD_BIST_CFG, ~_BIT2, _BIT2);

                    // Disable Rcv Msg INT
                    ScalerTypeC1PdRxIntControl_EXINT0(_DISABLE);
                }
            }

            // NOTE : WS111 GRL 2.1.2.1 PHY_BUSIDLE was Removed

            break;

        case _PD_CMD_VDM:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            if(GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE)
            {
                if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
                {   // DFP Rcv Any VDM Resp. or Attention Request When Alt Mode Ready
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
                    ScalerTypeC1PdIntDfpRcvVdmMsgProc_EXINT0();
#endif
                }
                else
                {   // Receive VDM Request, UFP Responds According to Rcv. VDM Msg.
                    ScalerTypeC1PdIntUfpRcvVdmMsgProc_EXINT0();
                }
            }
            else
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            {
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        // PD 3.0 Control Message
        case _PD_CMD_GET_SRC_CAP_EXT:

            // [MM1AE-2561] Send Not Support for MacBook Interop Issue.
            // Send "Not Support"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_GET_SNK_CAP_EXT:

            if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_SRC_ONLY)
            {
                // Send "Not Support"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                // Send "Sink Capability Extended"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_SNK_CAP_EXT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SNK_CAP_EXT, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_CMD_GET_STATUS:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Status"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_STATUS);

            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_STATUS, _PD_VDM_CMD_RESERVED);

            break;

#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
        case _PD_CMD_GET_PPS_STATUS:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Status"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_PPS_STATUS);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_PPS_STATUS, _PD_VDM_CMD_RESERVED);

            break;
#endif

        // PD 3.0 Data Message
        case _PD_CMD_ALERT:

            SET_TYPE_C_1_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_ALERT_EVENT);
            SET_TYPE_C_1_PD_PARTNER_TYPE_OF_ALERT((EnumTypeCTypeOfAlert)(g_pucTypeC1PdDataObject_EXINT[0]));
            SET_TYPE_C_1_PD_PARTNER_BAT_STATUS((EnumTypeCBatteryStatus)(g_pucTypeC1PdDataObject_EXINT[1]));
            SET_TYPE_C_1_PD_PARTNER_EXT_ALERT_EVENT((EnumTypeCExtAlertEventType)(g_pucTypeC1PdDataObject_EXINT[3] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            // Check Battery Status
            if((g_pucTypeC1PdDataObject_EXINT[0] & (_BIT1)) == _BIT1)
            {
                // Send "Get Battery Status Message" if Needed
            }

            // Check Status
            if((g_pucTypeC1PdDataObject_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
            {
                // Send "Get Status Message"
                // [MQP] : PROT-SNK3-STATUS(Rev3.0), Shall Initiate GET_STATUS Msg. When SnkTXOK
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
            }

            break;

        // PD 3.0 Extended Message
        case _PD_CMD_GET_MFC_INFO:
#if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
            // Send "Not Support"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
#else
            // Follow Standard Spec.
            // for DRP, PD 3.0 Standard Spec(USB_PD_R3_0 V1.2 20180621 - with ECRs 2018-09-24): Ignore
            if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_SRC_ONLY)
            {
                // for SRC Only, Send "Not Support"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
#endif // End of #if(_TYPE_C_EMB_CTS_FLOW == _ON)
#else
            // Byte 0-1 are Ext. Msg Header
            // Manufacturer Info Target "g_pucTypeC1PdDataObject_EXINT[2]" : 0 = Port / 1 = Battery
            if(g_pucTypeC1PdDataObject_EXINT[2] == 0x00)
            {
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                // Send "Manufacturer Info"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_MFC_INFO);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_MFC_INFO, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Not Support"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
#endif  // End of #if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
            break;

        case _PD_CMD_CHUNK_TEST:

            // Check If This Ext Msg is Chunked : Ext Message Header [15]
            if((GET_TYPE_C_1_PD_CHUNKED_MESSAGE() == _TRUE) && (GET_TYPE_C_1_PD_CHUNK_REQUEST() == _FALSE))
            {
                // If Received Chunk Response Data < Total Message Data Size, Sent Chunk Request
                if(((GET_TYPE_C_1_PD_CHUNK_NUMBER() + 1) * 26) < GET_TYPE_C_1_PD_EXT_MSG_DATA_SIZE())
                {
                    // Set Chunk Message As an Chunk Request
                    SET_TYPE_C_1_PD_CHUNK_REQUEST(_TRUE);

                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                    // Send "Chunk Test" REQUEST
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_CHK_TEST_REQ);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_CHUNK_TEST, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }

            break;

        // PD 3.0 Control Message
        case _PD_CMD_FR_SWAP:

            // CTS : For UUT AS SRC, But Not Support FR_Swap
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;

        // PD 3.0 Control Message
        case _PD_CMD_GET_REVISION:

            // Send "Revision Message"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REVISION);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REVISION, _PD_VDM_CMD_RESERVED);

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        case _PD_CMD_EPR_MODE:

            switch(g_pucTypeC1PdDataObject_EXINT[0])
            {
                case _PD_EPR_MODE_ENTER:

                    // If Received EPR Mode Enter, Start Enter EPR Mode Flow
                    SET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW();
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                    // Set EPR Sink Operational PDP
                    SET_TYPE_C_1_PD_PARTNER_EPR_SINK_PDP(g_pucTypeC1PdDataObject_EXINT[1]);

                    if(ScalerTypeC1PdCheckEPRCapable_EXINT0() == _TRUE)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_ACK);

                        // If Both Port Partners Support EPR Mode : Send Enter ACK
                        SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_ACK);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);

                        // If Source or Sink Not EPR Capable : Send Enter Failed
                        SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                    }

                    break;

                case _PD_EPR_MODE_EXIT:

                    if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
                    {
                        // Check the Port Partners are in an Explicit Contract with an SPR PDO
                        if((GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() > 0) && (GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() <= GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT()))
                        {
                            CLR_TYPE_C_1_PD_EPR_MODE();

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                            // Send "Source Capabilities"
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_SRC_CAP);
                            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);
                        }
                        else
                        {
                            ScalerTypeC1PdSendHardRst_EXINT0();
                        }
                    }
                    else
                    {
                        ScalerTypeC1PdPrlErrHandle_EXINT0();
                    }

                    break;

                default:

                    ScalerTypeC1PdPrlErrHandle_EXINT0();

                    break;
            }

            break;

        case _PD_CMD_EPR_REQUEST:

            if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
            {
                // Set AMS to Non-Interruptible
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                enumReqCheckResult = ScalerTypeC1PdCheckRequestValid_EXINT0();

                // Evaluate if Received Request is Valid
                if(enumReqCheckResult == _PD_REQUEST_VALID)
                {
                    SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_INT_SEND_ACCEPT_REQ);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
                }
                else if(enumReqCheckResult == _PD_REQUEST_INVALID_COPY_PDO)
                {
                    ScalerTypeC1PdSendHardRst_EXINT0();
                }
                else
                {
                    SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_INT_SEND_REJECT_REQ);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // Send Hard Reset When Receives a EPR Request in SPR Mode
                ScalerTypeC1PdSendHardRst_EXINT0();
            }

            break;

        case _PD_CMD_EXTENDED_CONTROL:

            // Set AMS to Non-Interruptible
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            switch(g_pucTypeC1PdDataObject_EXINT[2])
            {
                case _PD_EXT_CTRL_TYPE_EPR_GET_SRC_CAP:

                    if(GET_TYPE_C_1_PD_EPR_SRC_CAPABLE() == _TRUE)
                    {
                        // Send EPR Source Cap
                        CLR_TYPE_C_1_PD_TX_CHUNK_NUMBER();
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_SRC_CAP);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_SRC_CAP, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        // Send "Not Support"
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                    }

                    break;

                case _PD_EXT_CTRL_TYPE_EPR_KEEP_ALIVE:

                    if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_KEEP_ALIVE_ACK);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                        // Send Keep Alive ACK
                        SET_TYPE_C_1_PD_EXT_CTRL_TYPE(_PD_EXT_CTRL_TYPE_EPR_KEEP_ALIVE_ACK);
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EXTENDED_CONTROL, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        ScalerTypeC1PdPrlErrHandle_EXINT0();
                    }

                    break;

                case _PD_EXT_CTRL_TYPE_EPR_KEEP_ALIVE_ACK:

                    ScalerTypeC1PdPrlErrHandle_EXINT0();

                    break;

                case _PD_EXT_CTRL_TYPE_EPR_GET_SNK_CAP:
                default:

                    // Send "Not Support"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);

                    break;
            }

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
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
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
        case _PD_CMD_DATA_RESET_COMPLETE:
        case _PD_CMD_SRC_INFO:
        case _PD_CMD_EPR_SNK_CAP:
#endif
#endif
            ScalerTypeC1PdPrlErrHandle_EXINT0();

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
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
        case _PD_CMD_DATA_RESET:
        case _PD_CMD_GET_SRC_INFO:
        case _PD_CMD_ENTER_USB:
        case _PD_CMD_VENDOR_DEFINED_EXT:
#endif
#endif
        default:
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;
    }
}

//--------------------------------------------------
// Description  : Process Rcv. Msg. in Interrupt in SNK_READY During _AMS_NONE/_INTERRUPTIBLE
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntSnkRcvMsgNoAmsProc_EXINT0(void)
{
    // Receive Any Message When Not in AMS or in Interruptible AMS @ _PD_SNK_READY
    switch(GET_TYPE_C_1_PD_RCV_MSG())
    {
        case _PD_CMD_SRC_CAP:

            // 1. Store Src_Cap Info from Data Objects
            SET_TYPE_C_1_PD_PARTNER_DRP(g_pucTypeC1PdDataObject_EXINT[0] >> 5);
            SET_TYPE_C_1_PD_PARTNER_SUSPEND(g_pucTypeC1PdDataObject_EXINT[0] >> 4);
            SET_TYPE_C_1_PD_PARTNER_EXT_PWR(g_pucTypeC1PdDataObject_EXINT[0] >> 3);
            SET_TYPE_C_1_PD_PARTNER_USB_CAP(g_pucTypeC1PdDataObject_EXINT[0] >> 2);
            SET_TYPE_C_1_PD_PARTNER_DRD(g_pucTypeC1PdDataObject_EXINT[0] >> 1);
            SET_TYPE_C_1_PD_PARTNER_UNCHK(g_pucTypeC1PdDataObject_EXINT[0] >> 0);
            SET_TYPE_C_1_PD_PARTNER_EPR_CAP(g_pucTypeC1PdDataObject_EXINT[1] >> 7);

            // Get Number Of Capabilities
            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT(GET_TYPE_C_1_PD_RCV_NOD_CNT());

            // Evaluate and Set Request Data Objects
            for(BYTE ucLoopIndex = 0; ucLoopIndex < _TYPE_C_PDO_NUM_7; ucLoopIndex++)
            {
                if(ucLoopIndex < GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT())
                {
                    if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                    {
                        // Set APDO Type
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex, ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                    }
                    else
                    {
                        // Set PDO Type
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex, ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) >> 6));
                    }

                    if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex, (((((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & 0x01)) << 7) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 1] & 0xFE)) >> 1)) * 10));
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(ucLoopIndex, (((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2]) * 10));
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(ucLoopIndex, (((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 3] & 0x7F) * 5));
                    }
                    else
                    {
                        // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex, (((((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2] & 0xFC)) >> 2)) * 5));
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(ucLoopIndex, GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex));
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(ucLoopIndex, (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 3]));
                        SET_TYPE_C_1_PD_PARTNER_SRC_PEAK_CUR(ucLoopIndex, ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 1] & (_BIT5 | _BIT4)) >> 4));

                        // If Target Voltage Matches Partner's Voltage, Set the Macros of Capability Mismatch and Object Position.
                        if((GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_TARGET_VOL) && (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex) == (GET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL() * 10)))
                        {
                            SET_TYPE_C_1_PD_REQ_CAP_MIS(_FALSE);
                            SET_TYPE_C_1_PD_REQ_OBJ_POS((EnumTypeCPdoNumber)(ucLoopIndex + 1));
                        }
                    }
                }
                else
                {
                    // If ucLoopIndex >= GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT(), Clear the Related Macros to 0x00.
                    SET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex, _PD_NONE_SETTING_PDO);
                    SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex, 0x00);
                    SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(ucLoopIndex, 0x00);
                    SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(ucLoopIndex, 0x00);
                    SET_TYPE_C_1_PD_PARTNER_SRC_PEAK_CUR(ucLoopIndex, 0x00);
                }
            }

            // According to the corresponding Request Type, Set the Macros of Capability Mismatch and Object Position.
            if(GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_LOWEST_VOL)
            {
                SET_TYPE_C_1_PD_REQ_CAP_MIS(_FALSE);
                SET_TYPE_C_1_PD_REQ_OBJ_POS(_TYPE_C_PDO_NUM_1);
            }
            else if(GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_HIGHEST_VOL)
            {
                SET_TYPE_C_1_PD_REQ_CAP_MIS(_FALSE);

                // Select Highest Fix PDO
                for(BYTE ucLoopIndex = GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT(); ucLoopIndex > 0; ucLoopIndex--)
                {
                    if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex - 1) == _PD_FIX_SUPPLY_PDO)
                    {
                        SET_TYPE_C_1_PD_REQ_OBJ_POS((EnumTypeCPdoNumber)(ucLoopIndex));

                        break;
                    }
                }
            }
            else if((GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_TARGET_VOL) && (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) != (GET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL() * 10)))
            {
#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
                // [MM1AE-4187] Don't Set Capability Mismatch for Powered from Vbus 5.1V RDO
                if(GET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL() != 51)
                {
                    SET_TYPE_C_1_PD_REQ_CAP_MIS(_TRUE);
                }
#else
                SET_TYPE_C_1_PD_REQ_CAP_MIS(_TRUE);
#endif

                SET_TYPE_C_1_PD_REQ_OBJ_POS(_TYPE_C_PDO_NUM_1);
            }

            // If Request Type isn't Customized RDO, Need to be Set Operating and Max. Current.
            if(GET_TYPE_C_1_PD_REQ_TYPE() != _TYPE_C_REQ_CUSTOMIZED_RDO)
            {
                SET_TYPE_C_1_PD_REQ_INFO_1(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1));
                SET_TYPE_C_1_PD_REQ_INFO_2(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1));
            }

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);

            // Send Request (Success : Wait Resp / Fail : Hard Reset)
            SET_TYPE_C_1_PD_RCV_SRC_CAP();
            SET_TYPE_C_1_PD_FW_STATE(_PD_SNK_INT_SEND_REQUEST);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REQUEST, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_GET_SRC_CAP:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // if Able to Become Src, Reply "Src_Cap", Otherwise "Reject"
#if((_TYPE_C_1_PD_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
            if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                // Send "Source Capabilities"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_SRC_CAP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }
            else
#endif
            {
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "Reject"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_GET_SNK_CAP:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Sink Capabilities"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_SNK_CAP);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SNK_CAP, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_PR_SWAP:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

#if(_TYPE_C_1_PD_SNK_ACCEPT_SWAP_TO_SRC == _TRUE)
            if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _TRUE))
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_PRS);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
            }
            else
#endif
            {
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Send "Reject"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

        case _PD_CMD_DR_SWAP:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_VENDOR_ALT_MODE_NONE)
            if(GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE)
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
            if((GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE) && (GET_TYPE_C_1_PD_LENOVO_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
            if((GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE) && (GET_TYPE_C_1_PD_ACER_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
            if((GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE) && (GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _FALSE))
#elif(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
            if((GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE) && (GET_TYPE_C_1_PD_DELL_ALT_MODE_ENTER() == _FALSE))
#endif
            {
                if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
                {
#if(_TYPE_C_1_PD_DFP_SWAP_TO_UFP == _TRUE)
                    // Accept Swap from DFP -> UFP
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_DRS);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
#else
                    // Reject Swap from DFP -> UFP
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
#endif
                }
                else
                {
#if(_TYPE_C_1_PD_UFP_SWAP_TO_DFP == _TRUE)
                    // Accept Swap from UFP -> DFP
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_DRS);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
#else
                    // Reject Swap from UFP -> DFP
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
#endif
                }
            }
            else
            {
                // Receive DR_SWAP When in Alt Mode : Hard Reset
                ScalerTypeC1PdSendHardRst_EXINT0();
            }

            break;

        case _PD_CMD_VCONN_SWAP:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            if(GET_TYPE_C_1_CC_PORT_ROLE() != _TYPE_C_PORT_SNK_ONLY)
            {
                // Evaluate Vconn Swap : Vconn Source Must "Accept", Not Vconn Source Can "Accept/Reject/Wait"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_ACCEPT_VCS);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Sink Only : Send Reject to Vconn Swap
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_CMD_BIST:

            // BIST Mode Operate Only in vSafe5v
            if(GET_TYPE_C_1_PD_REQ_OBJ_POS() == 1)
            {
                SET_TYPE_C_1_PD_BIST_MODE((g_pucTypeC1PdDataObject_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

                if(GET_TYPE_C_1_PD_BIST_MODE() == (_BIT2 | _BIT0))
                {
                    // If Carrier Mode : Output 0101... for 30-60ms
                    // Turn On BIST UUT Carrier Mode
                    ScalerSetBit_EXINT(P6B_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
                    ScalerSetBit_EXINT(P6B_F1_PD_BIST_PATTERN, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

                    // Disable Rcv Msg INT
                    ScalerTypeC1PdRxIntControl_EXINT0(_DISABLE);

                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_BIST_MODE);

                    // Begin BIST Mode
                    ScalerSetBit_EXINT(P6B_F0_PD_BIST_CFG, ~_BIT2, _BIT2);

                    // If BIST Carrier Mode, Back to Ready State After 30-60ms
                    ScalerTimerWDActivateTimerEvent_EXINT0(45, _SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);
                }
                else if(GET_TYPE_C_1_PD_BIST_MODE() == _BIT3)
                {
                    // Lecroy [TEST.PD.PHY.ALL.07]
                    while(ScalerGetBit_EXINT(P6B_05_PD_PHY_IDLE_INT, _BIT2) == 0x00)
                    {
                        DELAY_XUS_EXINT(5);
                    }

                    // If Test Data Mode : Do Nothing, Turn Off Rcv. Msg INT and Wait For HardReset
                    // Turn On BIST UUT Test Data Mode
                    ScalerSetBit_EXINT(P6B_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

                    // [0x6B34] Setup Rx Valid Packet Type (SOP / Hard Reset)
                    ScalerSetByte_EXINT(P6B_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT0));

                    // Begin BIST Mode in Interrupt for CTS
                    ScalerSetBit_EXINT(P6B_F0_PD_BIST_CFG, ~_BIT2, _BIT2);

                    // Disable Rcv Msg INT
                    ScalerTypeC1PdRxIntControl_EXINT0(_DISABLE);

                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_BIST_MODE);
                }
            }

            break;

        case _PD_CMD_VDM:

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            if(GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE)
            {
                if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
                {   // DFP Rcv Any VDM Resp. or Attention Request When Alt Mode Ready
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
                    ScalerTypeC1PdIntDfpRcvVdmMsgProc_EXINT0();
#endif
                }
                else
                {   // Receive VDM Request, UFP Responds According to Rcv. VDM Msg.
                    ScalerTypeC1PdIntUfpRcvVdmMsgProc_EXINT0();
                }
            }
            else
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            {
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    // Send "Not Support"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        // PD 3.0 Control Message
        case _PD_CMD_GET_SRC_CAP_EXT:

            // [MM1AE-2561] Send Not Support for MacBook Interop Issue.
            // Send "Not Support"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_GET_SNK_CAP_EXT:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Sink Capability Extended"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_SNK_CAP_EXT);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_SNK_CAP_EXT, _PD_VDM_CMD_RESERVED);

            break;

        case _PD_CMD_GET_STATUS:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Send "Status"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_STATUS);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_STATUS, _PD_VDM_CMD_RESERVED);

            break;

        // PD 3.0 Data Message
        case _PD_CMD_ALERT:

            SET_TYPE_C_1_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_ALERT_EVENT);
            SET_TYPE_C_1_PD_PARTNER_TYPE_OF_ALERT((EnumTypeCTypeOfAlert)(g_pucTypeC1PdDataObject_EXINT[0]));
            SET_TYPE_C_1_PD_PARTNER_BAT_STATUS((EnumTypeCBatteryStatus)(g_pucTypeC1PdDataObject_EXINT[1]));
            SET_TYPE_C_1_PD_PARTNER_EXT_ALERT_EVENT((EnumTypeCExtAlertEventType)(g_pucTypeC1PdDataObject_EXINT[3] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            // Check Battery Status
            if((g_pucTypeC1PdDataObject_EXINT[0] & (_BIT1)) == _BIT1)
            {
                // Send "Get Battery Status Message" if Needed
            }

            // Check Status
            if((g_pucTypeC1PdDataObject_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2)) != 0x00)
            {
                // Send "Get Status Message"
                // [MQP] : PROT-SNK3-STATUS(Rev3.0), Shall Initiate GET_STATUS Msg. When SnkTXOK
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
            }

            break;

        // PD 3.0 Extended Message
        case _PD_CMD_GET_MFC_INFO:
#if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
            // PD 3.0 Standard Spec(USB_PD_R3_0 V1.2 20180621 - with ECRs 2018-09-24): Ignore
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
            // Send "Not Support"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
#endif // End of #if(_TYPE_C_EMB_CTS_FLOW == _ON)
#else
            // Byte 0-1 are Ext. Msg Header
            // Manufacturer Info Target "g_pucTypeC1PdDataObject_EXINT[2]" : 0 = Port / 1 = Battery
            if(g_pucTypeC1PdDataObject_EXINT[2] == 0x00)
            {
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                // Send "Manufacturer Info"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_MFC_INFO);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_MFC_INFO, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Not Support"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
#endif // End of #if(_MANUFACTURER_INFO_SUPPORT == _FALSE)
            break;

        case _PD_CMD_CHUNK_TEST:

            // Check If This Ext Msg is Chunked : Ext Message Header [15]
            if((GET_TYPE_C_1_PD_CHUNKED_MESSAGE() == _TRUE) && (GET_TYPE_C_1_PD_CHUNK_REQUEST() == _FALSE))
            {
                // If Received Chunk Response Data < Total Message Data Size, Sent Chunk Request
                if(((GET_TYPE_C_1_PD_CHUNK_NUMBER() + 1) * 26) < GET_TYPE_C_1_PD_EXT_MSG_DATA_SIZE())
                {
                    // Set Chunk Message As an Chunk Request
                    SET_TYPE_C_1_PD_CHUNK_REQUEST(_TRUE);

                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                    // Send "Chunk Test" REQUEST
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_CHK_TEST_REQ);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_CHUNK_TEST, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }

            break;

        // PD 3.0 Control Message
        case _PD_CMD_FR_SWAP:

            // CTS : For UUT AS SNK, But Not Support FR_Swap
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;

        // PD 3.0 Control Message
        case _PD_CMD_GET_REVISION:

            // Send "Revision Message"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REVISION);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REVISION, _PD_VDM_CMD_RESERVED);

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        case _PD_CMD_EXTENDED_CONTROL:

            // Set AMS to Non-Interruptible
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            switch(g_pucTypeC1PdDataObject_EXINT[2])
            {
                case _PD_EXT_CTRL_TYPE_EPR_GET_SRC_CAP:

                    // if Able to Become Src & Support EPR Src, Reply "EPR Source Cap", Otherwise "Not Support"
#if((_TYPE_C_1_PD_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
                    if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_PD_EPR_SRC_CAPABLE() == _TRUE))
                    {
                        // Send EPR Source Cap
                        CLR_TYPE_C_1_PD_TX_CHUNK_NUMBER();
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_SRC_CAP);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_SRC_CAP, _PD_VDM_CMD_RESERVED);
                    }
                    else
#endif
                    {
                        // Send "Not Support"
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                    }

                    break;

                case _PD_EXT_CTRL_TYPE_EPR_KEEP_ALIVE:
                case _PD_EXT_CTRL_TYPE_EPR_KEEP_ALIVE_ACK:

                    ScalerTypeC1PdPrlErrHandle_EXINT0();

                    break;

                case _PD_EXT_CTRL_TYPE_EPR_GET_SNK_CAP:
                default:

                    // Send "Not Support"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);

                    break;
            }

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
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
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
        case _PD_CMD_DATA_RESET_COMPLETE:
        case _PD_CMD_SRC_INFO:
        case _PD_CMD_EPR_SNK_CAP:
#endif
#endif
            ScalerTypeC1PdPrlErrHandle_EXINT0();

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
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
        case _PD_CMD_DATA_RESET:
        case _PD_CMD_GET_SRC_INFO:
        case _PD_CMD_ENTER_USB:
        case _PD_CMD_VENDOR_DEFINED_EXT:
#endif
#endif
        default:
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Send "Reject"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_REJECT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_REJECT, _PD_VDM_CMD_RESERVED);
            }

            break;
    }
}

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DFP Rcv. SOP VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntDfpRcvVdmMsgProc_EXINT0(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1);

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    EnumInputPort enumInputPort = ScalerTypeCPcbPortConvertToDx_EXINT0(enumTypeCPcbPort);
#endif

    // Rcv. Any VDM Resp (Attention Message Not Included)
    if(GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_INT_WAIT_VDM_RESP)
    {
        CLR_TYPE_C_1_PD_PARTNER_VDM_NO_RESP_CNT();

        // Cancel TimerEvent (Sender Response Timer = 24-30ms)
        ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT);

        switch(GET_TYPE_C_1_PD_DP_ALT_STATE())
        {
            case _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP:

                if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'00(2.0), b'01 (2.1)
                    if((GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1) && ((g_pucTypeC1PdDataObject_EXINT[2] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) <= (_BIT5)))
                    {
                        // if((Current SVDM >= 2.1) & (Rcv SVDM <= 2.0)), Downgrade to SVDM 2.0 Earlier & DPAM 2.0 Earlier
                        SET_TYPE_C_1_PD_PARTNER_SVDM_VERSION(_PD_SVDM_VER_2_0_EARLIER);
                        SET_TYPE_C_1_PD_PARTNER_DPAM_VERSION(_PD_DPAM_VER_2_0_EARLIER);
                    }

                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_SVID);
                }
                else
                {
                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP:

                if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_SVID_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID))
                {
                    if(ScalerTypeC1PdSearchSvid_EXINT0() == _TRUE)
                    {   // If Find DP_SID = 0xFF01, Send Discover Mode
                        SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_MODE);
                    }
                    else
                    {
                        // If Search Fnish = FALSE, Send Discover SVID Again to Get More SVID
                        if(GET_TYPE_C_1_PD_DP_SVID_SEARCH_FINISH() == _FALSE)
                        {
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_SVID);
                        }
                        else
                        {   // No More SVID and Cannot Find DP_SID, Stop Alt. Mode Flow
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                        }
                    }
                }
                else
                {
                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DISCOVER_MODE_RESP:

                if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_MODE_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                {
                    // Search All Modes to Get DP Port Capability (DP_Tx) and Pin Assignment ( C / D / E )
                    ScalerTypeC1PdSearchMode_EXINT0();

                    if(GET_TYPE_C_1_PD_DP_OBJ_POS() == 0)
                    {   // Cannot Find Any Acceptable Configuration, Stop Alt. Mode Flow
                        SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                    }
                    else
                    {
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
                        // Start to Discover Cable According to DPAM 2.1
                        if(GET_TYPE_C_1_PD_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)
                        {
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P);
                        }
                        else if(GET_TYPE_C_1_PD_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_NON_PD_CAPABLE)
                        {
                            // If Cable is Non-PD Capable, Set Passive Cable & HBR3 According to DPAM2.1
                            SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_PASSIVE);
                            SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_HBR3);

                            // Stop Enter DP Alt Mode Flow Just for Cable
                            CLR_TYPE_C_1_PD_CBL_ENTER_DP_MODE_SUPPORT();
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                        }
                        else
                        {
                            // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable(When Ack Vdo Received For Discover Id(SOP'/SOP''))
                            SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableId_EXINT0());
                        }
#else
                        // Use the Object Position Selected in Function to Initiate Enter Mode
                        SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
#endif  // End of #if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
                    }
                }
                else
                {
                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP:

                if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_ENTER_MODE_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID) && (GET_TYPE_C_1_PD_VDM_OBJ_POS() == GET_TYPE_C_1_PD_DP_OBJ_POS()))
                {
                    // Set DP Enter Mode Flag
                    SET_TYPE_C_1_PD_DP_ALT_MODE_ENTER();

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                    // Push _PD_HPD_LOW into HPD_Queue
                    ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_LOW, 0);
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                    // Clear HPD Queue
                    ScalerTypeC1PdClrHpd_EXINT0();
#endif

                    // Transit to "DP_STATUS" to Send DP_Status REQ
                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_STATUS);
                }
                else
                {
                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP:

                if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_EXIT_MODE_ACK) || (GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_EXIT_MODE_NAK))
                {
                    CLR_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ();

                    // Clear Alt. Mode Status
                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_NONE);
                    CLR_TYPE_C_1_PD_DP_ALT_MODE_ENTER();
                    SET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG(_PD_USB_CONFIG);

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                    ScalerDpAuxRxHpdTogglePhyResetProc(enumInputPort, _LOW);
                    SET_TYPE_C_1_PD_HPD_STATUS(_LOW);
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                    ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_LOW, 0);
#endif
                }
                else
                {
                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DP_STATUS_RESP:

                if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_50) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID) && (GET_TYPE_C_1_PD_VDM_OBJ_POS() == GET_TYPE_C_1_PD_DP_OBJ_POS()))
                {
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                    // Pop Out One HPD From Queue
                    ScalerTypeC1PdPopHpd_EXINT0();
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                    // DP_TX Update DP_RX HPD Status
                    ScalerTypeC1PdPushHpd_EXINT0(ScalerTypeC1PdDecodePartnerHpdStatus_EXINT0(), 0);
#endif
                    if(ScalerTypeC1PdCheckDpStatus_EXINT0() == _PD_CONFIG_REQUIRED)
                    {
                        if(GET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG() == _PD_DP_CONFIG)
                        {
                            // Check Avaliable Pin Assignment
                            if(ScalerTypeC1PdDfpJudgePinAssignment_EXINT0() == _TRUE)
                            {
                                // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                                if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                                }
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }
                        }
                        else
                        {
                            SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);

                            // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                            if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                        }
                    }
                    else
                    {
                        if(GET_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
                        {
                            // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Exit Mode First
                            if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE_SOP_P);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                        }
                        else
                        {
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ATTENTION);
                        }
                    }

                    // Update Port Partner DP Status
                    // Warning : PartnerDpStatus Shall Update After CheckDpStatus, Otherwise, MULTI_FUNCTION_CHANGE Macro Would Judge Incorrectly !!!
                    ScalerTypeC1PdUpdatePortPartnerDpStatus_EXINT0(_PD_VDM_DP_CMD_DP_STATUS_ACK);
                }
                else
                {
                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ATTENTION);
                }

                break;

            case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP:

                if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_51) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID) && (GET_TYPE_C_1_PD_VDM_OBJ_POS() == GET_TYPE_C_1_PD_DP_OBJ_POS()))
                {
                    // Swith DP Lane Mapping
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                    ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(enumInputPort, GET_TYPE_C_1_PD_PIN_ASSIGNMENT(), GET_TYPE_C_1_CC_ORIENTATION());
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                    ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToPx_EXINT0(enumTypeCPcbPort), GET_TYPE_C_1_PD_PIN_ASSIGNMENT(), GET_TYPE_C_1_CC_ORIENTATION());
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

                    SET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG(GET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG());

                    if(GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG)
                    {
                        SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_READY);

                        // Multi-Function Bit Change Process(Pin Assignment C <=> Pin Assignment D) Done.
                        if(GET_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE() == _TRUE)
                        {
                            SET_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE_DONE();
                        }
                    }
                    else
                    {
                        if(GET_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
                        {
                            // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Exit Mode First
                            if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE_SOP_P);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                        }
                        else
                        {
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ATTENTION);
                        }
                    }
                }
                else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_91) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                {
                    // Rcv DP Config Nak
                    if(GET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG() == _PD_USB_CONFIG)
                    {
                        SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ATTENTION);
                    }
                    else
                    {
                        SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);
                        SET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG(_PD_USB_CONFIG);

                        // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                        if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                        {
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                        }
                        else
                        {
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                        }
                    }
                }
                else
                {
                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                }

                // Clear Multi-Function Change When Rcv DP Config Ack / Nak
                if(GET_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE() == _TRUE)
                {
                    CLR_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE();
                }

                break;

            case _PD_ALT_MODE_READY:

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_50) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID) && (GET_TYPE_C_1_PD_VDM_OBJ_POS() == GET_TYPE_C_1_PD_DP_OBJ_POS()))
                {
                    if(GET_TYPE_C_1_PD_FORCE_HPD_IRQ() == _TRUE)
                    {
                        CLR_TYPE_C_1_PD_FORCE_HPD_IRQ();
                    }
                    else
                    {
                        // Set WAIT FLAG to Prevent from Sending Attention in HPD Space Time
                        if(GET_TYPE_C_1_PD_HPD_SPACE_TIME(GET_TYPE_C_1_PD_HPD_RPTR()) != 0)
                        {
                            SET_TYPE_C_1_PD_ATTENTION_WAIT();
                            ScalerTypeC1PdActiveTimerEvent_EXINT0(GET_TYPE_C_1_PD_HPD_SPACE_TIME(GET_TYPE_C_1_PD_HPD_RPTR()), _SCALER_TIMER_EVENT_PD_1_CLR_ATTENTION_WAIT);
                        }

                        // Pop Out One HPD From Queue
                        ScalerTypeC1PdPopHpd_EXINT0();
                    }

                    if(ScalerTypeC1PdCheckDpStatus_EXINT0() == _PD_CONFIG_REQUIRED)
                    {
                        if(GET_TYPE_C_1_PD_HPD_STATUS() == _LOW)
                        {
                            SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);

                            // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                            if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                        }
                        else
                        {
                            // Push _PD_HPD_LOW into HPD_Queue
                            ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_LOW, 0);

                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_STATUS);
                        }
                    }

                    // Update Port Partner DP Status
                    // Warning : PartnerDpStatus Shall Update After CheckDpStatus, Otherwise, MULTI_FUNCTION_CHANGE Macro Would Judge Incorrectly !!!
                    ScalerTypeC1PdUpdatePortPartnerDpStatus_EXINT0(_PD_VDM_DP_CMD_DP_STATUS_ACK);
                }
                else
                {
                    if(GET_TYPE_C_1_PD_FORCE_HPD_IRQ() == _TRUE)
                    {
                        CLR_TYPE_C_1_PD_FORCE_HPD_IRQ();

                        // Push HPD_IRQ into HPD Queue When Received Unexpected Msg during Force Sending HPD IRQ Process, then PD will Re-Send HPD_IRQ in Main loop
                        ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_IRQ, 0);
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

        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

        // Back to Ready State
        ScalerTypeC1PdBackToReadyState_EXINT0();
    }
    else
    {
        switch(GET_TYPE_C_1_PD_RCV_VDM_CMD())
        {
            case _PD_VDM_CMD_DISCOVER_ID_REQ:

                // PD Merged Test [TEST.PD.VDM.SRC.1], and [TEST.PD.VDM.SRC.2]
                if((GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0))
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover ID ACK"
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_ACK);
                }
                else
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover ID NAK" or "Ignore"
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_NAK);
                }

                break;

            case _PD_VDM_CMD_DISCOVER_SVID_REQ:

                // PD Merged Test [TEST.PD.VDM.SRC.1], and [TEST.PD.VDM.SRC.2]
                if((GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0))
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover SVID ACK"
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_ACK);
                }
                else
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover SVID NAK"  or "Ignore"
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_NAK);
                }

                break;

            case _PD_VDM_CMD_DISCOVER_MODE_REQ:

                // PD Merged Test [TEST.PD.VDM.SRC.1], and [TEST.PD.VDM.SRC.2]
                if((GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0))
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover Mode ACK" to Display Port
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);
                }
                else
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Discover Mode NAK" to Uncongnized SID
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_NAK);
                }

                break;

            case _PD_VDM_CMD_ATTENTION_REQ:

                // Check if SVID is correct, and Valid State to Receive Attention (DO Not Check Object Position)
                if((GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID) && ((GET_TYPE_C_1_PD_DP_ALT_STATE() == _PD_ALT_MODE_INT_WAIT_ATTENTION) || (GET_TYPE_C_1_PD_DP_ALT_STATE() == _PD_ALT_MODE_READY)))
                {
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                    // DP_TX Update DP_RX HPD Status
                    ScalerTypeC1PdPushHpd_EXINT0(ScalerTypeC1PdDecodePartnerHpdStatus_EXINT0(), 0);
#endif
                    if(ScalerTypeC1PdCheckDpStatus_EXINT0() == _PD_CONFIG_REQUIRED)
                    {
                        if(GET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG() == _PD_DP_CONFIG)
                        {
                            // Check Avaliable Pin Assignment
                            if(ScalerTypeC1PdDfpJudgePinAssignment_EXINT0() == _TRUE)
                            {
                                // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                                if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                                }
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }
                        }
                        else
                        {
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                            if(GET_TYPE_C_1_PD_HPD_STATUS() == _LOW)
                            {
                                SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);

                                // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                                if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                                }
                            }
                            else
                            {
                                // Push _PD_HPD_LOW into HPD_Queue
                                ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_LOW, 0);

                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_STATUS);
                            }

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                            ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_LOW, 0);

                            SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);

                            // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' DP Config First
                            if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG_SOP_P);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                            }
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                        }
                    }
                    else
                    {
                        if(GET_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
                        {
                            // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Exit Mode First
                            if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE_SOP_P);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                        }
                    }

                    // Update Port Partner DP Status
                    // Warning : PartnerDpStatus Shall Update After CheckDpStatus, Otherwise, MULTI_FUNCTION_CHANGE Macro Would Judge Incorrectly !!!
                    ScalerTypeC1PdUpdatePortPartnerDpStatus_EXINT0(_PD_VDM_DP_CMD_ATTENTION_REQ);
                }

                break;

            default:

                break;
        }
    }
}
#endif  // End of #if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : UFP Rcv. SOP VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntUfpRcvVdmMsgProc_EXINT0(void)
{
    // Check if BMC Channel, Rx PTCL State, and BUS are Idle
    if((ScalerGetBit_EXINT(P6B_05_PD_PHY_IDLE_INT, _BIT2) == _BIT2) && (ScalerGetByte_EXINT(P6B_21_RX_STATE_MACHINE_L) == _BIT0) && (GET_TYPE_C_1_PD_BUS_IDLE() == _TRUE))
    {
        // UFP Only Response to VDM Request, Ignore All Illegal ACK/NAK/BUSY
        if((GET_TYPE_C_1_PD_RCV_VDM_TYPE() == _PD_STRUCTURED_VDM) && (GET_TYPE_C_1_PD_RCV_VDM_CMD_TYPE() == _PD_VDM_CMD_TYPE_REQ))
        {
            if(GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID)
            {
                switch((EnumTypeCVdmCmd)GET_TYPE_C_1_PD_RCV_VDM_CMD())
                {
                    case _PD_VDM_CMD_DISCOVER_ID_REQ:

                        // FW Solution : Samsung S8 Plug-in then Start, Fail to Light Up
#if((_TYPE_C_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) && (_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON))
                        // If Rcv Discover ID, Cancel S8 HRST, Since Alt Mode Flow Start
                        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_S8_HRST);
                        if((GET_TYPE_C_1_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_1_S8_HRST) && (GET_TYPE_C_1_PD_TIMER_EVENT_VALID() == _TRUE))
                        {
                            CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();
                        }

                        // Clear Interop to Enable S8 FW Solution, When Alt Mode Flow Has Been Start
                        CLR_TYPE_C_1_PD_INTEROP_S8();
#endif

                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'00(2.0), b'01 (2.1)
                        if((GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1) && ((g_pucTypeC1PdDataObject_EXINT[2] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) <= (_BIT5)))
                        {
                            // if((Current SVDM >= 2.1) & (Rcv SVDM <= 2.0)), Downgrade to SVDM 2.0 Earlier & DPAM 2.0 Earlier
                            SET_TYPE_C_1_PD_PARTNER_SVDM_VERSION(_PD_SVDM_VER_2_0_EARLIER);
                            SET_TYPE_C_1_PD_PARTNER_DPAM_VERSION(_PD_DPAM_VER_2_0_EARLIER);
                        }

                        if(GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE)
                        {
                            // If Dp Alt Mode has not entered, Set Partner Initial Alt Mode Macro
                            SET_TYPE_C_1_PD_PARTNER_INIT_ALT_MODE();
                        }

                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                        // Send "Discover ID ACK"
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_ACK);

                        break;

                    case _PD_VDM_CMD_DISCOVER_SVID_REQ:

                        if(GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE)
                        {
                            // If Dp Alt Mode has not entered, Set Partner Initial Alt Mode Macro
                            SET_TYPE_C_1_PD_PARTNER_INIT_ALT_MODE();
                        }

                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                        if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SNK) && (GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _TRUE) && (GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_USB_CONFIG))
                        {
                            // FW Solution For Lenovol T480 : Fail To Light Up When Received Twice SVID(Second Svid Received Between Enter Mode and Dp Configure)
                            // Time Out: Do Error Recovery, Start From Unattach.SRC. If Go to DP Configure Successfully in 1s, Cancel WD Timer Event.
                            ScalerTypeC1PdActiveTimerEvent_EXINT0(_T480_ERROR_RECOVERY_TIMER, _SCALER_TIMER_EVENT_PD_1_T480_ERROR_RECOVERY);
                        }

                        // Send "Discover SVID ACK"
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_ACK);

                        break;

                    default:

                        // If Attention Command request is an Unrecognized Message it Shall be Ignored
                        // Otherwise, Send NAK Command to Uncongnized Message
                        if(!((EnumTypeCVdmCmd)GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_ATTENTION_REQ))
                        {
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                            // Send NAK Command to Uncongnized SVID
                            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, GET_TYPE_C_1_PD_RCV_VDM_CMD() | _BIT7);
                        }

                        break;
                }
            }
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
            else if(GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID)
            {   // Receive DP Alt Mode VDM Request, UFP Responds According to Rcv. VDM Msg.
                ScalerTypeC1PdIntUfpRcvDpVdmMsgProc_EXINT0();
            }
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
            else if(GET_TYPE_C_1_PD_VDM_SVID() == _LENOVO_VID)
            {   // Receive Lenovo Alt Mode VDM Request, UFP Responds According to Rcv. VDM Msg.
                ScalerTypeC1PdIntUfpRcvLenovoVdmMsgProc_EXINT0();
            }
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
            else if(GET_TYPE_C_1_PD_VDM_SVID() == _ACER_VID)
            {
                ScalerTypeC1PdIntUfpRcvAcerVdmMsgProc_EXINT0();
            }
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
            else if(GET_TYPE_C_1_PD_VDM_SVID() == _HP_VID)
            {
                if(ScalerTypeC1PdCheckHpVdmValid_EXINT0() == _TRUE)
                {
                    ScalerTypeC1PdIntUfpRcvHpVdmMsgProc_EXINT0();
                }
                // If AM Address Don't Match, Bypass Message to Downstream
                // Need to Check the 1st Bit of AM Address (If No Match -> Do Nothing)
            }
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
            else if(GET_TYPE_C_1_PD_VDM_SVID() == _DELL_VID)
            {
                ScalerTypeC1PdIntUfpRcvDellVdmMsgProc_EXINT0();
            }
#endif
            else
            {
                // If Attention Command request is an Unrecognized Message it Shall be Ignored
                // Otherwise, Send NAK Command to Uncongnized SVID
                if(!((EnumTypeCVdmCmd)GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_ATTENTION_REQ))
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send NAK Command to Uncongnized SVID
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, GET_TYPE_C_1_PD_RCV_VDM_CMD() | _BIT7);
                }
            }
        }
        else if(GET_TYPE_C_1_PD_RCV_VDM_TYPE() == _PD_UNSTRUCTURED_VDM)
        {
            // PD Merged Test [TEST.PD.VDM.SNK.7] :
            // For Rcv. Unstructured VDM : PD2.0 Should Ignore, PD3.0 Should Resp. w/ Not Support
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                // Send "Not Support"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
            }
        }
    }
    else
    {
        CLR_TYPE_C_1_PD_FIFO_CLR();
    }
}

#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : UFP Rcv. SOP Dp VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntUfpRcvDpVdmMsgProc_EXINT0(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1);

    switch((EnumTypeCVdmDpCmd)GET_TYPE_C_1_PD_RCV_VDM_CMD())
    {
        case _PD_VDM_DP_CMD_DISCOVER_MODE_REQ:

            if(GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE)
            {
                // If Dp Alt Mode has not entered, Set Partner Initial Alt Mode Macro
                SET_TYPE_C_1_PD_PARTNER_INIT_ALT_MODE();
            }

            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

            // Send "Discover Mode ACK" to Display Port
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);

            break;

        case _PD_VDM_DP_CMD_ENTER_MODE_REQ:

            if(GET_TYPE_C_1_PD_VDM_OBJ_POS() == 1)
            {
                // If Source Choose to Enter DP Alt Mode. Set Object Position to 1
                SET_TYPE_C_1_PD_DP_OBJ_POS(GET_TYPE_C_1_PD_VDM_OBJ_POS());

                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Enter Mode ACK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_ACK);
            }
            else
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Enter Mode NAK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_NAK);
            }

            break;

        case _PD_VDM_DP_CMD_EXIT_MODE_REQ:

            // If Obj Pos = DP_Alt_Mode or Exit All Modes & Already in Alt_Mode
            if(((GET_TYPE_C_1_PD_VDM_OBJ_POS() == GET_TYPE_C_1_PD_DP_OBJ_POS()) || (GET_TYPE_C_1_PD_VDM_OBJ_POS() == 7)) && (GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _TRUE))
            {
                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode ACK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_ACK);
            }
            else
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode NAK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_NAK);
            }

            break;

        case _PD_VDM_DP_CMD_DP_STATUS_REQ:

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
            // If Obj Pos = DP_Alt_Mode & Already in Alt_Mode
            // Lecroy [TD.DP.10.2.05] and DP Alt Mode Standard 3.9.2.1 : When DP Alt Mode is not enabled, PD shall not transmit any DisplayPort Status Update Command.
            if((GET_TYPE_C_1_PD_VDM_OBJ_POS() == GET_TYPE_C_1_PD_DP_OBJ_POS()) && (GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _TRUE))
#endif
            {
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                // DP_TX Update DP_RX HPD Status
                ScalerTypeC1PdPushHpd_EXINT0(ScalerTypeC1PdDecodePartnerHpdStatus_EXINT0(), 0);
#endif
                // Update Port Partner DP Status
                ScalerTypeC1PdUpdatePortPartnerDpStatus_EXINT0(_PD_VDM_DP_CMD_DP_STATUS_REQ);

                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_SEND_DP_STATUS_ACK);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "DP_Status ACK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_50);
            }

            break;

        case _PD_VDM_DP_CMD_DP_CONFIG_REQ:

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
            // If Obj Pos = DP_Alt_Mode & Already in Alt_Mode
            if((GET_TYPE_C_1_PD_VDM_OBJ_POS() == GET_TYPE_C_1_PD_DP_OBJ_POS()) && (GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _TRUE))
#endif
            {
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
                // Save Related DP Capabilities Info(From Dp Configure REQ) of Cable To Fill Into DPCD(DPAM v2.1)
                ScalerTypeC1PdUfpSaveCableInfoForDpcd_EXINT0();
#endif
                // REQ as DP_RX & Pin Assignment C / D / E || Config USB & Pin Assignment NONE
                if(ScalerTypeC1PdCheckDpConfig_EXINT0() == _TRUE)
                {
                    // Swith DP Lane Mapping
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                    ScalerDpPhyRxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToDx_EXINT0(enumTypeCPcbPort), GET_TYPE_C_1_PD_PIN_ASSIGNMENT(), GET_TYPE_C_1_CC_ORIENTATION());
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                    ScalerDpPhyTxSetAltModeLaneMapping_EXINT0(ScalerTypeCPcbPortConvertToPx_EXINT0(enumTypeCPcbPort), GET_TYPE_C_1_PD_PIN_ASSIGNMENT(), GET_TYPE_C_1_CC_ORIENTATION());
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_SEND_DP_CONFIG_ACK);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "DP_Configure ACK"
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_51);
                }
                else
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "DP_Configure NAK"
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_91);
                }
            }

            break;

        default:
            // Not Going to Happens, Receive Un-Recognized VDM Request, Reply NAK or Ignore?
            break;
    }
}
#endif  // End of #if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : UFP Rcv. SOP Lenovo VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntUfpRcvLenovoVdmMsgProc_EXINT0(void)
{
    switch((EnumTypeCVdmLenovoCmd)GET_TYPE_C_1_PD_RCV_VDM_CMD())
    {
        case _PD_VDM_LENOVO_CMD_DISCOVER_MODE_REQ:

            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

            // Send "Discover Mode ACK"
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);

            break;

        case _PD_VDM_LENOVO_CMD_ENTER_MODE_REQ:

            // if Obj Pos = Lenovo_Alt_Mode
            if(GET_TYPE_C_1_PD_VDM_OBJ_POS() == 1)
            {
                // If Source Choose to Enter Lenovo Alt Mode. Set Object Position to 1
                SET_TYPE_C_1_PD_LENOVO_OBJ_POS(GET_TYPE_C_1_PD_VDM_OBJ_POS());

                SET_TYPE_C_1_PD_LENOVO_ALT_STATE(_PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Enter Mode ACK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_ACK);
            }
            else
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Enter Mode NAK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_NAK);
            }

            break;

        case _PD_VDM_LENOVO_CMD_EXIT_MODE_REQ:

            // If Obj Pos = Lenovo_Alt_Mode or Exit All Modes & Already in Alt_Mode
            if(((GET_TYPE_C_1_PD_VDM_OBJ_POS() == GET_TYPE_C_1_PD_LENOVO_OBJ_POS()) || (GET_TYPE_C_1_PD_VDM_OBJ_POS() == 7)) && (GET_TYPE_C_1_PD_LENOVO_ALT_MODE_ENTER() == _TRUE))
            {
                SET_TYPE_C_1_PD_LENOVO_ALT_STATE(_PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode ACK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_ACK);
            }
            else
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode NAK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_NAK);
            }

            break;

        case _PD_VDM_LENOVO_CMD_GET_STATUS_REQ:

            // If Already in Alt_Mode
            if(GET_TYPE_C_1_PD_LENOVO_ALT_MODE_ENTER() == _TRUE)
            {
                CLR_TYPE_C_1_PD_LENOVO_ATTN_SENT_FLAG();
                CLR_TYPE_C_1_PD_LENOVO_ATTN_CNT();

                // Cancel TimerEvent (Lenovo Attention Timer = 300ms)
                ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_LENOVO_RESP_TIMEOUT);
                if((GET_TYPE_C_1_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_1_LENOVO_RESP_TIMEOUT) && (GET_TYPE_C_1_PD_TIMER_EVENT_VALID() == _TRUE))
                {
                    CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();
                }

                // Check Lenovo Get_Status
                ScalerTypeC1PdCheckLenovoStatus_EXINT0();

                SET_TYPE_C_1_PD_LENOVO_ALT_STATE(_PD_ALT_MODE_INT_SEND_LENOVO_GET_STATUS_ACK);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Lenovo Get_Status ACK (0x50)"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_LENOVO_CMD_GET_STATUS_ACK);
            }

            break;

        case _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_REQ:

            // Check Lenovo Device_ID
            ScalerTypeC1PdCheckLenovoDeviceId_EXINT0();

            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

            // Send "Lenovo Device ID ACK (0x51)"
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_ACK);

            break;

        default:
            // Not Going to Happens, Receive Un-Recognized VDM Request, Reply NAK or Ignore?
            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : UFP Rcv. SOP Acer VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntUfpRcvAcerVdmMsgProc_EXINT0(void)
{
    switch((EnumTypeCVdmAcerCmd)GET_TYPE_C_1_PD_RCV_VDM_CMD())
    {
        case _PD_VDM_ACER_CMD_DISCOVER_MODE_REQ:

            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

            // Send "Discover Mode ACK"
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);

            break;

        case _PD_VDM_ACER_CMD_ENTER_MODE_REQ:

            // if Obj Pos = Acer_Alt_Mode
            if(GET_TYPE_C_1_PD_VDM_OBJ_POS() == 1)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                SET_TYPE_C_1_PD_ACER_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK);

                // Send "Enter Mode ACK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_ACK);
            }
            else
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Enter Mode NAK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_NAK);
            }

            break;

        case _PD_VDM_ACER_CMD_EXIT_MODE_REQ:

            // If Obj Pos = Acer_Alt_Mode or Exit All Modes & Already in Alt_Mode
            if(((GET_TYPE_C_1_PD_VDM_OBJ_POS() == 1) || (GET_TYPE_C_1_PD_VDM_OBJ_POS() == 7)) && (GET_TYPE_C_1_PD_ACER_ALT_MODE_ENTER() == _TRUE))
            {
                SET_TYPE_C_1_PD_ACER_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode ACK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_ACK);
            }
            else
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode NAK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_NAK);
            }

            break;

        case _PD_VDM_ACER_CMD_GET_STATUS_REQ:

            if(GET_TYPE_C_1_PD_ACER_ALT_MODE_ENTER() == _TRUE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Get Acer System Status
                ScalerTypeC1PdGetAcerSysStatus_EXINT0();

                // Send "Acer Get_Status ACK (0x56)"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_ACER_CMD_GET_STATUS_ACK);
            }

            break;

        default:
            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : UFP Rcv. SOP Hp VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntUfpRcvHpVdmMsgProc_EXINT0(void)
{
    switch((EnumTypeCVdmHpCmd)GET_TYPE_C_1_PD_RCV_VDM_CMD())
    {
        case _PD_VDM_HP_CMD_DISCOVER_MODE_REQ:

            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

            // Send "Discover Mode ACK"
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);

            break;

        case _PD_VDM_HP_CMD_ENTER_MODE_REQ:

            // if Obj Pos = Hp_Alt_Mode
            if(GET_TYPE_C_1_PD_VDM_OBJ_POS() == 1)
            {
                // If Source Choose to Enter Hp Alt Mode. Set Object Position to 1
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK);

                // Send "Enter Mode ACK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_ACK);
            }
            else
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Enter Mode NAK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_NAK);
            }

            break;

        case _PD_VDM_HP_CMD_EXIT_MODE_REQ:

            // If Obj Pos = Hp_Alt_Mode or Exit All Modes & Already in Alt_Mode
            if(((GET_TYPE_C_1_PD_VDM_OBJ_POS() == 1) || (GET_TYPE_C_1_PD_VDM_OBJ_POS() == 7)) && (GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _TRUE))
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK);

                // Send "Exit Mode ACK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_ACK);
            }
            else
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode NAK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_NAK);
            }

            break;

        case _PD_VDM_HP_CMD_SET_CONFIG_REQ:

            if(GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _TRUE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_HP_SET_CONFIG_ACK);

                // Get Hp I2C and AM Address
                ScalerTypeC1PdSetHpOwnAddr_EXINT0();

                // Send "Hp Set_config ACK (0x50)"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_HP_CMD_SET_CONFIG_ACK);
            }

            break;

        case _PD_VDM_HP_CMD_GET_CONFIG_REQ:

            if(GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _TRUE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Hp Get_config ACK (0x51)"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_HP_CMD_GET_CONFIG_ACK);
            }

            break;

        case _PD_VDM_HP_CMD_SET_VWIRE_REQ:

            if(GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _TRUE)
            {
                // Get Hp System Status
                ScalerTypeC1PdGetHpSysStatus_EXINT0(_TYPE_C_HP_SYS_EVENT_SET_VWIRE_REQ);

                if(GET_TYPE_C_1_PD_HP_VWIRE_OP() != _PD_HP_VWIRE_OP_SAMPLE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "Hp Set_vwire ACK (0x52)"
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_HP_CMD_SET_VWIRE_ACK);
                }
            }

            break;

        case _PD_VDM_HP_CMD_GET_VWIRE_REQ:

            if(GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _TRUE)
            {
                // Get Hp System Status
                ScalerTypeC1PdGetHpSysStatus_EXINT0(_TYPE_C_HP_SYS_EVENT_GET_VWIRE_REQ);

                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Hp Get_vwire ACK (0x53)"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_HP_CMD_GET_VWIRE_ACK);
            }

            break;

        case _PD_VDM_HP_CMD_SET_DATA_REQ:

            if(GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _TRUE)
            {
                // Get Hp System Status
                ScalerTypeC1PdGetHpSysStatus_EXINT0(_TYPE_C_HP_SYS_EVENT_SET_DATA_REQ);

                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Hp Set_data ACK (0x54)"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_HP_CMD_SET_DATA_ACK);
            }

            break;

        case _PD_VDM_HP_CMD_GET_DATA_REQ:

            if(GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _TRUE)
            {
                // Get Hp System Status
                ScalerTypeC1PdGetHpSysStatus_EXINT0(_TYPE_C_HP_SYS_EVENT_GET_DATA_REQ);

                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Hp Get_data ACK (0x55)"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_HP_CMD_GET_DATA_ACK);
            }

            break;

        case _PD_VDM_HP_CMD_CMD_REQ:
        default:

            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : UFP Rcv. SOP Dell VDM Message Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntUfpRcvDellVdmMsgProc_EXINT0(void)
{
    switch((EnumTypeCVdmDellCmd)GET_TYPE_C_1_PD_RCV_VDM_CMD())
    {
        case _PD_VDM_DELL_CMD_DISCOVER_MODE_REQ:

            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

            // Send "Discover Mode ACK"
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_ACK);

            break;

        case _PD_VDM_DELL_CMD_ENTER_MODE_REQ:

            // if Obj Pos = Dell_Alt_Mode
            if(GET_TYPE_C_1_PD_VDM_OBJ_POS() == 1)
            {
                // Cancel WDTimerEvent (_TYPE_C_EMB_DELL_ALT_MODE_ENTER_TIMEOUT_TIMER)
                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_DELL_AM_ENTER_TIMEOUT);

                // If Source Choose to Enter Dell Alt Mode. Set Object Position to 1
                SET_TYPE_C_1_PD_DELL_OBJ_POS(GET_TYPE_C_1_PD_VDM_OBJ_POS());

                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                SET_TYPE_C_1_PD_DELL_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK);

                // Send "Enter Mode ACK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_ACK);
            }
            else
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Enter Mode NAK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_NAK);
            }

            break;

        case _PD_VDM_DELL_CMD_EXIT_MODE_REQ:

            // If Obj Pos = Dell_Alt_Mode or Exit All Modes & Already in Alt_Mode
            if(((GET_TYPE_C_1_PD_VDM_OBJ_POS() == GET_TYPE_C_1_PD_DELL_OBJ_POS()) || (GET_TYPE_C_1_PD_VDM_OBJ_POS() == 7)) && (GET_TYPE_C_1_PD_DELL_ALT_MODE_ENTER() == _TRUE))
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                SET_TYPE_C_1_PD_DELL_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK);

                // Send "Exit Mode ACK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_ACK);
            }
            else
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode NAK"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_NAK);
            }

            break;

        case _PD_VDM_DELL_CMD_0X12_REQ:

            if(GET_TYPE_C_1_PD_DELL_ALT_MODE_ENTER() == _TRUE)
            {
                // Get Dell System Information and Set 0x12 SysEvent
                ScalerTypeC1PdGetDellSysInfo_EXINT0();
                SET_TYPE_C_1_PD_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_0X12);

                if(GET_TYPE_C_1_PD_DELL_USER_EVENT() != _TYPE_C_DELL_USER_EVENT_NONE)
                {
                    if(GET_TYPE_C_1_PD_DELL_ALT_MODE_STATE() == _PD_ALT_MODE_INT_WAIT_DELL_0X13)
                    {
                        // Cancel WDTimerEvent (_TYPE_C_EMB_DELL_ALT_MODE_ATTEN_RETRY_TIMER)
                        ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_DELL_ATTEN_RETRY);

                        // If (User Event != None), Set Atten_NoResponse SysEvent to Kernel and Clear User Event
                        CLR_TYPE_C_1_PD_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ATTEN);
                        CLR_TYPE_C_1_PD_DELL_ATTEN_RETRY_CNT();
                        CLR_TYPE_C_1_PD_DELL_ATTEN_WAIT();
                        SET_TYPE_C_1_PD_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_NORESPONSE);
                    }
                    else
                    {
                        // If (User Event != None) && (Attention has not Sent by Kernel) , Set Atten_Discard SysEvent to Kernel and Clear User Event
                        CLR_TYPE_C_1_PD_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ATTEN);
                        SET_TYPE_C_1_PD_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_DISCARD);
                    }
                }

                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                SET_TYPE_C_1_PD_DELL_ALT_MODE_STATE(_PD_ALT_MODE_INT_SEND_DELL_0X12_ACK);

                // Send "Dell 0x12 ACK (0x52)"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_DELL_CMD_0X12_ACK);
            }

            break;

        case _PD_VDM_DELL_CMD_0X13_REQ:

            if(GET_TYPE_C_1_PD_DELL_ALT_MODE_ENTER() == _TRUE)
            {
                if(GET_TYPE_C_1_PD_DELL_USER_EVENT() != _TYPE_C_DELL_USER_EVENT_NONE)
                {
                    if(GET_TYPE_C_1_PD_DELL_ALT_MODE_STATE() == _PD_ALT_MODE_INT_WAIT_DELL_0X13)
                    {
                        // Cancel WDTimerEvent (_TYPE_C_EMB_DELL_ALT_MODE_ATTEN_RETRY_TIMER)
                        ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_DELL_ATTEN_RETRY);

                        // Clear Dell Related Macros and Set Atten_Success System Event
                        CLR_TYPE_C_1_PD_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ATTEN);
                        CLR_TYPE_C_1_PD_DELL_ATTEN_RETRY_CNT();
                        CLR_TYPE_C_1_PD_DELL_ATTEN_WAIT();
                        SET_TYPE_C_1_PD_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_SUCCESS);
                        SET_TYPE_C_1_PD_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
                    }
                }
            }

            break;

        default:

            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Process Rcv. Msg. in Interrupt in SNK_READY During _AMS_NON_INTERRUPTIBLE/_AMS_POWER_TRANSITION
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntRcvMsgInAmsProc_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo)
{
    enumRxProcFifo = enumRxProcFifo;

    switch(GET_TYPE_C_1_PD_SUB_STATE())
    {
        case _PD_SUB_INT_WAIT_SRC_CAP:

            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_SRC_CAP)
            {
                // 1. Store Src_Cap Info from Data Objects
                SET_TYPE_C_1_PD_PARTNER_DRP(g_pucTypeC1PdDataObject_EXINT[0] >> 5);
                SET_TYPE_C_1_PD_PARTNER_SUSPEND(g_pucTypeC1PdDataObject_EXINT[0] >> 4);
                SET_TYPE_C_1_PD_PARTNER_EXT_PWR(g_pucTypeC1PdDataObject_EXINT[0] >> 3);
                SET_TYPE_C_1_PD_PARTNER_USB_CAP(g_pucTypeC1PdDataObject_EXINT[0] >> 2);
                SET_TYPE_C_1_PD_PARTNER_DRD(g_pucTypeC1PdDataObject_EXINT[0] >> 1);
                SET_TYPE_C_1_PD_PARTNER_UNCHK(g_pucTypeC1PdDataObject_EXINT[0] >> 0);
                SET_TYPE_C_1_PD_PARTNER_EPR_CAP(g_pucTypeC1PdDataObject_EXINT[1] >> 7);

                // Get Number Of Capabilities
                SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT(GET_TYPE_C_1_PD_RCV_NOD_CNT());

                // Evaluate and Set Request Data Objects
                for(BYTE ucLoopIndex = 0; ucLoopIndex < _TYPE_C_PDO_NUM_7; ucLoopIndex++)
                {
                    if(ucLoopIndex < GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT())
                    {
                        if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                        {
                            // Set APDO Type
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex, ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                        }
                        else
                        {
                            // Set PDO Type
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex, ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) >> 6));
                        }

                        if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                        {
                            // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex, (((((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & 0x01)) << 7) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 1] & 0xFE)) >> 1)) * 10));
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(ucLoopIndex, (((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2]) * 10));
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(ucLoopIndex, (((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 3] & 0x7F) * 5));
                        }
                        else
                        {
                            // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex, (((((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2] & 0xFC)) >> 2)) * 5));
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(ucLoopIndex, GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex));
                            SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(ucLoopIndex, (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 3]));
                            SET_TYPE_C_1_PD_PARTNER_SRC_PEAK_CUR(ucLoopIndex, ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 1] & (_BIT5 | _BIT4)) >> 4));

                            // If Target Voltage Matches Partner's Voltage, Set the Macros of Capability Mismatch and Object Position.
                            if((GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_TARGET_VOL) && (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex) == (GET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL() * 100)))
                            {
                                SET_TYPE_C_1_PD_REQ_CAP_MIS(_FALSE);
                                SET_TYPE_C_1_PD_REQ_OBJ_POS((EnumTypeCPdoNumber)(ucLoopIndex + 1));
                            }
                        }
                    }
                    else
                    {
                        // If ucLoopIndex >= GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT(), Clear the Related Macros to 0x00.
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucLoopIndex, _PD_NONE_SETTING_PDO);
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucLoopIndex, 0x00);
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(ucLoopIndex, 0x00);
                        SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(ucLoopIndex, 0x00);
                        SET_TYPE_C_1_PD_PARTNER_SRC_PEAK_CUR(ucLoopIndex, 0x00);
                    }
                }

                // According to the corresponding Request Type, Set the Macros of Capability Mismatch and Object Position.
                if(GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_LOWEST_VOL)
                {
                    SET_TYPE_C_1_PD_REQ_CAP_MIS(_FALSE);
                    SET_TYPE_C_1_PD_REQ_OBJ_POS(_TYPE_C_PDO_NUM_1);
                }
                else if(GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_HIGHEST_VOL)
                {
                    SET_TYPE_C_1_PD_REQ_CAP_MIS(_FALSE);
                    SET_TYPE_C_1_PD_REQ_OBJ_POS((EnumTypeCPdoNumber)(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT()));
                }
                else if((GET_TYPE_C_1_PD_REQ_TYPE() == _TYPE_C_REQ_TARGET_VOL) && (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) != (GET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL() * 100)))
                {
#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
                    // [MM1AE-4187] Don't Set Capability Mismatch for Powered from Vbus 5.1V RDO
                    if(GET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL() != 51)
                    {
                        SET_TYPE_C_1_PD_REQ_CAP_MIS(_TRUE);
                    }
#else
                    SET_TYPE_C_1_PD_REQ_CAP_MIS(_TRUE);
#endif

                    SET_TYPE_C_1_PD_REQ_OBJ_POS(_TYPE_C_PDO_NUM_1);
                }

                // If Request Type isn't Customized RDO, Need to be Set Operating and Max. Current.
                if(GET_TYPE_C_1_PD_REQ_TYPE() != _TYPE_C_REQ_CUSTOMIZED_RDO)
                {
                    SET_TYPE_C_1_PD_REQ_INFO_1(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1));
                    SET_TYPE_C_1_PD_REQ_INFO_2(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1));
                }

                // 2. Evaluate if Received Source Capability is Valid
                SET_TYPE_C_1_PD_PARTNER_SRC_CAP_CHECK_RESULT(ScalerTypeC1PdCheckSrcCapValid_EXINT0());

                // 3. Update Flag and Transit State
                SET_TYPE_C_1_PD_RCV_SRC_CAP();
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);
                ScalerTypeC1PdBackToReadyState_EXINT0();
            }
            else if((GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_REJECT) || (GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_NOT_SUPPORT))
            {
                // Port Partner Does Not Support DRP
                SET_TYPE_C_1_PD_PARTNER_DRP(_FALSE);

                // Set AMS = None
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeC1PdBackToReadyState_EXINT0();
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_SNK_CAP:

            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_SNK_CAP)
            {
                // 1. Store Snk_Cap Info from Data Objects
                SET_TYPE_C_1_PD_PARTNER_DRP(g_pucTypeC1PdDataObject_EXINT[0] >> 5);
                SET_TYPE_C_1_PD_PARTNER_HIGH_CAP(g_pucTypeC1PdDataObject_EXINT[0] >> 4);
                SET_TYPE_C_1_PD_PARTNER_EXT_PWR(g_pucTypeC1PdDataObject_EXINT[0] >> 3);
                SET_TYPE_C_1_PD_PARTNER_USB_CAP(g_pucTypeC1PdDataObject_EXINT[0] >> 2);
                SET_TYPE_C_1_PD_PARTNER_DRD(g_pucTypeC1PdDataObject_EXINT[0] >> 1);

                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    // [24:23] Fast Role Swap Default Require Current
                    SET_TYPE_C_1_PD_PARTNER_FRS_CUR(((g_pucTypeC1PdDataObject_EXINT[0] & _BIT0) << 1) | ((g_pucTypeC1PdDataObject_EXINT[1] & _BIT7) >> 7));
                }

                // Get Number Of Capabilities
                SET_TYPE_C_1_PD_PARTNER_SNK_CAP_CNT(GET_TYPE_C_1_PD_RCV_NOD_CNT());

                // Evaluate and Set Request Data Objects
                for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TYPE_C_1_PD_PARTNER_SNK_CAP_CNT(); ucLoopIndex++)
                {
                    if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
                    {
                        // Set APDO Type
                        SET_TYPE_C_1_PD_PARTNER_SNK_CAP_TYPE(ucLoopIndex, ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
                    }
                    else
                    {
                        // Set PDO Type
                        SET_TYPE_C_1_PD_PARTNER_SNK_CAP_TYPE(ucLoopIndex, ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & (_BIT7 | _BIT6)) >> 6));
                    }

                    if(GET_TYPE_C_1_PD_PARTNER_SNK_CAP_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        // Set PDO Voltage (Unit 100mV to 10mV) and Current (Unit 50mA to 10mA)
                        SET_TYPE_C_1_PD_PARTNER_SNK_CAP_VOL_MAX(ucLoopIndex, (((((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4] & 0x01)) << 7) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 1] & 0xFE)) >> 1)) * 10));
                        SET_TYPE_C_1_PD_PARTNER_SNK_CAP_VOL_MIN(ucLoopIndex, (((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2]) * 10));
                        SET_TYPE_C_1_PD_PARTNER_SNK_CAP_CUR(ucLoopIndex, (((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 3] & 0x7F) * 5));
                    }
                    else
                    {
                        // Set PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                        SET_TYPE_C_1_PD_PARTNER_SNK_CAP_VOL_MAX(ucLoopIndex, (((((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 1] & 0x0F)) << 6) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2] & 0xFC)) >> 2)) * 5));
                        SET_TYPE_C_1_PD_PARTNER_SNK_CAP_VOL_MIN(ucLoopIndex, GET_TYPE_C_1_PD_PARTNER_SNK_CAP_VOL_MAX(ucLoopIndex));
                        SET_TYPE_C_1_PD_PARTNER_SNK_CAP_CUR(ucLoopIndex, (((WORD)(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 2] & 0x03)) << 8) | ((WORD)g_pucTypeC1PdDataObject_EXINT[ucLoopIndex * 4 + 3]));
                    }
                }

                SET_TYPE_C_1_PD_RCV_SNK_CAP();

                // Set AMS = None
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeC1PdBackToReadyState_EXINT0();
            }
            else if((GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_REJECT) || (GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_NOT_SUPPORT))
            {
                // Port Partner Does Not Support DRP
                SET_TYPE_C_1_PD_PARTNER_DRP(_FALSE);

                // Set AMS = None
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeC1PdBackToReadyState_EXINT0();
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_PRS_RESP:

            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_ACCEPT)
            {
                // "Accept" Message Has Been Sent Successfully
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_POWER_TRANSITION);

                if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
                {
                    // 1. Turn Off Power After 25-35ms
                    ScalerTimerWDActivateTimerEvent_EXINT0(_SRC_ADJUST_POWER_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_SRC_OFF_PSRDY);
                }
                else
                {
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
                    // 1. Turn Off Sink Power, Disable Detect Sink OVP/UVP
                    ScalerTypeC1PmicSetting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
#endif

                    // 2. Disable TypeC Vbus Detach Detect Function
                    // 3. Disable SNK Detect Rp to Transit from Attached.SNK to Unattached.SNK State
                    ScalerTypeC1CcVbusDetCtrl_EXINT0(_DISABLE);
                    ScalerTypeC1CcSnkDetRpCtrl_EXINT0(_DISABLE);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
                    // [Eizo] SIC437A Customized Power Control : Receive Accept to PR Swap as Sink
                    ScalerTypeC1PmicSic437aPRSwapStartProc_EXINT0(_TYPE_C_POWER_SNK);
#endif

                    // PD Merged Test [TEST.PD.PROT.SNK.12]
                    ScalerTypeC1PdActiveTimerEvent_EXINT0(_PS_SRC_OFF_TIMER, _SCALER_TIMER_EVENT_PD_1_TPC_ERROR_RECOVERY);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_SRC_OFF);
                }

                // Receive Accept to PR_Swap, Set Flag For Retimer Usage
                SET_TYPE_C_1_PD_PRS_PROCESSING();
            }
            else if((GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_REJECT) || (GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_NOT_SUPPORT))
            {
                // Port Partner Reject PR Swap
                SET_TYPE_C_1_PD_PRS_REJECT();

                // Set AMS = None
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeC1PdBackToReadyState_EXINT0();
            }
            else if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_WAIT)
            {
                // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                SET_TYPE_C_1_PD_PRS_WAIT_FLAG();
                ScalerTypeC1PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_PRS_WAIT);

                // Set AMS = None
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeC1PdBackToReadyState_EXINT0();
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_SRC_OFF:

            // Cancel TimerEvent(_PS_SRC_OFF_TIMER)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_TPC_ERROR_RECOVERY);
            if((GET_TYPE_C_1_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_1_TPC_ERROR_RECOVERY) && (GET_TYPE_C_1_PD_TIMER_EVENT_VALID() == _TRUE))
            {
                CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();
            }

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_PS_RDY)
            {
                // Wait > 5ms for Google Pixelbook Interop Issue (MM1AE-2956). Timeout : Switch Power Role to SRC and Turn on Vbus.
                ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_PD_1_SNK_SWITCH_TO_SRC);
            }
            else
            {
                // Rcv Unexpected Message During Rp-Rd Switch
                SET_TYPE_C_1_CC_ERROR_RECOVERY();
                CLR_TYPE_C_1_PD_PRS_PROCESSING();
            }

            break;

        case _PD_SUB_INT_WAIT_SRC_ON:

            // Cancel TimerEvent(PS_SRC_ON_TIMER);
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_TPC_ERROR_RECOVERY);
            if((GET_TYPE_C_1_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_1_TPC_ERROR_RECOVERY) && (GET_TYPE_C_1_PD_TIMER_EVENT_VALID() == _TRUE))
            {
                CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();
            }

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_PS_RDY)
            {
                // Set FW State to "_PD_SNK_START_UP" and Run PdStartUpProc
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);
                SET_TYPE_C_1_PD_FW_STATE(_PD_SNK_START_UP);

                ScalerTypeC1PdStartUpProc_EXINT0();

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
                // Update Vbus Power Info to Support Sink OVP/UVP
                ScalerTypeC1PmicSetting_EXINT0(_ON, _PD_POWER_SNK, _PD_FIX_SUPPLY_PDO, 500, 0, _PD_PEAK_CUR_NONE);
#endif

#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON))
                // Start PMIC Protection
                ScalerTypeC1PmicProtectStart_EXINT0(_TYPE_C_POWER_SNK);
#endif
            }
            else
            {
                // Receive Unexpected Message in Power-Transition AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
                CLR_TYPE_C_1_PD_PRS_PROCESSING();
            }

            break;

        case _PD_SUB_INT_WAIT_DRS_RESP:

            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_ACCEPT)
            {
                if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
                {
                    // [0x6BE5] Update FW/HW Data Role to UFP
                    ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);
                    SET_TYPE_C_1_PD_DATA_ROLE(_PD_DATA_UFP);

                    // PD 2.0 : Prevent Receiving Cable Message When Data Role is UFP During Explicit Contract
                    if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0)
                    {
                        // [0x6B34] Setup Rx Valid Packet Type (UFP : SOP / Hard Reset)
                        ScalerSetByte_EXINT(P6B_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT0));
                    }

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
                    // Set PARTNER_ALT_SUPPORT FLAG to Wait For Port Partner Initiating Alt Mode Flow
                    SET_TYPE_C_1_PD_PARTNER_ALT_SUPPORT();

                    // DFP DR_SWAP to UFP, if Not Enter ALt Mode in 2 Sec After Power Contract, timeout: Clear PARTNER_ALT_SUPPORT Macro
                    ScalerTypeC1PdActiveTimerEvent_EXINT0(_PARTNER_ALT_SUPPORT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_PARTNER_ALT_SUPPORT);
#endif
                }
                else
                {
                    // [0x6BE5] Update FW/HW Data Role to DFP
                    ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, _BIT0);
                    SET_TYPE_C_1_PD_DATA_ROLE(_PD_DATA_DFP);

                    // PD 2.0 : Only DFP && Vconn Source Can Communicate With Cable During Explicit Contract
                    if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) && (GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC))
                    {
                        // [0x6B34] Setup Rx Valid Packet Type (Vconn SRC : SOP / SOP' / SOP" / Hard Reset)
                        ScalerSetByte_EXINT(P6B_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }

                // DR Swap AMS Finished
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeC1PdBackToReadyState_EXINT0();
            }
            else if((GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_REJECT) || (GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_NOT_SUPPORT))
            {
                // Port Partner Reject DR Swap
                SET_TYPE_C_1_PD_DRS_REJECT();

                // Set AMS = None
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeC1PdBackToReadyState_EXINT0();

                // [Interop] Data Role Correction : Some Sources Have Wrong Data Role and Do Not Accept DR_SWAP
                // For Data Role Swap Reject & Data Role Error => Swith Our Data Role to Prevent From Both Side Start Alt Mode
                if(((ScalerGetBit_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20), _BIT5)) >> 5) == (ScalerGetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, _BIT0)))
                {
                    if((ScalerGetBit_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20), _BIT5)) == _BIT5)
                    {
                        // [0x6BE5] Update FW/HW Data Role to UFP
                        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);
                        SET_TYPE_C_1_PD_DATA_ROLE(_PD_DATA_UFP);
                    }
                    else
                    {
                        // [0x6BE5] Update FW/HW Data Role to DFP
                        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, _BIT0);
                        SET_TYPE_C_1_PD_DATA_ROLE(_PD_DATA_DFP);
                    }
                }
            }
            else if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_WAIT)
            {
                // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                SET_TYPE_C_1_PD_DRS_WAIT_FLAG();
                ScalerTypeC1PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_DRS_WAIT);

                // Set AMS = None
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeC1PdBackToReadyState_EXINT0();
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_VCS_RESP:

            if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
            {
                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_ENTER_FAILED);
            }
            else
            {
                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);
            }

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_ACCEPT)
            {
                // "Accept" Message Has Been Sent Successfully
                if(GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VCONN_ON);
                    ScalerTypeC1PdActiveTimerEvent_EXINT0(_WAIT_VCONN_ON_TIMER, _SCALER_TIMER_EVENT_PD_1_SEND_HARD_RST);
                }
                else
                {
                    // Turn On Vconn Power
                    ScalerTypeC1CcVconnControl_EXINT0(_ON);

                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_WDINT_SEND_VCONN_ON_PSRDY);
                    ScalerTimerWDActivateTimerEvent_EXINT0(5, _SCALER_WD_TIMER_EVENT_PD_1_SEND_VCONN_ON_PSRDY);
                }
            }
            else if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_REJECT)
            {
                // Port Partner Reject Vconn Swap
                SET_TYPE_C_1_PD_VCS_REJECT();

                if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);

                    // Send Enter Failed : Source Not Vconn Source
                    SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                    SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_NOT_VCONN_SOURCE);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Set AMS = None
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeC1PdBackToReadyState_EXINT0();
                }
            }
            else if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_NOT_SUPPORT)
            {
                if(GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC)
                {
                    // Port Partner Reject Vconn Swap
                    SET_TYPE_C_1_PD_VCS_REJECT();
                }
                else
                {
                    // Turn On Vconn Power
                    ScalerTypeC1CcVconnControl_EXINT0(_ON);

                    // Set Vconn Role to Vconn SRC
                    SET_TYPE_C_1_PD_VCONN_ROLE(_PD_VCONN_SRC);

                    // PD 2.0 : Only DFP && Vconn Source Can Communicate With Cable During Explicit Contract
                    // PD 3.0 : Only Vconn Source Can Communicate With Cable
                    if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) || ((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) && (GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)))
                    {
                        // [0x6B34] Setup Rx Valid Packet Type (Vconn SRC : SOP / SOP' / SOP" / Hard Reset)
                        ScalerSetByte_EXINT(P6B_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }

                    // Do Soft Reset to Cable When We Become Vconn Src During Enter EPR Mode Flow
                    if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_CABLE_PROC);
                        SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_INT_SEND_SOFT_RST);

#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                        // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                        ScalerTypeC1PdUpdateCableRetryCounter_EXINT0();
#endif
                        // Send Soft Reset(SOP') to Reset Cable
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                        ScalerTypeC1PdSendSoftRst_EXINT0(_PD_SOP_P_PKT);
                    }
                }

                if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _FALSE)
                {
                    // Set AMS = None
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeC1PdBackToReadyState_EXINT0();
                }
            }
            else if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_WAIT)
            {
                // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                SET_TYPE_C_1_PD_VCS_WAIT_FLAG();
                ScalerTypeC1PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_VCS_WAIT);

                if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);

                    // Send Enter Failed : Source Not Vconn Source
                    SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                    SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_NOT_VCONN_SOURCE);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                }
                else
                {
                    // Set AMS = None
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeC1PdBackToReadyState_EXINT0();
                }
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_VCONN_ON:

            // Cancel TimerEvent(WAIT_VCONN_ON_TIMER)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_SEND_HARD_RST);
            if((GET_TYPE_C_1_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_1_SEND_HARD_RST) && (GET_TYPE_C_1_PD_TIMER_EVENT_VALID() == _TRUE))
            {
                CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();
            }

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_PS_RDY)
            {
                // Turn Off Vconn
                ScalerTypeC1CcVconnControl_EXINT0(_OFF);
/*
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
                // [WS116] Ellisys TD 4.9.4 FW Solution, Turn off Vconn below 0.8V within 35ms
                ScalerTypeC1CcFWModeTurnOffVconn_EXINT0();

                // Active WD Timer Event to Switch Back to HW Mode
                ScalerTimerWDActivateTimerEvent_EXINT0(40, _SCALER_WD_TIMER_EVENT_PD_1_TURN_OFF_VCONN_BACK_TO_HW_MODE);
#endif // End of #if(_TYPE_C_EMB_CTS_FLOW == _ON)
*/
                // Set Vconn Role to Vconn SNK
                SET_TYPE_C_1_PD_VCONN_ROLE(_PD_VCONN_NOT_SRC);

                // [0x6B34] Setup Rx Valid Packet Type (Not Vconn SRC : SOP / Hard Reset)
                ScalerSetByte_EXINT(P6B_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT0));

                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Reset Discover ID Retry Fail Counter After Vconn_Swap
                CLR_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT();

                // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                SET_TYPE_C_1_PD_VCS_WAIT_FLAG();
                ScalerTypeC1PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_VCS_WAIT);

                // Back to Ready State
                ScalerTypeC1PdBackToReadyState_EXINT0();
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_SUB_INT_WAIT_CHK_TEST_RESP:

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_CHUNK_TEST)
            {
                // Check If This Ext Msg is Chunked : Ext Message Header [15]
                if((GET_TYPE_C_1_PD_CHUNKED_MESSAGE() == _TRUE) && (GET_TYPE_C_1_PD_CHUNK_REQUEST() == _FALSE))
                {
                    // If Received Chunk Response Data < Total Message Data Size, Sent Chunk Request
                    if(((GET_TYPE_C_1_PD_CHUNK_NUMBER() + 1) * 26) < GET_TYPE_C_1_PD_EXT_MSG_DATA_SIZE())
                    {
                        // Set Chunk Message As an Chunk Request
                        SET_TYPE_C_1_PD_CHUNK_REQUEST(_TRUE);

                        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                        // Send "Chunk Test" REQUEST
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_CHK_TEST_REQ);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_CHUNK_TEST, _PD_VDM_CMD_RESERVED);
                    }
                    else
                    {
                        // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                    }
                }
                else
                {
                    // Send "Not Support" if Extended Msg is Not Sent in Chunkings or Not Chunk Resp
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_NOT_SUPPORT);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_NOT_SUPPORT, _PD_VDM_CMD_RESERVED);
                }
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

        case _PD_SUB_INT_WAIT_STATUS:

            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_STATUS)
            {
                SET_TYPE_C_1_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_STATUS_EVENT);
                SET_TYPE_C_1_PD_PARTNER_NEW_POWER_STATE(g_pucTypeC1PdDataObject_EXINT[8] & (_BIT2 | _BIT1 | _BIT0));
                SET_TYPE_C_1_PD_PARTNER_NEW_POWER_INDICATOR((g_pucTypeC1PdDataObject_EXINT[8] >> 3) & (_BIT2 | _BIT1 | _BIT0));

                // Receive Status Message, Temporary do nothing, Only Protocol For CTS
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Back to Ready State
                ScalerTypeC1PdBackToReadyState_EXINT0();
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        case _PD_SUB_INT_WAIT_EPR_SRC_CAP_CHUNK_REQ:

            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_CHUNK_SENDER_REQ_TIMEOUT);

            if((GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_EPR_SRC_CAP) && (GET_TYPE_C_1_PD_CHUNK_REQUEST() == _TRUE) && (GET_TYPE_C_1_PD_CHUNK_NUMBER() == GET_TYPE_C_1_PD_TX_CHUNK_NUMBER()))
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_SRC_CAP);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }
            else
            {
                // Receive Unexpected Message in Non-Interruptible AMS
                ScalerTypeC1PdPrlErrHandle_EXINT0();
            }

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        default:

            // Receive Unexpected Message in Unexpected FW State
            ScalerTypeC1PdPrlErrHandle_EXINT0();

            break;
    }
}

//--------------------------------------------------
// Description  : Process When Receive Soft Reset Message
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdRcvSoftRstProc_EXINT0(void)
{
    if(GET_TYPE_C_1_PD_FW_STATE() != _PD_HARDRESET)
    {
        // Clear Enter EPR Mode Flow Flag
        CLR_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW();

        if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
        {
            // Cancel SourceEPRKeepAliveTimer (750~1000ms)
            ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT);

            if((GET_TYPE_C_1_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT) && (GET_TYPE_C_1_PD_TIMER_EVENT_VALID() == _TRUE))
            {
                CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();
            }
        }

        if((GET_TYPE_C_1_PD_AMS_STATUS() == _PD_AMS_POWER_TRANSITION) || (GET_TYPE_C_1_PD_FW_STATE() == _PD_INT_WAIT_SOFTRESET_RESP))
        {   // 1. If Rcv. Soft Reset During Power Transition or Already in Soft Reset => HARD RESET
            ScalerTypeC1PdSendHardRst_EXINT0();
        }
        else if((GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_INT_WAIT_DRS_RESP) || (GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_INT_SEND_ACCEPT_DRS))
        {   // 2. If Rcv. Soft Reset During DR_SWAP => Type-C Error Recovery (8.3.3.4.1)
            SET_TYPE_C_1_CC_ERROR_RECOVERY();
        }
        else
        {   // 3. Else Do Soft Reset, Response Accept (Include Rcv. Soft Reset Again Before Reply Accept)

            // [0x6B03] Reset Protocol Layer State
            ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~_BIT0, _BIT0);

            SET_TYPE_C_1_PD_FW_STATE(_PD_INT_SEND_SOFTRESET_RESP);
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_HARD_RESET);

            // Send "Accept"
            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_ACCEPT, _PD_VDM_CMD_RESERVED);
        }
    }
}

//--------------------------------------------------
// Description  : Process Rcv. SOP' /SOP" Msg. in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntRcvCableMsgProc_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo)
{
    enumRxProcFifo = enumRxProcFifo;

    // Cancel TimerEvent(SENDER_RESP_TIMER)
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

    // Update PR/DR/Spec Version In Msg Header For SOP Communication.
    ScalerTypeC1PdUpdateTxFifoMsgHeader_EXINT0();

    if(GET_TYPE_C_1_PD_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)
    {
        // Update Cable Spec Version According to Our Spec Version and Cable Spec Version
        if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ||
           ((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20)) & (_BIT7 | _BIT6)) == _BIT6))
        {
            SET_TYPE_C_1_PD_CBL_SPEC_VER(_PD_VERSION_2_0);
        }
        else
        {
            SET_TYPE_C_1_PD_CBL_SPEC_VER(_PD_VERSION_3_0);
        }
    }

#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
    ScalerTypeC1PdSetCableRetryCounter_EXINT0();
#endif

    switch(GET_TYPE_C_1_PD_FW_STATE())
    {
        case _PD_INT_WAIT_CBL_DISCOVER_ID_RESP:

            if((GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_VDM) && (GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_ACK))
            {
                // Record Cable Info Of Discover ID Ack
                ScalerTypeC1PdSaveCableDiscoverIdAckInfo_EXINT0();
                SET_TYPE_C_1_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED);
            }

            // Send SRC_CAP After Discover ID NAK/BUSY or Unexpected Msg Received Before Power Contract
            // Send Discover ID to Cable After Power Contract If Discover ID ACK Not Received
            SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_WDINT_SEND_CAP);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

            // Active WD Timer Event To Check Vbus, Then Start PMIC Protection and Send SRC_CAP if VbusSafe5V
            ScalerTimerWDActivateTimerEvent_EXINT0(20, _SCALER_WD_TIMER_EVENT_PD_1_CHECK_VBUS);

            break;

        case _PD_INT_WAIT_CBL_SOFT_RESET_RESP:

            if(GET_TYPE_C_1_PD_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)
            {
                SET_TYPE_C_1_PD_FW_STATE(_PD_WDINT_SEND_CBL_DISCOVER_ID);
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Active WD Timer Event To Wait To Send Discover_ID_REQ, Timeout : Send Discover_ID Msg.
                ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);
            }
            else
            {
                // PD Transit to On-going PD Flow
                SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_WDINT_SEND_CAP);
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Active WD Timer Event To Wait To Send SRC_CAP, Timeout : Send SRC_CAP.
                ScalerTimerWDActivateTimerEvent_EXINT0(20, _SCALER_WD_TIMER_EVENT_PD_1_SEND_SRC_CAP);
            }

            break;

        case _PD_SRC_READY:
        case _PD_SNK_READY:

            switch(GET_TYPE_C_1_PD_SUB_STATE())
            {
                case _PD_SUB_CABLE_PROC:

                    switch(GET_TYPE_C_1_PD_CBL_STATE())
                    {
                        case _PD_CBL_INT_WAIT_SOFT_RST_RESP:

                            if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
                            {
                                if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_ACCEPT)
                                {
                                    SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_INT_SEND_DISCOVER_ID);

#if(_DISCOVER_ID_NO_RETRY == _TRUE)
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                                    // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp(For RL6829)
                                    ScalerSetBit_EXINT(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
#else
                                    // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp(For RL6952)
                                    ScalerSetBit_EXINT(P6B_ED_TX_PD_CBL_RTY_CNT, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif
#else
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                                    // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                                    ScalerTypeC1PdUpdateCableRetryCounter_EXINT0();
#endif
#endif
                                    // Send Discover ID (SOP') to Get Cable Info
                                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);
                                    SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_STATE_NONE);

                                    // Send Enter Failed : Cable Not Support EPR Mode
                                    SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                                    SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_CABLE_NOT_EPR_CAP);
                                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                                }
                            }
                            else
                            {
                                // Back to Ready State
                                ScalerTypeC1PdBackToReadyState_EXINT0();
                                SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_STATE_NONE);
                                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);
                            }

                            break;

                        case _PD_CBL_INT_WAIT_DISCOVER_ID_RESP:

                            CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();

                            if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                // Record Cable Info Of Discover ID Ack
                                ScalerTypeC1PdSaveCableDiscoverIdAckInfo_EXINT0();
                                SET_TYPE_C_1_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED);

                                if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
                                {
                                    // Check If Cable is EPR Capable : (1) EPR Capable Bit = 1 (2) Max Vbus Voltage = 50V (3) Max Vbus Current = 5A
                                    if((GET_TYPE_C_1_PD_CBL_EPR_MODE_CAPABLE() == _TRUE) && (GET_TYPE_C_1_PD_CBL_MAX_VOL() == 500) && (GET_TYPE_C_1_PD_CBL_MAX_CUR() == 500))
                                    {
                                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_SUCCESSFUL);

                                        // Send Enter Successful
                                        SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_SUCCESS);
                                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                                    }
                                    else
                                    {
                                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);

                                        // Send Enter Failed : Cable Not Support EPR Mode
                                        SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                                        SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_CABLE_NOT_EPR_CAP);
                                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                                        ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                                    }
                                }
                                else
                                {
                                    // Re-send SRC Cap since new cable max current get, new power contract is needed, set system event
                                    if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
                                    {
                                        if(ScalerTypeC1PdCheckRebuildPowerContract_EXINT0() == _PD_REBUILD_REQUIRED)
                                        {
                                            SET_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_SEND_SRC_CAP);
                                        }
                                    }
                                }
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_NAK) && (GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();
                                SET_TYPE_C_1_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);

                                if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
                                {
                                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);

                                    // Send Enter Failed : Cable Not Support EPR Mode
                                    SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                                    SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_CABLE_NOT_EPR_CAP);
                                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                                }
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_BUSY) && (GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID))
                            {
                                ADD_TYPE_C_1_PD_VDM_BUSY_CNT();

                                if(GET_TYPE_C_1_PD_VDM_BUSY_CNT() >= _MAX_VDM_BUSY_CNT)
                                {
                                    CLR_TYPE_C_1_PD_VDM_BUSY_CNT();
                                    SET_TYPE_C_1_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_VDM_BUSY_FLAG();

                                    // Clear VDM Busy Flag after 50ms.
                                    ScalerTypeC1PdActiveTimerEvent_EXINT0(_VDM_BUSY_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_VDM_BUSY_FLAG);
                                }

                                if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
                                {
                                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);

                                    // Send Enter Failed : Cable Not Support EPR Mode
                                    SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                                    SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_CABLE_NOT_EPR_CAP);
                                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                                }
                            }
                            else
                            {
                                // If Received Unexpected Message During Enter EPR Mode Flow : Send Enter Failed
                                if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
                                {
                                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);

                                    // Send Enter Failed : Cable Not Support EPR Mode
                                    SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                                    SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_CABLE_NOT_EPR_CAP);
                                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                                    ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);
                                }
                            }

                            SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_STATE_NONE);
                            if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _FALSE)
                            {
                                // Back to Ready State
                                ScalerTypeC1PdBackToReadyState_EXINT0();
                                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);
                            }

                            break;

                        default:

                            break;
                    }

                    break;

#if((_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))
                case _PD_SUB_INT_WAIT_VDM_RESP:

                    switch(GET_TYPE_C_1_PD_DP_ALT_STATE())
                    {
                        case _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP_SOP_P:

                            CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();

                            if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                // Record Cable Info Of Discover ID Ack
                                ScalerTypeC1PdSaveCableDiscoverIdAckInfo_EXINT0();
                                SET_TYPE_C_1_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED);

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable(When Ack Vdo Received For Discover Id(SOP'/SOP''))
                                SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableId_EXINT0());

                                // Re-send SRC Cap since new cable max current get, new power contract is needed, set system event
                                if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
                                {
                                    if(ScalerTypeC1PdCheckRebuildPowerContract_EXINT0() == _PD_REBUILD_REQUIRED)
                                    {
                                        SET_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_SEND_SRC_CAP);
                                    }
                                }
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_NAK) && (GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();
                                SET_TYPE_C_1_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);

                                // If No VDO Received, Set Passive Cable & HBR3 According to DPAM2.1
                                SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_PASSIVE);
                                SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_HBR3);

                                // Stop Enter DP Alt Mode Flow Just for Cable
                                CLR_TYPE_C_1_PD_CBL_ENTER_DP_MODE_SUPPORT();
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_ID_BUSY) && (GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID))
                            {
                                ADD_TYPE_C_1_PD_VDM_BUSY_CNT();

                                if(GET_TYPE_C_1_PD_VDM_BUSY_CNT() >= _MAX_VDM_BUSY_CNT)
                                {
                                    CLR_TYPE_C_1_PD_VDM_BUSY_CNT();
                                    SET_TYPE_C_1_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);

                                    // If No VDO Received, Set Passive Cable & HBR3 According to DPAM2.1
                                    SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_PASSIVE);
                                    SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_HBR3);

                                    // Stop Enter DP Alt Mode Flow Just for Cable
                                    CLR_TYPE_C_1_PD_CBL_ENTER_DP_MODE_SUPPORT();
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P);
                                    SET_TYPE_C_1_PD_VDM_BUSY_FLAG();

                                    // Clear VDM Busy Flag after 50ms.
                                    ScalerTypeC1PdActiveTimerEvent_EXINT0(_VDM_BUSY_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_VDM_BUSY_FLAG);
                                }
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP_SOP_P:

                            CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();

                            if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_SVID_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                // Search Through All SVIDs to All Svid The Cable Supports
                                ScalerTypeC1PdSearchCableSvid_EXINT0();

                                if(GET_TYPE_C_1_PD_CBL_SVID_SEARCH_FINISH() == _FALSE)
                                {
                                    // If Search Finish = FALSE, Send Cable Discover SVID Again to Get More SVID
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P);
                                }
                                else
                                {
                                    if(GET_TYPE_C_1_PD_CBL_DP_SVID_SUPPORT() == _TRUE)
                                    {
                                        SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P);
                                    }
                                    else if(GET_TYPE_C_1_PD_CBL_TBT3_SVID_SUPPORT() == _TRUE)
                                    {
                                        SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P);
                                    }
                                    else
                                    {
                                        // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When Cable Don't Support DP or TBT3 SVID
                                        SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableDpFunctionality_EXINT0());
                                    }
                                }
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_SVID_NAK) && (GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When NAK of Discover Svid(SOP' / SOP'') Received
                                SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableDpFunctionality_EXINT0());
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_SVID_BUSY) && (GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID))
                            {
                                ADD_TYPE_C_1_PD_VDM_BUSY_CNT();

                                if(GET_TYPE_C_1_PD_VDM_BUSY_CNT() >= _MAX_VDM_BUSY_CNT)
                                {
                                    CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                    // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When BUSY of Discover Svid(SOP' / SOP'') Received
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableDpFunctionality_EXINT0());
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P);
                                    SET_TYPE_C_1_PD_VDM_BUSY_FLAG();

                                    // Clear VDM Busy Flag after 50ms.
                                    ScalerTypeC1PdActiveTimerEvent_EXINT0(_VDM_BUSY_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_VDM_BUSY_FLAG);
                                }
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_DISCOVER_MODE_RESP_SOP_P:

                            CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();

                            if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_MODE_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                // Record Cable Info Of Discover DP Mode Ack
                                ScalerTypeC1PdSaveCableDpModeInfo_EXINT0();
                                SET_TYPE_C_1_PD_CBL_DP_MODE_INFO_RECEIVED();

                                if(GET_TYPE_C_1_PD_CBL_TBT3_SVID_SUPPORT() == _TRUE)
                                {
                                    // If Cable Also Support TBT3 Mode, Discover Cable TBT3 Mode Before Enter Mode
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P);
                                }
                                else
                                {
                                    // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Enter Mode First
                                    if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
                                    {
                                        SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE_SOP_P);
                                    }
                                    else
                                    {
                                        SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                                    }
                                }
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_MODE_NAK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When NAK of DP Discover Mode(SOP' / SOP'') Received
                                SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableDpFunctionality_EXINT0());
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_MODE_BUSY) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                ADD_TYPE_C_1_PD_VDM_BUSY_CNT();

                                if(GET_TYPE_C_1_PD_VDM_BUSY_CNT() >= _MAX_VDM_BUSY_CNT)
                                {
                                    CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                    // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When BUSY of DP Discover Mode(SOP' / SOP'') Received
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableDpFunctionality_EXINT0());
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P);
                                    SET_TYPE_C_1_PD_VDM_BUSY_FLAG();

                                    // Clear VDM Busy Flag after 50ms.
                                    ScalerTypeC1PdActiveTimerEvent_EXINT0(_VDM_BUSY_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_VDM_BUSY_FLAG);
                                }
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_TBT3_DISCOVER_MODE_RESP_SOP_P:

                            CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();

                            if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_MODE_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _TBT3_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                // Record Cable Info Of TBT3 Discover Mode Ack
                                ScalerTypeC1PdSaveCableTbt3ModeInfo_EXINT0();

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When ACK of TBT3 Discover Mode(SOP' / SOP'') Received
                                SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableTbt3Mode_EXINT0());
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_MODE_NAK) && (GET_TYPE_C_1_PD_VDM_SVID() == _TBT3_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When NAK of TBT3 Discover Mode(SOP' / SOP'') Received
                                SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableDpFunctionality_EXINT0());
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_DISCOVER_MODE_BUSY) && (GET_TYPE_C_1_PD_VDM_SVID() == _TBT3_SID))
                            {
                                ADD_TYPE_C_1_PD_VDM_BUSY_CNT();

                                if(GET_TYPE_C_1_PD_VDM_BUSY_CNT() >= _MAX_VDM_BUSY_CNT)
                                {
                                    CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                    // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When BUSY of TBT3 Discover Mode(SOP' / SOP'') Received
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableDpFunctionality_EXINT0());
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P);
                                    SET_TYPE_C_1_PD_VDM_BUSY_FLAG();

                                    // Clear VDM Busy Flag after 50ms.
                                    ScalerTypeC1PdActiveTimerEvent_EXINT0(_VDM_BUSY_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_VDM_BUSY_FLAG);
                                }
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_P:

                            CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();

                            if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_ENTER_MODE_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                if(GET_TYPE_C_1_PD_CBL_SOP_PP_SUPPORT() == _TRUE)
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP);
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                                }
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_ENTER_MODE_NAK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_PP:

                            CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();

                            if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_ENTER_MODE_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_ENTER_MODE_NAK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_P:

                            CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();

                            if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_51) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                if(GET_TYPE_C_1_PD_CBL_SOP_PP_SUPPORT() == _TRUE)
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP);
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                                }
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_91) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_PP:

                            CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();

                            if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_51) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_91) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_P:

                            CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();

                            if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_EXIT_MODE_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                if(GET_TYPE_C_1_PD_CBL_SOP_PP_SUPPORT() == _TRUE)
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP);
                                }
                                else
                                {
                                    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                                }
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_EXIT_MODE_NAK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        case _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_PP:

                            CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();

                            if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_EXIT_MODE_ACK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                            else if((GET_TYPE_C_1_PD_RCV_VDM_CMD() == _PD_VDM_CMD_EXIT_MODE_NAK) && (GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID))
                            {
                                CLR_TYPE_C_1_PD_VDM_BUSY_CNT();

                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);
                            }
                            else
                            {
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_ERROR);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            break;

                        default:

                            break;
                    }

                    break;
#endif  // End of #if((_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))

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
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdPrlErrHandle_EXINT0(void)
{
    if(GET_TYPE_C_1_PD_FW_STATE() == _PD_INT_WAIT_SOFTRESET_RESP)
    {
        // If  : Rcv Unexpected Msg. During Soft Reset, Do "HARD RESET"
        ScalerTypeC1PdSendHardRst_EXINT0();
    }
    else
    {
        switch(GET_TYPE_C_1_PD_AMS_STATUS())
        {
            case _PD_AMS_NONE:
            case _PD_AMS_INTERRUPTIBLE:
            case _PD_AMS_NON_INTERRUPTIBLE:

                // Clear Enter EPR Mode Flow Flag
                CLR_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW();

                SET_TYPE_C_1_PD_FW_STATE(_PD_INT_SEND_SOFTRESET);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                ScalerTypeC1PdSendSoftRst_EXINT0(_PD_SOP_PKT);

                break;

            case _PD_AMS_POWER_TRANSITION:

                ScalerTypeC1PdSendHardRst_EXINT0();

                break;

            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Process When Tx Transmission Success in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntTxSuccessProc_EXINT0(void)
{
    WORD usSrcAdjustPowerTime = 0;

    switch(GET_TYPE_C_1_PD_FW_STATE())
    {
        case _PD_INT_SEND_CBL_DISCOVER_ID:
        case _PD_INT_SEND_CBL_SOFT_RESET:

            ScalerTypeC1PdIntTxCableReqSuccessProc_EXINT0();

            break;

        case _PD_SRC_INT_SEND_CAP:

            // Reset Source Cap Counter and Hard Reset Counter
            CLR_TYPE_C_1_PD_SRC_CAP_CNT();
            CLR_TYPE_C_1_PD_HARD_RST_CNT();
            CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_SEND_SRC_CAP);

            // State Transition, AMS & Timer Setting
            SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_INT_WAIT_REQ);
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Hard Reset
            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);

            break;

        case _PD_SRC_INT_SEND_ACCEPT_REQ:

            // State Transition
            SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_WDINT_TRANSIT_POWER);
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_POWER_TRANSITION);

            if((GET_TYPE_C_1_PD_REQ_PPS_VOL_SMALL_STEP() != _TRUE) && (GET_TYPE_C_1_PD_REQ_AVS_VOL_SMALL_STEP() != _TRUE))
            {
                usSrcAdjustPowerTime = _SRC_ADJUST_POWER_TIMER;
            }
            else
            {
                usSrcAdjustPowerTime = 5;
            }

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
            // [Eizo] SIC437A Customized Power Control : Receive Accept During Power Transition
            ScalerTypeC1PmicSic437aTransitionStartProc_EXINT0(GET_TYPE_C_1_PD_PARTNER_REQ_VOL(), GET_TYPE_C_1_PD_PARTNER_MAX_CUR(), &usSrcAdjustPowerTime);
#endif

            // Set WD Timer to Wait 25-35ms, then Turn On Vbus
            ScalerTimerWDActivateTimerEvent_EXINT0(usSrcAdjustPowerTime, _SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_ON_POWER);

            break;

        case _PD_SRC_INT_SEND_REJECT_REQ:
        case _PD_SRC_INT_SEND_WAIT_REQ:

            if(GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() == _TRUE)
            {
                // If Reject Request & Power Contract Exist,
                if(ScalerTypeC1PdCheckPowerContractValid_EXINT0() == _TRUE)
                {
                    // Set AMS = None
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeC1PdBackToReadyState_EXINT0();
                }
                else
                {
                    // If Power Contract is no more Valid, Do Hard Reset
                    ScalerTypeC1PdSendHardRst_EXINT0();
                }
            }
            else
            {
                // If Reject Request & No Power Contract, Wait 120ms and Re-Send Src_Cap
                SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_WDINT_SEND_CAP);
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                // Active WD Timer Event To Wait To Send SRC_CAP, Timeout : Send SRC_CAP.
                ScalerTimerWDActivateTimerEvent_EXINT0(120, _SCALER_WD_TIMER_EVENT_PD_1_SEND_SRC_CAP);
            }

            break;

        case _PD_SRC_INT_SEND_PSRDY:

            // Set AMS = None
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

            // Back to Ready State
            ScalerTypeC1PdBackToReadyState_EXINT0();

            // Set Power Contract = TRUE
            SET_TYPE_C_1_PD_EXPLICIT_CONTRACT();
            ScalerSetBit_EXINT(P6B_18_VENDOR_SPECIFIC_SOP3_CFG1, ~(_BIT7 | _BIT6), (GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() << 7));

#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
            // Clear OCP/OVP/UVP/Vconn OCP Event and Alert Macro due to New Power Contract Established
            CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);
            CLR_TYPE_C_1_PD_ALERT_SENT();
#endif

            break;

        case _PD_SNK_INT_SEND_REQUEST:

            CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_SEND_REQUEST);

            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Hard Reset
            SET_TYPE_C_1_PD_FW_STATE(_PD_SNK_INT_WAIT_REQ_RESP);
            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);

            break;

        case _PD_INT_SEND_SOFTRESET:

            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Hard Reset
            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);

            SET_TYPE_C_1_PD_FW_STATE(_PD_INT_WAIT_SOFTRESET_RESP);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

            break;

        case _PD_INT_SEND_SOFTRESET_RESP:

            if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
            {
                if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
                {
                    SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_READY);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_WDINT_SEND_EPR_SRC_CAP);

                    // Active WD Timer Event To Send EPR_SRC_CAP, Timeout : Send EPR_SRC_CAP.
                    ScalerTimerWDActivateTimerEvent_EXINT0(20, _SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_SRC_CAP);
                }
                else
                {
                    // Clear Explicit Power Contract and Flags
                    CLR_TYPE_C_1_PD_EXPLICIT_CONTRACT();
                    ScalerSetBit_EXINT(P6B_18_VENDOR_SPECIFIC_SOP3_CFG1, ~(_BIT7 | _BIT6), (GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() << 7));

                    SET_TYPE_C_1_PD_PARTNER_REQ_VOL(0);
                    CLR_TYPE_C_1_PD_SRC_CAP_CNT();

                    SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_WDINT_SEND_CAP);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Active WD Timer Event To Send 1st SRC_CAP, Timeout : Send SRC_CAP.
                    ScalerTimerWDActivateTimerEvent_EXINT0(20, _SCALER_WD_TIMER_EVENT_PD_1_SEND_SRC_CAP);
                }
            }
            else
            {
                // Clear Explicit Power Contract and Flags
                CLR_TYPE_C_1_PD_EXPLICIT_CONTRACT();
                ScalerSetBit_EXINT(P6B_18_VENDOR_SPECIFIC_SOP3_CFG1, ~(_BIT7 | _BIT6), (GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() << 7));

                // Start SinkWaitCapTimer (310~620ms), and Wait SRC_CAP
                SET_TYPE_C_1_PD_WD_TIMER_VALUE(_MAX_WD_EVENT_TIME);
                ScalerTimerWDActivateTimerEvent_EXINT0(_MAX_WD_EVENT_TIME, _SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST);

                SET_TYPE_C_1_PD_FW_STATE(_PD_SNK_INT_WAIT_SRC_CAP);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
                SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
            }

            break;

        case _PD_SRC_READY:
        case _PD_SNK_READY:

            switch(GET_TYPE_C_1_PD_SUB_STATE())
            {
                case _PD_SUB_INT_SEND_SRC_CAP:
                case _PD_SUB_SEND_SRC_CAP:

                    CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_SEND_SRC_CAP);
                    if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (GET_TYPE_C_1_PD_EPR_MODE() == _FALSE))
                    {
                        CLR_TYPE_C_1_PD_SRC_CAP_CNT();
                        SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_INT_WAIT_REQ);
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
                        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                        ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);
                    }
                    else
                    {
                        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                        // Back to Ready State
                        ScalerTypeC1PdBackToReadyState_EXINT0();
                    }

                    break;

                case _PD_SUB_SEND_GET_SRC_CAP:

                    SET_TYPE_C_1_PD_GET_SRC_CAP_SENT();
                    if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
                    {
                        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_SRC_CAP);

                        // Turn On Sender Response Timer 24~30 ms, Wait "Src_Cap" @ INT
                        ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);
                    }
                    else
                    {   // Sink Shoud Transit to Ready State, And Should Rcv. Src_Cap Later
                        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);
                        ScalerTypeC1PdBackToReadyState_EXINT0();
                    }

                    break;

                case _PD_SUB_SEND_GET_SNK_CAP:

                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_SNK_CAP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "Snk_Cap" @ INT
                    ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);

                    break;

                case _PD_SUB_CABLE_PROC:
                case _PD_SUB_SEND_CBL_DP_VDM_REQ:

                    ScalerTypeC1PdIntTxCableReqSuccessProc_EXINT0();

                    break;

                case _PD_SUB_SEND_PR_SWAP:

                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_PRS_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "Snk_Cap" @ INT
                    ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);

                    break;

                case _PD_SUB_INT_SEND_ACCEPT_PRS:

                    // Port Partner Initiates PR_Swap, which Means It Has the Ability to Change the Power Role, so CLR_TYPE_C_1_PD_PRS_REJECT().
                    CLR_TYPE_C_1_PD_PRS_REJECT();

                    // "Accept" Message Has Been Sent Successfully
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_POWER_TRANSITION);

                    if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
                    {
                        // 1. Turn Off Power After 25-35ms
                        ScalerTimerWDActivateTimerEvent_EXINT0(_SRC_ADJUST_POWER_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER);
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_SRC_OFF_PSRDY);
                    }
                    else
                    {
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
                        // 1. Turn Off Sink Power, Disable Detect Sink OVP/UVP
                        ScalerTypeC1PmicSetting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
#endif

                        // 2. Disable TypeC Vbus Detach Detect Function
                        // 3. Disable SNK Detect Rp to Transit from Attached.SNK to Unattached.SNK State
                        ScalerTypeC1CcVbusDetCtrl_EXINT0(_DISABLE);
                        ScalerTypeC1CcSnkDetRpCtrl_EXINT0(_DISABLE);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
                        // [Eizo] SIC437A Customized Power Control : Send Accept to PR Swap as Sink
                        ScalerTypeC1PmicSic437aPRSwapStartProc_EXINT0(_TYPE_C_POWER_SNK);
#endif

                        // PD Merged Test [TEST.PD.PROT.SNK.12]
                        ScalerTypeC1PdActiveTimerEvent_EXINT0(_PS_SRC_OFF_TIMER, _SCALER_TIMER_EVENT_PD_1_TPC_ERROR_RECOVERY);
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_SRC_OFF);
                    }

                    // Accept PR_Swap From Port Partner, Set Flag For Retimer Usage
                    SET_TYPE_C_1_PD_PRS_PROCESSING();

                    break;

                case _PD_SUB_SEND_SRC_OFF_PSRDY:

                    // SRC OFF "PS_RDY" Has Been Sent, Active Timer Event to Wait for SRC ON "PS_RDY"
                    ScalerTypeC1PdActiveTimerEvent_EXINT0(_PS_SRC_ON_TIMER, _SCALER_TIMER_EVENT_PD_1_TPC_ERROR_RECOVERY);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_SRC_ON);

                    break;

                case _PD_SUB_WDINT_SEND_SRC_ON_PSRDY:

                    // Transit to _PE_SRC_START_UP, and Send Soft Reset to Cable
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);
                    SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_START_UP);

                    ScalerTypeC1PdStartUpProc_EXINT0();

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                    if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
                    {
                        CLR_TYPE_C_1_PD_PARTNER_VDM_NO_RESP_CNT();
                        CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();
                        CLR_TYPE_C_1_PD_GET_SRC_CAP_SENT();
                    }
                    else
                    {
                        CLR_TYPE_C_1_PD_VCS_REJECT();
                        CLR_TYPE_C_1_PD_DRS_REJECT();
                        CLR_TYPE_C_1_PD_PRS_REJECT();

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
                        // Set PARTNER_ALT_SUPPORT FLAG to Wait For Port Partner Initiating Alt Mode Flow
                        SET_TYPE_C_1_PD_PARTNER_ALT_SUPPORT();

                        // After PR_SWAP, if Not Enter ALt Mode in 2 Sec After Power Contract, timeout: Clear PARTNER_ALT_SUPPORT Macro
                        ScalerTypeC1PdActiveTimerEvent_EXINT0(_PARTNER_ALT_SUPPORT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_PARTNER_ALT_SUPPORT);
#endif
                    }
#endif

                    break;

                case _PD_SUB_SEND_DR_SWAP:

                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_DRS_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "Snk_Cap" @ INT
                    ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);

                    break;

                case _PD_SUB_INT_SEND_ACCEPT_DRS:

                    // Port Partner Initiates DR_Swap, which Means It Has the Ability to Change the Data Role, so CLR_TYPE_C_1_PD_DRS_REJECT().
                    CLR_TYPE_C_1_PD_DRS_REJECT();

                    if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
                    {
                        // [0x6BE5] Update FW/HW Data Role to UFP
                        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);
                        SET_TYPE_C_1_PD_DATA_ROLE(_PD_DATA_UFP);

                        // Fix Lecroy [COMMON.CHECK.PD.3 Check GoodCRC]
                        ScalerSetBit_EXINT(P6B_3A_RX_CRC_RESPONSE_CTRL, ~(_BIT4), 0x00);

                        // PD 2.0 : Prevent Receiving Cable Message When Data Role is UFP During Explicit Contract
                        if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0)
                        {
                            // [0x6B34] Setup Rx Valid Packet Type (UFP : SOP / Hard Reset)
                            ScalerSetByte_EXINT(P6B_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT0));
                        }

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
                        // Set PARTNER_ALT_SUPPORT FLAG to Wait For Port Partner Initiating Alt Mode Flow
                        SET_TYPE_C_1_PD_PARTNER_ALT_SUPPORT();

                        // DFP DR_SWAP to UFP, if Not Enter ALt Mode in 2 Sec After Power Contract, timeout: Clear PARTNER_ALT_SUPPORT Macro
                        ScalerTypeC1PdActiveTimerEvent_EXINT0(_PARTNER_ALT_SUPPORT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_PARTNER_ALT_SUPPORT);
#endif
                    }
                    else
                    {
                        // [0x6BE5] Update FW/HW Data Role to DFP
                        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, _BIT0);
                        SET_TYPE_C_1_PD_DATA_ROLE(_PD_DATA_DFP);

                        // PD 2.0 : Only DFP && Vconn Source Can Communicate With Cable During Explicit Contract
                        if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) && (GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC))
                        {
                            // [0x6B34] Setup Rx Valid Packet Type (Vconn SRC : SOP / SOP' / SOP" / Hard Reset)
                            ScalerSetByte_EXINT(P6B_34_RX_VALID_MSG_TYPE, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                        }
                    }

                    // DR Swap AMS Finished
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeC1PdBackToReadyState_EXINT0();

                    break;

                case _PD_SUB_SEND_VCONN_SWAP:

                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VCS_RESP);

                    // Turn On Sender Response Timer 24~30 ms, Wait "Snk_Cap" @ INT
                    ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);

                    break;

                case _PD_SUB_INT_SEND_ACCEPT_VCS:

                    // Port Partner Initiates Vconn_Swap, which Means It Has the Ability to Change the Vconn Role, so CLR_TYPE_C_1_PD_VCS_REJECT().
                    CLR_TYPE_C_1_PD_VCS_REJECT();

                    // "Accept" Message Has Been Sent Successfully
                    if(GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VCONN_ON);
                        ScalerTypeC1PdActiveTimerEvent_EXINT0(_WAIT_VCONN_ON_TIMER, _SCALER_TIMER_EVENT_PD_1_SEND_HARD_RST);
                    }
                    else
                    {
                        // Turn On Vconn Power
                        ScalerTypeC1CcVconnControl_EXINT0(_ON);

                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_WDINT_SEND_VCONN_ON_PSRDY);
                        ScalerTimerWDActivateTimerEvent_EXINT0(5, _SCALER_WD_TIMER_EVENT_PD_1_SEND_VCONN_ON_PSRDY);
                    }

                    break;

                case _PD_SUB_WDINT_SEND_VCONN_ON_PSRDY:

                    // Do Soft Reset to Cable When We Become Vconn Src During Enter EPR Mode Flow
                    if(GET_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW() == _TRUE)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_CABLE_PROC);
                        SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_INT_SEND_SOFT_RST);

#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                        // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                        ScalerTypeC1PdUpdateCableRetryCounter_EXINT0();
#endif
                        // Send Soft Reset(SOP') to Reset Cable
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                        ScalerTypeC1PdSendSoftRst_EXINT0(_PD_SOP_P_PKT);
                    }
                    else
                    {
                        // Vconn Swap AMS Finished
                        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                        // Back to Ready State
                        ScalerTypeC1PdBackToReadyState_EXINT0();

                        // Do Soft Reset to Cable After Vconn_Swap Success & We Are Vconn Src
                        SET_TYPE_C_1_PD_CBL_SOFT_RESET_REQUIRED();
                    }

                    // SET Wait Flag, and Set TimerEvent to Clear in 100ms
                    SET_TYPE_C_1_PD_VCS_WAIT_FLAG();
                    ScalerTypeC1PdActiveTimerEvent_EXINT0(_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_VCS_WAIT);

                    break;

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
                case _PD_SUB_SEND_DP_VDM_REQ:

                    ScalerTypeC1PdIntTxDpVdmReqSuccessProc_EXINT0();

                    break;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
                case _PD_SUB_SEND_LENOVO_VDM_REQ:

                    ScalerTypeC1PdIntTxLenovoVdmReqSuccessProc_EXINT0();

                    break;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
                case _PD_SUB_SEND_ACER_VDM_REQ:

                    ScalerTypeC1PdIntTxAcerVdmReqSuccessProc_EXINT0();

                    break;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
                case _PD_SUB_SEND_HP_VDM_REQ:

                    ScalerTypeC1PdIntTxHpVdmReqSuccessProc_EXINT0();

                    break;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
                case _PD_SUB_SEND_DELL_VDM_REQ:

                    ScalerTypeC1PdIntTxDellVdmReqSuccessProc_EXINT0();

                    break;
#endif

                case _PD_SUB_INT_SEND_VDM_RESP:

                    ScalerTypeC1PdIntTxVdmRespSuccessProc_EXINT0();

                    break;
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
                case _PD_SUB_SEND_GET_STATUS:

                    CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_SEND_GET_STATUS_MSG);
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_STATUS);

                    // Turn On Sender Response Timer 24~30 ms, Wait "ACCEPT / REJECT / WAIT" @ INT
                    ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_BACK_TO_READY_STATE);

                    break;

                case _PD_SUB_SEND_ALERT:

                    SET_TYPE_C_1_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_ALERT_EVENT_SUCCESS);
                    CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_ALERT_EVENT);
                    CLR_TYPE_C_1_PD_TYPE_OF_ALERT(_TYPE_C_TYPE_OF_ALERT_ALL);
                    SET_TYPE_C_1_PD_EXT_ALERT_EVENT(_TYPE_C_EXT_ALERT_EVENT_NONE);

                    // Set Macro to Avoid Sending Alert Msg. Repeatedly in ReadyProc()
                    SET_TYPE_C_1_PD_ALERT_SENT();

                    // Set AMS = None
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeC1PdBackToReadyState_EXINT0();

                    break;

                case _PD_SUB_INT_SEND_CHK_TEST_REQ:

                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_CHK_TEST_RESP);

                    break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
                case _PD_SUB_INT_SEND_EPR_ENTER_ACK:

                    // Change Rp to SinkTxNG to Avoid Sink Initiate Message
                    ScalerSetBit_EXINT(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), _PD_SINK_TX_NG);

                    if(GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_WDINT_DISCOVER_CABLE);

                        // Active WD Timer Event For Source Initiate AMS Timer (16-20ms), Timeout : Discover Cable
                        ScalerTimerWDActivateTimerEvent_EXINT0(_SRC_INIT_AMS_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);
                    }
                    else
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_WDINT_SEND_VCONN_SWAP);

                        // Active WD Timer Event For Source Initiate AMS Timer (16-20ms), Timeout : Send Vconn Swap
                        ScalerTimerWDActivateTimerEvent_EXINT0(_SRC_INIT_AMS_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_SEND_VCONN_SWAP);
                    }

                    break;

                case _PD_SUB_INT_SEND_VCONN_SWAP:

                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VCS_RESP);

                    // Active WD Timer Event For Source Sender Response Timer (24~30 ms), Timeout : Send Entry Failed
                    ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_ENTER_FAILED);

                    break;

                case _PD_SUB_INT_SEND_EPR_ENTER_FAILED:

                    // Clear Enter EPR Mode Flow Flag
                    CLR_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW();

                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeC1PdBackToReadyState_EXINT0();

                    break;

                case _PD_SUB_INT_SEND_EPR_ENTER_SUCCESSFUL:

                    // Clear Enter EPR Mode Flow Flag
                    CLR_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW();

                    // Set EPR Mode Flag
                    SET_TYPE_C_1_PD_EPR_MODE();

                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_WDINT_SEND_EPR_SRC_CAP);

                    // Active WD Timer Event To Send EPR_SRC_CAP, Timeout : Send EPR_SRC_CAP.
                    ScalerTimerWDActivateTimerEvent_EXINT0(20, _SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_SRC_CAP);

                    break;

                case _PD_SUB_INT_SEND_EPR_SRC_CAP:
                case _PD_SUB_SEND_EPR_SRC_CAP:

                    if((GET_TYPE_C_1_PD_TX_CHUNKED_MESSAGE() == _TRUE) && (GET_TYPE_C_1_PD_TX_CHUNK_NUMBER() == 0))
                    {
                        // Wait for Chunk Request with Chunk Number = 1 before Sending Chunk 1
                        ADD_TYPE_C_1_PD_TX_CHUNK_NUMBER();
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_EPR_SRC_CAP_CHUNK_REQ);
                        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                        // Active WD Timer Event For Chunk Sender Req. Timer (24-30ms), Timeout : Soft Reset
                        ScalerTimerWDActivateTimerEvent_EXINT0(_CHUNK_SENDER_REQ_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CHUNK_SENDER_REQ_TIMEOUT);
                    }
                    else
                    {
                        // Chunk 1 has been Sent Successfully
                        CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_SEND_SRC_CAP);

                        if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (GET_TYPE_C_1_PD_EPR_MODE() == _TRUE))
                        {
                            SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_INT_WAIT_EPR_REQ);
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NON_INTERRUPTIBLE);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Hard Reset
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);
                        }
                        else
                        {
                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                        }
                    }

                    break;

                case _PD_SUB_INT_SEND_EPR_KEEP_ALIVE_ACK:

                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeC1PdBackToReadyState_EXINT0();

                    break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

                case _PD_SUB_INT_SEND_SNK_CAP:
                case _PD_SUB_INT_SEND_REJECT:
                case _PD_SUB_INT_SEND_WAIT:
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
                case _PD_SUB_INT_SEND_NOT_SUPPORT:
                case _PD_SUB_INT_SEND_SRC_CAP_EXT:
                case _PD_SUB_INT_SEND_SNK_CAP_EXT:
                case _PD_SUB_INT_SEND_MFC_INFO:
                case _PD_SUB_INT_SEND_PPS_STATUS:
                case _PD_SUB_INT_SEND_REVISION:
#endif
                    // Set AMS = None
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeC1PdBackToReadyState_EXINT0();

                    break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
                case _PD_SUB_INT_SEND_STATUS:

                    // Set AMS = None
                    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                    // Back to Ready State
                    ScalerTypeC1PdBackToReadyState_EXINT0();

                    break;
#endif

                default:

                    break;
            } // End of switch(GET_TYPE_C_1_PD_SUB_STATE())

            break;

        default:

            break;
    } // End of switch(GET_TYPE_C_1_PD_FW_STATE())
}

//--------------------------------------------------
// Description  : Process When Tx Transmission Retry Fail in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntTxFailProc_EXINT0(void)
{
    switch(GET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT())
    {
        case _PD_TX_RETRY_FAIL_BY_STATE:

            switch(GET_TYPE_C_1_PD_FW_STATE())
            {
                case _PD_INT_SEND_CBL_DISCOVER_ID:
                case _PD_INT_SEND_CBL_SOFT_RESET:

                    ScalerTypeC1PdIntTxCableReqFailProc_EXINT0();

                    break;

                case _PD_SRC_INT_SEND_CAP:

                    ADD_TYPE_C_1_PD_SRC_CAP_CNT();
                    // Check if Source Capability is sent More than Difined Max Times
                    if(GET_TYPE_C_1_PD_SRC_CAP_CNT() > _MAX_SRC_CAP_CNT)
                    {
                        // Transit to PD No-Response, and Disable Rcv Msg. INT
                        SET_TYPE_C_1_PD_FW_STATE(_PD_NO_RESPONSE);
                        ScalerTypeC1PdRxIntControl_EXINT0(_DISABLE);
                    }
                    else
                    {
#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
                        // Source does not receive Src_Cap response in 400ms, Set Flag for U3 Function Enable (S4 Only)
                        if(GET_TYPE_C_1_PD_SRC_CAP_CNT() == 5)
                        {
                            ScalerUsb3RepeaterMacSetPdNoResponse(ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1));
                        }
#endif

                        // Wait 120ms and Send Re-Src_Cap
                        ScalerTimerWDActivateTimerEvent_EXINT0(120, _SCALER_WD_TIMER_EVENT_PD_1_SEND_SRC_CAP);
                    }

                    break;

                case _PD_SRC_READY:
                case _PD_SNK_READY:

                    if((GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_CABLE_PROC) || (GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SEND_CBL_DP_VDM_REQ))
                    {
                        ScalerTypeC1PdIntTxCableReqFailProc_EXINT0();
                    }

                    if(GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SEND_ALERT)
                    {
                        // Set AMS = None
                        SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

                        // Back to Ready State
                        ScalerTypeC1PdBackToReadyState_EXINT0();

                        SET_TYPE_C_1_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_ALERT_EVENT_FAILED);
                        CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_ALERT_EVENT);
                        CLR_TYPE_C_1_PD_TYPE_OF_ALERT(_TYPE_C_TYPE_OF_ALERT_ALL);
                        SET_TYPE_C_1_PD_EXT_ALERT_EVENT(_TYPE_C_EXT_ALERT_EVENT_NONE);
                    }

                    break;

                default:

                    break;
            }

            break;

        case _PD_TX_RETRY_FAIL_ERROR_RECOVERY:

            SET_TYPE_C_1_CC_ERROR_RECOVERY();

            break;

        case _PD_TX_RETRY_FAIL_SOFT_RESET:

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
            if(GET_TYPE_C_1_PD_DELL_ALT_MODE_STATE() == _PD_ALT_MODE_SEND_DELL_ATTEN)
            {
                // Clear Dell Related Macros and Set Atten_NoResponse System Event
                CLR_TYPE_C_1_PD_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ATTEN);
                CLR_TYPE_C_1_PD_DELL_ATTEN_RETRY_CNT();
                CLR_TYPE_C_1_PD_DELL_ATTEN_WAIT();
                SET_TYPE_C_1_PD_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_NORESPONSE);
                SET_TYPE_C_1_PD_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
            }
#endif

            // Clear Enter EPR Mode Flow Flag
            CLR_TYPE_C_1_PD_ENTER_EPR_MODE_FLOW();

            if(GET_TYPE_C_1_PD_FORCE_HPD_IRQ() == _TRUE)
            {
                CLR_TYPE_C_1_PD_FORCE_HPD_IRQ();

                // Push HPD_IRQ into HPD Queue When Force Sending HPD IRQ Retry Failed, then PD will Re-Send HPD_IRQ in Main loop
                ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_IRQ, 0);
            }

            SET_TYPE_C_1_PD_FW_STATE(_PD_INT_SEND_SOFTRESET);
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_HARD_RESET);
            ScalerTypeC1PdSendSoftRst_EXINT0(_PD_SOP_PKT);

            break;

        case _PD_TX_RETRY_FAIL_HARD_RESET:

            ScalerTypeC1PdSendHardRst_EXINT0();

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process When Tx Transmit Cable Request Success in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntTxCableReqSuccessProc_EXINT0(void)
{
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
    // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
    ScalerTypeC1PdUpdatePortPartnerRetryCounter_EXINT0();
#endif

    switch(GET_TYPE_C_1_PD_FW_STATE())
    {
        case _PD_INT_SEND_CBL_DISCOVER_ID:

            SET_TYPE_C_1_PD_FW_STATE(_PD_INT_WAIT_CBL_DISCOVER_ID_RESP);
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);

            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Send Src_Cap
            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

            break;

        case _PD_INT_SEND_CBL_SOFT_RESET:

            SET_TYPE_C_1_PD_FW_STATE(_PD_INT_WAIT_CBL_SOFT_RESET_RESP);
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);

            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Send Discover ID(SOP')
            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

            break;

        case _PD_SRC_READY:
        case _PD_SNK_READY:

            switch(GET_TYPE_C_1_PD_SUB_STATE())
            {
                case _PD_SUB_CABLE_PROC:

                    switch(GET_TYPE_C_1_PD_CBL_STATE())
                    {
                        case _PD_CBL_SEND_SOFT_RST:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_INT_WAIT_SOFT_RST_RESP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Back to Ready State
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_CBL_SEND_DISCOVER_ID:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_INT_WAIT_DISCOVER_ID_RESP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Back to Ready State
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_CBL_INT_SEND_SOFT_RST:

                            SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_INT_WAIT_SOFT_RST_RESP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Send Entry Failed
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_CBL_INT_SEND_DISCOVER_ID:

                            SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_INT_WAIT_DISCOVER_ID_RESP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Send Entry Failed
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        default:

                            break;
                    }

                    break;

#if((_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))
                case _PD_SUB_SEND_CBL_DP_VDM_REQ:

                    switch(GET_TYPE_C_1_PD_DP_ALT_STATE())
                    {
                        case _PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Discover ID
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Discover SVID
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DP_DISCOVER_MODE_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Discover DP Mode
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_TBT3_DISCOVER_MODE_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Discover TBT3 Mode
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_P:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Enter DP Mode
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_PP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Enter DP Mode
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send DP Config
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_PP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send DP Config
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_P);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Exit DP Mode
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP:

                            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_PP);

                            // Active WD Timer Event For Sender Resp. Timer (24-30ms), Timeout : Re-Send Exit DP Mode
                            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

                            break;

                        default:

                            break;
                    }

                    break;
#endif  // End of #if((_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))

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
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntTxCableReqFailProc_EXINT0(void)
{
    // Update PR/DR/Spec Version In Msg Header For SOP Communication.
    ScalerTypeC1PdUpdateTxFifoMsgHeader_EXINT0();

#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
    // Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
    ScalerTypeC1PdUpdatePortPartnerRetryCounter_EXINT0();
#endif

    switch(GET_TYPE_C_1_PD_FW_STATE())
    {
        case _PD_INT_SEND_CBL_DISCOVER_ID:

            ADD_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT();

            // If Retry Fail, Set FW State to Continue On-going PD Flow
            SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_WDINT_SEND_CAP);

            // Active WD Timer Event To Check Vbus, Then Start PMIC Protection and Send SRC_CAP if VbusSafe5V
            ScalerTimerWDActivateTimerEvent_EXINT0(20, _SCALER_WD_TIMER_EVENT_PD_1_CHECK_VBUS);

            break;

        case _PD_INT_SEND_CBL_SOFT_RESET:

            SET_TYPE_C_1_PD_FW_STATE(_PD_WDINT_SEND_CBL_DISCOVER_ID);

            // Active WD Timer Event to Send Discover ID (SOP')
            ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_PD_1_CBL_TIMEOUT);

            break;

        case _PD_SRC_READY:
        case _PD_SNK_READY:

            switch(GET_TYPE_C_1_PD_SUB_STATE())
            {
                case _PD_SUB_CABLE_PROC:

                    switch(GET_TYPE_C_1_PD_CBL_STATE())
                    {
                        case _PD_CBL_SEND_SOFT_RST:

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_STATE_NONE);

                            break;

                        case _PD_CBL_SEND_DISCOVER_ID:

                            ADD_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT();

#if(_DISCOVER_ID_NO_RETRY == _TRUE)
                            if(GET_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT() >= _MAX_HW_NO_RETRY_CBL_DISCOVER_ID_RETRY_FAIL_CNT)
#else
                            if(GET_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT() >= _MAX_HW_RETRY_CBL_DISCOVER_ID_RETRY_FAIL_CNT)
#endif
                            {
                                SET_TYPE_C_1_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();
                            SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_STATE_NONE);

                            break;

                        case _PD_CBL_INT_SEND_SOFT_RST:

                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);
                            SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_STATE_NONE);

                            // Send Enter Failed : Cable Not Support EPR Mode
                            SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                            SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_CABLE_NOT_EPR_CAP);
                            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);

                            break;

                        case _PD_CBL_INT_SEND_DISCOVER_ID:

                            ADD_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT();

#if(_DISCOVER_ID_NO_RETRY == _TRUE)
                            if(GET_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT() >= _MAX_HW_NO_RETRY_CBL_DISCOVER_ID_RETRY_FAIL_CNT)
#else
                            if(GET_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT() >= _MAX_HW_RETRY_CBL_DISCOVER_ID_RETRY_FAIL_CNT)
#endif
                            {
                                SET_TYPE_C_1_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);
                            }

                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_EPR_ENTER_FAILED);
                            SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_STATE_NONE);

                            // Send Enter Failed : Cable Not Support EPR Mode
                            SET_TYPE_C_1_PD_EPR_MODE_ACTION(_PD_EPR_MODE_ENTER_FAILED);
                            SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_CABLE_NOT_EPR_CAP);
                            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                            ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_EPR_MODE, _PD_VDM_CMD_RESERVED);

                            break;

                        default:

                            break;
                    }

                    break;

#if((_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))
                case _PD_SUB_SEND_CBL_DP_VDM_REQ:

                    switch(GET_TYPE_C_1_PD_DP_ALT_STATE())
                    {
                        case _PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P:

                            ADD_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT();

#if(_DISCOVER_ID_NO_RETRY == _TRUE)
                            if(GET_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT() >= _MAX_HW_NO_RETRY_CBL_DISCOVER_ID_RETRY_FAIL_CNT)
#else
                            if(GET_TYPE_C_1_PD_CBL_DISCOVER_ID_RETRY_FAIL_CNT() >= _MAX_HW_RETRY_CBL_DISCOVER_ID_RETRY_FAIL_CNT)
#endif
                            {
                                SET_TYPE_C_1_PD_CBL_PD_CAPABILITY(_TYPE_C_CABLE_NON_PD_CAPABLE);

                                // If No VDO Received, Set Passive Cable & HBR3 According to DPAM2.1
                                SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_PASSIVE);
                                SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_HBR3);

                                // Stop Enter DP Alt Mode Flow Just for Cable
                                CLR_TYPE_C_1_PD_CBL_ENTER_DP_MODE_SUPPORT();
                                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);
                            }

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();

                            break;

                        case _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P:

                            // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No GoodCRC of Discover Svid(SOP' / SOP'') Received
                            SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableDpFunctionality_EXINT0());

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();

                            break;

                        case _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P:

                            // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No GoodCRC of DP Discover Mode(SOP' / SOP'') Received
                            SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableDpFunctionality_EXINT0());

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();

                            break;

                        case _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P:

                            // Switch DP_ALT_STATE by Judging DP Functionality Support Of Cable When No GoodCRC of TBT3 Discover Mode(SOP' / SOP'') Received
                            SET_TYPE_C_1_PD_DP_ALT_STATE(ScalerTypeC1PdJudgeCableDpFunctionality_EXINT0());

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();

                            break;

                        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_P:
                        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP:

                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ENTER_MODE);

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();

                            break;

                        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P:
                        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP:

                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DP_CONFIG);

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();

                            break;

                        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P:
                        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP:

                            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_EXIT_MODE);

                            // Back to Ready State
                            ScalerTypeC1PdBackToReadyState_EXINT0();

                            break;

                        default:

                            break;
                    }

                    break;
#endif  // End of #if((_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON) && (_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON) && (_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1))

                default:

                    break;
            }

            break;

        default:

            break;
    }
}

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process When Tx Transmit Dp VDM Request Msg Success in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntTxDpVdmReqSuccessProc_EXINT0(void)
{
    switch(GET_TYPE_C_1_PD_DP_ALT_STATE())
    {
        case _PD_ALT_MODE_SEND_DISCOVER_ID:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DISCOVER_ID
            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_SVID:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DISCOVER_SVID
            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_MODE:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DISCOVER_MODE_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DISCOVER_MODE
            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_ENTER_MODE:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP);

            // Start VDMModeEntryTimer (40-50ms), Timeout : back to Sub SRC/SNK Ready and Re-Send ENTER_MODE
            ScalerTimerWDActivateTimerEvent_EXINT0(_VDM_MODE_ENTRY_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_DP_STATUS:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DP_STATUS_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DP_STATUS
            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_DP_CONFIG:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DP_CONFIG
            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_READY:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);

            // Start Sender Resp. Timer (24-30ms), Timeout : back to Sub SRC/SNK Ready and Re-Send DP_STATUS
            ScalerTimerWDActivateTimerEvent_EXINT0((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) ? _PD2_SENDER_RESP_TIMER : _PD3_SENDER_RESP_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_EXIT_MODE:

            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_INTERRUPTIBLE);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_WAIT_VDM_RESP);
            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP);

            // Start VDMModeExitTimer (40-50ms), Timeout : back to Sub SRC/SNK Ready and Re-Send EXIT_MODE
            ScalerTimerWDActivateTimerEvent_EXINT0(_VDM_MODE_EXIT_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT);

            break;

        case _PD_ALT_MODE_SEND_ATTENTION:

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
            if(GET_TYPE_C_1_PD_FORCE_HPD_IRQ() == _TRUE)
            {
                CLR_TYPE_C_1_PD_FORCE_HPD_IRQ();
            }
            else
            {
                // Set WAIT FLAG to Prevent from Sending Attention in HPD Space Time
                if(GET_TYPE_C_1_PD_HPD_SPACE_TIME(GET_TYPE_C_1_PD_HPD_RPTR()) != 0)
                {
                    SET_TYPE_C_1_PD_ATTENTION_WAIT();
                    ScalerTypeC1PdActiveTimerEvent_EXINT0(GET_TYPE_C_1_PD_HPD_SPACE_TIME(GET_TYPE_C_1_PD_HPD_RPTR()), _SCALER_TIMER_EVENT_PD_1_CLR_ATTENTION_WAIT);
                }

                // Pop Out One HPD From Queue
                ScalerTypeC1PdPopHpd_EXINT0();
            }

            // Set AMS = None
            SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

            // Back to Ready State
            ScalerTypeC1PdBackToReadyState_EXINT0();
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

            break;

        default:

            break;
    }
}
#endif  // End of #if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : Process When Tx Transmit Lenovo VDM Request Msg Success in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntTxLenovoVdmReqSuccessProc_EXINT0(void)
{
    switch(GET_TYPE_C_1_PD_LENOVO_ALT_STATE())
    {
        case _PD_ALT_MODE_SEND_ATTENTION:

            SET_TYPE_C_1_PD_LENOVO_ATTN_SENT_FLAG();
            ADD_TYPE_C_1_PD_LENOVO_ATTN_CNT();

            // Wait 300ms and Re-Send Lenovo Attention
            ScalerTypeC1PdActiveTimerEvent_EXINT0(300, _SCALER_TIMER_EVENT_PD_1_LENOVO_RESP_TIMEOUT);

            // Back to Ready State (FW_STATE / SUB_STATE = SRC/SNK_READY)
            ScalerTypeC1PdBackToReadyState_EXINT0();
            SET_TYPE_C_1_PD_LENOVO_ALT_STATE(_PD_ALT_MODE_NONE);

            break;

        case _PD_ALT_MODE_SEND_LENOVO_GET_STATUS:

            CLR_TYPE_C_1_PD_LENOVO_ATTN_CNT();
            CLR_TYPE_C_1_PD_LENOVO_DOCK_EVENT();

            // Back to Ready State (FW_STATE / SUB_STATE = SRC/SNK_READY)
            ScalerTypeC1PdBackToReadyState_EXINT0();
            SET_TYPE_C_1_PD_LENOVO_ALT_STATE(_PD_ALT_MODE_NONE);

            break;

        default:

            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : Process When Tx Transmit Acer VDM Request Msg Success in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntTxAcerVdmReqSuccessProc_EXINT0(void)
{
    switch(GET_TYPE_C_1_PD_ACER_ALT_MODE_STATE())
    {
        case _PD_ALT_MODE_SEND_ATTENTION:

            // Clear Attention Event Once Message Has Been Sent
            CLR_TYPE_C_1_PD_ACER_USER_EVENT(_TYPE_C_ACER_USER_EVENT_ATTENTION);

            // Back to Ready State (FW_STATE / SUB_STATE = SRC/SNK_READY)
            ScalerTypeC1PdBackToReadyState_EXINT0();
            SET_TYPE_C_1_PD_ACER_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

            break;

        default:

            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : Process When Tx Transmit Hp VDM Request Msg Success in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntTxHpVdmReqSuccessProc_EXINT0(void)
{
    switch(GET_TYPE_C_1_PD_HP_ALT_MODE_STATE())
    {
        case _PD_ALT_MODE_SEND_HP_ATTEN_CONFIG:

            // Clear Attention Event Once Message Has Been Sent
            CLR_TYPE_C_1_PD_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTEN_CONFIG);

            // Back to Ready State (FW_STATE / SUB_STATE = SRC/SNK_READY)
            ScalerTypeC1PdBackToReadyState_EXINT0();
            SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

            break;

        case _PD_ALT_MODE_SEND_HP_ATTEN_VWIRE:

            // Clear Attention Event Once Message Has Been Sent
            CLR_TYPE_C_1_PD_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTEN_VWIRE);

            // Back to Ready State (FW_STATE / SUB_STATE = SRC/SNK_READY)
            ScalerTypeC1PdBackToReadyState_EXINT0();
            SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

            break;

        case _PD_ALT_MODE_SEND_HP_ATTEN_DATA:

            // Clear Attention Event Once Message Has Been Sent
            CLR_TYPE_C_1_PD_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTEN_DATA);

            // Back to Ready State (FW_STATE / SUB_STATE = SRC/SNK_READY)
            ScalerTypeC1PdBackToReadyState_EXINT0();
            SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

            break;

        default:

            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : Process When Tx Transmit Dell VDM Request Msg Success in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntTxDellVdmReqSuccessProc_EXINT0(void)
{
    switch(GET_TYPE_C_1_PD_DELL_ALT_MODE_STATE())
    {
        case _PD_ALT_MODE_SEND_DELL_ATTEN:

            // Back to Ready State (FW_STATE / SUB_STATE = SRC/SNK_READY)
            ScalerTypeC1PdBackToReadyState_EXINT0();
            SET_TYPE_C_1_PD_DELL_ALT_MODE_STATE(_PD_ALT_MODE_INT_WAIT_DELL_0X13);

            // Active WD Timer Event For Dell Attention Retry Timer (30ms), Timeout : ADD_TYPE_C_1_PD_DELL_ATTEN_RETRY_CNT()
            ScalerTimerWDActivateTimerEvent_EXINT0(_TYPE_C_EMB_DELL_ALT_MODE_ATTEN_RETRY_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_DELL_ATTEN_RETRY);

            break;

        default:

            break;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)

//--------------------------------------------------
// Description  : Process When Tx Transmit VDM Response Msg Success in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdIntTxVdmRespSuccessProc_EXINT0(void)
{
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1);
    enumTypeCPcbPort = enumTypeCPcbPort;

    if(GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID)
    {
        switch(GET_TYPE_C_1_PD_DP_ALT_STATE())
        {
            case _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK:

                // Set Enter Mode Flag
                SET_TYPE_C_1_PD_DP_ALT_MODE_ENTER();

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                if(GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_USB_CONFIG)
                {
                    // Push _PD_HPD_LOW into HPD_Queue
                    ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_LOW, 0);
                }
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                // Clear HPD Queue
                ScalerTypeC1PdClrHpd_EXINT0();
#endif

                break;

            case _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK:

                // For DC_OFF Option = Charge Function Only
                if(GET_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
                {
                    // Disable Alt. Mode Resp When DC_OFF
                    CLR_TYPE_C_1_PD_ALT_MODE_FUNCTION();

                    // Clear Exit Mode Request
                    CLR_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ();
                }

                // Clear Alt. Mode Status
                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_NONE);
                CLR_TYPE_C_1_PD_DP_ALT_MODE_ENTER();
                SET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG(_PD_USB_CONFIG);
                CLR_TYPE_C_1_PD_PARTNER_INIT_ALT_MODE();

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                ScalerDpAuxRxHpdTogglePhyResetProc(ScalerTypeCPcbPortConvertToDx_EXINT0(enumTypeCPcbPort), _LOW);
                SET_TYPE_C_1_PD_HPD_STATUS(_LOW);
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_LOW, 0);
#endif

                break;

            case _PD_ALT_MODE_INT_SEND_DP_STATUS_ACK:

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                // "DP Status Ack" Only Access HPD Queue when (HPD Count > 0) & (Not Attn Wait)
                if((GET_TYPE_C_1_PD_HPD_CNT() > 0) && (GET_TYPE_C_1_PD_ATTENTION_WAIT() == _FALSE))
                {
                    // Set WAIT FLAG to Prevent from Sending Attention in HPD Space Time
                    if(GET_TYPE_C_1_PD_HPD_SPACE_TIME(GET_TYPE_C_1_PD_HPD_RPTR()) != 0)
                    {
                        SET_TYPE_C_1_PD_ATTENTION_WAIT();
                        ScalerTypeC1PdActiveTimerEvent_EXINT0(GET_TYPE_C_1_PD_HPD_SPACE_TIME(GET_TYPE_C_1_PD_HPD_RPTR()), _SCALER_TIMER_EVENT_PD_1_CLR_ATTENTION_WAIT);
                    }

                    // Pop Out One HPD From Queue
                    ScalerTypeC1PdPopHpd_EXINT0();
                }
#endif

                break;

            case _PD_ALT_MODE_INT_SEND_DP_CONFIG_ACK:

                if(GET_TYPE_C_1_PD_PIN_ASSIGNMENT() == _TYPE_C_PIN_ASSIGNMENT_NONE)
                {
                    SET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG(_PD_USB_CONFIG);
                }
                else
                {
                    CLR_TYPE_C_1_PD_DP_ALT_MODE_WAIT_CONFIG();
                    SET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG(_PD_DP_CONFIG);

                    // If in DP Config, Clear Partner Initial Alt Mode Macro
                    CLR_TYPE_C_1_PD_PARTNER_INIT_ALT_MODE();

                    // Clear VDM Response Conflict Cnt and Cancel TimerEvent
                    CLR_TYPE_C_1_PD_VDM_RESP_CONFLICT_CNT();
                    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_VDM_RESP_CONFLICT_TIMEOUT);

                    // Cancel CLR_PARTNER_ALT_SUPPORT TimerEvent When Already Dp Config
                    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_CLR_PARTNER_ALT_SUPPORT);

                    // Cancel _T480_ERROR_RECOVERY TimerEvent When Already Dp Config
                    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_T480_ERROR_RECOVERY);

                    if(((GET_TYPE_C_1_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_1_VDM_RESP_CONFLICT_TIMEOUT) || (GET_TYPE_C_1_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_1_CLR_PARTNER_ALT_SUPPORT) || (GET_TYPE_C_1_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_1_T480_ERROR_RECOVERY)) && (GET_TYPE_C_1_PD_TIMER_EVENT_VALID() == _TRUE))
                    {
                        CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();
                    }

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
                    if(GET_TYPE_C_1_PD_DELL_ALT_MODE_ENTER() == _FALSE)
                    {
                        CLR_TYPE_C_1_PD_DELL_AM_ENTER_TIMEOUT();

                        // Active WD Timer Event For Enter_Dell_Alt_Mode Timer (30ms), Timeout : SET_TYPE_C_1_PD_DELL_AM_ENTER_TIMEOUT()
                        ScalerTimerWDActivateTimerEvent_EXINT0(_TYPE_C_EMB_DELL_ALT_MODE_ENTER_TIMEOUT_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_DELL_AM_ENTER_TIMEOUT);
                    }
#endif
                }

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
    if(GET_TYPE_C_1_PD_VDM_SVID() == _LENOVO_VID)
    {
        switch(GET_TYPE_C_1_PD_LENOVO_ALT_STATE())
        {
            case _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK:

                // Set Enter Mode Flag
                SET_TYPE_C_1_PD_LENOVO_ALT_MODE_ENTER();

                break;

            case _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK:

                // Clear HP Alt. Mode Status
                SET_TYPE_C_1_PD_LENOVO_ALT_STATE(_PD_ALT_MODE_NONE);
                CLR_TYPE_C_1_PD_LENOVO_ALT_MODE_ENTER();

                break;

            case _PD_ALT_MODE_INT_SEND_LENOVO_GET_STATUS_ACK:

                CLR_TYPE_C_1_PD_LENOVO_DOCK_EVENT();

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
    if(GET_TYPE_C_1_PD_VDM_SVID() == _ACER_VID)
    {
        switch(GET_TYPE_C_1_PD_ACER_ALT_MODE_STATE())
        {
            case _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK:

                // Set Enter Mode Flag
                SET_TYPE_C_1_PD_ACER_ALT_MODE_ENTER();

                break;

            case _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK:

                // Clear Acer Alt. Mode Status
                SET_TYPE_C_1_PD_ACER_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
                CLR_TYPE_C_1_PD_ACER_ALT_MODE_ENTER();

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
    if(GET_TYPE_C_1_PD_VDM_SVID() == _HP_VID)
    {
        switch(GET_TYPE_C_1_PD_HP_ALT_MODE_STATE())
        {
            case _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK:

                // Set Enter Mode Flag
                SET_TYPE_C_1_PD_HP_ALT_MODE_ENTER();

                break;

            case _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK:

                // Clear HP Alt. Mode Status
                SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
                CLR_TYPE_C_1_PD_HP_ALT_MODE_ENTER();

                break;

            case _PD_ALT_MODE_INT_SEND_HP_SET_CONFIG_ACK:

                // Set Atten_config User Event and Clear Retry CNT
                SET_TYPE_C_1_PD_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTEN_CONFIG);
                CLR_TYPE_C_1_PD_HP_ATTEN_RETRY_CNT();

                break;

            case _PD_ALT_MODE_SEND_HP_SET_VWIRE_SAMPLE_ACK:

                // Clear User Event Once Message Has Been Sent
                CLR_TYPE_C_1_PD_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_SET_VWIRE_SAMPLE_ACK);

                // Back to Ready State (FW_STATE / SUB_STATE = SRC/SNK_READY)
                ScalerTypeC1PdBackToReadyState_EXINT0();
                SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    if(GET_TYPE_C_1_PD_VDM_SVID() == _DELL_VID)
    {
        switch(GET_TYPE_C_1_PD_DELL_ALT_MODE_STATE())
        {
            case _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK:

                // Set Enter Mode Flag
                SET_TYPE_C_1_PD_DELL_ALT_MODE_ENTER();

                break;

            case _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK:

                // Clear Dell Alt. Mode Status
                SET_TYPE_C_1_PD_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
                CLR_TYPE_C_1_PD_DELL_ALT_MODE_ENTER();
                SET_TYPE_C_1_PD_DELL_AM_ENTER_TIMEOUT();

                break;

            case _PD_ALT_MODE_INT_SEND_DELL_0X12_ACK:

                // Clear Dell Alt. Mode Status
                SET_TYPE_C_1_PD_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)

    // Set AMS = None
    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);

    // Back to Ready State
    ScalerTypeC1PdBackToReadyState_EXINT0();
}
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Set Flag & Time in Interrupt For Main Loop to Active Timer Event
// Input Value  : enumEventID : Timer Event / usTime : Timeout Time
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdActiveTimerEvent_EXINT0(WORD usTime, EnumScalerTimerEventID enumEventID)
{
    SET_TYPE_C_1_PD_TIMER_EVENT_ID(enumEventID);
    SET_TYPE_C_1_PD_TIMER_EVENT_CNT(usTime);
    SET_TYPE_C_1_PD_TIMER_EVENT_VALID();
}

//--------------------------------------------------
// Description  : Send Power Delivery Message in Interrupt
// Input Value  : enumPacketType : _PD_SOP_PKT
//                enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REQUEST / _PD_CMD_SRC_CAP / _PD_CMD_VDM ...
//                enumVdmCmd : _PD_VDM_CMD_DISCOVER_ID_ACK / _PD_VDM_CMD_DISCOVER_ID_NAK ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSendMsg_EXINT0(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    // 1. Clear Flags
    CLR_TYPE_C_1_PD_TRANSMIT_RESULT();

    // 2. Construct Msg.
    ScalerTypeC1PdConstructMsg_EXINT0(enumPacketType, enumPdCmd, enumVdmCmd);

    // Start Disable Rcv Msg.
    ScalerTypeC1PdRxIntControl_EXINT0(_DISABLE);

    // 3. Send Msg. (Interrupt Does Not Check Overwrite and Disable Rcv Msg.)
    // [0x6BDC] Clear IRQs
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
    ScalerSetBit_EXINT(P6B_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
    ScalerSetBit_EXINT(P6B_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

    // [0x6BDD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
    ScalerSetBit_EXINT(P6B_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

    // [0x6BDA] Start Transmit ([1] = 0, Wait For GoodCRC Response After Transmission)
    ScalerSetBit_EXINT(P6B_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

    // [0x6BE5] Set Tx FIFO [2:1] Spec Ver = 2.0, For PD2.0/3.0 CTS
    ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (_BIT1));
}

//--------------------------------------------------
// Description  : Construct Power Delivery Message in Interrupt
// Input Value  : enumPacketType : _PD_SOP_PKT
//                enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REQUEST / _PD_CMD_SRC_CAP / _PD_CMD_VDM ...
//                enumVdmCmd : _PD_VDM_CMD_DISCOVER_ID_ACK / _PD_VDM_CMD_DISCOVER_ID_NAK ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdConstructMsg_EXINT0(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucExtendedBit_EXINT = 0;
    BYTE ucDataObjectCnt_EXINT = 0;

    // 1. [0x6BE9-EA] Set Up Number of Data Objects(Data Blocks) if Needed
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

            ucDataObjectCnt_EXINT = 0;
            break;

        // Data Message Has Different Num of Data Objects According to Different Message
        case _PD_CMD_SRC_CAP:

            ucDataObjectCnt_EXINT = GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT();

#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
            // Do not send PPS PDO when the Spec Version is PD2.0 or not support PPS
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0)
#endif
            {
                for(BYTE ucLoopIndex = GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1; ucLoopIndex > 0; ucLoopIndex--)
                {
                    if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
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

            ucDataObjectCnt_EXINT = GET_TYPE_C_1_PD_SPR_SNK_PDO_CNT();
            break;

        case _PD_CMD_VDM:

            ucDataObjectCnt_EXINT = ScalerTypeC1PdSetVdmDataObjCnt_EXINT0(enumVdmCmd);
            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_BAT_STATUS:        // Not Implemented
        case _PD_CMD_ALERT:
        case _PD_CMD_GET_COUNTRY_INFO:  // Not Implemented
        case _PD_CMD_REVISION:

            ucDataObjectCnt_EXINT = 1;

            break;

        // Extended Message Has Different Num Data Obj. According to Different Message
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

            if(GET_TYPE_C_1_PD_CHUNK_REQUEST() == _TRUE)
            {
                ucExtendedBit_EXINT = 1;
                ucDataObjectCnt_EXINT = 1;
            }

            break;

        case _PD_CMD_PPS_STATUS:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 2;

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        case _PD_CMD_EPR_MODE:

            ucDataObjectCnt_EXINT = 1;

            break;

        case _PD_CMD_EPR_SRC_CAP:

            ucExtendedBit_EXINT = 1;

            if((GET_TYPE_C_1_PD_EPR_SRC_PDO_CNT() == 0) && (GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() < 7))
            {
                // If Only SPR PDO and PDO Count < 7, Do Not Use Chunked to Send EPR Source Cap
                // Data Object = SPR PDO Count + 1 (Extended Header)
                ucDataObjectCnt_EXINT = GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() + 1;

                CLR_TYPE_C_1_PD_TX_CHUNKED_MESSAGE();
            }
            else
            {
                // If PDO Count > 7, Use Chunked to Send EPR Source Cap
                if(GET_TYPE_C_1_PD_TX_CHUNK_NUMBER() == 0)
                {
                    // Chunk 0 : Data Object = 7
                    ucDataObjectCnt_EXINT = 7;

                    SET_TYPE_C_1_PD_TX_CHUNKED_MESSAGE();
                }
                else
                {
                    // Chunk 1 : Data Object = EPR PDO Count + 1 (Extended Header)
                    ucDataObjectCnt_EXINT = GET_TYPE_C_1_PD_EPR_SRC_PDO_CNT() + 1;
                }
            }

            break;

        case _PD_CMD_EXTENDED_CONTROL:

            ucExtendedBit_EXINT = 1;
            ucDataObjectCnt_EXINT = 1;

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)

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

            ucDataObjectCnt_EXINT = 0;
            break;
    }

    // 2. Construct Data Object into Tx FIFO, if Number of Data Object is not 0
    if(ucDataObjectCnt_EXINT != 0)
    {
        ScalerTypeC1PdConstructDataObj_EXINT0(enumPacketType, enumPdCmd, enumVdmCmd);
    }

    // 3. Start to Fill Packet Type, Msg. Header & Data Object
    // [0x6BE0] Select Transmission Mode [7:6] b'00 = Preamble + SOP + Msg. Header + Data + CRC + EOP
    ScalerSetBit_EXINT(P6B_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), 0x00);

    // [0x6BE0] Set Packet Type [5:3]
    ScalerSetBit_EXINT(P6B_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), ((enumPacketType << 3) & (_BIT5 | _BIT4 | _BIT3)));

    // 4. [0x6BE5] Fill in Msg. Header0
    // [7]   Msg. Header[15]     : Extended Field
    ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT7, (ucExtendedBit_EXINT << 7));

    // [6:4] Msg. Header[14:12]  : Number of Data Object
    ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT6 | _BIT5 | _BIT4), ((ucDataObjectCnt_EXINT << 4) & (_BIT6 | _BIT5 | _BIT4)));

    if(enumPacketType == _PD_SOP_PKT)
    {
        // [3]   Msg. Header[8]  : Power Role
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, GET_TYPE_C_1_PD_POWER_ROLE() << 3);

        // [2:1] Msg. Header[7:6]  : Spec Version
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_TYPE_C_1_PD_SPEC_VER() << 1);

        // [0]   Msg. Header[5]  : Data Role
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_TYPE_C_1_PD_DATA_ROLE());
    }
    else
    {
        // [3]   Msg. Header[8]  : Cable Plug = Device (1)
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, ((BYTE)_PD_DEVICE << 3));

        // [2:1] Msg. Header[7:6]  : Cable Spec Version
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_TYPE_C_1_PD_CBL_SPEC_VER() << 1);

        // [0]   Msg. Header[5]  : Data Role
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);
    }

    // [0x6BE6] Fill in Msg. Header1
    // [4:0]  Msg. Header[4:0]    : Command Type = enumCtrlMsg
    ScalerSetBit_EXINT(P6B_E6_TX_FIFO_MSG_HEADER1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (enumPdCmd & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

    // Clear Tx FIFO Addr.
    ScalerSetByte_EXINT(P6B_E9_TX_FIFO_ADDR, 0x00);

    // Fill Data Object into Tx FIFO
    for(BYTE ucLoopIndex = 0; ucLoopIndex < (ucDataObjectCnt_EXINT * 4); ucLoopIndex++)
    {
        ScalerSetByte_EXINT(P6B_EA_TX_FIFO_DATA, g_pucTypeC1PdDataObject_EXINT[ucLoopIndex]);

        // Manual Increase Tx FIFO Address
        ScalerSetByte_EXINT(P6B_E9_TX_FIFO_ADDR, ScalerGetByte_EXINT(P6B_E9_TX_FIFO_ADDR) + 1);
    }
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO @ Interrupt
// Input Value  : enumPacketType : _PD_SOP_PKT / _PD_SOP_P_PKT
//                enumPdCmd : _PD_CMD_ACCEPT / _PD_CMD_REQUEST / _PD_CMD_SRC_CAP / _PD_CMD_VDM ...
//                enumVdmCmd : _PD_VDM_CMD_DISCOVER_ID_ACK / _PD_VDM_CMD_DISCOVER_ID_NAK ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdConstructDataObj_EXINT0(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    // Clear ucDataObj_EXINT
    for(BYTE ucLoopIndex = 0; ucLoopIndex < _MAX_DATA_OBJ_CNT * 4; ucLoopIndex ++)
    {
        g_pucTypeC1PdDataObject_EXINT[ucLoopIndex] = 0;
    }

    // Process Data Object Fields For FIFO Fill
    switch(enumPdCmd)
    {
        case _PD_CMD_SRC_CAP:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| DRP| Sus| UP | UC | DRD| Unc|
#if((_TYPE_C_1_PD_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
            if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT5);
            }
#endif

#if(_USB_SUSPEND == _TRUE)
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT4);
#endif
            if(GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _TRUE)
            {
                g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT3);
            }

#if(_EMB_TYPE_C_1_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT2);
#endif

#if((_TYPE_C_1_PD_DFP_SWAP_TO_UFP == _TRUE) || (_TYPE_C_1_PD_UFP_SWAP_TO_DFP == _TRUE))
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT1);
#endif

#if(_UNCHUNK_SUPPORT == _TRUE)
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT0);
            }
#endif

            // [23] EPR Mode Capable
            if(GET_TYPE_C_1_PD_EPR_SRC_CAPABLE() == _TRUE)
            {
                g_pucTypeC1PdDataObject_EXINT[1] = g_pucTypeC1PdDataObject_EXINT[1] | (_BIT7);
            }

            for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT(); ucLoopIndex ++)
            {
                if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_FIX_SUPPLY_PDO)
                {
                    // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex)) << 6);

                    // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                    // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_PEAK(ucLoopIndex) << 4) & (_BIT5 | _BIT4));
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                    // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex) > GET_TYPE_C_1_PD_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)(GET_TYPE_C_1_PD_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)GET_TYPE_C_1_PD_CBL_MAX_CUR());
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex) >> 8) & (_BIT1 | _BIT0));
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex)));
                    }
                }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
                else if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO))
                {
                    // [31:28] PDO Type = 4'b1100 (Programmabl Power Supply)
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex)) << 4);

                    // [24:17] Max Voltage in 100mV
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 10) >> 7) & (_BIT0));
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 10) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = (BYTE)(GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(ucLoopIndex) / 10);

                    // [6:0] Max Current in 50mA
                    if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (((GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex)) * 5) > GET_TYPE_C_1_PD_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = (((BYTE)(GET_TYPE_C_1_PD_CBL_MAX_CUR() / 5)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = (((BYTE)GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            }

            break;

        case _PD_CMD_REQUEST:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | 0  |   Obj. Pos   | GB | CM | UC | Sus|
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (GET_TYPE_C_1_PD_REQ_OBJ_POS() << 4);
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (GET_TYPE_C_1_PD_REQ_GIVE_BACK() << 3);

#if((_EMB_TYPE_C_1_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) || (_EMB_TYPE_C_1_USB_SPEED == _USB_BILLBOARD_ONLY))
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT1);
#endif

#if(_USB_SUSPEND == _FALSE)
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT0);
#endif

            // | 23 | 22 | 21 | 20 | 19 | ... | 16 | 15 | ... | 10 | 09 | 08 | 07 | ... | 00 |
            // | UC | Reserved(0)  |         Info1 [19:10]         |       Info2 [9:0]       |
#if(_UNCHUNK_SUPPORT == _TRUE)
            g_pucTypeC1PdDataObject_EXINT[1] = g_pucTypeC1PdDataObject_EXINT[1] | (_BIT7);
#endif

            if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
            {
                if((WORD)GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) < GET_TYPE_C_1_PD_REQ_INFO_2())
                {
                    // Set Capability Mismatch Flag
                    g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT2);

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucTypeC1PdDataObject_EXINT[1] = g_pucTypeC1PdDataObject_EXINT[1] | ((BYTE)(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | ((BYTE)(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | ((BYTE)(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) >> 8) & (_BIT1 | _BIT0));
                    g_pucTypeC1PdDataObject_EXINT[3] = g_pucTypeC1PdDataObject_EXINT[3] | (BYTE)(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1));
                }
                else
                {
                    // Set Capability Mismatch Flag
                    g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | ((GET_TYPE_C_1_PD_REQ_CAP_MIS() << 2) & (_BIT2));

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucTypeC1PdDataObject_EXINT[1] = g_pucTypeC1PdDataObject_EXINT[1] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_1() >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_1() << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_2() >> 8) & (_BIT1 | _BIT0));
                    g_pucTypeC1PdDataObject_EXINT[3] = g_pucTypeC1PdDataObject_EXINT[3] | (BYTE)(GET_TYPE_C_1_PD_REQ_INFO_2());
                }
            }
            else
            {
                // Set Capability Mismatch Flag
                g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | ((GET_TYPE_C_1_PD_REQ_CAP_MIS() << 2) & (_BIT2));

                // RDO[19:9] : PPS (Vol in 20mV)
                g_pucTypeC1PdDataObject_EXINT[1] = g_pucTypeC1PdDataObject_EXINT[1] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_1() >> 7) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_1() << 1) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

                // RDO[6:0] : PPS (Op. Cur in 50mA)
                g_pucTypeC1PdDataObject_EXINT[3] = g_pucTypeC1PdDataObject_EXINT[3] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_2()) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            }

            break;

        case _PD_CMD_SNK_CAP:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | PDO Type| PR | HC | UP | UC | DR | -- |
#if((_TYPE_C_1_PD_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
            if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP)
            {
                g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT5);
            }
#endif

#if(_HIGHER_CAP == _TRUE)
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT4);
#endif

            if(GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _TRUE)
            {
                g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT3);
            }

#if((_EMB_TYPE_C_1_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) || (_EMB_TYPE_C_1_USB_SPEED == _USB_BILLBOARD_ONLY))
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT2);
#endif

#if((_TYPE_C_1_PD_DFP_SWAP_TO_UFP == _TRUE) || (_TYPE_C_1_PD_UFP_SWAP_TO_DFP == _TRUE))
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT1);
#endif

            for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TYPE_C_1_PD_SPR_SNK_PDO_CNT(); ucLoopIndex ++)
            {
                if(GET_TYPE_C_1_PD_SNK_PDO_TYPE(ucLoopIndex) == _PD_FIX_SUPPLY_PDO)
                {
                    // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] | (((BYTE)GET_TYPE_C_1_PD_SNK_PDO_TYPE(ucLoopIndex)) << 6);

                    // | 23 | 22 | 21 | 20 | 19 .. 16 | 15 .. 10 | 09 | 08 | 07 .. 00 |
                    // | FR | Reserved(0)  | Voltage(50mV)[9:0]  |   Max.Cur [9:0]    |
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)((GET_TYPE_C_1_PD_SNK_CAP_VOL_MAX(ucLoopIndex) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)((GET_TYPE_C_1_PD_SNK_CAP_VOL_MAX(ucLoopIndex) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)(GET_TYPE_C_1_PD_SNK_CAP_CUR(ucLoopIndex) >> 8) & (_BIT1 | _BIT0));
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)(GET_TYPE_C_1_PD_SNK_CAP_CUR(ucLoopIndex)));
                }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
                else if(GET_TYPE_C_1_PD_SNK_PDO_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
                {
                    // [31:28] PDO Type = 4'b1100 (Programmabl Power Supply)
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] | (((BYTE)GET_TYPE_C_1_PD_SNK_PDO_TYPE(ucLoopIndex)) << 4);

                    // [24:17] Max Voltage in 100mV
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4)] | ((BYTE)((GET_TYPE_C_1_PD_SNK_CAP_VOL_MAX(ucLoopIndex) / 10) >> 7) & (_BIT0));
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 1] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 1] | ((BYTE)((GET_TYPE_C_1_PD_SNK_CAP_VOL_MAX(ucLoopIndex) / 10) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = (BYTE)(GET_TYPE_C_1_PD_SNK_CAP_VOL_MIN(ucLoopIndex) / 10);

                    // [6:0] Max Current in 50mA
                    g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = (((BYTE)GET_TYPE_C_1_PD_SNK_CAP_CUR(ucLoopIndex)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
#endif
            }

            break;

        case _PD_CMD_VDM:

            ScalerTypeC1PdConstructVdmDataObj_EXINT0(enumPacketType, enumVdmCmd);
            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_ALERT:

            // ---------- Data Message (1 Data Object) ----------
            // Set Type of Alert : [30] OVP Event, [26] OCP Event
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
            if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
            {
                g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT6);
            }
            if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
            {
                g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT2);
            }
#endif

            // [31:24] Type of Alert
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (BYTE)(GET_TYPE_C_1_PD_TYPE_OF_ALERT());

            // [23:20] Fixed Batteries, [19:16] Hot Swappable Batteries
            g_pucTypeC1PdDataObject_EXINT[1] = g_pucTypeC1PdDataObject_EXINT[1] | (BYTE)(GET_TYPE_C_1_PD_BAT_STATUS());

            // [15:4] Rsv., [3:0] Extended Alert Event Type
            g_pucTypeC1PdDataObject_EXINT[3] = g_pucTypeC1PdDataObject_EXINT[3] | ((BYTE)(GET_TYPE_C_1_PD_EXT_ALERT_EVENT()) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

        case _PD_CMD_SRC_CAP_EXT:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 25
            g_pucTypeC1PdDataObject_EXINT[1] = 25;

            // ---------- SECDB : Source Cap Ext Data Blocks (23 Bytes) ----------
            // Byte 00 - 01 :   Vender ID - 0x0BDA (RealTek)
            g_pucTypeC1PdDataObject_EXINT[2] = _USB_VENDOR_ID_L;
            g_pucTypeC1PdDataObject_EXINT[3] = _USB_VENDOR_ID_H;

            // Byte 02 - 03 :   Product ID
            g_pucTypeC1PdDataObject_EXINT[4] = _USB_PRODUCT_ID_L;
            g_pucTypeC1PdDataObject_EXINT[5] = _USB_PRODUCT_ID_H;

            // Byte 04 - 07 :   XID
            g_pucTypeC1PdDataObject_EXINT[6] = _USB_XID_BYTE0;
            g_pucTypeC1PdDataObject_EXINT[7] = _USB_XID_BYTE1;
            g_pucTypeC1PdDataObject_EXINT[8] = _USB_XID_BYTE2;
            g_pucTypeC1PdDataObject_EXINT[9] = _USB_XID_BYTE3;

            // Byte 08 : FW Version
            g_pucTypeC1PdDataObject_EXINT[10] = _PD_FW_VERSION;

            // Byte 09 : HW Version
            g_pucTypeC1PdDataObject_EXINT[11] = _PD_HW_VERSION;

            // Byte 10 : Voltage Regulation
            // Byte 11 : Holdup Time
            // Byte 12 : Compliance
            // Byte 13 : Touch Current
            // Byte 14 - 15 : Peak Current 1
            // Byte 16 - 17 : Peak Current 2
            // Byte 18 - 19 : Peak Current 3
            // Byte 20 : Touch Temp
            // Byte 21 : Source Input [0] Ext Power / [1] Ext Power Unconstrained / [2] Internal Battery Exist
            g_pucTypeC1PdDataObject_EXINT[23] = (_BIT1 | _BIT0);

            // Byte 22 : Battries
            // Byte 23 : SPR Source PDP Rating [Unit = W]
            if(GET_TYPE_C_1_MAX_POWER() > 1000)
            {
                g_pucTypeC1PdDataObject_EXINT[25] = 100;
            }
            else
            {
                g_pucTypeC1PdDataObject_EXINT[25] = (GET_TYPE_C_1_MAX_POWER() / 10);
            }

            // Byte 24 : EPR Source PDP Rating [Unit = W]
            if(GET_TYPE_C_1_PD_EPR_SRC_CAPABLE() == _TRUE)
            {
                g_pucTypeC1PdDataObject_EXINT[26] = (GET_TYPE_C_1_MAX_POWER() / 10);
            }

            break;

        case _PD_CMD_SNK_CAP_EXT:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 24
            g_pucTypeC1PdDataObject_EXINT[1] = 24;

            // ---------- SKEDB : Sink Cap Ext Data Blocks (24 Bytes) ----------
            // Byte 00 - 01 :   Vender ID - 0x0BDA (RealTek)
            g_pucTypeC1PdDataObject_EXINT[2] = _USB_VENDOR_ID_L;
            g_pucTypeC1PdDataObject_EXINT[3] = _USB_VENDOR_ID_H;

            // Byte 02 - 03 :   Product ID
            g_pucTypeC1PdDataObject_EXINT[4] = _USB_PRODUCT_ID_L;
            g_pucTypeC1PdDataObject_EXINT[5] = _USB_PRODUCT_ID_H;

            // Byte 04 - 07 :   XID
            g_pucTypeC1PdDataObject_EXINT[6] = _USB_XID_BYTE0;
            g_pucTypeC1PdDataObject_EXINT[7] = _USB_XID_BYTE1;
            g_pucTypeC1PdDataObject_EXINT[8] = _USB_XID_BYTE2;
            g_pucTypeC1PdDataObject_EXINT[9] = _USB_XID_BYTE3;

            // Byte 08 : FW Version
            g_pucTypeC1PdDataObject_EXINT[10] = _PD_FW_VERSION;

            // Byte 09 : HW Version
            g_pucTypeC1PdDataObject_EXINT[11] = _PD_HW_VERSION;

            // Byte 10 : SKEDB Version : 1 (Version 1.0)
            g_pucTypeC1PdDataObject_EXINT[12] = 1;

            // Byte 11 : Load Step
            // Byte 12 - 13 : Sink Load Characteristics
            // Byte 14 : Compliance
            // Byte 15 : Touch Temp
            // Byte 16 : Battery Info
            // Byte 17 : Sink Modes [0] PPS charging supported / [1] VBUS powered / [2] Mains powered / [3] Battery powered /
            // -------------------- [4] Battery essentially unlimited / [5] AVS Supported
#if(_TYPE_C_POWER_SOURCE == _TYPE_C_SELF_POWER_ONLY)
            g_pucTypeC1PdDataObject_EXINT[19] = _BIT2;
#elif(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
            g_pucTypeC1PdDataObject_EXINT[19] = _BIT1;
#elif(_TYPE_C_POWER_SOURCE == _TYPE_C_SELF_AND_VBUS_POWER)
            g_pucTypeC1PdDataObject_EXINT[19] = (_BIT2 | _BIT1);
#endif

            // Byte 18 : Sink Minimum PDP [Unit = W] (Rounded Up to the Next Integer)
            g_pucTypeC1PdDataObject_EXINT[20] = (GET_TYPE_C_1_PD_SNK_MIN_PDP() / 10) + ((GET_TYPE_C_1_PD_SNK_MIN_PDP() % 10) != 0);

            // Byte 19 : Sink Operational PDP [Unit = W] (Rounded Up to the Next Integer)
            g_pucTypeC1PdDataObject_EXINT[21] = (GET_TYPE_C_1_PD_SNK_OPERATIONAL_PDP() / 10) + ((GET_TYPE_C_1_PD_SNK_OPERATIONAL_PDP() % 10) != 0);

            // Byte 20 : Sink Maximum PDP [Unit = W] (Rounded Up to the Next Integer)
            g_pucTypeC1PdDataObject_EXINT[22] = (GET_TYPE_C_1_PD_SNK_MAX_PDP() / 10) + ((GET_TYPE_C_1_PD_SNK_MAX_PDP() % 10) != 0);

            // Byte 21 : EPR Sink Minimum PDP
            // Byte 22 : EPR Sink Operational PDP
            // Byte 23 : EPR Sink Maximum PDP

            break;

        case _PD_CMD_STATUS:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 7
            g_pucTypeC1PdDataObject_EXINT[1] = 7;

            // ---------- SDB : Status Data Blocks (7 Bytes) ----------
            // Byte 00 : Internal Temp (Unit = Temp in C / 0 = Not Support)

            // Byte 01 : Present Input [7:5] Reserved
            // [4] Internal Power From Non Battery
            // [3] Internal Power From Battery
            // [2] External Power DC = 0 / AC = 1
            // [1] External Power Exist
            g_pucTypeC1PdDataObject_EXINT[3] = g_pucTypeC1PdDataObject_EXINT[3] | (_BIT4 | _BIT2 | _BIT1);

            // Byte 02 : Present Battery Input [7:4] : Hot Swappable / [3:0] Fixed Battery
            // Byte 03 : Event Flag [7:5] : Reserved / [4] : CC,CV / [3] : OVP / [2] OTP / [1] OCP / [0] Reserved
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_BY_USER)
            if(((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP) || ((GET_TYPE_C_1_PD_PORT_CTRL_EVENT() & _PD_PORT_CTRL_EVENT_POWER_OVP) == _PD_PORT_CTRL_EVENT_POWER_OVP))
            {
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT3);
            }
            if(((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP) || ((GET_TYPE_C_1_PD_PORT_CTRL_EVENT() & _PD_PORT_CTRL_EVENT_POWER_OCP) == _PD_PORT_CTRL_EVENT_POWER_OCP))
            {
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT1);
            }
#else
            if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
            {
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT3);
            }
            if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
            {
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT1);
            }
#endif

            // Byte 04 : Temperature State
            // Byte 05 : Power Status [1] Source power limited due to cable supported current
            if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
            {
                for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT(); ucLoopIndex ++)
                {
                    if(GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex) > GET_TYPE_C_1_PD_CBL_MAX_CUR())
                    {
                        g_pucTypeC1PdDataObject_EXINT[7] = g_pucTypeC1PdDataObject_EXINT[7] | (_BIT1);
                    }
                }
            }

            // Byte 06 : Power State Change
            g_pucTypeC1PdDataObject_EXINT[8] = g_pucTypeC1PdDataObject_EXINT[8] | ((BYTE)(GET_TYPE_C_1_PD_NEW_POWER_STATE()) & (_BIT2 | _BIT1 | _BIT0));
            g_pucTypeC1PdDataObject_EXINT[8] = g_pucTypeC1PdDataObject_EXINT[8] | ((BYTE)(GET_TYPE_C_1_PD_NEW_POWER_INDICATOR() << 3) & (_BIT5 | _BIT4 | _BIT3));

            break;

        case _PD_CMD_MFC_INFO:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 4 ~ 26.
            // [MQP] PD3.0 Protocol test (Source) : GPROT-SRC3-MNINF.
            // Rcv. Get_Manu_Info with Invalid Target/Reference Shall Resp. Manu_Info with (VID + PID + Null-Ended "Not Supported" ASCII String).
            g_pucTypeC1PdDataObject_EXINT[1] = 18;

            // ---------- MIDB : Manufacturer Into Data Blocks (18 Bytes) ----------
            // Byte 00 - 01 :   Vender ID - 0x0BDA (RealTek)
            g_pucTypeC1PdDataObject_EXINT[2] = _USB_VENDOR_ID_L;
            g_pucTypeC1PdDataObject_EXINT[3] = _USB_VENDOR_ID_H;

            // Byte 02 - 03 :   Product ID
            g_pucTypeC1PdDataObject_EXINT[4] = _USB_PRODUCT_ID_L;
            g_pucTypeC1PdDataObject_EXINT[5] = _USB_PRODUCT_ID_H;

            // Byte 04 - 26 :   Manufacturer String
            g_pucTypeC1PdDataObject_EXINT[6] = 0x4E; // N
            g_pucTypeC1PdDataObject_EXINT[7] = 0x6F; // o

            g_pucTypeC1PdDataObject_EXINT[8] = 0x74; // t
            g_pucTypeC1PdDataObject_EXINT[9] = 0x20; // " "

            g_pucTypeC1PdDataObject_EXINT[10] = 0x53; // S
            g_pucTypeC1PdDataObject_EXINT[11] = 0x75; // u

            g_pucTypeC1PdDataObject_EXINT[12] = 0x70; // p
            g_pucTypeC1PdDataObject_EXINT[13] = 0x70; // p

            g_pucTypeC1PdDataObject_EXINT[14] = 0x6F; // o
            g_pucTypeC1PdDataObject_EXINT[15] = 0x72; // r

            g_pucTypeC1PdDataObject_EXINT[16] = 0x74; // t
            g_pucTypeC1PdDataObject_EXINT[17] = 0x65; // e

            g_pucTypeC1PdDataObject_EXINT[18] = 0x64; // d
            g_pucTypeC1PdDataObject_EXINT[19] = 0x00; // NULL

            break;

        case _PD_CMD_CHUNK_TEST:

            // If More Chunk Resp. Need to  Be Requested
            if(GET_TYPE_C_1_PD_CHUNK_REQUEST() == _TRUE)
            {
                // ---------- Extended Message Header (2 Bytes) ----------
                // [15] Ext Msg. is Sent in Chunk, [10] Chunk Request, [8:0] Data Size of Chunk Request Should Be 0
                g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT7 | _BIT2);

                // [14:11] Requested Next Chunk
                g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | ((GET_TYPE_C_1_PD_CHUNK_NUMBER() + 1) << 3);
            }

            break;

        case _PD_CMD_PPS_STATUS:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT7);
#endif
            // [8:0] Data Size : Total Num Of Data Blocks = 4
            g_pucTypeC1PdDataObject_EXINT[1] = 4;

            // ---------- PPSSDB : PPS Status Data Blocks (4 Bytes) ----------
            // Byte 00 - 01 : Output Voltage in 20mV (0xFFFF Not Support)
            g_pucTypeC1PdDataObject_EXINT[2] = 0xFF;
            g_pucTypeC1PdDataObject_EXINT[3] = 0xFF;

            // Byte 02 : Output Current in 50mA (0xFF Not Support)
            g_pucTypeC1PdDataObject_EXINT[4] = 0xFF;

            // Byte 03 : Real Time Flag
            // [3] OMF (1 : Current Fold Back / 0 : Constant Voltge)
#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON))
            if(ScalerTypeC1PmicReadPpsOperationModeStatus_EXINT0() == _TYPE_C_PMIC_CC_MODE_OPERATION)
            {
                // Set Current Limit Mode
                g_pucTypeC1PdDataObject_EXINT[5] |= _BIT3;
            }
            else
            {
                // Set Constant Voltage Mode
                g_pucTypeC1PdDataObject_EXINT[5] &= ~_BIT3;
            }
#else
            // Set Constant Voltage Mode
            g_pucTypeC1PdDataObject_EXINT[5] &= ~_BIT3;
#endif

            break;

        case _PD_CMD_REVISION:

            // ---------- Data Message (1 Data Object) ----------
            // [31:28] Revision.major, [27:24] Revision.minor,
            g_pucTypeC1PdDataObject_EXINT[0] = _PD_SPEC_REVISION;

            // [23:20] Version.major, [19:16] Version.minor, [15:0] Reserved
            g_pucTypeC1PdDataObject_EXINT[1] = _PD_SPEC_VERSION;
            g_pucTypeC1PdDataObject_EXINT[2] = 0x00;
            g_pucTypeC1PdDataObject_EXINT[3] = 0x00;

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        case _PD_CMD_EPR_MODE:

            // [31:24] Action :
            g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_EPR_MODE_ACTION();

            // [23:16] Data :
            if(GET_TYPE_C_1_PD_EPR_MODE_ACTION() == _PD_EPR_MODE_ENTER_FAILED)
            {
                // EPR Mode Enter Failed Reason
                g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON();
            }

            break;

        case _PD_CMD_EPR_SRC_CAP:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT7);
#endif

            if(GET_TYPE_C_1_PD_TX_CHUNKED_MESSAGE() == _TRUE)
            {
                // [14:11] Chunk Number
                g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | ((GET_TYPE_C_1_PD_TX_CHUNK_NUMBER()) << 3);

                // [8:0] Data Size : Total Num Of Data Blocks = [ 7 (Max SPR PDO Count) + EPR PDO Count ] * 4
                g_pucTypeC1PdDataObject_EXINT[1] = ((7 + GET_TYPE_C_1_PD_EPR_SRC_PDO_CNT()) * 4);
            }
            else
            {
                // [8:0] Data Size : Total Num Of Data Blocks = Total PDO Count * 4
                g_pucTypeC1PdDataObject_EXINT[1] = (GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() * 4);
            }

            // ---------- EPR Source Cap Data Blocks (1 PDO = 4 Bytes) ----------
            // ----------- | Byte 00 | Byte 01 | Byte 02 | Byte 03 | ------------
            // ----------- |  [7:0]  | [15:8]  | [23:16] | [31:24] | ------------
            if(((GET_TYPE_C_1_PD_TX_CHUNKED_MESSAGE() == _TRUE) && (GET_TYPE_C_1_PD_TX_CHUNK_NUMBER() == 0)) || (GET_TYPE_C_1_PD_TX_CHUNKED_MESSAGE() == _FALSE))
            {
                // Construct EPR Source Cap Chunk 0

                // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
                // | PDO Type| DRP| Sus| UP | UC | DRD| Unc|
#if((_TYPE_C_1_PD_SRC_ACCEPT_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_ACCEPT_SWAP_TO_SRC == _TRUE) || (_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE) || (_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE))
                if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP)
                {
                    g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT5);
                }
#endif

#if(_USB_SUSPEND == _TRUE)
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT4);
#endif
                if(GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _TRUE)
                {
                    g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT3);
                }

#if(_EMB_TYPE_C_1_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT2);
#endif

#if((_TYPE_C_1_PD_DFP_SWAP_TO_UFP == _TRUE) || (_TYPE_C_1_PD_UFP_SWAP_TO_DFP == _TRUE))
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT1);
#endif

#if(_UNCHUNK_SUPPORT == _TRUE)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT0);
                }
#endif

                // [23] EPR Mode Capable
                if(GET_TYPE_C_1_PD_EPR_SRC_CAPABLE() == _TRUE)
                {
                    g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT7);
                }

                for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT(); ucLoopIndex ++)
                {
                    if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_FIX_SUPPLY_PDO)
                    {
                        // Only Fill Half of The 7th SPR PDO [15:0] When Use Chunked Message to Send EPR Source Cap
                        if(ucLoopIndex < 6)
                        {
                            // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex)) << 6);

                            // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                            // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 4] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_PEAK(ucLoopIndex) << 4) & (_BIT5 | _BIT4));
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 4] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                        }

                        // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                        // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                        if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex) > GET_TYPE_C_1_PD_CBL_MAX_CUR()))
                        {
                            // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)(GET_TYPE_C_1_PD_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)GET_TYPE_C_1_PD_CBL_MAX_CUR());
                        }
                        else
                        {
                            // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                            // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex) >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex)));
                        }
                    }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
                    else if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO))
                    {
                        // Only Fill Half of The 7th SPR PDO [15:0] When Use Chunked Message to Send EPR Source Cap
                        if(ucLoopIndex < 6)
                        {
                            // [31:28] PDO Type = 4'b1100 (Programmabl Power Supply)
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex)) << 4);

                            // [24:17] Max Voltage in 100mV
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 10) >> 7) & (_BIT0));
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 4] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex) / 10) << 1) & (~_BIT0));
                        }

                        // [15:8] Min Voltage in 100mV
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 3] = (BYTE)(GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(ucLoopIndex) / 10);

                        // [6:0] Max Current in 50mA
                        if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (((GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex)) * 5) > GET_TYPE_C_1_PD_CBL_MAX_CUR()))
                        {
                            // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = (((BYTE)(GET_TYPE_C_1_PD_CBL_MAX_CUR() / 5)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                        }
                        else
                        {
                            // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                            // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 2] = (((BYTE)GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                        }
                    }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                }
            }
            else
            {
                // Construct EPR Source Cap Chunk 1

                // If SPR PDO Count = 7, Fill Remaining Half of The 7th SPR PDO
                if(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() == 7)
                {
                    if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1) == _PD_FIX_SUPPLY_PDO)
                    {
                        // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                        g_pucTypeC1PdDataObject_EXINT[3] = g_pucTypeC1PdDataObject_EXINT[3] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1)) << 6);

                        // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                        // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_PEAK(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1) << 4) & (_BIT5 | _BIT4));
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
                    else if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1) == _PD_3_PROGRAMMABLE_PDO))
                    {
                        // [31:28] PDO Type = 4'b1100 (Programmabl Power Supply)
                        g_pucTypeC1PdDataObject_EXINT[3] = g_pucTypeC1PdDataObject_EXINT[3] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1)) << 4);

                        // [24:17] Max Voltage in 100mV
                        g_pucTypeC1PdDataObject_EXINT[3] = g_pucTypeC1PdDataObject_EXINT[3] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1) / 10) >> 7) & (_BIT0));
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1) / 10) << 1) & (~_BIT0));
                    }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                }

                for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TYPE_C_1_PD_EPR_SRC_PDO_CNT(); ucLoopIndex ++)
                {
                    if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex + 7) == _PD_FIX_SUPPLY_PDO)
                    {
                        // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 7] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 7] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex + 7)) << 6);

                        // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                        // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 6] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 6] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_PEAK(ucLoopIndex + 7) << 4) & (_BIT5 | _BIT4));
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 6] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 6] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex + 7) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                        // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                        // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex + 7) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                        if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex + 7) > GET_TYPE_C_1_PD_CBL_MAX_CUR()))
                        {
                            // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | ((BYTE)(GET_TYPE_C_1_PD_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 4] | ((BYTE)GET_TYPE_C_1_PD_CBL_MAX_CUR());
                        }
                        else
                        {
                            // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                            // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex + 7) >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 4] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex + 7)));
                        }
                    }
                    else if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex + 7) == _PD_3_1_ADJUSTABLE_PDO)
                    {
                        // [31:28] PDO Type = 4'b1101 (Adjustable Voltage Supply)
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 7] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 7] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex + 7)) << 4);

                        // [27:26] Peak Current
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 7] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 7] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_PEAK(ucLoopIndex + 7) << 2) & (_BIT3 | _BIT2));

                        // [25:17] Max Voltage in 100mV
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 7] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 7] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex + 7) / 10) >> 7) & (_BIT1 | _BIT0));
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 6] = g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 6] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucLoopIndex + 7) / 10) << 1) & (~_BIT0));

                        // [15:8] Min Voltage in 100mV
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 5] = (BYTE)(GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(ucLoopIndex + 7) / 10);

                        // [7:0] PDP in 1W
                        g_pucTypeC1PdDataObject_EXINT[(ucLoopIndex * 4) + 4] = (BYTE)(GET_TYPE_C_1_MAX_POWER() / 10);
                    }
                }
            }

            break;

        case _PD_CMD_EXTENDED_CONTROL:

            switch(GET_TYPE_C_1_PD_EXT_CTRL_TYPE())
            {
                case _PD_EXT_CTRL_TYPE_EPR_KEEP_ALIVE_ACK:

                    // ---------- Extended Message Header (2 Bytes) ----------
                    // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
                    g_pucTypeC1PdDataObject_EXINT[0] = g_pucTypeC1PdDataObject_EXINT[0] | (_BIT7);
#endif
                    // [8:0] Data Size : Total Num Of Data Blocks = 2
                    g_pucTypeC1PdDataObject_EXINT[1] = 2;

                    // ---------- ECDB : Extended Control Data Block (2 Bytes) ----------
                    // Byte 00 : Type (0x04 : EPR Keep Alive ACK)
                    g_pucTypeC1PdDataObject_EXINT[2] = 0x04;

                    // Byte 01 : Data (Not Used)

                    break;

                default:

                    break;
            }

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        default:

            break;
    }// End of switch(enumPdCmd)
}

//--------------------------------------------------
// Description  : Set Up Number of VDM Data Objects(Data Blocks) @ Interrupt
// Input Value  : enumVdmCmd
// Output Value : Number of VDM Data Objects
//--------------------------------------------------
BYTE ScalerTypeC1PdSetVdmDataObjCnt_EXINT0(EnumTypeCVdmCmd enumVdmCmd)
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
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID)
    {
        switch(enumVdmCmd)
        {
            case _PD_VDM_CMD_DISCOVER_SVID_ACK:

                ucVdmDataObjectCnt_EXINT = 1 + (_TYPE_C_1_PD_ALT_MODE_SUPPORT_CNT >> 1) + 1;
                break;

            case _PD_VDM_CMD_DISCOVER_ID_ACK:

                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    if((GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() != _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED) && (GET_TYPE_C_1_PD_DFP_PRODUCT_TYPE() != _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED))
                    {
                        ucVdmDataObjectCnt_EXINT = 7;
                    }
                    else if((GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() != _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED) || (GET_TYPE_C_1_PD_DFP_PRODUCT_TYPE() != _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED))
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
                    if((GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_HUB) || (GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL) || (GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED))
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
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID)
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
#endif  // End of #if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _LENOVO_VID)
    {
        EnumTypeCVdmLenovoCmd enumVdmLenovoCmd = (EnumTypeCVdmLenovoCmd)enumVdmCmd;

        switch(enumVdmLenovoCmd)
        {
            case _PD_VDM_LENOVO_CMD_ENTER_MODE_ACK:
            case _PD_VDM_LENOVO_CMD_EXIT_MODE_ACK:
            case _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_ACK:
            case _PD_VDM_LENOVO_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_ENTER_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_EXIT_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_GET_STATUS_NAK:
            case _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_NAK:

                ucVdmDataObjectCnt_EXINT = 1;
                break;

            case _PD_VDM_LENOVO_CMD_DISCOVER_MODE_ACK:

                ucVdmDataObjectCnt_EXINT = 2;
                break;

            case _PD_VDM_LENOVO_CMD_GET_STATUS_ACK:

                ucVdmDataObjectCnt_EXINT = 3;
                break;

            default:

                ucVdmDataObjectCnt_EXINT = 0;
                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _ACER_VID)
    {
        EnumTypeCVdmAcerCmd enumVdmAcerCmd = (EnumTypeCVdmAcerCmd)enumVdmCmd;

        switch(enumVdmAcerCmd)
        {
            case _PD_VDM_ACER_CMD_DISCOVER_MODE_ACK:

                ucVdmDataObjectCnt_EXINT = 2;
                break;

            case _PD_VDM_ACER_CMD_ENTER_MODE_ACK:
            case _PD_VDM_ACER_CMD_EXIT_MODE_ACK:
            case _PD_VDM_ACER_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_ACER_CMD_ENTER_MODE_NAK:
            case _PD_VDM_ACER_CMD_EXIT_MODE_NAK:
            case _PD_VDM_ACER_CMD_GET_STATUS_NAK:

                ucVdmDataObjectCnt_EXINT = 1;
                break;

            case _PD_VDM_ACER_CMD_GET_STATUS_ACK:

                // "Acer Get Status Ack" Data Object Cnt from User + VDM Header(1 VDO)
                ucVdmDataObjectCnt_EXINT = GET_TYPE_C_1_PD_ACER_USER_VDM_CNT() + 1;

                break;

            default:

                ucVdmDataObjectCnt_EXINT = 0;
                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _HP_VID)
    {
        EnumTypeCVdmHpCmd enumVdmHpCmd = (EnumTypeCVdmHpCmd)enumVdmCmd;

        switch(enumVdmHpCmd)
        {
            case _PD_VDM_HP_CMD_ENTER_MODE_ACK:
            case _PD_VDM_HP_CMD_EXIT_MODE_ACK:
            case _PD_VDM_HP_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_HP_CMD_ENTER_MODE_NAK:
            case _PD_VDM_HP_CMD_EXIT_MODE_NAK:
            case _PD_VDM_HP_CMD_SET_CONFIG_ACK:
            case _PD_VDM_HP_CMD_SET_VWIRE_ACK:
            case _PD_VDM_HP_CMD_SET_DATA_ACK:

                ucVdmDataObjectCnt_EXINT = 1;
                break;

            case _PD_VDM_HP_CMD_DISCOVER_MODE_ACK:
            case _PD_VDM_HP_CMD_GET_CONFIG_ACK:

                ucVdmDataObjectCnt_EXINT = 2;
                break;

            case _PD_VDM_HP_CMD_GET_VWIRE_ACK:
            case _PD_VDM_HP_CMD_GET_DATA_ACK:

                ucVdmDataObjectCnt_EXINT = GET_TYPE_C_1_PD_HP_USER_VDM_CNT() + 2;
                break;

            default:

                ucVdmDataObjectCnt_EXINT = 0;
                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _DELL_VID)
    {
        EnumTypeCVdmDellCmd enumVdmDellCmd = (EnumTypeCVdmDellCmd)enumVdmCmd;

        switch(enumVdmDellCmd)
        {
            case _PD_VDM_DELL_CMD_ENTER_MODE_ACK:
            case _PD_VDM_DELL_CMD_EXIT_MODE_ACK:
            case _PD_VDM_DELL_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_DELL_CMD_ENTER_MODE_NAK:
            case _PD_VDM_DELL_CMD_EXIT_MODE_NAK:
            case _PD_VDM_DELL_CMD_0X12_ACK:

                ucVdmDataObjectCnt_EXINT = 1;
                break;

            case _PD_VDM_DELL_CMD_DISCOVER_MODE_ACK:

                ucVdmDataObjectCnt_EXINT = 2;
                break;

            default:

                ucVdmDataObjectCnt_EXINT = 0;
                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    else
    {
        ucVdmDataObjectCnt_EXINT = 1;
    }

    return ucVdmDataObjectCnt_EXINT;
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO @ Interrupt
// Input Value  : enumPacketType : _PD_SOP_PKT / _PD_SOP_P_PKT
//                enumVdmCmd : _VDM_CMD_DISCOVER_ID_REQ / _VDM_CMD_DISCOVER_SVID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdConstructVdmDataObj_EXINT0(EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucIndex = 0;
    enumPacketType = enumPacketType;

    if(enumVdmCmd == _PD_VDM_CMD_DISCOVER_ID_REQ)
    {
        // -------- Data Obj 0 : VDM Header --------
        // [31:16] PD SID = 0xFF00
        g_pucTypeC1PdDataObject_EXINT[0] = 0xFF;
        g_pucTypeC1PdDataObject_EXINT[1] = 0x00;

        // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos = b'000
        g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7);

        // For SOP Packet : If Port Partners Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
        // For SOP' Packet : If Port Partners & Cable Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
        if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)) ||
           ((enumPacketType == _PD_SOP_P_PKT) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_CBL_SPEC_VER() == _PD_VERSION_3_0)))
        {
            g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

            // SVDM Version = 2.1 Only when Port Partner or Cable Support 2.1 or Higher
            if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)) ||
               ((enumPacketType == _PD_SOP_P_PKT) && (GET_TYPE_C_1_PD_CBL_SVDM_VERSION() >= _PD_SVDM_VER_2_1)))
            {
                // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
            }
        }

        // [7:0] VDM CMD = Discover ID Request (0x01)
        g_pucTypeC1PdDataObject_EXINT[3] = enumVdmCmd;
    }
    else if(enumVdmCmd == _PD_VDM_CMD_ATTENTION_REQ)
    {
        // -------- Data Obj 0 : VDM Header --------
        // [31:16] DP SID = 0xFF01
        g_pucTypeC1PdDataObject_EXINT[0] = 0xFF;
        g_pucTypeC1PdDataObject_EXINT[1] = 0x01;

        // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
        g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7) | (GET_TYPE_C_1_PD_DP_OBJ_POS());

        // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
        if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
        {
            g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

            // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
            if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
            {
                // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
            }
        }

        // [7:0] VDM CMD = Attention Req (0x06)
        g_pucTypeC1PdDataObject_EXINT[3] = enumVdmCmd;

        // -------- Data Obj 1 : DP Status ---------
        // [31:16] Reserved = 0x00
        g_pucTypeC1PdDataObject_EXINT[4] = 0x00;
        g_pucTypeC1PdDataObject_EXINT[5] = 0x00;

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
        // [15:9] Reserved, [8] HPD IRQ, [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No
        // [4] Multi-Func = No, [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
        g_pucTypeC1PdDataObject_EXINT[6] = 0x00;
        g_pucTypeC1PdDataObject_EXINT[7] = (0x0A) | (GET_TYPE_C_1_PD_MULTI_FUNCTION() << 4);

        if(GET_TYPE_C_1_PD_FORCE_HPD_IRQ() == _TRUE)
        {
            // HPD = IRQ, HPD_High = 1
            g_pucTypeC1PdDataObject_EXINT[7] = (g_pucTypeC1PdDataObject_EXINT[7]) | (_BIT7);

            // HPD IRQ = 1
            g_pucTypeC1PdDataObject_EXINT[6] = _BIT0;
        }
        else if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) != _PD_HPD_LOW)
        {
            // HPD = HIGH or IRQ, HPD_High = 1
            g_pucTypeC1PdDataObject_EXINT[7] = (g_pucTypeC1PdDataObject_EXINT[7]) | (_BIT7);

            if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) == _PD_HPD_IRQ)
            {
                g_pucTypeC1PdDataObject_EXINT[6] = _BIT0;
            }
        }

        if(GET_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
        {
            g_pucTypeC1PdDataObject_EXINT[7] = g_pucTypeC1PdDataObject_EXINT[7] | (_BIT6);
        }

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
        // [15:9] Reserved, [8] HPD IRQ : No, [7] HPD State : LOW, [6] Exit DP : No, [5] USB Config = No
        // [4] Multi-Func, [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_TX(b'01)
        g_pucTypeC1PdDataObject_EXINT[6] = 0x00;
        g_pucTypeC1PdDataObject_EXINT[7] = (0x09) | (GET_TYPE_C_1_PD_MULTI_FUNCTION() << 4);

        if(GET_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
        {
            g_pucTypeC1PdDataObject_EXINT[7] = g_pucTypeC1PdDataObject_EXINT[7] | (_BIT6);
        }
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    }
    else if(enumVdmCmd == _PD_VDM_CMD_10)
    {
        // -------- Data Obj 0 : VDM Header --------
        // [31:16] DP SID = 0xFF01
        g_pucTypeC1PdDataObject_EXINT[0] = 0xFF;
        g_pucTypeC1PdDataObject_EXINT[1] = 0x01;

        // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
        g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7) | (GET_TYPE_C_1_PD_DP_OBJ_POS());

        // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
        if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
        {
            g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

            // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
            if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
            {
                // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
            }
        }

        // [7:0] VDM CMD = DP Status Req (0x10)
        g_pucTypeC1PdDataObject_EXINT[3] = enumVdmCmd;

        // -------- Data Obj 1 : DP Status ---------
        // [31:16] Reserved = 0x00
        g_pucTypeC1PdDataObject_EXINT[4] = 0x00;
        g_pucTypeC1PdDataObject_EXINT[5] = 0x00;

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
        // [15:9] Reserved, [8] HPD IRQ, [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No
        // [4] Multi-Func = No, [3] DP En = No, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
        g_pucTypeC1PdDataObject_EXINT[6] = 0x00;
        g_pucTypeC1PdDataObject_EXINT[7] = 0x02;

        if(GET_TYPE_C_1_PD_FORCE_HPD_IRQ() == _TRUE)
        {
            // HPD = IRQ, HPD_High = 1
            g_pucTypeC1PdDataObject_EXINT[7] = (g_pucTypeC1PdDataObject_EXINT[7]) | (_BIT7);

            // HPD IRQ = 1
            g_pucTypeC1PdDataObject_EXINT[6] = _BIT0;
        }
        else if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) != _PD_HPD_LOW)
        {
            // HPD = HIGH or IRQ, HPD_High = 1
            g_pucTypeC1PdDataObject_EXINT[7] = (g_pucTypeC1PdDataObject_EXINT[7]) | (_BIT7);

            if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) == _PD_HPD_IRQ)
            {
                g_pucTypeC1PdDataObject_EXINT[6] = _BIT0;
            }
        }

        if(GET_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
        {
            g_pucTypeC1PdDataObject_EXINT[7] = g_pucTypeC1PdDataObject_EXINT[7] | (_BIT6);
        }

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
        // [15:2] Reserved, [1:0] Connected DP Role : DP_TX(b'01)
        g_pucTypeC1PdDataObject_EXINT[6] = 0x00;
        g_pucTypeC1PdDataObject_EXINT[7] = 0x01;
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    }
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _PD_SID)
    {
        switch(enumVdmCmd)
        {
            case _PD_VDM_CMD_DISCOVER_ID_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] PD SID = 0xFF00
                g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_VDM_SVID_H();
                g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos = b'000
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Discover ID Ack (0x41)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmCmd;

                // According to the PD Version, Set Product Type VDO Differently
                ScalerTypeC1PdSetProductTypeVDO_EXINT0();

                break;

            case _PD_VDM_CMD_DISCOVER_SVID_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] PD SID = 0xFF00
                g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_VDM_SVID_H();
                g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Discover SVID Ack (0x42)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmCmd;

                // -------- Data Obj : SVIDs --------
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
                g_pucTypeC1PdDataObject_EXINT[4 + ucIndex] = 0xFF;
                g_pucTypeC1PdDataObject_EXINT[5 + ucIndex] = 0x01;
                ucIndex = ucIndex + 2;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
                g_pucTypeC1PdDataObject_EXINT[4 + ucIndex] = 0x17;
                g_pucTypeC1PdDataObject_EXINT[5 + ucIndex] = 0xEF;
                ucIndex = ucIndex + 2;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
                g_pucTypeC1PdDataObject_EXINT[4 + ucIndex] = (BYTE)(_ACER_VID >> 8);    // _ACER_VID = 0x0502
                g_pucTypeC1PdDataObject_EXINT[5 + ucIndex] = (BYTE)(_ACER_VID);
                ucIndex = ucIndex + 2;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
                g_pucTypeC1PdDataObject_EXINT[4 + ucIndex] = (BYTE)(_HP_VID >> 8);      // _HP_VID = 0x03F0
                g_pucTypeC1PdDataObject_EXINT[5 + ucIndex] = (BYTE)(_HP_VID);
                ucIndex = ucIndex + 2;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
                g_pucTypeC1PdDataObject_EXINT[4 + ucIndex] = (BYTE)(_DELL_VID >> 8);    // _DELL_VID = 0x413C
                g_pucTypeC1PdDataObject_EXINT[5 + ucIndex] = (BYTE)(_DELL_VID);
                ucIndex = ucIndex + 2;
#endif

                if((_TYPE_C_1_PD_ALT_MODE_SUPPORT_CNT % 2) == 0)
                {
                    g_pucTypeC1PdDataObject_EXINT[4 + ucIndex] = 0x00;
                    g_pucTypeC1PdDataObject_EXINT[5 + ucIndex] = 0x00;
                    g_pucTypeC1PdDataObject_EXINT[6 + ucIndex] = 0x00;
                    g_pucTypeC1PdDataObject_EXINT[7 + ucIndex] = 0x00;
                }
                else
                {
                    g_pucTypeC1PdDataObject_EXINT[4 + ucIndex] = 0x00;
                    g_pucTypeC1PdDataObject_EXINT[5 + ucIndex] = 0x00;
                }

                break;

            case _PD_VDM_CMD_DISCOVER_ID_NAK:
            case _PD_VDM_CMD_DISCOVER_SVID_NAK:
            case _PD_VDM_CMD_DISCOVER_ID_BUSY:
            case _PD_VDM_CMD_DISCOVER_SVID_BUSY:
            default:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_VDM_SVID_H();
                g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7) | (GET_TYPE_C_1_PD_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmCmd;

                break;
        }
    }
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _DP_SID)
    {
        EnumTypeCVdmDpCmd enumVdmDpCmd = (EnumTypeCVdmDpCmd)enumVdmCmd;

        switch(enumVdmDpCmd)
        {
            case _PD_VDM_DP_CMD_DISCOVER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_VDM_SVID_H();
                g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Discover Mode Ack (0x43)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmDpCmd;

                // -------- Data Obj 1 : DP Capability -----
                // DPAM v2.1 Supported Only when DFP/UFP both Support SVDM 2.1 or Higher
                // [31:30] VDO Version = b'01(DPAM v2.1) / b'00(Not DPAM v2.1), [29:24] Rsv
                if((GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1) && (GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER))
                {
                    g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT6);
                }

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

#if(_EMB_TYPE_C_1_CONNECTOR_TYPE == _TYPE_C_PORT_PLUG)
                // [23:16] DP_RX Pin Assignment Support (Not Supprt As DP Rx)
                g_pucTypeC1PdDataObject_EXINT[5] = 0x00;

                // [15:8] DP_TX Pin Assignment Support
                g_pucTypeC1PdDataObject_EXINT[6] = GET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP();

                // [7] U2 Not Use = 0, [6] Plug = 0, [5:2] Signal Support (DP 1.3) = b'001, [1:0] DP Config.(RX) = b'01
                g_pucTypeC1PdDataObject_EXINT[7] = 0x05;
#else
                // [23:16] DP_RX Pin Assignment Support
                g_pucTypeC1PdDataObject_EXINT[5] = GET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP();

                // [15:8] DP_TX Pin Assignment Support (Not Supprt As DP Tx)
                g_pucTypeC1PdDataObject_EXINT[6] = 0x00;

                // [7] U2 Not Use = 0, [6] Receptable = 1, [5:2] Signal Support (DP 1.3) = b'001, [1:0] DP Config.(RX) = b'01
                g_pucTypeC1PdDataObject_EXINT[7] = 0x45;
#endif

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)

#if(_EMB_TYPE_C_1_CONNECTOR_TYPE == _TYPE_C_PORT_PLUG)
                // [23:16] DP_RX Pin Assignment Support
                g_pucTypeC1PdDataObject_EXINT[5] = GET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP();

                // [15:8] DP_TX Pin Assignment Support (Not Supprt As DP Tx)
                g_pucTypeC1PdDataObject_EXINT[6] = 0x00;

                // [7] U2 Not Use = 0, [6] Plug = 0, [5:2] Signal Support (DP 1.3) = b'001, [1:0] DP Config.(TX) = b'10
                g_pucTypeC1PdDataObject_EXINT[7] = 0x06;
#else
                // [23:16] DP_RX Pin Assignment Support (Not Supprt As DP Rx)
                g_pucTypeC1PdDataObject_EXINT[5] = 0x00;

                // [15:8] DP_TX Pin Assignment Support
                g_pucTypeC1PdDataObject_EXINT[6] = GET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP();

                // [7] U2 Not Use = 0, [6] Receptable = 1, [5:2] Signal Support (DP 1.3) = b'001, [1:0] DP Config.(TX) = b'10
                g_pucTypeC1PdDataObject_EXINT[7] = 0x46;
#endif

#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

                break;

            case _PD_VDM_DP_CMD_DP_STATUS_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_VDM_SVID_H();
                g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = ((_BIT7) | (GET_TYPE_C_1_PD_VDM_OBJ_POS()));

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = DP Status Ack (0x50)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmDpCmd;

                // -------- Data Obj 1 : DP Status ---------
                // [31:16] Reserved = 0x00
                g_pucTypeC1PdDataObject_EXINT[4] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[5] = 0x00;

                // [15:9] Reserved, [8] HPD IRQ : No
                g_pucTypeC1PdDataObject_EXINT[6] = 0x00;

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                // [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No, [4] Multi-Func,
                // [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
                g_pucTypeC1PdDataObject_EXINT[7] = (0x0A) | (GET_TYPE_C_1_PD_MULTI_FUNCTION() << 4);

                // If (HPD Count != 0) & (Not Attn Wait), Get Status from HPD Queue; else Use Current Status
                if((GET_TYPE_C_1_PD_HPD_CNT() > 0) && (GET_TYPE_C_1_PD_ATTENTION_WAIT() == _FALSE))
                {
                    // Check "HPD High/Low" and "HPD Status" from HPD Queue
                    if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) != _PD_HPD_LOW)
                    {
                        g_pucTypeC1PdDataObject_EXINT[7] = g_pucTypeC1PdDataObject_EXINT[7] | (_BIT7);

                        if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) == _PD_HPD_IRQ)
                        {
                            g_pucTypeC1PdDataObject_EXINT[6] = g_pucTypeC1PdDataObject_EXINT[6] | (_BIT0);
                        }
                    }
                }
                else
                {
                    // "HPD Count = 0" or "During Attn Wait" (May Cause By DP Source Update Info During Alt Mode), Use Current HPD Status
                    g_pucTypeC1PdDataObject_EXINT[7] = g_pucTypeC1PdDataObject_EXINT[7] | (GET_TYPE_C_1_PD_HPD_STATUS() << 7);
                }

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                // [7] HPD State : LOW, [6] Exit DP : No, [5] USB Config = No, [4] Multi-Func,
                // [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_TX(b'01)
                g_pucTypeC1PdDataObject_EXINT[7] = (0x09) | (GET_TYPE_C_1_PD_MULTI_FUNCTION() << 4);
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

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
                g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_VDM_SVID_H();
                g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7) | (GET_TYPE_C_1_PD_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmDpCmd;

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _LENOVO_VID)
    {
        EnumTypeCVdmLenovoCmd enumVdmLenovoCmd = (EnumTypeCVdmLenovoCmd)enumVdmCmd;

        switch(enumVdmLenovoCmd)
        {
            case _PD_VDM_LENOVO_CMD_DISCOVER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] LENOVO VID = 0x17EF
                g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_VDM_SVID_H();
                g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Discover Mode Ack (0x43)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmLenovoCmd;

                // -------- Data Obj 1 : Lenovo Discover Mode Response -----
                g_pucTypeC1PdDataObject_EXINT[4] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[5] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[6] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[7] = 0x01;

                break;

            case _PD_VDM_LENOVO_CMD_GET_STATUS_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] LENOVO VID = 0x17EF
                g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_VDM_SVID_H();
                g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Get Status Ack (0x50)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmLenovoCmd;

                // -------- Data Obj 1 : Lenovo Get Status Response VDO1-----
                // [31:28] Rsv., [27] Docking Power Button Break, [26] Docking Power Button Make,
                // [25] Wol Request, [24] Event
                g_pucTypeC1PdDataObject_EXINT[4] = GET_TYPE_C_1_PD_LENOVO_DOCK_EVENT();

                // [23:20] Rsv., [19] System Acknowledge Power Button Break, [18] System Acknowledge Power Button Make,
                // [17] Wol Request, [16] Event Acknowledge
                g_pucTypeC1PdDataObject_EXINT[5] = (GET_TYPE_C_1_PD_LENOVO_SYS_ACKNOWLEDGE() & 0xFE);

                // [15:13] Rsv., [12] System Power Mode, [11:9] System State, [8] Event
                g_pucTypeC1PdDataObject_EXINT[6] = GET_TYPE_C_1_PD_LENOVO_SYS_EVENT();

                // [7:5] Rsv., [4] Docking Acknowledge System Power Mode, [3:1] Docking Acknowledge System State, [0] Event Acknowledge
                g_pucTypeC1PdDataObject_EXINT[7] = GET_TYPE_C_1_PD_LENOVO_SYS_EVENT();

                // -------- Data Obj 2 : Lenovo Get Status Response VDO2-----
                // [31:28] FW Ver. = 0, [27:24] Rsv.
                g_pucTypeC1PdDataObject_EXINT[8] = 0x00;

                // Power Source
                // [23] Supplier Info = 0, [22:21] Src Type : Type-C Adapter, [20] Src Quality = Good, [19:16] Rating = Unknown AC adapter detected
                g_pucTypeC1PdDataObject_EXINT[9] = 0x30;

                // Function Capability
                // [15] Power Button Supported, [14] Wol Supported, [13] Wol Supported,
                // [12] MAC address pass through not Supported, [11] Change charging ability not Supported, [11:8] Rsv.
                g_pucTypeC1PdDataObject_EXINT[10] = 0xC0;

                // [7:0] Reserved = 0x00
                g_pucTypeC1PdDataObject_EXINT[11] = 0x00;

                break;

            case _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_ACK:
            case _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_NAK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] LENOVO VID = 0x17EF
                g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_VDM_SVID_H();
                g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmLenovoCmd;

                break;

            case _PD_VDM_LENOVO_CMD_ENTER_MODE_ACK:
            case _PD_VDM_LENOVO_CMD_EXIT_MODE_ACK:
            case _PD_VDM_LENOVO_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_ENTER_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_EXIT_MODE_NAK:
            case _PD_VDM_LENOVO_CMD_GET_STATUS_NAK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] LENOVO VID = 0x17EF
                g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_VDM_SVID_H();
                g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_VDM_SVID_L();

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7) | (GET_TYPE_C_1_PD_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmLenovoCmd;

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _ACER_VID)
    {
        EnumTypeCVdmAcerCmd enumVdmAcerCmd = (EnumTypeCVdmAcerCmd)enumVdmCmd;

        switch(enumVdmAcerCmd)
        {
            case _PD_VDM_ACER_CMD_DISCOVER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] ACER VID = 0x0502
                g_pucTypeC1PdDataObject_EXINT[0] = (BYTE)(_ACER_VID >> 8);
                g_pucTypeC1PdDataObject_EXINT[1] = (BYTE)_ACER_VID;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Discover Mode Ack (0x43)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmAcerCmd;

                // -------- Data Obj 1 : Acer Discover Mode Response -----
                g_pucTypeC1PdDataObject_EXINT[4] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[5] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[6] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[7] = 0x00;

                break;

            case _PD_VDM_ACER_CMD_ENTER_MODE_ACK:
            case _PD_VDM_ACER_CMD_EXIT_MODE_ACK:
            case _PD_VDM_ACER_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_ACER_CMD_ENTER_MODE_NAK:
            case _PD_VDM_ACER_CMD_EXIT_MODE_NAK:
            case _PD_VDM_ACER_CMD_GET_STATUS_NAK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] ACER VID = 0x0502
                g_pucTypeC1PdDataObject_EXINT[0] = (BYTE)(_ACER_VID >> 8);
                g_pucTypeC1PdDataObject_EXINT[1] = (BYTE)_ACER_VID;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7) | (GET_TYPE_C_1_PD_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Enter Mode Ack
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmAcerCmd;

                break;

            case _PD_VDM_ACER_CMD_GET_STATUS_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] ACER VID = 0x0502
                g_pucTypeC1PdDataObject_EXINT[0] = (BYTE)(_ACER_VID >> 8);
                g_pucTypeC1PdDataObject_EXINT[1] = (BYTE)_ACER_VID;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Get Status Ack (0x56)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmAcerCmd;

                // Construct Acer "Get Status Ack" Data Object(0~6)
                for(BYTE ucLoopIndex = 0; ucLoopIndex < (GET_TYPE_C_1_PD_ACER_USER_VDM_CNT() * 4); ucLoopIndex++)
                {
                    g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 4] = GET_TYPE_C_1_PD_ACER_USER_VDM_DATA(ucLoopIndex);
                }

                break;

            default:
                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _HP_VID)
    {
        EnumTypeCVdmHpCmd enumVdmHpCmd = (EnumTypeCVdmHpCmd)enumVdmCmd;

        switch(enumVdmHpCmd)
        {
            case _PD_VDM_HP_CMD_DISCOVER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] HP VID = 0x03F0
                g_pucTypeC1PdDataObject_EXINT[0] = (BYTE)(_HP_VID >> 8);
                g_pucTypeC1PdDataObject_EXINT[1] = (BYTE)_HP_VID;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Discover Mode Ack (0x43)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmHpCmd;

                // -------- Data Obj 1 : Hp Discover Mode Response -----
                g_pucTypeC1PdDataObject_EXINT[4] = 0x60;
                g_pucTypeC1PdDataObject_EXINT[5] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[6] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[7] = 0x00;

                break;

            case _PD_VDM_HP_CMD_ENTER_MODE_ACK:
            case _PD_VDM_HP_CMD_EXIT_MODE_ACK:
            case _PD_VDM_HP_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_HP_CMD_ENTER_MODE_NAK:
            case _PD_VDM_HP_CMD_EXIT_MODE_NAK:
            case _PD_VDM_HP_CMD_SET_CONFIG_ACK:
            case _PD_VDM_HP_CMD_SET_VWIRE_ACK:
            case _PD_VDM_HP_CMD_SET_DATA_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] HP VID = 0x03F0
                g_pucTypeC1PdDataObject_EXINT[0] = (BYTE)(_HP_VID >> 8);
                g_pucTypeC1PdDataObject_EXINT[1] = (BYTE)_HP_VID;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7) | (GET_TYPE_C_1_PD_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmHpCmd;

                break;

            case _PD_VDM_HP_CMD_GET_CONFIG_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] HP VID = 0x03F0
                g_pucTypeC1PdDataObject_EXINT[0] = (BYTE)(_HP_VID >> 8);
                g_pucTypeC1PdDataObject_EXINT[1] = (BYTE)_HP_VID;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7) | (_BIT0);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Get_config Ack (0x51)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmHpCmd;

                // -------- Data Obj 1 : Hp VDO -----
                // [31:27] Rsv., [26:20] I2C Address
                g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | ((GET_TYPE_C_1_PD_HP_I2C_ADDR() >> 4) & (_BIT2 | _BIT1 | _BIT0));
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | ((GET_TYPE_C_1_PD_HP_I2C_ADDR() << 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));

                // [19:18] Rsv., [17:0] AM_addr
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_H() & (_BIT1 | _BIT0));
                g_pucTypeC1PdDataObject_EXINT[6] = GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_M();
                g_pucTypeC1PdDataObject_EXINT[7] = GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_L();

                break;

            case _PD_VDM_HP_CMD_GET_VWIRE_ACK:
            case _PD_VDM_HP_CMD_GET_DATA_ACK:   // Multi-aprt Need to Develop Later

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] HP VID = 0x03F0
                g_pucTypeC1PdDataObject_EXINT[0] = (BYTE)(_HP_VID >> 8);
                g_pucTypeC1PdDataObject_EXINT[1] = (BYTE)_HP_VID;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7) | (_BIT0);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Get_vwire Ack (0x53). Get_data Ack (0x55)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmHpCmd;

                // -------- Data Obj 1 : Hp Sub Header -----
                // [31:23] Rsv., [22:20] VDO_CNT
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | ((GET_TYPE_C_1_PD_HP_USER_VDM_CNT() << 4) & (_BIT6 | _BIT5 | _BIT4));

                // [19:18] Rsv., [17:0] AM_addr
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_H() & (_BIT1 | _BIT0));
                g_pucTypeC1PdDataObject_EXINT[6] = GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_M();
                g_pucTypeC1PdDataObject_EXINT[7] = GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_L();

                // -------- Data Obj 2 : Hp V-wire VDO1 -----
                // [31:16] Data, [15:8] Index, [7:4] Rsv., [3:0] Operation
                for(BYTE ucLoopIndex = 0; ucLoopIndex < (GET_TYPE_C_1_PD_HP_USER_VDM_CNT() * 4); ucLoopIndex++)
                {
                    g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 8] = GET_TYPE_C_1_PD_HP_USER_VDM_DATA(ucLoopIndex);
                }

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    else if(GET_TYPE_C_1_PD_VDM_SVID() == _DELL_VID)
    {
        EnumTypeCVdmDellCmd enumVdmDellCmd = (EnumTypeCVdmDellCmd)enumVdmCmd;

        switch(enumVdmDellCmd)
        {
            case _PD_VDM_DELL_CMD_DISCOVER_MODE_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DELL VID = 0x413C
                g_pucTypeC1PdDataObject_EXINT[0] = (BYTE)(_DELL_VID >> 8);
                g_pucTypeC1PdDataObject_EXINT[1] = (BYTE)_DELL_VID;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7);

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Discover Mode Ack (0x43)
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmDellCmd;

                // -------- Data Obj 1 : Dell Discover Mode Response -----
                g_pucTypeC1PdDataObject_EXINT[4] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[5] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[6] = 0x00;
                g_pucTypeC1PdDataObject_EXINT[7] = 0x01;

                break;

            case _PD_VDM_DELL_CMD_ENTER_MODE_ACK:
            case _PD_VDM_DELL_CMD_EXIT_MODE_ACK:
            case _PD_VDM_DELL_CMD_DISCOVER_MODE_NAK:
            case _PD_VDM_DELL_CMD_ENTER_MODE_NAK:
            case _PD_VDM_DELL_CMD_EXIT_MODE_NAK:
            case _PD_VDM_DELL_CMD_0X12_ACK:

                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DELL VID = 0x413C
                g_pucTypeC1PdDataObject_EXINT[0] = (BYTE)(_DELL_VID >> 8);
                g_pucTypeC1PdDataObject_EXINT[1] = (BYTE)_DELL_VID;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7) | (GET_TYPE_C_1_PD_VDM_OBJ_POS());

                // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD
                g_pucTypeC1PdDataObject_EXINT[3] = enumVdmDellCmd;

                break;

            default:

                break;
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    else
    {
        // -------- Data Obj 0 : VDM Header --------
        // [31:16] SVID
        g_pucTypeC1PdDataObject_EXINT[0] = GET_TYPE_C_1_PD_VDM_SVID_H();
        g_pucTypeC1PdDataObject_EXINT[1] = GET_TYPE_C_1_PD_VDM_SVID_L();

        // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
        g_pucTypeC1PdDataObject_EXINT[2] = (_BIT7) | (GET_TYPE_C_1_PD_VDM_OBJ_POS());

        // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
        if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
        {
            g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT5);

            // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
            if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
            {
                // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                g_pucTypeC1PdDataObject_EXINT[2] = g_pucTypeC1PdDataObject_EXINT[2] | (_BIT3);
            }
        }

        // [7:0] VDM CMD
        g_pucTypeC1PdDataObject_EXINT[3] = enumVdmCmd;
    }
}

//--------------------------------------------------
// Description  : According to the PD Version, Set Product Type VDO Differently
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetProductTypeVDO_EXINT0(void)
{
    BYTE ucIndex = 0;

    switch(GET_TYPE_C_1_PD_SPEC_VER())
    {
        case _PD_VERSION_3_0:

            // PD Version = 3.0, Products with USB Hub IC, Product Type UFP choose Hub , Product Type DFP choose Undefined;
            // Products without USB Hub IC, Product Type UFP choose Peripheral, Product Type DFP choose Undefined.

            // -------- Data Obj 1 : ID Header ---------
            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // |Host|Dev.|      UFP     |Mode|   DFP   |
#if((_EMB_TYPE_C_1_USB_ROLE == _TYPE_C_USB_HOST_ONLY) || (_EMB_TYPE_C_1_USB_ROLE == _TYPE_C_USB_HOST_DEVICE))
            g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT7);
#endif

#if((_EMB_TYPE_C_1_USB_ROLE == _TYPE_C_USB_DEVICE_ONLY) || (_EMB_TYPE_C_1_USB_ROLE == _TYPE_C_USB_HOST_DEVICE) || (_EMB_TYPE_C_1_USB_SPEED == _USB_BILLBOARD_ONLY))
            g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT6);
#endif
            // UFP Product Type = 3b'000 Undefined/ 3b'001 PDUSB Hub/ 3b'010 PDUSB Peripheral
            if(GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED)
            {
                g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] & (~(_BIT5 | _BIT4 | _BIT3));
            }
            else if(GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_HUB)
            {
                g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT3);
            }
            else if(GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL)
            {
                g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT4);
            }

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT2);
#endif

            // [25:23] DFP Product Type = 3b'000 Undefined/ 3b'001 PDUSB Hub/ 3b'010 PDUSB Host/ 3b'011 Power Brick
            if(GET_TYPE_C_1_PD_DFP_PRODUCT_TYPE() == _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED)
            {
                g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] & (~(_BIT1 | _BIT0));
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] & (~(_BIT7));
            }
            else if(GET_TYPE_C_1_PD_DFP_PRODUCT_TYPE() == _TYPE_C_DFP_PRODUCT_TYPE_HUB)
            {
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT7);
            }
            else if(GET_TYPE_C_1_PD_DFP_PRODUCT_TYPE() == _TYPE_C_DFP_PRODUCT_TYPE_HOST)
            {
                g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT0);
            }
            else if(GET_TYPE_C_1_PD_DFP_PRODUCT_TYPE() == _TYPE_C_DFP_PRODUCT_TYPE_BRICK)
            {
                g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT0);
                g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT7);
            }

#if(_EMB_TYPE_C_1_CONNECTOR_TYPE == _TYPE_C_PORT_PLUG)
            // [22:21] = Connector Type: USB Type-C Plug = 2b'11
            g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT6 | _BIT5);
#else
            // [22:21] = Connector Type: USB Type-C Receptacle = 2b'10
            g_pucTypeC1PdDataObject_EXINT[5] = g_pucTypeC1PdDataObject_EXINT[5] | (_BIT6);
#endif

            // [15:0] = USB Vender ID 0x0BDA (RealTek)
            g_pucTypeC1PdDataObject_EXINT[6] = _USB_VENDOR_ID_H;
            g_pucTypeC1PdDataObject_EXINT[7] = _USB_VENDOR_ID_L;

            // -------- Data Obj 2 : Cert State (XID)
            g_pucTypeC1PdDataObject_EXINT[8] = _USB_XID_BYTE3;
            g_pucTypeC1PdDataObject_EXINT[9] = _USB_XID_BYTE2;
            g_pucTypeC1PdDataObject_EXINT[10] = _USB_XID_BYTE1;
            g_pucTypeC1PdDataObject_EXINT[11] = _USB_XID_BYTE0;

            // -------- Data Obj 3 : Product -----------
            // [31:16] bcd Device = 0x0300, [15:0] Product ID = _USB_PRODUCT_ID_H / _USB_PRODUCT_ID_L
            g_pucTypeC1PdDataObject_EXINT[12] = _USB_PRODUCT_ID_H;
            g_pucTypeC1PdDataObject_EXINT[13] = _USB_PRODUCT_ID_L;
            g_pucTypeC1PdDataObject_EXINT[14] = 0x03;
            g_pucTypeC1PdDataObject_EXINT[15] = 0x00;

            // If (UFP Product Type != Undefined) && (DFP Product Type == Undefined), Product Type VDO [UFP | Pad | Pad].
            // If (UFP Product Type == Undefined) && (DFP Product Type != Undefined), Product Type VDO [DFP | Pad | Pad].
            // If (UFP Product Type != Undefined) && (DFP Product Type != Undefined), Product Type VDO [UFP | Pad | DFP].
            ucIndex = 15;

            if((GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_HUB) || (GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL))
            {
                // -------- Data Obj 4 : UFP VDO ---------
                // [31:29] UFP VDO Ver. : Ver. 1.3 = 3b'011
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] | (_BIT6 | _BIT5);

                // [27:24] Device Cap.
#if((_EMB_TYPE_C_1_USB_SPEED == _USB_3_GEN1) || (_EMB_TYPE_C_1_USB_SPEED == _USB_3_GEN2))
                // USB3.2/ USB2.0 = 4b'0101
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] | (_BIT2 | _BIT0);
#elif(_EMB_TYPE_C_1_USB_SPEED == _USB_BILLBOARD_ONLY)
                // USB2.0 (Billboard only) = 4b'0010
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] | (_BIT1);
#elif(_EMB_TYPE_C_1_USB_SPEED == _USB_2)
                // USB2.0 = 4b'0001
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] | (_BIT0);
#endif

                // [23:22] Connector Type (Legacy) : Shall be set to 00b, [21:16] Reserved = 0x00
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 2] = 0x00;

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
                // [15:11] Reserved = 0x00, [10:8] Vconn Power
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 3] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 3] | (_VCONN_POW);

#if(_VCONN_REQUIRE == _TRUE)
                // [7] Vconn Required
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] | (_BIT7);
#endif

                if(GET_TYPE_C_1_PD_SNK_CAP_CUR(0) != 0x00)
                {
                    // [6] Vbus Required = TRUE when 1st 5V Sink Cap Need More than 0mA
                    g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] | (_BIT6);
                }

                // [5:3] Alternate Modes;
#if(_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE)
                // [5] Supports Alternate Modes that do not Reconfigure the Signals on the [USB Type-C 2.0] Connector
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] | (_BIT5);
#endif
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
                // [4] Supports Alternate Modes that Reconfigure the Signals on the [USB Type-C 2.0] Connector
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] | (_BIT4);
#endif
                // [3] Supports TBT3 Alternate Mode (Need to Add in the Future)
#endif

                // [2:0] USB Highest Speed
#if(_EMB_TYPE_C_1_USB_SPEED == _USB_3_GEN2)
                // USB3.2 Gen2 = 3b'010
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] | (_BIT1);
#elif(_EMB_TYPE_C_1_USB_SPEED == _USB_3_GEN1)
                // USB3.2 Gen1 = 3b'001
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] | (_BIT0);
#elif(_EMB_TYPE_C_1_USB_SPEED == _USB_2)
                // USB2.0 = 3b'000
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] | (0x00);
#endif
                ucIndex = ucIndex + 8;
            }

            if(GET_TYPE_C_1_PD_DFP_PRODUCT_TYPE() != _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED)
            {
                // -------- Data Obj 6 : DFP VDO ---------
                // [31:29] DFP VDO Ver. : Ver. 1.2 = 3b'010
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] | (_BIT6);

                // [26:24] Host Cap.
#if((_EMB_TYPE_C_1_USB_SPEED == _USB_3_GEN1) || (_EMB_TYPE_C_1_USB_SPEED == _USB_3_GEN2))
                // USB3.2/ USB2.0 = 3b'011
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] | (_BIT1 | _BIT0);
#elif(_EMB_TYPE_C_1_USB_SPEED == _USB_2)
                // USB2.0 = 3b'001
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 1] | (_BIT0);
#endif

                // [23:22] Connector Type (Legacy) : Shall be set to 00b
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 2] = 0x00;

                // [4:0] Port Number: Port 0 = 5b'00001
                g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] = g_pucTypeC1PdDataObject_EXINT[ucIndex + 4] | (_BIT0);
            }
            break;

        case _PD_VERSION_2_0:
        default:

            // PD Version = 2.0, Products with USB Hub IC, Product Type UFP choose Hub;
            // Products without USB Hub IC, Product Type UFP choose Peripheral.

            // -------- Data Obj 1 : ID Header ---------
            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // |Host|Dev.|      UFP     |Mode|   DFP   |
#if((_EMB_TYPE_C_1_USB_ROLE == _TYPE_C_USB_HOST_ONLY) || (_EMB_TYPE_C_1_USB_ROLE == _TYPE_C_USB_HOST_DEVICE))
            g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT7);
#endif

#if((_EMB_TYPE_C_1_USB_ROLE == _TYPE_C_USB_DEVICE_ONLY) || (_EMB_TYPE_C_1_USB_ROLE == _TYPE_C_USB_HOST_DEVICE) || (_EMB_TYPE_C_1_USB_SPEED == _USB_BILLBOARD_ONLY))
            g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT6);
#endif

#if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)
            // For the PD2.0 version, Discover_ID_ACK Responds to AMA
            // (UFP Product Type = AMA) does not Meet the Latest Standard. This setting is for Compatibility.
            // UFP Product Type = 3b'101 (AMA)
            g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT5 | _BIT3);
#else
            // UFP Product Type = 3b'000 Undefined/ 3b'001 PDUSB Hub/ 3b'010 PDUSB Peripheral
            if(GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED)
            {
                g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] & (~(_BIT5 | _BIT4 | _BIT3));
            }
            else if(GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_HUB)
            {
                g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT3);
            }
            else if(GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE() == _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL)
            {
                g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT4);
            }
#endif
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            g_pucTypeC1PdDataObject_EXINT[4] = g_pucTypeC1PdDataObject_EXINT[4] | (_BIT2);
#endif

            // [15:0] = USB Vender ID 0x0BDA (RealTek)
            g_pucTypeC1PdDataObject_EXINT[6] = _USB_VENDOR_ID_H;
            g_pucTypeC1PdDataObject_EXINT[7] = _USB_VENDOR_ID_L;

            // -------- Data Obj 2 : Cert State (XID)
            g_pucTypeC1PdDataObject_EXINT[8] = _USB_XID_BYTE3;
            g_pucTypeC1PdDataObject_EXINT[9] = _USB_XID_BYTE2;
            g_pucTypeC1PdDataObject_EXINT[10] = _USB_XID_BYTE1;
            g_pucTypeC1PdDataObject_EXINT[11] = _USB_XID_BYTE0;

            // -------- Data Obj 3 : Product -----------
            // [31:16] bcd Device = 0x0300, [15:0] Product ID = _USB_PRODUCT_ID_H / _USB_PRODUCT_ID_L
            g_pucTypeC1PdDataObject_EXINT[12] = _USB_PRODUCT_ID_H;
            g_pucTypeC1PdDataObject_EXINT[13] = _USB_PRODUCT_ID_L;
            g_pucTypeC1PdDataObject_EXINT[14] = 0x03;
            g_pucTypeC1PdDataObject_EXINT[15] = 0x00;

#if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)
            // -------- Data Obj 4 : Alt. Mode ---------
            // [31:28] HW Ver. = 0, [27:24] FW Ver. = 0
            g_pucTypeC1PdDataObject_EXINT[16] = g_pucTypeC1PdDataObject_EXINT[16] | (_PD_HW_VERSION << 4);
            g_pucTypeC1PdDataObject_EXINT[16] = g_pucTypeC1PdDataObject_EXINT[16] | (_PD_FW_VERSION);

            // [23:16] Reserved = 0x00
            g_pucTypeC1PdDataObject_EXINT[17] = 0x00;

            // [15:8] Reserved = 0x00
            g_pucTypeC1PdDataObject_EXINT[18] = 0x00;

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            // [7:5] Vconn Power
            g_pucTypeC1PdDataObject_EXINT[19] = g_pucTypeC1PdDataObject_EXINT[19] | (_VCONN_POW << 5);

#if(_VCONN_REQUIRE == _TRUE)
            // [4] Vconn Required
            g_pucTypeC1PdDataObject_EXINT[19] = g_pucTypeC1PdDataObject_EXINT[19] | (_BIT4);
#endif

            if(GET_TYPE_C_1_PD_SNK_CAP_CUR(0) != 0x00)
            {
                // [3] Vbus Required = TRUE when 1st 5V Sink Cap Need More than 0mA
                g_pucTypeC1PdDataObject_EXINT[19] = g_pucTypeC1PdDataObject_EXINT[19] | (_BIT3);
            }
#endif // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)

            // [2:0] USB Highest Speed
#if(_EMB_TYPE_C_1_USB_SPEED == _USB_BILLBOARD_ONLY)
            // Billboard only = 3b'011
            g_pucTypeC1PdDataObject_EXINT[19] = g_pucTypeC1PdDataObject_EXINT[19] | (_BIT1 | _BIT0);
#elif(_EMB_TYPE_C_1_USB_SPEED == _USB_3_GEN2)
            // USB3.2 Gen2 = 3b'010
            g_pucTypeC1PdDataObject_EXINT[19] = g_pucTypeC1PdDataObject_EXINT[19] | (_BIT1);
#elif(_EMB_TYPE_C_1_USB_SPEED == _USB_3_GEN1)
            // USB3.2 Gen1 = 3b'001
            g_pucTypeC1PdDataObject_EXINT[19] = g_pucTypeC1PdDataObject_EXINT[19] | (_BIT0);
#elif(_EMB_TYPE_C_1_USB_SPEED == _USB_2)
            // USB2.0 = 3b'000
            g_pucTypeC1PdDataObject_EXINT[19] = g_pucTypeC1PdDataObject_EXINT[19] | (0x00);
#endif // End of #if(_EMB_TYPE_C_1_USB_SPEED == _USB_BILLBOARD_ONLY)
#endif // End of #if(_TYPE_C_EMB_PD_2_0_UFP_PRODUCT_TYPE_AMA == _TRUE)
            break;
    }
}

//--------------------------------------------------
// Description  : Send Soft Reset Message
// Input Value  : enumPacketType : _SOP_PKT
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSendSoftRst_EXINT0(EnumTypeCPDPacketType enumPacketType)
{
    // 1. Clear Flags & Reset PRL Layer [0x6B03]
    CLR_TYPE_C_1_PD_TRANSMIT_RESULT();
    ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~_BIT0, 0x00);

    // 2. Construct Msg.
    ScalerTypeC1PdConstructSoftReset_EXINT0(enumPacketType);

    // 3. Enable PRL Layer & Release Message ID Reset [0x6B03/E4]
    ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P6B_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Start Disable Rcv Msg.
    ScalerTypeC1PdRxIntControl_EXINT0(_DISABLE);

    // 4. Send Msg. (Interrupt Does Not Check Overwrite and Disable Rcv Msg.)
    // [0x6BDC] Clear IRQs
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
    ScalerSetBit_EXINT(P6B_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
    ScalerSetBit_EXINT(P6B_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

    // [0x6BDD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
    ScalerSetBit_EXINT(P6B_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

    // [0x6BDA] Start Transmit ([1] = 0, Wait For GoodCRC Response After Transmission)
    ScalerSetBit_EXINT(P6B_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

    // [0x6BE5] Set Tx FIFO [2:1] Spec Ver = 2.0, For PD2.0/3.0 CTS
    ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (_BIT1));
}

//--------------------------------------------------
// Description  : Construct Soft Reset Msg. in Interrupt
// Input Value  : enumPacketType : _SOP_PKT
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdConstructSoftReset_EXINT0(EnumTypeCPDPacketType enumPacketType)
{
    // 1. [0x6BE0] Set Transmit Type : b'00 = Preamble + SOP + Msg. Header + Data + CRC + EOP
    ScalerSetBit_EXINT(P6B_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), 0x00);

    // 2. [0x6BE0] Set Packet Type [5:3]
    ScalerSetBit_EXINT(P6B_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), ((enumPacketType << 3) & (_BIT5 | _BIT4 | _BIT3)));

    // 3. [0x6BE5] Fill in Msg. Header0
    // [7]   Msg. Header[15]     : Extended Field = 0
    // [6:4] Msg. Header[14:12]  : Number of Data Object = 0
    ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // [3] Msg. Header[8]  : Power Role
    // [0] Msg. Header[5]  : Data Role
    if(enumPacketType == _PD_SOP_PKT)
    {
        // [3] Power Role / [2:1] Spec Version / [0] Data Role
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, GET_TYPE_C_1_PD_POWER_ROLE() << 3);
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_TYPE_C_1_PD_SPEC_VER() << 1);
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_TYPE_C_1_PD_DATA_ROLE());

        // Reset Message ID [0x6BE4]
        ScalerSetBit_EXINT(P6B_E4_TX_MSG_ID_RST, ~_BIT2, 0x00);
    }
    else
    {
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, (BYTE)_PD_DEVICE << 3);
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_TYPE_C_1_PD_CBL_SPEC_VER() << 1);
        ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);

        if(enumPacketType == _PD_SOP_P_PKT)
        {
            // Reset Message ID [0x6BE4]
            ScalerSetBit_EXINT(P6B_E4_TX_MSG_ID_RST, ~_BIT1, 0x00);
        }
        else if(enumPacketType == _PD_SOP_PP_PKT)
        {
            // Reset Message ID [0x6BE4]
            ScalerSetBit_EXINT(P6B_E4_TX_MSG_ID_RST, ~_BIT0, 0x00);
        }
    }

    // [0x6BE6] Fill in Msg. Header1
    // [4:0]  Msg. Header[4:0] : Command Type = b'0_1101
    ScalerSetBit_EXINT(P6B_E6_TX_FIFO_MSG_HEADER1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
}

//--------------------------------------------------
// Description  : Initiate Hard Reset When Error Happens in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSendHardRst_EXINT0(void)
{
    if(GET_TYPE_C_1_PD_HARD_RST_CNT() <= _MAX_HARD_RST_CNT)
    {
        // Start Disable Rcv Msg.
        ScalerTypeC1PdRxIntControl_EXINT0(_DISABLE);

        // 1. [0x6BE0] Select Transmission Mode [7:6] : b'01 = Preamble + SOP
        ScalerSetBit_EXINT(P6B_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), _BIT6);

        // 2. [0x6BE0] Set Packet Type [5:3] : b'011 = HARD_RESET
        ScalerSetBit_EXINT(P6B_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

        // 3. [0x6BDC] Clear IRQs
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
        ScalerSetBit_EXINT(P6B_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
        ScalerSetBit_EXINT(P6B_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

        // 4. [0x6BDA] Start Transmit
        ScalerSetBit_EXINT(P6B_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));
        ADD_TYPE_C_1_PD_HARD_RST_CNT();

        // 5. Process Hard Reset
        ScalerTypeC1PdProcHardRst_EXINT0();
    }
    else
    {
        // Do Type-C Error Recovery
        SET_TYPE_C_1_CC_ERROR_RECOVERY();
    }
}

//--------------------------------------------------
// Description  : Process Hard Reset When Hard Reset Sent/Rcv. in Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdProcHardRst_EXINT0(void)
{
    // Clear Hard Reset Turn Off Power Flag (Set When 1.Power Already Turned Off to vSafe0v for SRC 2.Vbus Already Not vSafe5v)
    CLR_TYPE_C_1_PD_HRST_PWR_OFF();

    if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
    {
#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
        // Adjust Power (Turn Off Vbus)
        ScalerTypeC1PmicSetting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
        // Enable Vbus Discharge
        ScalerTypeC1PmicVbusDischarge_EXINT0(_ON);
#endif

        // [Eizo] SIC437A Customized Power Control : Send/Receive Hard Reset
        ScalerTypeC1PmicSic437aHardRstStartProc_EXINT0(_TYPE_C_POWER_SRC);

#if(_EMB_TYPE_C_1_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
        // Tool Not Show Warning UI when We Turn Off Vbus
        ScalerTypeC1CcToolWarningUIControl_EXINT0(_DISABLE);
#endif
#else
        // Source can Start Changing Power After tSrcTransition = 25-35 ms
        ScalerTimerWDActivateTimerEvent_EXINT0(_SRC_ADJUST_POWER_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER);
#endif
    }
    else
    {
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
        // 1. Turn Off Power Draw, Vbus should be drive to vSafe0V by Source (PD 7.1.5). Disable Detect Sink OVP/UVP
        ScalerTypeC1PmicSetting_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
#endif

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
        // [FW Sol. for _TYPE_C_5B_LS_ADC_GEN_1] Write 1 Clear 5Bit LS_ADC Vbus Off IRQ and Disable IRQ_EN
        ScalerTypeCAdcOnOffCompIntControl_EXINT0(_TYPE_C_CHANNEL_1_VMON, _OFF, _DISABLE);
#else
        // 2. Turn Off Type-C Unattach Vbus Detection
        ScalerTypeC1CcVbusDetCtrl_EXINT0(_DISABLE);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
        // [Eizo] SIC437A Customized Power Control : Send/Receive Hard Reset
        ScalerTypeC1PmicSic437aHardRstStartProc_EXINT0(_TYPE_C_POWER_SNK);
#endif
#endif

        ScalerTypeC1PdActiveTimerEvent_EXINT0(_SNK_HARD_RST_TIMER, _SCALER_TIMER_EVENT_PD_1_SNK_HARD_RST_TIMEOUT);
    }

    // Turn Off Vconn, If Already Turned On
    if(GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC)
    {
        ScalerTypeC1CcVconnControl_EXINT0(_OFF);
    }

    // [0x6B02] Disable PHY Layer BMC Tx/Rx
    ScalerSetBit_EXINT(P6B_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), 0x00);

    // [0x6B43] Clear and Disable Hard Reset IRQ
    ScalerSetBit_EXINT(P6B_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT3);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_SEND_HARD_RST);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);

    // State Transition
    SET_TYPE_C_1_PD_FW_STATE(_PD_HARDRESET);
    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);
    SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_STATE_NONE);
}

//--------------------------------------------------
// Description  : Filter Un-wanted Msg. Before Selecting FIFO to Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdRxInvalidPktFilter_EXINT0(void)
{
    // Un-wanted Msg : Invalid Packet Type, CRC Error, Abnormal Msg, Msg ID Error, CRC Resp Fail
    // Check FIFO0
    if(ScalerGetBit_EXINT(P6B_42_RX_FIFO_GENERAL_INFO, _BIT2) == _BIT2)
    {
        if((ScalerGetByte_EXINT(P6B_51_RX_FIFO0_RCV_ERR_INT) & (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0)) != 0x00)
        {
#if(_HW_PD_FUNCTION_GEN == _PD_FUNCTION_GEN_1)
            // FW Solution : When goodcrc_fail_irq && tx_ch_busy_irq Triggered, Reset Phy & Protocol FSM to Prevent HW Issue. (MM1GENERAL-2329)
            if((ScalerGetBit_EXINT(P6B_51_RX_FIFO0_RCV_ERR_INT, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P6B_DB_TX_PHY_TRANS_INT, _BIT1) == _BIT1))
            {
                // Reset Phy & Protocol FSM
                ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT0), 0x00);
                ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
            }
#endif

            ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_0);
        }
    }

    // Check FIFO1
    if(ScalerGetBit_EXINT(P6B_42_RX_FIFO_GENERAL_INFO, _BIT1) == _BIT1)
    {
        if((ScalerGetByte_EXINT(P6B_71_RX_FIFO1_RCV_ERR_INT) & (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0)) != 0x00)
        {
#if(_HW_PD_FUNCTION_GEN == _PD_FUNCTION_GEN_1)
            // FW Solution : When goodcrc_fail_irq && tx_ch_busy_irq Triggered, Reset Phy & Protocol FSM to Prevent HW Issue. (MM1GENERAL-2329)
            if((ScalerGetBit_EXINT(P6B_71_RX_FIFO1_RCV_ERR_INT, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P6B_DB_TX_PHY_TRANS_INT, _BIT1) == _BIT1))
            {
                // Reset Phy & Protocol FSM
                ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT0), 0x00);
                ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
            }
#endif

            ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_1);
        }
    }

    // Check FIFO2
    if(ScalerGetBit_EXINT(P6B_42_RX_FIFO_GENERAL_INFO, _BIT0) == _BIT0)
    {
        if((ScalerGetByte_EXINT(P6B_91_RX_FIFO2_RCV_ERR_INT) & (_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT0)) != 0x00)
        {
#if(_HW_PD_FUNCTION_GEN == _PD_FUNCTION_GEN_1)
            // FW Solution : When goodcrc_fail_irq && tx_ch_busy_irq Triggered, Reset Phy & Protocol FSM to Prevent HW Issue. (MM1GENERAL-2329)
            if((ScalerGetBit_EXINT(P6B_91_RX_FIFO2_RCV_ERR_INT, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P6B_DB_TX_PHY_TRANS_INT, _BIT1) == _BIT1))
            {
                // Reset Phy & Protocol FSM
                ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT0), 0x00);
                ScalerSetBit_EXINT(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
            }
#endif

            ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_2);
        }
    }
}

//--------------------------------------------------
// Description  : Choose One FIFO to Process (If Multiple FIFO Have Msg., Do The Arbitration Mechanism)
// Input Value  : None
// Output Value : FIFO Selected After Arbitration (_PD_RX_FIFO_0 / _PD_RX_FIFO_1 / _PD_RX_FIFO_2)
//--------------------------------------------------
EnumTypeCRxFifoIndex ScalerTypeC1PdRxFifoSelect_EXINT0(void)
{
    EnumTypeCRxFifoIndex enumTargetFifo = _PD_RX_FIFO_RSV;
    BYTE ucNoneEmptyFifo = ScalerGetBit_EXINT(P6B_42_RX_FIFO_GENERAL_INFO, (_BIT2 | _BIT1 | _BIT0));

    if((ucNoneEmptyFifo & _BIT2) == _BIT2)
    {
        // If FIFO_0 (_BIT2) Has Msg, Check FIFO_1 (_BIT1) & FIFO_2 (_BIT0)
        if((ucNoneEmptyFifo & _BIT1) == _BIT1)
        {
            // Both FIFO_0 and FIFO_1 Have Msg, Check Msg Type
            if((ScalerGetByte_EXINT(P6B_54_RX_FIFO0_RCV_SOP)) == (ScalerGetByte_EXINT(P6B_74_RX_FIFO1_RCV_SOP)))
            {
                // Check whether Both FIFO_0 and FIFO_1 are "Data & VDM Msg" or not.
                if(((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) &&
                   ((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) &&
                   (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM) &&
                   (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))
                {
                    // If Yes, Discard Old Msg FIFO, and Use Lastest Msg FIFO.
                    if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_1);
                        enumTargetFifo = _PD_RX_FIFO_0;
                    }
                    else
                    {
                        ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_0);
                        enumTargetFifo = _PD_RX_FIFO_1;
                    }
                }
                // Check wether One of FIFO0 and FIFO1 is VDM Msg or not.
                else if((((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)) ||
                        (((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)))
                {
                    if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        if(!((((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO0 = Lastest Msg) && (FIFO0 = PD Msg)), Discard FIFO1, and Use FIFO0.
                            ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_1);
                            enumTargetFifo = _PD_RX_FIFO_0;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            enumTargetFifo = _PD_RX_FIFO_1;
                        }
                    }
                    else if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_1)
                    {
                        if(!((((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO1 = Lastest Msg) && (FFIFO1 = PD Msg)), Discard FIFO0, and Use FIFO1.
                            ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_0);
                            enumTargetFifo = _PD_RX_FIFO_1;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            enumTargetFifo = _PD_RX_FIFO_0;
                        }
                    }
                }
                else
                {
                    // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                    if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        enumTargetFifo = _PD_RX_FIFO_1;
                    }
                    else
                    {
                        enumTargetFifo = _PD_RX_FIFO_0;
                    }
                }
            }
            else
            {
                // FIFO_0 and FIFO_1 Have Diff. Type of Msg, SOP Msg Has Top Priority
                if(ScalerGetByte_EXINT(P6B_54_RX_FIFO0_RCV_SOP) == 0x01)
                {
                    enumTargetFifo = _PD_RX_FIFO_0;
                }
                else
                {
                    enumTargetFifo = _PD_RX_FIFO_1;
                }
            }
        }
        else if((ucNoneEmptyFifo & _BIT0) == _BIT0)
        {
            // Both FIFO_0 & FIFO_2 Have SOP Msg, Chek Msg Type
            if((ScalerGetByte_EXINT(P6B_54_RX_FIFO0_RCV_SOP)) == (ScalerGetByte_EXINT(P6B_94_RX_FIFO2_RCV_SOP)))
            {
                // Check whether Both FIFO_0 and FIFO_2 are "Data & VDM Msg" or not.
                if(((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) &&
                   ((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) &&
                   (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM) &&
                   (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))
                {
                    // If Yes, Discard Old Msg FIFO, and Use Lastest Msg FIFO.
                    if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_2);
                        enumTargetFifo = _PD_RX_FIFO_0;
                    }
                    else
                    {
                        ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_0);
                        enumTargetFifo = _PD_RX_FIFO_2;
                    }
                }
                // Check wether One of FIFO0 and FIFO2 is VDM Msg or not.
                else if((((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)) ||
                        (((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)))
                {
                    if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        if(!((((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_0 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_0 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO0 = Lastest Msg) && (FIFO0 = PD Msg)), Discard FIFO2, and Use FIFO0.
                            ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_2);
                            enumTargetFifo = _PD_RX_FIFO_0;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            enumTargetFifo = _PD_RX_FIFO_2;
                        }
                    }
                    else if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_2)
                    {
                        if(!((((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO2 = Lastest Msg) && (FIFO2 = PD Msg)), Discard FIFO0, and Use FIFO2.
                            ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_0);
                            enumTargetFifo = _PD_RX_FIFO_2;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            enumTargetFifo = _PD_RX_FIFO_0;
                        }
                    }
                }
                else
                {
                    // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                    if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_0)
                    {
                        enumTargetFifo = _PD_RX_FIFO_2;
                    }
                    else
                    {
                        enumTargetFifo = _PD_RX_FIFO_0;
                    }
                }
            }
            else
            {
                // FIFO_0 and FIFO_2 Have Diff. Type of Msg, SOP Msg Has Top Priority
                if(ScalerGetByte_EXINT(P6B_54_RX_FIFO0_RCV_SOP) == 0x01)
                {
                    enumTargetFifo = _PD_RX_FIFO_0;
                }
                else
                {
                    enumTargetFifo = _PD_RX_FIFO_2;
                }
            }
        }
        else
        {
            // Only FIFO_0 Has Msg
            enumTargetFifo = _PD_RX_FIFO_0;
        }
    }
    else if((ucNoneEmptyFifo & _BIT1) == _BIT1)
    {
        // If FIFO_0 Does NOT Has Msg, FIFO1 Has Msg (_BIT1), Check FIFO_2
        if((ucNoneEmptyFifo & _BIT0) == _BIT0)
        {
            // Both FIFO_1 & FIFO_2 Have SOP Msg, Chek Msg Type
            if((ScalerGetByte_EXINT(P6B_74_RX_FIFO1_RCV_SOP)) == (ScalerGetByte_EXINT(P6B_94_RX_FIFO2_RCV_SOP)))
            {
                // Check whether Both FIFO_1 and FIFO_2 are "Data & VDM Msg" or not.
                if(((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) &&
                   ((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) &&
                   (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM) &&
                   (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))
                {
                    // If Yes, Discard Old Msg FIFO, and Use Lastest Msg FIFO.
                    if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_1)
                    {
                        ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_2);
                        enumTargetFifo = _PD_RX_FIFO_1;
                    }
                    else
                    {
                        ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_1);
                        enumTargetFifo = _PD_RX_FIFO_2;
                    }
                }
                // Check wether One of FIFO1 and FIFO2 is VDM Msg or not.
                else if((((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)) ||
                        (((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM)))
                {
                    if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_1)
                    {
                        if(!((((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_1 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_1 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO1 = Lastest Msg) && (FIFO1 = PD Msg)), Discard FIFO2, and Use FIFO1.
                            ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_2);
                            enumTargetFifo = _PD_RX_FIFO_1;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            enumTargetFifo = _PD_RX_FIFO_2;
                        }
                    }
                    else if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_2)
                    {
                        if(!((((ScalerGetBit_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (_PD_RX_FIFO_2 * 0x20), (_BIT3))) == _BIT3) && (((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (_PD_RX_FIFO_2 * 0x20)) & (0x1F)) | _PD_CMD_TYPE_DATA) == _PD_CMD_VDM))))
                        {
                            // If ((FIFO2 = Lastest Msg) && (FFIFO2 = PD Msg)), Discard FIFO1, and Use FIFO2.
                            ScalerTypeC1PdRxFifoClear_EXINT0(_PD_RX_FIFO_1);
                            enumTargetFifo = _PD_RX_FIFO_2;
                        }
                        else
                        {
                            // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                            enumTargetFifo = _PD_RX_FIFO_1;
                        }
                    }
                }
                else
                {
                    // Otherwise, Use Old Msg FIFO, and Not Clr Lastest Msg FIFO
                    if((ScalerGetByte_EXINT(P6B_40_RX_FIFO_CTRL) & (_BIT1 | _BIT0)) == _PD_RX_FIFO_1)
                    {
                        enumTargetFifo = _PD_RX_FIFO_2;
                    }
                    else
                    {
                        enumTargetFifo = _PD_RX_FIFO_1;
                    }
                }
            }
            else
            {
                // FIFO_1 and FIFO_2 Have Diff. Type of Msg, SOP Msg Has Top Priority
                if(ScalerGetByte_EXINT(P6B_74_RX_FIFO1_RCV_SOP) == 0x01)
                {
                    enumTargetFifo = _PD_RX_FIFO_1;
                }
                else
                {
                    enumTargetFifo = _PD_RX_FIFO_2;
                }
            }
        }
        else
        {
            // Only FIFO_1 Has Message
            enumTargetFifo = _PD_RX_FIFO_1;
        }
    }
    else
    {
        // Only FIFO_2 Has Message
        enumTargetFifo = _PD_RX_FIFO_2;
    }

    return enumTargetFifo;
}

//--------------------------------------------------
// Description  : Filter Un-wanted Msg. Before Selecting FIFO to Process
// Input Value  : enumRxProcFifo : _PD_RX_FIFO_0 / _PD_RX_FIFO_1 / _PD_RX_FIFO_2
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdRxFifoMsgDecode_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo)
{
    CLR_TYPE_C_1_PD_RCV_MSG();
    CLR_TYPE_C_1_PD_RCV_VDM_CMD();

    switch(ScalerGetByte_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT + (enumRxProcFifo * 0x20)) & (_BIT5 | _BIT3 | _BIT1))
    {
        case _BIT5:

            // [0x6B50] [5] Control Message IRQ
            SET_TYPE_C_1_PD_RCV_MSG(_PD_CMD_TYPE_CTRL | ScalerGetBit_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20), 0x1F));

            break;

        case _BIT3:

            // [0x6B50] [3] Data Message IRQ
            SET_TYPE_C_1_PD_RCV_MSG(_PD_CMD_TYPE_DATA | ScalerGetBit_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20), 0x1F));

            // Read Data Objects From "Rx FIFO" to "g_pucTypeC1PdDataObject_EXINT[0-28]"
            ScalerTypeC1PdRxReadDataObj_EXINT0(enumRxProcFifo);

            if(GET_TYPE_C_1_PD_RCV_MSG() == _PD_CMD_VDM)
            {
                // Get Standard & Vender ID : VDM Header[31:16]
                SET_TYPE_C_1_PD_VDM_SVID_H(g_pucTypeC1PdDataObject_EXINT[0]);
                SET_TYPE_C_1_PD_VDM_SVID_L(g_pucTypeC1PdDataObject_EXINT[1]);

                // Check If Rcv. an Structured VDM Message
                if((g_pucTypeC1PdDataObject_EXINT[2] & _BIT7) == _BIT7)
                {
                    // Set VDM Type = Structured VDM
                    SET_TYPE_C_1_PD_RCV_VDM_TYPE(_PD_STRUCTURED_VDM);

                    // Get VDM Object Position : VDM Header[10:8]
                    SET_TYPE_C_1_PD_VDM_OBJ_POS(g_pucTypeC1PdDataObject_EXINT[2] & (_BIT2 | _BIT1 | _BIT0));

                    // Get VDM Command Type : VDM Header[7:0] ([7:6] VDM CMD Type  [4:0] VDM CMD)
                    SET_TYPE_C_1_PD_RCV_VDM_CMD(g_pucTypeC1PdDataObject_EXINT[3]);
                }
                else
                {
                    // Set VDM Type = Unstructured VDM
                    SET_TYPE_C_1_PD_RCV_VDM_TYPE(_PD_UNSTRUCTURED_VDM);
                }
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _BIT1:

            SET_TYPE_C_1_PD_RCV_MSG(_PD_CMD_TYPE_EXT | ScalerGetBit_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20), 0x1F));

            // Read Data Objects From "Rx FIFO" to "g_pucTypeC1PdDataObject_EXINT[0-28]"
            ScalerTypeC1PdRxReadDataObj_EXINT0(enumRxProcFifo);

            // Check If This Ext Msg is Chunked : Ext Message Header [15]
            SET_TYPE_C_1_PD_CHUNKED_MESSAGE((g_pucTypeC1PdDataObject_EXINT[0] >> 7));

            // Get Ext Msg Chunk Number
            SET_TYPE_C_1_PD_CHUNK_NUMBER((g_pucTypeC1PdDataObject_EXINT[0] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3);

            // Get Ext Msg Chunk Request
            SET_TYPE_C_1_PD_CHUNK_REQUEST((g_pucTypeC1PdDataObject_EXINT[0] >> 2));

            // Get Ext Msg Total Size
            SET_TYPE_C_1_PD_EXT_MSG_DATA_SIZE(((WORD)(g_pucTypeC1PdDataObject_EXINT[0] & _BIT0) << 8) | (WORD)(g_pucTypeC1PdDataObject_EXINT[1]));

            break;
#endif

        default:

#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
            if((ScalerGetByte_EXINT(P6B_56_RX_FIFO0_MSG_HEADER0 + (enumRxProcFifo * 0x20)) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x00)
            {
                SET_TYPE_C_1_PD_RCV_MSG(_PD_CMD_TYPE_CTRL | ScalerGetBit_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20), 0x1F));
            }
            else if(((ScalerGetByte_EXINT(P6B_56_RX_FIFO0_MSG_HEADER0 + (enumRxProcFifo * 0x20)) & _BIT7) == _BIT7) && ((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20)) & (0x1F)) == 0x1F))
            {
                SET_TYPE_C_1_PD_RCV_MSG(_PD_CMD_CHUNK_TEST);

                // Read Data Objects From "Rx FIFO" to "g_pucTypeC1PdDataObject_EXINT[0-28]"
                ScalerTypeC1PdRxReadDataObj_EXINT0(enumRxProcFifo);

                // Check If This Ext Msg is Chunked : Ext Message Header [15]
                SET_TYPE_C_1_PD_CHUNKED_MESSAGE((g_pucTypeC1PdDataObject_EXINT[0] >> 7));

                // Get Ext Msg Chunk Number
                SET_TYPE_C_1_PD_CHUNK_NUMBER((g_pucTypeC1PdDataObject_EXINT[0] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3);

                // Get Ext Msg Chunk Request
                SET_TYPE_C_1_PD_CHUNK_REQUEST((g_pucTypeC1PdDataObject_EXINT[0] >> 2));

                // Get Ext Msg Total Size
                SET_TYPE_C_1_PD_EXT_MSG_DATA_SIZE(((WORD)(g_pucTypeC1PdDataObject_EXINT[0] & _BIT0) << 8) | (WORD)(g_pucTypeC1PdDataObject_EXINT[1]));
            }
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
            else if(((ScalerGetByte_EXINT(P6B_56_RX_FIFO0_MSG_HEADER0 + (enumRxProcFifo * 0x20)) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == _BIT4) && ((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20)) & (0x1F)) == 0x0A))
            {
                SET_TYPE_C_1_PD_RCV_MSG(_PD_CMD_EPR_MODE);

                // Read Data Objects From "Rx FIFO" to "g_pucTypeC1PdDataObject_EXINT[0-28]"
                ScalerTypeC1PdRxReadDataObj_EXINT0(enumRxProcFifo);
            }
            else if(((ScalerGetByte_EXINT(P6B_56_RX_FIFO0_MSG_HEADER0 + (enumRxProcFifo * 0x20)) & _BIT7) == _BIT7) && ((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20)) & (0x1F)) == 0x11))
            {
                SET_TYPE_C_1_PD_RCV_MSG(_PD_CMD_EPR_SRC_CAP);

                // Read Data Objects From "Rx FIFO" to "g_pucTypeC1PdDataObject_EXINT[0-28]"
                ScalerTypeC1PdRxReadDataObj_EXINT0(enumRxProcFifo);

                // Check If This Ext Msg is Chunked : Ext Message Header [15]
                SET_TYPE_C_1_PD_CHUNKED_MESSAGE((g_pucTypeC1PdDataObject_EXINT[0] >> 7));

                // Get Ext Msg Chunk Number
                SET_TYPE_C_1_PD_CHUNK_NUMBER((g_pucTypeC1PdDataObject_EXINT[0] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3);

                // Get Ext Msg Chunk Request
                SET_TYPE_C_1_PD_CHUNK_REQUEST((g_pucTypeC1PdDataObject_EXINT[0] >> 2));

                // Get Ext Msg Total Size
                SET_TYPE_C_1_PD_EXT_MSG_DATA_SIZE(((WORD)(g_pucTypeC1PdDataObject_EXINT[0] & _BIT0) << 8) | (WORD)(g_pucTypeC1PdDataObject_EXINT[1]));
            }
            else if(((ScalerGetByte_EXINT(P6B_56_RX_FIFO0_MSG_HEADER0 + (enumRxProcFifo * 0x20)) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == _BIT5) && ((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20)) & (0x1F)) == 0x09))
            {
                SET_TYPE_C_1_PD_RCV_MSG(_PD_CMD_EPR_REQUEST);

                // Read Data Objects From "Rx FIFO" to "g_pucTypeC1PdDataObject_EXINT[0-28]"
                ScalerTypeC1PdRxReadDataObj_EXINT0(enumRxProcFifo);
            }
            else if(((ScalerGetByte_EXINT(P6B_56_RX_FIFO0_MSG_HEADER0 + (enumRxProcFifo * 0x20)) & _BIT7) == _BIT7) && ((ScalerGetByte_EXINT(P6B_57_RX_FIFO0_MSG_HEADER1 + (enumRxProcFifo * 0x20)) & (0x1F)) == 0x10))
            {
                SET_TYPE_C_1_PD_RCV_MSG(_PD_CMD_EXTENDED_CONTROL);

                // Read Data Objects From "Rx FIFO" to "g_pucTypeC1PdDataObject_EXINT[0-28]"
                ScalerTypeC1PdRxReadDataObj_EXINT0(enumRxProcFifo);

                // Check If This Ext Msg is Chunked : Ext Message Header [15]
                SET_TYPE_C_1_PD_CHUNKED_MESSAGE((g_pucTypeC1PdDataObject_EXINT[0] >> 7));

                // Get Ext Msg Chunk Number
                SET_TYPE_C_1_PD_CHUNK_NUMBER((g_pucTypeC1PdDataObject_EXINT[0] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) >> 3);

                // Get Ext Msg Chunk Request
                SET_TYPE_C_1_PD_CHUNK_REQUEST((g_pucTypeC1PdDataObject_EXINT[0] >> 2));

                // Get Ext Msg Total Size
                SET_TYPE_C_1_PD_EXT_MSG_DATA_SIZE(((WORD)(g_pucTypeC1PdDataObject_EXINT[0] & _BIT0) << 8) | (WORD)(g_pucTypeC1PdDataObject_EXINT[1]));
            }
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
            else
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
#endif  // #if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
            {
                // TO DO Alex : Not a Good Coding Style...
                SET_TYPE_C_1_PD_RCV_MSG(_PD_CMD_UNDEFINED);
            }

            break;
    }
}

//--------------------------------------------------
// Description  : Read Data Object from Rx FIFO to g_pucTypeC1PdDataObject_EXINT[0~28]
// Input Value  : enumRxProcFifo : _RX_FIFO_0 / _RX_FIFO_1 / _RX_FIFO_2
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdRxReadDataObj_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo)
{
    // FIFO_0 Buffer : P6B_59_RX_FIFO0_ADDR/P6B_5A_RX_FIFO0_DATA, FIFO_1 Buffer : P6B_79_RX_FIFO1_ADDR/P6B_7A_RX_FIFO1_DATA, FIFO_2 Buffer : P6B_99_RX_FIFO2_ADDR/P6B_9A_RX_FIFO2_DATA
    // Get Number Of Data Object From Message Header NoD Field
    SET_TYPE_C_1_PD_RCV_NOD_CNT((ScalerGetByte_EXINT(P6B_56_RX_FIFO0_MSG_HEADER0 + (enumRxProcFifo * 0x20)) & (_BIT6 | _BIT5 | _BIT4)) >> 4);

    // Clear FIFO Address to 0
    ScalerSetByte_EXINT(P6B_59_RX_FIFO0_ADDR + (enumRxProcFifo * 0x20), 0x00);

    // Start Reading Data Object Contents from FIFO
    for(BYTE ucLoopIndex = 0; ucLoopIndex < (GET_TYPE_C_1_PD_RCV_NOD_CNT() * 4); ucLoopIndex++)
    {
        g_pucTypeC1PdDataObject_EXINT[ucLoopIndex] = ScalerGetByte_EXINT(P6B_5A_RX_FIFO0_DATA + (enumRxProcFifo * 0x20));

        // Manual Increase Rx FIFO Address
        ScalerSetByte_EXINT(P6B_59_RX_FIFO0_ADDR + (enumRxProcFifo * 0x20), ScalerGetByte_EXINT(P6B_59_RX_FIFO0_ADDR + (enumRxProcFifo * 0x20)) + 1);
    }
    // Data Object 0 [31:24] -> g_pucTypeC1PdDataObject_EXINT[0]
    // Data Object 0 [23:16] -> g_pucTypeC1PdDataObject_EXINT[1]
    // Data Object 0 [15:8]  -> g_pucTypeC1PdDataObject_EXINT[2]
    // Data Object 0 [7:0]   -> g_pucTypeC1PdDataObject_EXINT[3] ...
}

//--------------------------------------------------
// Description  : Clear and Disable All of Certain Rx FIFO IRQs @ Interrupt
// Input Value  : enumRxProcFifo : _RX_FIFO_0 / _RX_FIFO_1 / _RX_FIFO_2
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdRxFifoClear_EXINT0(EnumTypeCRxFifoIndex enumRxProcFifo)
{
    BYTE ucWaitRxFsmIdleCnt = 0;

    // Clear FIFO Only When Rx FSM is Idle (H/W P6B_42_RX_FIFO_GENERAL_INFO fifo_used Can Only Be Cleared When RX PTCL FSM = IDLE)
    while((ScalerGetByte_EXINT(P6B_21_RX_STATE_MACHINE_L) != 0x01) && (ucWaitRxFsmIdleCnt < 20))
    {
        ucWaitRxFsmIdleCnt ++;
        DELAY_XUS_EXINT(100);
    }

    switch(enumRxProcFifo)
    {
        case _PD_RX_FIFO_0:

            ScalerSetByte_EXINT(P6B_50_RX_FIFO0_RCV_MSG_INT, 0xAA);
            ScalerSetBit_EXINT(P6B_51_RX_FIFO0_RCV_ERR_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P6B_52_RX_FIFO0_RCV_ERR_INT_EN, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P6B_53_RX_FIFO0_MSG_MIS_FLAG, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0));
            ScalerSetBit_EXINT(P6B_60_RX_FIFO0_SP_MSG_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT5 | _BIT3));
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
            ScalerSetBit_EXINT(P6B_62_RX_FIFO0_MSG_INT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
#else
            ScalerSetBit_EXINT(P6B_62_RX_FIFO0_MSG_INT, ~(_BIT1 | _BIT0), (_BIT1));
#endif
            ScalerSetBit_EXINT(P6B_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

            break;

        case _PD_RX_FIFO_1:

            ScalerSetByte_EXINT(P6B_70_RX_FIFO1_RCV_MSG_INT, 0xAA);
            ScalerSetBit_EXINT(P6B_71_RX_FIFO1_RCV_ERR_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P6B_72_RX_FIFO1_RCV_ERR_INT_EN, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P6B_73_RX_FIFO1_MSG_MIS_FLAG, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0));
            ScalerSetBit_EXINT(P6B_80_RX_FIFO1_SP_MSG_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT5 | _BIT3));
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
            ScalerSetBit_EXINT(P6B_82_RX_FIFO1_MSG_INT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
#else
            ScalerSetBit_EXINT(P6B_82_RX_FIFO1_MSG_INT, ~(_BIT1 | _BIT0), (_BIT1));
#endif
            ScalerSetBit_EXINT(P6B_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            break;

        case _PD_RX_FIFO_2:

            ScalerSetByte_EXINT(P6B_90_RX_FIFO2_RCV_MSG_INT, 0xAA);
            ScalerSetBit_EXINT(P6B_91_RX_FIFO2_RCV_ERR_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P6B_92_RX_FIFO2_RCV_ERR_INT_EN, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P6B_93_RX_FIFO2_MSG_MIS_FLAG, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0));
            ScalerSetBit_EXINT(P6B_A0_RX_FIFO2_SP_MSG_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT5 | _BIT3));
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
            ScalerSetBit_EXINT(P6B_A2_RX_FIFO2_MSG_INT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
#else
            ScalerSetBit_EXINT(P6B_A2_RX_FIFO2_MSG_INT, ~(_BIT1 | _BIT0), (_BIT1));
#endif
            ScalerSetBit_EXINT(P6B_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

            break;

        default:
            // Should Not Happens
            break;
    }
}

//--------------------------------------------------
// Description  : Cancel All Timer Events When CC Unattach
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdUnattachCancelTimerEvent_EXINT0(void)
{
    CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();

    // Cancel Timer Event
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_SRC_TURN_ON_POWER);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_SEND_HARD_RST);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_SNK_HARD_RST_TIMEOUT);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_S8_HRST);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_TPC_ERROR_RECOVERY);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_CLR_GET_SNK_CAP_WAIT);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_CLR_VDMMSG_WAIT);
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_PPS_TIMEOUT);
#endif
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT);

    CLR_TYPE_C_1_PD_WD_TIMER_VALUE();

    // Cancel WD Timer Event
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_PS_TRANSITION_TIMEOUT);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_ON_POWER);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_CHECK_VBUS);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SEND_VCONN_ON_PSRDY);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_ENTER_FAILED);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SEND_VCONN_SWAP);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_CHUNK_SENDER_REQ_TIMEOUT);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_SRC_CAP);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_TX_AVALIABLE);
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_DELL_AM_ENTER_TIMEOUT);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_PD_1_DELL_ATTEN_RETRY);
#endif
}

//--------------------------------------------------
// Description  : Check if Tx HW is Avaliable (PD 3.0 : Check TxSinkOK/NG, PD 2.0 : Check PHY Idle)
// Input Value  : None
// Output Value : _PD_TX_NOT_AVAILABLE / _PD_TX_AVAILABLE / _PD_TX_WAIT_SRC_INIT_AMS_TIMER
//--------------------------------------------------
EnumTypeCTxCheckResult ScalerTypeC1PdTxAvaliable_EXINT0(void)
{
    EnumTypeCTxCheckResult enumTxCheckResult = _PD_TX_NOT_AVAILABLE;

    if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
    {
        if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
        {
            // Source Can Initiate AMS 16-20ms After Change Rp to SinkTxNG
            ScalerSetBit_EXINT(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), _PD_SINK_TX_NG);

            ScalerTimerWDActivateTimerEvent_EXINT0(_SRC_INIT_AMS_TIMER, _SCALER_WD_TIMER_EVENT_PD_1_TX_AVALIABLE);

            enumTxCheckResult = _PD_TX_WAIT_SRC_INIT_AMS_TIMER;

            if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
            {
                // Cancel SourceEPRKeepAliveTimer (750~1000ms)
                ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT);

                if((GET_TYPE_C_1_PD_TIMER_EVENT_ID() == _SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT) && (GET_TYPE_C_1_PD_TIMER_EVENT_VALID() == _TRUE))
                {
                    CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();
                }
            }
        }
        else
        {
            if(ScalerTypeC1CcDetResistor_EXINT0() == _TYPE_C_DET_RP_3P0A)
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
        if(ScalerGetBit_EXINT(P6B_05_PD_PHY_IDLE_INT, _BIT2) == _BIT2)
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
void ScalerTypeC1PdRxIntControl_EXINT0(bit b1Action)
{
    if(b1Action == _ENABLE)
    {
        // Enable Rx Rcv Msg IRQ
        ScalerSetBit_EXINT(P6B_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT6);
    }
    else
    {
        // Disable Rx Rcv Msg IRQ
        ScalerSetBit_EXINT(P6B_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), 0x00);
    }
}

#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
//--------------------------------------------------
// Description  : Update Retry Counter According to Spec Version
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetPortPartnerRetryCounter_EXINT0(void)
{
    // For New IC(RL6952) Use, Set Port Partner Retry Cnt to 0x65EC
    if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0)
    {
        ScalerSetBit_EXINT(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
    else
    {
        ScalerSetBit_EXINT(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
    }
}

//--------------------------------------------------
// Description  : Update Retry Counter According to Spec Version
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetCableRetryCounter_EXINT0(void)
{
    // For New IC(RL6952) Use, Set Cable Retry Cnt to 0x65ED
    if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_CBL_SPEC_VER() == _PD_VERSION_3_0))
    {
        ScalerSetBit_EXINT(P6B_ED_TX_PD_CBL_RTY_CNT, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else
    {
        ScalerSetBit_EXINT(P6B_ED_TX_PD_CBL_RTY_CNT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
    }
}

#else
//--------------------------------------------------
// Description  : Update Retry Counter According to Spec Version (Back to Port Spec Version Retry Count)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdUpdatePortPartnerRetryCounter_EXINT0(void)
{
    // For Old IC(RL6829) Use, Set Port Partner Retry Cnt to 0x65EC
    if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0)
    {
        ScalerSetBit_EXINT(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
    else
    {
        ScalerSetBit_EXINT(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
    }
}

//--------------------------------------------------
// Description  : Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdUpdateCableRetryCounter_EXINT0(void)
{
    // For Old IC(RL6829) Use, Set Cable Retry Cnt to 0x65EC
    if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_CBL_SPEC_VER() == _PD_VERSION_3_0))
    {
        ScalerSetBit_EXINT(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
    }
    else
    {
        ScalerSetBit_EXINT(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
}
#endif

//--------------------------------------------------
// Description  : Update PR/DR/Spec Version In Msg Header For SOP Communication.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdUpdateTxFifoMsgHeader_EXINT0(void)
{
    // [3] Power Role / [2:1] Spec Version / [0] Data Role
    ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, GET_TYPE_C_1_PD_POWER_ROLE() << 3);
    ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), GET_TYPE_C_1_PD_SPEC_VER() << 1);
    ScalerSetBit_EXINT(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_TYPE_C_1_PD_DATA_ROLE());
}

//--------------------------------------------------
// Description  : Go Back To Src/Snk Ready State According to Power Role
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdBackToReadyState_EXINT0(void)
{
    // Back to Ready State
    if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
    {
        SET_TYPE_C_1_PD_FW_STATE(_PD_SRC_READY);
        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SRC_READY);

        // If PD 3.0, Change Rp to SinkTxOK
        if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
        {
            ScalerSetBit_EXINT(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), _PD_SINK_TX_OK);
        }

        // Active SourceEPRKeepAliveTimer (750~1000ms) When Back to Ready State in EPR Mode, Timeout : Hard Reset
        if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
        {
            ScalerTypeC1PdActiveTimerEvent_EXINT0(_SRC_EPR_KEEP_ALIVE_TIMER, _SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT);

            // Clear Macro When Active SourceEPRKeepAliveTimer to Avoid Canceling it in Mainloop
            CLR_TYPE_C_1_PD_CANCEL_SRC_EPR_KEEP_ALIVE();
        }
    }
    else
    {
        SET_TYPE_C_1_PD_FW_STATE(_PD_SNK_READY);
        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SNK_READY);
    }
}

//--------------------------------------------------
// Description  : Check if Present Power Contract is still Valid
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeC1PdCheckPowerContractValid_EXINT0(void)
{
    // When Previously Negotiated Voltage and Current are Included in the New Capabilities, Return _TRUE
    if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
    {
        // New Source Capabilities : _SRC_CAP_VOL_MAX / _SRC_CAP_CUR (Unit : 10mV / 10mA)
        // Previously Negotiated Voltage and Current : _PDO_STATUS_VOL / _PDO_STATUS_CUR (Unit : 10mV / 10mA)
        if((GET_TYPE_C_1_PD_PDO_STATUS_VOL() == GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() - 1)) &&
           (GET_TYPE_C_1_PD_PDO_STATUS_CUR() <= GET_TYPE_C_1_PD_SRC_CAP_CUR(GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() - 1)))
        {
            return _TRUE;
        }
    }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
    else if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() - 1) == _PD_3_PROGRAMMABLE_PDO)
    {
        // New Source Capabilities : _SRC_CAP_VOL_MAX / _SRC_CAP_VOL_MIN / _SRC_CAP_CUR (Unit : 10mV / 10mV / 50mA)
        // Previously Negotiated Voltage and Current : _PDO_STATUS_VOL / _PDO_STATUS_CUR (Unit : 10mV / 10mA)
        if((GET_TYPE_C_1_PD_PDO_STATUS_VOL() <= GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() - 1)) &&
           (GET_TYPE_C_1_PD_PDO_STATUS_VOL() >= GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() - 1)) &&
           (GET_TYPE_C_1_PD_PDO_STATUS_CUR() <= (GET_TYPE_C_1_PD_SRC_CAP_CUR(GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() - 1) * 5)))
        {
            return _TRUE;
        }
    }
#endif
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
    else if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() - 1) == _PD_3_1_ADJUSTABLE_PDO)
    {
        // New Source Capabilities : _MAX_POWER / _SRC_CAP_VOL_MAX / _SRC_CAP_VOL_MIN (Unit : 0.1W / 10mV / 10mV)
        // Previously Negotiated Voltage and Current : _PDO_STATUS_VOL / _PDO_STATUS_CUR (Unit : 10mV / 10mA)
        if(((WORD)((((DWORD)GET_TYPE_C_1_PD_PDO_STATUS_CUR()) * ((DWORD)GET_TYPE_C_1_PD_PDO_STATUS_VOL())) / 1000) <= GET_TYPE_C_1_MAX_POWER()) &&
           (GET_TYPE_C_1_PD_PDO_STATUS_VOL() <= GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() - 1)) &&
           (GET_TYPE_C_1_PD_PDO_STATUS_VOL() >= GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(GET_TYPE_C_1_PD_PDO_STATUS_OBJ_POS() - 1)))
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if Power Contract Need to be Rebuild
// Input Value  : None
// Output Value : _PD_REBUILD_REQUIRED / _PD_REBUILD_NOT_REQUIRED
//--------------------------------------------------
EnumTypeCPDRebuildPowerContract ScalerTypeC1PdCheckRebuildPowerContract_EXINT0(void)
{
    EnumTypeCPDRebuildPowerContract enumRebuildCheckResult = _PD_REBUILD_NOT_REQUIRED;

    if(GET_TYPE_C_1_PD_CBL_MAX_CUR() == 500)
    {
        for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT(); ucLoopIndex ++)
        {
            if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_FIX_SUPPLY_PDO)
            {
                // When Get CBL Max Current = 5A , SRC CAP CUR > 3A, Rebuild is Required
                if(GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex) > 300)
                {
                    enumRebuildCheckResult = _PD_REBUILD_REQUIRED;
                }
            }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
            else if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
            {
                if(((GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex)) * 5) > 300)
                {
                    enumRebuildCheckResult = _PD_REBUILD_REQUIRED;
                }
            }
#endif
        }
    }
    else if(GET_TYPE_C_1_PD_CBL_MAX_CUR() < 300)
    {
        for(BYTE ucLoopIndex = 0; ucLoopIndex < GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT(); ucLoopIndex ++)
        {
            if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_FIX_SUPPLY_PDO)
            {
                // When Get CBL Max Current = USB Type-C Default Current(500mA/900mA/1.5A), SRC CAP CUR > CBL MAX CUR, Rebuild is Required
                if(GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex) > GET_TYPE_C_1_PD_CBL_MAX_CUR())
                {
                    enumRebuildCheckResult = _PD_REBUILD_REQUIRED;
                }
            }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
            else if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucLoopIndex) == _PD_3_PROGRAMMABLE_PDO)
            {
                if(((GET_TYPE_C_1_PD_SRC_CAP_CUR(ucLoopIndex)) * 5) > GET_TYPE_C_1_PD_CBL_MAX_CUR())
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
// Description  : Record Cable Info Of Discover ID Ack
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSaveCableDiscoverIdAckInfo_EXINT0(void)
{
    // Update Cable SVDM Version [14:13] Major = b'01 (2.x), [12:11] Minor = b'00(2.0), b'01 (2.1)
    if((GET_TYPE_C_1_PD_CBL_SVDM_VERSION() >= _PD_SVDM_VER_2_1) && ((g_pucTypeC1PdDataObject_EXINT[2] & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) <= (_BIT5)))
    {
        // if((Current SVDM >= 2.1) & (Rcv SVDM <= 2.0)), Downgrade to SVDM 2.0 Earlier
        SET_TYPE_C_1_PD_CBL_SVDM_VERSION(_PD_SVDM_VER_2_0_EARLIER);
    }

    // ID Header VDO, Bit[29:27] SOP' Product Type(Passive Cable / Active Cable / VPD)
    if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT5 | _BIT4 | _BIT3)) == (_BIT4 | _BIT3))
    {
        SET_TYPE_C_1_PD_CBL_PRODUCT_TYPE(_PD_PASSIVE_CABLE);

        // DPAM v2.1: Store Cable Info For DPCD Table(02217h For DPRX / 00110h For DPTX), When Not In DPAM, Discover Identity Takes Priority
        SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_PASSIVE);
    }
    else if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT5 | _BIT4 | _BIT3)) == _BIT5)
    {
        SET_TYPE_C_1_PD_CBL_PRODUCT_TYPE(_PD_ACTIVE_CABLE);
    }
    else if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4))
    {
        SET_TYPE_C_1_PD_CBL_PRODUCT_TYPE(_PD_VCONN_POWERED_USB_DEVICE);
    }

    // Bit[26] Modal Operation Support: Y/N
    if((g_pucTypeC1PdDataObject_EXINT[4] & _BIT2) == _BIT2)
    {
        SET_TYPE_C_1_PD_CBL_MODAL_OPERATION_SUPPORT();
    }

    // Bit[22:21] Connector Type(TypeC Receptacle / TypeC Plug)
    if((g_pucTypeC1PdDataObject_EXINT[5] & (_BIT6 | _BIT5)) == _BIT6)
    {
        SET_TYPE_C_1_PD_CBL_CONNECTOR_TYPE(_PD_CABLE_TYPEC_RECEPTACLE);
    }
    else if((g_pucTypeC1PdDataObject_EXINT[5] & (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
    {
        SET_TYPE_C_1_PD_CBL_CONNECTOR_TYPE(_PD_CABLE_TYPEC_PLUG);
    }

    // Passive Cable VDO
    if(GET_TYPE_C_1_PD_CBL_PRODUCT_TYPE() == _PD_PASSIVE_CABLE)
    {
        // Bit[17] EPR Mode Capable
        if((g_pucTypeC1PdDataObject_EXINT[17] & _BIT1) == _BIT1)
        {
            SET_TYPE_C_1_PD_CBL_EPR_MODE_CAPABLE();
        }
        else
        {
            CLR_TYPE_C_1_PD_CBL_EPR_MODE_CAPABLE();
        }

        // Bit[12:11] Cable Termination Type
        if((g_pucTypeC1PdDataObject_EXINT[18] & (_BIT4 | _BIT3)) == 0x00)
        {
            CLR_TYPE_C_1_PD_CBL_VCONN_REQUIRED();
        }

        // Bit[10:9] Max Vbus Voltage
        if((g_pucTypeC1PdDataObject_EXINT[18] & (_BIT2 | _BIT1)) == (_BIT2 | _BIT1))
        {
            // Cable Max Voltage = 50V = 500 * 100mV
            SET_TYPE_C_1_PD_CBL_MAX_VOL(500);
        }
        else
        {
            // Cable Max Voltage = 20V = 200 * 100mV
            SET_TYPE_C_1_PD_CBL_MAX_VOL(200);
        }

        // Bit[6:5] Cable Max Vbus Current
        if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT6 | _BIT5)) == _BIT5)
        {
            // Cable Max Current = 3.0A = 300 * 10mA
            SET_TYPE_C_1_PD_CBL_MAX_CUR(300);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT6 | _BIT5)) == _BIT6)
        {
            SET_TYPE_C_1_PD_CBL_MAX_CUR(500);
        }

        // Bit[2:0] Cable USB Highest Speed
        if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == 0x00)
        {
            SET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_2_ONLY);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
        {
            SET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_3_GEN1);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
        {
            SET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_3OR4_GEN2);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            SET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_4_GEN3);
        }
    }
    else if(GET_TYPE_C_1_PD_CBL_PRODUCT_TYPE() == _PD_ACTIVE_CABLE)
    {
        // Active Cable VDO1
        // Bit[17] EPR Mode Capable
        if((g_pucTypeC1PdDataObject_EXINT[17] & _BIT1) == _BIT1)
        {
            SET_TYPE_C_1_PD_CBL_EPR_MODE_CAPABLE();
        }
        else
        {
            CLR_TYPE_C_1_PD_CBL_EPR_MODE_CAPABLE();
        }

        // Bit[12:11] Cable Termination Type
        if((g_pucTypeC1PdDataObject_EXINT[18] & (_BIT4 | _BIT3)) == _BIT4)
        {
            SET_TYPE_C_1_PD_CBL_TERMINATION_TYPE(_PD_CBL_ONE_ACTIVE_ONE_PASSIVE);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[18] & (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
        {
            SET_TYPE_C_1_PD_CBL_TERMINATION_TYPE(_PD_CBL_BOTH_END_ACTIVE);
        }

        // Bit[10:9] Max Vbus Voltage
        if((g_pucTypeC1PdDataObject_EXINT[18] & (_BIT2 | _BIT1)) == (_BIT2 | _BIT1))
        {
            // Cable Max Voltage = 50V = 500 * 100mV
            SET_TYPE_C_1_PD_CBL_MAX_VOL(500);
        }
        else
        {
            // Cable Max Voltage = 20V = 200 * 100mV
            SET_TYPE_C_1_PD_CBL_MAX_VOL(200);
        }

        // Bit[8] SBU Supported :Y/N
        if((g_pucTypeC1PdDataObject_EXINT[18] & _BIT0) == 0x00)
        {
            SET_TYPE_C_1_PD_CBL_SBU_SUPPORT();
        }

        // If Bit[8] == 0, set Bit[7]: SBU Type, otherwise ignore Bit[7]
        if(GET_TYPE_C_1_PD_CBL_SBU_SUPPORT() == _TRUE)
        {
            if((g_pucTypeC1PdDataObject_EXINT[19] & _BIT7) == 0x00)
            {
                SET_TYPE_C_1_PD_CBL_SBU_TYPE(_PD_CBL_SBU_PASSIVE);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[19] & _BIT7) == _BIT7)
            {
                SET_TYPE_C_1_PD_CBL_SBU_TYPE(_PD_CBL_SBU_ACTIVE);
            }
        }

        // Bit[4] Vbus Through Cable: Y/N.
        if((g_pucTypeC1PdDataObject_EXINT[19] & _BIT4) == _BIT4)
        {
            SET_TYPE_C_1_PD_CBL_VBUS_THROUGH();
        }

        // Bit[3] SOP'' Controller Present : Y/N
        if((g_pucTypeC1PdDataObject_EXINT[19] & _BIT3) == _BIT3)
        {
            SET_TYPE_C_1_PD_CBL_SOP_PP_SUPPORT();
        }

        // Bit[2:0] Cable USB Highest Speed
        if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == 0x00)
        {
            SET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_2_ONLY);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
        {
            SET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_3_GEN1);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
        {
            SET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_3OR4_GEN2);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            SET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED(_PD_CBL_USB_4_GEN3);
        }

        // Active Cable VDO2
        // Bit[11] U3 to U0 Transition Mode
        if((g_pucTypeC1PdDataObject_EXINT[22] & _BIT3) == 0x00)
        {
            SET_TYPE_C_1_PD_CBL_U3_TO_U0_TRANSITION_MODE(_PD_CBL_U3_TO_U0_DIRECT);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[22] & _BIT3) == _BIT3)
        {
            SET_TYPE_C_1_PD_CBL_U3_TO_U0_TRANSITION_MODE(_PD_CBL_U3_TO_U0_THROUGH_U3S);
        }

        // Bit[9] Active Element
        if((g_pucTypeC1PdDataObject_EXINT[22] & _BIT1) == 0x00)
        {
            // Store Cable Info For DPCD Table(02217h For DPRX / 00110h For DPTX), When Not In DPAM, Discover Identity Takes Priority
            SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_ACTIVE_REDRIVER);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[22] & _BIT1) == _BIT1)
        {
            // Store Cable Info For DPCD Table(02217h For DPRX / 00110h For DPTX), When Not In DPAM, Discover Identity Takes Priority
            SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_ACTIVE_RETIMER);
        }

        // Bit[8] USB4 Support: Y/N
        if((g_pucTypeC1PdDataObject_EXINT[22] & _BIT0) == _BIT0)
        {
            SET_TYPE_C_1_PD_CBL_USB_4_SUPPORT();
        }

        // Bit[4] USB3.2 Support: Y/N
        if((g_pucTypeC1PdDataObject_EXINT[23] & _BIT4) == _BIT4)
        {
            SET_TYPE_C_1_PD_CBL_USB_3_2_SUPPORT();
        }

        // Bit[3] USB Lanes Supported: One Lane / Two Lanes
        if((g_pucTypeC1PdDataObject_EXINT[23] & _BIT3) == 0x00)
        {
            SET_TYPE_C_1_PD_CBL_LANES_SUPPORT(_PD_CBL_ONE_LANE);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[23] & _BIT3) == _BIT3)
        {
            SET_TYPE_C_1_PD_CBL_LANES_SUPPORT(_PD_CBL_TWO_LANES);
        }

        // If VDO1 Bit[4] == 1, set Bit[6:5]: CBL max Vbus current, otherwise ignore Bit[6:5]
        if(GET_TYPE_C_1_PD_CBL_VBUS_THROUGH() == _TRUE)
        {
            if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT6 | _BIT5)) == _BIT5)
            {
                // Cable Max Vbus Current = 3.0A = 300 * 10mA
                SET_TYPE_C_1_PD_CBL_MAX_CUR(300);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT6 | _BIT5)) == _BIT6)
            {
                SET_TYPE_C_1_PD_CBL_MAX_CUR(500);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[19] & (_BIT6 | _BIT5)) == 0x00)
            {
                // PD 3.0 Spec P150: 500mA USB2, 900mA USB3.2 x1, 1.5A USB3.2 x2.
                if(GET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_2_ONLY)
                {
                    SET_TYPE_C_1_PD_CBL_MAX_CUR(50);
                }
                else if((GET_TYPE_C_1_PD_CBL_USB_3_2_SUPPORT() == _TRUE) && (GET_TYPE_C_1_PD_CBL_LANES_SUPPORT() == _PD_CBL_ONE_LANE))
                {
                    SET_TYPE_C_1_PD_CBL_MAX_CUR(90);
                }
                else if((GET_TYPE_C_1_PD_CBL_USB_3_2_SUPPORT() == _TRUE) && (GET_TYPE_C_1_PD_CBL_LANES_SUPPORT() == _PD_CBL_TWO_LANES))
                {
                    SET_TYPE_C_1_PD_CBL_MAX_CUR(150);
                }
            }
        }
    }
    else if(GET_TYPE_C_1_PD_CBL_PRODUCT_TYPE() == _PD_VCONN_POWERED_USB_DEVICE)
    {
        // VPD VDO
        // Bit[16:15] Max Vbus Voltage
        if(((g_pucTypeC1PdDataObject_EXINT[17] & _BIT0) == 0x00) && ((g_pucTypeC1PdDataObject_EXINT[18] & _BIT7) == 0x00))
        {
            // Max Voltage = 20V = 200 * 100mV
            SET_TYPE_C_1_PD_CBL_MAX_VOL(200);
        }
        else if(((g_pucTypeC1PdDataObject_EXINT[17] & _BIT0) == 0x00) && ((g_pucTypeC1PdDataObject_EXINT[18] & _BIT7) == _BIT7))
        {
            SET_TYPE_C_1_PD_CBL_MAX_VOL(300);
        }
        else if(((g_pucTypeC1PdDataObject_EXINT[17] & _BIT0) == _BIT0) && ((g_pucTypeC1PdDataObject_EXINT[18] & _BIT7) == 0x00))
        {
            SET_TYPE_C_1_PD_CBL_MAX_VOL(400);
        }
        else if(((g_pucTypeC1PdDataObject_EXINT[17] & _BIT0) == _BIT0) && ((g_pucTypeC1PdDataObject_EXINT[18] & _BIT7) == _BIT7))
        {
            SET_TYPE_C_1_PD_CBL_MAX_VOL(500);
        }

        // Bit[0] Charge Through Support
        if((g_pucTypeC1PdDataObject_EXINT[19] & _BIT0) == _BIT0)
        {
            SET_TYPE_C_1_PD_CBL_CHARGE_THROUGH_SUPPORT();
        }

        // Bit[14] Charge Through Current Support; if Bit[0] = 1, Set Max Current Macro
        if(GET_TYPE_C_1_PD_CBL_CHARGE_THROUGH_SUPPORT() == _TRUE)
        {
            if((g_pucTypeC1PdDataObject_EXINT[18] & _BIT6) == 0x00)
            {
                // Charge Through Current = 3.0A = 300 * 10mA
                SET_TYPE_C_1_PD_CBL_MAX_CUR(300);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[18] & _BIT6) == _BIT6)
            {
                SET_TYPE_C_1_PD_CBL_MAX_CUR(500);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Check if Received Request is Valid
// Input Value  : None
// Output Value : _PD_REQUEST_INVALID_CURRENT / _PD_REQUEST_INVALID_COPY_PDO / _PD_REQUEST_VALID
//--------------------------------------------------
EnumTypeCPDRequestValid ScalerTypeC1PdCheckRequestValid_EXINT0(void)
{
    EnumTypeCPDRequestValid enumReqCheckResult = _PD_REQUEST_INVALID_CURRENT;
    WORD usCopyPdoMaxVoltage = 0;
    WORD usCopyPdoMinVoltage = 0;
    WORD usCopyPdoCurrent = 0;
    WORD usCopyPdoPDP = 0;

    usCopyPdoMaxVoltage = usCopyPdoMaxVoltage;
    usCopyPdoMinVoltage = usCopyPdoMinVoltage;
    usCopyPdoCurrent = usCopyPdoCurrent;
    usCopyPdoPDP = usCopyPdoPDP;

    SET_TYPE_C_1_PD_PARTNER_OBJ_POS((g_pucTypeC1PdDataObject_EXINT[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

    // 1. Check if Object Position is Valid :
    // (1) If Object Position <= 7 (SPR PDO), Check Object Position <= SPR PDO Count
    // (2) If Object Position > 7 (EPR PDO), Check Object Position -7 <= EPR PDO Count
    if(((GET_TYPE_C_1_PD_PARTNER_OBJ_POS() > 0) && (GET_TYPE_C_1_PD_PARTNER_OBJ_POS() <= GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT())) ||
       ((GET_TYPE_C_1_PD_PARTNER_OBJ_POS() > 7) && ((GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 7) <= GET_TYPE_C_1_PD_EPR_SRC_PDO_CNT())))
    {
        if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
        {
            // Get Fix Supply RDO Operating / Max Current (Unit = 10mA)
            SET_TYPE_C_1_PD_PARTNER_OP_CUR((((WORD)(g_pucTypeC1PdDataObject_EXINT[1] & 0x0F)) << 6) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[2] & 0xFC)) >> 2));
            SET_TYPE_C_1_PD_PARTNER_MAX_CUR((((WORD)(g_pucTypeC1PdDataObject_EXINT[2] & 0x03)) << 8) | ((WORD)g_pucTypeC1PdDataObject_EXINT[3]));

            // 2.1. Check if Requested "Operating Current" <= Src PDO Current / Cable Max Current
            if((GET_TYPE_C_1_PD_PARTNER_OP_CUR() <= GET_TYPE_C_1_PD_SRC_CAP_CUR(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)) &&
               (GET_TYPE_C_1_PD_PARTNER_OP_CUR() <= GET_TYPE_C_1_PD_CBL_MAX_CUR()))
            {
                // Record Requested Voltage
                SET_TYPE_C_1_PD_PARTNER_REQ_VOL(GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1));

#if(_TYPE_C_EIZO_CUSTOMIZED_OCP_THRESHOLD_SUPPORT == _OFF)
                // Set OCP Threshlod according to Min(Requested Max Cur, Cable Max Cur)
                if(GET_TYPE_C_1_PD_PARTNER_MAX_CUR() <= GET_TYPE_C_1_PD_CBL_MAX_CUR())
                {
                    SET_TYPE_C_1_OCP_CURRENT((WORD)(((DWORD)(GET_TYPE_C_1_PD_PARTNER_MAX_CUR()) * (DWORD)(GET_TYPE_C_1_OCP_RATIO(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1))) / 100));
                }
                else
                {
                    SET_TYPE_C_1_OCP_CURRENT((WORD)(((DWORD)(GET_TYPE_C_1_PD_CBL_MAX_CUR()) * (DWORD)(GET_TYPE_C_1_OCP_RATIO(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1))) / 100));
                }
#else
                // Set OCP Threshlod according to Min(PDO Max Cur, Cable Max Cur)
                if((GET_TYPE_C_1_PD_SRC_CAP_CUR(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)) <= GET_TYPE_C_1_PD_CBL_MAX_CUR())
                {
                    SET_TYPE_C_1_OCP_CURRENT((WORD)(((DWORD)(GET_TYPE_C_1_PD_SRC_CAP_CUR(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)) * (DWORD)(GET_TYPE_C_1_OCP_RATIO(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1))) / 100));
                }
                else
                {
                    SET_TYPE_C_1_OCP_CURRENT((WORD)(((DWORD)(GET_TYPE_C_1_PD_CBL_MAX_CUR()) * (DWORD)(GET_TYPE_C_1_OCP_RATIO(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1))) / 100));
                }
#endif

                // Clear Small Step Flag to Avoid Using Wrong Timer when Power Transition.
                CLR_TYPE_C_1_PD_REQ_PPS_VOL_SMALL_STEP();
                CLR_TYPE_C_1_PD_REQ_AVS_VOL_SMALL_STEP();

                enumReqCheckResult = _PD_REQUEST_VALID;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
                if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
                {
                    // Set Copy PDO Voltage (Unit 50mV to 10mV) and Current (Unit 10mA)
                    usCopyPdoMaxVoltage = (((((WORD)(g_pucTypeC1PdDataObject_EXINT[5] & 0x0F)) << 6) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[6] & 0xFC)) >> 2)) * 5);
                    usCopyPdoCurrent = ((((WORD)(g_pucTypeC1PdDataObject_EXINT[6] & 0x03)) << 8) | ((WORD)g_pucTypeC1PdDataObject_EXINT[7]));

                    if((usCopyPdoMaxVoltage != GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)) ||
                       (usCopyPdoCurrent != GET_TYPE_C_1_PD_SRC_CAP_CUR(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)))
                    {
                        // If Copy of PDO in EPR Request is Not Equal to PDO in EPR Source Cap, Do Hard Reset
                        enumReqCheckResult = _PD_REQUEST_INVALID_COPY_PDO;
                    }
                }
#endif
            }
        }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
        else if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1) == _PD_3_PROGRAMMABLE_PDO)
        {
            WORD usNewVoltage = 0x00;

            // Get PPS RDO Operating / Max Current (Unit = 50mA)
            SET_TYPE_C_1_PD_PARTNER_OP_CUR((WORD)(g_pucTypeC1PdDataObject_EXINT[3] & 0x7F));
            SET_TYPE_C_1_PD_PARTNER_MAX_CUR((WORD)(g_pucTypeC1PdDataObject_EXINT[3] & 0x7F));

            // Request PPS Voltage with Unit 20mV and Convert to 10mV
            usNewVoltage = (((((WORD)(g_pucTypeC1PdDataObject_EXINT[1] & 0x0F)) << 7) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[2] & 0xFE)) >> 1)) * 2);

            if(((usNewVoltage >= GET_TYPE_C_1_PD_PARTNER_REQ_VOL()) && ((usNewVoltage - GET_TYPE_C_1_PD_PARTNER_REQ_VOL()) <= 50)) ||
               ((usNewVoltage < GET_TYPE_C_1_PD_PARTNER_REQ_VOL()) && ((GET_TYPE_C_1_PD_PARTNER_REQ_VOL() - usNewVoltage) <= 50)))
            {
                SET_TYPE_C_1_PD_REQ_PPS_VOL_SMALL_STEP(_TRUE);
            }
            else
            {
                SET_TYPE_C_1_PD_REQ_PPS_VOL_SMALL_STEP(_FALSE);
            }

            SET_TYPE_C_1_PD_PARTNER_REQ_VOL(usNewVoltage);

            // 2.2. Check if (Req "Operating Current" <= Source PDO Cur / Cable Max Current) & (Req Voltage is Valid)
            if((GET_TYPE_C_1_PD_PARTNER_OP_CUR() <= GET_TYPE_C_1_PD_SRC_CAP_CUR(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)) &&
               (GET_TYPE_C_1_PD_PARTNER_OP_CUR() <= (GET_TYPE_C_1_PD_CBL_MAX_CUR() / 5)) &&
               (GET_TYPE_C_1_PD_PARTNER_REQ_VOL() >= GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)) &&
               (GET_TYPE_C_1_PD_PARTNER_REQ_VOL() <= GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)))
            {
                // Convert Requested Current From 50mA to 10mA (PPS PDO : Max Current = Operating Current)
                SET_TYPE_C_1_PD_PARTNER_OP_CUR(GET_TYPE_C_1_PD_PARTNER_OP_CUR() * 5);
                SET_TYPE_C_1_PD_PARTNER_MAX_CUR(GET_TYPE_C_1_PD_PARTNER_MAX_CUR() * 5);
#if(_TYPE_C_EIZO_CUSTOMIZED_OCP_THRESHOLD_SUPPORT == _OFF)
                SET_TYPE_C_1_OCP_CURRENT(GET_TYPE_C_1_PD_PARTNER_MAX_CUR());
#else
                // Set OCP Threshlod according to Min(PDO Max Cur, Cable Max Cur)
                if((GET_TYPE_C_1_PD_SRC_CAP_CUR(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)) <= (GET_TYPE_C_1_PD_CBL_MAX_CUR() / 5))
                {
                    SET_TYPE_C_1_OCP_CURRENT((GET_TYPE_C_1_PD_SRC_CAP_CUR(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)) * 5);
                }
                else
                {
                    SET_TYPE_C_1_OCP_CURRENT(GET_TYPE_C_1_PD_CBL_MAX_CUR());
                }
#endif

                // Start Timer Event 13.5 Sec, Sink Should Request PPS PDO every 10 sec
                ScalerTypeC1PdActiveTimerEvent_EXINT0(13500, _SCALER_TIMER_EVENT_PD_1_PPS_TIMEOUT);

                enumReqCheckResult = _PD_REQUEST_VALID;
            }
        }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        else if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1) == _PD_3_1_ADJUSTABLE_PDO)
        {
            WORD usEPRNewVoltage = 0x00;

            // Get AVS RDO Operating / Max Current (Unit = 50mA to 10mA)
            SET_TYPE_C_1_PD_PARTNER_OP_CUR(((WORD)(g_pucTypeC1PdDataObject_EXINT[3] & 0x7F)) * 5);
            SET_TYPE_C_1_PD_PARTNER_MAX_CUR(((WORD)(g_pucTypeC1PdDataObject_EXINT[3] & 0x7F)) * 5);

            // Request AVS Voltage with Unit 100mV and Convert to 10mV
            usEPRNewVoltage = (((((WORD)(g_pucTypeC1PdDataObject_EXINT[1] & 0x1F)) << 5) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[2] & 0xF8)) >> 3)) * 10);

            if(((usEPRNewVoltage >= GET_TYPE_C_1_PD_PARTNER_REQ_VOL()) && ((usEPRNewVoltage - GET_TYPE_C_1_PD_PARTNER_REQ_VOL()) <= 100)) ||
               ((usEPRNewVoltage < GET_TYPE_C_1_PD_PARTNER_REQ_VOL()) && ((GET_TYPE_C_1_PD_PARTNER_REQ_VOL() - usEPRNewVoltage) <= 100)))
            {
                SET_TYPE_C_1_PD_REQ_AVS_VOL_SMALL_STEP(_TRUE);
            }
            else
            {
                SET_TYPE_C_1_PD_REQ_AVS_VOL_SMALL_STEP(_FALSE);
            }

            SET_TYPE_C_1_PD_PARTNER_REQ_VOL(usEPRNewVoltage);

            // 2.2. Check if {[(Req Operating Current (Unit 10mA) * Req Voltage (Unit 10mV)) / 1000] <= Source PDP (Unit 0.1W)} & (Req Voltage is Valid)
            if(((WORD)((((DWORD)GET_TYPE_C_1_PD_PARTNER_OP_CUR()) * ((DWORD)GET_TYPE_C_1_PD_PARTNER_REQ_VOL())) / 1000) <= GET_TYPE_C_1_MAX_POWER()) &&
               (GET_TYPE_C_1_PD_PARTNER_REQ_VOL() >= GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)) &&
               (GET_TYPE_C_1_PD_PARTNER_REQ_VOL() <= GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)))
            {
                // Set Copy PDO Voltage (Unit 100mV to 10mV) and PDP (Unit 1W to 0.1W)
                usCopyPdoMaxVoltage = (((((WORD)(g_pucTypeC1PdDataObject_EXINT[4] & 0x03)) << 7) | (((WORD)(g_pucTypeC1PdDataObject_EXINT[5] & 0xFE)) >> 1)) * 10);
                usCopyPdoMinVoltage = (((WORD)g_pucTypeC1PdDataObject_EXINT[6]) * 10);
                usCopyPdoPDP = (((WORD)g_pucTypeC1PdDataObject_EXINT[7]) * 10);

                if((usCopyPdoMaxVoltage != GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)) ||
                   (usCopyPdoMinVoltage != GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1)) ||
                   (usCopyPdoPDP != GET_TYPE_C_1_MAX_POWER()))
                {
                    // If Copy of PDO in EPR Request is Not Equal to PDO in EPR Source Cap, Do Hard Reset
                    enumReqCheckResult = _PD_REQUEST_INVALID_COPY_PDO;
                }
                else
                {
#if(_TYPE_C_EIZO_CUSTOMIZED_OCP_THRESHOLD_SUPPORT == _OFF)
                    SET_TYPE_C_1_OCP_CURRENT(GET_TYPE_C_1_PD_PARTNER_MAX_CUR());
#else
                    // Set OCP Threshlod (Unit 10mA) = [(Max Power (Unit 0.1W) * 1000) / Req Voltage (Unit 10mV)]
                    SET_TYPE_C_1_OCP_CURRENT((WORD)(((DWORD)(GET_TYPE_C_1_MAX_POWER()) * 1000) / GET_TYPE_C_1_PD_PARTNER_REQ_VOL()));
#endif
                    enumReqCheckResult = _PD_REQUEST_VALID;
                }
            }
        }
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)

        // For Valid Request, Update Port Partner(Sink) Info
        if(enumReqCheckResult == _PD_REQUEST_VALID)
        {
            SET_TYPE_C_1_PD_PARTNER_GIVE_BACK(g_pucTypeC1PdDataObject_EXINT[0] >> 3);
            SET_TYPE_C_1_PD_PARTNER_CAP_MIS(g_pucTypeC1PdDataObject_EXINT[0] >> 2);
            SET_TYPE_C_1_PD_PARTNER_USB_CAP(g_pucTypeC1PdDataObject_EXINT[0] >> 1);
            SET_TYPE_C_1_PD_PARTNER_SUSPEND(~(g_pucTypeC1PdDataObject_EXINT[0] >> 0));
            SET_TYPE_C_1_PD_PARTNER_UNCHK(g_pucTypeC1PdDataObject_EXINT[1] >> 7);
            SET_TYPE_C_1_PD_PARTNER_EPR_CAP(g_pucTypeC1PdDataObject_EXINT[1] >> 6);
        }
    }

    return enumReqCheckResult;
}

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
//--------------------------------------------------
// Description  : Check if Both Port Partners Support EPR Mode
// Input Value  : None
// Output Value : _PD_EPR_MODE_ENTER_FAILED_SINK_NOT_EPR_CAP / _PD_EPR_MODE_ENTER_FAILED_SOURCE_NOT_EPR_CAP / _PD_EPR_MODE_ENTER_ACK
//--------------------------------------------------
BYTE ScalerTypeC1PdCheckEPRCapable_EXINT0(void)
{
    BYTE ucCheckResult = _FALSE;

    if(GET_TYPE_C_1_PD_PARTNER_EPR_CAP() == _FALSE)
    {
        // Sink Not Support EPR Mode
        SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_SINK_NOT_EPR_CAP);
    }
    else if(GET_TYPE_C_1_PD_EPR_SRC_CAPABLE() == _FALSE)
    {
        // Source Not Support EPR Mode
        SET_TYPE_C_1_PD_ENTER_EPR_FAILED_REASON(_PD_EPR_MODE_ENTER_FAILED_SOURCE_NOT_EPR_CAP);
    }
    else
    {
        // Both Port Partners Support EPR Mode
        ucCheckResult = _TRUE;
    }

    return ucCheckResult;
}
#endif

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Search Through All SVIDs to Check if DP_SID Exist
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeC1PdSearchSvid_EXINT0(void)
{
    BYTE ucSearchResult = _FALSE;

    CLR_TYPE_C_1_PD_DP_SVID_SEARCH_FINISH();

    for(BYTE ucLoopIndex = 0; ucLoopIndex < (GET_TYPE_C_1_PD_RCV_NOD_CNT() * 4); ucLoopIndex = ucLoopIndex + 2)
    {
        if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex] == 0xFF) && (g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 1] == 0x01))
        {   // if SVID = DP_SID (0xFF01), Set Result to TRUE
            ucSearchResult = _TRUE;
        }
        else if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex] == 0x00) && (g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 1] == 0x00))
        {   // if SVID = 0x00, Search Finish
            SET_TYPE_C_1_PD_DP_SVID_SEARCH_FINISH();
        }
    }

    return ucSearchResult;
}

//--------------------------------------------------
// Description  : Search All Modes to Get DP Port Capability (DP_Tx) and Pin Assignment ( C / D / E )
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSearchMode_EXINT0(void)
{
    CLR_TYPE_C_1_PD_DP_OBJ_POS();

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    for(BYTE ucLoopIndex = 4; ucLoopIndex < (GET_TYPE_C_1_PD_RCV_NOD_CNT() * 4); ucLoopIndex = ucLoopIndex + 4)
    {
        // if(Support DP Tx), Get Supported Pin Assignments
        if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 3] & _BIT1) == _BIT1)
        {
            // Discover Mode [31:30] DPAM Version = b'00(2.0), b'01 (2.1)
            if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex] & (_BIT7 | _BIT6)) == 0x00))
            {
                // if((Current DPAM >= 2.1) & (Rcv DPAM = 2.0)), Downgrade to DPAM 2.0
                SET_TYPE_C_1_PD_PARTNER_DPAM_VERSION(_PD_DPAM_VER_2_0_EARLIER);
            }

            // If Connect to Receptacle, Refer to DFP_D Pin Assignment
            if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 3] & _BIT6) == _BIT6)
            {
                SET_TYPE_C_1_PD_PARTNER_PIN_ASSIGNMENT(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 2]);
            }
            else
            {
                // If Connect to Plug, Refer to UFP_D Pin Assignment
                SET_TYPE_C_1_PD_PARTNER_PIN_ASSIGNMENT(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 1]);
            }

            // Check If There is Any Pin Assignment Avaliable (Partner & Our Cap Both Support)
            if((GET_TYPE_C_1_PD_PARTNER_PIN_ASSIGNMENT() & GET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP()) != 0x00)
            {
                SET_TYPE_C_1_PD_DP_OBJ_POS(ucLoopIndex / 4);
            }
        }
        // Else, Keep Target Object Position = 0x00
    }

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    for(BYTE ucLoopIndex = 4; ucLoopIndex < (GET_TYPE_C_1_PD_RCV_NOD_CNT() * 4); ucLoopIndex = ucLoopIndex + 4)
    {
        // if(Support DP Rx), Get Supported Pin Assignments
        if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 3] & _BIT0) == _BIT0)
        {
            // Discover Mode [31:30] DPAM Version = b'00(2.0), b'01 (2.1)
            if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex] & (_BIT7 | _BIT6)) == 0x00))
            {
                // if((Current DPAM >= 2.1) & (Rcv DPAM = 2.0)), Downgrade to DPAM 2.0
                SET_TYPE_C_1_PD_PARTNER_DPAM_VERSION(_PD_DPAM_VER_2_0_EARLIER);
            }

            // If Connect to Receptacle, Refer to UFP_D Pin Assignment
            if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 3] & _BIT6) == _BIT6)
            {
                SET_TYPE_C_1_PD_PARTNER_PIN_ASSIGNMENT(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 1]);
            }
            else
            {
                // If Connect to Plug, Refer to DFP_D Pin Assignment
                SET_TYPE_C_1_PD_PARTNER_PIN_ASSIGNMENT(g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 2]);
            }

            // Check If There is Any Pin Assignment Avaliable (Partner & Our Cap Both Support)
            if((GET_TYPE_C_1_PD_PARTNER_PIN_ASSIGNMENT() & GET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP()) != 0x00)
            {
                SET_TYPE_C_1_PD_DP_OBJ_POS(ucLoopIndex / 4);
            }
        }
        // Else, Keep Target Object Position = 0x00
    }
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
}

//--------------------------------------------------
// Description  : Update Port Partner DP Status
// Input Value  : enumVdmDpCmd
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdUpdatePortPartnerDpStatus_EXINT0(EnumTypeCVdmDpCmd enumVdmDpCmd)
{
    switch(enumVdmDpCmd)
    {
        case _PD_VDM_DP_CMD_DP_STATUS_REQ:

            // Bit[1:0] DP Connect Status
            if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x00)
            {
                // Bit[1:0] = b'00 => Both DP_TX / DP_RX Disconnected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_CONNECT_NONE);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x01)
            {
                // Bit[1:0] = b'01 => DP_TX Connected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_TX_CONNECTED);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x02)
            {
                // Bit[1:0] = b'10 => DP_RX Connected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_RX_CONNECTED);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x03)
            {
                // Bit[1:0] = b'11 => Both DP_TX / DP_RX Connected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_TX_RX_BOTH_CONNECTED);
            }

#if(_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1)
            // Bit[2] DP Power Low, DP2.0 : Only DFP Need to Update
            // Bit[3] DP Function Enabled, DP2.0 : Only DFP Need to Update
            // Bit[4] Multi-Function Prefer, DP2.0 : Only DFP Need to Update
            // Bit[5] Usb Config Request, DP2.0 : Only DFP Need to Update
            // Bit[6] DP ALT Mode Exit Request, DP2.0 : Only DFP Need to Update
#else
            // Bit[2] DP Power Low, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT2) == _BIT2)
            {
                SET_TYPE_C_1_PD_PARTNER_DP_POWER_LOW();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_DP_POWER_LOW();
            }

            // Bit[3] DP Function Enabled, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT3) == _BIT3)
            {
                SET_TYPE_C_1_PD_PARTNER_DP_FUNCTION_ENABLE();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_DP_FUNCTION_ENABLE();
            }

            // Bit[4] Multi-Function Prefer, DP2.1 : Only DFP Need to Update
            // Bit[5] Usb Config Request, DP2.1 : Only DFP Need to Update When Receive Attention
            // Bit[6] DP ALT Mode Exit Request, DP2.1 : Only DFP Need to Update When Receive Attention
#endif  // End of #if(_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1)

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
            // Bit[8:7] IRQ_HPD / HPD State, Only DPTX Need to Update
            if((g_pucTypeC1PdDataObject_EXINT[6] & _BIT0) == _BIT0)
            {
                SET_TYPE_C_1_PD_PARTNER_HPD_TYPE(_PD_HPD_IRQ);
            }
            else
            {
                if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT7) == _BIT7)
                {
                    SET_TYPE_C_1_PD_PARTNER_HPD_TYPE(_PD_HPD_HIGH);
                }
                else
                {
                    SET_TYPE_C_1_PD_PARTNER_HPD_TYPE(_PD_HPD_LOW);
                }
            }
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)

            break;

        case _PD_VDM_DP_CMD_DP_STATUS_ACK:

            // Bit[1:0] DP Connect Status
            if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x00)
            {
                // Bit[1:0] = b'00 => Both DP_TX / DP_RX Disconnected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_CONNECT_NONE);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x01)
            {
                // Bit[1:0] = b'01 => DP_TX Connected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_TX_CONNECTED);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x02)
            {
                // Bit[1:0] = b'10 => DP_RX Connected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_RX_CONNECTED);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x03)
            {
                // Bit[1:0] = b'11 => Both DP_TX / DP_RX Connected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_TX_RX_BOTH_CONNECTED);
            }

#if(_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1)
            // Bit[2] DP Power Low, DP2.0 : Only DFP Need to Update
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT2) == _BIT2)
            {
                SET_TYPE_C_1_PD_PARTNER_DP_POWER_LOW();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_DP_POWER_LOW();
            }

            // Bit[3] DP Function Enabled, DP2.0 : Only DFP Need to Update
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT3) == _BIT3)
            {
                SET_TYPE_C_1_PD_PARTNER_DP_FUNCTION_ENABLE();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_DP_FUNCTION_ENABLE();
            }

            // Bit[4] Multi-Function Prefer, DP2.0 : Only DFP Need to Update
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT4) == _BIT4)
            {
                SET_TYPE_C_1_PD_PARTNER_MULTI_FUNCTION();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_MULTI_FUNCTION();
            }

            // Bit[5] Usb Config Request, DP2.0 : Only DFP Need to Update
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT5) == _BIT5)
            {
                SET_TYPE_C_1_PD_PARTNER_USB_CONFIG_REQUEST();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_USB_CONFIG_REQUEST();
            }

            // Bit[6] DP ALT Mode Exit Request, DP2.0 : Only DFP Need to Update
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT6) == _BIT6)
            {
                SET_TYPE_C_1_PD_PARTNER_DP_ALT_MODE_EXIT_REQ();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_DP_ALT_MODE_EXIT_REQ();
            }
#else
            // Bit[2] DP Power Low, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention
            // Bit[3] DP Function Enabled, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention

            // Bit[4] Multi-Function Prefer, DP2.1 : Only DFP Need to Update
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT4) == _BIT4)
            {
                SET_TYPE_C_1_PD_PARTNER_MULTI_FUNCTION();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_MULTI_FUNCTION();
            }

            // Bit[5] Usb Config Request, DP2.1 : Only DFP Need to Update When Receive Attention
            // Bit[6] DP ALT Mode Exit Request, DP2.1 : Only DFP Need to Update When Receive Attention
#endif  // End of #if(_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1)

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
            // Bit[8:7] IRQ_HPD / HPD State, Only DPTX Need to Update
            if((g_pucTypeC1PdDataObject_EXINT[6] & _BIT0) == _BIT0)
            {
                SET_TYPE_C_1_PD_PARTNER_HPD_TYPE(_PD_HPD_IRQ);
            }
            else
            {
                if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT7) == _BIT7)
                {
                    SET_TYPE_C_1_PD_PARTNER_HPD_TYPE(_PD_HPD_HIGH);
                }
                else
                {
                    SET_TYPE_C_1_PD_PARTNER_HPD_TYPE(_PD_HPD_LOW);
                }
            }
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)

            break;

        case _PD_VDM_DP_CMD_ATTENTION_REQ:

            // Bit[1:0] DP Connect Status
            if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x00)
            {
                // Bit[1:0] = b'00 => Both DP_TX / DP_RX Disconnected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_CONNECT_NONE);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x01)
            {
                // Bit[1:0] = b'01 => DP_TX Connected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_TX_CONNECTED);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x02)
            {
                // Bit[1:0] = b'10 => DP_RX Connected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_RX_CONNECTED);
            }
            else if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x03)
            {
                // Bit[1:0] = b'11 => Both DP_TX / DP_RX Connected
                SET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS(_PD_DP_TX_RX_BOTH_CONNECTED);
            }

            // Bit[2] DP Power Low, DP2.0 : Only DFP Need to Update
            // Bit[2] DP Power Low, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT2) == _BIT2)
            {
                SET_TYPE_C_1_PD_PARTNER_DP_POWER_LOW();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_DP_POWER_LOW();
            }

            // Bit[3] DP Function Enabled, DP2.0 : Only DFP Need to Update
            // Bit[3] DP Function Enabled, DP2.1 : UFP Need to Update When Receive Dp_Status_Req, and DFP Need to Update When Receive Attention
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT3) == _BIT3)
            {
                SET_TYPE_C_1_PD_PARTNER_DP_FUNCTION_ENABLE();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_DP_FUNCTION_ENABLE();
            }

            // Bit[4] Multi-Function Prefer, DP2.0 : Only DFP Need to Update
            // Bit[4] Multi-Function Prefer, DP2.1 : Only DFP Need to Update
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT4) == _BIT4)
            {
                SET_TYPE_C_1_PD_PARTNER_MULTI_FUNCTION();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_MULTI_FUNCTION();
            }

            // Bit[5] Usb Config Request, DP2.0 : Only DFP Need to Update
            // Bit[5] Usb Config Request, DP2.1 : Only DFP Need to Update When Receive Attention
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT5) == _BIT5)
            {
                SET_TYPE_C_1_PD_PARTNER_USB_CONFIG_REQUEST();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_USB_CONFIG_REQUEST();
            }

            // Bit[6] DP ALT Mode Exit Request, DP2.0 : Only DFP Need to Update
            // Bit[6] DP ALT Mode Exit Request, DP2.1 : Only DFP Need to Update When Receive Attention
            if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT6) == _BIT6)
            {
                SET_TYPE_C_1_PD_PARTNER_DP_ALT_MODE_EXIT_REQ();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_DP_ALT_MODE_EXIT_REQ();
            }

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
            // Bit[8:7] IRQ_HPD / HPD State, Only DPTX Need to Update
            if((g_pucTypeC1PdDataObject_EXINT[6] & _BIT0) == _BIT0)
            {
                SET_TYPE_C_1_PD_PARTNER_HPD_TYPE(_PD_HPD_IRQ);
            }
            else
            {
                if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT7) == _BIT7)
                {
                    SET_TYPE_C_1_PD_PARTNER_HPD_TYPE(_PD_HPD_HIGH);
                }
                else
                {
                    SET_TYPE_C_1_PD_PARTNER_HPD_TYPE(_PD_HPD_LOW);
                }
            }
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
            // Bit[9] No DP ALT Suspend, DP2.1 : Only DFP Need to Update When Receive Attention
            if((g_pucTypeC1PdDataObject_EXINT[6] & _BIT1) == _BIT1)
            {
                SET_TYPE_C_1_PD_PARTNER_NO_DP_ALT_SUSPEND();
            }
            else
            {
                CLR_TYPE_C_1_PD_PARTNER_NO_DP_ALT_SUSPEND();
            }
#endif  // End of #if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check if to Send DP Config
// Input Value  : None
// Output Value : _PD_CONFIG_REQUIRED (Send DP Config)/ _PD_CONFIG_NOT_REQUIRED (Maintain Current Config or Exit Mode)
//--------------------------------------------------
EnumTypeCPDDpStatusCheckResult ScalerTypeC1PdCheckDpStatus_EXINT0(void)
{
    BYTE ucMultiFunctionPrefer = (((g_pucTypeC1PdDataObject_EXINT[7] & _BIT4) == _BIT4) ? _TRUE : _FALSE);

    SET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG(_PD_DP_CONFIG);

    // Display Port Status : [6] Exit DP Request / [5] USB Config Request / [4] Multi-Func = X
    // [3] Adaptor Func = 1 / [2] Power Low = 0 / [1:0] DP_TX Connected = 01/DP_RX Connected = 10
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
#if(_TYPE_C_EMB_CTS_FLOW == _ON)
    // DFP Check DP_TX Connected
    if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT0)) != _BIT0)
    {
        SET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG(_PD_USB_CONFIG);
    }
#endif

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    // DFP Check DP_RX Connected
    if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1)) != _BIT1)
    {
        SET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG(_PD_USB_CONFIG);
    }
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

    if((ucMultiFunctionPrefer == _TRUE) && (GET_TYPE_C_1_PD_PARTNER_MULTI_FUNCTION() == _FALSE))
    {
        // Set Multi-Function Bit Change in DP Config(Pin Assignment C <=> Pin Assignment D)
        if(GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG)
        {
            SET_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE();
        }
    }
    else if((ucMultiFunctionPrefer == _FALSE) && (GET_TYPE_C_1_PD_PARTNER_MULTI_FUNCTION() == _TRUE))
    {
        // Set Multi-Function Bit Change in DP Config(Pin Assignment C <=> Pin Assignment D)
        if(GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG)
        {
            SET_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE();
        }
    }
    else
    {
        CLR_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE();
    }

    // DFP Check USB Configuration Request Bit
    if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT5) == _BIT5)
    {
        SET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG(_PD_USB_CONFIG);
    }

    // DFP Check Exit Mode Bit
    if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT6) == _BIT6)
    {
        SET_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ();
        SET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG(_PD_USB_CONFIG);

        if(GET_TYPE_C_1_PD_PIN_ASSIGNMENT() == _TYPE_C_PIN_ASSIGNMENT_E)
        {
            // For C-DP Cable: DFP Shall not Send Exit Mode, But Still Send DP Config(USB) to DP_RX
            CLR_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ();
        }
    }

    // Check: Multi-Function Bit Change in DP Config(Pin Assignment C <=> Pin Assignment D)
    if((GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) && (GET_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE() == _TRUE))
    {
        // DP Config Required(Pin C => Pin D): (Current Pin Assignment = C) && (Both Support Pin Assignment D) && (Multi-Function = _TRUE)
        if((GET_TYPE_C_1_PD_PIN_ASSIGNMENT() == _TYPE_C_PIN_ASSIGNMENT_C) && ((GET_TYPE_C_1_PD_PARTNER_PIN_ASSIGNMENT() & GET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP() & _TYPE_C_PIN_ASSIGNMENT_D) != 0x00) && (ucMultiFunctionPrefer == _TRUE))
        {
            return _PD_CONFIG_REQUIRED;
        }
        // DP Config Required(Pin D => Pin C): (Current Pin Assignment = D) && (Both Support Pin Assignment C) && (Multi-Function = _FALSE)
        else if((GET_TYPE_C_1_PD_PIN_ASSIGNMENT() == _TYPE_C_PIN_ASSIGNMENT_D) && ((GET_TYPE_C_1_PD_PARTNER_PIN_ASSIGNMENT() & GET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP() & _TYPE_C_PIN_ASSIGNMENT_C) != 0x00) && (ucMultiFunctionPrefer == _FALSE))
        {
            return _PD_CONFIG_REQUIRED;
        }
        else
        {
            CLR_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE();
        }
    }

    if(GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == GET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG())
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
// Input Value  : None
// Output Value : EnumTypeCPDAltModeState(_PD_ALT_MODE_SEND_ENTER_MODE / _PD_ALT_MODE_ERROR)
//--------------------------------------------------
EnumTypeCPDAltModeState ScalerTypeC1PdJudgeCableId_EXINT0(void)
{
    // Judge Whether The Cable Supports DP Functionality, and Switch DP_ALT_STATE
    if(GET_TYPE_C_1_PD_CBL_PRODUCT_TYPE() == _PD_PASSIVE_CABLE)
    {
        if(GET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_2_ONLY)
        {
            // Stop Enter DP Alt Mode Flow Both for Device & Cable
            return _PD_ALT_MODE_ERROR;
        }
        else if(GET_TYPE_C_1_PD_CBL_MODAL_OPERATION_SUPPORT() == _FALSE)
        {
            if((GET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_3_GEN1) || (GET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_3OR4_GEN2))
            {
                SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR10);
            }
            else if(GET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_4_GEN3)
            {
                SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR20);

                // UHBR20 Capable Passive Cable Shall Support UHBR13.5
                SET_TYPE_C_1_PD_CBL_UHBR13P5_SUPPORT();
            }

            // Stop Enter DP Alt Mode Flow Just for Cable
            CLR_TYPE_C_1_PD_CBL_ENTER_DP_MODE_SUPPORT();

            return _PD_ALT_MODE_SEND_ENTER_MODE;
        }
        else
        {
            // On-going Enter DP Alt Mode Flow Both for Device & Cable
            return _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P;
        }
    }
    else if(GET_TYPE_C_1_PD_CBL_PRODUCT_TYPE() == _PD_ACTIVE_CABLE)
    {
        if(GET_TYPE_C_1_PD_CBL_MODAL_OPERATION_SUPPORT() == _FALSE)
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
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSearchCableSvid_EXINT0(void)
{
    CLR_TYPE_C_1_PD_CBL_SVID_SEARCH_FINISH();

    for(BYTE ucLoopIndex = 0; ucLoopIndex < (GET_TYPE_C_1_PD_RCV_NOD_CNT() * 4); ucLoopIndex = ucLoopIndex + 2)
    {
        if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex] == 0xFF) && (g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 1] == 0x01))
        {   // if SVID = DP_SID (0xFF01), Set Cable DP Svid Support
            SET_TYPE_C_1_PD_CBL_DP_SVID_SUPPORT();
        }
        else if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex] == 0x80) && (g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 1] == 0x87))
        {   // if SVID = TBT3_SID (0x8087), Set Cable TBT3 Svid Support
            SET_TYPE_C_1_PD_CBL_TBT3_SVID_SUPPORT();
        }
        else if((g_pucTypeC1PdDataObject_EXINT[ucLoopIndex] == 0x00) && (g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 1] == 0x00))
        {   // if SVID = 0x00, Search Finish
            SET_TYPE_C_1_PD_CBL_SVID_SEARCH_FINISH();
        }
    }
}

//--------------------------------------------------
// Description  : Record Cable Info Of Discover Dp Mode Ack
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSaveCableDpModeInfo_EXINT0(void)
{
    // Bit[31:30] VDO Version
    if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT7 | _BIT6)) == 0x00)
    {
        SET_TYPE_C_1_PD_CBL_DPAM_VERSION(_PD_DPAM_VER_2_0_EARLIER);
    }
    else if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT7 | _BIT6)) == _BIT6)
    {
        SET_TYPE_C_1_PD_CBL_DPAM_VERSION(_PD_DPAM_VER_2_1_HIGHER);
    }

    // Bit[29:28] Active Components.
    // When In DPAM:  1.[31:30] VDO Version = 1, Discover Mode Ack Takes Priority;  2.[31:30] VDO Version = 0, Discover ID Ack Takes Priotity.
    if(GET_TYPE_C_1_PD_CBL_DPAM_VERSION() == _PD_DPAM_VER_2_1_HIGHER)
    {
        if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT5 | _BIT4)) == 0x00)
        {
            SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_PASSIVE);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT5 | _BIT4)) == _BIT4)
        {
            SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_ACTIVE_RETIMER);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT5 | _BIT4)) == _BIT5)
        {
            SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_ACTIVE_REDRIVER);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
        {
            SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_OPTICAL);
        }

        // Bit[26] Cable UHBR13.5 Support: Y/N
        if((g_pucTypeC1PdDataObject_EXINT[4] & _BIT2) == _BIT2)
        {
            SET_TYPE_C_1_PD_CBL_UHBR13P5_SUPPORT();
        }

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
        // Bit[23:16] DP Sink Device Pin Assignments Supported
        if(g_pucTypeC1PdDataObject_EXINT[5] == 0x0C)
        {
            SET_TYPE_C_1_PD_CBL_PIN_ASSIGNMENT(_PD_CBL_PIN_ASSIGNMENT_C_AND_D);
        }
        else if(g_pucTypeC1PdDataObject_EXINT[5] == 0x10)
        {
            SET_TYPE_C_1_PD_CBL_PIN_ASSIGNMENT(_PD_CBL_PIN_ASSIGNMENT_E);
        }
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
        // Bit[15:8] DP Source Device Pin Assignments Supported
        if(g_pucTypeC1PdDataObject_EXINT[6] == 0x0C)
        {
            SET_TYPE_C_1_PD_CBL_PIN_ASSIGNMENT(_PD_CBL_PIN_ASSIGNMENT_C_AND_D);
        }
        else if(g_pucTypeC1PdDataObject_EXINT[6] == 0x10)
        {
            SET_TYPE_C_1_PD_CBL_PIN_ASSIGNMENT(_PD_CBL_PIN_ASSIGNMENT_E);
        }
#endif

        // Bit[5:2] Signalling for Cable Information Transport of DisplayPort Protocol
        if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT4) == _BIT4)
        {
            SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR20);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT3) == _BIT3)
        {
            SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR10);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT2) == _BIT2)
        {
            SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_HBR3);
        }
    }
    else // Save DPAM 2.0 Cable Info.
    {
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
        // Bit[23:16] DP Sink Device Pin Assignments Supported
        if(g_pucTypeC1PdDataObject_EXINT[5] == 0x0C)
        {
            SET_TYPE_C_1_PD_CBL_PIN_ASSIGNMENT(_PD_CBL_PIN_ASSIGNMENT_C_AND_D);
        }
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
        // Bit[15:8] DP Source Device Pin Assignments Supported
        if(g_pucTypeC1PdDataObject_EXINT[6] == 0x0C)
        {
            SET_TYPE_C_1_PD_CBL_PIN_ASSIGNMENT(_PD_CBL_PIN_ASSIGNMENT_C_AND_D);
        }
#endif

        // Bit[5:2] Signalling for Cable Information Transport of DisplayPort Protocol
        if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT2) == _BIT2)
        {
            SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_HBR3);
        }
    }
}

//--------------------------------------------------
// Description  : Record Cable Info Of TBT3 Discover Mode Ack
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSaveCableTbt3ModeInfo_EXINT0(void)
{
    // Bit[25] TBT3 Passive Cable(0b') / Active Cable(1b')
    if((g_pucTypeC1PdDataObject_EXINT[4] & _BIT1) == _BIT1)
    {
        SET_TYPE_C_1_PD_CBL_TBT3_PRODUCT_TYPE(_PD_CBL_TBT3_ACTIVE_CABLE);
    }
    else
    {
        SET_TYPE_C_1_PD_CBL_TBT3_PRODUCT_TYPE(_PD_CBL_TBT3_PASSIVE_CABLE);
    }

    // Bit[23] Active Cable Plug Link Training:  Active With Bi-Directional LSRX Or When Passive(0b') / Active With Uni-Directional LSRX(1b')
    if((g_pucTypeC1PdDataObject_EXINT[5] & _BIT7) == _BIT7)
    {
        SET_TYPE_C_1_PD_CBL_TBT3_DIRECTION(_PD_CBL_TBT3_UNIDIRECTION);
    }
    else
    {
        SET_TYPE_C_1_PD_CBL_TBT3_DIRECTION(_PD_CBL_TBT3_BIDIRECTION);
    }

    // Bit[22] Re-Timer Y/N
    if((g_pucTypeC1PdDataObject_EXINT[5] & _BIT6) == _BIT6)
    {
        SET_TYPE_C_1_PD_CBL_TBT3_RETIMER();
    }

    // Bit[21] Cable Type Optical Y/N
    if((g_pucTypeC1PdDataObject_EXINT[5] & _BIT5) == _BIT5)
    {
        SET_TYPE_C_1_PD_CBL_TBT3_OPTICAL();
    }

    // Bit[20:19] TBT Rounded Support
    if((g_pucTypeC1PdDataObject_EXINT[5] & (_BIT4 | _BIT3)) == 0x00)
    {
        SET_TYPE_C_1_PD_CBL_TBT3_ROUNDED_SUPPORT(_PD_CBL_TBT3_3RD_GEN_NON_ROUNDED);
    }
    else if((g_pucTypeC1PdDataObject_EXINT[5] & (_BIT4 | _BIT3)) == _BIT3)
    {
        SET_TYPE_C_1_PD_CBL_TBT3_ROUNDED_SUPPORT(_PD_CBL_TBT3_3RD_AND_4TH_GEN_ROUNDED);
    }

    // Bit[18:16] Cable Speed
    if((g_pucTypeC1PdDataObject_EXINT[5] & (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
    {
        SET_TYPE_C_1_PD_CBL_TBT3_SPEED(_PD_CBL_TBT3_U3P1_GEN1);
    }
    else if((g_pucTypeC1PdDataObject_EXINT[5] & (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
    {
        SET_TYPE_C_1_PD_CBL_TBT3_SPEED(_PD_CBL_TBT3_10G);
    }
    else if((g_pucTypeC1PdDataObject_EXINT[5] & (_BIT2 | _BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        SET_TYPE_C_1_PD_CBL_TBT3_SPEED(_PD_CBL_TBT3_20G);
    }
}

//--------------------------------------------------
// Description  : Judge DP Functionality Support Of Cable
// Input Value  : None
// Output Value : EnumTypeCPDAltModeState(_PD_ALT_MODE_SEND_ENTER_MODE / _PD_ALT_MODE_ERROR)
//--------------------------------------------------
EnumTypeCPDAltModeState ScalerTypeC1PdJudgeCableDpFunctionality_EXINT0(void)
{
    if(GET_TYPE_C_1_PD_CBL_DP_MODE_INFO_RECEIVED() == _TRUE)
    {
        // If Already Received Cable DP Discover Mode Ack, Do Enter Mode When Not Received Cable TBT3 Discover Mode ACK.
        // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Enter Mode First
        if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
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
        if(GET_TYPE_C_1_PD_CBL_PRODUCT_TYPE() == _PD_PASSIVE_CABLE)
        {
            if((GET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_3_GEN1) || (GET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_3OR4_GEN2))
            {
                SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR10);
            }
            else if(GET_TYPE_C_1_PD_CBL_USB_HIGHEST_SPEED() == _PD_CBL_USB_4_GEN3)
            {
                SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR20);

                // UHBR20 Capable Passive Cable Shall Support UHBR13.5
                SET_TYPE_C_1_PD_CBL_UHBR13P5_SUPPORT();
            }

            // Stop Enter DP Alt Mode Flow Just for Cable
            CLR_TYPE_C_1_PD_CBL_ENTER_DP_MODE_SUPPORT();

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
// Input Value  : None
// Output Value : EnumTypeCPDAltModeState(_PD_ALT_MODE_SEND_ENTER_MODE / _PD_ALT_MODE_ERROR)
//--------------------------------------------------
EnumTypeCPDAltModeState ScalerTypeC1PdJudgeCableTbt3Mode_EXINT0(void)
{
    if(GET_TYPE_C_1_PD_CBL_DP_MODE_INFO_RECEIVED() == _TRUE)
    {
        // If Cable Support DP Mode + TBT3 Mode : Update Cable Active Component and Do Enter Mode When Received Cable TBT3 Discover Mode Ack.
        if((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_PASSIVE) && (GET_TYPE_C_1_PD_CBL_TBT3_PRODUCT_TYPE() == _PD_CBL_TBT3_ACTIVE_CABLE))
        {
            if(GET_TYPE_C_1_PD_CBL_TBT3_RETIMER() == _TRUE)
            {
                SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_ACTIVE_RETIMER);
            }
            else
            {
                SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_ACTIVE_REDRIVER);
            }
        }

        // If DPAM Version is 2.1 or Higher and Cable is Active Cable, Send SOP' Enter Mode First
        if((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER) && ((GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_RETIMER) || (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() == _PD_CBL_COMPONENT_ACTIVE_REDRIVER)))
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
        if((GET_TYPE_C_1_PD_CBL_TBT3_RETIMER() == _FALSE) && (GET_TYPE_C_1_PD_CBL_TBT3_PRODUCT_TYPE() == _PD_CBL_TBT3_PASSIVE_CABLE))
        {
            if((GET_TYPE_C_1_PD_CBL_TBT3_SPEED() == _PD_CBL_TBT3_U3P1_GEN1) || ((GET_TYPE_C_1_PD_CBL_TBT3_SPEED() == _PD_CBL_TBT3_10G)))
            {
                SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR10);
            }
            else if(GET_TYPE_C_1_PD_CBL_TBT3_SPEED() == _PD_CBL_TBT3_20G)
            {
                SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR20);

                // UHBR20 Capable Passive Cable Shall Support UHBR13.5
                SET_TYPE_C_1_PD_CBL_UHBR13P5_SUPPORT();
            }

            // Stop Enter DP Alt Mode Flow Just for Cable
            CLR_TYPE_C_1_PD_CBL_ENTER_DP_MODE_SUPPORT();

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
void ScalerTypeC1PdUfpSaveCableInfoForDpcd_EXINT0(void)
{
    // Bit[31:30] VDO Version
    if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT7 | _BIT6)) == 0x00)
    {
        SET_TYPE_C_1_PD_PARTNER_DPAM_VERSION(_PD_DPAM_VER_2_0_EARLIER);
    }
    else if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT7 | _BIT6)) == _BIT6)
    {
        SET_TYPE_C_1_PD_PARTNER_DPAM_VERSION(_PD_DPAM_VER_2_1_HIGHER);
    }

    if(GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER)
    {
        // Bit[29:28] Cable Active Components
        if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT5 | _BIT4)) == 0x00)
        {
            SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_PASSIVE);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT5 | _BIT4)) == _BIT4)
        {
            SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_ACTIVE_RETIMER);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT5 | _BIT4)) == _BIT5)
        {
            SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_ACTIVE_REDRIVER);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
        {
            SET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT(_PD_CBL_COMPONENT_OPTICAL);
        }

        // Bit[26] Cable UHBR13.5 Support: Y/N
        if((g_pucTypeC1PdDataObject_EXINT[4] & _BIT2) == _BIT2)
        {
            SET_TYPE_C_1_PD_CBL_UHBR13P5_SUPPORT();
        }

        // Bit[5:2] Signalling for Cable Information Transport of DisplayPort Protocol
        if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT4) == _BIT4)
        {
            SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR20);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT3) == _BIT3)
        {
            SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_UHBR10);
        }
        else if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT2) == _BIT2)
        {
            SET_TYPE_C_1_PD_CBL_MAX_DP_RATE(_PD_CBL_MAX_HBR3);
        }
    }
}
#endif  // End of #if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)

//--------------------------------------------------
// Description  : Check if DP_Config is Valid @ Interrupt
// Input Value  : None
// Output Value : _TRUE(REQ as DP_RX & Pin Assignment C / D / E || Config USB & Pin Assignment NONE)/_FALSE
//--------------------------------------------------
BYTE ScalerTypeC1PdCheckDpConfig_EXINT0(void)
{
    BYTE ucCheckResult = _FALSE;

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    // Check if Request DP_RX (VDO1[1:0] = b'10)
    if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == _BIT1)
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    // Check if Request DP_TX (VDO1[1:0] = b'01)
    if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == _BIT0)
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    {
        switch(g_pucTypeC1PdDataObject_EXINT[6])
        {
            case _TYPE_C_PIN_ASSIGNMENT_C:
            case _TYPE_C_PIN_ASSIGNMENT_D:
            case _TYPE_C_PIN_ASSIGNMENT_E:

                SET_TYPE_C_1_PD_PIN_ASSIGNMENT(g_pucTypeC1PdDataObject_EXINT[6]);
                ucCheckResult = _TRUE;

                break;

            default:

                ucCheckResult = _FALSE;

                break;
        }
    }
    // Check if Request USB Configuration (VDO1[1:0] = b'00)
    else if((g_pucTypeC1PdDataObject_EXINT[7] & (_BIT1 | _BIT0)) == 0x00)
    {
        SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);
        ucCheckResult = _TRUE;
    }
    else
    {
        ucCheckResult = _FALSE;
    }

    return ucCheckResult;
}

//--------------------------------------------------
// Description  : DFP Judge Target Pin Assignment By Partner Capability
// Input Value  : None
// Output Value : Target Pin Assignment to be Configured
//--------------------------------------------------
BYTE ScalerTypeC1PdDfpJudgePinAssignment_EXINT0(void)
{
    BYTE ucMultiFunctionPrefer = (((g_pucTypeC1PdDataObject_EXINT[7] & _BIT4) == _BIT4) ? _TRUE : _FALSE);
    BYTE ucPinAssignment = (GET_TYPE_C_1_PD_PARTNER_PIN_ASSIGNMENT() & (BYTE)GET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP());
    SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_NONE);

    if((ucMultiFunctionPrefer == _TRUE) && ((ucPinAssignment & _BIT3) == _BIT3))
    {
        // If "Multi-Function = 1" and "Pin Assignment D Support"
        SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_D);
    }
    else if((ucPinAssignment & _BIT2) == _BIT2)
    {
        // If "Pin Assignment C Support"
        SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_C);
    }
    else if((ucPinAssignment & _BIT3) == _BIT3)
    {
        // If "Pin Assignment D Support"
        SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_D);
    }
    else if((ucPinAssignment & _BIT4) == _BIT4)
    {
        // If "Pin Assignment E Support"
        SET_TYPE_C_1_PD_PIN_ASSIGNMENT(_TYPE_C_PIN_ASSIGNMENT_E);
    }

    if(GET_TYPE_C_1_PD_PIN_ASSIGNMENT() != _TYPE_C_PIN_ASSIGNMENT_NONE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
//--------------------------------------------------
// Description  : Pop HPD from HPD Queue @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdPopHpd_EXINT0(void)
{
    EnumInputPort enumInputPort = ScalerTypeCPcbPortConvertToDx_EXINT0(ScalerTypeCxPcbxMapping_EXINT0(_EMB_TYPE_C_1));

    if(GET_TYPE_C_1_PD_HPD_CNT() > 0)
    {
        // Update HPD Status For DP Usage
        if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) == _PD_HPD_LOW)
        {
            ScalerDpAuxRxHpdTogglePhyResetProc(enumInputPort, _LOW);
            SET_TYPE_C_1_PD_HPD_STATUS(_LOW);
        }
        else if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) == _PD_HPD_HIGH)
        {
            ScalerDpAuxRxHpdTogglePhyResetProc(enumInputPort, _HIGH);
            SET_TYPE_C_1_PD_HPD_STATUS(_HIGH);
        }

        CLR_TYPE_C_1_PD_HPD_QUEUE();
        CLR_TYPE_C_1_PD_HPD_SPACE_TIME();

        // Adjust HPD Queue
        ADD_TYPE_C_1_PD_HPD_RPTR();
        SUB_TYPE_C_1_PD_HPD_CNT();
    }
}

//--------------------------------------------------
// Description  : Force Sending HPD IRQ for DP CTS @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdDpCTSForceHpdIrq_EXINT0(void)
{
    BYTE ucSendResult = _FAIL;
    EnumTypeCTxCheckResult enumTxCheckResult = _PD_TX_NOT_AVAILABLE;

    if((GET_TYPE_C_1_PD_HANDLER_ONGOING() == _FALSE) && (GET_TYPE_C_1_PD_HPD_STATUS() == _HIGH) &&
       (((GET_TYPE_C_1_PD_FW_STATE() == _PD_SRC_READY) && (GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SRC_READY)) || ((GET_TYPE_C_1_PD_FW_STATE() == _PD_SNK_READY) && (GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SNK_READY))) &&
       (GET_TYPE_C_1_PD_AMS_STATUS() == _PD_AMS_NONE) && (GET_TYPE_C_1_PD_SYS_EVENT() == _PD_SYS_EVENT_NONE) && (GET_TYPE_C_1_PD_ATTENTION_WAIT() == _FALSE))
    {
        if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_UFP)
        {
            enumTxCheckResult = ScalerTypeC1PdTxAvaliable_EXINT0();

            if(enumTxCheckResult == _PD_TX_AVAILABLE)
            {
                SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ATTENTION);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

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
                SET_TYPE_C_1_PD_FORCE_HPD_IRQ();

                // Send "Attention REQ"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);

                ucSendResult = _SUCCESS;
            }
            else if(enumTxCheckResult == _PD_TX_WAIT_SRC_INIT_AMS_TIMER)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);

                // Set Macro to Force Sending HPD IRQ (ignore HPD Queue When Costruct DP Status's or Attention's Data Object)
                SET_TYPE_C_1_PD_FORCE_HPD_IRQ();

                ucSendResult = _SUCCESS;
            }
        }
        else
        {
            enumTxCheckResult = ScalerTypeC1PdTxAvaliable_EXINT0();

            if(enumTxCheckResult == _PD_TX_AVAILABLE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

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
                SET_TYPE_C_1_PD_FORCE_HPD_IRQ();

                // Send "DP Status REQ"
                ScalerTypeC1PdSendMsg_EXINT0(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_10);

                ucSendResult = _SUCCESS;
            }
            else if(enumTxCheckResult == _PD_TX_WAIT_SRC_INIT_AMS_TIMER)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);

                // Set Macro to Force Sending HPD IRQ (ignore HPD Queue When Costruct DP Status's or Attention's Data Object)
                SET_TYPE_C_1_PD_FORCE_HPD_IRQ();

                ucSendResult = _SUCCESS;
            }
        }
    }

    if(ucSendResult == _FAIL)
    {
        // Push HPD_IRQ into HPD Queue When Force Sending HPD IRQ Failed, then PD will Re-Send HPD_IRQ in Main loop
        ScalerTypeC1PdPushHpd_EXINT0(_PD_HPD_IRQ, 0);
    }
}

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
//--------------------------------------------------
// Description  : DP_TX Update DP_RX HPD Status @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumTypeCPDHpdType ScalerTypeC1PdDecodePartnerHpdStatus_EXINT0(void)
{
    EnumTypeCPDHpdType enumHpdType = _PD_HPD_NONE;

    if((g_pucTypeC1PdDataObject_EXINT[6] & _BIT0) == _BIT0)
    {
        enumHpdType = _PD_HPD_IRQ;
    }
    else
    {
        if((g_pucTypeC1PdDataObject_EXINT[7] & _BIT7) == _BIT7)
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
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
#endif  // End of #if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : Check Lenovo Get Status @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdCheckLenovoStatus_EXINT0(void)
{
    SET_TYPE_C_1_PD_LENOVO_SYS_ACKNOWLEDGE(g_pucTypeC1PdDataObject_EXINT[5]);
    SET_TYPE_C_1_PD_LENOVO_SYS_EVENT(g_pucTypeC1PdDataObject_EXINT[6]);
}

//--------------------------------------------------
// Description  : Check Lenovo Device ID @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdCheckLenovoDeviceId_EXINT0(void)
{
    SET_TYPE_C_1_PD_LENOVO_DEVICE_TYPE(g_pucTypeC1PdDataObject_EXINT[7]);
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : Get Acer System Event when Rcv. Acer Get Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdGetAcerSysStatus_EXINT0(void)
{
    SET_TYPE_C_1_PD_ACER_SYS_EVENT(_TYPE_C_ACER_SYS_EVENT_STATUS_REQ);

    // User VDM Data = Rcv Data Object - VDM Header
    SET_TYPE_C_1_PD_ACER_SYS_VDM_CNT(GET_TYPE_C_1_PD_RCV_NOD_CNT() - 1);

    // Get Acer VDM Data Contents
    for(BYTE ucLoopIndex = 0; ucLoopIndex < (GET_TYPE_C_1_PD_ACER_SYS_VDM_CNT() * 4); ucLoopIndex++)
    {
        SET_TYPE_C_1_PD_ACER_SYS_VDM_DATA(ucLoopIndex, g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 4]);
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : Set Hp Own I2C Address and AM Address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetHpOwnAddr_EXINT0(void)
{
    SET_TYPE_C_1_PD_HP_I2C_ADDR(((g_pucTypeC1PdDataObject_EXINT[4] & (_BIT2 | _BIT1 | _BIT0)) << 4) | ((g_pucTypeC1PdDataObject_EXINT[5] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
    SET_TYPE_C_1_PD_HP_OWN_AM_ADDR_H(g_pucTypeC1PdDataObject_EXINT[5] & (_BIT1 | _BIT0));
    SET_TYPE_C_1_PD_HP_OWN_AM_ADDR_M(g_pucTypeC1PdDataObject_EXINT[6]);
    SET_TYPE_C_1_PD_HP_OWN_AM_ADDR_L(g_pucTypeC1PdDataObject_EXINT[7]);
}

//--------------------------------------------------
// Description  : Check if Hp AM Address is Valid @ Interrupt
// Input Value  : None
// Output Value : _TRUE(Ignore AM Address || AM Address is Valid)/_FALSE
//--------------------------------------------------
BYTE ScalerTypeC1PdCheckHpVdmValid_EXINT0(void)
{
    BYTE ucCheckResult = _FALSE;

    // Rev. HP AM Address
    BYTE ucHpRevAmAddr_H = (g_pucTypeC1PdDataObject_EXINT[5] & (_BIT1 | _BIT0));
    BYTE ucHpRevAmAddr_M = (g_pucTypeC1PdDataObject_EXINT[6]);
    BYTE ucHpRevAmAddr_L = (g_pucTypeC1PdDataObject_EXINT[7]);

    switch((EnumTypeCVdmHpCmd)GET_TYPE_C_1_PD_RCV_VDM_CMD())
    {
        // ------------ AM Address Do not Exist ------------
        // AM Address do not Exist, so Return True Directly
        case _PD_VDM_HP_CMD_DISCOVER_MODE_REQ:
        case _PD_VDM_HP_CMD_ENTER_MODE_REQ:
        case _PD_VDM_HP_CMD_EXIT_MODE_REQ:
        case _PD_VDM_HP_CMD_SET_CONFIG_REQ:

            ucCheckResult = _TRUE;

            break;

        // --------------- AM Address Exist ---------------
        // If AM Address Exist, Need to Check Address is Valid or not
        case _PD_VDM_HP_CMD_GET_CONFIG_REQ:
        case _PD_VDM_HP_CMD_SET_DATA_REQ:
        case _PD_VDM_HP_CMD_SET_VWIRE_REQ:

            if (((ucHpRevAmAddr_H == 0x03) && (ucHpRevAmAddr_M == 0xFF) && (ucHpRevAmAddr_L == 0xFF)) || ((GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_H() == ucHpRevAmAddr_H) && (GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_M() == ucHpRevAmAddr_M) && (GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_L() == ucHpRevAmAddr_L)))
            {
                if(((EnumTypeCVdmHpCmd)GET_TYPE_C_1_PD_RCV_VDM_CMD()) == _PD_VDM_HP_CMD_SET_VWIRE_REQ)
                {
                    // For _PD_VDM_HP_CMD_SET_VWIRE_REQ : Set Vwire Operation
                    SET_TYPE_C_1_PD_HP_VWIRE_OP(g_pucTypeC1PdDataObject_EXINT[11] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                }
                ucCheckResult = _TRUE;
            }

            break;

        case _PD_VDM_HP_CMD_GET_VWIRE_REQ:
        case _PD_VDM_HP_CMD_GET_DATA_REQ:

            // Get_viwre can't be Broadcast AM Address
            if ((GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_H() == ucHpRevAmAddr_H) && (GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_M() == ucHpRevAmAddr_M) && (GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_L() == ucHpRevAmAddr_L))
            {
                ucCheckResult = _TRUE;
            }

            break;

        case _PD_VDM_HP_CMD_CMD_REQ:
        default:

            break;
    }

    return ucCheckResult;
}

//--------------------------------------------------
// Description  : Get Hp System Event when Rcv. Hp Get Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdGetHpSysStatus_EXINT0(EnumTypeCHpSysEvent enumSysEvent)
{
    StructTypeCHpSysEvent stHpSysEvent = {_TYPE_C_HP_SYS_EVENT_NONE, {0x00}, 0x00};

    stHpSysEvent.enumEvent = enumSysEvent;

    // User VDM Data = Rcv Data Object - VDM Header - HP Sub Header
    stHpSysEvent.b3VdmCnt = GET_TYPE_C_1_PD_RCV_NOD_CNT() - 2;

    // Get Hp VDM Data Contents
    for(BYTE ucLoopIndex = 0; ucLoopIndex < (stHpSysEvent.b3VdmCnt * 4); ucLoopIndex++)
    {
        stHpSysEvent.pucVdmData[ucLoopIndex] = g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 8];
    }

    // Check if SysEvent Queue is full or not
    if(GET_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_CNT() < _TYPE_C_PD_HP_SYS_EVENT_QUEUE_SIZE)
    {
        SET_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE(GET_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_TAIL(), stHpSysEvent);
        ADD_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_TAIL();
        ADD_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_CNT();
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : Get Dell System Event Information
// Input Value  : enumSysEvent : _TYPE_C_DELL_SYS_EVENT_NONE/ _TYPE_C_DELL_SYS_EVENT_0X12/ _TYPE_C_DELL_SYS_EVENT_ATTEN_SUCCESS/ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdGetDellSysInfo_EXINT0(void)
{
    // User VDM Data = Rcv Data Object - VDM Header
    SET_TYPE_C_1_PD_DELL_SYS_VDM_CNT(GET_TYPE_C_1_PD_RCV_NOD_CNT() - 1);

    // Get Dell VDM Data Contents
    for(BYTE ucLoopIndex = 0; ucLoopIndex < (GET_TYPE_C_1_PD_DELL_SYS_VDM_CNT() * 4); ucLoopIndex++)
    {
        SET_TYPE_C_1_PD_DELL_SYS_VDM_DATA(ucLoopIndex, g_pucTypeC1PdDataObject_EXINT[ucLoopIndex + 4]);
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check if Received Source Capability is Valid
// Input Value  : None
// Output Value : _PD_SRC_CAP_INVALID/_PD_SRC_CAP_VALID
//--------------------------------------------------
EnumTypeCPDSrcCapValid ScalerTypeC1PdCheckSrcCapValid_EXINT0(void)
{
    EnumTypeCPDSrcCapValid enumSrcCapCheckResult = _PD_SRC_CAP_INVALID;

    // 1. Check if Object Position is Valid
    if((GET_TYPE_C_1_PD_REQ_OBJ_POS() > 0) && (GET_TYPE_C_1_PD_REQ_OBJ_POS() <= GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT()) && (GET_TYPE_C_1_PD_PARTNER_EXT_PWR() == _TRUE))
    {
        if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
        {
            // Check if Max Current Provided >= Requested Current
            if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) >= GET_TYPE_C_1_PD_REQ_INFO_2())
            {
                enumSrcCapCheckResult = _PD_SRC_CAP_VALID;
            }
        }
        else if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) == _PD_3_PROGRAMMABLE_PDO)
        {
            // Check if (Max Current Provided >= Requested Current) & (Source Capability Voltage is Valid)
            if(((GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) / 5) >= GET_TYPE_C_1_PD_REQ_INFO_2()) &&
               ((GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) / 2) <= GET_TYPE_C_1_PD_REQ_INFO_1()) &&
               ((GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) / 2) >= GET_TYPE_C_1_PD_REQ_INFO_1()))
            {
                enumSrcCapCheckResult = _PD_SRC_CAP_VALID;
            }
        }
    }

    return enumSrcCapCheckResult;
}

//--------------------------------------------------
// Description  : Push HPD into HPD Queue @ Interrupt
// Input Value  : enumHpdType : _PD_HPD_LOW / _PD_HPD_HIGH..., HPD Space Time(ms)
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdPushHpd_EXINT0(EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime)
{
    BYTE ucIndex = 0;

    // Push Queue Only Vlid When Alt Mode is Ready
    if(GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() != _TRUE)
    {
        return;
    }

    switch(enumHpdType)
    {
        case _PD_HPD_LOW:

            for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
            {
                SET_TYPE_C_1_PD_HPD_QUEUE(_PD_HPD_NONE);
                SET_TYPE_C_1_PD_HPD_SPACE_TIME(0);
                ADD_TYPE_C_1_PD_HPD_WPTR();
            }

            CLR_TYPE_C_1_PD_HPD_WPTR();
            CLR_TYPE_C_1_PD_HPD_RPTR();
            CLR_TYPE_C_1_PD_HPD_CNT();

            SET_TYPE_C_1_PD_HPD_QUEUE(_PD_HPD_LOW);
            SET_TYPE_C_1_PD_HPD_SPACE_TIME(usHpdSpaceTime);

            ADD_TYPE_C_1_PD_HPD_WPTR();
            ADD_TYPE_C_1_PD_HPD_CNT();

            break;

        case _PD_HPD_HIGH:

            if((GET_TYPE_C_1_PD_HPD_CNT() == 0) || (GET_TYPE_C_1_PD_HPD_QUEUE((GET_TYPE_C_1_PD_HPD_WPTR() + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_HIGH))
            {
                SET_TYPE_C_1_PD_HPD_QUEUE(_PD_HPD_HIGH);
                SET_TYPE_C_1_PD_HPD_SPACE_TIME(usHpdSpaceTime);

                ADD_TYPE_C_1_PD_HPD_WPTR();
                ADD_TYPE_C_1_PD_HPD_CNT();
            }

            break;

        case _PD_HPD_IRQ:

            // Make sure HPD_IRQ has a minumun spacing time of 10ms (DP Alt Mode 5.2.2)
            usHpdSpaceTime = (usHpdSpaceTime < _ATTENTION_SPACING_TIMER) ? _ATTENTION_SPACING_TIMER : usHpdSpaceTime;

            if(GET_TYPE_C_1_PD_HPD_CNT() <= 1)
            {
                SET_TYPE_C_1_PD_HPD_QUEUE(_PD_HPD_IRQ);
                SET_TYPE_C_1_PD_HPD_SPACE_TIME(usHpdSpaceTime);

                ADD_TYPE_C_1_PD_HPD_WPTR();
                ADD_TYPE_C_1_PD_HPD_CNT();
            }
            else
            {
                // If Last 2 HPDs are Not Both HPD_IRQs, Push New HPD_IRQ
                if((GET_TYPE_C_1_PD_HPD_QUEUE((GET_TYPE_C_1_PD_HPD_WPTR() + _HPD_QUEUE_DEPTH - 1) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ) ||
                   (GET_TYPE_C_1_PD_HPD_QUEUE((GET_TYPE_C_1_PD_HPD_WPTR() + _HPD_QUEUE_DEPTH - 2) % _HPD_QUEUE_DEPTH) != _PD_HPD_IRQ))
                {
                    SET_TYPE_C_1_PD_HPD_QUEUE(_PD_HPD_IRQ);
                    SET_TYPE_C_1_PD_HPD_SPACE_TIME(usHpdSpaceTime);

                    ADD_TYPE_C_1_PD_HPD_WPTR();
                    ADD_TYPE_C_1_PD_HPD_CNT();
                }
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get TypeC 1 PD Power Role
// Input Value  : None
// Output Value : PD Power Role (_TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC)
//--------------------------------------------------
EnumTypeCPowerRole ScalerTypeC1PdGetPowerRole_EXINT0(void)
{
    if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
    {
        return _TYPE_C_POWER_SRC;
    }
    else
    {
        return _TYPE_C_POWER_SNK;
    }
}

//--------------------------------------------------
// Description  : Get TypeC 1 PD Hard Reset Power Off Flag
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeC1PdGetHardRstPowerOff_EXINT0(void)
{
    return GET_TYPE_C_1_PD_HRST_PWR_OFF();
}

//--------------------------------------------------
// Description  : Clear Interop S8 Flag to Enable FW Solution
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdClrInteropS8Flag_EXINT0(void)
{
    CLR_TYPE_C_1_PD_INTEROP_S8();
}

//--------------------------------------------------
// Description  : Clear HPD Queue @ Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdClrHpd_EXINT0(void)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
    {
        SET_TYPE_C_1_PD_HPD_QUEUE(_PD_HPD_NONE);
        SET_TYPE_C_1_PD_HPD_SPACE_TIME(0);
        ADD_TYPE_C_1_PD_HPD_WPTR();
    }

    SET_TYPE_C_1_PD_HPD_STATUS(_LOW);
    CLR_TYPE_C_1_PD_HPD_WPTR();
    CLR_TYPE_C_1_PD_HPD_RPTR();
    CLR_TYPE_C_1_PD_HPD_CNT();
}

//--------------------------------------------------
// Description  : Set TypeC 1 System Event
// Input Value  : enumPdSysEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetSystemEvent_EXINT0(EnumTypeCPDSysEvent enumPdSysEvent)
{
    if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_ERROR_RECOVERY) == _PD_SYS_EVENT_ERROR_RECOVERY)
    {
        SET_TYPE_C_1_CC_ERROR_RECOVERY();
    }
    else
    {
        SET_TYPE_C_1_PD_SYS_EVENT(enumPdSysEvent);
    }

    // Update Port Controller Event to inform System / User of Specific Events Occurred
    if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
    {
        SET_TYPE_C_1_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_POWER_OCP);
    }

    if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
    {
        SET_TYPE_C_1_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_POWER_OVP);
    }

    if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_UVP) == _PD_SYS_EVENT_POWER_UVP)
    {
        SET_TYPE_C_1_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_POWER_UVP);
    }

    if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_VCONN_OCP) == _PD_SYS_EVENT_VCONN_OCP)
    {
        SET_TYPE_C_1_PD_PORT_CTRL_EVENT(_PD_PORT_CTRL_EVENT_VCONN_OCP);
    }
}

#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))

