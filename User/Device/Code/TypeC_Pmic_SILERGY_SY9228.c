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
// ID Code      : TypeC_Pmic_SILERGY_SY9228.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "../Header/TypeC_Pmic_SILERGY_SY9228.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))) || ((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))) && (_TYPE_C_PMIC_SY9228_SUPPORT == _ON))

#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
#if(_D0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY9228 can't support PPS!!!"
#endif
#endif // End of #if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)

#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
#if(_D1_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D1_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D1_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D1_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY9228 can't support PPS!!!"
#endif
#endif // End of #if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)

#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
#if(_P0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _P0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_P0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _P0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_P0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY9228 can't support PPS!!!"
#endif
#endif // End of #if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)

#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
#if(_ADAPTOR_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_ADAPTOR_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY9228 can't support PPS!!!"
#endif
#endif // End of #if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)


//****************************************************************************
// CODE TABLES
//****************************************************************************
StructSY9228RegisterMap code tPmicSy9228InitialData[] =
{
    // D0 Port Setting
    {
        0x00,                               // Reserved
        _SY9228_ADDR_00_GATE_ENABLE,        // Gate Enable by define
        _SY9228_ADDR_00_VBUS_DISCHARGE,     // Discharge Enable by define
        _SY9228_ADDR_00_ADC_MODE,           // ADC Mode select by define
        _SY9228_ADDR_00_ADC_ACTIVE,         // ADC Active select by define
        _SY9228_ADDR_00_SWITCH_FREQ,        // Switching Freq by define
        _SY9228_ADDR_00_REGULATOR_ENABLE,   // Regulator Enable by define

        0x00,                               // Reserved
        _SY9228_ADDR_01_CABLE_COMPENSATION, // Cable Impedance Compensation by define

        _SY9228_ADDR_02_VOUT_SETTING,       // Output Voltage by define

        0x00,                               // Reserved
        _SY9228_ADDR_03_SLEW_RATE,          // OVP Threshold by define
        _SY9228_ADDR_03_VOUT_OVP_SETTING,   // OVP Threshold by define
        _SY9228_ADDR_03_VOUT_OCP_SETTING,   // OCP Threshold by define

        _SY9228_ADDR_04_VOUT_OVP_MODE,      // OVP mode by define
        _SY9228_ADDR_04_OTP_MODE,           // OTP mode by define
        _SY9228_ADDR_04_VOUT_UVP_MODE,      // UVP mode by define
        _SY9228_ADDR_04_LOCP_MODE,          // LOCP mode by define
        _SY9228_ADDR_04_VOUT_UVP_SETTING,   // UVP Threshold by define
        _SY9228_ADDR_04_LOCP_SETTING,       // LOCP by define

        0x00,                               // Reserved
        0x00,                               // Input/Output Voltage relation (Read Only)
        0x00,                               // Power Good Status (Read Only)

        0x00,                               // Reserved
        0x00,                               // OVP Flag (Read Only)
        0x00,                               // OTP Flag (Read Only)
        0x00,                               // UVP Flag (Read Only)
        0x00,                               // LOCP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // ADC Data Ready (Read Only)

        0x00,                               // Input Voltage Value (Read Only)
        0x00,                               // Output Voltage Value (Read Only)
        0x00,                               // Output Current Value (Read Only)

        0x00,                               // Product (Read Only)
        0x00,                               // Vender ID (Read Only)
    },
    // D1 Port Setting
    {
        0x00,                               // Reserved
        _SY9228_ADDR_00_GATE_ENABLE,        // Gate Enable by define
        _SY9228_ADDR_00_VBUS_DISCHARGE,     // Discharge Enable by define
        _SY9228_ADDR_00_ADC_MODE,           // ADC Mode select by define
        _SY9228_ADDR_00_ADC_ACTIVE,         // ADC Active select by define
        _SY9228_ADDR_00_SWITCH_FREQ,        // Switching Freq by define
        _SY9228_ADDR_00_REGULATOR_ENABLE,   // Regulator Enable by define

        0x00,                               // Reserved
        _SY9228_ADDR_01_CABLE_COMPENSATION, // Cable Impedance Compensation by define

        _SY9228_ADDR_02_VOUT_SETTING,       // Output Voltage by define

        0x00,                               // Reserved
        _SY9228_ADDR_03_SLEW_RATE,          // OVP Threshold by define
        _SY9228_ADDR_03_VOUT_OVP_SETTING,   // OVP Threshold by define
        _SY9228_ADDR_03_VOUT_OCP_SETTING,   // OCP Threshold by define

        _SY9228_ADDR_04_VOUT_OVP_MODE,      // OVP mode by define
        _SY9228_ADDR_04_OTP_MODE,           // OTP mode by define
        _SY9228_ADDR_04_VOUT_UVP_MODE,      // UVP mode by define
        _SY9228_ADDR_04_LOCP_MODE,          // LOCP mode by define
        _SY9228_ADDR_04_VOUT_UVP_SETTING,   // UVP Threshold by define
        _SY9228_ADDR_04_LOCP_SETTING,       // LOCP by define

        0x00,                               // Reserved
        0x00,                               // Input/Output Voltage relation (Read Only)
        0x00,                               // Power Good Status (Read Only)

        0x00,                               // Reserved
        0x00,                               // OVP Flag (Read Only)
        0x00,                               // OTP Flag (Read Only)
        0x00,                               // UVP Flag (Read Only)
        0x00,                               // LOCP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // ADC Data Ready (Read Only)

        0x00,                               // Input Voltage Value (Read Only)
        0x00,                               // Output Voltage Value (Read Only)
        0x00,                               // Output Current Value (Read Only)

        0x00,                               // Product (Read Only)
        0x00,                               // Vender ID (Read Only)
    },
    // P0 Port Setting
    {
        0x00,                               // Reserved
        _SY9228_ADDR_00_GATE_ENABLE,        // Gate Enable by define
        _SY9228_ADDR_00_VBUS_DISCHARGE,     // Discharge Enable by define
        _SY9228_ADDR_00_ADC_MODE,           // ADC Mode select by define
        _SY9228_ADDR_00_ADC_ACTIVE,         // ADC Active select by define
        _SY9228_ADDR_00_SWITCH_FREQ,        // Switching Freq by define
        _SY9228_ADDR_00_REGULATOR_ENABLE,   // Regulator Enable by define

        0x00,                               // Reserved
        _SY9228_ADDR_01_CABLE_COMPENSATION, // Cable Impedance Compensation by define

        _SY9228_ADDR_02_VOUT_SETTING,       // Output Voltage by define

        0x00,                               // Reserved
        _SY9228_ADDR_03_SLEW_RATE,          // OVP Threshold by define
        _SY9228_ADDR_03_VOUT_OVP_SETTING,   // OVP Threshold by define
        _SY9228_ADDR_03_VOUT_OCP_SETTING,   // OCP Threshold by define

        _SY9228_ADDR_04_VOUT_OVP_MODE,      // OVP mode by define
        _SY9228_ADDR_04_OTP_MODE,           // OTP mode by define
        _SY9228_ADDR_04_VOUT_UVP_MODE,      // UVP mode by define
        _SY9228_ADDR_04_LOCP_MODE,          // LOCP mode by define
        _SY9228_ADDR_04_VOUT_UVP_SETTING,   // UVP Threshold by define
        _SY9228_ADDR_04_LOCP_SETTING,       // LOCP by define

        0x00,                               // Reserved
        0x00,                               // Input/Output Voltage relation (Read Only)
        0x00,                               // Power Good Status (Read Only)

        0x00,                               // Reserved
        0x00,                               // OVP Flag (Read Only)
        0x00,                               // OTP Flag (Read Only)
        0x00,                               // UVP Flag (Read Only)
        0x00,                               // LOCP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // ADC Data Ready (Read Only)

        0x00,                               // Input Voltage Value (Read Only)
        0x00,                               // Output Voltage Value (Read Only)
        0x00,                               // Output Current Value (Read Only)

        0x00,                               // Product (Read Only)
        0x00,                               // Vender ID (Read Only)
    },
    // Adaptor Setting
    {
        0x00,                               // Reserved
        _SY9228_ADDR_00_GATE_ENABLE,        // Gate Enable by define
        _SY9228_ADDR_00_VBUS_DISCHARGE,     // Discharge Enable by define
        _SY9228_ADDR_00_ADC_MODE,           // ADC Mode select by define
        _SY9228_ADDR_00_ADC_ACTIVE,         // ADC Active select by define
        _SY9228_ADDR_00_SWITCH_FREQ,        // Switching Freq by define
        _SY9228_ADDR_00_REGULATOR_ENABLE,   // Regulator Enable by define

        0x00,                               // Reserved
        _SY9228_ADDR_01_CABLE_COMPENSATION, // Cable Impedance Compensation by define

        _SY9228_ADDR_02_VOUT_SETTING,       // Output Voltage by define

        0x00,                               // Reserved
        _SY9228_ADDR_03_SLEW_RATE,          // OVP Threshold by define
        _SY9228_ADDR_03_VOUT_OVP_SETTING,   // OVP Threshold by define
        _SY9228_ADDR_03_VOUT_OCP_SETTING,   // OCP Threshold by define

        _SY9228_ADDR_04_VOUT_OVP_MODE,      // OVP mode by define
        _SY9228_ADDR_04_OTP_MODE,           // OTP mode by define
        _SY9228_ADDR_04_VOUT_UVP_MODE,      // UVP mode by define
        _SY9228_ADDR_04_LOCP_MODE,          // LOCP mode by define
        _SY9228_ADDR_04_VOUT_UVP_SETTING,   // UVP Threshold by define
        _SY9228_ADDR_04_LOCP_SETTING,       // LOCP by define

        0x00,                               // Reserved
        0x00,                               // Input/Output Voltage relation (Read Only)
        0x00,                               // Power Good Status (Read Only)

        0x00,                               // Reserved
        0x00,                               // OVP Flag (Read Only)
        0x00,                               // OTP Flag (Read Only)
        0x00,                               // UVP Flag (Read Only)
        0x00,                               // LOCP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // ADC Data Ready (Read Only)

        0x00,                               // Input Voltage Value (Read Only)
        0x00,                               // Output Voltage Value (Read Only)
        0x00,                               // Output Current Value (Read Only)

        0x00,                               // Product (Read Only)
        0x00,                               // Vender ID (Read Only)
    },
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSY9228RegisterMap g_pstPmicSy9228Data[4];


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PMIC Initial Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicSy9228ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC Data initial value
    g_pstPmicSy9228Data[ucDataIndex] = tPmicSy9228InitialData[ucDataIndex];

    // Enable Pin Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_POWER(_D0_PMIC_POWER_ON);

        // Delay 10ms for Silergy PMIC's Special Design
        UserCommonTimerDelayXms(10);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_POWER(_D1_PMIC_POWER_ON);

        // Delay 10ms for Silergy PMIC's Special Design
        UserCommonTimerDelayXms(10);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_POWER(_P0_PMIC_POWER_ON);

        // Delay 10ms for Silergy PMIC's Special Design
        UserCommonTimerDelayXms(10);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_ON);

        // Delay 10ms for Silergy PMIC's Special Design
        UserCommonTimerDelayXms(10);
    }

    // Initial Pmic Value
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 5, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1);

    // Clear INT Flag
    UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _SY9228_STATE_REG, _SY9228_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_STATE_REG);
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC Data initial value
    g_pstPmicSy9228Data[ucDataIndex] = tPmicSy9228InitialData[ucDataIndex];

    // Initial Pmic Value
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 5, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1);

    // Clear INT Flag
    UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _SY9228_STATE_REG, _SY9228_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_STATE_REG);
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC Data initial value
    g_pstPmicSy9228Data[ucDataIndex] = tPmicSy9228InitialData[ucDataIndex];

    // Initial Pmic Value
    UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 5, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1);

    // Clear INT Flag
    UserCommonUsbTypeCPmicIICRead_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9228_STATE_REG, _SY9228_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_STATE_REG);
}

