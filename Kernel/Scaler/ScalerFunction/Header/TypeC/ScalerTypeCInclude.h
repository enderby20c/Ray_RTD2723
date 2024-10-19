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
// ID Code      : ScalerTypeCInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Type C Debug Setting
//--------------------------------------------------
#define _TYPE_C_POWER_DEBUG                             _OFF
#define _TYPE_C_0_CC_FW_DEBUG                           _OFF
#define _TYPE_C_0_PD_FW_DEBUG                           _OFF
#define _TYPE_C_1_CC_FW_DEBUG                           _OFF
#define _TYPE_C_1_PD_FW_DEBUG                           _OFF

//--------------------------------------------------
// Type C Related Define list
//--------------------------------------------------
// TYPE C Connection Mode
#define _TYPE_C_HW_MODE                                 0x00
#define _TYPE_C_FW_MODE                                 0x01

// Definitions of TYPE C Debounce Type
#define _TYPE_C_CC                                      0x00
#define _TYPE_C_PD                                      0x01

// Definitions of CONNECT / DISCONNECT
#define _TYPE_C_DISCONNECT                              0x00
#define _TYPE_C_CONNECT                                 0x01

// Definitions of Type-C PD Behavior Type (DisplayPort Capability)
#define _TYPE_C_DP_NONE                                 0x00
#define _TYPE_C_DP_RX                                   0x01
#define _TYPE_C_DP_TX                                   0x02

// PD Related Define
// Definitions of Discover ID No Retry
#define _DISCOVER_ID_NO_RETRY                           _FALSE   // Fix Lecroy [COMMON.CHECK.PD.2 Check Message Header]

// Definitions of SVID
#define _PD_SID                                         0xFF00
#define _DP_SID                                         0xFF01
#define _TBT3_SID                                       0x8087
#define _LENOVO_VID                                     0x17EF
#define _ACER_VID                                       0x0502
#define _HP_VID                                         0x03F0
#define _DELL_VID                                       0x413C

// POWER OPTION
#define _VCONN_1W                                       0
#define _VCONN_1P5W                                     1
#define _VCONN_2W                                       2
#define _VCONN_3W                                       3
#define _VCONN_4W                                       4
#define _VCONN_5W                                       5
#define _VCONN_6W                                       6

#define _VCONN_REQUIRE                                  _FALSE
#define _VCONN_POW                                      _VCONN_1W

// USB Related Capability
#define _USB_SUSPEND                                    _FALSE

// Version Define
#define _PD_HW_VERSION                                  0x00
#define _PD_FW_VERSION                                  0x00

// The Revision and Version of PD Specification
#define _PD_SPEC_REVISION                               0x31
#define _PD_SPEC_VERSION                                0x15

// Refer to Port Partner Capability, e.g. DRP and DRD. This setting is for Compatibility.
#define _REFER_TO_PORT_PARTNER_CAP                      _TRUE

// PD3.0 Related Capability
#define _MANUFACTURER_INFO_SUPPORT                      _TRUE

// Definitions of Specification Counters
#define _MAX_SRC_CAP_CNT                                60
#define _MAX_HW_NO_RETRY_CBL_DISCOVER_ID_RETRY_FAIL_CNT 20      // Max FW Retry Fail Cnt When HW Don't Retry to Send Discover Id When No GoodCRC Received
#define _MAX_HW_RETRY_CBL_DISCOVER_ID_RETRY_FAIL_CNT    5       // Max FW Retry Fail Cnt When HW Retry to Send Discover Id When No GoodCRC Received
#define _MAX_HARD_RST_CNT                               2
#define _MAX_LENOVO_ATTN_CNT                            5
#define _MAX_VDM_NO_RESP_CNT                            3
#define _MAX_VDM_BUSY_CNT                               5

// Definitions of FW Usage Counters
#define _MAX_DATA_OBJ_CNT                               11

// Definitions of Specification Timer
#define _SRC_INIT_AMS_TIMER                             18      // 16 ~ 20ms (Source Wait After switch Rp to TxSinkNG)
#define _SWAP_SRC_START_TIMER                           20      // After PR_SWAP SRC should Wait At Least 20ms, After Power On, Cable Will Be Stable After 50ms
#define _PD2_SENDER_RESP_TIMER                          24      // PD2.0 : 24 ~ 30ms
#define _PD3_SENDER_RESP_TIMER                          27      // PD3.1 : 27 ~ 33ms
#define _SRC_ADJUST_POWER_TIMER                         27      // 25 ~ 35ms
#define _VDM_MODE_ENTRY_TIMER                           40      // 40 ~ 50ms
#define _VDM_MODE_EXIT_TIMER                            40      // 40 ~ 50ms
#define _VDM_BUSY_TIMER                                 50      // At Least 50ms
#define _SINK_WAIT_CAP_TIMER                            400     // 310 ~ 620ms
#define _SRC_RECOVER_TIMER                              700     // 660 ~ 1000ms
#define _WAIT_TIMER                                     100
#define _WAIT_VCONN_ON_TIMER                            100
#define _PS_TRANSITION_TIMER                            500     // 450 ~ 550ms
#define _PS_SRC_ON_TIMER                                400     // 390 ~ 480ms
#define _PS_SRC_OFF_TIMER                               750     // 750 ~ 920ms
#define _ATTENTION_SPACING_TIMER                        10      // (ms) DP Alt Mode Standard 5.2.2 Gap Between Attention
#define _SRC_SEND_PS_RDY_FIX_VOLTAGE_TIMER              35      // 35ms, Depends on tSrcReady (SPR : 285ms) : 35ms * 8 (Check Vbus Count) <= 285ms
#define _SRC_SEND_PS_RDY_PPS_MODE_TIMER                 3       // 3ms, Depends on tPpsSrcTransSmall (25ms) : 3ms * 8 (Check Vbus Count) <= 25ms
#define _SRC_SEND_PS_RDY_EPR_FIX_VOLTAGE_TIMER          90      // 90ms, Depends on tSrcReady (EPR : 720ms) : 90ms * 8 (Check Vbus Count) <= 720ms
#define _SRC_SEND_PS_RDY_EPR_AVS_MODE_TIMER             6       // 6ms, Depends on tAvsSrcTransSmall (50ms) : 6ms * 8 (Check Vbus Count) <= 50ms
#define _UNATTACH_VBUS_DISCHARGE_TIMER                  10      // Same as tPDDebounce (min)
#define _SNK_HARD_RST_TIMER                             3000
#define _SRC_EPR_KEEP_ALIVE_TIMER                       750     // 750 ~ 1000ms
#define _CHUNK_SENDER_REQ_TIMER                         24      // 24 ~ 30ms

// Definition of FW Usage Timer to Wait for Receiving Subsequent AMS, ex: Get_Status Msg., Timeout: Send Hard Reset.
#define _ALERT_WAIT_TIMER                               35      // (ms) Not Defined by Spec.

// Definitions of FW Usage Timer for Partner Support ALT Mode Detection
#define _PARTNER_ALT_SUPPORT_TIMER                      2000    // Wait 2 Sec to Detect Whether Partner Support ALT Mode

// FW Solution For Lenovol T480, Wait 1s to Do Error Recovery
#define _T480_ERROR_RECOVERY_TIMER                      1000    // Wait 1 Sec to Do Error Recovery

// Definitions of FW WD Timer Event Max Time
#define _MAX_WD_EVENT_TIME                              250     // (ms)

// Definitions of FW Usage Timer
#define _PD_SEND_MSG_TIMEOUT                            10

// Definitions of Other Default Value
#define _PD_DEFAULT_MAX_CUR                             300      // 300 * 10mA = 3.0A

// Definition of PD Capability
#define _SRC_CAP_NO_RETRY                               _FALSE   // [TEST.PD.PROT.SRC3.1] : All PD Message Should Implement 0.9~1.1ms Retry
#define _HIGHER_CAP                                     _FALSE
#define _GIVE_BACK                                      _FALSE
#define _UNCHUNK_SUPPORT                                _FALSE

// Definitions of PD Data(USB) DFP/UFP Role
#define _PD_DATA_UFP                                    0x00
#define _PD_DATA_DFP                                    0x01

// Definitions of PD Power SRC/SNK Role
#define _PD_POWER_SNK                                   0x00
#define _PD_POWER_SRC                                   0x01

// Definitions of PD Vconn SRC/SNK Role
#define _PD_VCONN_SRC                                   0x00
#define _PD_VCONN_NOT_SRC                               0x01

// Definitions of PD DP Alt. Mode Tx/Rx Role
#define _PD_DP_TX                                       0x00
#define _PD_DP_RX                                       0x01

// Definitions of PD Cable Plug Role
#define _PD_DEVICE                                      0x00
#define _PD_CABLE                                       0x01

// Definitions of DP Alt Mode USB/DP Config
#define _PD_USB_CONFIG                                  0x00
#define _PD_DP_CONFIG                                   0x01

// Definition of Hp Alt Mode SysEvent Queue Size
#define _TYPE_C_PD_HP_SYS_EVENT_QUEUE_SIZE              6

// Definitions of PD SinkTxOK/NG
#define _PD_SINK_TX_NG                                  _BIT6
#define _PD_SINK_TX_OK                                  _BIT7

// Definitions of PD VDM Type
#define _PD_UNSTRUCTURED_VDM                            0x00
#define _PD_STRUCTURED_VDM                              0x01

//--------------------------------------------------
// Type C PD Related Definition
//--------------------------------------------------
#define _HPD_QUEUE_DEPTH                                4

//--------------------------------------------------
// Type C Power Related Macro
//--------------------------------------------------
#define GET_TYPE_C_SYS_MODE_STATUS()                    (g_enumTypeCSysModeStatus)
#define SET_TYPE_C_SYS_MODE_STATUS(x)                   (g_enumTypeCSysModeStatus = (x))

#define GET_TYPE_C_CC_ATTACH(x)                         (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex(x)].enumAttachStatus)
#define SET_TYPE_C_CC_ATTACH(x, y)                      (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex(x)].enumAttachStatus = (y))

#define GET_TYPE_C_CC_ATTACH_EXINT(x)                   (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_EXINT0(x)].enumAttachStatus)
#define SET_TYPE_C_CC_ATTACH_EXINT(x, y)                (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_EXINT0(x)].enumAttachStatus = (y))

#define GET_TYPE_C_CC_ATTACH_WDINT(x)                   (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_WDINT(x)].enumAttachStatus)
#define SET_TYPE_C_CC_ATTACH_WDINT(x, y)                (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_WDINT(x)].enumAttachStatus = (y))

#define GET_TYPE_C_ORIENTATION(x)                       (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex(x)].enumOrientation)
#define SET_TYPE_C_ORIENTATION(x, y)                    (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex(x)].enumOrientation = (y))

#define GET_TYPE_C_ORIENTATION_EXINT(x)                 (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_EXINT0(x)].enumOrientation)
#define SET_TYPE_C_ORIENTATION_EXINT(x, y)              (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_EXINT0(x)].enumOrientation = (y))

#define GET_TYPE_C_ORIENTATION_WDINT(x)                 (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_WDINT(x)].enumOrientation)
#define SET_TYPE_C_ORIENTATION_WDINT(x, y)              (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_WDINT(x)].enumOrientation = (y))

#define GET_TYPE_C_PIN_ASSIGNMENT(x)                    (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex(x)].enumPinAssignment)
#define SET_TYPE_C_PIN_ASSIGNMENT(x, y)                 (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex(x)].enumPinAssignment = (y))

