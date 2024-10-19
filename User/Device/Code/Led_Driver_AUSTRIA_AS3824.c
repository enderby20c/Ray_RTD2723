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
// ID Code      : Led_Driver_AUSTRIA_AS3824.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include _USER_FUNCTION_INCLUDE

#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_04_AUSTRIA_AS3824)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
#define _DEVICE_LED_DRIVER_DEFALUIT_DAC             0x1B0
#elif(_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON)
#define _DEVICE_LED_DRIVER_DEFALUIT_DAC             0x3C0   // 3D/HDR:750mA
#else
#define _DEVICE_LED_DRIVER_DEFALUIT_DAC             0x200   // 2D:250mA
#endif

#if(_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS == _ON)
#define _LOCK_REG_VALUE                             0x0A    // Only Lock register Group2.
#else
#define _LOCK_REG_VALUE                             0xAC    // Lock register Group1 && Group2.
#endif

//--------------------------------------------------
// LED Driver PWM Setting
//--------------------------------------------------
// Set HSYNC PWM CLK out (19.5MHz)
// Use M2PLL as PWM reference clk source , (351MHz/2) = 175.5MHz = 0.0056980056980056980056980056980057us
// Set PWM div = 9 = (0x0008 + 1) , we can get 175.5MHz/(8+1) = 19.5MHz as AS3824 HSYNC clock source
// Since AS3824 Max HSYNC Freq. is 20MHz
#define _DEFAULT_PERIOD_VALUE                       (256)
#define _DEVICE_LED_DRIVER_EXTERNAL_PWM_CNT         (8)

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
    BYTE pucTemp[16];
    memset(pucTemp, 0, sizeof(pucTemp));

#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM != _NO_PWM)
    UserCommonMcuPwmByPassModeSettingFrequency(_DEVICE_LED_DRIVER_EXTERNAL_PWM, _DEVICE_LED_DRIVER_EXTERNAL_PWM_CNT);
#if((_COLOR_IP_LOCAL_DIMMING == _ON) && (_HW_LOCAL_DIMMING_PWM2SPI_ALIGN_PWM_PERIOD_CNT == _ON))
    ScalerColorLDPwmToSpiAlignPwm0PeriodCnt(_ON);
    ScalerColorLDPwmToSpiSetPwm0PeriodCnt(_DEFAULT_PERIOD_VALUE);
    ScalerColorLDPwmToSpiSetPwm0PeriodCntPulseDelay(0);
#endif
#endif

    ScalerSpiDimmingInit();

    // Unlock register Group1 and Group2.
    pucTemp[0] = 0xCA;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, pucTemp, _FALSE);

#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM != _NO_PWM)
    pucTemp[0] = _DEVICE_LED_DRIVER_VALID_BY_VSYNC_EXT_PWM;  // Use External CLK as PWM Clk Source && PWM Registers updated with next VSYNC edge
#else
    pucTemp[0] = _DEVICE_LED_DRIVER_VALID_BY_VSYNC_NO_PWM;  // Use I-OSC(8MHz) as PWM Clk Source && PWM Registers updated with next VSYNC edge
#endif
    pucTemp[1] = LOBYTE(_DEFAULT_PERIOD_VALUE);  // PWM_Period[7:0]
    pucTemp[2] = HIBYTE(_DEFAULT_PERIOD_VALUE);  // PWM_Period[12:8]
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x13, 3, pucTemp, _FALSE);

    pucTemp[0] = 0xFF;  // Enable Output CH1~CH8
    pucTemp[1] = 0xFF;  // Enable Output CH9~CH16
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x01, 2, pucTemp, _FALSE);

    pucTemp[0] = (((WORD)_DEVICE_LED_DRIVER_DEFALUIT_DAC & 0x03FC) >> 2);     // 0xA7;  // IDAC[9:2]
    pucTemp[1] = LOBYTE((WORD)_DEVICE_LED_DRIVER_DEFALUIT_DAC & 0x0003);          // 0x02;  // IDAC[1:0] ,
    pucTemp[2] = 0xFF;  // Enable CH1~CH8 Feedback
    pucTemp[3] = 0xFF;  // Enable CH9~CH16 Feedback
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x0C, 4, pucTemp, _FALSE);


