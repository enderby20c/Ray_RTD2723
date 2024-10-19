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
// ID Code      : ScalerTypeCInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definition of Default OCP Ratio
//--------------------------------------------------
#define _TYPE_C_PMIC_DEF_OCP_RATIO                  105 // Unit: %

//--------------------------------------------------
// Definition of Default PMIC Portection Debounce
//--------------------------------------------------
#define _TYPE_C_PMIC_DEF_OVP_DEBOUNCE               0 // Unit: Judge_Time
#define _TYPE_C_PMIC_DEF_UVP_DEBOUNCE               0 // Unit: Judge_Time
#define _TYPE_C_PMIC_DEF_OCP_DEBOUNCE               0 // Unit: Judge_Time


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumeration Of USB Scaler Level Mode Status
//--------------------------------------------------
typedef enum
{
    _USB_SYS_MODE_STATUS_INITIAL = 0x00,
    _USB_SYS_MODE_STATUS_DISPLAY_INITIAL,
    _USB_SYS_MODE_STATUS_DISPLAY_SETTING,
    _USB_SYS_MODE_STATUS_DISPLAY_CHECK,
    _USB_SYS_MODE_STATUS_POWER_SAVING,
    _USB_SYS_MODE_STATUS_POWER_OFF,
    _USB_SYS_MODE_STATUS_FACTORY,
    _USB_SYS_MODE_STATUS_NONE = 0xFF,
}EnumSysModeStatusForUsb;

//--------------------------------------------------
// Enumerations of Type-C Channel
//--------------------------------------------------
typedef enum
{
    _TYPE_C_CC1 = 0,
    _TYPE_C_CC2 = 1,
}EnumTypeCChannel;

//--------------------------------------------------
// Enumerations of Type-C CC Detect Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_CC_DETECT_LOW = 0,
    _TYPE_C_CC_DETECT_HIGH = 1,
}EnumTypeCCcDetectStatus;

//--------------------------------------------------
// Enumerations of Type-C Attach Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_UNATTACH = 0,
    _TYPE_C_ATTACH = 1,
}EnumTypeCAttachStatus;

//--------------------------------------------------
// Enumerations of Type-C DP Alt Mode Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ALT_MODE_NOT_READY = 0,
    _TYPE_C_ALT_MODE_READY = 1,
}EnumTypeCAltModeStatus;

//--------------------------------------------------
// Enumerations of Type-C DP Alt Mode Wait Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ALT_MODE_NOT_WAIT = 0,
    _TYPE_C_ALT_MODE_WAIT = 1,
}EnumTypeCAltModeWaitStatus;

//--------------------------------------------------
// Enumerations of Type-C Data Role
//--------------------------------------------------
typedef enum
{
    _TYPE_C_DATA_ROLE_NONE = 0x00,
    _TYPE_C_UFP_U = 0x01,
    _TYPE_C_DFP_U = 0x02,
}EnumTypeCDataRole;

//--------------------------------------------------
// Enumeration Of Type-C Orientation
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ORIENTATION_NONE = 0x00,
    _TYPE_C_ORIENTATION_UNFLIP = 0x01,
    _TYPE_C_ORIENTATION_FLIP = 0x02,
}EnumTypeCOrientation;

//--------------------------------------------------
// Definitions of Type-C Multi-Function Preferred Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_MULTI_FUNC_NOT_PREFER = 0,
    _TYPE_C_MULTI_FUNC_PREFER = 1,
    _TYPE_C_MULTI_FUNC_DEFAULT,
}EnumTypeCMultiFuncStatus;

//--------------------------------------------------
// Enumerations of Type-C Pin Assignment Mode
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PIN_ASSIGNMENT_CAP_NONE = 0x00,
    _TYPE_C_PIN_ASSIGNMENT_CAP_C = 0x04,
    _TYPE_C_PIN_ASSIGNMENT_CAP_CD = 0x0C,
    _TYPE_C_PIN_ASSIGNMENT_CAP_CE = 0x14,
    _TYPE_C_PIN_ASSIGNMENT_CAP_CDE = 0x1C,
    _TYPE_C_PIN_ASSIGNMENT_CAP_DEFAULT,
}EnumTypeCPinCfgCapType;

//--------------------------------------------------
// Enumerations of Type-C Pin Assignment Mismatch Action
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PIN_ASSIGNMENT_MISMATCH_NO_ACTION = 0x00,
    _TYPE_C_PIN_ASSIGNMENT_MISMATCH_RECONNECT = 0x01,
    _TYPE_C_PIN_ASSIGNMENT_MISMATCH_WAIT_CONFIG = 0x02,
}EnumTypeCPinMismatchAction;

