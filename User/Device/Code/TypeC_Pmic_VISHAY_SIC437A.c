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
// ID Code      : TypeC_Pmic_VISHAY_SIC437A.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "../Header/TypeC_Pmic_VISHAY_SIC437A.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_VISHAY_SIC437A_SUPPORT == _ON))

#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
#if(_D0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SIC437A can't support PPS!!!"
#endif

#if(_D0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SIC437A can't support voltage compensation!!!"
#endif
#endif // End of #if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)

#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
#if(_D1_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SIC437A can't support PPS!!!"
#endif

#if(_D1_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SIC437A can't support voltage compensation!!!"
#endif
#endif // End of #if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)

#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
#if(_P0_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SIC437A can't support PPS!!!"
#endif

#if(_P0_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SIC437A can't support voltage compensation!!!"
#endif
#endif // End of #if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)

#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
#if(_ADAPTOR_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SIC437A can't support PPS!!!"
#endif

#if(_ADAPTOR_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SIC437A can't support voltage compensation!!!"
#endif
#endif // End of #if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PMIC Initial Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicVishaySic437aACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    */
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    */
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    usVoltage = usVoltage;
    usCurrent = usCurrent;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    */
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    usVoltage = usVoltage;
    usCurrent = usCurrent;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    */
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerDirection = enumPowerDirection;
    usVoltage = usVoltage;
    usCurrent = usCurrent;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        // Set Target Voltage
        switch(usVoltage)
        {
            case 500:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 900:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1200:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 1500:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);

                break;

            case 2000:

                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_HIGH);
                PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_HIGH);

                break;

            default:

                return _TYPE_C_PMIC_CONTROL_FAIL;

                break;
        }
    }
    */
    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    */
    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    */
    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_D0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_D1_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_P0_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_0(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_1(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_2(_LOW);
        PCB_ADAPTOR_PMIC_VOLTAGE_SELECT_PIN_3(_LOW);
    }
    */
    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumEn = enumEn;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
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
    */
    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumEn = enumEn;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
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
    */
    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumEn = enumEn;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
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
    */
    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumSwitchControl = enumSwitchControl;
    enumPowerDirection = enumPowerDirection;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
    // Switch Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    */
    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumSwitchControl = enumSwitchControl;
    enumPowerDirection = enumPowerDirection;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
    // Switch Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    */
    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumSwitchControl = enumSwitchControl;
    enumPowerDirection = enumPowerDirection;

    // Kernel Power Flow, For Eizo Implement Customized Power Flow Please Keep This Function Empty

    /*
    // Switch Control
    if(enumTypeCPcbPort == _D0_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D0_PMIC_VBUS_SOURCE_CONTROL(_D0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    else if(enumTypeCPcbPort == _D1_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_D1_PMIC_VBUS_SOURCE_CONTROL(_D1_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    else if(enumTypeCPcbPort == _P0_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_P0_PMIC_VBUS_SOURCE_CONTROL(_P0_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    else if(enumTypeCPcbPort == _ADAPTOR_TYPE_C_PORT)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            if(enumSwitchControl == _ON)
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_ON);
            }
            else
            {
                PCB_ADAPTOR_PMIC_VBUS_SOURCE_CONTROL(_ADAPTOR_PMIC_VBUS_SOURCE_SWITCH_OFF);
            }
        }
    }
    */
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
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
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aDebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if(_EMB_TYPE_C_PMIC_DEBUG == _ON)

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC VBUS Current Reading
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : usCurrent : 0 ~ 500 (Unit = 10mA)
//--------------------------------------------------
WORD ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort)
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
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVishaySic437aForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)

