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
// ID Code      : ScalerTypeC1Pd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "TypeC1Pd/ScalerTypeC1Pd.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))

#if(_EMB_TYPE_C_1_PD3_1_EPR_SUPPORT == _ON)
#warning "NOTE: Type-C 1 only support EPR Source when _EMB_TYPE_C_1_PD3_1_EPR_SUPPORT == _ON !!! Please make sure EPR Sink PDO count is 0 !!!"
#endif

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))


#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructTypeCPDStatus g_stTypeC1PdStatus;
volatile StructTypeCCableStatus g_stTypeC1PdCableInfo;
volatile StructTypeCCableInfoForDpcd g_stTypeC1PdCableInfoForDpcd;
volatile StructTypeCMsgInfo g_stTypeC1PdMsgInfo;
volatile StructTypeCPdPartnerInfo g_stTypeC1PdPartnerInfo;
volatile StructTypeCEPRModeInfo g_stTypeC1PdEPRMode;
volatile StructTypeCAltModeInfo g_stTypeC1PdAltModeInfo;
volatile StructTypeCDpStatusInfo g_stTypeC1PdDpStatusInfo;
StructTypeCExtMsgInfo g_stTypeC1PdExtMsgInfo;
StructTypeCPDO g_pstTypeC1PdSrcPDO[_MAX_DATA_OBJ_CNT];
StructTypeCPDO g_pstTypeC1PdPartnerSrcCap[_MAX_DATA_OBJ_CNT];
volatile StructTypeCPDO g_pstTypeC1PdSnkCap[_MAX_DATA_OBJ_CNT];
StructTypeCPDO g_pstTypeC1PdPartnerSnkCap[_MAX_DATA_OBJ_CNT];
volatile StructTypeCSnkInfo g_stTypeC1PdSnkInfo;
volatile StructTypeCUserRDO g_stTypeC1PdSnkRDO;
volatile StructTypeCSnkRDO g_stTypeC1PdPartnerRDO;
volatile StructTypeCHpdQueue g_stTypeC1PdHpdQueue;
volatile StructTypeCPdTimerEvent g_stTypeC1PdTimerEvent;
volatile StructTypeCPdEvent g_stTypeC1PdEvent;
BYTE g_pucTypeC1PdDataObject[_MAX_DATA_OBJ_CNT * 4];
volatile StructTypeCPdoStatus g_stTypeC1PdPDOStatus;
volatile StructTypeCStatusEvent g_stTypeC1PdStatusEvent;
volatile StructTypeCAlertEvent g_stTypeC1PdAlertEvent;
volatile StructTypeCStatusEvent g_stTypeC1PdPartnerStatusEvent;
volatile StructTypeCAlertEvent g_stTypeC1PdPartnerAlertEvent;
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
volatile StructTypeCAcerAltModeInfo g_stTypeC1PdAcerAltModeInfo;
volatile StructTypeCAcerSysEvent g_stTypeC1PdAcerSysEvent;
volatile StructTypeCAcerUserEvent g_stTypeC1PdAcerUserEvent;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
volatile StructTypeCHpAltModeInfo g_stTypeC1PdHpAltModeInfo;
volatile StructTypeCHpUserEvent g_stTypeC1PdHpUserEvent;
volatile StructTypeCHpSysEventQueue g_stTypeC1PdHpSysEventQueue;
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
volatile StructTypeCDellAltModeInfo g_stTypeC1PdDellAltModeInfo;
volatile StructTypeCDellSysEvent g_stTypeC1PdDellSysEvent;
volatile StructTypeCDellUserEvent g_stTypeC1PdDellUserEvent;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : [Type C 1] PD Clk Setting (Always Use IOSC = 28MHz)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdClkSel(BYTE ucClockSel)
{
    if(ucClockSel == _IOSC_CLK)
    {
        // [0x6B0B] [7:6] Clk Sel = IOSC 28MHz (b'10) / [3:0] sys_clk_div = b'0001
        ScalerSetBit(P6B_0B_PD_SYS_CLK_CFG, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT0));

        // [0x6B0C] clk_1m_div = 28 (b'0001_1100)
        ScalerSetByte(P6B_0C_PD_1M_CLK_CFG, 0x1C);

        // [0x6B0D-0E] clk_1k_div = 1000 (b'11_11101000)
        ScalerSetBit(P6B_0D_PD_1K_CLK_CFG0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetByte(P6B_0E_PD_1K_CLK_CFG1, 0xE8);

        // ---------- PD Top Setting ----------
        // [0x6B06-07] PHY Idle Config : [7:5]Trans Cnt = 3 / [12:0] Trans Wnd = 12us
        ScalerSetByte(P6B_06_PD_PHY_IDLE_CFG0, 0x62);
        ScalerSetByte(P6B_07_PD_PHY_IDLE_CFG1, 0x30);

        // ---------- PD Tx Setting ----------
        // [0x6BD4-D6] Tx Tbit = 297.87K (Spec = 270 - 330K)
        ScalerSetByte(P6B_D4_BMC_TX_FW_HT, 0x2F);
        ScalerSetBit(P6B_D5_BMC_TX_FW_T1, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte(P6B_D6_BMC_TX_FW_T0, 0x5E);

        // [0x6BD9] Start Drive Count = 100/28 = 3.57us
        ScalerSetByte(P6B_D9_TX_BMC_START_DRIVE_CNT, 0x64);

        // ---------- PD Rx Setting ----------
        // [0x6B22] [4:1]BMC Filter Glitch of > 28 / 3 Mhz / [0] Use HW Auto Tracking Mode
        ScalerSetBit(P6B_22_BMC_RX_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

        // [0x6B23-24] BMC Tbit Lower Bound Setting = 250 K (Spec = 270K)
        ScalerSetBit(P6B_23_BMC_TBIT_LOW_BND1, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte(P6B_24_BMC_TBIT_LOW_BND0, 0x75);

        // [0x6B25-26] BMC Tbit Upper Bound Setting = 350 K (Spec = 330K)
        ScalerSetBit(P6B_25_BMC_TBIT_UP_BND1, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte(P6B_26_BMC_TBIT_UP_BND0, 0x38);

        // [0x6B2C] Hard Reset Detect Fail FW Solution, BMC Tbit Initial Set to 0x60
        ScalerSetByte(P6B_2C_BMC_RX_FW_TBIT0, 0x5E);

        // PD Rx fw_cfg_cnt Setting = 0x0D (270~330K)
        ScalerSetByte(P6B_58_RX_FIFO0_DUMMY_CELL, 0x18);
    }
}

//--------------------------------------------------
// Description  : TypeC 1 PD Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdInitial(void)
{
    // ------------------------ PD TOP Initial Setting ------------------------
    // [0x6B02] Disable BMC Tx/Rx
    ScalerSetBit(P6B_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), 0x00);

    // [0x6B05] PHY Hard Reset Detection Option : PHY Need to be Idle in 5 cycle After Receiving Hard Reset/ CabLe Reset
    ScalerSetBit(P6B_05_PD_PHY_IDLE_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1), (_BIT6 | _BIT4));

    // [0x6B0A] [1]Tx Transit Only When PHY Idle / [0] Incorrect K-Code Can Accept Up to 5-bit Error
    ScalerSetBit(P6B_0A_PD_PHY_TRANSITION_CFG, ~(_BIT1 | _BIT0), _BIT0);

    // ------------------------ PD Rx Initial Setting ------------------------
    // [0x6B27] Rx Tbit Config [7:6] Half Tbit Det Region +-25% / [3:2] Ignore Tbit = 16 for RL6561/6573 Enter Phy Rx loop Modified Condition: 2 Successive High to Low Preamble Bits / [1:0] Tbit Tracking Len = 32
    ScalerSetBit(P6B_27_BMC_RX_TBIT_CFG, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // [0x6B2F] Rx Receive Timeout Config = 2.0ms
    ScalerSetByte(P6B_2F_RX_PHY_RCV_TIMEOUT_CFG, 0xC8);

    // [0x6B38] Message ID Check Option : [5:4] Check Msg ID != Old Value / [0] Msg. ID Update When GoodCRC Sent Success
    ScalerSetBit(P6B_38_RX_PROTOCOL_CFG, ~(_BIT5 | _BIT4 | _BIT0), (_BIT5 | _BIT0));

    // [0x6B39] Rx FIFO Clear Option : Auto Clear GoodCRC, Invalid Pkt, Incorrect CRC, Abn. End, Msg.ID Error Messages
    ScalerSetByte(P6B_39_RX_ERROR_FIFO_CLR_CTRL, 0x7C);

    // [0x6B3A] GoodCRC Response Option : [5]Spec Ver = 0 (Tx Spec Ver) / [4]PR/DR = Tx FIFO / [3:0]Do Not Resp. Incorrect CRC Messages
    // [MQP] PHY tests : BMC-PHY-MSG, Tester Send Abnormal Msg. With Correct CRC + EOP, We Shall Return GoodCRC ( _BIT3 = 1 Only Check CRC Correct )
    ScalerSetByte(P6B_3A_RX_CRC_RESPONSE_CTRL, 0x88);

    // [0x6B40] Rx FIFO Control : [5] Disable Rx FIFO Address Auto Increase
    ScalerSetBit(P6B_40_RX_FIFO_CTRL, ~(_BIT5), 0x00);

    // ------------------------ PD Tx Initial Setting ------------------------
    // [0x6BD3] Tx Tbit Setting : [1] Use FW Tbit Setting / [0] Enable Auto Adjust to Even
    ScalerSetBit(P6B_D3_BMC_TX_TBIT_CFG, ~(_BIT1 | _BIT0), _BIT0);

    // [0x6BD7] Tx Preamble Length = 64
    ScalerSetByte(P6B_D7_BMC_TX_PREAMBLE_LN, 0x40);

    // [0x6BD8] [7:5]HW Pre Turn On Tx / [4:0]Hold Low Count = 10us
    ScalerSetByte(P6B_D8_TX_BMC_HOLD_LOW_CNT, 0x48);

    // [0x6BDA] [2] Disable Arbitration [0]Tx Transit to Discarded When Receive Any Message
    ScalerSetBit(P6B_DA_TX_TRANSMIT_CTRL, ~(_BIT2 | _BIT0), _BIT0);

    // [0x6BEE] Tx CRCReceiver Timer = 1 ms
    ScalerSetByte(P6B_EE_TX_PD_CRC_TIMER_CFG, 0x64);

    // [0x6BE8] Tx FIFO Control : [0] Disable Tx FIFO Address Auto Increase
    ScalerSetBit(P6B_E8_TX_FIFO_CTRL, ~(_BIT4 | _BIT0), 0x00);

    // Enable PD Function
    SET_TYPE_C_1_PD_FUNCTION_EN();

    // Enable Alt. Mode Function (DFP can Start Flow / UFP can Resp. Alt. REQ)
    SET_TYPE_C_1_PD_ALT_MODE_FUNCTION();

    // Clear All Sys Events
    CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_ALL);

    // Clear VDM Response Conflict Cnt
    CLR_TYPE_C_1_PD_VDM_RESP_CONFLICT_CNT();

    // Set UFP Product Type
#if(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_DEFAULT)
#if(_EMB_TYPE_C_1_USB_TYPE != _USB_NONE)
    // With Usb Hub IC, UFP Product Type = PDUSB Hub
    SET_TYPE_C_1_PD_UFP_PRODUCT_TYPE(_TYPE_C_UFP_PRODUCT_TYPE_HUB);
#else
    // Otherwise, UFP Product Type = PDUSB Peripheral
    SET_TYPE_C_1_PD_UFP_PRODUCT_TYPE(_TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL);
#endif // End of #if(_EMB_TYPE_C_1_USB_TYPE != _USB_NONE)
#elif(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED)
    SET_TYPE_C_1_PD_UFP_PRODUCT_TYPE(_TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED);
#elif(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_HUB)
    SET_TYPE_C_1_PD_UFP_PRODUCT_TYPE(_TYPE_C_UFP_PRODUCT_TYPE_HUB);
#elif(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL)
    SET_TYPE_C_1_PD_UFP_PRODUCT_TYPE(_TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL);
#endif // End of #if(_TYPE_C_EMB_UFP_PRODUCT_TYPE == _VALUE_TYPE_C_UFP_PRODUCT_TYPE_DEFAULT)

    // Set DFP Product Type
    SET_TYPE_C_1_PD_DFP_PRODUCT_TYPE(_TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED);

#if(_EMB_TYPE_C_1_PD3_1_EPR_SUPPORT == _ON)
    // If Support EPR Mode, Set EPR Capable
    SET_TYPE_C_1_PD_EPR_SRC_CAPABLE();
#else
    // Otherwise, Clr EPR Capable
    CLR_TYPE_C_1_PD_EPR_SRC_CAPABLE();
#endif
}

//--------------------------------------------------
// Description  : TypeC 1 PD Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdReset(void)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1);
    enumTypeCPcbPort = enumTypeCPcbPort;

    // -------------------- HW Clear, Disable or Reset to Default Value --------------------

    // Enable SNK Detect Rp to Transit from Attached.SNK to Unattached.SNK State
    ScalerTypeC1CcSnkDetRpCtrl(_ENABLE);

    // [0x6B02] Disable PHY Layer BMC Tx/Rx
    ScalerSetBit(P6B_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), 0x00);

    // [0x6B03] Reset CRCReceiver Timer / Retry Counter & Msg. ID Counter / Protocol and PHY Layer FSM
    ScalerSetBit(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P6B_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P6B_32_RX_MSG_ID_RST, ~_BIT3, 0x00);

    // WS111 GRL 2.1.2.1 PHY_BUSIDLE : Reset Rx/Tx Interframe to Default Value
    // [0x6B08] Tx Interframe Setting : [6]Interframe Gap Rst When High to Low [5:0] Interframe Gap = 63us
    ScalerSetByte(P6B_08_PD_PHY_INTERFRAME_CFG0, 0x3F);

    // CTS TD.PD.PHY.E5 Collision Avoidance Test (Must less than 8)
    // [0x6B09] Rx Interframe Setting : [6]Interframe Gap Rst When High to Low [5:0] Interframe Gap = 6us
    ScalerSetByte(P6B_09_PD_PHY_INTERFRAME_CFG1, 0x06);

    // [0x6BF0] Turn Off BIST Mode
    ScalerSetBit(P6B_F0_PD_BIST_CFG, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // [0x6BF5-F6] Clear BIST Mode Error Counter
    ScalerSetByte(P6B_F5_PD_BIST_ERROR_CNT1, 0x01);
    ScalerSetByte(P6B_F6_PD_BIST_ERROR_CNT0, 0x01);

    // [0x6BDB/DC/DD] Clear and Disable Tx IRQs
    ScalerSetBit(P6B_DB_TX_PHY_TRANS_INT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
    ScalerSetBit(P6B_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P6B_DD_TX_PD_MSG_INT_EN, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#else
    ScalerSetBit(P6B_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P6B_DD_TX_PD_MSG_INT_EN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

    // [0x6BE8] Clear Tx FIFO
    ScalerSetByte(P6B_E0_TX_PACKET_CFG, 0x00);
    ScalerSetBit(P6B_E8_TX_FIFO_CTRL, ~(_BIT4 | _BIT2 | _BIT1), (_BIT4));

    // [0x6B2E] Clear and Disable Rx PHY Status IRQ
    ScalerSetBit(P6B_2E_RX_PHY_ERR_INT, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [0x6B43] Clear and Disable Rx Protocol Receive Status IRQ
    ScalerSetByte(P6B_43_RX_RCV_STATUS_INT, 0xAA);

    // Clear Rx FIFO 0/1/2
    ScalerTypeC1PdRxFifoClear(_PD_RX_FIFO_0);
    ScalerTypeC1PdRxFifoClear(_PD_RX_FIFO_1);
    ScalerTypeC1PdRxFifoClear(_PD_RX_FIFO_2);

    // ------------------------- FW State & Counter & Flag Reset -------------------------
    // PD Initial States Setting
    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
    SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_STATE_NONE);
    SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_NONE);
    ScalerTypeC1PdClrHpd();
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    if(GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG)
    {
        ScalerTypeC1PdPushHpd(_PD_HPD_LOW, 0);
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
    ScalerDpPhyRxSetAltModeLaneMapping(ScalerTypeCPcbPortConvertToDx(enumTypeCPcbPort), GET_TYPE_C_1_PD_PIN_ASSIGNMENT(), GET_TYPE_C_1_CC_ORIENTATION());
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    ScalerDpPhyTxSetAltModeLaneMapping(ScalerTypeCPcbPortConvertToPx(enumTypeCPcbPort), GET_TYPE_C_1_PD_PIN_ASSIGNMENT(), GET_TYPE_C_1_CC_ORIENTATION());
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    ScalerTypeC1PdUnattachCancelTimerEvent();

    // Reset Counters
    CLR_TYPE_C_1_PD_SRC_CAP_CNT();
    ScalerSetBit(P6B_01_PHY_STATE_L, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_TYPE_C_1_PD_SRC_CAP_CNT());
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
    ScalerSetBit(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
    // Reset Cable Retry Cnt, if PD Gen >= GEN2
    ScalerSetBit(P6B_ED_TX_PD_CBL_RTY_CNT, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
#endif
#else
    SET_TYPE_C_1_PD_SPEC_VER(_PD_VERSION_2_0);
    SET_TYPE_C_1_PD_CBL_SPEC_VER(_PD_VERSION_2_0);

    // Reset Port Partner & Cable Retry Cnt
    ScalerSetBit(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
    // Reset Cable Retry Cnt, if PD Gen >= GEN2
    ScalerSetBit(P6B_ED_TX_PD_CBL_RTY_CNT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
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
// Description  : Main Flow Of PD Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdHandler(void)
{
    SET_TYPE_C_1_PD_HANDLER_ONGOING();

    // CTS: Reset Protocol & PHY FSM and Clear Error Flags if Any PHY Error (Frc End or Rcv Timeout) Exists
    if(ScalerGetBit(P6B_2E_RX_PHY_ERR_INT, _BIT0) == _BIT0)
    {
        ScalerSetBit(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT0), 0x00);
        ScalerSetBit(P6B_2E_RX_PHY_ERR_INT, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit(P6B_03_PD_TOP_RST, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
    }

    if(GET_TYPE_C_1_PD_TIMER_EVENT_VALID() == _TRUE)
    {
        // [0x6B43] Disable Rx Rcv Msg IRQ
        ScalerTypeC1PdRxIntControl(_DISABLE);

        // Active Timer Event and Clear Timer Event Valid
        ScalerTimerActiveTimerEvent(GET_TYPE_C_1_PD_TIMER_EVENT_CNT(), GET_TYPE_C_1_PD_TIMER_EVENT_ID());
        CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();

        // [0x6B43] Enable Rx Rcv Msg IRQ
        ScalerTypeC1PdRxIntControl(_ENABLE);
    }

    if((GET_TYPE_C_1_PD_EPR_MODE() == _TRUE) && (GET_TYPE_C_1_PD_CANCEL_SRC_EPR_KEEP_ALIVE() == _TRUE))
    {
        // Cancel SourceEPRKeepAliveTimer When Macro Set
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT);
        CLR_TYPE_C_1_PD_CANCEL_SRC_EPR_KEEP_ALIVE();
    }

    // Write Real-Time FW Info to Reserved Register For Debug
    ScalerSetByte(P6B_14_VENDOR_SPECIFIC_SOP1_CFG1, GET_TYPE_C_1_PD_PIN_ASSIGNMENT());
    ScalerSetByte(P6B_15_VENDOR_SPECIFIC_SOP2_CFG0, GET_TYPE_C_1_PD_FW_STATE());
    ScalerSetByte(P6B_16_VENDOR_SPECIFIC_SOP2_CFG1, GET_TYPE_C_1_PD_SUB_STATE());
    ScalerSetByte(P6B_17_VENDOR_SPECIFIC_SOP3_CFG0, GET_TYPE_C_1_PD_DP_ALT_STATE());
    ScalerSetBit(P6B_18_VENDOR_SPECIFIC_SOP3_CFG1, ~(_BIT5 | _BIT4 | _BIT3), (GET_TYPE_C_1_PD_HPD_CNT() << 3));
    ScalerSetBit(P6B_18_VENDOR_SPECIFIC_SOP3_CFG1, ~(_BIT2 | _BIT1 | _BIT0), ((GET_TYPE_C_1_PD_CBL_PD_CAPABILITY() << 1) | (GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG())));

    switch(GET_TYPE_C_1_PD_FW_STATE())
    {
        // ------------------------ Source/Sink Establish Power Contract in Interrupt ---------------
        // ------------------------ Source/Sink Ready to Initaite AMS Flow --------------------------
        case _PD_SRC_READY:
        case _PD_SNK_READY:

            // Process On-Going AMS Flow or Initiate New AMS According to Latest Status
            ScalerTypeC1PdReadyStateProc();

            break;

        // ----------------------------- Source / Sink Hard Reset Flow ------------------------------
        case _PD_HARDRESET:

            if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
            {
                // If Vbus Turned Off, Wait 0.66~1s and Turn On Power to vSafe5v
                if((GET_TYPE_C_1_PD_HRST_PWR_OFF() == _FALSE) && (ScalerTypeCAdcCheckVbusSafe0V(_EMB_TYPE_C_1) == _TRUE))
                {
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
                    // Disable Vbus Discharge
                    ScalerTypeC1PmicVbusDischarge(_OFF);
#endif
                    // Reset PD : WARNING !!! PD Must Reset Before Avtive TURN_ON_POWER Timer , Otherwise, Timer Would Be Canceled
                    ScalerTypeC1PdReset();

                    // Set Hard Reset Turn Off Power Flag (Clr When Send/Rcv Hard Reset & PD Reset), and Turn On Power Later
                    SET_TYPE_C_1_PD_HRST_PWR_OFF();
                    ScalerTimerActiveTimerEvent(_SRC_RECOVER_TIMER, _SCALER_TIMER_EVENT_PD_1_SRC_TURN_ON_POWER);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
                    // [Eizo] SIC437A Customized Power Control : SRC Has Turned Off Vbus During Hard Reset
                    ScalerTypeC1PmicSic437aHardRstVbusOffProc();
#endif

                    // Enable [adc1_comp_vbus_on_en], and Wait ADC VbusSafe5V [adc1_comp_vbus_on] INT Triggered, then call [ScalerTypeC1PdAttachedSetting_EXINT0(_PD_SRC_START_UP)] in ScalerTypeCAdc_EXINT0.c ScalerTypeCAdcIntHandler_EXINT0)
                    ScalerTypeCAdcOnOffCompIntControl(_TYPE_C_CHANNEL_1_VMON, _ON, _ENABLE);
                }
            }
            else
            {
                if((GET_TYPE_C_1_PD_HRST_PWR_OFF() == _FALSE) && (ScalerTypeCAdcGetAdcOutput(_TYPE_C_CHANNEL_1_VMON) < GET_TYPE_C_1_5V_LOW_BND()))
                {
                    ScalerTypeC1PdReset();

                    // Set Hard Reset Turn Off Power Flag (Clr When Send/Rcv Hard Reset & PD Reset)
                    SET_TYPE_C_1_PD_HRST_PWR_OFF();

                    // Set Vbus_On_Thr to vSafe5V(4.6V) to Detect Vbus On
                    ScalerTypeCAdcOnOffCompIntSetting(_TYPE_C_CHANNEL_1_VMON, _ON, GET_TYPE_C_1_5V_LOW_BND());

                    // Enable [adc1_comp_vbus_on_en], and Wait ADC VbusSafe5V [adc1_comp_vbus_on] INT Triggered, then call [ScalerTypeC1PdAttachedSetting_EXINT0(_PD_SNK_START_UP)] in ScalerTypeCAdc_EXINT0.c ScalerTypeCAdcIntHandler_EXINT0)
                    ScalerTypeCAdcOnOffCompIntControl(_TYPE_C_CHANNEL_1_VMON, _ON, _ENABLE);
                }
            }

            break;

        // --------------------------- Source / Sink Main Loop Idle State ---------------------------
        case _PD_SRC_WDINT_SEND_CAP:
        case _PD_SRC_INT_SEND_CAP:
        case _PD_SRC_INT_WAIT_REQ:
        case _PD_SRC_INT_SEND_ACCEPT_REQ:
        case _PD_SRC_INT_SEND_REJECT_REQ:
        case _PD_SRC_INT_SEND_WAIT_REQ:
        case _PD_SRC_WDINT_TRANSIT_POWER:
        case _PD_SRC_WDINT_SEND_PSRDY:
        case _PD_SRC_INT_SEND_PSRDY:
        case _PD_SNK_START_UP:
        case _PD_SNK_INT_WAIT_SRC_CAP:
        case _PD_SNK_INT_SEND_REQUEST:
        case _PD_SNK_INT_WAIT_REQ_RESP:
        case _PD_SNK_INT_WAIT_PS_RDY:
        case _PD_SRC_INT_WAIT_EPR_REQ:
        case _PD_INT_SEND_SOFTRESET:
        case _PD_INT_WAIT_SOFTRESET_RESP:
        case _PD_INT_SEND_SOFTRESET_RESP:
        case _PD_NO_RESPONSE:
        default:

            if((GET_TYPE_C_1_PD_SYS_EVENT() & (_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP)) != _PD_SYS_EVENT_NONE)
            {
                ScalerTypeC1PdOcpOvpProc();
            }

            break;
    }

    CLR_TYPE_C_1_PD_HANDLER_ONGOING();
}

//--------------------------------------------------
// Description  : Process For SRC/SNK_READY State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdReadyStateProc(void)
{   // Wait For Source to do PS_RDY or Alt. Mode Flow, Otherwise, Initiate Certain Flow
    // 1. If (DFP) : DR_Swap => Vconn Swap => Alt. Mode => Get_Snk_Cap => PR_SWAP
    // 2. If (UFP) : Get_Snk_Cap => PR_Swap

    switch(GET_TYPE_C_1_PD_SUB_STATE())
    {
        case _PD_SUB_SRC_READY:

            // Disable Rcv Message Int
            ScalerTypeC1PdRxIntControl(_DISABLE);

            if(GET_TYPE_C_1_PD_AMS_STATUS() == _PD_AMS_NONE)
            {   // Src Init Message Only When No AMS is On-Going
                ScalerTypeC1PdSrcReadyProc();
            }

            // Enable Rcv Message Int
            ScalerTypeC1PdRxIntControl(_ENABLE);

            break;

        case _PD_SUB_SNK_READY:

            // Disable Rcv Message Int
            ScalerTypeC1PdRxIntControl(_DISABLE);

            if(GET_TYPE_C_1_PD_AMS_STATUS() == _PD_AMS_NONE)
            {   // Src Init Message Only When No AMS is On-Going
                ScalerTypeC1PdSnkReadyProc();
            }

            // To Fix [TD.PD.PHY.E18]
            // If in BIST Mode, Rcv Message Int will not be Enabled
            if(GET_TYPE_C_1_PD_SUB_STATE() != _PD_SUB_BIST_MODE)
            {
                // Enable Rcv Message Int
                ScalerTypeC1PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SUB_SEND_GET_SRC_CAP:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Send "Get Src Cap" and Set Flag, DO Not Enable RxInt Here, Enable in TxDone
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_GET_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_SEND_GET_SNK_CAP:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Send "Get Snk Cap" and Set Flag, DO Not Enable RxInt Here, Enable in TxDone
                SET_TYPE_C_1_PD_GET_SNK_CAP_SENT();
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_GET_SNK_CAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_SEND_SRC_CAP:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Send "Src Cap" and Set Flag, DO Not Enable RxInt Here, Enable in TxDone
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_CABLE_PROC:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                switch(GET_TYPE_C_1_PD_CBL_STATE())
                {
                    case _PD_CBL_SEND_SOFT_RST:

#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                        // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                        ScalerTypeC1PdUpdateCableRetryCounter();
#endif

                        // Send Soft Reset(SOP') to Reset Cable
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                        ScalerTypeC1PdSendSoftRst(_PD_SOP_P_PKT);

                        break;

                    case _PD_CBL_SEND_DISCOVER_ID:

#if(_DISCOVER_ID_NO_RETRY == _TRUE)
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                        // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp(For RL6829)
                        ScalerSetBit(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
#else
                        // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp(For RL6952)
                        ScalerSetBit(P6B_ED_TX_PD_CBL_RTY_CNT, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif
#else
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                        // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                        ScalerTypeC1PdUpdateCableRetryCounter();
#endif
#endif

                        // Send Discover ID (SOP') to Get Cable Info
                        SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                        ScalerTypeC1PdSendMsg(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);

                        break;

                    default:

                        break;
                }
            }

            break;

        case _PD_SUB_SEND_PR_SWAP:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Send "PR SWAP" and Set Flag, DO Not Enable RxInt Here, Enable in TxDone
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_PR_SWAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_SEND_SRC_OFF_PSRDY:

            // Disable Rcv Message Int
            ScalerTypeC1PdRxIntControl(_DISABLE);

#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
            // Cancel TimerEvent for PPS PDO
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_PPS_TIMEOUT);
#endif

            // When Vubs is Turned Off
            // 1. Swith Rp -> Rd  2. Disable Vbus Discharge  3. Send PS_RDY Message  4. Active Timer to Wait Vbus On
            if(ScalerTypeCAdcCheckVbusSafe0V(_EMB_TYPE_C_1) == _TRUE)
            {
                // 1. Disable Vbus Det and Change Rd -> Rp (Set CC State to Sink)
                ScalerTypeC1CcVbusDetCtrl(_DISABLE);
                ScalerTypeC1CcSwitchPowerRole(_PD_POWER_SNK);

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
                // 2. Disable Vbus Discharge
                ScalerTypeC1PmicVbusDischarge(_OFF);
#endif

                // 3. Change PD Power Role to Sink & Send PS_RDY
                SET_TYPE_C_1_PD_POWER_ROLE(_PD_POWER_SNK);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_HARD_RESET);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_PS_RDY, _PD_VDM_CMD_RESERVED);

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
                {
                    CLR_TYPE_C_1_PD_PARTNER_VDM_NO_RESP_CNT();
                    CLR_TYPE_C_1_PD_CBL_VDM_NO_RESP_CNT();
                }
                else
                {
                    CLR_TYPE_C_1_PD_VCS_REJECT();
                    CLR_TYPE_C_1_PD_DRS_REJECT();
                    CLR_TYPE_C_1_PD_PRS_REJECT();
                }
#endif

                CLR_TYPE_C_1_PD_EPR_MODE();
            }
            else
            {
                // Only Enable Rcv Message Int When No Message Sent (SendMsg Should Enable in Tx Done)
                ScalerTypeC1PdRxIntControl(_ENABLE);
            }

            break;

        case _PD_SUB_SEND_DR_SWAP:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Send "DR SWAP" and Set Flag, DO Not Enable RxInt Here, Enable in TxDone
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_DR_SWAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_SEND_VCONN_SWAP:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Send "DR SWAP" and Set Flag, DO Not Enable RxInt Here, Enable in TxDone
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VCONN_SWAP, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_BIST_MODE:

            // Remove CTS TD.PD.PHY.E16 Valid Hard Reset Framing FW Solution

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        // [MQP] : PROT-SNK3-STATUS(Rev3.0), Shall Initiate GET_STATUS Msg. When SnkTXOK
        case _PD_SUB_SEND_GET_STATUS:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Send "Get_status" and Set Flag, DO Not Enable RxInt Here, Enable in TxDone
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_GET_STATUS, _PD_VDM_CMD_RESERVED);
            }

            break;

        case _PD_SUB_SEND_ALERT:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
                if((GET_TYPE_C_1_PD_SYS_EVENT() & (_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP)) != _PD_SYS_EVENT_NONE)
                {
                    // Active Timer Event For Receiving Subsequent AMS, ex: Get_Status Msg., Timeout : Hard Reset
                    ScalerTimerActiveTimerEvent(_ALERT_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_1_SEND_HARD_RST);
                }
#endif

                // Send "Alert" and Set Flag, DO Not Enable RxInt Here, Enable in TxDone
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_ALERT, _PD_VDM_CMD_RESERVED);
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        case _PD_SUB_SEND_EPR_SRC_CAP:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Send EPR Source Cap
                CLR_TYPE_C_1_PD_TX_CHUNK_NUMBER();
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_EPR_SRC_CAP, _PD_VDM_CMD_RESERVED);
            }

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)

        case _PD_SUB_INT_SEND_NOT_SUPPORT:
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_SUB_INT_SEND_SRC_CAP:
        case _PD_SUB_INT_SEND_SNK_CAP:
        case _PD_SUB_INT_SEND_REJECT:
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For SRC_READY State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSrcReadyProc(void)
{
    if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_HARD_RESET) == _PD_SYS_EVENT_SEND_HARD_RESET)
    {
        ScalerTypeC1PdSendHardRst();
        CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_SEND_HARD_RESET);
    }
    else if((GET_TYPE_C_1_PD_SYS_EVENT() & (_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP)) != _PD_SYS_EVENT_NONE)
    {
        ScalerTypeC1PdOcpOvpProc();
    }
    else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_ALERT_EVENT) == _PD_SYS_EVENT_ALERT_EVENT)
    {
        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_ALERT);
    }
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
    else if((ScalerTypeC1PdAltModeUrgentEvent() == _PD_ALT_MODE_URGENT) && (GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE))
    {
        ScalerTypeC1PdAltModeProc();
    }
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
    else
    {
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
        ScalerTypeC1PdSrcReadyDpRxProc();
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
        ScalerTypeC1PdSrcReadyDpTxProc();
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    }
}