#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_WDINT(EnumTypeCPcbPort enumTypeCPcbPort) USING(3)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_DP_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _P0_DP_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC Data initial value
    g_pstPmicSy9228Data[ucDataIndex] = tPmicSy9228InitialData[ucDataIndex];

    // Initial Pmic Value
    UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 5, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1);

    // Clear INT Flag
    UserCommonUsbTypeCPmicIICRead_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY9228_STATE_REG, _SY9228_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_STATE_REG);
}
#endif // End of #if(_PORT_CTRL_TCPM_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    enumPowerDirection = enumPowerDirection;

    // Set Pmic config
    g_pstPmicSy9228Data[ucDataIndex].b1PMICEnable = _ON;
    g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
    }

    if(enumPowerDirection == _SY9228_PMIC_SOURCE)
    {
        if((usVoltage > 2100) || (usVoltage < 360))
        {
            return _FAIL;
        }

        // Set VOUT Voltage
        g_pstPmicSy9228Data[ucDataIndex].ucOutputVoltageSetting = (BYTE)(usVoltage / 10);

        // Set Switch Frequency
        if(usVoltage >= 1330)
        {
            g_pstPmicSy9228Data[ucDataIndex].b2SwitchFreq = 0x00;
        }
        else if(usVoltage >= 610)
        {
            g_pstPmicSy9228Data[ucDataIndex].b2SwitchFreq = 0x01;
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b2SwitchFreq = 0x02;
        }

        // Set VBUS Current Limit
        if(usCurrent <= 50)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x00;
        }
        else if(usCurrent <= 100)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x01;
        }
        else if(usCurrent <= 150)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x02;
        }
        else if(usCurrent <= 200)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x03;
        }
        else if(usCurrent <= 300)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x04;
        }
        else if(usCurrent <= 400)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x05;
        }
        else if(usCurrent <= 500)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x06;
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x07;
        }

        if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 4, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    enumPowerDirection = enumPowerDirection;

    // Set Pmic config
    g_pstPmicSy9228Data[ucDataIndex].b1PMICEnable = _ON;
    g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
    }

    if(enumPowerDirection == _SY9228_PMIC_SOURCE)
    {
        if((usVoltage > 2100) || (usVoltage < 360))
        {
            return _FAIL;
        }

        // Set VOUT Voltage
        g_pstPmicSy9228Data[ucDataIndex].ucOutputVoltageSetting = (BYTE)(usVoltage / 10);

        // Set Switch Frequency
        if(usVoltage >= 1330)
        {
            g_pstPmicSy9228Data[ucDataIndex].b2SwitchFreq = 0x00;
        }
        else if(usVoltage >= 610)
        {
            g_pstPmicSy9228Data[ucDataIndex].b2SwitchFreq = 0x01;
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b2SwitchFreq = 0x02;
        }

        // Set VBUS Current Limit
        if(usCurrent <= 50)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x00;
        }
        else if(usCurrent <= 100)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x01;
        }
        else if(usCurrent <= 150)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x02;
        }
        else if(usCurrent <= 200)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x03;
        }
        else if(usCurrent <= 300)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x04;
        }
        else if(usCurrent <= 400)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x05;
        }
        else if(usCurrent <= 500)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x06;
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x07;
        }

        if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 4, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    enumPowerDirection = enumPowerDirection;

    // Set Pmic config
    g_pstPmicSy9228Data[ucDataIndex].b1PMICEnable = _ON;
    g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
    }

    if(enumPowerDirection == _SY9228_PMIC_SOURCE)
    {
        if((usVoltage > 2100) || (usVoltage < 360))
        {
            return _FAIL;
        }

        // Set VOUT Voltage
        g_pstPmicSy9228Data[ucDataIndex].ucOutputVoltageSetting = (BYTE)(usVoltage / 10);

        // Set Switch Frequency
        if(usVoltage >= 1330)
        {
            g_pstPmicSy9228Data[ucDataIndex].b2SwitchFreq = 0x00;
        }
        else if(usVoltage >= 610)
        {
            g_pstPmicSy9228Data[ucDataIndex].b2SwitchFreq = 0x01;
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b2SwitchFreq = 0x02;
        }

        // Set VBUS Current Limit
        if(usCurrent <= 50)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x00;
        }
        else if(usCurrent <= 100)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x01;
        }
        else if(usCurrent <= 150)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x02;
        }
        else if(usCurrent <= 200)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x03;
        }
        else if(usCurrent <= 300)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x04;
        }
        else if(usCurrent <= 400)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x05;
        }
        else if(usCurrent <= 500)
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x06;
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b3VOCPSetting = 0x07;
        }

        if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 4, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228TurnOff(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    g_pstPmicSy9228Data[ucDataIndex].b1PMICEnable = _OFF;

    // Disable PMIC
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    g_pstPmicSy9228Data[ucDataIndex].b1PMICEnable = _OFF;

    // Disable PMIC
    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    g_pstPmicSy9228Data[ucDataIndex].b1PMICEnable = _OFF;

    // Disable PMIC
    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC VBUS Discharge status
    g_pstPmicSy9228Data[ucDataIndex].b1VOUTDischarge = !enumEn;

    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_OFF);
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC VBUS Discharge status
    g_pstPmicSy9228Data[ucDataIndex].b1VOUTDischarge = !enumEn;

    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_OFF);
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set PMIC VBUS Discharge status
    g_pstPmicSy9228Data[ucDataIndex].b1VOUTDischarge = !enumEn;

    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D0_VBUS_DISCHARGE_CONTROL(_D0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_D1_VBUS_DISCHARGE_CONTROL(_D1_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_P0_VBUS_DISCHARGE_CONTROL(_P0_PMIC_VBUS_DISCHARGE_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_ON);
        }
        else
        {
            PCB_ADAPTOR_VBUS_DISCHARGE_CONTROL(_ADAPTOR_PMIC_VBUS_DISCHARGE_OFF);
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Switch Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }

    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Switch Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }

    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Switch Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _ON;

            if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
            {
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
                PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_ON);
            }
        }
        else
        {
            g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }

    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerDirection : _SRC / _SNK
