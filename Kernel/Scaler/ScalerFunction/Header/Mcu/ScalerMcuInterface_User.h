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
// ID Code      : ScalerMcuInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Define for DDC ram size
//--------------------------------------------------
#define _D0_EMBEDDED_DDCRAM_BLOCK_NUM                  ((_MCU_DDCRAM_D0_SIZE / _HW_DDCRAM_BLOCK_STEP) +\
                                                        ((_MCU_DDCRAM_D0_SIZE % _HW_DDCRAM_BLOCK_STEP == 0) ? 0 : 1))
#define _D1_EMBEDDED_DDCRAM_BLOCK_NUM                  ((_MCU_DDCRAM_D1_SIZE / _HW_DDCRAM_BLOCK_STEP) +\
                                                        ((_MCU_DDCRAM_D1_SIZE % _HW_DDCRAM_BLOCK_STEP == 0) ? 0 : 1))
#define _D2_EMBEDDED_DDCRAM_BLOCK_NUM                  ((_MCU_DDCRAM_D2_SIZE / _HW_DDCRAM_BLOCK_STEP) +\
                                                        ((_MCU_DDCRAM_D2_SIZE % _HW_DDCRAM_BLOCK_STEP == 0) ? 0 : 1))
#define _D3_EMBEDDED_DDCRAM_BLOCK_NUM                  ((_MCU_DDCRAM_D3_SIZE / _HW_DDCRAM_BLOCK_STEP) +\
                                                        ((_MCU_DDCRAM_D3_SIZE % _HW_DDCRAM_BLOCK_STEP == 0) ? 0 : 1))
#define _D4_EMBEDDED_DDCRAM_BLOCK_NUM                  ((_MCU_DDCRAM_D4_SIZE / _HW_DDCRAM_BLOCK_STEP) +\
                                                        ((_MCU_DDCRAM_D4_SIZE % _HW_DDCRAM_BLOCK_STEP == 0) ? 0 : 1))

#define _EMBEDDED_DDCRAM_VGA_DDC_ADDRESS               0xDF80
#define _EMBEDDED_DDCRAM_DDC0_ADDRESS                  _HW_DDCRAM_START_ADDRESS
#define _EMBEDDED_DDCRAM_DDC1_ADDRESS                  (_EMBEDDED_DDCRAM_DDC0_ADDRESS + _D0_EMBEDDED_DDCRAM_BLOCK_NUM * _HW_DDCRAM_BLOCK_STEP)
#define _EMBEDDED_DDCRAM_DDC2_ADDRESS                  (_EMBEDDED_DDCRAM_DDC1_ADDRESS + _D1_EMBEDDED_DDCRAM_BLOCK_NUM * _HW_DDCRAM_BLOCK_STEP)
#define _EMBEDDED_DDCRAM_DDC3_ADDRESS                  (_EMBEDDED_DDCRAM_DDC2_ADDRESS + _D2_EMBEDDED_DDCRAM_BLOCK_NUM * _HW_DDCRAM_BLOCK_STEP)
#define _EMBEDDED_DDCRAM_DDC4_ADDRESS                  (_EMBEDDED_DDCRAM_DDC3_ADDRESS + _D3_EMBEDDED_DDCRAM_BLOCK_NUM * _HW_DDCRAM_BLOCK_STEP)

#define _MCU_DDCRAM_A0_SIZE                            _A0_EMBEDDED_DDCRAM_MAX_SIZE

#if((_D7_DP_SUPPORT == _ON) && (_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))
#define _MCU_DDCRAM_D0_SIZE                            MAXOF(_D7_D0_EMBEDDED_DDCRAM_SIZE, _D0_EMBEDDED_DDCRAM_MAX_SIZE)
#else
#define _MCU_DDCRAM_D0_SIZE                            _D0_EMBEDDED_DDCRAM_MAX_SIZE
#endif

#if((_D7_DP_SUPPORT == _ON) && (_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))
#define _MCU_DDCRAM_D1_SIZE                            MAXOF(_D7_D1_EMBEDDED_DDCRAM_SIZE, _D1_EMBEDDED_DDCRAM_MAX_SIZE)
#elif((_D8_DP_SUPPORT == _ON) && (_D8_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))
#define _MCU_DDCRAM_D1_SIZE                            MAXOF(_D8_D1_EMBEDDED_DDCRAM_SIZE, _D1_EMBEDDED_DDCRAM_MAX_SIZE)
#else
#define _MCU_DDCRAM_D1_SIZE                            _D1_EMBEDDED_DDCRAM_MAX_SIZE
#endif

#if((_D8_DP_SUPPORT == _ON) && (_D8_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))
#define _MCU_DDCRAM_D2_SIZE                            MAXOF(_D8_D2_EMBEDDED_DDCRAM_SIZE, _D2_EMBEDDED_DDCRAM_MAX_SIZE)
#else
#define _MCU_DDCRAM_D2_SIZE                            _D2_EMBEDDED_DDCRAM_MAX_SIZE
#endif