#define GET_TYPE_C_PIN_ASSIGNMENT_EXINT(x)              (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_EXINT0(x)].enumPinAssignment)
#define SET_TYPE_C_PIN_ASSIGNMENT_EXINT(x, y)           (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_EXINT0(x)].enumPinAssignment = (y))

#define GET_TYPE_C_PIN_ASSIGNMENT_WDINT(x)              (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_WDINT(x)].enumPinAssignment)
#define SET_TYPE_C_PIN_ASSIGNMENT_WDINT(x, y)           (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_WDINT(x)].enumPinAssignment = (y))

#define GET_TYPE_C_ALT_MODE_READY(x)                    (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex(x)].enumAltModeStatus)
#define SET_TYPE_C_ALT_MODE_READY(x, y)                 (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex(x)].enumAltModeStatus = (y))

#define GET_TYPE_C_ALT_MODE_READY_EXINT(x)              (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_EXINT0(x)].enumAltModeStatus)
#define SET_TYPE_C_ALT_MODE_READY_EXINT(x, y)           (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_EXINT0(x)].enumAltModeStatus = (y))

#define GET_TYPE_C_ALT_MODE_READY_WDINT(x)              (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_WDINT(x)].enumAltModeStatus)
#define SET_TYPE_C_ALT_MODE_READY_WDINT(x, y)           (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_WDINT(x)].enumAltModeStatus = (y))

#define GET_TYPE_C_EXPLICIT_CONTRACT(x)                 (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex(x)].b1PowerContract)
#define SET_TYPE_C_EXPLICIT_CONTRACT(x)                 (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex(x)].b1PowerContract = _TRUE)
#define CLR_TYPE_C_EXPLICIT_CONTRACT(x)                 (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex(x)].b1PowerContract = _FALSE)

#define GET_TYPE_C_EXPLICIT_CONTRACT_EXINT(x)           (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_EXINT0(x)].b1PowerContract)
#define SET_TYPE_C_EXPLICIT_CONTRACT_EXINT(x)           (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_EXINT0(x)].b1PowerContract = _TRUE)
#define CLR_TYPE_C_EXPLICIT_CONTRACT_EXINT(x)           (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_EXINT0(x)].b1PowerContract = _FALSE)

#define GET_TYPE_C_EXPLICIT_CONTRACT_WDINT(x)           (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_WDINT(x)].b1PowerContract)
#define SET_TYPE_C_EXPLICIT_CONTRACT_WDINT(x)           (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_WDINT(x)].b1PowerContract = _TRUE)
#define CLR_TYPE_C_EXPLICIT_CONTRACT_WDINT(x)           (g_pstTypeCInfo[ScalerTypeCGetTypeCIndex_WDINT(x)].b1PowerContract = _FALSE)

#define GET_TYPE_C_CBL_INFO_FOR_DPCD(x)                 (g_pstTypeCCableInfoForDpcd[ScalerTypeCGetTypeCIndex(x)])
#define SET_TYPE_C_CBL_INFO_FOR_DPCD(x, y)              (g_pstTypeCCableInfoForDpcd[ScalerTypeCGetTypeCIndex(x)] = (y))

#define GET_TYPE_C_CBL_INFO_FOR_DPCD_EXINT(x)           (g_pstTypeCCableInfoForDpcd[ScalerTypeCGetTypeCIndex_EXINT0(x)])
#define SET_TYPE_C_CBL_INFO_FOR_DPCD_EXINT(x, y)        (g_pstTypeCCableInfoForDpcd[ScalerTypeCGetTypeCIndex_EXINT0(x)] = (y))

#define GET_TYPE_C_CBL_INFO_FOR_DPCD_WDINT(x)           (g_pstTypeCCableInfoForDpcd[ScalerTypeCGetTypeCIndex_WDINT(x)])
#define SET_TYPE_C_CBL_INFO_FOR_DPCD_WDINT(x, y)        (g_pstTypeCCableInfoForDpcd[ScalerTypeCGetTypeCIndex_WDINT(x)] = (y))

#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
#define GET_TYPE_C_0_MAX_POWER()                        (g_stTypeC0PowerInfo.usMaxPower)
#define SET_TYPE_C_0_MAX_POWER(x)                       (g_stTypeC0PowerInfo.usMaxPower = (x))

#define GET_TYPE_C_0_VBUS_STATUS()                      ((bit)(g_stTypeC0PowerInfo.b1VbusStatus))
#define SET_TYPE_C_0_VBUS_STATUS(x)                     (g_stTypeC0PowerInfo.b1VbusStatus = (x))

#define GET_TYPE_C_0_REQ_PWR()                          (g_stTypeC0PowerInfo.usReqPower)
#define SET_TYPE_C_0_REQ_PWR(x)                         (g_stTypeC0PowerInfo.usReqPower = (x))

#define GET_TYPE_C_0_OUTPUT_VOL()                       (g_stTypeC0PowerInfo.usOutputVol)
#define SET_TYPE_C_0_OUTPUT_VOL(x)                      (g_stTypeC0PowerInfo.usOutputVol = (x))

#define GET_TYPE_C_0_OUTPUT_CUR()                       ((WORD)(g_stTypeC0PowerInfo.b10OutputCur))
#define SET_TYPE_C_0_OUTPUT_CUR(x)                      (g_stTypeC0PowerInfo.b10OutputCur = (x))

#define GET_TYPE_C_0_OCP_CURRENT()                      (g_stTypeC0PowerInfo.usOcpCurrent)
#define SET_TYPE_C_0_OCP_CURRENT(x)                     (g_stTypeC0PowerInfo.usOcpCurrent = (x))

#define GET_TYPE_C_0_OCP_RATIO(x)                       (g_pstTypeC0PowerProtectInfo[x].ucOcpCurRatio)
#define SET_TYPE_C_0_OCP_RATIO(x, y)                    (g_pstTypeC0PowerProtectInfo[x].ucOcpCurRatio = (y))
#endif

#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
#define GET_TYPE_C_1_MAX_POWER()                        (g_stTypeC1PowerInfo.usMaxPower)
#define SET_TYPE_C_1_MAX_POWER(x)                       (g_stTypeC1PowerInfo.usMaxPower = (x))

#define GET_TYPE_C_1_VBUS_STATUS()                      ((bit)(g_stTypeC1PowerInfo.b1VbusStatus))
#define SET_TYPE_C_1_VBUS_STATUS(x)                     (g_stTypeC1PowerInfo.b1VbusStatus = (x))

#define GET_TYPE_C_1_REQ_PWR()                          (g_stTypeC1PowerInfo.usReqPower)
#define SET_TYPE_C_1_REQ_PWR(x)                         (g_stTypeC1PowerInfo.usReqPower = (x))

#define GET_TYPE_C_1_OUTPUT_VOL()                       (g_stTypeC1PowerInfo.usOutputVol)
#define SET_TYPE_C_1_OUTPUT_VOL(x)                      (g_stTypeC1PowerInfo.usOutputVol = (x))

#define GET_TYPE_C_1_OUTPUT_CUR()                       ((WORD)(g_stTypeC1PowerInfo.b10OutputCur))
#define SET_TYPE_C_1_OUTPUT_CUR(x)                      (g_stTypeC1PowerInfo.b10OutputCur = (x))

#define GET_TYPE_C_1_OCP_CURRENT()                      (g_stTypeC1PowerInfo.usOcpCurrent)
#define SET_TYPE_C_1_OCP_CURRENT(x)                     (g_stTypeC1PowerInfo.usOcpCurrent = (x))

#define GET_TYPE_C_1_OCP_RATIO(x)                       (g_pstTypeC1PowerProtectInfo[x].ucOcpCurRatio)
#define SET_TYPE_C_1_OCP_RATIO(x, y)                    (g_pstTypeC1PowerProtectInfo[x].ucOcpCurRatio = (y))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumeration Of USB-C CC
//--------------------------------------------------
typedef enum
{
    _TYPE_C_CC_EMB_FW_FSM_INITIAL = 0x00,
    _TYPE_C_CC_EMB_FW_FSM_UNATTACH = 0x01,
    _TYPE_C_CC_EMB_FW_FSM_CONNECTING = 0x02,
    _TYPE_C_CC_EMB_FW_FSM_ATTACHED = 0x03,
}EnumTypeCEmbTypeCCCFWState;

// Enumeration Of CC Pin Deglitch Unit
typedef enum
{
    _TYPE_C_UNIT_1US = 0x00,
    _TYPE_C_UNIT_10US = 0x01,
    _TYPE_C_UNIT_100US = 0x02,
    _TYPE_C_UNIT_1MS = 0x03,
}EnumTypeCDeglitchUnit;

// Enumeration Of CC HW State Machine
typedef enum
{
    _TYPE_C_CC_HW_FSM_IDLE = 0x00,
    _TYPE_C_CC_HW_FSM_UNATTACHED_SNK = 0x01,
    _TYPE_C_CC_HW_FSM_ATTACHWAIT_SNK = 0x02,
    _TYPE_C_CC_HW_FSM_ATTACHED_SNK = 0x03,
    _TYPE_C_CC_HW_FSM_UNATTACHED_SRC = 0x04,
    _TYPE_C_CC_HW_FSM_ATTACHWAIT_SRC = 0x05,
    _TYPE_C_CC_HW_FSM_ATTACHED_SRC = 0x06,
    _TYPE_C_CC_HW_FSM_TRY_SRC = 0x07,
    _TYPE_C_CC_HW_FSM_TRY_WAIT_SNK = 0x08,
    _TYPE_C_CC_HW_FSM_TRY_SNK = 0x09,
    _TYPE_C_CC_HW_FSM_TRY_WAIT_SRC = 0x0A,
    _TYPE_C_CC_HW_FSM_UNATTACHED_ACCESSORY = 0x0B,
    _TYPE_C_CC_HW_FSM_ATTACH_WAIT_ACCESSORY = 0x0C,
    _TYPE_C_CC_HW_FSM_POWER_ACCESSORY = 0x0D,
    _TYPE_C_CC_HW_FSM_UNSUPORTED_ACCESSORY = 0x0E,
    _TYPE_C_CC_HW_FSM_DEBUG_ACCESSORY_SNK = 0x0F,
    _TYPE_C_CC_HW_FSM_AUDIO_ACCESSORY = 0x10,
    _TYPE_C_CC_HW_FSM_AUDIO_ACCESSORY_SRC = 0x11,
    _TYPE_C_CC_HW_FSM_DEBUG_ACCESSORY_SRC = 0x12,
}EnumTypeCCCHWState;

// Enumeration of CC PIN Detected Resistor
typedef enum
{
    _TYPE_C_DET_OPEN = 0x00,
    _TYPE_C_DET_RA = 0x01,
    _TYPE_C_DET_RD = 0x02,
    _TYPE_C_DET_RP_DEF = 0x03,
    _TYPE_C_DET_RP_1P5A = 0x04,
    _TYPE_C_DET_RP_3P0A = 0x05,
}EnumTypeCCCDetResistor;

// Enumeration of CC PIN SNK Set Resistor
typedef enum
{
    _TYPE_C_SET_RD = 0x00,
    _TYPE_C_SET_RA = 0x01,
}EnumTypeCCCSnkSetResistor;

// Enumeration of CC PIN SRC Set Resistor
typedef enum
{
    _TYPE_C_SET_RP_DEF = 0x00,
    _TYPE_C_SET_RP_1P5A = 0x01,
    _TYPE_C_SET_RP_3P0A = 0x02,
}EnumTypeCCCSrcSetResistor;

