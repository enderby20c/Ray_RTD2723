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
// ID Code      : TypeC_Pmic_SILERGY_SY9329.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "../Header/TypeC_Pmic_SILERGY_SY9329.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_SY9329_SUPPORT == _ON))

#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
#if(_D0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SY9329 can't support voltage compensation!!!"
#endif

#if(_D0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY9329 can't support PPS!!!"
#endif
#endif // End of #if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)

#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
#if(_D1_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D1_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D1_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D1_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D1_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SY9329 can't support voltage compensation!!!"
#endif

#if(_D1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY9329 can't support PPS!!!"
#endif
#endif // End of #if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)

#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
#if(_P0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _P0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_P0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _P0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_P0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SY9329 can't support voltage compensation!!!"
#endif

#if(_P0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY9329 can't support PPS!!!"
#endif
#endif // End of #if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)

#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
#if(_ADAPTOR_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SY9329 can't support voltage compensation!!!"
#endif

#if(_ADAPTOR_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY9329 can't support PPS!!!"
#endif
#endif // End of #if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)


//****************************************************************************
// CODE TABLES
//****************************************************************************
StructSY9329RegisterMap code tPmicSy9329InitialData[] =
{
    // D0 Port Setting
    {
        0x00,                               // Reserved
        _SY9329_ADDR_00_VBUS_DISCHARGE,     // Discharge Disable
        _SY9329_ADDR_00_ADC_MODE,           // ADC Mode select single detect mode
        _SY9329_ADDR_00_ADC_ACTIVE,         // ADC Disable
        _SY9329_ADDR_00_LOWBATTERY_VOLTAGE, // Low Battery setting by define
        _SY9329_ADDR_00_REGULATOR_ENABLE,   // Regulator Disable

        _SY9329_ADDR_01_VOLTAGE_ADJUST,     // VBUS Adjust 0%
        _SY9329_ADDR_01_VOLTAGE_SETTING,    // VBUS Output 5V
        _SY9329_ADDR_01_SWITCH_FREQ,        // Switching Freq by define

        0x00,                               // Reserved
        _SY9329_ADDR_02_VBUS_UVP_SETTING,   // UVP Threshold by define
        _SY9329_ADDR_02_VBUS_OVP_SETTING,   // OVP Threshold by define
        _SY9329_ADDR_02_CURRENT_LIMIT,      // OCP 2.5A

        0x00,                               // Reserved
        _SY9329_ADDR_03_BIDIRECTIONAL_MODE, // Direction is source mode
        _SY9329_ADDR_03_OTP_MODE,           // OTP mode by define
        _SY9329_ADDR_03_VBUS_UVP_MODE,      // UVP mode by define
        _SY9329_ADDR_03_LOCP_MODE,          // LOCP mode by define
        _SY9329_ADDR_03_LOCP_SETTING,       // LOCP by define

        0x00,                               // Reserved
        0x00,                               // BAT Power status (Read Only)
        0x00,                               // BAT/VBUS relation (Read Only)
        0x00,                               // Power Good Status (Read Only)

        0x00,                               // Reserved
        0x00,                               // OTP Flag (Read Only)
        0x00,                               // UVP Flag (Read Only)
        0x00,                               // LOCP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // ADC Data Ready (Read Only)

        0x00,                               // BAT Voltage Value (Read Only)
        0x00,                               // VBUS Voltage Value (Read Only)
        0x00,                               // VBUS Current Value (Read Only)
    },
    // D1 Port Setting
    {
        0x00,                               // Reserved
        _SY9329_ADDR_00_VBUS_DISCHARGE,     // Discharge Disable
        _SY9329_ADDR_00_ADC_MODE,           // ADC Mode select single detect mode
        _SY9329_ADDR_00_ADC_ACTIVE,         // ADC Disable
        _SY9329_ADDR_00_LOWBATTERY_VOLTAGE, // Low Battery setting by define
        _SY9329_ADDR_00_REGULATOR_ENABLE,   // Regulator Disable

        _SY9329_ADDR_01_VOLTAGE_ADJUST,     // VBUS Adjust 0%
        _SY9329_ADDR_01_VOLTAGE_SETTING,    // VBUS Output 5V
        _SY9329_ADDR_01_SWITCH_FREQ,        // Switching Freq by define

        0x00,                               // Reserved
        _SY9329_ADDR_02_VBUS_UVP_SETTING,   // UVP Threshold by define
        _SY9329_ADDR_02_VBUS_OVP_SETTING,   // OVP Threshold by define
        _SY9329_ADDR_02_CURRENT_LIMIT,      // OCP 2.5A

        0x00,                               // Reserved
        _SY9329_ADDR_03_BIDIRECTIONAL_MODE, // Direction is source mode
        _SY9329_ADDR_03_OTP_MODE,           // OTP mode by define
        _SY9329_ADDR_03_VBUS_UVP_MODE,      // UVP mode by define
        _SY9329_ADDR_03_LOCP_MODE,          // LOCP mode by define
        _SY9329_ADDR_03_LOCP_SETTING,       // LOCP by define

        0x00,                               // Reserved
        0x00,                               // BAT Power status (Read Only)
        0x00,                               // BAT/VBUS relation (Read Only)
        0x00,                               // Power Good Status (Read Only)

        0x00,                               // Reserved
        0x00,                               // OTP Flag (Read Only)
        0x00,                               // UVP Flag (Read Only)
        0x00,                               // LOCP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // ADC Data Ready (Read Only)

        0x00,                               // BAT Voltage Value (Read Only)
        0x00,                               // VBUS Voltage Value (Read Only)
        0x00,                               // VBUS Current Value (Read Only)
    },
    // P0 Port Setting
    {
        0x00,                               // Reserved
        _SY9329_ADDR_00_VBUS_DISCHARGE,     // Discharge Disable
        _SY9329_ADDR_00_ADC_MODE,           // ADC Mode select single detect mode
        _SY9329_ADDR_00_ADC_ACTIVE,         // ADC Disable
        _SY9329_ADDR_00_LOWBATTERY_VOLTAGE, // Low Battery setting by define
        _SY9329_ADDR_00_REGULATOR_ENABLE,   // Regulator Disable

        _SY9329_ADDR_01_VOLTAGE_ADJUST,     // VBUS Adjust 0%
        _SY9329_ADDR_01_VOLTAGE_SETTING,    // VBUS Output 5V
        _SY9329_ADDR_01_SWITCH_FREQ,        // Switching Freq by define

        0x00,                               // Reserved
        _SY9329_ADDR_02_VBUS_UVP_SETTING,   // UVP Threshold by define
        _SY9329_ADDR_02_VBUS_OVP_SETTING,   // OVP Threshold by define
        _SY9329_ADDR_02_CURRENT_LIMIT,      // OCP 2.5A

        0x00,                               // Reserved
        _SY9329_ADDR_03_BIDIRECTIONAL_MODE, // Direction is source mode
        _SY9329_ADDR_03_OTP_MODE,           // OTP mode by define
        _SY9329_ADDR_03_VBUS_UVP_MODE,      // UVP mode by define
        _SY9329_ADDR_03_LOCP_MODE,          // LOCP mode by define
        _SY9329_ADDR_03_LOCP_SETTING,       // LOCP by define

        0x00,                               // Reserved
        0x00,                               // BAT Power status (Read Only)
        0x00,                               // BAT/VBUS relation (Read Only)
        0x00,                               // Power Good Status (Read Only)

        0x00,                               // Reserved
        0x00,                               // OTP Flag (Read Only)
        0x00,                               // UVP Flag (Read Only)
        0x00,                               // LOCP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // ADC Data Ready (Read Only)

        0x00,                               // BAT Voltage Value (Read Only)
        0x00,                               // VBUS Voltage Value (Read Only)
        0x00,                               // VBUS Current Value (Read Only)
    },
    // Adaptor Setting
    {
        0x00,                               // Reserved
        _SY9329_ADDR_00_VBUS_DISCHARGE,     // Discharge Disable
        _SY9329_ADDR_00_ADC_MODE,           // ADC Mode select single detect mode
        _SY9329_ADDR_00_ADC_ACTIVE,         // ADC Disable
        _SY9329_ADDR_00_LOWBATTERY_VOLTAGE, // Low Battery setting by define
        _SY9329_ADDR_00_REGULATOR_ENABLE,   // Regulator Disable

        _SY9329_ADDR_01_VOLTAGE_ADJUST,     // VBUS Adjust 0%
        _SY9329_ADDR_01_VOLTAGE_SETTING,    // VBUS Output 5V
        _SY9329_ADDR_01_SWITCH_FREQ,        // Switching Freq by define

        0x00,                               // Reserved
        _SY9329_ADDR_02_VBUS_UVP_SETTING,   // UVP Threshold by define
        _SY9329_ADDR_02_VBUS_OVP_SETTING,   // OVP Threshold by define
        _SY9329_ADDR_02_CURRENT_LIMIT,      // OCP 2.5A

        0x00,                               // Reserved
        _SY9329_ADDR_03_BIDIRECTIONAL_MODE, // Direction is source mode
        _SY9329_ADDR_03_OTP_MODE,           // OTP mode by define
        _SY9329_ADDR_03_VBUS_UVP_MODE,      // UVP mode by define
        _SY9329_ADDR_03_LOCP_MODE,          // LOCP mode by define
        _SY9329_ADDR_03_LOCP_SETTING,       // LOCP by define

        0x00,                               // Reserved
        0x00,                               // BAT Power status (Read Only)
        0x00,                               // BAT/VBUS relation (Read Only)
        0x00,                               // Power Good Status (Read Only)

        0x00,                               // Reserved
        0x00,                               // OTP Flag (Read Only)
        0x00,                               // UVP Flag (Read Only)
        0x00,                               // LOCP Flag (Read Only)
        0x00,                               // OCP Flag (Read Only)
        0x00,                               // ADC Data Ready (Read Only)

        0x00,                               // BAT Voltage Value (Read Only)
        0x00,                               // VBUS Voltage Value (Read Only)
        0x00,                               // VBUS Current Value (Read Only)
    },
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSY9329RegisterMap g_pstPmicSy9329Data[4];


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PMIC Initial Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicSy9329ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort)
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
    g_pstPmicSy9329Data[ucDataIndex] = tPmicSy9329InitialData[ucDataIndex];

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
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1);

    // Clear INT Flag
    UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _SY9329_STATE_REG, _SY9329_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_STATE_REG);
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort)
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
    g_pstPmicSy9329Data[ucDataIndex] = tPmicSy9329InitialData[ucDataIndex];

    // Initial Pmic Value
    UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1);

    // Clear INT Flag
    UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _SY9329_STATE_REG, _SY9329_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_STATE_REG);
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
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
    g_pstPmicSy9329Data[ucDataIndex] = tPmicSy9329InitialData[ucDataIndex];

    // Initial Pmic Value
    UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1);

    // Clear INT Flag
    UserCommonUsbTypeCPmicIICRead_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9329_STATE_REG, _SY9329_SUBADDR_LENGTH, 2, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_STATE_REG);
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
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

    // Set PMIC Direction
    g_pstPmicSy9329Data[ucDataIndex].b1BiDirSetting = !enumPowerDirection;

    // Set VBUS Voltage
    switch(usVoltage)
    {
        case _SY9329_VBUS_VOLTAGE_5V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x00;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 5;
            break;

        case _SY9329_VBUS_VOLTAGE_7V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x03;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_9V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x04;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_12V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x05;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_15V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x06;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x00;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_20V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x07;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x00;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        default:

            break;
    }

    // Set VBUS Current Limit
    if(usCurrent <= 100)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x00;
    }
    else if(usCurrent <= 150)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x01;
    }
    else if(usCurrent <= 200)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x02;
    }
    else if(usCurrent <= 250)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x03;
    }
    else if(usCurrent <= 300)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x04;
    }
    else if(usCurrent <= 400)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x05;
    }
    else
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x06;
    }

    if(g_pstPmicSy9329Data[ucDataIndex].b1PMICEnable == _OFF)
    {
        // Enable PMIC
        g_pstPmicSy9329Data[ucDataIndex].b1PMICEnable = _ON;

        if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }
    else
    {
        if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG2, _SY9329_SUBADDR_LENGTH, 3, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG2) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
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

    // Set PMIC Direction
    g_pstPmicSy9329Data[ucDataIndex].b1BiDirSetting = !enumPowerDirection;

    // Set VBUS Voltage
    switch(usVoltage)
    {
        case _SY9329_VBUS_VOLTAGE_5V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x00;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 5;
            break;

        case _SY9329_VBUS_VOLTAGE_7V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x03;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_9V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x04;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_12V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x05;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_15V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x06;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x00;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_20V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x07;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x00;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        default:

            break;
    }

    // Set VBUS Current Limit
    if(usCurrent <= 100)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x00;
    }
    else if(usCurrent <= 150)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x01;
    }
    else if(usCurrent <= 200)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x02;
    }
    else if(usCurrent <= 250)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x03;
    }
    else if(usCurrent <= 300)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x04;
    }
    else if(usCurrent <= 400)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x05;
    }
    else
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x06;
    }

    if(g_pstPmicSy9329Data[ucDataIndex].b1PMICEnable == _OFF)
    {
        // Enable PMIC
        g_pstPmicSy9329Data[ucDataIndex].b1PMICEnable = _ON;

        if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }
    else
    {
        if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG2, _SY9329_SUBADDR_LENGTH, 3, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG2) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
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

    // Set PMIC Direction
    g_pstPmicSy9329Data[ucDataIndex].b1BiDirSetting = !enumPowerDirection;

    // Set VBUS Voltage
    switch(usVoltage)
    {
        case _SY9329_VBUS_VOLTAGE_5V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x00;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 5;
            break;

        case _SY9329_VBUS_VOLTAGE_7V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x03;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_9V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x04;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_12V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x05;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x01;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_15V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x06;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x00;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        case _SY9329_VBUS_VOLTAGE_20V:
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSSetting = 0x07;
            g_pstPmicSy9329Data[ucDataIndex].b2SwitchFreq = 0x00;
            g_pstPmicSy9329Data[ucDataIndex].b3VBUSAdjust = 2;
            break;

        default:

            break;
    }

    // Set VBUS Current Limit
    if(usCurrent <= 100)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x00;
    }
    else if(usCurrent <= 150)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x01;
    }
    else if(usCurrent <= 200)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x02;
    }
    else if(usCurrent <= 250)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x03;
    }
    else if(usCurrent <= 300)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x04;
    }
    else if(usCurrent <= 400)
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x05;
    }
    else
    {
        g_pstPmicSy9329Data[ucDataIndex].b3VOCPSetting = 0x06;
    }

    if(g_pstPmicSy9329Data[ucDataIndex].b1PMICEnable == _OFF)
    {
        // Enable PMIC
        g_pstPmicSy9329Data[ucDataIndex].b1PMICEnable = _ON;

        if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 4, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1) == _FAIL)
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }
    }
    else
    {
        if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG2, _SY9329_SUBADDR_LENGTH, 3, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG2) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329TurnOff(EnumTypeCPcbPort enumTypeCPcbPort)
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

    // Disable PMIC
    g_pstPmicSy9329Data[ucDataIndex].b1PMICEnable = _OFF;

    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
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

    // Disable PMIC
    g_pstPmicSy9329Data[ucDataIndex].b1PMICEnable = _OFF;

    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
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

    // Disable PMIC
    g_pstPmicSy9329Data[ucDataIndex].b1PMICEnable = _OFF;

    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
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
    g_pstPmicSy9329Data[ucDataIndex].b1VBUSDischarge = !enumEn;

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
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
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
    g_pstPmicSy9329Data[ucDataIndex].b1VBUSDischarge = !enumEn;

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
    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
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
    g_pstPmicSy9329Data[ucDataIndex].b1VBUSDischarge = !enumEn;

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
    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
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
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicSy9329ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort)
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

    ucResult = UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _SY9329_STATE_REG, _SY9329_SUBADDR_LENGTH, 5, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_STATE_REG);

    DebugMessageTypeC("Pmic:Embbeded Type-C Port", ucDataIndex);
    DebugMessageTypeC("0.Pmic:Power Good Status", g_pstPmicSy9329Data[ucDataIndex].b1PowerGoodState);
    DebugMessageTypeC("0.Pmic:Relation Status", g_pstPmicSy9329Data[ucDataIndex].b1BATVBUSRelation);
    DebugMessageTypeC("0.Pmic:Battery Status", g_pstPmicSy9329Data[ucDataIndex].b1BATStatus);
    DebugMessageTypeC("0.Pmic:VBUS OCP Flag", g_pstPmicSy9329Data[ucDataIndex].b1VOCPFlag);
    DebugMessageTypeC("0.Pmic:Inductor OCP Flag", g_pstPmicSy9329Data[ucDataIndex].b1LOCPFlag);
    DebugMessageTypeC("0.Pmic:VBUS UVP Flag", g_pstPmicSy9329Data[ucDataIndex].b1UVPFlag);
    DebugMessageTypeC("0.Pmic:OTP Flag", g_pstPmicSy9329Data[ucDataIndex].b1OTPFlag);
    DebugMessageTypeC("0.Pmic:Battery Voltage Value", g_pstPmicSy9329Data[ucDataIndex].ucBATValue);
    DebugMessageTypeC("0.Pmic:VBUS Voltage Value", g_pstPmicSy9329Data[ucDataIndex].ucVBUSValue);
    DebugMessageTypeC("0.Pmic:VBUS Current Value", g_pstPmicSy9329Data[ucDataIndex].ucVBUSCurrentValue);

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
WORD ExternalDeviceInterfaceTypeCPmicSy9329ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort)
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
    UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CURRENT_VALUE_REG, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CURRENT_VALUE_REG);

    // Translate PMIC's Current Unit to 10mA/bit
    usCurrent = ((WORD)(((DWORD)g_pstPmicSy9329Data[ucDataIndex].ucVBUSCurrentValue * 100 * 6) / 256));

    // Show data
    DebugMessageTypeC("Pmic:Embbeded Type-C Port", ucDataIndex);
    DebugMessageTypeC("Pmic:Current Value(Bit)", g_pstPmicSy9329Data[ucDataIndex].ucVBUSCurrentValue);
    DebugMessageTypeC("Pmic:Current Value(10mA)", usCurrent);

    return usCurrent;
}
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
//--------------------------------------------------
// Description  : PMIC Vbus Force Off Config
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSy9329ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort)
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
    g_pstPmicSy9329Data[ucDataIndex].b1PMICEnable = _OFF;

    if(UserCommonUsbTypeCPmicSetForceOffIIC(enumTypeCPcbPort, ucSlaveAddr, _SY9329_CTRL_REG1, _SY9329_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicSy9329Data[ucDataIndex]) + _SY9329_CTRL_REG1) == _FAIL)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_SY9329_SUPPORT == _ON))