//--------------------------------------------------
// Description  : Process For SNK_READY State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSnkReadyProc(void)
{
    if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_HARD_RESET) == _PD_SYS_EVENT_SEND_HARD_RESET)
    {
        ScalerTypeC1PdSendHardRst();
        CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_SEND_HARD_RESET);
    }
    else if((GET_TYPE_C_1_PD_SYS_EVENT() & (_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP)) != _PD_SYS_EVENT_NONE)
    {
        ScalerTypeC1PdOcpOvpProc();
    }
    else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_ALERT_EVENT) == _PD_SYS_EVENT_ALERT_EVENT)
    {
        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_ALERT);
    }
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
    else if((ScalerTypeC1PdAltModeUrgentEvent() == _PD_ALT_MODE_URGENT) && (GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE))
    {
        ScalerTypeC1PdAltModeProc();
    }
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
    else
    {
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
        ScalerTypeC1PdSnkReadyDpRxProc();
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
        ScalerTypeC1PdSnkReadyDpTxProc();
#endif  // End of #if(_EMB_TYPE_C_1_DP_PORT_CAP == _TYPE_C_DP_RX)
    }
}

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
//--------------------------------------------------
// Description  : Process For SRC_READY DP_RX State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSrcReadyDpRxProc(void)
{
    // 1. DFP : Try to Discover Cable First ,then Get Sink Capability, Do DR_SWAP, If Un-Avaliable, Initiate Alt. Mode
    // 2. UFP : Ultimate Goal, Wait For Partner to Initaite Alt. Mode
    if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
    {
        if((GET_TYPE_C_1_PD_VCS_REJECT() == _FALSE) && (GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_NOT_SRC) && (GET_TYPE_C_1_PD_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED))
        {
            if(GET_TYPE_C_1_PD_VCS_WAIT_FLAG() == _FALSE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
            }
        }
        else if((GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC) && (GET_TYPE_C_1_PD_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED))
        {
            if(GET_TYPE_C_1_PD_CBL_SOFT_RESET_REQUIRED() == _TRUE)
            {
                CLR_TYPE_C_1_PD_CBL_SOFT_RESET_REQUIRED();

                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_CABLE_PROC);
                SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_SEND_SOFT_RST);
            }
            else
            {
                if(GET_TYPE_C_1_PD_VDM_BUSY_FLAG() == _FALSE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_CABLE_PROC);
                    SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_SEND_DISCOVER_ID);
                }
            }
        }
#if(_TYPE_C_1_PD_DFP_SWAP_TO_UFP == _TRUE)
        else if(GET_TYPE_C_1_PD_GET_SNK_CAP_SENT() == _FALSE)
        {
            if(GET_TYPE_C_1_PD_GET_SNK_CAP_WAIT_FLAG() == _FALSE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_SNK_CAP);
            }
            else
            {
                // [Allion 20210318] Ellisys TD.PD.VNDI3.E3. TD.PD.VNDI3.E5 .TD.PD.VNDI3.E7 : Solution: Wait > 10ms to Avoid Check Point. Timeout : Clear GET_SNK_CAP_WAIT_FLAG
                // [MM1AE-2994] Wait > 50ms for Samsung S21 Interop Issue.
                ScalerTimerActiveTimerEvent(_TYPE_C_SRC_GET_SNK_CAP_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_GET_SNK_CAP_WAIT);
            }
        }
#if(_REFER_TO_PORT_PARTNER_CAP == _TRUE)
        else if((GET_TYPE_C_1_PD_PARTNER_DRD() == _TRUE) && (GET_TYPE_C_1_PD_DRS_REJECT() == _FALSE) && (GET_TYPE_C_1_PD_DP_ALT_STATE() == _PD_ALT_MODE_NONE))
#else
        else if((GET_TYPE_C_1_PD_DRS_REJECT() == _FALSE) && (GET_TYPE_C_1_PD_DP_ALT_STATE() == _PD_ALT_MODE_NONE))
#endif
        {
#if(_TYPE_C_DPAM_VERSION <= _DPAM_VERSION_1_0)
            if((GET_TYPE_C_1_PD_VCS_REJECT() == _FALSE) && (GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC))
            {
                if(GET_TYPE_C_1_PD_VCS_WAIT_FLAG() == _FALSE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
                }
            }
            else
            {
                if(GET_TYPE_C_1_PD_DRS_WAIT_FLAG() == _FALSE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DR_SWAP);
                }
            }
#else
            if(GET_TYPE_C_1_PD_DRS_WAIT_FLAG() == _FALSE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DR_SWAP);
            }
#endif  // End of #if(_TYPE_C_DPAM_VERSION <= _DPAM_VERSION_1_0)
        }
#endif  // End of #if(_TYPE_C_1_PD_DFP_SWAP_TO_UFP == _TRUE)
        else
        {
            // Check if System Request to Send Src Cap
            if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
            {
                if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_EPR_SRC_CAP);
                }
                else
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_SRC_CAP);
                }
            }
            // Check if System Request to Send Get_Status Cap
            else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
            }
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            else if((GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE) && (GET_TYPE_C_1_PD_DP_ALT_STATE() != _PD_ALT_MODE_ERROR) && (GET_TYPE_C_1_PD_PARTNER_VDM_NO_RESP_CNT() < _MAX_VDM_NO_RESP_CNT))
            {
                if((GET_TYPE_C_1_PD_VCS_REJECT() == _FALSE) && (GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_NOT_SRC))
                {
                    if(GET_TYPE_C_1_PD_VCS_WAIT_FLAG() == _FALSE)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
                    }
                }
                else
                {
                    ScalerTypeC1PdAltModeProc();
                }
            }
#endif
        }
    }
    else
    {
        if((GET_TYPE_C_1_PD_PARTNER_ALT_SUPPORT() == _FALSE) || (GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) || (GET_TYPE_C_1_PD_PARTNER_INIT_ALT_MODE() == _FALSE))
        {
            if((GET_TYPE_C_1_PD_VCS_REJECT() == _FALSE) &&
               (((GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_NOT_SRC) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED)) ||
                ((GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC) && ((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) || ((GET_TYPE_C_1_PD_CBL_PD_CAPABILITY() != _TYPE_C_CABLE_PD_CAP_UNCONFIRMED) && (GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() != _PD_DP_CONFIG))))))
            {
                // There are two Conditions to Do Vconn_Swap:
                // 1. If (Vconn Not Source) && (PD 3.0) && (Cable Cap == Unconfirmed), Do Vconn_Swap for Cable Discovery.
                // Note: Lecroy [COMMON.PROC.PD.7 UUT Sent Discover Identity Request], As a UFP, It can't Send SOP' Msg to Cable in PD 2.0.
                // 2. If (Vconn Source) && {(PD 2.0) || [(Cable Cap != Unconfirmed) && (Not DP Config)]}, Do Vconn_Swap for Microsoft Surface Laptop 3 Interop Issue.
                // Note 1: If the FW don't Send Vconn_Swap here, Surface Laptop 3 will not Take any Action afterwards. (MM1AE-1999)
                // Note 2: If the FW Sends Vconn_Swap After DP Config, VAIO VJFH42H14T will Fail to Light Up. (MM1AE-2757)
                if(GET_TYPE_C_1_PD_VCS_WAIT_FLAG() == _FALSE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
                }
            }
            else if((GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_CBL_PD_CAPABILITY() == _TYPE_C_CABLE_PD_CAP_UNCONFIRMED))
            {
                if(GET_TYPE_C_1_PD_CBL_SOFT_RESET_REQUIRED() == _TRUE)
                {
                    CLR_TYPE_C_1_PD_CBL_SOFT_RESET_REQUIRED();

                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_CABLE_PROC);
                    SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_SEND_SOFT_RST);
                }
                else
                {
                    if(GET_TYPE_C_1_PD_VDM_BUSY_FLAG() == _FALSE)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_CABLE_PROC);
                        SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_SEND_DISCOVER_ID);
                    }
                }
            }
#if(_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE)
            else if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _FALSE) && (GET_TYPE_C_1_PD_PRS_REJECT() == _FALSE))
            {
                if(GET_TYPE_C_1_PD_GET_SRC_CAP_SENT() == _FALSE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_SRC_CAP);
                }
                else if((GET_TYPE_C_1_PD_PARTNER_DRP() == _TRUE) && (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CHECK_RESULT() == _PD_SRC_CAP_VALID))
                {
                    // When Rcv. PR_Swap Wait Msg. Response, Immediately Active Timer(100ms) to Clear PRS_WAIT_FLAG
                    if(GET_TYPE_C_1_PD_PRS_WAIT_FLAG() == _FALSE)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_PR_SWAP);
                    }
                }
            }
#endif
            // Check if System Request to Send Src Cap
            else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
            {
                if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_EPR_SRC_CAP);
                }
                else
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_SRC_CAP);
                }
            }
            // Check if System Request to Send Get_Status Cap
            else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
            }
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            else if(GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE)
            {
                ScalerTypeC1PdAltModeProc();
            }
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
        }
    }
}

//--------------------------------------------------
// Description  : Process For SNK_READY DP_RX State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSnkReadyDpRxProc(void)
{
    // Wait For Source to do PS_RDY or Alt. Mode Flow, Otherwise, Initiate Certain Flow
    if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_UFP)
    {
#if(_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
        if(GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP)
        {
            if((GET_TYPE_C_1_PD_PARTNER_ALT_SUPPORT() == _FALSE) || (GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) || (GET_TYPE_C_1_PD_PARTNER_INIT_ALT_MODE() == _FALSE) || (GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _FALSE))
            {
                if(GET_TYPE_C_1_PD_GET_SNK_CAP_SENT() == _FALSE)
                {
                    if(GET_TYPE_C_1_PD_GET_SNK_CAP_WAIT_FLAG() == _FALSE)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_SNK_CAP);
                    }
                    else
                    {
                        // [Workshop #114] MQP BMC-PHY-MSG (Rev 2.0):Confirm that repeated incoming MessageID is ignored. Solution: Wait > 40ms to avoid check point.
                        ScalerTimerActiveTimerEvent(_TYPE_C_SNK_GET_SNK_CAP_WAIT_TIMER, _SCALER_TIMER_EVENT_PD_1_CLR_GET_SNK_CAP_WAIT);
                    }
                }
#if(_REFER_TO_PORT_PARTNER_CAP == _TRUE)
                else if((GET_TYPE_C_1_PD_PARTNER_DRP() == _TRUE) && (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _TRUE) && (GET_TYPE_C_1_PD_PRS_REJECT() == _FALSE))
#else
                else if((GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _TRUE) && (GET_TYPE_C_1_PD_PRS_REJECT() == _FALSE))
#endif
                {
                    if((GET_TYPE_C_1_PD_VCS_REJECT() == _FALSE) && (GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_NOT_SRC))
                    {
                        if(GET_TYPE_C_1_PD_VCS_WAIT_FLAG() == _FALSE)
                        {
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
                        }
                    }
                    else
                    {
                        if(GET_TYPE_C_1_PD_PRS_WAIT_FLAG() == _FALSE)
                        {
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_PR_SWAP);
                        }
                    }
                }
                else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_REQUEST) == _PD_SYS_EVENT_SEND_REQUEST)
                {
                    // Send "Get Source Capabilitie to Ask Source to Send Src Cap, and Send New Request to Source"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_SRC_CAP);
                }
                // Check if System Request to Send Get_Status Cap
                else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
                }
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
                // Try to Do Alt. Mode Flow (Get HPD Queue)
                else if(GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE)
                {
                    ScalerTypeC1PdAltModeProc();
                }
#endif
            }
        }
        else
#endif  // End of #if(_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
        {
            // Snk-Only or DRP Do Not Support PR_SWAP, Check Whether Request Event Exist
            if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_REQUEST) == _PD_SYS_EVENT_SEND_REQUEST)
            {
                // Send "Get Source Capabilitie to Ask Source to Send Src Cap, and Send New Request to Source"
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_SRC_CAP);
            }
            // Check if System Request to Send Get_Status Cap
            else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
            }
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            // Try to Do Alt. Mode Flow (Get HPD Queue)
            else if(GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE)
            {
                ScalerTypeC1PdAltModeProc();
            }
#endif
        }
    }
}

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
//--------------------------------------------------
// Description  : Process For SRC_READY DP_TX State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSrcReadyDpTxProc(void)
{
    if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
    {
        // Check if System Request to Send Src Cap
        if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
        {
            if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_EPR_SRC_CAP);
            }
            else
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_SRC_CAP);
            }
        }
        // Check if System Request to Send Get_Status Cap
        else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
        {
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
        }
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
        else if((GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE) && (GET_TYPE_C_1_PD_DP_ALT_STATE() != _PD_ALT_MODE_ERROR) && (GET_TYPE_C_1_PD_DP_ALT_STATE() != _PD_ALT_MODE_READY) && (GET_TYPE_C_1_PD_DP_ALT_STATE() != _PD_ALT_MODE_INT_WAIT_ATTENTION) && (GET_TYPE_C_1_PD_PARTNER_VDM_NO_RESP_CNT() < _MAX_VDM_NO_RESP_CNT))
        {
            if((GET_TYPE_C_1_PD_VCS_REJECT() == _FALSE) && (GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_NOT_SRC))
            {
                if(GET_TYPE_C_1_PD_VCS_WAIT_FLAG() == _FALSE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
                }
            }
            else
            {
                ScalerTypeC1PdAltModeProc();
            }
        }
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)

#if(_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE)
        else if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _FALSE))
        {
            if(GET_TYPE_C_1_PD_GET_SRC_CAP_SENT() == _FALSE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_SRC_CAP);
            }
            else if((GET_TYPE_C_1_PD_PARTNER_DRP() == _TRUE) && (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CHECK_RESULT() == _PD_SRC_CAP_VALID))
            {
                // When Rcv. PR_Swap Wait Msg. Response, Immediately Active Timer(100ms) to Clear PRS_WAIT_FLAG
                if(GET_TYPE_C_1_PD_PRS_WAIT_FLAG() == _FALSE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_PR_SWAP);
                }
            }
        }
#endif  // End of #if(_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE)
    }
    else
    {
#if(_TYPE_C_1_PD_UFP_SWAP_TO_DFP == _TRUE)
        if((GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE) && (GET_TYPE_C_1_PD_PARTNER_DRD() == _TRUE) && (GET_TYPE_C_1_PD_DRS_REJECT() == _FALSE))
        {
            if((GET_TYPE_C_1_PD_PARTNER_INIT_ALT_MODE() == _FALSE) || (GET_TYPE_C_1_PD_PARTNER_ALT_SUPPORT() == _FALSE))
            {
                if(GET_TYPE_C_1_PD_DRS_WAIT_FLAG() == _FALSE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DR_SWAP);
                }
            }
        }
        else
#endif  // End of #if(_TYPE_C_1_PD_UFP_SWAP_TO_DFP == _TRUE)
        {
#if(_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE)
            if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _FALSE))
            {
                if((GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) || (GET_TYPE_C_1_PD_PARTNER_ALT_SUPPORT() == _FALSE) || (GET_TYPE_C_1_PD_PARTNER_INIT_ALT_MODE() == _FALSE))
                {
                    if(GET_TYPE_C_1_PD_GET_SRC_CAP_SENT() == _FALSE)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_SRC_CAP);
                    }
                    else if((GET_TYPE_C_1_PD_PARTNER_DRP() == _TRUE) && (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CHECK_RESULT() == _PD_SRC_CAP_VALID))
                    {
                        // When Rcv. PR_Swap Wait Msg. Response, Immediately Active Timer(100ms) to Clear PRS_WAIT_FLAG
                        if(GET_TYPE_C_1_PD_PRS_WAIT_FLAG() == _FALSE)
                        {
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_PR_SWAP);
                        }
                    }
                    else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
                    {
                        if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
                        {
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_EPR_SRC_CAP);
                        }
                        else
                        {
                            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_SRC_CAP);
                        }
                    }
                    // Check if System Request to Send Get_Status Cap
                    else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
                    }
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
                    else if(GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE)
                    {
                        ScalerTypeC1PdAltModeProc();
                    }
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
                }
            }
            else
#endif  // End of #if(_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE)
            {
                // Check if System Request to Send Src Cap
                if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_SRC_CAP) == _PD_SYS_EVENT_SEND_SRC_CAP)
                {
                    if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_EPR_SRC_CAP);
                    }
                    else
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_SRC_CAP);
                    }
                }
                // Check if System Request to Send Get_Status Cap
                else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
                }
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
                else if(GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE)
                {
                    ScalerTypeC1PdAltModeProc();
                }
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
            }
        }
    }
}

//--------------------------------------------------
// Description  : Process For SNK_READY DP_TX State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSnkReadyDpTxProc(void)
{
    if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
    {
        // Check Whether Request Event Exist
        if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_REQUEST) == _PD_SYS_EVENT_SEND_REQUEST)
        {
            // Send "Get Source Capabilitie to Ask Source to Send Src Cap, and Send New Request to Source"
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_SRC_CAP);
        }
        // Check if System Request to Send Get_Status Cap
        else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
        {
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
        }
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
        else if((GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE) && (GET_TYPE_C_1_PD_DP_ALT_STATE() != _PD_ALT_MODE_ERROR) && (GET_TYPE_C_1_PD_DP_ALT_STATE() != _PD_ALT_MODE_READY) && (GET_TYPE_C_1_PD_DP_ALT_STATE() != _PD_ALT_MODE_INT_WAIT_ATTENTION) && (GET_TYPE_C_1_PD_PARTNER_VDM_NO_RESP_CNT() < _MAX_VDM_NO_RESP_CNT))
        {
            if((GET_TYPE_C_1_PD_VCS_REJECT() == _FALSE) && (GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_NOT_SRC))
            {
                if(GET_TYPE_C_1_PD_VCS_WAIT_FLAG() == _FALSE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_VCONN_SWAP);
                }
            }
            else
            {
                ScalerTypeC1PdAltModeProc();
            }
        }
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)

#if(_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
        else if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_PD_PARTNER_DRP() == _TRUE) && (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _TRUE))
        {
            // When Rcv. PR_Swap Wait Msg. Response, Immediately Active Timer(100ms) to Clear PRS_WAIT_FLAG
            if(GET_TYPE_C_1_PD_PRS_WAIT_FLAG() == _FALSE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_PR_SWAP);
            }
        }
#endif  // End of #if(_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
    }
    else
    {
#if(_TYPE_C_1_PD_UFP_SWAP_TO_DFP == _TRUE)
        if((GET_TYPE_C_1_PD_DP_ALT_MODE_ENTER() == _FALSE) && (GET_TYPE_C_1_PD_PARTNER_DRD() == _TRUE) && (GET_TYPE_C_1_PD_DRS_REJECT() == _FALSE))
        {
            if((GET_TYPE_C_1_PD_PARTNER_INIT_ALT_MODE() == _FALSE) || (GET_TYPE_C_1_PD_PARTNER_ALT_SUPPORT() == _FALSE))
            {
                if(GET_TYPE_C_1_PD_DRS_WAIT_FLAG() == _FALSE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DR_SWAP);
                }
            }
        }
        else
#endif  // End of #if(_TYPE_C_1_PD_UFP_SWAP_TO_DFP == _TRUE)
        {
#if(_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
            if((GET_TYPE_C_1_CC_PORT_ROLE() == _TYPE_C_PORT_DRP) && (GET_TYPE_C_1_PD_PARTNER_DRP() == _TRUE) && (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _TRUE))
            {
                if((GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) || (GET_TYPE_C_1_PD_PARTNER_ALT_SUPPORT() == _FALSE))
                {
                    // When Rcv. PR_Swap Wait Msg. Response, Immediately Active Timer(100ms) to Clear PRS_WAIT_FLAG
                    if(GET_TYPE_C_1_PD_PRS_WAIT_FLAG() == _FALSE)
                    {
                        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_PR_SWAP);
                    }
                }
            }
            else
#endif  // End of #if(_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
            {
                // Check Whether Request Event Exist
                if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_REQUEST) == _PD_SYS_EVENT_SEND_REQUEST)
                {
                    // Send "Get Source Capabilitie to Ask Source to Send Src Cap, and Send New Request to Source"
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_SRC_CAP);
                }
                // Check if System Request to Send Get_Status Cap
                else if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_SEND_GET_STATUS_MSG) == _PD_SYS_EVENT_SEND_GET_STATUS_MSG)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_GET_STATUS);
                }
#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
                // Try to Do Alt. Mode Flow (Get HPD Queue)
                else if(GET_TYPE_C_1_PD_ALT_MODE_FUNCTION() == _TRUE)
                {
                    ScalerTypeC1PdAltModeProc();
                }
#endif
            }
        }
    }
}
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process For Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdAltModeProc(void)
{
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
    // Send Message Only When Data Role = DFP, and Alt Mode Not in Error State
    if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
    {
        if(GET_TYPE_C_1_PD_VDMMSG_WAIT_FLAG() == _TRUE)
        {
            ScalerTimerActiveTimerEvent(50, _SCALER_TIMER_EVENT_PD_1_CLR_VDMMSG_WAIT);
        }
        else if(GET_TYPE_C_1_PD_VDM_BUSY_FLAG() == _FALSE)
        {
            ScalerTypeC1PdDpAltModeDfpProc();
        }
    }
    else
#endif
    {
        if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_UFP)
        {
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
            if(GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG)
            {
                ScalerTypeC1PdDpAltModeUfpProc();

                if(GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SEND_DP_VDM_REQ)
                {
                    return;
                }
            }
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
            if(GET_TYPE_C_1_PD_LENOVO_ALT_MODE_ENTER() == _TRUE)
            {
                ScalerTypeC1PdLenovoAltModeUfpProc();
            }
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
            if(GET_TYPE_C_1_PD_ACER_ALT_MODE_ENTER() == _TRUE)
            {
                ScalerTypeC1PdAcerAltModeUfpProc();
            }
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
            if(GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _TRUE)
            {
                ScalerTypeC1PdHpAltModeUfpProc();
            }
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
            if(GET_TYPE_C_1_PD_DELL_ALT_MODE_ENTER() == _TRUE)
            {
                ScalerTypeC1PdDellAltModeUfpProc();
            }
#endif
        }
    }
}

#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Process For DFP Dp Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdDpAltModeDfpProc(void)
{
    switch(GET_TYPE_C_1_PD_DP_ALT_STATE())
    {
        case _PD_ALT_MODE_NONE:

            // DFP Waits 50ms then Starts Alt Mode
            ScalerTimerActiveTimerEvent(50, _SCALER_TIMER_EVENT_PD_1_DFP_START_ALT_MODE);

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_ID:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Discover ID REQ"
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_SVID:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Discover SVID REQ"
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_MODE:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "DP Discover Mode REQ"
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_REQ);
            }

            break;

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
        case _PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