// Enumeration of CC PIN Set Resistor Under FW Mode
typedef enum
{
    _TYPE_C_FW_MODE_RD = _BIT7,
    _TYPE_C_FW_MODE_DB_RD = _BIT6,
    _TYPE_C_FW_MODE_RP_1_5 = _BIT5,
    _TYPE_C_FW_MODE_RP_DEF = _BIT4,
    _TYPE_C_FW_MODE_RP_3_0 = _BIT3,
    _TYPE_C_FW_MODE_RA = _BIT2,
    _TYPE_C_FW_MODE_OPEN = 0x00,
}EnumTypeCCCFWModeSetResistor;

// Enumeration of CC PIN
typedef enum
{
    _TYPE_C_PIN_CC1 = 0x00,
    _TYPE_C_PIN_CC2 = 0x01,
}EnumTypeCCCPin;

// Enumeration of Backup Data Control
typedef enum
{
    _TYPE_C_BACKUP = 0x00,
    _TYPE_C_RELOAD = 0x01,
}EnumTypeCCCBackupDataControl;

//--------------------------------------------------
// Enumeration Of USB-C PD
//--------------------------------------------------
// Enumeration of PD State
typedef enum
{
    _PD_SRC_START_UP = 0x01,
    _PD_SRC_WDINT_SEND_CAP = 0x02,
    _PD_SRC_INT_SEND_CAP = 0x03,
    _PD_SRC_INT_WAIT_REQ = 0x04,
    _PD_SRC_INT_SEND_ACCEPT_REQ = 0x05,
    _PD_SRC_INT_SEND_REJECT_REQ = 0x06,
    _PD_SRC_INT_SEND_WAIT_REQ = 0x07,
    _PD_SRC_WDINT_TRANSIT_POWER = 0x08,
    _PD_SRC_WDINT_SEND_PSRDY = 0x09,
    _PD_SRC_INT_SEND_PSRDY = 0x0A,
    _PD_SRC_READY = 0x0B,
    _PD_SNK_START_UP = 0x11,
    _PD_SNK_INT_WAIT_SRC_CAP = 0x12,
    _PD_SNK_INT_SEND_REQUEST = 0x13,
    _PD_SNK_INT_WAIT_REQ_RESP = 0x14,
    _PD_SNK_INT_WAIT_PS_RDY = 0x15,
    _PD_SNK_READY = 0x16,
    _PD_WDINT_SEND_CBL_DISCOVER_ID = 0x20,
    _PD_INT_SEND_CBL_DISCOVER_ID = 0x21,
    _PD_INT_WAIT_CBL_DISCOVER_ID_RESP = 0x22,
    _PD_WDINT_SEND_CBL_SOFT_RESET = 0x23,
    _PD_INT_SEND_CBL_SOFT_RESET = 0x24,
    _PD_INT_WAIT_CBL_SOFT_RESET_RESP = 0x25,

    // FW STATE FOR EPR MODE
    _PD_SRC_INT_WAIT_EPR_REQ = 0x30,

    _PD_INT_SEND_SOFTRESET = 0xF0,
    _PD_INT_WAIT_SOFTRESET_RESP = 0xF1,
    _PD_INT_SEND_SOFTRESET_RESP = 0xF2,
    _PD_HARDRESET = 0xFE,
    _PD_NO_RESPONSE = 0xFF,
}EnumTypeCPDState;

// Enumeration of PD Sub-State (Running Under _PE_SRC_READY/_PE_SNK_READY)
typedef enum
{
    _PD_SUB_STATE_NONE = 0x00,
    _PD_SUB_SNK_READY = 0x01,
    _PD_SUB_SRC_READY = 0x10,
    _PD_SUB_CABLE_PROC = 0x20,
    _PD_SUB_SEND_GET_SNK_CAP = 0x31,
    _PD_SUB_INT_WAIT_SNK_CAP = 0x32,
    _PD_SUB_SEND_GET_SRC_CAP = 0x33,
    _PD_SUB_INT_WAIT_SRC_CAP = 0x34,
    _PD_SUB_INT_SEND_SRC_CAP = 0x35,
    _PD_SUB_INT_SEND_SNK_CAP = 0x36,
    _PD_SUB_SEND_SRC_CAP = 0x37,

    // PR_SWAP States
    _PD_SUB_SEND_PR_SWAP = 0x40,
    _PD_SUB_INT_WAIT_PRS_RESP = 0x41,
    _PD_SUB_INT_SEND_ACCEPT_PRS = 0x42,
    _PD_SUB_INT_WAIT_SRC_ON = 0x43,
    _PD_SUB_INT_WAIT_SRC_OFF = 0x44,
    _PD_SUB_WDINT_SEND_SRC_ON_PSRDY = 0x45,
    _PD_SUB_SEND_SRC_OFF_PSRDY = 0x46,

    // DR_SWAP States
    _PD_SUB_SEND_DR_SWAP = 0x47,
    _PD_SUB_INT_WAIT_DRS_RESP = 0x48,
    _PD_SUB_INT_SEND_ACCEPT_DRS = 0x49,

    // VCONN_SWAP States
    _PD_SUB_SEND_VCONN_SWAP = 0x4A,
    _PD_SUB_INT_WAIT_VCS_RESP = 0x4B,
    _PD_SUB_INT_SEND_ACCEPT_VCS = 0x4C,
    _PD_SUB_INT_WAIT_VCONN_ON = 0x4D,
    _PD_SUB_WDINT_SEND_VCONN_ON_PSRDY = 0x4E,

    // PD 3.0 DATA / EXTENDED MSG States
    _PD_SUB_INT_SEND_SRC_CAP_EXT = 0x60,
    _PD_SUB_INT_SEND_STATUS = 0x61,
    _PD_SUB_INT_SEND_MFC_INFO = 0x62,
    _PD_SUB_INT_SEND_CHK_TEST_REQ = 0x63,
    _PD_SUB_INT_WAIT_CHK_TEST_RESP = 0x64,
    _PD_SUB_INT_WAIT_STATUS = 0x65,
    _PD_SUB_INT_SEND_GET_BAT_STATUS = 0x66,
    _PD_SUB_INT_WAIT_BAT_STATUS = 0x67,
    _PD_SUB_INT_SEND_PPS_STATUS = 0x68,
    _PD_SUB_SEND_GET_STATUS = 0x69,
    _PD_SUB_SEND_ALERT = 0x6A,
    _PD_SUB_INT_SEND_REVISION = 0x6B,
    _PD_SUB_INT_SEND_SNK_CAP_EXT = 0x6C,

    // SUB STATE FOR EPR MODE
    _PD_SUB_INT_SEND_EPR_ENTER_ACK = 0x70,
    _PD_SUB_INT_SEND_EPR_ENTER_FAILED = 0x71,
    _PD_SUB_INT_SEND_EPR_ENTER_SUCCESSFUL = 0x72,
    _PD_SUB_WDINT_DISCOVER_CABLE = 0x73,
    _PD_SUB_WDINT_SEND_VCONN_SWAP = 0x74,
    _PD_SUB_INT_SEND_VCONN_SWAP = 0x75,
    _PD_SUB_SEND_EPR_SRC_CAP = 0x76,
    _PD_SUB_INT_WAIT_EPR_SRC_CAP_CHUNK_REQ = 0x77,
    _PD_SUB_INT_SEND_EPR_SRC_CAP = 0x78,
    _PD_SUB_INT_SEND_EPR_KEEP_ALIVE_ACK = 0x79,
    _PD_SUB_WDINT_SEND_EPR_SRC_CAP = 0x7A,

    // SUB STATE FOR ALT MODE
    _PD_SUB_SEND_DP_VDM_REQ = 0xA1,
    _PD_SUB_SEND_CBL_DP_VDM_REQ = 0xA2,
    _PD_SUB_SEND_LENOVO_VDM_REQ = 0xA3,
    _PD_SUB_INT_SEND_VDM_RESP = 0xA4,
    _PD_SUB_INT_WAIT_VDM_RESP = 0xA5,
    _PD_SUB_SEND_ACER_VDM_REQ = 0xA6,
    _PD_SUB_SEND_HP_VDM_REQ = 0xA7,
    _PD_SUB_SEND_DELL_VDM_REQ = 0xA8,
    _PD_SUB_BIST_MODE = 0xB0,
    _PD_SUB_INT_SEND_REJECT = 0xF0,
    _PD_SUB_INT_SEND_WAIT = 0xF1,
    _PD_SUB_INT_SEND_NOT_SUPPORT = 0xF2,
}EnumTypeCPDSubState;

// Enumeration of PD Cable State
typedef enum
{
    _PD_CBL_STATE_NONE = 0x00,
    _PD_CBL_SEND_DISCOVER_ID = 0x01,
    _PD_CBL_INT_SEND_DISCOVER_ID = 0x02,
    _PD_CBL_INT_WAIT_DISCOVER_ID_RESP = 0x03,
    _PD_CBL_SEND_SOFT_RST = 0x04,
    _PD_CBL_INT_SEND_SOFT_RST = 0x05,
    _PD_CBL_INT_WAIT_SOFT_RST_RESP = 0x06,
    _PD_CBL_SEND_CBL_RST = 0x0A,
    _PD_CBL_NO_RESPONSE = 0x0F,
}EnumTypeCPDCableState;