//--------------------------------------------------
// Enumerations of Type-C Function Support Option
//--------------------------------------------------
typedef enum
{
    _TYPE_C_SUPPORT_DEFAULT_FUNCTION = 0x00,            // Default Function (Full Function)
    _TYPE_C_SUPPORT_NO_FUNCTION = 0x01,                 // No TypeC Function (CC Pin Floating)
    _TYPE_C_SUPPORT_CC_FUNCTION = 0x02,                 // CC (Max Cur = 3.0A, No PD)
    _TYPE_C_SUPPORT_CC_AND_PD_FUNCTION = 0x03,          // CC / PD (no Alt Mode)
    _TYPE_C_SUPPORT_FULL_FUNCTION = 0x04,               // CC / PD / Alt Mode, All Feature Support
}EnumTypeCFunctionSupport;

//--------------------------------------------------
// Enumerations of Type-C Operation Mode
//--------------------------------------------------
typedef enum
{
    _TYPE_C_DEFAULT_OPERATION_MODE = 0x00,              // Default Operation Mode (From PCB Define Setting)
    _TYPE_C_SRC_ONLY_MODE = 0x01,
    _TYPE_C_SNK_ONLY_MODE = 0x02,
    _TYPE_C_DRP_NO_PREFERENCE_MODE = 0x03,
    _TYPE_C_DRP_TRY_SNK_MODE = 0x04,
    _TYPE_C_DRP_TRY_SRC_MODE = 0x05,
}EnumTypeCOperationMode;

//--------------------------------------------------
// Enumerations of Type-C Port Ctrl PDO from User (Src/Snk Cap)
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PDO_FROM_KERNEL = 0x00,
    _TYPE_C_PDO_FROM_USER = 0x01,
}EnumTypeCPdoReference;

//--------------------------------------------------
// Enumerations of Type-C Port Ctrl RDO from User (Request)
//--------------------------------------------------
typedef enum
{
    _TYPE_C_RDO_FROM_KERNEL = 0x00,
    _TYPE_C_RDO_FROM_USER = 0x01,
}EnumTypeCRdoReference;

//--------------------------------------------------
// Enumerations of Type-C Embedded Port Ctrl Vbus Protect by Kernel / User
//--------------------------------------------------
typedef enum
{
    _TYPE_C_VBUS_PROTECT_BY_KERNEL = 0x00,
    _TYPE_C_VBUS_PROTECT_BY_USER = 0x01,
}EnumTypeCEmbVbusProtectReference;

//--------------------------------------------------
// Enumeration of PD Check PDO Change
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PDO_NO_CHANGE = 0x0,
    _TYPE_C_PDO_CHANGE = 0x1,
}EnumPdoCheck;

//--------------------------------------------------
// Enumerations of Type-C PDO Count from User
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PDO_NUM_0 = 0x00,
    _TYPE_C_PDO_NUM_1 = 0x01,
    _TYPE_C_PDO_NUM_2 = 0x02,
    _TYPE_C_PDO_NUM_3 = 0x03,
    _TYPE_C_PDO_NUM_4 = 0x04,
    _TYPE_C_PDO_NUM_5 = 0x05,
    _TYPE_C_PDO_NUM_6 = 0x06,
    _TYPE_C_PDO_NUM_7 = 0x07,
    _TYPE_C_PDO_NUM_8 = 0x08,
    _TYPE_C_PDO_NUM_9 = 0x09,
    _TYPE_C_PDO_NUM_10 = 0x0A,
    _TYPE_C_PDO_NUM_11 = 0x0B,
}EnumTypeCPdoNumber;

//--------------------------------------------------
// Enumerations of Type-C Request Type
//--------------------------------------------------
typedef enum
{
    _TYPE_C_REQ_CUSTOMIZED_RDO = 0x00,                  // Request Customized Voltage and Current
    _TYPE_C_REQ_LOWEST_VOL = 0x01,                      // Request the PDO of Lowest Voltage (The Current will Select the Max. Current in the PDO)
    _TYPE_C_REQ_HIGHEST_VOL = 0x02,                     // Request the PDO of Highest Voltage (The Current will Select the Max. Current in the PDO)
    _TYPE_C_REQ_TARGET_VOL = 0x03,                      // Request the PDO of Target Voltage (The Current will Select the Max. Current in the PDO)
}EnumTypeCReqType;

//--------------------------------------------------
// Enumerations of Target Voltage for Type-C RDO
//--------------------------------------------------
typedef enum
{
    _TYPE_C_RDO_NO_TARGET = 0x00,
    _TYPE_C_RDO_5V = 0x01,
    _TYPE_C_RDO_5_1V = 0x02,
    _TYPE_C_RDO_9V = 0x03,
    _TYPE_C_RDO_12V = 0x04,
    _TYPE_C_RDO_15V = 0x05,
    _TYPE_C_RDO_20V = 0x06,
}EnumTypeCTargetVolRDO;

