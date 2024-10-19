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
// ID Code      : ScalerMcu.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MCU__

#include "ScalerFunctionInclude.h"
#include "Mcu/ScalerMcu.h"

//--------------------------------------------------
// Type-C PMIC IIC
//--------------------------------------------------
#if((_TYPEC_IIC_SUPPORT == _ON) && (_EMB_TYPE_C_0_PMIC_IIC != _PMIC_NO_IIC_PIN) && (_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN))
#warning "PMIC IIC should not be used for Normal IIC and Embedded Type-C at the same Time!!!"
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if((_HW_IIC_SUPPORT == _ON) || (_TYPEC_IIC_SUPPORT == _ON))
StructHwI2cSettingData code tHwI2cSetting[] =
{
#if((_HW_HW_IIC_GEN == _HW_IIC_GEN_2) || (_TYPEC_IIC_SUPPORT == _ON))
    // KERNEL _HW_IIC_LOW_SPEED_100K PARAMETERS
    {
        // _EXT_XTAL
#if(_EXT_XTAL == _XTAL14318K)
        {0x26, 0x22, 0x2A, 0x47, 0x02, 0x01, 0x2B},

#elif(_EXT_XTAL == _XTAL27000K)
        {0x30, 0x2C, 0x36, 0x47, 0x03, 0x02, 0x36},
#endif
        // IOSC_CLK(28000K)
        {0x2F, 0x2F, 0x38, 0x47, 0x03, 0x02, 0x38},
    },

    // KERNEL _HW_IIC_HIGH_SPEED_400K PARAMETERS
    {
        // _EXT_XTAL
#if(_EXT_XTAL == _XTAL14318K)
        {0x0C, 0x04, 0x06, 0x23, 0x02, 0x01, 0x09},

#elif(_EXT_XTAL == _XTAL27000K)
        {0x0D, 0x05, 0x09, 0x23, 0x03, 0x02, 0x0C},
#endif
        // IOSC_CLK(28000K)
        {0x0E, 0x06, 0x09, 0x23, 0x03, 0x02, 0x0C},
    },
#else
    // KERNEL _HW_IIC_LOW_SPEED_100K PARAMETERS
    {
        // _EXT_XTAL
#if(_EXT_XTAL == _XTAL14318K)
        {0x26, 0x22, 0x2A, 0x47, 0x02, 0x01},

#elif(_EXT_XTAL == _XTAL27000K)
        {0x30, 0x2C, 0x36, 0x47, 0x03, 0x02},
#endif
        // IOSC_CLK(28000K)
        {0x2F, 0x2F, 0x38, 0x47, 0x03, 0x02},
    },

    // KERNEL _HW_IIC_HIGH_SPEED_400K PARAMETERS
    {
        // _EXT_XTAL
#if(_EXT_XTAL == _XTAL14318K)
        {0x0C, 0x04, 0x06, 0x23, 0x02, 0x01},

#elif(_EXT_XTAL == _XTAL27000K)
        {0x0D, 0x05, 0x09, 0x23, 0x03, 0x02},
#endif
        // IOSC_CLK(28000K)
        {0x0E, 0x06, 0x09, 0x23, 0x03, 0x02},
    },
#endif // End of #if((_HW_HW_IIC_GEN == _HW_IIC_GEN_2) || (_TYPEC_IIC_SUPPORT == _ON))

#if(_HW_IIC_PAR_BY_USER_SUPPORT == _ON)
// Include User Parameters Setting
#include _USER_HW_IIC_PAR_INCLUDE
#endif
};
#endif

BYTE code tBW8InitialTable[] =
{
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x04, _NON_AUTOINC, (BYTE)PFD_0A_DDCCI_4_NULL_BYTE1, 0x6E,
    _END, // end flag
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE idata g_ucMcuDdcciCount;

BYTE data g_ucMcuDelay5usN_Base = 1;
BYTE data g_ucMcuDelayXusN_Base = 1;

__attribute__((section(".fast_data.g_ucMcu32Delay1usCnt")))
BYTE g_ucMcu32Delay1usCnt = _XTAL_BUSY_LOOP_1US_CNT;

#if(_HDMI_SUPPORT == _ON)
volatile StructDxTmdsDdcDetected g_stMcuDxTmdsDdcDetected;
#endif

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
volatile BYTE g_ucMcuReceiveDdcci0CmdNotFinish = _FAIL;
#endif
volatile BYTE g_ucMcuRunDdcciCommand;
volatile BYTE g_ucMcuSrcReadDdcciAlready;
volatile EnumDdcciCmdSrc g_penumMcuDdcciCommandSrc[_MULTI_DISPLAY_MAX];

BYTE g_pucMcuDdcciRxBuf[_DDCCI0_RXBUF_LENGTH];
volatile BYTE g_pucMcuDdcciTxBuf[_DDCCI_TXBUF_LENGTH];

BYTE g_ppucMcuDdcciGroupRxBuf[_MULTI_DISPLAY_MAX][_DDCCI_RXBUF_LENGTH];
BYTE g_ppucMcuDdcciGroupRxBackBuf[_MULTI_DISPLAY_MAX][_DDCCI_RXBUF_LENGTH];
BYTE g_pucMcuDdcciCmdLengthBack[_MULTI_DISPLAY_MAX];
BYTE g_pucMcuDdcciRetry[_MULTI_DISPLAY_MAX];

BYTE g_ppucMcuDdcciGroupTxBackBuf[_MULTI_DISPLAY_MAX][_DDCCI_TXBUF_LENGTH];

BYTE g_ucMcuDdcciHandlerInx;

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
volatile BYTE g_ucMcuDdcNum = _NO_DDC;
#endif

#if(_SW_IIC_SUPPORT == _ON)
BYTE idata g_ucMcuSwIICStatus;
#endif

#if(_HW_IIC_0_SUPPORT == _ON)
BYTE g_ucMcuHwI2c0SettingIndex = _HW_IIC_0_SPEED;
#endif

#if(_HW_IIC_1_SUPPORT == _ON)
BYTE g_ucMcuHwI2c1SettingIndex = _HW_IIC_1_SPEED;

#if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
BYTE g_pucMcuHwI2c1Data[_HW_IIC_1_SLAVE_RXBUF_LENGTH];
#endif
#endif

#if(_TYPEC_IIC_0_SUPPORT == _ON)
BYTE g_ucMcuTypecI2c0SettingIndex = _TYPEC_IIC_0_SPEED;
#endif

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
WORD g_usMcuSyncDataType;
bit g_bMcuSyncDataTag;
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : MCU initial function, must be called at first
//                Since code banking can not work correctly before this function is called,
//                this function should stay in bank0.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuInitial(void)
{
    // Clear Watchdog & Set CNT1 to Max
    ScalerWdtInitial();

    // Initial Setting of Mcu and Flash Clock/Div to External Xtal
    ScalerMcuFlashClockGroupSetting(_EXT_XTAL_CLK);

    ///////////////////
    // Flash Settings//
    ///////////////////

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
    ScalerMcuFlashInitial();
#endif

    // Set flash arbiter non-bypass mode
    MCU_FD57_MCU_FLASH_BYPASS_MODE &= ~_BIT0;

    ////////////////////////
    // Burst Write Initial//
    ////////////////////////

    ScalerMcuBurstWriteInitial();

    ///////////////////////
    //Delay 5us Caculate///
    ///////////////////////
    ScalerMcu1usDelayCalc(_EXT_XTAL_CLK);

    //////////////////
    //TIMER SETTINGS//
    //////////////////

    // Disable all interrupts
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);
    SET_INTERRUPT_ENABLE_STATUS(_INT_ALL, _DISABLE);

    // Initial timer
    ScalerTimerInitial();

    // Enable Global Interrupt
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);

    // Start Watchdog
    // MCU_FFEA_WATCHDOG_TIMER |= _BIT7;


    /////////////////////////
    //GPIO Control Settings//
    /////////////////////////

    ScalerMcuGpioInitial();

    ////////////////
    //ISP Settings//
    ////////////////

    ScalerMcuIspInitial();

    ////////////////
    //PWM Settings//
    ////////////////

#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
    // Select 8 bit duty width type
    MCU_FF53_PWM_DUT_TYPE |= (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
#else
    // Select 12 bit duty width type
    MCU_FF53_PWM_DUT_TYPE &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);

    // Enable double buffer mode
    MCU_FF48_PWM_EN |= _BIT7;
#endif

    // Enable PWM reset by DVS
    MCU_FF47_PWM_VS_CTRL = (((BYTE)_PWM5_RST_EN << 5) | ((BYTE)_PWM4_RST_EN << 4) | ((BYTE)_PWM3_RST_EN << 3) |
                            ((BYTE)_PWM2_RST_EN << 2) | ((BYTE)_PWM1_RST_EN << 1) | ((BYTE)_PWM0_RST_EN));


    ////////////////
    //DDC Settings//
    ////////////////

    ScalerMcuDdcInitial();


    ///////////////////
    //DDC-CI Settings//
    ///////////////////

    ScalerMcuDdcciInitial();


    ////////////////
    //IIC Settings//
    ////////////////

#if(_HW_IIC_SUPPORT == _ON)
    ScalerMcuHwIICConfigSetting();

#if(_HW_IIC_1_SUPPORT == _ON)
#if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
    ScalerMcuHwIIC1SlaveInitial();

    // Enable I2C_1 Slave for Main Chip to Updage Config
    ScalerMcuHwIIC1SlaveEnableIrq(_ENABLE);
#endif
#endif

#endif

    ////////////////
    //SPI Settings//
    ////////////////

#if(_SPI_SUPPORT == _ON)
    ScalerSpiInitial();
#endif

    ///////////////////
    //SARADC Settings//
    ///////////////////

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    // Set Threshold for Auto Mode
    MCU_FF0F_ADC0_THRESHOLD_H = 0x00;
    MCU_FF10_ADC0_THRESHOLD_L = 0xFF;
    MCU_FF11_ADC1_THRESHOLD_H = 0x00;
    MCU_FF12_ADC1_THRESHOLD_L = 0xFF;
    MCU_FF13_ADC2_THRESHOLD_H = 0x00;
    MCU_FF14_ADC2_THRESHOLD_L = 0xFF;
    MCU_FF15_ADC3_THRESHOLD_H = 0x00;
    MCU_FF16_ADC3_THRESHOLD_L = 0xFF;

    // Set Auto Mode
    MCU_FF08_ADC_ACONTROL |= _BIT5;

    // Set Wait Time between measure
    MCU_FF17_CTRL0_WAIT_TIME_VALUE = 0x00;

    // Set ADC bias current to 5uA
    MCU_FF08_ADC_ACONTROL &= ~(_BIT2 | _BIT1);

    // ADC Start Scan
    MCU_FF08_ADC_ACONTROL |= _BIT7;

#elif((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))
    // ---------------------------
    // LSADC_0 initial
    // ---------------------------
    // Set Threshold for Auto Mode
    MCU_FDF7_ADC0_THRESHOLD_H = 0x00;
    MCU_FDF8_ADC0_THRESHOLD_L = 0xFF;
    MCU_FDF9_ADC1_THRESHOLD_H = 0x00;
    MCU_FDFA_ADC1_THRESHOLD_L = 0xFF;
    MCU_FDFB_ADC2_THRESHOLD_H = 0x00;
    MCU_FDFC_ADC2_THRESHOLD_L = 0xFF;
    MCU_FDFD_ADC3_THRESHOLD_H = 0x00;
    MCU_FDFE_ADC3_THRESHOLD_L = 0xFF;

    // Set Auto Mode
    MCU_FD3A_ADC_ACONTROL |= _BIT5;

    // Set Wait Time between measure
    MCU_FDFF_CTRL0_WAIT_TIME_VALUE = 0x00;

    // Set ADC bias current to 5uA
    MCU_FD39_ADC_ANALOG_CONFIG &= ~(_BIT6 | _BIT5);

    // Set Jack Detection bias current to 5uA
    MCU_FD39_ADC_ANALOG_CONFIG &= ~(_BIT1 | _BIT0);

    // ADC Power Enable
    MCU_FD39_ADC_ANALOG_CONFIG |= _BIT2;

    // ADC Start Scan
    MCU_FD3A_ADC_ACONTROL |= _BIT7;

    // ---------------------------
    // LSADC_1 initial
    // ---------------------------
    // Set Threshold for Auto Mode
    MCU_FF0F_ADC0_THRESHOLD_H = 0x00;
    MCU_FF10_ADC0_THRESHOLD_L = 0xFF;
    MCU_FF11_ADC1_THRESHOLD_H = 0x00;
    MCU_FF12_ADC1_THRESHOLD_L = 0xFF;
    MCU_FF13_ADC2_THRESHOLD_H = 0x00;
    MCU_FF14_ADC2_THRESHOLD_L = 0xFF;
    MCU_FF15_ADC3_THRESHOLD_H = 0x00;
    MCU_FF16_ADC3_THRESHOLD_L = 0xFF;

    // Set Auto Mode
    MCU_FF08_ADC_ACONTROL |= _BIT5;

    // Set Wait Time between measure
    MCU_FF17_CTRL0_WAIT_TIME_VALUE = 0x00;

    // Set ADC bias current to 5uA
    MCU_FF02_ADC_ANALOG_CONFIG &= ~(_BIT6 | _BIT5);

    // Set Jack Detection bias current to 5uA
    MCU_FF02_ADC_ANALOG_CONFIG &= ~(_BIT1 | _BIT0);

    // ADC Power Enable
    MCU_FF02_ADC_ANALOG_CONFIG |= _BIT2;

    // ADC Start Scan
    MCU_FF08_ADC_ACONTROL |= _BIT7;

#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

#if(_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_NONE)
    ScalerMcuAdcLsAdcDetectIntInitial();
#endif
#endif // End of #if(_LOW_SPEED_ADC_SUPPORT == _ON)

    //////////////////////
    //WATCH DOG Settings//
    //////////////////////

    ScalerTimerWDInitial();


    //////////////////////////
    //Repeater INT3 Settings//
    //////////////////////////

#if(_USB3_REPEATER_MAC_SUPPORT == _ON)
    // Enable EXINT 3
    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_3, _ENABLE);
#endif
}

#if(_HW_XRAM_AUTO_RESET_TO_ZERO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset xram to zero
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerMcuXramReset(void)
{
    WORD usTimerCounter = 800;

    // Set HW Xram Reset
    MCU_FF34_XRAM_RESET |= _BIT0;

    while((MCU_FF34_XRAM_RESET & _BIT0) != 0)
    {
        if(usTimerCounter-- == 0)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : DDC-CI Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciInitial(void)
{
#if(_HW_DDCCI0_EXIST == _ON)
    // Set slave address for debug tool
    MCU_FF23_IIC_SET_SLAVE = 0x6A;
#endif

    // Disable DDCCI 1,2,3,4
#if(_HW_DDCCI1_EXIST == _ON)
    MCU_FE87_IIC_1_SET_SLAVE = 0x3C;
    ScalerSetBit(PFE_86_IIC_1_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif

#if(_HW_DDCCI2_EXIST == _ON)
    MCU_FE95_IIC_2_SET_SLAVE = 0x3C;
    ScalerSetBit(PFE_94_IIC_2_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif

#if(_HW_DDCCI3_EXIST == _ON)
    MCU_FEA4_IIC_3_SET_SLAVE = 0x3C;
    ScalerSetBit(PFE_A3_IIC_3_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif

#if(_HW_DDCCI4_EXIST == _ON)
    MCU_FD01_IIC_4_SET_SLAVE = 0x3C;
    ScalerSetBit(PFD_00_IIC_4_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif

#if((_DEBUG_DDC_CHANNEL_SEL == _DDC5) && (_HW_DDC5_EXIST == _ON))
    // DDC from DDC5 channel
    ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC4) && (_HW_DDC4_EXIST == _ON))
    // DDC from DDC4 channel
    ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC3) && (_HW_DDC3_EXIST == _ON))
    // DDC from DDC3 channel
    ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC2) && (_HW_DDC2_EXIST == _ON))
    // DDC from DDC2 channel
    ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC1) && (_HW_DDC1_EXIST == _ON))
    // DDC from DDC1 channel
    ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC0) && (_HW_DDC0_EXIST == _ON))
    // DDC from DDC0 channel
    ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) && (_HW_ISP_DDC_EXIST == _ON))
    // DDC from VGA_DDC channel
    ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

    // Assign DDC-CI interrupts to int1 (IRQ2)
    // MCU_FFC4_IRQ_PRIORITY_3 &= ~(_BIT2 | _BIT1 | _BIT0);
    // MCU_FFC4_IRQ_PRIORITY_3 |= _BIT0;

    //////////////////
    //DDC-CI 0 reset//
    //////////////////

#if(_HW_DDCCI0_EXIST == _ON)
    // Enable DDC-CI buffer auto reset
    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT7;

    // Clear DDCCI status
    MCU_FF27_IIC_STATUS = 0x00;
    pData[0] = MCU_FF25_IIC_DATA_IN;
    MCU_FF26_IIC_DATA_OUT = 0x00;
    MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);

    // Reset IIC Buffer
    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

    // For HP case, Reply Null Msg as DDCCI Buffer Empty
#if(_HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT == _ON)
    MCU_FF2B_IIC_CHANNEL_CONTROL |= _BIT5;
#endif

#endif

    //////////////////
    //DDC-CI 1 reset//
    //////////////////

#if(_HW_DDCCI1_EXIST == _ON)
    // Enable DDC-CI buffer auto reset
    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT7;

    // Clear DDCCI status
    MCU_FE8B_IIC_1_STATUS = 0x00;
    pData[1] = MCU_FE89_IIC_1_DATA_IN;
    MCU_FE8A_IIC_1_DATA_OUT = 0x00;
    MCU_FE8D_IIC_1_STATUS2 &= ~(_BIT5 | _BIT4);

    // Reset IIC Buffer
    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;

    // For HP case, Reply Null Msg as DDCCI Buffer Empty
#if(_HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT == _ON)
    MCU_FE8F_IIC_1_CHANNEL_CONTROL |= _BIT5;
#endif

#endif

    //////////////////
    //DDC-CI 2 reset//
    //////////////////

#if(_HW_DDCCI2_EXIST == _ON)
    // Enable DDC-CI buffer auto reset
    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT7;

    // Clear DDCCI status
    MCU_FE99_IIC_2_STATUS = 0x00;
    pData[2] = MCU_FE97_IIC_2_DATA_IN;
    MCU_FE98_IIC_2_DATA_OUT = 0x00;
    MCU_FE9B_IIC_2_STATUS2 &= ~(_BIT5 | _BIT4);

    // Reset IIC Buffer
    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT6;

    // For HP case, Reply Null Msg as DDCCI Buffer Empty
#if(_HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT == _ON)
    MCU_FE9D_IIC_2_CHANNEL_CONTROL |= _BIT5;
#endif

#endif

    //////////////////
    //DDC-CI 3 reset//
    //////////////////

#if(_HW_DDCCI3_EXIST == _ON)
    // Enable DDC-CI buffer auto reset
    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT7;

    // Clear DDCCI status
    MCU_FEA8_IIC_3_STATUS = 0x00;
    pData[3] = MCU_FEA6_IIC_3_DATA_IN;
    MCU_FEA7_IIC_3_DATA_OUT = 0x00;
    MCU_FEAA_IIC_3_STATUS2 &= ~(_BIT5 | _BIT4);

    // Reset IIC Buffer
    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT6;

    // For HP case, Reply Null Msg as DDCCI Buffer Empty
#if(_HW_DDCCI_BUFFER_EMPTY_REPLY_NULL_MSG_SUPPORT == _ON)
    MCU_FEAC_IIC_3_CHANNEL_CONTROL |= _BIT5;
#endif

#endif

    // Enable INT1
    SET_INTERRUPT_ENABLE_STATUS(_INT_EXINT_1, _ENABLE);

    // Enable STOP_I, D_IN_I, SUB_I interrupts
    MCU_FF28_IIC_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;

#if((_DDCCI_AUTO_SWITCH_SUPPORT == _ON) && (_DEBUG_MESSAGE_SUPPORT == _OFF))
    SET_DDCCI_AUTO_SWITCH();
#endif

    DebugMessageSystem("######    F/W START    ######", _OFF);

#if(_IO_TOGGLE_TEST_SUPPORT == _ON)
    IOToggleTest();
#endif
}

//--------------------------------------------------
// Description  : Send DDC Data
// Input Value  : enDdcciChannel --> DDCCI Channel Index
//                pWriteArray --> Data to be sent
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciSendData(EnumDDCCIPort enumDdcciChannel, BYTE *pucWriteArray)
{
    switch(enumDdcciChannel)
    {
        case _DDCCI0:
            ScalerMcuDdcci0SendData(pucWriteArray);
            break;

#if(_MULTI_DISPLAY_MAX >= 0x02)
        case _DDCCI1:
            ScalerMcuDdcci1SendData(pucWriteArray);
            break;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
        case _DDCCI2:
            ScalerMcuDdcci2SendData(pucWriteArray);
            break;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
        case _DDCCI3:
            ScalerMcuDdcci3SendData(pucWriteArray);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get InputPort by checking Active DDC Channel for Ddccci
// Input Value  : enDdcciChannel --> DDCCI Channel Index
// Output Value : InputPort
//--------------------------------------------------
EnumInputPort ScalerMcuDdcciGetInputPort(EnumDDCCIPort enumDdcciChannel)
{
    switch(enumDdcciChannel)
    {
        case _DDCCI0:
            return ScalerMcuDdcci0GetInputPort();

#if(_MULTI_DISPLAY_MAX >= 0x02)
        case _DDCCI1:
            return ScalerMcuDdcci1GetInputPort();
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
        case _DDCCI2:
            return ScalerMcuDdcci2GetInputPort();
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
        case _DDCCI3:
            return ScalerMcuDdcci3GetInputPort();
#endif

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Enable/Disable Ddcci Channel
// Input Value  : enumInputPort --> Input Port
//                bEn --> Enable/Disable
// Output Value : InputPort
//--------------------------------------------------
void ScalerMcuDdcciEnable(bit bEn, EnumInputPort enumInputPort)
{
    BYTE ucDdcChannel = ScalerMcuGetDdcChannelFromInputPort(enumInputPort);

    // A0 for bit6; D5/4/3/2/1/0 for bit5/4/3/2/1/0
    BYTE ucDdcciCanDisable = 0xFF;

#if(_DEBUG_MESSAGE_SUPPORT == _ON)

    switch(ucDdcChannel)
    {
#if(_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC)
        case _VGA_DDC:
            ucDdcciCanDisable = (ucDdcciCanDisable & ~_BIT7);
            break;
#endif

#if(_DEBUG_DDC_CHANNEL_SEL == _DDC0)
        case _D0_DDC_CHANNEL_SEL:
            ucDdcciCanDisable = (ucDdcciCanDisable & ~_BIT0);
            break;
#endif

#if(_DEBUG_DDC_CHANNEL_SEL == _DDC1)
        case _D1_DDC_CHANNEL_SEL:
            ucDdcciCanDisable = (ucDdcciCanDisable & ~_BIT1);
            break;
#endif

#if(_DEBUG_DDC_CHANNEL_SEL == _DDC2)
        case _D2_DDC_CHANNEL_SEL:
            ucDdcciCanDisable = (ucDdcciCanDisable & ~_BIT2);
            break;
#endif

#if(_DEBUG_DDC_CHANNEL_SEL == _DDC3)
        case _D3_DDC_CHANNEL_SEL:
            ucDdcciCanDisable = (ucDdcciCanDisable & ~_BIT3);
            break;
#endif

#if(_DEBUG_DDC_CHANNEL_SEL == _DDC4)
        case _D4_DDC_CHANNEL_SEL:
            ucDdcciCanDisable = (ucDdcciCanDisable & ~_BIT4);
            break;
#endif

#if(_DEBUG_DDC_CHANNEL_SEL == _DDC5)
        case _D5_DDC_CHANNEL_SEL:
            ucDdcciCanDisable = (ucDdcciCanDisable & ~_BIT5);
            break;
#endif

        default:
            break;
    }
#endif

    if(bEn == _DISABLE)
    {
        switch(ucDdcChannel)
        {
            case _VGA_DDC:
#if(_HW_ISP_DDC_EXIST == _ON)
                ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
#endif
                break;

#if(_D0_DDC_CHANNEL_SEL != _NO_DDC)
            case _D0_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if((_D0_DDC_CHANNEL_SEL == _DDC0) && ((ucDdcciCanDisable & _BIT0) == _BIT0))
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if((_D0_DDC_CHANNEL_SEL == _DDC1) && ((ucDdcciCanDisable & _BIT1) == _BIT1))
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if((_D0_DDC_CHANNEL_SEL == _DDC2) && ((ucDdcciCanDisable & _BIT2) == _BIT2))
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if((_D0_DDC_CHANNEL_SEL == _DDC3) && ((ucDdcciCanDisable & _BIT3) == _BIT3))
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if((_D0_DDC_CHANNEL_SEL == _DDC4) && ((ucDdcciCanDisable & _BIT4) == _BIT4))
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if((_D0_DDC_CHANNEL_SEL == _DDC5) && ((ucDdcciCanDisable & _BIT5) == _BIT5))
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif
                break;
#endif

#if(_D1_DDC_CHANNEL_SEL != _NO_DDC)
            case _D1_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if((_D1_DDC_CHANNEL_SEL == _DDC0) && ((ucDdcciCanDisable & _BIT0) == _BIT0))
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if((_D1_DDC_CHANNEL_SEL == _DDC1) && ((ucDdcciCanDisable & _BIT1) == _BIT1))
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if((_D1_DDC_CHANNEL_SEL == _DDC2) && ((ucDdcciCanDisable & _BIT2) == _BIT2))
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if((_D1_DDC_CHANNEL_SEL == _DDC3) && ((ucDdcciCanDisable & _BIT3) == _BIT3))
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if((_D1_DDC_CHANNEL_SEL == _DDC4) && ((ucDdcciCanDisable & _BIT4) == _BIT4))
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if((_D1_DDC_CHANNEL_SEL == _DDC5) && ((ucDdcciCanDisable & _BIT5) == _BIT5))
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif
                break;
#endif

#if(_D2_DDC_CHANNEL_SEL != _NO_DDC)
            case _D2_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if((_D2_DDC_CHANNEL_SEL == _DDC0) && ((ucDdcciCanDisable & _BIT0) == _BIT0))
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if((_D2_DDC_CHANNEL_SEL == _DDC1) && ((ucDdcciCanDisable & _BIT1) == _BIT1))
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if((_D2_DDC_CHANNEL_SEL == _DDC2) && ((ucDdcciCanDisable & _BIT2) == _BIT2))
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if((_D2_DDC_CHANNEL_SEL == _DDC3) && ((ucDdcciCanDisable & _BIT3) == _BIT3))
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if((_D2_DDC_CHANNEL_SEL == _DDC4) && ((ucDdcciCanDisable & _BIT4) == _BIT4))
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if((_D2_DDC_CHANNEL_SEL == _DDC5) && ((ucDdcciCanDisable & _BIT5) == _BIT5))
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif
                break;
#endif

#if(_D3_DDC_CHANNEL_SEL != _NO_DDC)
            case _D3_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if((_D3_DDC_CHANNEL_SEL == _DDC0) && ((ucDdcciCanDisable & _BIT0) == _BIT0))
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if((_D3_DDC_CHANNEL_SEL == _DDC1) && ((ucDdcciCanDisable & _BIT1) == _BIT1))
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if((_D3_DDC_CHANNEL_SEL == _DDC2) && ((ucDdcciCanDisable & _BIT2) == _BIT2))
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if((_D3_DDC_CHANNEL_SEL == _DDC3) && ((ucDdcciCanDisable & _BIT3) == _BIT3))
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if((_D3_DDC_CHANNEL_SEL == _DDC4) && ((ucDdcciCanDisable & _BIT4) == _BIT4))
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if((_D3_DDC_CHANNEL_SEL == _DDC5) && ((ucDdcciCanDisable & _BIT5) == _BIT5))
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif
                break;
#endif

#if(_D4_DDC_CHANNEL_SEL != _NO_DDC)
            case _D4_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if((_D4_DDC_CHANNEL_SEL == _DDC0) && ((ucDdcciCanDisable & _BIT0) == _BIT0))
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if((_D4_DDC_CHANNEL_SEL == _DDC1) && ((ucDdcciCanDisable & _BIT1) == _BIT1))
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if((_D4_DDC_CHANNEL_SEL == _DDC2) && ((ucDdcciCanDisable & _BIT2) == _BIT2))
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if((_D4_DDC_CHANNEL_SEL == _DDC3) && ((ucDdcciCanDisable & _BIT3) == _BIT3))
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if((_D4_DDC_CHANNEL_SEL == _DDC4) && ((ucDdcciCanDisable & _BIT4) == _BIT4))
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if((_D4_DDC_CHANNEL_SEL == _DDC5) && ((ucDdcciCanDisable & _BIT5) == _BIT5))
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif
                break;
#endif

#if(_D5_DDC_CHANNEL_SEL != _NO_DDC)
            case _D5_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if((_D5_DDC_CHANNEL_SEL == _DDC0) && ((ucDdcciCanDisable & _BIT0) == _BIT0))
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if((_D5_DDC_CHANNEL_SEL == _DDC1) && ((ucDdcciCanDisable & _BIT1) == _BIT1))
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if((_D5_DDC_CHANNEL_SEL == _DDC2) && ((ucDdcciCanDisable & _BIT2) == _BIT2))
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if((_D5_DDC_CHANNEL_SEL == _DDC3) && ((ucDdcciCanDisable & _BIT3) == _BIT3))
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if((_D5_DDC_CHANNEL_SEL == _DDC4) && ((ucDdcciCanDisable & _BIT4) == _BIT4))
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if((_D5_DDC_CHANNEL_SEL == _DDC5) && ((ucDdcciCanDisable & _BIT5) == _BIT5))
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
                }
#endif
                break;
#endif

            default:
                break;
        }
    }
    else
    {
        switch(ucDdcChannel)
        {
            case _VGA_DDC:
#if(_HW_ISP_DDC_EXIST == _ON)
                ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
#endif
                break;

#if(_D0_DDC_CHANNEL_SEL != _NO_DDC)
            case _D0_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if(_D0_DDC_CHANNEL_SEL == _DDC0)
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if(_D0_DDC_CHANNEL_SEL == _DDC1)
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if(_D0_DDC_CHANNEL_SEL == _DDC2)
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if(_D0_DDC_CHANNEL_SEL == _DDC3)
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if(_D0_DDC_CHANNEL_SEL == _DDC4)
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if(_D0_DDC_CHANNEL_SEL == _DDC5)
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif
                break;
#endif

#if(_D1_DDC_CHANNEL_SEL != _NO_DDC)
            case _D1_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if(_D1_DDC_CHANNEL_SEL == _DDC0)
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if(_D1_DDC_CHANNEL_SEL == _DDC1)
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if(_D1_DDC_CHANNEL_SEL == _DDC2)
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if(_D1_DDC_CHANNEL_SEL == _DDC3)
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if(_D1_DDC_CHANNEL_SEL == _DDC4)
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if(_D1_DDC_CHANNEL_SEL == _DDC5)
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif
                break;
#endif

#if(_D2_DDC_CHANNEL_SEL != _NO_DDC)
            case _D2_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if(_D2_DDC_CHANNEL_SEL == _DDC0)
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if(_D2_DDC_CHANNEL_SEL == _DDC1)
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if(_D2_DDC_CHANNEL_SEL == _DDC2)
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if(_D2_DDC_CHANNEL_SEL == _DDC3)
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if(_D2_DDC_CHANNEL_SEL == _DDC4)
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if(_D2_DDC_CHANNEL_SEL == _DDC5)
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif
                break;
#endif

#if(_D3_DDC_CHANNEL_SEL != _NO_DDC)
            case _D3_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if(_D3_DDC_CHANNEL_SEL == _DDC0)
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if(_D3_DDC_CHANNEL_SEL == _DDC1)
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if(_D3_DDC_CHANNEL_SEL == _DDC2)
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if(_D3_DDC_CHANNEL_SEL == _DDC3)
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if(_D3_DDC_CHANNEL_SEL == _DDC4)
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if(_D3_DDC_CHANNEL_SEL == _DDC5)
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif
                break;
#endif

#if(_D4_DDC_CHANNEL_SEL != _NO_DDC)
            case _D4_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if(_D4_DDC_CHANNEL_SEL == _DDC0)
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if(_D4_DDC_CHANNEL_SEL == _DDC1)
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if(_D4_DDC_CHANNEL_SEL == _DDC2)
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if(_D4_DDC_CHANNEL_SEL == _DDC3)
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if(_D4_DDC_CHANNEL_SEL == _DDC4)
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if(_D4_DDC_CHANNEL_SEL == _DDC5)
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif
                break;
#endif

#if(_D5_DDC_CHANNEL_SEL != _NO_DDC)
            case _D5_DDC_CHANNEL_SEL:
#if(_HW_DDC0_EXIST == _ON)
                if(_D5_DDC_CHANNEL_SEL == _DDC0)
                {
                    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC1_EXIST == _ON)
                if(_D5_DDC_CHANNEL_SEL == _DDC1)
                {
                    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC2_EXIST == _ON)
                if(_D5_DDC_CHANNEL_SEL == _DDC2)
                {
                    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC3_EXIST == _ON)
                if(_D5_DDC_CHANNEL_SEL == _DDC3)
                {
                    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC4_EXIST == _ON)
                if(_D5_DDC_CHANNEL_SEL == _DDC4)
                {
                    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif

#if(_HW_DDC5_EXIST == _ON)
                if(_D5_DDC_CHANNEL_SEL == _DDC5)
                {
                    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
                }
#endif
                break;
#endif

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Select which DDCCI Connect to which DDC
// Input Value  : enDdcciChannel --> DDCCI Channel Index
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciSelectDdcChannel(EnumDDCCIPort enumDdcciChannel, EnumInputPort enumInputPort)
{
    switch(enumDdcciChannel)
    {
        case _DDCCI0:
            ScalerMcuDdcci0SelectDdcChannel(enumInputPort);
            break;

#if(_MULTI_DISPLAY_MAX >= 0x02)
        case _DDCCI1:
            ScalerMcuDdcci1SelectDdcChannel(enumInputPort);
            break;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
        case _DDCCI2:
            ScalerMcuDdcci2SelectDdcChannel(enumInputPort);
            break;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
        case _DDCCI3:
            ScalerMcuDdcci3SelectDdcChannel(enumInputPort);
            break;
#endif

        default:
            break;
    }
}

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DDCCI Auto Switch Channel Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciAutoSwitchEnableChannel(void)
{
#if(_HW_ISP_DDC_EXIST == _ON)
    ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
#endif
#if(_HW_DDC0_EXIST == _ON)
    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
#endif
#if(_HW_DDC1_EXIST == _ON)
    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
#endif
#if(_HW_DDC2_EXIST == _ON)
    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
#endif
#if(_HW_DDC3_EXIST == _ON)
    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
#endif
#if(_HW_DDC4_EXIST == _ON)
    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
#endif
#if(_HW_DDC5_EXIST == _ON)
    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), _BIT4);
#endif
}
#endif

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
//--------------------------------------------------
// Description  : Clear DDCCI0 int flag when DDCCI0 switch to DDCCI4 channel
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci0ClearWrongIntFlag(void)
{
    ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    pData[0] = MCU_FF25_IIC_DATA_IN;
    MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);
    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
    if(GET_DDCCI_AUTO_SWITCH() == _FALSE)
    {
        SET_DDCCI_AUTO_SWITCH();
    }
}
#endif
#endif

//--------------------------------------------------
// Description  : DDCCI0 Channel Send DDC Data
// Input Value  : pWriteArray --> Data to be sent
//                usTimeOutCnt --> Timeout
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci0SendData(BYTE *pucWriteArray)
{
    WORD usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
    BYTE ucDdcciCount = 0;

    if(((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3) < _DDCCI_TXBUF_LENGTH)
    {
        memcpy(g_ppucMcuDdcciGroupTxBackBuf[_DDCCI0], pucWriteArray, ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3));
    }

    if((MCU_FF27_IIC_STATUS & _BIT0) == _BIT0)
    {
        g_ucMcuSrcReadDdcciAlready = ((g_ucMcuSrcReadDdcciAlready & (~_BIT0)) | (_BIT0));

        // Clear Flag
        MCU_FF27_IIC_STATUS &= ~_BIT0;
    }

    // Enable mcu write
    MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucDdcciCount < ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3))
    {
        // Load data to DDC-CI buffer until buffer full
        if((MCU_FF29_IIC_STATUS2 & _BIT2) == 0)
        {
            MCU_FF26_IIC_DATA_OUT = pucWriteArray[ucDdcciCount++];

            usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
        }
        else
        {
            ScalerTimerDelayXms(2);

            usTimeOutCnt--;
        }

        if(usTimeOutCnt == 0)
        {
            break;
        }
    }

    // Disable mcu write
    MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
}

//--------------------------------------------------
// Description  : Get InputPort by checking Active DDC Channel for Ddccci
// Input Value  : None
// Output Value : InputPort
//--------------------------------------------------
EnumInputPort ScalerMcuDdcci0GetInputPort(void)
{
    switch(ScalerGetBit(PFF_22_IIC_CH_SEL, (_BIT2 | _BIT1 | _BIT0)))
    {
        case _VGA_DDC:
            return _A0_INPUT_PORT;

        case _DDC0:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC0))
            return _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC0))
            return _D1_INPUT_PORT;