// Enumeration of Alt. Mode State Machine
typedef enum
{
    _PD_ALT_MODE_NONE = 0x00,
    _PD_ALT_MODE_SEND_DISCOVER_ID = 0x01,
    _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP = 0x02,
    _PD_ALT_MODE_INT_SEND_DISCOVER_ID_ACK = 0x03,
    _PD_ALT_MODE_INT_SEND_DISCOVER_ID_NAK = 0x04,
    _PD_ALT_MODE_SEND_DISCOVER_SVID = 0x05,
    _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP = 0x06,
    _PD_ALT_MODE_INT_SEND_DISCOVER_SVID_ACK = 0x07,
    _PD_ALT_MODE_INT_SEND_DISCOVER_SVID_NAK = 0x08,
    _PD_ALT_MODE_SEND_DISCOVER_MODE = 0x09,
    _PD_ALT_MODE_INT_WAIT_DISCOVER_MODE_RESP = 0x0A,
    _PD_ALT_MODE_INT_SEND_DISCOVER_MODE_ACK = 0x0B,
    _PD_ALT_MODE_INT_SEND_DISCOVER_MODE_NAK = 0x0C,
    _PD_ALT_MODE_SEND_ENTER_MODE = 0x0D,
    _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP = 0x0E,
    _PD_ALT_MODE_INT_SEND_ENTER_MODE_ACK = 0x0F,
    _PD_ALT_MODE_INT_SEND_ENTER_MODE_NAK = 0x10,
    _PD_ALT_MODE_SEND_EXIT_MODE = 0x11,
    _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP = 0x12,
    _PD_ALT_MODE_INT_SEND_EXIT_MODE_ACK = 0x13,
    _PD_ALT_MODE_INT_SEND_EXIT_MODE_NAK = 0x14,
    _PD_ALT_MODE_SEND_DP_STATUS = 0x15,
    _PD_ALT_MODE_INT_WAIT_DP_STATUS_RESP = 0x16,
    _PD_ALT_MODE_INT_SEND_DP_STATUS_ACK = 0x17,
    _PD_ALT_MODE_INT_SEND_DP_STATUS_NAK = 0x18,
    _PD_ALT_MODE_SEND_DP_CONFIG = 0x19,
    _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP = 0x1A,
    _PD_ALT_MODE_INT_SEND_DP_CONFIG_ACK = 0x1B,
    _PD_ALT_MODE_INT_SEND_DP_CONFIG_NAK = 0x1C,
    _PD_ALT_MODE_SEND_LENOVO_GET_STATUS = 0x1D,
    _PD_ALT_MODE_INT_WAIT_LENOVO_GET_STATUS_RESP = 0x1E,
    _PD_ALT_MODE_INT_SEND_LENOVO_GET_STATUS_ACK = 0x1F,
    _PD_ALT_MODE_INT_SEND_LENOVO_GET_STATUS_NAK = 0x20,
    _PD_ALT_MODE_INT_SEND_HP_SET_CONFIG_ACK = 0x21,
    _PD_ALT_MODE_SEND_HP_SET_VWIRE_SAMPLE_ACK = 0x22,
    _PD_ALT_MODE_SEND_HP_ATTEN_CONFIG = 0x23,
    _PD_ALT_MODE_SEND_HP_ATTEN_VWIRE = 0x24,
    _PD_ALT_MODE_SEND_HP_ATTEN_DATA = 0x25,
    _PD_ALT_MODE_INT_SEND_DELL_0X12_ACK = 0x26,
    _PD_ALT_MODE_SEND_DELL_ATTEN = 0x27,
    _PD_ALT_MODE_INT_WAIT_DELL_0X13 = 0x28,
    _PD_ALT_MODE_SEND_ATTENTION = 0x29,
    _PD_ALT_MODE_INT_WAIT_ATTENTION = 0x2A,
    _PD_ALT_MODE_SEND_DISCOVER_ID_SOP_P = 0x2B,
    _PD_ALT_MODE_INT_WAIT_DISCOVER_ID_RESP_SOP_P = 0x2C,
    _PD_ALT_MODE_SEND_DISCOVER_SVID_SOP_P = 0x2D,
    _PD_ALT_MODE_INT_WAIT_DISCOVER_SVID_RESP_SOP_P = 0x2E,
    _PD_ALT_MODE_SEND_DP_DISCOVER_MODE_SOP_P = 0x2F,
    _PD_ALT_MODE_INT_WAIT_DP_DISCOVER_MODE_RESP_SOP_P = 0x30,
    _PD_ALT_MODE_SEND_TBT3_DISCOVER_MODE_SOP_P = 0x31,
    _PD_ALT_MODE_INT_WAIT_TBT3_DISCOVER_MODE_RESP_SOP_P = 0x32,
    _PD_ALT_MODE_SEND_ENTER_MODE_SOP_P = 0x33,
    _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_P = 0x34,
    _PD_ALT_MODE_SEND_ENTER_MODE_SOP_PP = 0x35,
    _PD_ALT_MODE_INT_WAIT_ENTER_MODE_RESP_SOP_PP = 0x36,
    _PD_ALT_MODE_SEND_DP_CONFIG_SOP_P = 0x37,
    _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_P = 0x38,
    _PD_ALT_MODE_SEND_DP_CONFIG_SOP_PP = 0x39,
    _PD_ALT_MODE_INT_WAIT_DP_CONFIG_RESP_SOP_PP = 0x3A,
    _PD_ALT_MODE_SEND_EXIT_MODE_SOP_P = 0x3B,
    _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_P = 0x3C,
    _PD_ALT_MODE_SEND_EXIT_MODE_SOP_PP = 0x3D,
    _PD_ALT_MODE_INT_WAIT_EXIT_MODE_RESP_SOP_PP = 0x3E,
    _PD_ALT_MODE_READY = 0x3F,
    _PD_ALT_MODE_ERROR = 0x40,
}EnumTypeCPDAltModeState;

// Enumeration of Cable Discover ID Info
typedef enum
{
    _PD_PRODUCT_TYPE_UNDEFINED = 0x00,
    _PD_PASSIVE_CABLE = 0x01,
    _PD_ACTIVE_CABLE = 0x02,
    _PD_VCONN_POWERED_USB_DEVICE = 0x03,
}EnumTypeCPDCableProductType;

typedef enum
{
    _PD_CABLE_CONNECTOR_TYPE_UNCONFIRMED = 0x00,
    _PD_CABLE_TYPEC_RECEPTACLE = 0x01,
    _PD_CABLE_TYPEC_PLUG = 0x02,
}EnumTypeCPDCableConnectorType;

typedef enum
{
    _PD_CBL_TERMINATION_TYPE_UNDEFINED = 0x00,
    _PD_CBL_ONE_ACTIVE_ONE_PASSIVE = 0x01,
    _PD_CBL_BOTH_END_ACTIVE = 0x02,
}EnumTypeCPDCableTerminationType;

typedef enum
{
    _PD_CBL_SBU_TYPE_UNDEFINED = 0x00,
    _PD_CBL_SBU_PASSIVE = 0x01,
    _PD_CBL_SBU_ACTIVE = 0x02,
}EnumTypeCPDCableSbuType;

typedef enum
{
    _PD_CBL_USB_LANES_SUPPORT_UNDEFINED = 0x00,
    _PD_CBL_ONE_LANE = 0x01,
    _PD_CBL_TWO_LANES = 0x02,
}EnumTypeCPDCableUsbLanesSupport;

typedef enum
{
    _PD_CBL_PIN_ASSIGNMENT_UNCONFIRMED = 0x00,
    _PD_CBL_PIN_ASSIGNMENT_C_AND_D = 0x01,
    _PD_CBL_PIN_ASSIGNMENT_E = 0x02,
}EnumTypeCPDCablePinAssignment;

typedef enum
{
    _PD_CBL_TBT3_PRODUCT_TYPE_UNCONFIRMED = 0x00,
    _PD_CBL_TBT3_ACTIVE_CABLE = 0x01,
    _PD_CBL_TBT3_PASSIVE_CABLE = 0x02,
}EnumTypeCPDCableTbt3ProductType;

typedef enum
{
    _PD_CBL_TBT3_DIRECTION_UNCONFIRMED = 0x00,
    _PD_CBL_TBT3_BIDIRECTION = 0x01,
    _PD_CBL_TBT3_UNIDIRECTION = 0x02,
}EnumTypeCPDCableTbt3Direction;

typedef enum
{
    _PD_CBL_TBT3_ROUNDED_SUPPORT_UNCONFIRMED = 0x00,
    _PD_CBL_TBT3_3RD_GEN_NON_ROUNDED = 0x01,
    _PD_CBL_TBT3_3RD_AND_4TH_GEN_ROUNDED = 0x02,
}EnumTypeCPDCableTbt3RoundedSupport;

typedef enum
{
    _PD_CBL_TBT3_SPEED_UNCONFIRMED = 0x00,
    _PD_CBL_TBT3_U3P1_GEN1 = 0x01,
    _PD_CBL_TBT3_10G = 0x02,
    _PD_CBL_TBT3_20G = 0x03,
}EnumTypeCPDCableTbt3Speed;

typedef enum
{
    _PD_CBL_USB_2_ONLY = 0x00,
    _PD_CBL_USB_3_GEN1 = 0x01,
    _PD_CBL_USB_3OR4_GEN2 = 0x02,
    _PD_CBL_USB_4_GEN3 = 0x03,
}EnumTypeCPDCableUsbHighestSpeed;

typedef enum
{
    _PD_CBL_U3_TO_U0_UNDEFINED = 0x00,
    _PD_CBL_U3_TO_U0_DIRECT = 0x01,
    _PD_CBL_U3_TO_U0_THROUGH_U3S = 0x02,
}EnumTypeCPDCableU3ToU0TransitionMode;

// Enumeration of PD Atomic Message Sequence Status
typedef enum
{
    _PD_AMS_NONE = 0x00,
    _PD_AMS_INTERRUPTIBLE = 0x01,
    _PD_AMS_NON_INTERRUPTIBLE = 0x02,
    _PD_AMS_POWER_TRANSITION = 0x03,
}EnumDPAmsState;

// Enumeration of PD Packet Type
typedef enum
{
    _PD_SOP_PKT = 0x00,
    _PD_SOP_P_PKT = 0x01,
    _PD_SOP_PP_PKT = 0x02,
    _PD_HARD_RESET_PKT = 0x03,
    _PD_CABLE_RESET_PKT = 0x04,
    _PD_VS1_SOP_PKT = 0x05,
    _PD_VS2_SOP_PKT = 0x06,
    _PD_VS3_SOP_PKT = 0x07,
}EnumTypeCPDPacketType;

// Enumeration of PD Tx Transmission Retry Fail Event
typedef enum
{
    _PD_TX_RETRY_FAIL_BY_STATE = 0x00,
    _PD_TX_RETRY_FAIL_ERROR_RECOVERY = 0x01,
    _PD_TX_RETRY_FAIL_SOFT_RESET = 0x02,
    _PD_TX_RETRY_FAIL_HARD_RESET = 0x03,
}EnumTypeCTxRetryFailEvent;

// Enumeration of PD Tx Check Result
typedef enum
{
    _PD_TX_NOT_AVAILABLE = 0x00,
    _PD_TX_AVAILABLE = 0x01,
    _PD_TX_WAIT_SRC_INIT_AMS_TIMER = 0x02,
}EnumTypeCTxCheckResult;

// Enumeration of PD Tx Transmission Result
typedef enum
{
    _PD_SENT_CONFLICT = _BIT4,
    _PD_SENT_SUCCESS = _BIT3,
    _PD_SENT_RETRY_FAIL = _BIT2,
    _PD_SENT_DISCARDED = _BIT1,
    _PD_SENT_HARD_RST = _BIT0,
}EnumTypeCTxSentResult;

// Enumeration of PD Rx FIFO
typedef enum
{
    _PD_RX_FIFO_0 = 0x00,
    _PD_RX_FIFO_1 = 0x01,
    _PD_RX_FIFO_2 = 0x02,
    _PD_RX_FIFO_RSV = 0x03,
}EnumTypeCRxFifoIndex;

// Enumeration of PD Message Command Type
typedef enum
{
    _PD_CMD_TYPE_CTRL = 0x00,
    _PD_CMD_TYPE_DATA = _BIT6,
    _PD_CMD_TYPE_EXT = _BIT7,
}EnumTypeCPDCmdType;

