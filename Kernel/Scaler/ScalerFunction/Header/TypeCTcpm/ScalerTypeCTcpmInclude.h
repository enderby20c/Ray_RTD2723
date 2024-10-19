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
// ID Code      : ScalerTypeCTcpmInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// POWER & Data ROLE SWAP OPTIONS (If DRP Must Support One Kind Of Swap)
//--------------------------------------------------
#if(_HW_TCPM_0_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
// PRS Options for DP RX
#define _HW_TCPM_0_0_PD_DPRX_SRC_ACCEPT_SWAP_TO_SNK             _FALSE
#define _HW_TCPM_0_0_PD_DPRX_SRC_REQUEST_SWAP_TO_SNK            _FALSE
#define _HW_TCPM_0_0_PD_DPRX_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _HW_TCPM_0_0_PD_DPRX_SNK_REQUEST_SWAP_TO_SRC            _TRUE

// PRS Options for DP Tx
#define _HW_TCPM_0_0_PD_DPTX_SRC_ACCEPT_SWAP_TO_SNK             _TRUE
#define _HW_TCPM_0_0_PD_DPTX_SRC_REQUEST_SWAP_TO_SNK            _TRUE
#define _HW_TCPM_0_0_PD_DPTX_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _HW_TCPM_0_0_PD_DPTX_SNK_REQUEST_SWAP_TO_SRC            _TRUE

// DRS Options for DP RX
#define _HW_TCPM_0_0_PD_DPRX_DFP_SWAP_TO_UFP                    _TRUE
#define _HW_TCPM_0_0_PD_DPRX_UFP_SWAP_TO_DFP                    _FALSE

// DRS Options for DP TX
#define _HW_TCPM_0_0_PD_DPTX_DFP_SWAP_TO_UFP                    _FALSE
#define _HW_TCPM_0_0_PD_DPTX_UFP_SWAP_TO_DFP                    _TRUE
#endif

#if(_HW_TCPM_0_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
// PRS Options for DP RX
#define _HW_TCPM_0_1_PD_DPRX_SRC_ACCEPT_SWAP_TO_SNK             _FALSE
#define _HW_TCPM_0_1_PD_DPRX_SRC_REQUEST_SWAP_TO_SNK            _FALSE
#define _HW_TCPM_0_1_PD_DPRX_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _HW_TCPM_0_1_PD_DPRX_SNK_REQUEST_SWAP_TO_SRC            _TRUE

// PRS Options for DP Tx
#define _HW_TCPM_0_1_PD_DPTX_SRC_ACCEPT_SWAP_TO_SNK             _TRUE
#define _HW_TCPM_0_1_PD_DPTX_SRC_REQUEST_SWAP_TO_SNK            _TRUE
#define _HW_TCPM_0_1_PD_DPTX_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _HW_TCPM_0_1_PD_DPTX_SNK_REQUEST_SWAP_TO_SRC            _TRUE

// DRS Options for DP RX
#define _HW_TCPM_0_1_PD_DPRX_DFP_SWAP_TO_UFP                    _TRUE
#define _HW_TCPM_0_1_PD_DPRX_UFP_SWAP_TO_DFP                    _FALSE

// DRS Options for DP TX
#define _HW_TCPM_0_1_PD_DPTX_DFP_SWAP_TO_UFP                    _FALSE
#define _HW_TCPM_0_1_PD_DPTX_UFP_SWAP_TO_DFP                    _TRUE
#endif

#if(_HW_TCPM_1_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
// PRS Options for DP RX
#define _HW_TCPM_1_0_PD_DPRX_SRC_ACCEPT_SWAP_TO_SNK             _FALSE
#define _HW_TCPM_1_0_PD_DPRX_SRC_REQUEST_SWAP_TO_SNK            _FALSE
#define _HW_TCPM_1_0_PD_DPRX_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _HW_TCPM_1_0_PD_DPRX_SNK_REQUEST_SWAP_TO_SRC            _TRUE

// PRS Options for DP Tx
#define _HW_TCPM_1_0_PD_DPTX_SRC_ACCEPT_SWAP_TO_SNK             _TRUE
#define _HW_TCPM_1_0_PD_DPTX_SRC_REQUEST_SWAP_TO_SNK            _TRUE
#define _HW_TCPM_1_0_PD_DPTX_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _HW_TCPM_1_0_PD_DPTX_SNK_REQUEST_SWAP_TO_SRC            _TRUE

// DRS Options for DP RX
#define _HW_TCPM_1_0_PD_DPRX_DFP_SWAP_TO_UFP                    _TRUE
#define _HW_TCPM_1_0_PD_DPRX_UFP_SWAP_TO_DFP                    _FALSE

// DRS Options for DP TX
#define _HW_TCPM_1_0_PD_DPTX_DFP_SWAP_TO_UFP                    _FALSE
#define _HW_TCPM_1_0_PD_DPTX_UFP_SWAP_TO_DFP                    _TRUE
#endif

#if(_HW_TCPM_1_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
// PRS Options for DP RX
#define _HW_TCPM_1_1_PD_DPRX_SRC_ACCEPT_SWAP_TO_SNK             _FALSE
#define _HW_TCPM_1_1_PD_DPRX_SRC_REQUEST_SWAP_TO_SNK            _FALSE
#define _HW_TCPM_1_1_PD_DPRX_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _HW_TCPM_1_1_PD_DPRX_SNK_REQUEST_SWAP_TO_SRC            _TRUE