#elif((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC0))
            return _D2_INPUT_PORT;
#elif((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC0))
            return _D3_INPUT_PORT;
#elif((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC0))
            return _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC0))
            return _D5_INPUT_PORT;
#endif
            break;

        case _DDC1:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC1))
            return _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC1))
            return _D1_INPUT_PORT;
#elif((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC1))
            return _D2_INPUT_PORT;
#elif((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC1))
            return _D3_INPUT_PORT;
#elif((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC1))
            return _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC1))
            return _D5_INPUT_PORT;
#endif
            break;

        case _DDC2:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC2))
            return _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC2))
            return _D1_INPUT_PORT;
#elif((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC2))
            return _D2_INPUT_PORT;
#elif((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC2))
            return _D3_INPUT_PORT;
#elif((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC2))
            return _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC2))
            return _D5_INPUT_PORT;
#endif
            break;

        case _DDC3:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC3))
            return _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC3))
            return _D1_INPUT_PORT;
#elif((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC3))
            return _D2_INPUT_PORT;
#elif((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC3))
            return _D3_INPUT_PORT;
#elif((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC3))
            return _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC3))
            return _D5_INPUT_PORT;
#endif
            break;

        case _DDC4:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC4))
            return _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC4))
            return _D1_INPUT_PORT;
#elif((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC4))
            return _D2_INPUT_PORT;
#elif((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC4))
            return _D3_INPUT_PORT;
#elif((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC4))
            return _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC4))
            return _D5_INPUT_PORT;
#endif
            break;

        case _DDC5:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC5))
            return _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC5))
            return _D1_INPUT_PORT;
#elif((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC5))
            return _D2_INPUT_PORT;
#elif((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC5))
            return _D3_INPUT_PORT;
#elif((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC5))
            return _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC5))
            return _D5_INPUT_PORT;
#endif
            break;

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Get DDC Channel From Input Port
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
BYTE ScalerMcuGetDdcChannelFromInputPort(EnumInputPort enumInputPort)
{
    BYTE ucDdcChannel = _NO_DDC;

    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            ucDdcChannel = _VGA_DDC;
            break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            ucDdcChannel = _D0_DDC_CHANNEL_SEL;
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            ucDdcChannel = _D1_DDC_CHANNEL_SEL;
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            ucDdcChannel = _D2_DDC_CHANNEL_SEL;
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            ucDdcChannel = _D3_DDC_CHANNEL_SEL;
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            ucDdcChannel = _D4_DDC_CHANNEL_SEL;
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            ucDdcChannel = _D5_DDC_CHANNEL_SEL;
            break;
#endif

#if(_DUAL_DP_SUPPORT == _ON)
        case _DUAL_DP_INPUT_PORT:
            if(GET_DUAL_DP_PORT_SWITCH_SELECT() == _DUAL_DP_INPUT_PORT)
            {
                enumInputPort = _DUAL_DP_MAIN_PORT;
            }
            else
            {
                enumInputPort = GET_DUAL_DP_PORT_SWITCH_SELECT();
            }

            switch(enumInputPort)
            {
                case _D0_INPUT_PORT:
                    ucDdcChannel = _D0_DDC_CHANNEL_SEL;
                    break;

                case _D1_INPUT_PORT:
                    ucDdcChannel = _D1_DDC_CHANNEL_SEL;
                    break;

                case _D2_INPUT_PORT:
                    ucDdcChannel = _D2_DDC_CHANNEL_SEL;
                    break;

                default:
                    break;
            }

            break;
#endif

        default:
        case _NO_INPUT_PORT:
            ucDdcChannel = _NO_DDC;

            break;
    }

    return ucDdcChannel;
}

//--------------------------------------------------
// Description  : Select Which DDC Connect to DDCCI0
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci0SelectDdcChannel(EnumInputPort enumInputPort)
{
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
    if((ScalerFwUpdateGetState() == _FALSE) && (GET_DDCCI0_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS))
    {
        return;
    }
#endif
    if(enumInputPort == _NO_INPUT_PORT)
    {
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), ScalerMcuGetDdcChannelFromInputPort(enumInputPort));
    }
}

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Description  : DDCCI1 Channel Send DDC Data
// Input Value  : pWriteArray --> Data to be sent
//                usTimeOutCnt --> Timeout
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci1SendData(BYTE *pucWriteArray)
{
    WORD usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
    BYTE ucDdcciCount = 0;

    if(((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3) < _DDCCI_TXBUF_LENGTH)
    {
        memcpy(g_ppucMcuDdcciGroupTxBackBuf[_DDCCI1], pucWriteArray, ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3));
    }

    if((MCU_FE8B_IIC_1_STATUS & _BIT0) == _BIT0)
    {
        g_ucMcuSrcReadDdcciAlready = ((g_ucMcuSrcReadDdcciAlready & (~_BIT1)) | (_BIT1));

        // Clear Flag
        MCU_FE8B_IIC_1_STATUS &= ~_BIT0;
    }

    // Enable mcu write
    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucDdcciCount < ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3))
    {
        // Load data to DDC-CI buffer until buffer full
        if((MCU_FE8D_IIC_1_STATUS2 & _BIT2) == 0)
        {
            MCU_FE8A_IIC_1_DATA_OUT = pucWriteArray[ucDdcciCount++];

            usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
        }
        else
        {
            ScalerTimerDelayXms(2);

            usTimeOutCnt--;
        }

        if(usTimeOutCnt == 0)
        {
            break;
        }
    }

    // Disable mcu write
    MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;
}

//--------------------------------------------------
// Description  : Get InputPort by checking Active DDC Channel for Ddccci
// Input Value  : None
// Output Value : InputPort
//--------------------------------------------------
EnumInputPort ScalerMcuDdcci1GetInputPort(void)
{
    switch(ScalerGetBit(PFE_86_IIC_1_CH_SEL, (_BIT2 | _BIT1 | _BIT0)))
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            return _A0_INPUT_PORT;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            return _D0_INPUT_PORT;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            return _D1_INPUT_PORT;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            return _D2_INPUT_PORT;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            return _D3_INPUT_PORT;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            return _D4_INPUT_PORT;
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            return _D5_INPUT_PORT;
#endif

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Select Which DDC Connect to DDCCI1
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci1SelectDdcChannel(EnumInputPort enumInputPort)
{
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
    if((ScalerFwUpdateGetState() == _FALSE) && (GET_DDCCI1_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS))
    {
        return;
    }
#endif
    if(enumInputPort == _NO_INPUT_PORT)
    {
        ScalerSetBit(PFE_86_IIC_1_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(PFE_86_IIC_1_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), ScalerMcuGetDdcChannelFromInputPort(enumInputPort));
    }
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
//--------------------------------------------------
// Description  : DDCCI2 Channel Send DDC Data
// Input Value  : pWriteArray --> Data to be sent
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci2SendData(BYTE *pucWriteArray)
{
    WORD usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
    BYTE ucDdcciCount = 0;

    if(((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3) < _DDCCI_TXBUF_LENGTH)
    {
        memcpy(g_ppucMcuDdcciGroupTxBackBuf[_DDCCI2], pucWriteArray, ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3));
    }

    if((MCU_FE99_IIC_2_STATUS & _BIT0) == _BIT0)
    {
        g_ucMcuSrcReadDdcciAlready = ((g_ucMcuSrcReadDdcciAlready & (~_BIT2)) | (_BIT2));

        // Clear Flag
        MCU_FE99_IIC_2_STATUS &= ~_BIT0;
    }

    // Enable mcu write
    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucDdcciCount < ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3))
    {
        // Load data to DDC-CI buffer until buffer full
        if((MCU_FE9B_IIC_2_STATUS2 & _BIT2) == 0)
        {
            MCU_FE98_IIC_2_DATA_OUT = pucWriteArray[ucDdcciCount++];

            usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
        }
        else
        {
            ScalerTimerDelayXms(2);

            usTimeOutCnt--;
        }

        if(usTimeOutCnt == 0)
        {
            break;
        }
    }

    // Disable mcu write
    MCU_FE9C_IIC_2_IRQ_CONTROL2 &= ~_BIT5;
}

//--------------------------------------------------
// Description  : Get InputPort by checking Active DDC Channel for Ddccci
// Input Value  : None
// Output Value : InputPort
//--------------------------------------------------
EnumInputPort ScalerMcuDdcci2GetInputPort(void)
{
    switch(ScalerGetBit(PFE_94_IIC_2_CH_SEL, (_BIT2 | _BIT1 | _BIT0)))
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            return _A0_INPUT_PORT;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            return _D0_INPUT_PORT;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            return _D1_INPUT_PORT;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            return _D2_INPUT_PORT;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            return _D3_INPUT_PORT;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            return _D4_INPUT_PORT;
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            return _D5_INPUT_PORT;
#endif

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Select Which DDC Connect to DDCCI2
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci2SelectDdcChannel(EnumInputPort enumInputPort)
{
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
    if((ScalerFwUpdateGetState() == _FALSE) && (GET_DDCCI2_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS))
    {
        return;
    }
#endif
    if(enumInputPort == _NO_INPUT_PORT)
    {
        ScalerSetBit(PFE_94_IIC_2_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(PFE_94_IIC_2_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), ScalerMcuGetDdcChannelFromInputPort(enumInputPort));
    }
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// Description  : DDCCI3 Channel Send DDC Data
// Input Value  : pWriteArray --> Data to be sent
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci3SendData(BYTE *pucWriteArray)
{
    WORD usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
    BYTE ucDdcciCount = 0;

    if(((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3) < _DDCCI_TXBUF_LENGTH)
    {
        memcpy(g_ppucMcuDdcciGroupTxBackBuf[_DDCCI3], pucWriteArray, ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3));
    }

    if((MCU_FEA8_IIC_3_STATUS & _BIT0) == _BIT0)
    {
        g_ucMcuSrcReadDdcciAlready = ((g_ucMcuSrcReadDdcciAlready & (~_BIT3)) | (_BIT3));

        // Clear Flag
        MCU_FEA8_IIC_3_STATUS &= ~_BIT0;
    }

    // Enable mcu write
    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucDdcciCount < ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3))
    {
        // Load data to DDC-CI buffer until buffer full
        if((MCU_FEAA_IIC_3_STATUS2 & _BIT2) == 0)
        {
            MCU_FEA7_IIC_3_DATA_OUT = pucWriteArray[ucDdcciCount++];

            usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
        }
        else
        {
            ScalerTimerDelayXms(2);

            usTimeOutCnt--;
        }

        if(usTimeOutCnt == 0)
        {
            break;
        }
    }

    // Disable mcu write
    MCU_FEAB_IIC_3_IRQ_CONTROL2 &= ~_BIT5;
}