// Enumeration of PD Message Command
// Control Msg 0x01 - 1F / Data Msg. 0x40 - 5F / Ext Msg. 0x80 - 9F
typedef enum
{
    _PD_CMD_RSV = (_PD_CMD_TYPE_CTRL | 0x00),
    _PD_CMD_GOODCRC = (_PD_CMD_TYPE_CTRL | 0x01),
    _PD_CMD_GOTOMIN = (_PD_CMD_TYPE_CTRL | 0x02),
    _PD_CMD_ACCEPT = (_PD_CMD_TYPE_CTRL | 0x03),
    _PD_CMD_REJECT = (_PD_CMD_TYPE_CTRL | 0x04),
    _PD_CMD_PING = (_PD_CMD_TYPE_CTRL | 0x05),
    _PD_CMD_PS_RDY = (_PD_CMD_TYPE_CTRL | 0x06),
    _PD_CMD_GET_SRC_CAP = (_PD_CMD_TYPE_CTRL | 0x07),
    _PD_CMD_GET_SNK_CAP = (_PD_CMD_TYPE_CTRL | 0x08),
    _PD_CMD_DR_SWAP = (_PD_CMD_TYPE_CTRL | 0x09),
    _PD_CMD_PR_SWAP = (_PD_CMD_TYPE_CTRL | 0x0A),
    _PD_CMD_VCONN_SWAP = (_PD_CMD_TYPE_CTRL | 0x0B),
    _PD_CMD_WAIT = (_PD_CMD_TYPE_CTRL | 0x0C),
    _PD_CMD_SOFT_RESET = (_PD_CMD_TYPE_CTRL | 0x0D),
    _PD_CMD_DATA_RESET = (_PD_CMD_TYPE_CTRL | 0x0E),
    _PD_CMD_DATA_RESET_COMPLETE = (_PD_CMD_TYPE_CTRL | 0x0F),
    _PD_CMD_NOT_SUPPORT = (_PD_CMD_TYPE_CTRL | 0x10),
    _PD_CMD_GET_SRC_CAP_EXT = (_PD_CMD_TYPE_CTRL | 0x11),
    _PD_CMD_GET_STATUS = (_PD_CMD_TYPE_CTRL | 0x12),
    _PD_CMD_FR_SWAP = (_PD_CMD_TYPE_CTRL | 0x13),
    _PD_CMD_GET_PPS_STATUS = (_PD_CMD_TYPE_CTRL | 0x14),
    _PD_CMD_GET_COUNTRY_CODES = (_PD_CMD_TYPE_CTRL | 0x15),
    _PD_CMD_GET_SNK_CAP_EXT = (_PD_CMD_TYPE_CTRL | 0x16),
    _PD_CMD_GET_SRC_INFO = (_PD_CMD_TYPE_CTRL | 0x17),
    _PD_CMD_GET_REVISION = (_PD_CMD_TYPE_CTRL | 0x18),

    _PD_CMD_SRC_CAP = (_PD_CMD_TYPE_DATA | 0x01),
    _PD_CMD_REQUEST = (_PD_CMD_TYPE_DATA | 0x02),
    _PD_CMD_BIST = (_PD_CMD_TYPE_DATA | 0x03),
    _PD_CMD_SNK_CAP = (_PD_CMD_TYPE_DATA | 0x04),
    _PD_CMD_BAT_STATUS = (_PD_CMD_TYPE_DATA | 0x05),
    _PD_CMD_ALERT = (_PD_CMD_TYPE_DATA | 0x06),
    _PD_CMD_GET_COUNTRY_INFO = (_PD_CMD_TYPE_DATA | 0x07),
    _PD_CMD_ENTER_USB = (_PD_CMD_TYPE_DATA | 0x08),
    _PD_CMD_EPR_REQUEST = (_PD_CMD_TYPE_DATA | 0x09),
    _PD_CMD_EPR_MODE = (_PD_CMD_TYPE_DATA | 0x0A),
    _PD_CMD_SRC_INFO = (_PD_CMD_TYPE_DATA | 0x0B),
    _PD_CMD_REVISION = (_PD_CMD_TYPE_DATA | 0x0C),
    _PD_CMD_VDM = (_PD_CMD_TYPE_DATA | 0x0F),

    _PD_CMD_SRC_CAP_EXT = (_PD_CMD_TYPE_EXT | 0x1),
    _PD_CMD_STATUS = (_PD_CMD_TYPE_EXT | 0x02),
    _PD_CMD_GET_BAT_CAP = (_PD_CMD_TYPE_EXT | 0x03),
    _PD_CMD_GET_BAT_STATUS = (_PD_CMD_TYPE_EXT | 0x04),
    _PD_CMD_BAT_CAP = (_PD_CMD_TYPE_EXT | 0x05),
    _PD_CMD_GET_MFC_INFO = (_PD_CMD_TYPE_EXT | 0x06),
    _PD_CMD_MFC_INFO = (_PD_CMD_TYPE_EXT | 0x07),
    _PD_CMD_SEC_REQ = (_PD_CMD_TYPE_EXT | 0x08),
    _PD_CMD_SEC_RESP = (_PD_CMD_TYPE_EXT | 0x9),
    _PD_CMD_FW_UPDATE_REQ = (_PD_CMD_TYPE_EXT | 0x0A),
    _PD_CMD_FW_UPDATE_RESP = (_PD_CMD_TYPE_EXT | 0x0B),
    _PD_CMD_PPS_STATUS = (_PD_CMD_TYPE_EXT | 0x0C),
    _PD_CMD_COUNTRY_INFO = (_PD_CMD_TYPE_EXT | 0x0D),
    _PD_CMD_COUNTRY_CODES = (_PD_CMD_TYPE_EXT | 0x0E),
    _PD_CMD_SNK_CAP_EXT = (_PD_CMD_TYPE_EXT | 0x0F),
    _PD_CMD_EXTENDED_CONTROL = (_PD_CMD_TYPE_EXT | 0x10),
    _PD_CMD_EPR_SRC_CAP = (_PD_CMD_TYPE_EXT | 0x11),
    _PD_CMD_EPR_SNK_CAP = (_PD_CMD_TYPE_EXT | 0x12),
    _PD_CMD_VENDOR_DEFINED_EXT = (_PD_CMD_TYPE_EXT | 0x1E),

    _PD_CMD_CHUNK_TEST = (_PD_CMD_TYPE_EXT | 0x1F),

    _PD_CMD_UNDEFINED = 0xFF,
}EnumTypeCPDCmd;

// Enumeration of VDM Message Command Type
typedef enum
{
    _PD_VDM_CMD_TYPE_REQ = 0x00,
    _PD_VDM_CMD_TYPE_ACK = _BIT6,
    _PD_VDM_CMD_TYPE_NAK = _BIT7,
    _PD_VDM_CMD_TYPE_BUSY = (_BIT7 | _BIT6),
}EnumTypeCPDVdmCmdType;

// Enumeration of PD VDM Message Command Type
typedef enum
{
    _PD_VDM_CMD_RESERVED = 0x00,
    _PD_VDM_CMD_DISCOVER_ID_REQ = 0x01,
    _PD_VDM_CMD_DISCOVER_SVID_REQ = 0x02,
    _PD_VDM_CMD_DISCOVER_MODE_REQ = 0x03,
    _PD_VDM_CMD_ENTER_MODE_REQ = 0x04,
    _PD_VDM_CMD_EXIT_MODE_REQ = 0x05,
    _PD_VDM_CMD_ATTENTION_REQ = 0x06,
    _PD_VDM_CMD_10 = 0x10,  // DP, Lenovo Status Req
    _PD_VDM_CMD_11 = 0x11,  // DP Config Req
    _PD_VDM_CMD_15 = 0x15,  // Acer Attention
    _PD_VDM_CMD_DISCOVER_ID_ACK = 0x41,
    _PD_VDM_CMD_DISCOVER_SVID_ACK = 0x42,
    _PD_VDM_CMD_DISCOVER_MODE_ACK = 0x43,
    _PD_VDM_CMD_ENTER_MODE_ACK = 0x44,
    _PD_VDM_CMD_EXIT_MODE_ACK = 0x45,
    _PD_VDM_CMD_50 = 0x50,
    _PD_VDM_CMD_51 = 0x51,
    _PD_VDM_CMD_52 = 0x52,  // HP Set_vwire Sample ACK
    _PD_VDM_CMD_DISCOVER_ID_NAK = 0x81,
    _PD_VDM_CMD_DISCOVER_SVID_NAK = 0x82,
    _PD_VDM_CMD_DISCOVER_MODE_NAK = 0x83,
    _PD_VDM_CMD_ENTER_MODE_NAK = 0x84,
    _PD_VDM_CMD_EXIT_MODE_NAK = 0x85,
    _PD_VDM_CMD_90 = 0x90,
    _PD_VDM_CMD_91 = 0x91,
    _PD_VDM_CMD_DISCOVER_ID_BUSY = 0xC1,
    _PD_VDM_CMD_DISCOVER_SVID_BUSY = 0xC2,
    _PD_VDM_CMD_DISCOVER_MODE_BUSY = 0xC3,
    _PD_VDM_CMD_ENTER_MODE_BUSY = 0xC4,
    _PD_VDM_CMD_EXIT_MODE_BUSY = 0xC5,
    _PD_VDM_CMD_D0 = 0xD0,
    _PD_VDM_CMD_D1 = 0xD1,
}EnumTypeCVdmCmd;

// Enumeration of Dp VDM Message Command Type
typedef enum
{
    _PD_VDM_DP_CMD_RESERVED = 0x00,
    _PD_VDM_DP_CMD_DISCOVER_MODE_REQ = 0x03,
    _PD_VDM_DP_CMD_ENTER_MODE_REQ = 0x04,
    _PD_VDM_DP_CMD_EXIT_MODE_REQ = 0x05,
    _PD_VDM_DP_CMD_ATTENTION_REQ = 0x06,
    _PD_VDM_DP_CMD_DP_STATUS_REQ = 0x10,
    _PD_VDM_DP_CMD_DP_CONFIG_REQ = 0x11,
    _PD_VDM_DP_CMD_DISCOVER_MODE_ACK = 0x43,
    _PD_VDM_DP_CMD_ENTER_MODE_ACK = 0x44,
    _PD_VDM_DP_CMD_EXIT_MODE_ACK = 0x45,
    _PD_VDM_DP_CMD_DP_STATUS_ACK = 0x50,
    _PD_VDM_DP_CMD_DP_CONFIG_ACK = 0x51,
    _PD_VDM_DP_CMD_DISCOVER_MODE_NAK = 0x83,
    _PD_VDM_DP_CMD_ENTER_MODE_NAK = 0x84,
    _PD_VDM_DP_CMD_EXIT_MODE_NAK = 0x85,
    _PD_VDM_DP_CMD_DP_STATUS_NAK = 0x90,
    _PD_VDM_DP_CMD_DP_CONFIG_NAK = 0x91,
    _PD_VDM_DP_CMD_DISCOVER_MODE_BUSY = 0xC3,
    _PD_VDM_DP_CMD_ENTER_MODE_BUSY = 0xC4,
    _PD_VDM_DP_CMD_EXIT_MODE_BUSY = 0xC5,
    _PD_VDM_DP_CMD_DP_STATUS_BUSY = 0xD0,
    _PD_VDM_DP_CMD_DP_CONFIG_BUSY = 0xD1,
}EnumTypeCVdmDpCmd;

// Enumeration of Lenovo VDM Message Command Type
typedef enum
{
    _PD_VDM_LENOVO_CMD_RESERVED = 0x00,
    _PD_VDM_LENOVO_CMD_DISCOVER_MODE_REQ = 0x03,
    _PD_VDM_LENOVO_CMD_ENTER_MODE_REQ = 0x04,
    _PD_VDM_LENOVO_CMD_EXIT_MODE_REQ = 0x05,
    _PD_VDM_LENOVO_CMD_ATTENTION_REQ = 0x06,
    _PD_VDM_LENOVO_CMD_GET_STATUS_REQ = 0x10,
    _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_REQ = 0x11,
    _PD_VDM_LENOVO_CMD_DISCOVER_MODE_ACK = 0x43,
    _PD_VDM_LENOVO_CMD_ENTER_MODE_ACK = 0x44,
    _PD_VDM_LENOVO_CMD_EXIT_MODE_ACK = 0x45,
    _PD_VDM_LENOVO_CMD_GET_STATUS_ACK = 0x50,
    _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_ACK = 0x51,
    _PD_VDM_LENOVO_CMD_DISCOVER_MODE_NAK = 0x83,
    _PD_VDM_LENOVO_CMD_ENTER_MODE_NAK = 0x84,
    _PD_VDM_LENOVO_CMD_EXIT_MODE_NAK = 0x85,
    _PD_VDM_LENOVO_CMD_GET_STATUS_NAK = 0x90,
    _PD_VDM_LENOVO_CMD_LENOVO_DEVICE_ID_NAK = 0x91,
}EnumTypeCVdmLenovoCmd;