#if((_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON) || (_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON))
    pucTemp[0] = 0x16;  // HDR_MODE Enable, use different Boost DAC setting on each channel
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x67, 1, pucTemp, _FALSE);
    memset(pucTemp, (BYTE)(_DEVICE_LED_DRIVER_DEFALUIT_DAC >> 2), sizeof(pucTemp));
#else
    pucTemp[0] = 0x06;  // HDR_MODE Disable, use global DAC setting
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x67, 1, pucTemp, _FALSE);
    memset(pucTemp, 0, sizeof(pucTemp));
#endif
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x70, 16, pucTemp, _FALSE);

#if((_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON))
    pucTemp[0] = 0x87;  // FAULT_1
    pucTemp[4] = 0x07;  // CURR_CTRL, 3D/HDR DACref = 800mV, Slwe rate:250mV / 2us
#else
    pucTemp[0] = 0x97;  // FAULT_1
    pucTemp[4] = 0x03;  // CURR_CTRL, 2D DACref = 500mV, Slwe rate:250mV / 2us
#endif
    pucTemp[1] = 0x00;  // GPIO_CTRL
    pucTemp[2] = 0x00;  // FB_SEL1
    pucTemp[3] = 0x00;  // FB_SEL2
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x03, 5, pucTemp, _FALSE);

    pucTemp[0] = _LOCK_REG_VALUE;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, pucTemp, _TRUE);
}

//--------------------------------------------------
// Description  : Set Led Driver Pwm Enable/Disable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverPwmEnable(bit bEnable)
{
    BYTE pucTemp[1] = {0};

    // Unlock register Group1 and Group2.
    pucTemp[0] = 0xCA;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, pucTemp, _FALSE);

    if(bEnable == _ENABLE)
    {
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM != _NO_PWM)
        pucTemp[0] = _DEVICE_LED_DRIVER_VALID_BY_VSYNC_EXT_PWM;  // switch to external clk source
        UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, _DEVICE_LED_DRIVER_VALID_ADDR, 1, pucTemp, _FALSE);
#endif
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
        // ScalerSpiDimmingSetPwmValueToAllZone( ((((DWORD)_DEVICE_LED_DRIVER_PWM_MAX)*((DWORD)GET_OSD_BACKLIGHT()))/_BACKLIGHT_MAX) );
    }
    else
    {
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM != _NO_PWM)
        pucTemp[0] = _DEVICE_LED_DRIVER_VALID_BY_VSYNC_NO_PWM;  // switch to internal clk source
        UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, _DEVICE_LED_DRIVER_VALID_ADDR, 1, pucTemp, _FALSE);
#endif
        UserCommonSpiDimmingSetPwmValueToAllZone(((0 < _DEVICE_LED_DRIVER_PWM_MIN) ? _DEVICE_LED_DRIVER_PWM_MIN : 0));
    }

    pucTemp[0] = _LOCK_REG_VALUE;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, pucTemp, _TRUE);

    UserCommonSpiDimmingManualApplyUpdateSync();
}

#if((_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))
//--------------------------------------------------
// Description  : Adjust Backlight Boost Value
// Input Value  : ucBoostGain: Apply Gain vale = ucBoostGain / 100
//                ucPWMTotalRatio: 0~ 100, for judge cooling time
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverBoostAdjust(BYTE ucBoostGain)
{
    BYTE pucTemp[16];
    WORD usBoostValue = 100;

    pucTemp[0] = 0xCA;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, pucTemp, _FALSE);

    usBoostValue = ((DWORD)_DEVICE_LED_DRIVER_DEFALUIT_DAC * ucBoostGain + 50) / 100;

    // HDR_MODE Enable, use different Boost DAC setting on each channel
    memset(pucTemp, (BYTE)(usBoostValue >> 2), sizeof(pucTemp));
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x70, 16, pucTemp, _FALSE);

    pucTemp[0] = _LOCK_REG_VALUE;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, pucTemp, _FALSE);
}
#endif

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : modify region boost gain
// Input Value  : Adim gain array after remap
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverRegionBoostAdjust(WORD *pusBoostGainRemap)
{
    BYTE pucTemp[16] = {0};
    BYTE ucCnt = 0;
    // unlock
    pucTemp[0] = 0xCA;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, pucTemp, _FALSE);

    // Boost value adjust
    for(ucCnt = 0; ucCnt < _LOCAL_DIMMING_TOTAL_REGION; ucCnt++)
    {
        pucTemp[ucCnt] = (BYTE)((((DWORD)_DEVICE_LED_DRIVER_DEFALUIT_DAC * pusBoostGainRemap[ucCnt] + 500) / 1000) >> 2);
    }

    // Write Area Adim Value
    UserCommonColorLocalDimmingSetRegionBoostAdimValue(_LOCAL_DIMMING_AREA_ADIM_ADDR, pucTemp, _FALSE);

    pucTemp[0] = _LOCK_REG_VALUE;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, pucTemp, _FALSE);
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
    pucCmdBuffer[1] = (BYTE)usSpiReadByteNum;
    pucCmdBuffer[2] = (BYTE)(pstSpiCmdInfo->usRegStartAddr | _BIT7); // set read flag

    return _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES; // should be 3
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
    pucCmdBuffer[1] = (BYTE)usPayloadBufferSize;
    pucCmdBuffer[2] = (BYTE)pstSpiCmdInfo->usRegStartAddr;

    return _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES; // should be 3
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
    usOrgADimValue = ((((DWORD)((_DEVICE_LED_DRIVER_DEFALUIT_DAC) >> 2) * usOrgADimValue) + 2047) / 4095);
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
    pucSpiCmdBuffer[1] = 1;
    pucSpiCmdBuffer[2] = _DEVICE_LED_DRIVER_VALID_ADDR;
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _NO_PWM)
    pucSpiCmdBuffer[3] = _DEVICE_LED_DRIVER_VALID_BY_CE_NO_PWM;
