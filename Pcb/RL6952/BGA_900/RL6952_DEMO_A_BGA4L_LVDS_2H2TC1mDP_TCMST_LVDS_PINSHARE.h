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
// ID Code      : RL6952_DEMO_A_BGA4L_LVDS_2H2TC1mDP_TCMST_LVDS_PINSHARE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//////////////////////////////
// RL6952 Series Pin Share //
//////////////////////////////

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_N2
// Pinshare : 0x1000
// MCU Ctrl : 0xFE00 at _PIN_J4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_J4                                 (_PIN_J4_GPI)

typedef enum
{
    _PIN_J4_GPI = 0x00,
    _PIN_J4_GPO_PP = 0x01,
    _PIN_J4_GPO_OD = 0x02,
    _PIN_J4_DISP_FRAME_START_IN = 0x03,
    _PIN_J4_DISP_FRAME_START_OUT = 0x04,
    _PIN_J4_EXT_UART_TX_0_5 = 0x05,
    _PIN_J4_EXT_UART_TX_1_5 = 0x06,
    _PIN_J4_EXT_UART_TX_2_5 = 0x07,
    _PIN_J4_USB_SPI_CLK_0_4 = 0x08,
    _PIN_J4_USB_SPI_CLK_1_4 = 0x09,
    _PIN_J4_USB_SPI_CLK_2_4 = 0x0A,
    _PIN_J4_TEST12B_OUT3 = 0x0B,
    _PIN_J4_TEST12B_OUT4 = 0x0C,
    _PIN_J4_TEST12B_OUT5 = 0x0D,
    _PIN_J4_TEST12B_OUT6 = 0x0E,
    _PIN_J4_TEST12B_OUT7 = 0x0F,
    _PIN_J4_TEST12B_OUT8 = 0x10,
    _PIN_J4_TEST12B_OUT9 = 0x11,
    _PIN_J4_TEST12B_OUT10 = 0x12,
    _PIN_J4_TEST12B_OUT11 = 0x13,
    _PIN_J4_NC = _PIN_J4_GPO_PP,
} EnumPinshareInfoPINJ4;

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_P2
// Pinshare : 0x1001
// MCU Ctrl : 0xFE01 at _PIN_K4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_K4                                 (_PIN_K4_GPI)

typedef enum
{
    _PIN_K4_GPI = 0x00,
    _PIN_K4_GPO_PP = 0x01,
    _PIN_K4_GPO_OD = 0x02,
    _PIN_K4_INT0_0 = 0x03,
    _PIN_K4_INT1_0 = 0x04,
    _PIN_K4_EXT_UART_RX_0_5 = 0x05,
    _PIN_K4_EXT_UART_RX_1_5 = 0x06,
    _PIN_K4_EXT_UART_RX_2_5 = 0x07,
    _PIN_K4_PWM1_PP = 0x08,
    _PIN_K4_PWM1_OD = 0x09,
    _PIN_K4_PWM1_DIMMING_PP = 0x0A,
    _PIN_K4_PWM1_DIMMING = 0x0B,
    _PIN_K4_USB_SPI_CLK_0_5 = 0x0C,
    _PIN_K4_USB_SPI_CLK_1_5 = 0x0D,
    _PIN_K4_USB_SPI_CLK_2_5 = 0x0E,
    _PIN_K4_TEST12B_OUT3 = 0x0F,
    _PIN_K4_TEST12B_OUT4 = 0x10,
    _PIN_K4_TEST12B_OUT5 = 0x11,
    _PIN_K4_TEST12B_OUT6 = 0x12,
    _PIN_K4_TEST12B_OUT7 = 0x13,
    _PIN_K4_TEST12B_OUT8 = 0x14,
    _PIN_K4_TEST12B_OUT9 = 0x15,
    _PIN_K4_TEST12B_OUT10 = 0x16,
    _PIN_K4_TEST12B_OUT11 = 0x17,
    _PIN_K4_NC = _PIN_K4_GPO_PP,
} EnumPinshareInfoPINK4;

//---------------------------------------------------------------------------
// Function : DP_HOT_PLUG_2
// Pinshare : 0x1002
// MCU Ctrl : 0xFE02 at _PIN_H4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_H4                                 (_PIN_H4_GPO_PP)

typedef enum
{
    _PIN_H4_GPI = 0x00,
    _PIN_H4_GPO_PP = 0x01,
    _PIN_H4_GPO_OD = 0x02,
    _PIN_H4_PWM_IN_0_0 = 0x03,
    _PIN_H4_PWM1_PP = 0x04,
    _PIN_H4_PWM1_OD = 0x05,
    _PIN_H4_PWM1_DIMMING_PP = 0x06,
    _PIN_H4_PWM1_DIMMING = 0x07,
    _PIN_H4_EXT_UART_TX_0_4 = 0x08,
    _PIN_H4_EXT_UART_TX_1_4 = 0x09,
    _PIN_H4_EXT_UART_TX_2_4 = 0x0A,
    _PIN_H4_TCON13 = 0x0B,
    _PIN_H4_TEST12B_OUT0 = 0x0C,
    _PIN_H4_TEST12B_OUT1 = 0x0D,
    _PIN_H4_TEST12B_OUT2 = 0x0E,
    _PIN_H4_TEST12B_OUT3 = 0x0F,
    _PIN_H4_TEST12B_OUT4 = 0x10,
    _PIN_H4_TEST12B_OUT5 = 0x11,
    _PIN_H4_TEST12B_OUT6 = 0x12,
    _PIN_H4_TEST12B_OUT7 = 0x13,
    _PIN_H4_TEST12B_OUT8 = 0x14,
    _PIN_H4_TEST12B_OUT9 = 0x15,
    _PIN_H4_TEST12B_OUT10 = 0x16,
    _PIN_H4_TEST12B_OUT11 = 0x17,
    _PIN_H4_NC = _PIN_H4_GPO_PP,
} EnumPinshareInfoPINH4;

//---------------------------------------------------------------------------
// Function : DP_CABLE_DET_2
// Pinshare : 0x1003
// MCU Ctrl : 0xFE03 at _PIN_G6_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_G6                                 (_PIN_G6_GPI)

typedef enum
{
    _PIN_G6_GPI = 0x00,
    _PIN_G6_GPO_PP = 0x01,
    _PIN_G6_GPO_OD = 0x02,
    _PIN_G6_EXT_UART_RX_0_4 = 0x03,
    _PIN_G6_EXT_UART_RX_1_4 = 0x04,
    _PIN_G6_EXT_UART_RX_2_4 = 0x05,
    _PIN_G6_PWM2_PP = 0x06,
    _PIN_G6_PWM2_OD = 0x07,
    _PIN_G6_PWM2_DIMMING_PP = 0x08,
    _PIN_G6_PWM2_DIMMING = 0x09,
    _PIN_G6_TCON8 = 0x0A,
    _PIN_G6_TEST12B_OUT0 = 0x0B,
    _PIN_G6_TEST12B_OUT1 = 0x0C,
    _PIN_G6_TEST12B_OUT2 = 0x0D,
    _PIN_G6_TEST12B_OUT3 = 0x0E,
    _PIN_G6_TEST12B_OUT4 = 0x0F,
    _PIN_G6_TEST12B_OUT5 = 0x10,
    _PIN_G6_TEST12B_OUT6 = 0x11,
    _PIN_G6_TEST12B_OUT7 = 0x12,
    _PIN_G6_TEST12B_OUT8 = 0x13,
    _PIN_G6_TEST12B_OUT9 = 0x14,
    _PIN_G6_TEST12B_OUT10 = 0x15,
    _PIN_G6_TEST12B_OUT11 = 0x16,
    _PIN_G6_NC = _PIN_G6_GPO_PP,
} EnumPinshareInfoPING6;

//---------------------------------------------------------------------------
// Function : DPTX_HPD
// Pinshare : 0x1004
// MCU Ctrl : 0xFE04 at _PIN_AD4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AD4                                (_PIN_AD4_DPTX_HPD_0_ORG)

typedef enum
{
    _PIN_AD4_GPI = 0x00,
    _PIN_AD4_GPO_PP = 0x01,
    _PIN_AD4_GPO_OD = 0x02,
    _PIN_AD4_DPTX_HPD_0_ORG = 0x03,
    _PIN_AD4_CLKO = 0x04,
    _PIN_AD4_TEST12B_OUT0 = 0x05,
    _PIN_AD4_TEST12B_OUT1 = 0x06,
    _PIN_AD4_TEST12B_OUT2 = 0x07,
    _PIN_AD4_TEST12B_OUT3 = 0x08,
    _PIN_AD4_TEST12B_OUT4 = 0x09,
    _PIN_AD4_TEST12B_OUT5 = 0x0A,
    _PIN_AD4_TEST12B_OUT6 = 0x0B,
    _PIN_AD4_TEST12B_OUT7 = 0x0C,
    _PIN_AD4_TEST12B_OUT8 = 0x0D,
    _PIN_AD4_TEST12B_OUT9 = 0x0E,
    _PIN_AD4_TEST12B_OUT10 = 0x0F,
    _PIN_AD4_TEST12B_OUT11 = 0x10,
    _PIN_AD4_NC = _PIN_AD4_GPO_PP,
} EnumPinshareInfoPINAD4;

//---------------------------------------------------------------------------
// Function : D0_SBU2
// Pinshare : 0x1005
// MCU Ctrl : 0xFE05 at _PIN_W4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_W4                                 (_PIN_W4_DPRX_AUX_P_0)

typedef enum
{
    _PIN_W4_GPI = 0x00,
    _PIN_W4_GPO_PP = 0x01,
    _PIN_W4_GPO_OD = 0x02,
    _PIN_W4_DPRX_AUX_P_0 = 0x03,
    _PIN_W4_TEST12B_OUT0 = 0x04,
    _PIN_W4_TEST12B_OUT1 = 0x05,
    _PIN_W4_TEST12B_OUT2 = 0x06,
    _PIN_W4_TEST12B_OUT3 = 0x07,
    _PIN_W4_TEST12B_OUT4 = 0x08,
    _PIN_W4_TEST12B_OUT5 = 0x09,
    _PIN_W4_TEST12B_OUT6 = 0x0A,
    _PIN_W4_TEST12B_OUT7 = 0x0B,
    _PIN_W4_TEST12B_OUT8 = 0x0C,
    _PIN_W4_TEST12B_OUT9 = 0x0D,
    _PIN_W4_TEST12B_OUT10 = 0x0E,
    _PIN_W4_TEST12B_OUT11 = 0x0F,
    _PIN_W4_NC = _PIN_W4_GPO_PP,
} EnumPinshareInfoPINW4;

//---------------------------------------------------------------------------
// Function : D0_SBU1
// Pinshare : 0x1006
// MCU Ctrl : 0xFE06 at _PIN_W5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_W5                                 (_PIN_W5_DPRX_AUX_N_0)

typedef enum
{
    _PIN_W5_GPI = 0x00,
    _PIN_W5_GPO_PP = 0x01,
    _PIN_W5_GPO_OD = 0x02,
    _PIN_W5_DPRX_AUX_N_0 = 0x03,
    _PIN_W5_TEST12B_OUT0 = 0x04,
    _PIN_W5_TEST12B_OUT1 = 0x05,
    _PIN_W5_TEST12B_OUT2 = 0x06,
    _PIN_W5_TEST12B_OUT3 = 0x07,
    _PIN_W5_TEST12B_OUT4 = 0x08,
    _PIN_W5_TEST12B_OUT5 = 0x09,
    _PIN_W5_TEST12B_OUT6 = 0x0A,
    _PIN_W5_TEST12B_OUT7 = 0x0B,
    _PIN_W5_TEST12B_OUT8 = 0x0C,
    _PIN_W5_TEST12B_OUT9 = 0x0D,
    _PIN_W5_TEST12B_OUT10 = 0x0E,
    _PIN_W5_TEST12B_OUT11 = 0x0F,
    _PIN_W5_NC = _PIN_W5_GPO_PP,
} EnumPinshareInfoPINW5;

//---------------------------------------------------------------------------
// Function : PD_GPIO0
// Pinshare : 0x1007
// MCU Ctrl : 0xFE07 at _PIN_T4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_T4                                 (_PIN_T4_GPI)

typedef enum
{
    _PIN_T4_GPI = 0x00,
    _PIN_T4_GPO_PP = 0x01,
    _PIN_T4_GPO_OD = 0x02,
    _PIN_T4_PWM_OUT_0_0 = 0x03,
    _PIN_T4_PWM3_PP = 0x04,
    _PIN_T4_PWM3_OD = 0x05,
    _PIN_T4_PWM3_DIMMING_PP = 0x06,
    _PIN_T4_PWM3_DIMMING = 0x07,
    _PIN_T4_TCON6 = 0x08,
    _PIN_T4_TEST12B_OUT0 = 0x09,
    _PIN_T4_TEST12B_OUT1 = 0x0A,
    _PIN_T4_TEST12B_OUT2 = 0x0B,
    _PIN_T4_TEST12B_OUT3 = 0x0C,
    _PIN_T4_TEST12B_OUT4 = 0x0D,
    _PIN_T4_TEST12B_OUT5 = 0x0E,
    _PIN_T4_TEST12B_OUT6 = 0x0F,
    _PIN_T4_TEST12B_OUT7 = 0x10,
    _PIN_T4_TEST12B_OUT8 = 0x11,
    _PIN_T4_TEST12B_OUT9 = 0x12,
    _PIN_T4_TEST12B_OUT10 = 0x13,
    _PIN_T4_TEST12B_OUT11 = 0x14,
    _PIN_T4_NC = _PIN_T4_GPO_PP,
} EnumPinshareInfoPINT4;

//---------------------------------------------------------------------------
// Function : D1_10B_CH3
// Pinshare : 0x1008
// MCU Ctrl : 0xFE08 at _PIN_AA4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AA4                                (_PIN_AA4_10B_ADC_3)

typedef enum
{
    _PIN_AA4_GPI = 0x00,
    _PIN_AA4_GPO_PP = 0x01,
    _PIN_AA4_GPO_OD = 0x02,
    _PIN_AA4_10B_ADC_3 = 0x03,
    _PIN_AA4_TEST12B_OUT0 = 0x04,
    _PIN_AA4_TEST12B_OUT1 = 0x05,
    _PIN_AA4_TEST12B_OUT2 = 0x06,
    _PIN_AA4_TEST12B_OUT3 = 0x07,
    _PIN_AA4_TEST12B_OUT4 = 0x08,
    _PIN_AA4_TEST12B_OUT5 = 0x09,
    _PIN_AA4_TEST12B_OUT6 = 0x0A,
    _PIN_AA4_TEST12B_OUT7 = 0x0B,
    _PIN_AA4_TEST12B_OUT8 = 0x0C,
    _PIN_AA4_TEST12B_OUT9 = 0x0D,
    _PIN_AA4_TEST12B_OUT10 = 0x0E,
    _PIN_AA4_TEST12B_OUT11 = 0x0F,
    _PIN_AA4_NC = _PIN_AA4_GPO_PP,
} EnumPinshareInfoPINAA4;

//---------------------------------------------------------------------------
// Function : D1_10B_CH2
// Pinshare : 0x1009
// MCU Ctrl : 0xFE09 at _PIN_AA5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AA5                                (_PIN_AA5_10B_ADC_2)

typedef enum
{
    _PIN_AA5_GPI = 0x00,
    _PIN_AA5_GPO_PP = 0x01,
    _PIN_AA5_GPO_OD = 0x02,
    _PIN_AA5_10B_ADC_2 = 0x03,
    _PIN_AA5_TEST12B_OUT0 = 0x04,
    _PIN_AA5_TEST12B_OUT1 = 0x05,
    _PIN_AA5_TEST12B_OUT2 = 0x06,
    _PIN_AA5_TEST12B_OUT3 = 0x07,
    _PIN_AA5_TEST12B_OUT4 = 0x08,
    _PIN_AA5_TEST12B_OUT5 = 0x09,
    _PIN_AA5_TEST12B_OUT6 = 0x0A,
    _PIN_AA5_TEST12B_OUT7 = 0x0B,
    _PIN_AA5_TEST12B_OUT8 = 0x0C,
    _PIN_AA5_TEST12B_OUT9 = 0x0D,
    _PIN_AA5_TEST12B_OUT10 = 0x0E,
    _PIN_AA5_TEST12B_OUT11 = 0x0F,
    _PIN_AA5_NC = _PIN_AA5_GPO_PP,
} EnumPinshareInfoPINAA5;

//---------------------------------------------------------------------------
// Function : D0_10B_CH1
// Pinshare : 0x100A
// MCU Ctrl : 0xFE0A at _PIN_AB4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AB4                                (_PIN_AB4_10B_ADC_1)

typedef enum
{
    _PIN_AB4_GPI = 0x00,
    _PIN_AB4_GPO_PP = 0x01,
    _PIN_AB4_GPO_OD = 0x02,
    _PIN_AB4_10B_ADC_1 = 0x03,
    _PIN_AB4_TEST12B_OUT0 = 0x04,
    _PIN_AB4_TEST12B_OUT1 = 0x05,
    _PIN_AB4_TEST12B_OUT2 = 0x06,
    _PIN_AB4_TEST12B_OUT3 = 0x07,
    _PIN_AB4_TEST12B_OUT4 = 0x08,
    _PIN_AB4_TEST12B_OUT5 = 0x09,
    _PIN_AB4_TEST12B_OUT6 = 0x0A,
    _PIN_AB4_TEST12B_OUT7 = 0x0B,
    _PIN_AB4_TEST12B_OUT8 = 0x0C,
    _PIN_AB4_TEST12B_OUT9 = 0x0D,
    _PIN_AB4_TEST12B_OUT10 = 0x0E,
    _PIN_AB4_TEST12B_OUT11 = 0x0F,
    _PIN_AB4_NC = _PIN_AB4_GPO_PP,
} EnumPinshareInfoPINAB4;

//---------------------------------------------------------------------------
// Function : D0_10B_CH0
// Pinshare : 0x100B
// MCU Ctrl : 0xFE0B at _PIN_AB5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AB5                                (_PIN_AB5_10B_ADC_0)

typedef enum
{
    _PIN_AB5_GPI = 0x00,
    _PIN_AB5_GPO_PP = 0x01,
    _PIN_AB5_GPO_OD = 0x02,
    _PIN_AB5_10B_ADC_0 = 0x03,
    _PIN_AB5_TEST12B_OUT0 = 0x04,
    _PIN_AB5_TEST12B_OUT1 = 0x05,
    _PIN_AB5_TEST12B_OUT2 = 0x06,
    _PIN_AB5_TEST12B_OUT3 = 0x07,
    _PIN_AB5_TEST12B_OUT4 = 0x08,
    _PIN_AB5_TEST12B_OUT5 = 0x09,
    _PIN_AB5_TEST12B_OUT6 = 0x0A,
    _PIN_AB5_TEST12B_OUT7 = 0x0B,
    _PIN_AB5_TEST12B_OUT8 = 0x0C,
    _PIN_AB5_TEST12B_OUT9 = 0x0D,
    _PIN_AB5_TEST12B_OUT10 = 0x0E,
    _PIN_AB5_TEST12B_OUT11 = 0x0F,
    _PIN_AB5_NC = _PIN_AB5_GPO_PP,
} EnumPinshareInfoPINAB5;

//---------------------------------------------------------------------------
// Function : CEC
// Pinshare : 0x100C
// MCU Ctrl : 0xFE0C at _PIN_AE4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AE4                                (_PIN_AE4_CEC)

typedef enum
{
    _PIN_AE4_GPI = 0x00,
    _PIN_AE4_GPO_PP = 0x01,
    _PIN_AE4_GPO_OD = 0x02,
    _PIN_AE4_CEC = 0x03,
    _PIN_AE4_TCON13 = 0x04,
    _PIN_AE4_TEST12B_OUT0 = 0x05,
    _PIN_AE4_TEST12B_OUT1 = 0x06,
    _PIN_AE4_TEST12B_OUT2 = 0x07,
    _PIN_AE4_TEST12B_OUT3 = 0x08,
    _PIN_AE4_TEST12B_OUT4 = 0x09,
    _PIN_AE4_TEST12B_OUT5 = 0x0A,
    _PIN_AE4_TEST12B_OUT6 = 0x0B,
    _PIN_AE4_TEST12B_OUT7 = 0x0C,
    _PIN_AE4_TEST12B_OUT8 = 0x0D,
    _PIN_AE4_TEST12B_OUT9 = 0x0E,
    _PIN_AE4_TEST12B_OUT10 = 0x0F,
    _PIN_AE4_TEST12B_OUT11 = 0x10,
    _PIN_AE4_NC = _PIN_AE4_GPO_PP,
} EnumPinshareInfoPINAE4;

//---------------------------------------------------------------------------
// Function : DPTX_AUX_N
// Pinshare : 0x100D
// MCU Ctrl : 0xFE0D at _PIN_AE5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AE5                                (_PIN_AE5_DPTX_AUX_N_0)

typedef enum
{
    _PIN_AE5_GPI = 0x00,
    _PIN_AE5_GPO_PP = 0x01,
    _PIN_AE5_GPO_OD = 0x02,
    _PIN_AE5_DPTX_AUX_N_0 = 0x03,
    _PIN_AE5_TEST12B_OUT0 = 0x04,
    _PIN_AE5_TEST12B_OUT1 = 0x05,
    _PIN_AE5_TEST12B_OUT2 = 0x06,
    _PIN_AE5_TEST12B_OUT3 = 0x07,
    _PIN_AE5_TEST12B_OUT4 = 0x08,
    _PIN_AE5_TEST12B_OUT5 = 0x09,
    _PIN_AE5_TEST12B_OUT6 = 0x0A,
    _PIN_AE5_TEST12B_OUT7 = 0x0B,
    _PIN_AE5_TEST12B_OUT8 = 0x0C,
    _PIN_AE5_TEST12B_OUT9 = 0x0D,
    _PIN_AE5_TEST12B_OUT10 = 0x0E,
    _PIN_AE5_TEST12B_OUT11 = 0x0F,
    _PIN_AE5_NC = _PIN_AE5_GPO_PP,
} EnumPinshareInfoPINAE5;