// PRS Options for DP Tx
#define _HW_TCPM_1_1_PD_DPTX_SRC_ACCEPT_SWAP_TO_SNK             _TRUE
#define _HW_TCPM_1_1_PD_DPTX_SRC_REQUEST_SWAP_TO_SNK            _TRUE
#define _HW_TCPM_1_1_PD_DPTX_SNK_ACCEPT_SWAP_TO_SRC             _TRUE
#define _HW_TCPM_1_1_PD_DPTX_SNK_REQUEST_SWAP_TO_SRC            _TRUE

// DRS Options for DP RX
#define _HW_TCPM_1_1_PD_DPRX_DFP_SWAP_TO_UFP                    _TRUE
#define _HW_TCPM_1_1_PD_DPRX_UFP_SWAP_TO_DFP                    _FALSE

// DRS Options for DP TX
#define _HW_TCPM_1_1_PD_DPTX_DFP_SWAP_TO_UFP                    _FALSE
#define _HW_TCPM_1_1_PD_DPTX_UFP_SWAP_TO_DFP                    _TRUE
#endif

//--------------------------------------------------
// Definitions of TCPM CC Parameters
//--------------------------------------------------
#define _TCPM_CC_DEBOUNCE_TIME                                  120     // tCcDebounce : 100~200ms
#define _TCPM_PD_DEBOUNCE_TIME                                  10      // tPdDebounce : 10~20ms

//--------------------------------------------------
// Definitions of TCPM Power Parameters
//--------------------------------------------------
#define _TCPM_VSAFE5V_UP_BND                                    55UL
#define _TCPM_VSAFE5V_LOW_BND                                   47UL

#define _TCPM_VSAFE0V_UP_BND                                    8UL

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumeration Of TCPM_X HW Index
//--------------------------------------------------
typedef enum
{
    _HW_TCPM_IIC_0_SHIFT = 0x00, // Base
    _HW_TCPM_IIC_1_SHIFT = _HW_TCPM_IIC_1_REG_ST_ADDR - _HW_TCPM_IIC_0_REG_ST_ADDR,
}EnumTypeCTcpmIICHwShift;

//--------------------------------------------------
// Enumeration Of TCPM_X TCPC_X HW Index
//--------------------------------------------------
typedef enum
{
    _HW_TCPM_0_0_SHIFT = 0x00, // Base
    _HW_TCPM_0_1_SHIFT = _HW_TCPM_0_1_REG_ST_ADDR - _HW_TCPM_0_0_REG_ST_ADDR,
    _HW_TCPM_1_0_SHIFT = _HW_TCPM_1_0_REG_ST_ADDR - _HW_TCPM_0_0_REG_ST_ADDR,
    _HW_TCPM_1_1_SHIFT = _HW_TCPM_1_1_REG_ST_ADDR - _HW_TCPM_0_0_REG_ST_ADDR,
}EnumTypeCTcpmTcpcHwShift;

//--------------------------------------------------
// Enumeration Of TCPM Timer Event ID
// [Warning] The Order of the Events Should be the Same as the Order in TimerEventIDScaler.h
//--------------------------------------------------
typedef enum
{
    _SCALER_TIMER_EVENT_TCPM_SNK_HARD_RST_TIMEOUT = 0,
    _SCALER_TIMER_EVENT_TCPM_CLR_REQ_WAIT,
    _SCALER_TIMER_EVENT_TCPM_CLR_PARTNER_ALT_SUPPORT,
    _SCALER_TIMER_EVENT_TCPM_T480_ERROR_RECOVERY,
    _SCALER_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER,
    _SCALER_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER,
    _SCALER_TIMER_EVENT_TCPM_VDM_RESP_CONFLICT_TIMEOUT,
    _SCALER_TIMER_EVENT_TCPM_CLR_ATTENTION_WAIT,
    _SCALER_TIMER_EVENT_TCPM_CLR_GET_SNK_CAP_WAIT,
    _SCALER_TIMER_EVENT_TCPM_S8_HRST,
    _SCALER_TIMER_EVENT_TCPM_SEND_HARD_RST,
    _SCALER_TIMER_EVENT_TCPM_TPC_ERROR_RECOVERY,
    _SCALER_TIMER_EVENT_TCPM_CLR_PRS_WAIT,
    _SCALER_TIMER_EVENT_TCPM_CLR_DRS_WAIT,
    _SCALER_TIMER_EVENT_TCPM_CLR_VCS_WAIT,
    _SCALER_TIMER_EVENT_TCPM_CLR_VDMMSG_WAIT,
    _SCALER_TIMER_EVENT_TCPM_CLR_VDM_BUSY_FLAG,
    _SCALER_TIMER_EVENT_TCPM_DFP_START_ALT_MODE,

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    _SCALER_TIMER_EVENT_TCPM_PPS_TIMEOUT,
#endif

#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    _SCALER_TIMER_EVENT_TCPM_OVP_UVP_CHECK,
#endif

#if((_TYPE_C_PMIC_SUPPORT == _ON) && (_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON))
    _SCALER_TIMER_EVENT_TCPM_PMIC_TRACKING,
    _SCALER_TIMER_EVENT_TCPM_PMIC_POLLING_OCP,
#endif

    _SCALER_TIMER_EVENT_TCPM_INVALID,
}EnumTypeCTcpmEventID;

