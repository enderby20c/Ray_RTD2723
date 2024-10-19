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
// ID Code      : ScalerMcu.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_MCU_H__
#define __SCALER_MCU_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions DDCCI Protocol Items
//--------------------------------------------------
#define _DCCCI_LENGTH                           1

//--------------------------------------------------
// Definitions PWM Frequency
//--------------------------------------------------
#define _PWM_FREQ_DVSRST_BOUND                  1000

#define _PWM_ACT_MODE_FREQ_LOW_BOUND            16
#define _PWM_ACT_MODE_FREQ_UPPER_BOUND          55000

#define _PWM_PSPD_MODE_FREQ_LOW_BOUND           2
#define _PWM_PSPD_MODE_FREQ_UPPER_BOUND         3417

//--------------------------------------------------
// Definitions of Hardware IIC
//--------------------------------------------------
#define _HW_IIC_DELAY_TIME                      5

//--------------------------------------------------
// Definitions of Software IIC
//--------------------------------------------------
#define _IIC_POLLING_TIME                       240

#if(_HW_IIC_1_SUPPORT == _ON)
#if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
//--------------------------------------------------
// Definitions of Retimer I2C Slave
//--------------------------------------------------
#define _HW_IIC_1_SLAVE_RXBUF_LENGTH            16

//--------------------------------------------------
// MACRO for Retimer I2C Slave Command
//--------------------------------------------------
#define GET_HW_IIC_1_SLAVE_CMD()                ((g_pucMcuHwI2c1Data[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5)
#define GET_HW_IIC_1_SLAVE_START_ADDR()         (g_pucMcuHwI2c1Data[1] & (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0))
#define GET_HW_IIC_1_SLAVE_SUB_CMD()            (g_pucMcuHwI2c1Data[2])
#define GET_HW_IIC_1_SLAVE_DATA(x)              (g_pucMcuHwI2c1Data[(x) + 3])
#endif // End of #if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
#endif // End of #if(_HW_IIC_1_SUPPORT == _ON)

//--------------------------------------------------
// Definitions DDCCI Protocol Items
//--------------------------------------------------
#define _DDCCI_BUFFER_SIZE                      32

// If User Don't Want to Save Tx Buf Size, Reduce the Available DDCCI Buf Size
#if(_DDCCI_TXBUF_LENGTH < _DDCCI_BUFFER_SIZE)
#undef _DDCCI_BUFFER_SIZE
#define _DDCCI_BUFFER_SIZE                      _DDCCI_TXBUF_LENGTH
#endif

#define GET_REG_XTAL_CLK_SEL()                  ((ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT3) == 0x00) ? _EXT_XTAL_CLK : _IOSC_CLK)


////////////////////////////
// Power Saving/Down Mode //
////////////////////////////
#define _TIMER_COUNT_PS_TEMP                    ((DWORD)12 * _FLASH_CLK_PS_DIV * _MCU_CLK_DIV)

//////////////////////////////////////////////////////
// Power Saving/Down Fast Mode for DP Aux Handshake //
//////////////////////////////////////////////////////
#define _TIMER_COUNT_PS_FAST_TEMP               ((DWORD)12 * _FLASH_CLK_PS_FAST_DIV * _MCU_CLK_DIV)

//////////////////
// Initial Mode //
//////////////////
#define _TIMER_COUNT_IN_TEMP                    ((DWORD)12 * _FLASH_CLK_IN_DIV * _MCU_CLK_DIV)

////////////////////////////////////////////////////////////////////////////
// Active Mode --> for switching to a higher flash speed when OSD is used //
////////////////////////////////////////////////////////////////////////////
#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
#define _TIMER_COUNT_OSD_TEMP                   ((DWORD)12 * _M2PLL_PLL_N * _M2PLL_PLL_O * _FLASH_CLK_FAST_DIV * _MCU_CLK_DIV)
#endif

#define _TIMER_COUNT_TEMP_PS_FAST1              (_IDLE_TIME * _FLASH_CLK_PS_FAST_DIV / _FLASH_CLK_PS_DIV)
#define _TIMER_COUNT_TEMP_PS_FAST2              ((WORD)(((DWORD)_HW_INTERNAL_OSC_XTAL + (_TIMER2_COUNT_PS_FAST_TEMP / 2)) / _TIMER2_COUNT_PS_FAST_TEMP))
#define _TIMER_COUNT_TEMP_PS                    ((WORD)(((DWORD)_HW_INTERNAL_OSC_XTAL + (_TIMER2_COUNT_PS_TEMP / 2)) / _TIMER2_COUNT_PS_TEMP))

