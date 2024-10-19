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
// ID Code      : TypeC_Pmic_INTERSIL_RAA489800.h
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC RAA489800
//--------------------------------------------------
#define _TYPE_C_PMIC_RAA489800_SUPPORT              ((_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800) ||\
                                                     (_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800) ||\
                                                     (_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800) ||\
                                                     (_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800) ||\
                                                     (_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800) ||\
                                                     (_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800) ||\
                                                     (_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800) ||\
                                                     (_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800))

//--------------------------------------------------
// Register Addresss
//--------------------------------------------------
#define _RAA489800_SUBADDR_LENGTH                   0x01
#define _RAA489800_SYS_CURRENT_LIMIT                0x14
#define _RAA489800_FRW_REGULATING_VOLTAGE           0x15
#define _RAA489800_CONTROL0                         0x39
#define _RAA489800_INFORMATION1                     0x3A
#define _RAA489800_CONTROL1                         0x3C
#define _RAA489800_CONTROL2                         0x3D
#define _RAA489800_FRW_INPUT_CURRENT                0x3F
#define _RAA489800_RVS_REGULATING_VOLTAGE           0x49
#define _RAA489800_RVS_OUTPUT_CURRENT               0x4A
#define _RAA489800_INPUT_VOLTAGE_LIMIT              0x4B
#define _RAA489800_CONTROL3                         0x4C
#define _RAA489800_INFORMATION2                     0x4D
#define _RAA489800_CONTROL4                         0x4E
#define _RAA489800_MANUFACTURER_ID                  0xFE
#define _RAA489800_DEVICE_ID                        0xFF

//--------------------------------------------------
// Initial Setting
//--------------------------------------------------
#define _RAA489800_ADDR_14_SYS_CURRENT_LIMIT_LB     0xDC // 1.5A
#define _RAA489800_ADDR_14_SYS_CURRENT_LIMIT_HB     0x05

#define _RAA489800_ADDR_15_FRW_REGULATING_VOLT_LB   0x08 // 5.004V
#define _RAA489800_ADDR_15_FRW_REGULATING_VOLT_HB   0x0D

#define _RAA489800_ADDR_3F_FRW_INPUT_CURRENT_LB     0x80 // 4.992A
#define _RAA489800_ADDR_3F_FRW_INPUT_CURRENT_HB     0x13

#define _RAA489800_ADDR_49_RVS_REGULATING_VOLT_LB   0x08 // 5.004V
#define _RAA489800_ADDR_49_RVS_REGULATING_VOLT_HB   0x0D

#define _RAA489800_ADDR_4A_RVS_OUTPUT_CURRENT_LB    0x00 // 0.512A
#define _RAA489800_ADDR_4A_RVS_OUTPUT_CURRENT_HB    0x02

#define _RAA489800_ADDR_4B_INPUT_VOLTAGE_LIMIT_LB   0x00 // 4.096A
#define _RAA489800_ADDR_4B_INPUT_VOLTAGE_LIMIT_HB   0x08

//Control0 Register 0x39
#define _RAA489800_ADDR_39_SysSideDischarge         0x01 // Enable
#define _RAA489800_ADDR_39_ADPSideDischarge         0x00 // Disable
#define _RAA489800_ADDR_39_VINRegulationLoop        0x00 // Enable input voltage regulation loop
#define _RAA489800_ADDR_39_FETShortTH               0x00 // 400mV
#define _RAA489800_ADDR_39_RVSPhaseComparatorTH_1   0x00 // 0mV, BIT[7]
#define _RAA489800_ADDR_39_RVSPhaseComparatorTH_2   0x00 // 0mV, BIT[9:8]
#define _RAA489800_ADDR_39_FRWnRVSPhaseComparatorTH 0x00 // 0mV
#define _RAA489800_ADDR_39_FRWPhaseComparatorTH     0x00 // 0mV