//--------------------------------------------------
// Enumeration Of TCPM WD Timer Event ID
//--------------------------------------------------
typedef enum
{
    _SCALER_WD_TIMER_EVENT_TCPM_CC_DEBOUNCE = 0,
    _SCALER_WD_TIMER_EVENT_TCPM_PD_DEBOUNCE,
    _SCALER_WD_TIMER_EVENT_TCPM_CBL_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_SEND_SRC_CAP,
    _SCALER_WD_TIMER_EVENT_TCPM_SENDER_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_PS_TRANSITION_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_ON_POWER,
    _SCALER_WD_TIMER_EVENT_TCPM_SRC_TURN_OFF_POWER,
    _SCALER_WD_TIMER_EVENT_TCPM_CHECK_VBUS,
    _SCALER_WD_TIMER_EVENT_TCPM_BACK_TO_READY_STATE,
    _SCALER_WD_TIMER_EVENT_TCPM_SEND_HARD_RST,
    _SCALER_WD_TIMER_EVENT_TCPM_CC_CHECK_VBUS_0V, // Should Not Cancel When PD Reset !!
    _SCALER_WD_TIMER_EVENT_TCPM_SEND_REQUEST,
    _SCALER_WD_TIMER_EVENT_TCPM_VDM_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_TCPM_SNK_SWITCH_TO_SRC,
    _SCALER_WD_TIMER_EVENT_TCPM_SEND_VCONN_ON_PSRDY,

    _SCALER_WD_TIMER_EVENT_TCPM_INVALID,
}EnumTypeCTcpmWDEventID;

//--------------------------------------------------
// Enumeration Of TCPM State
//--------------------------------------------------
typedef enum
{
    _TCPM_WAIT_TCPC_ON = 0x00,
    _TCPM_ACTIVE = 0x01,
}EnumTypeCTcpmState;

//--------------------------------------------------
// Enumeration Of CC FW State
//--------------------------------------------------
typedef enum
{
    _TCPM_CC_FW_UNATTACH = 0x01,
    _TCPM_CC_FW_CONNECTING = 0x02,
    _TCPM_CC_FW_ATTACHED = 0x03,
}EnumTypeCTcpmCcFWState;

//--------------------------------------------------
// Enumeration Of CC FSW State
//--------------------------------------------------
typedef enum
{
    _TCPM_CC_FSM_NONE = 0x00,
    _TCPM_CC_FSM_DRP_TOGGLE = 0x01,
    _TCPM_CC_FSM_UNATTACH_SRC = 0x10,
    _TCPM_CC_FSM_ATTACH_WAIT_SRC = 0x11,
    _TCPM_CC_FSM_ATTACH_SRC = 0x12,
    _TCPM_CC_FSM_UNATTACH_SNK = 0x20,
    _TCPM_CC_FSM_ATTACH_WAIT_SNK = 0x21,
    _TCPM_CC_FSM_ATTACH_SNK = 0x22,
}EnumTypeCTcpmCcFSM;

//--------------------------------------------------
// Enumeration Of TCPCI Register Table
//--------------------------------------------------
typedef enum
{
    _TCPM_TCPCI_REG_VENDER_ID = 0x00,
    _TCPM_TCPCI_REG_PRODUCT_ID = 0x02,
    _TCPM_TCPCI_REG_DEVICE_ID = 0x04,
    _TCPM_TCPCI_REG_CC_VER = 0x06,
    _TCPM_TCPCI_REG_PD_VER = 0x08,
    _TCPM_TCPCI_REG_TCPCI_VER = 0x0A,
    _TCPM_TCPCI_REG_ALERT = 0x10,
    _TCPM_TCPCI_REG_ALERT_MASK = 0x12,
    _TCPM_TCPCI_REG_PWR_STATUS_MASK = 0x14,
    _TCPM_TCPCI_REG_FAULT_STATUS_MASK = 0x15,
    _TCPM_TCPCI_REG_EXT_STATUS_MASK = 0x16,
    _TCPM_TCPCI_REG_ALERT_EXT_MASK = 0x17,
    _TCPM_TCPCI_REG_CFG_STD_OUT = 0x18,
    _TCPM_TCPCI_REG_TCPC_CTRL = 0x19,
    _TCPM_TCPCI_REG_ROLE_CTRL = 0x1A,
    _TCPM_TCPCI_REG_FAULT_CTRL = 0x1B,
    _TCPM_TCPCI_REG_PWR_CTRL = 0x1C,
    _TCPM_TCPCI_REG_CC_STATUS = 0x1D,
    _TCPM_TCPCI_REG_PWR_STATUS = 0x1E,
    _TCPM_TCPCI_REG_FAULT_STATUS = 0x1F,
    _TCPM_TCPCI_REG_EXT_STATUS = 0x20,
    _TCPM_TCPCI_REG_ALERT_EXT = 0x21,
    _TCPM_TCPCI_REG_COMMAND = 0x23,
    _TCPM_TCPCI_REG_DEVICE_CAP1 = 0x24,
    _TCPM_TCPCI_REG_DEVICE_CAP2 = 0x26,
    _TCPM_TCPCI_REG_STD_IN_CAP = 0x28,
    _TCPM_TCPCI_REG_STD_OUT_CAP = 0x29,
    _TCPM_TCPCI_REG_CFG_EXT1 = 0x2A,
    _TCPM_TCPCI_REG_GENERIC_TIMER = 0x2C,
    _TCPM_TCPCI_REG_MSG_HEADER_INFO = 0x2E,
    _TCPM_TCPCI_REG_RCV_DETECT = 0x2F,
    _TCPM_TCPCI_REG_RX_BUF = 0x30,
    _TCPM_TCPCI_REG_TRANSMIT = 0x50,
    _TCPM_TCPCI_REG_TX_BUF = 0x51,
    _TCPM_TCPCI_REG_VBUS_VOL = 0x70,
    _TCPM_TCPCI_REG_SNK_DISC_THR = 0x72,
    _TCPM_TCPCI_REG_STOP_DISC_THR = 0x74,
    _TCPM_TCPCI_REG_VOL_ALARM_H = 0x76,
    _TCPM_TCPCI_REG_VOL_ALARM_L = 0x78,
    _TCPM_TCPCI_REG_VBUS_NDEF_TARGET = 0x7A,
    _TCPM_TCPCI_REG_DEVICE_CAP3 = 0x7C,

/*
    _TCPM_TCPCI_REG_A0 = 0xA0,       // FUSB307B : VCONN_OCP
    _TCPM_TCPCI_REG_A2 = 0xA2,       // FUSB307B : RESET
    _TCPM_TCPCI_REG_A4 = 0xA4,       // FUSB307B : GPIO_1_CFG
    _TCPM_TCPCI_REG_A5 = 0xA5,       // FUSB307B : GPIO_2_CFG
    _TCPM_TCPCI_REG_A6 = 0xA6,       // FUSB307B : GPIO_STAT
    _TCPM_TCPCI_REG_A7 = 0xA7,       // FUSB307B : DRP_TOGGLE
    _TCPM_TCPCI_REG_B0 = 0xB0,       // FUSB307B : SNK_TRANSMIT
    _TCPM_TCPCI_REG_B1 = 0xB1,       // FUSB307B : SRC_FRSWAP
    _TCPM_TCPCI_REG_B2 = 0xB2,       // FUSB307B : SNK_FRSWAP
    _TCPM_TCPCI_REG_B3 = 0xB3,       // FUSB307B : VD_ALERT_STATUS
    _TCPM_TCPCI_REG_B4 = 0xB4,       // FUSB307B : VD_ALERT_MASK
*/
}EnumTypeCTcpmTcpciReg;

