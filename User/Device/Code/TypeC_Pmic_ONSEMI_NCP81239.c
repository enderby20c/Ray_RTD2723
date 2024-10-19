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
// ID Code      : TypeC_Pmic_ONSEMI_NCP81239.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "../Header/TypeC_Pmic_ONSEMI_NCP81239.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_NCP81239_SUPPORT == _ON))

#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
#if(_D0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#warning "NCP81239 can't support OCP by polling PMIC ADC!!!"
#endif

#if(_D0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "NCP81239 can't support PPS!!!"
#endif
#endif // End of #if(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)

#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
#if(_D1_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _D1_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_D1_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _D1_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_D1_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#warning "NCP81239 can't support OCP by polling PMIC ADC!!!"
#endif

#if(_D1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "NCP81239 can't support PPS!!!"
#endif
#endif // End of #if(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)

#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
#if(_P0_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _P0_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_P0_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _P0_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_P0_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#warning "NCP81239 can't support OCP by polling PMIC ADC!!!"
#endif

#if(_P0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "NCP81239 can't support PPS!!!"
#endif
#endif // End of #if(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)

#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
#if(_ADAPTOR_TYPE_C_PMIC_IIC == _OFF)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_IIC should be ON!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _ADAPTOR_TYPE_C_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#warning "NCP81239 can't support OCP by polling PMIC ADC!!!"
#endif

#if(_ADAPTOR_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "NCP81239 can't support PPS!!!"
#endif
#endif // End of #if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)


