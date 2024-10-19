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
// ID Code      : ScalerMemoryDevicePLL.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_MEMORY_DEVICE_PLL_H__
#define __SCALER_MEMORY_DEVICE_PLL_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#if((_HW_MEMORY_DEVICE_PLL_GEN_TYPE == _MEMORY_DEVICE_PLL_GEN_3) || (_HW_MEMORY_DEVICE_PLL_GEN_TYPE == _MEMORY_DEVICE_PLL_GEN_4))

//--------------------------------------------------
// Definitions of DDR3PLL N.F code
//--------------------------------------------------
#if(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_1066MHZ)
#define _DDR_PLL_N_CODE                             (74 - 3)// 1066.496Mhz
#define _DDR_PLL_F_CODE                             (996)
#elif(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_933MHZ)
#define _DDR_PLL_N_CODE                             (65 - 3)// 932.998Mhz
#define _DDR_PLL_F_CODE                             (333)
#elif(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_800MHZ)
#define _DDR_PLL_N_CODE                             (55 - 3)// 799.997Mhz
#define _DDR_PLL_F_CODE                             (1788)
#elif(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_667MHZ)
#define _DDR_PLL_N_CODE                             (46 - 3)// 666.493Mhz
#define _DDR_PLL_F_CODE                             (1125)
#elif(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_533MHZ)
#define _DDR_PLL_N_CODE                             (37 - 3)// 532.99594Mhz
#define _DDR_PLL_F_CODE                             (462)
#elif(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_400MHZ)
#define _DDR_PLL_N_CODE                             (27 - 3)// 532.99594Mhz
#define _DDR_PLL_F_CODE                             (1918)
#else
#define _DDR_PLL_N_CODE                             (0)
#define _DDR_PLL_F_CODE                             (0)
#endif
#endif
#endif

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
#if(_HW_MEMORY_DEVICE_PLL_GEN_TYPE == _MEMORY_DEVICE_PLL_GEN_0)

//--------------------------------------------------
// Definitions of DDR3PLL N.F code
//--------------------------------------------------
#if(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_667MHZ)
#define _DDR_PLL_N_CODE                             (46 - 3)
#define _DDR_PLL_F_CODE                             (1125)
#elif(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_600MHZ)
#define _DDR_PLL_N_CODE                             (41 - 3)
#define _DDR_PLL_F_CODE                             (1853)
#elif(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_533MHZ)
#define _DDR_PLL_N_CODE                             (37 - 3)
#define _DDR_PLL_F_CODE                             (462)
#elif(_FW_DDR_PLL_CLOCK == _MEMORY_SPEED_400MHZ)
#define _DDR_PLL_N_CODE                             (27 - 3)
#define _DDR_PLL_F_CODE                             (1918)
#else
#define _DDR_PLL_N_CODE                             (0)
#define _DDR_PLL_F_CODE                             (0)
#endif
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif // End of #ifndef __SCALER_MEMORY_DEVICE_PLL_H__
