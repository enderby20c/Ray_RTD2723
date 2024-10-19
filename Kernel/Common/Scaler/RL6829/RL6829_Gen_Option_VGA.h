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
// ID Code      : RL6829_Gen_Option_VGA.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// VGA/ADC options
//--------------------------------------------------
//! _ON if VGA/ADC/ADC bandgap exists
#define _HW_VGA_ADC_SUPPORT                                     _OFF

//! _ON if VGA VGIP exists
#define _HW_VGA_CAPTURE_SUPPORT                                 _OFF

//! value to offset VGA V auto-function result for compensating latch edge difference
#define _HW_VGATOP_VSTART_OFFSET                                (0)

//! value for HS edge delay from clock edge in VGIP (unit: 1/64 ns)
#define _HW_VGA_PHASE_DELAY_TIME                                _GEN_NONE

//! value for maximum VGA APLL clock frequency
#define _HW_VGA_ADC_SAMPLE_CLOCK_LIMIT                          _GEN_NONE

//! value for maximum VGA APLL clock H total
#define _HW_VGA_ADC_PIXEL_WIDTH_LIMIT                           _GEN_NONE // Confirm

//-------------------------------------------------
// ADCNR Gen
//-------------------------------------------------
#define _HW_ADCNR_TYPE                                          _GEN_NONE // Confirm

//-------------------------------------------------
// Digital Filter Gen
//-------------------------------------------------
#define _HW_DIGITAL_FILTER_TYPE                                 _GEN_NONE // Confirm

//-------------------------------------------------
// Ringing Filter Gen
//-------------------------------------------------
#define _HW_RINGING_FILTER_TYPE                                 _GEN_NONE // Confirm