//---------------------------------------------------------------------------
// Function : DPTX_AUX_P
// Pinshare : 0x100E
// MCU Ctrl : 0xFE0E at _PIN_AD5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AD5                                (_PIN_AD5_DPTX_AUX_P_0)

typedef enum
{
    _PIN_AD5_GPI = 0x00,
    _PIN_AD5_GPO_PP = 0x01,
    _PIN_AD5_GPO_OD = 0x02,
    _PIN_AD5_DPTX_AUX_P_0 = 0x03,
    _PIN_AD5_TEST12B_OUT0 = 0x04,
    _PIN_AD5_TEST12B_OUT1 = 0x05,
    _PIN_AD5_TEST12B_OUT2 = 0x06,
    _PIN_AD5_TEST12B_OUT3 = 0x07,
    _PIN_AD5_TEST12B_OUT4 = 0x08,
    _PIN_AD5_TEST12B_OUT5 = 0x09,
    _PIN_AD5_TEST12B_OUT6 = 0x0A,
    _PIN_AD5_TEST12B_OUT7 = 0x0B,
    _PIN_AD5_TEST12B_OUT8 = 0x0C,
    _PIN_AD5_TEST12B_OUT9 = 0x0D,
    _PIN_AD5_TEST12B_OUT10 = 0x0E,
    _PIN_AD5_TEST12B_OUT11 = 0x0F,
    _PIN_AD5_NC = _PIN_AD5_GPO_PP,
} EnumPinshareInfoPINAD5;

//---------------------------------------------------------------------------
// Function : FLASH_WP
// Pinshare : 0x100F
// MCU Ctrl : 0xFE0F at _PIN_AF6_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AF6                                (_PIN_AF6_GPO_PP)

typedef enum
{
    _PIN_AF6_GPI = 0x00,
    _PIN_AF6_GPO_PP = 0x01,
    _PIN_AF6_GPO_OD = 0x02,
    _PIN_AF6_TEST12B_OUT0 = 0x03,
    _PIN_AF6_TEST12B_OUT1 = 0x04,
    _PIN_AF6_TEST12B_OUT2 = 0x05,
    _PIN_AF6_TEST12B_OUT3 = 0x06,
    _PIN_AF6_TEST12B_OUT4 = 0x07,
    _PIN_AF6_TEST12B_OUT5 = 0x08,
    _PIN_AF6_TEST12B_OUT6 = 0x09,
    _PIN_AF6_TEST12B_OUT7 = 0x0A,
    _PIN_AF6_TEST12B_OUT8 = 0x0B,
    _PIN_AF6_TEST12B_OUT9 = 0x0C,
    _PIN_AF6_TEST12B_OUT10 = 0x0D,
    _PIN_AF6_TEST12B_OUT11 = 0x0E,
    _PIN_AF6_NC = _PIN_AF6_GPO_PP,
} EnumPinshareInfoPINAF6;

//---------------------------------------------------------------------------
// Function : EEPROM_WP
// Pinshare : 0x1010
// MCU Ctrl : 0xFE10 at _PIN_AF7_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AF7                                (_PIN_AF7_GPO_OD)

typedef enum
{
    _PIN_AF7_GPI = 0x00,
    _PIN_AF7_GPO_PP = 0x01,
    _PIN_AF7_GPO_OD = 0x02,
    _PIN_AF7_PWM4_PP = 0x03,
    _PIN_AF7_PWM4_OD = 0x04,
    _PIN_AF7_PWM4_DIMMING_PP = 0x05,
    _PIN_AF7_PWM4_DIMMING = 0x06,
    _PIN_AF7_TEST12B_OUT0 = 0x07,
    _PIN_AF7_TEST12B_OUT1 = 0x08,
    _PIN_AF7_TEST12B_OUT2 = 0x09,
    _PIN_AF7_TEST12B_OUT3 = 0x0A,
    _PIN_AF7_TEST12B_OUT4 = 0x0B,
    _PIN_AF7_TEST12B_OUT5 = 0x0C,
    _PIN_AF7_TEST12B_OUT6 = 0x0D,
    _PIN_AF7_TEST12B_OUT7 = 0x0E,
    _PIN_AF7_TEST12B_OUT8 = 0x0F,
    _PIN_AF7_TEST12B_OUT9 = 0x10,
    _PIN_AF7_TEST12B_OUT10 = 0x11,
    _PIN_AF7_TEST12B_OUT11 = 0x12,
    _PIN_AF7_NC = _PIN_AF7_GPO_PP,
} EnumPinshareInfoPINAF7;

//---------------------------------------------------------------------------
// Function : EE_SCL
// Pinshare : 0x1011
// MCU Ctrl : 0xFE11 at _PIN_AG6_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AG6                                (_PIN_AG6_EEIICSCL)

typedef enum
{
    _PIN_AG6_GPI = 0x00,
    _PIN_AG6_GPO_PP = 0x01,
    _PIN_AG6_GPO_OD = 0x02,
    _PIN_AG6_EEIICSCL = 0x03,
    _PIN_AG6_TEST12B_OUT0 = 0x04,
    _PIN_AG6_TEST12B_OUT1 = 0x05,
    _PIN_AG6_TEST12B_OUT2 = 0x06,
    _PIN_AG6_TEST12B_OUT3 = 0x07,
    _PIN_AG6_TEST12B_OUT4 = 0x08,
    _PIN_AG6_TEST12B_OUT5 = 0x09,
    _PIN_AG6_TEST12B_OUT6 = 0x0A,
    _PIN_AG6_TEST12B_OUT7 = 0x0B,
    _PIN_AG6_TEST12B_OUT8 = 0x0C,
    _PIN_AG6_TEST12B_OUT9 = 0x0D,
    _PIN_AG6_TEST12B_OUT10 = 0x0E,
    _PIN_AG6_TEST12B_OUT11 = 0x0F,
    _PIN_AG6_NC = _PIN_AG6_GPO_PP,
} EnumPinshareInfoPINAG6;

//---------------------------------------------------------------------------
// Function : EE_SDA
// Pinshare : 0x1012
// MCU Ctrl : 0xFE12 at _PIN_AG7_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AG7                                (_PIN_AG7_EEIICSDA)

typedef enum
{
    _PIN_AG7_GPI = 0x00,
    _PIN_AG7_GPO_PP = 0x01,
    _PIN_AG7_GPO_OD = 0x02,
    _PIN_AG7_EEIICSDA = 0x03,
    _PIN_AG7_TEST12B_OUT0 = 0x04,
    _PIN_AG7_TEST12B_OUT1 = 0x05,
    _PIN_AG7_TEST12B_OUT2 = 0x06,
    _PIN_AG7_TEST12B_OUT3 = 0x07,
    _PIN_AG7_TEST12B_OUT4 = 0x08,
    _PIN_AG7_TEST12B_OUT5 = 0x09,
    _PIN_AG7_TEST12B_OUT6 = 0x0A,
    _PIN_AG7_TEST12B_OUT7 = 0x0B,
    _PIN_AG7_TEST12B_OUT8 = 0x0C,
    _PIN_AG7_TEST12B_OUT9 = 0x0D,
    _PIN_AG7_TEST12B_OUT10 = 0x0E,
    _PIN_AG7_TEST12B_OUT11 = 0x0F,
    _PIN_AG7_NC = _PIN_AG7_GPO_PP,
} EnumPinshareInfoPINAG7;

//---------------------------------------------------------------------------
// Function : D0_VMON
// Pinshare : 0x1013
// MCU Ctrl : 0xFE13 at _PIN_AF12_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AF12                               (_PIN_AF12_A_ADC0_0_0)

typedef enum
{
    _PIN_AF12_GPI = 0x00,
    _PIN_AF12_GPO_PP = 0x01,
    _PIN_AF12_GPO_OD = 0x02,
    _PIN_AF12_A_ADC0_0_0 = 0x03,
    _PIN_AF12_INT0_4 = 0x04,
    _PIN_AF12_INT1_4 = 0x05,
    _PIN_AF12_TEST12B_OUT0 = 0x06,
    _PIN_AF12_TEST12B_OUT1 = 0x07,
    _PIN_AF12_TEST12B_OUT2 = 0x08,
    _PIN_AF12_TEST12B_OUT3 = 0x09,
    _PIN_AF12_TEST12B_OUT4 = 0x0A,
    _PIN_AF12_TEST12B_OUT5 = 0x0B,
    _PIN_AF12_TEST12B_OUT6 = 0x0C,
    _PIN_AF12_TEST12B_OUT7 = 0x0D,
    _PIN_AF12_TEST12B_OUT8 = 0x0E,
    _PIN_AF12_TEST12B_OUT9 = 0x0F,
    _PIN_AF12_TEST12B_OUT10 = 0x10,
    _PIN_AF12_TEST12B_OUT11 = 0x11,
    _PIN_AF12_NC = _PIN_AF12_GPO_PP,
} EnumPinshareInfoPINAF12;

//---------------------------------------------------------------------------
// Function : D1_VMON
// Pinshare : 0x1014
// MCU Ctrl : 0xFE14 at _PIN_AF11_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AF11                               (_PIN_AF11_A_ADC1_0_0)

typedef enum
{
    _PIN_AF11_GPI = 0x00,
    _PIN_AF11_GPO_PP = 0x01,
    _PIN_AF11_GPO_OD = 0x02,
    _PIN_AF11_A_ADC1_0_0 = 0x03,
    _PIN_AF11_INT0_1 = 0x04,
    _PIN_AF11_INT1_1 = 0x05,
    _PIN_AF11_TEST12B_OUT0 = 0x06,
    _PIN_AF11_TEST12B_OUT1 = 0x07,
    _PIN_AF11_TEST12B_OUT2 = 0x08,
    _PIN_AF11_TEST12B_OUT3 = 0x09,
    _PIN_AF11_TEST12B_OUT4 = 0x0A,
    _PIN_AF11_TEST12B_OUT5 = 0x0B,
    _PIN_AF11_TEST12B_OUT6 = 0x0C,
    _PIN_AF11_TEST12B_OUT7 = 0x0D,
    _PIN_AF11_TEST12B_OUT8 = 0x0E,
    _PIN_AF11_TEST12B_OUT9 = 0x0F,
    _PIN_AF11_TEST12B_OUT10 = 0x10,
    _PIN_AF11_TEST12B_OUT11 = 0x11,
    _PIN_AF11_NC = _PIN_AF11_GPO_PP,
} EnumPinshareInfoPINAF11;

//---------------------------------------------------------------------------
// Function : LP_VMON_UFP
// Pinshare : 0x1015
// MCU Ctrl : 0xFE15 at _PIN_AF10_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AF10                               (_PIN_AF10_A_ADC2_0_0)

typedef enum
{
    _PIN_AF10_GPI = 0x00,
    _PIN_AF10_GPO_PP = 0x01,
    _PIN_AF10_GPO_OD = 0x02,
    _PIN_AF10_A_ADC2_0_0 = 0x03,
    _PIN_AF10_TYPEC_GPIO2_1_PP = 0x04,
    _PIN_AF10_TYPEC_GPIO2_1_OD = 0x05,
    _PIN_AF10_TYPEC_GPIO3_1_PP = 0x06,
    _PIN_AF10_TYPEC_GPIO3_1_OD = 0x07,
    _PIN_AF10_TEST12B_OUT0 = 0x08,
    _PIN_AF10_TEST12B_OUT1 = 0x09,
    _PIN_AF10_TEST12B_OUT2 = 0x0A,
    _PIN_AF10_TEST12B_OUT3 = 0x0B,
    _PIN_AF10_TEST12B_OUT4 = 0x0C,
    _PIN_AF10_TEST12B_OUT5 = 0x0D,
    _PIN_AF10_TEST12B_OUT6 = 0x0E,
    _PIN_AF10_TEST12B_OUT7 = 0x0F,
    _PIN_AF10_TEST12B_OUT8 = 0x10,
    _PIN_AF10_TEST12B_OUT9 = 0x11,
    _PIN_AF10_TEST12B_OUT10 = 0x12,
    _PIN_AF10_TEST12B_OUT11 = 0x13,
    _PIN_AF10_NC = _PIN_AF10_GPO_PP,
} EnumPinshareInfoPINAF10;

//---------------------------------------------------------------------------
// Function : DP_CFG2
// Pinshare : 0x1016
// MCU Ctrl : 0xFE16 at _PIN_AF9_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AF9                                (_PIN_AF9_A_ADC3_0_0)

typedef enum
{
    _PIN_AF9_GPI = 0x00,
    _PIN_AF9_GPO_PP = 0x01,
    _PIN_AF9_GPO_OD = 0x02,
    _PIN_AF9_A_ADC3_0_0 = 0x03,
    _PIN_AF9_TYPEC_GPIO0_1_PP = 0x04,
    _PIN_AF9_TYPEC_GPIO0_1_OD = 0x05,
    _PIN_AF9_TYPEC_GPIO1_1_PP = 0x06,
    _PIN_AF9_TYPEC_GPIO1_1_OD = 0x07,
    _PIN_AF9_TEST12B_OUT0 = 0x08,
    _PIN_AF9_TEST12B_OUT1 = 0x09,
    _PIN_AF9_TEST12B_OUT2 = 0x0A,
    _PIN_AF9_TEST12B_OUT3 = 0x0B,
    _PIN_AF9_TEST12B_OUT4 = 0x0C,
    _PIN_AF9_TEST12B_OUT5 = 0x0D,
    _PIN_AF9_TEST12B_OUT6 = 0x0E,
    _PIN_AF9_TEST12B_OUT7 = 0x0F,
    _PIN_AF9_TEST12B_OUT8 = 0x10,
    _PIN_AF9_TEST12B_OUT9 = 0x11,
    _PIN_AF9_TEST12B_OUT10 = 0x12,
    _PIN_AF9_TEST12B_OUT11 = 0x13,
    _PIN_AF9_NC = _PIN_AF9_GPO_PP,
} EnumPinshareInfoPINAF9;

//---------------------------------------------------------------------------
// Function : LED1
// Pinshare : 0x1017
// MCU Ctrl : 0xFE17 at _PIN_AG12_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AG12                               (_PIN_AG12_GPO_PP)

typedef enum
{
    _PIN_AG12_GPI = 0x00,
    _PIN_AG12_GPO_PP = 0x01,
    _PIN_AG12_GPO_OD = 0x02,
    _PIN_AG12_A_ADC0_1_0 = 0x03,
    _PIN_AG12_TEST12B_OUT0 = 0x04,
    _PIN_AG12_TEST12B_OUT1 = 0x05,
    _PIN_AG12_TEST12B_OUT2 = 0x06,
    _PIN_AG12_TEST12B_OUT3 = 0x07,
    _PIN_AG12_TEST12B_OUT4 = 0x08,
    _PIN_AG12_TEST12B_OUT5 = 0x09,
    _PIN_AG12_TEST12B_OUT6 = 0x0A,
    _PIN_AG12_TEST12B_OUT7 = 0x0B,
    _PIN_AG12_TEST12B_OUT8 = 0x0C,
    _PIN_AG12_TEST12B_OUT9 = 0x0D,
    _PIN_AG12_TEST12B_OUT10 = 0x0E,
    _PIN_AG12_TEST12B_OUT11 = 0x0F,
    _PIN_AG12_NC = _PIN_AG12_GPO_PP,
} EnumPinshareInfoPINAG12;

//---------------------------------------------------------------------------
// Function : LED2
// Pinshare : 0x1018
// MCU Ctrl : 0xFE18 at _PIN_AG11_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AG11                               (_PIN_AG11_GPO_PP)

typedef enum
{
    _PIN_AG11_GPI = 0x00,
    _PIN_AG11_GPO_PP = 0x01,
    _PIN_AG11_GPO_OD = 0x02,
    _PIN_AG11_A_ADC1_1_0 = 0x03,
    _PIN_AG11_TEST12B_OUT0 = 0x04,
    _PIN_AG11_TEST12B_OUT1 = 0x05,
    _PIN_AG11_TEST12B_OUT2 = 0x06,
    _PIN_AG11_TEST12B_OUT3 = 0x07,
    _PIN_AG11_TEST12B_OUT4 = 0x08,
    _PIN_AG11_TEST12B_OUT5 = 0x09,
    _PIN_AG11_TEST12B_OUT6 = 0x0A,
    _PIN_AG11_TEST12B_OUT7 = 0x0B,
    _PIN_AG11_TEST12B_OUT8 = 0x0C,
    _PIN_AG11_TEST12B_OUT9 = 0x0D,
    _PIN_AG11_TEST12B_OUT10 = 0x0E,
    _PIN_AG11_TEST12B_OUT11 = 0x0F,
    _PIN_AG11_NC = _PIN_AG11_GPO_PP,
} EnumPinshareInfoPINAG11;

//---------------------------------------------------------------------------
// Function : ADC_KEY1
// Pinshare : 0x1019
// MCU Ctrl : 0xFE19 at _PIN_AG10_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AG10                               (_PIN_AG10_A_ADC2_1_0)

typedef enum
{
    _PIN_AG10_GPI = 0x00,
    _PIN_AG10_GPO_PP = 0x01,
    _PIN_AG10_GPO_OD = 0x02,
    _PIN_AG10_A_ADC2_1_0 = 0x03,
    _PIN_AG10_EXT_UART_TX_0_0 = 0x04,
    _PIN_AG10_EXT_UART_TX_1_0 = 0x05,
    _PIN_AG10_EXT_UART_TX_2_0 = 0x06,
    _PIN_AG10_TEST12B_OUT0 = 0x07,
    _PIN_AG10_TEST12B_OUT1 = 0x08,
    _PIN_AG10_TEST12B_OUT2 = 0x09,
    _PIN_AG10_TEST12B_OUT3 = 0x0A,
    _PIN_AG10_TEST12B_OUT4 = 0x0B,
    _PIN_AG10_TEST12B_OUT5 = 0x0C,
    _PIN_AG10_TEST12B_OUT6 = 0x0D,
    _PIN_AG10_TEST12B_OUT7 = 0x0E,
    _PIN_AG10_TEST12B_OUT8 = 0x0F,
    _PIN_AG10_TEST12B_OUT9 = 0x10,
    _PIN_AG10_TEST12B_OUT10 = 0x11,
    _PIN_AG10_TEST12B_OUT11 = 0x12,
    _PIN_AG10_NC = _PIN_AG10_GPO_PP,
} EnumPinshareInfoPINAG10;

//---------------------------------------------------------------------------
// Function : ADC_KEY2
// Pinshare : 0x101A
// MCU Ctrl : 0xFE1A at _PIN_AG9_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AG9                                (_PIN_AG9_A_ADC3_1_0)

typedef enum
{
    _PIN_AG9_GPI = 0x00,
    _PIN_AG9_GPO_PP = 0x01,
    _PIN_AG9_GPO_OD = 0x02,
    _PIN_AG9_A_ADC3_1_0 = 0x03,
    _PIN_AG9_EXT_UART_RX_0_0 = 0x04,
    _PIN_AG9_EXT_UART_RX_1_0 = 0x05,
    _PIN_AG9_EXT_UART_RX_2_0 = 0x06,
    _PIN_AG9_TEST12B_OUT0 = 0x07,
    _PIN_AG9_TEST12B_OUT1 = 0x08,
    _PIN_AG9_TEST12B_OUT2 = 0x09,
    _PIN_AG9_TEST12B_OUT3 = 0x0A,
    _PIN_AG9_TEST12B_OUT4 = 0x0B,
    _PIN_AG9_TEST12B_OUT5 = 0x0C,
    _PIN_AG9_TEST12B_OUT6 = 0x0D,
    _PIN_AG9_TEST12B_OUT7 = 0x0E,
    _PIN_AG9_TEST12B_OUT8 = 0x0F,
    _PIN_AG9_TEST12B_OUT9 = 0x10,
    _PIN_AG9_TEST12B_OUT10 = 0x11,
    _PIN_AG9_TEST12B_OUT11 = 0x12,
    _PIN_AG9_NC = _PIN_AG9_GPO_PP,
} EnumPinshareInfoPINAG9;

//---------------------------------------------------------------------------
// Function : LINE_INL
// Pinshare : 0x101B at _OFF_Region
// MCU Ctrl : 0xFE1B at _PIN_AG20_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AG20_OFF_REGION                    (_PIN_AG20_LINE_INL)

typedef enum
{
    _PIN_AG20_GPI = 0x00,
    _PIN_AG20_GPO_PP = 0x01,
    _PIN_AG20_GPO_OD = 0x02,
    _PIN_AG20_LINE_INL = 0x03,
    _PIN_AG20_MCK = 0x04,
    _PIN_AG20_NC = _PIN_AG20_GPO_PP,
} EnumPinshareInfoPINAG20;

//---------------------------------------------------------------------------
// Function : LINE_INR
// Pinshare : 0x101C at _OFF_Region
// MCU Ctrl : 0xFE1C at _PIN_AF20_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AF20_OFF_REGION                    (_PIN_AF20_LINE_INR)

typedef enum
{
    _PIN_AF20_GPI = 0x00,
    _PIN_AF20_GPO_PP = 0x01,
    _PIN_AF20_GPO_OD = 0x02,
    _PIN_AF20_LINE_INR = 0x03,
    _PIN_AF20_SCK = 0x04,
    _PIN_AF20_NC = _PIN_AF20_GPO_PP,
} EnumPinshareInfoPINAF20;

//---------------------------------------------------------------------------
// Function : Audio_ADC_REF
// Pinshare : 0x101D at _OFF_Region
// MCU Ctrl : 0xFE1D at _PIN_AF19_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AF19_OFF_REGION                    (_PIN_AF19_AUDIO_ADC_VREF)

