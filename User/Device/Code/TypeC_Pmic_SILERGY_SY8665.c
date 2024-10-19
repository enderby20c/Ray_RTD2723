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
// ID Code      : TypeC_Pmic_SILERGY_SY8665.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "../Header/TypeC_Pmic_SILERGY_SY8665.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_SY8665_SUPPORT == _ON))

#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
#if(_D0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SY8665 can't support voltage compensation!!!"
#endif

#if(_D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#warning "SY8665 can't support OCP by polling PMIC ADC!!!"
#endif

#if(_D0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY8665 can't support PPS!!!"
#endif
#endif // End of #if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)

#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
#if(_D1_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D1_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D1_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D1_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D1_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SY8665 can't support voltage compensation!!!"
#endif

#if(_D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#warning "SY8665 can't support OCP by polling PMIC ADC!!!"
#endif

#if(_D1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY8665 can't support PPS!!!"
#endif
#endif // End of #if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)

#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
#if(_P0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _P0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_P0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _P0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_P0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SY8665 can't support voltage compensation!!!"
#endif

#if(_P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#warning "SY8665 can't support OCP by polling PMIC ADC!!!"
#endif

#if(_P0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY8665 can't support PPS!!!"
#endif
#endif // End of #if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)

#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
#if(_ADAPTOR_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SY8665 can't support voltage compensation!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#warning "SY8665 can't support OCP by polling PMIC ADC!!!"
#endif

#if(_ADAPTOR_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY8665 can't support PPS!!!"
#endif
#endif // End of #if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)