// Enumeration of Acer VDM Message Command Type
typedef enum
{
    _PD_VDM_ACER_CMD_RESERVED = 0x00,
    _PD_VDM_ACER_CMD_DISCOVER_MODE_REQ = 0x03,
    _PD_VDM_ACER_CMD_ENTER_MODE_REQ = 0x04,
    _PD_VDM_ACER_CMD_EXIT_MODE_REQ = 0x05,
    _PD_VDM_ACER_CMD_ATTENTION_REQ = 0x15,
    _PD_VDM_ACER_CMD_GET_STATUS_REQ = 0x16,
    _PD_VDM_ACER_CMD_DISCOVER_MODE_ACK = 0x43,
    _PD_VDM_ACER_CMD_ENTER_MODE_ACK = 0x44,
    _PD_VDM_ACER_CMD_EXIT_MODE_ACK = 0x45,
    _PD_VDM_ACER_CMD_GET_STATUS_ACK = 0x56,
    _PD_VDM_ACER_CMD_DISCOVER_MODE_NAK = 0x83,
    _PD_VDM_ACER_CMD_ENTER_MODE_NAK = 0x84,
    _PD_VDM_ACER_CMD_EXIT_MODE_NAK = 0x85,
    _PD_VDM_ACER_CMD_GET_STATUS_NAK = 0x96,
}EnumTypeCVdmAcerCmd;

// Enumeration of Hp VDM Message Command Type
typedef enum
{
    _PD_VDM_HP_CMD_RESERVED = 0x00,
    _PD_VDM_HP_CMD_DISCOVER_MODE_REQ = 0x03,
    _PD_VDM_HP_CMD_ENTER_MODE_REQ = 0x04,
    _PD_VDM_HP_CMD_EXIT_MODE_REQ = 0x05,
    _PD_VDM_HP_CMD_ATTENTION_REQ = 0x06,
    _PD_VDM_HP_CMD_SET_CONFIG_REQ = 0x10,
    _PD_VDM_HP_CMD_GET_CONFIG_REQ = 0x11,
    _PD_VDM_HP_CMD_SET_VWIRE_REQ = 0x12,
    _PD_VDM_HP_CMD_GET_VWIRE_REQ = 0x13,
    _PD_VDM_HP_CMD_SET_DATA_REQ = 0x14,
    _PD_VDM_HP_CMD_GET_DATA_REQ = 0x15,
    _PD_VDM_HP_CMD_CMD_REQ = 0x16,
    _PD_VDM_HP_CMD_DISCOVER_MODE_ACK = 0x43,
    _PD_VDM_HP_CMD_ENTER_MODE_ACK = 0x44,
    _PD_VDM_HP_CMD_EXIT_MODE_ACK = 0x45,
    _PD_VDM_HP_CMD_SET_CONFIG_ACK = 0x50,
    _PD_VDM_HP_CMD_GET_CONFIG_ACK = 0x51,
    _PD_VDM_HP_CMD_SET_VWIRE_ACK = 0x52,
    _PD_VDM_HP_CMD_GET_VWIRE_ACK = 0x53,
    _PD_VDM_HP_CMD_SET_DATA_ACK = 0x54,
    _PD_VDM_HP_CMD_GET_DATA_ACK = 0x55,
    _PD_VDM_HP_CMD_DISCOVER_MODE_NAK = 0x83,
    _PD_VDM_HP_CMD_ENTER_MODE_NAK = 0x84,
    _PD_VDM_HP_CMD_EXIT_MODE_NAK = 0x85,
}EnumTypeCVdmHpCmd;

// Enumeration of Dell VDM Message Command Type
typedef enum
{
    _PD_VDM_DELL_CMD_RESERVED = 0x00,
    _PD_VDM_DELL_CMD_DISCOVER_MODE_REQ = 0x03,
    _PD_VDM_DELL_CMD_ENTER_MODE_REQ = 0x04,
    _PD_VDM_DELL_CMD_EXIT_MODE_REQ = 0x05,
    _PD_VDM_DELL_CMD_ATTENTION_REQ = 0x06,
    _PD_VDM_DELL_CMD_0X12_REQ = 0x12,
    _PD_VDM_DELL_CMD_0X13_REQ = 0x13,
    _PD_VDM_DELL_CMD_DISCOVER_MODE_ACK = 0x43,
    _PD_VDM_DELL_CMD_ENTER_MODE_ACK = 0x44,
    _PD_VDM_DELL_CMD_EXIT_MODE_ACK = 0x45,
    _PD_VDM_DELL_CMD_0X12_ACK = 0x52,
    _PD_VDM_DELL_CMD_DISCOVER_MODE_NAK = 0x83,
    _PD_VDM_DELL_CMD_ENTER_MODE_NAK = 0x84,
    _PD_VDM_DELL_CMD_EXIT_MODE_NAK = 0x85,
}EnumTypeCVdmDellCmd;

// Enumeration of Check Rebuild Power Contract
typedef enum
{
    _PD_REBUILD_NOT_REQUIRED = 0x00,
    _PD_REBUILD_REQUIRED = 0x01,
}EnumTypeCPDRebuildPowerContract;

// Enumeration of Check PD Request Check
typedef enum
{
    _PD_REQUEST_INVALID_CURRENT = 0x00,
    _PD_REQUEST_INVALID_COPY_PDO = 0x01,
    _PD_REQUEST_VALID = 0x02,
}EnumTypeCPDRequestValid;

// Enumeration of Check PD SRC_CAP
typedef enum
{
    _PD_SRC_CAP_INVALID = 0x00,
    _PD_SRC_CAP_VALID = 0x01,
}EnumTypeCPDSrcCapValid;

// Enumeration of EPR Mode Action
typedef enum
{
    // EPR Mode Action
    _PD_EPR_MODE_RESERVED = 0x00,
    _PD_EPR_MODE_ENTER = 0x01,
    _PD_EPR_MODE_ENTER_ACK = 0x02,
    _PD_EPR_MODE_ENTER_SUCCESS = 0x03,
    _PD_EPR_MODE_ENTER_FAILED = 0x04,
    _PD_EPR_MODE_EXIT = 0x05,
}EnumTypeCPDEPRModeAction;

// Enumeration of EPR Mode Enter Failed Reason
typedef enum
{
    // EPR Mode Enter Failed Reason
    _PD_EPR_MODE_ENTER_FAILED_UNKNOWN = 0x00,
    _PD_EPR_MODE_ENTER_FAILED_CABLE_NOT_EPR_CAP = 0x01,
    _PD_EPR_MODE_ENTER_FAILED_NOT_VCONN_SOURCE = 0x02,
    _PD_EPR_MODE_ENTER_FAILED_SINK_NOT_EPR_CAP = 0x03,
    _PD_EPR_MODE_ENTER_FAILED_SOURCE_UNABLE_TO_ENTER_EPR = 0x04,
    _PD_EPR_MODE_ENTER_FAILED_SOURCE_NOT_EPR_CAP = 0x05,
}EnumTypeCPDEnterEPRFailedReason;

// Enumeration of Extended Conntrol Message Type
typedef enum
{
    _PD_EXT_CTRL_TYPE_RESERVED = 0x00,
    _PD_EXT_CTRL_TYPE_EPR_GET_SRC_CAP = 0x01,
    _PD_EXT_CTRL_TYPE_EPR_GET_SNK_CAP = 0x02,
    _PD_EXT_CTRL_TYPE_EPR_KEEP_ALIVE = 0x03,
    _PD_EXT_CTRL_TYPE_EPR_KEEP_ALIVE_ACK = 0x04,
}EnumTypeCPDExtCtrlType;

// Enumeration of PD SVDM Version From SVDM Header [14:13] Major, [12:11] Minor (Updated in Discover ID)
typedef enum
{
    _PD_SVDM_VER_2_0_EARLIER = _SVDM_VERSION_2_0_EARLIER,
    _PD_SVDM_VER_2_1 = _SVDM_VERSION_2_1,
}EnumTypeCPDSvdmVersion;

// DPAM v2.1: Enumeration of Vdo Version From Discover Mode Ack(SOP/SOP'/SOP'') or Dp Config(SOP)
typedef enum
{
    _PD_DPAM_VER_2_0_EARLIER = 0x00,
    _PD_DPAM_VER_2_1_HIGHER = 0x01,
}EnumTypeCPDDpamVersion;

// Enumeration of PD Rx FIFO Receive Error Status
typedef enum
{
    _PD_RX_MSG_CORRECT = 0x00,
    _PD_RX_MSG_NOD_MIS = _BIT0,
    _PD_RX_MSG_SEPC_VER_MIS = _BIT3,
    _PD_RX_MSG_DR_MIS = _BIT4,
    _PD_RX_MSG_CP_MIS = _BIT5,
    _PD_RX_MSG_PR_MIS = _BIT6,
}EnumTypeCRxFifoErrStatus;

// Enumeration of Check DP Status Result
typedef enum
{
    _PD_CONFIG_NOT_REQUIRED = 0x00,
    _PD_CONFIG_REQUIRED = 0x01,
}EnumTypeCPDDpStatusCheckResult;

// Enumeration of Alt Mode Urgent Status
typedef enum
{
    _PD_ALT_MODE_NOT_URGENT = 0x00,
    _PD_ALT_MODE_URGENT = 0x01,
}EnumTypeCPDAltModeUrgentStatus;

// Enumeration of Hp Atten_type
typedef enum
{
    _PD_HP_ATTEN_NONE = 0x00,
    _PD_HP_ATTEN_VWIRE = 0x01,
    _PD_HP_ATTEN_CONFIG = 0x02,
    _PD_HP_ATTEN_DATA = 0x03,
    _PD_HP_ATTEN_DISCONNECT = 0x04,
}EnumTypeCPDHpAttenType;

// Enumeration of Hp Vwire Operation
typedef enum
{
    _PD_HP_VWIRE_OP_NONE = 0x00,
    _PD_HP_VWIRE_OP_DEASSERT = 0x01,
    _PD_HP_VWIRE_OP_ASSERT = 0x02,
    _PD_HP_VWIRE_OP_TOGGLE = 0x03,
    _PD_HP_VWIRE_OP_SAMPLE = 0x04,
    _PD_HP_VWIRE_OP_ONE_SHOT = 0x08,
}EnumTypeCPDHpVwireOperation;

#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
// Enumeration of PD BIST Mode
typedef enum
{
    _PD_BIST_MODE_NONE = 0x00,
    _PD_BIST_CARRIER_MODE = 0x05,
    _PD_BIST_TEST_DATA_MODE = 0x08,
}EnumTypeCPDBistMode;
#endif

//--------------------------------------------------
// USB-C Related Structs
//--------------------------------------------------
// Type-C Orientation Structure
typedef struct
{
    EnumTypeCAttachStatus enumAttachStatus;
    EnumTypeCOrientation enumOrientation;
    EnumTypeCPinCfgType enumPinAssignment;
    EnumTypeCAltModeStatus enumAltModeStatus;
    // -----------------------------
    BYTE b1PowerContract : 1;
} StructTypeCInfo;

// USB-C Related Information Struct
typedef struct
{
    BYTE b5State : 5;
    EnumTypeCEmbTypeCCCFWState b3AttachStatus : 3;
    // -----------------------------
    EnumTypeCCCDetResistor b3CC1Resistor : 3;
    EnumTypeCCCDetResistor b3CC2Resistor : 3;
    BYTE b1FRSrcEnable : 1;
    BYTE b1FRSnkEnable : 1;
    // -----------------------------
    EnumTypeCOrientation enumOrientation;
    // -----------------------------
    BYTE ucDischargeCount;
    // -----------------------------
    WORD b1AcOnReconnect : 1;
    WORD b1Error : 1;
    WORD b1RaExist : 1;
    WORD b1VconnStatus : 1;
    WORD b1ConnectEnable : 1;
    WORD b1ResetFlag  : 1;
    WORD b10DefCurrent : 10;
    WORD usDefOcpCurrent;
    // -----------------------------
    BYTE b2PortRole : 2;
    BYTE b2DrpPrefer : 2;
    BYTE b1CCAttached : 1;
    BYTE b1DeviceDetect : 1;
    BYTE b1AttachedSrcToTryWaitSnk : 1;
    BYTE b1TryWaitSnkState : 1;
}StructTypeCEmbInfo;