typedef enum
{
    _PIN_AF19_GPI = 0x00,
    _PIN_AF19_GPO_PP = 0x01,
    _PIN_AF19_GPO_OD = 0x02,
    _PIN_AF19_AUDIO_ADC_VREF = 0x03,
    _PIN_AF19_NC = _PIN_AF19_GPO_PP,
} EnumPinshareInfoPINAF19;

//---------------------------------------------------------------------------
// Function : AUDIO_SOUTL
// Pinshare : 0x101F at _OFF_Region
// MCU Ctrl : 0xFE1F at _PIN_AG22_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AG22_OFF_REGION                    (_PIN_AG22_AUDIO_SOUTL)

typedef enum
{
    _PIN_AG22_GPI = 0x00,
    _PIN_AG22_GPO_PP = 0x01,
    _PIN_AG22_GPO_OD = 0x02,
    _PIN_AG22_AUDIO_SOUTL = 0x03,
    _PIN_AG22_SD0 = 0x04,
    _PIN_AG22_SPDIF0 = 0x05,
    _PIN_AG22_NC = _PIN_AG22_GPO_PP,
} EnumPinshareInfoPINAG22;

//---------------------------------------------------------------------------
// Function : AUDIO_SOUTR
// Pinshare : 0x1020 at _OFF_Region
// MCU Ctrl : 0xFE20 at _PIN_AF22_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AF22_OFF_REGION                    (_PIN_AF22_AUDIO_SOUTR)

typedef enum
{
    _PIN_AF22_GPI = 0x00,
    _PIN_AF22_GPO_PP = 0x01,
    _PIN_AF22_GPO_OD = 0x02,
    _PIN_AF22_AUDIO_SOUTR = 0x03,
    _PIN_AF22_SD1 = 0x04,
    _PIN_AF22_SPDIF1 = 0x05,
    _PIN_AF22_NC = _PIN_AF22_GPO_PP,
} EnumPinshareInfoPINAF22;

//---------------------------------------------------------------------------
// Function : AUDIO_HOUTL
// Pinshare : 0x1021 at _OFF_Region
// MCU Ctrl : 0xFE21 at _PIN_AG23_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AG23_OFF_REGION                    (_PIN_AG23_AUDIO_HOUTL)

typedef enum
{
    _PIN_AG23_GPI = 0x00,
    _PIN_AG23_GPO_PP = 0x01,
    _PIN_AG23_GPO_OD = 0x02,
    _PIN_AG23_AUDIO_HOUTL = 0x03,
    _PIN_AG23_SD2 = 0x04,
    _PIN_AG23_SPDIF2 = 0x05,
    _PIN_AG23_NC = _PIN_AG23_GPO_PP,
} EnumPinshareInfoPINAG23;

//---------------------------------------------------------------------------
// Function : AUDIO_HOUTR
// Pinshare : 0x1022 at _OFF_Region
// MCU Ctrl : 0xFE22 at _PIN_AE23_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AE23_OFF_REGION                    (_PIN_AE23_AUDIO_HOUTR)

typedef enum
{
    _PIN_AE23_GPI = 0x00,
    _PIN_AE23_GPO_PP = 0x01,
    _PIN_AE23_GPO_OD = 0x02,
    _PIN_AE23_AUDIO_HOUTR = 0x03,
    _PIN_AE23_SD3 = 0x04,
    _PIN_AE23_SPDIF3 = 0x05,
    _PIN_AE23_NC = _PIN_AE23_GPO_PP,
} EnumPinshareInfoPINAE23;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1023 at _OFF_Region
// MCU Ctrl : 0xFE23 at _PIN_AA22_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AA22_OFF_REGION                    (_PIN_AA22_NC)

typedef enum
{
    _PIN_AA22_GPI = 0x00,
    _PIN_AA22_GPO_PP = 0x01,
    _PIN_AA22_GPO_OD = 0x02,
    _PIN_AA22_PWM0_PP = 0x03,
    _PIN_AA22_PWM0_OD = 0x04,
    _PIN_AA22_PWM0_DIMMING_PP = 0x05,
    _PIN_AA22_PWM0_DIMMING = 0x06,
    _PIN_AA22_USB_SPI_CLK_0_3 = 0x07,
    _PIN_AA22_USB_SPI_CLK_1_3 = 0x08,
    _PIN_AA22_USB_SPI_CLK_2_3 = 0x09,
    _PIN_AA22_TCON6 = 0x0A,
    _PIN_AA22_TEST12B_OUT0 = 0x0B,
    _PIN_AA22_TEST12B_OUT1 = 0x0C,
    _PIN_AA22_TEST12B_OUT2 = 0x0D,
    _PIN_AA22_TEST12B_OUT3 = 0x0E,
    _PIN_AA22_TEST12B_OUT4 = 0x0F,
    _PIN_AA22_TEST12B_OUT5 = 0x10,
    _PIN_AA22_TEST12B_OUT6 = 0x11,
    _PIN_AA22_TEST12B_OUT7 = 0x12,
    _PIN_AA22_TEST12B_OUT8 = 0x13,
    _PIN_AA22_TEST12B_OUT9 = 0x14,
    _PIN_AA22_TEST12B_OUT10 = 0x15,
    _PIN_AA22_TEST12B_OUT11 = 0x16,
    _PIN_AA22_NC = _PIN_AA22_GPO_PP,
} EnumPinshareInfoPINAA22;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1024 at _OFF_Region
// MCU Ctrl : 0xFE24 at _PIN_W23_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_W23_OFF_REGION                     (_PIN_W23_NC)

typedef enum
{
    _PIN_W23_GPI = 0x00,
    _PIN_W23_GPO_PP = 0x01,
    _PIN_W23_GPO_OD = 0x02,
    _PIN_W23_IICSCL_0_6 = 0x03,
    _PIN_W23_IICSCL_1_6 = 0x04,
    _PIN_W23_PWM5_PP = 0x05,
    _PIN_W23_PWM5_OD = 0x06,
    _PIN_W23_PWM5_DIMMING_PP = 0x07,
    _PIN_W23_PWM5_DIMMING = 0x08,
    _PIN_W23_USB_SPI_SI_0_3 = 0x09,
    _PIN_W23_USB_SPI_SI_1_3 = 0x0A,
    _PIN_W23_USB_SPI_SI_2_3 = 0x0B,
    _PIN_W23_TEST12B_OUT0 = 0x0C,
    _PIN_W23_TEST12B_OUT1 = 0x0D,
    _PIN_W23_TEST12B_OUT2 = 0x0E,
    _PIN_W23_TEST12B_OUT3 = 0x0F,
    _PIN_W23_TEST12B_OUT4 = 0x10,
    _PIN_W23_TEST12B_OUT5 = 0x11,
    _PIN_W23_TEST12B_OUT6 = 0x12,
    _PIN_W23_TEST12B_OUT7 = 0x13,
    _PIN_W23_TEST12B_OUT8 = 0x14,
    _PIN_W23_TEST12B_OUT9 = 0x15,
    _PIN_W23_TEST12B_OUT10 = 0x16,
    _PIN_W23_TEST12B_OUT11 = 0x17,
    _PIN_W23_NC = _PIN_W23_GPO_PP,
} EnumPinshareInfoPINW23;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1025 at _OFF_Region
// MCU Ctrl : 0xFE25 at _PIN_W22_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_W22_OFF_REGION                     (_PIN_W22_NC)

typedef enum
{
    _PIN_W22_GPI = 0x00,
    _PIN_W22_GPO_PP = 0x01,
    _PIN_W22_GPO_OD = 0x02,
    _PIN_W22_IICSDA_0_6 = 0x03,
    _PIN_W22_IICSDA_1_6 = 0x04,
    _PIN_W22_M1_IDOMAIN_VS_OUT = 0x05,
    _PIN_W22_USB_SPI_SO_0_3 = 0x06,
    _PIN_W22_USB_SPI_SO_1_3 = 0x07,
    _PIN_W22_USB_SPI_SO_2_3 = 0x08,
    _PIN_W22_TEST12B_OUT0 = 0x09,
    _PIN_W22_TEST12B_OUT1 = 0x0A,
    _PIN_W22_TEST12B_OUT2 = 0x0B,
    _PIN_W22_TEST12B_OUT3 = 0x0C,
    _PIN_W22_TEST12B_OUT4 = 0x0D,
    _PIN_W22_TEST12B_OUT5 = 0x0E,
    _PIN_W22_TEST12B_OUT6 = 0x0F,
    _PIN_W22_TEST12B_OUT7 = 0x10,
    _PIN_W22_TEST12B_OUT8 = 0x11,
    _PIN_W22_TEST12B_OUT9 = 0x12,
    _PIN_W22_TEST12B_OUT10 = 0x13,
    _PIN_W22_TEST12B_OUT11 = 0x14,
    _PIN_W22_NC = _PIN_W22_GPO_PP,
} EnumPinshareInfoPINW22;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1026 at _OFF_Region
// MCU Ctrl : 0xFE26 at _PIN_AE26_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AE26_OFF_REGION                    (_PIN_AE26_NC)

typedef enum
{
    _PIN_AE26_GPI = 0x00,
    _PIN_AE26_GPO_PP = 0x01,
    _PIN_AE26_GPO_OD = 0x02,
    _PIN_AE26_IICSCL_0_4 = 0x03,
    _PIN_AE26_IICSCL_1_4 = 0x04,
    _PIN_AE26_USB_SPI_CEB0_0_3 = 0x05,
    _PIN_AE26_USB_SPI_CEB0_1_3 = 0x06,
    _PIN_AE26_USB_SPI_CEB0_2_3 = 0x07,
    _PIN_AE26_TEST12B_OUT0 = 0x08,
    _PIN_AE26_TEST12B_OUT1 = 0x09,
    _PIN_AE26_TEST12B_OUT2 = 0x0A,
    _PIN_AE26_TEST12B_OUT3 = 0x0B,
    _PIN_AE26_TEST12B_OUT4 = 0x0C,
    _PIN_AE26_TEST12B_OUT5 = 0x0D,
    _PIN_AE26_TEST12B_OUT6 = 0x0E,
    _PIN_AE26_TEST12B_OUT7 = 0x0F,
    _PIN_AE26_TEST12B_OUT8 = 0x10,
    _PIN_AE26_TEST12B_OUT9 = 0x11,
    _PIN_AE26_TEST12B_OUT10 = 0x12,
    _PIN_AE26_TEST12B_OUT11 = 0x13,
    _PIN_AE26_NC = _PIN_AE26_GPO_PP,
} EnumPinshareInfoPINAE26;

//---------------------------------------------------------------------------
// Function : NC
// Pinshare : 0x1027 at _OFF_Region
// MCU Ctrl : 0xFE27 at _PIN_AD26_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AD26_OFF_REGION                    (_PIN_AD26_NC)

typedef enum
{
    _PIN_AD26_GPI = 0x00,
    _PIN_AD26_GPO_PP = 0x01,
    _PIN_AD26_GPO_OD = 0x02,
    _PIN_AD26_IICSDA_0_4 = 0x03,
    _PIN_AD26_IICSDA_1_4 = 0x04,
    _PIN_AD26_USB_SPI_CEB1_0_3 = 0x05,
    _PIN_AD26_USB_SPI_CEB1_1_3 = 0x06,
    _PIN_AD26_USB_SPI_CEB1_2_3 = 0x07,
    _PIN_AD26_TEST12B_OUT0 = 0x08,
    _PIN_AD26_TEST12B_OUT1 = 0x09,
    _PIN_AD26_TEST12B_OUT2 = 0x0A,
    _PIN_AD26_TEST12B_OUT3 = 0x0B,
    _PIN_AD26_TEST12B_OUT4 = 0x0C,
    _PIN_AD26_TEST12B_OUT5 = 0x0D,
    _PIN_AD26_TEST12B_OUT6 = 0x0E,
    _PIN_AD26_TEST12B_OUT7 = 0x0F,
    _PIN_AD26_TEST12B_OUT8 = 0x10,
    _PIN_AD26_TEST12B_OUT9 = 0x11,
    _PIN_AD26_TEST12B_OUT10 = 0x12,
    _PIN_AD26_TEST12B_OUT11 = 0x13,
    _PIN_AD26_NC = _PIN_AD26_GPO_PP,
} EnumPinshareInfoPINAD26;

//---------------------------------------------------------------------------
// Function : EDPTX_AUXN0
// Pinshare : 0x1028 at _OFF_Region
// MCU Ctrl : 0xFE28 at _PIN_AB26_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AB26_OFF_REGION                    (_PIN_AB26_EDPTX_AUX_N_0)

typedef enum
{
    _PIN_AB26_GPI = 0x00,
    _PIN_AB26_GPO_PP = 0x01,
    _PIN_AB26_GPO_OD = 0x02,
    _PIN_AB26_EDPTX_AUX_N_0 = 0x03,
    _PIN_AB26_TEST12B_OUT0 = 0x04,
    _PIN_AB26_TEST12B_OUT1 = 0x05,
    _PIN_AB26_TEST12B_OUT2 = 0x06,
    _PIN_AB26_TEST12B_OUT3 = 0x07,
    _PIN_AB26_TEST12B_OUT4 = 0x08,
    _PIN_AB26_TEST12B_OUT5 = 0x09,
    _PIN_AB26_TEST12B_OUT6 = 0x0A,
    _PIN_AB26_TEST12B_OUT7 = 0x0B,
    _PIN_AB26_TEST12B_OUT8 = 0x0C,
    _PIN_AB26_TEST12B_OUT9 = 0x0D,
    _PIN_AB26_TEST12B_OUT10 = 0x0E,
    _PIN_AB26_TEST12B_OUT11 = 0x0F,
    _PIN_AB26_NC = _PIN_AB26_GPO_PP,
} EnumPinshareInfoPINAB26;

//---------------------------------------------------------------------------
// Function : EDPTX_AUXP0
// Pinshare : 0x1029 at _OFF_Region
// MCU Ctrl : 0xFE29 at _PIN_AC26_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AC26_OFF_REGION                    (_PIN_AC26_EDPTX_AUX_P_0)

typedef enum
{
    _PIN_AC26_GPI = 0x00,
    _PIN_AC26_GPO_PP = 0x01,
    _PIN_AC26_GPO_OD = 0x02,
    _PIN_AC26_EDPTX_AUX_P_0 = 0x03,
    _PIN_AC26_TEST12B_OUT0 = 0x04,
    _PIN_AC26_TEST12B_OUT1 = 0x05,
    _PIN_AC26_TEST12B_OUT2 = 0x06,
    _PIN_AC26_TEST12B_OUT3 = 0x07,
    _PIN_AC26_TEST12B_OUT4 = 0x08,
    _PIN_AC26_TEST12B_OUT5 = 0x09,
    _PIN_AC26_TEST12B_OUT6 = 0x0A,
    _PIN_AC26_TEST12B_OUT7 = 0x0B,
    _PIN_AC26_TEST12B_OUT8 = 0x0C,
    _PIN_AC26_TEST12B_OUT9 = 0x0D,
    _PIN_AC26_TEST12B_OUT10 = 0x0E,
    _PIN_AC26_TEST12B_OUT11 = 0x0F,
    _PIN_AC26_NC = _PIN_AC26_GPO_PP,
} EnumPinshareInfoPINAC26;

//---------------------------------------------------------------------------
// Function : EDPTX_AUXN1
// Pinshare : 0x102A at _OFF_Region
// MCU Ctrl : 0xFE2A at _PIN_Y26_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_Y26_OFF_REGION                     (_PIN_Y26_EDPTX_AUX_N_1)

typedef enum
{
    _PIN_Y26_GPI = 0x00,
    _PIN_Y26_GPO_PP = 0x01,
    _PIN_Y26_GPO_OD = 0x02,
    _PIN_Y26_EDPTX_AUX_N_1 = 0x03,
    _PIN_Y26_TEST12B_OUT0 = 0x04,
    _PIN_Y26_TEST12B_OUT1 = 0x05,
    _PIN_Y26_TEST12B_OUT2 = 0x06,
    _PIN_Y26_TEST12B_OUT3 = 0x07,
    _PIN_Y26_TEST12B_OUT4 = 0x08,
    _PIN_Y26_TEST12B_OUT5 = 0x09,
    _PIN_Y26_TEST12B_OUT6 = 0x0A,
    _PIN_Y26_TEST12B_OUT7 = 0x0B,
    _PIN_Y26_TEST12B_OUT8 = 0x0C,
    _PIN_Y26_TEST12B_OUT9 = 0x0D,
    _PIN_Y26_TEST12B_OUT10 = 0x0E,
    _PIN_Y26_TEST12B_OUT11 = 0x0F,
    _PIN_Y26_NC = _PIN_Y26_GPO_PP,
} EnumPinshareInfoPINY26;

//---------------------------------------------------------------------------
// Function : EDPTX_AUXP1
// Pinshare : 0x102B at _OFF_Region
// MCU Ctrl : 0xFE2B at _PIN_AA26_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AA26_OFF_REGION                    (_PIN_AA26_EDPTX_AUX_P_1)

typedef enum
{
    _PIN_AA26_GPI = 0x00,
    _PIN_AA26_GPO_PP = 0x01,
    _PIN_AA26_GPO_OD = 0x02,
    _PIN_AA26_EDPTX_AUX_P_1 = 0x03,
    _PIN_AA26_TEST12B_OUT0 = 0x04,
    _PIN_AA26_TEST12B_OUT1 = 0x05,
    _PIN_AA26_TEST12B_OUT2 = 0x06,
    _PIN_AA26_TEST12B_OUT3 = 0x07,
    _PIN_AA26_TEST12B_OUT4 = 0x08,
    _PIN_AA26_TEST12B_OUT5 = 0x09,
    _PIN_AA26_TEST12B_OUT6 = 0x0A,
    _PIN_AA26_TEST12B_OUT7 = 0x0B,
    _PIN_AA26_TEST12B_OUT8 = 0x0C,
    _PIN_AA26_TEST12B_OUT9 = 0x0D,
    _PIN_AA26_TEST12B_OUT10 = 0x0E,
    _PIN_AA26_TEST12B_OUT11 = 0x0F,
    _PIN_AA26_NC = _PIN_AA26_GPO_PP,
} EnumPinshareInfoPINAA26;

//---------------------------------------------------------------------------
// Function : UART_RX0
// Pinshare : 0x102C at _OFF_Region
// MCU Ctrl : 0xFE2C at _PIN_Y23_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_Y23_OFF_REGION                     (_PIN_Y23_EXT_UART_RX_0_6)

typedef enum
{
    _PIN_Y23_GPI = 0x00,
    _PIN_Y23_GPO_PP = 0x01,
    _PIN_Y23_GPO_OD = 0x02,
    _PIN_Y23_EXT_UART_RX_0_6 = 0x03,
    _PIN_Y23_EXT_UART_RX_1_6 = 0x04,
    _PIN_Y23_EXT_UART_RX_2_6 = 0x05,
    _PIN_Y23_TEST12B_OUT0 = 0x06,
    _PIN_Y23_TEST12B_OUT1 = 0x07,
    _PIN_Y23_TEST12B_OUT2 = 0x08,
    _PIN_Y23_TEST12B_OUT3 = 0x09,
    _PIN_Y23_TEST12B_OUT4 = 0x0A,
    _PIN_Y23_TEST12B_OUT5 = 0x0B,
    _PIN_Y23_TEST12B_OUT6 = 0x0C,
    _PIN_Y23_TEST12B_OUT7 = 0x0D,
    _PIN_Y23_TEST12B_OUT8 = 0x0E,
    _PIN_Y23_TEST12B_OUT9 = 0x0F,
    _PIN_Y23_TEST12B_OUT10 = 0x10,
    _PIN_Y23_TEST12B_OUT11 = 0x11,
    _PIN_Y23_NC = _PIN_Y23_GPO_PP,
} EnumPinshareInfoPINY23;

//---------------------------------------------------------------------------
// Function : UART_TX0
// Pinshare : 0x102D at _OFF_Region
// MCU Ctrl : 0xFE2D at _PIN_Y22_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_Y22_OFF_REGION                     (_PIN_Y22_EXT_UART_TX_0_6)

typedef enum
{
    _PIN_Y22_GPI = 0x00,
    _PIN_Y22_GPO_PP = 0x01,
    _PIN_Y22_GPO_OD = 0x02,
    _PIN_Y22_EXT_UART_TX_0_6 = 0x03,
    _PIN_Y22_EXT_UART_TX_1_6 = 0x04,
    _PIN_Y22_EXT_UART_TX_2_6 = 0x05,
    _PIN_Y22_TEST12B_OUT0 = 0x06,
    _PIN_Y22_TEST12B_OUT1 = 0x07,
    _PIN_Y22_TEST12B_OUT2 = 0x08,
    _PIN_Y22_TEST12B_OUT3 = 0x09,
    _PIN_Y22_TEST12B_OUT4 = 0x0A,
    _PIN_Y22_TEST12B_OUT5 = 0x0B,
    _PIN_Y22_TEST12B_OUT6 = 0x0C,
    _PIN_Y22_TEST12B_OUT7 = 0x0D,
    _PIN_Y22_TEST12B_OUT8 = 0x0E,
    _PIN_Y22_TEST12B_OUT9 = 0x0F,
    _PIN_Y22_TEST12B_OUT10 = 0x10,
    _PIN_Y22_TEST12B_OUT11 = 0x11,
    _PIN_Y22_NC = _PIN_Y22_GPO_PP,
} EnumPinshareInfoPINY22;

//---------------------------------------------------------------------------
// Function : CLK_1
// Pinshare : 0x102E at _OFF_Region
// MCU Ctrl : 0xFE2E at _PIN_AA23_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AA23_OFF_REGION                    (_PIN_AA23_USB_SPI_CLK_1_1)