#define _MCU_DDCRAM_D3_SIZE                            _D3_EMBEDDED_DDCRAM_MAX_SIZE
#define _MCU_DDCRAM_D4_SIZE                            _D4_EMBEDDED_DDCRAM_MAX_SIZE
#define _MCU_DDCRAM_D5_SIZE                            _D5_EMBEDDED_DDCRAM_MAX_SIZE

#if(_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define MCU_DDCRAM_A0                                  (GET_DDCRAM_POINTER(_EMBEDDED_DDCRAM_VGA_DDC_ADDRESS))
#endif

#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
#define MCU_DDCRAM_D0                                  (GET_DDCRAM_POINTER(_EMBEDDED_DDCRAM_DDC0_ADDRESS))
#endif
#endif

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D1_DDC_CHANNEL_SEL == _DDC1)
#define MCU_DDCRAM_D1                                  (GET_DDCRAM_POINTER(_EMBEDDED_DDCRAM_DDC1_ADDRESS))
#endif
#endif

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D2_DDC_CHANNEL_SEL == _DDC2)
#define MCU_DDCRAM_D2                                  (GET_DDCRAM_POINTER(_EMBEDDED_DDCRAM_DDC2_ADDRESS))
#endif
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D3_DDC_CHANNEL_SEL == _DDC3)
#define MCU_DDCRAM_D3                                  (GET_DDCRAM_POINTER(_EMBEDDED_DDCRAM_DDC3_ADDRESS))
#endif
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D4_DDC_CHANNEL_SEL == _DDC4)
#define MCU_DDCRAM_D4                                  (GET_DDCRAM_POINTER(_EMBEDDED_DDCRAM_DDC4_ADDRESS))
#endif
#endif

#if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#if(_D5_DDC_CHANNEL_SEL == _DDC5)
#define MCU_DDCRAM_D5                                  (GET_DDCRAM_POINTER(_EMBEDDED_DDCRAM_DDC5_ADDRESS))
#endif
#endif

//--------------------------------------------------
// Define for HW burst write
//--------------------------------------------------
#define _BURSTWRITE_FROM_FLASH                         0
#define _BURSTWRITE_FROM_XRAM                          1

#define _BURSTWRITE_COMMAND                            0
#define _BURSTWRITE_DATA_COMMON                        1
#define _BURSTWRITE_DATA_COMMON_AUTO_INC               2
#define _BURSTWRITE_DATA_OSD                           3

#define _BURSTWRITE32_DATA                             0
#define _BURSTWRITE32_DATA_AUTO_INC                    1
#define _BURSTWRITE32_CMD                              2

//--------------------------------------------------
// MACRO for DDC CI Command status
//--------------------------------------------------
#define GET_RUN_DDCCI_COMMAND()                        ((bit)g_ucMcuRunDdcciCommand)
#define CLR_RUN_DDCCI_COMMAND(x)                       (g_ucMcuRunDdcciCommand &= (~(_BIT0 << (x))))

//--------------------------------------------------
// MACRO for DDC CI 0 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI0_COMMAND(x)                      (g_ucMcuRunDdcciCommand = ((g_ucMcuRunDdcciCommand & (~_BIT0)) | (x)))
#define GET_RUN_DDCCI0_COMMAND()                       ((bit)(g_ucMcuRunDdcciCommand & _BIT0))

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// MACRO for DDC CI 1 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI1_COMMAND(x)                      (g_ucMcuRunDdcciCommand = ((g_ucMcuRunDdcciCommand & (~_BIT1)) | ((x) << 1)))
#define GET_RUN_DDCCI1_COMMAND()                       ((bit)(g_ucMcuRunDdcciCommand & _BIT1))
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
//--------------------------------------------------
// MACRO for DDC CI 2 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI2_COMMAND(x)                      (g_ucMcuRunDdcciCommand = ((g_ucMcuRunDdcciCommand & (~_BIT2)) | ((x) << 2)))
#define GET_RUN_DDCCI2_COMMAND()                       ((bit)(g_ucMcuRunDdcciCommand & _BIT2))
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// MACRO for DDC CI 3 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI3_COMMAND(x)                      (g_ucMcuRunDdcciCommand = ((g_ucMcuRunDdcciCommand & (~_BIT3)) | ((x) << 3)))
#define GET_RUN_DDCCI3_COMMAND()                       ((bit)(g_ucMcuRunDdcciCommand & _BIT3))
#endif

//--------------------------------------------------
// MACRO for DDC CI For Auto Switch Channel Command status
//--------------------------------------------------
#define GET_RUN_DDCCI_AUTO_CHANNEL_COMMAND()           ((bit)(g_ucMcuRunDdcciCommand & _BIT0))

//--------------------------------------------------
// MACRO for Current handle ddcci channel inx
//--------------------------------------------------
#define GET_RUN_DDCCI_HANDLE_CHANNEL()                 (g_ucMcuDdcciHandlerInx)
#define SET_RUN_DDCCI_HANDLE_CHANNEL(x)                (g_ucMcuDdcciHandlerInx = (x))