//Control1 Register 0x3C
#define _RAA489800_ADDR_3C_ForceVDAV                0x00 // Disable force 5.04V VDAC
#define _RAA489800_ADDR_3C_FRWnRVSOVEn              0x00 // Enable OV
#define _RAA489800_ADDR_3C_SwitchingInFWDMode       0x00 // Enable switching
#define _RAA489800_ADDR_3C_FastREFMode              0x00 // Disable
#define _RAA489800_ADDR_3C_BypassMode               0x00 // Disable
#define _RAA489800_ADDR_3C_SysSideCurrentAmp        0x00 // Enable system side current amplifier
#define _RAA489800_ADDR_3C_OutputCurrentLimitAlert  0x00 // Alert# will be asserted if the contoller enter or exit output current limit mode.
#define _RAA489800_ADDR_3C_SwitchingFreq_1          0x00 // 1000khz, BIT[7]
#define _RAA489800_ADDR_3C_SwitchingFreq_2          0x00 // 1000khz, BIT[9:8]
#define _RAA489800_ADDR_3C_AudioFilter              0x00 // Disable
#define _RAA489800_ADDR_3C_RVSModeFunction          0x00 // Disable Force Reverse mode function
#define _RAA489800_ADDR_3C_SkipAutozero             0x00 // Autozero during restart
#define _RAA489800_ADDR_3C_SkipTrim                 0x00 // Read trim during restart
#define _RAA489800_ADDR_3C_SinkingCurrent           0x00 // Sinking current during negative DAC transition enabled
#define _RAA489800_ADDR_3C_DiodeEmulationComparator 0x00 // Diode-emulation comparator enabled

//Control2 Register 0x3D
#define _RAA489800_ADDR_3D_FaultLatchOff            0x00 // Controller latches off after WOC, UV, ADPOV or OTP fault
#define _RAA489800_ADDR_3D_WOCFault                 0x00 // Enable WOC
#define _RAA489800_ADDR_3D_FRWFastSwap              0x00 // Disable forward fast swap
#define _RAA489800_ADDR_3D_RVSFastSwap              0x00 // Disable reverse fast swap
#define _RAA489800_ADDR_3D_ALERTDuration_1          0x00 // 10ms, BIT[7:6]
#define _RAA489800_ADDR_3D_ALERTDuration_2          0x00 // 10ms, BIT[8]
#define _RAA489800_ADDR_3D_ALERTDebounce            0x00 // 7us
#define _RAA489800_ADDR_3D_FRWRestartDebounce       0x00 // Debounce time is 1.3s
#define _RAA489800_ADDR_3D_FaultRestartDebounce     0x00 // Debounce time is 1.3s or 150ms, depends on bit<13> setting
#define _RAA489800_ADDR_3D_FaultRestartRVSEn        0x00 // Debounce time is 1.3s
#define _RAA489800_ADDR_3D_UVControl                0x01 // Disable UV
#define _RAA489800_ADDR_3D_OVControl                0x01 // Disable OV

//Control3 Register 0x4C
#define _RAA489800_ADDR_4C_PGOODSetting             0x01 // PGOOD suppressed until VREF equals to VDAC
#define _RAA489800_ADDR_4C_BBDCMConductionTime      0x00 // Shorter conduction time to reduce ripple
#define _RAA489800_ADDR_4C_DigitalReset             0x00 // Idle
#define _RAA489800_ADDR_4C_REFAmplifier             0x00 // Enable REF amplifier
#define _RAA489800_ADDR_4C_INCurrentLimitLoop       0x00 // Enable input current limit loop
#define _RAA489800_ADDR_4C_CurrentLoopFBGain        0x00 // Gain x 1
#define _RAA489800_ADDR_4C_ForceOpMode              0x00 // No effect
#define _RAA489800_ADDR_4C_FRWStartupDebounceTime   0x00 // Debounce time is 200us
#define _RAA489800_ADDR_4C_RVSStartupDebounceTime   0x00 // Debounce time is 200us
#define _RAA489800_ADDR_4C_ReReadPROGPinResistor    0x01 // Do not re-read PROG pin resistor

//Control4 Register 0x4E
#define _RAA489800_ADDR_4E_ALERTLatch               0x01 // ALERT# signal auto-clear
#define _RAA489800_ADDR_4E_ALERTClear               0x01 // Idle
#define _RAA489800_ADDR_4E_FRWSleepMode             0x00 // if FWREN=1 then controller is enabled, if FWREN=0 controller is disabled
#define _RAA489800_ADDR_4E_RVSModeCurrentALERT      0x00 // Enable


//--------------------------------------------------
// Definitions of Pmic RAA489800 Control
//--------------------------------------------------
#define _RAA489800_PMIC_SOURCE                      1 // Forward mode
#define _RAA489800_PMIC_SINK                        0 // Reverse mode

//--------------------------------------------------
// Definitions of Pmic Voltage & Current Offsets
//--------------------------------------------------
#define _RAA489800_PMIC_OFFSET_PLUS                 0 // Add offset
#define _RAA489800_PMIC_OFFSET_MINUS                1 // Subtract offset

