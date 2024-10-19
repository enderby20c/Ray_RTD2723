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
// ID Code      : Led_Driver_MCU_1152_BOE.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include _USER_FUNCTION_INCLUDE

#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_06_MCU_1152_BOE)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DEFAULT_PERIOD_VALUE                       (4095)


//****************************************************************************
// MACROS
//****************************************************************************


//****************************************************************************
// STRUCT
//****************************************************************************


//****************************************************************************
// TYPE / ENUM DEFINITTIONS
//****************************************************************************


//--------------------------------------------------
// DEFINITIONS CHECK
//--------------------------------------------------
#include "User/Device/Header/Led_Driver_Config_Check.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_SPI_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Led Driver Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverInitial(void)
{
    ScalerSpiDimmingInit();

    // Init Backlight to 0
    UserCommonSpiDimmingManualApplyUpdateSync();
    UserCommonSpiDimmingSetPwmValueToAllZone(0);
}

//--------------------------------------------------
// Description  : Set Led Driver Pwm Enable/Disable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverPwmEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
        // ScalerSpiDimmingSetPwmValueToAllZone( ((((DWORD)_DEVICE_LED_DRIVER_PWM_MAX)*((DWORD)GET_OSD_BACKLIGHT()))/_BACKLIGHT_MAX) );
    }
    else
    {
        UserCommonSpiDimmingSetPwmValueToAllZone(((0 < _DEVICE_LED_DRIVER_PWM_MIN) ? _DEVICE_LED_DRIVER_PWM_MIN : 0));
    }
}

#if((_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))
//--------------------------------------------------
// Description  : Adjust Backlight Boost Value
// Input Value  : ucBoostGain: Apply Gain vale = ucBoostGain / 100
//                ucPWMTotalRatio: 0~ 100, for judge cooling time
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverBoostAdjust(BYTE ucBoostGain)
{
    ucBoostGain = ucBoostGain;
}
#endif

//--------------------------------------------------
// Description  : Format LED Driver SPI Read Command Header
// Input Value  : StructSpiCmdInfo --> Spi Command Info (device Address, Start Address of Register Reading...etc)
//                usSpiReadByteNum --> read reg number (SPI0 max is 128 bytes , SPI1 max is 4 bytes)
//                pucCmdBuffer: SPI Read Cmd Header Buffer
// Output Value : SPI Read Cmd Header Byte Number
//--------------------------------------------------
WORD ExternalDeviceInterfaceLedFormatReadCmdHeader(StructSpiCmdInfo *pstSpiCmdInfo, WORD usSpiReadByteNum, BYTE *pucCmdBuffer)
{
    usSpiReadByteNum = usSpiReadByteNum;
    pucCmdBuffer[0] = LOBYTE(pstSpiCmdInfo->usDevAddr);
    pucCmdBuffer[1] = LOBYTE(pstSpiCmdInfo->usRegStartAddr);

    return _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES; // should be 6
}


//--------------------------------------------------
// Description  : Format LED Driver SPI Write Command Buffer
// Input Value  : StructSpiCmdInfo --> Spi Command Info (device Address, Start Address of Register Writing...etc)
//                usPayloadBufferSize --> Spi Command Data Byte Number
//                pucCmdBuffer: SPI Write Cmd Buffer
// Output Value : SPI Write Cmd Header Byte Number
//--------------------------------------------------
WORD ExternalDeviceInterfaceLedFormatWriteCmdHeader(StructSpiCmdInfo *pstSpiCmdInfo, WORD usPayloadBufferSize, BYTE *pucCmdBuffer)
{
    usPayloadBufferSize = usPayloadBufferSize;
    pucCmdBuffer[0] = LOBYTE(pstSpiCmdInfo->usDevAddr);
    pucCmdBuffer[1] = LOBYTE(pstSpiCmdInfo->usRegStartAddr);

    return _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES; // should be 6
}

//--------------------------------------------------
// Description  : Format SPI Command for Digital PWM Value
// Input Value  : origin PWM Target Value (0~4095)
// Output Value : PWM SPI format for LED Driver
//--------------------------------------------------
WORD ExternalDeviceInterfaceLedConvertPwmToSpiFormat(WORD usOrgPwmValue)
{
    return ((WORD)((((((DWORD)(usOrgPwmValue)) * (_LOCAL_DIMMING_PWM2SPI_PWM_GAIN_VALUE + 1)) >> 12) + _LOCAL_DIMMING_PWM2SPI_PWM_MIN) << _LOCAL_DIMMING_PWM2SPI_DATA_LEFT_SHIFT));
}

//--------------------------------------------------
// Description  : Format SPI Command for A-Dimming Value
// Input Value  : origin ADim Target Value (0~4095)
// Output Value : ADim SPI format for LED Driver
//--------------------------------------------------
WORD ExternalDeviceInterfaceLedConvertADimFormat(WORD usOrgADimValue)
{
    return usOrgADimValue;
}

#if(_DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM != 0)
//--------------------------------------------------
// Description  : Calculate && Appending Checksum to SPI Cmd Buffer
// Input Value  : pucSpiCmdBuffer --> SPI Cmd Buffer
//                usCmdDataByteLength --> Cmd Byte Number(Head+Data+Checksum) (Unit: Byte)
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverCalcChecksum(BYTE *pucSpiCmdBuffer, WORD usCmdDataByteLength)
{
    WORD usTmpHeadAndDataCnt = usCmdDataByteLength - _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM;
    WORD usIdx = 0;
    BYTE ucChecksum = 0;
    while(usIdx < usTmpHeadAndDataCnt)
    {
        ucChecksum ^= pucSpiCmdBuffer[usIdx++];
    }
    pucSpiCmdBuffer[usTmpHeadAndDataCnt] = ucChecksum;
}
#endif
#endif

#endif // End of #if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_06_MCU_1152_BOE)