typedef enum
{
    _PIN_AA23_GPI = 0x00,
    _PIN_AA23_GPO_PP = 0x01,
    _PIN_AA23_GPO_OD = 0x02,
    _PIN_AA23_USB_SPI_CLK_0_1 = 0x03,
    _PIN_AA23_USB_SPI_CLK_1_1 = 0x04,
    _PIN_AA23_USB_SPI_CLK_2_1 = 0x05,
    _PIN_AA23_IICSCL_0_5 = 0x06,
    _PIN_AA23_IICSCL_1_5 = 0x07,
    _PIN_AA23_TCON9 = 0x08,
    _PIN_AA23_TEST12B_OUT0 = 0x09,
    _PIN_AA23_TEST12B_OUT1 = 0x0A,
    _PIN_AA23_TEST12B_OUT2 = 0x0B,
    _PIN_AA23_TEST12B_OUT3 = 0x0C,
    _PIN_AA23_TEST12B_OUT4 = 0x0D,
    _PIN_AA23_TEST12B_OUT5 = 0x0E,
    _PIN_AA23_TEST12B_OUT6 = 0x0F,
    _PIN_AA23_TEST12B_OUT7 = 0x10,
    _PIN_AA23_TEST12B_OUT8 = 0x11,
    _PIN_AA23_TEST12B_OUT9 = 0x12,
    _PIN_AA23_TEST12B_OUT10 = 0x13,
    _PIN_AA23_TEST12B_OUT11 = 0x14,
    _PIN_AA23_NC = _PIN_AA23_GPO_PP,
} EnumPinshareInfoPINAA23;

//---------------------------------------------------------------------------
// Function : SDIN_1
// Pinshare : 0x102F at _OFF_Region
// MCU Ctrl : 0xFE2F at _PIN_Y24_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_Y24_OFF_REGION                     (_PIN_Y24_USB_SPI_SI_1_1)

typedef enum
{
    _PIN_Y24_GPI = 0x00,
    _PIN_Y24_GPO_PP = 0x01,
    _PIN_Y24_GPO_OD = 0x02,
    _PIN_Y24_USB_SPI_SI_0_1 = 0x03,
    _PIN_Y24_USB_SPI_SI_1_1 = 0x04,
    _PIN_Y24_USB_SPI_SI_2_1 = 0x05,
    _PIN_Y24_IICSDA_0_5 = 0x06,
    _PIN_Y24_IICSDA_1_5 = 0x07,
    _PIN_Y24_TCON10 = 0x08,
    _PIN_Y24_TEST12B_OUT0 = 0x09,
    _PIN_Y24_TEST12B_OUT1 = 0x0A,
    _PIN_Y24_TEST12B_OUT2 = 0x0B,
    _PIN_Y24_TEST12B_OUT3 = 0x0C,
    _PIN_Y24_TEST12B_OUT4 = 0x0D,
    _PIN_Y24_TEST12B_OUT5 = 0x0E,
    _PIN_Y24_TEST12B_OUT6 = 0x0F,
    _PIN_Y24_TEST12B_OUT7 = 0x10,
    _PIN_Y24_TEST12B_OUT8 = 0x11,
    _PIN_Y24_TEST12B_OUT9 = 0x12,
    _PIN_Y24_TEST12B_OUT10 = 0x13,
    _PIN_Y24_TEST12B_OUT11 = 0x14,
    _PIN_Y24_NC = _PIN_Y24_GPO_PP,
} EnumPinshareInfoPINY24;

//---------------------------------------------------------------------------
// Function : SDOUT_1
// Pinshare : 0x1030 at _OFF_Region
// MCU Ctrl : 0xFE30 at _PIN_AA24_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AA24_OFF_REGION                    (_PIN_AA24_USB_SPI_SO_1_1)

typedef enum
{
    _PIN_AA24_GPI = 0x00,
    _PIN_AA24_GPO_PP = 0x01,
    _PIN_AA24_GPO_OD = 0x02,
    _PIN_AA24_USB_SPI_SO_0_1 = 0x03,
    _PIN_AA24_USB_SPI_SO_1_1 = 0x04,
    _PIN_AA24_USB_SPI_SO_2_1 = 0x05,
    _PIN_AA24_TCON11 = 0x06,
    _PIN_AA24_TEST12B_OUT0 = 0x07,
    _PIN_AA24_TEST12B_OUT1 = 0x08,
    _PIN_AA24_TEST12B_OUT2 = 0x09,
    _PIN_AA24_TEST12B_OUT3 = 0x0A,
    _PIN_AA24_TEST12B_OUT4 = 0x0B,
    _PIN_AA24_TEST12B_OUT5 = 0x0C,
    _PIN_AA24_TEST12B_OUT6 = 0x0D,
    _PIN_AA24_TEST12B_OUT7 = 0x0E,
    _PIN_AA24_TEST12B_OUT8 = 0x0F,
    _PIN_AA24_TEST12B_OUT9 = 0x10,
    _PIN_AA24_TEST12B_OUT10 = 0x11,
    _PIN_AA24_TEST12B_OUT11 = 0x12,
    _PIN_AA24_NC = _PIN_AA24_GPO_PP,
} EnumPinshareInfoPINAA24;

//---------------------------------------------------------------------------
// Function : CE_1
// Pinshare : 0x1031 at _OFF_Region
// MCU Ctrl : 0xFE31 at _PIN_Y25_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_Y25_OFF_REGION                     (_PIN_Y25_USB_SPI_CEB0_1_1)

typedef enum
{
    _PIN_Y25_GPI = 0x00,
    _PIN_Y25_GPO_PP = 0x01,
    _PIN_Y25_GPO_OD = 0x02,
    _PIN_Y25_USB_SPI_CEB0_0_1 = 0x03,
    _PIN_Y25_USB_SPI_CEB0_1_1 = 0x04,
    _PIN_Y25_USB_SPI_CEB0_2_1 = 0x05,
    _PIN_Y25_TCON12 = 0x06,
    _PIN_Y25_TEST12B_OUT0 = 0x07,
    _PIN_Y25_TEST12B_OUT1 = 0x08,
    _PIN_Y25_TEST12B_OUT2 = 0x09,
    _PIN_Y25_TEST12B_OUT3 = 0x0A,
    _PIN_Y25_TEST12B_OUT4 = 0x0B,
    _PIN_Y25_TEST12B_OUT5 = 0x0C,
    _PIN_Y25_TEST12B_OUT6 = 0x0D,
    _PIN_Y25_TEST12B_OUT7 = 0x0E,
    _PIN_Y25_TEST12B_OUT8 = 0x0F,
    _PIN_Y25_TEST12B_OUT9 = 0x10,
    _PIN_Y25_TEST12B_OUT10 = 0x11,
    _PIN_Y25_TEST12B_OUT11 = 0x12,
    _PIN_Y25_NC = _PIN_Y25_GPO_PP,
} EnumPinshareInfoPINY25;

//---------------------------------------------------------------------------
// Function : LED4_1
// Pinshare : 0x1032 at _OFF_Region
// MCU Ctrl : 0xFE32 at _PIN_AA25_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_AA25_OFF_REGION                    (_PIN_AA25_GPO_PP)

typedef enum
{
    _PIN_AA25_GPI = 0x00,
    _PIN_AA25_GPO_PP = 0x01,
    _PIN_AA25_GPO_OD = 0x02,
    _PIN_AA25_USB_SPI_CEB1_0_1 = 0x03,
    _PIN_AA25_USB_SPI_CEB1_1_1 = 0x04,
    _PIN_AA25_USB_SPI_CEB1_2_1 = 0x05,
    _PIN_AA25_PWM4_PP = 0x06,
    _PIN_AA25_PWM4_OD = 0x07,
    _PIN_AA25_PWM4_DIMMING_PP = 0x08,
    _PIN_AA25_PWM4_DIMMING = 0x09,
    _PIN_AA25_TEST12B_OUT0 = 0x0A,
    _PIN_AA25_TEST12B_OUT1 = 0x0B,
    _PIN_AA25_TEST12B_OUT2 = 0x0C,
    _PIN_AA25_TEST12B_OUT3 = 0x0D,
    _PIN_AA25_TEST12B_OUT4 = 0x0E,
    _PIN_AA25_TEST12B_OUT5 = 0x0F,
    _PIN_AA25_TEST12B_OUT6 = 0x10,
    _PIN_AA25_TEST12B_OUT7 = 0x11,
    _PIN_AA25_TEST12B_OUT8 = 0x12,
    _PIN_AA25_TEST12B_OUT9 = 0x13,
    _PIN_AA25_TEST12B_OUT10 = 0x14,
    _PIN_AA25_TEST12B_OUT11 = 0x15,
    _PIN_AA25_NC = _PIN_AA25_GPO_PP,
} EnumPinshareInfoPINAA25;

//---------------------------------------------------------------------------
// Function : EDPTX_HPD0
// Pinshare : 0x1033 at _OFF_Region
// MCU Ctrl : 0xFE33 at _PIN_AC25_MCU_REG
//---------------------------------------------------------------------------
#if(_PANEL_STYLE == _PANEL_VBO)
#define _PIN_AC25_OFF_REGION                    (_PIN_AC25_VB1_HTPD_N_0_0)
#else
#define _PIN_AC25_OFF_REGION                    (_PIN_AC25_EDPTX_HPD_ORG_0)
#endif

typedef enum
{
    _PIN_AC25_GPI = 0x00,
    _PIN_AC25_GPO_PP = 0x01,
    _PIN_AC25_GPO_OD = 0x02,
    _PIN_AC25_EDPTX_HPD_ORG_0 = 0x03,
    _PIN_AC25_VB1_HTPD_N_0_0 = 0x04,
    _PIN_AC25_TEST12B_OUT0 = 0x05,
    _PIN_AC25_TEST12B_OUT1 = 0x06,
    _PIN_AC25_TEST12B_OUT2 = 0x07,
    _PIN_AC25_TEST12B_OUT3 = 0x08,
    _PIN_AC25_TEST12B_OUT4 = 0x09,
    _PIN_AC25_TEST12B_OUT5 = 0x0A,
    _PIN_AC25_TEST12B_OUT6 = 0x0B,
    _PIN_AC25_TEST12B_OUT7 = 0x0C,
    _PIN_AC25_TEST12B_OUT8 = 0x0D,
    _PIN_AC25_TEST12B_OUT9 = 0x0E,
    _PIN_AC25_TEST12B_OUT10 = 0x0F,
    _PIN_AC25_TEST12B_OUT11 = 0x10,
    _PIN_AC25_NC = _PIN_AC25_GPO_PP,
} EnumPinshareInfoPINAC25;

//---------------------------------------------------------------------------
// Function : EDPTX_HPD1
// Pinshare : 0x1034 at _OFF_Region
// MCU Ctrl : 0xFE34 at _PIN_AB25_MCU_REG
//---------------------------------------------------------------------------
#if(_PANEL_STYLE == _PANEL_VBO)
#define _PIN_AB25_OFF_REGION                    (_PIN_AB25_VB1_PLL_LOCK_N_0_0)
#else
#define _PIN_AB25_OFF_REGION                    (_PIN_AB25_EDPTX_HPD_ORG_1)
#endif

typedef enum
{
    _PIN_AB25_GPI = 0x00,
    _PIN_AB25_GPO_PP = 0x01,
    _PIN_AB25_GPO_OD = 0x02,
    _PIN_AB25_EDPTX_HPD_ORG_1 = 0x03,
    _PIN_AB25_VB1_PLL_LOCK_N_0_0 = 0x04,
    _PIN_AB25_TEST12B_OUT0 = 0x05,
    _PIN_AB25_TEST12B_OUT1 = 0x06,
    _PIN_AB25_TEST12B_OUT2 = 0x07,
    _PIN_AB25_TEST12B_OUT3 = 0x08,
    _PIN_AB25_TEST12B_OUT4 = 0x09,
    _PIN_AB25_TEST12B_OUT5 = 0x0A,
    _PIN_AB25_TEST12B_OUT6 = 0x0B,
    _PIN_AB25_TEST12B_OUT7 = 0x0C,
    _PIN_AB25_TEST12B_OUT8 = 0x0D,
    _PIN_AB25_TEST12B_OUT9 = 0x0E,
    _PIN_AB25_TEST12B_OUT10 = 0x0F,
    _PIN_AB25_TEST12B_OUT11 = 0x10,
    _PIN_AB25_NC = _PIN_AB25_GPO_PP,
} EnumPinshareInfoPINAB25;

//---------------------------------------------------------------------------
// Function : TXD4P
// Pinshare : 0x1035 at _OFF_Region
// MCU Ctrl : 0xFE35 at _PIN_R28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_R28_OFF_REGION                     (_PIN_R28_TXD4P_10B)

typedef enum
{
    _PIN_R28_HI_Z = 0x00,
    _PIN_R28_GPI = 0x01,
    _PIN_R28_TXD4P_10B = 0x04,
    _PIN_R28_NC = _PIN_R28_GPI,
} EnumPinshareInfoPINR28;

//---------------------------------------------------------------------------
// Function : TXD4N
// Pinshare : 0x1036 at _OFF_Region
// MCU Ctrl : 0xFE36 at _PIN_R30_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_R30_OFF_REGION                     (_PIN_R30_TXD4N_10B)

typedef enum
{
    _PIN_R30_HI_Z = 0x00,
    _PIN_R30_GPI = 0x01,
    _PIN_R30_TXD4N_10B = 0x04,
    _PIN_R30_NC = _PIN_R30_GPI,
} EnumPinshareInfoPINR30;

//---------------------------------------------------------------------------
// Function : TXD3P
// Pinshare : 0x1037 at _OFF_Region
// MCU Ctrl : 0xFE37 at _PIN_R29_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_R29_OFF_REGION                     (_PIN_R29_TXD3P_10B)

typedef enum
{
    _PIN_R29_HI_Z = 0x00,
    _PIN_R29_GPI = 0x01,
    _PIN_R29_TXD3P_10B = 0x04,
    _PIN_R29_NC = _PIN_R29_GPI,
} EnumPinshareInfoPINR29;

//---------------------------------------------------------------------------
// Function : TXD3N
// Pinshare : 0x1038 at _OFF_Region
// MCU Ctrl : 0xFE38 at _PIN_P28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_P28_OFF_REGION                     (_PIN_P28_TXD3N_10B)

typedef enum
{
    _PIN_P28_HI_Z = 0x00,
    _PIN_P28_GPI = 0x01,
    _PIN_P28_TXD3N_10B = 0x04,
    _PIN_P28_NC = _PIN_P28_GPI,
} EnumPinshareInfoPINP28;

//---------------------------------------------------------------------------
// Function : TXD2P
// Pinshare : 0x1039 at _OFF_Region
// MCU Ctrl : 0xFE39 at _PIN_P29_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_P29_OFF_REGION                     (_PIN_P29_TXD2P_10B)

typedef enum
{
    _PIN_P29_HI_Z = 0x00,
    _PIN_P29_GPI = 0x01,
    _PIN_P29_TXD2P_10B = 0x04,
    _PIN_P29_NC = _PIN_P29_GPI,
} EnumPinshareInfoPINP29;

//---------------------------------------------------------------------------
// Function : TXD2N
// Pinshare : 0x103A at _OFF_Region
// MCU Ctrl : 0xFE3A at _PIN_N29_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_N29_OFF_REGION                     (_PIN_N29_TXD2N_10B)

typedef enum
{
    _PIN_N29_HI_Z = 0x00,
    _PIN_N29_GPI = 0x01,
    _PIN_N29_TXD2N_10B = 0x04,
    _PIN_N29_NC = _PIN_N29_GPI,
} EnumPinshareInfoPINN29;

//---------------------------------------------------------------------------
// Function : TXD1P
// Pinshare : 0x103B at _OFF_Region
// MCU Ctrl : 0xFE3B at _PIN_N30_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_N30_OFF_REGION                     (_PIN_N30_TXD1P_10B)

typedef enum
{
    _PIN_N30_HI_Z = 0x00,
    _PIN_N30_GPI = 0x01,
    _PIN_N30_TXD1P_10B = 0x04,
    _PIN_N30_NC = _PIN_N30_GPI,
} EnumPinshareInfoPINN30;

//---------------------------------------------------------------------------
// Function : TXD1N
// Pinshare : 0x103C at _OFF_Region
// MCU Ctrl : 0xFE3C at _PIN_N28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_N28_OFF_REGION                     (_PIN_N28_TXD1N_10B)

typedef enum
{
    _PIN_N28_HI_Z = 0x00,
    _PIN_N28_GPI = 0x01,
    _PIN_N28_TXD1N_10B = 0x04,
    _PIN_N28_NC = _PIN_N28_GPI,
} EnumPinshareInfoPINN28;

//---------------------------------------------------------------------------
// Function : TXD0P
// Pinshare : 0x103D at _OFF_Region
// MCU Ctrl : 0xFE3D at _PIN_L28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_L28_OFF_REGION                     (_PIN_L28_TXD0P_10B)

typedef enum
{
    _PIN_L28_HI_Z = 0x00,
    _PIN_L28_GPI = 0x01,
    _PIN_L28_TXD0P_10B = 0x04,
    _PIN_L28_NC = _PIN_L28_GPI,
} EnumPinshareInfoPINL28;

//---------------------------------------------------------------------------
// Function : TXD0N
// Pinshare : 0x103E at _OFF_Region
// MCU Ctrl : 0xFE3E at _PIN_L30_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_L30_OFF_REGION                     (_PIN_L30_TXD0N_10B)

typedef enum
{
    _PIN_L30_HI_Z = 0x00,
    _PIN_L30_GPI = 0x01,
    _PIN_L30_TXD0N_10B = 0x04,
    _PIN_L30_NC = _PIN_L30_GPI,
} EnumPinshareInfoPINL30;

//---------------------------------------------------------------------------
// Function : TXC4P
// Pinshare : 0x103F at _OFF_Region
// MCU Ctrl : 0xFE3F at _PIN_L29_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_L29_OFF_REGION                     (_PIN_L29_TXC4P_10B)

typedef enum
{
    _PIN_L29_HI_Z = 0x00,
    _PIN_L29_GPI = 0x01,
    _PIN_L29_TXC4P_10B = 0x04,
    _PIN_L29_NC = _PIN_L29_GPI,
} EnumPinshareInfoPINL29;

//---------------------------------------------------------------------------
// Function : TXC4N
// Pinshare : 0x1040 at _OFF_Region
// MCU Ctrl : 0xFE40 at _PIN_K28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_K28_OFF_REGION                     (_PIN_K28_TXC4N_10B)

typedef enum
{
    _PIN_K28_HI_Z = 0x00,
    _PIN_K28_GPI = 0x01,
    _PIN_K28_TXC4N_10B = 0x04,
    _PIN_K28_NC = _PIN_K28_GPI,
} EnumPinshareInfoPINK28;

//---------------------------------------------------------------------------
// Function : TXC3P
// Pinshare : 0x1041 at _OFF_Region
// MCU Ctrl : 0xFE41 at _PIN_K29_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_K29_OFF_REGION                     (_PIN_K29_TXC3P_10B)

typedef enum
{
    _PIN_K29_HI_Z = 0x00,
    _PIN_K29_GPI = 0x01,
    _PIN_K29_TXC3P_10B = 0x04,
    _PIN_K29_NC = _PIN_K29_GPI,
} EnumPinshareInfoPINK29;

//---------------------------------------------------------------------------
// Function : TXC3N
// Pinshare : 0x1042 at _OFF_Region
// MCU Ctrl : 0xFE42 at _PIN_J29_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_J29_OFF_REGION                     (_PIN_J29_TXC3N_10B)

typedef enum
{
    _PIN_J29_HI_Z = 0x00,
    _PIN_J29_GPI = 0x01,
    _PIN_J29_TXC3N_10B = 0x04,
    _PIN_J29_NC = _PIN_J29_GPI,
} EnumPinshareInfoPINJ29;

//---------------------------------------------------------------------------
// Function : TXCCP
// Pinshare : 0x1043 at _OFF_Region
// MCU Ctrl : 0xFE43 at _PIN_J30_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_J30_OFF_REGION                     (_PIN_J30_TXCCP_10B)

typedef enum
{
    _PIN_J30_HI_Z = 0x00,
    _PIN_J30_GPI = 0x01,
    _PIN_J30_TXCCP_10B = 0x04,
    _PIN_J30_NC = _PIN_J30_GPI,
} EnumPinshareInfoPINJ30;

//---------------------------------------------------------------------------
// Function : TXCCN
// Pinshare : 0x1044 at _OFF_Region
// MCU Ctrl : 0xFE44 at _PIN_J28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_J28_OFF_REGION                     (_PIN_J28_TXCCN_10B)

typedef enum
{
    _PIN_J28_HI_Z = 0x00,
    _PIN_J28_GPI = 0x01,
    _PIN_J28_TXCCN_10B = 0x04,
    _PIN_J28_NC = _PIN_J28_GPI,
} EnumPinshareInfoPINJ28;

//---------------------------------------------------------------------------
// Function : TXC2P
// Pinshare : 0x1045 at _OFF_Region
// MCU Ctrl : 0xFE45 at _PIN_G28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_G28_OFF_REGION                     (_PIN_G28_TXC2P_10B)

typedef enum
{
    _PIN_G28_HI_Z = 0x00,
    _PIN_G28_GPI = 0x01,
    _PIN_G28_TXC2P_10B = 0x04,
    _PIN_G28_NC = _PIN_G28_GPI,
} EnumPinshareInfoPING28;

//---------------------------------------------------------------------------
// Function : TXC2N
// Pinshare : 0x1046 at _OFF_Region
// MCU Ctrl : 0xFE46 at _PIN_G30_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_G30_OFF_REGION                     (_PIN_G30_TXC2N_10B)

typedef enum
{
    _PIN_G30_HI_Z = 0x00,
    _PIN_G30_GPI = 0x01,
    _PIN_G30_TXC2N_10B = 0x04,
    _PIN_G30_NC = _PIN_G30_GPI,
} EnumPinshareInfoPING30;

