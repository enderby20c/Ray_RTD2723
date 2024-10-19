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
// ID Code      : UserCommonMcuPeripheralInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HW_IIC_SUPPORT == _ON)
#define UserCommonMcuHwIICWrite(ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucWriteArray, ucHwIICPinNum)\
                                                (\
                                                    ScalerMcuHwIICWrite((ucSlaveAddr), (ucSubAddrLength), (usSubAddr), (ucDataLength), (pucWriteArray), (ucHwIICPinNum))\
                                                )
#endif

#if(_SW_IIC_SUPPORT == _ON)
#define UserCommonMcuIICWrite(ucSlaveAddr, ucSubAddrLength, usSubAddr, usLength, pucWriteArray)\
                                                (\
                                                    ScalerMcuIICWrite((ucSlaveAddr), (ucSubAddrLength), (usSubAddr), (usLength), (pucWriteArray))\
                                                )
#endif

#if(_TYPEC_IIC_SUPPORT == _ON)
#define UserCommonMcuTypecIICWrite(ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucWriteArray, ucHwIICPinNum)\
                                                (\
                                                    ScalerMcuTypecIICWrite((ucSlaveAddr), (ucSubAddrLength), (usSubAddr), (ucDataLength), (pucWriteArray), (ucHwIICPinNum))\
                                                )
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonPinshareGpioDdcPinSwitch(BYTE ucPinType);
extern void UserCommonPinshareAdjustConfig(EnumConfigPin enumConfigPin, EnumPinConfigType enumConfigType);
extern void UserCommonPinsharePadDrivenConfig(EnumConfigPin enumConfigPin, EnumPadDrivingCurrentType enumPadDrivingCurrentType);

#if(_10_BIT_ADC_FOR_NONE_TYPE_C_SUPPORT == _ON)
extern WORD UserCommonPinshareTypeCAdcGetAdcIdealData(EnumTypeC10BitAdcChannel enumChannel);
#endif

#if(_SPI_SUPPORT == _ON)
extern bit UserCommonSpiDataIo(EnumSpiInterface enumSpiInterface, WORD usWritelength, BYTE ucReadlength, BYTE *pucWriteArray, BYTE *pucReadArray);
extern void UserCommonSpiCSPinSel(EnumSpiInterface enumSpiInterface, EnumSpiCsSel enumSpiCsSel);

#if(_SPI0_SUPPORT == _ON)
extern void UserCommonSpiData(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf);
extern void UserCommonSpiSPIDataCeForceLow(bit bReadWrite, WORD usDataLength, BYTE *pucDataBuf);
#endif

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
extern void UserCommonSpiDimmingManualApplyUpdateSync(void);
extern bit UserCommonSpiDimmingSetPwmValueToAllZone(WORD usPwmValue);
#endif

#endif

extern void UserCommonTcon0Enable(bit bEnable);
extern void UserCommonTcon0Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon0InvEnable(bit bEnable);
extern void UserCommonTcon1Enable(bit bEnable);
extern void UserCommonTcon1Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon1InvEnable(bit bEnable);
extern void UserCommonTcon2Enable(bit bEnable);
extern void UserCommonTcon2Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon2InvEnable(bit bEnable);
extern void UserCommonTcon3Enable(bit bEnable);
extern void UserCommonTcon3Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon3InvEnable(bit bEnable);
extern void UserCommonTcon4Enable(bit bEnable);
extern void UserCommonTcon4Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon4InvEnable(bit bEnable);
extern void UserCommonTcon5Enable(bit bEnable);
extern void UserCommonTcon5Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon5InvEnable(bit bEnable);
extern void UserCommonTcon6Enable(bit bEnable);
extern void UserCommonTcon6Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon6InvEnable(bit bEnable);
extern void UserCommonTcon7Enable(bit bEnable);
extern void UserCommonTcon7Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon7InvEnable(bit bEnable);
extern void UserCommonTcon8Enable(bit bEnable);
extern void UserCommonTcon8Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon8InvEnable(bit bEnable);
extern void UserCommonTcon9Enable(bit bEnable);
extern void UserCommonTcon9Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon9InvEnable(bit bEnable);
extern void UserCommonTcon10Enable(bit bEnable);
extern void UserCommonTcon10Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon10InvEnable(bit bEnable);
extern void UserCommonTcon11Enable(bit bEnable);
extern void UserCommonTcon11Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon11InvEnable(bit bEnable);
extern void UserCommonTcon12Enable(bit bEnable);
extern void UserCommonTcon12Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon12InvEnable(bit bEnable);
extern void UserCommonTcon13Enable(bit bEnable);
extern void UserCommonTcon13Adjust(WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);
extern void UserCommonTcon13InvEnable(bit bEnable);
extern void UserCommonTconLogicalOpEnable(EnumTconLogicalOpSet enumTconLogicalOpSet, EnumTconLogicalOp enumTconLogicalOp, bit bEnable);