//--------------------------------------------------
// Description  : Get InputPort by checking Active DDC Channel for Ddccci
// Input Value  : None
// Output Value : InputPort
//--------------------------------------------------
EnumInputPort ScalerMcuDdcci3GetInputPort(void)
{
    switch(ScalerGetBit(PFE_A3_IIC_3_CH_SEL, (_BIT2 | _BIT1 | _BIT0)))
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            return _A0_INPUT_PORT;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            return _D0_INPUT_PORT;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            return _D1_INPUT_PORT;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            return _D2_INPUT_PORT;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            return _D3_INPUT_PORT;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            return _D4_INPUT_PORT;
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            return _D5_INPUT_PORT;
#endif

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Select Which DDC Connect to DDCCI3
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci3SelectDdcChannel(EnumInputPort enumInputPort)
{
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
    if((ScalerFwUpdateGetState() == _FALSE) && (GET_DDCCI3_SLAVE_ADDRESS() == _FW_UPDATE_SLAVE_ADDRESS))
    {
        return;
    }
#endif
    if(enumInputPort == _NO_INPUT_PORT)
    {
        ScalerSetBit(PFE_A3_IIC_3_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit(PFE_A3_IIC_3_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), ScalerMcuGetDdcChannelFromInputPort(enumInputPort));
    }
}

#endif

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
//--------------------------------------------------
// Description  : Release SCL
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuDdcciReleaseScl(void)
{
    switch(g_ucMcuDdcNum & (_BIT2 | _BIT1 | _BIT0))
    {
#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
            break;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
            break;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
            break;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
            break;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
            break;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
            break;
#endif

#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DDC Channel for normal
// Input Value  : enDDCCIPort --> DDC CI Port
// Output Value : DDC Channel no
//--------------------------------------------------
BYTE ScalerMcuDdcciGetDDCChannel(EnumDDCCIPort enumDDCCIPort)
{
    BYTE ucDDCNo = _NO_DDC;

    switch(enumDDCCIPort)
    {
        case _DDCCI0:
            ucDDCNo = ScalerGetBit(PFF_22_IIC_CH_SEL, (_BIT2 | _BIT1 | _BIT0));
            break;

#if(_HW_DDCCI1_EXIST == _ON)
        case _DDCCI1:
            ucDDCNo = ScalerGetBit(PFE_86_IIC_1_CH_SEL, (_BIT2 | _BIT1 | _BIT0));
            break;
#endif

#if(_HW_DDCCI2_EXIST == _ON)
        case _DDCCI2:
            ucDDCNo = ScalerGetBit(PFE_94_IIC_2_CH_SEL, (_BIT2 | _BIT1 | _BIT0));
            break;
#endif

#if(_HW_DDCCI3_EXIST == _ON)
        case _DDCCI3:
            ucDDCNo = ScalerGetBit(PFE_A3_IIC_3_CH_SEL, (_BIT2 | _BIT1 | _BIT0));
            break;
#endif

        default:
            break;
    }

    return ucDDCNo;
}
#endif  // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Get DDC Buffer Size
// Input Value  : None
// Output Value : DDCCI Buffer Size
//--------------------------------------------------
BYTE ScalerMcuDdcciGetBufferSize(void)
{
    return _DDCCI_BUFFER_SIZE;
}

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Get DDC-CI Data in Interrupt Process
// Input Value  : pReadArray --> Data received
//                 ucBufLength --> DDC-DI 0 Rx Buffer Length
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
BYTE ScalerMcuDdcci0IntGetData(BYTE *pucReadArray, BYTE ucBufLength)
{
    BYTE ucDdcciCmdLength = 0;

    // Get DDC-CI Source Address
    if((MCU_FF27_IIC_STATUS & _BIT1) == _BIT1)
    {
        g_ucMcuDdcciCount = 0;

        // Save Address
        pucReadArray[g_ucMcuDdcciCount++] = MCU_FF24_IIC_SUB_IN;

        // Clear Flag
        MCU_FF27_IIC_STATUS &= ~_BIT1;
    }

    if((MCU_FF27_IIC_STATUS & _BIT2) == _BIT2)
    {
        // Save received data until buffer empty
        while((MCU_FF29_IIC_STATUS2 & _BIT1) == 0)
        {
            if(g_ucMcuDdcciCount >= ucBufLength)
            {
                // Reset data buffer
                MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

                g_ucMcuDdcciCount = 0;

                break;
            }

            pucReadArray[g_ucMcuDdcciCount++] = MCU_FF25_IIC_DATA_IN;

            ucDdcciCmdLength = (pucReadArray[_DCCCI_LENGTH] & 0x7F) + 3;

            // Reset data buffer and Enable mcu write
            if(ucDdcciCmdLength == g_ucMcuDdcciCount)
            {
                // Reset data buffer
                MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                g_ucMcuDdcciCount = 0;

                if((((bit)(g_ucMcuSrcReadDdcciAlready & _BIT0)) == _TRUE) && (ucDdcciCmdLength <= _DDCCI_RXBUF_LENGTH) && (ucDdcciCmdLength == g_pucMcuDdcciCmdLengthBack[_DDCCI0]) && (memcmp(g_ppucMcuDdcciGroupRxBackBuf[_DDCCI0], pucReadArray, ucDdcciCmdLength) == 0))
                {
                    BYTE ucPreTxLength = (g_ppucMcuDdcciGroupTxBackBuf[_DDCCI0][_DCCCI_LENGTH] & 0x7F) + 3;
                    BYTE ucIndex = 0;

                    if(ucPreTxLength <= _DDCCI_TXBUF_LENGTH)
                    {
                        while(ucIndex < ucPreTxLength)
                        {
                            // Load data to DDC-CI buffer until buffer full
                            if((MCU_FF29_IIC_STATUS2 & _BIT2) == 0)
                            {
                                MCU_FF26_IIC_DATA_OUT = g_ppucMcuDdcciGroupTxBackBuf[_DDCCI0][ucIndex++];
                            }
                        }
                    }

                    // Retry case flag
                    g_pucMcuDdcciRetry[_DDCCI0] = _TRUE;
                }
                else
                {
                    for(BYTE ucLoopIndex = 32; ucLoopIndex > 0; ucLoopIndex --)
                    {
                        MCU_FF26_IIC_DATA_OUT = 0;
                    }

                    if(ucDdcciCmdLength <= _DDCCI_RXBUF_LENGTH)
                    {
                        memcpy(g_ppucMcuDdcciGroupRxBackBuf[_DDCCI0], pucReadArray, ucDdcciCmdLength);

                        g_pucMcuDdcciCmdLengthBack[_DDCCI0] = ucDdcciCmdLength;
                    }
                    else
                    {
                        g_pucMcuDdcciCmdLengthBack[_DDCCI0] = 0;
                    }

                    // Reset data buffer
                    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
                }

                // Clear Flag
                MCU_FF27_IIC_STATUS &= ~_BIT0;

                // Disable mcu write
                MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;

                g_ucMcuSrcReadDdcciAlready = ((g_ucMcuSrcReadDdcciAlready & (~_BIT0)) | 0x00);

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
                if((pucReadArray[3] == _DDCCI_OPCODE_VCP_DISP_CALIBRATION) && (pucReadArray[2] == 0x03))
                {
                    // Hold Scl for Display Calibration Process
                    ScalerMcuDdcciHoldScl(_DDCCI0);
                }
#endif
                if(g_pucMcuDdcciRetry[_DDCCI0] == _TRUE)
                {
                    return _FAIL;
                }
                else
                {
                    return _SUCCESS;
                }
            }
        }
    }

    return _FAIL;
}

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Description  : Get DDC-CI1 Data in Interrupt Process
// Input Value  : pReadArray --> Data received
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
BYTE ScalerMcuDdcci1IntGetData(BYTE *pucReadArray)
{
    BYTE ucDdcciCmdLength = 0;

    // Get DDC-CI Source Address
    if((MCU_FE8B_IIC_1_STATUS & _BIT1) == _BIT1)
    {
        g_ucMcuDdcciCount = 0;

        // Save Address
        pucReadArray[g_ucMcuDdcciCount++] = MCU_FE88_IIC_1_SUB_IN;

        // Clear Flag
        MCU_FE8B_IIC_1_STATUS &= ~_BIT1;
    }

    if((MCU_FE8B_IIC_1_STATUS & _BIT2) == _BIT2)
    {
        // Save received data until buffer empty
        while((MCU_FE8D_IIC_1_STATUS2 & _BIT1) == 0)
        {
            if(g_ucMcuDdcciCount >= _DDCCI_RXBUF_LENGTH)
            {
                // Reset data buffer
                MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;

                g_ucMcuDdcciCount = 0;

                break;
            }

            pucReadArray[g_ucMcuDdcciCount++] = MCU_FE89_IIC_1_DATA_IN;

            ucDdcciCmdLength = (pucReadArray[_DCCCI_LENGTH] & 0x7F) + 3;

            // All data are received
            if(ucDdcciCmdLength == g_ucMcuDdcciCount)
            {
                // Reset data buffer and Enable mcu write
                MCU_FE8E_IIC_1_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                g_ucMcuDdcciCount = 0;

                if((((bit)(g_ucMcuSrcReadDdcciAlready & _BIT1)) == _TRUE) && (ucDdcciCmdLength <= _DDCCI_RXBUF_LENGTH) && (ucDdcciCmdLength == g_pucMcuDdcciCmdLengthBack[_DDCCI1]) && (memcmp(g_ppucMcuDdcciGroupRxBackBuf[_DDCCI1], pucReadArray, ucDdcciCmdLength) == 0))
                {
                    BYTE ucPreTxLength = (g_ppucMcuDdcciGroupTxBackBuf[_DDCCI1][_DCCCI_LENGTH] & 0x7F) + 3;
                    BYTE ucIndex = 0;

                    if(ucPreTxLength <= _DDCCI_TXBUF_LENGTH)
                    {
                        while(ucIndex < ucPreTxLength)
                        {
                            // Load data to DDC-CI buffer until buffer full
                            if((MCU_FE8D_IIC_1_STATUS2 & _BIT2) == 0)
                            {
                                MCU_FE8A_IIC_1_DATA_OUT = g_ppucMcuDdcciGroupTxBackBuf[_DDCCI1][ucIndex++];
                            }
                        }
                    }

                    // Retry case flag
                    g_pucMcuDdcciRetry[_DDCCI1] = _TRUE;
                }
                else
                {
                    for(BYTE ucLoopIndex = 32; ucLoopIndex > 0; ucLoopIndex --)
                    {
                        MCU_FE8A_IIC_1_DATA_OUT = 0;
                    }

                    if(ucDdcciCmdLength <= _DDCCI_RXBUF_LENGTH)
                    {
                        memcpy(g_ppucMcuDdcciGroupRxBackBuf[_DDCCI1], pucReadArray, ucDdcciCmdLength);

                        g_pucMcuDdcciCmdLengthBack[_DDCCI1] = ucDdcciCmdLength;
                    }
                    else
                    {
                        g_pucMcuDdcciCmdLengthBack[_DDCCI1] = 0;
                    }

                    // Reset data buffer
                    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;
                }

                // Clear Flag
                MCU_FE8B_IIC_1_STATUS &= ~_BIT0;

                // Disable mcu write
                MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;

                g_ucMcuSrcReadDdcciAlready = ((g_ucMcuSrcReadDdcciAlready & (~_BIT1)) | 0x00);

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
                if((pucReadArray[3] == _DDCCI_OPCODE_VCP_DISP_CALIBRATION) && (pucReadArray[2] == 0x03))
                {
                    // Hold Scl for Display Calibration Process
                    ScalerMcuDdcciHoldScl(_DDCCI1);
                }
#endif
                if(g_pucMcuDdcciRetry[_DDCCI1] == _TRUE)
                {
                    return _FAIL;
                }
                else
                {
                    return _SUCCESS;
                }
            }
        }
    }

    return _FAIL;
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
//--------------------------------------------------
// Description  : Get DDC-CI2 Data in Interrupt Process
// Input Value  : pReadArray --> Data received
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
BYTE ScalerMcuDdcci2IntGetData(BYTE *pucReadArray)
{
    BYTE ucDdcciCmdLength = 0;

    // Get DDC-CI Source Address
    if((MCU_FE99_IIC_2_STATUS & _BIT1) == _BIT1)
    {
        g_ucMcuDdcciCount = 0;

        // Save Address
        pucReadArray[g_ucMcuDdcciCount++] = MCU_FE96_IIC_2_SUB_IN;

        // Clear Flag
        MCU_FE99_IIC_2_STATUS &= ~_BIT1;
    }

    if((MCU_FE99_IIC_2_STATUS & _BIT2) == _BIT2)
    {
        // Save received data until buffer empty
        while((MCU_FE9B_IIC_2_STATUS2 & _BIT1) == 0)
        {
            if(g_ucMcuDdcciCount >= _DDCCI_RXBUF_LENGTH)
            {
                // Reset data buffer
                MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT6;

                g_ucMcuDdcciCount = 0;

                break;
            }

            pucReadArray[g_ucMcuDdcciCount++] = MCU_FE97_IIC_2_DATA_IN;

            ucDdcciCmdLength = (pucReadArray[_DCCCI_LENGTH] & 0x7F) + 3;

            // All data are received
            if(ucDdcciCmdLength == g_ucMcuDdcciCount)
            {
                // Reset data buffer and Enable mcu write
                MCU_FE9C_IIC_2_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                g_ucMcuDdcciCount = 0;

                if((((bit)(g_ucMcuSrcReadDdcciAlready & _BIT2)) == _TRUE) && (ucDdcciCmdLength <= _DDCCI_RXBUF_LENGTH) && (ucDdcciCmdLength == g_pucMcuDdcciCmdLengthBack[_DDCCI2]) && (memcmp(g_ppucMcuDdcciGroupRxBackBuf[_DDCCI2], pucReadArray, ucDdcciCmdLength) == 0))
                {
                    BYTE ucPreTxLength = (g_ppucMcuDdcciGroupTxBackBuf[_DDCCI2][_DCCCI_LENGTH] & 0x7F) + 3;
                    BYTE ucIndex = 0;

                    if(ucPreTxLength <= _DDCCI_TXBUF_LENGTH)
                    {
                        while(ucIndex < ucPreTxLength)
                        {
                            // Load data to DDC-CI buffer until buffer full
                            if((MCU_FE9B_IIC_2_STATUS2 & _BIT2) == 0)
                            {
                                MCU_FE98_IIC_2_DATA_OUT = g_ppucMcuDdcciGroupTxBackBuf[_DDCCI2][ucIndex++];
                            }
                        }
                    }

                    // Retry case flag
                    g_pucMcuDdcciRetry[_DDCCI2] = _TRUE;
                }
                else
                {
                    for(BYTE ucLoopIndex = 32; ucLoopIndex > 0; ucLoopIndex --)
                    {
                        MCU_FE98_IIC_2_DATA_OUT = 0;
                    }

                    if(ucDdcciCmdLength <= _DDCCI_RXBUF_LENGTH)
                    {
                        memcpy(g_ppucMcuDdcciGroupRxBackBuf[_DDCCI2], pucReadArray, ucDdcciCmdLength);

                        g_pucMcuDdcciCmdLengthBack[_DDCCI2] = ucDdcciCmdLength;
                    }
                    else
                    {
                        g_pucMcuDdcciCmdLengthBack[_DDCCI2] = 0;
                    }

                    // Reset data buffer
                    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT6;
                }

                // Clear Flag
                MCU_FE99_IIC_2_STATUS &= ~_BIT0;

                // Disable mcu write
                MCU_FE9C_IIC_2_IRQ_CONTROL2 &= ~_BIT5;

                g_ucMcuSrcReadDdcciAlready = ((g_ucMcuSrcReadDdcciAlready & (~_BIT2)) | 0x00);

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
                if((pucReadArray[3] == _DDCCI_OPCODE_VCP_DISP_CALIBRATION) && (pucReadArray[2] == 0x03))
                {
                    // Hold Scl for Display Calibration Process
                    ScalerMcuDdcciHoldScl(_DDCCI2);
                }
#endif
                if(g_pucMcuDdcciRetry[_DDCCI2] == _TRUE)
                {
                    return _FAIL;
                }
                else
                {
                    return _SUCCESS;
                }
            }
        }
    }

    return _FAIL;
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// Description  : Get DDC-CI3 Data in Interrupt Process
// Input Value  : pReadArray --> Data received
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
BYTE ScalerMcuDdcci3IntGetData(BYTE *pucReadArray)
{
    BYTE ucDdcciCmdLength = 0;

    // Get DDC-CI Source Address
    if((MCU_FEA8_IIC_3_STATUS & _BIT1) == _BIT1)
    {
        g_ucMcuDdcciCount = 0;

        // Save Address
        pucReadArray[g_ucMcuDdcciCount++] = MCU_FEA5_IIC_3_SUB_IN;

        // Clear Flag
        MCU_FEA8_IIC_3_STATUS &= ~_BIT1;
    }

    if((MCU_FEA8_IIC_3_STATUS & _BIT2) == _BIT2)
    {
        // Save received data until buffer empty
        while((MCU_FEAA_IIC_3_STATUS2 & _BIT1) == 0)
        {
            if(g_ucMcuDdcciCount >= _DDCCI_RXBUF_LENGTH)
            {
                // Reset data buffer
                MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT6;

                g_ucMcuDdcciCount = 0;

                break;
            }

            pucReadArray[g_ucMcuDdcciCount++] = MCU_FEA6_IIC_3_DATA_IN;

            ucDdcciCmdLength = (pucReadArray[_DCCCI_LENGTH] & 0x7F) + 3;

            // All data are received
            if(ucDdcciCmdLength == g_ucMcuDdcciCount)
            {
                // Reset data buffer and Enable mcu write
                MCU_FEAB_IIC_3_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                g_ucMcuDdcciCount = 0;

                if((((bit)(g_ucMcuSrcReadDdcciAlready & _BIT3)) == _TRUE) && (ucDdcciCmdLength <= _DDCCI_RXBUF_LENGTH) && (ucDdcciCmdLength == g_pucMcuDdcciCmdLengthBack[_DDCCI3]) && (memcmp(g_ppucMcuDdcciGroupRxBackBuf[_DDCCI3], pucReadArray, ucDdcciCmdLength) == 0))
                {
                    BYTE ucPreTxLength = (g_ppucMcuDdcciGroupTxBackBuf[_DDCCI3][_DCCCI_LENGTH] & 0x7F) + 3;
                    BYTE ucIndex = 0;

                    if(ucPreTxLength <= _DDCCI_TXBUF_LENGTH)
                    {
                        while(ucIndex < ucPreTxLength)
                        {
                            // Load data to DDC-CI buffer until buffer full
                            if((MCU_FEAA_IIC_3_STATUS2 & _BIT2) == 0)
                            {
                                MCU_FEA7_IIC_3_DATA_OUT = g_ppucMcuDdcciGroupTxBackBuf[_DDCCI3][ucIndex++];
                            }
                        }
                    }

                    // Retry case flag
                    g_pucMcuDdcciRetry[_DDCCI3] = _TRUE;
                }
                else
                {
                    for(BYTE ucLoopIndex = 32; ucLoopIndex > 0; ucLoopIndex --)
                    {
                        MCU_FEA7_IIC_3_DATA_OUT = 0;
                    }

                    if(ucDdcciCmdLength <= _DDCCI_RXBUF_LENGTH)
                    {
                        memcpy(g_ppucMcuDdcciGroupRxBackBuf[_DDCCI3], pucReadArray, ucDdcciCmdLength);

                        g_pucMcuDdcciCmdLengthBack[_DDCCI3] = ucDdcciCmdLength;
                    }
                    else
                    {
                        g_pucMcuDdcciCmdLengthBack[_DDCCI3] = 0;
                    }

                    // Reset data buffer
                    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT6;
                }

                // Clear Flag
                MCU_FEA8_IIC_3_STATUS &= ~_BIT0;

                // Disable mcu write
                MCU_FEAB_IIC_3_IRQ_CONTROL2 &= ~_BIT5;

                g_ucMcuSrcReadDdcciAlready = ((g_ucMcuSrcReadDdcciAlready & (~_BIT3)) | 0x00);

#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
                if((pucReadArray[3] == _DDCCI_OPCODE_VCP_DISP_CALIBRATION) && (pucReadArray[2] == 0x03))
                {
                    // Hold Scl for Display Calibration Process
                    ScalerMcuDdcciHoldScl(_DDCCI3);
                }
#endif
                if(g_pucMcuDdcciRetry[_DDCCI3] == _TRUE)
                {
                    return _FAIL;
                }
                else
                {
                    return _SUCCESS;
                }
            }
        }
    }

    return _FAIL;
}
#endif
#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _OFF)


#if((_OGC_FUNCTION == _ON) || (_OCC_FUNCTION == _ON) || (_OGC_DICOM_FUNCTION == _ON))
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : hold SCL
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuDdcciHoldScl(EnumDDCCIPort enumDDCCIPort)
{
    g_ucMcuDdcNum = ScalerMcuDdcciGetDDCChannel(enumDDCCIPort);

    switch(g_ucMcuDdcNum & (_BIT2 | _BIT1 | _BIT0))
    {
#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
            break;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
            break;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
            break;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
            break;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
            break;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
            break;
#endif

#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Check Display Mode for OGC/OCC Support on
// Input Value  : NONE
// Output Value : Result
//--------------------------------------------------
bit ScalerMcuDdcciColorCalibrationCheckDisplayMode(void)
{
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) || (GET_DISPLAY_MODE() == _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT))
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif  // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))


#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#if((_OGC_FUNCTION == _OFF) && (_OGC_DICOM_FUNCTION == _OFF) && (_OCC_FUNCTION == _OFF))
//--------------------------------------------------
// Description  : Set DDCCI Auto Switch Inactive Channel Disable
// Input Value  : enumDisplayMode --> Display mode
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciAutoSwitchDisableInactiveChannel(void)
{
    BYTE pucDdcciMappingStatus[8] = {0};
    BYTE ucDisplayCount = GET_RGN_MAX_DISPLAY_REGION();

    ucDisplayCount = ucDisplayCount;

#if(_HW_DDCCI0_EXIST == _ON)
    pucDdcciMappingStatus[ScalerGetBit(PFF_22_IIC_CH_SEL, (_BIT2 | _BIT1 | _BIT0))] = _TRUE;
#endif
#if(_HW_DDCCI1_EXIST == _ON)
    if(ucDisplayCount > 1)
    {
        pucDdcciMappingStatus[ScalerGetBit(PFE_86_IIC_1_CH_SEL, (_BIT2 | _BIT1 | _BIT0))] = _TRUE;
    }
#endif
#if(_HW_DDCCI2_EXIST == _ON)
    if(ucDisplayCount > 2)
    {
        pucDdcciMappingStatus[ScalerGetBit(PFE_94_IIC_2_CH_SEL, (_BIT2 | _BIT1 | _BIT0))] = _TRUE;
    }
#endif
#if(_HW_DDCCI3_EXIST == _ON)
    if(ucDisplayCount > 3)
    {
        pucDdcciMappingStatus[ScalerGetBit(PFE_A3_IIC_3_CH_SEL, (_BIT2 | _BIT1 | _BIT0))] = _TRUE;
    }
#endif

#if(_HW_ISP_DDC_EXIST == _ON)
    if(pucDdcciMappingStatus[_VGA_DDC] == _FALSE)
    {
        ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
    }
#endif
#if(_HW_DDC0_EXIST == _ON)
    if(pucDdcciMappingStatus[_DDC0] == _FALSE)
    {
        ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
    }
#endif
#if(_HW_DDC1_EXIST == _ON)
    if(pucDdcciMappingStatus[_DDC1] == _FALSE)
    {
        ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
    }
#endif
#if(_HW_DDC2_EXIST == _ON)
    if(pucDdcciMappingStatus[_DDC2] == _FALSE)
    {
        ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
    }
#endif
#if(_HW_DDC3_EXIST == _ON)
    if(pucDdcciMappingStatus[_DDC3] == _FALSE)
    {
        ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
    }
#endif
#if(_HW_DDC4_EXIST == _ON)
    if(pucDdcciMappingStatus[_DDC4] == _FALSE)
    {
        ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
    }
#endif
#if(_HW_DDC5_EXIST == _ON)
    if(pucDdcciMappingStatus[_DDC5] == _FALSE)
    {
        ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT4 | _BIT1), 0x00);
    }
#endif
}
#endif
#endif
#endif

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
//--------------------------------------------------
// Description  : Flash Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuFlashInitial(void)
{
    // latch Flash SO data in falling edge
    ScalerSetBit(PFF_6C_READ_INSTRUCTION, ~_BIT5, _BIT5);

#if(_FLASH_READ_MODE == _FLASH_FAST_READ)
    // Set Fast Read Opcode
    MCU_FF6B_FAST_READ_OP_CODE = 0x0B;

    // Set Flash Fast Read Mode
    ScalerSetBit(PFF_6C_READ_INSTRUCTION, ~(_BIT7 | _BIT6), _BIT6);
#else
    // Set Dual Read Opcode
    MCU_FF6B_FAST_READ_OP_CODE = 0x3B;

    // Set Flash Dual Read Mode
    ScalerSetBit(PFF_6C_READ_INSTRUCTION, ~(_BIT7 | _BIT6), _BIT7);
#endif
}
#endif
//--------------------------------------------------
// Description  : BurstWrite Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuBurstWriteInitial(void)
{
    ScalerBurstWrite((tBW8InitialTable + 32), 5, GET_CURRENT_BANK_NUMBER(), PFD_0A_DDCCI_4_NULL_BYTE1, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
}

//--------------------------------------------------
// Description  : Both MCU/Flash clock switching and setting
// Input Value  : Clock --> _M2PLL_CLK/_EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuFlashClockGroupSetting(EnumClkSel enumClock)
{
    bit bXtalClkSwitch = _FALSE;

    // Suspend Systick Count
    SET_INTERRUPT_ENABLE_STATUS(_INT_TIMER_2, _DISABLE);

    if(enumClock == _M2PLL_CLK)
    {
        ScalerGlobalCtrlSetSys32ClkSrc(_M2PLL_CLK);

        if(GET_REG_MCU_CLK_SEL() == _EXT_XTAL_CLK)
        {
            ScalerGlobalCrystalClkSel(_IOSC_CLK);

            bXtalClkSwitch = _TRUE;
        }

        // Both Mcu/Flash first stage divider
        ScalerSetBit(PFF_ED_MCU_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), ((_FLASH_CLK_DIV & 0x0F) << 2));

        // Flash second stage divider
        ScalerSetBit(PFF_E9_MCU_CLK_CONTROL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_FLASH_2_CLK_DIV & 0x0F));

        // Bit1 : 1 --> CPU CLK Source Select to M2PLL
        ScalerSetBit(PFF_ED_MCU_CONTROL, ~_BIT1, _BIT1);

        if(bXtalClkSwitch == _TRUE)
        {
            ScalerGlobalCrystalClkSel(_EXT_XTAL_CLK);
        }

        // Set Timer Count
        ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_NORMAL_MODE);
    }
    else if(enumClock == _IOSC_CLK)
    {
        // Bit1 : 0 --> CPU CLK Source Select to xtal
        ScalerSetBit(PFF_ED_MCU_CONTROL, ~_BIT1, 0x00);

        // Both Mcu/Flash first stage divider
        ScalerSetBit(PFF_ED_MCU_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), ((_FLASH_CLK_PS_DIV & 0x0F) << 2));

        // Flash second stage divider
        ScalerSetBit(PFF_E9_MCU_CLK_CONTROL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_FLASH_2_CLK_PS_DIV & 0x0F));

        ScalerGlobalCtrlSetSys32ClkSrc(_IOSC_CLK);

        // Set Timer Count
        ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_SAVING_MODE);
    }
    else if(enumClock == _EXT_XTAL_CLK)
    {
        if(GET_REG_XTAL_CLK_SEL() == _EXT_XTAL_CLK)
        {
            ScalerGlobalCrystalClkSel(_IOSC_CLK);

            bXtalClkSwitch = _TRUE;
        }

        // Bit1 : 0 --> CPU CLK Source Select to xtal
        ScalerSetBit(PFF_ED_MCU_CONTROL, ~_BIT1, 0x00);

        // Both Mcu/Flash first stage divider
        ScalerSetBit(PFF_ED_MCU_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), ((_FLASH_CLK_IN_DIV & 0x0F) << 2));

        // Flash second stage divider
        ScalerSetBit(PFF_E9_MCU_CLK_CONTROL_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_FLASH_2_CLK_IN_DIV & 0x0F));

        if(bXtalClkSwitch == _TRUE)
        {
            ScalerGlobalCrystalClkSel(_EXT_XTAL_CLK);
        }

        ScalerGlobalCtrlSetSys32ClkSrc(_EXT_XTAL_CLK);

        // Set Timer Count
        ScalerTimerSetTimerCount(_TIMER_OPERATION_INITIAL_MODE);
    }
}

#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
//--------------------------------------------------
// Description  : Set Flash Clock Divider.
// Input Value  : ClkDiv --> Flash Clock Divider
// Output Value : None
//--------------------------------------------------
void ScalerMcuFlashClockDiv(EnumFlashClkDiv enumClkDiv)
{
    ScalerSetBit(PFF_ED_MCU_CONTROL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), ((enumClkDiv & 0x0F) << 2));
}

//--------------------------------------------------
// Description  : Set Flash & Mcu Divider when OSD is running.
// Input Value  : Fast or Low Speed
// Output Value : None
//--------------------------------------------------
void ScalerMcuSwitchFlashMcuFastSpeed(bit bEnable)
{
    // Only Take Effect when Flash Clk is From M2PLL
    if(ScalerGetBit(PFF_ED_MCU_CONTROL, _BIT1) == _BIT1)
    {
        if(bEnable == _ENABLE)
        {
            // Don't Switch Again If It's Already Using Fast Div
            if((ScalerGetBit(PFF_ED_MCU_CONTROL, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) >> 2) != _FLASH_CLK_FAST_DIV)
            {
                // Switch Flash and MCU Clock to high speed
                ScalerMcuFlashClockDiv(_FLASH_CLK_FAST_DIV);
                // Reload Timer Count
                ScalerTimerSetTimerCount(_TIMER_OPERATION_OSD_MODE);
            }
        }
        else if(bEnable == _DISABLE)
        {
            // Don't Switch Again If It's Already Using Normal Div
            if((ScalerGetBit(PFF_ED_MCU_CONTROL, (_BIT5 | _BIT4 | _BIT3 | _BIT2)) >> 2) != _FLASH_CLK_DIV)
            {
                // Switch Flash and MCU Clock to low speed
                ScalerMcuFlashClockDiv(_FLASH_CLK_DIV);
                // Reload Timer Count
                ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_NORMAL_MODE);
            }
        }
    }
}
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : SARADC Clock Select.
// Input Value  : enumClock --> _M2PLL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuSarAdcClkSel(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // ADC clk from external Xtal and div by 4 to obtain clk target 3MHz
        MCU_FF0D_ADC_CLK_DIV = (_EXT_XTAL / 3000) & 0x7F;

#if((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))
        MCU_FD3F_ADC_CLK_DIV = (_EXT_XTAL / 3000) & 0x7F;
#endif
    }
    else
    {
        // ADC clk from IOSC(27M) and div by 9 to obtain clk target 3MHz
        MCU_FF0D_ADC_CLK_DIV = (_HW_INTERNAL_OSC_XTAL / 3000) & 0x7F;

#if((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))
        MCU_FD3F_ADC_CLK_DIV = (_HW_INTERNAL_OSC_XTAL / 3000) & 0x7F;
#endif
    }
}

#if(_LOW_SPEED_ADC_POWER_REDUCE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : SARADC Power Control
// Input Value  : EnumAdcPowerControl
// Output Value : None
//--------------------------------------------------
void ScalerMcuSarAdcPowerControl(EnumAdcPowerControl enumAdcPowerControl, EnumAdcPowerDelay enumAdcPowerDelay)
{
    if(enumAdcPowerControl == _ADC_POWER_ENABLE)
    {
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        // Set Auto Mode
        ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT5, _BIT5);

        // ADC Start Scan
        ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);

#elif((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))

        // ---------------------------
        // LSADC_0 Power Control
        // ---------------------------

        // Keep Enable for Other Use
#if((_ADC_DETECT_INT_BY_ADC_CHANNEL <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) || (_ADC_DETECT_INT_BY_ADC_CHANNEL >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3))
        // LSADC_0 Power Enable/Disable
        ScalerSetBit(PFD_39_ADC_ANALOG_CONFIG, ~_BIT2, _BIT2);

        // Set Auto Mode
        ScalerSetBit(PFD_3A_ADC_ACONTROL, ~_BIT5, _BIT5);

        // ADC Start Scan
        ScalerSetBit(PFD_3A_ADC_ACONTROL, ~_BIT7, _BIT7);
#endif

        // ---------------------------
        // LSADC_1 Power Control
        // ---------------------------

        // Keep Enable for Other Use
#if((_ADC_DETECT_INT_BY_ADC_CHANNEL <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) || (_ADC_DETECT_INT_BY_ADC_CHANNEL >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3))
        // LSADC_1 Power Enable/Disable
        ScalerSetBit(PFF_02_ADC_ANALOG_CONFIG, ~_BIT2, _BIT2);

        // Set Auto Mode
        ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT5, _BIT5);

        // ADC Start Scan
        ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);
#endif
#endif

        // ---------------------------
        // Delay for ADC Switch Data
        // ---------------------------
        if(enumAdcPowerDelay == _ADC_POWER_DELAY_ENABLE)
        {
            // If Wait Time = 0
            // 8-Bit ADC Switch Time under PS:  1 / 3MHz * (9 * 4 Channel + 4 Clock) = 13.3us
            DELAY_XUS(50);
        }
    }
    else
    {
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

        // ADC Stop Scan
        ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT7, 0x00);

        // Disable Auto Mode
        ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT5, 0x00);

#elif((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))

        // ---------------------------
        // LSADC_0 Power Control
        // ---------------------------

        // Keep Enable for Other Use
#if((_ADC_DETECT_INT_BY_ADC_CHANNEL <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) || (_ADC_DETECT_INT_BY_ADC_CHANNEL >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3))
        // ADC Stop Scan
        ScalerSetBit(PFD_3A_ADC_ACONTROL, ~_BIT7, 0x00);

        // Disable Auto Mode
        ScalerSetBit(PFD_3A_ADC_ACONTROL, ~_BIT5, 0x00);

        // LSADC_0 Power Enable/Disable
        ScalerSetBit(PFD_39_ADC_ANALOG_CONFIG, ~_BIT2, 0x00);
#endif

        // ---------------------------
        // LSADC_1 Power Control
        // ---------------------------

        // Keep Enable for Other Use
#if((_ADC_DETECT_INT_BY_ADC_CHANNEL <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) || (_ADC_DETECT_INT_BY_ADC_CHANNEL >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3))
        // ADC Stop Scan
        ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT7, 0x00);

        // Disable Auto Mode
        ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT5, 0x00);

        // LSADC_1 Power Enable/Disable
        ScalerSetBit(PFF_02_ADC_ANALOG_CONFIG, ~_BIT2, 0x00);
#endif
#endif
    }
}
#endif

#if((_DP_SUPPORT == _ON) && (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : DP Cable ID Detect
// Input Value  : EnumInputPort
// Output Value : EnumDpCableIDResult
//--------------------------------------------------
EnumDpCableIDResult ScalerMcuSarAdcDpCableIdDetect(EnumInputPort enumInputPort)
{
    BYTE ucAdcResult = _DP_CABLE_ID_RESULT_LOW;

#if(_LOW_SPEED_ADC_POWER_REDUCE_SUPPORT == _ON)
    // Enable ADC Power
    ScalerMcuSarAdcPowerControl(_ADC_POWER_ENABLE, _ADC_POWER_DELAY_DISABLE);
#endif

    // Get 5-Bit SARADC Result via DP por mapping
    switch(enumInputPort)
    {
#if(_D0_DP_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            // Switch Port
            PCB_DP_UHBR_CABLE_ID_SWITCH_PORT_CONTROL(_D0_INPUT_PORT);

            // Delay for PCB Switch Debounce
            ScalerTimerDelayXms(_DP_UHBR_CABLE_ID_SWITCH_PORT_DELAY_TIME);

            // Delay for PCB Capacitor Charge
            DELAY_XUS(_DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME);

            // Get ADC Value
            ucAdcResult = PCB_DP_UHBR_D0_CABLE_ID_DETECT_ADC_PIN() >> 3;

            break;
#endif

#if(_D1_DP_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            // Switch Port
            PCB_DP_UHBR_CABLE_ID_SWITCH_PORT_CONTROL(_D1_INPUT_PORT);

            // Delay for PCB Switch Debounce
            ScalerTimerDelayXms(_DP_UHBR_CABLE_ID_SWITCH_PORT_DELAY_TIME);

            // Delay for PCB Capacitor Charge
            DELAY_XUS(_DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME);

            // Get ADC Value
            ucAdcResult = PCB_DP_UHBR_D1_CABLE_ID_DETECT_ADC_PIN() >> 3;

            break;
#endif

#if(_D2_DP_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            // Switch Port
            PCB_DP_UHBR_CABLE_ID_SWITCH_PORT_CONTROL(_D2_INPUT_PORT);

            // Delay for PCB Switch Debounce
            ScalerTimerDelayXms(_DP_UHBR_CABLE_ID_SWITCH_PORT_DELAY_TIME);

            // Delay for PCB Capacitor Charge
            DELAY_XUS(_DP_UHBR_CABLE_ID_ADC_CAPACITOR_CHARGE_TIME);

            // Get ADC Value
            ucAdcResult = PCB_DP_UHBR_D2_CABLE_ID_DETECT_ADC_PIN() >> 3;

            break;
#endif

        default:
            break;
    }

#if(_LOW_SPEED_ADC_POWER_REDUCE_SUPPORT == _ON)
    // Disable ADC Power
    ScalerMcuSarAdcPowerControl(_ADC_POWER_DISABLE, _ADC_POWER_DELAY_DISABLE);
#endif

    // Get DP Cable ID Range via 5-Bit SARADC
    if(ucAdcResult <= 2)
    {
        // PU = None
        // PD = 100kOhm
        // Vin = 0V
        // Code_5Bit = 0

        return _DP_CABLE_ID_RESULT_LOW;
    }
    if(ucAdcResult <= 7)
    {
        // PU = 680kOhm
        // PD = 100kOhm
        // Vin = 3.3 * (100) / (100 + 680) = 0.423V
        // Code_5Bit = 0.423V * (32 / 3.3) = 4

        return _DP_CABLE_ID_RESULT_MID;
    }
    else
    {
        // PU = 220kOhm
        // PD = 100kOhm
        // Vin = 3.3 * (100) / (100 + 220) = 1.031V
        // Code_5Bit = 1.031V * (32 / 3.3) = 10

        return _DP_CABLE_ID_RESULT_HIGH;
    }
}
#endif // End of #if((_DP_SUPPORT == _ON) && (_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON))

#if(_ADC_DETECT_INT_BY_ADC_CHANNEL != _ADC_DET_INT_ADC_MAPPING_NONE)
//--------------------------------------------------
// Description  : Initial Int Detect By ADC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuAdcLsAdcDetectIntInitial(void)
{
    // Disable INT
    ScalerMcuAdcLsAdcInOutCompIntControl(_ADC_DETECT_INT_BY_ADC_CHANNEL, _ADC_INT_DISABLE);

    // Set AC_DET Pin ON
    PCB_ADC_INTERRUPT_CONTROL(_ADC_INTERRUPT_CONTROL_PIN_ON);
}

