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
// ID Code      : RL6952_Gen_Option_MCU.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of XRAM addresses
//--------------------------------------------------
#define _HW_XRAM_ISP_MAPPING_ADDR_START                         (0xA0101400) // Modify

//--------------------------------------------------
// HW Fw Update Fw  Speed up Support
//--------------------------------------------------
#define _HW_ISP_SPEED_UP_SUPPORT                                _ON
#define _HW_XRAM_BG_ISP_SPEED_UP_MAPPING_ADDR_START             (0xA0101600) // Invaild Address for not use
#define _HW_ISP_SPEED_UP_SRAM_SIZE                              (512U)

//--------------------------------------------------
// HW XRAM Reset Support
//--------------------------------------------------
#define _HW_XRAM_AUTO_RESET_TO_ZERO_SUPPORT                     _OFF

//--------------------------------------------------
// Definitions of DDCRAM info
//--------------------------------------------------
#define _HW_DDCRAM_START_ADDRESS                                (0xA0100200)
#define _HW_DDCRAM_BLOCK_STEP                                   (1024U) // Confirm

//--------------------------------------------------
// DDC Exist
//--------------------------------------------------
#define _HW_ISP_DDC_EXIST                                       _ON // Modify
#define _HW_ADC_DDC_EXIST                                       _OFF
#define _HW_DDC0_EXIST                                          _ON
#define _HW_DDC1_EXIST                                          _ON
#define _HW_DDC2_EXIST                                          _ON
#define _HW_DDC3_EXIST                                          _ON
#define _HW_DDC4_EXIST                                          _ON
#define _HW_DDC5_EXIST                                          _OFF // Confirm


//--------------------------------------------------
// DDCCI Exist
//--------------------------------------------------
#define _HW_DDCCI0_EXIST                                        _ON
#define _HW_DDCCI1_EXIST                                        _ON
#define _HW_DDCCI2_EXIST                                        _OFF
#define _HW_DDCCI3_EXIST                                        _OFF
#define _HW_DDCCI4_EXIST                                        _ON


//--------------------------------------------------
// DDC Mapping Switch
//--------------------------------------------------
#define _HW_DDC_CHANNEL_SWITCH_SUPPORT                          _OFF // Confirm

//--------------------------------------------------
// HW SarADC Support and Bit Num
//--------------------------------------------------
#define _HW_MCU_SARADC_SUPPORT                                  _SARADC_8BIT

//--------------------------------------------------
// HW SARADC Gen Options
//--------------------------------------------------
#define _HW_MCU_SARADC_GEN                                      _HW_SARADC_GEN_1

//--------------------------------------------------
// MCU PWM Hw Clock Source refence M2Pll / 2
//--------------------------------------------------
#define _HW_MCU_PWM_HW_REF_HALF_OF_M2PLL                        _OFF

//--------------------------------------------------
// MCU PWM Support Bit
//--------------------------------------------------
#define _HW_MCU_PWM_BIT_SUPPORT                                 _PWM_12BIT// Confirm

//-------------------------------------------------
// EPLL Option
//-------------------------------------------------
#define _HW_EPLL_SUPPORT                                        _OFF// Confirm

//--------------------------------------------------
// SPI Interface Count
//--------------------------------------------------
#define _HW_SPI0_EXIST                                          _ON
#define _HW_SPI1_EXIST                                          _ON// Confirm
#define _HW_SPI2_EXIST                                          _ON // Add

//-------------------------------------------------
// FW Flash Clock Option
//-------------------------------------------------
#define _HW_FLASH_CLK_SOURCE                                    _FLASH_EXT_XTAL_CLK// Confirm
#define _HW_FLASH_WRITE_ACCESS_METHOD                           _FLASH_WRITE_PORT_ACCESS
#define _HW_FLASH_READ_ACCESS_METHOD                            _MEMORY_MAP_ACCESS
#define _HW_FLASH_4BYTE_MODE_SUPPORT                            _OFF

//--------------------------------------------------
// HW Support Serial Port
//--------------------------------------------------
#define _HW_EXTERNAL_SERIAL_PORT_0_EXIST                        _ON
#define _HW_EXTERNAL_SERIAL_PORT_1_EXIST                        _ON
#define _HW_EXTERNAL_SERIAL_PORT_2_EXIST                        _ON // Modify

//--------------------------------------------------
// HW IIC Support
//--------------------------------------------------
#define _HW_HW_IIC_0_EXIST                                      _ON
#define _HW_HW_IIC_1_EXIST                                      _ON // Modify
#define _HW_TYPEC_IIC_0_EXIST                                   _ON
#define _HW_TYPEC_IIC_1_EXIST                                   _ON

//--------------------------------------------------
// HW IIC Gen Options
//--------------------------------------------------
#define _HW_HW_IIC_GEN                                          _HW_IIC_GEN_2

//--------------------------------------------------
// HW HDCP2 TX KEY for IROM Address
//--------------------------------------------------
#define _HW_TX_HDCP_2_2_KEY_START_ADDRESS_IROM                  0xBFC04E00 // Modify

//--------------------------------------------------
// HW GPIO Port Support
//--------------------------------------------------
#define _HW_GPIO_PORT_18_1F_SUPPORT                             _OFF


////////
// FW //
////////
//--------------------------------------------------
// _PWM_RST_BY_TCON SELECT
//--------------------------------------------------
#define _HW_PWM_RST_BY_TCON_SELECT                              _TCON8 // Confirm

#define _FW_SPI_CHECK_PINSHARE_CONFIG                           _OFF
