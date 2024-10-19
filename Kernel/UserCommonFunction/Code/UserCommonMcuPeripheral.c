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
// ID Code      : UserCommonMcuPeripheral.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "McuPeripheral/UserCommonMcuPeripheral.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Switch DDC pin to GPIO or viceversa
// Input Value  : ucPinType --> _DDC0_SWITCH_GPIO / _DDC0_SWITCH_DDC, etc.
// Output Value : None
//--------------------------------------------------
void UserCommonPinshareGpioDdcPinSwitch(BYTE ucPinType)
{
    ScalerPinshareGpioDdcPinSwitch(ucPinType);
}

//--------------------------------------------------
// Description  : Adjust pin share config
// Input Value  : enumConfigPin  --> Pin num
//                enumConfigType --> Pin type(GPIO/PWM..Etc.)
// Output Value : None
//--------------------------------------------------
void UserCommonPinshareAdjustConfig(EnumConfigPin enumConfigPin, EnumPinConfigType enumConfigType)
{
    ScalerPinshareAdjustConfig(enumConfigPin, enumConfigType);
}

//--------------------------------------------------
// Description  : Adjust Pad Driven Current config
// Input Value  : enumConfigPin  --> Pin num
//                enumPadDrivingCurrentType --> High/Low Driven Current
// Output Value : None
//--------------------------------------------------
void UserCommonPinsharePadDrivenConfig(EnumConfigPin enumConfigPin, EnumPadDrivingCurrentType enumPadDrivingCurrentType)
{
    ScalerPinsharePadDrivenConfig(enumConfigPin, enumPadDrivingCurrentType);
}

#if(_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get ADC Channel Output Value (Not IRQ)
// Input Value  : enumChannel : 0 (_TYPE_C_0_VMON) / 1 (_TYPE_C_1_VMON) / 2 (_TYPE_C_LOC_PW)
// Output Value : None
//--------------------------------------------------
WORD UserCommonPinshareTypeCAdcGetAdcIdealData(EnumTypeC10BitAdcChannel enumChannel)
{
    return ScalerPinshareTypeCAdcGetAdcIdealData(enumChannel);
}
#endif

#if(_SPI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : SPI Data I/O
// Input Value  : enumSpiInterface  --> SPI Interface(0 or 1)
//                ucWritelength     --> SPI Write Data Length
//                ucReadlength      --> SPI Read Data Length(must <= _SPI1_RX_BUFFER_MAX_LENGTH)
//                pucWriteArray     --> SPI Write Data Buffer
//                pucReadArray      --> SPI Read Data Buffer
// Output Value : SPI0 Data I/O Status
//--------------------------------------------------
bit UserCommonSpiDataIo(EnumSpiInterface enumSpiInterface, WORD usWritelength, BYTE ucReadlength, BYTE *pucWriteArray, BYTE *pucReadArray)
{
    return ScalerSpiDataIo(enumSpiInterface, usWritelength, ucReadlength, pucWriteArray, pucReadArray);
}

//--------------------------------------------------
// Description  : Get Dp MST Capable Port
// Input Value  : None
// Output Value : _DP_MST_RX0 or _DP_MST_RX1
//--------------------------------------------------
void UserCommonSpiCSPinSel(EnumSpiInterface enumSpiInterface, EnumSpiCsSel enumSpiCsSel)
{
#if(_SPI0_SUPPORT == _ON)
    if(enumSpiInterface == _SPI_INTERFACE_0)
    {
        ScalerSpi0CSPinSel(enumSpiCsSel);
    }
#endif
#if(_SPI1_SUPPORT == _ON)
    if(enumSpiInterface == _SPI_INTERFACE_1)
    {
        ScalerSpi1CSPinSel(enumSpiCsSel);
    }
#endif
#if(_SPI2_SUPPORT == _ON)
    if(enumSpiInterface == _SPI_INTERFACE_2)
    {
        ScalerSpi2CSPinSel(enumSpiCsSel);
    }
#endif
}