// Port 0
#define _RAA489800_PMIC_0_OFFSET_VOLTAGE            8 // Unit: 10mV
#define _RAA489800_PMIC_0_OFFSET_VOLTAGE_SIGN       _RAA489800_PMIC_OFFSET_PLUS

#define _RAA489800_PMIC_0_OFFSET_CURRENT            20 // Unit: 10mA
#define _RAA489800_PMIC_0_OFFSET_CURRENT_SIGN       _RAA489800_PMIC_OFFSET_PLUS

// Port 1
#define _RAA489800_PMIC_1_OFFSET_VOLTAGE            8 // Unit: 10mV
#define _RAA489800_PMIC_1_OFFSET_VOLTAGE_SIGN       _RAA489800_PMIC_OFFSET_PLUS

#define _RAA489800_PMIC_1_OFFSET_CURRENT            20 // Unit: 10mA
#define _RAA489800_PMIC_1_OFFSET_CURRENT_SIGN       _RAA489800_PMIC_OFFSET_PLUS

// Port 2
#define _RAA489800_PMIC_2_OFFSET_VOLTAGE            8 // Unit: 10mV
#define _RAA489800_PMIC_2_OFFSET_VOLTAGE_SIGN       _RAA489800_PMIC_OFFSET_PLUS

#define _RAA489800_PMIC_2_OFFSET_CURRENT            20 // Unit: 10mA
#define _RAA489800_PMIC_2_OFFSET_CURRENT_SIGN       _RAA489800_PMIC_OFFSET_PLUS

// Port 3
#define _RAA489800_PMIC_3_OFFSET_VOLTAGE            8 // Unit: 10mV
#define _RAA489800_PMIC_3_OFFSET_VOLTAGE_SIGN       _RAA489800_PMIC_OFFSET_PLUS

#define _RAA489800_PMIC_3_OFFSET_CURRENT            20 // Unit: 10mA
#define _RAA489800_PMIC_3_OFFSET_CURRENT_SIGN       _RAA489800_PMIC_OFFSET_PLUS


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct // Sys Current Limit Register 0x14
{
    BYTE ucSysCurrentLimit_LB;
    BYTE ucSysCurrentLimit_HB;
}StructRAA489800SysCurrentLimitMap;

typedef struct // FRW Regulating Voltage Register 0x15
{
    BYTE ucFRWRegulatingVolt_LB;
    BYTE ucFRWRegulatingVolt_HB;
}StructRAA489800FRWRegulatingVoltMap;

typedef struct // FRW Input Current Register 0x3F
{
    BYTE ucFRWInputCurrent_LB;
    BYTE ucFRWInputCurrent_HB;
}StructRAA489800FRWInputCurrentMap;


typedef struct // RVS Regulating Voltage Register 0x49
{
    BYTE ucRVSRegulatingVolt_LB;
    BYTE ucRVSRegulatingVolt_HB;
}StructRAA489800RVSRegulatingVoltMap;

typedef struct // RVS Onput Current Register 0x4A
{
    BYTE ucRVSOutputCurrent_LB;
    BYTE ucRVSOutputCurrent_HB;
}StructRAA489800RVSOutputCurrentMap;

typedef struct // Input Voltage Limit Register 0x4B
{
    BYTE ucInputVoltLimit_LB;
    BYTE ucInputVoltLimit_HB;
}StructRAA489800InputVoltLimitMap;

typedef struct // Control0 Register 0x39
{
    BYTE b1CR0SysSideDischarge : 1;         // BIT[0]:Enable or disable system side charger function
    BYTE b1CR0ADPSideDischarge : 1;         // BIT[1]:Enable or disable ADP side charger function
    BYTE b1CR0VINRegulationLoop : 1;        // BIT[2]:Disable or enable the input voltage regulation loop.
    BYTE b2CR0Reserved : 2;                 // BIT[4:3]:Not used
    BYTE b2CR0FETShortTH : 2;               // BIT[6:5]:Configure the high-side FET short detection PHASE node voltage threshold
    BYTE b1CR0RVSPhaseComparatorTH_1 : 1;   // BIT[7] of BIT[9:7]:Adjust phase comparator threshold offset for reverse buck and buck-boost

    BYTE b2CR0RVSPhaseComparatorTH_2 : 2;   // BIT[9:8] of BIT[9:7]:Adjust phase comparator threshold offset for reverse buck and buck-boost
    BYTE b3CR0FRWnRVSPhaseComparatorTH : 3; // BIT[12:10]:Adjust phase comparator threshold offset for forward and reverse bo
    BYTE b3CR0FRWPhaseComparatorTH : 3;     // BIT[15:13]:Adjust phase comparator threshold offset for forward buck and buck-boost
} StructRAA489800CR0RegisterMap;

