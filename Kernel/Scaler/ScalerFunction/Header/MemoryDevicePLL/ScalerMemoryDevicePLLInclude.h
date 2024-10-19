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
// ID Code      : ScalerMemoryDevicePLLInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definations of OESYNC
//--------------------------------------------------
#define OESYNC_OP_SEL(pi, usSelBit)                                ((((pi) & _BIT4) == _BIT4) ? (usSelBit) : 0x00)

#define GET_OESYNC_SETTING(stPI)                                   (\
                                                                    OESYNC_OP_SEL(((stPI).ucCLK), _BIT0) |\
                                                                    OESYNC_OP_SEL(((stPI).ucCMD), _BIT1) |\
                                                                    OESYNC_OP_SEL(((stPI).ucDQS0), _BIT2) |\
                                                                    OESYNC_OP_SEL(((stPI).ucDQS1), _BIT3) |\
                                                                    OESYNC_OP_SEL(((stPI).ucDQ0), _BIT6) |\
                                                                    OESYNC_OP_SEL(((stPI).ucDQ1), _BIT7)\
                                                                    )


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMemoryDevicePLLSetPLLFreq(DWORD ulFreq);