//--------------------------------------------------
// Enumeration Of TCPCi Alert Type (Reg : 0x10~11H, 0x12~13H)
//--------------------------------------------------
typedef enum
{
    _TCPM_TCPCI_ALERT_NONE = 0x00,
    _TCPM_TCPCI_ALERT_CC_STATUS = _BIT0,
    _TCPM_TCPCI_ALERT_PWR_STATUS = _BIT1,
    _TCPM_TCPCI_ALERT_RX_RCV_SOP = _BIT2,
    _TCPM_TCPCI_ALERT_RX_HRST = _BIT3,
    _TCPM_TCPCI_ALERT_TX_FAIL = _BIT4,
    _TCPM_TCPCI_ALERT_TX_DISCARD = _BIT5,
    _TCPM_TCPCI_ALERT_TX_SUCCESS = _BIT6,
    _TCPM_TCPCI_ALERT_VBUS_ALRM_H = _BIT7,
    _TCPM_TCPCI_ALERT_VBUS_ALRM_L = _BIT8,
    _TCPM_TCPCI_ALERT_FAULT = _BIT9,
    _TCPM_TCPCI_ALERT_RX_OVERFLOW = _BIT10,
    _TCPM_TCPCI_ALERT_SNK_DISC = _BIT11,
    _TCPM_TCPCI_ALERT_RX_SOP_BEGIN = _BIT12,
    _TCPM_TCPCI_ALERT_EXT_STATUS = _BIT13,
    _TCPM_TCPCI_ALERT_ALERT_EXT = _BIT14,
    _TCPM_TCPCI_ALERT_VENDOR_DEF = _BIT15,
    _TCPM_TCPCI_ALERT_ALL = 0xFFFF,
}EnumTypeCTcpmTcpciAlertType;

//--------------------------------------------------
// Enumeration Of TCPCi Power Control Type (Reg : 0x1CH)
//--------------------------------------------------
typedef enum
{
    _TCPM_TCPCI_PWR_CTRL_VCONN_EN = _BIT0,
    _TCPM_TCPCI_PWR_CTRL_VCONN_PWR = _BIT1,
    _TCPM_TCPCI_PWR_CTRL_FRC_DISCH = _BIT2,
    _TCPM_TCPCI_PWR_CTRL_BLD_DISCH = _BIT3,
    _TCPM_TCPCI_PWR_CTRL_AUTO_DISCH = _BIT4,
    _TCPM_TCPCI_PWR_CTRL_VBUS_ALRM = _BIT5,
    _TCPM_TCPCI_PWR_CTRL_VBUS_MNT = _BIT6,
    _TCPM_TCPCI_PWR_CTRL_FRS_EN = _BIT7,
}EnumTypeCTcpmTcpciPwrCtrlType;

//--------------------------------------------------
// Enumeration Of TCPCi CC Status Field (Reg : 0x1DH)
//--------------------------------------------------
typedef enum
{
    _TCPM_TCPCI_CC_STAT_CC1_STATE = (_BIT1 | _BIT0),
    _TCPM_TCPCI_CC_STAT_CC2_STATE = (_BIT3 | _BIT2),
    _TCPM_TCPCI_CC_STAT_CONNECT_RESULT = _BIT4,
    _TCPM_TCPCI_CC_STAT_L4C = _BIT5,
}EnumTypeCTcpmTcpciCcStatType;

//--------------------------------------------------
// Enumeration Of TCPCi Power Status & Mask Field (Reg : 0x14H / 0x1EH)
//--------------------------------------------------
typedef enum
{
    _TCPM_TCPCI_PWR_STAT_SNK_VBUS = _BIT0,
    _TCPM_TCPCI_PWR_STAT_VCONN_PRESENT = _BIT1,
    _TCPM_TCPCI_PWR_STAT_VBUS_PRESENT = _BIT2,
    _TCPM_TCPCI_PWR_STAT_VBUS_DETECT = _BIT3,
    _TCPM_TCPCI_PWR_STAT_SRC_VBUS = _BIT4,
    _TCPM_TCPCI_PWR_STAT_SRC_HV = _BIT5,
    _TCPM_TCPCI_PWR_STAT_INIT_STATUS = _BIT6,
    _TCPM_TCPCI_PWR_STAT_DEBUG_ACC = _BIT7,
}EnumTypeCTcpmTcpciPwrStatType;