#define _TIMER01_TEMP_COUNT_PS_FAST             (((DWORD)_HW_INTERNAL_OSC_XTAL + (_TIMER_COUNT_PS_FAST_TEMP / 2)) / _TIMER_COUNT_PS_FAST_TEMP)
#define _TIMER01_TEMP_COUNT_PS                  (((DWORD)_HW_INTERNAL_OSC_XTAL + (_TIMER_COUNT_PS_TEMP / 2)) / _TIMER_COUNT_PS_TEMP)

#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
#define _TIMER01_TEMP_COUNT_NORMAL              ((DWORD)_M2PLL_CLK_KHZ / _FLASH_CLK_DIV / _MCU_CLK_DIV / 12)
#define _TIMER01_TEMP_COUNT_OSD                 ((DWORD)_M2PLL_CLK_KHZ / _FLASH_CLK_DIV / _MCU_CLK_DIV / 12)
#endif

//--------------------------------------------------
// Definitions of Timer2
//--------------------------------------------------
#define _EVENT_TIME_MAX                         61000

/////////////////
// Active Mode //
/////////////////
#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#define _TIMER2_COUNT_TEMP                      ((DWORD)12 * 4 * _FLASH_CLK_DIV * _MCU_CLK_DIV)
#else
#define _TIMER2_COUNT_TEMP                      ((DWORD)12 * _FLASH_CLK_DIV * _MCU_CLK_DIV)
#endif
#endif

#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
#define _TIMER2_COUNT_NUM                       (0xFFFF - ((WORD)(((DWORD)_M2PLL_CLK_KHZ + (_TIMER2_COUNT_TEMP / 2)) / _TIMER2_COUNT_TEMP)))
#endif

#define _TIMER2_COUNT_LBYTE                     (_TIMER2_COUNT_NUM & 0x00FF)
#define _TIMER2_COUNT_HBYTE                     (_TIMER2_COUNT_NUM >> 8)

////////////////////////////
// Power Saving/Down Mode //
////////////////////////////
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#define _TIMER2_COUNT_PS_TEMP                   ((DWORD)12 * 4 * _FLASH_CLK_PS_DIV * _MCU_CLK_DIV)
#else
#define _TIMER2_COUNT_PS_TEMP                   ((DWORD)12 * _FLASH_CLK_PS_DIV * _MCU_CLK_DIV)
#endif
#define _TIMER2_COUNT_PS_NUM                    (0xFFFF - ((WORD)(((DWORD)_HW_INTERNAL_OSC_XTAL + (_TIMER2_COUNT_PS_TEMP / 2)) / _TIMER2_COUNT_PS_TEMP)))

#define _TIMER2_COUNT_PS_LBYTE                  (_TIMER2_COUNT_PS_NUM & 0x00FF)
#define _TIMER2_COUNT_PS_HBYTE                  (_TIMER2_COUNT_PS_NUM >> 8)

//////////////////////////////////////////////////////
// Power Saving/Down Fast Mode for DP Aux Handshake //
//////////////////////////////////////////////////////
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#define _TIMER2_COUNT_PS_FAST_TEMP              ((DWORD)12 * 4 * _FLASH_CLK_PS_FAST_DIV * _MCU_CLK_DIV)
#else
#define _TIMER2_COUNT_PS_FAST_TEMP              ((DWORD)12 * _FLASH_CLK_PS_FAST_DIV * _MCU_CLK_DIV)
#endif
#define _TIMER2_COUNT_PS_FAST_NUM               (0xFFFF - ((WORD)(((DWORD)_HW_INTERNAL_OSC_XTAL + (_TIMER2_COUNT_PS_FAST_TEMP / 2)) / _TIMER2_COUNT_PS_FAST_TEMP)))

#define _TIMER2_COUNT_PS_FAST_LBYTE             (_TIMER2_COUNT_PS_FAST_NUM & 0x00FF)
#define _TIMER2_COUNT_PS_FAST_HBYTE             (_TIMER2_COUNT_PS_FAST_NUM >> 8)

//////////////////
// Initial Mode //
//////////////////
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#define _TIMER2_COUNT_IN_TEMP                   ((DWORD)12 * 4 * _FLASH_CLK_IN_DIV * _MCU_CLK_DIV)
#else
#define _TIMER2_COUNT_IN_TEMP                   ((DWORD)12 * _FLASH_CLK_IN_DIV * _MCU_CLK_DIV)
#endif
#define _TIMER2_COUNT_IN_NUM                    (0xFFFF - ((WORD)(((DWORD)_EXT_XTAL + (_TIMER2_COUNT_IN_TEMP / 2)) / _TIMER2_COUNT_IN_TEMP)))