//---------------------------------------------------------------------------
// Function : TXC1P
// Pinshare : 0x1047 at _OFF_Region
// MCU Ctrl : 0xFE47 at _PIN_G29_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_G29_OFF_REGION                     (_PIN_G29_TXC1P_10B)

typedef enum
{
    _PIN_G29_HI_Z = 0x00,
    _PIN_G29_GPI = 0x01,
    _PIN_G29_TXC1P_10B = 0x04,
    _PIN_G29_NC = _PIN_G29_GPI,
} EnumPinshareInfoPING29;

//---------------------------------------------------------------------------
// Function : TXC1N
// Pinshare : 0x1048 at _OFF_Region
// MCU Ctrl : 0xFE48 at _PIN_F28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_F28_OFF_REGION                     (_PIN_F28_TXC1N_10B)

typedef enum
{
    _PIN_F28_HI_Z = 0x00,
    _PIN_F28_GPI = 0x01,
    _PIN_F28_TXC1N_10B = 0x04,
    _PIN_F28_NC = _PIN_F28_GPI,
} EnumPinshareInfoPINF28;

//---------------------------------------------------------------------------
// Function : TXC0P
// Pinshare : 0x1049 at _OFF_Region
// MCU Ctrl : 0xFE49 at _PIN_F29_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_F29_OFF_REGION                     (_PIN_F29_TXC0P_10B)

typedef enum
{
    _PIN_F29_HI_Z = 0x00,
    _PIN_F29_GPI = 0x01,
    _PIN_F29_TXC0P_10B = 0x04,
    _PIN_F29_NC = _PIN_F29_GPI,
} EnumPinshareInfoPINF29;

//---------------------------------------------------------------------------
// Function : TXC0N
// Pinshare : 0x104A at _OFF_Region
// MCU Ctrl : 0xFE4A at _PIN_E29_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_E29_OFF_REGION                     (_PIN_E29_TXC0N_10B)

typedef enum
{
    _PIN_E29_HI_Z = 0x00,
    _PIN_E29_GPI = 0x01,
    _PIN_E29_TXC0N_10B = 0x04,
    _PIN_E29_NC = _PIN_E29_GPI,
} EnumPinshareInfoPINE29;

//---------------------------------------------------------------------------
// Function : TXB4P
// Pinshare : 0x104B at _OFF_Region
// MCU Ctrl : 0xFE4B at _PIN_E30_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_E30_OFF_REGION                     (_PIN_E30_TXB4P_10B)

typedef enum
{
    _PIN_E30_HI_Z = 0x00,
    _PIN_E30_GPI = 0x01,
    _PIN_E30_TXB4P_10B = 0x04,
    _PIN_E30_NC = _PIN_E30_GPI,
} EnumPinshareInfoPINE30;

//---------------------------------------------------------------------------
// Function : TXB4N
// Pinshare : 0x104C at _OFF_Region
// MCU Ctrl : 0xFE4C at _PIN_E28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_E28_OFF_REGION                     (_PIN_E28_TXB4N_10B)

typedef enum
{
    _PIN_E28_HI_Z = 0x00,
    _PIN_E28_GPI = 0x01,
    _PIN_E28_TXB4N_10B = 0x04,
    _PIN_E28_NC = _PIN_E28_GPI,
} EnumPinshareInfoPINE28;

//---------------------------------------------------------------------------
// Function : TXB3P
// Pinshare : 0x104D at _OFF_Region
// MCU Ctrl : 0xFE4D at _PIN_C28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_C28_OFF_REGION                     (_PIN_C28_TXB3P_10B)

typedef enum
{
    _PIN_C28_HI_Z = 0x00,
    _PIN_C28_GPI = 0x01,
    _PIN_C28_TXB3P_10B = 0x04,
    _PIN_C28_NC = _PIN_C28_GPI,
} EnumPinshareInfoPINC28;

//---------------------------------------------------------------------------
// Function : TXB3N
// Pinshare : 0x104E at _OFF_Region
// MCU Ctrl : 0xFE4E at _PIN_A28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_A28_OFF_REGION                     (_PIN_A28_TXB3N_10B)

typedef enum
{
    _PIN_A28_HI_Z = 0x00,
    _PIN_A28_GPI = 0x01,
    _PIN_A28_TXB3N_10B = 0x04,
    _PIN_A28_NC = _PIN_A28_GPI,
} EnumPinshareInfoPINA28;

//---------------------------------------------------------------------------
// Function : TXB2P
// Pinshare : 0x104F at _OFF_Region
// MCU Ctrl : 0xFE4F at _PIN_B28_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B28_OFF_REGION                     (_PIN_B28_TXB2P_10B)

typedef enum
{
    _PIN_B28_HI_Z = 0x00,
    _PIN_B28_GPI = 0x01,
    _PIN_B28_TXB2P_10B = 0x04,
    _PIN_B28_NC = _PIN_B28_GPI,
} EnumPinshareInfoPINB28;

//---------------------------------------------------------------------------
// Function : TXB2N
// Pinshare : 0x1050 at _OFF_Region
// MCU Ctrl : 0xFE50 at _PIN_C27_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_C27_OFF_REGION                     (_PIN_C27_TXB2N_10B)

typedef enum
{
    _PIN_C27_HI_Z = 0x00,
    _PIN_C27_GPI = 0x01,
    _PIN_C27_TXB2N_10B = 0x04,
    _PIN_C27_NC = _PIN_C27_GPI,
} EnumPinshareInfoPINC27;

//---------------------------------------------------------------------------
// Function : TXB1P
// Pinshare : 0x1051 at _OFF_Region
// MCU Ctrl : 0xFE51 at _PIN_B27_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B27_OFF_REGION                     (_PIN_B27_TXB1P_10B)

typedef enum
{
    _PIN_B27_HI_Z = 0x00,
    _PIN_B27_GPI = 0x01,
    _PIN_B27_TXB1P_10B = 0x04,
    _PIN_B27_NC = _PIN_B27_GPI,
} EnumPinshareInfoPINB27;

//---------------------------------------------------------------------------
// Function : TXB1N
// Pinshare : 0x1052 at _OFF_Region
// MCU Ctrl : 0xFE52 at _PIN_B26_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B26_OFF_REGION                     (_PIN_B26_TXB1N_10B)

typedef enum
{
    _PIN_B26_HI_Z = 0x00,
    _PIN_B26_GPI = 0x01,
    _PIN_B26_TXB1N_10B = 0x04,
    _PIN_B26_NC = _PIN_B26_GPI,
} EnumPinshareInfoPINB26;

//---------------------------------------------------------------------------
// Function : TXB0P
// Pinshare : 0x1053 at _OFF_Region
// MCU Ctrl : 0xFE53 at _PIN_A26_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_A26_OFF_REGION                     (_PIN_A26_TXB0P_10B)

typedef enum
{
    _PIN_A26_HI_Z = 0x00,
    _PIN_A26_GPI = 0x01,
    _PIN_A26_TXB0P_10B = 0x04,
    _PIN_A26_NC = _PIN_A26_GPI,
} EnumPinshareInfoPINA26;

//---------------------------------------------------------------------------
// Function : TXB0N
// Pinshare : 0x1054 at _OFF_Region
// MCU Ctrl : 0xFE54 at _PIN_C26_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_C26_OFF_REGION                     (_PIN_C26_TXB0N_10B)

typedef enum
{
    _PIN_C26_HI_Z = 0x00,
    _PIN_C26_GPI = 0x01,
    _PIN_C26_TXB0N_10B = 0x04,
    _PIN_C26_NC = _PIN_C26_GPI,
} EnumPinshareInfoPINC26;

//---------------------------------------------------------------------------
// Function : TXA4P
// Pinshare : 0x1055 at _OFF_Region
// MCU Ctrl : 0xFE55 at _PIN_C24_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_C24_OFF_REGION                     (_PIN_C24_TXA4P_10B)

typedef enum
{
    _PIN_C24_HI_Z = 0x00,
    _PIN_C24_GPI = 0x01,
    _PIN_C24_TXA4P_10B = 0x04,
    _PIN_C24_NC = _PIN_C24_GPI,
} EnumPinshareInfoPINC24;

//---------------------------------------------------------------------------
// Function : TXA4N
// Pinshare : 0x1056 at _OFF_Region
// MCU Ctrl : 0xFE56 at _PIN_A24_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_A24_OFF_REGION                     (_PIN_A24_TXA4N_10B)

typedef enum
{
    _PIN_A24_HI_Z = 0x00,
    _PIN_A24_GPI = 0x01,
    _PIN_A24_TXA4N_10B = 0x04,
    _PIN_A24_NC = _PIN_A24_GPI,
} EnumPinshareInfoPINA24;

//---------------------------------------------------------------------------
// Function : TXA3P
// Pinshare : 0x1057 at _OFF_Region
// MCU Ctrl : 0xFE57 at _PIN_B24_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B24_OFF_REGION                     (_PIN_B24_TXA3P_10B)

typedef enum
{
    _PIN_B24_HI_Z = 0x00,
    _PIN_B24_GPI = 0x01,
    _PIN_B24_TXA3P_10B = 0x04,
    _PIN_B24_NC = _PIN_B24_GPI,
} EnumPinshareInfoPINB24;

//---------------------------------------------------------------------------
// Function : TXA3N
// Pinshare : 0x1058 at _OFF_Region
// MCU Ctrl : 0xFE58 at _PIN_C23_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_C23_OFF_REGION                     (_PIN_C23_TXA3N_10B)

typedef enum
{
    _PIN_C23_HI_Z = 0x00,
    _PIN_C23_GPI = 0x01,
    _PIN_C23_TXA3N_10B = 0x04,
    _PIN_C23_NC = _PIN_C23_GPI,
} EnumPinshareInfoPINC23;

//---------------------------------------------------------------------------
// Function : TXACP
// Pinshare : 0x1059 at _OFF_Region
// MCU Ctrl : 0xFE59 at _PIN_B23_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B23_OFF_REGION                     (_PIN_B23_TXACP_10B)

typedef enum
{
    _PIN_B23_HI_Z = 0x00,
    _PIN_B23_GPI = 0x01,
    _PIN_B23_TXACP_10B = 0x04,
    _PIN_B23_NC = _PIN_B23_GPI,
} EnumPinshareInfoPINB23;

//---------------------------------------------------------------------------
// Function : TXACN
// Pinshare : 0x105A at _OFF_Region
// MCU Ctrl : 0xFE5A at _PIN_B22_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B22_OFF_REGION                     (_PIN_B22_TXACN_10B)

typedef enum
{
    _PIN_B22_HI_Z = 0x00,
    _PIN_B22_GPI = 0x01,
    _PIN_B22_TXACN_10B = 0x04,
    _PIN_B22_NC = _PIN_B22_GPI,
} EnumPinshareInfoPINB22;

//---------------------------------------------------------------------------
// Function : TXA2P
// Pinshare : 0x105B at _OFF_Region
// MCU Ctrl : 0xFE5B at _PIN_A22_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_A22_OFF_REGION                     (_PIN_A22_TXA2P_10B)

typedef enum
{
    _PIN_A22_HI_Z = 0x00,
    _PIN_A22_GPI = 0x01,
    _PIN_A22_TXA2P_10B = 0x04,
    _PIN_A22_NC = _PIN_A22_GPI,
} EnumPinshareInfoPINA22;

//---------------------------------------------------------------------------
// Function : TXA2N
// Pinshare : 0x105C at _OFF_Region
// MCU Ctrl : 0xFE5C at _PIN_C22_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_C22_OFF_REGION                     (_PIN_C22_TXA2N_10B)

typedef enum
{
    _PIN_C22_HI_Z = 0x00,
    _PIN_C22_GPI = 0x01,
    _PIN_C22_TXA2N_10B = 0x04,
    _PIN_C22_NC = _PIN_C22_GPI,
} EnumPinshareInfoPINC22;

//---------------------------------------------------------------------------
// Function : TXA1P
// Pinshare : 0x105D at _OFF_Region
// MCU Ctrl : 0xFE5D at _PIN_B20_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B20_OFF_REGION                     (_PIN_B20_TXA1P_10B)

typedef enum
{
    _PIN_B20_HI_Z = 0x00,
    _PIN_B20_GPI = 0x01,
    _PIN_B20_TXA1P_10B = 0x04,
    _PIN_B20_NC = _PIN_B20_GPI,
} EnumPinshareInfoPINB20;

//---------------------------------------------------------------------------
// Function : TXA1N
// Pinshare : 0x105E at _OFF_Region
// MCU Ctrl : 0xFE5E at _PIN_A20_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_A20_OFF_REGION                     (_PIN_A20_TXA1N_10B)

typedef enum
{
    _PIN_A20_HI_Z = 0x00,
    _PIN_A20_GPI = 0x01,
    _PIN_A20_TXA1N_10B = 0x04,
    _PIN_A20_NC = _PIN_A20_GPI,
} EnumPinshareInfoPINA20;

//---------------------------------------------------------------------------
// Function : TXA0P
// Pinshare : 0x105F at _OFF_Region
// MCU Ctrl : 0xFE5F at _PIN_B19_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B19_OFF_REGION                     (_PIN_B19_TXA0P_10B)

typedef enum
{
    _PIN_B19_HI_Z = 0x00,
    _PIN_B19_GPI = 0x01,
    _PIN_B19_TXA0P_10B = 0x04,
    _PIN_B19_NC = _PIN_B19_GPI,
} EnumPinshareInfoPINB19;

//---------------------------------------------------------------------------
// Function : TXA0N
// Pinshare : 0x1060 at _OFF_Region
// MCU Ctrl : 0x2200 at _PIN_A19_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_A19_OFF_REGION                     (_PIN_A19_TXA0N_10B)

typedef enum
{
    _PIN_A19_HI_Z = 0x00,
    _PIN_A19_GPI = 0x01,
    _PIN_A19_TXA0N_10B = 0x04,
    _PIN_A19_NC = _PIN_A19_GPI,
} EnumPinshareInfoPINA19;

//---------------------------------------------------------------------------
// Function : HDMI_CABLE_DETECT_3
// Pinshare : 0x1061
// MCU Ctrl : 0x2201 at _PIN_K9_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_K9                                 (_PIN_K9_GPI)

typedef enum
{
    _PIN_K9_GPI = 0x00,
    _PIN_K9_GPO_PP = 0x01,
    _PIN_K9_GPO_OD = 0x02,
    _PIN_K9_PWM5_PP = 0x03,
    _PIN_K9_PWM5_OD = 0x04,
    _PIN_K9_PWM5_DIMMING_PP = 0x05,
    _PIN_K9_PWM5_DIMMING = 0x06,
    _PIN_K9_TCON7 = 0x07,
    _PIN_K9_DCLK = 0x08,
    _PIN_K9_TTS_SCLK = 0x09,
    _PIN_K9_TEST12B_OUT0 = 0x0A,
    _PIN_K9_TEST12B_OUT1 = 0x0B,
    _PIN_K9_TEST12B_OUT2 = 0x0C,
    _PIN_K9_TEST12B_OUT3 = 0x0D,
    _PIN_K9_TEST12B_OUT4 = 0x0E,
    _PIN_K9_TEST12B_OUT5 = 0x0F,
    _PIN_K9_TEST12B_OUT6 = 0x10,
    _PIN_K9_TEST12B_OUT7 = 0x11,
    _PIN_K9_TEST12B_OUT8 = 0x12,
    _PIN_K9_TEST12B_OUT9 = 0x13,
    _PIN_K9_TEST12B_OUT10 = 0x14,
    _PIN_K9_TEST12B_OUT11 = 0x15,
    _PIN_K9_NC = _PIN_K9_GPO_PP,
} EnumPinshareInfoPINK9;

//---------------------------------------------------------------------------
// Function : HDMI_HPD_3
// Pinshare : 0x1062
// MCU Ctrl : 0x2202 at _PIN_H13_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_H13                                (_PIN_H13_GPO_OD)

typedef enum
{
    _PIN_H13_GPI = 0x00,
    _PIN_H13_GPO_PP = 0x01,
    _PIN_H13_GPO_OD = 0x02,
    _PIN_H13_TCON10 = 0x03,
    _PIN_H13_TTL_DEN = 0x04,
    _PIN_H13_TTS_CEB = 0x05,
    _PIN_H13_TEST12B_OUT0 = 0x06,
    _PIN_H13_TEST12B_OUT1 = 0x07,
    _PIN_H13_TEST12B_OUT2 = 0x08,
    _PIN_H13_TEST12B_OUT3 = 0x09,
    _PIN_H13_TEST12B_OUT4 = 0x0A,
    _PIN_H13_TEST12B_OUT5 = 0x0B,
    _PIN_H13_TEST12B_OUT6 = 0x0C,
    _PIN_H13_TEST12B_OUT7 = 0x0D,
    _PIN_H13_TEST12B_OUT8 = 0x0E,
    _PIN_H13_TEST12B_OUT9 = 0x0F,
    _PIN_H13_TEST12B_OUT10 = 0x10,
    _PIN_H13_TEST12B_OUT11 = 0x11,
    _PIN_H13_NC = _PIN_H13_GPO_PP,
} EnumPinshareInfoPINH13;

//---------------------------------------------------------------------------
// Function : HDMI_CABLE_DETECT_4
// Pinshare : 0x1063
// MCU Ctrl : 0x2203 at _PIN_H11_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_H11                                (_PIN_H11_GPI)

typedef enum
{
    _PIN_H11_GPI = 0x00,
    _PIN_H11_GPO_PP = 0x01,
    _PIN_H11_GPO_OD = 0x02,
    _PIN_H11_PWM_IN_0_1 = 0x03,
    _PIN_H11_TTL_DHS = 0x04,
    _PIN_H11_TCON12 = 0x05,
    _PIN_H11_TYPEC_GPIO4_0_PP = 0x06,
    _PIN_H11_TYPEC_GPIO4_0_OD = 0x07,
    _PIN_H11_TYPEC_GPIO5_0_PP = 0x08,
    _PIN_H11_TYPEC_GPIO5_0_OD = 0x09,
    _PIN_H11_TTS_SI = 0x0A,
    _PIN_H11_TEST12B_OUT0 = 0x0B,
    _PIN_H11_TEST12B_OUT1 = 0x0C,
    _PIN_H11_TEST12B_OUT2 = 0x0D,
    _PIN_H11_TEST12B_OUT3 = 0x0E,
    _PIN_H11_TEST12B_OUT4 = 0x0F,
    _PIN_H11_TEST12B_OUT5 = 0x10,
    _PIN_H11_TEST12B_OUT6 = 0x11,
    _PIN_H11_TEST12B_OUT7 = 0x12,
    _PIN_H11_TEST12B_OUT8 = 0x13,
    _PIN_H11_TEST12B_OUT9 = 0x14,
    _PIN_H11_TEST12B_OUT10 = 0x15,
    _PIN_H11_TEST12B_OUT11 = 0x16,
    _PIN_H11_NC = _PIN_H11_GPO_PP,
} EnumPinshareInfoPINH11;

//---------------------------------------------------------------------------
// Function : HDMI_HPD_4
// Pinshare : 0x1064
// MCU Ctrl : 0x2204 at _PIN_K8_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_K8                                 (_PIN_K8_GPO_OD)

typedef enum
{
    _PIN_K8_GPI = 0x00,
    _PIN_K8_GPO_PP = 0x01,
    _PIN_K8_GPO_OD = 0x02,
    _PIN_K8_TCON11 = 0x03,
    _PIN_K8_TTL_DVS = 0x04,
    _PIN_K8_TTS_SO = 0x05,
    _PIN_K8_TEST12B_OUT0 = 0x06,
    _PIN_K8_TEST12B_OUT1 = 0x07,
    _PIN_K8_TEST12B_OUT2 = 0x08,
    _PIN_K8_TEST12B_OUT3 = 0x09,
    _PIN_K8_TEST12B_OUT4 = 0x0A,
    _PIN_K8_TEST12B_OUT5 = 0x0B,
    _PIN_K8_TEST12B_OUT6 = 0x0C,
    _PIN_K8_TEST12B_OUT7 = 0x0D,
    _PIN_K8_TEST12B_OUT8 = 0x0E,
    _PIN_K8_TEST12B_OUT9 = 0x0F,
    _PIN_K8_TEST12B_OUT10 = 0x10,
    _PIN_K8_TEST12B_OUT11 = 0x11,
    _PIN_K8_NC = _PIN_K8_GPO_PP,
} EnumPinshareInfoPINK8;

//---------------------------------------------------------------------------
// Function : SY9228_SCL_0
// Pinshare : 0x1065
// MCU Ctrl : 0x2205 at _PIN_H12_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_H12                                (_PIN_H12_TPC_IICSCL_0_1)

typedef enum
{
    _PIN_H12_GPI = 0x00,
    _PIN_H12_GPO_PP = 0x01,
    _PIN_H12_GPO_OD = 0x02,
    _PIN_H12_TPC_IICSCL_0_1 = 0x03,
    _PIN_H12_TPC_IICSCL_1_1 = 0x04,
    _PIN_H12_SWDIO_0_3 = 0x05,
    _PIN_H12_TEST12B_OUT0 = 0x06,
    _PIN_H12_TEST12B_OUT1 = 0x07,
    _PIN_H12_TEST12B_OUT2 = 0x08,
    _PIN_H12_TEST12B_OUT3 = 0x09,
    _PIN_H12_TEST12B_OUT4 = 0x0A,
    _PIN_H12_TEST12B_OUT5 = 0x0B,
    _PIN_H12_TEST12B_OUT6 = 0x0C,
    _PIN_H12_TEST12B_OUT7 = 0x0D,
    _PIN_H12_TEST12B_OUT8 = 0x0E,
    _PIN_H12_TEST12B_OUT9 = 0x0F,
    _PIN_H12_TEST12B_OUT10 = 0x10,
    _PIN_H12_TEST12B_OUT11 = 0x11,
    _PIN_H12_NC = _PIN_H12_GPO_PP,
} EnumPinshareInfoPINH12;