//--------------------------------------------------
// Enumeration Of TCPCi Fault Status & Mask Field (Reg : 0x15H / 0x1FH)
//--------------------------------------------------
typedef enum
{
    _TCPM_TCPCI_FT_STAT_I2C_ERR = _BIT0,
    _TCPM_TCPCI_FT_STAT_VCONN_OCP = _BIT1,
    _TCPM_TCPCI_FT_STAT_VBUS_OVP = _BIT2,
    _TCPM_TCPCI_FT_STAT_VBUS_OCP = _BIT3,
    _TCPM_TCPCI_FT_STAT_FORCE_VBUS_DISCHARGE = _BIT4,
    _TCPM_TCPCI_FT_STAT_AUTO_DISCHARGE_FAILED = _BIT5,
    _TCPM_TCPCI_FT_STAT_FORCE_OFF_VBUS = _BIT6,
    _TCPM_TCPCI_FT_STAT_DEBUG_ALL_REG_RESET_TO_DEFAULT = _BIT7,
}EnumTypeCTcpmTcpciFtStatType;

//--------------------------------------------------
// Enumeration Of TCPCi Command Type (Reg 0x23H)
//--------------------------------------------------
typedef enum
{
    _TCPM_TCPCI_CMD_WAKE_I2C = 0x11,
    _TCPM_TCPCI_CMD_DIS_VBUS_DET = 0x22,
    _TCPM_TCPCI_CMD_EN_VBUS_DET = 0x33,
    _TCPM_TCPCI_CMD_DIS_SNK_VBUS = 0x44,
    _TCPM_TCPCI_CMD_EN_SNK_VBUS = 0x55,
    _TCPM_TCPCI_CMD_DIS_SRC_VBUS = 0x66,
    _TCPM_TCPCI_CMD_EN_SRC_5V = 0x77,
    _TCPM_TCPCI_CMD_EN_SRC_HV = 0x88,
    _TCPM_TCPCI_CMD_LOOK_4_CONNECTION = 0x99,
    _TCPM_TCPCI_CMD_RX_1_MORE = 0xBB,
    _TCPM_TCPCI_CMD_SEND_FRS_SIGNAL = 0xCC,
    _TCPM_TCPCI_CMD_RESET_TX_BUFFER = 0xDD,
    _TCPM_TCPCI_CMD_RESET_RX_BUFFER = 0xEE,
    _TCPM_TCPCI_CMD_I2C_IDLE = 0xFF,
}EnumTypeCTcpmTcpciCmdType;

//--------------------------------------------------
// Enumeration Of TCPCi Receive Detect Type (Reg 0x2FH)
//--------------------------------------------------
typedef enum
{
    _TCPM_TCPCI_RCV_DET_SOP = _BIT0,
    _TCPM_TCPCI_RCV_DET_SOP_P = _BIT1,
    _TCPM_TCPCI_RCV_DET_SOP_PP = _BIT2,
    _TCPM_TCPCI_RCV_DET_SOP_DBG_P = _BIT3,
    _TCPM_TCPCI_RCV_DET_SOP_DBG_PP = _BIT4,
    _TCPM_TCPCI_RCV_DET_HRST = _BIT5,
    _TCPM_TCPCI_RCV_DET_CRST = _BIT6,
    _TCPM_TCPCI_RCV_DET_AUTO_DISABLE = _BIT7,
}EnumTypeCTcpmTcpciRcvDetType;

//--------------------------------------------------
// Enumeration Of TCPCi Rx Frame Type (Reg 0x30H)
//--------------------------------------------------
typedef enum
{
    _TCPM_TCPCI_RX_FRAME_TYPE_SOP = 0x00,
    _TCPM_TCPCI_RX_FRAME_TYPE_SOP_P = 0X01,
    _TCPM_TCPCI_RX_FRAME_TYPE_SOP_PP = 0x02,
    _TCPM_TCPCI_RX_FRAME_TYPE_SOP_DBG_P = 0x03,
    _TCPM_TCPCI_RX_FRAME_TYPE_SOP_DBG_PP = 0x04,
    _TCPM_TCPCI_RX_FRAME_TYPE_CRST = 0x06,
}EnumTypeCTcpmTcpciRxFrameType;

// TCPM Hw Index Struct
typedef struct
{
    EnumTypeCTcpmIICHwShift enumTcpmIICHwShift;
    EnumTypeCTcpmTcpcHwShift enumTcpmTcpcHwShift;
}StructTypeCTcpmHwShift;

// TCPM Information Struct
typedef struct
{
    EnumTypeCTcpmState enumTcpmState;
    // -----------------------------
    BYTE b2TcpmUsbType : 2;
    BYTE b2TcpmUsbSpeed : 2;
    BYTE b2TcpmUsbRole : 2;
    BYTE b1TcpmConnectorType : 1;
}StructTypeCTcpmInfo;