#define _TIMER2_COUNT_IN_LBYTE                  (_TIMER2_COUNT_IN_NUM & 0x00FF)
#define _TIMER2_COUNT_IN_HBYTE                  (_TIMER2_COUNT_IN_NUM >> 8)

///////////////
// Idle Mode //
///////////////
#define _IDLE_TIME_TEMP                         ((DWORD)0x0000FFFF / (((DWORD)_HW_INTERNAL_OSC_XTAL + _TIMER2_COUNT_PS_TEMP) / _TIMER2_COUNT_PS_TEMP))
#define _IDLE_TIME                              ((_IDLE_TIME_TEMP < _IDLE_TIME_MAX) ? _IDLE_TIME_TEMP : _IDLE_TIME_MAX) // Avoid_TIMER2_COUNT_IDLE_NUM Overflow
#define _TIMER2_COUNT_IDLE_NUM                  (0xFFFF - ((WORD)((((DWORD)_HW_INTERNAL_OSC_XTAL + (_TIMER2_COUNT_PS_TEMP / 2)) / _TIMER2_COUNT_PS_TEMP) * _IDLE_TIME)))

#define _TIMER2_COUNT_IDLE_LBYTE                (_TIMER2_COUNT_IDLE_NUM & 0x00FF)
#define _TIMER2_COUNT_IDLE_HBYTE                (_TIMER2_COUNT_IDLE_NUM >> 8)

////////////////////////////////////////////////////////////////////////////
// Active Mode --> for switching to a higher flash speed when OSD is used //
////////////////////////////////////////////////////////////////////////////
#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)

#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#define _TIMER2_COUNT_OSD_TEMP                  ((DWORD)12 * 4 * _FLASH_CLK_FAST_DIV * _MCU_CLK_DIV)
#else
#define _TIMER2_COUNT_OSD_TEMP                  ((DWORD)12 * _FLASH_CLK_FAST_DIV * _MCU_CLK_DIV)
#endif
#endif

#if(_HW_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
#define _TIMER2_COUNT_OSD_NUM                   (0xFFFF - ((WORD)(((DWORD)_M2PLL_CLK_KHZ + (_TIMER2_COUNT_OSD_TEMP / 2)) / _TIMER2_COUNT_OSD_TEMP)))
#endif

#define _TIMER2_COUNT_OSD_LBYTE                 (_TIMER2_COUNT_OSD_NUM & 0x00FF)
#define _TIMER2_COUNT_OSD_HBYTE                 (_TIMER2_COUNT_OSD_NUM >> 8)
#endif

//--------------------------------------------------
// Macros of MCU Watch Dog
//--------------------------------------------------
#define _TIMER_WD_MAX_COUNT                     0xFFF //!< about 586ms with 14.318MHz Reference Clk

//--------------------------------------------------
// Macros of Generated UART
//--------------------------------------------------
#define GET_EXT_UART_DIVISOR(ulClock, ulBaudRate)\
                                                ((ulClock) * 1000 / (ulBaudRate) / 16)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of I2C Slave
//--------------------------------------------------
typedef enum
{
    _HW_I2C_SLAVE_CMD_WRITE_BYTE = 0x00,
    _HW_I2C_SLAVE_CMD_WRITE_BIT,
    _HW_I2C_SLAVE_CMD_READ_BYTE,
    _HW_I2C_SLAVE_CMD_RESERVED = 0xFF
} EnumHwIICSlaveCmd;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE idata g_ucMcuDdcciCount;

#if(_HW_IIC_1_SUPPORT == _ON)
#if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
extern BYTE g_pucMcuHwI2c1Data[_HW_IIC_1_SLAVE_RXBUF_LENGTH];
#endif
#endif

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
extern WORD g_usMcuSyncDataType;
extern bit g_bMcuSyncDataTag;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMcuDdcciInitial(void);

extern void ScalerMcuDdcci0SendData(BYTE *pucWriteArray);
extern EnumInputPort ScalerMcuDdcci0GetInputPort(void);
extern void ScalerMcuDdcISPChannelCtrl(BYTE ucDdcChannel, bit bEnable);

extern void ScalerMcuDdcci0SelectDdcChannel(EnumInputPort enumInputPort);
extern void ScalerMcuClearDdcci0IRQFlag(void);

#if(_MULTI_DISPLAY_MAX >= 0x02)
extern void ScalerMcuDdcci1SendData(BYTE *pucWriteArray);
extern EnumInputPort ScalerMcuDdcci1GetInputPort(void);

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE ScalerMcuDdcci1GetInputPort_EXINT1(void);
#endif
#endif