// Type-C Power Related Information Struct
typedef struct
{
#if((_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT) || (_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT))
    BYTE b1VbusStatus : 1;
    WORD usMaxPower;
    WORD usReqPower;
    WORD usOutputVol;
    WORD b10OutputCur : 10;
    WORD usOcpCurrent;
#endif
    WORD b105VUpBound : 10;
    WORD b105VLowBound : 10;
    WORD b100VUpBound : 10;
    WORD b10LocPowOn : 10;
    WORD b10LocPowOff : 10;
}StructTypeCPowerInfo;

// Type-C Power Protect Info
typedef struct
{
    BYTE ucOcpCurRatio;
}StructTypeCPowerProtectInfo;

// PMIC IIC Structure
typedef struct
{
    BYTE b1PmicIICSetStart : 1;
    BYTE b1PmicIICMainLoop : 1;
    BYTE b1PmicIICExint0Loop : 1;
    BYTE b1PmicIICWdintLoop : 1;
    BYTE b1PmicIICExint0EverLoop : 1;
    BYTE b1PmicIICWdintEverLoop : 1;
} StructPmicIICStatus;

// PD Cable Status Info
typedef struct
{
    WORD b10CableMaxCur : 10;
    WORD b4CableState : 4;
    WORD b2CableSpecVer : 2;
    // -----------------------------
    WORD b10CableMaxVol : 10;   // Unit = 100mV
    WORD b5DiscoverIdRetryFailCnt : 5;
    WORD b1CableModalOperation : 1;
    // -----------------------------
    EnumTypeCCablePdCapability enumTypeCCablePdCap;
    EnumTypeCPDCableProductType enumTypeCCableProductType;
    EnumTypeCPDCableConnectorType enumTypeCCableConnectorType;
    EnumTypeCPDCableTerminationType enumTypeCCableTerminationType;
    EnumTypeCPDCableSbuType enumTypeCCableSbuType;
    EnumTypeCPDCableUsbLanesSupport enumTypeCCableUsbLanesSupport;
    EnumTypeCPDSvdmVersion enumTypeCCableSvdmVersion;
    EnumTypeCPDDpamVersion enumTypeCCableDpamVersion;
    EnumTypeCPDCablePinAssignment enumTypeCCablePinAssignment;
    EnumTypeCPDCableTbt3ProductType enumTypeCCableTbt3ProductType;
    EnumTypeCPDCableTbt3Direction enumTypeCCableTbt3Direction;
    EnumTypeCPDCableTbt3RoundedSupport enumTypeCCableTbt3RoundedSupport;
    EnumTypeCPDCableTbt3Speed enumTypeCCableTbt3Speed;
    EnumTypeCPDCableUsbHighestSpeed enumTypeCCableUsbHighestSpeed;
    EnumTypeCPDCableU3ToU0TransitionMode enumTypeCCableU3ToU0TransitionMode;
    BYTE b1CableVconnRequired : 1;
    BYTE b1CableVbusThrough : 1;
    BYTE b1CableSopPP : 1;
    BYTE b1CableUSB4 : 1;
    BYTE b1CableUSB3_2 : 1;
    BYTE b1ChargeThroughSupport : 1;
    BYTE b1CableSoftRstReq : 1;
    BYTE b1CableSbuSupport : 1;
    // -----------------------------
    BYTE b1CableDpEnterDpModeSupport : 1;
    BYTE b1CableSvidSearchFinish : 1;
    BYTE b1CableDpSvidSupport : 1;
    BYTE b1CableDpModeInfoReceived : 1;
    BYTE b1CableTbt3SvidSupport : 1;
    BYTE b1CableTbt3Retimer : 1;
    BYTE b1CableTbt3Optical : 1;
    BYTE b1CableEprModeCapable : 1;
}StructTypeCCableStatus;

// EPR Mode Info
typedef struct
{
    EnumTypeCPDEPRModeAction enumPDEPRModeAction;
    EnumTypeCPDEnterEPRFailedReason enumPDEnterEPRFailedReason;
    EnumTypeCPDExtCtrlType enumPDExtCtrlType;
    // -----------------------------
    BYTE ucPartnerEPRSinkPDP;
    // -----------------------------
    BYTE b1EnterEPRFlow : 1;
    BYTE b1EPRMode : 1;
    BYTE b1EPRSRCCapable : 1;
}StructTypeCEPRModeInfo;

// PD Alt. Mode Info
typedef struct
{
    BYTE ucRcvVdmMsg;
    // -----------------------------
    BYTE ucVdmSVID_H;
    // -----------------------------
    BYTE ucVdmSVID_L;
    // -----------------------------
    EnumTypeCPinCfgType enumDpRxPinAssignment;
    // -----------------------------
    EnumTypeCPinCfgCapType enumPinAssignmentCap;
    // -----------------------------
    BYTE ucPartnerPinAssignmentCap;
    // -----------------------------
    EnumTypeCUFPProductType enumUFPProductType;
    // -----------------------------
    EnumTypeCDFPProductType enumDFPProductType;
    // -----------------------------
    EnumTypeCLenovoDeviceType enumLenovoDeviceType;
    // -----------------------------
    BYTE ucLenovoDockingEvent;
    // -----------------------------
    BYTE ucLenovoSystemAcknowledge;
    // -----------------------------
    BYTE ucLenovoSystemEvent;
    // -----------------------------
    BYTE b3VdmObjPos : 3;
    BYTE b3DpObjPos : 3;
    BYTE b1AltModeFunc : 1;
    BYTE b1RcvVdmType : 1;
    // -----------------------------
    BYTE b3LenovoObjPos : 3;
    BYTE b3LenovoAttnCnt : 3;
    BYTE b2PartnerVdmNoRespCnt : 2;
    // -----------------------------
    BYTE b2CblVdmNoRespCnt : 2;
    BYTE b2VdmRespConflictCnt : 2;
    BYTE b1PartnerInitAltMode : 1;
    BYTE b1MultiFunctionBit : 1;
    BYTE b1DpSvidSearchFinish : 1;
    BYTE b1DpAltModeEnter : 1;
    // -----------------------------
    BYTE b1DpAltModeConfig : 1;
    BYTE b1DpAltModeTargetConfig : 1;
    BYTE b1DpAltModeWaitConfig : 1;
    BYTE b1DpAltModeExit : 1;
    BYTE b1LenovoAttnSent : 1;
    BYTE b3VdmBusyCnt : 3;
    // -----------------------------
    BYTE b1LenovoAltModeEnter : 1;
    BYTE b1AttentionWait : 1;
    BYTE b1MultiFunctionChange : 1;
    BYTE b1MultiFunctionChangeDone : 1;
    BYTE b1ForceHpdIrq : 1;
}StructTypeCAltModeInfo;

// PD Acer Alt Mode Info
typedef struct
{
    BYTE b6AcerAltModeState : 6;
    BYTE b1AcerAltModeEnter : 1;
}StructTypeCAcerAltModeInfo;

// PD Hp Alt Mode Info
typedef struct
{
    BYTE b1HpAltModeEnter : 1;
    BYTE b7HpI2cAddr : 7;
    // -----------------------------
    BYTE b6HpAltModeState : 6;
    BYTE b2HpOwnAmAddr_H : 2;
    // -----------------------------
    BYTE ucHpOwnAmAddr_L;
    // -----------------------------
    BYTE ucHpOwnAmAddr_M;
    // -----------------------------
    BYTE b3HpAttenCnt : 3;
    EnumTypeCPDHpVwireOperation enumHpVwireOp;
    EnumTypeCPDHpAttenType enumHpAttenType;
}StructTypeCHpAltModeInfo;

// Struct for Type-C Hp Alt Mode System Event Queue
typedef struct
{
    BYTE b3SysEventCnt : 3;
    BYTE b3SysEventHead : 3;
    BYTE b3SysEventTail : 3;
    StructTypeCHpSysEvent pstSysEvent[_TYPE_C_PD_HP_SYS_EVENT_QUEUE_SIZE];
}StructTypeCHpSysEventQueue;

// PD Dell Alt Mode Info
typedef struct
{
    BYTE b6DellAltModeState : 6;
    BYTE b1DellAltModeEnter : 1;
    BYTE b1DellAMTimeout : 1;
    // -----------------------------
    BYTE b3DellObjPos : 3;
    BYTE b3DellAttenCnt : 3;
    BYTE b1DellAttenWait : 1;
    BYTE b1DellInitComplete : 1;
}StructTypeCDellAltModeInfo;

// PD 3.0 Extended Message Header
typedef struct
{
    WORD b1Chunked : 1;
    WORD b4ChunkNum : 4;
    WORD b1ChunkRequest : 1;
    WORD b9DataSize : 9;
    WORD b1TxChunked : 1;
    // -----------------------------
    BYTE b4TxChunkNum : 4;
}StructTypeCExtMsgInfo;

// PD Current Status Info
typedef struct
{
    EnumTypeCPDState b8PDState : 8;
    // -----------------------------
    EnumTypeCPDSubState b8PDSubState : 8;
    // -----------------------------
    EnumTypeCPDAltModeState b8PDDpAltState : 8;
    // -----------------------------
    BYTE b6PDLenovoAltState : 6;
    BYTE b1PDPowerContract : 1;
    BYTE b1UnconstrainedPower : 1;
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
    BYTE b1PDFunctionEnable : 1;
    BYTE b1PDPowerRole : 1;
    // -----------------------------
    EnumDPAmsState b2PDAmsStatus : 2;
    BYTE b1PDDataRole : 1;
    BYTE b1PDVconnRole : 1;
    BYTE b1PDDRSwapReject : 1;
    BYTE b1PDVconnSwapReject : 1;
    BYTE b1GetSnkCapSent : 1;
    BYTE b1GetSrcCapSent : 1;
    // -----------------------------
    BYTE b1RcvSnkCap : 1;
    BYTE b1RcvSrcCap : 1;
    BYTE b1DRSwapReq : 1;
    BYTE b1ReqWait : 1;
    BYTE b1PRSwapWait : 1;
    BYTE b1DRSwapWait : 1;
    BYTE b1SrcCapSent : 1;
    BYTE b1SnkCapWait : 1;
    // -----------------------------
    BYTE b1VCSwapWait : 1;
    BYTE b1HRST_Pwr_Off : 1;
    BYTE b1PRS_Processing : 1;
    BYTE b1InteropS8 : 1;
    BYTE b1AlertSent : 1;
    BYTE b1GetSnkCapWait : 1;
    BYTE b1VdmMsgWait : 1;
    BYTE b1PDPRSwapReject : 1;
    // -----------------------------
    EnumTypeCReqType enumReqType;
    // -----------------------------
    BYTE ucTargetVolRDO;
    // -----------------------------
    WORD b1VdmBusy : 1;
    WORD b1PDHandlerOngoing : 1;
    WORD b10WDTimer : 10;
}StructTypeCPDStatus;

