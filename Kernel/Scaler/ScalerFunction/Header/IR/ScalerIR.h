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
// ID Code      : ScalerIR.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_IR_H__
#define __SCALER_IR_H__

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _IR_SAMPLE_CLK                  50 // kHz
#define _IR_HW_XTAL_SAMPLE_CLK_DIV      (((WORD)_EXT_XTAL / _IR_SAMPLE_CLK) - 1)
#define _IR_HW_IOSC_SAMPLE_CLK_DIV      (((WORD)_HW_INTERNAL_OSC_XTAL / _IR_SAMPLE_CLK) - 1)

#define _IR_TABLE_1_LENGTH              10
#define _IR_TABLE_2_LENGTH              6
#define _IR_TABLE_3_LENGTH              8
#define _IR_TABLE_4_LENGTH              2

#define _IR_TABLE_1_START               0
#define _IR_TABLE_2_START               (_IR_TABLE_1_LENGTH)
#define _IR_TABLE_3_START               (_IR_TABLE_1_LENGTH + _IR_TABLE_2_LENGTH)
#define _IR_TABLE_4_START               (_IR_TABLE_1_LENGTH + _IR_TABLE_2_LENGTH + _IR_TABLE_3_LENGTH)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile bit g_bIRReceived;
extern volatile BYTE g_pucIRCode[8];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)


#endif // End of #ifndef __SCALER_IR_H__