// TCPM Record Device (TCPC) Information Struct
typedef struct
{
    BYTE ucTcpcType;
    // -----------------------------
    BYTE ucSlaveAddr;
    // -----------------------------
    WORD usAlertValid;
    // -----------------------------
    WORD usVendorID;            // 0x00~01  Vendor ID
    // -----------------------------
    WORD usProductID;           // 0x02~03  Product ID
    // -----------------------------
    WORD usDeviceID;            // 0x04~05  Device ID
    // -----------------------------
    WORD usTypeCVer;            // 0x06~07  TypeC Spec Version
    // -----------------------------
    WORD usPdVer;               // 0x08~09  PD Sepc Version
    // -----------------------------
    WORD usInterfaceVer;        // 0x0A~0B  Interface (TCPCI) Spec Verion
    // -----------------------------
    WORD usAlertMask;           // 0x12~13  Alert Mask
    // -----------------------------
    BYTE ucPowerStatusMask;     // 0x14     Power Status Mask
    // -----------------------------
    BYTE ucFaultStatusMask;     // 0x15     Fault Status Mask
    // -----------------------------
    BYTE ucTcpcControl;         // 0x19     TCPC Control
    // -----------------------------
    BYTE ucRoleControl;         // 0x1A     Role Control
    // -----------------------------
    BYTE ucFaultControl;        // 0x1B     Fault Control
    // -----------------------------
    BYTE ucPowerControl;        // 0x1C     Power Control
    // -----------------------------
    BYTE ucCcStatus;            // 0x1D     CC Status
    // -----------------------------
    BYTE ucFaultStatus;         // 0x1F     Fault Status
    // -----------------------------
    WORD usDeviceCap1;          // 0x24~25  Device Capability 1
    // -----------------------------
    WORD usDeviceCap2;          // 0x26~27  Device Capability 2
    // -----------------------------
    BYTE ucStdInputCap;         // 0x28     Standard Input Capability
    // -----------------------------
    BYTE ucStdOutputCap;        // 0x29     Standard Output Capability
    // -----------------------------
    WORD usDeviceCap3;          // 0x7C~7D  Device Capability
}StructTypeCTcpmDeviceInfo;

// TCPM Cross CC/PD Top Information Struct
typedef struct
{
    BYTE b1PowerRole : 1;
    BYTE b1DataRole : 1;
    BYTE b1VconnRole : 1;
    BYTE b1SrcVbus : 1;
    BYTE b1SnkVbus : 1;
    BYTE b1SrcVconn : 1;
    // -----------------------------
    EnumTypeCOrientation enumOrientation;
}StructTypeCTcpmTopInfo;

// TCPM CC Related Information Struct
typedef struct
{
    EnumTypeCTcpmCcFWState enumTcpmCcFwState;
    // -----------------------------
    EnumTypeCTcpmCcFSM enumTcpmCcFSM;
    // -----------------------------
    BYTE ucDischargeCount;
    // -----------------------------
    BYTE b1ConnectEn : 1;
    BYTE b2PortRole : 2;
    BYTE b2DrpPrefer : 2;
    BYTE b2RpDefValue : 2;
    BYTE b1CCAttached : 1;
    // -----------------------------
    BYTE b1SourceDet : 1;
    BYTE b1SinkDet5V : 1;
    BYTE b1SinkUnattachDbc : 1;
    BYTE b1SinkDet : 1;
    BYTE b1SourceDet0V : 1;
    BYTE b1SourceDet5V : 1;
    BYTE b1CcStatusChange : 1;
    BYTE b1CcDebounce : 1;
    // -----------------------------
    BYTE b1RaExist : 1;
    BYTE b1ErrorRecovery : 1;
    BYTE b1ResetFlag : 1;
    BYTE b1SnkDetCcUnattach : 1; // For On-Semi Sink Not Detect Unattach when During PD Msg.
    // -----------------------------
    WORD b10DefCurrent : 10;
}StructTypeCTcpmCcInfo;

// TCPM PD Related Information Struct
typedef struct
{
    EnumTypeCPDState enumTcpmPdFwState;
    // -----------------------------
    EnumTypeCPDSubState enumTcpmPdSubState;
    // -----------------------------
    EnumDPAmsState enumTcpmPdAmsStatus;
    // -----------------------------
    EnumTypeCPDCableState enumTcpmPdCableState;
    // -----------------------------
    EnumTypeCPDAltModeState enumTcpmAltModeState;
    // -----------------------------
    BYTE b6SrcCapCnt : 6;
    BYTE b2HardRstCnt : 2;
    // -----------------------------
    BYTE b4CheckVbusCnt : 4;
    BYTE b4BistMode : 4;
    // -----------------------------
    BYTE b3PDNumOfSPRSrcCap : 3;
    BYTE b3PDNumOfEPRSrcCap : 3;
    BYTE b2SpecVersion : 2;
    // -----------------------------
    BYTE b3PDNumOfSPRSnkCap : 3;
    BYTE b3PDNumOfEPRSnkCap : 3;
    BYTE b1FunctionEnable : 1;
    BYTE b1PDPRSwapReject : 1;
    // -----------------------------
    BYTE b1PDDRSwapReject : 1;
    BYTE b1PDVconnSwapReject : 1;
    BYTE b1GetSnkCapSent : 1;
    BYTE b1GetSrcCapSent : 1;
    BYTE b1RcvSnkCap : 1;
    BYTE b1RcvSrcCap : 1;
    BYTE b1ReqWait : 1;
    BYTE b1PRSwapWait : 1;
    // -----------------------------
    BYTE b1DRSwapWait : 1;
    BYTE b1VCSwapWait : 1;
    BYTE b1HRST_Pwr_Off : 1;
    BYTE b1PRS_Processing : 1;
    BYTE b1InteropS8 : 1;
    BYTE b1AlertSent : 1;
    BYTE b1GetSnkCapWait : 1;
    BYTE b1VdmMsgWait : 1;
    // -----------------------------
    BYTE b5DiscoverIdRetryFailCnt : 5;
    BYTE b1PDPowerContract : 1;
    BYTE b1UnconstrainedPower : 1;
    BYTE b1VdmBusy : 1;
    // -----------------------------
    BYTE ucTargetVolRDO;
    // -----------------------------
    StructTypeCPDO pstSrcPDO[_MAX_DATA_OBJ_CNT];
    // -----------------------------
    StructTypeCPDO pstSnkPDO[_MAX_DATA_OBJ_CNT];
    // -----------------------------
    StructTypeCUserRDO stRDO;
    // -----------------------------
    StructTypeCPdoStatus stPDOStatus;
    // -----------------------------
    EnumTypeCReqType enumReqType;
    // -----------------------------
    StructTypeCSnkInfo stSnkInfo;
    // -----------------------------
    StructTypeCEPRModeInfo stEprModeInfo;
    // -----------------------------
    StructTypeCPdEvent stPdEvent;
    // -----------------------------
    WORD b10WDTimeLeft : 10;
    WORD b1SrcAcceptSwapToSnk : 1;
    WORD b1SrcRequestSwapToSnk : 1;
    WORD b1SnkAcceptSwapToSrc : 1;
    WORD b1SnkRequestSwapToSrc : 1;
    WORD b1DfpSwapToUfp : 1;
    WORD b1UfpSwapToDfp : 1;
    // -----------------------------
    BYTE b1PPSSupport : 1;
    BYTE b2cBehaviorType : 2;
    BYTE b1Valid : 1;
    BYTE b1WDEventValid : 1;
    BYTE b1WDEventTriggered : 1;
    // -----------------------------
    EnumTypeCTcpmEventID enumEventID;
    // -----------------------------
    EnumScalerWDTimerEventID enumWDEventID;
    // -----------------------------
    WORD usEventTime;
    // -----------------------------
    WORD usWDEventTime;
}StructTypeCTcpmPdInfo;