#if(_DISCOVER_ID_NO_RETRY == _TRUE)
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp(For RL6829)
                ScalerSetBit(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
#else
                // Do Not Retry Discover ID When Not Rcv. GoodCRC Resp(For RL6952)
                ScalerSetBit(P6B_ED_TX_PD_CBL_RTY_CNT, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif
#else
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                ScalerTypeC1PdUpdateCableRetryCounter();
#endif
#endif

                // Send Discover ID (SOP') to Get Cable Info
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_CBL_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeC1PdSendMsg(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_ID_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                ScalerTypeC1PdUpdateCableRetryCounter();
#endif
                // Send Discover SVID (SOP') to Get Cable SVID
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_CBL_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeC1PdSendMsg(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_SVID_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                ScalerTypeC1PdUpdateCableRetryCounter();
#endif

                // Send DP Discover Mode (SOP') to Get Cable DP Capabilities
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_CBL_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeC1PdSendMsg(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                ScalerTypeC1PdUpdateCableRetryCounter();
#endif

                // Send TBT3 Discover Mode (SOP') to Get Cable TBT3 Capabilities
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_CBL_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeC1PdSendMsg(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_DISCOVER_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_P:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                ScalerTypeC1PdUpdateCableRetryCounter();
#endif

                // Send SOP' Enter DP Mode
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_CBL_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeC1PdSendMsg(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                ScalerTypeC1PdUpdateCableRetryCounter();
#endif

                // Send SOP" Enter DP Mode
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_CBL_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeC1PdSendMsg(_PD_SOP_PP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                ScalerTypeC1PdUpdateCableRetryCounter();
#endif

                // Send SOP' DP Config
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_CBL_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeC1PdSendMsg(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_11);
            }

            break;

        case _PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                ScalerTypeC1PdUpdateCableRetryCounter();
#endif

                // Send SOP' DP Config
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_CBL_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeC1PdSendMsg(_PD_SOP_PP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_11);
            }

            break;

        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                ScalerTypeC1PdUpdateCableRetryCounter();
#endif

                // Send SOP' Enter DP Mode
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_CBL_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeC1PdSendMsg(_PD_SOP_P_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
                // Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
                ScalerTypeC1PdUpdateCableRetryCounter();
#endif

                // Send SOP" Enter DP Mode
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_CBL_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_BY_STATE);
                ScalerTypeC1PdSendMsg(_PD_SOP_PP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_REQ);
            }

            break;
#endif  // End of #if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)

        case _PD_ALT_MODE_SEND_ENTER_MODE:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Enter Mode REQ"
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ENTER_MODE_REQ);
            }

            break;

        case _PD_ALT_MODE_SEND_DP_STATUS:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "DP Status REQ"
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_10);
            }

            break;

        case _PD_ALT_MODE_SEND_DP_CONFIG:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                if(GET_TYPE_C_1_PD_PIN_ASSIGNMENT() == _TYPE_C_PIN_ASSIGNMENT_NONE)
                {
                    // When Re-configuration, DFP(DP_TX) Shall Ensure HPD_Low Maintained for a Minimum of 3ms
                    ScalerTimerDelayXms(3);
                }
#endif

                // Send "DP Config REQ"
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_11);
            }

            break;

        case _PD_ALT_MODE_READY:

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
            if((GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) && (GET_TYPE_C_1_PD_HPD_CNT() > 0) && (GET_TYPE_C_1_PD_ATTENTION_WAIT() == _FALSE))
            {
                if(ScalerTypeC1PdTxAvaliable() == _TRUE)
                {
                    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                    SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                    // Send "DP Status REQ"
                    ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_10);
                }
            }
#endif

            break;

        case _PD_ALT_MODE_SEND_EXIT_MODE:

            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Exit Mode REQ"
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_EXIT_MODE_REQ);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For UFP Dp Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdDpAltModeUfpProc(void)
{
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    if((GET_TYPE_C_1_PD_HPD_CNT() > 0) && (GET_TYPE_C_1_PD_ATTENTION_WAIT() == _FALSE))
    {
        if(ScalerTypeC1PdTxAvaliable() == _TRUE)
        {
            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_ATTENTION);
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DP_VDM_REQ);
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

            // Send "Attention REQ"
            ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);
        }
    }
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
}
#endif // End of #if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : Process For UFP Lenovo Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdLenovoAltModeUfpProc(void)
{
    if((GET_TYPE_C_1_PD_LENOVO_DOCK_EVENT() != 0x00) && (GET_TYPE_C_1_PD_LENOVO_ATTN_SENT_FLAG() == _FALSE))
    {
        if(ScalerTypeC1PdTxAvaliable() == _TRUE)
        {
            if(GET_TYPE_C_1_PD_LENOVO_ATTN_CNT() < _MAX_LENOVO_ATTN_CNT)
            {
                SET_TYPE_C_1_PD_LENOVO_ALT_STATE(_PD_ALT_MODE_SEND_ATTENTION);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_LENOVO_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Lenovo Attention REQ"
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);
            }
            else
            {
                SET_TYPE_C_1_PD_LENOVO_ALT_STATE(_PD_ALT_MODE_SEND_LENOVO_GET_STATUS);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_LENOVO_VDM_REQ);
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

                // Send "Lenovo Get_Status ACK (0x50)"
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_LENOVO_CMD_GET_STATUS_ACK);
            }
        }
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : Process For UFP Acer Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdAcerAltModeUfpProc(void)
{
    if((GET_TYPE_C_1_PD_ACER_USER_EVENT() & _TYPE_C_ACER_USER_EVENT_ATTENTION) == _TYPE_C_ACER_USER_EVENT_ATTENTION)
    {
        if(ScalerTypeC1PdTxAvaliable() == _TRUE)
        {
            // Send "Acer Attention (0x15)"
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, (EnumTypeCVdmCmd)_PD_VDM_ACER_CMD_ATTENTION_REQ);

            // Clear User Event When Attention Sent in Tx Success Int Flow
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_ACER_VDM_REQ);
            SET_TYPE_C_1_PD_ACER_ALT_MODE_STATE(_PD_ALT_MODE_SEND_ATTENTION);
        }
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : Process For UFP Hp Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdHpAltModeUfpProc(void)
{
    if((GET_TYPE_C_1_PD_HP_USER_EVENT() & _TYPE_C_HP_USER_EVENT_ATTEN_CONFIG) == _TYPE_C_HP_USER_EVENT_ATTEN_CONFIG)
    {
        if(GET_TYPE_C_1_PD_HP_ATTEN_RETRY_CNT() < 3)
        {
            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Send "Hp Atten_config"
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                SET_TYPE_C_1_PD_HP_ATTEN_TYPE(_PD_HP_ATTEN_CONFIG);

                // Clear User Event When Attention Sent in Tx Success Int Flow
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_HP_VDM_REQ);
                SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_SEND_HP_ATTEN_CONFIG);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);

                // Retry Fail CNT, for Atten_config
                ADD_TYPE_C_1_PD_HP_ATTEN_RETRY_CNT();
            }
        }
        else
        {
            // If Retry fail > 3, Clear User Event and Atten_retry_CNT
            CLR_TYPE_C_1_PD_HP_USER_EVENT(_TYPE_C_HP_USER_EVENT_ATTEN_CONFIG);
            CLR_TYPE_C_1_PD_HP_ATTEN_RETRY_CNT();
        }
    }
    else if((GET_TYPE_C_1_PD_HP_USER_EVENT() & _TYPE_C_HP_USER_EVENT_SET_VWIRE_SAMPLE_ACK) == _TYPE_C_HP_USER_EVENT_SET_VWIRE_SAMPLE_ACK)
    {
        if(ScalerTypeC1PdTxAvaliable() == _TRUE)
        {
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);

            // Clear User Event When Sample ACK Sent in Tx Success Int Flow
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_INT_SEND_VDM_RESP);
            SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_SEND_HP_SET_VWIRE_SAMPLE_ACK);

            // Send "Hp Set_vwire Sample ACK" (0x52)"
            ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_52);
        }
    }
    else if((GET_TYPE_C_1_PD_HP_USER_EVENT() & _TYPE_C_HP_USER_EVENT_ATTEN_VWIRE) == _TYPE_C_HP_USER_EVENT_ATTEN_VWIRE)
    {
        if(ScalerTypeC1PdTxAvaliable() == _TRUE)
        {
            // Send "Hp Atten_vwire"
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            SET_TYPE_C_1_PD_HP_ATTEN_TYPE(_PD_HP_ATTEN_VWIRE);

            // Clear User Event When Attention Sent in Tx Success Int Flow
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_HP_VDM_REQ);
            SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_SEND_HP_ATTEN_VWIRE);
            ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);
        }
    }
    else if((GET_TYPE_C_1_PD_HP_USER_EVENT() & _TYPE_C_HP_USER_EVENT_ATTEN_DATA) == _TYPE_C_HP_USER_EVENT_ATTEN_DATA)
    {
        if(ScalerTypeC1PdTxAvaliable() == _TRUE)
        {
            // Send "Hp Atten_data"
            SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
            SET_TYPE_C_1_PD_HP_ATTEN_TYPE(_PD_HP_ATTEN_DATA);

            // Clear User Event When Attention Sent in Tx Success Int Flow
            SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_HP_VDM_REQ);
            SET_TYPE_C_1_PD_HP_ALT_MODE_STATE(_PD_ALT_MODE_SEND_HP_ATTEN_DATA);
            ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);
        }
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : Process For UFP Dell Alt Mode Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdDellAltModeUfpProc(void)
{
    if(((GET_TYPE_C_1_PD_DELL_USER_EVENT() & _TYPE_C_DELL_USER_EVENT_ATTEN) == _TYPE_C_DELL_USER_EVENT_ATTEN) && (GET_TYPE_C_1_PD_DELL_ATTEN_WAIT() == _FALSE))
    {
        if(GET_TYPE_C_1_PD_DELL_ATTEN_RETRY_CNT() < 3)
        {
            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Clear User Event When Attention Sent in Tx Success Int Flow
                SET_TYPE_C_1_PD_TX_RETRY_FAIL_EVENT(_PD_TX_RETRY_FAIL_SOFT_RESET);
                SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_DELL_VDM_REQ);
                SET_TYPE_C_1_PD_DELL_ALT_MODE_STATE(_PD_ALT_MODE_SEND_DELL_ATTEN);
                ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);

                // Set Attention Wait Flag, Avoid Sending Attention all the Time
                SET_TYPE_C_1_PD_DELL_ATTEN_WAIT();
            }
        }
        else
        {
            // If Retry fail > 3, Clear Dell Related Macros and Set Atten_NoResponse System Event
            CLR_TYPE_C_1_PD_DELL_USER_EVENT(_TYPE_C_DELL_USER_EVENT_ATTEN);
            CLR_TYPE_C_1_PD_DELL_ATTEN_RETRY_CNT();
            CLR_TYPE_C_1_PD_DELL_ATTEN_WAIT();
            SET_TYPE_C_1_PD_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_NORESPONSE);
            SET_TYPE_C_1_PD_DELL_ALT_MODE_STATE(_PD_ALT_MODE_NONE);
        }
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#endif // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TypeC1 PD Power Switch Proc
// Input Value  : enumPowerAction : Power Switch Enum
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdPowerSwitch(EnumPowerAction enumPowerAction)
{
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // Set DP Alt Mode Lane Mapping
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
            ScalerDpPhyRxSetAltModeLaneMapping(ScalerTypeCPcbPortConvertToDx(enumTypeCPcbPort), GET_TYPE_C_1_PD_PIN_ASSIGNMENT(), GET_TYPE_C_1_CC_ORIENTATION());
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
            ScalerDpPhyTxSetAltModeLaneMapping(ScalerTypeCPcbPortConvertToPx(enumTypeCPcbPort), GET_TYPE_C_1_PD_PIN_ASSIGNMENT(), GET_TYPE_C_1_CC_ORIENTATION());
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Timer Event Proc of PD RX1
// Input Value  : enumEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _SCALER_TIMER_EVENT_PD_1_PPS_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT:

            if(GET_TYPE_C_1_PD_FW_STATE() == _PD_HARDRESET)
            {
                return;
            }

            if((GET_TYPE_C_1_PD_EPR_MODE() == _TRUE) && (GET_TYPE_C_1_PD_CANCEL_SRC_EPR_KEEP_ALIVE() == _TRUE))
            {
                // Skip Sending Hard Reset When Macro Set
                CLR_TYPE_C_1_PD_CANCEL_SRC_EPR_KEEP_ALIVE();

                return;
            }

            // PPS / SourceEPRKeepAlive Timeout : Send Hard Reset
            ScalerTypeC1PdSendHardRst();

            break;

        case _SCALER_TIMER_EVENT_PD_1_SEND_HARD_RST:

            if(GET_TYPE_C_1_PD_FW_STATE() == _PD_HARDRESET)
            {
                return;
            }

            // Separate "Normal Flow" & "S8 Interop" TimerEvent Since HRST Event Will be Canceled During Power Contract
            ScalerTypeC1PdSendHardRst();

            break;

        case _SCALER_TIMER_EVENT_PD_1_SNK_HARD_RST_TIMEOUT:

            if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SNK) && (GET_TYPE_C_1_PD_FW_STATE() == _PD_HARDRESET))
            {
                if(GET_TYPE_C_1_PD_HARD_RST_CNT() <= _MAX_HARD_RST_CNT)
                {
                    // [0x6B02] Enble PHY Layer BMC Tx/Rx
                    ScalerSetBit(P6B_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

                    // Send Hard Reset
                    ScalerTypeC1PdSendHardRst();
                }
                else
                {
                    // Transit to PD No-Response, and Disable Rcv Msg. INT
                    SET_TYPE_C_1_PD_FW_STATE(_PD_NO_RESPONSE);
                    ScalerTypeC1PdRxIntControl(_DISABLE);

#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
                    // Update Vbus Power Info to Support Sink OVP/UVP
                    ScalerTypeC1PmicSetting(_ON, _PD_POWER_SNK, _PD_FIX_SUPPLY_PDO, 500, 0, _PD_PEAK_CUR_NONE);
#endif

#if((_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE) && (_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON))
                    // Start PMIC Protection
                    ScalerTypeC1PmicProtectStart(_TYPE_C_POWER_SNK);
#endif

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
                    // [FW Sol. for _TYPE_C_5B_LS_ADC_GEN_1] Write 1 Clear 5Bit LS_ADC Vbus Off IRQ and Enable IRQ_EN to Detect Unattach Event
                    ScalerTypeCAdcOnOffCompIntControl(_TYPE_C_CHANNEL_1_VMON, _OFF, _ENABLE);
#else
                    // Enable Vbus Detection For CC HW to Detect Unattach Event
                    ScalerTypeC1CcVbusDetCtrl(_ENABLE);
#endif
                }
            }

            break;

        case _SCALER_TIMER_EVENT_PD_1_S8_HRST:

            if(GET_TYPE_C_1_PD_FW_STATE() == _PD_HARDRESET)
            {
                return;
            }

            // If It is Already in DP Config, No Need to Do Hard Reset
            if(GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() != _PD_DP_CONFIG)
            {
                ScalerTypeC1PdSendHardRst();
            }

            break;

        case _SCALER_TIMER_EVENT_PD_1_CLR_REQ_WAIT:

            CLR_TYPE_C_1_PD_REQ_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_1_CLR_PARTNER_ALT_SUPPORT:

            CLR_TYPE_C_1_PD_PARTNER_ALT_SUPPORT();

            break;

        case _SCALER_TIMER_EVENT_PD_1_TPC_ERROR_RECOVERY:

            SET_TYPE_C_1_CC_ERROR_RECOVERY();

            break;

        case _SCALER_TIMER_EVENT_PD_1_T480_ERROR_RECOVERY:

            SET_TYPE_C_1_CC_ERROR_RECOVERY();

            break;

        case _SCALER_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER:

            // From : 1.Proc Hard Reset
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
            // Turn Off Vbus Power
            ScalerTypeC1PmicSetting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
            // Enable Vbus Discharge
            ScalerTypeC1PmicVbusDischarge(_ON);
#endif

#if(_EMB_TYPE_C_1_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
            // Tool Not Show Warning UI when We Turn Off Vbus
            ScalerTypeC1CcToolWarningUIControl(_DISABLE);
#endif

            break;

        case _SCALER_TIMER_EVENT_PD_1_SRC_TURN_ON_POWER:

            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                // [0x6C37][7:6] if(PD 3.0) Switch Rp to Default Rp (36K / 12K / 4.7K)
#if(_EMB_TYPE_C_1_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
                ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_DEF << 6));
#elif(_EMB_TYPE_C_1_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
                ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_1P5A << 6));
#else
                ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_TYPE_C_SET_RP_3P0A << 6));
#endif  // End of #if(_EMB_TYPE_C_1_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
            }

            // Turn On Vconn
            ScalerTypeC1CcVconnControl(_ON);

            // Set OCP Threshlod
            SET_TYPE_C_1_OCP_CURRENT((WORD)(((DWORD)(GET_TYPE_C_1_CC_DEF_CUR()) * (DWORD)(GET_TYPE_C_1_OCP_RATIO(0))) / 100));

            // Turn On Vbus Power to vSafe5V
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
            ScalerTypeC1PmicSetting(_ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, 500, GET_TYPE_C_1_OCP_CURRENT(), _PD_PEAK_CUR_NONE);
#endif

            break;

        case _SCALER_TIMER_EVENT_PD_1_CLR_PRS_WAIT:

            CLR_TYPE_C_1_PD_PRS_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_1_CLR_DRS_WAIT:

            CLR_TYPE_C_1_PD_DRS_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_1_CLR_VCS_WAIT:

            CLR_TYPE_C_1_PD_VCS_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_1_DFP_START_ALT_MODE:

            SET_TYPE_C_1_PD_DP_ALT_STATE(_PD_ALT_MODE_SEND_DISCOVER_ID);

            break;

        case _SCALER_TIMER_EVENT_PD_1_LENOVO_RESP_TIMEOUT:

            CLR_TYPE_C_1_PD_LENOVO_ATTN_SENT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_1_VDM_RESP_CONFLICT_TIMEOUT:

            SET_TYPE_C_1_CC_ERROR_RECOVERY();
            ADD_TYPE_C_1_PD_VDM_RESP_CONFLICT_CNT();

            break;

        case _SCALER_TIMER_EVENT_PD_1_CLR_ATTENTION_WAIT:

            CLR_TYPE_C_1_PD_ATTENTION_WAIT();

            break;

        case _SCALER_TIMER_EVENT_PD_1_CLR_GET_SNK_CAP_WAIT:

            CLR_TYPE_C_1_PD_GET_SNK_CAP_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_1_CLR_VDMMSG_WAIT:

            CLR_TYPE_C_1_PD_VDMMSG_WAIT_FLAG();

            break;

        case _SCALER_TIMER_EVENT_PD_1_CLR_VDM_BUSY_FLAG:

            CLR_TYPE_C_1_PD_VDM_BUSY_FLAG();

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Process For OCP / OVP Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdOcpOvpProc(void)
{
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_ERROR_RECOVERY)
    // Set Error Recovery
    SET_TYPE_C_1_CC_ERROR_RECOVERY();
    CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);
#elif(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
    // PMIC OCP or OVP Triggered : (PD2.0 || Power Contract Not Ready) : Hard Reset, (PD3.0 && Power Contract Ready) : Alert + Hard Reset
    if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0) || (GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() == _FALSE))
    {
        ScalerTypeC1PdSendHardRst();
        CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);
    }
    else if(GET_TYPE_C_1_PD_ALERT_SENT() == _FALSE)
    {
        // Clear OCP/OVP/UVP/Vconn OCP Event when (Power Contract Established in EXINT0)
        SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_SEND_ALERT);

        if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
        {
            SET_TYPE_C_1_PD_TYPE_OF_ALERT(_TYPE_C_TYPE_OF_ALERT_OCP);
        }

        if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
        {
            SET_TYPE_C_1_PD_TYPE_OF_ALERT(_TYPE_C_TYPE_OF_ALERT_OVP);
        }
    }
#elif(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_BY_USER)
    // User directly Design the Processing Flow. Embedded Do Nothing but will refer to the Port Controller Event!
    CLR_TYPE_C_1_PD_SYS_EVENT(_PD_SYS_EVENT_POWER_OCP | _PD_SYS_EVENT_POWER_OVP | _PD_SYS_EVENT_POWER_UVP | _PD_SYS_EVENT_VCONN_OCP);
#endif
}

//--------------------------------------------------
// Description  : Send Power Delivery Message
// Input Value  : enumPacketType : _PD_SOP_PKT / _PD_SOP_P_PKT
//                enumPdCmd : _PD_CMD_SRC_CAP / _PD_CMD_PS_RDY / _PD_CMD_VDM ...
//                enumVdmCmd : _PD_VDM_CMD_RESERVED / _PD_VDM_CMD_DISCOVER_ID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSendMsg(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    // 1. Clear Flags
    CLR_TYPE_C_1_PD_INT_OVERWRITE();
    CLR_TYPE_C_1_PD_TRANSMIT_RESULT();

    // 2. Construct Msg.
    ScalerTypeC1PdConstructMsg(enumPacketType, enumPdCmd, enumVdmCmd);

    // Start Disable Rcv Msg.
    ScalerTypeC1PdRxIntControl(_DISABLE);

    // 3. Only Send Msg. When Tx FIFO Has Not Been Overwritten by INT during Msg. Construct Flow
    if(GET_TYPE_C_1_PD_INT_OVERWRITE() == _TRUE)
    {
        // Enable Rcv Msg.
        ScalerTypeC1PdRxIntControl(_ENABLE);

        // Function Has Been Interrupted Before Sending, Set "_PD_SENT_DISCARDED" and Just Not Start Transmit.
        SET_TYPE_C_1_PD_TRANSMIT_RESULT(_PD_SENT_DISCARDED);
    }
    else
    {
        // [0x6BDC] Clear IRQs
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
        ScalerSetBit(P6B_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
        ScalerSetBit(P6B_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

        // [0x6BDD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
        ScalerSetBit(P6B_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

        // [0x6BDA] Start Transmit ([1] = 1, Wait For GoodCRC Response After Transmission)
        ScalerSetBit(P6B_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

        // [0x6BE5] Set Tx FIFO [2:1] Spec Ver = 2.0, For PD2.0/3.0 CTS
        ScalerSetBit(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (_BIT1));
    }
}

//--------------------------------------------------
// Description  : Construct Power Delivery Message Not Include Soft Reset and Hard Reset and Cable Reset
// Input Value  : enumPacketType : _PD_SOP_PKT / _PD_SOP_P_PKT
//                enumPdCmd : _PD_CMD_SRC_CAP / _PD_CMD_PS_RDY / _PD_CMD_VDM ...
//                enumVdmCmd : _PD_VDM_CMD_RESERVED / _PD_VDM_CMD_DISCOVER_ID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdConstructMsg(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    BYTE ucExtendedBit = 0;
    BYTE ucDataObjectCnt = 0;
    BYTE ucMsgHeader = 0;

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
#endif
            ucDataObjectCnt = 0;
            break;

        // Data Message Has Different Num of Data Objects According to Different Message
        case _PD_CMD_SRC_CAP:

            ucDataObjectCnt = GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT();

#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
            // Do not send PPS PDO when the Spec Version is PD2.0 or not support PPS
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_2_0)
#endif
            {
                for(pData[0] = GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1; pData[0] > 0; pData[0]--)
                {
                    if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[0]) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        ucDataObjectCnt --;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;

        case _PD_CMD_REQUEST:

            ucDataObjectCnt = 1;
            break;

        case _PD_CMD_SNK_CAP:

            ucDataObjectCnt = GET_TYPE_C_1_PD_SPR_SNK_PDO_CNT();
            break;

        case _PD_CMD_VDM:

            switch(enumVdmCmd)
            {
                case _PD_VDM_CMD_DISCOVER_ID_REQ:
                case _PD_VDM_CMD_DISCOVER_SVID_REQ:
                case _PD_VDM_CMD_DISCOVER_MODE_REQ:
                case _PD_VDM_CMD_ENTER_MODE_REQ:
                case _PD_VDM_CMD_EXIT_MODE_REQ:
                case _PD_VDM_CMD_15:    // Acer Attention (0x15)

                    ucDataObjectCnt = 1;
                    break;

                case _PD_VDM_CMD_ATTENTION_REQ:

                    // If Sub State = SEND_DP_VDM_REQ, Dp Alt Mode Attention
                    if(GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SEND_DP_VDM_REQ)
                    {
                        ucDataObjectCnt = 2;
                    }
                    else if(GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SEND_LENOVO_VDM_REQ)
                    {
                        ucDataObjectCnt = 1;
                    }
                    else if(GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SEND_HP_VDM_REQ)
                    {
                        ucDataObjectCnt = 2;
                    }
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
                    else if(GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SEND_DELL_VDM_REQ)
                    {
                        // User VDM Cnt Should be 0~6, plus VDM Header
                        ucDataObjectCnt = GET_TYPE_C_1_PD_DELL_USER_VDM_CNT() + 1;
                    }
#endif

                    break;

                // If SVID = _DP_SID, CMD_10 = DP_Status REQ and CMD_11 = DP_Config REQ
                case _PD_VDM_CMD_10:
                case _PD_VDM_CMD_11:

                    ucDataObjectCnt = 2;
                    break;

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
                // If SVID = _LENOVO_VID, CMD_50 = GET_STATUS ACK
                case _PD_VDM_CMD_50:

                    ucDataObjectCnt = 3;
                    break;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
                // If SVID = _HP_VID, CMD_52 = Set_vwire Sample ACK
                case _PD_VDM_CMD_52:

                    ucDataObjectCnt = GET_TYPE_C_1_PD_HP_USER_VDM_CNT() + 2;
                    break;
#endif

                case _PD_VDM_CMD_RESERVED:
                default:

                    ucDataObjectCnt = 0;
                    break;
            }

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_BAT_STATUS:        // Not Implemented
        case _PD_CMD_ALERT:
        case _PD_CMD_GET_COUNTRY_INFO:  // Not Implemented

            ucDataObjectCnt = 1;
            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        case _PD_CMD_EPR_SRC_CAP:

            ucExtendedBit = 1;

            if((GET_TYPE_C_1_PD_EPR_SRC_PDO_CNT() == 0) && (GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() < 7))
            {
                // If Only SPR PDO and PDO Count < 7, Do Not Use Chunked to Send EPR Source Cap
                // Data Object = SPR PDO Count + 1 (Extended Header)
                ucDataObjectCnt = GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() + 1;

                CLR_TYPE_C_1_PD_TX_CHUNKED_MESSAGE();
            }
            else
            {
                // If PDO Count > 7, Use Chunked to Send EPR Source Cap
                if(GET_TYPE_C_1_PD_TX_CHUNK_NUMBER() == 0)
                {
                    // Chunk 0 : Data Object = 7
                    ucDataObjectCnt = 7;

                    SET_TYPE_C_1_PD_TX_CHUNKED_MESSAGE();
                }
                else
                {
                    // Chunk 1 : Data Object = EPR PDO Count + 1 (Extended Header)
                    ucDataObjectCnt = GET_TYPE_C_1_PD_EPR_SRC_PDO_CNT() + 1;
                }
            }

            break;
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
#endif  // #if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)

        default:

            ucDataObjectCnt = 0;
            break;
    }

    // 2. Construct Data Object into Tx FIFO, if Number of Data Object is not 0
    if(ucDataObjectCnt != 0)
    {
        ScalerTypeC1PdConstructDataObj(enumPacketType, enumPdCmd, enumVdmCmd);
    }

    // 3. [0x6BE5] Construct Msg. Header 0
    // ===================================================================
    // | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    // |Ext| Num. of DO| PR|  Spec | DR|
    ucMsgHeader = ucMsgHeader | ucExtendedBit;
    ucMsgHeader = ucMsgHeader | (BYTE)(ucDataObjectCnt << 4);

    if(enumPacketType == _PD_SOP_PKT)
    {
        ucMsgHeader = ucMsgHeader | (GET_TYPE_C_1_PD_POWER_ROLE() << 3);
        ucMsgHeader = ucMsgHeader | (GET_TYPE_C_1_PD_SPEC_VER() << 1);
        ucMsgHeader = ucMsgHeader | GET_TYPE_C_1_PD_DATA_ROLE();
    }
    else if((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT))
    {
        ucMsgHeader = ucMsgHeader | (BYTE)(_PD_DEVICE << 3);
        ucMsgHeader = ucMsgHeader | (GET_TYPE_C_1_PD_CBL_SPEC_VER() << 1);
    }

    // ====================================================================

    // 4. Disable Rcv Msg. INT
    ScalerTypeC1PdRxIntControl(_DISABLE);

    // 5. Start to Fill Packet Type, Msg. Header & Data Object
    if(ScalerGetBit(P6B_DA_TX_TRANSMIT_CTRL, _BIT7) == 0x00)
    {   // Do Not Write Tx FIFO When Tx is Transmitting During INT

        // [0x6BE0] Select Transmission Mode
        // [7:6] b'00 = Preamble + SOP + Msg. Header + Data + CRC + EOP
        ScalerSetBit(P6B_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), 0x00);

        // [0x6BE0] Set Packet Type [5:3]
        ScalerSetBit(P6B_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), ((enumPacketType << 3) & (_BIT5 | _BIT4 | _BIT3)));

        // [0x6BE5] Fill Message Header 0
        ScalerSetByte(P6B_E5_TX_FIFO_MSG_HEADER0, ucMsgHeader);

        // [0x6BE6] Fill in Msg. Header 1 ( Msg. Header[4:0] : Command Type = enumCtrlMsg )
        ScalerSetBit(P6B_E6_TX_FIFO_MSG_HEADER1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (enumPdCmd & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

        // Clear Tx FIFO Addr.
        ScalerSetByte(P6B_E9_TX_FIFO_ADDR, 0x00);

        // Fill Data Object into Tx FIFO
        for(pData[0] = 0; pData[0] < (ucDataObjectCnt * 4); pData[0]++)
        {
            ScalerSetByte(P6B_EA_TX_FIFO_DATA, g_pucTypeC1PdDataObject[pData[0]]);

            // Manual Increase Tx FIFO Address
            ScalerSetByte(P6B_E9_TX_FIFO_ADDR, ScalerGetByte(P6B_E9_TX_FIFO_ADDR) + 1);
        }
    }

    // 6. Enable Rcv Msg. INT
    ScalerTypeC1PdRxIntControl(_ENABLE);
}

//--------------------------------------------------
// Description  : Fill Data Objects into TX FIFO
// Input Value  : enumPacketType : _PD_SOP_PKT / _PD_SOP_P_PKT
//                enumPdCmd : _PD_CMD_SRC_CAP / _PD_CMD_PS_RDY / _PD_CMD_VDM ...
//                enumVdmCmd : _PD_VDM_CMD_RESERVED / _PD_VDM_CMD_DISCOVER_ID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdConstructDataObj(EnumTypeCPDPacketType enumPacketType, EnumTypeCPDCmd enumPdCmd, EnumTypeCVdmCmd enumVdmCmd)
{
    // Clear g_pucTypeC1PdDataObject
    for(pData[0] = 0; pData[0] < (_MAX_DATA_OBJ_CNT * 4); pData[0]++)
    {
        g_pucTypeC1PdDataObject[pData[0]] = 0;
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
                g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT5);
            }
#endif

#if(_USB_SUSPEND == _TRUE)
            g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT4);