//---------------------------------------------------------------------------
// Function : SY9228_SDA_0
// Pinshare : 0x1066
// MCU Ctrl : 0x2206 at _PIN_J8_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_J8                                 (_PIN_J8_TPC_IICSDA_0_1)

typedef enum
{
    _PIN_J8_GPI = 0x00,
    _PIN_J8_GPO_PP = 0x01,
    _PIN_J8_GPO_OD = 0x02,
    _PIN_J8_TPC_IICSDA_0_1 = 0x03,
    _PIN_J8_TPC_IICSDA_1_1 = 0x04,
    _PIN_J8_SWDCLK_0_3 = 0x05,
    _PIN_J8_TEST12B_OUT0 = 0x06,
    _PIN_J8_TEST12B_OUT1 = 0x07,
    _PIN_J8_TEST12B_OUT2 = 0x08,
    _PIN_J8_TEST12B_OUT3 = 0x09,
    _PIN_J8_TEST12B_OUT4 = 0x0A,
    _PIN_J8_TEST12B_OUT5 = 0x0B,
    _PIN_J8_TEST12B_OUT6 = 0x0C,
    _PIN_J8_TEST12B_OUT7 = 0x0D,
    _PIN_J8_TEST12B_OUT8 = 0x0E,
    _PIN_J8_TEST12B_OUT9 = 0x0F,
    _PIN_J8_TEST12B_OUT10 = 0x10,
    _PIN_J8_TEST12B_OUT11 = 0x11,
    _PIN_J8_NC = _PIN_J8_GPO_PP,
} EnumPinshareInfoPINJ8;

//---------------------------------------------------------------------------
// Function : VCCK_OFF_EN
// Pinshare : 0x1067
// MCU Ctrl : 0x2207 at _PIN_F9_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_F9                                 (_PIN_F9_GPO_OD)

typedef enum
{
    _PIN_F9_GPI = 0x00,
    _PIN_F9_GPO_PP = 0x01,
    _PIN_F9_GPO_OD = 0x02,
    _PIN_F9_EXT_UART_RX_0_3 = 0x03,
    _PIN_F9_EXT_UART_RX_1_3 = 0x04,
    _PIN_F9_EXT_UART_RX_2_3 = 0x05,
    _PIN_F9_M1_IDOMAIN_DEN_OUT = 0x06,
    _PIN_F9_TEST12B_OUT0 = 0x07,
    _PIN_F9_TEST12B_OUT1 = 0x08,
    _PIN_F9_TEST12B_OUT2 = 0x09,
    _PIN_F9_TEST12B_OUT3 = 0x0A,
    _PIN_F9_TEST12B_OUT4 = 0x0B,
    _PIN_F9_TEST12B_OUT5 = 0x0C,
    _PIN_F9_TEST12B_OUT6 = 0x0D,
    _PIN_F9_TEST12B_OUT7 = 0x0E,
    _PIN_F9_TEST12B_OUT8 = 0x0F,
    _PIN_F9_TEST12B_OUT9 = 0x10,
    _PIN_F9_TEST12B_OUT10 = 0x11,
    _PIN_F9_TEST12B_OUT11 = 0x12,
    _PIN_F9_NC = _PIN_F9_GPO_PP,
} EnumPinshareInfoPINF9;

//---------------------------------------------------------------------------
// Function : D1_SBU2
// Pinshare : 0x1068
// MCU Ctrl : 0x2208 at _PIN_F11_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_F11                                (_PIN_F11_DPRX_AUX_P_1)

typedef enum
{
    _PIN_F11_GPI = 0x00,
    _PIN_F11_GPO_PP = 0x01,
    _PIN_F11_GPO_OD = 0x02,
    _PIN_F11_DPRX_AUX_P_1 = 0x03,
    _PIN_F11_TEST12B_OUT0 = 0x04,
    _PIN_F11_TEST12B_OUT1 = 0x05,
    _PIN_F11_TEST12B_OUT2 = 0x06,
    _PIN_F11_TEST12B_OUT3 = 0x07,
    _PIN_F11_TEST12B_OUT4 = 0x08,
    _PIN_F11_TEST12B_OUT5 = 0x09,
    _PIN_F11_TEST12B_OUT6 = 0x0A,
    _PIN_F11_TEST12B_OUT7 = 0x0B,
    _PIN_F11_TEST12B_OUT8 = 0x0C,
    _PIN_F11_TEST12B_OUT9 = 0x0D,
    _PIN_F11_TEST12B_OUT10 = 0x0E,
    _PIN_F11_TEST12B_OUT11 = 0x0F,
    _PIN_F11_NC = _PIN_F11_GPO_PP,
} EnumPinshareInfoPINF11;

//---------------------------------------------------------------------------
// Function : D1_SBU1
// Pinshare : 0x1069
// MCU Ctrl : 0x2209 at _PIN_F12_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_F12                                (_PIN_F12_DPRX_AUX_N_1)

typedef enum
{
    _PIN_F12_GPI = 0x00,
    _PIN_F12_GPO_PP = 0x01,
    _PIN_F12_GPO_OD = 0x02,
    _PIN_F12_DPRX_AUX_N_1 = 0x03,
    _PIN_F12_TEST12B_OUT0 = 0x04,
    _PIN_F12_TEST12B_OUT1 = 0x05,
    _PIN_F12_TEST12B_OUT2 = 0x06,
    _PIN_F12_TEST12B_OUT3 = 0x07,
    _PIN_F12_TEST12B_OUT4 = 0x08,
    _PIN_F12_TEST12B_OUT5 = 0x09,
    _PIN_F12_TEST12B_OUT6 = 0x0A,
    _PIN_F12_TEST12B_OUT7 = 0x0B,
    _PIN_F12_TEST12B_OUT8 = 0x0C,
    _PIN_F12_TEST12B_OUT9 = 0x0D,
    _PIN_F12_TEST12B_OUT10 = 0x0E,
    _PIN_F12_TEST12B_OUT11 = 0x0F,
    _PIN_F12_NC = _PIN_F12_GPO_PP,
} EnumPinshareInfoPINF12;

//---------------------------------------------------------------------------
// Function : AUX_CHP_2
// Pinshare : 0x106A
// MCU Ctrl : 0x220A at _PIN_E13_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_E13                                (_PIN_E13_DPRX_AUX_P_2)

typedef enum
{
    _PIN_E13_GPI = 0x00,
    _PIN_E13_GPO_PP = 0x01,
    _PIN_E13_GPO_OD = 0x02,
    _PIN_E13_DPRX_AUX_P_2 = 0x03,
    _PIN_E13_TEST12B_OUT0 = 0x04,
    _PIN_E13_TEST12B_OUT1 = 0x05,
    _PIN_E13_TEST12B_OUT2 = 0x06,
    _PIN_E13_TEST12B_OUT3 = 0x07,
    _PIN_E13_TEST12B_OUT4 = 0x08,
    _PIN_E13_TEST12B_OUT5 = 0x09,
    _PIN_E13_TEST12B_OUT6 = 0x0A,
    _PIN_E13_TEST12B_OUT7 = 0x0B,
    _PIN_E13_TEST12B_OUT8 = 0x0C,
    _PIN_E13_TEST12B_OUT9 = 0x0D,
    _PIN_E13_TEST12B_OUT10 = 0x0E,
    _PIN_E13_TEST12B_OUT11 = 0x0F,
    _PIN_E13_NC = _PIN_E13_GPO_PP,
} EnumPinshareInfoPINE13;

//---------------------------------------------------------------------------
// Function : AUX_CHN_2
// Pinshare : 0x106B
// MCU Ctrl : 0x220B at _PIN_F13_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_F13                                (_PIN_F13_DPRX_AUX_N_2)

typedef enum
{
    _PIN_F13_GPI = 0x00,
    _PIN_F13_GPO_PP = 0x01,
    _PIN_F13_GPO_OD = 0x02,
    _PIN_F13_DPRX_AUX_N_2 = 0x03,
    _PIN_F13_TEST12B_OUT0 = 0x04,
    _PIN_F13_TEST12B_OUT1 = 0x05,
    _PIN_F13_TEST12B_OUT2 = 0x06,
    _PIN_F13_TEST12B_OUT3 = 0x07,
    _PIN_F13_TEST12B_OUT4 = 0x08,
    _PIN_F13_TEST12B_OUT5 = 0x09,
    _PIN_F13_TEST12B_OUT6 = 0x0A,
    _PIN_F13_TEST12B_OUT7 = 0x0B,
    _PIN_F13_TEST12B_OUT8 = 0x0C,
    _PIN_F13_TEST12B_OUT9 = 0x0D,
    _PIN_F13_TEST12B_OUT10 = 0x0E,
    _PIN_F13_TEST12B_OUT11 = 0x0F,
    _PIN_F13_NC = _PIN_F13_GPO_PP,
} EnumPinshareInfoPINF13;

//---------------------------------------------------------------------------
// Function : DDR_PW_EN
// Pinshare : 0x106C
// MCU Ctrl : 0x220C at _PIN_E12_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_E12                                (_PIN_E12_GPO_OD)

typedef enum
{
    _PIN_E12_GPI = 0x00,
    _PIN_E12_GPO_PP = 0x01,
    _PIN_E12_GPO_OD = 0x02,
    _PIN_E12_PWM3_PP = 0x03,
    _PIN_E12_PWM3_OD = 0x04,
    _PIN_E12_PWM3_DIMMING_PP = 0x05,
    _PIN_E12_PWM3_DIMMING = 0x06,
    _PIN_E12_TCON9 = 0x07,
    _PIN_E12_TEST12B_OUT0 = 0x08,
    _PIN_E12_TEST12B_OUT1 = 0x09,
    _PIN_E12_TEST12B_OUT2 = 0x0A,
    _PIN_E12_TEST12B_OUT3 = 0x0B,
    _PIN_E12_TEST12B_OUT4 = 0x0C,
    _PIN_E12_TEST12B_OUT5 = 0x0D,
    _PIN_E12_TEST12B_OUT6 = 0x0E,
    _PIN_E12_TEST12B_OUT7 = 0x0F,
    _PIN_E12_TEST12B_OUT8 = 0x10,
    _PIN_E12_TEST12B_OUT9 = 0x11,
    _PIN_E12_TEST12B_OUT10 = 0x12,
    _PIN_E12_TEST12B_OUT11 = 0x13,
    _PIN_E12_NC = _PIN_E12_GPO_PP,
} EnumPinshareInfoPINE12;

//---------------------------------------------------------------------------
// Function : onBACKLITE
// Pinshare : 0x106D
// MCU Ctrl : 0x220D at _PIN_G9_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_G9                                 (_PIN_G9_GPO_OD)

typedef enum
{
    _PIN_G9_GPI = 0x00,
    _PIN_G9_GPO_PP = 0x01,
    _PIN_G9_GPO_OD = 0x02,
    _PIN_G9_EXT_UART_TX_0_3 = 0x03,
    _PIN_G9_EXT_UART_TX_1_3 = 0x04,
    _PIN_G9_EXT_UART_TX_2_3 = 0x05,
    _PIN_G9_TEST12B_OUT0 = 0x06,
    _PIN_G9_TEST12B_OUT1 = 0x07,
    _PIN_G9_TEST12B_OUT2 = 0x08,
    _PIN_G9_TEST12B_OUT3 = 0x09,
    _PIN_G9_TEST12B_OUT4 = 0x0A,
    _PIN_G9_TEST12B_OUT5 = 0x0B,
    _PIN_G9_TEST12B_OUT6 = 0x0C,
    _PIN_G9_TEST12B_OUT7 = 0x0D,
    _PIN_G9_TEST12B_OUT8 = 0x0E,
    _PIN_G9_TEST12B_OUT9 = 0x0F,
    _PIN_G9_TEST12B_OUT10 = 0x10,
    _PIN_G9_TEST12B_OUT11 = 0x11,
    _PIN_G9_NC = _PIN_G9_GPO_PP,
} EnumPinshareInfoPING9;

//---------------------------------------------------------------------------
// Function : EDID_WP
// Pinshare : 0x106E
// MCU Ctrl : 0x220E at _PIN_F8_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_F8                                 (_PIN_F8_GPO_OD)

typedef enum
{
    _PIN_F8_GPI = 0x00,
    _PIN_F8_GPO_PP = 0x01,
    _PIN_F8_GPO_OD = 0x02,
    _PIN_F8_IRDA_IN_0_0 = 0x03,
    _PIN_F8_PWM2_PP = 0x04,
    _PIN_F8_PWM2_OD = 0x05,
    _PIN_F8_PWM2_DIMMING_PP = 0x06,
    _PIN_F8_PWM2_DIMMING = 0x07,
    _PIN_F8_TCON8 = 0x08,
    _PIN_F8_INT0_5 = 0x09,
    _PIN_F8_INT1_5 = 0x0A,
    _PIN_F8_TEST12B_OUT0 = 0x0B,
    _PIN_F8_TEST12B_OUT1 = 0x0C,
    _PIN_F8_TEST12B_OUT2 = 0x0D,
    _PIN_F8_TEST12B_OUT3 = 0x0E,
    _PIN_F8_TEST12B_OUT4 = 0x0F,
    _PIN_F8_TEST12B_OUT5 = 0x10,
    _PIN_F8_TEST12B_OUT6 = 0x11,
    _PIN_F8_TEST12B_OUT7 = 0x12,
    _PIN_F8_TEST12B_OUT8 = 0x13,
    _PIN_F8_TEST12B_OUT9 = 0x14,
    _PIN_F8_TEST12B_OUT10 = 0x15,
    _PIN_F8_TEST12B_OUT11 = 0x16,
    _PIN_F8_NC = _PIN_F8_GPO_PP,
} EnumPinshareInfoPINF8;

//---------------------------------------------------------------------------
// Function : SY9228_SCL_1
// Pinshare : 0x106F
// MCU Ctrl : 0x220F at _PIN_E3_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_E3                                 (_PIN_E3_TPC_IICSCL_1_0)

typedef enum
{
    _PIN_E3_GPI = 0x00,
    _PIN_E3_GPO_PP = 0x01,
    _PIN_E3_GPO_OD = 0x02,
    _PIN_E3_TPC_IICSCL_0_0 = 0x03,
    _PIN_E3_TPC_IICSCL_1_0 = 0x04,
    _PIN_E3_TEST12B_OUT0 = 0x05,
    _PIN_E3_TEST12B_OUT1 = 0x06,
    _PIN_E3_TEST12B_OUT2 = 0x07,
    _PIN_E3_TEST12B_OUT3 = 0x08,
    _PIN_E3_TEST12B_OUT4 = 0x09,
    _PIN_E3_TEST12B_OUT5 = 0x0A,
    _PIN_E3_TEST12B_OUT6 = 0x0B,
    _PIN_E3_TEST12B_OUT7 = 0x0C,
    _PIN_E3_TEST12B_OUT8 = 0x0D,
    _PIN_E3_TEST12B_OUT9 = 0x0E,
    _PIN_E3_TEST12B_OUT10 = 0x0F,
    _PIN_E3_TEST12B_OUT11 = 0x10,
    _PIN_E3_NC = _PIN_E3_GPO_PP,
} EnumPinshareInfoPINE3;

//---------------------------------------------------------------------------
// Function : SY9228_SDA_1
// Pinshare : 0x1070
// MCU Ctrl : 0x2210 at _PIN_H8_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_H8                                 (_PIN_H8_TPC_IICSDA_1_0)

typedef enum
{
    _PIN_H8_GPI = 0x00,
    _PIN_H8_GPO_PP = 0x01,
    _PIN_H8_GPO_OD = 0x02,
    _PIN_H8_TPC_IICSDA_0_0 = 0x03,
    _PIN_H8_TPC_IICSDA_1_0 = 0x04,
    _PIN_H8_TEST12B_OUT0 = 0x05,
    _PIN_H8_TEST12B_OUT1 = 0x06,
    _PIN_H8_TEST12B_OUT2 = 0x07,
    _PIN_H8_TEST12B_OUT3 = 0x08,
    _PIN_H8_TEST12B_OUT4 = 0x09,
    _PIN_H8_TEST12B_OUT5 = 0x0A,
    _PIN_H8_TEST12B_OUT6 = 0x0B,
    _PIN_H8_TEST12B_OUT7 = 0x0C,
    _PIN_H8_TEST12B_OUT8 = 0x0D,
    _PIN_H8_TEST12B_OUT9 = 0x0E,
    _PIN_H8_TEST12B_OUT10 = 0x0F,
    _PIN_H8_TEST12B_OUT11 = 0x10,
    _PIN_H8_NC = _PIN_H8_GPO_PP,
} EnumPinshareInfoPINH8;

//---------------------------------------------------------------------------
// Function : DDCSCL_ISP
// Pinshare : 0x1071
// MCU Ctrl : 0x2211 at _PIN_D5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_D5                                 (_PIN_D5_DDCSCL_ISP)

typedef enum
{
    _PIN_D5_GPI = 0x00,
    _PIN_D5_GPO_PP = 0x01,
    _PIN_D5_GPO_OD = 0x02,
    _PIN_D5_DDCSCL_ISP = 0x03,
    _PIN_D5_IICSCL_0_0 = 0x04,
    _PIN_D5_IICSCL_1_0 = 0x05,
    _PIN_D5_SWDCLK_0_0 = 0x06,
    _PIN_D5_USB_SPI_CLK_0_6 = 0x07,
    _PIN_D5_USB_SPI_CLK_1_6 = 0x08,
    _PIN_D5_USB_SPI_CLK_2_6 = 0x09,
    _PIN_D5_TEST12B_OUT3 = 0x0A,
    _PIN_D5_TEST12B_OUT4 = 0x0B,
    _PIN_D5_TEST12B_OUT5 = 0x0C,
    _PIN_D5_TEST12B_OUT6 = 0x0D,
    _PIN_D5_TEST12B_OUT7 = 0x0E,
    _PIN_D5_TEST12B_OUT8 = 0x0F,
    _PIN_D5_TEST12B_OUT9 = 0x10,
    _PIN_D5_TEST12B_OUT10 = 0x11,
    _PIN_D5_TEST12B_OUT11 = 0x12,
    _PIN_D5_NC = _PIN_D5_GPO_PP,
} EnumPinshareInfoPIND5;

//---------------------------------------------------------------------------
// Function : DDCSDA_ISP
// Pinshare : 0x1072
// MCU Ctrl : 0x2212 at _PIN_D4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_D4                                 (_PIN_D4_DDCSDA_ISP)

typedef enum
{
    _PIN_D4_GPI = 0x00,
    _PIN_D4_GPO_PP = 0x01,
    _PIN_D4_GPO_OD = 0x02,
    _PIN_D4_DDCSDA_ISP = 0x03,
    _PIN_D4_IICSDA_0_0 = 0x04,
    _PIN_D4_IICSDA_1_0 = 0x05,
    _PIN_D4_SWDIO_0_0 = 0x06,
    _PIN_D4_USB_SPI_CLK_0_7 = 0x07,
    _PIN_D4_USB_SPI_CLK_1_7 = 0x08,
    _PIN_D4_USB_SPI_CLK_2_7 = 0x09,
    _PIN_D4_TEST12B_OUT3 = 0x0A,
    _PIN_D4_TEST12B_OUT4 = 0x0B,
    _PIN_D4_TEST12B_OUT5 = 0x0C,
    _PIN_D4_TEST12B_OUT6 = 0x0D,
    _PIN_D4_TEST12B_OUT7 = 0x0E,
    _PIN_D4_TEST12B_OUT8 = 0x0F,
    _PIN_D4_TEST12B_OUT9 = 0x10,
    _PIN_D4_TEST12B_OUT10 = 0x11,
    _PIN_D4_TEST12B_OUT11 = 0x12,
    _PIN_D4_NC = _PIN_D4_GPO_PP,
} EnumPinshareInfoPIND4;

//---------------------------------------------------------------------------
// Function : SY9228_INT_0
// Pinshare : 0x1073
// MCU Ctrl : 0x2213 at _PIN_D3_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_D3                                 (_PIN_D3_GPI)

typedef enum
{
    _PIN_D3_GPI = 0x00,
    _PIN_D3_GPO_PP = 0x01,
    _PIN_D3_GPO_OD = 0x02,
    _PIN_D3_SD3 = 0x03,
    _PIN_D3_SPDIF3 = 0x04,
    _PIN_D3_IICSCL_0_1 = 0x05,
    _PIN_D3_IICSCL_1_1 = 0x06,
    _PIN_D3_TCON1 = 0x07,
    _PIN_D3_TEST12B_OUT0 = 0x08,
    _PIN_D3_TEST12B_OUT1 = 0x09,
    _PIN_D3_TEST12B_OUT2 = 0x0A,
    _PIN_D3_TEST12B_OUT3 = 0x0B,
    _PIN_D3_TEST12B_OUT4 = 0x0C,
    _PIN_D3_TEST12B_OUT5 = 0x0D,
    _PIN_D3_TEST12B_OUT6 = 0x0E,
    _PIN_D3_TEST12B_OUT7 = 0x0F,
    _PIN_D3_TEST12B_OUT8 = 0x10,
    _PIN_D3_TEST12B_OUT9 = 0x11,
    _PIN_D3_TEST12B_OUT10 = 0x12,
    _PIN_D3_TEST12B_OUT11 = 0x13,
    _PIN_D3_NC = _PIN_D3_GPO_PP,
} EnumPinshareInfoPIND3;

//---------------------------------------------------------------------------
// Function : USB_P3_EN
// Pinshare : 0x1074
// MCU Ctrl : 0x2214 at _PIN_H7_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_H7                                 (_PIN_H7_GPO_OD)

