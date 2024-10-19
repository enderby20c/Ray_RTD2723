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
// ID Code      : ScalerPinshareInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//------------------------------------------------------------
// Enumerations of Pin Share Config type that user can adjust
//------------------------------------------------------------
typedef enum
{
    _CONFIG_TYPE_GPI,
    _CONFIG_TYPE_GPO_PP,
    _CONFIG_TYPE_GPO_OD,
    _CONFIG_TYPE_PWM0_OD,
    _CONFIG_TYPE_PWM0_PP,
    _CONFIG_TYPE_PWM1_OD,
    _CONFIG_TYPE_PWM1_PP,
    _CONFIG_TYPE_PWM2_OD,
    _CONFIG_TYPE_PWM2_PP,
    _CONFIG_TYPE_PWM3_OD,
    _CONFIG_TYPE_PWM3_PP,
    _CONFIG_TYPE_PWM4_OD,
    _CONFIG_TYPE_PWM4_PP,
    _CONFIG_TYPE_PWM5_OD,
    _CONFIG_TYPE_PWM5_PP,
    _CONFIG_TYPE_PWM_UPD_SYNC_PP,
    _CONFIG_TYPE_USB_SPI_CLK,
    _CONFIG_TYPE_USB_SPI_SI,
    _CONFIG_TYPE_USB_SPI_SO,
    _CONFIG_TYPE_USB_SPI_CEB0_0,

    _CONFIG_TYPE_TCON_3,
    _CONFIG_TYPE_TCON_8,
    _CONFIG_TYPE_TCON_12,
    _CONFIG_TYPE_TCON_13,

    _CONFIG_TYPE_MCK,
    _CONFIG_TYPE_SCK,
    _CONFIG_TYPE_WS,
    _CONFIG_TYPE_SD0,
    _CONFIG_TYPE_SD1,
    _CONFIG_TYPE_SD2,
    _CONFIG_TYPE_SD3,
} EnumPinConfigType;

#if(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE != _TYPE_C_10_BIT_SARADC_NONE)
//--------------------------------------------------
// Definitions of 10-Bit ADC Channels
//--------------------------------------------------
typedef enum
{
#if(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_0)
    _TYPE_C_0_VMON = 0x00,
    _TYPE_C_1_VMON = 0x01,
    _TYPE_C_LOC_PW = 0x02,

#elif(_HW_TYPE_C_10_BIT_SARADC_GEN_TYPE == _TYPE_C_10_BIT_SARADC_GEN_1)
    _TYPE_C_0_VBUS_LOW = 0x00,
    _TYPE_C_0_VBUS_HIGH = 0x01,
    _TYPE_C_1_VBUS_LOW = 0x02,
    _TYPE_C_1_VBUS_HIGH = 0x03,
#endif
}EnumTypeC10BitAdcChannel;
#endif

//--------------------------------------------------
// Definitions of Pad Driven Current
//--------------------------------------------------
typedef enum
{
    _DRIVING_CURRENT_LOW = 0x00,
    _DRIVING_CURRENT_HIGH = 0x01,
}EnumPadDrivingCurrentType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

