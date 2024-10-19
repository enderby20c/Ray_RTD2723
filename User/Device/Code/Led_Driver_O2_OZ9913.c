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
// ID Code      : Led_Driver_O2_OZ9913.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include _USER_FUNCTION_INCLUDE

#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_01_O2_OZ9913)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Opteration Mode
//--------------------------------------------------
#define _DEFAULT_VSYNC_MODE                         _VSYNC_TRIGGERS_ON_RISING_EDGE
#define _DEFAULT_UPDATE_MODE                        _UPDATE_MODE_BY_CSB
#define _DEFAULT_ADMIM_MODE                         _ADIM_SET_BY_INTERNAL_REG
#define _DEFAULT_PWM_MODE                           _PWM_DETERMINED_BY_INTERNAL_REG
#define _DEFAULT_INDUCTOR_EN                        _BALANCE_WITH_INDUCTOR
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM != _NO_PWM)
#define _DEFAULT_HSYNC_EN                           _HSYNC_ENABLE
#else
#define _DEFAULT_HSYNC_EN                           _HSYNC_DISABLE
#endif
#define _DEFAULT_PWM_EN                             _PWM_NORMAL

//--------------------------------------------------
// Opteration Status
//--------------------------------------------------
#define _DEFAULT_STATUS_MODE                        0x00

//--------------------------------------------------
// PWM period and Period Reset control
//--------------------------------------------------
#define _DEFAULT_HSYNC_DIV                          _HSYNC_FREQ_1_OFF_4
#define _DEFAULT_PERIOD_RST_MODE                    _ON // _PERIOD_RST_AT_VSYNC_EDGE
#define _DEFAULT_PERIOD_VALUE                       _DEVICE_LED_DRIVER_PWM_MAX // Rang : 0 ~ 0x1FFF

//--------------------------------------------------
// Analog diming level control
//--------------------------------------------------
#define _DEFAULT_ADIM_LEVEL_VALUE                   0x3FF // Rang : 0 ~ 0x3FF
#define _DEFAULT_ADJUST_SPEED                       15 // Rang : 0~15, 0.0156m sec/step
#define _DEFAULT_OCP_THRESHOLD                      _OCP_THRESHOLD_2V5

//--------------------------------------------------
// Initial value
//--------------------------------------------------
#define _OPERATION_MODE                             ((_DEFAULT_PWM_EN << 7) | (_DEFAULT_HSYNC_EN << 6) | (_DEFAULT_INDUCTOR_EN << 5) | (_DEFAULT_PWM_MODE << 4) | (_DEFAULT_ADMIM_MODE << 3) | (_DEFAULT_UPDATE_MODE << 2) | (_DEFAULT_VSYNC_MODE))
#define _OPERATION_STATUS                           (_DEFAULT_STATUS_MODE)
#define _PERIOD_CONTROL                             (_DEFAULT_PERIOD_VALUE & 0x00FF)
#define _PERIOD_CONTROL2                            ((_DEFAULT_HSYNC_DIV << 6) | (_DEFAULT_PERIOD_RST_MODE << 5) | ((_DEFAULT_PERIOD_VALUE & 0x1F00) >> 8))
#define _DIMMING_LEVEL_CONTROL                      (_DEFAULT_ADIM_LEVEL_VALUE & 0x00FF)
#define _DIMMING_LEVEL_CONTROL2                     ((_DEFAULT_ADJUST_SPEED << 4) | (_DEFAULT_OCP_THRESHOLD << 2) | ((_DEFAULT_ADIM_LEVEL_VALUE & 0x300) >> 8))

//--------------------------------------------------
// Setting
//--------------------------------------------------
#define _REG_ADDRESS_OPERATION_MODE                 0x01

#if(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)
#define _DEVICE_LED_DRIVER_DEFALUIT_ADIM            0x1C2
#else
#define _DEVICE_LED_DRIVER_DEFALUIT_ADIM            0x2FE
#endif

//--------------------------------------------------
// LED Driver PWM Setting
//--------------------------------------------------
// Set HSYNC PWM CLK out (8MHz)
// Use M2PLL as PWM reference clk source , (351MHz/2) = 175.5MHz = 0.0056980056980056980056980056980057us
// Set PWM div = 22 = (0x0015 + 1) , we can get 175.5MHz/(21+1) = 7.97MHz as OZ9913 HSYNC clock source
// Since OZ9913 Max HSYNC Freq. is 8MHz
#define _DEVICE_LED_DRIVER_EXTERNAL_PWM_CNT         (21)


