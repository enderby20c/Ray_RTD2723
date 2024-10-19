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

#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_06_MCU_1152_BOE)

//----------------------------------------------------------------------------------------------------
// ID Code      : LedDriver_06_MCU_1152_BOE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PIN_INVERT      0               // 0:High pulse ; 1:Low Pulse
#define _LOCAL_DIMMING_PWM2SPI_UPD_SYNC_PULSE_FW_XUS    25
#define _LOCAL_DIMMING_PWM2SPI_APPEND_NUM_OF_BYTES      0               // 0:Not Append ; 1:Append
#define _LOCAL_DIMMING_PWM2SPI_PATTERN_OF_DUMMY_BYTE    0               // 0:0x00 ; 1:0xFF
#define _LOCAL_DIMMING_PWM2SPI_DUMMY_WIDTH_BY_BYTE      1
#define _DEVICE_LED_DRIVER_COMMUNICATE_TYPE             _INTERFACE_SPI
#define _DEVICE_LED_DRIVER_SUPPORT_BROADCAST            _OFF
#define _DEVICE_LED_DRIVER_SPI_CMD_HEADER_BYTES         2
#define _DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE            2
#define _DEVICE_LED_DRIVER_REG_BYTE_SWAP                _OFF
#define _DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE            2
#define _DEVICE_LED_DRIVER_PWM_ADDRESS_STEP             (_DEVICE_LED_DRIVER_PWM_WIDTH_BY_BYTE / _DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE)
#define _DEVICE_LED_DRIVER_READ_DUMMY_BYTE_NUM          0
#define _LOCAL_DIMMING_PWM2SPI_DATA_BYTE_SWAP           _ON
#define _DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM            1
#define _DEVICE_LED_DRIVER_MCU_TYPE                     _ON

// #define _DEVICE_LED_DRIVER_BROADCAST_ID                 0x00
// #define _DEVICE_LED_DRIVER_VALID_ADDR                   0x13
// #define _DEVICE_LED_DRIVER_VALID_BY_CE_NO_PWM           0x00
// #define _DEVICE_LED_DRIVER_VALID_BY_VSYNC_NO_PWM        0x02
// #define _DEVICE_LED_DRIVER_VALID_BY_CE_EXT_PWM          0x01
// #define _DEVICE_LED_DRIVER_VALID_BY_VSYNC_EXT_PWM       0x03
// #define _DEVICE_LED_DRIVER_UPDSYNC_DEFER_DCLK_CNT       0
// #define _DEVICE_LED_DRIVER_ADIM_ADDR                    0x70
// #define _DEVICE_LED_DRIVER_ADIM_WIDTH_BY_BYTE           1
// #define _DEVICE_LED_DRIVER_ADIM_BYTE_SWAP               _OFF


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#endif