#endif

            if(GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _TRUE)
            {
                g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT3);
            }

#if(_EMB_TYPE_C_1_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
            g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT2);
#endif

#if((_TYPE_C_1_PD_DFP_SWAP_TO_UFP == _TRUE) || (_TYPE_C_1_PD_UFP_SWAP_TO_DFP == _TRUE))
            g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT1);
#endif

#if(_UNCHUNK_SUPPORT == _TRUE)
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT0);
            }
#endif

            // [23] EPR Mode Capable
            if(GET_TYPE_C_1_PD_EPR_SRC_CAPABLE() == _TRUE)
            {
                g_pucTypeC1PdDataObject[1] = g_pucTypeC1PdDataObject[1] | (_BIT7);
            }

            for(pData[1] = 0; pData[1] < GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT(); pData[1]++)
            {
                if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1]) == _PD_FIX_SUPPLY_PDO)
                {
                    // [31:30] PDO Type = 2'b00
                    g_pucTypeC1PdDataObject[(pData[1] * 4)] = g_pucTypeC1PdDataObject[(pData[1] * 4)] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1]) << 6));

                    // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                    // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                    g_pucTypeC1PdDataObject[(pData[1] * 4) + 1] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 1] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_PEAK(pData[1]) << 4) & (_BIT5 | _BIT4));
                    g_pucTypeC1PdDataObject[(pData[1] * 4) + 1] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 1] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1]) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                    // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                    // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                    g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1]) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1]) > GET_TYPE_C_1_PD_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] | ((BYTE)(GET_TYPE_C_1_PD_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] | ((BYTE)GET_TYPE_C_1_PD_CBL_MAX_CUR());
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1]) >> 8) & (_BIT1 | _BIT0));
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1])));
                    }
                }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
                else if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1]) == _PD_3_PROGRAMMABLE_PDO))
                {
                    // [31:28] PDO Type = 4'b1100 (Programmabl Power Supply)
                    g_pucTypeC1PdDataObject[(pData[1] * 4)] = g_pucTypeC1PdDataObject[(pData[1] * 4)] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1])) << 4);

                    // [24:17] Max Voltage in 100mV
                    g_pucTypeC1PdDataObject[(pData[1] * 4)] = g_pucTypeC1PdDataObject[(pData[1] * 4)] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1]) / 10) >> 7) & (_BIT0));
                    g_pucTypeC1PdDataObject[(pData[1] * 4) + 1] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 1] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1]) / 10) << 1) & (~_BIT0));

                    // [15:8] Min Voltage in 100mV
                    g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] = (BYTE)(GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(pData[1]) / 10);

                    // [6:0] Max Current in 50mA
                    if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (((GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1])) * 5) > GET_TYPE_C_1_PD_CBL_MAX_CUR()))
                    {
                        // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] = (((BYTE)(GET_TYPE_C_1_PD_CBL_MAX_CUR() / 5)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                    else
                    {
                        // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                        // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] = (((BYTE)GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1])) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
                }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
            }

            break;

        case _PD_CMD_REQUEST:

            // | 31 | 30 | 29 | 28 | 27 | 26 | 25 | 24 |
            // | 0  |   Obj. Pos   | GB | CM | UC | Sus|
            g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (GET_TYPE_C_1_PD_REQ_OBJ_POS() << 4);
            g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (GET_TYPE_C_1_PD_REQ_GIVE_BACK() << 3);

#if((_EMB_TYPE_C_1_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT) || (_EMB_TYPE_C_1_USB_SPEED == _USB_BILLBOARD_ONLY))
            g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT1);
#endif

#if(_USB_SUSPEND == _FALSE)
            g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT0);
#endif

            // | 23 | 22 | 21 | 20 | 19 | 18 | 17 | 16 |
            // | UC | Reserved(0)  |   Op. Cur [9:6]   |
#if(_UNCHUNK_SUPPORT == _TRUE)
            g_pucTypeC1PdDataObject[1] = g_pucTypeC1PdDataObject[1] | (_BIT7);
#endif

            if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
            {
                if((WORD)GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) < GET_TYPE_C_1_PD_REQ_INFO_2())
                {
                    // Set Capability Mismatch Flag
                    g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT2);

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucTypeC1PdDataObject[1] = g_pucTypeC1PdDataObject[1] | ((BYTE)(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | ((BYTE)(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | ((BYTE)(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) >> 8) & (_BIT1 | _BIT0));
                    g_pucTypeC1PdDataObject[3] = g_pucTypeC1PdDataObject[3] | (BYTE)(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1));
                }
                else
                {
                    // Set Capability Mismatch Flag
                    g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | ((GET_TYPE_C_1_PD_REQ_CAP_MIS() << 2) & (_BIT2));

                    // RDO[19:10] : Fix (Op. Cur in 10mA)
                    g_pucTypeC1PdDataObject[1] = g_pucTypeC1PdDataObject[1] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_1() >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_1() << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                    // RDO[9:0] : Fix (Max. Cur in 10mA)
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_2() >> 8) & (_BIT1 | _BIT0));
                    g_pucTypeC1PdDataObject[3] = g_pucTypeC1PdDataObject[3] | (BYTE)(GET_TYPE_C_1_PD_REQ_INFO_2());
                }
            }
            else
            {
                // Set Capability Mismatch Flag
                g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | ((GET_TYPE_C_1_PD_REQ_CAP_MIS() << 2) & (_BIT2));

                // RDO[19:9] : PPS (Vol in 20mV)
                g_pucTypeC1PdDataObject[1] = g_pucTypeC1PdDataObject[1] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_1() >> 7) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_1() << 1) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

                // RDO[6:0] : PPS (Op. Cur in 50mA)
                g_pucTypeC1PdDataObject[3] = g_pucTypeC1PdDataObject[3] | ((BYTE)(GET_TYPE_C_1_PD_REQ_INFO_2()) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
            }

            break;

        case _PD_CMD_VDM:

            ScalerTypeC1PdConstructVdmDataObj(enumPacketType, enumVdmCmd);

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_0)
        case _PD_CMD_ALERT:

            // ---------- Data Message (1 Data Object) ----------
            // Set Type of Alert : [30] OVP Event, [26] OCP Event
#if(_TYPE_C_PMIC_OCP_OVP_PROCESS_OPTION == _TYPE_C_PMIC_PROCESS_OPTION_HARD_RESET)
            if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OVP) == _PD_SYS_EVENT_POWER_OVP)
            {
                g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT6);
            }
            if((GET_TYPE_C_1_PD_SYS_EVENT() & _PD_SYS_EVENT_POWER_OCP) == _PD_SYS_EVENT_POWER_OCP)
            {
                g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT2);
            }
#endif

            // [31:24] Type of Alert
            g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (BYTE)(GET_TYPE_C_1_PD_TYPE_OF_ALERT());

            // [23:20] Fixed Batteries, [19:16] Hot Swappable Batteries
            g_pucTypeC1PdDataObject[1] = g_pucTypeC1PdDataObject[1] | (BYTE)(GET_TYPE_C_1_PD_BAT_STATUS());

            // [15:4] Rsv., [3:0] Extended Alert Event Type
            g_pucTypeC1PdDataObject[3] = g_pucTypeC1PdDataObject[3] | ((BYTE)(GET_TYPE_C_1_PD_EXT_ALERT_EVENT()) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

#if(_TYPE_C_EMB_PD_VERSION >= _PD_VERSION_3_1)
        case _PD_CMD_EPR_SRC_CAP:

            // ---------- Extended Message Header (2 Bytes) ----------
            // [15] Ext Msg. is Sent in Chunk (Always Set to 1, if Not Support Unchunked Ext Msg.)
#if(_UNCHUNK_SUPPORT == _FALSE)
            g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | (_BIT7);
#endif

            if(GET_TYPE_C_1_PD_TX_CHUNKED_MESSAGE() == _TRUE)
            {
                // [14:11] Chunk Number
                g_pucTypeC1PdDataObject[0] = g_pucTypeC1PdDataObject[0] | ((GET_TYPE_C_1_PD_TX_CHUNK_NUMBER()) << 3);

                // [8:0] Data Size : Total Num Of Data Blocks = [ 7 (Max SPR PDO Count) + EPR PDO Count ] * 4
                g_pucTypeC1PdDataObject[1] = ((7 + GET_TYPE_C_1_PD_EPR_SRC_PDO_CNT()) * 4);
            }
            else
            {
                // [8:0] Data Size : Total Num Of Data Blocks = Total PDO Count * 4
                g_pucTypeC1PdDataObject[1] = (GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() * 4);
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
                    g_pucTypeC1PdDataObject[5] = g_pucTypeC1PdDataObject[5] | (_BIT5);
                }
#endif

#if(_USB_SUSPEND == _TRUE)
                g_pucTypeC1PdDataObject[5] = g_pucTypeC1PdDataObject[5] | (_BIT4);
#endif
                if(GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _TRUE)
                {
                    g_pucTypeC1PdDataObject[5] = g_pucTypeC1PdDataObject[5] | (_BIT3);
                }

#if(_EMB_TYPE_C_1_USB_ROLE != _TYPE_C_USB_NOT_SUPPORT)
                g_pucTypeC1PdDataObject[5] = g_pucTypeC1PdDataObject[5] | (_BIT2);
#endif

#if((_TYPE_C_1_PD_DFP_SWAP_TO_UFP == _TRUE) || (_TYPE_C_1_PD_UFP_SWAP_TO_DFP == _TRUE))
                g_pucTypeC1PdDataObject[5] = g_pucTypeC1PdDataObject[5] | (_BIT1);
#endif

#if(_UNCHUNK_SUPPORT == _TRUE)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject[5] = g_pucTypeC1PdDataObject[5] | (_BIT0);
                }