//--------------------------------------------------
// Description  : LS ADC Range Detection IRQ Control
// Input Value  : ucChannel : _ADC_DETECT_INT_BY_ADC_CHANNEL
//                enumAdcIntControl : _ADC_INT_ENABLE / _ADC_INT_DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerMcuAdcLsAdcInOutCompIntControl(BYTE ucChannel, EnumAdcIntControl enumAdcIntControl)
{
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)

    if(enumAdcIntControl == _ADC_INT_ENABLE)
    {
        // [0xFF0E] ADC0: Clear Flag & Enable INT
        ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0))), ((_BIT4 | _BIT0) << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0)));
    }
    else
    {
        // [0xFF0E] ADC0: Reset Threshold
        ScalerMcuAdcLsAdcInOutCompIntSetting(ucChannel, 0x0000, 0x03FF);

        // [0xFF0E] ADC0: Disable INT, but don't clear flag
        ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0))), 0x00);
    }

    // Clear INT Flag
    ScalerMcuAdcLsAdcInOutCompIntClearFlag(ucChannel);

    // ADC Start Scan
    ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);

#elif((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))
    if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3))
    {
        if(enumAdcIntControl == _ADC_INT_ENABLE)
        {
            // [0xFD40] ADC0: Clear Flag & Enable INT
            ScalerSetBit(PFD_40_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0))), ((_BIT4 | _BIT0) << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0)));
        }
        else
        {
            // [0xFD40] ADC0: Reset Threshold
            ScalerMcuAdcLsAdcInOutCompIntSetting(ucChannel, 0x0000, 0x03FF);

            // [0xFD40] ADC0: Disable INT, but don't clear flag
            ScalerSetBit(PFD_40_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0))), 0x00);
        }
    }
    else if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3))
    {
        if(enumAdcIntControl == _ADC_INT_ENABLE)
        {
            // [0xFF0E] ADC0: Clear Flag & Enable INT
            ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0))), ((_BIT4 | _BIT0) << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0)));
        }
        else
        {
            // [0xFF0E] ADC0: Reset Threshold
            ScalerMcuAdcLsAdcInOutCompIntSetting(ucChannel, 0x0000, 0x03FF);

            // [0xFF0E] ADC0: Disable INT, but don't clear flag
            ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | (_BIT0 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0))), 0x00);
        }
    }

    // Clear INT Flag
    ScalerMcuAdcLsAdcInOutCompIntClearFlag(ucChannel);

    // ADC Start Scan
    ScalerSetBit(PFD_3A_ADC_ACONTROL, ~_BIT7, _BIT7);
    ScalerSetBit(PFF_08_ADC_ACONTROL, ~_BIT7, _BIT7);
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : ADC Vbus Range Detection IRQ Setting
// Input Value  : ucChannel : _ADC_DETECT_INT_BY_ADC_CHANNEL
//                usHigh / usLow : High / Low Threshold
// Output Value : None
//--------------------------------------------------
void ScalerMcuAdcLsAdcInOutCompIntSetting(BYTE ucChannel, WORD usHigh, WORD usLow)
{
    // Must be In-Range

#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh >> 5;
    usHigh = ((usHigh >= 0x001F) ? 0x001F : (usHigh & 0x001F));

    usLow = usLow >> 5;
    usLow = ((usLow >= 0x001E) ? 0x001E : (usLow & 0x001F));

    // Set High/Low Threshold (250mA/bit for max current 8A)
    ScalerSetByte((PFF_0F_ADC0_THRESHOLD_H + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0) * 2)), (BYTE)(usHigh << 3));
    ScalerSetByte((PFF_10_ADC0_THRESHOLD_L + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0) * 2)), (BYTE)(usLow << 3));

#elif((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))
    // Clip High/Low Threshold to Valid Range
    usHigh = usHigh >> 2;
    usHigh = ((usHigh >= 0x00FF) ? 0x00FF : (usHigh & 0x00FF));

    usLow = usLow >> 2;
    usLow = ((usLow >= 0x00FE) ? 0x00FE : (usLow & 0x00FF));

    // Set High/Low Threshold (31mA/bit for max current 8A)
    if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3))
    {
        ScalerSetByte((PFD_F7_ADC0_THRESHOLD_H + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) * 2)), (BYTE)(usHigh));
        ScalerSetByte((PFD_F8_ADC0_THRESHOLD_L + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) * 2)), (BYTE)(usLow));
    }
    else if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3))
    {
        ScalerSetByte((PFF_0F_ADC0_THRESHOLD_H + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) * 2)), (BYTE)(usHigh));
        ScalerSetByte((PFF_10_ADC0_THRESHOLD_L + ((ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) * 2)), (BYTE)(usLow));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}

//--------------------------------------------------
// Description  : Clear ADC INT Flag
// Input Value  : ucChannel : _ADC_DETECT_INT_BY_ADC_CHANNEL
// Output Value : None
//--------------------------------------------------
void ScalerMcuAdcLsAdcInOutCompIntClearFlag(BYTE ucChannel)
{
    // Clear Flag
#if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
    ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0)), (_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0)));

#elif((_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_1) || (_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_3))
    if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_3))
    {
        ScalerSetBit(PFD_40_AUTO_MODE_CTRL01, ~(_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0)), (_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_0_0)));
    }
    else if((ucChannel >= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0) && (ucChannel <= _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_3))
    {
        ScalerSetBit(PFF_0E_AUTO_MODE_CTRL01, ~(_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0)), (_BIT4 << (ucChannel - _ADC_DET_INT_ADC_MAPPING_LS_ADC_1_0)));
    }
#endif // End of #if(_HW_MCU_SARADC_GEN == _HW_SARADC_GEN_0)
}
#endif
#endif // End of #if(_LOW_SPEED_ADC_SUPPORT == _ON)

#if(_PWM_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PWM Clock Switch.
// Input Value  : Clock --> _M2PLL_CLK/_EXT_XTAL_CLK(_IOSC_CLK)
// Output Value : None
//--------------------------------------------------
void ScalerMcuPwmClockSel(EnumClkSel enumClock)
{
    WORD usCLKDiv = 0;
    WORD usFrequency = 0;

    enumClock = enumClock;
    usCLKDiv = usCLKDiv;
    usFrequency = usFrequency;

    ////////////////////////////////
    // Adjust PWMx divider: M & N //
    ////////////////////////////////

#if((_PWM0_EN == _ON) || (_PWM0_PSAV_EN == _ON) || (_PWM0_PDOW_EN == _ON))
#if(_PWM0_BYPASS_MODE_EN == _OFF)

    // Get PWM0 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT1 | _BIT0)))
    // N = (((WORD)((MCU_FF3D_PWM01_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF3E_PWM0_N_LSB) + 1)

    usCLKDiv = (0x01 << ScalerGetBit(PFF_3B_PWM03_M, (_BIT1 | _BIT0))) * (((WORD)(ScalerGetBit(PFF_3D_PWM01_N_MSB, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF3E_PWM0_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT0) == _BIT0)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_HW_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT0;
    }
    else
    {
        // Switch Clock To IOSC/EXT_XTAL
        MCU_FF3A_PWM_CK_SEL &= ~_BIT0;
    }

    ScalerMcuPwmAdjustFrequency(_PWM0, usFrequency);

#endif // END of #if(_PWM0_BYPASS_MODE_EN == _OFF)
#endif // End of #if((_PWM0_EN == _ON) || (_PWM0_PSAV_EN == _ON) || (_PWM0_PDOW_EN == _ON))

#if((_PWM1_EN == _ON) || (_PWM1_PSAV_EN == _ON) || (_PWM1_PDOW_EN == _ON))
#if(_PWM1_BYPASS_MODE_EN == _OFF)

    // Get PWM1 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT3 | _BIT2)))
    // N = (((WORD)((MCU_FF3D_PWM01_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 8) | MCU_FF3F_PWM1_N_LSB) + 1)
    usCLKDiv = (0x01 << (ScalerGetBit(PFF_3B_PWM03_M, (_BIT3 | _BIT2)) >> 2)) * (((WORD)(ScalerGetBit(PFF_3D_PWM01_N_MSB, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF3F_PWM1_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT1) == _BIT1)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_HW_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT1;
    }
    else
    {
        // Switch Clock To IOSC/EXT_XTAL
        MCU_FF3A_PWM_CK_SEL &= ~_BIT1;
    }

    ScalerMcuPwmAdjustFrequency(_PWM1, usFrequency);

#endif // END of #if(_PWM1_BYPASS_MODE_EN == _OFF)
#endif // End of #if((_PWM1_EN == _ON) || (_PWM1_PSAV_EN == _ON) || (_PWM1_PDOW_EN == _ON) || (_PWM1_BYPASS_MODE_EN == _OFF))

#if((_PWM2_EN == _ON) || (_PWM2_PSAV_EN == _ON) || (_PWM2_PDOW_EN == _ON))
#if(_PWM2_BYPASS_MODE_EN == _OFF)

    // Get PWM2 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT5 | _BIT4)))
    // N = (((WORD)((MCU_FF40_PWM23_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF41_PWM2_N_LSB) + 1)
    usCLKDiv = (0x01 << (ScalerGetBit(PFF_3B_PWM03_M, (_BIT5 | _BIT4)) >> 4)) * (((WORD)(ScalerGetBit(PFF_40_PWM23_N_MSB, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF41_PWM2_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT2) == _BIT2)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_HW_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT2;
    }
    else
    {
        // Switch Clock To IOSC/EXT_XTAL
        MCU_FF3A_PWM_CK_SEL &= ~_BIT2;
    }

    ScalerMcuPwmAdjustFrequency(_PWM2, usFrequency);

#endif // END of #if(_PWM2_BYPASS_MODE_EN == _OFF)
#endif // End of #if((_PWM2_EN == _ON) || (_PWM2_PSAV_EN == _ON) || (_PWM2_PDOW_EN == _ON) ||(_PWM2_BYPASS_MODE_EN == _OFF))

#if((_PWM3_EN == _ON) || (_PWM3_PSAV_EN == _ON) || (_PWM3_PDOW_EN == _ON))
#if(_PWM3_BYPASS_MODE_EN == _OFF)

    // Get PWM3 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT7 | _BIT6)))
    // N = (((WORD)((MCU_FF40_PWM23_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF42_PWM3_N_LSB) + 1)
    usCLKDiv = (0x01 << (ScalerGetBit(PFF_3B_PWM03_M, (_BIT7 | _BIT6)) >> 6)) * (((WORD)(ScalerGetBit(PFF_40_PWM23_N_MSB, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF42_PWM3_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT3) == _BIT3)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)

        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_HW_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT3;
    }
    else
    {
        // Switch Clock To IOSC/EXT_XTAL
        MCU_FF3A_PWM_CK_SEL &= ~_BIT3;
    }

    ScalerMcuPwmAdjustFrequency(_PWM3, usFrequency);

#endif // END of #if(_PWM3_BYPASS_MODE_EN == _OFF)
#endif // End of #if((_PWM3_EN == _ON) || (_PWM3_PSAV_EN == _ON) || (_PWM3_PDOW_EN == _ON) || (_PWM3_BYPASS_MODE_EN == _OFF))

#if((_PWM4_EN == _ON) || (_PWM4_PSAV_EN == _ON) || (_PWM4_PDOW_EN == _ON))
#if(_PWM4_BYPASS_MODE_EN == _OFF)

    // Get PWM4 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3C_PWM45_M & (_BIT1 | _BIT0)))
    // N = (((WORD)((MCU_FF43_PWM45_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 8) | MCU_FF44_PWM4_N_LSB) + 1)
    usCLKDiv = (0x01 << ScalerGetBit(PFF_3C_PWM45_M, (_BIT1 | _BIT0))) * (((WORD)(ScalerGetBit(PFF_43_PWM45_N_MSB, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF44_PWM4_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT4) == _BIT4)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_HW_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT4;
    }
    else
    {
        // Switch Clock To IOSC/EXT_XTAL
        MCU_FF3A_PWM_CK_SEL &= ~_BIT4;
    }

    ScalerMcuPwmAdjustFrequency(_PWM4, usFrequency);

#endif // END of #if(_PWM4_BYPASS_MODE_EN == _OFF)
#endif // End of #if((_PWM4_EN == _ON) || (_PWM4_PSAV_EN == _ON) || (_PWM4_PDOW_EN == _ON) || (_PWM4_BYPASS_MODE_EN == _OFF))

#if((_PWM5_EN == _ON) || (_PWM5_PSAV_EN == _ON) || (_PWM5_PDOW_EN == _ON))
#if(_PWM5_BYPASS_MODE_EN == _OFF)

    // Get PWM5 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3C_PWM45_M & (_BIT1 | _BIT0)))
    // N = (((WORD)((MCU_FF43_PWM45_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF44_PWM4_N_LSB) + 1)
    usCLKDiv = (0x01 << (ScalerGetBit(PFF_3C_PWM45_M, (_BIT3 | _BIT2)) >> 2)) * (((WORD)(ScalerGetBit(PFF_43_PWM45_N_MSB, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF45_PWM5_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT5) == _BIT5)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_HW_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT5;
    }
    else
    {
        // Switch Clock To IOSC/EXT_XTAL
        MCU_FF3A_PWM_CK_SEL &= ~_BIT5;
    }

    ScalerMcuPwmAdjustFrequency(_PWM5, usFrequency);

#endif // END of #if(_PWM5_BYPASS_MODE_EN == _OFF)
#endif // End of #if((_PWM5_EN == _ON) || (_PWM5_PSAV_EN == _ON) || (_PWM5_PDOW_EN == _ON) || (_PWM5_BYPASS_MODE_EN == _OFF))
}

//--------------------------------------------------
// Description  : Adjust PWM reset by DVS
// Input Value  : ucPwmType --> _BACKLIGHT_PWM/_AUDIO_VOLUME...
//                bStatus --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerMcuPwmAdjustResetByDvs(BYTE ucPwmType, bit bStatus)
{
    BYTE ucMask = 0;

    switch(ucPwmType)
    {
        case _PWM0:
            ucMask = _BIT0;
            break;
        case _PWM1:
            ucMask = _BIT1;
            break;
        case _PWM2:
            ucMask = _BIT2;
            break;
        case _PWM3:
            ucMask = _BIT3;
            break;
        case _PWM4:
            ucMask = _BIT4;
            break;
        case _PWM5:
            ucMask = _BIT5;
            break;
        default:
            break;
    }

    if(ucMask != 0)
    {
        if(bStatus == _ENABLE)
        {
            MCU_FF47_PWM_VS_CTRL |= ucMask;
        }
        else
        {
            MCU_FF47_PWM_VS_CTRL &= ~ucMask;
        }
    }
}

//--------------------------------------------------
// Description  : PWM Clock Frequency.
// Input Value  : ucPwmType --> _BACKLIGHT_PWM/_AUDIO_VOLUME...
//                ucFrequency --> Frequency
// Output Value : None
//--------------------------------------------------
bit ScalerMcuPwmAdjustFrequency(BYTE ucPwmType, WORD usFrequency)
{
    BYTE ucPWM_M = 0;
    WORD usPWM_N = 0;
    bit bCheckResult = _FALSE;

    // Check if PWM clk is M2PLL or IOSC
    if((MCU_FF3A_PWM_CK_SEL & ucPwmType) == ucPwmType)
    {
        // Set limit for Pwm frequency
        if(usFrequency < _PWM_ACT_MODE_FREQ_LOW_BOUND)
        {
            usFrequency = _PWM_ACT_MODE_FREQ_LOW_BOUND;
            bCheckResult = _FALSE;
        }
        else if(usFrequency > _PWM_ACT_MODE_FREQ_UPPER_BOUND)
        {
            usFrequency = _PWM_ACT_MODE_FREQ_UPPER_BOUND;
            bCheckResult = _FALSE;
        }
        else
        {
            bCheckResult = _TRUE;
        }
    }
    else
    {
        // Set limit for Pwm frequency
        if(usFrequency < _PWM_PSPD_MODE_FREQ_LOW_BOUND)
        {
            usFrequency = _PWM_PSPD_MODE_FREQ_LOW_BOUND;
            bCheckResult = _FALSE;
        }
        else if(usFrequency > _PWM_PSPD_MODE_FREQ_UPPER_BOUND)
        {
            usFrequency = _PWM_PSPD_MODE_FREQ_UPPER_BOUND;
            bCheckResult = _FALSE;
        }
        else
        {
            bCheckResult = _TRUE;
        }
    }

#if(_PWM_FREQ_DVSRST_CHECK == _ON)
    if(usFrequency >= _PWM_FREQ_DVSRST_BOUND)
    {
        // Disable PWM reset by DVS
#if(_BACKLIGHT_PWM == _PWM0)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT0;

#elif(_BACKLIGHT_PWM == _PWM1)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT1;

#elif(_BACKLIGHT_PWM == _PWM2)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT2;

#elif(_BACKLIGHT_PWM == _PWM3)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT3;

#elif(_BACKLIGHT_PWM == _PWM4)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT4;

#elif(_BACKLIGHT_PWM == _PWM5)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT5;
#endif
    }
    else
    {
        // Enable PWM reset by DVS
#if(_BACKLIGHT_PWM == _PWM0)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM0_RST_EN);

#elif(_BACKLIGHT_PWM == _PWM1)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM1_RST_EN << 1);

#elif(_BACKLIGHT_PWM == _PWM2)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM2_RST_EN << 2);

#elif(_BACKLIGHT_PWM == _PWM3)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM3_RST_EN << 3);

#elif(_BACKLIGHT_PWM == _PWM4)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM4_RST_EN << 4);

#elif(_BACKLIGHT_PWM == _PWM5)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM5_RST_EN << 5);
#endif
    }
#endif

    // Check if PWM clk is M2PLL or IOSC
    if((MCU_FF3A_PWM_CK_SEL & ucPwmType) == ucPwmType)
    {
        for(ucPWM_M = 0; ucPWM_M < 4; ucPWM_M++)
        {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
            // HW Using M2Pll / 2 as PWM Reference Clock Source
            // Calculate N Divider for M2PLL / 2
            usPWM_N = ((DWORD)(((((DWORD)_M2PLL_CLK_KHZ * 1000) / ((DWORD)usFrequency * (0x01 << ucPWM_M) * _PWM_DUT_RESOLUTION)) + 1) / 2) - 1);
#else
            // Calculate N Divider for Define [_M2PLL_CLK_KHZ]
            usPWM_N = ((DWORD)(((((DWORD)_M2PLL_CLK_KHZ * 1000 * 2) / ((DWORD)usFrequency * (0x01 << ucPWM_M) * _PWM_DUT_RESOLUTION)) + 1) / 2) - 1);
#endif

            if(usPWM_N < 4096)
            {
                break;
            }
        }
    }
    else
    {
        for(ucPWM_M = 0; ucPWM_M < 4; ucPWM_M++)
        {
            // Calculate N Divider for IOSC 28MHz
            usPWM_N = ((DWORD)(((((DWORD)_HW_INTERNAL_OSC_XTAL * 1000 * 2) / ((DWORD)usFrequency * (0x01 << ucPWM_M) * _PWM_DUT_RESOLUTION)) + 1) / 2) - 1);

            if(usPWM_N < 4096)
            {
                break;
            }
        }
    }

    // Load M/N divider to corresponding register
    switch(ucPwmType)
    {
#if((_PWM0_EN == _ON) || (_PWM0_PSAV_EN == _ON) || (_PWM0_PDOW_EN == _ON))
        case _PWM0:

            ScalerSetBit(PFF_3B_PWM03_M, ~(_BIT1 | _BIT0), (ucPWM_M));
            ScalerSetBit(PFF_3D_PWM01_N_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)((usPWM_N >> 8) & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
            MCU_FF3E_PWM0_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT0;

            break;
#endif

#if((_PWM1_EN == _ON) || (_PWM1_PSAV_EN == _ON) || (_PWM1_PDOW_EN == _ON))
        case _PWM1:

            ScalerSetBit(PFF_3B_PWM03_M, ~(_BIT3 | _BIT2), (ucPWM_M << 2));
            ScalerSetBit(PFF_3D_PWM01_N_MSB, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (BYTE)((usPWM_N >> 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)));
            MCU_FF3F_PWM1_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT1;

            break;
#endif

#if((_PWM2_EN == _ON) || (_PWM2_PSAV_EN == _ON) || (_PWM2_PDOW_EN == _ON))
        case _PWM2:

            ScalerSetBit(PFF_3B_PWM03_M, ~(_BIT5 | _BIT4), (ucPWM_M << 4));
            ScalerSetBit(PFF_40_PWM23_N_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)((usPWM_N >> 8) & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
            MCU_FF41_PWM2_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT2;

            break;
#endif

#if((_PWM3_EN == _ON) || (_PWM3_PSAV_EN == _ON) || (_PWM3_PDOW_EN == _ON))
        case _PWM3:

            ScalerSetBit(PFF_3B_PWM03_M, ~(_BIT7 | _BIT6), (ucPWM_M << 6));
            ScalerSetBit(PFF_40_PWM23_N_MSB, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (BYTE)((usPWM_N >> 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)));
            MCU_FF42_PWM3_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT3;

            break;
#endif

#if((_PWM4_EN == _ON) || (_PWM4_PSAV_EN == _ON) || (_PWM4_PDOW_EN == _ON))
        case _PWM4:

            ScalerSetBit(PFF_3C_PWM45_M, ~(_BIT1 | _BIT0), (ucPWM_M));
            ScalerSetBit(PFF_43_PWM45_N_MSB, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (BYTE)((usPWM_N >> 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)));
            MCU_FF44_PWM4_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT4;

            break;
#endif

#if((_PWM5_EN == _ON) || (_PWM5_PSAV_EN == _ON) || (_PWM5_PDOW_EN == _ON))
        case _PWM5:

            ScalerSetBit(PFF_3C_PWM45_M, ~(_BIT3 | _BIT2), (ucPWM_M << 2));
            ScalerSetBit(PFF_43_PWM45_N_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (BYTE)((usPWM_N >> 8) & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
            MCU_FF45_PWM5_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT5;

            break;
#endif
        default:
            break;
    }
    return bCheckResult;
}

#if(_PWM_BYPASS_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PWM Clock ByPassMode Frequency Setting.
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerMcuPwmByPassModeSettingFrequency(BYTE ucPwmType, WORD usTotalcont)
{
    switch(ucPwmType)
    {
        case _PWM0:

            MCU_FF3A_PWM_CK_SEL |= _BIT0; // PWM clk from M2PLL/2=175.5MHz
            MCU_FF53_PWM_DUT_TYPE |= _BIT0; // PWM Duty 8bits
            ScalerSetBit(PFF_4C_PWM01L_DUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((usTotalcont >> 1) & 0x0F));
            MCU_FF4A_PWM0H_DUT = ((usTotalcont >> 1) >> 4); // Period = 88 , 50% duty = 44
            MCU_FF49_PWM_CK &= ~_BIT0;
            MCU_FF54_PWM_CNT_MODE |= _BIT0; // PWM as counter mode
            ScalerSetBit(PFF_90_PWM01_TOTALCNT_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usTotalcont)  & 0x0F));
            MCU_FF91_PWM0_TOTALCNT_LSB = LOBYTE(usTotalcont); // (351MHz/2) / 88 = 1994KHz
            MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM0_RST_EN); // Enable PWM reset by DVS

            break;

        case _PWM1:

            MCU_FF3A_PWM_CK_SEL |= _BIT1; // PWM clk from M2PLL/2=175.5MHz
            MCU_FF48_PWM_EN |= _BIT1; // PWM Enable
            MCU_FF53_PWM_DUT_TYPE |= _BIT1; // PWM Duty 8bits
            ScalerSetBit(PFF_4C_PWM01L_DUT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (((usTotalcont >> 1) << 4) & 0xF0));
            MCU_FF4B_PWM1H_DUT = ((usTotalcont >> 1) >> 4); // Period = 88 , 50% duty = 44
            MCU_FF49_PWM_CK &= ~_BIT1;
            MCU_FF54_PWM_CNT_MODE |= _BIT1; // PWM as counter mode
            ScalerSetBit(PFF_90_PWM01_TOTALCNT_MSB, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((HIBYTE(usTotalcont)  & 0x0F) << 4));
            MCU_FF92_PWM1_TOTALCNT_LSB = LOBYTE(usTotalcont); // (351MHz/2) / 88 = 1994KHz
            MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM1_RST_EN << 1);

            break;

        case _PWM2:

            MCU_FF3A_PWM_CK_SEL |= _BIT2; // PWM clk from M2PLL/2=175.5MHz
            MCU_FF48_PWM_EN |= _BIT2; // PWM Enable
            MCU_FF53_PWM_DUT_TYPE |= _BIT2; // PWM Duty 8bits
            ScalerSetBit(PFF_4F_PWM23L_DUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((usTotalcont >> 1) & 0x0F));
            MCU_FF4D_PWM2H_DUT = ((usTotalcont >> 1) >> 4); // Period = 88 , 50% duty = 44
            MCU_FF49_PWM_CK &= ~_BIT2;
            MCU_FF54_PWM_CNT_MODE |= _BIT2; // PWM2 as counter mode
            ScalerSetBit(PFF_93_PWM23_TOTALCNT_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usTotalcont)  & 0x0F));
            MCU_FF94_PWM2_TOTALCNT_LSB = LOBYTE(usTotalcont); // (351MHz/2) / 88 = 1994KHz
            MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM2_RST_EN << 2);

            break;

        case _PWM3:

            MCU_FF3A_PWM_CK_SEL |= _BIT3; // PWM clk from M2PLL/2=175.5MHz
            MCU_FF48_PWM_EN |= _BIT3; // PWM3 Enable
            MCU_FF53_PWM_DUT_TYPE |= _BIT3; // PWM Duty 8bits
            ScalerSetBit(PFF_4F_PWM23L_DUT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (((usTotalcont >> 1) << 4) & 0xF0));
            MCU_FF4E_PWM3H_DUT = ((usTotalcont >> 1) >> 4); // Period = 88 , 50% duty = 44
            MCU_FF49_PWM_CK &= ~_BIT3;
            MCU_FF54_PWM_CNT_MODE |= _BIT3; // PWM as counter mode
            ScalerSetBit(PFF_93_PWM23_TOTALCNT_MSB, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((HIBYTE(usTotalcont)  & 0x0F) << 4));
            MCU_FF95_PWM3_TOTALCNT_LSB = LOBYTE(usTotalcont); // (351MHz/2) / 88 = 1994KHz
            MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM3_RST_EN << 3);

            break;

        case _PWM4:

            MCU_FF3A_PWM_CK_SEL |= _BIT4; // PWM clk from M2PLL/2=175.5MHz
            MCU_FF48_PWM_EN |= _BIT4; // PWM Enable
            MCU_FF53_PWM_DUT_TYPE |= _BIT4; // PWM Duty 8bits
            ScalerSetBit(PFF_52_PWM45L_DUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((usTotalcont >> 1) & 0x0F));
            MCU_FF50_PWM4H_DUT = ((usTotalcont >> 1) >> 4); // Period = 88 , 50% duty = 44
            MCU_FF49_PWM_CK &= ~_BIT4;
            MCU_FF54_PWM_CNT_MODE |= _BIT4; // PWM4 as counter mode
            ScalerSetBit(PFF_96_PWM45_TOTALCNT_MSB, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((HIBYTE(usTotalcont) & 0x0F) << 4));
            MCU_FF97_PWM4_TOTALCNT_LSB = LOBYTE(usTotalcont); // (351MHz/2) / 88 = 1994KHz
            MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM4_RST_EN << 4);

            break;

        case _PWM5:

            MCU_FF3A_PWM_CK_SEL |= _BIT5; // PWM clk from M2PLL/2=175.5MHz
            MCU_FF48_PWM_EN |= _BIT5; // PWM Enable
            MCU_FF53_PWM_DUT_TYPE |= _BIT5; // PWM Duty 8bits
            ScalerSetBit(PFF_52_PWM45L_DUT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (((usTotalcont >> 1) << 4) & 0xF0));
            MCU_FF51_PWM5H_DUT = ((usTotalcont >> 1) >> 4); // Period = 88 , 50% duty = 44
            MCU_FF49_PWM_CK &= ~_BIT5;
            MCU_FF54_PWM_CNT_MODE |= _BIT5; // PWM5 as counter mode
            ScalerSetBit(PFF_96_PWM45_TOTALCNT_MSB, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((HIBYTE(usTotalcont) & 0x0F) << 4));
            MCU_FF98_PWM5_TOTALCNT_LSB = LOBYTE(usTotalcont); // (351MHz/2) / 88 = 1994KHz
            MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM5_RST_EN << 5);

            break;

        default:

            break;
    }
}
#endif // END of #if(_PWM_BYPASS_MODE_SUPPORT == _ON)
#endif // END of #if(_PWM_FUNCTION_SUPPORT == _ON)

#if(_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Software IIC Start
// Input Value  : ucSlaveAddr --> Slave Address
// Output Value : None
//--------------------------------------------------
BYTE ScalerMcuIICStart(BYTE ucSlaveAddr)
{
    BYTE ucTemp = 0;
    WORD usTimeOut = 6;

    PCB_SW_IIC_SCL_SET();
    PCB_SW_IIC_SDA_SET();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SCL_CHK(ucTemp);

    while(ucTemp == _LOW)
    {
        if(usTimeOut > 0)
        {
            usTimeOut--;
            SW_IIC_DELAY_TIME();
        }
        else
        {
            return _FAIL;
        }

        PCB_SW_IIC_SCL_CHK(ucTemp);
    }

    PCB_SW_IIC_SDA_CLR();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SCL_CLR();

#if(_SW_IIC_HOLD_TIME_LIMIT_SUPPORT == _OFF)
    SW_IIC_DELAY_TIME();
#endif

    return ScalerMcuIICSendByte(ucSlaveAddr);
}