//--------------------------------------------------
// Enumerations of Embedded Type-C System Event
//--------------------------------------------------
typedef enum
{
    _PD_SYS_EVENT_NONE = 0x00,                          // No Request Event to Embedded PD Ctrl
    _PD_SYS_EVENT_SEND_SRC_CAP = _BIT0,                 // Request Embedded PD Ctrl to Send Src Cap
    _PD_SYS_EVENT_SEND_REQUEST = _BIT1,                 // Request Embedded PD Ctrl to Send Request
    _PD_SYS_EVENT_SEND_HARD_RESET = _BIT2,              // Request Embedded PD Ctrl to Send Hard Reset
    _PD_SYS_EVENT_POWER_OCP = _BIT3,                    // Inform Embedded PD Ctrl of Vbus OCP Triggered
    _PD_SYS_EVENT_POWER_OVP = _BIT4,                    // Inform Embedded PD Ctrl of Vbus OVP Triggered
    _PD_SYS_EVENT_POWER_UVP = _BIT5,                    // Inform Embedded PD Ctrl of Vbus UVP Triggered
    _PD_SYS_EVENT_VCONN_OCP = _BIT6,                    // Inform Embedded PD Ctrl of Vconn OCP Triggered
    _PD_SYS_EVENT_ERROR_RECOVERY = _BIT7,               // Request Embedded PD Ctrl to Do Error Recovery
    _PD_SYS_EVENT_ALERT_EVENT = _BIT8,                  // Inform Embedded PD Ctrl that Alert Event Triggered
    _PD_SYS_EVENT_STATUS_EVENT = _BIT9,                 // Inform Embedded PD Ctrl that Status Event Triggered
    _PD_SYS_EVENT_SEND_GET_STATUS_MSG = _BIT10,         // Request Embedded PD Ctrl to Send Get_Status Message
    _PD_SYS_EVENT_ALL = 0xFFF,                          // All System Event
}EnumTypeCPDSysEvent;

//--------------------------------------------------
// Enumerations of Embedded Type-C Port Ctrl Event
//--------------------------------------------------
typedef enum
{
    _PD_PORT_CTRL_EVENT_NONE = 0x00,                    // Port Controller Inform System / User of No Event Occurred
    _PD_PORT_CTRL_EVENT_POWER_OCP = _BIT0,              // Port Controller Inform System / User of Vbus OCP Event Occurred
    _PD_PORT_CTRL_EVENT_POWER_OVP = _BIT1,              // Port Controller Inform System / User of Vbus OVP Event Occurred
    _PD_PORT_CTRL_EVENT_POWER_UVP = _BIT2,              // Port Controller Inform System / User of Vbus UVP Event Occurred
    _PD_PORT_CTRL_EVENT_VCONN_OCP = _BIT3,              // Port Controller Inform System / User of Vconn OCP Event Occurred
    _PD_PORT_CTRL_EVENT_ALERT_EVENT = _BIT4,            // Port Controller Inform System / Alert Event Occurred
    _PD_PORT_CTRL_EVENT_STATUS_EVENT = _BIT5,           // Port Controller Inform System / Status Event Occurred
    _PD_PORT_CTRL_EVENT_ALERT_EVENT_SUCCESS = _BIT6,    // Port Controller Inform System / Alert Event Sent Successfully
    _PD_PORT_CTRL_EVENT_ALERT_EVENT_FAILED = _BIT7,     // Port Controller Inform System / Alert Event Sent Failed
}EnumTypeCPDPortCtrlEvent;

//--------------------------------------------------
// Enumeration of Type-C Alert Type
//--------------------------------------------------
typedef enum
{
    _TYPE_C_TYPE_OF_ALERT_NONE = 0x00,
    _TYPE_C_TYPE_OF_ALERT_RSRV = _BIT0,
    _TYPE_C_TYPE_OF_ALERT_BATSTATUS_CHG = _BIT1,
    _TYPE_C_TYPE_OF_ALERT_OCP = _BIT2,
    _TYPE_C_TYPE_OF_ALERT_OTP = _BIT3,
    _TYPE_C_TYPE_OF_ALERT_OPERATING_CHG = _BIT4,
    _TYPE_C_TYPE_OF_ALERT_SRCINPUT_CHG = _BIT5,
    _TYPE_C_TYPE_OF_ALERT_OVP = _BIT6,
    _TYPE_C_TYPE_OF_ALERT_EXTALERTEVENT = _BIT7,
    _TYPE_C_TYPE_OF_ALERT_ALL = 0xFF,
}EnumTypeCTypeOfAlert;