#endif

                // [23] EPR Mode Capable
                if(GET_TYPE_C_1_PD_EPR_SRC_CAPABLE() == _TRUE)
                {
                    g_pucTypeC1PdDataObject[4] = g_pucTypeC1PdDataObject[4] | (_BIT7);
                }

                for(pData[1] = 0; pData[1] < GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT(); pData[1] ++)
                {
                    if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1]) == _PD_FIX_SUPPLY_PDO)
                    {
                        // Only Fill Half of The 7th SPR PDO [15:0] When Use Chunked Message to Send EPR Source Cap
                        if(pData[1] < 6)
                        {
                            // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1])) << 6);

                            // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                            // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 4] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 4] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_PEAK(pData[1]) << 4) & (_BIT5 | _BIT4));
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 4] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 4] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1]) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                        }

                        // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                        // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1]) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                        if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1]) > GET_TYPE_C_1_PD_CBL_MAX_CUR()))
                        {
                            // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] | ((BYTE)(GET_TYPE_C_1_PD_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] | ((BYTE)GET_TYPE_C_1_PD_CBL_MAX_CUR());
                        }
                        else
                        {
                            // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                            // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1]) >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1])));
                        }
                    }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
                    else if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1]) == _PD_3_PROGRAMMABLE_PDO))
                    {
                        // Only Fill Half of The 7th SPR PDO [15:0] When Use Chunked Message to Send EPR Source Cap
                        if(pData[1] < 6)
                        {
                            // [31:28] PDO Type = 4'b1100 (Programmabl Power Supply)
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1])) << 4);

                            // [24:17] Max Voltage in 100mV
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1]) / 10) >> 7) & (_BIT0));
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 4] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 4] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1]) / 10) << 1) & (~_BIT0));
                        }

                        // [15:8] Min Voltage in 100mV
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 3] = (BYTE)(GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(pData[1]) / 10);

                        // [6:0] Max Current in 50mA
                        if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (((GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1])) * 5) > GET_TYPE_C_1_PD_CBL_MAX_CUR()))
                        {
                            // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] = (((BYTE)(GET_TYPE_C_1_PD_CBL_MAX_CUR() / 5)) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                        }
                        else
                        {
                            // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                            // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 2] = (((BYTE)GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1])) & (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
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
                        g_pucTypeC1PdDataObject[3] = g_pucTypeC1PdDataObject[3] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1)) << 6);

                        // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                        // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                        g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_PEAK(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1) << 4) & (_BIT5 | _BIT4));
                        g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
                    }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
                    else if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1) == _PD_3_PROGRAMMABLE_PDO))
                    {
                        // [31:28] PDO Type = 4'b1100 (Programmabl Power Supply)
                        g_pucTypeC1PdDataObject[3] = g_pucTypeC1PdDataObject[3] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1)) << 4);

                        // [24:17] Max Voltage in 100mV
                        g_pucTypeC1PdDataObject[3] = g_pucTypeC1PdDataObject[3] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1) / 10) >> 7) & (_BIT0));
                        g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() - 1) / 10) << 1) & (~_BIT0));
                    }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                }

                for(pData[1] = 0; pData[1] < GET_TYPE_C_1_PD_EPR_SRC_PDO_CNT(); pData[1] ++)
                {
                    if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1] + 7) == _PD_FIX_SUPPLY_PDO)
                    {
                        // [31:30] PDO Type = 2'b00 (Fixed Power Supply)
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 7] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 7] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1] + 7)) << 6);

                        // |   22   | 21 | 20 | 19 | 18 | 17 | 16 |
                        // | Rsv(0) | Peak Cur| Voltage(50mV)[9:6]|
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 6] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 6] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_PEAK(pData[1] + 7) << 4) & (_BIT5 | _BIT4));
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 6] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 6] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1] + 7) / 5) >> 6) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));

                        // | 15 | 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00 |
                        // |     Voltage(50mV) [5:0]     |                  Max.Cur [7:0]                  |
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1] + 7) / 5) << 2) & (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

                        if((GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) && (GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1] + 7) > GET_TYPE_C_1_PD_CBL_MAX_CUR()))
                        {
                            // When Power Role = SRC, Adjust Source Capabilty Current Acording to Cable Info, Make Sure Current Not > Cable Current
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] | ((BYTE)(GET_TYPE_C_1_PD_CBL_MAX_CUR() >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 4] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 4] | ((BYTE)GET_TYPE_C_1_PD_CBL_MAX_CUR());
                        }
                        else
                        {
                            // When Power Role = SRC and Source Capabilty Current < Cable Current, Then No Need to Concern Cable's Info
                            // When Power Role = SNK, It Should Provide Full Source Capabilities (That is, The PDOs Declared By The VIF)
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1] + 7) >> 8) & (_BIT1 | _BIT0));
                            g_pucTypeC1PdDataObject[(pData[1] * 4) + 4] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 4] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_CUR(pData[1] + 7)));
                        }
                    }
                    else if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1] + 7) == _PD_3_1_ADJUSTABLE_PDO)
                    {
                        // [31:28] PDO Type = 4'b1101 (Adjustable Voltage Supply)
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 7] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 7] | (((BYTE)GET_TYPE_C_1_PD_SRC_PDO_TYPE(pData[1] + 7)) << 4);

                        // [27:26] Peak Current
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 7] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 7] | ((BYTE)(GET_TYPE_C_1_PD_SRC_CAP_PEAK(pData[1] + 7) << 2) & (_BIT3 | _BIT2));

                        // [25:17] Max Voltage in 100mV
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 7] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 7] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1] + 7) / 10) >> 7) & (_BIT1 | _BIT0));
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 6] = g_pucTypeC1PdDataObject[(pData[1] * 4) + 6] | ((BYTE)((GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(pData[1] + 7) / 10) << 1) & (~_BIT0));

                        // [15:8] Min Voltage in 100mV
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 5] = (BYTE)(GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(pData[1] + 7) / 10);

                        // [7:0] PDP in 1W
                        g_pucTypeC1PdDataObject[(pData[1] * 4) + 4] = (BYTE)(GET_TYPE_C_1_MAX_POWER() / 10);
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
// Description  : Fill Data Objects into TX FIFO @ Main Loop
// Input Value  : enumPacketType : _PD_SOP_PKT / _PD_SOP_P_PKT
//                enumVdmCmd : _PD_VDM_CMD_RESERVED / _PD_VDM_CMD_DISCOVER_ID_REQ ...
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdConstructVdmDataObj(EnumTypeCPDPacketType enumPacketType, EnumTypeCVdmCmd enumVdmCmd)
{
    switch(enumVdmCmd)
    {
        case _PD_VDM_CMD_DISCOVER_ID_REQ:
        case _PD_VDM_CMD_DISCOVER_SVID_REQ:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] PD SID = 0xFF00
            g_pucTypeC1PdDataObject[0] = 0xFF;
            g_pucTypeC1PdDataObject[1] = 0x00;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos = b'000
            g_pucTypeC1PdDataObject[2] = (_BIT7);

            // For SOP Packet : If Port Partners Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            // For SOP' Packet : If Port Partners & Cable Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)) ||
               ((enumPacketType == _PD_SOP_P_PKT) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_CBL_SPEC_VER() == _PD_VERSION_3_0)))
            {
                g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                // SVDM Version = 2.1 Only when Port Partner or Cable Support 2.1 or Higher
                if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)) ||
                   ((enumPacketType == _PD_SOP_P_PKT) && (GET_TYPE_C_1_PD_CBL_SVDM_VERSION() >= _PD_SVDM_VER_2_1)))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Discover ID Request (0x01) / Discover SVID Request (0x02)
            g_pucTypeC1PdDataObject[3] = enumVdmCmd;

            break;

        case _PD_VDM_CMD_DISCOVER_MODE_REQ:

            // -------- Data Obj 0 : VDM Header --------
            if((GET_TYPE_C_1_PD_DP_ALT_STATE() == _PD_ALT_MODE_SEND_DISCOVER_MODE) || (GET_TYPE_C_1_PD_DP_ALT_STATE() == _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P))
            {
                // [31:16] DP SID = 0xFF01
                g_pucTypeC1PdDataObject[0] = 0xFF;
                g_pucTypeC1PdDataObject[1] = 0x01;
            }
            else if(GET_TYPE_C_1_PD_DP_ALT_STATE() == _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P)
            {
                // [31:16] TBT3 SID = 0x8087
                g_pucTypeC1PdDataObject[0] = 0x80;
                g_pucTypeC1PdDataObject[1] = 0x87;
            }

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos = b'000
            g_pucTypeC1PdDataObject[2] = (_BIT7);

            // For SOP Packet : If Port Partners Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            // For SOP' Packet : If Port Partners & Cable Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)) ||
               ((enumPacketType == _PD_SOP_P_PKT) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_CBL_SPEC_VER() == _PD_VERSION_3_0)))
            {
                g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                // SVDM Version = 2.1 Only when Port Partner or Cable Support 2.1 or Higher
                if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)) ||
                   ((enumPacketType == _PD_SOP_P_PKT) && (GET_TYPE_C_1_PD_CBL_SVDM_VERSION() >= _PD_SVDM_VER_2_1)))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Discover Mode Request (0x03)
            g_pucTypeC1PdDataObject[3] = enumVdmCmd;

            break;

        case _PD_VDM_CMD_ENTER_MODE_REQ:
        case _PD_VDM_CMD_EXIT_MODE_REQ:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucTypeC1PdDataObject[0] = 0xFF;
            g_pucTypeC1PdDataObject[1] = 0x01;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos = b'001-111
            g_pucTypeC1PdDataObject[2] = (_BIT7) | (GET_TYPE_C_1_PD_DP_OBJ_POS());

            // For SOP Packet : If Port Partners Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            // For SOP' / SOP" Packet : If Port Partners & Cable Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)) ||
               (((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT)) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_CBL_SPEC_VER() == _PD_VERSION_3_0)))
            {
                g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                // SVDM Version = 2.1 Only when Port Partner or Cable Support 2.1 or Higher
                if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)) ||
                   (((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT)) && (GET_TYPE_C_1_PD_CBL_SVDM_VERSION() >= _PD_SVDM_VER_2_1)))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Enter / Exit Mode Request (0x04 / 0x05)
            g_pucTypeC1PdDataObject[3] = enumVdmCmd;

            break;

        // If SVID = _DP_SID, CMD_10 = DP_Status REQ
        case _PD_VDM_CMD_10:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucTypeC1PdDataObject[0] = 0xFF;
            g_pucTypeC1PdDataObject[1] = 0x01;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
            g_pucTypeC1PdDataObject[2] = (_BIT7) | (GET_TYPE_C_1_PD_DP_OBJ_POS());

            // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = DP Status Req (0x10)
            g_pucTypeC1PdDataObject[3] = enumVdmCmd;

            // -------- Data Obj 1 : DP Status ---------
            // [31:16] Reserved = 0x00
            g_pucTypeC1PdDataObject[4] = 0x00;
            g_pucTypeC1PdDataObject[5] = 0x00;

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
            // [15:9] Reserved, [8] HPD IRQ, [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No
            // [4] Multi-Func = No, [3] DP En = No, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
            g_pucTypeC1PdDataObject[6] = 0x00;
            g_pucTypeC1PdDataObject[7] = 0x02;

            if(GET_TYPE_C_1_PD_FORCE_HPD_IRQ() == _TRUE)
            {
                // HPD = IRQ, HPD_High = 1
                g_pucTypeC1PdDataObject[7] = (g_pucTypeC1PdDataObject[7]) | (_BIT7);

                // HPD IRQ = 1
                g_pucTypeC1PdDataObject[6] = _BIT0;

                DebugMessageTypeC("8. [PD] Force HPD IRQ : ", 1);
            }
            else
            {
                if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) == _PD_HPD_LOW)
                {
                    DebugMessageTypeC("8. [PD] HPD LOW : ", 0);
                }
                else
                {
                    // HPD = HIGH or IRQ, HPD_High = 1
                    g_pucTypeC1PdDataObject[7] = (g_pucTypeC1PdDataObject[7]) | (_BIT7);

                    if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) == _PD_HPD_HIGH)
                    {
                        DebugMessageTypeC("8. [PD] HPD HIGH : ", 1);
                    }
                    else
                    {
                        g_pucTypeC1PdDataObject[6] = _BIT0;

                        DebugMessageTypeC("8. [PD] HPD IRQ : ", 1);
                    }
                }
            }

            if(GET_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
            {
                g_pucTypeC1PdDataObject[7] = g_pucTypeC1PdDataObject[7] | (_BIT6);
            }

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
            // [15:2] Reserved, [1:0] Connected DP Role : DP_TX(b'01)
            g_pucTypeC1PdDataObject[6] = 0x00;
            g_pucTypeC1PdDataObject[7] = 0x01;
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)

            break;

        // If SVID = _DP_SID, CMD_11 = DP_Config REQ
        case _PD_VDM_CMD_11:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] DP SID = 0xFF01
            g_pucTypeC1PdDataObject[0] = 0xFF;
            g_pucTypeC1PdDataObject[1] = 0x01;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
            g_pucTypeC1PdDataObject[2] = (_BIT7) | (GET_TYPE_C_1_PD_DP_OBJ_POS());

            // For SOP Packet : If Port Partners Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            // For SOP' / SOP" Packet : If Port Partners & Cable Support PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)) ||
               (((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT)) && (GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_CBL_SPEC_VER() == _PD_VERSION_3_0)))
            {
                g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                // SVDM Version = 2.1 Only when Port Partner or Cable Support 2.1 or Higher
                if(((enumPacketType == _PD_SOP_PKT) && (GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)) ||
                   (((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT)) && (GET_TYPE_C_1_PD_CBL_SVDM_VERSION() >= _PD_SVDM_VER_2_1)))
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = DP Config Req (0x11)
            g_pucTypeC1PdDataObject[3] = enumVdmCmd;

            // -------- Data Obj 1 : DP Configurations ---------
            if(enumPacketType == _PD_SOP_PKT)
            {
                // DPAM v2.1: [31:30] Get From Discover Mode Ack(SOP), [29:26] Get From Discover Mode Ack(SOP'/SOP'')
                // DPAM v2.1: [31:30] VDO Version , [29:28] Cable Active Component, [27] Rsv, [26] Cable UHBR13.5 Support, [25:24] Rsv; Not DPAM v2.1: [31:24] = 0x00
                if(GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER)
                {
                    g_pucTypeC1PdDataObject[4] = ((GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() << 6) | (GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT() << 4) | (GET_TYPE_C_1_PD_CBL_UHBR13P5_SUPPORT() << 2));
                }
                else
                {
                    // if Partner VDO Version = 0, Set [31:30] VDO Version = Original Version(00), [29:28] Cable Active Component = Passive(00), [26] Cable UHBR13.5 Support = Not Support(0)
                    g_pucTypeC1PdDataObject[4] = 0x00;
                }

                // [23:16] Rsv
                g_pucTypeC1PdDataObject[5] = 0x00;

                // [15:8] Pin Assignment to be Configured
                g_pucTypeC1PdDataObject[6] = GET_TYPE_C_1_PD_PIN_ASSIGNMENT();

                if(GET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG() == _PD_DP_CONFIG)
                {
                    if(GET_TYPE_C_1_PD_PARTNER_DPAM_VERSION() >= _PD_DPAM_VER_2_1_HIGHER)
                    {
                        // DPAM v2.1: [7:6] Reserved, [5:2] Signaling for Cable : Get From Discover Mode Ack(SOP'/SOP'')
                        g_pucTypeC1PdDataObject[7] = (GET_TYPE_C_1_PD_CBL_MAX_DP_RATE() << 2);
                    }
                    else
                    {
                        // if Partner VDO Version = 0, Indicates That Port Partner Don't Support DPAM v2.1 Cable Discovery Flow, Set [5:2] Signaling for Cable = 0001
                        g_pucTypeC1PdDataObject[7] = 0x04;
                    }

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                    // [1:0] Other Side Config = DP_Tx = b'01
                    g_pucTypeC1PdDataObject[7] = (g_pucTypeC1PdDataObject[7] | 0x01);
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                    // [1:0] Other Side Config = DP_Rx = b'10
                    g_pucTypeC1PdDataObject[7] = (g_pucTypeC1PdDataObject[7] | 0x02);
#endif
                }
                else
                {
                    // [7:6] Reserved, [5:2] Signaling : Signaling unspecified = b'0000, [1:0] Other Side Config = Config USB = b'00
                    g_pucTypeC1PdDataObject[7] = 0x00;
                }
            }
            else if((enumPacketType == _PD_SOP_P_PKT) || (enumPacketType == _PD_SOP_PP_PKT))
            {
                // [15:8] Pin Assignment to be Configured
                g_pucTypeC1PdDataObject[6] = GET_TYPE_C_1_PD_PIN_ASSIGNMENT();

                if(GET_TYPE_C_1_PD_DP_ALT_MODE_TARGET_CONFIG() == _PD_DP_CONFIG)
                {
                    // DPAM v2.1: [7:6] Reserved, [5:2] Signaling for Transport = b'1 (Select DP Bit Rate)
                    g_pucTypeC1PdDataObject[7] = 0x04;

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                    // [1:0] Other Side Config = DP_Tx = b'01
                    g_pucTypeC1PdDataObject[7] = (g_pucTypeC1PdDataObject[7] | 0x01);
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                    // [1:0] Other Side Config = DP_Rx = b'10
                    g_pucTypeC1PdDataObject[7] = (g_pucTypeC1PdDataObject[7] | 0x02);
#endif
                }
                else
                {
                    // [7:6] Reserved, [5:2] Signaling : Signaling unspecified = b'0000, [1:0] Other Side Config = Config USB = b'00
                    g_pucTypeC1PdDataObject[7] = 0x00;
                }
            }

            break;

        case _PD_VDM_CMD_ATTENTION_REQ:

            // If Sub State = SEND_DP_VDM_REQ, Dp Alt Mode Attention
            if(GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SEND_DP_VDM_REQ)
            {
                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DP SID = 0xFF01
                g_pucTypeC1PdDataObject[0] = 0xFF;
                g_pucTypeC1PdDataObject[1] = 0x01;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject[2] = (_BIT7) | (GET_TYPE_C_1_PD_DP_OBJ_POS());

                // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                    // UFP Resp. SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Attention Req (0x06)
                g_pucTypeC1PdDataObject[3] = enumVdmCmd;

                // -------- Data Obj 1 : DP Status ---------
                // [31:16] Reserved = 0x00
                g_pucTypeC1PdDataObject[4] = 0x00;
                g_pucTypeC1PdDataObject[5] = 0x00;

#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
                // [15:9] Reserved, [8] HPD IRQ, [7] HPD State : HIGH/LOW, [6] Exit DP : No, [5] USB Config = No
                // [4] Multi-Func = No, [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_RX(b'10)
                g_pucTypeC1PdDataObject[6] = 0x00;
                g_pucTypeC1PdDataObject[7] = (0x0A) | (GET_TYPE_C_1_PD_MULTI_FUNCTION() << 4);

                if(GET_TYPE_C_1_PD_FORCE_HPD_IRQ() == _TRUE)
                {
                    // HPD = IRQ, HPD_High = 1
                    g_pucTypeC1PdDataObject[7] = (g_pucTypeC1PdDataObject[7]) | (_BIT7);

                    // HPD IRQ = 1
                    g_pucTypeC1PdDataObject[6] = _BIT0;

                    DebugMessageTypeC("8. [PD] Force HPD IRQ : ", 1);
                }
                else
                {
                    if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) == _PD_HPD_LOW)
                    {
                        DebugMessageTypeC("8. [PD] HPD LOW : ", 0);
                    }
                    else
                    {
                        // HPD = HIGH or IRQ, HPD_High = 1
                        g_pucTypeC1PdDataObject[7] = (g_pucTypeC1PdDataObject[7]) | (_BIT7);

                        if(GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR()) == _PD_HPD_HIGH)
                        {
                            DebugMessageTypeC("8. [PD] HPD HIGH : ", 1);
                        }
                        else
                        {
                            g_pucTypeC1PdDataObject[6] = _BIT0;

                            DebugMessageTypeC("8. [PD] HPD IRQ : ", 1);
                        }
                    }
                }

                if(GET_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
                {
                    g_pucTypeC1PdDataObject[7] = g_pucTypeC1PdDataObject[7] | (_BIT6);
                }

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
                // [15:9] Reserved, [8] HPD IRQ : No, [7] HPD State : LOW, [6] Exit DP : No, [5] USB Config = No
                // [4] Multi-Func, [3] DP En = Yes, [2] Low Power = No, [1:0] Connected DP Role : DP_TX(b'01)
                g_pucTypeC1PdDataObject[6] = 0x00;
                g_pucTypeC1PdDataObject[7] = (0x09) | (GET_TYPE_C_1_PD_MULTI_FUNCTION() << 4);

                if(GET_TYPE_C_1_PD_DP_ALT_MODE_EXIT_REQ() == _TRUE)
                {
                    g_pucTypeC1PdDataObject[7] = g_pucTypeC1PdDataObject[7] | (_BIT6);
                }
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
            }
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
            else if(GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SEND_LENOVO_VDM_REQ)
            {
                // -------- Data Obj 0 : VDM Header --------
                // [31:16] LENOVO VID = 0x17EF
                g_pucTypeC1PdDataObject[0] = 0x17;
                g_pucTypeC1PdDataObject[1] = 0xEF;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject[2] = (_BIT7) | (GET_TYPE_C_1_PD_LENOVO_OBJ_POS());

                // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                    // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Attention Req (0x06)
                g_pucTypeC1PdDataObject[3] = enumVdmCmd;
            }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
            else if(GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SEND_HP_VDM_REQ)
            {
                // HP Attention (Atten_vwire/ Atten_config/ Atten_data/ Atten_disconnect)
                // -------- Data Obj 0 : VDM Header --------
                // [31:16] HP VID = 0x03F0
                g_pucTypeC1PdDataObject[0] = 0x03;
                g_pucTypeC1PdDataObject[1] = 0xF0;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos = Attention Type
                g_pucTypeC1PdDataObject[2] = (_BIT7) | (GET_TYPE_C_1_PD_HP_ATTEN_TYPE());

                // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                    // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Attention Req (0x06)
                g_pucTypeC1PdDataObject[3] = enumVdmCmd;

                // -------- Data Obj 1 : Hp Attention Payload -----
                // [31:29] Hp Ver = 3b'011, [28:26] Atten_type, [25:24] Rsv.
                g_pucTypeC1PdDataObject[4] = (_BIT6 | _BIT5) | (GET_TYPE_C_1_PD_HP_ATTEN_TYPE() << 2);

                // [23:18] Rsv., [17:0] AM_addr
                g_pucTypeC1PdDataObject[5] = (GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_H() & (_BIT1 | _BIT0));
                g_pucTypeC1PdDataObject[6] = GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_M();
                g_pucTypeC1PdDataObject[7] = GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_L();
            }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
            else if(GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SEND_DELL_VDM_REQ)
            {
                // DELL Attention
                // -------- Data Obj 0 : VDM Header --------
                // [31:16] DELL VID = 0x413C
                g_pucTypeC1PdDataObject[0] = (BYTE)(_DELL_VID >> 8);
                g_pucTypeC1PdDataObject[1] = (BYTE)_DELL_VID;

                // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
                g_pucTypeC1PdDataObject[2] = (_BIT7) | (GET_TYPE_C_1_PD_DELL_OBJ_POS());

                // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
                if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
                {
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                    // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                    if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                    {
                        // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                        g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                    }
                }

                // [7:0] VDM CMD = Attention Req (0x06)
                g_pucTypeC1PdDataObject[3] = enumVdmCmd;

                // -------- Data Obj 1~7 : Dell Attention Payload -----
                // Fill in the Data of User Event
                for(pData[0] = 0; pData[0] < (GET_TYPE_C_1_PD_DELL_USER_VDM_CNT() * 4); pData[0]++)
                {
                    g_pucTypeC1PdDataObject[pData[0] + 4] = GET_TYPE_C_1_PD_DELL_USER_VDM_DATA(pData[0]);
                }
            }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)

            break;

        // If SVID = _LENOVO_VID, CMD_50 = GET_STATUS ACK
        case _PD_VDM_CMD_50:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] LENOVO VID = 0x17EF
            g_pucTypeC1PdDataObject[0] = 0x17;
            g_pucTypeC1PdDataObject[1] = 0xEF;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
            g_pucTypeC1PdDataObject[2] = (_BIT7);

            // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Get Status Ack (0x50)
            g_pucTypeC1PdDataObject[3] = enumVdmCmd;

            // -------- Data Obj 1 : Lenovo Get Status Response VDO1-----
            // [31:28] Rsv., [27] Docking Power Button Break, [26] Docking Power Button Make,
            // [25] Wol Request, [24] Event
            g_pucTypeC1PdDataObject[4] = GET_TYPE_C_1_PD_LENOVO_DOCK_EVENT();

            // [23:20] Rsv., [19] System Acknowledge Power Button Break, [18] System Acknowledge Power Button Make,
            // [17] Wol Request, [16] Event Acknowledge
            g_pucTypeC1PdDataObject[5] = (GET_TYPE_C_1_PD_LENOVO_SYS_ACKNOWLEDGE() & 0xFE);

            // [15:13] Rsv., [12] System Power Mode, [11:9] System State, [8] Event
            g_pucTypeC1PdDataObject[6] = GET_TYPE_C_1_PD_LENOVO_SYS_EVENT();

            // [7:5] Rsv., [4] Docking Acknowledge System Power Mode, [3:1] Docking Acknowledge System State, [0] Event Acknowledge
            g_pucTypeC1PdDataObject[7] = GET_TYPE_C_1_PD_LENOVO_SYS_EVENT();

            // -------- Data Obj 2 : Lenovo Get Status Response VDO2-----
            // [31:28] FW Ver. = 0, [27:24] Rsv.
            g_pucTypeC1PdDataObject[8] = 0x00;

            // Power Source
            // [23] Supplier Info = 0, [22:21] Src Type : Type-C Adapter, [20] Src Quality = Good, [19:16] Rating = Unknown AC adapter detected
            g_pucTypeC1PdDataObject[9] = 0x30;

            // Function Capability
            // [15] Power Button Supported, [14] Wol Supported, [13] Wol Supported,
            // [12] MAC address pass through not Supported, [11] Change charging ability not Supported, [11:8] Rsv.
            g_pucTypeC1PdDataObject[10] = 0xC0;

            // [7:0] Reserved = 0x00
            g_pucTypeC1PdDataObject[11] = 0x00;

            break;

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
        // Acer VDM Attention
        case _PD_VDM_CMD_15:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] ACER VID = 0x0502
            g_pucTypeC1PdDataObject[0] = (BYTE)(_ACER_VID >> 8);
            g_pucTypeC1PdDataObject[1] = (BYTE)_ACER_VID;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
            g_pucTypeC1PdDataObject[2] = (_BIT7);

            // If PD 3.0, VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Attention Req (0x15)
            g_pucTypeC1PdDataObject[3] = enumVdmCmd;

            break;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
        // Hp VDM Set_vwire Sample ACK
        case _PD_VDM_CMD_52:

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] HP VID = 0x03F0
            g_pucTypeC1PdDataObject[0] = 0x03;
            g_pucTypeC1PdDataObject[1] = 0xF0;

            // [15] Struct. VDM = 1, [14:11] SVDM Ver, [10:8] Obj. Pos
            g_pucTypeC1PdDataObject[2] = (_BIT7) | (_BIT0);

            // If PD 3.0, [14:13] VDM Spec Version = 2b'01 (Ver 2.0)
            if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
            {
                g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT5);

                // SVDM Version = 2.1 Only when DFP/UFP both Support 2.1 or Higher
                if(GET_TYPE_C_1_PD_PARTNER_SVDM_VERSION() >= _PD_SVDM_VER_2_1)
                {
                    // SVDM Header [14:13] Major = b'01 (2.x), [12:11] Minor = b'01 (2.1)
                    g_pucTypeC1PdDataObject[2] = g_pucTypeC1PdDataObject[2] | (_BIT3);
                }
            }

            // [7:0] VDM CMD = Set_vwire Sample ACK (0x52)
            g_pucTypeC1PdDataObject[3] = enumVdmCmd;

            // -------- Data Obj 1 : Hp Sub Header -----
            // [31:23] Rsv., [22:20] VDO_CNT
            g_pucTypeC1PdDataObject[5] = g_pucTypeC1PdDataObject[5] | ((GET_TYPE_C_1_PD_HP_USER_VDM_CNT() << 4) & (_BIT6 | _BIT5 | _BIT4));

            // [19:18] Rsv., [17:0] AM_addr
            g_pucTypeC1PdDataObject[5] = g_pucTypeC1PdDataObject[5] | (GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_H() & (_BIT1 | _BIT0));
            g_pucTypeC1PdDataObject[6] = GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_M();
            g_pucTypeC1PdDataObject[7] = GET_TYPE_C_1_PD_HP_OWN_AM_ADDR_L();

            // -------- Data Obj 2 : Hp V-wire VDO1 -----
            // [31:16] Data, [15:8] Index, [7:4] Rsv., [3:0] Operation
            for(pData[0] = 0; pData[0] < (GET_TYPE_C_1_PD_HP_USER_VDM_CNT() * 4); pData[0]++)
            {
                g_pucTypeC1PdDataObject[pData[0] + 8] = GET_TYPE_C_1_PD_HP_USER_VDM_DATA(pData[0]);
            }

            break;
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Send Soft Reset Message
// Input Value  : enumPacketType : _PD_SOP_PKT / _PD_SOP_P_PKT
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSendSoftRst(EnumTypeCPDPacketType enumPacketType)
{
    // 1. Clear Flags & Reset PRL Layer [0x6B03]
    CLR_TYPE_C_1_PD_INT_OVERWRITE();
    CLR_TYPE_C_1_PD_TRANSMIT_RESULT();
    ScalerSetBit(P6B_03_PD_TOP_RST, ~_BIT0, 0x00);

    // 2. Construct Msg.
    ScalerTypeC1PdConstructSoftReset(enumPacketType);

    // Start Disable Rcv Msg.
    ScalerTypeC1PdRxIntControl(_DISABLE);

    // 3. Enable PRL Layer & Release Message ID Reset [0x6B03/E4]
    ScalerSetBit(P6B_03_PD_TOP_RST, ~_BIT0, _BIT0);
    ScalerSetBit(P6B_E4_TX_MSG_ID_RST, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // 4. Only Send Msg. When Tx FIFO Has Not Been Overwritten by INT during Msg. Construct Flow
    if(GET_TYPE_C_1_PD_INT_OVERWRITE() == _TRUE)
    {
        // Enable Rcv Msg.
        ScalerTypeC1PdRxIntControl(_ENABLE);

        // Function Has Been Interrupted Before Sending, Set "_PD_SENT_DISCARDED" and Just Not Start Transmit.
        SET_TYPE_C_1_PD_TRANSMIT_RESULT(_PD_SENT_DISCARDED);
    }
    else
    {
        // [0x6BDC] Clear IRQs
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
        ScalerSetBit(P6B_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
        ScalerSetBit(P6B_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

        // [0x6BDD] Enable tx_prl_trans_done IRQs, When Triggered, Look into Flags to Know Success or Fail
        ScalerSetBit(P6B_DD_TX_PD_MSG_INT_EN, ~_BIT5, _BIT5);

        // [0x6BDA] Start Transmit ([1] = 1, Wait For GoodCRC Response After Transmission)
        ScalerSetBit(P6B_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), _BIT7);

        // [0x6BE5] Set Tx FIFO [2:1] Spec Ver = 2.0, For PD2.0/3.0 CTS
        ScalerSetBit(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (_BIT1));
    }
}

//--------------------------------------------------
// Description  : Construct Soft Reset Msg.
// Input Value  : enumPacketType : _PD_SOP_PKT / _PD_SOP_P_PKT
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdConstructSoftReset(EnumTypeCPDPacketType enumPacketType)
{
    // Disable Rcv Msg. INT
    ScalerTypeC1PdRxIntControl(_DISABLE);

    // Start to Fill Packet Type, Msg. Header
    if(ScalerGetBit(P6B_DA_TX_TRANSMIT_CTRL, _BIT7) == 0x00)
    {   // Do Not Write Tx FIFO When Tx is Transmitting During INT

        // 1. [0x6BE0] Set Transmit Type : b'00 = Preamble + SOP + Msg. Header + Data + CRC + EOP
        ScalerSetBit(P6B_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), 0x00);

        // 2. [0x6BE0] Set Packet Type [5:3]
        ScalerSetBit(P6B_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), ((enumPacketType << 3) & (_BIT5 | _BIT4 | _BIT3)));

        // 3. [0x6BE5] Fill in Msg. Header0
        // [7]   Msg. Header[15]     : Extended Field = 0
        // [6:4] Msg. Header[14:12]  : Number of Data Object = 0
        ScalerSetBit(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // [3]   Msg. Header[8]  : Power Role
        // [0]   Msg. Header[5]  : Data Role
        if(enumPacketType == _PD_SOP_PKT)
        {
            // [3] Power Role / [2:1] Spec Version / [0] Data Role
            ScalerSetBit(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, (GET_TYPE_C_1_PD_POWER_ROLE() << 3));
            ScalerSetBit(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (GET_TYPE_C_1_PD_SPEC_VER() << 1));
            ScalerSetBit(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, GET_TYPE_C_1_PD_DATA_ROLE());

            // Reset Message ID [0x6BE4]
            ScalerSetBit(P6B_E4_TX_MSG_ID_RST, ~_BIT2, 0x00);
        }
        else
        {
            ScalerSetBit(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT3, ((BYTE)_PD_DEVICE << 3));
            ScalerSetBit(P6B_E5_TX_FIFO_MSG_HEADER0, ~(_BIT2 | _BIT1), (GET_TYPE_C_1_PD_CBL_SPEC_VER() << 1));
            ScalerSetBit(P6B_E5_TX_FIFO_MSG_HEADER0, ~_BIT0, 0x00);

            if(enumPacketType == _PD_SOP_P_PKT)
            {
                // Reset Message ID [0x6BE4]
                ScalerSetBit(P6B_E4_TX_MSG_ID_RST, ~_BIT1, 0x00);
            }
            else if(enumPacketType == _PD_SOP_PP_PKT)
            {
                // Reset Message ID [0x6BE4]
                ScalerSetBit(P6B_E4_TX_MSG_ID_RST, ~_BIT0, 0x00);
            }
        }

        // [0x6BE6] Fill in Msg. Header1
        // [4:0]  Msg. Header[4:0]    : Command Type = b'0_1101
        ScalerSetBit(P6B_E6_TX_FIFO_MSG_HEADER1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
    }

    // Enable Rcv Msg. INT
    ScalerTypeC1PdRxIntControl(_ENABLE);
}

//--------------------------------------------------
// Description  : Initiate Hard Reset When Error Happens
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSendHardRst(void)
{
    BYTE ucHardRstWaitPhyIdleCnt = 0;

    if(GET_TYPE_C_1_PD_HARD_RST_CNT() <= _MAX_HARD_RST_CNT)
    {
        // Polling 200us * 10 to Wait ScalerTypeC1PdSendMsg Transmitted (No Concern About CRCReceive Timer)
        while((ucHardRstWaitPhyIdleCnt < 10) && (ScalerGetBit(P6B_05_PD_PHY_IDLE_INT, _BIT2) == 0x00))
        {
            ucHardRstWaitPhyIdleCnt += 1;
            DELAY_XUS(200);
        }

        // 1. Disable Rcv Msg. INT to Prevent Overwriting TX FIFO
        ScalerTypeC1PdRxIntControl(_DISABLE);

        // 2. [0x6BE0] Select Transmission Mode [7:6] : b'01 = Preamble + SOP
        ScalerSetBit(P6B_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), _BIT6);

        // 3. [0x6BE0] Set Packet Type [5:3] : b'011 = HARD_RESET
        ScalerSetBit(P6B_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

        // 4. [0x6BDC] Clear IRQs
#if(_HW_PD_FUNCTION_GEN >= _PD_FUNCTION_GEN_2)
        ScalerSetBit(P6B_DC_TX_PD_MSG_INT, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
        ScalerSetBit(P6B_DC_TX_PD_MSG_INT, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
#endif

        // 5. [0x6BDA] Start Transmit ([1] : Do Not Wait For GoodCRC)
        ScalerSetBit(P6B_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));
        ADD_TYPE_C_1_PD_HARD_RST_CNT();

        // 6. Process Hard Reset
        ScalerTypeC1PdProcHardRst();
    }
    else
    {
        // Do Type-C Error Recovery
        SET_TYPE_C_1_CC_ERROR_RECOVERY();
    }
}

//--------------------------------------------------
// Description  : Process Hard Reset When Hard Reset Sent/Rcv.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdProcHardRst(void)
{
    // Clear Hard Reset Turn Off Power Flag (Set When 1.Power Already Turned Off to vSafe0v for SRC 2.Vbus Already Not vSafe5v)
    CLR_TYPE_C_1_PD_HRST_PWR_OFF();

    if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
    {
#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
        // Turn Off Vbus Power
        ScalerTypeC1PmicSetting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
        // Enable Vbus Discharge
        ScalerTypeC1PmicVbusDischarge(_ON);
#endif

        // [Eizo] SIC437A Customized Power Control : Send Hard Reset
        ScalerTypeC1PmicSic437aHardRstStartProc(_TYPE_C_POWER_SRC);

#if(_EMB_TYPE_C_1_UNATTACH_HW_FORCE_VBUS_OFF == _OFF)
        // Tool Not Show Warning UI when We Turn Off Vbus
        ScalerTypeC1CcToolWarningUIControl(_DISABLE);
#endif
#else
        // TD.PD.SRC.E6 : Source can Start Changing Power After tSrcTransition = 25-35 ms
        ScalerTimerActiveTimerEvent(_SRC_ADJUST_POWER_TIMER, _SCALER_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER);
#endif
    }
    else
    {
#if(_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)
        // 1. Turn Off Power Draw, Vbus should be drive to vSafe0V by Source (PD 7.1.5). Disable Detect Sink OVP/UVP
        ScalerTypeC1PmicSetting(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0, _PD_PEAK_CUR_NONE);
#endif

#if((_HW_TYPE_C_LS_ADC_HW_VERSION == _TYPE_C_5B_LS_ADC_GEN_1) && ((_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL >= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_0) && (_EMB_TYPE_C_1_PMIC_VBUS_ADC_CHANNEL <= _TYPE_C_PMIC_ADC_MAPPING_LS_ADC_3)))
        // [FW Sol. for _TYPE_C_5B_LS_ADC_GEN_1] Write 1 Clear 5Bit LS_ADC Vbus Off IRQ and Disable IRQ_EN
        ScalerTypeCAdcOnOffCompIntControl(_TYPE_C_CHANNEL_1_VMON, _OFF, _DISABLE);
#else
        // 2. Turn Off Type-C Unattach Vbus Detection
        ScalerTypeC1CcVbusDetCtrl(_DISABLE);

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
        // [Eizo] SIC437A Customized Power Control : Send Hard Reset
        ScalerTypeC1PmicSic437aHardRstStartProc(_TYPE_C_POWER_SNK);
#endif
#endif

        ScalerTimerActiveTimerEvent(_SNK_HARD_RST_TIMER, _SCALER_TIMER_EVENT_PD_1_SNK_HARD_RST_TIMEOUT);
    }

    // Turn Off Vconn, If Already Turned On
    if(GET_TYPE_C_1_PD_VCONN_ROLE() == _PD_VCONN_SRC)
    {
        ScalerTypeC1CcVconnControl(_OFF);
    }

    // [0x6B02] Disable PHY Layer BMC Tx/Rx
    ScalerSetBit(P6B_02_PD_BMC_ENABLE, ~(_BIT2 | _BIT1), 0x00);

    // [0x6B43] Clear and Disable Hard Reset IRQ
    ScalerSetBit(P6B_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT3);

    SET_TYPE_C_1_PD_FW_STATE(_PD_HARDRESET);
    SET_TYPE_C_1_PD_SUB_STATE(_PD_SUB_STATE_NONE);
    SET_TYPE_C_1_PD_AMS_STATUS(_PD_AMS_NONE);
    SET_TYPE_C_1_PD_CBL_STATE(_PD_CBL_STATE_NONE);
}

//--------------------------------------------------
// Description  : Initiate Hard Reset When Error Happens
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSendCableRst(void)
{
    // 1. Clear Flags
    CLR_TYPE_C_1_PD_INT_OVERWRITE();
    CLR_TYPE_C_1_PD_TRANSMIT_RESULT();

    // 2. Disable Rcv Msg. INT to Prevent Overwriting TX FIFO
    ScalerTypeC1PdRxIntControl(_DISABLE);

    // 3. Only Send Msg. When Tx FIFO Has Not Been Overwritten by INT
    if(GET_TYPE_C_1_PD_INT_OVERWRITE() == _TRUE)
    {
        // Enable Rcv Msg.
        ScalerTypeC1PdRxIntControl(_ENABLE);

        // Function Has Been Interrupted Before Sending, Set "_PD_SENT_DISCARDED" and Just Not Start Transmit.
        SET_TYPE_C_1_PD_TRANSMIT_RESULT(_PD_SENT_DISCARDED);
    }
    else
    {
        // Start to Fill Packet Type
        if(ScalerGetBit(P6B_DA_TX_TRANSMIT_CTRL, _BIT7) == 0x00)
        {   // Do Not Write Tx FIFO When Tx is Transmitting During INT

            // 1. [0x6BE0] Select Transmission Mode [7:6] : b'01 = Preamble + SOP
            ScalerSetBit(P6B_E0_TX_PACKET_CFG, ~(_BIT7 | _BIT6), _BIT6);

            // 2. [0x6BE0] Set Packet Type [5:3] : b'100 = CBL_RESET
            ScalerSetBit(P6B_E0_TX_PACKET_CFG, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);

            // 3. [0x6BDA] Start Transmit ([1] : Do Not Wait For GoodCRC)
            ScalerSetBit(P6B_DA_TX_TRANSMIT_CTRL, ~(_BIT7 | _BIT1), (_BIT7 | _BIT1));
        }
    }
}

//--------------------------------------------------
// Description  : Set Default Src/Snk Cap
// Input Value  : enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetPdoByKernel(EnumTypeCPowerRole enumPowerRole)
{
    // ------------------------- NOTE -------------------------
    // * Fix Supply PDO Please Use "ScalerTypeC1PdSetFixPdo"
    // * Argumented PDO (PPS) Please Use "ScalerTypeC1PdSetArgumentedPdo"
    // * 1st PDO Must Be "FIX SUPPLY" With Voltage 5V
    // * According to PD Spec : Max Voltage = 20V, Max Current = 5A
    // * If Set Current > 3A, and FW Cannot Get Cable 5A Cap, Current Will Be Auto Reduce to 3A
    // * For More Info, Ref to PD Spec 10.2
    // --------------------------------------------------------

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Set Type-C PDP (PD Power)[Unit = 0.1 W], PDO Power Cannot > PDP
        SET_TYPE_C_1_MAX_POWER(270);

        // Set Total Number of SPR PDO
        SET_TYPE_C_1_PD_SPR_SRC_PDO_CNT(2);

        // Set Total Number of EPR PDO
        SET_TYPE_C_1_PD_EPR_SRC_PDO_CNT(0);

        // ----------------------- 1st PDO ------------------------
        // Index = 1 (1st PDO Must Be "FIX SUPPLY" With Voltage 5V)
        // PDO Type = Fix Supply PDO
        // Peak Current Only for Source Fix Supply PDO
        // Max/Min Voltage (Unit = 100mV) : 50 * 100mV = 5V
        // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
        // --------------------------------------------------------
        ScalerTypeC1PdSetFixPdo(_TYPE_C_POWER_SRC, 1, 50, 300, _PD_PEAK_CUR_NONE);

        // ----------------------- 2nd PDO ------------------------
        // Index = 2
        // PDO Type = Fix Supply PDO (Max = 20V / 5A)
        // Peak Current Only for Source Fix Supply PDO
        // Max/Min Voltage (Unit = 100mV) : 90 * 100mV = 9V
        // Max Current (Unit = 10mA)  : 300 *  10mA = 3A
        // --------------------------------------------------------
        ScalerTypeC1PdSetFixPdo(_TYPE_C_POWER_SRC, 2, 90, 300, _PD_PEAK_CUR_NONE);

#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
        SET_TYPE_C_1_PD_SPR_SRC_PDO_CNT(GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT() + 1);

        // ----------------------- 3rd PDO ------------------------
        // Index = 3
        // PDO Type = Programmable PDO (5V PPS PDO = 3.3V ~ 5.9V / 9V PPS PDO = 3.3V ~ 11V)
        // Max Voltage (Unit = 100mV) : 33 * 100mV = 3.3V
        // Min Voltage (Unit = 100mV) : 59 * 100mV = 5.9V
        // Max Current (Unit = 50mA)  : 60 *  50mA = 3A
        // --------------------------------------------------------
        ScalerTypeC1PdSetArgumentedPdo(_TYPE_C_POWER_SRC, 3, 33, 59, 60);
#endif
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Set Type-C Sink PDP [Unit = 0.1 W]
        SET_TYPE_C_1_PD_SNK_MIN_PDP(25);
        SET_TYPE_C_1_PD_SNK_OPERATIONAL_PDP(25);
        SET_TYPE_C_1_PD_SNK_MAX_PDP(25);

        // Kernel Default Use 1 Sink PDO
        SET_TYPE_C_1_PD_SPR_SNK_PDO_CNT(1);

        // Set Total Number of EPR PDO
        SET_TYPE_C_1_PD_EPR_SNK_PDO_CNT(0);

        // --------------------- 1st Sink PDO ---------------------
        // Index = 1 (1st PDO Must Be "FIX SUPPLY" With Voltage 5V)
        // PDO Type = Fix Supply PDO
        // Peak Current Only for Source Fix Supply PDO
        // Max/Min Voltage (Unit = 100mV) : 50 * 100mV = 5V
        // Max Current (Unit = 10mA)  : 50 *  10mA = 500mA
        // --------------------------------------------------------
        ScalerTypeC1PdSetFixPdo(_TYPE_C_POWER_SNK, 1, 50, 50, _PD_PEAK_CUR_NONE);

#if(_TYPE_C_POWER_SOURCE == _TYPE_C_VBUS_POWER_ONLY)
        // [MM1AE-3035] For Lecroy TEST.PD.PS.SNK.01 Issue, Vbus Powered Sink Must Set At Least 2 Sink PDOs
        SET_TYPE_C_1_PD_SPR_SNK_PDO_CNT(GET_TYPE_C_1_PD_SPR_SNK_PDO_CNT() + 1);

        // --------------------- 2nd Sink PDO ---------------------
        // Index = 2
        // PDO Type = Fix Supply PDO
        // Peak Current Only for Source Fix Supply PDO
        // Max/Min Voltage (Unit = 100mV) : 51 * 100mV = 5.1V
        // Max Current (Unit = 10mA)  : 50 *  10mA = 500mA
        // --------------------------------------------------------
        ScalerTypeC1PdSetFixPdo(_TYPE_C_POWER_SNK, 2, 51, 50, _PD_PEAK_CUR_NONE);
#endif
    }
}

//--------------------------------------------------
// Description  : Set TypeC 1 Source Max Supply Power
// Input Value  : usMaxPower in 0.1W
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetMaxPower(WORD usMaxPower)
{
#if(_EMB_TYPE_C_1_PD3_1_EPR_SUPPORT == _ON)
    if(usMaxPower <= 2400)
    {
        SET_TYPE_C_1_MAX_POWER(usMaxPower);
    }
    else
    {
        SET_TYPE_C_1_MAX_POWER(2400);
        DebugMessageTypeC("8. [TYPE C] ==========X Max Power > 240W, Clamp to 240W", usMaxPower);
    }
#else
    if(usMaxPower <= 1000)
    {
        SET_TYPE_C_1_MAX_POWER(usMaxPower);
    }
    else
    {
        SET_TYPE_C_1_MAX_POWER(1000);
        DebugMessageTypeC("8. [TYPE C] ==========X Max Power > 100W, Clamp to 100W", usMaxPower);
    }
#endif
}

//--------------------------------------------------
// Description  : Set TypeC 1 Sink Information
// Input Value  : stTypeCSnkInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetSnkInfo(StructTypeCSnkInfo stTypeCSnkInfo)
{
    if(stTypeCSnkInfo.usSnkMinPDP <= 1000)
    {
        SET_TYPE_C_1_PD_SNK_MIN_PDP(stTypeCSnkInfo.usSnkMinPDP);
    }
    else
    {
        SET_TYPE_C_1_PD_SNK_MIN_PDP(1000);
        DebugMessageTypeC("8. [TYPE C] ==========X Sink Min PDP > 100W, Clamp to 100W", stTypeCSnkInfo.usSnkMinPDP);
    }

    if(stTypeCSnkInfo.usSnkOpePDP <= 1000)
    {
        SET_TYPE_C_1_PD_SNK_OPERATIONAL_PDP(stTypeCSnkInfo.usSnkOpePDP);
    }
    else
    {
        SET_TYPE_C_1_PD_SNK_OPERATIONAL_PDP(1000);
        DebugMessageTypeC("8. [TYPE C] ==========X Sink Operational PDP > 100W, Clamp to 100W", stTypeCSnkInfo.usSnkOpePDP);
    }

    if(stTypeCSnkInfo.usSnkMaxPDP <= 1000)
    {
        SET_TYPE_C_1_PD_SNK_MAX_PDP(stTypeCSnkInfo.usSnkMaxPDP);
    }
    else
    {
        SET_TYPE_C_1_PD_SNK_MAX_PDP(1000);
        DebugMessageTypeC("8. [TYPE C] ==========X Sink Max PDP > 100W, Clamp to 100W", stTypeCSnkInfo.usSnkMaxPDP);
    }
}

//--------------------------------------------------
// Description  : Set TypeC 1 Status Event
// Input Value  : stTypeCStatusEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetStatusEvent(StructTypeCStatusEvent stTypeCStatusEvent)
{
    SET_TYPE_C_1_PD_NEW_POWER_STATE(stTypeCStatusEvent.b3NewPowerState);
    SET_TYPE_C_1_PD_NEW_POWER_INDICATOR(stTypeCStatusEvent.b3NewPSIndicator);
}

//--------------------------------------------------
// Description  : Set TypeC 1 Alert Event
// Input Value  : stTypeCAlertEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetAlertEvent(StructTypeCAlertEvent stTypeCAlertEvent)
{
    SET_TYPE_C_1_PD_TYPE_OF_ALERT(stTypeCAlertEvent.enumTypeOfAlert);
    SET_TYPE_C_1_PD_BAT_STATUS(stTypeCAlertEvent.enumBatStatus);
    SET_TYPE_C_1_PD_EXT_ALERT_EVENT(stTypeCAlertEvent.enumExtAlertEvent);
}

//--------------------------------------------------
// Description  : Set TypeC 1 Number of SPR Src/Snk Capability want to Provide
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
//                ucPdoCnt : Number of SPR Src/Snk Capability
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetSPRPdoCnt(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt)
{
    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        SET_TYPE_C_1_PD_SPR_SRC_PDO_CNT(ucPdoCnt);
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        SET_TYPE_C_1_PD_SPR_SNK_PDO_CNT(ucPdoCnt);
    }
}

//--------------------------------------------------
// Description  : Get TypeC 1 Number of SPR Src/Snk Capability want to Provide
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : ucPdoCnt : Number of SPR Src/Snk Capability
//--------------------------------------------------
BYTE ScalerTypeC1PdGetSPRPdoCnt(EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCnt = 0x00;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        ucPdoCnt = GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT();
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        ucPdoCnt = GET_TYPE_C_1_PD_SPR_SNK_PDO_CNT();
    }

    return ucPdoCnt;
}