typedef enum
{
    _PIN_H7_GPI = 0x00,
    _PIN_H7_GPO_PP = 0x01,
    _PIN_H7_GPO_OD = 0x02,
    _PIN_H7_SD2 = 0x03,
    _PIN_H7_SPDIF2 = 0x04,
    _PIN_H7_IICSDA_0_1 = 0x05,
    _PIN_H7_IICSDA_1_1 = 0x06,
    _PIN_H7_PWM_UPD_SYNC_0_0_PP = 0x07,
    _PIN_H7_TEST12B_OUT0 = 0x08,
    _PIN_H7_TEST12B_OUT1 = 0x09,
    _PIN_H7_TEST12B_OUT2 = 0x0A,
    _PIN_H7_TEST12B_OUT3 = 0x0B,
    _PIN_H7_TEST12B_OUT4 = 0x0C,
    _PIN_H7_TEST12B_OUT5 = 0x0D,
    _PIN_H7_TEST12B_OUT6 = 0x0E,
    _PIN_H7_TEST12B_OUT7 = 0x0F,
    _PIN_H7_TEST12B_OUT8 = 0x10,
    _PIN_H7_TEST12B_OUT9 = 0x11,
    _PIN_H7_TEST12B_OUT10 = 0x12,
    _PIN_H7_TEST12B_OUT11 = 0x13,
    _PIN_H7_NC = _PIN_H7_GPO_PP,
} EnumPinshareInfoPINH7;

//---------------------------------------------------------------------------
// Function : DP_CFG1
// Pinshare : 0x1075
// MCU Ctrl : 0x2215 at _PIN_C5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_C5                                 (_PIN_C5_GPO_PP)

typedef enum
{
    _PIN_C5_GPI = 0x00,
    _PIN_C5_GPO_PP = 0x01,
    _PIN_C5_GPO_OD = 0x02,
    _PIN_C5_SD1 = 0x03,
    _PIN_C5_SPDIF1 = 0x04,
    _PIN_C5_IRQB = 0x05,
    _PIN_C5_TCON2 = 0x06,
    _PIN_C5_TEST12B_OUT0 = 0x07,
    _PIN_C5_TEST12B_OUT1 = 0x08,
    _PIN_C5_TEST12B_OUT2 = 0x09,
    _PIN_C5_TEST12B_OUT3 = 0x0A,
    _PIN_C5_TEST12B_OUT4 = 0x0B,
    _PIN_C5_TEST12B_OUT5 = 0x0C,
    _PIN_C5_TEST12B_OUT6 = 0x0D,
    _PIN_C5_TEST12B_OUT7 = 0x0E,
    _PIN_C5_TEST12B_OUT8 = 0x0F,
    _PIN_C5_TEST12B_OUT9 = 0x10,
    _PIN_C5_TEST12B_OUT10 = 0x11,
    _PIN_C5_TEST12B_OUT11 = 0x12,
    _PIN_C5_NC = _PIN_C5_GPO_PP,
} EnumPinshareInfoPINC5;

//---------------------------------------------------------------------------
// Function : SY9228_EN_0
// Pinshare : 0x1076
// MCU Ctrl : 0x2216 at _PIN_B5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B5                                 (_PIN_B5_GPO_PP)

typedef enum
{
    _PIN_B5_GPI = 0x00,
    _PIN_B5_GPO_PP = 0x01,
    _PIN_B5_GPO_OD = 0x02,
    _PIN_B5_SD0 = 0x03,
    _PIN_B5_SPDIF0 = 0x04,
    _PIN_B5_TCON3 = 0x05,
    _PIN_B5_TEST12B_OUT0 = 0x06,
    _PIN_B5_TEST12B_OUT1 = 0x07,
    _PIN_B5_TEST12B_OUT2 = 0x08,
    _PIN_B5_TEST12B_OUT3 = 0x09,
    _PIN_B5_TEST12B_OUT4 = 0x0A,
    _PIN_B5_TEST12B_OUT5 = 0x0B,
    _PIN_B5_TEST12B_OUT6 = 0x0C,
    _PIN_B5_TEST12B_OUT7 = 0x0D,
    _PIN_B5_TEST12B_OUT8 = 0x0E,
    _PIN_B5_TEST12B_OUT9 = 0x0F,
    _PIN_B5_TEST12B_OUT10 = 0x10,
    _PIN_B5_TEST12B_OUT11 = 0x11,
    _PIN_B5_NC = _PIN_B5_GPO_PP,
} EnumPinshareInfoPINB5;

//---------------------------------------------------------------------------
// Function : D0_VBUS
// Pinshare : 0x1077
// MCU Ctrl : 0x2217 at _PIN_B4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B4                                 (_PIN_B4_GPO_PP)

typedef enum
{
    _PIN_B4_GPI = 0x00,
    _PIN_B4_GPO_PP = 0x01,
    _PIN_B4_GPO_OD = 0x02,
    _PIN_B4_WS = 0x03,
    _PIN_B4_TYPEC_GPIO6_1_PP = 0x04,
    _PIN_B4_TYPEC_GPIO6_1_OD = 0x05,
    _PIN_B4_TYPEC_GPIO7_1_PP = 0x06,
    _PIN_B4_TYPEC_GPIO7_1_OD = 0x07,
    _PIN_B4_TCON4 = 0x08,
    _PIN_B4_TEST12B_OUT0 = 0x09,
    _PIN_B4_TEST12B_OUT1 = 0x0A,
    _PIN_B4_TEST12B_OUT2 = 0x0B,
    _PIN_B4_TEST12B_OUT3 = 0x0C,
    _PIN_B4_TEST12B_OUT4 = 0x0D,
    _PIN_B4_TEST12B_OUT5 = 0x0E,
    _PIN_B4_TEST12B_OUT6 = 0x0F,
    _PIN_B4_TEST12B_OUT7 = 0x10,
    _PIN_B4_TEST12B_OUT8 = 0x11,
    _PIN_B4_TEST12B_OUT9 = 0x12,
    _PIN_B4_TEST12B_OUT10 = 0x13,
    _PIN_B4_TEST12B_OUT11 = 0x14,
    _PIN_B4_NC = _PIN_B4_GPO_PP,
} EnumPinshareInfoPINB4;

//---------------------------------------------------------------------------
// Function : DDCSCL_3
// Pinshare : 0x1078
// MCU Ctrl : 0x2218 at _PIN_C4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_C4                                 (_PIN_C4_DDCSCL_3)

typedef enum
{
    _PIN_C4_GPI = 0x00,
    _PIN_C4_GPO_PP = 0x01,
    _PIN_C4_GPO_OD = 0x02,
    _PIN_C4_DDCSCL_3 = 0x03,
    _PIN_C4_SWDCLK_0_1 = 0x04,
    _PIN_C4_TEST12B_OUT0 = 0x05,
    _PIN_C4_TEST12B_OUT1 = 0x06,
    _PIN_C4_TEST12B_OUT2 = 0x07,
    _PIN_C4_TEST12B_OUT3 = 0x08,
    _PIN_C4_TEST12B_OUT4 = 0x09,
    _PIN_C4_TEST12B_OUT5 = 0x0A,
    _PIN_C4_TEST12B_OUT6 = 0x0B,
    _PIN_C4_TEST12B_OUT7 = 0x0C,
    _PIN_C4_TEST12B_OUT8 = 0x0D,
    _PIN_C4_TEST12B_OUT9 = 0x0E,
    _PIN_C4_TEST12B_OUT10 = 0x0F,
    _PIN_C4_TEST12B_OUT11 = 0x10,
    _PIN_C4_NC = _PIN_C4_GPO_PP,
} EnumPinshareInfoPINC4;

//---------------------------------------------------------------------------
// Function : DDCSDA_3
// Pinshare : 0x1079
// MCU Ctrl : 0x2219 at _PIN_C3_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_C3                                 (_PIN_C3_DDCSDA_3)

typedef enum
{
    _PIN_C3_GPI = 0x00,
    _PIN_C3_GPO_PP = 0x01,
    _PIN_C3_GPO_OD = 0x02,
    _PIN_C3_DDCSDA_3 = 0x03,
    _PIN_C3_SWDIO_0_1 = 0x04,
    _PIN_C3_TEST12B_OUT0 = 0x05,
    _PIN_C3_TEST12B_OUT1 = 0x06,
    _PIN_C3_TEST12B_OUT2 = 0x07,
    _PIN_C3_TEST12B_OUT3 = 0x08,
    _PIN_C3_TEST12B_OUT4 = 0x09,
    _PIN_C3_TEST12B_OUT5 = 0x0A,
    _PIN_C3_TEST12B_OUT6 = 0x0B,
    _PIN_C3_TEST12B_OUT7 = 0x0C,
    _PIN_C3_TEST12B_OUT8 = 0x0D,
    _PIN_C3_TEST12B_OUT9 = 0x0E,
    _PIN_C3_TEST12B_OUT10 = 0x0F,
    _PIN_C3_TEST12B_OUT11 = 0x10,
    _PIN_C3_NC = _PIN_C3_GPO_PP,
} EnumPinshareInfoPINC3;

//---------------------------------------------------------------------------
// Function : SY9228_INT_1
// Pinshare : 0x107A
// MCU Ctrl : 0x221A at _PIN_J9_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_J9                                 (_PIN_J9_GPI)

typedef enum
{
    _PIN_J9_GPI = 0x00,
    _PIN_J9_GPO_PP = 0x01,
    _PIN_J9_GPO_OD = 0x02,
    _PIN_J9_USB_SPI_CLK_0_2 = 0x03,
    _PIN_J9_USB_SPI_CLK_1_2 = 0x04,
    _PIN_J9_USB_SPI_CLK_2_2 = 0x05,
    _PIN_J9_IICSCL_0_2 = 0x06,
    _PIN_J9_IICSCL_1_2 = 0x07,
    _PIN_J9_TTS_SCLK = 0x08,
    _PIN_J9_TEST12B_OUT0 = 0x09,
    _PIN_J9_TEST12B_OUT1 = 0x0A,
    _PIN_J9_TEST12B_OUT2 = 0x0B,
    _PIN_J9_TEST12B_OUT3 = 0x0C,
    _PIN_J9_TEST12B_OUT4 = 0x0D,
    _PIN_J9_TEST12B_OUT5 = 0x0E,
    _PIN_J9_TEST12B_OUT6 = 0x0F,
    _PIN_J9_TEST12B_OUT7 = 0x10,
    _PIN_J9_TEST12B_OUT8 = 0x11,
    _PIN_J9_TEST12B_OUT9 = 0x12,
    _PIN_J9_TEST12B_OUT10 = 0x13,
    _PIN_J9_TEST12B_OUT11 = 0x14,
    _PIN_J9_NC = _PIN_J9_GPO_PP,
} EnumPinshareInfoPINJ9;

//---------------------------------------------------------------------------
// Function : D3_EDID_SW1
// Pinshare : 0x107B
// MCU Ctrl : 0x221B at _PIN_E5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_E5                                 (_PIN_E5_GPO_OD)

typedef enum
{
    _PIN_E5_GPI = 0x00,
    _PIN_E5_GPO_PP = 0x01,
    _PIN_E5_GPO_OD = 0x02,
    _PIN_E5_USB_SPI_SI_0_2 = 0x03,
    _PIN_E5_USB_SPI_SI_1_2 = 0x04,
    _PIN_E5_USB_SPI_SI_2_2 = 0x05,
    _PIN_E5_IICSDA_0_2 = 0x06,
    _PIN_E5_IICSDA_1_2 = 0x07,
    _PIN_E5_TTS_CEB = 0x08,
    _PIN_E5_INT0_2 = 0x09,
    _PIN_E5_INT1_2 = 0x0A,
    _PIN_E5_TCON0 = 0x0B,
    _PIN_E5_TEST12B_OUT0 = 0x0C,
    _PIN_E5_TEST12B_OUT1 = 0x0D,
    _PIN_E5_TEST12B_OUT2 = 0x0E,
    _PIN_E5_TEST12B_OUT3 = 0x0F,
    _PIN_E5_TEST12B_OUT4 = 0x10,
    _PIN_E5_TEST12B_OUT5 = 0x11,
    _PIN_E5_TEST12B_OUT6 = 0x12,
    _PIN_E5_TEST12B_OUT7 = 0x13,
    _PIN_E5_TEST12B_OUT8 = 0x14,
    _PIN_E5_TEST12B_OUT9 = 0x15,
    _PIN_E5_TEST12B_OUT10 = 0x16,
    _PIN_E5_TEST12B_OUT11 = 0x17,
    _PIN_E5_NC = _PIN_E5_GPO_PP,
} EnumPinshareInfoPINE5;

//---------------------------------------------------------------------------
// Function : D4_EDID_SW1
// Pinshare : 0x107C
// MCU Ctrl : 0x221C at _PIN_D12_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_D12                                (_PIN_D12_GPO_OD)

typedef enum
{
    _PIN_D12_GPI = 0x00,
    _PIN_D12_GPO_PP = 0x01,
    _PIN_D12_GPO_OD = 0x02,
    _PIN_D12_USB_SPI_SO_0_2 = 0x03,
    _PIN_D12_USB_SPI_SO_1_2 = 0x04,
    _PIN_D12_USB_SPI_SO_2_2 = 0x05,
    _PIN_D12_TTS_SI = 0x06,
    _PIN_D12_TYPEC_GPIO0_0_PP = 0x07,
    _PIN_D12_TYPEC_GPIO0_0_OD = 0x08,
    _PIN_D12_TYPEC_GPIO1_0_PP = 0x09,
    _PIN_D12_TYPEC_GPIO1_0_OD = 0x0A,
    _PIN_D12_M1_IDOMAIN_HS_OUT = 0x0B,
    _PIN_D12_TEST12B_OUT0 = 0x0C,
    _PIN_D12_TEST12B_OUT1 = 0x0D,
    _PIN_D12_TEST12B_OUT2 = 0x0E,
    _PIN_D12_TEST12B_OUT3 = 0x0F,
    _PIN_D12_TEST12B_OUT4 = 0x10,
    _PIN_D12_TEST12B_OUT5 = 0x11,
    _PIN_D12_TEST12B_OUT6 = 0x12,
    _PIN_D12_TEST12B_OUT7 = 0x13,
    _PIN_D12_TEST12B_OUT8 = 0x14,
    _PIN_D12_TEST12B_OUT9 = 0x15,
    _PIN_D12_TEST12B_OUT10 = 0x16,
    _PIN_D12_TEST12B_OUT11 = 0x17,
    _PIN_D12_NC = _PIN_D12_GPO_PP,
} EnumPinshareInfoPIND12;

//---------------------------------------------------------------------------
// Function : SY9228_EN_1
// Pinshare : 0x107D
// MCU Ctrl : 0x221D at _PIN_D13_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_D13                                (_PIN_D13_GPO_PP)

typedef enum
{
    _PIN_D13_GPI = 0x00,
    _PIN_D13_GPO_PP = 0x01,
    _PIN_D13_GPO_OD = 0x02,
    _PIN_D13_USB_SPI_CEB0_0_2 = 0x03,
    _PIN_D13_USB_SPI_CEB0_1_2 = 0x04,
    _PIN_D13_USB_SPI_CEB0_2_2 = 0x05,
    _PIN_D13_IICSCL_0_3 = 0x06,
    _PIN_D13_IICSCL_1_3 = 0x07,
    _PIN_D13_TTS_SO = 0x08,
    _PIN_D13_TCON5 = 0x09,
    _PIN_D13_TEST12B_OUT0 = 0x0A,
    _PIN_D13_TEST12B_OUT1 = 0x0B,
    _PIN_D13_TEST12B_OUT2 = 0x0C,
    _PIN_D13_TEST12B_OUT3 = 0x0D,
    _PIN_D13_TEST12B_OUT4 = 0x0E,
    _PIN_D13_TEST12B_OUT5 = 0x0F,
    _PIN_D13_TEST12B_OUT6 = 0x10,
    _PIN_D13_TEST12B_OUT7 = 0x11,
    _PIN_D13_TEST12B_OUT8 = 0x12,
    _PIN_D13_TEST12B_OUT9 = 0x13,
    _PIN_D13_TEST12B_OUT10 = 0x14,
    _PIN_D13_TEST12B_OUT11 = 0x15,
    _PIN_D13_NC = _PIN_D13_GPO_PP,
} EnumPinshareInfoPIND13;

//---------------------------------------------------------------------------
// Function : D1_VBUS
// Pinshare : 0x107E
// MCU Ctrl : 0x221E at _PIN_H9_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_H9                                 (_PIN_H9_GPO_PP)

typedef enum
{
    _PIN_H9_GPI = 0x00,
    _PIN_H9_GPO_PP = 0x01,
    _PIN_H9_GPO_OD = 0x02,
    _PIN_H9_USB_SPI_CEB1_0_2 = 0x03,
    _PIN_H9_USB_SPI_CEB1_1_2 = 0x04,
    _PIN_H9_USB_SPI_CEB1_2_2 = 0x05,
    _PIN_H9_IICSDA_0_3 = 0x06,
    _PIN_H9_IICSDA_1_3 = 0x07,
    _PIN_H9_PWM_UPD_SYNC_0_1_PP = 0x08,
    _PIN_H9_INT0_3 = 0x09,
    _PIN_H9_INT1_3 = 0x0A,
    _PIN_H9_TCON5 = 0x0B,
    _PIN_H9_TEST12B_OUT0 = 0x0C,
    _PIN_H9_TEST12B_OUT1 = 0x0D,
    _PIN_H9_TEST12B_OUT2 = 0x0E,
    _PIN_H9_TEST12B_OUT3 = 0x0F,
    _PIN_H9_TEST12B_OUT4 = 0x10,
    _PIN_H9_TEST12B_OUT5 = 0x11,
    _PIN_H9_TEST12B_OUT6 = 0x12,
    _PIN_H9_TEST12B_OUT7 = 0x13,
    _PIN_H9_TEST12B_OUT8 = 0x14,
    _PIN_H9_TEST12B_OUT9 = 0x15,
    _PIN_H9_TEST12B_OUT10 = 0x16,
    _PIN_H9_TEST12B_OUT11 = 0x17,
    _PIN_H9_NC = _PIN_H9_GPO_PP,
} EnumPinshareInfoPINH9;

//---------------------------------------------------------------------------
// Function : D0_CAB_Det
// Pinshare : 0x107F
// MCU Ctrl : 0x221F at _PIN_A5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_A5                                 (_PIN_A5_GPI)

typedef enum
{
    _PIN_A5_GPI = 0x00,
    _PIN_A5_GPO_PP = 0x01,
    _PIN_A5_GPO_OD = 0x02,
    _PIN_A5_SCK = 0x03,
    _PIN_A5_IRDA_IN_0_1 = 0x04,
    _PIN_A5_TEST12B_OUT0 = 0x05,
    _PIN_A5_TEST12B_OUT1 = 0x06,
    _PIN_A5_TEST12B_OUT2 = 0x07,
    _PIN_A5_TEST12B_OUT3 = 0x08,
    _PIN_A5_TEST12B_OUT4 = 0x09,
    _PIN_A5_TEST12B_OUT5 = 0x0A,
    _PIN_A5_TEST12B_OUT6 = 0x0B,
    _PIN_A5_TEST12B_OUT7 = 0x0C,
    _PIN_A5_TEST12B_OUT8 = 0x0D,
    _PIN_A5_TEST12B_OUT9 = 0x0E,
    _PIN_A5_TEST12B_OUT10 = 0x0F,
    _PIN_A5_TEST12B_OUT11 = 0x10,
    _PIN_A5_NC = _PIN_A5_GPO_PP,
} EnumPinshareInfoPINA5;

//---------------------------------------------------------------------------
// Function : Panel_ON
// Pinshare : 0x1080
// MCU Ctrl : 0x2220 at _PIN_E11_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_E11                                (_PIN_E11_GPO_OD)

typedef enum
{
    _PIN_E11_GPI = 0x00,
    _PIN_E11_GPO_PP = 0x01,
    _PIN_E11_GPO_OD = 0x02,
    _PIN_E11_SPDIF2 = 0x03,
    _PIN_E11_SD2 = 0x04,
    _PIN_E11_EXT_UART_TX_0_2 = 0x05,
    _PIN_E11_EXT_UART_TX_1_2 = 0x06,
    _PIN_E11_EXT_UART_TX_2_2 = 0x07,
    _PIN_E11_USB_SPI_CLK_0_0 = 0x08,
    _PIN_E11_USB_SPI_CLK_1_0 = 0x09,
    _PIN_E11_USB_SPI_CLK_2_0 = 0x0A,
    _PIN_E11_TEST12B_OUT0 = 0x0B,
    _PIN_E11_TEST12B_OUT1 = 0x0C,
    _PIN_E11_TEST12B_OUT2 = 0x0D,
    _PIN_E11_TEST12B_OUT3 = 0x0E,
    _PIN_E11_TEST12B_OUT4 = 0x0F,
    _PIN_E11_TEST12B_OUT5 = 0x10,
    _PIN_E11_TEST12B_OUT6 = 0x11,
    _PIN_E11_TEST12B_OUT7 = 0x12,
    _PIN_E11_TEST12B_OUT8 = 0x13,
    _PIN_E11_TEST12B_OUT9 = 0x14,
    _PIN_E11_TEST12B_OUT10 = 0x15,
    _PIN_E11_TEST12B_OUT11 = 0x16,
    _PIN_E11_NC = _PIN_E11_GPO_PP,
} EnumPinshareInfoPINE11;

//---------------------------------------------------------------------------
// Function : SDIN_2
// Pinshare : 0x1081
// MCU Ctrl : 0x2221 at _PIN_V4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_V4                                 (_PIN_V4_USB_SPI_SI_2_0)

