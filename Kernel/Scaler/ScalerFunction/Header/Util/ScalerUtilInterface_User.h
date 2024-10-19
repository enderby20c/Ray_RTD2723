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
// ID Code      : ScalerUtilInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


//****************************************************************************
// IN-LINE FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : construct DWORD from bit sequence
//                ex: _BIT(11, 7) = (_BIT11 | _BIT10 | _BIT9 | _BIT8 | _BIT7)
// Input Value  : ucHiBit -> high bit range (inclusive)
//                ucLoBit -> low bit range (inclusive)
// Output Value : sequence of bits from _BIT0 to _BIT31
//--------------------------------------------------
__attribute__((always_inline))
static inline DWORD ScalerUtilGetBitSequence(BYTE ucHiBit, BYTE ucLoBit)
{
    return ((((ucHiBit >= 31) && (31 >= ucLoBit)) ? _BIT31 : 0) +
            (((ucHiBit >= 30) && (30 >= ucLoBit)) ? _BIT30 : 0) +
            (((ucHiBit >= 29) && (29 >= ucLoBit)) ? _BIT29 : 0) +
            (((ucHiBit >= 28) && (28 >= ucLoBit)) ? _BIT28 : 0) +
            (((ucHiBit >= 27) && (27 >= ucLoBit)) ? _BIT27 : 0) +
            (((ucHiBit >= 26) && (26 >= ucLoBit)) ? _BIT26 : 0) +
            (((ucHiBit >= 25) && (25 >= ucLoBit)) ? _BIT25 : 0) +
            (((ucHiBit >= 24) && (24 >= ucLoBit)) ? _BIT24 : 0) +
            (((ucHiBit >= 23) && (23 >= ucLoBit)) ? _BIT23 : 0) +
            (((ucHiBit >= 22) && (22 >= ucLoBit)) ? _BIT22 : 0) +
            (((ucHiBit >= 21) && (21 >= ucLoBit)) ? _BIT21 : 0) +
            (((ucHiBit >= 20) && (20 >= ucLoBit)) ? _BIT20 : 0) +
            (((ucHiBit >= 19) && (19 >= ucLoBit)) ? _BIT19 : 0) +
            (((ucHiBit >= 18) && (18 >= ucLoBit)) ? _BIT18 : 0) +
            (((ucHiBit >= 17) && (17 >= ucLoBit)) ? _BIT17 : 0) +
            (((ucHiBit >= 16) && (16 >= ucLoBit)) ? _BIT16 : 0) +
            (((ucHiBit >= 15) && (15 >= ucLoBit)) ? _BIT15 : 0) +
            (((ucHiBit >= 14) && (14 >= ucLoBit)) ? _BIT14 : 0) +
            (((ucHiBit >= 13) && (13 >= ucLoBit)) ? _BIT13 : 0) +
            (((ucHiBit >= 12) && (12 >= ucLoBit)) ? _BIT12 : 0) +
            (((ucHiBit >= 11) && (11 >= ucLoBit)) ? _BIT11 : 0) +
            (((ucHiBit >= 10) && (10 >= ucLoBit)) ? _BIT10 : 0) +
            (((ucHiBit >= 9) && (9 >= ucLoBit)) ? _BIT9 : 0) +
            (((ucHiBit >= 8) && (8 >= ucLoBit)) ? _BIT8 : 0) +
            (((ucHiBit >= 7) && (7 >= ucLoBit)) ? _BIT7 : 0) +
            (((ucHiBit >= 6) && (6 >= ucLoBit)) ? _BIT6 : 0) +
            (((ucHiBit >= 5) && (5 >= ucLoBit)) ? _BIT5 : 0) +
            (((ucHiBit >= 4) && (4 >= ucLoBit)) ? _BIT4 : 0) +
            (((ucHiBit >= 3) && (3 >= ucLoBit)) ? _BIT3 : 0) +
            (((ucHiBit >= 2) && (2 >= ucLoBit)) ? _BIT2 : 0) +
            (((ucHiBit >= 1) && (1 >= ucLoBit)) ? _BIT1 : 0) +
            ((0 == ucLoBit) ? _BIT0 : 0));
}
