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
// ID Code      : TypeC_Pmic_ONSEMI_NCP81239.h
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC NCP81239
//--------------------------------------------------
#define _TYPE_C_PMIC_NCP81239_SUPPORT               ((_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239) ||\
                                                     (_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239) ||\
                                                     (_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239) ||\
                                                     (_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239) ||\
                                                     (_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239) ||\
                                                     (_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239) ||\
                                                     (_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239) ||\
                                                     (_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239) ||\
                                                     (_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239))

//--------------------------------------------------
// Register Addresss
//--------------------------------------------------
#define _NCP81239_SUBADDR_LENGTH                    0x01
#define _NCP81239_CTRL_REG00                        0x00
#define _NCP81239_CTRL_REG01                        0x01
#define _NCP81239_CTRL_REG02                        0x02
#define _NCP81239_CTRL_REG03                        0x03
#define _NCP81239_CTRL_REG04                        0x04
#define _NCP81239_CTRL_REG05                        0x05
#define _NCP81239_CTRL_REG06                        0x06
#define _NCP81239_CTRL_REG07                        0x07
#define _NCP81239_CTRL_REG08                        0x08
#define _NCP81239_CTRL_REG09                        0x09
#define _NCP81239_CTRL_REG0A                        0x0A
#define _NCP81239_CTRL_REG10                        0x10
#define _NCP81239_CTRL_REG11                        0x11
#define _NCP81239_CTRL_REG12                        0x12
#define _NCP81239_CTRL_REG13                        0x13
#define _NCP81239_CTRL_REG14                        0x14
#define _NCP81239_CTRL_REG15                        0x15

//--------------------------------------------------
// Definitions of Pmic NCP81239 Control
//--------------------------------------------------
#define _NCP81239_TUNE_RISE                         0
#define _NCP81239_TUNE_FALL                         1
#define _NCP81239_PMIC_SOURCE                       1
#define _NCP81239_PMIC_SINK                         0

//--------------------------------------------------
// NCP81239 Initial Setting
//--------------------------------------------------
#define _NCP81239_ADDR_01_VBUS                      0x32 // 5V
#define _NCP81239_ADDR_02_SLEW_RATE                 0x00
#define _NCP81239_ADDR_03_PWM_FREQ                  0x00
#define _NCP81239_ADDR_05_OCP_CLIM_POS              0x00
#define _NCP81239_ADDR_05_OCP_CLIM_NEG              0x00
#define _NCP81239_ADDR_06_CS1_CLIND                 0x03 // 5A
#define _NCP81239_ADDR_06_CS2_CLIND                 0x03 // 5A
#define _NCP81239_ADDR_09_INT_MASK_CS_CLIND         0x00
#define _NCP81239_ADDR_09_INT_MASK_OVP              0x00
#define _NCP81239_ADDR_09_INT_MASK_OCP_P            0x00
#define _NCP81239_ADDR_09_INT_MASK_PG_INT           0x00
#define _NCP81239_ADDR_09_INT_MASK_TSD              0x00
#define _NCP81239_ADDR_09_INT_MASK_UVP              0x00
#define _NCP81239_ADDR_09_INT_MASK_VCHN             0x00
#define _NCP81239_ADDR_09_INT_MASK_IIC_ACK          0x00
#define _NCP81239_ADDR_09_INT_MASK_SHUT_DOWN        0x00

//--------------------------------------------------
// Definitions of PMIC FUNCTION
//--------------------------------------------------
#define _NCP81239_PMIC_VOLTAGE_OFFSET               1 // unit: 0.1V

//--------------------------------------------------
// Macros of PMIC STATUS
//--------------------------------------------------


//--------------------------------------------------
// Macros of PMIC CHECK START
//--------------------------------------------------

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b2CR00Reserved : 2;
    BYTE b1CR00EnMask : 1;
    BYTE b1CR00EnInternal : 1;
    BYTE b4CR00Reserved : 4;

    BYTE ucCR01DacTarget;

    BYTE b2CR02SlewRate : 2;
    BYTE b6CR02Reserved : 6;

    BYTE b3CR03PwmFreq : 3;
    BYTE b1CR03Reserved : 1;
    BYTE b1CR03DacLsb : 1;
    BYTE b3CR03Reserved : 3;

    BYTE b1CR04Pfet : 1;
    BYTE b1CR04Cfet : 1;
    BYTE b3CR04Reserved : 3;
    BYTE b1CR04Cs2DisCharge : 1;
    BYTE b2CR04Reserved : 2;

    BYTE b2CR05OcpClimPos : 2;
    BYTE b2CR05Reserved1 : 2;
    BYTE b2CR05OcpClimNeg : 2;
    BYTE b2CR05Reserved2 : 2;

    BYTE b2CR06Cs1Clind : 2;
    BYTE b2CR06Cs2Clind : 2;
    BYTE b4CR06Reserved : 4;

    BYTE b3CR07LoGmAmpSetting : 3;
    BYTE b1CR07GmManual : 1;
    BYTE b3CR07HiGmAmpSetting : 3;
    BYTE b1CR07GmAmpConfig : 1;

    BYTE b2CR08AmuxTrigger : 2;
    BYTE b3CR08AmuxSel : 3;
    BYTE b1CR08DisAdc : 1;
    BYTE b2CR08Reserved : 2;

    BYTE b1CR09IntMaskCsClind : 1;
    BYTE b1CR09IntMaskOvp : 1;
    BYTE b1CR09IntMaskOcpP : 1;
    BYTE b1CR09IntMaskPgInt : 1;
    BYTE b1CR09IntMaskTsd : 1;
    BYTE b1CR09IntMaskUvp : 1;
    BYTE b1CR09IntMaskVchn : 1;
    BYTE b1CR09IntMaskI2cAck : 1;

    BYTE b1CR0AIntMaskShutDown : 1;
    BYTE b7CR0AReserved : 7;

    BYTE b1CR0BPmicDirection : 1;
    BYTE b7CR0BReserved : 7;
    BYTE ucCR0CReserved;
    BYTE ucCR0DReserved;
    BYTE ucCR0EReserved;
    BYTE ucCR0FReserved;

    BYTE ucCR10VfbValue;
    BYTE ucCR11VinValue;
    BYTE ucCR12Cs2Value;
    BYTE ucCR13Cs1Value;

    BYTE b1CR14IntCsClindFlag : 1;
    BYTE b1CR14IntOvpFlag : 1;
    BYTE b1CR14IntOcpPFlag : 1;
    BYTE b1CR14IntPgIntFlag : 1;
    BYTE b1CR14IntTsdFlag : 1;
    BYTE b1CR14IntUvpFlag : 1;
    BYTE b1CR14IntVchnFlag : 1;
    BYTE b1CR14IntI2cAckFlag : 1;

    BYTE b1CR15IntShutDownFlag : 1;
    BYTE b7CR15Reserved : 7;
} StructNCP81239RegisterMap;

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_NCP81239_SUPPORT == _ON))
extern void ExternalDeviceInterfaceTypeCPmicNcp81239ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType);
extern EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicNcp81239ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
extern WORD ExternalDeviceInterfaceTypeCPmicNcp81239ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
extern EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort);
#endif

#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_NCP81239_SUPPORT == _ON))