//--------------------------------------------------
// Macros of 5us Delay
//--------------------------------------------------
#define DELAY_5US()                                    {ScalerMcuDelayXus(5);}
#define DELAY_5US_EXINT()                              {ScalerMcuDelayXus(5);}

#define ScalerMcuDelay5us()                            {DELAY_5US();}

//--------------------------------------------------
// Macros of SW IIC Status
//--------------------------------------------------
#if(_SW_IIC_SUPPORT == _ON)
#define GET_SW_IIC_STATUS()                            (g_ucMcuSwIICStatus)
#define SET_SW_IIC_STATUS(x)                           (g_ucMcuSwIICStatus = (x))
#endif

//--------------------------------------------------
// Macros of DDC-CI
//--------------------------------------------------
#define GET_DDCCI_AUTO_SWITCH()                        ((bit)(MCU_FF2A_IIC_IRQ_CONTROL2 & _BIT4))
#define SET_DDCCI_AUTO_SWITCH()                        (MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT4)
#define CLR_DDCCI_AUTO_SWITCH()                        (MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT4)


//--------------------------------------------------
// Macros of bank info
//--------------------------------------------------
#define GET_CURRENT_BANK_NUMBER()                      (0xFF)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//-------------------------------------------------
// Enum DDCCI Port
//-------------------------------------------------
typedef enum
{
    _DDCCI0 = 0,
    _DDCCI1,
    _DDCCI2,
    _DDCCI3,
    _DDCCI4,
    _DDCCIMAX,
    _NO_DDCCI,
}EnumDDCCIPort;

//-------------------------------------------------
// Enum External UART
//-------------------------------------------------
typedef enum
{
    _EXT_UART_0 = 0x00,
    _EXT_UART_1 = 0x01,
    _EXT_UART_2 = 0x02,
}EnumExtUartID;

typedef enum
{
    _UART_INT_ID_MODEM_STATUS = 0x00,
    _UART_INT_ID_NO_INT_PENDING = 0x01,
    _UART_INT_ID_TX_DATA_EMPTY = 0x02,
    _UART_INT_ID_RX_DATA_RDY = 0x04,
    _UART_INT_ID_RX_LINE_STATUS = 0x06,
    _UART_INT_ID_BUSY_DETECT = 0x07,
    _UART_INT_ID_CHAR_TIMEOUT = 0x0C,
}EnumMcuExtUartIntID;

//-------------------------------------------------
// Enum Data Exchange Type Group
//-------------------------------------------------
typedef enum
{
    _DATA_EXCHANGE_NONE = 0x00,
    _DATA_EXCHANGE_KERNEL_DATA,
    _DATA_EXCHANGE_KERNEL_EVENT,
    _DATA_EXCHANGE_USER_DATA,
} EnumDataExchangeTypeGroup;

//-------------------------------------------------
// Enum DDC Debounce Select Mode
//-------------------------------------------------
typedef enum
{
    _DBN_SEL_NORMAL_MODE,
    _DBN_SEL_SPEED_UP_MODE,
}EnumDdcDbnSelMode;

//------------------------------------------
// Enumerations of ADC Power Control
//------------------------------------------
typedef enum
{
    _ADC_POWER_ENABLE = _ENABLE,
    _ADC_POWER_DISABLE = _DISABLE,
} EnumAdcPowerControl;

//------------------------------------------
// Enumerations of ADC Power Delay Control
//------------------------------------------
typedef enum
{
    _ADC_POWER_DELAY_ENABLE = _ENABLE,
    _ADC_POWER_DELAY_DISABLE = _DISABLE,
} EnumAdcPowerDelay;

//------------------------------------------
// Enumerations of ADC INT Detect Control
//------------------------------------------
typedef enum
{
    _ADC_INT_ENABLE = _ENABLE,
    _ADC_INT_DISABLE = _DISABLE,
} EnumAdcIntControl;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE data g_ucMcuDelay5usN_Base;
extern BYTE data g_ucMcuDelayXusN_Base;


#if(_SW_IIC_SUPPORT == _ON)
extern BYTE idata g_ucMcuSwIICStatus;
#endif

extern volatile BYTE g_ucMcuRunDdcciCommand;

extern BYTE g_pucMcuDdcciRxBuf[_DDCCI0_RXBUF_LENGTH];
extern volatile BYTE g_pucMcuDdcciTxBuf[_DDCCI_TXBUF_LENGTH];

extern BYTE g_ppucMcuDdcciGroupRxBuf[_MULTI_DISPLAY_MAX][_DDCCI_RXBUF_LENGTH];
extern BYTE g_ucMcuDdcciHandlerInx;

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
extern volatile BYTE g_ucMcuDdcNum;
#endif
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_HW_IIC_SUPPORT == _ON)
extern bit ScalerMcuHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum);
#endif

#if(_SW_IIC_SUPPORT == _ON)
extern bit ScalerMcuIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

#if(_TYPEC_IIC_SUPPORT == _ON)
extern bit ScalerMcuTypecIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum);
#endif

__attribute__((section(".itcm_section.ScalerMcuDelayXus")))
extern void ScalerMcuDelayXus(DWORD ulMicroSecond);