#else
    pucSpiCmdBuffer[3] = _DEVICE_LED_DRIVER_VALID_BY_CE_EXT_PWM;
#endif
    return 4;
}

//--------------------------------------------------
// Description  : Format SPI Command for Boardcasting PWM valid by VSYNC
// Input Value  : pucSpiCmdBuffer --> Foramted SPI Command Buffer
// Output Value : length (count by byte) of pucSpiCmdBuffer
//--------------------------------------------------
WORD ExternalDeviceInterfaceLedUpdateSyncbySpiVS(BYTE *pucSpiCmdBuffer)
{
    pucSpiCmdBuffer[0] = _DEVICE_LED_DRIVER_BROADCAST_ID;
    pucSpiCmdBuffer[1] = 1;
    pucSpiCmdBuffer[2] = _DEVICE_LED_DRIVER_VALID_ADDR;
#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _NO_PWM)
    pucSpiCmdBuffer[3] = _DEVICE_LED_DRIVER_VALID_BY_VSYNC_NO_PWM;
#else
    pucSpiCmdBuffer[3] = _DEVICE_LED_DRIVER_VALID_BY_VSYNC_EXT_PWM;
#endif
    return 4;
}
#endif

#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Device LED driver PWM mode switch
// Input Value  : enumDeviceLedDriverMode: MBR/LD Mode
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverModeSwitch(EnumDeviceLedDriverMode enumDeviceLedDriverMode)
{
    BYTE pucTemp[1] = {0};
    // Unlock register Group1 and Group2.
    pucTemp[0] = 0xCA;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, &pucTemp[0], _FALSE);

    switch(enumDeviceLedDriverMode)
    {
        case _DEVICE_LED_DRIVER_MBR_MODE:
            pucTemp[0] = 0x04;
            break;

        case _DEVICE_LED_DRIVER_LD_MODE:
        default:
            pucTemp[0] = 0x00;
            break;
    }
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x13, 1, &pucTemp[0], _FALSE);

    pucTemp[0] = _LOCK_REG_VALUE;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, &pucTemp[0], _TRUE);
}

//--------------------------------------------------
// Description  : LED Driver's A-dimming SPI Format
// Input Value  : pusColorApplyADim --> buffer for Local A-dimming
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceLedDriverAdimSpiFormat(WORD *pusColorApplyADim)
{
    BYTE pucTemp[1];
    pucTemp[0] = 0XCA;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, pucTemp, _FALSE);
#if(_SPI_BOOST_FORMAT_SUPPORT == _ON)
    ScalerSpiDimmingLDUpdateSramADimData(pusColorApplyADim, _TRUE);
#endif
    pucTemp[0] = _LOCK_REG_VALUE;
    UserCommonColorSpiSetCommandRegion(_DEVICE_LED_DRIVER_ALL, 0x36, 1, pucTemp, _FALSE);
}
#endif
#endif
#endif // End of #if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_02_AUSTRIA_AS3824)