extern void ScalerMcuDdcci1SelectDdcChannel(EnumInputPort enumInputPort);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
extern void ScalerMcuDdcci2SendData(BYTE *pucWriteArray);
extern EnumInputPort ScalerMcuDdcci2GetInputPort(void);
extern void ScalerMcuDdcci2SelectDdcChannel(EnumInputPort enumInputPort);

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE ScalerMcuDdcci2GetInputPort_EXINT1(void);
#endif
#endif

#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
extern void ScalerMcuDdcci3SendData(BYTE *pucWriteArray);
extern EnumInputPort ScalerMcuDdcci3GetInputPort(void);
extern void ScalerMcuDdcci3SelectDdcChannel(EnumInputPort enumInputPort);

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE ScalerMcuDdcci3GetInputPort_EXINT1(void);
#endif
#endif

#endif

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern void ScalerMcuDdcciHoldScl(EnumDDCCIPort enumDDCCIPort);
#endif
extern BYTE ScalerMcuDdcciGetDDCChannel(EnumDDCCIPort enumDDCCIPort);
#endif

#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
extern void ScalerMcuFlashClockDiv(EnumFlashClkDiv enumClkDiv);
extern void ScalerMcuSwitchFlashMcuFastSpeed(bit bEnable);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
#if(_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_NONE)
extern void ScalerMcuAdcLsAdcInOutCompIntClearFlag(BYTE ucChannel);
extern void ScalerMcuAdcLsAdcInOutCompIntSetting_EXINT0(BYTE ucChannel, WORD usHigh, WORD usLow);
extern void ScalerMcuAdcLsAdcInOutCompIntControl_EXINT0(BYTE ucChannel, EnumAdcIntControl enumAdcIntControl);
extern void ScalerMcuAdcLsAdcInOutCompIntClearFlag_EXINT0(BYTE ucChannel);
extern bit ScalerMcuAdcLsAdcInOutCompIntCheck_EXINT0(BYTE ucChannel);
#endif
#endif

#if(_SW_IIC_SUPPORT == _ON)
extern BYTE ScalerMcuIICStart(BYTE ucSlaveAddr);
extern void ScalerMcuIICStop(void);
extern BYTE ScalerMcuIICGetAck(void);
extern void ScalerMcuIICSendAck(void);
extern void ScalerMcuIICSendNoAck(void);
extern BYTE ScalerMcuIICGetByte(void);
extern BYTE ScalerMcuIICSendByte(BYTE ucValue);
extern bit ScalerMcuIICWriteStart(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr);
#endif

#if(_HW_IIC_SUPPORT == _ON)
extern void ScalerMcuHwIICConfigSetting(void);
#endif

#if(_HW_IIC_0_SUPPORT == _ON)
extern void ScalerMcuHwIIC0Initial(void);
extern void ScalerMcuHwIIC0ConfigSetting(void);
extern void ScalerMcuHwIIC0SetFreqDiv(EnumClkSel enumClock);
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit ScalerMcuHwIIC0WritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum);
#endif
extern bit ScalerMcuHwIIC0Read(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
extern bit ScalerMcuHwIIC0Write(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum);
#endif

#if(_HW_IIC_1_SUPPORT == _ON)
extern void ScalerMcuHwIIC1Initial(void);
extern void ScalerMcuHwIIC1ConfigSetting(void);
extern void ScalerMcuHwIIC1SetFreqDiv(EnumClkSel enumClock);
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit ScalerMcuHwIIC1WritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum);
#endif
extern bit ScalerMcuHwIIC1Read(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
extern bit ScalerMcuHwIIC1Write(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum);
#if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
extern void ScalerMcuHwIIC1SlaveInitial(void);
#endif // End of #if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
#endif

#if(_TYPEC_IIC_0_SUPPORT == _ON)
extern void ScalerMcuTypecIIC0Initial(void);
extern void ScalerMcuTypecIIC0ConfigSetting(void);
extern void ScalerMcuTypecIIC0SetFreqDiv(EnumClkSel enumClock);
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit ScalerMcuTypecIIC0WritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum);
#endif
extern bit ScalerMcuTypecIIC0Read(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
extern bit ScalerMcuTypecIIC0Write(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum);
#endif

extern void ScalerMcuIspInitial(void);
extern void ScalerMcuDdcInitial(void);
extern void ScalerMcuGpioInitial(void);

extern void ScalerMcuDdcramConfig(void);
extern void ScalerMcuBurstWriteInitial(void);

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
__attribute__((section(".itcm_section.ScalerMcuFlashInitial")))
extern void ScalerMcuFlashInitial(void);
#endif

#endif // End of #ifndef __SCALER_MCU_H__