//--------------------------------------------------
// Struct for Type-C Source Capability PDO Content
//--------------------------------------------------
typedef struct
{
    EnumTypeCPDPdoType enumPdoType;
    // -----------------------------
    WORD usMaxVoltage;   // Unit = 10mV
    WORD usMinVoltage;   // Unit = 10mV
    // -----------------------------
    WORD b2PeakCurrent : 2;
    WORD b10MaxCurrent : 10;
}StructTypeCPDO;

// Power Delivery Alt. Mode HPD Queue
typedef struct
{
    BYTE b1HpdStatus : 1;
    BYTE b3HpdCnt : 3;
    BYTE b2HpdWptr : 2;
    BYTE b2HpdRptr : 2;
    // -----------------------------
    EnumTypeCPDHpdType penumHpdType[_HPD_QUEUE_DEPTH];
    WORD pusHpdSpace[_HPD_QUEUE_DEPTH];
}StructTypeCHpdQueue;

// USB-C PD SNK Request Normal RDO Struct
typedef struct
{
    WORD usVoltage;
    // -----------------------------
    WORD b4ObjPos : 4;
    WORD b10OpCurrent : 10;
    WORD b1CapMis : 1;
    WORD b1GiveBack : 1;
    // -----------------------------
    WORD b1PPSSmallStep : 1;
    WORD b1AVSSmallStep : 1;
    WORD b10MaxCurrent : 10;
}StructTypeCSnkRDO;

// PD Power Contract Negotiated Status
typedef struct
{
    WORD usVoltage;
    WORD usCurrent;
    // -----------------------------
    BYTE b4ObjPos : 4;
}StructTypeCPdoStatus;

// Power Delivery Alt. Mode HPD Queue
typedef struct
{
    BYTE b1Valid : 1;
    BYTE b1CancelSrcEprKeepAlive : 1;
    EnumScalerTimerEventID enumEventID;
    WORD usEventTime;
}StructTypeCPdTimerEvent;

// Power Delivery Event
typedef struct
{
    EnumTypeCPDSysEvent enumSystemEvent; // Power Delivery System Request Event
    EnumTypeCPDPortCtrlEvent enumPortCtrlEvent; // Power Delivery Port Controller Inform System / User of Events Occurred
}StructTypeCPdEvent;

// PD Message Transmit / Receive Info
typedef struct
{
    EnumTypeCPDCmd b8RcvMsg : 8;
    // -----------------------------
    EnumTypeCRxFifoErrStatus b8FifoRcvErrStatus : 8;
    // -----------------------------
    BYTE b3RcvNodCnt : 3;
    EnumTypeCTxSentResult b5TxResult : 5;
    // -----------------------------
    EnumTypeCTxRetryFailEvent b3TxRetryFailEvent : 3;
    BYTE b1IntOverWrite : 1;
    BYTE b1FifoClr : 1;
    BYTE b1BusIdle : 1;
}StructTypeCMsgInfo;

// PD Info From Port Partner Src/Snk Capability
typedef struct
{
    EnumTypeCPDSrcCapValid enumSrcCapValid;
    EnumTypeCPDSvdmVersion enumSvdmVersion;
    EnumTypeCPDDpamVersion enumDpamVersion;
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
}StructTypeCPdPartnerInfo;

// PD DP Tx Alt Mode HPD Queue
typedef struct
{
    BYTE b3TxHpdCnt : 3;
    EnumTypeCPDHpdType penumTxHpdType[_HPD_QUEUE_DEPTH];
}StructTypeCTxHpdQueue;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile EnumSysModeStatusForUsb g_enumTypeCSysModeStatus;
extern StructTypeCInfo g_pstTypeCInfo[_TYPE_C_PORT_VALID];
extern volatile StructTypeCCableInfoForDpcd g_pstTypeCCableInfoForDpcd[_TYPE_C_PORT_VALID];

#if(_EMB_TYPE_C_0_MAPPING != _VALUE_NO_TYPE_C_PORT)
extern volatile StructTypeCPowerInfo g_stTypeC0PowerInfo;
extern StructTypeCPowerProtectInfo g_pstTypeC0PowerProtectInfo[_MAX_DATA_OBJ_CNT];
#endif
#if(_EMB_TYPE_C_1_MAPPING != _VALUE_NO_TYPE_C_PORT)
extern volatile StructTypeCPowerInfo g_stTypeC1PowerInfo;
extern StructTypeCPowerProtectInfo g_pstTypeC1PowerProtectInfo[_MAX_DATA_OBJ_CNT];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern BYTE ScalerTypeCGetTypeCIndex(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ScalerTypeCGetTypeCIndex_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE ScalerTypeCGetTypeCIndex_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCAttachStatus ScalerTypeCRxGetCcAttach(EnumInputPort enumInputPort);
extern EnumTypeCAttachStatus ScalerTypeCTxGetCcAttach(EnumOutputPort enumOutputPort);
extern EnumTypeCAttachStatus ScalerTypeCRxGetCcAttach_EXINT0(EnumInputPort enumInputPort);
extern EnumTypeCAttachStatus ScalerTypeCTxGetCcAttach_EXINT0(EnumOutputPort enumOutputPort);
extern EnumTypeCAttachStatus ScalerTypeCRxGetCcAttach_WDINT(EnumInputPort enumInputPort);
extern EnumTypeCAttachStatus ScalerTypeCTxGetCcAttach_WDINT(EnumOutputPort enumOutputPort);
extern EnumTypeCOrientation ScalerTypeCRxGetOrientation(EnumInputPort enumInputPort);
extern EnumTypeCOrientation ScalerTypeCTxGetOrientation(EnumOutputPort enumOutputPort);
extern EnumTypeCOrientation ScalerTypeCRxGetOrientation_EXINT0(EnumInputPort enumInputPort);
extern EnumTypeCOrientation ScalerTypeCTxGetOrientation_EXINT0(EnumOutputPort enumOutputPort);
extern EnumTypeCOrientation ScalerTypeCRxGetOrientation_WDINT(EnumInputPort enumInputPort);
extern EnumTypeCOrientation ScalerTypeCTxGetOrientation_WDINT(EnumOutputPort enumOutputPort);
extern EnumTypeCPinCfgType ScalerTypeCRxGetPinAssignment(EnumInputPort enumInputPort);
extern EnumTypeCPinCfgType ScalerTypeCTxGetPinAssignment(EnumOutputPort enumOutputPort);
extern EnumTypeCPinCfgType ScalerTypeCRxGetPinAssignment_EXINT0(EnumInputPort enumInputPort);
extern EnumTypeCPinCfgType ScalerTypeCTxGetPinAssignment_EXINT0(EnumOutputPort enumOutputPort);
extern EnumTypeCPinCfgType ScalerTypeCRxGetPinAssignment_WDINT(EnumInputPort enumInputPort);
extern EnumTypeCPinCfgType ScalerTypeCTxGetPinAssignment_WDINT(EnumOutputPort enumOutputPort);
extern EnumTypeCAltModeStatus ScalerTypeCRxGetAltModeReady(EnumInputPort enumInputPort);
extern EnumTypeCAltModeStatus ScalerTypeCTxGetAltModeReady(EnumOutputPort enumOutputPort);
extern EnumTypeCAltModeStatus ScalerTypeCRxGetAltModeReady_EXINT0(EnumInputPort enumInputPort);
extern EnumTypeCAltModeStatus ScalerTypeCTxGetAltModeReady_EXINT0(EnumOutputPort enumOutputPort);
extern EnumTypeCAltModeStatus ScalerTypeCRxGetAltModeReady_WDINT(EnumInputPort enumInputPort);
extern EnumTypeCAltModeStatus ScalerTypeCTxGetAltModeReady_WDINT(EnumOutputPort enumOutputPort);
extern bit ScalerTypeCRxGetExplicitContract(EnumInputPort enumInputPort);
extern bit ScalerTypeCTxGetExplicitContract(EnumOutputPort enumOutputPort);
extern bit ScalerTypeCRxGetExplicitContract_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerTypeCTxGetExplicitContract_EXINT0(EnumOutputPort enumOutputPort);
extern bit ScalerTypeCRxGetExplicitContract_WDINT(EnumInputPort enumInputPort);
extern bit ScalerTypeCTxGetExplicitContract_WDINT(EnumOutputPort enumOutputPort);
extern StructTypeCCableInfoForDpcd ScalerTypeCRxGetCableInfoForDpcd(EnumInputPort enumInputPort);
extern StructTypeCCableInfoForDpcd ScalerTypeCRxGetCableInfoForDpcd_EXINT0(EnumInputPort enumInputPort);
extern StructTypeCCableInfoForDpcd ScalerTypeCRxGetCableInfoForDpcd_WDINT(EnumInputPort enumInputPort);
extern bit ScalerTypeCRxGetExtPinELaneSwapByScaler(EnumInputPort enumInputPort);
extern bit ScalerTypeCTxGetExtPinELaneSwapByScaler(EnumOutputPort enumOutputPort);
extern bit ScalerTypeCRxGetExtPinELaneSwapByScaler_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerTypeCTxGetExtPinELaneSwapByScaler_EXINT0(EnumOutputPort enumOutputPort);
extern bit ScalerTypeCTxCheckTypeCSupportOn(EnumOutputPort enumOutputPort);
extern bit ScalerTypeCRxCheckTypeCSupportOn_EXINT0(EnumInputPort enumInputPort);
extern bit ScalerTypeCTxCheckTypeCSupportOn_EXINT0(EnumOutputPort enumOutputPort);
extern bit ScalerTypeCRxCheckTypeCSupportOn_WDINT(EnumInputPort enumInputPort);
extern bit ScalerTypeCTxCheckTypeCSupportOn_WDINT(EnumOutputPort enumOutputPort);

#if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
extern void ScalerTypeCInitial(void);
extern EnumTypeCPcbPort ScalerTypeCxPcbxMapping(EnumTypeCEmbeddedList enumTypeCIndex);
extern EnumTypeCPcbPort ScalerTypeCxPcbxMapping_EXINT0(EnumTypeCEmbeddedList enumTypeCIndex);
extern EnumTypeCPcbPort ScalerTypeCxPcbxMapping_WDINT(EnumTypeCEmbeddedList enumTypeCIndex);

#if((_EMB_TYPE_C_0_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING) ||\
    (_EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING))
extern bit ScalerTypeCGetPmicInterruptDetectStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern bit ScalerTypeCGetPmicAlertDetectStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

extern void ScalerTypeCPdPushHpd(EnumInputPort enumInputPort, EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime);
extern void ScalerTypeCPdPushHpd_EXINT0(EnumInputPort enumInputPort, EnumTypeCPDHpdType enumHpdType, WORD usHpdSpaceTime);
extern void ScalerTypeCPdDpCTSForceHpdIrq(EnumInputPort enumInputPort);
extern void ScalerTypeCPdDpCTSForceHpdIrq_EXINT0(EnumInputPort enumInputPort);
extern void ScalerTypeCPdDpCTSForceHpdIrq_WDINT(EnumInputPort enumInputPort, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
extern EnumTypeCPDHpdType ScalerTypeCRxGetHPDQueue(EnumInputPort enumInputPort, BYTE ucIndex);
extern BYTE ScalerTypeCRxGetHPDQueueReadPointer(EnumInputPort enumInputPort);
extern StructTypeCTxHpdQueue ScalerTypeCTxGetHPDQueue(EnumOutputPort enumOutputPort);

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
extern void ScalerTypeCGetAltModeBillboardInfo(EnumTypeCPcbPort enumTypeCPcbPort, BYTE *pucBillboardAltModeInfo);
#endif

#endif // End of #if(_PORT_CTRL_EMBEDDED_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