#if(_SPI0_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonSpiData(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf)
{
    ScalerSpiData(bReadWrite, usDataLength, pucDataBuf);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonSpiSPIDataCeForceLow(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf)
{
    ScalerSpiSPIDataCeForceLow(bReadWrite, usDataLength, pucDataBuf);
}
#endif

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Manual Trigger PwmToSpi Update Sync Signal (Update Sync Source must set to manual mode(_UPD_SYNC_BY_MANUAL),this function can work when PwmToSpi IP disabled)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonSpiDimmingManualApplyUpdateSync(void)
{
    ScalerSpiDimmingToggleUpdateSync();
}

//--------------------------------------------------
// Description  : set PwmValue for all zones of all Devices
// Input Value  : usPwmValue --> PwmValue for all zones of all Devices
// Output Value : None
//--------------------------------------------------
bit UserCommonSpiDimmingSetPwmValueToAllZone(WORD usPwmValue)
{
    return ScalerSpiDimmingSetPwmValueToAllZone(usPwmValue);
}
#endif // End of #if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)

#endif // End of #if(_SPI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Tcon0 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon0Enable(bit bEnable)
{
    ScalerTcon0Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon0 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon0Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon0Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon0 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon0InvEnable(bit bEnable)
{
    ScalerTcon0InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon1 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon1Enable(bit bEnable)
{
    ScalerTcon1Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon1 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon1Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon1Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon1 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon1InvEnable(bit bEnable)
{
    ScalerTcon1InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon2 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon2Enable(bit bEnable)
{
    ScalerTcon2Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon2 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon2Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon2Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon2 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon2InvEnable(bit bEnable)
{
    ScalerTcon2InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon3 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon3Enable(bit bEnable)
{
    ScalerTcon3Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon3 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon3Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon3Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon3 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon3InvEnable(bit bEnable)
{
    ScalerTcon3InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon4 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon4Enable(bit bEnable)
{
    ScalerTcon4Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon4 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon4Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon4Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon4 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon4InvEnable(bit bEnable)
{
    ScalerTcon4InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon5 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon5Enable(bit bEnable)
{
    ScalerTcon5Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon5 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon5Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon5Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon5 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon5InvEnable(bit bEnable)
{
    ScalerTcon5InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon6 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon6Enable(bit bEnable)
{
    ScalerTcon6Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon6 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon6Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon6Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon6 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon6InvEnable(bit bEnable)
{
    ScalerTcon6InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon7 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon7Enable(bit bEnable)
{
    ScalerTcon7Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon7 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon7Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon7Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon7 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon7InvEnable(bit bEnable)
{
    ScalerTcon7InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon8 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon8Enable(bit bEnable)
{
    ScalerTcon8Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon8 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon8Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon8Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon8 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon8InvEnable(bit bEnable)
{
    ScalerTcon8InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon9 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon9Enable(bit bEnable)
{
    ScalerTcon9Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon9 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon9Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon9Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon9 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon9InvEnable(bit bEnable)
{
    ScalerTcon9InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon10 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon10Enable(bit bEnable)
{
    ScalerTcon10Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon10 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon10Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon10Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon10 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon10InvEnable(bit bEnable)
{
    ScalerTcon10InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon11 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon11Enable(bit bEnable)
{
    ScalerTcon11Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon11 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon11Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon11Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon11 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon11InvEnable(bit bEnable)
{
    ScalerTcon11InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon12 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon12Enable(bit bEnable)
{
    ScalerTcon12Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon12 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon12Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon12Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon12 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon12InvEnable(bit bEnable)
{
    ScalerTcon12InvEnable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon13 local enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon13Enable(bit bEnable)
{
    ScalerTcon13Enable(bEnable);
}


//--------------------------------------------------
// Description  : Set Tcon13 Region
// Input Value  : usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTcon13Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTcon13Adjust(usHstart, usHend, usVstart, usVend);
}


//--------------------------------------------------
// Description  : Set Tcon13 invert enable
// Input Value  : bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTcon13InvEnable(bit bEnable)
{
    ScalerTcon13InvEnable(bEnable);
}

//--------------------------------------------------
// Description  : Set Specified Tcon local enable
// Input Value  : ucTconIndex --> Specified Tcon Index
//                bEnable --> enable
// Output Value : None
//--------------------------------------------------
void UserCommonTconEnableByIndex(BYTE ucTconIndex, bit bEnable)
{
    ScalerTconEnableByIndex(ucTconIndex, bEnable);
}

//--------------------------------------------------
// Description  : Set Specified Tcon Region
// Input Value  : ucTconIndex --> Specified Tcon Index
//                usHstart --> Horizon start
//                usHend --> Horizon end
//                usVstart --> Vertical start
//                usVend --> Vertical end
// Output Value : None
//--------------------------------------------------
void UserCommonTconAdjustByIndex(BYTE ucTconIndex, WORD usHstart, WORD usHend, WORD usVstart, WORD usVend)
{
    ScalerTconAdjustByIndex(ucTconIndex, usHstart, usHend, usVstart, usVend);
}

//--------------------------------------------------
// Description  : Set Tcon logical operation enable
// Input Value  : enumTconLogicalOpSet --> Specified Tcon Index
//                enumTconLogicalOp --> Specified Tcon Operation
//                bit --> bEnable
// Output Value : None
//--------------------------------------------------
void UserCommonTconLogicalOpEnable(EnumTconLogicalOpSet enumTconLogicalOpSet, EnumTconLogicalOp enumTconLogicalOp, bit bEnable)
{
    ScalerTconLogicalOpEnable(enumTconLogicalOpSet, enumTconLogicalOp, bEnable);
}

#if(_PWM_RST_SIGNAL_SEL == _TCON)
//--------------------------------------------------
// Description  : PWM reset by TCON,adjust TCON
// Input Value  : usVstart --> TCON phase shift
// Output Value : None
//--------------------------------------------------
void UserCommonTconAdjust(BYTE ucArea)
{
    ScalerTconAdjust(ucArea);
}
#endif


#if(_PWM_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PWM Clock Frequency.
// Input Value  : ucPwmType --> _BACKLIGHT_PWM/_AUDIO_VOLUME...
//                bStatus --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonMcuPwmAdjustResetByDvs(BYTE ucPwmType, bit bStatus)
{
    ScalerMcuPwmAdjustResetByDvs(ucPwmType, bStatus);
}

//--------------------------------------------------
// Description  : PWM Clock Frequency.
// Input Value  : ucPwmType --> _BACKLIGHT_PWM/_AUDIO_VOLUME...
//                ucFrequency --> Frequency
// Output Value : None
//--------------------------------------------------
bit UserCommonMcuPwmAdjustFrequency(BYTE ucPwmType, WORD usFrequency)
{
    return ScalerMcuPwmAdjustFrequency(ucPwmType, usFrequency);
}

#if(_PWM_BYPASS_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PWM Clock ByPassMode Frequency Setting.
// Input Value  : ucPwmType --> PWM channel for Led Driver external PWM
//                usTotalcont --> usTotalcont : align value of FW3 define , (usTotalcont * 2) + 1 : fit the HW of FW4
// Output Value : None
//--------------------------------------------------
void UserCommonMcuPwmByPassModeSettingFrequency(BYTE ucPwmType, WORD usTotalcont)
{
    ScalerMcuPwmByPassModeSettingFrequency(ucPwmType, (usTotalcont * 2) + 1);
}
#endif
#endif

#if(_UART_SUPPORT == _ON)
#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
//--------------------------------------------------
// Description  : Set Ext UART0 Target Baud Rate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonMcuUartExt0UpdateBaudRate(void)
{
    EnumClkSel enumClkSel = ScalerMcuUartGetUartClkSource();

    if(enumClkSel == _IOSC_CLK)
    {
        ScalerMcuUartExt0SetBaudRate(enumClkSel, UserInterfaceUartExt0GetPowerSavingBaudRate());
    }
    else
    {
        ScalerMcuUartExt0SetBaudRate(enumClkSel, UserInterfaceUartExt0GetPowerNormalBaudRate());
    }
}

//--------------------------------------------------
// Description  : Check UART0 serial receive status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonMcuUartExt0CheckReceiveStatus(void)
{
    return ScalerMcuUartExt0CheckReceiveStatus();
}

//--------------------------------------------------
// Description  : Check Ext UART0 Int ID
// Input Value  : None
// Output Value : Ext Uart Int ID
//--------------------------------------------------
EnumMcuExtUartIntID UserCommonMcuUartExt0CheckIntID(void)
{
    return ScalerMcuUartExt0CheckIntID();
}

//--------------------------------------------------
// Description  : Clear UART2 serial transmit status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonMcuUartExt0GetByte(void)
{
    return ScalerMcuUartExt0GetByte();
}

//--------------------------------------------------
// Description  : Write data to the selected device by UART2
// Input Value  : ucValue ---> Data to be send
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit UserCommonMcuUartExt0SetByte(BYTE ucValue)
{
    return ScalerMcuUartExt0SetByte(ucValue);
}
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
//--------------------------------------------------
// Description  : Set Ext UART1 Target Baud Rate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonMcuUartExt1UpdateBaudRate(void)
{
    EnumClkSel enumClkSel = ScalerMcuUartGetUartClkSource();

    if(enumClkSel == _IOSC_CLK)
    {
        ScalerMcuUartExt1SetBaudRate(enumClkSel, UserInterfaceUartExt1GetPowerSavingBaudRate());
    }
    else
    {
        ScalerMcuUartExt1SetBaudRate(enumClkSel, UserInterfaceUartExt1GetPowerNormalBaudRate());
    }
}

//--------------------------------------------------
// Description  : Check UART1 serial receive status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonMcuUartExt1CheckReceiveStatus(void)
{
    return ScalerMcuUartExt1CheckReceiveStatus();
}

//--------------------------------------------------
// Description  : Check Ext UART1 Int ID
// Input Value  : None
// Output Value : Ext Uart Int ID
//--------------------------------------------------
EnumMcuExtUartIntID UserCommonMcuUartExt1CheckIntID(void)
{
    return ScalerMcuUartExt1CheckIntID();
}

//--------------------------------------------------
// Description  : Clear UART2 serial transmit status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonMcuUartExt1GetByte(void)
{
    return ScalerMcuUartExt1GetByte();
}

//--------------------------------------------------
// Description  : Write data to the selected device by UART2
// Input Value  : ucValue ---> Data to be send
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit UserCommonMcuUartExt1SetByte(BYTE ucValue)
{
    return ScalerMcuUartExt1SetByte(ucValue);
}
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
//--------------------------------------------------
// Description  : Set Ext UART2 Target Baud Rate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonMcuUartExt2UpdateBaudRate(void)
{
    EnumClkSel enumClkSel = ScalerMcuUartGetUartClkSource();

    if(enumClkSel == _IOSC_CLK)
    {
        ScalerMcuUartExt2SetBaudRate(enumClkSel, UserInterfaceUartExt2GetPowerSavingBaudRate());
    }
    else
    {
        ScalerMcuUartExt2SetBaudRate(enumClkSel, UserInterfaceUartExt2GetPowerNormalBaudRate());
    }
}

//--------------------------------------------------
// Description  : Check UART2 serial receive status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserCommonMcuUartExt2CheckReceiveStatus(void)
{
    return ScalerMcuUartExt2CheckReceiveStatus();
}

//--------------------------------------------------
// Description  : Check Ext UART2 Int ID
// Input Value  : None
// Output Value : Ext Uart Int ID
//--------------------------------------------------
EnumMcuExtUartIntID UserCommonMcuUartExt2CheckIntID(void)
{
    return ScalerMcuUartExt2CheckIntID();
}

//--------------------------------------------------
// Description  : Clear UART2 serial transmit status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserCommonMcuUartExt2GetByte(void)
{
    return ScalerMcuUartExt2GetByte();
}

//--------------------------------------------------
// Description  : Write data to the selected device by UART2
// Input Value  : ucValue ---> Data to be send
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit UserCommonMcuUartExt2SetByte(BYTE ucValue)
{
    return ScalerMcuUartExt2SetByte(ucValue);
}
#endif
#endif // End of #if(_UART_SUPPORT == _ON)

#if(_EMBEDDED_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Force nack DDC channel
// Input Value  : bSelect --> _ON: force nack
// Output Value : NONE
//--------------------------------------------------
void UserCommonMcuSetForceNack(EnumInputPort enumInputPort, bit bSelect)
{
    ScalerMcuDdcSetForceNack(enumInputPort, bSelect);
}
#endif

//--------------------------------------------------
// Description  : Get Slave Address of DDCCI0
// Input Value  : None
// Output Value : DDCCI0 Slave Address
//--------------------------------------------------
BYTE UserCommonMcuGetDDCCI0SlaveAddr(void)
{
    return GET_DDCCI0_SLAVE_ADDRESS();
}

//--------------------------------------------------
// Description  : Set Slave Address of DDCCI0
// Input Value  : ucSlaveAddr --> Slave Addr to Set
// Output Value : None
//--------------------------------------------------
void UserCommonMcuSetDDCCI0SlaveAddr(BYTE ucSlaveAddr)
{
    SET_DDCCI0_SLAVE_ADDRESS(ucSlaveAddr);
}

//--------------------------------------------------
// Description  : Get Sub Address of DDCCI0
// Input Value  : None
// Output Value : DDCCI0 Sub Address
//--------------------------------------------------
BYTE UserCommonMcuGetDDCCI0SubAddr(void)
{
    return GET_DDCCI0_SUBADDRESS();
}


//--------------------------------------------------
// Description  : Get Data In of DDCCI0
// Input Value  : None
// Output Value : DDCCI0 Data In
//--------------------------------------------------
BYTE UserCommonMcuGetDDCCI0DataIn(void)
{
    return GET_DDCCI0_DATA_IN();
}

//--------------------------------------------------
// Description  : Set Data Out of DDCCI0
// Input Value  : ucDataOut --> Data Out to Set
// Output Value : None
//--------------------------------------------------
void UserCommonMcuSetDDCCI0DataOut(BYTE ucDataOut)
{
    SET_DDCCI0_DATA_OUT(ucDataOut);
}

//--------------------------------------------------
// Description  : Get Irq Status of DDCCI0
// Input Value  : None
// Output Value : DDCCI0IrqStatus
//--------------------------------------------------
BYTE UserCommonMcuGetDDCCI0IrqStatus(void)
{
    return GET_DDCCI0_IRQ_STATUS();
}

//--------------------------------------------------
// Description  : Set Irq Status of DDCCI0
// Input Value  : ucStatus --> DDCCI0 Irq Status to Set
// Output Value : None
//--------------------------------------------------
void UserCommonMcuSetDDCCI0IrqStatus(BYTE ucStatus)
{
    SET_DDCCI0_IRQ_STATUS(ucStatus);
}

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//--------------------------------------------------
// Description  : Set HW IR Table
// Input Value  : User Table
// Output Value : None
//--------------------------------------------------
void UserCommonIRHWModeDecoder(BYTE *pucIRTableArray, BYTE ucBankNum)
{
    ScalerIRHWModeDecoder(pucIRTableArray, ucBankNum);
}

//--------------------------------------------------
// Description  : Read the IR raw data in fifo
// Input Value  : None
// Output Value : Data ready or not
//--------------------------------------------------
bit UserCommonIRHWModeGetData(BYTE *pucBuffer)
{
    return ScalerIRHWModeGetData(pucBuffer);
}

//--------------------------------------------------
// Description  : Get NEC IR Status
// Input Value  : None
// Output Value : _NEC_IR_REPEAT or _NEC_IR_DATA
//--------------------------------------------------
EnumNECIRStatus UserCommonIRHWModeGetNECIRStatus(void)
{
    return ScalerIRHWModeGetNECIRStatus();
}
#endif

#if(_HW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum)
{
    return ScalerMcuHwIICRead(ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucReadArray, ucHwIICPinNum);
}
#endif

#if(_TYPEC_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by Type-C IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonMcuTypecIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum)
{
    return ScalerMcuTypecIICRead(ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucReadArray, ucHwIICPinNum);
}
#endif

#if(_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Read data from the selected device by Software IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    return ScalerMcuIICRead(ucSlaveAddr, ucSubAddrLength, usSubAddr, usLength, pucReadArray);
}
#endif

//--------------------------------------------------
// Description  : User Common Adjust Ddc Debounce
// Input Value  : enumInputPort --> Input Port
//                enumDdcDbnSelMode --> Normal Mode/Speed up Mode
// Output Value : None
//--------------------------------------------------
void UserCommonMcuDdcDebounceAdjust(EnumInputPort enumInputPort, EnumDdcDbnSelMode enumDdcDbnSelMode)
{
    ScalerMcuDdcDebounceSelByPort(enumInputPort, enumDdcDbnSelMode);
}

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
//--------------------------------------------------
// Description  : Check Display Mode for OGC/OCC Support on
// Input Value  : NONE
// Output Value : Result
//--------------------------------------------------
bit UserCommonMcuDdcciColorCalibrationCheckDisplayMode(void)
{
    return ScalerMcuDdcciColorCalibrationCheckDisplayMode();
}
#endif

#if(_SPI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Force Control SPI CS/CLK/MOSI Pins State
// Input Value  : enumSpiInterface  --> SPI Interface(0/1/2)
//                enumPowerTarget   --> Power Status(_POWER_OFF/_POWER_ON)
// Output Value : None
//--------------------------------------------------
void UserCommonMcuSpiSetPinConfigForPowerState(EnumSpiInterface enumSpiInterface, EnumPowerTarget enumPowerTarget)
{
    ScalerSpiSetPinConfigForPowerState(enumSpiInterface, enumPowerTarget);
}
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
#if(_LOW_SPEED_ADC_POWER_REDUCE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : SARADC Power Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonMcuSarAdcPowerControl(EnumAdcPowerControl enumAdcPowerControl, EnumAdcPowerDelay enumAdcPowerDelay)
{
    ScalerMcuSarAdcPowerControl(enumAdcPowerControl, enumAdcPowerDelay);
}
#endif

#if(_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_NONE)
//--------------------------------------------------
// Description  : LS ADC Range Detection IRQ Control
// Input Value  : enumAdcIntControl : _ADC_INT_ENABLE / _ADC_INT_DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonMcuAdcLsAdcInOutCompIntControl(EnumAdcIntControl enumAdcIntControl)
{
    // Set INT Threshold when Enable
    if(enumAdcIntControl == _ADC_INT_ENABLE)
    {
        WORD usAdcThreshold = ((WORD)((DWORD)(1024 * _ADC_DETECT_INT_BY_ADC_THRESHOLD) / 100));

        ScalerMcuAdcLsAdcDetectIntInitial();

        // Set H-to-L Threshold
        ScalerMcuAdcLsAdcInOutCompIntSetting(_ADC_DETECT_INT_BY_ADC_CHANNEL, usAdcThreshold, 0x00);
    }

    ScalerMcuAdcLsAdcInOutCompIntControl(_ADC_DETECT_INT_BY_ADC_CHANNEL, enumAdcIntControl);
}
#endif
#endif