//--------------------------------------------------
// Enumeration of Type-C Battery Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_BAT_NONE = 0x00,
    _TYPE_C_FIX_BAT_0 = _BIT0,
    _TYPE_C_FIX_BAT_1 = _BIT1,
    _TYPE_C_FIX_BAT_2 = _BIT2,
    _TYPE_C_FIX_BAT_3 = _BIT3,
    _TYPE_C_HOTSWAP_BAT_4 = _BIT4,
    _TYPE_C_HOTSWAP_BAT_5 = _BIT5,
    _TYPE_C_HOTSWAP_BAT_6 = _BIT6,
    _TYPE_C_HOTSWAP_BAT_7 = _BIT7,
    _TYPE_C_BAT_ALL = 0xFF,
}EnumTypeCBatteryStatus;

//--------------------------------------------------
// Enumeration of Type-C Extended Alert Event Type
//--------------------------------------------------
typedef enum
{
    _TYPE_C_EXT_ALERT_EVENT_NONE = 0x00,
    _TYPE_C_EXT_ALERT_EVENT_POWERSTATE_CHG = 0x01,      // DFP Only
    _TYPE_C_EXT_ALERT_EVENT_POWERBUTTON_PRESS = 0x02,   // UFP Only
    _TYPE_C_EXT_ALERT_EVENT_POWERBUTTON_RELEASE = 0x03, // UFP Only
    _TYPE_C_EXT_ALERT_EVENT_CTRL_INIT_WAKE = 0x04,      // UFP Only
    _TYPE_C_EXT_ALERT_EVENT_ALL = 0xFF,
}EnumTypeCExtAlertEventType;

//--------------------------------------------------
// Struct for Type-C Alert Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCTypeOfAlert enumTypeOfAlert;
    EnumTypeCBatteryStatus enumBatStatus;
    EnumTypeCExtAlertEventType enumExtAlertEvent;
}StructTypeCAlertEvent;

//--------------------------------------------------
// Struct for Type-C Status Information
//--------------------------------------------------
typedef struct
{
    // BYTE ucInternalTemp;                             // Status Message, Offset Byte 0
    // EnumTypeCPresentInput enumPresentInput;          // Status Message, Offset Byte 1
    // EnumTypeCPresentBatInput enumPresentBatInput;    // Status Message, Offset Byte 2
    // EnumTypeCEventFlags enumEventFlags;              // Status Message, Offset Byte 3
    // EnumTypeCTempStatus enumTempStatus;              // Status Message, Offset Byte 4
    // EnumTypeCPowerStatus enumPowerStatus;            // Status Message, Offset Byte 5
    BYTE b3NewPowerState : 3;                           // Status Message, Offset Byte 6
    BYTE b3NewPSIndicator : 3;                          // Status Message, Offset Byte 6
}StructTypeCStatusEvent;

//--------------------------------------------------
// Enumerations of Type-C Local Power Exist from User
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LOCAL_POWER_NOT_EXIST = 0x00,
    _TYPE_C_LOCAL_POWER_EXIST = 0x01,
}EnumTypeCLocalPowerExist;

//--------------------------------------------------
// Enumerations of Type-C Unconstrainted Power Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_UNCONSTRAIN_POWER_NOT_EXIST = 0x00,
    _TYPE_C_UNCONSTRAIN_POWER_EXIST = 0x01,
}EnumTypeCUnconstrainPowerExist;

//--------------------------------------------------
// Enumerations of Type-C System Power Management Operation
//--------------------------------------------------
typedef enum
{
    _TYPE_C_SPM_FIX_DEFAULT_POWER = 0x00,
    _TYPE_C_SPM_ADJUST_DYNAMIC_POWER = 0x01,
}EnumTypeCSpmOperation;

//--------------------------------------------------
// Enumeration of PDO Peak Current Types
//--------------------------------------------------
typedef enum
{
    _PD_PEAK_CUR_NONE = 0x00,  // Peak Current = Ioc
    _PD_PEAK_CUR_1 = 0x01,     // 150%(1ms) / 125%(2ms) / 110%(10ms)
    _PD_PEAK_CUR_2 = 0x02,     // 200%(1ms) / 150%(2ms) / 125%(10ms)
    _PD_PEAK_CUR_3 = 0x03,     // 200%(1ms) / 175%(2ms) / 150%(10ms)
}EnumTypeCPDPeakCurType;

