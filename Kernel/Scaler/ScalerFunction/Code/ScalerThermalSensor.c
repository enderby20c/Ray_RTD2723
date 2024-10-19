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
// ID Code      : ScalerThermalSensor.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_THERMAL_SENSOR__

#include "ScalerFunctionInclude.h"
#include "ThermalSensor/ScalerThermalSensor.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_THERMAL_SENSOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Select Thermal Sensor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerThermalSensorControl(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            // Set Disable Latch Thermal Sensor Output
            ScalerSetBit(P5F_21_TSENSOR_01, ~_BIT6, 0x00);

            // Set Thermal Sensor 29bit Gain, A*alpha
            ScalerSetByte(P5F_22_TSENSOR_02, _FW_THERMAL_SENSOR_GAIN_1);
            ScalerSetByte(P5F_23_TSENSOR_03, _FW_THERMAL_SENSOR_GAIN_2);
            ScalerSetByte(P5F_24_TSENSOR_04, _FW_THERMAL_SENSOR_GAIN_3);
            ScalerSetByte(P5F_25_TSENSOR_05, _FW_THERMAL_SENSOR_GAIN_4);

            // Set Thermal Sensor 22bit Offset, B*signed
            ScalerSetByte(P5F_26_TSENSOR_06, _FW_THERMAL_SENSOR_OFFSET_1);
            ScalerSetByte(P5F_27_TSENSOR_07, _FW_THERMAL_SENSOR_OFFSET_2);
            ScalerSetByte(P5F_28_TSENSOR_08, _FW_THERMAL_SENSOR_OFFSET_3);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Thermal Sensor Temperatuor Value
// Input Value  : None
// Output Value : Temperature Vaule
//--------------------------------------------------
SWORD ScalerThermalSensorGetTempValue(void)
{
    SWORD shThermalCode = 0;

    if((ScalerGetBit(P5F_6E_TW_READ_H, 0x1F) & 0x10) == 0)
    {
        shThermalCode = TO_WORD((ScalerGetByte(P5F_6E_TW_READ_H) & 0x0F), ScalerGetByte(P5F_6F_TW_READ_L));
    }
    else
    {
        shThermalCode = 0x0FFF - TO_WORD((ScalerGetByte(P5F_6E_TW_READ_H) & 0x0F), ScalerGetByte(P5F_6F_TW_READ_L)) - 1;
        shThermalCode = -shThermalCode;
    }

    DebugMessageScaler("Thermal code", shThermalCode);

    return shThermalCode;
}
#endif