typedef struct // Control1 Register 0x3C
{
    BYTE b1CR1ForceVDAV : 1;                // BIT[0]:Enable or disable force 5.04VDAC in Forward and Reverse mode.
    BYTE b1CR1FRWnRVSOVEn : 1;              // BIT[1]:Enable or disable OV fault when VDAC slew rate down in Forward and Reverse mode
    BYTE b1CR1SwitchingInFWDMode : 1;       // BIT[2]:Enable or disable the buck-boost switching VOUT output.
    BYTE b1CR1FastREFMode : 1;              // BIT[3]:Enable or disable the fast REF mode
    BYTE b1CR1BypassMode : 1;               // BIT[4]:Enable or disable the Bypass mode.
    BYTE b1CR1SysSideCurrentAmp : 1;        // BIT[5]:Enable or disable the system side current amplifier when in FWD mode without ADP.
    BYTE b1CR1OutputCurrentLimitAlert : 1;  // BIT[6]:Configures enter or exit output Current limit mode, Alert# will be asserted or not.
    BYTE b1CR1SwitchingFreq_1 : 1;          // BIT[7] of BIT[9:7]:Configures the switching frequency.

    BYTE b2CR1SwitchingFreq_2 : 2;          // BIT[9:8] of BIT[9:7]:Configures the switching frequency.
    BYTE b1CR1AudioFilter : 1;              // BIT[10]:Enable or disable the audio filter function. No audio filter function in Buck-Boost mode.
    BYTE b1CR1RVSModeFunction : 1;          // BIT[11]:Enable or disable Force Reverse mode function.
    BYTE b1CR1SkipAutozero : 1;             // BIT[12]:Enable or disable autozero during restart. Make sure to program this bit when PGOOD is high.
    BYTE b1CR1SkipTrim : 1;                 // BIT[13]:Enable or disable trim read during restart. Make sure to program this bit when PGOOD is high.
    BYTE b1CR1SinkingCurrent : 1;           // BIT[14]:Enable or disable sinking current during negative DAC transition.
    BYTE b1CR1DiodeEmulationComparator : 1; // BIT[15]:Enable or disable diode-emulation comparator
}StructRAA489800CR1RegisterMap;

typedef struct // Control2 Register 0x3D
{
    BYTE b1CR2FaultLatchOff : 1;            // BIT[0]:Disable fault latch off fucntion for WOC, UV, ADPOV or OTP fault event
    BYTE b1CR2WOCFault : 1;                 // BIT[1]:Enable and disable WOC fault.
    BYTE b1CR2Reserved1 : 1;                // BIT[2]:Not used
    BYTE b1CR2FRWFastSwap : 1;              // BIT[3]:Configure forward fast swap.
    BYTE b1CR2RVSFastSwap : 1;              // BIT[4]:Configure reverse fast swap.
    BYTE b1CR2Reserved2 : 1;                // BIT[5]:Not used
    BYTE b2CR2ALERTDuration_1 : 2;          // BIT[7:6] of BIT[8:6]:Configure the minimum duration of ALERT# signal when it is asserted

    BYTE b1CR2ALERTDuration_2 : 1;          // BIT[8] of BIT[8:6]:Configure the minimum duration of ALERT# signal when it is asserted
    BYTE b2CR2ALERTDebounce : 2;            // BIT[10:9]:Configure the ALERT# debounce time before its assertion for ADPsideALERT# and SystemsideALERT#
    BYTE b1CR2FRWRestartDebounce : 1;       // BIT[11]:Configure fault restart debounce for forward enable.
    BYTE b1CR2FaultRestartDebounce : 1;     // BIT[12]:Configure fast fault restart debounce.
    BYTE b1CR2FaultRestartDebounceRVSEn : 1;// BIT[13]:Configure fault restart debounce for reverse enable
    BYTE b1CR2UVControl : 1;                // BIT[14]:Enable or disable UV
    BYTE b1CR2OVControl : 1;                // BIT[15]:Enable or disable OV
} StructRAA489800CR2RegisterMap;

