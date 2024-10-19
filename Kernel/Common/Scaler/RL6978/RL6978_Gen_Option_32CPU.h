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
// ID Code      : RL6978_Gen_Option_32CPU.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// HW support for cpu32 platform
//--------------------------------------------------
#define _HW_CPU32_SCPU_SUPPORT                                  _OFF
#define _HW_CPU32_BW32_SUPPORT                                  _OFF
#define _HW_CPU32_RBUS2DDR_SUPPORT                              _OFF
#define _HW_CPU32_NOTIFY_INT_SUPPORT                            _OFF
#define _HW_CPU32_TO_TIMER32_CLK_DIV                            1   // KR4 vs TIMER32
#define _HW_CPU32_TO_SYSTICK_CLK_DIV                            _HW_CPU32_TO_TIMER32_CLK_DIV    // Use TIMER3 as SysTick Timer


//--------------------------------------------------
// CPU D-cache setting
//--------------------------------------------------
#define _HW_CPU32_KCPU_HAVE_DCACHE                              (_TRUE)
#define _HW_CPU32_SCPU_HAVE_DCACHE                              (_FALSE)

#define _HW_CPU32_CPU_HAVE_DCACHE                               (((_HW_CPU32_IS_BOOT_CPU == _TRUE) && (_HW_CPU32_KCPU_HAVE_DCACHE == _TRUE)) ||\
                                                                 ((_HW_CPU32_IS_BOOT_CPU != _TRUE) && (_HW_CPU32_SCPU_HAVE_DCACHE == _TRUE)))

#define _HW_CPU32_KCPU_DCACHE_LINE_SIZE_IN_BYTE                 (32)
#define _HW_CPU32_SCPU_DCACHE_LINE_SIZE_IN_BYTE                 (0)


//--------------------------------------------------
// Definations of CPU32 Clock Source Frequency (KHz)
//--------------------------------------------------
#define _HW_CPU32_CLK_SRC_IOSC                                  _HW_INTERNAL_OSC_XTAL   // 28MHz,+-5%
#define _HW_CPU32_CLK_SRC_EXTAL                                 _EXT_XTAL   // 14.318MHz,+-300ppm
#define _HW_CPU32_CLK_SRC_EMCU_PLL                              _EMCU_PLL_SPEED_480M
#define _HW_CPU32_CLK_SRC_M2PLL                                 _M2PLL_CLK_KHZ  // 351MHz,+-1%


//--------------------------------------------------
// CPU Can MemoryMap Access DDR
//--------------------------------------------------
#define _HW_CPU32_KCPU_MEMORYMAP_ACCESS_DDR                     (_TRUE)
#define _HW_CPU32_SCPU_MEMORYMAP_ACCESS_DDR                     (_FALSE)
#define _HW_CPU32_MEMORYMAP_ACCESS_DDR                          (_HW_CPU32_KCPU_MEMORYMAP_ACCESS_DDR)
#define _HW_CPU32_ALLOCATE_DDR_SPACE                            (_HW_CPU32_KCPU_MEMORYMAP_ACCESS_DDR)
#define _HW_CPU32_CACHED_DDR                                    (_TRUE)


//--------------------------------------------------
// RXI300 SYSTEM BUS HW Generation
//--------------------------------------------------
#define _HW_CPU32_RXI300_GEN                                    (_RXI300_HW_GEN_1)


//--------------------------------------------------
// FW size for cpu32 in DDR
//--------------------------------------------------
#define _FW_CPU32_DDR_MEMORY_SIZE                               ((((DWORD)_KCPU_DDR_TOTAL_ALLOCATE_SIZE * 8 * _MEMORY_ROW / _MEMORY_SIZE) + 4) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM)
#define _FW_CPU32_MAIN_PROCESS_CPU                              _CPU_ID_KCPU


//--------------------------------------------------
// FW SCPU HIGH SPEED CPU
//--------------------------------------------------
#define _FW_CPU32_IS_HIGH_SPEED_CPU                             (_TRUE)

//--------------------------------------------------
// FW CPU USE INT31
//--------------------------------------------------
#define _FW_CPU32_USE_INT31_FOR_SCALER_INT                      _OFF

