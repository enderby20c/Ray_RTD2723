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
// ID Code      : User_LedDriver_Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// LED Driver Include Path
//--------------------------------------------------
#if(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_01_O2_OZ9913)
#include <LedDriver_01_O2_OZ9913.h>
#elif(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_02_AUSTRIA_AS3820)
#include <LedDriver_02_AUSTRIA_AS3820.h>
#elif(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_03_AUSTRIA_AS3812)
#include <LedDriver_03_AUSTRIA_AS3812.h>
#elif(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_04_AUSTRIA_AS3824)
#include <LedDriver_04_AUSTRIA_AS3824.h>
#elif(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_05_MBLOCK_MBI6353)
#include <LedDriver_05_MBLOCK_MBI6353.h>
#elif(_DEVICE_LED_DRIVER_TYPE == _DEVICE_LED_DRIVER_06_MCU_1152_BOE)
#include <LedDriver_06_MCU_1152_BOE.h>
#endif