#if(_EMB_TYPE_C_1_PD3_1_EPR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set TypeC 1 Number of EPR Src/Snk Capability want to Provide
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
//                ucPdoCnt : Number of EPR Src/Snk Capability
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetEPRPdoCnt(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoCnt)
{
    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        SET_TYPE_C_1_PD_EPR_SRC_PDO_CNT(ucPdoCnt);
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        SET_TYPE_C_1_PD_EPR_SNK_PDO_CNT(ucPdoCnt);
    }
}

//--------------------------------------------------
// Description  : Get TypeC 1 Number of EPR Src/Snk Capability want to Provide
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : ucPdoCnt : Number of EPR Src/Snk Capability
//--------------------------------------------------
BYTE ScalerTypeC1PdGetEPRPdoCnt(EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCnt = 0x00;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        ucPdoCnt = GET_TYPE_C_1_PD_EPR_SRC_PDO_CNT();
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        ucPdoCnt = GET_TYPE_C_1_PD_EPR_SNK_PDO_CNT();
    }

    return ucPdoCnt;
}
#endif

//--------------------------------------------------
// Description  : Get TypeC 1 Src/Snk Capability Info want to Provide
// Input Value  : enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeC1PdGetPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= 11))
        {
            stTypeCPdo.enumPdoType = GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucPdoIndex - 1);

            if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucPdoIndex - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCPdo.enumPeakCurrent = (EnumTypeCPDPeakCurType)GET_TYPE_C_1_PD_SRC_CAP_PEAK(ucPdoIndex - 1);

                // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                stTypeCPdo.usMaxVoltage = (GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucPdoIndex - 1) / 10);
                stTypeCPdo.usMinVoltage = (GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(ucPdoIndex - 1) / 10);

                // Get Fix PDO Current in Macro (Unit = 10mA)
                stTypeCPdo.usMaxCurrent = GET_TYPE_C_1_PD_SRC_CAP_CUR(ucPdoIndex - 1);
            }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
            else if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucPdoIndex - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                stTypeCPdo.usMaxVoltage = (GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucPdoIndex - 1) / 10);
                stTypeCPdo.usMinVoltage = (GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(ucPdoIndex - 1) / 10);

                // Get Programmable PDO Current in Macro (Unit = 50mA), and Convert to 10mA
                stTypeCPdo.usMaxCurrent = (GET_TYPE_C_1_PD_SRC_CAP_CUR(ucPdoIndex - 1) * 5);
            }
#endif  // End of #if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
            else if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(ucPdoIndex - 1) == _PD_3_1_ADJUSTABLE_PDO)
            {
                // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                stTypeCPdo.usMaxVoltage = (GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(ucPdoIndex - 1) / 10);
                stTypeCPdo.usMinVoltage = (GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(ucPdoIndex - 1) / 10);
            }
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= GET_TYPE_C_1_PD_SPR_SNK_PDO_CNT()))
        {
            stTypeCPdo.enumPdoType = GET_TYPE_C_1_PD_SNK_PDO_TYPE(ucPdoIndex - 1);

            if(GET_TYPE_C_1_PD_SNK_PDO_TYPE(ucPdoIndex - 1) == _PD_FIX_SUPPLY_PDO)
            {
                // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                stTypeCPdo.usMaxVoltage = (GET_TYPE_C_1_PD_SNK_CAP_VOL_MAX(ucPdoIndex - 1) / 10);
                stTypeCPdo.usMinVoltage = (GET_TYPE_C_1_PD_SNK_CAP_VOL_MIN(ucPdoIndex - 1) / 10);

                // Get Fix PDO Current in Macro (Unit = 10mA)
                stTypeCPdo.usMaxCurrent = GET_TYPE_C_1_PD_SNK_CAP_CUR(ucPdoIndex - 1);
            }
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
            else if(GET_TYPE_C_1_PD_SNK_PDO_TYPE(ucPdoIndex - 1) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                stTypeCPdo.usMaxVoltage = (GET_TYPE_C_1_PD_SNK_CAP_VOL_MAX(ucPdoIndex - 1) / 10);
                stTypeCPdo.usMinVoltage = (GET_TYPE_C_1_PD_SNK_CAP_VOL_MIN(ucPdoIndex - 1) / 10);

                // Get Programmable PDO Current in Macro (Unit = 50mA), and Convert to 10mA
                stTypeCPdo.usMaxCurrent = (GET_TYPE_C_1_PD_SNK_CAP_CUR(ucPdoIndex - 1) * 5);
            }
#endif  // End of #if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
        }
    }

    return stTypeCPdo;
}

//--------------------------------------------------
// Description  : Get TypeC 1 Number of Src/Snk Capability from Port Partner
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : ucPdoCnt : Number of Src/Snk Capability
//--------------------------------------------------
BYTE ScalerTypeC1PdGetPartnerPdoCnt(EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPartnerPdoCnt = 0x00;

    if((enumPowerRole == _TYPE_C_POWER_SRC) && (GET_TYPE_C_1_PD_RCV_SRC_CAP() == _TRUE))
    {
        ucPartnerPdoCnt = GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT();
    }
    else if((enumPowerRole == _TYPE_C_POWER_SNK) && (GET_TYPE_C_1_PD_RCV_SNK_CAP() == _TRUE))
    {
        ucPartnerPdoCnt = GET_TYPE_C_1_PD_PARTNER_SNK_CAP_CNT();
    }

    return ucPartnerPdoCnt;
}

//--------------------------------------------------
// Description  : Get TypeC 1 Src/Snk Capability Info from Port Partner
// Input Value  : enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeC1PdGetPartnerPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPartnerPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    if((enumPowerRole == _TYPE_C_POWER_SRC) && (GET_TYPE_C_1_PD_RCV_SRC_CAP() == _TRUE))
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT()))
        {
            stTypeCPartnerPdo.enumPdoType = GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucPdoIndex - 1);

            if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(ucPdoIndex - 1) == _PD_FIX_SUPPLY_PDO)
            {
                stTypeCPartnerPdo.enumPeakCurrent = (EnumTypeCPDPeakCurType)GET_TYPE_C_1_PD_PARTNER_SRC_PEAK_CUR(ucPdoIndex - 1);
            }

            // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
            stTypeCPartnerPdo.usMaxVoltage = (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(ucPdoIndex - 1) / 10);
            stTypeCPartnerPdo.usMinVoltage = (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(ucPdoIndex - 1) / 10);

            // Get Current in Macro (Unit = 10mA)
            stTypeCPartnerPdo.usMaxCurrent = GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(ucPdoIndex - 1);
        }
    }
    else if((enumPowerRole == _TYPE_C_POWER_SNK) && (GET_TYPE_C_1_PD_RCV_SNK_CAP() == _TRUE))
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= GET_TYPE_C_1_PD_PARTNER_SNK_CAP_CNT()))
        {
            stTypeCPartnerPdo.enumPdoType = GET_TYPE_C_1_PD_PARTNER_SNK_CAP_TYPE(ucPdoIndex - 1);

            // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
            stTypeCPartnerPdo.usMaxVoltage = (GET_TYPE_C_1_PD_PARTNER_SNK_CAP_VOL_MAX(ucPdoIndex - 1) / 10);
            stTypeCPartnerPdo.usMinVoltage = (GET_TYPE_C_1_PD_PARTNER_SNK_CAP_VOL_MIN(ucPdoIndex - 1) / 10);

            // Get Current in Macro (Unit = 10mA)
            stTypeCPartnerPdo.usMaxCurrent = GET_TYPE_C_1_PD_PARTNER_SNK_CAP_CUR(ucPdoIndex - 1);
        }
    }

    return stTypeCPartnerPdo;
}

//--------------------------------------------------
// Description  : Get TypeC 1 Status Info from Port Partner
// Input Value  : None
// Output Value : StructTypeCStatusEvent
//--------------------------------------------------
StructTypeCStatusEvent ScalerTypeC1PdGetPartnerStatusInfo(void)
{
    StructTypeCStatusEvent stTypeCPartnerStatusEvent = {0x00, 0x00};

    stTypeCPartnerStatusEvent.b3NewPowerState = GET_TYPE_C_1_PD_PARTNER_NEW_POWER_STATE();
    stTypeCPartnerStatusEvent.b3NewPSIndicator = GET_TYPE_C_1_PD_PARTNER_NEW_POWER_INDICATOR();

    return stTypeCPartnerStatusEvent;
}

//--------------------------------------------------
// Description  : Get TypeC 1 Alert Info from Port Partner
// Input Value  : None
// Output Value : StructTypeCAlertEvent
//--------------------------------------------------
StructTypeCAlertEvent ScalerTypeC1PdGetPartnerAlertInfo(void)
{
    StructTypeCAlertEvent stTypeCPartnerAlertEvent = {_TYPE_C_TYPE_OF_ALERT_NONE, _TYPE_C_BAT_NONE, _TYPE_C_EXT_ALERT_EVENT_NONE};

    stTypeCPartnerAlertEvent.enumTypeOfAlert = GET_TYPE_C_1_PD_PARTNER_TYPE_OF_ALERT();
    stTypeCPartnerAlertEvent.enumBatStatus = GET_TYPE_C_1_PD_PARTNER_BAT_STATUS();
    stTypeCPartnerAlertEvent.enumExtAlertEvent = GET_TYPE_C_1_PD_PARTNER_EXT_ALERT_EVENT();

    return stTypeCPartnerAlertEvent;
}

//--------------------------------------------------
// Description  : Get Type-C 1 PDO Info
// Input Value  : enumTypeCPcbPort, *pusVoltage (Unit: 10mV), *pusCurrent (Unit: 10mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdGetPdoStatus(EnumTypeCPcbPort enumTypeCPcbPort, WORD *pusVoltage, WORD *pusCurrent)
{
    // Check Power Role & Power
    if(ScalerTypeCGetCcAttach(enumTypeCPcbPort) == _TYPE_C_ATTACH)
    {
        if(GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() == _TRUE)
        {
            // CC Attached, PD Power Contract Established : Negotiated Voltage & Current
            *pusVoltage = GET_TYPE_C_1_PD_PDO_STATUS_VOL();

            *pusCurrent = GET_TYPE_C_1_PD_PDO_STATUS_CUR();
        }
        else
        {
            // CC Attached, No PD Power Contract : 5V / Current According to Rp Value
            // Voltage = 10mV * 500 = 5V
            *pusVoltage = 500;

            if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
            {
                *pusCurrent = GET_TYPE_C_1_CC_DEF_CUR();
            }
            else
            {
                if(ScalerTypeC1CcDetResistor() == _TYPE_C_DET_RP_3P0A)
                {
                    // Sink Detect Rp-3.0A, Set Current to 3.0A
                    *pusCurrent = 300;
                }
                else if(ScalerTypeC1CcDetResistor() == _TYPE_C_DET_RP_1P5A)
                {
                    // Sink Detect Rp-1.5A, Set Current to 1.5A
                    *pusCurrent = 150;
                }
                else
                {
                    // Sink Detect Rp-Default, Set Current to 500mA
                    *pusCurrent = 50;
                }
            }
        }
    }
    else
    {
        // Set Voltage & Current to 0
        *pusVoltage = 0;
        *pusCurrent = 0;
    }
}

//--------------------------------------------------
// Description  : Get TypeC 1 Current Source PDO that Sink Request
// Input Value  : enumTypeCPcbPort
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 10mA)
//--------------------------------------------------
StructTypeCUserPDO ScalerTypeC1PdGetRequestedSrcPdo(EnumTypeCPcbPort enumTypeCPcbPort)
{
    StructTypeCUserPDO stTypeCSrcPdo = {_PD_FIX_SUPPLY_PDO, _PD_PEAK_CUR_NONE, 0x00, 0x00, 0x00};

    // Check if CC Attached and PD Power Contract Established
    if(ScalerTypeCGetCcAttach(enumTypeCPcbPort) == _TYPE_C_ATTACH)
    {
        if(GET_TYPE_C_1_PD_EXPLICIT_CONTRACT() == _TRUE)
        {
            if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
            {
                if((GET_TYPE_C_1_PD_PARTNER_OBJ_POS() > 0) && (GET_TYPE_C_1_PD_PARTNER_OBJ_POS() <= GET_TYPE_C_1_PD_SPR_SRC_PDO_CNT()))
                {
                    stTypeCSrcPdo.enumPdoType = GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1);

                    if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
                    {
                        stTypeCSrcPdo.enumPeakCurrent = (EnumTypeCPDPeakCurType)GET_TYPE_C_1_PD_SRC_CAP_PEAK(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1);

                        // Get Fix PDO Current in Macro (Unit = 10mA)
                        stTypeCSrcPdo.usMaxCurrent = GET_TYPE_C_1_PD_SRC_CAP_CUR(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1);
                    }
                    else if(GET_TYPE_C_1_PD_SRC_PDO_TYPE(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1) == _PD_3_PROGRAMMABLE_PDO)
                    {
                        // Get Programmable PDO Current in Macro (Unit = 50mA), and Convert to 10mA
                        stTypeCSrcPdo.usMaxCurrent = (GET_TYPE_C_1_PD_SRC_CAP_CUR(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1) * 5);
                    }

                    // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                    stTypeCSrcPdo.usMaxVoltage = (GET_TYPE_C_1_PD_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1) / 10);
                    stTypeCSrcPdo.usMinVoltage = (GET_TYPE_C_1_PD_SRC_CAP_VOL_MIN(GET_TYPE_C_1_PD_PARTNER_OBJ_POS() - 1) / 10);
                }
            }
            else
            {
                if((GET_TYPE_C_1_PD_REQ_OBJ_POS() > 0) && (GET_TYPE_C_1_PD_REQ_OBJ_POS() <= GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CNT()))
                {
                    stTypeCSrcPdo.enumPdoType = GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1);

                    if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
                    {
                        stTypeCSrcPdo.enumPeakCurrent = (EnumTypeCPDPeakCurType)GET_TYPE_C_1_PD_PARTNER_SRC_PEAK_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1);
                    }

                    // Get Voltage in Macro (Unit = 10mV), and Convert to 100mV
                    stTypeCSrcPdo.usMaxVoltage = (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MAX(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) / 10);
                    stTypeCSrcPdo.usMinVoltage = (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_VOL_MIN(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) / 10);

                    // Get Current in Macro (Unit = 10mA)
                    stTypeCSrcPdo.usMaxCurrent = GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CUR(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1);
                }
            }
        }
    }

    return stTypeCSrcPdo;
}