// Tcon Advance Functions
extern void UserCommonTconEnableByIndex(BYTE ucTconIndex, bit bEnable);
extern void UserCommonTconAdjustByIndex(BYTE ucTconIndex, WORD usHstart, WORD usHend, WORD usVstart, WORD usVend);

#if(_PWM_RST_SIGNAL_SEL == _TCON)
extern void UserCommonTconAdjust(BYTE ucArea);
#endif

#if(_PWM_FUNCTION_SUPPORT == _ON)
extern void UserCommonMcuPwmAdjustResetByDvs(BYTE ucPwmType, bit bStatus);
extern bit UserCommonMcuPwmAdjustFrequency(BYTE ucPwmType, WORD usFrequency);

#if(_PWM_BYPASS_MODE_SUPPORT == _ON)
extern void UserCommonMcuPwmByPassModeSettingFrequency(BYTE ucPwmType, WORD usTotalcont);
#endif
#endif

#if(_UART_SUPPORT == _ON)
#if((_HW_EXTERNAL_SERIAL_PORT_0_EXIST == _ON) && (_EXT_UART0_EN == _ON))
extern void UserCommonMcuUartExt0UpdateBaudRate(void);
extern bit UserCommonMcuUartExt0CheckReceiveStatus(void);
extern EnumMcuExtUartIntID UserCommonMcuUartExt0CheckIntID(void);
extern BYTE UserCommonMcuUartExt0GetByte(void);
extern bit UserCommonMcuUartExt0SetByte(BYTE ucValue);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_1_EXIST == _ON) && (_EXT_UART1_EN == _ON))
extern void UserCommonMcuUartExt1UpdateBaudRate(void);
extern bit UserCommonMcuUartExt1CheckReceiveStatus(void);
extern EnumMcuExtUartIntID UserCommonMcuUartExt1CheckIntID(void);
extern BYTE UserCommonMcuUartExt1GetByte(void);
extern bit UserCommonMcuUartExt1SetByte(BYTE ucValue);
#endif

#if((_HW_EXTERNAL_SERIAL_PORT_2_EXIST == _ON) && (_EXT_UART2_EN == _ON))
extern void UserCommonMcuUartExt2UpdateBaudRate(void);
extern bit UserCommonMcuUartExt2CheckReceiveStatus(void);
extern EnumMcuExtUartIntID UserCommonMcuUartExt2CheckIntID(void);
extern BYTE UserCommonMcuUartExt2GetByte(void);
extern bit UserCommonMcuUartExt2SetByte(BYTE ucValue);
#endif
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
extern void UserCommonMcuSetForceNack(EnumInputPort enumInputPort, bit bSelect);
#endif

extern BYTE UserCommonMcuGetDDCCI0SlaveAddr(void);
extern void UserCommonMcuSetDDCCI0SlaveAddr(BYTE ucSlaveAddr);
extern BYTE UserCommonMcuGetDDCCI0SubAddr(void);
extern BYTE UserCommonMcuGetDDCCI0DataIn(void);
extern void UserCommonMcuSetDDCCI0DataOut(BYTE ucDataOut);
extern BYTE UserCommonMcuGetDDCCI0IrqStatus(void);
extern void UserCommonMcuSetDDCCI0IrqStatus(BYTE ucStatus);


#if(_IR_SUPPORT == _IR_HW_SUPPORT)
extern void UserCommonIRHWModeDecoder(BYTE *pucIRTableArray, BYTE ucBankNum);
extern bit UserCommonIRHWModeGetData(BYTE *pucBuffer);
extern EnumNECIRStatus UserCommonIRHWModeGetNECIRStatus(void);
#endif

#if(_HW_IIC_SUPPORT == _ON)
extern bit UserCommonMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
#endif

#if(_SW_IIC_SUPPORT == _ON)
extern bit UserCommonMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif

#if(_TYPEC_IIC_SUPPORT == _ON)
extern bit UserCommonMcuTypecIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
#endif

extern void UserCommonMcuDdcDebounceAdjust(EnumInputPort enumInputPort, EnumDdcDbnSelMode enumDdcDbnSelMode);

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
extern bit UserCommonMcuDdcciColorCalibrationCheckDisplayMode(void);
#endif

#if(_SPI_SUPPORT == _ON)
extern void UserCommonMcuSpiSetPinConfigForPowerState(EnumSpiInterface enumSpiInterface, EnumPowerTarget enumPowerTarget);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
#if(_LOW_SPEED_ADC_POWER_REDUCE_SUPPORT == _ON)
extern void UserCommonMcuSarAdcPowerControl(EnumAdcPowerControl enumAdcPowerControl, EnumAdcPowerDelay enumAdcPowerDelay);
#endif

#if(_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_NONE)
extern void UserCommonMcuAdcLsAdcInOutCompIntControl(EnumAdcIntControl enumAdcIntControl);
#endif
#endif