//****************************************************************************
// CODE TABLES
//****************************************************************************
StructNCP81239RegisterMap code tPmicNcp81239InitialData[] =
{
    // D0 Port Setting
    {
        0x00,                                   // Reserved
        0x00,                                   // Hardware enable selected
        0x00,                                   // Software control disable
        0x00,                                   // Reserved

        _NCP81239_ADDR_01_VBUS,                 // VBUS setting is 5V

        _NCP81239_ADDR_02_SLEW_RATE,            // Slwe rate by define
        0x00,                                   // Reserved

        _NCP81239_ADDR_03_PWM_FREQ,             // by define
        0x00,                                   // PWM freq Reserved
        0x00,                                   // DAC resolution is 10mV
        0x00,                                   // Reserved

        0x00,                                   // PFET is disable
        0x00,                                   // CFET is disable
        0x00,                                   // Reserved
        0x00,                                   // CS2 discharge is disable
        0x00,                                   // Reserved

        _NCP81239_ADDR_05_OCP_CLIM_POS,         // internal positive current limit by define
        0x00,                                   // Reserved
        _NCP81239_ADDR_05_OCP_CLIM_NEG,         // internal negative current limit by define
        0x00,                                   // Reserved

        _NCP81239_ADDR_06_CS1_CLIND,            // CS1 positive current limit
        _NCP81239_ADDR_06_CS2_CLIND,            // CS2 positive current limit
        0x00,                                   // Reserved

        0x01,                                   // Low Amp GM value
        0x01,                                   // register of amp gm settings
        0x05,                                   // High Amp GM value
        0x00,                                   // register of amp gm config

        0x00,                                   // ADC Trigger
        0x00,                                   // ADC MUX select
        0x00,                                   // ADC is enable
        0x00,                                   // Reserved

        _NCP81239_ADDR_09_INT_MASK_CS_CLIND,    // cs_clind int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_OVP,         // OVP int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_OCP_P,       // OCP_P int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_PG_INT,      // PG int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_TSD,         // TSD int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_UVP,         // UVP int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_VCHN,        // VCHN int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_IIC_ACK,     // IIC_ACK int flag enable by define

        _NCP81239_ADDR_09_INT_MASK_SHUT_DOWN,   // SHUT_DOWN int flag enable by define
        0x00,                                   // Reserved

        _NCP81239_PMIC_SINK,                    // Source/Sink status
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved

        0x00,                                   // Vfb value(Read Only)
        0x00,                                   // Vin value(Read Only)
        0x00,                                   // CS2 value(Read Only)
        0x00,                                   // CS1 value(Read Only)

        0x00,                                   // CsClind flag(Read Only)
        0x00,                                   // OVP flag(Read Only)
        0x00,                                   // OCP_P flag(Read Only)
        0x00,                                   // PG flag(Read Only)
        0x00,                                   // TSD flag(Read Only)
        0x00,                                   // UVP flag(Read Only)
        0x00,                                   // VCHN flag(Read Only)
        0x00,                                   // IIC_ACK flag(Read Only)

        0x00,                                   // SHUT_DOWN flag(Read Only)
        0x00,                                   // Reserved
    },
    // D1 Port Setting
    {
        0x00,                                   // Reserved
        0x00,                                   // Hardware enable selected
        0x00,                                   // Software control disable
        0x00,                                   // Reserved

        _NCP81239_ADDR_01_VBUS,                 // VBUS setting is 5V

        _NCP81239_ADDR_02_SLEW_RATE,            // Slwe rate by define
        0x00,                                   // Reserved

        _NCP81239_ADDR_03_PWM_FREQ,             // by define
        0x00,                                   // PWM freq Reserved
        0x00,                                   // DAC resolution is 10mV
        0x00,                                   // Reserved

        0x00,                                   // PFET is disable
        0x00,                                   // CFET is disable
        0x00,                                   // Reserved
        0x00,                                   // CS2 discharge is disable
        0x00,                                   // Reserved

        _NCP81239_ADDR_05_OCP_CLIM_POS,         // internal positive current limit by define
        0x00,                                   // Reserved
        _NCP81239_ADDR_05_OCP_CLIM_NEG,         // internal negative current limit by define
        0x00,                                   // Reserved

        _NCP81239_ADDR_06_CS1_CLIND,            // CS1 positive current limit
        _NCP81239_ADDR_06_CS2_CLIND,            // CS2 positive current limit
        0x00,                                   // Reserved

        0x01,                                   // Low Amp GM value
        0x01,                                   // register of amp gm settings
        0x05,                                   // High Amp GM value
        0x00,                                   // register of amp gm config

        0x00,                                   // ADC Trigger
        0x00,                                   // ADC MUX select
        0x00,                                   // ADC is enable
        0x00,                                   // Reserved

        _NCP81239_ADDR_09_INT_MASK_CS_CLIND,    // cs_clind int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_OVP,         // OVP int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_OCP_P,       // OCP_P int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_PG_INT,      // PG int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_TSD,         // TSD int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_UVP,         // UVP int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_VCHN,        // VCHN int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_IIC_ACK,     // IIC_ACK int flag enable by define

        _NCP81239_ADDR_09_INT_MASK_SHUT_DOWN,   // SHUT_DOWN int flag enable by define
        0x00,                                   // Reserved

        _NCP81239_PMIC_SINK,                    // Source/Sink status
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved

        0x00,                                   // Vfb value(Read Only)
        0x00,                                   // Vin value(Read Only)
        0x00,                                   // CS2 value(Read Only)
        0x00,                                   // CS1 value(Read Only)

        0x00,                                   // CsClind flag(Read Only)
        0x00,                                   // OVP flag(Read Only)
        0x00,                                   // OCP_P flag(Read Only)
        0x00,                                   // PG flag(Read Only)
        0x00,                                   // TSD flag(Read Only)
        0x00,                                   // UVP flag(Read Only)
        0x00,                                   // VCHN flag(Read Only)
        0x00,                                   // IIC_ACK flag(Read Only)

        0x00,                                   // SHUT_DOWN flag(Read Only)
        0x00,                                   // Reserved
    },
    // P0 Port Setting
    {
        0x00,                                   // Reserved
        0x00,                                   // Hardware enable selected
        0x00,                                   // Software control disable
        0x00,                                   // Reserved

        _NCP81239_ADDR_01_VBUS,                 // VBUS setting is 5V

        _NCP81239_ADDR_02_SLEW_RATE,            // Slwe rate by define
        0x00,                                   // Reserved

        _NCP81239_ADDR_03_PWM_FREQ,             // by define
        0x00,                                   // PWM freq Reserved
        0x00,                                   // DAC resolution is 10mV
        0x00,                                   // Reserved

        0x00,                                   // PFET is disable
        0x00,                                   // CFET is disable
        0x00,                                   // Reserved
        0x00,                                   // CS2 discharge is disable
        0x00,                                   // Reserved

        _NCP81239_ADDR_05_OCP_CLIM_POS,         // internal positive current limit by define
        0x00,                                   // Reserved
        _NCP81239_ADDR_05_OCP_CLIM_NEG,         // internal negative current limit by define
        0x00,                                   // Reserved

        _NCP81239_ADDR_06_CS1_CLIND,            // CS1 positive current limit
        _NCP81239_ADDR_06_CS2_CLIND,            // CS2 positive current limit
        0x00,                                   // Reserved

        0x01,                                   // Low Amp GM value
        0x01,                                   // register of amp gm settings
        0x05,                                   // High Amp GM value
        0x00,                                   // register of amp gm config

        0x00,                                   // ADC Trigger
        0x00,                                   // ADC MUX select
        0x00,                                   // ADC is enable
        0x00,                                   // Reserved

        _NCP81239_ADDR_09_INT_MASK_CS_CLIND,    // cs_clind int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_OVP,         // OVP int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_OCP_P,       // OCP_P int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_PG_INT,      // PG int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_TSD,         // TSD int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_UVP,         // UVP int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_VCHN,        // VCHN int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_IIC_ACK,     // IIC_ACK int flag enable by define

        _NCP81239_ADDR_09_INT_MASK_SHUT_DOWN,   // SHUT_DOWN int flag enable by define
        0x00,                                   // Reserved

        _NCP81239_PMIC_SINK,                    // Source/Sink status
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved

        0x00,                                   // Vfb value(Read Only)
        0x00,                                   // Vin value(Read Only)
        0x00,                                   // CS2 value(Read Only)
        0x00,                                   // CS1 value(Read Only)

        0x00,                                   // CsClind flag(Read Only)
        0x00,                                   // OVP flag(Read Only)
        0x00,                                   // OCP_P flag(Read Only)
        0x00,                                   // PG flag(Read Only)
        0x00,                                   // TSD flag(Read Only)
        0x00,                                   // UVP flag(Read Only)
        0x00,                                   // VCHN flag(Read Only)
        0x00,                                   // IIC_ACK flag(Read Only)

        0x00,                                   // SHUT_DOWN flag(Read Only)
        0x00,                                   // Reserved
    },
    // Adaptor Setting
    {
        0x00,                                   // Reserved
        0x00,                                   // Hardware enable selected
        0x00,                                   // Software control disable
        0x00,                                   // Reserved

        _NCP81239_ADDR_01_VBUS,                 // VBUS setting is 5V

        _NCP81239_ADDR_02_SLEW_RATE,            // Slwe rate by define
        0x00,                                   // Reserved

        _NCP81239_ADDR_03_PWM_FREQ,             // by define
        0x00,                                   // PWM freq Reserved
        0x00,                                   // DAC resolution is 10mV
        0x00,                                   // Reserved

        0x00,                                   // PFET is disable
        0x00,                                   // CFET is disable
        0x00,                                   // Reserved
        0x00,                                   // CS2 discharge is disable
        0x00,                                   // Reserved

        _NCP81239_ADDR_05_OCP_CLIM_POS,         // internal positive current limit by define
        0x00,                                   // Reserved
        _NCP81239_ADDR_05_OCP_CLIM_NEG,         // internal negative current limit by define
        0x00,                                   // Reserved

        _NCP81239_ADDR_06_CS1_CLIND,            // CS1 positive current limit
        _NCP81239_ADDR_06_CS2_CLIND,            // CS2 positive current limit
        0x00,                                   // Reserved

        0x01,                                   // Low Amp GM value
        0x01,                                   // register of amp gm settings
        0x05,                                   // High Amp GM value
        0x00,                                   // register of amp gm config

        0x00,                                   // ADC Trigger
        0x00,                                   // ADC MUX select
        0x00,                                   // ADC is enable
        0x00,                                   // Reserved

        _NCP81239_ADDR_09_INT_MASK_CS_CLIND,    // cs_clind int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_OVP,         // OVP int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_OCP_P,       // OCP_P int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_PG_INT,      // PG int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_TSD,         // TSD int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_UVP,         // UVP int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_VCHN,        // VCHN int flag enable by define
        _NCP81239_ADDR_09_INT_MASK_IIC_ACK,     // IIC_ACK int flag enable by define

        _NCP81239_ADDR_09_INT_MASK_SHUT_DOWN,   // SHUT_DOWN int flag enable by define
        0x00,                                   // Reserved

        _NCP81239_PMIC_SINK,                    // Source/Sink status
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved
        0x00,                                   // Reserved

        0x00,                                   // Vfb value(Read Only)
        0x00,                                   // Vin value(Read Only)
        0x00,                                   // CS2 value(Read Only)
        0x00,                                   // CS1 value(Read Only)

        0x00,                                   // CsClind flag(Read Only)
        0x00,                                   // OVP flag(Read Only)
        0x00,                                   // OCP_P flag(Read Only)
        0x00,                                   // PG flag(Read Only)
        0x00,                                   // TSD flag(Read Only)
        0x00,                                   // UVP flag(Read Only)
        0x00,                                   // VCHN flag(Read Only)
        0x00,                                   // IIC_ACK flag(Read Only)

        0x00,                                   // SHUT_DOWN flag(Read Only)
        0x00,                                   // Reserved
    },
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructNCP81239RegisterMap g_pstPmicNcp81239Data[4];


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PMIC Initial Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicNcp81239ACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucDataIndex = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucDataIndex = 0;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucDataIndex = 1;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucDataIndex = 2;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucDataIndex = 3;
    }

    g_pstPmicNcp81239Data[ucDataIndex] = tPmicNcp81239InitialData[ucDataIndex];
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_POWER(_D0_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_POWER(_D1_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_POWER(_P0_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_OFF);
    }
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_POWER(_D0_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_POWER(_D1_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_POWER(_P0_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_OFF);
    }
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;
    BYTE ucPowerOnCount = 0;

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

    usCurrent = usCurrent;

    if(usVoltage > 2100)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(enumPowerDirection == _NCP81239_PMIC_SOURCE)
    {
        g_pstPmicNcp81239Data[ucDataIndex].b1CR0BPmicDirection = _NCP81239_PMIC_SOURCE;
    }
    else
    {
        g_pstPmicNcp81239Data[ucDataIndex].b1CR0BPmicDirection = _NCP81239_PMIC_SINK;

        if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
        {
            PCB_D0_PMIC_POWER(_D0_PMIC_POWER_OFF);
        }
        else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
        {
            PCB_D1_PMIC_POWER(_D1_PMIC_POWER_OFF);
        }
        else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
        {
            PCB_P0_PMIC_POWER(_P0_PMIC_POWER_OFF);
        }
        else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
        {
            PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_OFF);
        }

        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }

    // Set VBUS Voltage
    g_pstPmicNcp81239Data[ucDataIndex].ucCR01DacTarget = (BYTE)((usVoltage / 10) + _NCP81239_PMIC_VOLTAGE_OFFSET);

    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(PCB_D0_PMIC_POWER_DETECT() == _D0_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_D0_PMIC_POWER(_D0_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US();
            }

            if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(PCB_D1_PMIC_POWER_DETECT() == _D1_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_D1_PMIC_POWER(_D1_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US();
            }

            if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(PCB_P0_PMIC_POWER_DETECT() == _P0_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_P0_PMIC_POWER(_P0_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US();
            }

            if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(PCB_ADAPTOR_PMIC_POWER_DETECT() == _ADAPTOR_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US();
            }

            if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;
    BYTE ucPowerOnCount = 0;

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

    usCurrent = usCurrent;

    if(usVoltage > 2100)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(enumPowerDirection == _NCP81239_PMIC_SOURCE)
    {
        g_pstPmicNcp81239Data[ucDataIndex].b1CR0BPmicDirection = _NCP81239_PMIC_SOURCE;
    }
    else
    {
        g_pstPmicNcp81239Data[ucDataIndex].b1CR0BPmicDirection = _NCP81239_PMIC_SINK;

        if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
        {
            PCB_D0_PMIC_POWER(_D0_PMIC_POWER_OFF);
        }
        else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
        {
            PCB_D1_PMIC_POWER(_D1_PMIC_POWER_OFF);
        }
        else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
        {
            PCB_P0_PMIC_POWER(_P0_PMIC_POWER_OFF);
        }
        else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
        {
            PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_OFF);
        }

        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }

    // Set VBUS Voltage
    g_pstPmicNcp81239Data[ucDataIndex].ucCR01DacTarget = (BYTE)((usVoltage / 10) + _NCP81239_PMIC_VOLTAGE_OFFSET);

    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(PCB_D0_PMIC_POWER_DETECT() == _D0_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_D0_PMIC_POWER(_D0_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US_EXINT();
            }

            if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(PCB_D1_PMIC_POWER_DETECT() == _D1_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_D1_PMIC_POWER(_D1_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US_EXINT();
            }

            if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(PCB_P0_PMIC_POWER_DETECT() == _P0_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_P0_PMIC_POWER(_P0_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US_EXINT();
            }

            if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(PCB_ADAPTOR_PMIC_POWER_DETECT() == _ADAPTOR_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US_EXINT();
            }

            if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE ucDataIndex = 0;
    BYTE ucSlaveAddr = 0;
    BYTE ucPowerOnCount = 0;

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

    usCurrent = usCurrent;

    if(usVoltage > 2100)
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(enumPowerDirection == _NCP81239_PMIC_SOURCE)
    {
        g_pstPmicNcp81239Data[ucDataIndex].b1CR0BPmicDirection = _NCP81239_PMIC_SOURCE;
    }
    else
    {
        g_pstPmicNcp81239Data[ucDataIndex].b1CR0BPmicDirection = _NCP81239_PMIC_SINK;

        if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
        {
            PCB_D0_PMIC_POWER(_D0_PMIC_POWER_OFF);
        }
        else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
        {
            PCB_D1_PMIC_POWER(_D1_PMIC_POWER_OFF);
        }
        else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
        {
            PCB_P0_PMIC_POWER(_P0_PMIC_POWER_OFF);
        }
        else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
        {
            PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_OFF);
        }

        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }

    // Set VBUS Voltage
    g_pstPmicNcp81239Data[ucDataIndex].ucCR01DacTarget = (BYTE)((usVoltage / 10) + _NCP81239_PMIC_VOLTAGE_OFFSET);

    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(PCB_D0_PMIC_POWER_DETECT() == _D0_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_D0_PMIC_POWER(_D0_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US_EXINT();
            }

            if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(PCB_D1_PMIC_POWER_DETECT() == _D1_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_D1_PMIC_POWER(_D1_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US_EXINT();
            }

            if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(PCB_P0_PMIC_POWER_DETECT() == _P0_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_P0_PMIC_POWER(_P0_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US_EXINT();
            }

            if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(PCB_ADAPTOR_PMIC_POWER_DETECT() == _ADAPTOR_PMIC_POWER_TURN_OFF)
        {
            // Enable PMIC from power saving mode
            PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_ON);

            // Wait for PMIC power ON
            for(ucPowerOnCount = 0; ucPowerOnCount < 200; ucPowerOnCount++)
            {
                DELAY_5US_EXINT();
            }

            if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG00, _NCP81239_SUBADDR_LENGTH, 11, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG00) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
        else
        {
            if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG01, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG01) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_POWER(_D0_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_POWER(_D1_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_POWER(_P0_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_POWER(_D0_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_POWER(_D1_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_POWER(_P0_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    // PCB Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_POWER(_D0_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_POWER(_D1_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_POWER(_P0_PMIC_POWER_OFF);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_POWER(_ADAPTOR_PMIC_POWER_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
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
    g_pstPmicNcp81239Data[ucDataIndex].b1CR04Pfet = enumEn;

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

        // Check Pmic Turn-off or not
        if(PCB_D0_PMIC_POWER_DETECT() == _D0_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
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

        // Check Pmic Turn-off or not
        if(PCB_D1_PMIC_POWER_DETECT() == _D1_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
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

        // Check Pmic Turn-off or not
        if(PCB_P0_PMIC_POWER_DETECT() == _P0_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
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

        // Check Pmic Turn-off or not
        if(PCB_ADAPTOR_PMIC_POWER_DETECT() == _ADAPTOR_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG04, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG04) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
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
    g_pstPmicNcp81239Data[ucDataIndex].b1CR04Pfet = enumEn;

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

        // Check Pmic Turn-off or not
        if(PCB_D0_PMIC_POWER_DETECT() == _D0_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
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

        // Check Pmic Turn-off or not
        if(PCB_D1_PMIC_POWER_DETECT() == _D1_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
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

        // Check Pmic Turn-off or not
        if(PCB_P0_PMIC_POWER_DETECT() == _P0_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
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

        // Check Pmic Turn-off or not
        if(PCB_ADAPTOR_PMIC_POWER_DETECT() == _ADAPTOR_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite_EXINT0(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG04, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG04) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
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
    g_pstPmicNcp81239Data[ucDataIndex].b1CR04Pfet = enumEn;

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

        // Check Pmic Turn-off or not
        if(PCB_D0_PMIC_POWER_DETECT() == _D0_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
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

        // Check Pmic Turn-off or not
        if(PCB_D1_PMIC_POWER_DETECT() == _D1_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
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

        // Check Pmic Turn-off or not
        if(PCB_P0_PMIC_POWER_DETECT() == _P0_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
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

        // Check Pmic Turn-off or not
        if(PCB_ADAPTOR_PMIC_POWER_DETECT() == _ADAPTOR_PMIC_POWER_TURN_OFF)
        {
            return _TYPE_C_PMIC_CONTROL_SUCCESS;
        }
    }

    // Disable Pmic VBUS Discharge
    if(UserCommonUsbTypeCPmicIICWrite_WDINT(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG04, _NCP81239_SUBADDR_LENGTH, 1, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG04) == _FAIL)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
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
            PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
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
            PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
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
            PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
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
            PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
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
            PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
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
            PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
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
            PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
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
            PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
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
            PCB_D0_PMIC_VBUS_SINK_CONTROL(_D0_PMIC_VBUS_SINK_SWITCH_OFF);
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
            PCB_D1_PMIC_VBUS_SINK_CONTROL(_D1_PMIC_VBUS_SINK_SWITCH_OFF);
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
            PCB_P0_PMIC_VBUS_SINK_CONTROL(_P0_PMIC_VBUS_SINK_SWITCH_OFF);
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
            PCB_ADAPTOR_PMIC_VBUS_SINK_CONTROL(_ADAPTOR_PMIC_VBUS_SINK_SWITCH_OFF);
        }
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
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
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicNcp81239ReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239DebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort)
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

    ucResult = UserCommonUsbTypeCPmicIICRead(enumTypeCPcbPort, ucSlaveAddr, _NCP81239_CTRL_REG10, _NCP81239_SUBADDR_LENGTH, 6, (BYTE *)(&g_pstPmicNcp81239Data[ucDataIndex]) + _NCP81239_CTRL_REG10);

    DebugMessageTypeC("Pmic:Embbeded Type-C Port", ucDataIndex);
    DebugMessageTypeC("0.Pmic:VFB Value", g_pstPmicNcp81239Data[ucDataIndex].ucCR10VfbValue);
    DebugMessageTypeC("0.Pmic:Vin Value", g_pstPmicNcp81239Data[ucDataIndex].ucCR11VinValue);
    DebugMessageTypeC("0.Pmic:CS2 Value", g_pstPmicNcp81239Data[ucDataIndex].ucCR12Cs2Value);
    DebugMessageTypeC("0.Pmic:CS1 Value", g_pstPmicNcp81239Data[ucDataIndex].ucCR13Cs1Value);
    DebugMessageTypeC("0.Pmic:Cs Clind Flag", g_pstPmicNcp81239Data[ucDataIndex].b1CR14IntCsClindFlag);
    DebugMessageTypeC("0.Pmic:VBUS OVP Flag", g_pstPmicNcp81239Data[ucDataIndex].b1CR14IntOvpFlag);
    DebugMessageTypeC("0.Pmic:OCP_P Flag", g_pstPmicNcp81239Data[ucDataIndex].b1CR14IntOcpPFlag);
    DebugMessageTypeC("0.Pmic:Power Good Flag", g_pstPmicNcp81239Data[ucDataIndex].b1CR14IntPgIntFlag);
    DebugMessageTypeC("0.Pmic:Thermal Sensor Flag", g_pstPmicNcp81239Data[ucDataIndex].b1CR14IntTsdFlag);
    DebugMessageTypeC("0.Pmic:VBUS UVP Flag", g_pstPmicNcp81239Data[ucDataIndex].b1CR14IntUvpFlag);
    DebugMessageTypeC("0.Pmic:Vchn Flag", g_pstPmicNcp81239Data[ucDataIndex].b1CR14IntVchnFlag);
    DebugMessageTypeC("0.Pmic:IIC ACK Flag", g_pstPmicNcp81239Data[ucDataIndex].b1CR14IntI2cAckFlag);
    DebugMessageTypeC("0.Pmic:Shut Down Flag", g_pstPmicNcp81239Data[ucDataIndex].b1CR15IntShutDownFlag);

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
WORD ExternalDeviceInterfaceTypeCPmicNcp81239ReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicNcp81239ForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort)
{
    BYTE ucPinControl = 0;

    // Set Data Index
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        ucPinControl = _D0_PMIC_POWER_OFF;
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        ucPinControl = _D1_PMIC_POWER_OFF;
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        ucPinControl = _P0_PMIC_POWER_OFF;
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        ucPinControl = _ADAPTOR_PMIC_POWER_OFF;
    }

    // Set Vbus Force Off Type
    UserCommonUsbTypeCPmicSetForceOffControlType(enumTypeCPcbPort, _TYPE_C_PMIC_FORCE_OFF_BY_GPIO);

    // Set PMIC GPIO value
    UserCommonUsbTypeCPmicSetForceOffGpio(enumTypeCPcbPort, _CONFIG_TYPE_GPO_PP, ucPinControl);

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_NCP81239_SUPPORT == _ON))