typedef struct // Control3 Register 0x4C
{
    BYTE b1CR3PGOODSetting : 1;             // BIT[0]:Configure PGOOD assert condition
    BYTE b1CR3BBDCMConductionTime : 1;      // BIT[1]:Configure the conduction time in Buck-Boost DCM.
    BYTE b1CR3DigitalReset : 1;             // BIT[2]:Reset all SMBus register values to POR default value and restarts switching.
    BYTE b1CR3REFAmplifier : 1;             // BIT[3]:Disable REF amplifier.
    BYTE b1CR3Reserved1 : 1;                // BIT[4]:Not used
    BYTE b1CR3INCurrentLimitLoop : 1;       // BIT[5]:Disable input current limit loop.
    BYTE b1CR3CurrentLoopFBGain : 1;        // BIT[6]:Configure current loop feedback gain for high current.
    BYTE b1CR3Reserved2 : 1;                // BIT[7]:Not used

    BYTE b3CR3ForceOpMode : 3;              // BIT[10:8]:Enable or disable Force Operating mode.
    BYTE b1CR3FRWStartupDebounceTime : 1;   // BIT[11]:Configure startup debounce time for forward mode
    BYTE b1CR3RVSStartupDebounceTime : 1;   // BIT[12]:Configure startup debounce time for reverse mode
    BYTE b1CR3Reserved3 : 1;                // BIT[13]:Not used
    BYTE b1CR3Reserved4 : 1;                // BIT[14]:Not used
    BYTE b1CR3ReReadPROGPinResistor : 1;    // BIT[15]:Re-read PROG pin resistor or not before switching.
} StructRAA489800CR3RegisterMap;

typedef struct // Control4 Register 0x4E
{
    BYTE b1CR4ALERTLatch : 1;               // BIT[0]:Manually resets ALERT#.
    BYTE b1CR4ALERTClear : 1;               // BIT[1]:Clear ALERT#.
    BYTE b4CR4Reserved1 : 4;                // BIT[5:2]:Not used
    BYTE b1CR4FRWSleepMode : 1;             // BIT[6]:Enable or disable Chip Sleep mode in Forward mode regardless of ADP voltage
    BYTE b1CR4RVSModeCurrentALERT : 1;      // BIT[7]:Enable or disable trigger ALERT# with current in Reverse mode

    BYTE b8CR4Reserved2 : 8;                // BIT[15:8]:Not used
} StructRAA489800CR4RegisterMap;

typedef struct
{
    BYTE b7INFO1Reserved : 7;               // BIT[6:0]: Not used

    BYTE b1INFO1CCModeChange : 1;           // BIT[7]: Controller has entered/exited CC mode
    BYTE b1INFO1ADPsideOV : 1;              // BIT[8]: Adapter side OV fault
    BYTE b1INFO1OTP : 1;                    // BIT[9]: OTP fault
    BYTE b1INFO1SYSsideUV : 1;              // BIT[10]: Sys output UV fault
    BYTE b1INFO1SYSsideOV : 1;              // BIT[11]: Sys output OV fault
    BYTE b1INFO1WOCP : 1;                   // BIT[12]: WOC fault
    BYTE b2INFO1ActiveControlLoop : 2;      // BIT[14:13]: indicator for active control loop
    BYTE b1INFO1ActiveReferenceCircuit : 1; // BIT[15]: indicator for int reference circuit
} StructRAA489800Info1RegisterMap;

typedef struct
{
    BYTE b5INFO2PROGResistor : 5;           // BIT[4:0]:Program Resister read out
    BYTE b3INFO2OperationMode : 3;          // BIT[7:5]:Indicates the RAA489800 operation mode

    BYTE b4INFO2StateMachineStatus : 4;     // BIT[11:8]:Indicates the RAA489800 state machine status.
    BYTE b2INFO2Reserved : 2;               // BIT[13:12]:Not used
    BYTE b1INFO2FWRSwitchEn : 1;            // BIT[14]:Indicates forward switching enable
    BYTE b1INFO2Reserved : 1;               // BIT[15]:Not used
} StructRAA489800Info2RegisterMap;

typedef struct
{
    BYTE ucVoltageOffset;
    BYTE ucVoltageOffsetSign;
    BYTE ucCurrentOffset;
    BYTE ucCurrentOffsetSign;
}StructRAA489800CompensationOffset;

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_RAA489800_SUPPORT == _ON))
extern void ExternalDeviceInterfaceTypeCPmicRaa489800ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicRaa489800ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
extern WORD ExternalDeviceInterfaceTypeCPmicRaa489800ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicRaa489800ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_RAA489800_SUPPORT == _ON))