//--------------------------------------------------
// Enumeration of Type-C Power Control Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_POWER_ON = 0x00,
    _TYPE_C_POWER_OFF = 0x01,
}EnumTypeCPowerControlStatus;

//--------------------------------------------------
// Enumerations of Type-C CC Function
//--------------------------------------------------
typedef enum
{
    _TYPE_C_CC_FUNCTION_DISABLE = 0x00,
    _TYPE_C_CC_FUNCTION_ENABLE = 0x01,
}EnumTypeCCcFunction;

//--------------------------------------------------
// Struct for Type-C Source/Sink Capability PDO Content for User
//--------------------------------------------------
typedef struct
{
    EnumTypeCPDPdoType enumPdoType;
    EnumTypeCPDPeakCurType enumPeakCurrent;
    // -----------------------------
    WORD usMaxVoltage;  // Unit = 100mV
    WORD usMinVoltage;  // Unit = 100mV
    WORD usMaxCurrent;  // Unit =  10mA
}StructTypeCUserPDO;

//--------------------------------------------------
// Struct for Type-C Sink Information for User
//--------------------------------------------------
typedef struct
{
    WORD usSnkMinPDP;  // Sink Minimum PDP, Unit = 0.1W
    WORD usSnkOpePDP;  // Sink Operational PDP , Unit = 0.1W
    WORD usSnkMaxPDP;  // Sink Maximum PDP, Unit = 0.1W
}StructTypeCSnkInfo;

//--------------------------------------------------
// Enumerations of OCP Include Peak Current
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PEAK_CURRENT_PROTECT_DISABLE = 0x00,
    _TYPE_C_PEAK_CURRENT_PROTECT_ENABLE = 0x01,
}EnumTypeCPDPeakCurProtect;

//--------------------------------------------------
// Struct for Type-C Vbus PMIC Protect Info
//--------------------------------------------------
typedef struct
{
    BYTE ucOcpCurRatio; // Unit = %
    // -----------------------------
    BYTE ucOvpDebounce; // Unit = 1 judgment
    // -----------------------------
    BYTE ucUvpDebounce; // Unit = 1 judgment
    // -----------------------------
    BYTE ucOcpDebounce; // Unit = 1 judgment
    // -----------------------------
    EnumTypeCPDPeakCurProtect enumPeakCurrentProtect;
}StructTypeCVbusProtectInfo;

//--------------------------------------------------
// Struct for Type-C Initial Request Content for User
//--------------------------------------------------
typedef struct
{
    EnumTypeCReqType enumReqType;
    EnumTypeCTargetVolRDO enumTargetVolRDO;
}StructTypeCUserInitRDO;

//--------------------------------------------------
// Struct for Type-C Request Content for User
//--------------------------------------------------
typedef struct
{
    EnumTypeCPdoNumber enumObjPos;  // Object Position
    // -----------------------------
    WORD usReqInfo1;            // Fix RDO (Op. Cur in 10mA) / PPS RDO (Vol in 20mV) / AVS RDO (Vol in 25mV)
    // -----------------------------
    WORD usReqInfo2;            // Fix RDO (Max. Cur in 10mA) / PPS RDO (Op. Cur in 50mA) / AVS RDO (Op. Cur in 50mA)
    // -----------------------------
    BYTE b1CapMismatch : 1;     // Capability Mismatch Flag
    BYTE b1GiveBack : 1;        // Give Back Flag
}StructTypeCUserRDO;

//--------------------------------------------------
// Enumerations of Type-C U3 Mode Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_U3_ON = 0,
    _TYPE_C_U3_OFF = 1,
}EnumTypeCU3ModeType;

//--------------------------------------------------
// Enumerations of TypeC Cable Status Change
//--------------------------------------------------
typedef enum
{
    _TYPE_C_CABLE_UNPLUG = 0x00,
    _TYPE_C_CABLE_PLUG = 0x01,
    _TYPE_C_CABLE_UNCHANGE = 0xFF,
} EnumTypeCCableStatus;

//--------------------------------------------------
// Enumerations of TypeC Cable PD Capability
//--------------------------------------------------
typedef enum
{
    _TYPE_C_CABLE_PD_CAP_UNCONFIRMED = 0x00,
    _TYPE_C_CABLE_NON_PD_CAPABLE = 0x01,
    _TYPE_C_CABLE_DISCOVER_ID_ACK_RECEIVED = 0x02,
} EnumTypeCCablePdCapability;

//--------------------------------------------------
// Enumerations of Type-C UFP Product Type
//--------------------------------------------------
typedef enum
{
    _TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED = _VALUE_TYPE_C_UFP_PRODUCT_TYPE_UNDEFINED,
    _TYPE_C_UFP_PRODUCT_TYPE_HUB = _VALUE_TYPE_C_UFP_PRODUCT_TYPE_HUB,
    _TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL = _VALUE_TYPE_C_UFP_PRODUCT_TYPE_PERIPHERAL,
}EnumTypeCUFPProductType;

