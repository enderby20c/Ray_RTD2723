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
// ID Code      : Led_Driver_MBLOCK_MBI6353.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include _USER_FUNCTION_INCLUDE

#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_05_MBLOCK_MBI6353)

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

const WORD tMBI6353_INIT_TABLE[] =
{
    0x0360, // CFG01
    0x0800, // CFG02
    0x0019, // CFG03
    0xC8C8, // CFG04
    0x0000, // CFG05
    0x0000, // CFG06
    0x0000, // CFG07
    0x0000, // CFG08
    0x1C68, // CFG09
    0x0002, // CFG10
    0x00FF, // CFG11
    0x181B, // CFG12
    0x0011, // CFG13
    0x0006, // CFG14
    0x0000, // CFG15
    0x001E, // CFG16
};

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
    WORD pusTemp[16];
    memset(pusTemp, 0, sizeof(pusTemp));

    ScalerSpiDimmingInit();

    // Unlock status && ch_mask register
    pusTemp[0] = 0xCC00;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _FALSE);
    // Unlock pwm register
    pusTemp[0] = 0x00AA;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _FALSE);

    // Init CFG01 ~ CFG16 REG
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0000, sizeof(tMBI6353_INIT_TABLE), (BYTE *)tMBI6353_INIT_TABLE, _FALSE);

    // Lock status && ch_mask register
    pusTemp[0] = 0xAA00;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _FALSE);
    // Lock pwm register
    pusTemp[0] = 0x00CC;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _TRUE);
}

//--------------------------------------------------
// Description  : Set Led Driver Pwm Enable/Disable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverPwmEnable(bit bEnable)
{
    WORD pusTemp[1] = {0};

    // Unlock status && ch_mask register
    pusTemp[0] = 0xCC00;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _FALSE);
    // Unlock pwm register
    pusTemp[0] = 0x00AA;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _FALSE);

    if(bEnable == _ENABLE)
    {
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
        // ScalerSpiDimmingSetPwmValueToAllZone( ((((DWORD)_DEVICE_LED_DRIVER_PWM_MAX)*((DWORD)GET_OSD_BACKLIGHT()))/_BACKLIGHT_MAX) );
    }
    else
    {
        UserCommonSpiDimmingSetPwmValueToAllZone(((0 < _DEVICE_LED_DRIVER_PWM_MIN) ? _DEVICE_LED_DRIVER_PWM_MIN : 0));
    }

    // Lock status && ch_mask register
    pusTemp[0] = 0xAA00;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _FALSE);
    // Lock pwm register
    pusTemp[0] = 0x00CC;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _TRUE);
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
    WORD pusTemp[1] = {0};

    // Unlock status && ch_mask register
    pusTemp[0] = 0xCC00;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _FALSE);
    // Unlock pwm register
    pusTemp[0] = 0x00AA;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _FALSE);

    ucBoostGain = ucBoostGain;

    // Lock status && ch_mask register
    pusTemp[0] = 0xAA00;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _FALSE);
    // Lock pwm register
    pusTemp[0] = 0x00CC;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0B00, 2, (BYTE *)pusTemp, _FALSE);
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
    WORD usReadAddr = (pstSpiCmdInfo->usRegStartAddr | _BIT15); // set read flag
    pucCmdBuffer[0] = HIBYTE(pstSpiCmdInfo->usDevAddr);
    pucCmdBuffer[1] = LOBYTE(pstSpiCmdInfo->usDevAddr);
    pucCmdBuffer[2] = HIBYTE(usSpiReadByteNum);
    pucCmdBuffer[3] = LOBYTE(usSpiReadByteNum);
    pucCmdBuffer[4] = HIBYTE(usReadAddr);
    pucCmdBuffer[5] = LOBYTE(usReadAddr);

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
    pucCmdBuffer[0] = HIBYTE(pstSpiCmdInfo->usDevAddr);
    pucCmdBuffer[1] = LOBYTE(pstSpiCmdInfo->usDevAddr);
    pucCmdBuffer[2] = HIBYTE(usPayloadBufferSize);
    pucCmdBuffer[3] = LOBYTE(usPayloadBufferSize);
    pucCmdBuffer[4] = HIBYTE(pstSpiCmdInfo->usRegStartAddr);
    pucCmdBuffer[5] = LOBYTE(pstSpiCmdInfo->usRegStartAddr);

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
#endif

#endif // End of #if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_05_MBLOCK_MBI6353)