//--------------------------------------------------
// Description  : Set Src/Snk Cap Fix PDO Info
// Input Value  : enumPowerRole : _TYPE_C_POWER_SRC/SNK, ucPdoIndex : 1~7 / enumPdoType / usVoltage (100mV) / usMaxCur (10mA) / enumPeakCur
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetFixPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usVoltage, WORD usMaxCur, EnumTypeCPDPeakCurType enumPeakCur)
{
    // Convert Voltage from User 100mV to Fix PDO 10mV
    usVoltage = usVoltage * 10;

    usMaxCur = usMaxCur;

    enumPeakCur = enumPeakCur;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Check PDO Index is Valid [Max PDO Num = 11 (7 SPR PDO + 4 EPR PDO)] and PDO Power < Max Power
        if(((ucPdoIndex >= 1) && (ucPdoIndex <= 11)) && ((WORD)((DWORD)usVoltage * usMaxCur / 1000) <= GET_TYPE_C_1_MAX_POWER()))
        {
            SET_TYPE_C_1_PD_SRC_PDO_TYPE((ucPdoIndex - 1), _PD_FIX_SUPPLY_PDO);

            // Set Peak Current
            SET_TYPE_C_1_PD_SRC_CAP_PEAK((ucPdoIndex - 1), enumPeakCur);

            // -------------------- Voltage Setting --------------------
            if(ucPdoIndex <= 7)
            {
                if(usVoltage <= 2000)
                {
                    // SPR PDOs Voltage Cannot More Than 20V
                    SET_TYPE_C_1_PD_SRC_CAP_VOL_MAX((ucPdoIndex - 1), usVoltage);
                    SET_TYPE_C_1_PD_SRC_CAP_VOL_MIN((ucPdoIndex - 1), usVoltage);
                }
                else
                {
                    SET_TYPE_C_1_PD_SRC_CAP_VOL_MAX((ucPdoIndex - 1), 2000);
                    SET_TYPE_C_1_PD_SRC_CAP_VOL_MIN((ucPdoIndex - 1), 2000);
                }
            }
            else
            {
                if(usVoltage <= 4800)
                {
                    // EPR PDOs Voltage Cannot More Than 48V
                    SET_TYPE_C_1_PD_SRC_CAP_VOL_MAX((ucPdoIndex - 1), usVoltage);
                    SET_TYPE_C_1_PD_SRC_CAP_VOL_MIN((ucPdoIndex - 1), usVoltage);
                }
                else
                {
                    SET_TYPE_C_1_PD_SRC_CAP_VOL_MAX((ucPdoIndex - 1), 4800);
                    SET_TYPE_C_1_PD_SRC_CAP_VOL_MIN((ucPdoIndex - 1), 4800);
                }
            }

            // -------------------- Current Setting --------------------
            if(usMaxCur <= 500)
            {
                SET_TYPE_C_1_PD_SRC_CAP_CUR((ucPdoIndex - 1), usMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_TYPE_C_1_PD_SRC_CAP_CUR((ucPdoIndex - 1), 500);
            }
        }
        else
        {
            if((usVoltage * usMaxCur / 1000) > GET_TYPE_C_1_MAX_POWER())
            {
                DebugMessageTypeC("8. [TYPE C] ==========X Set Fix PDO Error : PDO > Max Power", ucPdoIndex);
            }
            else
            {
                DebugMessageTypeC("8. [TYPE C] ==========X Set Fix PDO Index Error", ucPdoIndex);
            }
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Set Sink Capability
        if((ucPdoIndex >= 1) && (ucPdoIndex <= 7))
        {
            SET_TYPE_C_1_PD_SNK_PDO_TYPE((ucPdoIndex - 1), _PD_FIX_SUPPLY_PDO);

            // -------------------- Voltage Setting --------------------
            if(usVoltage <= 2000)
            {
                // Other PDOs Voltage Cannot More Than 20V
                SET_TYPE_C_1_PD_SNK_CAP_VOL_MAX((ucPdoIndex - 1), usVoltage);
                SET_TYPE_C_1_PD_SNK_CAP_VOL_MIN((ucPdoIndex - 1), usVoltage);
            }
            else
            {
                SET_TYPE_C_1_PD_SNK_CAP_VOL_MAX((ucPdoIndex - 1), 2000);
                SET_TYPE_C_1_PD_SNK_CAP_VOL_MIN((ucPdoIndex - 1), 2000);
            }

            // -------------------- Current Setting --------------------
            if(usMaxCur <= 500)
            {
                SET_TYPE_C_1_PD_SNK_CAP_CUR((ucPdoIndex - 1), usMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_TYPE_C_1_PD_SNK_CAP_CUR((ucPdoIndex - 1), 500);
            }
        }
    }
}

#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Src/Snk Cap Argumented PDO (PPS) Info
// Input Value  : enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 2~7 / usMinVol(100mV) / usMaxVol(100mV) / ucMaxCur (50mA)
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetArgumentedPdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, BYTE ucMaxCur)
{
    // Convert Voltage from User 100mV to Fix PDO 10mV
    WORD usMaxVoltage = usMaxVol * 10;
    WORD usMinVoltage = usMinVol * 10;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // The 1st PDO Cannot Be Argumented PDO (Must Be Fix PDO with 5V), PDO Power Must < Max Power
        if((ucPdoIndex >= 2) && (ucPdoIndex <= 7))
        {
            SET_TYPE_C_1_PD_SRC_PDO_TYPE((ucPdoIndex - 1), _PD_3_PROGRAMMABLE_PDO);

            // Reset Peak Current Setting
            SET_TYPE_C_1_PD_SRC_CAP_PEAK((ucPdoIndex - 1), _PD_PEAK_CUR_NONE);

            // ------------------ Max Voltage Setting ------------------
            // NOTE : Max Voltage Cannot > 21V
            if(usMaxVoltage <= 2100)
            {
                SET_TYPE_C_1_PD_SRC_CAP_VOL_MAX((ucPdoIndex - 1), usMaxVoltage);
            }
            else
            {
                // Max Voltage Cannot > 21V
                SET_TYPE_C_1_PD_SRC_CAP_VOL_MAX((ucPdoIndex - 1), 2100);
            }

            // ------------------ Min Voltage Setting ------------------
            // NOTE : Min Voltage Cannot > Max Voltage
            if(usMinVoltage <= usMaxVoltage)
            {
                // NOTE : Min Voltage Cannot < 3V
                if(usMinVoltage < 300)
                {
                    usMinVoltage = 300;
                }

                SET_TYPE_C_1_PD_SRC_CAP_VOL_MIN((ucPdoIndex - 1), usMinVoltage);
            }
            else
            {
                // Min Voltage Cannot More Than Max Voltage
                SET_TYPE_C_1_PD_SRC_CAP_VOL_MIN((ucPdoIndex - 1), usMaxVoltage);
            }

            // -------------------- Current Setting --------------------
            if(ucMaxCur <= 100)
            {
                SET_TYPE_C_1_PD_SRC_CAP_CUR((ucPdoIndex - 1), (WORD)ucMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_TYPE_C_1_PD_SRC_CAP_CUR((ucPdoIndex - 1), 100);
            }
        }
        else
        {
            if((WORD)(((DWORD)usMaxVol * ucMaxCur) / 20) > GET_TYPE_C_1_MAX_POWER())
            {
                DebugMessageTypeC("8. [TYPE C] ==========X Set Fix PDO Error : PDO > Max Power", ucPdoIndex);
            }
            else
            {
                DebugMessageTypeC("8. [TYPE C] ==========X Set Fix PDO Index Error", ucPdoIndex);
            }
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Sink Capability
        if((ucPdoIndex >= 2) && (ucPdoIndex <= 7))
        {
            SET_TYPE_C_1_PD_SNK_PDO_TYPE((ucPdoIndex - 1), _PD_3_PROGRAMMABLE_PDO);

            // ------------------ Max Voltage Setting ------------------
            // NOTE : Max Voltage Cannot > 21V
            if(usMaxVoltage <= 2100)
            {
                SET_TYPE_C_1_PD_SNK_CAP_VOL_MAX((ucPdoIndex - 1), usMaxVoltage);
            }
            else
            {
                // Max Voltage Cannot > 21V
                SET_TYPE_C_1_PD_SNK_CAP_VOL_MAX((ucPdoIndex - 1), 2100);
            }

            // ------------------ Min Voltage Setting ------------------
            // NOTE : Min Voltage Cannot > Max Voltage
            if(usMinVoltage <= usMaxVoltage)
            {
                // NOTE : Min Voltage Cannot < 3V
                if(usMinVoltage < 300)
                {
                    usMinVoltage = 300;
                }

                SET_TYPE_C_1_PD_SNK_CAP_VOL_MIN((ucPdoIndex - 1), usMinVoltage);
            }
            else
            {
                // Min Voltage Cannot More Than Max Voltage
                SET_TYPE_C_1_PD_SNK_CAP_VOL_MIN((ucPdoIndex - 1), usMaxVoltage);
            }

            // -------------------- Current Setting --------------------
            if(ucMaxCur <= 100)
            {
                SET_TYPE_C_1_PD_SNK_CAP_CUR((ucPdoIndex - 1), (WORD)ucMaxCur);
            }
            else
            {
                // Current Cannot More Than 5A
                SET_TYPE_C_1_PD_SNK_CAP_CUR((ucPdoIndex - 1), 100);
            }
        }
    }
}
#endif  // End of #if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Set EPR Src/Snk Cap Argumented PDO (PPS) Info
// Input Value  : enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 9~11 / usMinVol (100mV) / usMaxVol(100mV) / enumPeakCur
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetAdjustablePdo(EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex, WORD usMinVol, WORD usMaxVol, EnumTypeCPDPeakCurType enumPeakCur)
{
    // Convert Voltage from User 100mV to Fix PDO 10mV
    WORD usMaxVoltage = usMaxVol * 10;
    WORD usMinVoltage = usMinVol * 10;

    enumPeakCur = enumPeakCur;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // The 8th PDO Cannot Be AVS PDO (Must Be Fix PDO with 28V), PDO Power Must < Max Power
        if((ucPdoIndex >= 9) && (ucPdoIndex <= 11))
        {
            SET_TYPE_C_1_PD_SRC_PDO_TYPE((ucPdoIndex - 1), _PD_3_1_ADJUSTABLE_PDO);

            // Set Peak Current
            SET_TYPE_C_1_PD_SRC_CAP_PEAK((ucPdoIndex - 1), enumPeakCur);

            // ------------------ Max Voltage Setting ------------------
            // NOTE : Max Voltage Cannot > 48V
            if(usMaxVoltage <= 4800)
            {
                SET_TYPE_C_1_PD_SRC_CAP_VOL_MAX((ucPdoIndex - 1), usMaxVoltage);
            }
            else
            {
                // Max Voltage Cannot > 28V
                SET_TYPE_C_1_PD_SRC_CAP_VOL_MAX((ucPdoIndex - 1), 4800);
            }

            // ------------------ Min Voltage Setting ------------------
            // NOTE : Min Voltage Cannot > Max Voltage
            if(usMinVoltage <= usMaxVoltage)
            {
                // NOTE : Min Voltage Cannot < 15V
                if(usMinVoltage < 1500)
                {
                    usMinVoltage = 1500;
                }

                SET_TYPE_C_1_PD_SRC_CAP_VOL_MIN((ucPdoIndex - 1), usMinVoltage);
            }
            else
            {
                // Min Voltage Cannot More Than Max Voltage
                SET_TYPE_C_1_PD_SRC_CAP_VOL_MIN((ucPdoIndex - 1), usMaxVoltage);
            }
        }
        else
        {
            DebugMessageTypeC("8. [TYPE C] ==========X Set AVS PDO Index Error", ucPdoIndex);
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Set EPR Sink AVS PDO
    }
}

//--------------------------------------------------
// Description  : Set TypeC 1 Initial Request RDO Info
// Input Value  : StructTypeCUserInitRDO(Initial Request Option, Target Voltage)
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetInitRdo(StructTypeCUserInitRDO stTypeCUserInitRdo)
{
    SET_TYPE_C_1_PD_REQ_TYPE(stTypeCUserInitRdo.enumReqType);

    switch(stTypeCUserInitRdo.enumTargetVolRDO)
    {
        case _TYPE_C_RDO_5V:

            SET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL(50);

            break;

        case _TYPE_C_RDO_5_1V:

            SET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL(51);

            break;

        case _TYPE_C_RDO_9V:

            SET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL(90);

            break;

        case _TYPE_C_RDO_12V:

            SET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL(120);

            break;

        case _TYPE_C_RDO_15V:

            SET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL(150);

            break;

        case _TYPE_C_RDO_20V:

            SET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL(200);

            break;

        case _TYPE_C_RDO_NO_TARGET:
        default:

            SET_TYPE_C_1_PD_INIT_REQ_TARGET_VOL(0);

            break;
    }

    // Set Operating Current and Maximum Current to 0xFFFF, which Means Kernel will Request the Maximum Current of Partner's Src Cap PDO.
    SET_TYPE_C_1_PD_REQ_INFO_1(0xFFFF);
    SET_TYPE_C_1_PD_REQ_INFO_2(0xFFFF);
}

//--------------------------------------------------
// Description  : Set TypeC 1 Request RDO Info
// Input Value  : StructTypeCUserRDO(Object Position, ReqInfo1, ReqInfo2, Cap Mismatch)
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetRdo(StructTypeCUserRDO stTypeCUserRdo)
{
    SET_TYPE_C_1_PD_REQ_OBJ_POS(stTypeCUserRdo.enumObjPos);
    SET_TYPE_C_1_PD_REQ_CAP_MIS(stTypeCUserRdo.b1CapMismatch);

    // Give Back Flag Define By Kernel
    SET_TYPE_C_1_PD_REQ_GIVE_BACK(_GIVE_BACK);

    if(GET_TYPE_C_1_PD_PARTNER_SRC_CAP_TYPE(GET_TYPE_C_1_PD_REQ_OBJ_POS() - 1) == _PD_FIX_SUPPLY_PDO)
    {
        // RDO[19:10] : Fix RDO (Op. Cur in 10mA)
        SET_TYPE_C_1_PD_REQ_INFO_1((stTypeCUserRdo.usReqInfo1) & 0x3FF);

        // RDO[9:0] : Fix RDO (Max. Cur in 10mA)
        SET_TYPE_C_1_PD_REQ_INFO_2((stTypeCUserRdo.usReqInfo2) & 0x3FF);
    }
    else
    {
        // RDO[19:9] : PPS RDO (Vol in 20mV)
        SET_TYPE_C_1_PD_REQ_INFO_1((stTypeCUserRdo.usReqInfo1) & 0x7FF);

        // RDO[6:0] : PPS RDO (Op. Cur in 50mA)
        SET_TYPE_C_1_PD_REQ_INFO_2((stTypeCUserRdo.usReqInfo2) & 0x7F);
    }

    // Set Request Type to Customized RDO
    SET_TYPE_C_1_PD_REQ_TYPE(_TYPE_C_REQ_CUSTOMIZED_RDO);
}

//--------------------------------------------------
// Description  : Set TypeC 1 Unconstrained Power Status
// Input Value  : enumTypeCUnconstrainPowerExist : _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST/ _TYPE_C_UNCONSTRAIN_POWER_EXIST
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetUnconstrainedPow(EnumTypeCUnconstrainPowerExist enumTypeCUnconstrainPowerExist)
{
    if(enumTypeCUnconstrainPowerExist == _TYPE_C_UNCONSTRAIN_POWER_EXIST)
    {
        SET_TYPE_C_1_PD_UNCONSTRAIN_POWER(_TRUE);
    }
    else
    {
        SET_TYPE_C_1_PD_UNCONSTRAIN_POWER(_FALSE);
    }
}

//--------------------------------------------------
// Description  : Enable / Disable FIFO_0/1/2 Interrupt when Rcv Msg.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdRxIntControl(bit b1Action)
{
    if(b1Action == _ENABLE)
    {
        // Enable Rx Rcv Msg IRQ
        ScalerSetBit(P6B_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT6);
    }
    else
    {
        // Disable Rx Rcv Msg IRQ
        ScalerSetBit(P6B_43_RX_RCV_STATUS_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT1), 0x00);
    }
}

#if(_HW_PD_FUNCTION_GEN < _PD_FUNCTION_GEN_2)
//--------------------------------------------------
// Description  : Update Retry Counter According to Spec Version (Back to Cable Spec Version Retry Count)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdUpdateCableRetryCounter(void)
{
    // For Old IC(RL6829) Use, Set Cable Retry Cnt to 0x65EC
    if((GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0) && (GET_TYPE_C_1_PD_CBL_SPEC_VER() == _PD_VERSION_3_0))
    {
        ScalerSetBit(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), _BIT4);
    }
    else
    {
        ScalerSetBit(P6B_EC_TX_PD_RTY_CNT, ~(_BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
}
#endif

//--------------------------------------------------
// Description  : Clear and Disable All of Certain Rx FIFO IRQs
// Input Value  : enumFifo : _RX_FIFO_0 / _RX_FIFO_1 / _RX_FIFO_2
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdRxFifoClear(EnumTypeCRxFifoIndex enumFifo)
{
    BYTE ucRxWaitCnt = 0;

    // Clear FIFO Only When Rx is Idle (H/W P6B_42_RX_FIFO_GENERAL_INFO fifo_used Can Only Be Cleared When RX PTCL FSM = IDLE)
    while((ScalerGetByte(P6B_21_RX_STATE_MACHINE_L) != 0x01) && (ucRxWaitCnt < 20))
    {
        ucRxWaitCnt ++;
        DELAY_XUS(100);
    }

    switch(enumFifo)
    {
        case _PD_RX_FIFO_0:

            ScalerSetByte(P6B_50_RX_FIFO0_RCV_MSG_INT, 0xAA);
            ScalerSetByte(P6B_51_RX_FIFO0_RCV_ERR_INT, 0x7F);
            ScalerSetByte(P6B_52_RX_FIFO0_RCV_ERR_INT_EN, 0x00);
            ScalerSetByte(P6B_53_RX_FIFO0_MSG_MIS_FLAG, 0x79);
            ScalerSetByte(P6B_60_RX_FIFO0_SP_MSG_INT, 0xAA);
            ScalerSetByte(P6B_62_RX_FIFO0_MSG_INT, 0xAA);
            ScalerSetBit(P6B_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT2));

            break;

        case _PD_RX_FIFO_1:

            ScalerSetByte(P6B_70_RX_FIFO1_RCV_MSG_INT, 0xAA);
            ScalerSetByte(P6B_71_RX_FIFO1_RCV_ERR_INT, 0x7F);
            ScalerSetByte(P6B_72_RX_FIFO1_RCV_ERR_INT_EN, 0x00);
            ScalerSetByte(P6B_73_RX_FIFO1_MSG_MIS_FLAG, 0x79);
            ScalerSetByte(P6B_80_RX_FIFO1_SP_MSG_INT, 0xAA);
            ScalerSetByte(P6B_82_RX_FIFO1_MSG_INT, 0xAA);
            ScalerSetBit(P6B_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1));

            break;

        case _PD_RX_FIFO_2:

            ScalerSetByte(P6B_90_RX_FIFO2_RCV_MSG_INT, 0xAA);
            ScalerSetByte(P6B_91_RX_FIFO2_RCV_ERR_INT, 0x7F);
            ScalerSetByte(P6B_92_RX_FIFO2_RCV_ERR_INT_EN, 0x00);
            ScalerSetByte(P6B_93_RX_FIFO2_MSG_MIS_FLAG, 0x79);
            ScalerSetByte(P6B_A0_RX_FIFO2_SP_MSG_INT, 0xAA);
            ScalerSetByte(P6B_A2_RX_FIFO2_MSG_INT, 0xAA);
            ScalerSetBit(P6B_42_RX_FIFO_GENERAL_INFO, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT0));

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
void ScalerTypeC1PdUnattachCancelTimerEvent(void)
{
    CLR_TYPE_C_1_PD_TIMER_EVENT_VALID();

    // Cancel Timer Event
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_SRC_TURN_ON_POWER);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_SEND_HARD_RST);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_SNK_HARD_RST_TIMEOUT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_S8_HRST);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_TPC_ERROR_RECOVERY);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_CLR_GET_SNK_CAP_WAIT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_CLR_VDMMSG_WAIT);
#if(_EMB_TYPE_C_1_PD3_PPS_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_PPS_TIMEOUT);
#endif
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT);

    CLR_TYPE_C_1_PD_WD_TIMER_VALUE();

    // Cancel WD Timer Event
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_SEND_HARD_RST);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_SENDER_RESP_TIMEOUT);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_PS_TRANSITION_TIMEOUT);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_VDM_RESP_TIMEOUT);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_ON_POWER);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_SRC_TURN_OFF_POWER);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_CHECK_VBUS);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_SEND_VCONN_ON_PSRDY);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_ENTER_FAILED);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_SEND_VCONN_SWAP);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_CHUNK_SENDER_REQ_TIMEOUT);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_SEND_EPR_SRC_CAP);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_TX_AVALIABLE);
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_DELL_AM_ENTER_TIMEOUT);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_PD_1_DELL_ATTEN_RETRY);
#endif
}

//--------------------------------------------------
// Description  : Check if Tx HW is Avaliable (PD 3.0 : Check TxSinkOK/NG, PD 2.0 : Check PHY Idle)
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeC1PdTxAvaliable(void)
{
    bit bCheckResult = _FALSE;

    if(GET_TYPE_C_1_PD_SPEC_VER() == _PD_VERSION_3_0)
    {
        if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
        {
            // Source Can Initiate AMS 16-20ms After Change Rp to SinkTxNG
            ScalerSetBit(P6C_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), _PD_SINK_TX_NG);

            ScalerTimerDelayXms(_SRC_INIT_AMS_TIMER);

            if(ScalerGetBit(P6C_37_CC_HW_Z_CFG, (_BIT7 | _BIT6)) == _PD_SINK_TX_NG)
            {
                // Check if Rp is Still SinkTxNG Before Initiate AMS, Prevent Receive Message During the Delay Time and Reset Rp to SinkTxOK.
                bCheckResult = _TRUE;

                if(GET_TYPE_C_1_PD_EPR_MODE() == _TRUE)
                {
                    // Cancel SourceEPRKeepAliveTimer (750~1000ms)
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_PD_1_SRC_EPR_KEEP_ALIVE_TIMEOUT);
                }
            }
        }
        else
        {
            if(ScalerTypeC1CcDetResistor() == _TYPE_C_DET_RP_3P0A)
            {   // Rp = SinkTxOK (Rp 3.0A)
                bCheckResult = _TRUE;
            }
            else
            {   // Rp = SinkTxNG (Rp 1.5A)
                bCheckResult = _FALSE;
            }
        }
    }
    else
    {   // Check PHY Idle
        if(ScalerGetBit(P6B_05_PD_PHY_IDLE_INT, _BIT2) == _BIT2)
        {   // PHY Idle Flag = 1
            bCheckResult = _TRUE;
        }
        else
        {   // PHY Idle Flag = 0
            bCheckResult = _FALSE;
        }
    }
    return bCheckResult;

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_TYPE_C_1_PD_FW_DEBUG == _ON))
    DebugMessageTypeC("[PD] Tx Avaliable Check : ", bCheckResult);
#endif
}

//--------------------------------------------------
// Description  : Get DP Alt. Mode Ready Status
// Input Value  : None
// Output Value : Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeC1PdGetAltModeReady(void)
{
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
#if(_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
    if((GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) && (GET_TYPE_C_1_PD_DP_ALT_MODE_WAIT_CONFIG() == _FALSE) && ((GET_TYPE_C_1_CC_PORT_ROLE() != _TYPE_C_PORT_DRP) || (GET_TYPE_C_1_PD_PARTNER_DRP() == _FALSE) || (GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) || (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _FALSE) || (GET_TYPE_C_1_PD_PRS_REJECT() == _TRUE)))
#else
    if((GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) && (GET_TYPE_C_1_PD_DP_ALT_MODE_WAIT_CONFIG() == _FALSE))
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }

#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    if(GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC)
    {
#if(_TYPE_C_1_PD_SRC_REQUEST_SWAP_TO_SNK == _TRUE)
        if((GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) && ((GET_TYPE_C_1_CC_PORT_ROLE() != _TYPE_C_PORT_DRP) || (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _TRUE) || ((GET_TYPE_C_1_PD_GET_SRC_CAP_SENT() == _TRUE) && ((GET_TYPE_C_1_PD_PARTNER_DRP() == _FALSE) || (GET_TYPE_C_1_PD_PARTNER_SRC_CAP_CHECK_RESULT() == _PD_SRC_CAP_INVALID) || (GET_TYPE_C_1_PD_PRS_REJECT() == _TRUE)))))
#else
        if(GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG)
#endif
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
#if(_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
        if((GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG) && ((GET_TYPE_C_1_CC_PORT_ROLE() != _TYPE_C_PORT_DRP) || (GET_TYPE_C_1_PD_PARTNER_DRP() == _FALSE) || (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _FALSE) || (GET_TYPE_C_1_PD_PRS_REJECT() == _TRUE)))
#else
        if(GET_TYPE_C_1_PD_DP_ALT_MODE_CONFIG() == _PD_DP_CONFIG)
#endif
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
#endif  // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
}

//--------------------------------------------------
// Description  : Push HPD into HPD Queue
// Input Value  : enumHpdType : _PD_HPD_LOW / _PD_HPD_HIGH..., HPD Space Time(ms)
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdPushHpd(EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime)
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
// Description  : Clear HPD Queue When PD Reset TO Prevent DP Urgent Event DeadLock
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdClrHpd(void)
{
    BYTE ucIndex = 0;
    EnumTypeCPcbPort enumTypeCPcbPort = ScalerTypeCxPcbxMapping(_EMB_TYPE_C_1);

    for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
    {
        SET_TYPE_C_1_PD_HPD_QUEUE(_PD_HPD_NONE);
        SET_TYPE_C_1_PD_HPD_SPACE_TIME(0);
        ADD_TYPE_C_1_PD_HPD_WPTR();
    }

    ScalerDpAuxRxHpdTogglePhyResetProc(ScalerTypeCPcbPortConvertToDx(enumTypeCPcbPort), _LOW);
    SET_TYPE_C_1_PD_HPD_STATUS(_LOW);
    CLR_TYPE_C_1_PD_HPD_WPTR();
    CLR_TYPE_C_1_PD_HPD_RPTR();
    CLR_TYPE_C_1_PD_HPD_CNT();
}

//--------------------------------------------------
// Description  : Check if Alt Mode is Urgent or not
// Input Value  : None
// Output Value : _PD_ALT_MODE_NOT_URGENT / _PD_ALT_MODE_URGENT
//--------------------------------------------------
EnumTypeCPDAltModeUrgentStatus ScalerTypeC1PdAltModeUrgentEvent(void)
{
    EnumTypeCPDAltModeUrgentStatus enumAltModeUrgentStatus = _PD_ALT_MODE_NOT_URGENT;

    if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
    {
        enumAltModeUrgentStatus = _PD_ALT_MODE_NOT_URGENT;
    }
    else
    {
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
        if((GET_TYPE_C_1_PD_DELL_AM_INIT_COMPLETE() == _FALSE) && (GET_TYPE_C_1_PD_DELL_AM_ENTER_TIMEOUT() == _FALSE))
        {
            enumAltModeUrgentStatus = _PD_ALT_MODE_URGENT;
        }
        else
        {
            enumAltModeUrgentStatus = _PD_ALT_MODE_NOT_URGENT;
        }
#else
        enumAltModeUrgentStatus = _PD_ALT_MODE_NOT_URGENT;
#endif
    }

    return enumAltModeUrgentStatus;
}

//--------------------------------------------------
// Description  : Get Rx1 PD HPD Queue(index)
// Input Value  : None
// Output Value : PD HPD Status
//--------------------------------------------------
EnumTypeCPDHpdType ScalerTypeC1PdRxGetHPDQueue(BYTE ucIndex)
{
    return GET_TYPE_C_1_PD_HPD_QUEUE(ucIndex);
}

//--------------------------------------------------
// Description  : Get Rx1 PD HPD Que Read Pointer
// Input Value  : None
// Output Value : Que Read Pointer
//--------------------------------------------------
BYTE ScalerTypeC1PdRxGetHPDQueReadPointer(void)
{
    return GET_TYPE_C_1_PD_HPD_RPTR();
}

//--------------------------------------------------
// Description  : Get Rx1 PD HPD Status
// Input Value  : None
// Output Value : PD HPD Status
//--------------------------------------------------
bit ScalerTypeC1PdRxGetHPDStatus(void)
{
    return GET_TYPE_C_1_PD_HPD_STATUS();
}

//--------------------------------------------------
// Description  : Get Tx1 PD HPD Queue
// Input Value  : None
// Output Value : StructTypeCTxHpdQueue
//--------------------------------------------------
StructTypeCTxHpdQueue ScalerTypeC1PdTxGetHPDQueue(void)
{
    StructTypeCTxHpdQueue stTxHpdQueue;
    BYTE ucIndex = 0;

    stTxHpdQueue.b3TxHpdCnt = GET_TYPE_C_1_PD_HPD_CNT();

    for(ucIndex = 0; ucIndex < _HPD_QUEUE_DEPTH; ucIndex++)
    {
        stTxHpdQueue.penumTxHpdType[ucIndex] = GET_TYPE_C_1_PD_HPD_QUEUE(GET_TYPE_C_1_PD_HPD_RPTR() + ucIndex);
    }

    ScalerTypeC1PdClrHpd();

    return stTxHpdQueue;
}

//--------------------------------------------------
// Description  : Get DP Alt. Mode Pin Assignment
// Input Value  : None
// Output Value : Enumeration of Pin Assignment C/D/E
//--------------------------------------------------
EnumTypeCPinCfgType ScalerTypeC1PdGetPinAssignment(void)
{
    return GET_TYPE_C_1_PD_PIN_ASSIGNMENT();
}

//--------------------------------------------------
// Description  : Set Pin Assignment Capabiliy
// Input Value  : None
// Output Value : Enumeration of Pin Assignment C/D/E
//--------------------------------------------------
void ScalerTypeC1PdSetPinAssignmentCapability(EnumTypeCPinCfgCapType enumPinAssignmentCap)
{
    SET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP(enumPinAssignmentCap);
}

//--------------------------------------------------
// Description  : Set Multi Function Bit
// Input Value  : None
// Output Value : Enumeration of Multi Function
//--------------------------------------------------
void ScalerTypeC1PdSetMultiFunctionBit(EnumTypeCMultiFuncStatus enumMultiFunc)
{
    if(enumMultiFunc == _TYPE_C_MULTI_FUNC_PREFER)
    {
        SET_TYPE_C_1_PD_MULTI_FUNCTION();
    }
    else
    {
        CLR_TYPE_C_1_PD_MULTI_FUNCTION();
    }
}

