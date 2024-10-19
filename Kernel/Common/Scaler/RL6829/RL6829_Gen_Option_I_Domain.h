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
// ID Code      : RL6829_Gen_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// I Domain Format Conversion
//--------------------------------------------------
#define _HW_FORMAT_CONVERSION_SUPPORT                           _ON
#define _HW_FORMAT_CONVERSION_FB_SUPPORT                        _ON
#define _HW_FORMAT_CONVERSION_PIXEL_MODE                        _ON
#define _HW_FORMAT_CONVERSION_EO_MODE                           _ON
#define _HW_FORMAT_CONVERSION_SD_MODE                           _FORMAT_CONVERSION_SD_HALF_FOUR
#define _HW_FORMAT_CONVERSION_PATH1_SUPPORT                     _ON
#define _HW_FORMAT_CONVERSION_PATH2_SUPPORT                     _ON
#define _HW_FORMAT_CONVERSION_PATH3_SUPPORT                     _ON
#define _HW_FORMAT_CONVERSION_PATH4_SUPPORT                     _ON
#define _HW_FORMAT_CONVERSION_PATH5_SUPPORT                     _ON
#define _HW_FORMAT_CONVERSION_CLK_GATED_SUPPORT                 _ON
#define _HW_FORMAT_CONVERSION_EAGLE_SIGHT_SUPPORT               _ON
#define _HW_FORMAT_CONVERSION_EO_MODE_BUFFER_WIDTH              (5120)

//--------------------------------------------------
// On-line measure settings
//--------------------------------------------------
//! on-line measure support for input paths
#define _HW_IDOMAIN_M1_ONLINE_MEASURE_SUPPORT                   _ON
#define _HW_IDOMAIN_M2_ONLINE_MEASURE_SUPPORT                   _ON
#define _HW_IDOMAIN_S1_ONLINE_MEASURE_SUPPORT                   _ON
#define _HW_IDOMAIN_S2_ONLINE_MEASURE_SUPPORT                   _ON

//! on-line measure register page for input paths
#define _HW_PAGED_M1_ON_LINE_MEAS                               0x03
#define _HW_PAGED_M2_ON_LINE_MEAS                               0x43
#define _HW_PAGED_S1_ON_LINE_MEAS                               0x83
#define _HW_PAGED_S2_ON_LINE_MEAS                               0x50

//--------------------------------------------------
// Off-line measure clk divider
//--------------------------------------------------
#define _HW_IDOMAIN_OFFLINE_MEASURE_CLK_DIV_SUPPORT             _ON

//--------------------------------------------------
// Off-line measure Hstart support
//--------------------------------------------------
#define _HW_IDOMAIN_OFFLINE_HSTART_MEASURE_SUPPORT              _OFF

//--------------------------------------------------
// off-line measure Vstart support
//--------------------------------------------------
#define _HW_IDOMAIN_OFFLINE_VSTART_MEASURE_SUPPORT              _OFF

//-------------------------------------------------
// VGIP Bit
//-------------------------------------------------
#define _HW_VGIP_IV_CAPTURE_BIT                                 (_13_BIT)
#define _HW_VGIP_IV_DELAY_BIT                                   (_10_BIT) // Confirm

//-------------------------------------------------
// Measure H/ V timing Bit
//-------------------------------------------------
#define _HW_MEASURE_H_BIT                                       (_13_BIT)
#define _HW_MEASURE_V_BIT                                       (_15_BIT)

//--------------------------------------------------
// FW FRL Measure from interface
//--------------------------------------------------
#define _FW_FRL_MEASURE_FROM_INTERFACE                          _OFF// ADD