//--------------------------------------------------
// DEFINITIONS CHECK
//--------------------------------------------------
#include "User/Device/Header/Led_Driver_Config_Check.h"


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _VSYNC_TRIGGERS_ON_RISING_EDGE = 0x01,
    _VSYNC_TRIGGERS_ON_FALLING_EDGE,
    _VSYNC_TRIGGERS_ON_BOTH_EDGE,
} EnumOperationModeVsyncMode;

typedef enum
{
    _UPDATE_MODE_BY_CSB = 0,
    _UPDATE_MODE_BY_VSYNC,
} EnumOperationModeUpdateMode;

typedef enum
{
    _ADIM_SET_BY_ADIM_PIN = 0,
    _ADIM_SET_BY_INTERNAL_REG,
} EnumOperationAdimMode;

typedef enum
{
    _PWM_DETERMINED_BY_INTERNAL_REG = 0,
    _PWM_DETERMINED_BY_VSYNC,
} EnumOperationPwmMode;

typedef enum
{
    _BALANCE_WITH_INDUCTOR = 0,
    _BALANCE_WITHOUT_INDUCTOR,
} EnumOperationInductorEn;

typedef enum
{
    _HSYNC_DISABLE = 0,
    _HSYNC_ENABLE,
} EnumOperationHsyncEn;

typedef enum
{
    _PWM_OFF = 0,
    _PWM_NORMAL,
} EnumOperationPwmEn;

typedef enum
{
    _HSYNC_FREQ_1_OFF_4 = 0,
    _HSYNC_FREQ_1_OFF_8,
    _HSYNC_FREQ_1_OFF_16,
    _HSYNC_FREQ_1_OFF_32,
} EnumOperationHsyncDiv;

typedef enum
{
    _PERIOD_RST_AT_VSYNC_EDGE = 0,
} EnumOperationPeriodRst;

typedef enum
{
    _OCP_THRESHOLD_1V = 0,
    _OCP_THRESHOLD_1V5,
    _OCP_THRESHOLD_2V,
    _OCP_THRESHOLD_2V5,
} EnumOCPThreshold;

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
    BYTE pucTemp[6] =
    {
        _OPERATION_MODE,        // 0x89,
        _OPERATION_STATUS,      // 0x00,
        _PERIOD_CONTROL,        // 0xEE,
        _PERIOD_CONTROL2,       // 0xE6,
        _DIMMING_LEVEL_CONTROL, // 0x00,
        _DIMMING_LEVEL_CONTROL2,// 0x00,
    };
    pucTemp[4] = LOBYTE((WORD)_DEVICE_LED_DRIVER_DEFALUIT_ADIM & 0xFF);
    pucTemp[5] = ((0x3F) << 2) + ((WORD)_DEVICE_LED_DRIVER_DEFALUIT_ADIM >> 8);

#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM != _NO_PWM)
    UserCommonMcuPwmByPassModeSettingFrequency(_DEVICE_LED_DRIVER_EXTERNAL_PWM, _DEVICE_LED_DRIVER_EXTERNAL_PWM_CNT);
#if((_COLOR_IP_LOCAL_DIMMING == _ON) && (_HW_LOCAL_DIMMING_PWM2SPI_ALIGN_PWM_PERIOD_CNT == _ON))
    ScalerColorLDPwmToSpiAlignPwm0PeriodCnt(_ON);
    ScalerColorLDPwmToSpiSetPwm0PeriodCnt(_DEFAULT_PERIOD_VALUE);
    ScalerColorLDPwmToSpiSetPwm0PeriodCntPulseDelay(0);
#endif
#endif

    ScalerSpiDimmingInit();

    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, _REG_ADDRESS_OPERATION_MODE, 6, pucTemp, _TRUE);
}

//--------------------------------------------------
// Description  : Set Led Driver Pwm Enable/Disable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverPwmEnable(bit bEnable)
{
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM != _NO_PWM)
    BYTE pucTemp[1] = {0};
#endif

    if(bEnable == _ENABLE)
    {
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM != _NO_PWM)
        pucTemp[0] = _OPERATION_MODE;  // switch to external clk source
        UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, _REG_ADDRESS_OPERATION_MODE, 1, pucTemp, _FALSE);
#endif
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
        // ScalerSpiDimmingSetPwmValueToAllZone( ((((DWORD)_DEVICE_LED_DRIVER_PWM_MAX)*((DWORD)GET_OSD_BACKLIGHT()))/_BACKLIGHT_MAX) );
    }
    else
    {
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM != _NO_PWM)
        pucTemp[0] = _OPERATION_MODE & (~_BIT6);  // switch to internal clk source
        UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, _REG_ADDRESS_OPERATION_MODE, 1, pucTemp, _FALSE);