//--------------------------------------------------
// Description  : Get DP Alt. Mode Multi Function Change Process Done(Pin Assignment C <=> Pin Assignment D)
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeC1PdGetMultiFunctionChangeDone(void)
{
    if(GET_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE_DONE() == _TRUE)
    {
        CLR_TYPE_C_1_PD_MULTI_FUNCTION_CHANGE_DONE();

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Set Wait DP Config Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdWaitDpConfig(void)
{
    // Set Wait DP Config Flag to trigger Alt Mode Not Ready, Clr when rcv DP Config
    SET_TYPE_C_1_PD_DP_ALT_MODE_WAIT_CONFIG();
}

//--------------------------------------------------
// Description  : Set TypeC 1 System Event
// Input Value  : enumPdSysEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetSystemEvent(EnumTypeCPDSysEvent enumPdSysEvent)
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

//--------------------------------------------------
// Description  : Get TypeC 1 Port Controller Event
// Input Value  : None
// Output Value : EnumTypeCPDPortCtrlEvent
//--------------------------------------------------
EnumTypeCPDPortCtrlEvent ScalerTypeC1PdGetPortCtrlEvent(void)
{
    return GET_TYPE_C_1_PD_PORT_CTRL_EVENT();
}

//--------------------------------------------------
// Description  : Clear TypeC 1 Port Controller Event
// Input Value  : enumPdPortCtrlEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdClrPortCtrlEvent(EnumTypeCPDPortCtrlEvent enumPdPortCtrlEvent)
{
    CLR_TYPE_C_1_PD_PORT_CTRL_EVENT(enumPdPortCtrlEvent);
}

//--------------------------------------------------
// Description  : Get TypeC 1 PD Data Role
// Input Value  : None
// Output Value : PD Data Role (_TYPE_C_UFP_U / _TYPE_C_DFP_U)
//--------------------------------------------------
EnumTypeCDataRole ScalerTypeC1PdGetDataRole(void)
{
    if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_DFP)
    {
        return _TYPE_C_DFP_U;
    }
    else
    {
        return _TYPE_C_UFP_U;
    }
}

//--------------------------------------------------
// Description  : Get TypeC 1 PD Power Role
// Input Value  : None
// Output Value : PD Power Role (_TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC)
//--------------------------------------------------
EnumTypeCPowerRole ScalerTypeC1PdGetPowerRole(void)
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
// Description  : Get TypeC 1 PD Explicit Contract
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeC1PdGetExplicitContract(void)
{
    return GET_TYPE_C_1_PD_EXPLICIT_CONTRACT();
}

//--------------------------------------------------
// Description  : Get TypeC 1 PD is Processing PR Swap
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerTypeC1PdGetPRSwapProcesing(void)
{
    return GET_TYPE_C_1_PD_PRS_PROCESSING();
}

//--------------------------------------------------
// Description  : Set PD Vbus Protect Info
// Input Value  : ucPdoIndex , stTypeCVbusProtectInfo
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetVbusProtectInfo(BYTE ucPdoIndex, StructTypeCVbusProtectInfo stTypeCVbusProtectInfo)
{
    // Set OCP Setting
    SET_TYPE_C_1_OCP_RATIO((ucPdoIndex - 1), stTypeCVbusProtectInfo.ucOcpCurRatio);
}

//--------------------------------------------------
// Description  : Clear Interop S8 Flag to Enable FW Solution
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdClrInteropS8Flag(void)
{
    CLR_TYPE_C_1_PD_INTEROP_S8();
}

//--------------------------------------------------
// Description  : Get TypeC 1 TypeC Cable PD Capability
// Input Value  : None
// Output Value : _TYPE_C_CABLE_PD_CAP_UNCONFIRMED / _TYPE_C_CABLE_NON_PD_CAPABLE / _TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED
//--------------------------------------------------
EnumTypeCCablePdCapability ScalerTypeC1PdGetCablePdCapability(void)
{
    return GET_TYPE_C_1_PD_CBL_PD_CAPABILITY();
}

//--------------------------------------------------
// Description  : Get TypeC 1 TypeC Product Type when in UFP Data Role
// Input Value  : None
// Output Value : _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED / _TYPE_C_UFP_PRODUCT_TYPE_HUB / _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL
//--------------------------------------------------
EnumTypeCUFPProductType ScalerTypeC1PdGetUFPProductType(void)
{
    return GET_TYPE_C_1_PD_UFP_PRODUCT_TYPE();
}

//--------------------------------------------------
// Description  : Get TypeC 1 TypeC Product Type when in DFP Data Role
// Input Value  : None
// Output Value : _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED / _TYPE_C_DFP_PRODUCT_TYPE_HUB / _TYPE_C_DFP_PRODUCT_TYPE_HOST / _TYPE_C_DFP_PRODUCT_TYPE_BRICK
//--------------------------------------------------
EnumTypeCDFPProductType ScalerTypeC1PdGetDFPProductType(void)
{
    return GET_TYPE_C_1_PD_DFP_PRODUCT_TYPE();
}

//--------------------------------------------------
// Description  : Get TypeC 1 TypeC Cable Max Current
// Input Value  : None
// Output Value : return Cable Max Current (Unit: 10mA)
//--------------------------------------------------
WORD ScalerTypeC1PdGetCableMaxCurrent(void)
{
    return GET_TYPE_C_1_PD_CBL_MAX_CUR();
}

//--------------------------------------------------
// Description  : Get TypeC 1 TypeC Cable Info For DPCD
// Input Value  : None
// Output Value : StructTypeCCableInfoForDpcd
//--------------------------------------------------
StructTypeCCableInfoForDpcd ScalerTypeC1PdGetCableInfoForDpcd(void)
{
    StructTypeCCableInfoForDpcd stTypeCCableInfoForDpcd = {_PD_CBL_COMPONENT_PASSIVE, _PD_CBL_MAX_DP_RATE_UNCONFIRMED, _FALSE};

#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    // DPCD Table Bit[5:3]: Cable Type
    stTypeCCableInfoForDpcd.enumTypeCCableActiveComponent = GET_TYPE_C_1_PD_CBL_ACTIVE_COMPONENT();

    // DPCD Table Bit[2]: Cable UHBR13.5 Support
    stTypeCCableInfoForDpcd.b1CableUhbr13p5Support = GET_TYPE_C_1_PD_CBL_UHBR13P5_SUPPORT();

    // DPCD Table Bit[1:0]: Cable UHBR10_20 Capability
    stTypeCCableInfoForDpcd.enumTypeCCableMaxDpRate = GET_TYPE_C_1_PD_CBL_MAX_DP_RATE();
#endif
    return stTypeCCableInfoForDpcd;
}

//--------------------------------------------------
// Description  : Set PD Function Support Option
// Input Value  : enumFunctionSupport
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetFunctionSupport(EnumTypeCFunctionSupport enumFunctionSupport)
{
    switch(enumFunctionSupport)
    {
        case _TYPE_C_SUPPORT_NO_FUNCTION:
        case _TYPE_C_SUPPORT_CC_FUNCTION:

            CLR_TYPE_C_1_PD_FUNCTION_EN();
            CLR_TYPE_C_1_PD_ALT_MODE_FUNCTION();

            break;

        case _TYPE_C_SUPPORT_CC_AND_PD_FUNCTION:

            SET_TYPE_C_1_PD_FUNCTION_EN();
            CLR_TYPE_C_1_PD_ALT_MODE_FUNCTION();

            break;

        case _TYPE_C_SUPPORT_FULL_FUNCTION:

            SET_TYPE_C_1_PD_FUNCTION_EN();
            SET_TYPE_C_1_PD_ALT_MODE_FUNCTION();

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get TypeC 1 PD DP Status Info
// Input Value  : None
// Output Value : StructTypeCDpStatusInfo (enumPartnerDpConnectStatus / b1PartnerMultiFunctionBit...)
//--------------------------------------------------
StructTypeCDpStatusInfo ScalerTypeC1PdGetDpStatusInfo(void)
{
#if(_TYPE_C_DPAM_VERSION < _DPAM_VERSION_2_1)
    StructTypeCDpStatusInfo stDpStatusInfo = {_PD_DP_CONNECT_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, _PD_HPD_NONE};
#else
    StructTypeCDpStatusInfo stDpStatusInfo = {_PD_DP_CONNECT_NONE, 0x00, 0x00, 0x00, 0x00, 0x00, _PD_HPD_NONE, 0x00};
#endif

    stDpStatusInfo.enumPartnerDpConnectStatus = GET_TYPE_C_1_PD_PARTNER_DP_CONNECT_STATUS();
    stDpStatusInfo.b1PartnerDpPowerLow = GET_TYPE_C_1_PD_PARTNER_DP_POWER_LOW();
    stDpStatusInfo.b1PartnerDpFunctionEnabled = GET_TYPE_C_1_PD_PARTNER_DP_FUNCTION_ENABLE();
    stDpStatusInfo.b1PartnerMultiFunctionBit = GET_TYPE_C_1_PD_PARTNER_MULTI_FUNCTION();
    stDpStatusInfo.b1PartnerUsbConfigRequest = GET_TYPE_C_1_PD_PARTNER_USB_CONFIG_REQUEST();
    stDpStatusInfo.b1PartnerDpAltModeExit = GET_TYPE_C_1_PD_PARTNER_DP_ALT_MODE_EXIT_REQ();
    stDpStatusInfo.enumPartnerHpdType = GET_TYPE_C_1_PD_PARTNER_HPD_TYPE();
#if(_TYPE_C_DPAM_VERSION >= _DPAM_VERSION_2_1)
    stDpStatusInfo.b1PartnerNoDpAltSuspend = GET_TYPE_C_1_PD_PARTNER_NO_DP_ALT_SUSPEND();
#endif

    return stDpStatusInfo;
}

#if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
//--------------------------------------------------
// Description  : Force Sending HPD IRQ for DP CTS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdDpCTSForceHpdIrq(void)
{
    BYTE ucSendResult = _FAIL;

    CLR_TYPE_C_1_PD_INT_OVERWRITE();

    if((GET_TYPE_C_1_PD_HPD_STATUS() == _HIGH) &&
       (((GET_TYPE_C_1_PD_FW_STATE() == _PD_SRC_READY) && (GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SRC_READY)) || ((GET_TYPE_C_1_PD_FW_STATE() == _PD_SNK_READY) && (GET_TYPE_C_1_PD_SUB_STATE() == _PD_SUB_SNK_READY))) &&
       (GET_TYPE_C_1_PD_AMS_STATUS() == _PD_AMS_NONE) && (GET_TYPE_C_1_PD_SYS_EVENT() == _PD_SYS_EVENT_NONE) && (GET_TYPE_C_1_PD_ATTENTION_WAIT() == _FALSE))
    {
        if(GET_TYPE_C_1_PD_DATA_ROLE() == _PD_DATA_UFP)
        {
            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Only Send Msg When Function Has not Been Interrupted by Receive INT
                if(GET_TYPE_C_1_PD_INT_OVERWRITE() == _FALSE)
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
                    ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_ATTENTION_REQ);

                    // Sent Discarded will be Set When Send Msg Has Been Interrupted
                    if(GET_TYPE_C_1_PD_TRANSMIT_RESULT() == _PD_SENT_DISCARDED)
                    {
                        CLR_TYPE_C_1_PD_FORCE_HPD_IRQ();
                    }
                    else
                    {
                        ucSendResult = _SUCCESS;
                    }
                }
            }
        }
        else
        {
            if(ScalerTypeC1PdTxAvaliable() == _TRUE)
            {
                // Only Send Msg When Function Has not Been Interrupted by Receive INT
                if(GET_TYPE_C_1_PD_INT_OVERWRITE() == _FALSE)
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
                    ScalerTypeC1PdSendMsg(_PD_SOP_PKT, _PD_CMD_VDM, _PD_VDM_CMD_10);

                    // Sent Discarded will be Set When Send Msg Has Been Interrupted
                    if(GET_TYPE_C_1_PD_TRANSMIT_RESULT() == _PD_SENT_DISCARDED)
                    {
                        CLR_TYPE_C_1_PD_FORCE_HPD_IRQ();
                    }
                    else
                    {
                        ucSendResult = _SUCCESS;
                    }
                }
            }
        }
    }

    if(ucSendResult == _FAIL)
    {
        // Push HPD_IRQ into HPD Queue When Force Sending HPD IRQ Failed, then PD will Re-Send HPD_IRQ in Main loop
        ScalerTypeC1PdPushHpd(_PD_HPD_IRQ, 0);
    }
}
#endif // End of #if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
#endif // End of #if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : Get Lenovo Alt Mode Ready Status
// Input Value  : None
// Output Value : Lenovo Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeC1PdGetLenovoAltModeReady(void)
{
#if(_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
    if((GET_TYPE_C_1_PD_LENOVO_ALT_MODE_ENTER() == _TRUE) && ((GET_TYPE_C_1_CC_PORT_ROLE() != _TYPE_C_PORT_DRP) || (GET_TYPE_C_1_PD_PARTNER_DRP() == _FALSE) || (GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) || (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _FALSE) || (GET_TYPE_C_1_PD_PRS_REJECT() == _TRUE)))
#else
    if(GET_TYPE_C_1_PD_LENOVO_ALT_MODE_ENTER() == _TRUE)
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get Port Partner Lenovo Device Type
// Input Value  : None
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType ScalerTypeC1PdGetLenovoDeviceType(void)
{
    return GET_TYPE_C_1_PD_LENOVO_DEVICE_TYPE();
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event (Including System Acknowledge)
// Input Value  : None
// Output Value : StructTypeCLenovoSysEvent
//--------------------------------------------------
StructTypeCLenovoSysEvent ScalerTypeC1PdGetLenovoSystemEvent(void)
{
    StructTypeCLenovoSysEvent stLenovoSysEvent = {_TYPE_C_LENOVO_SYS_DC_MODE, _TYPE_C_LENOVO_SYS_STATE_NONE, _FALSE, 0x00, 0x00};

    stLenovoSysEvent.b3SystemReserved = (GET_TYPE_C_1_PD_LENOVO_SYS_EVENT() & (_BIT7 | _BIT6 | _BIT5)) >> 5;
    stLenovoSysEvent.enumSystemPowerMode = (GET_TYPE_C_1_PD_LENOVO_SYS_EVENT() & _BIT4) >> 4;
    stLenovoSysEvent.enumSystemState = (GET_TYPE_C_1_PD_LENOVO_SYS_EVENT() & (_BIT3 | _BIT2 | _BIT1)) >> 1;
    stLenovoSysEvent.b1SystemEvent = (bit)(GET_TYPE_C_1_PD_LENOVO_SYS_EVENT() & _BIT0);
    stLenovoSysEvent.ucSystemAcknowlegde = GET_TYPE_C_1_PD_LENOVO_SYS_ACKNOWLEDGE();

    return stLenovoSysEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Set Docking Event
// Input Value  : stLenovoDockEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetLenovoDockingEvent(StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    if(stLenovoDockEvent.b1DockingEvent == _TRUE)
    {
        SET_TYPE_C_1_PD_LENOVO_DOCK_EVENT(((BYTE)stLenovoDockEvent.b4DockingReserved << 4) | (stLenovoDockEvent.enumDockingPowerSwitch << 2) | ((BYTE)stLenovoDockEvent.b1DockingWolRequest << 1) | ((BYTE)stLenovoDockEvent.b1DockingEvent));
    }
    else
    {
        CLR_TYPE_C_1_PD_LENOVO_DOCK_EVENT();
    }
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : None
// Output Value : Docking Event Check Busy Result (_TYPE_C_LENOVO_DOCK_EVENT_BUSY / _TYPE_C_LENOVO_DOCK_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCLenovoCheckBusyResult ScalerTypeC1PdCheckLenovoDockingEventBusy(void)
{
    if(GET_TYPE_C_1_PD_LENOVO_DOCK_EVENT() == 0x00)
    {
        return _TYPE_C_LENOVO_DOCK_EVENT_NOT_BUSY;
    }
    else
    {
        return _TYPE_C_LENOVO_DOCK_EVENT_BUSY;
    }
}
#endif // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : Get Acer Alt Mode Ready Status
// Input Value  : None
// Output Value : Acer Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeC1PdGetAcerAltModeReady(void)
{
#if(_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
    if((GET_TYPE_C_1_PD_ACER_ALT_MODE_ENTER() == _TRUE) && ((GET_TYPE_C_1_CC_PORT_ROLE() != _TYPE_C_PORT_DRP) || (GET_TYPE_C_1_PD_PARTNER_DRP() == _FALSE) || (GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) || (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _FALSE) || (GET_TYPE_C_1_PD_PRS_REJECT() == _TRUE)))
#else
    if(GET_TYPE_C_1_PD_ACER_ALT_MODE_ENTER() == _TRUE)
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Get System Event from Kernel
// Input Value  : None
// Output Value : StructTypeCAcerSysEvent
//--------------------------------------------------
StructTypeCAcerSysEvent ScalerTypeC1PdGetAcerSystemEvent(void)
{
    StructTypeCAcerSysEvent stAcerSysEvent = {_TYPE_C_ACER_SYS_EVENT_NONE, {0x00}, 0x00};

    if(GET_TYPE_C_1_PD_ACER_SYS_EVENT() != _TYPE_C_ACER_SYS_EVENT_NONE)
    {
        stAcerSysEvent.enumEvent = GET_TYPE_C_1_PD_ACER_SYS_EVENT();
        stAcerSysEvent.b3VdmCnt = GET_TYPE_C_1_PD_ACER_SYS_VDM_CNT();

        for(pData[0] = 0; pData[0] < (GET_TYPE_C_1_PD_ACER_SYS_VDM_CNT() * 4); pData[0]++)
        {
            stAcerSysEvent.pucVdmData[pData[0]] = GET_TYPE_C_1_PD_ACER_SYS_VDM_DATA(pData[0]);
        }

        CLR_TYPE_C_1_PD_ACER_SYS_EVENT(_TYPE_C_ACER_SYS_EVENT_ALL);
    }

    return stAcerSysEvent;
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Set User Event to Kernel
// Input Value  : stAcerUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetAcerUserEvent(StructTypeCAcerUserEvent stAcerUserEvent)
{
    if(stAcerUserEvent.enumEvent != _TYPE_C_ACER_USER_EVENT_NONE)
    {
        SET_TYPE_C_1_PD_ACER_USER_EVENT(stAcerUserEvent.enumEvent);

        // VDO Cnt Should be 0~6, not including VDM Header
        SET_TYPE_C_1_PD_ACER_USER_VDM_CNT(stAcerUserEvent.b3VdmCnt);

        for(pData[0] = 0; pData[0] < (stAcerUserEvent.b3VdmCnt * 4); pData[0]++)
        {
            SET_TYPE_C_1_PD_ACER_USER_VDM_DATA(pData[0], stAcerUserEvent.pucVdmData[pData[0]]);
        }
    }
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Check if Last User Event has been Sent
// Input Value  : None
// Output Value : User Event Busy Status (_TYPE_C_ACER_USER_EVENT_BUSY / _TYPE_C_ACER_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCAcerBusyStatus ScalerTypeC1PdCheckAcerUserEventBusy(void)
{
    if(GET_TYPE_C_1_PD_ACER_USER_EVENT() == _TYPE_C_ACER_USER_EVENT_NONE)
    {
        return _TYPE_C_ACER_USER_EVENT_NOT_BUSY;
    }
    else
    {
        return _TYPE_C_ACER_USER_EVENT_BUSY;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : Get Hp Alt Mode Ready Status
// Input Value  : None
// Output Value : Hp Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeC1PdGetHpAltModeReady(void)
{
#if(_TYPE_C_1_PD_SNK_REQUEST_SWAP_TO_SRC == _TRUE)
    if((GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _TRUE) && ((GET_TYPE_C_1_CC_PORT_ROLE() != _TYPE_C_PORT_DRP) || (GET_TYPE_C_1_PD_PARTNER_DRP() == _FALSE) || (GET_TYPE_C_1_PD_POWER_ROLE() == _PD_POWER_SRC) || (GET_TYPE_C_1_PD_UNCONSTRAIN_POWER() == _FALSE) || (GET_TYPE_C_1_PD_PRS_REJECT() == _TRUE)))
#else
    if(GET_TYPE_C_1_PD_HP_ALT_MODE_ENTER() == _TRUE)
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Get System Event from Kernel
// Input Value  : None
// Output Value : StructTypeCHpSysEvent
//--------------------------------------------------
StructTypeCHpSysEvent ScalerTypeC1PdGetHpSystemEvent(void)
{
    StructTypeCHpSysEvent stHpSysEvent = {_TYPE_C_HP_SYS_EVENT_NONE, {0x00}, 0x00};

    // Check if Sys Event Queue is Empty
    if(GET_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_CNT() > 0)
    {
        // Update Sys Event Struct For Kernel Usage
        stHpSysEvent = GET_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE(GET_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_HEAD());

        CLR_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE(GET_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_HEAD());
        ADD_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_HEAD();
        SUB_TYPE_C_1_PD_HP_SYS_EVENT_QUEUE_CNT();
    }

    return stHpSysEvent;
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Set User Event to Kernel
// Input Value  : stHpUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetHpUserEvent(StructTypeCHpUserEvent stHpUserEvent)
{
    if(stHpUserEvent.enumEvent != _TYPE_C_HP_USER_EVENT_NONE)
    {
        SET_TYPE_C_1_PD_HP_USER_EVENT(stHpUserEvent.enumEvent);

        // VDO Cnt Should be 0~5, not including VDM Header
        SET_TYPE_C_1_PD_HP_USER_VDM_CNT(stHpUserEvent.b3VdmCnt);

        for(pData[0] = 0; pData[0] < (stHpUserEvent.b3VdmCnt * 4); pData[0]++)
        {
            SET_TYPE_C_1_PD_HP_USER_VDM_DATA(pData[0], stHpUserEvent.pucVdmData[pData[0]]);
        }
    }
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Check if Last User Event has been Sent
// Input Value  : None
// Output Value : User Event Busy Status (_TYPE_C_HP_USER_EVENT_BUSY / _TYPE_C_HP_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCHpBusyStatus ScalerTypeC1PdCheckHpUserEventBusy(void)
{
    if(GET_TYPE_C_1_PD_HP_USER_EVENT() == _TYPE_C_HP_USER_EVENT_NONE)
    {
        return _TYPE_C_HP_USER_EVENT_NOT_BUSY;
    }
    else
    {
        return _TYPE_C_HP_USER_EVENT_BUSY;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
//--------------------------------------------------
// Description  : Get Dell Alt Mode Ready Status
// Input Value  : None
// Output Value : Dell Alt Mode Ready (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeC1PdGetDellAltModeReady(void)
{
    if(GET_TYPE_C_1_PD_DELL_ALT_MODE_ENTER() == _TRUE)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Get System Event from Kernel
// Input Value  : None
// Output Value : StructTypeCDellSysEvent
//--------------------------------------------------
StructTypeCDellSysEvent ScalerTypeC1PdGetDellSystemEvent(void)
{
    StructTypeCDellSysEvent stDellSysEvent = {_TYPE_C_DELL_SYS_EVENT_NONE, {0x00}, 0x00};

    if(GET_TYPE_C_1_PD_DELL_SYS_EVENT() != _TYPE_C_DELL_SYS_EVENT_NONE)
    {
        stDellSysEvent.enumEvent = GET_TYPE_C_1_PD_DELL_SYS_EVENT();

        if((GET_TYPE_C_1_PD_DELL_SYS_EVENT() & _TYPE_C_DELL_SYS_EVENT_0X12) == _TYPE_C_DELL_SYS_EVENT_0X12)
        {
            stDellSysEvent.b3VdmCnt = GET_TYPE_C_1_PD_DELL_SYS_VDM_CNT();

            for(pData[0] = 0; pData[0] < (stDellSysEvent.b3VdmCnt * 4); pData[0]++)
            {
                stDellSysEvent.pucVdmData[pData[0]] = GET_TYPE_C_1_PD_DELL_SYS_VDM_DATA(pData[0]);
            }
        }

        CLR_TYPE_C_1_PD_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ALL);
    }

    return stDellSysEvent;
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Set User Event to Kernel
// Input Value  : stDellUserEvent
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetDellUserEvent(StructTypeCDellUserEvent stDellUserEvent)
{
    if(stDellUserEvent.enumEvent != _TYPE_C_DELL_USER_EVENT_NONE)
    {
        if((GET_TYPE_C_1_PD_DELL_SYS_EVENT() & _TYPE_C_DELL_SYS_EVENT_0X12) == _TYPE_C_DELL_SYS_EVENT_0X12)
        {
            // If (System Event == 0x12) , Set Atten_Discard SysEvent and Don't Set User Event to Kernel.
            SET_TYPE_C_1_PD_DELL_SYS_EVENT(_TYPE_C_DELL_SYS_EVENT_ATTEN_DISCARD);
        }
        else
        {
            SET_TYPE_C_1_PD_DELL_USER_EVENT(stDellUserEvent.enumEvent);

            // VDO Cnt Should be 0~6, not including VDM Header
            SET_TYPE_C_1_PD_DELL_USER_VDM_CNT(stDellUserEvent.b3VdmCnt);

            for(pData[0] = 0; pData[0] < (stDellUserEvent.b3VdmCnt * 4); pData[0]++)
            {
                SET_TYPE_C_1_PD_DELL_USER_VDM_DATA(pData[0], stDellUserEvent.pucVdmData[pData[0]]);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Set Initial Complete Status to Kernel
// Input Value  : enumDellInitCompleteStatus
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdSetDellAltModeInitComplete(EnumTypeCDellInitCompleteStatus enumDellInitCompleteStatus)
{
    if(enumDellInitCompleteStatus == _TYPE_C_DELL_INIT_COMPLETE)
    {
        SET_TYPE_C_1_PD_DELL_AM_INIT_COMPLETE();
    }
    else
    {
        CLR_TYPE_C_1_PD_DELL_AM_INIT_COMPLETE();
    }
}

//--------------------------------------------------
// Description  : Type C Dell Alt Mode Check if Last User Event has been Sent
// Input Value  : None
// Output Value : User Event Busy Status (_TYPE_C_DELL_USER_EVENT_BUSY / _TYPE_C_DELL_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCDellBusyStatus ScalerTypeC1PdCheckDellUserEventBusy(void)
{
    if(GET_TYPE_C_1_PD_DELL_USER_EVENT() == _TYPE_C_DELL_USER_EVENT_NONE)
    {
        return _TYPE_C_DELL_USER_EVENT_NOT_BUSY;
    }
    else
    {
        return _TYPE_C_DELL_USER_EVENT_BUSY;
    }
}

//--------------------------------------------------
// Description  : Type C Get Enter Dell Alt Mode Time Out Result
// Input Value  : None
// Output Value : Enter Dell Alt Mode Time Out Result (_TYPE_C_ENTER_DELL_ALT_MODE_TIMEOUT/ _TYPE_C_ENTER_DELL_ALT_MODE_WITHOUT_TIMEOUT)
//--------------------------------------------------
EnumTypeCEnterDellAltModeTimeOut ScalerTypeC1PdGetEnterDellAltModeTimeOut(void)
{
    if(GET_TYPE_C_1_PD_DELL_AM_ENTER_TIMEOUT() == _TRUE)
    {
        return _TYPE_C_ENTER_DELL_ALT_MODE_TIMEOUT;
    }
    else
    {
        return _TYPE_C_ENTER_DELL_ALT_MODE_WITHOUT_TIMEOUT;
    }
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_DELL_ALT_MODE)
#endif  // End of #if(_EMB_TYPE_C_1_MODAL_OPERATION_SUPPORT == _ON)

#if(_BILLBOARD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type C Alt Mode Related Info for Billboard Display
// Input Value  : Pointer of Billboard Info
// Output Value : None
//--------------------------------------------------
void ScalerTypeC1PdGetAltModeBillboardInfo(BYTE *pucBillboardAltModeInfo)
{
    // Call Example : ScalerTypeC1PdGetAltModeBillboardInfo((BYTE *)(&Array))
    // Note : Array Size Should be _TYPE_C_1_PD_ALT_MODE_SUPPORT_CNT

    pucBillboardAltModeInfo = pucBillboardAltModeInfo;

#if(_EMB_TYPE_C_1_DP_ALT_MODE_SUPPORT == _ON)
    if(ScalerTypeC1PdGetAltModeReady() == _TRUE)
    {
        *pucBillboardAltModeInfo++ = 0x03;                              // Alt Mode Status
    }
    else
    {
        *pucBillboardAltModeInfo++ = 0x00;                              // Alt Mode Status
    }
    *pucBillboardAltModeInfo++ = (BYTE)(_DP_SID);                       // Alt Mode SVID_Low
    *pucBillboardAltModeInfo++ = (BYTE)(_DP_SID >> 8);                  // Alt Mode SVID_High
    *pucBillboardAltModeInfo++ = 0x00;                                  // Mode of SVID
    *pucBillboardAltModeInfo++ = _TYPE_C_EMB_DP_ALT_MODE_URL_INDEX;     // URL Index
#if(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_RX)
    *pucBillboardAltModeInfo++ = 0x45;                                  // Discover Mode Ack VDO1[7:0]
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[15:8] : DP Tx Pin Assignment Cap
    *pucBillboardAltModeInfo++ = GET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP();  // Discover Mode Ack VDO1[23:16] : DP Rx Pin Assignment Cap
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[31:24] : Rsv
#elif(_EMB_TYPE_C_1_PD_BEHAVIOR_TYPE == _TYPE_C_DP_TX)
    *pucBillboardAltModeInfo++ = 0x46;                                  // Discover Mode Ack VDO1[7:0]
    *pucBillboardAltModeInfo++ = GET_TYPE_C_1_PD_PIN_ASSIGNMENT_CAP();  // Discover Mode Ack VDO1[15:8] : DP Tx Pin Assignment Cap
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[23:16] : DP Rx Pin Assignment Cap
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[31:24] : Rsv
#endif
    *pucBillboardAltModeInfo++ = _TRUE;                                 // Current altmode active
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
    if(ScalerTypeC1PdGetLenovoAltModeReady() == _TRUE)
    {
        *pucBillboardAltModeInfo++ = 0x03;                              // Alt Mode Status
    }
    else
    {
        *pucBillboardAltModeInfo++ = 0x00;                              // Alt Mode Status
    }
    *pucBillboardAltModeInfo++ = (BYTE)(_LENOVO_VID);                   // Alt Mode SVID_Low
    *pucBillboardAltModeInfo++ = (BYTE)(_LENOVO_VID >> 8);              // Alt Mode SVID_High
    *pucBillboardAltModeInfo++ = 0x00;                                  // Mode of SVID
    *pucBillboardAltModeInfo++ = _TYPE_C_EMB_LENOVO_ALT_MODE_URL_INDEX; // URL Index
    *pucBillboardAltModeInfo++ = 0x01;                                  // Discover Mode Ack VDO1[7:0]
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[15:8]
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[23:16]
    *pucBillboardAltModeInfo++ = 0x00;                                  // Discover Mode Ack VDO1[31:24]
    *pucBillboardAltModeInfo++ = _TRUE;                                 // Current altmode active
#endif
}
#endif  // End of #if(_BILLBOARD_SUPPORT == _ON)

#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))
