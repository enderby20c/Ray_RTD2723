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
// ID Code      : RL6952_BGA2L_PCB_LVDS_EXAMPLE_PINSHARE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//////////////////////////////
// RL6952 Series Pin Share //
//////////////////////////////

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1000
// MCU Ctrl : 0xFE00 at _2L_900PIN_PIN_J4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_J4                       (_2L_900PIN_PIN_J4_NC)

typedef enum
{
    _2L_900PIN_PIN_J4_GPI = 0x00,
    _2L_900PIN_PIN_J4_GPO_PP = 0x01,
    _2L_900PIN_PIN_J4_GPO_OD = 0x02,
    _2L_900PIN_PIN_J4_DISP_FRAME_START_IN = 0x03,
    _2L_900PIN_PIN_J4_DISP_FRAME_START_OUT = 0x04,
    _2L_900PIN_PIN_J4_EXT_UART_TX_0_5 = 0x05,
    _2L_900PIN_PIN_J4_EXT_UART_TX_1_5 = 0x06,
    _2L_900PIN_PIN_J4_EXT_UART_TX_2_5 = 0x07,
    _2L_900PIN_PIN_J4_USB_SPI_CLK_0_4 = 0x08,
    _2L_900PIN_PIN_J4_USB_SPI_CLK_1_4 = 0x09,
    _2L_900PIN_PIN_J4_USB_SPI_CLK_2_4 = 0x0A,
    _2L_900PIN_PIN_J4_TEST12B_OUT3 = 0x0B,
    _2L_900PIN_PIN_J4_TEST12B_OUT4 = 0x0C,
    _2L_900PIN_PIN_J4_TEST12B_OUT5 = 0x0D,
    _2L_900PIN_PIN_J4_TEST12B_OUT6 = 0x0E,
    _2L_900PIN_PIN_J4_TEST12B_OUT7 = 0x0F,
    _2L_900PIN_PIN_J4_TEST12B_OUT8 = 0x10,
    _2L_900PIN_PIN_J4_TEST12B_OUT9 = 0x11,
    _2L_900PIN_PIN_J4_TEST12B_OUT10 = 0x12,
    _2L_900PIN_PIN_J4_TEST12B_OUT11 = 0x13,
    _2L_900PIN_PIN_J4_NC = _2L_900PIN_PIN_J4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_J4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1001
// MCU Ctrl : 0xFE01 at _2L_900PIN_PIN_H5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_H5                       (_2L_900PIN_PIN_H5_NC)

typedef enum
{
    _2L_900PIN_PIN_H5_GPI = 0x00,
    _2L_900PIN_PIN_H5_GPO_PP = 0x01,
    _2L_900PIN_PIN_H5_GPO_OD = 0x02,
    _2L_900PIN_PIN_H5_INT0_0 = 0x03,
    _2L_900PIN_PIN_H5_INT1_0 = 0x04,
    _2L_900PIN_PIN_H5_EXT_UART_RX_0_5 = 0x05,
    _2L_900PIN_PIN_H5_EXT_UART_RX_1_5 = 0x06,
    _2L_900PIN_PIN_H5_EXT_UART_RX_2_5 = 0x07,
    _2L_900PIN_PIN_H5_PWM1_PP = 0x08,
    _2L_900PIN_PIN_H5_PWM1_OD = 0x09,
    _2L_900PIN_PIN_H5_PWM1_DIMMING_PP = 0x0A,
    _2L_900PIN_PIN_H5_PWM1_DIMMING = 0x0B,
    _2L_900PIN_PIN_H5_USB_SPI_CLK_0_5 = 0x0C,
    _2L_900PIN_PIN_H5_USB_SPI_CLK_1_5 = 0x0D,
    _2L_900PIN_PIN_H5_USB_SPI_CLK_2_5 = 0x0E,
    _2L_900PIN_PIN_H5_TEST12B_OUT3 = 0x0F,
    _2L_900PIN_PIN_H5_TEST12B_OUT4 = 0x10,
    _2L_900PIN_PIN_H5_TEST12B_OUT5 = 0x11,
    _2L_900PIN_PIN_H5_TEST12B_OUT6 = 0x12,
    _2L_900PIN_PIN_H5_TEST12B_OUT7 = 0x13,
    _2L_900PIN_PIN_H5_TEST12B_OUT8 = 0x14,
    _2L_900PIN_PIN_H5_TEST12B_OUT9 = 0x15,
    _2L_900PIN_PIN_H5_TEST12B_OUT10 = 0x16,
    _2L_900PIN_PIN_H5_TEST12B_OUT11 = 0x17,
    _2L_900PIN_PIN_H5_NC = _2L_900PIN_PIN_H5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_H5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1002
// MCU Ctrl : 0xFE02 at _2L_900PIN_PIN_J5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_J5                       (_2L_900PIN_PIN_J5_NC)

typedef enum
{
    _2L_900PIN_PIN_J5_GPI = 0x00,
    _2L_900PIN_PIN_J5_GPO_PP = 0x01,
    _2L_900PIN_PIN_J5_GPO_OD = 0x02,
    _2L_900PIN_PIN_J5_PWM_IN_0_0 = 0x03,
    _2L_900PIN_PIN_J5_PWM1_PP = 0x04,
    _2L_900PIN_PIN_J5_PWM1_OD = 0x05,
    _2L_900PIN_PIN_J5_PWM1_DIMMING_PP = 0x06,
    _2L_900PIN_PIN_J5_PWM1_DIMMING = 0x07,
    _2L_900PIN_PIN_J5_EXT_UART_TX_0_4 = 0x08,
    _2L_900PIN_PIN_J5_EXT_UART_TX_1_4 = 0x09,
    _2L_900PIN_PIN_J5_EXT_UART_TX_2_4 = 0x0A,
    _2L_900PIN_PIN_J5_TCON13 = 0x0B,
    _2L_900PIN_PIN_J5_TEST12B_OUT0 = 0x0C,
    _2L_900PIN_PIN_J5_TEST12B_OUT1 = 0x0D,
    _2L_900PIN_PIN_J5_TEST12B_OUT2 = 0x0E,
    _2L_900PIN_PIN_J5_TEST12B_OUT3 = 0x0F,
    _2L_900PIN_PIN_J5_TEST12B_OUT4 = 0x10,
    _2L_900PIN_PIN_J5_TEST12B_OUT5 = 0x11,
    _2L_900PIN_PIN_J5_TEST12B_OUT6 = 0x12,
    _2L_900PIN_PIN_J5_TEST12B_OUT7 = 0x13,
    _2L_900PIN_PIN_J5_TEST12B_OUT8 = 0x14,
    _2L_900PIN_PIN_J5_TEST12B_OUT9 = 0x15,
    _2L_900PIN_PIN_J5_TEST12B_OUT10 = 0x16,
    _2L_900PIN_PIN_J5_TEST12B_OUT11 = 0x17,
    _2L_900PIN_PIN_J5_NC = _2L_900PIN_PIN_J5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_J5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1003
// MCU Ctrl : 0xFE03 at _2L_900PIN_PIN_H4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_H4                       (_2L_900PIN_PIN_H4_NC)

typedef enum
{
    _2L_900PIN_PIN_H4_GPI = 0x00,
    _2L_900PIN_PIN_H4_GPO_PP = 0x01,
    _2L_900PIN_PIN_H4_GPO_OD = 0x02,
    _2L_900PIN_PIN_H4_EXT_UART_RX_0_4 = 0x03,
    _2L_900PIN_PIN_H4_EXT_UART_RX_1_4 = 0x04,
    _2L_900PIN_PIN_H4_EXT_UART_RX_2_4 = 0x05,
    _2L_900PIN_PIN_H4_PWM2_PP = 0x06,
    _2L_900PIN_PIN_H4_PWM2_OD = 0x07,
    _2L_900PIN_PIN_H4_PWM2_DIMMING_PP = 0x08,
    _2L_900PIN_PIN_H4_PWM2_DIMMING = 0x09,
    _2L_900PIN_PIN_H4_TCON8 = 0x0A,
    _2L_900PIN_PIN_H4_TEST12B_OUT0 = 0x0B,
    _2L_900PIN_PIN_H4_TEST12B_OUT1 = 0x0C,
    _2L_900PIN_PIN_H4_TEST12B_OUT2 = 0x0D,
    _2L_900PIN_PIN_H4_TEST12B_OUT3 = 0x0E,
    _2L_900PIN_PIN_H4_TEST12B_OUT4 = 0x0F,
    _2L_900PIN_PIN_H4_TEST12B_OUT5 = 0x10,
    _2L_900PIN_PIN_H4_TEST12B_OUT6 = 0x11,
    _2L_900PIN_PIN_H4_TEST12B_OUT7 = 0x12,
    _2L_900PIN_PIN_H4_TEST12B_OUT8 = 0x13,
    _2L_900PIN_PIN_H4_TEST12B_OUT9 = 0x14,
    _2L_900PIN_PIN_H4_TEST12B_OUT10 = 0x15,
    _2L_900PIN_PIN_H4_TEST12B_OUT11 = 0x16,
    _2L_900PIN_PIN_H4_NC = _2L_900PIN_PIN_H4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_H4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1004
// MCU Ctrl : 0xFE04 at _2L_900PIN_PIN_W5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_W5                       (_2L_900PIN_PIN_W5_NC)

typedef enum
{
    _2L_900PIN_PIN_W5_GPI = 0x00,
    _2L_900PIN_PIN_W5_GPO_PP = 0x01,
    _2L_900PIN_PIN_W5_GPO_OD = 0x02,
    _2L_900PIN_PIN_W5_DPTX_HPD_0_ORG = 0x03,
    _2L_900PIN_PIN_W5_CLKO = 0x04,
    _2L_900PIN_PIN_W5_TEST12B_OUT0 = 0x05,
    _2L_900PIN_PIN_W5_TEST12B_OUT1 = 0x06,
    _2L_900PIN_PIN_W5_TEST12B_OUT2 = 0x07,
    _2L_900PIN_PIN_W5_TEST12B_OUT3 = 0x08,
    _2L_900PIN_PIN_W5_TEST12B_OUT4 = 0x09,
    _2L_900PIN_PIN_W5_TEST12B_OUT5 = 0x0A,
    _2L_900PIN_PIN_W5_TEST12B_OUT6 = 0x0B,
    _2L_900PIN_PIN_W5_TEST12B_OUT7 = 0x0C,
    _2L_900PIN_PIN_W5_TEST12B_OUT8 = 0x0D,
    _2L_900PIN_PIN_W5_TEST12B_OUT9 = 0x0E,
    _2L_900PIN_PIN_W5_TEST12B_OUT10 = 0x0F,
    _2L_900PIN_PIN_W5_TEST12B_OUT11 = 0x10,
    _2L_900PIN_PIN_W5_NC = _2L_900PIN_PIN_W5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_W5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1005
// MCU Ctrl : 0xFE05 at _2L_900PIN_PIN_AB4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AB4                      (_2L_900PIN_PIN_AB4_NC)

typedef enum
{
    _2L_900PIN_PIN_AB4_GPI = 0x00,
    _2L_900PIN_PIN_AB4_GPO_PP = 0x01,
    _2L_900PIN_PIN_AB4_GPO_OD = 0x02,
    _2L_900PIN_PIN_AB4_DPRX_AUX_P_0 = 0x03,
    _2L_900PIN_PIN_AB4_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AB4_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AB4_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AB4_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AB4_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AB4_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AB4_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AB4_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AB4_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AB4_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AB4_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AB4_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AB4_NC = _2L_900PIN_PIN_AB4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AB4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1006
// MCU Ctrl : 0xFE06 at _2L_900PIN_PIN_AB5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AB5                      (_2L_900PIN_PIN_AB5_NC)

typedef enum
{
    _2L_900PIN_PIN_AB5_GPI = 0x00,
    _2L_900PIN_PIN_AB5_GPO_PP = 0x01,
    _2L_900PIN_PIN_AB5_GPO_OD = 0x02,
    _2L_900PIN_PIN_AB5_DPRX_AUX_N_0 = 0x03,
    _2L_900PIN_PIN_AB5_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AB5_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AB5_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AB5_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AB5_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AB5_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AB5_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AB5_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AB5_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AB5_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AB5_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AB5_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AB5_NC = _2L_900PIN_PIN_AB5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AB5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1007
// MCU Ctrl : 0xFE07 at _2L_900PIN_PIN_V5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_V5                       (_2L_900PIN_PIN_V5_NC)

typedef enum
{
    _2L_900PIN_PIN_V5_GPI = 0x00,
    _2L_900PIN_PIN_V5_GPO_PP = 0x01,
    _2L_900PIN_PIN_V5_GPO_OD = 0x02,
    _2L_900PIN_PIN_V5_PWM_OUT_0_0 = 0x03,
    _2L_900PIN_PIN_V5_PWM3_PP = 0x04,
    _2L_900PIN_PIN_V5_PWM3_OD = 0x05,
    _2L_900PIN_PIN_V5_PWM3_DIMMING_PP = 0x06,
    _2L_900PIN_PIN_V5_PWM3_DIMMING = 0x07,
    _2L_900PIN_PIN_V5_TCON6 = 0x08,
    _2L_900PIN_PIN_V5_TEST12B_OUT0 = 0x09,
    _2L_900PIN_PIN_V5_TEST12B_OUT1 = 0x0A,
    _2L_900PIN_PIN_V5_TEST12B_OUT2 = 0x0B,
    _2L_900PIN_PIN_V5_TEST12B_OUT3 = 0x0C,
    _2L_900PIN_PIN_V5_TEST12B_OUT4 = 0x0D,
    _2L_900PIN_PIN_V5_TEST12B_OUT5 = 0x0E,
    _2L_900PIN_PIN_V5_TEST12B_OUT6 = 0x0F,
    _2L_900PIN_PIN_V5_TEST12B_OUT7 = 0x10,
    _2L_900PIN_PIN_V5_TEST12B_OUT8 = 0x11,
    _2L_900PIN_PIN_V5_TEST12B_OUT9 = 0x12,
    _2L_900PIN_PIN_V5_TEST12B_OUT10 = 0x13,
    _2L_900PIN_PIN_V5_TEST12B_OUT11 = 0x14,
    _2L_900PIN_PIN_V5_NC = _2L_900PIN_PIN_V5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_V5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1008
// MCU Ctrl : 0xFE08 at _2L_900PIN_PIN_AD4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AD4                      (_2L_900PIN_PIN_AD4_NC)

typedef enum
{
    _2L_900PIN_PIN_AD4_GPI = 0x00,
    _2L_900PIN_PIN_AD4_GPO_PP = 0x01,
    _2L_900PIN_PIN_AD4_GPO_OD = 0x02,
    _2L_900PIN_PIN_AD4_10B_ADC_3 = 0x03,
    _2L_900PIN_PIN_AD4_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AD4_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AD4_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AD4_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AD4_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AD4_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AD4_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AD4_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AD4_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AD4_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AD4_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AD4_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AD4_NC = _2L_900PIN_PIN_AD4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AD4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1009
// MCU Ctrl : 0xFE09 at _2L_900PIN_PIN_AD5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AD5                      (_2L_900PIN_PIN_AD5_NC)

typedef enum
{
    _2L_900PIN_PIN_AD5_GPI = 0x00,
    _2L_900PIN_PIN_AD5_GPO_PP = 0x01,
    _2L_900PIN_PIN_AD5_GPO_OD = 0x02,
    _2L_900PIN_PIN_AD5_10B_ADC_2 = 0x03,
    _2L_900PIN_PIN_AD5_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AD5_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AD5_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AD5_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AD5_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AD5_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AD5_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AD5_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AD5_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AD5_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AD5_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AD5_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AD5_NC = _2L_900PIN_PIN_AD5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AD5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100A
// MCU Ctrl : 0xFE0A at _2L_900PIN_PIN_AE4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AE4                      (_2L_900PIN_PIN_AE4_NC)

typedef enum
{
    _2L_900PIN_PIN_AE4_GPI = 0x00,
    _2L_900PIN_PIN_AE4_GPO_PP = 0x01,
    _2L_900PIN_PIN_AE4_GPO_OD = 0x02,
    _2L_900PIN_PIN_AE4_10B_ADC_1 = 0x03,
    _2L_900PIN_PIN_AE4_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AE4_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AE4_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AE4_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AE4_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AE4_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AE4_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AE4_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AE4_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AE4_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AE4_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AE4_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AE4_NC = _2L_900PIN_PIN_AE4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AE4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100B
// MCU Ctrl : 0xFE0B at _2L_900PIN_PIN_AE5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AE5                      (_2L_900PIN_PIN_AE5_NC)

typedef enum
{
    _2L_900PIN_PIN_AE5_GPI = 0x00,
    _2L_900PIN_PIN_AE5_GPO_PP = 0x01,
    _2L_900PIN_PIN_AE5_GPO_OD = 0x02,
    _2L_900PIN_PIN_AE5_10B_ADC_0 = 0x03,
    _2L_900PIN_PIN_AE5_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AE5_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AE5_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AE5_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AE5_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AE5_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AE5_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AE5_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AE5_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AE5_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AE5_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AE5_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AE5_NC = _2L_900PIN_PIN_AE5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AE5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100C
// MCU Ctrl : 0xFE0C at _2L_900PIN_PIN_AF15_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AF15                     (_2L_900PIN_PIN_AF15_NC)

typedef enum
{
    _2L_900PIN_PIN_AF15_GPI = 0x00,
    _2L_900PIN_PIN_AF15_GPO_PP = 0x01,
    _2L_900PIN_PIN_AF15_GPO_OD = 0x02,
    _2L_900PIN_PIN_AF15_CEC = 0x03,
    _2L_900PIN_PIN_AF15_TCON13 = 0x04,
    _2L_900PIN_PIN_AF15_TEST12B_OUT0 = 0x05,
    _2L_900PIN_PIN_AF15_TEST12B_OUT1 = 0x06,
    _2L_900PIN_PIN_AF15_TEST12B_OUT2 = 0x07,
    _2L_900PIN_PIN_AF15_TEST12B_OUT3 = 0x08,
    _2L_900PIN_PIN_AF15_TEST12B_OUT4 = 0x09,
    _2L_900PIN_PIN_AF15_TEST12B_OUT5 = 0x0A,
    _2L_900PIN_PIN_AF15_TEST12B_OUT6 = 0x0B,
    _2L_900PIN_PIN_AF15_TEST12B_OUT7 = 0x0C,
    _2L_900PIN_PIN_AF15_TEST12B_OUT8 = 0x0D,
    _2L_900PIN_PIN_AF15_TEST12B_OUT9 = 0x0E,
    _2L_900PIN_PIN_AF15_TEST12B_OUT10 = 0x0F,
    _2L_900PIN_PIN_AF15_TEST12B_OUT11 = 0x10,
    _2L_900PIN_PIN_AF15_NC = _2L_900PIN_PIN_AF15_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AF15;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100D
// MCU Ctrl : 0xFE0D at _2L_900PIN_PIN_AG12_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AG12                     (_2L_900PIN_PIN_AG12_NC)

typedef enum
{
    _2L_900PIN_PIN_AG12_GPI = 0x00,
    _2L_900PIN_PIN_AG12_GPO_PP = 0x01,
    _2L_900PIN_PIN_AG12_GPO_OD = 0x02,
    _2L_900PIN_PIN_AG12_DPTX_AUX_N_0 = 0x03,
    _2L_900PIN_PIN_AG12_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AG12_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AG12_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AG12_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AG12_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AG12_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AG12_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AG12_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AG12_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AG12_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AG12_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AG12_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AG12_NC = _2L_900PIN_PIN_AG12_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AG12;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100E
// MCU Ctrl : 0xFE0E at _2L_900PIN_PIN_AF12_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AF12                     (_2L_900PIN_PIN_AF12_NC)

typedef enum
{
    _2L_900PIN_PIN_AF12_GPI = 0x00,
    _2L_900PIN_PIN_AF12_GPO_PP = 0x01,
    _2L_900PIN_PIN_AF12_GPO_OD = 0x02,
    _2L_900PIN_PIN_AF12_DPTX_AUX_P_0 = 0x03,
    _2L_900PIN_PIN_AF12_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AF12_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AF12_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AF12_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AF12_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AF12_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AF12_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AF12_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AF12_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AF12_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AF12_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AF12_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AF12_NC = _2L_900PIN_PIN_AF12_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AF12;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x100F
// MCU Ctrl : 0xFE0F at _2L_900PIN_PIN_AF16_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AF16                     (_2L_900PIN_PIN_AF16_NC)

typedef enum
{
    _2L_900PIN_PIN_AF16_GPI = 0x00,
    _2L_900PIN_PIN_AF16_GPO_PP = 0x01,
    _2L_900PIN_PIN_AF16_GPO_OD = 0x02,
    _2L_900PIN_PIN_AF16_TEST12B_OUT0 = 0x03,
    _2L_900PIN_PIN_AF16_TEST12B_OUT1 = 0x04,
    _2L_900PIN_PIN_AF16_TEST12B_OUT2 = 0x05,
    _2L_900PIN_PIN_AF16_TEST12B_OUT3 = 0x06,
    _2L_900PIN_PIN_AF16_TEST12B_OUT4 = 0x07,
    _2L_900PIN_PIN_AF16_TEST12B_OUT5 = 0x08,
    _2L_900PIN_PIN_AF16_TEST12B_OUT6 = 0x09,
    _2L_900PIN_PIN_AF16_TEST12B_OUT7 = 0x0A,
    _2L_900PIN_PIN_AF16_TEST12B_OUT8 = 0x0B,
    _2L_900PIN_PIN_AF16_TEST12B_OUT9 = 0x0C,
    _2L_900PIN_PIN_AF16_TEST12B_OUT10 = 0x0D,
    _2L_900PIN_PIN_AF16_TEST12B_OUT11 = 0x0E,
    _2L_900PIN_PIN_AF16_NC = _2L_900PIN_PIN_AF16_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AF16;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1010
// MCU Ctrl : 0xFE10 at _2L_900PIN_PIN_AF17_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AF17                     (_2L_900PIN_PIN_AF17_NC)

typedef enum
{
    _2L_900PIN_PIN_AF17_GPI = 0x00,
    _2L_900PIN_PIN_AF17_GPO_PP = 0x01,
    _2L_900PIN_PIN_AF17_GPO_OD = 0x02,
    _2L_900PIN_PIN_AF17_PWM4_PP = 0x03,
    _2L_900PIN_PIN_AF17_PWM4_OD = 0x04,
    _2L_900PIN_PIN_AF17_PWM4_DIMMING_PP = 0x05,
    _2L_900PIN_PIN_AF17_PWM4_DIMMING = 0x06,
    _2L_900PIN_PIN_AF17_TEST12B_OUT0 = 0x07,
    _2L_900PIN_PIN_AF17_TEST12B_OUT1 = 0x08,
    _2L_900PIN_PIN_AF17_TEST12B_OUT2 = 0x09,
    _2L_900PIN_PIN_AF17_TEST12B_OUT3 = 0x0A,
    _2L_900PIN_PIN_AF17_TEST12B_OUT4 = 0x0B,
    _2L_900PIN_PIN_AF17_TEST12B_OUT5 = 0x0C,
    _2L_900PIN_PIN_AF17_TEST12B_OUT6 = 0x0D,
    _2L_900PIN_PIN_AF17_TEST12B_OUT7 = 0x0E,
    _2L_900PIN_PIN_AF17_TEST12B_OUT8 = 0x0F,
    _2L_900PIN_PIN_AF17_TEST12B_OUT9 = 0x10,
    _2L_900PIN_PIN_AF17_TEST12B_OUT10 = 0x11,
    _2L_900PIN_PIN_AF17_TEST12B_OUT11 = 0x12,
    _2L_900PIN_PIN_AF17_NC = _2L_900PIN_PIN_AF17_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AF17;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1011
// MCU Ctrl : 0xFE11 at _2L_900PIN_PIN_AG16_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AG16                     (_2L_900PIN_PIN_AG16_NC)

typedef enum
{
    _2L_900PIN_PIN_AG16_GPI = 0x00,
    _2L_900PIN_PIN_AG16_GPO_PP = 0x01,
    _2L_900PIN_PIN_AG16_GPO_OD = 0x02,
    _2L_900PIN_PIN_AG16_EEIICSCL = 0x03,
    _2L_900PIN_PIN_AG16_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AG16_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AG16_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AG16_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AG16_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AG16_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AG16_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AG16_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AG16_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AG16_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AG16_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AG16_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AG16_NC = _2L_900PIN_PIN_AG16_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AG16;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1012
// MCU Ctrl : 0xFE12 at _2L_900PIN_PIN_AG17_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AG17                     (_2L_900PIN_PIN_AG17_NC)

typedef enum
{
    _2L_900PIN_PIN_AG17_GPI = 0x00,
    _2L_900PIN_PIN_AG17_GPO_PP = 0x01,
    _2L_900PIN_PIN_AG17_GPO_OD = 0x02,
    _2L_900PIN_PIN_AG17_EEIICSDA = 0x03,
    _2L_900PIN_PIN_AG17_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AG17_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AG17_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AG17_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AG17_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AG17_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AG17_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AG17_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AG17_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AG17_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AG17_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AG17_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AG17_NC = _2L_900PIN_PIN_AG17_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AG17;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1016
// MCU Ctrl : 0xFE16 at _2L_900PIN_PIN_AJ15_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AJ15                     (_2L_900PIN_PIN_AJ15_NC)

typedef enum
{
    _2L_900PIN_PIN_AJ15_GPI = 0x00,
    _2L_900PIN_PIN_AJ15_GPO_PP = 0x01,
    _2L_900PIN_PIN_AJ15_GPO_OD = 0x02,
    _2L_900PIN_PIN_AJ15_A_ADC3_0_0 = 0x03,
    _2L_900PIN_PIN_AJ15_TYPEC_GPIO0_1_PP = 0x04,
    _2L_900PIN_PIN_AJ15_TYPEC_GPIO0_1_OD = 0x05,
    _2L_900PIN_PIN_AJ15_TYPEC_GPIO1_1_PP = 0x06,
    _2L_900PIN_PIN_AJ15_TYPEC_GPIO1_1_OD = 0x07,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT0 = 0x08,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT1 = 0x09,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT2 = 0x0A,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT3 = 0x0B,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT4 = 0x0C,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT5 = 0x0D,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT6 = 0x0E,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT7 = 0x0F,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT8 = 0x10,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT9 = 0x11,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT10 = 0x12,
    _2L_900PIN_PIN_AJ15_TEST12B_OUT11 = 0x13,
    _2L_900PIN_PIN_AJ15_NC = _2L_900PIN_PIN_AJ15_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AJ15;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1015
// MCU Ctrl : 0xFE15 at _2L_900PIN_PIN_AJ16_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AJ16                     (_2L_900PIN_PIN_AJ16_NC)

typedef enum
{
    _2L_900PIN_PIN_AJ16_GPI = 0x00,
    _2L_900PIN_PIN_AJ16_GPO_PP = 0x01,
    _2L_900PIN_PIN_AJ16_GPO_OD = 0x02,
    _2L_900PIN_PIN_AJ16_A_ADC2_0_0 = 0x03,
    _2L_900PIN_PIN_AJ16_TYPEC_GPIO2_1_PP = 0x04,
    _2L_900PIN_PIN_AJ16_TYPEC_GPIO2_1_OD = 0x05,
    _2L_900PIN_PIN_AJ16_TYPEC_GPIO3_1_PP = 0x06,
    _2L_900PIN_PIN_AJ16_TYPEC_GPIO3_1_OD = 0x07,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT0 = 0x08,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT1 = 0x09,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT2 = 0x0A,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT3 = 0x0B,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT4 = 0x0C,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT5 = 0x0D,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT6 = 0x0E,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT7 = 0x0F,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT8 = 0x10,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT9 = 0x11,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT10 = 0x12,
    _2L_900PIN_PIN_AJ16_TEST12B_OUT11 = 0x13,
    _2L_900PIN_PIN_AJ16_NC = _2L_900PIN_PIN_AJ16_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AJ16;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1014
// MCU Ctrl : 0xFE14 at _2L_900PIN_PIN_AJ17_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AJ17                     (_2L_900PIN_PIN_AJ17_NC)

typedef enum
{
    _2L_900PIN_PIN_AJ17_GPI = 0x00,
    _2L_900PIN_PIN_AJ17_GPO_PP = 0x01,
    _2L_900PIN_PIN_AJ17_GPO_OD = 0x02,
    _2L_900PIN_PIN_AJ17_A_ADC1_0_0 = 0x03,
    _2L_900PIN_PIN_AJ17_INT0_1 = 0x04,
    _2L_900PIN_PIN_AJ17_INT1_1 = 0x05,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT0 = 0x06,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT1 = 0x07,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT2 = 0x08,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT3 = 0x09,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT4 = 0x0A,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT5 = 0x0B,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT6 = 0x0C,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT7 = 0x0D,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT8 = 0x0E,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT9 = 0x0F,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT10 = 0x10,
    _2L_900PIN_PIN_AJ17_TEST12B_OUT11 = 0x11,
    _2L_900PIN_PIN_AJ17_NC = _2L_900PIN_PIN_AJ17_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AJ17;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1013
// MCU Ctrl : 0xFE13 at _2L_900PIN_PIN_AJ18_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AJ18                     (_2L_900PIN_PIN_AJ18_NC)

typedef enum
{
    _2L_900PIN_PIN_AJ18_GPI = 0x00,
    _2L_900PIN_PIN_AJ18_GPO_PP = 0x01,
    _2L_900PIN_PIN_AJ18_GPO_OD = 0x02,
    _2L_900PIN_PIN_AJ18_A_ADC0_0_0 = 0x03,
    _2L_900PIN_PIN_AJ18_INT0_4 = 0x04,
    _2L_900PIN_PIN_AJ18_INT1_4 = 0x05,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT0 = 0x06,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT1 = 0x07,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT2 = 0x08,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT3 = 0x09,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT4 = 0x0A,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT5 = 0x0B,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT6 = 0x0C,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT7 = 0x0D,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT8 = 0x0E,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT9 = 0x0F,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT10 = 0x10,
    _2L_900PIN_PIN_AJ18_TEST12B_OUT11 = 0x11,
    _2L_900PIN_PIN_AJ18_NC = _2L_900PIN_PIN_AJ18_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AJ18;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101A
// MCU Ctrl : 0xFE1A at _2L_900PIN_PIN_AK15_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AK15                     (_2L_900PIN_PIN_AK15_NC)

typedef enum
{
    _2L_900PIN_PIN_AK15_GPI = 0x00,
    _2L_900PIN_PIN_AK15_GPO_PP = 0x01,
    _2L_900PIN_PIN_AK15_GPO_OD = 0x02,
    _2L_900PIN_PIN_AK15_A_ADC3_1_0 = 0x03,
    _2L_900PIN_PIN_AK15_EXT_UART_RX_0_0 = 0x04,
    _2L_900PIN_PIN_AK15_EXT_UART_RX_1_0 = 0x05,
    _2L_900PIN_PIN_AK15_EXT_UART_RX_2_0 = 0x06,
    _2L_900PIN_PIN_AK15_TEST12B_OUT0 = 0x07,
    _2L_900PIN_PIN_AK15_TEST12B_OUT1 = 0x08,
    _2L_900PIN_PIN_AK15_TEST12B_OUT2 = 0x09,
    _2L_900PIN_PIN_AK15_TEST12B_OUT3 = 0x0A,
    _2L_900PIN_PIN_AK15_TEST12B_OUT4 = 0x0B,
    _2L_900PIN_PIN_AK15_TEST12B_OUT5 = 0x0C,
    _2L_900PIN_PIN_AK15_TEST12B_OUT6 = 0x0D,
    _2L_900PIN_PIN_AK15_TEST12B_OUT7 = 0x0E,
    _2L_900PIN_PIN_AK15_TEST12B_OUT8 = 0x0F,
    _2L_900PIN_PIN_AK15_TEST12B_OUT9 = 0x10,
    _2L_900PIN_PIN_AK15_TEST12B_OUT10 = 0x11,
    _2L_900PIN_PIN_AK15_TEST12B_OUT11 = 0x12,
    _2L_900PIN_PIN_AK15_NC = _2L_900PIN_PIN_AK15_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AK15;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1019
// MCU Ctrl : 0xFE19 at _2L_900PIN_PIN_AK16_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AK16                     (_2L_900PIN_PIN_AK16_NC)

typedef enum
{
    _2L_900PIN_PIN_AK16_GPI = 0x00,
    _2L_900PIN_PIN_AK16_GPO_PP = 0x01,
    _2L_900PIN_PIN_AK16_GPO_OD = 0x02,
    _2L_900PIN_PIN_AK16_A_ADC2_1_0 = 0x03,
    _2L_900PIN_PIN_AK16_EXT_UART_TX_0_0 = 0x04,
    _2L_900PIN_PIN_AK16_EXT_UART_TX_1_0 = 0x05,
    _2L_900PIN_PIN_AK16_EXT_UART_TX_2_0 = 0x06,
    _2L_900PIN_PIN_AK16_TEST12B_OUT0 = 0x07,
    _2L_900PIN_PIN_AK16_TEST12B_OUT1 = 0x08,
    _2L_900PIN_PIN_AK16_TEST12B_OUT2 = 0x09,
    _2L_900PIN_PIN_AK16_TEST12B_OUT3 = 0x0A,
    _2L_900PIN_PIN_AK16_TEST12B_OUT4 = 0x0B,
    _2L_900PIN_PIN_AK16_TEST12B_OUT5 = 0x0C,
    _2L_900PIN_PIN_AK16_TEST12B_OUT6 = 0x0D,
    _2L_900PIN_PIN_AK16_TEST12B_OUT7 = 0x0E,
    _2L_900PIN_PIN_AK16_TEST12B_OUT8 = 0x0F,
    _2L_900PIN_PIN_AK16_TEST12B_OUT9 = 0x10,
    _2L_900PIN_PIN_AK16_TEST12B_OUT10 = 0x11,
    _2L_900PIN_PIN_AK16_TEST12B_OUT11 = 0x12,
    _2L_900PIN_PIN_AK16_NC = _2L_900PIN_PIN_AK16_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AK16;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1018
// MCU Ctrl : 0xFE18 at _2L_900PIN_PIN_AK17_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AK17                     (_2L_900PIN_PIN_AK17_NC)

typedef enum
{
    _2L_900PIN_PIN_AK17_GPI = 0x00,
    _2L_900PIN_PIN_AK17_GPO_PP = 0x01,
    _2L_900PIN_PIN_AK17_GPO_OD = 0x02,
    _2L_900PIN_PIN_AK17_A_ADC1_1_0 = 0x03,
    _2L_900PIN_PIN_AK17_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AK17_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AK17_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AK17_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AK17_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AK17_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AK17_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AK17_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AK17_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AK17_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AK17_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AK17_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AK17_NC = _2L_900PIN_PIN_AK17_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AK17;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1017
// MCU Ctrl : 0xFE17 at _2L_900PIN_PIN_AK18_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AK18                     (_2L_900PIN_PIN_AK18_NC)

typedef enum
{
    _2L_900PIN_PIN_AK18_GPI = 0x00,
    _2L_900PIN_PIN_AK18_GPO_PP = 0x01,
    _2L_900PIN_PIN_AK18_GPO_OD = 0x02,
    _2L_900PIN_PIN_AK18_A_ADC0_1_0 = 0x03,
    _2L_900PIN_PIN_AK18_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AK18_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AK18_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AK18_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AK18_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AK18_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AK18_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AK18_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AK18_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AK18_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AK18_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AK18_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AK18_NC = _2L_900PIN_PIN_AK18_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AK18;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101B at _OFF_Region
// MCU Ctrl : 0xFE1B at _2L_900PIN_2L_900PIN_PIN_AG20_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AG20_OFF_REGION          (_2L_900PIN_PIN_AG20_NC)

typedef enum
{
    _2L_900PIN_PIN_AG20_GPI = 0x00,
    _2L_900PIN_PIN_AG20_GPO_PP = 0x01,
    _2L_900PIN_PIN_AG20_GPO_OD = 0x02,
    _2L_900PIN_PIN_AG20_LINE_INL = 0x03,
    _2L_900PIN_PIN_AG20_MCK = 0x04,
    _2L_900PIN_PIN_AG20_NC = _2L_900PIN_PIN_AG20_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AG20;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101C at _OFF_Region
// MCU Ctrl : 0xFE1C at _2L_900PIN_2L_900PIN_PIN_AF20_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AF20_OFF_REGION          (_2L_900PIN_PIN_AF20_NC)

typedef enum
{
    _2L_900PIN_PIN_AF20_GPI = 0x00,
    _2L_900PIN_PIN_AF20_GPO_PP = 0x01,
    _2L_900PIN_PIN_AF20_GPO_OD = 0x02,
    _2L_900PIN_PIN_AF20_LINE_INR = 0x03,
    _2L_900PIN_PIN_AF20_SCK = 0x04,
    _2L_900PIN_PIN_AF20_NC = _2L_900PIN_PIN_AF20_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AF20;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101D at _OFF_Region
// MCU Ctrl : 0xFE1D at _2L_900PIN_2L_900PIN_PIN_AF19_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AF19_OFF_REGION          (_2L_900PIN_PIN_AF19_NC)

typedef enum
{
    _2L_900PIN_PIN_AF19_GPI = 0x00,
    _2L_900PIN_PIN_AF19_GPO_PP = 0x01,
    _2L_900PIN_PIN_AF19_GPO_OD = 0x02,
    _2L_900PIN_PIN_AF19_AUDIO_ADC_VREF = 0x03,
    _2L_900PIN_PIN_AF19_NC = _2L_900PIN_PIN_AF19_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AF19;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x101F at _OFF_Region
// MCU Ctrl : 0xFE1F at _2L_900PIN_2L_900PIN_PIN_AG22_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AG22_OFF_REGION          (_2L_900PIN_PIN_AG22_NC)

typedef enum
{
    _2L_900PIN_PIN_AG22_GPI = 0x00,
    _2L_900PIN_PIN_AG22_GPO_PP = 0x01,
    _2L_900PIN_PIN_AG22_GPO_OD = 0x02,
    _2L_900PIN_PIN_AG22_AUDIO_SOUTL = 0x03,
    _2L_900PIN_PIN_AG22_SD0 = 0x04,
    _2L_900PIN_PIN_AG22_SPDIF0 = 0x05,
    _2L_900PIN_PIN_AG22_NC = _2L_900PIN_PIN_AG22_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AG22;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1020 at _OFF_Region
// MCU Ctrl : 0xFE20 at _2L_900PIN_2L_900PIN_PIN_AF22_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AF22_OFF_REGION          (_2L_900PIN_PIN_AF22_NC)

typedef enum
{
    _2L_900PIN_PIN_AF22_GPI = 0x00,
    _2L_900PIN_PIN_AF22_GPO_PP = 0x01,
    _2L_900PIN_PIN_AF22_GPO_OD = 0x02,
    _2L_900PIN_PIN_AF22_AUDIO_SOUTR = 0x03,
    _2L_900PIN_PIN_AF22_SD1 = 0x04,
    _2L_900PIN_PIN_AF22_SPDIF1 = 0x05,
    _2L_900PIN_PIN_AF22_NC = _2L_900PIN_PIN_AF22_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AF22;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1021 at _OFF_Region
// MCU Ctrl : 0xFE21 at _2L_900PIN_2L_900PIN_PIN_AG23_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AG23_OFF_REGION          (_2L_900PIN_PIN_AG23_NC)

typedef enum
{
    _2L_900PIN_PIN_AG23_GPI = 0x00,
    _2L_900PIN_PIN_AG23_GPO_PP = 0x01,
    _2L_900PIN_PIN_AG23_GPO_OD = 0x02,
    _2L_900PIN_PIN_AG23_AUDIO_HOUTL = 0x03,
    _2L_900PIN_PIN_AG23_SD2 = 0x04,
    _2L_900PIN_PIN_AG23_SPDIF2 = 0x05,
    _2L_900PIN_PIN_AG23_NC = _2L_900PIN_PIN_AG23_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AG23;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1022 at _OFF_Region
// MCU Ctrl : 0xFE22 at _2L_900PIN_2L_900PIN_PIN_AE23_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AE23_OFF_REGION          (_2L_900PIN_PIN_AE23_NC)

typedef enum
{
    _2L_900PIN_PIN_AE23_GPI = 0x00,
    _2L_900PIN_PIN_AE23_GPO_PP = 0x01,
    _2L_900PIN_PIN_AE23_GPO_OD = 0x02,
    _2L_900PIN_PIN_AE23_AUDIO_HOUTR = 0x03,
    _2L_900PIN_PIN_AE23_SD3 = 0x04,
    _2L_900PIN_PIN_AE23_SPDIF3 = 0x05,
    _2L_900PIN_PIN_AE23_NC = _2L_900PIN_PIN_AE23_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AE23;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1023 at _OFF_Region
// MCU Ctrl : 0xFE23 at _2L_900PIN_2L_900PIN_PIN_AA22_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AA22_OFF_REGION          (_2L_900PIN_PIN_AA22_NC)

typedef enum
{
    _2L_900PIN_PIN_AA22_GPI = 0x00,
    _2L_900PIN_PIN_AA22_GPO_PP = 0x01,
    _2L_900PIN_PIN_AA22_GPO_OD = 0x02,
    _2L_900PIN_PIN_AA22_PWM0_PP = 0x03,
    _2L_900PIN_PIN_AA22_PWM0_OD = 0x04,
    _2L_900PIN_PIN_AA22_PWM0_DIMMING_PP = 0x05,
    _2L_900PIN_PIN_AA22_PWM0_DIMMING = 0x06,
    _2L_900PIN_PIN_AA22_USB_SPI_CLK_0_3 = 0x07,
    _2L_900PIN_PIN_AA22_USB_SPI_CLK_1_3 = 0x08,
    _2L_900PIN_PIN_AA22_USB_SPI_CLK_2_3 = 0x09,
    _2L_900PIN_PIN_AA22_TCON6 = 0x0A,
    _2L_900PIN_PIN_AA22_TEST12B_OUT0 = 0x0B,
    _2L_900PIN_PIN_AA22_TEST12B_OUT1 = 0x0C,
    _2L_900PIN_PIN_AA22_TEST12B_OUT2 = 0x0D,
    _2L_900PIN_PIN_AA22_TEST12B_OUT3 = 0x0E,
    _2L_900PIN_PIN_AA22_TEST12B_OUT4 = 0x0F,
    _2L_900PIN_PIN_AA22_TEST12B_OUT5 = 0x10,
    _2L_900PIN_PIN_AA22_TEST12B_OUT6 = 0x11,
    _2L_900PIN_PIN_AA22_TEST12B_OUT7 = 0x12,
    _2L_900PIN_PIN_AA22_TEST12B_OUT8 = 0x13,
    _2L_900PIN_PIN_AA22_TEST12B_OUT9 = 0x14,
    _2L_900PIN_PIN_AA22_TEST12B_OUT10 = 0x15,
    _2L_900PIN_PIN_AA22_TEST12B_OUT11 = 0x16,
    _2L_900PIN_PIN_AA22_NC = _2L_900PIN_PIN_AA22_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AA22;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1024 at _OFF_Region
// MCU Ctrl : 0xFE24 at _2L_900PIN_2L_900PIN_PIN_W23_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_W23_OFF_REGION           (_2L_900PIN_PIN_W23_NC)

typedef enum
{
    _2L_900PIN_PIN_W23_GPI = 0x00,
    _2L_900PIN_PIN_W23_GPO_PP = 0x01,
    _2L_900PIN_PIN_W23_GPO_OD = 0x02,
    _2L_900PIN_PIN_W23_IICSCL_0_6 = 0x03,
    _2L_900PIN_PIN_W23_IICSCL_1_6 = 0x04,
    _2L_900PIN_PIN_W23_PWM5_PP = 0x05,
    _2L_900PIN_PIN_W23_PWM5_OD = 0x06,
    _2L_900PIN_PIN_W23_PWM5_DIMMING_PP = 0x07,
    _2L_900PIN_PIN_W23_PWM5_DIMMING = 0x08,
    _2L_900PIN_PIN_W23_USB_SPI_SI_0_3 = 0x09,
    _2L_900PIN_PIN_W23_USB_SPI_SI_1_3 = 0x0A,
    _2L_900PIN_PIN_W23_USB_SPI_SI_2_3 = 0x0B,
    _2L_900PIN_PIN_W23_TEST12B_OUT0 = 0x0C,
    _2L_900PIN_PIN_W23_TEST12B_OUT1 = 0x0D,
    _2L_900PIN_PIN_W23_TEST12B_OUT2 = 0x0E,
    _2L_900PIN_PIN_W23_TEST12B_OUT3 = 0x0F,
    _2L_900PIN_PIN_W23_TEST12B_OUT4 = 0x10,
    _2L_900PIN_PIN_W23_TEST12B_OUT5 = 0x11,
    _2L_900PIN_PIN_W23_TEST12B_OUT6 = 0x12,
    _2L_900PIN_PIN_W23_TEST12B_OUT7 = 0x13,
    _2L_900PIN_PIN_W23_TEST12B_OUT8 = 0x14,
    _2L_900PIN_PIN_W23_TEST12B_OUT9 = 0x15,
    _2L_900PIN_PIN_W23_TEST12B_OUT10 = 0x16,
    _2L_900PIN_PIN_W23_TEST12B_OUT11 = 0x17,
    _2L_900PIN_PIN_W23_NC = _2L_900PIN_PIN_W23_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_W23;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1025 at _OFF_Region
// MCU Ctrl : 0xFE25 at _2L_900PIN_2L_900PIN_PIN_W22_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_W22_OFF_REGION           (_2L_900PIN_PIN_W22_NC)

typedef enum
{
    _2L_900PIN_PIN_W22_GPI = 0x00,
    _2L_900PIN_PIN_W22_GPO_PP = 0x01,
    _2L_900PIN_PIN_W22_GPO_OD = 0x02,
    _2L_900PIN_PIN_W22_IICSDA_0_6 = 0x03,
    _2L_900PIN_PIN_W22_IICSDA_1_6 = 0x04,
    _2L_900PIN_PIN_W22_M1_IDOMAIN_VS_OUT = 0x05,
    _2L_900PIN_PIN_W22_USB_SPI_SO_0_3 = 0x06,
    _2L_900PIN_PIN_W22_USB_SPI_SO_1_3 = 0x07,
    _2L_900PIN_PIN_W22_USB_SPI_SO_2_3 = 0x08,
    _2L_900PIN_PIN_W22_TEST12B_OUT0 = 0x09,
    _2L_900PIN_PIN_W22_TEST12B_OUT1 = 0x0A,
    _2L_900PIN_PIN_W22_TEST12B_OUT2 = 0x0B,
    _2L_900PIN_PIN_W22_TEST12B_OUT3 = 0x0C,
    _2L_900PIN_PIN_W22_TEST12B_OUT4 = 0x0D,
    _2L_900PIN_PIN_W22_TEST12B_OUT5 = 0x0E,
    _2L_900PIN_PIN_W22_TEST12B_OUT6 = 0x0F,
    _2L_900PIN_PIN_W22_TEST12B_OUT7 = 0x10,
    _2L_900PIN_PIN_W22_TEST12B_OUT8 = 0x11,
    _2L_900PIN_PIN_W22_TEST12B_OUT9 = 0x12,
    _2L_900PIN_PIN_W22_TEST12B_OUT10 = 0x13,
    _2L_900PIN_PIN_W22_TEST12B_OUT11 = 0x14,
    _2L_900PIN_PIN_W22_NC = _2L_900PIN_PIN_W22_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_W22;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1026 at _OFF_Region
// MCU Ctrl : 0xFE26 at _2L_900PIN_PIN_AC26_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AC26_OFF_REGION          (_2L_900PIN_PIN_AC26_NC)

typedef enum
{
    _2L_900PIN_PIN_AC26_GPI = 0x00,
    _2L_900PIN_PIN_AC26_GPO_PP = 0x01,
    _2L_900PIN_PIN_AC26_GPO_OD = 0x02,
    _2L_900PIN_PIN_AC26_IICSCL_0_4 = 0x03,
    _2L_900PIN_PIN_AC26_IICSCL_1_4 = 0x04,
    _2L_900PIN_PIN_AC26_USB_SPI_CEB0_0_3 = 0x05,
    _2L_900PIN_PIN_AC26_USB_SPI_CEB0_1_3 = 0x06,
    _2L_900PIN_PIN_AC26_USB_SPI_CEB0_2_3 = 0x07,
    _2L_900PIN_PIN_AC26_TEST12B_OUT0 = 0x08,
    _2L_900PIN_PIN_AC26_TEST12B_OUT1 = 0x09,
    _2L_900PIN_PIN_AC26_TEST12B_OUT2 = 0x0A,
    _2L_900PIN_PIN_AC26_TEST12B_OUT3 = 0x0B,
    _2L_900PIN_PIN_AC26_TEST12B_OUT4 = 0x0C,
    _2L_900PIN_PIN_AC26_TEST12B_OUT5 = 0x0D,
    _2L_900PIN_PIN_AC26_TEST12B_OUT6 = 0x0E,
    _2L_900PIN_PIN_AC26_TEST12B_OUT7 = 0x0F,
    _2L_900PIN_PIN_AC26_TEST12B_OUT8 = 0x10,
    _2L_900PIN_PIN_AC26_TEST12B_OUT9 = 0x11,
    _2L_900PIN_PIN_AC26_TEST12B_OUT10 = 0x12,
    _2L_900PIN_PIN_AC26_TEST12B_OUT11 = 0x13,
    _2L_900PIN_PIN_AC26_NC = _2L_900PIN_PIN_AC26_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AC26;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1027 at _OFF_Region
// MCU Ctrl : 0xFE27 at _2L_900PIN_PIN_AB26_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AB26_OFF_REGION          (_2L_900PIN_PIN_AB26_NC)

typedef enum
{
    _2L_900PIN_PIN_AB26_GPI = 0x00,
    _2L_900PIN_PIN_AB26_GPO_PP = 0x01,
    _2L_900PIN_PIN_AB26_GPO_OD = 0x02,
    _2L_900PIN_PIN_AB26_IICSDA_0_4 = 0x03,
    _2L_900PIN_PIN_AB26_IICSDA_1_4 = 0x04,
    _2L_900PIN_PIN_AB26_USB_SPI_CEB1_0_3 = 0x05,
    _2L_900PIN_PIN_AB26_USB_SPI_CEB1_1_3 = 0x06,
    _2L_900PIN_PIN_AB26_USB_SPI_CEB1_2_3 = 0x07,
    _2L_900PIN_PIN_AB26_TEST12B_OUT0 = 0x08,
    _2L_900PIN_PIN_AB26_TEST12B_OUT1 = 0x09,
    _2L_900PIN_PIN_AB26_TEST12B_OUT2 = 0x0A,
    _2L_900PIN_PIN_AB26_TEST12B_OUT3 = 0x0B,
    _2L_900PIN_PIN_AB26_TEST12B_OUT4 = 0x0C,
    _2L_900PIN_PIN_AB26_TEST12B_OUT5 = 0x0D,
    _2L_900PIN_PIN_AB26_TEST12B_OUT6 = 0x0E,
    _2L_900PIN_PIN_AB26_TEST12B_OUT7 = 0x0F,
    _2L_900PIN_PIN_AB26_TEST12B_OUT8 = 0x10,
    _2L_900PIN_PIN_AB26_TEST12B_OUT9 = 0x11,
    _2L_900PIN_PIN_AB26_TEST12B_OUT10 = 0x12,
    _2L_900PIN_PIN_AB26_TEST12B_OUT11 = 0x13,
    _2L_900PIN_PIN_AB26_NC = _2L_900PIN_PIN_AB26_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AB26;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1028 at _OFF_Region
// MCU Ctrl : 0xFE28 at _2L_900PIN_PIN_AJ30_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AJ30_OFF_REGION          (_2L_900PIN_PIN_AJ30_NC)

typedef enum
{
    _2L_900PIN_PIN_AJ30_GPI = 0x00,
    _2L_900PIN_PIN_AJ30_GPO_PP = 0x01,
    _2L_900PIN_PIN_AJ30_GPO_OD = 0x02,
    _2L_900PIN_PIN_AJ30_EDPTX_AUX_N_0 = 0x03,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AJ30_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AJ30_NC = _2L_900PIN_PIN_AJ30_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AJ30;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1029 at _OFF_Region
// MCU Ctrl : 0xFE29 at _2L_900PIN_PIN_AH30_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AH30_OFF_REGION          (_2L_900PIN_PIN_AH30_NC)

typedef enum
{
    _2L_900PIN_PIN_AH30_GPI = 0x00,
    _2L_900PIN_PIN_AH30_GPO_PP = 0x01,
    _2L_900PIN_PIN_AH30_GPO_OD = 0x02,
    _2L_900PIN_PIN_AH30_EDPTX_AUX_P_0 = 0x03,
    _2L_900PIN_PIN_AH30_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AH30_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AH30_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AH30_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AH30_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AH30_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AH30_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AH30_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AH30_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AH30_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AH30_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AH30_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AH30_NC = _2L_900PIN_PIN_AH30_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AH30;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102A at _OFF_Region
// MCU Ctrl : 0xFE2A at _2L_900PIN_PIN_AG30_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AG30_OFF_REGION          (_2L_900PIN_PIN_AG30_NC)

typedef enum
{
    _2L_900PIN_PIN_AG30_GPI = 0x00,
    _2L_900PIN_PIN_AG30_GPO_PP = 0x01,
    _2L_900PIN_PIN_AG30_GPO_OD = 0x02,
    _2L_900PIN_PIN_AG30_EDPTX_AUX_N_1 = 0x03,
    _2L_900PIN_PIN_AG30_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AG30_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AG30_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AG30_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AG30_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AG30_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AG30_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AG30_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AG30_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AG30_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AG30_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AG30_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AG30_NC = _2L_900PIN_PIN_AG30_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AG30;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102B at _OFF_Region
// MCU Ctrl : 0xFE2B at _2L_900PIN_PIN_AF30_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AF30_OFF_REGION          (_2L_900PIN_PIN_AF30_NC)

typedef enum
{
    _2L_900PIN_PIN_AF30_GPI = 0x00,
    _2L_900PIN_PIN_AF30_GPO_PP = 0x01,
    _2L_900PIN_PIN_AF30_GPO_OD = 0x02,
    _2L_900PIN_PIN_AF30_EDPTX_AUX_P_1 = 0x03,
    _2L_900PIN_PIN_AF30_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_AF30_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_AF30_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_AF30_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_AF30_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_AF30_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_AF30_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_AF30_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_AF30_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_AF30_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_AF30_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_AF30_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_AF30_NC = _2L_900PIN_PIN_AF30_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AF30;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102C at _OFF_Region
// MCU Ctrl : 0xFE2C at _2L_900PIN_2L_900PIN_PIN_Y23_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_Y23_OFF_REGION           (_2L_900PIN_PIN_Y23_NC)

typedef enum
{
    _2L_900PIN_PIN_Y23_GPI = 0x00,
    _2L_900PIN_PIN_Y23_GPO_PP = 0x01,
    _2L_900PIN_PIN_Y23_GPO_OD = 0x02,
    _2L_900PIN_PIN_Y23_EXT_UART_RX_0_6 = 0x03,
    _2L_900PIN_PIN_Y23_EXT_UART_RX_1_6 = 0x04,
    _2L_900PIN_PIN_Y23_EXT_UART_RX_2_6 = 0x05,
    _2L_900PIN_PIN_Y23_TEST12B_OUT0 = 0x06,
    _2L_900PIN_PIN_Y23_TEST12B_OUT1 = 0x07,
    _2L_900PIN_PIN_Y23_TEST12B_OUT2 = 0x08,
    _2L_900PIN_PIN_Y23_TEST12B_OUT3 = 0x09,
    _2L_900PIN_PIN_Y23_TEST12B_OUT4 = 0x0A,
    _2L_900PIN_PIN_Y23_TEST12B_OUT5 = 0x0B,
    _2L_900PIN_PIN_Y23_TEST12B_OUT6 = 0x0C,
    _2L_900PIN_PIN_Y23_TEST12B_OUT7 = 0x0D,
    _2L_900PIN_PIN_Y23_TEST12B_OUT8 = 0x0E,
    _2L_900PIN_PIN_Y23_TEST12B_OUT9 = 0x0F,
    _2L_900PIN_PIN_Y23_TEST12B_OUT10 = 0x10,
    _2L_900PIN_PIN_Y23_TEST12B_OUT11 = 0x11,
    _2L_900PIN_PIN_Y23_NC = _2L_900PIN_PIN_Y23_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_Y23;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102D at _OFF_Region
// MCU Ctrl : 0xFE2D at _2L_900PIN_2L_900PIN_PIN_Y22_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_Y22_OFF_REGION           (_2L_900PIN_PIN_Y22_NC)

typedef enum
{
    _2L_900PIN_PIN_Y22_GPI = 0x00,
    _2L_900PIN_PIN_Y22_GPO_PP = 0x01,
    _2L_900PIN_PIN_Y22_GPO_OD = 0x02,
    _2L_900PIN_PIN_Y22_EXT_UART_TX_0_6 = 0x03,
    _2L_900PIN_PIN_Y22_EXT_UART_TX_1_6 = 0x04,
    _2L_900PIN_PIN_Y22_EXT_UART_TX_2_6 = 0x05,
    _2L_900PIN_PIN_Y22_TEST12B_OUT0 = 0x06,
    _2L_900PIN_PIN_Y22_TEST12B_OUT1 = 0x07,
    _2L_900PIN_PIN_Y22_TEST12B_OUT2 = 0x08,
    _2L_900PIN_PIN_Y22_TEST12B_OUT3 = 0x09,
    _2L_900PIN_PIN_Y22_TEST12B_OUT4 = 0x0A,
    _2L_900PIN_PIN_Y22_TEST12B_OUT5 = 0x0B,
    _2L_900PIN_PIN_Y22_TEST12B_OUT6 = 0x0C,
    _2L_900PIN_PIN_Y22_TEST12B_OUT7 = 0x0D,
    _2L_900PIN_PIN_Y22_TEST12B_OUT8 = 0x0E,
    _2L_900PIN_PIN_Y22_TEST12B_OUT9 = 0x0F,
    _2L_900PIN_PIN_Y22_TEST12B_OUT10 = 0x10,
    _2L_900PIN_PIN_Y22_TEST12B_OUT11 = 0x11,
    _2L_900PIN_PIN_Y22_NC = _2L_900PIN_PIN_Y22_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_Y22;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102E at _OFF_Region
// MCU Ctrl : 0xFE2E at _2L_900PIN_2L_900PIN_PIN_AA23_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AA23_OFF_REGION          (_2L_900PIN_PIN_AA23_NC)

typedef enum
{
    _2L_900PIN_PIN_AA23_GPI = 0x00,
    _2L_900PIN_PIN_AA23_GPO_PP = 0x01,
    _2L_900PIN_PIN_AA23_GPO_OD = 0x02,
    _2L_900PIN_PIN_AA23_USB_SPI_CLK_0_1 = 0x03,
    _2L_900PIN_PIN_AA23_USB_SPI_CLK_1_1 = 0x04,
    _2L_900PIN_PIN_AA23_USB_SPI_CLK_2_1 = 0x05,
    _2L_900PIN_PIN_AA23_IICSCL_0_5 = 0x06,
    _2L_900PIN_PIN_AA23_IICSCL_1_5 = 0x07,
    _2L_900PIN_PIN_AA23_TCON9 = 0x08,
    _2L_900PIN_PIN_AA23_TEST12B_OUT0 = 0x09,
    _2L_900PIN_PIN_AA23_TEST12B_OUT1 = 0x0A,
    _2L_900PIN_PIN_AA23_TEST12B_OUT2 = 0x0B,
    _2L_900PIN_PIN_AA23_TEST12B_OUT3 = 0x0C,
    _2L_900PIN_PIN_AA23_TEST12B_OUT4 = 0x0D,
    _2L_900PIN_PIN_AA23_TEST12B_OUT5 = 0x0E,
    _2L_900PIN_PIN_AA23_TEST12B_OUT6 = 0x0F,
    _2L_900PIN_PIN_AA23_TEST12B_OUT7 = 0x10,
    _2L_900PIN_PIN_AA23_TEST12B_OUT8 = 0x11,
    _2L_900PIN_PIN_AA23_TEST12B_OUT9 = 0x12,
    _2L_900PIN_PIN_AA23_TEST12B_OUT10 = 0x13,
    _2L_900PIN_PIN_AA23_TEST12B_OUT11 = 0x14,
    _2L_900PIN_PIN_AA23_NC = _2L_900PIN_PIN_AA23_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AA23;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x102F at _OFF_Region
// MCU Ctrl : 0xFE2F at _2L_900PIN_2L_900PIN_PIN_Y24_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_Y24_OFF_REGION           (_2L_900PIN_PIN_Y24_NC)

typedef enum
{
    _2L_900PIN_PIN_Y24_GPI = 0x00,
    _2L_900PIN_PIN_Y24_GPO_PP = 0x01,
    _2L_900PIN_PIN_Y24_GPO_OD = 0x02,
    _2L_900PIN_PIN_Y24_USB_SPI_SI_0_1 = 0x03,
    _2L_900PIN_PIN_Y24_USB_SPI_SI_1_1 = 0x04,
    _2L_900PIN_PIN_Y24_USB_SPI_SI_2_1 = 0x05,
    _2L_900PIN_PIN_Y24_IICSDA_0_5 = 0x06,
    _2L_900PIN_PIN_Y24_IICSDA_1_5 = 0x07,
    _2L_900PIN_PIN_Y24_TCON10 = 0x08,
    _2L_900PIN_PIN_Y24_TEST12B_OUT0 = 0x09,
    _2L_900PIN_PIN_Y24_TEST12B_OUT1 = 0x0A,
    _2L_900PIN_PIN_Y24_TEST12B_OUT2 = 0x0B,
    _2L_900PIN_PIN_Y24_TEST12B_OUT3 = 0x0C,
    _2L_900PIN_PIN_Y24_TEST12B_OUT4 = 0x0D,
    _2L_900PIN_PIN_Y24_TEST12B_OUT5 = 0x0E,
    _2L_900PIN_PIN_Y24_TEST12B_OUT6 = 0x0F,
    _2L_900PIN_PIN_Y24_TEST12B_OUT7 = 0x10,
    _2L_900PIN_PIN_Y24_TEST12B_OUT8 = 0x11,
    _2L_900PIN_PIN_Y24_TEST12B_OUT9 = 0x12,
    _2L_900PIN_PIN_Y24_TEST12B_OUT10 = 0x13,
    _2L_900PIN_PIN_Y24_TEST12B_OUT11 = 0x14,
    _2L_900PIN_PIN_Y24_NC = _2L_900PIN_PIN_Y24_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_Y24;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1030 at _OFF_Region
// MCU Ctrl : 0xFE30 at _2L_900PIN_2L_900PIN_PIN_AA24_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AA24_OFF_REGION          (_2L_900PIN_PIN_AA24_NC)

typedef enum
{
    _2L_900PIN_PIN_AA24_GPI = 0x00,
    _2L_900PIN_PIN_AA24_GPO_PP = 0x01,
    _2L_900PIN_PIN_AA24_GPO_OD = 0x02,
    _2L_900PIN_PIN_AA24_USB_SPI_SO_0_1 = 0x03,
    _2L_900PIN_PIN_AA24_USB_SPI_SO_1_1 = 0x04,
    _2L_900PIN_PIN_AA24_USB_SPI_SO_2_1 = 0x05,
    _2L_900PIN_PIN_AA24_TCON11 = 0x06,
    _2L_900PIN_PIN_AA24_TEST12B_OUT0 = 0x07,
    _2L_900PIN_PIN_AA24_TEST12B_OUT1 = 0x08,
    _2L_900PIN_PIN_AA24_TEST12B_OUT2 = 0x09,
    _2L_900PIN_PIN_AA24_TEST12B_OUT3 = 0x0A,
    _2L_900PIN_PIN_AA24_TEST12B_OUT4 = 0x0B,
    _2L_900PIN_PIN_AA24_TEST12B_OUT5 = 0x0C,
    _2L_900PIN_PIN_AA24_TEST12B_OUT6 = 0x0D,
    _2L_900PIN_PIN_AA24_TEST12B_OUT7 = 0x0E,
    _2L_900PIN_PIN_AA24_TEST12B_OUT8 = 0x0F,
    _2L_900PIN_PIN_AA24_TEST12B_OUT9 = 0x10,
    _2L_900PIN_PIN_AA24_TEST12B_OUT10 = 0x11,
    _2L_900PIN_PIN_AA24_TEST12B_OUT11 = 0x12,
    _2L_900PIN_PIN_AA24_NC = _2L_900PIN_PIN_AA24_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AA24;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1031 at _OFF_Region
// MCU Ctrl : 0xFE31 at _2L_900PIN_2L_900PIN_PIN_Y25_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_Y25_OFF_REGION           (_2L_900PIN_PIN_Y25_NC)

typedef enum
{
    _2L_900PIN_PIN_Y25_GPI = 0x00,
    _2L_900PIN_PIN_Y25_GPO_PP = 0x01,
    _2L_900PIN_PIN_Y25_GPO_OD = 0x02,
    _2L_900PIN_PIN_Y25_USB_SPI_CEB0_0_1 = 0x03,
    _2L_900PIN_PIN_Y25_USB_SPI_CEB0_1_1 = 0x04,
    _2L_900PIN_PIN_Y25_USB_SPI_CEB0_2_1 = 0x05,
    _2L_900PIN_PIN_Y25_TCON12 = 0x06,
    _2L_900PIN_PIN_Y25_TEST12B_OUT0 = 0x07,
    _2L_900PIN_PIN_Y25_TEST12B_OUT1 = 0x08,
    _2L_900PIN_PIN_Y25_TEST12B_OUT2 = 0x09,
    _2L_900PIN_PIN_Y25_TEST12B_OUT3 = 0x0A,
    _2L_900PIN_PIN_Y25_TEST12B_OUT4 = 0x0B,
    _2L_900PIN_PIN_Y25_TEST12B_OUT5 = 0x0C,
    _2L_900PIN_PIN_Y25_TEST12B_OUT6 = 0x0D,
    _2L_900PIN_PIN_Y25_TEST12B_OUT7 = 0x0E,
    _2L_900PIN_PIN_Y25_TEST12B_OUT8 = 0x0F,
    _2L_900PIN_PIN_Y25_TEST12B_OUT9 = 0x10,
    _2L_900PIN_PIN_Y25_TEST12B_OUT10 = 0x11,
    _2L_900PIN_PIN_Y25_TEST12B_OUT11 = 0x12,
    _2L_900PIN_PIN_Y25_NC = _2L_900PIN_PIN_Y25_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_Y25;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1032 at _OFF_Region
// MCU Ctrl : 0xFE32 at _2L_900PIN_2L_900PIN_PIN_AA25_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AA25_OFF_REGION          (_2L_900PIN_PIN_AA25_NC)

typedef enum
{
    _2L_900PIN_PIN_AA25_GPI = 0x00,
    _2L_900PIN_PIN_AA25_GPO_PP = 0x01,
    _2L_900PIN_PIN_AA25_GPO_OD = 0x02,
    _2L_900PIN_PIN_AA25_USB_SPI_CEB1_0_1 = 0x03,
    _2L_900PIN_PIN_AA25_USB_SPI_CEB1_1_1 = 0x04,
    _2L_900PIN_PIN_AA25_USB_SPI_CEB1_2_1 = 0x05,
    _2L_900PIN_PIN_AA25_PWM4_PP = 0x06,
    _2L_900PIN_PIN_AA25_PWM4_OD = 0x07,
    _2L_900PIN_PIN_AA25_PWM4_DIMMING_PP = 0x08,
    _2L_900PIN_PIN_AA25_PWM4_DIMMING = 0x09,
    _2L_900PIN_PIN_AA25_TEST12B_OUT0 = 0x0A,
    _2L_900PIN_PIN_AA25_TEST12B_OUT1 = 0x0B,
    _2L_900PIN_PIN_AA25_TEST12B_OUT2 = 0x0C,
    _2L_900PIN_PIN_AA25_TEST12B_OUT3 = 0x0D,
    _2L_900PIN_PIN_AA25_TEST12B_OUT4 = 0x0E,
    _2L_900PIN_PIN_AA25_TEST12B_OUT5 = 0x0F,
    _2L_900PIN_PIN_AA25_TEST12B_OUT6 = 0x10,
    _2L_900PIN_PIN_AA25_TEST12B_OUT7 = 0x11,
    _2L_900PIN_PIN_AA25_TEST12B_OUT8 = 0x12,
    _2L_900PIN_PIN_AA25_TEST12B_OUT9 = 0x13,
    _2L_900PIN_PIN_AA25_TEST12B_OUT10 = 0x14,
    _2L_900PIN_PIN_AA25_TEST12B_OUT11 = 0x15,
    _2L_900PIN_PIN_AA25_NC = _2L_900PIN_PIN_AA25_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AA25;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1033 at _OFF_Region
// MCU Ctrl : 0xFE33 at _2L_900PIN_PIN_AA26_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AA26_OFF_REGION          (_2L_900PIN_PIN_AA26_NC)

typedef enum
{
    _2L_900PIN_PIN_AA26_GPI = 0x00,
    _2L_900PIN_PIN_AA26_GPO_PP = 0x01,
    _2L_900PIN_PIN_AA26_GPO_OD = 0x02,
    _2L_900PIN_PIN_AA26_EDPTX_HPD_ORG_0 = 0x03,
    _2L_900PIN_PIN_AA26_VB1_HTPD_N_0_0 = 0x04,
    _2L_900PIN_PIN_AA26_TEST12B_OUT0 = 0x05,
    _2L_900PIN_PIN_AA26_TEST12B_OUT1 = 0x06,
    _2L_900PIN_PIN_AA26_TEST12B_OUT2 = 0x07,
    _2L_900PIN_PIN_AA26_TEST12B_OUT3 = 0x08,
    _2L_900PIN_PIN_AA26_TEST12B_OUT4 = 0x09,
    _2L_900PIN_PIN_AA26_TEST12B_OUT5 = 0x0A,
    _2L_900PIN_PIN_AA26_TEST12B_OUT6 = 0x0B,
    _2L_900PIN_PIN_AA26_TEST12B_OUT7 = 0x0C,
    _2L_900PIN_PIN_AA26_TEST12B_OUT8 = 0x0D,
    _2L_900PIN_PIN_AA26_TEST12B_OUT9 = 0x0E,
    _2L_900PIN_PIN_AA26_TEST12B_OUT10 = 0x0F,
    _2L_900PIN_PIN_AA26_TEST12B_OUT11 = 0x10,
    _2L_900PIN_PIN_AA26_NC = _2L_900PIN_PIN_AA26_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AA26;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1034 at _OFF_Region
// MCU Ctrl : 0xFE34 at _2L_900PIN_PIN_Y26_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_Y26_OFF_REGION           (_2L_900PIN_PIN_Y26_NC)

typedef enum
{
    _2L_900PIN_PIN_Y26_GPI = 0x00,
    _2L_900PIN_PIN_Y26_GPO_PP = 0x01,
    _2L_900PIN_PIN_Y26_GPO_OD = 0x02,
    _2L_900PIN_PIN_Y26_EDPTX_HPD_ORG_1 = 0x03,
    _2L_900PIN_PIN_Y26_VB1_PLL_LOCK_N_0_0 = 0x04,
    _2L_900PIN_PIN_Y26_TEST12B_OUT0 = 0x05,
    _2L_900PIN_PIN_Y26_TEST12B_OUT1 = 0x06,
    _2L_900PIN_PIN_Y26_TEST12B_OUT2 = 0x07,
    _2L_900PIN_PIN_Y26_TEST12B_OUT3 = 0x08,
    _2L_900PIN_PIN_Y26_TEST12B_OUT4 = 0x09,
    _2L_900PIN_PIN_Y26_TEST12B_OUT5 = 0x0A,
    _2L_900PIN_PIN_Y26_TEST12B_OUT6 = 0x0B,
    _2L_900PIN_PIN_Y26_TEST12B_OUT7 = 0x0C,
    _2L_900PIN_PIN_Y26_TEST12B_OUT8 = 0x0D,
    _2L_900PIN_PIN_Y26_TEST12B_OUT9 = 0x0E,
    _2L_900PIN_PIN_Y26_TEST12B_OUT10 = 0x0F,
    _2L_900PIN_PIN_Y26_TEST12B_OUT11 = 0x10,
    _2L_900PIN_PIN_Y26_NC = _2L_900PIN_PIN_Y26_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_Y26;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1035 at _OFF_Region
// MCU Ctrl : 0xFE35 at _2L_900PIN_2L_900PIN_PIN_R28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_R28_OFF_REGION           (_2L_900PIN_PIN_R28_NC)

typedef enum
{
    _2L_900PIN_PIN_R28_HI_Z = 0x00,
    _2L_900PIN_PIN_R28_GPI = 0x01,
    _2L_900PIN_PIN_R28_TXD4P_10B = 0x04,
    _2L_900PIN_PIN_R28_NC = _2L_900PIN_PIN_R28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_R28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1036 at _OFF_Region
// MCU Ctrl : 0xFE36 at _2L_900PIN_2L_900PIN_PIN_R30_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_R30_OFF_REGION           (_2L_900PIN_PIN_R30_NC)

typedef enum
{
    _2L_900PIN_PIN_R30_HI_Z = 0x00,
    _2L_900PIN_PIN_R30_GPI = 0x01,
    _2L_900PIN_PIN_R30_TXD4N_10B = 0x04,
    _2L_900PIN_PIN_R30_NC = _2L_900PIN_PIN_R30_GPI,
} EnumPinshareInfo2L_900PIN_PIN_R30;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1037 at _OFF_Region
// MCU Ctrl : 0xFE37 at _2L_900PIN_2L_900PIN_PIN_R29_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_R29_OFF_REGION           (_2L_900PIN_PIN_R29_NC)

typedef enum
{
    _2L_900PIN_PIN_R29_HI_Z = 0x00,
    _2L_900PIN_PIN_R29_GPI = 0x01,
    _2L_900PIN_PIN_R29_TXD3P_10B = 0x04,
    _2L_900PIN_PIN_R29_NC = _2L_900PIN_PIN_R29_GPI,
} EnumPinshareInfo2L_900PIN_PIN_R29;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1038 at _OFF_Region
// MCU Ctrl : 0xFE38 at _2L_900PIN_2L_900PIN_PIN_P28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_P28_OFF_REGION           (_2L_900PIN_PIN_P28_NC)

typedef enum
{
    _2L_900PIN_PIN_P28_HI_Z = 0x00,
    _2L_900PIN_PIN_P28_GPI = 0x01,
    _2L_900PIN_PIN_P28_TXD3N_10B = 0x04,
    _2L_900PIN_PIN_P28_NC = _2L_900PIN_PIN_P28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_P28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1039 at _OFF_Region
// MCU Ctrl : 0xFE39 at _2L_900PIN_2L_900PIN_PIN_P29_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_P29_OFF_REGION           (_2L_900PIN_PIN_P29_NC)

typedef enum
{
    _2L_900PIN_PIN_P29_HI_Z = 0x00,
    _2L_900PIN_PIN_P29_GPI = 0x01,
    _2L_900PIN_PIN_P29_TXD2P_10B = 0x04,
    _2L_900PIN_PIN_P29_NC = _2L_900PIN_PIN_P29_GPI,
} EnumPinshareInfo2L_900PIN_PIN_P29;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x103A at _OFF_Region
// MCU Ctrl : 0xFE3A at _2L_900PIN_2L_900PIN_PIN_N29_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_N29_OFF_REGION           (_2L_900PIN_PIN_N29_NC)

typedef enum
{
    _2L_900PIN_PIN_N29_HI_Z = 0x00,
    _2L_900PIN_PIN_N29_GPI = 0x01,
    _2L_900PIN_PIN_N29_TXD2N_10B = 0x04,
    _2L_900PIN_PIN_N29_NC = _2L_900PIN_PIN_N29_GPI,
} EnumPinshareInfo2L_900PIN_PIN_N29;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x103B at _OFF_Region
// MCU Ctrl : 0xFE3B at _2L_900PIN_2L_900PIN_PIN_N30_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_N30_OFF_REGION           (_2L_900PIN_PIN_N30_NC)

typedef enum
{
    _2L_900PIN_PIN_N30_HI_Z = 0x00,
    _2L_900PIN_PIN_N30_GPI = 0x01,
    _2L_900PIN_PIN_N30_TXD1P_10B = 0x04,
    _2L_900PIN_PIN_N30_NC = _2L_900PIN_PIN_N30_GPI,
} EnumPinshareInfo2L_900PIN_PIN_N30;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x103C at _OFF_Region
// MCU Ctrl : 0xFE3C at _2L_900PIN_2L_900PIN_PIN_N28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_N28_OFF_REGION           (_2L_900PIN_PIN_N28_NC)

typedef enum
{
    _2L_900PIN_PIN_N28_HI_Z = 0x00,
    _2L_900PIN_PIN_N28_GPI = 0x01,
    _2L_900PIN_PIN_N28_TXD1N_10B = 0x04,
    _2L_900PIN_PIN_N28_NC = _2L_900PIN_PIN_N28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_N28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x103D at _OFF_Region
// MCU Ctrl : 0xFE3D at _2L_900PIN_2L_900PIN_PIN_L28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_L28_OFF_REGION           (_2L_900PIN_PIN_L28_NC)

typedef enum
{
    _2L_900PIN_PIN_L28_HI_Z = 0x00,
    _2L_900PIN_PIN_L28_GPI = 0x01,
    _2L_900PIN_PIN_L28_TXD0P_10B = 0x04,
    _2L_900PIN_PIN_L28_NC = _2L_900PIN_PIN_L28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_L28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x103E at _OFF_Region
// MCU Ctrl : 0xFE3E at _2L_900PIN_2L_900PIN_PIN_L30_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_L30_OFF_REGION           (_2L_900PIN_PIN_L30_NC)

typedef enum
{
    _2L_900PIN_PIN_L30_HI_Z = 0x00,
    _2L_900PIN_PIN_L30_GPI = 0x01,
    _2L_900PIN_PIN_L30_TXD0N_10B = 0x04,
    _2L_900PIN_PIN_L30_NC = _2L_900PIN_PIN_L30_GPI,
} EnumPinshareInfo2L_900PIN_PIN_L30;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x103F at _OFF_Region
// MCU Ctrl : 0xFE3F at _2L_900PIN_2L_900PIN_PIN_L29_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_L29_OFF_REGION           (_2L_900PIN_PIN_L29_NC)

typedef enum
{
    _2L_900PIN_PIN_L29_HI_Z = 0x00,
    _2L_900PIN_PIN_L29_GPI = 0x01,
    _2L_900PIN_PIN_L29_TXC4P_10B = 0x04,
    _2L_900PIN_PIN_L29_NC = _2L_900PIN_PIN_L29_GPI,
} EnumPinshareInfo2L_900PIN_PIN_L29;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1040 at _OFF_Region
// MCU Ctrl : 0xFE40 at _2L_900PIN_2L_900PIN_PIN_K28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_K28_OFF_REGION           (_2L_900PIN_PIN_K28_NC)

typedef enum
{
    _2L_900PIN_PIN_K28_HI_Z = 0x00,
    _2L_900PIN_PIN_K28_GPI = 0x01,
    _2L_900PIN_PIN_K28_TXC4N_10B = 0x04,
    _2L_900PIN_PIN_K28_NC = _2L_900PIN_PIN_K28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_K28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1041 at _OFF_Region
// MCU Ctrl : 0xFE41 at _2L_900PIN_2L_900PIN_PIN_K29_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_K29_OFF_REGION           (_2L_900PIN_PIN_K29_NC)

typedef enum
{
    _2L_900PIN_PIN_K29_HI_Z = 0x00,
    _2L_900PIN_PIN_K29_GPI = 0x01,
    _2L_900PIN_PIN_K29_TXC3P_10B = 0x04,
    _2L_900PIN_PIN_K29_NC = _2L_900PIN_PIN_K29_GPI,
} EnumPinshareInfo2L_900PIN_PIN_K29;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1042 at _OFF_Region
// MCU Ctrl : 0xFE42 at _2L_900PIN_2L_900PIN_PIN_J29_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_J29_OFF_REGION           (_2L_900PIN_PIN_J29_NC)

typedef enum
{
    _2L_900PIN_PIN_J29_HI_Z = 0x00,
    _2L_900PIN_PIN_J29_GPI = 0x01,
    _2L_900PIN_PIN_J29_TXC3N_10B = 0x04,
    _2L_900PIN_PIN_J29_NC = _2L_900PIN_PIN_J29_GPI,
} EnumPinshareInfo2L_900PIN_PIN_J29;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1043 at _OFF_Region
// MCU Ctrl : 0xFE43 at _2L_900PIN_2L_900PIN_PIN_J30_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_J30_OFF_REGION           (_2L_900PIN_PIN_J30_NC)

typedef enum
{
    _2L_900PIN_PIN_J30_HI_Z = 0x00,
    _2L_900PIN_PIN_J30_GPI = 0x01,
    _2L_900PIN_PIN_J30_TXCCP_10B = 0x04,
    _2L_900PIN_PIN_J30_NC = _2L_900PIN_PIN_J30_GPI,
} EnumPinshareInfo2L_900PIN_PIN_J30;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1044 at _OFF_Region
// MCU Ctrl : 0xFE44 at _2L_900PIN_2L_900PIN_PIN_J28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_J28_OFF_REGION           (_2L_900PIN_PIN_J28_NC)

typedef enum
{
    _2L_900PIN_PIN_J28_HI_Z = 0x00,
    _2L_900PIN_PIN_J28_GPI = 0x01,
    _2L_900PIN_PIN_J28_TXCCN_10B = 0x04,
    _2L_900PIN_PIN_J28_NC = _2L_900PIN_PIN_J28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_J28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1045 at _OFF_Region
// MCU Ctrl : 0xFE45 at _2L_900PIN_2L_900PIN_PIN_G28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_G28_OFF_REGION           (_2L_900PIN_PIN_G28_NC)

typedef enum
{
    _2L_900PIN_PIN_G28_HI_Z = 0x00,
    _2L_900PIN_PIN_G28_GPI = 0x01,
    _2L_900PIN_PIN_G28_TXC2P_10B = 0x04,
    _2L_900PIN_PIN_G28_NC = _2L_900PIN_PIN_G28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_G28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1046 at _OFF_Region
// MCU Ctrl : 0xFE46 at _2L_900PIN_2L_900PIN_PIN_G30_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_G30_OFF_REGION           (_2L_900PIN_PIN_G30_NC)

typedef enum
{
    _2L_900PIN_PIN_G30_HI_Z = 0x00,
    _2L_900PIN_PIN_G30_GPI = 0x01,
    _2L_900PIN_PIN_G30_TXC2N_10B = 0x04,
    _2L_900PIN_PIN_G30_NC = _2L_900PIN_PIN_G30_GPI,
} EnumPinshareInfo2L_900PIN_PIN_G30;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1047 at _OFF_Region
// MCU Ctrl : 0xFE47 at _2L_900PIN_2L_900PIN_PIN_G29_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_G29_OFF_REGION           (_2L_900PIN_PIN_G29_NC)

typedef enum
{
    _2L_900PIN_PIN_G29_HI_Z = 0x00,
    _2L_900PIN_PIN_G29_GPI = 0x01,
    _2L_900PIN_PIN_G29_TXC1P_10B = 0x04,
    _2L_900PIN_PIN_G29_NC = _2L_900PIN_PIN_G29_GPI,
} EnumPinshareInfo2L_900PIN_PIN_G29;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1048 at _OFF_Region
// MCU Ctrl : 0xFE48 at _2L_900PIN_2L_900PIN_PIN_F28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_F28_OFF_REGION           (_2L_900PIN_PIN_F28_NC)

typedef enum
{
    _2L_900PIN_PIN_F28_HI_Z = 0x00,
    _2L_900PIN_PIN_F28_GPI = 0x01,
    _2L_900PIN_PIN_F28_TXC1N_10B = 0x04,
    _2L_900PIN_PIN_F28_NC = _2L_900PIN_PIN_F28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_F28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1049 at _OFF_Region
// MCU Ctrl : 0xFE49 at _2L_900PIN_2L_900PIN_PIN_F29_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_F29_OFF_REGION           (_2L_900PIN_PIN_F29_NC)

typedef enum
{
    _2L_900PIN_PIN_F29_HI_Z = 0x00,
    _2L_900PIN_PIN_F29_GPI = 0x01,
    _2L_900PIN_PIN_F29_TXC0P_10B = 0x04,
    _2L_900PIN_PIN_F29_NC = _2L_900PIN_PIN_F29_GPI,
} EnumPinshareInfo2L_900PIN_PIN_F29;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x104A at _OFF_Region
// MCU Ctrl : 0xFE4A at _2L_900PIN_2L_900PIN_PIN_E29_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_E29_OFF_REGION           (_2L_900PIN_PIN_E29_NC)

typedef enum
{
    _2L_900PIN_PIN_E29_HI_Z = 0x00,
    _2L_900PIN_PIN_E29_GPI = 0x01,
    _2L_900PIN_PIN_E29_TXC0N_10B = 0x04,
    _2L_900PIN_PIN_E29_NC = _2L_900PIN_PIN_E29_GPI,
} EnumPinshareInfo2L_900PIN_PIN_E29;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x104B at _OFF_Region
// MCU Ctrl : 0xFE4B at _2L_900PIN_2L_900PIN_PIN_E30_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_E30_OFF_REGION           (_2L_900PIN_PIN_E30_NC)

typedef enum
{
    _2L_900PIN_PIN_E30_HI_Z = 0x00,
    _2L_900PIN_PIN_E30_GPI = 0x01,
    _2L_900PIN_PIN_E30_TXB4P_10B = 0x04,
    _2L_900PIN_PIN_E30_NC = _2L_900PIN_PIN_E30_GPI,
} EnumPinshareInfo2L_900PIN_PIN_E30;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x104C at _OFF_Region
// MCU Ctrl : 0xFE4C at _2L_900PIN_2L_900PIN_PIN_E28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_E28_OFF_REGION           (_2L_900PIN_PIN_E28_NC)

typedef enum
{
    _2L_900PIN_PIN_E28_HI_Z = 0x00,
    _2L_900PIN_PIN_E28_GPI = 0x01,
    _2L_900PIN_PIN_E28_TXB4N_10B = 0x04,
    _2L_900PIN_PIN_E28_NC = _2L_900PIN_PIN_E28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_E28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x104D at _OFF_Region
// MCU Ctrl : 0xFE4D at _2L_900PIN_2L_900PIN_PIN_C28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_C28_OFF_REGION           (_2L_900PIN_PIN_C28_NC)

typedef enum
{
    _2L_900PIN_PIN_C28_HI_Z = 0x00,
    _2L_900PIN_PIN_C28_GPI = 0x01,
    _2L_900PIN_PIN_C28_TXB3P_10B = 0x04,
    _2L_900PIN_PIN_C28_NC = _2L_900PIN_PIN_C28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_C28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x104E at _OFF_Region
// MCU Ctrl : 0xFE4E at _2L_900PIN_2L_900PIN_PIN_A28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_A28_OFF_REGION           (_2L_900PIN_PIN_A28_NC)

typedef enum
{
    _2L_900PIN_PIN_A28_HI_Z = 0x00,
    _2L_900PIN_PIN_A28_GPI = 0x01,
    _2L_900PIN_PIN_A28_TXB3N_10B = 0x04,
    _2L_900PIN_PIN_A28_NC = _2L_900PIN_PIN_A28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_A28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x104F at _OFF_Region
// MCU Ctrl : 0xFE4F at _2L_900PIN_2L_900PIN_PIN_B28_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B28_OFF_REGION           (_2L_900PIN_PIN_B28_NC)

typedef enum
{
    _2L_900PIN_PIN_B28_HI_Z = 0x00,
    _2L_900PIN_PIN_B28_GPI = 0x01,
    _2L_900PIN_PIN_B28_TXB2P_10B = 0x04,
    _2L_900PIN_PIN_B28_NC = _2L_900PIN_PIN_B28_GPI,
} EnumPinshareInfo2L_900PIN_PIN_B28;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1050 at _OFF_Region
// MCU Ctrl : 0xFE50 at _2L_900PIN_2L_900PIN_PIN_C27_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_C27_OFF_REGION           (_2L_900PIN_PIN_C27_NC)

typedef enum
{
    _2L_900PIN_PIN_C27_HI_Z = 0x00,
    _2L_900PIN_PIN_C27_GPI = 0x01,
    _2L_900PIN_PIN_C27_TXB2N_10B = 0x04,
    _2L_900PIN_PIN_C27_NC = _2L_900PIN_PIN_C27_GPI,
} EnumPinshareInfo2L_900PIN_PIN_C27;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1051 at _OFF_Region
// MCU Ctrl : 0xFE51 at _2L_900PIN_2L_900PIN_PIN_B27_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B27_OFF_REGION           (_2L_900PIN_PIN_B27_NC)

typedef enum
{
    _2L_900PIN_PIN_B27_HI_Z = 0x00,
    _2L_900PIN_PIN_B27_GPI = 0x01,
    _2L_900PIN_PIN_B27_TXB1P_10B = 0x04,
    _2L_900PIN_PIN_B27_NC = _2L_900PIN_PIN_B27_GPI,
} EnumPinshareInfo2L_900PIN_PIN_B27;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1052 at _OFF_Region
// MCU Ctrl : 0xFE52 at _2L_900PIN_2L_900PIN_PIN_B26_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B26_OFF_REGION           (_2L_900PIN_PIN_B26_NC)

typedef enum
{
    _2L_900PIN_PIN_B26_HI_Z = 0x00,
    _2L_900PIN_PIN_B26_GPI = 0x01,
    _2L_900PIN_PIN_B26_TXB1N_10B = 0x04,
    _2L_900PIN_PIN_B26_NC = _2L_900PIN_PIN_B26_GPI,
} EnumPinshareInfo2L_900PIN_PIN_B26;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1053 at _OFF_Region
// MCU Ctrl : 0xFE53 at _2L_900PIN_2L_900PIN_PIN_A26_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_A26_OFF_REGION           (_2L_900PIN_PIN_A26_NC)

typedef enum
{
    _2L_900PIN_PIN_A26_HI_Z = 0x00,
    _2L_900PIN_PIN_A26_GPI = 0x01,
    _2L_900PIN_PIN_A26_TXB0P_10B = 0x04,
    _2L_900PIN_PIN_A26_NC = _2L_900PIN_PIN_A26_GPI,
} EnumPinshareInfo2L_900PIN_PIN_A26;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1054 at _OFF_Region
// MCU Ctrl : 0xFE54 at _2L_900PIN_2L_900PIN_PIN_C26_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_C26_OFF_REGION           (_2L_900PIN_PIN_C26_NC)

typedef enum
{
    _2L_900PIN_PIN_C26_HI_Z = 0x00,
    _2L_900PIN_PIN_C26_GPI = 0x01,
    _2L_900PIN_PIN_C26_TXB0N_10B = 0x04,
    _2L_900PIN_PIN_C26_NC = _2L_900PIN_PIN_C26_GPI,
} EnumPinshareInfo2L_900PIN_PIN_C26;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1055 at _OFF_Region
// MCU Ctrl : 0xFE55 at _2L_900PIN_2L_900PIN_PIN_C24_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_C24_OFF_REGION           (_2L_900PIN_PIN_C24_NC)

typedef enum
{
    _2L_900PIN_PIN_C24_HI_Z = 0x00,
    _2L_900PIN_PIN_C24_GPI = 0x01,
    _2L_900PIN_PIN_C24_TXA4P_10B = 0x04,
    _2L_900PIN_PIN_C24_NC = _2L_900PIN_PIN_C24_GPI,
} EnumPinshareInfo2L_900PIN_PIN_C24;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1056 at _OFF_Region
// MCU Ctrl : 0xFE56 at _2L_900PIN_2L_900PIN_PIN_A24_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_A24_OFF_REGION           (_2L_900PIN_PIN_A24_NC)

typedef enum
{
    _2L_900PIN_PIN_A24_HI_Z = 0x00,
    _2L_900PIN_PIN_A24_GPI = 0x01,
    _2L_900PIN_PIN_A24_TXA4N_10B = 0x04,
    _2L_900PIN_PIN_A24_NC = _2L_900PIN_PIN_A24_GPI,
} EnumPinshareInfo2L_900PIN_PIN_A24;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1057 at _OFF_Region
// MCU Ctrl : 0xFE57 at _2L_900PIN_2L_900PIN_PIN_B24_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B24_OFF_REGION           (_2L_900PIN_PIN_B24_NC)

typedef enum
{
    _2L_900PIN_PIN_B24_HI_Z = 0x00,
    _2L_900PIN_PIN_B24_GPI = 0x01,
    _2L_900PIN_PIN_B24_TXA3P_10B = 0x04,
    _2L_900PIN_PIN_B24_NC = _2L_900PIN_PIN_B24_GPI,
} EnumPinshareInfo2L_900PIN_PIN_B24;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1058 at _OFF_Region
// MCU Ctrl : 0xFE58 at _2L_900PIN_2L_900PIN_PIN_C23_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_C23_OFF_REGION           (_2L_900PIN_PIN_C23_NC)

typedef enum
{
    _2L_900PIN_PIN_C23_HI_Z = 0x00,
    _2L_900PIN_PIN_C23_GPI = 0x01,
    _2L_900PIN_PIN_C23_TXA3N_10B = 0x04,
    _2L_900PIN_PIN_C23_NC = _2L_900PIN_PIN_C23_GPI,
} EnumPinshareInfo2L_900PIN_PIN_C23;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1059 at _OFF_Region
// MCU Ctrl : 0xFE59 at _2L_900PIN_2L_900PIN_PIN_B23_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B23_OFF_REGION           (_2L_900PIN_PIN_B23_NC)

typedef enum
{
    _2L_900PIN_PIN_B23_HI_Z = 0x00,
    _2L_900PIN_PIN_B23_GPI = 0x01,
    _2L_900PIN_PIN_B23_TXACP_10B = 0x04,
    _2L_900PIN_PIN_B23_NC = _2L_900PIN_PIN_B23_GPI,
} EnumPinshareInfo2L_900PIN_PIN_B23;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x105A at _OFF_Region
// MCU Ctrl : 0xFE5A at _2L_900PIN_2L_900PIN_PIN_B22_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B22_OFF_REGION           (_2L_900PIN_PIN_B22_NC)

typedef enum
{
    _2L_900PIN_PIN_B22_HI_Z = 0x00,
    _2L_900PIN_PIN_B22_GPI = 0x01,
    _2L_900PIN_PIN_B22_TXACN_10B = 0x04,
    _2L_900PIN_PIN_B22_NC = _2L_900PIN_PIN_B22_GPI,
} EnumPinshareInfo2L_900PIN_PIN_B22;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x105B at _OFF_Region
// MCU Ctrl : 0xFE5B at _2L_900PIN_2L_900PIN_PIN_A22_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_A22_OFF_REGION           (_2L_900PIN_PIN_A22_NC)

typedef enum
{
    _2L_900PIN_PIN_A22_HI_Z = 0x00,
    _2L_900PIN_PIN_A22_GPI = 0x01,
    _2L_900PIN_PIN_A22_TXA2P_10B = 0x04,
    _2L_900PIN_PIN_A22_NC = _2L_900PIN_PIN_A22_GPI,
} EnumPinshareInfo2L_900PIN_PIN_A22;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x105C at _OFF_Region
// MCU Ctrl : 0xFE5C at _2L_900PIN_2L_900PIN_PIN_C22_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_C22_OFF_REGION           (_2L_900PIN_PIN_C22_NC)

typedef enum
{
    _2L_900PIN_PIN_C22_HI_Z = 0x00,
    _2L_900PIN_PIN_C22_GPI = 0x01,
    _2L_900PIN_PIN_C22_TXA2N_10B = 0x04,
    _2L_900PIN_PIN_C22_NC = _2L_900PIN_PIN_C22_GPI,
} EnumPinshareInfo2L_900PIN_PIN_C22;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x105D at _OFF_Region
// MCU Ctrl : 0xFE5D at _2L_900PIN_2L_900PIN_PIN_B20_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B20_OFF_REGION           (_2L_900PIN_PIN_B20_NC)

typedef enum
{
    _2L_900PIN_PIN_B20_HI_Z = 0x00,
    _2L_900PIN_PIN_B20_GPI = 0x01,
    _2L_900PIN_PIN_B20_TXA1P_10B = 0x04,
    _2L_900PIN_PIN_B20_NC = _2L_900PIN_PIN_B20_GPI,
} EnumPinshareInfo2L_900PIN_PIN_B20;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x105E at _OFF_Region
// MCU Ctrl : 0xFE5E at _2L_900PIN_2L_900PIN_PIN_A20_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_A20_OFF_REGION           (_2L_900PIN_PIN_A20_NC)

typedef enum
{
    _2L_900PIN_PIN_A20_HI_Z = 0x00,
    _2L_900PIN_PIN_A20_GPI = 0x01,
    _2L_900PIN_PIN_A20_TXA1N_10B = 0x04,
    _2L_900PIN_PIN_A20_NC = _2L_900PIN_PIN_A20_GPI,
} EnumPinshareInfo2L_900PIN_PIN_A20;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x105F at _OFF_Region
// MCU Ctrl : 0xFE5F at _2L_900PIN_2L_900PIN_PIN_B19_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B19_OFF_REGION           (_2L_900PIN_PIN_B19_NC)

typedef enum
{
    _2L_900PIN_PIN_B19_HI_Z = 0x00,
    _2L_900PIN_PIN_B19_GPI = 0x01,
    _2L_900PIN_PIN_B19_TXA0P_10B = 0x04,
    _2L_900PIN_PIN_B19_NC = _2L_900PIN_PIN_B19_GPI,
} EnumPinshareInfo2L_900PIN_PIN_B19;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1060 at _OFF_Region
// MCU Ctrl : 0x2200 at _2L_900PIN_2L_900PIN_PIN_A19_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_A19_OFF_REGION           (_2L_900PIN_PIN_A19_NC)

typedef enum
{
    _2L_900PIN_PIN_A19_HI_Z = 0x00,
    _2L_900PIN_PIN_A19_GPI = 0x01,
    _2L_900PIN_PIN_A19_TXA0N_10B = 0x04,
    _2L_900PIN_PIN_A19_NC = _2L_900PIN_PIN_A19_GPI,
} EnumPinshareInfo2L_900PIN_PIN_A19;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1061
// MCU Ctrl : 0x2201 at _2L_900PIN_PIN_K11_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_K11                      (_2L_900PIN_PIN_K11_NC)

typedef enum
{
    _2L_900PIN_PIN_K11_GPI = 0x00,
    _2L_900PIN_PIN_K11_GPO_PP = 0x01,
    _2L_900PIN_PIN_K11_GPO_OD = 0x02,
    _2L_900PIN_PIN_K11_PWM5_PP = 0x03,
    _2L_900PIN_PIN_K11_PWM5_OD = 0x04,
    _2L_900PIN_PIN_K11_PWM5_DIMMING_PP = 0x05,
    _2L_900PIN_PIN_K11_PWM5_DIMMING = 0x06,
    _2L_900PIN_PIN_K11_TCON7 = 0x07,
    _2L_900PIN_PIN_K11_DCLK = 0x08,
    _2L_900PIN_PIN_K11_TTS_SCLK = 0x09,
    _2L_900PIN_PIN_K11_TEST12B_OUT0 = 0x0A,
    _2L_900PIN_PIN_K11_TEST12B_OUT1 = 0x0B,
    _2L_900PIN_PIN_K11_TEST12B_OUT2 = 0x0C,
    _2L_900PIN_PIN_K11_TEST12B_OUT3 = 0x0D,
    _2L_900PIN_PIN_K11_TEST12B_OUT4 = 0x0E,
    _2L_900PIN_PIN_K11_TEST12B_OUT5 = 0x0F,
    _2L_900PIN_PIN_K11_TEST12B_OUT6 = 0x10,
    _2L_900PIN_PIN_K11_TEST12B_OUT7 = 0x11,
    _2L_900PIN_PIN_K11_TEST12B_OUT8 = 0x12,
    _2L_900PIN_PIN_K11_TEST12B_OUT9 = 0x13,
    _2L_900PIN_PIN_K11_TEST12B_OUT10 = 0x14,
    _2L_900PIN_PIN_K11_TEST12B_OUT11 = 0x15,
    _2L_900PIN_PIN_K11_NC = _2L_900PIN_PIN_K11_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_K11;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1062
// MCU Ctrl : 0x2202 at _2L_900PIN_PIN_H11_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_H11                      (_2L_900PIN_PIN_H11_NC)

typedef enum
{
    _2L_900PIN_PIN_H11_GPI = 0x00,
    _2L_900PIN_PIN_H11_GPO_PP = 0x01,
    _2L_900PIN_PIN_H11_GPO_OD = 0x02,
    _2L_900PIN_PIN_H11_TCON10 = 0x03,
    _2L_900PIN_PIN_H11_TTL_DEN = 0x04,
    _2L_900PIN_PIN_H11_TTS_CEB = 0x05,
    _2L_900PIN_PIN_H11_TEST12B_OUT0 = 0x06,
    _2L_900PIN_PIN_H11_TEST12B_OUT1 = 0x07,
    _2L_900PIN_PIN_H11_TEST12B_OUT2 = 0x08,
    _2L_900PIN_PIN_H11_TEST12B_OUT3 = 0x09,
    _2L_900PIN_PIN_H11_TEST12B_OUT4 = 0x0A,
    _2L_900PIN_PIN_H11_TEST12B_OUT5 = 0x0B,
    _2L_900PIN_PIN_H11_TEST12B_OUT6 = 0x0C,
    _2L_900PIN_PIN_H11_TEST12B_OUT7 = 0x0D,
    _2L_900PIN_PIN_H11_TEST12B_OUT8 = 0x0E,
    _2L_900PIN_PIN_H11_TEST12B_OUT9 = 0x0F,
    _2L_900PIN_PIN_H11_TEST12B_OUT10 = 0x10,
    _2L_900PIN_PIN_H11_TEST12B_OUT11 = 0x11,
    _2L_900PIN_PIN_H11_NC = _2L_900PIN_PIN_H11_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_H11;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1063
// MCU Ctrl : 0x2203 at _2L_900PIN_PIN_H10_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_H10                      (_2L_900PIN_PIN_H10_NC)

typedef enum
{
    _2L_900PIN_PIN_H10_GPI = 0x00,
    _2L_900PIN_PIN_H10_GPO_PP = 0x01,
    _2L_900PIN_PIN_H10_GPO_OD = 0x02,
    _2L_900PIN_PIN_H10_PWM_IN_0_1 = 0x03,
    _2L_900PIN_PIN_H10_TTL_DHS = 0x04,
    _2L_900PIN_PIN_H10_TCON12 = 0x05,
    _2L_900PIN_PIN_H10_TYPEC_GPIO4_0_PP = 0x06,
    _2L_900PIN_PIN_H10_TYPEC_GPIO4_0_OD = 0x07,
    _2L_900PIN_PIN_H10_TYPEC_GPIO5_0_PP = 0x08,
    _2L_900PIN_PIN_H10_TYPEC_GPIO5_0_OD = 0x09,
    _2L_900PIN_PIN_H10_TTS_SI = 0x0A,
    _2L_900PIN_PIN_H10_TEST12B_OUT0 = 0x0B,
    _2L_900PIN_PIN_H10_TEST12B_OUT1 = 0x0C,
    _2L_900PIN_PIN_H10_TEST12B_OUT2 = 0x0D,
    _2L_900PIN_PIN_H10_TEST12B_OUT3 = 0x0E,
    _2L_900PIN_PIN_H10_TEST12B_OUT4 = 0x0F,
    _2L_900PIN_PIN_H10_TEST12B_OUT5 = 0x10,
    _2L_900PIN_PIN_H10_TEST12B_OUT6 = 0x11,
    _2L_900PIN_PIN_H10_TEST12B_OUT7 = 0x12,
    _2L_900PIN_PIN_H10_TEST12B_OUT8 = 0x13,
    _2L_900PIN_PIN_H10_TEST12B_OUT9 = 0x14,
    _2L_900PIN_PIN_H10_TEST12B_OUT10 = 0x15,
    _2L_900PIN_PIN_H10_TEST12B_OUT11 = 0x16,
    _2L_900PIN_PIN_H10_NC = _2L_900PIN_PIN_H10_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_H10;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1064
// MCU Ctrl : 0x2204 at _2L_900PIN_PIN_J11_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_J11                      (_2L_900PIN_PIN_J11_NC)

typedef enum
{
    _2L_900PIN_PIN_J11_GPI = 0x00,
    _2L_900PIN_PIN_J11_GPO_PP = 0x01,
    _2L_900PIN_PIN_J11_GPO_OD = 0x02,
    _2L_900PIN_PIN_J11_TCON11 = 0x03,
    _2L_900PIN_PIN_J11_TTL_DVS = 0x04,
    _2L_900PIN_PIN_J11_TTS_SO = 0x05,
    _2L_900PIN_PIN_J11_TEST12B_OUT0 = 0x06,
    _2L_900PIN_PIN_J11_TEST12B_OUT1 = 0x07,
    _2L_900PIN_PIN_J11_TEST12B_OUT2 = 0x08,
    _2L_900PIN_PIN_J11_TEST12B_OUT3 = 0x09,
    _2L_900PIN_PIN_J11_TEST12B_OUT4 = 0x0A,
    _2L_900PIN_PIN_J11_TEST12B_OUT5 = 0x0B,
    _2L_900PIN_PIN_J11_TEST12B_OUT6 = 0x0C,
    _2L_900PIN_PIN_J11_TEST12B_OUT7 = 0x0D,
    _2L_900PIN_PIN_J11_TEST12B_OUT8 = 0x0E,
    _2L_900PIN_PIN_J11_TEST12B_OUT9 = 0x0F,
    _2L_900PIN_PIN_J11_TEST12B_OUT10 = 0x10,
    _2L_900PIN_PIN_J11_TEST12B_OUT11 = 0x11,
    _2L_900PIN_PIN_J11_NC = _2L_900PIN_PIN_J11_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_J11;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1065
// MCU Ctrl : 0x2205 at _2L_900PIN_PIN_G9_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_G9                       (_2L_900PIN_PIN_G9_NC)

typedef enum
{
    _2L_900PIN_PIN_G9_GPI = 0x00,
    _2L_900PIN_PIN_G9_GPO_PP = 0x01,
    _2L_900PIN_PIN_G9_GPO_OD = 0x02,
    _2L_900PIN_PIN_G9_TPC_IICSCL_0_1 = 0x03,
    _2L_900PIN_PIN_G9_TPC_IICSCL_1_1 = 0x04,
    _2L_900PIN_PIN_G9_SWDIO_0_3 = 0x05,
    _2L_900PIN_PIN_G9_TEST12B_OUT0 = 0x06,
    _2L_900PIN_PIN_G9_TEST12B_OUT1 = 0x07,
    _2L_900PIN_PIN_G9_TEST12B_OUT2 = 0x08,
    _2L_900PIN_PIN_G9_TEST12B_OUT3 = 0x09,
    _2L_900PIN_PIN_G9_TEST12B_OUT4 = 0x0A,
    _2L_900PIN_PIN_G9_TEST12B_OUT5 = 0x0B,
    _2L_900PIN_PIN_G9_TEST12B_OUT6 = 0x0C,
    _2L_900PIN_PIN_G9_TEST12B_OUT7 = 0x0D,
    _2L_900PIN_PIN_G9_TEST12B_OUT8 = 0x0E,
    _2L_900PIN_PIN_G9_TEST12B_OUT9 = 0x0F,
    _2L_900PIN_PIN_G9_TEST12B_OUT10 = 0x10,
    _2L_900PIN_PIN_G9_TEST12B_OUT11 = 0x11,
    _2L_900PIN_PIN_G9_NC = _2L_900PIN_PIN_G9_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_G9;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1066
// MCU Ctrl : 0x2206 at _2L_900PIN_PIN_G8_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_G8                       (_2L_900PIN_PIN_G8_NC)

typedef enum
{
    _2L_900PIN_PIN_G8_GPI = 0x00,
    _2L_900PIN_PIN_G8_GPO_PP = 0x01,
    _2L_900PIN_PIN_G8_GPO_OD = 0x02,
    _2L_900PIN_PIN_G8_TPC_IICSDA_0_1 = 0x03,
    _2L_900PIN_PIN_G8_TPC_IICSDA_1_1 = 0x04,
    _2L_900PIN_PIN_G8_SWDCLK_0_3 = 0x05,
    _2L_900PIN_PIN_G8_TEST12B_OUT0 = 0x06,
    _2L_900PIN_PIN_G8_TEST12B_OUT1 = 0x07,
    _2L_900PIN_PIN_G8_TEST12B_OUT2 = 0x08,
    _2L_900PIN_PIN_G8_TEST12B_OUT3 = 0x09,
    _2L_900PIN_PIN_G8_TEST12B_OUT4 = 0x0A,
    _2L_900PIN_PIN_G8_TEST12B_OUT5 = 0x0B,
    _2L_900PIN_PIN_G8_TEST12B_OUT6 = 0x0C,
    _2L_900PIN_PIN_G8_TEST12B_OUT7 = 0x0D,
    _2L_900PIN_PIN_G8_TEST12B_OUT8 = 0x0E,
    _2L_900PIN_PIN_G8_TEST12B_OUT9 = 0x0F,
    _2L_900PIN_PIN_G8_TEST12B_OUT10 = 0x10,
    _2L_900PIN_PIN_G8_TEST12B_OUT11 = 0x11,
    _2L_900PIN_PIN_G8_NC = _2L_900PIN_PIN_G8_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_G8;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1067
// MCU Ctrl : 0x2207 at _2L_900PIN_PIN_G7_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_G7                       (_2L_900PIN_PIN_G7_NC)

typedef enum
{
    _2L_900PIN_PIN_G7_GPI = 0x00,
    _2L_900PIN_PIN_G7_GPO_PP = 0x01,
    _2L_900PIN_PIN_G7_GPO_OD = 0x02,
    _2L_900PIN_PIN_G7_EXT_UART_RX_0_3 = 0x03,
    _2L_900PIN_PIN_G7_EXT_UART_RX_1_3 = 0x04,
    _2L_900PIN_PIN_G7_EXT_UART_RX_2_3 = 0x05,
    _2L_900PIN_PIN_G7_M1_IDOMAIN_DEN_OUT = 0x06,
    _2L_900PIN_PIN_G7_TEST12B_OUT0 = 0x07,
    _2L_900PIN_PIN_G7_TEST12B_OUT1 = 0x08,
    _2L_900PIN_PIN_G7_TEST12B_OUT2 = 0x09,
    _2L_900PIN_PIN_G7_TEST12B_OUT3 = 0x0A,
    _2L_900PIN_PIN_G7_TEST12B_OUT4 = 0x0B,
    _2L_900PIN_PIN_G7_TEST12B_OUT5 = 0x0C,
    _2L_900PIN_PIN_G7_TEST12B_OUT6 = 0x0D,
    _2L_900PIN_PIN_G7_TEST12B_OUT7 = 0x0E,
    _2L_900PIN_PIN_G7_TEST12B_OUT8 = 0x0F,
    _2L_900PIN_PIN_G7_TEST12B_OUT9 = 0x10,
    _2L_900PIN_PIN_G7_TEST12B_OUT10 = 0x11,
    _2L_900PIN_PIN_G7_TEST12B_OUT11 = 0x12,
    _2L_900PIN_PIN_G7_NC = _2L_900PIN_PIN_G7_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_G7;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x106A
// MCU Ctrl : 0x220A at _2L_900PIN_PIN_E10_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_E10                      (_2L_900PIN_PIN_E10_NC)

typedef enum
{
    _2L_900PIN_PIN_E10_GPI = 0x00,
    _2L_900PIN_PIN_E10_GPO_PP = 0x01,
    _2L_900PIN_PIN_E10_GPO_OD = 0x02,
    _2L_900PIN_PIN_E10_DPRX_AUX_P_2 = 0x03,
    _2L_900PIN_PIN_E10_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_E10_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_E10_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_E10_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_E10_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_E10_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_E10_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_E10_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_E10_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_E10_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_E10_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_E10_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_E10_NC = _2L_900PIN_PIN_E10_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_E10;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x106B
// MCU Ctrl : 0x220B at _2L_900PIN_PIN_F10_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_F10                      (_2L_900PIN_PIN_F10_NC)

typedef enum
{
    _2L_900PIN_PIN_F10_GPI = 0x00,
    _2L_900PIN_PIN_F10_GPO_PP = 0x01,
    _2L_900PIN_PIN_F10_GPO_OD = 0x02,
    _2L_900PIN_PIN_F10_DPRX_AUX_N_2 = 0x03,
    _2L_900PIN_PIN_F10_TEST12B_OUT0 = 0x04,
    _2L_900PIN_PIN_F10_TEST12B_OUT1 = 0x05,
    _2L_900PIN_PIN_F10_TEST12B_OUT2 = 0x06,
    _2L_900PIN_PIN_F10_TEST12B_OUT3 = 0x07,
    _2L_900PIN_PIN_F10_TEST12B_OUT4 = 0x08,
    _2L_900PIN_PIN_F10_TEST12B_OUT5 = 0x09,
    _2L_900PIN_PIN_F10_TEST12B_OUT6 = 0x0A,
    _2L_900PIN_PIN_F10_TEST12B_OUT7 = 0x0B,
    _2L_900PIN_PIN_F10_TEST12B_OUT8 = 0x0C,
    _2L_900PIN_PIN_F10_TEST12B_OUT9 = 0x0D,
    _2L_900PIN_PIN_F10_TEST12B_OUT10 = 0x0E,
    _2L_900PIN_PIN_F10_TEST12B_OUT11 = 0x0F,
    _2L_900PIN_PIN_F10_NC = _2L_900PIN_PIN_F10_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_F10;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x106C
// MCU Ctrl : 0x220C at _2L_900PIN_PIN_F6_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_F6                       (_2L_900PIN_PIN_F6_NC)

typedef enum
{
    _2L_900PIN_PIN_F6_GPI = 0x00,
    _2L_900PIN_PIN_F6_GPO_PP = 0x01,
    _2L_900PIN_PIN_F6_GPO_OD = 0x02,
    _2L_900PIN_PIN_F6_PWM3_PP = 0x03,
    _2L_900PIN_PIN_F6_PWM3_OD = 0x04,
    _2L_900PIN_PIN_F6_PWM3_DIMMING_PP = 0x05,
    _2L_900PIN_PIN_F6_PWM3_DIMMING = 0x06,
    _2L_900PIN_PIN_F6_TCON9 = 0x07,
    _2L_900PIN_PIN_F6_TEST12B_OUT0 = 0x08,
    _2L_900PIN_PIN_F6_TEST12B_OUT1 = 0x09,
    _2L_900PIN_PIN_F6_TEST12B_OUT2 = 0x0A,
    _2L_900PIN_PIN_F6_TEST12B_OUT3 = 0x0B,
    _2L_900PIN_PIN_F6_TEST12B_OUT4 = 0x0C,
    _2L_900PIN_PIN_F6_TEST12B_OUT5 = 0x0D,
    _2L_900PIN_PIN_F6_TEST12B_OUT6 = 0x0E,
    _2L_900PIN_PIN_F6_TEST12B_OUT7 = 0x0F,
    _2L_900PIN_PIN_F6_TEST12B_OUT8 = 0x10,
    _2L_900PIN_PIN_F6_TEST12B_OUT9 = 0x11,
    _2L_900PIN_PIN_F6_TEST12B_OUT10 = 0x12,
    _2L_900PIN_PIN_F6_TEST12B_OUT11 = 0x13,
    _2L_900PIN_PIN_F6_NC = _2L_900PIN_PIN_F6_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_F6;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x106D
// MCU Ctrl : 0x220D at _2L_900PIN_PIN_F7_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_F7                       (_2L_900PIN_PIN_F7_NC)

typedef enum
{
    _2L_900PIN_PIN_F7_GPI = 0x00,
    _2L_900PIN_PIN_F7_GPO_PP = 0x01,
    _2L_900PIN_PIN_F7_GPO_OD = 0x02,
    _2L_900PIN_PIN_F7_EXT_UART_TX_0_3 = 0x03,
    _2L_900PIN_PIN_F7_EXT_UART_TX_1_3 = 0x04,
    _2L_900PIN_PIN_F7_EXT_UART_TX_2_3 = 0x05,
    _2L_900PIN_PIN_F7_TEST12B_OUT0 = 0x06,
    _2L_900PIN_PIN_F7_TEST12B_OUT1 = 0x07,
    _2L_900PIN_PIN_F7_TEST12B_OUT2 = 0x08,
    _2L_900PIN_PIN_F7_TEST12B_OUT3 = 0x09,
    _2L_900PIN_PIN_F7_TEST12B_OUT4 = 0x0A,
    _2L_900PIN_PIN_F7_TEST12B_OUT5 = 0x0B,
    _2L_900PIN_PIN_F7_TEST12B_OUT6 = 0x0C,
    _2L_900PIN_PIN_F7_TEST12B_OUT7 = 0x0D,
    _2L_900PIN_PIN_F7_TEST12B_OUT8 = 0x0E,
    _2L_900PIN_PIN_F7_TEST12B_OUT9 = 0x0F,
    _2L_900PIN_PIN_F7_TEST12B_OUT10 = 0x10,
    _2L_900PIN_PIN_F7_TEST12B_OUT11 = 0x11,
    _2L_900PIN_PIN_F7_NC = _2L_900PIN_PIN_F7_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_F7;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x106E
// MCU Ctrl : 0x220E at _2L_900PIN_PIN_G6_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_G6                       (_2L_900PIN_PIN_G6_NC)

typedef enum
{
    _2L_900PIN_PIN_G6_GPI = 0x00,
    _2L_900PIN_PIN_G6_GPO_PP = 0x01,
    _2L_900PIN_PIN_G6_GPO_OD = 0x02,
    _2L_900PIN_PIN_G6_IRDA_IN_0_0 = 0x03,
    _2L_900PIN_PIN_G6_PWM2_PP = 0x04,
    _2L_900PIN_PIN_G6_PWM2_OD = 0x05,
    _2L_900PIN_PIN_G6_PWM2_DIMMING_PP = 0x06,
    _2L_900PIN_PIN_G6_PWM2_DIMMING = 0x07,
    _2L_900PIN_PIN_G6_TCON8 = 0x08,
    _2L_900PIN_PIN_G6_INT0_5 = 0x09,
    _2L_900PIN_PIN_G6_INT1_5 = 0x0A,
    _2L_900PIN_PIN_G6_TEST12B_OUT0 = 0x0B,
    _2L_900PIN_PIN_G6_TEST12B_OUT1 = 0x0C,
    _2L_900PIN_PIN_G6_TEST12B_OUT2 = 0x0D,
    _2L_900PIN_PIN_G6_TEST12B_OUT3 = 0x0E,
    _2L_900PIN_PIN_G6_TEST12B_OUT4 = 0x0F,
    _2L_900PIN_PIN_G6_TEST12B_OUT5 = 0x10,
    _2L_900PIN_PIN_G6_TEST12B_OUT6 = 0x11,
    _2L_900PIN_PIN_G6_TEST12B_OUT7 = 0x12,
    _2L_900PIN_PIN_G6_TEST12B_OUT8 = 0x13,
    _2L_900PIN_PIN_G6_TEST12B_OUT9 = 0x14,
    _2L_900PIN_PIN_G6_TEST12B_OUT10 = 0x15,
    _2L_900PIN_PIN_G6_TEST12B_OUT11 = 0x16,
    _2L_900PIN_PIN_G6_NC = _2L_900PIN_PIN_G6_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_G6;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x106F
// MCU Ctrl : 0x220F at _2L_900PIN_PIN_D4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_D4                       (_2L_900PIN_PIN_D4_NC)

typedef enum
{
    _2L_900PIN_PIN_D4_GPI = 0x00,
    _2L_900PIN_PIN_D4_GPO_PP = 0x01,
    _2L_900PIN_PIN_D4_GPO_OD = 0x02,
    _2L_900PIN_PIN_D4_TPC_IICSCL_0_0 = 0x03,
    _2L_900PIN_PIN_D4_TPC_IICSCL_1_0 = 0x04,
    _2L_900PIN_PIN_D4_TEST12B_OUT0 = 0x05,
    _2L_900PIN_PIN_D4_TEST12B_OUT1 = 0x06,
    _2L_900PIN_PIN_D4_TEST12B_OUT2 = 0x07,
    _2L_900PIN_PIN_D4_TEST12B_OUT3 = 0x08,
    _2L_900PIN_PIN_D4_TEST12B_OUT4 = 0x09,
    _2L_900PIN_PIN_D4_TEST12B_OUT5 = 0x0A,
    _2L_900PIN_PIN_D4_TEST12B_OUT6 = 0x0B,
    _2L_900PIN_PIN_D4_TEST12B_OUT7 = 0x0C,
    _2L_900PIN_PIN_D4_TEST12B_OUT8 = 0x0D,
    _2L_900PIN_PIN_D4_TEST12B_OUT9 = 0x0E,
    _2L_900PIN_PIN_D4_TEST12B_OUT10 = 0x0F,
    _2L_900PIN_PIN_D4_TEST12B_OUT11 = 0x10,
    _2L_900PIN_PIN_D4_NC = _2L_900PIN_PIN_D4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_D4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1070
// MCU Ctrl : 0x2210 at _2L_900PIN_PIN_G4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_G4                       (_2L_900PIN_PIN_G4_NC)

typedef enum
{
    _2L_900PIN_PIN_G4_GPI = 0x00,
    _2L_900PIN_PIN_G4_GPO_PP = 0x01,
    _2L_900PIN_PIN_G4_GPO_OD = 0x02,
    _2L_900PIN_PIN_G4_TPC_IICSDA_0_0 = 0x03,
    _2L_900PIN_PIN_G4_TPC_IICSDA_1_0 = 0x04,
    _2L_900PIN_PIN_G4_TEST12B_OUT0 = 0x05,
    _2L_900PIN_PIN_G4_TEST12B_OUT1 = 0x06,
    _2L_900PIN_PIN_G4_TEST12B_OUT2 = 0x07,
    _2L_900PIN_PIN_G4_TEST12B_OUT3 = 0x08,
    _2L_900PIN_PIN_G4_TEST12B_OUT4 = 0x09,
    _2L_900PIN_PIN_G4_TEST12B_OUT5 = 0x0A,
    _2L_900PIN_PIN_G4_TEST12B_OUT6 = 0x0B,
    _2L_900PIN_PIN_G4_TEST12B_OUT7 = 0x0C,
    _2L_900PIN_PIN_G4_TEST12B_OUT8 = 0x0D,
    _2L_900PIN_PIN_G4_TEST12B_OUT9 = 0x0E,
    _2L_900PIN_PIN_G4_TEST12B_OUT10 = 0x0F,
    _2L_900PIN_PIN_G4_TEST12B_OUT11 = 0x10,
    _2L_900PIN_PIN_G4_NC = _2L_900PIN_PIN_G4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_G4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1071
// MCU Ctrl : 0x2211 at _2L_900PIN_PIN_A4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_A4                       (_2L_900PIN_PIN_A4_NC)

typedef enum
{
    _2L_900PIN_PIN_A4_GPI = 0x00,
    _2L_900PIN_PIN_A4_GPO_PP = 0x01,
    _2L_900PIN_PIN_A4_GPO_OD = 0x02,
    _2L_900PIN_PIN_A4_DDCSCL_ISP = 0x03,
    _2L_900PIN_PIN_A4_IICSCL_0_0 = 0x04,
    _2L_900PIN_PIN_A4_IICSCL_1_0 = 0x05,
    _2L_900PIN_PIN_A4_SWDCLK_0_0 = 0x06,
    _2L_900PIN_PIN_A4_USB_SPI_CLK_0_6 = 0x07,
    _2L_900PIN_PIN_A4_USB_SPI_CLK_1_6 = 0x08,
    _2L_900PIN_PIN_A4_USB_SPI_CLK_2_6 = 0x09,
    _2L_900PIN_PIN_A4_TEST12B_OUT3 = 0x0A,
    _2L_900PIN_PIN_A4_TEST12B_OUT4 = 0x0B,
    _2L_900PIN_PIN_A4_TEST12B_OUT5 = 0x0C,
    _2L_900PIN_PIN_A4_TEST12B_OUT6 = 0x0D,
    _2L_900PIN_PIN_A4_TEST12B_OUT7 = 0x0E,
    _2L_900PIN_PIN_A4_TEST12B_OUT8 = 0x0F,
    _2L_900PIN_PIN_A4_TEST12B_OUT9 = 0x10,
    _2L_900PIN_PIN_A4_TEST12B_OUT10 = 0x11,
    _2L_900PIN_PIN_A4_TEST12B_OUT11 = 0x12,
    _2L_900PIN_PIN_A4_NC = _2L_900PIN_PIN_A4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_A4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1072
// MCU Ctrl : 0x2212 at _2L_900PIN_PIN_B4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B4                       (_2L_900PIN_PIN_B4_NC)

typedef enum
{
    _2L_900PIN_PIN_B4_GPI = 0x00,
    _2L_900PIN_PIN_B4_GPO_PP = 0x01,
    _2L_900PIN_PIN_B4_GPO_OD = 0x02,
    _2L_900PIN_PIN_B4_DDCSDA_ISP = 0x03,
    _2L_900PIN_PIN_B4_IICSDA_0_0 = 0x04,
    _2L_900PIN_PIN_B4_IICSDA_1_0 = 0x05,
    _2L_900PIN_PIN_B4_SWDIO_0_0 = 0x06,
    _2L_900PIN_PIN_B4_USB_SPI_CLK_0_7 = 0x07,
    _2L_900PIN_PIN_B4_USB_SPI_CLK_1_7 = 0x08,
    _2L_900PIN_PIN_B4_USB_SPI_CLK_2_7 = 0x09,
    _2L_900PIN_PIN_B4_TEST12B_OUT3 = 0x0A,
    _2L_900PIN_PIN_B4_TEST12B_OUT4 = 0x0B,
    _2L_900PIN_PIN_B4_TEST12B_OUT5 = 0x0C,
    _2L_900PIN_PIN_B4_TEST12B_OUT6 = 0x0D,
    _2L_900PIN_PIN_B4_TEST12B_OUT7 = 0x0E,
    _2L_900PIN_PIN_B4_TEST12B_OUT8 = 0x0F,
    _2L_900PIN_PIN_B4_TEST12B_OUT9 = 0x10,
    _2L_900PIN_PIN_B4_TEST12B_OUT10 = 0x11,
    _2L_900PIN_PIN_B4_TEST12B_OUT11 = 0x12,
    _2L_900PIN_PIN_B4_NC = _2L_900PIN_PIN_B4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_B4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1073
// MCU Ctrl : 0x2213 at _2L_900PIN_PIN_E4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_E4                       (_2L_900PIN_PIN_E4_NC)

typedef enum
{
    _2L_900PIN_PIN_E4_GPI = 0x00,
    _2L_900PIN_PIN_E4_GPO_PP = 0x01,
    _2L_900PIN_PIN_E4_GPO_OD = 0x02,
    _2L_900PIN_PIN_E4_SD3 = 0x03,
    _2L_900PIN_PIN_E4_SPDIF3 = 0x04,
    _2L_900PIN_PIN_E4_IICSCL_0_1 = 0x05,
    _2L_900PIN_PIN_E4_IICSCL_1_1 = 0x06,
    _2L_900PIN_PIN_E4_TCON1 = 0x07,
    _2L_900PIN_PIN_E4_TEST12B_OUT0 = 0x08,
    _2L_900PIN_PIN_E4_TEST12B_OUT1 = 0x09,
    _2L_900PIN_PIN_E4_TEST12B_OUT2 = 0x0A,
    _2L_900PIN_PIN_E4_TEST12B_OUT3 = 0x0B,
    _2L_900PIN_PIN_E4_TEST12B_OUT4 = 0x0C,
    _2L_900PIN_PIN_E4_TEST12B_OUT5 = 0x0D,
    _2L_900PIN_PIN_E4_TEST12B_OUT6 = 0x0E,
    _2L_900PIN_PIN_E4_TEST12B_OUT7 = 0x0F,
    _2L_900PIN_PIN_E4_TEST12B_OUT8 = 0x10,
    _2L_900PIN_PIN_E4_TEST12B_OUT9 = 0x11,
    _2L_900PIN_PIN_E4_TEST12B_OUT10 = 0x12,
    _2L_900PIN_PIN_E4_TEST12B_OUT11 = 0x13,
    _2L_900PIN_PIN_E4_NC = _2L_900PIN_PIN_E4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_E4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1074
// MCU Ctrl : 0x2214 at _2L_900PIN_PIN_G5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_G5                       (_2L_900PIN_PIN_G5_NC)

typedef enum
{
    _2L_900PIN_PIN_G5_GPI = 0x00,
    _2L_900PIN_PIN_G5_GPO_PP = 0x01,
    _2L_900PIN_PIN_G5_GPO_OD = 0x02,
    _2L_900PIN_PIN_G5_SD2 = 0x03,
    _2L_900PIN_PIN_G5_SPDIF2 = 0x04,
    _2L_900PIN_PIN_G5_IICSDA_0_1 = 0x05,
    _2L_900PIN_PIN_G5_IICSDA_1_1 = 0x06,
    _2L_900PIN_PIN_G5_PWM_UPD_SYNC_0_0_PP = 0x07,
    _2L_900PIN_PIN_G5_TEST12B_OUT0 = 0x08,
    _2L_900PIN_PIN_G5_TEST12B_OUT1 = 0x09,
    _2L_900PIN_PIN_G5_TEST12B_OUT2 = 0x0A,
    _2L_900PIN_PIN_G5_TEST12B_OUT3 = 0x0B,
    _2L_900PIN_PIN_G5_TEST12B_OUT4 = 0x0C,
    _2L_900PIN_PIN_G5_TEST12B_OUT5 = 0x0D,
    _2L_900PIN_PIN_G5_TEST12B_OUT6 = 0x0E,
    _2L_900PIN_PIN_G5_TEST12B_OUT7 = 0x0F,
    _2L_900PIN_PIN_G5_TEST12B_OUT8 = 0x10,
    _2L_900PIN_PIN_G5_TEST12B_OUT9 = 0x11,
    _2L_900PIN_PIN_G5_TEST12B_OUT10 = 0x12,
    _2L_900PIN_PIN_G5_TEST12B_OUT11 = 0x13,
    _2L_900PIN_PIN_G5_NC = _2L_900PIN_PIN_G5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_G5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1075
// MCU Ctrl : 0x2215 at _2L_900PIN_PIN_E5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_E5                       (_2L_900PIN_PIN_E5_NC)

typedef enum
{
    _2L_900PIN_PIN_E5_GPI = 0x00,
    _2L_900PIN_PIN_E5_GPO_PP = 0x01,
    _2L_900PIN_PIN_E5_GPO_OD = 0x02,
    _2L_900PIN_PIN_E5_SD1 = 0x03,
    _2L_900PIN_PIN_E5_SPDIF1 = 0x04,
    _2L_900PIN_PIN_E5_IRQB = 0x05,
    _2L_900PIN_PIN_E5_TCON2 = 0x06,
    _2L_900PIN_PIN_E5_TEST12B_OUT0 = 0x07,
    _2L_900PIN_PIN_E5_TEST12B_OUT1 = 0x08,
    _2L_900PIN_PIN_E5_TEST12B_OUT2 = 0x09,
    _2L_900PIN_PIN_E5_TEST12B_OUT3 = 0x0A,
    _2L_900PIN_PIN_E5_TEST12B_OUT4 = 0x0B,
    _2L_900PIN_PIN_E5_TEST12B_OUT5 = 0x0C,
    _2L_900PIN_PIN_E5_TEST12B_OUT6 = 0x0D,
    _2L_900PIN_PIN_E5_TEST12B_OUT7 = 0x0E,
    _2L_900PIN_PIN_E5_TEST12B_OUT8 = 0x0F,
    _2L_900PIN_PIN_E5_TEST12B_OUT9 = 0x10,
    _2L_900PIN_PIN_E5_TEST12B_OUT10 = 0x11,
    _2L_900PIN_PIN_E5_TEST12B_OUT11 = 0x12,
    _2L_900PIN_PIN_E5_NC = _2L_900PIN_PIN_E5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_E5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1076
// MCU Ctrl : 0x2216 at _2L_900PIN_PIN_F5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_F5                       (_2L_900PIN_PIN_F5_NC)

typedef enum
{
    _2L_900PIN_PIN_F5_GPI = 0x00,
    _2L_900PIN_PIN_F5_GPO_PP = 0x01,
    _2L_900PIN_PIN_F5_GPO_OD = 0x02,
    _2L_900PIN_PIN_F5_SD0 = 0x03,
    _2L_900PIN_PIN_F5_SPDIF0 = 0x04,
    _2L_900PIN_PIN_F5_TCON3 = 0x05,
    _2L_900PIN_PIN_F5_TEST12B_OUT0 = 0x06,
    _2L_900PIN_PIN_F5_TEST12B_OUT1 = 0x07,
    _2L_900PIN_PIN_F5_TEST12B_OUT2 = 0x08,
    _2L_900PIN_PIN_F5_TEST12B_OUT3 = 0x09,
    _2L_900PIN_PIN_F5_TEST12B_OUT4 = 0x0A,
    _2L_900PIN_PIN_F5_TEST12B_OUT5 = 0x0B,
    _2L_900PIN_PIN_F5_TEST12B_OUT6 = 0x0C,
    _2L_900PIN_PIN_F5_TEST12B_OUT7 = 0x0D,
    _2L_900PIN_PIN_F5_TEST12B_OUT8 = 0x0E,
    _2L_900PIN_PIN_F5_TEST12B_OUT9 = 0x0F,
    _2L_900PIN_PIN_F5_TEST12B_OUT10 = 0x10,
    _2L_900PIN_PIN_F5_TEST12B_OUT11 = 0x11,
    _2L_900PIN_PIN_F5_NC = _2L_900PIN_PIN_F5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_F5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1077
// MCU Ctrl : 0x2217 at _2L_900PIN_PIN_F4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_F4                       (_2L_900PIN_PIN_F4_NC)

typedef enum
{
    _2L_900PIN_PIN_F4_GPI = 0x00,
    _2L_900PIN_PIN_F4_GPO_PP = 0x01,
    _2L_900PIN_PIN_F4_GPO_OD = 0x02,
    _2L_900PIN_PIN_F4_WS = 0x03,
    _2L_900PIN_PIN_F4_TYPEC_GPIO6_1_PP = 0x04,
    _2L_900PIN_PIN_F4_TYPEC_GPIO6_1_OD = 0x05,
    _2L_900PIN_PIN_F4_TYPEC_GPIO7_1_PP = 0x06,
    _2L_900PIN_PIN_F4_TYPEC_GPIO7_1_OD = 0x07,
    _2L_900PIN_PIN_F4_TCON4 = 0x08,
    _2L_900PIN_PIN_F4_TEST12B_OUT0 = 0x09,
    _2L_900PIN_PIN_F4_TEST12B_OUT1 = 0x0A,
    _2L_900PIN_PIN_F4_TEST12B_OUT2 = 0x0B,
    _2L_900PIN_PIN_F4_TEST12B_OUT3 = 0x0C,
    _2L_900PIN_PIN_F4_TEST12B_OUT4 = 0x0D,
    _2L_900PIN_PIN_F4_TEST12B_OUT5 = 0x0E,
    _2L_900PIN_PIN_F4_TEST12B_OUT6 = 0x0F,
    _2L_900PIN_PIN_F4_TEST12B_OUT7 = 0x10,
    _2L_900PIN_PIN_F4_TEST12B_OUT8 = 0x11,
    _2L_900PIN_PIN_F4_TEST12B_OUT9 = 0x12,
    _2L_900PIN_PIN_F4_TEST12B_OUT10 = 0x13,
    _2L_900PIN_PIN_F4_TEST12B_OUT11 = 0x14,
    _2L_900PIN_PIN_F4_NC = _2L_900PIN_PIN_F4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_F4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1078
// MCU Ctrl : 0x2218 at _2L_900PIN_PIN_A2_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_A2                       (_2L_900PIN_PIN_A2_NC)

typedef enum
{
    _2L_900PIN_PIN_A2_GPI = 0x00,
    _2L_900PIN_PIN_A2_GPO_PP = 0x01,
    _2L_900PIN_PIN_A2_GPO_OD = 0x02,
    _2L_900PIN_PIN_A2_DDCSCL_3 = 0x03,
    _2L_900PIN_PIN_A2_SWDCLK_0_1 = 0x04,
    _2L_900PIN_PIN_A2_TEST12B_OUT0 = 0x05,
    _2L_900PIN_PIN_A2_TEST12B_OUT1 = 0x06,
    _2L_900PIN_PIN_A2_TEST12B_OUT2 = 0x07,
    _2L_900PIN_PIN_A2_TEST12B_OUT3 = 0x08,
    _2L_900PIN_PIN_A2_TEST12B_OUT4 = 0x09,
    _2L_900PIN_PIN_A2_TEST12B_OUT5 = 0x0A,
    _2L_900PIN_PIN_A2_TEST12B_OUT6 = 0x0B,
    _2L_900PIN_PIN_A2_TEST12B_OUT7 = 0x0C,
    _2L_900PIN_PIN_A2_TEST12B_OUT8 = 0x0D,
    _2L_900PIN_PIN_A2_TEST12B_OUT9 = 0x0E,
    _2L_900PIN_PIN_A2_TEST12B_OUT10 = 0x0F,
    _2L_900PIN_PIN_A2_TEST12B_OUT11 = 0x10,
    _2L_900PIN_PIN_A2_NC = _2L_900PIN_PIN_A2_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_A2;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1079
// MCU Ctrl : 0x2219 at _2L_900PIN_PIN_B2_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B2                       (_2L_900PIN_PIN_B2_NC)

typedef enum
{
    _2L_900PIN_PIN_B2_GPI = 0x00,
    _2L_900PIN_PIN_B2_GPO_PP = 0x01,
    _2L_900PIN_PIN_B2_GPO_OD = 0x02,
    _2L_900PIN_PIN_B2_DDCSDA_3 = 0x03,
    _2L_900PIN_PIN_B2_SWDIO_0_1 = 0x04,
    _2L_900PIN_PIN_B2_TEST12B_OUT0 = 0x05,
    _2L_900PIN_PIN_B2_TEST12B_OUT1 = 0x06,
    _2L_900PIN_PIN_B2_TEST12B_OUT2 = 0x07,
    _2L_900PIN_PIN_B2_TEST12B_OUT3 = 0x08,
    _2L_900PIN_PIN_B2_TEST12B_OUT4 = 0x09,
    _2L_900PIN_PIN_B2_TEST12B_OUT5 = 0x0A,
    _2L_900PIN_PIN_B2_TEST12B_OUT6 = 0x0B,
    _2L_900PIN_PIN_B2_TEST12B_OUT7 = 0x0C,
    _2L_900PIN_PIN_B2_TEST12B_OUT8 = 0x0D,
    _2L_900PIN_PIN_B2_TEST12B_OUT9 = 0x0E,
    _2L_900PIN_PIN_B2_TEST12B_OUT10 = 0x0F,
    _2L_900PIN_PIN_B2_TEST12B_OUT11 = 0x10,
    _2L_900PIN_PIN_B2_NC = _2L_900PIN_PIN_B2_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_B2;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x107A
// MCU Ctrl : 0x221A at _2L_900PIN_PIN_E9_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_E9                       (_2L_900PIN_PIN_E9_NC)

typedef enum
{
    _2L_900PIN_PIN_E9_GPI = 0x00,
    _2L_900PIN_PIN_E9_GPO_PP = 0x01,
    _2L_900PIN_PIN_E9_GPO_OD = 0x02,
    _2L_900PIN_PIN_E9_USB_SPI_CLK_0_2 = 0x03,
    _2L_900PIN_PIN_E9_USB_SPI_CLK_1_2 = 0x04,
    _2L_900PIN_PIN_E9_USB_SPI_CLK_2_2 = 0x05,
    _2L_900PIN_PIN_E9_IICSCL_0_2 = 0x06,
    _2L_900PIN_PIN_E9_IICSCL_1_2 = 0x07,
    _2L_900PIN_PIN_E9_TTS_SCLK = 0x08,
    _2L_900PIN_PIN_E9_TEST12B_OUT0 = 0x09,
    _2L_900PIN_PIN_E9_TEST12B_OUT1 = 0x0A,
    _2L_900PIN_PIN_E9_TEST12B_OUT2 = 0x0B,
    _2L_900PIN_PIN_E9_TEST12B_OUT3 = 0x0C,
    _2L_900PIN_PIN_E9_TEST12B_OUT4 = 0x0D,
    _2L_900PIN_PIN_E9_TEST12B_OUT5 = 0x0E,
    _2L_900PIN_PIN_E9_TEST12B_OUT6 = 0x0F,
    _2L_900PIN_PIN_E9_TEST12B_OUT7 = 0x10,
    _2L_900PIN_PIN_E9_TEST12B_OUT8 = 0x11,
    _2L_900PIN_PIN_E9_TEST12B_OUT9 = 0x12,
    _2L_900PIN_PIN_E9_TEST12B_OUT10 = 0x13,
    _2L_900PIN_PIN_E9_TEST12B_OUT11 = 0x14,
    _2L_900PIN_PIN_E9_NC = _2L_900PIN_PIN_E9_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_E9;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x107B
// MCU Ctrl : 0x221B at _2L_900PIN_PIN_F9_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_F9                       (_2L_900PIN_PIN_F9_NC)

typedef enum
{
    _2L_900PIN_PIN_F9_GPI = 0x00,
    _2L_900PIN_PIN_F9_GPO_PP = 0x01,
    _2L_900PIN_PIN_F9_GPO_OD = 0x02,
    _2L_900PIN_PIN_F9_USB_SPI_SI_0_2 = 0x03,
    _2L_900PIN_PIN_F9_USB_SPI_SI_1_2 = 0x04,
    _2L_900PIN_PIN_F9_USB_SPI_SI_2_2 = 0x05,
    _2L_900PIN_PIN_F9_IICSDA_0_2 = 0x06,
    _2L_900PIN_PIN_F9_IICSDA_1_2 = 0x07,
    _2L_900PIN_PIN_F9_TTS_CEB = 0x08,
    _2L_900PIN_PIN_F9_INT0_2 = 0x09,
    _2L_900PIN_PIN_F9_INT1_2 = 0x0A,
    _2L_900PIN_PIN_F9_TCON0 = 0x0B,
    _2L_900PIN_PIN_F9_TEST12B_OUT0 = 0x0C,
    _2L_900PIN_PIN_F9_TEST12B_OUT1 = 0x0D,
    _2L_900PIN_PIN_F9_TEST12B_OUT2 = 0x0E,
    _2L_900PIN_PIN_F9_TEST12B_OUT3 = 0x0F,
    _2L_900PIN_PIN_F9_TEST12B_OUT4 = 0x10,
    _2L_900PIN_PIN_F9_TEST12B_OUT5 = 0x11,
    _2L_900PIN_PIN_F9_TEST12B_OUT6 = 0x12,
    _2L_900PIN_PIN_F9_TEST12B_OUT7 = 0x13,
    _2L_900PIN_PIN_F9_TEST12B_OUT8 = 0x14,
    _2L_900PIN_PIN_F9_TEST12B_OUT9 = 0x15,
    _2L_900PIN_PIN_F9_TEST12B_OUT10 = 0x16,
    _2L_900PIN_PIN_F9_TEST12B_OUT11 = 0x17,
    _2L_900PIN_PIN_F9_NC = _2L_900PIN_PIN_F9_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_F9;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x107C
// MCU Ctrl : 0x221C at _2L_900PIN_PIN_E8_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_E8                       (_2L_900PIN_PIN_E8_NC)

typedef enum
{
    _2L_900PIN_PIN_E8_GPI = 0x00,
    _2L_900PIN_PIN_E8_GPO_PP = 0x01,
    _2L_900PIN_PIN_E8_GPO_OD = 0x02,
    _2L_900PIN_PIN_E8_USB_SPI_SO_0_2 = 0x03,
    _2L_900PIN_PIN_E8_USB_SPI_SO_1_2 = 0x04,
    _2L_900PIN_PIN_E8_USB_SPI_SO_2_2 = 0x05,
    _2L_900PIN_PIN_E8_TTS_SI = 0x06,
    _2L_900PIN_PIN_E8_TYPEC_GPIO0_0_PP = 0x07,
    _2L_900PIN_PIN_E8_TYPEC_GPIO0_0_OD = 0x08,
    _2L_900PIN_PIN_E8_TYPEC_GPIO1_0_PP = 0x09,
    _2L_900PIN_PIN_E8_TYPEC_GPIO1_0_OD = 0x0A,
    _2L_900PIN_PIN_E8_M1_IDOMAIN_HS_OUT = 0x0B,
    _2L_900PIN_PIN_E8_TEST12B_OUT0 = 0x0C,
    _2L_900PIN_PIN_E8_TEST12B_OUT1 = 0x0D,
    _2L_900PIN_PIN_E8_TEST12B_OUT2 = 0x0E,
    _2L_900PIN_PIN_E8_TEST12B_OUT3 = 0x0F,
    _2L_900PIN_PIN_E8_TEST12B_OUT4 = 0x10,
    _2L_900PIN_PIN_E8_TEST12B_OUT5 = 0x11,
    _2L_900PIN_PIN_E8_TEST12B_OUT6 = 0x12,
    _2L_900PIN_PIN_E8_TEST12B_OUT7 = 0x13,
    _2L_900PIN_PIN_E8_TEST12B_OUT8 = 0x14,
    _2L_900PIN_PIN_E8_TEST12B_OUT9 = 0x15,
    _2L_900PIN_PIN_E8_TEST12B_OUT10 = 0x16,
    _2L_900PIN_PIN_E8_TEST12B_OUT11 = 0x17,
    _2L_900PIN_PIN_E8_NC = _2L_900PIN_PIN_E8_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_E8;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x107D
// MCU Ctrl : 0x221D at _2L_900PIN_PIN_F8_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_F8                       (_2L_900PIN_PIN_F8_NC)

typedef enum
{
    _2L_900PIN_PIN_F8_GPI = 0x00,
    _2L_900PIN_PIN_F8_GPO_PP = 0x01,
    _2L_900PIN_PIN_F8_GPO_OD = 0x02,
    _2L_900PIN_PIN_F8_USB_SPI_CEB0_0_2 = 0x03,
    _2L_900PIN_PIN_F8_USB_SPI_CEB0_1_2 = 0x04,
    _2L_900PIN_PIN_F8_USB_SPI_CEB0_2_2 = 0x05,
    _2L_900PIN_PIN_F8_IICSCL_0_3 = 0x06,
    _2L_900PIN_PIN_F8_IICSCL_1_3 = 0x07,
    _2L_900PIN_PIN_F8_TTS_SO = 0x08,
    _2L_900PIN_PIN_F8_TCON5 = 0x09,
    _2L_900PIN_PIN_F8_TEST12B_OUT0 = 0x0A,
    _2L_900PIN_PIN_F8_TEST12B_OUT1 = 0x0B,
    _2L_900PIN_PIN_F8_TEST12B_OUT2 = 0x0C,
    _2L_900PIN_PIN_F8_TEST12B_OUT3 = 0x0D,
    _2L_900PIN_PIN_F8_TEST12B_OUT4 = 0x0E,
    _2L_900PIN_PIN_F8_TEST12B_OUT5 = 0x0F,
    _2L_900PIN_PIN_F8_TEST12B_OUT6 = 0x10,
    _2L_900PIN_PIN_F8_TEST12B_OUT7 = 0x11,
    _2L_900PIN_PIN_F8_TEST12B_OUT8 = 0x12,
    _2L_900PIN_PIN_F8_TEST12B_OUT9 = 0x13,
    _2L_900PIN_PIN_F8_TEST12B_OUT10 = 0x14,
    _2L_900PIN_PIN_F8_TEST12B_OUT11 = 0x15,
    _2L_900PIN_PIN_F8_NC = _2L_900PIN_PIN_F8_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_F8;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x107E
// MCU Ctrl : 0x221E at _2L_900PIN_PIN_E7_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_E7                       (_2L_900PIN_PIN_E7_NC)

typedef enum
{
    _2L_900PIN_PIN_E7_GPI = 0x00,
    _2L_900PIN_PIN_E7_GPO_PP = 0x01,
    _2L_900PIN_PIN_E7_GPO_OD = 0x02,
    _2L_900PIN_PIN_E7_USB_SPI_CEB1_0_2 = 0x03,
    _2L_900PIN_PIN_E7_USB_SPI_CEB1_1_2 = 0x04,
    _2L_900PIN_PIN_E7_USB_SPI_CEB1_2_2 = 0x05,
    _2L_900PIN_PIN_E7_IICSDA_0_3 = 0x06,
    _2L_900PIN_PIN_E7_IICSDA_1_3 = 0x07,
    _2L_900PIN_PIN_E7_PWM_UPD_SYNC_0_1_PP = 0x08,
    _2L_900PIN_PIN_E7_INT0_3 = 0x09,
    _2L_900PIN_PIN_E7_INT1_3 = 0x0A,
    _2L_900PIN_PIN_E7_TCON5 = 0x0B,
    _2L_900PIN_PIN_E7_TEST12B_OUT0 = 0x0C,
    _2L_900PIN_PIN_E7_TEST12B_OUT1 = 0x0D,
    _2L_900PIN_PIN_E7_TEST12B_OUT2 = 0x0E,
    _2L_900PIN_PIN_E7_TEST12B_OUT3 = 0x0F,
    _2L_900PIN_PIN_E7_TEST12B_OUT4 = 0x10,
    _2L_900PIN_PIN_E7_TEST12B_OUT5 = 0x11,
    _2L_900PIN_PIN_E7_TEST12B_OUT6 = 0x12,
    _2L_900PIN_PIN_E7_TEST12B_OUT7 = 0x13,
    _2L_900PIN_PIN_E7_TEST12B_OUT8 = 0x14,
    _2L_900PIN_PIN_E7_TEST12B_OUT9 = 0x15,
    _2L_900PIN_PIN_E7_TEST12B_OUT10 = 0x16,
    _2L_900PIN_PIN_E7_TEST12B_OUT11 = 0x17,
    _2L_900PIN_PIN_E7_NC = _2L_900PIN_PIN_E7_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_E7;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x107F
// MCU Ctrl : 0x221F at _2L_900PIN_PIN_D3_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_D3                       (_2L_900PIN_PIN_D3_NC)

typedef enum
{
    _2L_900PIN_PIN_D3_GPI = 0x00,
    _2L_900PIN_PIN_D3_GPO_PP = 0x01,
    _2L_900PIN_PIN_D3_GPO_OD = 0x02,
    _2L_900PIN_PIN_D3_SCK = 0x03,
    _2L_900PIN_PIN_D3_IRDA_IN_0_1 = 0x04,
    _2L_900PIN_PIN_D3_TEST12B_OUT0 = 0x05,
    _2L_900PIN_PIN_D3_TEST12B_OUT1 = 0x06,
    _2L_900PIN_PIN_D3_TEST12B_OUT2 = 0x07,
    _2L_900PIN_PIN_D3_TEST12B_OUT3 = 0x08,
    _2L_900PIN_PIN_D3_TEST12B_OUT4 = 0x09,
    _2L_900PIN_PIN_D3_TEST12B_OUT5 = 0x0A,
    _2L_900PIN_PIN_D3_TEST12B_OUT6 = 0x0B,
    _2L_900PIN_PIN_D3_TEST12B_OUT7 = 0x0C,
    _2L_900PIN_PIN_D3_TEST12B_OUT8 = 0x0D,
    _2L_900PIN_PIN_D3_TEST12B_OUT9 = 0x0E,
    _2L_900PIN_PIN_D3_TEST12B_OUT10 = 0x0F,
    _2L_900PIN_PIN_D3_TEST12B_OUT11 = 0x10,
    _2L_900PIN_PIN_D3_NC = _2L_900PIN_PIN_D3_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_D3;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1080
// MCU Ctrl : 0x2220 at _2L_900PIN_PIN_B5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B5                       (_2L_900PIN_PIN_B5_NC)

typedef enum
{
    _2L_900PIN_PIN_B5_GPI = 0x00,
    _2L_900PIN_PIN_B5_GPO_PP = 0x01,
    _2L_900PIN_PIN_B5_GPO_OD = 0x02,
    _2L_900PIN_PIN_B5_SPDIF2 = 0x03,
    _2L_900PIN_PIN_B5_SD2 = 0x04,
    _2L_900PIN_PIN_B5_EXT_UART_TX_0_2 = 0x05,
    _2L_900PIN_PIN_B5_EXT_UART_TX_1_2 = 0x06,
    _2L_900PIN_PIN_B5_EXT_UART_TX_2_2 = 0x07,
    _2L_900PIN_PIN_B5_USB_SPI_CLK_0_0 = 0x08,
    _2L_900PIN_PIN_B5_USB_SPI_CLK_1_0 = 0x09,
    _2L_900PIN_PIN_B5_USB_SPI_CLK_2_0 = 0x0A,
    _2L_900PIN_PIN_B5_TEST12B_OUT0 = 0x0B,
    _2L_900PIN_PIN_B5_TEST12B_OUT1 = 0x0C,
    _2L_900PIN_PIN_B5_TEST12B_OUT2 = 0x0D,
    _2L_900PIN_PIN_B5_TEST12B_OUT3 = 0x0E,
    _2L_900PIN_PIN_B5_TEST12B_OUT4 = 0x0F,
    _2L_900PIN_PIN_B5_TEST12B_OUT5 = 0x10,
    _2L_900PIN_PIN_B5_TEST12B_OUT6 = 0x11,
    _2L_900PIN_PIN_B5_TEST12B_OUT7 = 0x12,
    _2L_900PIN_PIN_B5_TEST12B_OUT8 = 0x13,
    _2L_900PIN_PIN_B5_TEST12B_OUT9 = 0x14,
    _2L_900PIN_PIN_B5_TEST12B_OUT10 = 0x15,
    _2L_900PIN_PIN_B5_TEST12B_OUT11 = 0x16,
    _2L_900PIN_PIN_B5_NC = _2L_900PIN_PIN_B5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_B5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1081
// MCU Ctrl : 0x2221 at _2L_900PIN_PIN_AA4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_AA4                      (_2L_900PIN_PIN_AA4_NC)

typedef enum
{
    _2L_900PIN_PIN_AA4_GPI = 0x00,
    _2L_900PIN_PIN_AA4_GPO_PP = 0x01,
    _2L_900PIN_PIN_AA4_GPO_OD = 0x02,
    _2L_900PIN_PIN_AA4_SD1 = 0x03,
    _2L_900PIN_PIN_AA4_SPDIF1 = 0x04,
    _2L_900PIN_PIN_AA4_EXT_UART_RX_0_2 = 0x05,
    _2L_900PIN_PIN_AA4_EXT_UART_RX_1_2 = 0x06,
    _2L_900PIN_PIN_AA4_EXT_UART_RX_2_2 = 0x07,
    _2L_900PIN_PIN_AA4_USB_SPI_SI_0_0 = 0x08,
    _2L_900PIN_PIN_AA4_USB_SPI_SI_1_0 = 0x09,
    _2L_900PIN_PIN_AA4_USB_SPI_SI_2_0 = 0x0A,
    _2L_900PIN_PIN_AA4_TCON1 = 0x0B,
    _2L_900PIN_PIN_AA4_TEST12B_OUT0 = 0x0C,
    _2L_900PIN_PIN_AA4_TEST12B_OUT1 = 0x0D,
    _2L_900PIN_PIN_AA4_TEST12B_OUT2 = 0x0E,
    _2L_900PIN_PIN_AA4_TEST12B_OUT3 = 0x0F,
    _2L_900PIN_PIN_AA4_TEST12B_OUT4 = 0x10,
    _2L_900PIN_PIN_AA4_TEST12B_OUT5 = 0x11,
    _2L_900PIN_PIN_AA4_TEST12B_OUT6 = 0x12,
    _2L_900PIN_PIN_AA4_TEST12B_OUT7 = 0x13,
    _2L_900PIN_PIN_AA4_TEST12B_OUT8 = 0x14,
    _2L_900PIN_PIN_AA4_TEST12B_OUT9 = 0x15,
    _2L_900PIN_PIN_AA4_TEST12B_OUT10 = 0x16,
    _2L_900PIN_PIN_AA4_TEST12B_OUT11 = 0x17,
    _2L_900PIN_PIN_AA4_NC = _2L_900PIN_PIN_AA4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_AA4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1082
// MCU Ctrl : 0x2222 at _2L_900PIN_PIN_Y4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_Y4                       (_2L_900PIN_PIN_Y4_NC)

typedef enum
{
    _2L_900PIN_PIN_Y4_GPI = 0x00,
    _2L_900PIN_PIN_Y4_GPO_PP = 0x01,
    _2L_900PIN_PIN_Y4_GPO_OD = 0x02,
    _2L_900PIN_PIN_Y4_SD0 = 0x03,
    _2L_900PIN_PIN_Y4_SPDIF0 = 0x04,
    _2L_900PIN_PIN_Y4_USB_SPI_SO_0_0 = 0x05,
    _2L_900PIN_PIN_Y4_USB_SPI_SO_1_0 = 0x06,
    _2L_900PIN_PIN_Y4_USB_SPI_SO_2_0 = 0x07,
    _2L_900PIN_PIN_Y4_IICSCL_0_7 = 0x08,
    _2L_900PIN_PIN_Y4_IICSCL_1_7 = 0x09,
    _2L_900PIN_PIN_Y4_TEST12B_OUT0 = 0x0A,
    _2L_900PIN_PIN_Y4_TEST12B_OUT1 = 0x0B,
    _2L_900PIN_PIN_Y4_TEST12B_OUT2 = 0x0C,
    _2L_900PIN_PIN_Y4_TEST12B_OUT3 = 0x0D,
    _2L_900PIN_PIN_Y4_TEST12B_OUT4 = 0x0E,
    _2L_900PIN_PIN_Y4_TEST12B_OUT5 = 0x0F,
    _2L_900PIN_PIN_Y4_TEST12B_OUT6 = 0x10,
    _2L_900PIN_PIN_Y4_TEST12B_OUT7 = 0x11,
    _2L_900PIN_PIN_Y4_TEST12B_OUT8 = 0x12,
    _2L_900PIN_PIN_Y4_TEST12B_OUT9 = 0x13,
    _2L_900PIN_PIN_Y4_TEST12B_OUT10 = 0x14,
    _2L_900PIN_PIN_Y4_TEST12B_OUT11 = 0x15,
    _2L_900PIN_PIN_Y4_NC = _2L_900PIN_PIN_Y4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_Y4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1083
// MCU Ctrl : 0x2223 at _2L_900PIN_PIN_C5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_C5                       (_2L_900PIN_PIN_C5_NC)

typedef enum
{
    _2L_900PIN_PIN_C5_GPI = 0x00,
    _2L_900PIN_PIN_C5_GPO_PP = 0x01,
    _2L_900PIN_PIN_C5_GPO_OD = 0x02,
    _2L_900PIN_PIN_C5_WS = 0x03,
    _2L_900PIN_PIN_C5_USB_SPI_CEB0_0_0 = 0x04,
    _2L_900PIN_PIN_C5_USB_SPI_CEB0_1_0 = 0x05,
    _2L_900PIN_PIN_C5_USB_SPI_CEB0_2_0 = 0x06,
    _2L_900PIN_PIN_C5_IICSDA_0_7 = 0x07,
    _2L_900PIN_PIN_C5_IICSDA_1_7 = 0x08,
    _2L_900PIN_PIN_C5_TCON2 = 0x09,
    _2L_900PIN_PIN_C5_TEST12B_OUT0 = 0x0A,
    _2L_900PIN_PIN_C5_TEST12B_OUT1 = 0x0B,
    _2L_900PIN_PIN_C5_TEST12B_OUT2 = 0x0C,
    _2L_900PIN_PIN_C5_TEST12B_OUT3 = 0x0D,
    _2L_900PIN_PIN_C5_TEST12B_OUT4 = 0x0E,
    _2L_900PIN_PIN_C5_TEST12B_OUT5 = 0x0F,
    _2L_900PIN_PIN_C5_TEST12B_OUT6 = 0x10,
    _2L_900PIN_PIN_C5_TEST12B_OUT7 = 0x11,
    _2L_900PIN_PIN_C5_TEST12B_OUT8 = 0x12,
    _2L_900PIN_PIN_C5_TEST12B_OUT9 = 0x13,
    _2L_900PIN_PIN_C5_TEST12B_OUT10 = 0x14,
    _2L_900PIN_PIN_C5_TEST12B_OUT11 = 0x15,
    _2L_900PIN_PIN_C5_NC = _2L_900PIN_PIN_C5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_C5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1084
// MCU Ctrl : 0x2224 at _2L_900PIN_PIN_C4_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_C4                       (_2L_900PIN_PIN_C4_NC)

typedef enum
{
    _2L_900PIN_PIN_C4_GPI = 0x00,
    _2L_900PIN_PIN_C4_GPO_PP = 0x01,
    _2L_900PIN_PIN_C4_GPO_OD = 0x02,
    _2L_900PIN_PIN_C4_SCK = 0x03,
    _2L_900PIN_PIN_C4_EXT_UART_TX_0_1 = 0x04,
    _2L_900PIN_PIN_C4_EXT_UART_TX_1_1 = 0x05,
    _2L_900PIN_PIN_C4_EXT_UART_TX_2_1 = 0x06,
    _2L_900PIN_PIN_C4_USB_SPI_CEB1_0_0 = 0x07,
    _2L_900PIN_PIN_C4_USB_SPI_CEB1_1_0 = 0x08,
    _2L_900PIN_PIN_C4_USB_SPI_CEB1_2_0 = 0x09,
    _2L_900PIN_PIN_C4_TCON3 = 0x0A,
    _2L_900PIN_PIN_C4_TEST12B_OUT0 = 0x0B,
    _2L_900PIN_PIN_C4_TEST12B_OUT1 = 0x0C,
    _2L_900PIN_PIN_C4_TEST12B_OUT2 = 0x0D,
    _2L_900PIN_PIN_C4_TEST12B_OUT3 = 0x0E,
    _2L_900PIN_PIN_C4_TEST12B_OUT4 = 0x0F,
    _2L_900PIN_PIN_C4_TEST12B_OUT5 = 0x10,
    _2L_900PIN_PIN_C4_TEST12B_OUT6 = 0x11,
    _2L_900PIN_PIN_C4_TEST12B_OUT7 = 0x12,
    _2L_900PIN_PIN_C4_TEST12B_OUT8 = 0x13,
    _2L_900PIN_PIN_C4_TEST12B_OUT9 = 0x14,
    _2L_900PIN_PIN_C4_TEST12B_OUT10 = 0x15,
    _2L_900PIN_PIN_C4_TEST12B_OUT11 = 0x16,
    _2L_900PIN_PIN_C4_NC = _2L_900PIN_PIN_C4_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_C4;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1085
// MCU Ctrl : 0x2225 at _2L_900PIN_PIN_D5_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_D5                       (_2L_900PIN_PIN_D5_NC)

typedef enum
{
    _2L_900PIN_PIN_D5_GPI = 0x00,
    _2L_900PIN_PIN_D5_GPO_PP = 0x01,
    _2L_900PIN_PIN_D5_GPO_OD = 0x02,
    _2L_900PIN_PIN_D5_MCK = 0x03,
    _2L_900PIN_PIN_D5_EXT_UART_RX_0_1 = 0x04,
    _2L_900PIN_PIN_D5_EXT_UART_RX_1_1 = 0x05,
    _2L_900PIN_PIN_D5_EXT_UART_RX_2_1 = 0x06,
    _2L_900PIN_PIN_D5_TCON4 = 0x07,
    _2L_900PIN_PIN_D5_TYPEC_GPIO4_1_PP = 0x08,
    _2L_900PIN_PIN_D5_TYPEC_GPIO4_1_OD = 0x09,
    _2L_900PIN_PIN_D5_TYPEC_GPIO5_1_PP = 0x0A,
    _2L_900PIN_PIN_D5_TYPEC_GPIO5_1_OD = 0x0B,
    _2L_900PIN_PIN_D5_TEST12B_OUT0 = 0x0C,
    _2L_900PIN_PIN_D5_TEST12B_OUT1 = 0x0D,
    _2L_900PIN_PIN_D5_TEST12B_OUT2 = 0x0E,
    _2L_900PIN_PIN_D5_TEST12B_OUT3 = 0x0F,
    _2L_900PIN_PIN_D5_TEST12B_OUT4 = 0x10,
    _2L_900PIN_PIN_D5_TEST12B_OUT5 = 0x11,
    _2L_900PIN_PIN_D5_TEST12B_OUT6 = 0x12,
    _2L_900PIN_PIN_D5_TEST12B_OUT7 = 0x13,
    _2L_900PIN_PIN_D5_TEST12B_OUT8 = 0x14,
    _2L_900PIN_PIN_D5_TEST12B_OUT9 = 0x15,
    _2L_900PIN_PIN_D5_TEST12B_OUT10 = 0x16,
    _2L_900PIN_PIN_D5_TEST12B_OUT11 = 0x17,
    _2L_900PIN_PIN_D5_NC = _2L_900PIN_PIN_D5_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_D5;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1086
// MCU Ctrl : 0x2226 at _2L_900PIN_PIN_E6_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_E6                       (_2L_900PIN_PIN_E6_NC)

typedef enum
{
    _2L_900PIN_PIN_E6_GPI = 0x00,
    _2L_900PIN_PIN_E6_GPO_PP = 0x01,
    _2L_900PIN_PIN_E6_GPO_OD = 0x02,
    _2L_900PIN_PIN_E6_PWM_OUT_0_1 = 0x03,
    _2L_900PIN_PIN_E6_SD3 = 0x04,
    _2L_900PIN_PIN_E6_SPDIF3 = 0x05,
    _2L_900PIN_PIN_E6_PWM0_PP = 0x06,
    _2L_900PIN_PIN_E6_PWM0_OD = 0x07,
    _2L_900PIN_PIN_E6_PWM0_DIMMING_PP = 0x08,
    _2L_900PIN_PIN_E6_PWM0_DIMMING = 0x09,
    _2L_900PIN_PIN_E6_TCON0 = 0x0A,
    _2L_900PIN_PIN_E6_TEST12B_OUT0 = 0x0B,
    _2L_900PIN_PIN_E6_TEST12B_OUT1 = 0x0C,
    _2L_900PIN_PIN_E6_TEST12B_OUT2 = 0x0D,
    _2L_900PIN_PIN_E6_TEST12B_OUT3 = 0x0E,
    _2L_900PIN_PIN_E6_TEST12B_OUT4 = 0x0F,
    _2L_900PIN_PIN_E6_TEST12B_OUT5 = 0x10,
    _2L_900PIN_PIN_E6_TEST12B_OUT6 = 0x11,
    _2L_900PIN_PIN_E6_TEST12B_OUT7 = 0x12,
    _2L_900PIN_PIN_E6_TEST12B_OUT8 = 0x13,
    _2L_900PIN_PIN_E6_TEST12B_OUT9 = 0x14,
    _2L_900PIN_PIN_E6_TEST12B_OUT10 = 0x15,
    _2L_900PIN_PIN_E6_TEST12B_OUT11 = 0x16,
    _2L_900PIN_PIN_E6_NC = _2L_900PIN_PIN_E6_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_E6;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1087
// MCU Ctrl : 0x2227 at _2L_900PIN_PIN_A3_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_A3                       (_2L_900PIN_PIN_A3_NC)

typedef enum
{
    _2L_900PIN_PIN_A3_GPI = 0x00,
    _2L_900PIN_PIN_A3_GPO_PP = 0x01,
    _2L_900PIN_PIN_A3_GPO_OD = 0x02,
    _2L_900PIN_PIN_A3_DDCSCL_4 = 0x03,
    _2L_900PIN_PIN_A3_SWDCLK_0_2 = 0x04,
    _2L_900PIN_PIN_A3_TEST12B_OUT0 = 0x05,
    _2L_900PIN_PIN_A3_TEST12B_OUT1 = 0x06,
    _2L_900PIN_PIN_A3_TEST12B_OUT2 = 0x07,
    _2L_900PIN_PIN_A3_TEST12B_OUT3 = 0x08,
    _2L_900PIN_PIN_A3_TEST12B_OUT4 = 0x09,
    _2L_900PIN_PIN_A3_TEST12B_OUT5 = 0x0A,
    _2L_900PIN_PIN_A3_TEST12B_OUT6 = 0x0B,
    _2L_900PIN_PIN_A3_TEST12B_OUT7 = 0x0C,
    _2L_900PIN_PIN_A3_TEST12B_OUT8 = 0x0D,
    _2L_900PIN_PIN_A3_TEST12B_OUT9 = 0x0E,
    _2L_900PIN_PIN_A3_TEST12B_OUT10 = 0x0F,
    _2L_900PIN_PIN_A3_TEST12B_OUT11 = 0x10,
    _2L_900PIN_PIN_A3_NC = _2L_900PIN_PIN_A3_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_A3;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1088
// MCU Ctrl : 0x2228 at _2L_900PIN_PIN_B3_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_B3                       (_2L_900PIN_PIN_B3_NC)

typedef enum
{
    _2L_900PIN_PIN_B3_GPI = 0x00,
    _2L_900PIN_PIN_B3_GPO_PP = 0x01,
    _2L_900PIN_PIN_B3_GPO_OD = 0x02,
    _2L_900PIN_PIN_B3_DDCSDA_4 = 0x03,
    _2L_900PIN_PIN_B3_SWDIO_0_2 = 0x04,
    _2L_900PIN_PIN_B3_TEST12B_OUT0 = 0x05,
    _2L_900PIN_PIN_B3_TEST12B_OUT1 = 0x06,
    _2L_900PIN_PIN_B3_TEST12B_OUT2 = 0x07,
    _2L_900PIN_PIN_B3_TEST12B_OUT3 = 0x08,
    _2L_900PIN_PIN_B3_TEST12B_OUT4 = 0x09,
    _2L_900PIN_PIN_B3_TEST12B_OUT5 = 0x0A,
    _2L_900PIN_PIN_B3_TEST12B_OUT6 = 0x0B,
    _2L_900PIN_PIN_B3_TEST12B_OUT7 = 0x0C,
    _2L_900PIN_PIN_B3_TEST12B_OUT8 = 0x0D,
    _2L_900PIN_PIN_B3_TEST12B_OUT9 = 0x0E,
    _2L_900PIN_PIN_B3_TEST12B_OUT10 = 0x0F,
    _2L_900PIN_PIN_B3_TEST12B_OUT11 = 0x10,
    _2L_900PIN_PIN_B3_NC = _2L_900PIN_PIN_B3_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_B3;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1089
// MCU Ctrl : 0x2229 at _2L_900PIN_PIN_C3_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_C3                       (_2L_900PIN_PIN_C3_NC)

typedef enum
{
    _2L_900PIN_PIN_C3_GPI = 0x00,
    _2L_900PIN_PIN_C3_GPO_PP = 0x01,
    _2L_900PIN_PIN_C3_GPO_OD = 0x02,
    _2L_900PIN_PIN_C3_IRDA_IN_0_2 = 0x03,
    _2L_900PIN_PIN_C3_TCON7 = 0x04,
    _2L_900PIN_PIN_C3_TYPEC_GPIO2_0_PP = 0x05,
    _2L_900PIN_PIN_C3_TYPEC_GPIO2_0_OD = 0x06,
    _2L_900PIN_PIN_C3_TYPEC_GPIO3_0_PP = 0x07,
    _2L_900PIN_PIN_C3_TYPEC_GPIO3_0_OD = 0x08,
    _2L_900PIN_PIN_C3_TEST12B_OUT0 = 0x09,
    _2L_900PIN_PIN_C3_TEST12B_OUT1 = 0x0A,
    _2L_900PIN_PIN_C3_TEST12B_OUT2 = 0x0B,
    _2L_900PIN_PIN_C3_TEST12B_OUT3 = 0x0C,
    _2L_900PIN_PIN_C3_TEST12B_OUT4 = 0x0D,
    _2L_900PIN_PIN_C3_TEST12B_OUT5 = 0x0E,
    _2L_900PIN_PIN_C3_TEST12B_OUT6 = 0x0F,
    _2L_900PIN_PIN_C3_TEST12B_OUT7 = 0x10,
    _2L_900PIN_PIN_C3_TEST12B_OUT8 = 0x11,
    _2L_900PIN_PIN_C3_TEST12B_OUT9 = 0x12,
    _2L_900PIN_PIN_C3_TEST12B_OUT10 = 0x13,
    _2L_900PIN_PIN_C3_TEST12B_OUT11 = 0x14,
    _2L_900PIN_PIN_C3_NC = _2L_900PIN_PIN_C3_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_C3;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x108A
// MCU Ctrl : 0x222A at _2L_900PIN_PIN_E3_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_E3                       (_2L_900PIN_PIN_E3_NC)

typedef enum
{
    _2L_900PIN_PIN_E3_GPI = 0x00,
    _2L_900PIN_PIN_E3_GPO_PP = 0x01,
    _2L_900PIN_PIN_E3_GPO_OD = 0x02,
    _2L_900PIN_PIN_E3_MCK = 0x03,
    _2L_900PIN_PIN_E3_TYPEC_GPIO6_0_PP = 0x04,
    _2L_900PIN_PIN_E3_TYPEC_GPIO6_0_OD = 0x05,
    _2L_900PIN_PIN_E3_TYPEC_GPIO7_0_PP = 0x06,
    _2L_900PIN_PIN_E3_TYPEC_GPIO7_0_OD = 0x07,
    _2L_900PIN_PIN_E3_TEST12B_OUT0 = 0x08,
    _2L_900PIN_PIN_E3_TEST12B_OUT1 = 0x09,
    _2L_900PIN_PIN_E3_TEST12B_OUT2 = 0x0A,
    _2L_900PIN_PIN_E3_TEST12B_OUT3 = 0x0B,
    _2L_900PIN_PIN_E3_TEST12B_OUT4 = 0x0C,
    _2L_900PIN_PIN_E3_TEST12B_OUT5 = 0x0D,
    _2L_900PIN_PIN_E3_TEST12B_OUT6 = 0x0E,
    _2L_900PIN_PIN_E3_TEST12B_OUT7 = 0x0F,
    _2L_900PIN_PIN_E3_TEST12B_OUT8 = 0x10,
    _2L_900PIN_PIN_E3_TEST12B_OUT9 = 0x11,
    _2L_900PIN_PIN_E3_TEST12B_OUT10 = 0x12,
    _2L_900PIN_PIN_E3_TEST12B_OUT11 = 0x13,
    _2L_900PIN_PIN_E3_NC = _2L_900PIN_PIN_E3_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_E3;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x108B
// MCU Ctrl : 0x222B at _2L_900PIN_PIN_C2_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_C2                       (_2L_900PIN_PIN_C2_NC)

typedef enum
{
    _2L_900PIN_PIN_C2_GPI = 0x00,
    _2L_900PIN_PIN_C2_GPO_PP = 0x01,
    _2L_900PIN_PIN_C2_GPO_OD = 0x02,
    _2L_900PIN_PIN_C2_TEST12B_OUT0 = 0x03,
    _2L_900PIN_PIN_C2_TEST12B_OUT1 = 0x04,
    _2L_900PIN_PIN_C2_TEST12B_OUT2 = 0x05,
    _2L_900PIN_PIN_C2_TEST12B_OUT3 = 0x06,
    _2L_900PIN_PIN_C2_TEST12B_OUT4 = 0x07,
    _2L_900PIN_PIN_C2_TEST12B_OUT5 = 0x08,
    _2L_900PIN_PIN_C2_TEST12B_OUT6 = 0x09,
    _2L_900PIN_PIN_C2_TEST12B_OUT7 = 0x0A,
    _2L_900PIN_PIN_C2_TEST12B_OUT8 = 0x0B,
    _2L_900PIN_PIN_C2_TEST12B_OUT9 = 0x0C,
    _2L_900PIN_PIN_C2_TEST12B_OUT10 = 0x0D,
    _2L_900PIN_PIN_C2_TEST12B_OUT11 = 0x0E,
    _2L_900PIN_PIN_C2_NC = _2L_900PIN_PIN_C2_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_C2;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x108C
// MCU Ctrl : 0x222C at _2L_900PIN_PIN_C1_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_C1                       (_2L_900PIN_PIN_C1_NC)

typedef enum
{
    _2L_900PIN_PIN_C1_GPI = 0x00,
    _2L_900PIN_PIN_C1_GPO_PP = 0x01,
    _2L_900PIN_PIN_C1_GPO_OD = 0x02,
    _2L_900PIN_PIN_C1_TEST12B_OUT0 = 0x03,
    _2L_900PIN_PIN_C1_TEST12B_OUT1 = 0x04,
    _2L_900PIN_PIN_C1_TEST12B_OUT2 = 0x05,
    _2L_900PIN_PIN_C1_TEST12B_OUT3 = 0x06,
    _2L_900PIN_PIN_C1_TEST12B_OUT4 = 0x07,
    _2L_900PIN_PIN_C1_TEST12B_OUT5 = 0x08,
    _2L_900PIN_PIN_C1_TEST12B_OUT6 = 0x09,
    _2L_900PIN_PIN_C1_TEST12B_OUT7 = 0x0A,
    _2L_900PIN_PIN_C1_TEST12B_OUT8 = 0x0B,
    _2L_900PIN_PIN_C1_TEST12B_OUT9 = 0x0C,
    _2L_900PIN_PIN_C1_TEST12B_OUT10 = 0x0D,
    _2L_900PIN_PIN_C1_TEST12B_OUT11 = 0x0E,
    _2L_900PIN_PIN_C1_NC = _2L_900PIN_PIN_C1_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_C1;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x108D
// MCU Ctrl : 0x222D at _2L_900PIN_PIN_D2_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_D2                       (_2L_900PIN_PIN_D2_NC)

typedef enum
{
    _2L_900PIN_PIN_D2_GPI = 0x00,
    _2L_900PIN_PIN_D2_GPO_PP = 0x01,
    _2L_900PIN_PIN_D2_GPO_OD = 0x02,
    _2L_900PIN_PIN_D2_TEST12B_OUT0 = 0x03,
    _2L_900PIN_PIN_D2_TEST12B_OUT1 = 0x04,
    _2L_900PIN_PIN_D2_TEST12B_OUT2 = 0x05,
    _2L_900PIN_PIN_D2_TEST12B_OUT3 = 0x06,
    _2L_900PIN_PIN_D2_TEST12B_OUT4 = 0x07,
    _2L_900PIN_PIN_D2_TEST12B_OUT5 = 0x08,
    _2L_900PIN_PIN_D2_TEST12B_OUT6 = 0x09,
    _2L_900PIN_PIN_D2_TEST12B_OUT7 = 0x0A,
    _2L_900PIN_PIN_D2_TEST12B_OUT8 = 0x0B,
    _2L_900PIN_PIN_D2_TEST12B_OUT9 = 0x0C,
    _2L_900PIN_PIN_D2_TEST12B_OUT10 = 0x0D,
    _2L_900PIN_PIN_D2_TEST12B_OUT11 = 0x0E,
    _2L_900PIN_PIN_D2_NC = _2L_900PIN_PIN_D2_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_D2;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x108E
// MCU Ctrl : 0x222E at _2L_900PIN_PIN_D1_MCU_REG
//---------------------------------------------------------------------------
#define _2L_900PIN_PIN_D1                       (_2L_900PIN_PIN_D1_NC)

typedef enum
{
    _2L_900PIN_PIN_D1_GPI = 0x00,
    _2L_900PIN_PIN_D1_GPO_PP = 0x01,
    _2L_900PIN_PIN_D1_GPO_OD = 0x02,
    _2L_900PIN_PIN_D1_TEST12B_OUT0 = 0x03,
    _2L_900PIN_PIN_D1_TEST12B_OUT1 = 0x04,
    _2L_900PIN_PIN_D1_TEST12B_OUT2 = 0x05,
    _2L_900PIN_PIN_D1_TEST12B_OUT3 = 0x06,
    _2L_900PIN_PIN_D1_TEST12B_OUT4 = 0x07,
    _2L_900PIN_PIN_D1_TEST12B_OUT5 = 0x08,
    _2L_900PIN_PIN_D1_TEST12B_OUT6 = 0x09,
    _2L_900PIN_PIN_D1_TEST12B_OUT7 = 0x0A,
    _2L_900PIN_PIN_D1_TEST12B_OUT8 = 0x0B,
    _2L_900PIN_PIN_D1_TEST12B_OUT9 = 0x0C,
    _2L_900PIN_PIN_D1_TEST12B_OUT10 = 0x0D,
    _2L_900PIN_PIN_D1_TEST12B_OUT11 = 0x0E,
    _2L_900PIN_PIN_D1_NC = _2L_900PIN_PIN_D1_GPO_PP,
} EnumPinshareInfo2L_900PIN_PIN_D1;