// TCPM PD Rx Information Struct
typedef struct
{
    BYTE ucRcvMsg;
    // -----------------------------
    BYTE b4MsgID_SOP : 4;
    BYTE b4MsgID_SOP_P : 4;
    // -----------------------------
    BYTE b4MsgID_SOP_PP : 4;
    BYTE b3RcvNodCnt : 3;
    // -----------------------------
    StructTypeCExtMsgInfo stExtMsgInfo;
    // -----------------------------
}StructTypeCTcpmPdRxInfo;

// TCPM PD Tx Information Struct
typedef struct
{
    EnumTypeCTxRetryFailEvent enumTxRetryFailEvent;
    // -----------------------------
    BYTE b4MsgID_SOP : 4;
    BYTE b4MsgID_SOP_P : 4;
    // -----------------------------
    BYTE b4MsgID_SOP_PP : 4;
    BYTE b1IntOverWrite : 1;
}StructTypeCTcpmPdTxInfo;

// TCPM PD Related Information Struct
typedef struct
{
    EnumTypeCPDSrcCapValid enumSrcCapValid;
    EnumTypeCPDSvdmVersion enumSvdmVersion;
    EnumTypeCPDDpamVersion enumDpamVersion;
    // -----------------------------
    StructTypeCPDO pstSrcPDO[_MAX_DATA_OBJ_CNT];
    // -----------------------------
    StructTypeCPDO pstSnkPDO[_MAX_DATA_OBJ_CNT];
    // -----------------------------
    StructTypeCSnkRDO stRDO;
    // -----------------------------
    StructTypeCStatusEvent stStatusEvent;
    // -----------------------------
    StructTypeCAlertEvent stAlertEvent;
    // -----------------------------
    BYTE b3NumOfSrcCap : 3;
    BYTE b3NumOfSnkCap : 3;
    BYTE b2FrsCurrent : 2;
    // -----------------------------
    BYTE b1DualRolePower : 1;
    BYTE b1DualRoleData : 1;
    BYTE b1SuspendSupport : 1;
    BYTE b1ExtPower : 1;
    BYTE b1UsbCapable : 1;
    BYTE b1UnchkSupport : 1;
    BYTE b1PartnerEPRCapable : 1;
    BYTE b1HigherCap : 1;
    // -----------------------------
    BYTE b1ALTSupport : 1;
}StructTypeCTcpmPdPartnerInfo;

// TCPM PD DP Alt Mode Information Struct
typedef struct
{
    BYTE b3ObjPos : 3;
    BYTE b1MultiFunction : 1;
    BYTE b1MultiFunctionChange : 1;
    BYTE b1MultiFunctionChangeDone : 1;
    BYTE b1SvidSearchFinish : 1;
    BYTE b1EnterMode : 1;
    // -----------------------------
    BYTE b1Config : 1;
    BYTE b1TargetConfig : 1;
    BYTE b1WaitConfig : 1;
    BYTE b1ExitMode : 1;
    BYTE b1AttentionWait : 1;
    BYTE b1ForceHpdIrq : 1;
    // -----------------------------
    BYTE ucPartnerPinAssignmentCap;
    // -----------------------------
    EnumTypeCPinCfgType enumPinAssignment;
    // -----------------------------
    EnumTypeCPinCfgCapType enumPinAssignmentCap;
    // -----------------------------
    StructTypeCHpdQueue stHpdQueue;
    // -----------------------------
    StructTypeCDpStatusInfo stDpStatusInfo;
    // -----------------------------
}StructTypeCTcpmPdDpamInfo;

// TCPM PD VDM Information Struct
typedef struct
{
    BYTE ucRcvVdmMsg;
    // -----------------------------
    BYTE ucVdmSVID_H;
    // -----------------------------
    BYTE ucVdmSVID_L;
    // -----------------------------
    BYTE b3VdmObjPos : 3;
    BYTE b1AltModeFunc : 1;
    BYTE b1RcvVdmType : 1;
    BYTE b2VdmRespConflictCnt : 2;
    BYTE b1DpamSupport : 1;
    // -----------------------------
    BYTE b1ModalOperationSupport : 1;
    BYTE b1PartnerInitAltMode : 1;
    BYTE b2PartnerVdmNoRespCnt : 2;
    BYTE b2CblVdmNoRespCnt : 2;
    BYTE b3VdmBusyCnt : 3;
    // -----------------------------
    EnumTypeCUFPProductType enumUFPProductType;
    // -----------------------------
    EnumTypeCDFPProductType enumDFPProductType;
    // -----------------------------
    StructTypeCTcpmPdDpamInfo stDpamInfo;
    // -----------------------------
}StructTypeCTcpmPdVdmInfo;