//****************************************************************************
// CODE TABLES
//****************************************************************************
StructSY8665RegisterMap code tPmicSy8665InitialData[] =
{
    // D0 Port Setting
    {
        _MODE_ALL_OFF1,                     // Mode
        _TURN_OFF_DISCHANGE_AT_ALL,         // Discharge Enable at All off
        0x00,                               // Reserved
        _DISCHARGE_REG_1_80_K,              // Discharge Resistor Setting
        _OFF,                               // Reset all registers to default value. Automatically clear to "0" after reset is done.

        _OUTPUT_VOLTAGE_5V,                 // Output Voltage Setting
        0x00,                               // Reserved

        0x00,                               // Reserved
        _SY8665_INT_DISABLE,                // Interrupt Disable
        _GO_BIT_INTERNAL_MODE,              // Go_bit
        _CABLE_IMPEDANCE_RCMP_100,          // Cable Impedance Compensation
        _LIGHT_LOAD_PULSE_SKIP,             // Light Load Operation

        0x00,                               // Reserved
        _BUCK_SWITCHING_250KHZ,             // Buck Switching Frequency Setting
        _AUTO_RECOVER_MODE,                 // UVP((Source Mode 1)
        _AUTO_RECOVER_MODE,                 // OVP((Source Mode 1)
        _AUTO_RECOVER_MODE,                 // OTP
        _AUTO_RECOVER_MODE,                 // Reverse Current Protection mode

        INDUCTOR_PEAK_CURRENT_LIMIT_5A,     // Inductor Peak Current Limit
        _V_SWO_UVP_THRESHOLD_60P,           // VSWO UVP Threshold (Buck mode)
        _V_VBUS_OVP_THRESHOLD_125P,         // VVBUS OVP Threshold (Buck mode)
        _OUTPUT_CURRENT_LIMIT_50MV,         // Output Current Limit

        0x00,                               // UVP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // OVP Flag (Read Only)
        0x00,                               // Over temperature protection Flag (Read Only)
        0x00,                               // Voltage reserved(Read Only)
        0x00,                               // VBUS absolute maximum OVP Flag (Read Only)
        0x00,                               // Reserved
        0x00,                               // Power Good
    },
    // D1 Port Setting
    {
        _MODE_ALL_OFF1,                     // Mode
        _TURN_OFF_DISCHANGE_AT_ALL,         // Discharge Enable at All off
        0x00,                               // Reserved
        _DISCHARGE_REG_1_80_K,              // Discharge Resistor Setting
        _OFF,                               // Reset all registers to default value. Automatically clear to "0" after reset is done.

        _OUTPUT_VOLTAGE_5V,                 // Output Voltage Setting
        0x00,                               // Reserved

        0x00,                               // Reserved
        _SY8665_INT_DISABLE,                // Interrupt Disable
        _GO_BIT_INTERNAL_MODE,              // Go_bit
        _CABLE_IMPEDANCE_RCMP_100,          // Cable Impedance Compensation
        _LIGHT_LOAD_PULSE_SKIP,             // Light Load Operation

        0x00,                               // Reserved
        _BUCK_SWITCHING_250KHZ,             // Buck Switching Frequency Setting
        _AUTO_RECOVER_MODE,                 // UVP((Source Mode 1)
        _AUTO_RECOVER_MODE,                 // OVP((Source Mode 1)
        _AUTO_RECOVER_MODE,                 // OTP
        _AUTO_RECOVER_MODE,                 // Reverse Current Protection mode

        INDUCTOR_PEAK_CURRENT_LIMIT_5A,     // Inductor Peak Current Limit
        _V_SWO_UVP_THRESHOLD_60P,           // VSWO UVP Threshold (Buck mode)
        _V_VBUS_OVP_THRESHOLD_125P,         // VVBUS OVP Threshold (Buck mode)
        _OUTPUT_CURRENT_LIMIT_50MV,         // Output Current Limit

        0x00,                               // UVP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // OVP Flag (Read Only)
        0x00,                               // Over temperature protection Flag (Read Only)
        0x00,                               // Voltage reserved(Read Only)
        0x00,                               // VBUS absolute maximum OVP Flag (Read Only)
        0x00,                               // Reserved
        0x00,                               // Power Good
    },
    // P0 Port Setting
    {
        _MODE_ALL_OFF1,                     // Mode
        _TURN_OFF_DISCHANGE_AT_ALL,         // Discharge Enable at All off
        0x00,                               // Reserved
        _DISCHARGE_REG_1_80_K,              // Discharge Resistor Setting
        _OFF,                               // Reset all registers to default value. Automatically clear to "0" after reset is done.

        _OUTPUT_VOLTAGE_5V,                 // Output Voltage Setting
        0x00,                               // Reserved

        0x00,                               // Reserved
        _SY8665_INT_DISABLE,                // Interrupt Disable
        _GO_BIT_INTERNAL_MODE,              // Go_bit
        _CABLE_IMPEDANCE_RCMP_100,          // Cable Impedance Compensation
        _LIGHT_LOAD_PULSE_SKIP,             // Light Load Operation

        0x00,                               // Reserved
        _BUCK_SWITCHING_250KHZ,             // Buck Switching Frequency Setting
        _AUTO_RECOVER_MODE,                 // UVP((Source Mode 1)
        _AUTO_RECOVER_MODE,                 // OVP((Source Mode 1)
        _AUTO_RECOVER_MODE,                 // OTP
        _AUTO_RECOVER_MODE,                 // Reverse Current Protection mode

        INDUCTOR_PEAK_CURRENT_LIMIT_5A,     // Inductor Peak Current Limit
        _V_SWO_UVP_THRESHOLD_60P,           // VSWO UVP Threshold (Buck mode)
        _V_VBUS_OVP_THRESHOLD_125P,         // VVBUS OVP Threshold (Buck mode)
        _OUTPUT_CURRENT_LIMIT_50MV,         // Output Current Limit

        0x00,                               // UVP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // OVP Flag (Read Only)
        0x00,                               // Over temperature protection Flag (Read Only)
        0x00,                               // Voltage reserved(Read Only)
        0x00,                               // VBUS absolute maximum OVP Flag (Read Only)
        0x00,                               // Reserved
        0x00,                               // Power Good
    },
    // Adaptor Setting
    {
        _MODE_ALL_OFF1,                     // Mode
        _TURN_OFF_DISCHANGE_AT_ALL,         // Discharge Enable at All off
        0x00,                               // Reserved
        _DISCHARGE_REG_1_80_K,              // Discharge Resistor Setting
        _OFF,                               // Reset all registers to default value. Automatically clear to "0" after reset is done.

        _OUTPUT_VOLTAGE_5V,                 // Output Voltage Setting
        0x00,                               // Reserved

        0x00,                               // Reserved
        _SY8665_INT_DISABLE,                // Interrupt Disable
        _GO_BIT_INTERNAL_MODE,              // Go_bit
        _CABLE_IMPEDANCE_RCMP_100,          // Cable Impedance Compensation
        _LIGHT_LOAD_PULSE_SKIP,             // Light Load Operation

        0x00,                               // Reserved
        _BUCK_SWITCHING_250KHZ,             // Buck Switching Frequency Setting
        _AUTO_RECOVER_MODE,                 // UVP((Source Mode 1)
        _AUTO_RECOVER_MODE,                 // OVP((Source Mode 1)
        _AUTO_RECOVER_MODE,                 // OTP
        _AUTO_RECOVER_MODE,                 // Reverse Current Protection mode

        INDUCTOR_PEAK_CURRENT_LIMIT_5A,     // Inductor Peak Current Limit
        _V_SWO_UVP_THRESHOLD_60P,           // VSWO UVP Threshold (Buck mode)
        _V_VBUS_OVP_THRESHOLD_125P,         // VVBUS OVP Threshold (Buck mode)
        _OUTPUT_CURRENT_LIMIT_50MV,         // Output Current Limit

        0x00,                               // UVP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // OVP Flag (Read Only)
        0x00,                               // Over temperature protection Flag (Read Only)
        0x00,                               // Voltage reserved(Read Only)
        0x00,                               // VBUS absolute maximum OVP Flag (Read Only)
        0x00,                               // Reserved
        0x00,                               // Power Good
    },
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSY8665RegisterMap g_pstPmicSy8665Data[4];


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PMIC Initial Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicSy8665ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort)
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
    g_pstPmicSy8665Data[ucDataIndex] = tPmicSy8665InitialData[ucDataIndex];

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

    // Start Initial
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 5, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1);

    // Clear INT Flag
    UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _SY8665_STATE_REG, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_STATE_REG);
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort)
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
    g_pstPmicSy8665Data[ucDataIndex] = tPmicSy8665InitialData[ucDataIndex];

    // Initial Pmic Value
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 5, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1);

    // Clear INT Flag
    UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _SY8665_STATE_REG, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_STATE_REG);
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
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
    g_pstPmicSy8665Data[ucDataIndex] = tPmicSy8665InitialData[ucDataIndex];

    // Initial Pmic Value
    UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 5, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1);

    // Clear INT Flag
    UserCommonUsbTypeCPmicIICRead_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY8665_STATE_REG, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_STATE_REG);
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
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

    if(usVoltage > 2000) // Maximum Voltage: 20V
    {
        usVoltage = 2000;
    }

    // Set operation mode
    if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SNK)
    {
        // Sink mode1: 5V~20V@5A
        g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_SINK_MODE1;
    }
    else // _TYPE_C_PMIC_DIRECTION_SRC
    {
        if(usVoltage >= (2000)) // 20V (unit: 10mV)
        {
            // Source mode2: 20V@5A
            g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_SOURCE_MODE2;
        }
        else
        {
            // Source mode1: 3V~12V@5A, 15V@3A
            g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_SOURCE_MODE1;
        }
    }

    // Set VBUS Voltage
    if(usVoltage <= (300)) // 3V (unit: 10mV)
    {
        g_pstPmicSy8665Data[ucDataIndex].b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V;
    }
    else if(usVoltage < (2000))
    {
        g_pstPmicSy8665Data[ucDataIndex].b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V + (((usVoltage) - 300) / 20);
    }

    // Set Switching Frequency
    g_pstPmicSy8665Data[ucDataIndex].b2BuckSwitchingFrequence = _BUCK_SWITCHING_500KHZ;

    // Set VBUS Current Limit
    if(usCurrent <= 100) // < 1A (unit: 10mA, Rsense: 10m Ohm)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_10MV;
    }
    else if(usCurrent <= 150)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_15MV;
    }
    else if(usCurrent <= 200)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_20MV;
    }
    else if(usCurrent <= 250)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_25MV;
    }
    else if(usCurrent <= 300)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_30MV;
    }
    else if(usCurrent <= 400)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_40MV;
    }
    else if(usCurrent <= 500)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_50MV;
    }
    else
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_60MV;
    }

    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 5, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
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

    if(usVoltage > 2000) // Maximum Voltage: 20V
    {
        usVoltage = 2000;
    }

    // Set operation mode
    if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SNK)
    {
        // Sink mode1: 5V~20V@5A
        g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_SINK_MODE1;
    }
    else // _TYPE_C_PMIC_DIRECTION_SRC
    {
        if(usVoltage >= (2000)) // 20V (unit: 10mV)
        {
            // Source mode2: 20V@5A
            g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_SOURCE_MODE2;
        }
        else
        {
            // Source mode1: 3V~12V@5A, 15V@3A
            g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_SOURCE_MODE1;
        }
    }

    // Set VBUS Voltage
    if(usVoltage <= (300)) // 3V (unit: 10mV)
    {
        g_pstPmicSy8665Data[ucDataIndex].b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V;
    }
    else if(usVoltage < (2000))
    {
        g_pstPmicSy8665Data[ucDataIndex].b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V + (((usVoltage) - 300) / 20);
    }

    // Set Switching Frequency
    g_pstPmicSy8665Data[ucDataIndex].b2BuckSwitchingFrequence = _BUCK_SWITCHING_500KHZ;

    // Set VBUS Current Limit
    if(usCurrent <= 100) // < 1A (unit: 10mA, Rsense: 10m Ohm)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_10MV;
    }
    else if(usCurrent <= 150)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_15MV;
    }
    else if(usCurrent <= 200)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_20MV;
    }
    else if(usCurrent <= 250)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_25MV;
    }
    else if(usCurrent <= 300)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_30MV;
    }
    else if(usCurrent <= 400)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_40MV;
    }
    else if(usCurrent <= 500)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_50MV;
    }
    else
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_60MV;
    }

    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 5, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
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

    if(usVoltage > 2000) // Maximum Voltage: 20V
    {
        usVoltage = 2000;
    }

    // Set operation mode
    if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SNK)
    {
        // Sink mode1: 5V~20V@5A
        g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_SINK_MODE1;
    }
    else // _TYPE_C_PMIC_DIRECTION_SRC
    {
        if(usVoltage >= (2000)) // 20V (unit: 10mV)
        {
            // Source mode2: 20V@5A
            g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_SOURCE_MODE2;
        }
        else
        {
            // Source mode1: 3V~12V@5A, 15V@3A
            g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_SOURCE_MODE1;
        }
    }

    // Set VBUS Voltage
    if(usVoltage <= (300)) // 3V (unit: 10mV)
    {
        g_pstPmicSy8665Data[ucDataIndex].b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V;
    }
    else if(usVoltage < (2000))
    {
        g_pstPmicSy8665Data[ucDataIndex].b7OutputVoltageSetting = _OUTPUT_VOLTAGE_3V + (((usVoltage) - 300) / 20);
    }

    // Set Switching Frequency
    g_pstPmicSy8665Data[ucDataIndex].b2BuckSwitchingFrequence = _BUCK_SWITCHING_500KHZ;

    // Set VBUS Current Limit
    if(usCurrent <= 100) // < 1A (unit: 10mA, Rsense: 10m Ohm)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_10MV;
    }
    else if(usCurrent <= 150)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_15MV;
    }
    else if(usCurrent <= 200)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_20MV;
    }
    else if(usCurrent <= 250)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_25MV;
    }
    else if(usCurrent <= 300)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_30MV;
    }
    else if(usCurrent <= 400)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_40MV;
    }
    else if(usCurrent <= 500)
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_50MV;
    }
    else
    {
        g_pstPmicSy8665Data[ucDataIndex].b3OutputCurrentLimit = _OUTPUT_CURRENT_LIMIT_60MV;
    }

    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 5, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665TurnOff(EnumTypeCPcbPort enumTypeCPcbPort)
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

    // Set operation mode
    g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_ALL_OFF1;

    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
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

    // Set operation mode
    g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_ALL_OFF1;

    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
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

    // Set operation mode
    g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_ALL_OFF1;

    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
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
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_DISABLE)
    {
        g_pstPmicSy8665Data[ucDataIndex].b1DischargeEnableAllOff = _TURN_OFF_DISCHANGE_AT_ALL;
    }
    else
    {
        g_pstPmicSy8665Data[ucDataIndex].b1DischargeEnableAllOff = _TURN_ON_DISCHANGE_AT_ALL;
    }

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
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
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
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_DISABLE)
    {
        g_pstPmicSy8665Data[ucDataIndex].b1DischargeEnableAllOff = _TURN_OFF_DISCHANGE_AT_ALL;
    }
    else
    {
        g_pstPmicSy8665Data[ucDataIndex].b1DischargeEnableAllOff = _TURN_ON_DISCHANGE_AT_ALL;
    }

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
    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
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
    if(enumEn == _TYPE_C_PMIC_DISCHARGE_DISABLE)
    {
        g_pstPmicSy8665Data[ucDataIndex].b1DischargeEnableAllOff = _TURN_OFF_DISCHANGE_AT_ALL;
    }
    else
    {
        g_pstPmicSy8665Data[ucDataIndex].b1DischargeEnableAllOff = _TURN_ON_DISCHANGE_AT_ALL;
    }

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
    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
        {
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
            PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
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
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicSy8665ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort)
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

    ucResult = UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _SY8665_STATE_REG, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_STATE_REG);

    DebugMessageTypeC("Pmic:Embbeded Type-C Port", ucDataIndex);
    DebugMessageTypeC("0.Pmic:Power Good Status", g_pstPmicSy8665Data[ucDataIndex].b1PowerGood);
    DebugMessageTypeC("0.Pmic:Vbus Absolute Maximum Ovp", g_pstPmicSy8665Data[ucDataIndex].b1IntFlagVbusAbsoluteMaximumOvp);
    DebugMessageTypeC("0.Pmic:Voltage Reversed", g_pstPmicSy8665Data[ucDataIndex].b1IntFlagVoltageReversed);
    DebugMessageTypeC("0.Pmic:Over Temperature Protection", g_pstPmicSy8665Data[ucDataIndex].b1IntFlagOverTemperatureProtection);
    DebugMessageTypeC("0.Pmic:OVP Flag", g_pstPmicSy8665Data[ucDataIndex].b1IntFlagOvp);
    DebugMessageTypeC("0.Pmic:OCP Flag", g_pstPmicSy8665Data[ucDataIndex].b1IntFlagOcp);
    DebugMessageTypeC("0.Pmic:UVO Flag", g_pstPmicSy8665Data[ucDataIndex].b1IntFlagUvp);

    if (ucResult == _SUCCESS)
    {
        DebugMessageTypeC("_TYPE_C_PMIC_CONTROL_SUCCESS", ucResult);

        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }
    else
    {
        DebugMessageTypeC("_TYPE_C_PMIC_CONTROL_FAIL", ucResult);

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
WORD ExternalDeviceInterfaceTypeCPmicSy8665ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    return 0;
}
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
//--------------------------------------------------
// Description  : PMIC Vbus Force Off Config
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy8665ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort)
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
    g_pstPmicSy8665Data[ucDataIndex].b3Mode = _MODE_ALL_OFF1;

    if(UserCommonUsbTypeCPmicSetForceOffIIC(enumTypeCPcbPort, ucSlaveAddr, _SY8665_FUNCTION_SETTING1, _SY8665_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy8665Data[ucDataIndex]) + _SY8665_FUNCTION_SETTING1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_SY8665_SUPPORT == _ON))