//--------------------------------------------------
// Enumerations of Type-C DFP Product Type
//--------------------------------------------------
typedef enum
{
    _TYPE_C_DFP_PRODUCT_TYPE_UNDEFINED = 0x00,
    _TYPE_C_DFP_PRODUCT_TYPE_HUB = 0x01,
    _TYPE_C_DFP_PRODUCT_TYPE_HOST = 0x02,
    _TYPE_C_DFP_PRODUCT_TYPE_BRICK = 0x03,
}EnumTypeCDFPProductType;

//--------------------------------------------------
// Enumerations of DP Alt Mode 2.1 Cable ID
//--------------------------------------------------
typedef enum
{
    _PD_CBL_COMPONENT_PASSIVE = 0x00,
    _PD_CBL_COMPONENT_ACTIVE_RETIMER = 0x01,
    _PD_CBL_COMPONENT_ACTIVE_REDRIVER = 0x02,
    _PD_CBL_COMPONENT_OPTICAL = 0x03,
}EnumTypeCPDCableActiveComponent;

typedef enum
{
    _PD_CBL_MAX_DP_RATE_UNCONFIRMED = 0x00,
    _PD_CBL_MAX_HBR3 = 0x01,
    _PD_CBL_MAX_UHBR10 = 0x03, // UHBR10 Cable Also Support HBR3
    _PD_CBL_MAX_UHBR20 = 0x07, // UHBR20 Cable Also Support UHBR10 & HBR3
}EnumTypeCPDCableMaxDpRate;

// Cable Info For DPCD
typedef struct
{
    EnumTypeCPDCableActiveComponent enumTypeCCableActiveComponent;
    EnumTypeCPDCableMaxDpRate enumTypeCCableMaxDpRate;
    // -----------------------------
    BYTE b1CableUhbr13p5Support : 1;
}StructTypeCCableInfoForDpcd;


/////////////////////
// LENOVO ALT MODE //
/////////////////////

//--------------------------------------------------
// Enumerations of Type-C Lenovo Alt Mode Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_ALT_MODE_NOT_READY = 0,
    _TYPE_C_LENOVO_ALT_MODE_READY = 1,
}EnumTypeCLenovoAltModeStatus;

//--------------------------------------------------
// Enumerations of Type-C Lenovo Device Type
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_DEVICE_TYPE_RESERVED = 0x00,
    _TYPE_C_LENOVO_NOTEBOOK = 0x01,
    _TYPE_C_LENOVO_DOCKING = 0x02,
    _TYPE_C_LENOVO_POWER_ADAPTER = 0x03,
    _TYPE_C_LENOVO_DESKTOP_PC = 0x04,
    _TYPE_C_LENOVO_MONITOR = 0x05,
    _TYPE_C_LENOVO_UPS = 0x06,
    _TYPE_C_LENOVO_DEVICE_TYPE_NONE = 0xFF,
}EnumTypeCLenovoDeviceType;

//--------------------------------------------------
// Enumerations of Type-C Lenovo Device Type Check Result
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_DEVICE_TYPE_INVALID = 0x00,
    _TYPE_C_LENOVO_DEVICE_TYPE_VALID = 0x01,
}EnumTypeCLenovoCheckDeviceTypeResult;

//--------------------------------------------------
// Enumerations of Type-C Lenovo Alt Mode Docking Event Check Busy Result
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_DOCK_EVENT_NOT_BUSY = 0,
    _TYPE_C_LENOVO_DOCK_EVENT_BUSY = 1,
}EnumTypeCLenovoCheckBusyResult;

//--------------------------------------------------
// Enumeration of Type-C Lenovo Alt Mode Docking Power Switch
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_DOCK_POWER_SWITCH_NONE = 0x00,
    _TYPE_C_LENOVO_DOCK_POWER_BUTTON_MAKE = 0x01,
    _TYPE_C_LENOVO_DOCK_POWER_BUTTON_BREAK = 0x02,
}EnumTypeCLenovoDockPowerSwitch;

//--------------------------------------------------
// Enumeration of Type-C Lenovo Alt Mode System Power Mode
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_SYS_DC_MODE = 0x00,
    _TYPE_C_LENOVO_SYS_AC_MODE = 0x01,
}EnumTypeCLenovoSysPowerMode;