/////////////////////////////////////
// EIZO PMIC SIC437A CUSTOMIZED FW //
/////////////////////////////////////
#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C Attached Power Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aAttachProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;

    // For Eizo Implement Customized Attach Power Flow
    // Kernel Call This Funciton When TypeC CC Attach as SRC/SNK

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C Unattached Power Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;

    // For Eizo Implement Customized Unattach Power Flow
    // Kernel Call This Funciton When TypeC CC Unattach from SRC/SNK

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C Unattached Power Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;

    // For Eizo Implement Customized Unattach Power Flow
    // Kernel Call This Funciton When TypeC CC Unattach from SRC/SNK

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C Power Transition Start Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
//                pusSrcAdjustPowerTime : 25 ~ 35 (Unit = ms)
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, WORD usVoltage, WORD usCurrent, WORD *pusSrcAdjustPowerTime)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    usVoltage = usVoltage;
    usCurrent = usCurrent;
    pusSrcAdjustPowerTime = pusSrcAdjustPowerTime;

    // For Eizo Implement Customized Power Transition Flow
    // Kernel Call This Funciton When TypeC PD as SRC and has Sent Accept to SNK During Power Contract

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C Power Transition Ready Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionReadyProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // For Eizo Implement Customized Power Transition Flow
    // Kernel Call This Funciton When TypeC PD as SRC and Vbus is Ready During Power Transition

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C Power Role Swap Start Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;

    // For Eizo Implement Customized PR Swap Flow
    // Kernel Call This Funciton When TypeC PD Recive/Send Accept During PR Swap
    // enumPowerRole = _TYPE_C_POWER_SNK means PD Controller as Sink Receive/Send Accept to PR Swap

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C Power Role Swap Inital Sink Rcv. PS_RDY Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapToSrcProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // For Eizo Implement Customized PR Swap Flow
    // Kernel Call This Funciton When TypeC PD as SNK and Receive PS_RDY from SRC During PR Swap

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C Send/Receive Hard Reset Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;

    // For Eizo Implement Customized Hard Reset Flow
    // Kernel Call This Funciton When TypeC PD Send/Receive Hard Reset
    // Use enumPowerRole to Get PD Contrller is SRC or SNK When Hard Reset Happens

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C Send/Receive Hard Reset Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;

    // For Eizo Implement Customized Hard Reset Flow
    // Kernel Call This Funciton When TypeC PD Send/Receive Hard Reset
    // Use enumPowerRole to Get PD Contrller is SRC or SNK When Hard Reset Happens

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C Send/Receive Hard Reset Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;

    // For Eizo Implement Customized Hard Reset Flow
    // Kernel Call This Funciton When TypeC PD Send/Receive Hard Reset
    // Use enumPowerRole to Get PD Contrller is SRC or SNK When Hard Reset Happens

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C as SRC and Vbus Has Turned Off During Hard Reset Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstVbusOffProc(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // For Eizo Implement Customized Hard Reset Flow
    // Kernel Call This Funciton When TypeC PD as SRC and Vbus Has Turned Off During Hard Reset
    // User Need to Wait 660~1000mS then Turn On Vbus

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C Detect OCP Event Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // For Eizo Implement Customized OCP Flow
    // Kernel Call This Funciton When TypeC PD Detect OCP Event

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C Detect OCP Event Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // For Eizo Implement Customized OCP Flow
    // Kernel Call This Funciton When TypeC PD Detect OCP Event

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C Detect OCP Event Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // For Eizo Implement Customized OCP Flow
    // Kernel Call This Funciton When TypeC PD Detect OCP Event

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C Detect OVP Event Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aOvpProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    enumTypeCPcbPort = enumTypeCPcbPort;

    // For Eizo Implement Customized OVP Flow
    // Kernel Call This Funciton When TypeC PD Detect OVP Event

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Type-C Vbus 5V Power Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus5VReadyProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;

    // For Eizo Implement Customized Vbus 5V Power Flow
    // Kernel Call This Funciton When TypeC Detect Vbus 5V
    // Use enumPowerRole to Get PD Contrller is SRC or SNK When Vbus 5V Detected

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C Vbus 0V Power Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus0VReadyProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumTypeCPcbPort = enumTypeCPcbPort;
    enumPowerRole = enumPowerRole;

    // For Eizo Implement Customized Vbus 0V Power Flow
    // Kernel Call This Funciton When TypeC Detect Vbus 0V
    // Use enumPowerRole to Get PD Contrller is SRC or SNK When Vbus 0V Detected

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && ((_EMB_TYPE_C_0_PMIC_TYPE != _PMIC_NONE) || (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE)) && (_TYPE_C_PMIC_VISHAY_SIC437A_SUPPORT == _ON))