// TCPM Power Related Information Struct
typedef struct
{
    StructTypeCPowerProtectInfo pstPowerProtectInfo[_MAX_DATA_OBJ_CNT];
    BYTE b1VbusStatus : 1;
#if(_PORT_CTRL_TCPM_OCP_PROTECT_BY_TCPC == _ON)
    BYTE b1OcpProtectByTcpc : 1;
#endif
#if(_PORT_CTRL_TCPM_OVP_UVP_SUPPORT == _ON)
    BYTE b1OvpUvpSupport : 1;
    BYTE b1OvpUvpCheck : 1;
    BYTE ucOvpThreshold;
    BYTE ucUvpThreshold;
    BYTE ucOvpProtectDebounce;
    BYTE ucUvpProtectDebounce;
    WORD usOvpVol;
    WORD usUvpVol;
#endif
    WORD usMaxPower;
    WORD usReqPower;
    WORD usOutputVol;
    WORD b10OutputCur : 10;
    WORD usOcpCurrent;
}StructTypeCTcpmPowerInfo;

#if(_TYPE_C_PMIC_SUPPORT == _ON)
// TCPM PMIC Related Struct
typedef struct
{
    BYTE ucOcpProtectDebounce;
    // -----------------------------
    BYTE b1PmicSupport : 1;
    BYTE b2PmicOcpProtectMethod : 2;

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
    BYTE ucOcpCurrentValue;
    BYTE ucOcpDelayShutdown;
    WORD b12OcpByPollingCurrent : 12;
    WORD b1PollingOcpProtectFlag : 1;
#endif

#if(_PORT_CTRL_TCPM_PMIC_CHECK_SUPPORT == _ON)
    WORD b1OutputEnable : 1;
    WORD b1BiDirMode : 1;
    WORD b1ProtectValid : 1;
    WORD b1ProtectTimerCheck : 1;
    WORD b1ProtectTimerStart : 1;
#endif

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    WORD b1GetOmfInfoFlag : 1;
    EnumTypeCPmicOperationMode enumOmfInfo;
#endif

    // -----------------------------
    EnumTypeCPDPdoType enumOutputPdoType;
    // -----------------------------

}StructTypeCTcpmPmicControl;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructTypeCTcpmHwShift g_pstTypeCTcpmHwShift[_TCPM_PORT_VALID];
extern volatile StructTypeCTcpmInfo g_pstTypeCTcpmInfo[_TCPM_PORT_VALID];
extern volatile StructTypeCTcpmDeviceInfo g_pstTypeCTcpmDeviceInfo[_TCPM_PORT_VALID];
extern volatile StructTypeCTcpmTopInfo g_pstTypeCTcpmTopInfo[_TCPM_PORT_VALID];
extern volatile StructTypeCTcpmCcInfo g_pstTypeCTcpmCcInfo[_TCPM_PORT_VALID];
extern volatile StructTypeCTcpmPdInfo g_pstTypeCTcpmPdInfo[_TCPM_PORT_VALID];
extern volatile StructTypeCTcpmPdPartnerInfo g_pstTypeCTcpmPdPartnerInfo[_TCPM_PORT_VALID];
extern volatile StructTypeCTcpmPdVdmInfo g_pstTypeCTcpmPdVdmInfo[_TCPM_PORT_VALID];
extern volatile StructTypeCTcpmPdRxInfo g_pstTypeCTcpmPdRxInfo[_TCPM_PORT_VALID];
extern volatile StructTypeCTcpmPdTxInfo g_pstTypeCTcpmPdTxInfo[_TCPM_PORT_VALID];
extern volatile StructTypeCTcpmPowerInfo g_pstTypeCTcpmPowerInfo[_TCPM_PORT_VALID];

#if(_TYPE_C_PMIC_SUPPORT == _ON)
extern volatile StructTypeCTcpmPmicControl g_pstTypeCTcpmPmicControl[_TCPM_PORT_VALID];
#endif

extern volatile StructTypeCCableStatus g_pstTypeCTcpmPdCableInfo[_TCPM_PORT_VALID];
extern volatile StructTypeCCableInfoForDpcd g_pstTypeCTcpmPdCableInfoForDpcd[_TCPM_PORT_VALID];
extern volatile StructTypeCStatusEvent g_pstTypeCTcpmPdStatusEvent[_TCPM_PORT_VALID];
extern volatile StructTypeCAlertEvent g_pstTypeCTcpmPdAlertEvent[_TCPM_PORT_VALID];

extern volatile BYTE g_pucTypeCTcpmRxBuffer_EXINT[(_MAX_DATA_OBJ_CNT * 4) + 4];
extern volatile BYTE g_pucTypeCTcpmPdDataObj_EXINT[_MAX_DATA_OBJ_CNT * 4];
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// Main Loop
extern void ScalerTypeCTcpmTimerEventProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCTcpmEventID enumTcpmEventID);
extern void ScalerTypeCTcpmPdPushHpd(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime);

// EXINT0
extern void ScalerTypeCTcpmPdPushHpd_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime);

// WDINT
extern void ScalerTypeCTcpmWDTimerEventProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCTcpmWDEventID enumTcpmWDEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);

#endif // End of #if(_PORT_CTRL_TCPM_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