//--------------------------------------------------
// Description  : Software IIC Stop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIICStop(void)
{
    PCB_SW_IIC_SDA_CLR();
    PCB_SW_IIC_SCL_SET();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SDA_SET();
}

//--------------------------------------------------
// Description  : Software IIC Get Acknowledge
// Input Value  : None
// Output Value : ucAck --> 0: Ack / 1: Nack
//--------------------------------------------------
BYTE ScalerMcuIICGetAck(void)
{
    BYTE ucAck = 0;

    PCB_SW_IIC_SDA_SET();
    PCB_SW_IIC_SCL_SET();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SDA_CHK(ucAck);

    PCB_SW_IIC_SCL_CLR();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SDA_SET();

    return ucAck;
}

//--------------------------------------------------
// Description  : Software IIC Send Acknowledge
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIICSendAck(void)
{
    PCB_SW_IIC_SDA_CLR();
    PCB_SW_IIC_SCL_SET();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SCL_CLR();

    SW_IIC_DELAY_TIME();
}

//--------------------------------------------------
// Description  : Software IIC Send No-Acknowledge
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIICSendNoAck(void)
{
    PCB_SW_IIC_SDA_SET();
    PCB_SW_IIC_SCL_SET();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SCL_CLR();

    SW_IIC_DELAY_TIME();
}

//--------------------------------------------------
// Description  : Software IIC Read 1 Byte
// Input Value  : None
// Output Value : ucValue --> Received Byte
//--------------------------------------------------
BYTE ScalerMcuIICGetByte(void)
{
    BYTE ucTemp = 0;
    BYTE ucCnt = 0;
    BYTE ucValue = 0;

    PCB_SW_IIC_SDA_SET();

    for(ucCnt = 0; ucCnt < 8; ucCnt++)
    {
        PCB_SW_IIC_SCL_SET();

        SW_IIC_DELAY_TIME();

        PCB_SW_IIC_SDA_CHK(ucTemp);

        ucValue = (ucValue << 1) | ucTemp;

        PCB_SW_IIC_SCL_CLR();

        SW_IIC_DELAY_TIME();
    }

    return ucValue;
}