//--------------------------------------------------
// Enumeration of Type-C Lenovo Alt Mode System State
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_SYS_STATE_NONE = 0x00,
    _TYPE_C_LENOVO_SYS_S0 = 0x01,
    _TYPE_C_LENOVO_SYS_S0I3 = 0x02,
    _TYPE_C_LENOVO_SYS_S3 = 0x03,
    _TYPE_C_LENOVO_SYS_S4 = 0x04,
    _TYPE_C_LENOVO_SYS_S5 = 0x05,
}EnumTypeCLenovoSysState;

//--------------------------------------------------
// Struct for Type-C Lenovo Alt Mode Docking Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCLenovoDockPowerSwitch enumDockingPowerSwitch;
    BYTE b1DockingWolRequest : 1;
    BYTE b1DockingEvent : 1;
    BYTE b4DockingReserved : 4;
}StructTypeCLenovoDockEvent;

//--------------------------------------------------
// Struct for Type-C Lenovo Alt Mode System Event (Including System Acknowledge)
//--------------------------------------------------
typedef struct
{
    EnumTypeCLenovoSysPowerMode enumSystemPowerMode;
    EnumTypeCLenovoSysState enumSystemState;
    BYTE b1SystemEvent : 1;
    BYTE b3SystemReserved : 3;
    BYTE ucSystemAcknowlegde;       // [7:4] Reserved, [3] Power Button Break, [2] Power Button Make, [1] WoL, [0] Event Acknowledge
}StructTypeCLenovoSysEvent;


///////////////////
// ACER ALT MODE //
///////////////////

//--------------------------------------------------
// Enumeration of Type-C Acer Alt Mode Ready
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ACER_ALT_MODE_NOT_READY = 0,
    _TYPE_C_ACER_ALT_MODE_READY = 1,
}EnumTypeCAcerAltModeStatus;

//--------------------------------------------------
// Enumerations of Type-C Acer Alt Mode User Event Busy Result
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ACER_USER_EVENT_NOT_BUSY = 0,
    _TYPE_C_ACER_USER_EVENT_BUSY = 1,
}EnumTypeCAcerBusyStatus;

//--------------------------------------------------
// Enumeration of Type-C Acer User Event
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ACER_USER_EVENT_NONE = 0x00,
    _TYPE_C_ACER_USER_EVENT_ATTENTION = _BIT0,
    _TYPE_C_ACER_USER_EVENT_ALL = 0xFF,
}EnumTypeCAcerUserEvent;

//--------------------------------------------------
// Enumeration of Type-C Acer System Event
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ACER_SYS_EVENT_NONE = 0x00,
    _TYPE_C_ACER_SYS_EVENT_STATUS_REQ = _BIT0,
    _TYPE_C_ACER_SYS_EVENT_ALL = 0xFF,
}EnumTypeCAcerSysEvent;

//--------------------------------------------------
// Struct for Type-C Acer Alt Mode User Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCAcerUserEvent enumEvent;
    BYTE pucVdmData[24];
    BYTE b3VdmCnt : 3;
}StructTypeCAcerUserEvent;

//--------------------------------------------------
// Struct for Type-C Acer Alt Mode System Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCAcerSysEvent enumEvent;
    BYTE pucVdmData[24];
    BYTE b3VdmCnt : 3;
}StructTypeCAcerSysEvent;


///////////////////
/// HP ALT MODE ///
///////////////////

//--------------------------------------------------
// Enumeration of Type-C Hp Alt Mode Ready
//--------------------------------------------------
typedef enum
{
    _TYPE_C_HP_ALT_MODE_NOT_READY = 0,
    _TYPE_C_HP_ALT_MODE_READY = 1,
}EnumTypeCHpAltModeStatus;

//--------------------------------------------------
// Enumerations of Type-C Hp Alt Mode User Event Busy Result
//--------------------------------------------------
typedef enum
{
    _TYPE_C_HP_USER_EVENT_NOT_BUSY = 0,
    _TYPE_C_HP_USER_EVENT_BUSY = 1,
}EnumTypeCHpBusyStatus;

//--------------------------------------------------
// Enumeration of Type-C Hp User Event
//--------------------------------------------------
typedef enum
{
    _TYPE_C_HP_USER_EVENT_NONE = 0x00,
    _TYPE_C_HP_USER_EVENT_ATTEN_VWIRE = _BIT0,
    _TYPE_C_HP_USER_EVENT_ATTEN_CONFIG = _BIT1,
    _TYPE_C_HP_USER_EVENT_ATTEN_DATA = _BIT2,
    _TYPE_C_HP_USER_EVENT_ATTEN_DISCONNECT = _BIT3,
    _TYPE_C_HP_USER_EVENT_SET_VWIRE_SAMPLE_ACK = _BIT4,
    _TYPE_C_HP_USER_EVENT_ALL = 0xFF,
}EnumTypeCHpUserEvent;

