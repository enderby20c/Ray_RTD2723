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
// ID Code      : TypeC_Pmic_MPS_MP4247.h
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC MP4247
//--------------------------------------------------
#define _TYPE_C_PMIC_MP4247_SUPPORT                 ((_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247) ||\
                                                     (_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247) ||\
                                                     (_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247) ||\
                                                     (_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247) ||\
                                                     (_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247) ||\
                                                     (_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247) ||\
                                                     (_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247) ||\
                                                     (_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247))


//--------------------------------------------------
// Register Addresss
//--------------------------------------------------
#define _MP4247_OPEARTION                           0x01
#define _MP4247_CLEAR_FAULTS                        0x03
#define _MP4247_VOUT_COMMAND                        0x21
#define _MP4247_STATUS_WORD                         0x79
#define _MP4247_STATUS_TEMPERATURE                  0x7D
#define _MP4247_MFR_CTRL1                           0xD0
#define _MP4247_MFR_CURRENT_LIMIT                   0xD1
#define _MP4247_MFR_CTRL2                           0xD2
#define _MP4247_MFR_CTRL3                           0xD3
#define _MP4247_MFR_CTRL4                           0xD4
#define _MP4247_MFR_STATUS_MASK                     0xD8
#define _MP4247_MFR_OTP_CONFIGURATION_CODE          0xD9
#define _MP4247_MFR_OTP_REVISION_NUMBER             0xDA
#define _MP4247_REGISTER_END                        0xFF

//--------------------------------------------------
// Register Addresss
//--------------------------------------------------
#define _MP4247_SUBADDR_LENGTH                      0x01
#define _MP4247_DATA_LENGTH_1                       0x01
#define _MP4247_DATA_LENGTH_2                       0x02

//--------------------------------------------------
// Definitions of Voltage(250mV)
//--------------------------------------------------
#define _MP4247_OUTPUT_VOL_0V                       0x0000
#define _MP4247_OUTPUT_VOL_3V                       0x000C
#define _MP4247_OUTPUT_VOL_5V                       0x0014
#define _MP4247_OUTPUT_VOL_7V                       0x001C
#define _MP4247_OUTPUT_VOL_9V                       0x0024
#define _MP4247_OUTPUT_VOL_12V                      0x0030
#define _MP4247_OUTPUT_VOL_15V                      0x003C
#define _MP4247_OUTPUT_VOL_20V                      0x0050

//--------------------------------------------------
// Definitions of Current(Rsense 10m ohm)
//--------------------------------------------------
#define _MP4247_OUTPUT_CURRENT_LIMIT_1_0A           0x14
#define _MP4247_OUTPUT_CURRENT_LIMIT_1_5A           0x1E
#define _MP4247_OUTPUT_CURRENT_LIMIT_2_0A           0x28
#define _MP4247_OUTPUT_CURRENT_LIMIT_2_5A           0x32
#define _MP4247_OUTPUT_CURRENT_LIMIT_3_0A           0x3C
#define _MP4247_OUTPUT_CURRENT_LIMIT_3_25A          0x41
#define _MP4247_OUTPUT_CURRENT_LIMIT_3_5A           0x46
#define _MP4247_OUTPUT_CURRENT_LIMIT_4_0A           0x50
#define _MP4247_OUTPUT_CURRENT_LIMIT_4_5A           0x5A
#define _MP4247_OUTPUT_CURRENT_LIMIT_5_0A           0x64

//--------------------------------------------------
// Definitions of Operation Mode
//--------------------------------------------------
#define _MP4247_MODE_OFF                            0x00
#define _MP4247_MODE_ON                             0x80

//--------------------------------------------------
// Definitions of Discharge Control
//--------------------------------------------------
#define _MP4247_DISCHANGE_DISABLE                   0x00
#define _MP4247_DISCHANGE_ENABLE                    0x01

//--------------------------------------------------
// Macros of PMIC Default STATUS
//--------------------------------------------------
#define _MP4247_OPEARTION_DEFAULT                   0x00
#define _MP4247_VOUT_COMMAND_DEFAULT                _MP4247_OUTPUT_VOL_5V
#define _MP4247_MFR_CTRL1_DEFAULT                   0x2F
#define _MP4247_MFR_CURRENT_LIMIT_DEFAULT           0x3C
#define _MP4247_MFR_CTRL2_DEFAULT                   0x00
#define _MP4247_MFR_CTRL3_DEFAULT                   0x84 // Select the Rsens resistor value: 0: 5mo, Default; 1: 10mo
#define _MP4247_MFR_CTRL4_DEFAULT                   0x27
#define _MP4247_MFR_STATUS_MASK_DEFAULT             0xBF


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE ucOperation; // 0x01 OPERATION  0x00 OFF , 0x80 ON
    WORD usVoutCommand; // 0x21 VOUT_COMMAND
    BYTE ucMfrCtrl1; // 0xD0 MFR_CTRL1
    BYTE ucMfrCurrentLimit; // 0xD1 MFR_CURRENT_LIMIT
    BYTE ucMfrCtrl2; // 0xD2 MFR_CTRL2
    BYTE ucMfrCtrl3; // 0xD3 MFR_CTRL3
    BYTE ucMfrCtrl4; // 0xD4 MFR_CTRL4
    BYTE ucMfrStatusMask; // 0xD8 MFR_STATUS_MASK
} StructMP4247RegisterMap;


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_MP4247_SUPPORT == _ON))
extern void ExternalDeviceInterfaceTypeCPmicMp4247ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247TurnOff(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicMp4247ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
extern WORD ExternalDeviceInterfaceTypeCPmicMp4247ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicMp4247ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_Mp4247_SUPPORT == _ON))

