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
// ID Code      : Led_Driver_Config_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __LED_DRIVER_CONFIG_CHECK_H__
#define __LED_DRIVER_CONFIG_CHECK_H__

#if(_SPI_SUPPORT != _ON)
#warning "_SPI_SUPPORT should be _ON for LED driver!"
#endif

#if(_LOCAL_DIMMING_FUNCTION == _ON)
#if((_LOCAL_DIMMING_PWM2SPI_SPI_OUTPUT_SWAP == _ON) && (_SPI1_SUPPORT == _OFF))
#error "_SPI1_SUPPORT should be _ON for LED driver when PWM2SPI SPI Output Swap is On!"
#endif

#if((_LOCAL_DIMMING_PWM2SPI_SPI_OUTPUT_SWAP == _OFF) && (_SPI0_SUPPORT == _OFF))
#error "_SPI0_SUPPORT should be _ON for LED driver when PWM2SPI SPI Output Swap is Off!"
#endif

#if((_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON) && (_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_04_AUSTRIA_AS3824))
#warning "When _LOCAL_DIMMING_MBR_MODE_SUPPORT is _ON but LED Driver isn't AS3824, please check LED drvier has local A-dimming which can work on direct mode"
#endif
#endif

#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
#if(((((4095 * (_LOCAL_DIMMING_PWM2SPI_PWM_GAIN_CALC + 1)) / 4096) + _LOCAL_DIMMING_PWM2SPI_PWM_MIN) << _LOCAL_DIMMING_PWM2SPI_DATA_LEFT_SHIFT) < _DEVICE_LED_DRIVER_PWM_MAX)
#warning "Please enlarge _LOCAL_DIMMING_PWM2SPI_PWM_MIN or lower _DEVICE_LED_DRIVER_PWM_MAX for Match PWM MAX Setting!"
#endif
#else
#warning "_SPI_BACKLIGHT_DIMMING_SUPPORT should be _ON for LED driver!"
#endif

#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM0)
#if(_PWM0_EN != _ON)
#warning "_PWM0_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM0"
#endif
#if(_PWM0_BYPASS_MODE_EN != _ON)
#warning "_PWM0_BYPASS_MODE_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM0"
#endif
#if(_PWM0_RST_EN != _OFF)
#warning "_PWM0_RST_EN should be _OFF when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM0"
#endif
#endif

#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM1)
#if(_PWM1_EN != _ON)
#warning "_PWM1_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM1"
#endif
#if(_PWM1_BYPASS_MODE_EN != _ON)
#warning "_PWM1_BYPASS_MODE_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM1"
#endif
#if(_PWM1_RST_EN != _OFF)
#warning "_PWM1_RST_EN should be _OFF when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM1"
#endif
#endif

#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM2)
#if(_PWM2_EN != _ON)
#warning "_PWM2_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM2"
#endif
#if(_PWM2_BYPASS_MODE_EN != _ON)
#warning "_PWM2_BYPASS_MODE_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM2"
#endif
#if(_PWM2_RST_EN != _OFF)
#warning "_PWM2_RST_EN should be _OFF when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM2"
#endif
#endif

#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM3)
#if(_PWM3_EN != _ON)
#warning "_PWM3_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM3"
#endif
#if(_PWM3_BYPASS_MODE_EN != _ON)
#warning "_PWM3_BYPASS_MODE_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM3"
#endif
#if(_PWM3_RST_EN != _OFF)
#warning "_PWM3_RST_EN should be _OFF when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM3"
#endif
#endif

#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM4)
#if(_PWM4_EN != _ON)
#warning "_PWM4_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM4"
#endif
#if(_PWM4_BYPASS_MODE_EN != _ON)
#warning "_PWM4_BYPASS_MODE_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM4"
#endif
#if(_PWM4_RST_EN != _OFF)
#warning "_PWM4_RST_EN should be _OFF when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM4"
#endif
#endif

#if(_DEVICE_LED_DRIVER_EXTERNAL_PWM == _PWM5)
#if(_PWM5_EN != _ON)
#warning "_PWM5_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM5"
#endif
#if(_PWM5_BYPASS_MODE_EN != _ON)
#warning "_PWM5_BYPASS_MODE_EN should be _ON when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM5"
#endif
#if(_PWM5_RST_EN != _OFF)
#warning "_PWM5_RST_EN should be _OFF when _DEVICE_LED_DRIVER_EXTERNAL_PWM = _PWM5"
#endif
#endif

#if(_DEVICE_LED_DRIVER_PWM_MAX > _DEFAULT_PERIOD_VALUE)
#warning "_DEVICE_LED_DRIVER_PWM_MAX > _DEFAULT_PERIOD_VALUE !"
#endif

#if(_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS == _ON)
#if(_LOCK_REG_VALUE != 0x0A)
#warning "When _LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS is _ON, _LOCK_REG_VALUE should be 0x0A for AMS Series LED Driver !"
#endif
#endif

#if((_MAX_PWM2SPI_SMODE_REUSE_TIMES != 1) && !((_HW_CPU32_BW32_SUPPORT == _ON) && (_SCPU_SUPPORT == _ON)))
#warning "_MAX_PWM2SPI_SMODE_REUSE_TIMES can only be 1"
#endif

#endif // End of #ifndef __LED_DRIVER_CONFIG_CHECK_H__