//--------------------------------------------------
// Description  : SoftWare IIC Write 1 Byte
// Input Value  : ucValue --> Data to be transmitted
// Output Value : None
//--------------------------------------------------
BYTE ScalerMcuIICSendByte(BYTE ucValue)
{
    BYTE ucCnt = 0;
    BYTE ucClksel = (MCU_FFED_MCU_CONTROL & _BIT1);

    for(ucCnt = 0; ucCnt < 8; ucCnt++)
    {
        if((bit)(ucValue & _BIT7) == _HIGH)
        {
            PCB_SW_IIC_SDA_SET();
        }
        else
        {
            PCB_SW_IIC_SDA_CLR();
        }

#if(_SW_IIC_HOLD_TIME_LIMIT_SUPPORT == _ON)
        if(ucClksel == _BIT1)
        {
            SW_IIC_DELAY_TIME();
        }
#endif

        PCB_SW_IIC_SCL_SET();

        SW_IIC_DELAY_TIME();

        PCB_SW_IIC_SCL_CLR();

#if(_SW_IIC_HOLD_TIME_LIMIT_SUPPORT == _OFF)
        if(ucClksel == _BIT1)
        {
            SW_IIC_DELAY_TIME();
        }
#endif

        ucValue = ucValue << 1;
    }

#if(_SW_IIC_HOLD_TIME_LIMIT_SUPPORT == _ON)
    if(ucClksel == _BIT1)
    {
        SW_IIC_DELAY_TIME();
    }
#endif

    if(ScalerMcuIICGetAck() == _HIGH)
    {
        ScalerMcuIICStop();

        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuIICWriteStart(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr)
{
    if(ScalerMcuIICStart(ucSlaveAddr | _WRITE) == _FAIL)
    {
        return _FAIL;
    }

    switch(ucSubAddrLength)
    {
        case 1:

            if(ScalerMcuIICSendByte((BYTE)(usSubAddr)) == _FAIL)
            {
                return _FAIL;
            }

            break;

        case 2:

            if(ScalerMcuIICSendByte((BYTE)((usSubAddr & 0xFF00) >> 8)) == _FAIL)
            {
                return _FAIL;
            }
            else
            {
                if(ScalerMcuIICSendByte((BYTE)(usSubAddr)) == _FAIL)
                {
                    return _FAIL;
                }
            }

            break;

        default:

            break;
    }

    return _SUCCESS;
}

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuIICWritePolling(BYTE ucSlaveAddr)
{
    if(ScalerMcuIICStart(ucSlaveAddr | _WRITE) == _FAIL)
    {
        return _FAIL;
    }

    ScalerMcuIICStop();

    return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Read data from the selected device by Software IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    if(usLength == 0)
    {
        return _FAIL;
    }

    if(ucSubAddrLength != 0)
    {
        // Write Slave address and Sub-address
        if(ScalerMcuIICWriteStart(ucSlaveAddr, ucSubAddrLength, usSubAddr) == _FAIL)
        {
            return _FAIL;
        }
    }

    // Write Slave address to read
    if(ScalerMcuIICStart(ucSlaveAddr | _READ) == _FAIL)
    {
        return _FAIL;
    }

    // Save received data
    while(--usLength)
    {
        *pucReadArray++ = ScalerMcuIICGetByte();

        ScalerMcuIICSendAck();
    }

    *pucReadArray++ = ScalerMcuIICGetByte();

    ScalerMcuIICSendNoAck();

    ScalerMcuIICStop();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by Software IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray)
{
    if(usLength == 0)
    {
        return _FAIL;
    }

    // Write Slave address and Sub-address
    if(ScalerMcuIICWriteStart(ucSlaveAddr, ucSubAddrLength, usSubAddr) == _FAIL)
    {
        return _FAIL;
    }

    // Send data
    while(usLength--)
    {
        if(ScalerMcuIICSendByte(*pucWriteArray++) == _FAIL)
        {
            return _FAIL;
        }
    }

    ScalerMcuIICStop();

    return _SUCCESS;
}
#endif    // End of #if(_SW_IIC_SUPPORT == _ON)

#if(_HW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hardware IIC Parameters Alter Setting By Use Case
// Input Value  : enumParType --> HW IIC Parameter Type
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIICConfigSetting(void)
{
#if(_HW_IIC_0_SUPPORT == _ON)
    ScalerMcuHwIIC0ConfigSetting();
#endif

#if(_HW_IIC_1_SUPPORT == _ON)
    ScalerMcuHwIIC1ConfigSetting();
#endif
}

//--------------------------------------------------
// Description  : Hardware IIC Clock Select
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIICSetFreqDiv(EnumClkSel enumClock)
{
#if(_HW_IIC_0_SUPPORT == _ON)
    ScalerMcuHwIIC0SetFreqDiv(enumClock);
#endif

#if(_HW_IIC_1_SUPPORT == _ON)
    ScalerMcuHwIIC1SetFreqDiv(enumClock);
#endif
}

//--------------------------------------------------
// Description  : Read data from the selected device by IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum)
{
#if(_HW_IIC_0_SUPPORT == _ON)
    return ScalerMcuHwIIC0Read(ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucReadArray, ucHwIICPinNum);
#endif
}

//--------------------------------------------------
// Description  : Write data to the selected device by IIC0
// Input Value  : ucSlaveAddr  --> Slave address
//                usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum)
{
#if(_HW_IIC_0_SUPPORT == _ON)
    return ScalerMcuHwIIC0Write(ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucWriteArray, ucHwIICPinNum);
#endif
}


#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIICWritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum)
{
#if(_HW_IIC_0_SUPPORT == _ON)
    return ScalerMcuHwIIC0WritePolling(ucSlaveAddr, ucSubAddrLength, ucHwIICPinNum);
#endif
}
#endif
#endif  // End of #if(_HW_IIC_SUPPORT == _ON)

#if(_HW_IIC_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hardware IIC0 Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIIC0Initial(void)
{
    // Reset IIC0 module
    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC0 module and disable TOR
    ScalerSetBit(PFF_55_I2CM_CR0, ~(_BIT7 | _BIT0), _BIT7);

    // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
    MCU_FF56_I2CM_CR1 = _HW_IIC0_TOR_XTAL;

    // Disable burst mode
    ScalerSetByte(PFF_57_I2CM_CR2, 0x00);

    // Clear interrupts
    ScalerSetByte(PFF_58_I2CM_CR3, 0x00);

#if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
    // Set fall time period count
    // Set ftpc[3:0]
    ScalerSetBit(PFF_59_I2CM_STR0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_HW_IIC0_FTPC_XTAL & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

    // Set ftpc[5:4]
    ScalerSetByte(PFF_5D_I2CM_SR, ((_HW_IIC0_FTPC_XTAL & (_BIT5 | _BIT4)) << 2) | (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#elif(_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
    // Set fall time period count
    MCU_FFD7_I2CM_STR4 = _HW_IIC0_FTPC_XTAL;

    // Set I2C Master Hold Time (Repeated) Start Count
    // If ucTHD_STA_C is not set, take ucFTPC value.
    if(_HW_IIC0_THD_STA_C_XTAL == 0)
    {
        MCU_FFD8_I2CM_STR5 = _HW_IIC0_FTPC_XTAL;
    }
    else
    {
        MCU_FFD8_I2CM_STR5 = _HW_IIC0_THD_STA_C_XTAL;
    }
#endif // End of #if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)

    // Set STA setup time period count
    MCU_FF5A_I2CM_STR1 = _HW_IIC0_STA_SUGPIO_C_XTAL;

    // Set SCL high period count
    MCU_FF5B_I2CM_STR2 = _HW_IIC0_SHPC_XTAL;

    // Set SCL low period count
    MCU_FF5C_I2CM_STR3 = _HW_IIC0_SLPC_XTAL;

    // Set frequency divisor: ref = xtal/(FD10+1)
    MCU_FF5F_I2CM_CCR = _HW_IIC0_FD10_XTAL;
}

//--------------------------------------------------
// Description  : Hardware IIC0 Parameters Alter Setting By Use Case
// Input Value  : enumParType --> HW IIC Parameter Type
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIIC0ConfigSetting(void)
{
    g_ucMcuHwI2c0SettingIndex = _HW_IIC_0_SPEED;

    ScalerMcuHwIIC0Initial();

    if(GET_REG_XTAL_CLK_SEL() == _EXT_XTAL_CLK)
    {
        // Select at external Xtal.
        ScalerMcuHwIIC0SetFreqDiv(_EXT_XTAL_CLK);
    }
    else
    {
        // Select at internal Xtal.
        ScalerMcuHwIIC0SetFreqDiv(_IOSC_CLK);
    }
}

//--------------------------------------------------
// Description  : Hardware IIC0 Clock Select
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIIC0SetFreqDiv(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
        MCU_FF56_I2CM_CR1 = _HW_IIC0_TOR_XTAL;

        // Set freq. divisor: ref = XTAL/(FD10+1) = 7.16M(ref should be approx 10MHz)
        MCU_FF5F_I2CM_CCR = _HW_IIC0_FD10_XTAL;

        // Set STA setup time period count
        MCU_FF5A_I2CM_STR1 = _HW_IIC0_STA_SUGPIO_C_XTAL;

        // Set SCL high period count
        MCU_FF5B_I2CM_STR2 = _HW_IIC0_SHPC_XTAL;

        // Set SCL low period count
        MCU_FF5C_I2CM_STR3 = _HW_IIC0_SLPC_XTAL;

#if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
        // Set fall time period count
        // Set ftpc[3:0]
        ScalerSetBit(PFF_59_I2CM_STR0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_HW_IIC0_FTPC_XTAL & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        // Set ftpc[5:4]
        ScalerSetByte(PFF_5D_I2CM_SR, ((_HW_IIC0_FTPC_XTAL & (_BIT5 | _BIT4)) << 2) | (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#elif(_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
        // Set fall time period count
        MCU_FFD7_I2CM_STR4 = _HW_IIC0_FTPC_XTAL;

        // Set I2C Master Hold Time (Repeated) Start Count
        // If ucTHD_STA_C is not set, take ucFTPC value.
        if(_HW_IIC0_THD_STA_C_XTAL == 0)
        {
            MCU_FFD8_I2CM_STR5 = _HW_IIC0_FTPC_XTAL;
        }
        else
        {
            MCU_FFD8_I2CM_STR5 = _HW_IIC0_THD_STA_C_XTAL;
        }
#endif // End of #if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
    }
    else
    {
        // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
        MCU_FF56_I2CM_CR1 = _HW_IIC0_TOR_IOSC;

        // Set freq. divisor: ref = IOSC/(FD10+1) = 9M(ref should be approx 10MHz)
        MCU_FF5F_I2CM_CCR = _HW_IIC0_FD10_IOSC;

        // Set STA setup time period count
        MCU_FF5A_I2CM_STR1 = _HW_IIC0_STA_SUGPIO_C_IOSC;

        // Set SCL high period count
        MCU_FF5B_I2CM_STR2 = _HW_IIC0_SHPC_IOSC;

        // Set SCL low period count
        MCU_FF5C_I2CM_STR3 = _HW_IIC0_SLPC_IOSC;

#if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
        // Set fall time period count
        // Set ftpc[3:0]
        ScalerSetBit(PFF_59_I2CM_STR0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_HW_IIC0_FTPC_IOSC & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        // Set ftpc[5:4]
        ScalerSetByte(PFF_5D_I2CM_SR, ((_HW_IIC0_FTPC_IOSC & (_BIT5 | _BIT4)) << 2) | (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#elif(_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
        // Set fall time period count
        MCU_FFD7_I2CM_STR4 = _HW_IIC0_FTPC_IOSC;

        // Set I2C Master Hold Time (Repeated) Start Count
        // If ucTHD_STA_C is not set, take ucFTPC value.
        if(_HW_IIC0_THD_STA_C_IOSC == 0)
        {
            MCU_FFD8_I2CM_STR5 = _HW_IIC0_FTPC_IOSC;
        }
        else
        {
            MCU_FFD8_I2CM_STR5 = _HW_IIC0_THD_STA_C_IOSC;
        }
#endif // End of #if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
    }
}

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIIC0WritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum)
{
    BYTE ucSubAddress = 0x00;
    BYTE ucLength = 0;
    BYTE ucTimeOutCnt = _IIC_POLLING_TIME;

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit(PFF_57_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit(PFF_58_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    while(ScalerGetBit(PFF_5D_I2CM_SR, _BIT5) != _BIT5)
    {
        if(ucTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
        else
        {
            ucTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Load Slave Address to IIC Buffer
    MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

    ScalerSetBit(PFF_55_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    switch(ucSubAddrLength)
    {
        case 0:

            break;

        case 1:

            // Set data length
            ScalerSetBit(PFF_55_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (ucLength << 1));

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(ucSubAddress);

            break;

        case 2:

            // Set data length
            ScalerSetBit(PFF_55_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucLength + 1) << 1));

            // Load First Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSubAddress;

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSubAddress;

            break;

        default:

            break;
    }

    // IIC command Start
    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT6, _BIT6);

    // Wait until Master Transmit Complete
    ucTimeOutCnt = _IIC_POLLING_TIME;

    while(ScalerGetBit(PFF_5D_I2CM_SR, _BIT0) != _BIT0)
    {
        ucTimeOutCnt--;

        DELAY_5US();

        if(ucTimeOutCnt == 0x00)
        {
            // Reset(Block) IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
    }

    // Clear all flags
    ScalerSetBit(PFF_5D_I2CM_SR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}
#endif // End of #if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Read data from the selected device by IIC0
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIIC0Read(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum)
{
    BYTE ucI = 0;
    WORD usTimeOutCnt = 600;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _HW_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    while(ScalerGetBit(PFF_5D_I2CM_SR, _BIT5) != _BIT5)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            ScalerSetBit(PFF_57_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

            // Set no repeat start
            ScalerSetBit(PFF_58_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _READ;

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit(PFF_57_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit(PFF_58_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Load Slave Address to receive data
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _READ;

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit(PFF_57_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit(PFF_58_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

            // Load First Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)((usSubAddr & 0xFF00) >> 8);

            // Load Second Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Load Slave Address to receive data
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _READ;

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit(PFF_55_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (ucDataLength - 1) << 1);

    // IIC command Start
    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT6, _BIT6);

    // Wait until Master Receive Complete
    usTimeOutCnt = 600;

    while(ScalerGetBit(PFF_5D_I2CM_SR, _BIT1) != _BIT1)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    usTimeOutCnt = 600;

    while(ScalerGetBit(PFF_5D_I2CM_SR, _BIT5) != _BIT5)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = MCU_FF5E_I2CM_TD;
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetBit(PFF_5D_I2CM_SR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by IIC0
// Input Value  : ucSlaveAddr  --> Slave address
//                usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIIC0Write(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum)
{
    BYTE ucI = 0;
    WORD usTimeOutCnt = 600;
    BYTE ucTempLength = 0;

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit(PFF_57_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit(PFF_58_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    while(ScalerGetBit(PFF_5D_I2CM_SR, _BIT5) != _BIT5)
    {
        if(usTimeOutCnt == 0)
        {
            DebugMessageScaler("- IIC Write Time Out: FIFO Clock", 0xA1);

            // Reset(Block) IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Load Slave Address to IIC Buffer
    MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

    ScalerSetBit(PFF_55_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    if(ucDataLength > 16)
    {
        pData[0] = 16;
    }
    else
    {
        pData[0] = ucDataLength;
    }

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Set data length
            ucTempLength = (pData[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)((usSubAddr & 0xFF00) >> 8);

            // Load Second Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Set data length
            ucTempLength = ((pData[0] + 1) << 1);

            break;

        default:

            break;
    }

    if(ucDataLength <= 16)
    {
        // Load data to IIC buffer for transmission
        for(ucI = 0; ucI < pData[0]; ucI++)
        {
            MCU_FF5E_I2CM_TD = *pucWriteArray;
            pucWriteArray++;
        }

        // Send IIC command Start
        ScalerSetByte(PFF_55_I2CM_CR0, 0xC0 + ucTempLength);
    }
    else
    {
        // Disable HW TOR
        ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT0, 0x00);

        // Enable Burst Mode
        ScalerSetBit(PFF_57_I2CM_CR2, ~_BIT6, _BIT6);

        // Calcualte Burst Command
        pData[1] = (ucDataLength / 16) + ((ucDataLength % 16) ? 1 : 0);

        for(pData[2] = 0; pData[2] < pData[1]; pData[2]++)
        {
            usTimeOutCnt = 600;

            // Wait I2C Fifo Clk Switch to Mcu Clk
            while(ScalerGetBit(PFF_5D_I2CM_SR, _BIT5) != _BIT5)
            {
                if(usTimeOutCnt == 0)
                {
                    DebugMessageScaler("- IIC Write Time Out: FIFO Clock", 0xA2);

                    // Reset(Block) IIC module
                    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

                    // Enable IIC module
                    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

                    // Disable Burst Mode
                    ScalerSetBit(PFF_57_I2CM_CR2, ~_BIT6, 0x00);

                    return _FAIL;
                }
                else
                {
                    usTimeOutCnt--;

                    DELAY_5US();
                }
            }

            if(pData[0] != 0)
            {
                // Load data to IIC buffer for transmission
                for(ucI = 0; ucI < pData[0]; ucI++)
                {
                    MCU_FF5E_I2CM_TD = *pucWriteArray;
                    pucWriteArray++;
                }

                if(pData[2] != 0)
                {
                    // Set data length
                    ucTempLength = ((pData[0] - 1) << 1) & (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1);
                }
            }

            // Set Length and First Burst Command Start, Must Keep FF55[6] = 1 until Burst Mode end
            ScalerSetByte(PFF_55_I2CM_CR0, 0xC0 + ucTempLength);

            // Update Remaider Data Length
            ucDataLength = ucDataLength - pData[0];

            if(ucDataLength > 16)
            {
                pData[0] = 16;
            }
            else
            {
                pData[0] = ucDataLength;
            }

            if(pData[2] == (pData[1] - 1))
            {
                // Disable Burst Write
                ScalerSetBit(PFF_57_I2CM_CR2, ~_BIT6, 0x00);

                // Burst write again
                ScalerSetBit(PFF_5D_I2CM_SR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

                break;
            }
            else if(pData[2] != 0)
            {
                // Burst write again
                ScalerSetBit(PFF_5D_I2CM_SR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
            }

            usTimeOutCnt = 600;

            // Wait into Burst Wait State
            while(ScalerGetBit(PFF_5D_I2CM_SR, _BIT3) != _BIT3)
            {
                if(usTimeOutCnt == 0)
                {
                    DebugMessageScaler("- IIC Write Time Out: Burst Mode", 0xA3);

                    // Reset(Block) IIC module
                    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

                    // Enable IIC module
                    ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

                    // Disable Burst Mode
                    ScalerSetBit(PFF_57_I2CM_CR2, ~_BIT6, 0x00);

                    return _FAIL;
                }
                else
                {
                    usTimeOutCnt--;

                    DELAY_5US();
                }
            }
        }
    }

    usTimeOutCnt = 600;

    // Wait until Master Transmit Complete
    while(ScalerGetBit(PFF_5D_I2CM_SR, _BIT0) != _BIT0)
    {
        if(usTimeOutCnt == 0)
        {
            DebugMessageScaler("- IIC Write Time Out: Transmit", 0xA4);

            // Reset(Block) IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_55_I2CM_CR0, ~_BIT7, _BIT7);

            // Disable Burst Mode
            ScalerSetBit(PFF_57_I2CM_CR2, ~_BIT6, 0x00);

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Clear all flags
    ScalerSetBit(PFF_5D_I2CM_SR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}

#endif // End of #if(_HW_IIC_0_SUPPORT == _ON)

#if(_HW_IIC_1_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hardware IIC1 Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIIC1Initial(void)
{
    // Reset IIC1 module
    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC1 module and disable TOR
    ScalerSetBit(PFF_C5_I2CM_CR0, ~(_BIT7 | _BIT0), _BIT7);

    // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
    MCU_FFC6_I2CM_CR1 = _HW_IIC1_TOR_XTAL;

    // Disable burst mode
    MCU_FFC7_I2CM_CR2 = 0x00;

    // Clear interrupts
    ScalerSetByte(PFF_C8_I2CM_CR3, 0x00);

#if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
    // Set fall time period count
    // Set ftpc[3:0]
    ScalerSetBit(PFF_C9_I2CM_STR0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_HW_IIC1_FTPC_XTAL & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

    // Set ftpc[5:4]
    ScalerSetByte(PFF_CD_I2CM_SR, ((_HW_IIC1_FTPC_XTAL & (_BIT5 | _BIT4)) << 2) | (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#elif(_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
    // Set fall time period count
    MCU_FFD9_I2CM_STR4 = _HW_IIC1_FTPC_XTAL;

    // Set I2C Master Hold Time (Repeated) Start Count
    // If ucTHD_STA_C is not set, take ucFTPC value.
    if(_HW_IIC1_THD_STA_C_XTAL == 0)
    {
        MCU_FFDA_I2CM_STR5 = _HW_IIC1_FTPC_XTAL;
    }
    else
    {
        MCU_FFDA_I2CM_STR5 = _HW_IIC1_THD_STA_C_XTAL;
    }
#endif // End of #if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)

    // Set STA setup time period count
    MCU_FFCA_I2CM_STR1 = _HW_IIC1_STA_SUGPIO_C_XTAL;

    // Set SCL high period count
    MCU_FFCB_I2CM_STR2 = _HW_IIC1_SHPC_XTAL;

    // Set SCL low period count
    MCU_FFCC_I2CM_STR3 = _HW_IIC1_SLPC_XTAL;

    // Set frequency divisor: ref = xtal/(FD10+1)
    MCU_FFCF_I2CM_CCR = _HW_IIC1_FD10_XTAL;
}

//--------------------------------------------------
// Description  : Hardware IIC1 Parameters Alter Setting By Use Case
// Input Value  : enumParType --> HW IIC Parameter Type
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIIC1ConfigSetting(void)
{
    g_ucMcuHwI2c1SettingIndex = _HW_IIC_1_SPEED;

    ScalerMcuHwIIC1Initial();

    if(GET_REG_XTAL_CLK_SEL() == _EXT_XTAL_CLK)
    {
        // Select at external Xtal.
        ScalerMcuHwIIC1SetFreqDiv(_EXT_XTAL_CLK);
    }
    else
    {
        // Select at internal Xtal.
        ScalerMcuHwIIC1SetFreqDiv(_IOSC_CLK);
    }
}

//--------------------------------------------------
// Description  : Hardware IIC1 Clock Select
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIIC1SetFreqDiv(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
        MCU_FFC6_I2CM_CR1 = _HW_IIC1_TOR_XTAL;

        // Set freq. divisor: ref = XTAL/(FD10+1) = 7.16M(ref should be approx 10MHz)
        MCU_FFCF_I2CM_CCR = _HW_IIC1_FD10_XTAL;

        // Set STA setup time period count
        MCU_FFCA_I2CM_STR1 = _HW_IIC1_STA_SUGPIO_C_XTAL;

        // Set SCL high period count
        MCU_FFCB_I2CM_STR2 = _HW_IIC1_SHPC_XTAL;

        // Set SCL low period count
        MCU_FFCC_I2CM_STR3 = _HW_IIC1_SLPC_XTAL;

#if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
        // Set fall time period count
        // Set ftpc[3:0]
        ScalerSetBit(PFF_C9_I2CM_STR0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_HW_IIC1_FTPC_XTAL & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        // Set ftpc[5:4]
        ScalerSetByte(PFF_CD_I2CM_SR, ((_HW_IIC1_FTPC_XTAL & (_BIT5 | _BIT4)) << 2) | (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#elif(_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
        // Set fall time period count
        MCU_FFD9_I2CM_STR4 = _HW_IIC1_FTPC_XTAL;

        // Set I2C Master Hold Time (Repeated) Start Count
        // If ucTHD_STA_C is not set, take ucFTPC value.
        if(_HW_IIC1_THD_STA_C_XTAL == 0)
        {
            MCU_FFDA_I2CM_STR5 = _HW_IIC1_FTPC_XTAL;
        }
        else
        {
            MCU_FFDA_I2CM_STR5 = _HW_IIC1_THD_STA_C_XTAL;
        }
#endif // End of #if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
    }
    else
    {
        // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
        MCU_FFC6_I2CM_CR1 = _HW_IIC1_TOR_IOSC;

        // Set freq. divisor: ref = IOSC/(FD10+1) = 9M(ref should be approx 10MHz)
        MCU_FFCF_I2CM_CCR = _HW_IIC1_FD10_IOSC;

        // Set STA setup time period count
        MCU_FFCA_I2CM_STR1 = _HW_IIC1_STA_SUGPIO_C_IOSC;

        // Set SCL high period count
        MCU_FFCB_I2CM_STR2 = _HW_IIC1_SHPC_IOSC;

        // Set SCL low period count
        MCU_FFCC_I2CM_STR3 = _HW_IIC1_SLPC_IOSC;

#if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
        // Set fall time period count
        // Set ftpc[3:0]
        ScalerSetBit(PFF_C9_I2CM_STR0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_HW_IIC1_FTPC_IOSC & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        // Set ftpc[5:4]
        ScalerSetByte(PFF_CD_I2CM_SR, ((_HW_IIC1_FTPC_IOSC & (_BIT5 | _BIT4)) << 2) | (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#elif(_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
        // Set fall time period count
        MCU_FFD9_I2CM_STR4 = _HW_IIC1_FTPC_IOSC;

        // Set I2C Master Hold Time (Repeated) Start Count
        // If ucTHD_STA_C is not set, take ucFTPC value.
        if(_HW_IIC1_THD_STA_C_IOSC == 0)
        {
            MCU_FFDA_I2CM_STR5 = _HW_IIC1_FTPC_IOSC;
        }
        else
        {
            MCU_FFDA_I2CM_STR5 = _HW_IIC1_THD_STA_C_IOSC;
        }
#endif // End of #if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
    }
}

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIIC1WritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum)
{
    BYTE ucSubAddress = 0x00;
    BYTE ucLength = 0;
    BYTE ucTimeOutCnt = _IIC_POLLING_TIME;

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    MCU_FFC7_I2CM_CR2 &= ~(_BIT1 | _BIT0);

    // Set no repeat start
    ScalerSetBit(PFF_C8_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    while(ScalerGetBit(PFF_CD_I2CM_SR, _BIT5) != _BIT5)
    {
        if(ucTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
        else
        {
            ucTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Load Slave Address to IIC Buffer
    MCU_FFCE_I2CM_TD = ucSlaveAddr | _WRITE;

    ScalerSetBit(PFF_C5_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    switch(ucSubAddrLength)
    {
        case 0:

            break;

        case 1:

            // Set data length
            ScalerSetBit(PFF_C5_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (ucLength << 1));

            // Load Sub-Address to IIC Buffer
            MCU_FFCE_I2CM_TD = (BYTE)(ucSubAddress);

            break;

        case 2:

            // Set data length
            ScalerSetBit(PFF_C5_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucLength + 1) << 1));

            // Load First Sub-Address to IIC Buffer
            MCU_FFCE_I2CM_TD = ucSubAddress;

            // Load Sub-Address to IIC Buffer
            MCU_FFCE_I2CM_TD = ucSubAddress;

            break;

        default:

            break;
    }

    // IIC command Start
    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT6, _BIT6);

    // Wait until Master Transmit Complete
    ucTimeOutCnt = _IIC_POLLING_TIME;

    while(ScalerGetBit(PFF_CD_I2CM_SR, _BIT0) != _BIT0)
    {
        ucTimeOutCnt--;

        DELAY_5US();

        if(ucTimeOutCnt == 0x00)
        {
            // Reset(Block) IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
    }

    // Clear all flags
    ScalerSetBit(PFF_CD_I2CM_SR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Read data from the selected device by IIC1
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIIC1Read(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum)
{
    BYTE ucI = 0;
    WORD usTimeOutCnt = 600;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _HW_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    while(ScalerGetBit(PFF_CD_I2CM_SR, _BIT5) != _BIT5)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            MCU_FFC7_I2CM_CR2 &= ~(_BIT1 | _BIT0);

            // Set no repeat start
            ScalerSetBit(PFF_C8_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            MCU_FFCE_I2CM_TD = ucSlaveAddr | _READ;

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit(PFF_C7_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit(PFF_C8_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            MCU_FFCE_I2CM_TD = ucSlaveAddr | _WRITE;

            // Load Sub-Address to IIC Buffer
            MCU_FFCE_I2CM_TD = (BYTE)(usSubAddr);

            // Load Slave Address to receive data
            MCU_FFCE_I2CM_TD = ucSlaveAddr | _READ;

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit(PFF_C7_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit(PFF_C8_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            MCU_FFCE_I2CM_TD = ucSlaveAddr | _WRITE;

            // Load First Sub-Address to IIC Buffer
            MCU_FFCE_I2CM_TD = (BYTE)((usSubAddr & 0xFF00) >> 8);

            // Load Second Sub-Address to IIC Buffer
            MCU_FFCE_I2CM_TD = (BYTE)(usSubAddr);

            // Load Slave Address to receive data
            MCU_FFCE_I2CM_TD = ucSlaveAddr | _READ;

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit(PFF_C5_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (ucDataLength - 1) << 1);

    // IIC command Start
    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT6, _BIT6);

    // Wait until Master Receive Complete
    usTimeOutCnt = 600;

    while(ScalerGetBit(PFF_CD_I2CM_SR, _BIT1) != _BIT1)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    usTimeOutCnt = 600;

    while(ScalerGetBit(PFF_CD_I2CM_SR, _BIT5) != _BIT5)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = MCU_FFCE_I2CM_TD;
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetBit(PFF_CD_I2CM_SR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by IIC1
// Input Value  : ucSlaveAddr  --> Slave address
//                usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIIC1Write(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum)
{
    BYTE ucI = 0;
    WORD usTimeOutCnt = 600;
    BYTE ucTempLength = 0;

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    MCU_FFC7_I2CM_CR2 &= ~(_BIT1 | _BIT0);

    // Set no repeat start
    ScalerSetBit(PFF_C8_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    while(ScalerGetBit(PFF_CD_I2CM_SR, _BIT5) != _BIT5)
    {
        if(usTimeOutCnt == 0)
        {
            DebugMessageScaler("- IIC Write Time Out: FIFO Clock", 0xB1);

            // Reset(Block) IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Load Slave Address to IIC Buffer
    MCU_FFCE_I2CM_TD = ucSlaveAddr | _WRITE;

    ScalerSetBit(PFF_C5_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    if(ucDataLength > 16)
    {
        pData[0] = 16;
    }
    else
    {
        pData[0] = ucDataLength;
    }

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            MCU_FFCE_I2CM_TD = (BYTE)(usSubAddr);

            // Set data length
            ucTempLength = (pData[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            MCU_FFCE_I2CM_TD = (BYTE)((usSubAddr & 0xFF00) >> 8);

            // Load Second Sub-Address to IIC Buffer
            MCU_FFCE_I2CM_TD = (BYTE)(usSubAddr);

            // Set data length
            ucTempLength = ((pData[0] + 1) << 1);

            break;

        default:

            break;
    }

    if(ucDataLength <= 16)
    {
        // Load data to IIC buffer for transmission
        for(ucI = 0; ucI < pData[0]; ucI++)
        {
            MCU_FFCE_I2CM_TD = *pucWriteArray;
            pucWriteArray++;
        }

        // Send IIC command Start
        ScalerSetByte(PFF_C5_I2CM_CR0, 0xC0 + ucTempLength);
    }
    else
    {
        // Disable HW TOR
        ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT0, 0x00);

        // Enable Burst Mode
        MCU_FFC7_I2CM_CR2 |= _BIT6;

        // Calcualte Burst Command
        pData[1] = (ucDataLength / 16) + ((ucDataLength % 16) ? 1 : 0);

        for(pData[2] = 0; pData[2] < pData[1]; pData[2]++)
        {
            usTimeOutCnt = 600;

            // Wait I2C Fifo Clk Switch to Mcu Clk
            while(ScalerGetBit(PFF_CD_I2CM_SR, _BIT5) != _BIT5)
            {
                if(usTimeOutCnt == 0)
                {
                    DebugMessageScaler("- IIC Write Time Out: FIFO Clock", 0xB2);

                    // Reset(Block) IIC module
                    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

                    // Enable IIC module
                    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

                    // Disable Burst Mode
                    MCU_FFC7_I2CM_CR2 &= ~_BIT6;

                    return _FAIL;
                }
                else
                {
                    usTimeOutCnt--;

                    DELAY_5US();
                }
            }

            if(pData[0] != 0)
            {
                // Load data to IIC buffer for transmission
                for(ucI = 0; ucI < pData[0]; ucI++)
                {
                    MCU_FFCE_I2CM_TD = *pucWriteArray;
                    pucWriteArray++;
                }

                if(pData[2] != 0)
                {
                    // Set data length
                    ucTempLength = ((pData[0] - 1) << 1) & (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1);
                }
            }

            // Set Length and First Burst Command Start, Must Keep FF55[6] = 1 until Burst Mode end
            ScalerSetByte(PFF_C5_I2CM_CR0, 0xC0 + ucTempLength);

            // Update Remaider Data Length
            ucDataLength = ucDataLength - pData[0];

            if(ucDataLength > 16)
            {
                pData[0] = 16;
            }
            else
            {
                pData[0] = ucDataLength;
            }

            if(pData[2] == (pData[1] - 1))
            {
                // Disable Burst Write
                MCU_FFC7_I2CM_CR2 &= ~_BIT6;

                // Burst write again
                ScalerSetBit(PFF_CD_I2CM_SR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

                break;
            }
            else if(pData[2] != 0)
            {
                // Burst write again
                ScalerSetBit(PFF_CD_I2CM_SR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
            }

            usTimeOutCnt = 600;

            // Wait into Burst Wait State
            while(ScalerGetBit(PFF_CD_I2CM_SR, _BIT3) != _BIT3)
            {
                if(usTimeOutCnt == 0)
                {
                    DebugMessageScaler("- IIC Write Time Out: Burst Mode", 0xB3);

                    // Reset(Block) IIC module
                    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

                    // Enable IIC module
                    ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

                    // Disable Burst Mode
                    MCU_FFC7_I2CM_CR2 &= ~_BIT6;

                    return _FAIL;
                }
                else
                {
                    usTimeOutCnt--;

                    DELAY_5US();
                }
            }
        }
    }

    usTimeOutCnt = 600;

    // Wait until Master Transmit Complete
    while(ScalerGetBit(PFF_CD_I2CM_SR, _BIT0) != _BIT0)
    {
        if(usTimeOutCnt == 0)
        {
            DebugMessageScaler("- IIC Write Time Out: Transmit", 0xB4);

            // Reset(Block) IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

            // Disable Burst Mode
            MCU_FFC7_I2CM_CR2 &= ~_BIT6;

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Clear all flags
    ScalerSetBit(PFF_CD_I2CM_SR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}

#if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
//--------------------------------------------------
// Description  : HW IIC 1 Slave Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIIC1SlaveInitial(void)
{
#if(_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO)
    BYTE ucSlaveAddrConfig = 0x00;

    // Check I2C Slave Enable Pin (Only Exist when not use EXT_FLASH)
    if(PCB_GPIO_GET_IIC_1_SLAVE_SUPPORT_CONFIG() == _HW_IIC_1_SLAVE_SUPPORT_ENABLE)
#endif
    {
        // For I2C Master_1 (Fixed Master_1 Module Used For IIC Slave Mode)
        // Release IIC_1 Module Clock Gating
        // MCU_FFF2_PWM_I2C_CLOCK_STOP &= ~_BIT6;

#if(_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO)
        // Check I2C Slave Addr Pin (Only Exist when not use EXT_FLASH), and Set Slave Address
        ucSlaveAddrConfig = ((BYTE)PCB_GPIO_GET_IIC_1_SLAVE_ADDR_CONFIG_1() << 1) | PCB_GPIO_GET_IIC_1_SLAVE_ADDR_CONFIG_0();

        switch(ucSlaveAddrConfig)
        {
            case 0x00:
                MCU_FF89_I2CS_CTRL0 = _HW_IIC_1_SLAVE_ADDRESS_CONFIG_00;

                break;

            case 0x01:
                MCU_FF89_I2CS_CTRL0 = _HW_IIC_1_SLAVE_ADDRESS_CONFIG_01;

                break;

            case 0x02:
                MCU_FF89_I2CS_CTRL0 = _HW_IIC_1_SLAVE_ADDRESS_CONFIG_10;

                break;

            case 0x03:
                MCU_FF89_I2CS_CTRL0 = _HW_IIC_1_SLAVE_ADDRESS_CONFIG_11;

                break;

            default:
                break;
        }
#else
        // Use Default I2C Slave Addr When NOT _IIC_SLAVE_DET_BY_GPIO
        MCU_FF89_I2CS_CTRL0 = _HW_IIC_1_SLAVE_ADDRESS_CONFIG_00;
#endif  // End of #if(_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO)

        // Set Slave Module Enable
        ScalerSetBit(PFF_89_I2CS_CTRL0, ~_BIT0, _BIT0);

        // Reset IIC 1 module
        ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, 0x00);
        ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT7, _BIT7);

        // Disable & Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
        ScalerSetBit(PFF_C5_I2CM_CR0, ~_BIT0, 0x00);
        MCU_FFC6_I2CM_CR1 = 0xF0;

        // Disable Master Burst mode Interrupt
        MCU_FFC7_I2CM_CR2 = 0x00;
        ScalerSetByte(PFF_C8_I2CM_CR3, 0x00);

#if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)
        // Set Master Time Parameter : Fall time period count
        // Set ftpc[3:0]
        ScalerSetBit(PFF_C9_I2CM_STR0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_HW_IIC1_FTPC_XTAL & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        // Set ftpc[5:4]
        ScalerSetByte(PFF_CD_I2CM_SR, ((_HW_IIC1_FTPC_XTAL & (_BIT5 | _BIT4)) << 2) | (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#elif(_HW_HW_IIC_GEN == _HW_IIC_GEN_2)
        // Set Master Time Parameter : Fall time period count
        MCU_FFD9_I2CM_STR4 = _HW_IIC1_FTPC_XTAL;

        // Set I2C Master Hold Time (Repeated) Start Count
        // If ucTHD_STA_C is not set, take ucFTPC value.
        if(_HW_IIC1_THD_STA_C_XTAL == 0)
        {
            MCU_FFDA_I2CM_STR5 = _HW_IIC1_FTPC_XTAL;
        }
        else
        {
            MCU_FFDA_I2CM_STR5 = _HW_IIC1_THD_STA_C_XTAL;
        }
#endif // End of #if(_HW_HW_IIC_GEN == _HW_IIC_GEN_1)

        // Set STA setup time period count
        MCU_FFCA_I2CM_STR1 = _HW_IIC1_STA_SUGPIO_C_XTAL;

        // Set SCL high period count
        MCU_FFCB_I2CM_STR2 = _HW_IIC1_SHPC_XTAL;

        // Set SCL low period count
        MCU_FFCC_I2CM_STR3 = _HW_IIC1_SLPC_XTAL;

        // Set frequency divisor: ref = xtal/(FD10+1)
        MCU_FFCF_I2CM_CCR = _HW_IIC1_FD10_XTAL;

        // Default Disable write cmd finish IRQ (Enable when System Initial Done)
        MCU_FF8B_I2CS_CTRL2 &= ~_BIT7;

        // Reset data point
        ScalerSetBit(PFF_8E_I2CS_BUFLEN, ~_BIT7, 0x00);
        ScalerSetBit(PFF_8E_I2CS_BUFLEN, ~_BIT7, _BIT7);

        // First Reply data is get from 0xFFA1
        ScalerSetBit(PFF_8E_I2CS_BUFLEN, ~_BIT5, _BIT5);

        // I2C Module_1 to INT1
        // No Need in RLE1039
        // MCU_FFC2_IRQ_PRIORITY_1 &= ~(_BIT5 | _BIT4 | _BIT3);
        // MCU_FFC2_IRQ_PRIORITY_1 |= _BIT3;
    }
}

//--------------------------------------------------
// Description  : HW IIC 1 Slave (Write Cmd Finish) IRQ Control
// Input Value  : bEn  --> _ENABLE / _DISABLE
// Output Value : void
//--------------------------------------------------
void ScalerMcuHwIIC1SlaveEnableIrq(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Clear Host Write Finished & Busy Bit
        MCU_FF8D_I2CS_STATUS1 |= (_BIT7 | _BIT3);

        // Enable IRQ
        MCU_FF8B_I2CS_CTRL2 |= _BIT7;
    }
    else
    {
        // Disable IRQ
        MCU_FF8B_I2CS_CTRL2 &= ~_BIT7;
    }
}
#endif // End of #if((_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DET_BY_GPIO) || (_HW_IIC_1_SLAVE_SUPPORT_OPTION == _IIC_SLAVE_DEFAULT_ON))
#endif // End of #if(_HW_IIC_1_SUPPORT == _ON)

#if(_TYPEC_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C IIC Parameters Alter Setting By Use Case
// Input Value  : enumParType --> Type-C IIC Parameter Type
// Output Value : None
//--------------------------------------------------
void ScalerMcuTypecIICConfigSetting(void)
{
#if(_TYPEC_IIC_0_SUPPORT == _ON)
    ScalerMcuTypecIIC0ConfigSetting();
#endif
}

//--------------------------------------------------
// Description  : Hardware IIC Clock Select
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuTypecIICSetFreqDiv(EnumClkSel enumClock)
{
#if(_TYPEC_IIC_0_SUPPORT == _ON)
    ScalerMcuTypecIIC0SetFreqDiv(enumClock);
#endif
}

//--------------------------------------------------
// Description  : Read data from the selected device by IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuTypecIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum)
{
#if(_TYPEC_IIC_0_SUPPORT == _ON)
    return ScalerMcuTypecIIC0Read(ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucReadArray, ucHwIICPinNum);
#endif

    return _FAIL;
}

//--------------------------------------------------
// Description  : Write data to the selected device by IIC0
// Input Value  : ucSlaveAddr  --> Slave address
//                usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuTypecIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum)
{
#if(_TYPEC_IIC_0_SUPPORT == _ON)
    return ScalerMcuTypecIIC0Write(ucSlaveAddr, ucSubAddrLength, usSubAddr, ucDataLength, pucWriteArray, ucHwIICPinNum);
#endif

    return _FAIL;
}

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuTypecIICWritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum)
{
#if(_TYPEC_IIC_0_SUPPORT == _ON)
    return ScalerMcuTypecIIC0WritePolling(ucSlaveAddr, ucSubAddrLength, ucHwIICPinNum);
#endif

    return _FAIL;
}
#endif
#endif  // End of #if(_TYPEC_IIC_SUPPORT == _ON)

#if(_TYPEC_IIC_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C IIC0 Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuTypecIIC0Initial(void)
{
    // Reset IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module and disable TOR
    ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT7 | _BIT0), _BIT7);

    // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
    ScalerSetByte(P7F_61_I2CM_CR1, _TYPEC_IIC0_TOR_XTAL);

    // Disable burst mode
    ScalerSetByte(P7F_62_I2CM_CR2, 0x00);

    // Clear interrupts
    ScalerSetByte(P7F_63_I2CM_CR3, 0x00);

    // Set STA setup time period count
    ScalerSetByte(P7F_65_I2CM_STR1, _TYPEC_IIC0_STA_SUGPIO_C_XTAL);

    // Set SCL high period count
    ScalerSetByte(P7F_66_I2CM_STR2, _TYPEC_IIC0_SHPC_XTAL);

    // Set SCL low period count
    ScalerSetByte(P7F_67_I2CM_STR3, _TYPEC_IIC0_SLPC_XTAL);

    // Set frequency divisor: ref = xtal/(FD10+1)
    ScalerSetByte(P7F_6A_I2CM_CCR, _TYPEC_IIC0_FD10_XTAL);

    // Set fall time period count
    ScalerSetByte(P7F_6E_I2CM_STR4, _TYPEC_IIC0_FTPC_XTAL);

    // Set I2C Master Repeated_Start
    ScalerSetByte(P7F_6F_I2CM_STR5, _TYPEC_IIC0_THD_STA_C_XTAL);
}

//--------------------------------------------------
// Description  : Type-C IIC0 Parameters Alter Setting By Use Case
// Input Value  : enumParType --> Type-C IIC Parameter Type
// Output Value : None
//--------------------------------------------------
void ScalerMcuTypecIIC0ConfigSetting(void)
{
    g_ucMcuTypecI2c0SettingIndex = _TYPEC_IIC_0_SPEED;

    ScalerMcuTypecIIC0Initial();

    if(GET_REG_XTAL_CLK_SEL() == _EXT_XTAL_CLK)
    {
        // Select at external Xtal.
        ScalerMcuTypecIIC0SetFreqDiv(_EXT_XTAL_CLK);
    }
    else
    {
        // Select at internal IOSC.
        ScalerMcuTypecIIC0SetFreqDiv(_IOSC_CLK);
    }
}

//--------------------------------------------------
// Description  : Type-C IIC0 Clock Select
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuTypecIIC0SetFreqDiv(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // Set Clock Source to XTAL
        ScalerSetBit(P7F_03_10B_ADC_CLK_CLRT, ~(_BIT7 | _BIT6), _BIT6);

        // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
        ScalerSetByte(P7F_61_I2CM_CR1, _TYPEC_IIC0_TOR_XTAL);

        // Set freq. divisor: ref = XTAL/(FD10+1) = 7.16M(ref should be approx 10MHz)
        ScalerSetByte(P7F_6A_I2CM_CCR, _TYPEC_IIC0_FD10_XTAL);

        // Set STA setup time period count
        ScalerSetByte(P7F_65_I2CM_STR1, _TYPEC_IIC0_STA_SUGPIO_C_XTAL);

        // Set SCL high period count
        ScalerSetByte(P7F_66_I2CM_STR2, _TYPEC_IIC0_SHPC_XTAL);

        // Set SCL low period count
        ScalerSetByte(P7F_67_I2CM_STR3, _TYPEC_IIC0_SLPC_XTAL);

        // Set fall time period count
        ScalerSetByte(P7F_6E_I2CM_STR4, _TYPEC_IIC0_FTPC_XTAL);

        // Set I2C Master Repeated_Start
        ScalerSetByte(P7F_6F_I2CM_STR5, _TYPEC_IIC0_THD_STA_C_XTAL);
    }
    else
    {
        // Set Clock Source to IOSC
        ScalerSetBit(P7F_03_10B_ADC_CLK_CLRT, ~(_BIT7 | _BIT6), 0x00);

        // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
        ScalerSetByte(P7F_61_I2CM_CR1, _TYPEC_IIC0_TOR_IOSC);

        // Set freq. divisor: ref = IOSC/(FD10+1) = 9.3M(ref should be approx 10MHz)
        ScalerSetByte(P7F_6A_I2CM_CCR, _TYPEC_IIC0_FD10_IOSC);

        // Set STA setup time period count
        ScalerSetByte(P7F_65_I2CM_STR1, _TYPEC_IIC0_STA_SUGPIO_C_IOSC);

        // Set SCL high period count
        ScalerSetByte(P7F_66_I2CM_STR2, _TYPEC_IIC0_SHPC_IOSC);

        // Set SCL low period count
        ScalerSetByte(P7F_67_I2CM_STR3, _TYPEC_IIC0_SLPC_IOSC);

        // Set fall time period count
        ScalerSetByte(P7F_6E_I2CM_STR4, _TYPEC_IIC0_FTPC_IOSC);

        // Set I2C Master Repeated_Start
        ScalerSetByte(P7F_6F_I2CM_STR5, _TYPEC_IIC0_THD_STA_C_IOSC);
    }
}

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuTypecIIC0WritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum)
{
    BYTE ucSubAddress = 0x00;
    BYTE ucLength = 0;
    BYTE ucTimeOutCnt = _IIC_POLLING_TIME;

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

    ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    switch(ucSubAddrLength)
    {
        case 0:

            break;

        case 1:

            // Set data length
            ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ucLength << 1);

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, ucSubAddress);

            break;

        case 2:

            // Set data length
            ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (ucLength + 1) << 1);

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, ucSubAddress);

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, ucSubAddress);
            break;

        default:

            break;
    }

    // IIC command Start
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT6, _BIT6);

    // Wait until Master Transmit Complete
    ucTimeOutCnt = _IIC_POLLING_TIME;

    while(ScalerGetBit(P7F_68_I2CM_SR, _BIT0) != _BIT0)
    {
        ucTimeOutCnt--;

        DELAY_5US();

        if(ucTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            return _FAIL;
        }
    }

    // Clear all flags
    ScalerSetByte(P7F_68_I2CM_SR, (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}
#endif // End of #if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Read data from the selected device by Type-C IIC0
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuTypecIIC0Read(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum)
{
    BYTE ucI = 0;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _HW_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

            // Set no repeat start
            ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

            // Load Slave Address to receive data
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 1:

            // Set 2 bytes for FRSIB
            ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT0);

            // Set one repeat start
            ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        case 2:

            // Set 3 bytes for FRSIB
            ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), _BIT1);

            // Set one repeat start
            ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), _BIT3);

            // Load Slave Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Load Slave Address to receive data
            ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _READ));

            break;

        default:

            break;
    }

    // Set data length
    ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ((ucDataLength - 1) << 1));

    // IIC command Start
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT6, _BIT6);

    // Wait until Master Receive Complete
    if(ScalerTimerPollingFlagProc(4, P7F_68_I2CM_SR, _BIT1, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = ScalerGetByte(P7F_69_I2CM_TD);
        pucReadArray++;
    }

    // Clear all flags
    ScalerSetByte(P7F_68_I2CM_SR, (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by Type-C IIC0
// Input Value  : ucSlaveAddr  --> Slave address
//                usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuTypecIIC0Write(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum)
{
    BYTE ucI = 0;
    BYTE ucTempLength = 0;

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

    // Enable IIC module
    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

    // Set 1 byte for FRSIB
    ScalerSetBit(P7F_62_I2CM_CR2, ~(_BIT1 | _BIT0), 0x00);

    // Set no repeat start
    ScalerSetBit(P7F_63_I2CM_CR3, ~(_BIT4 | _BIT3), 0x00);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    if(ScalerTimerPollingFlagProc(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
    {
        DebugMessageScaler("- IIC Write Time Out: FIFO Clock", 0xC1);

        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        return _FAIL;
    }

    // Load Slave Address to IIC Buffer
    ScalerSetByte(P7F_69_I2CM_TD, (ucSlaveAddr | _WRITE));

    ScalerSetBit(P7F_60_I2CM_CR0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    if(ucDataLength > 16)
    {
        pData[0] = 16;
    }
    else
    {
        pData[0] = ucDataLength;
    }

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = (pData[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)((usSubAddr & 0xFF00) >> 8));

            // Load Second Sub-Address to IIC Buffer
            ScalerSetByte(P7F_69_I2CM_TD, (BYTE)(usSubAddr));

            // Set data length
            ucTempLength = ((pData[0] + 1) << 1);

            break;

        default:

            break;
    }

    if(ucDataLength <= 16)
    {
        // Load data to IIC buffer for transmission
        for(ucI = 0; ucI < pData[0]; ucI++)
        {
            ScalerSetByte(P7F_69_I2CM_TD, *pucWriteArray++);
        }

        // Send IIC command Start
        ScalerSetByte(P7F_60_I2CM_CR0, (0xC0 + ucTempLength));
    }
    else
    {
        BYTE ucBurstNum = 0;
        BYTE ucBurstCnt = 0;

        // Disable HW TOR
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT0, 0x00);

        // Enable Burst Mode
        ScalerSetBit(P7F_62_I2CM_CR2, ~_BIT6, _BIT6);

        // Calculate Burst Command
        ucBurstNum = (ucDataLength / 16) + ((ucDataLength % 16) ? 1 : 0);

        if(pData[0] != 0)
        {
            // Load data to IIC buffer for transmission
            for(ucI = 0; ucI < pData[0]; ucI++)
            {
                ScalerSetByte(P7F_69_I2CM_TD, *pucWriteArray++);
            }
        }

        // Set Length and First Burst Command Start, Must Keep FF55[6] = 1 until Burst Mode end
        ScalerSetByte(P7F_60_I2CM_CR0, 0xC0 + ucTempLength);

        // Update Remaider Data Length
        ucDataLength = ucDataLength - pData[0];

        if(ucDataLength > 16)
        {
            pData[0] = 16;
        }
        else
        {
            pData[0] = ucDataLength;
        }

        // Wait into Burst Wait State
        if(ScalerTimerPollingFlagProc(3, P7F_68_I2CM_SR, _BIT3, _TRUE) == _FALSE)
        {
            DebugMessageScaler("- IIC Write Time Out: Burst Mode", 0xC3);

            // Reset(Block) IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

            // Enable IIC module
            ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

            // Disable Burst Mode
            ScalerSetBit(P7F_62_I2CM_CR2, ~_BIT6, 0x00);

            return _FAIL;
        }

        // After the first write
        for(ucBurstCnt = 1; ucBurstCnt < ucBurstNum; ucBurstCnt++)
        {
            // Wait I2C Fifo Clk Switch to Mcu Clk
            if(ScalerTimerPollingFlagProc(2, P7F_68_I2CM_SR, _BIT5, _TRUE) == _FALSE)
            {
                DebugMessageScaler("- IIC Write Time Out: FIFO Clock", 0xC2);

                // Reset(Block) IIC module
                ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

                // Enable IIC module
                ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

                // Disable Burst Mode
                ScalerSetBit(P7F_62_I2CM_CR2, ~_BIT6, 0x00);

                return _FAIL;
            }

            if(pData[0] != 0)
            {
                // Load data to IIC buffer for transmission
                for(ucI = 0; ucI < pData[0]; ucI++)
                {
                    ScalerSetByte(P7F_69_I2CM_TD, *pucWriteArray++);
                }

                // Set data length
                ucTempLength = ((pData[0] - 1) << 1) & (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1);
            }

            // Set Length and First Burst Command Start, Must Keep FF55[6] = 1 until Burst Mode end
            ScalerSetByte(P7F_60_I2CM_CR0, 0xC0 + ucTempLength);

            // Update Remaider Data Length
            ucDataLength = ucDataLength - pData[0];

            if(ucDataLength > 16)
            {
                pData[0] = 16;
            }
            else
            {
                pData[0] = ucDataLength;
            }

            // Burst write again
            ScalerSetBit(P7F_68_I2CM_SR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

            if(ucBurstCnt != (ucBurstNum - 1))
            {
                // Wait into Burst Wait State
                if(ScalerTimerPollingFlagProc(3, P7F_68_I2CM_SR, _BIT3, _TRUE) == _FALSE)
                {
                    DebugMessageScaler("- IIC Write Time Out: Burst Mode", 0xC3);

                    // Reset(Block) IIC module
                    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

                    // Enable IIC module
                    ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

                    // Disable Burst Mode
                    ScalerSetBit(P7F_62_I2CM_CR2, ~_BIT6, 0x00);

                    return _FAIL;
                }
            }
        }
        // Disable Burst Write
        ScalerSetBit(P7F_62_I2CM_CR2, ~_BIT6, 0x00);
    }

    // Wait until Master Transmit Complete
    if(ScalerTimerPollingFlagProc(4, P7F_68_I2CM_SR, _BIT0, _TRUE) == _FALSE)
    {
        DebugMessageScaler("- IIC Write Time Out: Transmit", 0xC4);

        // Reset(Block) IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, 0x00);

        // Enable IIC module
        ScalerSetBit(P7F_60_I2CM_CR0, ~_BIT7, _BIT7);

        // Disable Burst Mode
        ScalerSetBit(P7F_62_I2CM_CR2, ~_BIT6, 0x00);

        return _FAIL;
    }

    // Clear all flags
    ScalerSetByte(P7F_68_I2CM_SR, (_BIT2 | _BIT1 | _BIT0));

    return _SUCCESS;
}
#endif // End of #if(_TYPEC_IIC_0_SUPPORT == _ON)

//--------------------------------------------------
// Description  : ISP Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIspInitial(void)
{
    // MCU_FFEE_MCU_CLOCK_CONTROL in RLE1039 doesn't have BIT6
    // Keep mcu peripheral(timer) running while mcu stopped by spi flash access
    // MCU_FFEE_MCU_CLOCK_CONTROL |= _BIT6;

#if(_ISP_CHANNEL_PROTECT_SUPPORT == _ON)
    // ISP channel initial select for Hub
    ScalerMcuSetISPChannel(_ISP_CHANNEL_EN_FW_RUN);

    // Set Error ISP Slave Address
    ScalerMcuSetISPSlaveAddr(_DISABLE);
#else
    // Enable ISP Channel and Set Defualt ISP Slave Address
    ScalerMcuSetISPChannel(0xFFFF);

    // Set Error ISP Slave Address
    ScalerMcuSetISPSlaveAddr(_ENABLE);
#endif
}

//--------------------------------------------------
// Description  : Low Power Consumption Setting For Mcu Module.
// Input Value  : enumPowAction
// Output Value : None
//--------------------------------------------------
void ScalerMcuPwmControl(EnumPowerStatus enumPowStatus)
{
    BYTE ucPwmEn = 0;

    if(enumPowStatus == _POWER_STATUS_NORMAL)
    {
        ucPwmEn = (((BYTE)_PWM5_EN << 5) |
                   ((BYTE)_PWM4_EN << 4) |
                   ((BYTE)_PWM3_EN << 3) |
                   ((BYTE)_PWM2_EN << 2) |
                   ((BYTE)_PWM1_EN << 1) |
                   ((BYTE)_PWM0_EN));
        // PWM output clock stop disable
        ScalerSetBit(PFF_F2_PWM_I2C_CLOCK_STOP, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (~ucPwmEn & 0x3F));
        // PWM Output Enable
        ScalerSetBit(PFF_48_PWM_EN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ucPwmEn & 0x3F));
#if(_PWM_RST_SIGNAL_SEL == _TCON)
        // Enable TCON
        ScalerTconEnable(_ON);
        // Enable PWM reset by TCON
        MCU_FF47_PWM_VS_CTRL |= _BIT6;
#endif
    }
    else if(enumPowStatus == _POWER_STATUS_SAVING)
    {
        ucPwmEn = (((BYTE)_PWM5_PSAV_EN << 5) |
                   ((BYTE)_PWM4_PSAV_EN << 4) |
                   ((BYTE)_PWM3_PSAV_EN << 3) |
                   ((BYTE)_PWM2_PSAV_EN << 2) |
                   ((BYTE)_PWM1_PSAV_EN << 1) |
                   ((BYTE)_PWM0_PSAV_EN));
        // PWM Output Enable
        ScalerSetBit(PFF_48_PWM_EN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ucPwmEn & 0x3F));

        // PWM output clock stop disable
        ScalerSetBit(PFF_F2_PWM_I2C_CLOCK_STOP, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (~ucPwmEn & 0x3F));
    }
    else if(enumPowStatus == _POWER_STATUS_OFF)
    {
        ucPwmEn = (((BYTE)_PWM5_PDOW_EN << 5) |
                   ((BYTE)_PWM4_PDOW_EN << 4) |
                   ((BYTE)_PWM3_PDOW_EN << 3) |
                   ((BYTE)_PWM2_PDOW_EN << 2) |
                   ((BYTE)_PWM1_PDOW_EN << 1) |
                   ((BYTE)_PWM0_PDOW_EN));
        // PWM Output Enable
        ScalerSetBit(PFF_48_PWM_EN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ucPwmEn & 0x3F));

        // PWM output clock stop disable
        ScalerSetBit(PFF_F2_PWM_I2C_CLOCK_STOP, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (~ucPwmEn & 0x3F));
    }
    else
    {
        // PWM Output Disable
        ScalerSetBit(PFF_48_PWM_EN, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // PWM Output Clock Stop Enable
        ScalerSetBit(PFF_F2_PWM_I2C_CLOCK_STOP, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3F);
    }
}

//--------------------------------------------------
// Description  : Clear DDCCI0 IRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuClearDdcci0IRQFlag(void)
{
    // Clear IRQ FLag
    MCU_FF27_IIC_STATUS = 0x00;
    // Read IIC Data In(0xFF25) to Clear Data In Flag
    pData[0] = MCU_FF25_IIC_DATA_IN;
    // Write IIC Data Out(0xFF26) to Clear Data Out Flag
    MCU_FF26_IIC_DATA_OUT = 0x00;
    // Clear IIC Buffer Overflow or Underflow Flag
    MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);
    // Reset IIC Buffer
    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
}

//--------------------------------------------------
// Description  : DDCCI switch DDC Port
// Input Value  : enumMode --> Debug or DDCCI Mode
//                enumInputPort --> Input Port Type
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciSwitchPort(EnumDDCCIDebugMode enumMode)
{
#if(_AUTO_TEST_SUPPORT == _ON)
    // Set slave address for DDCCI
    MCU_FF23_IIC_SET_SLAVE = 0x3E;

    // Disable STOP_I, Enable D_IN_I, SUB_I interrupts
    ScalerSetBit(PFF_28_IIC_IRQ_CONTROL, ~(_BIT4 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    return;
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    // Force to debug mode when debug message is enable
    enumMode = _DEBUG_MODE;
#endif

    if(enumMode == _DDCCI_MODE)
    {
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
        CLR_DDCCI_SWITCH_STATE();
#endif
        // Set slave address for DDCCI
        MCU_FF23_IIC_SET_SLAVE = 0x6E;

        // Disable STOP_I, Enable D_IN_I, SUB_I interrupts
        MCU_FF28_IIC_IRQ_CONTROL &= ~_BIT4;
        // Debug Mode Change to DDCCI Mode Need Clear IRQ Flag
        if(ScalerDebugGetDDCCIDebugMode() != enumMode)
        {
            ScalerMcuClearDdcci0IRQFlag();
        }
        MCU_FF28_IIC_IRQ_CONTROL |= _BIT2 | _BIT1;

#if(_MULTI_DISPLAY_MAX >= 0x02)
        // Set slave address for DDCCI
        MCU_FE87_IIC_1_SET_SLAVE = 0x6E;

        // Enable D_IN_I, SUB_I interrupts
        MCU_FE8C_IIC_1_IRQ_CONTROL |= _BIT2 | _BIT1;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
        // Set slave address for DDCCI
        MCU_FE95_IIC_2_SET_SLAVE = 0x6E;

        // Enable D_IN_I, SUB_I interrupts
        MCU_FE9A_IIC_2_IRQ_CONTROL |= _BIT2 | _BIT1;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
        // Set slave address for DDCCI
        MCU_FEA4_IIC_3_SET_SLAVE = 0x6E;

        // Enable D_IN_I, SUB_I interrupts
        MCU_FEA9_IIC_3_IRQ_CONTROL |= _BIT2 | _BIT1;
#endif
    }
    else
    {
        // Set slave address for debug tool
        MCU_FF23_IIC_SET_SLAVE = 0x6A;

        // Disable STOP_I, D_IN_I, SUB_I interrupts
        MCU_FF28_IIC_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
        // Debug Mode Change to DDCCI Mode Need Clear IRQ Flag
        if(ScalerDebugGetDDCCIDebugMode() != enumMode)
        {
            ScalerMcuClearDdcci0IRQFlag();
        }
        // Enable STOP_I, D_IN_I, SUB_I interrupts
        MCU_FF28_IIC_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;

        // Setting 0xFF22 is invalid if DDCCI auto switch enable
        if(GET_DDCCI_AUTO_SWITCH() == _TRUE)
        {
            CLR_DDCCI_AUTO_SWITCH();
        }

#if((_DEBUG_DDC_CHANNEL_SEL == _DDC5) && (_HW_DDC5_EXIST == _ON))
        // DDC from DDC5 channel
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC4) && (_HW_DDC4_EXIST == _ON))
        // DDC from DDC4 channel
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC3) && (_HW_DDC3_EXIST == _ON))
        // DDC from DDC3 channel
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC2) && (_HW_DDC2_EXIST == _ON))
        // DDC from DDC2 channel
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC1) && (_HW_DDC1_EXIST == _ON))
        // DDC from DDC1 channel
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC0) && (_HW_DDC0_EXIST == _ON))
        // DDC from DDC0 channel
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) && (_HW_ISP_DDC_EXIST == _ON))
        // DDC from VGA_DDC channel
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif

        //////////////////////////////////////////////////////////////////
        /////////////////////Disable DDCCI 1~3 ///////////////////////////
        //////////////////////////////////////////////////////////////////
        // Config ddc-ci address to no used addaress
#if(_HW_DDCCI1_EXIST == _ON)
        MCU_FE87_IIC_1_SET_SLAVE = 0x3C;
#endif

#if(_HW_DDCCI2_EXIST == _ON)
        MCU_FE95_IIC_2_SET_SLAVE = 0x3C;
#endif

#if(_HW_DDCCI3_EXIST == _ON)
        MCU_FEA4_IIC_3_SET_SLAVE = 0x3C;
#endif

        // Disable all ddc interrupt
#if(_HW_DDCCI1_EXIST == _ON)
        MCU_FE8C_IIC_1_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
#endif

#if(_HW_DDCCI2_EXIST == _ON)
        MCU_FE9A_IIC_2_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
#endif

#if(_HW_DDCCI3_EXIST == _ON)
        MCU_FEA9_IIC_3_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
#endif

        // Config none ddc port
#if(_HW_DDCCI1_EXIST == _ON)
        ScalerSetBit(PFE_86_IIC_1_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif

#if(_HW_DDCCI2_EXIST == _ON)
        ScalerSetBit(PFE_94_IIC_2_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif

#if(_HW_DDCCI3_EXIST == _ON)
        ScalerSetBit(PFE_A3_IIC_3_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
#endif
    }
    ScalerDebugSelectDDCCIDebugMode(enumMode);
}

//--------------------------------------------------
// Description  : DDC Debounce Settings
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcDebounceSel(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
#if(_VGA_SUPPORT == _ON)
        // VGA_DDC De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        ScalerSetBit(PFF_1C_ADC_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
#endif

#if(_D0_DP_SUPPORT == _ON)
        // DDC0 De-bounce Reference Clock(Xtal = 14.318M) div by 1, latch 1 stages
        ScalerSetBit(PFF_1F_DDC0_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
        // DDC0 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        ScalerSetBit(PFF_1F_DDC0_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
#endif

#if(_D1_DP_SUPPORT == _ON)
        // DDC1 De-bounce Reference Clock(Xtal = 14.318M) div by 1, latch 1 stages
        ScalerSetBit(PFF_2D_DDC1_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
        // DDC1 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        ScalerSetBit(PFF_2D_DDC1_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
#endif

#if(_D2_DP_SUPPORT == _ON)
        // DDC2 De-bounce Reference Clock(Xtal = 14.318M) div by 1, latch 1 stages
        ScalerSetBit(PFE_65_DDC2_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
        // DDC2 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        ScalerSetBit(PFE_65_DDC2_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
#endif

#if(_D3_DP_SUPPORT == _ON)
        // DDC3 De-bounce Reference Clock(Xtal = 14.318M) div by 1, latch 1 stages
        ScalerSetBit(PFE_6E_DDC3_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
#elif(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
        // DDC3 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        ScalerSetBit(PFE_6E_DDC3_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
#endif

#if(_D4_DP_SUPPORT == _ON)
        // DDC4 De-bounce Reference Clock(Xtal = 14.318M) div by 1, latch 1 stages
        ScalerSetBit(PFE_77_DDC4_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
#elif(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
        // DDC4 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        ScalerSetBit(PFE_77_DDC4_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
#endif

#if(_D5_DP_SUPPORT == _ON)
        // DDC5 De-bounce Reference Clock(Xtal = 14.318M) div by 1, latch 1 stages
        ScalerSetBit(PFE_80_DDC5_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
#elif(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
        // DDC5 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        ScalerSetBit(PFE_80_DDC5_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
#endif
    }
    else
    {
#if(_VGA_SUPPORT == _ON)
        // VGA_DDC De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        ScalerSetBit(PFF_1C_ADC_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#endif

#if(_D0_DP_SUPPORT == _ON)
        // DDC0 De-bounce Reference Clock(IOSC = 27M) div by 2, latch 1 stages
        ScalerSetBit(PFF_1F_DDC0_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
        // DDC0 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        ScalerSetBit(PFF_1F_DDC0_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#endif

#if(_D1_DP_SUPPORT == _ON)
        // DDC1 De-bounce Reference Clock(IOSC = 27M) div by 2, latch 1 stages
        ScalerSetBit(PFF_2D_DDC1_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
        // DDC1 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        ScalerSetBit(PFF_2D_DDC1_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#endif

#if(_D2_DP_SUPPORT == _ON)
        // DDC2 De-bounce Reference Clock(IOSC = 27M) div by 2, latch 1 stages
        ScalerSetBit(PFE_65_DDC2_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
        // DDC2 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        ScalerSetBit(PFE_65_DDC2_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#endif

#if(_D3_DP_SUPPORT == _ON)
        // DDC3 De-bounce Reference Clock(IOSC = 27M) div by 2, latch 1 stages
        ScalerSetBit(PFE_6E_DDC3_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
#elif(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
        // DDC3 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        ScalerSetBit(PFE_6E_DDC3_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#endif

#if(_D4_DP_SUPPORT == _ON)
        // DDC4 De-bounce Reference Clock(IOSC = 27M) div by 2, latch 1 stages
        ScalerSetBit(PFE_77_DDC4_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
#elif(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
        // DDC4 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        ScalerSetBit(PFE_77_DDC4_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#endif

#if(_D5_DP_SUPPORT == _ON)
        // DDC5 De-bounce Reference Clock(IOSC = 27M) div by 2, latch 1 stages
        ScalerSetBit(PFE_80_DDC5_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
#elif(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
        // DDC5 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        ScalerSetBit(PFE_80_DDC5_DDC_CONTROL_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#endif
    }
}

//--------------------------------------------------
// Description  : DDC Debounce Adjust
// Input Value  : enumInputPort --> Input Port
//                enumDdcDbnSelMode --> Normal Mode/Speed up Mode
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcDebounceSelByPort(EnumInputPort enumInputPort, EnumDdcDbnSelMode enumDdcDbnSelMode)
{
    if(enumDdcDbnSelMode == _DBN_SEL_SPEED_UP_MODE)
    {
        switch(ScalerMcuGetDdcChannelFromInputPort(enumInputPort))
        {
#if(_HW_ISP_DDC_EXIST == _ON)
            case _VGA_DDC:
                // Speed up mode, VGA_DDC De-bounce Reference Clock div by 1
                ScalerSetBit(PFF_1C_ADC_DDC_CONTROL_1, ~(_BIT7 | _BIT6), 0x00);
                break;
#endif

#if(_HW_DDC0_EXIST == _ON)
            case _DDC0:
                // Speed up mode, DDC0 De-bounce Reference Clock div by 1
                ScalerSetBit(PFF_1F_DDC0_DDC_CONTROL_1, ~(_BIT7 | _BIT6), 0x00);
                break;
#endif

#if(_HW_DDC1_EXIST == _ON)
            case _DDC1:
                // Speed up mode, DDC1 De-bounce Reference Clock div by 1
                ScalerSetBit(PFF_2D_DDC1_DDC_CONTROL_1, ~(_BIT7 | _BIT6), 0x00);
                break;
#endif

#if(_HW_DDC2_EXIST == _ON)
            case _DDC2:
                // Speed up mode, DDC2 De-bounce Reference Clock div by 1
                ScalerSetBit(PFE_65_DDC2_DDC_CONTROL_1, ~(_BIT7 | _BIT6), 0x00);
                break;
#endif

#if(_HW_DDC3_EXIST == _ON)
            case _DDC3:
                // Speed up mode, DDC3 De-bounce Reference Clock div by 1
                ScalerSetBit(PFE_6E_DDC3_DDC_CONTROL_1, ~(_BIT7 | _BIT6), 0x00);
                break;
#endif

#if(_HW_DDC4_EXIST == _ON)
            case _DDC4:
                // Speed up mode, DDC4 De-bounce Reference Clock div by 1
                ScalerSetBit(PFE_77_DDC4_DDC_CONTROL_1, ~(_BIT7 | _BIT6), 0x00);
                break;
#endif

#if(_HW_DDC5_EXIST == _ON)
            case _DDC5:
                // Speed up mode, DDC5 De-bounce Reference Clock div by 1
                ScalerSetBit(PFE_80_DDC5_DDC_CONTROL_1, ~(_BIT7 | _BIT6), 0x00);
                break;
#endif

            default:
                break;
        }
    }
    else
    {
        if((ScalerGetByte(P0_09_GA_POWER_CTRL) & _BIT3) == 0x00)
        {
            // _EXT_XTAL_CLK
            ScalerMcuDdcDebounceSel(_EXT_XTAL_CLK);
        }
        else
        {
            // _IOSC_CLK
            ScalerMcuDdcDebounceSel(_IOSC_CLK);
        }
    }
}

//--------------------------------------------------
// Description  : DDC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcInitial(void)
{
    // disable MXIC function, not allow DDC2B access in ISP mode, ddc can progrom
    ScalerSetBit(PFF_E9_MCU_CLK_CONTROL_1, ~_BIT5, 0x00);

    // DDC Port DDCRAM Block Config
    ScalerMcuDdcramConfig();

    // DDC Debounce Settings
    ScalerMcuDdcDebounceSel(_EXT_XTAL_CLK);

#if(_HW_ISP_DDC_EXIST == _ON)
    // Disable DDC Segment for VGA_DDC
    ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);

    // Slave address 0xA0 for VGA_DDC
    MCU_FF1B_ADC_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Force ADC_DDC to DDC2 Mode
    ScalerSetBit(PFF_1C_ADC_DDC_CONTROL_1, ~_BIT2, _BIT2);

    // VGA_DDC Debounce reference clock from Xtal
    ScalerSetBit(PFF_1C_ADC_DDC_CONTROL_1, ~_BIT3, 0x00);

    // A0 DDC force Nack
    ScalerSetBit(PFF_E7_VGA_EDID_IRQ, ~_BIT5, _BIT5);

    // Release VGA DDC SCL Pin force to Low
    ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#endif

#if(_HW_DDC0_EXIST == _ON)
    // Disable DDC Segment for DDC0
    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);

    // Slave address 0xA0 for DDC0
    MCU_FF1E_DDC0_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Force DDC to DDC2 Mode
    ScalerSetBit(PFF_1F_DDC0_DDC_CONTROL_1, ~_BIT2, _BIT2);

    // DDC0 Debounce reference clock from Xtal
    ScalerSetBit(PFF_1F_DDC0_DDC_CONTROL_1, ~_BIT3, 0x00);

    // D0 DDC force Nack
    ScalerSetBit(PFF_E4_DDC0_EDID_IRQ, ~_BIT5, _BIT5);

    // Release DDC0 SCL Pin force to Low
    ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#endif

#if(_HW_DDC1_EXIST == _ON)
    // Disable DDC Segment for DDC1
    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);

    // Slave address 0xA0 for DDC1
    MCU_FF2C_DDC1_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Force DDC to DDC2 Mode
    ScalerSetBit(PFF_2D_DDC1_DDC_CONTROL_1, ~_BIT2, _BIT2);

    // DDC1 Debounce reference clock from Xtal
    ScalerSetBit(PFF_2D_DDC1_DDC_CONTROL_1, ~_BIT3, 0x00);

    // D1 DDC force Nack
    ScalerSetBit(PFF_E5_DDC1_EDID_IRQ, ~_BIT5, _BIT5);

    // Release DDC1 SCL Pin force to Low
    ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#endif

#if(_HW_DDC2_EXIST == _ON)
    // Disable DDC Segment for DDC2
    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);

    // Slave address 0xA0 for DDC2
    MCU_FE64_DDC2_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Force DDC to DDC2 Mode
    ScalerSetBit(PFE_65_DDC2_DDC_CONTROL_1, ~_BIT2, _BIT2);

    // DDC2 Debounce reference clock from Xtal
    ScalerSetBit(PFE_65_DDC2_DDC_CONTROL_1, ~_BIT3, 0x00);

    // D2 DDC force Nack
    ScalerSetBit(PFE_69_DDC2_EDID_IRQ, ~_BIT5, _BIT5);

    // Release DDC2 SCL Pin force to Low
    ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#endif

#if(_HW_DDC3_EXIST == _ON)
    // Disable DDC Segment for DDC3
    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);

    // Slave address 0xA0 for DDC3
    MCU_FE6D_DDC3_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Force DDC to DDC2 Mode
    ScalerSetBit(PFE_6E_DDC3_DDC_CONTROL_1, ~_BIT2, _BIT2);

    // DDC3 Debounce reference clock from Xtal
    ScalerSetBit(PFE_6E_DDC3_DDC_CONTROL_1, ~_BIT3, 0x00);

    // D3 DDC force Nack
    ScalerSetBit(PFE_72_DDC3_EDID_IRQ, ~_BIT5, _BIT5);

    // Release DDC3 SCL Pin force to Low
    ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#endif

#if(_HW_DDC4_EXIST == _ON)
    // Disable DDC Segment for DDC4
    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);

    // Slave address 0xA0 for DDC4
    MCU_FE76_DDC4_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Force DDC to DDC2 Mode
    ScalerSetBit(PFE_77_DDC4_DDC_CONTROL_1, ~_BIT2, _BIT2);

    // DDC4 Debounce reference clock from Xtal
    ScalerSetBit(PFE_77_DDC4_DDC_CONTROL_1, ~_BIT3, 0x00);

    // D4 DDC force Nack
    ScalerSetBit(PFE_7B_DDC4_EDID_IRQ, ~_BIT5, _BIT5);

    // Release DDC4 SCL Pin force to Low
    ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#endif

#if(_HW_DDC5_EXIST == _ON)
    // Disable DDC Segment for DDC5
    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);

    // Slave address 0xA0 for DDC5
    MCU_FE7F_DDC5_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Force DDC to DDC2 Mode
    ScalerSetBit(PFE_80_DDC5_DDC_CONTROL_1, ~_BIT2, _BIT2);

    // DDC5 Debounce reference clock from Xtal
    ScalerSetBit(PFE_80_DDC5_DDC_CONTROL_1, ~_BIT3, 0x00);

    // D5 DDC force Nack
    ScalerSetBit(PFE_84_DDC5_EDID_IRQ, ~_BIT5, _BIT5);

    // Release DDC5 SCL Pin force to Low
    ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#endif
}

//--------------------------------------------------
// Description  : Enable DDC Ram
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcRamEnable(void)
{
#if(_HW_ISP_DDC_EXIST == _ON)
    // VGA_DDC Debounce Enable, ADC DDC channel enable
    MCU_FF1B_ADC_DDC_ENABLE |= (_BIT1 | _BIT0);
#endif

#if(_HW_DDC0_EXIST == _ON)
    // DDC0 Debounce Enable, DDC0 channel enable
    MCU_FF1E_DDC0_DDC_ENABLE |= (_BIT1 | _BIT0);
#endif

#if(_HW_DDC1_EXIST == _ON)
    // DDC1 Debounce Enable, DDC1 channel enable
    MCU_FF2C_DDC1_DDC_ENABLE |= (_BIT1 | _BIT0);
#endif

#if(_HW_DDC2_EXIST == _ON)
    // DDC2 Debounce Enable, DDC2 channel enable
    MCU_FE64_DDC2_DDC_ENABLE |= (_BIT1 | _BIT0);
#endif

#if(_HW_DDC3_EXIST == _ON)
    // DDC3 Debounce Enable, DDC3 channel enable
    MCU_FE6D_DDC3_DDC_ENABLE |= (_BIT1 | _BIT0);
#endif

#if(_HW_DDC4_EXIST == _ON)
    // DDC4 Debounce Enable, DDC4 channel enable
    MCU_FE76_DDC4_DDC_ENABLE |= (_BIT1 | _BIT0);
#endif

#if(_HW_DDC5_EXIST == _ON)
    // DDC5 Debounce Enable, DDC5 channel enable
    MCU_FE7F_DDC5_DDC_ENABLE |= (_BIT1 | _BIT0);
#endif
}

//--------------------------------------------------
// Description  : GPIO Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuGpioInitial(void)
{
    // Port_pin_reg_n signal is enabled (P1, P3 GPI->Bus Value)
    ScalerSetBit(PFF_ED_MCU_CONTROL, ~_BIT7, _BIT7);

    // Source selection for All-Port, read back from bus value
    MCU_FE60_PORT_READ_CONTROL = 0xFF;
    MCU_FE61_PORT_READ_CONTROL_2 = 0xFF;
    MCU_229A_PORT_READ_CONTROL_3 = 0xFF;
#if(_HW_GPIO_PORT_18_1F_SUPPORT == _ON)
    MCU_229B_PORT_READ_CONTROL_4 = 0xFF;
#endif

#if(_DELL_HDMI_HPD_DDC_STYLE_SUPPORT == _OFF)
    PCB_D0_HOTPLUG((_D0_DP_SUPPORT == _ON) ? _D0_HOT_PLUG_LOW : _D0_HOT_PLUG_HIGH);
    PCB_D1_HOTPLUG((_D1_DP_SUPPORT == _ON) ? _D1_HOT_PLUG_LOW : _D1_HOT_PLUG_HIGH);
    PCB_D2_HOTPLUG((_D2_DP_SUPPORT == _ON) ? _D2_HOT_PLUG_LOW : _D2_HOT_PLUG_HIGH);
    PCB_D3_HOTPLUG((_D3_DP_SUPPORT == _ON) ? _D3_HOT_PLUG_LOW : _D3_HOT_PLUG_HIGH);
    PCB_D4_HOTPLUG((_D4_DP_SUPPORT == _ON) ? _D4_HOT_PLUG_LOW : _D4_HOT_PLUG_HIGH);
    PCB_D5_HOTPLUG((_D5_DP_SUPPORT == _ON) ? _D5_HOT_PLUG_LOW : _D5_HOT_PLUG_HIGH);
#else
    // HDMI HPD set low as initial value
    PCB_D0_HOTPLUG(((_D0_DP_SUPPORT == _ON) || (_D0_HDMI_SUPPORT == _ON)) ? _D0_HOT_PLUG_LOW : _D0_HOT_PLUG_HIGH);
    PCB_D1_HOTPLUG(((_D1_DP_SUPPORT == _ON) || (_D1_HDMI_SUPPORT == _ON)) ? _D1_HOT_PLUG_LOW : _D1_HOT_PLUG_HIGH);
    PCB_D2_HOTPLUG(((_D2_DP_SUPPORT == _ON) || (_D2_HDMI_SUPPORT == _ON)) ? _D2_HOT_PLUG_LOW : _D2_HOT_PLUG_HIGH);
    PCB_D3_HOTPLUG(((_D3_DP_SUPPORT == _ON) || (_D3_HDMI_SUPPORT == _ON)) ? _D3_HOT_PLUG_LOW : _D3_HOT_PLUG_HIGH);
    PCB_D4_HOTPLUG(((_D4_DP_SUPPORT == _ON) || (_D4_HDMI_SUPPORT == _ON)) ? _D4_HOT_PLUG_LOW : _D4_HOT_PLUG_HIGH);
    PCB_D5_HOTPLUG(((_D5_DP_SUPPORT == _ON) || (_D5_HDMI_SUPPORT == _ON)) ? _D5_HOT_PLUG_LOW : _D5_HOT_PLUG_HIGH);
#endif

#if(_HDMI_SUPPORT == _ON)
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
    SET_D1_HDMI_5V_STATUS();
    SET_D2_HDMI_5V_STATUS();
    SET_D3_HDMI_5V_STATUS();
    SET_D4_HDMI_5V_STATUS();
    SET_D5_HDMI_5V_STATUS();
#endif
#endif

    PCB_A0_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
    PCB_D2_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
    PCB_D3_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
    PCB_D4_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
    PCB_D5_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

#if(_AUDIO_TTS_SUPPORT_TYPE == _AUDIO_TTS_EMBEDDED_TYPE)
    PCB_TTS_FLASH_WRITE_PROTECT(_TTS_FLASH_WRITE_PROTECT_ENABLE);
#endif

    // RX_LV Power cut
    PCB_SET_RX_LV_POWER(_RX_LV_POWER_ON);

    // VCCKOFF Power on
    PCB_VCCK_OFF_POWER(_VCCK_OFF_POWER_ON);

    // Wait for VCCK_OFF Power On Stable
    POLLING_VCCK_OFF_STATUS(_VCCK_OFF_TIME_POLLING_POWER_ON);

    // DDR Power on
    PCB_DDR_POWER(_DDR_POWER_ON);

    PCB_PANEL_POWER(_PANEL_CONTROL_OFF);
    PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);
    PCB_LED_AC_ON_INITIAL();

    PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON();
    PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON();

    // Initi External Edid Gpio in AC ON Case
    PCB_MULTI_EDID_SWITCH_POWER_AC_ON();
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DDC Reset
// Input Value  : enumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcReset(EnumInputPort enumInputPort)
{
    switch(ScalerMcuGetDdcChannelFromInputPort(enumInputPort))
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            ScalerSetBit(PFF_1C_ADC_DDC_CONTROL_1, ~_BIT1, _BIT1);
            break;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            ScalerSetBit(PFF_1F_DDC0_DDC_CONTROL_1, ~_BIT1, _BIT1);
            break;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            ScalerSetBit(PFF_2D_DDC1_DDC_CONTROL_1, ~_BIT1, _BIT1);
            break;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            ScalerSetBit(PFE_65_DDC2_DDC_CONTROL_1, ~_BIT1, _BIT1);
            break;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            ScalerSetBit(PFE_6E_DDC3_DDC_CONTROL_1, ~_BIT1, _BIT1);
            break;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            ScalerSetBit(PFE_77_DDC4_DDC_CONTROL_1, ~_BIT1, _BIT1);
            break;
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            ScalerSetBit(PFE_80_DDC5_DDC_CONTROL_1, ~_BIT1, _BIT1);
            break;
#endif

        default:
            break;
    }
}
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DDC Toggle Detect Flag
// Input Value  : enumInputPort
// Output Value : bit
//--------------------------------------------------
bit ScalerMcuDdcGetDdcDetectFlag(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:
            return GET_D1_TMDS_DDC_DETECTED();
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:
            return GET_D2_TMDS_DDC_DETECTED();
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:
            return GET_D3_TMDS_DDC_DETECTED();
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:
            return GET_D4_TMDS_DDC_DETECTED();
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:
            return GET_D5_TMDS_DDC_DETECTED();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Clear DDC Toggle Detect Flag
// Input Value  : enumInputPort
// Output Value :
//--------------------------------------------------
void ScalerMcuDdcClrDdcDetectFlag(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            CLR_D1_TMDS_DDC_DETECTED();
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            CLR_D2_TMDS_DDC_DETECTED();
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            CLR_D3_TMDS_DDC_DETECTED();
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

            CLR_D4_TMDS_DDC_DETECTED();
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

            CLR_D5_TMDS_DDC_DETECTED();
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DDC SCL Toggle IRQ Enable
// Input Value  : ucDDCx
// Output Value : None
//--------------------------------------------------
BYTE ScalerMcuDdcGetSclToggleIrqEnable(BYTE ucDDCx)
{
    switch(ucDDCx)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            return ((bit)ScalerGetBit(PFF_E7_VGA_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            return ((bit)ScalerGetBit(PFF_E4_DDC0_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            return ((bit)ScalerGetBit(PFF_E5_DDC1_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            return ((bit)ScalerGetBit(PFE_69_DDC2_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            return ((bit)ScalerGetBit(PFE_72_DDC3_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            return ((bit)ScalerGetBit(PFE_7B_DDC4_EDID_IRQ, _BIT3));
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            return ((bit)ScalerGetBit(PFE_84_DDC5_EDID_IRQ, _BIT3));
#endif

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Set DDC SCL Toggle IRQ Enable
// Input Value  : ucDDCx
// Input Value  : ucEnable
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcSetSclToggleIrqEnable(BYTE ucDDCx, BYTE ucEnable)
{
    switch(ucDDCx)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            ScalerSetBit(PFF_E7_VGA_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            ScalerSetBit(PFF_E4_DDC0_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            ScalerSetBit(PFF_E5_DDC1_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            ScalerSetBit(PFE_69_DDC2_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            ScalerSetBit(PFE_72_DDC3_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            ScalerSetBit(PFE_7B_DDC4_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            ScalerSetBit(PFE_84_DDC5_EDID_IRQ, ~(_BIT3 | _BIT2), ((ucEnable << 3) | _BIT2));
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set DDC EDID Read IRQ Enable
// Input Value  : ucDDCx
// Input Value  : ucEnable
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcSetEdidReadIrqEnable(BYTE ucDDCx, BYTE ucEnable)
{
    switch(ucDDCx)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            ScalerSetBit(PFF_E7_VGA_EDID_IRQ, ~(_BIT1 | _BIT0), ((ucEnable << 1) | _BIT0));
            break;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            ScalerSetBit(PFF_E4_DDC0_EDID_IRQ, ~(_BIT1 | _BIT0), ((ucEnable << 1) | _BIT0));
            break;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            ScalerSetBit(PFF_E5_DDC1_EDID_IRQ, ~(_BIT1 | _BIT0), ((ucEnable << 1) | _BIT0));
            break;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            ScalerSetBit(PFE_69_DDC2_EDID_IRQ, ~(_BIT1 | _BIT0), ((ucEnable << 1) | _BIT0));
            break;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            ScalerSetBit(PFE_72_DDC3_EDID_IRQ, ~(_BIT1 | _BIT0), ((ucEnable << 1) | _BIT0));
            break;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            ScalerSetBit(PFE_7B_DDC4_EDID_IRQ, ~(_BIT1 | _BIT0), ((ucEnable << 1) | _BIT0));
            break;
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            ScalerSetBit(PFE_84_DDC5_EDID_IRQ, ~(_BIT1 | _BIT0), ((ucEnable << 1) | _BIT0));
            break;
#endif

        default:
            break;
    }
}
#endif

#if((_HDMI_MULTI_EDID_SUPPORT == _ON) || (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON))
//--------------------------------------------------
// Description  : Clear DDC SCL Toggle IRQ Status
// Input Value  : ucDDCx
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcClearSclToggleIrqStatus(BYTE ucDDCx)
{
    switch(ucDDCx)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            ScalerSetBit(PFF_E7_VGA_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            ScalerSetBit(PFF_E4_DDC0_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            ScalerSetBit(PFF_E5_DDC1_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            ScalerSetBit(PFE_69_DDC2_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            ScalerSetBit(PFE_72_DDC3_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            ScalerSetBit(PFE_7B_DDC4_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            ScalerSetBit(PFE_84_DDC5_EDID_IRQ, ~_BIT2, _BIT2);
            break;
#endif

        default:
            break;
    }
}
#endif

#if((_HDMI_MULTI_EDID_SUPPORT == _ON) || (_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON) || (_HDMI_HPD_TOGGLE_BY_Z0_OFF_DDC_TOGGLE == _ON))
//--------------------------------------------------
// Description  : Get DDC SCL Toggle IRQ Status
// Input Value  : ucDDCx
// Output Value : None
//--------------------------------------------------
BYTE ScalerMcuDdcGetSclToggleIrqStatus(BYTE ucDDCx)
{
    switch(ucDDCx)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            return ((bit)ScalerGetBit(PFF_E7_VGA_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            return ((bit)ScalerGetBit(PFF_E4_DDC0_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            return ((bit)ScalerGetBit(PFF_E5_DDC1_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            return ((bit)ScalerGetBit(PFE_69_DDC2_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            return ((bit)ScalerGetBit(PFE_72_DDC3_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            return ((bit)ScalerGetBit(PFE_7B_DDC4_EDID_IRQ, _BIT2));
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            return ((bit)ScalerGetBit(PFE_84_DDC5_EDID_IRQ, _BIT2));
#endif

        default:
            return _FALSE;
    }
}
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DDC Channel Segment Enable Switch
// Input Value  : bSelect --> _ON: force nack
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuDdcSetSegmentSwitch(EnumInputPort enumInputPort, bit bSelect)
{
    if(bSelect == _ON)
    {
        switch(enumInputPort)
        {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            case _A0_INPUT_PORT:
                // A0 DDC force Nack
                ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT2 | _BIT1), _BIT2);
                break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            case _D0_INPUT_PORT:
                ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT2 | _BIT1), _BIT2);
                break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            case _D1_INPUT_PORT:
                ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT2 | _BIT1), _BIT2);
                break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            case _D2_INPUT_PORT:
                ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT2 | _BIT1), _BIT2);
                break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            case _D3_INPUT_PORT:
                ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT2 | _BIT1), _BIT2);
                break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            case _D4_INPUT_PORT:
                ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT2 | _BIT1), _BIT2);
                break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            case _D5_INPUT_PORT:
                ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT2 | _BIT1), _BIT2);
                break;
#endif
            default:
                break;
        }
    }
    else
    {
        switch(enumInputPort)
        {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            case _A0_INPUT_PORT:
                // A0 DDC force Nack
                ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);
                break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            case _D0_INPUT_PORT:
                ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);
                break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            case _D1_INPUT_PORT:
                ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);
                break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            case _D2_INPUT_PORT:
                ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);
                break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            case _D3_INPUT_PORT:
                ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);
                break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            case _D4_INPUT_PORT:
                ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);
                break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            case _D5_INPUT_PORT:
                ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT2 | _BIT1), 0x00);
                break;
#endif
            default:
                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Force nack DDC channel
// Input Value  : bSelect --> _ON: force nack
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuDdcSetForceNack(EnumInputPort enumInputPort, bit bSelect)
{
    if(bSelect == _ON)
    {
        switch(enumInputPort)
        {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            case _A0_INPUT_PORT:
                // A0 DDC force Nack
                ScalerSetBit(PFF_E7_VGA_EDID_IRQ, ~_BIT5, _BIT5);
                break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            case _D0_INPUT_PORT:
                // DDC0 force nack
                ScalerSetBit(PFF_E4_DDC0_EDID_IRQ, ~_BIT5, _BIT5);
                break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            case _D1_INPUT_PORT:
                // DDC1 force nack
                ScalerSetBit(PFF_E5_DDC1_EDID_IRQ, ~_BIT5, _BIT5);
                break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            case _D2_INPUT_PORT:
                // DDC2 force nack
                ScalerSetBit(PFE_69_DDC2_EDID_IRQ, ~_BIT5, _BIT5);
                break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            case _D3_INPUT_PORT:
                // DDC3 force nack
                ScalerSetBit(PFE_72_DDC3_EDID_IRQ, ~_BIT5, _BIT5);
                break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            case _D4_INPUT_PORT:
                // DDC4 force nack
                ScalerSetBit(PFE_7B_DDC4_EDID_IRQ, ~_BIT5, _BIT5);
                break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            case _D5_INPUT_PORT:
                // DDC5 force nack
                ScalerSetBit(PFE_84_DDC5_EDID_IRQ, ~_BIT5, _BIT5);
                break;
#endif
            default:
                break;
        }
    }
    else
    {
        switch(enumInputPort)
        {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            case _A0_INPUT_PORT:

                // A0 DDC nack off
                ScalerSetBit(PFF_E7_VGA_EDID_IRQ, ~_BIT5, 0x00);
                break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            case _D0_INPUT_PORT:
                // DDC0 nack off
                ScalerSetBit(PFF_E4_DDC0_EDID_IRQ, ~_BIT5, 0x00);
                break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            case _D1_INPUT_PORT:
                // DDC1 nack off
                ScalerSetBit(PFF_E5_DDC1_EDID_IRQ, ~_BIT5, 0x00);
                break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            case _D2_INPUT_PORT:
                // DDC2 nack off
                ScalerSetBit(PFE_69_DDC2_EDID_IRQ, ~_BIT5, 0x00);
                break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            case _D3_INPUT_PORT:
                // DDC3 nack off
                ScalerSetBit(PFE_72_DDC3_EDID_IRQ, ~_BIT5, 0x00);
                break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            case _D4_INPUT_PORT:
                // DDC4 nack off
                ScalerSetBit(PFE_7B_DDC4_EDID_IRQ, ~_BIT5, 0x00);
                break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            case _D5_INPUT_PORT:
                // DDC5 nack off
                ScalerSetBit(PFE_84_DDC5_EDID_IRQ, ~_BIT5, 0x00);
                break;
#endif
            default:

                break;
        }
    }
}

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Force nack DDC channel
// Input Value  : enumInputPort
// Output Value : _TRUE --> Force Nack State
//--------------------------------------------------
bit ScalerMcuDdcGetForceNackStatus(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            if(ScalerGetBit(PFF_E7_VGA_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
            break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            // DDC0 force nack
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
            if(ScalerGetBit(PFF_E4_DDC0_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
            if(ScalerGetBit(PFF_E5_DDC1_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
            if(ScalerGetBit(PFE_69_DDC2_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
#endif
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            // DDC1 force nack
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
            if(ScalerGetBit(PFF_E4_DDC0_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
            if(ScalerGetBit(PFF_E5_DDC1_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
            if(ScalerGetBit(PFE_69_DDC2_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
#endif
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            // DDC2 force nack
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
            if(ScalerGetBit(PFF_E4_DDC0_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
            if(ScalerGetBit(PFF_E5_DDC1_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
            if(ScalerGetBit(PFE_69_DDC2_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
#endif
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            if(ScalerGetBit(PFE_72_DDC3_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            if(ScalerGetBit(PFE_7B_DDC4_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            if(ScalerGetBit(PFE_84_DDC5_EDID_IRQ, _BIT5) == _BIT5)
            {
                return _TRUE;
            }
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}
#endif // End of #if(_HDMI_MULTI_EDID_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Irom access
// Input Value  : usStartAddr, usLength, pucArrat
// Output Value : None
//--------------------------------------------------
void ScalerMcuIromAccess(DWORD ulStartAddr, WORD usLength, BYTE *pucArray)
{
    volatile BYTE *pucRomArray = (volatile BYTE *)(ulStartAddr);
    WORD usIndex = 0;

    // Read out irom data
    for(usIndex = 0; usIndex < usLength; usIndex++)
    {
        pucArray[usIndex] = pucRomArray[usIndex];
    }
}

//--------------------------------------------------
// Description  : Config DDC Port DDCRAM Block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcramConfig(void)
{
    // disable DID Function
    MCU_FEB9_DDC_DID_CTRL = 0x00;

#if(_HW_DDC0_EXIST == _ON)
    // DDC0 DDCRAM Select
    ScalerSetBit(PFE_BA_DDC0_DDCRAM_SEL, ~(_BIT4 | _BIT3 | _BIT2), (ScalerMcuDdcramBlockSel(_EMBEDDED_DDCRAM_DDC0_ADDRESS) << 2));
#endif

#if(_HW_DDC1_EXIST == _ON)
    // DDC1 DDCRAM Select
    ScalerSetBit(PFE_C5_DDC1_DDCRAM_SEL, ~(_BIT4 | _BIT3 | _BIT2), (ScalerMcuDdcramBlockSel(_EMBEDDED_DDCRAM_DDC1_ADDRESS) << 2));
#endif

#if(_HW_DDC2_EXIST == _ON)
    // DDC2 DDCRAM Select
    ScalerSetBit(PFE_D3_DDC2_DDCRAM_SEL, ~(_BIT4 | _BIT3 | _BIT2), (ScalerMcuDdcramBlockSel(_EMBEDDED_DDCRAM_DDC2_ADDRESS) << 2));
#endif

#if(_HW_DDC3_EXIST == _ON)
    // DDC3 DDCRAM Select
    ScalerSetBit(PFE_DE_DDC3_DDCRAM_SEL, ~(_BIT4 | _BIT3 | _BIT2), (ScalerMcuDdcramBlockSel(_EMBEDDED_DDCRAM_DDC3_ADDRESS) << 2));
#endif

#if(_HW_DDC4_EXIST == _ON)
    // DDC4 DDCRAM Select
    ScalerSetBit(PFE_E9_DDC4_DDCRAM_SEL, ~(_BIT4 | _BIT3 | _BIT2), (ScalerMcuDdcramBlockSel(_EMBEDDED_DDCRAM_DDC4_ADDRESS) << 2));
#endif
}

#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : 4byte Flash mode Set 0xFF01
// Input Value  : ucHighBank --> Flash High Bank index
// Output Value : None
//--------------------------------------------------
void ScalerMcuFlashHighByteSet(BYTE ucHighByte)
{
    if(GET_INTERRUPT_GLOBAL_ENABLE_STATUS() == _ENABLE)
    {
        // Disable All interrupt
        SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_DISABLE);

        // Set 0xFF01
        MCU_FF01_FLASH_PROG_ISP = ucHighByte;

        DELAY_5US();

        // Enable All interrupt
        SET_INTERRUPT_GLOBAL_ENABLE_STATUS(_ENABLE);
    }
    else
    {
        // Set 0xFF01
        MCU_FF01_FLASH_PROG_ISP = ucHighByte;

        DELAY_5US();
    }
}
#endif
//--------------------------------------------------
// Description  : FW mode Flash Data CRC Calculate
// Input Value  : ulStartAddr --> Flash Start Address
//                ulEndAddr --> Flash End Address
//                pucCRCResult --> CRC calculate Result
// Output Value : CRC Calculate Result
//--------------------------------------------------
bit ScalerMcuFlashCRCCal(DWORD ulStartAddr, DWORD ulEndAddr, BYTE *pucCRCResult)
{
    DWORD ulTimeOut = 200;

    // Set Flash Data Start & End Address
#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        ScalerMcuFlashHighByteSet(HIBYTE(HIWORD(ulStartAddr)));
    }
#endif
    MCU_FF64_FLASH_PROG_ISP0 = LOBYTE(HIWORD(ulStartAddr));
    MCU_FF65_FLASH_PROG_ISP1 = HIBYTE(LOWORD(ulStartAddr));
    MCU_FF66_FLASH_PROG_ISP2 = LOBYTE(LOWORD(ulStartAddr));
#if(_FLASH_4BYTE_MODE_FUNCTION_SUPPORT == _ON)
    if(GET_POL_FLASH_ADDR_MODE() == _TRUE)
    {
        MCU_FFA3_CRC_END_ADDR = HIBYTE(HIWORD(ulEndAddr));
    }
#endif
    MCU_FF72_CRC_END_ADDR0 = LOBYTE(HIWORD(ulEndAddr));
    MCU_FF73_CRC_END_ADDR1 = HIBYTE(LOWORD(ulEndAddr));
    MCU_FF74_CRC_END_ADDR2 = LOBYTE(LOWORD(ulEndAddr));

    // Start Calculate
    MCU_FF6F_PROGRAM_INSTRUCTION |= _BIT2;

    // Set timeout 200/bank
    if(((ulEndAddr - ulStartAddr + 1) % _FALSH_BANK_SIZE) == 0)
    {
        ulTimeOut = ((ulEndAddr - ulStartAddr + 1) / _FALSH_BANK_SIZE) * 200;
    }
    else
    {
        ulTimeOut = (((ulEndAddr - ulStartAddr + 1) / _FALSH_BANK_SIZE) + 1) * 200;
    }

    // Polling CRC_Start & TimeOut
    while(((MCU_FF6F_PROGRAM_INSTRUCTION & _BIT2) == _BIT2) && (--ulTimeOut > 0))
    {
        DELAY_5US();
    }

    if(((MCU_FF6F_PROGRAM_INSTRUCTION & _BIT1) == _BIT1) && ((MCU_FF6F_PROGRAM_INSTRUCTION & _BIT2) == 0))
    {
        *pucCRCResult = MCU_FF75_CRC_RESULT;
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : MCU Initial INT Priority Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIntPriorityInit(void)
{
    EnumIRQnType enumIRQnTypeIdx = 0;

    // Set Interrupt Group Priority
    ScalerCpuHalSetPrioritygrouping(_NVIC_PRIORITYGROUP_4);

    while(enumIRQnTypeIdx < 32)
    {
        EnumCpuIrqPriority enumCpuIrqPriority = GET_INT_PRIORITY(enumIRQnTypeIdx);

        ScalerCpuHalSetPriority(enumIRQnTypeIdx, enumCpuIrqPriority);

        if(enumCpuIrqPriority == _CPU_IRQ_DISABLE)
        {
            ScalerCpuHalDisableIRQ(enumIRQnTypeIdx);
        }
        else
        {
            ScalerCpuHalEnableIRQ(enumIRQnTypeIdx);
        }

        enumIRQnTypeIdx++;
    }
}

//--------------------------------------------------
// Description  : Set 1us busy delay Cnt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcu1usDelayCalc(EnumClkSel enumClock)
{
    if(enumClock == _M2PLL_CLK)
    {
        g_ucMcu32Delay1usCnt = _M2PLL_BUSY_LOOP_1US_CNT;
    }
    else if(enumClock == _IOSC_CLK)
    {
        g_ucMcu32Delay1usCnt = _IOSC_BUSY_LOOP_1US_CNT;
    }
    else // For Xtal
    {
        g_ucMcu32Delay1usCnt = _XTAL_BUSY_LOOP_1US_CNT;
    }
}

//--------------------------------------------------
// Description  : Get 1us busy delay Cnt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerMcuGet1usDelayCnt(void)
{
    return g_ucMcu32Delay1usCnt;
}



#ifdef __GNUC__
#pragma GCC push_options
#pragma GCC optimize("Os")
#endif
//--------------------------------------------------
// Description  : 5us busy delay.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDelayXus(DWORD ulMicroSecond)
{
    volatile DWORD ulCnt = (ulMicroSecond * g_ucMcu32Delay1usCnt) + (ulMicroSecond >> 1);
    while(ulCnt--){};
}
#ifdef __GNUC__
#pragma GCC pop_options
#endif

#ifdef __GNUC__
#pragma GCC push_options
#pragma GCC optimize("Os")
#endif
//--------------------------------------------------
// Description  : 5us busy delay.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDelayDot2usPN(void)
{
    volatile DWORD ulcnt = _M2PLL_BUSY_LOOP_DOT2US_CNT;
    while(--ulcnt){};
}
#ifdef __GNUC__
#pragma GCC pop_options
#endif

//--------------------------------------------------
// Description  : ISP Channel Setting
// Input Value  : ISPChannel -> VGA_DDC: _BIT0; DDC0: _BIT1; DDC1: _BIT2;... DDC5: _BIT6;
//                _NO_DDC: _BIT7; VGA_DDC2: _BIT8
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuSetISPChannel(WORD usISPChannel)
{
    // VGA_DDC
    ScalerMcuDdcISPChannelCtrl(_VGA_DDC, (bit)(usISPChannel & _BIT0));
    // DDC0
    ScalerMcuDdcISPChannelCtrl(_DDC0, (bit)(usISPChannel & _BIT1));
    // DDC1
    ScalerMcuDdcISPChannelCtrl(_DDC1, (bit)(usISPChannel & _BIT2));
    // DDC2
    ScalerMcuDdcISPChannelCtrl(_DDC2, (bit)(usISPChannel & _BIT3));
    // DDC3
    ScalerMcuDdcISPChannelCtrl(_DDC3, (bit)(usISPChannel & _BIT4));
    // DDC4
    ScalerMcuDdcISPChannelCtrl(_DDC4, (bit)(usISPChannel & _BIT5));
    // DDC5
    ScalerMcuDdcISPChannelCtrl(_DDC5, (bit)(usISPChannel & _BIT6));
}

//--------------------------------------------------
// Description  : ISP Channel Setting
// Input Value  : ucDdcChannel --> VGA_DDC...VGA_DDC2
//                bEnable --> _ENABLE: enable DDC ISP function, no protect
//                            _DISABLE: disable DDC ISP function, protect
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuDdcISPChannelCtrl(BYTE ucDdcChannel, bit bEnable)
{
    switch(ucDdcChannel)
    {
#if(_HW_ISP_DDC_EXIST == _ON)
        case _VGA_DDC:
            // VGA_DDC ISP
            ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT3 | _BIT1), ((bEnable == _TRUE) ? _BIT3 : 0));
            break;
#endif

#if(_HW_DDC0_EXIST == _ON)
        case _DDC0:
            // DDC0 ISP
            ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT3 | _BIT1), ((bEnable == _TRUE) ? _BIT3 : 0));
            break;
#endif

#if(_HW_DDC1_EXIST == _ON)
        case _DDC1:
            // DDC1 ISP
            ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT3 | _BIT1), ((bEnable == _TRUE) ? _BIT3 : 0));
            break;
#endif

#if(_HW_DDC2_EXIST == _ON)
        case _DDC2:
            // DDC2 ISP
            ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT3 | _BIT1), ((bEnable == _TRUE) ? _BIT3 : 0));
            break;
#endif

#if(_HW_DDC3_EXIST == _ON)
        case _DDC3:
            // DDC3 ISP
            ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT3 | _BIT1), ((bEnable == _TRUE) ? _BIT3 : 0));
            break;
#endif

#if(_HW_DDC4_EXIST == _ON)
        case _DDC4:
            // DDC4 ISP
            ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT3 | _BIT1), ((bEnable == _TRUE) ? _BIT3 : 0));
            break;
#endif

#if(_HW_DDC5_EXIST == _ON)
        case _DDC5:
            // DDC5 ISP
            ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT3 | _BIT1), ((bEnable == _TRUE) ? _BIT3 : 0));
            break;
#endif

        case _NO_DDC:
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Modify ISP addr
// Input Value  : _ENABLE or _DISABLE
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuSetISPSlaveAddr(BYTE ucISPStatus)
{
    if(ucISPStatus == _ENABLE)
    {
        // Set ISP Slave Address to Right Value
        MCU_FFEC_ISP_SLAVE_ADDRESS = 0x94;
    }
    else
    {
        // Set ISP Slave Address to any Wrong Value,
        MCU_FFEC_ISP_SLAVE_ADDRESS = 0xFC;
    }
}

//--------------------------------------------------
// Description  : Set Interrupt Global Enable Status
// Input Value  : _ENABLE or _DISABLE
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuSetInterruptGlobalEnableStatus(bit bEnable)
{
    SET_INTERRUPT_GLOBAL_ENABLE_STATUS(bEnable);
}

//--------------------------------------------------
// Description  : Get ISP Channel Channel Status
// Input Value  :
// Output Value :
//--------------------------------------------------
WORD ScalerMcuGetIspChannelEnableStatus(void)
{
    return _ISP_CHANNEL_EN_FW_UPDATE;
}

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Data Exchange Send Data
// Input Value  : BYTE ucCmdTypeGroup, BYTE ucCmdType, BYTE ucDataLength, BYTE *pucWriteArray
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMcuDataExchangeSendData(BYTE ucCmdTypeGroup, BYTE ucCmdType, BYTE ucDataLength, BYTE *pucWriteArray)
{
    BYTE pucTempData[26] = {0};
    BYTE ucReadWaitLoopCnt = 5;
    BYTE ucLoopCnt = 0;
    BYTE ucLength = 0;
    BYTE ucLengthSend = 0;
    BYTE ucIndex = 0;

    if(((ucCmdTypeGroup << 7) | ucCmdType) == g_usMcuSyncDataType)
    {
        g_bMcuSyncDataTag += 1;
        g_usMcuSyncDataType = ((g_bMcuSyncDataTag << 15) | (ucCmdTypeGroup << 7) | ucCmdType);
    }
    else
    {
        g_usMcuSyncDataType = ((ucCmdTypeGroup << 7) | ucCmdType);
    }

    // Data Type Group -- 0
    pucTempData[0] = (g_bMcuSyncDataTag << 7) | ucCmdTypeGroup;

    // CMD Type -- 1
    pucTempData[1] = ucCmdType;

    // Calculate the data needs to be transmitted Loop Cnt
    ucLoopCnt = ucDataLength / 24 + ((ucDataLength % 24 == 0) ? 0 : 1);

    if(ucDataLength == 0)
    {
        ucLoopCnt = 1;
    }

    for(ucIndex = 0; ucIndex < ucLoopCnt; ucIndex++)
    {
        if((ucLoopCnt - ucIndex) != 1)
        {
            ucLength = 24;
            ucDataLength = ucDataLength - 24;
        }
        else
        {
            ucLength = ucDataLength;
        }

        // Data Length -- 2
        pucTempData[2] = ucLength;

        // CMD Data
        memcpy(&pucTempData[3], &pucWriteArray[ucIndex * 24], ucLength);

        // LengthSend = CMD Type + Data Length + Data
        ucLengthSend = ucLength + 2;

        // Tx I2C Write
#if(_HW_IIC_SUPPORT == _ON)
        ScalerMcuHwIICWrite(_TWO_CHIP_DATA_EXCHANGE_RX_SLAVE_ADDR, 1, pucTempData[0], ucLengthSend, &pucTempData[1], _TWO_CHIP_DATA_EXCHANGE_TX_IIC_PIN);

        DELAY_XUS(800);

        do
        {
            if(ScalerMcuHwIICRead(_TWO_CHIP_DATA_EXCHANGE_RX_SLAVE_ADDR, 0, 0x00, 2, pData, _TWO_CHIP_DATA_EXCHANGE_TX_IIC_PIN) == _TRUE)
            {
                if((pData[0] == (pucTempData[0] | 0x70)) && (pData[1] == (pucTempData[1] | 0x80)))
                {
                    break;
                }
            }
            DELAY_XUS(50);

            ucReadWaitLoopCnt--;
        }
        while(ucReadWaitLoopCnt != 0);
#endif

        if(ucReadWaitLoopCnt == 0)
        {
            DebugMessageScaler("Mcu Data Exchange Transmit fail", 0);
            return _FALSE;
        }
    }

    DebugMessageScaler("Mcu Data Exchange Transmit pass", 1);
    return _TRUE;
}

//--------------------------------------------------
// Description  : Data Exchange Check Send Data Done
// Input Value  : BYTE ucCmdTypeGroup, BYTE ucCmdType, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucPollingInterval
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerMcuDataCheckSendDataDone(EnumDataExchangeTypeGroup enumDataExchangeTypeGroup, BYTE ucCmdType, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucPollingInterval)
{
    BYTE ucPollingCnt = 0;

    do
    {
        if(ScalerMcuDataExchangeSendData((BYTE)enumDataExchangeTypeGroup, ucCmdType, ucDataLength, pucWriteArray) == _TRUE)
        {
            DebugMessageSystem("Data Exchange Check Send Data Pass", 1);
            return _TRUE;
        }

        ScalerTimerDelayXms(ucPollingInterval);

        ucPollingCnt++;
    }
    while(ucPollingCnt < 20);

    DebugMessageScaler("Data Exchange Check Send Data Fail ", 0);
    return _FALSE;
}
#endif