//                enumOutputPdoType : PDO Type
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerDirection : _SRC / _SNK
//                enumOutputPdoType : PDO Type
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerDirection : _SRC / _SNK
//                enumOutputPdoType : PDO Type
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Read Output Status
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Output Mode (Fixed Voltage/PPS)
//--------------------------------------------------
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicSy9228ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    return _TYPE_C_PMIC_NONE_MODE_OPERATION;
}
#endif // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)

#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
//--------------------------------------------------
// Description  : PMIC Status
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucResult = 0;
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    ucResult = UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _SY9228_STATE_REG, _SY9228_SUBADDR_LENGTH, 6, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_STATE_REG);

    DebugMessageTypeC("Pmic:Embbeded Type-C Port", ucDataIndex);
    DebugMessageTypeC("5.Pmic:Power Good Status", g_pstPmicSy9228Data[ucDataIndex].b1PowerGoodState);
    DebugMessageTypeC("5.Pmic:Relation Status", g_pstPmicSy9228Data[ucDataIndex].b1VinVoutRelation);
    DebugMessageTypeC("6.Pmic:Output OCP Flag", g_pstPmicSy9228Data[ucDataIndex].b1VOCPFlag);
    DebugMessageTypeC("6.Pmic:Inductor OCP Flag", g_pstPmicSy9228Data[ucDataIndex].b1LOCPFlag);
    DebugMessageTypeC("6.Pmic:Output UVP Flag", g_pstPmicSy9228Data[ucDataIndex].b1UVPFlag);
    DebugMessageTypeC("6.Pmic:OTP Flag", g_pstPmicSy9228Data[ucDataIndex].b1OTPFlag);
    DebugMessageTypeC("6.Pmic:Output UVP Flag", g_pstPmicSy9228Data[ucDataIndex].b1OVPFlag);
    DebugMessageTypeC("7.Pmic:Input Voltage Value", g_pstPmicSy9228Data[ucDataIndex].ucInputVoltageValue);
    DebugMessageTypeC("8.Pmic:Output Voltage Value", g_pstPmicSy9228Data[ucDataIndex].ucOutputVoltageValue);
    DebugMessageTypeC("9.Pmic:Output Current Value", g_pstPmicSy9228Data[ucDataIndex].ucOutputCurrentValue);
    DebugMessageTypeC("A.Pmic:Product ID", g_pstPmicSy9228Data[ucDataIndex].b4Product);
    DebugMessageTypeC("A.Pmic:Vender ID", g_pstPmicSy9228Data[ucDataIndex].b4VenderID);

    if (ucResult == _SUCCESS)
    {
        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }
    else
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }
}
#endif // End of #if(_EMB_TYPE_C_PMIC_DEBUG == _ON)

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC VBUS Current Reading
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : usCurrent : 0 ~ 500 (Unit = 10mA)
//--------------------------------------------------
WORD ExternalDeviceInterfaceTypeCPmicSy9228ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort)
{
    WORD usCurrent = 0;
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;

#if(_D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        return 0;
#endif
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;

#if(_D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        return 0;
#endif
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;

#if(_P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        return 0;
#endif
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;

#if(_ADAPTOR_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        return 0;
#endif
    }

    // Get Current value from PMIC's ADC
    UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _SY9228_CURRENT_VALUE_REG, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_CURRENT_VALUE_REG);

    // Translate PMIC's Current Unit to 10mA/bit
    usCurrent = ((WORD)(((DWORD)g_pstPmicSy9228Data[ucDataIndex].ucOutputCurrentValue * 100 * 6) / 256));

    // Show data
    DebugMessageTypeC("Pmic:Embbeded Type-C Port", ucDataIndex);
    DebugMessageTypeC("Pmic:Current Value(Bit)", g_pstPmicSy9228Data[ucDataIndex].ucOutputCurrentValue);
    DebugMessageTypeC("Pmic:Current Value(10mA)", usCurrent);

    return usCurrent;
}
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON))
//--------------------------------------------------
// Description  : PMIC Vbus Force Off Config
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9228ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
        ucSlaveAddr = _D0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
        ucSlaveAddr = _D1_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
        ucSlaveAddr = _P0_TYPE_C_PMIC_SLAVE_ADDRESS;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
        ucSlaveAddr = _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS;
    }

    // Set Vbus Force Off Type
    UserCommonUsbTypeCPmicSetForceOffControlType(enumTypeCPcbPort, _TYPE_C_PMIC_FORCE_OFF_BY_IIC);

    // Set PMIC IIC Data value
    g_pstPmicSy9228Data[ucDataIndex].b1PMICEnable = _OFF;
    g_pstPmicSy9228Data[ucDataIndex].b1GateEnable = _OFF;

    if(UserCommonUsbTypeCPmicSetForceOffIIC(enumTypeCPcbPort, ucSlaveAddr, _SY9228_FUNCTION_SETTING1, _SY9228_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9228Data[ucDataIndex]) + _SY9228_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON))
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))) || ((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))) && (_TYPE_C_PMIC_SY9228_SUPPORT == _ON))