#endif
        UserCommonSpiDimmingSetPwmValueToAllZone(((0 < _DEVICE_LED_DRIVER_PWM_MIN) ? _DEVICE_LED_DRIVER_PWM_MIN : 0));
    }
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
    UserCommonSpiDimmingManualApplyUpdateSync();
#endif
}

#if((_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))
//--------------------------------------------------
// Description  : Adjust Backlight Boost Value
// Input Value  : Boost Gain, Apply Gain vale = Boost Gain / 100
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverBoostAdjust(BYTE ucBoostGain)
{
    WORD usBoostValue = 0;
    BYTE pucTemp[4];

    usBoostValue = ((DWORD)_DEVICE_LED_DRIVER_DEFALUIT_ADIM * ucBoostGain + 50) / 100;
    pucTemp[0] = LOBYTE((WORD)usBoostValue & 0xFF);
    pucTemp[1] = ((0x3F) << 2) + ((WORD)usBoostValue >> 8);
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x05, 2, pucTemp, _FALSE);
}
#endif

//--------------------------------------------------
// Description  : Format LED Driver SPI Read Command Header
// Input Value  : StructSpiCmdInfo --> Spi Command Info (device Address, Start Address of Register Reading...etc)
//                usSpiReadByteNum --> read reg number (SPI0 max is 128 bytes , SPI1 max is 4 bytes)
//                pucCmdBuffer: SPI Read Cmd Buffer
// Output Value : SPI Read Cmd Header Byte Number
//--------------------------------------------------
WORD ExternalDeviceInterfaceLedFormatReadCmdHeader(StructSpiCmdInfo *pstSpiCmdInfo, WORD usSpiReadByteNum, BYTE *pucCmdBuffer)
{
    pucCmdBuffer[0] = (BYTE)pstSpiCmdInfo->usDevAddr;
    usSpiReadByteNum = usSpiReadByteNum;
    // O2 series Driver
    pucCmdBuffer[0] |= _BIT0; // set read flag
    pucCmdBuffer[1] = (BYTE)pstSpiCmdInfo->usRegStartAddr;

    return _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES; // should be 2
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
    pucCmdBuffer[0] = (BYTE)pstSpiCmdInfo->usDevAddr;
    usPayloadBufferSize = usPayloadBufferSize;
    pucCmdBuffer[1] = (BYTE)pstSpiCmdInfo->usRegStartAddr;

    return _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES; // should be 2
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

#if(_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS == _ON)
//--------------------------------------------------
// Description  : Format SPI Command for Digital PWM Value
// Input Value  : pucSpiCmdBuffer --> Foramted SPI Command Buffer
// Output Value : length (count by byte) of pucSpiCmdBuffer (not count dummy bytes)
//--------------------------------------------------
WORD ExternalDeviceInterfaceLedUpdateSyncbySpiCE(BYTE *pucSpiCmdBuffer)
{
    pucSpiCmdBuffer[0] = _DEVICE_LED_DRIVER_BROADCAST_ID;
    pucSpiCmdBuffer[1] = _DEVICE_LED_DRIVER_VALID_ADDR;
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _NO_PWM)
    pucSpiCmdBuffer[2] = _DEVICE_LED_DRIVER_VALID_BY_CE_NO_PWM;
#else
    pucSpiCmdBuffer[2] = _DEVICE_LED_DRIVER_VALID_BY_CE_EXT_PWM;
#endif
    return 3;
}

//--------------------------------------------------
// Description  : Format SPI Command for Boardcasting PWM valid by VSYNC
// Input Value  : pucSpiCmdBuffer --> Foramted SPI Command Buffer
// Output Value : length (count by byte) of pucSpiCmdBuffer
//--------------------------------------------------
WORD ExternalDeviceInterfaceLedUpdateSyncbySpiVS(BYTE *pucSpiCmdBuffer)
{
    pucSpiCmdBuffer[0] = _DEVICE_LED_DRIVER_BROADCAST_ID;
    pucSpiCmdBuffer[1] = _DEVICE_LED_DRIVER_VALID_ADDR;
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _NO_PWM)
    pucSpiCmdBuffer[2] = _DEVICE_LED_DRIVER_VALID_BY_VSYNC_NO_PWM;
#else
    pucSpiCmdBuffer[2] = _DEVICE_LED_DRIVER_VALID_BY_VSYNC_EXT_PWM;
#endif
    return 3;
}
#endif
#endif
#endif // End of #if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_01_O2_OZ9913)