//--------------------------------------------------
// Enumeration of Type-C Hp System Event
//--------------------------------------------------
typedef enum
{
    _TYPE_C_HP_SYS_EVENT_NONE = 0x00,
    _TYPE_C_HP_SYS_EVENT_SET_CONFIG_REQ = _BIT0,
    _TYPE_C_HP_SYS_EVENT_GET_CONFIG_REQ = _BIT1,
    _TYPE_C_HP_SYS_EVENT_SET_VWIRE_REQ = _BIT2,
    _TYPE_C_HP_SYS_EVENT_GET_VWIRE_REQ = _BIT3,
    _TYPE_C_HP_SYS_EVENT_SET_DATA_REQ = _BIT4,
    _TYPE_C_HP_SYS_EVENT_GET_DATA_REQ = _BIT5,
    _TYPE_C_HP_SYS_EVENT_CMD_REQ = _BIT6,
    _TYPE_C_HP_SYS_EVENT_ALL = 0xFF,
}EnumTypeCHpSysEvent;

//--------------------------------------------------
// Struct for Type-C Hp Alt Mode User Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCHpUserEvent enumEvent;
    BYTE pucVdmData[20];
    BYTE b3VdmCnt : 3;
}StructTypeCHpUserEvent;

//--------------------------------------------------
// Struct for Type-C Hp Alt Mode System Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCHpSysEvent enumEvent;
    BYTE pucVdmData[20];
    BYTE b3VdmCnt : 3;
}StructTypeCHpSysEvent;


///////////////////
// DELL ALT MODE //
///////////////////

//--------------------------------------------------
// Enumeration of Type-C Dell Alt Mode Ready
//--------------------------------------------------
typedef enum
{
    _TYPE_C_DELL_ALT_MODE_NOT_READY = 0,
    _TYPE_C_DELL_ALT_MODE_READY = 1,
}EnumTypeCDellAltModeStatus;

//--------------------------------------------------
// Enumerations of Type-C Dell Alt Mode User Event Busy Result
//--------------------------------------------------
typedef enum
{
    _TYPE_C_DELL_USER_EVENT_NOT_BUSY = 0,
    _TYPE_C_DELL_USER_EVENT_BUSY = 1,
}EnumTypeCDellBusyStatus;

//--------------------------------------------------
// Enumerations of Type-C Dell Alt Mode Initial Complete Result
//--------------------------------------------------
typedef enum
{
    _TYPE_C_DELL_INIT_NOT_COMPLETE = 0,
    _TYPE_C_DELL_INIT_COMPLETE = 1,
}EnumTypeCDellInitCompleteStatus;

//--------------------------------------------------
// Enumeration of Enter Dell Alt Mode Time Out Result
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ENTER_DELL_ALT_MODE_WITHOUT_TIMEOUT = 0,
    _TYPE_C_ENTER_DELL_ALT_MODE_TIMEOUT = 1,
}EnumTypeCEnterDellAltModeTimeOut;

//--------------------------------------------------
// Enumeration of Type-C Dell User Event
//--------------------------------------------------
typedef enum
{
    _TYPE_C_DELL_USER_EVENT_NONE = 0x00,
    _TYPE_C_DELL_USER_EVENT_ATTEN = _BIT0,
    _TYPE_C_DELL_USER_EVENT_ALL = 0xFF,
}EnumTypeCDellUserEvent;

//--------------------------------------------------
// Enumeration of Type-C Dell System Event
//--------------------------------------------------
typedef enum
{
    _TYPE_C_DELL_SYS_EVENT_NONE = 0x00,
    _TYPE_C_DELL_SYS_EVENT_0X12 = _BIT0,
    _TYPE_C_DELL_SYS_EVENT_ATTEN_SUCCESS = _BIT1,
    _TYPE_C_DELL_SYS_EVENT_ATTEN_DISCARD = _BIT2,
    _TYPE_C_DELL_SYS_EVENT_ATTEN_NORESPONSE = _BIT3,
    _TYPE_C_DELL_SYS_EVENT_ALL = 0xFF,
}EnumTypeCDellSysEvent;

//--------------------------------------------------
// Struct for Type-C Dell Alt Mode User Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCDellUserEvent enumEvent;
    BYTE pucVdmData[24];
    BYTE b3VdmCnt : 3;
}StructTypeCDellUserEvent;

//--------------------------------------------------
// Struct for Type-C Dell Alt Mode System Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCDellSysEvent enumEvent;
    BYTE pucVdmData[24];
    BYTE b3VdmCnt : 3;
}StructTypeCDellSysEvent;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