typedef enum
{
    _PIN_V4_GPI = 0x00,
    _PIN_V4_GPO_PP = 0x01,
    _PIN_V4_GPO_OD = 0x02,
    _PIN_V4_SD1 = 0x03,
    _PIN_V4_SPDIF1 = 0x04,
    _PIN_V4_EXT_UART_RX_0_2 = 0x05,
    _PIN_V4_EXT_UART_RX_1_2 = 0x06,
    _PIN_V4_EXT_UART_RX_2_2 = 0x07,
    _PIN_V4_USB_SPI_SI_0_0 = 0x08,
    _PIN_V4_USB_SPI_SI_1_0 = 0x09,
    _PIN_V4_USB_SPI_SI_2_0 = 0x0A,
    _PIN_V4_TCON1 = 0x0B,
    _PIN_V4_TEST12B_OUT0 = 0x0C,
    _PIN_V4_TEST12B_OUT1 = 0x0D,
    _PIN_V4_TEST12B_OUT2 = 0x0E,
    _PIN_V4_TEST12B_OUT3 = 0x0F,
    _PIN_V4_TEST12B_OUT4 = 0x10,
    _PIN_V4_TEST12B_OUT5 = 0x11,
    _PIN_V4_TEST12B_OUT6 = 0x12,
    _PIN_V4_TEST12B_OUT7 = 0x13,
    _PIN_V4_TEST12B_OUT8 = 0x14,
    _PIN_V4_TEST12B_OUT9 = 0x15,
    _PIN_V4_TEST12B_OUT10 = 0x16,
    _PIN_V4_TEST12B_OUT11 = 0x17,
    _PIN_V4_NC = _PIN_V4_GPO_PP,
} EnumPinshareInfoPINV4;

//---------------------------------------------------------------------------
// Function : SDOUT_2
// Pinshare : 0x1082
// MCU Ctrl : 0x2222 at _PIN_U4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_U4                                 (_PIN_U4_USB_SPI_SO_2_0)

typedef enum
{
    _PIN_U4_GPI = 0x00,
    _PIN_U4_GPO_PP = 0x01,
    _PIN_U4_GPO_OD = 0x02,
    _PIN_U4_SD0 = 0x03,
    _PIN_U4_SPDIF0 = 0x04,
    _PIN_U4_USB_SPI_SO_0_0 = 0x05,
    _PIN_U4_USB_SPI_SO_1_0 = 0x06,
    _PIN_U4_USB_SPI_SO_2_0 = 0x07,
    _PIN_U4_IICSCL_0_7 = 0x08,
    _PIN_U4_IICSCL_1_7 = 0x09,
    _PIN_U4_TEST12B_OUT0 = 0x0A,
    _PIN_U4_TEST12B_OUT1 = 0x0B,
    _PIN_U4_TEST12B_OUT2 = 0x0C,
    _PIN_U4_TEST12B_OUT3 = 0x0D,
    _PIN_U4_TEST12B_OUT4 = 0x0E,
    _PIN_U4_TEST12B_OUT5 = 0x0F,
    _PIN_U4_TEST12B_OUT6 = 0x10,
    _PIN_U4_TEST12B_OUT7 = 0x11,
    _PIN_U4_TEST12B_OUT8 = 0x12,
    _PIN_U4_TEST12B_OUT9 = 0x13,
    _PIN_U4_TEST12B_OUT10 = 0x14,
    _PIN_U4_TEST12B_OUT11 = 0x15,
    _PIN_U4_NC = _PIN_U4_GPO_PP,
} EnumPinshareInfoPINU4;

//---------------------------------------------------------------------------
// Function : CE_2
// Pinshare : 0x1083
// MCU Ctrl : 0x2223 at _PIN_G8_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_G8                                 (_PIN_G8_USB_SPI_CEB0_2_0)

typedef enum
{
    _PIN_G8_GPI = 0x00,
    _PIN_G8_GPO_PP = 0x01,
    _PIN_G8_GPO_OD = 0x02,
    _PIN_G8_WS = 0x03,
    _PIN_G8_USB_SPI_CEB0_0_0 = 0x04,
    _PIN_G8_USB_SPI_CEB0_1_0 = 0x05,
    _PIN_G8_USB_SPI_CEB0_2_0 = 0x06,
    _PIN_G8_IICSDA_0_7 = 0x07,
    _PIN_G8_IICSDA_1_7 = 0x08,
    _PIN_G8_TCON2 = 0x09,
    _PIN_G8_TEST12B_OUT0 = 0x0A,
    _PIN_G8_TEST12B_OUT1 = 0x0B,
    _PIN_G8_TEST12B_OUT2 = 0x0C,
    _PIN_G8_TEST12B_OUT3 = 0x0D,
    _PIN_G8_TEST12B_OUT4 = 0x0E,
    _PIN_G8_TEST12B_OUT5 = 0x0F,
    _PIN_G8_TEST12B_OUT6 = 0x10,
    _PIN_G8_TEST12B_OUT7 = 0x11,
    _PIN_G8_TEST12B_OUT8 = 0x12,
    _PIN_G8_TEST12B_OUT9 = 0x13,
    _PIN_G8_TEST12B_OUT10 = 0x14,
    _PIN_G8_TEST12B_OUT11 = 0x15,
    _PIN_G8_NC = _PIN_G8_GPO_PP,
} EnumPinshareInfoPING8;

//---------------------------------------------------------------------------
// Function : LED3_1
// Pinshare : 0x1084
// MCU Ctrl : 0x2224 at _PIN_E4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_E4                                 (_PIN_E4_GPO_PP)

typedef enum
{
    _PIN_E4_GPI = 0x00,
    _PIN_E4_GPO_PP = 0x01,
    _PIN_E4_GPO_OD = 0x02,
    _PIN_E4_SCK = 0x03,
    _PIN_E4_EXT_UART_TX_0_1 = 0x04,
    _PIN_E4_EXT_UART_TX_1_1 = 0x05,
    _PIN_E4_EXT_UART_TX_2_1 = 0x06,
    _PIN_E4_USB_SPI_CEB1_0_0 = 0x07,
    _PIN_E4_USB_SPI_CEB1_1_0 = 0x08,
    _PIN_E4_USB_SPI_CEB1_2_0 = 0x09,
    _PIN_E4_TCON3 = 0x0A,
    _PIN_E4_TEST12B_OUT0 = 0x0B,
    _PIN_E4_TEST12B_OUT1 = 0x0C,
    _PIN_E4_TEST12B_OUT2 = 0x0D,
    _PIN_E4_TEST12B_OUT3 = 0x0E,
    _PIN_E4_TEST12B_OUT4 = 0x0F,
    _PIN_E4_TEST12B_OUT5 = 0x10,
    _PIN_E4_TEST12B_OUT6 = 0x11,
    _PIN_E4_TEST12B_OUT7 = 0x12,
    _PIN_E4_TEST12B_OUT8 = 0x13,
    _PIN_E4_TEST12B_OUT9 = 0x14,
    _PIN_E4_TEST12B_OUT10 = 0x15,
    _PIN_E4_TEST12B_OUT11 = 0x16,
    _PIN_E4_NC = _PIN_E4_GPO_PP,
} EnumPinshareInfoPINE4;

//---------------------------------------------------------------------------
// Function : HOST_PW
// Pinshare : 0x1085
// MCU Ctrl : 0x2225 at _PIN_G7_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_G7                                 (_PIN_G7_GPO_OD)

typedef enum
{
    _PIN_G7_GPI = 0x00,
    _PIN_G7_GPO_PP = 0x01,
    _PIN_G7_GPO_OD = 0x02,
    _PIN_G7_MCK = 0x03,
    _PIN_G7_EXT_UART_RX_0_1 = 0x04,
    _PIN_G7_EXT_UART_RX_1_1 = 0x05,
    _PIN_G7_EXT_UART_RX_2_1 = 0x06,
    _PIN_G7_TCON4 = 0x07,
    _PIN_G7_TYPEC_GPIO4_1_PP = 0x08,
    _PIN_G7_TYPEC_GPIO4_1_OD = 0x09,
    _PIN_G7_TYPEC_GPIO5_1_PP = 0x0A,
    _PIN_G7_TYPEC_GPIO5_1_OD = 0x0B,
    _PIN_G7_TEST12B_OUT0 = 0x0C,
    _PIN_G7_TEST12B_OUT1 = 0x0D,
    _PIN_G7_TEST12B_OUT2 = 0x0E,
    _PIN_G7_TEST12B_OUT3 = 0x0F,
    _PIN_G7_TEST12B_OUT4 = 0x10,
    _PIN_G7_TEST12B_OUT5 = 0x11,
    _PIN_G7_TEST12B_OUT6 = 0x12,
    _PIN_G7_TEST12B_OUT7 = 0x13,
    _PIN_G7_TEST12B_OUT8 = 0x14,
    _PIN_G7_TEST12B_OUT9 = 0x15,
    _PIN_G7_TEST12B_OUT10 = 0x16,
    _PIN_G7_TEST12B_OUT11 = 0x17,
    _PIN_G7_NC = _PIN_G7_GPO_PP,
} EnumPinshareInfoPING7;

//---------------------------------------------------------------------------
// Function : ADJBACKLITE
// Pinshare : 0x1086
// MCU Ctrl : 0x2226 at _PIN_A2_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_A2                                 (_PIN_A2_PWM0_PP)

typedef enum
{
    _PIN_A2_GPI = 0x00,
    _PIN_A2_GPO_PP = 0x01,
    _PIN_A2_GPO_OD = 0x02,
    _PIN_A2_PWM_OUT_0_1 = 0x03,
    _PIN_A2_SD3 = 0x04,
    _PIN_A2_SPDIF3 = 0x05,
    _PIN_A2_PWM0_PP = 0x06,
    _PIN_A2_PWM0_OD = 0x07,
    _PIN_A2_PWM0_DIMMING_PP = 0x08,
    _PIN_A2_PWM0_DIMMING = 0x09,
    _PIN_A2_TCON0 = 0x0A,
    _PIN_A2_TEST12B_OUT0 = 0x0B,
    _PIN_A2_TEST12B_OUT1 = 0x0C,
    _PIN_A2_TEST12B_OUT2 = 0x0D,
    _PIN_A2_TEST12B_OUT3 = 0x0E,
    _PIN_A2_TEST12B_OUT4 = 0x0F,
    _PIN_A2_TEST12B_OUT5 = 0x10,
    _PIN_A2_TEST12B_OUT6 = 0x11,
    _PIN_A2_TEST12B_OUT7 = 0x12,
    _PIN_A2_TEST12B_OUT8 = 0x13,
    _PIN_A2_TEST12B_OUT9 = 0x14,
    _PIN_A2_TEST12B_OUT10 = 0x15,
    _PIN_A2_TEST12B_OUT11 = 0x16,
    _PIN_A2_NC = _PIN_A2_GPO_PP,
} EnumPinshareInfoPINA2;

//---------------------------------------------------------------------------
// Function : DDCSCL_4
// Pinshare : 0x1087
// MCU Ctrl : 0x2227 at _PIN_B3_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B3                                 (_PIN_B3_DDCSCL_4)

typedef enum
{
    _PIN_B3_GPI = 0x00,
    _PIN_B3_GPO_PP = 0x01,
    _PIN_B3_GPO_OD = 0x02,
    _PIN_B3_DDCSCL_4 = 0x03,
    _PIN_B3_SWDCLK_0_2 = 0x04,
    _PIN_B3_TEST12B_OUT0 = 0x05,
    _PIN_B3_TEST12B_OUT1 = 0x06,
    _PIN_B3_TEST12B_OUT2 = 0x07,
    _PIN_B3_TEST12B_OUT3 = 0x08,
    _PIN_B3_TEST12B_OUT4 = 0x09,
    _PIN_B3_TEST12B_OUT5 = 0x0A,
    _PIN_B3_TEST12B_OUT6 = 0x0B,
    _PIN_B3_TEST12B_OUT7 = 0x0C,
    _PIN_B3_TEST12B_OUT8 = 0x0D,
    _PIN_B3_TEST12B_OUT9 = 0x0E,
    _PIN_B3_TEST12B_OUT10 = 0x0F,
    _PIN_B3_TEST12B_OUT11 = 0x10,
    _PIN_B3_NC = _PIN_B3_GPO_PP,
} EnumPinshareInfoPINB3;

//---------------------------------------------------------------------------
// Function : DDCSDA_4
// Pinshare : 0x1088
// MCU Ctrl : 0x2228 at _PIN_B2_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_B2                                 (_PIN_B2_DDCSDA_4)

typedef enum
{
    _PIN_B2_GPI = 0x00,
    _PIN_B2_GPO_PP = 0x01,
    _PIN_B2_GPO_OD = 0x02,
    _PIN_B2_DDCSDA_4 = 0x03,
    _PIN_B2_SWDIO_0_2 = 0x04,
    _PIN_B2_TEST12B_OUT0 = 0x05,
    _PIN_B2_TEST12B_OUT1 = 0x06,
    _PIN_B2_TEST12B_OUT2 = 0x07,
    _PIN_B2_TEST12B_OUT3 = 0x08,
    _PIN_B2_TEST12B_OUT4 = 0x09,
    _PIN_B2_TEST12B_OUT5 = 0x0A,
    _PIN_B2_TEST12B_OUT6 = 0x0B,
    _PIN_B2_TEST12B_OUT7 = 0x0C,
    _PIN_B2_TEST12B_OUT8 = 0x0D,
    _PIN_B2_TEST12B_OUT9 = 0x0E,
    _PIN_B2_TEST12B_OUT10 = 0x0F,
    _PIN_B2_TEST12B_OUT11 = 0x10,
    _PIN_B2_NC = _PIN_B2_GPO_PP,
} EnumPinshareInfoPINB2;

//---------------------------------------------------------------------------
// Function : D1_CAB_Det
// Pinshare : 0x1089
// MCU Ctrl : 0x2229 at _PIN_A4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_A4                                 (_PIN_A4_GPI)

typedef enum
{
    _PIN_A4_GPI = 0x00,
    _PIN_A4_GPO_PP = 0x01,
    _PIN_A4_GPO_OD = 0x02,
    _PIN_A4_IRDA_IN_0_2 = 0x03,
    _PIN_A4_TCON7 = 0x04,
    _PIN_A4_TYPEC_GPIO2_0_PP = 0x05,
    _PIN_A4_TYPEC_GPIO2_0_OD = 0x06,
    _PIN_A4_TYPEC_GPIO3_0_PP = 0x07,
    _PIN_A4_TYPEC_GPIO3_0_OD = 0x08,
    _PIN_A4_TEST12B_OUT0 = 0x09,
    _PIN_A4_TEST12B_OUT1 = 0x0A,
    _PIN_A4_TEST12B_OUT2 = 0x0B,
    _PIN_A4_TEST12B_OUT3 = 0x0C,
    _PIN_A4_TEST12B_OUT4 = 0x0D,
    _PIN_A4_TEST12B_OUT5 = 0x0E,
    _PIN_A4_TEST12B_OUT6 = 0x0F,
    _PIN_A4_TEST12B_OUT7 = 0x10,
    _PIN_A4_TEST12B_OUT8 = 0x11,
    _PIN_A4_TEST12B_OUT9 = 0x12,
    _PIN_A4_TEST12B_OUT10 = 0x13,
    _PIN_A4_TEST12B_OUT11 = 0x14,
    _PIN_A4_NC = _PIN_A4_GPO_PP,
} EnumPinshareInfoPINA4;

//---------------------------------------------------------------------------
// Function : PD_GPIO1
// Pinshare : 0x108A
// MCU Ctrl : 0x222A at _PIN_A3_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_A3                                 (_PIN_A3_GPI)

typedef enum
{
    _PIN_A3_GPI = 0x00,
    _PIN_A3_GPO_PP = 0x01,
    _PIN_A3_GPO_OD = 0x02,
    _PIN_A3_MCK = 0x03,
    _PIN_A3_TYPEC_GPIO6_0_PP = 0x04,
    _PIN_A3_TYPEC_GPIO6_0_OD = 0x05,
    _PIN_A3_TYPEC_GPIO7_0_PP = 0x06,
    _PIN_A3_TYPEC_GPIO7_0_OD = 0x07,
    _PIN_A3_TEST12B_OUT0 = 0x08,
    _PIN_A3_TEST12B_OUT1 = 0x09,
    _PIN_A3_TEST12B_OUT2 = 0x0A,
    _PIN_A3_TEST12B_OUT3 = 0x0B,
    _PIN_A3_TEST12B_OUT4 = 0x0C,
    _PIN_A3_TEST12B_OUT5 = 0x0D,
    _PIN_A3_TEST12B_OUT6 = 0x0E,
    _PIN_A3_TEST12B_OUT7 = 0x0F,
    _PIN_A3_TEST12B_OUT8 = 0x10,
    _PIN_A3_TEST12B_OUT9 = 0x11,
    _PIN_A3_TEST12B_OUT10 = 0x12,
    _PIN_A3_TEST12B_OUT11 = 0x13,
    _PIN_A3_NC = _PIN_A3_GPO_PP,
} EnumPinshareInfoPINA3;

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_P0
// Pinshare : 0x108B
// MCU Ctrl : 0x222B at _PIN_G5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_G5                                 (_PIN_G5_GPI)

typedef enum
{
    _PIN_G5_GPI = 0x00,
    _PIN_G5_GPO_PP = 0x01,
    _PIN_G5_GPO_OD = 0x02,
    _PIN_G5_TEST12B_OUT0 = 0x03,
    _PIN_G5_TEST12B_OUT1 = 0x04,
    _PIN_G5_TEST12B_OUT2 = 0x05,
    _PIN_G5_TEST12B_OUT3 = 0x06,
    _PIN_G5_TEST12B_OUT4 = 0x07,
    _PIN_G5_TEST12B_OUT5 = 0x08,
    _PIN_G5_TEST12B_OUT6 = 0x09,
    _PIN_G5_TEST12B_OUT7 = 0x0A,
    _PIN_G5_TEST12B_OUT8 = 0x0B,
    _PIN_G5_TEST12B_OUT9 = 0x0C,
    _PIN_G5_TEST12B_OUT10 = 0x0D,
    _PIN_G5_TEST12B_OUT11 = 0x0E,
    _PIN_G5_NC = _PIN_G5_GPO_PP,
} EnumPinshareInfoPING5;

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_N0
// Pinshare : 0x108C
// MCU Ctrl : 0x222C at _PIN_F4_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_F4                                 (_PIN_F4_GPI)

typedef enum
{
    _PIN_F4_GPI = 0x00,
    _PIN_F4_GPO_PP = 0x01,
    _PIN_F4_GPO_OD = 0x02,
    _PIN_F4_TEST12B_OUT0 = 0x03,
    _PIN_F4_TEST12B_OUT1 = 0x04,
    _PIN_F4_TEST12B_OUT2 = 0x05,
    _PIN_F4_TEST12B_OUT3 = 0x06,
    _PIN_F4_TEST12B_OUT4 = 0x07,
    _PIN_F4_TEST12B_OUT5 = 0x08,
    _PIN_F4_TEST12B_OUT6 = 0x09,
    _PIN_F4_TEST12B_OUT7 = 0x0A,
    _PIN_F4_TEST12B_OUT8 = 0x0B,
    _PIN_F4_TEST12B_OUT9 = 0x0C,
    _PIN_F4_TEST12B_OUT10 = 0x0D,
    _PIN_F4_TEST12B_OUT11 = 0x0E,
    _PIN_F4_NC = _PIN_F4_GPO_PP,
} EnumPinshareInfoPINF4;

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_P1
// Pinshare : 0x108D
// MCU Ctrl : 0x222D at _PIN_DPRX_AUX_P_2H5_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_H5                                 (_PIN_H5_GPI)

typedef enum
{
    _PIN_H5_GPI = 0x00,
    _PIN_H5_GPO_PP = 0x01,
    _PIN_H5_GPO_OD = 0x02,
    _PIN_H5_TEST12B_OUT0 = 0x03,
    _PIN_H5_TEST12B_OUT1 = 0x04,
    _PIN_H5_TEST12B_OUT2 = 0x05,
    _PIN_H5_TEST12B_OUT3 = 0x06,
    _PIN_H5_TEST12B_OUT4 = 0x07,
    _PIN_H5_TEST12B_OUT5 = 0x08,
    _PIN_H5_TEST12B_OUT6 = 0x09,
    _PIN_H5_TEST12B_OUT7 = 0x0A,
    _PIN_H5_TEST12B_OUT8 = 0x0B,
    _PIN_H5_TEST12B_OUT9 = 0x0C,
    _PIN_H5_TEST12B_OUT10 = 0x0D,
    _PIN_H5_TEST12B_OUT11 = 0x0E,
    _PIN_H5_NC = _PIN_H5_GPO_PP,
} EnumPinshareInfoPINH5;

//---------------------------------------------------------------------------
// Function : DP_SINK_ASS_N1
// Pinshare : 0x108E
// MCU Ctrl : 0x222E at _PIN_F3_MCU_REG
//---------------------------------------------------------------------------
#define _PIN_F3                                 (_PIN_F3_GPI)

typedef enum
{
    _PIN_F3_GPI = 0x00,
    _PIN_F3_GPO_PP = 0x01,
    _PIN_F3_GPO_OD = 0x02,
    _PIN_F3_TEST12B_OUT0 = 0x03,
    _PIN_F3_TEST12B_OUT1 = 0x04,
    _PIN_F3_TEST12B_OUT2 = 0x05,
    _PIN_F3_TEST12B_OUT3 = 0x06,
    _PIN_F3_TEST12B_OUT4 = 0x07,
    _PIN_F3_TEST12B_OUT5 = 0x08,
    _PIN_F3_TEST12B_OUT6 = 0x09,
    _PIN_F3_TEST12B_OUT7 = 0x0A,
    _PIN_F3_TEST12B_OUT8 = 0x0B,
    _PIN_F3_TEST12B_OUT9 = 0x0C,
    _PIN_F3_TEST12B_OUT10 = 0x0D,
    _PIN_F3_TEST12B_OUT11 = 0x0E,
    _PIN_F3_NC = _PIN_F3_GPO_PP,
} EnumPinshareInfoPINF3;

