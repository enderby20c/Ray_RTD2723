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
// ID Code      : ScalerPower.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_POWER__
#include "ScalerFunctionInclude.h"
#include "Power/ScalerPower.h"
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructPowerIsolation g_stPowerIsolationStatus;
StructPowerClockControl g_stPowerClockControl;


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Xtal Power Control.
// Input Value  : ucOn    --> On/Off Select.
// Output Value : None
//--------------------------------------------------
void ScalerPowerXtalPower(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Xtal has power down
        if(ScalerGetBit(P80_0E_XTAL_CTRL0, _BIT7) == 0x00)
        {
            // Bit4~3 : 00 --> XI/XO Pad Driving to Strong
            ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), 0x00);

            // Power On External Xtal
            ScalerSetBit(P80_0E_XTAL_CTRL0, ~_BIT7, _BIT7);

            // Waiting for xtal stable.
            ScalerTimerDelayXms(6);
        }

        // Bit4~3 : 00 --> XI/XO Pad Driving to weak
        ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
    else
    {
        // Power down External Xtal
        ScalerSetBit(P80_0E_XTAL_CTRL0, ~_BIT7, 0x00);

        // Bit4~3 : 00 --> XI/XO Pad Driving to weak
        ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
}

//--------------------------------------------------
// Description  : Set Clock Control in Fake_PS Mode
// Input Value  : _TRUE => Clock Control
// Output Value : None
//--------------------------------------------------
void ScalerPowerSetFakeSavingClockControl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        SET_POWER_FAKE_SAVING_CLOCK_CONTROL();
    }
    else
    {
        CLR_POWER_FAKE_SAVING_CLOCK_CONTROL();
    }
}

//--------------------------------------------------
// Description  : Check Clock Control or not in Fake_PS Mode
// Input Value  : None
// Output Value : _TRUE => Clock Control
//--------------------------------------------------
bit ScalerPowerCheckFakeSavingClockControl(void)
{
    return GET_POWER_FAKE_SAVING_CLOCK_CONTROL();
}

//--------------------------------------------------
// Description  : Delay Time when Enable Power Domain
// Input Value  : enumPowerOnDelay
// Output Value : None
//--------------------------------------------------
void ScalerPowerDomainEnableDelay(EnumPowerOnDelay enumPowerOnDelay)
{
    // Delay after power-cut disabled to allow full recovery
    switch(enumPowerOnDelay)
    {
        case _POWER_ON_DELAY_NONE:

            // No Delay

            break;

        case _POWER_ON_DELAY_1_MS:

            // Delay 1ms
            DELAY_XUS(1000);

            break;

        case _POWER_ON_DELAY_2_MS:

            // Delay 2ms
            DELAY_XUS(1000);
            DELAY_XUS(1000);

            break;

        case _POWER_ON_DELAY_3_MS:

            // Delay 3ms
            DELAY_XUS(1000);
            DELAY_XUS(1000);
            DELAY_XUS(1000);

            break;

        case _POWER_ON_DELAY_4_MS:

            // Delay 4ms
            DELAY_XUS(1000);
            DELAY_XUS(1000);
            DELAY_XUS(1000);
            DELAY_XUS(1000);

            break;

        case _POWER_ON_DELAY_5_MS:

            // Delay 5ms
            DELAY_XUS(1000);
            DELAY_XUS(1000);
            DELAY_XUS(1000);
            DELAY_XUS(1000);
            DELAY_XUS(1000);

            break;

        default:

            // Delay 5ms
            DELAY_XUS(1000);
            DELAY_XUS(1000);
            DELAY_XUS(1000);
            DELAY_XUS(1000);
            DELAY_XUS(1000);

            break;
    }
}

//--------------------------------------------------
// Description  : LVR Threshold Voltage Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerLvrThresholdVoltage(void)
{
    // Scaler LVR Threshold Voltage Setting
    ScalerSetBit(P40_40_POWER_ON_RESET, ~(_BIT5 | _BIT4), _BIT5);
}
